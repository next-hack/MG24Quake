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
// client.h
#if WIN32
#include "extMemoryWin32.h"
#else
#include "extMemory.h"
#endif

typedef struct
{
    vec3_t viewangles;

// intended velocities
    float forwardmove;
    float sidemove;
    float upmove;
#ifdef QUAKE2
	byte	lightlevel;
#endif
} usercmd_t;

typedef struct
{
    uint8_t length;
#if OLD_LIGHTSTYLE
	char map[MAX_STYLESTRING];
#else
    uint8_t map_nibbles[(MAX_STYLESTRING + 1) / 2];
    uint8_t map_topBits[(MAX_STYLESTRING + 7) / 8];
#endif
} lightstyle_t;

typedef struct
{
    char name[MAX_SCOREBOARDNAME];
    float entertime;
    int frags;
    int colors;			// two 4 bit fields
#if HAS_MULTIPLAYER
	byte	translations[VID_GRADES*256];
#endif
} scoreboard_t;

typedef struct
{
    byte destcolor[3];
    short percent;		// 0-256
} cshift_t;

#define	CSHIFT_CONTENTS	0
#define	CSHIFT_DAMAGE	1
#define	CSHIFT_BONUS	2
#define	CSHIFT_POWERUP	3
#define	NUM_CSHIFTS		4

#define	NAME_LENGTH	64

//
// client_state_t should hold all pieces of the client state
//

#define	SIGNONS		4			// signon messages to receive before connected

#define	MAX_DLIGHTS		32
typedef struct
{
    float die;				// stop lighting after this time
#if DLIGHT_HAS_FLOAT_ORIGIN
	vec3_t	origin;
#else
    short iorigin_s[3];   // next-hack: who cares about decimal part in a light... nobody will notice.
#endif
    short key;                  // could be smaller.
    //float	radius;
#if PACK_DLIGHTS
	short radius:14;               // was float but who cares. This is large enough
	short hasMinlight32 :   1;      // if 1 then minlight is 32. This is the only case, beside 0 .
	short hasDecay300 : 1    ;      // if 1, decay is 300. This is the only case, beside 0.
#else
    short radius;               // was float but who cares. This is large enough
    unsigned short minlight :6;      // if 1 then minlight is 32. This is the only case, beside 0 .
    unsigned short decay :12;      // if 1, decay is 300. This is the only case, beside 0.

#endif
//float	decay;				// drop this each second
//float	minlight;			// don't add when contributing less

#ifdef QUAKE2
	qboolean	dark;			// subtracts light instead of adding
#endif
} dlight_t;

#define	MAX_BEAMS	24
typedef struct
{
    short entity; //was int
#if BEAM_HAS_MODEL_POINTER
	struct model_s	*model;
#else
    short model_index;
#endif
    float endtime;
#if BEAM_HAS_FLOAT_COORDS
	vec3_t	start, end;
#else
    short start_s[3], end_s[3];
#endif
} beam_t;

#define	MAX_EFRAGS		16 //640

#define	MAX_MAPSTRING	2048
#define	MAX_DEMOS		4
#define	MAX_DEMONAME	10   // we really don't have to waste bytes! DEMOx.DEM

typedef enum
{
    ca_dedicated, 		// a dedicated server with no ability to start a client
    ca_disconnected, 	// full screen console with no connection
    ca_connected		// valid netcon, talking to a server
} cactive_t;

//
// the client_static_t structure is persistant through an arbitrary number
// of server connections
//
typedef struct
{
    /*cactive_t*/byte state;

// personalization data sent to server
    char mapstring[MAX_QPATH];       // note: this can be very small... exmy or start...
#if HAS_SPAWN_PARAMS
	char		spawnparms[MAX_MAPSTRING];	// to restart a level
#endif
// demo loop control
    int8_t demonum;		// -1 = don't play demos
    char demos[MAX_DEMOS][MAX_DEMONAME];		// when not playing

// demo recording info must be here, because record is started before
// entering a map (and clearing client_state_t)
    short demorecording :1;
    short demoplayback :1;
    short timedemo :1;
    short forcetrack :13;			// -1 = use normal cd track
#if !USE_EXT_MEMORY
    FILE *demofile;
#else
    unsigned int demoPos;
    unsigned char *demoBase;
    unsigned int demoSize;
#endif // USE_EXT_MEMORY
    int td_lastframe;		// to meter out one message a frame
    int td_startframe;		// host_framecount at start
    float td_starttime;		// realtime at second frame of timedemo

// connection information
    byte signon;			// 0 to SIGNONS
    struct qsocket_s *netcon;
    sizebuf_t message;		// writing buffer to send to server
    char *signonreply;
} client_static_t;

//extern client_static_t	cls;

//
// the client_state_t structure is wiped completely at every
// server signon
//
typedef struct
{
    int movemessages;	// since connecting to this server
                        // throw out the first couple, so the player
                        // doesn't accidentally do something the
                        // first frame
    usercmd_t cmd;			// last command sent to the server

// information for local display
    short stats[MAX_CL_STATS];	// health, etc
    int items;			// inventory bit flags
    float item_gettime[32];	// cl.time of acquiring item, for blinking. next-hack: Cannot be reduced:(
    float faceanimtime;	// use anim frame if cl.time < this

    cshift_t cshifts[NUM_CSHIFTS];	// color shifts for damage, powerups
    cshift_t prev_cshifts[NUM_CSHIFTS];	// and content types

// the client maintains its own idea of view angles, which are
// sent to the server each frame.  The server sets punchangle when
// the view is temporarliy offset, and an angle reset commands at the start
// of each level and after teleporting.
    vec3_t mviewangles[2];	// during demo playback viewangles is lerped
                            // between these
    vec3_t viewangles;

    vec3_t mvelocity[2];	// update by server, used for lean+bob
                            // (0 is newest)
    vec3_t velocity;		// lerped between mvelocity[0] and [1]

    vec3_t punchangle;		// temporary offset

// pitch drifting vars
    float idealpitch;
    float pitchvel;
    qboolean nodrift;
    float driftmove;
    QDFLOAT laststop;

    float viewheight;
    float crouch;			// local amount for smoothing stepups

    qboolean paused;			// send over by server
    qboolean onground;
    qboolean inwater;

    int intermission;	// don't change view angle, full screen, etc
    int completed_time;	// latched at intermission start
// These are trash. Why double ? Couldn't have been simply uint32_t, with ms accuracy ?
    QDFLOAT mtime[2];		// the timestamp of last two messages
    QDFLOAT time;			// clients view of time, should be between
                            // servertime and oldservertime to generate
                            // a lerp point for other data
    QDFLOAT oldtime;		// previous cl.time, time-oldtime is used
                            // to decay light values and smooth step ups

    float last_received_message;	// (realtime) for net trouble icon

//
// information that is static for the entire time connected to a server
//
    struct model_s **model_precache;
    struct sfx_s **sound_precache;

    char levelname[40];	// for display on solo scoreboard
    int viewentity;		// cl_entitites[cl.viewentity] = player
    int maxclients;
    int gametype;

// refresh related state
    struct model_s *worldmodel;	// cl_entitites[0].model
    struct efrag_s *free_efrags;
    int num_entities;	// held in cl_entities array
    int num_statics;	// held in cl_staticentities array
    entity_t viewent;			// the gun model

    int cdtrack, looptrack;	// cd audio

// frag scoreboard
    scoreboard_t scores[MAX_CLIENTS];

#ifdef QUAKE2
// light level at player's position including dlights
// this is sent back to the server each frame
// architectually ugly but it works
	int			light_level;
#endif
} client_state_t;

//
// cvars
//
#if USE_ORIGINAL_CVAR
extern	cvar_t	cl_name;
extern	cvar_t	cl_color;

extern	cvar_t	cl_upspeed;
extern	cvar_t	cl_forwardspeed;
extern	cvar_t	cl_backspeed;
extern	cvar_t	cl_sidespeed;

extern	cvar_t	cl_movespeedkey;

extern	cvar_t	cl_yawspeed;
extern	cvar_t	cl_pitchspeed;

extern	cvar_t	cl_anglespeedkey;

extern	cvar_t	cl_autofire;

extern	cvar_t	cl_shownet;
extern	cvar_t	cl_nolerp;

extern	cvar_t	cl_pitchdriftspeed;
extern	cvar_t	lookspring;
extern	cvar_t	lookstrafe;
extern	cvar_t	sensitivity;

extern	cvar_t	m_pitch;
extern	cvar_t	m_yaw;
extern	cvar_t	m_forward;
extern	cvar_t	m_side;
#endif

#define	MAX_TEMP_ENTITIES	MAX_BEAMS //64			// lightning bolts, etc
#define	MAX_STATIC_ENTITIES	128			// torches, etc

//extern	client_state_t	cl;

// FIXME, allocate dynamically
extern efrag_t cl_efrags[MAX_EFRAGS];
#if !DIRECT_SINGLE_PLAYER
extern entity_t cl_static_entities[MAX_STATIC_ENTITIES];
#endif
//extern lightstyle_t	        *cl_lightstyle;
//extern	dlight_t		cl_dlights[MAX_DLIGHTS];
#if SEPARATE_TEMP_ENTITIES
extern	entity_t		cl_temp_entities[MAX_TEMP_ENTITIES];
extern	entity_t		cl_entities[MAX_EDICTS];
#else
extern entity_t cl_entities[MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES + MAX_TEMP_ENTITIES];
#endif
//extern	beam_t			cl_beams[MAX_BEAMS];

//=============================================================================

//
// cl_main
//
dlight_t* CL_AllocDlight(int key);
void CL_DecayLights(void);

void CL_Init(void);

void CL_EstablishConnection(char *host);
void CL_Signon1(void);
void CL_Signon2(void);
void CL_Signon3(void);
void CL_Signon4(void);

void CL_Disconnect(void);
void CL_Disconnect_f(void);
void CL_NextDemo(void);

#define			MAX_VISEDICTS	256

//extern	int				cl_numvisedicts;
#if POINTER_CL_VISEDICT
//    extern entity_t		*cl_visedicts[MAX_VISEDICTS];       // this to be converted to index.
#else
//    extern short		cl_visedicts[MAX_VISEDICTS];       // this to be converted to index.
#endif
//
// cl_input
//
typedef struct
{
    byte down[2];		// key nums holding it down
    byte state;			// low bit is down state
} kbutton_t;

extern kbutton_t in_mlook, in_klook;
extern kbutton_t in_strafe;
extern kbutton_t in_speed;

void CL_InitInput(void);
void CL_SendCmd(void);
void CL_SendMove(usercmd_t *cmd);

void CL_ParseTEnt(void);
void CL_UpdateTEnts(void);

void CL_ClearState(void);

int CL_ReadFromServer(void);
void CL_WriteToServer(usercmd_t *cmd);
void CL_BaseMove(usercmd_t *cmd);

float CL_KeyState(kbutton_t *key);
char* Key_KeynumToString(int keynum);

//
// cl_demo.c
//
void CL_StopPlayback(void);
int CL_GetMessage(void);

void CL_Stop_f(void);
void CL_Record_f(void);
void CL_PlayDemo_f(void);
void CL_TimeDemo_f(void);

//
// cl_parse.c
//
void CL_ParseServerMessage(void);
void CL_NewTranslation(int slot);
void CL_ParseDummyUpdate(void);
//
// view
//
void V_StartPitchDrift(void);
void V_StopPitchDrift(void);

void V_RenderView(void);
void V_Register(void);
void V_ParseDamage(void);
void V_SetContentsColor(int contents);

//
// cl_tent
//
void CL_InitTEnts(void);
void CL_SignonReply(void);
