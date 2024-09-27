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

#include "quakedef.h"
#if WIN32
#include "extMemoryWin32.h"
#else
#include "extMemory.h"
#endif

void CL_FinishTimeDemo(void);
/*
 ==============================================================================

 DEMO CODE

 When a demo is playing back, all NET_SendMessages are skipped, and
 NET_GetMessages are read from the demo file.

 Whenever cl.time gets past the last received message, another message is
 read from the demo file.
 ==============================================================================
 */

/*
 ==============
 CL_StopPlayback

 Called when a demo file runs out, or the user starts a game
 ==============
 */
void CL_StopPlayback(void)
{
    if (!_g->cls.demoplayback)
        return;
    Z_Free(_g->client_entity_data);
    Z_Free(_g->cl_lightstyle);
    _g->cl_lightstyle = NULL;
#if !USE_EXT_MEMORY
	fclose (_g->cls.demofile);
    _g->cls.demofile = NULL;
#else
    _g->cls.demoBase = NULL;
#endif
    _g->cls.demoplayback = false;

    _g->cls.state = ca_disconnected;

    if (_g->cls.timedemo)
        CL_FinishTimeDemo();
}

/*
 ====================
 CL_WriteDemoMessage

 Dumps the current net message, prefixed by the length and view angles
 ====================
 */
void CL_WriteDemoMessage(void)
{
#if !USE_EXT_MEMORY
	int		len;
	int		i;
	float	f;

	len = LittleLong (net_message.cursize);
	fwrite (&len, 4, 1, _g->cls.demofile);
	for (i=0 ; i<3 ; i++)
	{
		f = LittleFloat (cl.viewangles[i]);
		fwrite (&f, 4, 1, _g->cls.demofile);
	}
	fwrite (net_message.data, net_message.cursize, 1, _g->cls.demofile);
	fflush (_g->cls.demofile);
	#endif
}

/*
 ====================
 CL_GetMessage

 Handles recording and playback of demos, on top of NET_ code
 ====================
 */
int CL_GetMessage(void)
{
    int r, i;
    if (_g->cls.demoplayback)
    {
        // decide if it is time to grab the next message
        if (_g->cls.signon == SIGNONS)	// always grab until fully connected
        {
            if (_g->cls.timedemo)
            {
                if (host_framecount == _g->cls.td_lastframe)
                    return 0;		// already read this frame's message
                _g->cls.td_lastframe = host_framecount;
                // if this is the second frame, grab the real td_starttime
                // so the bogus time on the first frame doesn't count
                if (host_framecount == _g->cls.td_startframe + 1)
                    _g->cls.td_starttime = realtime;
            }
            else if ( /* cl.time > 0 && */_g->cl.time <= _g->cl.mtime[0])
            {
                return 0;		// don't need another message yet
            }
        }

        // get the next message
#if !USE_EXT_MEMORY
		fread (&net_message.cursize, 4, 1, _g->cls.demofile);
    #endif
        VectorCopy(_g->cl.mviewangles[0], _g->cl.mviewangles[1]);
#if USE_EXT_MEMORY
        struct
        {
            int size;
            float coords[3];
        } message;
        extMemGetDataFromAddress(&message, &_g->cls.demoBase[_g->cls.demoPos], sizeof(message));
        net_message.cursize = message.size;
        _g->cls.demoPos += sizeof(message);
        for (i = 0; i < 3; i++)
            _g->cl.mviewangles[0][i] = message.coords[i];
#else
		for (i=0 ; i<3 ; i++)
		{
		    #if 0
	            float ff;
	            extMemGetDataFromAddress(&ff, &_g->cls.demoBase[_g->cls.demoPos], sizeof(ff));
                f = ff;
                _g->cls.demoPos += 4;
		    #else
    			r = fread (&f, 4, 1, _g->cls.demofile);
		    #endif // USE_EXT_MEMORY
    			_g->cl.mviewangles[0][i] = LittleFloat (f);
		}
#endif
#if !USE_EXT_MEMORY
		if (net_message.cursize > MAX_MSGLEN)
        {
			Sys_Error ("Demo message > MAX_MSGLEN: %d",net_message.cursize );
        }
		r = fread (net_message.data, net_message.cursize, 1, _g->cls.demofile);
		#else
        r = (_g->cls.demoPos + net_message.cursize < _g->cls.demoSize);
        if (r)
        {
            extMemGetDataFromAddress(net_message.data, &_g->cls.demoBase[_g->cls.demoPos], net_message.cursize);
        }
        _g->cls.demoPos += net_message.cursize;
#endif
        if (r != 1)
        {
            CL_StopPlayback();
            return 0;
        }

        return 1;
    }

    while (1)
    {
        r = NET_GetMessage(_g->cls.netcon);

        if (r != 1 && r != 2)
            return r;

        // discard nop keepalive message
        if (net_message.cursize == 1 && net_message.data[0] == svc_nop)
            Con_Printf("<-- server to client keepalive\n");
        else
            break;
    }

    if (_g->cls.demorecording)
        CL_WriteDemoMessage();

    return r;
}

/*
 ====================
 CL_Stop_f

 stop recording a demo
 ====================
 */
void CL_Stop_f(void)
{
    if (cmd_source != src_command)
        return;

    if (!_g->cls.demorecording)
    {
        Con_Printf("Not recording a demo.\n");
        return;
    }

// write a disconnect message to the demo file
    SZ_Clear(&net_message);
    MSG_WriteByte(&net_message, svc_disconnect);
    CL_WriteDemoMessage();

// finish up
#if !USE_EXT_MEMORY
	fclose (_g->cls.demofile);
	_g->cls.demofile = NULL;
#else
    _g->cls.demoBase = NULL;
    _g->cls.demoPos = 0;
    _g->cls.demoSize = 0;
#endif
    _g->cls.demorecording = false;
    Con_Printf("Completed demo\n");
}

/*
 ====================
 CL_Record_f

 record <demoname> <map> [cd track]
 ====================
 */
void CL_Record_f(void)
{
#if !USE_EXT_MEMORY
	int		c;
	char	name[MAX_OSPATH];
	int		track;

	if (cmd_source != src_command)
		return;

	c = Cmd_Argc();
	if (c != 2 && c != 3 && c != 4)
	{
		Con_Printf ("record <demoname> [<map> [cd track]]\n");
		return;
	}

	if (strstr(Cmd_Argv(1), ".."))
	{
		Con_Printf ("Relative pathnames are not allowed.\n");
		return;
	}

	if (c == 2 && _g->cls.state == ca_connected)
	{
		Con_Printf("Can not record - already connected to server\nClient demo recording must be started before connecting\n");
		return;
	}

// write the forced cd track number, or -1
	if (c == 4)
	{
		track = atoi(Cmd_Argv(3));
		Con_Printf ("Forcing CD track to %i\n", _g->cls.forcetrack);
	}
	else
		track = -1;

	sprintf (name, "%s/%s", com_gamedir, Cmd_Argv(1));

//
// start the map up
//
    char vastr[128];
	if (c > 2)
		Cmd_ExecuteString ( va(vastr,"map %s", Cmd_Argv(2)), src_command);

//
// open the demo file
//
	COM_DefaultExtension (name, ".dem");

	Con_Printf ("recording to %s.\n", name);
	_g->cls.demofile = fopen (name, "wb");
	if (!_g->cls.demofile)
	{
		Con_Printf ("ERROR: couldn't open.\n");
		return;
	}

	_g->cls.forcetrack = track;
	fprintf (_g->cls.demofile, "%i\n", _g->cls.forcetrack);

	_g->cls.demorecording = true;
	#endif
}

/*
 ====================
 CL_PlayDemo_f

 play [demoname]
 ====================
 */

void CL_PlayDemo_f(void)
{
#if ENABLE_DEMO
    char name[256];
    int c;
    qboolean neg = false;

    if (cmd_source != src_command)
        return;

    if (Cmd_Argc() != 2)
    {
        Con_Printf("play <demoname> : plays a demo\n");
        return;
    }

//
// disconnect from server
//
    CL_Disconnect();

//
// open the demo file
//

#if FORCE_TIME_DEMO
    strcpy(name, TIME_DEMO_NAME);
#else
    strcpy (name, Cmd_Argv(1));
#endif
    COM_DefaultExtension(name, ".dem");

    Con_Printf("Playing demo from %s.\n", name);
#if USE_EXT_MEMORY
    _g->cls.demoBase = COM_LoadFileFromExtMem(name, &_g->cls.demoSize);
    if (!_g->cls.demoBase)
    {
        Con_Printf("ERROR: couldn't open.\n");
        _g->cls.demonum = -1;		// stop demo loop
        _g->cls.demoSize = 0;
        return;
    }
    else
    {
        _g->cls.demoPos = 0;
    }
#else
	COM_FOpenFile (name, &_g->cls.demofile);
	if (!_g->cls.demofile)
	{
		Con_Printf ("ERROR: couldn't open.\n");
		_g->cls.demonum = -1;		// stop demo loop
		return;
	}
#endif // USE_EXT_MEMORY
    _g->cls.demoplayback = true;
    _g->cls.state = ca_connected;
    _g->cls.forcetrack = 0;
#if USE_EXT_MEMORY
    while ((c = extMemGetByteFromAddress(&_g->cls.demoBase[_g->cls.demoPos++])) != '\n')
        if (c == '-')
            neg = true;
        else
            _g->cls.forcetrack = _g->cls.forcetrack * 10 + (c - '0');

#else

	while ((c = getc(_g->cls.demofile)) != '\n')
		if (c == '-')
			neg = true;
		else
			_g->cls.forcetrack = _g->cls.forcetrack * 10 + (c - '0');
#endif // USE_EXT_MEMORY

    if (neg)
        _g->cls.forcetrack = -_g->cls.forcetrack;
    resetTempModKnown(NULL, NULL);
    if (!_g->cl_lightstyle)
        _g->cl_lightstyle = Z_Calloc(sizeof(*_g->cl_lightstyle), MAX_LIGHTSTYLES, PU_STATIC, 0);
    _g->cls.timedemo = FORCE_TIME_DEMO;
#else

    if (cmd_source != src_command)
        return;

    _g->cls.demonum = -1;   // stop demo loop in case this fails

    CL_Disconnect();
    Host_ShutdownServer(false);
    //
#if FORCE_START_GAME_IF_NO_DEMO
    //
    key_dest = key_game;      // remove console or menu
    SCR_BeginLoadingPlaque();
    //
    skill = START_SKILL;
    current_skill = START_SKILL;
    //
    char name[MAX_QPATH];
    _g->cls.mapstring[0] = 0;
    strcat(_g->cls.mapstring, START_MAP);
    strcat(_g->cls.mapstring, " ");
    strcat(_g->cls.mapstring, "\n");

    svs.serverflags = 0;      // haven't completed an episode yet
    strcpy(name, START_MAP);
    SV_SpawnServer(name, false);
    if (!sv.active)
        return;

    if (_g->cls.state != ca_dedicated)
    {
#if HAS_SPAWN_PARAMS
    strcpy (_g->cls.spawnparms, "");

    for (int i=2 ; i<Cmd_Argc() ; i++)
    {
      strcat (_g->cls.spawnparms, Cmd_Argv(i));
      strcat (_g->cls.spawnparms, " ");
    }
#endif
        Cmd_ExecuteString("connect local", src_command);
    }

#endif
#endif
}

/*
 ====================
 CL_FinishTimeDemo

 ====================
 */
#if WIN32
extern int aliasPixelsDrawn;
extern int aliasPixelsDrawnSingle;
extern int lightcells;
#endif
void CL_FinishTimeDemo(void)
{
    int frames;
    float time;

    _g->cls.timedemo = false;

// the first frame didn't count
    frames = (host_framecount - _g->cls.td_startframe) - 1;
    time = realtime - _g->cls.td_starttime;
    if (!time)
        time = 1;
    float mfps = (frames / time) * 1000;
    int imfps = mfps;
    Con_Printf("%i frames %d milliseconds %d.%03d fps\n", frames, (int) (1000 * time), imfps / 1000, imfps % 1000);
    printf("%i frames %d milliseconds %d.%03d fps\n", frames, (int) (1000 * time), imfps / 1000, imfps % 1000);

}

/*
 ====================
 CL_TimeDemo_f

 timedemo [demoname]
 ====================
 */
void CL_TimeDemo_f(void)
{
    if (cmd_source != src_command)
        return;

    if (Cmd_Argc() != 2)
    {
        Con_Printf("timedemo <demoname> : gets demo speeds\n");
        return;
    }

    CL_PlayDemo_f();

// _g->cls.td_starttime will be grabbed at the second frame of the demo, so
// all the loading time doesn't get counted

    _g->cls.timedemo = true;
    _g->cls.td_startframe = host_framecount;
    _g->cls.td_lastframe = -1;		// get a new message this frame
}

