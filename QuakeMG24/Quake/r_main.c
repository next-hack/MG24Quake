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
// r_main.c
#include "quakedef.h"
#include "r_local.h"

//define	PASSAGES

void *colormap;
vec3_t viewlightvec;
alight_t r_viewlighting =
{ 128, 192, viewlightvec
};
#if PROFILE_SPEED
  float		r_time1;
#endif
//qboolean	r_drawpolys;
//qboolean	r_drawculledpolys;
//qboolean	r_worldpolysbacktofront;
//qboolean	r_recursiveaffinetriangles = true;
//const int			r_pixbytes = 1;
//const int		r_aliasuvscale = 1; // was float.
int r_outofsurfaces;
int r_outofedges;

qboolean r_dowarp, r_dowarpold, r_viewchanged;
#if r_drawpolys
int			numbtofpolys;
btofpoly_t	*pbtofpolys;
#endif
mvertex_t *r_pcurrentvertbase;
#if PROFILE_SPEED
int			c_surf, pixLoaded, singlePixelLoaded, pixSaved;
float       pixLoadMicrosecs;
#endif
#if WIN32
int r_maxsurfsseen, r_maxedgesseen;
#endif
int r_cnumsurfs;
qboolean r_surfsonstack;
int r_clipflags;
#if WARP_HAS_DIFFERENT_RESOLUTION
byte		*r_warpbuffer;
#endif
#if 0
byte		*r_stack_start;
#endif
qboolean r_fov_greater_than_90;

//
// screen size info
//
//refdef_t	_g->r_refdef;

float xscaleshrink, yscaleshrink;
#if !CONSTANT_VIDEO_VALUES
float   xcenter, ycenter;
float   xscale, yscale;
float   xscaleinv, yscaleinv;
float		aliasxscale, aliasyscale, aliasxcenter, aliasycenter;
float pixelAspect;
#endif
//const int		screenwidth = SCREEN_WIDTH;
float screenAspect;
float verticalFieldOfView;
float xOrigin, yOrigin;

mplane_t screenedge[4];

//
// refresh flags
//
#if USE_R_FRAMECOUNT
int		r_framecount = 1;	// so frame counts initialized to 0 don't match
#endif
#if USING_R_VISFRAMECOUNT
int		r_visframecount;
#endif
#if PROFILE
int		d_spanpixcount;
int		r_polycount;
int		r_drawnpolycount;
int		r_wholepolycount;
#endif
#define		VIEWMODNAME_LENGTH	256
char viewmodname[VIEWMODNAME_LENGTH + 1];
int modcount;

int *pfrustum_indexes[4];
int r_frustum_indexes[4 * 6];

int reinit_surfcache = 1;	// if 1, surface cache is currently empty and
                            // must be reinitialized for current cache size

mleaf_t *r_viewleaf, *r_oldviewleaf;

texture_t *r_notexture_mip;

float r_aliastransition, r_resfudge;

short d_lightstylevalue[MAX_LIGHTSTYLES];	// 8.8 fraction of base light value
#if PROFILE_SPEED
float	dp_time1, dp_time2, db_time1, db_time2, rw_time1, rw_time2;
float	se_time1, se_time2, de_time1, de_time2, dv_time1, dv_time2;
#endif
void R_MarkLeaves(void);
#if USE_ORIGINAL_CVAR
cvar_t	r_draworder = {"r_draworder","0"};
cvar_t	r_speeds = {"r_speeds","0"};
cvar_t	r_timegraph = {"r_timegraph","0"};
cvar_t	r_graphheight = {"r_graphheight","10"};
cvar_t	r_clearcolor = {"r_clearcolor","2"};
cvar_t	r_waterwarp = {"r_waterwarp","1"};
cvar_t	r_fullbright = {"r_fullbright","0"};
cvar_t	r_drawentities = {"r_drawentities","1"};
cvar_t	r_drawviewmodel = {"r_drawviewmodel","1"};
cvar_t	r_aliasstats = {"r_polymodelstats","0"};
cvar_t	r_dspeeds = {"r_dspeeds","0"};
cvar_t	r_drawflat = {"r_drawflat", "0"};
cvar_t	r_ambient = {"r_ambient", "0"};
cvar_t	r_reportsurfout = {"r_reportsurfout", "0"};
cvar_t	r_maxsurfs = {"r_maxsurfs", "0"};
cvar_t	r_numsurfs = {"r_numsurfs", "0"};
cvar_t	r_reportedgeout = {"r_reportedgeout", "0"};
cvar_t	r_maxedges = {"r_maxedges", "0"};
cvar_t	r_numedges = {"r_numedges", "0"};
cvar_t	r_aliastransbase = {"r_aliastransbase", "200"};
cvar_t	r_aliastransadj = {"r_aliastransadj", "100"};
extern cvar_t	scr_fov;
#endif

/*
 ==================
 R_InitTextures
 ==================
 */
#if TEXTURE_HAS_POINTER_TO_EXTMEM
const byte notexturedata[256 + 64 + 16 + 4] =
{
// FIXME: put some checkerboard pattern...
    0
};
#endif
void R_InitTextures(void)
{
// create a simple checkerboard texture for the default
    r_notexture_mip = Z_Calloc(sizeof(texture_t), 1, PU_STATIC, NULL);
    r_notexture_mip->width = r_notexture_mip->height = 16;
    r_notexture_mip->extmemdata[0] = (uint8_t*) &notexturedata[0];
    r_notexture_mip->extmemdata[1] = (uint8_t*) &notexturedata[0] + 16 * 16;
    r_notexture_mip->extmemdata[2] = (uint8_t*) &notexturedata[0] + 8 * 8;
    r_notexture_mip->extmemdata[3] = (uint8_t*) &notexturedata[0] + 4 * 4;
    void *tmp = storeToInternalFlash(r_notexture_mip, sizeof(texture_t));
    Z_Free(r_notexture_mip);
    r_notexture_mip = tmp;
}

/*
 ===============
 R_Init
 ===============
 */
void R_Init(void)
{

// get stack position so we can guess if we are going to overflow
#if 0
	r_stack_start = (byte *)&dummy;
#endif
    R_InitTurb();

#if READ_POINT_FILE
	Cmd_AddCommand ("timerefresh", R_TimeRefresh_f);

	Cmd_AddCommand ("pointfile", R_ReadPointFile_f);
    #endif
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&r_draworder);
	Cvar_RegisterVariable (&r_speeds);
	Cvar_RegisterVariable (&r_timegraph);
	Cvar_RegisterVariable (&r_graphheight);
	Cvar_RegisterVariable (&r_drawflat);
	Cvar_RegisterVariable (&r_ambient);
	Cvar_RegisterVariable (&r_clearcolor);
	Cvar_RegisterVariable (&r_waterwarp);
	Cvar_RegisterVariable (&r_fullbright);
	Cvar_RegisterVariable (&r_drawentities);
	Cvar_RegisterVariable (&r_drawviewmodel);
	Cvar_RegisterVariable (&r_aliasstats);
	Cvar_RegisterVariable (&r_dspeeds);
	Cvar_RegisterVariable (&r_reportsurfout);
	Cvar_RegisterVariable (&r_maxsurfs);
	Cvar_RegisterVariable (&r_numsurfs);
	Cvar_RegisterVariable (&r_reportedgeout);
	Cvar_RegisterVariable (&r_maxedges);
	Cvar_RegisterVariable (&r_numedges);
	Cvar_RegisterVariable (&r_aliastransbase);
	Cvar_RegisterVariable (&r_aliastransadj);
#endif
    Cvar_SetValue("r_maxedges", (float) NUMSTACKEDGES);
    Cvar_SetValue("r_maxsurfs", (float) NUMSTACKSURFACES);

    _g->view_clipplanes[0].leftedge = true;
    _g->view_clipplanes[1].rightedge = true;
    _g->view_clipplanes[1].leftedge = _g->view_clipplanes[2].leftedge = _g->view_clipplanes[3].leftedge = false;
    _g->view_clipplanes[0].rightedge = _g->view_clipplanes[2].rightedge = _g->view_clipplanes[3].rightedge = false;

    _g->r_refdef.xOrigin = XCENTERING;
    _g->r_refdef.yOrigin = YCENTERING;

    R_InitParticles();

// TODO: collect 386-specific code in one place
#if	id386
	Sys_MakeCodeWriteable ((long)R_EdgeCodeStart,
					     (long)R_EdgeCodeEnd - (long)R_EdgeCodeStart);
#endif	// id386

    D_Init();
}

/*
 ===============
 R_NewMap
 ===============
 */
void R_NewMap(void)
{

// clear out efrags in case the level hasn't been reloaded
// FIXME: is this one short?
#if LEAF_HAS_EFRAGS
  int   i;
  for (i=0 ; i<cl.worldmodel->numleafs ; i++)
		cl.worldmodel->leafs[i].efrags = NULL;
#endif
    r_viewleaf = NULL;
    R_ClearParticles();

    r_cnumsurfs = r_maxsurfs;

    if (r_cnumsurfs <= MINSURFACES)
        r_cnumsurfs = MINSURFACES;

    if (r_cnumsurfs > NUMSTACKSURFACES)
    {
        while (1)
            FIXME("ERROR");
//		surfaces = Hunk_AllocName (r_cnumsurfs * sizeof(surf_t), "surfaces");
        _g->surface_p = _g->surfaces;
        _g->surf_max = &_g->surfaces[r_cnumsurfs];
        r_surfsonstack = false;
        // surface 0 doesn't really exist; it's just a dummy because index 0
        // is used to indicate no edge attached to surface
        _g->surfaces--;
        R_SurfacePatch();
    }
    else
    {
        r_surfsonstack = true;
    }
#if WIN32
    r_maxedgesseen = 0;
    r_maxsurfsseen = 0;
#endif
    r_dowarpold = false;
    r_viewchanged = false;
#ifdef PASSAGES
CreatePassages ();
#endif
}

/*
 ===============
 R_SetVrect
 ===============
 */
void R_SetVrect(vrect_t *pvrectin, vrect_t *pvrect, int lineadj)
{
    int h;
    float size;

    size = viewsize > 100 ? 100 : viewsize;
//	printf("viewsize is %f, lineadj %d\r\n", size, lineadj);
    if (_g->cl.intermission)
    {
        size = 100;
        lineadj = 48; // next-hack was 0, but we cannot go fullscreen
    }
    size /= 100;

    h = pvrectin->height - lineadj;
    pvrect->width = pvrectin->width * size;
    if (pvrect->width < 96)
    {
        size = 96.0 / pvrectin->width;
        pvrect->width = 96;	// min for icons
    }
    pvrect->width &= ~7;
    pvrect->height = pvrectin->height * size;
    if (pvrect->height > pvrectin->height - lineadj)
        pvrect->height = pvrectin->height - lineadj;

    pvrect->height &= ~1;

    pvrect->x = (pvrectin->width - pvrect->width) / 2;
    pvrect->y = (h - pvrect->height) / 2;

    {
        if (lcd_x)
        {
            pvrect->y >>= 1;
            pvrect->height >>= 1;
        }
    }
}

/*
 ===============
 R_ViewChanged

 Called every time the vid structure or _g->r_refdef changes.
 Guaranteed to be called before the first refresh
 ===============
 */
void R_ViewChanged(vrect_t *pvrect, int lineadj, float aspect)
{
    (void) aspect;
    int i;
    float res_scale;

    r_viewchanged = true;

    R_SetVrect(pvrect, &_g->r_refdef.vrect, lineadj);

    _g->r_refdef.fvrectx = (float) _g->r_refdef.vrect.x;
    _g->r_refdef.fvrectx_adj = (float) _g->r_refdef.vrect.x - 0.5;
    _g->r_refdef.vrect_x_adj_shift20 = (_g->r_refdef.vrect.x << 20) + (1 << 19) - 1;
    _g->r_refdef.fvrecty = (float) _g->r_refdef.vrect.y;
    _g->r_refdef.fvrecty_adj = (float) _g->r_refdef.vrect.y - 0.5;
    _g->r_refdef.vrectright = _g->r_refdef.vrect.x + _g->r_refdef.vrect.width;
    _g->r_refdef.vrectright_adj_shift20 = (_g->r_refdef.vrectright << 20) + (1 << 19) - 1;
    _g->r_refdef.fvrectright = (float) _g->r_refdef.vrectright;
    _g->r_refdef.fvrectright_adj = (float) _g->r_refdef.vrectright - 0.5;
    _g->r_refdef.vrectrightedge = (float) _g->r_refdef.vrectright - 0.99;
    _g->r_refdef.vrectbottom = _g->r_refdef.vrect.y + _g->r_refdef.vrect.height;
    _g->r_refdef.fvrectbottom = (float) _g->r_refdef.vrectbottom;
    _g->r_refdef.fvrectbottom_adj = (float) _g->r_refdef.vrectbottom - 0.5;

    _g->r_refdef.aliasvrect.x = (int) (_g->r_refdef.vrect.x * r_aliasuvscale);
    _g->r_refdef.aliasvrect.y = (int) (_g->r_refdef.vrect.y * r_aliasuvscale);
    _g->r_refdef.aliasvrect.width = (int) (_g->r_refdef.vrect.width * r_aliasuvscale);
    _g->r_refdef.aliasvrect.height = (int) (_g->r_refdef.vrect.height * r_aliasuvscale);
    _g->r_refdef.aliasvrectright = _g->r_refdef.aliasvrect.x + _g->r_refdef.aliasvrect.width;
    _g->r_refdef.aliasvrectbottom = _g->r_refdef.aliasvrect.y + _g->r_refdef.aliasvrect.height;
#if !CONSTANT_VIDEO_VALUES
	pixelAspect = aspect;
#endif
    xOrigin = _g->r_refdef.xOrigin;
    yOrigin = _g->r_refdef.yOrigin;

    screenAspect = _g->r_refdef.vrect.width * pixelAspect / _g->r_refdef.vrect.height;
// 320*200 1.0 pixelAspect = 1.6 screenAspect
// 320*240 1.0 pixelAspect = 1.3333 screenAspect
// proper 320*200 pixelAspect = 0.8333333

    verticalFieldOfView = _g->r_refdef.horizontalFieldOfView / screenAspect;
#if CONSTANT_VIDEO_VALUES
    _g->r_refdef.horizontalFieldOfView = 2;

#else
  _g->r_refdef.horizontalFieldOfView = 2.0 * tan_t(_g->r_refdef.fov_x/360*M_PI);
#endif
// values for perspective projection
// if math were exact, the values would range from 0.5 to to range+0.5
// hopefully they wll be in the 0.000001 to range+.999999 and truncate
// the polygon rasterization will never render in the first row or column
// but will definately render in the [range] row and column, so adjust the
// buffer origin to get an exact edge to edge fill
#if !CONSTANT_VIDEO_VALUES
	xcenter = ((float)_g->r_refdef.vrect.width * XCENTERING) + _g->r_refdef.vrect.x - 0.5;
	aliasxcenter = xcenter * r_aliasuvscale;
	ycenter = ((float)_g->r_refdef.vrect.height * YCENTERING) + _g->r_refdef.vrect.y - 0.5;
	aliasycenter = ycenter * r_aliasuvscale;

	xscale = _g->r_refdef.vrect.width / _g->r_refdef.horizontalFieldOfView;
	aliasxscale = xscale * r_aliasuvscale;
	xscaleinv = 1.0f / xscale;
	yscale = xscale * pixelAspect;
	aliasyscale = yscale * r_aliasuvscale;
	yscaleinv = 1.0f / yscale;
#endif
    xscaleshrink = (_g->r_refdef.vrect.width - 6) / _g->r_refdef.horizontalFieldOfView;
    yscaleshrink = xscaleshrink * pixelAspect;

// left side clip
    screenedge[0].normal[0] = -1.0 / (xOrigin * _g->r_refdef.horizontalFieldOfView);
    screenedge[0].normal[1] = 0;
    screenedge[0].normal[2] = 1;
    screenedge[0].type = PLANE_ANYZ;

// right side clip
    screenedge[1].normal[0] = 1.0 / ((1.0 - xOrigin) * _g->r_refdef.horizontalFieldOfView);
    screenedge[1].normal[1] = 0;
    screenedge[1].normal[2] = 1;
    screenedge[1].type = PLANE_ANYZ;

// top side clip
    screenedge[2].normal[0] = 0;
    screenedge[2].normal[1] = -1.0 / (yOrigin * verticalFieldOfView);
    screenedge[2].normal[2] = 1;
    screenedge[2].type = PLANE_ANYZ;

// bottom side clip
    screenedge[3].normal[0] = 0;
    screenedge[3].normal[1] = 1.0 / ((1.0 - yOrigin) * verticalFieldOfView);
    screenedge[3].normal[2] = 1;
    screenedge[3].type = PLANE_ANYZ;

    for (i = 0; i < 4; i++)
        VectorNormalize(screenedge[i].normal);

    res_scale = sqrtf_m((QDFLOAT) (_g->r_refdef.vrect.width * _g->r_refdef.vrect.height) / (320.0f * 152.0f)) * (2.0f / _g->r_refdef.horizontalFieldOfView);
    r_aliastransition = r_aliastransbase * res_scale;
    r_resfudge = r_aliastransadj * res_scale;

    if (fov <= 90.0f)
        r_fov_greater_than_90 = false;
    else
        r_fov_greater_than_90 = true;

    D_ViewChanged();
}

/*
 ===============
 R_MarkLeaves
 ===============
 */
void R_MarkLeaves(void)
{
    byte *vis;
    mnode_t *node;
    int i;
#if !VISLEAVES_IN_Z_BUFFER
	if (r_oldviewleaf == r_viewleaf)
		return;
#else
// note: recalculating visited leaves everytime might affect performance!
#endif
#if USING_R_VISFRAMECOUNT
	r_visframecount++;
#else
#if VISLEAVES_IN_Z_BUFFER
    _g->visleaves = (byte*) d_zbuffer;
    _g->visnodes = (byte*) _g->visleaves + 4 * ((MAX_MAP_LEAFS + 31) / 32);
#endif
    fastMemclear32(_g->visleaves, (MAX_MAP_LEAFS + 31) / 32);
    fastMemclear32(_g->visnodes, (MAX_MAP_NODES + 31) / 32);
#endif
    r_oldviewleaf = r_viewleaf;

    vis = Mod_LeafPVS(r_viewleaf, _g->cl.worldmodel);
#if !SEPARATE_BRUSH_MODEL_DATA
	for (i=0 ; i<cl.worldmodel->numleafs ; i++)
#else
    for (i = 0; i < _g->cl.worldmodel->brushModelData->numleafs; i++)
#endif
    {
        if (vis[i >> 3] & (1 << (i & 7)))
        {
#if USING_R_VISFRAMECOUNT
			node = (mnode_t *)&cl.worldmodel->leafs[i+1];
			do
			{
				if (node->visframe == r_visframecount)
					break;
				node->visframe = r_visframecount;
				node = node->parent;
			} while (node);
			#else
            int nodeindex;

            int alreadyVisible /*=  _g->visleaves[(i + 1) >> 3]  & (1 << ((i + 1) & 7));
             if (alreadyVisible)
             continue*/;
#if !SEPARATE_BRUSH_MODEL_DATA
            node = (mnode_t *)&cl.worldmodel->leafs[i+1];
#else
            node = (mnode_t*) &_g->cl.worldmodel->brushModelData->leafs[i + 1];
#endif
            _g->visleaves[(i + 1) >> 3] |= 1 << ((i + 1) & 7);      // set leaf visible
            do
            {
#if NODE_HAS_PARENT_POINTER
			    node = node->parent;                            // get parent (now should be only nodes)
#else
                node = Mod_GetParent(node, _g->cl.worldmodel);
#endif
                if (node)
                {
#if OLD_NODE_STRUCTURE
#if !SEPARATE_BRUSH_MODEL_DATA
                    nodeindex = node - cl.worldmodel->nodes;
#else
                    nodeindex = node - cl.worldmodel->brushModelData->nodes;
#endif
#else
                    nodeindex = node->node_idx;
#endif
                    checkNodeIndex(nodeindex, 30, __LINE__);
                    alreadyVisible = _g->visnodes[(nodeindex) >> 3] & (1 << ((nodeindex) & 7));
                    if (alreadyVisible)
                        break;
                    else
                        _g->visnodes[(nodeindex) >> 3] |= (1 << ((nodeindex) & 7));
                }
            }
            while (node);
#endif
        }
    }
}
#define COPY_COLORMAP_TO_RAM   0
#if COPY_COLORMAP_TO_RAM
void *oldVidColormap;
#endif
/*
 =============
 R_DrawEntitiesOnList
 =============
 */
void R_DrawEntitiesOnList(void)
{
    int i, j;
    int lnum;
    alight_t lighting;
// FIXME: remove and do real lighting
    float lightvec[3] =
    { -1, 0, 0
    };
    vec3_t dist;
    float add;
#if WIN32
  // debug/profiling (next-hack)
	int aliasNumDrawn = 0;
    int spritesNumDrawn = 0;
#endif
    //
    if (!r_drawentities)
        return;
#if COPY_COLORMAP_TO_RAM
#define MIN_ENTITIES_TO_COPY_COLORS 0
	oldVidColormap = vid.colormap;
   if (_g->cl_numvisedicts > MIN_ENTITIES_TO_COPY_COLORS)
   {
        vid.colormap = (byte*) getTextureCacheBuffer() + MAX_TEXTURE_SIZE - 16384;
      // copy to ram
      for (int i = 0; i < 16384 / 4; i+=2)
      {
        ((uint32_t*)vid.colormap)[i] = ((uint32_t*)oldVidColormap)[i];
        ((uint32_t*)vid.colormap)[i+1] = ((uint32_t*)oldVidColormap)[i+1];
        ((uint32_t*)vid.colormap)[i+2] = ((uint32_t*)oldVidColormap)[i+2];
        ((uint32_t*)vid.colormap)[i+3] = ((uint32_t*)oldVidColormap)[i+3];

      }
   }
#endif

    for (i = 0; i < _g->cl_numvisedicts; i++)
    {

#if POINTER_CL_VISEDICT
		currententity = cl_visedicts[i];
#else
        _g->currententity = &cl_entities[_g->cl_visedicts[i]];
#endif
        if (_g->currententity == &cl_entities[_g->cl.viewentity])
            continue;	// don't draw the player

        switch (getEntityModel(_g->currententity)->type)
        {
            case mod_sprite:
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (currententity->origin, r_entorigin);
#else
                VectorCopy(VEC(getEntityOrigins(_g->currententity)), _g->r_entorigin)
                ;
#endif
                VectorSubtract(_g->r_origin, _g->r_entorigin, _g->modelorg)
                ;
                R_DrawSprite();
#if WIN32
			spritesNumDrawn ++;
#endif
                break;

            case mod_alias:
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (currententity->origin, r_entorigin);
#else
                VectorCopy(VEC(getEntityOrigins(_g->currententity)), _g->r_entorigin)
                ;
#endif
                VectorSubtract(_g->r_origin, _g->r_entorigin, _g->modelorg)
                ;

                // see if the bounding box lets us trivially reject, also sets
                // trivial accept status
                if (R_AliasCheckBBox())
                {
#if !ENTITY_HAS_SHORT_COORDS
				j = R_LightPoint (currententity->origin);
#else
                    j = R_LightPoint(VEC(getEntityOrigins(_g->currententity)));
#endif

                    lighting.ambientlight = j;
                    lighting.shadelight = j;

                    lighting.plightvec = lightvec;
                    vect_t origin = getEntityOrigins(_g->currententity);
                    for (lnum = 0; lnum < MAX_DLIGHTS; lnum++)
                    {
                        if (_g->cl_dlights[lnum].die >= _g->cl.time && _g->cl_dlights[lnum].radius)
                        {
#if !ENTITY_HAS_SHORT_COORDS
						VectorSubtract (currententity->origin,	cl_dlights[lnum].origin, dist);
#else
#if DLIGHT_HAS_FLOAT_ORIGIN
						VectorSubtract (VEC(getEntityOrigins(currententity)),	cl_dlights[lnum].origin, dist);
#else
                            VectorSubtract(origin.v, _g->cl_dlights[lnum].iorigin_s, dist);
#endif
#endif
                            add = _g->cl_dlights[lnum].radius - Length(dist);

                            if (add > 0)
                                lighting.ambientlight += add;
                        }
                    }

                    // clamp lighting so it doesn't overbright as much
                    if (lighting.ambientlight > 128)
                        lighting.ambientlight = 128;
                    if (lighting.ambientlight + lighting.shadelight > 192)
                        lighting.shadelight = 192 - lighting.ambientlight;
#if WIN32
				aliasNumDrawn++;
#endif
                    R_AliasDrawModel(&lighting);
                }

                break;

            default:
                break;
        }
    }
//	printf("aliasNumDrawn: %d, sprites: %d\r\n", aliasNumDrawn, spritesNumDrawn);
}

/*
 =============
 R_DrawViewModel
 =============
 */
void R_DrawViewModel(void)
{
// FIXME: remove and do real lighting
    float lightvec[3] =
    { -1, 0, 0
    };
    int j;
    int lnum;
    vec3_t dist;
    float add;
    dlight_t *dl;

    if (!r_drawviewmodel || r_fov_greater_than_90)
        return;

    if (_g->cl.items & IT_INVISIBILITY)
        return;

    if (_g->cl.stats[STAT_HEALTH] <= 0)
        return;

    _g->currententity = &_g->cl.viewent;
    if (!getEntityModel(_g->currententity))
        return;

#if !ENTITY_HAS_SHORT_COORDS
	VectorCopy (currententity->origin, r_entorigin);
#else
    VectorCopy(VEC(getEntityOrigins(_g->currententity)), _g->r_entorigin);
#endif
    VectorSubtract(_g->r_origin, _g->r_entorigin, _g->modelorg);

    VectorCopy(_g->vup, viewlightvec);
    VectorInverse(viewlightvec);
#if !ENTITY_HAS_SHORT_COORDS
	j = R_LightPoint (currententity->origin);
#else
    j = R_LightPoint(VEC(getEntityOrigins(_g->currententity)));

#endif
    if (j < 24)
        j = 24;		// allways give some light on gun
    r_viewlighting.ambientlight = j;
    r_viewlighting.shadelight = j;

// add dynamic lights
    for (lnum = 0; lnum < MAX_DLIGHTS; lnum++)
    {
        dl = &_g->cl_dlights[lnum];
        if (!dl->radius)
            continue;
        if (!dl->radius)
            continue;
        if (dl->die < _g->cl.time)
            continue;
#if !ENTITY_HAS_SHORT_COORDS
		VectorSubtract (currententity->origin, dl->origin, dist);
#else
#if DLIGHT_HAS_FLOAT_ORIGIN
		VectorSubtract (VEC(getEntityOrigins(currententity)), dl->origin, dist);
#else
        VectorSubtract(VEC(getEntityOrigins(_g->currententity)), dl->iorigin_s, dist);
#endif
#endif
        add = dl->radius - Length(dist);
        if (add > 0)
            r_viewlighting.ambientlight += add;
    }

// clamp lighting so it doesn't overbright as much
    if (r_viewlighting.ambientlight > 128)
        r_viewlighting.ambientlight = 128;
    if (r_viewlighting.ambientlight + r_viewlighting.shadelight > 192)
        r_viewlighting.shadelight = 192 - r_viewlighting.ambientlight;

    r_viewlighting.plightvec = lightvec;

#ifdef QUAKE2
	cl.light_level = r_viewlighting.ambientlight;
#endif

    R_AliasDrawModel(&r_viewlighting);

#if COPY_COLORMAP_TO_RAM
    // restore colormap
    vid.colormap = oldVidColormap;
#endif

}

/*
 =============
 R_BmodelCheckBBox
 =============
 */
int R_BmodelCheckBBox(model_t *clmodel, float *minmaxs)
{
    int i, *pindex, clipflags;
    vec3_t acceptpt, rejectpt;
#if CLIP_PLANE_USES_FLOAT
    QDFLOAT d;
#else
    int d;
#endif

    clipflags = 0;
#if !ENTITY_HAS_SHORT_COORDS
	if (currententity->angles[0] || currententity->angles[1] || currententity->angles[2])
#else
    if (getEntityAngle(_g->currententity, 0) || getEntityAngle(_g->currententity, 1) || getEntityAngle(_g->currententity, 2))
#endif
    {
        for (i = 0; i < 4; i++)
        {
#if !ENTITY_HAS_SHORT_COORDS
			d = DotProduct (currententity->origin, view_clipplanes[i].normal);
#else
#if CLIP_PLANE_USES_FLOAT
            d = DotProduct(VEC(getEntityOrigins(_g->currententity)), _g->view_clipplanes[i].normal);
#else
      d = DotProduct (VEC(getEntityOrigins(_g->currententity)), view_clipplanes[i].frac_normal);
#endif
#endif
#if CLIP_PLANE_USES_FLOAT
            d -= _g->view_clipplanes[i].dist;
#else
      d -= _g->view_clipplanes[i].frac_dist;
#endif

#if !CLIP_PLANE_USES_FLOAT
            d = d * (1.0f / (1 << CLIP_PLANE_FRACBITS));
 #endif // CLIP_PLANE_USES_FLOAT

            if (d <= -clmodel->radius)
                return BMODEL_FULLY_CLIPPED;

            if (d <= clmodel->radius)
                clipflags |= (1 << i);
        }
    }
    else
    {
        for (i = 0; i < 4; i++)
        {
            // generate accept and reject points
            // FIXME: do with fast look-ups or integer tests based on the sign bit
            // of the floating point values

            pindex = pfrustum_indexes[i];

            rejectpt[0] = minmaxs[pindex[0]];
            rejectpt[1] = minmaxs[pindex[1]];
            rejectpt[2] = minmaxs[pindex[2]];
#if CLIP_PLANE_USES_FLOAT
            d = DotProduct(rejectpt, _g->view_clipplanes[i].normal);
            d -= _g->view_clipplanes[i].dist;
#else
			d = DotProduct (rejectpt, view_clipplanes[i].frac_normal);
			d -= view_clipplanes[i].frac_dist;
#endif
            if (d <= 0)
                return BMODEL_FULLY_CLIPPED;

            acceptpt[0] = minmaxs[pindex[3 + 0]];
            acceptpt[1] = minmaxs[pindex[3 + 1]];
            acceptpt[2] = minmaxs[pindex[3 + 2]];

#if CLIP_PLANE_USES_FLOAT
            d = DotProduct(acceptpt, _g->view_clipplanes[i].normal);
            d -= _g->view_clipplanes[i].dist;
#else
			d = DotProduct (acceptpt, view_clipplanes[i].frac_normal);
			d -= view_clipplanes[i].frac_dist;
#endif

            if (d <= 0)
                clipflags |= (1 << i);
        }
    }

    return clipflags;
}

/*
 =============
 R_DrawBEntitiesOnList
 =============
 */
#if !MARK_NODE_IN_SURFACE
extern byte surfdlightVisited[MAX_SURFACES/8];
#endif
void R_DrawBEntitiesOnList(void)
{
    int i, j, k, clipflags;
    vec3_t oldorigin;
    model_t *clmodel;
    float minmaxs[6];

    if (!r_drawentities)
        return;

    VectorCopy(_g->modelorg, oldorigin);
    _g->insubmodel = true;
#if USING_R_DLIGHTFRAMECOUNT
	r_dlightframecount = r_framecount;
#endif
    for (i = 0; i < _g->cl_numvisedicts; i++)
    {
#if POINTER_CL_VISEDICT
    		currententity = cl_visedicts[i];
#else
        _g->currententity = &cl_entities[_g->cl_visedicts[i]];
#endif
        clmodel = getEntityModel(_g->currententity);

        switch (clmodel->type)
        {
            case mod_brush:
                // see if the bounding box lets us trivially reject, also sets
                // trivial accept status
                for (j = 0; j < 3; j++)
                {
#if !ENTITY_HAS_SHORT_COORDS
				minmaxs[j] = currententity->origin[j] + clmodel->mins[j];
				minmaxs[3+j] = currententity->origin[j] + clmodel->maxs[j];
#else
#if MODEL_HAS_FLOAT_MINS_MAX
				minmaxs[j] = getEntityOrigin(currententity,j) + clmodel->mins[j];
				minmaxs[3+j] = getEntityOrigin(currententity,j) + clmodel->maxs[j];
#else
                    minmaxs[j] = getEntityOrigin(_g->currententity, j) + clmodel->mins_s[j];
                    minmaxs[3 + j] = getEntityOrigin(_g->currententity, j) + clmodel->maxs_s[j];

#endif

#endif
                }

                clipflags = R_BmodelCheckBBox(clmodel, minmaxs);

                if (clipflags != BMODEL_FULLY_CLIPPED)
                {
#if !ENTITY_HAS_SHORT_COORDS
				VectorCopy (currententity->origin, r_entorigin);
#else
                    VectorCopy(VEC(getEntityOrigins(_g->currententity)), _g->r_entorigin);
#endif
                    VectorSubtract(_g->r_origin, _g->r_entorigin, _g->modelorg);
                    // FIXME: is this needed?
                    VectorCopy(_g->modelorg, _g->r_worldmodelorg);
#if !SEPARATE_BRUSH_MODEL_DATA
				r_pcurrentvertbase = clmodel->vertexes;
#else
                    r_pcurrentvertbase = clmodel->brushModelData->vertexes;
#endif
                    // FIXME: stop transforming twice
                    R_RotateBmodel();

                    // calculate dynamic lighting for bmodel if it's not an
                    // instanced model
#if !SEPARATE_BRUSH_MODEL_DATA
				if (clmodel->firstmodelsurface != 0)
#else
                    if (clmodel->brushModelData->firstmodelsurface != 0)
#endif
                    {
                        for (k = 0; k < MAX_DLIGHTS; k++)
                        {
                            if ((_g->cl_dlights[k].die < _g->cl.time) || (!_g->cl_dlights[k].radius))
                            {
                                continue;
                            }
#if !SEPARATE_BRUSH_MODEL_DATA
						R_MarkLights (&cl_dlights[k], 1<<k, clmodel->nodes + clmodel->hulls[0].firstclipnode);
#else
                            R_MarkLights(&_g->cl_dlights[k], 1 << k, clmodel->brushModelData->nodes + clmodel->brushModelData->hulls[0].firstclipnode);
#endif
                        }
                    }

                    // if the driver wants polygons, deliver those. Z-buffering is on
                    // at this point, so no clipping to the world tree is needed, just
                    // frustum clipping
#if (r_drawpolys || r_drawculledpolys) // both false by default
				{
					R_ZDrawSubmodelPolys (clmodel);
				}
				#else
                    {
                        r_pefragtopnode = NULL;

                        for (j = 0; j < 3; j++)
                        {
                            r_emins[j] = minmaxs[j];
                            r_emaxs[j] = minmaxs[3 + j];
                        }
#if !SEPARATE_BRUSH_MODEL_DATA
					R_SplitEntityOnNode2 (cl.worldmodel->nodes);
#else
                        R_SplitEntityOnNode2(_g->cl.worldmodel->brushModelData->nodes);
#endif
                        if (r_pefragtopnode)
                        {
#if ENTITY_HAS_TOPNODE_POINTER
						currententity->topnode = r_pefragtopnode;
#else
                            setEntityTopnode(_g->currententity, r_pefragtopnode);
#endif
                            if (r_pefragtopnode->contents >= 0)
                            {
                                // not a leaf; has to be clipped to the world BSP
                                r_clipflags = clipflags;
                                R_DrawSolidClippedSubmodelPolygons(clmodel);
                            }
                            else
                            {
                                // falls entirely in one leaf, so we just put all the
                                // edges in the edge list and let 1/z sorting handle
                                // drawing order
                                R_DrawSubmodelPolygons(clmodel, clipflags);
                            }
#if ENTITY_HAS_TOPNODE_POINTER
						currententity->topnode = NULL;
#else
                            setEntityTopnode(_g->currententity, NULL);
#endif
                        }
                    }
#endif
                    // put back world rotation and frustum clipping
                    // FIXME: R_RotateBmodel should just work off base_vxx
                    VectorCopy(_g->base_vpn, _g->vpn);
                    VectorCopy(_g->base_vup, _g->vup);
                    VectorCopy(_g->base_vright, _g->vright);
                    VectorCopy(_g->base_modelorg, _g->modelorg);
                    VectorCopy(oldorigin, _g->modelorg);
                    R_TransformFrustum();
                }

                break;

            default:
                break;
        }
    }

    _g->insubmodel = false;
}

/*
 ================
 R_EdgeDrawing
 ================
 */

#if COPY_COLOR_MAP_TO_RAM
#define MIN_BUFFER_SIZE  (16384)
#else
#define MIN_BUFFER_SIZE ((SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT) * SCREEN_WIDTH)
#endif
void R_EdgeDrawing(void)
{

#if EDGES_IN_Z_BUFFER

    // make sure we are leaving space for the last part of the screen which might be under drawing
#if !EDGE_HAS_NEXTREMOVEIDX && !EDGE_POINTERS
    STATIC_ASSERT(
        sizeof(edge_t) * (NUMSTACKEDGES + 5) + 2 * sizeof(edge_t*) * MAXHEIGHT + NUMSTACKEDGES * 2 + sizeof(*_g->edgeNextRemoveIdx) *(((NUMSTACKEDGES + 5) + 1) & ~1) + MAX_MAP_LEAFS * sizeof(*_g->leafKey)<= sizeof(d_zbuffer) - MIN_BUFFER_SIZE);
    _g->edgeNextRemoveIdx = (uint16_t*) (((byte*) aux_buffer)
        - sizeof(*_g->edgeNextRemoveIdx) * (((NUMSTACKEDGES + 5) + 1) & ~1));
    fastMemclear32(_g->edgeNextRemoveIdx, sizeof(*_g->edgeNextRemoveIdx) * (((NUMSTACKEDGES + 5) + 1) & ~1) / 4);
    edge_t *ledges = (edge_t*) ((byte*) _g->edgeNextRemoveIdx - sizeof(edge_t) * (NUMSTACKEDGES + 5));
#else
    STATIC_ASSERT(
        sizeof(edge_t) * (NUMSTACKEDGES + 5) + 2 * sizeof(edge_t*) * MAXHEIGHT + NUMSTACKEDGES * 2 + MAX_MAP_LEAFS * sizeof(*_g->leafKey)<= sizeof(d_zbuffer) - MIN_BUFFER_SIZE);
    edge_t *ledges = (edge_t*) ((byte*) aux_buffer - sizeof(edge_t) * (NUMSTACKEDGES + 5));
#endif

    _g->newedges = (edge_t**) ((byte*) ledges - sizeof(edge_t*) * (MAXHEIGHT));   // these might be indexes
    _g->removeedges = _g->newedges - MAXHEIGHT;    // these might be indexes
    _g->edgeOwnwers = (uint16_t*) _g->removeedges - NUMSTACKEDGES;
    fastMemclear32(_g->edgeOwnwers, NUMSTACKEDGES / 2);
#if !LEAF_KEY_IN_AUX_RAM
    _g->leafKey = (short*) _g->edgeOwnwers - MAX_MAP_LEAFS;    // note: this can be trashed when doing scanEdge.
#endif
#else
    #error code supports edge in Z-buffer only!
#endif
    surf_t lsurfs[NUMSTACKSURFACES];

        _g->base_edge_p = &ledges[0];
        _g->r_edges = (edge_t*) &ledges[1];
        _g->edge_head = &ledges[NUMSTACKEDGES + 1];
        _g->edge_tail = &ledges[NUMSTACKEDGES + 2];
        _g->edge_aftertail = &ledges[NUMSTACKEDGES + 3];
        _g->edge_sentinel = &ledges[NUMSTACKEDGES + 4];
// TODO: we should clean up. Why are we using 2 surfs base pointer?
    // next-hack: added this to prevent compiler complaining a pointer is outside bounds
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    _g->base_surf_p = &lsurfs[0] - 1;
#pragma GCC diagnostic pop
    _g->surfaces = _g->base_surf_p;
    _g->surf_max = &lsurfs[NUMSTACKSURFACES];
    for (int i = 0; i < NUMSTACKSURFACES; i++)
    {
        lsurfs[i].surfIndex = i + 1;
    }
    R_BeginEdgeFrame();
#if PROFILE_SPEED
	if (r_dspeeds)
	{
		rw_time1 = Sys_FloatTime ();
	}
#endif
    // clear surface buffer used temporarily to store cachededgesoffets
    fastMemclear32(getTextureCacheBuffer(), MAX_TEXTURE_SIZE / 4);

    R_RenderWorld();

#if r_drawculledpolys
		R_ScanEdges ();
#endif
// only the world can be drawn back to front with no z reads or compares, just
// z writes, so have the driver turn z compares on now
    D_TurnZOn();
#if PROFILE_SPEED
	if (r_dspeeds)
	{
		rw_time2 = Sys_FloatTime ();
		db_time1 = rw_time2;
	}
#endif
    R_DrawBEntitiesOnList();
#if PROFILE_SPEED

	if (r_dspeeds)
	{
		db_time2 = Sys_FloatTime ();
		se_time1 = db_time2;
	}
#endif
    if (!r_dspeeds)
    {
        VID_UnlockBuffer ();
        S_ExtraUpdate();	// don't let sound get messed up if going slow
        VID_LockBuffer ();
    }

    if (!(r_drawpolys | r_drawculledpolys)) // both false, so this is done
        R_ScanEdges();
}

/*
 ================
 R_RenderView

 _g->r_refdef must be set before the first call
 ================
 */
void R_RenderView_(void)
{
#if WARP_HAS_DIFFERENT_RESOLUTION
    // next-hack: WTF?!?!?
	byte	warpbuffer[WARP_WIDTH * WARP_HEIGHT];

	r_warpbuffer = warpbuffer;
#endif
#if PROFILE_SPEED
	if (r_timegraph || r_speeds || r_dspeeds)
		r_time1 = Sys_FloatTime ();
#endif
    R_SetupFrame();

#ifdef PASSAGES
SetVisibilityByPassages ();
#else
    R_MarkLeaves();	// done here so we know if we're in water
    // next-hack: R_MarkLeaves will call Mod_LeafPVS() which will call Mod_DecompressVis() function, which uses a temporary buffer, "decompressed"
    // which is (allocated in the zbuffer). However, after the R_MarkLeaves() call, such buffer is not used, so it is safe to overwrite such temporary buffer.
#if STATIC_ENTITY_SUPPORT
    // next-hack: added this one, so that we can support static entities
    if (_g->cls.demoplayback)
    {
        for (int entityIdx = MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES - _g->cl.num_statics; entityIdx < MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES; entityIdx++)
        {
            entLeaves_t *el = &_g->client_entity_data[entityIdx].entLeaves;
            for (int leafIdx = 0; leafIdx < el->num_leaves; leafIdx++)
            {
                int leaf = el->leafnums[leafIdx];
                if (_g->visleaves[leaf / 8] & (1 << (leaf % 8)))
                {
                    // add entity
                    _g->cl_visedicts[_g->cl_numvisedicts] = entityIdx;
                    _g->cl_numvisedicts++;
                    break;
                }
            }
        }
    }
#endif
#endif

// make FDIV fast. This reduces timing precision after we've been running for a
// while, so we don't do it globally.  This also sets chop mode, and we do it
// here so that setup stuff like the refresh area calculations match what's
// done in screen.c
#if WIN32
	Sys_LowFPPrecision ();
#endif
    if (!getEntityModel(&cl_entities[0]) || !_g->cl.worldmodel)
        Sys_Error("R_RenderView: NULL worldmodel");

    if (!r_dspeeds)
    {
        VID_UnlockBuffer ();
        S_ExtraUpdate();	// don't let sound get messed up if going slow
        VID_LockBuffer ();
    }
    R_EdgeDrawing();

    if (!r_dspeeds)
    {
        VID_UnlockBuffer ();
        S_ExtraUpdate();	// don't let sound get messed up if going slow
        VID_LockBuffer ();
    }
#if PROFILE_SPEED

	if (r_dspeeds)
	{
		se_time2 = Sys_FloatTime ();
		de_time1 = se_time2;
	}
#endif
    R_DrawEntitiesOnList();
#if PROFILE_SPEED
	if (r_dspeeds)
	{
		de_time2 = Sys_FloatTime ();
		dv_time1 = de_time2;
	}
#endif
    R_DrawViewModel();
#if PROFILE_SPEED
	if (r_dspeeds)
	{
		dv_time2 = Sys_FloatTime ();
		dp_time1 = Sys_FloatTime ();
	}
#endif
    R_DrawParticles();
#if PROFILE_SPEED
	if (r_dspeeds)
		dp_time2 = Sys_FloatTime ();
#endif
    if (r_dowarp)
        D_WarpScreen();

    V_SetContentsColor(r_viewleaf->contents);
#if PROFILE_SPEED
	if (r_timegraph)
		R_TimeGraph ();

	if (r_aliasstats)
		R_PrintAliasStats ();

	if (r_speeds)
		R_PrintTimes ();

	if (r_dspeeds)
		R_PrintDSpeeds ();
#endif
#if WIN32
    if (r_reportsurfout && r_outofsurfaces)
        Con_Printf("Short %d surfaces\n", r_outofsurfaces);

    if (r_reportedgeout && r_outofedges)
        Con_Printf("Short roughly %d edges\n", r_outofedges * 2 / 3);

// back to high floating-point precision
	Sys_HighFPPrecision ();
#endif
   char frameratestring[10];
   if (showfps)
   {
       snprintf(frameratestring, sizeof(frameratestring), "%u.%u", (unsigned int) _g->fps10/10, (unsigned int) _g->fps10 % 10);
       Draw_String(0, DRAW_BUFFER_HEIGHT - 8, frameratestring);
   }
}

void R_RenderView(void)
{

    R_RenderView_();
}

/*
 ================
 R_InitTurb
 ================
 */
void R_InitTurb(void)
{
#if RUNTIME_TABLES
	int		i;

	for (i=0 ; i<(SIN_BUFFER_SIZE) ; i++)
	{
		sintable[i] = AMP + sin_t(i*3.14159*2/CYCLE)*AMP;

		intsintable[i] = AMP2 + sin_t(i*3.14159*2/CYCLE)*AMP2 ;	// AMP2, not 20
	}
#endif
}

