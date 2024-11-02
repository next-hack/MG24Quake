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
// d_polyset.c: routines for drawing sets of polygons sharing the same
// texture (used for Alias models)

#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"
#if !WIN32
#include "memory_defs.h"
#endif
#if WIN32
int aliasPixelsDrawn = 0;
int aliasPixelsDrawnSingle = 0;
#endif // WIN32
//
#define MODELS_HAVE_ORIGINAL_SKIN_TOO    1
#define LETS_TEST_SKINS 0
#define APPROX_X 1
#define APPROX_Y 0  // was 0
#define LAZY_MTOD_LOAD 1
#define ASYNCH_LOAD_RECURSIVE 0
//
// TODO: put in span spilling to shrink list size
// !!! if this is changed, it must be changed in d_polysa.s too !!!
#define DPS_MAXSPANS      MAXHEIGHT+1
// 1 extra for spanpackage that marks end

global_data_t global;
global_data_t *const _g = &global;
#if ENABLE_RECURSIVE_DRAWING && !MODELS_HAVE_ORIGINAL_SKIN_TOO
mtriangleOffsetData_t *recursiveMtod;
byte * recursive_ptex;
#endif

const edgetable edgetables[12] =
{
    { 0, 1, global.r_p0, global.r_p2, NULL, 2, global.r_p0, global.r_p1, global.r_p2},
    { 0, 2, global.r_p1, global.r_p0, global.r_p2, 1, global.r_p1, global.r_p2, NULL},
    { 1, 1, global.r_p0, global.r_p2, NULL, 1, global.r_p1, global.r_p2, NULL},
    { 0, 1, global.r_p1, global.r_p0, NULL, 2, global.r_p1, global.r_p2, global.r_p0},
    { 0, 2, global.r_p0, global.r_p2, global.r_p1, 1, global.r_p0, global.r_p1, NULL},
    { 0, 1, global.r_p2, global.r_p1, NULL, 1, global.r_p2, global.r_p0, NULL},
    { 0, 1, global.r_p2, global.r_p1, NULL, 2, global.r_p2, global.r_p0, global.r_p1},
    { 0, 2, global.r_p2, global.r_p1, global.r_p0, 1, global.r_p2, global.r_p0, NULL},
    { 0, 1, global.r_p1, global.r_p0, NULL, 1, global.r_p1, global.r_p2, NULL},
    { 1, 1, global.r_p2, global.r_p1, NULL, 1, global.r_p0, global.r_p1, NULL},
    { 1, 1, global.r_p1, global.r_p0, NULL, 1, global.r_p2, global.r_p0, NULL},
    { 0, 1, global.r_p0, global.r_p2, NULL, 1, global.r_p0, global.r_p1, NULL},
};

typedef struct
{
    int quotient;
    int remainder;
} adivtab_t;

static const adivtab_t adivtab[32 * 32] = {
#include "adivtab.h"
    };
static inline void D_PolysetDrawSpans8(spanpackage_t *pspanpackage);
void D_PolysetCalcGradients(int skinwidth);
void D_DrawSubdiv(void);
void D_DrawNonSubdiv(void);
#if ENABLE_RECURSIVE_DRAWING
void D_PolysetRecursiveTriangle(int *p1, int *p2, int *p3);
#endif
void D_PolysetSetEdgeTable(void);
#if NO_MINIMIZE
void D_RasterizeAliasPolySmooth (void);
#else
void D_RasterizeAliasPolySmooth(int numtri);
#endif
void D_PolysetScanLeftEdge(int height);

#if !id386

/*
 ================
 D_PolysetDraw
 ================
 */
void D_PolysetDraw(void)
{
    spanpackage_t spans[DPS_MAXSPANS + 1 + ((CACHE_SIZE - 1) / sizeof(spanpackage_t)) + 1];
    // one extra because of cache line pretouching

    _g->a_spans = (spanpackage_t*) (((long) &spans[0] + CACHE_SIZE - 1) & ~(CACHE_SIZE - 1));
#if ENABLE_RECURSIVE_DRAWING
    if (_g->r_affinetridesc.drawtype)
    {
        // FIXME: abort speculative loading of triangles!
        D_DrawSubdiv();
    }
    else
#endif
    {
        D_DrawNonSubdiv();
    }
}

/*
 ================
 D_PolysetDrawFinalVerts
 ================
 */
#if ENABLE_RECURSIVE_DRAWING
void D_PolysetDrawFinalVerts(finalvert_t *fv, int numverts)
{
    int i, z;
    short *zbuf;
    for (i = 0; i < numverts; i++, fv++)
    {
        // valid triangle coordinates for filling can include the bottom and
        // right clip edges, due to the fill rule; these shouldn't be drawn
        if ((fv->v[0] < _g->r_refdef.vrectright) && (fv->v[1] < _g->r_refdef.vrectbottom))
        {
            z = fv->v[5] >> 16;
            zbuf = zspantable(fv->v[1]) + fv->v[0];
            if (z >= *zbuf)
            {
                int pix;

                *zbuf = z;
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
#if ASYNCH_LOAD_RECURSIVE
        flushAliasPendingPixel();
        interleavedSpiFlashAsynchReadByteDMA ((byte*)r_affinetridesc.pOriginalskin + (fv->v[2] >> 16) +  (fv->v[3] >> 16) * r_affinetridesc.skinwidth);
        _g->aliasRecursiveLight = (fv->v[4] & 0xFF00);
        _g->aliasPendingAddress = &_g->d_viewbuffer[d_scantable(fv->v[1]) + fv->v[0]];
        _g->aliasPendingPixel = 1;
#else
#if CACHE_SKINS_TO_FLASH
                if (_g->originalSkinInInternalFlash)
                {
                    pix = *((byte*)_g->r_affinetridesc.pOriginalskin + (fv->v[2] >> 16) + (fv->v[3] >> 16) * _g->r_affinetridesc.skinwidth);
                }
                else
#endif
                {
                pix = extMemGetByteFromAddress((byte*) _g->r_affinetridesc.pOriginalskin + (fv->v[2] >> 16) + (fv->v[3] >> 16) * _g->r_affinetridesc.skinwidth);
                }

                pix = ((byte*) _g->acolormap)[pix + (fv->v[4] & 0xFF00)];
                _g->d_viewbuffer[d_scantable(fv->v[1]) + fv->v[0]] = pix;
#endif
#else
#error
    pix =   extMemGetByteFromAddress (&recursive_ptex[recursiveMtod->offsets[((fv->v[2] + APPROX_X*0x8000) >> 16) - recursiveMtod->offsetS] + ((fv->v[3] + APPROX_Y*0x8000) >> 16)]);
    _g->d_viewbuffer[d_scantable(fv->v[1]) + fv->v[0]] = pix;


#endif

            }
        }
    }
}
/*
 ================
 D_DrawSubdiv
 ================
 */
void D_DrawSubdiv(void)
{
    mtriangle_t *ptri;
    finalvert_t *pfv, *index0, *index1, *index2;
    int i;
    int lnumtriangles;

    pfv = _g->r_affinetridesc.pfinalverts;
    ptri = _g->r_affinetridesc.ptriangles;
    lnumtriangles = _g->r_affinetridesc.numtriangles;

    for (i = 0; i < lnumtriangles; i++)
    {
        // We should put currentTriangle as global, to be able to get the current triangle
        index0 = pfv + ptri[i].vertindex0;
        index1 = pfv + ptri[i].vertindex1;
        index2 = pfv + ptri[i].vertindex2;
        //

        //
        if (((index0->v[1] - index1->v[1]) * (index0->v[0] - index2->v[0]) - (index0->v[0] - index1->v[0]) * (index0->v[1] - index2->v[1])) >= 0)
        {
            continue;
        }
#if !MODELS_HAVE_ORIGINAL_SKIN_TOO
#error we need original skin!
        recursiveMtod =  (mtriangleOffsetData_t *) ((byte*) r_affinetridesc.paliashdr + (ptri[i].triangleOffsetDataPos << 2));

        recursiveMtod = extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,
                                         recursiveMtod,
                                         ( sizeof (*recursiveMtod) + sizeof(recursiveMtod->offsets[0]) * (ptri[i].triangleOffsetNumber) + 3) & ~3 );
        recursive_ptex = (byte *)r_affinetridesc.pskin - recursiveMtod->bufferOffset;
#endif

        _g->aliasRecursiveLight = index0->v[4] & 0xFF00;
        _g->d_pcolormap = &((byte*) _g->acolormap)[_g->aliasRecursiveLight];

        if (ptri[i].facesfront)
        {
            D_PolysetRecursiveTriangle(index0->v, index1->v, index2->v);
        }
        else
        {
            int s0, s1, s2;

            s0 = index0->v[2];
            s1 = index1->v[2];
            s2 = index2->v[2];

            if (index0->flags & ALIAS_ONSEAM)
                index0->v[2] += _g->r_affinetridesc.seamfixupX16;
            if (index1->flags & ALIAS_ONSEAM)
                index1->v[2] += _g->r_affinetridesc.seamfixupX16;
            if (index2->flags & ALIAS_ONSEAM)
                index2->v[2] += _g->r_affinetridesc.seamfixupX16;

            D_PolysetRecursiveTriangle(index0->v, index1->v, index2->v);

            index0->v[2] = s0;
            index1->v[2] = s1;
            index2->v[2] = s2;
        }
    }
}
#endif
/*
 ================
 D_DrawNonSubdiv
 ================
 */
void D_DrawNonSubdiv(void)
{
    mtriangle_t *ptri;
    finalvert_t *pfv, *index0, *index1, *index2;
    int i;
    int lnumtriangles;

    pfv = _g->r_affinetridesc.pfinalverts;
    ptri = _g->r_affinetridesc.ptriangles;
    lnumtriangles = _g->r_affinetridesc.numtriangles;
#if WIN32
            int removedTri = 0;
        #endif

    for (i = 0; i < lnumtriangles; i++, ptri++)
    {
#if TRIANGLE_HAS_SENTINEL
        if ( r_affinetridesc.ptriangles[i].sentinel != 0xDEADBEEF)
        {
            printf("Triangle %i has sentinel %x\r\n", i, r_affinetridesc.ptriangles[i].sentinel);
            system("pause");
        }
#endif

        index0 = pfv + ptri->vertindex0;
        index1 = pfv + ptri->vertindex1;
        index2 = pfv + ptri->vertindex2;

        _g->d_xdenom = (index0->v[1] - index1->v[1]) * (index0->v[0] - index2->v[0]) - (index0->v[0] - index1->v[0]) * (index0->v[1] - index2->v[1]);

        if (_g->d_xdenom >= 0)
        {
#if WIN32
        removedTri++;
        #endif
            continue;
        }
// FIXME: this is implemented with a series of LDR/STR. This can be improved by using FP registers
#if WIN32
    _g->r_p0[0] = index0->v[0];   // u
    _g->r_p0[1] = index0->v[1];   // v
    _g->r_p0[2] = index0->v[2];   // s
    _g->r_p0[3] = index0->v[3];   // t
    _g->r_p0[4] = index0->v[4];   // light
    _g->r_p0[5] = index0->v[5];   // iz

    _g->r_p1[0] = index1->v[0];
    _g->r_p1[1] = index1->v[1];
    _g->r_p1[2] = index1->v[2];
    _g->r_p1[3] = index1->v[3];
    _g->r_p1[4] = index1->v[4];
    _g->r_p1[5] = index1->v[5];

    _g->r_p2[0] = index2->v[0];
    _g->r_p2[1] = index2->v[1];
    _g->r_p2[2] = index2->v[2];
    _g->r_p2[3] = index2->v[3];
    _g->r_p2[4] = index2->v[4];
    _g->r_p2[5] = index2->v[5];
#else
        __asm volatile
        (
            "VLDMIA %[src0], {s26, s27, s28, s29, s30, s31}\n\t"
            "VSTMIA %[pdst]!, {s26, s27, s28, s29, s30, s31}\n\t"
            "VLDMIA %[src1], {s26, s27, s28, s29, s30, s31}\n\t"
            "VSTMIA %[pdst]!, {s26, s27, s28, s29, s30, s31}\n\t"
            "VLDMIA %[src2], {s26, s27, s28, s29, s30, s31}\n\t"
            "VSTMIA %[pdst]!, {s26, s27, s28, s29, s30, s31}\n\t"
            :
            : [pdst] "r" (&_g->r_p0[0]), [src0] "r" (&index0->v[0]), [src1] "r" (&index1->v[0]), [src2] "r" (&index2->v[0])
            : "s26", "s27", "s28", "s29", "s30", "s31", "memory"
        );
#endif
        if (!ptri->facesfront)
        {
            if (index0->flags & ALIAS_ONSEAM)
                _g->r_p0[2] += _g->r_affinetridesc.seamfixupX16;
            if (index1->flags & ALIAS_ONSEAM)
                _g->r_p1[2] += _g->r_affinetridesc.seamfixupX16;
            if (index2->flags & ALIAS_ONSEAM)
                _g->r_p2[2] += _g->r_affinetridesc.seamfixupX16;
        }

        D_PolysetSetEdgeTable();
#if NO_MINIMIZE
    D_RasterizeAliasPolySmooth ();
#else
//    printf("Mod %i, tri %i\r\n",lnumtriangles, i );
        D_RasterizeAliasPolySmooth(i);
#endif
    }
#if WIN32 & 0
  printf("Trivial Accept. Num tri was %d, removed %d\r\n",lnumtriangles, removedTri );
  #endif
}

#if ENABLE_RECURSIVE_DRAWING
/*
 ================
 D_PolysetRecursiveTriangle
 ================
 */
void D_PolysetRecursiveTriangle(int *lp1, int *lp2, int *lp3)
{
    int *temp;
    int d;
    int new[6];
    int z;
    short *zbuf;

    d = lp2[0] - lp1[0];
    if (d < -1 || d > 1)
        goto split;
    d = lp2[1] - lp1[1];
    if (d < -1 || d > 1)
        goto split;

    d = lp3[0] - lp2[0];
    if (d < -1 || d > 1)
        goto split2;
    d = lp3[1] - lp2[1];
    if (d < -1 || d > 1)
        goto split2;

    d = lp1[0] - lp3[0];
    if (d < -1 || d > 1)
        goto split3;
    d = lp1[1] - lp3[1];
    if (d < -1 || d > 1)
    {
        split3:
        temp = lp1;
        lp1 = lp3;
        lp3 = lp2;
        lp2 = temp;

        goto split;
    }

    return;     // entire tri is filled

    split2:
    temp = lp1;
    lp1 = lp2;
    lp2 = lp3;
    lp3 = temp;

    split:
// split this edge
    new[0] = (lp1[0] + lp2[0]) >> 1;
    new[1] = (lp1[1] + lp2[1]) >> 1;
    new[2] = (lp1[2] + lp2[2]) >> 1;
    new[3] = (lp1[3] + lp2[3]) >> 1;
    new[5] = (lp1[5] + lp2[5]) >> 1;

// draw the point if splitting a leading edge
    if (lp2[1] > lp1[1])
        goto nodraw;
    if ((lp2[1] == lp1[1]) && (lp2[0] < lp1[0]))
        goto nodraw;

    z = new[5] >> 16;
    zbuf = zspantable(new[1]) + new[0];
    if (z >= *zbuf)
    {
        int pix;

#if NO_MINIMIZE
    *zbuf = z;
    pix = d_pcolormap[skintable[new[3]>>16][new[2]>>16]];
#else
#if LETS_TEST_SKINS
    pix = d_pcolormap[skinstart[skinwidth * (new[3]>>16) + (new[2]>>16)]];
    _g->d_viewbuffer[d_scantable(new[1]) + new[0]] = pix;
#else
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
#if ASYNCH_LOAD_RECURSIVE
    flushAliasPendingPixel();
    interleavedSpiFlashAsynchReadByteDMA ((byte*)r_affinetridesc.pOriginalskin +( new[2]  >> 16) +  (new[3] >> 16) * r_affinetridesc.skinwidth);
    _g->aliasPendingLight = _g->aliasRecursiveLight;
    _g->aliasPendingAddress = &_g->d_viewbuffer[d_scantable(new[1]) + new[0]] ;
    _g->aliasPendingPixel = 1;
    *zbuf = z;

    #else
#if 1
#if CACHE_SKINS_TO_FLASH
        if (_g->originalSkinInInternalFlash)
        {
            pix = *((byte*) _g->r_affinetridesc.pOriginalskin + (new[2] >> 16) + (new[3] >> 16) * _g->r_affinetridesc.skinwidth);
        }
        else
#endif
        {
        pix = extMemGetByteFromAddress((byte*) _g->r_affinetridesc.pOriginalskin + (new[2] >> 16) + (new[3] >> 16) * _g->r_affinetridesc.skinwidth);

        }
        pix = _g->d_pcolormap[pix];
        _g->d_viewbuffer[d_scantable(new[1]) + new[0]] = pix;
        *zbuf = z;
#else
#error
    interleavedSpiFlashAsynchReadByteDMA ((byte*)r_affinetridesc.pOriginalskin +( new[2]  >> 16) +  (new[3] >> 16) * r_affinetridesc.skinwidth);
    *zbuf = z;
    pix = _g->d_pcolormap[interleavedSpiFlashGetAsynchReadByteDMA()];
    _g->d_viewbuffer[d_scantable(new[1]) + new[0]] = pix;

#endif
#endif
#else
#error we want original skin!
        pix = extMemGetByteFromAddress (&recursive_ptex[recursiveMtod->offsets[((new[2] /*+ APPROX_X*0x8000*/) >> 16) - recursiveMtod->offsetS] + ((new[3] + APPROX_Y*0x8000) >> 16)]);
        pix = _g->d_pcolormap[pix];
        _g->d_viewbuffer[d_scantable(new[1]) + new[0]] = pix;
#endif

#endif
#endif
    }

    nodraw:
// recursively continue
    D_PolysetRecursiveTriangle(lp3, lp1, new);
    D_PolysetRecursiveTriangle(lp3, new, lp2);
}
#endif
#endif

/*
 ================
 D_PolysetUpdateTables
 ================
 */


#if !id386

/*
 ===================
 D_PolysetScanLeftEdge
 ====================
 */
void D_PolysetScanLeftEdge(int height)
{

    do
    {
        _g->d_pedgespanpackage->pdest = _g->d_pdest;
        _g->d_pedgespanpackage->pz = _g->d_pz;
        _g->d_pedgespanpackage->count = _g->d_aspancount;
#if NO_MINIMIZE
    _g->d_pedgespanpackage->ptex = _g->d_ptex;
    d_pedgespanpackage->sfrac = d_sfrac;
    d_pedgespanpackage->tfrac = d_tfrac;
#else
//    _g->d_pedgespanpackage->mtod = _g->d_mtod;
        _g->d_pedgespanpackage->s = _g->d_s;
        _g->d_pedgespanpackage->t = _g->d_t;
#endif
        // FIXME: need to clamp l, s, t, at both ends?
        _g->d_pedgespanpackage->light = _g->d_light;
        _g->d_pedgespanpackage->zi = _g->d_zi;

        _g->d_pedgespanpackage++;

        _g->errorterm += _g->erroradjustup;
        if (_g->errorterm >= 0)
        {
            _g->d_pdest += _g->d_pdestextrastep;
            _g->d_pz += _g->d_pzextrastep;
            _g->d_aspancount += _g->d_countextrastep;
#if NO_MINIMIZE
      d_ptex += d_ptexextrastep;
      d_sfrac += d_sfracextrastep;
      d_ptex += d_sfrac >> 16;
            d_sfrac &= 0xFFFF;
      d_tfrac += d_tfracextrastep;
      if (d_tfrac & 0x10000)
      {
        d_ptex += r_affinetridesc.skinwidth;
        d_tfrac &= 0xFFFF;
      }
#else
            _g->d_s += _g->d_ptexextrastep_s16p16;
            _g->d_t += _g->d_ptexextrastep_t16p16;
#endif

            _g->d_light += _g->d_lightextrastep;
            _g->d_zi += _g->d_ziextrastep;
            _g->errorterm -= _g->erroradjustdown;
        }
        else
        {
            _g->d_pdest += _g->d_pdestbasestep;
            _g->d_pz += _g->d_pzbasestep;
            _g->d_aspancount += _g->ubasestep;
#if NO_MINIMIZE
      d_ptex += d_ptexbasestep;
      d_sfrac += d_sfracbasestep;
      d_ptex += d_sfrac >> 16;
      d_sfrac &= 0xFFFF;
      d_tfrac += d_tfracbasestep;
      if (d_tfrac & 0x10000)
      {
        d_ptex += r_affinetridesc.skinwidth;
        d_tfrac &= 0xFFFF;
      }
#else
            _g->d_s += _g->d_ptexbasestep_s16p16;
            _g->d_t += _g->d_ptexbasestep_t16p16;
#endif
            _g->d_light += _g->d_lightbasestep;
            _g->d_zi += _g->d_zibasestep;
        }
    }
    while (--height);
}

#endif  // !id386

/*
 ===================
 D_PolysetSetUpForLineScan
 ====================
 */
void D_PolysetSetUpForLineScan(fixed8_t startvertu, fixed8_t startvertv, fixed8_t endvertu, fixed8_t endvertv)
{
    QDFLOAT dm, dn;
    int tm, tn;
    const adivtab_t *ptemp;

// TODO: implement x86 version

    _g->errorterm = -1;

    tm = endvertu - startvertu;
    tn = endvertv - startvertv;

    if (((tm <= 16) && (tm >= -15)) && ((tn <= 16) && (tn >= -15)))
    {
        ptemp = &adivtab[((tm + 15) << 5) + (tn + 15)];
        _g->ubasestep = ptemp->quotient;
        _g->erroradjustup = ptemp->remainder;
        _g->erroradjustdown = tn;
    }
    else
    {
        dm = (QDFLOAT) tm;
        dn = (QDFLOAT) tn;

        FloorDivMod(dm, dn, &_g->ubasestep, &_g->erroradjustup);

        _g->erroradjustdown = tn; //next-hack: why was it dn ?
    }
}

#if !id386

/*
 ================
 D_PolysetCalcGradients
 ================
 */
void D_PolysetCalcGradients(int skinwidth)
{
    (void) skinwidth;
    float xstepdenominv, ystepdenominv, t0, t1;
    float p01_minus_p21, p11_minus_p21, p00_minus_p20, p10_minus_p20;

    p00_minus_p20 = _g->r_p0[0] - _g->r_p2[0];
    p01_minus_p21 = _g->r_p0[1] - _g->r_p2[1];
    p10_minus_p20 = _g->r_p1[0] - _g->r_p2[0];
    p11_minus_p21 = _g->r_p1[1] - _g->r_p2[1];

    xstepdenominv = 1.0f / (float) _g->d_xdenom;

    ystepdenominv = -xstepdenominv;

// ceil () for light so positive steps are exaggerated, negative steps
// diminished,  pushing us away from underflow toward overflow. Underflow is
// very visible, overflow is very unlikely, because of ambient lighting
    t0 = _g->r_p0[4] - _g->r_p2[4];
    t1 = _g->r_p1[4] - _g->r_p2[4];
    _g->r_lstepx = (int) ceilf_m((t1 * p01_minus_p21 - t0 * p11_minus_p21) * xstepdenominv);
    _g->r_lstepy = (int) ceilf_m((t1 * p00_minus_p20 - t0 * p10_minus_p20) * ystepdenominv);

    t0 = _g->r_p0[2] - _g->r_p2[2];
    t1 = _g->r_p1[2] - _g->r_p2[2];
    _g->r_sstepx = (int) ((t1 * p01_minus_p21 - t0 * p11_minus_p21) * xstepdenominv);
    _g->r_sstepy = (int) ((t1 * p00_minus_p20 - t0 * p10_minus_p20) * ystepdenominv);

    t0 = _g->r_p0[3] - _g->r_p2[3];
    t1 = _g->r_p1[3] - _g->r_p2[3];
    _g->r_tstepx = (int) ((t1 * p01_minus_p21 - t0 * p11_minus_p21) * xstepdenominv);
    _g->r_tstepy = (int) ((t1 * p00_minus_p20 - t0 * p10_minus_p20) * ystepdenominv);

    t0 = _g->r_p0[5] - _g->r_p2[5];
    t1 = _g->r_p1[5] - _g->r_p2[5];
    _g->r_zistepx = (int) ((t1 * p01_minus_p21 - t0 * p11_minus_p21) * xstepdenominv);
    _g->r_zistepy = (int) ((t1 * p00_minus_p20 - t0 * p10_minus_p20) * ystepdenominv);
#if NO_MINIMIZE
#if id386
  a_sstepxfrac = r_sstepx << 16;
  a_tstepxfrac = r_tstepx << 16;
#else
  a_sstepxfrac = r_sstepx & 0xFFFF;
  a_tstepxfrac = r_tstepx & 0xFFFF;
#endif

  a_ststepxwhole = skinwidth * (r_tstepx >> 16) + (r_sstepx >> 16);
#else
    _g->a_sstepx = _g->r_sstepx;
    _g->a_tstepx = _g->r_tstepx;
#endif
}

#endif  // !id386

#if 0
byte gelmap[256];
void InitGel (byte *palette)
{
  int   i;
  int   r;

  for (i=0 ; i<256 ; i++)
  {
//    r = (palette[i*3]>>4);
    r = (palette[i*3] + palette[i*3+1] + palette[i*3+2])/(16*3);
    gelmap[i] = /* 64 */ 0 + r;
  }
}
#endif

#if !id386

#if WIN32
int alias_drawn_pixels = 0;
int aliasPotentiallyDrawablePixels = 0;
int         alias_flash_accesses = 0;
int        aliasMtodDataLoaded = 0;
int        aliasPixLoeaded = 0 ;
#endif
/*
 ================
 D_PolysetDrawSpans8
 ================
 */
#if LAZY_MTOD_LOAD
#if ASYNCH_ALIAS_SINGLE_RENDERING
#if MTRIANGLE_HAS_OFFSET_DATA
#error
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
              flushAliasPendingPixel(); /* flush the pixel, if any*/\
              if (isOnExternalFlash(_g->d_mtod)) \
              {\
                if (loadMtodWorthy) \
                { \
                  _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,\
                                        (byte*) r_affinetridesc.paliashdr->extMemAddress +\
                                        (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),\
                                        (sizeof(_g->d_mtod->offsets[0]) * (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber) + 3) & ~3 );\
                  interleavedSpiFlashAsynchReadByteDMA( &_g->d_ptex[_g->d_mtod->offsets[((ls + APPROX_X*0x8000) >> 16) - offsetS] + ((lt + APPROX_Y*0x8000) >> 16)]); \
                }\
                else \
                { \
                  uint16_t offset; \
                  extMemGetDataFromAddress(&offset,\
                                          (byte*) &_g->d_mtod->offsets[((ls + APPROX_X*0x8000) >> 16) - offsetS],\
                                          sizeof(offset));\
                  interleavedSpiFlashAsynchReadByteDMA( &_g->d_ptex[offset + ((lt + APPROX_Y*0x8000) >> 16)]); \
                }\
              }\
              else\
              {\
                   interleavedSpiFlashAsynchReadByteDMA( &_g->d_ptex[_g->d_mtod->offsets[((ls + APPROX_X*0x8000) >> 16) - offsetS] + ((lt + APPROX_Y*0x8000) >> 16)]); \
              }\
              _g->aliasPendingLight = (llight & 0xFF00); \
              _g->aliasPendingAddress = lpdest; \
              _g->aliasPendingPixel = 1; \
              *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;

#elif MODELS_HAVE_ORIGINAL_SKIN_TOO
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
              flushAliasPendingPixel(); /* flush the pixel, if any*/\
              extMemAsynchReadByteFromAddress( (uint32_t)_g->r_affinetridesc.pOriginalskin  + (ls >> 16) + (lt >> 16) * _g->r_affinetridesc.skinwidth); \
              _g->aliasPendingLight = (llight & 0xFF00); \
              _g->aliasPendingAddress = lpdest; \
              _g->aliasPendingPixel = 1; \
              *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;

#elif 1
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
              flushAliasPendingPixel(); /* flush the pixel, if any*/\
              if (isOnExternalFlash(_g->d_mtod)) \
              {\
                   _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,\
                                         (byte*) r_affinetridesc.paliashdr->extMemAddress +\
                                         (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),\
                                         (sizeof(*_g->d_mtod) + sizeof(uint16_t) * r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3 );\
                    _g->d_ptex =  (byte *)r_affinetridesc.pskin  - _g->d_mtod->bufferOffset;\
              }\
              interleavedSpiFlashAsynchReadByteDMA( &_g->d_ptex[_g->d_mtod ->offsets[((ls + APPROX_X*0x8000) >> 16) - _g->d_mtod->offsetS] + ((lt + APPROX_Y*0x8000) >> 16)]); \
              _g->aliasPendingLight = (llight & 0xFF00); \
              _g->aliasPendingAddress = lpdest; \
              _g->aliasPendingPixel = 1; \
              *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;

#else
static inline void flushAliasPixels(void)
{
  // wait until mtod has been loaded
  extMemWaitAsynchDataRead();
  // flush queued pixels
  while(_g->pendingAliasPixels--)
  {
    int idx = _g->pendingAliasPixels;
    uint16_t ls = _g->pendingLs[idx];
    uint16_t lt = _g->pendingLt[idx];
    uint8_t pix =  extMemGetByteFromAddress( &_g->d_ptex[_g->d_mtod ->offsets[ls  - _g->d_mtod->offsetS] + lt]);
    *_g->pendingAliasPixelDestPtr[idx] = ((byte *)acolormap)[pix | _g->pendingAliasLight[idx]];
  }
  _g->pendingAliasPixels = 0;
}
static inline void addAliasAsynchPixel(uint16_t llight, uint8_t *lpdest, int lls, int llt)
{
  // Are we out of seats? Flush
  if (_g->pendingAliasPixels >= MAX_PENDING_ALIAS_PIXELS)
  {
    flushAliasPixels();
  }
  // if mtod loaded, just render the pixel.
  if (0 == _g->pendingAliasPixels)
  {
    int pix =  extMemGetByteFromAddress(  &_g->d_ptex[_g->d_mtod ->offsets[((lls + APPROX_X*0x8000) >> 16) - _g->d_mtod->offsetS] + ((llt + APPROX_Y*0x8000) >> 16)]); \
    *lpdest = ((byte *)acolormap)[pix + (llight & 0xFF00)]; \
    return;
  }
  // if we are here, mtod has not been loaded yet or we can still queue pixels.
  // store where to find the pixel
  _g->pendingLs[_g->pendingAliasPixels] = (lls + APPROX_X) >> 16;
  _g->pendingLs[_g->pendingAliasPixels] = (llt + APPROX_Y) >> 16;
  // store light
  _g->pendingAliasLight[_g->pendingAliasPixels] =  (llight & 0xFF00);
   // store where to store
  _g->pendingAliasPixelDestPtr[_g->pendingAliasPixels] = lpdest;
  _g->pendingAliasPixels++;

}
#error
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
              if (isOnExternalFlash(_g->d_mtod)) \
              {\
                   _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,\
                                         (uint8_t*) r_affinetridesc.paliashdr->extMemAddress +\
                                         (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),\
                                         (sizeof(*_g->d_mtod) + sizeof(uint16_t) * r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3 );\
                    _g->d_ptex =  (uint8_t *)r_affinetridesc.pskin  - _g->d_mtod->bufferOffset;\
                    /* store first pixel data*/ \
                    _g->pendingLs[0] = (ls + APPROX_X) >> 16; \
                    _g->pendingLs[0] = (lt + APPROX_Y) >> 16; \
                    /* store light*/ \
                    _g->pendingAliasLight[0] =  (llight & 0xFF00);\
                     /* store where to store*/ \
                    _g->pendingAliasPixelDestPtr[0] = lpdest;\
                    _g->pendingAliasPixels = 1;\
              } \
              else \
              { \
                addAliasAsynchPixel(llight, lpdest, ls, lt);\
              } \
              *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;
#endif
#else
#error
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
              if (isOnExternalFlash(_g->d_mtod)) \
              {\
                   _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,\
                                         (byte*) r_affinetridesc.paliashdr->extMemAddress +\
                                         (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),\
                                         (sizeof(*_g->d_mtod) + sizeof(uint16_t) * r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3 );\
                    _g->d_ptex =  (byte *)r_affinetridesc.pskin  - _g->d_mtod->bufferOffset;\
              }\
            int pix =  /*extMemGetByteFromAddress*/ interleavedSpiFlashReadByteDMA( &_g->d_ptex[_g->d_mtod ->offsets[((ls + APPROX_X*0x8000) >> 16) - _g->d_mtod->offsetS] + ((lt + APPROX_Y*0x8000) >> 16)]); \
            *lpdest = ((byte *)acolormap)[pix + (llight & 0xFF00)]; \
            *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;
#endif

#else
#define drawPolysetPixelSingle() \
        if ((lzi >> 16) >= *lpz) \
        { \
            int pix =  extMemGetByteFromAddress( &lptex[td->offsets[((ls + APPROX_X*0x8000) >> 16) - td->offsetS] + ((lt + APPROX_Y*0x8000) >> 16)]); \
            *lpdest = ((byte *)acolormap)[pix + (llight & 0xFF00)]; \
            *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;
#endif
#define drawPolysetPixel() \
        if ((lzi >> 16) >= *lpz) \
        { \
            int pix =  lptex[offsets[((ls + APPROX_X*0x8000) >> 16)] + ((lt + APPROX_Y*0x8000) >> 16)]; \
            *lpdest = ((byte *)_g->acolormap)[pix + (llight & 0xFF00)]; \
            *lpz = lzi >> 16; \
        } \
        lpdest++;  \
        lzi += _g->r_zistepx;  \
        lpz++; \
        llight += _g->r_lstepx; \
        ls += _g->a_sstepx; lt += _g->a_tstepx;

static inline __attribute__ ((always_inline)) void drawPolysetSpanFromInternalMemory(spanpackage_t *pspanpackage, short lcount)
{
    byte *lpdest;

    short *lpz;
    int ls, lt;
    lpdest = pspanpackage->pdest;
    lpz = pspanpackage->pz;

    lt = pspanpackage->t;

    int lzi = pspanpackage->zi;
    int llight = pspanpackage->light;

    ls = pspanpackage->s;

    int zistepx = _g->r_zistepx;
    int a_sstepx = _g->a_sstepx;
    int a_tstepx = _g->a_tstepx;
   int lstepx = _g->r_lstepx;
   byte *lptex = (byte*) _g->r_affinetridesc.pOriginalskin;
   int width = _g->r_affinetridesc.skinwidth;
   byte * colormap = (byte *)_g->acolormap;
   while (lcount--)
   {
     if ((lzi >> 16) >= *lpz)
     {
         *lpz = lzi >> 16;
         int pix =  lptex[(ls  >> 16) + (lt  >> 16) * width];
         *lpdest = colormap[pix + (llight & 0xFF00)];
     }
     lpdest++;
     lzi += zistepx;
     llight += lstepx;

     lpz++;
     ls += a_sstepx;
     lt += a_tstepx;
   }
}
void drawPolysetSpan(spanpackage_t *pspanpackage, short lcount)
{
    byte *lpdest;

    short *lpz;
    int ls, lt;
    lpdest = pspanpackage->pdest;
    lpz = pspanpackage->pz;

    lt = pspanpackage->t;

    int lzi = pspanpackage->zi;
    int llight = pspanpackage->light;

    mtriangleOffsetData_t *td = _g->d_mtod;

#if MTRIANGLE_HAS_OFFSET_DATA
   ls = pspanpackage->s - (r_affinetridesc.ptriangles[_g->d_trinum].offsetS << 16);
#else
#if CACHE_SKINS_TO_FLASH

if (_g->originalSkinInInternalFlash)
{
    ls = pspanpackage->s;
}
else
#endif
{
    ls = pspanpackage->s - (td->offsetS << 16) + APPROX_X * 0x8000; // note this was explicit after shift.
}
#endif

    uint16_t *offsets = td->offsets;

    int zistepx = _g->r_zistepx;
    int a_sstepx = _g->a_sstepx;
    int a_tstepx = _g->a_tstepx;
#if CACHE_SKINS_TO_FLASH
    if (_g->originalSkinInInternalFlash)
    {
       int lstepx = _g->r_lstepx;
       byte *lptex = (byte*) _g->r_affinetridesc.pOriginalskin;
       int width = _g->r_affinetridesc.skinwidth;
       byte * colormap = (byte *)_g->acolormap;
       while (lcount--)
       {
         if ((lzi >> 16) >= *lpz)
         {
             *lpz = lzi >> 16;
             int pix =  lptex[(ls  >> 16) + (lt  >> 16) * width];
             *lpdest = colormap[pix + (llight & 0xFF00)];
         }
         lpdest++;
         lzi += zistepx;
         llight += lstepx;

         lpz++;
         ls += a_sstepx;
         lt += a_tstepx;
       }
       return;
    }
#endif
#if WIN32
   byte *lptex = _g->d_ptex;
   while(lcount--)
   {
     drawPolysetPixel();
   }
#else
#define C_POLYSET_CODE 0
#if C_POLYSET_CODE
   int lstepx = _g->r_lstepx;
   byte *lptex = _g->d_ptex;
   byte *colormap = _g->acolormap;
   while (lcount--)
   {
     if ((lzi >> 16) >= *lpz)
     {
         *lpz = lzi >> 16;
         int pix =  lptex[offsets[((ls /*+ APPROX_X*0x8000*/) >> 16)] + ((lt + APPROX_Y*0x8000) >> 16)];
         *lpdest = ((byte *)colormap)[pix + (llight & 0xFF00)];
     }
     lpdest++;
     lzi += zistepx;
     llight += lstepx;

     lpz++;
     ls += a_sstepx;
     lt += a_tstepx;
   }
#else
    // next-hack: the union below is to pass easily parameters through floating point registers regardless what they actually are.
    union
    {
        float fv;
        void *ptr;
        int32_t v;
    } lptex, colormap, lstepx;
    lptex.ptr = _g->d_ptex;
    colormap.ptr = _g->acolormap;
    lstepx.v = _g->r_lstepx;
    //
    int tmp;
    float maxcount, f_offset;
    __ASM volatile
    (
        ".align(2)\n\t"
        "MOV r1, #0\n\t"
        "VMOV %[f_offset], %[tmp2]\n\t"
        "loop%=:\n\t"
        "ASR %[tmp], %[lzi], #16\n\t"   // get lzi>>16 int tmp
        "LDRSH %[tmp2], [%[lpz],  r1, LSL #1]\n\t"// get what it is stored
        "CMP %[tmp], %[tmp2]\n\t"// compare
        "BLT noAdd%=\n\t"// if smaller, skip
        "STRH %[tmp], [%[lpz], r1, LSL #1]\n\t"// larger: store
        "MLA %[tmp], %[a_sstepx], r1, %[ls]\n\t"
        "VMOV %[tmp2], %[f_offset]\n\t"
        "ASR %[tmp], %[tmp], #16\n\t"// in tmp ls >> 16
        "LDRH %[tmp], [%[tmp2], %[tmp], LSL #1]\n\t"// in tmp the offset
        "MLA r0, %[a_tstepx], r1, %[lt]\n\t"
        "VMOV %[tmp2], %[f_lptex]\n\t"
        "ADD %[tmp], %[tmp], r0, ASR #16\n\t"
        "VMOV r0, %[f_llightStepx]\n\t"
        "LDRB %[tmp], [%[tmp2], %[tmp]]\n\t"
        "MLA %[tmp2], r0, r1, %[llight]\n\t"
        "VMOV r0, %[f_colormap]\n\t"
        "BFI %[tmp2], %[tmp], #0, #8\n\t"
        "LDRB %[tmp2], [r0, %[tmp2]]\n\t"
        "ADD %[lzi], %[lzi], %[zistepx]\n\t"
        "STRB %[tmp2],[%[lpdest], r1]\n\t"
        "ADD r1, r1, #1\n\t"
        "CMP r1, %[count]\n\t"
        "BNE loop%=\n\t"
        "B end%=\n\t"
        "noAdd%=:\n\t"
        "ADD %[lzi], %[lzi], %[zistepx]\n\t"
        "ADD r1, r1, #1\n\t"
        "CMP r1, %[count]\n\t"
        "BNE loop%=\n\t"
        "end%=:\n\t"
        :
        [tmp] "=&r" (tmp),
        [tmp2] "+r" (offsets),
        [lzi] "+r" (lzi),
        [lpz] "+r" (lpz),
        [llight] "+r" (llight),
        [lpdest] "+r" (lpdest),
        [zistepx] "+r" (zistepx),
        [ls] "+r" (ls),
        [lt] "+r" (lt),
        [a_sstepx] "+r" (a_sstepx),
        [a_tstepx] "+r" (a_tstepx),
        [count] "+r" (lcount),
        [maxcount] "=&w" (maxcount),
        [f_offset] "=&w" (f_offset)
        :// using floating-point registers to increase number of available registers.
        [f_lptex] "w" (lptex.fv),
        [f_colormap] "w" (colormap.fv),
        [f_llightStepx] "w" (lstepx.fv)

        : "cc", "r0", "r1"
    );
#endif
#endif
}
__attribute__ ((always_inline)) static inline void D_PolysetDrawSpans8(spanpackage_t *pspanpackage)
{
    int lcount;
    byte *lpdest;
    int llight;
    int lzi;
    short *lpz;
    int ls;
    int lt;

    #if CACHE_SKINS_TO_FLASH
    if (_g->originalSkinInInternalFlash)
    {
        _g->d_ptex = (byte*) _g->r_affinetridesc.pOriginalskin;
        do
        {
            lcount = _g->d_aspancount - pspanpackage->count;
            _g->errorterm += _g->erroradjustup;
            if (_g->errorterm >= 0)
            {
                _g->d_aspancount += _g->d_countextrastep;
                _g->errorterm -= _g->erroradjustdown;
            }
            else
            {
                _g->d_aspancount += _g->ubasestep;
            }
            if (lcount)
            {
                drawPolysetSpanFromInternalMemory(pspanpackage, lcount);

            }

            pspanpackage++;
        }
        while (pspanpackage->count != -999999);
        return;
    }

    #endif


    // is it better loading all or singularly ?
#define TIME_PER_ACCESS   12 // 12 ?11 better //30 // 65 is measured but does not yield best results.
#define TIME_PER_BYTE 1

    spanpackage_t *bpspanpackage = pspanpackage;
    int acnt = _g->d_aspancount;
    int errt = _g->errorterm;
    int pixAmount = 0;
    int timeAll = 0, timeSingle = 1;
    // timeAll is set to 0 and timeSingle1 so that if the _g->d_ptex was already loaded,
    // the faster drawing is used.
    if (isOnExternalFlash(_g->d_mtod) || _g->d_ptex == NULL || isOnExternalFlash(_g->d_ptex))
    {
        do
        {
            pixAmount += acnt - pspanpackage->count;
            errt += _g->erroradjustup;
            if (errt >= 0)
            {
                acnt += _g->d_countextrastep;
                errt -= _g->erroradjustdown;
            }
            else
            {
                acnt += _g->ubasestep;
            }
            pspanpackage++;
        }
        while (pspanpackage->count != -999999);
        // restore spanpackage.
        pspanpackage = bpspanpackage;
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
        timeAll = 2 * TIME_PER_ACCESS + ((_g->r_affinetridesc.triangleSize + 3) & ~3) * TIME_PER_BYTE
            + ((sizeof(uint16_t) * _g->r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3) * TIME_PER_BYTE;
        ;
#else
    timeAll = TIME_PER_ACCESS + ((r_affinetridesc.triangleSize + 3) & ~3) * TIME_PER_BYTE;

#endif
        timeSingle = TIME_PER_ACCESS * pixAmount + TIME_PER_BYTE;
    }
    if (timeAll < timeSingle) // note: this is true even when the mtod & triangle are already loaded.
    {  // better load all
        flushAliasPendingPixel();
        do
        {
            lcount = _g->d_aspancount - pspanpackage->count;
            _g->errorterm += _g->erroradjustup;
            if (_g->errorterm >= 0)
            {
                _g->d_aspancount += _g->d_countextrastep;
                _g->errorterm -= _g->erroradjustdown;
            }
            else
            {
                _g->d_aspancount += _g->ubasestep;
            }
            if (lcount)
            {
#if !ALWAYS_LOAD_MTOD
                if (isOnExternalFlash(_g->d_mtod))
                {
#if MTRIANGLE_HAS_OFFSET_DATA

    _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,
                                         (byte*) r_affinetridesc.paliashdr->extMemAddress +
                                         (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),
                                         (sizeof(_g->d_mtod->offsets[0]) * (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber) + 3) & ~3 );
#else
                    _g->d_mtod = extMemGetDataFromAddress(_g->r_affinetridesc.tempTriangleOffsetData,
                        (byte*) _g->r_affinetridesc.paliashdr->extMemAddress + (_g->r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),
                        (sizeof(*_g->d_mtod) + sizeof(uint16_t) * _g->r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3);
#endif
#if WIN32
#if MTRIANGLE_HAS_OFFSET_DATA
               if ((uint32_t) ( (byte*) r_affinetridesc.paliashdr->extMemAddress +
                                      (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2)) &3)
                               printf("Err,mtod %p\r\n", ((byte *)r_affinetridesc.pskin  + r_affinetridesc.ptriangles[_g->d_trinum].startOffset));

               if ((uint32_t) ((byte *)r_affinetridesc.pskin  + r_affinetridesc.ptriangles[_g->d_trinum].startOffset) &3)
                               printf("Err, tridata %p\r\n", ((byte *)r_affinetridesc.pskin  + r_affinetridesc.ptriangles[_g->d_trinum].startOffset));
#else
               if ((uint32_t) ( (byte*) _g->r_affinetridesc.paliashdr->extMemAddress +
                                      (_g->r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2)) &3)
                               printf("Err,mtod %p\r\n", ((byte *)_g->r_affinetridesc.pskin  + _g->d_mtod->startOffset));

               if ((uint32_t) ((byte *)_g->r_affinetridesc.pskin  + _g->d_mtod->startOffset) &3)
                               printf("Err, tridata %p\r\n", ((byte *)_g->r_affinetridesc.pskin  + _g->d_mtod->startOffset));
#endif
           #endif
                }
                if (NULL == _g->d_ptex || isOnExternalFlash(_g->d_ptex))
                {
#if MTRIANGLE_HAS_OFFSET_DATA
               _g->d_ptex =   (byte *) extMemGetDataFromAddress(r_affinetridesc.tempTrianglePixBuffer, (byte *)r_affinetridesc.pskin  + r_affinetridesc.ptriangles[_g->d_trinum].startOffset,
                                                  (r_affinetridesc.triangleSize + 3) & ~3) - r_affinetridesc.ptriangles[_g->d_trinum].bufferOffset - r_affinetridesc.ptriangles[_g->d_trinum].startOffset;

#else
                    _g->d_ptex = (byte*) extMemGetDataFromAddress(_g->r_affinetridesc.tempTrianglePixBuffer,
                        (byte*) _g->r_affinetridesc.pskin + _g->d_mtod->startOffset, (_g->r_affinetridesc.triangleSize + 3) & ~3) - _g->d_mtod->bufferOffset
                        - _g->d_mtod->startOffset;
#endif
                }

#else
         mtriangleOffsetData_t *td =  pspanpackage->mtod;

   #endif

                drawPolysetSpan(pspanpackage, lcount);

            }

            pspanpackage++;
        }
        while (pspanpackage->count != -999999);
    }
    else
    {
#if MTRIANGLE_HAS_OFFSET_DATA
    _g->d_ptex =  (byte *)r_affinetridesc.pskin  - r_affinetridesc.ptriangles[_g->d_trinum].bufferOffset;
    int offsetS = r_affinetridesc.ptriangles[_g->d_trinum].offsetS;
    int loadMtodWorthy = timeSingle * 4 > r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber * 2 * TIME_PER_BYTE + TIME_PER_ACCESS;
#endif
        do
        {
            lcount = _g->d_aspancount - pspanpackage->count;
            _g->errorterm += _g->erroradjustup;
            if (_g->errorterm >= 0)
            {
                _g->d_aspancount += _g->d_countextrastep;
                _g->errorterm -= _g->erroradjustdown;
            }
            else
            {
                _g->d_aspancount += _g->ubasestep;
            }
            if (lcount)
            {
#if !ALWAYS_LOAD_MTOD
#if !LAZY_MTOD_LOAD
#error
           if (isOnExternalFlash(_g->d_mtod))
           {
                _g->d_mtod =  extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,
                                      (byte*) r_affinetridesc.paliashdr->extMemAddress +
                                      (r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetDataPos << 2),
                                      (sizeof(*_g->d_mtod) + sizeof(uint16_t) * r_affinetridesc.ptriangles[_g->d_trinum].triangleOffsetNumber + 3) & ~3 );
                 _g->d_ptex =  (byte *)r_affinetridesc.pskin  - _g->d_mtod->bufferOffset;
           }
           pspanpackage->ptex = _g->d_ptex;
         mtriangleOffsetData_t *td = _g->d_mtod;
 #endif

#else
         mtriangleOffsetData_t *td =  pspanpackage->mtod;

   #endif
                lpdest = pspanpackage->pdest;
#if NO_MINIMIZE
         lptex = pspanpackage->ptex;
#endif
                lpz = pspanpackage->pz;

                ls = pspanpackage->s;
                lt = pspanpackage->t;

                llight = pspanpackage->light;
                lzi = pspanpackage->zi;

                while (lcount--)
                {
#if WIN32
        aliasPixelsDrawnSingle++;
#endif

                    drawPolysetPixelSingle();
                }
            }

            pspanpackage++;
        }
        while (pspanpackage->count != -999999);

    }
}
#endif  // !id386

/*
 ================
 D_PolysetFillSpans8
 ================
 */
void D_PolysetFillSpans8(spanpackage_t *pspanpackage)
{
    int color;

// FIXME: do z buffering

    color = _g->d_aflatcolor++;

    while (1)
    {
        int lcount;
        byte *lpdest;

        lcount = pspanpackage->count;

        if (lcount == -1)
            return;

        if (lcount)
        {
            lpdest = pspanpackage->pdest;

            do
            {
                *lpdest++ = color;
            }
            while (--lcount);
        }

        pspanpackage++;
    }
}

/*
 ================
 D_RasterizeAliasPolySmooth
 ================
 */
// BIG NOTE FOR MYSELF!!! IN R_AliasClipTriangle (r_alias.c) a local triangle is generated and, this function will be called
// from that (not directly, but through D_PolysetDraw()->D_DrawNonSubdiv()).
#if WIN32
int pixAlias = 0;
#endif
#if NO_MINIMIZE
void D_RasterizeAliasPolySmooth (void)
#else
void D_RasterizeAliasPolySmooth(int trinum)
#endif
{
    int initialleftheight, initialrightheight;
    int *plefttop, *prighttop, *pleftbottom, *prightbottom;
    int working_lstepx, originalcount;

    plefttop = _g->pedgetable->pleftedgevert0;
    prighttop = _g->pedgetable->prightedgevert0;

    pleftbottom = _g->pedgetable->pleftedgevert1;
    prightbottom = _g->pedgetable->prightedgevert1;

    initialleftheight = pleftbottom[1] - plefttop[1];
    initialrightheight = prightbottom[1] - prighttop[1];

//
// set the s, t, and light gradients, which are consistent across the triangle
// because being a triangle, things are affine
//
    D_PolysetCalcGradients(_g->r_affinetridesc.skinwidth);

//
// rasterize the polygon
//

//
// scan out the top (and possibly only) part of the left edge
//
    _g->d_pedgespanpackage = _g->a_spans;

    _g->ystart = plefttop[1];
    _g->d_aspancount = plefttop[0] - prighttop[0];

#if NO_MINIMIZE
  d_ptex = (byte *)r_affinetridesc.pskin + (plefttop[2] >> 16) +
      (plefttop[3] >> 16) * r_affinetridesc.skinwidth;
#else
    mtriangleOffsetData_t *mtod = NULL; //=  (mtriangleOffsetData_t *) ((byte*) r_affinetridesc.paliashdr + (r_affinetridesc.ptriangles[trinum].triangleOffsetDataPos << 2));
#if CACHEABLE_SKIN && CACHE_SKINS_TO_FLASH
    if (!_g->originalSkinInInternalFlash)
#endif
    {
    #if ALWAYS_LOAD_MTOD
       mtod = extMemGetDataFromAddress(r_affinetridesc.tempTriangleOffsetData,
                                       (byte*) r_affinetridesc.paliashdr->extMemAddress +
                                       (r_affinetridesc.ptriangles[trinum].triangleOffsetDataPos << 2),
                                       (sizeof(*mtod) + sizeof(uint16_t) * r_affinetridesc.ptriangles[trinum].triangleOffsetNumber + 3) & ~3 );
    #else
        mtod =
            (mtriangleOffsetData_t*) ((byte*) _g->r_affinetridesc.paliashdr->extMemAddress + (_g->r_affinetridesc.ptriangles[trinum].triangleOffsetDataPos << 2));
    #endif
        _g->r_affinetridesc.triangleSize = _g->r_affinetridesc.ptriangles[trinum].triangleSize;
        _g->d_mtod = mtod;
        _g->d_trinum = trinum;
    #if WIN32
        if (!mtod)
        {
            printf("NULL MTOD!!!!");
            system("pause");
        }
    #endif
    //    _g->d_pedgespanpackage->mtod = mtod;
        _g->r_affinetridesc.tempTrianglePixBuffer = (byte*) ((uint32_t) ((byte*) _g->r_affinetridesc.tempTriangleOffsetData + sizeof(*mtod)
            + sizeof(uint16_t) * _g->r_affinetridesc.ptriangles[trinum].triangleOffsetNumber + 3) & ~3);
        _g->d_ptex = NULL;
    #if WIN32
        pixAlias += _g->r_affinetridesc.triangleSize;
    #endif
    }
#endif



#if id386
  d_sfrac = (plefttop[2] & 0xFFFF) << 16;
  d_tfrac = (plefttop[3] & 0xFFFF) << 16;
#else
#if NO_MINIMIZE
  d_sfrac = plefttop[2] & 0xFFFF;
  d_tfrac = plefttop[3] & 0xFFFF;
#else
    // next-hack: we get the absolute s,t coordinate in the triangle.
    _g->d_s = plefttop[2];
    _g->d_t = plefttop[3];
#endif
#endif
    _g->d_light = plefttop[4];
    _g->d_zi = plefttop[5];

    _g->d_pdest = (byte*) _g->d_viewbuffer + _g->ystart * screenwidth + plefttop[0];
    _g->d_pz = _g->d_pzbuffer + _g->ystart * d_zwidth + plefttop[0];

    if (initialleftheight == 1)
    {
        _g->d_pedgespanpackage->pdest = _g->d_pdest;
        _g->d_pedgespanpackage->pz = _g->d_pz;
        _g->d_pedgespanpackage->count = _g->d_aspancount;
        //
#if NO_MINIMIZE
    _g->d_pedgespanpackage->ptex = _g->d_ptex;
#endif
        //
#if NO_MINIMIZE
        d_pedgespanpackage->sfrac = d_sfrac;
        d_pedgespanpackage->tfrac = d_tfrac;
    #else
        _g->d_pedgespanpackage->s = _g->d_s;
        _g->d_pedgespanpackage->t = _g->d_t;
//        _g->d_pedgespanpackage->mtod = mtod;
#endif
        // FIXME: need to clamp l, s, t, at both ends?
        _g->d_pedgespanpackage->light = _g->d_light;
        _g->d_pedgespanpackage->zi = _g->d_zi;

        _g->d_pedgespanpackage++;
    }
    else
    {
        D_PolysetSetUpForLineScan(plefttop[0], plefttop[1], pleftbottom[0], pleftbottom[1]);

#if id386
    d_pzbasestep = (d_zwidth + ubasestep) << 1;
    d_pzextrastep = d_pzbasestep + 2;
  #else
        _g->d_pzbasestep = d_zwidth + _g->ubasestep;
        _g->d_pzextrastep = _g->d_pzbasestep + 1;
#endif

        _g->d_pdestbasestep = screenwidth + _g->ubasestep;
        _g->d_pdestextrastep = _g->d_pdestbasestep + 1;

        // TODO: can reuse partial expressions here

        // for negative steps in x along left edge, bias toward overflow rather than
        // underflow (sort of turning the floor () we did in the gradient calcs into
        // ceil (), but plus a little bit)
        if (_g->ubasestep < 0)
            working_lstepx = _g->r_lstepx - 1;
        else
            working_lstepx = _g->r_lstepx;

        _g->d_countextrastep = _g->ubasestep + 1;
#if NO_MINIMIZE
    d_ptexbasestep = ((r_sstepy + r_sstepx * ubasestep) >> 16) +
        ((r_tstepy + r_tstepx * ubasestep) >> 16) *
        r_affinetridesc.skinwidth;
        #if id386
                d_sfracbasestep = (r_sstepy + r_sstepx * ubasestep) << 16;
                d_tfracbasestep = (r_tstepy + r_tstepx * ubasestep) << 16;
            #else
                d_sfracbasestep = (r_sstepy + r_sstepx * ubasestep) & 0xFFFF;
                d_tfracbasestep = (r_tstepy + r_tstepx * ubasestep) & 0xFFFF;
            #endif
      d_ptexextrastep = ((r_sstepy + r_sstepx * d_countextrastep) >> 16) +
        ((r_tstepy + r_tstepx * d_countextrastep) >> 16) *
        r_affinetridesc.skinwidth;
#else
        _g->d_ptexextrastep_s16p16 = ((_g->r_sstepy + _g->r_sstepx * _g->d_countextrastep));
        _g->d_ptexextrastep_t16p16 = ((_g->r_tstepy + _g->r_tstepx * _g->d_countextrastep));
        _g->d_ptexbasestep_s16p16 = ((_g->r_sstepy + _g->r_sstepx * _g->ubasestep));
        _g->d_ptexbasestep_t16p16 = ((_g->r_tstepy + _g->r_tstepx * _g->ubasestep));
#endif

        _g->d_lightbasestep = _g->r_lstepy + working_lstepx * _g->ubasestep;
        _g->d_zibasestep = _g->r_zistepy + _g->r_zistepx * _g->ubasestep;

#if id386
    d_sfracextrastep = (r_sstepy + r_sstepx*d_countextrastep) << 16;
    d_tfracextrastep = (r_tstepy + r_tstepx*d_countextrastep) << 16;
  #else
#if NO_MINIMIZE
    d_sfracextrastep = (r_sstepy + r_sstepx*d_countextrastep) & 0xFFFF;
    d_tfracextrastep = (r_tstepy + r_tstepx*d_countextrastep) & 0xFFFF;
    #else
        _g->d_mtod = mtod;

#endif
#endif
        _g->d_lightextrastep = _g->d_lightbasestep + working_lstepx;
        _g->d_ziextrastep = _g->d_zibasestep + _g->r_zistepx;
        D_PolysetScanLeftEdge(initialleftheight);
    }

//
// scan out the bottom part of the left edge, if it exists
//
    if (_g->pedgetable->numleftedges == 2)
    {
        int height;

        plefttop = pleftbottom;
        pleftbottom = _g->pedgetable->pleftedgevert2;

        height = pleftbottom[1] - plefttop[1];

// TODO: make this a function; modularize this function in general

        _g->ystart = plefttop[1];
        _g->d_aspancount = plefttop[0] - prighttop[0];

#if NO_MINIMIZE
d_ptex = (byte *)r_affinetridesc.pskin + (plefttop[2] >> 16) +
        (plefttop[3] >> 16) * r_affinetridesc.skinwidth;
    d_sfrac = 0;
    d_tfrac = 0;
#else
        _g->d_s = plefttop[2] & 0xFFFF0000;
        _g->d_t = plefttop[3] & 0xFFFF0000;
#endif
        _g->d_light = plefttop[4];
        _g->d_zi = plefttop[5];

        _g->d_pdest = (byte*) _g->d_viewbuffer + _g->ystart * screenwidth + plefttop[0];
        _g->d_pz = _g->d_pzbuffer + _g->ystart * d_zwidth + plefttop[0];

        if (height == 1)
        {
            _g->d_pedgespanpackage->pdest = _g->d_pdest;
            _g->d_pedgespanpackage->pz = _g->d_pz;
            _g->d_pedgespanpackage->count = _g->d_aspancount;
#if NO_MINIMIZE
      _g->d_pedgespanpackage->ptex = _g->d_ptex;
      d_pedgespanpackage->sfrac = d_sfrac;
      d_pedgespanpackage->tfrac = d_tfrac;
#else
            _g->d_pedgespanpackage->s = _g->d_s;
            _g->d_pedgespanpackage->t = _g->d_t;
//      _g->d_pedgespanpackage->mtod = mtod;
#endif
            // FIXME: need to clamp l, s, t, at both ends?
            _g->d_pedgespanpackage->light = _g->d_light;
            _g->d_pedgespanpackage->zi = _g->d_zi;

            _g->d_pedgespanpackage++;
        }
        else
        {
            D_PolysetSetUpForLineScan(plefttop[0], plefttop[1], pleftbottom[0], pleftbottom[1]);

            _g->d_pdestbasestep = screenwidth + _g->ubasestep;
            _g->d_pdestextrastep = _g->d_pdestbasestep + 1;

#if id386
      d_pzbasestep = (d_zwidth + ubasestep) << 1;
      d_pzextrastep = d_pzbasestep + 2;
  #else
            _g->d_pzbasestep = d_zwidth + _g->ubasestep;
            _g->d_pzextrastep = _g->d_pzbasestep + 1;
#endif

            if (_g->ubasestep < 0)
                working_lstepx = _g->r_lstepx - 1;
            else
                working_lstepx = _g->r_lstepx;

            _g->d_countextrastep = _g->ubasestep + 1;
#if NO_MINIMIZE
      d_ptexbasestep = ((r_sstepy + r_sstepx * ubasestep) >> 16) +
          ((r_tstepy + r_tstepx * ubasestep) >> 16) *
          r_affinetridesc.skinwidth;
  #if id386
      d_sfracbasestep = (r_sstepy + r_sstepx * ubasestep) << 16;
      d_tfracbasestep = (r_tstepy + r_tstepx * ubasestep) << 16;
  #else
      d_sfracbasestep = (r_sstepy + r_sstepx * ubasestep) & 0xFFFF;
      d_tfracbasestep = (r_tstepy + r_tstepx * ubasestep) & 0xFFFF;
  #endif
    d_ptexextrastep = ((r_sstepy + r_sstepx * d_countextrastep) >> 16) +
          ((r_tstepy + r_tstepx * d_countextrastep) >> 16) *
          r_affinetridesc.skinwidth;
#if id386
      d_sfracextrastep = ((r_sstepy+r_sstepx*d_countextrastep) & 0xFFFF)<<16;
      d_tfracextrastep = ((r_tstepy+r_tstepx*d_countextrastep) & 0xFFFF)<<16;
  #else
      d_sfracextrastep = (r_sstepy+r_sstepx*d_countextrastep) & 0xFFFF;
      d_tfracextrastep = (r_tstepy+r_tstepx*d_countextrastep) & 0xFFFF;
  #endif

#else
            _g->d_ptexbasestep_s16p16 = (_g->r_sstepy + _g->r_sstepx * _g->ubasestep);
            _g->d_ptexbasestep_t16p16 = (_g->r_tstepy + _g->r_tstepx * _g->ubasestep);
            _g->d_ptexextrastep_s16p16 = (_g->r_sstepy + _g->r_sstepx * _g->d_countextrastep);
            _g->d_ptexextrastep_t16p16 = (_g->r_tstepy + _g->r_tstepx * _g->d_countextrastep);
            _g->d_mtod = mtod;
#endif

            _g->d_lightbasestep = _g->r_lstepy + working_lstepx * _g->ubasestep;
            _g->d_zibasestep = _g->r_zistepy + _g->r_zistepx * _g->ubasestep;

            _g->d_lightextrastep = _g->d_lightbasestep + working_lstepx;
            _g->d_ziextrastep = _g->d_zibasestep + _g->r_zistepx;
            D_PolysetScanLeftEdge(height);
        }
    }

// scan out the top (and possibly only) part of the right edge, updating the
// count field
    _g->d_pedgespanpackage = _g->a_spans;
    D_PolysetSetUpForLineScan(prighttop[0], prighttop[1], prightbottom[0], prightbottom[1]);
    _g->d_aspancount = 0;
    _g->d_countextrastep = _g->ubasestep + 1;
    originalcount = _g->a_spans[initialrightheight].count;
    _g->a_spans[initialrightheight].count = -999999; // mark end of the spanpackages
#if WIN32
    int drawnPixels = alias_drawn_pixels;
#endif

    D_PolysetDrawSpans8(_g->a_spans);

// scan out the bottom part of the right edge, if it exists
    if (_g->pedgetable->numrightedges == 2)
    {
        int height;
        spanpackage_t *pstart;

        pstart = _g->a_spans + initialrightheight;
        pstart->count = originalcount;

        _g->d_aspancount = prightbottom[0] - prighttop[0];

        prighttop = prightbottom;
        prightbottom = _g->pedgetable->prightedgevert2;

        height = prightbottom[1] - prighttop[1];

        D_PolysetSetUpForLineScan(prighttop[0], prighttop[1], prightbottom[0], prightbottom[1]);

        _g->d_countextrastep = _g->ubasestep + 1;
        _g->a_spans[initialrightheight + height].count = -999999;
        // mark end of the spanpackages
        D_PolysetDrawSpans8(pstart);
    }
#if WIN32 &&0
    if (drawnPixels == alias_drawn_pixels)
    {
        FIXME("ONE TRIANGLE DID NOT DRAW");
    }
  #endif // WIN32
}

/*
 ================
 D_PolysetSetEdgeTable
 ================
 */
void D_PolysetSetEdgeTable(void)
{
    int edgetableindex;

    edgetableindex = 0; // assume the vertices are already in
    //  top to bottom order

//
// determine which edges are right & left, and the order in which
// to rasterize them
//
    if (_g->r_p0[1] >= _g->r_p1[1])
    {
        if (_g->r_p0[1] == _g->r_p1[1])
        {
            if (_g->r_p0[1] < _g->r_p2[1])
                _g->pedgetable = &edgetables[2];
            else
                _g->pedgetable = &edgetables[5];

            return;
        }
        else
        {
            edgetableindex = 1;
        }
    }

    if (_g->r_p0[1] == _g->r_p2[1])
    {
        if (edgetableindex)
            _g->pedgetable = &edgetables[8];
        else
            _g->pedgetable = &edgetables[9];

        return;
    }
    else if (_g->r_p1[1] == _g->r_p2[1])
    {
        if (edgetableindex)
            _g->pedgetable = &edgetables[10];
        else
            _g->pedgetable = &edgetables[11];

        return;
    }

    if (_g->r_p0[1] > _g->r_p2[1])
        edgetableindex += 2;

    if (_g->r_p1[1] > _g->r_p2[1])
        edgetableindex += 4;

    _g->pedgetable = &edgetables[edgetableindex];
}

