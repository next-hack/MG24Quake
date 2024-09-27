/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

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

 --------------------------------------------------------------------------

 This memory allocator is based on our previous project, which, in turn,
 is based on the original Id Software's code. See below old copyright notice
 and discussion.

 For Quake, we have made it even more optimized so that each block uses 4 Bytes.

 */
/**
 *  Doom Port to Silicon Labs EFR32xG24 devices and MGM240 modules
 *  by Nicola Wrachien (next-hack in the comments).
 *
 *  This port is based on the excellent doomhack's GBA Doom Port,
 *  with Kippykip additions.
 *
 *  Several data structures and functions have been optimized
 *  to fit in only 256kB RAM (GBA has 384 kB RAM).
 *  Z-Depth Light has been restored with almost no RAM consumption!
 *  Added BLE-based multiplayer.
 *  Added OPL2-based music.
 *  Restored screen melt effect!
 *  Tons of speed optimizations have been done, and the game now
 *  runs extremely fast, despite the much higher 3D resolution with
 *  respect to GBA.
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *  Copyright (C) 2021-2023 Nicola Wrachien (next-hack in the comments)
 *  on the EFR32xG24 and MGM240 port.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * DESCRIPTION:
 *      Zone Memory Allocation, perhaps NeXT ObjectiveC inspired.
 *      Remark: this was the only stuff that, according
 *       to John Carmack, might have been useful for
 *       Quake.
 *
 * Rewritten by Lee Killough, though, since it was not efficient enough.
 *
 * Restored back to its original form by Nicola Wrachien and optimized,
 * as it was not memory efficient enough (see zone.c).
 *
 *---------------------------------------------------------------------*/

#ifndef __Z_ZONE__
#define __Z_ZONE__

#ifndef __GNUC__
#define __attribute__(x)
#endif

// Include system definitions so that prototypes become
// active before macro replacements below are in effect.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#if !WIN32
#include "printf.h"
#endif
#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// ZONE MEMORY
typedef struct memblock
{
#if MAX_STATIC_ZONE < 131072 - 4
    unsigned int next_sptr:15;
    unsigned int prev_sptr:15;
    unsigned int tag :2;
#elif MAX_STATIC_ZONE < 262144
    unsigned int next_sptr:16;
    unsigned int prev_sptr:16;
    union
    {
        unsigned short user_spptr;  // short pointer to pointer.
        unsigned short nextPool_sptr;
    };
    unsigned short allocated:14;    // bitfield: allocated
   // unsigned short poolObjectWordSize:6;        // number of 32 bit words for each object. Max 63 * 4 bytes.
    unsigned short tag :2;
#else
    void *next;
    void *prev;
    union
    {
        void *user;  // short pointer to pointer.
        void *nextPool;
    };
    unsigned short allocated:14;    // bitfield: allocated
    unsigned short tag :2;
#endif
} memblock_t;

// PU - purge tags.

enum
{
    PU_FREE, PU_STATIC,PU_LEVEL, PU_POOL,
    PU_MAX
};
#define PU_LEVSPEC PU_LEVEL
#define PU_PURGELEVEL PU_MAX        /* First purgable tag's level */


void* (Z_Malloc2)(uint32_t size, int tag, void **ptr, const char *sz, int canFail);
void (Z_Free)(void *ptr);
void (Z_FreeTags)(int lowtag, int hightag );
void (Z_ChangeTag)(void *ptr, int tag );
void (Z_Init)(void);
void Z_Close(void);
void* (Z_Calloc)(size_t n, size_t n2, int tag, void **user );
void* (Z_CallocFailable)(size_t n, size_t n2, int tag, void **user );
void* (Z_Realloc)(void *p, size_t n, int tag, void **user );
char* (Z_Strdup)(const char *s, int tag, void **user );
uint32_t getStaticZoneSize(void);

#define Z_Malloc(n)  Z_Calloc(n, 1 , PU_STATIC, NULL)
#define Z_MallocOld(size, tag, user)  Z_Malloc2(size, tag, user, TOSTRING(n), false)

/* cphipps 2001/11/18 -
 * If we're using memory mapped file access to WADs, we won't need to maintain
 * our own heap. So we *could* let "normal" malloc users use the libc malloc
 * directly, for efficiency. Except we do need a wrapper to handle out of memory
 * errors... damn, ok, we'll leave it for now.
 */
#ifndef HAVE_LIBDMALLOC
// Remove all definitions before including system definitions
//
#undef malloc
#undef free
#undef realloc
#undef calloc
#undef strdup

#define malloc(n)          Z_Malloc(n)
#define free(p)            Z_Free(p)
#define realloc(p,n)       Z_Realloc(p,n,PU_STATIC,0)
#define calloc(n1,n2)      Z_Calloc(n1,n2,PU_STATIC,0)
#define strdup(s)          Z_Strdup(s,PU_STATIC,0)
#endif
#endif
