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

// cvar.c -- dynamic variable tracking
#include "quakedef.h"
#pragma GCC optimize("Os") //
/*
 cvar_t	chase_back = {"chase_back", "100"};
 cvar_t	chase_up = {"chase_up", "16"};
 cvar_t	chase_right = {"chase_right", "0"};
 cvar_t	chase_active = {"chase_active", "0"};
 cvar_t	cl_upspeed = {"cl_upspeed","200"};
 cvar_t	cl_forwardspeed = {"cl_forwardspeed","200", true};
 cvar_t	cl_backspeed = {"cl_backspeed","200", true};
 cvar_t	cl_sidespeed = {"cl_sidespeed","350"};
 cvar_t	cl_movespeedkey = {"cl_movespeedkey","2.0"};
 cvar_t	cl_yawspeed = {"cl_yawspeed","140"};
 cvar_t	cl_pitchspeed = {"cl_pitchspeed","150"};
 cvar_t	cl_anglespeedkey = {"cl_anglespeedkey","1.5"};
 cvar_t  registered = {"registered","0"};
 cvar_t  cmdline = {"cmdline","0", false, true};
 cvar_t	d_subdiv16 = {"d_subdiv16", "1"};
 cvar_t	d_mipcap = {"d_mipcap", "0"};
 cvar_t	d_mipscale = {"d_mipscale", "1"};
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
 cvar_t	sv_aim = {"sv_aim", "0.93"};
 cvar_t	nomonsters = {"nomonsters", "0"};
 cvar_t	gamecfg = {"gamecfg", "0"};
 cvar_t	scratch1 = {"scratch1", "0"};
 cvar_t	scratch2 = {"scratch2", "0"};
 cvar_t	scratch3 = {"scratch3", "0"};
 cvar_t	scratch4 = {"scratch4", "0"};
 cvar_t	savedgamecfg = {"savedgamecfg", "0", true};
 cvar_t	saved1 = {"saved1", "0", true};
 cvar_t	saved2 = {"saved2", "0", true};
 cvar_t	saved3 = {"saved3", "0", true};
 cvar_t	saved4 = {"saved4", "0", true};
 cvar_t	r_draworder = {"r_draworder","0"};
 cvar_t	r_speeds = {"r_speeds","0"};
 cvar_t	r_timegraph = {"r_timegraph","0"};
 cvar_t	r_graphheight = {"r_graphheight","10"};
 cvar_t	r_clearcolor = {"r_clearcolor","2"};
 cvar_t	r_waterwarp = {"r_waterwarp","1"};
 cvar_t	r_fullbright = {"r_fullbright","0"};
 cvar_t	r_drawentities = {"r_drawentities","1"};
 cvar_t	r_drawviewmodel = {"r_drawviewmodel","1"};
 cvar_t	r_aliasstats = {"r_polymodelstats","0"};
 cvar_t	r_dspeeds = {"r_dspeeds","0"};
 cvar_t	r_drawflat = {"r_drawflat", "0"};
 cvar_t	r_ambient = {"r_ambient", "0"};
 cvar_t	r_reportsurfout = {"r_reportsurfout", "0"};
 cvar_t	r_maxsurfs = {"r_maxsurfs", "0"};
 cvar_t	r_numsurfs = {"r_numsurfs", "0"};
 cvar_t	r_reportedgeout = {"r_reportedgeout", "0"};
 cvar_t	r_maxedges = {"r_maxedges", "0"};
 cvar_t	r_numedges = {"r_numedges", "0"};
 cvar_t	r_aliastransbase = {"r_aliastransbase", "200"};
 cvar_t	r_aliastransadj = {"r_aliastransadj", "100"};
 cvar_t		scr_viewsize = {"viewsize","100", true};
 cvar_t		scr_fov = {"fov","90"};	// 10 - 170
 cvar_t		scr_conspeed = {"scr_conspeed","300"};
 cvar_t		scr_centertime = {"scr_centertime","2"};
 cvar_t		scr_showram = {"showram","1"};
 cvar_t		scr_showturtle = {"showturtle","0"};
 cvar_t		scr_showpause = {"showpause","1"};
 cvar_t		scr_printspeed = {"scr_printspeed","8"};
 cvar_t bgmvolume = {"bgmvolume", "1", true};
 cvar_t volume = {"volume", "0.7", true};

 cvar_t nosound = {"nosound", "0"};
 cvar_t precache = {"precache", "1"};
 cvar_t loadas8bit = {"loadas8bit", "0"};
 cvar_t bgmbuffer = {"bgmbuffer", "4096"};
 cvar_t ambient_level = {"ambient_level", "0.3"};
 cvar_t ambient_fade = {"ambient_fade", "100"};
 cvar_t snd_noextraupdate = {"snd_noextraupdate", "0"};
 cvar_t snd_show = {"snd_show", "0"};
 cvar_t _snd_mixahead = {"_snd_mixahead", "0.1", true}
 cvar_t	sv_friction = {"sv_friction","4",false,true};
 cvar_t	sv_stopspeed = {"sv_stopspeed","100"};
 cvar_t	sv_gravity = {"sv_gravity","800",false,true};
 cvar_t	sv_maxvelocity = {"sv_maxvelocity","2000"};
 cvar_t	sv_nostep = {"sv_nostep","0"};
 cvar_t	sv_edgefriction = {"edgefriction", "2"};
 cvar_t	sv_idealpitchscale = {"sv_idealpitchscale","0.8"};
 cvar_t	sv_maxspeed = {"sv_maxspeed", "320", false, true};
 cvar_t	sv_accelerate = {"sv_accelerate", "10"};
 cvar_t  sys_linerefresh = {"sys_linerefresh","0"};// set for entity display
 cvar_t  sys_nostdout = {"sys_nostdout","0"};
 cvar_t		lcd_x = {"lcd_x","0"};
 cvar_t		lcd_yaw = {"lcd_yaw","0"};

 cvar_t	scr_ofsx = {"scr_ofsx","0", false};
 cvar_t	scr_ofsy = {"scr_ofsy","0", false};
 cvar_t	scr_ofsz = {"scr_ofsz","0", false};

 cvar_t	cl_rollspeed = {"cl_rollspeed", "200"};
 cvar_t	cl_rollangle = {"cl_rollangle", "2.0"};

 cvar_t	cl_bob = {"cl_bob","0.02", false};
 cvar_t	cl_bobcycle = {"cl_bobcycle","0.6", false};
 cvar_t	cl_bobup = {"cl_bobup","0.5", false};

 cvar_t	v_kicktime = {"v_kicktime", "0.5", false};
 cvar_t	v_kickroll = {"v_kickroll", "0.6", false};
 cvar_t	v_kickpitch = {"v_kickpitch", "0.6", false};

 cvar_t	v_iyaw_cycle = {"v_iyaw_cycle", "2", false};
 cvar_t	v_iroll_cycle = {"v_iroll_cycle", "0.5", false};
 cvar_t	v_ipitch_cycle = {"v_ipitch_cycle", "1", false};
 cvar_t	v_iyaw_level = {"v_iyaw_level", "0.3", false};
 cvar_t	v_iroll_level = {"v_iroll_level", "0.1", false};
 cvar_t	v_ipitch_level = {"v_ipitch_level", "0.3", false};

 cvar_t	v_idlescale = {"v_idlescale", "0", false};

 cvar_t	crosshair = {"crosshair", "0", true};
 cvar_t	cl_crossx = {"cl_crossx", "0", false};
 cvar_t	cl_crossy = {"cl_crossy", "0", false};

 //cvar_t	gl_cshiftpercent = {"gl_cshiftpercent", "100", false};
 */
// VARIABLE DECLARATION
CVARDECL(v_centermove, "0.15", false, false, CV_FLOAT);
CVARDECL(v_centerspeed, "500", false, false, CV_SHORT);

CVARDECLDIFF(v_gamma, "gamma", "1", true, false, CV_FLOAT);

CVARDECL(con_notifytime, "3", false, false, CV_BYTE);		//seconds

#if HAS_MULTIPLAYER
CVARDECL(cl_name, "player", true, false, CV_STRING);
#endif
CVARDECL(cl_color, "0", true, false, CV_BYTE);

CVARDECL(showfps, "0", false, false, CV_BYTE);

//CVARDECL(cl_shownet, "0", false, false, CV_BYTE);	// can be 0, 1, or 2
CVARDECL(cl_nolerp, "0", false, false, CV_BYTE);

CVARDECL(lookspring, "0", true, false, CV_BYTE);
CVARDECL(lookstrafe, "0", true, false, CV_BYTE);
CVARDECL(sensitivity, "3", true, false, CV_FLOAT);

CVARDECL(m_pitch, "0.022", true, false, CV_FLOAT);
CVARDECL(m_yaw, "0.022", true, false, CV_FLOAT);
CVARDECL(m_forward, "1", true, false, CV_FLOAT);
CVARDECL(m_side, "0.8", true, false, CV_FLOAT);

CVARDECL(chase_back, "100", false, false, CV_SHORT);
CVARDECL(chase_up, "16", false, false, CV_SHORT);
CVARDECL(chase_right, "0", false, false, CV_SHORT);
CVARDECL(chase_active, "0", false, false, CV_SHORT);
CVARDECL(cl_upspeed, "200", false, false, CV_SHORT);
CVARDECL(cl_forwardspeed, "200", true, false, CV_SHORT);
CVARDECL(cl_backspeed, "200", true, false, CV_SHORT);
CVARDECL(cl_sidespeed, "350", false, false, CV_SHORT);
CVARDECL(cl_movespeedkey, "2.0", false, false, CV_FLOAT);
CVARDECL(cl_yawspeed, "140", false, false, CV_SHORT);
CVARDECL(cl_pitchspeed, "150", false, false, CV_SHORT);
CVARDECL(cl_anglespeedkey, "1.5", false, false, CV_FLOAT);
CVARDECL(registered, "0", false, false, CV_BYTE);
#if WIN32
CVARDECL(cmdline, "0", false, true, CV_BYTE);
#endif
//CVARDECL(d_subdiv16, "1", false, false, CV_BYTE);
//CVARDECL(d_mipcap, "0", false, false, CV_BYTE);
CVARDECL(d_mipscale, "1", false, false, CV_FLOAT);
CVARDECL(host_framerate, "0", false, false, CV_BYTE);	// set for slow motion
#if WIN32
CVARDECL(host_speeds, "0", false, false, CV_BYTE);			// set for running times
#endif
CVARDECL(sys_ticrate, "0.05", false, false, CV_FLOAT);
#if 0
CVARDECL(serverprofile, "0", false, false, CV_BYTE);

CVARDECL(fraglimit, "0", false, true, CV_BYTE);
CVARDECL(timelimit, "0", false, true, CV_BYTE);
CVARDECL(teamplay, "0", false, true, CV_BYTE);
#endif
CVARDECL(samelevel, "0", false, false, CV_BYTE);
CVARDECL(noexit, "0", false, true, CV_BYTE);

#ifdef QUAKE2
CVARDECL(	developer ,"1", false, false,);	// should be 0 for release!
#elif WIN32
CVARDECL(developer, "0", false, false, CV_BYTE);
#endif

CVARDECL(skill, "1", false, false, CV_BYTE);						// 0 - 3
#if HAS_MULTIPLAYER
CVARDECL(deathmatch, "0", false, false, CV_BYTE);			// 0, 1, or 2
CVARDECL(coop, "0", false, false, CV_BYTE);			// 0 or 1
#endif
CVARDECL(pausable, "1", false, false, CV_BYTE);

CVARDECL(temp1, "0", false, false, CV_BYTE);
#if HAS_MULTIPLAYER
CVARDECL(net_messagetimeout, "300", false, false, CV_SHORT);
#endif
CVARDECL(hostname, "UNNAMED", false, false, CV_STRING);

#ifdef IDGODS
CVARDECL(	idgods , "0");
#endif
CVARDECL(sv_aim, "0.93", false, false, CV_FLOAT);
//CVARDECL(nomonsters, "0", false, false, CV_BYTE);
CVARDECL(gamecfg, "0", false, false, CV_BYTE);
CVARDECL(scratch1, "0", false, false, CV_HALT);
CVARDECL(scratch2, "0", false, false, CV_HALT);
CVARDECL(scratch3, "0", false, false, CV_HALT);
CVARDECL(scratch4, "0", false, false, CV_HALT);
CVARDECL(savedgamecfg, "0", true, false, CV_BYTE);
CVARDECL(saved1, "0", true, false, CV_BYTE);
CVARDECL(saved2, "0", true, false, CV_BYTE);
CVARDECL(saved3, "0", true, false, CV_BYTE);
CVARDECL(saved4, "0", true, false, CV_BYTE);
CVARDECL(r_draworder, "0", false, false, CV_BYTE);
CVARDECL(r_speeds, "0", false, false, CV_BYTE);
CVARDECL(r_timegraph, "0", false, false, CV_BYTE);
CVARDECL(r_graphheight, "10", false, false, CV_BYTE);
CVARDECL(r_clearcolor, "2", false, false, CV_BYTE);
CVARDECL(r_waterwarp, "1", false, false, CV_BYTE);
CVARDECL(r_fullbright, "0", false, false, CV_BYTE);
CVARDECL(r_drawentities, "1", false, false, CV_BYTE);
CVARDECL(r_drawviewmodel, "1", false, false, CV_BYTE);
CVARDECL(r_aliasstats, "0", false, false, CV_BYTE);
#if WIN32
CVARDECL(r_dspeeds, "0", false, false, CV_BYTE);
#endif
//CVARDECL(r_drawflat, "0", false, false, CV_BYTE);
CVARDECL(r_ambient, "0", false, false, CV_BYTE);
CVARDECL(r_reportsurfout, "0", false, false, CV_BYTE);
CVARDECL(r_maxsurfs, "0", false, false, CV_SHORT);
CVARDECL(r_numsurfs, "0", false, false, CV_SHORT);
CVARDECL(r_reportedgeout, "0", false, false, CV_BYTE);
CVARDECL(r_maxedges, "0", false, false, CV_SHORT);
CVARDECL(r_numedges, "0", false, false, CV_SHORT);
CVARDECL(r_aliastransbase, "200", false, false, CV_SHORT);
CVARDECL(r_aliastransadj, "100", false, false, CV_SHORT);
CVARDECL(viewsize, "100", true, false, CV_BYTE);
CVARDECL(fov, "90", false, false, CV_BYTE);	// 10 - 170
CVARDECL(scr_conspeed, "300", false, false, CV_SHORT);
CVARDECL(scr_centertime, "2", false, false, CV_BYTE);
//CVARDECL(showram, "0", false, false, CV_BYTE);
//CVARDECL(showturtle, "0", false, false, CV_BYTE);
CVARDECL(showpause, "1", false, false, CV_BYTE);
CVARDECL(scr_printspeed, "8", false, false, CV_BYTE);
CVARDECL(bgmvolume, "1", true, false, CV_FLOAT);
CVARDECL(volume, "0.7", true, false, CV_FLOAT);

CVARDECL(nosound, "0", false, false, CV_BYTE);
//CVARDECL(precache, "1", false, false, CV_BYTE);
//CVARDECL(loadas8bit, "0", false, false, CV_BYTE);
//CVARDECL(bgmbuffer, "4096", false, false, CV_SHORT);
CVARDECL(ambient_level, "0.3", false, false, CV_FLOAT);
CVARDECL(ambient_fade, "100", false, false, CV_BYTE);
CVARDECL(snd_noextraupdate, "0", false, false, CV_BYTE);
CVARDECL(snd_show, "0", false, false, CV_BYTE);
CVARDECL(_snd_mixahead, "0.1", true, false, CV_FLOAT);
CVARDECL(sv_friction, "4", false, true, CV_FLOAT);
CVARDECL(sv_stopspeed, "100", false, false, CV_SHORT);
CVARDECL(sv_gravity, "800", false, true, CV_SHORT);
CVARDECL(sv_maxvelocity, "2000", false, false, CV_SHORT);
CVARDECL(sv_nostep, "0", false, false, CV_BYTE);
CVARDECL(edgefriction, "2", false, false, CV_FLOAT);
CVARDECL(sv_idealpitchscale, "0.8", false, false, CV_FLOAT);
CVARDECL(sv_maxspeed, "320", false, true, CV_SHORT);
CVARDECL(sv_accelerate, "10", false, false, CV_BYTE);
CVARDECL(sys_linerefresh, "0", false, false, CV_BYTE);	// set for entity display
//CVARDECL(sys_nostdout, "0", false, false, CV_BYTE);
#if LCD_X
CVARDECL(lcd_x, "0", false, false, CV_SHORT);
CVARDECL(lcd_yaw, "0", false, false, CV_SHORT);
#endif
CVARDECL(scr_ofsx, "0", false, false, CV_BYTE);
CVARDECL(scr_ofsy, "0", false, false, CV_BYTE);
CVARDECL(scr_ofsz, "0", false, false, CV_BYTE);

CVARDECL(cl_rollspeed, "200", false, false, CV_SHORT);
CVARDECL(cl_rollangle, "2.0", false, false, CV_FLOAT);

CVARDECL(cl_bob, "0.02", false, false, CV_FLOAT);
CVARDECL(cl_bobcycle, "0.6", false, false, CV_FLOAT);
CVARDECL(cl_bobup, "0.5", false, false, CV_FLOAT);

CVARDECL(v_kicktime, "0.5", false, false, CV_FLOAT);
CVARDECL(v_kickroll, "0.6", false, false, CV_FLOAT);
CVARDECL(v_kickpitch, "0.6", false, false, CV_FLOAT);

CVARDECL(v_iyaw_cycle, "2", false, false, CV_FLOAT);
CVARDECL(v_iroll_cycle, "0.5", false, false, CV_FLOAT);
CVARDECL(v_ipitch_cycle, "1", false, false, CV_FLOAT);
CVARDECL(v_iyaw_level, "0.3", false, false, CV_FLOAT);
CVARDECL(v_iroll_level, "0.1", false, false, CV_FLOAT);
CVARDECL(v_ipitch_level, "0.3", false, false, CV_FLOAT);

CVARDECL(v_idlescale, "0", false, false, CV_BYTE);

CVARDECL(crosshair, "0", true, false, CV_BYTE);
CVARDECL(cl_crossx, "0", false, false, CV_SHORT);
CVARDECL(cl_crossy, "0", false, false, CV_BYTE);

// CVARS DEFINITON

const cvar_t cvar_vars[] =
{
    CVARDEF(v_centermove, "0.15", false, false, CV_FLOAT),
    CVARDEF(v_centerspeed,"500", false, false, CV_SHORT),

    CVARDEFDIFF(v_gamma, "gamma", "0.4", true, false, CV_FLOAT),

    CVARDEF(con_notifytime,"3", false, false, CV_BYTE),		//seconds
#if HAS_MULTIPLAYER
    CVARDEF(cl_name, "player", true, false, CV_STRING),
#endif
    CVARDEF(cl_color, "0", true, false, CV_BYTE),

    CVARDEF(showfps, "0", false, false, CV_BYTE),

    //CVARDEF(cl_shownet,"0", false, false, CV_BYTE),	// can be 0, 1, or 2
    CVARDEF(cl_nolerp,"0", false, false, CV_BYTE),

    CVARDEF(lookspring,"0", true, false, CV_BYTE),
    CVARDEF(lookstrafe,"0", true, false, CV_BYTE),
    CVARDEF(sensitivity,"3", true, false, CV_FLOAT),

    CVARDEF(m_pitch,"0.022", true, false, CV_FLOAT),
    CVARDEF(m_yaw, "0.022", true, false, CV_FLOAT),
    CVARDEF(m_forward,"1", true, false, CV_FLOAT),
    CVARDEF(m_side,"0.8", true, false, CV_FLOAT),
    CVARDEF( chase_back, "100", false, false, CV_SHORT),
    CVARDEF( chase_up, "16", false, false, CV_SHORT),
    CVARDEF( chase_right, "0", false, false, CV_SHORT),
    CVARDEF( chase_active, "0", false, false, CV_SHORT),
    CVARDEF( cl_upspeed,"200", false, false, CV_SHORT),
    CVARDEF( cl_forwardspeed ,"200", true, false, CV_SHORT),
    CVARDEF( cl_backspeed ,"200", true, false, CV_SHORT),
    CVARDEF( cl_sidespeed ,"350", false, false, CV_SHORT),
    CVARDEF( cl_movespeedkey ,"2.0", false, false, CV_FLOAT),
    CVARDEF( cl_yawspeed ,"140", false, false, CV_SHORT),
    CVARDEF( cl_pitchspeed ,"150", false, false, CV_SHORT),
    CVARDEF( cl_anglespeedkey ,"1.5", false, false, CV_FLOAT),
    CVARDEF( registered ,"0", false, false, CV_BYTE),
#if WIN32
    CVARDEF( cmdline ,"0", false, true, CV_BYTE),
#endif
    //CVARDEF( d_subdiv16 , "1", false, false, CV_BYTE),
    //CVARDEF( d_mipcap , "0", false, false, CV_BYTE),
    CVARDEF( d_mipscale , "1", false, false, CV_FLOAT),
    CVARDEF( host_framerate ,"0", false, false, CV_BYTE),	// set for slow motion
#if WIN32
    CVARDEF( host_speeds ,"0", false, false, CV_BYTE),			// set for running times
#endif
    CVARDEF( sys_ticrate ,"0.05", false, false, CV_FLOAT),

//    CVARDEF( serverprofile ,"0", false, false, CV_BYTE),
#if 0
    CVARDEF( fraglimit ,"0",false,true, CV_BYTE),
    CVARDEF( timelimit ,"0",false,true, CV_BYTE),
    CVARDEF( teamplay ,"0",false,true, CV_BYTE),
#endif
    CVARDEF( samelevel ,"0", false, false, CV_BYTE),
    CVARDEF( noexit ,"0",false,true, CV_BYTE),

#ifdef QUAKE2
    CVARDEF( developer ,"1", false, false,),	// should be 0 for release!
#elif WIN32
    CVARDEF( developer ,"0", false, false, CV_BYTE),
#endif

    CVARDEF( skill ,"1", false, false, CV_BYTE),						// 0 - 3
#if HAS_MULTIPLAYER
    CVARDEF( deathmatch ,"0", false, false, CV_BYTE),			// 0, 1, or 2
    CVARDEF( coop ,"0", false, false, CV_BYTE),			// 0 or 1
#endif
    CVARDEF( pausable ,"1", false, false, CV_BYTE),

    CVARDEF( temp1 ,"0", false, false, CV_BYTE),
#if HAS_MULTIPLAYER
    CVARDEF( net_messagetimeout ,"300", false, false, CV_SHORT),
#endif
    CVARDEF( hostname , "UNNAMED", false, false, CV_STRING),

#ifdef IDGODS
    CVARDEF( idgods , "0"),
#endif
    CVARDEF( sv_aim , "0.93", false, false, CV_FLOAT),
#if 0
    CVARDEF( nomonsters , "0", false, false, CV_BYTE),
#endif
    CVARDEF( gamecfg , "0", false, false, CV_BYTE),
    CVARDEF( scratch1 , "0", false, false, CV_HALT),
    CVARDEF( scratch2 , "0", false, false, CV_HALT),
    CVARDEF( scratch3 , "0", false, false, CV_HALT),
    CVARDEF( scratch4 , "0", false, false, CV_HALT),
    CVARDEF( savedgamecfg , "0", true, false, CV_BYTE),
    CVARDEF( saved1 , "0", true, false, CV_BYTE),
    CVARDEF( saved2 , "0", true, false, CV_BYTE),
    CVARDEF( saved3 , "0", true, false, CV_BYTE),
    CVARDEF( saved4 , "0", true, false, CV_BYTE),
#if WIN32
    CVARDEF( r_draworder ,"0", false, false, CV_BYTE),
    CVARDEF( r_speeds ,"0", false, false, CV_BYTE),
    CVARDEF( r_timegraph ,"0", false, false, CV_BYTE),
    CVARDEF( r_graphheight ,"10", false, false, CV_BYTE),
#endif
    CVARDEF( r_clearcolor ,"2", false, false, CV_BYTE),
    CVARDEF( r_waterwarp ,"1", false, false, CV_BYTE),
    CVARDEF( r_fullbright ,"0", false, false, CV_BYTE),
    CVARDEF( r_drawentities ,"1", false, false, CV_BYTE),
    CVARDEF( r_drawviewmodel ,"1", false, false, CV_BYTE),
    CVARDEF( r_aliasstats ,"0", false, false, CV_BYTE),
#if WIN32
    CVARDEF( r_dspeeds ,"0", false, false, CV_BYTE),
#endif
//    CVARDEF( r_drawflat , "0", false, false, CV_BYTE),
    CVARDEF( r_ambient , "0", false, false, CV_BYTE),
    CVARDEF( r_reportsurfout , "0", false, false, CV_BYTE),
    CVARDEF( r_maxsurfs , "0", false, false, CV_SHORT),
    CVARDEF( r_numsurfs , "0", false, false, CV_SHORT),
    CVARDEF( r_reportedgeout , "0", false, false, CV_BYTE),
    CVARDEF( r_maxedges , "0", false, false, CV_SHORT),
    CVARDEF( r_numedges , "0", false, false, CV_SHORT),
    CVARDEF( r_aliastransbase , "200", false, false, CV_SHORT),
    CVARDEF( r_aliastransadj , "100", false, false, CV_SHORT),
    CVARDEF( viewsize ,"100", true, false, CV_BYTE),
    CVARDEF( fov ,"90", false, false, CV_BYTE),	// 10 - 170
    CVARDEF( scr_conspeed ,"300", false, false, CV_SHORT),
    CVARDEF( scr_centertime, "2", false, false, CV_BYTE),
  //  CVARDEF( showram ,"0", false, false, CV_BYTE),
  //  CVARDEF( showturtle ,"0", false, false, CV_BYTE),
    CVARDEF( showpause ,"1", false, false, CV_BYTE),
    CVARDEF( scr_printspeed ,"8", false, false, CV_BYTE),
    CVARDEF( bgmvolume , "1", true, false, CV_FLOAT),
    CVARDEF( volume , "1", true, false, CV_FLOAT),

    CVARDEF( nosound , "0", false, false, CV_BYTE),
//    CVARDEF( precache , "1", false, false, CV_BYTE),
  //  CVARDEF( loadas8bit , "0", false, false, CV_BYTE),
  //  CVARDEF( bgmbuffer , "4096", false, false, CV_SHORT),
    CVARDEF( ambient_level , "0.3", false, false, CV_FLOAT),
    CVARDEF( ambient_fade , "100", false, false,CV_BYTE),
    CVARDEF( snd_noextraupdate , "0", false, false, CV_BYTE),
 //   CVARDEF( snd_show , "0", false, false, CV_BYTE),
    CVARDEF( _snd_mixahead , "0.1", true, false, CV_FLOAT),
    CVARDEF( sv_friction ,"4",false,true, CV_FLOAT),
    CVARDEF( sv_stopspeed ,"100", false, false, CV_SHORT),
    CVARDEF( sv_gravity ,"800",false,true, CV_SHORT),
    CVARDEF( sv_maxvelocity ,"2000", false, false,CV_SHORT),
    CVARDEF( sv_nostep ,"0", false, false,CV_BYTE),
    CVARDEF( edgefriction , "2", false, false,CV_FLOAT),
    CVARDEF( sv_idealpitchscale ,"0.8", false, false,CV_FLOAT),
    CVARDEF( sv_maxspeed , "320", false, true, CV_SHORT),
    CVARDEF( sv_accelerate , "10", false, false, CV_BYTE),
    CVARDEF( sys_linerefresh ,"0", false, false, CV_BYTE),	// set for entity display
//    CVARDEF( sys_nostdout ,"0", false, false, CV_BYTE),
#if LCD_X
    CVARDEF( lcd_x ,"0", false, false, CV_SHORT),
    CVARDEF( lcd_yaw ,"0", false, false, CV_SHORT),
#endif

    CVARDEF( scr_ofsx ,"0", false, false,CV_BYTE),
    CVARDEF( scr_ofsy ,"0", false, false, CV_BYTE),
    CVARDEF( scr_ofsz ,"0", false, false,CV_BYTE),

    CVARDEF( cl_rollspeed , "200", false, false, CV_SHORT),
    CVARDEF( cl_rollangle , "2.0", false, false, CV_FLOAT),

    CVARDEF( cl_bob ,"0.02", false, false, CV_FLOAT),
    CVARDEF( cl_bobcycle ,"0.6", false, false, CV_FLOAT),
    CVARDEF( cl_bobup ,"0.5", false, false, CV_FLOAT),

    CVARDEF( v_kicktime , "0.5", false, false, CV_FLOAT),
    CVARDEF( v_kickroll , "0.6", false, false, CV_FLOAT),
    CVARDEF( v_kickpitch , "0.6", false, false, CV_FLOAT),

    CVARDEF( v_iyaw_cycle , "2", false, false, CV_FLOAT),
    CVARDEF( v_iroll_cycle , "0.5", false, false, CV_FLOAT),
    CVARDEF( v_ipitch_cycle , "1", false, false, CV_FLOAT),
    CVARDEF( v_iyaw_level , "0.3", false, false, CV_FLOAT),
    CVARDEF( v_iroll_level , "0.1", false, false, CV_FLOAT),
    CVARDEF( v_ipitch_level , "0.3", false, false, CV_FLOAT),

    CVARDEF( v_idlescale , "0", false, false, CV_BYTE),

    CVARDEF( crosshair , "0", true, false, CV_BYTE),
    CVARDEF( cl_crossx , "0", false, false, CV_SHORT),
    CVARDEF( cl_crossy , "0", false, false, CV_BYTE),
    }
;
const char *cvar_null_string = "";

/*
 ============
 Cvar_FindVar
 ============
 */
const cvar_t* Cvar_FindVar(const char *var_name)
{
    const cvar_t *var;
    unsigned int i;
    for (i = 0, var = &cvar_vars[i]; i < sizeof(cvar_vars) / sizeof(cvar_vars[0]); i++, var = &cvar_vars[i])
        if (!Q_strcmp(var_name, var->name))
            return var;

    return NULL;
}

float Cvar_VariableValueForVar(const cvar_t *var)
{
    byte byteValue;
    short shortValue;
    int intValue;
    switch (var->type)
    {
        case EN_CV_BYTE:
            byteValue = *((byte*) var->pvalue);
            return byteValue;
        case EN_CV_SHORT:
            shortValue = *((short*) var->pvalue);
            return shortValue;
        case EN_CV_INT:
            intValue = *((int*) var->pvalue);
            return intValue;
        case EN_CV_FLOAT:
            return *((float*) var->pvalue);
        default:
            return Q_atof(var->string);
    }

}
/*
 ============
 Cvar_VariableValue
 ============
 */
float Cvar_VariableValue(const char *var_name)
{
    const cvar_t *var;

    var = Cvar_FindVar(var_name);
    if (!var)
        return 0;
    return Cvar_VariableValueForVar(var);
}

/*
 ============
 Cvar_VariableString
 ============
 */
const char* Cvar_VariableString(const char *var_name)
{
    const cvar_t *var;

    var = Cvar_FindVar(var_name);
    if (!var)
        return cvar_null_string;
    return var->string;
}

/*
 ============
 Cvar_CompleteVariable
 ============
 */
const char* Cvar_CompleteVariable(const char *partial)
{
    const cvar_t *cvar;
    int len;

    len = Q_strlen(partial);

    if (!len)
        return NULL;

// check functions
    unsigned int i;
    for (i = 0, cvar = &cvar_vars[i]; i < sizeof(cvar_vars) / sizeof(cvar_vars[0]); i++, cvar = &cvar_vars[i])
        if (!Q_strncmp(partial, cvar->name, len))
            return (char*) cvar->name;

    return NULL;
}

/*
 ============
 Cvar_Set
 ============
 */
qboolean Cvar_SetFromRef(const cvar_t *var, const char *value, int crash, int forceInit)
{
    qboolean changed = false;
    float oldvalue;
    float newvalue;
    if (forceInit)
        newvalue = Q_atof(var->string);
    else
        newvalue = Q_atof(value);
    switch (var->type)
    {
        case EN_CV_BYTE:
            oldvalue = *((byte*) var->pvalue);
            *((byte*) var->pvalue) = newvalue;
            changed = oldvalue != newvalue;

            break;
        case EN_CV_SHORT:
            oldvalue = *((short*) var->pvalue);
            *((short*) var->pvalue) = newvalue;
            changed = oldvalue != newvalue;
            break;
        case EN_CV_INT:
            oldvalue = *((int*) var->pvalue);
            *((int*) var->pvalue) = newvalue;
            changed = oldvalue != newvalue;
            break;
        case EN_CV_FLOAT:
            oldvalue = *((float*) var->pvalue);
            *((float*) var->pvalue) = newvalue;
            changed = oldvalue != newvalue;
            break;
        case EN_CV_STRING:
            // we are not changing
            if (crash)
                while (1)
                    FIXME("Changing string");
            else
                *((char**) var->pvalue) = (char*) var->string;
            break;

        case EN_CV_HALT:
            while (crash)
            {
                printf("var is %s \r\n", var->name);
                FIXME("Changing halt type cvar");
            }

            break;
    }

    return changed;
}
void Cvar_Set(const char *var_name, const char *value)
{
    const cvar_t *var;
    qboolean changed;

    var = Cvar_FindVar(var_name);
    if (!var)
    {	// there is an error in C code if this happens
        Con_Printf("Cvar_Set: variable %s not found\n", var_name);
        return;
    }
#if USE_ORIGINAL_CVAR
	changed = Q_strcmp(var->string, value);

	Z_Free (var->string);	// free the old value string

	var->string = Z_Malloc (Q_strlen(value)+1);
	Q_strcpy (var->string, value);
	var->value = Q_atof (var->string);
#else
    changed = Cvar_SetFromRef(var, value, 1, 0);

#endif
    if (var->server && changed)
    {
        if (sv.active)
            SV_BroadcastPrintf("\"%s\" changed to \"%s\"\n", var->name, value);
    }
}
char* floatToString(char *string, int len, float value)
{
    int negative;
    int i_mvalue;
    // we don't have %f. So let's print something like d.03d
    if (value < 0)
    {
        negative = 1;
        i_mvalue = -1000 * value;
    }
    else
    {
        negative = 0;
        i_mvalue = 1000 * value;
    }
    snprintf(string, len, "%s%d.%03d", negative ? "-" : "", i_mvalue / 1000, i_mvalue % 1000);
    return string;
}
/*
 ============
 Cvar_SetValue
 ============
 */
void Cvar_SetValue(const char *var_name, float value)
{
    // todo: optimize this crap as we don't want to have to convert from float to string back to float!
    char val[32];
    floatToString(val, sizeof(val), value);
    //
    Cvar_Set(var_name, val);
}

/*
 ============
 Cvar_RegisterVariable

 Adds a freestanding variable to the variable list.
 ============
 */
#if USE_ORIGINAL_CVAR
void Cvar_RegisterVariable (cvar_t *variable)
{
    printf("CVar Register variable %s\r\n", variable->name);
	char	*oldstr;

// first check to see if it has allready been defined
	if (Cvar_FindVar (variable->name))
	{
		Con_Printf ("Can't register variable %s, already defined\n", variable->name);
		return;
	}

// check for overlap with a command
	if (Cmd_Exists (variable->name))
	{
		Con_Printf ("Cvar_RegisterVariable: %s is a command\n", variable->name);
		return;
	}

// copy the value off, because future sets will Z_Free it
	oldstr = variable->string;
	variable->string = Z_Malloc (Q_strlen(variable->string)+1);
	Q_strcpy (variable->string, oldstr);
	variable->value = Q_atof (variable->string);

// link the variable in
	variable->next = cvar_vars;
	cvar_vars = variable;
}
#endif
/*
 ============
 Cvar_Command

 Handles variable inspection and changing from the console
 ============
 */
qboolean Cvar_Command(void)
{
    const cvar_t *v;

// check variables
    v = Cvar_FindVar(Cmd_Argv(0));
    if (!v)
        return false;

// perform a variable print or set
    if (Cmd_Argc() == 1)
    {
        Con_Printf("\"%s\" defaults to \"%s\", current value is %f\n", v->name, v->string, Cvar_VariableValue(Cmd_Argv(0)));
        return true;
    }

    Cvar_Set(v->name, Cmd_Argv(1));
    return true;
}

/*
 ============
 Cvar_WriteVariables

 Writes lines containing "set variable value" for all variables
 with the archive flag set to true.
 ============
 */

void Cvar_WriteVariables(byte **pos)
{

#if 0

	cvar_t	*var;

	for (var = cvar_vars ; var ; var = var->next)
		if (var->archive)
			fprintf (f, "%s \"%s\"\n", var->name, var->string);
#endif
    const cvar_t *var;
    unsigned int i;
    // next-hack: we put here only numeric values, because strings can't be changed
    for (i = 0, var = &cvar_vars[i]; i < sizeof(cvar_vars) / sizeof(cvar_vars[0]); i++, var = &cvar_vars[i])
    {
        if (var->type == EN_CV_STRING)
            continue;   // we can't change strings.
        if (!var->archive)
            continue;
        char variableBuffer[256 + 1];
        int written;
        char val[32];

        floatToString(val, sizeof(val), Cvar_VariableValueForVar(var));
        written = snprintf(variableBuffer, sizeof(variableBuffer), "%s %s\n", var->name, val);
        //  extMemory can only write in block of 4 bytes. Luckily adding spaces is not an issue.
        if (written <= 0)
        {
#if WIN32
            FIXME("SOMETHING NEEDS YOUR ATTENTION!");
#endif // WIN32
            return;         // stop if something happened.

        }
        unsigned int nextWritten = (written + 3) & ~3;
        for (unsigned int j = written; j < nextWritten; j++)
        {
            variableBuffer[j] = ' ';
        }
        extMemProgram((uint32_t) *pos, (uint8_t*) variableBuffer, nextWritten);
        *pos = *pos + nextWritten;
    }
}
void Cvar_Init(void)
{
    for (unsigned int i = 0; i < sizeof(cvar_vars) / sizeof(cvar_vars[0]); i++)
        Cvar_SetFromRef(&cvar_vars[i], cvar_vars[i].string, 0, true);

}

