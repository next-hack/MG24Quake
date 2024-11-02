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
// cl_main.c  -- client main loop
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
//#pragma GCC optimize("Os") //
#endif
// we need to declare some mouse variables here, because the menu system
// references them even when on a unix system.

// these two are not intended to be set directly
#if USE_ORIGINAL_CVAR
cvar_t cl_name =
{   "_cl_name", "player", true};
cvar_t cl_color =
{   "_cl_color", "0", true};

cvar_t cl_shownet =
{   "cl_shownet","0"};	// can be 0, 1, or 2
cvar_t cl_nolerp =
{   "cl_nolerp","0"};

cvar_t lookspring =
{   "lookspring","0", true};
cvar_t lookstrafe =
{   "lookstrafe","0", true};
cvar_t sensitivity =
{   "sensitivity","3", true};

cvar_t m_pitch =
{   "m_pitch","0.022", true};
cvar_t m_yaw =
{   "m_yaw","0.022", true};
cvar_t m_forward =
{   "m_forward","1", true};
cvar_t m_side =
{   "m_side","0.8", true};

#endif

// FIXME: put these on hunk? NO for God's sake!
#if !DIRECT_SINGLE_PLAYER
efrag_t cl_efrags[MAX_EFRAGS];
entity_t cl_static_entities[MAX_STATIC_ENTITIES];
#endif

#if SEPARATE_TEMP_ENTITIES
entity_t cl_entities[MAX_EDICTS];
#else
AUX_SECTION entity_t cl_entities[MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES + MAX_TEMP_ENTITIES];
#endif

#if DIRECT_SINGLE_PLAYER
extern uint8_t *pve; //[(MAX_EDICTS + 7) / 8];  //potential visible entities
#endif // DIRECT_SINGLE_PLAYER

/*
 =====================
 CL_ClearState

 =====================
 */
void CL_ClearState(void)
{
    if (!sv.active)
    {
        Host_ClearMemory();
    }
    SZ_Clear(&_g->cls.message);
#if SEPARATE_TEMP_ENTITIES
	memset (cl_temp_entities, 0, sizeof(cl_temp_entities));
#endif
    memset(_g->cl_beams, 0, sizeof(_g->cl_beams));
    memset(_g->cl_dlights, 0, sizeof(_g->cl_dlights));
    //
    if (areModelsFinalized()) // this is the case when exactly the same level is being reloaded due to savegame.
    {
        // next-hack: yes this is a hack, but it will simplify reload and reduce flash write operations.
        return;
    }

    // wipe the entire cl structure
    memset(&_g->cl, 0, sizeof(_g->cl));


// clear other arrays
#if !DIRECT_SINGLE_PLAYER
	memset (cl_efrags, 0, sizeof(cl_efrags));
#endif
    memset(cl_entities, 0, sizeof(cl_entities));
//	memset (cl_lightstyle, 0, sizeof(cl_lightstyle));

//
// allocate the efrags and chain together into a free list
//
#if !DIRECT_SINGLE_PLAYER
	cl.free_efrags = cl_efrags;
	int i;
	for (i=0 ; i<MAX_EFRAGS-1 ; i++)
		cl.free_efrags[i].entnext = &cl.free_efrags[i+1];
	cl.free_efrags[i].entnext = NULL;
#endif
}

/*
 =====================
 CL_Disconnect

 Sends a disconnect message to the server
 This is also called on Host_Error, so it shouldn't cause any errors
 =====================
 */
void CL_Disconnect(void)
{
// stop sounds (especially looping!)
    S_StopAllSounds(true);

// bring the console down and fade the colors back to normal
//	SCR_BringDownConsole ();

// if running a local server, shut it down
    if (_g->cls.demoplayback)
        CL_StopPlayback();
    else if (_g->cls.state == ca_connected)
    {
        if (_g->cls.demorecording)
            CL_Stop_f();

        Con_DPrintf("Sending clc_disconnect\n");
        SZ_Clear(&_g->cls.message);
        MSG_WriteByte(&_g->cls.message, clc_disconnect);
        NET_SendUnreliableMessage(_g->cls.netcon, &_g->cls.message);
        SZ_Clear(&_g->cls.message);
        NET_Close(_g->cls.netcon);

        _g->cls.state = ca_disconnected;
        if (sv.active)
            Host_ShutdownServer(false);
    }

    _g->cls.demoplayback = _g->cls.timedemo = false;
    _g->cls.signon = 0;
}

void CL_Disconnect_f(void)
{
    CL_Disconnect();
    if (sv.active)
        Host_ShutdownServer(false);
}

/*
 =====================
 CL_EstablishConnection

 Host should be either "local" or a net address to be passed on
 =====================
 */
void CL_EstablishConnection(char *host)
{
    if (_g->cls.state == ca_dedicated)
        return;

    if (_g->cls.demoplayback)
        return;

    CL_Disconnect();

    _g->cls.netcon = NET_Connect(host);
    if (!_g->cls.netcon)
        Host_Error("CL_Connect: connect failed\n");
    Con_DPrintf("CL_EstablishConnection: connected to %s\n", host);

    _g->cls.demonum = -1;			// not in the demo loop now
    _g->cls.state = ca_connected;
    _g->cls.signon = 0;				// need all the signon messages before playing
}

/*
 =====================
 CL_SignonReply

 An svc_signonnum has been received, perform a client side setup
 =====================
 */
void CL_SignonReply(void)
{
    char *str = _g->cls.signonreply;

    Con_DPrintf("CL_SignonReply: %i\n", _g->cls.signon);
    printf("_g->cls.signon %d\r\n", _g->cls.signon);
    char vastr[64];
    switch (_g->cls.signon)
    {
        case 1:
            MSG_WriteByte(&_g->cls.message, clc_stringcmd);
            MSG_WriteString(&_g->cls.message, "prespawn");
            break;

        case 2:
            MSG_WriteByte(&_g->cls.message, clc_stringcmd);
            MSG_WriteString(&_g->cls.message, va(vastr, "name \"%s\"\n", cl_name));

            MSG_WriteByte(&_g->cls.message, clc_stringcmd);
            MSG_WriteString(&_g->cls.message, va(vastr, "color %i %i\n", ((int )cl_color) >> 4, ((int )cl_color) & 15));

            MSG_WriteByte(&_g->cls.message, clc_stringcmd);
#if HAS_SPAWN_PARAMS
		sprintf (str, "spawn %s", _g->cls.spawnparms);
#else
            sprintf(str, "spawn");
#endif
            MSG_WriteString(&_g->cls.message, str);
            break;

        case 3:
            MSG_WriteByte(&_g->cls.message, clc_stringcmd);
            MSG_WriteString(&_g->cls.message, "begin");
            //Cache_Report ();		// print remaining memory
            break;

        case 4:
            SCR_EndLoadingPlaque();		// allow normal screen updates
//        system("pause");
            break;
    }
}

/*
 =====================
 CL_NextDemo

 Called to play the next demo in the demo loop
 =====================
 */
void CL_NextDemo(void)
{
#if USE_MORE_STACK
	char	str[1024]; // actually 64 would be fine too...
#else
    tempStringStack -= 1024;
    char *str = tempStringStack;
#endif

    if (_g->cls.demonum == -1)
        return;		// don't play demos

    SCR_BeginLoadingPlaque();

    if (!_g->cls.demos[_g->cls.demonum][0] || _g->cls.demonum == MAX_DEMOS)
    {
        _g->cls.demonum = 0;
        if (!_g->cls.demos[_g->cls.demonum][0])
        {
            Con_Printf("No demos listed with startdemos\n");
            _g->cls.demonum = -1;
            return;
        }
    }

    sprintf(str, "playdemo %s\n", _g->cls.demos[_g->cls.demonum]);
    Cbuf_InsertText(str);
    _g->cls.demonum++;
}

/*
 ==============
 CL_PrintEntities_f
 ==============
 */
void CL_PrintEntities_f(void)
{
#if 0
	entity_t	*ent;
	int			i;

	for (i=0,ent=cl_entities ; i<cl.num_entities ; i++,ent++)
	{
		Con_Printf ("%3i:",i);
		if (!getEntityModel(ent))
		{
			Con_Printf ("EMPTY\n");
			continue;
		}
		#if !ENTITY_HAS_SHORT_COORDS
		Con_Printf ("%s:%2i  (%5.1f,%5.1f,%5.1f) [%5.1f %5.1f %5.1f]\n"
		,getEntityModel(ent)->name,ent->frame, ent->origin[0], ent->origin[1], ent->origin[2], ent->angles[0], ent->angles[1], ent->angles[2]);
		#else
		Con_Printf ("%s:%2i  (%5.1f,%5.1f,%5.1f) [%5.1f %5.1f %5.1f]\n"
		,getEntityModel(ent)->name,
		getEntityFrame(ent),
		toFloatCoord(getEntityOrigin(ent, 0)),
		toFloatCoord(getEntityOrigin(ent, 1)),
		toFloatCoord(getEntityOrigin(ent, 2)),
		toFloatAngle(getEntityAngle(ent, 0)),
		toFloatAngle(getEntityAngle(ent, 1)),
		toFloatAngle(getEntityAngle(ent, 2)));

		#endif
	}
	#else
    if (!sv.active)
        return;
    edict_t *e = sv.edicts;
    int num = 0;
    do
    {
        int classname = get_qcc_classname(e);
        int type = qcc_classname2type[classname];
        Con_Printf("Ent: %i, idx %d, type %d, size %d, classname (%d) %s\n", num, EDICT_TO_PROG(e), type, getEdictEntvarSize(e), classname, getStringFromIndex(classname));
        num++;
        e = getNextEdict(e);
    }
    while (e != END_EDICT);
#endif
}

/*
 ===============
 SetPal

 Debugging tool, just flashes the screen
 ===============
 */
void SetPal(int i)
{
#if 0
	static int old;
	byte	pal[768];
	int		c;

	if (i == old)
		return;
	old = i;

	if (i==0)
		VID_SetPalette (host_basepal);
	else if (i==1)
	{
		for (c=0 ; c<768 ; c+=3)
		{
			pal[c] = 0;
			pal[c+1] = 255;
			pal[c+2] = 0;
		}
		VID_SetPalette (pal);
	}
	else
	{
		for (c=0 ; c<768 ; c+=3)
		{
			pal[c] = 0;
			pal[c+1] = 0;
			pal[c+2] = 255;
		}
		VID_SetPalette (pal);
	}
#else
    (void) i;
#endif
}

/*
 ===============
 CL_AllocDlight

 ===============
 */
dlight_t* CL_AllocDlight(int key)
{
    int i;
    dlight_t *dl;

// first look for an exact key match
    if (key)
    {
        dl = _g->cl_dlights;
        for (i = 0; i < MAX_DLIGHTS; i++, dl++)
        {
            if (dl->key == key)
            {
                fastMemclear32(dl, sizeof(*dl) / 4);
                dl->key = key;
                return dl;
            }
        }
    }

// then look for anything else
    dl = _g->cl_dlights;
    for (i = 0; i < MAX_DLIGHTS; i++, dl++)
    {
        if (dl->die < _g->cl.time)
        {
            fastMemclear32(dl, sizeof(*dl) / 4);
            dl->key = key;
            return dl;
        }
    }

    dl = &_g->cl_dlights[0];
    fastMemclear32(dl, sizeof(*dl) / 4);
    dl->key = key;
    return dl;
}

/*
 ===============
 CL_DecayLights

 ===============
 */
void CL_DecayLights(void)
{
    int i;
    dlight_t *dl;
    float time;

    time = _g->cl.time - _g->cl.oldtime;

    dl = _g->cl_dlights;
    for (i = 0; i < MAX_DLIGHTS; i++, dl++)
    {
        if (dl->die < _g->cl.time || !dl->radius)
            continue;
#if PACK_DLIGHTS
		dl->radius -= time* (dl->hasDecay300 ? 300 : 0);
#else
        dl->radius -= time * dl->decay;
#endif
        if (dl->radius < 0)
            dl->radius = 0;
    }
}

/*
 ===============
 CL_LerpPoint

 Determines the fraction between the last two messages that the objects
 should be put at.
 ===============
 */
float CL_LerpPoint(void)
{
    float f, frac;

    f = _g->cl.mtime[0] - _g->cl.mtime[1];

    if (!f || cl_nolerp || _g->cls.timedemo || sv.active)
    {
        _g->cl.time = _g->cl.mtime[0];
        return 1;
    }

    if (f > 0.1)
    {	// dropped packet, or start of demo
        _g->cl.mtime[1] = _g->cl.mtime[0] - 0.1;
        f = 0.1;
    }
    frac = (_g->cl.time - _g->cl.mtime[1]) / f;
    if (frac < 0)
    {
        if (frac < -0.01)
        {
            SetPal(1);
            _g->cl.time = _g->cl.mtime[1];
        }
        frac = 0;
    }
    else if (frac > 1)
    {
        if (frac > 1.01)
        {
            SetPal(2);
            _g->cl.time = _g->cl.mtime[0];
        }
        frac = 1;
    }
    else
        SetPal(0);

    return frac;
}

/*
 ===============
 CL_RelinkEntities
 ===============
 */
void CL_RelinkEntities(void)
{
    entity_t *ent;
    int i, j;
    float frac, f, d;
    vec3_t delta;
    float bobjrotate;
    vec3_t oldorg;
    dlight_t *dl;

// determine partial update time
    frac = CL_LerpPoint();

    _g->cl_numvisedicts = 0;

//
// interpolate player info
//
    for (i = 0; i < 3; i++)
        _g->cl.velocity[i] = _g->cl.mvelocity[1][i] + frac * (_g->cl.mvelocity[0][i] - _g->cl.mvelocity[1][i]);

    if (_g->cls.demoplayback)
    {
        // interpolate the angles
        for (j = 0; j < 3; j++)
        {
            d = _g->cl.mviewangles[0][j] - _g->cl.mviewangles[1][j];
            if (d > 180)
                d -= 360;
            else if (d < -180)
                d += 360;
            _g->cl.viewangles[j] = _g->cl.mviewangles[1][j] + frac * d;
        }
    }

    bobjrotate = anglemod(100 * _g->cl.time);
    //   edict_t *pedict =  sv.edicts;
// start on the entity after the world
    for (i = 1, ent = cl_entities + 1; i < _g->cl.num_entities; i++, ent++)
    {
        if (sv.active)
        {
//            pedict = getNextEdict(pedict);
//            ent->data = pedict;
            ent->mustBeDrawn = (pve[i >> 3] & (1 << (i & 7))) ? 1 : 0;
            if (!ent->mustBeDrawn)
                continue;
        }
        else
        {
            ent->data = &_g->client_entity_data[i];
        }
        if (!getEntityModel(ent))
        {	// empty slot
#if !DIRECT_SINGLE_PLAYER
			if (ent->forcelink)
				R_RemoveEfrags (ent);	// just became empty
    #endif
            continue;
        }

// if the object wasn't included in the last packet, remove it
        if (!sv.active && (getEntityMsgTime(ent) != _g->cl.mtime[0]))
        {
            setEntityModel(ent, NULL);
            continue;
        }
        if (!sv.active)
        {
            VectorCopy(VEC(getEntityOrigins(ent)), oldorg);
        }
        else
        {
            // next-hack: fix for missing trails. Well, better than nothing. Probably we could use get_qcc_oldorg, but we are getting 0. FIXME.
            if (ent->data)
            {
                VectorCopy(VEC(get_qcc_origin(ent->data)), oldorg);
                float deltatime = _g->cl.time - _g->cl.oldtime;
                vec3_t delta;
                VectorScale(VEC(get_qcc_velocity(ent->data)), deltatime, delta);
                VectorSubtract(oldorg, delta, oldorg);  // recover old position
            }
        }
        if (getEntityForceLink(ent))
        {	// the entity was not updated in the last message
            // so move to the final spot
            // next-hack: FIXME this will not work if you late implement multiplayer (i.e. not direct single)
            if (!sv.active)
            {
                for (int i = 0; i < 3; i++)
                {
                    VectorCopy(((client_entity_t* )ent->data)->msg_origins_s[0], ((client_entity_t* ) ent->data)->origin_s);
                    VectorCopy(((client_entity_t* )ent->data)->msg_angles_s[0], ((client_entity_t* ) ent->data)->angles_s);
                }
            }
        }
        else if (!sv.active)
        {	// if the delta is large, assume a teleport and don't lerp
            f = frac;
            for (j = 0; j < 3; j++)
            {
#if !ENTITY_HAS_SHORT_COORDS
				delta[j] = ent->msg_origins[0][j] - ent->msg_origins[1][j];
#else
                delta[j] = toFloatCoord(((client_entity_t*) ent->data)->msg_origins_s[0][j] - ((client_entity_t*) ent->data)->msg_origins_s[1][j]);
#endif

                if (delta[j] > 100 || delta[j] < -100)
                    f = 1;		// assume a teleportation, not a motion
            }

            // interpolate the origin and angles
            for (j = 0; j < 3; j++)
            {
#if !NO_LERP
#if !ENTITY_HAS_SHORT_COORDS
				ent->origin[j] = ent->msg_origins[1][j] + f*delta[j];
#else
                ((client_entity_t*) ent->data)->origin_s[j] = ((client_entity_t*) ent->data)->msg_origins_s[1][j] + toShortCoord(f * delta[j]);
#endif
#if !ENTITY_HAS_SHORT_COORDS
				d = ent->msg_angles[0][j] - ent->msg_angles[1][j];
				if (d > 180)
					d -= 360;
				else if (d < -180)
					d += 360;
				ent->angles[j] = ent->msg_angles[1][j] + f*d;
#else
                d = toFloatAngle(((client_entity_t*) ent->data)->msg_angles_s[0][j] - ((client_entity_t*) ent->data)->msg_angles_s[1][j]);
                if (d > 180)
                    d -= 360;
                else if (d < -180)
                    d += 360;
                ((client_entity_t*) ent->data)->angles_s[j] = toShortAngle(toFloatAngle(((client_entity_t*) ent->data)->msg_angles_s[1][j]) + f * d);
#endif
#else
    ent->origin[j] = ent->msg_origins[0][j];
    ent->angles[j] = ent->msg_angles[0][j];
#endif
            }

        }

// rotate binary objects locally
        if (getEntityModel(ent)->flags & EF_ROTATE)
#if !ENTITY_HAS_SHORT_COORDS
			ent->angles[1] = bobjrotate;
#else
            setEntityAngle(ent, 1, bobjrotate);
#endif
        if (getEntityEffects(ent) & EF_BRIGHTFIELD)
            R_EntityParticles(ent);
#ifdef QUAKE2
		if (ent->effects & EF_DARKFIELD)
			R_DarkFieldParticles (ent);
#endif
        if (getEntityEffects(ent) & EF_MUZZLEFLASH)
        {
            vec3_t fv, rv, uv;

            dl = CL_AllocDlight(i);
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (ent->origin,  dl->origin);
			dl->origin[2] += 16;
			AngleVectors (ent->angles, fv, rv, uv);
#else
#if DLIGHT_HAS_FLOAT_ORIGIN
            VectorCopy (VEC(getEntityOrigins(ent)),  dl->origin);
			dl->origin[2] += 16;
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = getEntityOrigin(ent, j);
            dl->iorigin_s[2] += 16;
#endif
            AngleVectors(VEC(getEntityAngles(ent)), fv, rv, uv);
#endif
#if DLIGHT_HAS_FLOAT_ORIGIN
			VectorMA (dl->origin, 18, fv, dl->origin);
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] += fv[j] * 18;
#endif
            dl->radius = 200 + (rand() & 31);
#if PACK_DLIGHTS
      dl->hasMinlight32 = 1;  // let's save one float!
#else
            dl->minlight = 32;
#endif
            dl->die = _g->cl.time + 0.1;
        }
        if (getEntityEffects(ent) & EF_BRIGHTLIGHT)
        {
            dl = CL_AllocDlight(i);
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (ent->origin,  dl->origin);
#else
#if DLIGHT_HAS_FLOAT_ORIGIN
			VectorCopy (VEC(getEntityOrigins(ent)),  dl->origin);
			dl->origin[2] += 16;
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = getEntityOrigin(ent, j);
            dl->iorigin_s[2] += 16;
#endif
#endif
            dl->radius = 400 + (rand() & 31);
            dl->die = _g->cl.time + 0.001;
        }
        if (getEntityEffects(ent) & EF_DIMLIGHT)
        {
            dl = CL_AllocDlight(i);
#if !ENTITY_HAS_SHORT_COORDS
			VectorCopy (ent->origin,  dl->origin);
#else
#if DLIGHT_HAS_FLOAT_ORIGIN
			VectorCopy (VEC(getEntityOrigins(ent)),  dl->origin);
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = getEntityOrigin(ent, j);
#endif
#endif
            dl->radius = 200 + (rand() & 31);
            dl->die = _g->cl.time + 0.001;
        }
#ifdef QUAKE2
		if (ent->effects & EF_DARKLIGHT)
		{
			dl = CL_AllocDlight (i);
			VectorCopy (ent->origin,  dl->origin);
			dl->radius = 200.0 + (rand()&31);
			dl->die = cl.time + 0.001;
			dl->dark = true;
		}
		if (ent->effects & EF_LIGHT)
		{
			dl = CL_AllocDlight (i);
			VectorCopy (ent->origin,  dl->origin);
			dl->radius = 200;
			dl->die = cl.time + 0.001;
		}
#endif
#if !ENTITY_HAS_SHORT_COORDS
		if (ent->model->flags & EF_GIB)
			R_RocketTrail (oldorg, ent->origin, 2);
		else if (ent->model->flags & EF_ZOMGIB)
			R_RocketTrail (oldorg, ent->origin, 4);
		else if (ent->model->flags & EF_TRACER)
			R_RocketTrail (oldorg, ent->origin, 3);
		else if (ent->model->flags & EF_TRACER2)
			R_RocketTrail (oldorg, ent->origin, 5);
		else if (ent->model->flags & EF_ROCKET)
		{
			R_RocketTrail (oldorg, ent->origin, 0);
			dl = CL_AllocDlight (i);
			VectorCopy (ent->origin, dl->origin);
			dl->radius = 200;
			dl->die = cl.time + 0.01;
		}
		else if (ent->model->flags & EF_GRENADE)
			R_RocketTrail (oldorg, ent->origin, 1);
		else if (ent->model->flags & EF_TRACER3)
			R_RocketTrail (oldorg, ent->origin, 6);
#else
        int entflags = getEntityModel(ent)->flags;
        if (entflags & EF_GIB)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 2);
        else if (entflags & EF_ZOMGIB)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 4);
        else if (entflags & EF_TRACER)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 3);
        else if (entflags & EF_TRACER2)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 5);
        else if (entflags & EF_ROCKET)
        {
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 0);
            dl = CL_AllocDlight(i);
#if DLIGHT_HAS_FLOAT_ORIGIN
			VectorCopy (VEC(getEntityOrigins(ent)),  dl->origin);
#else
            for (int j = 0; j < 3; j++)
                dl->iorigin_s[j] = getEntityOrigin(ent, j);
#endif
            dl->radius = 200;
            dl->die = _g->cl.time + 0.01;
        }
        else if (entflags & EF_GRENADE)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 1);
        else if (entflags & EF_TRACER3)
            R_RocketTrail(oldorg, VEC(getEntityOrigins(ent)), 6);

#endif
        setEntityForceLink(ent, false);

        if (i == _g->cl.viewentity && !chase_active)
            continue;

#ifdef QUAKE2
		if ( ent->effects & EF_NODRAW )
			continue;
#endif
        if (_g->cl_numvisedicts < MAX_VISEDICTS)
        {
#if POINTER_CL_VISEDICT
		  _g->cl_visedicts[_g->cl_numvisedicts] = ent;
#else
            _g->cl_visedicts[_g->cl_numvisedicts] = ent - &cl_entities[0];
#endif
            _g->cl_numvisedicts++;
        }
    }

}

/*
 ===============
 CL_ReadFromServer

 Read all incoming data from the server
 ===============
 */
int CL_ReadFromServer(void)
{
    int ret;

    _g->cl.oldtime = _g->cl.time;
    _g->cl.time += host_frametime;

    do
    {
        ret = CL_GetMessage();
        if (ret == -1)
            Host_Error("CL_ReadFromServer: lost server connection");
        if (!ret)
            break;

        _g->cl.last_received_message = realtime;
        CL_ParseServerMessage();
    }
    while (ret && _g->cls.state == ca_connected);

#if 0
    if (cl_shownet)
        Con_Printf("\n");
#endif
#if DONT_SEND_DATA_LOCALLY
    if (DIRECT_SINGLE_PLAYER && sv.active)
    {
        edict_t *pedict = sv.edicts;
	    for (int i = 1; i < MAX_EDICTS; i++)
        {
            if (pedict)    // end of edicts
                pedict = getNextEdict(pedict);
            entity_t *ent = CL_EntityNum (i);
            ent->entityType = TYPE_EDICT_ENTITY;
            if ((pve[i >> 3] & (1 << (i & 7))) && pedict)
            {
                ent->data = pedict;
                ent->mustBeDrawn = 1;
                if ((pve[i >> 3] & (1 << (i & 7))))
                    setEntityForceLink(ent, true);
            }
            else
            {
                setEntityForceLink(ent, true);
                ent->mustBeDrawn = 0;
            }
        }
    }
#endif
    CL_ParseDummyUpdate();      // this will return if !sv.active
    CL_RelinkEntities();
    CL_UpdateTEnts();

//
// bring the links up to date
//
    return 0;
}

/*
 =================
 CL_SendCmd
 =================
 */
void CL_SendCmd(void)
{
    usercmd_t cmd;

    if (_g->cls.state != ca_connected)
        return;

    if (_g->cls.signon == SIGNONS)
    {
        // get basic movement from keyboard
        CL_BaseMove(&cmd);

        // allow mice or other external controllers to add to the move
        IN_Move(&cmd);

        // send the unreliable message
        CL_SendMove(&cmd);

    }

    if (_g->cls.demoplayback)
    {
        SZ_Clear(&_g->cls.message);
        return;
    }

// send the reliable message
    if (!_g->cls.message.cursize)
        return;		// no message at all

    if (!NET_CanSendMessage(_g->cls.netcon))
    {
        Con_DPrintf("CL_WriteToServer: can't send\n");
        return;
    }

    if (NET_SendMessage(_g->cls.netcon, &_g->cls.message) == -1)
        Host_Error("CL_WriteToServer: lost server connection");

    SZ_Clear(&_g->cls.message);
}

/*
 =================
 CL_Init
 =================
 */
#define USE_GP_BUFFER_FOR_CLIENT_DATA 1
void CL_Init(void)
{
#if !USE_GP_BUFFER_FOR_CLIENT_DATA

	ERRORSZ_Alloc (&_g->cls.message, 1024);
#else
    int maxsize = 0;
    _g->cls.message.data = allocFromTempBuffer(1024, &maxsize);
    _g->cls.message.maxsize = maxsize;
    _g->cls.message.cursize = 0;
    _g->cls.signonreply = allocFromTempBuffer(8192, NULL);
#endif
    CL_InitInput();
    CL_InitTEnts();

//
// register our commands
//
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&cl_name);
	Cvar_RegisterVariable (&cl_color);
	Cvar_RegisterVariable (&cl_upspeed);
	Cvar_RegisterVariable (&cl_forwardspeed);
	Cvar_RegisterVariable (&cl_backspeed);
	Cvar_RegisterVariable (&cl_sidespeed);
	Cvar_RegisterVariable (&cl_movespeedkey);
	Cvar_RegisterVariable (&cl_yawspeed);
	Cvar_RegisterVariable (&cl_pitchspeed);
	Cvar_RegisterVariable (&cl_anglespeedkey);
	Cvar_RegisterVariable (&cl_shownet);
	Cvar_RegisterVariable (&cl_nolerp);
	Cvar_RegisterVariable (&lookspring);
	Cvar_RegisterVariable (&lookstrafe);
	Cvar_RegisterVariable (&sensitivity);

	Cvar_RegisterVariable (&m_pitch);
	Cvar_RegisterVariable (&m_yaw);
	Cvar_RegisterVariable (&m_forward);
	Cvar_RegisterVariable (&m_side);

//	Cvar_RegisterVariable (&cl_autofire);
#endif
}

