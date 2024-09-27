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
// d_init.c: rasterization driver initialization
#include "quakedef.h"
#include "d_local.h"

#define NUM_MIPS	4

#if USE_ORIGINAL_CVAR
cvar_t	d_subdiv16 = {"d_subdiv16", "1"};
cvar_t	d_mipcap = {"d_mipcap", "0"};
cvar_t	d_mipscale = {"d_mipscale", "1"};
#endif
surfcache_t *d_initial_rover;
qboolean d_roverwrapped;
int d_minmip;
#if 0
float			d_scalemip[NUM_MIPS-1];

const float	basemip[NUM_MIPS-1] = {1.0, 0.5*0.8, 0.25*0.8};
#endif
//extern int			d_aflatcolor;

void (*d_drawspans)(espan_t *pspan);

/*
 ===============
 D_Init
 ===============
 */
void D_Init(void)
{
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&d_subdiv16);
	Cvar_RegisterVariable (&d_mipcap);
	Cvar_RegisterVariable (&d_mipscale);
#endif
}

/*
 ===============
 D_CopyRects
 ===============
 */
void D_CopyRects(vrect_t *prects, int transparent)
{

// this function is only required if the CPU doesn't have direct access to the
// back buffer, and there's some driver interface function that the driver
// doesn't support and requires Quake to do in software (such as drawing the
// console); Quake will then draw into wherever the driver points vid.buffer
// and will call this function before swapping buffers

    UNUSED(prects);
    UNUSED(transparent);
}

/*
 ===============
 D_EnableBackBufferAccess
 ===============
 */
void D_EnableBackBufferAccess(void)
{
    VID_LockBuffer ();
}

/*
 ===============
 D_TurnZOn
 ===============
 */
void D_TurnZOn(void)
{
// not needed for software version
}

/*
 ===============
 D_DisableBackBufferAccess
 ===============
 */
void D_DisableBackBufferAccess(void)
{
    VID_UnlockBuffer ();
}

/*
 ===============
 D_SetupFrame
 ===============
 */
void D_SetupFrame(void)
{
#if WARP_HAS_DIFFERENT_RESOLUTION
	if (r_dowarp)
		_g->d_viewbuffer = r_warpbuffer;
	else
#endif
#if PROFILE_SPEED
	  pixAlias = 0;
#endif
    _g->d_viewbuffer = (void*) (byte*) vid.buffer;
#if 0
	if (r_dowarp)
		screenwidth = WARP_WIDTH;
	else
		screenwidth = vid.rowbytes;
#endif
    d_roverwrapped = false;
#if SURF_CACHE
	d_initial_rover = sc_rover;
#endif
#if 0
  int   i;
	d_minmip = d_mipcap;
	if (d_minmip > 3)
		d_minmip = 3;
	else if (d_minmip < 0)
		d_minmip = 0;
	for (i=0 ; i<(NUM_MIPS-1) ; i++)
		d_scalemip[i] = basemip[i] * d_mipscale;
#endif
#if	id386
				if (d_subdiv16)
					d_drawspans = D_DrawSpans16;
				else
					d_drawspans = D_DrawSpans8;
#else
    d_drawspans = D_DrawSpans8;
#endif

    _g->d_aflatcolor = 0;
}

/*
 ===============
 D_UpdateRects
 ===============
 */
void D_UpdateRects(vrect_t *prect)
{

// the software driver draws these directly to the vid buffer

    UNUSED(prect);
}

