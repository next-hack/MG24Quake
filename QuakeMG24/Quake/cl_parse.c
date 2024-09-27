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
// cl_parse.c  -- parse a message received from the server

#include "quakedef.h"

const char *const svc_strings[] =
{
    "svc_bad",
    "svc_nop",
    "svc_disconnect",
    "svc_updatestat",
    "svc_version",    // [long] server version
    "svc_setview",    // [short] entity number
    "svc_sound",      // <see code>
    "svc_time",     // [float] server time
    "svc_print",      // [string] null terminated string
    "svc_stufftext",    // [string] stuffed into client's console buffer
            // the string should be \n terminated
    "svc_setangle",   // [vec3] set the view angle to this absolute value

    "svc_serverinfo",   // [long] version
            // [string] signon string
            // [string]..[0]model cache [string]...[0]sounds cache
            // [string]..[0]item cache
    "svc_lightstyle",   // [byte] [string]
    "svc_updatename",   // [byte] [string]
    "svc_updatefrags",  // [byte] [short]
    "svc_clientdata",   // <shortbits + data>
    "svc_stopsound",    // <see code>
    "svc_updatecolors", // [byte] [byte]
    "svc_particle",   // [vec3] <variable>
    "svc_damage",     // [byte] impact [byte] blood [vec3] from

    "svc_spawnstatic",
    "OBSOLETE svc_spawnbinary",
    "svc_spawnbaseline",

    "svc_temp_entity",    // <variable>
    "svc_setpause",
    "svc_signonnum",
    "svc_centerprint",
    "svc_killedmonster",
    "svc_foundsecret",
    "svc_spawnstaticsound",
    "svc_intermission",
    "svc_finale",     // [string] music [string] text
    "svc_cdtrack",      // [byte] track [byte] looptrack
    "svc_sellscreen",
    "svc_cutscene"
};

//=============================================================================

/*
 ===============
 CL_EntityNum

 This error checks and tracks the total number of entities
 ===============
 */
entity_t* CL_EntityNum(int num)
{
    if (num >= _g->cl.num_entities)
    {
        if (num >= MAX_EDICTS)
            Host_Error("CL_EntityNum: %i is an invalid number", num);
        while (_g->cl.num_entities <= num)
        {
#if HAS_MULTIPLAYER
      cl_entities[cl.num_entities].colormap = vid.colormap;
#endif
            _g->cl.num_entities++;
        }
    }

    return &cl_entities[num];
}

/*
 ==================
 CL_ParseStartSoundPacket
 ==================
 */
void CL_ParseStartSoundPacket(void)
{
    vec3_t pos;
    int channel, ent;
    int sound_num;
    int volume;
    int field_mask;
    float attenuation;
    int i;

    field_mask = MSG_ReadByte();

    if (field_mask & SND_VOLUME)
    {
        volume = MSG_ReadByte();
    }
    else
    {
        volume = DEFAULT_SOUND_PACKET_VOLUME;
    }
    if (field_mask & SND_ATTENUATION)
    {
        attenuation = MSG_ReadByte() / 64.0f;
    }
    else
    {
        attenuation = DEFAULT_SOUND_PACKET_ATTENUATION;
    }
    channel = MSG_ReadShort();
    sound_num = MSG_ReadByte();

    ent = channel >> 3;
    channel &= 7;
#if !EDICT_LINKED_LIST
  if (ent > MAX_EDICTS)
    Host_Error ("CL_ParseStartSoundPacket: ent = %i", ent);
#endif
    for (i = 0; i < 3; i++)
    {
        pos[i] = MSG_ReadCoord();
    }
    S_StartSound(ent, channel, _g->cl.sound_precache[sound_num], pos, volume / 255.0, attenuation);
}

/*
 ==================
 CL_KeepaliveMessage

 When the client is taking a long time to load stuff, send keepalive messages
 so the server doesn't disconnect.
 ==================
 */
void CL_KeepaliveMessage(void)
{
// FIXME: next-hack this function to be basically removed.
    float time;
    static float lastmsg;
    int ret;
    sizebuf_t old;
    byte olddata[8192];

    if (sv.active)
        return;   // no need if server is local
    if (_g->cls.demoplayback)
        return;

// read messages from server, should just be nops
    old = net_message;
    memcpy(olddata, net_message.data, net_message.cursize);

    do
    {
        ret = CL_GetMessage();
        switch (ret)
        {
            default:
                Host_Error("CL_KeepaliveMessage: CL_GetMessage failed");
                /* no break */
            case 0:
                break;  // nothing waiting
            case 1:
                Host_Error("CL_KeepaliveMessage: received a message");
                break;
            case 2:
                if (MSG_ReadByte() != svc_nop)
                    Host_Error("CL_KeepaliveMessage: datagram wasn't a nop");
                break;
        }
    }
    while (ret);

    net_message = old;
    memcpy(net_message.data, olddata, net_message.cursize);

// check time
    time = Sys_FloatTime();
    if (time - lastmsg < 5)
        return;
    lastmsg = time;

// write out a nop
    Con_Printf("--> client to server keepalive\n");

    MSG_WriteByte(&_g->cls.message, clc_nop);
    NET_SendMessage(_g->cls.netcon, &_g->cls.message);
    SZ_Clear(&_g->cls.message);
}

/*
 ==================
 CL_ParseServerInfo
 ==================
 */
//extern client_entity_t *_client_entity_data;
void CL_ParseServerInfo(void)
{
    char *str;
    int i;
#if READ_BEFORE_CACHE
#error No more implemented.
#else

    Con_DPrintf("Serverinfo packet received.\n");
//
// wipe the client_state_t struct
//
    CL_ClearState();

// parse protocol version number
    i = MSG_ReadLong();
    if (i != PROTOCOL_VERSION)
    {
        Con_Printf("Server returned version %i, not %i", i, PROTOCOL_VERSION);
        return;
    }

// parse maxclients
    _g->cl.maxclients = MSG_ReadByte();
    if (_g->cl.maxclients < 1 || _g->cl.maxclients > MAX_SCOREBOARD)
    {
        Con_Printf("Bad maxclients (%u) from server\n", _g->cl.maxclients);
        return;
    }
// parse gametype
    _g->cl.gametype = MSG_ReadByte();

// parse signon message
    char *strbuf = getTextureCacheBuffer();  //[2048];
    str = MSG_ReadString(strbuf, 2048);
    strncpy(_g->cl.levelname, str, sizeof(_g->cl.levelname) - 1);

// seperate the printfs so the server message can have a color
    Con_Printf("\n\n\35\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\36\37\n\n");
    Con_Printf("%c%s\n", 2, _g->cl.levelname);

//
// first we go through and touch all of the precache data that still
// happens to be in the cache, so precaching something else doesn't
// needlessly purge it
//

// precache models
    model_t **model_precache = (model_t**) ((byte*) getTextureCacheBuffer() + 2048); // + 2048 because the temp string "strbuf" is at +0, and is 2048 bytes long
    memset(model_precache, 0, sizeof(*model_precache) * MAX_MODELS);
    _g->cl.model_precache = model_precache;
    int nummodels;
    for (nummodels = 1;; nummodels++)
    {
        str = MSG_ReadString(strbuf, 2048);
        if (!str[0])
            break; edictDbgPrintf("Server asked to precache %s\r\n", str);
        if (nummodels == MAX_MODELS)
        {
            Con_Printf("Server sent too many model precaches\n");
            return;
        }
//    strcpy (model_precache[nummodels], str);
        Mod_TouchModel(str);
        //
        _g->cl.model_precache[nummodels] = Mod_ForName(str, false);
        if (_g->cl.model_precache[nummodels] == NULL)
        {
            Con_Printf("Model %s not found\n", str);
            return;
        }
//    CL_KeepaliveMessage ();
    } edictDbgPrintf("Server asked to precache %d models\r\n", nummodels);
    //FIXME("Finished precaching firstModels\r\n");
    byte *wm = (byte*) mod_known;
    if (sv.active)
    {
        for (int i = 0; i < MAX_MODELS; i++)
        {
            edictDbgPrintf("sv.models[%i] = 0x%p; &modknown[%i] = %p\r\n", i , sv.models[i], i, &mod_known[i]);
        }
    }
    finalizeModKnown();
    int delta = (byte*) mod_known - wm;
    // fix model references
    if (sv.active)
    {
        sv.worldmodel = (model_t*) ((byte*) sv.worldmodel + delta);
        for (int i = 0; i < MAX_MODELS; i++)
        {
            //next-hack: I'm not happy about this but whatever...
            sv.models[i] = (model_t*) ((byte*) sv.models[i] + delta);
        }
        sv.models = storeToInternalFlash(sv.models, sizeof(*sv.models) * MAX_MODELS);
    }
    // next-hack this is a horrid hack, but I can't find a better way.
    _g->cl.model_precache[0] = Mod_ForName("progs/h_player.mdl", 1);
    //
    for (int i = 1; i < MAX_MODELS; i++)
    {
        _g->cl.model_precache[i] = (model_t*) ((byte*) _g->cl.model_precache[i] + delta);
    }
    // store this info as well
    _g->cl.model_precache = storeToInternalFlash(_g->cl.model_precache, sizeof(*_g->cl.model_precache) * MAX_MODELS);
// precache sounds
    sfx_t **sound_precache = (sfx_t**) ((byte*) getTextureCacheBuffer() + 2048);  // + 2048 because the temp string "strbuf" is at +0, and is 2048 bytes long
    memset(sound_precache, 0, sizeof(*sound_precache) * MAX_SFX);

    _g->cl.sound_precache = sound_precache;
    S_BeginPrecaching();
    int numsounds;
    for (numsounds = 1;; numsounds++)
    {
        str = MSG_ReadString(strbuf, 2048);
        if (!str[0])
            break;
        if (numsounds == MAX_SOUNDS)
        {
            Con_Printf("Server sent too many sound precaches\n");
            return;
        }
        //    strcpy (sound_precache[numsounds], str);
        S_TouchSound(str);
        _g->cl.sound_precache[numsounds] = S_PrecacheSound(str);
    }
    S_EndPrecaching();
    _g->cl.sound_precache = storeToInternalFlash(_g->cl.sound_precache, sizeof(*_g->cl.sound_precache) * numsounds);

#endif
    if (_g->cls.demoplayback)
        _g->client_entity_data = Z_Calloc(MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES, sizeof(*_g->client_entity_data), PU_STATIC, NULL);

// local state
    if (sv.active)
    {
        cl_entities[0].data = &sv.edicts[0];
        cl_entities[0].entityType = TYPE_EDICT_ENTITY;
    }
    else
    {
        cl_entities[0].data = &_g->client_entity_data[0];
        cl_entities[0].entityType = TYPE_CLIENT_ENTITY;
    }
    setEntityModel(&cl_entities[0], _g->cl.model_precache[1]);
    _g->cl.worldmodel = _g->cl.model_precache[1];
#if MARK_NODE_IN_SURFACE
#if USE_NODE_DLIGHTBITS
#error
    if (nodeDlightBits)
        Z_Free(nodeDlightBits);
    nodeDlightBits = Z_Calloc(sizeof(*nodeDlightBits) * cl.worldmodel->numnodes, 1, PU_STATIC, NULL);
#else
    if (nodeHadDlight)
    {
        Z_Free(nodeHadDlight);
    }
#if !SEPARATE_BRUSH_MODEL_DATA
    nodeHadDlight = Z_Calloc( 4 * (cl.worldmodel->numnodes + 31) / 32 , 1 , PU_STATIC, NULL);
#else
    nodeHadDlight = Z_Calloc(4 * (_g->cl.worldmodel->brushModelData->numnodes + 31) / 32, 1, PU_STATIC, NULL);
#endif
#endif
#endif // MARK_NODE_IN_SURFACE
    R_NewMap();

//  Hunk_Check ();    // make sure nothing is hurt

    noclip_anglehack = false;   // noclip is turned off at start
}

/*
 ==================
 CL_ParseUpdate

 Parse an entity update message from the server
 If an entities model or origin changes from frame to frame, it must be
 relinked.  Other attributes can change without relinking.
 ==================
 */
void CL_ParseUpdate(int bits)
{
    int i;
    model_t *model;
    int modnum = 0;  // shut up compiler!
    qboolean forcelink;
    entity_t *ent;
    int num;

    if (_g->cls.signon == SIGNONS - 1)
    { // first update is the final signon stage
        _g->cls.signon = SIGNONS;
        CL_SignonReply();
    }

    if (bits & U_MOREBITS)
    {
        i = MSG_ReadByte();
        bits |= (i << 8);
    }

    if (bits & U_LONGENTITY)
        num = MSG_ReadShort();
    else
        num = MSG_ReadByte();

// FIXME next-hack: This must be checked, not sure if we still want to send from server to client.
    ent = CL_EntityNum(num);
    if (sv.active)
    {
        ent->entityType = TYPE_EDICT_ENTITY;
#if DIRECT_SINGLE_PLAYER
        if (num == 1)
            ent->data = getNextEdict(sv.edicts);
        else
            FIXME("Reading data for a client different than 1");
#endif
    }
    else
    {
        ent->entityType = TYPE_CLIENT_ENTITY;
        ent->data = &_g->client_entity_data[num];
    }

    if (sv.active || getEntityMsgTime(ent) != _g->cl.mtime[1])
    {
        forcelink = true; // no previous frame to lerp from
    }
    else
    {
        forcelink = false;
    }
    if (!sv.active)
        setEntityMsgTime(ent, _g->cl.mtime[0]);

    if (bits & U_MODEL)
    {
        modnum = MSG_ReadByte();
        if (modnum >= MAX_MODELS)
            Host_Error("CL_ParseModel: bad modnum");
    }
#if DIRECT_SINGLE_PLAYER
    else if (!sv.active)
        modnum = getEntityBaseLine(ent)->modelindex;
#else
    else
    modnum = getEntityBaseLine(ent)->modelindex;
#endif

    model = _g->cl.model_precache[modnum];
    if (model != getEntityModel(ent))
    {
        setEntityModel(ent, model);
        // automatic animation (torches, etc) can be either all together
        // or randomized
        if (model)
        {
#if FLOAT_SYNCBASE
      if (model->synctype == ST_RAND)
        ent->syncbase = (float)(rand()&0x7fff) / 0x7fff;
      else
        ent->syncbase = 0.0;
#else
            if (model->synctype == ST_RAND)
                ent->syncbase_s = rand() & ((1 << SYNCBASE_BITS) - 1);
            else
                ent->syncbase_s = 0;
#endif
        }
        else
            forcelink = true; // hack to make null model players work
#ifdef GLQUAKE
    if (num > 0 && num <= cl.maxclients)
      R_TranslatePlayerSkin (num - 1);
#endif
    }
#if DIRECT_SINGLE_PLAYER
    if (!sv.active)
#endif
    {
        if (bits & U_FRAME)
            setEntityFrame(ent, MSG_ReadByte());
        else
            setEntityFrame(ent, getEntityBaseLine(ent)->frame);
    }

    if (bits & U_COLORMAP)
        i = MSG_ReadByte();
#if HAS_MULTIPLAYER
  else
    i = ent->baseline.colormap;
  if (!i)
    ent->colormap = vid.colormap;
  else
  {
    if (i > cl.maxclients)
      Sys_Error ("i >= cl.maxclients");
    ent->colormap = cl.scores[i-1].translations;
  }
#endif
#ifdef GLQUAKE
  int     skin;

  if (bits & U_SKIN)
    skin = MSG_ReadByte();
  else
    skin = ent->baseline.skin;
  if (skin != ent->skinnum) {
    ent->skinnum = skin;
    if (num > 0 && num <= cl.maxclients)
      R_TranslatePlayerSkin (num - 1);
  }

#else
#if DIRECT_SINGLE_PLAYER
    if (!sv.active)
#endif
    {
        if (bits & U_SKIN)
            setEntitySkinnum(ent, MSG_ReadByte());
        else
            setEntitySkinnum(ent, getEntityBaseLine(ent)->skin);
    }
#endif
#if DIRECT_SINGLE_PLAYER
    if (!sv.active)
#endif
    {
        if (bits & U_EFFECTS)
            setEntityEffects(ent, MSG_ReadByte());
        else
            setEntityEffects(ent, getEntityBaseLine(ent)->effects);
    }
// shift the known values for interpolation
#if !ENTITY_HAS_SHORT_COORDS
  VectorCopy (ent->msg_origins[0], ent->msg_origins[1]);
  VectorCopy (ent->msg_angles[0], ent->msg_angles[1]);
#if DIRECT_SINGLE_PLAYER
    if (!sv.active)
#endif
    {
        if (bits & U_ORIGIN1)
            ent->msg_origins[0][0] = MSG_ReadCoord ();
        else
            ent->msg_origins[0][0] = ent->baseline.origin[0];
        if (bits & U_ANGLE1)
            ent->msg_angles[0][0] = MSG_ReadAngle();
        else
            ent->msg_angles[0][0] = ent->baseline.angles[0];

        if (bits & U_ORIGIN2)
            ent->msg_origins[0][1] = MSG_ReadCoord ();
        else
            ent->msg_origins[0][1] = ent->baseline.origin[1];
        if (bits & U_ANGLE2)
            ent->msg_angles[0][1] = MSG_ReadAngle();
        else
            ent->msg_angles[0][1] = ent->baseline.angles[1];

        if (bits & U_ORIGIN3)
            ent->msg_origins[0][2] = MSG_ReadCoord ();
        else
            ent->msg_origins[0][2] = ent->baseline.origin[2];
        if (bits & U_ANGLE3)
            ent->msg_angles[0][2] = MSG_ReadAngle();
        else
            ent->msg_angles[0][2] = ent->baseline.angles[2];
    }
#else
#if DIRECT_SINGLE_PLAYER
    if (!sv.active)
#endif // DIRECT_SINGLE_PLAYER
    {
        VectorCopy(((client_entity_t* )ent->data)->msg_origins_s[0], ((client_entity_t* )ent->data)->msg_origins_s[1]);
        VectorCopy(((client_entity_t* )ent->data)->msg_angles_s[0], ((client_entity_t* )ent->data)->msg_angles_s[1]);
        if (bits & U_ORIGIN1)
            ((client_entity_t*) ent->data)->msg_origins_s[0][0] = MSG_ReadCoordS();
        else
            ((client_entity_t*) ent->data)->msg_origins_s[0][0] = getEntityBaseLine(ent)->origin_s[0];
        if (bits & U_ANGLE1)
            ((client_entity_t*) ent->data)->msg_angles_s[0][0] = MSG_ReadAngleS();
        else
            ((client_entity_t*) ent->data)->msg_angles_s[0][0] = getEntityBaseLine(ent)->angles_s[0];

        if (bits & U_ORIGIN2)
            ((client_entity_t*) ent->data)->msg_origins_s[0][1] = MSG_ReadCoordS();
        else
            ((client_entity_t*) ent->data)->msg_origins_s[0][1] = getEntityBaseLine(ent)->origin_s[1];
        if (bits & U_ANGLE2)
            ((client_entity_t*) ent->data)->msg_angles_s[0][1] = MSG_ReadAngleS();
        else
            ((client_entity_t*) ent->data)->msg_angles_s[0][1] = getEntityBaseLine(ent)->angles_s[1];

        if (bits & U_ORIGIN3)
            ((client_entity_t*) ent->data)->msg_origins_s[0][2] = MSG_ReadCoordS();
        else
            ((client_entity_t*) ent->data)->msg_origins_s[0][2] = getEntityBaseLine(ent)->origin_s[2];
        if (bits & U_ANGLE3)
            ((client_entity_t*) ent->data)->msg_angles_s[0][2] = MSG_ReadAngleS();
        else
            ((client_entity_t*) ent->data)->msg_angles_s[0][2] = getEntityBaseLine(ent)->angles_s[2];

    }

#endif

    if (bits & U_NOLERP)
        setEntityForceLink(ent, true);

    if (forcelink)
    { // didn't have an update last message
#if !ENTITY_HAS_SHORT_COORDS
    VectorCopy (ent->msg_origins[0], ent->msg_origins[1]);
    VectorCopy (ent->msg_origins[0], ent->origin);
    VectorCopy (ent->msg_angles[0], ent->msg_angles[1]);
    VectorCopy (ent->msg_angles[0], ent->angles);
#else
        if (!sv.active)
        {
            VectorCopy(((client_entity_t* )ent->data)->msg_origins_s[0], ((client_entity_t* )ent->data)->origin_s);
            VectorCopy(((client_entity_t* )ent->data)->msg_angles_s[0], ((client_entity_t* )ent->data)->angles_s);
            VectorCopy(((client_entity_t* )ent->data)->msg_origins_s[0], ((client_entity_t* )ent->data)->msg_origins_s[1]);
            VectorCopy(((client_entity_t* )ent->data)->msg_angles_s[0], ((client_entity_t* )ent->data)->msg_angles_s[1]);

        }
#endif
        setEntityForceLink(ent, true);
    }
}
#if DIRECT_SINGLE_PLAYER
extern uint8_t pve[(MAX_EDICTS + 7) / 8];  //potential visible entities
#endif // DIRECT_SINGLE_PLAYER
#define START_DUMMY_UPDATE_EDICT 2      // one after client
void CL_ParseDummyUpdate(void)
{
    model_t *model;
    int modnum;
    entity_t *ent;
    if (!sv.active)
        return;
    if (_g->cls.signon != SIGNONS)
        return;

    edict_t *pedict = sv.edicts;
    for (int i = 0; i < START_DUMMY_UPDATE_EDICT; i++)
    {
        pedict = getNextEdict(pedict);
        if (pedict == END_EDICT)
        {
            FIXME("No enough edicts");
            return;
        }
    }

    for (int i = START_DUMMY_UPDATE_EDICT; i < sv.num_edicts; i++)
    {
        if (pve[i >> 3] & (1 << (i & 7)))
        {
            ent = CL_EntityNum(i);
            ent->entityType = TYPE_EDICT_ENTITY;
            ent->data = pedict;
            modnum = get_qcc_modelindex(pedict);

            model = _g->cl.model_precache[modnum];
            if (model != getEntityModel(ent))
            {
                setEntityModel(ent, model);
                // automatic animation (torches, etc) can be either all together
                // or randomized
                if (model)
                {
#if FLOAT_SYNCBASE
                    if (model->synctype == ST_RAND)
                        ent->syncbase = (float)(rand()&0x7fff) / 0x7fff;
                    else
                        ent->syncbase = 0.0;
        #else
                    if (model->synctype == ST_RAND)
                        ent->syncbase_s = rand() & ((1 << SYNCBASE_BITS) - 1);
                    else
                        ent->syncbase_s = 0;
#endif
                }

            }
            setEntityForceLink(ent, true);
        }
        pedict = getNextEdict(pedict);
        if (pedict == END_EDICT)
            break;
    }
}

/*
 ==================
 CL_ParseBaseline
 ==================
 */
void CL_ParseBaseline(entity_t *ent)
{
    int i;
    getEntityBaseLine(ent)->modelindex = MSG_ReadByte();
    getEntityBaseLine(ent)->frame = MSG_ReadByte();
    getEntityBaseLine(ent)->colormap = MSG_ReadByte();
    getEntityBaseLine(ent)->skin = MSG_ReadByte();
    for (i = 0; i < 3; i++)
    {
#if !ENTITY_HAS_SHORT_COORDS
    ent->baseline.origin[i] = MSG_ReadCoord ();
    ent->baseline.angles[i] = MSG_ReadAngle ();
#else
        getEntityBaseLine(ent)->origin_s[i] = MSG_ReadCoordS();
        getEntityBaseLine(ent)->angles_s[i] = MSG_ReadAngleS();

#endif
    }
}

/*
 ==================
 CL_ParseClientdata

 Server information pertaining to this client only
 ==================
 */
void CL_ParseClientdata(int bits)
{
    int i, j;

    if (bits & SU_VIEWHEIGHT)
        _g->cl.viewheight = MSG_ReadChar();
    else
        _g->cl.viewheight = DEFAULT_VIEWHEIGHT;

    if (bits & SU_IDEALPITCH)
        _g->cl.idealpitch = MSG_ReadChar();
    else
        _g->cl.idealpitch = 0;

    VectorCopy(_g->cl.mvelocity[0], _g->cl.mvelocity[1]);
    for (i = 0; i < 3; i++)
    {
        if (bits & (SU_PUNCH1 << i))
            _g->cl.punchangle[i] = MSG_ReadChar();
        else
            _g->cl.punchangle[i] = 0;
        if (bits & (SU_VELOCITY1 << i))
            _g->cl.mvelocity[0][i] = MSG_ReadChar() * 16;
        else
            _g->cl.mvelocity[0][i] = 0;
    }

// [always sent]  if (bits & SU_ITEMS)
    i = MSG_ReadLong();

    if (_g->cl.items != i)
    { // set flash times
        Sbar_Changed();
        for (j = 0; j < 32; j++)
            if ((i & (1 << j)) && !(_g->cl.items & (1 << j)))
                _g->cl.item_gettime[j] = _g->cl.time;
        _g->cl.items = i;
    }

    _g->cl.onground = (bits & SU_ONGROUND) != 0;
    _g->cl.inwater = (bits & SU_INWATER) != 0;

    if (bits & SU_WEAPONFRAME)
        _g->cl.stats[STAT_WEAPONFRAME] = MSG_ReadByte();
    else
        _g->cl.stats[STAT_WEAPONFRAME] = 0;

    if (bits & SU_ARMOR)
        i = MSG_ReadByte();
    else
        i = 0;
    if (_g->cl.stats[STAT_ARMOR] != i)
    {
        _g->cl.stats[STAT_ARMOR] = i;
        Sbar_Changed();
    }

    if (bits & SU_WEAPON)
        i = MSG_ReadByte();
    else
        i = 0;
    if (_g->cl.stats[STAT_WEAPON] != i)
    {
        _g->cl.stats[STAT_WEAPON] = i;
        Sbar_Changed();
    }

    i = MSG_ReadShort();
    if (_g->cl.stats[STAT_HEALTH] != i)
    {
        _g->cl.stats[STAT_HEALTH] = i;
        Sbar_Changed();
    }

    i = MSG_ReadByte();
    if (_g->cl.stats[STAT_AMMO] != i)
    {
        _g->cl.stats[STAT_AMMO] = i;
        Sbar_Changed();
    }

    for (i = 0; i < 4; i++)
    {
        j = MSG_ReadByte();
        if (_g->cl.stats[STAT_SHELLS + i] != j)
        {
            _g->cl.stats[STAT_SHELLS + i] = j;
            Sbar_Changed();
        }
    }

    i = MSG_ReadByte();

    if (standard_quake)
    {
        if (_g->cl.stats[STAT_ACTIVEWEAPON] != i)
        {
            _g->cl.stats[STAT_ACTIVEWEAPON] = i;
            Sbar_Changed();
        }
    }
    else
    {
        if (_g->cl.stats[STAT_ACTIVEWEAPON] != (1 << i))
        {
            _g->cl.stats[STAT_ACTIVEWEAPON] = (1 << i);
            Sbar_Changed();
        }
    }
}

/*
 =====================
 CL_NewTranslation
 =====================
 */
void CL_NewTranslation(int slot)
{

    if (slot > _g->cl.maxclients)
        Sys_Error("CL_NewTranslation: slot > cl.maxclients");
#if HAS_MULTIPLAYER
  int   i, j;
  int   top, bottom;
  byte  *dest, *source;

  dest = cl.scores[slot].translations;
  source = vid.colormap;
  memcpy (dest, vid.colormap, sizeof(cl.scores[slot].translations));
  top = cl.scores[slot].colors & 0xf0;
  bottom = (cl.scores[slot].colors &15)<<4;
#ifdef GLQUAKE
  R_TranslatePlayerSkin (slot);
#endif

  for (i=0 ; i<VID_GRADES ; i++, dest += 256, source+=256)
  {
    if (top < 128)  // the artists made some backwards ranges.  sigh.
      memcpy (dest + TOP_RANGE, source + top, 16);
    else
      for (j=0 ; j<16 ; j++)
        dest[TOP_RANGE+j] = source[top+15-j];

    if (bottom < 128)
      memcpy (dest + BOTTOM_RANGE, source + bottom, 16);
    else
      for (j=0 ; j<16 ; j++)
        dest[BOTTOM_RANGE+j] = source[bottom+15-j];
  }
  #endif
}

/*
 =====================
 CL_ParseStatic
 =====================
 */
void CL_ParseStatic(void)
{
#if !DIRECT_SINGLE_PLAYER
  entity_t *ent;
  int   i;

  i = cl.num_statics;
  if (i >= MAX_STATIC_ENTITIES)
    Host_Error ("Too many static entities");
  ent = &cl_static_entities[i];
  cl.num_statics++;
  CL_ParseBaseline (ent);

// copy it to the current state
  ent->model = cl.model_precache[ent->baseline.modelindex];
  ent->frame = ent->baseline.frame;
  ent->colormap = vid.colormap;
  ent->skinnum = ent->baseline.skin;
  ent->effects = ent->baseline.effects;

  VectorCopy (ent->baseline.origin, ent->origin);
  VectorCopy (ent->baseline.angles, ent->angles);
  R_AddEfrags (ent);
#elif STATIC_ENTITY_SUPPORT
    if (_g->cls.demoplayback)
    {
        entity_t *ent;
        int i;
        i = _g->cl.num_statics;
        if (i >= MAX_STATIC_ENTITIES)
            Host_Error("Too many static entities");
        printf("ent is %d\r\n", i);
        int entIdx = MAX_EDICTS + ADDITIONAL_CLIENT_ENTITIES - i - 1;
        ent = &cl_entities[entIdx];
        ent->data = &_g->client_entity_data[entIdx];
        ent->entityType = TYPE_CLIENT_ENTITY;
        _g->cl.num_statics++;
        CL_ParseBaseline(ent);
        // copy it to the current state
        // 	ent->frame = ent->baseline.frame;
        setEntityFrame(ent, getEntityBaseLine(ent)->frame);
        //ent->model = cl.model_precache[ent->baseline.modelindex];

        setEntityModel(ent, _g->cl.model_precache[getEntityBaseLine(ent)->modelindex]);
        //ent->colormap = vid.colormap;

        setEntitySkinnum(ent, getEntityBaseLine(ent)->skin);
        //	ent->skinnum = ent->baseline.skin;

        setEntityEffects(ent, getEntityBaseLine(ent)->effects);
        //	ent->effects = ent->baseline.effects;

        for (int j = 0; j < 3; j++)
        {
            setEntityOrigin(ent, j, toFloatCoord(getEntityBaseLine(ent)->origin_s[j]));
            setEntityAngle(ent, j, toFloatAngle(getEntityBaseLine(ent)->angles_s[j]));
        }
        CL_FindTouchedLeafs(ent, _g->cl.worldmodel->brushModelData->nodes, &_g->client_entity_data[entIdx].entLeaves);
        //
    }
    else
    {
        MSG_ReadByte(); //modelindex
        MSG_ReadByte(); //frame
        MSG_ReadByte(); //colormap
        MSG_ReadByte(); //skin
        for (int i = 0; i < 3; i++)
        {
#if !ENTITY_HAS_SHORT_COORDS
            MSG_ReadCoord (); //origin
            MSG_ReadAngle (); //angles
    #else
            MSG_ReadCoordS();
            MSG_ReadAngleS();
#endif
        }
    }
#else
  MSG_ReadByte (); //modelindex
  MSG_ReadByte (); //frame
  MSG_ReadByte(); //colormap
    MSG_ReadByte(); //skin
  for (int i=0 ; i<3 ; i++)
  {
#if !ENTITY_HAS_SHORT_COORDS
        MSG_ReadCoord (); //origin
        MSG_ReadAngle (); //angles
#else
    MSG_ReadCoordS ();
    MSG_ReadAngleS ();
#endif
  }

#endif
}

/*
 ===================
 CL_ParseStaticSound
 ===================
 */
extern sfx_t *known_sfx;
void CL_ParseStaticSound(void)
{
    vec3_t org;
    int sound_num, vol, atten;
    int i;

    for (i = 0; i < 3; i++)
        org[i] = MSG_ReadCoord();
    sound_num = MSG_ReadByte();
    vol = MSG_ReadByte();
    atten = MSG_ReadByte();
    if (_g->cl.sound_precache[sound_num])
        S_StaticSound(_g->cl.sound_precache[sound_num] - &known_sfx[0] + 1, org, vol, atten);
}

#define SHOWNET(x) // if(cl_shownet==2)Con_Printf ("%3i:%s\n", msg_readcount-1, x);

/*
 =====================
 CL_ParseServerMessage
 =====================
 */
void CL_ParseServerMessage(void)
{
    int cmd;
    int i;

//
// if recording demos, copy the message out
//
    if (cl_shownet == 1)
        Con_Printf("%i ", net_message.cursize);
    else if (cl_shownet == 2)
        Con_Printf("------------------\n");

    _g->cl.onground = false;  // unless the server says otherwise
//
// parse the message
//
    MSG_BeginReading();
    char *strbuf = getTextureCacheBuffer(); //[2048];
    if (sv.active)
    {
        _g->cl.num_entities = 0;
    }
    while (1)
    {
        if (msg_badread)
        {
            Host_Error("CL_ParseServerMessage: Bad server message");
        }
#if DEBUG_MSG_READS
        readCanFail = 1;
#endif // DEBUG_MSG_READS
        cmd = MSG_ReadByte();
#if DEBUG_MSG_READS
        readCanFail = 0;
#endif // DEBUG_MSG_READS

        if (cmd == -1)
        {
            SHOWNET("END OF MESSAGE");
            return;   // end of message
        }

        // if the high bit of the command byte is set, it is a fast update
        if (cmd & 128)
        {
            SHOWNET("fast update");
            CL_ParseUpdate(cmd & 127);
            continue;
        }

        SHOWNET(svc_strings[cmd]);

        // other commands
        switch (cmd)
        {
            default:
                Host_Error("CL_ParseServerMessage: Illegible server message\n");
                break;

            case svc_nop:
//      Con_Printf ("svc_nop\n");
                break;

            case svc_time:
                _g->cl.mtime[1] = _g->cl.mtime[0];
                _g->cl.mtime[0] = MSG_ReadFloat();
                break;

            case svc_clientdata:
                i = MSG_ReadShort();
                CL_ParseClientdata(i);
                break;

            case svc_version:
                i = MSG_ReadLong();
                if (i != PROTOCOL_VERSION)
                    Host_Error("CL_ParseServerMessage: Server is protocol %i instead of %i\n", i, PROTOCOL_VERSION);
                break;

            case svc_disconnect:
                Host_EndGame("Server disconnected\n");
                break; // next-hack: added break. The function used "abort server" instead.

            case svc_print:
                Con_Printf("%s", MSG_ReadString(strbuf, 2048));
                break;

            case svc_centerprint:
                SCR_CenterPrint(MSG_ReadString(strbuf, 2048));
                break;

            case svc_stufftext:
                Cbuf_AddText(MSG_ReadString(strbuf, 2048));
                break;

            case svc_damage:
                V_ParseDamage();
                break;

            case svc_serverinfo:
                CL_ParseServerInfo();
                vid.recalc_refdef = true; // leave intermission full screen
                break;

            case svc_setangle:
                for (i = 0; i < 3; i++)
                    _g->cl.viewangles[i] = MSG_ReadAngle();
                break;

            case svc_setview:
                _g->cl.viewentity = MSG_ReadShort();
                break;

            case svc_lightstyle:
            {

                i = MSG_ReadByte();

                char *str = MSG_ReadString(strbuf, 2048);
                int len = Q_strlen(str);
                if (i >= MAX_LIGHTSTYLES)
                {
                    printf("Warning ignoring %d-length light style above MAX_LIGHTSTYLES = %d", len, MAX_LIGHTSTYLES);
                }
                else
                {
                    if (len > MAX_STYLESTRING)
                    {
#if WIN32
                        printf("Len is %d\r\n");
                        FIXME("Len too long");
#endif
                        len = sizeof(MAX_STYLESTRING);
                    }
#if OLD_LIGHTSTYLE
                    Q_strcpy (cl_lightstyle[i].map,  str);
                    #else
                    for (int j = 0; j < len;)
                    {
                        uint8_t tmp, nibble;
                        tmp = str[j] - 'a';
                        if (tmp > 15)
                        {
                            _g->cl_lightstyle[i].map_topBits[j / 8] |= (1 << (j % 8));
                            tmp &= 15;
                        }
                        nibble = tmp;
                        j++; // point to next char
                        tmp = str[j] - 'a';
                        if (tmp > 15)
                        {
                            _g->cl_lightstyle[i].map_topBits[j / 8] |= (1 << (j % 8));
                            tmp &= 15;
                        }
                        nibble |= tmp << 4;
                        _g->cl_lightstyle[i].map_nibbles[j / 2] = nibble;
                        j++;
                    }
#endif
                    _g->cl_lightstyle[i].length = len;
                }
#if WIN32
                printf(">>>>>>>>LIGHT STYLE %i, len %d\r\n", i, len);
#endif
            }

                break;

            case svc_sound:
                CL_ParseStartSoundPacket();
                break;

            case svc_stopsound:
                i = MSG_ReadShort();
                S_StopSound(i >> 3, i & 7);
                break;

            case svc_updatename:
                Sbar_Changed();
                i = MSG_ReadByte();
                if (i >= _g->cl.maxclients)
                    Host_Error("CL_ParseServerMessage: svc_updatename > MAX_SCOREBOARD");
                strcpy(_g->cl.scores[i].name, MSG_ReadString(strbuf, 2048));
                break;

            case svc_updatefrags:
                Sbar_Changed();
                i = MSG_ReadByte();
                if (i >= _g->cl.maxclients)
                    Host_Error("CL_ParseServerMessage: svc_updatefrags > MAX_SCOREBOARD");
                _g->cl.scores[i].frags = MSG_ReadShort();
                break;

            case svc_updatecolors:
                Sbar_Changed();
                i = MSG_ReadByte();
                if (i >= _g->cl.maxclients)
                    Host_Error("CL_ParseServerMessage: svc_updatecolors > MAX_SCOREBOARD");
                _g->cl.scores[i].colors = MSG_ReadByte();
                CL_NewTranslation(i);
                break;

            case svc_particle:
                R_ParseParticleEffect();
                break;

            case svc_spawnbaseline:
                i = MSG_ReadShort();
                if (sv.active)
                {
                    FIXME("PARSE BASELINE ON SV ACTIVE\r\n");
                }
                else
                {
                    CL_EntityNum(i)->data = &_g->client_entity_data[i];
                }
                // must use CL_EntityNum() to force cl.num_entities up
                CL_ParseBaseline(CL_EntityNum(i));
                break;
            case svc_spawnstatic:
                CL_ParseStatic();
                break;
            case svc_temp_entity:
                CL_ParseTEnt();
                break;

            case svc_setpause:
            {
                _g->cl.paused = MSG_ReadByte();

                if (_g->cl.paused)
                {
                    CDAudio_Pause();
#ifdef VID_HandlePause
          VID_HandlePause (true);
#endif
                }
                else
                {
                    CDAudio_Resume();
#ifdef VID_HandlePause
          VID_HandlePause (false);
#endif
                }
            }
                break;

            case svc_signonnum:
                i = MSG_ReadByte();
                if (i <= _g->cls.signon)
                    Host_Error("Received signon %i when at %i", i, _g->cls.signon);
                _g->cls.signon = i;
#if 0
      if (i == 3)
            {
                if (cl_lightstyle)
                {
                    void *buff = cl_lightstyle;
                    cl_lightstyle = storeToInternalFlash(cl_lightstyle, MAX_LIGHTSTYLES * sizeof(*cl_lightstyle));
                    Z_Free(buff);
                }
                else
                {
                    Sys_Error("No CL LIGHTSTYLE RECEIVED");
                }
            }
#endif
                //  FIXME("CHECK LIGHTSTYLES!");
                CL_SignonReply();
                break;

            case svc_killedmonster:
                _g->cl.stats[STAT_MONSTERS]++;
                break;

            case svc_foundsecret:
                _g->cl.stats[STAT_SECRETS]++;
                break;

            case svc_updatestat:
                i = MSG_ReadByte();
                if (i < 0 || i >= MAX_CL_STATS)
                    Sys_Error("svc_updatestat: %i is invalid", i);
                _g->cl.stats[i] = MSG_ReadLong();
                ;
                break;

            case svc_spawnstaticsound:
                CL_ParseStaticSound();
                break;

            case svc_cdtrack:
                _g->cl.cdtrack = MSG_ReadByte();
                _g->cl.looptrack = MSG_ReadByte();
                if ((_g->cls.demoplayback || _g->cls.demorecording) && (_g->cls.forcetrack != -1))
                    CDAudio_Play((byte) _g->cls.forcetrack, true);
                else
                    CDAudio_Play((byte) _g->cl.cdtrack, true);
                break;

            case svc_intermission:
                _g->cl.intermission = 1;
                _g->cl.completed_time = _g->cl.time;
                vid.recalc_refdef = true; // go to full screen
                break;

            case svc_finale:
                _g->cl.intermission = 2;
                _g->cl.completed_time = _g->cl.time;
                vid.recalc_refdef = true; // go to full screen
                SCR_CenterPrint(MSG_ReadString(strbuf, 2048));
                break;

            case svc_cutscene:
                _g->cl.intermission = 3;
                _g->cl.completed_time = _g->cl.time;
                vid.recalc_refdef = true; // go to full screen
                SCR_CenterPrint(MSG_ReadString(strbuf, 2048));
                break;

            case svc_sellscreen:
                Cmd_ExecuteString("help", src_command);
                break;
        }
    }
}

