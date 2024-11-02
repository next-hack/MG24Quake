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
// r_light.c

#include "quakedef.h"
#include "r_local.h"
#if USING_R_DLIGHTFRAMECOUNT
int	r_dlightframecount;
#endif
#if MARK_NODE_IN_SURFACE
#if USE_NODE_DLIGHTBITS
#if MAX_DLIGHTS <= 8
uint8_t *nodeDlightBits = NULL;
#elif MAX_DLIGHTS <= 16
uint16_t *nodeDlightBits = NULL;
#else
uint32_t *nodeDlightBits = NULL;
#endif
#else
uint8_t * nodeHadDlight = NULL;
#endif
#endif // MARK_NODE_IN_SURFACE

/*
==================
R_AnimateLight
==================
*/
void R_AnimateLight (void)
{
	int			i,j,k;

//
// light animations
// 'm' is normal light, 'a' is no light, 'z' is double bright
	i = (int)(_g->cl.time*10);
    if (sv.active && DIRECT_SINGLE_PLAYER)
    {
        for (j=0 ; j<MAX_LIGHTSTYLES ; j++)
        {
            if (!sv.lightstyles_len[j])
            {
                d_lightstylevalue[j] = 256;
                continue;
            }
            k = i % sv.lightstyles_len[j];
            k = getStringFromIndex(sv.lightstyles_idx[j])[k] - 'a';
            k = k*22;
            d_lightstylevalue[j] = k;
        }

    }
    else if (_g->cls.demoplayback)
    {
        for (j=0 ; j<MAX_LIGHTSTYLES ; j++)
        {
            if (!_g->cl_lightstyle[j].length)
            {
                d_lightstylevalue[j] = 256;
                continue;
            }
            k = i % _g->cl_lightstyle[j].length;
    #if OLD_LIGHTSTYLE
            k = cl_lightstyle[j].map[k] - 'a';
    #else
            uint8_t nibble = _g->cl_lightstyle[j].map_nibbles[k / 2];
            if (k & 1)
               nibble = nibble >> 4;
            nibble &= 0xF;
            if (_g->cl_lightstyle[j].map_topBits[k / 8] & (1 << (k % 8)))
            {
                nibble |= 0x10;
            }
            k = nibble;
    #endif
            k = k*22;
            d_lightstylevalue[j] = k;
        }

    }
}


/*
=============================================================================

DYNAMIC LIGHTS

=============================================================================
*/
#if !MARK_NODE_IN_SURFACE
byte surfdlightVisited[MAX_SURFACES/8];

int isSurfDlightVisited(unsigned int index)
{
    if (index >= MAX_SURFACES)
    {
        while(1)
        {
            printf("index %d is > MAX_SURFACES\r\n", index);
            FIXME("ERROR");
        }
    }
    return 0 != (surfdlightVisited[index >> 3] & (1 << (index & 7)));
}
#endif
/*
=============
R_MarkLights
=============
*/
void R_MarkLights (dlight_t *light, int bit, mnode_t *node)
{
	mplane_t	*splitplane;
	float		dist;
	msurface_t	*surf;
	if (node->contents < 0)
		return;

#if NODE_HAS_PLANE_POINTER
	    splitplane = node->plane;
#else
        splitplane =  Mod_GetNodePlane(node , cl.worldmodel);//currententity->model); // is it right ?
#endif
#if DLIGHT_HAS_FLOAT_ORIGIN
	dist = DotProduct (light->origin, splitplane->normal) - splitplane->dist;
#else
	dist = DotProduct (light->iorigin_s, splitplane->normal) - getPlaneDist(splitplane);
#endif
	if (dist > light->radius)
	{
#if NODE_HAS_CHILDREN_POINTERS
		R_MarkLights (light, bit, node->children[0]);
#else
		R_MarkLights (light, bit, Mod_GetChildNode(node, 0, getEntityModel(_g->currententity)));
#endif
		return;
	}
	if (dist < -light->radius)
	{
#if NODE_HAS_CHILDREN_POINTERS
		R_MarkLights (light, bit, node->children[1]);
#else
		R_MarkLights (light, bit, Mod_GetChildNode(node, 1, getEntityModel(_g->currententity)));
#endif
		return;
	}

// mark the polygons
#if !SEPARATE_BRUSH_MODEL_DATA
	surf = cl.worldmodel->surfaces + node->firstsurface;
#else
	surf = _g->cl.worldmodel->brushModelData->surfaces + node->firstsurface;
#endif
#if !MARK_NODE_IN_SURFACE
	int i;
	for (i=0 ; i<node->numsurfaces ; i++, surf++)
	{
#if USING_R_DLIGHTFRAMECOUNT
		if (surf->dlightframe != r_dlightframecount)
		{
			surf->dlightbits = 0;
			surf->dlightframe = r_dlightframecount;
		}
#else
        unsigned int index = surf - cl.worldmodel->surfaces;
		if (!(isSurfDlightVisited(index)))
		{
			surf->dlightbits = 0;
			surfdlightVisited[index >> 3] |= (1 << (index & 7));
		}

#endif
		surf->dlightbits |= bit;
	}
#else
    unsigned int nodeindex = surf->surfNodeIndex;
 //printf("ni %d\r\n", nodeindex);
#if USE_NODE_DLIGHTBITS
    nodeDlightBits[nodeindex] |= bit;
#else
    nodeHadDlight[nodeindex / 8] |= 1 << (nodeindex % 8);
#endif
#endif
#if NODE_HAS_CHILDREN_POINTERS
	R_MarkLights (light, bit, node->children[0]);
	R_MarkLights (light, bit, node->children[1]);
#else
    R_MarkLights (light, bit, Mod_GetChildNode(node, 0, getEntityModel(_g->currententity)));
    R_MarkLights (light, bit, Mod_GetChildNode(node, 1, getEntityModel(_g->currententity)));
#endif
}


/*
=============
R_PushDlights
=============
*/

void R_PushDlights (void)
{
	int		i;
	dlight_t	*l;
#if USING_R_DLIGHTFRAMECOUNT
	r_dlightframecount = r_framecount + 1;	// because the count hasn't advanced yet for this frame
#else
#if MARK_NODE_IN_SURFACE
#if USE_NODE_DLIGHTBITS
    memset(nodeDlightBits, 0, sizeof(*nodeDlightBits) * cl.worldmodel->numnodes);
#else
#if !SEPARATE_BRUSH_MODEL_DATA
    memset(nodeHadDlight, 0, 4 * (cl.worldmodel->numnodes + 31) / 32);
#else
    fastMemclear32(nodeHadDlight, (_g->cl.worldmodel->brushModelData->numnodes + 31) / 32);
#endif
#endif
#else
    memset(surfdlightVisited, 0, sizeof (surfdlightVisited));
#endif
#endif
	l = _g->cl_dlights;

	for (i=0 ; i<MAX_DLIGHTS ; i++, l++)
	{
		if (l->die < _g->cl.time || !l->radius)
			continue;
#if !SEPARATE_BRUSH_MODEL_DATA
		R_MarkLights ( l, 1<<i, cl.worldmodel->nodes );
#else
		R_MarkLights ( l, 1<<i, _g->cl.worldmodel->brushModelData->nodes );
#endif
	}
}


/*
=============================================================================

LIGHT SAMPLING

=============================================================================
*/

int RecursiveLightPoint (mnode_t *node, vec3_t start, vec3_t end)
{
	int			r;
	float		front, back, frac;
	int			side;
	mplane_t	*plane;
	vec3_t		mid;
	msurface_t	*surf;
	int			s, t, ds, dt;
	int			i;
	mtexinfo_t	*tex;
	byte		*lightmap;
	unsigned	scale;
	int			maps;

	if (node->contents < 0)
		return -1;		// didn't hit anything

// calculate mid point

// FIXME: optimize for axial

#if NODE_HAS_PLANE_POINTER
		plane = node->plane;
#else
        plane = Mod_GetNodePlane(node, cl.worldmodel);
#endif
    float planedist = getPlaneDist(plane);
	front = DotProduct (start, plane->normal) - planedist;
	back = DotProduct (end, plane->normal) - planedist;
	side = front < 0;
#if NODE_HAS_CHILDREN_POINTERS
	if ( (back < 0) == side)
		return RecursiveLightPoint (node->children[side], start, end);
#else
	if ( (back < 0) == side)
		return RecursiveLightPoint (Mod_GetChildNode(node, side, _g->cl.worldmodel), start, end);
#endif
	frac = front / (front-back);
	mid[0] = start[0] + (end[0] - start[0])*frac;
	mid[1] = start[1] + (end[1] - start[1])*frac;
	mid[2] = start[2] + (end[2] - start[2])*frac;

// go down front side
#if NODE_HAS_CHILDREN_POINTERS
	r = RecursiveLightPoint (node->children[side], start, mid);
#else
	r = RecursiveLightPoint (Mod_GetChildNode(node, side, _g->cl.worldmodel), start, mid);
#endif

	if (r >= 0)
		return r;		// hit something

	if ( (back < 0) == side )
		return -1;		// didn't hit anuthing

// check for impact on this node

#if !SEPARATE_BRUSH_MODEL_DATA
	surf = cl.worldmodel->surfaces + node->firstsurface;
#else
	surf = _g->cl.worldmodel->brushModelData->surfaces + node->firstsurface;
#endif
	for (i=0 ; i<node->numsurfaces ; i++, surf++)
	{
		if (surf->flags & SURF_DRAWTILED)
			continue;	// no lightmaps
#if MSURFACE_HAS_TEXINFO_POINTER
		tex = surf->texinfo;
#else
        tex = getMsurfaceTexinfo(surf);
#endif
		s = DotProduct (mid, tex->vecs[0]) + tex->vecs[0][3];
		t = DotProduct (mid, tex->vecs[1]) + tex->vecs[1][3];;

		if (s < surf->texturemins[0] ||
		t < surf->texturemins[1])
			continue;

		ds = s - surf->texturemins[0];
		dt = t - surf->texturemins[1];

		if ( ds > surf->extents[0] || dt > surf->extents[1] )
			continue;
#if MSURFACE_HAS_SAMPLE_POINTER
		if (!surf->samples)
			return 0;
#else
        if (!getMsurfaceSamples(surf))
            return 0;
#endif

		ds >>= 4;
		dt >>= 4;
#if MSURFACE_HAS_SAMPLE_POINTER
		lightmap = surf->samples;
#else
        lightmap = getMsurfaceSamples(surf);
#endif
		r = 0;
		if (lightmap)
		{

			lightmap += dt * ((surf->extents[0]>>4)+1) + ds;
			int lmsize = ((surf->extents[0]>>4)+1) * ((surf->extents[1]>>4)+1);
			for (maps = 0 ; maps < MAXLIGHTMAPS && surf->styles[maps] != 255 ;maps++)
			{
#if 1
				scale = d_lightstylevalue[surf->styles[maps]];
#if LIGHTMAP_ON_INTERNAL_FLASH
				r += *lightmap * scale;
#else
                r += scale * extMemGetByteFromAddress(lightmap);
#endif
				lightmap += lmsize;
#else
				interleavedSpiFlashAsynchReadByteDMA(lightmap);
        scale = d_lightstylevalue[surf->styles[maps]];
        lightmap += ((surf->extents[0]>>4)+1) * ((surf->extents[1]>>4)+1);
        r += scale * interleavedSpiFlashGetAsynchReadByteDMA();
#endif
			}

			r >>= 8;
		}

		return r;
	}

// go down back side
#if NODE_HAS_CHILDREN_POINTERS
	return RecursiveLightPoint (node->children[!side], mid, end);
#else
	return RecursiveLightPoint (Mod_GetChildNode(node, !side, _g->cl.worldmodel), mid, end);
#endif

}

int R_LightPoint (vec3_t p)
{
	vec3_t		end;
	int			r;

#if !SEPARATE_BRUSH_MODEL_DATA
	if (!cl.worldmodel->lightdata)
		return 255;
#else
	if (!_g->cl.worldmodel->brushModelData->lightdata)
		return 255;
#endif

	end[0] = p[0];
	end[1] = p[1];
	end[2] = p[2] - 2048;
#if !SEPARATE_BRUSH_MODEL_DATA
	r = RecursiveLightPoint (cl.worldmodel->nodes, p, end);
#else
	r = RecursiveLightPoint (_g->cl.worldmodel->brushModelData->nodes, p, end);
#endif
	if (r == -1)
		r = 0;

	if (r < _g->r_refdef.ambientlight)
		r = _g->r_refdef.ambientlight;

	return r;
}

