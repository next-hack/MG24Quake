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
// d_clear: clears a specified rectangle to the specified color
#include "quakedef.h"

/*
 ================
 D_FillRect
 ================
 */
void D_FillRect(vrect_t *rect, int color)
{
    int rx, ry, rwidth, rheight;
    unsigned char *dest;
    unsigned *ldest;

    rx = rect->x;
    ry = rect->y;
    rwidth = rect->width;
    rheight = rect->height;

    if (rx < 0)
    {
        rwidth += rx;
        rx = 0;
    }
    if (ry < 0)
    {
        rheight += ry;
        ry = 0;
    }
    if (rx + rwidth > VID_WIDTH)
        rwidth = VID_WIDTH - rx;
    if (ry + rheight > VID_HEIGHT)
        rheight = VID_HEIGHT - rx;

    if (rwidth < 1 || rheight < 1)
        return;

    dest = ((byte*) vid.buffer + ry * VID_ROWBYTES + rx);

    if (((rwidth & 0x03) == 0) && (((long) dest & 0x03) == 0))
    {
        // faster aligned dword clear
        ldest = (unsigned*) dest;
        color += color << 16;

        rwidth >>= 2;
        color += color << 8;

        for (ry = 0; ry < rheight; ry++)
        {
            for (rx = 0; rx < rwidth; rx++)
                ldest[rx] = color;
            ldest = (unsigned*) ((byte*) ldest + VID_ROWBYTES);
        }
    }
    else
    {
        // slower byte-by-byte clear for unaligned cases
        for (ry = 0; ry < rheight; ry++)
        {
            for (rx = 0; rx < rwidth; rx++)
                dest[rx] = color;
            dest += VID_ROWBYTES;
        }
    }
}

