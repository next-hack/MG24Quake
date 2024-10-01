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
//
// modelgen.h: header file for model generation program
//
// *********************************************************
// * This file must be identical in the modelgen directory *
// * and in the Quake directory, because it's used to      *
// * pass data from one to the other via model files.      *
// *********************************************************
#ifdef INCLUDELIBS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "cmdlib.h"
#include "scriplib.h"
#include "trilib.h"
#include "lbmlib.h"
#include "mathlib.h"

#endif

#define ALIAS_VERSION	6

#define ALIAS_ONSEAM				0x0020

// must match definition in spritegn.h
#ifndef SYNCTYPE_T
#define SYNCTYPE_T
typedef enum
{
    ST_SYNC = 0, ST_RAND
} synctype_t;
#endif

typedef enum
{
    ALIAS_SINGLE = 0, ALIAS_GROUP
} aliasframetype_t;

typedef enum
{
    ALIAS_SKIN_SINGLE = 0, ALIAS_SKIN_GROUP
} aliasskintype_t;
/*
 typedef struct {
 int			ident;
 int			version;
 vec3_t		scale;
 vec3_t		scale_origin;
 float		boundingradius;
 vec3_t		eyeposition;
 int			numskins;
 int			skinwidth;
 int			skinheight;
 int			numverts;
 int			numtris;
 int			numframes;
 synctype_t	synctype;
 int			flags;
 float		size;
 } mdl_t;        // this is the reduced one.*/
//
typedef struct
{
    int ident;
    int version;
    vec3_t scale;
    vec3_t scale_origin;
    float boundingradius;
    vec3_t eyeposition;
    int numskins;
    int skinwidth;
    int skinheight;
    int numverts;
    int numtris;
    int numframes;
    synctype_t synctype;
    int flags;
    float size;
} disk_mdl_t;
typedef struct
{
//	int			ident;
//	int			version;
    vec3_t scale;
    vec3_t scale_origin;
    vec3_t eyeposition;
    float boundingradius;
    float size;
    short skinwidth;
    short skinheight;
    short numverts;
    short numtris;
    byte numskins;
    byte synctype;
    byte numframes;
    byte flags;
} reduced_mdl_t;
typedef reduced_mdl_t mdl_t;
//typedef disk_mdl_t mdl_t;
// TODO: could be shorts
#define FASTER_STVERTS 0 // buggy.
#if FASTER_STVERTS
typedef struct {
    #if NO_MINIMIZE
  int   onseam;
  int   s;
  int   t;
  #else
  int16_t   onseam ;
  int16_t   s16 ;
  int16_t   t16 ;
  #endif
} stvert_t;
typedef struct {
    #if NO_MINIMIZE
  int   onseam;
  int   s;
  int   t;
  #else
  int   onseam : 1;
  int   s16 : 15;
  int   t16 : 16;
  #endif
} disk_stvert_t;

#else
typedef struct
{
#if NO_MINIMIZE
	int		onseam;
	int		s;
	int		t;
	#else
    int onseam :1;
    int s16 :15;
    int t16 :16;
#endif
} stvert_t;
#endif
#if !NO_MINIMIZE
typedef struct
{
    int onseam;
    int s;
    int t;
} dstvert_t;
#endif

typedef struct dtriangle_s
{
    int facesfront;
    int vertindex[3];
} dtriangle_t;

#define DT_FACES_FRONT				0x0010

// This mirrors trivert_t in trilib.h, is present so Quake knows how to
// load this data

typedef struct
{
    byte v[3];
    byte lightnormalindex;
} trivertx_t;

typedef struct
{
    trivertx_t bboxmin;	// lightnormal isn't used
    trivertx_t bboxmax;	// lightnormal isn't used
    char name[16];	// frame name from grabbing
} daliasframe_t;

typedef struct
{
    int numframes;
    trivertx_t bboxmin;	// lightnormal isn't used
    trivertx_t bboxmax;	// lightnormal isn't used
} daliasgroup_t;

typedef struct
{
    int numskins;
} daliasskingroup_t;

typedef struct
{
    float interval;
} daliasinterval_t;

typedef struct
{
    float interval;
} daliasskininterval_t;

typedef struct
{
    aliasframetype_t type;
} daliasframetype_t;

typedef struct
{
    aliasskintype_t type;
} daliasskintype_t;

#define IDPOLYHEADER	            (('O'<<24)+('P'<<16)+('D'<<8)+'I')
#define IDPOLYHEADER_MEMORY_READY	(('M'<<24)+('P'<<16)+('D'<<8)+'I')

// little-endian "IDPO"

