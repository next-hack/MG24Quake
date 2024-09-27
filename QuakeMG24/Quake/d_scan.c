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
// d_scan.c
//
// Portable C scan-level rasterization code, all pixel depths.
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"

static unsigned char *r_turb_pbase, *r_turb_pdest;
static fixed16_t r_turb_s, r_turb_t, r_turb_sstep, r_turb_tstep;
static const int *r_turb_turb;
static int r_turb_spancount;

static inline void D_DrawTurbulent8Span(int r_turb_spancount, int tstep, int sstep);

/*
 =============
 D_WarpScreen

 // this performs a slight compression of the screen at the same time as
 // the sine warp, to keep the edges from wrapping
 =============
 */
void D_WarpScreen(void)
{
#if ORIGINAL_IMPLEMENTATION
	int		w, h;
	int		u,v;
	byte	*dest;
	int		*turb;
	int		*col;
	byte	**row;
	byte	*rowptr[MAXHEIGHT+(AMP2*2)];
	int		column[MAXWIDTH+(AMP2*2)];
	float	wratio, hratio;
	w = _g->r_refdef.vrect.width;
	h = _g->r_refdef.vrect.height;

	wratio = w / (float)scr_vrect.width;
	hratio = h / (float)scr_vrect.height;
// next-hack: hratio=wratio = 1
	for (v=0 ; v<scr_vrect.height+AMP2*2 ; v++)
	{
		rowptr[v] = _g->d_viewbuffer + (_g->r_refdef.vrect.y * screenwidth) +
				 (screenwidth * (int)((float)v * hratio * h / (h + AMP2 * 2)));
	}

	for (u=0 ; u<scr_vrect.width+AMP2*2 ; u++)
	{
		column[u] = _g->r_refdef.vrect.x +
				(int)((float)u * wratio * w / (w + AMP2 * 2));
	}

	turb = intsintable + ((int)(cl.time*SPEED)&(CYCLE-1));
	dest = vid.buffer + scr_vrect.y * vid.rowbytes + scr_vrect.x;

	for (v=0 ; v<scr_vrect.height ; v++, dest += vid.rowbytes)
	{
		col = &column[turb[v]];
		row = &rowptr[v];

		for (u=0 ; u<scr_vrect.width ; u+=4)
		{
			dest[u+0] = row[turb[u+0]][col[u+0]];
			dest[u+1] = row[turb[u+1]][col[u+1]];
			dest[u+2] = row[turb[u+2]][col[u+2]];
			dest[u+3] = row[turb[u+3]][col[u+3]];
		}
	}
#elif 1
    int w, h;
    int u, v;
    byte *dest;
    byte *turb;
    short *col;
    byte **row;
    byte *rowptr[MAXHEIGHT + (AMP2 * 2)];
    short column[MAXWIDTH + (AMP2 * 2)];

    w = _g->r_refdef.vrect.width;
    h = _g->r_refdef.vrect.height;

    uint64_t *src = (uint64_t*) vid.buffer;
    uint64_t *dst = (uint64_t*) d_zbuffer;
    // copy everything to the Z-buffer, now unused.
    for (int p = 0; p < SCREEN_WIDTH * DRAW_BUFFER_HEIGHT / 8; p++)
    {
        *dst++ = *src++;
    }
    float hr = (float) h / (h + AMP2 * 2);
    for (v = 0; v < scr_vrect.height + AMP2 * 2; v++)
    {
        rowptr[v] = (byte*) d_zbuffer + ((int) ((float) v * hr)) * SCREEN_WIDTH;
    }
    float wr = (float) w / (w + AMP2 * 2);
    for (u = 0; u < scr_vrect.width + AMP2 * 2; u++)
    {
        column[u] = (int) ((float) u * wr);
    }
    // copy to RAM because RAM access is much faster than rom
    byte *ramIntSinTable = (byte*) d_zbuffer + SCREEN_WIDTH * DRAW_BUFFER_HEIGHT;
    Q_memcpy(ramIntSinTable, intsintable, (sizeof(intsintable) + 3) & ~3);

    turb = ramIntSinTable + ((int) (_g->cl.time * SPEED) & (CYCLE - 1));
    dest = vid.buffer;

    for (v = 0; v < scr_vrect.height; v++/*, dest += SCREEN_WIDTH*/)
    {

        col = &column[turb[v]];
        row = &rowptr[v];

        for (u = 0; u < SCREEN_WIDTH; u += 8)
        {
            uint32_t pix;
            pix = row[turb[u + 0]][col[u + 0]];
            pix |= row[turb[u + 1]][col[u + 1]] << 8;
            pix |= row[turb[u + 2]][col[u + 2]] << 16;
            pix |= row[turb[u + 3]][col[u + 3]] << 24;
            *((uint32_t*) (dest)) = pix;

            pix = row[turb[u + 4]][col[u + 4]];
            pix |= row[turb[u + 5]][col[u + 5]] << 8;
            pix |= row[turb[u + 6]][col[u + 6]] << 16;
            pix |= row[turb[u + 7]][col[u + 7]] << 24;
            *((uint32_t*) (dest + 4)) = pix;
            dest += 8;
        }
    }
#else
	int		w, h;
	int		u,v;
	byte	*dest;
	byte	*turb;
	short	*col;
	byte	**rowp;
	byte	*rowptr[MAXHEIGHT+(AMP2*2)];

	short		column[MAXWIDTH+(AMP2*2)];

	w = _g->r_refdef.vrect.width;
	h = _g->r_refdef.vrect.height;
    // create column and row translation tables
    // take also into account that the screen is enlarged, to take into account the size of
    // wave

	for (u=0 ; u<scr_vrect.width+AMP2 * 2; u++)
	{
		column[u] = (int)((float)u * w / (w + AMP2 * 2));
	}

	turb = intsintable + ((int)(_g->cl.time*SPEED)&(CYCLE-1));
	dest = vid.buffer;
    int rowsCopied;
    #define BACKROWS 16
    byte backupRows[BACKROWS][320];
    for (rowsCopied = 0; rowsCopied < BACKROWS/2; rowsCopied ++)
    {
        memcpy(backupRows[rowsCopied % BACKROWS], _g->d_viewbuffer + rowsCopied * screenwidth, screenwidth);
    }
	for (v=0 ; v < scr_vrect.height + AMP2 * 2 ; v++)
	{
		rowptr[v] = backupRows [(int)((float)v * h / (h + AMP2 * 2)) % BACKROWS];
    }

	for (v=0 ; v<scr_vrect.height ; v++, dest += vid.rowbytes)
	{
		col = &column[turb[v]];
		rowp = &rowptr[v];

		for (u=0 ; u<scr_vrect.width ; u+=4)
		{
			dest[u+0] = rowp[turb[u+0]][col[u+0] ];
			dest[u+1] = rowp[turb[u+1]][col[u+1] ];
			dest[u+2] = rowp[turb[u+2]][col[u+2] ];
			dest[u+3] = rowp[turb[u+3]][col[u+3] ];
		}
        if (rowsCopied < v<scr_vrect.height)
        {
            memcpy(backupRows[rowsCopied % BACKROWS], _g->d_viewbuffer + rowsCopied * screenwidth, screenwidth);
            rowsCopied++;
        }
	}
#endif
}

#if	!id386

/*
 =============
 D_DrawTurbulent8Span
 =============
 */
static inline void D_DrawTurbulent8Span(int r_turb_spancount, int r_turb_sstep, int r_turb_tstep)
{
#define LETS_TRY_TO_OPTIMIZE 0
#if LETS_TRY_TO_OPTIMIZE
  unsigned  int sturb, tturb;
  unsigned int local_r_turb_s = r_turb_s << (16 - 7);   // shift so that we don't have to do " & (CYCLE-1) "
  unsigned int local_r_turb_t = r_turb_t << (16 - 7);   //
  r_turb_sstep <<= 16 - 7;
  r_turb_tstep <<= 16 - 7;
  do
  {
    sturb = ((local_r_turb_s + r_turb_turb[local_r_turb_t >> (32 - 7)]) >> (32 - 7)) & 63;
    tturb = ((local_r_turb_t + r_turb_turb[local_r_turb_s >> (32 - 7)]) >> (32 - 7)) & 63;
    *r_turb_pdest++ = *(r_turb_pbase + (tturb << 6) + sturb);
    local_r_turb_s += r_turb_sstep;
    local_r_turb_t += r_turb_tstep;
  } while (--r_turb_spancount > 0);
#elif 1
    int sturb, tturb;

    unsigned int local_r_turb_s = r_turb_s;
    unsigned int local_r_turb_t = r_turb_t;
    int doubleSpancount = r_turb_spancount >> 1;
    while (doubleSpancount--)
    {
        sturb = ((local_r_turb_s + r_turb_turb[(local_r_turb_t >> 16) & (CYCLE - 1)]) >> 16) & 63;
        tturb = ((local_r_turb_t + r_turb_turb[(local_r_turb_s >> 16) & (CYCLE - 1)]) >> 16) & 63;
        *r_turb_pdest++ = *(r_turb_pbase + (tturb << 6) + sturb);
        local_r_turb_s += r_turb_sstep;
        local_r_turb_t += r_turb_tstep;
        sturb = ((local_r_turb_s + r_turb_turb[(local_r_turb_t >> 16) & (CYCLE - 1)]) >> 16) & 63;
        tturb = ((local_r_turb_t + r_turb_turb[(local_r_turb_s >> 16) & (CYCLE - 1)]) >> 16) & 63;
        *r_turb_pdest++ = *(r_turb_pbase + (tturb << 6) + sturb);
        local_r_turb_s += r_turb_sstep;
        local_r_turb_t += r_turb_tstep;

    }
    if (r_turb_spancount & 1)
    {
        sturb = ((local_r_turb_s + r_turb_turb[(local_r_turb_t >> 16) & (CYCLE - 1)]) >> 16) & 63;
        tturb = ((local_r_turb_t + r_turb_turb[(local_r_turb_s >> 16) & (CYCLE - 1)]) >> 16) & 63;
        *r_turb_pdest++ = *(r_turb_pbase + (tturb << 6) + sturb);
    }

#else
	do
	{
		sturb = ((r_turb_s + r_turb_turb[(r_turb_t >> 16) & (CYCLE-1)]) >> 16) & 63;
		tturb = ((r_turb_t + r_turb_turb[(r_turb_s >> 16) & (CYCLE-1)]) >> 16) & 63;
		*r_turb_pdest++ = *(r_turb_pbase + (tturb << 6) + sturb);
		r_turb_s += r_turb_sstep;
		r_turb_t += r_turb_tstep;
	} while (--r_turb_spancount > 0);
#endif
}

#endif	// !id386

/*
 =============
 Turbulent8
 =============
 */
#define NO_FIXED_BBEXTENT 1
void Turbulent8(espan_t *pspan)
{
    int count;
    fixed16_t snext, tnext;
    float sdivz, tdivz, zi, z, du, dv;
    float sdivz16stepu, tdivz16stepu, zi16stepu;

    r_turb_turb = sintable + ((int) (_g->cl.time * SPEED) & (CYCLE - 1));

    r_turb_sstep = 0; // keep compiler happy
    r_turb_tstep = 0; // ditto

    r_turb_pbase = (unsigned char*) _g->cacheblock;

    sdivz16stepu = _g->d_sdivzstepu * 16;
    tdivz16stepu = _g->d_tdivzstepu * 16;
    zi16stepu = _g->d_zistepu * 16;
#if WIN32
            if (_g->bbextents == 64 || _g->bbextentt == 64)
                    {
                        printf("TURB EXTENTS: %d %d\r\n", _g->bbextents, _g->bbextentt);
                        _g->bbextents  = 0x3FFFFFFF;
                        _g->bbextentt  = 0x3FFFFFFF;
                    }
                     _g->bbextents  = 0x3FFFFFFF;
                        _g->bbextentt  = 0x3FFFFFFF;
        #endif // WIN3
    do
    {
#if ESPANS_HAVE_V
    r_turb_pdest = (unsigned char *)((byte *)_g->d_viewbuffer + (screenwidth * pspan->v) + pspan->u);
    du = (float)pspan->u;
    dv = (float)pspan->v;

#else
        int spanIndex = pspan - _g->basespan_p;
        r_turb_pdest = (unsigned char*) ((byte*) _g->d_viewbuffer + (screenwidth * _g->basespanV_p[spanIndex]) + pspan->u);
        du = (float) pspan->u;
        dv = (float) _g->basespanV_p[spanIndex];

#endif

        count = pspan->count;

        // calculate the initial s/z, t/z, 1/z, s, and t and clamp

        sdivz = _g->d_sdivzorigin + dv * _g->d_sdivzstepv + du * _g->d_sdivzstepu;
        tdivz = _g->d_tdivzorigin + dv * _g->d_tdivzstepv + du * _g->d_tdivzstepu;
        zi = _g->d_ziorigin + dv * _g->d_zistepv + du * _g->d_zistepu;
        z = (float) 0x10000 / zi;  // prescale to 16.16 fixed-point

        r_turb_s = (int) (sdivz * z) + _g->sadjust;
#if NO_FIXED_BBEXTENT
        if (r_turb_s > _g->bbextents)
            r_turb_s = _g->bbextents;
#else
    if (r_turb_s > 0x3FFFFFFF)
      r_turb_s = 0x3FFFFFFF;
#endif
        else if (r_turb_s < 0)
            r_turb_s = 0;

        r_turb_t = (int) (tdivz * z) + _g->tadjust;
#if NO_FIXED_BBEXTENT
        if (r_turb_t > _g->bbextentt)
            r_turb_t = _g->bbextentt;
#else
    if (r_turb_t > 0x3FFFFFFF)
      r_turb_t = 0x3FFFFFFF;
#endif
        else if (r_turb_t < 0)
            r_turb_t = 0;

        do
        {
            // calculate s and t at the far end of the span
            if (count >= 16)
                r_turb_spancount = 16;
            else
                r_turb_spancount = count;

            count -= r_turb_spancount;

            if (count)
            {
                // calculate s/z, t/z, zi->fixed s and t at far end of span,
                // calculate s and t steps across span by shifting
                sdivz += sdivz16stepu;
                tdivz += tdivz16stepu;
                zi += zi16stepu;
                z = (float) 0x10000 / zi;  // prescale to 16.16 fixed-point

                snext = (int) (sdivz * z) + _g->sadjust;
#if NO_FIXED_BBEXTENT
                if (snext > _g->bbextents)
                    snext = _g->bbextents;
#else
        if (snext > 0x3FFFFFFF)
          snext = 0x3FFFFFFF;
#endif
                else if (snext < 16)
                    snext = 16; // prevent round-off error on <0 steps from
                //  from causing overstepping & running off the
                //  edge of the texture

                tnext = (int) (tdivz * z) + _g->tadjust;
#if NO_FIXED_BBEXTENT
                if (tnext > _g->bbextentt)
                    tnext = _g->bbextentt;
#else
        if (tnext > 0x3FFFFFFF)
          tnext = 0x3FFFFFFF;
#endif
                else if (tnext < 16)
                    tnext = 16; // guard against round-off error on <0 steps

                r_turb_sstep = (snext - r_turb_s) >> 4;
                r_turb_tstep = (tnext - r_turb_t) >> 4;
            }
            else
            {
                // calculate s/z, t/z, zi->fixed s and t at last pixel in span (so
                // can't step off polygon), clamp, calculate s and t steps across
                // span by division, biasing steps low so we don't run off the
                // texture
                float spancountminus1 = (float) (r_turb_spancount - 1);
                sdivz += _g->d_sdivzstepu * spancountminus1;
                tdivz += _g->d_tdivzstepu * spancountminus1;
                zi += _g->d_zistepu * spancountminus1;
                z = (float) 0x10000 / zi;  // prescale to 16.16 fixed-point
                snext = (int) (sdivz * z) + _g->sadjust;
#if NO_FIXED_BBEXTENT
                if (snext > _g->bbextents)
                    snext = _g->bbextents;
#else
        if (snext > 0x3FFFFFFF)
          snext = 0x3FFFFFFF;
#endif
                else if (snext < 16)
                    snext = 16; // prevent round-off error on <0 steps from
                //  from causing overstepping & running off the
                //  edge of the texture

                tnext = (int) (tdivz * z) + _g->tadjust;
#if NO_FIXED_BBEXTENT
                if (tnext > _g->bbextentt)
                    tnext = _g->bbextentt;
#else
        if (tnext > 0x3FFFFFFF)
          tnext = 0x3FFFFFFF;
#endif
                else if (tnext < 16)
                    tnext = 16; // guard against round-off error on <0 steps

                if (r_turb_spancount > 1)
                {
                    r_turb_sstep = fixedApproxDiv256(snext - r_turb_s, r_turb_spancount - 1); //  (snext - r_turb_s) / (r_turb_spancount - 1);
                    r_turb_tstep = fixedApproxDiv256(tnext - r_turb_t, r_turb_spancount - 1); // (tnext - r_turb_t) / (r_turb_spancount - 1);
                }
            }

            r_turb_s = r_turb_s & ((CYCLE << 16) - 1);
            r_turb_t = r_turb_t & ((CYCLE << 16) - 1);

            D_DrawTurbulent8Span(r_turb_spancount, r_turb_sstep, r_turb_tstep);

            r_turb_s = snext;
            r_turb_t = tnext;

        }
        while (count > 0);
#if OLD_SPAN_METHOD
  } while ((pspan = pspan->pnext) != NULL);
#else
    }
    while ((pspan = getNextSpan(pspan, 1)) != NULL);
#endif
}

#if	!id386
#define TEST_SIMD 1
#define SPAN_PRECISION  6
/*
 =============
 D_DrawSpans8
 =============
 */
extern surfDrawData_t sdd;
#define mipMask(m) ((1 << (4 - m)) - 1)
#define mipShift(m) (4 - m)
#if !WIN32
#define USE_ASM_CODE 1
#endif
#if USE_ASM_CODE
#define MIP_SHIFTVALUE_STR(miplvl)   XSTR(4 - miplvl)
#define MIP_MASK_STR(miplvl) XSTR( (1 << (4 - miplvl) - 1) )
#if TEST_SIMD
#define TEST_TWO_PIX 1
#if TEST_TWO_PIX
#define drawSurfSpanPower2(miplvl) \
      __ASM volatile ( \
          ".align(2)\n\t" \
          /*prepare word for sstep*/ \
          "ASR %[sstep], %[sstep], #(16 - " XSTR(SPAN_PRECISION) ")\n\t" \
          /*Pack sstep and tstep halfwords*/ \
          "PKHBT %[sstep], %[sstep], %[tstep], LSL #" XSTR(SPAN_PRECISION) "\n\t" \
          /*prepare word for s*/ \
          "ASR %[s], %[s], #(16 - " XSTR(SPAN_PRECISION) ")\n\t" \
          /*Pack sstep and tstep halfwords*/ \
          "PKHBT %[s], %[s], %[t], LSL #" XSTR(SPAN_PRECISION) "\n\t" /*in s now we have both s and t with SPAN_PRECISION fractional part*/\
          "LDR.W r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR.w r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load lightwidth. We are using %[t] as it is free*/ \
          "LDR %[t], [r11, %[lightwidthOffset]]\n\t"  /*t is now lightwidth*/\
          "LDR r8, [r11, %[textureWidthOr1Offset]]\n\t" \
          "MOV %[tstep], #0x001F001F\n\t"\
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          /*First we calculate the integer part of the st. It will be used also later so we save in tstep, which is free*/ \
          /* calculate hblock and vblock in the same word*/ \
          "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  \
          "TST %[spancount], #1\n\t"  /*check for odd number of pixels*/ \
          "ADD %[spancount], %[spancount], %[pdest]\n\t" /* now spancount is the end address + 1*/ \
          "BEQ loop_span2%=\n\t"  /*skip this first part if even*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLAD r11, %[t],  r11, r12\n\t" \
          "UBFX r9, %[s], #(16 +  "  XSTR(SPAN_PRECISION)  " ), #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          "RSB r9, r9, r9, LSL #16\n\t" /*in R9 x (top) -x (bottom)*/\
          "ADD r9, r9,  #((" MIP_MASK_STR(miplvl) " + 1))\n\t" \
          "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS */ \
          "UBFX r9, %[s], #" XSTR(SPAN_PRECISION)", #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* multiply and accumulate the other term*/ \
          "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
          /* integer part of s, and t are multiplied by, respectively 1 and twidth, and added together and to the source.*/ \
          "AND r9, %[tWidthHeightMask], %[s], LSR #" XSTR(SPAN_PRECISION)"\n\t"  \
          "SMLAD r9, r9, r8, %[source]\n\t" \
          /* in r11 we got Light. But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r9]\n\t"           /* read pixel*/ \
          "SADD16 %[s], %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  /*this is for the next pixel!*/\
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[spancount], %[pdest]\n\t" /*note: spancount is now the end address + 1*/ \
          "BLS endLoop%=\n\t" \
          "loop_span2%=:\n\t" \
           "SMLAD r11, %[t],  r11, r12\n\t" \
           "UBFX r9, %[s], #(16 +  "  XSTR(SPAN_PRECISION)  " ), #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
           /* compute deltaT and reverse deltaT and pack*/ \
           "LDM r11, {r10, r11}\n\t" \
           /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
           "RSB r9, r9, r9, LSL #16\n\t" /*in R9 x (top) -x (bottom)*/\
           "ADD r9, r9,  #((" MIP_MASK_STR(miplvl) " + 1))\n\t" \
           "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
           "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
           /* compute deltaS */ \
           "UBFX r9, %[s], #" XSTR(SPAN_PRECISION)", #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
           /* multiply light right by deltaS*/ \
           "MUL r11, r9, r11\n\t" \
           /* multiply and accumulate the other term*/ \
           "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
           "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
           /* integer part of s, and t are multiplied by, respectively 1 and twidth, and added together and to the source.*/ \
           "AND r9, %[tWidthHeightMask], %[s], LSR #" XSTR(SPAN_PRECISION)"\n\t"  \
           "SMLAD r9, r9, r8, %[source]\n\t" \
           /* in r11 we got Light. But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
           "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
           /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
           "LDRB r9, [r9]\n\t"           /* read pixel*/ \
           "SADD16 %[s], %[s], %[sstep]\n\t" \
           "ADD r9, r9, r11, LSL #8\n\t" \
           "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
           "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  /*this is for the next pixel!*/\
           "STRB r9, [%[pdest]], #1\n\t" \
           "SMLAD r11, %[t],  r11, r12\n\t" \
           "UBFX r9, %[s], #(16 +  "  XSTR(SPAN_PRECISION)  " ), #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
           /* compute deltaT and reverse deltaT and pack*/ \
           "LDM r11, {r10, r11}\n\t" \
           /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
           "RSB r9, r9, r9, LSL #16\n\t" /*in R9 x (top) -x (bottom)*/\
           "ADD r9, r9,  #((" MIP_MASK_STR(miplvl) " + 1))\n\t" \
           "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
           "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
           /* compute deltaS */ \
           "UBFX r9, %[s], #" XSTR(SPAN_PRECISION)", #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
           /* multiply light right by deltaS*/ \
           "MUL r11, r9, r11\n\t" \
           /* multiply and accumulate the other term*/ \
           "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
           "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
           /* integer part of s, and t are multiplied by, respectively 1 and twidth, and added together and to the source.*/ \
           "AND r9, %[tWidthHeightMask], %[s], LSR #" XSTR(SPAN_PRECISION)"\n\t"  \
           "SMLAD r9, r9, r8, %[source]\n\t" \
           /* in r11 we got Light. But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
           "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
           /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
           "LDRB r9, [r9]\n\t"           /* read pixel*/ \
           "SADD16 %[s], %[s], %[sstep]\n\t" \
           "ADD r9, r9, r11, LSL #8\n\t" \
           "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
           "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  /*this is for the next pixel!*/\
           "STRB r9, [%[pdest]], #1\n\t" \
           "CMP  %[spancount], %[pdest]\n\t" /*note: spancount is now the end address + 1*/ \
           "BHI loop_span2%=\n\t" \
            "endLoop%=:\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [spancount] "r"  (spancount ), \
            [tWidthHeightMask] "r" (sdd.tWidthHeightMask), \
            [textureWidthOr1Offset] "I" (offsetof(surfDrawData_t, tWidthOr1)), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8");

#else
#define drawSurfSpanPower2(miplvl) \
      __ASM volatile ( \
          ".align(2)\n\t" \
          "LDR.W r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR.w r12, [r11, %[pblocklightOffset]]\n\t"\
          /*prepare word for sstep*/ \
          "ASR %[sstep], %[sstep], #(16 - " XSTR(SPAN_PRECISION) ")\n\t" \
          /*Pack sstep and tstep halfwords*/ \
          "PKHBT %[sstep], %[sstep], %[tstep], LSL #" XSTR(SPAN_PRECISION) "\n\t" \
          /*prepare word for s*/ \
          "ASR %[s], %[s], #(16 - " XSTR(SPAN_PRECISION) ")\n\t" \
          /*Pack sstep and tstep halfwords*/ \
          "PKHBT %[s], %[s], %[t], LSL #" XSTR(SPAN_PRECISION) "\n\t" /*in s now we have both s and t with SPAN_PRECISION fractional part*/\
          /* load lightwidth. We are using %[t] as it is free*/ \
          "LDR %[t], [r11, %[lightwidthOffset]]\n\t"  /*t is now lightwidth*/\
         "LDR r8, [r11, %[textureWidthOr1Offset]]\n\t" \
          "MOV %[tstep], #0x001F001F\n\t"\
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          /*First we calculate the integer part of the st. It will be used also later so we save in tstep, which is free*/ \
          /* calculate hblock and vblock in the same word*/ \
         "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  \
          /* compute s + lightwidthOffset * t*/ \
          "loop_span2%=:\n\t" \
          "SMLAD r11, %[t],  r11, r12\n\t" \
          "UBFX r9, %[s], #(16 +  "  XSTR(SPAN_PRECISION)  " ), #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          "RSB r9, r9, r9, LSL #16\n\t" /*in R9 x (top) -x (bottom)*/\
          "ADD r9, r9,  #((" MIP_MASK_STR(miplvl) " + 1))\n\t" \
          "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS */ \
          "UBFX r9, %[s], #" XSTR(SPAN_PRECISION)", #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* multiply and accumulate the other term*/ \
          "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
          /* integer part of s, and t are multiplied by, respectively 1 and twidth, and added together and to the source.*/ \
          "AND r9, %[tWidthHeightMask], %[s], LSR #" XSTR(SPAN_PRECISION)"\n\t"  \
          "SMLAD r9, r9, r8, %[source]\n\t" \
          /* in r11 we got Light. But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r9]\n\t"           /* read pixel*/ \
          "SADD16 %[s], %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "AND r11, %[tstep], %[s], ASR #("MIP_SHIFTVALUE_STR(miplvl) "+"  XSTR(SPAN_PRECISION)  ")\n\t"  /*this is for the next pixel!*/\
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[pdestEnd], %[pdest]\n\t" \
          "BHI loop_span2%=\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [pdestEnd] "r"  (pdest + spancount ), \
            [tWidthHeightMask] "r" (sdd.tWidthHeightMask), \
            [textureWidthOr1Offset] "I" (offsetof(surfDrawData_t, tWidthOr1)), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8");
#endif
#if TEST_TWO_PIX
#define drawSurfSpan(miplvl) \
      __ASM volatile ( \
          ".align(2)\n\t" \
          "LDR.W r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR.W r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load qcs*/ \
          "VLDR.F32 s0, [r11, %[qcsOffset]]\n\t" \
          /* load qct*/ \
          "VLDR.F32 s1, [r11, %[qctOffset]]\n\t" \
          /* load textureHeight*/ \
          "VLDR.F32 s2, [r11, %[textureHeightOffset]]\n\t" \
           /* load lightwidth*/ \
          "VLDR.F32 s5, [r11, %[lightwidthOffset]]\n\t" \
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT*/ \
          "TST %[spancount], #1\n\t"  /*check for odd number of pixels*/ \
          "ADD %[spancount], %[spancount], %[pdest]\n\t" /* now spancount is the end address + 1*/ \
          "BEQ loop_span2%=\n\t"  /*skip this first part if even*/ \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r8, r8, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "SMUAD r11, r11, r8 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r8 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS and reverse deltaS*/ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* get the coefficient 1/height + 1. Doing it here to save penalties.*/ \
          "VMOV r9, s1\n\t" \
          /* multiply and accumulate the other term*/ \
          "SMLABB r11, r10, r8, r11\n\t" \
          /* get texture height. (Done here because it will be faster)*/ \
          "VMOV r10, s2\n\t" \
          /* multiply the 1/height+1 by t*/ \
          "MUL r8, r9, %[t]\n\t"  /*   "MUL r8, r9\n\t"*/ \
          /* get the coefficient 1/width + 1*/ \
          "VMOV r9, s0\n\t" \
          /* multiply by texture height*/ \
          "UMULL r8, r10, r8, r10\n\t"  /* in r10 the correct t position, i.e. mod TextureHeight*/ \
          /* Now with s*/ \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* multiply the coefficient 1/width + 1 by s+offset*/ \
          "MUL r8, r9, %[s]\n\t"     /*   "MUL r8, r9\n\t"*/ \
          /*calculate Address + yTexture * width*/ \
          "SMLABB r10, r10, %[textureWidth], %[source]\n\t"  /* in r10 the address*/ \
          /* multiply by texture width*/ \
          "UMULL r8, r9, r8, %[textureWidth]\n\t"  /* in r9 the correct s position*/ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10, r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT. This is for next pixel!*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[spancount], %[pdest]\n\t" /*note: spancount is now the end address + 1*/ \
          "BLS endLoop%=\n\t" \
          "loop_span2%=:\n\t" \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r8, r8, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "SMUAD r11, r11, r8 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r8 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS and reverse deltaS*/ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* get the coefficient 1/height + 1. Doing it here to save penalties.*/ \
          "VMOV r9, s1\n\t" \
          /* multiply and accumulate the other term*/ \
          "SMLABB r11, r10, r8, r11\n\t" \
          /* get texture height. (Done here because it will be faster)*/ \
          "VMOV r10, s2\n\t" \
          /* multiply the 1/height+1 by t*/ \
          "MUL r8, r9, %[t]\n\t"  /*   "MUL r8, r9\n\t"*/ \
          /* get the coefficient 1/width + 1*/ \
          "VMOV r9, s0\n\t" \
          /* multiply by texture height*/ \
          "UMULL r8, r10, r8, r10\n\t"  /* in r10 the correct t position, i.e. mod TextureHeight*/ \
          /* Now with s*/ \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* multiply the coefficient 1/width + 1 by s+offset*/ \
          "MUL r8, r9, %[s]\n\t"     /*   "MUL r8, r9\n\t"*/ \
          /*calculate Address + yTexture * width*/ \
          "SMLABB r10, r10, %[textureWidth], %[source]\n\t"  /* in r10 the address*/ \
          /* multiply by texture width*/ \
          "UMULL r8, r9, r8, %[textureWidth]\n\t"  /* in r9 the correct s position*/ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10, r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT. This is for next pixel!*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r8, r8, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "SMUAD r11, r11, r8 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r8 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS and reverse deltaS*/ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* get the coefficient 1/height + 1. Doing it here to save penalties.*/ \
          "VMOV r9, s1\n\t" \
          /* multiply and accumulate the other term*/ \
          "SMLABB r11, r10, r8, r11\n\t" \
          /* get texture height. (Done here because it will be faster)*/ \
          "VMOV r10, s2\n\t" \
          /* multiply the 1/height+1 by t*/ \
          "MUL r8, r9, %[t]\n\t"  /*   "MUL r8, r9\n\t"*/ \
          /* get the coefficient 1/width + 1*/ \
          "VMOV r9, s0\n\t" \
          /* multiply by texture height*/ \
          "UMULL r8, r10, r8, r10\n\t"  /* in r10 the correct t position, i.e. mod TextureHeight*/ \
          /* Now with s*/ \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* multiply the coefficient 1/width + 1 by s+offset*/ \
          "MUL r8, r9, %[s]\n\t"     /*   "MUL r8, r9\n\t"*/ \
          /*calculate Address + yTexture * width*/ \
          "SMLABB r10, r10, %[textureWidth], %[source]\n\t"  /* in r10 the address*/ \
          /* multiply by texture width*/ \
          "UMULL r8, r9, r8, %[textureWidth]\n\t"  /* in r9 the correct s position*/ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10, r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT. This is for next pixel!*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[spancount], %[pdest]\n\t" /*note: spancount is now the end address + 1*/ \
          "BHI loop_span2%=\n\t" \
          "endLoop%=:\n\t"\
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [spancount] "r"  (spancount + 0), \
            [textureWidth] "r" (sdd.r_texture_width), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [qcsOffset] "I" (offsetof(surfDrawData_t, qcs)), \
            [qctOffset] "I" (offsetof(surfDrawData_t, qct)), \
            [textureHeightOffset] "I" (offsetof(surfDrawData_t, r_texture_height)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8", "s0", "s1", "s2", "s5");

#else
#define drawSurfSpan(miplvl) \
      __ASM volatile ( \
          ".align(2)\n\t" \
          "LDR.W r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR.W r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load qcs*/ \
          "VLDR.F32 s0, [r11, %[qcsOffset]]\n\t" \
          /* load qct*/ \
          "VLDR.F32 s1, [r11, %[qctOffset]]\n\t" \
          /* load textureHeight*/ \
          "VLDR.F32 s2, [r11, %[textureHeightOffset]]\n\t" \
           /* load lightwidth*/ \
          "VLDR.F32 s5, [r11, %[lightwidthOffset]]\n\t" \
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT*/ \
          "loop_span2%=:\n\t" \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r8, r8, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "SMUAD r11, r11, r8 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r8 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS and reverse deltaS*/ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* get the coefficient 1/height + 1. Doing it here to save penalties.*/ \
          "VMOV r9, s1\n\t" \
          /* multiply and accumulate the other term*/ \
          "SMLABB r11, r10, r8, r11\n\t" \
          /* get texture height. (Done here because it will be faster)*/ \
          "VMOV r10, s2\n\t" \
          /* multiply the 1/height+1 by t*/ \
          "MUL r8, r9, %[t]\n\t"  /*   "MUL r8, r9\n\t"*/ \
          /* get the coefficient 1/width + 1*/ \
          "VMOV r9, s0\n\t" \
          /* multiply by texture height*/ \
          "UMULL r8, r10, r8, r10\n\t"  /* in r10 the correct t position, i.e. mod TextureHeight*/ \
          /* Now with s*/ \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* multiply the coefficient 1/width + 1 by s+offset*/ \
          "MUL r8, r9, %[s]\n\t"     /*   "MUL r8, r9\n\t"*/ \
          /*calculate Address + yTexture * width*/ \
          "SMLABB r10, r10, %[textureWidth], %[source]\n\t"  /* in r10 the address*/ \
          /* multiply by texture width*/ \
          "UMULL r8, r9, r8, %[textureWidth]\n\t"  /* in r9 the correct s position*/ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10, r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT. This is for next pixel!*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[pdestEnd], %[pdest]\n\t" \
          "BHI loop_span2%=\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [pdestEnd] "r"  (pdest + spancount), \
            [textureWidth] "r" (sdd.r_texture_width), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [qcsOffset] "I" (offsetof(surfDrawData_t, qcs)), \
            [qctOffset] "I" (offsetof(surfDrawData_t, qct)), \
            [textureHeightOffset] "I" (offsetof(surfDrawData_t, r_texture_height)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8", "s0", "s1", "s2", "s5");
#endif
#elif 1
#define drawSurfSpanPower2(miplvl) \
      __ASM volatile ( \
          "LDR r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load lightwidth*/ \
          "VLDR.F32 s5, [r11, %[lightwidthOffset]]\n\t" \
          "LDR r8, [r11, %[textureHeightMaskOffset]]\n\t" \
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT*/ \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          /* compute deltaT and reverse deltaT and pack*/ \
   /*       "RSB r10, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t"*/ \
   /*       "ORR r9, r10, r9, LSL #16\n\t"    */    /* pack the two halfwords*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          "RSB r9, r9, r9, LSL #16\n\t" /*in R9 x (top) -x (bottom)*/\
          "ADD r9, r9,  #((" MIP_MASK_STR(miplvl) " + 1))\n\t" \
          "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS */ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* multiply and accumulate the other term*/ \
          "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
          /* get t >> 16 mod THEIGHT*/ \
          "AND r10, r8, %[t], LSR #16\n\n"   \
          /* t = t + texwidth-1 *t */ \
          "SMLABB r10, %[tWidthMask], r10, r10\n\t"   /*"MLA r10, %[tWidthMask], r10, r10\n\t" these are equivalent for our purpose*/ \
          /* get s >> 16 mod TWIDTH*/ \
          "AND r9, %[tWidthMask], %[s], LSR #16\r\n" \
          /*Now we must do: t*w + s*/  \
          "ADD r9, r10\n\t" \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [%[source], r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[pdestEnd], %[pdest]\n\t" \
          "BHI loop_span%=\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [pdestEnd] "r"  (pdest + spancount), \
            [tWidthMask] "r" (sdd.tWidthMask), \
            [textureHeightMaskOffset] "I" (offsetof(surfDrawData_t, tHeightMask)), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8","s5");
#if 0 // not working for now because of rounding errors
#define drawSurfSpanPower2NoMod(miplvl) \
      __ASM volatile ( \
          "LDR r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load lightwidth. NOTE: IN r8 NOW!*/ \
          "LDR r8, [r11, %[lightwidthOffset]]\n\t" \
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r8, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r10, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r9, r10, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          "SMUAD r11, r11, r9 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r9 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS */ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* multiply and accumulate the other term*/ \
          "RSB r9, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "SMLABB r11, r10, r9, r11\n\t" /* in r11 we got Light shifted*/ \
          /* t =  twidth*t + source */ \
          "ADD r9, %[t], #0x8000\n\t" \
          "SMLABT r10, %[textureWidth], r9, %[source]\n\t"  \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /*Now we add s >> 16 to get the correct pointer*/  \
          "ADD r10, r10, %[s], ASR #16\n\t" \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[pdestEnd], %[pdest]\n\t" \
          "BHI loop_span%=\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [pdestEnd] "r"  (pdest + spancount), \
            [textureWidth] "r" (sdd.r_texture_width), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8","s5");
#endif
#define drawSurfSpan(miplvl) \
      __ASM volatile ( \
          "LDR r11, =sdd\n\t"  /*load sdd structure in temporary reg*/ \
          /* load pblocklight*/ \
          "LDR r12, [r11, %[pblocklightOffset]]\n\t"\
          /* load qcs*/ \
          "VLDR.F32 s0, [r11, %[qcsOffset]]\n\t" \
          /* load qct*/ \
          "VLDR.F32 s1, [r11, %[qctOffset]]\n\t" \
          /* load textureHeight*/ \
          "VLDR.F32 s2, [r11, %[textureHeightOffset]]\n\t" \
           /* load lightwidth*/ \
          "VLDR.F32 s5, [r11, %[lightwidthOffset]]\n\t" \
          "loop_span%=:\n\t" \
          /* calculate Light pointer: s >> 16+miplevel + (t >> 16) * lightwidth*/ \
          "ASR r11, %[s], #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*hblock = s >> 16 >> MIPSHIFT*/ \
          "VMOV r9, s5\n\t"             /* get lightwidth*/ \
          "ASR r10, %[t],  #(16+" MIP_SHIFTVALUE_STR(miplvl) ")\n\t"      /*vblock = t >> 16 >> MIPSHIFT*/ \
          /* compute s + lightwidthOffset * t*/ \
          "SMLABB r11, r10, r9, r11\r\n"       /* now in r11 we have n = hblock + lightwidthOffset * vblock*/ \
          "UBFX r9, %[t], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t" /* deltaT: (t >> 16) & MASK*. Put here because we need to prevent using R11 immediately*/ \
          "ADD r11, r12, r11, lsl #2\n\t"      /* now we have address of blocklight[n] in r11*/ \
          "LDM r11, {r10, r11}\n\t" \
          /* now r10 =  blocklight[n], r11 = blocklight[n + 1] (note: blocklight contains the information of next blocklight row in top hw) */ \
          /* compute deltaT and reverse deltaT and pack*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          "ORR r8, r8, r9, LSL #16\n\t"        /* pack the two halfwords*/ \
          "SMUAD r11, r11, r8 \n\t"            /* dot product to calculate light left*/ \
          "SMUAD r10, r10, r8 \n\t"            /* dot product to calculate light right*/ \
          /* compute deltaS and reverse deltaS*/ \
          "UBFX r9, %[s], #16, #" MIP_SHIFTVALUE_STR(miplvl) "\n\t"      /* (s >> 16) & MASK*/ \
          "RSB r8, r9, #(" MIP_MASK_STR(miplvl) " + 1) \n\t" \
          /* multiply light right by deltaS*/ \
          "MUL r11, r9, r11\n\t" \
          /* get the coefficient 1/height + 1. Doing it here to save penalties.*/ \
          "VMOV r9, s1\n\t" \
          /* multiply and accumulate the other term*/ \
          "SMLABB r11, r10, r8, r11\n\t" \
          /* get texture height. (Done here because it will be faster)*/ \
          "VMOV r10, s2\n\t" \
          /* multiply the 1/height+1 by t*/ \
          "MUL r8, r9, %[t]\n\t"  /*   "MUL r8, r9\n\t"*/ \
          /* get the coefficient 1/width + 1*/ \
          "VMOV r9, s0\n\t" \
          /* multiply by texture height*/ \
          "UMULL r8, r10, r8, r10\n\t"  /* in r10 the correct t position, i.e. mod TextureHeight*/ \
          /* Now with s*/ \
          "ADD %[t], %[tstep]\n\t"  /*placed here to avoid stalling */ \
          /* multiply the coefficient 1/width + 1 by s+offset*/ \
          "MUL r8, r9, %[s]\n\t"     /*   "MUL r8, r9\n\t"*/ \
          /*calculate Address + yTexture * width*/ \
          "SMLABB r10, r10, %[textureWidth], %[source]\n\t"  /* in r10 the address*/ \
          /* multiply by texture width*/ \
          "UMULL r8, r9, r8, %[textureWidth]\n\t"  /* in r9 the correct s position*/ \
          /* in r11 we got Light.But it was not right shifted by MIP_SHIFTVALUE_STR*/ \
          "UBFX r11, r11, #(8 +  " MIP_SHIFTVALUE_STR(miplvl) "), #6\n\t" /*done here to prevent using r9 immediately*/ \
          /* In r10: Address+yTexture*width. In r9 the xTexture position*/ \
          "LDRB r9, [r10, r9]\n\t"           /* read pixel*/ \
          "ADD %[s], %[sstep]\n\t" \
          "ADD r9, r9, r11, LSL #8\n\t" \
          "LDRB r9, [%[colormap], r9]\n\t" /*load pixel from colormap*/ \
          "STRB r9, [%[pdest]], #1\n\t" \
          "CMP  %[pdestEnd], %[pdest]\n\t" \
          "BHI loop_span%=\n\t" \
          : /* OUTPUTS*/ \
            [pdest] "+r"  (pdest), \
            [s] "+r" (s), \
            [t] "+r" (t), \
            [sstep] "+r" (sstep),\
            [tstep] "+r" (tstep) \
          : /* INPUT ONLY*/\
            [colormap] "r" (sdd.colormap), \
            [source] "r" (sdd.r_source), \
            [pdestEnd] "r"  (pdest + spancount), \
            [textureWidth] "r" (sdd.r_texture_width), \
            [lightwidthOffset] "I" (offsetof(surfDrawData_t, r_lightwidth)), \
            [qcsOffset] "I" (offsetof(surfDrawData_t, qcs)), \
            [qctOffset] "I" (offsetof(surfDrawData_t, qct)), \
            [textureHeightOffset] "I" (offsetof(surfDrawData_t, r_texture_height)), \
            [pblocklightOffset] "I" (offsetof(surfDrawData_t, blocklights)) \
          : "cc", "r12", "r11", "r10", "r9", "r8", "s0", "s1", "s2", "s5");
#endif
#endif

#if !PRE_LIGHT_SURFACES
#define OLD_WAY_CALC 1
#if OLD_WAY_CALC
#if !CREATE_DELTA_LIGHT_MAP
#define defineR_GetSurfacePixelForMiplevel(miplevel)                            \
__attribute__((always_inline))  static inline uint8_t R_GetSurfacePixel##miplevel(int s, int t, int st, int tt)               \
{                                                                               \
    uint8_t pix;                                                                \
    int hblock = s >> mipShift(miplevel);                                       \
    int vblock = t >> mipShift(miplevel);                                       \
    BLOCKLIGHT_TYPE * lightptr = sdd.blocklights + hblock + sdd.r_lightwidth * vblock;     \
    int lightUp = ((lightptr[1] - lightptr[0]) >> mipShift(miplevel)) * (s & mipMask(miplevel)) + lightptr[0]; \
    lightptr += sdd.r_lightwidth;                                                   \
    int lightDown = ((lightptr[1] - lightptr[0]) >> mipShift(miplevel)) * (s & mipMask(miplevel)) + lightptr[0]; \
    int light = ((lightDown - lightUp)  >> mipShift(miplevel)) * (t & mipMask(miplevel)) + lightUp; \
    t = t + sdd.r_surf_toffs;                                                               \
    t = t - sdd.r_texture_height * ((t * sdd.r_i_texture_height) >> TFRACSHIFT);              \
    s = (s + sdd.r_surf_soffs);                                                             \
    s = s - sdd.r_texture_width * ((s * sdd.r_i_texture_width) >> TFRACSHIFT);                \
    pix = sdd.r_source[t * sdd.r_texture_width + s];                                            \
    pix = ((unsigned char *)sdd.colormap) [(light & 0xFF00) + pix];                     \
    return pix;                                                                         \
}
#elif  NEW_BILINEAR_INTERPOLATION
#if TEST_SIMD
#define PACK16(s,t) ( ((s)  & 0xFFFF) |  (( (t)  & 0xFFFF) << 16))
#define getS(st) ((int32_t) ((int16_t) ((st) & 0xFFFF)))
#define getT(st) ((int32_t) ((int16_t) ((st) >> 16)))
#if WIN32
static inline uint32_t sadd16(uint32_t a, uint32_t b)
{
    uint16_t sa, sb, ta, tb;
    sa = getS(a);
    sb = getS(b);
    ta = getT(a);
    tb = getT(b);
    //  printf("sa %x, sb %x ta %x tb %x\r\n", sa, sb, ta, tb);
    return PACK16((sa + sb), (ta + tb));
}
#endif
// Hey! This C code is not optimized for speed! This is just to emulate (and test!) what the asm routine does!
#define defineR_GetSurfacePixelForMiplevel(miplevel)                            \
__attribute__((always_inline))  static inline uint8_t R_GetSurfacePixel##miplevel(int ss, int tt)               \
{                                                                               \
    uint8_t pix;                                                                \
    int st = PACK16(ss >> (16 - SPAN_PRECISION), tt >> (16 - SPAN_PRECISION));     \
    int s = getS(st) >> SPAN_PRECISION, t = getT(st) >> SPAN_PRECISION;       \
    int hblock = s >> mipShift(miplevel);                                       \
    int vblock = t >> mipShift(miplevel);                                       \
    int * lightptr = sdd.blocklights + hblock + (int)sdd.r_lightwidth * vblock;     \
    int16_t light11 = lightptr[0] & 0xFFFF; \
    int16_t light12 = lightptr[0] >> 16; \
    /* calculate deltaT and reverseDeltaT  */  \
    int16_t deltaT = t & mipMask(miplevel);  \
    int16_t reverseDeltaT = (1 << mipShift(miplevel)) - deltaT; \
    int32_t lightLeft = light11 * reverseDeltaT + light12 * deltaT; \
    int16_t light21 = lightptr[1] & 0xFFFF; \
    int16_t light22 = lightptr[1] >> 16; \
    int32_t lightRight = light21 * reverseDeltaT + light22 * deltaT; \
    int16_t deltaS = s & mipMask(miplevel);  \
    int32_t light = lightRight * deltaS; \
    int16_t reverseDeltaS = (1 << mipShift(miplevel)) - deltaS; \
    light += lightLeft * reverseDeltaS; \
    /*now in light we have the light but left shifted by 2 * mipShift*/ \
    uint32_t c; \
    /*t = t + sdd.r_surf_toffs;   */  \
    c = sdd.qct; \
    c =  c * tt; \
    t = ((uint64_t)c * sdd.r_texture_height) >> 32;   \
    /*s = s + sdd.r_surf_soffs;  */   \
    c = sdd.qcs; \
    c =  c * ss; \
    s = ((uint64_t)c * sdd.r_texture_width) >> 32;   \
    if (r_fullbright) light = 0; \
    pix = sdd.r_source[t * (int) sdd.r_texture_width + s];                                            \
    pix = ((unsigned char *)sdd.colormap) [((light >> (mipShift(miplevel))) & 0xFF00) + pix];                     \
    return pix;                                                                         \
}
#define defineR_GetSurfacePixelForMiplevelPower2(miplevel)                            \
__attribute__((always_inline))  static inline uint8_t R_GetSurfacePixel##miplevel##Power2(int ss, int tt)               \
{                                                                               \
    uint8_t pix;                                                                \
    int st = PACK16(ss >> (16 - SPAN_PRECISION), tt >> (16 - SPAN_PRECISION));     \
    int s = getS(st) >> SPAN_PRECISION, t = getT(st) >> SPAN_PRECISION;       \
    int hblock = s >> mipShift(miplevel);                                       \
    int vblock = t >> mipShift(miplevel);                                       \
    int * lightptr = sdd.blocklights + hblock + (int)sdd.r_lightwidth * vblock;     \
    int16_t light11 = lightptr[0] & 0xFFFF; \
    int16_t light12 = lightptr[0] >> 16; \
    /* calculate deltaT and reverseDeltaT  */  \
    int16_t deltaT = t & mipMask(miplevel);  \
    int16_t reverseDeltaT = (1 << mipShift(miplevel)) - deltaT; \
    int32_t lightLeft = light11 * reverseDeltaT + light12 * deltaT; \
    int16_t light21 = lightptr[1] & 0xFFFF; \
    int16_t light22 = lightptr[1] >> 16; \
    int32_t lightRight = light21 * reverseDeltaT + light22 * deltaT; \
    int16_t deltaS = s & mipMask(miplevel);  \
    int32_t light = lightRight * deltaS; \
    int16_t reverseDeltaS = (1 << mipShift(miplevel)) - deltaS; \
    light += lightLeft * reverseDeltaS; \
    /*now in light we have the light but left shifted by 2 * mipShift*/ \
    /* s and t just need bit field extract, because the texture has power of two*/\
    t = t & (sdd.r_texture_height - 1); \
    s = s & (sdd.r_texture_width - 1); \
    pix = sdd.r_source[t * (int) sdd.r_texture_width + s];\
    if (r_fullbright) light = 0;                                     \
    pix = ((unsigned char *)sdd.colormap) [((light >> (mipShift(miplevel))) & 0xFF00) + pix];                     \
    return pix;                                                                         \
}
#else
// Hey! This C code is not optimized for speed! This is just to emulate (and test!) what the asm routine does!
#define defineR_GetSurfacePixelForMiplevel(miplevel)                            \
__attribute__((always_inline))  static inline uint8_t R_GetSurfacePixel##miplevel(int ss, int tt)               \
{                                                                               \
    uint8_t pix;                                                                \
    int s = ss >> 16, t = tt >> 16;                                             \
    int hblock = s >> mipShift(miplevel);                                       \
    int vblock = t >> mipShift(miplevel);                                       \
    int * lightptr = sdd.blocklights + hblock + (int)sdd.r_lightwidth * vblock;     \
    int16_t light11 = lightptr[0] & 0xFFFF; \
    int16_t light12 = lightptr[0] >> 16; \
    /* calculate deltaT and reverseDeltaT  */  \
    int16_t deltaT = t & mipMask(miplevel);  \
    int16_t reverseDeltaT = (1 << mipShift(miplevel)) - deltaT; \
    int32_t lightLeft = light11 * reverseDeltaT + light12 * deltaT; \
    int16_t light21 = lightptr[1] & 0xFFFF; \
    int16_t light22 = lightptr[1] >> 16; \
    int32_t lightRight = light21 * reverseDeltaT + light22 * deltaT; \
    int16_t deltaS = s & mipMask(miplevel);  \
    int32_t light = lightRight * deltaS; \
    int16_t reverseDeltaS = (1 << mipShift(miplevel)) - deltaS; \
    light += lightLeft * reverseDeltaS; \
    /*now in light we have the light but left shifted by 2 * mipShift*/ \
    uint32_t c; \
    /*t = t + sdd.r_surf_toffs;   */  \
    c = sdd.qct; \
    c =  c * tt; \
    t = ((uint64_t)c * sdd.r_texture_height) >> 32;   \
    /*s = s + sdd.r_surf_soffs;  */   \
    c = sdd.qcs; \
    c =  c * ss; \
    s = ((uint64_t)c * sdd.r_texture_width) >> 32;   \
    if (r_fullbright) light = 0;\
    pix = sdd.r_source[t * (int) sdd.r_texture_width + s];                                            \
    pix = ((unsigned char *)sdd.colormap) [((light >> (mipShift(miplevel))) & 0xFF00) + pix];                     \
    return pix;                                                                         \
}
#define defineR_GetSurfacePixelForMiplevelPower2(miplevel)                            \
__attribute__((always_inline))  static inline uint8_t R_GetSurfacePixel##miplevel##Power2(int ss, int tt)               \
{                                                                               \
    int s = ss >>16, t = tt>>16; \
    uint8_t pix;                                                                \
    int hblock = s >> mipShift(miplevel);                                       \
    int vblock = t >> mipShift(miplevel);                                       \
    int * lightptr = sdd.blocklights + hblock + (int)sdd.r_lightwidth * vblock;     \
    int16_t light11 = lightptr[0] & 0xFFFF; \
    int16_t light12 = lightptr[0] >> 16; \
    /* calculate deltaT and reverseDeltaT  */  \
    int16_t deltaT = t & mipMask(miplevel);  \
    int16_t reverseDeltaT = (1 << mipShift(miplevel)) - deltaT; \
    int32_t lightLeft = light11 * reverseDeltaT + light12 * deltaT; \
    int16_t light21 = lightptr[1] & 0xFFFF; \
    int16_t light22 = lightptr[1] >> 16; \
    int32_t lightRight = light21 * reverseDeltaT + light22 * deltaT; \
    int16_t deltaS = s & mipMask(miplevel);  \
    int32_t light = lightRight * deltaS; \
    int16_t reverseDeltaS = (1 << mipShift(miplevel)) - deltaS; \
    light += lightLeft * reverseDeltaS; \
    /*now in light we have the light but left shifted by 2 * mipShift*/ \
    /* s and t just need bit field extract, because the texture has power of two*/\
    t = t & (sdd.r_texture_height - 1); \
    s = s & (sdd.r_texture_width - 1); \
    if (r_fullbright) light = 0;\
    pix = sdd.r_source[t * (int) sdd.r_texture_width + s];                                            \
    pix = ((unsigned char *)sdd.colormap) [((light >> (mipShift(miplevel))) & 0xFF00) + pix];                     \
    return pix;                                                                         \
}
#endif
#endif
#endif

#if WIN32
defineR_GetSurfacePixelForMiplevel(0);
defineR_GetSurfacePixelForMiplevel(1);
defineR_GetSurfacePixelForMiplevel(2);
defineR_GetSurfacePixelForMiplevel(3);
defineR_GetSurfacePixelForMiplevelPower2(0);
defineR_GetSurfacePixelForMiplevelPower2(1);
defineR_GetSurfacePixelForMiplevelPower2(2);
defineR_GetSurfacePixelForMiplevelPower2(3);
#endif
#endif
#define MAX_SPAN_COUNT 32    // next-hack: Quake originally used 8, which gives more precise rendering. With 8, you lose on average 2 fps (so timedemo 3 will run on 26.1 avg fps). We prefer speed over accuracy, which is barely noticeable.
DRAWSURF_SEC void D_DrawSpans8(espan_t *pspan)
#define MAX_SPAN_COUNT2 64
#define DYNAMIC_MAX_SPAN_COUNT 0
{
#if DYNAMIC_MAX_SPAN_COUNT
    int count, spancount;
    unsigned char *pdest;
    fixed16_t s, t, snext, tnext, sstep, tstep;
    float sdivz, tdivz, zi, z, du, dv;
    float sdivz8stepu, tdivz8stepu, zi8stepu;

    sstep = 0;	// keep compiler happy
    tstep = 0;	// ditto
    int miplevel = sdd.surfmip;
    if (miplevel == 0)
    {
    sdivz8stepu = _g->d_sdivzstepu * MAX_SPAN_COUNT;
    tdivz8stepu = _g->d_tdivzstepu * MAX_SPAN_COUNT;
    zi8stepu = _g->d_zistepu * MAX_SPAN_COUNT;
    }
    else
    {
        sdivz8stepu = _g->d_sdivzstepu * MAX_SPAN_COUNT2;
        tdivz8stepu = _g->d_tdivzstepu * MAX_SPAN_COUNT2;
        zi8stepu = _g->d_zistepu * MAX_SPAN_COUNT2;
    }
	do
	{
        int spanIndex = pspan - _g->basespan_p;
        dv = (float) _g->basespanV_p[spanIndex];
        // calculate the initial s/z, t/z, 1/z, s, and t and clamp
            du = (float)pspan->u;

		sdivz = _g->d_sdivzorigin + dv*_g->d_sdivzstepv + du*_g->d_sdivzstepu;
		tdivz = _g->d_tdivzorigin + dv*_g->d_tdivzstepv + du*_g->d_tdivzstepu;
		zi = _g->d_ziorigin + dv*_g->d_zistepv + du*_g->d_zistepu;
        z = (float)0x10000 / zi;  // prescale to 16.16 fixed-point

        pdest = (unsigned char *)((byte *)_g->d_viewbuffer + (screenwidth * _g->basespanV_p[spanIndex]) + pspan->u);

        count = pspan->count;


		s = (int)(sdivz * z) + _g->sadjust;
		if (s > _g->bbextents)
			s = _g->bbextents;
		else if (s < 0)
			s = 0;

		t = (int)(tdivz * z) + _g->tadjust;
		if (t > _g->bbextentt)
			t = _g->bbextentt;
		else if (t < 0)
			t = 0;

		do
		{
		// calculate s and t at the far end of the span
			if (miplevel == 0)
            {
                if (count >= MAX_SPAN_COUNT)
                {
                    spancount = MAX_SPAN_COUNT;
                }
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
                    z = (float)0x10000 / zi;	// prescale to 16.16 fixed-point

                    snext = (int)(sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT)
                        snext = MAX_SPAN_COUNT;	// prevent round-off error on <0 steps from
                                    //  from causing overstepping & running off the
                                    //  edge of the texture

                    tnext = (int)(tdivz * z) + _g->tadjust;
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
                    float spancountminus1 = (float)(spancount - 1);
                    sdivz += _g->d_sdivzstepu * spancountminus1;
                    tdivz += _g->d_tdivzstepu * spancountminus1;
                    zi += _g->d_zistepu * spancountminus1;
                    z = (float)0x10000 / zi;	// prescale to 16.16 fixed-point
                    snext = (int)(sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT)
                        snext = MAX_SPAN_COUNT;	// prevent round-off error on <0 steps from
                                    //  from causing overstepping & running off the
                                    //  edge of the texture

                    tnext = (int)(tdivz * z) + _g->tadjust;
                    if (tnext > _g->bbextentt)
                        tnext = _g->bbextentt;
                    else if (tnext < MAX_SPAN_COUNT)
                        tnext = MAX_SPAN_COUNT;	// guard against round-off error on <0 steps
                    if (spancount > 1)
                    {
                      int rec = fixedReciprocal256[spancount - 1];
                      sstep = ((int64_t) (snext - s) * rec) >> 16;
                      tstep = ((int64_t) (tnext - t) * rec) >> 16;
                    }
                }
            }
            else    // far texture. Artifact less visible!
            {
                if (count >= MAX_SPAN_COUNT2)
                {
                    spancount = MAX_SPAN_COUNT2;
                }
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
                    z = (float)0x10000 / zi;	// prescale to 16.16 fixed-point
                    snext = (int)(sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT2)
                        snext = MAX_SPAN_COUNT2;	// prevent round-off error on <0 steps from
                                    //  from causing overstepping & running off the
                                    //  edge of the texture
                    tnext = (int)(tdivz * z) + _g->tadjust;
                    if (tnext > _g->bbextentt)
                        tnext = _g->bbextentt;
                    else if (tnext < MAX_SPAN_COUNT2)
                        tnext = MAX_SPAN_COUNT2;	// guard against round-off error on <0 steps
                    sstep = (snext - s) / MAX_SPAN_COUNT2;
                    tstep = (tnext - t) / MAX_SPAN_COUNT2;
                }
                else
                {
                // calculate s/z, t/z, zi->fixed s and t at last pixel in span (so
                // can't step off polygon), clamp, calculate s and t steps across
                // span by division, biasing steps low so we don't run off the
                // texture
                    float spancountminus1 = (float)(spancount - 1);
                    sdivz += _g->d_sdivzstepu * spancountminus1;
                    tdivz += _g->d_tdivzstepu * spancountminus1;
                    zi += _g->d_zistepu * spancountminus1;
                    z = (float)0x10000 / zi;	// prescale to 16.16 fixed-point
                    snext = (int)(sdivz * z) + _g->sadjust;
                    if (snext > _g->bbextents)
                        snext = _g->bbextents;
                    else if (snext < MAX_SPAN_COUNT2)
                        snext = MAX_SPAN_COUNT2;	// prevent round-off error on <0 steps from
                                    //  from causing overstepping & running off the
                                    //  edge of the texture
                    tnext = (int)(tdivz * z) + _g->tadjust;
                    if (tnext > _g->bbextentt)
                        tnext = _g->bbextentt;
                    else if (tnext < MAX_SPAN_COUNT2)
                        tnext = MAX_SPAN_COUNT2;	// guard against round-off error on <0 steps
                    if (spancount > 1)
                    {
                      int rec = fixedReciprocal256[spancount - 1];
                      sstep = ((int64_t) (snext - s) * rec) >> 16;
                      tstep = ((int64_t) (tnext - t) * rec) >> 16;
                    }
                }
            }
#else
    #if WIN32
    static float maxzi8stepu;
    #endif
	int				count, spancount;
	unsigned char	*pdest;
	fixed16_t		s, t, snext, tnext, sstep, tstep;
	float			sdivz, tdivz, zi, z, du, dv;
	float			sdivz8stepu, tdivz8stepu, zi8stepu;
	sstep = 0;	// keep compiler happy
	tstep = 0;	// ditto
	sdivz8stepu = _g->d_sdivzstepu * MAX_SPAN_COUNT;
	tdivz8stepu = _g->d_tdivzstepu * MAX_SPAN_COUNT;
	zi8stepu = _g->d_zistepu * MAX_SPAN_COUNT;
    #if WIN32
    if (fabs(zi8stepu) > maxzi8stepu)
    {
        maxzi8stepu = fabs(zi8stepu);
        printf(">>>>>>>>>>>>>>>>>>maxzi8stepu increased to %f, value %f\r\n", maxzi8stepu, zi8stepu);
    }
    #endif
    do
    {
#if !ESPANS_HAVE_V
        int spanIndex = pspan - _g->basespan_p;
        dv = (float) _g->basespanV_p[spanIndex];

#else
    dv = (float)pspan->v;
#endif
        // calculate the initial s/z, t/z, 1/z, s, and t and clamp
        du = (float) pspan->u;

        sdivz = _g->d_sdivzorigin + dv * _g->d_sdivzstepv + du * _g->d_sdivzstepu;
        tdivz = _g->d_tdivzorigin + dv * _g->d_tdivzstepv + du * _g->d_tdivzstepu;
        zi = _g->d_ziorigin + dv * _g->d_zistepv + du * _g->d_zistepu;
        z = (float) 0x10000 / zi;  // prescale to 16.16 fixed-point
#if !ESPANS_HAVE_V
        pdest = (unsigned char*) ((byte*) _g->d_viewbuffer + (screenwidth * _g->basespanV_p[spanIndex]) + pspan->u);

#else
    pdest = (unsigned char *)((byte *)_g->d_viewbuffer + (screenwidth * pspan->v) + pspan->u);
#endif
        count = pspan->count;

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
            {
                spancount = MAX_SPAN_COUNT;
            }
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
                float spancountminus1 = (float) (spancount - 1);
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
//					sstep = (snext - s) / (spancount - 1);
//					tstep = (tnext - t) / (spancount - 1);
                    int rec = fixedReciprocal256[spancount - 1];
                    sstep = ((int64_t) (snext - s) * rec) >> 16;
                    tstep = ((int64_t) (tnext - t) * rec) >> 16;
                }
            }
#endif
    #if PRE_LIGHT_SURFACES

			do
			{

				*pdest++ = *(pbase + (s >> 16) + (t >> 16) * cachewidth);
				s += sstep;
				t += tstep;
			} while (--spancount > 0);
#else
// TODO OPTIMIZE HERE

            s += sdd.r_surf_soffs << 16;
            t += sdd.r_surf_toffs << 16;

            if (sstep < 0)
                sstep += 1 << (16 - SPAN_PRECISION);
            if (tstep < 0)
                tstep += 1 << (16 - SPAN_PRECISION);

#if USE_ASM_CODE

#if 0 // unfortunately we have rounding errors.
    if (sdd.textureType == -1)
    { // best case: we don't have to do mod
      switch (r_drawsurf.surfmip & 3)
      {
          case 0:
              drawSurfSpanPower2NoMod(0);
          break;
          case 1:
            drawSurfSpanPower2NoMod(1);
          break;
          case 2:
            drawSurfSpanPower2NoMod(2);
          break;
          case 3:
            drawSurfSpanPower2NoMod(3);
          break;
      }

    }
    else
#endif
            if (!sdd.textureType)
            { // second best case: we do have to do mod, but by powers of 2
#if 0
      switch (mip)
      {
          case 0:
              drawSurfSpanPower2(0);
          break;
          case 1:
            drawSurfSpanPower2(1);
          break;
          case 2:
            drawSurfSpanPower2(2);
          break;
          case 3:
            drawSurfSpanPower2(3);
          break;
      }
#else
#if USE_SWITCH_CASE
      switch (sdd.surfmip & 3)
      {
               case 0:
                   drawSurfSpanPower2(0);
               break;
               case 1:
                 drawSurfSpanPower2(1);
               break;
               case 2:
                 drawSurfSpanPower2(2);
               break;
               case 3:
                 drawSurfSpanPower2(3);
               break;
     }
#else
                int mip = sdd.surfmip & 3;
                if (mip == 0)
                {
                    drawSurfSpanPower2(0);
                }
                else if (mip == 1)
                {
                    drawSurfSpanPower2(1);
                }
                else if (mip == 2)
                {
                    drawSurfSpanPower2(2);
                }
                else
                {
                    drawSurfSpanPower2(3);
                }

#endif
#endif
            }
            else
            { // bad case (this is like one over 100
                switch (sdd.surfmip & 3)
                {
                    case 0:
                        drawSurfSpan(0)
                        ;
                        break;
                    case 1:
                        drawSurfSpan(1)
                        ;
                        break;
                    case 2:
                        drawSurfSpan(2)
                        ;
                        break;
                    case 3:
                        drawSurfSpan(3)
                        ;
                        break;
                }
            }
            spancount = 0;
#else
    unsigned int st = PACK16(s >> (16 - SPAN_PRECISION), t >> (16 - SPAN_PRECISION));
    /*if (sstep < 0)
        sstep += 1 << (16 - SPAN_PRECISION);//(uint32_t) sstep >> (31 - (16 - SPAN_PRECISION));//1 << (16 - SPAN_PRECISION);
    if (tstep < 0)
        tstep += 1 << (16 - SPAN_PRECISION);//(uint32_t) tstep >> (31 - (16 - SPAN_PRECISION));//1 << (16 - SPAN_PRECISION);
    */
    unsigned int ststep = PACK16(sstep >> (16 - SPAN_PRECISION) ,tstep >> (16 - SPAN_PRECISION));

   // printf("st 0x%08x ststep 0x%08x, s 0x%08x t 0x%08x\r\n", st, ststep, s, t);
   // printf("Sadd: 0x%08x\r\n", sadd16(0x10002001, 0x12345678));
    //FIXME("STEP");
    do
    {
#if TEST_SIMD
        s = (int32_t) (getS(st)) << (16 - SPAN_PRECISION);
        t = (int32_t) (getT(st)) << (16 - SPAN_PRECISION);
 //   printf("New s 0x%08x t 0x%08x\r\n", s, t);

#endif
        if (!sdd.textureType)
        {
            switch (r_drawsurf.surfmip & 3)
            {
                case 0:
                    *pdest++=R_GetSurfacePixel0Power2(s, t);
                break;
                case 1:
                    *pdest++=R_GetSurfacePixel1Power2(s, t);
                break;
                case 2:
                    *pdest++=R_GetSurfacePixel2Power2(s, t);
                break;
                case 3:
                    *pdest++=R_GetSurfacePixel3Power2(s, t);
            }


        }
        else
        {
            switch (r_drawsurf.surfmip & 3)
            {
                case 0:
                    *pdest++=R_GetSurfacePixel0(s, t);
                break;
                case 1:
                    *pdest++=R_GetSurfacePixel1(s, t);
                break;
                case 2:
                    *pdest++=R_GetSurfacePixel2(s, t);
                break;
                case 3:
                    *pdest++=R_GetSurfacePixel3(s, t);
            }

        }
#if TEST_SIMD
        st = sadd16( st, ststep);
#else
        s += sstep;
        t += tstep;
#endif
    } while(--spancount > 0);


/*                    do
                    {
                        *pdest++ = R_GetSurfacePixel3(s >> 16, t >> 16,  st * sdd.iwfactor, tt * sdd.ihfactor);
                        s += sstep;
                        t += tstep;
                        st += ststep;
                        tt += ttstep;
                    } while (--spancount > 0*/
#endif

#endif
            s = snext;
            t = tnext;

        }
        while (count > 0);
#if OLD_SPAN_METHOD
	} while ((pspan = pspan->pnext) != NULL);
#elif 0
	} while ((pspan = getNextSpan(pspan, 1)) != NULL);
#else
    }
    while ((pspan = getNextSpan(pspan, 0)) != _g->basespan_p);
#endif
}

#endif

#if	!id386

/*
 =============
 D_DrawZSpans
 =============
 */
__attribute__ ((section(".drawsurf"))) void D_DrawZSpans(espan_t *pspan)
{
    int count, izistep;
    int izi;
    short *pdest;
    unsigned ltemp;
    QDFLOAT zi;
    float du, dv;
// FIXME: check for clamping/range problems
// we count on FP exceptions being turned off to avoid range problems
    izistep = (int) (_g->d_zistepu * 0x8000 * 0x10000);

    do
    {
#if !ESPANS_HAVE_V
        int spanIndex = pspan - _g->basespan_p;
        dv = (float) _g->basespanV_p[spanIndex];
        pdest = _g->d_pzbuffer + (d_zwidth * _g->basespanV_p[spanIndex]) + pspan->u;

#else
    pdest = _g->d_pzbuffer + (d_zwidth * pspan->v) + pspan->u;
    dv = (float)pspan->v;

#endif

        count = pspan->count;

        // calculate the initial 1/z
        du = (float) pspan->u;

        zi = _g->d_ziorigin + dv * _g->d_zistepv + du * _g->d_zistepu;
        // we count on FP exceptions being turned off to avoid range problems
        izi = (int) (zi * 0x8000 * 0x10000);

        if ((long) pdest & 0x02)
        {
            *pdest++ = (short) (izi >> 16);
            izi += izistep;
            count--;
        }
#define NEW_MODE (WIN32 ? 0 : 3)
#define DO_QUADCOUNTS 1
#if DO_QUADCOUNTS
#if NEW_MODE
        int quadcount;
        if ((quadcount = count / 4) > 0)
        {

            int pixHi, pixLo;
            int finalPtr;
#if NEW_MODE < 3
        count &= 3;
#endif
            __ASM volatile
            (
                ".align(2)\n\t"
                "ADD %[finalPtr], %[pdest], %[quadcount], LSL #3\n\t" // get final ptr value
                "loop%=:\n\t"
                "ADD %[pixLo], %[izi], %[izistep]\n\t"// get in top ltemp the next lzi. The bottom part is trash
                "PKHTB %[pixLo], %[pixLo],  %[izi], ASR #16\n\t"// get in bottom ltemp, the current izi
                "ADD %[izi], %[izi], %[izistep], LSL #1\n\t"// get in izi the next-next one.
                //
                "ADD %[pixHi], %[izi], %[izistep]\n\t"// get in top ltemp the next lzi. The bottom part is trash
                "PKHTB %[pixHi], %[pixHi],  %[izi], ASR #16\n\t"// get in bottom ltemp, the current izi
                "ADD %[izi], %[izi], %[izistep], LSL #1\n\t"// get in izi the next-next one.
                "STRD %[pixLo], %[pixHi], [%[pdest]], #8\n\t"// store with post increment
                "CMP %[pdest], %[finalPtr]\n\t"// compare and branch if not reached.
                "BNE loop%=\n\t"
                :// out
                [pixHi] "=&r" (pixHi),
                [pixLo] "=&r" (pixLo),
                [finalPtr] "=&r" (finalPtr),
                [izi] "+r" (izi),
                [pdest] "+r" (pdest)
                :// in
                [izistep] "r" (izistep),
                [quadcount] "r" (quadcount)
                :// clobber
            );
        }
#else
        int quadcount;
    if ((quadcount = count / 4) > 0)
    {
        count &= 3;
      uint64_t quadpixel;
      do
      {
        quadpixel = izi >> 16;
        izi += izistep;
        quadpixel |= izi & 0xFFFF0000;
        izi += izistep;
                quadpixel |= (uint64_t)(izi & 0xFFFF0000) << 16;
        izi += izistep;
                quadpixel |= (uint64_t)(izi & 0xFFFF0000) << 32;
        izi += izistep;
        *(uint64_t *)pdest = quadpixel;
        pdest += 4;
      } while (--quadcount > 0);
    }
#endif
#endif
#if NEW_MODE  == 1
    if ((doublecount = count >> 1) > 0)
    {
      do
			{
			  __ASM volatile
			  (
			  //    "ASR %[ltemp], %[izi], #16\n\t"
            "ADD %[ltemp], %[izi], %[izistep]\n\t"                  // get in top ltemp the next lzi. The bottom part is trash
            "PKHTB %[ltemp], %[ltemp],  %[izi], ASR #16\n\t"        // get in bottom ltemp, the current izi
            "ADD %[izi], %[izi], %[izistep], LSL #1\n\t"            // get in izi the next-next one.
	//		      "STR %[ltemp], [%[pdest]], #4\n\t"
			      :  // out
			       [ltemp] "=&r" (ltemp),
             [izi] "+r" (izi)
//             [pdest] "+r" (pdest)


			      :  // in
             [izistep] "r" (izistep)

			     : // clobber
			  );
        *(int *)pdest = ltemp;
        pdest += 2;
		  } while (--doublecount > 0);
    }
#elif NEW_MODE == 2
    if ((doublecount = count >> 1) > 0)
    {
		    int finalPtr;
		    __ASM volatile
        (
            ".align(2)\n\t"
            "ADD %[finalPtr], %[pdest], %[doublecount], LSL #2\n\t" // get final ptr value
            "loop%=:\n\t"
            "ADD %[ltemp], %[izi], %[izistep]\n\t"                  // get in top ltemp the next lzi. The bottom part is trash
            "PKHTB %[ltemp], %[ltemp],  %[izi], ASR #16\n\t"        // get in bottom ltemp, the current izi
            "ADD %[izi], %[izi], %[izistep], LSL #1\n\t"            // get in izi the next-next one.
            "STR %[ltemp], [%[pdest]], #4\n\t"                      // store with post increment
            "CMP %[pdest], %[finalPtr]\n\t"                         // compare and branch if not reached.
            "BNE loop%=\n\t"
            :  // out
             [ltemp] "=&r" (ltemp),
             [finalPtr] "=&r" (finalPtr),
             [izi] "+r" (izi),
             [pdest] "+r" (pdest)
            :  // in
             [izistep] "r" (izistep),
             [doublecount] "r" (doublecount)
             : // clobber
        );
    }
#elif NEW_MODE == 3
        if (count & 2)
        {
            __ASM volatile
            (
                ".align(2)\n\t"
                "ADD %[ltemp], %[izi], %[izistep]\n\t"                  // get in top ltemp the next lzi. The bottom part is trash
                "PKHTB %[ltemp], %[ltemp],  %[izi], ASR #16\n\t"// get in bottom ltemp, the current izi
                "ADD %[izi], %[izi], %[izistep], LSL #1\n\t"// get in izi the next-next one.
                "STR %[ltemp], [%[pdest]], #4\n\t"// store with post increment
                :// out
                [ltemp] "=&r" (ltemp),
                [izi] "+r" (izi),
                [pdest] "+r" (pdest)
                :// in
                [izistep] "r" (izistep)
                :// clobber
            );
        }
#else
    int doublecount;
        if ((doublecount = count >> 1) > 0)
        {
          do
          {
            ltemp = izi >> 16;
            izi += izistep;
            ltemp |= izi & 0xFFFF0000;
            izi += izistep;
            *(int *)pdest = ltemp;
            pdest += 2;
          } while (--doublecount > 0);
        }
#endif
        if (count & 1)
            *pdest = (short) (izi >> 16);

#if OLD_SPAN_METHOD
	} while ((pspan = pspan->pnext) != NULL);
#else
    }
    while ((pspan = getNextSpan(pspan, 1)) != NULL);
#endif
}

#endif

