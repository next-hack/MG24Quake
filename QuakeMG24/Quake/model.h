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
#ifndef __MODEL__
#define __MODEL__
#include "modelgen.h"
#include "spritegn.h"
#define MARK_NODE_IN_SURFACE 1
#define MTRIANGLE_HAS_OFFSET_DATA 0
/*

 d*_t structures are on-disk representations
 m*_t structures are in-memory

 */

/*
 ==============================================================================

 BRUSH MODELS

 ==============================================================================
 */

//
// in memory representation
//
// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct
{
    vec3_t position;
} mvertex_t;

#define	SIDE_FRONT	0
#define	SIDE_BACK	1
#define	SIDE_ON		2

// plane_t structure
// !!! if this is changed, it must be changed in asm_i386.h too !!!
#define PLANE_DIST_PRECISION 8
typedef struct mplane_s
{
#define PLANE_HAS_FLOAT_NORMAL 1
#if PLANE_HAS_FLOAT_NORMAL
    vec3_t normal;
#else
	short	fract_normal[3];
#endif
#if PLANE_HAS_FLOAT_DIST
	float	dist;
	// note: these two below: can be byte to have good alignment or can be as small as 4 bits.

	byte	type;			// for texture axis selection and fast side tests
	byte	signbits;		// signx + signy<<1 + signz<<1
#else
    int32_t fixed_dist :24;   // was float
    // note: these two below: can be byte to have good alignment or can be as small as 4 bits.
    int32_t type :4;			// for texture axis selection and fast side tests
    int32_t signbits :4;		// signx + signy<<1 + signz<<1
#endif
} mplane_t;
static inline float getPlaneDist(mplane_t *plane)
{
#if PLANE_HAS_FLOAT_DIST
    return plane->dist;
#else
    return plane->fixed_dist * (float) (1.0f / (1 << PLANE_DIST_PRECISION));
#endif
}
static inline void setPlaneDist(mplane_t *plane, float dist)
{
#if PLANE_HAS_FLOAT_DIST
    plane->dist = dist;
#else
    plane->fixed_dist = dist * (1 << PLANE_DIST_PRECISION);
#endif
}

#define TEXTURE_HAS_POINTER_TO_EXTMEM 1
typedef struct texture_s
{
#if NO_MINIMIZE
	char		name[16];
	unsigned	width, height;
	int			anim_total;				// total tenths in sequence ( 0 = no)
	int			anim_min, anim_max;		// time for this frame min <=time< max
	struct texture_s *anim_next;		// in the animation sequence
	struct texture_s *alternate_anims;	// bmodels in frame 1 use these
	unsigned	offsets[MIPLEVELS];		// four mip maps stored
	#else
#if TEXTURE_HAS_NAME
	char		name[16];
	unsigned int	width : 12, height : 12;

#else
    unsigned int width :10;
    unsigned int height :10;
    unsigned int isSky :1;
    unsigned int isTurbulent :1;
#endif
    unsigned int anim_total :10;				// total tenths in sequence ( 0 = no)
    int alternate_anim_ofs :24;
    int anim_min :8, anim_max :8;		// time for this frame min <=time< max. WAS SHORT
#define TEXTURE_HAS_ANIM_POINTERS 0
#if TEXTURE_HAS_ANIM_POINTERS
	struct texture_s *anim_next;		// in the animation sequence
	struct texture_s *alternate_anims;	// bmodels in frame 1 use these
#else
    int anim_next_ofs :24;
#endif
#if !TEXTURE_HAS_POINTER_TO_EXTMEM
	unsigned short	offsets[MIPLEVELS];		// four mip maps stored
#else
    uint8_t *extmemdata[MIPLEVELS];		// four mip maps stored
#endif
#endif
} texture_t;

#define	SURF_PLANEBACK	1	// 2
#define	SURF_DRAWSKY	  2 //4
#define SURF_DRAWSPRITE	4 // 8
#define SURF_DRAWTURB	  8 //0x10
#define SURF_DRAWTILED	16 //  0x20
#define SURF_DRAWBACKGROUND 32	//  1  //0x40

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct
{
    unsigned short v[2];
#if CACHED_EDGES
	unsigned int	cachededgeoffset;
#endif
} medge_t;

typedef struct
{
    float vecs[2][4];
    texture_t *texture;
    unsigned int mipadjust :3; // 1...4
    unsigned int reduced_flags :1;
} mtexinfo_t;
#define FASTER_MSURFACE_T 1
#if FASTER_MSURFACE_T
#define MSURFACE_HAS_PLANE_POINTER 1
#define MSURFACE_HAS_TEXINFO_POINTER 1
#define MSURFACE_HAS_LIGHT_SAMPLE_POINTER  1

typedef struct msurface_s
{

#define MSURFACE_USES_MODEL_IDX 0
#if MSURFACE_USES_MODEL_IDX
    uint32_t            modelIdx : 8;
#endif
    uint32_t flags :8;          // was int
    int32_t numedges :8; // are backwards edges
#if MSURFACE_HAS_LIGHT_SAMPLE_POINTER
    byte *samples;
#else
    uint32_t            samplesIdx : 16;            // [numstyles*surfsize]
#endif

#if MSURFACE_HAS_TEXINFO_POINTER
    mtexinfo_t *texinfo;
#else
    uint16_t            texinfoIdx;
#endif
#if MSURFACE_HAS_PLANE_POINTER
    mplane_t *plane;
#else
    int16_t            planeIdx;
#endif
    uint16_t surfIdx;
    int16_t firstedge;  // look up in model->surfedges[], negative numbers

// surface generation data
    short texturemins[2]; // probably smaller is ok: turbulent has -8192
    short extents[2];     // idem                    turbulent has 16384

// lighting info
    byte styles[MAXLIGHTMAPS];

} msurface_t;

#else
typedef struct msurface_s
{
#if NO_MINIMIZE
 	int			visframe;		// should be drawn when node is crossed

	int			dlightframe;
	int			dlightbits;

	mplane_t	*plane;
	int			flags;

	int			firstedge;	// look up in model->surfedges[], negative numbers
	int			numedges;	// are backwards edges

// surface generation data
	struct surfcache_s	*cachespots[MIPLEVELS];

	short		texturemins[2];
	short		extents[2];

	mtexinfo_t	*texinfo;

// lighting info
	byte		styles[MAXLIGHTMAPS];
	byte		*samples;		// [numstyles*surfsize]
	#else
#if SURF_HAS_VISFRAME
 	int			visframe;		// should be drawn when node is crossed
#endif
#if USING_R_DLIGHTFRAMECOUNT
	int			dlightframe;
#endif
#if !MARK_NODE_IN_SURFACE
	int			dlightbits;     // this to be put in a RAM
#endif
#warning: we could optimize by putting here the model ptr (actually index) and then reference the plane, text info and samples from there.

	#define MSURFACE_HAS_MODEL_IDX 1
    uint32_t            modelIdx : 8;
	uint32_t			flags : 6;          // was int
// optimized from int
	int32_t		    numedges : 6;	// are backwards edges
    uint32_t            planeIdx : 12;
    uint16_t            surfIdx;
    int16_t            firstedge : 16;	// look up in model->surfedges[], negative numbers
    uint16_t            samplesIdx;            // [numstyles*surfsize]
    uint16_t            texinfoIdx;



// surface generation data
#if SURF_CACHE
	struct surfcache_s	*cachespots[MIPLEVELS];
#endif
	short		texturemins[2]; // probably smaller is ok: turbulent has -8192
	short		extents[2];     // idem                    turbulent has 16384


// lighting info
	byte		styles[MAXLIGHTMAPS];

	#endif
} msurface_t;
#endif
#if !OLDSTRUCTURE
#define NODE_HAS_PLANE_POINTER 1 // pointer and aligned structure saves a lot.
typedef struct mnode_s
{
// common with leaf
    int32_t contents :6;		// 0, to differentiate from leafs. Leaves from -1 to -14
    int32_t parent_idx :13;
    uint32_t node_idx :13;
#if USING_R_VISFRAMECOUNT
	int			visframe;		// node needs to be traversed if current
#endif
    short minmaxs[6];		// for bounding box culling
// node specific
#if NODE_HAS_PLANE_POINTER
    mplane_t *plane;
#else
	short plane_idx;
#endif
#define NODE_HAS_CHILDREN_POINTERS 0
#if NODE_HAS_CHILDREN_POINTERS
	struct mnode_s	*children[2];
#else
    short children_idx[2];              // note: node 0 should not be a children, right ?
#endif
    unsigned short firstsurface;
    unsigned short numsurfaces;
}
#if !NODE_HAS_PLANE_POINTER
__attribute__ ((packed)) mnode_t;
#else
mnode_t;
#endif
#if !NODE_HAS_PLANE_POINTER
#define disk_mnode_t mnode_t;
#else
typedef struct disk_mnode_s
{
// common with leaf
    int32_t contents :6;   // 0, to differentiate from leafs. Leaves from -1 to -14
    int32_t parent_idx :13;
    uint32_t node_idx :13;
    short minmaxs[6];   // for bounding box culling
// node specific
    short plane_idx;
    short children_idx[2];              // note: node 0 should not be a children, right ?
    unsigned short firstsurface;
    unsigned short numsurfaces;
} __attribute__ ((packed)) disk_mnode_t;
#endif

typedef struct mleaf_s
{
// common with node
    int32_t contents :6;		// will be a negative contents number -1 to -14
    int32_t parent_idx :13;
    int32_t leaf_idx :13;
#if USING_R_VISFRAMECOUNT
	int			visframe;		// node needs to be traversed if current
#endif
    short minmaxs[6];		// for bounding box culling
// leaf specific
#if LEAF_HAS_COMPRESSED_VIS_POINTER
	byte		*compressed_vis;
#else
    unsigned short compressed_vis_idx;
#endif
#if LEAF_HAS_EFRAGS
	efrag_t		*efrags;
#endif
#if LEAF_HAS_MARKSURFACES_POINTER
	msurface_t	**firstmarksurface;
#else
    short firstMarkSurfaceIdx;
#endif
    short nummarksurfaces;
    byte ambient_sound_level[NUM_AMBIENTS];
} mleaf_t;

#else
typedef struct mnode_s
{
// common with leaf
	int8_t			contents;		// 0, to differentiate from leafs. Leaves from -1 to -14
#if USING_R_VISFRAMECOUNT
	int			visframe;		// node needs to be traversed if current
#endif
	short		minmaxs[6];		// for bounding box culling
#if NODE_HAS_PARENT_POINTER
	struct mnode_s	*parent;
#else
    short parent_idx;
#endif
// node specific
#if NODE_HAS_PLANE_POINTER
	mplane_t	*plane;
#else
    short plane_idx;
#endif
#define NODE_HAS_CHILDREN_POINTERS 0
#if NODE_HAS_CHILDREN_POINTERS
	struct mnode_s	*children[2];
#else
    short children_idx[2];              // note: node 0 should not be a children, right ?
#endif
	unsigned short		firstsurface;
	unsigned short		numsurfaces;
} mnode_t;



typedef struct mleaf_s
{
// common with node
	int8_t			contents;		// will be a negative contents number -1 to -14
#if USING_R_VISFRAMECOUNT
	int			visframe;		// node needs to be traversed if current
#endif
	short		minmaxs[6];		// for bounding box culling
#if NODE_HAS_PARENT_POINTER
	struct mnode_s	*parent;
#else
    short parent_idx;
#endif
// leaf specific
#if LEAF_HAS_COMPRESSED_VIS_POINTER
	byte		*compressed_vis;
#else
    unsigned short compressed_vis_idx;
#endif
#if LEAF_HAS_EFRAGS
	efrag_t		*efrags;
#endif
#if LEAF_HAS_MARKSURFACES_POINTER
	msurface_t	**firstmarksurface;
#else
    short firstMarkSurfaceIdx;
#endif
	short			nummarksurfaces;
#define LEAF_HAS_KEY 0
#if LEAF_HAS_KEY
	short			key;			// BSP sequence number for leaf's contents
#else
    short dummy;
#endif
	byte		ambient_sound_level[NUM_AMBIENTS];
}  mleaf_t;
#endif
// !!! if this is changed, it must be changed in asm_i386.h too !!!
typedef struct
{
    dclipnode_t *clipnodes;
    mplane_t *planes;
    int firstclipnode;
    int lastclipnode;
    vec3_t clip_mins;
    vec3_t clip_maxs;
} hull_t;

/*
 ==============================================================================

 SPRITE MODELS

 ==============================================================================
 */

// FIXME: shorten these?
typedef struct mspriteframe_s
{
//	int		width;
//	int		height;
    short width;
    short height;
    //void	*pcachespot;			// remove?
    short up, down, left, right;      // were float :/
    byte *pixels;
} mspriteframe_t;

typedef struct
{
    int numframes;
    float *intervals;
    mspriteframe_t *frames[];
} mspritegroup_t;

typedef struct
{
    spriteframetype_t type;       // this is only a bit...
    mspriteframe_t *frameptr;
} mspriteframedesc_t;

typedef struct
{
    byte type;
    byte numframes;
    short maxwidth;
    short maxheight;
    short beamlength;		// remove?
    //void				*cachespot;		// remove?
    mspriteframedesc_t frames[];
} msprite_t;

/*
 ==============================================================================

 ALIAS MODELS

 Alias models are position independent, so the cache manager can move them.
 ==============================================================================
 */
#define MODELS_HAVE_ORIGINAL_SKIN_TOO 1

typedef struct
{
#if NO_MINIMIZE
	aliasframetype_t	type;
	trivertx_t			bboxmin;
	trivertx_t			bboxmax;
	int					frame;
	char				name[16];
	#else
    trivertx_t bboxmin;
    trivertx_t bboxmax;
    int type :1;
    int frame :31;   // this is actually an offset into mem
#endif
} maliasframedesc_t;

typedef struct
{
#if NO_MINIMIZE
	aliasskintype_t		type;
	void				*pcachespot;
	int					skin;
	#else
    unsigned int type :1;
    int skin :31;  // this is an offset into mem
    //void				*pcachespot;
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
    int originalSkin;
#endif
#endif

} maliasskindesc_t;

typedef struct
{
    trivertx_t bboxmin;
    trivertx_t bboxmax;
    int frame;                  // this is probably an offset
} maliasgroupframedesc_t;

typedef struct
{
#if NO_MINIMIZE
	int						numframes ;
	int						intervals;
	maliasgroupframedesc_t	frames[1];
	#else
    int numframes :9;
    int intervals :(32 - 9);     // offset into mem
    maliasgroupframedesc_t frames[];
#endif
} maliasgroup_t;

typedef struct
{
#if NO_MINIMIZE
	int					numskins;
	int					intervals;
	maliasskindesc_t	skindescs[1];
	#else
    int numskins :10;
    int intervals :22;         //offset into mem
    maliasskindesc_t skindescs[];

#endif
} maliasskingroup_t;

// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct mtriangle_s
{
#if NO_MINIMIZE
	int					facesfront;
	int					vertindex[3];
	#else
#if TRIANGLE_HAS_SENTINEL
	uint32_t           sentinel;
#endif
    /*
     uint16_t				facesfront : 1;
     uint32_t                triangleOffsetDataPos : 32;
     //int16_t		     		vertindex[3];
     int16_t                 vertindex0;
     int16_t                 vertindex1;
     int16_t                 vertindex2;*/
    uint32_t facesfront :1;
    uint32_t triangleSize :13;                  //
    uint32_t vertindex0 :9;  // max 350 vertex. 512 is fine
    uint32_t vertindex1 :9;
    uint32_t vertindex2 :9;
    uint32_t triangleOffsetDataPos :15;
    uint32_t triangleOffsetNumber :8;      //how many columns the triangle has.
#if MTRIANGLE_HAS_OFFSET_DATA
    uint16_t                    offsetS;
    uint16_t                    bufferOffset;
    uint32_t                    startOffset;
#endif
#endif
} mtriangle_t;
typedef struct
{
#if MTOD_HAS_SENTINEL
    uint32_t sentinel;          // TO BE REMOVED
#endif
#if !MTRIANGLE_HAS_OFFSET_DATA
    uint16_t offsetS;          // the real s is a positive integer. To select the column in offsetTable, we need to remove this value.
    uint16_t bufferOffset; // when we pass the buffer to retrieve the skin data, we need to subtract this value. This allows the offsetTable to be uint16_t instead of int32_t
    uint16_t startOffset;
#endif
    uint16_t offsets[1];
} mtriangleOffsetData_t;
typedef struct
{
    int extMemAddress;                // position in external memory.
    int model;          //offset into mem
    int stverts;        // offset into mem
    int skindesc;       // offset into mem
    int triangles;      // offset into mem
    maliasframedesc_t frames[];      // variable length
} aliashdr_t;
//
typedef struct
{
    int id;                // next-hack added to avoid changing too many things.
    int model;          //offset into mem
    int stverts;        // offset into mem
    int skindesc;       // offset into mem
    int triangles;      // offset into mem
    maliasframedesc_t frames[];  // variable length
} disk_aliashdr_t;

//===================================================================

//
// Whole model
//

typedef enum
{
    mod_brush, mod_sprite, mod_alias
} modtype_t;

#define	EF_ROCKET	1			// leave a trail
#define	EF_GRENADE	2			// leave a trail
#define	EF_GIB		4			// leave a trail
#define	EF_ROTATE	8			// rotate (bonus items)
#define	EF_TRACER	16			// green split trail
#define	EF_ZOMGIB	32			// small blood trail
#define	EF_TRACER2	64			// orange split trail + rotate
#define	EF_TRACER3	128			// purple trail

typedef struct
{
// the following to include a pointer to another struct.
//
// brush model
//

    short firstmodelsurface, nummodelsurfaces;
#if BRUSHMODELDATA_USES_NUMPLANES
	short			numplanes;
#endif
    short numleafs;		// number of visible leafs, not counting 0
#if BRUSHMODELDATA_HAS_NUMVERTEX
	short			numvertexes;
#endif
//	short			numedges;
    short numnodes;
//	short			numtexinfo;
    short numsurfaces;
//	short			numsurfedges;
//	short			numclipnodes;
//	short			nummarksurfaces;
//	short			numtextures;
    uint8_t numsubmodels; // this would be only for the worldmodel, but let's keep it here.
    //
//	dmodel_t	*submodels;     // not really used.

    mplane_t *planes;

    mleaf_t *leafs;

    mvertex_t *vertexes;

    medge_t *edges;

    mnode_t *nodes;

    mtexinfo_t *texinfo;

    msurface_t *surfaces;

#define SURF_EDGES_INT 0
#if SURF_EDGES_INT
	int			*surfedges;
    #else
    short *surfedges;

#endif
//	dclipnode_t	*clipnodes; // not used :O (these are used in hulls)

#if MODEL_HAS_MARKSURFACES_POINTER
	msurface_t	**marksurfaces;
#else
    short *marksurfaceIdx;
#endif

    hull_t hulls[MAX_MAP_HULLS];

    texture_t **textures;

    byte *visdata;
    byte *lightdata;
    char *entities;      // NOTE! THIS IS A POINTER TO EXTERNAL FLASH
#if MARK_NODE_IN_SURFACE
    short *surfNodeIndex;
#endif
} brush_model_data_t;
#define MAX_BRUSH_MODELS 150
extern brush_model_data_t brushModelData[MAX_BRUSH_MODELS];
#define MODEL_HAS_NAME_POINTER  1
typedef struct model_s
{
#if MODEL_HAS_NAME_POINTER
    char *name;
#else
	char		name[MAX_QPATH];     // next-hack: this to contain instead pointer to a pool of characters with many concatenated null terminated strings.
#endif
#if NO_MOD_OPTIMIZE
	qboolean	needload;		// bmodels and sprites don't cache normally.

	modtype_t	type;           // 2 bits.
	int			numframes;      // probably less that 256 frames?
	synctype_t	synctype;       // few bits

	int			flags;          // few bits.
#else
#if 0
    int32_t numframes : 8;
    uint32_t flags : 8;
    uint32_t needload : 2;      // note: NOT a qboolean! Damn you!
    uint32_t type :2 ;
    uint32_t synctype :1 ;
    // 4 + 8 bits more available
#else
    int8_t numframes;
    uint8_t flags;
    uint8_t type;
    uint8_t needload :2;      // note: NOT a qboolean! Damn you!
    uint8_t synctype :1;

#endif
#endif
//
// volume occupied by the model
//
#if MODEL_HAS_FLOAT_MINS_MAX
	vec3_t		mins, maxs;
#else
    short mins_s[3], maxs_s[3];
#endif
    float radius;

#if !SEPARATE_BRUSH_MODEL_DATA
#error we want to separate data!
    uint32_t brushModelDataIndex :8;

// the following to include a pointer to another struct.
//
// brush model
//
    short firstmodelsurface;
    short nummodelsurfaces;
    short numplanes;       // actually not really used...
    short numleafs;		// number of visible leafs, not counting 0
    short numvertexes;
    short numedges;
    short numnodes;
    short numtexinfo;
    short numsurfaces;
    short numsurfedges;
    short numclipnodes;
    short nummarksurfaces;
    short numtextures;
    short numsubmodels;
    //
    dmodel_t *submodels;

    mplane_t *planes;

    mleaf_t *leafs;

    mvertex_t *vertexes;

    medge_t *edges;

    mnode_t *nodes;

    mtexinfo_t *texinfo;

    msurface_t *surfaces;

#define SURF_EDGES_INT 0
#if SURF_EDGES_INT
	int			*surfedges;
    #else
    short *surfedges;

#endif
    dclipnode_t *clipnodes;

#if MODEL_HAS_MARKSURFACES_POINTER
	msurface_t	**marksurfaces;
#else
    short *marksurfaceIdx;
#endif

    hull_t hulls[MAX_MAP_HULLS];

    texture_t **textures;

    byte *visdata;
    byte *lightdata;
    char *entities;

//
// additional model data
//
#else
    //uint32_t brushModelDataIndex : 8;
    brush_model_data_t *brushModelData;
#endif
    //cache_user_t	cache;		// only access through Mod_Extradata
    void *data;
} model_t;

extern model_t *mod_known;
#if MSURFACE_USES_MODEL_IDX
#if !MSURFACE_HAS_PLANE_POINTER
__attribute__((always_inline))  static inline void setMsurfacePlane(msurface_t *s, mplane_t *p)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    s->planeIdx = p - mod_known[s->modelIdx].planes;
#else
#if MSURFACE_HAS_PLANE_POINTER
    s->plane = p;
 #else
    s->planeIdx = p - mod_known[s->modelIdx].brushModelData->planes;
#endif
#endif

}
__attribute__((always_inline))  static inline mplane_t* getMsurfacePlane(msurface_t *s)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    return mod_known[s->modelIdx].planes + s->planeIdx;
#else
#if MSURFACE_HAS_PLANE_POINTER
    return s->plane;
#else
    return mod_known[s->modelIdx].brushModelData->planes + s->planeIdx;
#endif
#endif
}
#endif
#if !MSURFACE_HAS_LIGHT_SAMPLE_POINTER
static inline byte* getMsurfaceSamples(msurface_t *s)
{
    if (s->samplesIdx == 0xFFFF)
        return NULL;
    else
#if !SEPARATE_BRUSH_MODEL_DATA
        return mod_known[s->modelIdx].lightdata + (s->samplesIdx << 2);
#else
        return mod_known[s->modelIdx].brushModelData->lightdata + (s->samplesIdx << 2);
#endif
}
#endif
#if !MSURFACE_HAS_TEXINFO_POINTER
static inline mtexinfo_t* getMsurfaceTexinfo(msurface_t *s)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    return mod_known[s->modelIdx].texinfo + s->texinfoIdx;
#else
#if MSURFACE_HAS_TEXINFO_POINTER
    return s->texinfo;
#else
    return mod_known[s->modelIdx].brushModelData->texinfo + s->texinfoIdx;
#endif
#endif
}
#endif
#else

#if !MSURFACE_HAS_PLANE_POINTER
__attribute__((always_inline))  static inline void setMsurfacePlane(msurface_t *s, mplane_t *p)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    s->planeIdx = p - mod_known[s->modelIdx].planes;
#else
#if MSURFACE_HAS_PLANE_POINTER
    s->plane = p;
 #else
    s->planeIdx = p - s->model->brushModelData->planes;
#endif
#endif

}
__attribute__((always_inline))  static inline mplane_t* getMsurfacePlane(msurface_t *s)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    return mod_known[s->modelIdx].planes + s->planeIdx;
#else
#if MSURFACE_HAS_PLANE_POINTER
    return s->plane;
#else
    return s->model->brushModelData->planes + s->planeIdx;
#endif
#endif
}
#endif
static inline byte* getMsurfaceSamples(msurface_t *s)
{
#if !MSURFACE_HAS_LIGHT_SAMPLE_POINTER
    if (s->samplesIdx == 0xFFFF)
        return NULL;
    else
        return s->model->brushModelData->lightdata + (s->samplesIdx << 2);
#else
    return s->samples;
#endif
}
#if MSURFACE_HAS_TEXINFO_POINTER

static inline mtexinfo_t* getMsurfaceTexinfo(msurface_t *s)
{
    return s->texinfo;
}
#endif

#endif

//============================================================================
#if 1
#if WIN32
extern int gcn;
#endif
static inline __attribute__ ((always_inline)) mnode_t* Mod_GetChildNode(mnode_t *node, int childNumber, model_t *model)
{
#if WIN32 && 0
        gcn++;
        printf("GetChild Node %d\r\n", gcn);
    #endif
#if 1
    int p = node->children_idx[childNumber];
#if !SEPARATE_BRUSH_MODEL_DATA
    if (p >= 0)
    {
        return model->nodes + p;
    }
    else
        return (mnode_t*) (model->leafs + (-1 - p));
#else
    if (p >= 0)
    {
        return model->brushModelData->nodes + p;
    }
    else
        return (mnode_t *)(model->brushModelData->leafs + (-1 - p));

#endif
#else
    return  node->children_idx[childNumber];
#endif
}
#if WIN32
extern int gpn;
#endif
static inline __attribute__ ((always_inline)) mnode_t* Mod_GetParent(mnode_t *node, model_t *model)
{
#if WIN32 && 0
    gpn++;
    printf("GetParent %d\r\n", gpn);
    #endif
    if (node->parent_idx < 0)
        return NULL;
    else
#if !SEPARATE_BRUSH_MODEL_DATA
        return model->nodes + node->parent_idx;
#else
        return model->brushModelData->nodes + node->parent_idx;
#endif
}
#if !NODE_HAS_CHILDREN_POINTERS

#endif
#if !NODE_HAS_PLANE_POINTER
static inline __attribute__ ((always_inline))  mplane_t *Mod_GetNodePlane(mnode_t *node, model_t *model)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    return model->planes + node->plane_idx;
#else
    return model->brushModelData->planes + node->plane_idx;

#endif
}
#endif
#endif
void Mod_Init(void);
void Mod_ClearAll(void);
model_t* Mod_ForName(const char *name, qboolean crash);
void* Mod_Extradata(model_t *mod);	// handles caching
void Mod_TouchModel(char *name);
mleaf_t* Mod_PointInLeaf(vec3_t p, model_t *model);
byte* Mod_LeafPVS(mleaf_t *leaf, model_t *model);
texture_t* Mod_GetNextAnimTexture(texture_t *base);
texture_t* Mod_GetAlternateAnimTexture(texture_t *base);
// next-hack: model loading (actually storing to flash) support functions.
void finalizeModKnown(void);
int canNewModelBeLoaded(void);
void resetTempModKnown(void **smb, void **mpb);

#endif	// __MODEL__
