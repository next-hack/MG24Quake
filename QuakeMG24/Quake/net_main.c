/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

 Copyright (C) 1996-1997 Id Software, Inc.
 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments)
 on EFR32MG24 and MGM240 port.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 */
// net_main.c
#include "quakedef.h"
#include "net_vcr.h"

qsocket_t *net_activeSockets = NULL;
qsocket_t *net_freeSockets = NULL;
const int net_numsockets = 2;
#if HAS_MULTIPLAYER

qboolean	serialAvailable = false;
qboolean	ipxAvailable = false;
qboolean	tcpipAvailable = false;

int			net_hostport;
int			DEFAULTnet_hostport = 26000;
char		my_ipx_address[NET_NAMELEN];
char		my_tcpip_address[NET_NAMELEN];

void (*GetComPortConfig) (int portNumber, int *port, int *irq, int *baud, qboolean *useModem);
void (*SetComPortConfig) (int portNumber, int port, int irq, int baud, qboolean useModem);
void (*GetModemConfig) (int portNumber, char *dialType, char *clear, char *init, char *hangup);
void (*SetModemConfig) (int portNumber, char *dialType, char *clear, char *init, char *hangup);
#endif
static qboolean listening = false;
#if HAS_MULTIPLAYER
qboolean	slistInProgress = false;
qboolean	slistSilent = false;
qboolean	slistLocal = true;
static QDFLOAT	slistStartTime;
static int		slistLastShown;

static void Slist_Send(void);
static void Slist_Poll(void);
const PollProcedure	slistSendProcedure = {NULL, 0.0, Slist_Send};
const PollProcedure	slistPollProcedure = {NULL, 0.0, Slist_Poll};
#endif

sizebuf_t net_message;
int net_activeconnections = 0;

int messagesSent = 0;
int messagesReceived = 0;
int unreliableMessagesSent = 0;
int unreliableMessagesReceived = 0;
//qboolean	configRestored = false;
#if USE_ORIGINAL_CVAR
cvar_t	net_messagetimeout = {"net_messagetimeout","300"};
cvar_t	hostname = {"hostname", "UNNAMED"};

cvar_t	config_com_port = {"_config_com_port", "0x3f8", true};
cvar_t	config_com_irq = {"_config_com_irq", "4", true};
cvar_t	config_com_baud = {"_config_com_baud", "57600", true};
cvar_t	config_com_modem = {"_config_com_modem", "1", true};
cvar_t	config_modem_dialtype = {"_config_modem_dialtype", "T", true};
cvar_t	config_modem_clear = {"_config_modem_clear", "ATZ", true};
cvar_t	config_modem_init = {"_config_modem_init", "", true};
cvar_t	config_modem_hangup = {"_config_modem_hangup", "AT H", true};

#ifdef IDGODS
cvar_t	idgods = {"idgods", "0"};
#endif
#endif

int vcrFile = -1;
qboolean recording = false;

// these two macros are to make the code more readable
#define sfunc	net_drivers[sock->driver]
#define dfunc	net_drivers[net_driverlevel]

int net_driverlevel;

QDFLOAT net_time;

QDFLOAT SetNetTime(void)
{
    net_time = Sys_FloatTime();
    return net_time;
}

/*
 ===================
 NET_NewQSocket

 Called by drivers when a new communications endpoint is required
 The sequence and buffer fields will be filled in properly
 ===================
 */
qsocket_t* NET_NewQSocket(void)
{
    qsocket_t *sock;

    if (net_freeSockets == NULL)
        return NULL;

    if (net_activeconnections >= svs.maxclients)
        return NULL;

    // get one from free list
    sock = net_freeSockets;
    net_freeSockets = sock->next;

    // add it to active list
    sock->next = net_activeSockets;
    net_activeSockets = sock;

    sock->disconnected = false;
#if HAS_MULTIPLAYER
	sock->connecttime = net_time;
#endif
#if USING_REALLY_NETWORK
	Q_strcpy (sock->address,"UNSET ADDRESS");
#endif
    sock->driver = net_driverlevel;
    sock->socket = 0;
    sock->driverdata = NULL;
    sock->canSend = true;
    sock->sendNext = false;
#if HAS_MULTIPLAYER
	sock->lastMessageTime = net_time;
#endif
#if USING_REALLY_NETWORK
	sock->ackSequence = 0;
	sock->sendSequence = 0;
	sock->unreliableSendSequence = 0;
	sock->sendMessageLength = 0;
	sock->receiveSequence = 0;
	sock->unreliableReceiveSequence = 0;
#endif
    sock->receiveMessageLength = 0;

    return sock;
}

void NET_FreeQSocket(qsocket_t *sock)
{
    qsocket_t *s;

    // remove it from active list
    if (sock == net_activeSockets)
        net_activeSockets = net_activeSockets->next;
    else
    {
        for (s = net_activeSockets; s; s = s->next)
            if (s->next == sock)
            {
                s->next = sock->next;
                break;
            }
        if (!s)
            Sys_Error("NET_FreeQSocket: not active\n");
    }

    // add it to free list
    sock->next = net_freeSockets;
    net_freeSockets = sock;
    sock->disconnected = true;
}

void NET_Listen_f(void)
{
    if (Cmd_Argc() != 2)
    {
        Con_Printf("\"listen\" is \"%u\"\n", listening ? 1 : 0);
        return;
    }

    listening = Q_atoi(Cmd_Argv(1)) ? true : false;

    for (net_driverlevel = 0; net_driverlevel < net_numdrivers; net_driverlevel++)
    {
        if (ram_net_drivers[net_driverlevel].initialized == false)
            continue;
        dfunc.Listen (listening);
    }
}

void MaxPlayers_f(void)
{
    int n;

    if (Cmd_Argc() != 2)
    {
        Con_Printf("\"maxplayers\" is \"%u\"\n", svs.maxclients);
        return;
    }

    if (sv.active)
    {
        Con_Printf("maxplayers can not be changed while a server is running.\n");
        return;
    }

    n = Q_atoi(Cmd_Argv(1));
    if (n < 1)
        n = 1;
    if (n > svs.maxclientslimit)
    {
        n = svs.maxclientslimit;
        Con_Printf("\"maxplayers\" set to \"%u\"\n", n);
    }

    if ((n == 1) && listening)
        Cbuf_AddText("listen 0\n");

    if ((n > 1) && (!listening))
        Cbuf_AddText("listen 1\n");

    svs.maxclients = n;
    if (n == 1)
        Cvar_Set("deathmatch", "0");
    else
        Cvar_Set("deathmatch", "1");
}

void NET_Port_f(void)
{
#if HAS_MULTIPLAYER
    int     n;
    if (Cmd_Argc () != 2)
	{
		Con_Printf ("\"port\" is \"%u\"\n", net_hostport);
		return;
	}

	n = Q_atoi(Cmd_Argv(1));
	if (n < 1 || n > 65534)
	{
		Con_Printf ("Bad value, must be between 1 and 65534\n");
		return;
	}

	DEFAULTnet_hostport = n;
	net_hostport = n;

	if (listening)
	{
		// force a change to the new port
		Cbuf_AddText ("listen 0\n");
		Cbuf_AddText ("listen 1\n");
	}
#endif
}

#if HAS_MULTIPLAYER

static void PrintSlistHeader(void)
{
	Con_Printf("Server          Map             Users\n");
	Con_Printf("--------------- --------------- -----\n");
	slistLastShown = 0;
}


static void PrintSlist(void)
{
	int n;

	for (n = slistLastShown; n < hostCacheCount; n++)
	{
		if (hostcache[n].maxusers)
			Con_Printf("%-15.15s %-15.15s %2u/%2u\n", hostcache[n].name, hostcache[n].map, hostcache[n].users, hostcache[n].maxusers);
		else
			Con_Printf("%-15.15s %-15.15s\n", hostcache[n].name, hostcache[n].map);
	}
	slistLastShown = n;
}


static void PrintSlistTrailer(void)
{
	if (hostCacheCount)
		Con_Printf("== end list ==\n\n");
	else
		Con_Printf("No Quake servers found.\n\n");
}


void NET_Slist_f (void)
{
	if (slistInProgress)
		return;

	if (! slistSilent)
	{
		Con_Printf("Looking for Quake servers...\n");
		PrintSlistHeader();
	}

	slistInProgress = true;
	slistStartTime = Sys_FloatTime();

	SchedulePollProcedure(&slistSendProcedure, 0.0);
	SchedulePollProcedure(&slistPollProcedure, 0.1);

	hostCacheCount = 0;
}


static void Slist_Send(void)
{
	for (net_driverlevel=0; net_driverlevel < net_numdrivers; net_driverlevel++)
	{
		if (!slistLocal && net_driverlevel == 0)
			continue;
		if (ram_net_drivers[net_driverlevel].initialized == false)
			continue;
		dfunc.SearchForHosts (true);
	}

	if ((Sys_FloatTime() - slistStartTime) < 0.5)
		SchedulePollProcedure(&slistSendProcedure, 0.75);
}


static void Slist_Poll(void)
{
	for (net_driverlevel=0; net_driverlevel < net_numdrivers; net_driverlevel++)
	{
		if (!slistLocal && net_driverlevel == 0)
			continue;
		if (ram_net_drivers[net_driverlevel].initialized == false)
			continue;
		dfunc.SearchForHosts (false);
	}

	if (! slistSilent)
		PrintSlist();

	if ((Sys_FloatTime() - slistStartTime) < 1.5)
	{
		SchedulePollProcedure(&slistPollProcedure, 0.1);
		return;
	}

	if (! slistSilent)
		PrintSlistTrailer();
	slistInProgress = false;
	slistSilent = false;
	slistLocal = true;
}

#endif
/*
 ===================
 NET_Connect
 ===================
 */
#if HAS_MULTIPLAYER
int hostCacheCount = 0;
hostcache_t hostcache[HOSTCACHESIZE];
#endif
qsocket_t* NET_Connect(char *host)
{
    qsocket_t *ret;
    int numdrivers = net_numdrivers;

    SetNetTime();
#if HAS_MULTIPLAYER
  int       n;

	if (host && *host == 0)
		host = NULL;

	if (host)
	{
		if (Q_strcasecmp (host, "local") == 0)
		{
			numdrivers = 1;
			goto JustDoIt;
		}

		if (hostCacheCount)
		{
			for (n = 0; n < hostCacheCount; n++)
				if (Q_strcasecmp (host, hostcache[n].name) == 0)
				{
					host = hostcache[n].cname;
					break;
				}
			if (n < hostCacheCount)
				goto JustDoIt;
		}
	}

	slistSilent = host ? true : false;
	NET_Slist_f ();

	while(slistInProgress)
		NET_Poll();

	if (host == NULL)
	{
		if (hostCacheCount != 1)
			return NULL;
		host = hostcache[0].cname;
		Con_Printf("Connecting to...\n%s @ %s\n\n", hostcache[0].name, host);
	}

	if (hostCacheCount)
		for (n = 0; n < hostCacheCount; n++)
			if (Q_strcasecmp (host, hostcache[n].name) == 0)
			{
				host = hostcache[n].cname;
				break;
			}
JustDoIt:
#endif
    for (net_driverlevel = 0; net_driverlevel < numdrivers; net_driverlevel++)
    {
        if (ram_net_drivers[net_driverlevel].initialized == false)
            continue;
        ret = dfunc.Connect (host);
        if (ret)
            return ret;
    }
#if HAS_MULTIPLAYER
	if (host)
	{
		Con_Printf("\n");
		PrintSlistHeader();
		PrintSlist();
		PrintSlistTrailer();
	}
#endif
    return NULL;
}

/*
 ===================
 NET_CheckNewConnections
 ===================
 */

struct
{
    QDFLOAT time;
    int op;
    long session;
} vcrConnect;

qsocket_t* NET_CheckNewConnections(void)
{
    qsocket_t *ret;

    SetNetTime();
    //   printf("net_numdrivers %d\r\n", net_numdrivers);
    for (net_driverlevel = 0; net_driverlevel < net_numdrivers; net_driverlevel++)
    {

        if (ram_net_drivers[net_driverlevel].initialized == false)
            continue;
        if (net_driverlevel && listening == false)
            continue;
        ret = dfunc.CheckNewConnections ();
        if (ret)
        {
#if ALLOW_RECORDING
			if (recording)
			{
				vcrConnect.time = host_time;
				vcrConnect.op = VCR_OP_CONNECT;
				vcrConnect.session = (long)ret;
				Sys_FileWrite (vcrFile, &vcrConnect, sizeof(vcrConnect));
				Sys_FileWrite (vcrFile, ret->address, NET_NAMELEN);
			}
#endif
            return ret;
        }
    }
#if ALLOW_RECORDING
	if (recording)
	{
		vcrConnect.time = host_time;
		vcrConnect.op = VCR_OP_CONNECT;
		vcrConnect.session = 0;
		Sys_FileWrite (vcrFile, &vcrConnect, sizeof(vcrConnect));
	}
#endif
    return NULL;
}

/*
 ===================
 NET_Close
 ===================
 */
void NET_Close(qsocket_t *sock)
{
    if (!sock)
        return;

    if (sock->disconnected)
        return;

    SetNetTime();

    // call the driver_Close function
    sfunc.Close (sock);

    NET_FreeQSocket(sock);
}

/*
 =================
 NET_GetMessage

 If there is a complete message, return it in net_message

 returns 0 if no data is waiting
 returns 1 if a message was received
 returns -1 if connection is invalid
 =================
 */

struct
{
    QDFLOAT time;
    int op;
    long session;
    int ret;
    int len;
} vcrGetMessage;
#if MULTIPLAYER
extern void PrintStats(qsocket_t *s);
#endif
int NET_GetMessage(qsocket_t *sock)
{
    int ret;

    if (!sock)
        return -1;

    if (sock->disconnected)
    {
        Con_Printf("NET_GetMessage: disconnected socket\n");
        return -1;
    }

    SetNetTime();

    ret = sfunc.QGetMessage(sock);

    // see if this connection has timed out
    if (ret == 0 && sock->driver)
    {
#if HAS_MULTIPLAYER
		if (net_time - sock->lastMessageTime > net_messagetimeout)
		{
			NET_Close(sock);
			return -1;
		}
		#endif
    }

    if (ret > 0)
    {
        if (sock->driver)
        {
#if HAS_MULTIPLAYER
			sock->lastMessageTime = net_time;
			#endif
            if (ret == 1)
                messagesReceived++;
            else if (ret == 2)
                unreliableMessagesReceived++;
        }
#if IMPLEMENT_RECORDING
		if (recording)
		{
			vcrGetMessage.time = host_time;
			vcrGetMessage.op = VCR_OP_GETMESSAGE;
			vcrGetMessage.session = (long)sock;
			vcrGetMessage.ret = ret;
			vcrGetMessage.len = net_message.cursize;
			Sys_FileWrite (vcrFile, &vcrGetMessage, 24);
			Sys_FileWrite (vcrFile, net_message.data, net_message.cursize);
		}
#endif
    }
    else
    {
#if IMPLEMENT_RECORDING
		if (recording)
		{
			vcrGetMessage.time = host_time;
			vcrGetMessage.op = VCR_OP_GETMESSAGE;
			vcrGetMessage.session = (long)sock;
			vcrGetMessage.ret = ret;
			Sys_FileWrite (vcrFile, &vcrGetMessage, 20);
		}
#endif
    }

    return ret;
}

/*
 ==================
 NET_SendMessage

 Try to send a complete length+message unit over the reliable stream.
 returns 0 if the message cannot be delivered reliably, but the connection
 is still considered valid
 returns 1 if the message was sent properly
 returns -1 if the connection died
 ==================
 */
struct
{
    QDFLOAT time;
    int op;
    long session;
    int r;
} vcrSendMessage;

int NET_SendMessage(qsocket_t *sock, sizebuf_t *data)
{
    int r;

    if (!sock)
        return -1;

    if (sock->disconnected)
    {
        Con_Printf("NET_SendMessage: disconnected socket\n");
        return -1;
    }

    SetNetTime();
    r = sfunc.QSendMessage(sock, data);
    if (r == 1 && sock->driver)
        messagesSent++;
#if IMPLEMENT_RECORDING
	if (recording)
	{
		vcrSendMessage.time = host_time;
		vcrSendMessage.op = VCR_OP_SENDMESSAGE;
		vcrSendMessage.session = (long)sock;
		vcrSendMessage.r = r;
		Sys_FileWrite (vcrFile, &vcrSendMessage, 20);
	}
#endif
    return r;
}

int NET_SendUnreliableMessage(qsocket_t *sock, sizebuf_t *data)
{
    int r;

    if (!sock)
        return -1;

    if (sock->disconnected)
    {
        Con_Printf("NET_SendMessage: disconnected socket\n");
        return -1;
    }

    SetNetTime();
    r = sfunc.SendUnreliableMessage(sock, data);
    if (r == 1 && sock->driver)
        unreliableMessagesSent++;

#if IMPLEMENT_RECORDING
	if (recording)
	{
		vcrSendMessage.time = host_time;
		vcrSendMessage.op = VCR_OP_SENDMESSAGE;
		vcrSendMessage.session = (long)sock;
		vcrSendMessage.r = r;
		Sys_FileWrite (vcrFile, &vcrSendMessage, 20);
	}
#endif
    return r;
}

/*
 ==================
 NET_CanSendMessage

 Returns true or false if the given qsocket can currently accept a
 message to be transmitted.
 ==================
 */
AUX_SECTION qsocket_t qsockets[MAX_CLIENTS + 1];
qboolean NET_CanSendMessage(qsocket_t *sock)
{
    int r;

    if (!sock)
        return false;

    if (sock->disconnected)
        return false;

    SetNetTime();

    r = sfunc.CanSendMessage(sock);
#if IMPLEMENT_RECORDING
    if (recording)
    {
        vcrSendMessage.time = host_time;
        vcrSendMessage.op = VCR_OP_CANSENDMESSAGE;
        vcrSendMessage.session = (long)sock;
        vcrSendMessage.r = r;
        Sys_FileWrite (vcrFile, &vcrSendMessage, 20);
    }
#endif
    return r;
}

int NET_SendToAll(sizebuf_t *data, int blocktime)
{

    QDFLOAT start;
    int i;
    int count = 0;
    qboolean state1[MAX_SCOREBOARD];
    qboolean state2[MAX_SCOREBOARD];

    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
    {
        if (!host_client->netconnection)
            continue;
        if (host_client->active)
        {
            if (host_client->netconnection->driver == 0)
            {
                NET_SendMessage(host_client->netconnection, data);
                state1[i] = true;
                state2[i] = true;
                continue;
            }
            count++;
            state1[i] = false;
            state2[i] = false;
        }
        else
        {
            state1[i] = true;
            state2[i] = true;
        }
    }

    start = Sys_FloatTime();
    while (count)
    {
        count = 0;
        for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
        {
            if (!state1[i])
            {
                if (NET_CanSendMessage(host_client->netconnection))
                {
                    state1[i] = true;
                    NET_SendMessage(host_client->netconnection, data);
                }
                else
                {
                    NET_GetMessage(host_client->netconnection);
                }
                count++;
                continue;
            }

            if (!state2[i])
            {
                if (NET_CanSendMessage(host_client->netconnection))
                {
                    state2[i] = true;
                }
                else
                {
                    NET_GetMessage(host_client->netconnection);
                }
                count++;
                continue;
            }
        }
        if ((Sys_FloatTime() - start) > blocktime)
            break;
    }
    return count;
}

//=============================================================================

/*
 ====================
 NET_Init
 ====================
 */

void NET_Init(void)
{
    int i;
    int controlSocket;
    qsocket_t *s;

#if WIN32
	if (COM_CheckParm("-playback"))
	{
//		net_numdrivers = 1;
//		net_drivers[0].Init = VCR_Init;
	}

	if (COM_CheckParm("-record"))
		recording = true;
	    #if HAS_MULTIPLAYER
	i = COM_CheckParm ("-port");
	if (!i)
		i = COM_CheckParm ("-udpport");
	if (!i)
		i = COM_CheckParm ("-ipxport");

	if (i)
	{
		if (i < com_argc-1)
			DEFAULTnet_hostport = Q_atoi (com_argv[i+1]);
		else
			Sys_Error ("NET_Init: you must specify a number after -port");
	}
	net_hostport = DEFAULTnet_hostport;

	if (COM_CheckParm("-listen") || cls.state == ca_dedicated)
		listening = true;
    #endif
#endif
#if HAS_MULTIPLAYER
	net_numsockets = svs.maxclientslimit;
	if (cls.state != ca_dedicated)
		net_numsockets++;
#endif
    SetNetTime();
#define MAX_CLIENT_MESSAGE_LENGTH  NET_MAXMESSAGE
    for (i = 0; i < net_numsockets; i++)
    {
        s = (qsocket_t*) &qsockets[i]; //Hunk_AllocName(sizeof(qsocket_t), "qsocket");
        s->maxMessageLength = i == 0 ? NET_MAXMESSAGE : MAX_CLIENT_MESSAGE_LENGTH;
#if !USING_REALLY_NETWORK
        byte *buffer = allocFromTempBuffer(s->maxMessageLength, NULL);

        s->receiveMessage = buffer;
#endif // USING_REALLY_NETWORK
        s->next = net_freeSockets;
        net_freeSockets = s;
        s->disconnected = true;
    }

    // allocate space for network message buffer
#if NET_MESSAGE_SZ_ALLOC
	ERRORSZ_Alloc (&net_message, NET_MAXMESSAGE);
#else
    int maxsize = 0;
    net_message.data = allocFromTempBuffer(NET_MAXMESSAGE, &maxsize);
    net_message.maxsize = maxsize;
#endif
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&net_messagetimeout);
	Cvar_RegisterVariable (&hostname);
	Cvar_RegisterVariable (&config_com_port);
	Cvar_RegisterVariable (&config_com_irq);
	Cvar_RegisterVariable (&config_com_baud);
	Cvar_RegisterVariable (&config_com_modem);
	Cvar_RegisterVariable (&config_modem_dialtype);
	Cvar_RegisterVariable (&config_modem_clear);
	Cvar_RegisterVariable (&config_modem_init);
	Cvar_RegisterVariable (&config_modem_hangup);
#ifdef IDGODS
	Cvar_RegisterVariable (&idgods);
#endif
#endif

    // initialize all the drivers
    for (net_driverlevel = 0; net_driverlevel < net_numdrivers; net_driverlevel++)
    {
        controlSocket = net_drivers[net_driverlevel].Init();
        if (controlSocket == -1)
            continue;
        ram_net_drivers[net_driverlevel].initialized = true;
        ram_net_drivers[net_driverlevel].controlSock = controlSocket;
        if (listening)
            net_drivers[net_driverlevel].Listen(true);
    }
#if HAS_MULTIPLAYER
	if (*my_ipx_address)
		Con_DPrintf("IPX address %s\n", my_ipx_address);
	if (*my_tcpip_address)
		Con_DPrintf("TCP/IP address %s\n", my_tcpip_address);
#endif
}

/*
 ====================
 NET_Shutdown
 ====================
 */

void NET_Shutdown(void)
{
    qsocket_t *sock;

    SetNetTime();

    for (sock = net_activeSockets; sock; sock = sock->next)
        NET_Close(sock);

//
// shutdown the drivers
//
    for (net_driverlevel = 0; net_driverlevel < net_numdrivers; net_driverlevel++)
    {
        if (ram_net_drivers[net_driverlevel].initialized == true)
        {
            net_drivers[net_driverlevel].Shutdown();
            ram_net_drivers[net_driverlevel].initialized = false;
        }
    }

    if (vcrFile != -1)
    {
        Con_Printf("Closing vcrfile.\n");
        Sys_FileClose(vcrFile);
    }
}

static PollProcedure *pollProcedureList = NULL;

void NET_Poll(void)
{
    PollProcedure *pp;
#if HAS_SERIAL
	static qboolean configRestored;
	qboolean	useModem;

	if (!configRestored)
	{
		if (serialAvailable)
		{
			if (config_com_modem == 1.0)
				useModem = true;
			else
				useModem = false;
			SetComPortConfig (0, (int)config_com_port, (int)config_com_irq, (int)config_com_baud, useModem);
			SetModemConfig (0, config_modem_dialtype.string, config_modem_clear.string, config_modem_init.string, config_modem_hangup.string);
		}
		configRestored = true;
	}
#endif

    SetNetTime();

    for (pp = pollProcedureList; pp; pp = pp->next)
    {
        if (pp->nextTime > net_time)
            break;
        pollProcedureList = pp->next;
        pp->procedure(pp->arg);
    }
}

void SchedulePollProcedure(PollProcedure *proc, QDFLOAT timeOffset)
{
    PollProcedure *pp, *prev;

    proc->nextTime = Sys_FloatTime() + timeOffset;
    for (pp = pollProcedureList, prev = NULL; pp; pp = pp->next)
    {
        if (pp->nextTime >= proc->nextTime)
            break;
        prev = pp;
    }

    if (prev == NULL)
    {
        proc->next = pollProcedureList;
        pollProcedureList = proc;
        return;
    }

    proc->next = pp;
    prev->next = proc;
}

#ifdef IDGODS
#define IDNET	0xc0f62800

qboolean IsID(struct qsockaddr *addr)
{
	if (idgods == 0.0)
		return false;

	if (addr->sa_family != 2)
		return false;

	if ((BigLong(*(int *)&addr->sa_data[2]) & 0xffffff00) == IDNET)
		return true;
	return false;
}
#endif
