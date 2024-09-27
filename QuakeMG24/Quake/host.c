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
// host.c -- coordinates spawning and killing of local servers
#include "quakedef.h"
#include "r_local.h"
#if WIN32
#include "extMemoryWin32.h"
#else
#include "extMemory.h"
#include "delay.h"
#endif
#if WIN32
int gcn = 0;    // counter for get childnode
int gpn = 0;    // counter for get parent node.
int gem = 0;    // counter for get entity model
#endif // WIN32
/*

 A server can allways be started, even if the system started out as a client
 to a remote system.

 A client can NOT be started if the system started as a dedicated server.

 Memory is cleared / released when a server or client begins, not when they end.

 */

const quakeparms_t host_parms;

qboolean host_initialized;		// true if into command execution

QDFLOAT host_frametime;
QDFLOAT host_time;
QDFLOAT realtime;				// without any filtering or bounding
QDFLOAT oldrealtime;			// last frame run
int host_framecount;

//int			minimum_memory;

client_t *host_client;			// current client

#if HOST_ABORT_SERVER
jmp_buf 	host_abortserver;
#endif
byte *host_basepal;
byte *host_colormap;

#if USE_ORIGINAL_CVAR
cvar_t	host_framerate = {"host_framerate","0"};	// set for slow motion
cvar_t	host_speeds = {"host_speeds","0"};			// set for running times

cvar_t	sys_ticrate = {"sys_ticrate","0.05"};
cvar_t	serverprofile = {"serverprofile","0"};

cvar_t	fraglimit = {"fraglimit","0",false,true};
cvar_t	timelimit = {"timelimit","0",false,true};
cvar_t	teamplay = {"teamplay","0",false,true};

cvar_t	samelevel = {"samelevel","0"};
cvar_t	noexit = {"noexit","0",false,true};

#ifdef QUAKE2
cvar_t	developer = {"developer","1"};	// should be 0 for release!
#else
cvar_t	developer = {"developer","0"};
#endif

cvar_t	skill = {"skill","1"};						// 0 - 3
cvar_t	deathmatch = {"deathmatch","0"};			// 0, 1, or 2
cvar_t	coop = {"coop","0"};			// 0 or 1

cvar_t	pausable = {"pausable","1"};

cvar_t	temp1 = {"temp1","0"};
#endif

/*
 ================
 Host_EndGame
 ================
 */
void Host_EndGame(char *message, ...)
{
    va_list argptr;
#if USE_MORE_STACK
	char		string[1024];
#else
    tempStringStack -= 1024;
    char *string = tempStringStack;
#endif
    va_start(argptr, message);
    vsprintf(string, message, argptr);
    va_end(argptr);
    Con_DPrintf("Host_EndGame: %s\n", string);

    if (sv.active)
        Host_ShutdownServer(false);

    if (_g->cls.state == ca_dedicated)
        Sys_Error("Host_EndGame: %s\n", string);	// dedicated servers exit

    if (_g->cls.demonum != -1)
        CL_NextDemo();
    else
        CL_Disconnect();
#if HOST_ABORT_SERVER
	longjmp (host_abortserver, 1);
#endif
}

/*
 ================
 Host_Error

 This shuts down both the client and server
 ================
 */
void Host_Error(char *error, ...)
{
    va_list argptr;
    char string[1024];
    static qboolean inerror = false;

    if (inerror)
        Sys_Error("Host_Error: recursively entered");
    inerror = true;

    SCR_EndLoadingPlaque();		// reenable screen updates

    va_start(argptr, error);
    vsprintf(string, error, argptr);
    va_end(argptr);
    Con_Printf("Host_Error: %s\n", string);

    if (sv.active)
        Host_ShutdownServer(false);

    if (_g->cls.state == ca_dedicated)
        Sys_Error("Host_Error: %s\n", string);	// dedicated servers exit

    CL_Disconnect();
    _g->cls.demonum = -1;

    inerror = false;
#if HOST_ABORT_SERVER
	longjmp (host_abortserver, 1);
#endif
}

/*
 ================
 Host_FindMaxClients
 ================
 */
void Host_FindMaxClients(void)
{

    svs.maxclients = MAX_CLIENTS;
#if WIN32
  int   i;

	i = COM_CheckParm ("-dedicated");
	if (i)
	{
		_g->cls.state = ca_dedicated;
		if (i != (com_argc - 1))
		{
			svs.maxclients = Q_atoi (com_argv[i+1]);
		}
		else
			svs.maxclients = 8;
	}
	else
		_g->cls.state = ca_disconnected;
	i = COM_CheckParm ("-listen");
	if (i)
	{
		if (_g->cls.state == ca_dedicated)
			Sys_Error ("Only one of -dedicated or -listen can be specified");
		if (i != (com_argc - 1))
			svs.maxclients = Q_atoi (com_argv[i+1]);
		else
			svs.maxclients = 8;
	}
  if (svs.maxclients < 1)
    svs.maxclients = 8;
  else if (svs.maxclients > MAX_SCOREBOARD)
    svs.maxclients = MAX_SCOREBOARD;

#else
    _g->cls.state = ca_disconnected;
#endif

    svs.maxclientslimit = MAX_CLIENTS;
    memset(svs.clients, 0, svs.maxclientslimit * sizeof(client_t));
    if (svs.maxclients > 1)
        Cvar_SetValue("deathmatch", 1.0);
    else
        Cvar_SetValue("deathmatch", 0.0);
}

/*
 =======================
 Host_InitLocal
 ======================
 */
void Host_InitLocal(void)
{
    Host_InitCommands();
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&host_framerate);
	Cvar_RegisterVariable (&host_speeds);

	Cvar_RegisterVariable (&sys_ticrate);
	Cvar_RegisterVariable (&serverprofile);

	Cvar_RegisterVariable (&fraglimit);
	Cvar_RegisterVariable (&timelimit);
	Cvar_RegisterVariable (&teamplay);
	Cvar_RegisterVariable (&samelevel);
	Cvar_RegisterVariable (&noexit);
	Cvar_RegisterVariable (&skill);
	Cvar_RegisterVariable (&developer);
	Cvar_RegisterVariable (&deathmatch);
	Cvar_RegisterVariable (&coop);

	Cvar_RegisterVariable (&pausable);

	Cvar_RegisterVariable (&temp1);
#endif
    Host_FindMaxClients();

    host_time = 1.0;		// so a think at time 0 won't get called
}

/*
 ===============
 Host_WriteConfiguration

 Writes key bindings and archived cvars to config.cfg
 ===============
 */
void Host_WriteConfiguration(void)
{
#if WIN32
  FILE  *f;
  FIXME("WRITE CONF");
	#endif // WIN32
#if 0
// dedicated servers initialize the host but don't parse and set the
// config.cfg cvars
	if (host_initialized & !isDedicated)
	{
		f = fopen (va("%s\\config.cfg",com_gamedir), "w");
		if (!f)
		{
			Con_Printf ("Couldn't write config.cfg.\n");
			return;
		}

		Key_WriteBindings (f);
		Cvar_WriteVariables (f);

		fclose (f);
	}
#else
    nvmData_t *nvm = (nvmData_t*) ((byte*) extMemGetSize() - sizeof(nvmData_t));
    extMemErase((uint32_t) &nvm->settings, sizeof(nvm->settings));
    // todo: check length. But for sure we are not going to have like a huge file
    byte *pos = (byte*) &nvm->settings.settingsText;
    //
    Key_WriteBindings(&pos);
    Cvar_WriteVariables(&pos);
    // add nullpointer
    int zeroptr = 0;
    extMemProgram((uint32_t) pos, (uint8_t*) &zeroptr, sizeof(zeroptr));
    pos += 4;
    // write cookie and length.
    int len = pos - (byte*) &nvm->settings.settingsText;
    extMemProgram((uint32_t) &nvm->settings.s.len, (uint8_t*) &len, sizeof(nvm->settings.s.len));
    int cookie = SETTINGS_COOKIE;
    extMemProgram((uint32_t) &nvm->settings.s.cookie, (uint8_t*) &cookie, sizeof(nvm->settings.s.cookie));
#endif
}

/*
 =================
 SV_ClientPrintf

 Sends text across to be displayed
 FIXME: make this just a stuffed echo?
 =================
 */
void SV_ClientPrintf(char *fmt, ...)
{
    //   printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");
    va_list argptr;
    char string[1024];

    va_start(argptr, fmt);
    vsprintf(string, fmt, argptr);
    va_end(argptr);

    MSG_WriteByte(&host_client->message, svc_print);
    MSG_WriteString(&host_client->message, string);
}

/*
 =================
 SV_BroadcastPrintf

 Sends text to all active clients
 =================
 */
void SV_BroadcastPrintf(char *fmt, ...)
{
    //      printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    va_list argptr;
    char string[1024];
    int i;

    va_start(argptr, fmt);
    vsprintf(string, fmt, argptr);
    va_end(argptr);

    for (i = 0; i < svs.maxclients; i++)
        if (svs.clients[i].active && svs.clients[i].spawned)
        {
            MSG_WriteByte(&svs.clients[i].message, svc_print);
            MSG_WriteString(&svs.clients[i].message, string);
        }

}

/*
 =================
 Host_ClientCommands

 Send text over to the client to be executed
 =================
 */
void Host_ClientCommands(char *fmt, ...)
{
    va_list argptr;
    char string[1024];

    va_start(argptr, fmt);
    vsprintf(string, fmt, argptr);
    va_end(argptr);

    MSG_WriteByte(&host_client->message, svc_stufftext);
    MSG_WriteString(&host_client->message, string);
}

/*
 =====================
 SV_DropClient

 Called when the player is getting totally kicked off the host
 if (crash = true), don't bother sending signofs
 =====================
 */
void SV_DropClient(qboolean crash)
{
    int saveSelf;
    int i;
    client_t *client;
    if (!crash)
    {
        // send any final messages (don't check for errors)
        if (NET_CanSendMessage(host_client->netconnection))
        {
            MSG_WriteByte(&host_client->message, svc_disconnect);
            NET_SendMessage(host_client->netconnection, &host_client->message);
        }

        if (host_client->edict && host_client->spawned)
        {
            // call the prog function for removing a client
            // this will set the body to a dead frame, among other things
#if USE_PROGSDAT
			saveSelf = pr_global_struct->self;
			pr_global_struct->self = EDICT_TO_PROG(host_client->edict);
			PR_ExecuteProgram (pr_global_struct->ClientDisconnect);
			pr_global_struct->self = saveSelf;
        #else
            saveSelf = progs.qcc_self;
            progs.qcc_self = EDICT_TO_PROG(host_client->edict);
            //PR_ExecuteProgram (pr_global_struct->ClientDisconnect);
            qcc_ClientDisconnect();
            progs.qcc_self = saveSelf;
#endif
        }

        Sys_Printf("Client %s removed\n", host_client->name);
    }

// break the net connection
    NET_Close(host_client->netconnection);
    host_client->netconnection = NULL;

// free the client (the body stays around)
    host_client->active = false;
    host_client->name[0] = 0;
    host_client->old_frags = -999999;
    net_activeconnections--;

// send notification to all clients
    for (i = 0, client = svs.clients; i < svs.maxclients; i++, client++)
    {
        if (!client->active)
            continue;
        MSG_WriteByte(&client->message, svc_updatename);
        MSG_WriteByte(&client->message, host_client - svs.clients);
        MSG_WriteString(&client->message, "");
        MSG_WriteByte(&client->message, svc_updatefrags);
        MSG_WriteByte(&client->message, host_client - svs.clients);
        MSG_WriteShort(&client->message, 0);
        MSG_WriteByte(&client->message, svc_updatecolors);
        MSG_WriteByte(&client->message, host_client - svs.clients);
        MSG_WriteByte(&client->message, 0);
    }
}

/*
 ==================
 Host_ShutdownServer

 This only happens at the end of a game, not between levels
 ==================
 */
void Host_ShutdownServer(qboolean crash)
{
    int i;
    int count;
    sizebuf_t buf;
    char message[4];
    QDFLOAT start;

    if (!sv.active)
        return;

    sv.active = false;

// stop all client sounds immediately
    if (_g->cls.state == ca_connected)
        CL_Disconnect();

// flush any pending messages - like the score!!!
    start = Sys_FloatTime();
    do
    {
        count = 0;
        for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
        {
            if (host_client->active && host_client->message.cursize)
            {
                if (NET_CanSendMessage(host_client->netconnection))
                {
                    NET_SendMessage(host_client->netconnection, &host_client->message);
                    SZ_Clear(&host_client->message);
                }
                else
                {
                    NET_GetMessage(host_client->netconnection);
                    count++;
                }
            }
        }
        if ((Sys_FloatTime() - start) > 3.0)
            break;
    }
    while (count);

// make sure all the clients know we're disconnecting
    buf.data = (uint8_t*) message;
    buf.maxsize = 4;
    buf.cursize = 0;
    MSG_WriteByte(&buf, svc_disconnect);
    count = NET_SendToAll(&buf, 5);
    if (count)
        Con_Printf("Host_ShutdownServer: NET_SendToAll failed for %u clients\n", count);

    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
        if (host_client->active)
            SV_DropClient(crash);

//
// clear structures
//
    memset(&sv, 0, sizeof(sv));
    memset(svs.clients, 0, svs.maxclientslimit * sizeof(client_t));

}

/*
 ================
 Host_ClearMemory

 This clears all the memory used by both the client and server, but does
 not reinitialize anything.
 ================
 */
//extern int qcc_newmis;
//extern int qcc_activator;
//extern int qcc_damage_attacker;
//extern int qcc_trace_ent;
//extern int qcc_sight_entity;
//extern int qcc_msg_entity;
void Host_ClearMemory(void)
{
    Con_DPrintf("Clearing memory\n");
#if SURF_CACHE
	D_FlushCaches ();
#endif
    Mod_ClearAll();

    _g->cls.signon = 0;
    memset(&sv, 0, sizeof(sv));
    memset(&_g->cl, 0, sizeof(_g->cl));
    //
#if 0
 progs.qcc_newmis = 0;
 progs.qcc_activator = 0;
 progs.qcc_damage_attacker = 0;
 progs.qcc_trace_ent = 0;
 progs.qcc_sight_entity = 0;
 progs.qcc_msg_entity = 0;
 #else
    memset(&progs, 0, sizeof(progs));
#endif
}

//============================================================================

/*
 ===================
 Host_FilterTime

 Returns false if the time is too short to run a frame
 ===================
 */
qboolean Host_FilterTime(float time)
{
    realtime += time;

    if (!_g->cls.timedemo && realtime - oldrealtime < 1.0 / 72.0)
        return false;		// framerate is too high

    host_frametime = realtime - oldrealtime;
    oldrealtime = realtime;

    if (host_framerate > 0)
        host_frametime = host_framerate;
    else
    {	// don't allow really long or short frames
        if (host_frametime > 0.1)
            host_frametime = 0.1;
        if (host_frametime < 0.001)
            host_frametime = 0.001;
    }

    return true;
}

/*
 ===================
 Host_GetConsoleCommands

 Add them exactly as if they had been typed at the console
 ===================
 */
void Host_GetConsoleCommands(void)
{
    char *cmd;

    while (1)
    {
        cmd = Sys_ConsoleInput();
        if (!cmd)
            break;
        Cbuf_AddText(cmd);
    }
}

/*
 ==================
 Host_ServerFrame

 ==================
 */
#ifdef FPS_20

void _Host_ServerFrame (void)
{
// run the world state
	pr_global_struct->frametime = host_frametime;

// read client messages
	SV_RunClients ();

// move things around and think
// always pause in single player if in console or menus
	if (!sv.paused && (svs.maxclients > 1 || key_dest == key_game) )
		SV_Physics ();
}

void Host_ServerFrame (void)
{
	float	save_host_frametime;
	float	temp_host_frametime;

// run the world state
	pr_global_struct->frametime = host_frametime;

// set the time and clear the general datagram
	SV_ClearDatagram ();

// check for new clients
	SV_CheckForNewClients ();

	temp_host_frametime = save_host_frametime = host_frametime;
	while(temp_host_frametime > (1.0/72.0))
	{
		if (temp_host_frametime > 0.05)
			host_frametime = 0.05;
		else
			host_frametime = temp_host_frametime;
		temp_host_frametime -= host_frametime;
		_Host_ServerFrame ();
	}
	host_frametime = save_host_frametime;

// send all messages to the clients
	SV_SendClientMessages ();
}

#else

void Host_ServerFrame(void)
{
// run the world state
#if USE_PROGSDAT
	pr_global_struct->frametime = host_frametime;
#else
    progs.qcc_frametime = host_frametime;
#endif
// set the time and clear the general datagram
    SV_ClearDatagram();

// check for new clients
    SV_CheckForNewClients();

// read client messages
    SV_RunClients();

// move things around and think
// always pause in single player if in console or menus
    if (!sv.paused && (svs.maxclients > 1 || key_dest == key_game))
        SV_Physics();

// send all messages to the clients
    SV_SendClientMessages();
}

#endif

/*
 ==================
 Host_Frame

 Runs all active servers
 ==================
 */
#if WIN32
int screenUpdated = 0;
extern sizebuf_t cmd_text;
#endif // WIN32
char *tempStringStack = (char*) (d_zbuffer + SCREEN_WIDTH * DRAW_BUFFER_HEIGHT) - SCREEN_WIDTH * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT);
void _Host_Frame(float time)
{
#if WIN32
    static float time1 = 0;
    static float time2 = 0;
    static float time3 = 0;
#endif
    tempStringStack = (char*) (d_zbuffer + SCREEN_WIDTH * DRAW_BUFFER_HEIGHT) - SCREEN_WIDTH * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT);
#if !WIN32
    static unsigned int lastTime;
#endif
#if WIN32
    int pass1, pass2, pass3;
#endif
    if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
        while (1)
            FIXME("RECEIVE MESSAGELENGTH NOT 0");

#if HOST_ABORT_SERVER
	if (setjmp (host_abortserver) )
		return;			// something bad happened, or the server disconnected
#endif
// keep the random time dependent
    rand();

// decide the simulation time
    if (!Host_FilterTime(time))
        return;			// don't run too fast, or packets will flood out
//	if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
//	    while(1) FIXME("RECEIVE MESSAGELENGTH NOT 0");

// get new key events
    Sys_SendKeyEvents();

//	if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
//	    while(1) FIXME("RECEIVE MESSAGELENGTH NOT 0");

// allow mice or other external controllers to add commands
    IN_Commands();

//	if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
//	    while(1) FIXME("RECEIVE MESSAGELENGTH NOT 0");

// process console commands
    Cbuf_Execute();

    NET_Poll();

//	if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
//	    while(1) FIXME("RECEIVE MESSAGELENGTH NOT 0");

// if running the server locally, make intentions now
    if (sv.active)
        CL_SendCmd();

//	if (_g->cls.netcon && _g->cls.netcon->receiveMessageLength)
//	    while(1) FIXME("RECEIVE MESSAGELENGTH NOT 0");

//-------------------
//
// server operations
//
//-------------------

// check for commands typed to the host
    Host_GetConsoleCommands();

    if (sv.active)
        Host_ServerFrame();

//-------------------
//
// client operations
//
//-------------------

// if running the server remotely, send intentions now after
// the incoming messages have been read
    if (!sv.active)
        CL_SendCmd();

    host_time += host_frametime;

// fetch results from server
    if (_g->cls.state == ca_connected)
    {
#if WIN32
	    if (screenUpdated)
	        FIXME("Screen updated before!");
        #endif
        CL_ReadFromServer();
    }

// update video
#if WIN32
    if (host_speeds)
        time1 = Sys_FloatTime();
#endif
    SCR_UpdateScreen();

#if WIN32
    screenUpdated = 0;
#endif // WIN32
#if DIRECT_SINGLE_PLAYER
// clear muzzle flashes
    SV_CleanupEnts(); // cleared after, because with DIRECT_SINGLE_PLAYER we read directly
#endif
#if WIN32
    if (host_speeds)
        time2 = Sys_FloatTime();
#endif
// update audio
    if (_g->cls.signon == SIGNONS)
    {
        S_Update(_g->r_origin, _g->vpn, _g->vright, _g->vup);
        CL_DecayLights();
    }
    else
        S_Update(vec3_origin, vec3_origin, vec3_origin, vec3_origin);

    CDAudio_Update();
#if WIN32
    if (host_speeds)
    {
        pass1 = (time1 - time3) * 1000;
        time3 = Sys_FloatTime();
        pass2 = (time2 - time1) * 1000;
        pass3 = (time3 - time2) * 1000;
        Con_Printf("%3i tot %3i server %3i gfx %3i snd\n", pass1 + pass2 + pass3, pass1, pass2, pass3);
    }
#endif
    host_framecount++;
#if !WIN32
    // calculate how much time we took coming here
    uint32_t timeTaken = lastTime;
    lastTime = I_GetTimeMicrosecs();
    timeTaken = lastTime - timeTaken;
    if (timeTaken)
    {
        // calculate the frame rate * 10 and approximate at the closest integer
        _g->fps10 = (10000000.0f / timeTaken) + 0.5f;
    }
#define PRITNTIMES 1
#if PRITNTIMES
    printf("%u\r", (unsigned int) timeTaken);
#endif
    //  if (host_framecount == 83)
//    __ASM("BKPT\n\t");
#endif
}

void Host_Frame(float time)
{
#if 0
    float time1, time2;
    static float timetotal;
    static int timecount;
    int i, c, m;

    if (!serverprofile)
    {
        _Host_Frame(time);
        return;
    }

    time1 = Sys_FloatTime();
    _Host_Frame(time);
    time2 = Sys_FloatTime();

    timetotal += time2 - time1;
    timecount++;

    if (timecount < 1000)
        return;

    m = timetotal * 1000 / timecount;
    timecount = 0;
    timetotal = 0;
    c = 0;
    for (i = 0; i < svs.maxclients; i++)
    {
        if (svs.clients[i].active)
            c++;
    }

    Con_Printf("serverprofile: %2i clients %2i msec\n", c, m);
#else
    _Host_Frame(time);
#endif
}

//============================================================================

#define	VCR_SIGNATURE	0x56435231
// "VCR1"

void Host_InitVCR(quakeparms_t *parms)
{
    (void) parms;
#if IMPLEMENT_EXTERNAL_DEMO
  int		i, len, n;
  char  *p;
	if (COM_CheckParm("-playback"))
	{
	    printf("playback\r\n");
		if (com_argc != 2)
			Sys_Error("No other parameters allowed with -playback\n");

		Sys_FileOpenRead("quake.vcr", &vcrFile);
		if (vcrFile == -1)
			Sys_Error("playback file not found\n");

		Sys_FileRead (vcrFile, &i, sizeof(int));
		if (i != VCR_SIGNATURE)
			Sys_Error("Invalid signature in vcr file\n");

		Sys_FileRead (vcrFile, &com_argc, sizeof(int));
		com_argv = malloc(com_argc * sizeof(char *));
		com_argv[0] = parms->argv[0];
		for (i = 0; i < com_argc; i++)
		{
			Sys_FileRead (vcrFile, &len, sizeof(int));
			p = malloc(len);
			Sys_FileRead (vcrFile, p, len);
			com_argv[i+1] = p;
		}
		com_argc++; /* add one for arg[0] */
		parms->argc = com_argc;
		parms->argv = com_argv;
	}
#endif

#if IMPLEMENT_RECORDING

	if ( (n = COM_CheckParm("-record")) != 0)
	{
		vcrFile = Sys_FileOpenWrite("quake.vcr");

		i = VCR_SIGNATURE;
		Sys_FileWrite(vcrFile, &i, sizeof(int));
		i = com_argc - 1;
		Sys_FileWrite(vcrFile, &i, sizeof(int));
		for (i = 1; i < com_argc; i++)
		{
			if (i == n)
			{
				len = 10;
				Sys_FileWrite(vcrFile, &len, sizeof(int));
				Sys_FileWrite(vcrFile, "-playback", len);
				continue;
			}
			len = Q_strlen(com_argv[i]) + 1;
			Sys_FileWrite(vcrFile, &len, sizeof(int));
			Sys_FileWrite(vcrFile, com_argv[i], len);
		}
	}
#endif

}

/*
 ====================
 Host_Init
 ====================
 */
void Host_Init(quakeparms_t *parms)
{
    com_argc = 0;
    com_argv = NULL;
    internalFlashInit();
    Cbuf_Init();
    Cmd_Init();
    V_Init();
    Chase_Init();
    Host_InitVCR(parms);
    if (parms)
        COM_Init(parms->basedir);
    else
        COM_Init(NULL);
    Host_InitLocal();
    W_LoadWadFile("gfx.wad");
    Key_Init();
    Con_Init();
    M_Init();
    PR_Init();
    Mod_Init();
    NET_Init();
    SV_Init();

    Con_Printf("Exe: "__TIME__" "__DATE__"\n");
    Con_Printf("%d bytes zone memory\n", MAX_STATIC_ZONE);
    R_InitTextures();		// needed even for dedicated servers
    printf("R Init_Textures\r\n");
    if (_g->cls.state != ca_dedicated)
    {
#if !USE_EXT_MEMORY
		host_basepal = (byte *)COM_LoadHunkFile ("gfx/palette.lmp");
#else
        host_basepal = (byte*) COM_LoadFileFromExtMem("gfx/palette.lmp", NULL);
#endif
        if (!host_basepal)
            Sys_Error("Couldn't load gfx/palette.lmp");
#if !USE_EXT_MEMORY
		host_colormap = (byte *)COM_LoadHunkFile ("gfx/colormap.lmp");
#else
        unsigned int colormapsize;
        host_colormap = (byte*) COM_LoadFileFromExtMem("gfx/colormap.lmp", &colormapsize);
        host_colormap = storeToInternalFlash(host_colormap, (colormapsize + 3) & ~3);
#endif
        if (!host_colormap)
            Sys_Error("Couldn't load gfx/colormap.lmp");

#ifndef _WIN32_NO_SDL // on non win32, mouse comes before video for security reasons
        printf("In Init\r\n");
        IN_Init();
#endif
        printf("Before Vid_init\r\n");
        VID_Init(host_basepal);
        printf("Vid Init\r\n");
        Draw_Init();       // will store chars in internal memory
        SCR_Init();
        R_Init();
        printf("R init");
        Sbar_Init();
        S_Init();         // will store sound data to internal memory
        internalFlashSetCommonZone();
        CDAudio_Init();
        CL_Init();
#ifdef _WIN32 // on non win32, mouse comes before video for security reasons
		IN_Init ();
#endif
    }

    Cbuf_InsertText("exec quake.rc\n");

    host_initialized = true;

    Sys_Printf("========Quake Initialized=========\n");
}

/*
 ===============
 Host_Shutdown

 FIXME: this is a callback from Sys_Quit and Sys_Error.  It would be better
 to run quit through here before the final handoff to the sys code.
 ===============
 */
void Host_Shutdown(void)
{
    static qboolean isdown = false;

    if (isdown)
    {
        printf("recursive shutdown\n");
        return;
    }
    isdown = true;

// keep Con_Printf from trying to update the screen
    scr_disabled_for_loading = true;

    Host_WriteConfiguration();

    CDAudio_Shutdown();
    NET_Shutdown();
    S_Shutdown();
    IN_Shutdown();

    if (_g->cls.state != ca_dedicated)
    {
        VID_Shutdown();
    }
}
#if !WIN32
#include "printf.h"
void Sys_Printf(char *fmt, ...)
{
    va_list argptr;
    va_start(argptr, fmt);
    sharedUsartVPrintf(fmt, argptr);
    va_end(argptr);
}
#endif
