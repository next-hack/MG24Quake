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
// sv_phys.c
#include "quakedef.h"

/*


 pushmove objects do not obey gravity, and do not interact with each other or trigger fields, but block normal movement and push normal objects when they move.

 onground is set for toss objects when they come to a complete rest.  it is set for steping or walking objects

 doors, plats, etc are SOLID_BSP, and MOVETYPE_PUSH
 bonus items are SOLID_TRIGGER touch, and MOVETYPE_TOSS
 corpses are SOLID_NOT and MOVETYPE_TOSS
 crates are SOLID_BBOX and MOVETYPE_TOSS
 walking monsters are SOLID_SLIDEBOX and MOVETYPE_STEP
 flying/floating monsters are SOLID_SLIDEBOX and MOVETYPE_FLY

 solid_edge items only clip against bsp models.

 */
#if USE_ORIGINAL_CVAR
cvar_t	sv_friction = {"sv_friction","4",false,true};
cvar_t	sv_stopspeed = {"sv_stopspeed","100"};
cvar_t	sv_gravity = {"sv_gravity","800",false,true};
cvar_t	sv_maxvelocity = {"sv_maxvelocity","2000"};
cvar_t	sv_nostep = {"sv_nostep","0"};
#endif
#ifdef QUAKE2
static	vec3_t	vec_origin = {0.0, 0.0, 0.0};
#endif

#define	MOVE_EPSILON	0.01

void SV_Physics_Toss(edict_t *ent);

/*
 ================
 SV_CheckAllEnts
 ================
 */
void SV_CheckAllEnts(void)
{
    int e;
    edict_t *check;

// see if any solid entities are inside the final position
    check = NEXT_EDICT(sv.edicts);
    for (e = 1; e < sv.num_edicts; e++, check = NEXT_EDICT(check))
    {
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (check->free)
            continue;
#endif
        if (get_qcc_movetype(check) == MOVETYPE_PUSH || get_qcc_movetype(check) == MOVETYPE_NONE
#ifdef QUAKE2
		|| check->v.movetype == MOVETYPE_FOLLOW
#endif
            || get_qcc_movetype(check) == MOVETYPE_NOCLIP)
            continue;

        if (SV_TestEntityPosition(check))
            Con_Printf("entity in invalid position\n");
    }
}

/*
 ================
 SV_CheckVelocity
 ================
 */
void SV_CheckVelocity(edict_t *ent)
{
    int i;
    vec3_t vel, orig;
    VectorCopy(VEC(get_qcc_velocity(ent)), vel);
    VectorCopy(VEC(get_qcc_origin(ent)), orig);
//
// bound velocity
//
    for (i = 0; i < 3; i++)
    {
        // next-hack: IS_NAN() macro will trigger the annoying "breaking strict aliasing rule" warning. Let's disable it.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"

        if (IS_NAN(vel[i]))
        {
#if USE_PROGSDAT
			Con_Printf ("Got a NaN velocity on %s\n", pr_strings + get_qcc_classname(ent));
#else
            Con_Printf("Got a NaN velocity on %s\n", getStringFromIndex(get_qcc_classname(ent)));
#endif
            vel[i] = 0;
        }
        if (IS_NAN(orig[i]))
        {
#if USE_PROGSDAT
			Con_Printf ("Got a NaN origin on %s\n", pr_strings + get_qcc_classname(ent));
#else
            Con_Printf("Got a NaN origin on %s\n", getStringFromIndex(get_qcc_classname(ent)));
#endif
            orig[i] = 0;
        }
#pragma GCC diagnostic pop

        if (vel[i] > sv_maxvelocity)
            vel[i] = sv_maxvelocity;
        else if (vel[i] < -sv_maxvelocity)
            vel[i] = -sv_maxvelocity;
    }
    set_qcc_velocity(ent, vectorize(vel));
    set_qcc_origin(ent, vectorize(orig));
}

/*
 =============
 SV_RunThink

 Runs thinking code if time.  There is some play in the exact time the think
 function will be called, because it is called before any movement is done
 in a frame.  Not used for pushmove objects, because they must be exact.
 Returns false if the entity removed itself.
 =============
 */
qboolean SV_RunThink(edict_t *ent)
{
    float thinktime;

    thinktime = get_qcc_nextthink(ent);
    if (thinktime <= 0 || thinktime > sv.time + host_frametime)
        return true;

    if (thinktime < sv.time)
        thinktime = sv.time;	// don't let things stay in the past.
                                // it is possible to start that way
                                // by a trigger with a local time.
    set_qcc_nextthink(ent, 0);  // next-hack: added this hack...
#if USE_PROGSDAT
	pr_global_struct->time = thinktime;
	pr_global_struct->self = EDICT_TO_PROG(ent);
	pr_global_struct->other = EDICT_TO_PROG(sv.edicts);
	PR_ExecuteProgram (get_qcc_think(ent));
#else
#if EDICT_LINKED_LIST_WITH_WATCH
    ED_WatchForFree(ent);
#endif
    progs.qcc_time = thinktime;
    progs.qcc_self = EDICT_TO_PROG(ent);
    progs.qcc_other = EDICT_TO_PROG(sv.edicts);
//	printf("Executing think for edict %p, type %d, name %s\r\n", ent, ent->qcc_classname, getStringFromIndex(ent->qcc_classname));
    qcc_PR_ExecuteProgram(get_qcc_think(ent));

#endif
#if !EDICT_LINKED_LIST_WITH_WATCH
    return !ent->free;
#else
    return !ED_hasBeenWatchedEntityFreed(ent);
#endif
}

/*
 ==================
 SV_Impact

 Two entities have touched, so run their touch functions
 ==================
 */
void SV_Impact(edict_t *e1, edict_t *e2)
{
    int old_self, old_other;
#if USE_PROGSDAT
	old_self = pr_global_struct->self;
	old_other = pr_global_struct->other;
	pr_global_struct->time = sv.time;

	if (get_qcc_touch(e1) && get_qcc_solid(e1) != SOLID_NOT)
	{
		pr_global_struct->self = EDICT_TO_PROG(e1);
		pr_global_struct->other = EDICT_TO_PROG(e2);
		PR_ExecuteProgram (get_qcc_touch(e1));
	}

	if (get_qcc_touch(e2) && get_qcc_solid(e2) != SOLID_NOT)
	{
		pr_global_struct->self = EDICT_TO_PROG(e2);
		pr_global_struct->other = EDICT_TO_PROG(e1);
		PR_ExecuteProgram (get_qcc_touch(e2));
	}

	pr_global_struct->self = old_self;
	pr_global_struct->other = old_other;
	#else
    old_self = progs.qcc_self;
    old_other = progs.qcc_other;
    progs.qcc_time = sv.time;

    if (get_qcc_touch(e1) && get_qcc_solid(e1) != SOLID_NOT)
    {
        progs.qcc_self = EDICT_TO_PROG(e1);
        progs.qcc_other = EDICT_TO_PROG(e2);
        qcc_PR_ExecuteProgram(get_qcc_touch(e1));
    }

    if (get_qcc_touch(e2) && get_qcc_solid(e2) != SOLID_NOT)
    {
        progs.qcc_self = EDICT_TO_PROG(e2);
        progs.qcc_other = EDICT_TO_PROG(e1);
        qcc_PR_ExecuteProgram(get_qcc_touch(e2));
    }

    progs.qcc_self = old_self;
    progs.qcc_other = old_other;
#endif
}

/*
 ==================
 ClipVelocity

 Slide off of the impacting object
 returns the blocked flags (1 = floor, 2 = step / wall)
 ==================
 */
#define	STOP_EPSILON	0.1

int ClipVelocity(vec3_t in, vec3_t normal, vec3_t out, float overbounce)
{
    float backoff;
    float change;
    int i, blocked;

    blocked = 0;
    if (normal[2] > 0)
        blocked |= 1;		// floor
    if (!normal[2])
        blocked |= 2;		// step

    backoff = DotProduct (in, normal) * overbounce;

    for (i = 0; i < 3; i++)
    {
        change = normal[i] * backoff;
        out[i] = in[i] - change;
        if (out[i] > -STOP_EPSILON && out[i] < STOP_EPSILON)
            out[i] = 0;
    }

    return blocked;
}

/*
 ============
 SV_FlyMove

 The basic solid body movement clip that slides along multiple planes
 Returns the clipflags if the velocity was modified (hit something solid)
 1 = floor
 2 = wall / step
 4 = dead stop
 If steptrace is not NULL, the trace of any vertical wall hit will be stored
 ============
 */
#define	MAX_CLIP_PLANES	5
int SV_FlyMove(edict_t *ent, float time, trace_t *steptrace)
{
    int bumpcount, numbumps;
    vec3_t dir;
    float d;
    int numplanes;
    vec3_t planes[MAX_CLIP_PLANES];
    vec3_t primal_velocity, original_velocity, new_velocity;
    int i, j;
    trace_t trace;
    vec3_t end;
    float time_left;
    int blocked;

    numbumps = 4;

    blocked = 0;
    VectorCopy(VEC(get_qcc_velocity(ent)), original_velocity);
    VectorCopy(VEC(get_qcc_velocity(ent)), primal_velocity);
    numplanes = 0;

    time_left = time;

    for (bumpcount = 0; bumpcount < numbumps; bumpcount++)
    {
        if (!VEC(get_qcc_velocity(ent))[0] && !VEC(get_qcc_velocity(ent))[1] && !VEC(get_qcc_velocity(ent))[2])
            break;

        for (i = 0; i < 3; i++)
            end[i] = VEC(get_qcc_origin(ent))[i] + time_left * VEC(get_qcc_velocity(ent))[i];

        trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, false, ent);

        if (trace.allsolid)
        {	// entity is trapped in another solid
            set_qcc_velocity(ent, vectorize(vec3_origin));
            return 3;
        }

        if (trace.fraction > 0)
        {	// actually covered some distance
            set_qcc_origin(ent, vectorize(trace.endpos));
            VectorCopy(VEC(get_qcc_velocity(ent)), original_velocity);
            numplanes = 0;
        }

        if (trace.fraction == 1)
            break;		// moved the entire distance

        if (!trace.ent)
            Sys_Error("SV_FlyMove: !trace.ent");

        if (trace.plane.normal[2] > 0.7)
        {
            blocked |= 1;		// floor
            if (get_qcc_solid(trace.ent) == SOLID_BSP)
            {
                set_qcc_flags(ent, (int) get_qcc_flags(ent) | FL_ONGROUND);
                set_qcc_groundentity(ent, EDICT_TO_PROG(trace.ent));
            }
        }
        if (!trace.plane.normal[2])
        {
            blocked |= 2;		// step
            if (steptrace)
            {
                *steptrace = trace;	// save for player extrafriction
            }
        }
//
// run the impact function
//
#if EDICT_LINKED_LIST_WITH_WATCH
        ED_WatchForFree(ent);
#endif
        SV_Impact(ent, trace.ent);

#if EDICT_LINKED_LIST_WITH_WATCH
		if (ED_hasBeenWatchedEntityFreed(ent))
			break;		// removed by the impact function
#else
        if (ent->free)
            break;		// removed by the impact function

#endif

        time_left -= time_left * trace.fraction;

        // cliped to another plane
        if (numplanes >= MAX_CLIP_PLANES)
        {	// this shouldn't really happen
            set_qcc_velocity(ent, vectorize(vec3_origin));
            return 3;
        }

        VectorCopy(trace.plane.normal, planes[numplanes]);
        numplanes++;

//
// modify original_velocity so it parallels all of the clip planes
//
        for (i = 0; i < numplanes; i++)
        {
            ClipVelocity(original_velocity, planes[i], new_velocity, 1);
            for (j = 0; j < numplanes; j++)
                if (j != i)
                {
                    if (DotProduct (new_velocity, planes[j]) < 0)
                    {
                        break;	// not ok
                    }
                }
            if (j == numplanes)
                break;
        }

        if (i != numplanes)
        {	// go along this plane
            set_qcc_velocity(ent, vectorize(new_velocity));
        }
        else
        {	// go along the crease
            if (numplanes != 2)
            {
//				Con_Printf ("clip velocity, numplanes == %i\n",numplanes);
                set_qcc_velocity(ent, vectorize(vec3_origin));
                return 7;
            }
            CrossProduct(planes[0], planes[1], dir);
            d = DotProduct(dir, VEC(get_qcc_velocity(ent)));
            vec3_t tmp;
            VectorScale(dir, d, tmp);
            set_qcc_velocity(ent, vectorize(tmp));
        }

//
// if original velocity is against the original velocity, stop dead
// to avoid tiny occilations in sloping corners
//
        if (DotProduct (VEC(get_qcc_velocity(ent)), primal_velocity) <= 0)
        {
            set_qcc_velocity(ent, vectorize(vec3_origin));
            return blocked;
        }
    }

    return blocked;
}

/*
 ============
 SV_AddGravity

 ============
 */
void SV_AddGravity(edict_t *ent)
{
    float ent_gravity;

#ifdef QUAKE2
	if (ent->v.gravity)
		ent_gravity = ent->v.gravity;
	else
		ent_gravity = 1.0;
#else
#if USE_PROGSDAT
    eval_t  *val;
	val = GetEdictFieldValue(ent, "gravity");
	if (val && val->_float)
		ent_gravity = val->_float;
	else
#else
    ent_gravity = 1.0;
#endif
#endif
    set_qcc_velocity_z(ent, VEC(get_qcc_velocity(ent))[2] - ent_gravity * sv_gravity * host_frametime);
}

/*
 ===============================================================================

 PUSHMOVE

 ===============================================================================
 */

/*
 ============
 SV_PushEntity

 Does not change the entities velocity at all
 ============
 */
trace_t SV_PushEntity(edict_t *ent, vec3_t push)
{
    trace_t trace;
    vec3_t end;

    VectorAdd(VEC(get_qcc_origin(ent)), push, end);
    if (get_qcc_movetype(ent) == MOVETYPE_FLYMISSILE)
        trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, MOVE_MISSILE, ent);
    else if (get_qcc_solid(ent) == SOLID_TRIGGER || get_qcc_solid(ent) == SOLID_NOT)
        // only clip against bmodels
        trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, MOVE_NOMONSTERS, ent);
    else
        trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, MOVE_NORMAL, ent);

    set_qcc_origin(ent, vectorize(trace.endpos));
    SV_LinkEdict(ent, true);

    if (trace.ent)
        SV_Impact(ent, trace.ent);

    return trace;
}

/*
 ============
 SV_PushMove

 ============
 */
void SV_PushMove(edict_t *pusher, float movetime)
{
    int i, e;
    edict_t *check, *block;
    vec3_t mins, maxs, move;
    vec3_t entorig, pushorig;
    int num_moved;
    edict_t *moved_edict[MAX_MOVABLE_EDICTS];
    vec3_t moved_from[MAX_MOVABLE_EDICTS];

    if (!VEC(get_qcc_velocity(pusher))[0] && !VEC(get_qcc_velocity(pusher))[1] && !VEC(get_qcc_velocity(pusher))[2])
    {
        set_qcc_ltime(pusher, get_qcc_ltime(pusher) + movetime);
        return;
    }
#if USE_OLD_ABS_CALLS
    for (i=0; i<3; i++)
    {
        move[i] = VEC(get_qcc_velocity(pusher))[i] * movetime;
        mins[i] = VEC(get_qcc_absmin(pusher))[i] + move[i];
        maxs[i] = VEC(get_qcc_absmax(pusher))[i] + move[i];
    }
#else
    vector vmove = get_qcc_velocity(pusher);
    move[0] = vmove.v[0] * movetime;
    move[1] = vmove.v[1] * movetime;
    move[2] = vmove.v[2] * movetime;
    //
    vector absmins = get_qcc_absmin(pusher);
    mins[0] = absmins.v[0] + move[0];
    mins[1] = absmins.v[1] + move[1];
    mins[2] = absmins.v[2] + move[2];
    //
    vector absmaxs = get_qcc_absmax(pusher);
    maxs[0] = absmaxs.v[0] + move[0];
    maxs[1] = absmaxs.v[1] + move[1];
    maxs[2] = absmaxs.v[2] + move[2];

#endif

    VectorCopy(VEC(get_qcc_origin(pusher)), pushorig);

// move the pusher to it's final position
    vec3_t temp;
    VectorAdd(VEC(get_qcc_origin(pusher)), move, temp);
    set_qcc_origin(pusher, vectorize(temp));
    set_qcc_ltime(pusher, get_qcc_ltime(pusher) + movetime);
    SV_LinkEdict(pusher, false);

// see if any solid entities are inside the final position
    num_moved = 0;
    check = NEXT_EDICT(sv.edicts);
    for (e = 1; e < sv.num_edicts; e++, check = NEXT_EDICT(check))
    {
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (check->free)
            continue;
#endif
        if (get_qcc_movetype(check) == MOVETYPE_PUSH || get_qcc_movetype(check) == MOVETYPE_NONE
#ifdef QUAKE2
		|| check->v.movetype == MOVETYPE_FOLLOW
#endif
            || get_qcc_movetype(check) == MOVETYPE_NOCLIP)
            continue;

        // if the entity is standing on the pusher, it will definately be moved
        if (!(((int) get_qcc_flags(check) & FL_ONGROUND) && PROG_TO_EDICT(get_qcc_groundentity(check)) == pusher))
        {
#if USE_OLD_ABS_CALLS
			if ( VEC(get_qcc_absmin(check))[0] >= maxs[0]
			|| VEC(get_qcc_absmin(check))[1] >= maxs[1]
			|| VEC(get_qcc_absmin(check))[2] >= maxs[2]
			|| VEC(get_qcc_absmax(check))[0] <= mins[0]
			|| VEC(get_qcc_absmax(check))[1] <= mins[1]
			|| VEC(get_qcc_absmax(check))[2] <= mins[2] )
				continue;
#else
            vector checkabsmin = get_qcc_absmin(check);
            if (checkabsmin.v[0] >= maxs[0])
                continue;
            if (checkabsmin.v[1] >= maxs[1])
                continue;
            if (checkabsmin.v[2] >= maxs[2])
                continue;
            //
            vector checkabsmax = get_qcc_absmax(check);
            if (checkabsmax.v[0] <= mins[0])
                continue;
            if (checkabsmax.v[1] <= mins[1])
                continue;
            if (checkabsmax.v[2] <= mins[2])
                continue;

#endif
            // see if the ent's bbox is inside the pusher's final position
            if (!SV_TestEntityPosition(check))
                continue;
        }

        // remove the onground flag for non-players
        if (get_qcc_movetype(check) != MOVETYPE_WALK)
            set_qcc_flags(check, (int) get_qcc_flags(check) & ~FL_ONGROUND);

        VectorCopy(VEC(get_qcc_origin(check)), entorig);
        VectorCopy(VEC(get_qcc_origin(check)), moved_from[num_moved]);
        moved_edict[num_moved] = check;
        num_moved++;
        if (num_moved >= MAX_MOVABLE_EDICTS)
        {
            FIXME("TOO MANY ENTITIES MOVED");
            num_moved--;
        }

        // try moving the contacted entity
        set_qcc_solid(pusher, SOLID_NOT);
        SV_PushEntity(check, move);
        set_qcc_solid(pusher, SOLID_BSP);

        // if it is still inside the pusher, block
        block = SV_TestEntityPosition(check);
        if (block)
        {	// fail the move
            if (VEC(get_qcc_mins(check))[0] == VEC(get_qcc_maxs(check))[0])
                continue;
            if (get_qcc_solid(check) == SOLID_NOT || get_qcc_solid(check) == SOLID_TRIGGER)
            {	// corpse
                set_qcc_mins_x(check, 0);
                set_qcc_mins_y(check, 0);
                set_qcc_maxs(check, get_qcc_mins(check));
                continue;
            }

            set_qcc_origin(check, vectorize(entorig));
            SV_LinkEdict(check, true);

            set_qcc_origin(pusher, vectorize(pushorig));
            SV_LinkEdict(pusher, false);
            set_qcc_ltime(pusher, get_qcc_ltime(pusher) - movetime);

            // if the pusher has a "blocked" function, call it
            // otherwise, just stay in place until the obstacle is gone
            if (get_qcc_blocked(pusher))
            {
#if USE_PROGSDAT
				pr_global_struct->self = EDICT_TO_PROG(pusher);
				pr_global_struct->other = EDICT_TO_PROG(check);
				PR_ExecuteProgram (get_qcc_blocked(pusher));
#else
                progs.qcc_self = EDICT_TO_PROG(pusher);
                progs.qcc_other = EDICT_TO_PROG(check);
                qcc_PR_ExecuteProgram(get_qcc_blocked(pusher));
#endif
            }

            // move back any entities we already moved
            for (i = 0; i < num_moved; i++)
            {
                //
                set_qcc_origin(moved_edict[i], vectorize(moved_from[i]));
                SV_LinkEdict(moved_edict[i], false);
            }
            return;
        }
    }

}

#ifdef QUAKE2
/*
============
SV_PushRotate

============
*/
void SV_PushRotate (edict_t *pusher, float movetime)
{
	int			i, e;
	edict_t		*check, *block;
	vec3_t		move, a, amove;
	vec3_t		entorig, pushorig;
	int			num_moved;
	edict_t		*moved_edict[MAX_EDICTS];
	vec3_t		moved_from[MAX_EDICTS];
	vec3_t		org, org2;
	vec3_t		forward, right, up;

	if (!pusher->v.avelocity[0] && !pusher->v.avelocity[1] && !pusher->v.avelocity[2])
	{
		pusher->v.ltime += movetime;
		return;
	}

	for (i=0 ; i<3 ; i++)
		amove[i] = pusher->v.avelocity[i] * movetime;

	VectorSubtract (vec3_origin, amove, a);
	AngleVectors (a, forward, right, up);

	VectorCopy (pusher->v.angles, pushorig);

// move the pusher to it's final position

	VectorAdd (pusher->v.angles, amove, pusher->v.angles);
	pusher->v.ltime += movetime;
	SV_LinkEdict (pusher, false);


// see if any solid entities are inside the final position
	num_moved = 0;
	check = NEXT_EDICT(sv.edicts);
	for (e=1 ; e<sv.num_edicts ; e++, check = NEXT_EDICT(check))
	{
		if (check->free)
			continue;
		if (check->v.movetype == MOVETYPE_PUSH
		|| check->v.movetype == MOVETYPE_NONE
		|| check->v.movetype == MOVETYPE_FOLLOW
		|| check->v.movetype == MOVETYPE_NOCLIP)
			continue;

	// if the entity is standing on the pusher, it will definately be moved
		if ( ! ( ((int)check->v.flags & FL_ONGROUND)
		&& PROG_TO_EDICT(check->v.groundentity) == pusher) )
		{
			if ( check->v.absmin[0] >= pusher->v.absmax[0]
			|| check->v.absmin[1] >= pusher->v.absmax[1]
			|| check->v.absmin[2] >= pusher->v.absmax[2]
			|| check->v.absmax[0] <= pusher->v.absmin[0]
			|| check->v.absmax[1] <= pusher->v.absmin[1]
			|| check->v.absmax[2] <= pusher->v.absmin[2] )
				continue;

		// see if the ent's bbox is inside the pusher's final position
			if (!SV_TestEntityPosition (check))
				continue;
		}

	// remove the onground flag for non-players
		if (check->v.movetype != MOVETYPE_WALK)
			check->v.flags = (int)check->v.flags & ~FL_ONGROUND;

		VectorCopy (check->v.origin, entorig);
		VectorCopy (check->v.origin, moved_from[num_moved]);
		moved_edict[num_moved] = check;
		num_moved++;

		// calculate destination position
		VectorSubtract (check->v.origin, pusher->v.origin, org);
		org2[0] = DotProduct (org, forward);
		org2[1] = -DotProduct (org, right);
		org2[2] = DotProduct (org, up);
		VectorSubtract (org2, org, move);

		// try moving the contacted entity
		pusher->v.solid = SOLID_NOT;
		SV_PushEntity (check, move);
		pusher->v.solid = SOLID_BSP;

	// if it is still inside the pusher, block
		block = SV_TestEntityPosition (check);
		if (block)
		{	// fail the move
			if (check->v.mins[0] == check->v.maxs[0])
				continue;
			if (check->v.solid == SOLID_NOT || check->v.solid == SOLID_TRIGGER)
			{	// corpse
				check->v.mins[0] = check->v.mins[1] = 0;
				VectorCopy (check->v.mins, check->v.maxs);
				continue;
			}

			VectorCopy (entorig, check->v.origin);
			SV_LinkEdict (check, true);

			VectorCopy (pushorig, pusher->v.angles);
			SV_LinkEdict (pusher, false);
			pusher->v.ltime -= movetime;

			// if the pusher has a "blocked" function, call it
			// otherwise, just stay in place until the obstacle is gone
			if (pusher->v.blocked)
			{
				pr_global_struct->self = EDICT_TO_PROG(pusher);
				pr_global_struct->other = EDICT_TO_PROG(check);
				PR_ExecuteProgram (pusher->v.blocked);
			}

		// move back any entities we already moved
			for (i=0 ; i<num_moved ; i++)
			{
				VectorCopy (moved_from[i], moved_edict[i]->v.origin);
				VectorSubtract (moved_edict[i]->v.angles, amove, moved_edict[i]->v.angles);
				SV_LinkEdict (moved_edict[i], false);
			}
			return;
		}
		else
		{
			VectorAdd (check->v.angles, amove, check->v.angles);
		}
	}


}
#endif

/*
 ================
 SV_Physics_Pusher

 ================
 */
void SV_Physics_Pusher(edict_t *ent)
{
    float thinktime;
    float oldltime;
    float movetime;

    oldltime = get_qcc_ltime(ent);

    thinktime = get_qcc_nextthink(ent);
    if (thinktime < get_qcc_ltime(ent) + host_frametime)
    {
        movetime = thinktime - get_qcc_ltime(ent);
        if (movetime < 0)
            movetime = 0;
    }
    else
        movetime = host_frametime;

    if (movetime)
    {
#ifdef QUAKE2
		if (ent->v.avelocity[0] || ent->v.avelocity[1] || ent->v.avelocity[2])
			SV_PushRotate (ent, movetime);
		else
#endif
        SV_PushMove(ent, movetime);	// advances ent->v.ltime if not blocked
    }

    if (thinktime > oldltime && thinktime <= get_qcc_ltime(ent))
    {
        set_qcc_nextthink(ent, 0);
#if USE_PROGSDAT
		pr_global_struct->time = sv.time;
		pr_global_struct->self = EDICT_TO_PROG(ent);
		pr_global_struct->other = EDICT_TO_PROG(sv.edicts);
		PR_ExecuteProgram (get_qcc_think(ent));
#else
        progs.qcc_time = sv.time;
        progs.qcc_self = EDICT_TO_PROG(ent);
        progs.qcc_other = EDICT_TO_PROG(sv.edicts);
#if EDICT_LINKED_LIST_WITH_WATCH
        ED_WatchForFree(ent);
#endif
        qcc_PR_ExecuteProgram(get_qcc_think(ent));

#endif // USE_PROGSDAT

#if !EDICT_LINKED_LIST_WITH_WATCH
        if (ent->free)
            return;
#else
        if (ED_hasBeenWatchedEntityFreed(ent))
        {
            return;
        }
#endif
    }

}

/*
 ===============================================================================

 CLIENT MOVEMENT

 ===============================================================================
 */

/*
 =============
 SV_CheckStuck

 This is a big hack to try and fix the rare case of getting stuck in the world
 clipping hull.
 =============
 */
void SV_CheckStuck(edict_t *ent)
{
    int i, j;
    int z;
    vec3_t org;

    if (!SV_TestEntityPosition(ent))
    {
        set_qcc_oldorigin(ent, get_qcc_origin(ent));
        return;
    }

    VectorCopy(VEC(get_qcc_origin(ent)), org);
    set_qcc_origin(ent, get_qcc_oldorigin(ent));
    if (!SV_TestEntityPosition(ent))
    {
        Con_DPrintf("Unstuck.\n");
        SV_LinkEdict(ent, true);
        return;
    }

    for (z = 0; z < 18; z++)
        for (i = -1; i <= 1; i++)
            for (j = -1; j <= 1; j++)
            {
                set_qcc_origin_x(ent, org[0] + i);
                set_qcc_origin_y(ent, org[1] + j);
                set_qcc_origin_z(ent, org[2] + z);
                if (!SV_TestEntityPosition(ent))
                {
                    Con_DPrintf("Unstuck.\n");
                    SV_LinkEdict(ent, true);
                    return;
                }
            }

    set_qcc_origin(ent, vectorize(org));
    Con_DPrintf("player is stuck.\n");
}

/*
 =============
 SV_CheckWater
 =============
 */
qboolean SV_CheckWater(edict_t *ent)
{
    vec3_t point;
    int cont;
#ifdef QUAKE2
    int truecont;
#endif
#if USE_OLD_ABS_CALLS
    point[0] = VEC(get_qcc_origin(ent))[0];
    point[1] = VEC(get_qcc_origin(ent))[1];
    point[2] = VEC(get_qcc_origin(ent))[2] + VEC(get_qcc_mins(ent))[2] + 1;
#else
    vector entOrigin = get_qcc_origin(ent);
    float entMinsZ = get_qcc_mins(ent).z;
    point[0] = entOrigin.v[0];
    point[1] = entOrigin.v[1];
    point[2] = entOrigin.v[2] + entMinsZ + 1;
#endif
    set_qcc_waterlevel(ent, 0);
    set_qcc_watertype(ent, CONTENTS_EMPTY);
    cont = SV_PointContents(point);
    if (cont <= CONTENTS_WATER)
    {
#ifdef QUAKE2
		truecont = SV_TruePointContents (point);
#endif
        set_qcc_watertype(ent, cont);
        set_qcc_waterlevel(ent, 1);
#if USE_OLD_ABS_CALLS
		point[2] = VEC(get_qcc_origin(ent))[2] + (VEC(get_qcc_mins(ent))[2] + VEC(get_qcc_maxs(ent))[2])*0.5;
		cont = SV_PointContents (point);
		if (cont <= CONTENTS_WATER)
		{
			set_qcc_waterlevel(ent,  2);
			point[2] = VEC(get_qcc_origin(ent))[2] + VEC(get_qcc_view_ofs(ent))[2];
			cont = SV_PointContents (point);
			if (cont <= CONTENTS_WATER)
				set_qcc_waterlevel(ent,  3);
		}
#else
        float entMaxsZ = get_qcc_maxs(ent).z;
        point[2] = entOrigin.v[2] + (entMinsZ + entMaxsZ) * 0.5f;
        cont = SV_PointContents(point);
        if (cont <= CONTENTS_WATER)
        {
            set_qcc_waterlevel(ent, 2);
            point[2] = entOrigin.v[2] + VEC(get_qcc_view_ofs(ent))[2];
            cont = SV_PointContents(point);
            if (cont <= CONTENTS_WATER)
                set_qcc_waterlevel(ent, 3);
        }
#endif
    }

    return get_qcc_waterlevel(ent) > 1;
}

/*
 ============
 SV_WallFriction

 ============
 */
void SV_WallFriction(edict_t *ent, trace_t *trace)
{
    vec3_t forward, right, up;
    float d, i;
    vec3_t into, side;

    AngleVectors(VEC(get_qcc_v_angle(ent)), forward, right, up);
    d = DotProduct(trace->plane.normal, forward);

    d += 0.5;
    if (d >= 0)
        return;

// cut the tangential velocity
    i = DotProduct(trace->plane.normal, VEC(get_qcc_velocity(ent)));
    VectorScale(trace->plane.normal, i, into);
    VectorSubtract(VEC(get_qcc_velocity(ent)), into, side);

    set_qcc_velocity_x(ent, side[0] * (1 + d));
    set_qcc_velocity_y(ent, side[1] * (1 + d));
}

/*
 =====================
 SV_TryUnstick

 Player has come to a dead stop, possibly due to the problem with limited
 float precision at some angle joins in the BSP hull.

 Try fixing by pushing one pixel in each direction.

 This is a hack, but in the interest of good gameplay...
 ======================
 */
int SV_TryUnstick(edict_t *ent, vec3_t oldvel)
{
    int i;
    vec3_t oldorg;
    vec3_t dir;
    int clip;
    trace_t steptrace;

    VectorCopy(VEC(get_qcc_origin(ent)), oldorg);
    VectorCopy(vec3_origin, dir);

    for (i = 0; i < 8; i++)
    {
// try pushing a little in an axial direction
        switch (i)
        {
            case 0:
                dir[0] = 2;
                dir[1] = 0;
                break;
            case 1:
                dir[0] = 0;
                dir[1] = 2;
                break;
            case 2:
                dir[0] = -2;
                dir[1] = 0;
                break;
            case 3:
                dir[0] = 0;
                dir[1] = -2;
                break;
            case 4:
                dir[0] = 2;
                dir[1] = 2;
                break;
            case 5:
                dir[0] = -2;
                dir[1] = 2;
                break;
            case 6:
                dir[0] = 2;
                dir[1] = -2;
                break;
            case 7:
                dir[0] = -2;
                dir[1] = -2;
                break;
        }

        SV_PushEntity(ent, dir);

// retry the original move
        set_qcc_velocity_x(ent, oldvel[0]);
        set_qcc_velocity_y(ent, oldvel[1]);
        set_qcc_velocity_z(ent, 0);
        clip = SV_FlyMove(ent, 0.1, &steptrace);

        if (fabsf_m(oldorg[1] - VEC(get_qcc_origin(ent))[1]) > 4 || fabsf_m(oldorg[0] - VEC(get_qcc_origin(ent))[0]) > 4)
        {
//Con_DPrintf ("unstuck!\n");
            return clip;
        }

// go back to the original pos and try again
        set_qcc_origin(ent, vectorize(oldorg));
    }

    set_qcc_velocity(ent, vectorize(vec3_origin));
    return 7;		// still not moving
}

/*
 =====================
 SV_WalkMove

 Only used by players
 ======================
 */
#define	STEPSIZE	18
void SV_WalkMove(edict_t *ent)
{
    vec3_t upmove, downmove;
    vec3_t oldorg, oldvel;
    vec3_t nosteporg, nostepvel;
    int clip;
    int oldonground;
    trace_t steptrace, downtrace;

//
// do a regular slide move unless it looks like you ran into a step
//
    oldonground = (int) get_qcc_flags(ent) & FL_ONGROUND;
    set_qcc_flags(ent, (int) get_qcc_flags(ent) & ~FL_ONGROUND);

    VectorCopy(VEC(get_qcc_origin(ent)), oldorg);
    VectorCopy(VEC(get_qcc_velocity(ent)), oldvel);

    clip = SV_FlyMove(ent, host_frametime, &steptrace);

    if (!(clip & 2))
        return;		// move didn't block on a step

    if (!oldonground && get_qcc_waterlevel(ent) == 0)
        return;		// don't stair up while jumping

    if (get_qcc_movetype(ent) != MOVETYPE_WALK)
        return;		// gibbed by a trigger

    if (sv_nostep)
        return;

    if ((int) get_qcc_flags((edict_t*) sv_player) & FL_WATERJUMP)
        return;

    VectorCopy(VEC(get_qcc_origin(ent)), nosteporg);
    VectorCopy(VEC(get_qcc_velocity(ent)), nostepvel);

//
// try moving up and forward to go up a step
//
    set_qcc_origin(ent, vectorize(oldorg));	// back to start pos

    VectorCopy(vec3_origin, upmove);
    VectorCopy(vec3_origin, downmove);
    upmove[2] = STEPSIZE;
    downmove[2] = -STEPSIZE + oldvel[2] * host_frametime;

// move up
    SV_PushEntity(ent, upmove);	// FIXME: don't link?

// move forward
    set_qcc_velocity_x(ent, oldvel[0]);
    set_qcc_velocity_y(ent, oldvel[1]);
    set_qcc_velocity_z(ent, 0);
    clip = SV_FlyMove(ent, host_frametime, &steptrace);

// check for stuckness, possibly due to the limited precision of floats
// in the clipping hulls
    if (clip)
    {
        if (fabsf_m(oldorg[1] - VEC(get_qcc_origin(ent))[1]) < 0.03125 && fabsf_m(oldorg[0] - VEC(get_qcc_origin(ent))[0]) < 0.03125)
        {	// stepping up didn't make any progress
            clip = SV_TryUnstick(ent, oldvel);
        }
    }

// extra friction based on view angle
    if (clip & 2)
        SV_WallFriction(ent, &steptrace);

// move down
    downtrace = SV_PushEntity(ent, downmove);	// FIXME: don't link?

    if (downtrace.plane.normal[2] > 0.7f)
    {
        if (get_qcc_solid(ent) == SOLID_BSP)
        {
            set_qcc_flags(ent, (int) get_qcc_flags(ent) | FL_ONGROUND);
            set_qcc_groundentity(ent, EDICT_TO_PROG(downtrace.ent));
        }
    }
    else
    {
// if the push down didn't end up on good ground, use the move without
// the step up.  This happens near wall / slope combinations, and can
// cause the player to hop up higher on a slope too steep to climb
        set_qcc_origin(ent, vectorize(nosteporg));
        set_qcc_velocity(ent, vectorize(nostepvel));
    }
}

/*
 ================
 SV_Physics_Client

 Player character actions
 ================
 */
void SV_Physics_Client(edict_t *ent, int num)
{
    vec3_t tmp;
    if (!svs.clients[num - 1].active)
        return;		// unconnected slot

//
// call standard client pre-think
//
#if USE_PROGSDAT
	pr_global_struct->time = sv.time;
	pr_global_struct->self = EDICT_TO_PROG(ent);
	PR_ExecuteProgram (pr_global_struct->PlayerPreThink);
#else
    progs.qcc_time = sv.time;
    progs.qcc_self = EDICT_TO_PROG(ent);
    qcc_PlayerPreThink();

#endif

//
// do a move
//
    SV_CheckVelocity(ent);

//
// decide which move function to call
//
    switch ((int) get_qcc_movetype(ent))
    {
        case MOVETYPE_NONE:
            if (!SV_RunThink(ent))
                return;
            break;

        case MOVETYPE_WALK:
            if (!SV_RunThink(ent))
                return;
            if (!SV_CheckWater(ent) && !((int) get_qcc_flags(ent) & FL_WATERJUMP))
                SV_AddGravity(ent);
            SV_CheckStuck(ent);
#ifdef QUAKE2
		VectorAdd (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);
#endif
            SV_WalkMove(ent);

#ifdef QUAKE2
		VectorSubtract (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);
#endif
            break;

        case MOVETYPE_TOSS:
        case MOVETYPE_BOUNCE:
            SV_Physics_Toss(ent);
            break;

        case MOVETYPE_FLY:
            if (!SV_RunThink(ent))
                return;
            SV_FlyMove(ent, host_frametime, NULL);
            break;

        case MOVETYPE_NOCLIP:
            if (!SV_RunThink(ent))
                return;
            VectorMA(VEC(get_qcc_origin(ent)), host_frametime, VEC(get_qcc_velocity(ent)), tmp);
            set_qcc_origin(ent, vectorize(tmp));
            break;

        default:
            Sys_Error("SV_PhysicsClient: bad movetype %i for entity name %s\r\n", (int) get_qcc_movetype(ent), getStringFromIndex(get_qcc_classname(ent)));
    }

//
// call standard player post-think
//
    SV_LinkEdict(ent, true);
#if USE_PROGSDAT
	pr_global_struct->time = sv.time;
	pr_global_struct->self = EDICT_TO_PROG(ent);
	PR_ExecuteProgram (pr_global_struct->PlayerPostThink);
#else
    progs.qcc_time = sv.time;
    progs.qcc_self = EDICT_TO_PROG(ent);
    qcc_PlayerPostThink();

#endif
}

//============================================================================

/*
 =============
 SV_Physics_None

 Non moving objects can only think
 =============
 */
void SV_Physics_None(edict_t *ent)
{
// regular thinking
    SV_RunThink(ent);
}

#ifdef QUAKE2
/*
=============
SV_Physics_Follow

Entities that are "stuck" to another entity
=============
*/
void SV_Physics_Follow (edict_t *ent)
{
// regular thinking
	SV_RunThink (ent);
	VectorAdd (PROG_TO_EDICT(ent->v.aiment)->v.origin, ent->v.v_angle, ent->v.origin);
	SV_LinkEdict (ent, true);
}
#endif

/*
 =============
 SV_Physics_Noclip

 A moving object that doesn't obey physics
 =============
 */
void SV_Physics_Noclip(edict_t *ent)
{
// regular thinking
    if (!SV_RunThink(ent))
        return;
    vec3_t tmp;
    VectorMA(VEC(get_qcc_angles(ent)), host_frametime, VEC(get_qcc_avelocity(ent)), tmp);
    set_qcc_angles(ent, vectorize(tmp));
    VectorMA(VEC(get_qcc_origin(ent)), host_frametime, VEC(get_qcc_velocity(ent)), tmp);
    set_qcc_origin(ent, vectorize(tmp));
    SV_LinkEdict(ent, false);
}

/*
 ==============================================================================

 TOSS / BOUNCE

 ==============================================================================
 */

/*
 =============
 SV_CheckWaterTransition

 =============
 */
void SV_CheckWaterTransition(edict_t *ent)
{
    int cont;
#ifdef QUAKE2
	vec3_t	point;

	point[0] = ent->v.origin[0];
	point[1] = ent->v.origin[1];
	point[2] = ent->v.origin[2] + ent->v.mins[2] + 1;
	cont = SV_PointContents (point);
#else
    cont = SV_PointContents(VEC(get_qcc_origin(ent)));
#endif
    if (!get_qcc_watertype(ent))
    {	// just spawned here
        set_qcc_watertype(ent, cont);
        set_qcc_waterlevel(ent, 1);
        return;
    }

    if (cont <= CONTENTS_WATER)
    {
        if (get_qcc_watertype(ent) == CONTENTS_EMPTY)
        {	// just crossed into water
            SV_StartSound(ent, 0, "misc/h2ohit1.wav", 255, 1);
        }
        set_qcc_watertype(ent, cont);
        set_qcc_waterlevel(ent, 1);
    }
    else
    {
        if (get_qcc_watertype(ent) != CONTENTS_EMPTY)
        {	// just crossed into water
            SV_StartSound(ent, 0, "misc/h2ohit1.wav", 255, 1);
        }
        set_qcc_watertype(ent, CONTENTS_EMPTY);
        set_qcc_waterlevel(ent, cont);
    }
}

/*
 =============
 SV_Physics_Toss

 Toss, bounce, and fly movement.  When onground, do nothing.
 =============
 */
void SV_Physics_Toss(edict_t *ent)
{
    vec3_t tmp;

    trace_t trace;
    vec3_t move;
    float backoff;
#ifdef QUAKE2
	edict_t	*groundentity;

	groundentity = PROG_TO_EDICT(ent->v.groundentity);
	if ((int)groundentity->v.flags & FL_CONVEYOR)
		VectorScale(groundentity->v.movedir, groundentity->v.speed, ent->v.basevelocity);
	else
		VectorCopy(vec_origin, ent->v.basevelocity);
	SV_CheckWater (ent);
#endif
    // regular thinking
    if (!SV_RunThink(ent))
        return;

#ifdef QUAKE2
	if (ent->v.velocity[2] > 0)
		ent->v.flags = (int)ent->v.flags & ~FL_ONGROUND;

	if ( ((int)ent->v.flags & FL_ONGROUND) )
//@@
		if (VectorCompare(ent->v.basevelocity, vec_origin))
			return;

	SV_CheckVelocity (ent);

// add gravity
	if (! ((int)ent->v.flags & FL_ONGROUND)
		&& ent->v.movetype != MOVETYPE_FLY
		&& ent->v.movetype != MOVETYPE_BOUNCEMISSILE
		&& ent->v.movetype != MOVETYPE_FLYMISSILE)
			SV_AddGravity (ent);

#else
// if onground, return without moving
    if (((int) get_qcc_flags(ent) & FL_ONGROUND))
        return;

    SV_CheckVelocity(ent);

// add gravity
    if (get_qcc_movetype(ent) != MOVETYPE_FLY && get_qcc_movetype(ent) != MOVETYPE_FLYMISSILE)
        SV_AddGravity(ent);
#endif

// move angles
    VectorMA(VEC(get_qcc_angles(ent)), host_frametime, VEC(get_qcc_avelocity(ent)), tmp);
    set_qcc_angles(ent, vectorize(tmp));
// move origin
#ifdef QUAKE2
	VectorAdd (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);
#endif
    VectorScale(VEC(get_qcc_velocity(ent)), host_frametime, move);
#if EDICT_LINKED_LIST_WITH_WATCH
    ED_WatchForFree(ent);
#endif // EDICT_LINKED_LIST
    trace = SV_PushEntity(ent, move);
#ifdef QUAKE2
	VectorSubtract (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);
#endif
    if (trace.fraction == 1)
        return;
#if EDICT_LINKED_LIST_WITH_WATCH
    if (ED_hasBeenWatchedEntityFreed(ent))
        return;
#else
    if (ent->free)
        return;
#endif // EDICT_LINKED_LIST

    if (get_qcc_movetype(ent) == MOVETYPE_BOUNCE)
        backoff = 1.5;
#ifdef QUAKE2
	else if (ent->v.movetype == MOVETYPE_BOUNCEMISSILE)
		backoff = 2.0;
#endif
    else
        backoff = 1;
    ClipVelocity(VEC(get_qcc_velocity(ent)), trace.plane.normal, tmp, backoff);
    set_qcc_velocity(ent, vectorize(tmp));
// stop if on ground
    if (trace.plane.normal[2] > 0.7)
    {
#ifdef QUAKE2
		if (ent->v.velocity[2] < 60 || (ent->v.movetype != MOVETYPE_BOUNCE && ent->v.movetype != MOVETYPE_BOUNCEMISSILE))
#else
        if (VEC(get_qcc_velocity(ent))[2] < 60 || get_qcc_movetype(ent) != MOVETYPE_BOUNCE)
#endif
        {
            set_qcc_flags(ent, (int) get_qcc_flags(ent) | FL_ONGROUND);
            set_qcc_groundentity(ent, EDICT_TO_PROG(trace.ent));
            set_qcc_velocity(ent, vectorize(vec3_origin));
            set_qcc_avelocity(ent, vectorize(vec3_origin));
        }
    }

// check for in water
    SV_CheckWaterTransition(ent);
}

/*
 ===============================================================================

 STEPPING MOVEMENT

 ===============================================================================
 */

/*
 =============
 SV_Physics_Step

 Monsters freefall when they don't have a ground entity, otherwise
 all movement is done with discrete steps.

 This is also used for objects that have become still on the ground, but
 will fall if the floor is pulled out from under them.
 =============
 */
#ifdef QUAKE2
void SV_Physics_Step (edict_t *ent)
{
	qboolean	wasonground;
	qboolean	inwater;
	qboolean	hitsound = false;
	float		*vel;
	float		speed, newspeed, control;
	float		friction;
	edict_t		*groundentity;

	groundentity = PROG_TO_EDICT(ent->v.groundentity);
	if ((int)groundentity->v.flags & FL_CONVEYOR)
		VectorScale(groundentity->v.movedir, groundentity->v.speed, ent->v.basevelocity);
	else
		VectorCopy(vec_origin, ent->v.basevelocity);
//@@
	pr_global_struct->time = sv.time;
	pr_global_struct->self = EDICT_TO_PROG(ent);
	PF_WaterMove();

	SV_CheckVelocity (ent);

	wasonground = (int)ent->v.flags & FL_ONGROUND;
//	ent->v.flags = (int)ent->v.flags & ~FL_ONGROUND;

	// add gravity except:
	//   flying monsters
	//   swimming monsters who are in the water
	inwater = SV_CheckWater(ent);
	if (! wasonground)
		if (!((int)ent->v.flags & FL_FLY))
			if (!(((int)ent->v.flags & FL_SWIM) && (ent->v.waterlevel > 0)))
			{
				if (ent->v.velocity[2] < sv_gravity*-0.1)
					hitsound = true;
				if (!inwater)
					SV_AddGravity (ent);
			}

	if (!VectorCompare(ent->v.velocity, vec_origin) || !VectorCompare(ent->v.basevelocity, vec_origin))
	{
		ent->v.flags = (int)ent->v.flags & ~FL_ONGROUND;
		// apply friction
		// let dead monsters who aren't completely onground slide
		if (wasonground)
			if (!(ent->v.health <= 0.0 && !SV_CheckBottom(ent)))
			{
				vel = ent->v.velocity;
				speed = sqrt(vel[0]*vel[0] +vel[1]*vel[1]);
				if (speed)
				{
					friction = sv_friction;

					control = speed < sv_stopspeed ? sv_stopspeed : speed;
					newspeed = speed - host_frametime*control*friction;

					if (newspeed < 0)
						newspeed = 0;
					newspeed /= speed;

					vel[0] = vel[0] * newspeed;
					vel[1] = vel[1] * newspeed;
				}
			}

		VectorAdd (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);
		SV_FlyMove (ent, host_frametime, NULL);
		VectorSubtract (ent->v.velocity, ent->v.basevelocity, ent->v.velocity);

		// determine if it's on solid ground at all
		{
			vec3_t	mins, maxs, point;
			int		x, y;

			VectorAdd (ent->v.origin, ent->v.mins, mins);
			VectorAdd (ent->v.origin, ent->v.maxs, maxs);

			point[2] = mins[2] - 1;
			for	(x=0 ; x<=1 ; x++)
				for	(y=0 ; y<=1 ; y++)
				{
					point[0] = x ? maxs[0] : mins[0];
					point[1] = y ? maxs[1] : mins[1];
					if (SV_PointContents (point) == CONTENTS_SOLID)
					{
						ent->v.flags = (int)ent->v.flags | FL_ONGROUND;
						break;
					}
				}

		}

		SV_LinkEdict (ent, true);

		if ((int)ent->v.flags & FL_ONGROUND)
			if (!wasonground)
				if (hitsound)
					SV_StartSound (ent, 0, "demon/dland2.wav", 255, 1);
	}

// regular thinking
	SV_RunThink (ent);
	SV_CheckWaterTransition (ent);
}
#else
void SV_Physics_Step(edict_t *ent)
{
    qboolean hitsound;

// freefall if not onground
    if (!((int) get_qcc_flags(ent) & (FL_ONGROUND | FL_FLY | FL_SWIM)))
    {
        if (VEC(get_qcc_velocity(ent))[2] < sv_gravity * -0.1)
            hitsound = true;
        else
            hitsound = false;

        SV_AddGravity(ent);
        SV_CheckVelocity(ent);
        SV_FlyMove(ent, host_frametime, NULL);
        SV_LinkEdict(ent, true);

        if ((int) get_qcc_flags(ent) & FL_ONGROUND)	// just hit ground
        {
            if (hitsound)
                SV_StartSound(ent, 0, "demon/dland2.wav", 255, 1);
        }
    }

// regular thinking
    SV_RunThink(ent);

    SV_CheckWaterTransition(ent);
}
#endif

//============================================================================

/*
 ================
 SV_Physics

 ================
 */
void SV_Physics(void)
{
    int i;
    edict_t *ent;

// let the progs know that a new frame has started
#if USE_PROGSDAT
	pr_global_struct->self = EDICT_TO_PROG(sv.edicts);
	pr_global_struct->other = EDICT_TO_PROG(sv.edicts);
	pr_global_struct->time = sv.time;
	PR_ExecuteProgram (pr_global_struct->StartFrame);
#else

    progs.qcc_self = EDICT_TO_PROG(sv.edicts);
    progs.qcc_other = EDICT_TO_PROG(sv.edicts);
    progs.qcc_time = sv.time;
    qcc_StartFrame();
#endif

//SV_CheckAllEnts ();

//
// treat each object in turn
//
    ent = sv.edicts;
    for (i = 0; i < sv.num_edicts; i++, ent = NEXT_EDICT(ent))
    {
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (ent->free)
            continue;
#endif
#if USE_PROGSDAT
		if (pr_global_struct->force_retouch)
#else
        if (progs.qcc_force_retouch)
#endif
        {
            SV_LinkEdict(ent, true);	// force retouch even for stationary
        }

        if (i > 0 && i <= svs.maxclients)
            SV_Physics_Client(ent, i);
        else if (get_qcc_movetype(ent) == MOVETYPE_PUSH)
            SV_Physics_Pusher(ent);
        else if (get_qcc_movetype(ent) == MOVETYPE_NONE)
            SV_Physics_None(ent);
#ifdef QUAKE2
		else if (ent->v.movetype == MOVETYPE_FOLLOW)
			SV_Physics_Follow (ent);
#endif
        else if (get_qcc_movetype(ent) == MOVETYPE_NOCLIP)
            SV_Physics_Noclip(ent);
        else if (get_qcc_movetype(ent) == MOVETYPE_STEP)
            SV_Physics_Step(ent);
        else if (get_qcc_movetype(ent) == MOVETYPE_TOSS || get_qcc_movetype(ent) == MOVETYPE_BOUNCE
#ifdef QUAKE2
		|| ent->v.movetype == MOVETYPE_BOUNCEMISSILE
#endif
            || get_qcc_movetype(ent) == MOVETYPE_FLY || get_qcc_movetype(ent) == MOVETYPE_FLYMISSILE)
            SV_Physics_Toss(ent);
        else
            Sys_Error("SV_Physics: bad movetype %i for entity name %s\r\n", (int) get_qcc_movetype(ent), getStringFromIndex(get_qcc_classname(ent)));
    }
#if USE_PROGSDAT
	if (pr_global_struct->force_retouch)
		pr_global_struct->force_retouch--;
#else
    if (progs.qcc_force_retouch)
        progs.qcc_force_retouch--;

#endif
    sv.time += host_frametime;
    //
#if !EDICT_IMMEDIATE_FREE
    ED_PendingRemoval();
#endif // EDICT_IMMEDIATE_FREE
}

#ifdef QUAKE2
trace_t SV_Trace_Toss (edict_t *ent, edict_t *ignore)
{
	edict_t	tempent, *tent;
	trace_t	trace;
	vec3_t	move;
	vec3_t	end;
	QDFLOAT	save_frametime;
//	extern particle_t	*active_particles, *free_particles;
//	particle_t	*p;


	save_frametime = host_frametime;
	host_frametime = 0.05;

	memcpy(&tempent, ent, sizeof(edict_t));
	tent = &tempent;

	while (1)
	{
		SV_CheckVelocity (tent);
		SV_AddGravity (tent);
		VectorMA (tent->v.angles, host_frametime, tent->v.avelocity, tent->v.angles);
		VectorScale (tent->v.velocity, host_frametime, move);
		VectorAdd (tent->v.origin, move, end);
		trace = SV_Move (tent->v.origin, tent->v.mins, tent->v.maxs, end, MOVE_NORMAL, tent);
		VectorCopy (trace.endpos, tent->v.origin);

//		p = free_particles;
//		if (p)
//		{
//			free_particles = p->next;
//			p->next = active_particles;
//			active_particles = p;
//
//			p->die = 256;
//			p->color = 15;
//			p->type = pt_static;
//			VectorCopy (vec3_origin, p->vel);
//			VectorCopy (tent->v.origin, p->org);
//		}

		if (trace.ent)
			if (trace.ent != ignore)
				break;
	}
//	p->color = 224;
	host_frametime = save_frametime;
	return trace;
}
#endif
