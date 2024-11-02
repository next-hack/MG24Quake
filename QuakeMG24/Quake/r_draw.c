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

// r_draw.c

#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"	// FIXME: shouldn't need to include this
#define MAXLEFTCLIPEDGES		100

// !!! if these are changed, they must be changed in asm_draw.h too !!!
#if NEW_CACHED_EDGES
    #define FULLY_CLIPPED_CACHED	0x8000
    #define FRAMECOUNT_MASK			0x7FFF
    #define CACHED_VALID_FRAME      1
#else
    #define FULLY_CLIPPED_CACHED	0x80000000
    #define FRAMECOUNT_MASK			0x7FFFFFFF
#endif // NEW_CACHED_EDGES

#if COUNT_FACE_CLIP
int			c_faceclip;					// number of faces clipped. Added only if COUNT_FACECLIP is non 0
#endif

//medge_t			*r_pedge;

#if RUNTIME_TABLES
int		sintable[SIN_BUFFER_SIZE];
byte	intsintable[SIN_BUFFER_SIZE];
#else
const int sintable[SIN_BUFFER_SIZE] =
{
    0x00080000, 0x0008647d, 0x0008c8bd, 0x00092c80, 0x00098f8b, 0x0009f19f, 0x000a5280, 0x000ab1f3,
    0x000b0fbc, 0x000b6ba1, 0x000bc56b, 0x000c1ce1, 0x000c71ce, 0x000cc3fd, 0x000d133c, 0x000d5f5a,
    0x000da827, 0x000ded77, 0x000e2f1f, 0x000e6cf7, 0x000ea6d9, 0x000edca0, 0x000f0e2c, 0x000f3b5e,
    0x000f641a, 0x000f8848, 0x000fa7d0, 0x000fc29f, 0x000fd8a5, 0x000fe9d5, 0x000ff623, 0x000ffd88,
    0x000fffff, 0x000ffd88, 0x000ff623, 0x000fe9d5, 0x000fd8a6, 0x000fc29f, 0x000fa7d0, 0x000f8848,
    0x000f641b, 0x000f3b5f, 0x000f0e2d, 0x000edca1, 0x000ea6da, 0x000e6cf8, 0x000e2f20, 0x000ded78,
    0x000da828, 0x000d5f5b, 0x000d133d, 0x000cc3fe, 0x000c71cf, 0x000c1ce2, 0x000bc56c, 0x000b6ba3,
    0x000b0fbd, 0x000ab1f4, 0x000a5281, 0x0009f1a0, 0x00098f8c, 0x00092c82, 0x0008c8be, 0x0008647e,
    0x00080001, 0x00079b83, 0x00073744, 0x0006d380, 0x00067075, 0x00060e61, 0x0005ad80, 0x00054e0e,
    0x0004f045, 0x0004945f, 0x00043a95, 0x0003e31f, 0x00038e32, 0x00033c03, 0x0002ecc4, 0x0002a0a6,
    0x000257d9, 0x00021289, 0x0001d0e1, 0x00019309, 0x00015927, 0x00012360, 0x0000f1d4, 0x0000c4a2,
    0x00009be5, 0x000077b8, 0x00005830, 0x00003d60, 0x0000275a, 0x0000162a, 0x000009dc, 0x00000277,
    0x00000000, 0x00000277, 0x000009dc, 0x0000162a, 0x00002759, 0x00003d5f, 0x0000582f, 0x000077b6,
    0x00009be4, 0x0000c4a0, 0x0000f1d2, 0x0001235d, 0x00015925, 0x00019306, 0x0001d0de, 0x00021286,
    0x000257d6, 0x0002a0a3, 0x0002ecc1, 0x00033bff, 0x00038e2f, 0x0003e31b, 0x00043a92, 0x0004945b,
    0x0004f041, 0x00054e0a, 0x0005ad7c, 0x00060e5d, 0x00067071, 0x0006d37c, 0x00073740, 0x00079b7f,
    0x0007fffd, 0x0008647a, 0x0008c8ba, 0x00092c7e, 0x00098f88, 0x0009f19c, 0x000a527d, 0x000ab1f0,
    0x000b0fb9, 0x000b6b9f, 0x000bc569, 0x000c1cdf, 0x000c71cc, 0x000cc3fb, 0x000d133a, 0x000d5f57,
    0x000da825, 0x000ded75, 0x000e2f1e, 0x000e6cf6, 0x000ea6d7, 0x000edc9f, 0x000f0e2b, 0x000f3b5d,
    0x000f6419, 0x000f8847, 0x000fa7cf, 0x000fc29e, 0x000fd8a5, 0x000fe9d4, 0x000ff623, 0x000ffd88,
    0x000fffff, 0x000ffd88, 0x000ff623, 0x000fe9d5, 0x000fd8a6, 0x000fc2a0, 0x000fa7d1, 0x000f8849,
    0x000f641c, 0x000f3b60, 0x000f0e2e, 0x000edca2, 0x000ea6db, 0x000e6cfa, 0x000e2f22, 0x000ded7a,
    0x000da82a, 0x000d5f5d, 0x000d133f, 0x000cc401, 0x000c71d2, 0x000c1ce5, 0x000bc56f, 0x000b6ba5,
    0x000b0fc0, 0x000ab1f7, 0x000a5284, 0x0009f1a3, 0x00098f8f, 0x00092c85, 0x0008c8c1, 0x00086481,
    0x00080004, 0x00079b86, 0x00073746, 0x0006d383, 0x00067078, 0x00060e64, 0x0005ad83, 0x00054e10,
    0x0004f047, 0x00049461, 0x00043a98, 0x0003e321, 0x00038e34, 0x00033c05, 0x0002ecc6, 0x0002a0a9,
    0x000257db, 0x0002128b, 0x0001d0e2, 0x0001930a, 0x00015929, 0x00012361, 0x0000f1d5, 0x0000c4a3,
    0x00009be6, 0x000077b9, 0x00005831, 0x00003d61, 0x0000275a, 0x0000162b, 0x000009dd, 0x00000277,
    0x00000000, 0x00000277, 0x000009dc, 0x00001629, 0x00002759, 0x00003d5f, 0x0000582e, 0x000077b6,
    0x00009be3, 0x0000c49f, 0x0000f1d0, 0x0001235c, 0x00015923, 0x00019304, 0x0001d0dc, 0x00021284,
    0x000257d4, 0x0002a0a1, 0x0002ecbf, 0x00033bfd, 0x00038e2c, 0x0003e319, 0x00043a8f, 0x00049459,
    0x0004f03e, 0x00054e07, 0x0005ad7a, 0x00060e5b, 0x0006706f, 0x0006d379, 0x0007373d, 0x00079b7c,
    0x0007fffa, 0x00086478, 0x0008c8b7, 0x00092c7b, 0x00098f85, 0x0009f19a, 0x000a527b, 0x000ab1ed,
    0x000b0fb7, 0x000b6b9c, 0x000bc566, 0x000c1cdc, 0x000c71c9, 0x000cc3f9, 0x000d1338, 0x000d5f55,
    0x000da823, 0x000ded73, 0x000e2f1c, 0x000e6cf4, 0x000ea6d6, 0x000edc9d, 0x000f0e29, 0x000f3b5c,
    0x000f6418, 0x000f8846, 0x000fa7ce, 0x000fc29e, 0x000fd8a4, 0x000fe9d4, 0x000ff622, 0x000ffd88,
    0x000fffff, 0x000ffd88, 0x000ff624, 0x000fe9d6, 0x000fd8a7, 0x000fc2a1, 0x000fa7d2, 0x000f884a,
    0x000f641d, 0x000f3b61, 0x000f0e2f, 0x000edca4, 0x000ea6dd, 0x000e6cfb, 0x000e2f24, 0x000ded7c,
    0x000da82c, 0x000d5f5f, 0x000d1341, 0x000cc403, 0x000c71d4, 0x000c1ce7, 0x000bc571, 0x000b6ba8,
    0x000b0fc2, 0x000ab1f9, 0x000a5287, 0x0009f1a6, 0x00098f92, 0x00092c87, 0x0008c8c4, 0x00086484,
    0x00080006, 0x00079b89, 0x00073749, 0x0006d385, 0x0006707b, 0x00060e67, 0x0005ad86, 0x00054e13,
    0x0004f04a, 0x00049464, 0x00043a9a, 0x0003e324, 0x00038e37, 0x00033c07, 0x0002ecc8, 0x0002a0ab,
    0x000257dd, 0x0002128d, 0x0001d0e4, 0x0001930c, 0x0001592a, 0x00012362, 0x0000f1d6, 0x0000c4a4,
    0x00009be7, 0x000077ba, 0x00005831, 0x00003d62, 0x0000275b, 0x0000162b, 0x000009dd, 0x00000277,
    0x00000000, 0x00000277, 0x000009db, 0x00001629, 0x00002758, 0x00003d5e, 0x0000582d, 0x000077b5,
    0x00009be2, 0x0000c49d, 0x0000f1cf, 0x0001235b, 0x00015922, 0x00019303, 0x0001d0da, 0x00021282,
    0x000257d2, 0x0002a09f, 0x0002ecbc, 0x00033bfb, 0x00038e2a, 0x0003e317, 0x00043a8d, 0x00049456,
    0x0004f03c, 0x00054e04, 0x0005ad77, 0x00060e58, 0x0006706c, 0x0006d376, 0x0007373a, 0x00079b7a,
    0x0007fff7, 0x00086475, 0x0008c8b4, 0x00092c78, 0x00098f83, 0x0009f197, 0x000a5278, 0x000ab1eb,
    0x000b0fb4, 0x000b6b9a, 0x000bc564, 0x000c1cda, 0x000c71c7, 0x000cc3f7, 0x000d1336, 0x000d5f53,
    0x000da821, 0x000ded71, 0x000e2f1a, 0x000e6cf2, 0x000ea6d4, 0x000edc9c, 0x000f0e28, 0x000f3b5a,
    0x000f6417, 0x000f8845, 0x000fa7cd, 0x000fc29d, 0x000fd8a4, 0x000fe9d4, 0x000ff622, 0x000ffd88,
    0x000fffff, 0x000ffd88, 0x000ff624, 0x000fe9d6, 0x000fd8a7, 0x000fc2a1, 0x000fa7d2, 0x000f884b,
    0x000f641e, 0x000f3b62, 0x000f0e31, 0x000edca5, 0x000ea6de, 0x000e6cfd, 0x000e2f26, 0x000ded7e,
    0x000da82e, 0x000d5f61, 0x000d1344, 0x000cc405, 0x000c71d6, 0x000c1cea, 0x000bc574, 0x000b6baa,
    0x000b0fc5, 0x000ab1fc, 0x000a5289, 0x0009f1a8, 0x00098f94, 0x00092c8a, 0x0008c8c6, 0x00086487,
};
const byte intsintable[SIN_BUFFER_SIZE] =
{
    0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
};
#endif

typedef struct
{
    float u, v;
    int ceilv;
} evert_t;

#if NEW_CACHED_EDGES
#if WIN32 && 0
uint16_t goffsets[40000];
#endif
#define SINGLE_CACHED_EDGE_BUFFER 0
static inline uint16_t *getCachedEdgeOffsetBuffer(int index)
{
    #if SINGLE_CACHED_EDGE_BUFFER
        return (uint16_t *) getTextureCacheBuffer() + index;
    #else
        if (index <(MAX_TEXTURE_SIZE / 2))
        {
            return (uint16_t *) getTextureCacheBuffer() + index;
        }
        else
        {
            uint16_t *off= (uint16_t*) (( (uint8_t *)d_zbuffer +  4 * ((MAX_MAP_NODES + 31) / 32) + 12 * ((MAX_MAP_LEAFS + 31) / 32)));
            return off + index - (MAX_TEXTURE_SIZE / 2);
        }
    #endif
}

void clearCachedEdgeOffsets(void)
{
    #if SINGLE_CACHED_EDGE_BUFFER
        fastMemclear32(getCachedEdgeOffsetBuffer(0), (MAX_MAP_EDGES) / 2);
    #else
        fastMemclear32(getTextureCacheBuffer(0), MAX_TEXTURE_SIZE / 4);
        fastMemclear32(getCachedEdgeOffsetBuffer(MAX_TEXTURE_SIZE / 2), (MAX_MAP_EDGES - MAX_TEXTURE_SIZE / 2 ) / 2 );
    #endif
}
static inline uint16_t getMedgeIndex(medge_t *edge)
{
    int index = edge - &_g->cl.worldmodel->brushModelData->edges[0];
    // printf("Index %d. In submodel %d\r\n", index, _g->insubmodel);
    return index;
}
static inline void setCachedEdgeOffset(medge_t *edge, unsigned int offset)
{
    if (_g->insubmodel)
        return;
    int index = getMedgeIndex(edge);
#if WIN32 && 0
    uint16_t *offsets = goffsets;
#else
    uint16_t *offsets = getCachedEdgeOffsetBuffer(index);
#endif
    *offsets = offset;
}
static inline uint16_t getCachedEdgeOffset(medge_t *edge)
{
    //if (_g->insubmodel)
    //     return FRAMECOUNT_MASK;
    int index = getMedgeIndex(edge);
    uint16_t *offsets = getCachedEdgeOffsetBuffer(index);
    return *offsets;
}
#endif // NEW_CACHED_EDGES

#if	!id386

/*
 ================
 R_EmitEdge
 ================
 */
static inline void R_EmitEdge(mvertex_t *pv0, mvertex_t *pv1)
{

    edge_t *edge, *pcheck;
    int u_check;
    float u, u_step;
    vec3_t local, transformed;
    float *world;
    int v, v2, ceilv0;
    float scale, lzi0, u0, v0;
    int side;

    if (_g->r_lastvertvalid)
    {
        u0 = _g->r_u1;
        v0 = _g->r_v1;
        lzi0 = _g->r_lzi1;
        ceilv0 = _g->r_ceilv1;
    }
    else
    {
        world = &pv0->position[0];

        // transform and project
        VectorSubtract(world, _g->modelorg, local);
        TransformVector(local, transformed);

        if (transformed[2] < NEAR_CLIP)
            transformed[2] = NEAR_CLIP;

        lzi0 = 1.0f / transformed[2];

        // FIXME: build x/yscale into transform?
        scale = xscale * lzi0;
        u0 = (xcenter + scale * transformed[0]);
        if (u0 < _g->r_refdef.fvrectx_adj)
            u0 = _g->r_refdef.fvrectx_adj;
        if (u0 > _g->r_refdef.fvrectright_adj)
            u0 = _g->r_refdef.fvrectright_adj;

        scale = yscale * lzi0;
        v0 = (ycenter - scale * transformed[1]);
        if (v0 < _g->r_refdef.fvrecty_adj)
            v0 = _g->r_refdef.fvrecty_adj;
        if (v0 > _g->r_refdef.fvrectbottom_adj)
            v0 = _g->r_refdef.fvrectbottom_adj;

        ceilv0 = (int) ceilf_m(v0);
    }

    world = &pv1->position[0];

// transform and project
    VectorSubtract(world, _g->modelorg, local);
    TransformVector(local, transformed);

    if (transformed[2] < NEAR_CLIP)
        transformed[2] = NEAR_CLIP;

    _g->r_lzi1 = 1.0f / transformed[2];

    scale = xscale * _g->r_lzi1;
    _g->r_u1 = (xcenter + scale * transformed[0]);
    if (_g->r_u1 < _g->r_refdef.fvrectx_adj)
        _g->r_u1 = _g->r_refdef.fvrectx_adj;
    if (_g->r_u1 > _g->r_refdef.fvrectright_adj)
        _g->r_u1 = _g->r_refdef.fvrectright_adj;

    scale = yscale * _g->r_lzi1;
    _g->r_v1 = (ycenter - scale * transformed[1]);
    if (_g->r_v1 < _g->r_refdef.fvrecty_adj)
        _g->r_v1 = _g->r_refdef.fvrecty_adj;
    if (_g->r_v1 > _g->r_refdef.fvrectbottom_adj)
        _g->r_v1 = _g->r_refdef.fvrectbottom_adj;

    if (_g->r_lzi1 > lzi0)
        lzi0 = _g->r_lzi1;

    if (lzi0 > _g->r_nearzi)	// for mipmap finding
        _g->r_nearzi = lzi0;

// for right edges, all we want is the effect on 1/z
    if (_g->r_nearzionly)
        return;

    _g->r_emitted = 1;

    _g->r_ceilv1 = (int) ceilf_m(_g->r_v1);

// create the edge
    if (ceilv0 == _g->r_ceilv1)
    {
        // we cache unclipped horizontal edges as fully clipped
#if CACHED_EDGES
		if (cacheoffset != 0x7FFFFFFF)
		{
			cacheoffset = FULLY_CLIPPED_CACHED |
					(r_framecount & FRAMECOUNT_MASK);
		}
#elif NEW_CACHED_EDGES
        if (_g->cacheoffset != 0x7FFF)
        {
            _g->cacheoffset = FULLY_CLIPPED_CACHED | CACHED_VALID_FRAME;  // actually we clear all data before, so we don't have to use frame, 1 is ok
        }

#endif
        return;		// horizontal edge
    }

    side = ceilv0 > _g->r_ceilv1;

    edge = _g->edge_p++;
#if CACHED_EDGES
	edge->owner = r_pedge;
#elif NEW_CACHED_EDGES
    _g->edgeOwnwers[edge - _g->base_edge_p] = getMedgeIndex(_g->r_pedge);
#endif
    setEdgeNearzi(edge, lzi0);

    if (side == 0)
    {
        // trailing edge (go from p1 to p2)
        v = ceilv0;
        v2 = _g->r_ceilv1 - 1;
#if EDGE_SURF_ARRAY
		edge->surfs[0] = surface_p - surfaces;
		edge->surfs[1] = 0;
#else
#if PROFILE_DIVISIONS
        divisionForPointers++;
#endif
        edge->surf0 = _g->surface_p->surfIndex;
        edge->surf1 = 0;
#endif
        u_step = ((_g->r_u1 - u0) / (_g->r_v1 - v0));
        u = u0 + ((float) v - v0) * u_step;
    }
    else
    {
        // leading edge (go from p2 to p1)
        v2 = ceilv0 - 1;
        v = _g->r_ceilv1;

#if EDGE_SURF_ARRAY
		edge->surfs[0] = 0;
		edge->surfs[1] = surface_p - surfaces;
#else
        edge->surf0 = 0;
        edge->surf1 = _g->surface_p->surfIndex;
#endif

        u_step = ((u0 - _g->r_u1) / (v0 - _g->r_v1));
        u = _g->r_u1 + ((float) v - _g->r_v1) * u_step;
    }

    edge->u_step = u_step * 0x100000;
    edge->u = u * 0x100000 + 0xFFFFF;

// we need to do this to avoid stepping off the edges if a very nearly
// horizontal edge is less than epsilon above a scan, and numeric error causes
// it to incorrectly extend to the scan, and the extension of the line goes off
// the edge of the screen
// FIXME: is this actually needed?
    if (edge->u < _g->r_refdef.vrect_x_adj_shift20)
        edge->u = _g->r_refdef.vrect_x_adj_shift20;
    if (edge->u > _g->r_refdef.vrectright_adj_shift20)
        edge->u = _g->r_refdef.vrectright_adj_shift20;

//
// sort the edge in normally
//
    u_check = edge->u;
#if EDGE_SURF_ARRAY
	if (edge->surfs[0])
#else
    if (edge->surf0)
#endif

        u_check++;	// sort trailers after leaders
    edge_t **newedges = _g->newedges;
    if (!newedges[v] || newedges[v]->u >= u_check)
    {
#if EDGE_POINTERS
		edge->next = newedges[v];

#else
        setEdgeNext(edge, newedges[v]);
#endif
        newedges[v] = edge;
    }
    else
    {
        pcheck = newedges[v];
#if EDGE_POINTERS
		while (pcheck->next && pcheck->next->u < u_check)
			pcheck = pcheck->next;
		edge->next = pcheck->next;
		pcheck->next = edge;
#else
        edge_t *edges = _g->base_edge_p;
        while (pcheck->NextIdx && edges[pcheck->NextIdx].u < u_check)
            pcheck = &edges[pcheck->NextIdx];
        setEdgeNext(edge, getEdgeNext(pcheck, 0));  // warning: is it ok not checking for null?
        // edge guaranteed not null.
//		setEdgeNext(pcheck, edge);
        pcheck->NextIdx = edge - edges;
#endif
    }
#if EDGE_POINTERS
	edge->nextremove = _g->removeedges[v2];
#else
    setEdgeNextRemove(edge, _g->removeedges[v2]);
#endif
    _g->removeedges[v2] = edge;
}

/*
 ================
 R_ClipEdge
 ================
 */
void R_ClipEdge(mvertex_t *pv0, mvertex_t *pv1, clipplane_t *clip)
{
    float f;
#define OPTIMIZE 1
#if CLIP_PLANE_USES_FLOAT
    float d0, d1;
#else
    int d0, d1;
#endif
    mvertex_t clipvert;

    if (clip)
    {
        do
        {

#if CLIP_PLANE_USES_FLOAT
#define FASTER_WAY 1
#if FASTER_WAY
            d0 = DotProduct(pv0->position, clip->normal);
            d1 = DotProduct(pv1->position, clip->normal);
#else
      d0 = DotProduct (pv0->position, clip->normal) - clip->dist;
      d1 = DotProduct (pv1->position, clip->normal) - clip->dist;

#endif
#else
			d0 = DotProduct (pv0->position, clip->frac_normal) - clip->frac_dist;
			d1 = DotProduct (pv1->position, clip->frac_normal) - clip->frac_dist;
#endif
#if FASTER_WAY
            if (d0 >= clip->dist)
            {
                // point 0 is unclipped
                if (d1 >= clip->dist)
                {
                    // both points are unclipped
                    continue;
                }

                // only point 1 is clipped
#if CACHED_EDGES || NEW_CACHED_EDGES
                // we don't cache clipped edges
                _g->cacheoffset = FRAMECOUNT_MASK; // WAS 0x7FFFFFFF;
#endif
                f = (float) (d0 - clip->dist) / (d0 - d1);
#else
	      if (d0 >= 0)
	      {
	      // point 0 is unclipped
	        if (d1 >= 0)
	        {
	        // both points are unclipped
	          continue;
	        }

	      // only point 1 is clipped
	#if CACHED_EDGES || NEW_CACHED_EDGES
	      // we don't cache clipped edges
	        cacheoffset = FRAMECOUNT_MASK ; // WAS 0x7FFFFFFF;
	#endif
	        f = (float) d0 / (d0 - d1);

#endif
#if !OPTIMIZE
        // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
        clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
        clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
        clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif

                if (clip->leftedge)
                {
                    _g->r_leftclipped = true;
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
#if OPTIMIZE
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                    _g->r_leftexit = clipvert;
                }
                else if (clip->rightedge)
                {
                    _g->r_rightclipped = true;
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
#if OPTIMIZE
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                    _g->r_rightexit = clipvert;
                }
                else
                {
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
#if OPTIMIZE
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                }

                R_ClipEdge(pv0, &clipvert, clip->next);
                return;
            }
            else
            {
                // point 0 is clipped
#if FASTER_WAY
                if (d1 < clip->dist)
#else
	        if (d1 < 0)
#endif
                {
                    // both points are clipped
                    // we do cache fully clipped edges
#if CACHED_EDGES
					if (!r_leftclipped)
						cacheoffset = FULLY_CLIPPED_CACHED |
								(r_framecount & FRAMECOUNT_MASK);
#elif NEW_CACHED_EDGES
                    if (!_g->r_leftclipped)
                        _g->cacheoffset = FULLY_CLIPPED_CACHED | CACHED_VALID_FRAME; // don't need to use frame. 1 is fine because we memclear everything

#endif
                    return;
                }
#if FASTER_WAY
                f = (float) (d0 - clip->dist) / (d0 - d1);
#else
        f = (float) d0 / (d0 - d1);
#endif
                // only point 0 is clipped
                _g->r_lastvertvalid = false;
#if CACHED_EDGES || NEW_CACHED_EDGES
                // we don't cache partially clipped edges
                _g->cacheoffset = FRAMECOUNT_MASK;  // was 0x7FFFFFFF
#endif
#if !OPTIMIZE
        clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
        clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
        clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                if (clip->leftedge)
                {
                    _g->r_leftclipped = true;
#if OPTIMIZE
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                    _g->r_leftenter = clipvert;
                }
                else if (clip->rightedge)
                {
                    _g->r_rightclipped = true;
#if OPTIMIZE
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                    _g->r_rightenter = clipvert;
                }
                else
                {
#if OPTIMIZE
                    // next-hack: moved here so hopefully the compiler will emit some non fp instructions after vdiv
                    clipvert.position[0] = pv0->position[0] + f * (pv1->position[0] - pv0->position[0]);
                    clipvert.position[1] = pv0->position[1] + f * (pv1->position[1] - pv0->position[1]);
                    clipvert.position[2] = pv0->position[2] + f * (pv1->position[2] - pv0->position[2]);
#endif
                }

                R_ClipEdge(&clipvert, pv1, clip->next);
                return;
            }
        }
        while ((clip = clip->next) != NULL);
    }

// add the edge
    R_EmitEdge(pv0, pv1);
}

#endif	// !id386

/*
 ================
 R_EmitCachedEdge
 ================
 */
#if CACHED_EDGES
void R_EmitCachedEdge (void)
{
	edge_t		*pedge_t;

	pedge_t = (edge_t *)((unsigned long)r_edges + r_pedge->cachededgeoffset);
#if EDGE_SURF_ARRAY
	if (!pedge_t->surfs[0])
		pedge_t->surfs[0] = surface_p - surfaces;
	else
		pedge_t->surfs[1] = surface_p - surfaces;
#else
	if (!pedge_t->surf0)
		pedge_t->surf0 = surface_p - surfaces;
	else
		pedge_t->surf1 = surface_p - surfaces;
#endif
	if (getEdgeNearzi(pedge_t) > r_nearzi)	// for mipmap finding
		r_nearzi = getEdgeNearzi(pedge_t);

	r_emitted = 1;
}
#elif NEW_CACHED_EDGES
static inline void R_EmitCachedEdge(void)
{
    edge_t *pedge_t;
    uint32_t index = getCachedEdgeOffset(_g->r_pedge);
#if WIN32
	if (index >= 0x7FFF)
    FIXME("ERROR");
   // printf("Cached offset: %d\r\n", getCachedEdgeOffset(_g->r_pedge));
#endif
    pedge_t = _g->base_edge_p + index;
#if EDGE_SURF_ARRAY
	if (!pedge_t->surfs[0])
		pedge_t->surfs[0] = surface_p - surfaces;
	else
		pedge_t->surfs[1] = surface_p - surfaces;
#else
    if (!pedge_t->surf0)
        pedge_t->surf0 = _g->surface_p->surfIndex;
    else
        pedge_t->surf1 = _g->surface_p->surfIndex;
#endif
    if (getEdgeNearzi(pedge_t) > _g->r_nearzi)	// for mipmap finding
        _g->r_nearzi = getEdgeNearzi(pedge_t);

    _g->r_emitted = 1;
}

#endif

/*
 ================
 R_RenderFace
 ================
 */
void R_RenderFace(msurface_t *fa, int clipflags)
{
    //printf("World number of medges %d\r\n", cl_entities[0].model->numedges); // max is 14770
    int i, lindex;
    unsigned mask;
    mplane_t *pplane;
    float distinv;
    vec3_t p_normal;
    medge_t *pedges, tedge;
    clipplane_t *pclip;

// skip out if no more surfs
    if ((_g->surface_p) >= _g->surf_max)
    {
        r_outofsurfaces++;
#if WIN32
		printf("OUT OF SURFACES");
#endif
        return;
    }
#if CACHED_EDGES

	static int maxEdgeSeen = 0;
	if (edge_p - r_edges > maxEdgeSeen)
    {
        maxEdgeSeen = edge_p - r_edges;
    }
#endif
// ditto if not enough edges left, or switch to auxedges if possible
    if ((_g->edge_p + fa->numedges + 4) >= _g->edge_max)
    {
#if WIN32
	  r_outofedges += fa->numedges;
		printf("OUT OF EDGES");
#endif
        return;
    }
#if COUNT_FACE_CLIP
	c_faceclip++;
#endif
// set up clip planes
    pclip = NULL;

    for (i = 3, mask = 0x08; i >= 0; i--, mask >>= 1)
    {
        if (clipflags & mask)
        {
            _g->view_clipplanes[i].next = pclip;
            pclip = &_g->view_clipplanes[i];
        }
    }

// push the edges through
    _g->r_emitted = 0;
    _g->r_nearzi = 0;
    _g->r_nearzionly = false;
    _g->makeleftedge = _g->makerightedge = false;
#if !SEPARATE_BRUSH_MODEL_DATA
  pedges = currententity->model->edges;
#else
    brush_model_data_t *currentBmd = getEntityModel(_g->currententity)->brushModelData;
    pedges = currentBmd->edges;
#endif
    _g->r_lastvertvalid = false;

    int numedeges = fa->numedges;
    short *surfedges = &currentBmd->surfedges[fa->firstedge];
    for (i = 0; i < numedeges; i++)
    {
#if !SEPARATE_BRUSH_MODEL_DATA
    lindex = currententity->model->surfedges[fa->firstedge + i];
#else
//    lindex = currentBmd->surfedges[fa->firstedge + i];
        lindex = *surfedges++;
#endif
        if (lindex > 0)
        {
            _g->r_pedge = &pedges[lindex];

#if CACHED_EDGES
		// if the edge is cached, we can just reuse the edge
			if (!insubmodel)
			{
               if (currententity != &cl_entities[0])
                    while(1) {printf("CE: %p cle %p\r\n",currententity, &cl_entities[0]); FIXME("ERROOOOOOOOOOOR");}

				if (r_pedge->cachededgeoffset & FULLY_CLIPPED_CACHED)
				{
					if ((r_pedge->cachededgeoffset & FRAMECOUNT_MASK) ==
						r_framecount)
					{
						r_lastvertvalid = false;
						continue;
					}
				}
				else
				{
					if ((((unsigned long)edge_p - (unsigned long)r_edges) >
						 r_pedge->cachededgeoffset) &&
						(((edge_t *)((unsigned long)r_edges +
						 r_pedge->cachededgeoffset))->owner == r_pedge))
					{
						R_EmitCachedEdge ();
						r_lastvertvalid = false;
						continue;
					}
				}
			}
#elif NEW_CACHED_EDGES
            // if the edge is cached, we can just reuse the edge
            if (!_g->insubmodel)
            {
                int cachededgeoffset = getCachedEdgeOffset(_g->r_pedge);
                if (cachededgeoffset & FULLY_CLIPPED_CACHED)
                {
                    if ((cachededgeoffset & FRAMECOUNT_MASK) == CACHED_VALID_FRAME)
                    {
                        _g->r_lastvertvalid = false;
                        continue;
                    }
                }
                else
                {
                    // it's cached if the cached edge is valid and is owned
                    // by this medge_t
                    if ((_g->edge_p - _g->base_edge_p) > cachededgeoffset && _g->edgeOwnwers[cachededgeoffset] == getMedgeIndex(_g->r_pedge))
                    {
                        R_EmitCachedEdge();
                        _g->r_lastvertvalid = false;
                        continue;
                    }
                }
            }
#endif

            // assume it's cacheable
#if CACHED_EDGES
			cacheoffset = (byte *)edge_p - (byte *)r_edges;
#elif NEW_CACHED_EDGES
            _g->cacheoffset = _g->edge_p - _g->base_edge_p;
#endif

            _g->r_leftclipped = _g->r_rightclipped = false;
            R_ClipEdge(&r_pcurrentvertbase[_g->r_pedge->v[0]], &r_pcurrentvertbase[_g->r_pedge->v[1]], pclip);
#if CACHED_EDGES
			r_pedge->cachededgeoffset = cacheoffset;
#elif NEW_CACHED_EDGES
//            printf("CACHE OFFSET: %d\r\n", cacheoffset);
            setCachedEdgeOffset(_g->r_pedge, _g->cacheoffset);
#endif
            if (_g->r_leftclipped)
                _g->makeleftedge = true;
            if (_g->r_rightclipped)
                _g->makerightedge = true;
            _g->r_lastvertvalid = true;
        }
        else
        {
            lindex = -lindex;
            _g->r_pedge = &pedges[lindex];
#if CACHED_EDGES
		// if the edge is cached, we can just reuse the edge
			if (!insubmodel)
			{
               if (currententity != &cl_entities[0])
                    while(1) {printf("CE: %p cle %p\r\n",currententity, &cl_entities[0]); FIXME("ERROOOOOOOOOOOR");}

				if (r_pedge->cachededgeoffset & FULLY_CLIPPED_CACHED)
				{
					if ((r_pedge->cachededgeoffset & FRAMECOUNT_MASK) ==
						r_framecount)
					{
						r_lastvertvalid = false;
						continue;
					}
				}
				else
				{
				// it's cached if the cached edge is valid and is owned
				// by this medge_t
					if ((((unsigned long)edge_p - (unsigned long)r_edges) >
						 r_pedge->cachededgeoffset) &&
						(((edge_t *)((unsigned long)r_edges +
						 r_pedge->cachededgeoffset))->owner == r_pedge))
					{
						R_EmitCachedEdge ();
						r_lastvertvalid = false;
						continue;
					}
				}
			}
#elif NEW_CACHED_EDGES
            // if the edge is cached, we can just reuse the edge
            if (!_g->insubmodel)
            {
                int cachededgeoffset = getCachedEdgeOffset(_g->r_pedge);
                if (cachededgeoffset & FULLY_CLIPPED_CACHED)
                {
                    if ((cachededgeoffset & FRAMECOUNT_MASK) == CACHED_VALID_FRAME)
                    {
                        _g->r_lastvertvalid = false;
                        continue;
                    }
                }
                else
                {
                    // it's cached if the cached edge is valid and is owned
                    // by this medge_t
                    if ((_g->edge_p - _g->base_edge_p) > cachededgeoffset && _g->edgeOwnwers[cachededgeoffset] == getMedgeIndex(_g->r_pedge))
                    {
                        R_EmitCachedEdge();
                        _g->r_lastvertvalid = false;
                        continue;
                    }
                }
            }
#endif
            // assume it's cacheable
#if CACHED_EDGES
			cacheoffset = (byte *)edge_p - (byte *)r_edges;
#elif NEW_CACHED_EDGES
            _g->cacheoffset = _g->edge_p - _g->base_edge_p;
#endif
            _g->r_leftclipped = _g->r_rightclipped = false;
            R_ClipEdge(&r_pcurrentvertbase[_g->r_pedge->v[1]], &r_pcurrentvertbase[_g->r_pedge->v[0]], pclip);
#if CACHED_EDGES
			r_pedge->cachededgeoffset = cacheoffset;
#elif NEW_CACHED_EDGES
            setCachedEdgeOffset(_g->r_pedge, _g->cacheoffset);
#endif
            if (_g->r_leftclipped)
                _g->makeleftedge = true;
            if (_g->r_rightclipped)
                _g->makerightedge = true;
            _g->r_lastvertvalid = true;
        }
    }

// if there was a clip off the left edge, add that edge too
// FIXME: faster to do in screen space?
// FIXME: share clipped edges?
    if (_g->makeleftedge)
    {
        _g->r_pedge = &tedge;
        _g->r_lastvertvalid = false;
        R_ClipEdge(&_g->r_leftexit, &_g->r_leftenter, pclip->next);
    }

// if there was a clip off the right edge, get the right r_nearzi
    if (_g->makerightedge)
    {
        _g->r_pedge = &tedge;
        _g->r_lastvertvalid = false;
        _g->r_nearzionly = true;
        R_ClipEdge(&_g->r_rightexit, &_g->r_rightenter, _g->view_clipplanes[1].next);
    }

// if no edges made it out, return without posting the surface
    if (!_g->r_emitted)
        return;
#if WIN32 && PROFILE_SPEED
	r_polycount++;
#endif
    _g->surface_p->data = (void*) fa;
    //surface_p->nearzi = r_nearzi;
#if SURF_INT_NEARZI
	setSurfNearzi(surface_p, r_nearzi);
#else
#if MSURFACE_HAS_TEXINFO_POINTER
    setSurfMiplevel(_g->surface_p, D_MipLevelForScale(_g->r_nearzi * _g->scale_for_mip * ((msurface_t*) _g->surface_p->data)->texinfo->mipadjust));
#else
    setSurfMiplevel(_g->surface_p, D_MipLevelForScale (_g->r_nearzi * _g->scale_for_mip * getMsurfaceTexinfo((msurface_t*) _g->surface_p->data)->mipadjust));
#endif
#endif
//	surface_p->flags = fa->flags;
    _g->surface_p->insubmodel = _g->insubmodel;
    _g->surface_p->spanstate = 0;
#if SURF_HAS_ENTITY_POINTER
	surface_p->entity = currententity;
#else
    setSurfEntity(_g->surface_p, _g->currententity);
#endif
    _g->surface_p->key = _g->r_currentkey++;
#if OLD_SPAN_METHOD
	surface_p->spans = NULL;
#else
    setSurfSpans(_g->surface_p, NULL);
#endif
#if SURF_HAS_D_ZI_DATA
#if TEST_D_ZI_DATA
//    printf("Mo: %f %f %f\r\n", modelorg[0], modelorg[1], modelorg[2]);
    vec3_t tempPnormal;
    float *tempModelOrg;
    tempModelOrg = modelorg;
    mplane_t *tempPlane = ((msurface_t*) surface_p->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	float temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;
	surface_p->d_zistepu = temp_d_zistepu;
	surface_p->d_zistepv = temp_d_zistepv;
	surface_p->d_ziorigin = temp_d_ziorigin;

#else
#if MSURFACE_HAS_PLANE_POINTER
    pplane = fa->plane;
#else
    pplane = getMsurfacePlane(fa);
#endif
    TransformVector(pplane->normal, p_normal);
    distinv = 1.0f / (getPlaneDist(pplane) - DotProduct(_g->modelorg, pplane->normal));
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
    _g->surface_p->d_zistepu = p_normal[0] * xscaleinv * distinv;
    _g->surface_p->d_zistepv = -p_normal[1] * yscaleinv * distinv;
    _g->surface_p->d_ziorigin = p_normal[2] * distinv - xcenter * _g->surface_p->d_zistepu - ycenter * _g->surface_p->d_zistepv;
#else
    float d_zistepu = p_normal[0] * xscaleinv * distinv;
	setSurfD_zistepu(_g->surface_p, d_zistepu);
	float d_zistepv = -p_normal[1] * yscaleinv * distinv;
	setSurfD_zistepv(_g->surface_p, d_zistepv);
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
	setSurfD_ziorigin(_g->surface_p, p_normal[2] * distinv -	xcenter * d_zistepu - ycenter * d_zistepv);
#else
	surface_p->d_ziorigin = p_normal[2] * distinv -	xcenter * d_zistepu - ycenter * d_zistepv;
#endif
#endif

#if 0
    static float maxAbsd_zistepu = 0;
    static float maxAbsd_zistepv = 0;
    static float maxAbsd_ziorigin  = 0;
    if (fabs(surface_p->d_zistepu) >= maxAbsd_zistepu)
    {
        maxAbsd_zistepu = fabs(surface_p->d_zistepu);
    }
    if (fabs(surface_p->d_zistepv) >= maxAbsd_zistepv)
    {
        maxAbsd_zistepv = fabs(surface_p->d_zistepv);
    }
    if (fabs(surface_p->d_ziorigin ) >= maxAbsd_ziorigin )
    {
        maxAbsd_ziorigin  = fabs(surface_p->d_ziorigin );
    }
    printf("stepu %f, stepv %f, orig %f\r\n", maxAbsd_zistepu, maxAbsd_zistepv, maxAbsd_ziorigin);
#endif
#endif

#endif
//JDC	VectorCopy (r_worldmodelorg, surface_p->modelorg);
    _g->surface_p++;
}

/*
 ================
 R_RenderBmodelFace
 ================
 */
#if !BEDGE_HAS_NEXT_POINTERS
extern bedge_t *getBedgeNext(bedge_t *pb);
#endif
#if !BEDGE_HAS_VERTEX_POINTERS
extern mvertex_t *getBedgeV(bedge_t *pb, int index);
#endif
void R_RenderBmodelFace(bedge_t *pedges, msurface_t *psurf)
{
    int i;
    unsigned mask;
    mplane_t *pplane;
    float distinv;
    vec3_t p_normal;
    medge_t tedge;
    clipplane_t *pclip;

// skip out if no more surfs
    if (_g->surface_p >= _g->surf_max)
    {
        r_outofsurfaces++;
#if WIN32
        printf("OUT OF SURFACES BRUSH MODEL");
#endif
        return;
    }

// ditto if not enough edges left, or switch to auxedges if possible
    if ((_g->edge_p + psurf->numedges + 4) >= _g->edge_max)
    {
        r_outofedges += psurf->numedges;
#if WIN32
        printf("OUT OF EDGES FOR BRUSH MODEL");
#endif
        return;
    }
#if COUNT_FACE_CLIP
	c_faceclip++;
#endif
// this is a dummy to give the caching mechanism someplace to write to
    _g->r_pedge = &tedge;

// set up clip planes
    pclip = NULL;

    for (i = 3, mask = 0x08; i >= 0; i--, mask >>= 1)
    {
        if (r_clipflags & mask)
        {
            _g->view_clipplanes[i].next = pclip;
            pclip = &_g->view_clipplanes[i];
        }
    }

// push the edges through
    _g->r_emitted = 0;
    _g->r_nearzi = 0;
    _g->r_nearzionly = false;
    _g->makeleftedge = _g->makerightedge = false;
// FIXME: keep clipped bmodel edges in clockwise order so last vertex caching
// can be used?
    _g->r_lastvertvalid = false;
#if BEDGE_HAS_NEXT_POINTERS
    for (; pedges; pedges = pedges->pnext)
#else
	for ( ; pedges ; pedges = getBedgeNext(pedges))
#endif
    {
        _g->r_leftclipped = _g->r_rightclipped = false;
#if BEDGE_HAS_VERTEX_POINTERS
        R_ClipEdge(pedges->v[0], pedges->v[1], pclip);
#else
		R_ClipEdge (getBedgeV(pedges, 0), getBedgeV(pedges, 1), pclip);
#endif
        if (_g->r_leftclipped)
            _g->makeleftedge = true;
        if (_g->r_rightclipped)
            _g->makerightedge = true;
    }

// if there was a clip off the left edge, add that edge too
// FIXME: faster to do in screen space?
// FIXME: share clipped edges?
    if (_g->makeleftedge)
    {
        _g->r_pedge = &tedge;
        R_ClipEdge(&_g->r_leftexit, &_g->r_leftenter, pclip->next);
    }

// if there was a clip off the right edge, get the right r_nearzi
    if (_g->makerightedge)
    {
        _g->r_pedge = &tedge;
        _g->r_nearzionly = true;
        R_ClipEdge(&_g->r_rightexit, &_g->r_rightenter, _g->view_clipplanes[1].next);
    }

// if no edges made it out, return without posting the surface
    if (!_g->r_emitted)
        return;
#if WIN32 && PROFILE_SPEED
	r_polycount++;
#endif
    _g->surface_p->data = (void*) psurf;
//	surface_p->nearzi = r_nearzi;

#if SURF_INT_NEARZI
	setSurfNearzi(surface_p, r_nearzi);
#else
#if MSURFACE_HAS_TEXINFO_POINTER
    setSurfMiplevel(_g->surface_p, D_MipLevelForScale(_g->r_nearzi * _g->scale_for_mip * ((msurface_t*) _g->surface_p->data)->texinfo->mipadjust));
#else
    setSurfMiplevel(_g->surface_p, D_MipLevelForScale (_g->r_nearzi * _g->scale_for_mip * getMsurfaceTexinfo((msurface_t*) _g->surface_p->data)->mipadjust));
#endif
#endif
//	surface_p->flags = psurf->flags;
    _g->surface_p->insubmodel = true;
    _g->surface_p->spanstate = 0;
#if SURF_HAS_ENTITY_POINTER
	surface_p->entity = currententity;
#else
    setSurfEntity(_g->surface_p, _g->currententity);
#endif
#if 0
	if (_g->r_currentbkey < 0 || r_currentbkey > MAX_SURFACE_KEY)
    {
        printf("Exceeded surface key: 0x%x (%d)\r\n", r_currentbkey, r_currentbkey);
        FIXME("Insufficient surface key");
    }
#endif
    _g->surface_p->key = _g->r_currentbkey;
//	printf("r_currentbkey: %d\r\n", r_currentbkey);
#if OLD_SPAN_METHOD
	surface_p->spans = NULL;
#else
    setSurfSpans(_g->surface_p, NULL);
#endif
#if SURF_HAS_D_ZI_DATA
//printf("BMo: %f %f %f ent %p\r\n", modelorg[0], modelorg[1], modelorg[2], surface_p->entity);
#if MSURFACE_HAS_PLANE_POINTER
    pplane = psurf->plane;
#else
    pplane = getMsurfacePlane(psurf);
#endif
// FIXME: cache this?
    TransformVector(pplane->normal, p_normal);
// FIXME: cache this?
    distinv = 1.0f / (getPlaneDist(pplane) - DotProduct(_g->modelorg, pplane->normal));

#if !SURF_HAS_FIXED_D_ZISTEP_DATA
    _g->surface_p->d_zistepu = p_normal[0] * xscaleinv * distinv;
    _g->surface_p->d_zistepv = -p_normal[1] * yscaleinv * distinv;
    _g->surface_p->d_ziorigin = p_normal[2] * distinv - xcenter * _g->surface_p->d_zistepu - ycenter * _g->surface_p->d_zistepv;
#else
    float d_zistepu = p_normal[0] * xscaleinv * distinv;
	setSurfD_zistepu(_g->surface_p, d_zistepu);
	float d_zistepv = -p_normal[1] * yscaleinv * distinv;
	setSurfD_zistepv(_g->surface_p, d_zistepv);
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
	setSurfD_ziorigin(_g->surface_p, p_normal[2] * distinv -	xcenter * d_zistepu - ycenter * d_zistepv);
#else
	surface_p->d_ziorigin = p_normal[2] * distinv -	xcenter * d_zistepu - ycenter * d_zistepv;
#endif
#endif
#if 0
    static float maxAbsd_zistepu = 0;
    static float maxAbsd_zistepv = 0;
    static float maxAbsd_ziorigin  = 0;
    if (fabs(surface_p->d_zistepu) >= maxAbsd_zistepu)
    {
        maxAbsd_zistepu = fabs(surface_p->d_zistepu);
    }
    if (fabs(surface_p->d_zistepv) >= maxAbsd_zistepv)
    {
        maxAbsd_zistepv = fabs(surface_p->d_zistepv);
    }
    if (fabs(surface_p->d_ziorigin ) >= maxAbsd_ziorigin )
    {
        maxAbsd_ziorigin  = fabs(surface_p->d_ziorigin );
    }
    printf("brush stepu %f, stepv %f, orig %f\r\n", maxAbsd_zistepu, maxAbsd_zistepv, maxAbsd_ziorigin);
#endif
#endif
//JDC	VectorCopy (r_worldmodelorg, surface_p->modelorg);
    _g->surface_p++;
}

/*
 ================
 R_RenderPoly
 ================
 */
#if (r_drawpolys || r_drawculledpolys)
void R_RenderPoly (msurface_t *fa, int clipflags)
{
	int			i, lindex, lnumverts, s_axis, t_axis;
	float		dist, lastdist, lzi, scale, u, v, frac;
	unsigned	mask;
	vec3_t		local, transformed;
	clipplane_t	*pclip;
	medge_t		*pedges;
	mplane_t	*pplane;
	mvertex_t	verts[2][100];	//FIXME: do real number
	polyvert_t	pverts[100];	//FIXME: do real number, safely
	int			vertpage, newverts, newpage, lastvert;
	qboolean	visible;

// FIXME: clean this up and make it faster
// FIXME: guard against running out of vertices

	s_axis = t_axis = 0;	// keep compiler happy

// set up clip planes
	pclip = NULL;

	for (i=3, mask = 0x08 ; i>=0 ; i--, mask >>= 1)
	{
		if (clipflags & mask)
		{
			view_clipplanes[i].next = pclip;
			pclip = &view_clipplanes[i];
		}
	}

// reconstruct the polygon
// FIXME: these should be precalculated and loaded off disk
	pedges = currententity->model->edges;
	lnumverts = fa->numedges;
	vertpage = 0;

	for (i=0 ; i<lnumverts ; i++)
	{
		lindex = currententity->model->surfedges[fa->firstedge + i];

		if (lindex > 0)
		{
			r_pedge = &pedges[lindex];
			verts[0][i] = r_pcurrentvertbase[r_pedge->v[0]];
		}
		else
		{
			r_pedge = &pedges[-lindex];
			verts[0][i] = r_pcurrentvertbase[r_pedge->v[1]];
		}
	}

// clip the polygon, done if not visible
	while (pclip)
	{
		lastvert = lnumverts - 1;
		lastdist = DotProduct (verts[vertpage][lastvert].position,
							   pclip->normal) - pclip->dist;

		visible = false;
		newverts = 0;
		newpage = vertpage ^ 1;

		for (i=0 ; i<lnumverts ; i++)
		{
			dist = DotProduct (verts[vertpage][i].position, pclip->normal) -
					pclip->dist;

			if ((lastdist > 0) != (dist > 0))
			{
				frac = dist / (dist - lastdist);
				verts[newpage][newverts].position[0] =
						verts[vertpage][i].position[0] +
						((verts[vertpage][lastvert].position[0] -
						  verts[vertpage][i].position[0]) * frac);
				verts[newpage][newverts].position[1] =
						verts[vertpage][i].position[1] +
						((verts[vertpage][lastvert].position[1] -
						  verts[vertpage][i].position[1]) * frac);
				verts[newpage][newverts].position[2] =
						verts[vertpage][i].position[2] +
						((verts[vertpage][lastvert].position[2] -
						  verts[vertpage][i].position[2]) * frac);
				newverts++;
			}

			if (dist >= 0)
			{
				verts[newpage][newverts] = verts[vertpage][i];
				newverts++;
				visible = true;
			}

			lastvert = i;
			lastdist = dist;
		}

		if (!visible || (newverts < 3))
			return;

		lnumverts = newverts;
		vertpage ^= 1;
		pclip = pclip->next;
	}

// transform and project, remembering the z values at the vertices and
// r_nearzi, and extract the s and t coordinates at the vertices
	pplane = fa->plane;
	switch (pplane->type)
	{
	case PLANE_X:
	case PLANE_ANYX:
		s_axis = 1;
		t_axis = 2;
		break;
	case PLANE_Y:
	case PLANE_ANYY:
		s_axis = 0;
		t_axis = 2;
		break;
	case PLANE_Z:
	case PLANE_ANYZ:
		s_axis = 0;
		t_axis = 1;
		break;
	}

	r_nearzi = 0;

	for (i=0 ; i<lnumverts ; i++)
	{
	// transform and project
		VectorSubtract (verts[vertpage][i].position, modelorg, local);
		TransformVector (local, transformed);

		if (transformed[2] < NEAR_CLIP)
			transformed[2] = NEAR_CLIP;

		lzi = 1.0 / transformed[2];

		if (lzi > r_nearzi)	// for mipmap finding
			r_nearzi = lzi;

	// FIXME: build x/yscale into transform?
		scale = xscale * lzi;
		u = (xcenter + scale*transformed[0]);
		if (u < _g->r_refdef.fvrectx_adj)
			u = _g->r_refdef.fvrectx_adj;
		if (u > _g->r_refdef.fvrectright_adj)
			u = _g->r_refdef.fvrectright_adj;

		scale = yscale * lzi;
		v = (ycenter - scale*transformed[1]);
		if (v < _g->r_refdef.fvrecty_adj)
			v = _g->r_refdef.fvrecty_adj;
		if (v > _g->r_refdef.fvrectbottom_adj)
			v = _g->r_refdef.fvrectbottom_adj;

		pverts[i].u = u;
		pverts[i].v = v;
		pverts[i].zi = lzi;
		pverts[i].s = verts[vertpage][i].position[s_axis];
		pverts[i].t = verts[vertpage][i].position[t_axis];
	}

// build the polygon descriptor, including fa, r_nearzi, and u, v, s, t, and z
// for each vertex
	r_polydesc.numverts = lnumverts;
	r_polydesc.nearzi = r_nearzi;
	r_polydesc.pcurrentface = fa;
	r_polydesc.pverts = pverts;

// draw the polygon
	D_DrawPoly ();
}

/*
================
R_ZDrawSubmodelPolys
================
*/
void R_ZDrawSubmodelPolys (model_t *pmodel)
{
	int			i, numsurfaces;
	msurface_t	*psurf;
	float		dot;
	mplane_t	*pplane;

	psurf = &pmodel->surfaces[pmodel->firstmodelsurface];
	numsurfaces = pmodel->nummodelsurfaces;

	for (i=0 ; i<numsurfaces ; i++, psurf++)
	{
	// find which side of the node we are on
		pplane = psurf->plane;

		dot = DotProduct (modelorg, pplane->normal) - pplane->dist;

	// draw the polygon
		if (((psurf->flags & SURF_PLANEBACK) && (dot < -BACKFACE_EPSILON)) ||
			(!(psurf->flags & SURF_PLANEBACK) && (dot > BACKFACE_EPSILON)))
		{
		// FIXME: use bounding-box-based frustum clipping info?
			R_RenderPoly (psurf, 15);
		}
	}
}

#endif
