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
// d_sky.c
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"
#define SKY_SPAN_SHIFT	5
#define SKY_SPAN_MAX	(1 << SKY_SPAN_SHIFT)

/*
 =================
 D_Sky_uv_To_st
 =================
 */
void D_Sky_uv_To_st(int u, int v, fixed16_t *s, fixed16_t *t)
{
    float wu, wv, temp;
    vec3_t end;

    if (_g->r_refdef.vrect.width >= _g->r_refdef.vrect.height)
        temp = (float) _g->r_refdef.vrect.width;
    else
        temp = (float) _g->r_refdef.vrect.height;

    wu = 8192.0f * (float) (u - ((int) vid.width >> 1)) / temp;
    wv = 8192.0f * (float) (((int) vid.height >> 1) - v) / temp;

    end[0] = 4096 * _g->vpn[0] + wu * _g->vright[0] + wv * _g->vup[0];
    end[1] = 4096 * _g->vpn[1] + wu * _g->vright[1] + wv * _g->vup[1];
    end[2] = 4096 * _g->vpn[2] + wu * _g->vright[2] + wv * _g->vup[2];
    end[2] *= 3;
    VectorNormalize(end);

    temp = skytime * skyspeed;	// TODO: add D_SetupFrame & set this there
    *s = (int) ((temp + 6 * (SKYSIZE / 2 - 1) * end[0]) * 0x10000);
    *t = (int) ((temp + 6 * (SKYSIZE / 2 - 1) * end[1]) * 0x10000);
}

/*
 =================
 D_DrawSkyScans8
 =================
 */
void D_DrawSkyScans8(espan_t *pspan)
{
    int count, spancount, u, v;
    unsigned char *pdest;
    fixed16_t s, t, snext, tnext, sstep, tstep;
    sstep = 0;	// keep compiler happy
    tstep = 0;	// ditto
    byte *ram_r_skysource = getCurrentTextureCacheAddress();
    do
    {
#if !ESPANS_HAVE_V
        int spanIndex = pspan - _g->basespan_p;

        pdest = (unsigned char*) ((byte*) _g->d_viewbuffer + (screenwidth * _g->basespanV_p[spanIndex]) + pspan->u);
        v = _g->basespanV_p[spanIndex];

#else
    pdest = (unsigned char *)((byte *)_g->d_viewbuffer + (screenwidth * pspan->v) + pspan->u);
    v = pspan->v;

#endif

        count = pspan->count;

        // calculate the initial s & t
        u = pspan->u;
        D_Sky_uv_To_st(u, v, &s, &t);

        do
        {
            if (count >= SKY_SPAN_MAX)
                spancount = SKY_SPAN_MAX;
            else
                spancount = count;

            count -= spancount;

            if (count)
            {
                u += spancount;

                // calculate s and t at far end of span,
                // calculate s and t steps across span by shifting
                D_Sky_uv_To_st(u, v, &snext, &tnext);

                sstep = (snext - s) >> SKY_SPAN_SHIFT;
                tstep = (tnext - t) >> SKY_SPAN_SHIFT;
            }
            else
            {
                // calculate s and t at last pixel in span,
                // calculate s and t steps across span by division
                int spancountminus1 = (spancount - 1);

                if (spancountminus1 > 0)
                {
                    u += spancountminus1;
                    D_Sky_uv_To_st(u, v, &snext, &tnext);

                    sstep = (snext - s) / spancountminus1;
                    tstep = (tnext - t) / spancountminus1;
                }
            }

            do
            {
#if SKY_IN_RAM
				*pdest++ = r_skysource[((t & R_SKY_TMASK) >> 8) + ((s & R_SKY_SMASK) >> 16)];
#else
                *pdest++ = ram_r_skysource[((t & R_SKY_TMASK) >> 9) | ((s & R_SKY_SMASK) >> 16)];
#endif
                s += sstep;
                t += tstep;
            }
            while (--spancount > 0);

            s = snext;
            t = tnext;

        }
        while (count > 0);

#if OLD_SPAN_METHOD
	} while ((pspan = pspan->pnext) != NULL);
#else
    }
    while ((pspan = getNextSpan(pspan, 1)) != NULL);
#endif
}

