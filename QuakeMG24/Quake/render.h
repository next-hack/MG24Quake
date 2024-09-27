/*
 Copyright (C) 1996-1997 Id Software, Inc.

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

// refresh.h -- public interface to refresh functions
#define	MAXCLIPPLANES	11

#define	TOP_RANGE		16			// soldier uniform colors
#define	BOTTOM_RANGE	96

//=============================================================================
#if DIRECT_SINGLE_PLAYER
typedef struct efrag_s
{
	struct mleaf_s		*leaf;
	struct efrag_s		*leafnext;
	struct entity_s		*entity;
	struct efrag_s		*entnext;
} efrag_t;
#endif
typedef enum
{
    // next-hack: to support unified edict-entity
    TYPE_CLIENT_ENTITY,     // when playing demos
    TYPE_EDICT_ENTITY,      // when hosting a game
    TYPE_TEMP_ENTITY,       // temp entities, weapon, and client entity.
    TYPE_MAX_ENTITIES,
} entity_type_t;
#define SYNCBASE_BITS 11
typedef struct entity_s
{
#define ENTITY_HAS_DATA 1
//	int						update_type;   // next-hack: not used :O
#if ENTITY_HAS_DATA
    void *data;             // this is a pointer either to an edict or to an entity
#endif
// data that will be still used for client drawing purposes, regardless if it is demo or regular play
#if FLOAT_SYNCBASE
	float					syncbase;		// for client-side animations
#else
    unsigned short syncbase_s :SYNCBASE_BITS;		// for client-side animations
#endif
    unsigned short entityType :2;
    unsigned short mustBeDrawn :1;      // this will be used to return NULL model
    unsigned short trivial_accept :2;
#if ENTITY_HAS_TOPNODE_POINTER
	struct mnode_s			*topnode;		// for bmodels, first world node
											//  that splits bmodel, or NULL if
											//  not split
#else
    union
    {
        struct
        {
            uint16_t nodeIdx :15;             // for bmodels, first world node that splits bmodel, 0 if not split
            uint16_t isNode :1;               //
        };
        uint16_t topnodeIdx;
    };
#endif
} entity_t;
#if !ENTITY_HAS_DATA
#error too bad edict have no array.
void *getEntityData(entity_t *e)
{
    int index = e - cl_entities[0];
    switch(e->entityType)
    {
    case TYPE_CLIENT_ENTITY:
        return &client_entity_data[index];
    break;
    case TYPE_EDICT_ENTITY:
        return &edic[index];
    break;
    case TYPE_TEMP_ENTITY:
    break;
    }
    return NULL;
}
#endif
typedef struct client_entity_s
{
    entity_state_t baseline;		// to fill in defaults in updates [16 bytes]
    /* next-hack: let's comment a little bit. efrag is entity fragment, which is only used by static entities. Static entities are not present on the server,
     but only on client side. We might get rid of all this not using static entities at all.
     */
    QDFLOAT msgtime;		// time of last update
#if !ENTITIES_HAVE_LINEAR_INT
#if !ENTITY_HAS_SHORT_COORDS
    vec3_t msg_origins[2];	// last two updates (0 is newest)
    vec3_t msg_angles[2];	// last two updates (0 is newest)
#else
    short                   msg_origins_s[2][3];
    ANGLE_SHORT_TYPE                   msg_angles_s[2][3];
#endif
#endif
#if ENTITY_HAS_SHORT_COORDS
    short                   origin_s[3];
    ANGLE_SHORT_TYPE                    angles_s[3];
#else
    vec3_t origin;
    vec3_t angles;
#endif // ENTITY_HAS_SHORT_COORDS
//	struct model_s			*model;			// NULL = no model
#if !DIRECT_SINGLE_PLAYER
    struct efrag_s *efrag;			// linked list of efrags
#endif
    unsigned int frame :8;      // fix! should have at least up to 255 frames (no signed!)
    int skinnum :8;		// for Alias models
    int modelIdx :9;			// -1 = no model
    int effects :4;		// light, particals, etc. For Q2 is 8 bit, can be 4 in Q1
    int trivial_accept :2; // TBD
    int forcelink :1;		// model changed

#if HAS_MULTIPLAYER
	byte					*colormap;      // next-hack: in single player this is basically always vid.colormap.
#endif
#if STATIC_ENTITY_SUPPORT
    entLeaves_t entLeaves;
#endif // STATIC_ENTITY_SUPPORT
} client_entity_t;
//
#if 1
typedef struct temp_entity_s
{
#if ENTITY_HAS_SHORT_COORDS
    short                   origin_s[3];
    ANGLE_SHORT_TYPE                    angles_s[3];
#else
    vec3_t origin;
    vec3_t angles;
#endif // ENTITY_HAS_SHORT_COORDS
#if !DIRECT_SINGLE_PLAYER
    struct efrag_s *efrag;			// linked list of efrags
#endif
    int frame :8;
    int skinnum :8;		// for Alias models
    int modelIdx :9;			// -1 = no model
    int effects :4;		// light, particals, etc. For Q2 is 8 bit, can be 4 in Q1
    int trivial_accept :2;
    int forcelink :1;		// model changed
#if HAS_MULTIPLAYER
	byte					*colormap;      // next-hack: in single player this is basically always vid.colormap.
#endif
} temp_entity_t;
#endif
// !!! if this is changed, it must be changed in asm_draw.h too !!!
typedef struct
{
    vrect_t vrect;				// subwindow in video for refresh
                                // FIXME: not need vrect next field here?
    vrect_t aliasvrect;			// scaled Alias version
    int vrectright, vrectbottom;	// right & bottom screen coords
    int aliasvrectright, aliasvrectbottom;	// scaled Alias versions
    float vrectrightedge;			// rightmost right edge we care about,
                                    //  for use in edge list
    float fvrectx, fvrecty;		// for floating-point compares
    float fvrectx_adj, fvrecty_adj; // left and top edges, for clamping
    int vrect_x_adj_shift20;	// (vrect.x + 0.5 - epsilon) << 20
    int vrectright_adj_shift20;	// (vrectright + 0.5 - epsilon) << 20
    float fvrectright_adj, fvrectbottom_adj;
    // right and bottom edges, for clamping
    float fvrectright;			// rightmost edge, for Alias clamping
    float fvrectbottom;			// bottommost edge, for Alias clamping
    float horizontalFieldOfView;	// at Z = 1.0, this many X is visible
                                    // 2.0 = 90 degrees
    float xOrigin;			// should probably allways be 0.5
    float yOrigin;			// between be around 0.3 to 0.5

    vec3_t vieworg;
    vec3_t viewangles;

    float fov_x, fov_y;

    int ambientlight;
} refdef_t;

//
// refresh
//
extern int reinit_surfcache;

//extern	refdef_t	r_refdef;
//extern vec3_t	r_origin, vpn, vright, vup;

extern struct texture_s *r_notexture_mip;

void R_Init(void);
void R_InitTextures(void);
void R_InitEfrags(void);
void R_RenderView(void);		// must set r_refdef first
void R_ViewChanged(vrect_t *pvrect, int lineadj, float aspect);
// called whenever r_refdef or vid change
void R_InitSky(struct texture_s *mt);	// called at level load

void R_AddEfrags(entity_t *ent);
void R_RemoveEfrags(entity_t *ent);

void R_NewMap(void);

void R_ParseParticleEffect(void);
void R_RunParticleEffect(vec3_t org, vec3_t dir, int color, int count);
void R_RocketTrail(vec3_t start, vec3_t end, int type);

#ifdef QUAKE2
void R_DarkFieldParticles (entity_t *ent);
#endif
void R_EntityParticles(entity_t *ent);
void R_BlobExplosion(vec3_t org);
void R_ParticleExplosion(vec3_t org);
void R_ParticleExplosion2(vec3_t org, int colorStart, int colorLength);
void R_LavaSplash(vec3_t org);
void R_TeleportSplash(vec3_t org);

void R_PushDlights(void);

//
// surface cache related
//
extern int reinit_surfcache;	// if 1, surface cache is currently empty and
extern qboolean r_cache_thrash;	// set if thrashing the surface cache

int D_SurfaceCacheForRes(int width, int height);
void D_FlushCaches(void);
void D_DeleteSurfaceCache(void);
void D_InitCaches(void *buffer, int size);
void R_SetVrect(vrect_t *pvrect, vrect_t *pvrectin, int lineadj);

