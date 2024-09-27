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
#ifndef ENTITY_GETTERS_SETTERS_H
#define ENTITY_GETTERS_SETTERS_H
//#define temp_entity_t client_entity_t
#include "global_data.h"
#if DYNAMIC_3D_VIEWPORT_SIZE
    extern short *d_zbuffer;
#else
extern short d_zbuffer[_3D_VIEWPORT_SIZE];
#endif
#if WIN32
extern int gem;
#endif
static inline model_t* getEntityModel(entity_t *ent)
{
#if WIN32 && 0
    gem++;
    printf("Get EntityModel: %d\r\n", gem);
    #endif
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        if (((temp_entity_t*) ent->data)->modelIdx < 0)
            return NULL;
        else
            return &mod_known[((temp_entity_t*) ent->data)->modelIdx];
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        if (ent->mustBeDrawn)
            return sv.models[(int) get_qcc_modelindex((edict_t*) ent->data)];
        else
            return NULL;
    }
    else
    {
        if (((client_entity_t*) ent->data)->modelIdx < 0)
            return NULL;
        else
            return &mod_known[((client_entity_t*) ent->data)->modelIdx];
    }
}
static inline void setEntityModel(entity_t *ent, model_t *model)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        if (model == NULL)
            ((temp_entity_t*) ent->data)->modelIdx = -1;
        else
            ((temp_entity_t*) ent->data)->modelIdx = model - &mod_known[0];
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        if (NULL == model)
        {
            ent->mustBeDrawn = 0;
        }
        else
        {
            ent->mustBeDrawn = 1;
        }
    }
    else
    {
        if (model == NULL)
            ((client_entity_t*) ent->data)->modelIdx = -1;
        else
            ((client_entity_t*) ent->data)->modelIdx = model - &mod_known[0];
    }
}
//
static inline int getEntityFrame(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        return ((temp_entity_t*) ent->data)->frame;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_frame((edict_t*) ent->data);
    }
    else
    {
        return ((client_entity_t*) ent->data)->frame;
    }
}
static inline void setEntityFrame(entity_t *ent, int frame)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        ((temp_entity_t*) ent->data)->frame = frame;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        FIXME("SET FRAME ON EDICT");
    }
    else
    {
        ((client_entity_t*) ent->data)->frame = frame;
    }
}
//
static inline int getEntityEffects(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        return ((temp_entity_t*) ent->data)->effects;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_effects((edict_t*) ent->data);
    }
    else
    {
        return ((client_entity_t*) ent->data)->effects;
    }
}
static inline void setEntityEffects(entity_t *ent, int effects)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        ((temp_entity_t*) ent->data)->effects = effects;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        FIXME("SET EFFECTS ON EDICT");
    }
    else
    {
        ((client_entity_t*) ent->data)->effects = effects;
    }
}
//
static inline int getEntitySkinnum(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        return ((temp_entity_t*) ent->data)->skinnum;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_skin((edict_t*) ent->data);
    }
    else
    {
        return ((client_entity_t*) ent->data)->skinnum;
    }
}
static inline void setEntitySkinnum(entity_t *ent, int skinnum)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
        ((temp_entity_t*) ent->data)->skinnum = skinnum;
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        FIXME("SET EFFECTS ON EDICT");
    }
    else
    {
        ((client_entity_t*) ent->data)->skinnum = skinnum;
    }
}

//
static inline entity_state_t* getEntityBaseLine(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type != TYPE_CLIENT_ENTITY)
    {
        while (1)
            FIXME("Asked to get baseline for entity type not client");
        return NULL;
    }
    else
    {
        return &((client_entity_t*) ent->data)->baseline;
    }
}
static inline QDFLOAT getEntityMsgTime(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type != TYPE_CLIENT_ENTITY)
    {
        while (1)
            FIXME("Asked to get msg time for entity type not client");
        return 0;
    }
    else
    {
        return ((client_entity_t*) ent->data)->msgtime;
    }
}
static inline void setEntityMsgTime(entity_t *ent, QDFLOAT time)
{
    unsigned int type = ent->entityType;
    if (type != TYPE_CLIENT_ENTITY)
    {
        while (1)
            FIXME("Asked to set msg time for entity type not client");
    }
    else
    {
        ((client_entity_t*) ent->data)->msgtime = time;
    }
}
static inline float getEntityOrigin(entity_t *ent, int index)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatCoord(((temp_entity_t*)ent->data)->origin_s[index]);
        #else
        return ((temp_entity_t*) ent->data)->origin[index];
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_origin((edict_t*) ent->data).v[index];
    }
    else
    {
#if ENTITY_HAS_SHORT_COORDS
            return toFloatCoord(((client_entity_t*)ent->data)->origin_s[index]);
        #else
        return ((client_entity_t*) ent->data)->origin[index];
#endif // ENTITY_HAS_SHORT_COORDS
    }
}
static inline float setEntityOrigin(entity_t *ent, int index, float value)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return ((temp_entity_t*)ent->data)->origin_s[index] = toShortCoord(value);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        FIXME("CAN'T SET ENTITY ORIGIN FROM SERVER");
        return 0;
    }
    else
    {
#if ENTITY_HAS_SHORT_COORDS
            return ((client_entity_t*)ent->data)->origin_s[index] = toShortCoord(value);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
}
static inline vect_t getEntityOrigins(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatCoords(((temp_entity_t*)ent->data)->origin_s);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_origin((edict_t*) ent->data);
    }
    else
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatCoords(((client_entity_t*)ent->data)->origin_s);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
}
///

static inline vector getEntityAbsMaxs(entity_t *ent)
{
    vector o =
    {
        {
            0, 0, 0
        }
    };
    unsigned int type = ent->entityType;
    if (type == TYPE_CLIENT_ENTITY)
    {
        o = getEntityOrigins(ent);
        short *maxs_s = getEntityModel(ent)->maxs_s;
        o.x += maxs_s[0];
        o.y += maxs_s[1];
        o.z += maxs_s[2];
        o.x += 1;
        o.y += 1;
        o.z += 1;
    }
    else
    {
        FIXME("Asked for mins/maxs of not TYPE_CLIENT_ENTITY\r\n");
    }
    return o;
}
static inline vector getEntityAbsMins(entity_t *ent)
{
    vector o =
    {
        {
            0, 0, 0
        }
    };
    unsigned int type = ent->entityType;
    if (type == TYPE_CLIENT_ENTITY)
    {
        o = getEntityOrigins(ent);
        short *mins_s = getEntityModel(ent)->mins_s;
        o.x += mins_s[0];
        o.y += mins_s[1];
        o.z += mins_s[2];
        o.x -= 1;
        o.y -= 1;
        o.z -= 1;
    }
    else
    {
        FIXME("Asked for mins/maxs of not TYPE_CLIENT_ENTITY\r\n");
    }
    return o;
}

//////// ANGLES

static inline float getEntityAngle(entity_t *ent, int index)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatAngle(((temp_entity_t*)ent->data)->angles_s[index]);
        #else
        return ((temp_entity_t*) ent->data)->angles[index];
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_angles((edict_t*) ent->data).v[index];
    }
    else
    {
#if ENTITY_HAS_SHORT_COORDS
            return toFloatAngle(((client_entity_t*)ent->data)->angles_s[index]);
        #else
        return ((client_entity_t*) ent->data)->angles[index];
#endif // ENTITY_HAS_SHORT_COORDS
    }
}
static inline void setEntityAngle(entity_t *ent, int index, float value)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            ((temp_entity_t*)ent->data)->angles_s[index] = toShortAngle(value);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        // must be done for rotating objects
        if (index == 0)
            set_qcc_angles_x((edict_t*) ent->data, value);
        else if (index == 1)
            set_qcc_angles_y((edict_t*) ent->data, value);
        else if (index == 2)
            set_qcc_angles_z((edict_t*) ent->data, value);
    }
    else
    {
#if ENTITY_HAS_SHORT_COORDS
            ((client_entity_t*)ent->data)->angles_s[index] = toShortAngle(value);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
}
static inline vect_t getEntityAngles(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_TEMP_ENTITY)
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatAngles(((temp_entity_t*)ent->data)->angles_s);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
    else if (type == TYPE_EDICT_ENTITY)
    {
        return get_qcc_angles((edict_t*) ent->data);
    }
    else
    {
        // it's a temp entity. Note Temp entities must be reduced
#if ENTITY_HAS_SHORT_COORDS
            return toFloatAngles(((client_entity_t*)ent->data)->angles_s);
        #else
#error
#endif // ENTITY_HAS_SHORT_COORDS
    }
}

////////// END ANGLES

static inline void setEntityForceLink(entity_t *ent, unsigned int fl)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_CLIENT_ENTITY)
    {
        ((client_entity_t*) ent->data)->forcelink = fl != 0;
    }
    else if (type != TYPE_EDICT_ENTITY)
    {
        FIXME("Force link set on view or temp");
    }
}
static inline unsigned int getEntityForceLink(entity_t *ent)
{
    unsigned int type = ent->entityType;
    if (type == TYPE_CLIENT_ENTITY)
    {
        return ((client_entity_t*) ent->data)->forcelink;
    }
    return 1;
}
#if !BEAM_HAS_MODEL_POINTER
static inline void setBeamModel(beam_t *b, model_t *pmodel)
{
    if (pmodel == NULL)
    {
        b->model_index = -1;
    }
    else
    {
        b->model_index = pmodel - &mod_known[0];
    }
}
static inline model_t* getBeamModel(beam_t *b)
{
    if (b->model_index >= 0)
    {
        return &mod_known[b->model_index];
    }
    else
    {
        return NULL;
    }
}
static inline void setEntityTopnode(entity_t *ent, mnode_t *topnode)
{
    if (!topnode)
    {
        ent->topnodeIdx = 0;
    }
    else
    {
        if (topnode->contents >= 0)
        {
#if OLD_NODE_STRUCTURE
            ent->nodeIdx = topnode - cl.worldmodel->brushModelData->nodes;
#else
            ent->nodeIdx = topnode->node_idx;
#endif
            ent->isNode = 1;
        }
        else
        {
#if OLD_NODE_STRUCTURE
            ent->nodeIdx = (mleaf_t*) topnode - cl.worldmodel->brushModelData->leafs;
#else
            ent->nodeIdx = topnode->node_idx;
#endif
            ent->isNode = 0;
        }
    }
}
static inline mnode_t* getEntityTopnode(entity_t *ent)
{
    if (ent->topnodeIdx == 0)
    {
        return NULL;
    }
    else
    {
        if (ent->isNode)
        {
            return _g->cl.worldmodel->brushModelData->nodes + ent->nodeIdx;
        }
        else
        {
            return (mnode_t*) (_g->cl.worldmodel->brushModelData->leafs + ent->nodeIdx);
        }
    }
}
#endif
// Edict functions: TODO: put in a separate file.
#if EDICTS_USE_SHORT_PTR
extern uint8_t staticZone[];
static inline void* getStaticZoneLongPtr(uint16_t sp)
{
    if (sp == 0)
        return NULL;
    else
        return (byte*) staticZone + (sp << 2);
}
static inline uint16_t getStaticZoneShortPtr(void *p)
{
    if (p == NULL)
        return 0;       // staticZone[0] is occupied by the first block data.
    else
        return ((byte*) p - (byte*)staticZone) >> 2;
}

 //   #define	EDICT_TO_PROG(e) ((byte *)(e) - (byte *)sv.edicts)
 //   #define PROG_TO_EDICT(e) ((edict_t *)((byte *)sv.edicts + e))
#if BETTER_EDICT_COMPATIBILITY
static inline int EDICT_TO_PROG(void *e)
{
 int difference = (byte*) e - (byte*) sv.edicts;
// printf("Difference is: %d, >>2 is %d\r\n", difference, difference >> 2);
 return difference >> 2;
}
static inline void* PROG_TO_EDICT(short e)
{
// printf("e is: %d, shifted %d, sv.edicts is %p, returned value %p\r\n", e, e << 2, (byte*) sv.edicts + (e << 2));
 return (byte*) sv.edicts + ((int)e << 2);
}
/*
    #define	EDICT_TO_PROG(e) (((byte *)e - (byte *)sv.edicts) >> 2)
    #define PROG_TO_EDICT(e) ((edict_t *)((byte *)sv.edicts + ((e) << 2)))*/
#else
    #define	EDICT_TO_PROG(e) (((byte *)e - (byte *)staticZone) >> 2)
    #define PROG_TO_EDICT(e) ((edict_t *)((byte *)staticZone + ((e) << 2)))
#endif
#else
#error
#define	EDICT_TO_PROG(e) ((byte *)e - (byte *)sv.edicts)
#define PROG_TO_EDICT(e) ((edict_t *)((byte *)sv.edicts + e))
#endif // EDICTS_USE_SHORT_PTR
#if EDICT_LINKED_LIST
extern server_t		sv;
static inline edict_t *getNextEdict(edict_t *e)
{
    #if EDICTS_USE_SHORT_PTR
    #if !BETTER_EDICT_COMPATIBILITY
        if (e->nextEdict_sptr == 0x7FFF)
            return NULL;
    #endif
        return PROG_TO_EDICT(e->nextEdict_sptr);
    #else
        return e->nextEdict;
    #endif
}
int ED_hasBeenWatchedEntityFreed(edict_t *ent);
void ED_WatchForFree(edict_t *e);
static inline void setNextEdict(edict_t *e, edict_t *ne)
{
    #if EDICTS_USE_SHORT_PTR
    #if !BETTER_EDICT_COMPATIBILITY
        if (ne == NULL)
            e->nextEdict_sptr = 0x7FFF;
        else
    #endif
            e->nextEdict_sptr = EDICT_TO_PROG(ne);
    #else
        e->nextEdict = ne;
    #endif
}
#define NEXT_EDICT(e)  getNextEdict((edict_t *)(e))
//#define	NEXT_EDICT(e) ((edict_t *)( (byte *)e + pr_edict_size))
#endif
#endif // ENTITY_GETTERS_SETTERS_H
