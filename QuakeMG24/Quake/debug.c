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

 */
#if WIN32
#include "sdl.h"
#include "quakedef.h"
#include <stdint.h>
#define TRISCREEN_X 640
#define TRISCREEN_Y 400
static SDL_Surface *tri_screen = NULL;
static SDL_Surface * tri_workSurface = NULL;
static SDL_Window * tri_window  = NULL;
void debug_triangle_init(uint8_t * palette)
{
    tri_window =   SDL_CreateWindow( "Debug SDL Window", 10, 400, TRISCREEN_X, TRISCREEN_Y, SDL_WINDOW_SHOWN );
    tri_screen = SDL_GetWindowSurface(tri_window);
    tri_workSurface = SDL_CreateRGBSurface(0, TRISCREEN_X, TRISCREEN_Y,8, 0, 0, 0, 0);
    if (!tri_screen)
        Sys_Error("VID: Couldn't set video mode: %s\n", SDL_GetError());
    SDL_Color colors[256];

    for (int i=0; i<256; ++i )
    {
        colors[i].r = *palette++;
        colors[i].g = *palette++;
        colors[i].b = *palette++;
    }
    SDL_SetPaletteColors(tri_workSurface->format->palette, colors, 0, 256);

}
void dbgDrawTriPixel(int x, int y, int color, int clear)
{
    if (clear)
        memset(tri_workSurface->pixels, 244, TRISCREEN_X * TRISCREEN_Y);
    putTriPixel(x, y, color);
}
void dbgVidUpd(void)
{
    SDL_BlitSurface(tri_workSurface, NULL, tri_screen, NULL);
    //Update the surface
    SDL_UpdateWindowSurface(tri_window );
}
void putTriPixel(unsigned int x, unsigned int y, int color)
{
    ((uint8_t*)tri_workSurface->pixels)[x + y * TRISCREEN_X] = color;
}
void   drawTriangle (uint8_t * tribuffer, coord16_t *coords, uint16_t *offsetTable, uint16_t offsetS, int ss, int tt, int clear)
{
    #if 0
    if (clear)
        memset(tri_workSurface->pixels, 0, TRISCREEN_X * TRISCREEN_Y);
    // draw a triangle based on data
    uint16_t minS = coords[0].s;
    uint16_t maxS = coords[0].s;
    uint16_t minT = coords[0].t;
    uint16_t maxT = coords[0].t;
    int leftmost = 0;
    int rightmost = 0;
    // find mins and maxs
    for (int i = 1; i < 3; i++)
    {
        if (minS > coords[i].s)
        {
            minS = coords[i].s;
            leftmost = i;
        }
        if (minT > coords[i].t)
            minT = coords[i].t;
        if (maxS < coords[i].s)
        {
            maxS = coords[i].s;
            rightmost = i;
        }
        if (maxT < coords[i].t)
            maxT = coords[i].t;
    }
    // now we have the minimum s and t values. these will be our offsets
    // Now, we will draw a line between the leftmost and rightmost, and from these two to the central
    int central = 3 - leftmost - rightmost;
    // for each column, it will say where x = 0 is located.
    if (minS != maxS)
    {
        if (coords[central].s == maxS)
        {
            // two points are aligned to the right.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[central].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);

                t1-= REMOVE_T; t2 += ADD_T; // ADDED

                for (int t = t1; t <= t2; t++)
                {
                    putTriPixel(s, t, decodeTriangle(offsetTable, offsetS, tribuffer, s, t, 0));
                }
            }
        }
        else if (coords[central].s == minS)
        {
            // two points are aligned to the left.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);

                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                for (int t = t1; t <= t2; t++)
                {
                    putTriPixel(s, t, decodeTriangle(offsetTable, offsetS, tribuffer, s, t, 0));
                }
            }

        }
        else
        {
            // three points not x-aligned.
            // from leftmost to central
            for (int s = minS - REMOVE_S; s < coords[central].s; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, coords[central].s, coords[central].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                for (int t = t1; t <= t2; t++)
                {
                    putTriPixel(s, t, decodeTriangle(offsetTable, offsetS, tribuffer, s, t, 0));
                }
            }
            // from central to rightmost
            for (int s = coords[central].s; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(coords[central].s, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED

                for (int t = t1; t <= t2; t++)
                {
                    putTriPixel(s, t, decodeTriangle(offsetTable, offsetS, tribuffer, s, t, 0));
                }
            }
        }
    }
    else
    {
      int t1  = coords[0].t;
      int t2 =  coords[0].t;
      if (t1 > coords[1].t)
        t1 = coords[1].t;
      if (t1 > coords[2].t)
        t1 = coords[2].t;
      if (t2 < coords[1].t)
        t2 = coords[1].t;
      if (t2 < coords[2].t)
        t2 = coords[2].t;
        int s = coords[0].s;
        t1-= REMOVE_T; t2 += ADD_T; // ADDED
        for (int t = t1; t <= t2; t++)
        {
            putTriPixel(s, t, decodeTriangle(offsetTable, offsetS, tribuffer, s, t, 0));
        }
    }
    putTriPixel(ss, tt, 251);
    SDL_BlitSurface(tri_workSurface, NULL, tri_screen, NULL);
    //Update the surface
    SDL_UpdateWindowSurface(tri_window );
    #endif
}
#endif
