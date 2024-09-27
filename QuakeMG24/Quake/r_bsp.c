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
// r_bsp.c
#include "quakedef.h"
#include "r_local.h"
#if !LEAF_HAS_KEY
#if LEAF_KEY_IN_AUX_RAM
AUX_SECTION short leafKey[MAX_MAP_LEAFS];         // this might be too big
#error correct the code using _g->leafKey
#endif
#endif // LEAF_HAS_KEY
/* next-hack: MAX_BMODEL_VERTS and MAX_BMODEL_EDGES were originally 500 and 1000, respectively. However, later these were reduced to 100 and 500, respectively
 * to save stack. Also structures were trimmed. Later, we discovered that these could have been safely placed in the (temporarily) unused texture buffer, so
 * we restored the original structs (faster) and limits. Note that we found that 100 and 200 limits are still fine, but let's keep original implementation
 * where possible, to have less things to be worried about.
 */
#if WIN32
#define MAX_BMODEL_VERTS  500 //100  // next-hack: see comment above
// If we have a 64 bit environment, this stil has to be reduced as it won't fit.
#define MAX_BMODEL_EDGES  500 //200  // next-hack: see comment above
#else
#define MAX_BMODEL_VERTS  500 //100  // next-hack: see comment above
#define MAX_BMODEL_EDGES  1000 //200  // next-hack: see comment above
#endif
#if !BEDGE_HAS_NEXT_POINTERS
bedge_t *getBedgeNext(bedge_t *pb)
{
    int index = _g->sp_nextBedgeIndexArray[pb - _g->sp_bedge];
    if (!index)
        return NULL;
    else
        return _g->sp_bedge + index;
}
void setBedgeNext(bedge_t *pb, bedge_t *next)
{
    if (next == NULL)
    {
      _g->sp_nextBedgeIndexArray[pb - _g->sp_bedge] = 0;
    }
    else
    {
      _g->sp_nextBedgeIndexArray[pb - _g->sp_bedge] = next - _g->sp_bedge;
    }
}
#endif

#if !BEDGE_HAS_VERTEX_POINTERS
mvertex_t *getBedgeV(bedge_t *pb, int index)
{
    if (index)
    {
        if (!pb->v1_idx)
            return NULL;
        else if (pb->notStackVertRelative1)
        {
            if (!r_pcurrentvertbase)
            {
                FIXME("HARD ERROR");
            }
            return r_pcurrentvertbase - 1 + pb->v1_idx;
        }
        else
            return _g->sp_bverts + pb->v1_idx;
    }
    else
    {
        if (!pb->v0_idx)
            return NULL;
        else if (pb->notStackVertRelative0)
        {
            if (!r_pcurrentvertbase)
            {
                FIXME("HARD ERROR");
            }
            return r_pcurrentvertbase - 1 + pb->v0_idx;
        }
        else
            return _g->sp_bverts + pb->v0_idx;
    }
}
void setBedgeV(bedge_t *pb, int index, mvertex_t *v)
{
    if (v == NULL)
    {
        if (index)
            pb->v1_idx = 0;
        else
            pb->v0_idx = 0;
    }
    else
    {
        unsigned int distance = (byte*)v - (byte*)_g->sp_bverts;
        distance = distance / sizeof(*v);
        int notStackVertRelative ;
        if (distance >= MAX_BMODEL_VERTS)
        {
            distance = v - (r_pcurrentvertbase - 1);
            notStackVertRelative = 1;
           /* if (distance > 32767)
            {
                printf("distance %d, v %p, r_pcurrentvertbase %p, sp_bverts %p, stack distance %d\r\n", distance, v, r_pcurrentvertbase, sp_bverts, v - sp_bverts);
                FIXME("ERROR, INDEX TOO LARGE FOR vertex in bedge");

            }*/
        }
        else
        {
            notStackVertRelative = 0;
        }
/*        if (distance == 0)
        {
            FIXME("ERROR DISTANCE 0");
        }*/
        if (index)
        {
            pb->v1_idx = distance;
            pb->notStackVertRelative1 = notStackVertRelative;
        }
        else
        {
            pb->v0_idx = distance;
            pb->notStackVertRelative0 = notStackVertRelative;
        }
    }
}
#endif
//===========================================================================

/*
 ================
 R_EntityRotate
 ================
 */
void R_EntityRotate(vec3_t vec)
{
    vec3_t tvec;

    VectorCopy(vec, tvec);
    vec[0] = DotProduct(_g->entity_rotation[0], tvec);
    vec[1] = DotProduct(_g->entity_rotation[1], tvec);
    vec[2] = DotProduct(_g->entity_rotation[2], tvec);
}

/*
 ================
 R_RotateBmodel
 ================
 */
void R_RotateBmodel(void)
{
    float angle, s, c, temp1[3][3], temp2[3][3], temp3[3][3];

// TODO: should use a look-up table
// TODO: should really be stored with the entity instead of being reconstructed
// TODO: could cache lazily, stored in the entity
// TODO: share work with R_SetUpAliasTransform

// yaw
#if !ENTITY_HAS_SHORT_COORDS
  angle = currententity->angles[YAW];
#else
    angle = getEntityAngle(_g->currententity, YAW);
#endif
    angle = angle * M_PI * 2 / 360;
    s = sin_t(angle);
    c = cos_t(angle);

    temp1[0][0] = c;
    temp1[0][1] = s;
    temp1[0][2] = 0;
    temp1[1][0] = -s;
    temp1[1][1] = c;
    temp1[1][2] = 0;
    temp1[2][0] = 0;
    temp1[2][1] = 0;
    temp1[2][2] = 1;

// pitch
#if !ENTITY_HAS_SHORT_COORDS
  angle = currententity->angles[PITCH];
#else
    angle = getEntityAngle(_g->currententity, PITCH);
#endif
    angle = angle * M_PI * 2 / 360;
    s = sin_t(angle);
    c = cos_t(angle);

    temp2[0][0] = c;
    temp2[0][1] = 0;
    temp2[0][2] = -s;
    temp2[1][0] = 0;
    temp2[1][1] = 1;
    temp2[1][2] = 0;
    temp2[2][0] = s;
    temp2[2][1] = 0;
    temp2[2][2] = c;

    R_ConcatRotations(temp2, temp1, temp3);

// roll
#if !ENTITY_HAS_SHORT_COORDS
  angle = currententity->angles[ROLL];
#else
    angle = getEntityAngle(_g->currententity, ROLL);
#endif
    angle = angle * M_PI * 2 / 360;
    s = sin_t(angle);
    c = cos_t(angle);

    temp1[0][0] = 1;
    temp1[0][1] = 0;
    temp1[0][2] = 0;
    temp1[1][0] = 0;
    temp1[1][1] = c;
    temp1[1][2] = s;
    temp1[2][0] = 0;
    temp1[2][1] = -s;
    temp1[2][2] = c;

    R_ConcatRotations(temp1, temp3, _g->entity_rotation);

//
// rotate modelorg and the transformation matrix
//
    R_EntityRotate(_g->modelorg);
    R_EntityRotate(_g->vpn);
    R_EntityRotate(_g->vright);
    R_EntityRotate(_g->vup);

    R_TransformFrustum();
}

/*
 ================
 R_RecursiveClipBPoly
 ================
 */
//
void R_RecursiveClipBPoly(bedge_t *pedges, mnode_t *pnode, msurface_t *psurf)
{
    bedge_t *psideedges[2], *pnextedge, *ptedge;
    int i, side, lastside;
    float dist, frac, lastdist;
    mplane_t *splitplane, tplane;
    mvertex_t *pvert, *plastvert, *ptvert;
    mnode_t *pn;

    //
    psideedges[0] = psideedges[1] = NULL;

    _g->makeclippededge = false;

// transform the BSP plane into model space
// FIXME: cache these?
#if NODE_HAS_PLANE_POINTER
    splitplane = pnode->plane;
#else
        splitplane = Mod_GetNodePlane(pnode, cl.worldmodel);
#endif

    setPlaneDist(&tplane, getPlaneDist(splitplane) - DotProduct(_g->r_entorigin, splitplane->normal));
    tplane.normal[0] = DotProduct(_g->entity_rotation[0], splitplane->normal);
    tplane.normal[1] = DotProduct(_g->entity_rotation[1], splitplane->normal);
    tplane.normal[2] = DotProduct(_g->entity_rotation[2], splitplane->normal);

// clip edges to BSP plane
    for (; pedges; pedges = pnextedge)
    {
#if BEDGE_HAS_NEXT_POINTERS
        pnextedge = pedges->pnext;
#else
        pnextedge = getBedgeNext(pedges);
#endif
        // set the status for the last point as the previous point
        // FIXME: cache this stuff somehow?
#if BEDGE_HAS_VERTEX_POINTERS
        plastvert = pedges->v[0];
#else
    plastvert = getBedgeV(pedges, 0);
#endif
        lastdist = DotProduct(plastvert->position, tplane.normal);
        float tplanedist = getPlaneDist(&tplane);
        if (lastdist > tplanedist)
            lastside = 0;
        else
            lastside = 1;
#if BEDGE_HAS_VERTEX_POINTERS
        pvert = pedges->v[1];
#else
    pvert = getBedgeV(pedges, 1);
#endif
        dist = DotProduct(pvert->position, tplane.normal);

        if (dist > tplanedist)
            side = 0;
        else
            side = 1;

        if (side != lastside)
        {
            // clipped
            if (_g->numbverts >= MAX_BMODEL_VERTS)
            {
                Con_Printf("Out of BMODEL_VERTS for bmodel\n");
                FIXME("Out of BMODEL_VERTS");

                return;
            }

            // generate the clipped vertex
            frac = (lastdist - tplanedist) / (lastdist - dist);
            ptvert = &_g->pbverts[_g->numbverts++];
            ptvert->position[0] = plastvert->position[0] + frac * (pvert->position[0] - plastvert->position[0]);
            ptvert->position[1] = plastvert->position[1] + frac * (pvert->position[1] - plastvert->position[1]);
            ptvert->position[2] = plastvert->position[2] + frac * (pvert->position[2] - plastvert->position[2]);

            // split into two edges, one on each side, and remember entering
            // and exiting points
            // FIXME: share the clip edge by having a winding direction flag?
            if (_g->numbedges >= (MAX_BMODEL_EDGES - 1))
            {
                Con_Printf("Out of edges for bmodel\n");
                FIXME("Out of BMODEL_EDGES");
                return;
            }

            ptedge = &_g->pbedges[_g->numbedges];
#if BEDGE_HAS_NEXT_POINTERS
            ptedge->pnext = psideedges[lastside];
#else
      setBedgeNext(ptedge, psideedges[lastside]);
#endif
            psideedges[lastside] = ptedge;
#if BEDGE_HAS_VERTEX_POINTERS
            ptedge->v[0] = plastvert;
            ptedge->v[1] = ptvert;
#else
      setBedgeV(ptedge, 0, plastvert);
      setBedgeV(ptedge, 1, ptvert);
#endif
            ptedge = &_g->pbedges[_g->numbedges + 1];
#if BEDGE_HAS_NEXT_POINTERS
            ptedge->pnext = psideedges[side];
#else
      setBedgeNext(ptedge, psideedges[side]);
#endif
            psideedges[side] = ptedge;
#if BEDGE_HAS_VERTEX_POINTERS
            ptedge->v[0] = ptvert;
            ptedge->v[1] = pvert;
#else
      setBedgeV(ptedge, 0, ptvert);
      setBedgeV(ptedge, 1, pvert);
#endif
            _g->numbedges += 2;

            if (side == 0)
            {
                // entering for front, exiting for back
                _g->pfrontenter = ptvert;
                _g->makeclippededge = true;
            }
            else
            {
                _g->pfrontexit = ptvert;
                _g->makeclippededge = true;
            }
        }
        else
        {
            // add the edge to the appropriate side
#if BEDGE_HAS_NEXT_POINTERS
            pedges->pnext = psideedges[side];
#else
      setBedgeNext(pedges, psideedges[side]);

#endif
            psideedges[side] = pedges;
        }
    }

// if anything was clipped, reconstitute and add the edges along the clip
// plane to both sides (but in opposite directions)
    if (_g->makeclippededge)
    {
        if (_g->numbedges >= (MAX_BMODEL_EDGES - 2))
        {
            Con_Printf("Out of edges for bmodel2\n");
            FIXME("Out of BMODEL_EDGES");
            return;
        }

        ptedge = &_g->pbedges[_g->numbedges];
#if BEDGE_HAS_NEXT_POINTERS
        ptedge->pnext = psideedges[0];
#else
        setBedgeNext(ptedge, psideedges[0]);
#endif
        psideedges[0] = ptedge;
#if BEDGE_HAS_VERTEX_POINTERS
        ptedge->v[0] = _g->pfrontexit;
        ptedge->v[1] = _g->pfrontenter;
#else
    setBedgeV(ptedge, 0, _g->pfrontexit);
    setBedgeV(ptedge, 1, _g->pfrontenter);

#endif
        ptedge = &_g->pbedges[_g->numbedges + 1];
#if BEDGE_HAS_NEXT_POINTERS
        ptedge->pnext = psideedges[1];
#else
        setBedgeNext(ptedge, psideedges[1]);
#endif
        psideedges[1] = ptedge;
#if BEDGE_HAS_VERTEX_POINTERS
        ptedge->v[0] = _g->pfrontenter;
        ptedge->v[1] = _g->pfrontexit;
#else
    setBedgeV(ptedge, 0, _g->pfrontenter);
    setBedgeV(ptedge, 1, _g->pfrontexit);
#endif
        _g->numbedges += 2;
    }

// draw or recurse further
    for (i = 0; i < 2; i++)
    {
        if (psideedges[i])
        {
            // draw if we've reached a non-solid leaf, done if all that's left is a
            // solid leaf, and continue down the tree if it's not a leaf
#if NODE_HAS_CHILDREN_POINTERS
      pn = pnode->children[i];
#else

//      pn = Mod_GetChildNode(pnode, i, currententity->model);
            pn = Mod_GetChildNode(pnode, i, _g->cl.worldmodel);
#endif
            // we're done with this branch if the node or leaf isn't in the PVS
#if USING_R_VISFRAMECOUNT
      if (pn->visframe == r_visframecount)
#else
            //FIXME if (currententity->model->nodes == cl.worldmodel->nodes)
#endif
            {
                if (pn->contents < 0)
                {   //leaf
#if !USING_R_VISFRAMECOUNT
#if OLD_NODE_STRUCTURE
#if !SEPARATE_BRUSH_MODEL_DATA
                     unsigned int index = ((byte*) pn - (byte*)cl.worldmodel->leafs) / sizeof(mleaf_t);
#else
                     unsigned int index = ((byte*) pn - (byte*)cl.worldmodel->brushModelData->leafs) / sizeof(mleaf_t);
#endif
#else
                    unsigned int index = pn->node_idx;
#endif
                    checkNodeIndex(index, -1, __LINE__);
                    if ((pn->contents != CONTENTS_SOLID) && (_g->visleaves[index >> 3] & (1 << (index & 7))))
#else
          if (pn->contents != CONTENTS_SOLID)
#endif

                    {
#if LEAF_HAS_KEY
            r_currentbkey = ((mleaf_t *)pn)->key;
#else
                        _g->r_currentbkey = _g->leafKey[index];
#endif
                        R_RenderBmodelFace(psideedges[i], psurf);
                    }
                }
                else
                {  //node
#if !USING_R_VISFRAMECOUNT
#if OLD_NODE_STRUCTURE
#if !SEPARATE_BRUSH_MODEL_DATA
                    unsigned int index = ((byte*) pn - (byte*)cl.worldmodel->nodes) / sizeof(mnode_t);
#else
                    unsigned int index = ((byte*) pn - (byte*)cl.worldmodel->brushModelData->nodes) / sizeof(mnode_t);
#endif
#else
                    unsigned int index = pn->node_idx;
#endif
                    checkNodeIndex(index, 0, __LINE__);
                    if ((_g->visnodes[index >> 3] & (1 << (index & 7))))
#endif
#if NODE_HAS_CHILDREN_POINTERS
              R_RecursiveClipBPoly (psideedges[i], pnode->children[i], psurf);
                    #else
//                        R_RecursiveClipBPoly (psideedges[i], Mod_GetChildNode (pnode, i, currententity->model), psurf);
                        R_RecursiveClipBPoly(psideedges[i], Mod_GetChildNode(pnode, i, _g->cl.worldmodel), psurf);

#endif
                }
            }
        }
    }
}
/*
 ================
 R_DrawSolidClippedSubmodelPolygons
 ================
 */
void R_DrawSolidClippedSubmodelPolygons(model_t *pmodel)
{
    int i, j, lindex;
    vec_t dot;
    msurface_t *psurf;
    int numsurfaces;
    mplane_t *pplane;
#if MVERTEX_AND_BEDGE_IN_STACK
  mvertex_t bverts[MAX_BMODEL_VERTS];
  bedge_t   bedges[MAX_BMODEL_EDGES];
  uint8_t     nextBedgeIndexArray[MAX_BMODEL_EDGES] ;

#else
    mvertex_t *bverts = getTextureCacheBuffer();
    bedge_t *bedges = (bedge_t*) ((byte*) getTextureCacheBuffer() + MAX_BMODEL_VERTS * sizeof(mvertex_t));
    STATIC_ASSERT( MAX_BMODEL_EDGES * sizeof (bedge_t) + sizeof(mvertex_t) * MAX_BMODEL_VERTS < MAX_TEXTURE_SIZE);

#endif
    bedge_t *pbedge;
#if !BEDGE_HAS_NEXT_POINTERS
  _g->sp_bedge = &bedges[0] - 1; // so 0 will be NULL
  _g->sp_nextBedgeIndexArray = &nextBedgeIndexArray[0] - 1;
#endif
#if !BEDGE_HAS_VERTEX_POINTERS
  _g->sp_bverts = &bverts[0] - 1;  // so 0 will be NULL
#endif
    medge_t *pedge, *pedges;

// FIXME: use bounding-box-based frustum clipping info?

#if !SEPARATE_BRUSH_MODEL_DATA
  psurf = &pmodel->surfaces[pmodel->firstmodelsurface];
  numsurfaces = pmodel->nummodelsurfaces;
  pedges = pmodel->edges;

#else
    brush_model_data_t *currentBmd = pmodel->brushModelData;
    psurf = &currentBmd->surfaces[pmodel->brushModelData->firstmodelsurface];
    numsurfaces = currentBmd->nummodelsurfaces;
    pedges = currentBmd->edges;

#endif

    for (i = 0; i < numsurfaces; i++, psurf++)
    {
        // find which side of the node we are on
#if MSURFACE_HAS_PLANE_POINTER
        pplane = psurf->plane;
#else
        pplane = getMsurfacePlane(psurf);
#endif
        dot = DotProduct (_g->modelorg, pplane->normal) - getPlaneDist(pplane);

        // draw the polygon
        if (((psurf->flags & SURF_PLANEBACK) && (dot < -BACKFACE_EPSILON)) || (!(psurf->flags & SURF_PLANEBACK) && (dot > BACKFACE_EPSILON)))
        {
            // FIXME: use bounding-box-based frustum clipping info?

            // copy the edges to bedges, flipping if necessary so always
            // clockwise winding
            // FIXME: if edges and vertices get caches, these assignments must move
            // outside the loop, and overflow checking must be done here
            _g->pbverts = bverts;
            _g->pbedges = bedges;
            _g->numbverts = _g->numbedges = 0;
            int numedges = psurf->numedges;
            if (numedges > 0)
            {
                pbedge = &bedges[_g->numbedges];
                _g->numbedges += numedges;
                short *surfedges = &currentBmd->surfedges[psurf->firstedge];
                for (j = 0; j < numedges; j++)
                {
#if !SEPARATE_BRUSH_MODEL_DATA
           lindex = pmodel->surfedges[psurf->firstedge+j];
#else
                    lindex = *surfedges++;
#endif

                    if (lindex > 0)
                    {
                        pedge = &pedges[lindex];
#if BEDGE_HAS_VERTEX_POINTERS
                        pbedge[j].v[0] = &r_pcurrentvertbase[pedge->v[0]];
                        pbedge[j].v[1] = &r_pcurrentvertbase[pedge->v[1]];
#else
                    setBedgeV(&pbedge[j], 0, &r_pcurrentvertbase[pedge->v[0]]);
                    setBedgeV(&pbedge[j], 1, &r_pcurrentvertbase[pedge->v[1]]);
#endif
                    }
                    else
                    {
                        lindex = -lindex;
                        pedge = &pedges[lindex];
#if BEDGE_HAS_VERTEX_POINTERS
                        pbedge[j].v[0] = &r_pcurrentvertbase[pedge->v[1]];
                        pbedge[j].v[1] = &r_pcurrentvertbase[pedge->v[0]];
#else
                    setBedgeV(&pbedge[j], 0, &r_pcurrentvertbase[pedge->v[1]]);
                    setBedgeV(&pbedge[j], 1, &r_pcurrentvertbase[pedge->v[0]]);
#endif
                    }
#if BEDGE_HAS_NEXT_POINTERS
                    pbedge[j].pnext = &pbedge[j + 1];
#else
          setBedgeNext(&pbedge[j], &pbedge[j+1]);
#endif
                }
#if BEDGE_HAS_NEXT_POINTERS
                pbedge[j - 1].pnext = NULL; // mark end of edges
#else
        setBedgeNext(&pbedge[j-1], NULL); // mark end of edges

#endif
#if ENTITY_HAS_TOPNODE_POINTER
        R_RecursiveClipBPoly (pbedge, currententity->topnode, psurf);
#else
                R_RecursiveClipBPoly(pbedge, getEntityTopnode(_g->currententity), psurf);

#endif
            }
            else
            {
                Sys_Error("no edges in bmodel");
            }
        }
    }
}

/*
 ================
 R_DrawSubmodelPolygons
 ================
 */
void R_DrawSubmodelPolygons(model_t *pmodel, int clipflags)
{
    int i;
    vec_t dot;
    msurface_t *psurf;
    int numsurfaces;
    mplane_t *pplane;

// FIXME: use bounding-box-based frustum clipping info?
#if !SEPARATE_BRUSH_MODEL_DATA
  psurf = &pmodel->surfaces[pmodel->firstmodelsurface];
  numsurfaces = pmodel->nummodelsurfaces;
#else
    psurf = &pmodel->brushModelData->surfaces[pmodel->brushModelData->firstmodelsurface];
    numsurfaces = pmodel->brushModelData->nummodelsurfaces;
#endif
#if !LEAF_HAS_KEY  && !ENTITY_HAS_TOPNODE_POINTER
    int leafkey = _g->leafKey[((mleaf_t*) getEntityTopnode(_g->currententity))->leaf_idx];
#endif
    for (i = 0; i < numsurfaces; i++, psurf++)
    {
        // find which side of the node we are on
#if MSURFACE_HAS_PLANE_POINTER
        pplane = psurf->plane;
#else
        pplane = getMsurfacePlane(psurf);
#endif
        dot = DotProduct (_g->modelorg, pplane->normal) - getPlaneDist(pplane);

        // draw the polygon
        if (((psurf->flags & SURF_PLANEBACK) && (dot < -BACKFACE_EPSILON)) || (!(psurf->flags & SURF_PLANEBACK) && (dot > BACKFACE_EPSILON)))
        {
#if LEAF_HAS_KEY
#if ENTITY_HAS_TOPNODE_POINTER
      r_currentkey = ((mleaf_t *)currententity->topnode)->key;
#else
      r_currentkey = ((mleaf_t *)getEntityTopnode(currententity))->key;
#endif
#else
#if ENTITY_HAS_TOPNODE_POINTER
      r_currentkey = _g->leafKey[((mleaf_t *)currententity->topnode) - ((mleaf_t *)currententity->model->leafs)];
#else
#if PROFILE_DIVISIONS
    divisionForPointers++;
#endif
            _g->r_currentkey = leafkey;
#endif
#endif
            // FIXME: use bounding-box-based frustum clipping info?
            R_RenderFace(psurf, clipflags);
        }
    }
}
#if !USING_R_VISFRAMECOUNT
#if CHECK_NODE_INDEX
void checkNodeIndex(unsigned int index, int type, int line)
{
    if (index > MAX_MAP_LEAFS && type < 0 || index > MAX_MAP_NODES)
    {
        printf("index %d > MAX_MAP_LEAFS. Type is %d, line is %d\r\n", index, type, line);
        while(1) FIXME("broken");
    }
}
#endif
#if NO_INLINE_VISIBLE_NODE
int isNodeVisible(mnode_t *node)
{
    if (node->contents == 0)
    { // node
#if OLD_NODE_STRUCTURE
#if !SEPARATE_BRUSH_MODEL_DATA
        unsigned int index = node - cl.worldmodel->nodes;
#else
        unsigned int index = node - cl.worldmodel->brushModelData->nodes;

#endif
#else
        unsigned int index = node->node_idx;
#endif
        if ((_g->visnodes[index >> 3] & (1 << (index & 7))))
            return 1;
    }
    else
    {
#if OLD_NODE_STRUCTURE
#if !SEPARATE_BRUSH_MODEL_DATA
        unsigned int index = (mleaf_t*) node - cl.worldmodel->leafs;
#else
        unsigned int index = (mleaf_t*) node - cl.worldmodel->brushModelData->leafs;
#endif
#else
        unsigned int index = node->node_idx;     // common with leaf.
#endif
        checkNodeIndex(index, -1, __LINE__);
        if ((_g->visleaves[index >> 3] & (1 << (index & 7))))
            return 1;
    }
    return 0;
}
#endif
#endif
/*
 ================
 R_RecursiveWorldNode
 ================
 */
void R_RecursiveWorldNode(mnode_t *node, int clipflags)
{
    int i, c, side, *pindex;
    vec3_t acceptpt, rejectpt;
    mplane_t *plane;
    msurface_t *surf;
    mleaf_t *pleaf;
    QDFLOAT dot;
#if !CLIP_PLANE_USES_FLOAT
    int d;
#else
    QDFLOAT d;
#endif // CLIP_PLANE_USES_FLOAT

    if (node->contents == CONTENTS_SOLID)
        return;   // solid
#if USING_R_VISFRAMECOUNT
  if (node->visframe != r_visframecount)
    return;
#else
    if (!isNodeVisible(node))
    {
        return;
    }
#endif

// cull the clipping planes if not trivial accept
// FIXME: the compiler is doing a lousy job of optimizing here; it could be
//  twice as fast in ASM
    if (clipflags)
    {
        for (i = 0; i < 4; i++)
        {
            if (!(clipflags & (1 << i)))
                continue; // don't need to clip against it

            // generate accept and reject points
            // FIXME: do with fast look-ups or integer tests based on the sign bit
            // of the floating point values

            pindex = pfrustum_indexes[i];
#if CLIP_PLANE_USES_FLOAT
            rejectpt[0] = (float) node->minmaxs[pindex[0]];
            rejectpt[1] = (float) node->minmaxs[pindex[1]];
            rejectpt[2] = (float) node->minmaxs[pindex[2]];
            d = DotProduct(rejectpt, _g->view_clipplanes[i].normal);
            d -= _g->view_clipplanes[i].dist;

#else
            int rs[3];
            rs[0] = node->minmaxs[pindex[0]];
            rs[1] = node->minmaxs[pindex[1]];
            rs[2] = node->minmaxs[pindex[2]];
      d = DotProduct (rs, view_clipplanes[i].frac_normal);
      d -= view_clipplanes[i].dist;

#endif

            if (d <= 0)
            {
                return;
            }
#if CLIP_PLANE_USES_FLOAT
            acceptpt[0] = (float) node->minmaxs[pindex[3 + 0]];
            acceptpt[1] = (float) node->minmaxs[pindex[3 + 1]];
            acceptpt[2] = (float) node->minmaxs[pindex[3 + 2]];
            d = DotProduct(acceptpt, _g->view_clipplanes[i].normal);
            d -= _g->view_clipplanes[i].dist;
#else
            int as[3];
      as[0] = node->minmaxs[pindex[3+0]];
      as[1] = node->minmaxs[pindex[3+1]];
      as[2] = node->minmaxs[pindex[3+2]];

      d = DotProduct (as, view_clipplanes[i].frac_normal);
      d -= view_clipplanes[i].frac_dist;
#endif

            if (d >= 0)
                clipflags &= ~(1 << i); // node is entirely on screen
        }
    }

// if a leaf node, draw stuff
    if (node->contents < 0)
    {
        pleaf = (mleaf_t*) node;
#if LEAF_HAS_MARKSURFACES_POINTER
        msurface_t  **mark;
    mark = pleaf->firstmarksurface;
        c = pleaf->nummarksurfaces;

    if (c)
    {
      do
      {
#if SURF_HAS_VISFRAME
        (*mark)->visframe = r_framecount;
#else
            int index = (*mark) - cl.worldmodel->surfaces;
            if (index >= MAX_SURFACES)
                FIXME("BUUUU");
            surfMarked[index / 8] |= 1 << (index % 8);
            #error
#endif
        mark++;
      } while (--c);
    }

#else
#if !SEPARATE_BRUSH_MODEL_DATA
        short *markIdx = cl.worldmodel->marksurfaceIdx + pleaf->firstMarkSurfaceIdx;
#else
        short *markIdx = _g->cl.worldmodel->brushModelData->marksurfaceIdx + pleaf->firstMarkSurfaceIdx;
#endif
        c = pleaf->nummarksurfaces;

        if (c)
        {
#if 1
            do
            {
                unsigned int index = (*markIdx);
                _g->surfMarked[index / 32] |= 1 << (index % 32);
                markIdx++;
            }
            while (--c);
#else // tried to save but no, does not work..
 uint32_t oldArrayIndex = (*markIdx) / 32;
 uint32_t value = _g->surfMarked[oldArrayIndex];
 do
 {
           unsigned int index = (*markIdx);
           if (index / 32 != oldArrayIndex)
           {
             _g->surfMarked[oldArrayIndex] = value;
             oldArrayIndex = index / 32;
             value = _g->surfMarked[oldArrayIndex];
           }
           value |= 1 << (index % 32);
   markIdx++;
 } while (--c);
 _g->surfMarked[oldArrayIndex] = value;
#endif
        }
#endif

        // deal with model fragments in this leaf
#if !DIRECT_SINGLE_PLAYER
    if (pleaf->efrags)
    {
      R_StoreEfrags (&pleaf->efrags);
    }
#endif

#if LEAF_HAS_KEY
    pleaf->key = r_currentkey;
#else
#if OLD_NODE_STRUCTURE
        int idx = pleaf - cl.worldmodel->brushModelData->leafs;
#else
        int idx = pleaf->leaf_idx;
#endif
        _g->leafKey[idx] = _g->r_currentkey;
#endif
        _g->r_currentkey++;   // all bmodels in a leaf share the same key
    }
    else
    {
        // node is just a decision point, so go down the appropriate sides

        // find which side of the node we are on
#if NODE_HAS_PLANE_POINTER
        plane = node->plane;
#else
// todo check
        plane = Mod_GetNodePlane(node, cl.worldmodel);
#endif
        float planedist = getPlaneDist(plane);
        switch (plane->type)
        {
            case PLANE_X:
                dot = _g->modelorg[0] - planedist;
                break;
            case PLANE_Y:
                dot = _g->modelorg[1] - planedist;
                break;
            case PLANE_Z:
                dot = _g->modelorg[2] - planedist;
                break;
            default:
                dot = DotProduct (_g->modelorg, plane->normal) - planedist;
                break;
        }

        if (dot >= 0)
            side = 0;
        else
            side = 1;

        // recurse down the children, front side first
#if NODE_HAS_CHILDREN_POINTERS
    R_RecursiveWorldNode (node->children[side], clipflags);
#else
        R_RecursiveWorldNode(Mod_GetChildNode(node, side, _g->cl.worldmodel), clipflags);
#endif
        // draw stuff
        c = node->numsurfaces;

        if (c)
        {
#if !SEPARATE_BRUSH_MODEL_DATA
      surf = cl.worldmodel->surfaces + node->firstsurface;
#else
            surf = _g->cl.worldmodel->brushModelData->surfaces + node->firstsurface;
#endif
            if (dot < -BACKFACE_EPSILON)
            {
                do
                {
#if SURF_HAS_VISFRAME
          if ((surf->flags & SURF_PLANEBACK) && (surf->visframe == r_framecount))
#else
#if !SEPARATE_BRUSH_MODEL_DATA
                    int surfIndex = surf - cl.worldmodel->surfaces;
#else
                    int surfIndex = surf->surfIdx; //surf - cl.worldmodel->brushModelData->surfaces;
#endif
                    if ((surf->flags & SURF_PLANEBACK) && (_g->surfMarked[surfIndex / 32] & (1 << (surfIndex % 32))))
#endif
                    {
#if            (r_drawpolys) // note: false by default
            {
              if (r_worldpolysbacktofront)
              {
                if (numbtofpolys < MAX_BTOFPOLYS)
                {
                  pbtofpolys[numbtofpolys].clipflags =
                      clipflags;
                  pbtofpolys[numbtofpolys].psurf = surf;
                  numbtofpolys++;
                }
              }
              else
              {
                R_RenderPoly (surf, clipflags);
              }
            }
            #else
                        {
                            R_RenderFace(surf, clipflags);
                        }
#endif
                    }

                    surf++;
                }
                while (--c);
            }
            else if (dot > BACKFACE_EPSILON)
            {
                do
                {
#if SURF_HAS_VISFRAME
          if (!(surf->flags & SURF_PLANEBACK) && (surf->visframe == r_framecount))
#else
#if !SEPARATE_BRUSH_MODEL_DATA
                    int surfIndex = surf - cl.worldmodel->surfaces;
#else
                    int surfIndex = surf->surfIdx; //surf - cl.worldmodel->brushModelData->surfaces;
#endif
                    if (!(surf->flags & SURF_PLANEBACK) && (_g->surfMarked[surfIndex / 32] & (1 << (surfIndex % 32))))
#endif
                    {
#if (r_drawpolys) // false by default
            {
              if (r_worldpolysbacktofront)
              {
                if (numbtofpolys < MAX_BTOFPOLYS)
                {
                  pbtofpolys[numbtofpolys].clipflags =
                      clipflags;
                  pbtofpolys[numbtofpolys].psurf = surf;
                  numbtofpolys++;
                }
              }
              else
              {
                R_RenderPoly (surf, clipflags);
              }
            }
            #else
                        {
                            R_RenderFace(surf, clipflags);
                        }
#endif
                    }

                    surf++;
                }
                while (--c);
            }

            // all surfaces on the same node share the same sequence number
            _g->r_currentkey++;
        }

        // recurse down the back side
#if NODE_HAS_CHILDREN_POINTERS
    R_RecursiveWorldNode (node->children[!side], clipflags);
#else
        R_RecursiveWorldNode(Mod_GetChildNode(node, !side, _g->cl.worldmodel), clipflags);
#endif
    }
}

/*
 ================
 R_RenderWorld
 ================
 */
void R_RenderWorld(void)
{
    model_t *clmodel;

#if r_worldpolysbacktofront
  btofpoly_t  btofpolys[MAX_BTOFPOLYS];

  pbtofpolys = btofpolys;
#endif
    _g->currententity = &cl_entities[0];
    VectorCopy(_g->r_origin, _g->modelorg);
    clmodel = getEntityModel(_g->currententity);
#if !SEPARATE_BRUSH_MODEL_DATA
  r_pcurrentvertbase = clmodel->vertexes;
#else
    r_pcurrentvertbase = clmodel->brushModelData->vertexes;
#endif
    //
#if !SURF_HAS_VISFRAME
    uint32_t stackSurfMarked[(MAX_SURFACES + 31) / 32];
    fastMemclear32(stackSurfMarked, sizeof(stackSurfMarked) / 4);
    _g->surfMarked = stackSurfMarked;
#endif
    //
#if !SEPARATE_BRUSH_MODEL_DATA
  R_RecursiveWorldNode (clmodel->nodes, 15);
#else
    R_RecursiveWorldNode(clmodel->brushModelData->nodes, 15);
#endif
// if the driver wants the polygons back to front, play the visible ones back
// in that order
#if (r_worldpolysbacktofront)
  {
    for (int i=numbtofpolys-1 ; i>=0 ; i--)
    {
      R_RenderPoly (btofpolys[i].psurf, btofpolys[i].clipflags);
    }
  }
#endif
}

