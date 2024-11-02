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
// quakedef.h -- primary header for client
#ifndef QUAKEDEF_H
#define QUAKEDEF_H

//
// debugging symbols
#define ENABLE_DEMO                     1           // if 0, it won't load demo.
#define FORCE_START_GAME_IF_NO_DEMO     1           // if 1, and ENABLE_DEMO is 0, then it will start a new game by default
#define START_MAP                       "e1m1"      // start map of the new game e.g. "e1m4" or "start"
#define START_SKILL                     1           // start skill of the new game. 0 = easy, 1 = normal, 2 = hard, 3 = nightmare.
#define FORCE_TIME_DEMO                 0           // if 1, it will force timedemo. Note that ENABLE_DEMO shall be 1 as well
#define TIME_DEMO_NAME                  "demo3"     // timedemo name. We use timedemo 3 for comparison with: https://thandor.net/benchmark/33

#define RETAIL_QUAKE_PAK_SUPPORT        1           // 1 will support the full retail version
//
#define CACHE_SKINS_TO_FLASH            1           //
//
#define MIN_ZONE_FREE_TO_CACHE_COLORMAP (16384 + 3900)


#if !WIN32
#define moncontrol(m)
#define DRAWSURF_SEC __attribute__ ((section(".drawsurf")))
#else
#define DRAWSURF_SEC
#endif
#define PRE_LIGHT_SURFACES   0
#define LIGHTMAP_ON_INTERNAL_FLASH  0
#define SPRITE_IN_INTERNAL_FLASH    0
#define STATIC_ENTITY_SUPPORT       1
#define SORT_SURFS 1                // sort surfaces to minimize loading from ext mem when drawing.
#if WIN32
#define FIXME(reason) do{printf("\r\n%s at line %d file %s\r\n", reason, __LINE__, __FILE__); system("pause");}while(0)
#else

#define FIXME(reason) do{/*printf("\r\n%s at line %d file %s\r\n", reason, __LINE__, __FILE__);*/ }while(0)
#endif
#if WIN32
#define __ASM(m) FIXME(m)
#define waitForDisplayDMA(y)
#endif
#define STATIC_ASSERT(condition) ((void) sizeof(char[1 - 2 * !(condition)]))
#define SCREEN_HEIGHT 200
#define SCREEN_WIDTH 320
// aux buffer is the last part of the z-buffer, so that when the dma is still drawing there, the bottom part is free.
#define aux_buffer ((byte*) (&d_zbuffer[320*DRAW_BUFFER_HEIGHT]) - 320 * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT))

//
#define LittleShort(s) (s)
#define LittleLong(l) (l)
#define LittleFloat(f) (f)
//
#define vectorize(v) (*(vector *)v)
#define CHECK_NODE_INDEX 0
#if !CHECK_NODE_INDEX
#define checkNodeIndex(...)
#endif

#if !WIN32
#include "printf.h"
#endif
#if WIN32
#include <string.h>
#include "extMemoryWin32.h"
#else
#include "extMemory.h"
#endif

#if WIN32
#define AUX_SECTION
#else
#define AUX_SECTION __attribute__ ((section(".aux_ram_bss")))
#endif
#define	QUAKE_GAME			// as opposed to utilities
#define USE_EXT_MEMORY 1
#define MAX_CONCURRENT_CHANNELS             8
#define MAX_CLIENTS 1
#if WIN32
#define PROFILE_DIVISIONS 0
#define PROFILE_EXT_MEM_LOADS 0
#define PROFILE_SQRTF 0
#endif
#if PROFILE_SQRTF
extern int numSqrtf;
#endif
#if WIN32
extern int alias_drawn_pixels;
#endif
#if PROFILE_EXT_MEM_LOADS
    extern int bytesLoadedFromExtMem;
    extern int extMemAccesses;
    extern int bytesLoadedUnalignedFromExtMem;
#endif
#if PROFILE_DIVISIONS
    extern int divisionForPointers;
#endif // PROFILE_DIVISIONS
#define BLOCKLIGHT_TYPE                 uint32_t
#define HAS_R_LIGHT_WIDTH               1
#define NEW_BILINEAR_INTERPOLATION      1
#define USE_OLD_ABS_CALLS               0
#define ENTITY_HAS_SHORT_COORDS         1
#define CACHE_TO_FLASH                  1
#define CACHED_EDGES                    0
#define CLIP_PLANE_USES_FLOAT           1
#define NEW_CACHED_EDGES                1
#define ESPANS_HAVE_V                   0
#define ENABLE_RECURSIVE_DRAWING        1
#define EDICTS_USE_SHORT_PTR            1       // idem
#define LINKS_USE_SHORT_PTR             1       // to put back to 1
#define	MAX_MOD_KNOWN	                  256
#define ANGLE_PRECISION                 64      //
#define CACHE_STATUS_BAR_TO_FLASH_IF_POSSIBLE       1
#define MTOD_HAS_SENTINEL 0
#define TRIANGLE_HAS_SENTINEL 0
#define SEPARATE_BRUSH_MODEL_DATA 1
#define USING_R_DLIGHTFRAMECOUNT     0
#define USE_PROGSDAT 0
#define EDICT_LINKED_LIST   1
#define EDICT_LINKED_LIST_WITH_WATCH 0
#define NO_MINIMIZE 0
#define OLD_WAY 0
#define EDICT_GETTER_SETTERS        1
#define DO_FIND_TOUCHED_LEAVES_JIT      3
#define DIRECT_SINGLE_PLAYER        1
#define MEMORY_OPTIMIZED_MALLOC     1
#define _3D_VIEWPORT_SIZE   (320 * 152)
#define VISLEAVES_IN_Z_BUFFER           1
#define	r_drawpolys                     0
#define	r_drawculledpolys               0
#define	r_worldpolysbacktofront         0
#define	MAX_SFX		255         // strictly less than 256, we use byte index!
#define DRAW_BUFFER_HEIGHT  152
#if RETAIL_QUAKE_PAK_SUPPORT
#define MAX_STATIC_ZONE                 ( 48412)
#define MAX_TEXTURE_SIZE   (16384 + 4096) //note: in the surf buffer the medge cache offset is stored! And there are up to 14.8k medges in the shareware version

#else
//#define MAX_STATIC_ZONE                 ( 32768 + 3300 + 1300 + 1024 + 768 )
#define MAX_TEXTURE_SIZE   (14800 * 2) //note: in the surf buffer the medge cache offset is stored! And there are up to 14.8k medges in the shareware version
#define MAX_STATIC_ZONE                 (39292)

#endif
#define QDFLOAT                 float
#define CREATE_DELTA_LIGHT_MAP          1
#define BETTER_EDICT_COMPATIBILITY      1
#define SAVE_GAME_SIZE                  (65536)  // should be enough.
#define		MAXCMDLINE	40
#define MAX_HISTORY_LINES 1
#if BETTER_EDICT_COMPATIBILITY
#define END_EDICT                       sv.edicts
#else
    #define END_EDICT                       NULL
#endif
#define STATIC_TEMP_ENTITIES 1
#if DEBUG_EDICTS
    #define edictDbgPrintf printf
#else
#define edictDbgPrintf(...)
#endif // DEBUG_EDICTS
#define REMOVE_S 0
#define ADD_S    0
#define REMOVE_T 0
#define ADD_T    0
#define APPROX_T1   0
#define APPROX_T2   0
//
#define v(x) (x)

#if ENTITY_HAS_SHORT_COORDS
#define ANGLE_SHORT_TYPE    short
static inline float toFloatCoord(short s)
{
    return s * (1.0f / 8);
}
static inline float toFloatAngle(ANGLE_SHORT_TYPE s)
{
    return s * (1.0f / ANGLE_PRECISION); // (360 / (256.0f * ANGLE_PRECISION));
}
static inline short toShortCoord(float c)
{
    return c * 8;
}
static inline ANGLE_SHORT_TYPE toShortAngle(float a)
{
    return a * ANGLE_PRECISION; //(ANGLE_PRECISION * 256.0f/360);
}
typedef union
{
    struct
    {
        float x, y, z;
    };
    float v[3];
} vect_t;
typedef union
{
    struct
    {
        short x, y, z;
    };
    short v[3];
} shortVect_t;
static inline short floatToShortAngle(float a)
{
    return toShortAngle(a);
}
static inline float shortAngleToFloat(short a)
{
    return toFloatAngle(a);
}

static inline shortVect_t vfloatToShortAngle(vect_t v)
{
    shortVect_t s;
    s.v[0] = toShortAngle(v.v[0]);
    s.v[1] = toShortAngle(v.v[1]);
    s.v[2] = toShortAngle(v.v[2]);
    return s;
}
static inline vect_t vshortAngleToFloat(shortVect_t s)
{
    vect_t v;
    v.v[0] = toFloatAngle(s.v[0]);
    v.v[1] = toFloatAngle(s.v[1]);
    v.v[2] = toFloatAngle(s.v[2]);
    return v;
}
static inline vect_t toFloatAngles(ANGLE_SHORT_TYPE s[3])
{
    vect_t v;
    v.v[0] = toFloatAngle(s[0]);
    v.v[1] = toFloatAngle(s[1]);
    v.v[2] = toFloatAngle(s[2]);
    return v;
}
static inline vect_t toFloatCoords(short s[3])
{
    vect_t v;
    v.v[0] = toFloatCoord(s[0]);
    v.v[1] = toFloatCoord(s[1]);
    v.v[2] = toFloatCoord(s[2]);
    return v;
}
static inline float short13p3ToFloat(short s)
{
    return s * (1 / 8.0f);
}
static inline float short12p4ToFloat(short s)
{
    return s * (1 / 16.0f);
}
static inline short floatToShort13p3(float f)
{
    return f * 8.0f;
}
static inline short floatToShort12p4(float f)
{
    return f * 16.0f;
}
static inline float short10p6ToFloat(short s)
{
    return s * (1 / 64.0f);
}
static inline short floatToShort10p6(float f)
{
    return f * 64.0f;
}
static inline float short8p8ToFloat(short s)
{
    return s * (1 / 256.0f);
}
static inline short floatToShort8p8(float f)
{
    return f * 256.0f;
}

static inline vect_t vshort13p3ToFloat(shortVect_t s)
{
    vect_t v;
    v.v[0] = short13p3ToFloat(s.v[0]);
    v.v[1] = short13p3ToFloat(s.v[1]);
    v.v[2] = short13p3ToFloat(s.v[2]);
    return v;
}
static inline vect_t vshort12p4ToFloat(shortVect_t s)
{
    vect_t v;
    v.v[0] = short12p4ToFloat(s.v[0]);
    v.v[1] = short12p4ToFloat(s.v[1]);
    v.v[2] = short12p4ToFloat(s.v[2]);
    return v;
}
static inline vect_t vshort10p6ToFloat(shortVect_t s)
{
    vect_t v;
    v.v[0] = short10p6ToFloat(s.v[0]);
    v.v[1] = short10p6ToFloat(s.v[1]);
    v.v[2] = short10p6ToFloat(s.v[2]);
    return v;
}
static inline shortVect_t vfloatToShort13p3(vect_t v)
{
    shortVect_t s;
    s.v[0] = floatToShort13p3(v.v[0]);
    s.v[1] = floatToShort13p3(v.v[1]);
    s.v[2] = floatToShort13p3(v.v[2]);
    return s;
}
static inline shortVect_t vfloatToShort12p4(vect_t v)
{
    shortVect_t s;
    s.v[0] = floatToShort12p4(v.v[0]);
    s.v[1] = floatToShort12p4(v.v[1]);
    s.v[2] = floatToShort12p4(v.v[2]);
    return s;
}

static inline shortVect_t vfloatToShort10p6(vect_t v)
{
    shortVect_t s;
    s.v[0] = floatToShort10p6(v.v[0]);
    s.v[1] = floatToShort10p6(v.v[1]);
    s.v[2] = floatToShort10p6(v.v[2]);
    return s;
}

#endif
#if !USE_PROGSDAT
#define VEC(x) x.v
//#define getEdictFieldValue(ent, name) (ent->v.qcc_##name)
#endif // USE_PROGSDAT

#define MAX_GAMMA       0.5f
#define MIN_GAMMA       0.2f

#undef VERSION
#define	VERSION				1.09
#define STR(x)        #x
#define XSTR(x)       STR(x)    // expanded
#define	GLQUAKE_VERSION		1.00
#define	D3DQUAKE_VERSION	0.01
#define	WINQUAKE_VERSION	0.996
#define	LINUX_VERSION		1.30
#define	X11_VERSION			1.10

//define	PARANOID			// speed sapping error checking

#ifdef QUAKE2
#define	GAMENAME	"id1"		// directory to look in by default
#else
#define	GAMENAME	"id1"
#endif

#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

#include "z_zone.h"
#if !WIN32
#include "graphics.h"
#endif

#if defined(_WIN32) && !defined(WINDED)

#if defined(_M_IX86)
#define __i386__	1
#endif

void	VID_LockBuffer (void);
void	VID_UnlockBuffer (void);

#else

#define	VID_LockBuffer()
#define	VID_UnlockBuffer()

#endif

#if defined(__i386__) && defined(USE_ASM)
#define id386	1
#else
#define id386	0
#endif

#if id386
#define UNALIGNED_OK	1	// set to 0 if unaligned accesses are not supported
#else
#define UNALIGNED_OK	0
#endif

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define CACHE_SIZE	1		// used to align key data structures

#define UNUSED(x)	(x = x)	// for pesky compiler / lint warnings

#define	MINIMUM_MEMORY			0x550000
#define	MINIMUM_MEMORY_LEVELPAK	(MINIMUM_MEMORY + 0x100000)

#define MAX_NUM_ARGVS	50

// up / down
#define	PITCH	0

// left / right
#define	YAW		1

// fall over
#define	ROLL	2

#define	MAX_QPATH		56			// max length of a quake game pathname. WAS 64
#define	MAX_OSPATH		128			// max length of a filesystem pathname

#define	ON_EPSILON		0.1			// point on plane side epsilon

#if !USE_EXT_MEMORY
#define	MAX_MSGLEN	    8000		// max length of a reliable message
#define	MAX_DATAGRAM	1024		// max length of unreliable message
#else
#define	MAX_MSGLEN	    6500		// max length of a reliable message
#define	MAX_DATAGRAM	1024		// max length of unreliable message

#endif
//

//
// per-level limits
//
#if RETAIL_QUAKE_PAK_SUPPORT
#define MAX_SURFACES    7104        // tuned?
#define	MAX_EDICTS		408			// FIXME: ouch! ouch! ouch!
#else
#define MAX_SURFACES    6144        // tuned?
#define	MAX_EDICTS		400			// FIXME: ouch! ouch! ouch!
#endif
#if STATIC_ENTITY_SUPPORT
#define ADDITIONAL_CLIENT_ENTITIES      0      // this is for demo and static edicts support
#else
    #define ADDITIONAL_CLIENT_ENTITIES      0
#endif
#define MAX_MOVABLE_EDICTS (MAX_EDICTS/10)      // 1/10 of edicts moved at once is a lot.
#define	MAX_LIGHTSTYLES	64          // was 64
#define	MAX_MODELS		256			// these are sent over the net as bytes
#define	MAX_SOUNDS		256			// so they cannot be blindly increased

#define	SAVEGAME_COMMENT_LENGTH	7
#define MAX_SAVEGAMES   8
#define	MAX_STYLESTRING	56          // was 64

//
// stats are integers communicated to the client by the server
//
#define	MAX_CL_STATS		32  // can it be reduced? looks like yes...
#define	STAT_HEALTH			0
#define	STAT_FRAGS			1
#define	STAT_WEAPON			2
#define	STAT_AMMO			3
#define	STAT_ARMOR			4
#define	STAT_WEAPONFRAME	5
#define	STAT_SHELLS			6
#define	STAT_NAILS			7
#define	STAT_ROCKETS		8
#define	STAT_CELLS			9
#define	STAT_ACTIVEWEAPON	10
#define	STAT_TOTALSECRETS	11
#define	STAT_TOTALMONSTERS	12
#define	STAT_SECRETS		13		// bumped on client side by svc_foundsecret
#define	STAT_MONSTERS		14		// bumped by svc_killedmonster

// stock defines

#define	IT_SHOTGUN				1
#define	IT_SUPER_SHOTGUN		2
#define	IT_NAILGUN				4
#define	IT_SUPER_NAILGUN		8
#define	IT_GRENADE_LAUNCHER		16
#define	IT_ROCKET_LAUNCHER		32
#define	IT_LIGHTNING			64
#define IT_SUPER_LIGHTNING      128
#define IT_SHELLS               256
#define IT_NAILS                512
#define IT_ROCKETS              1024
#define IT_CELLS                2048
#define IT_AXE                  4096
#define IT_ARMOR1               8192
#define IT_ARMOR2               16384
#define IT_ARMOR3               32768
#define IT_SUPERHEALTH          65536
#define IT_KEY1                 131072
#define IT_KEY2                 262144
#define	IT_INVISIBILITY			524288
#define	IT_INVULNERABILITY		1048576
#define	IT_SUIT					2097152
#define	IT_QUAD					4194304
#define IT_SIGIL1               (1<<28)
#define IT_SIGIL2               (1<<29)
#define IT_SIGIL3               (1<<30)
#define IT_SIGIL4               (1<<31)

//===========================================
//rogue changed and added defines

#define RIT_SHELLS              128
#define RIT_NAILS               256
#define RIT_ROCKETS             512
#define RIT_CELLS               1024
#define RIT_AXE                 2048
#define RIT_LAVA_NAILGUN        4096
#define RIT_LAVA_SUPER_NAILGUN  8192
#define RIT_MULTI_GRENADE       16384
#define RIT_MULTI_ROCKET        32768
#define RIT_PLASMA_GUN          65536
#define RIT_ARMOR1              8388608
#define RIT_ARMOR2              16777216
#define RIT_ARMOR3              33554432
#define RIT_LAVA_NAILS          67108864
#define RIT_PLASMA_AMMO         134217728
#define RIT_MULTI_ROCKETS       268435456
#define RIT_SHIELD              536870912
#define RIT_ANTIGRAV            1073741824
#define RIT_SUPERHEALTH         2147483648

//MED 01/04/97 added hipnotic defines
//===========================================
//hipnotic added defines
#define HIT_PROXIMITY_GUN_BIT 16
#define HIT_MJOLNIR_BIT       7
#define HIT_LASER_CANNON_BIT  23
#define HIT_PROXIMITY_GUN   (1<<HIT_PROXIMITY_GUN_BIT)
#define HIT_MJOLNIR         (1<<HIT_MJOLNIR_BIT)
#define HIT_LASER_CANNON    (1<<HIT_LASER_CANNON_BIT)
#define HIT_WETSUIT         (1<<(23+2))
#define HIT_EMPATHY_SHIELDS (1<<(23+3))

//===========================================

#define	MAX_SCOREBOARD		1
#define	MAX_SCOREBOARDNAME	8

#define	SOUND_CHANNELS		8

// This makes anyone on id's net privileged
// Use for multiplayer testing only - VERY dangerous!!!
// #define IDGODS
#include "tabmath.h"
#include "common.h"
#include "bspfile.h"
#include "vid.h"
#include "sys.h"
#include "mathlib.h"
#include <stdint.h>
#include "progs.h"
extern uint8_t allowMipMapReduction;
typedef struct
{
    uint16_t s;
    uint16_t t;
} coord16_t;
typedef struct
{
#if ENTITY_HAS_SHORT_COORDS
    short origin_s[3];
    ANGLE_SHORT_TYPE angles_s[3];
#else
	    vec3_t	origin;
	    vec3_t	angles;
	#endif
    uint8_t modelindex;
    uint8_t frame;
    uint8_t colormap :4;
    uint8_t effects :4;  // for Q2 is 8 bits
    uint8_t skin;
} entity_state_t;

#include "wad.h"
#include "draw.h"
#include "cvar.h"
#include "screen.h"
#include "net.h"
#include "protocol.h"
#include "cmd.h"
#include "sbar.h"
#include "sound.h"
#include "render.h"
#include "client.h"

#include "server.h"

#ifdef GLQUAKE
#include "gl_model.h"
#else
#include "model.h"
#include "d_iface.h"
#endif

#include "input.h"
#include "world.h"
#include "keys.h"
#include "console.h"
#include "view.h"
#include "menu.h"
//#include "crc.h"
#include "cdaudio.h"
#if !WIN32
void initAudio(void);
#endif
#include "internalFlash.h"
#if EDICT_GETTER_SETTERS
#include "field_getters_setters.h"
#endif
#include "entity_getters_setters.h"
#ifdef GLQUAKE
#include "glquake.h"
#endif
#if MARK_NODE_IN_SURFACE
#if USE_NODE_DLIGHTBITS
#if MAX_DLIGHTS <= 8
extern uint8_t *nodeDlightBits;
#elif MAX_DLIGHTS <= 16
extern uint16_t *nodeDlightBits;
#else
extern uint32_t *nodeDlightBits;
#endif
#else
extern uint8_t *nodeHadDlight;
#endif
#endif // MARK_NODE_IN_SURFACE
#define TFRACSHIFT 16
typedef struct
{
#if NEW_BILINEAR_INTERPOLATION
    BLOCKLIGHT_TYPE *blocklights;
    byte *r_source;
#if !WIN32
    unsigned int tWidthHeightMask;
    unsigned int tWidthOr1;
#endif
    int surfmip;            // yes, could use uint8_t, but for speed this is better.
    int textureType;        // if 0, no need for complex mod!
    int r_texture_width;
    int qcs;
    int qct;
    int r_texture_height;
    int r_surf_soffs;
    int r_surf_toffs;
    int r_lightwidth;
    int tWidthMask;
    int tHeightMask;
#else
    int r_i_texture_width;
    int r_i_texture_height;
    BLOCKLIGHT_TYPE *blocklights;
    int r_lightwidth;
    byte *r_source;
    int r_surf_soffs;
    int r_surf_toffs;
    int r_texture_width;
    int r_texture_height;
    unsigned  int qcs;
    unsigned int qct;
    #endif
    byte *colormap;
} surfDrawData_t;

//=============================================================================

// the host system specifies the base of the directory tree, the
// command line parms passed to the program, and the amount of memory
// available for the program to use

typedef struct
{
    char *basedir;
    char *cachedir;		// for development over ISDN lines
    int argc;
    char **argv;
    void *membase;
    int memsize;
} quakeparms_t;

#include "global_data.h"
#include "tempBuffer.h"
//=============================================================================

// next-hack: Savegame structure. Used only for offset address calculation.
#define SAVEGAME_COOKIE 0x12345678
#define SETTINGS_COOKIE 0x12345678
#define	SAVEGAME_VERSION	5

typedef struct
{
    uint32_t dummy;
    uint32_t cookie;
    int32_t version;
    char comment[SAVEGAME_COMMENT_LENGTH + 1];
    float spawn_params[NUM_SPAWN_PARMS];
    short lightstyles_idx[MAX_LIGHTSTYLES];
    uint8_t lightstyles_len[MAX_LIGHTSTYLES];
    progsvars_t progsvars;
    int numEdicts;
    int skill;
    float time;
    edict_t *sv_edicts;
    edict_t *sv_lastEdict;
    char name[32];
    uint8_t memzone[MAX_STATIC_ZONE];
#if SAVE_STATIC_LIGHTS
    static_light_romEntvars_t romEntvars[MAX_EDICTS];
#endif
    int numSounds;
    channel_t channels[MAX_CHANNELS];
    uint8_t *nodeHadDlight;
    void *areanode;
    int numareadnodes;
    uint32_t pcolormap;
} savegame_t;
typedef struct
{
    savegame_t s;
    uint8_t padding[SAVE_GAME_SIZE - sizeof(savegame_t)];
} padded_savegame_t;
typedef struct
{
    uint32_t cookie;
    uint32_t len;
} settings_t;
typedef struct
{
    settings_t s;
    uint8_t settingsText[SAVE_GAME_SIZE - sizeof(settings_t)];
} padded_settings_t;
typedef struct
{
    padded_settings_t settings;
    padded_savegame_t savegames[MAX_SAVEGAMES];
} nvmData_t;
extern int total_channels;

extern qboolean noclip_anglehack;

//
// host
//
extern const quakeparms_t host_parms;
#if USE_ORIGINAL_CVAR
extern	cvar_t		sys_ticrate;
extern	cvar_t		sys_nostdout;
extern	cvar_t		developer;
#endif
extern qboolean host_initialized;		// true if into command execution
extern QDFLOAT host_frametime;
extern byte *host_basepal;
extern byte *host_colormap;
extern int host_framecount;	// incremented every frame, never reset
extern QDFLOAT realtime;			// not bounded in any way, changed at
                                    // start of every frame, never reset

void Host_ClearMemory(void);
void Host_ServerFrame(void);
void Host_InitCommands(void);
void Host_Init(quakeparms_t *parms);
void Host_Shutdown(void);
void Host_Error(char *error, ...);
void Host_EndGame(char *message, ...);
void Host_Frame(float time);
void Host_Quit_f(void);
void Host_ClientCommands(char *fmt, ...);
void Host_ShutdownServer(qboolean crash);
void Host_WriteConfiguration(void);
static inline void fastMemclear32(void *ptr, uint32_t wordNum)
{
    uint32_t *ptr32 = ptr;
    for (uint32_t i = 0; i < wordNum; i++)
        *ptr32++ = 0;
}

extern qboolean msg_suppress_1;		// suppresses resolution and cache size console output
                                    //  an fullscreen DIB focus gain/loss
extern int current_skill;		// skill level for currently loaded level (in case
                                //  the user changes the cvar while the level is
                                //  running, this reflects the level actually in use)

extern qboolean isDedicated;
extern char *tempStringStack;

//extern int			minimum_memory;

//
// chase
//
//extern	cvar_t	chase_active;

void Chase_Init(void);
void Chase_Reset(void);
void Chase_Update(void);
#endif
