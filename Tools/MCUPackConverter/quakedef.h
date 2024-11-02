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

//#define	GLTEST			// experimental stuff
#ifndef QUAKEDEF_H
#define QUAKEDEF_H          // DAMN YOU FOR NOT USING HEADER GUARDS!
#define PROFILE_NUM_ELEMENTS 1
#define CACHEABLE_SKIN       1
#if PROFILE_NUM_ELEMENTS
extern int maxLeaves;
extern int maxFaces;
extern int maxNodes;
extern int maxEdges;
extern int maxEntitiesEasy;
extern int maxEntitiesMedium;
extern int maxEntitiesHard;
extern int maxLighting;
#define PROFILE(name, count) do {if (max##name < (count)) max##name = (count); } while(0)
#endif // PROFILE_NUM_ELEMENTS


#define FIXME(reason) do{printf("\r\n%s at line %d file %s\r\n", reason, __LINE__, __FILE__); system("pause");}while(0)
#define vectorize(v) (*(vector *)v)
#define	QUAKE_GAME			// as opposed to utilities
#define MTOD_HAS_SENTINEL 0
#define TRIANGLE_HAS_SENTINEL 0
#define EDICT_LINKED_LIST   1
#define EDICT_LINKED_LIST_WITH_WATCH 0
#define NO_MINIMIZE 0
#define OLD_WAY 0
#define EDICT_GETTER_SETTERS        1
#define DO_FIND_TOUCHED_LEAVES_JIT  2
#define DIRECT_SINGLE_PLAYER        1
#define MEMORY_OPTIMIZED_MALLOC     1
    #define REMOVE_S 0
    #define ADD_S    0
    #define REMOVE_T 0
    #define ADD_T    0
    #define APPROX_T1   0
    #define APPROX_T2   0

#define	MAX_QPATH		56			// max length of a quake game pathname. WAS 64
#define	MAX_OSPATH		128			// max length of a filesystem pathname

#define MIPLEVELS 4
#define MAX_LBM_HEIGHT	480
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t qboolean;
typedef uint8_t byte;
typedef struct cvar_s
{
	char	*name;
	char	*string;
	qboolean archive;		// set to true to cause it to be saved to vars.rc
	qboolean server;		// notifies players when changed
	float	value;
	struct cvar_s *next;
} cvar_t;
typedef struct
{
    uint16_t s;
    uint16_t t;
} coord16_t;

#define r_pixbytes 1
#include "mathlib.h"
#include "model.h"
#include "bspfile.h"
#include "sky.h"
static inline short  BigShort (short l) {return l;}
static inline short   LittleShort (short l) {return l;}
static inline int     BigLong (int l) {return l;}
static inline int     LittleLong (int l) {return l;}
static inline float   BigFloat (float l) {return l;}
static inline float   LittleFloat (float l) {return l;}
uint8_t * Convert_AliasModel(model_t *mod, void *buffer, uint32_t * size);
uint8_t * Convert_BrushModel(model_t *mod, uint8_t *buffer, uint32_t * size);
#define Sys_Error printf
#endif

