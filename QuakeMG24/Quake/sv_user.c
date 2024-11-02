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
// sv_user.c -- server code for moving users
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
player_edict_t *sv_player;
#if USE_ORIGINAL_CVAR
extern	cvar_t	sv_friction;
cvar_t	sv_edgefriction = {"edgefriction", "2"};
extern	cvar_t	sv_stopspeed;
#endif

static vec3_t forward, right, up;

vec3_t wishdir;
float wishspeed;

// world
//float	*angles;
// float *origin;
//float	*velocity;
vec3_t player_origin;
vec3_t player_velocity;

qboolean onground;

usercmd_t cmd;
#if USE_ORIGINAL_CVAR
cvar_t	sv_idealpitchscale = {"sv_idealpitchscale","0.8"};
#endif

/*
 ===============
 SV_SetIdealPitch
 ===============
 */
#define	MAX_FORWARD	6
void SV_SetIdealPitch(void)
{
    float angleval, sinval, cosval;
    trace_t tr;
    vec3_t top, bottom;
    float z[MAX_FORWARD];
    int i, j;
    int step, dir, steps;

    if (!((int) get_qcc_flags((edict_t*) sv_player) & FL_ONGROUND))
        return;

    angleval = VEC(get_qcc_angles((edict_t *) sv_player))[YAW] * M_PI * 2 / 360;
    sinval = sin_t(angleval);
    cosval = cos_t(angleval);

    for (i = 0; i < MAX_FORWARD; i++)
    {
        // next-hack: TODO: optimize this, we should not get every time the origin separately.
        top[0] = VEC(get_qcc_origin((edict_t *) sv_player))[0] + cosval * (i + 3) * 12;
        top[1] = VEC(get_qcc_origin((edict_t *) sv_player))[1] + sinval * (i + 3) * 12;
        top[2] = VEC(get_qcc_origin((edict_t *) sv_player))[2] + VEC(get_qcc_view_ofs((edict_t *) sv_player))[2];

        bottom[0] = top[0];
        bottom[1] = top[1];
        bottom[2] = top[2] - 160;

        tr = SV_Move(top, vec3_origin, vec3_origin, bottom, 1, (edict_t*) sv_player);
        if (tr.allsolid)
            return;	// looking at a wall, leave ideal the way is was

        if (tr.fraction == 1)
            return;	// near a dropoff

        z[i] = top[2] + tr.fraction * (bottom[2] - top[2]);
    }

    dir = 0;
    steps = 0;
    for (j = 1; j < i; j++)
    {
        step = z[j] - z[j - 1];
        if (step > -ON_EPSILON && step < ON_EPSILON)
            continue;

        if (dir && (step - dir > ON_EPSILON || step - dir < -ON_EPSILON))
            return;		// mixed changes

        steps++;
        dir = step;
    }

    if (!dir)
    {
        set_qcc_idealpitch((edict_t*) sv_player, 0);
        return;
    }

    if (steps < 2)
        return;
    set_qcc_idealpitch((edict_t*) sv_player, -dir * sv_idealpitchscale);
}

/*
 ==================
 SV_UserFriction

 ==================
 */
void SV_UserFriction(void)
{
    float *vel;
    float speed, newspeed, control;
    vec3_t start, stop;
    float friction;
    trace_t trace;

    vel = player_velocity;

    speed = sqrtf_m(vel[0] * vel[0] + vel[1] * vel[1]);
    if (!speed)
        return;

// if the leading edge is over a dropoff, increase friction
    start[0] = stop[0] = player_origin[0] + vel[0] / speed * 16;
    start[1] = stop[1] = player_origin[1] + vel[1] / speed * 16;
    start[2] = player_origin[2] + VEC(get_qcc_mins((edict_t *) sv_player))[2];
    stop[2] = start[2] - 34;

    trace = SV_Move(start, vec3_origin, vec3_origin, stop, true, (edict_t*) sv_player);

    if (trace.fraction == 1.0)
        friction = sv_friction * edgefriction;
    else
        friction = sv_friction;

// apply friction
    control = speed < sv_stopspeed ? sv_stopspeed : speed;
    newspeed = speed - host_frametime * control * friction;

    if (newspeed < 0)
        newspeed = 0;
    newspeed /= speed;

    vel[0] = vel[0] * newspeed;
    vel[1] = vel[1] * newspeed;
    vel[2] = vel[2] * newspeed;
    set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));
}

/*
 ==============
 SV_Accelerate
 ==============
 */
#if USE_ORIGINAL_CVAR
cvar_t	sv_maxspeed = {"sv_maxspeed", "320", false, true};
cvar_t	sv_accelerate = {"sv_accelerate", "10"};
#endif
#if 0
void SV_Accelerate (vec3_t wishvel)
{
	int			i;
	float		addspeed, accelspeed;
	vec3_t		pushvec;

	if (wishspeed == 0)
		return;

	VectorSubtract (wishvel, velocity, pushvec);
	addspeed = VectorNormalize (pushvec);

	accelspeed = sv_accelerate*host_frametime*addspeed;
	if (accelspeed > addspeed)
		accelspeed = addspeed;

	for (i=0 ; i<3 ; i++)
		velocity[i] += accelspeed*pushvec[i];
}
#endif
void SV_Accelerate(void)
{
    int i;
    float addspeed, accelspeed, currentspeed;

    currentspeed = DotProduct(player_velocity, wishdir);
    addspeed = wishspeed - currentspeed;
    if (addspeed <= 0)
        return;
    accelspeed = sv_accelerate * host_frametime * wishspeed;
    if (accelspeed > addspeed)
        accelspeed = addspeed;

    for (i = 0; i < 3; i++)
        player_velocity[i] += accelspeed * wishdir[i];
    set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));

}

void SV_AirAccelerate(vec3_t wishveloc)
{
    int i;
    float addspeed, wishspd, accelspeed, currentspeed;

    wishspd = VectorNormalize(wishveloc);
    if (wishspd > 30)
        wishspd = 30;
    currentspeed = DotProduct(player_velocity, wishveloc);
    addspeed = wishspd - currentspeed;
    if (addspeed <= 0)
        return;
//	accelspeed = sv_accelerate * host_frametime;
    accelspeed = sv_accelerate * wishspeed * host_frametime;
    if (accelspeed > addspeed)
        accelspeed = addspeed;

    for (i = 0; i < 3; i++)
        player_velocity[i] += accelspeed * wishveloc[i];
    set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));

}

void DropPunchAngle(void)
{
    float len;
    vec3_t tmp;
    VectorCopy(VEC(get_qcc_punchangle((edict_t *) sv_player)), tmp);
    len = VectorNormalize(tmp);
    set_qcc_punchangle((edict_t*) sv_player, vectorize(tmp));
    len -= 10 * host_frametime;
    if (len < 0)

        len = 0;
    VectorScale(VEC(get_qcc_punchangle((edict_t* ) sv_player)), len, tmp);
    set_qcc_punchangle((edict_t*) sv_player, vectorize(tmp));
}

/*
 ===================
 SV_WaterMove

 ===================
 */
void SV_WaterMove(void)
{
    int i;
    vec3_t wishvel;
    float speed, newspeed, wishspeed, addspeed, accelspeed;

//
// user intentions
//
    AngleVectors(VEC(get_qcc_v_angle((edict_t* ) sv_player)), forward, right, up);

    for (i = 0; i < 3; i++)
        wishvel[i] = forward[i] * cmd.forwardmove + right[i] * cmd.sidemove;

    if (!cmd.forwardmove && !cmd.sidemove && !cmd.upmove)
        wishvel[2] -= 60;		// drift towards bottom
    else
        wishvel[2] += cmd.upmove;

    wishspeed = Length(wishvel);
    if (wishspeed > sv_maxspeed)
    {
        VectorScale(wishvel, sv_maxspeed / wishspeed, wishvel);
        wishspeed = sv_maxspeed;
    }
    wishspeed *= 0.7;

//
// water friction
//
    speed = Length(player_velocity);
    if (speed)
    {
        newspeed = speed - host_frametime * speed * sv_friction;
        if (newspeed < 0)
            newspeed = 0;
        VectorScale(player_velocity, newspeed / speed, player_velocity);
        set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));

    }
    else
        newspeed = 0;

//
// water acceleration
//
    if (!wishspeed)
        return;

    addspeed = wishspeed - newspeed;
    if (addspeed <= 0)
        return;

    VectorNormalize(wishvel);
    accelspeed = sv_accelerate * wishspeed * host_frametime;
    if (accelspeed > addspeed)
        accelspeed = addspeed;

    for (i = 0; i < 3; i++)
        player_velocity[i] += accelspeed * wishvel[i];
    set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));

}

void SV_WaterJump(void)
{
    if (sv.time > get_qcc_teleport_time((edict_t*) sv_player) || !get_qcc_waterlevel((edict_t*) sv_player))
    {
        set_qcc_flags((edict_t*) sv_player, (int) get_qcc_flags((edict_t*) sv_player) & ~FL_WATERJUMP);
        set_qcc_teleport_time((edict_t*) sv_player, 0);
    }
    set_qcc_velocity_x((edict_t*) sv_player, VEC(get_qcc_movedir((edict_t *) sv_player))[0]);
    set_qcc_velocity_y((edict_t*) sv_player, VEC(get_qcc_movedir((edict_t *) sv_player))[1]);
}

/*
 ===================
 SV_AirMove

 ===================
 */
void SV_AirMove(void)
{
    int i;
    vec3_t wishvel;
    float fmove, smove;

    AngleVectors(VEC(get_qcc_angles((edict_t* ) sv_player)), forward, right, up);

    fmove = cmd.forwardmove;
    smove = cmd.sidemove;

// hack to not let you back into teleporter
    if (sv.time < get_qcc_teleport_time((edict_t*) sv_player) && fmove < 0)
        fmove = 0;

    for (i = 0; i < 3; i++)
        wishvel[i] = forward[i] * fmove + right[i] * smove;

    if ((int) get_qcc_movetype((edict_t*) sv_player) != MOVETYPE_WALK)
        wishvel[2] = cmd.upmove;
    else
        wishvel[2] = 0;

    VectorCopy(wishvel, wishdir);
    wishspeed = VectorNormalize(wishdir);
    if (wishspeed > sv_maxspeed)
    {
        VectorScale(wishvel, sv_maxspeed / wishspeed, wishvel);
        wishspeed = sv_maxspeed;
    }

    if (get_qcc_movetype((edict_t*) sv_player) == MOVETYPE_NOCLIP)
    {	// noclip
        VectorCopy(wishvel, player_velocity);
        set_qcc_velocity((edict_t*) sv_player, vectorize(player_velocity));

    }
    else if (onground)
    {
        SV_UserFriction();
        SV_Accelerate();
    }
    else
    {	// not on ground, so little effect on velocity
        SV_AirAccelerate(wishvel);
    }
}

/*
 ===================
 SV_ClientThink

 the move fields specify an intended velocity in pix/sec
 the angle fields specify an exact angular motion in degrees
 ===================
 */
void SV_ClientThink(void)
{
    vec3_t v_angle;
    vec3_t angles;
    if (get_qcc_movetype((edict_t*) sv_player) == MOVETYPE_NONE)
        return;

    onground = 0 != ((int) get_qcc_flags((edict_t*) sv_player) & FL_ONGROUND); // next-hack: this was driving me crazy. onground is an 8-bit so this would not work without "0!=..."
    VectorCopy(VEC(get_qcc_origin((edict_t *) sv_player)), player_origin);
    VectorCopy(VEC(get_qcc_velocity((edict_t *) sv_player)), player_velocity);

    DropPunchAngle();

//
// if dead, behave differently
//
    if (get_qcc_health((edict_t*) sv_player) <= 0)
        return;

//
// angles
// show 1/3 the pitch angle and all the roll angle
    cmd = host_client->cmd;
    VectorCopy(VEC(get_qcc_angles((edict_t *) sv_player)), angles);

    VectorAdd(VEC(get_qcc_v_angle((edict_t *) sv_player)), VEC(get_qcc_punchangle((edict_t *) sv_player)), v_angle);
    angles[ROLL] = V_CalcRoll(VEC(get_qcc_angles((edict_t* ) sv_player)), VEC(get_qcc_velocity((edict_t* ) sv_player))) * 4;
    if (!get_qcc_fixangle((edict_t*) sv_player))
    {
        angles[PITCH] = -v_angle[PITCH] / 3;
        angles[YAW] = v_angle[YAW];
    }
    // nh: copy back angles
    set_qcc_angles((edict_t*) sv_player, vectorize(angles));
    //
    if ((int) get_qcc_flags((edict_t*) sv_player) & FL_WATERJUMP)
    {
        SV_WaterJump();
        return;
    }
//
// walk
//
    if ((get_qcc_waterlevel((edict_t*) sv_player) >= 2) && (get_qcc_movetype((edict_t*) sv_player) != MOVETYPE_NOCLIP))
    {
        SV_WaterMove();
        return;
    }

    SV_AirMove();
}

/*
 ===================
 SV_ReadClientMove
 ===================
 */
void SV_ReadClientMove(usercmd_t *move)
{
    int i;
    vec3_t angle;
    int bits;

// read ping time
#if 0
    host_client->ping_times[host_client->num_pings % NUM_PING_TIMES] = sv.time - MSG_ReadFloat();
    host_client->num_pings++;
#else
    MSG_ReadFloat();
#endif
// read current angles
    for (i = 0; i < 3; i++)
        angle[i] = MSG_ReadAngle();

    set_qcc_v_angle((edict_t*) host_client->edict, vectorize(angle));

// read movement
    move->forwardmove = MSG_ReadShort();
    move->sidemove = MSG_ReadShort();
    move->upmove = MSG_ReadShort();

// read buttons
    bits = MSG_ReadByte();
    set_qcc_button0((edict_t*) host_client->edict, bits & 1);
    set_qcc_button2((edict_t*) host_client->edict, (bits & 2) >> 1);

    i = MSG_ReadByte();
    if (i)
        set_qcc_impulse((edict_t*) host_client->edict, i);

#ifdef QUAKE2
// read light level
	host_client->edict->v.light_level = MSG_ReadByte ();
#endif
}

/*
 ===================
 SV_ReadClientMessage

 Returns false if the client should be killed
 ===================
 */
qboolean SV_ReadClientMessage(void)
{
    int ret;
    int cmd;
    char *s;

    char *strbuf = getTextureCacheBuffer();  //[2048];
    do
    {
        nextmsg:
        ret = NET_GetMessage(host_client->netconnection);
        if (ret == -1)
        {
            Sys_Printf("SV_ReadClientMessage: NET_GetMessage failed\n");
            return false;
        }
        if (!ret)
            return true;

        MSG_BeginReading();

        while (1)
        {
            if (!host_client->active)
                return false;	// a command caused an error

            if (msg_badread)
            {
                Sys_Printf("SV_ReadClientMessage: badread\n");
                return false;
            }
#if DEBUG_MSG_READS
    readCanFail = 1;
#endif // DEBUG_MSG_READS
            cmd = MSG_ReadChar();
#if DEBUG_MSG_READS
    readCanFail = 0;
#endif // DEBUG_MSG_READS

            switch (cmd)
            {
                case -1:
                    goto nextmsg;
                    // end of message

                default:
                    Sys_Printf("SV_ReadClientMessage: unknown command char\n");
                    return false;

                case clc_nop:
//				Sys_Printf ("clc_nop\n");
                    break;

                case clc_stringcmd:
                    s = MSG_ReadString(strbuf, 2048);
                    if (host_client->privileged)
                        ret = 2;
                    else
                        ret = 0;
                    if (Q_strncasecmp(s, "status", 6) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "god", 3) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "notarget", 8) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "fly", 3) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "name", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "noclip", 6) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "say", 3) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "say_team", 8) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "tell", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "color", 5) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "kill", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "pause", 5) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "spawn", 5) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "begin", 5) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "prespawn", 8) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "kick", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "ping", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "give", 4) == 0)
                        ret = 1;
                    else if (Q_strncasecmp(s, "ban", 3) == 0)
                        ret = 1;
                    if (ret == 2)
                        Cbuf_InsertText(s);
                    else if (ret == 1)
                        Cmd_ExecuteString(s, src_client);
                    else
                        Con_DPrintf("%s tried to %s\n", host_client->name, s);
                    break;

                case clc_disconnect:
//				Sys_Printf ("SV_ReadClientMessage: client disconnected\n");
                    return false;

                case clc_move:
                    SV_ReadClientMove(&host_client->cmd);
                    break;
            }
        }
    }
    while (ret == 1);

    return true;
}

/*
 ==================
 SV_RunClients
 ==================
 */
void SV_RunClients(void)
{
    int i;

    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
    {
        if (!host_client->active)
            continue;

        sv_player = host_client->edict;

        if (!SV_ReadClientMessage())
        {
            SV_DropClient(false);	// client misbehaved...
            continue;
        }

        if (!host_client->spawned)
        {
            // clear client movement until a new packet is received
            memset(&host_client->cmd, 0, sizeof(host_client->cmd));
            continue;
        }

// always pause in single player if in console or menus
        if (!sv.paused && (svs.maxclients > 1 || key_dest == key_game))
            SV_ClientThink();
    }
}

