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
// cl_tent.c -- client side temporary entities
#include "quakedef.h"

#ifdef QUAKE2
sfx_t			*cl_sfx_imp;
sfx_t			*cl_sfx_rail;
#endif

/*
 =================
 CL_ParseTEnt
 =================
 */
void CL_InitTEnts(void)
{
    _g->cl_sfx_wizhit = S_PrecacheSound("wizard/hit.wav");
    _g->cl_sfx_knighthit = S_PrecacheSound("hknight/hit.wav");
    _g->cl_sfx_tink1 = S_PrecacheSound("weapons/tink1.wav");
    _g->cl_sfx_ric1 = S_PrecacheSound("weapons/ric1.wav");
    _g->cl_sfx_ric2 = S_PrecacheSound("weapons/ric2.wav");
    _g->cl_sfx_ric3 = S_PrecacheSound("weapons/ric3.wav");
    _g->cl_sfx_r_exp3 = S_PrecacheSound("weapons/r_exp3.wav");
#ifdef QUAKE2
	cl_sfx_imp = S_PrecacheSound ("shambler/sattck1.wav");
	cl_sfx_rail = S_PrecacheSound ("weapons/lstart.wav");
#endif
}

/*
 =================
 CL_ParseBeam
 =================
 */
void CL_ParseBeam(model_t *m)
{
    int ent;
    vec3_t start, end;
    beam_t *b;
    int i;

    ent = MSG_ReadShort();

    start[0] = MSG_ReadCoord();
    start[1] = MSG_ReadCoord();
    start[2] = MSG_ReadCoord();

    end[0] = MSG_ReadCoord();
    end[1] = MSG_ReadCoord();
    end[2] = MSG_ReadCoord();

// override any beam with the same entity
    for (i = 0, b = _g->cl_beams; i < MAX_BEAMS; i++, b++)
        if (b->entity == ent)
        {
            b->entity = ent;
#if BEAM_HAS_MODEL_POINTER
			b->model = m;
#else
            setBeamModel(b, m);
#endif
            b->endtime = _g->cl.time + 0.2f;
#if BEAM_HAS_FLOAT_COORDS
			VectorCopy (start, b->start);
			VectorCopy (end, b->end);
#else
            b->start_s[0] = toShortCoord(start[0]);
            b->start_s[1] = toShortCoord(start[1]);
            b->start_s[2] = toShortCoord(start[2]);
            b->end_s[0] = toShortCoord(end[0]);
            b->end_s[1] = toShortCoord(end[1]);
            b->end_s[2] = toShortCoord(end[2]);

#endif // BEAM_HAS_FLOAT_COORDS
            return;
        }

// find a free beam
    for (i = 0, b = _g->cl_beams; i < MAX_BEAMS; i++, b++)
    {
#if BEAM_HAS_MODEL_POINTER
		if (!b->model || b->endtime < cl.time)
#else
        if (!getBeamModel(b) || b->endtime < _g->cl.time)
#endif
        {
            b->entity = ent;
#if BEAM_HAS_MODEL_POINTER
			b->model = m;
#else
            setBeamModel(b, m);
#endif
            b->endtime = _g->cl.time + 0.2f;
#if BEAM_HAS_FLOAT_COORDS
			VectorCopy (start, b->start);
			VectorCopy (end, b->end);
#else
            b->start_s[0] = toShortCoord(start[0]);
            b->start_s[1] = toShortCoord(start[1]);
            b->start_s[2] = toShortCoord(start[2]);
            b->end_s[0] = toShortCoord(end[0]);
            b->end_s[1] = toShortCoord(end[1]);
            b->end_s[2] = toShortCoord(end[2]);

#endif // BEAM_HAS_FLOAT_COORDS

            return;
        }
    }
    Con_Printf("beam list overflow!\n");
}

/*
 =================
 CL_ParseTEnt
 =================
 */
void CL_ParseTEnt(void)
{
    int type;
    vec3_t pos;
#ifdef QUAKE2
	vec3_t	endpos;
#endif
    dlight_t *dl;
    int rnd;
    int colorStart, colorLength;

    type = MSG_ReadByte();
    switch (type)
    {
        case TE_WIZSPIKE:			// spike hitting wall
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_RunParticleEffect(pos, vec3_origin, 20, 30);
            S_StartSound(-1, 0, _g->cl_sfx_wizhit, pos, 1, 1);
            break;

        case TE_KNIGHTSPIKE:			// spike hitting wall
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_RunParticleEffect(pos, vec3_origin, 226, 20);
            S_StartSound(-1, 0, _g->cl_sfx_knighthit, pos, 1, 1);
            break;

        case TE_SPIKE:			// spike hitting wall
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
#ifdef GLTEST
		Test_Spawn (pos);
#else
            R_RunParticleEffect(pos, vec3_origin, 0, 10);
#endif
            if (rand() % 5)
                S_StartSound(-1, 0, _g->cl_sfx_tink1, pos, 1, 1);
            else
            {
                rnd = rand() & 3;
                if (rnd == 1)
                    S_StartSound(-1, 0, _g->cl_sfx_ric1, pos, 1, 1);
                else if (rnd == 2)
                    S_StartSound(-1, 0, _g->cl_sfx_ric2, pos, 1, 1);
                else
                    S_StartSound(-1, 0, _g->cl_sfx_ric3, pos, 1, 1);
            }
            break;
        case TE_SUPERSPIKE:			// super spike hitting wall
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_RunParticleEffect(pos, vec3_origin, 0, 20);

            if (rand() % 5)
                S_StartSound(-1, 0, _g->cl_sfx_tink1, pos, 1, 1);
            else
            {
                rnd = rand() & 3;
                if (rnd == 1)
                    S_StartSound(-1, 0, _g->cl_sfx_ric1, pos, 1, 1);
                else if (rnd == 2)
                    S_StartSound(-1, 0, _g->cl_sfx_ric2, pos, 1, 1);
                else
                    S_StartSound(-1, 0, _g->cl_sfx_ric3, pos, 1, 1);
            }
            break;

        case TE_GUNSHOT:			// bullet hitting wall
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_RunParticleEffect(pos, vec3_origin, 0, 20);
            break;

        case TE_EXPLOSION:			// rocket explosion
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_ParticleExplosion(pos);
            dl = CL_AllocDlight(0);

#if DLIGHT_HAS_FLOAT_ORIGIN
		VectorCopy (pos, dl->origin);
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = pos[j];
#endif

            dl->radius = 350;
            dl->die = _g->cl.time + 0.5;
#if PACK_DLIGHTS
    dl->hasDecay300 = 1;
#else
            dl->decay = 300;
#endif
            S_StartSound(-1, 0, _g->cl_sfx_r_exp3, pos, 1, 1);
            break;

        case TE_TAREXPLOSION:			// tarbaby explosion
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_BlobExplosion(pos);

            S_StartSound(-1, 0, _g->cl_sfx_r_exp3, pos, 1, 1);
            break;

        case TE_LIGHTNING1:				// lightning bolts
            CL_ParseBeam(Mod_ForName("progs/bolt.mdl", true));
            break;

        case TE_LIGHTNING2:				// lightning bolts
            CL_ParseBeam(Mod_ForName("progs/bolt2.mdl", true));
            break;

        case TE_LIGHTNING3:				// lightning bolts
            CL_ParseBeam(Mod_ForName("progs/bolt3.mdl", true));
            break;

// PGM 01/21/97
        case TE_BEAM:				// grappling hook beam
            CL_ParseBeam(Mod_ForName("progs/beam.mdl", true));
            break;
// PGM 01/21/97

        case TE_LAVASPLASH:
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_LavaSplash(pos);
            break;

        case TE_TELEPORT:
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            R_TeleportSplash(pos);
            break;

        case TE_EXPLOSION2:				// color mapped explosion
            pos[0] = MSG_ReadCoord();
            pos[1] = MSG_ReadCoord();
            pos[2] = MSG_ReadCoord();
            colorStart = MSG_ReadByte();
            colorLength = MSG_ReadByte();
            R_ParticleExplosion2(pos, colorStart, colorLength);
            dl = CL_AllocDlight(0);

#if DLIGHT_HAS_FLOAT_ORIGIN
		VectorCopy (pos, dl->origin);
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = pos[j];
#endif
            dl->radius = 350;
            dl->die = _g->cl.time + 0.5f;
#if PACK_DLIGHTS
    dl->hasDecay300 = 1;
#else
            dl->decay = 300;
#endif
            S_StartSound(-1, 0, _g->cl_sfx_r_exp3, pos, 1, 1);
            break;

#ifdef QUAKE2
	case TE_IMPLOSION:
		pos[0] = MSG_ReadCoord ();
		pos[1] = MSG_ReadCoord ();
		pos[2] = MSG_ReadCoord ();
		S_StartSound (-1, 0, cl_sfx_imp, pos, 1, 1);
		break;

	case TE_RAILTRAIL:
		pos[0] = MSG_ReadCoord ();
		pos[1] = MSG_ReadCoord ();
		pos[2] = MSG_ReadCoord ();
		endpos[0] = MSG_ReadCoord ();
		endpos[1] = MSG_ReadCoord ();
		endpos[2] = MSG_ReadCoord ();
		S_StartSound (-1, 0, cl_sfx_rail, pos, 1, 1);
		S_StartSound (-1, 1, cl_sfx_r_exp3, endpos, 1, 1);
		R_RocketTrail (pos, endpos, 0+128);
		R_ParticleExplosion (endpos);
		dl = CL_AllocDlight (-1);
		VectorCopy (endpos, dl->origin);
		dl->radius = 350;
		dl->die = cl.time + 0.5;
		dl->decay = 300;
		break;
#endif

        default:
            Sys_Error("CL_ParseTEnt: bad type");
    }
}

/*
 =================
 CL_NewTempEntity
 =================
 */
entity_t* CL_NewTempEntity(void)
{
    entity_t *ent;

    if (_g->cl_numvisedicts == MAX_VISEDICTS)
        return NULL;
    if (_g->num_temp_entities == MAX_TEMP_ENTITIES)
        return NULL;
#if SEPARATE_TEMP_ENTITIES
	ent = &cl_temp_entities[num_temp_entities];
#else
    ent = &cl_entities[_g->num_temp_entities + MAX_EDICTS];
#endif
    fastMemclear32(ent, sizeof(*ent) / 4);
    ent->entityType = TYPE_TEMP_ENTITY;
#if STATIC_TEMP_ENTITIES
    ent->data = &_g->cl_temp_entity_data[_g->num_temp_entities];
#else
#error
    ent->data = Z_Calloc(sizeof(temp_entity_t), 1, PU_LEVEL, ent->data);    // user set to ent->data so if it is freed, data will be 0
#endif
    _g->num_temp_entities++;
    //printf("New temp entity %d\r\n", _g->num_temp_entities);

#if POINTER_CL_VISEDICT
	_g->cl_visedicts[_g->cl_numvisedicts] = ent;
#else
    _g->cl_visedicts[_g->cl_numvisedicts] = ent - &cl_entities[0];
#endif
    _g->cl_numvisedicts++;
#if HAS_MULTIPLAYER
	ent->colormap = vid.colormap;
#endif
    return ent;
}

/*
 =================
 CL_UpdateTEnts
 =================
 */
void CL_UpdateTEnts(void)
{
    int i;
    beam_t *b;
    vec3_t dist, org;
    float d;
    entity_t *ent;
    float yaw, pitch;
    float forward;
#if !STATIC_TEMP_ENTITIES
	// next-hack: free allocated entities
	for (i = 0; i < num_temp_entities; i++)
    {
#if SEPARATE_TEMP_ENTITIES
        ent = &cl_temp_entities[i];
#else
        ent = &cl_entities[i + MAX_EDICTS];
#endif
        if (ent->data)
        {
            Z_Free(ent->data);
        }
        ent->data = 0;
    }
#endif
    _g->num_temp_entities = 0;

// update lightning
    for (i = 0, b = _g->cl_beams; i < MAX_BEAMS; i++, b++)
    {
#if BEAM_HAS_MODEL_POINTER
		if (!b->model || b->endtime < cl.time)
			continue;
#else
        if (!getBeamModel(b) || b->endtime < _g->cl.time)
            continue;

#endif

        // if coming from the player, update the start position
        if (b->entity == _g->cl.viewentity)
        {
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (cl_entities[cl.viewentity].origin, b->start);
#else
#if BEAM_HAS_FLOAT_COORDS
			VectorCopy (VEC(getEntityOrigins(&cl_entities[cl.viewentity])), b->start);
#else
            for (int j = 0; j < 3; j++)
            {
                b->start_s[j] = toShortCoord(getEntityOrigin(&cl_entities[_g->cl.viewentity], j));
            }
#endif
#endif
        }

        // calculate pitch and yaw
#if BEAM_HAS_FLOAT_COORDS
		VectorSubtract (b->end, b->start, dist);
#else
        VectorSubtract(VEC(toFloatCoords(b->end_s)), VEC(toFloatCoords(b->start_s)), dist);

#endif
        if (dist[1] == 0 && dist[0] == 0)
        {
            yaw = 0;
            if (dist[2] > 0)
                pitch = 90;
            else
                pitch = 270;
        }
        else
        {
            yaw = (int) (atan2f(dist[1], dist[0]) * (180 / M_PI));
            if (yaw < 0)
                yaw += 360;
            forward = sqrtf(dist[0] * dist[0] + dist[1] * dist[1]);
            pitch = (int) (atan2f(dist[2], forward) * (180 / M_PI));
            if (pitch < 0)
                pitch += 360;
        }

        // add new entities for the lightning
#if BEAM_HAS_FLOAT_COORDS
		VectorCopy (b->start, org);
#else
        VectorCopy(VEC(toFloatCoords(b->start_s)), org);

#endif
        d = VectorNormalize(dist);
        while (d > 0)
        {
            ent = CL_NewTempEntity();
            if (!ent)
                return;
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (org, ent->origin);
			ent->model = b->model;
			ent->angles[0] = pitch;
			ent->angles[1] = yaw;
			ent->angles[2] = rand()%360;
#else
            ((temp_entity_t*) ent->data)->origin_s[0] = toShortCoord(org[0]);
            ((temp_entity_t*) ent->data)->origin_s[1] = toShortCoord(org[1]);
            ((temp_entity_t*) ent->data)->origin_s[2] = toShortCoord(org[2]);
#if BEAM_HAS_MODEL_POINTER
			setEntityModel(ent, b->model);
#else
            setEntityModel(ent, getBeamModel(b));
#endif
            setEntityAngle(ent, 0, pitch);
            setEntityAngle(ent, 1, yaw);
            setEntityAngle(ent, 2, rand() % 360);

#endif
            for (i = 0; i < 3; i++)
                org[i] += dist[i] * 30;
            d -= 30;
        }
    }

}

