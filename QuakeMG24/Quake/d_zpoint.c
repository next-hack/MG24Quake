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
// d_zpoint.c: software driver module for drawing z-buffered points
#include "quakedef.h"
#include "d_local.h"
#include "r_local.h"

/*
 =====================
 D_DrawZPoint
 =====================
 */
/*
 void D_DrawZPoint (void)
 {
 byte	*pdest;
 short	*pz;
 int		izi;

 pz = d_pzbuffer + (d_zwidth * r_zpointdesc.v) + r_zpointdesc.u;
 pdest = d_viewbuffer + d_scantable(r_zpointdesc.v) + r_zpointdesc.u;
 izi = (int)(r_zpointdesc.zi * 0x8000);

 if (*pz <= izi)
 {
 *pz = izi;
 *pdest = r_zpointdesc.color;
 }
 }

 */
