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

// cvar.h
/*

 cvar_t variables are used to hold scalar or string variables that can be changed or displayed at the console or prog code as well as accessed directly
 in C code.

 it is sufficient to initialize a cvar_t with just the first two fields, or
 you can add a ,true flag for variables that you want saved to the configuration
 file when the game is quit:

 cvar_t	r_draworder = {"r_draworder","1"};
 cvar_t	scr_screensize = {"screensize","1",true};

 Cvars must be registered before use, or they will have a 0 value instead of the float interpretation of the string.  Generally, all cvar_t declarations should be registered in the apropriate init function before any console commands are executed:
 Cvar_RegisterVariable (&host_framerate);


 C code usually just references a cvar in place:
 if ( r_draworder )

 It could optionally ask for the value to be looked up for a string name:
 if (Cvar_VariableValue ("r_draworder"))

 Interpreted prog code can access cvars with the cvar(name) or
 cvar_set (name, value) internal functions:
 teamplay = cvar("teamplay");
 cvar_set ("registered", "1");

 The user can access cvars from the console in two ways:
 r_draworder			prints the current value
 r_draworder 0		sets the current value to 0
 Cvars are restricted from having the same names as commands to keep this
 interface from being ambiguous.
 */
#define USE_ORIGINAL_CVAR 0
#if USE_ORIGINAL_CVAR
typedef struct cvar_s
{
	char	*name;
	char	*string;
	qboolean archive;		// set to true to cause it to be saved to vars.rc
	qboolean server;		// notifies players when changed
	float	value;
	struct cvar_s *next;
} cvar_t;
#else
#define TYPE_CV_BYTE byte
#define TYPE_CV_SHORT short
#define TYPE_CV_FLOAT float
#define TYPE_CV_INT    int
#define TYPE_CV_STRING char *
#define TYPE_CV_HALT float

typedef enum
{
    EN_CV_BYTE = 0, EN_CV_SHORT, EN_CV_INT, EN_CV_FLOAT, EN_CV_STRING, EN_CV_HALT,
} cvar_type;
#define CVARDEF(varName, initialValue, save, notify, varType) {.name = #varName, .string = initialValue, .archive = save, .server = notify, .type = EN_##varType, .pvalue = &varName}
#define CVARDECL(varName, initialValue, save, notify, varType) TYPE_##varType varName
#define CVARDECLEXT(varName, initialValue, save, notify, varType) extern TYPE_##varType varName
#define CVARDEFDIFF(varName, stringVarName, initialValue, save, notify, varType) {.name = stringVarName, .string = initialValue, .archive = save, .server = notify, .type = EN_##varType, .pvalue = &varName}
#define CVARDECLDIFF(varName, stringVarName, initialValue, save, notify, varType) TYPE_##varType varName
#define CVARDECLEXTDIFF(varName, stringVarName, initialValue, save, notify, varType) extern TYPE_##varType varName

typedef struct cvar_s
{
    const char *const name;
    const char *const string;
    const uint8_t archive;		// set to true to cause it to be saved to vars.rc
    const uint8_t server;		// notifies players when changed
    const uint8_t type;
    const uint8_t dummy;
    const void *pvalue;
//	struct cvar_s *next;
} cvar_t;
CVARDECLEXT(v_centermove, "0.15", false, false, CV_FLOAT);
CVARDECLEXT(v_centerspeed, "500", false, false, CV_SHORT);

CVARDECLEXTDIFF(v_gamma, "gamma", "1", true, false, CV_FLOAT);

CVARDECLEXT(con_notifytime, "3", false, false, CV_BYTE);		//seconds
#if HAS_MULTIPLAYER
CVARDECLEXT(cl_name, "player", true, false, CV_STRING);
#else
#define cl_name "player"
#endif
CVARDECLEXT(cl_color, "0", true, false, CV_BYTE);

CVARDECLEXT(showfps, "0", false, false, CV_BYTE);


CVARDECLEXT(cl_shownet, "0", false, false, CV_BYTE);	// can be 0, 1, or 2
CVARDECLEXT(cl_nolerp, "0", false, false, CV_BYTE);

CVARDECLEXT(lookspring, "0", true, false, CV_BYTE);
CVARDECLEXT(lookstrafe, "0", true, false, CV_BYTE);
CVARDECLEXT(sensitivity, "3", true, false, CV_FLOAT);

CVARDECLEXT(m_pitch, "0.022", true, false, CV_FLOAT);
CVARDECLEXT(m_yaw, "0.022", true, false, CV_FLOAT);
CVARDECLEXT(m_forward, "1", true, false, CV_FLOAT);
CVARDECLEXT(m_side, "0.8", true, false, CV_FLOAT);

CVARDECLEXT(chase_back, "100", false, false, CV_SHORT);
CVARDECLEXT(chase_up, "16", false, false, CV_SHORT);
CVARDECLEXT(chase_right, "0", false, false, CV_SHORT);
CVARDECLEXT(chase_active, "0", false, false, CV_SHORT);
CVARDECLEXT(cl_upspeed, "200", false, false, CV_SHORT);
CVARDECLEXT(cl_forwardspeed, "200", true, false, CV_SHORT);
CVARDECLEXT(cl_backspeed, "200", true, false, CV_SHORT);
CVARDECLEXT(cl_sidespeed, "350", false, false, CV_SHORT);
CVARDECLEXT(cl_movespeedkey, "2.0", false, false, CV_FLOAT);
CVARDECLEXT(cl_yawspeed, "140", false, false, CV_SHORT);
CVARDECLEXT(cl_pitchspeed, "150", false, false, CV_SHORT);
CVARDECLEXT(cl_anglespeedkey, "1.5", false, false, CV_FLOAT);
CVARDECLEXT(registered, "0", false, false, CV_BYTE);
CVARDECLEXT(cmdline, "0", false, true, CV_BYTE);
CVARDECLEXT(d_subdiv16, "1", false, false, CV_BYTE);
CVARDECLEXT(d_mipcap, "0", false, false, CV_BYTE);
CVARDECLEXT(d_mipscale, "1", false, false, CV_FLOAT);
CVARDECLEXT(host_framerate, "0", false, false, CV_BYTE);	// set for slow motion
CVARDECLEXT(host_speeds, "0", false, false, CV_BYTE);			// set for running times

CVARDECLEXT(sys_ticrate, "0.05", false, false, CV_FLOAT);
CVARDECLEXT(serverprofile, "0", false, false, CV_BYTE);

CVARDECLEXT(fraglimit, "0", false, true, CV_BYTE);
CVARDECLEXT(timelimit, "0", false, true, CV_BYTE);
#if HAS_MULTIPLAYER
CVARDECLEXT(teamplay, "0", false, true, CV_BYTE);
#else
#define teamplay      0
#endif
CVARDECLEXT(samelevel, "0", false, false, CV_BYTE);
CVARDECLEXT(noexit, "0", false, true, CV_BYTE);

#ifdef QUAKE2
CVARDECLEXT(	developer ,"1", false, false,);	// should be 0 for release!
#else
CVARDECLEXT(developer, "0", false, false, CV_BYTE);
#endif

CVARDECLEXT(skill, "1", false, false, CV_BYTE);						// 0 - 3
#if HAS_MULTIPLAYER
CVARDECLEXT(deathmatch, "0", false, false, CV_BYTE);			// 0, 1, or 2
CVARDECLEXT(coop, "0", false, false, CV_BYTE);			// 0 or 1
#else
#define coop                0
#define deathmatch          0
#endif
CVARDECLEXT(pausable, "1", false, false, CV_BYTE);

CVARDECLEXT(temp1, "0", false, false, CV_BYTE);
CVARDECLEXT(net_messagetimeout, "300", false, false, CV_SHORT);
CVARDECLEXT(hostname, "UNNAMED", false, false, CV_STRING);

#ifdef IDGODS
CVARDECLEXT(	idgods , "0");
#endif
CVARDECLEXT(sv_aim, "0.93", false, false, CV_FLOAT);
CVARDECLEXT(nomonsters, "0", false, false, CV_BYTE);
CVARDECLEXT(gamecfg, "0", false, false, CV_BYTE);
CVARDECLEXT(scratch1, "0", false, false, CV_HALT);
CVARDECLEXT(scratch2, "0", false, false, CV_HALT);
CVARDECLEXT(scratch3, "0", false, false, CV_HALT);
CVARDECLEXT(scratch4, "0", false, false, CV_HALT);
CVARDECLEXT(savedgamecfg, "0", true, false, CV_BYTE);
CVARDECLEXT(saved1, "0", true, false, CV_BYTE);
CVARDECLEXT(saved2, "0", true, false, CV_BYTE);
CVARDECLEXT(saved3, "0", true, false, CV_BYTE);
CVARDECLEXT(saved4, "0", true, false, CV_BYTE);
CVARDECLEXT(r_draworder, "0", false, false, CV_BYTE);
CVARDECLEXT(r_speeds, "0", false, false, CV_BYTE);
CVARDECLEXT(r_timegraph, "0", false, false, CV_BYTE);
CVARDECLEXT(r_graphheight, "10", false, false, CV_BYTE);
CVARDECLEXT(r_clearcolor, "2", false, false, CV_BYTE);
CVARDECLEXT(r_waterwarp, "1", false, false, CV_BYTE);
CVARDECLEXT(r_fullbright, "0", false, false, CV_BYTE);
CVARDECLEXT(r_drawentities, "1", false, false, CV_BYTE);
CVARDECLEXT(r_drawviewmodel, "1", false, false, CV_BYTE);
CVARDECLEXT(r_aliasstats, "0", false, false, CV_BYTE);
CVARDECLEXT(r_dspeeds, "0", false, false, CV_BYTE);
CVARDECLEXT(r_drawflat, "0", false, false, CV_BYTE);
CVARDECLEXT(r_ambient, "0", false, false, CV_BYTE);
CVARDECLEXT(r_reportsurfout, "0", false, false, CV_BYTE);
CVARDECLEXT(r_maxsurfs, "0", false, false, CV_SHORT);
CVARDECLEXT(r_numsurfs, "0", false, false, CV_SHORT);
CVARDECLEXT(r_reportedgeout, "0", false, false, CV_BYTE);
CVARDECLEXT(r_maxedges, "0", false, false, CV_SHORT);
CVARDECLEXT(r_numedges, "0", false, false, CV_SHORT);
CVARDECLEXT(r_aliastransbase, "200", false, false, CV_SHORT);
CVARDECLEXT(r_aliastransadj, "100", false, false, CV_SHORT);
CVARDECLEXT(viewsize, "100", true, false, CV_BYTE);
CVARDECLEXT(fov, "90", false, false, CV_BYTE);	// 10 - 170
CVARDECLEXT(scr_conspeed, "300", false, false, CV_SHORT);
CVARDECLEXT(scr_centertime, "2", false, false, CV_BYTE);
//CVARDECLEXT(showram, "1", false, false, CV_BYTE);
//CVARDECLEXT(showturtle, "0", false, false, CV_BYTE);
#define showram             0
#define showturtle          0
CVARDECLEXT(showpause, "1", false, false, CV_BYTE);
CVARDECLEXT(scr_printspeed, "8", false, false, CV_BYTE);
CVARDECLEXT(bgmvolume, "1", true, false, CV_FLOAT);
CVARDECLEXT(volume, "0.7", true, false, CV_FLOAT);

CVARDECLEXT(nosound, "0", false, false, CV_BYTE);
//CVARDECLEXT(precache, "1", false, false, CV_BYTE);
#define precache            1
CVARDECLEXT(loadas8bit, "0", false, false, CV_BYTE);
CVARDECLEXT(bgmbuffer, "4096", false, false, CV_SHORT);
CVARDECLEXT(ambient_level, "0.3", false, false, CV_FLOAT);
CVARDECLEXT(ambient_fade, "100", false, false, CV_BYTE);
CVARDECLEXT(snd_noextraupdate, "0", false, false, CV_BYTE);
CVARDECLEXT(snd_show, "0", false, false, CV_BYTE);
CVARDECLEXT(_snd_mixahead, "0.1", true, false, CV_FLOAT);
CVARDECLEXT(sv_friction, "4", false, true, CV_FLOAT);
CVARDECLEXT(sv_stopspeed, "100", false, false, CV_SHORT);
CVARDECLEXT(sv_gravity, "800", false, true, CV_SHORT);
CVARDECLEXT(sv_maxvelocity, "2000", false, false, CV_SHORT);
CVARDECLEXT(sv_nostep, "0", false, false, CV_BYTE);
CVARDECLEXT(edgefriction, "2", false, false, CV_FLOAT);
CVARDECLEXT(sv_idealpitchscale, "0.8", false, false, CV_FLOAT);
CVARDECLEXT(sv_maxspeed, "320", false, true, CV_SHORT);
CVARDECLEXT(sv_accelerate, "10", false, false, CV_BYTE);
CVARDECLEXT(sys_linerefresh, "0", false, false, CV_BYTE);	// set for entity display
CVARDECLEXT(sys_nostdout, "0", false, false, CV_BYTE);
CVARDECLEXT(lcd_x, "0", false, false, CV_SHORT);
CVARDECLEXT(lcd_yaw, "0", false, false, CV_SHORT);

CVARDECLEXT(scr_ofsx, "0", false, false, CV_BYTE);
CVARDECLEXT(scr_ofsy, "0", false, false, CV_BYTE);
CVARDECLEXT(scr_ofsz, "0", false, false, CV_BYTE);

CVARDECLEXT(cl_rollspeed, "200", false, false, CV_SHORT);
CVARDECLEXT(cl_rollangle, "2.0", false, false, CV_FLOAT);

CVARDECLEXT(cl_bob, "0.02", false, false, CV_FLOAT);
CVARDECLEXT(cl_bobcycle, "0.6", false, false, CV_FLOAT);
CVARDECLEXT(cl_bobup, "0.5", false, false, CV_FLOAT);

CVARDECLEXT(v_kicktime, "0.5", false, false, CV_FLOAT);
CVARDECLEXT(v_kickroll, "0.6", false, false, CV_FLOAT);
CVARDECLEXT(v_kickpitch, "0.6", false, false, CV_FLOAT);

CVARDECLEXT(v_iyaw_cycle, "2", false, false, CV_FLOAT);
CVARDECLEXT(v_iroll_cycle, "0.5", false, false, CV_FLOAT);
CVARDECLEXT(v_ipitch_cycle, "1", false, false, CV_FLOAT);
CVARDECLEXT(v_iyaw_level, "0.3", false, false, CV_FLOAT);
CVARDECLEXT(v_iroll_level, "0.1", false, false, CV_FLOAT);
CVARDECLEXT(v_ipitch_level, "0.3", false, false, CV_FLOAT);

CVARDECLEXT(v_idlescale, "0", false, false, CV_BYTE);

CVARDECLEXT(crosshair, "0", true, false, CV_BYTE);
CVARDECLEXT(cl_crossx, "0", false, false, CV_SHORT);
CVARDECLEXT(cl_crossy, "0", false, false, CV_BYTE);

#endif

void Cvar_RegisterVariable(cvar_t *variable);
// registers a cvar that already has the name, string, and optionally the
// archive elements set.

void Cvar_Set(const char *var_name, const char *value);
// equivelant to "<name> <variable>" typed at the console

void Cvar_SetValue(const char *var_name, float value);
// expands value to a string and calls Cvar_Set

float Cvar_VariableValue(const char *var_name);
// returns 0 if not defined or non numeric

const char* Cvar_VariableString(const char *var_name);
// returns an empty string if not defined

const char* Cvar_CompleteVariable(const char *partial);
// attempts to match a partial variable name for command line completion
// returns NULL if nothing fits

qboolean Cvar_Command(void);
// called by Cmd_ExecuteString when Cmd_Argv(0) doesn't match a known
// command.  Returns true if the command was a variable reference that
// was handled. (print or change)

void Cvar_WriteVariables(byte **pos);
// Writes lines containing "set variable value" for all variables
// with the archive flag set to true.

const cvar_t* Cvar_FindVar(const char *var_name);
void Cvar_Init(void);
extern const cvar_t cvar_vars[];
