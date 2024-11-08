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
// net_loop.c
#include "quakedef.h"
#include "net_loop.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
qboolean localconnectpending = false;
qsocket_t *loop_client = NULL;
qsocket_t *loop_server = NULL;

int Loop_Init(void)
{
    if (_g->cls.state == ca_dedicated)
        return -1;
    return 0;
}

void Loop_Shutdown(void)
{
}

void Loop_Listen(qboolean state)
{
    (void) state;
}

void Loop_SearchForHosts(qboolean xmit)
{
    (void) xmit;
    if (!sv.active)
        return;
#if HAS_MULTIPLAYER
	hostCacheCount = 1;
	if (Q_strcmp(hostname, "UNNAMED") == 0)
		Q_strcpy(hostcache[0].name, "local");
	else
		Q_strcpy(hostcache[0].name, hostname);
	Q_strcpy(hostcache[0].map, sv.name);
	hostcache[0].users = net_activeconnections;
	hostcache[0].maxusers = svs.maxclients;
	hostcache[0].driver = net_driverlevel;
	Q_strcpy(hostcache[0].cname, "local");
#endif
}

qsocket_t* Loop_Connect(char *host)
{
    if (Q_strcmp(host, "local") != 0)
        return NULL;

    localconnectpending = true;

    if (!loop_client)
    {
        if ((loop_client = NET_NewQSocket()) == NULL)
        {
            Con_Printf("Loop_Connect: no qsocket available\n");
            return NULL;
        }
#if USING_REALLY_NETWORK
		Q_strcpy (loop_client->address, "localhost");
#endif
    }
    loop_client->receiveMessageLength = 0;
#if USING_REALLY_NETWORK
	loop_client->sendMessageLength = 0;
#endif
    loop_client->canSend = true;

    if (!loop_server)
    {
        if ((loop_server = NET_NewQSocket()) == NULL)
        {
            Con_Printf("Loop_Connect: no qsocket available\n");
            return NULL;
        }
#if USING_REALLY_NETWORK
		Q_strcpy (loop_server->address, "LOCAL");
#endif
    }
    loop_server->receiveMessageLength = 0;
#if USING_REALLY_NETWORK
	loop_server->sendMessageLength = 0;
#endif
    loop_server->canSend = true;

    loop_client->driverdata = (void*) loop_server;
    loop_server->driverdata = (void*) loop_client;

    return loop_client;
}

qsocket_t* Loop_CheckNewConnections(void)
{
    if (!localconnectpending)
        return NULL;

    localconnectpending = false;
#if USING_REALLY_NETWORK
	loop_server->sendMessageLength = 0;
#endif
    loop_server->receiveMessageLength = 0;
    loop_server->canSend = true;
#if USING_REALLY_NETWORK
	loop_client->sendMessageLength = 0;
#endif
    loop_client->receiveMessageLength = 0;
    loop_client->canSend = true;
    return loop_server;
}

static int IntAlign(int value)
{
    return (value + (sizeof(int) - 1)) & (~(sizeof(int) - 1));
}

int Loop_GetMessage(qsocket_t *sock)
{
    int ret;
    int length;

    if (sock->receiveMessageLength == 0)
        return 0;

    ret = sock->receiveMessage[0];
    length = sock->receiveMessage[1] + (sock->receiveMessage[2] << 8);
//    printf("Loop Get Message len %d, actual len: %d\r\n", sock->receiveMessageLength, length);

// alignment byte skipped here
    SZ_Clear(&net_message);
    SZ_Write(&net_message, &sock->receiveMessage[4], length);

    length = IntAlign(length + 4);
    sock->receiveMessageLength -= length;

    if (sock->receiveMessageLength)
        Q_memcpy(sock->receiveMessage, &sock->receiveMessage[length], sock->receiveMessageLength);

    if (sock->driverdata && ret == 1)
        ((qsocket_t*) sock->driverdata)->canSend = true;

    return ret;
}

int Loop_SendMessage(qsocket_t *sock, sizebuf_t *data)
{
    byte *buffer;
    short *bufferLength;

    if (!sock->driverdata)
        return -1;

    bufferLength = &((qsocket_t*) sock->driverdata)->receiveMessageLength;

    if ((*bufferLength + data->cursize + 4) > sock->maxMessageLength)
        Sys_Error("Loop_SendMessage: overflow\n");

    buffer = ((qsocket_t*) sock->driverdata)->receiveMessage + *bufferLength;

    // message type
    *buffer++ = 1;

    // length
    *buffer++ = data->cursize & 0xff;
    *buffer++ = data->cursize >> 8;

    // align
    buffer++;

    // message
    Q_memcpy(buffer, data->data, data->cursize);
    *bufferLength = IntAlign(*bufferLength + data->cursize + 4);

    sock->canSend = false;
    return 1;
}

int Loop_SendUnreliableMessage(qsocket_t *sock, sizebuf_t *data)
{
    byte *buffer;
    short *bufferLength;

    if (!sock->driverdata)
        return -1;

    bufferLength = &((qsocket_t*) sock->driverdata)->receiveMessageLength;

    if ((*bufferLength + data->cursize + (int) sizeof(byte) + (int) sizeof(short)) > sock->maxMessageLength)
        return 0;

    buffer = ((qsocket_t*) sock->driverdata)->receiveMessage + *bufferLength;

    // message type
    *buffer++ = 2;

    // length
    *buffer++ = data->cursize & 0xff;
    *buffer++ = data->cursize >> 8;

    // align
    buffer++;

    // message
    Q_memcpy(buffer, data->data, data->cursize);
    *bufferLength = IntAlign(*bufferLength + data->cursize + 4);
    return 1;
}

qboolean Loop_CanSendMessage(qsocket_t *sock)
{
    if (!sock->driverdata)
        return false;
    return sock->canSend;
}

qboolean Loop_CanSendUnreliableMessage(qsocket_t *sock)
{
    (void) sock;
    return true;
}

void Loop_Close(qsocket_t *sock)
{
    if (sock->driverdata)
        ((qsocket_t*) sock->driverdata)->driverdata = NULL;
    sock->receiveMessageLength = 0;
#if USING_REALLY_NETWORK
	sock->sendMessageLength = 0;
#endif
    sock->canSend = true;
    if (sock == loop_client)
        loop_client = NULL;
    else
        loop_server = NULL;
}
