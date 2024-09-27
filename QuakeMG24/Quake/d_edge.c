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

// d_edge.c
#include "quakedef.h"
#include "d_local.h"

#if WIN32
uint8_t allowMipMapReduction;
#endif
//static int	miplevel;

// FIXME: should go away
extern void R_RotateBmodel(void);
extern void R_TransformFrustum(void);

/*
 ==============
 D_DrawPoly

 ==============
 */
void D_DrawPoly(void)
{
// this driver takes spans, not polygons
}

/*
 =============
 D_MipLevelForScale
 =============
 */
int D_MipLevelForScale(float scale)
{
    int lmiplevel;
#if 0
	if (scale >= d_scalemip[0] )
		lmiplevel = 0;
	else if (scale >= d_scalemip[1] )
		lmiplevel = 1;
	else if (scale >= d_scalemip[2] )
		lmiplevel = 2;
	else
		lmiplevel = 3;
#else
    if (scale >= 1.0f)
        lmiplevel = 0;
    else if (scale >= 0.4f)
        lmiplevel = 1;
    else if (scale >= 0.2f)
        lmiplevel = 2;
    else
        lmiplevel = 3;

#endif
    if (lmiplevel < d_minmip)
        lmiplevel = d_minmip;

    return lmiplevel;
}

/*
 ==============
 D_DrawSolidSurface
 ==============
 */

// FIXME: clean this up
#define ENABLESUBMODEL  1
void D_DrawSolidSurface(surf_t *surf, int color)
{
    espan_t *span;
    byte *pdest;
    int u, u2, pix;

    pix = (color << 24) | (color << 16) | (color << 8) | color;
#if OLD_SPAN_METHOD
	for (span=surf->spans ; span ; span=span->pnext)
#else
    int spanIndex;
#if ESPANS_HAVE_V
    for (span = getSurfSpans(surf, 1) ; span ; span = getNextSpan(span, 1))
#else
    for (spanIndex = surf->spansIdx; spanIndex; spanIndex = span->nextSpanIdx)
#endif
#endif
    {
#if !ESPANS_HAVE_V
        span = &_g->basespan_p[spanIndex];
        pdest = (byte*) _g->d_viewbuffer + screenwidth * _g->basespanV_p[spanIndex];
#else
        pdest = (byte *)_g->d_viewbuffer + screenwidth * span->v;
#endif
        u = span->u;
        u2 = span->u + span->count - 1;
        ((byte*) pdest)[u] = pix;

        if (u2 - u < 8)
        {
            for (u++; u <= u2; u++)
                ((byte*) pdest)[u] = pix;
        }
        else
        {
            for (u++; u & 3; u++)
                ((byte*) pdest)[u] = pix;

            u2 -= 4;
            for (; u <= u2; u += 4)
                *(int*) ((byte*) pdest + u) = pix;
            u2 += 4;
            for (; u <= u2; u++)
                ((byte*) pdest)[u] = pix;
        }
    }
}

/*
 ==============
 D_CalcGradients
 ==============
 */
DRAWSURF_SEC void D_CalcGradients(msurface_t *pface, int miplevel)
{
    float mipscale;
    vec3_t p_temp1;
    vec3_t p_saxis, p_taxis;
    float t;
    mipscale = 1.0 / (float) (1 << miplevel);

#if MSURFACE_HAS_TEXINFO_POINTER
    TransformVector(pface->texinfo->vecs[0], p_saxis);
    TransformVector(pface->texinfo->vecs[1], p_taxis);
#else
    mtexinfo_t *ti = getMsurfaceTexinfo(pface);
	TransformVector (ti->vecs[0], p_saxis);
	TransformVector (ti->vecs[1], p_taxis);
#endif
    t = xscaleinv * mipscale;
    _g->d_sdivzstepu = p_saxis[0] * t;
    _g->d_tdivzstepu = p_taxis[0] * t;

    t = yscaleinv * mipscale;
    _g->d_sdivzstepv = -p_saxis[1] * t;
    _g->d_tdivzstepv = -p_taxis[1] * t;

    _g->d_sdivzorigin = p_saxis[2] * mipscale - xcenter * _g->d_sdivzstepu -
    ycenter * _g->d_sdivzstepv;
    _g->d_tdivzorigin = p_taxis[2] * mipscale - xcenter * _g->d_tdivzstepu -
    ycenter * _g->d_tdivzstepv;

    VectorScale(_g->transformed_modelorg, mipscale, p_temp1);

    t = 0x10000 * mipscale;
#if MSURFACE_HAS_TEXINFO_POINTER
    _g->sadjust = ((fixed16_t) (DotProduct (p_temp1, p_saxis) * 0x10000 + 0.5)) - ((pface->texturemins[0] << 16) >> miplevel) + pface->texinfo->vecs[0][3] * t;
    _g->tadjust = ((fixed16_t) (DotProduct (p_temp1, p_taxis) * 0x10000 + 0.5)) - ((pface->texturemins[1] << 16) >> miplevel) + pface->texinfo->vecs[1][3] * t;
#else
	_g->sadjust = ((fixed16_t)(DotProduct (p_temp1, p_saxis) * 0x10000 + 0.5)) - ((pface->texturemins[0] << 16) >> miplevel) + ti->vecs[0][3]*t;
	_g->tadjust = ((fixed16_t)(DotProduct (p_temp1, p_taxis) * 0x10000 + 0.5)) - ((pface->texturemins[1] << 16) >> miplevel) + ti->vecs[1][3]*t;

#endif
//
// -1 (-epsilon) so we never wander off the edge of the texture
//
    _g->bbextents = ((pface->extents[0] << 16) >> miplevel) - 1;
    _g->bbextentt = ((pface->extents[1] << 16) >> miplevel) - 1;
}
/*
 ==============
 D_DrawSurfaces
 ==============
 */
#define TEST_PIX_SAVED_SAME_TEXTURE 1
#if TEST_PIX_SAVED_SAME_TEXTURE
#if USE_TEXTURE_METADATA
texture_t*  lastTexture = NULL;
#else
void *lastTextureEmd = NULL;
#endif
#endif // TEST_PIX_SAVED_SAME_TEXTURE

#if SORT_SURFS
AUX_SECTION uint16_t surfIdx[NUMSTACKSURFACES] __attribute__ ((aligned(4)));

DRAWSURF_SEC int surfCmp(const uint16_t *ia, const uint16_t *ib)
{
    surf_t *a = &_g->surfaces[*ia];
    surf_t *b = &_g->surfaces[*ib];
    int fa = getSurfFlags(a);
    int fb = getSurfFlags(b);
    int diff = fb - fa;    // reverse flag ordering, so we draw non lightmapped texture first.
    if (diff)
        return diff;
    if (!(fa & (SURF_DRAWBACKGROUND | SURF_DRAWSKY)))
    {
        msurface_t *pfacea, *pfaceb;
        pfacea = a->data;
        pfaceb = b->data;
#if MSURFACE_HAS_TEXINFO_POINTER
        diff = pfacea->texinfo->texture - pfaceb->texinfo->texture;

#else
        diff = getMsurfaceTexinfo(pfacea)->texture - getMsurfaceTexinfo(pfaceb)->texture;
#endif
        if (diff)
            return diff;
        return a->miplevel - b->miplevel;
    }
    return 0;
}
DRAWSURF_SEC void sortSurfs(void)
{
#define USE_TCB_FOR_SORTING 1
#if USE_TCB_FOR_SORTING
    uint16_t *tmpSurfIdx = (uint16_t *) textureCacheBuffer;
#else
    #define tmpSurfIdx surfIdx
#endif
    surf_t *s;
    int i;
    int j = 0;
    // pre-reduce the array not containing those surfaces that do not have spans
    for (s = &_g->surfaces[1], i = 1; s < _g->surface_p; i++, s++)
    {
        // do not even try to order the surfaces with no spans.
        if (!s->spansIdx)
            continue;
        tmpSurfIdx[j] = i;
        j++;
        int f = getSurfFlags(s);
        if (!(f & (SURF_DRAWBACKGROUND | SURF_DRAWSKY | SURF_DRAWTURB)))
        {
            // we also adjust surface mip level so that it will fit on the texture
            msurface_t *pface = (msurface_t*) s->data;
#if MSURFACE_HAS_TEXINFO_POINTER
            mtexinfo_t *ti = pface->texinfo;
#else
            mtexinfo_t *ti = getMsurfaceTexinfo(pface);
#endif
            // get size according to the miplevel we would like
            int size = (ti->texture->width * ti->texture->height) >> (2 * s->miplevel);
            // reduce size according to maximum we can have
            while (size > MAX_TEXTURE_SIZE)
            {
                size = size / 4;
                s->miplevel++;
            }
#if WIN32
            if (s->miplevel > 3)
            {
                FIXME("ERROR");
            }
            #endif
            // adjusted!
        }
        if (f & (SURF_DRAWSKY | SURF_DRAWTURB))
        {
            s->miplevel = 0;
        }
    }
    _g->surfNum = j;
    // now quicksort the surfaces
    qsort(tmpSurfIdx, _g->surfNum, sizeof(tmpSurfIdx[0]), (int (*)(const void*, const void*)) surfCmp);
#if USE_TCB_FOR_SORTING
    uint32_t *src = (uint32_t *) tmpSurfIdx;
    uint32_t *dst = (uint32_t *) surfIdx;
    unsigned int numwords =   (_g->surfNum * sizeof(tmpSurfIdx[0]) + 15) & ~15;
    for (unsigned int i = 0; i < numwords; i+= 16)
    {
        *dst ++ = *src++;
        *dst ++ = *src++;
        *dst ++ = *src++;
        *dst ++ = *src++;
    }
#endif
}
#endif // SORT_SURFS
DRAWSURF_SEC void D_DrawSurfaces(void)
{
    surf_t *s;
    msurface_t *pface;
    //surfcache_t		*pcurrentcache;
    vec3_t world_transformed_modelorg;
    vec3_t local_modelorg;
    int miplevel;
    _g->currententity = &cl_entities[0];
    TransformVector(_g->modelorg, _g->transformed_modelorg);
    VectorCopy(_g->transformed_modelorg, world_transformed_modelorg);

// TODO: could preset a lot of this at mode set time
#if 0
	if (r_drawflat)
	{
		for (s = &_g->surfaces[1] ; s<_g->surface_p ; s++)
		{
#if OLD_SPAN_METHOD
			if (!s->spans)
#else
            if (!s->spansIdx)
#endif
				continue;
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
			_g->d_zistepu = s->d_zistepu;
			_g->d_zistepv = s->d_zistepv;
#else
			_g->d_zistepu = getSurfD_zistepu(s);
			_g->d_zistepv = getSurfD_zistepv(s);
#endif
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
			_g->d_ziorigin = getSurfD_ziorigin(s);
#else
			_g->d_ziorigin = s->d_ziorigin;
#endif
#else
    vec3_t tempPnormal;
    float *tempModelOrg;
    tempModelOrg = modelorg;
    mplane_t *tempPlane = ((msurface_t*) s->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	float temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;
    d_zistepu = temp_d_zistepu;
    d_zistepv = temp_d_zistepv;
    d_ziorigin = temp_d_ziorigin;

#endif
			D_DrawSolidSurface (s, (int)s->data & 0xFF);
#if OLD_SPAN_METHOD
			D_DrawZSpans (s->spans);
#else
			D_DrawZSpans (getSurfSpans(s, 0));
#endif
		}
	}
	else
#endif
    {
#if TEST_PIX_SAVED_SAME_TEXTURE
#if USE_TEXTURE_METADATA
        lastTexture = NULL;
#else
        lastTextureEmd = NULL;
#endif
        int lastSurfFlags = 0;
#endif // TEST_PIX_SAVED_SAME_TEXTURE
#if SORT_SURFS
//        printf("Num surfaces before: %d\r\n", surface_p - &surfaces[1]);
        sortSurfs();
        clearTextureCache();
        for (int surfPos = 0; surfPos < _g->surfNum; surfPos++)
        {
            s = &_g->surfaces[surfIdx[surfPos]];
#else
		for (s = &surfaces[1] ; s<surface_p ; s++)
		{

#endif // SORT_SURFS

            if (!s->spansIdx)
                continue;
#if PROFILE_SPEED
			r_drawnpolycount++;
#endif
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
            _g->d_zistepu = s->d_zistepu;
            _g->d_zistepv = s->d_zistepv;
#else
			_g->d_zistepu = getSurfD_zistepu(s);
			_g->d_zistepv = getSurfD_zistepv(s);
#endif
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
			_g->d_ziorigin = getSurfD_ziorigin(s);
#else
            _g->d_ziorigin = s->d_ziorigin;
#endif
#else
    vec3_t tempPnormal;
    float *tempModelOrg;
    tempModelOrg = modelorg;
    mplane_t *tempPlane = ((msurface_t*) s->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	float temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;
    d_zistepu = temp_d_zistepu;
    d_zistepv = temp_d_zistepv;
    d_ziorigin = temp_d_ziorigin;
#endif
#define WAIT_HERE_FOR_LINE 1
#if WAIT_HERE_FOR_LINE
    {
        espan_t *span = getSurfSpans(s, 0);

        int spanIndex = span - _g->basespan_p;
        int iv = _g->basespanV_p[spanIndex];
#if !WIN32
        while ((iv + 1) * 320 >= displayData.displayDmaLineBuffersSent * PIXELS_PER_DMA_LINE )
        {
          // wait
        }
#endif
    }
#endif
            if (getSurfFlags(s) & SURF_DRAWSKY)
            {
                if (!(lastSurfFlags & SURF_DRAWSKY))
                {
                    R_MakeSky();
                    // this a dirty hack.
                    clearTextureCache();
                    // todo: I hope that sky has 128x128 texture width,height set!
                    textureLoaderHandler(NULL, r_skysource, 0, surfPos, _g->surfNum);
                }
                else
                {
                    textureLoaderHandler(r_skysource, r_skysource, 0, surfPos, _g->surfNum);
                }
                espan_t *span = getSurfSpans(s, 0);
                D_DrawSkyScans8(span);
                D_DrawZSpans(span);

            }
            else if (getSurfFlags(s) & SURF_DRAWBACKGROUND)
            {

                lastTextureEmd = NULL;

                textureLoaderHandler((lastSurfFlags & SURF_DRAWBACKGROUND) ? NULL : (void*) -1, NULL, 0, surfPos, _g->surfNum);

                // set up a gradient for the background surface that places it
                // effectively at infinity distance from the viewpoint
                _g->d_zistepu = 0;
                _g->d_zistepv = 0;
                _g->d_ziorigin = -0.9f;

                D_DrawSolidSurface(s, (int) r_clearcolor & 0xFF);

                D_DrawZSpans(getSurfSpans(s, 0));
            }
            else if (getSurfFlags(s) & SURF_DRAWTURB)
            {
                miplevel = 0;
                pface = s->data;
#if MSURFACE_HAS_TEXINFO_POINTER
                mtexinfo_t *ti = pface->texinfo;
#else
                mtexinfo_t *ti = getMsurfaceTexinfo(pface);
#endif // MSURFACE_HAS_TEXINFO_POINTER
#if 0
                if (lastTextureEmd != ti->texture->extmemdata[0])
                {

                  //                    memcpy (getGpBuffer(), (pixel_t *) ((byte *)ti->texture + ti->texture->offsets[0]),  ti->texture->width * ti->texture->height);

                 //   memcpy (getGpBuffer(), (pixel_t *) ti->texture->extmemdata[0],  ti->texture->width * ti->texture->height);
                    extMemGetDataFromAddress(getGpBuffer(), (pixel_t *) ti->texture->extmemdata[0],  ti->texture->width * ti->texture->height);
                }
                else
                {
                    pixSaved += ti->texture->width * ti->texture->height;
                }
                pixLoaded += ti->texture->width * ti->texture->height;
               _g->cacheblock = getGpBuffer();
#else
                textureLoaderHandler(lastTextureEmd, ti->texture->extmemdata[0], 0, surfPos, _g->surfNum);
                _g->cacheblock = getCurrentTextureCacheAddress();
#endif
                lastTextureEmd = ti->texture->extmemdata[0];

                _g->cachewidth = 64;
                if (s->insubmodel && ENABLESUBMODEL)
                {
                    // FIXME: we don't want to do all this for every polygon!
                    // TODO: store once at start of frame

                    _g->currententity = getSurfEntity(s);	//FIXME: make this passed in to R_RotateBmodel ()

                    VectorSubtract(_g->r_origin, VEC(getEntityOrigins(_g->currententity)), local_modelorg);

                    TransformVector(local_modelorg, _g->transformed_modelorg);

                    R_RotateBmodel();	// FIXME: don't mess with the frustum,
                                        // make entity passed in
                }

                D_CalcGradients(pface, miplevel);
                espan_t *span = getSurfSpans(s, 0);
                Turbulent8(span);
                D_DrawZSpans(span);

                if (s->insubmodel && ENABLESUBMODEL)
                {
                    //
                    // restore the old drawing state
                    // FIXME: we don't want to do this every time!
                    // TODO: speed up
                    //
                    _g->currententity = &cl_entities[0];
                    VectorCopy(world_transformed_modelorg, _g->transformed_modelorg);
                    VectorCopy(_g->base_vpn, _g->vpn);
                    VectorCopy(_g->base_vup, _g->vup);
                    VectorCopy(_g->base_vright, _g->vright);
                    VectorCopy(_g->base_modelorg, _g->modelorg);
                    R_TransformFrustum();
                }
            }
            else
            {

                if (s->insubmodel && ENABLESUBMODEL)
                {
                    // FIXME: we don't want to do all this for every polygon!
                    // TODO: store once at start of frame
                    _g->currententity = getSurfEntity(s); //FIXME: make this passed in to R_RotateBmodel ()
#if !ENTITY_HAS_SHORT_COORDS
					VectorSubtract (r_origin, currententity->origin, local_modelorg);
#else
                    VectorSubtract(_g->r_origin, VEC(getEntityOrigins(_g->currententity)), local_modelorg);
#endif
                    TransformVector(local_modelorg, _g->transformed_modelorg);

                    R_RotateBmodel();	// FIXME: don't mess with the frustum,
                                        // make entity passed in
                }
                pface = s->data;
                miplevel = getSurfMiplevel(s);
#if 0
				if (allowMipMapReduction && miplevel == 0)
				    miplevel = 1;
			// FIXME: make this passed in to D_CacheSurface

                _g->cacheblock = getSurfBuffer(pface, miplevel, &_g->cachewidth);
#else
                _g->cacheblock = getSurfBuffer(pface, surfPos, _g->surfNum, miplevel, &_g->cachewidth);
                //
#endif
                D_CalcGradients(pface, miplevel);
                espan_t *span = getSurfSpans(s, 0);
                D_DrawSpans8(span);
                D_DrawZSpans(span);

                if (s->insubmodel && ENABLESUBMODEL)
                {
                    //
                    // restore the old drawing state
                    // FIXME: we don't want to do this every time!
                    // TODO: speed up
                    //
                    _g->currententity = &cl_entities[0];
                    VectorCopy(world_transformed_modelorg, _g->transformed_modelorg);
                    VectorCopy(_g->base_vpn, _g->vpn);
                    VectorCopy(_g->base_vup, _g->vup);
                    VectorCopy(_g->base_vright, _g->vright);
                    VectorCopy(_g->base_modelorg, _g->modelorg);
                    R_TransformFrustum();
                }
            }
            lastSurfFlags = getSurfFlags(s);
        }
    }
}

