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
// r_aclip.c: clip routines for drawing Alias models directly to the screen
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"

void R_AliasProjectFinalVert(finalvert_t *fv, auxvert_t *av);
void R_Alias_clip_top(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out);
void R_Alias_clip_bottom(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out);
void R_Alias_clip_left(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out);
void R_Alias_clip_right(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out);

/*
 ================
 R_Alias_clip_z

 pfv0 is the unclipped vertex, pfv1 is the z-clipped vertex
 ================
 */
void R_Alias_clip_z(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out)
{
#if WIN32 && 0
    static int cnt = 0;
    cnt ++;
    printf("%s %d\r\n", __FUNCTION__, cnt);
    #endif // WIN32
    float scale;
    auxvert_t *pav0, *pav1, avout;

    pav0 = &_g->av[pfv0 - &_g->aclip_fv[0][0]];
    pav1 = &_g->av[pfv1 - &_g->aclip_fv[0][0]];

    if (pfv0->v[1] >= pfv1->v[1])
    {
        scale = (ALIAS_Z_CLIP_PLANE - pav0->fv[2]) / (pav1->fv[2] - pav0->fv[2]);

        avout.fv[0] = pav0->fv[0] + (pav1->fv[0] - pav0->fv[0]) * scale;
        avout.fv[1] = pav0->fv[1] + (pav1->fv[1] - pav0->fv[1]) * scale;
        avout.fv[2] = ALIAS_Z_CLIP_PLANE;

        out->v[2] = pfv0->v[2] + (pfv1->v[2] - pfv0->v[2]) * scale;
        out->v[3] = pfv0->v[3] + (pfv1->v[3] - pfv0->v[3]) * scale;
        out->v[4] = pfv0->v[4] + (pfv1->v[4] - pfv0->v[4]) * scale;
    }
    else
    {
        scale = (ALIAS_Z_CLIP_PLANE - pav1->fv[2]) / (pav0->fv[2] - pav1->fv[2]);

        avout.fv[0] = pav1->fv[0] + (pav0->fv[0] - pav1->fv[0]) * scale;
        avout.fv[1] = pav1->fv[1] + (pav0->fv[1] - pav1->fv[1]) * scale;
        avout.fv[2] = ALIAS_Z_CLIP_PLANE;

        out->v[2] = pfv1->v[2] + (pfv0->v[2] - pfv1->v[2]) * scale;
        out->v[3] = pfv1->v[3] + (pfv0->v[3] - pfv1->v[3]) * scale;
        out->v[4] = pfv1->v[4] + (pfv0->v[4] - pfv1->v[4]) * scale;
    }

    R_AliasProjectFinalVert(out, &avout);
    int flags = 0;
    if (out->v[0] < _g->r_refdef.aliasvrect.x)
        flags = ALIAS_LEFT_CLIP;
    if (out->v[1] < _g->r_refdef.aliasvrect.y)
        flags |= ALIAS_TOP_CLIP;
    if (out->v[0] > _g->r_refdef.aliasvrectright)
        flags |= ALIAS_RIGHT_CLIP;
    if (out->v[1] > _g->r_refdef.aliasvrectbottom)
        flags |= ALIAS_BOTTOM_CLIP;
    out->flags |= flags;
}

#if	!id386

void R_Alias_clip_left(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out)
{
    float scale;
    int i;

    if (pfv0->v[1] >= pfv1->v[1])
    {
        scale = (float) (_g->r_refdef.aliasvrect.x - pfv0->v[0]) / (pfv1->v[0] - pfv0->v[0]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv0->v[i] + (pfv1->v[i] - pfv0->v[i]) * scale + 0.5f;
    }
    else
    {
        scale = (float) (_g->r_refdef.aliasvrect.x - pfv1->v[0]) / (pfv0->v[0] - pfv1->v[0]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv1->v[i] + (pfv0->v[i] - pfv1->v[i]) * scale + 0.5f;
    }
}

void R_Alias_clip_right(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out)
{
    float scale;
    int i;

    if (pfv0->v[1] >= pfv1->v[1])
    {
        scale = (float) (_g->r_refdef.aliasvrectright - pfv0->v[0]) / (pfv1->v[0] - pfv0->v[0]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv0->v[i] + (pfv1->v[i] - pfv0->v[i]) * scale + 0.5f;
    }
    else
    {
        scale = (float) (_g->r_refdef.aliasvrectright - pfv1->v[0]) / (pfv0->v[0] - pfv1->v[0]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv1->v[i] + (pfv0->v[i] - pfv1->v[i]) * scale + 0.5f;
    }
}

void R_Alias_clip_top(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out)
{
    float scale;
    int i;

    if (pfv0->v[1] >= pfv1->v[1])
    {
        scale = (float) (_g->r_refdef.aliasvrect.y - pfv0->v[1]) / (pfv1->v[1] - pfv0->v[1]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv0->v[i] + (pfv1->v[i] - pfv0->v[i]) * scale + 0.5;
    }
    else
    {
        scale = (float) (_g->r_refdef.aliasvrect.y - pfv1->v[1]) / (pfv0->v[1] - pfv1->v[1]);
        for (i = 0; i < 6; i++)
            out->v[i] = pfv1->v[i] + (pfv0->v[i] - pfv1->v[i]) * scale + 0.5;
    }
}

void R_Alias_clip_bottom(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out)
{
    float scale;
    int i;

    if (pfv0->v[1] >= pfv1->v[1])
    {
        scale = (float) (_g->r_refdef.aliasvrectbottom - pfv0->v[1]) / (pfv1->v[1] - pfv0->v[1]);

        for (i = 0; i < 6; i++)
            out->v[i] = pfv0->v[i] + (pfv1->v[i] - pfv0->v[i]) * scale + 0.5f;
    }
    else
    {
        scale = (float) (_g->r_refdef.aliasvrectbottom - pfv1->v[1]) / (pfv0->v[1] - pfv1->v[1]);

        for (i = 0; i < 6; i++)
            out->v[i] = pfv1->v[i] + (pfv0->v[i] - pfv1->v[i]) * scale + 0.5f;
    }
}

#endif

int R_AliasClip(finalvert_t *in, finalvert_t *out, int flag, int count, void (*clip)(finalvert_t *pfv0, finalvert_t *pfv1, finalvert_t *out))
{
    int i, j, k;
    int flags, oldflags;

    j = count - 1;
    k = 0;
    for (i = 0; i < count; j = i, i++)
    {
        oldflags = in[j].flags & flag;
        flags = in[i].flags & flag;

        if (flags && oldflags)
            continue;
        if (oldflags ^ flags)
        {
            clip(&in[j], &in[i], &out[k]);
            int outflags = 0; // was out[k].flags = 0;
            if (out[k].v[0] < _g->r_refdef.aliasvrect.x)
                outflags = ALIAS_LEFT_CLIP;
            if (out[k].v[1] < _g->r_refdef.aliasvrect.y)
                outflags |= ALIAS_TOP_CLIP;
            if (out[k].v[0] > _g->r_refdef.aliasvrectright)
                outflags |= ALIAS_RIGHT_CLIP;
            if (out[k].v[1] > _g->r_refdef.aliasvrectbottom)
                outflags |= ALIAS_BOTTOM_CLIP;
            out[k].flags = outflags;
            k++;
        }
        if (!flags)
        {
            out[k] = in[i];
            k++;
        }
    }

    return k;
}

/*
 ================
 R_AliasClipTriangle
 ================
 */
void R_AliasClipTriangle(mtriangle_t *ptri)
{
    int i, k, pingpong;
    mtriangle_t mtri;
    unsigned clipflags;

// copy vertexes and fix seam texture coordinates
    if (ptri->facesfront)
    {
        _g->aclip_fv[0][0] = _g->pfinalverts[ptri->vertindex0];
        _g->aclip_fv[0][1] = _g->pfinalverts[ptri->vertindex1];
        _g->aclip_fv[0][2] = _g->pfinalverts[ptri->vertindex2];
    }
    else
    {
        _g->aclip_fv[0][0] = _g->pfinalverts[ptri->vertindex0];
        _g->aclip_fv[0][1] = _g->pfinalverts[ptri->vertindex1];
        _g->aclip_fv[0][2] = _g->pfinalverts[ptri->vertindex2];

        for (i = 0; i < 3; i++)
        {

            if (!ptri->facesfront && (_g->aclip_fv[0][i].flags & ALIAS_ONSEAM))
                _g->aclip_fv[0][i].v[2] += _g->r_affinetridesc.seamfixupX16;
        }
    }

// clip
    clipflags = _g->aclip_fv[0][0].flags | _g->aclip_fv[0][1].flags | _g->aclip_fv[0][2].flags;

    if (clipflags & ALIAS_Z_CLIP)
    {
//		for (i=0 ; i<3 ; i++)
        _g->av[0] = _g->pauxverts[ptri->vertindex0];
        _g->av[1] = _g->pauxverts[ptri->vertindex1];
        _g->av[2] = _g->pauxverts[ptri->vertindex2];

        k = R_AliasClip(_g->aclip_fv[0], _g->aclip_fv[1], ALIAS_Z_CLIP, 3, R_Alias_clip_z);
        if (k == 0)
            return;

        pingpong = 1;
        clipflags = _g->aclip_fv[1][0].flags | _g->aclip_fv[1][1].flags | _g->aclip_fv[1][2].flags;
    }
    else
    {
        pingpong = 0;
        k = 3;
    }

    if (clipflags & ALIAS_LEFT_CLIP)
    {
        k = R_AliasClip(_g->aclip_fv[pingpong], _g->aclip_fv[pingpong ^ 1],
        ALIAS_LEFT_CLIP, k, R_Alias_clip_left);
        if (k == 0)
            return;

        pingpong ^= 1;
    }

    if (clipflags & ALIAS_RIGHT_CLIP)
    {
        k = R_AliasClip(_g->aclip_fv[pingpong], _g->aclip_fv[pingpong ^ 1],
        ALIAS_RIGHT_CLIP, k, R_Alias_clip_right);
        if (k == 0)
            return;

        pingpong ^= 1;
    }

    if (clipflags & ALIAS_BOTTOM_CLIP)
    {
        k = R_AliasClip(_g->aclip_fv[pingpong], _g->aclip_fv[pingpong ^ 1],
        ALIAS_BOTTOM_CLIP, k, R_Alias_clip_bottom);
        if (k == 0)
            return;

        pingpong ^= 1;
    }

    if (clipflags & ALIAS_TOP_CLIP)
    {
        k = R_AliasClip(_g->aclip_fv[pingpong], _g->aclip_fv[pingpong ^ 1],
        ALIAS_TOP_CLIP, k, R_Alias_clip_top);
        if (k == 0)
            return;

        pingpong ^= 1;
    }

    for (i = 0; i < k; i++)
    {
        if (_g->aclip_fv[pingpong][i].v[0] < _g->r_refdef.aliasvrect.x)
            _g->aclip_fv[pingpong][i].v[0] = _g->r_refdef.aliasvrect.x;
        else if (_g->aclip_fv[pingpong][i].v[0] > _g->r_refdef.aliasvrectright)
            _g->aclip_fv[pingpong][i].v[0] = _g->r_refdef.aliasvrectright;

        if (_g->aclip_fv[pingpong][i].v[1] < _g->r_refdef.aliasvrect.y)
            _g->aclip_fv[pingpong][i].v[1] = _g->r_refdef.aliasvrect.y;
        else if (_g->aclip_fv[pingpong][i].v[1] > _g->r_refdef.aliasvrectbottom)
            _g->aclip_fv[pingpong][i].v[1] = _g->r_refdef.aliasvrectbottom;

        _g->aclip_fv[pingpong][i].flags = 0;
    }

// draw triangles
#if !NO_MINIMIZE
    mtri.triangleOffsetDataPos = ptri->triangleOffsetDataPos;
#endif
    mtri.facesfront = ptri->facesfront;
    mtri.triangleSize = ptri->triangleSize;
    mtri.triangleOffsetNumber = ptri->triangleOffsetNumber;
#if MTRIANGLE_HAS_OFFSET_DATA
	mtri.bufferOffset = ptri->bufferOffset;
	mtri.offsetS = ptri->offsetS;
	mtri.startOffset  = ptri->startOffset;
#endif
    _g->r_affinetridesc.ptriangles = &mtri;
    _g->r_affinetridesc.pfinalverts = _g->aclip_fv[pingpong];
// FIXME: do all at once as trifan?
    mtri.vertindex0 = 0;
    for (i = 1; i < k - 1; i++)
    {
        mtri.vertindex1 = i;
        mtri.vertindex2 = i + 1;
        D_PolysetDraw();
    }
}

