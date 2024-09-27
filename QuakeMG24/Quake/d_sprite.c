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
// d_sprite.c: software top-level rasterization driver module for drawing
// sprites
#include "quakedef.h"
#include "d_local.h"
#define ASYNCH_LOAD_SPRITE 1
#if	!id386
#define drawSpritePixel()             \
          do {                        \
          btemp = *(pbase + (s >> 16) + (t >> 16) * _g->cachewidth); \
          if (btemp != 255)           \
          {                           \
            if (*pz <= (izi >> 16))   \
            {                         \
              *pz = izi >> 16;        \
              *pdest = btemp;         \
            }             \
          }               \
          izi += izistep; \
          pdest++;        \
          pz++;           \
          s += sstep;     \
          t += tstep;     \
          }while(0)

/*
 =====================
 D_SpriteDrawSpans
 =====================
 */
void D_SpriteDrawSpans(sspan_t *pspan)
{
    int count, spancount, izistep;
    int izi;
    byte *pbase, *pdest;
    fixed16_t s, t, snext, tnext, sstep, tstep;
    float sdivz, tdivz, zi, z, du, dv, spancountminus1;
    float sdivz8stepu, tdivz8stepu, zi8stepu;
    byte btemp;
    short *pz;

    sstep = 0;	// keep compiler happy
    tstep = 0;	// ditto

//	pbase =  _g->cacheblock;
#if WIN32
    if (_g->cachewidth * _g->sprite_height > MAX_TEXTURE_SIZE)
    {
        printf("Error, the sprite is %d wide and %d high\r\n", _g->cachewidth, _g->sprite_height);
        FIXME("sprite too large");
    }
#endif
#if SPRITE_IN_INTERNAL_FLASH
  pbase = _g->cacheblock;

  uint32_t *dst = getTextureCacheBuffer();
  uint32_t *src = _g->cacheblock;
  pbase = dst;
  for (int i = 0; i <  _g->cachewidth * _g->sprite_height / 4; i++)
   *dst++ = *src++;
#else
#if ASYNCH_LOAD_SPRITE
    pbase = _g->cacheblock;
#else
	pbase = extMemGetDataFromAddress(getTextureCacheBuffer(), _g->cacheblock, _g->cachewidth * _g->sprite_height);
#endif
#endif
#define MAX_SPAN_COUNT    8
    sdivz8stepu = _g->d_sdivzstepu * MAX_SPAN_COUNT;
    tdivz8stepu = _g->d_tdivzstepu * MAX_SPAN_COUNT;
    zi8stepu = _g->d_zistepu * MAX_SPAN_COUNT;
    int loaded = 0;
// we count on FP exceptions being turned off to avoid range problems
    izistep = (int) (_g->d_zistepu * 0x8000 * 0x10000);

    do
    {
        pdest = (byte*) _g->d_viewbuffer + (screenwidth * pspan->v) + pspan->u;
        pz = _g->d_pzbuffer + (d_zwidth * pspan->v) + pspan->u;

        count = pspan->count;

        if (count > 0)
        {

            // calculate the initial s/z, t/z, 1/z, s, and t and clamp
            du = (float) pspan->u;
            dv = (float) pspan->v;

            sdivz = _g->d_sdivzorigin + dv * _g->d_sdivzstepv + du * _g->d_sdivzstepu;
            tdivz = _g->d_tdivzorigin + dv * _g->d_tdivzstepv + du * _g->d_tdivzstepu;
            zi = _g->d_ziorigin + dv * _g->d_zistepv + du * _g->d_zistepu;
            z = (float) 0x10000 / zi;	// prescale to 16.16 fixed-point
            // we count on FP exceptions being turned off to avoid range problems
            izi = (int) (zi * 0x8000 * 0x10000);

            s = (int) (sdivz * z) + _g->sadjust;
            if (s > _g->bbextents)
                s = _g->bbextents;
            else if (s < 0)
                s = 0;

            t = (int) (tdivz * z) + _g->tadjust;
            if (t > _g->bbextentt)
                t = _g->bbextentt;
            else if (t < 0)
                t = 0;

            do
            {
                // calculate s and t at the far end of the span
                if (count >= MAX_SPAN_COUNT)
                    spancount = MAX_SPAN_COUNT;
                else
                    spancount = count;

                count -= spancount;

                if (count)
                {
                    // calculate s/z, t/z, zi->fixed s and t at far end of span,
                    // calculate s and t steps across span by shifting
                    sdivz += sdivz8stepu;
                    tdivz += tdivz8stepu;
                    zi += zi8stepu;
                    z = (float) 0x10000 / zi;	// prescale to 16.16 fixed-point

                    snext = (int) (sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT)
                        snext = MAX_SPAN_COUNT;	// prevent round-off error on <0 steps from
                    //  from causing overstepping & running off the
                    //  edge of the texture

                    tnext = (int) (tdivz * z) + _g->tadjust;
                    if (tnext > _g->bbextentt)
                        tnext = _g->bbextentt;
                    else if (tnext < MAX_SPAN_COUNT)
                        tnext = MAX_SPAN_COUNT;	// guard against round-off error on <0 steps

                    sstep = (snext - s) / MAX_SPAN_COUNT;
                    tstep = (tnext - t) / MAX_SPAN_COUNT;
                }
                else
                {
                    // calculate s/z, t/z, zi->fixed s and t at last pixel in span (so
                    // can't step off polygon), clamp, calculate s and t steps across
                    // span by division, biasing steps low so we don't run off the
                    // texture
                    spancountminus1 = (float) (spancount - 1);
                    sdivz += _g->d_sdivzstepu * spancountminus1;
                    tdivz += _g->d_tdivzstepu * spancountminus1;
                    zi += _g->d_zistepu * spancountminus1;
                    z = (float) 0x10000 / zi;	// prescale to 16.16 fixed-point
                    snext = (int) (sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT)
                        snext = MAX_SPAN_COUNT;	// prevent round-off error on <0 steps from
                    //  from causing overstepping & running off the
                    //  edge of the texture

                    tnext = (int) (tdivz * z) + _g->tadjust;
                    if (tnext > _g->bbextentt)
                        tnext = _g->bbextentt;
                    else if (tnext < MAX_SPAN_COUNT)
                        tnext = MAX_SPAN_COUNT;	// guard against round-off error on <0 steps

                    if (spancount > 1)
                    {
                        sstep = (snext - s) / (spancount - 1);
                        tstep = (tnext - t) / (spancount - 1);
                    }
                }
                if (!loaded)
                {
                    extMemWaitAsynchDataRead();
                    loaded = 1;
                }
#define UNROLL_SPRITE_LOOP 1
#if UNROLL_SPRITE_LOOP
                switch (spancount)
                {
                    // next-hack: have to put both fall through and no break comments to shut off CDT and compiler warnings.
                    case 8:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 7:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 6:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 5:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 4:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 3:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 2:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                    case 1:
                        drawSpritePixel();
                        /* fall through */
                        /* no break */
                }
#else
        do
        {
          btemp = *(pbase + (s >> 16) + (t >> 16) * _g->cachewidth);
          if (btemp != 255)
          {
            if (*pz <= (izi >> 16))
            {
              *pz = izi >> 16;
              *pdest = btemp;
            }
          }
          izi += izistep;
          pdest++;
          pz++;
          s += sstep;
          t += tstep;
        } while (--spancount > 0);
#endif
                s = snext;
                t = tnext;

            }
            while (count > 0);
        }
        pspan++;

    }
    while (pspan->count != DS_SPAN_LIST_END);
}

#endif

/*
 =====================
 D_SpriteScanLeftEdge
 =====================
 */
void D_SpriteScanLeftEdge(void)
{
    int i, v, itop, ibottom, lmaxindex;
    emitpoint_t *pvert, *pnext;
    sspan_t *pspan;
    float du, dv, vtop, vbottom, slope;
    fixed16_t u, u_step;

    pspan = _g->sprite_spans;
    i = _g->minindex;
    if (i == 0)
        i = r_spritedesc.nump;

    lmaxindex = _g->maxindex;
    if (lmaxindex == 0)
        lmaxindex = r_spritedesc.nump;

    vtop = ceilf_m(r_spritedesc.pverts[i].v);

    do
    {
        pvert = &r_spritedesc.pverts[i];
        pnext = pvert - 1;

        vbottom = ceilf_m(pnext->v);

        if (vtop < vbottom)
        {
            du = pnext->u - pvert->u;
            dv = pnext->v - pvert->v;
            slope = du / dv;
            u_step = (int) (slope * 0x10000);
            // adjust u to ceil the integer portion
            u = (int) ((pvert->u + (slope * (vtop - pvert->v))) * 0x10000) + (0x10000 - 1);
            itop = (int) vtop;
            ibottom = (int) vbottom;

            for (v = itop; v < ibottom; v++)
            {
                pspan->u = u >> 16;
                pspan->v = v;
                u += u_step;
                pspan++;
            }
        }

        vtop = vbottom;

        i--;
        if (i == 0)
            i = r_spritedesc.nump;

    }
    while (i != lmaxindex);
}

/*
 =====================
 D_SpriteScanRightEdge
 =====================
 */
void D_SpriteScanRightEdge(void)
{
    int i, v, itop, ibottom;
    emitpoint_t *pvert, *pnext;
    sspan_t *pspan;
    float du, dv, vtop, vbottom, slope, uvert, unext, vvert, vnext;
    fixed16_t u, u_step;

    pspan = _g->sprite_spans;
    i = _g->minindex;

    vvert = r_spritedesc.pverts[i].v;
    if (vvert < _g->r_refdef.fvrecty_adj)
        vvert = _g->r_refdef.fvrecty_adj;
    if (vvert > _g->r_refdef.fvrectbottom_adj)
        vvert = _g->r_refdef.fvrectbottom_adj;

    vtop = ceilf_m(vvert);

    do
    {
        pvert = &r_spritedesc.pverts[i];
        pnext = pvert + 1;

        vnext = pnext->v;
        if (vnext < _g->r_refdef.fvrecty_adj)
            vnext = _g->r_refdef.fvrecty_adj;
        if (vnext > _g->r_refdef.fvrectbottom_adj)
            vnext = _g->r_refdef.fvrectbottom_adj;

        vbottom = ceilf_m(vnext);

        if (vtop < vbottom)
        {
            uvert = pvert->u;
            if (uvert < _g->r_refdef.fvrectx_adj)
                uvert = _g->r_refdef.fvrectx_adj;
            if (uvert > _g->r_refdef.fvrectright_adj)
                uvert = _g->r_refdef.fvrectright_adj;

            unext = pnext->u;
            if (unext < _g->r_refdef.fvrectx_adj)
                unext = _g->r_refdef.fvrectx_adj;
            if (unext > _g->r_refdef.fvrectright_adj)
                unext = _g->r_refdef.fvrectright_adj;

            du = unext - uvert;
            dv = vnext - vvert;
            slope = du / dv;
            u_step = (int) (slope * 0x10000);
            // adjust u to ceil the integer portion
            u = (int) ((uvert + (slope * (vtop - vvert))) * 0x10000) + (0x10000 - 1);
            itop = (int) vtop;
            ibottom = (int) vbottom;

            for (v = itop; v < ibottom; v++)
            {
                pspan->count = (u >> 16) - pspan->u;
                u += u_step;
                pspan++;
            }
        }

        vtop = vbottom;
        vvert = vnext;

        i++;
        if (i == r_spritedesc.nump)
            i = 0;

    }
    while (i != _g->maxindex);

    pspan->count = DS_SPAN_LIST_END;	// mark the end of the span list
}

/*
 =====================
 D_SpriteCalculateGradients
 =====================
 */
void D_SpriteCalculateGradients(void)
{
    vec3_t p_normal, p_saxis, p_taxis, p_temp1;
    float distinv;

    TransformVector(r_spritedesc.vpn, p_normal);
    TransformVector(r_spritedesc.vright, p_saxis);
    TransformVector(r_spritedesc.vup, p_taxis);
    VectorInverse(p_taxis);

    distinv = 1.0f / (-DotProduct(_g->modelorg, r_spritedesc.vpn));

    _g->d_sdivzstepu = p_saxis[0] * xscaleinv;
    _g->d_tdivzstepu = p_taxis[0] * xscaleinv;

    _g->d_sdivzstepv = -p_saxis[1] * yscaleinv;
    _g->d_tdivzstepv = -p_taxis[1] * yscaleinv;

    _g->d_zistepu = p_normal[0] * xscaleinv * distinv;
    _g->d_zistepv = -p_normal[1] * yscaleinv * distinv;

    _g->d_sdivzorigin = p_saxis[2] - xcenter * _g->d_sdivzstepu -
    ycenter * _g->d_sdivzstepv;
    _g->d_tdivzorigin = p_taxis[2] - xcenter * _g->d_tdivzstepu -
    ycenter * _g->d_tdivzstepv;
    _g->d_ziorigin = p_normal[2] * distinv - xcenter * _g->d_zistepu -
    ycenter * _g->d_zistepv;

    TransformVector(_g->modelorg, p_temp1);

    _g->sadjust = ((fixed16_t) (DotProduct (p_temp1, p_saxis) * 0x10000 + 0.5f)) - (-(_g->cachewidth >> 1) << 16);
    _g->tadjust = ((fixed16_t) (DotProduct (p_temp1, p_taxis) * 0x10000 + 0.5f)) - (-(_g->sprite_height >> 1) << 16);

// -1 (-epsilon) so we never wander off the edge of the texture
    _g->bbextents = (_g->cachewidth << 16) - 1;
    _g->bbextentt = (_g->sprite_height << 16) - 1;
}

/*
 =====================
 D_DrawSprite
 =====================
 */
void D_DrawSprite(void)
{
    int i, nump;
    float ymin, ymax;
    emitpoint_t *pverts;
    sspan_t spans[MAXHEIGHT + 1];

    _g->sprite_spans = spans;

// find the top and bottom vertices, and make sure there's at least one scan to
// draw
    ymin = 999999.9f;
    ymax = -999999.9f;
    pverts = r_spritedesc.pverts;

    for (i = 0; i < r_spritedesc.nump; i++)
    {
        if (pverts->v < ymin)
        {
            ymin = pverts->v;
            _g->minindex = i;
        }

        if (pverts->v > ymax)
        {
            ymax = pverts->v;
            _g->maxindex = i;
        }

        pverts++;
    }

    ymin = ceilf_m(ymin);
    ymax = ceilf_m(ymax);

    if (ymin >= ymax)
        return;		// doesn't cross any scans at all

    _g->cachewidth = r_spritedesc.pspriteframe->width;
    _g->sprite_height = r_spritedesc.pspriteframe->height;
    _g->cacheblock = (byte*) &r_spritedesc.pspriteframe->pixels[0];
#if !SPRITE_IN_INTERNAL_FLASH
#if ASYNCH_LOAD_SPRITE
    _g->cacheblock = extMemStartAsynchDataRead((uint32_t) _g->cacheblock, getTextureCacheBuffer(), (_g->cachewidth * _g->sprite_height + 3) & ~3);
#endif
#endif
// copy the first vertex to the last vertex, so we don't have to deal with
// wrapping
    nump = r_spritedesc.nump;
    pverts = r_spritedesc.pverts;
    pverts[nump] = pverts[0];

    D_SpriteCalculateGradients();
    D_SpriteScanLeftEdge();
    D_SpriteScanRightEdge();
    D_SpriteDrawSpans(_g->sprite_spans);
}

