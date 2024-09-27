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
// view.c -- player eye positioning
#include "quakedef.h"
#include "r_local.h"
/*

 The view is allowed to move slightly from it's true position for bobbing,
 but if it exceeds 8 pixels linear distance (spherical, not box), the list of
 entities sent from the server may not include everything in the pvs, especially
 when crossing a water boudnary.

 */
#if USE_ORIGINAL_CVAR
cvar_t		lcd_x = {"lcd_x","0"};
cvar_t		lcd_yaw = {"lcd_yaw","0"};

cvar_t	scr_ofsx = {"scr_ofsx","0", false};
cvar_t	scr_ofsy = {"scr_ofsy","0", false};
cvar_t	scr_ofsz = {"scr_ofsz","0", false};

cvar_t	cl_rollspeed = {"cl_rollspeed", "200"};
cvar_t	cl_rollangle = {"cl_rollangle", "2.0"};

cvar_t	cl_bob = {"cl_bob","0.02", false};
cvar_t	cl_bobcycle = {"cl_bobcycle","0.6", false};
cvar_t	cl_bobup = {"cl_bobup","0.5", false};

cvar_t	v_kicktime = {"v_kicktime", "0.5", false};
cvar_t	v_kickroll = {"v_kickroll", "0.6", false};
cvar_t	v_kickpitch = {"v_kickpitch", "0.6", false};

cvar_t	v_iyaw_cycle = {"v_iyaw_cycle", "2", false};
cvar_t	v_iroll_cycle = {"v_iroll_cycle", "0.5", false};
cvar_t	v_ipitch_cycle = {"v_ipitch_cycle", "1", false};
cvar_t	v_iyaw_level = {"v_iyaw_level", "0.3", false};
cvar_t	v_iroll_level = {"v_iroll_level", "0.1", false};
cvar_t	v_ipitch_level = {"v_ipitch_level", "0.3", false};

cvar_t	v_idlescale = {"v_idlescale", "0", false};

cvar_t	crosshair = {"crosshair", "0", true};
cvar_t	cl_crossx = {"cl_crossx", "0", false};
cvar_t	cl_crossy = {"cl_crossy", "0", false};

cvar_t	gl_cshiftpercent = {"gl_cshiftpercent", "100", false};
#endif
float v_dmg_time, v_dmg_roll, v_dmg_pitch;

/*
 ===============
 V_CalcRoll

 Used by view and sv_user
 ===============
 */
vec3_t forward, right, up;

float V_CalcRoll(vec3_t angles, vec3_t velocity)
{
    float sign;
    float side;
    float value;

    AngleVectors(angles, forward, right, up);
    side = DotProduct(velocity, right);
    sign = side < 0 ? -1 : 1;
    side = fabsf_m(side);

    value = cl_rollangle;
//	if (_g->cl.inwater)
//		value *= 6;

    if (side < cl_rollspeed)
        side = side * value / cl_rollspeed;
    else
        side = value;

    return side * sign;

}

/*
 ===============
 V_CalcBob

 ===============
 */
float V_CalcBob(void)
{
    float bob;
    float cycle;

    cycle = _g->cl.time - (int) (_g->cl.time / cl_bobcycle) * cl_bobcycle;
    cycle /= cl_bobcycle;
    if (cycle < cl_bobup)
        cycle = M_PI * cycle / cl_bobup;
    else
        cycle = M_PI + M_PI * (cycle - cl_bobup) / (1.0 - cl_bobup);

// bob is proportional to velocity in the xy plane
// (don't count Z, or jumping messes it up)

    bob = sqrtf_m(_g->cl.velocity[0] * _g->cl.velocity[0] + _g->cl.velocity[1] * _g->cl.velocity[1]) * cl_bob;
//Con_Printf ("speed: %5.1f\n", Length(_g->cl.velocity));
    bob = bob * 0.3 + bob * 0.7 * sin_t(cycle);
    if (bob > 4)
        bob = 4;
    else if (bob < -7)
        bob = -7;
    return bob;

}

//=============================================================================

#if USE_ORIGINAL_CVAR
cvar_t	v_centermove = {"v_centermove", "0.15", false};
cvar_t	v_centerspeed = {"v_centerspeed","500"};
#endif

void V_StartPitchDrift(void)
{
#if 1
    if (_g->cl.laststop == _g->cl.time)
    {
        return;		// something else is keeping it from drifting
    }
#endif
    if (_g->cl.nodrift || !_g->cl.pitchvel)
    {
        _g->cl.pitchvel = v_centerspeed;
        _g->cl.nodrift = false;
        _g->cl.driftmove = 0;
    }
}

void V_StopPitchDrift(void)
{
    _g->cl.laststop = _g->cl.time;
    _g->cl.nodrift = true;
    _g->cl.pitchvel = 0;
}

/*
 ===============
 V_DriftPitch

 Moves the client pitch angle towards _g->cl.idealpitch sent by the server.

 If the user is adjusting pitch manually, either with lookup/lookdown,
 mlook and mouse, or klook and keyboard, pitch drifting is constantly stopped.

 Drifting is enabled when the center view key is hit, mlook is released and
 lookspring is non 0, or when
 ===============
 */
void V_DriftPitch(void)
{
    float delta, move;

    if (noclip_anglehack || !_g->cl.onground || _g->cls.demoplayback)
    {
        _g->cl.driftmove = 0;
        _g->cl.pitchvel = 0;
        return;
    }

// don't count small mouse motion
    if (_g->cl.nodrift)
    {
        if (fabsf_m(_g->cl.cmd.forwardmove) < cl_forwardspeed)
            _g->cl.driftmove = 0;
        else
            _g->cl.driftmove += host_frametime;

        if (_g->cl.driftmove > v_centermove)
        {
            V_StartPitchDrift();
        }
        return;
    }

    delta = _g->cl.idealpitch - _g->cl.viewangles[PITCH];

    if (!delta)
    {
        _g->cl.pitchvel = 0;
        return;
    }

    move = host_frametime * _g->cl.pitchvel;
    _g->cl.pitchvel += host_frametime * v_centerspeed;

//Con_Printf ("move: %f (%f)\n", move, host_frametime);

    if (delta > 0)
    {
        if (move > delta)
        {
            _g->cl.pitchvel = 0;
            move = delta;
        }
        _g->cl.viewangles[PITCH] += move;
    }
    else if (delta < 0)
    {
        if (move > -delta)
        {
            _g->cl.pitchvel = 0;
            move = -delta;
        }
        _g->cl.viewangles[PITCH] -= move;
    }
}

/*
 ==============================================================================

 PALETTE FLASHES

 ==============================================================================
 */

cshift_t cshift_empty =
{
{ 130, 80, 50
}, 0
};
cshift_t cshift_water =
{
{ 130, 80, 50
}, 128
};
cshift_t cshift_slime =
{
{ 0, 25, 5
}, 150
};
cshift_t cshift_lava =
{
{ 255, 80, 0
}, 150
};
#if USE_ORIGINAL_CVAR
cvar_t		v_gamma = {"gamma", "1", true};
#endif
AUX_SECTION byte gammatable[256];	// palette is sent through this

#ifdef	GLQUAKE
byte		ramps[3][256];
float		v_blend[4];		// rgba 0.0 - 1.0
#endif	// GLQUAKE

void BuildGammaTable(float g)
{
    int i, inf;

    if (g == 1.0f)
    {
        for (i = 0; i < 256; i++)
            gammatable[i] = i;
        return;
    }

    for (i = 0; i < 256; i++)
    {
        inf = 255 * powf((i + 0.5f) / 255.5f, g) + 0.5f;
        if (inf < 0)
            inf = 0;
        if (inf > 255)
            inf = 255;
        gammatable[i] = inf;
    }
}

/*
 =================
 V_CheckGamma
 =================
 */
qboolean V_CheckGamma(void)
{
    static float oldgammavalue;

    if (v_gamma == oldgammavalue)
        return false;
    if (v_gamma > MAX_GAMMA)
        v_gamma = MAX_GAMMA;
    if (v_gamma < MIN_GAMMA)
        v_gamma = MIN_GAMMA;
    oldgammavalue = v_gamma;

    BuildGammaTable(v_gamma);
    vid.recalc_refdef = 1;				// force a surface cache flush

    return true;
}

/*
 ===============
 V_ParseDamage
 ===============
 */
void V_ParseDamage(void)
{
    int armor, blood;
    vec3_t from;
    int i;
    vec3_t forward, right, up;
    entity_t *ent;
    float side;
    float count;

    armor = MSG_ReadByte();
    blood = MSG_ReadByte();
    for (i = 0; i < 3; i++)
        from[i] = MSG_ReadCoord();

    count = blood * 0.5 + armor * 0.5;
    if (count < 10)
        count = 10;

    _g->cl.faceanimtime = _g->cl.time + 0.2;		// but sbar face into pain frame

    _g->cl.cshifts[CSHIFT_DAMAGE].percent += 3 * count;
    if (_g->cl.cshifts[CSHIFT_DAMAGE].percent < 0)
        _g->cl.cshifts[CSHIFT_DAMAGE].percent = 0;
    if (_g->cl.cshifts[CSHIFT_DAMAGE].percent > 150)
        _g->cl.cshifts[CSHIFT_DAMAGE].percent = 150;

    if (armor > blood)
    {
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[0] = 200;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[1] = 100;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[2] = 100;
    }
    else if (armor)
    {
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[0] = 220;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[1] = 50;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[2] = 50;
    }
    else
    {
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[0] = 255;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[1] = 0;
        _g->cl.cshifts[CSHIFT_DAMAGE].destcolor[2] = 0;
    }

//
// calculate view angle kicks
//
    ent = &cl_entities[_g->cl.viewentity];
#if !ENTITY_HAS_SHORT_COORDS
	VectorSubtract (from, ent->origin, from);
#else
    VectorSubtract(from, VEC(getEntityOrigins(ent)), from);
#endif
    VectorNormalize(from);

#if !ENTITY_HAS_SHORT_COORDS
	AngleVectors (ent->angles, forward, right, up);
#else
    AngleVectors(VEC(getEntityAngles(ent)), forward, right, up);
#endif
    side = DotProduct(from, right);
    v_dmg_roll = count * side * v_kickroll;

    side = DotProduct(from, forward);
    v_dmg_pitch = count * side * v_kickpitch;

    v_dmg_time = v_kicktime;
}

/*
 ==================
 V_cshift_f
 ==================
 */
void V_cshift_f(void)
{
    cshift_empty.destcolor[0] = atoi(Cmd_Argv(1));
    cshift_empty.destcolor[1] = atoi(Cmd_Argv(2));
    cshift_empty.destcolor[2] = atoi(Cmd_Argv(3));

    cshift_empty.percent = atoi(Cmd_Argv(4));
}

/*
 ==================
 V_BonusFlash_f

 When you run over an item, the server sends this command
 ==================
 */
void V_BonusFlash_f(void)
{
    _g->cl.cshifts[CSHIFT_BONUS].destcolor[0] = 215;
    _g->cl.cshifts[CSHIFT_BONUS].destcolor[1] = 186;
    _g->cl.cshifts[CSHIFT_BONUS].destcolor[2] = 69;
    _g->cl.cshifts[CSHIFT_BONUS].percent = 50;
}

/*
 =============
 V_SetContentsColor

 Underwater, lava, etc each has a color shift
 =============
 */
void V_SetContentsColor(int contents)
{
    switch (contents)
    {
        case CONTENTS_EMPTY:
        case CONTENTS_SOLID:
            _g->cl.cshifts[CSHIFT_CONTENTS] = cshift_empty;
            break;
        case CONTENTS_LAVA:
            _g->cl.cshifts[CSHIFT_CONTENTS] = cshift_lava;
            break;
        case CONTENTS_SLIME:
            _g->cl.cshifts[CSHIFT_CONTENTS] = cshift_slime;
            break;
        default:
            _g->cl.cshifts[CSHIFT_CONTENTS] = cshift_water;
    }
}

/*
 =============
 V_CalcPowerupCshift
 =============
 */
void V_CalcPowerupCshift(void)
{
    if (_g->cl.items & IT_QUAD)
    {
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[0] = 0;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[1] = 0;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[2] = 255;
        _g->cl.cshifts[CSHIFT_POWERUP].percent = 30;
    }
    else if (_g->cl.items & IT_SUIT)
    {
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[0] = 0;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[1] = 255;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[2] = 0;
        _g->cl.cshifts[CSHIFT_POWERUP].percent = 20;
    }
    else if (_g->cl.items & IT_INVISIBILITY)
    {
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[0] = 100;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[1] = 100;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[2] = 100;
        _g->cl.cshifts[CSHIFT_POWERUP].percent = 100;
    }
    else if (_g->cl.items & IT_INVULNERABILITY)
    {
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[0] = 255;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[1] = 255;
        _g->cl.cshifts[CSHIFT_POWERUP].destcolor[2] = 0;
        _g->cl.cshifts[CSHIFT_POWERUP].percent = 30;
    }
    else
        _g->cl.cshifts[CSHIFT_POWERUP].percent = 0;
}

/*
 =============
 V_CalcBlend
 =============
 */
#ifdef	GLQUAKE
void V_CalcBlend (void)
{
	float	r, g, b, a, a2;
	int		j;

	r = 0;
	g = 0;
	b = 0;
	a = 0;

	for (j=0 ; j<NUM_CSHIFTS ; j++)
	{
		if (!gl_cshiftpercent)
			continue;

		a2 = ((_g->cl.cshifts[j].percent * gl_cshiftpercent) / 100.0) / 255.0;

//		a2 = _g->cl.cshifts[j].percent/255.0;
		if (!a2)
			continue;
		a = a + a2*(1-a);
//Con_Printf ("j:%i a:%f\n", j, a);
		a2 = a2/a;
		r = r*(1-a2) + _g->cl.cshifts[j].destcolor[0]*a2;
		g = g*(1-a2) + _g->cl.cshifts[j].destcolor[1]*a2;
		b = b*(1-a2) + _g->cl.cshifts[j].destcolor[2]*a2;
	}

	v_blend[0] = r/255.0;
	v_blend[1] = g/255.0;
	v_blend[2] = b/255.0;
	v_blend[3] = a;
	if (v_blend[3] > 1)
		v_blend[3] = 1;
	if (v_blend[3] < 0)
		v_blend[3] = 0;
}
#endif

/*
 =============
 V_UpdatePalette
 =============
 */
#ifdef	GLQUAKE
void V_UpdatePalette (void)
{
	int		i, j;
	qboolean	new;
	byte	*basepal, *newpal;
	byte	pal[768];
	float	r,g,b,a;
	int		ir, ig, ib;
	qboolean force;

	V_CalcPowerupCshift ();

	new = false;

	for (i=0 ; i<NUM_CSHIFTS ; i++)
	{
		if (_g->cl.cshifts[i].percent != _g->cl.prev_cshifts[i].percent)
		{
			new = true;
			_g->cl.prev_cshifts[i].percent = _g->cl.cshifts[i].percent;
		}
		for (j=0 ; j<3 ; j++)
			if (_g->cl.cshifts[i].destcolor[j] != _g->cl.prev_cshifts[i].destcolor[j])
			{
				new = true;
				_g->cl.prev_cshifts[i].destcolor[j] = _g->cl.cshifts[i].destcolor[j];
			}
	}

// drop the damage value
	_g->cl.cshifts[CSHIFT_DAMAGE].percent -= host_frametime*150;
	if (_g->cl.cshifts[CSHIFT_DAMAGE].percent <= 0)
		_g->cl.cshifts[CSHIFT_DAMAGE].percent = 0;

// drop the bonus value
	_g->cl.cshifts[CSHIFT_BONUS].percent -= host_frametime*100;
	if (_g->cl.cshifts[CSHIFT_BONUS].percent <= 0)
		_g->cl.cshifts[CSHIFT_BONUS].percent = 0;

	force = V_CheckGamma ();
	if (!new && !force)
		return;

	V_CalcBlend ();

	a = v_blend[3];
	r = 255*v_blend[0]*a;
	g = 255*v_blend[1]*a;
	b = 255*v_blend[2]*a;

	a = 1-a;
	for (i=0 ; i<256 ; i++)
	{
		ir = i*a + r;
		ig = i*a + g;
		ib = i*a + b;
		if (ir > 255)
			ir = 255;
		if (ig > 255)
			ig = 255;
		if (ib > 255)
			ib = 255;

		ramps[0][i] = gammatable[ir];
		ramps[1][i] = gammatable[ig];
		ramps[2][i] = gammatable[ib];
	}

	basepal = host_basepal;
	newpal = pal;

	for (i=0 ; i<256 ; i++)
	{
		ir = basepal[0];
		ig = basepal[1];
		ib = basepal[2];
		basepal += 3;

		newpal[0] = ramps[0][ir];
		newpal[1] = ramps[1][ig];
		newpal[2] = ramps[2][ib];
		newpal += 3;
	}

	VID_ShiftPalette (pal);
}
#else	// !GLQUAKE
void V_UpdatePalette(void)
{
    int i, j;
    qboolean new;
    byte *basepal, *newpal;
    byte pal[768];
    int r, g, b;
    qboolean force;

    V_CalcPowerupCshift();

    new = false;

    for (i = 0; i < NUM_CSHIFTS; i++)
    {
        if (_g->cl.cshifts[i].percent != _g->cl.prev_cshifts[i].percent)
        {
            new = true;
            _g->cl.prev_cshifts[i].percent = _g->cl.cshifts[i].percent;
        }
        for (j = 0; j < 3; j++)
            if (_g->cl.cshifts[i].destcolor[j] != _g->cl.prev_cshifts[i].destcolor[j])
            {
                new = true;
                _g->cl.prev_cshifts[i].destcolor[j] = _g->cl.cshifts[i].destcolor[j];
            }
    }

// drop the damage value
    _g->cl.cshifts[CSHIFT_DAMAGE].percent -= host_frametime * 150;
    if (_g->cl.cshifts[CSHIFT_DAMAGE].percent <= 0)
        _g->cl.cshifts[CSHIFT_DAMAGE].percent = 0;

// drop the bonus value
    _g->cl.cshifts[CSHIFT_BONUS].percent -= host_frametime * 100;
    if (_g->cl.cshifts[CSHIFT_BONUS].percent <= 0)
        _g->cl.cshifts[CSHIFT_BONUS].percent = 0;

    force = V_CheckGamma();
    if (!new && !force)
        return;
//
    uint8_t stackPalette[256 * 3];
    basepal = extMemGetDataFromAddress(stackPalette, host_basepal, sizeof(stackPalette));
    newpal = pal;

    for (i = 0; i < 256; i++)
    {
        r = basepal[0];
        g = basepal[1];
        b = basepal[2];
        basepal += 3;

        for (j = 0; j < NUM_CSHIFTS; j++)
        {
            r += (_g->cl.cshifts[j].percent * (_g->cl.cshifts[j].destcolor[0] - r)) >> 8;
            g += (_g->cl.cshifts[j].percent * (_g->cl.cshifts[j].destcolor[1] - g)) >> 8;
            b += (_g->cl.cshifts[j].percent * (_g->cl.cshifts[j].destcolor[2] - b)) >> 8;
        }

        newpal[0] = gammatable[r];
        newpal[1] = gammatable[g];
        newpal[2] = gammatable[b];
        newpal += 3;
    }

    VID_ShiftPalette(pal);
    //
}
#endif	// !GLQUAKE

/*
 ==============================================================================

 VIEW RENDERING

 ==============================================================================
 */

float angledelta(float a)
{
    a = anglemod(a);
    if (a > 180)
        a -= 360;
    return a;
}

/*
 ==================
 CalcGunAngle
 ==================
 */
void CalcGunAngle(void)
{
    float yaw, pitch, move;
    static float oldyaw = 0;
    static float oldpitch = 0;

    yaw = _g->r_refdef.viewangles[YAW];
    pitch = -_g->r_refdef.viewangles[PITCH];

    yaw = angledelta(yaw - _g->r_refdef.viewangles[YAW]) * 0.4;
    if (yaw > 10)
        yaw = 10;
    if (yaw < -10)
        yaw = -10;
    pitch = angledelta(-pitch - _g->r_refdef.viewangles[PITCH]) * 0.4;
    if (pitch > 10)
        pitch = 10;
    if (pitch < -10)
        pitch = -10;
    move = host_frametime * 20;
    if (yaw > oldyaw)
    {
        if (oldyaw + move < yaw)
            yaw = oldyaw + move;
    }
    else
    {
        if (oldyaw - move > yaw)
            yaw = oldyaw - move;
    }

    if (pitch > oldpitch)
    {
        if (oldpitch + move < pitch)
            pitch = oldpitch + move;
    }
    else
    {
        if (oldpitch - move > pitch)
            pitch = oldpitch - move;
    }

    oldyaw = yaw;
    oldpitch = pitch;
#if !ENTITY_HAS_SHORT_COORDS
	_g->cl.viewent.angles[YAW] = _g->r_refdef.viewangles[YAW] + yaw;
	_g->cl.viewent.angles[PITCH] = - (_g->r_refdef.viewangles[PITCH] + pitch);

	_g->cl.viewent.angles[ROLL] -= v_idlescale * sin_t(_g->cl.time*v_iroll_cycle) * v_iroll_level;
	_g->cl.viewent.angles[PITCH] -= v_idlescale * sin_t(_g->cl.time*v_ipitch_cycle) * v_ipitch_level;
	_g->cl.viewent.angles[YAW] -= v_idlescale * sin_t(_g->cl.time*v_iyaw_cycle) * v_iyaw_level;
#else
    ((temp_entity_t*) _g->cl.viewent.data)->angles_s[YAW] = toShortAngle(_g->r_refdef.viewangles[YAW] + yaw);
    ((temp_entity_t*) _g->cl.viewent.data)->angles_s[PITCH] = -toShortAngle(_g->r_refdef.viewangles[PITCH] + pitch);

    ((temp_entity_t*) _g->cl.viewent.data)->angles_s[ROLL] -= toShortAngle(v_idlescale * sin_t(_g->cl.time * v_iroll_cycle) * v_iroll_level);
    ((temp_entity_t*) _g->cl.viewent.data)->angles_s[PITCH] -= toShortAngle(v_idlescale * sin_t(_g->cl.time * v_ipitch_cycle) * v_ipitch_level);
    ((temp_entity_t*) _g->cl.viewent.data)->angles_s[YAW] -= toShortAngle(v_idlescale * sin_t(_g->cl.time * v_iyaw_cycle) * v_iyaw_level);
#endif
}

/*
 ==============
 V_BoundOffsets
 ==============
 */
void V_BoundOffsets(void)
{
    entity_t *ent;

    ent = &cl_entities[_g->cl.viewentity];

// absolutely bound refresh reletive to entity clipping hull
// so the view can never be inside a solid wall
#if !ENTITY_HAS_SHORT_COORDS
	if (_g->r_refdef.vieworg[0] < ent->origin[0] - 14)
		_g->r_refdef.vieworg[0] = ent->origin[0] - 14;
	else if (_g->r_refdef.vieworg[0] > ent->origin[0] + 14)
		_g->r_refdef.vieworg[0] = ent->origin[0] + 14;
	if (_g->r_refdef.vieworg[1] < ent->origin[1] - 14)
		_g->r_refdef.vieworg[1] = ent->origin[1] - 14;
	else if (_g->r_refdef.vieworg[1] > ent->origin[1] + 14)
		_g->r_refdef.vieworg[1] = ent->origin[1] + 14;
	if (_g->r_refdef.vieworg[2] < ent->origin[2] - 22)
		_g->r_refdef.vieworg[2] = ent->origin[2] - 22;
	else if (_g->r_refdef.vieworg[2] > ent->origin[2] + 30)
		_g->r_refdef.vieworg[2] = ent->origin[2] + 30;
#else
    if (_g->r_refdef.vieworg[0] < getEntityOrigin(ent, 0) - 14)
        _g->r_refdef.vieworg[0] = getEntityOrigin(ent, 0) - 14;
    else if (_g->r_refdef.vieworg[0] > getEntityOrigin(ent, 0) + 14)
        _g->r_refdef.vieworg[0] = getEntityOrigin(ent, 0) + 14;
    if (_g->r_refdef.vieworg[1] < getEntityOrigin(ent, 1) - 14)
        _g->r_refdef.vieworg[1] = getEntityOrigin(ent, 1) - 14;
    else if (_g->r_refdef.vieworg[1] > getEntityOrigin(ent, 1) + 14)
        _g->r_refdef.vieworg[1] = getEntityOrigin(ent, 1) + 14;
    if (_g->r_refdef.vieworg[2] < getEntityOrigin(ent, 2) - 22)
        _g->r_refdef.vieworg[2] = getEntityOrigin(ent, 2) - 22;
    else if (_g->r_refdef.vieworg[2] > getEntityOrigin(ent, 2) + 30)
        _g->r_refdef.vieworg[2] = getEntityOrigin(ent, 2) + 30;

#endif
}

/*
 ==============
 V_AddIdle

 Idle swaying
 ==============
 */
void V_AddIdle(void)
{
    _g->r_refdef.viewangles[ROLL] += v_idlescale * sin_t(_g->cl.time * v_iroll_cycle) * v_iroll_level;
    _g->r_refdef.viewangles[PITCH] += v_idlescale * sin_t(_g->cl.time * v_ipitch_cycle) * v_ipitch_level;
    _g->r_refdef.viewangles[YAW] += v_idlescale * sin_t(_g->cl.time * v_iyaw_cycle) * v_iyaw_level;
}

/*
 ==============
 V_CalcViewRoll

 Roll is induced by movement and damage
 ==============
 */
void V_CalcViewRoll(void)
{
    float side;
#if !ENTITY_HAS_SHORT_COORDS
	side = V_CalcRoll (cl_entities[_g->cl.viewentity].angles, _g->cl.velocity);
#else
    side = V_CalcRoll(VEC(getEntityAngles(&cl_entities[_g->cl.viewentity])), _g->cl.velocity);
#endif
    _g->r_refdef.viewangles[ROLL] += side;

    if (v_dmg_time > 0)
    {
        _g->r_refdef.viewangles[ROLL] += v_dmg_time / v_kicktime * v_dmg_roll;
        _g->r_refdef.viewangles[PITCH] += v_dmg_time / v_kicktime * v_dmg_pitch;
        v_dmg_time -= host_frametime;
    }

    if (_g->cl.stats[STAT_HEALTH] <= 0)
    {
        _g->r_refdef.viewangles[ROLL] = 80;	// dead view angle
        return;
    }

}

/*
 ==================
 V_CalcIntermissionRefdef

 ==================
 */
void V_CalcIntermissionRefdef(void)
{
    entity_t *ent, *view;
    float old;

// ent is the player model (visible when out of body)
    ent = &cl_entities[_g->cl.viewentity];
// view is the weapon model (only visible from inside body)
    view = &_g->cl.viewent;
#if !ENTITY_HAS_SHORT_COORDS
	VectorCopy (ent->origin, _g->r_refdef.vieworg);
	VectorCopy (ent->angles, _g->r_refdef.viewangles);
#else
    VectorCopy(VEC(getEntityOrigins(ent)), _g->r_refdef.vieworg);
    VectorCopy(VEC(getEntityAngles(ent)), _g->r_refdef.viewangles);
#endif
    setEntityModel(view, NULL);

// allways idle in intermission
    old = v_idlescale;
    v_idlescale = 1;
    V_AddIdle();
    v_idlescale = old;
}

/*
 ==================
 V_CalcRefdef

 ==================
 */
#if DIRECT_SINGLE_PLAYER
temp_entity_t viewEnt;
#endif
void V_CalcRefdef(void)
{
    entity_t *ent, *view;
    int i;
    vec3_t forward, right, up;
    vec3_t angles;
    float bob;
    static float oldz = 0;

    V_DriftPitch();

// ent is the player model (visible when out of body)
    ent = &cl_entities[_g->cl.viewentity];
#if DIRECT_SINGLE_PLAYER
    if (sv.active)
    {
        edict_t *edict = (edict_t*) ent->data;
        // copy all the data to the viewEntity
        ent->data = &viewEnt;
        ent->entityType = TYPE_TEMP_ENTITY;
        vect_t origin = get_qcc_origin(edict);
        setEntityOrigin(ent, 0, origin.x);
        setEntityOrigin(ent, 1, origin.y);
        setEntityOrigin(ent, 2, origin.z);
        // angles
        vect_t edict_angles = get_qcc_angles(edict);
        setEntityAngle(ent, 0, edict_angles.x);
        setEntityAngle(ent, 1, edict_angles.y);
        setEntityAngle(ent, 2, edict_angles.z);
        //
        setEntityFrame(ent, get_qcc_frame(edict));
        //
        setEntityEffects(ent, get_qcc_effects(edict));
        //
        setEntitySkinnum(ent, get_qcc_skin(edict));
        //
        setEntityModel(ent, sv.models[(int) get_qcc_modelindex(edict)]);
    }
#endif
// view is the weapon model (only visible from inside body)
    view = &_g->cl.viewent;

// transform the view offset by the model's matrix to get the offset from
// model origin for the view
#if !ENTITY_HAS_SHORT_COORDS
	ent->angles[YAW] = _g->cl.viewangles[YAW];	// the model should face
										// the view dir
	ent->angles[PITCH] = -_g->cl.viewangles[PITCH];	// the model should face
										// the view dir
#else
    //
    setEntityAngle(ent, YAW, _g->cl.viewangles[YAW]);	// the model should face the view dir
    setEntityAngle(ent, PITCH, -_g->cl.viewangles[PITCH]);	// the model should face the view dir

#endif
    bob = V_CalcBob();

// refresh position
#if !ENTITY_HAS_SHORT_COORDS
	VectorCopy (ent->origin, _g->r_refdef.vieworg);
#else
    VectorCopy(VEC(getEntityOrigins(ent)), _g->r_refdef.vieworg);
#endif

    _g->r_refdef.vieworg[2] += _g->cl.viewheight + bob;

// never let it sit exactly on a node line, because a water plane can
// disappear when viewed with the eye exactly on it.
// the server protocol only specifies to 1/16 pixel, so add 1/32 in each axis
    _g->r_refdef.vieworg[0] += 1.0 / 32;
    _g->r_refdef.vieworg[1] += 1.0 / 32;
    _g->r_refdef.vieworg[2] += 1.0 / 32;

    VectorCopy(_g->cl.viewangles, _g->r_refdef.viewangles);
    V_CalcViewRoll();
    V_AddIdle();

// offsets
#if !ENTITY_HAS_SHORT_COORDS
	angles[PITCH] = -ent->angles[PITCH];	// because entity pitches are
											//  actually backward
	angles[YAW] = ent->angles[YAW];
	angles[ROLL] = ent->angles[ROLL];
#else
    angles[PITCH] = -getEntityAngle(ent, PITCH);	// because entity pitches are
    //  actually backward
    angles[YAW] = getEntityAngle(ent, YAW);
    angles[ROLL] = getEntityAngle(ent, ROLL);

#endif
    AngleVectors(angles, forward, right, up);

    for (i = 0; i < 3; i++)
        _g->r_refdef.vieworg[i] += scr_ofsx * forward[i] + scr_ofsy * right[i] + scr_ofsz * up[i];

    V_BoundOffsets();

// set up gun position
#if !ENTITY_HAS_SHORT_COORDS
	VectorCopy (_g->cl.viewangles, view->angles);
#else
    setEntityAngle(view, 0, _g->cl.viewangles[0]);
    setEntityAngle(view, 1, _g->cl.viewangles[1]);
    setEntityAngle(view, 2, _g->cl.viewangles[2]);
#endif
    CalcGunAngle();
#if !ENTITY_HAS_SHORT_COORDS
	VectorCopy (ent->origin, view->origin);
	view->origin[2] += _g->cl.viewheight;
#else
    for (int i = 0; i < 3; i++)
    {
        setEntityOrigin(view, i, getEntityOrigin(ent, i));
    }
    ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(_g->cl.viewheight);
#endif
    for (i = 0; i < 3; i++)
    {
#if !ENTITY_HAS_SHORT_COORDS
		view->origin[i] += forward[i]*bob*0.4;
#else
        ((temp_entity_t*) view->data)->origin_s[i] += toShortCoord(forward[i] * bob * 0.4);
#endif
//		view->origin[i] += right[i]*bob*0.4;
//		view->origin[i] += up[i]*bob*0.8;
    }
#if !ENTITY_HAS_SHORT_COORDS
	view->origin[2] += bob;
#else
    ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(bob);
#endif
// fudge position around to keep amount of weapon visible
// roughly equal with different FOV

#if 0
	if (_g->cl.model_precache[_g->cl.stats[STAT_WEAPON]] && strcmp (_g->cl.model_precache[_g->cl.stats[STAT_WEAPON]]->name,  "progs/v_shot2.mdl"))
#endif
#if !ENTITY_HAS_SHORT_COORDS
	if (scr_viewsize == 110)
		view->origin[2] += 1;
	else if (scr_viewsize == 100)
		view->origin[2] += 2;
	else if (scr_viewsize == 90)
		view->origin[2] += 1;
	else if (scr_viewsize == 80)
		view->origin[2] += 0.5;
#else
    if (viewsize == 110)
        ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(1);
    else if (viewsize == 100)
        ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(2);
    else if (viewsize == 90)
        ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(1);
    else if (viewsize == 80)
        ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(0.5);

#endif
    setEntityModel(view, _g->cl.model_precache[_g->cl.stats[STAT_WEAPON]]);
    setEntityFrame(view, _g->cl.stats[STAT_WEAPONFRAME]);
#if HAS_MULTIPLAYER
	view->colormap = vid.colormap;
#endif
// set up the refresh position
    VectorAdd(_g->r_refdef.viewangles, _g->cl.punchangle, _g->r_refdef.viewangles);

// smooth out stair step ups
#if !ENTITY_HAS_SHORT_COORDS
if (_g->cl.onground && ent->origin[2] - oldz > 0)
#else
    if (_g->cl.onground && getEntityOrigin(ent, 2) - oldz > 0)
#endif

    {
        float steptime;

        steptime = _g->cl.time - _g->cl.oldtime;
        if (steptime < 0)
//FIXME		I_Error ("steptime < 0");
            steptime = 0;

        oldz += steptime * 80;
#if !ENTITY_HAS_SHORT_COORDS
	if (oldz > ent->origin[2])
		oldz = ent->origin[2];
	if (ent->origin[2] - oldz > 12)
		oldz = ent->origin[2] - 12;
	_g->r_refdef.vieworg[2] += oldz - ent->origin[2];
	view->origin[2] += oldz - ent->origin[2];
#else
        if (oldz > getEntityOrigin(ent, 2))
            oldz = getEntityOrigin(ent, 2);
        if (getEntityOrigin(ent, 2) - oldz > 12)
            oldz = getEntityOrigin(ent, 2) - 12;
        _g->r_refdef.vieworg[2] += oldz - getEntityOrigin(ent, 2);
        ((temp_entity_t*) view->data)->origin_s[2] += toShortCoord(oldz - getEntityOrigin(ent, 2));

#endif
    }
    else
#if !ENTITY_HAS_SHORT_COORDS
	oldz = ent->origin[2];
#else
        oldz = getEntityOrigin(ent, 2);
#endif
    if (chase_active)
        Chase_Update();
}

/*
 ==================
 V_RenderView

 The player's clipping box goes from (-16 -16 -24) to (16 16 32) from
 the entity origin, so any view position inside that will be valid
 ==================
 */
extern vrect_t scr_vrect;

void V_RenderView(void)
{
    if (con_forcedup)
        return;

// don't allow cheats in multiplayer
    /*	if (_g->cl.maxclients > 1)
     {
     Cvar_Set ("scr_ofsx", "0");
     Cvar_Set ("scr_ofsy", "0");
     Cvar_Set ("scr_ofsz", "0");
     }
     */
    if (_g->cl.intermission)
    {	// intermission / finale rendering
        V_CalcIntermissionRefdef();
    }
    else
    {
        if (!_g->cl.paused /* && (sv.maxclients > 1 || key_dest == key_game) */)
            V_CalcRefdef();
    }
#if !NODE_HAS_CHILDREN_POINTERS
    _g->currententity = &cl_entities[0];
#endif
    _g->d_pzbuffer = d_zbuffer;
    R_PushDlights();

#if 0
	if (lcd_x)
	{
		//
		// render two interleaved views
		//
		int		i;

		vid.rowbytes <<= 1;
		vid.aspect *= 0.5;

		_g->r_refdef.viewangles[YAW] -= lcd_yaw;
		for (i=0 ; i<3 ; i++)
			_g->r_refdef.vieworg[i] -= right[i]*lcd_x;
		R_RenderView ();

		vid.buffer += vid.rowbytes>>1;

		R_PushDlights ();

		_g->r_refdef.viewangles[YAW] += lcd_yaw*2;
		for (i=0 ; i<3 ; i++)
			_g->r_refdef.vieworg[i] += 2*right[i]*lcd_x;
		R_RenderView ();

		vid.buffer -= vid.rowbytes>>1;

		_g->r_refdef.vrect.height <<= 1;

		vid.rowbytes >>= 1;
		vid.aspect *= 2;
	}
	else
	{
		R_RenderView ();
	}
#else
    R_RenderView();
#endif

#ifndef GLQUAKE
    if (crosshair)
        Draw_Character(scr_vrect.x + scr_vrect.width / 2 + cl_crossx, scr_vrect.y + scr_vrect.height / 2 + cl_crossy, '+');
#endif

}

//============================================================================

/*
 =============
 V_Init
 =============
 */
void V_Init(void)
{
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&lcd_x);
	Cvar_RegisterVariable (&lcd_yaw);

	Cvar_RegisterVariable (&v_centermove);
	Cvar_RegisterVariable (&v_centerspeed);

	Cvar_RegisterVariable (&v_iyaw_cycle);
	Cvar_RegisterVariable (&v_iroll_cycle);
	Cvar_RegisterVariable (&v_ipitch_cycle);
	Cvar_RegisterVariable (&v_iyaw_level);
	Cvar_RegisterVariable (&v_iroll_level);
	Cvar_RegisterVariable (&v_ipitch_level);

	Cvar_RegisterVariable (&v_idlescale);
	Cvar_RegisterVariable (&crosshair);
	Cvar_RegisterVariable (&cl_crossx);
	Cvar_RegisterVariable (&cl_crossy);
	Cvar_RegisterVariable (&gl_cshiftpercent);

	Cvar_RegisterVariable (&scr_ofsx);
	Cvar_RegisterVariable (&scr_ofsy);
	Cvar_RegisterVariable (&scr_ofsz);
	Cvar_RegisterVariable (&cl_rollspeed);
	Cvar_RegisterVariable (&cl_rollangle);
	Cvar_RegisterVariable (&cl_bob);
	Cvar_RegisterVariable (&cl_bobcycle);
	Cvar_RegisterVariable (&cl_bobup);

	Cvar_RegisterVariable (&v_kicktime);
	Cvar_RegisterVariable (&v_kickroll);
	Cvar_RegisterVariable (&v_kickpitch);
	Cvar_RegisterVariable (&v_gamma);
#endif
    BuildGammaTable(1.0);	// no gamma yet
}

