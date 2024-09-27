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
// r_alias.c: routines for setting up to draw alias models
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"	// FIXME: shouldn't be needed (is needed for patch
                        // right now, but that should move)

#define LIGHT_MIN	5		// lowest light value we'll allow, to avoid the
                            //  need for inner-loop light clamping

typedef struct
{
    int index0;
    int index1;
} aedge_t;

static const aedge_t	aedges[12] =
{
    {0, 1}, {1, 2}, {2, 3}, {3, 0},
    {4, 5}, {5, 6}, {6, 7}, {7, 4},
    {0, 5}, {1, 4}, {2, 7}, {3, 6}
};

#define NUMVERTEXNORMALS	162

const float r_avertexnormals[NUMVERTEXNORMALS][3] = {
#include "anorms.h"
    };

void R_AliasTransformAndProjectFinalVerts(finalvert_t *fv, stvert_t *pstverts);
void R_AliasSetUpTransform(int trivial_accept);
void R_AliasTransformVector(vec3_t in, vec3_t out);
void R_AliasTransformFinalVert(finalvert_t *fv, auxvert_t *av, trivertx_t *pverts, stvert_t *pstverts);
void R_AliasProjectFinalVert(finalvert_t *fv, auxvert_t *av);

/*
 ================
 R_AliasCheckBBox
 ================
 */
qboolean R_AliasCheckBBox(void)
{
    int i, flags, frame, numv;
    aliashdr_t *pahdr;
    float zi, basepts[8][3], v0, v1, frac;
    finalvert_t *pv0, *pv1, viewpts[16];
    auxvert_t *pa0, *pa1, viewaux[16];
    maliasframedesc_t *pframedesc;
    qboolean zclipped, zfullyclipped;
    unsigned anyclip, allclip;
    int minz;

// expand, rotate, and translate points into worldspace

    _g->currententity->trivial_accept = 0;
    _g->pmodel = getEntityModel(_g->currententity);
    pahdr = Mod_Extradata(_g->pmodel);
    _g->pmdl = (mdl_t*) ((byte*) pahdr + pahdr->model);

    R_AliasSetUpTransform(0);

// construct the base bounding box for this frame
    frame = getEntityFrame(_g->currententity);
// TODO: don't repeat this check when drawing?
    if ((frame >= _g->pmdl->numframes) || (frame < 0))
    {
        Con_DPrintf("No such frame %d %s\n", frame, _g->pmodel->name);
        frame = 0;
    }

    pframedesc = &pahdr->frames[frame];

// x worldspace coordinates
    basepts[0][0] = basepts[1][0] = basepts[2][0] = basepts[3][0] = (float) pframedesc->bboxmin.v[0];
    basepts[4][0] = basepts[5][0] = basepts[6][0] = basepts[7][0] = (float) pframedesc->bboxmax.v[0];

// y worldspace coordinates
    basepts[0][1] = basepts[3][1] = basepts[5][1] = basepts[6][1] = (float) pframedesc->bboxmin.v[1];
    basepts[1][1] = basepts[2][1] = basepts[4][1] = basepts[7][1] = (float) pframedesc->bboxmax.v[1];

// z worldspace coordinates
    basepts[0][2] = basepts[1][2] = basepts[4][2] = basepts[5][2] = (float) pframedesc->bboxmin.v[2];
    basepts[2][2] = basepts[3][2] = basepts[6][2] = basepts[7][2] = (float) pframedesc->bboxmax.v[2];

    zclipped = false;
    zfullyclipped = true;

    minz = 9999;
    for (i = 0; i < 8; i++)
    {
        R_AliasTransformVector(&basepts[i][0], &viewaux[i].fv[0]);

        if (viewaux[i].fv[2] < ALIAS_Z_CLIP_PLANE)
        {
            // we must clip points that are closer than the near clip plane
            viewpts[i].flags = ALIAS_Z_CLIP;
            zclipped = true;
        }
        else
        {
            if (viewaux[i].fv[2] < minz)
                minz = viewaux[i].fv[2];
            viewpts[i].flags = 0;
            zfullyclipped = false;
        }
    }

    if (zfullyclipped)
    {
        return false;	// everything was near-z-clipped
    }

    numv = 8;

    if (zclipped)
    {
        // organize points by edges, use edges to get new points (possible trivial
        // reject)
        for (i = 0; i < 12; i++)
        {
            // edge endpoints
            pv0 = &viewpts[aedges[i].index0];
            pv1 = &viewpts[aedges[i].index1];
            pa0 = &viewaux[aedges[i].index0];
            pa1 = &viewaux[aedges[i].index1];

            // if one end is clipped and the other isn't, make a new point
            if (pv0->flags ^ pv1->flags)
            {
                frac = (ALIAS_Z_CLIP_PLANE - pa0->fv[2]) / (pa1->fv[2] - pa0->fv[2]);
                viewaux[numv].fv[0] = pa0->fv[0] + (pa1->fv[0] - pa0->fv[0]) * frac;
                viewaux[numv].fv[1] = pa0->fv[1] + (pa1->fv[1] - pa0->fv[1]) * frac;
                viewaux[numv].fv[2] = ALIAS_Z_CLIP_PLANE;
                viewpts[numv].flags = 0;
                numv++;
            }
        }
    }

// project the vertices that remain after clipping
    anyclip = 0;
    allclip = ALIAS_XY_CLIP_MASK;

// TODO: probably should do this loop in ASM, especially if we use floats
    for (i = 0; i < numv; i++)
    {
        // we don't need to bother with vertices that were z-clipped
        if (viewpts[i].flags & ALIAS_Z_CLIP)
            continue;

        zi = 1.0 / viewaux[i].fv[2];

        // FIXME: do with chop mode in ASM, or convert to float
        v0 = (viewaux[i].fv[0] * xscale * zi) + xcenter;
        v1 = (viewaux[i].fv[1] * yscale * zi) + ycenter;

        flags = 0;
//		int izi = (int)zi >> 16;

        if (v0 < _g->r_refdef.fvrectx)
            flags |= ALIAS_LEFT_CLIP;
        if (v1 < _g->r_refdef.fvrecty)
            flags |= ALIAS_TOP_CLIP;
        if (v0 > _g->r_refdef.fvrectright)
            flags |= ALIAS_RIGHT_CLIP;
        if (v1 > _g->r_refdef.fvrectbottom)
            flags |= ALIAS_BOTTOM_CLIP;
        anyclip |= flags;
        allclip &= flags;
    }

    if (allclip)
        return false;	// trivial reject off one side

    _g->currententity->trivial_accept = !anyclip & !zclipped;

    if (_g->currententity->trivial_accept)
    {
        if (minz > (r_aliastransition + (_g->pmdl->size * r_resfudge)))
        {
            _g->currententity->trivial_accept |= 2;
        }
    }

    return true;
}

/*
 ================
 R_AliasTransformVector
 ================
 */
void R_AliasTransformVector(vec3_t in, vec3_t out)
{
    out[0] = DotProduct(in, _g->aliastransform[0]) + _g->aliastransform[0][3];
    out[1] = DotProduct(in, _g->aliastransform[1]) + _g->aliastransform[1][3];
    out[2] = DotProduct(in, _g->aliastransform[2]) + _g->aliastransform[2][3];
}

/*
 ================
 R_AliasPreparePoints

 General clipped case
 ================
 */
void R_AliasPreparePoints(void)
{
    int i;
    stvert_t *pstverts;
    finalvert_t *fv;
    auxvert_t *av;
    mtriangle_t *ptri;
    finalvert_t *pfv[3];

    pstverts = (stvert_t*) ((byte*) _g->paliashdr + _g->paliashdr->stverts);
    _g->r_anumverts = _g->pmdl->numverts;

    // copy verts in ram to get better speed later
    byte *buffer = (byte*) getTextureCacheBuffer() + MAX_TEXTURE_SIZE;
    int size = _g->r_anumverts * sizeof(*pstverts);
    buffer = buffer - size;
    Q_memcpy(buffer, pstverts, size);
    pstverts = (stvert_t*) buffer;

    fv = _g->pfinalverts;
    av = _g->pauxverts;

    for (i = 0; i < _g->r_anumverts; i++, fv++, av++, _g->r_apverts++, pstverts++)
    {
        R_AliasTransformFinalVert(fv, av, _g->r_apverts, pstverts);
        if (av->fv[2] < ALIAS_Z_CLIP_PLANE)
            fv->flags |= ALIAS_Z_CLIP;
        else
        {
            R_AliasProjectFinalVert(fv, av);
            int flags = 0;
            if (fv->v[0] < _g->r_refdef.aliasvrect.x)
                flags = ALIAS_LEFT_CLIP;
            if (fv->v[1] < _g->r_refdef.aliasvrect.y)
                flags |= ALIAS_TOP_CLIP;
            if (fv->v[0] > _g->r_refdef.aliasvrectright)
                flags |= ALIAS_RIGHT_CLIP;
            if (fv->v[1] > _g->r_refdef.aliasvrectbottom)
                flags |= ALIAS_BOTTOM_CLIP;
            fv->flags |= flags;
        }
    }
//
// clip and draw all triangles
//
    _g->r_affinetridesc.numtriangles = 1;
    ptri = _g->r_affinetridesc.tempTriangleBuffer; // triangles are loaded in tempTriangleBuffer from extmem
//	ptri = (mtriangle_t *)((byte *)paliashdr + paliashdr->triangles);
    for (i = 0; i < _g->pmdl->numtris; i++, ptri++)
    {
        pfv[0] = &_g->pfinalverts[ptri->vertindex0];
        pfv[1] = &_g->pfinalverts[ptri->vertindex1];
        pfv[2] = &_g->pfinalverts[ptri->vertindex2];

        if (pfv[0]->flags & pfv[1]->flags & pfv[2]->flags & (ALIAS_XY_CLIP_MASK | ALIAS_Z_CLIP))
            continue;		// completely clipped

        if (!((pfv[0]->flags | pfv[1]->flags | pfv[2]->flags) & (ALIAS_XY_CLIP_MASK | ALIAS_Z_CLIP)))
        {	// totally unclipped
            _g->r_affinetridesc.pfinalverts = _g->pfinalverts;
            _g->r_affinetridesc.ptriangles = ptri;
            D_PolysetDraw();
        }
        else
        {	// partially clipped
            R_AliasClipTriangle(ptri);
        }
    }
}

/*
 ================
 R_AliasSetUpTransform
 ================
 */
void R_AliasSetUpTransform(int trivial_accept)
{
    int i;
    float rotationmatrix[3][4], t2matrix[3][4];
    // must be static.
    static float tmatrix[3][4];
    static float viewmatrix[3][4];
    vec3_t angles;

// TODO: should really be stored with the entity instead of being reconstructed
// TODO: should use a look-up table
// TODO: could cache lazily, stored in the entity
#if !ENTITY_HAS_SHORT_COORDS
	angles[ROLL] = currententity->angles[ROLL];
	angles[PITCH] = -currententity->angles[PITCH];
	angles[YAW] = currententity->angles[YAW];
#else
    angles[ROLL] = getEntityAngle(_g->currententity, ROLL);
    angles[PITCH] = -getEntityAngle(_g->currententity, PITCH);
    angles[YAW] = getEntityAngle(_g->currententity, YAW);

#endif
    AngleVectors(angles, _g->alias_forward, _g->alias_right, _g->alias_up);

    tmatrix[0][0] = _g->pmdl->scale[0];
    tmatrix[1][1] = _g->pmdl->scale[1];
    tmatrix[2][2] = _g->pmdl->scale[2];

    tmatrix[0][3] = _g->pmdl->scale_origin[0];
    tmatrix[1][3] = _g->pmdl->scale_origin[1];
    tmatrix[2][3] = _g->pmdl->scale_origin[2];

// TODO: can do this with simple matrix rearrangement

    for (i = 0; i < 3; i++)
    {
        t2matrix[i][0] = _g->alias_forward[i];
        t2matrix[i][1] = -_g->alias_right[i];
        t2matrix[i][2] = _g->alias_up[i];
    }

    t2matrix[0][3] = -_g->modelorg[0];
    t2matrix[1][3] = -_g->modelorg[1];
    t2matrix[2][3] = -_g->modelorg[2];

// FIXME: can do more efficiently than full concatenation
    R_ConcatTransforms(t2matrix, tmatrix, rotationmatrix);

// TODO: should be global, set when vright, etc., set
    VectorCopy(_g->vright, viewmatrix[0]);
    VectorCopy(_g->vup, viewmatrix[1]);
    VectorInverse(viewmatrix[1]);
    VectorCopy(_g->vpn, viewmatrix[2]);

//	viewmatrix[0][3] = 0;
//	viewmatrix[1][3] = 0;
//	viewmatrix[2][3] = 0;

    R_ConcatTransforms(viewmatrix, rotationmatrix, _g->aliastransform);

// do the scaling up of x and y to screen coordinates as part of the transform
// for the unclipped case (it would mess up clipping in the clipped case).
// Also scale down z, so 1/z is scaled 31 bits for free, and scale down x and y
// correspondingly so the projected x and y come out right
// FIXME: make this work for clipped case too?
    if (trivial_accept)
    {
        for (i = 0; i < 4; i++)
        {
            _g->aliastransform[0][i] *= aliasxscale * (1.0f / ((float) 0x8000 * 0x10000));
            _g->aliastransform[1][i] *= aliasyscale * (1.0f / ((float) 0x8000 * 0x10000));
            _g->aliastransform[2][i] *= 1.0f / ((float) 0x8000 * 0x10000);

        }
    }
}

/*
 ================
 R_AliasTransformFinalVert
 ================
 */
void R_AliasTransformFinalVert(finalvert_t *fv, auxvert_t *av, trivertx_t *pverts, stvert_t *pstverts)
{
    int temp;
    float lightcos, *plightnormal;

    av->fv[0] = DotProduct(pverts->v, _g->aliastransform[0]) + _g->aliastransform[0][3];
    av->fv[1] = DotProduct(pverts->v, _g->aliastransform[1]) + _g->aliastransform[1][3];
    av->fv[2] = DotProduct(pverts->v, _g->aliastransform[2]) + _g->aliastransform[2][3];
#if NO_MINIMIZE
	fv->v[2] = pstverts->s;
	fv->v[3] = pstverts->t;
#else
    fv->v[2] = pstverts->s16 << 16;
    fv->v[3] = pstverts->t16 << 16;

#endif
    fv->flags = pstverts->onseam ? ALIAS_ONSEAM : 0;

// lighting
    plightnormal = (float*) r_avertexnormals[pverts->lightnormalindex];
    lightcos = DotProduct(plightnormal, _g->r_plightvec);
    temp = _g->r_ambientlight;

    if (lightcos < 0)
    {
        temp += (int) (_g->r_shadelight * lightcos);

        // clamp; because we limited the minimum ambient and shading light, we
        // don't have to clamp low light, just bright
        if (temp < 0)
            temp = 0;
    }

    fv->v[4] = temp;
}

#if	!id386

/*
 ================
 R_AliasTransformAndProjectFinalVerts
 ================
 */
void R_AliasTransformAndProjectFinalVerts(finalvert_t *fv, stvert_t *pstverts)
{
    int i, temp;
    float lightcos, *plightnormal, zi;
    trivertx_t *pverts;

    pverts = _g->r_apverts;

    for (i = 0; i < _g->r_anumverts; i++, fv++, pverts++, pstverts++)
    {
        // transform and project
        zi = 1.0f / (DotProduct(pverts->v, _g->aliastransform[2]) + _g->aliastransform[2][3]);

        // x, y, and z are scaled down by 1/2**31 in the transform, so 1/z is
        // scaled up by 1/2**31, and the scaling cancels out for x and y in the
        // projection
        fv->v[5] = zi;
        fv->v[0] = ((DotProduct(pverts->v, _g->aliastransform[0]) + _g->aliastransform[0][3]) * zi) + aliasxcenter;
        fv->v[1] = ((DotProduct(pverts->v, _g->aliastransform[1]) + _g->aliastransform[1][3]) * zi) + aliasycenter;
#if NO_MINIMIZE

		fv->v[2] = pstverts->s;
		fv->v[3] = pstverts->t;
#else
        fv->v[2] = pstverts->s16 << 16;
        fv->v[3] = pstverts->t16 << 16;

#endif
        fv->flags = pstverts->onseam ? ALIAS_ONSEAM : 0;

        // lighting
        plightnormal = (float*) r_avertexnormals[pverts->lightnormalindex];
        lightcos = DotProduct(plightnormal, _g->r_plightvec);
        temp = _g->r_ambientlight;

        if (lightcos < 0)
        {
            temp += (int) (_g->r_shadelight * lightcos);

            // clamp; because we limited the minimum ambient and shading light, we
            // don't have to clamp low light, just bright
            if (temp < 0)
                temp = 0;
        }

        fv->v[4] = temp;
    }
}

#endif

/*
 ================
 R_AliasProjectFinalVert
 ================
 */
void R_AliasProjectFinalVert(finalvert_t *fv, auxvert_t *av)
{
    float zi;

// project points
    zi = 1.0f / av->fv[2];

    fv->v[5] = zi * _g->ziscale;

    fv->v[0] = (av->fv[0] * aliasxscale * zi) + aliasxcenter;
    fv->v[1] = (av->fv[1] * aliasyscale * zi) + aliasycenter;
}

/*
 ================
 R_AliasPrepareUnclippedPoints
 ================
 */
void R_AliasPrepareUnclippedPoints(void)
{
    stvert_t *pstverts;
    finalvert_t *fv;

    pstverts = (stvert_t*) ((byte*) _g->paliashdr + _g->paliashdr->stverts);
    _g->r_anumverts = _g->pmdl->numverts;
    /*
     // copy verts in ram to get better speed later
     byte *buffer = (byte*) getGpBuffer() + SURFACE_SIZE;
     int size = _g->r_anumverts * sizeof(*pstverts);
     buffer = buffer - size;
     Q_memcpy(buffer, pstverts, size);
     pstverts = buffer;
     */
// FIXME: just use pfinalverts directly?
    fv = _g->pfinalverts;
#if !NO_MINIMIZE
    _g->r_affinetridesc.paliashdr = _g->paliashdr;

#endif
    R_AliasTransformAndProjectFinalVerts(fv, pstverts);
#if NO_MINIMIZE
	if (r_affinetridesc.drawtype)
		D_PolysetDrawFinalVerts (fv, r_anumverts);
#else
#if ENABLE_RECURSIVE_DRAWING
    if (_g->r_affinetridesc.drawtype)
        D_PolysetDrawFinalVerts(fv, _g->r_anumverts);
#endif
#endif
    _g->r_affinetridesc.pfinalverts = _g->pfinalverts;
    //r_affinetridesc.ptriangles = (mtriangle_t *) ((byte *)paliashdr + paliashdr->triangles);
    _g->r_affinetridesc.ptriangles = _g->r_affinetridesc.tempTriangleBuffer;     // triangles are loaded there

    _g->r_affinetridesc.numtriangles = _g->pmdl->numtris;

    D_PolysetDraw();
}

/*
 ===============
 R_AliasSetupSkin
 ===============
 */
void R_AliasSetupSkin(void)
{
    int skinnum;
    int i, numskins;
    maliasskingroup_t *paliasskingroup;
    float *pskinintervals, fullskininterval;
    float skintargettime, skintime;

    skinnum = getEntitySkinnum(_g->currententity);
    if ((skinnum >= _g->pmdl->numskins) || (skinnum < 0))
    {
        Con_DPrintf("R_AliasSetupSkin: no such skin # %d\n", skinnum);
        skinnum = 0;
    }

    _g->pskindesc = ((maliasskindesc_t*) ((byte*) _g->paliashdr + _g->paliashdr->skindesc)) + skinnum;
    _g->a_skinwidth = _g->pmdl->skinwidth;

    if (_g->pskindesc->type != ALIAS_SKIN_SINGLE)
    {
        while (1)
            FIXME("ALIAS SKIN GROUP NOT SUPPORTED FOR NOW");
        paliasskingroup = (maliasskingroup_t*) ((byte*) _g->paliashdr + _g->pskindesc->skin);
        pskinintervals = (float*) ((byte*) _g->paliashdr + paliasskingroup->intervals);
        numskins = paliasskingroup->numskins;
        fullskininterval = pskinintervals[numskins - 1];

#if FLOAT_SYNCBASE
		skintime = cl.time + currententity->syncbase;
#else
        skintime = _g->cl.time + _g->currententity->syncbase_s * (1.0f / ((1 << SYNCBASE_BITS) - 1));
#endif
        // when loading in Mod_LoadAliasSkinGroup, we guaranteed all interval
        // values are positive, so we don't have to worry about division by 0
        skintargettime = skintime - ((int) (skintime / fullskininterval)) * fullskininterval;

        for (i = 0; i < (numskins - 1); i++)
        {
            if (pskinintervals[i] > skintargettime)
                break;
        }

        _g->pskindesc = &paliasskingroup->skindescs[i];
    }

    _g->r_affinetridesc.pskindesc = _g->pskindesc;
    //

    //
    _g->r_affinetridesc.pskin = (void*) ((byte*) _g->paliashdr->extMemAddress + _g->pskindesc->skin);
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
    _g->r_affinetridesc.pOriginalskin = (void*) ((byte*) _g->paliashdr->extMemAddress + _g->pskindesc->originalSkin);
#endif
    _g->r_affinetridesc.skinwidth = _g->a_skinwidth;
    _g->r_affinetridesc.seamfixupX16 = (_g->a_skinwidth >> 1) << 16;
    _g->r_affinetridesc.skinheight = _g->pmdl->skinheight;
}

/*
 ================
 R_AliasSetupLighting
 ================
 */
void R_AliasSetupLighting(alight_t *plighting)
{

// guarantee that no vertex will ever be lit below LIGHT_MIN, so we don't have
// to clamp off the bottom
    _g->r_ambientlight = plighting->ambientlight;

    if (_g->r_ambientlight < LIGHT_MIN)
        _g->r_ambientlight = LIGHT_MIN;

    _g->r_ambientlight = (255 - _g->r_ambientlight) << VID_CBITS;

    if (_g->r_ambientlight < LIGHT_MIN)
        _g->r_ambientlight = LIGHT_MIN;

    _g->r_shadelight = plighting->shadelight;

    if (_g->r_shadelight < 0)
        _g->r_shadelight = 0;

    _g->r_shadelight *= VID_GRADES;

// rotate the lighting vector into the model's frame of reference
    _g->r_plightvec[0] = DotProduct(plighting->plightvec, _g->alias_forward);
    _g->r_plightvec[1] = -DotProduct(plighting->plightvec, _g->alias_right);
    _g->r_plightvec[2] = DotProduct(plighting->plightvec, _g->alias_up);
}

/*
 =================
 R_AliasSetupFrame

 set r_apverts
 =================
 */
void R_AliasSetupFrame(void)
{
    int frame;
    int i, numframes;
    maliasgroup_t *paliasgroup;
    float *pintervals, fullinterval, targettime, time;

    frame = getEntityFrame(_g->currententity);
    if ((frame >= _g->pmdl->numframes) || (frame < 0))
    {
        Con_DPrintf("R_AliasSetupFrame: no such frame %d\n", frame);
        frame = 0;
    }

    if (_g->paliashdr->frames[frame].type == ALIAS_SINGLE)
    {
//		r_apverts = (trivertx_t *)	((byte *)paliashdr->extMemAddress + paliashdr->frames[frame].frame);
        extMemWaitAsynchDataRead();
        _g->r_apverts = extMemGetDataFromAddress(_g->r_affinetridesc.tempAnimVertsBuffer,
            (trivertx_t*) ((byte*) _g->paliashdr->extMemAddress + _g->paliashdr->frames[frame].frame), sizeof(trivertx_t) * _g->pmdl->numverts);
#if WIN32
            if (((uint32_t)((byte *)_g->paliashdr->extMemAddress + _g->paliashdr->frames[frame].frame)) & 3)
                FIXME("r_apverts_Not aligned");
        #endif // WIN32
        return;
    }

    paliasgroup = (maliasgroup_t*) ((byte*) _g->paliashdr + _g->paliashdr->frames[frame].frame);
    pintervals = (float*) ((byte*) _g->paliashdr/*->extMemAddress*/+ paliasgroup->intervals);

    numframes = paliasgroup->numframes;
    fullinterval = pintervals[numframes - 1];
#if FLOAT_SYNCBASE
	time = cl.time + currententity->syncbase;
#else
    time = _g->cl.time + _g->currententity->syncbase_s * (1.0f / ((1 << SYNCBASE_BITS) - 1));
#endif
//
// when loading in Mod_LoadAliasGroup, we guaranteed all interval values
// are positive, so we don't have to worry about division by 0
//
    targettime = time - ((int) (time / fullinterval)) * fullinterval;

    for (i = 0; i < (numframes - 1); i++)
    {
        if (pintervals[i] > targettime)
            break;
    }

    //r_apverts = (trivertx_t *) 	((byte *)paliashdr->extMemAddress + paliasgroup->frames[i].frame);
    extMemWaitAsynchDataRead();
    _g->r_apverts = (trivertx_t*) extMemGetDataFromAddress(_g->r_affinetridesc.tempAnimVertsBuffer,
        ((byte*) _g->paliashdr->extMemAddress + paliasgroup->frames[i].frame), sizeof(trivertx_t) * _g->pmdl->numverts);
#if WIN32
            if (((uint32_t) ((byte *)_g->paliashdr->extMemAddress + paliasgroup->frames[i].frame)) & 3)
                FIXME("r_apverts 2 Not aligned");
        #endif // WIN32
}

/*
 ================
 R_AliasDrawModel
 ================
 */
void R_AliasDrawModel(alight_t *plighting)
{
    finalvert_t finalverts[MAXALIASVERTS + ((CACHE_SIZE - 1) / sizeof(finalvert_t)) + 1];
    auxvert_t auxverts[MAXALIASVERTS];

    _g->paliashdr = (aliashdr_t*) Mod_Extradata(getEntityModel(_g->currententity));
#if !NO_MINIMIZE
    _g->r_affinetridesc.paliashdr = _g->paliashdr;
#endif
    _g->pmdl = (mdl_t*) ((byte*) _g->paliashdr + _g->paliashdr->model);

    _g->r_affinetridesc.tempTriangleBuffer = extMemStartAsynchDataRead((uint32_t) (((byte*) _g->paliashdr->extMemAddress + _g->paliashdr->triangles)),
        getTextureCacheBuffer(), sizeof(mtriangle_t) * _g->pmdl->numtris);

// cache align
    _g->pfinalverts = (finalvert_t*) (((long) &finalverts[0] + CACHE_SIZE - 1) & ~(CACHE_SIZE - 1));
    _g->pauxverts = &auxverts[0];
#if WIN32
        if (((uint32_t)_g->paliashdr->extMemAddress + _g->paliashdr->triangles) & 3)
            FIXME(">>>>>>>>>Not aligned");
    #endif // WIN32

    _g->r_affinetridesc.tempAnimVertsBuffer = (byte*) _g->r_affinetridesc.tempTriangleBuffer + sizeof(mtriangle_t) * _g->pmdl->numtris;
    _g->r_affinetridesc.tempTriangleOffsetData = (byte*) _g->r_affinetridesc.tempAnimVertsBuffer + sizeof(trivertx_t) * _g->pmdl->numverts;

//	printf("Position in gpBuffer: %d\r\n", (byte*) r_affinetridesc.tempTriangleOffsetData - (byte*)getGpBuffer());

    R_AliasSetupSkin();
    R_AliasSetUpTransform(_g->currententity->trivial_accept);
    R_AliasSetupLighting(plighting);
    //
#if HAS_MULTIPLAYER
  acolormap = currententity->colormap;
#else
    _g->acolormap = vid.colormap;
#endif
    if (_g->currententity != &_g->cl.viewent)
        _g->ziscale = (float) 0x8000 * (float) 0x10000;
    else
        _g->ziscale = (float) 0x8000 * (float) 0x10000 * 3.0f;

    //

    R_AliasSetupFrame(); // this will ask for wait for dma operation.

#if HAS_MULTIPLAYER
	if (!currententity->colormap)
		Sys_Error ("R_AliasDrawModel: !currententity->colormap");
#endif
#define TRIVIAL_ACCEPT 1
#if TRIVIAL_ACCEPT
    _g->r_affinetridesc.drawtype = (_g->currententity->trivial_accept == 3) && (ENABLE_RECURSIVE_DRAWING);
#else
	r_affinetridesc.drawtype = 0;
#endif
#if NO_MINIMIZE
	if (r_affinetridesc.drawtype)
	{
		D_PolysetUpdateTables ();		// FIXME: precalc...
	}
	else
	{
#if	id386
		D_Aff8Patch (currententity->colormap);
#endif
	}
#endif

    if (_g->currententity->trivial_accept)
    {
        R_AliasPrepareUnclippedPoints();
    }
    else
        R_AliasPreparePoints();
#if ASYNCH_ALIAS_SINGLE_RENDERING
    flushAliasPendingPixel();
#endif
}

