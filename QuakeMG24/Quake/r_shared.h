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
#ifndef GLQUAKE
// r_shared.h: general refresh-related stuff shared between the refresh and the
// driver

// FIXME: clean up and move into d_iface.h

#ifndef _R_SHARED_H_
#define _R_SHARED_H_
#include "global_data.h"
#include "stddef.h"
#define MAXVERTS  16          // max points in a surface polygon
#define MAXWORKINGVERTS (MAXVERTS+4)  // max points in an intermediate
                    //  polygon (while processing)
// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define MAXHEIGHT   152
#define MAXWIDTH    320
#define EDGES_IN_Z_BUFFER 1
#define EDGE_POINTERS   1   // will be marginally faster.

#define MAXDIMENSION  ((MAXHEIGHT > MAXWIDTH) ? MAXHEIGHT : MAXWIDTH)

#define SIN_BUFFER_SIZE (MAXDIMENSION+CYCLE)

#define INFINITE_DISTANCE 0x10000   // distance that's always guaranteed to
                    //  be farther away than anything in
                    //  the scene

//===================================================================

extern void R_DrawLine (polyvert_t *polyvert0, polyvert_t *polyvert1);

//extern int    cachewidth;
//extern pixel_t  *cacheblock;
//extern const int    screenwidth;
#if !CONSTANT_VIDEO_VALUES
extern  float pixelAspect;
#endif
#if PROFILE_SPEED
extern int    r_drawnpolycount;
#endif
#if USE_ORIGINAL_CVAR
extern cvar_t r_clearcolor;
#endif
#if RUNTIME_TABLES
extern int  sintable[SIN_BUFFER_SIZE];
extern byte  intsintable[SIN_BUFFER_SIZE];
#else
extern const int  sintable[SIN_BUFFER_SIZE];
extern const byte  intsintable[SIN_BUFFER_SIZE];
#endif
//extern  vec3_t  vup, base_vup;
//extern  vec3_t  vpn, base_vpn;
//extern  vec3_t  vright, base_vright;
//extern  entity_t    *currententity;
#if NEW_CACHED_EDGES
#define COPY_COLOR_MAP_TO_RAM 0
#if COPY_COLOR_MAP_TO_RAM
  #define NUMSTACKEDGES   1800 // 2400
#else
#if WIN32
#define NUMSTACKEDGES   1500 // 2400
#elif EDGE_POINTERS
#define NUMSTACKEDGES   1600 // 2400
#else
#define NUMSTACKEDGES   1800 // 2400
#endif
#endif
#else
#error
  #define NUMSTACKEDGES   2040 // 2400
#endif
#define SURF_HAS_FIXED_D_ZISTEP_DATA            0
#define SURF_HAS_FIXED_D_ZIORIGIN_DATA          0
#define MINEDGES      NUMSTACKEDGES
#define NUMSTACKSURFACES  600 //800
#define MINSURFACES     NUMSTACKSURFACES
#define LESS_SPANS 1
#if LESS_SPANS
#if SURF_HAS_FIXED_D_ZISTEP_DATA
#define MAXSPANS      3000 //3000
#elif EDGE_POINTERS
// if edge pointer, we need to have a lot of spans.
#define MAXSPANS      3650 //3000
#else
// if no edge pointers, edge_t is smaller, we can update near y = 75
#define MAXSPANS      3500 //3000
#endif
#else
#define MAXSPANS      4500 //3000
#endif
#define SEPARATE_SPAN_NEXT 0

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct espan_s
{   // this could be reduced to 3 bytes. u: 9 bits. v: 8 bits. count: 7 bits. (if larger than 127, we allocate more...)
  #if OLD_SPAN_METHOD
  int       u, v, count;
  struct espan_s  *pnext;
  #elif SEPARATE_SPAN_NEXT
    unsigned int        u:9, v:8, count:9;
  #else
    unsigned int nextSpanIdx: 13;   //
    unsigned int u:9, count:9;
#if ESPANS_HAVE_V
    uint8_t v;
#endif
  #endif
}
#if ESPANS_HAVE_V
__attribute__ ((packed)) espan_t;
#else
espan_t;
#endif
#if !OLD_SPAN_METHOD
//extern espan_t  *basespan_p;
#if SEPARATE_SPAN_NEXT
extern short *nextSpanIndexes_p;
#endif
#endif
// FIXME: compress, make a union if that will help
// insubmodel is only 1, flags is fewer than 32, spanstate could be a byte
//#define MAX_SURFACE_KEY 0x7FFFFFFF
#define MAX_SURFACE_KEY 0x7FFF
#define SURF_SPAN_IDX_BITS 16

#define SURF_HAS_D_ZI_DATA 1
#define TEST_D_ZI_DATA 0
#define SURF_HAS_ENTITY_POINTER     0
typedef struct surf_s
{
    #if 0
    // these 3 can fit all in 32 bits probably (max 800 surfs, max 3k spans). 10:10:12
#if SURF_HAS_PREV_NEXT
  struct surf_s *next;      // active surface stack in r_edge.c
  struct surf_s *prev;      // used in r_edge.c for active surf stack
#endif
#if OLD_SPAN_METHOD
  struct espan_s  *spans;     // pointer to linked list of spans to draw
#endif
  //int     key;        // sorting key (BSP order)
  unsigned int      key:16;       // sorting key (BSP order)
#if ORIGINAL_NEARZI
  float   nearzi;       // nearest 1/z on surface, for mipmapping. This can be easily modified to hold a 16 bit saturated fraction.
#elif SURF_INT_NEARZI
  unsigned int    nearziInt: 13;           // nearest 1/z on surface, for mipmapping. This can be easily modified to hold a 16 bit saturated fraction, or even 8 bit.
#else
  unsigned int    miplevel:2;
#endif
                  // 1 = in span
                  // -1 = in inverted span (end before
                  //  start)
  int insubmodel:1;
#if !OLD_SPAN_METHOD
  unsigned int  spansIdx:SURF_NRZI_FRAC_BITS;      // pointer to linked list of spans to draw
#endif

  int     spanstate:2;      // 0 = not in span
  unsigned int      last_u: 9;        // set during tracing. next-hack: It can be 9 bit. not sure if it can be negative.
#if !SURF_HAS_PREV_NEXT
  unsigned int  NextIdx: 10;      // active surface stack in r_edge.c
  unsigned int  PrevIdx : 10;      // used in r_edge.c for active surf stack
#endif

//  int     flags;        // currentface flags
  void    *data;        // associated data like msurface_t
  entity_t  *entity;            // which BRUSH model it is. This can be a maximum 9-bit index.
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZIORIGIN_DATA
  float   d_ziorigin;
#else
    int32_t fixed_d_ziorigin : 22;      // to be coupled with 10 bit
#endif
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
  float  d_zistepu, d_zistepv;
#else
  int  fixed_d_zistepu:23, fixed_d_zistepv:23;      // coupled with 9 bits
//float  d_zistepu, d_zistepv;
#endif
#endif
//  int     pad[2];       // to 64 bytes
#elif SURF_HAS_FIXED_D_ZISTEP_DATA

    uint32_t      key:16;       // sorting key (BSP order)
    uint32_t    miplevel:2;
    int32_t insubmodel:1;
    uint32_t  spansIdx:SURF_NRZI_FRAC_BITS;      // pointer to linked list of spans to draw
    //
    int32_t fixed_d_ziorigin : 22;      // to be coupled with 10 bit
    unsigned int  NextIdx: 10;      // active surface stack in r_edge.c
    //
    int32_t  fixed_d_zistepu:23;
    uint32_t     last_u: 9;        // set during tracing. next-hack: It can be 9 bit. not sure if it can be negative.

    int32_t fixed_d_zistepv:23;      // coupled with 9 bits
    uint32_t entity_idx : 9;
//
    void    *data;        // associated data like msurface_t

    uint32_t  PrevIdx : 10;      // used in r_edge.c for active surf stack
    int         spanstate:2;      // 0 = not in span
                               // 1 = in span
                              // -1 = in inverted span (end before start)
    uint32_t   surfIndex : 10;  //
#else

    uint32_t      key:16;       // sorting key (BSP order)
    uint32_t  spansIdx:SURF_SPAN_IDX_BITS;      // pointer to linked list of spans to draw

    //
    float d_ziorigin;
    float d_zistepu;
    float d_zistepv;

    void    *data;        // associated data like msurface_t

    uint32_t  PrevIdx : 16;      // used in r_edge.c for active surf stack
    uint32_t  NextIdx: 16;      // active surface stack in r_edge.c

    //
    uint32_t     last_u: 9;        // set during tracing. next-hack: It can be 9 bit (unsigned). not sure if it can be negative.
    //
    uint32_t   surfIndex : 10;  //

    uint32_t    entity_idx : 9;

    uint32_t        spanstate:1;      // 0 = not in span
    // 1 = in span
   // -1 = in inverted span (end before start) NOT USED!
    uint32_t    miplevel:2;
    uint32_t insubmodel:1;
    //
#endif
} surf_t;
#if !SURF_HAS_ENTITY_POINTER
static inline void setSurfEntity(surf_t *s, entity_t *e)
{
    if (NULL == e)
        s->entity_idx = 0;
    else
    {
#if !WIN32
        // make sure entity_t size is a power of two.
        STATIC_ASSERT(0 == (sizeof(entity_t) & (sizeof(entity_t) - 1)) );
#endif
        s->entity_idx = (e - &cl_entities[0]) + 1;
    }
}
static inline entity_t *getSurfEntity(surf_t *s)
{
    if (s->entity_idx == 0)
        return NULL;
    else
        return &cl_entities[s->entity_idx - 1];
}
#endif
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
#define D_ZIORIGIN_PRECISION 65536
static inline void setSurfD_ziorigin(surf_t *s, float v)
{
  s->fixed_d_ziorigin = (v * D_ZIORIGIN_PRECISION);
}
static inline float getSurfD_ziorigin(surf_t *s)
{
  return s->fixed_d_ziorigin  * (1.0f / D_ZIORIGIN_PRECISION);
}

#endif
#if SURF_HAS_FIXED_D_ZISTEP_DATA
#define D_ZISTEP_PRECISION  (8 * 1048576)
static inline void setSurfD_zistepu(surf_t *s, float v)
{
  s->fixed_d_zistepu = (v * D_ZISTEP_PRECISION);
}
static inline void setSurfD_zistepv(surf_t *s, float v)
{
  s->fixed_d_zistepv = (v * D_ZISTEP_PRECISION);
}
static inline float getSurfD_zistepu(surf_t *s)
{
  return s->fixed_d_zistepu * (1.0f / D_ZISTEP_PRECISION);
}
static inline float getSurfD_zistepv(surf_t *s)
{
  return s->fixed_d_zistepv * (1.0f / D_ZISTEP_PRECISION);
}
#endif
#if !SURF_HAS_PREV_NEXT
//extern surf_t *base_surf_p;
#if SURF_HAS_NO_INDEX
#if PROFILE_DIVISIONS
#define implementSurfSetterGetter(field) \
static inline void setSurf##field(surf_t * s, surf_t * field) \
{                                               \
    if (NULL == field)                          \
    {                                           \
        s->field##Idx = 0;                      \
    }                                           \
    else                                        \
    {                                           \
        divisionForPointers++;\
         s->field##Idx = field - base_surf_p;       \
    }                                           \
}                                               \
static inline surf_t* getSurf##field(surf_t * s)   \
{                                               \
    if (s->field##Idx == 0)                     \
    {                                           \
        return NULL;                               \
    }                                           \
    else                                        \
    {                                           \
         return base_surf_p + s->field##Idx;    \
    }                                           \
}
#else
#define implementSurfSetterGetter(field) \
static inline void setSurf##field(surf_t * s, surf_t * field) \
{                                               \
    if (NULL == field)                          \
    {                                           \
        s->field##Idx = 0;                      \
    }                                           \
    else                                        \
    {                                           \
         s->field##Idx = field - base_surf_p;       \
    }                                           \
}                                               \
static inline surf_t* getSurf##field(surf_t * s)   \
{                                               \
    if (s->field##Idx == 0)                     \
    {                                           \
        return NULL;                               \
    }                                           \
    else                                        \
    {                                           \
         return base_surf_p + s->field##Idx;    \
    }                                           \
}
#endif
#else

#endif
#endif

#if !OLD_SPAN_METHOD
#endif
#if !ORIGINAL_NEARZI
#if SURF_INT_NEARZI
static inline float getSurfNearzi(surf_t *s)
{
    return s->nearziInt * (1.0f / (1 << SURF_NRZI_FRAC_BITS));
}
static inline void setSurfNearzi(surf_t *s, float nearzi)
{
    if (nearzi >= 1.0f)
    {
        s->nearziInt  = (1 << SURF_NRZI_FRAC_BITS) - 1;
    }
    else
    {
        s->nearziInt = (1 << SURF_NRZI_FRAC_BITS) * nearzi;
    }
}
#else
static inline int getSurfMiplevel(surf_t *s)
{
    return s->miplevel;
}
static inline void setSurfMiplevel(surf_t *s, int miplevel)
{
    s->miplevel = miplevel;
}

#endif
#endif
static inline int getSurfFlags(surf_t *s)
{
  /*
    if (!s->data)  // it seems data is always non NULL
        return 0;*/
    return ((msurface_t*)s->data)->flags;
}
//extern  surf_t  *surfaces, *surface_p, *surf_max;

// surfaces are generated in back to front order by the bsp, so if a surf
// pointer is greater than another one, it should be drawn in front
// surfaces[1] is the background, and is used as the active surface stack.
// surfaces[0] is a dummy, because index 0 is used to indicate no surface
//  attached to an edge_t

//===================================================================

extern vec3_t sxformaxis[4];  // s axis transformed into viewspace
extern vec3_t txformaxis[4];  // t axis transformed into viewspac

//extern vec3_t modelorg, base_modelorg;
#if !CONSTANT_VIDEO_VALUES
  extern  float xcenter, ycenter;
  extern  float xscale, yscale;
  extern  float xscaleinv, yscaleinv;
#endif
extern  float xscaleshrink, yscaleshrink;

extern  short d_lightstylevalue[MAX_LIGHTSTYLES]; // 8.8 frac of base light value

//extern void TransformVector (vec3_t in, vec3_t out);
extern void SetUpForLineScan(fixed8_t startvertu, fixed8_t startvertv,
  fixed8_t endvertu, fixed8_t endvertv);

extern int  r_skymade;
extern void R_MakeSky (void);
extern void R_InitFlashSky(miptex_t *mt, char *modelName);
//extern int  ubasestep, errorterm, erroradjustup, erroradjustdown;

// flags in finalvert_t.flags
#define ALIAS_LEFT_CLIP       0x0001
#define ALIAS_TOP_CLIP        0x0002
#define ALIAS_RIGHT_CLIP      0x0004
#define ALIAS_BOTTOM_CLIP     0x0008
#define ALIAS_Z_CLIP        0x0010
// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define ALIAS_ONSEAM        0x0020  // also defined in modelgen.h;
                      //  must be kept in sync
#define ALIAS_XY_CLIP_MASK      0x000F
#define FLOAT_NEARZI 0
#define EDGE_NEARZI16 0
// !!! if this is changed, it must be changed in asm_draw.h too !!!
#define FASTER_EDGE 1

#if EDGE_POINTERS
typedef struct edge_s
{
  fixed16_t   u;
  fixed16_t   u_step;
  struct edge_s *prev, *next;
  struct edge_s *nextremove;
  unsigned int surf0 : 10;
  unsigned int    surf1 : 10;
  unsigned int nearzi : 12;
} edge_t;

#elif FASTER_EDGE // this would save 1ms
typedef struct edge_s
{ //note; size is not 16 if there is remove index.
  fixed16_t   u;
  fixed16_t   u_step;
  unsigned short  PrevIdx;
  unsigned short  NextIdx;
#if EDGE_HAS_NEXTREMOVEIDX
  unsigned int  NextRemoveIdx : 16;
#endif
  unsigned int surf0 : 10;
  unsigned int    surf1 : 10;
  unsigned int nearzi : 12;
#if EDGE_HAS_NEXTREMOVEIDX
} __attribute__ ((packed)) edge_t;
#else
} edge_t;
#endif
#else
typedef struct edge_s
{ //note; size is 16
  fixed16_t   u;
  fixed16_t   u_step;
#if EDGE_POINTERS
  struct edge_s *prev, *next; // nh: it will be quite a nightmare to fix these.
  struct edge_s *nextremove;
#else
  unsigned int  PrevIdx : 11;
  unsigned int  NextIdx : 11;
#if !EDGE_SURF_ARRAY

unsigned int surf0 : 10;
unsigned int    surf1 : 10;
#endif
  unsigned int  NextRemoveIdx : 11;
#endif
#if EDGE_SURF_ARRAY
  unsigned short  surfs[2];     // this can be much less than a 16 bit
#endif
#if FLOAT_NEARZI
  float     nearzif; // this can be between 100 and 0.
#else
#if EDGE_NEARZI16
  uint16_t          nearzi16;
#else
  unsigned int nearzi : 11;
#endif
#endif
#if CACHED_EDGES
  medge_t     *owner;
#endif

} __attribute__ ((packed)) edge_t;
#endif
static inline float getEdgeNearzi(edge_t *e)
{
#if FLOAT_NEARZI
    return e->nearzif;
#elif EDGE_NEARZI16
    return e->nearzi16 * (128.0f/ 65536.0f);
#else
    return e->nearzi * (4.0f/2048.0f);
#endif
}
static inline float setEdgeNearzi(edge_t *e, float value)
{
#if FLOAT_NEARZI
    e->nearzif = value;
#elif EDGE_NEARZI16
    e->nearzi16 = value * (65536 / 128);
#else
#if WIN32
    if (value >= 4)
    {
      e->nearzi = (1 << 11) - 1;
    }
    else
    {
      e->nearzi = value * (2048 / 4);
    }
#else
    int ivalue = value * (2048 / 4);
    __ASM volatile ("usat %0, %1, %2" : "=r" (e->nearzi ) :  "I" (11), "r" (ivalue) : "cc" );
#endif
#endif // FLOAT_NEARZI
    return value;
}

#endif  // _R_SHARED_H_

#endif  // GLQUAKE
