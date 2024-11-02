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
// d_iface.h: interface header file for rasterization driver modules
#ifndef D_IFACE_H
#define D_IFACE_H
#define WARP_WIDTH		320
#define WARP_HEIGHT		200

#define MAX_LBM_HEIGHT	480

typedef struct
{
    float u, v;
    float s, t;
    float zi;
} emitpoint_t;

typedef enum
{
    pt_static = 0, pt_grav, pt_slowgrav, pt_fire, pt_explode, pt_explode2, pt_blob, pt_blob2
} ptype_t;
// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define NO_MINIMIZE_PARTICLES 0
#define COPY_PARTICLES_TO_TEXTURE_BUFFER            0
typedef struct particle_s
{
#if NO_MINIMIZE_PARTICLES

// driver-usable fields
	vec3_t		org;
	float		color;  // can be uint8_t

// drivers never touch the following fields
	struct particle_s	*next;      // will be short ptr
	vec3_t		vel;
	float		ramp;
	float		die;
	ptype_t		type;
#else
// driver-usable fields
#define PART_HAS_FLOAT_ORG 0
#if PART_HAS_FLOAT_ORG
	vec3_t		org;
#else
    short org16[3];
#endif
    uint8_t color;  // can be uint8_t

    uint8_t fixed_ramp;           // max is 8. Frame time is larger than 0.01. And time1 is typically at least 0.05.

    uint32_t fixed_die :16;      // die must have 0.01 resolution and max is 5
    int32_t vel0 :16;            // can be 14 bits

    int32_t vel2 :14;
    int32_t vel1 :14;
    uint32_t type :3;           // can be uint8_t:3 bits.
    uint32_t inUse :1;
#endif

} particle_t;
#define PARTICLE_VEL_FRAC_SHIFT             3
#define defineParticleVelSetterGetter(number) \
static inline void setParticleVel##number(particle_t *p, float v)   \
{   \
    p->vel##number = v * (1 << PARTICLE_VEL_FRAC_SHIFT);\
}   \
static inline float getParticleVel##number(particle_t *p)   \
{   \
    return p->vel##number * (1.0f / (1 << PARTICLE_VEL_FRAC_SHIFT));\
}
defineParticleVelSetterGetter(0);
defineParticleVelSetterGetter(1);
defineParticleVelSetterGetter(2);

#define PARTICLE_Z_CLIP	8.0f

typedef struct polyvert_s
{
    float u, v, zi, s, t;
} polyvert_t;

typedef struct polydesc_s
{
    int numverts;
    float nearzi;
    msurface_t *pcurrentface;
    polyvert_t *pverts;
} polydesc_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct finalvert_s
{
    int v[6];		// u, v, s, t, l, 1/z
    int flags;
#if NO_MINIMIZE
	float	reserved;
#else
//	int tri;        // next-hack any triangle this belongs to.
#endif
} finalvert_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct
{
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
	void				*pskin;
	byte *				*pOriginalskin;

	#endif
    maliasskindesc_t *pskindesc;
    int skinwidth;
    int skinheight;
    mtriangle_t *ptriangles;
    finalvert_t *pfinalverts;
    int numtriangles;
    int drawtype;
    int seamfixupX16;
    //
    int triangleSize;
    mtriangle_t *tempTriangleBuffer;
    void *tempTriangleOffsetData;
    void *tempAnimVertsBuffer;
    byte *tempTrianglePixBuffer;

#if !NO_MINIMIZE
    aliashdr_t *paliashdr;
#endif
} affinetridesc_t;

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
typedef struct
{
    float u, v, zi, color;
} screenpart_t;

typedef struct
{
    int nump;
    emitpoint_t *pverts;	// there's room for an extra element at [nump],
                            //  if the driver wants to duplicate element [0] at
                            //  element [nump] to avoid dealing with wrapping
    mspriteframe_t *pspriteframe;
    vec3_t vup, vright, vpn;	// in worldspace
    float nearzi;
} spritedesc_t;

typedef struct
{
    int u, v;
    float zi;
    int color;
} zpointdesc_t;
#if USE_ORIGINAL_CVAR
extern cvar_t	r_drawflat;
#endif
extern int d_spanpixcount;
extern int r_framecount;		// sequence # of current frame since Quake
                                //  started
//extern qboolean	r_drawpolys;		// 1 if driver wants clipped polygons
//  rather than a span list
//extern qboolean	r_drawculledpolys;	// 1 if driver wants clipped polygons that
//  have been culled by the edge list
//extern qboolean	r_worldpolysbacktofront;	// 1 if driver wants polygons
//  delivered back to front rather
//  than front to back
extern qboolean r_recursiveaffinetriangles;	// true if a driver wants to use
                                            //  recursive triangular subdivison
                                            //  and vertex drawing via
                                            //  D_PolysetDrawFinalVerts() past
                                            //  a certain distance (normally
                                            //  only used by the software
                                            //  driver)
#define CONSTANT_VIDEO_VALUES 1
#if CONSTANT_VIDEO_VALUES
#define	r_aliasuvscale 1		// scale-up factor for screen u and v
//  on Alias vertices passed to driver
#define pixelAspect (((float)SCREEN_HEIGHT / (float)SCREEN_WIDTH) * (320.0f / 240.0f))
#define xcenter (SCREEN_WIDTH / 2 - 0.5f)
#define aliasxcenter (xcenter * r_aliasuvscale)
#define ycenter (DRAW_BUFFER_HEIGHT / 2 - 0.5f)
#define aliasycenter (ycenter * r_aliasuvscale)
#define xscale (SCREEN_WIDTH / 2)
#define aliasxscale (r_aliasuvscale * xscale)
#define xscaleinv (1.0f / xscale)
#define yscale  (xscale * pixelAspect)
#define aliasyscale  (yscale * r_aliasuvscale)
#define yscaleinv  (1.0f / yscale)
#define	r_pixbytes 1
#endif
extern qboolean r_dowarp;

//extern affinetridesc_t	r_affinetridesc;
extern spritedesc_t r_spritedesc;
//extern zpointdesc_t		r_zpointdesc;

extern int d_con_indirect;	// if 0, Quake will draw console directly
                            //  to vid.buffer; if 1, Quake will
                            //  draw console via D_DrawRect. Must be
                            //  defined by driver

extern vec3_t r_pright, r_pup, r_ppn;

void D_Aff8Patch(void *pcolormap);
void D_BeginDirectRect(int x, int y, byte *pbitmap, int width, int height);
void D_DisableBackBufferAccess(void);
void D_EndDirectRect(int x, int y, int width, int height);
void D_PolysetDraw(void);

void D_PolysetDrawFinalVerts(finalvert_t *fv, int numverts);

void D_DrawParticle(const particle_t *pparticle);
void D_DrawPoly(void);
void D_DrawSprite(void);
void D_DrawSurfaces(void);
void D_DrawZPoint(void);
void D_EnableBackBufferAccess(void);
void D_EndParticles(void);
void D_Init(void);
void D_ViewChanged(void);
void D_SetupFrame(void);
void D_StartParticles(void);
void D_TurnZOn(void);
void D_WarpScreen(void);

void D_FillRect(vrect_t *vrect, int color);
void D_DrawRect(void);
void D_UpdateRects(vrect_t *prect);

// currently for internal use only, and should be a do-nothing function in
// hardware drivers
// FIXME: this should go away
void D_PolysetUpdateTables(void);

// these are currently for internal use only, and should not be used by drivers
extern byte *r_skysource;

// transparency types for D_DrawRect ()
#define DR_SOLID		0
#define DR_TRANSPARENT	1

// !!! must be kept the same as in quakeasm.h !!!
#define TRANSPARENT_COLOR	0xFF

//extern void *acolormap;	// FIXME: should go away

//=======================================================================//

// callbacks to Quake

typedef struct
{
//	pixel_t		*surfdat;	// destination for generated surface
    //int			rowbytes;	// destination logical width in bytes
    msurface_t *surf;		// description for surface to generate
    fixed8_t lightadj[MAXLIGHTMAPS];
    // adjust for lightmap levels for dynamic lighting
    texture_t *texture;	// corrected for animating textures
    int surfmip;	// mipmapped ratio of surface texels / world pixels
    int surfwidth;	// in mipmapped texels
    int surfheight;	// in mipmapped texels
} drawsurf_t;

extern drawsurf_t r_drawsurf;

void R_DrawSurface(void);
void R_GenTile(msurface_t *psurf, void *pdest);

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define TURB_TEX_SIZE	64		// base turbulent texture size

// !!! if this is changed, it must be changed in d_ifacea.h too !!!
#define	CYCLE			128		// turbulent cycle size

#define TILE_SIZE		128		// size of textures generated by R_GenTiledSurf

#define SKYSHIFT		7
#define	SKYSIZE			(1 << SKYSHIFT)
#define SKYMASK			(SKYSIZE - 1)

extern float skyspeed, skyspeed2;
extern float skytime;
#if PROFILE_SPEED
extern int		c_surf, pixLoaded, singlePixelLoaded, pixSaved;
extern int      pixAlias;
extern float       pixLoadMicrosecs;
#endif
extern vrect_t scr_vrect;
#if WARP_HAS_DIFFERENT_RESOLUTION
extern byte		*r_warpbuffer;
#endif
#endif
