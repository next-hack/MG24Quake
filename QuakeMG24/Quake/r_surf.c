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
// r_surf.c: surface-related refresh code
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"
drawsurf_t r_drawsurf;

#if PRE_LIGHT_SURFACES
//int       surfrowbytes; // used by ASM files
unsigned *r_lightptr;
void *prowdestbase;
unsigned blockdivmask;
unsigned char *pbasesource;

int lightleft, sourcesstep, blocksize, sourcetstep;
int lightdelta, lightdeltastep;
int lightright, lightleftstep, lightrightstep, blockdivshift;

int r_stepback;
int r_numhblocks, r_numvblocks;
unsigned char *r_source, *r_sourcemax;
#endif
#if PRE_LIGHT_SURFACES
void R_DrawSurfaceBlock8_mip0 (void);
void R_DrawSurfaceBlock8_mip1 (void);
void R_DrawSurfaceBlock8_mip2 (void);
void R_DrawSurfaceBlock8_mip3 (void);

static void (*surfmiptable[4])(void) =
{
    R_DrawSurfaceBlock8_mip0,
    R_DrawSurfaceBlock8_mip1,
    R_DrawSurfaceBlock8_mip2,
    R_DrawSurfaceBlock8_mip3
};
#endif

/*
 ===============
 R_AddDynamicLights
 ===============
 */
#if USE_FLOAT_DIST
DRAWSURF_SEC void R_AddDynamicLights (void)
{
    msurface_t *surf;
    int lnum;
    int sd, td;
    float dist, rad, minlight;
    vec3_t impact, local;
    int s, t;
    int i;
    int smax, tmax;
    mtexinfo_t *tex;

    surf = r_drawsurf.surf;
    smax = (surf->extents[0]>>4)+1;
    tmax = (surf->extents[1]>>4)+1;
#if MSURFACE_HAS_TEXINFO_POINTER
    tex = surf->texinfo;
#else
    tex = getMsurfaceTexinfo(surf);
#endif
#if 1
#error
    unsigned int index = surf - _g->cl.worldmodel->brushModelData->surfaces;
    unsigned int nodeindex = _g->cl.worldmodel->brushModelData->surfNodeIndex[index];
    mplane_t *splitplane;
#if NODE_HAS_PLANE_POINTER
    splitplane = _g->cl.worldmodel->brushModelData->nodes[nodeindex].plane; // is it right ?

#else
    splitplane = Mod_GetNodePlane(&cl.worldmodel->brushModelData->nodes[nodeindex] , cl.worldmodel); // is it right ?
#endif
#if MSURFACE_HAS_PLANE_POINTER
    mplane_t *pplane = surf->plane;
#else
    mplane_t *pplane = getMsurfacePlane(surf);
#endif
#endif
    for (lnum=0; lnum < MAX_DLIGHTS; lnum++)
    {
        if (_g->cl_dlights[lnum].die < _g->cl.time || !_g->cl_dlights[lnum].radius)
        continue;
#if 0
#if !MARK_NODE_IN_SURFACE
        if ( !(surf->dlightbits & (1<<lnum) ) )
        continue;		// not lit by this light
        rad = cl_dlights[lnum].radius;

#else
#if !SEPARATE_BRUSH_MODEL_DATA
        unsigned int index = surf - cl.worldmodel->surfaces;
#else
#error
        unsigned int index = surf - cl.worldmodel->brushModelData->surfaces;
#endif
        unsigned int nodeindex = cl.worldmodel->brushModelData->surfNodeIndex[index];
 printf("ni %d\r\n", nodeindex);
#if USE_NODE_DLIGHTBITS
        if ( !(nodeDlightBits[nodeindex] & (1<<lnum) ))
        continue;
        rad = cl_dlights[lnum].radius;
#else
        mplane_t *splitplane;
#if !SEPARATE_BRUSH_MODEL_DATA
        splitplane = Mod_GetNodePlane(&cl.worldmodel->nodes[nodeindex] , cl.worldmodel); // is it right ?
#else
        splitplane = Mod_GetNodePlane(&cl.worldmodel->brushModelData->nodes[nodeindex] , cl.worldmodel); // is it right ?
#endif
#if DLIGHT_HAS_FLOAT_ORIGIN
        dist = DotProduct (cl_dlights[lnum].origin, splitplane->normal) - splitplane->dist;
#else
        dist = DotProduct (cl_dlights[lnum].iorigin_s, splitplane->normal) - splitplane->dist;
#endif
        rad = cl_dlights[lnum].radius;
        if (dist > rad || dist < -rad)
        continue;
#endif
#endif
#else
        dist = fabsf_m(DotProduct (_g->cl_dlights[lnum].iorigin_s, splitplane->normal) - getPlaneDist(splitplane));
        rad = _g->cl_dlights[lnum].radius;
        if (dist > rad) //|| dist < -rad)
        continue;
#endif
#if DLIGHT_HAS_FLOAT_ORIGIN
        dist = DotProduct (cl_dlights[lnum].origin, pplane->normal) - pplane->dist;
#else
        dist = DotProduct (_g->cl_dlights[lnum].iorigin_s, pplane->normal) - getPlaneDist(pplane);
#endif
        rad -= fabsf_m(dist);
#if PACK_DLIGHTS
        minlight = _g->cl_dlights[lnum].hasMinlight32 ? 32 : 0;
#else
        minlight = _g->cl_dlights[lnum].minlight;
#endif
        if (rad < minlight)
        continue;
        minlight = rad - minlight;

        for (i=0; i<3; i++)
        {
#if DLIGHT_HAS_FLOAT_ORIGIN
            impact[i] = cl_dlights[lnum].iorigin_s[i] - pplane->normal[i]*dist;
#else
            impact[i] = _g->cl_dlights[lnum].iorigin_s[i] - pplane->normal[i]*dist;
#endif
        }

        local[0] = DotProduct (impact, tex->vecs[0]) + tex->vecs[0][3];
        local[1] = DotProduct (impact, tex->vecs[1]) + tex->vecs[1][3];

        local[0] -= surf->texturemins[0];
        local[1] -= surf->texturemins[1];
        int tdd = local[1];
        for (t = 0; t < tmax; t++, tdd -=16)
        {
            if (tdd < 0)
            td = -tdd;
            else
            td = tdd;
            int sdd = local[0];
            for (s = 0; s < smax; s++, sdd -= 16)
            {
                if (sdd < 0)
                sd = -sdd;
                else
                sd = sdd;
                if (sd > td)
                dist = sd + (td >> 1);
                else
                dist = td + (sd >> 1);
                if (dist < minlight)
#ifdef QUAKE2
                {
                    unsigned temp;
                    temp = (rad - dist)*256;
                    i = t*smax + s;
                    if (!cl_dlights[lnum].dark)
                    blocklights[i] += temp;
                    else
                    {
                        if (blocklights[i] > temp)
                        blocklights[i] -= temp;
                        else
                        blocklights[i] = 0;
                    }
                }
#else
                _g->blocklights[t*smax + s] += (rad - dist)*256;
#endif
            }
        }
    }
}
#else
DRAWSURF_SEC void R_AddDynamicLights(void)
{
    msurface_t *surf;
    int lnum;
    int sd, td;
    int dist, rad, minlight;
    vec3_t impact, local;
    int s, t;
    int i;
    int smax, tmax;
    mtexinfo_t *tex;

    surf = r_drawsurf.surf;
    smax = (surf->extents[0] >> 4) + 1;
    tmax = (surf->extents[1] >> 4) + 1;
    tex = surf->texinfo;
   // unsigned int index = surf - _g->cl.worldmodel->brushModelData->surfaces;
    unsigned int nodeindex = surf->surfNodeIndex; // _g->cl.worldmodel->brushModelData->surfNodeIndex[index];
    mplane_t *splitplane;
    splitplane = _g->cl.worldmodel->brushModelData->nodes[nodeindex].plane; // is it right ?

    mplane_t *pplane = surf->plane;
    for (lnum = 0; lnum < MAX_DLIGHTS; lnum++)
    {
        if (_g->cl_dlights[lnum].die < _g->cl.time || !_g->cl_dlights[lnum].radius)
            continue;
        dist = abs(256 * (DotProduct (_g->cl_dlights[lnum].iorigin_s, splitplane->normal) - getPlaneDist(splitplane)));
        rad = 256 * _g->cl_dlights[lnum].radius;
        if (dist > rad) //|| dist < -rad)
            continue;
        dist = 256 * (DotProduct (_g->cl_dlights[lnum].iorigin_s, pplane->normal) - getPlaneDist(pplane));
        rad -= abs(dist);
        minlight = 256 * _g->cl_dlights[lnum].minlight;
        if (rad < minlight)
            continue;
        minlight = rad - minlight;

        for (i = 0; i < 3; i++)
        {
            impact[i] = _g->cl_dlights[lnum].iorigin_s[i] - pplane->normal[i] * dist * (1 / 256.0f);
        }

        local[0] = DotProduct (impact, tex->vecs[0]) + tex->vecs[0][3];
        local[1] = DotProduct (impact, tex->vecs[1]) + tex->vecs[1][3];

        local[0] -= surf->texturemins[0];
        local[1] -= surf->texturemins[1];
        int tdd = local[1];
        for (t = 0; t < tmax; t++, tdd -= 16)
        {
            if (tdd < 0)
                td = -tdd;
            else
                td = tdd;
            int sdd = local[0];
            BLOCKLIGHT_TYPE *pbl = &_g->blocklights[t * smax];
            for (s = 0; s < smax; s++, sdd -= 16)
            {
                if (sdd < 0)
                    sd = -sdd;
                else
                    sd = sdd;
                if (sd > td)
                    dist = 256 * (sd + (td >> 1));
                else
                    dist = 256 * (td + (sd >> 1));
                if (dist < minlight)
                    /*_g->blocklights[t*smax + s]*/pbl[s] += (rad - dist);
            }
        }
    }
}
#endif

/*
 ===============
 R_BuildLightMap

 Combine and scale multiple lightmaps into the 8.8 format in blocklights
 ===============
 */
#if WIN32
int lightcells = 0;
#endif // WIN32
DRAWSURF_SEC void R_BuildLightMap(void)
{
    int smax, tmax;
    int t;
    int i, size;
#if LIGHTMAP_ON_INTERNAL_FLASH
	byte		*lightmap;
	unsigned int	scale;
	int			maps;
#endif
    msurface_t *surf;

    surf = r_drawsurf.surf;

    smax = (surf->extents[0] >> 4) + 1;
    tmax = (surf->extents[1] >> 4) + 1;
    size = smax * tmax;
#if LIGHTMAP_ON_INTERNAL_FLASH
#if MSURFACE_HAS_SAMPLES_POINTER
	lightmap = surf->samples;
#else
    lightmap = getMsurfaceSamples(surf);
#endif

#if !SEPARATE_BRUSH_MODEL_DATA
	if (r_fullbright || !cl.worldmodel->lightdata)
#else
	if (r_fullbright || !_g->cl.worldmodel->brushModelData->lightdata)
#endif
	{
		for (i=0 ; i<size ; i++)
			_g->blocklights[i] = 0;
		return;
	}

// clear to ambient
	for (i=0 ; i<size ; i++)
		_g->blocklights[i] = _g->r_refdef.ambientlight<<8;


// add all the lightmaps
	if (lightmap)
		for (maps = 0 ; maps < MAXLIGHTMAPS && surf->styles[maps] != 255 ;
			 maps++)
		{
			scale = r_drawsurf.lightadj[maps];	// 8.8 fraction
			for (i=0 ; i<size ; i++)
				_g->blocklights[i] += lightmap[i] * scale;
			lightmap += size;	// skip to next lightmap
		}

// add all the dynamic lights
#if USING_R_DLIGHTFRAMECOUNT
	if (surf->dlightframe == r_framecount)
		R_AddDynamicLights ();
#else
#if !MARK_NODE_IN_SURFACE
    if (isSurfDlightVisited(index))
		R_AddDynamicLights ();
#else
 //   printf("idx: %d. Model %p\r\n", index, currententity->model);
    {
        unsigned int nodeindex = surf->surfNodeIndex;
#if USE_NODE_DLIGHTBITS
        if (nodeDlightBits[nodeindex])
	    	R_AddDynamicLights ();
#else
        if (nodeHadDlight[nodeindex / 8] & (1 << (nodeindex % 8)))
	    	R_AddDynamicLights ();
#endif
    }
#endif
#endif
#endif
// bound, invert, and shift
#if 0
	for (i=0 ; i<size ; i++)
	{
		t = (255*256 - (int)_g->blocklights[i]) >> (8 - VID_CBITS);

		if (t < (1 << 6))
			t = (1 << 6);

    _g->blocklights[i] = t >> ( 4 - r_drawsurf.surfmip);
    #if WIN32
    lightcells++;
    #endif // WIN32
	}
#else
    unsigned int shiftValue = (8 - VID_CBITS + 4 - r_drawsurf.surfmip);
    int minValue = (1 << (6 - 4 + r_drawsurf.surfmip));
    for (i = 0; i < size; i++)
    {
        t = (255 * 256 - (int) _g->blocklights[i]) >> shiftValue;

        if (t < minValue)
            t = minValue;

        _g->blocklights[i] = t; // >> ( 4 - r_drawsurf.surfmip);
    }
#endif
#if NEW_BILINEAR_INTERPOLATION
    // put in high halfword the value of the next row
#if 0

	for (int i = 0; i < size - _g->r_lightwidth; i++)
  {
	  _g->blocklights[i] |= _g->blocklights[i + _g->r_lightwidth] << 16;
  }
#else
    uint16_t *d = (uint16_t*) _g->blocklights + 1;
    int lw = _g->r_lightwidth;
    uint32_t *s = (uint32_t*) &_g->blocklights[lw];
    for (int i = 0; i < size - lw; i += 2)
    {
        *d = *s++;
        d += 2;
        *d = *s++;
        d += 2;

    }

#endif
#endif
}

/*
 ===============
 R_TextureAnimation

 Returns the proper texture for a given time and base texture
 ===============
 */
__attribute__ ((section(".drawsurf"))) texture_t* R_TextureAnimation(texture_t *base)
{
    int relative;
    int count;

    if (getEntityFrame(_g->currententity))
    {
#if TEXTURE_HAS_ANIM_POINTERS
            if (base->alternate_anims)
                base = base->alternate_anims;
        #else
        if (base->alternate_anim_ofs)
            base = Mod_GetAlternateAnimTexture(base);
#endif
    }

    if (!base->anim_total)
        return base;

    relative = (int) (_g->cl.time * 10) % base->anim_total;

    count = 0;
    while (base->anim_min > relative || base->anim_max <= relative)
    {
#if TEXTURE_HAS_ANIM_POINTERS
    		base = base->anim_next;
        #else
        base = Mod_GetNextAnimTexture(base);
#endif
        if (!base)
            Sys_Error("R_TextureAnimation: broken cycle");
        if (++count > 100)
            Sys_Error("R_TextureAnimation: infinite cycle");
    }

    return base;
}
#define USE_STRUCT_FOR_SURF_DRAW_DATA 1
#if USE_STRUCT_FOR_SURF_DRAW_DATA

surfDrawData_t sdd;
#else
int r_texture_width;
int r_texture_height;
int r_surf_soffs, r_surf_toffs;
#if FLOAT_I_TEXTURE_SIZE
float r_i_texture_width;
float r_i_texture_height;
#else
#define TFRACSHIFT 16
unsigned int r_i_texture_width;
unsigned int r_i_texture_height;
#endif
#endif
/*
 ===============
 R_DrawSurface
 ===============
 */
DRAWSURF_SEC void R_DrawSurface(void)
{
    int smax, tmax, twidth;
    int soffset, basetoffset, texwidth;
    texture_t *mt;

    mt = r_drawsurf.texture;
#if PRE_LIGHT_SURFACES
    r_source = getCurrentTextureCacheAddress();
#else
    sdd.r_source = getCurrentTextureCacheAddress();
#endif

// the fractional light values should range from 0 to (VID_GRADES - 1) << 16
// from a source range of 0 - 255

    texwidth = mt->width >> r_drawsurf.surfmip;
#if PRE_LIGHT_SURFACES
	blocksize = 16 >> r_drawsurf.surfmip;
	blockdivshift = 4 - r_drawsurf.surfmip;
	blockdivmask = (1 << blockdivshift) - 1;
#endif

    _g->r_lightwidth = (r_drawsurf.surf->extents[0] >> 4) + 1;

    // calculate the lightings. Note: moved here so that we have r_lightwidth.
    R_BuildLightMap();

#if PRE_LIGHT_SURFACES
  r_numhblocks = r_drawsurf.surfwidth >> blockdivshift;
  r_numvblocks = r_drawsurf.surfheight >> blockdivshift;

//==============================

	if (r_pixbytes == 1)
	{
		pblockdrawer = surfmiptable[r_drawsurf.surfmip];
	// TODO: only needs to be set when there is a display settings change
		horzblockstep = blocksize;
	}
	else
	{
		pblockdrawer = R_DrawSurfaceBlock16;
	// TODO: only needs to be set when there is a display settings change
		horzblockstep = blocksize << 1;
	}
#endif
    smax = mt->width >> r_drawsurf.surfmip;
    twidth = texwidth;
    tmax = mt->height >> r_drawsurf.surfmip;
#if PRE_LIGHT_SURFACES
	sourcetstep = texwidth;
	r_sourcemax = r_source + (tmax * smax);
#endif

    soffset = r_drawsurf.surf->texturemins[0];
    basetoffset = r_drawsurf.surf->texturemins[1];

// << 16 components are to guarantee positive values for %
    soffset = ((soffset >> r_drawsurf.surfmip) + (smax << 16)) % smax;

#if PRE_LIGHT_SURFACES
  r_stepback = tmax * twidth;

	unsigned char *basetptr;
	basetptr = &r_source[((((basetoffset >> r_drawsurf.surfmip) + (tmax << 16)) % tmax) * twidth)];
	unsigned char *pcolumndest;
  pcolumndest = r_drawsurf.surfdat;
	for (u=0 ; u<r_numhblocks; u++)
	{
		r_lightptr = blocklights + u;

		prowdestbase = pcolumndest;

		pbasesource = basetptr + soffset;

		(*pblockdrawer)();

		soffset = soffset + blocksize;
		if (soffset >= smax)
			soffset = 0;

		pcolumndest += horzblockstep;
	}
#else
#if !USE_STRUCT_FOR_SURF_DRAW_DATA
    r_texture_width = twidth;
    r_texture_height = tmax;
#if FLOAT_I_TEXTURE_SIZE
    r_i_texture_width = 1.0f / twidth;
    r_i_texture_height = 1.0f / r_texture_height;
#else
    r_i_texture_width =  (1 << TFRACSHIFT) / twidth;
    r_i_texture_height = (1 << TFRACSHIFT) / r_texture_height;

#endif
    r_surf_toffs = (((basetoffset >> r_drawsurf.surfmip) + (tmax << 16)) % tmax);
    r_surf_soffs = soffset;
    r_lightptr = blocklights;
#else
#if !NEW_BILINEAR_INTERPOLATION
    sdd.r_i_texture_width = (1 << TFRACSHIFT) / twidth;
    sdd.r_i_texture_height = (1 << TFRACSHIFT) / tmax;
#endif
    sdd.surfmip = r_drawsurf.surfmip;
    sdd.r_surf_soffs = soffset;
    sdd.r_surf_toffs = (((basetoffset >> r_drawsurf.surfmip) + (tmax << 16)) % tmax);
    sdd.blocklights = &_g->blocklights[0] - (_g->r_lightwidth * (sdd.r_surf_toffs >> (4 - r_drawsurf.surfmip)))
        - (sdd.r_surf_soffs >> (4 - r_drawsurf.surfmip));
    sdd.r_texture_width = twidth;
    sdd.r_texture_height = tmax;
    sdd.colormap = vid.colormap;
    int textureType = 0;
    if ((twidth - 1) & twidth)
    {
        textureType |= 1;
    }
    if ((tmax - 1) & tmax)
    {
        textureType |= 2;
    }
#if 0  // unfortunately, not good for now: rounding erros make t and s negative, which will create issues.
    if (!textureType &&  sdd.r_texture_width >= r_drawsurf.surfwidth && sdd.r_texture_height >= r_drawsurf.surfheight)
    {
        textureType = -1;   // this is the easiest case: no need for mod.
    }
#endif
    sdd.textureType = textureType;  // if 0, then go for simplified drawing, saving many cycles!
    if (!textureType)
    {
#if WIN32
      sdd.tWidthMask = sdd.r_texture_width - 1;
      sdd.tHeightMask = sdd.r_texture_height - 1;
      sdd.r_lightwidth = _g->r_lightwidth;

#else
        sdd.tWidthHeightMask = (sdd.r_texture_width - 1) | ((sdd.r_texture_height - 1) << 16);
        sdd.tWidthOr1 = (sdd.r_texture_width << 16) | 1;
        sdd.r_lightwidth = ((4 * _g->r_lightwidth) << 16) | 4;
#endif
    }
    else
    {
#if WIN3 || 1
        sdd.r_lightwidth = _g->r_lightwidth;
#else
        // unfortunately this trick won't optimize for the general case.
        sdd.r_lightwidth = ( (4 * r_lightwidth) << 16) | 4;
#endif
    }
#if OLD_MOD_SIZE
    sdd.qcs =  0xFFFFFFFF / sdd.r_texture_width + 1;
    sdd.qct =  0xFFFFFFFF / sdd.r_texture_height + 1;
#else
    // this is less precise but allows us to reduce by 2 instruction in the ASM code!
    sdd.qcs = (0xFFFFFFFF / (sdd.r_texture_width << 16) + 1);
    sdd.qct = (0xFFFFFFFF / (sdd.r_texture_height << 16) + 1);
#endif
#define PROFILE_SURFACE_SIZE 0
#if PROFILE_SURFACE_SIZE && WIN32
    int surfType = 0;
    int texType = 0;
    static int total = 0;
    static int small = 0;
    total++;
    static int ultrasmall = 0;
    if (r_drawsurf.surfwidth * r_drawsurf.surfheight <= 1024)
    {
        if (!(((twidth - 1) &twidth) || ((tmax - 1) & tmax)))
            small++;
        if (twidth < 32 || tmax < 32)
            ultrasmall++;
        printf("This was small: data: surf %d x %d tex %d x %d, mip: %d\r\n",
               r_drawsurf.surfwidth, r_drawsurf.surfheight , twidth, tmax, r_drawsurf.surfmip);
    }

    static int surfTypes[4];
    static int texTypes[4];
    if (r_drawsurf.surfwidth > twidth)
    {
        surfType |= 1;
    }
    if (r_drawsurf.surfheight > tmax)
    {
        surfType |= 2;
    }
    if ((twidth - 1) &twidth)
    {
        texType |= 1;
    }
    if ((tmax - 1) & tmax)
    {
        texType |= 2;
    }

    surfTypes[surfType]++;
    texTypes[texType]++;
    printf("Surface type is %d. So far: %d %d %d %d. Power2: %d %d %d %d, total %d, =< 1024 %d (%f %%). UltraSmall: %d\r\n",
           surfType, surfTypes[0], surfTypes[1], surfTypes[2], surfTypes[3],
           texTypes[0], texTypes[1], texTypes[2], texTypes[3], total, small, (float) 100*small/total, ultrasmall);
#endif
#endif

#endif
}

//=============================================================================

#if	!id386

/*
 ================


 ================
 */
#if PRE_LIGHT_SURFACES
void R_DrawSurfaceBlock8_mip0 (void)
{
	int				v, i, b, lightstep, lighttemp, light;
	unsigned char	pix, *psource, *prowdest;

	psource = pbasesource;
	prowdest = prowdestbase;

	for (v=0 ; v<r_numvblocks ; v++)
	{
	// FIXME: make these locals?
	// FIXME: use delta rather than both right and left, like ASM?
		lightleft = r_lightptr[0];
		lightright = r_lightptr[1];
		r_lightptr += r_lightwidth;
		lightleftstep = (r_lightptr[0] - lightleft) >> 4;
		lightrightstep = (r_lightptr[1] - lightright) >> 4;

		for (i=0 ; i<16 ; i++)
		{
			lighttemp = lightleft - lightright;
			lightstep = lighttemp >> 4;

			light = lightright;

			for (b=15; b>=0; b--)
			{
				pix = psource[b];
				prowdest[b] = ((unsigned char *)vid.colormap)
						[(light & 0xFF00) + pix];
				light += lightstep;
			}

			psource += sourcetstep;
			lightright += lightrightstep;
			lightleft += lightleftstep;
			prowdest += surfrowbytes;
		}

		if (psource >= r_sourcemax)
			psource -= r_stepback;
	}
}


/*
================
R_DrawSurfaceBlock8_mip1
================
*/
void R_DrawSurfaceBlock8_mip1 (void)
{
	int				v, i, b, lightstep, lighttemp, light;
	unsigned char	pix, *psource, *prowdest;

	psource = pbasesource;
	prowdest = prowdestbase;

	for (v=0 ; v<r_numvblocks ; v++)
	{
	// FIXME: make these locals?
	// FIXME: use delta rather than both right and left, like ASM?
		lightleft = r_lightptr[0];
		lightright = r_lightptr[1];
		r_lightptr += r_lightwidth;
		lightleftstep = (r_lightptr[0] - lightleft) >> 3;
		lightrightstep = (r_lightptr[1] - lightright) >> 3;

		for (i=0 ; i<8 ; i++)
		{
			lighttemp = lightleft - lightright;
			lightstep = lighttemp >> 3;

			light = lightright;

			for (b=7; b>=0; b--)
			{
				pix = psource[b];
				prowdest[b] = ((unsigned char *)vid.colormap)
						[(light & 0xFF00) + pix];
				light += lightstep;
			}

			psource += sourcetstep;
			lightright += lightrightstep;
			lightleft += lightleftstep;
			prowdest += surfrowbytes;
		}

		if (psource >= r_sourcemax)
			psource -= r_stepback;
	}
}


/*
================
R_DrawSurfaceBlock8_mip2
================
*/
void R_DrawSurfaceBlock8_mip2 (void)
{
	int				v, i, b, lightstep, lighttemp, light;
	unsigned char	pix, *psource, *prowdest;

	psource = pbasesource;
	prowdest = prowdestbase;

	for (v=0 ; v<r_numvblocks ; v++)
	{
	// FIXME: make these locals?
	// FIXME: use delta rather than both right and left, like ASM?
		lightleft = r_lightptr[0];
		lightright = r_lightptr[1];
		r_lightptr += r_lightwidth;
		lightleftstep = (r_lightptr[0] - lightleft) >> 2;
		lightrightstep = (r_lightptr[1] - lightright) >> 2;

		for (i=0 ; i<4 ; i++)
		{
			lighttemp = lightleft - lightright;
			lightstep = lighttemp >> 2;

			light = lightright;

			for (b=3; b>=0; b--)
			{
				pix = psource[b];
				prowdest[b] = ((unsigned char *)vid.colormap)
						[(light & 0xFF00) + pix];
				light += lightstep;
			}

			psource += sourcetstep;
			lightright += lightrightstep;
			lightleft += lightleftstep;
			prowdest += surfrowbytes;
		}

		if (psource >= r_sourcemax)
			psource -= r_stepback;
	}
}


/*
================
R_DrawSurfaceBlock8_mip3
================
*/
void R_DrawSurfaceBlock8_mip3 (void)
{
	int				v, i, b, lightstep, lighttemp, light;
	unsigned char	pix, *psource, *prowdest;

	psource = pbasesource;
	prowdest = prowdestbase;

	for (v=0 ; v<r_numvblocks ; v++)
	{
	// FIXME: make these locals?
	// FIXME: use delta rather than both right and left, like ASM?
		lightleft = r_lightptr[0];
		lightright = r_lightptr[1];
		r_lightptr += r_lightwidth;
		lightleftstep = (r_lightptr[0] - lightleft) >> 1;
		lightrightstep = (r_lightptr[1] - lightright) >> 1;

		for (i=0 ; i<2 ; i++)
		{
			lighttemp = lightleft - lightright;
			lightstep = lighttemp >> 1;

			light = lightright;

			for (b=1; b>=0; b--)
			{
				pix = psource[b];
				prowdest[b] = ((unsigned char *)vid.colormap)
						[(light & 0xFF00) + pix];
				light += lightstep;
			}

			psource += sourcetstep;
			lightright += lightrightstep;
			lightleft += lightleftstep;
			prowdest += surfrowbytes;
		}

		if (psource >= r_sourcemax)
			psource -= r_stepback;
	}
}


/*
================
R_DrawSurfaceBlock16

FIXME: make this work
================
*/
void R_DrawSurfaceBlock16 (void)
{
	int				k;
	unsigned char	*psource;
	int				lighttemp, lightstep, light;
	unsigned short	*prowdest;

	prowdest = (unsigned short *)prowdestbase;

	for (k=0 ; k<blocksize ; k++)
	{
		unsigned short	*pdest;
		unsigned char	pix;
		int				b;

		psource = pbasesource;
		lighttemp = lightright - lightleft;
		lightstep = lighttemp >> blockdivshift;

		light = lightleft;
		pdest = prowdest;

		for (b=0; b<blocksize; b++)
		{
			pix = *psource;
			*pdest = vid.colormap16[(light & 0xFF00) + pix];
			psource += sourcesstep;
			pdest++;
			light += lightstep;
		}

		pbasesource += sourcetstep;
		lightright += lightrightstep;
		lightleft += lightleftstep;
		prowdest = (unsigned short *)((long)prowdest + surfrowbytes);
	}

	prowdestbase = prowdest;
}
#endif
#endif

//============================================================================
#if DO_WE_REALLY_NEED_THIS

/*
================
R_GenTurbTile
================
*/
void R_GenTurbTile (pixel_t *pbasetex, void *pdest)
{
	int		*turb;
	int		i, j, s, t;
	byte	*pd;

	turb = sintable + ((int)(cl.time*SPEED)&(CYCLE-1));
	pd = (byte *)pdest;

	for (i=0 ; i<TILE_SIZE ; i++)
	{
		for (j=0 ; j<TILE_SIZE ; j++)
		{
			s = (((j << 16) + turb[i & (CYCLE-1)]) >> 16) & 63;
			t = (((i << 16) + turb[j & (CYCLE-1)]) >> 16) & 63;
			*pd++ = *(pbasetex + (t<<6) + s);
		}
	}
}


/*
================
R_GenTurbTile16
================
*/
void R_GenTurbTile16 (pixel_t *pbasetex, void *pdest)
{
	int				*turb;
	int				i, j, s, t;
	unsigned short	*pd;

	turb = sintable + ((int)(cl.time*SPEED)&(CYCLE-1));
	pd = (unsigned short *)pdest;

	for (i=0 ; i<TILE_SIZE ; i++)
	{
		for (j=0 ; j<TILE_SIZE ; j++)
		{
			s = (((j << 16) + turb[i & (CYCLE-1)]) >> 16) & 63;
			t = (((i << 16) + turb[j & (CYCLE-1)]) >> 16) & 63;
			*pd++ = d_8to16table[*(pbasetex + (t<<6) + s)];
		}
	}
}


/*
================
R_GenTile
================
*/
void R_GenTile (msurface_t *psurf, void *pdest)
{
	if (psurf->flags & SURF_DRAWTURB)
	{

#if 1
#if MSURFACE_HAS_TEXINFO_POINTER
			R_GenTurbTile ((pixel_t *) ((byte *)psurf->texinfo->texture + psurf->texinfo->texture->offsets[0]), pdest);
#else
        mtexinfo_t *ti = getMsurfaceTexinfo(psurf);
			R_GenTurbTile ((pixel_t *) ((byte *)ti->texture + ti->texture->offsets[0]), pdest);

#endif
#else   // no crappy 16 bit!
R_GenTurbTile16 ((pixel_t *)
				((byte *)psurf->texinfo->texture + psurf->texinfo->texture->offsets[0]), pdest);
#endif
	}
	else if (psurf->flags & SURF_DRAWSKY)
	{
		if (r_pixbytes == 1)
		{
			R_GenSkyTile (pdest);
		}
		else
		{
			R_GenSkyTile16 (pdest);
		}
	}
	else
	{
		Sys_Error ("Unknown tile type");
	}
}
#endif
