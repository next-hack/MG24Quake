/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

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
#ifndef QUAKE_GLOBAL_DATA_H_
#define QUAKE_GLOBAL_DATA_H_
#include "r_local.h"
typedef struct
{
    void *pdest;
    short *pz;
    int count;
#if NO_MINIMIZE
    byte      *ptex;
    int       sfrac, tfrac;
  #else
    int s, t;
#endif
    int light, zi;
//    mtriangleOffsetData_t *mtod;
} spanpackage_t;

typedef struct
{
    int isflattop;
    int numleftedges;
    int *pleftedgevert0;
    int *pleftedgevert1;
    int *pleftedgevert2;
    int numrightedges;
    int *prightedgevert0;
    int *prightedgevert1;
    int *prightedgevert2;
} edgetable;

typedef byte pixel_t;

typedef struct
{
    int32_t fps10;
    // r_draw.c
    qboolean r_leftclipped, r_rightclipped;
    qboolean makeleftedge, makerightedge;
    qboolean r_nearzionly;
    qboolean r_lastvertvalid;
    int r_emitted;
    int r_ceilv1;
    float r_nearzi;
    float r_u1, r_v1, r_lzi1;
    mvertex_t r_leftenter, r_leftexit;
    mvertex_t r_rightenter, r_rightexit;
    medge_t *r_pedge;
#if CACHED_EDGES || NEW_CACHED_EDGES
  unsigned int  cacheoffset;
#endif
    clipplane_t view_clipplanes[4];

    // d_edge.c
    float scale_for_mip;
    int ubasestep, errorterm, erroradjustup, erroradjustdown;
    int vstartscan;
    vec3_t transformed_modelorg;

    // r_bsp.c

    //
    // current entity info
    //
    qboolean insubmodel;
    entity_t *currententity;
    vec3_t modelorg, base_modelorg;
    // modelorg is the viewpoint reletive to
    // the currently rendering entity
    vec3_t r_entorigin;  // the currently rendering entity in world
    // coordinates

    float entity_rotation[3][3];

    vec3_t r_worldmodelorg;

    int r_currentbkey;

    mvertex_t *pbverts;
    bedge_t *pbedges;
    int numbverts, numbedges;
#if !SURF_HAS_VISFRAME
    uint32_t *surfMarked;
#endif
    mvertex_t *pfrontenter, *pfrontexit;
    qboolean makeclippededge;

#if !BEDGE_HAS_NEXT_POINTERS
  bedge_t *sp_bedge;
  uint8_t *sp_nextBedgeIndexArray;
  #endif
#if !BEDGE_HAS_VERTEX_POINTERS
  mvertex_t *sp_bverts;
  #endif
    //
    // r_edge.c
    //
    //edge_t  *auxedges;

    espan_t *basespan_p;
#if !ESPANS_HAVE_V
    uint8_t *basespanV_p;
#endif
    edge_t *r_edges, *edge_p, *edge_max;
#if !EDGE_HAS_NEXTREMOVEIDX && !EDGE_POINTERS
    uint16_t *edgeNextRemoveIdx;
#endif
    surf_t *surfaces, *surface_p, *surf_max;
    surf_t *base_surf_p;
    // surfaces are generated in back to front order by the bsp, so if a surf
    // pointer is greater than another one, it should be drawn in front
    // surfaces[1] is the background, and is used as the active surface stack

#if STATIC_NEW_REMOVE_EDGES
      edge_t  *newedges[MAXHEIGHT];   // these might be indexes
      edge_t  *removeedges[MAXHEIGHT];    // these might be indexes
  #else
    edge_t **newedges;   // these might be indexes. Note these should be initialized to null
    edge_t **removeedges;    // these might be indexes. idem
#endif // STATIC_EDGES
    espan_t *span_p, *max_span_p;

    int r_currentkey;

    int current_iv;

    int edge_head_u_shift20, edge_tail_u_shift20;

    //static void (*pdrawfunc)(void);
    edge_t *edge_head;
    edge_t *edge_tail;
    edge_t *edge_aftertail;
    edge_t *edge_sentinel;

    float fv;
    //
    // r_main.c (not complete)
    edge_t *base_edge_p;
    refdef_t r_refdef;

    //
    // view origin
    //
    vec3_t vup, base_vup;
    vec3_t vpn, base_vpn;
    vec3_t vright, base_vright;
    vec3_t r_origin;
#if !VISLEAVES_IN_Z_BUFFER
    byte visleaves[MAX_MAP_LEAFS / 8];
    byte visnodes[MAX_MAP_NODES / 8];
#else
  byte *visleaves;
  byte *visnodes;
  #endif

#define ASYNCH_ALIAS_SINGLE_RENDERING 1
#if ASYNCH_ALIAS_SINGLE_RENDERING
    byte aliasPendingPixel;
#endif
    // d_vars.c (incomplete)
    float d_sdivzstepu, d_tdivzstepu, d_zistepu;
    float d_sdivzstepv, d_tdivzstepv, d_zistepv;
    float d_sdivzorigin, d_tdivzorigin, d_ziorigin;
    fixed16_t sadjust, tadjust, bbextents, bbextentt;
    // mix (New)
    uint16_t *edgeOwnwers;
    short *leafKey;
    short *d_pzbuffer;
    // chase.c
    vec3_t chase_pos;
    vec3_t chase_angles;
    vec3_t chase_dest;
    vec3_t chase_dest_angles;
    // cl_main.c:
    client_state_t cl;
    client_static_t cls;
    client_entity_t *client_entity_data;    //
    lightstyle_t *cl_lightstyle;
    dlight_t cl_dlights[MAX_DLIGHTS];
    int cl_numvisedicts;
#if POINTER_CL_VISEDICT
  entity_t    *cl_visedicts[MAX_VISEDICTS];       // this to be converted to index.
  #else
    short cl_visedicts[MAX_VISEDICTS];       // this to be converted to index.
#endif
    // cl_tent.c
    int num_temp_entities;
#if SEPARATE_TEMP_ENTITIES
  entity_t  cl_temp_entities[MAX_TEMP_ENTITIES];
  #endif

#if STATIC_TEMP_ENTITIES
  temp_entity_t cl_temp_entity_data[MAX_TEMP_ENTITIES];
  #endif
    beam_t cl_beams[MAX_BEAMS];

    sfx_t *cl_sfx_wizhit;
    sfx_t *cl_sfx_knighthit;
    sfx_t *cl_sfx_tink1;
    sfx_t *cl_sfx_ric1;
    sfx_t *cl_sfx_ric2;
    sfx_t *cl_sfx_ric3;
    sfx_t *cl_sfx_r_exp3;
    // d_vars.c

    pixel_t *cacheblock;
    uint16_t surfNum;
    int cachewidth;
    pixel_t *d_viewbuffer;

    union
    {
        struct
        {
#if ASYNCH_ALIAS_SINGLE_RENDERING
            uint16_t aliasPendingLight;
            uint16_t aliasRecursiveLight;
            uint8_t *aliasPendingAddress;
#endif
            // d_sprite:
            int sprite_height;
            int minindex, maxindex;
            struct sspan_s *sprite_spans;
            //
            // d_polyse.c
            //
            int r_p0[6], r_p1[6], r_p2[6];

            byte *d_pcolormap;

            int d_aflatcolor;
            int d_xdenom;

            const edgetable *pedgetable;
            // FIXME: some of these can become statics
#if NO_MINIMIZE
          int       a_sstepxfrac, a_tstepxfrac, r_lstepx, a_ststepxwhole;
          #else
            int a_sstepx, a_tstepx, r_lstepx;

#endif
            int r_sstepx, r_tstepx, r_lstepy, r_sstepy, r_tstepy;
            int r_zistepx, r_zistepy;
            int d_aspancount, d_countextrastep;

            spanpackage_t *a_spans;
            spanpackage_t *d_pedgespanpackage;
            int ystart;
            byte *d_pdest, *d_ptex;
            short *d_pz;
#if NO_MINIMIZE
          int           d_sfrac, d_tfrac;
          #else
            int d_s, d_t;
            mtriangleOffsetData_t *d_mtod;
            int d_trinum; // to init to 0?
#endif
            int d_light, d_zi;
#if NO_MINIMIZE
          int           d_ptexextrastep, d_sfracextrastep;
          #else
            int d_ptexextrastep_s16p16;
            int d_ptexextrastep_t16p16;
            int d_ptexbasestep_s16p16;
            int d_ptexbasestep_t16p16;
#endif
            int d_tfracextrastep, d_lightextrastep, d_pdestextrastep;
            int d_lightbasestep, d_pdestbasestep;
#if NO_MINIMIZE
          int  d_ptexbasestep;
          int           d_sfracbasestep, d_tfracbasestep;
          int   skinwidth;
          byte  *skinstart;
          #endif
            int d_ziextrastep, d_zibasestep;
            int d_pzextrastep, d_pzbasestep;
#if NO_MINIMIZE
          byte  *skintable[MAX_LBM_HEIGHT];
          #else
            byte *skinBuffer;
            int triNum;
#endif // NO_MINIMIZE
            // r_aclip.c
            finalvert_t aclip_fv[2][8];
            auxvert_t av[8];
            // r_alias.c
            mtriangle_t *ptriangles;
            affinetridesc_t r_affinetridesc;

            void *acolormap;  // FIXME: should go away

            trivertx_t *r_apverts;

            // TODO: these probably will go away with optimized rasterization
            mdl_t *pmdl;
            vec3_t r_plightvec;
            int r_ambientlight;
            float r_shadelight;
            aliashdr_t *paliashdr;
            finalvert_t *pfinalverts;
            auxvert_t *pauxverts;
            float ziscale;
            model_t *pmodel;

            vec3_t alias_forward, alias_right, alias_up;

            maliasskindesc_t *pskindesc;
            int originalSkinInInternalFlash;    // can be smaller
            int r_amodels_drawn;
            int a_skinwidth;
            int r_anumverts;

            float aliastransform[3][4];

        };
        //
        struct
        {
            int r_lightwidth;
            BLOCKLIGHT_TYPE blocklights[18 * 18];

        };

    };

} global_data_t;
extern global_data_t *const _g;
#if ASYNCH_ALIAS_SINGLE_RENDERING
static inline void flushAliasPendingPixel(void)
{
    if (_g->aliasPendingPixel)
    {
        _g->aliasPendingPixel = 0;
#if !WIN32
        uint8_t pix = interleavedSpiFlashGetAsynchReadByteDMA();
#else
    uint8_t pix = extMemGetDMAByte();
    #endif
        *_g->aliasPendingAddress = ((byte*) _g->acolormap)[pix + _g->aliasPendingLight];
    }
}
#else
static inline void flushAliasPendingPixel()
{

}
#endif

static inline void setNextSpan(espan_t *span, espan_t *next)
{
    if (next == NULL)
    {
#if SEPARATE_SPAN_NEXT
            int spanIndex = span - basespan_p;
            nextSpanIndexes_p[spanIndex] = 0;
        #else
        span->nextSpanIdx = 0;
#endif

    }
    else
    {
        int nextSpanIndex = next - _g->basespan_p;
#if SEPARATE_SPAN_NEXT
            int spanIndex = span - basespan_p;
            nextSpanIndexes_p[spanIndex] = nextSpanIndex;
        #else
        span->nextSpanIdx = nextSpanIndex;
#endif
    }
}
__attribute__ ((always_inline)) static inline espan_t* getNextSpan(espan_t *s, int verifyNull)
{
    /*   if (verifyNull && !s)
     {
     return NULL;
     }*/
#if SEPARATE_SPAN_NEXT
    int index = s - basespan_p;
    if (0 == index)
    {
        return NULL;
    }
    else
    {
        return basespan_p + nextSpanIndexes_p[index];
    }
#else
    if (verifyNull && 0 == s->nextSpanIdx)
        return NULL;
    return _g->basespan_p + s->nextSpanIdx;
#endif
}
static inline espan_t* getSurfSpans(surf_t *s, int verifyNull)
{
    if (verifyNull && !s->spansIdx)
        return NULL;
    else
        return s->spansIdx + _g->basespan_p;
}
static inline void setSurfSpans(surf_t *s, espan_t *span)
{
    if (NULL == span)
        s->spansIdx = 0;
    else
        s->spansIdx = span - _g->basespan_p;
}
#if !EDGE_POINTERS
//extern edge_t *base_edge_p;
//extern edge_t *r_edges;
#define implementEdgeSetterGetter(field) \
static inline void setEdge##field(edge_t * e, edge_t * field) \
{                                               \
    if (NULL == field)                          \
    {                                           \
        e->field##Idx = 0;                      \
    }                                           \
    else                                        \
    {                                           \
         e->field##Idx = field - _g->base_edge_p;   \
    }                                           \
}                                               \
static inline edge_t* getEdge##field(edge_t * e, int verifyNull)   \
{                                               \
    if (verifyNull && e->field##Idx == 0)                     \
    {                                           \
        return NULL;                               \
    }                                           \
    else                                        \
    {                                           \
         return _g->base_edge_p + e->field##Idx;       \
    }                                           \
}

implementEdgeSetterGetter(Next);
implementEdgeSetterGetter(Prev);
#if EDGE_HAS_NEXTREMOVEIDX
implementEdgeSetterGetter(NextRemove);
#else
static inline void setEdgeNextRemove(edge_t *e, edge_t *nextRemove)
{
    int edgeIndex = e - _g->base_edge_p;

    if (NULL == nextRemove)
    {
        _g->edgeNextRemoveIdx[edgeIndex] = 0;
    }
    else
    {
        int edgeRemove = nextRemove - _g->base_edge_p;
        _g->edgeNextRemoveIdx[edgeIndex] = edgeRemove;
    }
}
static inline edge_t* getEdgeNextRemove(edge_t *e, int verifyNull)
{
    int edgeIndex = e - _g->base_edge_p;
    if (verifyNull && _g->edgeNextRemoveIdx[edgeIndex] == 0)
    {
        return NULL;
    }
    else
    {
        return _g->base_edge_p + _g->edgeNextRemoveIdx[edgeIndex];
    }
}
#endif
#else
static inline edge_t* getEdgeNext(edge_t *e) {return e->next;}
static inline edge_t* getEdgePrev(edge_t *e) {return e->prev;}
static inline edge_t* getEdgeNextRemove(edge_t *e) {return e->nextremove;}
static inline void setEdgeNext(edge_t *e, edge_t *n) {e->next = n;}
static inline void setEdgePrev(edge_t *e, edge_t *p) {e->prev = p;}
static inline void setEdgeNextRemove(edge_t *e, edge_t *nr) {e->nextremove = nr;}

#endif
#define implementSurfSetterGetter(field) \
static inline void setSurf##field(surf_t * s, surf_t * field) \
{                                               \
    if (NULL == field)                          \
    {                                           \
        s->field##Idx = 0;                      \
    }                                           \
    else                                        \
    {                                           \
         s->field##Idx = field->surfIndex;       \
    }                                           \
}                                               \
static inline surf_t* getSurf##field(surf_t * s, int verifyNull)   \
{                                               \
    if (verifyNull && s->field##Idx == 0)                     \
    {                                           \
        return NULL;                               \
    }                                           \
    else                                        \
    {                                           \
         return _g->base_surf_p + s->field##Idx;    \
    }                                           \
}
//implementSurfSetterGetter(Prev);
implementSurfSetterGetter(Next);
// r_misc
static inline void TransformVector(vec3_t in, vec3_t out)
{
    out[0] = DotProduct(in, _g->vright);
    out[1] = DotProduct(in, _g->vup);
    out[2] = DotProduct(in, _g->vpn);
}
//
extern uint8_t textureCacheBuffer[MAX_TEXTURE_SIZE];        // for surface rendering and edges.
static inline void* getTextureCacheBuffer()
{
    return textureCacheBuffer;
}
static inline int isNodeVisible(mnode_t *node)
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
//        checkNodeIndex(index, -1, __LINE__);
        if ((_g->visleaves[index >> 3] & (1 << (index & 7))))
            return 1;
    }
    return 0;
}
#endif /* QUAKE_GLOBAL_DATA_H_ */
