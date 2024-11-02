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
// r_local.h -- private refresh defs
#ifndef GLQUAKE
#include "r_shared.h"
#ifndef R_LOCAL_H
#define R_LOCAL_H
#define MAX_PARTICLES       512 //2047  // default max # of particles at one

#define ALIAS_BASE_SIZE_RATIO		(1.0f / 11.0f)
					// normalizing factor so player model works out to about
					//  1 pixel per triangle

#define BMODEL_FULLY_CLIPPED	0x10 // value returned by R_BmodelCheckBBox ()
									 //  if bbox is trivially rejected

//===========================================================================
// viewmodel lighting

typedef struct {
	int			ambientlight;
	int			shadelight;
	float		*plightvec;
} alight_t;

//===========================================================================
// clipped bmodel edges

// clipped bmodel edges
#define BEDGE_HAS_VERTEX_POINTERS 1
#define BEDGE_HAS_NEXT_POINTERS 1
typedef struct bedge_s
{
#if BEDGE_HAS_VERTEX_POINTERS
  mvertex_t   *v[2];
#else
//    uint8_t v_idx[2];
// mvertex_t *pv[2];
    uint32_t v0_idx : 15;
    uint32_t notStackVertRelative0:1;
    uint32_t v1_idx : 15;
    uint32_t notStackVertRelative1:1;
#endif

#if BEDGE_HAS_NEXT_POINTERS
  struct bedge_s  *pnext;
#endif
} bedge_t;

typedef struct {
	float	fv[3];		// viewspace x, y
} auxvert_t;

//===========================================================================
#if USE_ORIGINAL_CVAR
extern cvar_t	r_draworder;
extern cvar_t	r_speeds;
extern cvar_t	r_timegraph;
extern cvar_t	r_graphheight;
extern cvar_t	r_clearcolor;
extern cvar_t	r_waterwarp;
extern cvar_t	r_fullbright;
extern cvar_t	r_drawentities;
extern cvar_t	r_aliasstats;
extern cvar_t	r_dspeeds;
extern cvar_t	r_drawflat;
extern cvar_t	r_ambient;
extern cvar_t	r_reportsurfout;
extern cvar_t	r_maxsurfs;
extern cvar_t	r_numsurfs;
extern cvar_t	r_reportedgeout;
extern cvar_t	r_maxedges;
extern cvar_t	r_numedges;
#endif
#define XCENTERING	(1.0f / 2.0f)
#define YCENTERING	(1.0f / 2.0f)

#define CLIP_EPSILON		0.001f

#define BACKFACE_EPSILON	0.01f

//===========================================================================

#define	DIST_NOT_SET	98765

// !!! if this is changed, it must be changed in asm_draw.h too !!!
#define CLIP_PLANE_FRACBITS         16
typedef struct clipplane_s
{
#if CLIP_PLANE_USES_FLOAT
    vec3_t   normal;
    float   dist; // must be float
    struct    clipplane_s *next;
    byte    leftedge;
    byte    rightedge;
    byte    reserved[2];

    #else

	/*vec3_t*/ short		frac_normal[3];
	int		frac_dist; // must be float
	struct		clipplane_s	*next;
	byte		leftedge;
	byte		rightedge;
	byte		reserved[2];
#endif
} clipplane_t;

//extern	clipplane_t	view_clipplanes[4];

//=============================================================================

void R_RenderWorld (void);

//=============================================================================

extern	mplane_t	screenedge[4];

//extern	vec3_t	r_origin;

//extern	vec3_t	r_entorigin;

extern	float	screenAspect;
extern	float	verticalFieldOfView;
extern	float	xOrigin, yOrigin;
#if USING_R_VISFRAMECOUNT
extern	int		r_visframecount;
#endif
//=============================================================================

extern int	vstartscan;


void R_ClearPolyList (void);
void R_DrawPolyList (void);

//
// current entity info
//
//extern	qboolean		insubmodel;
//extern	vec3_t			r_worldmodelorg;


void R_DrawSprite (void);
void R_RenderFace (msurface_t *fa, int clipflags);
void R_RenderPoly (msurface_t *fa, int clipflags);
void R_RenderBmodelFace (bedge_t *pedges, msurface_t *psurf);
void R_TransformPlane (mplane_t *p, float *normal, float *dist);
void R_TransformFrustum (void);
void R_SetSkyFrame (void);
void R_DrawSurfaceBlock16 (void);
void R_DrawSurfaceBlock8 (void);
texture_t *R_TextureAnimation (texture_t *base);
DRAWSURF_SEC void R_AddDynamicLights (void);

#if	id386

void R_DrawSurfaceBlock8_mip0 (void);
void R_DrawSurfaceBlock8_mip1 (void);
void R_DrawSurfaceBlock8_mip2 (void);
void R_DrawSurfaceBlock8_mip3 (void);

#endif

void R_GenSkyTile (void *pdest);
void R_GenSkyTile16 (void *pdest);
void R_Surf8Patch (void);
void R_Surf16Patch (void);
void R_DrawSubmodelPolygons (model_t *pmodel, int clipflags);
void R_DrawSolidClippedSubmodelPolygons (model_t *pmodel);

void R_AddPolygonEdges (emitpoint_t *pverts, int numverts, int miplevel);
surf_t *R_GetSurf (void);
void R_AliasDrawModel (alight_t *plighting);
void R_BeginEdgeFrame (void);
void R_ScanEdges (void);
void D_DrawSurfaces (void);
//void R_InsertNewEdges (edge_t *edgestoadd, edge_t *edgelist);
//void R_StepActiveU (edge_t *pedge);
void R_RemoveEdges (edge_t *pedge);

extern void R_Surf8Start (void);
extern void R_Surf8End (void);
extern void R_Surf16Start (void);
extern void R_Surf16End (void);
extern void R_EdgeCodeStart (void);
extern void R_EdgeCodeEnd (void);

extern void R_RotateBmodel (void);
extern void clearCachedEdgeOffsets(void);
extern int	c_faceclip;
extern int	r_polycount;
extern int	r_wholepolycount;

extern	model_t		*cl_worldmodel;

extern int		*pfrustum_indexes[4];

// !!! if this is changed, it must be changed in asm_draw.h too !!!
#define	NEAR_CLIP	0.01f

//extern int			ubasestep, errorterm, erroradjustup, erroradjustdown;
//extern int			vstartscan;

//extern fixed16_t	sadjust, tadjust;
//extern fixed16_t	bbextents, bbextentt;

#define MAXBVERTINDEXES	1000	// new clipped vertices when clipping bmodels
								//  to the world BSP
extern mvertex_t	*r_ptverts, *r_ptvertsmax;

extern vec3_t			sbaseaxis[3], tbaseaxis[3];
//extern float			entity_rotation[3][3];

extern int		reinit_surfcache;

//extern int		r_currentkey;
//extern int		r_currentbkey;

typedef struct btofpoly_s {
	int			clipflags;
	msurface_t	*psurf;
} btofpoly_t;

#define MAX_BTOFPOLYS	5000	// FIXME: tune this

extern int			numbtofpolys;
extern btofpoly_t	*pbtofpolys;

void	R_InitTurb (void);
void	R_ZDrawSubmodelPolys (model_t *clmodel);

//=========================================================
// Alias models
//=========================================================

#define MAXALIASVERTS		350	// TODO: tune this // next-hack: 256 are fine for demo1.
#define ALIAS_Z_CLIP_PLANE	5

//extern int				numverts;
//extern int				a_skinwidth;
//extern mtriangle_t		*ptriangles;
//extern int				numtriangles;
//extern aliashdr_t		*paliashdr;
//extern mdl_t			*pmdl;
//extern float			leftclip, topclip, rightclip, bottomclip;
//extern int				r_acliptype;
//extern finalvert_t		*pfinalverts;
//extern auxvert_t		*pauxverts;

qboolean R_AliasCheckBBox (void);

//=========================================================
// turbulence stuff

#define	AMP		8*0x10000
#define	AMP2	3
#define	SPEED	20

//=========================================================
// particle stuff

void R_DrawParticles (void);
void R_InitParticles (void);
void R_ClearParticles (void);
void R_ReadPointFile_f (void);
void R_SurfacePatch (void);

//extern int		r_amodels_drawn;
//extern edge_t	*auxedges;
//extern int		r_numallocatededges;
//extern edge_t	*r_edges, *edge_p, *edge_max;

#if STATIC_NEW_REMOVE_EDGES
    extern edge_t	*newedges[MAXHEIGHT];   // these might be indexes
    extern edge_t	*removeedges[MAXHEIGHT];    // these might be indexes
#else
//    extern edge_t	**newedges;   // these might be indexes
//    extern edge_t	**removeedges;    // these might be indexes
#endif // STATIC_EDGES
#define screenwidth SCREEN_WIDTH

extern int		r_bmodelactive;
extern vrect_t	*pconupdate;
#if !CONSTANT_VIDEO_VALUES
extern float		aliasxscale, aliasyscale, aliasxcenter, aliasycenter;
#endif
extern float		r_aliastransition, r_resfudge;

extern int		r_outofsurfaces;
extern int		r_outofedges;

extern mvertex_t	*r_pcurrentvertbase;
extern int			r_maxvalidedgeoffset;

void R_AliasClipTriangle (mtriangle_t *ptri);
#if PROFILE_SPEED
extern float	r_time1;
extern float	dp_time1, dp_time2, db_time1, db_time2, rw_time1, rw_time2;
extern float	se_time1, se_time2, de_time1, de_time2, dv_time1, dv_time2;
#endif
extern int		r_frustum_indexes[4*6];
extern int		r_maxsurfsseen, r_maxedgesseen, r_cnumsurfs;
extern qboolean	r_surfsonstack;
extern cshift_t	cshift_water;
extern qboolean	r_dowarpold, r_viewchanged;

extern mleaf_t	*r_viewleaf, *r_oldviewleaf;

extern vec3_t	r_emins, r_emaxs;
extern mnode_t	*r_pefragtopnode;
extern int		r_clipflags;
extern int		r_dlightframecount;
extern qboolean	r_fov_greater_than_90;
//void R_StoreEfrags (efrag_t **ppefrag);
// next-hack: added this function so that we don't need efrags.
void CL_FindTouchedLeafs (entity_t *ent, mnode_t *node, entLeaves_t *el);
void R_TimeRefresh_f (void);
void R_TimeGraph (void);
void R_PrintAliasStats (void);
void R_PrintTimes (void);
void R_PrintDSpeeds (void);
void R_AnimateLight (void);
int R_LightPoint (vec3_t p);
void R_SetupFrame (void);
void R_cshift_f (void);
//void R_EmitEdge (mvertex_t *pv0, mvertex_t *pv1);
//void R_ClipEdge (mvertex_t *pv0, mvertex_t *pv1, clipplane_t *clip);
void R_SplitEntityOnNode2 (mnode_t *node);
void R_MarkLights (dlight_t *light, int bit, mnode_t *node);
#if !DYNAMIC_RESOLUTION
#define SCREEN_WIDTH 320
#define d_scantable(i) (i * SCREEN_WIDTH)
#define	zspantable(i)  (_g->d_pzbuffer + i * SCREEN_WIDTH)
#else
#define d_scantable(i) d_scantable[i]
#define	zspantable(i)  zspantable[i]

#endif
#endif
#endif
