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
// chase.c -- chase camera code

#include "quakedef.h"

#if USE_ORIGINAL_CVAR
cvar_t	chase_back = {"chase_back", "100"};
cvar_t	chase_up = {"chase_up", "16"};
cvar_t	chase_right = {"chase_right", "0"};
cvar_t	chase_active = {"chase_active", "0"};
#endif

void Chase_Init(void)
{
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&chase_back);
	Cvar_RegisterVariable (&chase_up);
	Cvar_RegisterVariable (&chase_right);
	Cvar_RegisterVariable (&chase_active);
#endif
}

void Chase_Reset(void)
{
    // for respawning and teleporting
//	start position 12 units behind head
}

void TraceLine(vec3_t start, vec3_t end, vec3_t impact)
{
    trace_t trace;

    fastMemclear32(&trace, sizeof(trace) / 4);
#if !SEPARATE_BRUSH_MODEL_DATA
	SV_RecursiveHullCheck (cl.worldmodel->hulls, 0, 0, 1, start, end, &trace);
#else
    SV_RecursiveHullCheck(_g->cl.worldmodel->brushModelData->hulls, 0, 0, 1,
            start, end, &trace);
#endif
    VectorCopy(trace.endpos, impact);
}

void Chase_Update(void)
{
    int i;
    float dist;
    vec3_t forward, up, right;
    vec3_t dest, stop;

    // if can't see player, reset
    AngleVectors(_g->cl.viewangles, forward, right, up);

    // calc exact destination
    for (i = 0; i < 3; i++)
        _g->chase_dest[i] = _g->r_refdef.vieworg[i] - forward[i] * chase_back - right[i] * chase_right;
    _g->chase_dest[2] = _g->r_refdef.vieworg[2] + chase_up;

    // find the spot the player is looking at
    VectorMA(_g->r_refdef.vieworg, 4096, forward, dest);
    TraceLine(_g->r_refdef.vieworg, dest, stop);

    // calculate pitch to look at the same spot from camera
    VectorSubtract(stop, _g->r_refdef.vieworg, stop);
    dist = DotProduct(stop, forward);
    if (dist < 1)
        dist = 1;
    _g->r_refdef.viewangles[PITCH] = -atanf(stop[2] / dist) / M_PI * 180;

    // move towards destination
    VectorCopy(_g->chase_dest, _g->r_refdef.vieworg);
}

