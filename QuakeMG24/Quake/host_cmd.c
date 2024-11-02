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
#if USE_ORIGINAL_CVAR
extern cvar_t	pausable;
#endif
#pragma GCC optimize("Os") //
int current_skill;

/*
 ==================
 Host_Quit_f
 ==================
 */

extern void M_Menu_Quit_f(void);

void Host_Quit_f(void)
{
    if (key_dest != key_console && _g->cls.state != ca_dedicated)
    {
        M_Menu_Quit_f();
        return;
    }
    CL_Disconnect();
    Host_ShutdownServer(false);
#if WIN32
	Sys_Quit ();
#else
    NVIC_SystemReset();
#endif
}

/*
 ==================
 Host_Status_f
 ==================
 */
void Host_Status_f(void)
{
#if HAS_MULTIPLAYER
	client_t	*client;
	int			seconds;
	int			minutes;
	int			hours = 0;
	int			j;
#endif
    void (*print)(char *fmt, ...);

    if (cmd_source == src_command)
    {
        if (!sv.active)
        {
            Cmd_ForwardToServer();
            return;
        }
        print = Con_Printf;
    }
    else
        print = SV_ClientPrintf;

    print("host:    %s\n", Cvar_VariableString("hostname"));
    print("version: %4.2f\n", VERSION);
#if HAS_MULTIPLAYER
	if (tcpipAvailable)
		print ("tcp/ip:  %s\n", my_tcpip_address);
	if (ipxAvailable)
		print ("ipx:     %s\n", my_ipx_address);
#endif
    print("map:     %s\n", sv.name);
    print("players: %i active (%i max)\n\n", net_activeconnections, svs.maxclients);
#if HAS_MULTIPLAYER
	for (j=0, client = svs.clients ; j<svs.maxclients ; j++, client++)
	{
		if (!client->active)
			continue;
		seconds = (int)(net_time - client->netconnection->connecttime);
		minutes = seconds / 60;
		if (minutes)
		{
			seconds -= (minutes * 60);
			hours = minutes / 60;
			if (hours)
				minutes -= (hours * 60);
		}
		else
			hours = 0;
		print ("#%-2u %-16.16s  %3i  %2i:%02i:%02i\n", j+1, client->name, (int)get_qcc_frags(client->edict), hours, minutes, seconds);
#if USING_REALLY_NETWORK
		print ("   %s\n", client->netconnection->address);
#endif
	}
#endif
}

/*
 ==================
 Host_God_f

 Sets client to godmode
 ==================
 */
void Host_God_f(void)
{
    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
#if USE_PROGSDAT
	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    if (progs.qcc_deathmatch && !host_client->privileged)
        return;

#endif
    set_qcc_flags((edict_t*) sv_player, (int) get_qcc_flags((edict_t*) sv_player) ^ FL_GODMODE);
    if (!((int) get_qcc_flags((edict_t*) sv_player) & FL_GODMODE))
        SV_ClientPrintf("godmode OFF\n");
    else
        SV_ClientPrintf("godmode ON\n");
}

void Host_Notarget_f(void)
{
    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }

#if USE_PROGSDAT
	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    if (progs.qcc_deathmatch && !host_client->privileged)
        return;

#endif

    set_qcc_flags((edict_t*) sv_player, (int) get_qcc_flags((edict_t*) sv_player) ^ FL_NOTARGET);
    if (!((int) get_qcc_flags((edict_t*) sv_player) & FL_NOTARGET))
        SV_ClientPrintf("notarget OFF\n");
    else
        SV_ClientPrintf("notarget ON\n");
}

qboolean noclip_anglehack;

void Host_Noclip_f(void)
{
    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
#if USE_PROGSDAT
	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    if (progs.qcc_deathmatch && !host_client->privileged)
        return;

#endif

    if (get_qcc_movetype((edict_t*) sv_player) != MOVETYPE_NOCLIP)
    {
        noclip_anglehack = true;
        set_qcc_movetype((edict_t*) sv_player, MOVETYPE_NOCLIP);
        SV_ClientPrintf("noclip ON\n");
    }
    else
    {
        noclip_anglehack = false;
        set_qcc_movetype((edict_t*) sv_player, MOVETYPE_WALK);
        SV_ClientPrintf("noclip OFF\n");
    }
}

/*
 ==================
 Host_Fly_f

 Sets client to flymode
 ==================
 */
void Host_Fly_f(void)
{
    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
#if USE_PROGSDAT
	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    if (progs.qcc_deathmatch && !host_client->privileged)
        return;
#endif

    if (get_qcc_movetype((edict_t*) sv_player) != MOVETYPE_FLY)
    {
        set_qcc_movetype((edict_t*) sv_player, MOVETYPE_FLY);
        SV_ClientPrintf("flymode ON\n");
    }
    else
    {
        set_qcc_movetype((edict_t*) sv_player, MOVETYPE_WALK);
        SV_ClientPrintf("flymode OFF\n");
    }
}

/*
 ==================
 Host_Ping_f

 ==================
 */
void Host_Ping_f(void)
{


    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
#if 0
    int i, j;
    float total;
    client_t *client;

    SV_ClientPrintf("Client ping times:\n");
    for (i = 0, client = svs.clients; i < svs.maxclients; i++, client++)
    {
        if (!client->active)
            continue;
        total = 0;
        for (j = 0; j < NUM_PING_TIMES; j++)
            total += client->ping_times[j];
        total /= NUM_PING_TIMES;
        SV_ClientPrintf("%4i %s\n", (int) (total * 1000), client->name);
    }
#endif

}

/*
 ===============================================================================

 SERVER TRANSITIONS

 ===============================================================================
 */

/*
 ======================
 Host_Map_f

 handle a
 map <servername>
 command from the console.  Active clients are kicked off.
 ======================
 */
void Host_Map_f(void)
{
    int i;
    char name[MAX_QPATH];

    if (cmd_source != src_command)
        return;

    _g->cls.demonum = -1;		// stop demo loop in case this fails

    CL_Disconnect();
    Host_ShutdownServer(false);

    key_dest = key_game;			// remove console or menu
    SCR_BeginLoadingPlaque();

    _g->cls.mapstring[0] = 0;
    for (i = 0; i < Cmd_Argc(); i++)
    {
        strcat(_g->cls.mapstring, Cmd_Argv(i));
        strcat(_g->cls.mapstring, " ");
    }
    strcat(_g->cls.mapstring, "\n");

    svs.serverflags = 0;			// haven't completed an episode yet
    strcpy(name, Cmd_Argv(1));

    SV_SpawnServer(name, false);

    if (!sv.active)
        return;

    if (_g->cls.state != ca_dedicated)
    {
#if HAS_SPAWN_PARAMS
		strcpy (_g->cls.spawnparms, "");

		for (i=2 ; i<Cmd_Argc() ; i++)
		{
			strcat (_g->cls.spawnparms, Cmd_Argv(i));
			strcat (_g->cls.spawnparms, " ");
		}
#endif
        Cmd_ExecuteString("connect local", src_command);
    }
}

/*
 ==================
 Host_Changelevel_f

 Goes to a new map, taking all clients along
 ==================
 */
void Host_Changelevel_f(void)
{
    char level[MAX_QPATH];

    if (Cmd_Argc() != 2)
    {
        Con_Printf("changelevel <levelname> : continue game on a new level\n");
        return;
    }
    if (!sv.active || _g->cls.demoplayback)
    {
        Con_Printf("Only the server may changelevel\n");
        return;
    }
    FIXME("HOST CHANGE LEVEL");
    SV_SaveSpawnparms();
    strcpy(level, Cmd_Argv(1));
    SV_SpawnServer(level, false);
}

/*
 ==================
 Host_Restart_f

 Restarts the current server for a dead player
 ==================
 */
void Host_Restart_f(void)
{
    char mapname[MAX_QPATH];

    if (_g->cls.demoplayback || !sv.active)
        return;

    if (cmd_source != src_command)
        return;
    strcpy(mapname, sv.name);	// must copy out, because it gets cleared
                                // in sv_spawnserver
    SV_SpawnServer(mapname, true);
}

/*
 ==================
 Host_Reconnect_f

 This command causes the client to wait for the signon messages again.
 This is sent just before a server changes levels
 ==================
 */
void Host_Reconnect_f(void)
{
    SCR_BeginLoadingPlaque();
    _g->cls.signon = 0;		// need new connection messages
}

/*
 =====================
 Host_Connect_f

 User command to connect to server
 =====================
 */
void Host_Connect_f(void)
{
    char name[MAX_QPATH];

    _g->cls.demonum = -1;		// stop demo loop in case this fails
    if (_g->cls.demoplayback)
    {
        CL_StopPlayback();
        CL_Disconnect();
    }
    strcpy(name, Cmd_Argv(1));
    CL_EstablishConnection(name);
    Host_Reconnect_f();
}

/*
 ===============================================================================

 LOAD / SAVE GAME

 ===============================================================================
 */

/*
 ===============
 Host_SavegameComment

 Writes a SAVEGAME_COMMENT_LENGTH character comment describing the current
 ===============
 */
void Host_SavegameComment(char *text)
{
    int i;

    for (i = 0; i < SAVEGAME_COMMENT_LENGTH; i++)
        text[i] = ' ';
    // next-hack: remove all the stuff. Just write exmy. FIXME: We  will do something better later.
    strncpy(text, /*_g->cls.mapstring*/sv.name, SAVEGAME_COMMENT_LENGTH + 1);
    text[SAVEGAME_COMMENT_LENGTH] = '\0';
}

/*
 ===============
 Host_Savegame_f
 ===============
 */
void Host_Savegame_f(void)
{
    printf("Size of is nvm: %d sett: %d %d sg: %d %d\r\n", sizeof(nvmData_t), sizeof(padded_settings_t), sizeof(settings_t), sizeof (padded_savegame_t), sizeof (savegame_t));
    FIXME("SIZE OF savegame\r\n");
    int i;
    char comment[SAVEGAME_COMMENT_LENGTH + 1];
    if (cmd_source != src_command)
        return;

    if (!sv.active)
    {
        Con_Printf("Not playing a local game.\n");
        return;
    }

    if (_g->cl.intermission)
    {
        Con_Printf("Can't save in intermission.\n");
        return;
    }

    if (svs.maxclients != 1)
    {
        Con_Printf("Can't save multiplayer games.\n");
        return;
    }

    if (Cmd_Argc() != 2)
    {
        Con_Printf("save <savename> : save a game\n");
        return;
    }
    if (strstr(Cmd_Argv(1), ".."))
    {
        Con_Printf("Relative pathnames are not allowed.\n");
        return;
    }
    for (i = 0; i < svs.maxclients; i++)
    {
        if (svs.clients[i].active && (get_qcc_health((edict_t*) svs.clients[i].edict) <= 0))
        {
            Con_Printf("Can't savegame with a dead player\n");
            return;
        }
    }
    // getting savegame number.
    unsigned int savegameNumber = MAX_SAVEGAMES;
    sscanf(&(Cmd_Argv(1)[1]), "%d", &savegameNumber);
    if (savegameNumber >= MAX_SAVEGAMES)
    {
        Con_Printf("Wrong save game number!\n");
        return;
    }
    // next-hack. Ok this is really crappy. We cannot really use the pointer, it's just for offsets!
    nvmData_t *nvm = (nvmData_t*) ((byte*) extMemGetSize() - sizeof(nvmData_t));
    extMemErase((uint32_t) &nvm->savegames[savegameNumber], SAVE_GAME_SIZE);
    //
    //

    // save indexes
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.numEdicts, (uint8_t*) &sv.num_edicts, sizeof(nvm->savegames[savegameNumber].s.numEdicts));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.numSounds, (uint8_t*) &total_channels, sizeof(nvm->savegames[savegameNumber].s.numSounds));

    // save comment, name, time, skill
    Host_SavegameComment(comment);
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.comment, (uint8_t*) &comment, sizeof(nvm->savegames[savegameNumber].s.comment));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.skill, (uint8_t*) &current_skill, sizeof(nvm->savegames[savegameNumber].s.skill));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.name, (uint8_t*) &sv.name, sizeof(nvm->savegames[savegameNumber].s.name));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.time, (uint8_t*) &sv.time, sizeof(nvm->savegames[savegameNumber].s.time));
    // save edicts ptr
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.sv_edicts, (uint8_t*) &sv.edicts, sizeof(sv.edicts));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.sv_lastEdict, (uint8_t*) &sv.lastEdict, sizeof(sv.lastEdict));
    // save area node info
    int numAreaNodes = getNumAreaNodes();
    void *areanode = getAreaNode();
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.numareadnodes, (uint8_t*) &numAreaNodes, sizeof(nvm->savegames[savegameNumber].s.numareadnodes));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.areanode, (uint8_t*) &areanode, sizeof(nvm->savegames[savegameNumber].s.areanode));
    // save nodehaddlight
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.nodeHadDlight, (uint8_t*) &nodeHadDlight,
        sizeof(nvm->savegames[savegameNumber].s.nodeHadDlight));
    // spawn params
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.spawn_params, (uint8_t*) &svs.clients->spawn_parms[0],
        sizeof(nvm->savegames[savegameNumber].s.spawn_params));
    // write the light styles
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.lightstyles_idx, (uint8_t*) &sv.lightstyles_idx,
        sizeof(nvm->savegames[savegameNumber].s.lightstyles_idx));
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.lightstyles_len, (uint8_t*) &sv.lightstyles_len,
        sizeof(nvm->savegames[savegameNumber].s.lightstyles_len));

    // save zone mem
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.memzone, (uint8_t*) staticZone, sizeof(nvm->savegames[savegameNumber].s.memzone));
    // save all the data about static_light_edicts.
#if SAVE_STATIC_LIGHTS
    static_light_edict_t  * e = ( static_light_edict_t *) sv.edicts;
    int numEdict = 0;
    while ((e = getNextEdict(e)) != END_EDICT)
    {
        numEdict++;
        int type = qcc_classname2type[get_qcc_classname(e)];
        if (type == static_light_edict_idx)
        {
            extMemProgram(&nvm->savegames[savegameNumber].s.romEntvars[numEdict], e->v.romEntvars, sizeof(nvm->savegames[savegameNumber].s.romEntvars[numEdict]));
        }
    }
#endif
    // save audio channels, including sounds coming from edicts.
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.channels, (uint8_t*) &channels, sizeof(nvm->savegames[savegameNumber].s.channels));
    // save global progs data
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.progsvars, (uint8_t*) &progs, sizeof(nvm->savegames[savegameNumber].s.progsvars));
    // save vid pointer
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.pcolormap, (uint8_t*) &vid.colormap, sizeof(nvm->savegames[savegameNumber].s.pcolormap));

    uint32_t cookie = SAVEGAME_COOKIE;
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.cookie, (uint8_t*) &cookie, sizeof(nvm->savegames[savegameNumber].s.cookie));
    uint32_t version = SAVEGAME_VERSION;
    extMemProgram((uint32_t) &nvm->savegames[savegameNumber].s.version, (uint8_t*) &version, sizeof(nvm->savegames[savegameNumber].s.version));
    Con_Printf("done.\n");

}

/*
 ===============
 Host_Loadgame_f
 ===============
 */
void Host_Loadgame_f(void)
{
    char mapname[MAX_QPATH];
    float time;
    float spawn_parms[NUM_SPAWN_PARMS];

    if (cmd_source != src_command)
        return;

    if (Cmd_Argc() != 2)
    {
        Con_Printf("load <savename> : load a game\n");
        return;
    }

    _g->cls.demonum = -1;		// stop demo loop in case this fails

    unsigned int savegameNumber = MAX_SAVEGAMES;
    sscanf(&(Cmd_Argv(1)[1]), "%d", &savegameNumber);
    if (savegameNumber >= MAX_SAVEGAMES)
    {
        Con_Printf("Wrong save game number!\n");
        return;
    }

    // next-hack. Ok this is really crappy. We cannot really use the pointer, it's just for offsets!
#if WIN32
  nvmData_t *nvm = &ext_memory[EXT_MEMORY_SIZE - sizeof(nvmData_t)];
#else
    nvmData_t *nvm = (nvmData_t*) ((byte*) extMemGetSize() - sizeof(nvmData_t));
#endif
    uint32_t cookie;
    extMemGetDataFromAddress(&cookie, (uint8_t*) &nvm->savegames[savegameNumber].s.cookie, sizeof(cookie));

    if (cookie != SAVEGAME_COOKIE)
    {
        Con_Printf("Savegame cookie is 0x%x, not 0x%x\n", cookie, SAVEGAME_COOKIE);
        return;
    }
    uint32_t version;

    extMemGetDataFromAddress(&version, &nvm->savegames[savegameNumber].s.version, sizeof(version));

    //
    if (version != SAVEGAME_VERSION)
    {
        Con_Printf("Savegame version is %i, not %i\n", version, SAVEGAME_VERSION);
        return;
    }
    // read spawn params

    extMemGetDataFromAddress(&spawn_parms, &nvm->savegames[savegameNumber].s.spawn_params, sizeof(nvm->savegames[savegameNumber].s.spawn_params));

    extMemGetDataFromAddress(mapname, &nvm->savegames[savegameNumber].s.name, sizeof(nvm->savegames[savegameNumber].s.name));

    extMemGetDataFromAddress(&time, &nvm->savegames[savegameNumber].s.time, sizeof(nvm->savegames[savegameNumber].s.time));
    // make copy of sv, because disconnect will clear it.
    qboolean sameMapAndSettings = false;
    tempStringStack = (char*) ((uint32_t) tempStringStack & ~3) - sizeof(server_t);
    server_t *oldSv = (server_t*) tempStringStack;
    // read skill
    extMemGetDataFromAddress(&current_skill, &nvm->savegames[savegameNumber].s.skill, sizeof(current_skill));
    if (!strcmp(mapname, sv.name) && skill == current_skill && sv.name[0] != 0)
    {
        sameMapAndSettings = true;
        memcpy(oldSv, &sv, sizeof(*oldSv));
    }
    Cvar_SetValue("skill", (float) current_skill);

    CL_Disconnect_f();
    // copy, back, so that we have again the server map on it, so that we detect if we have to reload all.
    if (sameMapAndSettings)
    {
        oldSv->active = false;
        memcpy(&sv, oldSv, sizeof(sv));
    }
    SV_SpawnServer(mapname, false);
    // load vid pointer
    extMemGetDataFromAddress((uint8_t*) &vid.colormap, (void*) &nvm->savegames[savegameNumber].s.pcolormap,  sizeof(nvm->savegames[savegameNumber].s.pcolormap));

    //
    if (!sv.active)
    {
        Con_Printf("Couldn't load map\n");
        return;
    }

    sv.paused = true;		// pause until all clients connect
    sv.loadgame = true;

    // load the light styles
    extMemGetDataFromAddress(&sv.lightstyles_idx, &nvm->savegames[savegameNumber].s.lightstyles_idx, sizeof(nvm->savegames[savegameNumber].s.lightstyles_idx));

    extMemGetDataFromAddress(&sv.lightstyles_len, &nvm->savegames[savegameNumber].s.lightstyles_len, sizeof(nvm->savegames[savegameNumber].s.lightstyles_len));
    // get number of channels

    extMemGetDataFromAddress(&total_channels, &nvm->savegames[savegameNumber].s.numSounds, sizeof(total_channels));
    // get num of edicts
    extMemGetDataFromAddress(&sv.num_edicts, &nvm->savegames[savegameNumber].s.numEdicts, sizeof(sv.num_edicts));
    // get zone mem (including edicts)
    printf("There were %d edicts\r\n", sv.num_edicts);
    extMemGetDataFromAddress(staticZone, &nvm->savegames[savegameNumber].s.memzone, sizeof(nvm->savegames[savegameNumber].s.memzone));

    extMemGetDataFromAddress(&sv.edicts, &nvm->savegames[savegameNumber].s.sv_edicts, sizeof(sv.edicts));
    extMemGetDataFromAddress(&sv.lastEdict, &nvm->savegames[savegameNumber].s.sv_lastEdict, sizeof(sv.lastEdict));
    //
    svs.clients[0].edict = (player_edict_t*) EDICT_NUM(1);
    //
    void *areanode;
    int numAreaNodes;
    extMemGetDataFromAddress(&areanode, &nvm->savegames[savegameNumber].s.areanode, sizeof(nvm->savegames[savegameNumber].s.areanode));
    extMemGetDataFromAddress(&numAreaNodes, &nvm->savegames[savegameNumber].s.numareadnodes, sizeof(nvm->savegames[savegameNumber].s.numareadnodes));
    //
    setAreaNode(areanode, numAreaNodes);
    // load nodehaddlight
    extMemGetDataFromAddress(&nodeHadDlight, &nvm->savegames[savegameNumber].s.nodeHadDlight, sizeof(nvm->savegames[savegameNumber].s.nodeHadDlight));

    // read audio channels, including sounds coming from edicts.
    extMemGetDataFromAddress(&channels, &nvm->savegames[savegameNumber].s.channels, sizeof(nvm->savegames[savegameNumber].s.channels));
    // read global data
    extMemGetDataFromAddress(&progs, &nvm->savegames[savegameNumber].s.progsvars, sizeof(nvm->savegames[savegameNumber].s.progsvars));
    //
    //
    sv.time = time;
    // copy spawn params
    for (int i = 0; i < NUM_SPAWN_PARMS; i++)
        svs.clients->spawn_parms[i] = spawn_parms[i];

    if (_g->cls.state != ca_dedicated)
    {
        CL_EstablishConnection("local");
        Host_Reconnect_f();
        _g->cls.signon = 0;
    }
}

//============================================================================

/*
 ======================
 Host_Name_f
 ======================
 */
void Host_Name_f(void)
{
#if HAS_MULTIPLAYER
    char *newName;

    if (Cmd_Argc() == 1)
    {
        Con_Printf("\"name\" is \"%s\"\n", cl_name);
        return;
    }
    if (Cmd_Argc() == 2)
        newName = Cmd_Argv(1);
    else
        newName = Cmd_Args();
    newName[15] = 0;

    if (cmd_source == src_command)
    {
        if (Q_strcmp(cl_name, newName) == 0)
            return;
        Cvar_Set("_cl_name", newName);
        if (_g->cls.state == ca_connected)
            Cmd_ForwardToServer();
        return;
    }

    if (host_client->name[0] && strcmp(host_client->name, "unconnected"))
        if (Q_strcmp(host_client->name, newName) != 0)
            Con_Printf("%s renamed to %s\n", host_client->name, newName);
    Q_strcpy(host_client->name, newName);
#if USE_PROGSDAT
	set_qcc_netname(host_client->edict,  host_client->name - pr_strings);
#endif
// send notification to all clients

    MSG_WriteByte(&sv.reliable_datagram, svc_updatename);
    MSG_WriteByte(&sv.reliable_datagram, host_client - svs.clients);
    MSG_WriteString(&sv.reliable_datagram, host_client->name);
#endif
}

void Host_Version_f(void)
{
    Con_Printf("Version %d.%02d\n", (int) VERSION, (int) (VERSION * 100) % 100);
    Con_Printf("Exe: "__TIME__" "__DATE__"\n");
}

#ifdef IDGODS
void Host_Please_f (void)
{
	client_t *cl;
	int			j;

	if (cmd_source != src_command)
		return;

	if ((Cmd_Argc () == 3) && Q_strcmp(Cmd_Argv(1), "#") == 0)
	{
		j = Q_atof(Cmd_Argv(2)) - 1;
		if (j < 0 || j >= svs.maxclients)
			return;
		if (!svs.clients[j].active)
			return;
		cl = &svs.clients[j];
		if (cl->privileged)
		{
			cl->privileged = false;
			cl->edict->v.flags = (int)cl->edict->v.flags & ~(FL_GODMODE|FL_NOTARGET);
			cl->edict->v.movetype = MOVETYPE_WALK;
			noclip_anglehack = false;
		}
		else
			cl->privileged = true;
	}

	if (Cmd_Argc () != 2)
		return;

	for (j=0, cl = svs.clients ; j<svs.maxclients ; j++, cl++)
	{
		if (!cl->active)
			continue;
		if (Q_strcasecmp(cl->name, Cmd_Argv(1)) == 0)
		{
			if (cl->privileged)
			{
				cl->privileged = false;
				cl->edict->v.flags = (int)cl->edict->v.flags & ~(FL_GODMODE|FL_NOTARGET);
				cl->edict->v.movetype = MOVETYPE_WALK;
				noclip_anglehack = false;
			}
			else
				cl->privileged = true;
			break;
		}
	}
}
#endif
#if HAS_MULTIPLAYER
void Host_Say(qboolean teamonly)
{
    client_t *client;
    client_t *save;
    int j;
    char *p;
    char text[64];
    qboolean fromServer = false;

    if (cmd_source == src_command)
    {
        if (_g->cls.state == ca_dedicated)
        {
            fromServer = true;
            teamonly = false;
        }
        else
        {
            Cmd_ForwardToServer();
            return;
        }
    }

    if (Cmd_Argc() < 2)
        return;

    save = host_client;

    p = Cmd_Args();
// remove quotes if present
    if (*p == '"')
    {
        p++;
        p[Q_strlen(p) - 1] = 0;
    }

// turn on color set 1
    if (!fromServer)
        sprintf(text, "%c%s: ", 1, save->name);
    else
        sprintf(text, "%c<%s> ", 1, hostname);

    j = sizeof(text) - 2 - Q_strlen(text);  // -2 for /n and null terminator
    if (Q_strlen(p) > j)
        p[j] = 0;

    strcat(text, p);
    strcat(text, "\n");

    for (j = 0, client = svs.clients; j < svs.maxclients; j++, client++)
    {
        if (!client || !client->active || !client->spawned)
            continue;
        if (teamplay && teamonly && get_qcc_team((edict_t*) client->edict) != get_qcc_team((edict_t*) save->edict))
            continue;
        host_client = client;
        SV_ClientPrintf("%s", text);
    }
    host_client = save;

    Sys_Printf("%s", &text[1]);
}
#endif
void Host_Say_f(void)
{
#if HAS_MULTIPLAYER
    Host_Say(false);
#endif
}

void Host_Say_Team_f(void)
{
#if HAS_MULTIPLAYER
    Host_Say(true);
#endif
}

void Host_Tell_f(void)
{
    client_t *client;
    client_t *save;
    int j;
    char *p;
    char text[64];

    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }

    if (Cmd_Argc() < 3)
        return;

    Q_strcpy(text, host_client->name);
    Q_strcat(text, ": ");

    p = Cmd_Args();

// remove quotes if present
    if (*p == '"')
    {
        p++;
        p[Q_strlen(p) - 1] = 0;
    }

// check length & truncate if necessary
    j = sizeof(text) - 2 - Q_strlen(text);  // -2 for /n and null terminator
    if (Q_strlen(p) > j)
        p[j] = 0;

    strcat(text, p);
    strcat(text, "\n");

    save = host_client;
    for (j = 0, client = svs.clients; j < svs.maxclients; j++, client++)
    {
        if (!client->active || !client->spawned)
            continue;
        if (Q_strcasecmp(client->name, Cmd_Argv(1)))
            continue;
        host_client = client;
        SV_ClientPrintf("%s", text);
        break;
    }
    host_client = save;

}

/*
 ==================
 Host_Color_f
 ==================
 */
void Host_Color_f(void)
{
    int top, bottom;
    int playercolor;

    if (Cmd_Argc() == 1)
    {
        Con_Printf("\"color\" is \"%i %i\"\n", ((int) cl_color) >> 4, ((int) cl_color) & 0x0f);
        Con_Printf("color <0-13> [0-13]\n");
        return;
    }

    if (Cmd_Argc() == 2)
        top = bottom = atoi(Cmd_Argv(1));
    else
    {
        top = atoi(Cmd_Argv(1));
        bottom = atoi(Cmd_Argv(2));
    }

    top &= 15;
    if (top > 13)
        top = 13;
    bottom &= 15;
    if (bottom > 13)
        bottom = 13;

    playercolor = top * 16 + bottom;

    if (cmd_source == src_command)
    {
        Cvar_SetValue("_cl_color", playercolor);
        if (_g->cls.state == ca_connected)
            Cmd_ForwardToServer();
        return;
    }

    host_client->colors = playercolor;
    set_qcc_team((edict_t*) host_client->edict, bottom + 1);

// send notification to all clients
    MSG_WriteByte(&sv.reliable_datagram, svc_updatecolors);
    MSG_WriteByte(&sv.reliable_datagram, host_client - svs.clients);
    MSG_WriteByte(&sv.reliable_datagram, host_client->colors);

}

/*
 ==================
 Host_Kill_f
 ==================
 */
void Host_Kill_f(void)
{
    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }

    if (get_qcc_health((edict_t*) sv_player) <= 0)
    {
        SV_ClientPrintf("Can't suicide -- allready dead!\n");
        return;
    }
#if USE_PROGSDAT
	pr_global_struct->time = sv.time;
	pr_global_struct->self = EDICT_TO_PROG((edict_t*) sv_player);
	PR_ExecuteProgram (pr_global_struct->ClientKill);
#else
    progs.qcc_time = sv.time;
    progs.qcc_self = EDICT_TO_PROG((edict_t*) sv_player);
    qcc_ClientKill();

#endif
}

/*
 ==================
 Host_Pause_f
 ==================
 */
void Host_Pause_f(void)
{

    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
    if (!pausable)
        SV_ClientPrintf("Pause not allowed.\n");
    else
    {
        sv.paused ^= 1;

        if (sv.paused)
        {
#if USE_PROGSDAT
    			SV_BroadcastPrintf ("%s paused the game\n", pr_strings + get_qcc_netname((edict_t*) sv_player));
            #else
            FIXME("Host Pause not implemented");
#endif
        }
        else
        {
#if USE_PROGSDAT
			SV_BroadcastPrintf ("%s unpaused the game\n",pr_strings + get_qcc_netname((edict_t*) sv_player));
            #else
            FIXME("Host Pause not implemented");
#endif
        }

        // send notification to all clients
        MSG_WriteByte(&sv.reliable_datagram, svc_setpause);
        MSG_WriteByte(&sv.reliable_datagram, sv.paused);
    }
}

//===========================================================================

/*
 ==================
 Host_PreSpawn_f
 ==================
 */
void Host_PreSpawn_f(void)
{
    if (cmd_source == src_command)
    {
        Con_Printf("prespawn is not valid from the console\n");
        return;
    }

    if (host_client->spawned)
    {
        Con_Printf("prespawn not valid -- allready spawned\n");
        return;
    }
    SZ_Write(&host_client->message, sv.signon.data, sv.signon.cursize);
    MSG_WriteByte(&host_client->message, svc_signonnum);
    MSG_WriteByte(&host_client->message, 2);
    host_client->sendsignon = true;
}

/*
 ==================
 Host_Spawn_f
 ==================
 */
void Host_Spawn_f(void)
{
    int i;
    client_t *client;
    edict_t *ent;

    if (cmd_source == src_command)
    {
        Con_Printf("spawn is not valid from the console\n");
        return;
    }

    if (host_client->spawned)
    {
        Con_Printf("Spawn not valid -- already spawned\n");
        return;
    }

// run the entrance script
    if (sv.loadgame)
    {	// loaded games are fully inited already
        // if this is the last client to be connected, unpause
        sv.paused = false;
    }
    else
    {
        // set up the edict
        ent = (edict_t*) host_client->edict;
#if USE_PROGSDAT
		memset (&ent->v, 0, progs->entityfields * 4);
#else
        memset(&ent->v, 0, getEdictEntvarSize(ent));
#endif
        set_qcc_colormap(ent, NUM_FOR_EDICT(ent));

        set_qcc_team(ent, (host_client->colors & 15) + 1);
#if USE_PROGSDAT
		set_qcc_netname(ent,  host_client->name - pr_strings);
#else
        set_qcc_netname(ent, player_string_index);
#endif
        // copy spawn parms out of the client_t
#if USE_PROGSDAT
		for (i=0 ; i< NUM_SPAWN_PARMS ; i++)
			(&pr_global_struct->parm1)[i] = host_client->spawn_parms[i];
        // call the spawn function
		pr_global_struct->time = sv.time;
		pr_global_struct->self = EDICT_TO_PROG((edict_t*) sv_player);
		PR_ExecuteProgram (pr_global_struct->ClientConnect);
		if ((Sys_FloatTime() - host_client->netconnection->connecttime) <= sv.time)
			Sys_Printf ("%s entered the game\n", host_client->name);

		PR_ExecuteProgram (pr_global_struct->PutClientInServer);
#else
        i = 0;
        progs.qcc_parm1 = host_client->spawn_parms[i++];
        progs.qcc_parm2 = host_client->spawn_parms[i++];
        progs.qcc_parm3 = host_client->spawn_parms[i++];
        progs.qcc_parm4 = host_client->spawn_parms[i++];
        progs.qcc_parm5 = host_client->spawn_parms[i++];
        progs.qcc_parm6 = host_client->spawn_parms[i++];
        progs.qcc_parm7 = host_client->spawn_parms[i++];
        progs.qcc_parm8 = host_client->spawn_parms[i++];
        progs.qcc_parm9 = host_client->spawn_parms[i++];
        progs.qcc_parm10 = host_client->spawn_parms[i++];
        progs.qcc_parm11 = host_client->spawn_parms[i++];
        progs.qcc_parm12 = host_client->spawn_parms[i++];
        progs.qcc_parm13 = host_client->spawn_parms[i++];
        progs.qcc_parm14 = host_client->spawn_parms[i++];
        progs.qcc_parm15 = host_client->spawn_parms[i++];
        progs.qcc_parm16 = host_client->spawn_parms[i++];
        //
        progs.qcc_time = sv.time;
        progs.qcc_self = EDICT_TO_PROG((edict_t*) sv_player);
        qcc_ClientConnect();
#if HAS_MULTIPLAYER
    if ((Sys_FloatTime() - host_client->netconnection->connecttime) <= sv.time)
			Sys_Printf ("%s entered the game\n", host_client->name);
#endif
        qcc_PutClientInServer();
#endif

    }

// send all current names, colors, and frag counts
    SZ_Clear(&host_client->message);

// send time of update
    MSG_WriteByte(&host_client->message, svc_time);
    MSG_WriteFloat(&host_client->message, sv.time);

    for (i = 0, client = svs.clients; i < svs.maxclients; i++, client++)
    {
        MSG_WriteByte(&host_client->message, svc_updatename);
        MSG_WriteByte(&host_client->message, i);
        MSG_WriteString(&host_client->message, client->name);
        MSG_WriteByte(&host_client->message, svc_updatefrags);
        MSG_WriteByte(&host_client->message, i);
        MSG_WriteShort(&host_client->message, client->old_frags);
        MSG_WriteByte(&host_client->message, svc_updatecolors);
        MSG_WriteByte(&host_client->message, i);
        MSG_WriteByte(&host_client->message, client->colors);
    }
#if !DIRECT_SINGLE_PLAYER
// send all current light styles
	for (i=0 ; i<MAX_LIGHTSTYLES ; i++)
	{
		MSG_WriteByte (&host_client->message, svc_lightstyle);
		MSG_WriteByte (&host_client->message, (char)i);
		MSG_WriteString (&host_client->message, sv.lightstyles[i]);
	}
#endif

//
// send some stats
//
    MSG_WriteByte(&host_client->message, svc_updatestat);
    MSG_WriteByte(&host_client->message, STAT_TOTALSECRETS);
#if USE_PROGSDAT
	MSG_WriteLong (&host_client->message, pr_global_struct->total_secrets);
	MSG_WriteByte (&host_client->message, svc_updatestat);
	MSG_WriteByte (&host_client->message, STAT_TOTALMONSTERS);
	MSG_WriteLong (&host_client->message, pr_global_struct->total_monsters);

	MSG_WriteByte (&host_client->message, svc_updatestat);
	MSG_WriteByte (&host_client->message, STAT_SECRETS);
	MSG_WriteLong (&host_client->message, pr_global_struct->found_secrets);

	MSG_WriteByte (&host_client->message, svc_updatestat);
	MSG_WriteByte (&host_client->message, STAT_MONSTERS);
	MSG_WriteLong (&host_client->message, pr_global_struct->killed_monsters);
#else
    MSG_WriteLong(&host_client->message, progs.qcc_total_secrets);
    MSG_WriteByte(&host_client->message, svc_updatestat);
    MSG_WriteByte(&host_client->message, STAT_TOTALMONSTERS);
    MSG_WriteLong(&host_client->message, progs.qcc_total_monsters);

    MSG_WriteByte(&host_client->message, svc_updatestat);
    MSG_WriteByte(&host_client->message, STAT_SECRETS);
    MSG_WriteLong(&host_client->message, progs.qcc_found_secrets);

    MSG_WriteByte(&host_client->message, svc_updatestat);
    MSG_WriteByte(&host_client->message, STAT_MONSTERS);
    MSG_WriteLong(&host_client->message, progs.qcc_killed_monsters);

#endif

//
// send a fixangle
// Never send a roll angle, because savegames can catch the server
// in a state where it is expecting the client to correct the angle
// and it won't happen if the game was just loaded, so you wind up
// with a permanent head tilt
    ent = EDICT_NUM(1 + (host_client - svs.clients));
    MSG_WriteByte(&host_client->message, svc_setangle);
    for (i = 0; i < 2; i++)
    {
        MSG_WriteAngle(&host_client->message, VEC(get_qcc_angles(ent))[i]);
    }
    MSG_WriteAngle(&host_client->message, 0);

    SV_WriteClientdataToMessage((edict_t*) sv_player, &host_client->message);

    MSG_WriteByte(&host_client->message, svc_signonnum);
    MSG_WriteByte(&host_client->message, 3);
    host_client->sendsignon = true;

}

/*
 ==================
 Host_Begin_f
 ==================
 */
void Host_Begin_f(void)
{
    if (cmd_source == src_command)
    {
        Con_Printf("begin is not valid from the console\n");
        return;
    }

    host_client->spawned = true;
}

//===========================================================================

/*
 ==================
 Host_Kick_f

 Kicks a user off of the server
 ==================
 */
#if HAS_MULTIPLAYER
void Host_Kick_f(void)
{
    char com_token[1024];
    char *who;
    char *message = NULL;
    client_t *save;
    int i;
    qboolean byNumber = false;

    if (cmd_source == src_command)
    {
        if (!sv.active)
        {
            Cmd_ForwardToServer();
            return;
        }
    }
#if USE_PROGSDAT
	else if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    else if (progs.qcc_deathmatch && !host_client->privileged)
        return;

#endif
    save = host_client;

    if (Cmd_Argc() > 2 && Q_strcmp(Cmd_Argv(1), "#") == 0)
    {
        i = Q_atof(Cmd_Argv(2)) - 1;
        if (i < 0 || i >= svs.maxclients)
            return;
        if (!svs.clients[i].active)
            return;
        host_client = &svs.clients[i];
        byNumber = true;
    }
    else
    {
        for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
        {
            if (!host_client->active)
                continue;
            if (Q_strcasecmp(host_client->name, Cmd_Argv(1)) == 0)
                break;
        }
    }

    if (i < svs.maxclients)
    {
        if (cmd_source == src_command)
            if (_g->cls.state == ca_dedicated)
                who = "Console";
            else
                who = cl_name;
        else
            who = save->name;

        // can't kick yourself!
        if (host_client == save)
            return;

        if (Cmd_Argc() > 2)
        {
            message = COM_Parse(Cmd_Args(), com_token);
            if (byNumber)
            {
                message++;							// skip the #
                while (*message == ' ')				// skip white space
                    message++;
                message += Q_strlen(Cmd_Argv(2));	// skip the number
            }
            while (*message && *message == ' ')
                message++;
        }
        if (message)
            SV_ClientPrintf("Kicked by %s: %s\n", who, message);
        else
            SV_ClientPrintf("Kicked by %s\n", who);
        SV_DropClient(false);
    }

    host_client = save;
}
#endif
/*
 ===============================================================================

 DEBUGGING TOOLS

 ===============================================================================
 */

/*
 ==================
 Host_Give_f
 ==================
 */
#if USE_PROGSDAT
void Host_Give_f (void)
{
	char	*t;
	int		v, w;
	eval_t	*val;

	if (cmd_source == src_command)
	{
		Cmd_ForwardToServer ();
		return;
	}

	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;

	t = Cmd_Argv(1);
	v = atoi (Cmd_Argv(2));

	switch (t[0])
	{
   case '0':
   case '1':
   case '2':
   case '3':
   case '4':
   case '5':
   case '6':
   case '7':
   case '8':
   case '9':
      // MED 01/04/97 added hipnotic give stuff
      if (hipnotic)
      {
         if (t[0] == '6')
         {
            if (t[1] == 'a')
               set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | HIT_PROXIMITY_GUN);
            else
               set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | IT_GRENADE_LAUNCHER);
         }
         else if (t[0] == '9')
            set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | HIT_LASER_CANNON);
         else if (t[0] == '0')
            set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | HIT_MJOLNIR);
         else if (t[0] >= '2')
            set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | (IT_SHOTGUN << (t[0] - '2')));
      }
      else
      {
         if (t[0] >= '2')
            set_qcc_items((edict_t*) sv_player,  (int)get_qcc_items((edict_t*) sv_player) | (IT_SHOTGUN << (t[0] - '2')));
      }
		break;

    case 's':
		if (rogue)
		{
	        val = GetEdictFieldValue((edict_t*) sv_player, "ammo_shells1");
		    if (val)
			    val->_float = v;
		}

        set_qcc_ammo_shells((edict_t*) sv_player,  v);
        break;
    case 'n':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_nails1");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
					set_qcc_ammo_nails((edict_t*) sv_player,  v);
			}
		}
		else
		{
			set_qcc_ammo_nails((edict_t*) sv_player,  v);
		}
        break;
    case 'l':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_lava_nails");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
					set_qcc_ammo_nails((edict_t*) sv_player,  v);
			}
		}
        break;
    case 'r':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_rockets1");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
					set_qcc_ammo_rockets((edict_t*) sv_player,  v);
			}
		}
		else
		{
			set_qcc_ammo_rockets((edict_t*) sv_player,  v);
		}
        break;
    case 'm':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_multi_rockets");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
					set_qcc_ammo_rockets((edict_t*) sv_player,  v);
			}
		}
        break;
    case 'h':
        set_qcc_health((edict_t*) sv_player,  v);
        break;
    case 'c':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_cells1");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
					set_qcc_ammo_cells((edict_t*) sv_player,  v);
			}
		}
		else
		{
			set_qcc_ammo_cells((edict_t*) sv_player,  v);
		}
        break;
    case 'p':
		if (rogue)
		{
			val = GetEdictFieldValue((edict_t*) sv_player, "ammo_plasma");
			if (val)
			{
				val->_float = v;
				if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
					set_qcc_ammo_cells((edict_t*) sv_player,  v);
			}
		}
        break;
    }
}
#else
void Host_Give_f(void)
{
    char *t;
    int v;
    //eval_t	*val;

    if (cmd_source == src_command)
    {
        Cmd_ForwardToServer();
        return;
    }
#if USE_PROGSDAT
	if (pr_global_struct->deathmatch && !host_client->privileged)
		return;
#else
    if (progs.qcc_deathmatch && !host_client->privileged)
        return;
#endif
    t = Cmd_Argv(1);
    v = atoi(Cmd_Argv(2));

    switch (t[0])
    {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            // MED 01/04/97 added hipnotic give stuff
            if (hipnotic)
            {
                if (t[0] == '6')
                {
                    if (t[1] == 'a')
                        set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | HIT_PROXIMITY_GUN);
                    else
                        set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | IT_GRENADE_LAUNCHER);
                }
                else if (t[0] == '9')
                    set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | HIT_LASER_CANNON);
                else if (t[0] == '0')
                    set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | HIT_MJOLNIR);
                else if (t[0] >= '2')
                    set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | (IT_SHOTGUN << (t[0] - '2')));
            }
            else
            {
                if (t[0] >= '2')
                    set_qcc_items((edict_t*) sv_player, (int) get_qcc_items((edict_t*) sv_player) | (IT_SHOTGUN << (t[0] - '2')));
            }
            break;

        case 's':
            /*if (rogue)
             {
             val = GetEdictFieldValue((edict_t*) sv_player, "ammo_shells1");
             if (val)
             val->_float = v;
             }*/

            set_qcc_ammo_shells((edict_t*) sv_player, v);
            break;
        case 'n':
            if (rogue)
            {
                /*val = GetEdictFieldValue((edict_t*) sv_player, "ammo_nails1");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
                 set_qcc_ammo_nails((edict_t*) sv_player,  v);
                 }*/
            }
            else
            {
                set_qcc_ammo_nails((edict_t*) sv_player, v);
            }
            break;
        case 'l':
            if (rogue)
            {
                /*val = GetEdictFieldValue((edict_t*) sv_player, "ammo_lava_nails");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
                 set_qcc_ammo_nails((edict_t*) sv_player,  v);
                 }*/
            }
            break;
        case 'r':
            if (rogue)
            {
                /*val = GetEdictFieldValue((edict_t*) sv_player, "ammo_rockets1");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
                 set_qcc_ammo_rockets((edict_t*) sv_player,  v);
                 }*/
            }
            else
            {
                set_qcc_ammo_rockets((edict_t*) sv_player, v);
            }
            break;
        case 'm':
            if (rogue)
            {
                /*val = GetEdictFieldValue((edict_t*) sv_player, "ammo_multi_rockets");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
                 set_qcc_ammo_rockets((edict_t*) sv_player,  v);
                 }*/
            }
            break;
        case 'h':
            set_qcc_health((edict_t*) sv_player, v);
            break;
        case 'c':
            if (rogue)
            {
                /*	val = GetEdictFieldValue((edict_t*) sv_player, "ammo_cells1");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) <= IT_LIGHTNING)
                 set_qcc_ammo_cells((edict_t*) sv_player,  v);
                 }*/
            }
            else
            {
                set_qcc_ammo_cells((edict_t*) sv_player, v);
            }
            break;
        case 'p':
            if (rogue)
            {
                /*val = GetEdictFieldValue((edict_t*) sv_player, "ammo_plasma");
                 if (val)
                 {
                 val->_float = v;
                 if (get_qcc_weapon((edict_t*) sv_player) > IT_LIGHTNING)
                 set_qcc_ammo_cells((edict_t*) sv_player,  v);
                 }*/
            }
            break;
    }
}
#endif
edict_t* FindViewthing(void)
{
    int i;
    edict_t *e;
#if !EDICT_LINKED_LIST
	for (i=0 ; i<sv.num_edicts ; i++)
	{
		e = EDICT_NUM(i);
#if USE_PROGSDAT
		if ( !strcmp (pr_strings + get_qcc_classname(e), "viewthing") )
#else
		if ( !strcmp (getStringFromIndex(get_qcc_classname(e)), "viewthing") )
#endif
			return e;
	}
#else
    e = sv.edicts;
    for (i = 0; i < sv.num_edicts; i++)
    {
#if USE_PROGSDAT
		if ( !strcmp (pr_strings + get_qcc_classname(e), "viewthing") )
#else
        if (!strcmp(getStringFromIndex(get_qcc_classname(e)), "viewthing"))
#endif
            return e;
        e = getNextEdict(e);
    }

#endif
    Con_Printf("No viewthing on map\n");
    return NULL;
}

/*
 ==================
 Host_Viewmodel_f
 ==================
 */
void Host_Viewmodel_f(void)
{
    edict_t *e;
    model_t *m;

    e = FindViewthing();
    if (!e)
        return;

    m = Mod_ForName(Cmd_Argv(1), false);
    if (!m)
    {
        Con_Printf("Can't load %s\n", Cmd_Argv(1));
        return;
    }

    set_qcc_frame(e, 0);
    _g->cl.model_precache[(int) get_qcc_modelindex(e)] = m;
}

/*
 ==================
 Host_Viewframe_f
 ==================
 */
void Host_Viewframe_f(void)
{
    edict_t *e;
    int f;
    model_t *m;

    e = FindViewthing();
    if (!e)
        return;
    m = _g->cl.model_precache[(int) get_qcc_modelindex(e)];

    f = atoi(Cmd_Argv(1));
    if (f >= m->numframes)
        f = m->numframes - 1;

    set_qcc_frame(e, f);
}

void PrintFrameName(model_t *m, int frame)
{
    // disabled
    (void) m;
    (void) frame;
#if 0
    aliashdr_t 			*hdr;
	maliasframedesc_t	*pframedesc;

	hdr = (aliashdr_t *)Mod_Extradata (m);
	if (!hdr)
		return;
	pframedesc = &hdr->frames[frame];

	//Con_Printf ("frame %i: %s\n", frame, pframedesc->name);
#endif
}

/*
 ==================
 Host_Viewnext_f
 ==================
 */
void Host_Viewnext_f(void)
{
    edict_t *e;
    model_t *m;

    e = FindViewthing();
    if (!e)
        return;
    m = _g->cl.model_precache[(int) get_qcc_modelindex(e)];

    set_qcc_frame(e, get_qcc_frame(e) + 1);
    if (get_qcc_frame(e) >= m->numframes)
        set_qcc_frame(e, m->numframes - 1);

    PrintFrameName(m, get_qcc_frame(e));
}

/*
 ==================
 Host_Viewprev_f
 ==================
 */
void Host_Viewprev_f(void)
{
    edict_t *e;
    model_t *m;

    e = FindViewthing();
    if (!e)
        return;

    m = _g->cl.model_precache[(int) get_qcc_modelindex(e)];

    set_qcc_frame(e, get_qcc_frame(e) - 1);
    if (get_qcc_frame(e) < 0)
        set_qcc_frame(e, 0);

    PrintFrameName(m, get_qcc_frame(e));
}

/*
 ===============================================================================

 DEMO LOOP CONTROL

 ===============================================================================
 */

/*
 ==================
 Host_Startdemos_f
 ==================
 */
void Host_Startdemos_f(void)
{
    int i, c;

    if (_g->cls.state == ca_dedicated)
    {
        if (!sv.active)
            Cbuf_AddText("map start\n");
        return;
    }

    c = Cmd_Argc() - 1;
    if (c > MAX_DEMOS)
    {
        Con_Printf("Max %i demos in demoloop\n", MAX_DEMOS);
        c = MAX_DEMOS;
    }
    Con_Printf("%i demo(s) in loop\n", c);

    for (i = 1; i < c + 1; i++)
        strncpy(_g->cls.demos[i - 1], Cmd_Argv(i), sizeof(_g->cls.demos[0]) - 1);

    if (!sv.active && _g->cls.demonum != -1 && !_g->cls.demoplayback)
    {
        _g->cls.demonum = 0;
        CL_NextDemo();
    }
    else
        _g->cls.demonum = -1;
}

/*
 ==================
 Host_Demos_f

 Return to looping demos
 ==================
 */
void Host_Demos_f(void)
{
    if (_g->cls.state == ca_dedicated)
        return;
    if (_g->cls.demonum == -1)
        _g->cls.demonum = 1;
    CL_Disconnect_f();
    CL_NextDemo();
}

/*
 ==================
 Host_Stopdemo_f

 Return to looping demos
 ==================
 */
void Host_Stopdemo_f(void)
{
    if (_g->cls.state == ca_dedicated)
        return;
    if (!_g->cls.demoplayback)
        return;
    CL_StopPlayback();
    CL_Disconnect();
}

//=============================================================================

/*
 ==================
 Host_InitCommands
 ==================
 */
void Host_InitCommands(void)
{
}
