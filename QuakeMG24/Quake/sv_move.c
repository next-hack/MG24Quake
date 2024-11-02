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
// sv_move.c -- monster movement
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
#define	STEPSIZE	18

/*
 =============
 SV_CheckBottom

 Returns false if any part of the bottom of the entity is off an edge that
 is not a staircase.

 =============
 */
int c_yes, c_no;

qboolean SV_CheckBottom(edict_t *ent)
{
    vec3_t mins, maxs, start, stop;
    trace_t trace;
    int x, y;
    float mid, bottom;

    VectorAdd(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), mins);
    VectorAdd(VEC(get_qcc_origin(ent)), VEC(get_qcc_maxs(ent)), maxs);

// if all of the points under the corners are solid world, don't bother
// with the tougher checks
// the corners must be within 16 of the midpoint
    start[2] = mins[2] - 1;
    for (x = 0; x <= 1; x++)
        for (y = 0; y <= 1; y++)
        {
            start[0] = x ? maxs[0] : mins[0];
            start[1] = y ? maxs[1] : mins[1];
            if (SV_PointContents(start) != CONTENTS_SOLID)
                goto realcheck;
        }

    c_yes++;
    return true;		// we got out easy

    realcheck:
    c_no++;
//
// check it for real...
//
    start[2] = mins[2];

// the midpoint must be within 16 of the bottom
    start[0] = stop[0] = (mins[0] + maxs[0]) * 0.5;
    start[1] = stop[1] = (mins[1] + maxs[1]) * 0.5;
    stop[2] = start[2] - 2 * STEPSIZE;
    trace = SV_Move(start, vec3_origin, vec3_origin, stop, true, ent);

    if (trace.fraction == 1.0)
        return false;
    mid = bottom = trace.endpos[2];

// the corners must be within 16 of the midpoint
    for (x = 0; x <= 1; x++)
        for (y = 0; y <= 1; y++)
        {
            start[0] = stop[0] = x ? maxs[0] : mins[0];
            start[1] = stop[1] = y ? maxs[1] : mins[1];

            trace = SV_Move(start, vec3_origin, vec3_origin, stop, true, ent);

            if (trace.fraction != 1.0 && trace.endpos[2] > bottom)
                bottom = trace.endpos[2];
            if (trace.fraction == 1.0 || mid - trace.endpos[2] > STEPSIZE)
                return false;
        }

    c_yes++;
    return true;
}

/*
 =============
 SV_movestep

 Called by monster program code.
 The move will be adjusted for slopes and stairs, but if the move isn't
 possible, no move is done, false is returned, and
 pr_global_struct->trace_normal is set to the normal of the blocking wall
 =============
 */
qboolean SV_movestep(edict_t *ent, vec3_t move, qboolean relink)
{
    float dz;
    vec3_t oldorg, neworg, end;
    trace_t trace;
    int i;
    edict_t *enemy;

// try the move
    VectorCopy(VEC(get_qcc_origin(ent)), oldorg);
    VectorAdd(VEC(get_qcc_origin(ent)), move, neworg);

// flying monsters don't step up
    if ((int) get_qcc_flags(ent) & (FL_SWIM | FL_FLY))
    {
        // try one move with vertical motion, then one without
        for (i = 0; i < 2; i++)
        {
            VectorAdd(VEC(get_qcc_origin(ent)), move, neworg);
            enemy = PROG_TO_EDICT(get_qcc_enemy(ent));
            if (i == 0 && enemy != sv.edicts)
            {
                dz = VEC(get_qcc_origin(ent))[2] - VEC(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(ent))))[2];
                if (dz > 40)
                    neworg[2] -= 8;
                if (dz < 30)
                    neworg[2] += 8;
            }
            trace = SV_Move(VEC(get_qcc_origin(ent)), VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), neworg, false, ent);

            if (trace.fraction == 1)
            {
                if (((int) get_qcc_flags(ent) & FL_SWIM) && SV_PointContents(trace.endpos) == CONTENTS_EMPTY)
                    return false;	// swim monster left water

                set_qcc_origin(ent, vectorize(trace.endpos));
                if (relink)
                    SV_LinkEdict(ent, true);
                return true;
            }

            if (enemy == sv.edicts)
                break;
        }

        return false;
    }

// push down from a step height above the wished position
    neworg[2] += STEPSIZE;
    VectorCopy(neworg, end);
    end[2] -= STEPSIZE * 2;

    trace = SV_Move(neworg, VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, false, ent);

    if (trace.allsolid)
        return false;

    if (trace.startsolid)
    {
        neworg[2] -= STEPSIZE;
        trace = SV_Move(neworg, VEC(get_qcc_mins(ent)), VEC(get_qcc_maxs(ent)), end, false, ent);
        if (trace.allsolid || trace.startsolid)
            return false;
    }
    if (trace.fraction == 1)
    {
        // if monster had the ground pulled out, go ahead and fall
        if ((int) get_qcc_flags(ent) & FL_PARTIALGROUND)
        {
            vec3_t temp;
            VectorAdd(VEC(get_qcc_origin(ent)), move, temp);
            set_qcc_origin(ent, vectorize(temp));
            if (relink)
                SV_LinkEdict(ent, true);
            set_qcc_flags(ent, (int) get_qcc_flags(ent) & ~FL_ONGROUND);
//	Con_Printf ("fall down\n");
            return true;
        }

        return false;		// walked off an edge
    }

// check point traces down for dangling corners
    set_qcc_origin(ent, vectorize(trace.endpos));

    if (!SV_CheckBottom(ent))
    {
        if ((int) get_qcc_flags(ent) & FL_PARTIALGROUND)
        {	// entity had floor mostly pulled out from underneath it
            // and is trying to correct
            if (relink)
                SV_LinkEdict(ent, true);
            return true;
        }
        set_qcc_origin(ent, vectorize(oldorg));
        return false;
    }

    if ((int) get_qcc_flags(ent) & FL_PARTIALGROUND)
    {
//		Con_Printf ("back on ground\n");
        set_qcc_flags(ent, (int) get_qcc_flags(ent) & ~FL_PARTIALGROUND);
    }
    set_qcc_groundentity(ent, EDICT_TO_PROG(trace.ent));

// the move is ok
    if (relink)
        SV_LinkEdict(ent, true);
    return true;
}

//============================================================================

/*
 ======================
 SV_StepDirection

 Turns to the movement direction, and walks the current distance if
 facing it.

 ======================
 */
qboolean SV_StepDirection(edict_t *ent, float yaw, float dist)
{
    vec3_t move, oldorigin;
    float delta;

    set_qcc_ideal_yaw(ent, yaw);
#if USE_PROGSDAT
	PF_changeyaw();
#else
    qcc_ChangeYaw();
#endif
    yaw = yaw * M_PI * 2 / 360;
    move[0] = cos_t(yaw) * dist;
    move[1] = sin_t(yaw) * dist;
    move[2] = 0;

    VectorCopy(VEC(get_qcc_origin(ent)), oldorigin);
    if (SV_movestep(ent, move, false))
    {
        delta = VEC(get_qcc_angles(ent))[YAW] - get_qcc_ideal_yaw(ent);
        if (delta > 45 && delta < 315)
        {		// not turned far enough, so don't take the step
            set_qcc_origin(ent, vectorize(oldorigin));
        }
        SV_LinkEdict(ent, true);
        return true;
    }
    SV_LinkEdict(ent, true);

    return false;
}

/*
 ======================
 SV_FixCheckBottom

 ======================
 */
void SV_FixCheckBottom(edict_t *ent)
{
//	Con_Printf ("SV_FixCheckBottom\n");

    set_qcc_flags(ent, (int) get_qcc_flags(ent) | FL_PARTIALGROUND);
}

/*
 ================
 SV_NewChaseDir

 ================
 */
#define	DI_NODIR	-1
void SV_NewChaseDir(edict_t *actor, edict_t *enemy, float dist)
{
    float deltax, deltay;
    float d[3];
    float tdir, olddir, turnaround;

    olddir = anglemod((int) (get_qcc_ideal_yaw(actor) / 45) * 45);
    turnaround = anglemod(olddir - 180);

    deltax = VEC(get_qcc_origin(enemy))[0] - VEC(get_qcc_origin(actor))[0];
    deltay = VEC(get_qcc_origin(enemy))[1] - VEC(get_qcc_origin(actor))[1];
    if (deltax > 10)
        d[1] = 0;
    else if (deltax < -10)
        d[1] = 180;
    else
        d[1] = DI_NODIR;
    if (deltay < -10)
        d[2] = 270;
    else if (deltay > 10)
        d[2] = 90;
    else
        d[2] = DI_NODIR;

// try direct route
    if (d[1] != DI_NODIR && d[2] != DI_NODIR)
    {
        if (d[1] == 0)
            tdir = d[2] == 90 ? 45 : 315;
        else
            tdir = d[2] == 90 ? 135 : 215;

        if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
            return;
    }

// try other directions
    if (((rand() & 3) & 1) || abs(deltay) > abs(deltax))
    {
        tdir = d[1];
        d[1] = d[2];
        d[2] = tdir;
    }

    if (d[1] != DI_NODIR && d[1] != turnaround && SV_StepDirection(actor, d[1], dist))
        return;

    if (d[2] != DI_NODIR && d[2] != turnaround && SV_StepDirection(actor, d[2], dist))
        return;

    /* there is no direct path to the player, so pick another direction */

    if (olddir != DI_NODIR && SV_StepDirection(actor, olddir, dist))
        return;

    if (rand() & 1) /*randomly determine direction of search*/
    {
        for (tdir = 0; tdir <= 315; tdir += 45)
            if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
                return;
    }
    else
    {
        for (tdir = 315; tdir >= 0; tdir -= 45)
            if (tdir != turnaround && SV_StepDirection(actor, tdir, dist))
                return;
    }

    if (turnaround != DI_NODIR && SV_StepDirection(actor, turnaround, dist))
        return;

    set_qcc_ideal_yaw(actor, olddir);		// can't move

// if a bridge was pulled out from underneath a monster, it may not have
// a valid standing position at all

    if (!SV_CheckBottom(actor))
        SV_FixCheckBottom(actor);

}

/*
 ======================
 SV_CloseEnough

 ======================
 */
qboolean SV_CloseEnough(edict_t *ent, edict_t *goal, float dist)
{

#if USE_OLD_ABS_CALLS // tbd if is faster
  int   i;
  for (i=0 ; i<3 ; i++)
	{
		if (VEC(get_qcc_absmin(goal))[i] > VEC(get_qcc_absmax(ent))[i] + dist)
			return false;
		if (VEC(get_qcc_absmax(goal))[i] < VEC(get_qcc_absmin(ent))[i] - dist)
			return false;


	}
#else
    vector absminGoal = get_qcc_absmin(goal);
    vector absmaxEnt = get_qcc_absmax(ent);
    if (absminGoal.v[0] > absmaxEnt.v[0] + dist)
        return false;
    if (absminGoal.v[1] > absmaxEnt.v[1] + dist)
        return false;
    if (absminGoal.v[2] > absmaxEnt.v[2] + dist)
        return false;

    vector absmaxGoal = get_qcc_absmax(goal);
    vector absminEnt = get_qcc_absmin(ent);
    if (absmaxGoal.v[0] < absminEnt.v[0] - dist)
        return false;
    if (absmaxGoal.v[1] < absminEnt.v[1] - dist)
        return false;
    if (absmaxGoal.v[2] < absminEnt.v[2] - dist)
        return false;

#endif

    return true;
}

/*
 ======================
 SV_MoveToGoal

 ======================
 */

void qcc_movetogoal(float dist)
{
    edict_t *ent, *goal;
    //float		dist;
    ent = PROG_TO_EDICT(progs.qcc_self);
    goal = PROG_TO_EDICT(get_qcc_goalentity(ent));
//	dist = G_FLOAT(OFS_PARM0);

    if (!((int) get_qcc_flags(ent) & (FL_ONGROUND | FL_FLY | FL_SWIM)))
    {
        // ???	G_FLOAT(OFS_RETURN) = 0;
        return;
    }

// if the next step hits the enemy, return immediately
    if (PROG_TO_EDICT(get_qcc_enemy(ent)) != sv.edicts && SV_CloseEnough(ent, goal, dist))
        return;

// bump around...
    if ((rand() & 3) == 1 || !SV_StepDirection(ent, get_qcc_ideal_yaw(ent), dist))
    {
        SV_NewChaseDir(ent, goal, dist);
    }
    return;
}

