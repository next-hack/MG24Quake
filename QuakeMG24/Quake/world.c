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
// world.c -- world query functions
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
/*

 entities never clip against themselves, or their owner

 line of sight checks trace->crosscontent, but bullets don't

 */

typedef struct
{
    vec3_t boxmins, boxmaxs; // enclose the test object along entire move
    float *mins, *maxs;	// size of the moving object
    vec3_t mins2, maxs2;	// size when clipping against mosnters
    float *start, *end;
    trace_t trace;
    int type;
    edict_t *passedict;
} moveclip_t;

int SV_HullPointContents(hull_t *hull, int num, vec3_t p);

/*
 ===============================================================================

 HULL BOXES

 ===============================================================================
 */

static hull_t box_hull;
static dclipnode_t box_clipnodes[6];
static mplane_t box_planes[6];

/*
 ===================
 SV_InitBoxHull

 Set up the planes and clipnodes so that the six floats of a bounding box
 can just be stored out and get a proper hull_t structure.
 ===================
 */
void SV_InitBoxHull(void)
{
    int i;
    int side;

    box_hull.clipnodes = box_clipnodes;
    box_hull.planes = box_planes;
    box_hull.firstclipnode = 0;
    box_hull.lastclipnode = 5;

    for (i = 0; i < 6; i++)
    {
        box_clipnodes[i].planenum = i;

        side = i & 1;

        box_clipnodes[i].children[side] = CONTENTS_EMPTY;
        if (i != 5)
            box_clipnodes[i].children[side ^ 1] = i + 1;
        else
            box_clipnodes[i].children[side ^ 1] = CONTENTS_SOLID;

        box_planes[i].type = i >> 1;
        box_planes[i].normal[i >> 1] = 1;
    }

}

/*
 ===================
 SV_HullForBox

 To keep everything totally uniform, bounding boxes are turned into small
 BSP trees instead of being compared directly.
 ===================
 */
hull_t* SV_HullForBox(vec3_t mins, vec3_t maxs)
{
    setPlaneDist(&box_planes[0], maxs[0]);
    setPlaneDist(&box_planes[1], mins[0]);
    setPlaneDist(&box_planes[2], maxs[1]);
    setPlaneDist(&box_planes[3], mins[1]);
    setPlaneDist(&box_planes[4], maxs[2]);
    setPlaneDist(&box_planes[5], mins[2]);

    return &box_hull;
}

/*
 ================
 SV_HullForEntity

 Returns a hull that can be used for testing or clipping an object of mins/maxs
 size.
 Offset is filled in to contain the adjustment that must be added to the
 testing object's origin to get a point to use with the returned hull.
 ================
 */
hull_t* SV_HullForEntity(edict_t *ent, vec3_t mins, vec3_t maxs, vec3_t offset)
{
    model_t *model;
    vec3_t size;
    vec3_t hullmins, hullmaxs;
    hull_t *hull;

// decide which clipping hull to use, based on the size
    if (get_qcc_solid(ent) == SOLID_BSP)
    {	// explicit hulls in the BSP model
        if (get_qcc_movetype(ent) != MOVETYPE_PUSH)
            Sys_Error("SOLID_BSP without MOVETYPE_PUSH");

        model = sv.models[(int) get_qcc_modelindex(ent)];

        if (!model || model->type != mod_brush)
            Sys_Error("MOVETYPE_PUSH with a non bsp model");

        VectorSubtract(maxs, mins, size);
#if !SEPARATE_BRUSH_MODEL_DATA
		if (size[0] < 3)
			hull = &model->hulls[0];
		else if (size[0] <= 32)
			hull = &model->hulls[1];
		else
			hull = &model->hulls[2];
#else
        if (size[0] < 3)
            hull = &model->brushModelData->hulls[0];
        else if (size[0] <= 32)
            hull = &model->brushModelData->hulls[1];
        else
            hull = &model->brushModelData->hulls[2];

#endif
// calculate an offset value to center the origin
        VectorSubtract(hull->clip_mins, mins, offset);
        VectorAdd(offset, VEC(get_qcc_origin(ent)), offset);
    }
    else
    {	// create a temp hull from bounding box sizes

        VectorSubtract(VEC(get_qcc_mins(ent)), maxs, hullmins);
        VectorSubtract(VEC(get_qcc_maxs(ent)), mins, hullmaxs);
        hull = SV_HullForBox(hullmins, hullmaxs);

        VectorCopy(VEC(get_qcc_origin(ent)), offset);
    }

    return hull;
}

/*
 ===============================================================================

 ENTITY AREA CHECKING

 ===============================================================================
 */
// this can be optimized anyway.
typedef struct areanode_s
{
    int axis;		// -1 = leaf node
    float dist;
    struct areanode_s *children[2];
    link_t trigger_edicts;
    link_t solid_edicts;
} areanode_t;

#define	AREA_DEPTH	4
#define	AREA_NODES	((1 << (AREA_DEPTH + 1)) - 1)
#define GLOBAL_AREA_NODE 0
#if GLOBAL_AREA_NODE
static	areanode_t	sv_areanodes[AREA_NODES];
#else
static areanode_t *sv_areanodes = NULL;
#endif
static int sv_numareanodes;
// next-hack: utilities used for load/save games
void setAreaNode(void *areanode, int num)
{
    sv_areanodes = (areanode_t*) areanode;
    sv_numareanodes = num;
}
void* getAreaNode(void)
{
    return sv_areanodes;
}
int getNumAreaNodes(void)
{
    return sv_numareanodes;
}
/*
 ===============
 SV_CreateAreaNode

 ===============
 */
areanode_t* SV_CreateAreaNode(int depth, vec3_t mins, vec3_t maxs)
{
    areanode_t *anode;
    vec3_t size;
    vec3_t mins1, maxs1, mins2, maxs2;

    anode = &sv_areanodes[sv_numareanodes];
    sv_numareanodes++;
    if (sv_numareanodes > AREA_NODES)
        Sys_Error("Too many area nodes");
    ClearLink(&anode->trigger_edicts);
    ClearLink(&anode->solid_edicts);

    if (depth == AREA_DEPTH)
    {
        anode->axis = -1;
        anode->children[0] = anode->children[1] = NULL;
        return anode;
    }

    VectorSubtract(maxs, mins, size);
    if (size[0] > size[1])
        anode->axis = 0;
    else
        anode->axis = 1;

    anode->dist = 0.5 * (maxs[anode->axis] + mins[anode->axis]);
    VectorCopy(mins, mins1);
    VectorCopy(mins, mins2);
    VectorCopy(maxs, maxs1);
    VectorCopy(maxs, maxs2);

    maxs1[anode->axis] = mins2[anode->axis] = anode->dist;

    anode->children[0] = SV_CreateAreaNode(depth + 1, mins2, maxs2);
    anode->children[1] = SV_CreateAreaNode(depth + 1, mins1, maxs1);

    return anode;
}
areanode_t* SV_CreateAreaNode_s(int depth, short *mins_s, short *maxs_s)
{
    vec3_t mins, maxs;
    VectorCopy(mins_s, mins);
    VectorCopy(maxs_s, maxs);
    return SV_CreateAreaNode(depth, mins, maxs);
}
/*
 ===============
 SV_ClearWorld

 ===============
 */
void SV_ClearWorld(void)
{
    SV_InitBoxHull();
#if !GLOBAL_AREA_NODE
    if (!sv_areanodes)
    {
        sv_areanodes = Z_Calloc(sizeof(areanode_t) * AREA_NODES, 1, PU_STATIC, NULL);
    }
#endif // GLOBAL_AREA_NODE
    memset(sv_areanodes, 0, sizeof(areanode_t) * AREA_NODES);
    sv_numareanodes = 0;
#if MODEL_HAS_FLOAT_MINS_MAX
	SV_CreateAreaNode (0, sv.worldmodel->mins, sv.worldmodel->maxs);
#else
    SV_CreateAreaNode_s(0, sv.worldmodel->mins_s, sv.worldmodel->maxs_s);
#endif
}

/*
 ===============
 SV_UnlinkEdict

 ===============
 */
void SV_UnlinkEdict(edict_t *ent)
{
#if LINKS_USE_SHORT_PTR
    if (!ent->area.prev_sptr)
        return;		// not linked in anywhere
    RemoveLink(&ent->area);
    ent->area.prev_sptr = ent->area.next_sptr = 0;

#else
	if (!ent->area.prev)
		return;		// not linked in anywhere
	RemoveLink (&ent->area);
	ent->area.prev = ent->area.next = NULL;
#endif // LINKS_USE_SHORT_PTR

}

/*
 ====================
 SV_TouchLinks
 ====================
 */
void SV_TouchLinks(edict_t *ent, areanode_t *node)
{
    link_t *l, *next;
    edict_t *touch;
    int old_self, old_other;

// touch linked edicts
#if LINKS_USE_SHORT_PTR
    for (l = getStaticZoneLongPtr(node->trigger_edicts.next_sptr); l != &node->trigger_edicts; l = next)
    {
        next = getStaticZoneLongPtr(l->next_sptr);

#else
	for (l = node->trigger_edicts.next ; l != &node->trigger_edicts ; l = next)
	{
		next = l->next;

#endif // LINKS_USE_SHORT_PTR
        touch = EDICT_FROM_AREA(l);
        if (touch == ent)
            continue;
        if (!get_qcc_touch(touch) || get_qcc_solid(touch) != SOLID_TRIGGER)
            continue;

#if USE_OLD_ABS_CALLS
        if (VEC(get_qcc_absmin(ent))[0] > VEC(get_qcc_absmax(touch))[0]
            || VEC(get_qcc_absmin(ent))[1] > VEC(get_qcc_absmax(touch))[1]
            || VEC(get_qcc_absmin(ent))[2] > VEC(get_qcc_absmax(touch))[2]
            || VEC(get_qcc_absmax(ent))[0] < VEC(get_qcc_absmin(touch))[0]
            || VEC(get_qcc_absmax(ent))[1] < VEC(get_qcc_absmin(touch))[1]
            || VEC(get_qcc_absmax(ent))[2] < VEC(get_qcc_absmin(touch))[2] )
        continue;
#else
        vector absminEnt = get_qcc_absmin(ent);
        vector absmaxTouch = get_qcc_absmax(touch);

        if (absminEnt.x > absmaxTouch.x || absminEnt.y > absmaxTouch.y || absminEnt.z > absmaxTouch.z)
            continue;
        vector absminTouch = get_qcc_absmin(touch);
        vector absmaxEnt = get_qcc_absmax(ent);
        if (absmaxEnt.x < absminTouch.x || absmaxEnt.y < absminTouch.y || absmaxEnt.z < absminTouch.z)
            continue;
#endif
#if USE_PROGSDAT
		old_self = pr_global_struct->self;
		old_other = pr_global_struct->other;

		pr_global_struct->self = EDICT_TO_PROG(touch);
		pr_global_struct->other = EDICT_TO_PROG(ent);
		pr_global_struct->time = sv.time;
		PR_ExecuteProgram (get_qcc_touch(touch));

		pr_global_struct->self = old_self;
		pr_global_struct->other = old_other;
#else
        old_self = progs.qcc_self;
        old_other = progs.qcc_other;

        progs.qcc_self = EDICT_TO_PROG(touch);
        progs.qcc_other = EDICT_TO_PROG(ent);
        progs.qcc_time = sv.time;
        qcc_PR_ExecuteProgram(get_qcc_touch(touch));

        progs.qcc_self = old_self;
        progs.qcc_other = old_other;
#endif
    }

// recurse down both sides
    if (node->axis == -1)
        return;

    if ( VEC(get_qcc_absmax(ent))[node->axis] > node->dist)
        SV_TouchLinks(ent, node->children[0]);
    if ( VEC(get_qcc_absmin(ent))[node->axis] < node->dist)
        SV_TouchLinks(ent, node->children[1]);
}

/*
 ===============
 SV_FindTouchedLeafs

 ===============
 */
#if DO_FIND_TOUCHED_LEAVES_JIT < 2
void SV_FindTouchedLeafs (edict_t *ent, mnode_t *node)
{
	mplane_t	*splitplane;
	mleaf_t		*leaf;
	int			sides;
	int			leafnum;

	if (node->contents == CONTENTS_SOLID)
		return;

// add an efrag if the node is a leaf

	if ( node->contents < 0)
	{
            if (ent->num_leafs == MAX_ENT_LEAFS)
                return;

            leaf = (mleaf_t *)node;
            leafnum = leaf - sv.worldmodel->leafs - 1;

            ent->leafnums[ent->num_leafs] = leafnum;
            ent->num_leafs++;
            return;
	}

// NODE_MIXED

	splitplane = node->plane;
	sides = BOX_ON_PLANE_SIDE(VEC(get_qcc_absmin(ent)), VEC(get_qcc_absmax(ent)), splitplane);

// recurse down the contacted sides
	if (sides & 1)
		SV_FindTouchedLeafs (ent, node->children[0]);

	if (sides & 2)
		SV_FindTouchedLeafs (ent, node->children[1]);
}
#elif DO_FIND_TOUCHED_LEAVES_JIT == 2
short		global_leafnums[MAX_ENT_LEAFS];
uint8_t     global_num_leafs;
void SV_FindTouchedLeafs (edict_t *ent, mnode_t *node)
{
	mplane_t	*splitplane;
	mleaf_t		*leaf;
	int			sides;
	int			leafnum;

	if (node->contents == CONTENTS_SOLID)
		return;

// add an efrag if the node is a leaf

	if ( node->contents < 0)
	{
            if (global_num_leafs == MAX_ENT_LEAFS)
                return;

            leaf = (mleaf_t *)node;
#if !SEPARATE_BRUSH_MODEL_DATA
            leafnum = leaf - sv.worldmodel->leafs - 1;
#else
            leafnum = leaf - sv.worldmodel->brushModelData->leafs - 1;
#endif
            global_leafnums[global_num_leafs] = leafnum;
            global_num_leafs++;
            return;
	}

// NODE_MIXED

#if NODE_HAS_PLANE_POINTER
		splitplane = node->plane;
#else
        splitplane = Mod_GetNodePlane(node, sv.worldmodel);
#endif
	sides = BOX_ON_PLANE_SIDE(VEC(get_qcc_absmin(ent)), VEC(get_qcc_absmax(ent)), splitplane);

// recurse down the contacted sides
#if NODE_HAS_CHILDREN_POINTERS
	if (sides & 1)
		SV_FindTouchedLeafs (ent, node->children[0]);

	if (sides & 2)
		SV_FindTouchedLeafs (ent, node->children[1]);
#else
	if (sides & 1)
		SV_FindTouchedLeafs (ent, Mod_GetChildNode(node, 0, sv.worldmodel));

	if (sides & 2)
		SV_FindTouchedLeafs (ent, Mod_GetChildNode(node, 1, sv.worldmodel));

#endif
}
#elif DO_FIND_TOUCHED_LEAVES_JIT == 3
void SV_FindTouchedLeafs(edict_t *ent, mnode_t *node, entLeaves_t *el)
{
    mplane_t *splitplane;
    mleaf_t *leaf;
    int sides;
    int leafnum;

    if (node->contents == CONTENTS_SOLID)
        return;

// add an efrag if the node is a leaf

    if (node->contents < 0)
    {
        if (el->num_leaves == MAX_ENT_LEAFS)
            return;

        leaf = (mleaf_t*) node;
#if !SEPARATE_BRUSH_MODEL_DATA
            leafnum = leaf - sv.worldmodel->leafs - 1;
#else
        leafnum = leaf - sv.worldmodel->brushModelData->leafs - 1;
#endif
        el->leafnums[el->num_leaves] = leafnum;
        el->num_leaves++;
        return;
    }

// NODE_MIXED

#if NODE_HAS_PLANE_POINTER
    splitplane = node->plane;
#else
        splitplane = Mod_GetNodePlane(node, sv.worldmodel);
#endif
    sides = BOX_ON_PLANE_SIDE(VEC(get_qcc_absmin(ent)), VEC(get_qcc_absmax(ent)), splitplane);

// recurse down the contacted sides
#if NODE_HAS_CHILDREN_POINTERS
	if (sides & 1)
		SV_FindTouchedLeafs (ent, node->children[0], el);

	if (sides & 2)
		SV_FindTouchedLeafs (ent, node->children[1], el);
#else
    if (sides & 1)
        SV_FindTouchedLeafs(ent, Mod_GetChildNode(node, 0, sv.worldmodel), el);

    if (sides & 2)
        SV_FindTouchedLeafs(ent, Mod_GetChildNode(node, 1, sv.worldmodel), el);

#endif
}
#endif

/*
 ===============
 SV_LinkEdict

 ===============
 */
void SV_LinkEdict(edict_t *ent, qboolean touch_triggers)
{
    areanode_t *node;

#if LINKS_USE_SHORT_PTR
    if (ent->area.prev_sptr)
        SV_UnlinkEdict(ent);	// unlink from old position
#else
	if (ent->area.prev)
		SV_UnlinkEdict (ent);	// unlink from old position
	#endif // LINKS_USE_SHORT_PTR
    if (ent == sv.edicts)
        return;		// don't add the world
#if !EDICT_LINKED_LIST_WITH_WATCH
    if (ent->free)
        return;
#endif
// set the abs box

#ifdef QUAKE2
	if (ent->v.solid == SOLID_BSP &&
	(ent->v.angles[0] || ent->v.angles[1] || ent->v.angles[2]) )
	{	// expand for rotation
		float		max, v;
		int			i;

		max = 0;
		for (i=0 ; i<3 ; i++)
		{
			v =fabs( ent->v.mins[i]);
			if (v > max)
				max = v;
			v =fabs( ent->v.maxs[i]);
			if (v > max)
				max = v;
		}
		for (i=0 ; i<3 ; i++)
		{
			ent->v.absmin[i] = ent->v.origin[i] - max;
			ent->v.absmax[i] = ent->v.origin[i] + max;
		}
	}
	else
#endif
#if USE_ABS_MAXMIN
	{
	    vec3_t temp;
		VectorAdd (VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), temp);
		set_qcc_absmin(ent, vectorize(temp));
		VectorAdd (VEC(get_qcc_origin(ent)), VEC(get_qcc_maxs(ent)), temp);
		set_qcc_absmax(ent, vectorize(temp));

	}

//
// to make items easier to pick up and allow them to be grabbed off
// of shelves, the abs sizes are expanded
//

	if ((int)get_qcc_flags(ent) & FL_ITEM)
	{
		set_qcc_absmin_x(ent,  VEC(get_qcc_absmin(ent))[0] - 15);
		set_qcc_absmin_y(ent,  VEC(get_qcc_absmin(ent))[1] - 15);
		set_qcc_absmax_x(ent,  VEC(get_qcc_absmax(ent))[0] + 15);
		set_qcc_absmax_y(ent,  VEC(get_qcc_absmax(ent))[1] + 15);
	}
	else
	{	// because movement is clipped an epsilon away from an actual edge,
		// we must fully check even when bounding boxes don't quite touch
		set_qcc_absmin_x(ent,  VEC(get_qcc_absmin(ent))[0] - 1);
		set_qcc_absmin_y(ent,  VEC(get_qcc_absmin(ent))[1] - 1);
		set_qcc_absmin_z(ent,  VEC(get_qcc_absmin(ent))[2] - 1);
		set_qcc_absmax_x(ent,  VEC(get_qcc_absmax(ent))[0] + 1);
		set_qcc_absmax_y(ent,  VEC(get_qcc_absmax(ent))[1] + 1);
		set_qcc_absmax_z(ent,  VEC(get_qcc_absmax(ent))[2] + 1);
	}
#endif
#if !DO_FIND_TOUCHED_LEAVES_JIT
// link to PVS leafs
	ent->num_leafs = 0;
	if (get_qcc_modelindex(ent))
		SV_FindTouchedLeafs (ent, sv.worldmodel->nodes);
#elif DO_FIND_TOUCHED_LEAVES_JIT == 1
    ent->needs_relink = 1;
#elif DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t *el = get_entLeaves(ent);
    if (el)
    {
        el->needs_relink = 1;
    }
#endif
    if (get_qcc_solid(ent) == SOLID_NOT)
        return;

// find the first node that the ent's box crosses
    node = sv_areanodes;
    //
#if USE_OLD_ABS_CALLS
	while (1)
	{
		if (node->axis == -1)
			break;
		if (VEC(get_qcc_absmin(ent))[node->axis] > node->dist)
			node = node->children[0];
		else if (VEC(get_qcc_absmax(ent))[node->axis] < node->dist)
			node = node->children[1];
		else
			break;		// crosses the node
	}
#else
    if (node->axis != -1)
    {
        vector absmin = get_qcc_absmin(ent);
        vector absmax = get_qcc_absmax(ent);
        while (1)
        {
            if (node->axis == -1)
                break;
            if (absmin.v[node->axis] > node->dist)
                node = node->children[0];
            else if (absmax.v[node->axis] < node->dist)
                node = node->children[1];
            else
                break;    // crosses the node
        }
    }
#endif
// link it in

    if (get_qcc_solid(ent) == SOLID_TRIGGER)
        InsertLinkBefore(&ent->area, &node->trigger_edicts);
    else
        InsertLinkBefore(&ent->area, &node->solid_edicts);

// if touch_triggers, touch all entities at this node and decend for more
    if (touch_triggers)
        SV_TouchLinks(ent, sv_areanodes);
}

/*
 ===============================================================================

 POINT TESTING IN HULLS

 ===============================================================================
 */

#if	!id386

/*
 ==================
 SV_HullPointContents

 ==================
 */
int SV_HullPointContents(hull_t *hull, int num, vec3_t p)
{
    float d;
    dclipnode_t *node;
    mplane_t *plane;

    while (num >= 0)
    {
        if (num < hull->firstclipnode || num > hull->lastclipnode)
            Sys_Error("SV_HullPointContents: bad node number");

        node = hull->clipnodes + num;
        plane = hull->planes + node->planenum;

        if (plane->type < 3)
            d = p[plane->type] - getPlaneDist(plane);
        else
            d = DotProduct (plane->normal, p) - getPlaneDist(plane);
        if (d < 0)
            num = node->children[1];
        else
            num = node->children[0];
    }

    return num;
}

#endif	// !id386

/*
 ==================
 SV_PointContents

 ==================
 */
int SV_PointContents(vec3_t p)
{
    int cont;
#if !SEPARATE_BRUSH_MODEL_DATA
	cont = SV_HullPointContents (&sv.worldmodel->hulls[0], 0, p);
#else
    cont = SV_HullPointContents(&sv.worldmodel->brushModelData->hulls[0], 0, p);
#endif
    if (cont <= CONTENTS_CURRENT_0 && cont >= CONTENTS_CURRENT_DOWN)
        cont = CONTENTS_WATER;
    return cont;
}

int SV_TruePointContents(vec3_t p)
{
#if !SEPARATE_BRUSH_MODEL_DATA
	return SV_HullPointContents (&sv.worldmodel->hulls[0], 0, p);
#else
    return SV_HullPointContents(&sv.worldmodel->brushModelData->hulls[0], 0, p);
#endif
}

//===========================================================================

/*
 ============
 SV_TestEntityPosition

 This could be a lot more efficient...
 ============
 */
edict_t* SV_TestEntityPosition(edict_t *ent)
{
    trace_t trace;

    trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), VEC(get_qcc_origin(ent)), 0, ent);

    if (trace.startsolid)
        return sv.edicts;

    return NULL;
}

/*
 ===============================================================================

 LINE TESTING IN HULLS

 ===============================================================================
 */

// 1/32 epsilon to keep floating point happy
#define	DIST_EPSILON	(0.03125)

/*
 ==================
 SV_RecursiveHullCheck

 ==================
 */
qboolean SV_RecursiveHullCheck(hull_t *hull, int num, float p1f, float p2f, vec3_t p1, vec3_t p2, trace_t *trace)
{
    dclipnode_t *node;
    mplane_t *plane;
    float t1, t2;
    float frac;
    int i;
    vec3_t mid;
    int side;
    float midf;

// check for empty
    if (num < 0)
    {
        if (num != CONTENTS_SOLID)
        {
            trace->allsolid = false;
            if (num == CONTENTS_EMPTY)
                trace->inopen = true;
            else
                trace->inwater = true;
        }
        else
            trace->startsolid = true;
        return true;		// empty
    }

    if (num < hull->firstclipnode || num > hull->lastclipnode)
        Sys_Error("SV_RecursiveHullCheck: bad node number");

//
// find the point distances
//
    node = hull->clipnodes + num;
    plane = hull->planes + node->planenum;

    if (plane->type < 3)
    {
        float planedist = getPlaneDist(plane);
        t1 = p1[plane->type] - planedist;
        t2 = p2[plane->type] - planedist;
    }
    else
    {
        float planedist = getPlaneDist(plane);
        t1 = DotProduct (plane->normal, p1) - planedist;
        t2 = DotProduct (plane->normal, p2) - planedist;
    }

#if 1
    if (t1 >= 0 && t2 >= 0)
        return SV_RecursiveHullCheck(hull, node->children[0], p1f, p2f, p1, p2, trace);
    if (t1 < 0 && t2 < 0)
        return SV_RecursiveHullCheck(hull, node->children[1], p1f, p2f, p1, p2, trace);
#else
	if ( (t1 >= DIST_EPSILON && t2 >= DIST_EPSILON) || (t2 > t1 && t1 >= 0) )
		return SV_RecursiveHullCheck (hull, node->children[0], p1f, p2f, p1, p2, trace);
	if ( (t1 <= -DIST_EPSILON && t2 <= -DIST_EPSILON) || (t2 < t1 && t1 <= 0) )
		return SV_RecursiveHullCheck (hull, node->children[1], p1f, p2f, p1, p2, trace);
#endif

// put the crosspoint DIST_EPSILON pixels on the near side
    if (t1 < 0)
        frac = (t1 + DIST_EPSILON) / (t1 - t2);
    else
        frac = (t1 - DIST_EPSILON) / (t1 - t2);
    if (frac < 0)
        frac = 0;
    if (frac > 1)
        frac = 1;

    midf = p1f + (p2f - p1f) * frac;
    for (i = 0; i < 3; i++)
        mid[i] = p1[i] + frac * (p2[i] - p1[i]);

    side = (t1 < 0);

// move up to the node
    if (!SV_RecursiveHullCheck(hull, node->children[side], p1f, midf, p1, mid, trace))
        return false;

#ifdef PARANOID
	if (SV_HullPointContents (sv_hullmodel, mid, node->children[side])
	== CONTENTS_SOLID)
	{
		Con_Printf ("mid PointInHullSolid\n");
		return false;
	}
#endif

    if (SV_HullPointContents(hull, node->children[side ^ 1], mid) != CONTENTS_SOLID)
// go past the node
        return SV_RecursiveHullCheck(hull, node->children[side ^ 1], midf, p2f, mid, p2, trace);

    if (trace->allsolid)
        return false;		// never got out of the solid area

//==================
// the other side of the node is solid, this is the impact point
//==================
    if (!side)
    {
        VectorCopy(plane->normal, trace->plane.normal);
        trace->plane.dist = getPlaneDist(plane);
    }
    else
    {
        VectorSubtract(vec3_origin, plane->normal, trace->plane.normal);
        trace->plane.dist = -getPlaneDist(plane);
    }

    while (SV_HullPointContents(hull, hull->firstclipnode, mid) == CONTENTS_SOLID)
    { // shouldn't really happen, but does occasionally
        frac -= 0.1;
        if (frac < 0)
        {
            trace->fraction = midf;
            VectorCopy(mid, trace->endpos);
            Con_DPrintf("backup past 0\n");
            return false;
        }
        midf = p1f + (p2f - p1f) * frac;
        for (i = 0; i < 3; i++)
            mid[i] = p1[i] + frac * (p2[i] - p1[i]);
    }

    trace->fraction = midf;
    VectorCopy(mid, trace->endpos);

    return false;
}

/*
 ==================
 SV_ClipMoveToEntity

 Handles selection or creation of a clipping hull, and offseting (and
 eventually rotation) of the end points
 ==================
 */
trace_t SV_ClipMoveToEntity(edict_t *ent, vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end)
{
    trace_t trace;
    vec3_t offset;
    vec3_t start_l, end_l;
    hull_t *hull;

// fill in a default trace
    memset(&trace, 0, sizeof(trace_t));
    trace.fraction = 1;
    trace.allsolid = true;
    VectorCopy(end, trace.endpos);

// get the clipping hull
    hull = SV_HullForEntity(ent, mins, maxs, offset);

    VectorSubtract(start, offset, start_l);
    VectorSubtract(end, offset, end_l);

#ifdef QUAKE2
	// rotate start and end into the models frame of reference
	if (ent->v.solid == SOLID_BSP &&
	(ent->v.angles[0] || ent->v.angles[1] || ent->v.angles[2]) )
	{
		vec3_t	a;
		vec3_t	forward, right, up;
		vec3_t	temp;

		AngleVectors (ent->v.angles, forward, right, up);

		VectorCopy (start_l, temp);
		start_l[0] = DotProduct (temp, forward);
		start_l[1] = -DotProduct (temp, right);
		start_l[2] = DotProduct (temp, up);

		VectorCopy (end_l, temp);
		end_l[0] = DotProduct (temp, forward);
		end_l[1] = -DotProduct (temp, right);
		end_l[2] = DotProduct (temp, up);
	}
#endif

// trace a line through the apropriate clipping hull
    SV_RecursiveHullCheck(hull, hull->firstclipnode, 0, 1, start_l, end_l, &trace);

#ifdef QUAKE2
	// rotate endpos back to world frame of reference
	if (ent->v.solid == SOLID_BSP &&
	(ent->v.angles[0] || ent->v.angles[1] || ent->v.angles[2]) )
	{
		vec3_t	a;
		vec3_t	forward, right, up;
		vec3_t	temp;

		if (trace.fraction != 1)
		{
			VectorSubtract (vec3_origin, ent->v.angles, a);
			AngleVectors (a, forward, right, up);

			VectorCopy (trace.endpos, temp);
			trace.endpos[0] = DotProduct (temp, forward);
			trace.endpos[1] = -DotProduct (temp, right);
			trace.endpos[2] = DotProduct (temp, up);

			VectorCopy (trace.plane.normal, temp);
			trace.plane.normal[0] = DotProduct (temp, forward);
			trace.plane.normal[1] = -DotProduct (temp, right);
			trace.plane.normal[2] = DotProduct (temp, up);
		}
	}
#endif

// fix trace up by the offset
    if (trace.fraction != 1)
        VectorAdd(trace.endpos, offset, trace.endpos);

// did we clip the move?
    if (trace.fraction < 1 || trace.startsolid)
        trace.ent = ent;

    return trace;
}

//===========================================================================

/*
 ====================
 SV_ClipToLinks

 Mins and maxs enclose the entire area swept by the move
 ====================
 */
void SV_ClipToLinks(areanode_t *node, moveclip_t *clip)
{
    link_t *l, *next;
    edict_t *touch;
    trace_t trace;

// touch linked edicts
#if LINKS_USE_SHORT_PTR
    for (l = getStaticZoneLongPtr(node->solid_edicts.next_sptr); l != &node->solid_edicts; l = next)
    {
        next = getStaticZoneLongPtr(l->next_sptr);

#else
	for (l = node->solid_edicts.next ; l != &node->solid_edicts ; l = next)
	{
		next = l->next;

#endif // LINKS_USE_SHORT_PTR
        touch = EDICT_FROM_AREA(l);
        if (get_qcc_solid(touch) == SOLID_NOT)
            continue;
        if (touch == clip->passedict)
            continue;
        if (get_qcc_solid(touch) == SOLID_TRIGGER)
            Sys_Error("Trigger in clipping list");

        if (clip->type == MOVE_NOMONSTERS && get_qcc_solid(touch) != SOLID_BSP)
            continue;
#if USE_OLD_ABS_CALLS
        if (clip->boxmins[0] > VEC(get_qcc_absmax(touch))[0]
            || clip->boxmins[1] > VEC(get_qcc_absmax(touch))[1]
            || clip->boxmins[2] > VEC(get_qcc_absmax(touch))[2]
            || clip->boxmaxs[0] < VEC(get_qcc_absmin(touch))[0]
            || clip->boxmaxs[1] < VEC(get_qcc_absmin(touch))[1]
            || clip->boxmaxs[2] < VEC(get_qcc_absmin(touch))[2] )
        continue;
#else
        vector absmax = get_qcc_absmax(touch);
        if (clip->boxmins[0] > absmax.v[0] || clip->boxmins[1] > absmax.v[1] || clip->boxmins[2] > absmax.v[2])
            continue;
        vector absmin = get_qcc_absmin(touch);
        if (clip->boxmaxs[0] < absmin.v[0] || clip->boxmaxs[1] < absmin.v[1] || clip->boxmaxs[2] < absmin.v[2])
            continue;

#endif
        if (clip->passedict && VEC(get_qcc_size(clip->passedict))[0] && !VEC(get_qcc_size(touch))[0])
            continue;	// points never interact

        // might intersect, so do an exact clip
        if (clip->trace.allsolid)
            return;
        if (clip->passedict)
        {
            if (PROG_TO_EDICT(get_qcc_owner(touch)) == clip->passedict)
                continue;	// don't clip against own missiles
            if (PROG_TO_EDICT(get_qcc_owner(clip->passedict)) == touch)
                continue;	// don't clip against owner
        }

        if ((int) get_qcc_flags(touch) & FL_MONSTER)
            trace = SV_ClipMoveToEntity(touch, clip->start, clip->mins2, clip->maxs2, clip->end);
        else
            trace = SV_ClipMoveToEntity(touch, clip->start, clip->mins, clip->maxs, clip->end);
        if (trace.allsolid || trace.startsolid || trace.fraction < clip->trace.fraction)
        {
            trace.ent = touch;
            if (clip->trace.startsolid)
            {
                clip->trace = trace;
                clip->trace.startsolid = true;
            }
            else
                clip->trace = trace;
        }
        else if (trace.startsolid)
            clip->trace.startsolid = true;
    }

// recurse down both sides
    if (node->axis == -1)
        return;

    if (clip->boxmaxs[node->axis] > node->dist)
        SV_ClipToLinks(node->children[0], clip);
    if (clip->boxmins[node->axis] < node->dist)
        SV_ClipToLinks(node->children[1], clip);
}

/*
 ==================
 SV_MoveBounds
 ==================
 */
void SV_MoveBounds(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, vec3_t boxmins, vec3_t boxmaxs)
{
#if 0
// debug to test against everything
boxmins[0] = boxmins[1] = boxmins[2] = -9999;
boxmaxs[0] = boxmaxs[1] = boxmaxs[2] = 9999;
#else
    int i;

    for (i = 0; i < 3; i++)
    {
        if (end[i] > start[i])
        {
            boxmins[i] = start[i] + mins[i] - 1;
            boxmaxs[i] = end[i] + maxs[i] + 1;
        }
        else
        {
            boxmins[i] = end[i] + mins[i] - 1;
            boxmaxs[i] = start[i] + maxs[i] + 1;
        }
    }
#endif
}

/*
 ==================
 SV_Move
 ==================
 */
trace_t SV_Move(vec3_t start, vec3_t mins, vec3_t maxs, vec3_t end, int type, edict_t *passedict)
{
    moveclip_t clip;
    int i;

    memset(&clip, 0, sizeof(moveclip_t));

// clip to world
    clip.trace = SV_ClipMoveToEntity(sv.edicts, start, mins, maxs, end);

    clip.start = start;
    clip.end = end;
    clip.mins = mins;
    clip.maxs = maxs;
    clip.type = type;
    clip.passedict = passedict;

    if (type == MOVE_MISSILE)
    {
        for (i = 0; i < 3; i++)
        {
            clip.mins2[i] = -15;
            clip.maxs2[i] = 15;
        }
    }
    else
    {
        VectorCopy(mins, clip.mins2);
        VectorCopy(maxs, clip.maxs2);
    }

// create the bounding box of the entire move
    SV_MoveBounds(start, clip.mins2, clip.maxs2, end, clip.boxmins, clip.boxmaxs);

// clip to entities
    SV_ClipToLinks(sv_areanodes, &clip);

    return clip.trace;
}

