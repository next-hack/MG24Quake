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
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
#define	RETURN_EDICT(e) (((int *)pr_globals)[OFS_RETURN] = EDICT_TO_PROG(e))
char *entityFieldName;

void SetMinMaxSize_s(edict_t *e, short *min_s, short *max_s, qboolean rotate);
void SetMinMaxSize(edict_t *e, float *min, float *max, qboolean rotate);

/*
 ===============================================================================

 BUILT-IN FUNCTIONS

 ===============================================================================
 */
#if USE_PROGSDAT
// deleted.
#else
void PR_CheckEmptyString(const char *s)
{
    if (s[0] <= ' ')
        PR_RunError("Bad string");
}

void qcc_remove(int entid)
{
    ED_Free(PROG_TO_EDICT(entid));
}
float qcc_random(void)
{
    float num;

    num = (rand() & 0x7fff) / ((float) 0x7fff);

    return num;
}
void qcc_sound(int entid, float channelf, uint16_t sampleString, float volumef, float attenuation)
{
    const char *sample;
    int channel;
    edict_t *entity;
    int volume;
//	float attenuation;

    entity = PROG_TO_EDICT(entid);
    channel = channelf;
    sample = getStringFromIndex(sampleString);
    volume = volumef * 255;

    if (volume < 0 || volume > 255)
        Sys_Error("SV_StartSound: volume = %i", volume);

    if (attenuation < 0 || attenuation > 4)
        Sys_Error("SV_StartSound: attenuation = %f", attenuation);

    if (channel < 0 || channel > 7)
        Sys_Error("SV_StartSound: channel = %i", channel);

    SV_StartSound(entity, channel, sample, volume, attenuation);
}
void qcc_makevectors(vector v)
{
//	AngleVectors (v.v, pr_global_struct->v_forward.v, pr_global_struct->v_right.v, pr_global_struct->v_up.v);
    AngleVectors(v.v, progs.qcc_v_forward.v, progs.qcc_v_right.v, progs.qcc_v_up.v);

}

/*
 =================
 PF_setmodel

 setmodel(entity, model)
 =================
 */
void qcc_setmodel(int entid, uint16_t modelStringnum)
{
    edict_t *e;
    const char *m;
    const char **check;
    model_t *mod;
    int i;

    e = PROG_TO_EDICT(entid);
    m = getStringFromIndex(modelStringnum);

// check to see if model was properly precached
    for (i = 0, check = sv.model_precache; *check; i++, check++)
        if (!strcmp(*check, m))
            break;
#define CACHE_IF_NOT_FOUND 0
#if CACHE_IF_NOT_FOUND
    #warning FIX THIS
    if (!check)
    {
        printf("Warning, model %s was not cached. Caching, will have index %i\r\n", getStringFromIndex(modelStringnum), i);

        qcc_precache_model(modelStringnum);
    }
    #else
    if (!*check)
        PR_RunError("no model precache: %s\n", m);
#endif
    if (i == 0)
    {
        i++;
//      printf("%s ", getStringFromIndex(modelStringnum));
        //   while(1) FIXME("Modelindex is 0\r\n");
    }
    set_qcc_model(e, modelStringnum); //m - pr_strings;
//	printf("model stringNum is %d", modelStringnum);
    set_qcc_modelindex(e, i); //SV_ModelIndex (m);
//    printf("afteer vfield\r\n");
    mod = sv.models[(int) get_qcc_modelindex(e)];  // Mod_ForName (m, true);
//    printf("accessing model\r\n");
    if (mod)
    {
#if MODEL_HAS_FLOAT_MINS_MAX
		SetMinMaxSize (e, mod->mins, mod->maxs, true);
#else
        SetMinMaxSize_s(e, mod->mins_s, mod->maxs_s, true);
#endif
    }
    else
        SetMinMaxSize(e, vec3_origin, vec3_origin, true);
    //  printf("EndSetModel\r\n");
}
void SetMinMaxSize_s(edict_t *e, short *min_s, short *max_s, qboolean rotate)
{
    vec3_t mins, maxs;
    VectorCopy(min_s, mins);
    VectorCopy(max_s, maxs);
    SetMinMaxSize(e, mins, maxs, rotate);
}
void SetMinMaxSize(edict_t *e, float *min, float *max, qboolean rotate)
{
    float angleY;
    vec3_t rmin, rmax;
    float bounds[2][3];
    float xvector[2], yvector[2];
    float a;
    vec3_t base, transformed;
    int i, j, k, l;

    for (i = 0; i < 3; i++)
        if (min[i] > max[i])
            PR_RunError("backwards mins/maxs at index %i: %f %f", i, min[i], max[i]);

    rotate = false;		// FIXME: implement rotation properly again

    if (!rotate)
    {
        VectorCopy(min, rmin);
        VectorCopy(max, rmax);
    }
    else
    {
        // find min / max for rotations
        angleY = VEC(get_qcc_angles(e))[1];

        a = angleY / 180 * M_PI;

        xvector[0] = cos_t(a);
        xvector[1] = sin_t(a);
        yvector[0] = -sin_t(a);
        yvector[1] = cos_t(a);

        VectorCopy(min, bounds[0]);
        VectorCopy(max, bounds[1]);

        rmin[0] = rmin[1] = rmin[2] = 9999;
        rmax[0] = rmax[1] = rmax[2] = -9999;

        for (i = 0; i <= 1; i++)
        {
            base[0] = bounds[i][0];
            for (j = 0; j <= 1; j++)
            {
                base[1] = bounds[j][1];
                for (k = 0; k <= 1; k++)
                {
                    base[2] = bounds[k][2];

                    // transform the point
                    transformed[0] = xvector[0] * base[0] + yvector[0] * base[1];
                    transformed[1] = xvector[1] * base[0] + yvector[1] * base[1];
                    transformed[2] = base[2];

                    for (l = 0; l < 3; l++)
                    {
                        if (transformed[l] < rmin[l])
                            rmin[l] = transformed[l];
                        if (transformed[l] > rmax[l])
                            rmax[l] = transformed[l];
                    }
                }
            }
        }
    }

// set derived values
    set_qcc_mins(e, vectorize(rmin));
    set_qcc_maxs(e, vectorize(rmax));
    //
    SV_LinkEdict(e, false);
}
/*
 =================
 PF_objerror

 Dumps out self, then an error message.  The program is aborted and self is
 removed, but the level can continue.

 objerror(value)
 =================
 */
void qcc_objerror(uint16_t stringNum)
{
    (void) stringNum;
    while (1)
    {
        printf("Error: %s\r\n", getStringFromIndex(stringNum));
        FIXME("OBJERR");
    }

// next-hack: removed.
#if 0
    edict_t *ed;
//	s = PF_VarString(0);
//	Con_Printf ("======OBJECT ERROR in %s:\n%s\n"	,pr_strings + pr_xfunction->s_name,s);
//	ed = PROG_TO_EDICT(pr_global_struct->self);

	ed = PROG_TO_EDICT(progs.qcc_self);
	ED_Print (ed);
	ED_Free (ed);
	Host_Error ("Program error");
#endif
}

/*
 =================
 PF_setorigin

 This is the only valid way to move an object without using the physics of the world (setting velocity and waiting).  Directly changing origin will not set internal links correctly, so clipping would be messed up.  This should be called when an object is spawned, and then only if it is teleported.

 setorigin (entity, origin)
 =================
 */
void qcc_setorigin(int entid, vector origin)
{
    edict_t *e;
    e = PROG_TO_EDICT(entid);
    set_qcc_origin(e, origin);
    SV_LinkEdict(e, false);
}

/*
 =================
 PF_traceline

 Used for use tracing and shot targeting
 Traces are blocked by bbox and exact bsp entityes, and also slide box entities
 if the tryents flag is set.

 traceline (vector1, vector2, tryents)
 =================
 */
void qcc_traceline(vector v1, vector v2, float nomonsterf, int entid)
{
    trace_t trace;
    int nomonsters;
    edict_t *ent;

    nomonsters = nomonsterf;
    ent = PROG_TO_EDICT(entid);

    trace = SV_Move(v1.v, vec3_origin, vec3_origin, v2.v, nomonsters, ent);

    /*	pr_global_struct->trace_allsolid = trace.allsolid;
     pr_global_struct->trace_startsolid = trace.startsolid;
     pr_global_struct->trace_fraction = trace.fraction;
     pr_global_struct->trace_inwater = trace.inwater;
     pr_global_struct->trace_inopen = trace.inopen;
     VectorCopy (trace.endpos, pr_global_struct->trace_endpos.v);
     VectorCopy (trace.plane.normal, pr_global_struct->trace_plane_normal.v);
     pr_global_struct->trace_plane_dist =  trace.plane.dist;
     if (trace.ent)
     pr_global_struct->trace_ent = EDICT_TO_PROG(trace.ent);
     else
     pr_global_struct->trace_ent = EDICT_TO_PROG(sv.edicts);
     */
    progs.qcc_trace_allsolid = trace.allsolid;
    progs.qcc_trace_startsolid = trace.startsolid;
    progs.qcc_trace_fraction = trace.fraction;
    progs.qcc_trace_inwater = trace.inwater;
    progs.qcc_trace_inopen = trace.inopen;
    VectorCopy(trace.endpos, progs.qcc_trace_endpos.v);
    VectorCopy(trace.plane.normal, progs.qcc_trace_plane_normal.v);
    progs.qcc_trace_plane_dist = trace.plane.dist;
    if (trace.ent)
        progs.qcc_trace_ent = EDICT_TO_PROG(trace.ent);
    else
        progs.qcc_trace_ent = EDICT_TO_PROG(sv.edicts);
}
/*
 =================
 PF_vectoyaw

 float vectoyaw(vector)
 =================
 */
float qcc_vectoyaw(vector value1)
{
    float yaw;

//	value1 = G_VECTOR(OFS_PARM0);

    if (value1.v[1] == 0 && value1.v[0] == 0)
        yaw = 0;
    else
    {
        yaw = (int) (atan2f(value1.v[1], value1.v[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;
    }
    return yaw;
}

// entity (entity start, .string field, string match) find = #5;
int qcc_find(int entid, uint16_t offset, uint16_t match)
#ifdef QUAKE2
#error not implemented
#else
{
    const char *s, *t;
    edict_t *ed;
#if !EDICT_LINKED_LIST
#error
	int		e;
	e = NUM_FOR_EDICT(PROG_TO_EDICT(entid));
	s = getStringFromIndex(match);
	if (!s)
		PR_RunError ("PF_Find: bad search string");

	for (e++ ; e < sv.num_edicts ; e++)
	{
		ed = EDICT_NUM(e);
		if (ed->free)
			continue;
        int snum = 0;
        switch (offset)
        {
            case offsetof (big_entvars_t, qcc_targetname):
                snum = get_qcc_targetname(ed);
                break;
            case offsetof (big_entvars_t, qcc_classname):
                snum = get_qcc_classname(ed);
                break;
            case offsetof (big_entvars_t, qcc_target):
                snum = get_qcc_target(ed);
                break;
    		default:
                printf("Unknown case %d\r\n", offset);
                FIXME("Attempting to find for an implemented case\r\n");
                snum = 0;
        }
        t = getStringFromIndex(snum);

		if (!t)
			continue;
		if (!strcmp(t,s)) // note: need to perform actually strcmp because one could have an arbitrary string ?
		{
			return EDICT_TO_PROG(ed);// (byte*) ed - (byte*) sv.edicts;
		}
	}
    return 0;
    #else
    ed = PROG_TO_EDICT(entid);
    s = getStringFromIndex(match);
	// next-hack: FIXME, there might be some issues in fields not present, returning 0 in match.
	if (match == 0)
	    return 0;
    if (!s)
    {
        printf("Search idx = %d\r\n", match);
        PR_RunError("PF_Find: bad search string");
    }
    ed = getNextEdict(ed);
    while (ed != END_EDICT)
    {
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (!ed->free)
#endif
        {
            int snum = 0;
            switch (offset)
            {
                case offsetof(big_entvars_t, qcc_targetname):
                    snum = get_qcc_targetname(ed);
                    break;
                case offsetof(big_entvars_t, qcc_classname):
                    snum = get_qcc_classname(ed);
                    break;
                case offsetof(big_entvars_t, qcc_target):
                    snum = get_qcc_target(ed);
                    break;
                default:
                    printf("Unknown case %d\r\n", offset);
                    FIXME("Attempting to find for an implemented case\r\n");
                    snum = 0;
            }
            t = getStringFromIndex(snum);
            if (t && !strcmp(t, s)) // note: need to perform actually strcmp because one could have an arbitrary string ?
            {
                return EDICT_TO_PROG(ed);
            }
        }
        ed = getNextEdict(ed);
    }
    return 0;
#endif
#endif
}

float qcc_rint(float f)
{
    if (f > 0)
        return (int) (f + 0.5);
    else
        return (int) (f - 0.5);
}
float qcc_floor(float v)
{
    return floorf_m(v);
}
float qcc_ceil(float v)
{
    return ceilf_m(v);
}
uint16_t qcc_precache_sound(uint16_t stringIndex)
{
    const char *s;
    int i;

    if (sv.state != ss_loading)
        PR_RunError("PF_Precache_*: Precache can only be done in spawn functions");
    s = getStringFromIndex(stringIndex);

    PR_CheckEmptyString(s);

    for (i = 0; i < MAX_SOUNDS; i++)
    {
        if (!get_sv_sound_precache(i))
        {
            set_sv_sound_precache(i, stringIndex);
            return i;
        }
        if (!strcmp(get_sv_sound_precache(i), s))
            return i;
    }
    PR_RunError("PF_precache_sound: overflow");
    return stringIndex;
}
uint16_t qcc_precache_sound2(uint16_t stringIndex)
{
    return qcc_precache_sound(stringIndex);
}

uint16_t qcc_precache_model(uint16_t stringIndex)
{
    const char *s;
    int i;

    if (sv.state != ss_loading)
        PR_RunError("PF_Precache_*: Precache can only be done in spawn functions");

    s = getStringFromIndex(stringIndex);

    PR_CheckEmptyString(s);

    for (i = 0; i < MAX_MODELS; i++)
    {
        if (!sv.model_precache[i])
        {
#if WIN32
		    printf("PRECACHE MODEL %i %s\r\n",i, s);
#endif
            sv.model_precache[i] = s;
            sv.models[i] = Mod_ForName(s, true);
            return 0;
        }
        if (!strcmp(sv.model_precache[i], s))
            return 0;
    }
    PR_RunError("PF_precache_model: overflow");
    return stringIndex;
}
uint16_t qcc_precache_model2(uint16_t stringIndex)
{
    return qcc_precache_model(stringIndex);
}

/*
 =================
 PF_setsize

 the size box is rotated by the current angle

 setsize (entity, minvector, maxvector)
 =================
 */
void qcc_setsize(int en, vector min, vector max)
{
    edict_t *e = PROG_TO_EDICT(en);

    //	e = G_EDICT(OFS_PARM0);
//	min = G_VECTOR(OFS_PARM1);
//	max = G_VECTOR(OFS_PARM2);
    SetMinMaxSize(e, min.v, max.v, false);
}
float qcc_vlen(vector v)
{
    float modsq = v.x * v.x + v.y * v.y + v.z * v.z;
    return sqrtf_m(modsq);
}
int qcc_spawn(uint16_t className)
{
    edict_t *ed;
    ed = ED_Alloc(className);
    return EDICT_TO_PROG(ed);
}

/*
 =================
 PF_sprint

 single print to a specific client

 sprint(clientent, value)
 =================
 */

void qcc_sprint(int entity, uint16_t stringIndex)
{
    client_t *client;
    int entnum;

    entnum = NUM_FOR_EDICT(PROG_TO_EDICT(entity));
    //G_EDICTNUM(entity);
    char s[256];
    snprintf(s, sizeof(s), "%s", getStringFromIndex(stringIndex));

    if (entnum < 1 || entnum > svs.maxclients)
    {
        Con_Printf("tried to sprint to a non-client\n");
        return;
    }

    client = &svs.clients[entnum - 1];
    MSG_WriteChar(&client->message, svc_print);
    MSG_WriteString(&client->message, s);
}
/*
 =================
 PF_centerprint

 single print to a specific client

 centerprint(clientent, value)
 =================
 */
void qcc_centerprint(int entity, uint16_t stringIndex)
{
    client_t *client;
    int entnum;

    entnum = NUM_FOR_EDICT(PROG_TO_EDICT(entity));
    char s[256];
    snprintf(s, sizeof(s), "%s", getStringFromIndex(stringIndex));

    if (entnum < 1 || entnum > svs.maxclients)
    {
        Con_Printf("tried to sprint to a non-client\n");
        return;
    }

    client = &svs.clients[entnum - 1];

    MSG_WriteChar(&client->message, svc_centerprint);
    MSG_WriteString(&client->message, s);
}
/*
 ==============
 PF_changeyaw

 This was a major timewaster in progs, so it was converted to C
 ==============
 */
void qcc_ChangeYaw(void)
{
    edict_t *ent;
    float ideal, current, move, speed;

//	ent = PROG_TO_EDICT(pr_global_struct->self);
    ent = PROG_TO_EDICT(progs.qcc_self);
    current = anglemod( VEC(get_qcc_angles(ent))[1]);
    ideal = get_qcc_ideal_yaw(ent);
    speed = get_qcc_yaw_speed(ent);

    if (current == ideal)
        return;
    move = ideal - current;
    if (ideal > current)
    {
        if (move >= 180)
            move = move - 360;
    }
    else
    {
        if (move <= -180)
            move = move + 360;
    }
    if (move > 0)
    {
        if (move > speed)
            move = speed;
    }
    else
    {
        if (move < -speed)
            move = -speed;
    }

    set_qcc_angles_y(ent, anglemod(current + move));
}
/*
 ===============
 PF_walkmove

 float(float yaw, float dist) walkmove
 ===============
 */
float qcc_walkmove(float yaw, float dist)
{
    edict_t *ent;
    //float	yaw, dist;
    vec3_t move;
    //dfunction_t	*oldf;
    int oldself;

//	ent = PROG_TO_EDICT(pr_global_struct->self);
    ent = PROG_TO_EDICT(progs.qcc_self);

    if (!((int) get_qcc_flags(ent) & (FL_ONGROUND | FL_FLY | FL_SWIM)))
    {
//		G_FLOAT(OFS_RETURN) = 0;
        return 0;
    }

    yaw = yaw * M_PI * 2 / 360;

    move[0] = cos_t(yaw) * dist;
    move[1] = sin_t(yaw) * dist;
    move[2] = 0;

// save program state, because SV_movestep may call other progs
    //oldf = pr_xfunction;
//	oldself = pr_global_struct->self;
    oldself = progs.qcc_self;

    float rtn = SV_movestep(ent, move, true);

// restore program state
    //pr_xfunction = oldf;
//	pr_global_struct->self = oldself;
    progs.qcc_self = oldself;
    return rtn;
}
/*
 =================
 PF_normalize

 vector normalize(vector)
 =================
 */
vector qcc_normalize(vector value1)
{
    vector newvalue;
    float new;

    new = value1.v[0] * value1.v[0] + value1.v[1] * value1.v[1] + value1.v[2] * value1.v[2];

    if (new == 0)
        newvalue.v[0] = newvalue.v[1] = newvalue.v[2] = 0;
    else
    {
        new = sqrtf_m(new);
        new = 1 / new;
        newvalue.v[0] = value1.v[0] * new;
        newvalue.v[1] = value1.v[1] * new;
        newvalue.v[2] = value1.v[2] * new;
    }

    return newvalue;
}
//
byte checkpvs[((MAX_MAP_LEAFS + 31) / 32) * 4];   // next-hack: must be here, because it's not calculated every frame :(
//
int PF_newcheckclient(int check)
{
    int i;
    byte *pvs;
    player_edict_t *ent;
    mleaf_t *leaf;
    vec3_t org;

// cycle to the next one
#if HAS_MULTIPLAYER
	if (check < 1)
		check = 1;
	if (check > svs.maxclients)
		check = svs.maxclients;

	if (check == svs.maxclients)
		i = 1;
	else
		i = check + 1;

	for ( ;  ; i++)
	{
		if (i == svs.maxclients+1)
			i = 1;
#warning doable as list but this is only for 1 client.
		ent = EDICT_NUM(i);

		if (i == check)
			break;	// didn't find anything else
#if !EDICT_LINKED_LIST_WITH_WATCH
		if (ent->free)
			continue;
#endif
		if (get_qcc_health(ent) <= 0)
			continue;
		if ((int)get_qcc_flags(ent) & FL_NOTARGET)
			continue;

	// anything that is a client, or has a client as an enemy
		break;
	}
#else
    (void) check;
    i = 1;
    ent = svs.clients[0].edict;
#endif
// get the PVS for the entity
    VectorAdd(VEC(get_qcc_origin((edict_t*) ent)), VEC(get_qcc_view_ofs((edict_t*) ent)), org);
    leaf = Mod_PointInLeaf(org, sv.worldmodel);
    static mleaf_t *oldleaf = 0;
    if (oldleaf != leaf)
    {
        pvs = Mod_LeafPVS(leaf, sv.worldmodel);
        // next-hack: why copying ? because Mod_LeafPVS is used in many functions.
#if !SEPARATE_BRUSH_MODEL_DATA
      memcpy (checkpvs, pvs, (sv.worldmodel->numleafs+7)>>3 );
    #else
        Q_memcpy(checkpvs, pvs, (sv.worldmodel->brushModelData->numleafs + 7) >> 3);
#endif
    }
    oldleaf = leaf;
    return i;
}
/*
 =================
 PF_checkclient

 Returns a client (or object that has a client enemy) that would be a
 valid target.

 If there are more than one valid options, they are cycled each frame

 If (self.origin + self.viewofs) is not in the PVS of the current target,
 it is not returned at all.

 name checkclient ()
 =================
 */
#define	MAX_CHECK	16

int c_invis, c_notvis;
int qcc_checkclient(void)
{
    edict_t *ent, *self;
    mleaf_t *leaf;
    int l;
    vec3_t view;

// find a new check if on a new frame
    if (sv.time - sv.lastchecktime >= 0.1)
    {
        sv.lastcheck = PF_newcheckclient(sv.lastcheck);
        sv.lastchecktime = sv.time;
    }
#if HAS_MULTIPLAYER
// return check if it might be visible
	ent = EDICT_NUM(sv.lastcheck);
#else
    ent = (edict_t*) svs.clients[0].edict;
#endif
#if EDICT_LINKED_LIST_WITH_WATCH
	if ( get_qcc_health(ent) <= 0)
#else
    if (ent->free || get_qcc_health(ent) <= 0)

#endif
    {
//		RETURN_EDICT(sv.edicts);
        return 0;
    }

// if current entity can't possibly see the check entity, return 0
//	self = PROG_TO_EDICT(pr_global_struct->self);
    self = PROG_TO_EDICT(progs.qcc_self);
    VectorAdd(VEC(get_qcc_origin(self)), VEC(get_qcc_view_ofs(self)), view);
    leaf = Mod_PointInLeaf(view, sv.worldmodel);
#if !SEPARATE_BRUSH_MODEL_DATA
	l = (leaf - sv.worldmodel->leafs) - 1;
#else
    l = (leaf - sv.worldmodel->brushModelData->leafs) - 1;
#endif
    if ((l < 0) || !(checkpvs[l >> 3] & (1 << (l & 7))))
    {
        c_notvis++;
        //RETURN_EDICT(sv.edicts);
        return 0;
    }

// might be able to see it
    c_invis++;
    return EDICT_TO_PROG(ent);
}
/*
 ===============================================================================

 MESSAGE WRITING

 ===============================================================================
 */

#define	MSG_BROADCAST	0		// unreliable to all
#define	MSG_ONE			1		// reliable to one (msg_entity)
#define	MSG_ALL			2		// reliable to all
#define	MSG_INIT		3		// write to the init string

sizebuf_t* WriteDest(int dest)
{
    //    printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    int entnum;
//	int		dest;
    edict_t *ent;

//	dest = G_FLOAT(OFS_PARM0);
    switch (dest)
    {
        case MSG_BROADCAST:
            return &sv.datagram;

        case MSG_ONE:
#if USE_PROGSDAT
		ent = PROG_TO_EDICT(pr_global_struct->msg_entity);
#else
            ent = PROG_TO_EDICT(progs.qcc_msg_entity);

#endif
            entnum = NUM_FOR_EDICT(ent);
            if (entnum < 1 || entnum > svs.maxclients)
                PR_RunError("WriteDest: not a client");
            return &svs.clients[entnum - 1].message;

        case MSG_ALL:
            return &sv.reliable_datagram;

        case MSG_INIT:
            return &sv.signon;

        default:
            PR_RunError("WriteDest: bad destination");
            break;
    }

    return NULL;
}
/*
 =================
 PF_bprint

 broadcast print to everyone on server

 bprint(value)
 =================
 */
void qcc_bprint(uint16_t stringIndex)
{

    const char *s = getStringFromIndex(stringIndex);
    SV_BroadcastPrintf("%s", s);
}

void qcc_WriteByte(float dst, float data)
{
    MSG_WriteByte(WriteDest(dst), data);
}

void qcc_WriteChar(float dst, float data)
{
    MSG_WriteChar(WriteDest(dst), data);
}

void qcc_WriteShort(float dst, float data)
{
    MSG_WriteShort(WriteDest(dst), data);
}

void qcc_WriteLong(float dst, float data)
{
    MSG_WriteLong(WriteDest(dst), data);
}

void qcc_WriteAngle(float dst, float data)
{
    MSG_WriteAngle(WriteDest(dst), data);
}

void qcc_WriteCoord(float dst, float data)
{
    MSG_WriteCoord(WriteDest(dst), data);
}

void qcc_WriteString(float dst, uint16_t string)
{
    MSG_WriteString(WriteDest(dst), getStringFromIndex(string));
}

void qcc_WriteEntity(float dst, int data)
{
    MSG_WriteShort(WriteDest(dst), NUM_FOR_EDICT(PROG_TO_EDICT(data)));
}

/*
 =================
 PF_findradius

 Returns a chain of entities that have origins within a spherical area

 findradius (origin, radius)
 =================
 */
int qcc_findradius(vector org, float rad)
{
    edict_t *ent, *chain;
//	float	rad;
//	float	*org;
    vec3_t eorg;
    int i, j;

    chain = (edict_t*) sv.edicts;

//	org = G_VECTOR(OFS_PARM0);
//	rad = G_FLOAT(OFS_PARM1);

    ent = NEXT_EDICT(sv.edicts);
    for (i = 1; i < sv.num_edicts; i++, ent = NEXT_EDICT(ent))
    {
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (ent->free)
            continue;
#endif
        if (get_qcc_solid(ent) == SOLID_NOT)
            continue;
        if (get_qcc_takedamage(ent) == DAMAGE_NO) //next-hack: added to prevent including things that are not thing or can't be damaged. This function is only used for damage purpose.
            continue;
        for (j = 0; j < 3; j++)
            eorg[j] = org.v[j] - (VEC(get_qcc_origin(ent))[j] + (VEC(get_qcc_mins(ent))[j] + VEC(get_qcc_maxs(ent))[j]) * 0.5);
        if (Length(eorg) > rad)
            continue;

        set_qcc_chain(ent, EDICT_TO_PROG(chain));
        chain = ent;
    }

    //RETURN_EDICT(chain);
    return EDICT_TO_PROG(chain);
}
/*
 =================
 PF_particle

 particle(origin, color, count)
 =================
 */
void qcc_particle(vector org, vector dir, float color, float count)
{
    //float		*org, *dir;
    //float		color;
    //float		count;

    //org = G_VECTOR(OFS_PARM0);
    //dir = G_VECTOR(OFS_PARM1);
    //color = G_FLOAT(OFS_PARM2);
    //count = G_FLOAT(OFS_PARM3);
    SV_StartParticle(org.v, dir.v, color, count);
}
uint16_t qcc_precache_file(uint16_t s)
{	// precache_file is only used to copy files with qcc, it does nothing
    return s;
}
uint16_t qcc_precache_file2(uint16_t s)
{	// precache_file is only used to copy files with qcc, it does nothing
    return s;
}
/*
 ===============
 PF_lightstyle

 void(float style, string value) lightstyle
 ===============
 */
void qcc_lightstyle(float stylef, uint16_t value)
{
    int style = stylef;
    const char *val;

    //style = G_FLOAT(OFS_PARM0);
    val = getStringFromIndex(value);

// change the string in sv

#if DIRECT_SINGLE_PLAYER
    sv.lightstyles_idx[style] = value;
    sv.lightstyles_len[style] = strlen(val);
#else
	sv.lightstyles[style] = val;
#endif

// send message to all clients on this server
    if (sv.state != ss_active)
        return;
#if !DIRECT_SINGLE_PLAYER
	for (j=0, client = svs.clients ; j<svs.maxclients ; j++, client++)
		if (client->active || client->spawned)
		{
			MSG_WriteChar (&client->message, svc_lightstyle);
			MSG_WriteChar (&client->message,style);
			MSG_WriteString (&client->message, val);
		}
#endif
}
/*
 =========
 PF_dprint
 =========
 */
AUX_SECTION char tempPrintString[TEMP_STRING_SIZE];
void qcc_dprint(uint16_t s)
{
    Con_DPrintf("%s", getStringFromIndex(s));
}

uint16_t qcc_ftos(float v)
{
//	float	v;
//	v = G_FLOAT(OFS_PARM0);

    if (v == (int) v)
        sprintf(getStringFromIndex(tempPrintString_string_index), "%d", (int) v);
    else
        sprintf(getStringFromIndex(tempPrintString_string_index), "%5.1f", v);
    return tempPrintString_string_index;
//	G_INT(OFS_RETURN) = pr_string_temp - pr_strings;
}

float qcc_fabs(float v)
{
    return fabsf_m(v);
}

uint16_t qcc_vtos(vector v)
{
    sprintf(getStringFromIndex(tempPrintString_string_index), "'%5.1f %5.1f %5.1f'", v.v[0], v.v[1], v.v[2]);
    return tempPrintString_string_index;
}
/*
 =================
 PF_stuffcmd

 Sends text over to the client's execution buffer

 stuffcmd (clientent, value)
 =================
 */
void qcc_stuffcmd(int ent, uint16_t value)
{
    int entnum;
    client_t *old;

    entnum = NUM_FOR_EDICT(PROG_TO_EDICT(ent));
    if (entnum < 1 || entnum > svs.maxclients)
        PR_RunError("Parm 0 not a client");
//	str = G_STRING(OFS_PARM1);
    const char *str = getStringFromIndex(value);
    old = host_client;
    host_client = &svs.clients[entnum - 1];
    Host_ClientCommands("%s", str);
    host_client = old;
}
/*
 ===============
 PF_droptofloor

 void() droptofloor
 ===============
 */
float qcc_droptofloor(void)
{
    edict_t *ent;
    vec3_t end;
    trace_t trace;

    //ent = PROG_TO_EDICT(pr_global_struct->self);
    ent = PROG_TO_EDICT(progs.qcc_self);

    VectorCopy(VEC(get_qcc_origin(ent)), end);
    end[2] -= 256;

    trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, false, ent);

    if (trace.fraction == 1 || trace.allsolid)
        return 0;
    else
    {
        set_qcc_origin(ent, vectorize(trace.endpos));
        SV_LinkEdict(ent, false);
        set_qcc_flags(ent, (int) get_qcc_flags(ent) | FL_ONGROUND);
        set_qcc_groundentity(ent, EDICT_TO_PROG(trace.ent));
        return 1;
    }
}
/*
 =============
 PF_aim

 Pick a vector for the player to shoot along
 vector aim(entity, missilespeed)
 =============
 */
#if USE_ORIGINAL_CVAR
cvar_t sv_aim =
{   "sv_aim", "0.93"};
#endif
vector qcc_aim(int entid, float speed)
{
    vector vret;
    edict_t *ent, *check, *bestent;
    vec3_t start, dir, end, bestdir;
    int i;
    trace_t tr;
    float dist, bestdist;
    // next-hack: actually the original PF_aim read speed, but did not use it.
    (void) speed;
    ent = PROG_TO_EDICT(entid); //G_EDICT(OFS_PARM0);
    //speed = G_FLOAT(OFS_PARM1);

    VectorCopy(VEC(get_qcc_origin(ent)), start);
    start[2] += 20;

// try sending a trace straight
//	VectorCopy (pr_global_struct->v_forward.v, dir);
    VectorCopy(progs.qcc_v_forward.v, dir);

    VectorMA(start, 2048, dir, end);
    tr = SV_Move(start, vec3_origin, vec3_origin, end, false, ent);

    if (tr.ent && get_qcc_takedamage(tr.ent) == DAMAGE_AIM && (!teamplay || get_qcc_team(ent) <= 0 || get_qcc_team(ent) != get_qcc_team(tr.ent)))
    {
        //VectorCopy (pr_global_struct->v_forward.v, vret.v);
        VectorCopy(progs.qcc_v_forward.v, vret.v);
        return vret;
    }

// try all possible entities
    VectorCopy(dir, bestdir);
    bestdist = sv_aim;
    bestent = NULL;

    check = NEXT_EDICT(sv.edicts);
    for (i = 1; i < sv.num_edicts; i++, check = NEXT_EDICT(check))
    {
        if (get_qcc_takedamage(check) != DAMAGE_AIM)
            continue;
        if (check == ent)
            continue;
        if (teamplay && get_qcc_team(ent) > 0 && get_qcc_team(ent) == get_qcc_team(check))
            continue;	// don't aim at teammate
#if USE_OLD_ABS_CALLS
		for (j=0 ; j<3 ; j++)
			end[j] = VEC(get_qcc_origin(check))[j] + 0.5f*(VEC(get_qcc_mins(check))[j] + VEC(get_qcc_maxs(check))[j]);
#else
        vector checkOrigin = get_qcc_origin(check);
        vector checkMins = get_qcc_mins(check);
        vector checkMaxs = get_qcc_maxs(check);
        end[0] = checkOrigin.v[0] + 0.5f * (checkMins.v[0] + checkMaxs.v[0]);
        end[1] = checkOrigin.v[1] + 0.5f * (checkMins.v[1] + checkMaxs.v[1]);
        end[2] = checkOrigin.v[2] + 0.5f * (checkMins.v[2] + checkMaxs.v[2]);

#endif
        VectorSubtract(end, start, dir);
        VectorNormalize(dir);
//		dist = DotProduct (dir, pr_global_struct->v_forward.v);
        dist = DotProduct(dir, progs.qcc_v_forward.v);

        if (dist < bestdist)
            continue;	// to far to turn
        tr = SV_Move(start, vec3_origin, vec3_origin, end, false, ent);
        if (tr.ent == check)
        {	// can shoot at this one
            bestdist = dist;
            bestent = check;
        }
    }

    if (bestent)
    {
        VectorSubtract(VEC(get_qcc_origin(bestent)), VEC(get_qcc_origin(ent)), dir);
//		dist = DotProduct (dir, pr_global_struct->v_forward.v);
        dist = DotProduct(dir, progs.qcc_v_forward.v);
//		VectorScale (pr_global_struct->v_forward.v, dist, end);
        VectorScale(progs.qcc_v_forward.v, dist, end);
        end[2] = dir[2];
        VectorNormalize(end);
        VectorCopy(end, vret.v);
        return vret;
    }
    else
    {
        VectorCopy(bestdir, vret.v);
        return vret;
    }
}
/*
 =============
 PF_pointcontents
 =============
 */
float qcc_pointcontents(vector v)
{
    return SV_PointContents(v.v);
}
/*
 =================
 PF_vectoangles

 vector vectoangles(vector)
 =================
 */
vector qcc_vectoangles(vector v)
{
    float *value1;
    float forward;
    float yaw, pitch;

    value1 = v.v;

    if (value1[1] == 0 && value1[0] == 0)
    {
        yaw = 0;
        if (value1[2] > 0)
            pitch = 90;
        else
            pitch = 270;
    }
    else
    {
        yaw = (int) (atan2f(value1[1], value1[0]) * 180 / M_PI);
        if (yaw < 0)
            yaw += 360;

        forward = sqrtf_m(value1[0] * value1[0] + value1[1] * value1[1]);
        pitch = (int) (atan2f(value1[2], forward) * 180 / M_PI);
        if (pitch < 0)
            pitch += 360;
    }
    vector r;
    r.v[0] = pitch;
    r.v[1] = yaw;
    r.v[2] = 0;
    return r;
}
/*
 =================
 PF_cvar

 float cvar (string)
 =================
 */
float qcc_cvar(uint16_t s)
{
    const char *str;

    str = getStringFromIndex(s);

    return Cvar_VariableValue(str);
}
/*
 =================
 PF_localcmd

 Sends text over to the client's execution buffer

 localcmd (string)
 =================
 */
void qcc_localcmd(uint16_t sidx)
{
    const char *str;

    str = getStringFromIndex(sidx);
    Cbuf_AddText(str);
}

/*
 =================
 PF_cvar_set

 float cvar (string)
 =================
 */
void qcc_cvar_set(uint16_t s1, uint16_t s2)
{
    const char *var, *val;

    var = getStringFromIndex(s1);
    val = getStringFromIndex(s2);

    Cvar_Set(var, val);
}

/*
 ==============
 PF_changelevel
 ==============
 */
//extern float qcc_intermission_running;
void qcc_changelevel(uint16_t sidx)
{
#ifdef QUAKE2
	char	*s1, *s2;

	if (svs.changelevel_issued)
		return;
	svs.changelevel_issued = true;

	s1 = G_STRING(OFS_PARM0);
	s2 = G_STRING(OFS_PARM1);

	if ((int)pr_global_struct->serverflags & (SFL_NEW_UNIT | SFL_NEW_EPISODE))
		Cbuf_AddText (va("changelevel %s %s\n",s1, s2));
	else
		Cbuf_AddText (va("changelevel2 %s %s\n",s1, s2));
#else
    const char *s;
    progs.qcc_intermission_running = 0;   // next-hack added
// make sure we don't issue two changelevels
    if (svs.changelevel_issued)
        return;
    svs.changelevel_issued = true;
    char vastr[64];

    s = getStringFromIndex(sidx);
    Cbuf_AddText(va(vastr, "changelevel %s\n", s));
#endif
}

/*
 ==============
 PF_setspawnparms
 ==============
 */
void qcc_setspawnparms(int entid)
{
    edict_t *ent;
    int i;
    client_t *client;

    ent = PROG_TO_EDICT(entid);
    i = NUM_FOR_EDICT(ent);
    if (i < 1 || i > svs.maxclients)
        PR_RunError("Entity is not a client");

    // copy spawn parms out of the client_t
    client = svs.clients + (i - 1);

//	for (i=0 ; i< NUM_SPAWN_PARMS ; i++)
//		(&pr_global_struct->parm1)[i] = client->spawn_parms[i];
    i = 0;
    progs.qcc_parm1 = client->spawn_parms[i++];
    progs.qcc_parm2 = client->spawn_parms[i++];
    progs.qcc_parm3 = client->spawn_parms[i++];
    progs.qcc_parm4 = client->spawn_parms[i++];
    progs.qcc_parm5 = client->spawn_parms[i++];
    progs.qcc_parm6 = client->spawn_parms[i++];
    progs.qcc_parm7 = client->spawn_parms[i++];
    progs.qcc_parm8 = client->spawn_parms[i++];
    progs.qcc_parm9 = client->spawn_parms[i++];
    progs.qcc_parm10 = client->spawn_parms[i++];
    progs.qcc_parm11 = client->spawn_parms[i++];
    progs.qcc_parm12 = client->spawn_parms[i++];
    progs.qcc_parm13 = client->spawn_parms[i++];
    progs.qcc_parm14 = client->spawn_parms[i++];
    progs.qcc_parm15 = client->spawn_parms[i++];
    progs.qcc_parm16 = client->spawn_parms[i++];

}
/*
 =================
 PF_errror

 This is a TERMINAL error, which will kill off the entire server.
 Dumps self.

 error(value)
 =================
 */
void qcc_error(uint16_t idx)
{
    edict_t *ed;

    Con_Printf("======SERVER ERROR in %s:\n%s\n", "TBD", getStringFromIndex(idx));
    ed = PROG_TO_EDICT(progs.qcc_self);
    ED_Print(ed);

    Host_Error("QCC Program error");
}
/*
 =================
 PF_ambientsound

 =================
 */
void qcc_ambientsound(vector posv, uint16_t sampleStringIdx, float vol, float attenuation)
{
    const char *samp;
    float *pos = posv.v;
    int i, soundnum;

    samp = getStringFromIndex(sampleStringIdx);

    // check to see if samp was properly precached
    for (soundnum = 0; get_sv_sound_precache(soundnum); soundnum++)
        if (!strcmp(get_sv_sound_precache(soundnum), samp))
            break;

    if (!get_sv_sound_precache(soundnum))
    {
        Con_Printf("no sound precache: %s\n", samp);
        return;
    }

// add an svc_spawnambient command to the level signon packet

    MSG_WriteByte(&sv.signon, svc_spawnstaticsound);
    for (i = 0; i < 3; i++)
        MSG_WriteCoord(&sv.signon, pos[i]);

    MSG_WriteByte(&sv.signon, soundnum);

    MSG_WriteByte(&sv.signon, vol * 255);
    MSG_WriteByte(&sv.signon, attenuation * 64);

}
void qcc_makestatic(int entid)
{
    /*next-hack: let's comment a little bit. A static entity is an entity living only on the client side. this is probably to reduce the need of big entities structure on the server
     and speeding up. But if you are using a single player, then static entities might make less sense*/
#if DIRECT_SINGLE_PLAYER
    static_light_edict_t *ent;
//
    ent = PROG_TO_EDICT(entid);
//
    entLeaves_t *el;
    el = get_entLeaves((edict_t*) ent);    // guaranteed not null because get_qcc_modelindex was not 0.
    el->needs_relink = 0;
    el->num_leaves = 0; // reset num of leaves
    SV_FindTouchedLeafs((edict_t*) ent, sv.worldmodel->brushModelData->nodes, el);
    //
    static_light_romEntvars_t *tmp = ent->v.romEntvars;
    //
    ent->v.romEntvars = storeToInternalFlash(tmp, (3 + sizeof(static_light_romEntvars_t)) & ~3);
    Z_Free(tmp);
    return;
#else
        edict_t *ent;
        int   i;

        #error


	MSG_WriteByte (&sv.signon,svc_spawnstatic);
#if USE_PROGSDAT
	MSG_WriteByte (&sv.signon, SV_ModelIndex(pr_strings + get_qcc_model(ent)));
#else
	MSG_WriteByte (&sv.signon, SV_ModelIndex(getStringFromIndex(get_qcc_model(ent))));
#endif
	MSG_WriteByte (&sv.signon, get_qcc_frame(ent));
	MSG_WriteByte (&sv.signon, get_qcc_colormap(ent));
	MSG_WriteByte (&sv.signon, get_qcc_skin(ent));
	for (i=0 ; i<3 ; i++)
	{
		MSG_WriteCoord(&sv.signon, VEC(get_qcc_origin(ent))[i]);
		MSG_WriteAngle(&sv.signon, VEC(get_qcc_angles(ent))[i]);
	}

// throw the entity away now
	ED_Free (ent);
#endif
}

/*
 =============
 PF_checkbottom
 =============
 */
float qcc_checkbottom(int entid)
{
    edict_t *ent;

    ent = PROG_TO_EDICT(entid);

    return SV_CheckBottom(ent);
}
void qcc_coredump(void)
{
    ED_PrintEdicts();
}
void qcc_traceon(void)
{
    ///pr_trace = true;
}

void qcc_traceoff(void)
{
    //pr_trace = false;
}

void qcc_eprint(int eid)
{
    ED_PrintNum(NUM_FOR_EDICT(PROG_TO_EDICT(eid)));
}
/*
 =============
 PF_nextent

 entity nextent(entity)
 =============
 */
int qcc_nextent(int eid)
{
    edict_t *ent;
#if !EDICT_LINKED_LIST
    int     i;
	i = NUM_FOR_EDICT(PROG_TO_EDICT(eid));
	while (1)
	{
		i++;
		if (i == sv.num_edicts)
		{
			//RETURN_EDICT(sv.edicts);
			return 0;
		}
		ent = EDICT_NUM(i);
		if (!ent->free)
		{
//			RETURN_EDICT(ent);
			return EDICT_TO_PROG(ent);
		}
	}
#else
    ent = PROG_TO_EDICT(eid);
    while (1)
    {
        ent = getNextEdict(ent);
        if (END_EDICT == ent)
        {
            //RETURN_EDICT(sv.edicts);
            return 0;
        }
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (!ent->free)  // guaranteed to be used
#endif
        {
            return EDICT_TO_PROG(ent);
        }
    }

#endif
}
#endif // USE_CRAPPY_PROGDAT

