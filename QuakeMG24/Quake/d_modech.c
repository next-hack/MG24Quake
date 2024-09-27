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
// d_modech.c: called when mode has just changed

#include "quakedef.h"
#include "d_local.h"

int d_vrectx, d_vrecty, d_vrectright_particle, d_vrectbottom_particle;

int d_y_aspect_shift; //, d_pix_min, d_pix_max, d_pix_shift;
#if DYNAMIC_RESOLUTION
int		d_scantable[MAXHEIGHT];
short	*zspantable[MAXHEIGHT];
#endif
/*
 ================
 D_Patch
 ================
 */
void D_Patch(void)
{
#if id386

	static qboolean protectset8 = false;

	if (!protectset8)
	{
		Sys_MakeCodeWriteable ((int)D_PolysetAff8Start,
						     (int)D_PolysetAff8End - (int)D_PolysetAff8Start);
		protectset8 = true;
	}

#endif	// id386
}

/*
 ================
 D_ViewChanged
 ================
 */
void D_ViewChanged(void)
{

    _g->scale_for_mip = xscale;
    if (yscale > xscale)
        _g->scale_for_mip = yscale;

    if (pixelAspect > 1.4)
        d_y_aspect_shift = 1;
    else
        d_y_aspect_shift = 0;

    d_vrectx = _g->r_refdef.vrect.x;
    d_vrecty = _g->r_refdef.vrect.y;
    d_vrectright_particle = _g->r_refdef.vrectright - d_pix_max;
    d_vrectbottom_particle = _g->r_refdef.vrectbottom - (d_pix_max << d_y_aspect_shift);

    D_Patch();
}

