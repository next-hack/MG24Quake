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
// sv_main.c -- server main program
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
//#pragma GCC optimize("Os") //
#endif
AUX_SECTION server_t		sv;
AUX_SECTION server_static_t	svs;
#if RUNTIME_LOCAL_MODEL_STRINGS
char	localmodels[MAX_MODELS][5];			// inline model names for precache.
#else
const char localmodels[MAX_MODELS][5] =
{
    "*0", "*1", "*2", "*3", "*4", "*5", "*6", "*7",
    "*8", "*9", "*10", "*11", "*12", "*13", "*14", "*15", "*16", "*17", "*18", "*19", "*20", "*21", "*22", "*23", "*24", "*25", "*26", "*27", "*28", "*29", "*30", "*31", "*32", "*33", "*34", "*35", "*36", "*37", "*38", "*39",
    "*40", "*41", "*42", "*43", "*44", "*45", "*46", "*47", "*48", "*49", "*50", "*51", "*52", "*53", "*54", "*55", "*56", "*57", "*58", "*59", "*60", "*61", "*62", "*63", "*64", "*65", "*66", "*67", "*68", "*69", "*70", "*71",
    "*72", "*73", "*74", "*75", "*76", "*77", "*78", "*79", "*80", "*81", "*82", "*83", "*84", "*85", "*86", "*87", "*88", "*89", "*90", "*91", "*92", "*93", "*94", "*95", "*96", "*97", "*98", "*99", "*100", "*101", "*102", "*103",
    "*104", "*105", "*106", "*107", "*108", "*109", "*110", "*111", "*112", "*113", "*114", "*115", "*116", "*117", "*118", "*119", "*120", "*121", "*122", "*123", "*124", "*125", "*126", "*127", "*128", "*129", "*130", "*131", "*132", "*133", "*134", "*135",
    "*136", "*137", "*138", "*139", "*140", "*141", "*142", "*143", "*144", "*145", "*146", "*147", "*148", "*149", "*150", "*151", "*152", "*153", "*154", "*155", "*156", "*157", "*158", "*159", "*160", "*161",
};
#endif
byte *fatpvs = NULL;
byte *decompressed = NULL;

//============================================================================

/*
 ===============
 SV_Init
 ===============
 */

void SV_Init(void)
{
#if USE_ORIGINAL_CVAR
	extern	cvar_t	sv_maxvelocity;
	extern	cvar_t	sv_gravity;
	extern	cvar_t	sv_nostep;
	extern	cvar_t	sv_friction;
	extern	cvar_t	sv_edgefriction;
	extern	cvar_t	sv_stopspeed;
	extern	cvar_t	sv_maxspeed;
	extern	cvar_t	sv_accelerate;
	extern	cvar_t	sv_idealpitchscale;
	extern	cvar_t	sv_aim;
#endif
    if (fatpvs == NULL)
        fatpvs = allocFromTempBuffer(MAX_MAP_LEAFS / 8, NULL);
    if (decompressed == NULL)
        decompressed = allocFromTempBuffer(MAX_MAP_LEAFS / 8, NULL);
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&sv_maxvelocity);
	Cvar_RegisterVariable (&sv_gravity);
	Cvar_RegisterVariable (&sv_friction);
	Cvar_RegisterVariable (&sv_edgefriction);
	Cvar_RegisterVariable (&sv_stopspeed);
	Cvar_RegisterVariable (&sv_maxspeed);
	Cvar_RegisterVariable (&sv_accelerate);
	Cvar_RegisterVariable (&sv_idealpitchscale);
	Cvar_RegisterVariable (&sv_aim);
	Cvar_RegisterVariable (&sv_nostep);
#endif
#if RUNTIME_LOCAL_MODEL_STRINGS
	for (int i = 0 ; i < MAX_MODELS ; i++)
		sprintf (localmodels[i], "*%i", i);
#endif
}

/*
 =============================================================================

 EVENT MESSAGES

 =============================================================================
 */

/*
 ==================
 SV_StartParticle

 Make sure the event gets sent to all clients
 ==================
 */
void SV_StartParticle(vec3_t org, vec3_t dir, int color, int count)
{
    int i, v;

    if (sv.datagram.cursize > MAX_DATAGRAM - 16)
        return;
    MSG_WriteByte(&sv.datagram, svc_particle);
    MSG_WriteCoord(&sv.datagram, org[0]);
    MSG_WriteCoord(&sv.datagram, org[1]);
    MSG_WriteCoord(&sv.datagram, org[2]);
    for (i = 0; i < 3; i++)
    {
        v = dir[i] * 16;
        if (v > 127)
            v = 127;
        else if (v < -128)
            v = -128;
        MSG_WriteChar(&sv.datagram, v);
    }
    MSG_WriteByte(&sv.datagram, count);
    MSG_WriteByte(&sv.datagram, color);
}

/*
 ==================
 SV_StartSound

 Each entity can have eight independant sound sources, like voice,
 weapon, feet, etc.

 Channel 0 is an auto-allocate channel, the others override anything
 allready running on that entity/channel pair.

 An attenuation of 0 will play full volume everywhere in the level.
 Larger attenuations will drop off.  (max 4 attenuation)

 ==================
 */
void SV_StartSound(edict_t *entity, int channel, const char *sample, int volume, float attenuation)
{
    int sound_num;
    int field_mask;
    int i;
    int ent;

    if (volume < 0 || volume > 255)
        Sys_Error("SV_StartSound: volume = %i", volume);

    if (attenuation < 0 || attenuation > 4)
        Sys_Error("SV_StartSound: attenuation = %f", attenuation);

    if (channel < 0 || channel > 7)
        Sys_Error("SV_StartSound: channel = %i", channel);

    if (sv.datagram.cursize > MAX_DATAGRAM - 16)
        return;

// find precache number for sound
    for (sound_num = 1; sound_num < MAX_SOUNDS && get_sv_sound_precache(sound_num); sound_num++)
        if (!strcmp(sample, get_sv_sound_precache(sound_num)))
            break;

    if (sound_num == MAX_SOUNDS || !get_sv_sound_precache(sound_num))
    {
// TODO: FIXME this one!
//        Con_Printf ("SV_StartSound: %s not precached\n", sample);
        return;
    }
#if !EDICT_LINKED_LIST
	ent = NUM_FOR_EDICT(entity);
#else
    ent = EDICT_TO_PROG(entity);
#endif
    channel = (ent << 3) | channel;

    field_mask = 0;
    if (volume != DEFAULT_SOUND_PACKET_VOLUME)
        field_mask |= SND_VOLUME;
    if (attenuation != DEFAULT_SOUND_PACKET_ATTENUATION)
        field_mask |= SND_ATTENUATION;

// directed messages go only to the entity the are targeted on
    MSG_WriteByte(&sv.datagram, svc_sound);
    MSG_WriteByte(&sv.datagram, field_mask);
    if (field_mask & SND_VOLUME)
        MSG_WriteByte(&sv.datagram, volume);
    if (field_mask & SND_ATTENUATION)
        MSG_WriteByte(&sv.datagram, attenuation * 64);
    MSG_WriteShort(&sv.datagram, channel);
    MSG_WriteByte(&sv.datagram, sound_num);
#if USE_OLD_ABS_CALLS
    for (i=0; i<3; i++)
    MSG_WriteCoord (&sv.datagram, VEC(get_qcc_origin(entity))[i]+0.5*(VEC(get_qcc_mins(entity))[i]+VEC(get_qcc_maxs(entity))[i]));
#else
    vector entOrigin = get_qcc_origin(entity);
    vector entMins = get_qcc_mins(entity);
    vector entMaxs = get_qcc_maxs(entity);
    for (i = 0; i < 3; i++)
        MSG_WriteCoord(&sv.datagram, entOrigin.v[i] + 0.5f * (entMins.v[i] + entMaxs.v[i]));
#endif
}

/*
 ==============================================================================

 CLIENT SPAWNING

 ==============================================================================
 */

/*
 ================
 SV_SendServerinfo

 Sends the first message from the server to a connected client.
 This will be sent on the initial connection and upon each server load.
 ================
 */
void SV_SendServerinfo(client_t *client)
{
    //      printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    const char **s;
    char message[2048];

    MSG_WriteByte(&client->message, svc_print);
    sprintf(message, "%c\nVERSION %d.%02d SERVER (%i CRC)", 2, (int) VERSION, ((int) (VERSION * 100)) % 100, pr_crc);
    MSG_WriteString(&client->message, message);

    MSG_WriteByte(&client->message, svc_serverinfo);
    MSG_WriteLong(&client->message, PROTOCOL_VERSION);
    MSG_WriteByte(&client->message, svs.maxclients);

    if (!coop && deathmatch)
        MSG_WriteByte(&client->message, GAME_DEATHMATCH);
    else
        MSG_WriteByte(&client->message, GAME_COOP);
#if USE_PROGSDAT
    sprintf (message, pr_strings+sv.get_qcc_message(edicts));
#else
    sprintf(message, getStringFromIndex(get_qcc_message(sv.edicts)));
#if WIN32
    printf("Message is %s\r\n", message);
    FIXME("");
#endif
#endif
    MSG_WriteString(&client->message, message);

    for (s = sv.model_precache + 1; *s; s++)
        MSG_WriteString(&client->message, *s);
    MSG_WriteByte(&client->message, 0);

    //
    for (int i = 1; get_sv_sound_precache(i); i++)
//	for (s = sv.sound_precache+1 ; *s ; s++)
        MSG_WriteString(&client->message, get_sv_sound_precache(i));
    MSG_WriteByte(&client->message, 0);

// send music
    MSG_WriteByte(&client->message, svc_cdtrack);
    MSG_WriteByte(&client->message, get_qcc_sounds(sv.edicts));
    MSG_WriteByte(&client->message, get_qcc_sounds(sv.edicts));

// set view
    MSG_WriteByte(&client->message, svc_setview);
    MSG_WriteShort(&client->message, NUM_FOR_EDICT((edict_t*) client->edict));

    MSG_WriteByte(&client->message, svc_signonnum);
    MSG_WriteByte(&client->message, 1);

    client->sendsignon = true;
    client->spawned = false;		// need prespawn, spawn, etc
}

/*
 ================
 SV_ConnectClient

 Initializes a client_t for a new net connection.  This will only be called
 once for a player each game, not once for each level change.
 ================
 */
void SV_ConnectClient(int clientnum)
{
    static		//printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");
    edict_t *ent;
    client_t *client;
    int edictnum;
    struct qsocket_s *netconnection;
    float spawn_parms[NUM_SPAWN_PARMS];

    client = svs.clients + clientnum;
#if USING_REALLY_NETWORK
	Con_DPrintf ("Client %s connected\n", client->netconnection->address);
#else
    Con_DPrintf("Client %s connected\n", "localhost");
#endif
    edictnum = clientnum + 1;
#if EDICT_LINKED_LIST
    ent = sv.edicts;
    for (int i = 0; i < edictnum; i++)
    {
        ent = getNextEdict(ent);
    }
#else
	ent = EDICT_NUM(edictnum);
#endif // EDICT_LINKED_LIST

// set up the client_t
    netconnection = client->netconnection;

    if (sv.loadgame)
        memcpy(spawn_parms, client->spawn_parms, sizeof(spawn_parms));
    memset(client, 0, sizeof(*client));
    client->netconnection = netconnection;

    strcpy(client->name, "unconnected");
    client->active = true;
    client->spawned = false;
    client->edict = (player_edict_t*) ent;
#if USE_GP_BUFFER_FOR_CLIENT_HOST_DATA
    static void *messageDataBuffer[MAX_CLIENTS] =
    { NULL
    };
    if (messageDataBuffer[clientnum] == NULL) // next-hack: fix for reusing the same buffer
    {
        int maxsize = 0;
        messageDataBuffer[clientnum] = client->message.data = allocFromTempBuffer(MAX_MSGLEN, &maxsize);
        client->message.maxsize = maxsize;
    }
    else
    {
        client->message.data = messageDataBuffer[clientnum];
        client->message.maxsize = MAX_MSGLEN;
    }
#else
	client->message.data = client->msgbuf;
	client->message.maxsize = sizeof(client->msgbuf);
#endif // USE_GP_BUFFER_FOR_CLIENT_HOST_DATA
    client->message.allowoverflow = true;		// we can catch it

#ifdef IDGODS
	client->privileged = IsID(&client->netconnection->addr);
#else
    client->privileged = false;
#endif

    if (sv.loadgame)
        memcpy(client->spawn_parms, spawn_parms, sizeof(spawn_parms));
    else
    {
        // call the progs to get default spawn parms for the new client
#if USE_PROGSDAT
		PR_ExecuteProgram (pr_global_struct->SetNewParms);
		for (i=0 ; i<NUM_SPAWN_PARMS ; i++)
			client->spawn_parms[i] = (&pr_global_struct->parm1)[i];
#else
        qcc_SetNewParms();
        client->spawn_parms[0] = progs.qcc_parm1;
        client->spawn_parms[1] = progs.qcc_parm2;
        client->spawn_parms[2] = progs.qcc_parm3;
        client->spawn_parms[3] = progs.qcc_parm4;
        client->spawn_parms[4] = progs.qcc_parm5;
        client->spawn_parms[5] = progs.qcc_parm6;
        client->spawn_parms[6] = progs.qcc_parm7;
        client->spawn_parms[7] = progs.qcc_parm8;
        client->spawn_parms[8] = progs.qcc_parm9;
        client->spawn_parms[9] = progs.qcc_parm10;
        client->spawn_parms[10] = progs.qcc_parm11;
        client->spawn_parms[11] = progs.qcc_parm12;
        client->spawn_parms[12] = progs.qcc_parm13;
        client->spawn_parms[13] = progs.qcc_parm14;
        client->spawn_parms[14] = progs.qcc_parm15;
        client->spawn_parms[15] = progs.qcc_parm16;
#endif

    }

    SV_SendServerinfo(client);

}

/*
 ===================
 SV_CheckForNewClients

 ===================
 */
void SV_CheckForNewClients(void)
{

    struct qsocket_s *ret;
    int i;

//
// check for new connections
//
    while (1)
    {
        ret = NET_CheckNewConnections();
        if (!ret)
            break;

        //
        // init a new client structure
        //
        for (i = 0; i < svs.maxclients; i++)
            if (!svs.clients[i].active)
                break;
        if (i == svs.maxclients)
            Sys_Error("Host_CheckForNewClients: no free clients");

        svs.clients[i].netconnection = ret;
        SV_ConnectClient(i);

        net_activeconnections++;
    }

}

/*
 ===============================================================================

 FRAME UPDATES

 ===============================================================================
 */

/*
 ==================
 SV_ClearDatagram

 ==================
 */
void SV_ClearDatagram(void)
{
    SZ_Clear(&sv.datagram);
}

/*
 =============================================================================

 The PVS must include a small area around the client to allow head bobbing
 or other small motion on the client side.  Otherwise, a bob might cause an
 entity that should be visible to not show up, especially when the bob
 crosses a waterline.

 =============================================================================
 */

int fatbytes;

void SV_AddToFatPVS(vec3_t org, mnode_t *node)
{
    int i;
    byte *pvs;
    mplane_t *plane;
    float d;

    while (1)
    {
        // if this is a leaf, accumulate the pvs bits
        if (node->contents < 0)
        {
            if (node->contents != CONTENTS_SOLID)
            {
                pvs = Mod_LeafPVS((mleaf_t*) node, sv.worldmodel);
                for (i = 0; i < fatbytes; i++)
                    fatpvs[i] |= pvs[i];
            }
            return;
        }
#if NODE_HAS_PLANE_POINTER
        plane = node->plane;
#else
        plane = Mod_GetNodePlane(node, sv.worldmodel);
#endif
        d = DotProduct (org, plane->normal) - getPlaneDist(plane);
#if NODE_HAS_CHILDREN_POINTERS
		if (d > 8)
			node = node->children[0];
		else if (d < -8)
			node = node->children[1];
		else
		{	// go down both
			SV_AddToFatPVS (org, node->children[0]);
			node = node->children[1];
		}
#else
        if (d > 8)
            node = Mod_GetChildNode(node, 0, sv.worldmodel);
        else if (d < -8)
            node = Mod_GetChildNode(node, 1, sv.worldmodel);
        else
        {	// go down both
            SV_AddToFatPVS(org, Mod_GetChildNode(node, 0, sv.worldmodel));
            node = Mod_GetChildNode(node, 1, sv.worldmodel);
        }
#endif
    }
}

/*
 =============
 SV_FatPVS

 Calculates a PVS that is the inclusive or of all leafs within 8 pixels of the
 given point.
 =============
 */
byte* SV_FatPVS(vec3_t org)
{
#if !SEPARATE_BRUSH_MODEL_DATA
	fatbytes = (sv.worldmodel->numleafs+31)>>3;
	Q_memset (fatpvs, 0, fatbytes);
	SV_AddToFatPVS (org, sv.worldmodel->nodes);

#else
    fatbytes = (sv.worldmodel->brushModelData->numleafs + 31) >> 3;
    Q_memset(fatpvs, 0, fatbytes);
    SV_AddToFatPVS(org, sv.worldmodel->brushModelData->nodes);

#endif

    return fatpvs;
}

//=============================================================================

/*
 =============
 SV_WriteEntitiesToClient

 =============
 */
#if DIRECT_SINGLE_PLAYER
//uint8_t pve[(MAX_EDICTS + 7) / 8];  //potential visible entities
uint8_t *pve = &textureCacheBuffer[ sizeof(textureCacheBuffer) - 4* ((MAX_EDICTS + 31) / 32)];
#endif // DIRECT_SINGLE_PLAYER
#if DO_FIND_TOUCHED_LEAVES_JIT == 2
extern short		global_leafnums[MAX_ENT_LEAFS];
extern uint8_t     global_num_leafs;
#endif
void SV_WriteEntitiesToClient(edict_t *clent, sizebuf_t *msg)
{
    int e, i;
    int bits;
    byte *pvs;
    vec3_t org;
    edict_t *ent;
    fastMemclear32(pve, 4* ((MAX_EDICTS + 31) / 32));
    pve[0] = 1;
// find the client's PVS
    VectorAdd(VEC(get_qcc_origin(clent)), VEC(get_qcc_view_ofs(clent)), org);
    pvs = SV_FatPVS(org);

// send over all entities (excpet the client) that touch the pvs
    ent = NEXT_EDICT(sv.edicts);
    for (e = 1; e < sv.num_edicts; e++, ent = NEXT_EDICT(ent))
    {

// ignore if not touching a PV leaf
        if (ent != clent)	// clent is ALWAYS sent
        {
// ignore ents without visible models
#if USE_PROGSDAT
			if (!get_qcc_modelindex(ent) || !pr_strings[get_qcc_model(ent)])
				continue;
#else
            if (!get_qcc_modelindex(ent) || !get_qcc_model(ent))
                continue;
#endif
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
            entLeaves_t *el;
            el = get_entLeaves(ent);    // guaranteed not null because get_qcc_modelindex was not 0.
            if (el->needs_relink && qcc_classname2type[ent->qcc_classname] != static_light_edict_idx)
            {
                el->needs_relink = 0;

                // link to PVS leafs
                el->num_leaves = 0; // reset num of leaves
//                if (get_qcc_modelindex(ent))  el not null only if edict has modelindex
                SV_FindTouchedLeafs(ent, sv.worldmodel->brushModelData->nodes, el);
                //printf("%d relinked. Num leaves after relinkg %d\r\n", e, el->num_leaves);
                //FIXME("Needs relink\r\n");

            }
#elif DO_FIND_TOUCHED_LEAVES_JIT == 1
            if (ent->needs_relink)
            {
                ent->needs_relink = 0;

                // link to PVS leafs
                ent->num_leafs = 0;
                if (get_qcc_modelindex(ent))
                    SV_FindTouchedLeafs (ent, sv.worldmodel->nodes);
            }
#elif DO_FIND_TOUCHED_LEAVES_JIT == 2
            global_num_leafs = 0;
            if (get_qcc_modelindex(ent))
#if !SEPARATE_BRUSH_MODEL_DATA
                SV_FindTouchedLeafs (ent, sv.worldmodel->nodes);
#else
                SV_FindTouchedLeafs (ent, sv.worldmodel->brushModelData->nodes);
#endif
			for (i=0 ; i < global_num_leafs ; i++)
				if (pvs[global_leafnums[i] >> 3] & (1 << (global_leafnums[i]&7) ))
					break;

			if (i == global_num_leafs)
				continue;		// not visible

#endif

#if DO_FIND_TOUCHED_LEAVES_JIT <= 1
			for (i=0 ; i < ent->num_leafs ; i++)
				if (pvs[ent->leafnums[i] >> 3] & (1 << (ent->leafnums[i]&7) ))
					break;

			if (i == ent->num_leafs)
				continue;		// not visible
#elif DO_FIND_TOUCHED_LEAVES_JIT == 3

            for (i = 0; i < el->num_leaves; i++)
                if (pvs[el->leafnums[i] >> 3] & (1 << (el->leafnums[i] & 7)))
                    break;

            if (i == el->num_leaves)
            {
                //    printf("e %d Not visible\r\n", e);
                continue;// not visible

            }
            //  printf("e %d IS visible\r\n", e);
#endif
        }
#if DIRECT_SINGLE_PLAYER
        pve[e >> 3] |= 1 << (e & 7);
        if (ent != clent)
            continue;
//        printf("Sending data for Ent %i\r\n", e);
#endif
#if !DIRECT_SINGLE_PLAYER
		if (msg->maxsize - msg->cursize < 16)
		{
			Con_Printf ("packet overflow\n");
			return;
		}
// send an update
		bits = 0;

		for (i=0 ; i<3 ; i++)
		{
#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
			miss = VEC(get_qcc_origin(ent))[i] - ent->baseline.origin[i];
			if ( miss < -0.1 || miss > 0.1 )
#endif
				bits |= U_ORIGIN1<<i;
		}

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if ( VEC(get_qcc_angles(ent))[0] != ent->baseline.angles[0] )
#endif
			bits |= U_ANGLE1;

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if ( VEC(get_qcc_angles(ent))[1] != ent->baseline.angles[1] )
#endif
			bits |= U_ANGLE2;

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if ( VEC(get_qcc_angles(ent))[2] != ent->baseline.angles[2] )
#endif
			bits |= U_ANGLE3;


		if (get_qcc_movetype(ent) == MOVETYPE_STEP)
			bits |= U_NOLERP;	// don't mess up the step animation

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if (ent->baseline.colormap != get_qcc_colormap(ent))
#endif
			bits |= U_COLORMAP;

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if (ent->baseline.skin != get_qcc_skin(ent))
#endif
#if !DIRECT_SINGLE_PLAYER
			bits |= U_SKIN;
#endif

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if (ent->baseline.frame != get_qcc_frame(ent))
#endif
#if !DIRECT_SINGLE_PLAYER
			bits |= U_FRAME;
#endif

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if (ent->baseline.effects != get_qcc_effects(ent))
#endif
#if !DIRECT_SINGLE_PLAYER
			bits |= U_EFFECTS;
#endif

#if OLD_SERVER_BASELINE && !DIRECT_SINGLE_PLAYER
		if (ent->baseline.modelindex != get_qcc_modelindex(ent))
#endif
        bits |= U_MODEL;
		if (e >= 256)
			bits |= U_LONGENTITY;

		if (bits >= 256)
			bits |= U_MOREBITS;

	//
	// write the message
	//
		MSG_WriteByte (msg,bits | U_SIGNAL);

		if (bits & U_MOREBITS)
			MSG_WriteByte (msg, bits>>8);
		if (bits & U_LONGENTITY)
			MSG_WriteShort (msg,e);
		else
			MSG_WriteByte (msg,e);

		if (bits & U_MODEL)
			MSG_WriteByte (msg,	get_qcc_modelindex(ent));
		if (bits & U_FRAME)
			MSG_WriteByte (msg, get_qcc_frame(ent));
		if (bits & U_COLORMAP)
			MSG_WriteByte (msg, get_qcc_colormap(ent));
		if (bits & U_SKIN)
			MSG_WriteByte (msg, get_qcc_skin(ent));
		if (bits & U_EFFECTS)
			MSG_WriteByte (msg, get_qcc_effects(ent));
		if (bits & U_ORIGIN1)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[0]);
		if (bits & U_ANGLE1)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[0]);
		if (bits & U_ORIGIN2)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[1]);
		if (bits & U_ANGLE2)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[1]);
		if (bits & U_ORIGIN3)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[2]);
		if (bits & U_ANGLE3)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[2]);
#elif !DONT_SEND_DATA_LOCALLY
        bits = U_MODEL;
        if (e >= 256)
            bits |= U_LONGENTITY;

        if (bits >= 256)
            bits |= U_MOREBITS;

        //
        // write the message
        //
        MSG_WriteByte(msg, bits | U_SIGNAL);

        if (bits & U_MOREBITS)
            MSG_WriteByte(msg, bits >> 8);
        if (bits & U_LONGENTITY)
            MSG_WriteShort(msg, e);
        else
            MSG_WriteByte(msg, e);

        if (bits & U_MODEL)
            MSG_WriteByte(msg, get_qcc_modelindex(ent));
        if (bits & U_FRAME)
            MSG_WriteByte(msg, get_qcc_frame(ent));
        if (bits & U_COLORMAP)
            MSG_WriteByte(msg, get_qcc_colormap(ent));
        if (bits & U_SKIN)
            MSG_WriteByte(msg, get_qcc_skin(ent));
        if (bits & U_EFFECTS)
            MSG_WriteByte(msg, get_qcc_effects(ent));
        if (bits & U_ORIGIN1)
            MSG_WriteCoord(msg, VEC(get_qcc_origin(ent))[0]);
        if (bits & U_ANGLE1)
            MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[0]);
        if (bits & U_ORIGIN2)
            MSG_WriteCoord(msg, VEC(get_qcc_origin(ent))[1]);
        if (bits & U_ANGLE2)
            MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[1]);
        if (bits & U_ORIGIN3)
            MSG_WriteCoord(msg, VEC(get_qcc_origin(ent))[2]);
        if (bits & U_ANGLE3)
            MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[2]);

#endif

    }
#if DIRECT_SINGLE_PLAYER && DONT_SEND_DATA_LOCALLY
ent = NEXT_EDICT(sv.edicts);
{
        bits = U_MODEL;
		if (e >= 256)
			bits |= U_LONGENTITY;

		if (bits >= 256)
			bits |= U_MOREBITS;

	//
	// write the message
	//
		MSG_WriteByte (msg,bits | U_SIGNAL);

		if (bits & U_MOREBITS)
			MSG_WriteByte (msg, bits>>8);
		if (bits & U_LONGENTITY)
			MSG_WriteShort (msg,e);
		else
			MSG_WriteByte (msg,e);

		if (bits & U_MODEL)
			MSG_WriteByte (msg,	get_qcc_modelindex(ent));
		if (bits & U_FRAME)
			MSG_WriteByte (msg, get_qcc_frame(ent));
		if (bits & U_COLORMAP)
			MSG_WriteByte (msg, get_qcc_colormap(ent));
		if (bits & U_SKIN)
			MSG_WriteByte (msg, get_qcc_skin(ent));
		if (bits & U_EFFECTS)
			MSG_WriteByte (msg, get_qcc_effects(ent));
		if (bits & U_ORIGIN1)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[0]);
		if (bits & U_ANGLE1)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[0]);
		if (bits & U_ORIGIN2)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[1]);
		if (bits & U_ANGLE2)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[1]);
		if (bits & U_ORIGIN3)
			MSG_WriteCoord (msg, VEC(get_qcc_origin(ent))[2]);
		if (bits & U_ANGLE3)
			MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[2]);
}

#endif // DIRECT_SINGLE_PLAYER
}

/*
 =============
 SV_CleanupEnts

 =============
 */
void SV_CleanupEnts(void)
{
    int e;
    edict_t *ent;
    if (!sv.active)
    {
        return;
    }
    ent = NEXT_EDICT(sv.edicts);
    for (e = 1; e < sv.num_edicts; e++, ent = NEXT_EDICT(ent))
    {
        set_qcc_effects(ent, (int) get_qcc_effects(ent) & ~EF_MUZZLEFLASH);
    }

}

/*
 ==================
 SV_WriteClientdataToMessage

 ==================
 */
void SV_WriteClientdataToMessage(edict_t *ent, sizebuf_t *msg)
{
    int bits;
    int i;
    edict_t *other;
    int items;

//
// send a damage message
//
    if (get_qcc_dmg_take(ent) || get_qcc_dmg_save(ent))
    {
        other = PROG_TO_EDICT(get_qcc_dmg_inflictor(ent));
        MSG_WriteByte(msg, svc_damage);
        MSG_WriteByte(msg, get_qcc_dmg_save(ent));
        MSG_WriteByte(msg, get_qcc_dmg_take(ent));
        for (i = 0; i < 3; i++)
            MSG_WriteCoord(msg, VEC(get_qcc_origin(other))[i] + 0.5 * (VEC(get_qcc_mins(other))[i] + VEC(get_qcc_maxs(other))[i]));

        set_qcc_dmg_take(ent, 0);
        set_qcc_dmg_save(ent, 0);
    }

//
// send the current viewpos offset from the view entity
//
    SV_SetIdealPitch();		// how much to look up / down ideally

// a fixangle might get lost in a dropped packet.  Oh well.
    if (get_qcc_fixangle(ent))
    {
        MSG_WriteByte(msg, svc_setangle);
        for (i = 0; i < 3; i++)
            MSG_WriteAngle(msg, VEC(get_qcc_angles(ent))[i]);
        set_qcc_fixangle(ent, 0);
    }

    bits = 0;

    if (VEC(get_qcc_view_ofs(ent))[2] != DEFAULT_VIEWHEIGHT)
        bits |= SU_VIEWHEIGHT;

    if (get_qcc_idealpitch(ent))
        bits |= SU_IDEALPITCH;

// stuff the sigil bits into the high bits of items for sbar, or else
// mix in items2
#ifdef QUAKE2
	items = (int)ent->v.items | ((int)ent->v.items2 << 23);
#else
#if USE_PROGSDAT
	val = GetEdictFieldValue(ent, "items2");
	if (val)
		items = (int)get_qcc_items(ent) | ((int)val->_float << 23);
	else
		items = (int)get_qcc_items(ent) | ((int)pr_global_struct->serverflags << 28);
#else
    items = (int) get_qcc_items(ent) | ((int) progs.qcc_serverflags << 28);
#endif
#endif

    bits |= SU_ITEMS;

    if ((int) get_qcc_flags(ent) & FL_ONGROUND)
        bits |= SU_ONGROUND;

    if (get_qcc_waterlevel(ent) >= 2)
        bits |= SU_INWATER;

    for (i = 0; i < 3; i++)
    {
        if (VEC(get_qcc_punchangle(ent))[i])
            bits |= (SU_PUNCH1 << i);
        if (VEC(get_qcc_velocity(ent))[i])
            bits |= (SU_VELOCITY1 << i);
    }

    if (get_qcc_weaponframe(ent))
        bits |= SU_WEAPONFRAME;

    if (get_qcc_armorvalue(ent))
        bits |= SU_ARMOR;

//	if (ent->v.weapon)
    bits |= SU_WEAPON;

// send the data

    MSG_WriteByte(msg, svc_clientdata);
    MSG_WriteShort(msg, bits);

    if (bits & SU_VIEWHEIGHT)
        MSG_WriteChar(msg, VEC(get_qcc_view_ofs(ent))[2]);

    if (bits & SU_IDEALPITCH)
        MSG_WriteChar(msg, get_qcc_idealpitch(ent));

    for (i = 0; i < 3; i++)
    {
        if (bits & (SU_PUNCH1 << i))
            MSG_WriteChar(msg, VEC(get_qcc_punchangle(ent))[i]);
        if (bits & (SU_VELOCITY1 << i))
            MSG_WriteChar(msg, VEC(get_qcc_velocity(ent))[i] / 16);
    }

// [always sent]	if (bits & SU_ITEMS)
    MSG_WriteLong(msg, items);

    if (bits & SU_WEAPONFRAME)
        MSG_WriteByte(msg, get_qcc_weaponframe(ent));
    if (bits & SU_ARMOR)
        MSG_WriteByte(msg, get_qcc_armorvalue(ent));
    if (bits & SU_WEAPON)
#if USE_PROGSDAT
		MSG_WriteByte (msg, SV_ModelIndex(pr_strings+get_qcc_weaponmodel(ent)));
    #else
        MSG_WriteByte(msg, SV_ModelIndex(getStringFromIndex(get_qcc_weaponmodel(ent))));
#endif
    MSG_WriteShort(msg, get_qcc_health(ent));
    MSG_WriteByte(msg, get_qcc_currentammo(ent));
    MSG_WriteByte(msg, get_qcc_ammo_shells(ent));
    MSG_WriteByte(msg, get_qcc_ammo_nails(ent));
    MSG_WriteByte(msg, get_qcc_ammo_rockets(ent));
    MSG_WriteByte(msg, get_qcc_ammo_cells(ent));

    if (standard_quake)
    {
        MSG_WriteByte(msg, get_qcc_weapon(ent));
    }
    else
    {
        for (i = 0; i < 32; i++)
        {
            if (((int) get_qcc_weapon(ent)) & (1 << i))
            {
                MSG_WriteByte(msg, i);
                break;
            }
        }
    }
}

/*
 =======================
 SV_SendClientDatagram
 =======================
 */
qboolean SV_SendClientDatagram(client_t *client)
{
    //printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    byte buf[MAX_DATAGRAM];
    sizebuf_t msg;

    msg.data = buf;
    msg.maxsize = sizeof(buf);
    msg.cursize = 0;

    MSG_WriteByte(&msg, svc_time);
    MSG_WriteFloat(&msg, sv.time);

// add the client specific data to the datagram
    SV_WriteClientdataToMessage((edict_t*) client->edict, &msg);

    SV_WriteEntitiesToClient((edict_t*) client->edict, &msg);

// copy the server datagram if there is space
    if (msg.cursize + sv.datagram.cursize < msg.maxsize)
        SZ_Write(&msg, sv.datagram.data, sv.datagram.cursize);

// send the datagram
    if (NET_SendUnreliableMessage(client->netconnection, &msg) == -1)
    {
        SV_DropClient(true);		// if the message couldn't send, kick off
        return false;
    }

    return true;
}

/*
 =======================
 SV_UpdateToReliableMessages
 =======================
 */
void SV_UpdateToReliableMessages(void)
{
    //      printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");
    int i, j;
    client_t *client;

// check for changes to be sent over the reliable streams
    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
    {
        if (host_client->old_frags != get_qcc_frags((edict_t*) host_client->edict))
        {
            for (j = 0, client = svs.clients; j < svs.maxclients; j++, client++)
            {
                if (!client->active)
                    continue;
                MSG_WriteByte(&client->message, svc_updatefrags);
                MSG_WriteByte(&client->message, i);
                MSG_WriteShort(&client->message, get_qcc_frags((edict_t*) host_client->edict));
            }

            host_client->old_frags = get_qcc_frags((edict_t*) host_client->edict);
        }
    }

    for (j = 0, client = svs.clients; j < svs.maxclients; j++, client++)
    {
        if (!client->active)
            continue;
        SZ_Write(&client->message, sv.reliable_datagram.data, sv.reliable_datagram.cursize);
    }

    SZ_Clear(&sv.reliable_datagram);

}

/*
 =======================
 SV_SendNop

 Send a nop message without trashing or sending the accumulated client
 message buffer
 =======================
 */
void SV_SendNop(client_t *client)
{
    // printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    sizebuf_t msg;
    byte buf[4];

    msg.data = buf;
    msg.maxsize = sizeof(buf);
    msg.cursize = 0;

    MSG_WriteChar(&msg, svc_nop);

    if (NET_SendUnreliableMessage(client->netconnection, &msg) == -1)
        SV_DropClient(true);	// if the message couldn't send, kick off
    client->last_message = realtime;

}

/*
 =======================
 SV_SendClientMessages
 =======================
 */
void SV_SendClientMessages(void)
{

    int i;

// update frags, names, etc
    SV_UpdateToReliableMessages();

// build individual updates
    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
    {
        if (!host_client->active)
            continue;

        if (host_client->spawned)
        {
            if (!SV_SendClientDatagram(host_client))
                continue;
        }
        else
        {
            // the player isn't totally in the game yet
            // send small keepalive messages if too much time has passed
            // send a full message when the next signon stage has been requested
            // some other message data (name changes, etc) may accumulate
            // between signon stages
            if (!host_client->sendsignon)
            {
                if (realtime - host_client->last_message > 5)
                    SV_SendNop(host_client);
                continue;	// don't send out non-signon messages
            }
        }

        // check for an overflowed message.  Should only happen
        // on a very fucked up connection that backs up a lot, then
        // changes level
        if (host_client->message.overflowed)
        {
            SV_DropClient(true);
            host_client->message.overflowed = false;
            continue;
        }

        if (host_client->message.cursize || host_client->dropasap)
        {
            if (!NET_CanSendMessage(host_client->netconnection))
            {
//				I_Printf ("can't write\n");
                continue;
            }

            if (host_client->dropasap)
                SV_DropClient(false);	// went to another level
            else
            {
                if (NET_SendMessage(host_client->netconnection, &host_client->message) == -1)
                    SV_DropClient(true);	// if the message couldn't send, kick off
                SZ_Clear(&host_client->message);
                host_client->last_message = realtime;
                host_client->sendsignon = false;
            }
        }
    }

#if !DIRECT_SINGLE_PLAYER
// clear muzzle flashes
	SV_CleanupEnts ();
#endif
}

/*
 ==============================================================================

 SERVER SPAWNING

 ==============================================================================
 */

/*
 ================
 SV_ModelIndex

 ================
 */
int SV_ModelIndex(char *name)
{
    int i;

    if (!name || !name[0])
        return 0;
#define CACHE_IF_NOT_FOUND 0
#if CACHE_IF_NOT_FOUND
    #warning FIX THIS

        for (i=0 ; i<MAX_MODELS ; i++)
        {
            if (!sv.model_precache[i])
            {
               printf("Warning, model %s was not cached. Caching\r\n", name);
                sv.model_precache[i] = name;
                sv.models[i] = Mod_ForName (name, true);
                return i;
            }
            if (!strcmp(sv.model_precache[i], name))
                return i;
        }
        #else
    for (i = 0; i < MAX_MODELS && sv.model_precache[i]; i++)
        if (!strcmp(sv.model_precache[i], name))
            return i;

    if (i == MAX_MODELS || !sv.model_precache[i])
        Sys_Error("SV_ModelIndex: model %s not precached", name);
#endif

    return i;

}

/*
 ================
 SV_CreateBaseline

 ================
 */
void SV_CreateBaseline(void)
{
#if OLD_SERVER_BASELINE
	int			i;
	edict_t			*svent;
	int				entnum;
    #if EDICT_LINKED_LIST
        svent = sv.edicts;
    #endif // EDICT_LINKED_LIST
	for (entnum = 0; entnum < sv.num_edicts ; entnum++)
	{
	// get the current server version
	#if EDICT_LINKED_LIST
	    if (entnum) // dirty hack.
	        svent = getNextEdict(svent);
    #if !EDICT_LINKED_LIST_WITH_WATCH
		if (svent->free)
			continue;
    #endif
	#else
		svent = EDICT_NUM(entnum);
		if (svent->free)
			continue;
	#endif // EDICT_LINKED_LIST
		if (entnum > svs.maxclients && !get_qcc_modelindex(svent))
			continue;

	//
	// create entity baseline
	//
		VectorCopy (VEC(get_qcc_origin(svent)), svent->baseline.origin);
		VectorCopy (VEC(get_qcc_angles(svent)), svent->baseline.angles);
		svent->baseline.frame = get_qcc_frame(svent);
		svent->baseline.skin = get_qcc_skin(svent);
		if (entnum > 0 && entnum <= svs.maxclients)
		{
			svent->baseline.colormap = entnum;
			svent->baseline.modelindex = SV_ModelIndex("progs/player.mdl");
		}
		else
		{
			svent->baseline.colormap = 0;
#if USE_PROGSDAT
			svent->baseline.modelindex = SV_ModelIndex(pr_strings + get_qcc_model(svent));
#else
			svent->baseline.modelindex = SV_ModelIndex(getStringFromIndex(get_qcc_model(svent)));
#endif
		}

	//
	// add to the message
	//
		MSG_WriteByte (&sv.signon,svc_spawnbaseline);
		MSG_WriteShort (&sv.signon,entnum);

		MSG_WriteByte (&sv.signon, svent->baseline.modelindex);
		MSG_WriteByte (&sv.signon, svent->baseline.frame);
		MSG_WriteByte (&sv.signon, svent->baseline.colormap);
		MSG_WriteByte (&sv.signon, svent->baseline.skin);
		for (i=0 ; i<3 ; i++)
		{
			MSG_WriteCoord(&sv.signon, svent->baseline.origin[i]);
			MSG_WriteAngle(&sv.signon, svent->baseline.angles[i]);
		}
	}
	#else
    return;
#if 0 // baseline is not required as we are always sending all the coordinates and data.

    int			i;
	edict_t			*svent;
	int				entnum;
    #if EDICT_LINKED_LIST
        svent = sv.edicts;
    #endif // EDICT_LINKED_LIST
	for (entnum = 0; entnum < sv.num_edicts ; entnum++)
	{

	// get the current server version
	#if EDICT_LINKED_LIST
	    if (entnum) // dirty hack.
	        svent = getNextEdict(svent);
    #if !EDICT_LINKED_LIST_WITH_WATCH
		if (svent->free)
			continue;
    #endif
	#else


		svent = EDICT_NUM(entnum);
		if (svent->free)
			continue;
	#endif // EDICT_LINKED_LIST
		if (entnum > svs.maxclients && !get_qcc_modelindex(svent))
			continue;
	//
	// create entity baseline
	//
		MSG_WriteByte (&sv.signon,svc_spawnbaseline);
		MSG_WriteShort (&sv.signon,entnum);
		int modelindex;
        int colormap;
		if (entnum > 0 && entnum <= svs.maxclients)
		{
			colormap = entnum;
			modelindex = SV_ModelIndex("progs/player.mdl");
		}
		else
		{
			colormap = colormap = 0;
            #if USE_PROGSDAT
                        modelindex = SV_ModelIndex(pr_strings + get_qcc_model(svent));
            #else
                        modelindex = SV_ModelIndex(getStringFromIndex(get_qcc_model(svent)));
            #endif
		}
		MSG_WriteByte (&sv.signon, modelindex);
		MSG_WriteByte (&sv.signon, get_qcc_frame(svent));
		MSG_WriteByte (&sv.signon, colormap);
		MSG_WriteByte (&sv.signon, get_qcc_skin(svent));
		for (i=0 ; i<3 ; i++)
		{
			MSG_WriteCoord(&sv.signon, VEC(get_qcc_origin(svent))[i]);
			MSG_WriteAngle(&sv.signon, VEC(get_qcc_angles(svent))[i]);
		}
	}
#endif
#endif
}

/*
 ================
 SV_SendReconnect

 Tell all the clients that the server is changing levels
 ================
 */
void SV_SendReconnect(void)
{
//printf("%s\r\n", __PRETTY_FUNCTION__); system("pause");

    char data[128];
    sizebuf_t msg;

    msg.data = (uint8_t*) data;
    msg.cursize = 0;
    msg.maxsize = sizeof(data);

    MSG_WriteChar(&msg, svc_stufftext);
    MSG_WriteString(&msg, "reconnect\n");
    NET_SendToAll(&msg, 5);

    if (_g->cls.state != ca_dedicated)
    {
#ifdef QUAKE2
		Cbuf_InsertText ("reconnect\n");
#else
        Cmd_ExecuteString("reconnect\n", src_command);
#endif
    }
}

/*
 ================
 SV_SaveSpawnparms

 Grabs the current state of each client for saving across the
 transition to another level
 ================
 */
void SV_SaveSpawnparms(void)
{
    int i, j;
#if USE_PROGSDAT
	svs.serverflags = pr_global_struct->serverflags;
#else
    svs.serverflags = progs.qcc_serverflags;

#endif
    for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
    {
        if (!host_client->active)
            continue;

        // call the progs to get default spawn parms for the new client
#if USE_PROGSDAT
		pr_global_struct->self = EDICT_TO_PROG(host_client->edict);
		PR_ExecuteProgram (pr_global_struct->SetChangeParms);
		for (j=0 ; j<NUM_SPAWN_PARMS ; j++)
			host_client->spawn_parms[j] = (&pr_global_struct->parm1)[j];
#else
        progs.qcc_self = EDICT_TO_PROG(host_client->edict);
        qcc_SetChangeParms();
        j = 0;
        host_client->spawn_parms[j++] = progs.qcc_parm1;
        host_client->spawn_parms[j++] = progs.qcc_parm2;
        host_client->spawn_parms[j++] = progs.qcc_parm3;
        host_client->spawn_parms[j++] = progs.qcc_parm4;
        host_client->spawn_parms[j++] = progs.qcc_parm5;
        host_client->spawn_parms[j++] = progs.qcc_parm6;
        host_client->spawn_parms[j++] = progs.qcc_parm7;
        host_client->spawn_parms[j++] = progs.qcc_parm8;
        host_client->spawn_parms[j++] = progs.qcc_parm9;
        host_client->spawn_parms[j++] = progs.qcc_parm10;
        host_client->spawn_parms[j++] = progs.qcc_parm11;
        host_client->spawn_parms[j++] = progs.qcc_parm12;
        host_client->spawn_parms[j++] = progs.qcc_parm13;
        host_client->spawn_parms[j++] = progs.qcc_parm14;
        host_client->spawn_parms[j++] = progs.qcc_parm15;
        host_client->spawn_parms[j++] = progs.qcc_parm16;
#endif
    }
}

/*
 ================
 SV_SpawnServer

 This is called at the start of each level
 ================
 */
extern float scr_centertime_off;

void SV_SpawnServer(char *server, qboolean forceReload)
{
    edict_t *ent;
    int i;
    void *mpb;  // model_precache buffer
    void *smb;  // model
    // let's not have any servers with no name
    if (hostname[0] == 0)
        Cvar_Set("hostname", "UNNAMED");
    scr_centertime_off = 0;

    Con_DPrintf("SpawnServer: %s\n", server);
    svs.changelevel_issued = false;		// now safe to issue another
    if (!strcmp(sv.name, server) && current_skill == skill && !forceReload)
    {
        if (sv.active)
        {
            SV_SendReconnect();
        }
        sv.state = ss_loading;
        sv.paused = false;

        sv.time = 1.0;

        sprintf(sv.modelname, "maps/%s.bsp", server);

        sv.worldmodel = Mod_ForName(sv.modelname, false);

        if (!sv.worldmodel)
        {
            Con_Printf("Couldn't spawn server %s\n", sv.modelname);
            sv.active = false;
            return;
        }
        sv.models[1] = sv.worldmodel;
        sv.active = true;
        sv.datagram.cursize = 0;
        sv.reliable_datagram.cursize = 0;
        sv.active = true;

        // all setup is completed, any further precache statements are errors
        sv.state = ss_active;

        // run two frames to allow everything to settle
        host_frametime = 0.1;
        sv.signon.cursize = 0;

        for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
            if (host_client->active)
                SV_SendServerinfo(host_client);
    }
    else
    {
        resetTempModKnown(&smb, &mpb);
        //
        // tell all connected clients that we are going to a new level
        //
        if (sv.active)
        {
            SV_SendReconnect();
        }

        //
        // make cvars consistant
        //
        if (coop)
            Cvar_SetValue("deathmatch", 0);
        current_skill = (int) skill;
        if (current_skill < 0)
            current_skill = 0;
        if (current_skill > 3)
            current_skill = 3;

        Cvar_SetValue("skill", (float) current_skill);

        //
        // set up the new server
        //

        Host_ClearMemory();
        //	memset (&sv, 0, sizeof(sv)); // already in host_clear memory
        //

        //
#if !SV_MODEL_ARRAY
        sv.models = smb;
        memset(smb, 0, sizeof(smb) * MAX_MODELS);
#endif
#if !SV_HAS_FIXED_MODEL_PRECACHE
        memset(mpb, 0, sizeof(*sv.model_precache) * MAX_MODELS);
        sv.model_precache = mpb;
#endif
        strcpy(sv.name, server);

        // load progs to get entity field count
        //	PR_LoadProgs (); // next-hack: removed.
        //
        //
        COM_ResetDynamicMemory();   // next-hack: let's have a clean start to prevent memory fragmentation.
        //
        // create edict for world
        sv.edicts = ED_Alloc(worldspawn_string_index);
        progs.qcc_world = EDICT_TO_PROG(sv.edicts);
        //
#if USE_GP_BUFFER_FOR_SERVER_DATAGRAM
        static void *svDatagramBuffer = NULL;
        static void *svReliableDatagramBuffer = NULL;
        if (!svDatagramBuffer)
        {
            int maxsize = 0;
            svDatagramBuffer = sv.datagram.data = allocFromTempBuffer(MAX_DATAGRAM, &maxsize);
            sv.datagram.maxsize = maxsize;
        }
        else
        {
            sv.datagram.data = svDatagramBuffer;
            sv.datagram.maxsize = MAX_DATAGRAM;
        }
        if (!svReliableDatagramBuffer)
        {
            int maxsize = 0;
            svReliableDatagramBuffer = sv.reliable_datagram.data = allocFromTempBuffer(MAX_DATAGRAM, &maxsize);
            sv.reliable_datagram.maxsize = maxsize;
        }
        else
        {
            sv.reliable_datagram.data = svReliableDatagramBuffer;
            sv.reliable_datagram.maxsize = MAX_DATAGRAM;
        }
#else
	sv.reliable_datagram.maxsize = sizeof(sv.reliable_datagram_buf);
	sv.datagram.maxsize = sizeof(sv.datagram_buf);
	sv.datagram.data = sv.datagram_buf;
	sv.reliable_datagram.data = sv.reliable_datagram_buf;
    #endif
        sv.datagram.cursize = 0;
        sv.reliable_datagram.cursize = 0;
#if USE_GP_BUFFER_FOR_SERVER_SIGNON
        static void *serverSignonBuffer = NULL;
        if (serverSignonBuffer == NULL)
        {
            int maxsize = 0;
            serverSignonBuffer = sv.signon.data = allocFromTempBuffer(SIGNON_BUFF_SIZE, &maxsize);
            sv.signon.maxsize = maxsize;
        }
        else
        {
            sv.signon.data = serverSignonBuffer;
            sv.signon.maxsize = SIGNON_BUFF_SIZE;
        }
#else
	sv.signon.maxsize = sizeof(sv.signon_buf);
	sv.signon.data = sv.signon_buf;
    #endif
        sv.signon.cursize = 0;

        // leave slots at start for clients only
#if EDICT_LINKED_LIST
        //    ent = sv.edicts;
#else
	sv.num_edicts = svs.maxclients+1;
    #endif
        for (i = 0; i < svs.maxclients; i++)
        {
#if EDICT_LINKED_LIST
            //    ent = getNextEdict(ent);
            ent = ED_Alloc(player_string_index);   //create edict for client.

#else
    ent = EDICT_NUM(i+1);
    #endif // EDICT_LINKED_LIST
            svs.clients[i].edict = (player_edict_t*) ent;
        }

        sv.state = ss_loading;
        sv.paused = false;

        sv.time = 1.0;

        strcpy(sv.name, server);
        sprintf(sv.modelname, "maps/%s.bsp", server);
        sv.worldmodel = Mod_ForName(sv.modelname, false);
        if (!sv.worldmodel)
        {
            Con_Printf("Couldn't spawn server %s\n", sv.modelname);
            sv.active = false;
            return;
        }
        sv.models[1] = sv.worldmodel;

        //
        // clear world interaction links
        //
        SV_ClearWorld();
#if USE_PROGSDAT
        sv.sound_precache[0] = pr_strings;

        sv.model_precache[0] = pr_strings;
        sv.model_precache[1] = sv.modelname;
        for (i=1; i<sv.worldmodel->numsubmodels; i++)
        {
            sv.model_precache[1+i] = localmodels[i];
            sv.models[i+1] = Mod_ForName (localmodels[i], false);
        }
#else
#if !SEPARATE_BRUSH_MODEL_DATA
        printf("numsubmodels %d\r\n", sv.worldmodel->numsubmodels);
#else
        printf("numsubmodels %d\r\n", sv.worldmodel->brushModelData->numsubmodels);
#endif
        sv.model_precache[1] = sv.modelname;
#if !SEPARATE_BRUSH_MODEL_DATA
    for (i=1 ; i<sv.worldmodel->numsubmodels ; i++)
    #else
        for (i = 1; i < sv.worldmodel->brushModelData->numsubmodels; i++)
#endif
        {
#if WIN32
	    printf("Model %d is %s\r\n", i, localmodels[i]);
    #endif
            sv.model_precache[1 + i] = localmodels[i];
            sv.models[i + 1] = Mod_ForName(localmodels[i], false);
        }
#endif

        //
        // load the rest of the entities
        //
#if USE_PROGSDAT
	ent = EDICT_NUM(0);
	memset (&ent->v, 0, progs->entityfields * 4);
    #else
        ent = &sv.edicts[0];
        memset(&ent->v, 0, getEdictEntvarSize(ent));
#endif
#if !EDICT_LINKED_LIST_WITH_WATCH
        ent->free = false;
#endif
#if USE_PROGSDAT
	set_qcc_model(ent,  sv.worldmodel->name - pr_strings);
    #else
        set_qcc_model(ent, sv.worldmodel->nameIdx); 
#endif
        set_qcc_modelindex(ent, 1);		// world model
        set_qcc_solid(ent, SOLID_BSP);
        set_qcc_movetype(ent, MOVETYPE_PUSH);

#if USE_PROGSDAT

	if (coop)
		pr_global_struct->coop = coop;
	else
		pr_global_struct->deathmatch = deathmatch;
	pr_global_struct->mapname = sv.name - pr_strings;
    #else
        if (coop)
            progs.qcc_coop = coop;
        else
            progs.qcc_deathmatch = deathmatch;

#endif

        // serverflags are for cross level information (sigils)
#if USE_PROGSDAT
        pr_global_struct->serverflags = svs.serverflags;
#else
        progs.qcc_serverflags = svs.serverflags;
#endif

#if !SEPARATE_BRUSH_MODEL_DATA
        ED_LoadFromFile (sv.worldmodel->entities);
#else
        ED_LoadFromFile(sv.worldmodel->brushModelData->entities);
#endif
        sv.active = true;

        // all setup is completed, any further precache statements are errors
        sv.state = ss_active;

        // run two frames to allow everything to settle
        host_frametime = 0.1f;
        SV_Physics();
        SV_Physics();

        sv.model_precache = storeToInternalFlash(sv.model_precache, sizeof(*sv.model_precache) * MAX_MODELS);

        // create a baseline for more efficient communications
        SV_CreateBaseline();
        // save to internal flash

        // send serverinfo to all connected clients
        for (i = 0, host_client = svs.clients; i < svs.maxclients; i++, host_client++)
            if (host_client->active)
                SV_SendServerinfo(host_client);
    }
    Con_DPrintf("Server spawned.\n");
}

