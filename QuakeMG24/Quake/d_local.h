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
// d_local.h:  private rasterization driver defs
#include "r_shared.h"

/* next-hack: these were variables...
  d_pix_min = 1;
    d_pix_max = 4;
    d_pix_shift = 8 - 1;
*/
#define d_pix_min   1
#define d_pix_max   4
#define d_pix_shift (8 - 1)
//
// TODO: fine-tune this; it's based on providing some overage even if there
// is a 2k-wide scan, with subdivision every 8, for 256 spans of 12 bytes each
//
#define SCANBUFFERPAD		0x1000

#define R_SKY_SMASK	0x007F0000
#define R_SKY_TMASK	0x007F0000

#define DS_SPAN_LIST_END	-128

#define SURFCACHE_SIZE_AT_320X200	600*1024

typedef struct surfcache_s
{
#if NO_MINIMIZE
	struct surfcache_s	*next;
	struct surfcache_s 	**owner;		// NULL is an empty chunk of memory
	int					lightadj[MAXLIGHTMAPS]; // checked for strobe flush
	int					dlight;
	int					size;		// including header
	unsigned			width;
	unsigned			height;		// DEBUG only needed for debug
	float				mipscale;
	struct texture_s	*texture;	// checked for animating textures
	byte				data[4];	// width*height elements
	#else
    struct surfcache_s *next;
    struct surfcache_s **owner;		// NULL is an empty chunk of memory
    int16_t lightadj[MAXLIGHTMAPS]; // checked for strobe flush
    int dlight :1;
    unsigned int width :9;
    int size :22;	// including header. Max size is 208 x 240 I think
//	unsigned			height;		// DEBUG only needed for debug
    //float				mipscale;       // not used
    struct texture_s *texture;	// checked for animating textures
    byte data[4];	// width*height elements
#endif
} surfcache_t;

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct sspan_s
{
    int u, v, count;
} sspan_t;
#if USE_ORIGINAL_CVAR
extern cvar_t	d_subdiv16;
#endif
//extern float	scale_for_mip;

extern qboolean d_roverwrapped;
extern surfcache_t *sc_rover;
extern surfcache_t *d_initial_rover;

//extern float	d_sdivzstepu, d_tdivzstepu, d_zistepu;
//extern float	d_sdivzstepv, d_tdivzstepv, d_zistepv;
//extern float	d_sdivzorigin, d_tdivzorigin, d_ziorigin;

//extern fixed16_t	sadjust, tadjust;
//extern fixed16_t	bbextents, bbextentt;

void D_DrawSpans8(espan_t *pspans);
void D_DrawSpans16(espan_t *pspans);
void D_DrawZSpans(espan_t *pspans);
void Turbulent8(espan_t *pspan);
void D_SpriteDrawSpans(sspan_t *pspan);

void D_DrawSkyScans8(espan_t *pspan);
void D_DrawSkyScans16(espan_t *pspan);

void R_ShowSubDiv(void);
extern void (*prealspandrawer)(void);

extern int D_MipLevelForScale(float scale);

DRAWSURF_SEC void textureLoaderHandler(byte *lastTexture, byte *newTexture, int newMip, int currentSurfIndex, int maxSurfIndex);
DRAWSURF_SEC byte* getCurrentTextureCacheAddress(void);
void clearTextureCache(void);
DRAWSURF_SEC void* getSurfBuffer(msurface_t *surface, int surfPos, int surfNum, int miplevel, int *width);

#if id386
extern void D_PolysetAff8Start (void);
extern void D_PolysetAff8End (void);
#endif

#if DYNAMIC_3D_VIEWPORT_SIZE
extern short *d_pzbuffer;
#else
extern short d_zbuffer[_3D_VIEWPORT_SIZE];
#endif
#define d_zwidth SCREEN_WIDTH

extern int *d_pscantable;

#if DYNAMIC_RESOLUTION
extern int	d_scantable[MAXHEIGHT];
extern short	*zspantable[MAXHEIGHT];
#endif

extern int d_vrectx, d_vrecty, d_vrectright_particle, d_vrectbottom_particle;

extern int d_y_aspect_shift;

//extern pixel_t	*d_viewbuffer;

extern int d_minmip;
extern float d_scalemip[3];

extern void (*d_drawspans)(espan_t *pspan);

