//File: defs.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/// next-hack: class_name list. NOTE: THESE SHALL BE THE FIRST DATA!!!
//
//
const uint16_t qcc_classname_air_bubbles = air_bubbles_string_index;
const uint16_t qcc_classname_ambient_drip = ambient_drip_string_index;
const uint16_t qcc_classname_ambient_drone = ambient_drone_string_index;
const uint16_t qcc_classname_ambient_comp_hum = ambient_comp_hum_string_index;
const uint16_t qcc_classname_ambient_flouro_buzz = ambient_flouro_buzz_string_index;
const uint16_t qcc_classname_ambient_light_buzz = ambient_light_buzz_string_index;
const uint16_t qcc_classname_ambient_suck_wind = ambient_suck_wind_string_index;
const uint16_t qcc_classname_ambient_swamp1 = ambient_swamp1_string_index;
const uint16_t qcc_classname_ambient_swamp2 = ambient_swamp2_string_index;
const uint16_t qcc_classname_ambient_thunder = ambient_thunder_string_index;
const uint16_t qcc_classname_event_lightning = event_lightning_string_index;
const uint16_t qcc_classname_func_door = func_door_string_index;
const uint16_t qcc_classname_func_door_secret = func_door_secret_string_index;
const uint16_t qcc_classname_func_wall = func_wall_string_index;
const uint16_t qcc_classname_func_button = func_button_string_index;
const uint16_t qcc_classname_func_train = func_train_string_index;
const uint16_t qcc_classname_func_plat = func_plat_string_index;
const uint16_t qcc_classname_func_dm_only = func_dm_only_string_index;
const uint16_t qcc_classname_func_illusionary = func_illusionary_string_index;
const uint16_t qcc_classname_info_null = info_null_string_index;
const uint16_t qcc_classname_info_notnull = info_notnull_string_index;
const uint16_t qcc_classname_info_intermission = info_intermission_string_index;
const uint16_t qcc_classname_info_player_start = info_player_start_string_index;
const uint16_t qcc_classname_info_player_deathmatch = info_player_deathmatch_string_index;
const uint16_t qcc_classname_info_player_coop = info_player_coop_string_index;
const uint16_t qcc_classname_info_player_start2 = info_player_start2_string_index;
const uint16_t qcc_classname_info_teleport_destination = info_teleport_destination_string_index;
const uint16_t qcc_classname_item_cells = item_cells_string_index;
const uint16_t qcc_classname_item_rockets = item_rockets_string_index;
const uint16_t qcc_classname_item_shells = item_shells_string_index;
const uint16_t qcc_classname_item_spikes = item_spikes_string_index;
const uint16_t qcc_classname_item_weapon = item_weapon_string_index;
const uint16_t qcc_classname_item_health = item_health_string_index;
const uint16_t qcc_classname_item_artifact_envirosuit = item_artifact_envirosuit_string_index;
const uint16_t qcc_classname_item_artifact_super_damage = item_artifact_super_damage_string_index;
const uint16_t qcc_classname_item_artifact_invulnerability = item_artifact_invulnerability_string_index;
const uint16_t qcc_classname_item_artifact_invisibility = item_artifact_invisibility_string_index;
const uint16_t qcc_classname_item_armorInv = item_armorInv_string_index;
const uint16_t qcc_classname_item_armor2 = item_armor2_string_index;
const uint16_t qcc_classname_item_armor1 = item_armor1_string_index;
const uint16_t qcc_classname_item_key1 = item_key1_string_index;
const uint16_t qcc_classname_item_key2 = item_key2_string_index;
const uint16_t qcc_classname_item_sigil = item_sigil_string_index;
const uint16_t qcc_classname_light = light_string_index;
const uint16_t qcc_classname_light_torch_small_walltorch = light_torch_small_walltorch_string_index;
const uint16_t qcc_classname_light_flame_large_yellow = light_flame_large_yellow_string_index;
const uint16_t qcc_classname_light_flame_small_yellow = light_flame_small_yellow_string_index;
const uint16_t qcc_classname_light_flame_small_white = light_flame_small_white_string_index;
const uint16_t qcc_classname_light_fluoro = light_fluoro_string_index;
const uint16_t qcc_classname_light_fluorospark = light_fluorospark_string_index;
const uint16_t qcc_classname_light_globe = light_globe_string_index;
const uint16_t qcc_classname_monster_army = monster_army_string_index;
const uint16_t qcc_classname_monster_dog = monster_dog_string_index;
const uint16_t qcc_classname_monster_ogre = monster_ogre_string_index;
const uint16_t qcc_classname_monster_ogre_marksman = monster_ogre_marksman_string_index;
const uint16_t qcc_classname_monster_knight = monster_knight_string_index;
const uint16_t qcc_classname_monster_zombie = monster_zombie_string_index;
const uint16_t qcc_classname_monster_wizard = monster_wizard_string_index;
const uint16_t qcc_classname_monster_demon1 = monster_demon1_string_index;
const uint16_t qcc_classname_monster_shambler = monster_shambler_string_index;
const uint16_t qcc_classname_monster_boss = monster_boss_string_index;
const uint16_t qcc_classname_monster_enforcer = monster_enforcer_string_index;
const uint16_t qcc_classname_monster_hell_knight = monster_hell_knight_string_index;
const uint16_t qcc_classname_monster_shalrath = monster_shalrath_string_index;
const uint16_t qcc_classname_monster_tarbaby = monster_tarbaby_string_index;
const uint16_t qcc_classname_monster_fish = monster_fish_string_index;
const uint16_t qcc_classname_monster_oldone = monster_oldone_string_index;
const uint16_t qcc_classname_misc_fireball = misc_fireball_string_index;
const uint16_t qcc_classname_misc_explobox = misc_explobox_string_index;
const uint16_t qcc_classname_misc_explobox2 = misc_explobox2_string_index;
const uint16_t qcc_classname_misc_teleporttrain = misc_teleporttrain_string_index;
const uint16_t qcc_classname_path_corner = path_corner_string_index;
const uint16_t qcc_classname_trap_spikeshooter = trap_spikeshooter_string_index;
const uint16_t qcc_classname_trap_shooter = trap_shooter_string_index;
const uint16_t qcc_classname_trigger_teleport = trigger_teleport_string_index;
const uint16_t qcc_classname_trigger_changelevel = trigger_changelevel_string_index;
const uint16_t qcc_classname_trigger_setskill = trigger_setskill_string_index;
const uint16_t qcc_classname_trigger_counter = trigger_counter_string_index;
const uint16_t qcc_classname_trigger_once = trigger_once_string_index;
const uint16_t qcc_classname_trigger_multiple = trigger_multiple_string_index;
const uint16_t qcc_classname_trigger_onlyregistered = trigger_onlyregistered_string_index;
const uint16_t qcc_classname_trigger_secret = trigger_secret_string_index;
const uint16_t qcc_classname_trigger_monsterjump = trigger_monsterjump_string_index;
const uint16_t qcc_classname_trigger_relay = trigger_relay_string_index;
const uint16_t qcc_classname_trigger_push = trigger_push_string_index;
const uint16_t qcc_classname_trigger_hurt = trigger_hurt_string_index;
const uint16_t qcc_classname_weapon_supershotgun = weapon_supershotgun_string_index;
const uint16_t qcc_classname_weapon_nailgun = weapon_nailgun_string_index;
const uint16_t qcc_classname_weapon_supernailgun = weapon_supernailgun_string_index;
const uint16_t qcc_classname_weapon_grenadelauncher = weapon_grenadelauncher_string_index;
const uint16_t qcc_classname_weapon_rocketlauncher = weapon_rocketlauncher_string_index;
const uint16_t qcc_classname_weapon_lightning = weapon_lightning_string_index;
const uint16_t qcc_classname_worldspawn = worldspawn_string_index;
const uint16_t qcc_classname_player = player_string_index;
const uint16_t qcc_classname_bodyque = bodyque_string_index;
const uint16_t qcc_classname_fireball = fireball_string_index;
const uint16_t qcc_classname_door = door_string_index;
const uint16_t qcc_classname_func_bossgate = func_bossgate_string_index;
const uint16_t qcc_classname_func_episodegate = func_episodegate_string_index;
const uint16_t qcc_classname_plat = plat_string_index;
const uint16_t qcc_classname_train = train_string_index;
const uint16_t qcc_classname_bubble = bubble_string_index;
const uint16_t qcc_classname_teledeath = teledeath_string_index;
const uint16_t qcc_classname_DelayedUse = DelayedUse_string_index;
const uint16_t qcc_classname_spike = spike_string_index// This entity is of type missile, can be modified to other like knightspike or wizspike by changing class name
;
const uint16_t qcc_classname_grenade = grenade_string_index// this refers only to grenade (progs/grenade.mdl)
;
const uint16_t qcc_classname_wizspike = wizspike_string_index;
const uint16_t qcc_classname_knightspike = knightspike_string_index;
const uint16_t qcc_classname_teledeath2 = teledeath2_string_index// next-hack: classes added so that spawn() can get already a valid classname.
;
const uint16_t qcc_classname_nh_missile = nh_missile_string_index// missile
;
const uint16_t qcc_classname_nh_trigger = nh_trigger_string_index// general trigger
;
const uint16_t qcc_classname_nh_map = nh_map_string_index// for changing maps
;
const uint16_t qcc_classname_nh_timer = nh_timer_string_index// timer. it's the smallest edict.  
;
const uint16_t qcc_classname_nh_backpack = nh_backpack_string_index// dropped by killed entities
;
const uint16_t qcc_classname_nh_tfog = nh_tfog_string_index// teleport fog.
;
const uint16_t qcc_classname_nh_sigil_removed = nh_sigil_removed_string_index// to prevent assigning NULL
// additional classes identified by model name. These edicts are of type missile.
;
const uint16_t qcc_classname_nh_wiz_startfast = nh_wiz_startfast_string_index// this has no model
;
const uint16_t qcc_classname_progs_laser_mdl = progs_laser_mdl_string_index;
const uint16_t qcc_classname_progs_s_light_mdl = progs_s_light_mdl_string_index;
const uint16_t qcc_classname_progs_v_spike_mdl = progs_v_spike_mdl_string_index// gibs
;
const uint16_t qcc_classname_progs_zom_gib_mdl = progs_zom_gib_mdl_string_index;
const uint16_t qcc_classname_progs_gib1_mdl = progs_gib1_mdl_string_index;
const uint16_t qcc_classname_progs_gib2_mdl = progs_gib2_mdl_string_index;
const uint16_t qcc_classname_progs_gib3_mdl = progs_gib3_mdl_string_index//
;
const uint16_t qcc_classname_explo_box = explo_box_string_index//
//
// LAST CLASSNAME IS JUST A PLACEHOLDER
;
const uint16_t qcc_classname_max_classname = max_classname_string_index/*
==============================================================================

			SOURCE FOR GLOBALVARS_T C STRUCTURE

==============================================================================
*///
// system globals
//
;
;
;
;
;
;
// force all entities to touch triggers
// next frame.  this is needed because
// non-moving things don't normally scan
// for triggers, and when a trigger is
// created (like a teleport trigger), it
// needs to catch everything.
// decremented each frame, so set to 2
// to guarantee everything is touched
;
;
;
;
;
// propagated from level to level, used to
// keep track of completed episodes
;
;
;
// number of secrets found
;
// number of monsters killed
// spawnparms are used to encode information about clients across server
// level changes
;
//
// global variables set by built in functions
//	
;
// set by makevectors()
// set by traceline / tracebox
;
;
;
;
;
;
;
;
;
;
// destination of single entity writes
//
// required prog functions
//
;
// only for testing
void qcc_main(void);
void qcc_StartFrame(void);
void qcc_PlayerPreThink(void);
void qcc_PlayerPostThink(void);
void qcc_ClientKill(void);
void qcc_ClientConnect(void);
// call after setting the parm1... parms
void qcc_PutClientInServer(void);
void qcc_ClientDisconnect(void);
// called when a client first connects to
// a server. sets parms so they can be
// saved off for restarts
void qcc_SetNewParms(void);
// call to set parms for self so they can
// be saved for a level transition
//================================================
void qcc_SetChangeParms(void);
// flag for structure dumping
//================================================
/*
==============================================================================

			SOURCE FOR ENTVARS_T C STRUCTURE

==============================================================================
*///
// system fields (*** = do not set in prog code, maintained by C code)
//
;
// *** model index in the precached list
// *** origin + mins / maxs
// local time for entity
// ***
// ***
// temp angle adjust from damage or recoil
// spawn function
// bounding box extents reletive to origin
// maxs - mins
// for doors or plats, called when can't push other
// stats
// one of the IT_SHOTGUN, etc flags
// bit flags
// add to origin to get eye point
// fire
// use
// jump
// weapon changes
// view / targeting angle for players
// calculated pitch angle for lookup up slopes
// players maximum health is stored here
// don't back up
// save this fraction of incoming damage
// 0 = not in, 1 = feet, 2 = wast, 3 = eyes
// a contents value
// a movetarget or an enemy
// damage is accumulated through a frame. and sent as one single
// message, so the super shotgun doesn't generate huge messages
// who launched a missile
// mostly for doors, but also used for waterjump
// trigger messages
// either a cd track number or sound number
// contains names of wavs to play
//================================================
// flag for structure dumping
//================================================
/*
==============================================================================

				VARS NOT REFERENCED BY C CODE

==============================================================================
*///
// constants
//
;
const float qcc_FALSE = 0;
const float qcc_TRUE = 1// edict.flags
;
const float qcc_FL_FLY = 1;
const float qcc_FL_SWIM = 2;
const float qcc_FL_CLIENT = 8// set for all client edicts
;
const float qcc_FL_INWATER = 16// for enter / leave water splash
;
const float qcc_FL_MONSTER = 32;
const float qcc_FL_GODMODE = 64// player cheat
;
const float qcc_FL_NOTARGET = 128// player cheat
;
const float qcc_FL_ITEM = 256// extra wide size for bonus items
;
const float qcc_FL_ONGROUND = 512// standing on something
;
const float qcc_FL_PARTIALGROUND = 1024// not all corners are valid
;
const float qcc_FL_WATERJUMP = 2048// player jumping out of water
;
const float qcc_FL_JUMPRELEASED = 4096// for jump debouncing
// edict.movetype values
;
const float qcc_MOVETYPE_NONE = 0// never moves
//float	MOVETYPE_ANGLENOCLIP	= 1;
//float	MOVETYPE_ANGLECLIP		= 2;
;
const float qcc_MOVETYPE_WALK = 3// players only
;
const float qcc_MOVETYPE_STEP = 4// discrete, not real time unless fall
;
const float qcc_MOVETYPE_FLY = 5;
const float qcc_MOVETYPE_TOSS = 6// gravity
;
const float qcc_MOVETYPE_PUSH = 7// no clip to world, push and crush
;
const float qcc_MOVETYPE_NOCLIP = 8;
const float qcc_MOVETYPE_FLYMISSILE = 9// fly with extra size against monsters
;
const float qcc_MOVETYPE_BOUNCE = 10;
const float qcc_MOVETYPE_BOUNCEMISSILE = 11// bounce with extra size
// edict.solid values
;
const float qcc_SOLID_NOT = 0// no interaction with other objects
;
const float qcc_SOLID_TRIGGER = 1// touch on edge, but not blocking
;
const float qcc_SOLID_BBOX = 2// touch on edge, block
;
const float qcc_SOLID_SLIDEBOX = 3// touch on edge, but not an onground
;
const float qcc_SOLID_BSP = 4// bsp clip, touch on edge, block
// range values
;
const float qcc_RANGE_MELEE = 0;
const float qcc_RANGE_NEAR = 1;
const float qcc_RANGE_MID = 2;
const float qcc_RANGE_FAR = 3// deadflag values
;
const float qcc_DEAD_NO = 0;
const float qcc_DEAD_DYING = 1;
const float qcc_DEAD_DEAD = 2;
const float qcc_DEAD_RESPAWNABLE = 3// takedamage values
;
const float qcc_DAMAGE_NO = 0;
const float qcc_DAMAGE_YES = 1;
const float qcc_DAMAGE_AIM = 2// items
;
const float qcc_IT_AXE = 4096;
const float qcc_IT_SHOTGUN = 1;
const float qcc_IT_SUPER_SHOTGUN = 2;
const float qcc_IT_NAILGUN = 4;
const float qcc_IT_SUPER_NAILGUN = 8;
const float qcc_IT_GRENADE_LAUNCHER = 16;
const float qcc_IT_ROCKET_LAUNCHER = 32;
const float qcc_IT_LIGHTNING = 64;
const float qcc_IT_EXTRA_WEAPON = 128;
const float qcc_IT_SHELLS = 256;
const float qcc_IT_NAILS = 512;
const float qcc_IT_ROCKETS = 1024;
const float qcc_IT_CELLS = 2048;
const float qcc_IT_ARMOR1 = 8192;
const float qcc_IT_ARMOR2 = 16384;
const float qcc_IT_ARMOR3 = 32768;
const float qcc_IT_SUPERHEALTH = 65536;
const float qcc_IT_KEY1 = 131072;
const float qcc_IT_KEY2 = 262144;
const float qcc_IT_INVISIBILITY = 524288;
const float qcc_IT_INVULNERABILITY = 1048576;
const float qcc_IT_SUIT = 2097152;
const float qcc_IT_QUAD = 4194304// point content values
;
const float qcc_CONTENT_EMPTY = -1;
const float qcc_CONTENT_SOLID = -2;
const float qcc_CONTENT_WATER = -3;
const float qcc_CONTENT_SLIME = -4;
const float qcc_CONTENT_LAVA = -5;
const float qcc_CONTENT_SKY = -6;
const float qcc_STATE_TOP = 0;
const float qcc_STATE_BOTTOM = 1;
const float qcc_STATE_UP = 2;
const float qcc_STATE_DOWN = 3;
const vector qcc_VEC_ORIGIN = {{0.000000f,0.000000f, 0.000000f}};
const vector qcc_VEC_HULL_MIN = {{-16.0000f,-16.0000f, -24.0000f}};
const vector qcc_VEC_HULL_MAX = {{16.0000f,16.0000f, 32.0000f}};
const vector qcc_VEC_HULL2_MIN = {{-32.0000f,-32.0000f, -24.0000f}};
const vector qcc_VEC_HULL2_MAX = {{32.0000f,32.0000f, 64.0000f}}// protocol bytes
;
const float qcc_SVC_TEMPENTITY = 23;
const float qcc_SVC_KILLEDMONSTER = 27;
const float qcc_SVC_FOUNDSECRET = 28;
const float qcc_SVC_INTERMISSION = 30;
const float qcc_SVC_FINALE = 31;
const float qcc_SVC_CDTRACK = 32;
const float qcc_SVC_SELLSCREEN = 33;
const float qcc_TE_SPIKE = 0;
const float qcc_TE_SUPERSPIKE = 1;
const float qcc_TE_GUNSHOT = 2;
const float qcc_TE_EXPLOSION = 3;
const float qcc_TE_TAREXPLOSION = 4;
const float qcc_TE_LIGHTNING1 = 5;
const float qcc_TE_LIGHTNING2 = 6;
const float qcc_TE_WIZSPIKE = 7;
const float qcc_TE_KNIGHTSPIKE = 8;
const float qcc_TE_LIGHTNING3 = 9;
const float qcc_TE_LAVASPLASH = 10;
const float qcc_TE_TELEPORT = 11// sound channels
// channel 0 never willingly overrides
// other channels (1-7) allways override a playing sound on that channel
;
const float qcc_CHAN_AUTO = 0;
const float qcc_CHAN_WEAPON = 1;
const float qcc_CHAN_VOICE = 2;
const float qcc_CHAN_ITEM = 3;
const float qcc_CHAN_BODY = 4;
const float qcc_ATTN_NONE = 0;
const float qcc_ATTN_NORM = 1;
const float qcc_ATTN_IDLE = 2;
const float qcc_ATTN_STATIC = 3// update types
;
const float qcc_UPDATE_GENERAL = 0;
const float qcc_UPDATE_STATIC = 1;
const float qcc_UPDATE_BINARY = 2;
const float qcc_UPDATE_TEMP = 3// entity effects
;
const float qcc_EF_BRIGHTFIELD = 1;
const float qcc_EF_MUZZLEFLASH = 2;
const float qcc_EF_BRIGHTLIGHT = 4;
const float qcc_EF_DIMLIGHT = 8// messages
;
const float qcc_MSG_BROADCAST = 0// unreliable to all
;
const float qcc_MSG_ONE = 1// reliable to one (msg_entity)
;
const float qcc_MSG_ALL = 2// reliable to all
;
const float qcc_MSG_INIT = 3// write to the init string
//================================================
//
// globals
//
;
;
// set when a rule exits
;
// null string, nothing should be held here
;
;
// launch_spike sets this after spawning it
;
// the entity that activated a trigger or brush
;
// set by T_Damage
;
;
//================================================
//
// world fields (FIXME: make globals)
//
;
// 0=medieval 1=metal 2=base
//================================================
//
// quakeed fields
//
// not used by game, but parsed by light util
//
// monster ai
//
// mad at this player before taking damage
const float qcc_AS_STRAIGHT = 1;
const float qcc_AS_SLIDING = 2;
const float qcc_AS_MELEE = 3;
const float qcc_AS_MISSILE = 4//
// player only fields
//
;
// set to time+0.2 whenever a client fires a
// weapon or takes damage.  Used to alert
// monsters that otherwise would let the player go
// player jump flag
// player swimming sound flag
// when time > air_finished, start drowning
// keeps track of the number of bubbles
// keeps track of how the player died
//
// object stuff
//
// angle at start
// only used by secret door
//
// doors, etc
//
// time from firing to restarting
// time from activation to firing
// door's trigger entity
//
// monsters
//
//
// doors
//
// damage done by door when hit
//
// misc
//
// misc flag
//
// subs
//
//
// triggers
//
// for counting triggers
//
// plats / doors / buttons
//
// top and bottom positions
//
// sounds
//
//===========================================================================
//
// builtin functions
//
void qcc_makevectors(// sets v_forward, etc globals
vector );
void qcc_setorigin(int , vector );
void qcc_setmodel(// set movetype and solid first
int , uint16_t );
void qcc_setsize(// #5 was removed
//void() break						= #6;
int , vector , vector );
float qcc_random(// returns 0 - 1
void);
void qcc_sound(int , float , uint16_t , float , float );
vector qcc_normalize(vector );
void qcc_error(uint16_t );
void qcc_objerror(uint16_t );
float qcc_vlen(vector );
float qcc_vectoyaw(vector );
int qcc_spawn(uint16_t );
void qcc_remove(// sets trace_* globals
// nomonsters can be:
// An entity will also be ignored for testing if forent == test,
// forent->owner == test, or test->owner == forent
// a forent of world is ignored
int );
void qcc_traceline(vector , vector , float , int );
int qcc_checkclient(// returns a client to look for
void);
int qcc_find(int , field , uint16_t );
uint16_t qcc_precache_sound(uint16_t );
uint16_t qcc_precache_model(uint16_t );
void qcc_stuffcmd(int , uint16_t );
int qcc_findradius(vector , float );
void qcc_bprint(uint16_t );
void qcc_sprint(int , uint16_t );
void qcc_dprint(uint16_t );
uint16_t qcc_ftos(float );
uint16_t qcc_vtos(vector );
void qcc_coredump(// prints all edicts
void);
void qcc_traceon(// turns statment trace on
void);
void qcc_traceoff(void);
void qcc_eprint(// prints an entire edict
int );
float qcc_walkmove(// returns TRUE or FALSE
// #33 was removed
//float(float yaw, float dist) droptofloor= #34;	// WHY THIS HAD THESE ARGS?
float , float );
float qcc_droptofloor(// TRUE if landed on floor
void);
void qcc_lightstyle(float , uint16_t );
float qcc_rint(// round to nearest int
float );
float qcc_floor(// largest integer <= v
float );
float qcc_ceil(// smallest integer >= v
// #39 was removed
float );
float qcc_checkbottom(// true if self is on ground
int );
float qcc_pointcontents(// returns a CONTENT_*
// #42 was removed
vector );
float qcc_fabs(float );
vector qcc_aim(// returns the shooting vector
int , float );
float qcc_cvar(// return cvar.value
uint16_t );
void qcc_localcmd(// put string into local que
uint16_t );
int qcc_nextent(// for looping through all ents
int );
void qcc_particle(// start a particle effect
vector , vector , float , float );
void qcc_ChangeYaw(// turn towards self.ideal_yaw
// at self.yaw_speed
// #50 was removed
void);
vector qcc_vectoangles(//
// direct client message generation
//
vector );
void qcc_WriteByte(float , float );
void qcc_WriteChar(float , float );
void qcc_WriteShort(float , float );
void qcc_WriteLong(float , float );
void qcc_WriteCoord(float , float );
void qcc_WriteAngle(float , float );
void qcc_WriteString(float , uint16_t );
void qcc_WriteEntity(//
// broadcast client message generation
//
// void(float f) bWriteByte		= #59;
// void(float f) bWriteChar		= #60;
// void(float f) bWriteShort		= #61;
// void(float f) bWriteLong		= #62;
// void(float f) bWriteCoord		= #63;
// void(float f) bWriteAngle		= #64;
// void(string s) bWriteString	= #65;
// void(entity e) bWriteEntity = #66;
float , int );
void qcc_movetogoal(float );
uint16_t qcc_precache_file(// no effect except for -copy
uint16_t );
void qcc_makestatic(int );
void qcc_changelevel(//#71 was removed
uint16_t );
void qcc_cvar_set(// sets cvar.value
uint16_t , uint16_t );
void qcc_centerprint(// sprint, but in middle
int , uint16_t );
void qcc_ambientsound(vector , uint16_t , float , float );
uint16_t qcc_precache_model2(// registered version only
uint16_t );
uint16_t qcc_precache_sound2(// registered version only
uint16_t );
uint16_t qcc_precache_file2(// registered version only
uint16_t );
void qcc_setspawnparms(// set parm1... to the
// values at level start
// for coop respawn
//============================================================================
//
// subs.qc
//
int );
void qcc_SUB_CalcMove(vector , float , function );
void qcc_SUB_CalcMoveEnt(int , vector , float , function );
void qcc_SUB_CalcAngleMove(vector , float , function );
void qcc_SUB_CalcMoveDone(void);
void qcc_SUB_CalcAngleMoveDone(void);
void qcc_SUB_Null(void);
void qcc_SUB_UseTargets(void);
//
//	combat.qc
//
void qcc_SUB_Remove(void);
void qcc_T_Damage(int , int , int , float );
// health function
float qcc_T_Heal(int , float , float );
//File: subs.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/float qcc_CanDamage(int , int );
void qcc_SUB_Null(void)
{
}
void qcc_SUB_Remove(void)
{
    qcc_remove(progs.qcc_self);
/*
QuakeEd only writes a single float for angles (bad idea), so up and down are
just constant angles.
*/}
void qcc_SetMovedir(void)
{
    if (areVectorEqual(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, -1.00000f, 0.000000f}}))
        set_qcc_movedir(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 1.00000f}});
    else
        if (areVectorEqual(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, -2.00000f, 0.000000f}}))
            set_qcc_movedir(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, -1.00000f}});
        else
        {
            qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
            set_qcc_movedir(PROG_TO_EDICT(progs.qcc_self), progs.qcc_v_forward);
        }
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
/*
================
InitTrigger
================
*/}
void qcc_InitTrigger(void)
{
// trigger angles are used for one-way touches.  An angle of 0 is assumed
// to mean no restrictions, so use a yaw of 360 instead.
    if ((!areVectorEqual(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}})))
        qcc_SetMovedir();
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER);
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)))// set size and link into world
;
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
/*
=============
SUB_CalcMove

calculate self.velocity and self.nextthink to reach dest from
self.origin traveling at speed
===============
*/}
void qcc_SUB_CalcMoveEnt(int qcc_ent, vector qcc_tdest, float qcc_tspeed, function qcc_func)
{
    int qcc_stemp;
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = qcc_ent;
    qcc_SUB_CalcMove(qcc_tdest, qcc_tspeed, qcc_func);
    progs.qcc_self = qcc_stemp;
}
void qcc_SUB_CalcMove(vector qcc_tdest, float qcc_tspeed, function qcc_func)
{
    vector qcc_vdestdelta;
    float qcc_len,     qcc_traveltime;
    if (!qcc_tspeed)
        qcc_objerror(No_speed_is_defined__string_index);
    set_qcc_think1(PROG_TO_EDICT(progs.qcc_self), qcc_func);
    set_qcc_finaldest(PROG_TO_EDICT(progs.qcc_self), qcc_tdest);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_CalcMoveDone));
    if (areVectorEqual(qcc_tdest, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))))
    {
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
        return;
// set destdelta to the vector needed to move
    }
    qcc_vdestdelta = vectorSub(qcc_tdest, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))// calculate length of vector
;
    qcc_len = qcc_vlen(qcc_vdestdelta)// divide by speed to get time to reach dest
;
    qcc_traveltime = qcc_len / qcc_tspeed;
    if (qcc_traveltime < 0.1f)
    {
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
        return;
// set nextthink to trigger a think when dest is reached
    }
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + qcc_traveltime)// scale the destdelta vector by the time spent traveling to get velocity
;
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorMulFloat(qcc_vdestdelta, ( 1 / qcc_traveltime )))// qcc won't take vec/float	
;
/*
============
After moving, set origin to exact final destination
============
*/}
void qcc_SUB_CalcMoveDone(void)
{
    qcc_setorigin(progs.qcc_self, get_qcc_finaldest(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1);
    if (get_qcc_think1(PROG_TO_EDICT(progs.qcc_self)))
        ((void (*)() )getFunction(get_qcc_think1(PROG_TO_EDICT(progs.qcc_self))))();
/*
=============
SUB_CalcAngleMove

calculate self.avelocity and self.nextthink to reach destangle from
self.angles rotating 

The calling function should make sure self.think is valid
===============
*/}
void qcc_SUB_CalcAngleMoveEnt(int qcc_ent, vector qcc_destangle, float qcc_tspeed, function qcc_func)
{
    int qcc_stemp;
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = qcc_ent;
    qcc_SUB_CalcAngleMove(qcc_destangle, qcc_tspeed, qcc_func);
    progs.qcc_self = qcc_stemp;
}
void qcc_SUB_CalcAngleMove(vector qcc_destangle, float qcc_tspeed, function qcc_func)
{
    vector qcc_destdelta;
    float qcc_len,     qcc_traveltime;
    if (!qcc_tspeed)
        qcc_objerror(No_speed_is_defined__string_index)// set destdelta to the vector needed to move
;
    qcc_destdelta = vectorSub(qcc_destangle, get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)))// calculate length of vector
;
    qcc_len = qcc_vlen(qcc_destdelta)// divide by speed to get time to reach dest
;
    qcc_traveltime = qcc_len / qcc_tspeed// set nextthink to trigger a think when dest is reached
;
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + qcc_traveltime)// scale the destdelta vector by the time spent traveling to get velocity
;
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), vectorMulFloat(qcc_destdelta, ( 1 / qcc_traveltime )));
    set_qcc_think1(PROG_TO_EDICT(progs.qcc_self), qcc_func);
    set_qcc_finalangle(PROG_TO_EDICT(progs.qcc_self), qcc_destangle);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_CalcAngleMoveDone));
/*
============
After rotating, set angle to exact final angle
============
*/}
void qcc_SUB_CalcAngleMoveDone(void)
{
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), get_qcc_finalangle(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1);
    if (get_qcc_think1(PROG_TO_EDICT(progs.qcc_self)))
        ((void (*)() )getFunction(get_qcc_think1(PROG_TO_EDICT(progs.qcc_self))))();
//=============================================================================
}
void qcc_DelayThink(void)
{
    progs.qcc_activator = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    qcc_SUB_UseTargets();
    qcc_remove(progs.qcc_self);
/*
==============================
SUB_UseTargets

the global "activator" should be set to the entity that initiated the firing.

If self.delay is set, a DelayedUse entity will be created that will actually
do the SUB_UseTargets after that many seconds have passed.

Centerprints any self.message to the activator.

Removes all entities with a targetname that match self.killtarget,
and removes them, so some events can remove other triggers.

Search for (string)targetname in all entities that
match (string)self.target and call their .use function

==============================
*/}
void qcc_SUB_UseTargets(void)
{
    int qcc_t,     qcc_stemp,     qcc_otemp,     qcc_act//
// check for a delay
//
;
    if (get_qcc_delay(PROG_TO_EDICT(progs.qcc_self)))
// create a temp object to fire at a later time
    {
        qcc_t = qcc_spawn(qcc_classname_DelayedUse);
        set_qcc_classname(PROG_TO_EDICT(qcc_t), qcc_classname_DelayedUse);
        set_qcc_nextthink(PROG_TO_EDICT(qcc_t), progs.qcc_time + get_qcc_delay(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_think(PROG_TO_EDICT(qcc_t), getFunctionIndex(qcc_DelayThink));
        set_qcc_enemy(PROG_TO_EDICT(qcc_t), progs.qcc_activator);
        set_qcc_message(PROG_TO_EDICT(qcc_t), get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_killtarget(PROG_TO_EDICT(qcc_t), get_qcc_killtarget(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_target(PROG_TO_EDICT(qcc_t), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)));
        return;
//
// print the message
//
    }
    if (((int) areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_activator)), qcc_classname_player)) && ((int) (!areStringsEqual(get_qcc_message(PROG_TO_EDICT(progs.qcc_self)), NULL_string_index))))
    {
        qcc_centerprint(progs.qcc_activator, get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
        if (isEmptyString(get_qcc_noise(PROG_TO_EDICT(progs.qcc_self))))
            qcc_sound(progs.qcc_activator, qcc_CHAN_VOICE, misc_talk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
//
// kill the killtagets
//
    }
    if (get_qcc_killtarget(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_t = progs.qcc_world;
        do
        {
            qcc_t = qcc_find(qcc_t, offsetof (big_entvars_t, qcc_targetname), get_qcc_killtarget(PROG_TO_EDICT(progs.qcc_self)));
            if ((!qcc_t))
                return;
            qcc_remove(qcc_t);
        }
        while(1.00000f);
//
// fire targets
//
    }
    if (get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_act = progs.qcc_activator;
        qcc_t = progs.qcc_world;
        do
        {
            qcc_t = qcc_find(qcc_t, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)));
            if ((!qcc_t))
            {
                return;
            }
            qcc_stemp = progs.qcc_self;
            qcc_otemp = progs.qcc_other;
            progs.qcc_self = qcc_t;
            progs.qcc_other = qcc_stemp;
            if ((!areFunctionsEqual(get_qcc_use(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex(qcc_SUB_Null))))
            {
                if (get_qcc_use(PROG_TO_EDICT(progs.qcc_self)))
                    ((void (*)() )getFunction(get_qcc_use(PROG_TO_EDICT(progs.qcc_self))))();
            }
            progs.qcc_self = qcc_stemp;
            progs.qcc_other = qcc_otemp;
            progs.qcc_activator = qcc_act;
        }
        while(1.00000f);
    }
/*

in nightmare mode, all attack_finished times become 0
some monsters refire twice automatically

*/}
void qcc_SUB_AttackFinished(float qcc_normal)
{
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 0)// refire count for nightmare
;
    if (progs.qcc_skill != 3)
        set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + qcc_normal);
}
float qcc_visible(int );
void qcc_SUB_CheckRefire(function qcc_thinkst)
{
    if (progs.qcc_skill != 3)
        return;
    if (get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) == 1)
        return;
    if (!qcc_visible(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        return;
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), qcc_thinkst);
//File: fight.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*

A monster is in fight mode if it thinks it can effectively attack its
enemy.

When it decides it can't attack, it goes into hunt mode.

*/}
float qcc_anglemod(float );
void qcc_knight_atk1(void);
void qcc_knight_runatk1(void);
void qcc_ogre_smash1(void);
void qcc_ogre_swing1(void);
void qcc_sham_smash1(void);
void qcc_sham_swingr1(void);
void qcc_sham_swingl1(void);
float qcc_DemonCheckAttack(void);
void qcc_Demon_Melee(float );
void qcc_ChooseTurn(vector );
void qcc_ai_face(void);
;
;
void qcc_knight_attack(void)
{
    float qcc_len// decide if now is a good swing time
;
    qcc_len = qcc_vlen(vectorSub(vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_view_ofs(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))), ( vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self))) )));
    if (qcc_len < 80)
        qcc_knight_atk1();
    else
        qcc_knight_runatk1();
//=============================================================================
/*
===========
CheckAttack

The player is in view, so decide to move or launch an attack
Returns FALSE if movement should continue
============
*/}
float qcc_CheckAttack(void)
{
    vector qcc_spot1,     qcc_spot2;
    int qcc_targ;
    float qcc_chance;
    qcc_targ = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))// see if any entities are in the way of the shot
;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_FALSE, progs.qcc_self);
    if (progs.qcc_trace_ent != qcc_targ)
// don't have a clear shot
        return qcc_FALSE;
    if (((int) progs.qcc_trace_inopen) && ((int) progs.qcc_trace_inwater))
// sight line crossed contents
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
// melee attack
    {
        if (get_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self)))
        {
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_knight))
                qcc_knight_attack();
            else
                ((void (*)() )getFunction(get_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self))))();
            return qcc_TRUE;
        }
// missile attack
    }
    if (!get_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_FAR)
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
    {
        qcc_chance = 0.9f;
        set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    }
    else
        if (progs.qcc_enemy_range == qcc_RANGE_NEAR)
        {
            if (get_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self)))
                qcc_chance = 0.2f;
            else
                qcc_chance = 0.4f;
        }
        else
            if (progs.qcc_enemy_range == qcc_RANGE_MID)
            {
                if (get_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self)))
                    qcc_chance = 0.05f;
                else
                    qcc_chance = 0.1f;
            }
            else
                qcc_chance = 0;
    if (qcc_random() < qcc_chance)
    {
        ((void (*)() )getFunction(get_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self))))();
        qcc_SUB_AttackFinished(2 * qcc_random());
        return qcc_TRUE;
    }
    return qcc_FALSE;
/*
=============
ai_face

Stay facing the enemy
=============
*/}
void qcc_ai_face(void)
{
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
    qcc_ChangeYaw();
/*
=============
ai_charge

The monster is in a melee attack, so get as close as possible to .enemy
=============
*/}
float qcc_visible(int );
float qcc_infront(int );
float qcc_range(int );
void qcc_ai_charge(float qcc_d)
{
    qcc_ai_face();
    qcc_movetogoal(qcc_d)// done in C code...
;
}
void qcc_ai_charge_side(void)
{
    vector qcc_dtemp;
    float qcc_heading// aim to the left of the enemy for a flyby
;
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
    qcc_ChangeYaw();
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_dtemp = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), floatMulVector(30, progs.qcc_v_right));
    qcc_heading = qcc_vectoyaw(vectorSub(qcc_dtemp, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_walkmove(qcc_heading, 20.0000f);
/*
=============
ai_melee

=============
*/}
void qcc_ai_melee(void)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
// removed before stroke
        return;
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 60)
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 3;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
}
void qcc_ai_melee_side(void)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
// removed before stroke
        return;
    qcc_ai_charge_side();
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 60)
        return;
    if (!qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 3;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
//=============================================================================
/*
===========
SoldierCheckAttack

The player is in view, so decide to move or launch an attack
Returns FALSE if movement should continue
============
*/}
float qcc_SoldierCheckAttack(void)
{
    vector qcc_spot1,     qcc_spot2;
    int qcc_targ;
    float qcc_chance;
    qcc_targ = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))// see if any entities are in the way of the shot
;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_FALSE, progs.qcc_self);
    if (((int) progs.qcc_trace_inopen) && ((int) progs.qcc_trace_inwater))
// sight line crossed contents
        return qcc_FALSE;
    if (progs.qcc_trace_ent != qcc_targ)
// don't have a clear shot
// missile attack
        return qcc_FALSE;
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_FAR)
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
        qcc_chance = 0.9f;
    else
        if (progs.qcc_enemy_range == qcc_RANGE_NEAR)
            qcc_chance = 0.4f;
        else
            if (progs.qcc_enemy_range == qcc_RANGE_MID)
                qcc_chance = 0.05f;
            else
                qcc_chance = 0;
    if (qcc_random() < qcc_chance)
    {
        ((void (*)() )getFunction(get_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self))))();
        qcc_SUB_AttackFinished(1 + qcc_random());
        if (qcc_random() < 0.3f)
            set_qcc_lefty(PROG_TO_EDICT(progs.qcc_self), !get_qcc_lefty(PROG_TO_EDICT(progs.qcc_self)));
        return qcc_TRUE;
    }
    return qcc_FALSE;
//=============================================================================
/*
===========
ShamCheckAttack

The player is in view, so decide to move or launch an attack
Returns FALSE if movement should continue
============
*/}
float qcc_ShamCheckAttack(void)
{
    vector qcc_spot1,     qcc_spot2;
    int qcc_targ;
    float qcc_chance//	local float		enemy_yaw;     // next-hack removed, not used.
;
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
    {
        if (qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
            return qcc_TRUE;
        }
    }
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (!progs.qcc_enemy_vis)
        return qcc_FALSE;
    qcc_targ = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))// see if any entities are in the way of the shot
;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    if (qcc_vlen(vectorSub(qcc_spot1, qcc_spot2)) > 600)
        return qcc_FALSE;
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_FALSE, progs.qcc_self);
    if (((int) progs.qcc_trace_inopen) && ((int) progs.qcc_trace_inwater))
// sight line crossed contents
        return qcc_FALSE;
    if (progs.qcc_trace_ent != qcc_targ)
    {
// don't have a clear shot
        return qcc_FALSE;
// missile attack
    }
    if (progs.qcc_enemy_range == qcc_RANGE_FAR)
        return qcc_FALSE;
    set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MISSILE);
    qcc_SUB_AttackFinished(2 + 2 * qcc_random());
    return qcc_TRUE;
//============================================================================
/*
===========
OgreCheckAttack

The player is in view, so decide to move or launch an attack
Returns FALSE if movement should continue
============
*/}
float qcc_OgreCheckAttack(void)
{
    vector qcc_spot1,     qcc_spot2;
    int qcc_targ;
    float qcc_chance;
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
    {
        if (qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
            return qcc_TRUE;
        }
    }
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (!progs.qcc_enemy_vis)
        return qcc_FALSE;
    qcc_targ = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))// see if any entities are in the way of the shot
;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_FALSE, progs.qcc_self);
    if (((int) progs.qcc_trace_inopen) && ((int) progs.qcc_trace_inwater))
// sight line crossed contents
        return qcc_FALSE;
    if (progs.qcc_trace_ent != qcc_targ)
    {
// don't have a clear shot
        return qcc_FALSE;
// missile attack
    }
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_FAR)
        return qcc_FALSE;
    else
        if (progs.qcc_enemy_range == qcc_RANGE_NEAR)
            qcc_chance = 0.1f;
        else
            if (progs.qcc_enemy_range == qcc_RANGE_MID)
                qcc_chance = 0.05f;
            else
                qcc_chance = 0;
    set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MISSILE);
    qcc_SUB_AttackFinished(1 + 2 * qcc_random());
    return qcc_TRUE;
//File: ai.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
void qcc_movetarget_f(void);
void qcc_t_movetarget(void);
void qcc_knight_walk1(void);
void qcc_knight_bow6(void);
void qcc_knight_bow1(void);
/*

.enemy
Will be world if not currently angry at anyone.

.movetarget
The next path spot to walk toward.  If .enemy, ignore .movetarget.
When an enemy is killed, the monster will try to return to it's path.

.huntt_ime
Set to time + something when the player is in sight, but movement straight for
him is blocked.  This causes the monster to use wall following code for
movement direction instead of sighting on the player.

.ideal_yaw
A yaw angle of the intended direction, which will be turned towards at up
to 45 deg / state.  If the enemy is in view and hunt_time is not active,
this will be the exact line towards the enemy.

.pausetime
A monster will leave it's stand state and head towards it's .movetarget when
time > .pausetime.

walkmove(angle, speed) primitive is all or nothing
*///
// globals
//
void qcc_T_Damage(int , int , int , float );
//
// when a monster becomes angry at a player, that monster will be used
// as the sight target the next frame so that monsters near that one
// will wake up even if they wouldn't have noticed the player
//
;
;
;
float qcc_anglemod(float qcc_v)
{
    while (qcc_v >= 360)
        qcc_v = qcc_v - 360;
    while (qcc_v < 0)
        qcc_v = qcc_v + 360;
    return qcc_v;
/*
==============================================================================

MOVETARGET CODE

The angle of the movetarget effects standing and bowing direction, but has no effect on movement, which allways heads to the next target.

targetname
must be present.  The name of this movetarget.

target
the next spot to move to.  If not present, stop here for good.

pausetime
The number of seconds to spend standing or bowing for path_stand or path_bow

==============================================================================
*/}
void qcc_movetarget_f(void)
{
    if (isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(monster_movetarget__no_targetnam_06ED6ACF_long_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_t_movetarget));
    qcc_setsize(progs.qcc_self, (vector) {{-8.00000f, -8.00000f, -8.00000f}}, (vector) {{8.00000f, 8.00000f, 8.00000f}});
/*QUAKED path_corner (0.5 0.3 0) (-8 -8 -8) (8 8 8)
Monsters will continue walking towards the next target corner.
*/}
void qcc_path_corner(void)
{
    qcc_movetarget_f();
/*
=============
t_movetarget

Something has bumped into a movetarget.  If it is a monster
moving towards it, change the next destination and continue.
==============
*/}
void qcc_t_movetarget(void)
{
    int qcc_temp;
    if (get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_other)) != progs.qcc_self)
        return;
    if (get_qcc_enemy(PROG_TO_EDICT(progs.qcc_other)))
// fighting, not following a path
        return;
    qcc_temp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    progs.qcc_other = qcc_temp;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_ogre))
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogdrag_wav_string_index, 1.00000f, qcc_ATTN_IDLE)// play chainsaw drag sound
//dprint ("t_movetarget\n");
;
    set_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self), set_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self), qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_other)))));
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
    if ((!get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self))))
    {
        set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 999999);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
        return;
    }
//============================================================================
/*
=============
range

returns the range catagorization of an entity reletive to self
0	melee range, will become hostile even if back is turned
1	visibility and infront, or visibility and show hostile
2	infront and show hostile
3	only triggered by damage
=============
*/}
float qcc_range(int qcc_targ)
{
    vector qcc_spot1,     qcc_spot2;
    float qcc_r;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_r = qcc_vlen(vectorSub(qcc_spot1, qcc_spot2));
    if (qcc_r < 120)
        return qcc_RANGE_MELEE;
    if (qcc_r < 500)
        return qcc_RANGE_NEAR;
    if (qcc_r < 1000)
        return qcc_RANGE_MID;
    return qcc_RANGE_FAR;
/*
=============
visible

returns 1 if the entity is visible to self, even if not infront ()
=============
*/}
float qcc_visible(int qcc_targ)
{
    vector qcc_spot1,     qcc_spot2;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_TRUE, progs.qcc_self)// see through other monsters
;
    if (((int) progs.qcc_trace_inopen) && ((int) progs.qcc_trace_inwater))
// sight line crossed contents
        return qcc_FALSE;
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    return qcc_FALSE;
/*
=============
infront

returns 1 if the entity is in front (in sight) of self
=============
*/}
float qcc_infront(int qcc_targ)
{
    vector qcc_vec;
    float qcc_dot;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_vec = qcc_normalize(vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_dot = dotProduct(qcc_vec, progs.qcc_v_forward);
    if (qcc_dot > 0.3f)
    {
        return qcc_TRUE;
    }
    return qcc_FALSE;
//============================================================================
/*
===========
ChangeYaw

Turns towards self.ideal_yaw at self.yaw_speed
Sets the global variable current_yaw
Called every 0.1 sec by monsters
============
*//*

void() ChangeYaw =
{
	local float		ideal, move;

//current_yaw = self.ideal_yaw;
// mod down the current angle
	current_yaw = anglemod( self.angles_y );
	ideal = self.ideal_yaw;
	
	if (current_yaw == ideal)
		return;
	
	move = ideal - current_yaw;
	if (ideal > current_yaw)
	{
		if (move > 180)
			move = move - 360;
	}
	else
	{
		if (move < -180)
			move = move + 360;
	}
		
	if (move > 0)
	{
		if (move > self.yaw_speed)
			move = self.yaw_speed;
	}
	else
	{
		if (move < 0-self.yaw_speed )
			move = 0-self.yaw_speed;
	}

	current_yaw = anglemod (current_yaw + move);

	self.angles_y = current_yaw;
};

*///============================================================================
}
void qcc_HuntTarget(void)
{
    set_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self), get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), get_qcc_th_run(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
    qcc_SUB_AttackFinished(1.00000f)// wait a while before first attack
;
}
void qcc_SightSound(void)
{
    float qcc_rsnd;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_ogre))
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogwake_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    else
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_knight))
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, knight_ksight_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_shambler))
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_ssight_wav_string_index, 1.00000f, qcc_ATTN_NORM);
            else
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_demon1))
                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_sight2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                else
                    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_wizard))
                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, wizard_wsight_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                    else
                        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_zombie))
                            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_idle_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                        else
                            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_dog))
                                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_dsight_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                            else
                                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_hell_knight))
                                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, hknight_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                else
                                    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_tarbaby))
                                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, blob_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                    else
                                        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), monster_vomit_string_index))
                                            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, vomitus_v_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                        else
                                            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_enforcer))
                                            {
                                                qcc_rsnd = qcc_rint(qcc_random() * 3);
                                                if (qcc_rsnd == 1)
                                                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                                else
                                                    if (qcc_rsnd == 2)
                                                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_sight2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                                    else
                                                        if (qcc_rsnd == 0)
                                                            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_sight3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                                        else
                                                            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_sight4_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                            }
                                            else
                                                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_army))
                                                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                                else
                                                    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_shalrath))
                                                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_sight_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_FoundTarget(void)
{
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player))
// let other monsters see this monster for a while
    {
        progs.qcc_sight_entity = progs.qcc_self;
        progs.qcc_sight_entity_time = progs.qcc_time;
    }
    set_qcc_show_hostile(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1)// wake up other monsters
;
    qcc_SightSound();
    qcc_HuntTarget();
/*
===========
FindTarget

Self is currently not attacking anything, so try to find a target

Returns TRUE if an enemy was sighted

When a player fires a missile, the point of impact becomes a fakeplayer so
that monsters that see the impact will respond as if they had seen the
player.

To avoid spending too much time, only a single client (or fakeclient) is
checked each frame.  This means multi player games will have slightly
slower noticing monsters.
============
*/}
float qcc_FindTarget(void)
{
    int qcc_client;
    float qcc_r// if the first spawnflag bit is set, the monster will only wake up on
// really seeing the player, not another monster getting angry
// spawnflags & 3 is a big hack, because zombie crucified used the first
// spawn flag prior to the ambush flag, and I forgot about it, so the second
// spawn flag works as well
;
    if (((int) progs.qcc_sight_entity_time >= progs.qcc_time - 0.1f) && ((int) !( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 3)) )))
    {
        qcc_client = progs.qcc_sight_entity;
        if (get_qcc_enemy(PROG_TO_EDICT(qcc_client)) == get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))
// WAS MISSING
            return qcc_TRUE;
    }
    else
    {
        qcc_client = qcc_checkclient();
        if ((!qcc_client))
// current check entity isn't in PVS
            return qcc_FALSE;
    }
    if (qcc_client == get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(qcc_client))) & ((int) qcc_FL_NOTARGET)))
        return qcc_FALSE;
    if ((((int) get_qcc_items(PROG_TO_EDICT(qcc_client))) & ((int) qcc_IT_INVISIBILITY)))
        return qcc_FALSE;
    qcc_r = qcc_range(qcc_client);
    if (qcc_r == qcc_RANGE_FAR)
        return qcc_FALSE;
    if (!qcc_visible(qcc_client))
        return qcc_FALSE;
    if (qcc_r == qcc_RANGE_NEAR)
    {
        if (((int) get_qcc_show_hostile(PROG_TO_EDICT(qcc_client)) < progs.qcc_time) && ((int) !qcc_infront(qcc_client)))
            return qcc_FALSE;
    }
    else
        if (qcc_r == qcc_RANGE_MID)
        {
/* client.show_hostile < time || */            if (!qcc_infront(qcc_client))
                return qcc_FALSE;
//
// got one
//
        }
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_client);
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player)))
    {
        set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), get_qcc_enemy(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))));
        if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player)))
        {
            set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_world);
            return qcc_FALSE;
        }
    }
    qcc_FoundTarget();
    return qcc_TRUE;
//=============================================================================
}
void qcc_ai_forward(float qcc_dist)
{
    qcc_walkmove(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y, qcc_dist);
}
void qcc_ai_back(float qcc_dist)
{
    qcc_walkmove(( get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + 180 ), qcc_dist);
/*
=============
ai_pain

stagger back a bit
=============
*/}
void qcc_ai_pain(float qcc_dist)
{
    qcc_ai_back(qcc_dist)/*
	local float	away;
	
	away = anglemod (vectoyaw (self.origin - self.enemy.origin) 
	+ 180*(random()- 0.5) );
	
	walkmove (away, dist);
*/;
/*
=============
ai_painforward

stagger back a bit
=============
*/}
void qcc_ai_painforward(float qcc_dist)
{
    qcc_walkmove(get_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self)), qcc_dist);
/*
=============
ai_walk

The monster is walking it's beat
=============
*/}
void qcc_ai_walk(float qcc_dist)
{
    vector qcc_mtemp;
    progs.qcc_movedist = qcc_dist;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), monster_dragon_string_index))
    {
        qcc_movetogoal(qcc_dist);
        return;
// check for noticing a player
    }
    if (qcc_FindTarget())
        return;
    qcc_movetogoal(qcc_dist);
/*
=============
ai_stand

The monster is staying in one place for a while, with slight angle turns
=============
*/}
void qcc_ai_stand(void)
{
    if (qcc_FindTarget())
        return;
    if (progs.qcc_time > get_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self)))
    {
        ((void (*)() )getFunction(get_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self))))();
        return;
// change angle slightly
    }
/*
=============
ai_turn

don't move, but turn towards ideal_yaw
=============
*/}
void qcc_ai_turn(void)
{
    if (qcc_FindTarget())
        return;
    qcc_ChangeYaw();
//=============================================================================
/*
=============
ChooseTurn
=============
*/}
void qcc_ChooseTurn(vector qcc_dest3)
{
    vector qcc_dir,     qcc_newdir;
    qcc_dir = vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), qcc_dest3);
    qcc_newdir.x = progs.qcc_trace_plane_normal.y;
    qcc_newdir.y = 0 - progs.qcc_trace_plane_normal.x;
    qcc_newdir.z = 0;
    if (dotProduct(qcc_dir, qcc_newdir) > 0)
    {
        qcc_dir.x = 0 - progs.qcc_trace_plane_normal.y;
        qcc_dir.y = progs.qcc_trace_plane_normal.x;
    }
    else
    {
        qcc_dir.x = progs.qcc_trace_plane_normal.y;
        qcc_dir.y = 0 - progs.qcc_trace_plane_normal.x;
    }
    qcc_dir.z = 0;
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(qcc_dir));
/*
============
FacingIdeal

============
*/}
float qcc_FacingIdeal(void)
{
    float qcc_delta;
    qcc_delta = qcc_anglemod(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y - get_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self)));
    if (((int) qcc_delta > 45) && ((int) qcc_delta < 315))
        return qcc_FALSE;
    return qcc_TRUE;
//=============================================================================
}
float qcc_WizardCheckAttack(void);
float qcc_DogCheckAttack(void);
float qcc_CheckAnyAttack(void)
{
    if (!progs.qcc_enemy_vis)
// WAS MISSING
        return qcc_FALSE;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_army))
        return qcc_SoldierCheckAttack();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_ogre))
        return qcc_OgreCheckAttack();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_shambler))
        return qcc_ShamCheckAttack();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_demon1))
        return qcc_DemonCheckAttack();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_dog))
        return qcc_DogCheckAttack();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_wizard))
        return qcc_WizardCheckAttack();
    return qcc_CheckAttack();
/*
=============
ai_run_melee

Turn and close until within an angle to launch a melee attack
=============
*/}
void qcc_ai_run_melee(void)
{
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), progs.qcc_enemy_yaw);
    qcc_ChangeYaw();
    if (qcc_FacingIdeal())
    {
        ((void (*)() )getFunction(get_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self))))();
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
    }
/*
=============
ai_run_missile

Turn in place until within an angle to launch a missile attack
=============
*/}
void qcc_ai_run_missile(void)
{
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), progs.qcc_enemy_yaw);
    qcc_ChangeYaw();
    if (qcc_FacingIdeal())
    {
        ((void (*)() )getFunction(get_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self))))();
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
    }
/*
=============
ai_run_slide

Strafe sideways, but stay at aproximately the same range
=============
*/}
void qcc_ai_run_slide(void)
{
    float qcc_ofs;
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), progs.qcc_enemy_yaw);
    qcc_ChangeYaw();
    if (get_qcc_lefty(PROG_TO_EDICT(progs.qcc_self)))
        qcc_ofs = 90;
    else
        qcc_ofs = -90;
    if (qcc_walkmove(get_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self)) + qcc_ofs, progs.qcc_movedist))
        return;
    set_qcc_lefty(PROG_TO_EDICT(progs.qcc_self), 1 - get_qcc_lefty(PROG_TO_EDICT(progs.qcc_self)));
    qcc_walkmove(get_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self)) - qcc_ofs, progs.qcc_movedist);
/*
=============
ai_run

The monster has an enemy it is trying to kill
=============
*/}
void qcc_ai_run(float qcc_dist)
{
    vector qcc_delta;
    float qcc_axis;
    float qcc_direct,     qcc_ang_rint,     qcc_ang_floor,     qcc_ang_ceil;
    progs.qcc_movedist = qcc_dist// see if the enemy is dead
;
    if (get_qcc_health(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))) <= 0)
    {
        set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_world)// FIXME: look all around for other targets
;
        if (get_qcc_health(PROG_TO_EDICT(get_qcc_oldenemy(PROG_TO_EDICT(progs.qcc_self)))) > 0)
        {
            set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), get_qcc_oldenemy(PROG_TO_EDICT(progs.qcc_self)));
            qcc_HuntTarget();
        }
        else
        {
            if (get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self)))
                ((void (*)() )getFunction(get_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self))))();
            else
                ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
            return;
        }
    }
    set_qcc_show_hostile(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1)// wake up other monsters
// check knowledge of enemy
;
    progs.qcc_enemy_vis = qcc_visible(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    if (progs.qcc_enemy_vis)
        set_qcc_search_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 5)// look for other coop players
;
    if (((int) progs.qcc_coop) && ((int) get_qcc_search_time(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time))
    {
        if (qcc_FindTarget())
            return;
    }
    progs.qcc_enemy_infront = qcc_infront(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    progs.qcc_enemy_range = qcc_range(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    progs.qcc_enemy_yaw = qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_AS_MISSILE)
//dprint ("ai_run_missile\n");
    {
        qcc_ai_run_missile();
        return;
    }
    if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_AS_MELEE)
//dprint ("ai_run_melee\n");
    {
        qcc_ai_run_melee();
        return;
    }
    if (qcc_CheckAnyAttack())
// beginning an attack
        return;
    if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_AS_SLIDING)
    {
        qcc_ai_run_slide();
        return;
// head straight in
    }
    qcc_movetogoal(qcc_dist)// done in C code...
;
//File: combat.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
void qcc_T_MissileTouch(void);
void qcc_info_player_start(void);
void qcc_ClientObituary(int , int );
//============================================================================
/*
============
CanDamage

Returns true if the inflictor can directly damage the target.  Used for
explosions and melee attacks.
============
*/void qcc_monster_death_use(void);
float qcc_CanDamage(int qcc_targ, int qcc_inflictor)
{
// bmodels need special checking because their origin is 0,0,0
    if (get_qcc_movetype(PROG_TO_EDICT(qcc_targ)) == qcc_MOVETYPE_PUSH)
    {
        qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), floatMulVector(0.5f, ( vectorAdd(get_qcc_absmin(PROG_TO_EDICT(qcc_targ)), get_qcc_absmax(PROG_TO_EDICT(qcc_targ))) )), qcc_TRUE, progs.qcc_self);
        if (progs.qcc_trace_fraction == 1)
            return qcc_TRUE;
        if (progs.qcc_trace_ent == qcc_targ)
            return qcc_TRUE;
        return qcc_FALSE;
    }
    qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), get_qcc_origin(PROG_TO_EDICT(qcc_targ)), qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), (vector)  {{15.0000f, 15.0000f, 0.000000f}}), qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), (vector)  {{-15.0000f, -15.0000f, 0.000000f}}), qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), (vector)  {{-15.0000f, 15.0000f, 0.000000f}}), qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    qcc_traceline(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), (vector)  {{15.0000f, -15.0000f, 0.000000f}}), qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return qcc_TRUE;
    return qcc_FALSE;
/*
============
Killed
============
*/}
void qcc_Killed(int qcc_targ, int qcc_attacker)
{
    int qcc_oself;
    qcc_oself = progs.qcc_self;
    progs.qcc_self = qcc_targ;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -99)
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), -99)// don't let sbar look bad if a player
;
    if (((int) get_qcc_movetype(PROG_TO_EDICT(progs.qcc_self)) == qcc_MOVETYPE_PUSH) || ((int) get_qcc_movetype(PROG_TO_EDICT(progs.qcc_self)) == qcc_MOVETYPE_NONE))
// doors, triggers, etc
    {
        ((void (*)() )getFunction(get_qcc_th_die(PROG_TO_EDICT(progs.qcc_self))))();
        progs.qcc_self = qcc_oself;
        return;
    }
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_attacker)// bump the monster counter
;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_MONSTER)))
    {
        progs.qcc_killed_monsters = progs.qcc_killed_monsters + 1;
        qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_KILLEDMONSTER);
    }
    qcc_ClientObituary(progs.qcc_self, qcc_attacker);
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    qcc_monster_death_use();
    ((void (*)() )getFunction(get_qcc_th_die(PROG_TO_EDICT(progs.qcc_self))))();
    progs.qcc_self = qcc_oself;
/*
============
T_Damage

The damage is coming from inflictor, but get mad at attacker
This should be the only function that ever reduces health.
============
*/}
void qcc_T_Damage(int qcc_targ, int qcc_inflictor, int qcc_attacker, float qcc_damage)
{
    vector qcc_dir;
    int qcc_oldself;
    float qcc_save;
    float qcc_take;
    if (!get_qcc_takedamage(PROG_TO_EDICT(qcc_targ)))
// used by buttons and triggers to set activator for target firing
        return;
    progs.qcc_damage_attacker = qcc_attacker// check for quad damage powerup on the attacker
;
    if (get_qcc_super_damage_finished(PROG_TO_EDICT(qcc_attacker)) > progs.qcc_time)
        qcc_damage = qcc_damage * 4// save damage based on the target's armor level
;
    qcc_save = qcc_ceil(get_qcc_armortype(PROG_TO_EDICT(qcc_targ)) * qcc_damage);
    if (qcc_save >= get_qcc_armorvalue(PROG_TO_EDICT(qcc_targ)))
    {
        qcc_save = get_qcc_armorvalue(PROG_TO_EDICT(qcc_targ));
        set_qcc_armortype(PROG_TO_EDICT(qcc_targ), 0)// lost all armor
;
        set_qcc_items(PROG_TO_EDICT(qcc_targ), get_qcc_items(PROG_TO_EDICT(qcc_targ)) - ( (((int) get_qcc_items(PROG_TO_EDICT(qcc_targ))) & ((int) ( (((int) (((int) qcc_IT_ARMOR1) | ((int) qcc_IT_ARMOR2))) | ((int) qcc_IT_ARMOR3)) ))) ));
    }
    set_qcc_armorvalue(PROG_TO_EDICT(qcc_targ), get_qcc_armorvalue(PROG_TO_EDICT(qcc_targ)) - qcc_save);
    qcc_take = qcc_ceil(qcc_damage - qcc_save)// add to the damage total for clients, which will be sent as a single
// message at the end of the frame
// FIXME: remove after combining shotgun blasts?
;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(qcc_targ))) & ((int) qcc_FL_CLIENT)))
    {
        set_qcc_dmg_take(PROG_TO_EDICT(qcc_targ), get_qcc_dmg_take(PROG_TO_EDICT(qcc_targ)) + qcc_take);
        set_qcc_dmg_save(PROG_TO_EDICT(qcc_targ), get_qcc_dmg_save(PROG_TO_EDICT(qcc_targ)) + qcc_save);
        set_qcc_dmg_inflictor(PROG_TO_EDICT(qcc_targ), qcc_inflictor);
// figure momentum add
    }
    if (((int) ( qcc_inflictor != progs.qcc_world )) && ((int) ( get_qcc_movetype(PROG_TO_EDICT(qcc_targ)) == qcc_MOVETYPE_WALK )))
    {
        qcc_dir = vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), vectorMulFloat(( vectorAdd(get_qcc_absmin(PROG_TO_EDICT(qcc_inflictor)), get_qcc_absmax(PROG_TO_EDICT(qcc_inflictor))) ), 0.5f));
        qcc_dir = qcc_normalize(qcc_dir);
        set_qcc_velocity(PROG_TO_EDICT(qcc_targ), vectorAdd(get_qcc_velocity(PROG_TO_EDICT(qcc_targ)), vectorMulFloat(vectorMulFloat(qcc_dir, qcc_damage), 8)));
// check for godmode or invincibility
    }
    if ((((int) get_qcc_flags(PROG_TO_EDICT(qcc_targ))) & ((int) qcc_FL_GODMODE)))
        return;
    if (get_qcc_invincible_finished(PROG_TO_EDICT(qcc_targ)) >= progs.qcc_time)
    {
        if (get_qcc_invincible_sound(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
            qcc_sound(qcc_targ, qcc_CHAN_ITEM, items_protect3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
            set_qcc_invincible_sound(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
        }
        return;
// team play damage avoidance
    }
    if (((int) ((int) ( progs.qcc_teamplay == 1 )) && ((int) ( get_qcc_team(PROG_TO_EDICT(qcc_targ)) > 0 ))) && ((int) ( get_qcc_team(PROG_TO_EDICT(qcc_targ)) == get_qcc_team(PROG_TO_EDICT(qcc_attacker)) )))
// do the damage
        return;
    set_qcc_health(PROG_TO_EDICT(qcc_targ), get_qcc_health(PROG_TO_EDICT(qcc_targ)) - qcc_take);
    if (get_qcc_health(PROG_TO_EDICT(qcc_targ)) <= 0)
    {
        qcc_Killed(qcc_targ, qcc_attacker);
        return;
// react to the damage
    }
    qcc_oldself = progs.qcc_self;
    progs.qcc_self = qcc_targ;
    if (((int) ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_MONSTER)) )) && ((int) qcc_attacker != progs.qcc_world))
// get mad unless of the same class (except for soldiers)
    {
        if (((int) progs.qcc_self != qcc_attacker) && ((int) qcc_attacker != get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        {
            if (((int) ( (!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), get_qcc_classname(PROG_TO_EDICT(qcc_attacker)))) )) || ((int) ( areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_army) )))
            {
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player))
                    set_qcc_oldenemy(PROG_TO_EDICT(progs.qcc_self), get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
                set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_attacker);
                qcc_FoundTarget();
            }
        }
    }
    if (get_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self)))
    {
        ((void (*)(int,float) )getFunction(get_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self))))(qcc_attacker, qcc_take)// nightmare mode monsters don't go into pain frames often
;
        if (progs.qcc_skill == 3)
            set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 5);
    }
    progs.qcc_self = qcc_oldself;
/*
============
T_RadiusDamage
============
*/}
void qcc_T_RadiusDamage(int qcc_inflictor, int qcc_attacker, float qcc_damage, int qcc_ignore)
{
    float qcc_points;
    int qcc_head;
    vector qcc_org;
    qcc_head = qcc_findradius(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), qcc_damage + 40);
    while (qcc_head)
    {
        if (qcc_head != qcc_ignore)
        {
            if (get_qcc_takedamage(PROG_TO_EDICT(qcc_head)))
            {
                qcc_org = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_head)), vectorMulFloat(( vectorAdd(get_qcc_mins(PROG_TO_EDICT(qcc_head)), get_qcc_maxs(PROG_TO_EDICT(qcc_head))) ), 0.5f));
                qcc_points = 0.5f * qcc_vlen(vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_inflictor)), qcc_org));
                if (qcc_points < 0)
                    qcc_points = 0;
                qcc_points = qcc_damage - qcc_points;
                if (qcc_head == qcc_attacker)
                    qcc_points = qcc_points * 0.5f;
                if (qcc_points > 0)
                {
                    if (qcc_CanDamage(qcc_head, qcc_inflictor))
// shambler takes half damage from all explosions
                    {
                        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_head)), qcc_classname_monster_shambler))
                            qcc_T_Damage(qcc_head, qcc_inflictor, qcc_attacker, qcc_points * 0.5f);
                        else
                            qcc_T_Damage(qcc_head, qcc_inflictor, qcc_attacker, qcc_points);
                    }
                }
            }
        }
        qcc_head = get_qcc_chain(PROG_TO_EDICT(qcc_head));
    }
/*
============
T_BeamDamage
============
*/}
void qcc_T_BeamDamage(int qcc_attacker, float qcc_damage)
{
    float qcc_points;
    int qcc_head;
    qcc_head = qcc_findradius(get_qcc_origin(PROG_TO_EDICT(qcc_attacker)), qcc_damage + 40);
    while (qcc_head)
    {
        if (get_qcc_takedamage(PROG_TO_EDICT(qcc_head)))
        {
            qcc_points = 0.5f * qcc_vlen(vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_attacker)), get_qcc_origin(PROG_TO_EDICT(qcc_head))));
            if (qcc_points < 0)
                qcc_points = 0;
            qcc_points = qcc_damage - qcc_points;
            if (qcc_head == qcc_attacker)
                qcc_points = qcc_points * 0.5f;
            if (qcc_points > 0)
            {
                if (qcc_CanDamage(qcc_head, qcc_attacker))
                {
                    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_head)), qcc_classname_monster_shambler))
                        qcc_T_Damage(qcc_head, qcc_attacker, qcc_attacker, qcc_points * 0.5f);
                    else
                        qcc_T_Damage(qcc_head, qcc_attacker, qcc_attacker, qcc_points);
                }
            }
        }
        qcc_head = get_qcc_chain(PROG_TO_EDICT(qcc_head));
    }
//File: items.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
/* ALL LIGHTS SHOULD BE 0 1 0 IN COLOR ALL OTHER ITEMS SHOULD
BE .8 .3 .4 IN COLOR */void qcc_W_SetCurrentAmmo(void);
void qcc_SUB_regen(void)
{
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), get_qcc_mdl(PROG_TO_EDICT(progs.qcc_self)))// restore original model
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER)// allow it to be touched again
;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, items_itembk2_wav_string_index, 1.00000f, qcc_ATTN_NORM)// play respawn sound
;
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED noclass (0 0 0) (-8 -8 -8) (8 8 8)
prints a warning message when spawned
*/}
void qcc_noclass(void)
{
    qcc_dprint(noclass_spawned_at_string_index);
    qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_dprint(_n__string_index);
    qcc_remove(progs.qcc_self);
/*
============
PlaceItem

plants the object on the floor
============
*/}
void qcc_PlaceItem(void)
{
    float qcc_oldz;
    set_qcc_mdl(PROG_TO_EDICT(progs.qcc_self), get_qcc_model(PROG_TO_EDICT(progs.qcc_self)))// so it can be restored on respawn
;
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), qcc_FL_ITEM)// make extra wide
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_TOSS);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 6);
    qcc_oldz = get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z;
    if (!qcc_droptofloor())
    {
        qcc_dprint(Bonus_item_fell_out_of_level_at__string_index);
        qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_dprint(_n__string_index);
        qcc_remove(progs.qcc_self);
        return;
    }
/*
============
StartItem

Sets the clipping size and plants the object on the floor
============
*/}
void qcc_StartItem(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f)// items start after other solids
;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_PlaceItem));
/*
=========================================================================

HEALTH BOX

=========================================================================
*///
// T_Heal: add health to an entity, limiting health to max_health
// "ignore" will ignore max_health limit
//
}
float qcc_T_Heal(int qcc_e, float qcc_healamount, float qcc_ignore)
{
    if (get_qcc_health(PROG_TO_EDICT(qcc_e)) <= 0)
        return 0.000000f;
    if (((int) ( !qcc_ignore )) && ((int) ( get_qcc_health(PROG_TO_EDICT(qcc_e)) >= get_qcc_max_health(PROG_TO_EDICT(progs.qcc_other)) )))
        return 0.000000f;
    qcc_healamount = qcc_ceil(qcc_healamount);
    set_qcc_health(PROG_TO_EDICT(qcc_e), get_qcc_health(PROG_TO_EDICT(qcc_e)) + qcc_healamount);
    if (((int) ( !qcc_ignore )) && ((int) ( get_qcc_health(PROG_TO_EDICT(qcc_e)) >= get_qcc_max_health(PROG_TO_EDICT(progs.qcc_other)) )))
        set_qcc_health(PROG_TO_EDICT(qcc_e), get_qcc_max_health(PROG_TO_EDICT(progs.qcc_other)));
    if (get_qcc_health(PROG_TO_EDICT(qcc_e)) > 250)
        set_qcc_health(PROG_TO_EDICT(qcc_e), 250);
    return 1.00000f;
/*QUAKED item_health (.3 .3 1) (0 0 0) (32 32 32) rotten megahealth
Health box. Normally gives 25 points.
Rotten box heals 5-10 points,
megahealth will add 100 health, then 
rot you down to your maximum health limit, 
one point per second.
*/}
const float qcc_H_ROTTEN = 1;
const float qcc_H_MEGA = 2;
void qcc_health_touch(void);
void qcc_item_megahealth_rot(void);
void qcc_item_health(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_health_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_H_ROTTEN)))
    {
        qcc_precache_model(maps_b_bh10_bsp_string_index);
        qcc_precache_sound(items_r_item1_wav_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_bh10_bsp_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_r_item1_wav_string_index);
        set_qcc_healamount(PROG_TO_EDICT(progs.qcc_self), 15);
        set_qcc_healtype(PROG_TO_EDICT(progs.qcc_self), 0);
    }
    else
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_H_MEGA)))
        {
            qcc_precache_model(maps_b_bh100_bsp_string_index);
            qcc_precache_sound(items_r_item2_wav_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_bh100_bsp_string_index);
            set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_r_item2_wav_string_index);
            set_qcc_healamount(PROG_TO_EDICT(progs.qcc_self), 100);
            set_qcc_healtype(PROG_TO_EDICT(progs.qcc_self), 2);
        }
        else
        {
            qcc_precache_model(maps_b_bh25_bsp_string_index);
            qcc_precache_sound(items_health1_wav_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_bh25_bsp_string_index);
            set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_health1_wav_string_index);
            set_qcc_healamount(PROG_TO_EDICT(progs.qcc_self), 25);
            set_qcc_healtype(PROG_TO_EDICT(progs.qcc_self), 1);
        }
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
}
void qcc_health_touch(void)
{
    float qcc_amount;
    uint16_t qcc_s;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
// Megahealth?  Ignore max_health...
    if (get_qcc_healtype(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) >= 250)
            return;
        if (!qcc_T_Heal(progs.qcc_other, get_qcc_healamount(PROG_TO_EDICT(progs.qcc_self)), 1.00000f))
            return;
    }
    else
    {
        if (!qcc_T_Heal(progs.qcc_other, get_qcc_healamount(PROG_TO_EDICT(progs.qcc_self)), 0.000000f))
            return;
    }
    qcc_sprint(progs.qcc_other, You_receive__string_index);
    qcc_s = qcc_ftos(get_qcc_healamount(PROG_TO_EDICT(progs.qcc_self)));
    qcc_sprint(progs.qcc_other, qcc_s);
    qcc_sprint(progs.qcc_other, _health_n__string_index)// health touch sound
;
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT)// Megahealth = rot down the player's super health
;
    if (get_qcc_healtype(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        set_qcc_items(PROG_TO_EDICT(progs.qcc_other), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) | ((int) qcc_IT_SUPERHEALTH)));
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 5);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_item_megahealth_rot));
        set_qcc_owner(PROG_TO_EDICT(progs.qcc_self), progs.qcc_other);
    }
    else
    {
// deathmatch 2 is the silly old rules
        if (progs.qcc_deathmatch != 2)
        {
            if (progs.qcc_deathmatch)
                set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 20);
            set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
        }
    }
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
}
void qcc_item_megahealth_rot(void)
{
    progs.qcc_other = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) > get_qcc_max_health(PROG_TO_EDICT(progs.qcc_other)))
    {
        set_qcc_health(PROG_TO_EDICT(progs.qcc_other), get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) - 1);
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
        return;
// it is possible for a player to die and respawn between rots, so don't
// just blindly subtract the flag off
    }
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), get_qcc_items(PROG_TO_EDICT(progs.qcc_other)) - ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_SUPERHEALTH)) ));
// deathmatch 2 is silly old rules
    if (progs.qcc_deathmatch == 1)
    {
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 20);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
    }
/*
===============================================================================

ARMOR

===============================================================================
*/}
void qcc_armor_touch(void);
void qcc_armor_touch(void)
{
    float qcc_type,     qcc_value,     qcc_bit;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_armor1))
    {
        qcc_type = 0.3f;
        qcc_value = 100;
        qcc_bit = qcc_IT_ARMOR1;
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_armor2))
    {
        qcc_type = 0.6f;
        qcc_value = 150;
        qcc_bit = qcc_IT_ARMOR2;
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_armorInv))
    {
        qcc_type = 0.8f;
        qcc_value = 200;
        qcc_bit = qcc_IT_ARMOR3;
    }
    if (get_qcc_armortype(PROG_TO_EDICT(progs.qcc_other)) * get_qcc_armorvalue(PROG_TO_EDICT(progs.qcc_other)) >= qcc_type * qcc_value)
        return;
    set_qcc_armortype(PROG_TO_EDICT(progs.qcc_other), qcc_type);
    set_qcc_armorvalue(PROG_TO_EDICT(progs.qcc_other), qcc_value);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), get_qcc_items(PROG_TO_EDICT(progs.qcc_other)) - ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) ( (((int) (((int) qcc_IT_ARMOR1) | ((int) qcc_IT_ARMOR2))) | ((int) qcc_IT_ARMOR3)) ))) ) + qcc_bit);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    if (progs.qcc_deathmatch == 1)
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 20);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
    qcc_sprint(progs.qcc_other, You_got_armor_n__string_index)// armor touch sound
;
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, items_armor1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
/*QUAKED item_armor1 (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_item_armor1(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_armor_touch));
    qcc_precache_model(progs_armor_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_armor_mdl_string_index);
    set_qcc_skin(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_armor2 (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_item_armor2(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_armor_touch));
    qcc_precache_model(progs_armor_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_armor_mdl_string_index);
    set_qcc_skin(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_armorInv (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_item_armorInv(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_armor_touch));
    qcc_precache_model(progs_armor_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_armor_mdl_string_index);
    set_qcc_skin(PROG_TO_EDICT(progs.qcc_self), 2);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*
===============================================================================

WEAPONS

===============================================================================
*/}
void qcc_bound_other_ammo(void)
{
    if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other)) > 100)
        set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other), 100);
    if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) > 200)
        set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other), 200);
    if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) > 100)
        set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other), 100);
    if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other)) > 100)
        set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other), 100);
}
float qcc_RankForWeapon(float qcc_w)
{
    if (qcc_w == qcc_IT_LIGHTNING)
        return 1.00000f;
    if (qcc_w == qcc_IT_ROCKET_LAUNCHER)
        return 2.00000f;
    if (qcc_w == qcc_IT_SUPER_NAILGUN)
        return 3.00000f;
    if (qcc_w == qcc_IT_GRENADE_LAUNCHER)
        return 4.00000f;
    if (qcc_w == qcc_IT_SUPER_SHOTGUN)
        return 5.00000f;
    if (qcc_w == qcc_IT_NAILGUN)
        return 6.00000f;
    return 7.00000f;
/*
=============
Deathmatch_Weapon

Deathmatch weapon change rules for picking up a weapon

.float		ammo_shells, ammo_nails, ammo_rockets, ammo_cells;
=============
*/}
void qcc_Deathmatch_Weapon(float qcc_old, float qcc_new)
{
    float qcc_or,     qcc_nr// change self.weapon if desired
;
    qcc_or = qcc_RankForWeapon(get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)));
    qcc_nr = qcc_RankForWeapon(qcc_new);
    if (qcc_nr < qcc_or)
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_new);
/*
=============
weapon_touch
=============
*/}
float qcc_W_BestWeapon(void);
void qcc_weapon_touch(void)
{
    float qcc_hadammo,     qcc_best,     qcc_new,     qcc_old;
    int qcc_stemp;
    float qcc_leave;
    qcc_new = get_qcc_items(PROG_TO_EDICT(progs.qcc_other));
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_FL_CLIENT)) ))
// if the player was using his best weapon, change up to the new one if better
        return;
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    qcc_best = qcc_W_BestWeapon();
    progs.qcc_self = qcc_stemp;
    if (((int) progs.qcc_deathmatch == 2) || ((int) progs.qcc_coop))
        qcc_leave = 1;
    else
        qcc_leave = 0;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_nailgun))
    {
        if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_NAILGUN)) )))
            return;
        qcc_hadammo = get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other));
        qcc_new = qcc_IT_NAILGUN;
        set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) + 30);
    }
    else
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_supernailgun))
        {
            if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_SUPER_NAILGUN)) )))
                return;
            qcc_hadammo = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other));
            qcc_new = qcc_IT_SUPER_NAILGUN;
            set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) + 30);
        }
        else
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_supershotgun))
            {
                if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_SUPER_SHOTGUN)) )))
                    return;
                qcc_hadammo = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other));
                qcc_new = qcc_IT_SUPER_SHOTGUN;
                set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other)) + 5);
            }
            else
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_rocketlauncher))
                {
                    if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_ROCKET_LAUNCHER)) )))
                        return;
                    qcc_hadammo = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other));
                    qcc_new = qcc_IT_ROCKET_LAUNCHER;
                    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) + 5);
                }
                else
                    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_grenadelauncher))
                    {
                        if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_GRENADE_LAUNCHER)) )))
                            return;
                        qcc_hadammo = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other));
                        qcc_new = qcc_IT_GRENADE_LAUNCHER;
                        set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) + 5);
                    }
                    else
                        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_weapon_lightning))
                        {
                            if (((int) qcc_leave) && ((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_IT_LIGHTNING)) )))
                                return;
                            qcc_hadammo = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other));
                            qcc_new = qcc_IT_LIGHTNING;
                            set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other)) + 15);
                        }
                        else
                            qcc_objerror(weapon_touch__unknown_classname_string_index);
    qcc_sprint(progs.qcc_other, You_got_the__string_index);
    qcc_sprint(progs.qcc_other, get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_sprint(progs.qcc_other, _n__string_index)// weapon touch sound
;
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, weapons_pkup_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    qcc_bound_other_ammo()// change to the weapon
;
    qcc_old = get_qcc_items(PROG_TO_EDICT(progs.qcc_other));
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) | ((int) qcc_new)));
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    if (!progs.qcc_deathmatch)
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_new);
    else
        qcc_Deathmatch_Weapon(qcc_old, qcc_new);
    qcc_W_SetCurrentAmmo();
    progs.qcc_self = qcc_stemp;
    if (qcc_leave)
// remove it in single player, or setup for respawning in deathmatch
        return;
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    if (progs.qcc_deathmatch == 1)
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 30);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
/*QUAKED weapon_supershotgun (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_supershotgun(void)
{
    qcc_precache_model(progs_g_shot_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_shot_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SUPER_SHOTGUN);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Double_barrelled_Shotgun_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED weapon_nailgun (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_nailgun(void)
{
    qcc_precache_model(progs_g_nail_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_nail_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_NAILGUN);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), nailgun_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED weapon_supernailgun (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_supernailgun(void)
{
    qcc_precache_model(progs_g_nail2_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_nail2_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SUPER_NAILGUN);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Super_Nailgun_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED weapon_grenadelauncher (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_grenadelauncher(void)
{
    qcc_precache_model(progs_g_rock_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_rock_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 3);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Grenade_Launcher_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED weapon_rocketlauncher (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_rocketlauncher(void)
{
    qcc_precache_model(progs_g_rock2_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_rock2_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 3);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Rocket_Launcher_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED weapon_lightning (0 .5 .8) (-16 -16 0) (16 16 32)
*/}
void qcc_weapon_lightning(void)
{
    qcc_precache_model(progs_g_light_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_g_light_mdl_string_index);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 3);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Thunderbolt_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_weapon_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    qcc_StartItem();
/*
===============================================================================

AMMO

===============================================================================
*/}
void qcc_ammo_touch(void)
{
    int qcc_stemp;
    float qcc_best;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
// if the player was using his best weapon, change up to the new one if better		
        return;
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    qcc_best = qcc_W_BestWeapon();
    progs.qcc_self = qcc_stemp// shotgun
;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other)) >= 100)
            return;
        set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_aflag(PROG_TO_EDICT(progs.qcc_self)));
// spikes
    }
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) >= 200)
            return;
        set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_aflag(PROG_TO_EDICT(progs.qcc_self)));
//	rockets
    }
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == 3)
    {
        if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) >= 100)
            return;
        set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_aflag(PROG_TO_EDICT(progs.qcc_self)));
//	cells
    }
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == 4)
    {
        if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other)) >= 200)
            return;
        set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_aflag(PROG_TO_EDICT(progs.qcc_self)));
    }
    qcc_bound_other_ammo();
    qcc_sprint(progs.qcc_other, You_got_the__string_index);
    qcc_sprint(progs.qcc_other, get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_sprint(progs.qcc_other, _n__string_index)// ammo touch sound
;
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, weapons_lock4_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index)// change to a better weapon if appropriate
;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_other)) == qcc_best)
    {
        qcc_stemp = progs.qcc_self;
        progs.qcc_self = progs.qcc_other;
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_W_BestWeapon());
        qcc_W_SetCurrentAmmo();
        progs.qcc_self = qcc_stemp;
// if changed current ammo, update it
    }
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    qcc_W_SetCurrentAmmo();
    progs.qcc_self = qcc_stemp// remove it in single player, or setup for respawning in deathmatch
;
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    if (progs.qcc_deathmatch == 1)
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 30);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
}
const float qcc_WEAPON_BIG2 = 1/*QUAKED item_shells (0 .5 .8) (0 0 0) (32 32 32) big
*/;
void qcc_item_shells(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ammo_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG2)))
    {
        qcc_precache_model(maps_b_shell1_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_shell1_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 40);
    }
    else
    {
        qcc_precache_model(maps_b_shell0_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_shell0_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 20);
    }
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), shells_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_spikes (0 .5 .8) (0 0 0) (32 32 32) big
*/}
void qcc_item_spikes(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ammo_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG2)))
    {
        qcc_precache_model(maps_b_nail1_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_nail1_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 50);
    }
    else
    {
        qcc_precache_model(maps_b_nail0_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_nail0_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 25);
    }
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 2);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), nails_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_rockets (0 .5 .8) (0 0 0) (32 32 32) big
*/}
void qcc_item_rockets(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ammo_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG2)))
    {
        qcc_precache_model(maps_b_rock1_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_rock1_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 10);
    }
    else
    {
        qcc_precache_model(maps_b_rock0_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_rock0_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 5);
    }
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 3);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), rockets_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_cells (0 .5 .8) (0 0 0) (32 32 32) big
*/}
void qcc_item_cells(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ammo_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG2)))
    {
        qcc_precache_model(maps_b_batt1_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_batt1_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 12);
    }
    else
    {
        qcc_precache_model(maps_b_batt0_bsp_string_index);
        qcc_setmodel(progs.qcc_self, maps_b_batt0_bsp_string_index);
        set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 6);
    }
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 4);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), cells_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
/*QUAKED item_weapon (0 .5 .8) (0 0 0) (32 32 32) shotgun rocket spikes big
DO NOT USE THIS!!!! IT WILL BE REMOVED!
*/}
const float qcc_WEAPON_SHOTGUN = 1;
const float qcc_WEAPON_ROCKET = 2;
const float qcc_WEAPON_SPIKES = 4;
const float qcc_WEAPON_BIG = 8;
void qcc_item_weapon(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ammo_touch));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_SHOTGUN)))
    {
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG)))
        {
            qcc_precache_model(maps_b_shell1_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_shell1_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 40);
        }
        else
        {
            qcc_precache_model(maps_b_shell0_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_shell0_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 20);
        }
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 1);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), shells_string_index);
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_SPIKES)))
    {
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG)))
        {
            qcc_precache_model(maps_b_nail1_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_nail1_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 40);
        }
        else
        {
            qcc_precache_model(maps_b_nail0_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_nail0_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 20);
        }
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 2);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), spikes_string_index);
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_ROCKET)))
    {
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_WEAPON_BIG)))
        {
            qcc_precache_model(maps_b_rock1_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_rock1_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 10);
        }
        else
        {
            qcc_precache_model(maps_b_rock0_bsp_string_index);
            qcc_setmodel(progs.qcc_self, maps_b_rock0_bsp_string_index);
            set_qcc_aflag(PROG_TO_EDICT(progs.qcc_self), 5);
        }
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), 3);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), rockets_string_index);
    }
    qcc_setsize(progs.qcc_self, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{32.0000f, 32.0000f, 56.0000f}});
    qcc_StartItem();
/*
===============================================================================

KEYS

===============================================================================
*/}
void qcc_key_touch(void)
{
    int qcc_stemp;
    float qcc_best;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    if ((((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) & ((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))))
        return;
    qcc_sprint(progs.qcc_other, You_got_the__string_index);
    qcc_sprint(progs.qcc_other, get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_sprint(progs.qcc_other, _n__string_index);
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) | ((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))));
    if (!progs.qcc_coop)
    {
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
        set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    }
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
}
void qcc_key_setsounds(void)
{
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
    {
        qcc_precache_sound(misc_medkey_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_medkey_wav_string_index);
    }
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
    {
        qcc_precache_sound(misc_runekey_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_runekey_wav_string_index);
    }
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
    {
        qcc_precache_sound2(misc_basekey_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_basekey_wav_string_index);
    }
/*QUAKED item_key1 (0 .5 .8) (-16 -16 -24) (16 16 32)
SILVER key
In order for keys to work
you MUST set your maps
worldtype to one of the
following:
0: medieval
1: metal
2: base
*/}
void qcc_item_key1(void)
{
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
    {
        qcc_precache_model(progs_w_s_key_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_w_s_key_mdl_string_index);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), silver_key_string_index);
    }
    else
        if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
        {
            qcc_precache_model(progs_m_s_key_mdl_string_index);
            qcc_setmodel(progs.qcc_self, progs_m_s_key_mdl_string_index);
            set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), silver_runekey_string_index);
        }
        else
            if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
            {
                qcc_precache_model2(progs_b_s_key_mdl_string_index);
                qcc_setmodel(progs.qcc_self, progs_b_s_key_mdl_string_index);
                set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), silver_keycard_string_index);
            }
    qcc_key_setsounds();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_key_touch));
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_KEY1);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*QUAKED item_key2 (0 .5 .8) (-16 -16 -24) (16 16 32)
GOLD key
In order for keys to work
you MUST set your maps
worldtype to one of the
following:
0: medieval
1: metal
2: base
*/}
void qcc_item_key2(void)
{
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
    {
        qcc_precache_model(progs_w_g_key_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_w_g_key_mdl_string_index);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), gold_key_string_index);
    }
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
    {
        qcc_precache_model(progs_m_g_key_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_m_g_key_mdl_string_index);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), gold_runekey_string_index);
    }
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
    {
        qcc_precache_model2(progs_b_g_key_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_b_g_key_mdl_string_index);
        set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), gold_keycard_string_index);
    }
    qcc_key_setsounds();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_key_touch));
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_KEY2);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*
===============================================================================

END OF LEVEL RUNES

===============================================================================
*/}
void qcc_sigil_touch(void)
{
    int qcc_stemp;
    float qcc_best;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    qcc_centerprint(progs.qcc_other, You_got_the_rune__string_index);
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null);
    progs.qcc_serverflags = (((int) progs.qcc_serverflags) | ((int) ( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 15)) )));
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_nh_sigil_removed)// so rune doors won't find it
;
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
/*QUAKED item_sigil (0 .5 .8) (-16 -16 -24) (16 16 32) E1 E2 E3 E4
End of level sigil, pick up to end episode and return to jrstart.
*/}
void qcc_item_sigil(void)
{
    if (!get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self)))
        qcc_objerror(no_spawnflags_string_index);
    qcc_precache_sound(misc_runekey_wav_string_index);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_runekey_wav_string_index);
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 1)))
    {
        qcc_precache_model(progs_end1_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_end1_mdl_string_index);
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 2)))
    {
        qcc_precache_model2(progs_end2_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_end2_mdl_string_index);
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 4)))
    {
        qcc_precache_model2(progs_end3_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_end3_mdl_string_index);
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 8)))
    {
        qcc_precache_model2(progs_end4_mdl_string_index);
        qcc_setmodel(progs.qcc_self, progs_end4_mdl_string_index);
    }
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sigil_touch));
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*
===============================================================================

POWERUPS

===============================================================================
*/}
void qcc_powerup_touch(void);
void qcc_powerup_touch(void)
{
    int qcc_stemp;
    float qcc_best;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    qcc_sprint(progs.qcc_other, You_got_the__string_index);
    qcc_sprint(progs.qcc_other, get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_sprint(progs.qcc_other, _n__string_index);
    if (progs.qcc_deathmatch)
    {
        set_qcc_mdl(PROG_TO_EDICT(progs.qcc_self), get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
        if (((int) ( areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_invulnerability) )) || ((int) ( areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_invisibility) )))
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 60 * 5);
        else
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 60);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_regen));
    }
    qcc_sound(progs.qcc_other, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) | ((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))));
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null)// do the apropriate action
;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_envirosuit))
    {
        set_qcc_rad_time(PROG_TO_EDICT(progs.qcc_other), 1);
        set_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 30);
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_invulnerability))
    {
        set_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_other), 1);
        set_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 30);
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_invisibility))
    {
        set_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_other), 1);
        set_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 30);
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_item_artifact_super_damage))
    {
        set_qcc_super_time(PROG_TO_EDICT(progs.qcc_other), 1);
        set_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 30);
    }
    progs.qcc_activator = progs.qcc_other;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
/*QUAKED item_artifact_invulnerability (0 .5 .8) (-16 -16 -24) (16 16 32)
Player is invulnerable for 30 seconds
*/}
void qcc_item_artifact_invulnerability(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_powerup_touch));
    qcc_precache_model(progs_invulner_mdl_string_index);
    qcc_precache_sound(items_protect_wav_string_index);
    qcc_precache_sound(items_protect2_wav_string_index);
    qcc_precache_sound(items_protect3_wav_string_index);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_protect_wav_string_index);
    qcc_setmodel(progs.qcc_self, progs_invulner_mdl_string_index);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Pentagram_of_Protection_string_index);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_INVULNERABILITY);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*QUAKED item_artifact_envirosuit (0 .5 .8) (-16 -16 -24) (16 16 32)
Player takes no damage from water or slime for 30 seconds
*/}
void qcc_item_artifact_envirosuit(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_powerup_touch));
    qcc_precache_model(progs_suit_mdl_string_index);
    qcc_precache_sound(items_suit_wav_string_index);
    qcc_precache_sound(items_suit2_wav_string_index);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_suit_wav_string_index);
    qcc_setmodel(progs.qcc_self, progs_suit_mdl_string_index);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Biosuit_string_index);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SUIT);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*QUAKED item_artifact_invisibility (0 .5 .8) (-16 -16 -24) (16 16 32)
Player is invisible for 30 seconds
*/}
void qcc_item_artifact_invisibility(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_powerup_touch));
    qcc_precache_model(progs_invisibl_mdl_string_index);
    qcc_precache_sound(items_inv1_wav_string_index);
    qcc_precache_sound(items_inv2_wav_string_index);
    qcc_precache_sound(items_inv3_wav_string_index);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_inv1_wav_string_index);
    qcc_setmodel(progs.qcc_self, progs_invisibl_mdl_string_index);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Ring_of_Shadows_string_index);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_INVISIBILITY);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*QUAKED item_artifact_super_damage (0 .5 .8) (-16 -16 -24) (16 16 32)
The next attack from the player will do 4x damage
*/}
void qcc_item_artifact_super_damage(void)
{
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_powerup_touch));
    qcc_precache_model(progs_quaddama_mdl_string_index);
    qcc_precache_sound(items_damage_wav_string_index);
    qcc_precache_sound(items_damage2_wav_string_index);
    qcc_precache_sound(items_damage3_wav_string_index);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), items_damage_wav_string_index);
    qcc_setmodel(progs.qcc_self, progs_quaddama_mdl_string_index);
    set_qcc_netname(PROG_TO_EDICT(progs.qcc_self), Quad_Damage_string_index);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_QUAD);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 32.0000f}});
    qcc_StartItem();
/*
===============================================================================

PLAYER BACKPACKS

===============================================================================
*/}
void qcc_BackpackTouch(void)
{
    uint16_t qcc_s;
    float qcc_best;
    int qcc_stemp;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
// if the player was using his best weapon, change up to the new one if better		
        return;
    qcc_stemp = progs.qcc_self;
    progs.qcc_self = progs.qcc_other;
    qcc_best = qcc_W_BestWeapon();
    progs.qcc_self = qcc_stemp// change weapons
;
    set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_other)) + get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other))) | ((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))));
    qcc_bound_other_ammo();
    qcc_sprint(progs.qcc_other, You_get__string_index);
    if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_s = qcc_ftos(get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sprint(progs.qcc_other, qcc_s);
        qcc_sprint(progs.qcc_other, _shells___string_index);
    }
    if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_s = qcc_ftos(get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sprint(progs.qcc_other, qcc_s);
        qcc_sprint(progs.qcc_other, _nails__string_index);
    }
    if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_s = qcc_ftos(get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sprint(progs.qcc_other, qcc_s);
        qcc_sprint(progs.qcc_other, _rockets___string_index);
    }
    if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_s = qcc_ftos(get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sprint(progs.qcc_other, qcc_s);
        qcc_sprint(progs.qcc_other, _cells___string_index);
    }
    qcc_sprint(progs.qcc_other, _n__string_index)// backpack touch sound
;
    qcc_sound(progs.qcc_other, qcc_CHAN_ITEM, weapons_lock4_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_stuffcmd(progs.qcc_other, bf_n__string_index)// change to a better weapon if appropriate
;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_other)) == qcc_best)
    {
        qcc_stemp = progs.qcc_self;
        progs.qcc_self = progs.qcc_other;
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_W_BestWeapon());
        progs.qcc_self = qcc_stemp;
    }
    qcc_remove(progs.qcc_self);
    progs.qcc_self = progs.qcc_other;
    qcc_W_SetCurrentAmmo();
/*
===============
DropBackpack
===============
*/}
void qcc_DropBackpack(void)
{
    int qcc_item;
    if (!( get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) ))
// nothing in it
        return;
    qcc_item = qcc_spawn(qcc_classname_nh_backpack);
    set_qcc_origin(PROG_TO_EDICT(qcc_item), vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 24.0000f}}));
    set_qcc_items(PROG_TO_EDICT(qcc_item), get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_shells(PROG_TO_EDICT(qcc_item), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_nails(PROG_TO_EDICT(qcc_item), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_rockets(PROG_TO_EDICT(qcc_item), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_ammo_cells(PROG_TO_EDICT(qcc_item), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity_z(PROG_TO_EDICT(qcc_item), 300);
    set_qcc_velocity_x(PROG_TO_EDICT(qcc_item), -100 + ( qcc_random() * 200 ));
    set_qcc_velocity_y(PROG_TO_EDICT(qcc_item), -100 + ( qcc_random() * 200 ));
    set_qcc_flags(PROG_TO_EDICT(qcc_item), qcc_FL_ITEM);
    set_qcc_solid(PROG_TO_EDICT(qcc_item), qcc_SOLID_TRIGGER);
    set_qcc_movetype(PROG_TO_EDICT(qcc_item), qcc_MOVETYPE_TOSS);
    qcc_setmodel(qcc_item, progs_backpack_mdl_string_index);
    qcc_setsize(qcc_item, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    set_qcc_touch(PROG_TO_EDICT(qcc_item), getFunctionIndex(qcc_BackpackTouch));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_item), progs.qcc_time + 120)// remove after 2 minutes
;
    set_qcc_think(PROG_TO_EDICT(qcc_item), getFunctionIndex(qcc_SUB_Remove));
//File: weapons.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//* 
*/}
void qcc_T_Damage(int , int , int , float );
void qcc_T_RadiusDamage(int , int , float , int );
void qcc_player_run(void);
void qcc_SpawnBlood(vector , vector , float );
// called by worldspawn
void qcc_SuperDamageSound(void);
void qcc_W_Precache(void)
{
    qcc_precache_sound(weapons_r_exp3_wav_string_index)// new rocket explosion
;
    qcc_precache_sound(weapons_rocket1i_wav_string_index)// spike gun
;
    qcc_precache_sound(weapons_sgun1_wav_string_index);
    qcc_precache_sound(weapons_guncock_wav_string_index)// player shotgun
;
    qcc_precache_sound(weapons_ric1_wav_string_index)// ricochet (used in c code)
;
    qcc_precache_sound(weapons_ric2_wav_string_index)// ricochet (used in c code)
;
    qcc_precache_sound(weapons_ric3_wav_string_index)// ricochet (used in c code)
;
    qcc_precache_sound(weapons_spike2_wav_string_index)// super spikes
;
    qcc_precache_sound(weapons_tink1_wav_string_index)// spikes tink (used in c code)
;
    qcc_precache_sound(weapons_grenade_wav_string_index)// grenade launcher
;
    qcc_precache_sound(weapons_bounce_wav_string_index)// grenade bounce
;
    qcc_precache_sound(weapons_shotgn2_wav_string_index)// super shotgun
;
}
float qcc_crandom(void)
{
    return 2 * ( qcc_random() - 0.5f );
/*
================
W_FireAxe
================
*/}
void qcc_W_FireAxe(void)
{
    vector qcc_source;
    vector qcc_org;
    qcc_source = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 16.0000f}});
    qcc_traceline(qcc_source, vectorAdd(qcc_source, vectorMulFloat(progs.qcc_v_forward, 64)), qcc_FALSE, progs.qcc_self);
    if (progs.qcc_trace_fraction == 1)
        return;
    qcc_org = vectorSub(progs.qcc_trace_endpos, vectorMulFloat(progs.qcc_v_forward, 4));
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_trace_ent)))
    {
        set_qcc_axhitme(PROG_TO_EDICT(progs.qcc_trace_ent), 1);
        qcc_SpawnBlood(qcc_org, (vector) {{0.000000f, 0.000000f, 0.000000f}}, 20.0000f);
        qcc_T_Damage(progs.qcc_trace_ent, progs.qcc_self, progs.qcc_self, 20.0000f);
    }
    else
// hit wall
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, player_axhit2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_GUNSHOT);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
    }
//============================================================================
}
vector qcc_wall_velocity(void)
{
    vector qcc_vel;
    qcc_vel = qcc_normalize(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)));
    qcc_vel = qcc_normalize(vectorAdd(vectorAdd(qcc_vel, vectorMulFloat(progs.qcc_v_up, ( qcc_random() - 0.5f ))), vectorMulFloat(progs.qcc_v_right, ( qcc_random() - 0.5f ))));
    qcc_vel = vectorAdd(qcc_vel, floatMulVector(2, progs.qcc_trace_plane_normal));
    qcc_vel = vectorMulFloat(qcc_vel, 200);
    return qcc_vel;
/*
================
SpawnMeatSpray
================
*/}
void qcc_SpawnMeatSpray(vector qcc_org, vector qcc_vel)
{
    int qcc_missile,     qcc_mpuff//local	vector	org;  // was this error ?
;
    qcc_missile = qcc_spawn(qcc_classname_progs_zom_gib_mdl);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_BOUNCE);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_NOT);
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), qcc_vel);
    set_qcc_velocity_z(PROG_TO_EDICT(qcc_missile), get_qcc_velocity(PROG_TO_EDICT(qcc_missile)).z + 250 + 50 * qcc_random());
    set_qcc_avelocity(PROG_TO_EDICT(qcc_missile), (vector)  {{3000.00f, 1000.00f, 2000.00f}})// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 1);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_SUB_Remove));
    qcc_setmodel(qcc_missile, qcc_classname_progs_zom_gib_mdl);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, qcc_org);
/*
================
SpawnBlood
================
*/}
void qcc_SpawnBlood(vector qcc_org, vector qcc_vel, float qcc_damage)
{
    qcc_particle(qcc_org, vectorMulFloat(qcc_vel, 0.1f), 73.0000f, qcc_damage * 2);
/*
================
spawn_touchblood
================
*/}
void qcc_spawn_touchblood(float qcc_damage)
{
    vector qcc_vel;
    qcc_vel = vectorMulFloat(qcc_wall_velocity(), 0.2f);
    qcc_SpawnBlood(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(qcc_vel, 0.01f)), qcc_vel, qcc_damage);
/*
================
SpawnChunk
================
*/}
void qcc_SpawnChunk(vector qcc_org, vector qcc_vel)
{
    qcc_particle(qcc_org, vectorMulFloat(qcc_vel, 0.02f), 0.000000f, 10.0000f);
/*
==============================================================================

MULTI-DAMAGE

Collects multiple small damages into a single damage

==============================================================================
*/}
;
;
void qcc_ClearMultiDamage(void)
{
    progs.qcc_multi_ent = progs.qcc_world;
    progs.qcc_multi_damage = 0;
}
void qcc_ApplyMultiDamage(void)
{
    if ((!progs.qcc_multi_ent))
        return;
    qcc_T_Damage(progs.qcc_multi_ent, progs.qcc_self, progs.qcc_self, progs.qcc_multi_damage);
}
void qcc_AddMultiDamage(int qcc_hit, float qcc_damage)
{
    if ((!qcc_hit))
        return;
    if (qcc_hit != progs.qcc_multi_ent)
    {
        qcc_ApplyMultiDamage();
        progs.qcc_multi_damage = qcc_damage;
        progs.qcc_multi_ent = qcc_hit;
    }
    else
        progs.qcc_multi_damage = progs.qcc_multi_damage + qcc_damage;
/*
==============================================================================

BULLETS

==============================================================================
*//*
================
TraceAttack
================
*/}
void qcc_TraceAttack(float qcc_damage, vector qcc_dir)
{
    vector qcc_vel,     qcc_org;
    qcc_vel = qcc_normalize(vectorAdd(vectorAdd(qcc_dir, vectorMulFloat(progs.qcc_v_up, qcc_crandom())), vectorMulFloat(progs.qcc_v_right, qcc_crandom())));
    qcc_vel = vectorAdd(qcc_vel, floatMulVector(2, progs.qcc_trace_plane_normal));
    qcc_vel = vectorMulFloat(qcc_vel, 200);
    qcc_org = vectorSub(progs.qcc_trace_endpos, vectorMulFloat(qcc_dir, 4));
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_trace_ent)))
    {
        qcc_SpawnBlood(qcc_org, vectorMulFloat(qcc_vel, 0.2f), qcc_damage);
        qcc_AddMultiDamage(progs.qcc_trace_ent, qcc_damage);
    }
    else
    {
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_GUNSHOT);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
    }
/*
================
FireBullets

Used by shotgun, super shotgun, and enemy soldier firing
Go to the trouble of combining multiple pellets into a single damage call.
================
*/}
void qcc_FireBullets(float qcc_shotcount, vector qcc_dir, vector qcc_spread)
{
    vector qcc_direction;
    vector qcc_src;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)));
    qcc_src = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 10));
    qcc_src.z = get_qcc_absmin(PROG_TO_EDICT(progs.qcc_self)).z + get_qcc_size(PROG_TO_EDICT(progs.qcc_self)).z * 0.7f;
    qcc_ClearMultiDamage();
    while (qcc_shotcount > 0)
    {
        qcc_direction = vectorAdd(vectorAdd(qcc_dir, floatMulVector(qcc_crandom() * qcc_spread.x, progs.qcc_v_right)), floatMulVector(qcc_crandom() * qcc_spread.y, progs.qcc_v_up));
        qcc_traceline(qcc_src, vectorAdd(qcc_src, vectorMulFloat(qcc_direction, 2048)), qcc_FALSE, progs.qcc_self);
        if (progs.qcc_trace_fraction != 1)
            qcc_TraceAttack(4.00000f, qcc_direction);
        qcc_shotcount = qcc_shotcount - 1;
    }
    qcc_ApplyMultiDamage();
/*
================
W_FireShotgun
================
*/}
void qcc_W_FireShotgun(void)
{
    vector qcc_dir;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_guncock_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) - 1));
    qcc_dir = qcc_aim(progs.qcc_self, 100000.f);
    qcc_FireBullets(6.00000f, qcc_dir, (vector) {{0.0400000f, 0.0400000f, 0.000000f}});
/*
================
W_FireSuperShotgun
================
*/}
void qcc_W_FireSuperShotgun(void)
{
    vector qcc_dir;
    if (get_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_W_FireShotgun();
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_shotgn2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -4);
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) - 2));
    qcc_dir = qcc_aim(progs.qcc_self, 100000.f);
    qcc_FireBullets(14.0000f, qcc_dir, (vector) {{0.140000f, 0.0800000f, 0.000000f}});
/*
==============================================================================

ROCKETS

==============================================================================
*/}
void qcc_s_explode1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_s_explode2));
}
void qcc_s_explode2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_s_explode3));
}
void qcc_s_explode3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_s_explode4));
}
void qcc_s_explode4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_s_explode5));
}
void qcc_s_explode5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_s_explode6));
}
void qcc_s_explode6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Remove));
}
void qcc_BecomeExplosion(void)
{
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    qcc_setmodel(progs.qcc_self, progs_s_explod_spr_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_s_explode1();
}
void qcc_T_MissileTouch(void)
{
    float qcc_damg;
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (qcc_pointcontents(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))) == qcc_CONTENT_SKY)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_damg = 100 + qcc_random() * 20;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)))
    {
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_monster_shambler))
            qcc_damg = qcc_damg * 0.5f// mostly immune
;
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), qcc_damg);
// don't do radius damage to the other, because all the damage
// was done in the impact
    }
    qcc_T_RadiusDamage(progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 120.000f, progs.qcc_other)//	sound (self, CHAN_WEAPON, "weapons/r_exp3.wav", 1, ATTN_NORM);
;
    set_qcc_origin(PROG_TO_EDICT(progs.qcc_self), vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(8, qcc_normalize(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self))))));
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_EXPLOSION);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    qcc_BecomeExplosion();
/*
================
W_FireRocket
================
*/}
void qcc_W_FireRocket(void)
{
    int qcc_missile,     qcc_mpuff;
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) - 1));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_sgun1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
    qcc_missile = qcc_spawn(qcc_classname_nh_missile);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_FLYMISSILE);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_BBOX)// set missile speed	
;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), qcc_aim(progs.qcc_self, 1000.00f));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(qcc_missile)), 1000));
    set_qcc_angles(PROG_TO_EDICT(qcc_missile), qcc_vectoangles(get_qcc_velocity(PROG_TO_EDICT(qcc_missile))));
    set_qcc_touch(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_T_MissileTouch))// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 5);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_SUB_Remove));
    qcc_setmodel(qcc_missile, progs_missile_mdl_string_index);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 8)), (vector)  {{0.000000f, 0.000000f, 16.0000f}}));
/*
===============================================================================

LIGHTNING

===============================================================================
*//*
=================
LightningDamage
=================
*/}
void qcc_LightningDamage(vector qcc_p1, vector qcc_p2, int qcc_from, float qcc_damage)
{
    int qcc_e1,     qcc_e2;
    vector qcc_f;
    qcc_f = vectorSub(qcc_p2, qcc_p1);
    qcc_normalize(qcc_f);
    qcc_f.x = 0 - qcc_f.y;
    qcc_f.y = qcc_f.x;
    qcc_f.z = 0;
    qcc_f = vectorMulFloat(qcc_f, 16);
    qcc_e1 = qcc_e2 = progs.qcc_world;
    qcc_traceline(qcc_p1, qcc_p2, qcc_FALSE, progs.qcc_self);
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_trace_ent)))
    {
        qcc_particle(progs.qcc_trace_endpos, (vector) {{0.000000f, 0.000000f, 100.000f}}, 225.000f, qcc_damage * 4);
        qcc_T_Damage(progs.qcc_trace_ent, qcc_from, qcc_from, qcc_damage);
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_player))
        {
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player))
                set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_trace_ent), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_trace_ent)).z + 400);
        }
    }
    qcc_e1 = progs.qcc_trace_ent;
    qcc_traceline(vectorAdd(qcc_p1, qcc_f), vectorAdd(qcc_p2, qcc_f), qcc_FALSE, progs.qcc_self);
    if (((int) progs.qcc_trace_ent != qcc_e1) && ((int) get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_trace_ent))))
    {
        qcc_particle(progs.qcc_trace_endpos, (vector) {{0.000000f, 0.000000f, 100.000f}}, 225.000f, qcc_damage * 4);
        qcc_T_Damage(progs.qcc_trace_ent, qcc_from, qcc_from, qcc_damage);
    }
    qcc_e2 = progs.qcc_trace_ent;
    qcc_traceline(vectorSub(qcc_p1, qcc_f), vectorSub(qcc_p2, qcc_f), qcc_FALSE, progs.qcc_self);
    if (((int) ((int) progs.qcc_trace_ent != qcc_e1) && ((int) progs.qcc_trace_ent != qcc_e2)) && ((int) get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_trace_ent))))
    {
        qcc_particle(progs.qcc_trace_endpos, (vector) {{0.000000f, 0.000000f, 100.000f}}, 225.000f, qcc_damage * 4);
        qcc_T_Damage(progs.qcc_trace_ent, qcc_from, qcc_from, qcc_damage);
    }
}
void qcc_W_FireLightning(void)
{
    vector qcc_org;
    if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) < 1)
    {
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_W_BestWeapon());
        qcc_W_SetCurrentAmmo();
        return;
// explode if under water
    }
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) > 1)
    {
        qcc_T_RadiusDamage(progs.qcc_self, progs.qcc_self, 35 * get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_world);
        set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), 0);
        qcc_W_SetCurrentAmmo();
        return;
    }
    if (get_qcc_t_width(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_lhit_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        set_qcc_t_width(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.6f);
    }
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) - 1));
    qcc_org = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 16.0000f}});
    qcc_traceline(qcc_org, vectorAdd(qcc_org, vectorMulFloat(progs.qcc_v_forward, 600)), qcc_TRUE, progs.qcc_self);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_LIGHTNING2);
    qcc_WriteEntity(qcc_MSG_BROADCAST, progs.qcc_self);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.z);
    qcc_LightningDamage(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorAdd(progs.qcc_trace_endpos, vectorMulFloat(progs.qcc_v_forward, 4)), progs.qcc_self, 30.0000f);
//=============================================================================
}
void qcc_GrenadeExplode(void)
{
    qcc_T_RadiusDamage(progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 120.000f, progs.qcc_world);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_EXPLOSION);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    qcc_BecomeExplosion();
}
void qcc_GrenadeTouch(void)
{
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)) == qcc_DAMAGE_AIM)
    {
        qcc_GrenadeExplode();
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_bounce_wav_string_index, 1.00000f, qcc_ATTN_NORM)// bounce sound
;
    if (areVectorEqual(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}}))
        set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
/*
================
W_FireGrenade
================
*/}
void qcc_W_FireGrenade(void)
{
    int qcc_missile,     qcc_mpuff;
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) - 1));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_grenade_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
    qcc_missile = qcc_spawn(qcc_classname_grenade);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_BOUNCE);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_BBOX);
    set_qcc_classname(PROG_TO_EDICT(qcc_missile), qcc_classname_grenade)// set missile speed	
;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)));
    if (get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)).x)
        set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorAdd(vectorAdd(vectorAdd(vectorMulFloat(progs.qcc_v_forward, 600), vectorMulFloat(progs.qcc_v_up, 200)), vectorMulFloat(floatMulVector(qcc_crandom(), progs.qcc_v_right), 10)), vectorMulFloat(floatMulVector(qcc_crandom(), progs.qcc_v_up), 10)));
    else
    {
        set_qcc_velocity(PROG_TO_EDICT(qcc_missile), qcc_aim(progs.qcc_self, 10000.0f));
        set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(qcc_missile)), 600));
        set_qcc_velocity_z(PROG_TO_EDICT(qcc_missile), 200);
    }
    set_qcc_avelocity(PROG_TO_EDICT(qcc_missile), (vector)  {{300.000f, 300.000f, 300.000f}});
    set_qcc_angles(PROG_TO_EDICT(qcc_missile), qcc_vectoangles(get_qcc_velocity(PROG_TO_EDICT(qcc_missile))));
    set_qcc_touch(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_GrenadeTouch))// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 2.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_GrenadeExplode));
    qcc_setmodel(qcc_missile, progs_grenade_mdl_string_index);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
//=============================================================================
}
void qcc_spike_touch(void);
/*
===============
launch_spike

Used for both the player and the ogre
===============
*/void qcc_superspike_touch(void);
void qcc_launch_spike(vector qcc_org, vector qcc_dir)
{
    progs.qcc_newmis = qcc_spawn(qcc_classname_spike);
    set_qcc_owner(PROG_TO_EDICT(progs.qcc_newmis), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_newmis), qcc_MOVETYPE_FLYMISSILE);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_newmis), qcc_SOLID_BBOX);
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_newmis), qcc_vectoangles(qcc_dir));
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_spike_touch));
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_newmis), qcc_classname_spike);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_SUB_Remove));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_newmis), progs.qcc_time + 6);
    qcc_setmodel(progs.qcc_newmis, progs_spike_mdl_string_index);
    qcc_setsize(progs.qcc_newmis, qcc_VEC_ORIGIN, qcc_VEC_ORIGIN);
    qcc_setorigin(progs.qcc_newmis, qcc_org);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(qcc_dir, 1000));
}
void qcc_W_FireSuperSpikes(void)
{
    vector qcc_dir;
    int qcc_old;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_spike2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) - 2));
    qcc_dir = qcc_aim(progs.qcc_self, 1000.00f);
    qcc_launch_spike(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 16.0000f}}), qcc_dir);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_superspike_touch));
    qcc_setmodel(progs.qcc_newmis, progs_s_spike_mdl_string_index);
    qcc_setsize(progs.qcc_newmis, qcc_VEC_ORIGIN, qcc_VEC_ORIGIN);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
}
void qcc_W_FireSpikes(float qcc_ox)
{
    vector qcc_dir;
    int qcc_old;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)));
    if (((int) get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) >= 2) && ((int) get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_NAILGUN))
    {
        qcc_W_FireSuperSpikes();
        return;
    }
    if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) < 1)
    {
        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_W_BestWeapon());
        qcc_W_SetCurrentAmmo();
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_rocket1i_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) - 1));
    qcc_dir = qcc_aim(progs.qcc_self, 1000.00f);
    qcc_launch_spike(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 16.0000f}}), vectorMulFloat(progs.qcc_v_right, qcc_ox)), qcc_dir);
    set_qcc_punchangle_x(PROG_TO_EDICT(progs.qcc_self), -2);
}
void qcc_spike_touch(void)
{
    float qcc_rand;
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
        return;
    if (get_qcc_solid(PROG_TO_EDICT(progs.qcc_other)) == qcc_SOLID_TRIGGER)
// trigger field, do nothing
        return;
    if (qcc_pointcontents(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))) == qcc_CONTENT_SKY)
    {
        qcc_remove(progs.qcc_self);
        return;
// hit something that bleeds
    }
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        qcc_spawn_touchblood(9.00000f);
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 9.00000f);
    }
    else
    {
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_wizspike))
            qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_WIZSPIKE);
        else
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_knightspike))
                qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_KNIGHTSPIKE);
            else
                qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_SPIKE);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    }
    qcc_remove(progs.qcc_self);
}
void qcc_superspike_touch(void)
{
    float qcc_rand;
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
        return;
    if (get_qcc_solid(PROG_TO_EDICT(progs.qcc_other)) == qcc_SOLID_TRIGGER)
// trigger field, do nothing
        return;
    if (qcc_pointcontents(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))) == qcc_CONTENT_SKY)
    {
        qcc_remove(progs.qcc_self);
        return;
// hit something that bleeds
    }
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        qcc_spawn_touchblood(18.0000f);
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 18.0000f);
    }
    else
    {
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_SUPERSPIKE);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
        qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    }
    qcc_remove(progs.qcc_self);
/*
===============================================================================

PLAYER WEAPON USE

===============================================================================
*/}
void qcc_W_SetCurrentAmmo(void)
{
    qcc_player_run()// get out of any weapon firing states
;
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) ( (((int) (((int) (((int) qcc_IT_SHELLS) | ((int) qcc_IT_NAILS))) | ((int) qcc_IT_ROCKETS))) | ((int) qcc_IT_CELLS)) ))) ));
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
    {
        set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_axe_mdl_string_index);
        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
    }
    else
        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SHOTGUN)
        {
            set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)));
            set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_shot_mdl_string_index);
            set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_SHELLS)));
        }
        else
            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_SHOTGUN)
            {
                set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)));
                set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_shot2_mdl_string_index);
                set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_SHELLS)));
            }
            else
                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_NAILGUN)
                {
                    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)));
                    set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_nail_mdl_string_index);
                    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_NAILS)));
                }
                else
                    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_NAILGUN)
                    {
                        set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)));
                        set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_nail2_mdl_string_index);
                        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                        set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_NAILS)));
                    }
                    else
                        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_GRENADE_LAUNCHER)
                        {
                            set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)));
                            set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_rock_mdl_string_index);
                            set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_ROCKETS)));
                        }
                        else
                            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_ROCKET_LAUNCHER)
                            {
                                set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)));
                                set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_rock2_mdl_string_index);
                                set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                                set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_ROCKETS)));
                            }
                            else
                                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_LIGHTNING)
                                {
                                    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)));
                                    set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), progs_v_light_mdl_string_index);
                                    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                                    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_CELLS)));
                                }
                                else
                                {
                                    set_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self), 0);
                                    set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
                                    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
                                }
}
float qcc_W_BestWeapon(void)
{
    float qcc_it;
    qcc_it = get_qcc_items(PROG_TO_EDICT(progs.qcc_self));
    if (((int) get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) >= 1) && ((int) ( (((int) qcc_it) & ((int) qcc_IT_LIGHTNING)) )))
        return qcc_IT_LIGHTNING;
    else
        if (((int) get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) >= 2) && ((int) ( (((int) qcc_it) & ((int) qcc_IT_SUPER_NAILGUN)) )))
            return qcc_IT_SUPER_NAILGUN;
        else
            if (((int) get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) >= 2) && ((int) ( (((int) qcc_it) & ((int) qcc_IT_SUPER_SHOTGUN)) )))
                return qcc_IT_SUPER_SHOTGUN;
            else
                if (((int) get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) >= 1) && ((int) ( (((int) qcc_it) & ((int) qcc_IT_NAILGUN)) )))
                    return qcc_IT_NAILGUN;
                else
                    if (((int) get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) >= 1) && ((int) ( (((int) qcc_it) & ((int) qcc_IT_SHOTGUN)) )))
/*
	if(self.ammo_rockets >= 1 && (it & IT_ROCKET_LAUNCHER) )
		return IT_ROCKET_LAUNCHER;
	else if(self.ammo_rockets >= 1 && (it & IT_GRENADE_LAUNCHER) )
		return IT_GRENADE_LAUNCHER;

*/                        return qcc_IT_SHOTGUN;
    return qcc_IT_AXE;
}
float qcc_W_CheckNoAmmo(void)
{
    if (get_qcc_currentammo(PROG_TO_EDICT(progs.qcc_self)) > 0)
        return qcc_TRUE;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
        return qcc_TRUE;
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_W_BestWeapon());
    qcc_W_SetCurrentAmmo()// drop the weapon down
;
    return qcc_FALSE;
/*
============
W_Attack

An attack impulse can be triggered now
============
*/}
void qcc_player_axe1(void);
void qcc_player_axeb1(void);
void qcc_player_axec1(void);
void qcc_player_axed1(void);
void qcc_player_shot1(void);
void qcc_player_nail1(void);
void qcc_player_light1(void);
void qcc_player_rocket1(void);
void qcc_W_Attack(void)
{
    float qcc_r;
    if (!qcc_W_CheckNoAmmo())
        return;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)))// calculate forward angle for velocity
;
    set_qcc_show_hostile(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1)// wake monsters up
;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_ax1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_r = qcc_random();
        if (qcc_r < 0.25f)
            qcc_player_axe1();
        else
            if (qcc_r < 0.5f)
                qcc_player_axeb1();
            else
                if (qcc_r < 0.75f)
                    qcc_player_axec1();
                else
                    qcc_player_axed1();
        set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
    }
    else
        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SHOTGUN)
        {
            qcc_player_shot1();
            qcc_W_FireShotgun();
            set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
        }
        else
            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_SHOTGUN)
            {
                qcc_player_shot1();
                qcc_W_FireSuperShotgun();
                set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.7f);
            }
            else
                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_NAILGUN)
                {
                    qcc_player_nail1();
                }
                else
                    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_NAILGUN)
                    {
                        qcc_player_nail1();
                    }
                    else
                        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_GRENADE_LAUNCHER)
                        {
                            qcc_player_rocket1();
                            qcc_W_FireGrenade();
                            set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.6f);
                        }
                        else
                            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_ROCKET_LAUNCHER)
                            {
                                qcc_player_rocket1();
                                qcc_W_FireRocket();
                                set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.8f);
                            }
                            else
                                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_LIGHTNING)
                                {
                                    qcc_player_light1();
                                    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
                                    qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, weapons_lstart_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                                }
/*
============
W_ChangeWeapon

============
*/}
void qcc_W_ChangeWeapon(void)
{
    float qcc_it,     qcc_am,     qcc_fl;
    qcc_it = get_qcc_items(PROG_TO_EDICT(progs.qcc_self));
    qcc_fl = get_qcc_items(PROG_TO_EDICT(progs.qcc_self))//next-hack fixed.
;
    qcc_am = 0;
    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_fl = qcc_IT_AXE;
    }
    else
        if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 2)
        {
            qcc_fl = qcc_IT_SHOTGUN;
            if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) < 1)
                qcc_am = 1;
        }
        else
            if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 3)
            {
                qcc_fl = qcc_IT_SUPER_SHOTGUN;
                if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) < 2)
                    qcc_am = 1;
            }
            else
                if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 4)
                {
                    qcc_fl = qcc_IT_NAILGUN;
                    if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) < 1)
                        qcc_am = 1;
                }
                else
                    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 5)
                    {
                        qcc_fl = qcc_IT_SUPER_NAILGUN;
                        if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) < 2)
                            qcc_am = 1;
                    }
                    else
                        if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 6)
                        {
                            qcc_fl = qcc_IT_GRENADE_LAUNCHER;
                            if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                qcc_am = 1;
                        }
                        else
                            if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 7)
                            {
                                qcc_fl = qcc_IT_ROCKET_LAUNCHER;
                                if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                    qcc_am = 1;
                            }
                            else
                                if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 8)
                                {
                                    qcc_fl = qcc_IT_LIGHTNING;
                                    if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                        qcc_am = 1;
                                }
    set_qcc_impulse(PROG_TO_EDICT(progs.qcc_self), 0);
    if (!( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_fl)) ))
// don't have the weapon or the ammo
    {
        qcc_sprint(progs.qcc_self, no_weapon__n__string_index);
        return;
    }
    if (qcc_am)
// don't have the ammo
    {
        qcc_sprint(progs.qcc_self, not_enough_ammo__n__string_index);
        return;
//
// set weapon, set ammo
//
    }
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_fl);
    qcc_W_SetCurrentAmmo();
/*
============
CheatCommand
============
*/}
void qcc_CheatCommand(void)
{
    if (((int) progs.qcc_deathmatch) || ((int) progs.qcc_coop))
        return;
    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), 100);
    set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self), 200);
    set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), 100);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) (((int) (((int) (((int) (((int) (((int) (((int) (((int) (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_AXE))) | ((int) qcc_IT_SHOTGUN))) | ((int) qcc_IT_SUPER_SHOTGUN))) | ((int) qcc_IT_NAILGUN))) | ((int) qcc_IT_SUPER_NAILGUN))) | ((int) qcc_IT_GRENADE_LAUNCHER))) | ((int) qcc_IT_ROCKET_LAUNCHER))) | ((int) qcc_IT_KEY1))) | ((int) qcc_IT_KEY2)));
    set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), 200);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_LIGHTNING)));
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_ROCKET_LAUNCHER);
    set_qcc_impulse(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_W_SetCurrentAmmo();
/*
============
CycleWeaponCommand

Go to the next weapon with ammo
============
*/}
void qcc_CycleWeaponCommand(void)
{
    float qcc_it,     qcc_am;
    qcc_it = get_qcc_items(PROG_TO_EDICT(progs.qcc_self));
    set_qcc_impulse(PROG_TO_EDICT(progs.qcc_self), 0);
    while (1.00000f)
    {
        qcc_am = 0;
        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_LIGHTNING)
        {
            set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_AXE);
        }
        else
            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
            {
                set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SHOTGUN);
                if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) < 1)
                    qcc_am = 1;
            }
            else
                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SHOTGUN)
                {
                    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SUPER_SHOTGUN);
                    if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) < 2)
                        qcc_am = 1;
                }
                else
                    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_SHOTGUN)
                    {
                        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_NAILGUN);
                        if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) < 1)
                            qcc_am = 1;
                    }
                    else
                        if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_NAILGUN)
                        {
                            set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_SUPER_NAILGUN);
                            if (get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self)) < 2)
                                qcc_am = 1;
                        }
                        else
                            if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_SUPER_NAILGUN)
                            {
                                set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_GRENADE_LAUNCHER);
                                if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                    qcc_am = 1;
                            }
                            else
                                if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_GRENADE_LAUNCHER)
                                {
                                    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_ROCKET_LAUNCHER);
                                    if (get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                        qcc_am = 1;
                                }
                                else
                                    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_ROCKET_LAUNCHER)
                                    {
                                        set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), qcc_IT_LIGHTNING);
                                        if (get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self)) < 1)
                                            qcc_am = 1;
                                    }
        if (((int) ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)))) )) && ((int) qcc_am == 0))
        {
            qcc_W_SetCurrentAmmo();
            return;
        }
    }
/*
============
ServerflagsCommand

Just for development
============
*/}
void qcc_ServerflagsCommand(void)
{
    progs.qcc_serverflags = progs.qcc_serverflags * 2 + 1;
}
void qcc_QuadCheat(void)
{
    if (((int) progs.qcc_deathmatch) || ((int) progs.qcc_coop))
        return;
    set_qcc_super_time(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 30);
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_IT_QUAD)));
    qcc_dprint(quad_cheat_n__string_index);
/*
============
ImpulseCommands

============
*/}
void qcc_ImpulseCommands(void)
{
    if (((int) get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) >= 1) && ((int) get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) <= 8))
        qcc_W_ChangeWeapon();
    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 9)
        qcc_CheatCommand();
    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 10)
        qcc_CycleWeaponCommand();
    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 11)
        qcc_ServerflagsCommand();
    if (get_qcc_impulse(PROG_TO_EDICT(progs.qcc_self)) == 255)
        qcc_QuadCheat();
    set_qcc_impulse(PROG_TO_EDICT(progs.qcc_self), 0);
/*
============
W_WeaponFrame

Called every frame so impulse events can be handled as well as possible
============
*/}
void qcc_W_WeaponFrame(void)
{
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return;
    qcc_ImpulseCommands()// check for attack
;
    if (get_qcc_button0(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_SuperDamageSound();
        qcc_W_Attack();
    }
/*
========
SuperDamageSound

Plays sound if needed
========
*/}
void qcc_SuperDamageSound(void)
{
    if (get_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
    {
        if (get_qcc_super_sound(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
            set_qcc_super_sound(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, items_damage3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
    }
    return;
//File: world.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
void qcc_InitBodyQue(void);
void qcc_main(void)
{
    qcc_dprint(main_function_n__string_index)// these are just commands the the prog compiler to copy these files
;
    qcc_precache_file(progs_dat_string_index);
    qcc_precache_file(gfx_wad_string_index);
    qcc_precache_file(quake_rc_string_index);
    qcc_precache_file(default_cfg_string_index);
    qcc_precache_file(end1_bin_string_index);
    qcc_precache_file2(end2_bin_string_index);
    qcc_precache_file(demo1_dem_string_index);
    qcc_precache_file(demo2_dem_string_index);
    qcc_precache_file(demo3_dem_string_index)//
// these are all of the lumps from the cached.ls files
//
;
    qcc_precache_file(gfx_palette_lmp_string_index);
    qcc_precache_file(gfx_colormap_lmp_string_index);
    qcc_precache_file2(gfx_pop_lmp_string_index);
    qcc_precache_file(gfx_complete_lmp_string_index);
    qcc_precache_file(gfx_inter_lmp_string_index);
    qcc_precache_file(gfx_ranking_lmp_string_index);
    qcc_precache_file(gfx_vidmodes_lmp_string_index);
    qcc_precache_file(gfx_finale_lmp_string_index);
    qcc_precache_file(gfx_conback_lmp_string_index);
    qcc_precache_file(gfx_qplaque_lmp_string_index);
    qcc_precache_file(gfx_menudot1_lmp_string_index);
    qcc_precache_file(gfx_menudot2_lmp_string_index);
    qcc_precache_file(gfx_menudot3_lmp_string_index);
    qcc_precache_file(gfx_menudot4_lmp_string_index);
    qcc_precache_file(gfx_menudot5_lmp_string_index);
    qcc_precache_file(gfx_menudot6_lmp_string_index);
    qcc_precache_file(gfx_menuplyr_lmp_string_index);
    qcc_precache_file(gfx_bigbox_lmp_string_index);
    qcc_precache_file(gfx_dim_modm_lmp_string_index);
    qcc_precache_file(gfx_dim_drct_lmp_string_index);
    qcc_precache_file(gfx_dim_ipx_lmp_string_index);
    qcc_precache_file(gfx_dim_tcp_lmp_string_index);
    qcc_precache_file(gfx_dim_mult_lmp_string_index);
    qcc_precache_file(gfx_mainmenu_lmp_string_index);
    qcc_precache_file(gfx_box_tl_lmp_string_index);
    qcc_precache_file(gfx_box_tm_lmp_string_index);
    qcc_precache_file(gfx_box_tr_lmp_string_index);
    qcc_precache_file(gfx_box_ml_lmp_string_index);
    qcc_precache_file(gfx_box_mm_lmp_string_index);
    qcc_precache_file(gfx_box_mm2_lmp_string_index);
    qcc_precache_file(gfx_box_mr_lmp_string_index);
    qcc_precache_file(gfx_box_bl_lmp_string_index);
    qcc_precache_file(gfx_box_bm_lmp_string_index);
    qcc_precache_file(gfx_box_br_lmp_string_index);
    qcc_precache_file(gfx_sp_menu_lmp_string_index);
    qcc_precache_file(gfx_ttl_sgl_lmp_string_index);
    qcc_precache_file(gfx_ttl_main_lmp_string_index);
    qcc_precache_file(gfx_ttl_cstm_lmp_string_index);
    qcc_precache_file(gfx_mp_menu_lmp_string_index);
    qcc_precache_file(gfx_netmen1_lmp_string_index);
    qcc_precache_file(gfx_netmen2_lmp_string_index);
    qcc_precache_file(gfx_netmen3_lmp_string_index);
    qcc_precache_file(gfx_netmen4_lmp_string_index);
    qcc_precache_file(gfx_netmen5_lmp_string_index);
    qcc_precache_file(gfx_sell_lmp_string_index);
    qcc_precache_file(gfx_help0_lmp_string_index);
    qcc_precache_file(gfx_help1_lmp_string_index);
    qcc_precache_file(gfx_help2_lmp_string_index);
    qcc_precache_file(gfx_help3_lmp_string_index);
    qcc_precache_file(gfx_help4_lmp_string_index);
    qcc_precache_file(gfx_help5_lmp_string_index);
    qcc_precache_file(gfx_pause_lmp_string_index);
    qcc_precache_file(gfx_loading_lmp_string_index);
    qcc_precache_file(gfx_p_option_lmp_string_index);
    qcc_precache_file(gfx_p_load_lmp_string_index);
    qcc_precache_file(gfx_p_save_lmp_string_index);
    qcc_precache_file(gfx_p_multi_lmp_string_index)// sounds loaded by C code
;
    qcc_precache_sound(misc_menu1_wav_string_index);
    qcc_precache_sound(misc_menu2_wav_string_index);
    qcc_precache_sound(misc_menu3_wav_string_index);
    qcc_precache_sound(ambience_water1_wav_string_index);
    qcc_precache_sound(ambience_wind2_wav_string_index)// shareware
;
    qcc_precache_file(maps_start_bsp_string_index);
    qcc_precache_file(maps_e1m1_bsp_string_index);
    qcc_precache_file(maps_e1m2_bsp_string_index);
    qcc_precache_file(maps_e1m3_bsp_string_index);
    qcc_precache_file(maps_e1m4_bsp_string_index);
    qcc_precache_file(maps_e1m5_bsp_string_index);
    qcc_precache_file(maps_e1m6_bsp_string_index);
    qcc_precache_file(maps_e1m7_bsp_string_index);
    qcc_precache_file(maps_e1m8_bsp_string_index)// registered
;
    qcc_precache_file2(gfx_pop_lmp_string_index);
    qcc_precache_file2(maps_e2m1_bsp_string_index);
    qcc_precache_file2(maps_e2m2_bsp_string_index);
    qcc_precache_file2(maps_e2m3_bsp_string_index);
    qcc_precache_file2(maps_e2m4_bsp_string_index);
    qcc_precache_file2(maps_e2m5_bsp_string_index);
    qcc_precache_file2(maps_e2m6_bsp_string_index);
    qcc_precache_file2(maps_e2m7_bsp_string_index);
    qcc_precache_file2(maps_e3m1_bsp_string_index);
    qcc_precache_file2(maps_e3m2_bsp_string_index);
    qcc_precache_file2(maps_e3m3_bsp_string_index);
    qcc_precache_file2(maps_e3m4_bsp_string_index);
    qcc_precache_file2(maps_e3m5_bsp_string_index);
    qcc_precache_file2(maps_e3m6_bsp_string_index);
    qcc_precache_file2(maps_e3m7_bsp_string_index);
    qcc_precache_file2(maps_e4m1_bsp_string_index);
    qcc_precache_file2(maps_e4m2_bsp_string_index);
    qcc_precache_file2(maps_e4m3_bsp_string_index);
    qcc_precache_file2(maps_e4m4_bsp_string_index);
    qcc_precache_file2(maps_e4m5_bsp_string_index);
    qcc_precache_file2(maps_e4m6_bsp_string_index);
    qcc_precache_file2(maps_e4m7_bsp_string_index);
    qcc_precache_file2(maps_e4m8_bsp_string_index);
    qcc_precache_file2(maps_end_bsp_string_index);
    qcc_precache_file2(maps_dm1_bsp_string_index);
    qcc_precache_file2(maps_dm2_bsp_string_index);
    qcc_precache_file2(maps_dm3_bsp_string_index);
    qcc_precache_file2(maps_dm4_bsp_string_index);
    qcc_precache_file2(maps_dm5_bsp_string_index);
    qcc_precache_file2(maps_dm6_bsp_string_index);
}
//=======================
/*QUAKED worldspawn (0 0 0) ?
Only used for the world entity.
Set message to the level name.
Set sounds to the cd track to play.

World Types:
0: medieval
1: metal
2: base
*///=======================
;
void qcc_worldspawn(void)
{
    progs.qcc_lastspawn = progs.qcc_world;
    qcc_InitBodyQue()// custom map attributes
;
    if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_self)), maps_e1m8_bsp_string_index))
        qcc_cvar_set(sv_gravity_string_index, n10_string_index);
    else
        qcc_cvar_set(sv_gravity_string_index, n80_string_index)// the area based ambient sounds MUST be the first precache_sounds
// player precaches	
;
    qcc_W_Precache()// get weapon precaches
// sounds used from C physics code
;
    qcc_precache_sound(demon_dland2_wav_string_index)// landing thud
;
    qcc_precache_sound(misc_h2ohit1_wav_string_index)// landing splash
// setup precaches allways needed
;
    qcc_precache_sound(items_itembk2_wav_string_index)// item respawn sound
;
    qcc_precache_sound(player_plyrjmp8_wav_string_index)// player jump
;
    qcc_precache_sound(player_land_wav_string_index)// player landing
;
    qcc_precache_sound(player_land2_wav_string_index)// player hurt landing
;
    qcc_precache_sound(player_drown1_wav_string_index)// drowning pain
;
    qcc_precache_sound(player_drown2_wav_string_index)// drowning pain
;
    qcc_precache_sound(player_gasp1_wav_string_index)// gasping for air
;
    qcc_precache_sound(player_gasp2_wav_string_index)// taking breath
;
    qcc_precache_sound(player_h2odeath_wav_string_index)// drowning death
;
    qcc_precache_sound(misc_talk_wav_string_index)// talk
;
    qcc_precache_sound(player_teledth1_wav_string_index)// telefrag
;
    qcc_precache_sound(misc_r_tele1_wav_string_index)// teleport sounds
;
    qcc_precache_sound(misc_r_tele2_wav_string_index);
    qcc_precache_sound(misc_r_tele3_wav_string_index);
    qcc_precache_sound(misc_r_tele4_wav_string_index);
    qcc_precache_sound(misc_r_tele5_wav_string_index);
    qcc_precache_sound(weapons_lock4_wav_string_index)// ammo pick up
;
    qcc_precache_sound(weapons_pkup_wav_string_index)// weapon up
;
    qcc_precache_sound(items_armor1_wav_string_index)// armor up
;
    qcc_precache_sound(weapons_lhit_wav_string_index)//lightning
;
    qcc_precache_sound(weapons_lstart_wav_string_index)//lightning start
;
    qcc_precache_sound(items_damage3_wav_string_index);
    qcc_precache_sound(misc_power_wav_string_index)//lightning for boss
// player gib sounds
;
    qcc_precache_sound(player_gib_wav_string_index)// player gib sound
;
    qcc_precache_sound(player_udeath_wav_string_index)// player gib sound
;
    qcc_precache_sound(player_tornoff2_wav_string_index)// gib sound
// player pain sounds
;
    qcc_precache_sound(player_pain1_wav_string_index);
    qcc_precache_sound(player_pain2_wav_string_index);
    qcc_precache_sound(player_pain3_wav_string_index);
    qcc_precache_sound(player_pain4_wav_string_index);
    qcc_precache_sound(player_pain5_wav_string_index);
    qcc_precache_sound(player_pain6_wav_string_index)// player death sounds
;
    qcc_precache_sound(player_death1_wav_string_index);
    qcc_precache_sound(player_death2_wav_string_index);
    qcc_precache_sound(player_death3_wav_string_index);
    qcc_precache_sound(player_death4_wav_string_index);
    qcc_precache_sound(player_death5_wav_string_index)// ax sounds	
;
    qcc_precache_sound(weapons_ax1_wav_string_index)// ax swoosh
;
    qcc_precache_sound(player_axhit1_wav_string_index)// ax hit meat
;
    qcc_precache_sound(player_axhit2_wav_string_index)// ax hit world
;
    qcc_precache_sound(player_h2ojump_wav_string_index)// player jumping into water
;
    qcc_precache_sound(player_slimbrn2_wav_string_index)// player enter slime
;
    qcc_precache_sound(player_inh2o_wav_string_index)// player enter water
;
    qcc_precache_sound(player_inlava_wav_string_index)// player enter lava
;
    qcc_precache_sound(misc_outwater_wav_string_index)// leaving water sound
;
    qcc_precache_sound(player_lburn1_wav_string_index)// lava burn
;
    qcc_precache_sound(player_lburn2_wav_string_index)// lava burn
;
    qcc_precache_sound(misc_water1_wav_string_index)// swimming
;
    qcc_precache_sound(misc_water2_wav_string_index)// swimming
;
    qcc_precache_model(progs_player_mdl_string_index);
    qcc_precache_model(progs_eyes_mdl_string_index);
    qcc_precache_model(progs_h_player_mdl_string_index);
    qcc_precache_model(qcc_classname_progs_gib1_mdl);
    qcc_precache_model(qcc_classname_progs_gib2_mdl);
    qcc_precache_model(qcc_classname_progs_gib3_mdl);
    qcc_precache_model(progs_s_bubble_spr_string_index)// drowning bubbles
;
    qcc_precache_model(progs_s_explod_spr_string_index)// sprite explosion
;
    qcc_precache_model(progs_v_axe_mdl_string_index);
    qcc_precache_model(progs_v_shot_mdl_string_index);
    qcc_precache_model(progs_v_nail_mdl_string_index);
    qcc_precache_model(progs_v_rock_mdl_string_index);
    qcc_precache_model(progs_v_shot2_mdl_string_index);
    qcc_precache_model(progs_v_nail2_mdl_string_index);
    qcc_precache_model(progs_v_rock2_mdl_string_index);
    qcc_precache_model(progs_bolt_mdl_string_index)// for lightning gun
;
    qcc_precache_model(progs_bolt2_mdl_string_index)// for lightning gun
;
    qcc_precache_model(progs_bolt3_mdl_string_index)// for boss shock
;
    qcc_precache_model(progs_lavaball_mdl_string_index)// for testing
;
    qcc_precache_model(progs_missile_mdl_string_index);
    qcc_precache_model(progs_grenade_mdl_string_index);
    qcc_precache_model(progs_spike_mdl_string_index);
    qcc_precache_model(progs_s_spike_mdl_string_index);
    qcc_precache_model(progs_backpack_mdl_string_index);
    qcc_precache_model(qcc_classname_progs_zom_gib_mdl);
    qcc_precache_model(progs_v_light_mdl_string_index)//
// Setup light animation tables. 'a' is total darkness, 'z' is maxbright.
//
// 0 normal
;
    qcc_lightstyle(0.000000f, m_string_index)// 1 FLICKER (first variety)
;
    qcc_lightstyle(1.00000f, mmnmmommommnonmmonqnmmo_string_index)// 2 SLOW STRONG PULSE
;
    qcc_lightstyle(2.00000f, abcdefghijklmnopqrstuvwxyzyxwvut_2D8E8F89_long_string_index)// 3 CANDLE (first variety)
;
    qcc_lightstyle(3.00000f, mmmmmaaaaammmmmaaaaaabcdefgabcde_2A3A9297_long_string_index)// 4 FAST STROBE
;
    qcc_lightstyle(4.00000f, mamamamamama_string_index)// 5 GENTLE PULSE 1
;
    qcc_lightstyle(5.00000f, jklmnopqrstuvwxyzyxwvutsrqponmlk_939393FA_long_string_index)// 6 FLICKER (second variety)
;
    qcc_lightstyle(6.00000f, nmonqnmomnmomomno_string_index)// 7 CANDLE (second variety)
;
    qcc_lightstyle(7.00000f, mmmaaaabcdefgmmmmaaaammmaamm_string_index)// 8 CANDLE (third variety)
;
    qcc_lightstyle(8.00000f, mmmaaammmaaammmabcdefaaaammmmabc_F8076570_long_string_index)// 9 SLOW STROBE (fourth variety)
;
    qcc_lightstyle(9.00000f, aaaaaaaazzzzzzzz_string_index)// 10 FLUORESCENT FLICKER
;
    qcc_lightstyle(10.0000f, mmamammmmammamamaaamammma_string_index)// 11 SLOW PULSE NOT FADE TO BLACK
;
    qcc_lightstyle(11.0000f, abcdefghijklmnopqrrqponmlkjihgfe_B8B9B9B5_long_string_index)// styles 32-62 are assigned by the light program for switchable lights
// 63 testing
;
    qcc_lightstyle(63.0000f, a_string_index);
}
void qcc_StartFrame(void)
{
    progs.qcc_teamplay = qcc_cvar(teamplay_string_index);
    progs.qcc_skill = qcc_cvar(skill_string_index);
    progs.qcc_framecount = progs.qcc_framecount + 1;
/*
==============================================================================

BODY QUE

==============================================================================
*/}
;
void qcc_bodyque(void)
{
// just here so spawn functions don't complain after the world
// creates bodyques
}
void qcc_InitBodyQue(void)
{
    int qcc_e;
    progs.qcc_bodyque_head = qcc_spawn(qcc_classname_bodyque);
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_bodyque_head), qcc_classname_bodyque);
    set_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head), qcc_spawn(qcc_classname_bodyque));
    set_qcc_classname(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))), qcc_classname_bodyque);
    set_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))), qcc_spawn(qcc_classname_bodyque));
    set_qcc_classname(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))))), qcc_classname_bodyque);
    set_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))))), qcc_spawn(qcc_classname_bodyque));
    set_qcc_classname(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))))))), qcc_classname_bodyque);
    set_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head))))))), progs.qcc_bodyque_head);
// make a body que entry for the given ent so the ent can be
// respawned elsewhere
}
void qcc_CopyToBodyQue(int qcc_ent)
{
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_angles(PROG_TO_EDICT(qcc_ent)));
    set_qcc_model(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_model(PROG_TO_EDICT(qcc_ent)));
    set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_modelindex(PROG_TO_EDICT(qcc_ent)));
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_frame(PROG_TO_EDICT(qcc_ent)));
    set_qcc_colormap(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_colormap(PROG_TO_EDICT(qcc_ent)));
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_movetype(PROG_TO_EDICT(qcc_ent)));
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_bodyque_head), get_qcc_velocity(PROG_TO_EDICT(qcc_ent)));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_bodyque_head), 0);
    qcc_setorigin(progs.qcc_bodyque_head, get_qcc_origin(PROG_TO_EDICT(qcc_ent)));
    qcc_setsize(progs.qcc_bodyque_head, get_qcc_mins(PROG_TO_EDICT(qcc_ent)), get_qcc_maxs(PROG_TO_EDICT(qcc_ent)));
    progs.qcc_bodyque_head = get_qcc_owner(PROG_TO_EDICT(progs.qcc_bodyque_head));
//File: client.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/// prototypes
}
void qcc_W_WeaponFrame(void);
void qcc_W_SetCurrentAmmo(void);
void qcc_player_pain(void);
void qcc_player_stand1(void);
void qcc_spawn_tfog(vector );
void qcc_spawn_tdeath(vector , int );
/*
=============================================================================

				LEVEL CHANGING / INTERMISSION

=============================================================================
*/;
;
/*QUAKED info_intermission (1 0.5 0.5) (-16 -16 -16) (16 16 16)
This is the camera point for the intermission.
Use mangle instead of angle, so you can set pitch or roll as well as yaw.  'pitch roll yaw'
*/;
void qcc_info_intermission(void)
{
}
void qcc_SetChangeParms(void)
{
// remove items
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) ( (((int) (((int) (((int) (((int) (((int) qcc_IT_KEY1) | ((int) qcc_IT_KEY2))) | ((int) qcc_IT_INVISIBILITY))) | ((int) qcc_IT_INVULNERABILITY))) | ((int) qcc_IT_SUIT))) | ((int) qcc_IT_QUAD)) ))) ))// cap super health
;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) > 100)
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 100);
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < 50)
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 50);
    progs.qcc_parm1 = get_qcc_items(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm2 = get_qcc_health(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm3 = get_qcc_armorvalue(PROG_TO_EDICT(progs.qcc_self));
    if (get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self)) < 25)
        progs.qcc_parm4 = 25;
    else
        progs.qcc_parm4 = get_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm5 = get_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm6 = get_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm7 = get_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm8 = get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self));
    progs.qcc_parm9 = get_qcc_armortype(PROG_TO_EDICT(progs.qcc_self)) * 100;
}
void qcc_SetNewParms(void)
{
    progs.qcc_parm1 = (((int) qcc_IT_SHOTGUN) | ((int) qcc_IT_AXE));
    progs.qcc_parm2 = 100;
    progs.qcc_parm3 = 0;
    progs.qcc_parm4 = 25;
    progs.qcc_parm5 = 0;
    progs.qcc_parm6 = 0;
    progs.qcc_parm6 = 0;
    progs.qcc_parm8 = 1;
    progs.qcc_parm9 = 0;
}
void qcc_DecodeLevelParms(void)
{
    if (progs.qcc_serverflags)
    {
        if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_world)), maps_start_bsp_string_index))
            qcc_SetNewParms()// take away all stuff on starting new episode
;
    }
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm1);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm2);
    set_qcc_armorvalue(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm3);
    set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm4);
    set_qcc_ammo_nails(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm5);
    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm6);
    set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm7);
    set_qcc_weapon(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm8);
    set_qcc_armortype(PROG_TO_EDICT(progs.qcc_self), progs.qcc_parm9 * 0.01f);
/*
============
FindIntermission

Returns the entity to view from
============
*/}
int qcc_FindIntermission(void)
{
    int qcc_spot;
    float qcc_cyc// look for info_intermission first
;
    qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_intermission);
    if (qcc_spot)
// pick a random one
    {
        qcc_cyc = qcc_random() * 4;
        while (qcc_cyc > 1)
        {
            qcc_spot = qcc_find(qcc_spot, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_intermission);
            if ((!qcc_spot))
                qcc_spot = qcc_find(qcc_spot, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_intermission);
            qcc_cyc = qcc_cyc - 1;
        }
        return qcc_spot;
// then look for the start position
    }
    qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_start);
    if (qcc_spot)
// testinfo_player_start is only found in regioned levels
        return qcc_spot;
    qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), testplayerstart_string_index);
    if (qcc_spot)
        return qcc_spot;
    qcc_objerror(FindIntermission__no_spot_string_index);
    return progs.qcc_world;
}
;
void qcc_GotoNextMap(void)
{
// if samelevel is set, stay on same level
    if (qcc_cvar(samelevel_string_index))
        qcc_changelevel(progs.qcc_mapname);
    else
        qcc_changelevel(progs.qcc_nextmap);
}
void qcc_ExitIntermission(void)
{
// skip any text in deathmatch
    if (progs.qcc_deathmatch)
    {
        qcc_GotoNextMap();
        return;
    }
    progs.qcc_intermission_exittime = progs.qcc_time + 1;
    progs.qcc_intermission_running = progs.qcc_intermission_running + 1//
// run some text if at the end of an episode
//
;
    if (progs.qcc_intermission_running == 2)
    {
        if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_world)), maps_e1m7_bsp_string_index))
        {
            qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
            qcc_WriteByte(qcc_MSG_ALL, 2.00000f);
            qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
            if (!qcc_cvar(registered_string_index))
            {
                qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
                qcc_WriteString(qcc_MSG_ALL, As_the_corpse_of_the_monstrous_e_59D5E202_long_string_index);
            }
            else
            {
                qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
                qcc_WriteString(qcc_MSG_ALL, As_the_corpse_of_the_monstrous_e_D206AD52_long_string_index);
            }
            return;
        }
        else
            if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_world)), maps_e2m6_bsp_string_index))
            {
                qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
                qcc_WriteByte(qcc_MSG_ALL, 2.00000f);
                qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
                qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
                qcc_WriteString(qcc_MSG_ALL, The_Rune_of_Black_Magic_throbs_e_1E9916A6_long_string_index);
                return;
            }
            else
                if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_world)), maps_e3m6_bsp_string_index))
                {
                    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
                    qcc_WriteByte(qcc_MSG_ALL, 2.00000f);
                    qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
                    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
                    qcc_WriteString(qcc_MSG_ALL, The_charred_viscera_of_diabolic__DD8714D9_long_string_index);
                    return;
                }
                else
                    if (areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_world)), maps_e4m7_bsp_string_index))
                    {
                        qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
                        qcc_WriteByte(qcc_MSG_ALL, 2.00000f);
                        qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
                        qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
                        qcc_WriteString(qcc_MSG_ALL, Despite_the_awful_might_of_the_E_7A20934D_long_string_index);
                        return;
                    }
        qcc_GotoNextMap();
    }
    if (progs.qcc_intermission_running == 3)
    {
        if (!qcc_cvar(registered_string_index))
// shareware episode has been completed, go to sell screen
        {
            qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_SELLSCREEN);
            return;
        }
        if (( (((int) progs.qcc_serverflags) & ((int) 15)) ) == 15)
        {
            qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
            qcc_WriteString(qcc_MSG_ALL, Now__you_have_all_four_Runes__Yo_4B027745_long_string_index);
            return;
        }
    }
    qcc_GotoNextMap();
/*
============
IntermissionThink

When the player presses attack or jump, change to the next level
============
*/}
void qcc_IntermissionThink(void)
{
    if (progs.qcc_time < progs.qcc_intermission_exittime)
        return;
    if (((int) ((int) !get_qcc_button0(PROG_TO_EDICT(progs.qcc_self))) && ((int) !get_qcc_button1(PROG_TO_EDICT(progs.qcc_self)))) && ((int) !get_qcc_button2(PROG_TO_EDICT(progs.qcc_self))))
        return;
    qcc_ExitIntermission();
}
void qcc_execute_changelevel(void)
{
    int qcc_pos;
    progs.qcc_intermission_running = 1// enforce a wait time before allowing changelevel
;
    if (progs.qcc_deathmatch)
        progs.qcc_intermission_exittime = progs.qcc_time + 5;
    else
        progs.qcc_intermission_exittime = progs.qcc_time + 2;
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
    qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
    qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
    qcc_pos = qcc_FindIntermission();
    progs.qcc_other = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
    while (progs.qcc_other != progs.qcc_world)
    {
        set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_other), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
        set_qcc_angles(PROG_TO_EDICT(progs.qcc_other), set_qcc_v_angle(PROG_TO_EDICT(progs.qcc_other), get_qcc_mangle(PROG_TO_EDICT(qcc_pos))));
        set_qcc_fixangle(PROG_TO_EDICT(progs.qcc_other), qcc_TRUE)// turn this way immediately
;
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 0.5f);
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other), qcc_DAMAGE_NO);
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_other), qcc_SOLID_NOT);
        set_qcc_movetype(PROG_TO_EDICT(progs.qcc_other), qcc_MOVETYPE_NONE);
        set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_other), 0);
        qcc_setorigin(progs.qcc_other, get_qcc_origin(PROG_TO_EDICT(qcc_pos)));
        progs.qcc_other = qcc_find(progs.qcc_other, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
    }
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_INTERMISSION);
}
void qcc_changelevel_touch(void)
{
    int qcc_pos;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (qcc_cvar(noexit_string_index))
    {
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, 50000.0f);
        return;
    }
    qcc_bprint(get_qcc_netname(PROG_TO_EDICT(progs.qcc_other)));
    qcc_bprint(_exited_the_level_n__string_index);
    progs.qcc_nextmap = get_qcc_map(PROG_TO_EDICT(progs.qcc_self));
    qcc_SUB_UseTargets();
    if (((int) ( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 1)) )) && ((int) ( progs.qcc_deathmatch == 0 )))
// NO_INTERMISSION
    {
        qcc_GotoNextMap();
        return;
    }
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null))// we can't move people right now, because touch functions are called
// in the middle of C movement code, so set a think time to do it
;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_execute_changelevel));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
/*QUAKED trigger_changelevel (0.5 0.5 0.5) ? NO_INTERMISSION
When the player touches this, he gets sent to the map listed in the "map" variable.  Unless the NO_INTERMISSION flag is set, the view will go to the info_intermission spot and display stats.
*/}
void qcc_trigger_changelevel(void)
{
    if (isEmptyString(get_qcc_map(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(chagnelevel_trigger_doesn_t_have_DEC7707C_long_string_index);
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_changelevel_touch));
/*
=============================================================================

				PLAYER GAME EDGE FUNCTIONS

=============================================================================
*/}
// called by ClientKill and DeadThink
void qcc_set_suicide_frame(void);
void qcc_respawn(void)
{
    if (progs.qcc_coop)
// make a copy of the dead body for appearances sake
    {
        qcc_CopyToBodyQue(progs.qcc_self)// get the spawn parms as they were at level start
;
        qcc_setspawnparms(progs.qcc_self)// respawn		
;
        qcc_PutClientInServer();
    }
    else
        if (progs.qcc_deathmatch)
// make a copy of the dead body for appearances sake
        {
            qcc_CopyToBodyQue(progs.qcc_self)// set default spawn parms
;
            qcc_SetNewParms()// respawn		
;
            qcc_PutClientInServer();
        }
        else
// restart the entire server
        {
            qcc_localcmd(restart_n__string_index);
        }
/*
============
ClientKill

Player entered the suicide command
============
*/}
void qcc_ClientKill(void)
{
    qcc_bprint(get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_bprint(_suicides_n__string_index);
    qcc_set_suicide_frame();
    set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self), progs.qcc_modelindex_player);
    set_qcc_frags(PROG_TO_EDICT(progs.qcc_self), get_qcc_frags(PROG_TO_EDICT(progs.qcc_self)) - 2)// extra penalty
;
    qcc_respawn();
}
float qcc_CheckSpawnPoint(vector qcc_v)
{
    return qcc_FALSE;
/*
============
SelectSpawnPoint

Returns the entity to spawn at
============
*/}
int qcc_SelectSpawnPoint(void)
{
    int qcc_spot// testinfo_player_start is only found in regioned levels
;
    qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), testplayerstart_string_index);
    if (qcc_spot)
// choose a info_player_deathmatch point
        return qcc_spot;
    if (progs.qcc_coop)
    {
        progs.qcc_lastspawn = qcc_find(progs.qcc_lastspawn, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_coop);
        if (progs.qcc_lastspawn == progs.qcc_world)
            progs.qcc_lastspawn = qcc_find(progs.qcc_lastspawn, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_start);
        if (progs.qcc_lastspawn != progs.qcc_world)
            return progs.qcc_lastspawn;
    }
    else
        if (progs.qcc_deathmatch)
        {
            progs.qcc_lastspawn = qcc_find(progs.qcc_lastspawn, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_deathmatch);
            if (progs.qcc_lastspawn == progs.qcc_world)
                progs.qcc_lastspawn = qcc_find(progs.qcc_lastspawn, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_deathmatch);
            if (progs.qcc_lastspawn != progs.qcc_world)
                return progs.qcc_lastspawn;
        }
    if (progs.qcc_serverflags)
// return with a rune to start
    {
        qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_start2);
        if (qcc_spot)
            return qcc_spot;
    }
    qcc_spot = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_player_start);
    if ((!qcc_spot))
        qcc_error(PutClientInServer__no_info_playe_8A8E7CEF_long_string_index);
    return qcc_spot;
/*
===========
PutClientInServer

called each time a player is spawned
============
*/}
void qcc_DecodeLevelParms(void);
void qcc_PlayerDie(void);
void qcc_PutClientInServer(void)
{
    int qcc_spot;
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_player);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 100);
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_WALK);
    set_qcc_show_hostile(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_max_health(PROG_TO_EDICT(progs.qcc_self), 100);
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), qcc_FL_CLIENT);
    set_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 12);
    set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 2)// initial water damage
;
    set_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_DecodeLevelParms();
    qcc_W_SetCurrentAmmo();
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time);
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_PlayerDie));
    set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_NO)// paustime is set by teleporters to keep the player from moving a while
;
    set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_spot = qcc_SelectSpawnPoint();
    set_qcc_origin(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_spot)), (vector)  {{0.000000f, 0.000000f, 1.00000f}}));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(qcc_spot)));
    set_qcc_fixangle(PROG_TO_EDICT(progs.qcc_self), qcc_TRUE)// turn this way immediately
// oh, this is a hack!
;
    qcc_setmodel(progs.qcc_self, progs_eyes_mdl_string_index);
    progs.qcc_modelindex_eyes = get_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self));
    qcc_setmodel(progs.qcc_self, progs_player_mdl_string_index);
    progs.qcc_modelindex_player = get_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self));
    qcc_setsize(progs.qcc_self, qcc_VEC_HULL_MIN, qcc_VEC_HULL_MAX);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 22.0000f}});
    qcc_player_stand1();
    if (((int) progs.qcc_deathmatch) || ((int) progs.qcc_coop))
    {
        qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
        qcc_spawn_tfog(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 20)));
    }
    qcc_spawn_tdeath(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self);
/*
=============================================================================

				QUAKED FUNCTIONS

=============================================================================
*//*QUAKED info_player_start (1 0 0) (-16 -16 -24) (16 16 24)
The normal starting point for a level.
*/}
void qcc_info_player_start(void)
{
/*QUAKED info_player_start2 (1 0 0) (-16 -16 -24) (16 16 24)
Only used on start map for the return point from an episode.
*/}
void qcc_info_player_start2(void)
{
/*
saved out by quaked in region mode
*/}
void qcc_testplayerstart(void)
{
/*QUAKED info_player_deathmatch (1 0 1) (-16 -16 -24) (16 16 24)
potential spawning position for deathmatch games
*/}
void qcc_info_player_deathmatch(void)
{
/*QUAKED info_player_coop (1 0 1) (-16 -16 -24) (16 16 24)
potential spawning position for coop games
*/}
void qcc_info_player_coop(void)
{
/*
===============================================================================

RULES

===============================================================================
*/}
void qcc_PrintClientScore(int qcc_c)
{
    if (((int) get_qcc_frags(PROG_TO_EDICT(qcc_c)) > -10) && ((int) get_qcc_frags(PROG_TO_EDICT(qcc_c)) < 0))
        qcc_bprint(__string_index);
    else
        if (get_qcc_frags(PROG_TO_EDICT(qcc_c)) >= 0)
        {
            if (get_qcc_frags(PROG_TO_EDICT(qcc_c)) < 100)
                qcc_bprint(__string_index);
            if (get_qcc_frags(PROG_TO_EDICT(qcc_c)) < 10)
                qcc_bprint(__string_index);
        }
    qcc_bprint(qcc_ftos(get_qcc_frags(PROG_TO_EDICT(qcc_c))));
    qcc_bprint(__string_index);
    qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_c)));
    qcc_bprint(_n__string_index);
}
void qcc_DumpScore(void)
{
    int qcc_e,     qcc_sort,     qcc_walk;
    if (get_qcc_chain(PROG_TO_EDICT(progs.qcc_world)))
        qcc_error(DumpScore__world_chain_is_set_string_index)// build a sorted lis
;
    qcc_e = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
    qcc_sort = progs.qcc_world;
    while (qcc_e)
    {
        if ((!qcc_sort))
        {
            qcc_sort = qcc_e;
            set_qcc_chain(PROG_TO_EDICT(qcc_e), progs.qcc_world);
        }
        else
        {
            if (get_qcc_frags(PROG_TO_EDICT(qcc_e)) > get_qcc_frags(PROG_TO_EDICT(qcc_sort)))
            {
                set_qcc_chain(PROG_TO_EDICT(qcc_e), qcc_sort);
                qcc_sort = qcc_e;
            }
            else
            {
                qcc_walk = qcc_sort;
                do
                {
                    if ((!get_qcc_chain(PROG_TO_EDICT(qcc_walk))))
                    {
                        set_qcc_chain(PROG_TO_EDICT(qcc_e), progs.qcc_world);
                        set_qcc_chain(PROG_TO_EDICT(qcc_walk), qcc_e);
                    }
                    else
                        if (get_qcc_frags(PROG_TO_EDICT(get_qcc_chain(PROG_TO_EDICT(qcc_walk)))) < get_qcc_frags(PROG_TO_EDICT(qcc_e)))
                        {
                            set_qcc_chain(PROG_TO_EDICT(qcc_e), get_qcc_chain(PROG_TO_EDICT(qcc_walk)));
                            set_qcc_chain(PROG_TO_EDICT(qcc_walk), qcc_e);
                        }
                        else
                            qcc_walk = get_qcc_chain(PROG_TO_EDICT(qcc_walk));
                }
                while(get_qcc_chain(PROG_TO_EDICT(qcc_walk)) != qcc_e);
            }
        }
        qcc_e = qcc_find(qcc_e, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
// print the list
    }
    qcc_bprint(_n__string_index);
    while (qcc_sort)
    {
        qcc_PrintClientScore(qcc_sort);
        qcc_sort = get_qcc_chain(PROG_TO_EDICT(qcc_sort));
    }
    qcc_bprint(_n__string_index);
/*
go to the next level for deathmatch
*/}
void qcc_NextLevel(void)
{
    int qcc_o// find a trigger changelevel
;
    qcc_o = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_trigger_changelevel);
    if (((int) (!qcc_o)) || ((int) areStringsEqual(progs.qcc_mapname, start_string_index)))
// go back to same map if no trigger_changelevel
    {
        qcc_o = qcc_spawn(qcc_classname_nh_map);
        set_qcc_map(PROG_TO_EDICT(qcc_o), progs.qcc_mapname);
    }
    progs.qcc_nextmap = get_qcc_map(PROG_TO_EDICT(qcc_o));
    if (get_qcc_nextthink(PROG_TO_EDICT(qcc_o)) < progs.qcc_time)
    {
        set_qcc_think(PROG_TO_EDICT(qcc_o), getFunctionIndex(qcc_execute_changelevel));
        set_qcc_nextthink(PROG_TO_EDICT(qcc_o), progs.qcc_time + 0.1f);
    }
/*
============
CheckRules

Exit deathmatch games upon conditions
============
*/}
void qcc_CheckRules(void)
{
    float qcc_timelimit;
    float qcc_fraglimit;
// someone else quit the game already
    if (progs.qcc_gameover)
        return;
    qcc_timelimit = qcc_cvar(timelimit_string_index) * 60;
    qcc_fraglimit = qcc_cvar(fraglimit_string_index);
    if (((int) qcc_timelimit) && ((int) progs.qcc_time >= qcc_timelimit))
    {
        qcc_NextLevel()/*
		gameover = TRUE;
		bprint ("\n\n\n==============================\n");
		bprint ("game exited after ");
		bprint (ftos(timelimit/60));
		bprint (" minutes\n");
		DumpScore ();
		localcmd ("killserver\n");
*/;
        return;
    }
    if (((int) qcc_fraglimit) && ((int) get_qcc_frags(PROG_TO_EDICT(progs.qcc_self)) >= qcc_fraglimit))
    {
        qcc_NextLevel()/*
		gameover = TRUE;
		bprint ("\n\n\n==============================\n");
		bprint ("game exited after ");
		bprint (ftos(self.frags));
		bprint (" frags\n");
		DumpScore ();
		localcmd ("killserver\n");
*/;
        return;
    }
//============================================================================
}
void qcc_PlayerDeathThink(void)
{
    int qcc_old_self;
    float qcc_forward;
    if (( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ))
    {
        qcc_forward = qcc_vlen(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)));
        qcc_forward = qcc_forward - 20;
        if (qcc_forward <= 0)
            set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
        else
            set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), floatMulVector(qcc_forward, qcc_normalize(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)))));
// wait for all buttons released
    }
    if (get_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self)) == qcc_DEAD_DEAD)
    {
        if (((int) ((int) get_qcc_button2(PROG_TO_EDICT(progs.qcc_self))) || ((int) get_qcc_button1(PROG_TO_EDICT(progs.qcc_self)))) || ((int) get_qcc_button0(PROG_TO_EDICT(progs.qcc_self))))
            return;
        set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_RESPAWNABLE);
        return;
// wait for any button down
    }
    if (((int) ((int) !get_qcc_button2(PROG_TO_EDICT(progs.qcc_self))) && ((int) !get_qcc_button1(PROG_TO_EDICT(progs.qcc_self)))) && ((int) !get_qcc_button0(PROG_TO_EDICT(progs.qcc_self))))
        return;
    set_qcc_button0(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_button1(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_button2(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_respawn();
}
void qcc_PlayerJump(void)
{
    vector qcc_start,     qcc_end;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_WATERJUMP)))
        return;
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) >= 2)
    {
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_WATER)
            set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), 100);
        else
            if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_SLIME)
                set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), 80);
            else
                set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), 50)// play swiming sound
;
        if (get_qcc_swim_flag(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
            set_qcc_swim_flag(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            if (qcc_random() < 0.5f)
                qcc_sound(progs.qcc_self, qcc_CHAN_BODY, misc_water1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
            else
                qcc_sound(progs.qcc_self, qcc_CHAN_BODY, misc_water2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
        return;
    }
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ))
        return;
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_JUMPRELEASED)) ))
// don't pogo stick
        return;
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_JUMPRELEASED)) ));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_ONGROUND)// don't stairwalk
;
    set_qcc_button2(PROG_TO_EDICT(progs.qcc_self), 0)// player jumping sound
;
    qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_plyrjmp8_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z + 270);
/*
===========
WaterMove

============
*/}
void qcc_WaterMove(void)
{
//dprint (ftos(self.waterlevel));
    if (get_qcc_movetype(PROG_TO_EDICT(progs.qcc_self)) == qcc_MOVETYPE_NOCLIP)
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < 0)
        return;
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) != 3)
    {
        if (get_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_gasp2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            if (get_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time + 9)
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_gasp1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        set_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 12);
        set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 2);
    }
    else
        if (get_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
// drown!
        {
            if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            {
                set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)) + 2);
                if (get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)) > 15)
                    set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 10);
                qcc_T_Damage(progs.qcc_self, progs.qcc_world, progs.qcc_world, get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)));
                set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
        }
    if (!get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)))
    {
        if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_INWATER)))
// play leave water sound
        {
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, misc_outwater_wav_string_index, 1.00000f, qcc_ATTN_NORM);
            set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_INWATER);
        }
        return;
    }
    if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_LAVA)
// do damage
    {
        if (get_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
            if (get_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
                set_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            else
                set_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
            qcc_T_Damage(progs.qcc_self, progs.qcc_world, progs.qcc_world, 10 * get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)));
        }
    }
    else
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_SLIME)
// do damage
        {
            if (((int) get_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time) && ((int) get_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time))
            {
                set_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_T_Damage(progs.qcc_self, progs.qcc_world, progs.qcc_world, 4 * get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)));
            }
        }
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_INWATER)) ))
// player enter water sound
    {
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_LAVA)
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_inlava_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_WATER)
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_inh2o_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_SLIME)
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_slimbrn2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) + qcc_FL_INWATER);
        set_qcc_dmgtime(PROG_TO_EDICT(progs.qcc_self), 0);
    }
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_WATERJUMP)) ))
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorSub(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(0.8f * get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) * progs.qcc_frametime, get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)))));
}
void qcc_CheckWaterJump(void)
{
    vector qcc_start,     qcc_end// check for a jump-out-of-water
;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_start = get_qcc_origin(PROG_TO_EDICT(progs.qcc_self));
    qcc_start.z = qcc_start.z + 8;
    progs.qcc_v_forward.z = 0;
    qcc_normalize(progs.qcc_v_forward);
    qcc_end = vectorAdd(qcc_start, vectorMulFloat(progs.qcc_v_forward, 24));
    qcc_traceline(qcc_start, qcc_end, qcc_TRUE, progs.qcc_self);
    if (progs.qcc_trace_fraction < 1)
// solid at waist
    {
        qcc_start.z = qcc_start.z + get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)).z - 8;
        qcc_end = vectorAdd(qcc_start, vectorMulFloat(progs.qcc_v_forward, 24));
        set_qcc_movedir(PROG_TO_EDICT(progs.qcc_self), vectorMulFloat(progs.qcc_trace_plane_normal, -50));
        qcc_traceline(qcc_start, qcc_end, qcc_TRUE, progs.qcc_self);
        if (progs.qcc_trace_fraction == 1)
// open at eye level
        {
            set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_WATERJUMP)));
            set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), 225);
            set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_JUMPRELEASED)) ));
            set_qcc_teleport_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2)// safety net
;
            return;
        }
    }
/*
================
PlayerPreThink

Called every frame before physics are run
================
*/}
void qcc_PlayerPreThink(void)
{
    float qcc_mspeed,     qcc_aspeed;
    float qcc_r;
    if (progs.qcc_intermission_running)
    {
        qcc_IntermissionThink()// otherwise a button could be missed between
;
// the think tics
        return;
    }
    if (areVectorEqual(get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}}))
// intermission or finale
        return;
    qcc_makevectors(get_qcc_v_angle(PROG_TO_EDICT(progs.qcc_self)))// is this still used
;
    qcc_CheckRules();
    qcc_WaterMove();
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) == 2)
        qcc_CheckWaterJump();
    if (get_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self)) >= qcc_DEAD_DEAD)
    {
        qcc_PlayerDeathThink();
        return;
    }
    if (get_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self)) == qcc_DEAD_DYING)
// dying, so do nothing
        return;
    if (get_qcc_button2(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_PlayerJump();
    }
    else
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_JUMPRELEASED)))// teleporters can force a non-moving pause time	
;
    if (progs.qcc_time < get_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
/*
================
CheckPowerups

Check for turning off powerups
================
*/}
void qcc_CheckPowerups(void)
{
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) <= 0)
// invisibility
        return;
    if (get_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self)))
// sound and screen flash when items starts to run out
    {
        if (get_qcc_invisible_sound(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
            qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, items_inv3_wav_string_index, 0.500000f, qcc_ATTN_IDLE);
            set_qcc_invisible_sound(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + ( ( qcc_random() * 3 ) + 1 ));
        }
        if (get_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time + 3)
        {
            if (get_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_self)) == 1)
            {
                qcc_sprint(progs.qcc_self, Ring_of_Shadows_magic_is_fading_n__string_index);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, items_inv2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                set_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
            if (get_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            {
                set_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
            }
        }
        if (get_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
// just stopped
        {
            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - qcc_IT_INVISIBILITY);
            set_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self), 0);
            set_qcc_invisible_time(PROG_TO_EDICT(progs.qcc_self), 0);
// use the eyes
        }
        set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self), progs.qcc_modelindex_eyes);
    }
    else
        set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self), progs.qcc_modelindex_player)// don't use eyes
// invincibility
;
    if (get_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self)))
// sound and screen flash when items starts to run out
    {
        if (get_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time + 3)
        {
            if (get_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self)) == 1)
            {
                qcc_sprint(progs.qcc_self, Protection_is_almost_burned_out_n__string_index);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, items_protect2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                set_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
            if (get_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            {
                set_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
            }
        }
        if (get_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
// just stopped
        {
            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - qcc_IT_INVULNERABILITY);
            set_qcc_invincible_time(PROG_TO_EDICT(progs.qcc_self), 0);
            set_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self), 0);
        }
        if (get_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
            set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_DIMLIGHT)));
        else
            set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), get_qcc_effects(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_EF_DIMLIGHT)) ));
// super damage
    }
    if (get_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self)))
// sound and screen flash when items starts to run out
    {
        if (get_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time + 3)
        {
            if (get_qcc_super_time(PROG_TO_EDICT(progs.qcc_self)) == 1)
            {
                qcc_sprint(progs.qcc_self, Quad_Damage_is_wearing_off_n__string_index);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, items_damage2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                set_qcc_super_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
            if (get_qcc_super_time(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            {
                set_qcc_super_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
            }
        }
        if (get_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
// just stopped
        {
            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - qcc_IT_QUAD);
            set_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self), 0);
            set_qcc_super_time(PROG_TO_EDICT(progs.qcc_self), 0);
        }
        if (get_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
            set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_DIMLIGHT)));
        else
            set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), get_qcc_effects(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_EF_DIMLIGHT)) ));
// suit	
    }
    if (get_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 12)// don't drown
// sound and screen flash when items starts to run out
;
        if (get_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time + 3)
        {
            if (get_qcc_rad_time(PROG_TO_EDICT(progs.qcc_self)) == 1)
            {
                qcc_sprint(progs.qcc_self, Air_supply_in_Biosuit_expiring_n__string_index);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_AUTO, items_suit2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                set_qcc_rad_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
            if (get_qcc_rad_time(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
            {
                set_qcc_rad_time(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_stuffcmd(progs.qcc_self, bf_n__string_index);
            }
        }
        if (get_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
// just stopped
        {
            set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - qcc_IT_SUIT);
            set_qcc_rad_time(PROG_TO_EDICT(progs.qcc_self), 0);
            set_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self), 0);
        }
    }
/*
================
PlayerPostThink

Called every frame after physics are run
================
*/}
void qcc_PlayerPostThink(void)
{
    float qcc_mspeed,     qcc_aspeed;
    float qcc_r;
    if (areVectorEqual(get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}}))
// intermission or finale
        return;
    if (get_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self)))
// do weapon stuff
        return;
    qcc_W_WeaponFrame()// check to see if player landed and play landing sound	
;
    if (((int) ((int) ( get_qcc_jump_flag(PROG_TO_EDICT(progs.qcc_self)) < -300 )) && ((int) ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ))) && ((int) ( get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) > 0 )))
    {
        if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_WATER)
            qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_h2ojump_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            if (get_qcc_jump_flag(PROG_TO_EDICT(progs.qcc_self)) < -650)
            {
                qcc_T_Damage(progs.qcc_self, progs.qcc_world, progs.qcc_world, 5.00000f);
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_land2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                set_qcc_deathtype(PROG_TO_EDICT(progs.qcc_self), falling_string_index);
            }
            else
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_land_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        set_qcc_jump_flag(PROG_TO_EDICT(progs.qcc_self), 0);
    }
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ))
        set_qcc_jump_flag(PROG_TO_EDICT(progs.qcc_self), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z);
    qcc_CheckPowerups();
/*
===========
ClientConnect

called when a player connects to a server
============
*/}
void qcc_ClientConnect(void)
{
    qcc_bprint(get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_bprint(_entered_the_game_n__string_index)// a client connecting during an intermission can cause problems
;
    if (progs.qcc_intermission_running)
        qcc_ExitIntermission();
/*
===========
ClientDisconnect

called when a player disconnects from a server
============
*/}
void qcc_ClientDisconnect(void)
{
    if (progs.qcc_gameover)
// if the level end trigger has been activated, just return
// since they aren't *really* leaving
// let everyone else know
        return;
    qcc_bprint(get_qcc_netname(PROG_TO_EDICT(progs.qcc_self)));
    qcc_bprint(_left_the_game_with__string_index);
    qcc_bprint(qcc_ftos(get_qcc_frags(PROG_TO_EDICT(progs.qcc_self))));
    qcc_bprint(_frags_n__string_index);
    qcc_sound(progs.qcc_self, qcc_CHAN_BODY, player_tornoff2_wav_string_index, 1.00000f, qcc_ATTN_NONE);
    qcc_set_suicide_frame();
/*
===========
ClientObituary

called when a player dies
============
*/}
void qcc_ClientObituary(int qcc_targ, int qcc_attacker)
{
    float qcc_rnum;
    uint16_t qcc_deathstring,     qcc_deathstring2;
    qcc_rnum = qcc_random();
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_targ)), qcc_classname_player))
    {
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_teledeath))
        {
            qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_targ)));
            qcc_bprint(_was_telefragged_by__string_index);
            qcc_bprint(get_qcc_netname(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(qcc_attacker)))));
            qcc_bprint(_n__string_index);
            set_qcc_frags(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(qcc_attacker))), get_qcc_frags(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(qcc_attacker)))) + 1);
            return;
        }
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_teledeath2))
        {
            qcc_bprint(Satan_s_power_deflects__string_index);
            qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_targ)));
            qcc_bprint(_s_telefrag_n__string_index);
            set_qcc_frags(PROG_TO_EDICT(qcc_targ), get_qcc_frags(PROG_TO_EDICT(qcc_targ)) - 1);
            return;
        }
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_player))
        {
            if (qcc_targ == qcc_attacker)
// killed self
            {
                set_qcc_frags(PROG_TO_EDICT(qcc_attacker), get_qcc_frags(PROG_TO_EDICT(qcc_attacker)) - 1);
                qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_targ)));
                if (((int) get_qcc_weapon(PROG_TO_EDICT(qcc_targ)) == 64) && ((int) get_qcc_waterlevel(PROG_TO_EDICT(qcc_targ)) > 1))
                {
                    qcc_bprint(_discharges_into_the_water__n__string_index);
                    return;
                }
                if (get_qcc_weapon(PROG_TO_EDICT(qcc_targ)) == 16)
                    qcc_bprint(_tries_to_put_the_pin_back_in_n__string_index);
                else
                    if (qcc_rnum)
                        qcc_bprint(_becomes_bored_with_life_n__string_index);
                    else
                        qcc_bprint(_checks_if_his_weapon_is_loaded_n__string_index);
                return;
            }
            else
            {
                set_qcc_frags(PROG_TO_EDICT(qcc_attacker), get_qcc_frags(PROG_TO_EDICT(qcc_attacker)) + 1);
                qcc_rnum = get_qcc_weapon(PROG_TO_EDICT(qcc_attacker));
                if (qcc_rnum == qcc_IT_AXE)
                {
                    qcc_deathstring = _was_ax_murdered_by__string_index;
                    qcc_deathstring2 = _n__string_index;
                }
                if (qcc_rnum == qcc_IT_SHOTGUN)
                {
                    qcc_deathstring = _chewed_on__string_index;
                    qcc_deathstring2 = _s_boomstick_n__string_index;
                }
                if (qcc_rnum == qcc_IT_SUPER_SHOTGUN)
                {
                    qcc_deathstring = _ate_2_loads_of__string_index;
                    qcc_deathstring2 = _s_buckshot_n__string_index;
                }
                if (qcc_rnum == qcc_IT_NAILGUN)
                {
                    qcc_deathstring = _was_nailed_by__string_index;
                    qcc_deathstring2 = _n__string_index;
                }
                if (qcc_rnum == qcc_IT_SUPER_NAILGUN)
                {
                    qcc_deathstring = _was_punctured_by__string_index;
                    qcc_deathstring2 = _n__string_index;
                }
                if (qcc_rnum == qcc_IT_GRENADE_LAUNCHER)
                {
                    qcc_deathstring = _eats__string_index;
                    qcc_deathstring2 = _s_pineapple_n__string_index;
                    if (get_qcc_health(PROG_TO_EDICT(qcc_targ)) < -40)
                    {
                        qcc_deathstring = _was_gibbed_by__string_index;
                        qcc_deathstring2 = _s_grenade_n__string_index;
                    }
                }
                if (qcc_rnum == qcc_IT_ROCKET_LAUNCHER)
                {
                    qcc_deathstring = _rides__string_index;
                    qcc_deathstring2 = _s_rocket_n__string_index;
                    if (get_qcc_health(PROG_TO_EDICT(qcc_targ)) < -40)
                    {
                        qcc_deathstring = _was_gibbed_by__string_index;
                        qcc_deathstring2 = _s_rocket_n__string_index;
                    }
                }
                if (qcc_rnum == qcc_IT_LIGHTNING)
                {
                    qcc_deathstring = _accepts__string_index;
                    if (get_qcc_waterlevel(PROG_TO_EDICT(qcc_attacker)) > 1)
                        qcc_deathstring2 = _s_discharge_n__string_index;
                    else
                        qcc_deathstring2 = _s_shaft_n__string_index;
                }
                qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_targ)));
                qcc_bprint(qcc_deathstring);
                qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_attacker)));
                qcc_bprint(qcc_deathstring2);
            }
            return;
        }
        else
        {
            set_qcc_frags(PROG_TO_EDICT(qcc_targ), get_qcc_frags(PROG_TO_EDICT(qcc_targ)) - 1)// killed self
;
            qcc_rnum = get_qcc_watertype(PROG_TO_EDICT(qcc_targ));
            qcc_bprint(get_qcc_netname(PROG_TO_EDICT(qcc_targ)));
            if (qcc_rnum == -3)
            {
                if (qcc_random() < 0.5f)
                    qcc_bprint(_sleeps_with_the_fishes_n__string_index);
                else
                    qcc_bprint(_sucks_it_down_n__string_index);
                return;
            }
            else
                if (qcc_rnum == -4)
                {
                    if (qcc_random() < 0.5f)
                        qcc_bprint(_gulped_a_load_of_slime_n__string_index);
                    else
                        qcc_bprint(_can_t_exist_on_slime_alone_n__string_index);
                    return;
                }
                else
                    if (qcc_rnum == -5)
                    {
                        if (get_qcc_health(PROG_TO_EDICT(qcc_targ)) < -15)
                        {
                            qcc_bprint(_burst_into_flames_n__string_index);
                            return;
                        }
                        if (qcc_random() < 0.5f)
                            qcc_bprint(_turned_into_hot_slag_n__string_index);
                        else
                            qcc_bprint(_visits_the_Volcano_God_n__string_index);
                        return;
                    }
            if ((((int) get_qcc_flags(PROG_TO_EDICT(qcc_attacker))) & ((int) qcc_FL_MONSTER)))
            {
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_army))
                    qcc_bprint(_was_shot_by_a_Grunt_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_demon1))
                    qcc_bprint(_was_eviscerated_by_a_Fiend_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_dog))
                    qcc_bprint(_was_mauled_by_a_Rottweiler_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), monster_dragon_string_index))
                    qcc_bprint(_was_fried_by_a_Dragon_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_enforcer))
                    qcc_bprint(_was_blasted_by_an_Enforcer_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_fish))
                    qcc_bprint(_was_fed_to_the_Rotfish_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_hell_knight))
                    qcc_bprint(_was_slain_by_a_Death_Knight_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_knight))
                    qcc_bprint(_was_slashed_by_a_Knight_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_ogre))
                    qcc_bprint(_was_destroyed_by_an_Ogre_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_oldone))
                    qcc_bprint(_became_one_with_Shub_Niggurath_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_shalrath))
                    qcc_bprint(_was_exploded_by_a_Vore_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_shambler))
                    qcc_bprint(_was_smashed_by_a_Shambler_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_tarbaby))
                    qcc_bprint(_was_slimed_by_a_Spawn_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), monster_vomit_string_index))
                    qcc_bprint(_was_vomited_on_by_a_Vomitus_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_wizard))
                    qcc_bprint(_was_scragged_by_a_Scrag_n__string_index);
                if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_monster_zombie))
                    qcc_bprint(_joins_the_Zombies_n__string_index);
                return;
            }
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_explo_box))
            {
                qcc_bprint(_blew_up_n__string_index);
                return;
            }
            if (((int) get_qcc_solid(PROG_TO_EDICT(qcc_attacker)) == qcc_SOLID_BSP) && ((int) qcc_attacker != progs.qcc_world))
            {
                qcc_bprint(_was_squished_n__string_index);
                return;
            }
            if (areStringsEqual(get_qcc_deathtype(PROG_TO_EDICT(qcc_targ)), falling_string_index))
            {
                set_qcc_deathtype(PROG_TO_EDICT(qcc_targ), NULL_string_index);
                qcc_bprint(_fell_to_his_death_n__string_index);
                return;
            }
            if (((int) areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_trap_shooter)) || ((int) areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_trap_spikeshooter)))
            {
                qcc_bprint(_was_spiked_n__string_index);
                return;
            }
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_fireball))
            {
                qcc_bprint(_ate_a_lavaball_n__string_index);
                return;
            }
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(qcc_attacker)), qcc_classname_trigger_changelevel))
            {
                qcc_bprint(_tried_to_leave_n__string_index);
                return;
            }
            qcc_bprint(_died_n__string_index);
        }
    }
//File: player.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
/*
==============================================================================

PLAYER

==============================================================================
*///
// running
//
//
// standing
//
//
// pain
//
//
// death
//
//
// attacks
//
/*
==============================================================================
PLAYER
==============================================================================
*/void qcc_bubble_bob(void);
void qcc_player_run(void);
void qcc_player_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_stand1));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
    if (((int) get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).x) || ((int) get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).y))
    {
        set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        qcc_player_run();
        return;
    }
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
    {
        if (get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) >= 12)
            set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17 + get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)));
    }
    else
    {
        if (get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) >= 5)
            set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12 + get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)));
    }
    set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
}
void qcc_player_run(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
    if (((int) !get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).x) && ((int) !get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).y))
    {
        set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        qcc_player_stand1();
        return;
    }
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
    {
        if (get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) == 6)
            set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0 + get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)));
    }
    else
    {
        if (get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) == 6)
            set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), 0);
        set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), get_qcc_frame(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)));
    }
    set_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_walkframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
}
void qcc_player_shot1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 113); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_shot2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
}
void qcc_player_shot2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 114); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_shot3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 2);
}
void qcc_player_shot3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 115); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_shot4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 3);
}
void qcc_player_shot4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 116); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_shot5));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 4);
}
void qcc_player_shot5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 117); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_shot6));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 5);
}
void qcc_player_shot6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 118); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 6);
}
void qcc_player_axe1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 119); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axe2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
}
void qcc_player_axe2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 120); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axe3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 2);
}
void qcc_player_axe3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 121); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axe4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 3);
    qcc_W_FireAxe();
}
void qcc_player_axe4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 122); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 4);
}
void qcc_player_axeb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 125); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axeb2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 5);
}
void qcc_player_axeb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 126); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axeb3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 6);
}
void qcc_player_axeb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 127); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axeb4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 7);
    qcc_W_FireAxe();
}
void qcc_player_axeb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 128); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 8);
}
void qcc_player_axec1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 131); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axec2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
}
void qcc_player_axec2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 132); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axec3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 2);
}
void qcc_player_axec3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 133); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axec4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 3);
    qcc_W_FireAxe();
}
void qcc_player_axec4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 134); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 4);
}
void qcc_player_axed1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 137); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axed2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 5);
}
void qcc_player_axed2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 138); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axed3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 6);
}
void qcc_player_axed3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 139); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axed4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 7);
    qcc_W_FireAxe();
}
void qcc_player_axed4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 140); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 8);
//============================================================================
}
void qcc_player_nail1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_nail2));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    if (!get_qcc_button0(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_player_run();
        return;
    }
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) == 9)
        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_SuperDamageSound();
    qcc_W_FireSpikes(4.00000f);
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
}
void qcc_player_nail2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_nail1));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    if (!get_qcc_button0(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_player_run();
        return;
    }
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) == 9)
        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_SuperDamageSound();
    qcc_W_FireSpikes(-4.00000f);
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
//============================================================================
}
void qcc_player_light1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_light2));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    if (!get_qcc_button0(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_player_run();
        return;
    }
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) == 5)
        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_SuperDamageSound();
    qcc_W_FireLightning();
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
}
void qcc_player_light2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 106); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_light1));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    if (!get_qcc_button0(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_player_run();
        return;
    }
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)) == 5)
        set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_SuperDamageSound();
    qcc_W_FireLightning();
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
//============================================================================
}
void qcc_player_rocket1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 107); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_rocket2));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
}
void qcc_player_rocket2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 108); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_rocket3));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 2);
}
void qcc_player_rocket3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 109); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_rocket4));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 3);
}
void qcc_player_rocket4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 110); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_rocket5));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 4);
}
void qcc_player_rocket5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 111); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_rocket6));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 5);
}
void qcc_player_rocket6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 112); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 6);
}
void qcc_DeathBubbles(float );
void qcc_PainSound(void)
{
    float qcc_rs;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < 0)
        return;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_damage_attacker)), qcc_classname_teledeath))
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_teledth1_wav_string_index, 1.00000f, qcc_ATTN_NONE);
        return;
// water pain sounds
    }
    if (((int) get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_WATER) && ((int) get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) == 3))
    {
        qcc_DeathBubbles(1.00000f);
        if (qcc_random() > 0.5f)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_drown1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_drown2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        return;
// slime pain sounds
    }
    if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_SLIME)
// FIX ME	put in some steam here
    {
        if (qcc_random() > 0.5f)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_lburn1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_lburn2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        return;
    }
    if (get_qcc_watertype(PROG_TO_EDICT(progs.qcc_self)) == qcc_CONTENT_LAVA)
    {
        if (qcc_random() > 0.5f)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_lburn1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        else
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_lburn2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        return;
    }
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
    {
        set_qcc_axhitme(PROG_TO_EDICT(progs.qcc_self), 0);
        return;
    }
    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f)// don't make multiple pain sounds right after each other
// ax pain sound
;
    if (get_qcc_axhitme(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        set_qcc_axhitme(PROG_TO_EDICT(progs.qcc_self), 0);
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_axhit1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        return;
    }
    qcc_rs = qcc_rint(( qcc_random() * 5 ) + 1);
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
    if (qcc_rs == 1)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain1_wav_string_index);
    else
        if (qcc_rs == 2)
            set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain2_wav_string_index);
        else
            if (qcc_rs == 3)
                set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain3_wav_string_index);
            else
                if (qcc_rs == 4)
                    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain4_wav_string_index);
                else
                    if (qcc_rs == 5)
                        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain5_wav_string_index);
                    else
                        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_pain6_wav_string_index);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    return;
}
void qcc_player_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain2));
    qcc_PainSound();
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
}
void qcc_player_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain3));
}
void qcc_player_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain4));
}
void qcc_player_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain5));
}
void qcc_player_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_pain6));
}
void qcc_player_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
}
void qcc_player_axpain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axpain2));
    qcc_PainSound();
    set_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self), 0);
}
void qcc_player_axpain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axpain3));
}
void qcc_player_axpain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axpain4));
}
void qcc_player_axpain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axpain5));
}
void qcc_player_axpain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_axpain6));
}
void qcc_player_axpain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_run));
}
void qcc_player_pain(void)
{
    if (get_qcc_weaponframe(PROG_TO_EDICT(progs.qcc_self)))
        return;
    if (get_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
// eyes don't have pain frames
        return;
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
        qcc_player_axpain1();
    else
        qcc_player_pain1();
}
void qcc_player_diea1(void);
void qcc_player_dieb1(void);
void qcc_player_diec1(void);
void qcc_player_died1(void);
void qcc_player_diee1(void);
void qcc_player_die_ax1(void);
// next-hack added because setting self.think=DeathBubblesSpawn will generate bad code... 
void qcc_DeathBubblesSpawn(void);
void qcc_DeathBubblesSpawn(void)
{
    int qcc_bubble;
    if (get_qcc_waterlevel(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))) != 3)
        return;
    qcc_bubble = qcc_spawn(qcc_classname_bubble);
    qcc_setmodel(qcc_bubble, progs_s_bubble_spr_string_index);
    qcc_setorigin(qcc_bubble, vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))), (vector)  {{0.000000f, 0.000000f, 24.0000f}}));
    set_qcc_movetype(PROG_TO_EDICT(qcc_bubble), qcc_MOVETYPE_NOCLIP);
    set_qcc_solid(PROG_TO_EDICT(qcc_bubble), qcc_SOLID_NOT);
    set_qcc_velocity(PROG_TO_EDICT(qcc_bubble), (vector)  {{0.000000f, 0.000000f, 15.0000f}});
    set_qcc_nextthink(PROG_TO_EDICT(qcc_bubble), progs.qcc_time + 0.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_bubble), getFunctionIndex(qcc_bubble_bob));
    set_qcc_classname(PROG_TO_EDICT(qcc_bubble), qcc_classname_bubble);
    set_qcc_frame(PROG_TO_EDICT(qcc_bubble), 0);
    set_qcc_cnt(PROG_TO_EDICT(qcc_bubble), 0);
    qcc_setsize(qcc_bubble, (vector) {{-8.00000f, -8.00000f, -8.00000f}}, (vector) {{8.00000f, 8.00000f, 8.00000f}});
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_DeathBubblesSpawn));
    set_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self), get_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_air_finished(PROG_TO_EDICT(progs.qcc_self)) >= get_qcc_bubble_count(PROG_TO_EDICT(progs.qcc_self)))
        qcc_remove(progs.qcc_self);
}
void qcc_DeathBubbles(float qcc_num_bubbles)
{
    int qcc_bubble_spawner;
    qcc_bubble_spawner = qcc_spawn(qcc_classname_bubble);
    qcc_setorigin(qcc_bubble_spawner, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_movetype(PROG_TO_EDICT(qcc_bubble_spawner), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(qcc_bubble_spawner), qcc_SOLID_NOT);
    set_qcc_nextthink(PROG_TO_EDICT(qcc_bubble_spawner), progs.qcc_time + 0.1f);
    set_qcc_think(PROG_TO_EDICT(qcc_bubble_spawner), getFunctionIndex(qcc_DeathBubblesSpawn));
    set_qcc_air_finished(PROG_TO_EDICT(qcc_bubble_spawner), 0);
    set_qcc_owner(PROG_TO_EDICT(qcc_bubble_spawner), progs.qcc_self);
    set_qcc_bubble_count(PROG_TO_EDICT(qcc_bubble_spawner), qcc_num_bubbles);
    return;
}
void qcc_DeathSound(void)
{
    float qcc_rs// water death sounds
;
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) == 3)
    {
        qcc_DeathBubbles(20.0000f);
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_h2odeath_wav_string_index, 1.00000f, qcc_ATTN_NONE);
        return;
    }
    qcc_rs = qcc_rint(( qcc_random() * 4 ) + 1);
    if (qcc_rs == 1)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_death1_wav_string_index);
    if (qcc_rs == 2)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_death2_wav_string_index);
    if (qcc_rs == 3)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_death3_wav_string_index);
    if (qcc_rs == 4)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_death4_wav_string_index);
    if (qcc_rs == 5)
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), player_death5_wav_string_index);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NONE);
    return;
}
void qcc_PlayerDead(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1)// allow respawn after a certain time
;
    set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_DEAD);
}
vector qcc_VelocityForDamage(float qcc_dm)
{
    vector qcc_v;
    qcc_v.x = 100 * qcc_crandom();
    qcc_v.y = 100 * qcc_crandom();
    qcc_v.z = 200 + 100 * qcc_random();
    if (qcc_dm > -50)
//		dprint ("level 1\n");
    {
        qcc_v = vectorMulFloat(qcc_v, 0.7f);
    }
    else
        if (qcc_dm > -200)
//		dprint ("level 3\n");
        {
            qcc_v = vectorMulFloat(qcc_v, 2);
        }
        else
            qcc_v = vectorMulFloat(qcc_v, 10);
    return qcc_v;
}
void qcc_ThrowGib(uint16_t qcc_gibname, float qcc_dm)
{
    int qcc_new;
    qcc_new = qcc_spawn(qcc_gibname);
    set_qcc_origin(PROG_TO_EDICT(qcc_new), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setmodel(qcc_new, qcc_gibname);
    qcc_setsize(qcc_new, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_velocity(PROG_TO_EDICT(qcc_new), qcc_VelocityForDamage(qcc_dm));
    set_qcc_movetype(PROG_TO_EDICT(qcc_new), qcc_MOVETYPE_BOUNCE);
    set_qcc_solid(PROG_TO_EDICT(qcc_new), qcc_SOLID_NOT);
    set_qcc_avelocity_x(PROG_TO_EDICT(qcc_new), qcc_random() * 600);
    set_qcc_avelocity_y(PROG_TO_EDICT(qcc_new), qcc_random() * 600);
    set_qcc_avelocity_z(PROG_TO_EDICT(qcc_new), qcc_random() * 600);
    set_qcc_think(PROG_TO_EDICT(qcc_new), getFunctionIndex(qcc_SUB_Remove));
    set_qcc_ltime(PROG_TO_EDICT(qcc_new), progs.qcc_time);
    set_qcc_nextthink(PROG_TO_EDICT(qcc_new), progs.qcc_time + 10 + qcc_random() * 10);
    set_qcc_frame(PROG_TO_EDICT(qcc_new), 0);
    set_qcc_flags(PROG_TO_EDICT(qcc_new), 0);
}
void qcc_ThrowHead(uint16_t qcc_gibname, float qcc_dm)
{
    qcc_setmodel(progs.qcc_self, qcc_gibname);
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_BOUNCE);
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 8.00000f}});
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, 0.000000f}}, (vector) {{16.0000f, 16.0000f, 56.0000f}});
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), qcc_VelocityForDamage(qcc_dm));
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z - 24);
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ));
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), floatMulVector(qcc_crandom(), (vector)  {{0.000000f, 600.000f, 0.000000f}}));
}
void qcc_GibPlayer(void)
{
    qcc_ThrowHead(progs_h_player_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_DEAD);
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_damage_attacker)), qcc_classname_teledeath))
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_teledth1_wav_string_index, 1.00000f, qcc_ATTN_NONE);
        return;
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_damage_attacker)), qcc_classname_teledeath2))
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_teledth1_wav_string_index, 1.00000f, qcc_ATTN_NONE);
        return;
    }
    if (qcc_random() < 0.5f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_gib_wav_string_index, 1.00000f, qcc_ATTN_NONE);
    else
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NONE);
}
void qcc_PlayerDie(void)
{
    float qcc_i;
    set_qcc_items(PROG_TO_EDICT(progs.qcc_self), get_qcc_items(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_IT_INVISIBILITY)) ));
    set_qcc_invisible_finished(PROG_TO_EDICT(progs.qcc_self), 0)// don't die as eyes
;
    set_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_super_damage_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_radsuit_finished(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_modelindex(PROG_TO_EDICT(progs.qcc_self), progs.qcc_modelindex_player)// don't use eyes
;
    if (((int) progs.qcc_deathmatch) || ((int) progs.qcc_coop))
        qcc_DropBackpack();
    set_qcc_weaponmodel(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, -8.00000f}});
    set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_DYING);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ));
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_TOSS);
    if (get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z < 10)
        set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z + qcc_random() * 300);
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -40)
    {
        qcc_GibPlayer();
        return;
    }
    qcc_DeathSound();
    set_qcc_angles_x(PROG_TO_EDICT(progs.qcc_self), 0);
    set_qcc_angles_z(PROG_TO_EDICT(progs.qcc_self), 0);
    if (get_qcc_weapon(PROG_TO_EDICT(progs.qcc_self)) == qcc_IT_AXE)
    {
        qcc_player_die_ax1();
        return;
    }
    qcc_i = qcc_cvar(temp1_string_index);
    if (!qcc_i)
        qcc_i = 1 + qcc_floor(qcc_random() * 6);
    if (qcc_i == 1)
        qcc_player_diea1();
    else
        if (qcc_i == 2)
            qcc_player_dieb1();
        else
            if (qcc_i == 3)
                qcc_player_diec1();
            else
                if (qcc_i == 4)
                    qcc_player_died1();
                else
                    qcc_player_diee1();
}
void qcc_set_suicide_frame(void)
{
// used by klill command and diconnect command
    if ((!areStringsEqual(get_qcc_model(PROG_TO_EDICT(progs.qcc_self)), progs_player_mdl_string_index)))
// allready gibbed
        return;
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_TOSS);
    set_qcc_deadflag(PROG_TO_EDICT(progs.qcc_self), qcc_DEAD_DEAD);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1);
}
void qcc_player_diea1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea2));
}
void qcc_player_diea2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea3));
}
void qcc_player_diea3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea4));
}
void qcc_player_diea4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea5));
}
void qcc_player_diea5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea6));
}
void qcc_player_diea6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea7));
}
void qcc_player_diea7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea8));
}
void qcc_player_diea8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea9));
}
void qcc_player_diea9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea10));
}
void qcc_player_diea10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea11));
}
void qcc_player_diea11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diea11));
    qcc_PlayerDead();
}
void qcc_player_dieb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb2));
}
void qcc_player_dieb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb3));
}
void qcc_player_dieb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb4));
}
void qcc_player_dieb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb5));
}
void qcc_player_dieb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb6));
}
void qcc_player_dieb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb7));
}
void qcc_player_dieb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb8));
}
void qcc_player_dieb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb9));
}
void qcc_player_dieb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_dieb9));
    qcc_PlayerDead();
}
void qcc_player_diec1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec2));
}
void qcc_player_diec2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec3));
}
void qcc_player_diec3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec4));
}
void qcc_player_diec4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec5));
}
void qcc_player_diec5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec6));
}
void qcc_player_diec6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec7));
}
void qcc_player_diec7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec8));
}
void qcc_player_diec8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec9));
}
void qcc_player_diec9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec10));
}
void qcc_player_diec10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec11));
}
void qcc_player_diec11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec12));
}
void qcc_player_diec12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec13));
}
void qcc_player_diec13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec14));
}
void qcc_player_diec14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec15));
}
void qcc_player_diec15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diec15));
    qcc_PlayerDead();
}
void qcc_player_died1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died2));
}
void qcc_player_died2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died3));
}
void qcc_player_died3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died4));
}
void qcc_player_died4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died5));
}
void qcc_player_died5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died6));
}
void qcc_player_died6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died7));
}
void qcc_player_died7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died8));
}
void qcc_player_died8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died9));
}
void qcc_player_died9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_died9));
    qcc_PlayerDead();
}
void qcc_player_diee1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee2));
}
void qcc_player_diee2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee3));
}
void qcc_player_diee3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee4));
}
void qcc_player_diee4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee5));
}
void qcc_player_diee5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee6));
}
void qcc_player_diee6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee7));
}
void qcc_player_diee7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee8));
}
void qcc_player_diee8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee9));
}
void qcc_player_diee9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_diee9));
    qcc_PlayerDead();
}
void qcc_player_die_ax1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax2));
}
void qcc_player_die_ax2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax3));
}
void qcc_player_die_ax3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax4));
}
void qcc_player_die_ax4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax5));
}
void qcc_player_die_ax5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax6));
}
void qcc_player_die_ax6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax7));
}
void qcc_player_die_ax7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax8));
}
void qcc_player_die_ax8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax9));
}
void qcc_player_die_ax9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_player_die_ax9));
    qcc_PlayerDead();
//File: monsters.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//* ALL MONSTERS SHOULD BE 1 0 0 IN COLOR */// name =[framenum,	nexttime, nextthink] {code}
// expands to:
// name ()
// {
//		self.frame=framenum;
//		self.nextthink = time + nexttime;
//		self.think = nextthink
//		<code>
// };
/*
================
monster_use

Using a monster makes it angry at the current activator
================
*/}
void qcc_monster_use(void)
{
    if (get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) <= 0)
        return;
    if ((((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_activator))) & ((int) qcc_IT_INVISIBILITY)))
        return;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_activator))) & ((int) qcc_FL_NOTARGET)))
        return;
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_activator)), qcc_classname_player)))
// delay reaction so if the monster is teleported, its sound is still
// heard
        return;
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_FoundTarget));
/*
================
monster_death_use

When a mosnter dies, it fires all of its targets with the current
enemy as activator.
================
*/}
void qcc_monster_death_use(void)
{
    int qcc_ent,     qcc_otemp,     qcc_stemp// fall to ground
;
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_FLY)))
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_FLY);
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_SWIM)))
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_SWIM);
    if (isEmptyString(get_qcc_target(PROG_TO_EDICT(progs.qcc_self))))
        return;
    progs.qcc_activator = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    qcc_SUB_UseTargets();
//============================================================================
}
void qcc_walkmonster_start_go(void)
{
    uint16_t qcc_stemp;
    int qcc_etemp;
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 1)// raise off floor a bit
;
    qcc_droptofloor();
    if (!qcc_walkmove(0.000000f, 0.000000f))
    {
        qcc_dprint(walkmonster_in_wall_at___string_index);
        qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_dprint(_n__string_index);
    }
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), dotProduct(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 1.00000f, 0.000000f}}));
    if (!get_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self), 20);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 25.0000f}});
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_monster_use));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_MONSTER)));
    if (get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self), set_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self), qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))));
        set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
        if ((!get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self))))
        {
            qcc_dprint(Monster_can_t_find_target_at__string_index);
            qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
            qcc_dprint(_n__string_index);
// this used to be an objerror
        }
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_path_corner))
            ((void (*)() )getFunction(get_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self))))();
        else
            set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 100000000);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
    }
    else
    {
        set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 100000000);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
// spread think times so they don't all happen at same time
    }
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.5f);
}
void qcc_walkmonster_start(void)
{
// delay drop to floor to make sure all doors have been spawned
// spread think times so they don't all happen at same time
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.5f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_walkmonster_start_go));
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
}
void qcc_flymonster_start_go(void)
{
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), dotProduct(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 1.00000f, 0.000000f}}));
    if (!get_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self), 10);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 25.0000f}});
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_monster_use));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_FLY)));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_MONSTER)));
    if (!qcc_walkmove(0.000000f, 0.000000f))
    {
        qcc_dprint(flymonster_in_wall_at___string_index);
        qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_dprint(_n__string_index);
    }
    if (get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self), set_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self), qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))));
        if ((!get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self))))
        {
            qcc_dprint(Monster_can_t_find_target_at__string_index);
            qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
            qcc_dprint(_n__string_index);
// this used to be an objerror
        }
        if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_path_corner))
            ((void (*)() )getFunction(get_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self))))();
        else
            set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 100000000);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
    }
    else
    {
        set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 100000000);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
    }
}
void qcc_flymonster_start(void)
{
// spread think times so they don't all happen at same time
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.5f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_flymonster_start_go));
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
}
void qcc_swimmonster_start_go(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
    set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), dotProduct(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 1.00000f, 0.000000f}}));
    if (!get_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self), 10);
    set_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 10.0000f}});
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_monster_use));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_SWIM)));
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_FL_MONSTER)));
    if (get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self), set_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self), qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)))));
        if ((!get_qcc_movetarget(PROG_TO_EDICT(progs.qcc_self))))
        {
            qcc_dprint(Monster_can_t_find_target_at__string_index);
            qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
            qcc_dprint(_n__string_index);
// this used to be an objerror
        }
        set_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self), qcc_vectoyaw(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_goalentity(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
        ((void (*)() )getFunction(get_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self))))();
    }
    else
    {
        set_qcc_pausetime(PROG_TO_EDICT(progs.qcc_self), 100000000);
        ((void (*)() )getFunction(get_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self))))();
// spread think times so they don't all happen at same time
    }
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.5f);
}
void qcc_swimmonster_start(void)
{
// spread think times so they don't all happen at same time
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.5f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_swimmonster_start_go));
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
//File: doors.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
const float qcc_DOOR_START_OPEN = 1;
const float qcc_DOOR_DONT_LINK = 4;
const float qcc_DOOR_GOLD_KEY = 8;
const float qcc_DOOR_SILVER_KEY = 16;
const float qcc_DOOR_TOGGLE = 32/*

Doors are similar to buttons, but can spawn a fat trigger field around them
to open without a touch, and they link together to form simultanious
double/quad doors.
 
Door.owner is the master door.  If there is only one door, it points to itself.
If multiple doors, all will point to a single one.

Door.enemy chains from the master door through all doors linked in the chain.

*//*
=============================================================================

THINK FUNCTIONS

=============================================================================
*/;
void qcc_door_go_down(void);
void qcc_door_go_up(void);
void qcc_door_blocked(void)
{
    qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)))// if a door has a negative wait, it would never come back if blocked,
// so let it just squash the object to death real fast
;
    if (get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)) >= 0)
    {
        if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_DOWN)
            qcc_door_go_up();
        else
            qcc_door_go_down();
    }
}
void qcc_door_hit_top(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_TOP);
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_DOOR_TOGGLE)))
// don't come down automatically
        return;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_door_go_down));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
}
void qcc_door_hit_bottom(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
}
void qcc_door_go_down(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    if (get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)));
    }
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_DOWN);
    qcc_SUB_CalcMove(get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_door_hit_bottom));
}
void qcc_door_go_up(void)
{
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_UP)
// allready going up
        return;
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_TOP)
// reset top wait time
    {
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_UP);
    qcc_SUB_CalcMove(get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_door_hit_top));
    qcc_SUB_UseTargets();
/*
=============================================================================

ACTIVATION FUNCTIONS

=============================================================================
*/}
void qcc_door_fire(void)
{
    int qcc_oself;
    int qcc_starte;
    if (get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)) != progs.qcc_self)
        qcc_objerror(door_fire__self_owner____self_string_index)// play use key sound
;
    if (get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise4(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_message(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null)// no more message
;
    qcc_oself = progs.qcc_self;
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_DOOR_TOGGLE)))
    {
        if (((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_UP) || ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_TOP))
        {
            qcc_starte = progs.qcc_self;
            do
            {
                qcc_door_go_down();
                progs.qcc_self = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
            }
            while(((int) ( progs.qcc_self != qcc_starte )) && ((int) ( progs.qcc_self != progs.qcc_world )));
            progs.qcc_self = qcc_oself;
            return;
        }
// trigger all paired doors
    }
    qcc_starte = progs.qcc_self;
    do
    {
        qcc_door_go_up();
        progs.qcc_self = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    }
    while(((int) ( progs.qcc_self != qcc_starte )) && ((int) ( progs.qcc_self != progs.qcc_world )));
    progs.qcc_self = qcc_oself;
}
void qcc_door_use(void)
{
    int qcc_oself;
    set_qcc_message(PROG_TO_EDICT(progs.qcc_self), NULL_string_index)// door message are for touch only
;
    set_qcc_message(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), NULL_string_index);
    set_qcc_message(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))), NULL_string_index);
    qcc_oself = progs.qcc_self;
    progs.qcc_self = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
    qcc_door_fire();
    progs.qcc_self = qcc_oself;
}
void qcc_door_trigger_touch(void)
{
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    progs.qcc_activator = progs.qcc_other;
    progs.qcc_self = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
    qcc_door_use();
}
void qcc_door_killed(void)
{
    int qcc_oself;
    qcc_oself = progs.qcc_self;
    progs.qcc_self = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO)// wil be reset upon return
;
    qcc_door_use();
    progs.qcc_self = qcc_oself;
/*
================
door_touch

Prints messages and opens key doors
================
*/}
void qcc_door_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_attack_finished(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))) > progs.qcc_time)
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), progs.qcc_time + 2);
    if ((!areStringsEqual(get_qcc_message(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))), NULL_string_index)))
    {
        qcc_centerprint(progs.qcc_other, get_qcc_message(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))));
        qcc_sound(progs.qcc_other, qcc_CHAN_VOICE, misc_talk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
// key door stuff
    }
    if (!get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))
// FIXME: blink key on player's status bar
        return;
    if (( (((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_self))) & ((int) get_qcc_items(PROG_TO_EDICT(progs.qcc_other)))) ) != get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))
    {
        if (get_qcc_items(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))) == qcc_IT_KEY1)
        {
            if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
            {
                qcc_centerprint(progs.qcc_other, You_need_the_silver_keycard_string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
            }
            else
                if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
                {
                    qcc_centerprint(progs.qcc_other, You_need_the_silver_runekey_string_index);
                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
                }
                else
                    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
                    {
                        qcc_centerprint(progs.qcc_other, You_need_the_silver_key_string_index);
                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
                    }
        }
        else
        {
            if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
            {
                qcc_centerprint(progs.qcc_other, You_need_the_gold_keycard_string_index);
                qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
            }
            else
                if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
                {
                    qcc_centerprint(progs.qcc_other, You_need_the_gold_runekey_string_index);
                    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
                }
                else
                    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
                    {
                        qcc_centerprint(progs.qcc_other, You_need_the_gold_key_string_index);
                        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
                    }
        }
        return;
    }
    set_qcc_items(PROG_TO_EDICT(progs.qcc_other), get_qcc_items(PROG_TO_EDICT(progs.qcc_other)) - get_qcc_items(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    if (get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_touch(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))), getFunctionIndex(qcc_SUB_Null))// get paired door
;
    qcc_door_use();
/*
=============================================================================

SPAWNING FUNCTIONS

=============================================================================
*/}
int qcc_spawn_field(vector qcc_fmins, vector qcc_fmaxs)
{
    int qcc_trigger;
    vector qcc_t1,     qcc_t2;
    qcc_trigger = qcc_spawn(qcc_classname_nh_trigger)// next-hack
;
    set_qcc_movetype(PROG_TO_EDICT(qcc_trigger), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(qcc_trigger), qcc_SOLID_TRIGGER);
    set_qcc_owner(PROG_TO_EDICT(qcc_trigger), progs.qcc_self);
    set_qcc_touch(PROG_TO_EDICT(qcc_trigger), getFunctionIndex(qcc_door_trigger_touch));
    qcc_t1 = qcc_fmins;
    qcc_t2 = qcc_fmaxs;
    qcc_setsize(qcc_trigger, vectorSub(qcc_t1, (vector)  {{60.0000f, 60.0000f, 8.00000f}}), vectorAdd(qcc_t2, (vector)  {{60.0000f, 60.0000f, 8.00000f}}));
    return ( qcc_trigger );
}
float qcc_EntitiesTouching(int qcc_e1, int qcc_e2)
{
    if (get_qcc_mins(PROG_TO_EDICT(qcc_e1)).x > get_qcc_maxs(PROG_TO_EDICT(qcc_e2)).x)
        return qcc_FALSE;
    if (get_qcc_mins(PROG_TO_EDICT(qcc_e1)).y > get_qcc_maxs(PROG_TO_EDICT(qcc_e2)).y)
        return qcc_FALSE;
    if (get_qcc_mins(PROG_TO_EDICT(qcc_e1)).z > get_qcc_maxs(PROG_TO_EDICT(qcc_e2)).z)
        return qcc_FALSE;
    if (get_qcc_maxs(PROG_TO_EDICT(qcc_e1)).x < get_qcc_mins(PROG_TO_EDICT(qcc_e2)).x)
        return qcc_FALSE;
    if (get_qcc_maxs(PROG_TO_EDICT(qcc_e1)).y < get_qcc_mins(PROG_TO_EDICT(qcc_e2)).y)
        return qcc_FALSE;
    if (get_qcc_maxs(PROG_TO_EDICT(qcc_e1)).z < get_qcc_mins(PROG_TO_EDICT(qcc_e2)).z)
        return qcc_FALSE;
    return qcc_TRUE;
/*
=============
LinkDoors


=============
*/}
void qcc_LinkDoors(void)
{
    int qcc_t,     qcc_starte;
    vector qcc_cmins,     qcc_cmaxs;
    if (get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))
// already linked by another door
        return;
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) 4)))
    {
        set_qcc_owner(PROG_TO_EDICT(progs.qcc_self), set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_self));
// don't want to link this door
        return;
    }
    qcc_cmins = get_qcc_mins(PROG_TO_EDICT(progs.qcc_self));
    qcc_cmaxs = get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self));
    qcc_starte = progs.qcc_self;
    qcc_t = progs.qcc_self;
    do
    {
        set_qcc_owner(PROG_TO_EDICT(progs.qcc_self), qcc_starte)// master door
;
        if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
            set_qcc_health(PROG_TO_EDICT(qcc_starte), get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        if (get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))
            set_qcc_targetname(PROG_TO_EDICT(qcc_starte), get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)));
        if ((!areStringsEqual(get_qcc_message(PROG_TO_EDICT(progs.qcc_self)), NULL_string_index)))
            set_qcc_message(PROG_TO_EDICT(qcc_starte), get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
        qcc_t = qcc_find(qcc_t, offsetof (big_entvars_t, qcc_classname), get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)));
        if ((!qcc_t))
        {
            set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_starte)// make the chain a loop
// shootable, fired, or key doors just needed the owner/enemy links,
// they don't spawn a field
;
            progs.qcc_self = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
            if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
                return;
            if (get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))
                return;
            if (get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))
                return;
            set_qcc_trigger_field(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), qcc_spawn_field(qcc_cmins, qcc_cmaxs));
            return;
        }
        if (qcc_EntitiesTouching(progs.qcc_self, qcc_t))
        {
            if (get_qcc_enemy(PROG_TO_EDICT(qcc_t)))
                qcc_objerror(cross_connected_doors_string_index);
            set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_t);
            progs.qcc_self = qcc_t;
            if (get_qcc_mins(PROG_TO_EDICT(qcc_t)).x < qcc_cmins.x)
                qcc_cmins.x = get_qcc_mins(PROG_TO_EDICT(qcc_t)).x;
            if (get_qcc_mins(PROG_TO_EDICT(qcc_t)).y < qcc_cmins.y)
                qcc_cmins.y = get_qcc_mins(PROG_TO_EDICT(qcc_t)).y;
            if (get_qcc_mins(PROG_TO_EDICT(qcc_t)).z < qcc_cmins.z)
                qcc_cmins.z = get_qcc_mins(PROG_TO_EDICT(qcc_t)).z;
            if (get_qcc_maxs(PROG_TO_EDICT(qcc_t)).x > qcc_cmaxs.x)
                qcc_cmaxs.x = get_qcc_maxs(PROG_TO_EDICT(qcc_t)).x;
            if (get_qcc_maxs(PROG_TO_EDICT(qcc_t)).y > qcc_cmaxs.y)
                qcc_cmaxs.y = get_qcc_maxs(PROG_TO_EDICT(qcc_t)).y;
            if (get_qcc_maxs(PROG_TO_EDICT(qcc_t)).z > qcc_cmaxs.z)
                qcc_cmaxs.z = get_qcc_maxs(PROG_TO_EDICT(qcc_t)).z;
        }
    }
    while(1.00000f);
/*QUAKED func_door (0 .5 .8) ? START_OPEN x DOOR_DONT_LINK GOLD_KEY SILVER_KEY TOGGLE
if two doors touch, they are assumed to be connected and operate as a unit.

TOGGLE causes the door to wait in both the start and end states for a trigger event.

START_OPEN causes the door to move to its destination when spawned, and operate in reverse.  It is used to temporarily or permanently close off an area when triggered (not usefull for touch or takedamage doors).

Key doors are allways wait -1.

"message"	is printed when the door is touched if it is a trigger door and it hasn't been fired yet
"angle"		determines the opening direction
"targetname" if set, no touch field will be spawned and a remote button or trigger field activates the door.
"health"	if set, door must be shot open
"speed"		movement speed (100 default)
"wait"		wait before returning (3 default, -1 = never return)
"lip"		lip remaining at end of move (8 default)
"dmg"		damage to inflict when blocked (2 default)
"sounds"
0)	no sound
1)	stone
2)	base
3)	stone chain
4)	screechy metal
*/}
void qcc_func_door(void)
{
    if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 0)
    {
        qcc_precache_sound(doors_medtry_wav_string_index);
        qcc_precache_sound(doors_meduse_wav_string_index);
        set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_medtry_wav_string_index);
        set_qcc_noise4(PROG_TO_EDICT(progs.qcc_self), doors_meduse_wav_string_index);
    }
    else
        if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 1)
        {
            qcc_precache_sound(doors_runetry_wav_string_index);
            qcc_precache_sound(doors_runeuse_wav_string_index);
            set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_runetry_wav_string_index);
            set_qcc_noise4(PROG_TO_EDICT(progs.qcc_self), doors_runeuse_wav_string_index);
        }
        else
            if (get_qcc_worldtype(PROG_TO_EDICT(progs.qcc_world)) == 2)
            {
                qcc_precache_sound(doors_basetry_wav_string_index);
                qcc_precache_sound(doors_baseuse_wav_string_index);
                set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_basetry_wav_string_index);
                set_qcc_noise4(PROG_TO_EDICT(progs.qcc_self), doors_baseuse_wav_string_index);
            }
            else
            {
                qcc_dprint(no_worldtype_set__n__string_index);
            }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 0)
    {
        qcc_precache_sound(misc_null_wav_string_index);
        qcc_precache_sound(misc_null_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(doors_drclos4_wav_string_index);
        qcc_precache_sound(doors_doormv1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_drclos4_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_doormv1_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        qcc_precache_sound(doors_hydro1_wav_string_index);
        qcc_precache_sound(doors_hydro2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_hydro1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_hydro2_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 3)
    {
        qcc_precache_sound(doors_stndr1_wav_string_index);
        qcc_precache_sound(doors_stndr2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_stndr1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_stndr2_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 4)
    {
        qcc_precache_sound(doors_ddoor1_wav_string_index);
        qcc_precache_sound(doors_ddoor2_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_ddoor2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_ddoor1_wav_string_index);
    }
    qcc_SetMovedir();
    set_qcc_max_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_door);
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_door_blocked));
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_door_use));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_DOOR_SILVER_KEY)))
        set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_KEY1);
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_DOOR_GOLD_KEY)))
        set_qcc_items(PROG_TO_EDICT(progs.qcc_self), qcc_IT_KEY2);
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 100);
    if (!get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 3);
    if (!get_qcc_lip(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_lip(PROG_TO_EDICT(progs.qcc_self), 8);
    if (!get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 2);
    set_qcc_pos1(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_pos2(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), ( qcc_fabs(dotProduct(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), get_qcc_size(PROG_TO_EDICT(progs.qcc_self)))) - get_qcc_lip(PROG_TO_EDICT(progs.qcc_self)) ))))// DOOR_START_OPEN is to allow an entity to be lighted in the closed position
// but spawn in the open position
;
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_DOOR_START_OPEN)))
    {
        qcc_setorigin(progs.qcc_self, get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_pos2(PROG_TO_EDICT(progs.qcc_self), get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_pos1(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    }
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_door_killed));
    }
    if (get_qcc_items(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), -1);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_door_touch))// LinkDoors can't be done until all of the doors have been spawned, so
// the sizes can be detected properly.
;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_LinkDoors));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
/*
=============================================================================

SECRET DOORS

=============================================================================
*/}
void qcc_fd_secret_move1(void);
void qcc_fd_secret_move2(void);
void qcc_fd_secret_move3(void);
void qcc_fd_secret_move4(void);
void qcc_fd_secret_move5(void);
void qcc_fd_secret_move6(void);
void qcc_fd_secret_done(void);
const float qcc_SECRET_OPEN_ONCE = 1// stays open
;
const float qcc_SECRET_1ST_LEFT = 2// 1st move is left of arrow
;
const float qcc_SECRET_1ST_DOWN = 4// 1st move is down from arrow
;
const float qcc_SECRET_NO_SHOOT = 8// only opened by trigger
;
const float qcc_SECRET_YES_SHOOT = 16// shootable even if targeted
;
void qcc_fd_secret_use(void)
{
    float qcc_temp;
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 10000)// exit if still moving around...
;
    if ((!areVectorEqual(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_oldorigin(PROG_TO_EDICT(progs.qcc_self)))))
        return;
    set_qcc_message(PROG_TO_EDICT(progs.qcc_self), progs.qcc_string_null)// no more message
;
    qcc_SUB_UseTargets()// fire all targets / killtargets
;
    if (!( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_NO_SHOOT)) ))
    {
        set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    }
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}})// Make a sound, wait a little...
;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
    qcc_temp = 1 - ( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_1ST_LEFT)) )// 1 or -1
;
    qcc_makevectors(get_qcc_mangle(PROG_TO_EDICT(progs.qcc_self)));
    if (!get_qcc_t_width(PROG_TO_EDICT(progs.qcc_self)))
    {
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_1ST_DOWN)))
            set_qcc_t_width(PROG_TO_EDICT(progs.qcc_self), qcc_fabs(dotProduct(progs.qcc_v_up, get_qcc_size(PROG_TO_EDICT(progs.qcc_self)))));
        else
            set_qcc_t_width(PROG_TO_EDICT(progs.qcc_self), qcc_fabs(dotProduct(progs.qcc_v_right, get_qcc_size(PROG_TO_EDICT(progs.qcc_self)))));
    }
    if (!get_qcc_t_length(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_t_length(PROG_TO_EDICT(progs.qcc_self), qcc_fabs(dotProduct(progs.qcc_v_forward, get_qcc_size(PROG_TO_EDICT(progs.qcc_self)))));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_1ST_DOWN)))
        set_qcc_dest1(PROG_TO_EDICT(progs.qcc_self), vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_up, get_qcc_t_width(PROG_TO_EDICT(progs.qcc_self)))));
    else
        set_qcc_dest1(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_right, ( get_qcc_t_width(PROG_TO_EDICT(progs.qcc_self)) * qcc_temp ))));
    set_qcc_dest2(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_dest1(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, get_qcc_t_length(PROG_TO_EDICT(progs.qcc_self)))));
    qcc_SUB_CalcMove(get_qcc_dest1(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_fd_secret_move1));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
// Wait after first movement...
}
void qcc_fd_secret_move1(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 1);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_move2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
// Start moving sideways w/sound...
}
void qcc_fd_secret_move2(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_SUB_CalcMove(get_qcc_dest2(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_fd_secret_move3));
// Wait here until time to go back...
}
void qcc_fd_secret_move3(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    if (!( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_OPEN_ONCE)) ))
    {
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_move4));
    }
// Move backward...
}
void qcc_fd_secret_move4(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_SUB_CalcMove(get_qcc_dest1(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_fd_secret_move5));
// Wait 1 second...
}
void qcc_fd_secret_move5(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 1);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_move6));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
}
void qcc_fd_secret_move6(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise2(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_SUB_CalcMove(get_qcc_oldorigin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_fd_secret_done));
}
void qcc_fd_secret_done(void)
{
    if (((int) isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))) || ((int) (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_YES_SHOOT))))
    {
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 10000);
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_use));
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise3(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
}
void qcc_secret_blocked(void)
{
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
    qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)));
/*
================
secret_touch

Prints messages
================
*/}
void qcc_secret_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
    if (get_qcc_message(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_centerprint(progs.qcc_other, get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sound(progs.qcc_other, qcc_CHAN_BODY, misc_talk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    }
/*QUAKED func_door_secret (0 .5 .8) ? open_once 1st_left 1st_down no_shoot always_shoot
Basic secret door. Slides back, then to the side. Angle determines direction.
wait  = # of seconds before coming back
1st_left = 1st move is left of arrow
1st_down = 1st move is down from arrow
always_shoot = even if targeted, keep shootable
t_width = override WIDTH to move back (or height if going down)
t_length = override LENGTH to move sideways
"dmg"		damage to inflict when blocked (2 default)

If a secret door has a targetname, it will only be opened by it's botton or trigger, not by damage.
"sounds"
1) medieval
2) metal
3) base
*/}
void qcc_func_door_secret(void)
{
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 0)
        set_qcc_sounds(PROG_TO_EDICT(progs.qcc_self), 3);
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(doors_latch2_wav_string_index);
        qcc_precache_sound(doors_winch2_wav_string_index);
        qcc_precache_sound(doors_drclos4_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_latch2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_winch2_wav_string_index);
        set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_drclos4_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        qcc_precache_sound(doors_airdoor1_wav_string_index);
        qcc_precache_sound(doors_airdoor2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_airdoor1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_airdoor2_wav_string_index);
        set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_airdoor2_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 3)
    {
        qcc_precache_sound(doors_basesec1_wav_string_index);
        qcc_precache_sound(doors_basesec2_wav_string_index);
        set_qcc_noise2(PROG_TO_EDICT(progs.qcc_self), doors_basesec1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), doors_basesec2_wav_string_index);
        set_qcc_noise3(PROG_TO_EDICT(progs.qcc_self), doors_basesec2_wav_string_index);
    }
    if (!get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 2)// Magic formula...
;
    set_qcc_mangle(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_door);
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_secret_touch));
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_secret_blocked));
    set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 50);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_use));
    if (((int) isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))) || ((int) (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SECRET_YES_SHOOT))))
    {
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 10000);
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fd_secret_use));
    }
    set_qcc_oldorigin(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (!get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 5)// 5 seconds before closing
;
//File: buttons.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/// button and multiple button
}
void qcc_button_wait(void);
void qcc_button_return(void);
void qcc_button_wait(void)
{
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_TOP);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_button_return));
    progs.qcc_activator = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    qcc_SUB_UseTargets();
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1)// use alternate textures
;
}
void qcc_button_done(void)
{
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
}
void qcc_button_return(void)
{
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_DOWN);
    qcc_SUB_CalcMove(get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_button_done));
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0)// use normal textures
;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES)// can be shot again
;
}
void qcc_button_blocked(void)
{
// do nothing, just don't ome all the way back out
}
void qcc_button_fire(void)
{
    if (((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_UP) || ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_TOP))
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_UP);
    qcc_SUB_CalcMove(get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_button_wait));
}
void qcc_button_use(void)
{
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    qcc_button_fire();
}
void qcc_button_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_other);
    qcc_button_fire();
}
void qcc_button_killed(void)
{
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_damage_attacker);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO)// wil be reset upon return
;
    qcc_button_fire();
/*QUAKED func_button (0 .5 .8) ?
When a button is touched, it moves some distance in the direction of it's angle, triggers all of it's targets, waits some time, then returns to it's original position where it can be triggered again.

"angle"		determines the opening direction
"target"	all entities with a matching targetname will be used
"speed"		override the default 40 speed
"wait"		override the default 1 second wait (-1 = never return)
"lip"		override the default 4 pixel lip remaining at end of move
"health"	if set, the button must be killed instead of touched
"sounds"
0) steam metal
1) wooden clunk
2) metallic click
3) in-out
*/}
void qcc_func_button(void)
{
    float qcc_gtemp,     qcc_ftemp;
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 0)
    {
        qcc_precache_sound(buttons_airbut1_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), buttons_airbut1_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(buttons_switch21_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), buttons_switch21_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        qcc_precache_sound(buttons_switch02_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), buttons_switch02_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 3)
    {
        qcc_precache_sound(buttons_switch04_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), buttons_switch04_wav_string_index);
    }
    qcc_SetMovedir();
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_button_blocked));
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_button_use));
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_max_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_button_killed));
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
    }
    else
        set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_button_touch));
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 40);
    if (!get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 1);
    if (!get_qcc_lip(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_lip(PROG_TO_EDICT(progs.qcc_self), 4);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
    set_qcc_pos1(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_pos2(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), ( qcc_fabs(dotProduct(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), get_qcc_size(PROG_TO_EDICT(progs.qcc_self)))) - get_qcc_lip(PROG_TO_EDICT(progs.qcc_self)) ))));
//File: triggers.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
;
void qcc_trigger_reactivate(void)
{
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER);
//=============================================================================
}
const float qcc_SPAWNFLAG_NOMESSAGE = 1;
const float qcc_SPAWNFLAG_NOTOUCH = 1// the wait time has passed, so set back up for another activation
;
void qcc_multi_wait(void)
{
    if (get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_max_health(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BBOX);
    }
// the trigger was just touched/killed/used
// self.enemy should be set to the activator so it can be held through a delay
// so wait for the delay time before firing
}
void qcc_multi_trigger(void)
{
    if (get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
    {
// allready been triggered
        return;
    }
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_trigger_secret))
    {
        if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player)))
            return;
        progs.qcc_found_secrets = progs.qcc_found_secrets + 1;
        qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FOUNDSECRET);
    }
    if (get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)))
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM)// don't trigger again until reset
;
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    progs.qcc_activator = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    qcc_SUB_UseTargets();
    if (get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)) > 0)
    {
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_multi_wait));
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
    }
    else
// we can't just remove (self) here, because this is a touch function
// called wheil C code is looping through area links...
    {
        set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Remove));
    }
}
void qcc_multi_killed(void)
{
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_damage_attacker);
    qcc_multi_trigger();
}
void qcc_multi_use(void)
{
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    qcc_multi_trigger();
}
void qcc_multi_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
// if the trigger has an angles field, check player's facing direction
        return;
    if ((!areVectorEqual(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}})))
    {
        qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_other)));
        if (dotProduct(progs.qcc_v_forward, get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self))) < 0)
// not facing the right way
            return;
    }
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_other);
    qcc_multi_trigger();
/*QUAKED trigger_multiple (.5 .5 .5) ? notouch
Variable sized repeatable trigger.  Must be targeted at one or more entities.  If "health" is set, the trigger must be killed to activate each time.
If "delay" is set, the trigger waits some time after activating before firing.
"wait" : Seconds between triggerings. (.2 default)
If notouch is set, the trigger is only fired by other entities, not by touching.
NOTOUCH has been obsoleted by trigger_relay!
sounds
1)	secret
2)	beep beep
3)	large switch
4)
set "message" to text string
*/}
void qcc_trigger_multiple(void)
{
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(misc_secret_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_secret_wav_string_index);
    }
    else
        if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
        {
            qcc_precache_sound(misc_talk_wav_string_index);
            set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_talk_wav_string_index);
        }
        else
            if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 3)
            {
                qcc_precache_sound(misc_trigger1_wav_string_index);
                set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_trigger1_wav_string_index);
            }
    if (!get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 0.2f);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_multi_use));
    qcc_InitTrigger();
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)))
    {
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_NOTOUCH)))
            qcc_objerror(health_and_notouch_don_t_make_se_64937E7E_long_string_index);
        set_qcc_max_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_multi_killed));
        set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BBOX);
        qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))// make sure it links into the world
;
    }
    else
    {
        if (!( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_NOTOUCH)) ))
        {
            set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_multi_touch));
        }
    }
/*QUAKED trigger_once (.5 .5 .5) ? notouch
Variable sized trigger. Triggers once, then removes itself.  You must set the key "target" to the name of another object in the level that has a matching
"targetname".  If "health" is set, the trigger must be killed to activate.
If notouch is set, the trigger is only fired by other entities, not by touching.
if "killtarget" is set, any objects that have a matching "target" will be removed when the trigger is fired.
if "angle" is set, the trigger will only fire when someone is facing the direction of the angle.  Use "360" for an angle of 0.
sounds
1)	secret
2)	beep beep
3)	large switch
4)
set "message" to text string
*/}
void qcc_trigger_once(void)
{
    set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), -1);
    qcc_trigger_multiple();
//=============================================================================
/*QUAKED trigger_relay (.5 .5 .5) (-8 -8 -8) (8 8 8)
This fixed size trigger cannot be touched, it can only be fired by other events.  It can contain killtargets, targets, delays, and messages.
*/}
void qcc_trigger_relay(void)
{
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_UseTargets));
//=============================================================================
/*QUAKED trigger_secret (.5 .5 .5) ?
secret counter trigger
sounds
1)	secret
2)	beep beep
3)
4)
set "message" to text string
*/}
void qcc_trigger_secret(void)
{
    progs.qcc_total_secrets = progs.qcc_total_secrets + 1;
    set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), -1);
    if (isEmptyString(get_qcc_message(PROG_TO_EDICT(progs.qcc_self))))
        set_qcc_message(PROG_TO_EDICT(progs.qcc_self), You_found_a_secret_area__string_index);
    if (!get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_sounds(PROG_TO_EDICT(progs.qcc_self), 1);
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(misc_secret_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_secret_wav_string_index);
    }
    else
        if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
        {
            qcc_precache_sound(misc_talk_wav_string_index);
            set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_talk_wav_string_index);
        }
    qcc_trigger_multiple();
//=============================================================================
}
void qcc_counter_use(void)
{
    uint16_t qcc_junk;
    set_qcc_count(PROG_TO_EDICT(progs.qcc_self), get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) - 1);
    if (get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) < 0)
        return;
    if (get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) != 0)
    {
        if (((int) areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_activator)), qcc_classname_player)) && ((int) ( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_NOMESSAGE)) ) == 0))
        {
            if (get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) >= 4)
                qcc_centerprint(progs.qcc_activator, There_are_more_to_go____string_index);
            else
                if (get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) == 3)
                    qcc_centerprint(progs.qcc_activator, Only_3_more_to_go____string_index);
                else
                    if (get_qcc_count(PROG_TO_EDICT(progs.qcc_self)) == 2)
                        qcc_centerprint(progs.qcc_activator, Only_2_more_to_go____string_index);
                    else
                        qcc_centerprint(progs.qcc_activator, Only_1_more_to_go____string_index);
        }
        return;
    }
    if (((int) areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_activator)), qcc_classname_player)) && ((int) ( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_NOMESSAGE)) ) == 0))
        qcc_centerprint(progs.qcc_activator, Sequence_completed__string_index);
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    qcc_multi_trigger();
/*QUAKED trigger_counter (.5 .5 .5) ? nomessage
Acts as an intermediary for an action that takes multiple inputs.

If nomessage is not set, t will print "1 more.. " etc when triggered and "sequence complete" when finished.

After the counter has been triggered "count" times (default 2), it will fire all of it's targets and remove itself.
*/}
void qcc_trigger_counter(void)
{
    set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), -1);
    if (!get_qcc_count(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_count(PROG_TO_EDICT(progs.qcc_self), 2);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_counter_use));
/*
==============================================================================

TELEPORT TRIGGERS

==============================================================================
*/}
const float qcc_PLAYER_ONLY = 1;
const float qcc_SILENT = 2;
void qcc_play_teleport(void)
{
    float qcc_v;
    uint16_t qcc_tmpstr;
    qcc_v = qcc_random() * 5;
    if (qcc_v < 1)
        qcc_tmpstr = misc_r_tele1_wav_string_index;
    else
        if (qcc_v < 2)
            qcc_tmpstr = misc_r_tele2_wav_string_index;
        else
            if (qcc_v < 3)
                qcc_tmpstr = misc_r_tele3_wav_string_index;
            else
                if (qcc_v < 4)
                    qcc_tmpstr = misc_r_tele4_wav_string_index;
                else
                    qcc_tmpstr = misc_r_tele5_wav_string_index;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, qcc_tmpstr, 1.00000f, qcc_ATTN_NORM);
    qcc_remove(progs.qcc_self);
}
void qcc_spawn_tfog(vector qcc_org)
{
    progs.qcc_s = qcc_spawn(qcc_classname_nh_tfog);
    set_qcc_origin(PROG_TO_EDICT(progs.qcc_s), qcc_org);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_s), progs.qcc_time + 0.2f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_s), getFunctionIndex(qcc_play_teleport));
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_TELEPORT);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
}
void qcc_tdeath_touch(void)
{
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// frag anyone who teleports in on top of an invincible player
        return;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player))
    {
        if (get_qcc_invincible_finished(PROG_TO_EDICT(progs.qcc_other)) > progs.qcc_time)
            set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_teledeath2);
        if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))), qcc_classname_player)))
// other monsters explode themselves
        {
            qcc_T_Damage(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, 50000.0f);
            return;
        }
    }
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)))
    {
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, 50000.0f);
    }
}
void qcc_spawn_tdeath(vector qcc_org, int qcc_death_owner)
{
    int qcc_death;
    qcc_death = qcc_spawn(qcc_classname_teledeath);
    set_qcc_classname(PROG_TO_EDICT(qcc_death), qcc_classname_teledeath);
    set_qcc_movetype(PROG_TO_EDICT(qcc_death), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(qcc_death), qcc_SOLID_TRIGGER);
    set_qcc_angles(PROG_TO_EDICT(qcc_death), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setsize(qcc_death, vectorSub(get_qcc_mins(PROG_TO_EDICT(qcc_death_owner)), (vector)  {{1.00000f, 1.00000f, 1.00000f}}), vectorAdd(get_qcc_maxs(PROG_TO_EDICT(qcc_death_owner)), (vector)  {{1.00000f, 1.00000f, 1.00000f}}));
    qcc_setorigin(qcc_death, qcc_org);
    set_qcc_touch(PROG_TO_EDICT(qcc_death), getFunctionIndex(qcc_tdeath_touch));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_death), progs.qcc_time + 0.2f);
    set_qcc_think(PROG_TO_EDICT(qcc_death), getFunctionIndex(qcc_SUB_Remove));
    set_qcc_owner(PROG_TO_EDICT(qcc_death), qcc_death_owner);
    progs.qcc_force_retouch = 2// make sure even still objects get hit
;
}
void qcc_teleport_touch(void)
{
    int qcc_t;
    vector qcc_org;
    if (get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))
    {
        if (get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
        {
// not fired yet
            return;
        }
    }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_PLAYER_ONLY)))
    {
        if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
            return;
// only teleport living creatures
    }
    if (((int) get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0) || ((int) get_qcc_solid(PROG_TO_EDICT(progs.qcc_other)) != qcc_SOLID_SLIDEBOX))
        return;
    qcc_SUB_UseTargets()// put a tfog where the player was
;
    qcc_spawn_tfog(get_qcc_origin(PROG_TO_EDICT(progs.qcc_other)));
    qcc_t = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)));
    if ((!qcc_t))
        qcc_objerror(couldn_t_find_target_string_index)// spawn a tfog flash in front of the destination
;
    qcc_makevectors(get_qcc_mangle(PROG_TO_EDICT(qcc_t)));
    qcc_org = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_t)), floatMulVector(32, progs.qcc_v_forward));
    qcc_spawn_tfog(qcc_org);
    qcc_spawn_tdeath(get_qcc_origin(PROG_TO_EDICT(qcc_t)), progs.qcc_other)// move the player and lock him down for a little while
;
    if (!get_qcc_health(PROG_TO_EDICT(progs.qcc_other)))
    {
        set_qcc_origin(PROG_TO_EDICT(progs.qcc_other), get_qcc_origin(PROG_TO_EDICT(qcc_t)));
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_other), vectorAdd(( vectorMulFloat(progs.qcc_v_forward, get_qcc_velocity(PROG_TO_EDICT(progs.qcc_other)).x) ), ( vectorMulFloat(progs.qcc_v_forward, get_qcc_velocity(PROG_TO_EDICT(progs.qcc_other)).y) )));
        return;
    }
    qcc_setorigin(progs.qcc_other, get_qcc_origin(PROG_TO_EDICT(qcc_t)));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_other), get_qcc_mangle(PROG_TO_EDICT(qcc_t)));
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player))
    {
        set_qcc_fixangle(PROG_TO_EDICT(progs.qcc_other), 1)// turn this way immediately
;
        set_qcc_teleport_time(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 0.7f);
        if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_FL_ONGROUND)))
            set_qcc_flags(PROG_TO_EDICT(progs.qcc_other), get_qcc_flags(PROG_TO_EDICT(progs.qcc_other)) - qcc_FL_ONGROUND);
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_other), vectorMulFloat(progs.qcc_v_forward, 300));
    }
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_other), get_qcc_flags(PROG_TO_EDICT(progs.qcc_other)) - (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_FL_ONGROUND)));
/*QUAKED info_teleport_destination (.5 .5 .5) (-8 -8 -8) (8 8 32)
This is the destination marker for a teleporter.  It should have a "targetname" field with the same value as a teleporter's "target" field.
*/}
void qcc_info_teleport_destination(void)
{
// this does nothing, just serves as a target spot
    set_qcc_mangle(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_model(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
    set_qcc_origin(PROG_TO_EDICT(progs.qcc_self), vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 27.0000f}}));
    if (isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(no_targetname_string_index);
}
void qcc_teleport_use(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
    progs.qcc_force_retouch = 2// make sure even still objects get hit
;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
/*QUAKED trigger_teleport (.5 .5 .5) ? PLAYER_ONLY SILENT
Any object touching this will be transported to the corresponding info_teleport_destination entity. You must set the "target" field, and create an object with a "targetname" field that matches.

If the trigger_teleport has a targetname, it will only teleport entities when it has been fired.
*/}
void qcc_trigger_teleport(void)
{
    vector qcc_o;
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_teleport_touch))// find the destination 
;
    if (isEmptyString(get_qcc_target(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(no_target_string_index);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_teleport_use));
    if (!( (((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SILENT)) ))
    {
        qcc_precache_sound(ambience_hum1_wav_string_index);
        qcc_o = vectorMulFloat(( vectorAdd(get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self))) ), 0.5f);
        qcc_ambientsound(qcc_o, ambience_hum1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
    }
/*
==============================================================================

trigger_setskill

==============================================================================
*/}
void qcc_trigger_skill_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    qcc_cvar_set(skill_string_index, get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED trigger_setskill (.5 .5 .5) ?
sets skill level to the value of "message".
Only used on start map.
*/}
void qcc_trigger_setskill(void)
{
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_trigger_skill_touch));
/*
==============================================================================

ONLY REGISTERED TRIGGERS

==============================================================================
*/}
void qcc_trigger_onlyregistered_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
    if (qcc_cvar(registered_string_index))
    {
        set_qcc_message(PROG_TO_EDICT(progs.qcc_self), NULL_string_index);
        qcc_SUB_UseTargets();
        qcc_remove(progs.qcc_self);
    }
    else
    {
        if ((!areStringsEqual(get_qcc_message(PROG_TO_EDICT(progs.qcc_self)), NULL_string_index)))
        {
            qcc_centerprint(progs.qcc_other, get_qcc_message(PROG_TO_EDICT(progs.qcc_self)));
            qcc_sound(progs.qcc_other, qcc_CHAN_BODY, misc_talk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
    }
/*QUAKED trigger_onlyregistered (.5 .5 .5) ?
Only fires if playing the registered version, otherwise prints the message
*/}
void qcc_trigger_onlyregistered(void)
{
    qcc_precache_sound(misc_talk_wav_string_index);
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_trigger_onlyregistered_touch));
//============================================================================
}
void qcc_hurt_on(void)
{
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_TRIGGER);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), -1);
}
void qcc_hurt_touch(void)
{
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hurt_on));
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    }
    return;
/*QUAKED trigger_hurt (.5 .5 .5) ?
Any object touching this will be hurt
set dmg to damage amount
defalt dmg = 5
*/}
void qcc_trigger_hurt(void)
{
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hurt_touch));
    if (!get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 5);
//============================================================================
}
const float qcc_PUSH_ONCE = 1;
void qcc_trigger_push_touch(void)
{
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_grenade))
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_other), vectorMulFloat(floatMulVector(get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self))), 10));
    else
        if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) > 0)
        {
            set_qcc_velocity(PROG_TO_EDICT(progs.qcc_other), vectorMulFloat(floatMulVector(get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self))), 10));
            if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player))
            {
                if (get_qcc_fly_sound(PROG_TO_EDICT(progs.qcc_other)) < progs.qcc_time)
                {
                    set_qcc_fly_sound(PROG_TO_EDICT(progs.qcc_other), progs.qcc_time + 1.5f);
                    qcc_sound(progs.qcc_other, qcc_CHAN_AUTO, ambience_windfly_wav_string_index, 1.00000f, qcc_ATTN_NORM);
                }
            }
        }
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_PUSH_ONCE)))
        qcc_remove(progs.qcc_self);
/*QUAKED trigger_push (.5 .5 .5) ? PUSH_ONCE
Pushes the player
*/}
void qcc_trigger_push(void)
{
    qcc_InitTrigger();
    qcc_precache_sound(ambience_windfly_wav_string_index);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_trigger_push_touch));
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 1000);
//============================================================================
}
void qcc_trigger_monsterjump_touch(void)
{
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_other))) & ((int) ( (((int) (((int) qcc_FL_MONSTER) | ((int) qcc_FL_FLY))) | ((int) qcc_FL_SWIM)) ))) != qcc_FL_MONSTER)
// set XY even if not on ground, so the jump will clear lips
        return;
    set_qcc_velocity_x(PROG_TO_EDICT(progs.qcc_other), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)).x * get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity_y(PROG_TO_EDICT(progs.qcc_other), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)).y * get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)));
    if (!( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_other))) & ((int) qcc_FL_ONGROUND)) ))
        return;
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_other), get_qcc_flags(PROG_TO_EDICT(progs.qcc_other)) - qcc_FL_ONGROUND);
    set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_other), get_qcc_height(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED trigger_monsterjump (.5 .5 .5) ?
Walking monsters that touch this will jump in the direction of the trigger's angle
"speed" default to 200, the speed thrown forward
"height" default to 200, the speed thrown upwards
*/}
void qcc_trigger_monsterjump(void)
{
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 200);
    if (!get_qcc_height(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_height(PROG_TO_EDICT(progs.qcc_self), 200);
    if (areVectorEqual(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}}))
        set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 360.000f, 0.000000f}});
    qcc_InitTrigger();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_trigger_monsterjump_touch));
//File: plats.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
void qcc_plat_center_touch(void);
void qcc_plat_outside_touch(void);
void qcc_plat_trigger_use(void);
void qcc_plat_go_up(void);
void qcc_plat_go_down(void);
void qcc_plat_crush(void);
const float qcc_PLAT_LOW_TRIGGER = 1;
void qcc_plat_spawn_inside_trigger(void)
{
    int qcc_trigger;
    vector qcc_tmin,     qcc_tmax//
// middle trigger
//	
;
    qcc_trigger = qcc_spawn(qcc_classname_nh_trigger);
    set_qcc_touch(PROG_TO_EDICT(qcc_trigger), getFunctionIndex(qcc_plat_center_touch));
    set_qcc_movetype(PROG_TO_EDICT(qcc_trigger), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(qcc_trigger), qcc_SOLID_TRIGGER);
    set_qcc_enemy(PROG_TO_EDICT(qcc_trigger), progs.qcc_self);
    qcc_tmin = vectorAdd(get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{25.0000f, 25.0000f, 0.000000f}});
    qcc_tmax = vectorSub(get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{25.0000f, 25.0000f, -8.00000f}});
    qcc_tmin.z = qcc_tmax.z - ( get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)).z - get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)).z + 8 );
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_PLAT_LOW_TRIGGER)))
        qcc_tmax.z = qcc_tmin.z + 8;
    if (get_qcc_size(PROG_TO_EDICT(progs.qcc_self)).x <= 50)
    {
        qcc_tmin.x = ( get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)).x + get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)).x ) / 2;
        qcc_tmax.x = qcc_tmin.x + 1;
    }
    if (get_qcc_size(PROG_TO_EDICT(progs.qcc_self)).y <= 50)
    {
        qcc_tmin.y = ( get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)).y + get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)).y ) / 2;
        qcc_tmax.y = qcc_tmin.y + 1;
    }
    qcc_setsize(qcc_trigger, qcc_tmin, qcc_tmax);
}
void qcc_plat_hit_top(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_TOP);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_plat_go_down));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 3);
}
void qcc_plat_hit_bottom(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
}
void qcc_plat_go_down(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_DOWN);
    qcc_SUB_CalcMove(get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_plat_hit_bottom));
}
void qcc_plat_go_up(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_UP);
    qcc_SUB_CalcMove(get_qcc_pos1(PROG_TO_EDICT(progs.qcc_self)), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_plat_hit_top));
}
void qcc_plat_center_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
        return;
    progs.qcc_self = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_BOTTOM)
        qcc_plat_go_up();
    else
        if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_TOP)
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 1)// delay going down
;
}
void qcc_plat_outside_touch(void)
{
    if ((!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_player)))
        return;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)) <= 0)
//dprint ("plat_outside_touch\n");
        return;
    progs.qcc_self = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_TOP)
        qcc_plat_go_down();
}
void qcc_plat_trigger_use(void)
{
    if (get_qcc_think(PROG_TO_EDICT(progs.qcc_self)))
// allready activated
        return;
    qcc_plat_go_down();
}
void qcc_plat_crush(void)
{
//dprint ("plat_crush\n");
    qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, 1.00000f);
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_UP)
        qcc_plat_go_down();
    else
        if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) == qcc_STATE_DOWN)
            qcc_plat_go_up();
        else
            qcc_objerror(plat_crush__bad_self_state_n__string_index);
}
void qcc_plat_use(void)
{
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    if (get_qcc_state(PROG_TO_EDICT(progs.qcc_self)) != qcc_STATE_UP)
        qcc_objerror(plat_use__not_in_up_state_string_index);
    qcc_plat_go_down();
/*QUAKED func_plat (0 .5 .8) ? PLAT_LOW_TRIGGER
speed	default 150

Plats are always drawn in the extended position, so they will light correctly.

If the plat is the target of another trigger or button, it will start out disabled in the extended position until it is trigger, when it will lower and become a normal plat.

If the "height" key is set, that will determine the amount the plat moves, instead of being implicitly determined by the model's height.
Set "sounds" to one of the following:
1) base fast
2) chain slow
*/}
void qcc_func_plat(void)
{
    int qcc_t;
    if (!get_qcc_t_length(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_t_length(PROG_TO_EDICT(progs.qcc_self), 80);
    if (!get_qcc_t_width(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_t_width(PROG_TO_EDICT(progs.qcc_self), 10);
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 0)
        set_qcc_sounds(PROG_TO_EDICT(progs.qcc_self), 2)// FIX THIS TO LOAD A GENERIC PLAT SOUND
;
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        qcc_precache_sound(plats_plat1_wav_string_index);
        qcc_precache_sound(plats_plat2_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), plats_plat1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), plats_plat2_wav_string_index);
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 2)
    {
        qcc_precache_sound(plats_medplat1_wav_string_index);
        qcc_precache_sound(plats_medplat2_wav_string_index);
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), plats_medplat1_wav_string_index);
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), plats_medplat2_wav_string_index);
    }
    set_qcc_mangle(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_plat);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setsize(progs.qcc_self, get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_plat_crush));
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 150)// pos1 is the top position, pos2 is the bottom
;
    set_qcc_pos1(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_pos2(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (get_qcc_height(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_pos2_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z - get_qcc_height(PROG_TO_EDICT(progs.qcc_self)));
    else
        set_qcc_pos2_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z - get_qcc_size(PROG_TO_EDICT(progs.qcc_self)).z + 8);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_plat_trigger_use));
    qcc_plat_spawn_inside_trigger()// the "start moving" trigger	
;
    if (get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_UP);
        set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_plat_use));
    }
    else
    {
        qcc_setorigin(progs.qcc_self, get_qcc_pos2(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_state(PROG_TO_EDICT(progs.qcc_self), qcc_STATE_BOTTOM);
    }
//============================================================================
}
void qcc_train_next(void);
void qcc_func_train_find(void);
void qcc_train_blocked(void)
{
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return;
    set_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
    qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)));
}
void qcc_train_use(void)
{
    if ((!areFunctionsEqual(get_qcc_think(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex(qcc_func_train_find))))
// already activated
        return;
    qcc_train_next();
}
void qcc_train_wait(void)
{
    if (get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)))
    {
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    }
    else
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_next));
}
void qcc_train_next(void)
{
    int qcc_targ;
    qcc_targ = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_target(PROG_TO_EDICT(progs.qcc_self), get_qcc_target(PROG_TO_EDICT(qcc_targ)));
    if (isEmptyString(get_qcc_target(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(train_next__no_next_target_string_index);
    if (get_qcc_wait(PROG_TO_EDICT(qcc_targ)))
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), get_qcc_wait(PROG_TO_EDICT(qcc_targ)));
    else
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 0);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, get_qcc_noise1(PROG_TO_EDICT(progs.qcc_self)), 1.00000f, qcc_ATTN_NORM);
    qcc_SUB_CalcMove(vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_mins(PROG_TO_EDICT(progs.qcc_self))), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex (qcc_train_wait));
}
void qcc_func_train_find(void)
{
    int qcc_targ;
    qcc_targ = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_targetname), get_qcc_target(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_target(PROG_TO_EDICT(progs.qcc_self), get_qcc_target(PROG_TO_EDICT(qcc_targ)));
    qcc_setorigin(progs.qcc_self, vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_mins(PROG_TO_EDICT(progs.qcc_self))));
    if (isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self))))
// not triggered, so start immediately
    {
        set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_next));
    }
/*QUAKED func_train (0 .5 .8) ?
Trains are moving platforms that players can ride.
The targets origin specifies the min point of the train at each corner.
The train spawns at the first target it is pointing at.
If the train is the target of a button or trigger, it will not begin moving until activated.
speed	default 100
dmg		default	2
sounds
1) ratchet metal

*/}
void qcc_func_train(void)
{
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 100);
    if (isEmptyString(get_qcc_target(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(func_train_without_a_target_string_index);
    if (!get_qcc_dmg(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_dmg(PROG_TO_EDICT(progs.qcc_self), 2);
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 0)
    {
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
        qcc_precache_sound(( misc_null_wav_string_index ));
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
        qcc_precache_sound(( ( misc_null_wav_string_index ) ));
    }
    if (get_qcc_sounds(PROG_TO_EDICT(progs.qcc_self)) == 1)
    {
        set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), plats_train2_wav_string_index);
        qcc_precache_sound(( plats_train2_wav_string_index ));
        set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), plats_train1_wav_string_index);
        qcc_precache_sound(( plats_train1_wav_string_index ));
    }
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_blocked));
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_use));
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_train);
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setsize(progs.qcc_self, get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))// start trains on the second frame, to make sure their targets have had
// a chance to spawn
;
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_func_train_find));
/*QUAKED misc_teleporttrain (0 .5 .8) (-8 -8 -8) (8 8 8)
This is used for the final bos
*/}
void qcc_misc_teleporttrain(void)
{
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 100);
    if (isEmptyString(get_qcc_target(PROG_TO_EDICT(progs.qcc_self))))
        qcc_objerror(func_train_without_a_target_string_index);
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH);
    set_qcc_blocked(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_blocked));
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_train_use));
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{100.000f, 200.000f, 300.000f}});
    set_qcc_noise(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
    qcc_precache_sound(( ( ( misc_null_wav_string_index ) ) ));
    set_qcc_noise1(PROG_TO_EDICT(progs.qcc_self), misc_null_wav_string_index);
    qcc_precache_sound(( ( ( ( misc_null_wav_string_index ) ) ) ));
    qcc_precache_model2(progs_teleport_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_teleport_mdl_string_index);
    qcc_setsize(progs.qcc_self, get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_setorigin(progs.qcc_self, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))// start trains on the second frame, to make sure their targets have had
// a chance to spawn
;
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)) + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_func_train_find));
//File: misc.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*QUAKED info_null (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for spotlights, etc.
*/}
void qcc_info_null(void)
{
    qcc_remove(progs.qcc_self);
/*QUAKED info_notnull (0 0.5 0) (-4 -4 -4) (4 4 4)
Used as a positional target for lightning.
*/}
void qcc_info_notnull(void)
{
//============================================================================
}
const float qcc_START_OFF = 1;
void qcc_light_use(void)
{
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_START_OFF)))
    {
        qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), m_string_index);
        set_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self), get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self)) - qcc_START_OFF);
    }
    else
    {
        qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), a_string_index);
        set_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self), get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self)) + qcc_START_OFF);
    }
/*QUAKED light (0 1 0) (-8 -8 -8) (8 8 8) START_OFF
Non-displayed light.
Default light value is 300
Default style is 0
If targeted, it will toggle between on or off.
*/}
void qcc_light(void)
{
    if (isEmptyString(get_qcc_targetname(PROG_TO_EDICT(progs.qcc_self))))
// inert light
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    if (get_qcc_style(PROG_TO_EDICT(progs.qcc_self)) >= 32)
    {
        set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_light_use));
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_START_OFF)))
            qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), a_string_index);
        else
            qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), m_string_index);
    }
/*QUAKED light_fluoro (0 1 0) (-8 -8 -8) (8 8 8) START_OFF
Non-displayed light.
Default light value is 300
Default style is 0
If targeted, it will toggle between on or off.
Makes steady fluorescent humming sound
*/}
void qcc_light_fluoro(void)
{
    if (get_qcc_style(PROG_TO_EDICT(progs.qcc_self)) >= 32)
    {
        set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_light_use));
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_START_OFF)))
            qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), a_string_index);
        else
            qcc_lightstyle(get_qcc_style(PROG_TO_EDICT(progs.qcc_self)), m_string_index);
    }
    qcc_precache_sound(ambience_fl_hum1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_fl_hum1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED light_fluorospark (0 1 0) (-8 -8 -8) (8 8 8)
Non-displayed light.
Default light value is 300
Default style is 10
Makes sparking, broken fluorescent sound
*/}
void qcc_light_fluorospark(void)
{
    if (!get_qcc_style(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_style(PROG_TO_EDICT(progs.qcc_self), 10);
    qcc_precache_sound(ambience_buzz1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_buzz1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED light_globe (0 1 0) (-8 -8 -8) (8 8 8)
Sphere globe light.
Default light value is 300
Default style is 0
*/}
void qcc_light_globe(void)
{
    qcc_precache_model(progs_s_light_spr_string_index);
    qcc_setmodel(progs.qcc_self, progs_s_light_spr_string_index);
    qcc_makestatic(progs.qcc_self);
}
void qcc_FireAmbient(void)
{
    qcc_precache_sound(ambience_fire1_wav_string_index)// attenuate fast
;
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_fire1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED light_torch_small_walltorch (0 .5 0) (-10 -10 -20) (10 10 20)
Short wall torch
Default light value is 200
Default style is 0
*/}
void qcc_light_torch_small_walltorch(void)
{
    qcc_precache_model(progs_flame_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_flame_mdl_string_index);
    qcc_FireAmbient();
    qcc_makestatic(progs.qcc_self);
/*QUAKED light_flame_large_yellow (0 1 0) (-10 -10 -12) (12 12 18)
Large yellow flame ball
*/}
void qcc_light_flame_large_yellow(void)
{
    qcc_precache_model(progs_flame2_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_flame2_mdl_string_index);
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_FireAmbient();
    qcc_makestatic(progs.qcc_self);
/*QUAKED light_flame_small_yellow (0 1 0) (-8 -8 -8) (8 8 8) START_OFF
Small yellow flame ball
*/}
void qcc_light_flame_small_yellow(void)
{
    qcc_precache_model(progs_flame2_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_flame2_mdl_string_index);
    qcc_FireAmbient();
    qcc_makestatic(progs.qcc_self);
/*QUAKED light_flame_small_white (0 1 0) (-10 -10 -40) (10 10 40) START_OFF
Small white flame ball
*/}
void qcc_light_flame_small_white(void)
{
    qcc_precache_model(progs_flame2_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_flame2_mdl_string_index);
    qcc_FireAmbient();
    qcc_makestatic(progs.qcc_self);
//============================================================================
/*QUAKED misc_fireball (0 .5 .8) (-8 -8 -8) (8 8 8)
Lava Balls
*/}
void qcc_fire_fly(void);
void qcc_fire_touch(void);
void qcc_misc_fireball(void)
{
    qcc_precache_model(progs_lavaball_mdl_string_index);
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_fireball);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + ( qcc_random() * 5 ));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fire_fly));
    if (!get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)))
        set_qcc_speed(PROG_TO_EDICT(progs.qcc_self), 1000)// next-hack this was fixed, was ==
;
}
void qcc_fire_fly(void)
{
    int qcc_fireball;
    qcc_fireball = qcc_spawn(qcc_classname_fireball);
    set_qcc_solid(PROG_TO_EDICT(qcc_fireball), qcc_SOLID_TRIGGER);
    set_qcc_movetype(PROG_TO_EDICT(qcc_fireball), qcc_MOVETYPE_TOSS);
    set_qcc_velocity(PROG_TO_EDICT(qcc_fireball), (vector)  {{0.000000f, 0.000000f, 1000.00f}});
    set_qcc_velocity_x(PROG_TO_EDICT(qcc_fireball), ( qcc_random() * 100 ) - 50);
    set_qcc_velocity_y(PROG_TO_EDICT(qcc_fireball), ( qcc_random() * 100 ) - 50);
    set_qcc_velocity_z(PROG_TO_EDICT(qcc_fireball), get_qcc_speed(PROG_TO_EDICT(progs.qcc_self)) + ( qcc_random() * 200 ));
    set_qcc_classname(PROG_TO_EDICT(qcc_fireball), qcc_classname_fireball);
    qcc_setmodel(qcc_fireball, progs_lavaball_mdl_string_index);
    qcc_setsize(qcc_fireball, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_fireball, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_fireball), progs.qcc_time + 5);
    set_qcc_think(PROG_TO_EDICT(qcc_fireball), getFunctionIndex(qcc_SUB_Remove));
    set_qcc_touch(PROG_TO_EDICT(qcc_fireball), getFunctionIndex(qcc_fire_touch));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + ( qcc_random() * 5 ) + 3);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fire_fly));
}
void qcc_fire_touch(void)
{
    qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, 20.0000f);
    qcc_remove(progs.qcc_self);
//============================================================================
}
void qcc_barrel_explode(void)
{
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_self), qcc_classname_explo_box)// did say self.owner
;
    qcc_T_RadiusDamage(progs.qcc_self, progs.qcc_self, 160.000f, progs.qcc_world);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, weapons_r_exp3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_particle(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector) {{0.000000f, 0.000000f, 0.000000f}}, 75.0000f, 255.000f);
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 32);
    qcc_BecomeExplosion();
/*QUAKED misc_explobox (0 .5 .8) (0 0 0) (32 32 64)
TESTING THING
*/}
void qcc_misc_explobox(void)
{
    float qcc_oldz;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    qcc_precache_model(maps_b_explob_bsp_string_index);
    qcc_setmodel(progs.qcc_self, maps_b_explob_bsp_string_index);
    qcc_precache_sound(weapons_r_exp3_wav_string_index);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 20);
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_barrel_explode));
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 2);
    qcc_oldz = get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z;
    qcc_droptofloor();
    if (qcc_oldz - get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z > 250)
    {
        qcc_dprint(item_fell_out_of_level_at__string_index);
        qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_dprint(_n__string_index);
        qcc_remove(progs.qcc_self);
    }
/*QUAKED misc_explobox2 (0 .5 .8) (0 0 0) (32 32 64)
Smaller exploding box, REGISTERED ONLY
*/}
void qcc_misc_explobox2(void)
{
    float qcc_oldz;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    qcc_precache_model2(maps_b_exbox2_bsp_string_index);
    qcc_setmodel(progs.qcc_self, maps_b_exbox2_bsp_string_index);
    qcc_precache_sound(weapons_r_exp3_wav_string_index);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 20);
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_barrel_explode));
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_AIM);
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 2);
    qcc_oldz = get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z;
    qcc_droptofloor();
    if (qcc_oldz - get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z > 250)
    {
        qcc_dprint(item_fell_out_of_level_at__string_index);
        qcc_dprint(qcc_vtos(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_dprint(_n__string_index);
        qcc_remove(progs.qcc_self);
    }
//============================================================================
}
const float qcc_SPAWNFLAG_SUPERSPIKE = 1;
const float qcc_SPAWNFLAG_LASER = 2;
void qcc_LaunchLaser(vector , vector );
void qcc_spikeshooter_use(void)
{
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_LASER)))
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_enfire_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_LaunchLaser(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)));
    }
    else
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, weapons_spike2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_launch_spike(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), 500));
        if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_SUPERSPIKE)))
            set_qcc_touch(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_superspike_touch));
    }
}
void qcc_shooter_think(void)
{
    qcc_spikeshooter_use();
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self)), 500));
/*QUAKED trap_spikeshooter (0 .5 .8) (-8 -8 -8) (8 8 8) superspike laser
When triggered, fires a spike in the direction set in QuakeEd.
Laser is only for REGISTERED.
*/}
void qcc_trap_spikeshooter(void)
{
    qcc_SetMovedir();
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_spikeshooter_use));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWNFLAG_LASER)))
    {
        qcc_precache_model2(qcc_classname_progs_laser_mdl);
        qcc_precache_sound2(enforcer_enfire_wav_string_index);
        qcc_precache_sound2(enforcer_enfstop_wav_string_index);
    }
    else
        qcc_precache_sound(weapons_spike2_wav_string_index);
/*QUAKED trap_shooter (0 .5 .8) (-8 -8 -8) (8 8 8) superspike laser
Continuously fires spikes.
"wait" time between spike (1.0 default)
"nextthink" delay before firing first spike, so multiple shooters can be stagered.
*/}
void qcc_trap_shooter(void)
{
    qcc_trap_spikeshooter();
    if (get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)) == 0)
        set_qcc_wait(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_wait(PROG_TO_EDICT(progs.qcc_self)) + get_qcc_ltime(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shooter_think));
/*
===============================================================================


===============================================================================
*/}
void qcc_make_bubbles(void);
void qcc_bubble_remove(void);
/*QUAKED air_bubbles (0 .5 .8) (-8 -8 -8) (8 8 8)

testing air bubbles
*/void qcc_bubble_bob(void);
void qcc_air_bubbles(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_s_bubble_spr_string_index);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_make_bubbles));
}
void qcc_make_bubbles(void)
{
    int qcc_bubble;
    qcc_bubble = qcc_spawn(qcc_classname_bubble);
    qcc_setmodel(qcc_bubble, progs_s_bubble_spr_string_index);
    qcc_setorigin(qcc_bubble, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_movetype(PROG_TO_EDICT(qcc_bubble), qcc_MOVETYPE_NOCLIP);
    set_qcc_solid(PROG_TO_EDICT(qcc_bubble), qcc_SOLID_NOT);
    set_qcc_velocity(PROG_TO_EDICT(qcc_bubble), (vector)  {{0.000000f, 0.000000f, 15.0000f}});
    set_qcc_nextthink(PROG_TO_EDICT(qcc_bubble), progs.qcc_time + 0.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_bubble), getFunctionIndex(qcc_bubble_bob));
    set_qcc_touch(PROG_TO_EDICT(qcc_bubble), getFunctionIndex(qcc_bubble_remove));
    set_qcc_classname(PROG_TO_EDICT(qcc_bubble), qcc_classname_bubble);
    set_qcc_frame(PROG_TO_EDICT(qcc_bubble), 0);
    set_qcc_cnt(PROG_TO_EDICT(qcc_bubble), 0);
    qcc_setsize(qcc_bubble, (vector) {{-8.00000f, -8.00000f, -8.00000f}}, (vector) {{8.00000f, 8.00000f, 8.00000f}});
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + qcc_random() + 0.5f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_make_bubbles));
}
void qcc_bubble_split(void)
{
    int qcc_bubble;
    qcc_bubble = qcc_spawn(qcc_classname_bubble);
    qcc_setmodel(qcc_bubble, progs_s_bubble_spr_string_index);
    qcc_setorigin(qcc_bubble, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_movetype(PROG_TO_EDICT(qcc_bubble), qcc_MOVETYPE_NOCLIP);
    set_qcc_solid(PROG_TO_EDICT(qcc_bubble), qcc_SOLID_NOT);
    set_qcc_velocity(PROG_TO_EDICT(qcc_bubble), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_bubble), progs.qcc_time + 0.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_bubble), getFunctionIndex(qcc_bubble_bob));
    set_qcc_touch(PROG_TO_EDICT(qcc_bubble), getFunctionIndex(qcc_bubble_remove));
    set_qcc_classname(PROG_TO_EDICT(qcc_bubble), qcc_classname_bubble);
    set_qcc_frame(PROG_TO_EDICT(qcc_bubble), 1);
    set_qcc_cnt(PROG_TO_EDICT(qcc_bubble), 10);
    qcc_setsize(qcc_bubble, (vector) {{-8.00000f, -8.00000f, -8.00000f}}, (vector) {{8.00000f, 8.00000f, 8.00000f}});
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1);
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 10);
    if (get_qcc_waterlevel(PROG_TO_EDICT(progs.qcc_self)) != 3)
        qcc_remove(progs.qcc_self);
}
void qcc_bubble_remove(void)
{
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), get_qcc_classname(PROG_TO_EDICT(progs.qcc_self))))
//		dprint ("bump");
    {
        return;
    }
    qcc_remove(progs.qcc_self);
}
void qcc_bubble_bob(void)
{
    float qcc_rnd1,     qcc_rnd2,     qcc_rnd3;
    vector qcc_vtmp1,     qcc_modi;
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) == 4)
        qcc_bubble_split();
    if (get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) == 20)
        qcc_remove(progs.qcc_self);
    qcc_rnd1 = get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).x + ( -10 + ( qcc_random() * 20 ) );
    qcc_rnd2 = get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).y + ( -10 + ( qcc_random() * 20 ) );
    qcc_rnd3 = get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z + 10 + qcc_random() * 10;
    if (qcc_rnd1 > 10)
        qcc_rnd1 = 5;
    if (qcc_rnd1 < -10)
        qcc_rnd1 = -5;
    if (qcc_rnd2 > 10)
        qcc_rnd2 = 5;
    if (qcc_rnd2 < -10)
        qcc_rnd2 = -5;
    if (qcc_rnd3 < 10)
        qcc_rnd3 = 15;
    if (qcc_rnd3 > 30)
        qcc_rnd3 = 25;
    set_qcc_velocity_x(PROG_TO_EDICT(progs.qcc_self), qcc_rnd1);
    set_qcc_velocity_y(PROG_TO_EDICT(progs.qcc_self), qcc_rnd2);
    set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), qcc_rnd3);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_bubble_bob));
/*~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>
~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~<~>~*//*QUAKED viewthing (0 .5 .8) (-8 -8 -8) (8 8 8)

Just for the debugging level.  Don't use
*/}
void qcc_viewthing(void)
{
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_precache_model(progs_player_mdl_string_index);
    qcc_setmodel(progs.qcc_self, progs_player_mdl_string_index);
/*
==============================================================================

SIMPLE BMODELS

==============================================================================
*/}
void qcc_func_wall_use(void)
{
// change to alternate textures
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1 - get_qcc_frame(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED func_wall (0 .5 .8) ?
This is just a solid wall if not inhibitted
*/}
void qcc_func_wall(void)
{
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH)// so it doesn't get pushed by anything
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_func_wall_use));
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED func_illusionary (0 .5 .8) ?
A simple entity that looks solid but lets you walk through it.
*/}
void qcc_func_illusionary(void)
{
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
    qcc_makestatic(progs.qcc_self)// next-hack: had to provide id.
;
/*QUAKED func_episodegate (0 .5 .8) ? E1 E2 E3 E4
This bmodel will appear if the episode has allready been completed, so players can't reenter it.
*/}
void qcc_func_episodegate(void)
{
    if (!( (((int) progs.qcc_serverflags) & ((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self)))) ))
// can still enter episode
        return;
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH)// so it doesn't get pushed by anything
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_func_wall_use));
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
/*QUAKED func_bossgate (0 .5 .8) ?
This bmodel appears unless players have all of the episode sigils.
*/}
void qcc_func_bossgate(void)
{
    if (( (((int) progs.qcc_serverflags) & ((int) 15)) ) == 15)
// all episodes completed
        return;
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_PUSH)// so it doesn't get pushed by anything
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_BSP);
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_func_wall_use));
    qcc_setmodel(progs.qcc_self, get_qcc_model(PROG_TO_EDICT(progs.qcc_self)));
//============================================================================
/*QUAKED ambient_suck_wind (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_suck_wind(void)
{
    qcc_precache_sound(ambience_suck1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_suck1_wav_string_index, 1.00000f, qcc_ATTN_STATIC);
/*QUAKED ambient_drone (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_drone(void)
{
    qcc_precache_sound(ambience_drone6_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_drone6_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED ambient_flouro_buzz (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_flouro_buzz(void)
{
    qcc_precache_sound(ambience_buzz1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_buzz1_wav_string_index, 1.00000f, qcc_ATTN_STATIC);
/*QUAKED ambient_drip (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_drip(void)
{
    qcc_precache_sound(ambience_drip1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_drip1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED ambient_comp_hum (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_comp_hum(void)
{
    qcc_precache_sound(ambience_comp1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_comp1_wav_string_index, 1.00000f, qcc_ATTN_STATIC);
/*QUAKED ambient_thunder (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_thunder(void)
{
    qcc_precache_sound(ambience_thunder1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_thunder1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED ambient_light_buzz (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_light_buzz(void)
{
    qcc_precache_sound(ambience_fl_hum1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_fl_hum1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED ambient_swamp1 (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_swamp1(void)
{
    qcc_precache_sound(ambience_swamp1_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_swamp1_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
/*QUAKED ambient_swamp2 (0.3 0.1 0.6) (-10 -10 -8) (10 10 8)
*/}
void qcc_ambient_swamp2(void)
{
    qcc_precache_sound(ambience_swamp2_wav_string_index);
    qcc_ambientsound(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), ambience_swamp2_wav_string_index, 0.500000f, qcc_ATTN_STATIC);
//============================================================================
}
void qcc_noise_think(void)
{
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.5f);
    qcc_sound(progs.qcc_self, 1.00000f, enforcer_enfire_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 2.00000f, enforcer_enfstop_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 3.00000f, enforcer_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 4.00000f, enforcer_sight2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 5.00000f, enforcer_sight3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 6.00000f, enforcer_sight4_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sound(progs.qcc_self, 7.00000f, enforcer_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
/*QUAKED misc_noisemaker (1 0.5 0) (-10 -10 -10) (10 10 10)

For optimzation testing, starts a lot of sounds.
*/}
void qcc_misc_noisemaker(void)
{
    qcc_precache_sound2(enforcer_enfire_wav_string_index);
    qcc_precache_sound2(enforcer_enfstop_wav_string_index);
    qcc_precache_sound2(enforcer_sight1_wav_string_index);
    qcc_precache_sound2(enforcer_sight2_wav_string_index);
    qcc_precache_sound2(enforcer_sight3_wav_string_index);
    qcc_precache_sound2(enforcer_sight4_wav_string_index);
    qcc_precache_sound2(enforcer_pain1_wav_string_index);
    qcc_precache_sound2(enforcer_pain2_wav_string_index);
    qcc_precache_sound2(enforcer_death1_wav_string_index);
    qcc_precache_sound2(enforcer_idle1_wav_string_index);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random());
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_noise_think));
//File: ogre.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

OGRE

==============================================================================
*///=============================================================================
}
void qcc_OgreGrenadeExplode(void)
{
    qcc_T_RadiusDamage(progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 40.0000f, progs.qcc_world);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, weapons_r_exp3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_EXPLOSION);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    qcc_setmodel(progs.qcc_self, progs_s_explod_spr_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_s_explode1();
}
void qcc_OgreGrenadeTouch(void)
{
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)) == qcc_DAMAGE_AIM)
    {
        qcc_OgreGrenadeExplode();
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, weapons_bounce_wav_string_index, 1.00000f, qcc_ATTN_NORM)// bounce sound
;
    if (areVectorEqual(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 0.000000f}}))
        set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
/*
================
OgreFireGrenade
================
*/}
void qcc_OgreFireGrenade(void)
{
    int qcc_missile,     qcc_mpuff;
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_grenade_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_missile = qcc_spawn(qcc_classname_grenade);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_BOUNCE);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_BBOX)// set missile speed	
;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), qcc_normalize(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)))));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(qcc_missile)), 600));
    set_qcc_velocity_z(PROG_TO_EDICT(qcc_missile), 200);
    set_qcc_avelocity(PROG_TO_EDICT(qcc_missile), (vector)  {{300.000f, 300.000f, 300.000f}});
    set_qcc_angles(PROG_TO_EDICT(qcc_missile), qcc_vectoangles(get_qcc_velocity(PROG_TO_EDICT(qcc_missile))));
    set_qcc_touch(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_OgreGrenadeTouch))// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 2.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_OgreGrenadeExplode));
    qcc_setmodel(qcc_missile, progs_grenade_mdl_string_index);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
//=============================================================================
/*
================
chainsaw

FIXME
================
*/}
void qcc_chainsaw(float qcc_side)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        return;
    if (!qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        return;
    qcc_ai_charge(10.0000f);
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 100)
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 4;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
    if (qcc_side)
    {
        qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
        if (qcc_side == 1)
            qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_crandom() * 100, progs.qcc_v_right));
        else
            qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_side, progs.qcc_v_right));
    }
}
void qcc_ogre_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand2));
    qcc_ai_stand();
}
void qcc_ogre_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand3));
    qcc_ai_stand();
}
void qcc_ogre_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand4));
    qcc_ai_stand();
}
void qcc_ogre_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand5));
    qcc_ai_stand();
}
void qcc_ogre_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand6));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogidle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_stand();
}
void qcc_ogre_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand7));
    qcc_ai_stand();
}
void qcc_ogre_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand8));
    qcc_ai_stand();
}
void qcc_ogre_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand9));
    qcc_ai_stand();
}
void qcc_ogre_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand1));
    qcc_ai_stand();
}
void qcc_ogre_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk2));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk3));
    qcc_ai_walk(2.00000f);
}
void qcc_ogre_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk4));
    qcc_ai_walk(2.00000f);
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogidle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_ogre_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk5));
    qcc_ai_walk(2.00000f);
}
void qcc_ogre_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk6));
    qcc_ai_walk(2.00000f);
}
void qcc_ogre_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk7));
    qcc_ai_walk(5.00000f);
    if (qcc_random() < 0.1f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogdrag_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_ogre_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk8));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk9));
    qcc_ai_walk(2.00000f);
}
void qcc_ogre_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk10));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk11));
    qcc_ai_walk(1.00000f);
}
void qcc_ogre_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk12));
    qcc_ai_walk(2.00000f);
}
void qcc_ogre_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk13));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk14));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk15));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk16));
    qcc_ai_walk(3.00000f);
}
void qcc_ogre_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk1));
    qcc_ai_walk(4.00000f);
}
void qcc_ogre_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run2));
    qcc_ai_run(9.00000f);
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogidle2_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_ogre_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run3));
    qcc_ai_run(12.0000f);
}
void qcc_ogre_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run4));
    qcc_ai_run(8.00000f);
}
void qcc_ogre_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run5));
    qcc_ai_run(22.0000f);
}
void qcc_ogre_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run6));
    qcc_ai_run(16.0000f);
}
void qcc_ogre_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run7));
    qcc_ai_run(4.00000f);
}
void qcc_ogre_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run8));
    qcc_ai_run(13.0000f);
}
void qcc_ogre_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
    qcc_ai_run(24.0000f);
}
void qcc_ogre_swing1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing2));
    qcc_ai_charge(11.0000f);
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, ogre_ogsawatk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_ogre_swing2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing3));
    qcc_ai_charge(1.00000f);
}
void qcc_ogre_swing3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing4));
    qcc_ai_charge(4.00000f);
}
void qcc_ogre_swing4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing5));
    qcc_ai_charge(13.0000f);
}
void qcc_ogre_swing5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing6));
    qcc_ai_charge(9.00000f);
    qcc_chainsaw(0.000000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing7));
    qcc_chainsaw(200.000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing8));
    qcc_chainsaw(0.000000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing9));
    qcc_chainsaw(0.000000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing10));
    qcc_chainsaw(0.000000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing11));
    qcc_chainsaw(-200.000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing12));
    qcc_chainsaw(0.000000f);
    set_qcc_angles_y(PROG_TO_EDICT(progs.qcc_self), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)).y + qcc_random() * 25);
}
void qcc_ogre_swing12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing13));
    qcc_ai_charge(3.00000f);
}
void qcc_ogre_swing13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_swing14));
    qcc_ai_charge(8.00000f);
}
void qcc_ogre_swing14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
    qcc_ai_charge(9.00000f);
}
void qcc_ogre_smash1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash2));
    qcc_ai_charge(6.00000f);
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, ogre_ogsawatk_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_ogre_smash2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash3));
    qcc_ai_charge(0.000000f);
}
void qcc_ogre_smash3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash4));
    qcc_ai_charge(0.000000f);
}
void qcc_ogre_smash4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash5));
    qcc_ai_charge(1.00000f);
}
void qcc_ogre_smash5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash6));
    qcc_ai_charge(4.00000f);
}
void qcc_ogre_smash6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash7));
    qcc_ai_charge(4.00000f);
    qcc_chainsaw(0.000000f);
}
void qcc_ogre_smash7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash8));
    qcc_ai_charge(4.00000f);
    qcc_chainsaw(0.000000f);
}
void qcc_ogre_smash8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash9));
    qcc_ai_charge(10.0000f);
    qcc_chainsaw(0.000000f);
}
void qcc_ogre_smash9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash10));
    qcc_ai_charge(13.0000f);
    qcc_chainsaw(0.000000f);
}
void qcc_ogre_smash10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash11));
    qcc_chainsaw(1.00000f);
}
void qcc_ogre_smash11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash12));
    qcc_ai_charge(2.00000f);
    qcc_chainsaw(0.000000f);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + qcc_random() * 0.2f);
// slight variation
}
void qcc_ogre_smash12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash13));
    qcc_ai_charge(0.000000f);
// next-hack was ai_charge()
}
void qcc_ogre_smash13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_smash14));
    qcc_ai_charge(4.00000f);
}
void qcc_ogre_smash14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
    qcc_ai_charge(12.0000f);
}
void qcc_ogre_nail1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail2));
    qcc_ai_face();
}
void qcc_ogre_nail2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail3));
    qcc_ai_face();
}
void qcc_ogre_nail3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail4));
    qcc_ai_face();
}
void qcc_ogre_nail4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail5));
    qcc_ai_face();
    qcc_OgreFireGrenade();
}
void qcc_ogre_nail5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail6));
    qcc_ai_face();
}
void qcc_ogre_nail6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail7));
    qcc_ai_face();
}
void qcc_ogre_nail7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
    qcc_ai_face();
}
void qcc_ogre_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_pain2));
}
void qcc_ogre_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_pain3));
}
void qcc_ogre_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_pain4));
}
void qcc_ogre_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_pain5));
}
void qcc_ogre_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
}
void qcc_ogre_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painb2));
}
void qcc_ogre_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painb3));
}
void qcc_ogre_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
}
void qcc_ogre_painc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painc2));
}
void qcc_ogre_painc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painc3));
}
void qcc_ogre_painc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painc4));
}
void qcc_ogre_painc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painc5));
}
void qcc_ogre_painc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_painc6));
}
void qcc_ogre_painc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
}
void qcc_ogre_paind1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind2));
}
void qcc_ogre_paind2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind3));
    qcc_ai_pain(10.0000f);
}
void qcc_ogre_paind3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind4));
    qcc_ai_pain(9.00000f);
}
void qcc_ogre_paind4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind5));
    qcc_ai_pain(4.00000f);
}
void qcc_ogre_paind5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind6));
}
void qcc_ogre_paind6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind7));
}
void qcc_ogre_paind7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind8));
}
void qcc_ogre_paind8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind9));
}
void qcc_ogre_paind9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind10));
}
void qcc_ogre_paind10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind11));
}
void qcc_ogre_paind11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind12));
}
void qcc_ogre_paind12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind13));
}
void qcc_ogre_paind13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind14));
}
void qcc_ogre_paind14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind15));
}
void qcc_ogre_paind15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paind16));
}
void qcc_ogre_paind16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
}
void qcc_ogre_paine1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine2));
}
void qcc_ogre_paine2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine3));
    qcc_ai_pain(10.0000f);
}
void qcc_ogre_paine3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine4));
    qcc_ai_pain(9.00000f);
}
void qcc_ogre_paine4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine5));
    qcc_ai_pain(4.00000f);
}
void qcc_ogre_paine5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine6));
}
void qcc_ogre_paine6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine7));
}
void qcc_ogre_paine7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine8));
}
void qcc_ogre_paine8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine9));
}
void qcc_ogre_paine9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine10));
}
void qcc_ogre_paine10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 106); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine11));
}
void qcc_ogre_paine11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 107); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine12));
}
void qcc_ogre_paine12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 108); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine13));
}
void qcc_ogre_paine13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 109); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine14));
}
void qcc_ogre_paine14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 110); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_paine15));
}
void qcc_ogre_paine15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 111); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
}
void qcc_ogre_pain(int qcc_attacker, float qcc_damage)
{
    float qcc_r// don't make multiple pain sounds right after each other
;
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogpain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_r = qcc_random();
    if (qcc_r < 0.25f)
    {
        qcc_ogre_pain1();
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    }
    else
        if (qcc_r < 0.5f)
        {
            qcc_ogre_painb1();
            set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
        }
        else
            if (qcc_r < 0.75f)
            {
                qcc_ogre_painc1();
                set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            }
            else
                if (qcc_r < 0.88f)
                {
                    qcc_ogre_paind1();
                    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
                }
                else
                {
                    qcc_ogre_paine1();
                    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
                }
}
void qcc_ogre_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 112); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die2));
}
void qcc_ogre_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 113); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die3));
}
void qcc_ogre_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 114); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), 2);
    qcc_DropBackpack();
}
void qcc_ogre_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 115); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die5));
}
void qcc_ogre_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 116); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die6));
}
void qcc_ogre_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 117); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die7));
}
void qcc_ogre_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 118); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die8));
}
void qcc_ogre_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 119); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die9));
}
void qcc_ogre_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 120); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die10));
}
void qcc_ogre_die10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 121); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die11));
}
void qcc_ogre_die11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 122); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die12));
}
void qcc_ogre_die12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 123); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die13));
}
void qcc_ogre_die13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 124); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die14));
}
void qcc_ogre_die14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 125); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die14));
}
void qcc_ogre_bdie1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 126); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie2));
}
void qcc_ogre_bdie2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 127); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie3));
    qcc_ai_forward(5.00000f);
}
void qcc_ogre_bdie3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 128); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_rockets(PROG_TO_EDICT(progs.qcc_self), 2);
    qcc_DropBackpack();
}
void qcc_ogre_bdie4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 129); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie5));
    qcc_ai_forward(1.00000f);
}
void qcc_ogre_bdie5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 130); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie6));
    qcc_ai_forward(3.00000f);
}
void qcc_ogre_bdie6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 131); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie7));
    qcc_ai_forward(7.00000f);
}
void qcc_ogre_bdie7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 132); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie8));
    qcc_ai_forward(25.0000f);
}
void qcc_ogre_bdie8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 133); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie9));
}
void qcc_ogre_bdie9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 134); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie10));
}
void qcc_ogre_bdie10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 135); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_bdie10));
}
void qcc_ogre_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -80)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_ogre_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, ogre_ogdth_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() < 0.5f)
        qcc_ogre_die1();
    else
        qcc_ogre_bdie1();
}
void qcc_ogre_melee(void)
{
    if (qcc_random() > 0.5f)
        qcc_ogre_smash1();
    else
        qcc_ogre_swing1();
/*QUAKED monster_ogre (1 0 0) (-32 -32 -24) (32 32 64) Ambush

*/}
void qcc_monster_ogre(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_ogre_mdl_string_index);
    qcc_precache_model(progs_h_ogre_mdl_string_index);
    qcc_precache_model(progs_grenade_mdl_string_index);
    qcc_precache_sound(ogre_ogdrag_wav_string_index);
    qcc_precache_sound(ogre_ogdth_wav_string_index);
    qcc_precache_sound(ogre_ogidle_wav_string_index);
    qcc_precache_sound(ogre_ogidle2_wav_string_index);
    qcc_precache_sound(ogre_ogpain1_wav_string_index);
    qcc_precache_sound(ogre_ogsawatk_wav_string_index);
    qcc_precache_sound(ogre_ogwake_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_ogre_mdl_string_index);
    qcc_setsize(progs.qcc_self, qcc_VEC_HULL2_MIN, qcc_VEC_HULL2_MAX);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 200);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_run1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_die));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_melee));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_nail1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ogre_pain));
    qcc_walkmonster_start();
}
void qcc_monster_ogre_marksman(void)
{
    qcc_monster_ogre();
//File: demon.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

DEMON

==============================================================================
*///============================================================================
}
void qcc_Demon_JumpTouch(void);
void qcc_demon1_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand2));
    qcc_ai_stand();
}
void qcc_demon1_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand3));
    qcc_ai_stand();
}
void qcc_demon1_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand4));
    qcc_ai_stand();
}
void qcc_demon1_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand5));
    qcc_ai_stand();
}
void qcc_demon1_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand6));
    qcc_ai_stand();
}
void qcc_demon1_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand7));
    qcc_ai_stand();
}
void qcc_demon1_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand8));
    qcc_ai_stand();
}
void qcc_demon1_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand9));
    qcc_ai_stand();
}
void qcc_demon1_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand10));
    qcc_ai_stand();
}
void qcc_demon1_stand10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand11));
    qcc_ai_stand();
}
void qcc_demon1_stand11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand12));
    qcc_ai_stand();
}
void qcc_demon1_stand12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand13));
    qcc_ai_stand();
}
void qcc_demon1_stand13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand1));
    qcc_ai_stand();
}
void qcc_demon1_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_idle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(8.00000f);
}
void qcc_demon1_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk3));
    qcc_ai_walk(6.00000f);
}
void qcc_demon1_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk4));
    qcc_ai_walk(6.00000f);
}
void qcc_demon1_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk5));
    qcc_ai_walk(7.00000f);
}
void qcc_demon1_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk6));
    qcc_ai_walk(4.00000f);
}
void qcc_demon1_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk7));
    qcc_ai_walk(6.00000f);
}
void qcc_demon1_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk8));
    qcc_ai_walk(10.0000f);
}
void qcc_demon1_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk1));
    qcc_ai_walk(10.0000f);
}
void qcc_demon1_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_idle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(20.0000f);
}
void qcc_demon1_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run3));
    qcc_ai_run(15.0000f);
}
void qcc_demon1_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run4));
    qcc_ai_run(36.0000f);
}
void qcc_demon1_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run5));
    qcc_ai_run(20.0000f);
}
void qcc_demon1_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run6));
    qcc_ai_run(15.0000f);
}
void qcc_demon1_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run1));
    qcc_ai_run(36.0000f);
}
void qcc_demon1_jump1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump2));
    qcc_ai_face();
}
void qcc_demon1_jump2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump3));
    qcc_ai_face();
}
void qcc_demon1_jump3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump4));
    qcc_ai_face();
}
void qcc_demon1_jump4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump5));
    qcc_ai_face();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Demon_JumpTouch));
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 1);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorAdd(vectorMulFloat(progs.qcc_v_forward, 600), (vector)  {{0.000000f, 0.000000f, 250.000f}}));
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_ONGROUND);
}
void qcc_demon1_jump5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump6));
}
void qcc_demon1_jump6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump7));
}
void qcc_demon1_jump7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump8));
}
void qcc_demon1_jump8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump9));
}
void qcc_demon1_jump9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump10));
}
void qcc_demon1_jump10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump1));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 3)// if three seconds pass, assume demon is stuck and jump again
;
}
void qcc_demon1_jump11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump12));
}
void qcc_demon1_jump12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run1));
}
void qcc_demon1_atta1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta2));
    qcc_ai_charge(4.00000f);
}
void qcc_demon1_atta2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta3));
    qcc_ai_charge(0.000000f);
}
void qcc_demon1_atta3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta4));
    qcc_ai_charge(0.000000f);
}
void qcc_demon1_atta4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta5));
    qcc_ai_charge(1.00000f);
}
void qcc_demon1_atta5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta6));
    qcc_ai_charge(2.00000f);
    qcc_Demon_Melee(200.000f);
}
void qcc_demon1_atta6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta7));
    qcc_ai_charge(1.00000f);
}
void qcc_demon1_atta7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta8));
    qcc_ai_charge(6.00000f);
}
void qcc_demon1_atta8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta9));
    qcc_ai_charge(8.00000f);
}
void qcc_demon1_atta9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta10));
    qcc_ai_charge(4.00000f);
}
void qcc_demon1_atta10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta11));
    qcc_ai_charge(2.00000f);
}
void qcc_demon1_atta11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta12));
    qcc_Demon_Melee(-200.000f);
}
void qcc_demon1_atta12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta13));
    qcc_ai_charge(5.00000f);
}
void qcc_demon1_atta13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta14));
    qcc_ai_charge(8.00000f);
}
void qcc_demon1_atta14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_atta15));
    qcc_ai_charge(4.00000f);
}
void qcc_demon1_atta15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run1));
    qcc_ai_charge(4.00000f);
}
void qcc_demon1_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain2));
}
void qcc_demon1_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain3));
}
void qcc_demon1_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain4));
}
void qcc_demon1_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain5));
}
void qcc_demon1_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain6));
}
void qcc_demon1_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run1));
}
void qcc_demon1_pain(int qcc_attacker, float qcc_damage)
{
    if (areFunctionsEqual(get_qcc_touch(PROG_TO_EDICT(progs.qcc_self)), getFunctionIndex(qcc_Demon_JumpTouch)))
        return;
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_dpain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() * 200 > qcc_damage)
// didn't flinch
        return;
    qcc_demon1_pain1();
}
void qcc_demon1_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_ddeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_demon1_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die3));
}
void qcc_demon1_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die4));
}
void qcc_demon1_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die5));
}
void qcc_demon1_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die6));
}
void qcc_demon1_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die7));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_demon1_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die8));
}
void qcc_demon1_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die9));
}
void qcc_demon1_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_die9));
}
void qcc_demon_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -80)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_demon_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_demon1_die1();
}
void qcc_Demon_MeleeAttack(void)
{
    qcc_demon1_atta1();
/*QUAKED monster_demon1 (1 0 0) (-32 -32 -24) (32 32 64) Ambush

*/}
void qcc_monster_demon1(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_demon_mdl_string_index);
    qcc_precache_model(progs_h_demon_mdl_string_index);
    qcc_precache_sound(demon_ddeath_wav_string_index);
    qcc_precache_sound(demon_dhit2_wav_string_index);
    qcc_precache_sound(demon_djump_wav_string_index);
    qcc_precache_sound(demon_dpain1_wav_string_index);
    qcc_precache_sound(demon_idle1_wav_string_index);
    qcc_precache_sound(demon_sight2_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_demon_mdl_string_index);
    qcc_setsize(progs.qcc_self, qcc_VEC_HULL2_MIN, qcc_VEC_HULL2_MAX);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 300);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_run1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon_die));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Demon_MeleeAttack))// one of two attacks
;
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump1))// jump attack
;
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_pain));
    qcc_walkmonster_start();
/*
==============================================================================

DEMON

==============================================================================
*//*
==============
CheckDemonMelee

Returns TRUE if a melee attack would hit right now
==============
*/}
float qcc_CheckDemonMelee(void)
{
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
// FIXME: check canreach
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
        return qcc_TRUE;
    }
    return qcc_FALSE;
/*
==============
CheckDemonJump

==============
*/}
float qcc_CheckDemonJump(void)
{
    vector qcc_dist;
    float qcc_d;
    if (get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)).z > get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + get_qcc_mins(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + 0.75f * get_qcc_size(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z)
        return qcc_FALSE;
    if (get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)).z < get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + get_qcc_mins(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + 0.25f * get_qcc_size(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z)
        return qcc_FALSE;
    qcc_dist = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    qcc_dist.z = 0;
    qcc_d = qcc_vlen(qcc_dist);
    if (qcc_d < 100)
        return qcc_FALSE;
    if (qcc_d > 200)
    {
        if (qcc_random() < 0.9f)
            return qcc_FALSE;
    }
    return qcc_TRUE;
}
float qcc_DemonCheckAttack(void)
{
    vector qcc_vec// if close enough for slashing, go for it
;
    if (qcc_CheckDemonMelee())
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
        return qcc_TRUE;
    }
    if (qcc_CheckDemonJump())
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MISSILE);
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, demon_djump_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        return qcc_TRUE;
    }
    return qcc_FALSE;
//===========================================================================
}
void qcc_Demon_Melee(float qcc_side)
{
    float qcc_ldmg;
    vector qcc_delta;
    qcc_ai_face();
    qcc_walkmove(get_qcc_ideal_yaw(PROG_TO_EDICT(progs.qcc_self)), 12.0000f)// allow a little closing
;
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 100)
        return;
    if (!qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, demon_dhit2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ldmg = 10 + 5 * qcc_random();
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_side, progs.qcc_v_right));
}
void qcc_Demon_JumpTouch(void)
{
    float qcc_ldmg;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) <= 0)
        return;
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        if (qcc_vlen(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self))) > 400)
        {
            qcc_ldmg = 40 + 10 * qcc_random();
            qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, qcc_ldmg);
        }
    }
    if (!qcc_checkbottom(progs.qcc_self))
    {
        if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
// jump randomly to not get hung up
//dprint ("popjump\n");
        {
            set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
            set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump1));
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f)//			self.velocity_x = (random() - 0.5) * 600;
//			self.velocity_y = (random() - 0.5) * 600;
//			self.velocity_z = 200;
//			self.flags = self.flags - FL_ONGROUND;
;
        }
// not on ground yet
        return;
    }
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_demon1_jump11));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
//File: shambler.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

SHAMBLER

==============================================================================
*/}
void qcc_sham_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand2));
    qcc_ai_stand();
}
void qcc_sham_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand3));
    qcc_ai_stand();
}
void qcc_sham_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand4));
    qcc_ai_stand();
}
void qcc_sham_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand5));
    qcc_ai_stand();
}
void qcc_sham_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand6));
    qcc_ai_stand();
}
void qcc_sham_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand7));
    qcc_ai_stand();
}
void qcc_sham_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand8));
    qcc_ai_stand();
}
void qcc_sham_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand9));
    qcc_ai_stand();
}
void qcc_sham_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand10));
    qcc_ai_stand();
}
void qcc_sham_stand10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand11));
    qcc_ai_stand();
}
void qcc_sham_stand11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand12));
    qcc_ai_stand();
}
void qcc_sham_stand12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand13));
    qcc_ai_stand();
}
void qcc_sham_stand13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand14));
    qcc_ai_stand();
}
void qcc_sham_stand14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand15));
    qcc_ai_stand();
}
void qcc_sham_stand15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand16));
    qcc_ai_stand();
}
void qcc_sham_stand16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand17));
    qcc_ai_stand();
}
void qcc_sham_stand17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand1));
    qcc_ai_stand();
}
void qcc_sham_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk2));
    qcc_ai_walk(10.0000f);
}
void qcc_sham_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk3));
    qcc_ai_walk(9.00000f);
}
void qcc_sham_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk4));
    qcc_ai_walk(9.00000f);
}
void qcc_sham_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk5));
    qcc_ai_walk(5.00000f);
}
void qcc_sham_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk6));
    qcc_ai_walk(6.00000f);
}
void qcc_sham_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk7));
    qcc_ai_walk(12.0000f);
}
void qcc_sham_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk8));
    qcc_ai_walk(8.00000f);
}
void qcc_sham_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk9));
    qcc_ai_walk(3.00000f);
}
void qcc_sham_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk10));
    qcc_ai_walk(13.0000f);
}
void qcc_sham_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk11));
    qcc_ai_walk(9.00000f);
}
void qcc_sham_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk12));
    qcc_ai_walk(7.00000f);
}
void qcc_sham_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk1));
    qcc_ai_walk(7.00000f);
    if (qcc_random() > 0.8f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_sidle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_sham_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run2));
    qcc_ai_run(20.0000f);
}
void qcc_sham_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run3));
    qcc_ai_run(24.0000f);
}
void qcc_sham_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run4));
    qcc_ai_run(20.0000f);
}
void qcc_sham_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run5));
    qcc_ai_run(20.0000f);
}
void qcc_sham_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run6));
    qcc_ai_run(24.0000f);
}
void qcc_sham_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
    qcc_ai_run(20.0000f);
    if (qcc_random() > 0.8f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_sidle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_sham_smash1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_melee1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_charge(2.00000f);
}
void qcc_sham_smash2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash3));
    qcc_ai_charge(6.00000f);
}
void qcc_sham_smash3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash4));
    qcc_ai_charge(6.00000f);
}
void qcc_sham_smash4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash5));
    qcc_ai_charge(5.00000f);
}
void qcc_sham_smash5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash6));
    qcc_ai_charge(4.00000f);
}
void qcc_sham_smash6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash7));
    qcc_ai_charge(1.00000f);
}
void qcc_sham_smash7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash8));
    qcc_ai_charge(0.000000f);
}
void qcc_sham_smash8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash9));
    qcc_ai_charge(0.000000f);
}
void qcc_sham_smash9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash10));
    qcc_ai_charge(0.000000f);
}
void qcc_sham_smash10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash11));
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        return;
    qcc_ai_charge(0.000000f);
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 100)
        return;
    if (!qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 40;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_smack_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_crandom() * 100, progs.qcc_v_right));
    qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_crandom() * 100, progs.qcc_v_right));
}
void qcc_sham_smash11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_smash12));
    qcc_ai_charge(5.00000f);
}
void qcc_sham_smash12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
    qcc_ai_charge(4.00000f);
}
void qcc_sham_swingr1(void);
void qcc_ShamClaw(float qcc_side)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        return;
    qcc_ai_charge(10.0000f);
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 100)
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 20;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_smack_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_side)
    {
        qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
        qcc_SpawnMeatSpray(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 16)), floatMulVector(qcc_side, progs.qcc_v_right));
    }
}
void qcc_sham_swingl1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_melee2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_charge(5.00000f);
}
void qcc_sham_swingl2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl3));
    qcc_ai_charge(3.00000f);
}
void qcc_sham_swingl3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl4));
    qcc_ai_charge(7.00000f);
}
void qcc_sham_swingl4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl5));
    qcc_ai_charge(3.00000f);
}
void qcc_sham_swingl5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl6));
    qcc_ai_charge(7.00000f);
}
void qcc_sham_swingl6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl7));
    qcc_ai_charge(9.00000f);
}
void qcc_sham_swingl7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl8));
    qcc_ai_charge(5.00000f);
    qcc_ShamClaw(250.000f);
}
void qcc_sham_swingl8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl9));
    qcc_ai_charge(4.00000f);
}
void qcc_sham_swingl9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
    qcc_ai_charge(8.00000f);
    if (qcc_random() < 0.5f)
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr1));
}
void qcc_sham_swingr1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_melee1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_charge(1.00000f);
}
void qcc_sham_swingr2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr3));
    qcc_ai_charge(8.00000f);
}
void qcc_sham_swingr3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr4));
    qcc_ai_charge(14.0000f);
}
void qcc_sham_swingr4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr5));
    qcc_ai_charge(7.00000f);
}
void qcc_sham_swingr5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr6));
    qcc_ai_charge(3.00000f);
}
void qcc_sham_swingr6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr7));
    qcc_ai_charge(6.00000f);
}
void qcc_sham_swingr7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr8));
    qcc_ai_charge(6.00000f);
    qcc_ShamClaw(-250.000f);
}
void qcc_sham_swingr8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingr9));
    qcc_ai_charge(3.00000f);
}
void qcc_sham_swingr9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
    qcc_ai_charge(1.00000f);
    qcc_ai_charge(10.0000f);
    if (qcc_random() < 0.5f)
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_swingl1));
}
void qcc_sham_melee(void)
{
    float qcc_chance;
    qcc_chance = qcc_random();
    if (((int) qcc_chance > 0.6f) || ((int) get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) == 600))
        qcc_sham_smash1();
    else
        if (qcc_chance > 0.3f)
            qcc_sham_swingr1();
        else
            qcc_sham_swingl1();
//============================================================================
}
void qcc_CastLightning(void)
{
    vector qcc_org,     qcc_dir;
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    qcc_ai_face();
    qcc_org = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 40.0000f}});
    qcc_dir = vectorSub(vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), (vector)  {{0.000000f, 0.000000f, 16.0000f}}), qcc_org);
    qcc_dir = qcc_normalize(qcc_dir);
    qcc_traceline(qcc_org, vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(qcc_dir, 600)), qcc_TRUE, progs.qcc_self);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_LIGHTNING1);
    qcc_WriteEntity(qcc_MSG_BROADCAST, progs.qcc_self);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, progs.qcc_trace_endpos.z);
    qcc_LightningDamage(qcc_org, progs.qcc_trace_endpos, progs.qcc_self, 10.0000f);
}
void qcc_sham_magic1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic2));
    qcc_ai_face();
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, shambler_sattck1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_sham_magic2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic3));
    qcc_ai_face();
}
void qcc_sham_magic3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic4));
    qcc_ai_face();
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + 0.2f);
    int qcc_o;
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    qcc_ai_face();
    set_qcc_owner(PROG_TO_EDICT(progs.qcc_self), qcc_spawn(qcc_classname_progs_s_light_mdl));
    qcc_o = get_qcc_owner(PROG_TO_EDICT(progs.qcc_self));
    qcc_setmodel(qcc_o, qcc_classname_progs_s_light_mdl);
    qcc_setorigin(qcc_o, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_angles(PROG_TO_EDICT(qcc_o), get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_o), progs.qcc_time + 0.7f);
    set_qcc_think(PROG_TO_EDICT(qcc_o), getFunctionIndex(qcc_SUB_Remove));
}
void qcc_sham_magic4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic5));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    set_qcc_frame(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), 1);
}
void qcc_sham_magic5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic6));
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    set_qcc_frame(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), 2);
}
void qcc_sham_magic6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic9));
    qcc_remove(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)));
    qcc_CastLightning();
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, shambler_sboom_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_sham_magic9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic10));
    qcc_CastLightning();
}
void qcc_sham_magic10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic11));
    qcc_CastLightning();
}
void qcc_sham_magic11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic12));
    if (progs.qcc_skill == 3)
        qcc_CastLightning();
}
void qcc_sham_magic12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
}
void qcc_sham_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain2));
}
void qcc_sham_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain3));
}
void qcc_sham_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain4));
}
void qcc_sham_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain5));
}
void qcc_sham_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain6));
}
void qcc_sham_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
}
void qcc_sham_pain(int qcc_attacker, float qcc_damage)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_shurt2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) <= 0)
// allready dying, don't go into pain frame
        return;
    if (qcc_random() * 400 > qcc_damage)
// didn't flinch
        return;
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
    qcc_sham_pain1();
//============================================================================
}
void qcc_sham_death1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death2));
}
void qcc_sham_death2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death3));
}
void qcc_sham_death3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_sham_death4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death5));
}
void qcc_sham_death5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death6));
}
void qcc_sham_death6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death7));
}
void qcc_sham_death7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death8));
}
void qcc_sham_death8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death9));
}
void qcc_sham_death9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death10));
}
void qcc_sham_death10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death11));
}
void qcc_sham_death11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_death11));
}
void qcc_sham_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -60)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_shams_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shambler_sdeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_sham_death1();
//============================================================================
/*QUAKED monster_shambler (1 0 0) (-32 -32 -24) (32 32 64) Ambush
*/}
void qcc_monster_shambler(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_shambler_mdl_string_index);
    qcc_precache_model(qcc_classname_progs_s_light_mdl);
    qcc_precache_model(progs_h_shams_mdl_string_index);
    qcc_precache_model(progs_bolt_mdl_string_index);
    qcc_precache_sound(shambler_sattck1_wav_string_index);
    qcc_precache_sound(shambler_sboom_wav_string_index);
    qcc_precache_sound(shambler_sdeath_wav_string_index);
    qcc_precache_sound(shambler_shurt2_wav_string_index);
    qcc_precache_sound(shambler_sidle_wav_string_index);
    qcc_precache_sound(shambler_ssight_wav_string_index);
    qcc_precache_sound(shambler_melee1_wav_string_index);
    qcc_precache_sound(shambler_melee2_wav_string_index);
    qcc_precache_sound(shambler_smack_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_shambler_mdl_string_index);
    qcc_setsize(progs.qcc_self, qcc_VEC_HULL2_MIN, qcc_VEC_HULL2_MAX);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 600);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_run1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_die));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_melee));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_magic1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_sham_pain));
    qcc_walkmonster_start();
//File: knight.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

KNIGHT

==============================================================================
*///frame runc1 runc2 runc3 runc4 runc5 runc6
//frame attack1 attack2 attack3 attack4 attack5 attack6 attack7
//frame attack8 attack9 attack10 attack11
}
void qcc_knight_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand2));
    qcc_ai_stand();
}
void qcc_knight_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand3));
    qcc_ai_stand();
}
void qcc_knight_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand4));
    qcc_ai_stand();
}
void qcc_knight_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand5));
    qcc_ai_stand();
}
void qcc_knight_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand6));
    qcc_ai_stand();
}
void qcc_knight_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand7));
    qcc_ai_stand();
}
void qcc_knight_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand8));
    qcc_ai_stand();
}
void qcc_knight_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand9));
    qcc_ai_stand();
}
void qcc_knight_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand1));
    qcc_ai_stand();
}
void qcc_knight_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, knight_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk3));
    qcc_ai_walk(2.00000f);
}
void qcc_knight_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk4));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk5));
    qcc_ai_walk(4.00000f);
}
void qcc_knight_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk6));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk7));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk8));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk9));
    qcc_ai_walk(4.00000f);
}
void qcc_knight_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk10));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk11));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk12));
    qcc_ai_walk(2.00000f);
}
void qcc_knight_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk13));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk14));
    qcc_ai_walk(4.00000f);
}
void qcc_knight_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk1));
    qcc_ai_walk(3.00000f);
}
void qcc_knight_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, knight_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(16.0000f);
}
void qcc_knight_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run3));
    qcc_ai_run(20.0000f);
}
void qcc_knight_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run4));
    qcc_ai_run(13.0000f);
}
void qcc_knight_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run5));
    qcc_ai_run(7.00000f);
}
void qcc_knight_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run6));
    qcc_ai_run(16.0000f);
}
void qcc_knight_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run7));
    qcc_ai_run(20.0000f);
}
void qcc_knight_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run8));
    qcc_ai_run(14.0000f);
}
void qcc_knight_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
    qcc_ai_run(6.00000f);
}
void qcc_knight_runatk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk2));
    if (qcc_random() > 0.5f)
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, knight_sword2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    else
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, knight_sword1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_charge(20.0000f);
}
void qcc_knight_runatk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk3));
    qcc_ai_charge_side();
}
void qcc_knight_runatk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk4));
    qcc_ai_charge_side();
}
void qcc_knight_runatk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk5));
    qcc_ai_charge_side();
}
void qcc_knight_runatk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk6));
    qcc_ai_melee_side();
}
void qcc_knight_runatk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk7));
    qcc_ai_melee_side();
}
void qcc_knight_runatk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk8));
    qcc_ai_melee_side();
}
void qcc_knight_runatk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk9));
    qcc_ai_melee_side();
}
void qcc_knight_runatk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk10));
    qcc_ai_melee_side();
}
void qcc_knight_runatk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_runatk11));
    qcc_ai_charge_side();
}
void qcc_knight_runatk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
    qcc_ai_charge(10.0000f);
}
void qcc_knight_atk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk2));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, knight_sword1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_charge(0.000000f);
}
void qcc_knight_atk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk3));
    qcc_ai_charge(7.00000f);
}
void qcc_knight_atk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk4));
    qcc_ai_charge(4.00000f);
}
void qcc_knight_atk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk5));
    qcc_ai_charge(0.000000f);
}
void qcc_knight_atk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk6));
    qcc_ai_charge(3.00000f);
}
void qcc_knight_atk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk7));
    qcc_ai_charge(4.00000f);
    qcc_ai_melee();
}
void qcc_knight_atk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk8));
    qcc_ai_charge(1.00000f);
    qcc_ai_melee();
}
void qcc_knight_atk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk9));
    qcc_ai_charge(3.00000f);
    qcc_ai_melee();
}
void qcc_knight_atk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk10));
    qcc_ai_charge(1.00000f);
}
void qcc_knight_atk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
    qcc_ai_charge(5.00000f);
//void()	knight_atk9	=[	$attack9,		knight_atk10	] {};
//void()	knight_atk10	=[	$attack10,		knight_atk11	] {};
//void()	knight_atk11	=[	$attack11,		knight_run1	] {};
//===========================================================================
}
void qcc_knight_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_pain2));
}
void qcc_knight_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_pain3));
}
void qcc_knight_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
}
void qcc_knight_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb2));
    qcc_ai_painforward(0.000000f);
}
void qcc_knight_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb3));
    qcc_ai_painforward(3.00000f);
}
void qcc_knight_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb4));
}
void qcc_knight_painb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb5));
}
void qcc_knight_painb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb6));
    qcc_ai_painforward(2.00000f);
}
void qcc_knight_painb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb7));
    qcc_ai_painforward(4.00000f);
}
void qcc_knight_painb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb8));
    qcc_ai_painforward(2.00000f);
}
void qcc_knight_painb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb9));
    qcc_ai_painforward(5.00000f);
}
void qcc_knight_painb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb10));
    qcc_ai_painforward(5.00000f);
}
void qcc_knight_painb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_painb11));
    qcc_ai_painforward(0.000000f);
}
void qcc_knight_painb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
}
void qcc_knight_pain(int qcc_attacker, float qcc_damage)
{
    float qcc_r;
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    qcc_r = qcc_random();
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, knight_khurt_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_r < 0.85f)
    {
        qcc_knight_pain1();
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    }
    else
    {
        qcc_knight_painb1();
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    }
//===========================================================================
}
void qcc_knight_bow1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow2));
    qcc_ai_turn();
}
void qcc_knight_bow2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow3));
    qcc_ai_turn();
}
void qcc_knight_bow3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow4));
    qcc_ai_turn();
}
void qcc_knight_bow4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow5));
    qcc_ai_turn();
}
void qcc_knight_bow5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow5));
    qcc_ai_turn();
}
void qcc_knight_bow6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow7));
    qcc_ai_turn();
}
void qcc_knight_bow7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow8));
    qcc_ai_turn();
}
void qcc_knight_bow8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow9));
    qcc_ai_turn();
}
void qcc_knight_bow9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_bow10));
    qcc_ai_turn();
}
void qcc_knight_bow10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk1));
    qcc_ai_turn();
}
void qcc_knight_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die2));
}
void qcc_knight_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die3));
}
void qcc_knight_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_knight_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die5));
}
void qcc_knight_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die6));
}
void qcc_knight_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die7));
}
void qcc_knight_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die8));
}
void qcc_knight_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die9));
}
void qcc_knight_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die10));
}
void qcc_knight_die10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die10));
}
void qcc_knight_dieb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb2));
}
void qcc_knight_dieb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb3));
}
void qcc_knight_dieb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_knight_dieb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb5));
}
void qcc_knight_dieb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb6));
}
void qcc_knight_dieb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb7));
}
void qcc_knight_dieb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb8));
}
void qcc_knight_dieb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb9));
}
void qcc_knight_dieb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb10));
}
void qcc_knight_dieb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb11));
}
void qcc_knight_dieb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_dieb11));
}
void qcc_knight_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -40)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_knight_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, knight_kdeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() < 0.5f)
        qcc_knight_die1();
    else
        qcc_knight_dieb1();
/*QUAKED monster_knight (1 0 0) (-16 -16 -24) (16 16 40) Ambush
*/}
void qcc_monster_knight(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_knight_mdl_string_index);
    qcc_precache_model(progs_h_knight_mdl_string_index);
    qcc_precache_sound(knight_kdeath_wav_string_index);
    qcc_precache_sound(knight_khurt_wav_string_index);
    qcc_precache_sound(knight_ksight_wav_string_index);
    qcc_precache_sound(knight_sword1_wav_string_index);
    qcc_precache_sound(knight_sword2_wav_string_index);
    qcc_precache_sound(knight_idle_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_knight_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 75);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_run1));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_atk1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_knight_die));
    qcc_walkmonster_start();
//File: soldier.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

SOLDIER / PLAYER

==============================================================================
*//*
==============================================================================
SOLDIER CODE
==============================================================================
*/}
void qcc_army_fire(void);
void qcc_army_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand2));
    qcc_ai_stand();
}
void qcc_army_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand3));
    qcc_ai_stand();
}
void qcc_army_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand4));
    qcc_ai_stand();
}
void qcc_army_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand5));
    qcc_ai_stand();
}
void qcc_army_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand6));
    qcc_ai_stand();
}
void qcc_army_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand7));
    qcc_ai_stand();
}
void qcc_army_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand8));
    qcc_ai_stand();
}
void qcc_army_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand1));
    qcc_ai_stand();
}
void qcc_army_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk3));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk4));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk5));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk6));
    qcc_ai_walk(2.00000f);
}
void qcc_army_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk7));
    qcc_ai_walk(3.00000f);
}
void qcc_army_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk8));
    qcc_ai_walk(4.00000f);
}
void qcc_army_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk9));
    qcc_ai_walk(4.00000f);
}
void qcc_army_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk10));
    qcc_ai_walk(2.00000f);
}
void qcc_army_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk11));
    qcc_ai_walk(2.00000f);
}
void qcc_army_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk12));
    qcc_ai_walk(2.00000f);
}
void qcc_army_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk13));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk14));
    qcc_ai_walk(0.000000f);
}
void qcc_army_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk15));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk16));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk17));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 106); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk18));
    qcc_ai_walk(3.00000f);
}
void qcc_army_walk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 107); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk19));
    qcc_ai_walk(3.00000f);
}
void qcc_army_walk19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 108); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk20));
    qcc_ai_walk(3.00000f);
}
void qcc_army_walk20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 109); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk21));
    qcc_ai_walk(3.00000f);
}
void qcc_army_walk21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 110); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk22));
    qcc_ai_walk(2.00000f);
}
void qcc_army_walk22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 111); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk23));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 112); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk24));
    qcc_ai_walk(1.00000f);
}
void qcc_army_walk24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 113); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk1));
    qcc_ai_walk(1.00000f);
}
void qcc_army_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(11.0000f);
}
void qcc_army_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run3));
    qcc_ai_run(15.0000f);
}
void qcc_army_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run4));
    qcc_ai_run(10.0000f);
}
void qcc_army_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run5));
    qcc_ai_run(10.0000f);
}
void qcc_army_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run6));
    qcc_ai_run(8.00000f);
}
void qcc_army_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run7));
    qcc_ai_run(15.0000f);
}
void qcc_army_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run8));
    qcc_ai_run(10.0000f);
}
void qcc_army_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
    qcc_ai_run(8.00000f);
}
void qcc_army_atk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk2));
    qcc_ai_face();
}
void qcc_army_atk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk3));
    qcc_ai_face();
}
void qcc_army_atk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk4));
    qcc_ai_face();
}
void qcc_army_atk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk5));
    qcc_ai_face();
}
void qcc_army_atk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk6));
    qcc_ai_face();
    qcc_army_fire();
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
}
void qcc_army_atk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk7));
    qcc_ai_face();
}
void qcc_army_atk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk8));
    qcc_ai_face();
    qcc_SUB_CheckRefire(getFunctionIndex (qcc_army_atk1));
}
void qcc_army_atk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk9));
    qcc_ai_face();
}
void qcc_army_atk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
    qcc_ai_face();
}
void qcc_army_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain2));
}
void qcc_army_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain3));
}
void qcc_army_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain4));
}
void qcc_army_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain5));
}
void qcc_army_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain6));
}
void qcc_army_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
    qcc_ai_pain(1.00000f);
}
void qcc_army_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb2));
}
void qcc_army_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb3));
    qcc_ai_painforward(13.0000f);
}
void qcc_army_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb4));
    qcc_ai_painforward(9.00000f);
}
void qcc_army_painb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb5));
}
void qcc_army_painb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb6));
}
void qcc_army_painb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb7));
}
void qcc_army_painb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb8));
}
void qcc_army_painb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb9));
}
void qcc_army_painb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb10));
}
void qcc_army_painb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb11));
}
void qcc_army_painb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb12));
}
void qcc_army_painb12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb13));
    qcc_ai_pain(2.00000f);
}
void qcc_army_painb13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painb14));
}
void qcc_army_painb14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
}
void qcc_army_painc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc2));
}
void qcc_army_painc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc3));
    qcc_ai_pain(1.00000f);
}
void qcc_army_painc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc4));
}
void qcc_army_painc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc5));
}
void qcc_army_painc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc6));
    qcc_ai_painforward(1.00000f);
}
void qcc_army_painc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc7));
    qcc_ai_painforward(1.00000f);
}
void qcc_army_painc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc8));
}
void qcc_army_painc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc9));
    qcc_ai_pain(1.00000f);
}
void qcc_army_painc9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc10));
    qcc_ai_painforward(4.00000f);
}
void qcc_army_painc10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc11));
    qcc_ai_painforward(3.00000f);
}
void qcc_army_painc11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc12));
    qcc_ai_painforward(6.00000f);
}
void qcc_army_painc12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_painc13));
    qcc_ai_painforward(8.00000f);
}
void qcc_army_painc13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
}
void qcc_army_pain(int qcc_attacker, float qcc_damage)
{
    float qcc_r;
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    qcc_r = qcc_random();
    if (qcc_r < 0.2f)
    {
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.6f);
        qcc_army_pain1();
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    }
    else
        if (qcc_r < 0.6f)
        {
            set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1.1f);
            qcc_army_painb1();
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_pain2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
        else
        {
            set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1.1f);
            qcc_army_painc1();
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_pain2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
}
void qcc_army_fire(void)
{
    vector qcc_dir;
    int qcc_en;
    qcc_ai_face();
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, soldier_sattck1_wav_string_index, 1.00000f, qcc_ATTN_NORM)// fire somewhat behind the player, so a dodging player is harder to hit
;
    qcc_en = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self));
    qcc_dir = vectorSub(get_qcc_origin(PROG_TO_EDICT(qcc_en)), vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(qcc_en)), 0.2f));
    qcc_dir = qcc_normalize(vectorSub(qcc_dir, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_FireBullets(4.00000f, qcc_dir, (vector) {{0.100000f, 0.100000f, 0.000000f}});
}
void qcc_army_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die2));
}
void qcc_army_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die3));
}
void qcc_army_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), 5);
    qcc_DropBackpack();
}
void qcc_army_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die5));
}
void qcc_army_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die6));
}
void qcc_army_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die7));
}
void qcc_army_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die8));
}
void qcc_army_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die9));
}
void qcc_army_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die10));
}
void qcc_army_die10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die10));
}
void qcc_army_cdie1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie2));
}
void qcc_army_cdie2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie3));
    qcc_ai_back(5.00000f);
}
void qcc_army_cdie3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_shells(PROG_TO_EDICT(progs.qcc_self), 5);
    qcc_DropBackpack();
    qcc_ai_back(4.00000f);
}
void qcc_army_cdie4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie5));
    qcc_ai_back(13.0000f);
}
void qcc_army_cdie5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie6));
    qcc_ai_back(3.00000f);
}
void qcc_army_cdie6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie7));
    qcc_ai_back(4.00000f);
}
void qcc_army_cdie7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie8));
}
void qcc_army_cdie8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie9));
}
void qcc_army_cdie9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie10));
}
void qcc_army_cdie10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie11));
}
void qcc_army_cdie11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_cdie11));
}
void qcc_army_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -35)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_guard_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, soldier_death1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() < 0.5f)
        qcc_army_die1();
    else
        qcc_army_cdie1();
/*QUAKED monster_army (1 0 0) (-16 -16 -24) (16 16 40) Ambush
*/}
void qcc_monster_army(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_soldier_mdl_string_index);
    qcc_precache_model(progs_h_guard_mdl_string_index);
    qcc_precache_model(qcc_classname_progs_gib1_mdl);
    qcc_precache_model(qcc_classname_progs_gib2_mdl);
    qcc_precache_model(qcc_classname_progs_gib3_mdl);
    qcc_precache_sound(soldier_death1_wav_string_index);
    qcc_precache_sound(soldier_idle_wav_string_index);
    qcc_precache_sound(soldier_pain1_wav_string_index);
    qcc_precache_sound(soldier_pain2_wav_string_index);
    qcc_precache_sound(soldier_sattck1_wav_string_index);
    qcc_precache_sound(soldier_sight1_wav_string_index);
    qcc_precache_sound(player_udeath_wav_string_index)// gib death
;
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_soldier_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 30);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_run1));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_atk1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_army_die));
    qcc_walkmonster_start();
//File: wizard.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

WIZARD

==============================================================================
*//*
==============================================================================

WIZARD

If the player moves behind cover before the missile is launched, launch it
at the last visible spot with no velocity leading, in hopes that the player
will duck back out and catch it.
==============================================================================
*//*
=============
LaunchMissile

Sets the given entities velocity and angles so that it will hit self.enemy
if self.enemy maintains it's current velocity
0.1 is moderately accurate, 0.0 is totally accurate
=============
*/}
void qcc_LaunchMissile(int qcc_missile, float qcc_mspeed, float qcc_accuracy)
{
    vector qcc_vec,     qcc_move;
    float qcc_fly;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)))// set missile speed
;
    qcc_vec = vectorSub(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_mins(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))), vectorMulFloat(get_qcc_size(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), 0.7f)), get_qcc_origin(PROG_TO_EDICT(qcc_missile)))// calc aproximate time for missile to reach vec
;
    qcc_fly = qcc_vlen(qcc_vec) / qcc_mspeed// get the entities xy velocity
;
    qcc_move = get_qcc_velocity(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))));
    qcc_move.z = 0// project the target forward in time
;
    qcc_vec = vectorAdd(qcc_vec, vectorMulFloat(qcc_move, qcc_fly));
    qcc_vec = qcc_normalize(qcc_vec);
    qcc_vec = vectorAdd(vectorAdd(qcc_vec, vectorMulFloat(floatMulVector(qcc_accuracy, progs.qcc_v_up), ( qcc_random() - 0.5f ))), vectorMulFloat(floatMulVector(qcc_accuracy, progs.qcc_v_right), ( qcc_random() - 0.5f )));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(qcc_vec, qcc_mspeed));
    set_qcc_angles(PROG_TO_EDICT(qcc_missile), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_angles_y(PROG_TO_EDICT(qcc_missile), qcc_vectoyaw(get_qcc_velocity(PROG_TO_EDICT(qcc_missile))))// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 5);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_SUB_Remove));
}
void qcc_wiz_run1(void);
/*
=================
WizardCheckAttack
=================
*/void qcc_wiz_side1(void);
float qcc_WizardCheckAttack(void)
{
    vector qcc_spot1,     qcc_spot2;
    int qcc_targ;
    float qcc_chance;
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return qcc_FALSE;
    if (!progs.qcc_enemy_vis)
        return qcc_FALSE;
    if (progs.qcc_enemy_range == qcc_RANGE_FAR)
    {
        if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) != qcc_AS_STRAIGHT)
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
            qcc_wiz_run1();
        }
        return qcc_FALSE;
    }
    qcc_targ = get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))// see if any entities are in the way of the shot
;
    qcc_spot1 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_view_ofs(PROG_TO_EDICT(progs.qcc_self)));
    qcc_spot2 = vectorAdd(get_qcc_origin(PROG_TO_EDICT(qcc_targ)), get_qcc_view_ofs(PROG_TO_EDICT(qcc_targ)));
    qcc_traceline(qcc_spot1, qcc_spot2, qcc_FALSE, progs.qcc_self);
    if (progs.qcc_trace_ent != qcc_targ)
// don't have a clear shot, so move to a side
    {
        if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) != qcc_AS_STRAIGHT)
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
            qcc_wiz_run1();
        }
        return qcc_FALSE;
    }
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
        qcc_chance = 0.9f;
    else
        if (progs.qcc_enemy_range == qcc_RANGE_NEAR)
            qcc_chance = 0.6f;
        else
            if (progs.qcc_enemy_range == qcc_RANGE_MID)
                qcc_chance = 0.2f;
            else
                qcc_chance = 0;
    if (qcc_random() < qcc_chance)
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MISSILE);
        return qcc_TRUE;
    }
    if (progs.qcc_enemy_range == qcc_RANGE_MID)
    {
        if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) != qcc_AS_STRAIGHT)
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
            qcc_wiz_run1();
        }
    }
    else
    {
        if (get_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self)) != qcc_AS_SLIDING)
        {
            set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_SLIDING);
            qcc_wiz_side1();
        }
    }
    return qcc_FALSE;
/*
=================
WizardAttackFinished
=================
*/}
void qcc_WizardAttackFinished(void)
{
    if (((int) progs.qcc_enemy_range >= qcc_RANGE_MID) || ((int) !progs.qcc_enemy_vis))
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_STRAIGHT);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run1));
    }
    else
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_SLIDING);
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side1));
    }
/*
==============================================================================

FAST ATTACKS

==============================================================================
*/}
void qcc_Wiz_FastFire(void)
{
    vector qcc_vec;
    vector qcc_dst;
    if (get_qcc_health(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))) > 0)
    {
        set_qcc_effects(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))), (((int) get_qcc_effects(PROG_TO_EDICT(get_qcc_owner(PROG_TO_EDICT(progs.qcc_self))))) | ((int) qcc_EF_MUZZLEFLASH)));
        qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))));
        qcc_dst = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), floatMulVector(13, get_qcc_movedir(PROG_TO_EDICT(progs.qcc_self))));
        qcc_vec = qcc_normalize(vectorSub(qcc_dst, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, wizard_wattack_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_launch_spike(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), qcc_vec);
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(qcc_vec, 600));
        set_qcc_owner(PROG_TO_EDICT(progs.qcc_newmis), get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_classname(PROG_TO_EDICT(progs.qcc_newmis), qcc_classname_wizspike);
        qcc_setmodel(progs.qcc_newmis, progs_w_spike_mdl_string_index);
        qcc_setsize(progs.qcc_newmis, qcc_VEC_ORIGIN, qcc_VEC_ORIGIN);
    }
    qcc_remove(progs.qcc_self);
}
void qcc_Wiz_StartFast(void)
{
    int qcc_missile;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, wizard_wattack_wav_string_index, 1.00000f, qcc_ATTN_NORM)//      next-hack: removed. Why was there, btw ?
//	self.v_angle = self.angles;
;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_missile = qcc_spawn(qcc_classname_nh_wiz_startfast);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 0.6f);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 30.0000f}}), vectorMulFloat(progs.qcc_v_forward, 14)), vectorMulFloat(progs.qcc_v_right, 14)));
    set_qcc_enemy(PROG_TO_EDICT(qcc_missile), get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 0.8f);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_Wiz_FastFire));
    set_qcc_movedir(PROG_TO_EDICT(qcc_missile), progs.qcc_v_right);
    qcc_missile = qcc_spawn(qcc_classname_nh_wiz_startfast);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 1);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 30.0000f}}), vectorMulFloat(progs.qcc_v_forward, 14)), vectorMulFloat(progs.qcc_v_right, -14)));
    set_qcc_enemy(PROG_TO_EDICT(qcc_missile), get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 0.3f);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_Wiz_FastFire));
    set_qcc_movedir(PROG_TO_EDICT(qcc_missile), vectorSub(qcc_VEC_ORIGIN, progs.qcc_v_right));
}
void qcc_Wiz_idlesound(void)
{
    float qcc_wr;
    qcc_wr = qcc_random() * 5;
    if (get_qcc_waitmin(PROG_TO_EDICT(progs.qcc_self)) < progs.qcc_time)
    {
        set_qcc_waitmin(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
        if (qcc_wr > 4.5f)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, wizard_widle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
        if (qcc_wr < 1.5f)
            qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, wizard_widle2_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    }
    return;
}
void qcc_wiz_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand2));
    qcc_ai_stand();
}
void qcc_wiz_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand3));
    qcc_ai_stand();
}
void qcc_wiz_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand4));
    qcc_ai_stand();
}
void qcc_wiz_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand5));
    qcc_ai_stand();
}
void qcc_wiz_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand6));
    qcc_ai_stand();
}
void qcc_wiz_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand7));
    qcc_ai_stand();
}
void qcc_wiz_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand8));
    qcc_ai_stand();
}
void qcc_wiz_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand1));
    qcc_ai_stand();
}
void qcc_wiz_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk2));
    qcc_ai_walk(8.00000f);
    qcc_Wiz_idlesound();
}
void qcc_wiz_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk3));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk4));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk5));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk6));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk7));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk8));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk1));
    qcc_ai_walk(8.00000f);
}
void qcc_wiz_side1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side2));
    qcc_ai_run(8.00000f);
    qcc_Wiz_idlesound();
}
void qcc_wiz_side2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side3));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side4));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side5));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side6));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side7));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side8));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_side8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_side1));
    qcc_ai_run(8.00000f);
}
void qcc_wiz_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run2));
    qcc_ai_run(16.0000f);
    qcc_Wiz_idlesound();
}
void qcc_wiz_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run3));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run4));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run5));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run6));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run7));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run8));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run9));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run10));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run11));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run12));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run13));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run14));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_run14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run1));
    qcc_ai_run(16.0000f);
}
void qcc_wiz_fast1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast2));
    qcc_ai_face();
    qcc_Wiz_StartFast();
}
void qcc_wiz_fast2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast3));
    qcc_ai_face();
}
void qcc_wiz_fast3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast4));
    qcc_ai_face();
}
void qcc_wiz_fast4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast5));
    qcc_ai_face();
}
void qcc_wiz_fast5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast6));
    qcc_ai_face();
}
void qcc_wiz_fast6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast7));
    qcc_ai_face();
}
void qcc_wiz_fast7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast8));
    qcc_ai_face();
}
void qcc_wiz_fast8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast9));
    qcc_ai_face();
}
void qcc_wiz_fast9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_fast10));
    qcc_ai_face();
}
void qcc_wiz_fast10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run1));
    qcc_ai_face();
    qcc_SUB_AttackFinished(2.00000f);
    qcc_WizardAttackFinished();
}
void qcc_wiz_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_pain2));
}
void qcc_wiz_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_pain3));
}
void qcc_wiz_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_pain4));
}
void qcc_wiz_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run1));
}
void qcc_wiz_death1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death2));
    set_qcc_velocity_x(PROG_TO_EDICT(progs.qcc_self), -200 + 400 * qcc_random());
    set_qcc_velocity_y(PROG_TO_EDICT(progs.qcc_self), -200 + 400 * qcc_random());
    set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), 100 + 100 * qcc_random());
    set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - ( (((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)) ));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, wizard_wdeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_wiz_death2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death3));
}
void qcc_wiz_death3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_wiz_death4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death5));
}
void qcc_wiz_death5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death6));
}
void qcc_wiz_death6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death7));
}
void qcc_wiz_death7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death8));
}
void qcc_wiz_death8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_death8));
}
void qcc_wiz_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -40)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_wizard_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
    }
    qcc_wiz_death1();
}
void qcc_Wiz_Pain(int qcc_attacker, float qcc_damage)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, wizard_wpain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() * 70 > qcc_damage)
// didn't flinch
        return;
    qcc_wiz_pain1();
}
void qcc_Wiz_Missile(void)
{
    qcc_wiz_fast1();
/*QUAKED monster_wizard (1 0 0) (-16 -16 -24) (16 16 40) Ambush
*/}
void qcc_monster_wizard(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_wizard_mdl_string_index);
    qcc_precache_model(progs_h_wizard_mdl_string_index);
    qcc_precache_model(progs_w_spike_mdl_string_index);
    qcc_precache_sound(wizard_hit_wav_string_index)// used by c code
;
    qcc_precache_sound(wizard_wattack_wav_string_index);
    qcc_precache_sound(wizard_wdeath_wav_string_index);
    qcc_precache_sound(wizard_widle1_wav_string_index);
    qcc_precache_sound(wizard_widle2_wav_string_index);
    qcc_precache_sound(wizard_wpain_wav_string_index);
    qcc_precache_sound(wizard_wsight_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_wizard_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 80);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_run1));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Wiz_Missile));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Wiz_Pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_wiz_die));
    qcc_flymonster_start();
//File: dog.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

DOG

==============================================================================
*/}
void qcc_dog_leap1(void);
/*
================
dog_bite

================
*/void qcc_dog_run1(void);
void qcc_dog_bite(void)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
        return;
    qcc_ai_charge(10.0000f);
    if (!qcc_CanDamage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self))
        return;
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 100)
        return;
    qcc_ldmg = ( qcc_random() + qcc_random() + qcc_random() ) * 8;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
}
void qcc_Dog_JumpTouch(void)
{
    float qcc_ldmg;
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) <= 0)
        return;
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        if (qcc_vlen(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self))) > 300)
        {
            qcc_ldmg = 10 + 10 * qcc_random();
            qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, qcc_ldmg);
        }
    }
    if (!qcc_checkbottom(progs.qcc_self))
    {
        if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
// jump randomly to not get hung up
//dprint ("popjump\n");
        {
            set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
            set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap1));
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f)//			self.velocity_x = (random() - 0.5) * 600;
//			self.velocity_y = (random() - 0.5) * 600;
//			self.velocity_z = 200;
//			self.flags = self.flags - FL_ONGROUND;
;
        }
// not on ground yet
        return;
    }
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
}
void qcc_dog_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand2));
    qcc_ai_stand();
}
void qcc_dog_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand3));
    qcc_ai_stand();
}
void qcc_dog_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand4));
    qcc_ai_stand();
}
void qcc_dog_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand5));
    qcc_ai_stand();
}
void qcc_dog_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand6));
    qcc_ai_stand();
}
void qcc_dog_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand7));
    qcc_ai_stand();
}
void qcc_dog_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand8));
    qcc_ai_stand();
}
void qcc_dog_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand9));
    qcc_ai_stand();
}
void qcc_dog_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand1));
    qcc_ai_stand();
}
void qcc_dog_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk3));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk4));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk5));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk6));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk7));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk8));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk1));
    qcc_ai_walk(8.00000f);
}
void qcc_dog_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(16.0000f);
}
void qcc_dog_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run3));
    qcc_ai_run(32.0000f);
}
void qcc_dog_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run4));
    qcc_ai_run(32.0000f);
}
void qcc_dog_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run5));
    qcc_ai_run(20.0000f);
}
void qcc_dog_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run6));
    qcc_ai_run(64.0000f);
}
void qcc_dog_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run7));
    qcc_ai_run(32.0000f);
}
void qcc_dog_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run8));
    qcc_ai_run(16.0000f);
}
void qcc_dog_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run9));
    qcc_ai_run(32.0000f);
}
void qcc_dog_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run10));
    qcc_ai_run(32.0000f);
}
void qcc_dog_run10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run11));
    qcc_ai_run(20.0000f);
}
void qcc_dog_run11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run12));
    qcc_ai_run(64.0000f);
}
void qcc_dog_run12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
    qcc_ai_run(32.0000f);
}
void qcc_dog_atta1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta2));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta3));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta4));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta5));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_dattack1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_dog_bite();
}
void qcc_dog_atta5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta6));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta7));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta8));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_atta8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
    qcc_ai_charge(10.0000f);
}
void qcc_dog_leap1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap2));
    qcc_ai_face();
}
void qcc_dog_leap2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap3));
    qcc_ai_face();
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Dog_JumpTouch));
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 1);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorAdd(vectorMulFloat(progs.qcc_v_forward, 300), (vector)  {{0.000000f, 0.000000f, 200.000f}}));
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_ONGROUND);
}
void qcc_dog_leap3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap4));
}
void qcc_dog_leap4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap5));
}
void qcc_dog_leap5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap6));
}
void qcc_dog_leap6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap7));
}
void qcc_dog_leap7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap8));
}
void qcc_dog_leap8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap9));
}
void qcc_dog_leap9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap9));
}
void qcc_dog_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain2));
}
void qcc_dog_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain3));
}
void qcc_dog_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain4));
}
void qcc_dog_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain5));
}
void qcc_dog_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain6));
}
void qcc_dog_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
}
void qcc_dog_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb2));
}
void qcc_dog_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb3));
}
void qcc_dog_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb4));
    qcc_ai_pain(4.00000f);
}
void qcc_dog_painb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb5));
    qcc_ai_pain(12.0000f);
}
void qcc_dog_painb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb6));
    qcc_ai_pain(12.0000f);
}
void qcc_dog_painb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb7));
    qcc_ai_pain(2.00000f);
}
void qcc_dog_painb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb8));
}
void qcc_dog_painb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb9));
    qcc_ai_pain(4.00000f);
}
void qcc_dog_painb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb10));
}
void qcc_dog_painb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb11));
    qcc_ai_pain(10.0000f);
}
void qcc_dog_painb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb12));
}
void qcc_dog_painb12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb13));
}
void qcc_dog_painb13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb14));
}
void qcc_dog_painb14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb15));
}
void qcc_dog_painb15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_painb16));
}
void qcc_dog_painb16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
}
void qcc_dog_pain(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_dpain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() > 0.5f)
        qcc_dog_pain1();
    else
        qcc_dog_painb1();
}
void qcc_dog_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die2));
}
void qcc_dog_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die3));
}
void qcc_dog_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die4));
}
void qcc_dog_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die5));
}
void qcc_dog_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die6));
}
void qcc_dog_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die7));
}
void qcc_dog_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die8));
}
void qcc_dog_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die9));
}
void qcc_dog_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die9));
}
void qcc_dog_dieb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb2));
}
void qcc_dog_dieb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb3));
}
void qcc_dog_dieb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb4));
}
void qcc_dog_dieb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb5));
}
void qcc_dog_dieb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb6));
}
void qcc_dog_dieb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb7));
}
void qcc_dog_dieb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb8));
}
void qcc_dog_dieb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb9));
}
void qcc_dog_dieb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_dieb9));
}
void qcc_dog_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -35)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowHead(progs_h_dog_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, dog_ddeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    if (qcc_random() > 0.5f)
        qcc_dog_die1();
    else
        qcc_dog_dieb1();
//============================================================================
/*
==============
CheckDogMelee

Returns TRUE if a melee attack would hit right now
==============
*/}
float qcc_CheckDogMelee(void)
{
    if (progs.qcc_enemy_range == qcc_RANGE_MELEE)
// FIXME: check canreach
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
        return qcc_TRUE;
    }
    return qcc_FALSE;
/*
==============
CheckDogJump

==============
*/}
float qcc_CheckDogJump(void)
{
    vector qcc_dist;
    float qcc_d;
    if (get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + get_qcc_mins(PROG_TO_EDICT(progs.qcc_self)).z > get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + get_qcc_mins(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + 0.75f * get_qcc_size(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z)
        return qcc_FALSE;
    if (get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + get_qcc_maxs(PROG_TO_EDICT(progs.qcc_self)).z < get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + get_qcc_mins(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z + 0.25f * get_qcc_size(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z)
        return qcc_FALSE;
    qcc_dist = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    qcc_dist.z = 0;
    qcc_d = qcc_vlen(qcc_dist);
    if (qcc_d < 80)
        return qcc_FALSE;
    if (qcc_d > 150)
        return qcc_FALSE;
    return qcc_TRUE;
}
float qcc_DogCheckAttack(void)
{
    vector qcc_vec// if close enough for slashing, go for it
;
    if (qcc_CheckDogMelee())
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MELEE);
        return qcc_TRUE;
    }
    if (qcc_CheckDogJump())
    {
        set_qcc_attack_state(PROG_TO_EDICT(progs.qcc_self), qcc_AS_MISSILE);
        return qcc_TRUE;
    }
    return qcc_FALSE;
//===========================================================================
/*QUAKED monster_dog (1 0 0) (-32 -32 -24) (32 32 40) Ambush

*/}
void qcc_monster_dog(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_h_dog_mdl_string_index);
    qcc_precache_model(progs_dog_mdl_string_index);
    qcc_precache_sound(dog_dattack1_wav_string_index);
    qcc_precache_sound(dog_ddeath_wav_string_index);
    qcc_precache_sound(dog_dpain1_wav_string_index);
    qcc_precache_sound(dog_dsight_wav_string_index);
    qcc_precache_sound(dog_idle_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_dog_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-32.0000f, -32.0000f, -24.0000f}}, (vector) {{32.0000f, 32.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 25);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_run1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_die));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_atta1));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_dog_leap1));
    qcc_walkmonster_start();
//File: zombie.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

ZOMBIE

==============================================================================
*/}
const float qcc_SPAWN_CRUCIFIED = 1//=============================================================================
;
void qcc_zombie_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand2));
    qcc_ai_stand();
}
void qcc_zombie_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand3));
    qcc_ai_stand();
}
void qcc_zombie_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand4));
    qcc_ai_stand();
}
void qcc_zombie_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand5));
    qcc_ai_stand();
}
void qcc_zombie_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand6));
    qcc_ai_stand();
}
void qcc_zombie_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand7));
    qcc_ai_stand();
}
void qcc_zombie_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand8));
    qcc_ai_stand();
}
void qcc_zombie_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand9));
    qcc_ai_stand();
}
void qcc_zombie_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand10));
    qcc_ai_stand();
}
void qcc_zombie_stand10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand11));
    qcc_ai_stand();
}
void qcc_zombie_stand11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand12));
    qcc_ai_stand();
}
void qcc_zombie_stand12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand13));
    qcc_ai_stand();
}
void qcc_zombie_stand13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand14));
    qcc_ai_stand();
}
void qcc_zombie_stand14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand15));
    qcc_ai_stand();
}
void qcc_zombie_stand15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand1));
    qcc_ai_stand();
}
void qcc_zombie_cruc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 192); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc2));
    if (qcc_random() < 0.1f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_idle_w2_wav_string_index, 1.00000f, qcc_ATTN_STATIC);
}
void qcc_zombie_cruc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 193); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc3));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
}
void qcc_zombie_cruc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 194); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc4));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
}
void qcc_zombie_cruc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 195); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc5));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
}
void qcc_zombie_cruc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 196); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc6));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
}
void qcc_zombie_cruc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 197); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_cruc1));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
}
void qcc_zombie_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk2));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk3));
    qcc_ai_walk(2.00000f);
}
void qcc_zombie_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk4));
    qcc_ai_walk(3.00000f);
}
void qcc_zombie_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk5));
    qcc_ai_walk(2.00000f);
}
void qcc_zombie_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk6));
    qcc_ai_walk(1.00000f);
}
void qcc_zombie_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk7));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk8));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk9));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk10));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk11));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk12));
    qcc_ai_walk(2.00000f);
}
void qcc_zombie_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk13));
    qcc_ai_walk(2.00000f);
}
void qcc_zombie_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk14));
    qcc_ai_walk(1.00000f);
}
void qcc_zombie_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk15));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk16));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk17));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk18));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk19));
    qcc_ai_walk(0.000000f);
}
void qcc_zombie_walk19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk1));
    qcc_ai_walk(0.000000f);
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
}
void qcc_zombie_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run2));
    qcc_ai_run(1.00000f);
    set_qcc_inpain(PROG_TO_EDICT(progs.qcc_self), 0);
}
void qcc_zombie_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run3));
    qcc_ai_run(1.00000f);
}
void qcc_zombie_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run4));
    qcc_ai_run(0.000000f);
}
void qcc_zombie_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run5));
    qcc_ai_run(1.00000f);
}
void qcc_zombie_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run6));
    qcc_ai_run(2.00000f);
}
void qcc_zombie_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run7));
    qcc_ai_run(3.00000f);
}
void qcc_zombie_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run8));
    qcc_ai_run(4.00000f);
}
void qcc_zombie_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run9));
    qcc_ai_run(4.00000f);
}
void qcc_zombie_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run10));
    qcc_ai_run(2.00000f);
}
void qcc_zombie_run10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run11));
    qcc_ai_run(0.000000f);
}
void qcc_zombie_run11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run12));
    qcc_ai_run(0.000000f);
}
void qcc_zombie_run12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run13));
    qcc_ai_run(0.000000f);
}
void qcc_zombie_run13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run14));
    qcc_ai_run(2.00000f);
}
void qcc_zombie_run14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run15));
    qcc_ai_run(4.00000f);
}
void qcc_zombie_run15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run16));
    qcc_ai_run(6.00000f);
}
void qcc_zombie_run16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run17));
    qcc_ai_run(7.00000f);
}
void qcc_zombie_run17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run18));
    qcc_ai_run(3.00000f);
}
void qcc_zombie_run18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
    qcc_ai_run(8.00000f);
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    if (qcc_random() > 0.8f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_idle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
/*
=============================================================================

ATTACKS

=============================================================================
*/}
void qcc_ZombieGrenadeTouch(void)
{
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other)))
    {
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 10.0000f);
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, zombie_z_hit_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, zombie_z_miss_wav_string_index, 1.00000f, qcc_ATTN_NORM)// bounce sound
;
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Remove));
/*
================
ZombieFireGrenade
================
*/}
void qcc_ZombieFireGrenade(vector qcc_st)
{
    int qcc_missile,     qcc_mpuff;
    vector qcc_org;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, zombie_z_shot1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_missile = qcc_spawn(qcc_classname_progs_zom_gib_mdl);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_BOUNCE);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_BBOX)// calc org
;
    qcc_org = vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(qcc_st.x, progs.qcc_v_forward)), floatMulVector(qcc_st.y, progs.qcc_v_right)), floatMulVector(( qcc_st.z - 24 ), progs.qcc_v_up))// set missile speed	
;
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), qcc_normalize(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_org)));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(qcc_missile)), 600));
    set_qcc_velocity_z(PROG_TO_EDICT(qcc_missile), 200);
    set_qcc_avelocity(PROG_TO_EDICT(qcc_missile), (vector)  {{3000.00f, 1000.00f, 2000.00f}});
    set_qcc_touch(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_ZombieGrenadeTouch))// set missile duration
;
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), progs.qcc_time + 2.5f);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_SUB_Remove));
    qcc_setmodel(qcc_missile, qcc_classname_progs_zom_gib_mdl);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(qcc_missile, qcc_org);
}
void qcc_zombie_atta1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta2));
    qcc_ai_face();
}
void qcc_zombie_atta2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta3));
    qcc_ai_face();
}
void qcc_zombie_atta3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta4));
    qcc_ai_face();
}
void qcc_zombie_atta4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta5));
    qcc_ai_face();
}
void qcc_zombie_atta5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta6));
    qcc_ai_face();
}
void qcc_zombie_atta6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta7));
    qcc_ai_face();
}
void qcc_zombie_atta7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta8));
    qcc_ai_face();
}
void qcc_zombie_atta8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta9));
    qcc_ai_face();
}
void qcc_zombie_atta9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta10));
    qcc_ai_face();
}
void qcc_zombie_atta10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta11));
    qcc_ai_face();
}
void qcc_zombie_atta11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta12));
    qcc_ai_face();
}
void qcc_zombie_atta12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_atta13));
    qcc_ai_face();
}
void qcc_zombie_atta13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
    qcc_ai_face();
    qcc_ZombieFireGrenade((vector) {{-10.0000f, -22.0000f, 30.0000f}});
}
void qcc_zombie_attb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb2));
    qcc_ai_face();
}
void qcc_zombie_attb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb3));
    qcc_ai_face();
}
void qcc_zombie_attb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb4));
    qcc_ai_face();
}
void qcc_zombie_attb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb5));
    qcc_ai_face();
}
void qcc_zombie_attb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb6));
    qcc_ai_face();
}
void qcc_zombie_attb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb7));
    qcc_ai_face();
}
void qcc_zombie_attb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb8));
    qcc_ai_face();
}
void qcc_zombie_attb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb9));
    qcc_ai_face();
}
void qcc_zombie_attb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb10));
    qcc_ai_face();
}
void qcc_zombie_attb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb11));
    qcc_ai_face();
}
void qcc_zombie_attb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb12));
    qcc_ai_face();
}
void qcc_zombie_attb12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb13));
    qcc_ai_face();
}
void qcc_zombie_attb13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attb14));
    qcc_ai_face();
}
void qcc_zombie_attb14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
    qcc_ai_face();
    qcc_ZombieFireGrenade((vector) {{-10.0000f, -24.0000f, 29.0000f}});
}
void qcc_zombie_attc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc2));
    qcc_ai_face();
}
void qcc_zombie_attc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc3));
    qcc_ai_face();
}
void qcc_zombie_attc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc4));
    qcc_ai_face();
}
void qcc_zombie_attc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc5));
    qcc_ai_face();
}
void qcc_zombie_attc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc6));
    qcc_ai_face();
}
void qcc_zombie_attc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc7));
    qcc_ai_face();
}
void qcc_zombie_attc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc8));
    qcc_ai_face();
}
void qcc_zombie_attc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc9));
    qcc_ai_face();
}
void qcc_zombie_attc9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc10));
    qcc_ai_face();
}
void qcc_zombie_attc10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc11));
    qcc_ai_face();
}
void qcc_zombie_attc11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_attc12));
    qcc_ai_face();
}
void qcc_zombie_attc12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
    qcc_ai_face();
    qcc_ZombieFireGrenade((vector) {{-12.0000f, -19.0000f, 29.0000f}});
}
void qcc_zombie_missile(void)
{
    float qcc_r;
    qcc_r = qcc_random();
    if (qcc_r < 0.3f)
        qcc_zombie_atta1();
    else
        if (qcc_r < 0.6f)
            qcc_zombie_attb1();
        else
            qcc_zombie_attc1();
/*
=============================================================================

PAIN

=============================================================================
*/}
void qcc_zombie_paina1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_pain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_zombie_paina2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina3));
    qcc_ai_painforward(3.00000f);
}
void qcc_zombie_paina3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina4));
    qcc_ai_painforward(1.00000f);
}
void qcc_zombie_paina4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina5));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paina5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina6));
    qcc_ai_pain(3.00000f);
}
void qcc_zombie_paina6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina7));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paina7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina8));
}
void qcc_zombie_paina8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina9));
}
void qcc_zombie_paina9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina10));
}
void qcc_zombie_paina10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina11));
}
void qcc_zombie_paina11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paina12));
}
void qcc_zombie_paina12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
}
void qcc_zombie_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_zombie_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb3));
    qcc_ai_pain(2.00000f);
}
void qcc_zombie_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb4));
    qcc_ai_pain(8.00000f);
}
void qcc_zombie_painb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 106); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb5));
    qcc_ai_pain(6.00000f);
}
void qcc_zombie_painb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 107); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb6));
    qcc_ai_pain(2.00000f);
}
void qcc_zombie_painb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 108); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb7));
}
void qcc_zombie_painb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 109); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb8));
}
void qcc_zombie_painb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 110); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb9));
}
void qcc_zombie_painb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 111); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb10));
    qcc_sound(progs.qcc_self, qcc_CHAN_BODY, zombie_z_fall_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_zombie_painb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 112); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb11));
}
void qcc_zombie_painb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 113); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb12));
}
void qcc_zombie_painb12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 114); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb13));
}
void qcc_zombie_painb13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 115); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb14));
}
void qcc_zombie_painb14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 116); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb15));
}
void qcc_zombie_painb15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 117); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb16));
}
void qcc_zombie_painb16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 118); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb17));
}
void qcc_zombie_painb17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 119); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb18));
}
void qcc_zombie_painb18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 120); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb19));
}
void qcc_zombie_painb19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 121); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb20));
}
void qcc_zombie_painb20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 122); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb21));
}
void qcc_zombie_painb21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 123); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb22));
}
void qcc_zombie_painb22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 124); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb23));
}
void qcc_zombie_painb23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 125); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb24));
}
void qcc_zombie_painb24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 126); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb25));
}
void qcc_zombie_painb25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 127); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb26));
    qcc_ai_painforward(1.00000f);
}
void qcc_zombie_painb26(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 128); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb27));
}
void qcc_zombie_painb27(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 129); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painb28));
}
void qcc_zombie_painb28(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 130); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
}
void qcc_zombie_painc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 131); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_zombie_painc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 132); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc3));
}
void qcc_zombie_painc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 133); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc4));
    qcc_ai_pain(3.00000f);
}
void qcc_zombie_painc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 134); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc5));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_painc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 135); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc6));
}
void qcc_zombie_painc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 136); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc7));
}
void qcc_zombie_painc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 137); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc8));
}
void qcc_zombie_painc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 138); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc9));
}
void qcc_zombie_painc9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 139); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc10));
}
void qcc_zombie_painc10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 140); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc11));
}
void qcc_zombie_painc11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 141); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc12));
    qcc_ai_painforward(1.00000f);
}
void qcc_zombie_painc12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 142); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc13));
    qcc_ai_painforward(1.00000f);
}
void qcc_zombie_painc13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 143); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc14));
}
void qcc_zombie_painc14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 144); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc15));
}
void qcc_zombie_painc15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 145); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc16));
}
void qcc_zombie_painc16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 146); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc17));
}
void qcc_zombie_painc17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 147); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_painc18));
}
void qcc_zombie_painc18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 148); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
}
void qcc_zombie_paind1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 149); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_pain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_zombie_paind2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 150); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind3));
}
void qcc_zombie_paind3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 151); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind4));
}
void qcc_zombie_paind4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 152); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind5));
}
void qcc_zombie_paind5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 153); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind6));
}
void qcc_zombie_paind6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 154); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind7));
}
void qcc_zombie_paind7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 155); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind8));
}
void qcc_zombie_paind8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 156); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind9));
}
void qcc_zombie_paind9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 157); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind10));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paind10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 158); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind11));
}
void qcc_zombie_paind11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 159); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind12));
}
void qcc_zombie_paind12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 160); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paind13));
}
void qcc_zombie_paind13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 161); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
}
void qcc_zombie_paine1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 162); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_pain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 60);
}
void qcc_zombie_paine2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 163); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine3));
    qcc_ai_pain(8.00000f);
}
void qcc_zombie_paine3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 164); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine4));
    qcc_ai_pain(5.00000f);
}
void qcc_zombie_paine4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 165); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine5));
    qcc_ai_pain(3.00000f);
}
void qcc_zombie_paine5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 166); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine6));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paine6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 167); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine7));
    qcc_ai_pain(2.00000f);
}
void qcc_zombie_paine7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 168); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine8));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paine8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 169); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine9));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paine9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 170); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine10));
    qcc_ai_pain(2.00000f);
}
void qcc_zombie_paine10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 171); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine11));
    qcc_sound(progs.qcc_self, qcc_CHAN_BODY, zombie_z_fall_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_zombie_paine11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 172); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine12));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), get_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self)) + 5);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 60);
}
void qcc_zombie_paine12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 173); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine13));
// see if ok to stand up
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 60);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    if (!qcc_walkmove(0.000000f, 0.000000f))
    {
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine11));
        set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
        return;
    }
}
void qcc_zombie_paine13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 174); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine14));
}
void qcc_zombie_paine14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 175); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine15));
}
void qcc_zombie_paine15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 176); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine16));
}
void qcc_zombie_paine16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 177); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine17));
}
void qcc_zombie_paine17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 178); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine18));
}
void qcc_zombie_paine18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 179); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine19));
}
void qcc_zombie_paine19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 180); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine20));
}
void qcc_zombie_paine20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 181); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine21));
}
void qcc_zombie_paine21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 182); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine22));
}
void qcc_zombie_paine22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 183); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine23));
}
void qcc_zombie_paine23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 184); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine24));
}
void qcc_zombie_paine24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 185); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine25));
}
void qcc_zombie_paine25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 186); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine26));
    qcc_ai_painforward(5.00000f);
}
void qcc_zombie_paine26(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 187); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine27));
    qcc_ai_painforward(3.00000f);
}
void qcc_zombie_paine27(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 188); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine28));
    qcc_ai_painforward(1.00000f);
}
void qcc_zombie_paine28(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 189); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine29));
    qcc_ai_pain(1.00000f);
}
void qcc_zombie_paine29(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 190); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_paine30));
}
void qcc_zombie_paine30(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 191); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
}
void qcc_zombie_die(void)
{
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, zombie_z_gib_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ThrowHead(progs_h_zombie_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
    qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
/*
=================
zombie_pain

Zombies can only be killed (gibbed) by doing 60 hit points of damage
in a single frame (rockets, grenades, quad shotgun, quad nailgun).

A hit of 25 points or more (super shotgun, quad nailgun) will allways put it
down to the ground.

A hit of from 10 to 40 points in one frame will cause it to go down if it
has been twice in two seconds, otherwise it goes into one of the four
fast pain frames.

A hit of less than 10 points of damage (winged by a shotgun) will be ignored.

FIXME: don't use pain_finished because of nightmare hack
=================
*/}
void qcc_zombie_pain(int qcc_attacker, float qcc_take)
{
    float qcc_r;
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 60)// allways reset health
;
    if (qcc_take < 9)
// totally ignore
        return;
    if (get_qcc_inpain(PROG_TO_EDICT(progs.qcc_self)) == 2)
// down on ground, so don't reset any counters
// go down immediately if a big enough hit
        return;
    if (qcc_take >= 25)
    {
        set_qcc_inpain(PROG_TO_EDICT(progs.qcc_self), 2);
        qcc_zombie_paine1();
        return;
    }
    if (get_qcc_inpain(PROG_TO_EDICT(progs.qcc_self)))
// if hit again in next gre seconds while not in pain frames, definately drop
    {
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 3);
// currently going through an animation, don't change
        return;
    }
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
// hit again, so drop down
    {
        set_qcc_inpain(PROG_TO_EDICT(progs.qcc_self), 2);
        qcc_zombie_paine1();
        return;
// gp into one of the fast pain animations	
    }
    set_qcc_inpain(PROG_TO_EDICT(progs.qcc_self), 1);
    qcc_r = qcc_random();
    if (qcc_r < 0.25f)
        qcc_zombie_paina1();
    else
        if (qcc_r < 0.5f)
            qcc_zombie_painb1();
        else
            if (qcc_r < 0.75f)
                qcc_zombie_painc1();
            else
                qcc_zombie_paind1();
//============================================================================
/*QUAKED monster_zombie (1 0 0) (-16 -16 -24) (16 16 32) Crucified ambush

If crucified, stick the bounding box 12 pixels back into a wall to look right.
*/}
void qcc_monster_zombie(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_zombie_mdl_string_index);
    qcc_precache_model(progs_h_zombie_mdl_string_index);
    qcc_precache_model(qcc_classname_progs_zom_gib_mdl);
    qcc_precache_sound(zombie_z_idle_wav_string_index);
    qcc_precache_sound(zombie_z_idle1_wav_string_index);
    qcc_precache_sound(zombie_z_shot1_wav_string_index);
    qcc_precache_sound(zombie_z_gib_wav_string_index);
    qcc_precache_sound(zombie_z_pain_wav_string_index);
    qcc_precache_sound(zombie_z_pain1_wav_string_index);
    qcc_precache_sound(zombie_z_fall_wav_string_index);
    qcc_precache_sound(zombie_z_miss_wav_string_index);
    qcc_precache_sound(zombie_z_hit_wav_string_index);
    qcc_precache_sound(zombie_idle_w2_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_zombie_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 60);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_run1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_die));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_zombie_missile));
    if ((((int) get_qcc_spawnflags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_SPAWN_CRUCIFIED)))
    {
        set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_NONE);
        qcc_zombie_cruc1();
    }
    else
        qcc_walkmonster_start();
//File: boss.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

BOSS-ONE

==============================================================================
*/}
void qcc_boss_missile(vector );
void qcc_boss_face(void)
{
// go for another player if multi player
    if (((int) get_qcc_health(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))) <= 0) || ((int) qcc_random() < 0.02f))
    {
        set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_find(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), offsetof (big_entvars_t, qcc_classname), qcc_classname_player));
        if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
            set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), qcc_find(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), offsetof (big_entvars_t, qcc_classname), qcc_classname_player));
    }
    qcc_ai_face();
}
void qcc_boss_rise1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise2));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, boss1_out1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_boss_rise2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise3));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, boss1_sight1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_boss_rise3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise4));
}
void qcc_boss_rise4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise5));
}
void qcc_boss_rise5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise6));
}
void qcc_boss_rise6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise7));
}
void qcc_boss_rise7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise8));
}
void qcc_boss_rise8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise9));
}
void qcc_boss_rise9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise10));
}
void qcc_boss_rise10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise11));
}
void qcc_boss_rise11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise12));
}
void qcc_boss_rise12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise13));
}
void qcc_boss_rise13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise14));
}
void qcc_boss_rise14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise15));
}
void qcc_boss_rise15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise16));
}
void qcc_boss_rise16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_rise17));
}
void qcc_boss_rise17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile1));
}
void qcc_boss_idle1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle2));
// look for other players
}
void qcc_boss_idle2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle3));
    qcc_boss_face();
}
void qcc_boss_idle3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle4));
    qcc_boss_face();
}
void qcc_boss_idle4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle5));
    qcc_boss_face();
}
void qcc_boss_idle5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle6));
    qcc_boss_face();
}
void qcc_boss_idle6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle7));
    qcc_boss_face();
}
void qcc_boss_idle7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle8));
    qcc_boss_face();
}
void qcc_boss_idle8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle9));
    qcc_boss_face();
}
void qcc_boss_idle9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle10));
    qcc_boss_face();
}
void qcc_boss_idle10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle11));
    qcc_boss_face();
}
void qcc_boss_idle11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle12));
    qcc_boss_face();
}
void qcc_boss_idle12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle13));
    qcc_boss_face();
}
void qcc_boss_idle13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle14));
    qcc_boss_face();
}
void qcc_boss_idle14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle15));
    qcc_boss_face();
}
void qcc_boss_idle15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle16));
    qcc_boss_face();
}
void qcc_boss_idle16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle17));
    qcc_boss_face();
}
void qcc_boss_idle17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle18));
    qcc_boss_face();
}
void qcc_boss_idle18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle19));
    qcc_boss_face();
}
void qcc_boss_idle19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle20));
    qcc_boss_face();
}
void qcc_boss_idle20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle21));
    qcc_boss_face();
}
void qcc_boss_idle21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle22));
    qcc_boss_face();
}
void qcc_boss_idle22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle23));
    qcc_boss_face();
}
void qcc_boss_idle23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle24));
    qcc_boss_face();
}
void qcc_boss_idle24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle25));
    qcc_boss_face();
}
void qcc_boss_idle25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle26));
    qcc_boss_face();
}
void qcc_boss_idle26(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle27));
    qcc_boss_face();
}
void qcc_boss_idle27(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle28));
    qcc_boss_face();
}
void qcc_boss_idle28(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle29));
    qcc_boss_face();
}
void qcc_boss_idle29(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle30));
    qcc_boss_face();
}
void qcc_boss_idle30(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle31));
    qcc_boss_face();
}
void qcc_boss_idle31(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_idle1));
    qcc_boss_face();
}
void qcc_boss_missile1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile2));
    qcc_boss_face();
}
void qcc_boss_missile2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile3));
    qcc_boss_face();
}
void qcc_boss_missile3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile4));
    qcc_boss_face();
}
void qcc_boss_missile4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile5));
    qcc_boss_face();
}
void qcc_boss_missile5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile6));
    qcc_boss_face();
}
void qcc_boss_missile6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile7));
    qcc_boss_face();
}
void qcc_boss_missile7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile8));
    qcc_boss_face();
}
void qcc_boss_missile8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile9));
    qcc_boss_face();
}
void qcc_boss_missile9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile10));
    qcc_boss_missile((vector) {{100.000f, 100.000f, 200.000f}});
}
void qcc_boss_missile10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile11));
    qcc_boss_face();
}
void qcc_boss_missile11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile12));
    qcc_boss_face();
}
void qcc_boss_missile12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile13));
    qcc_boss_face();
}
void qcc_boss_missile13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile14));
    qcc_boss_face();
}
void qcc_boss_missile14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile15));
    qcc_boss_face();
}
void qcc_boss_missile15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile16));
    qcc_boss_face();
}
void qcc_boss_missile16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile17));
    qcc_boss_face();
}
void qcc_boss_missile17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile18));
    qcc_boss_face();
}
void qcc_boss_missile18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile19));
    qcc_boss_face();
}
void qcc_boss_missile19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile20));
    qcc_boss_face();
}
void qcc_boss_missile20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile21));
    qcc_boss_missile((vector) {{100.000f, -100.000f, 200.000f}});
}
void qcc_boss_missile21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile22));
    qcc_boss_face();
}
void qcc_boss_missile22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile23));
    qcc_boss_face();
}
void qcc_boss_missile23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile1));
    qcc_boss_face();
}
void qcc_boss_shocka1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka2));
}
void qcc_boss_shocka2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka3));
}
void qcc_boss_shocka3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka4));
}
void qcc_boss_shocka4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka5));
}
void qcc_boss_shocka5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka6));
}
void qcc_boss_shocka6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka7));
}
void qcc_boss_shocka7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka8));
}
void qcc_boss_shocka8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka9));
}
void qcc_boss_shocka9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shocka10));
}
void qcc_boss_shocka10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile1));
}
void qcc_boss_shockb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb2));
}
void qcc_boss_shockb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb3));
}
void qcc_boss_shockb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb4));
}
void qcc_boss_shockb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb5));
}
void qcc_boss_shockb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb6));
}
void qcc_boss_shockb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb7));
}
void qcc_boss_shockb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb8));
}
void qcc_boss_shockb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb9));
}
void qcc_boss_shockb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockb10));
}
void qcc_boss_shockb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_missile1));
}
void qcc_boss_shockc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc2));
}
void qcc_boss_shockc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc3));
}
void qcc_boss_shockc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc4));
}
void qcc_boss_shockc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc5));
}
void qcc_boss_shockc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc6));
}
void qcc_boss_shockc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc7));
}
void qcc_boss_shockc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc8));
}
void qcc_boss_shockc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc9));
}
void qcc_boss_shockc9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_shockc10));
}
void qcc_boss_shockc10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death1));
}
void qcc_boss_death1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, boss1_death_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_boss_death2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death3));
}
void qcc_boss_death3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death4));
}
void qcc_boss_death4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death5));
}
void qcc_boss_death5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death6));
}
void qcc_boss_death6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death7));
}
void qcc_boss_death7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death8));
}
void qcc_boss_death8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death9));
}
void qcc_boss_death9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death10));
    qcc_sound(progs.qcc_self, qcc_CHAN_BODY, boss1_out1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_LAVASPLASH);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
}
void qcc_boss_death10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_death10));
    progs.qcc_killed_monsters = progs.qcc_killed_monsters + 1;
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_KILLEDMONSTER)// FIXME: reliable broadcast
;
    qcc_SUB_UseTargets();
    qcc_remove(progs.qcc_self);
}
void qcc_boss_missile(vector qcc_p)
{
    vector qcc_offang;
    vector qcc_org,     qcc_vec,     qcc_d;
    float qcc_t;
    qcc_offang = qcc_vectoangles(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_makevectors(qcc_offang);
    qcc_org = vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(qcc_p.x, progs.qcc_v_forward)), floatMulVector(qcc_p.y, progs.qcc_v_right)), floatMulVector(qcc_p.z, (vector)  {{0.000000f, 0.000000f, 1.00000f}}))// lead the player on hard mode
;
    if (progs.qcc_skill > 1)
    {
        qcc_t = qcc_vlen(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), qcc_org)) / 300;
        qcc_vec = get_qcc_velocity(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))));
        qcc_vec.z = 0;
        qcc_d = vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), floatMulVector(qcc_t, qcc_vec));
    }
    else
    {
        qcc_d = get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))));
    }
    qcc_vec = qcc_normalize(vectorSub(qcc_d, qcc_org));
    qcc_launch_spike(qcc_org, qcc_vec);
    qcc_setmodel(progs.qcc_newmis, progs_lavaball_mdl_string_index);
    set_qcc_avelocity(PROG_TO_EDICT(progs.qcc_newmis), (vector)  {{200.000f, 100.000f, 300.000f}});
    qcc_setsize(progs.qcc_newmis, qcc_VEC_ORIGIN, qcc_VEC_ORIGIN);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(qcc_vec, 300));
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_T_MissileTouch))// rocket explosion
;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, boss1_throw_wav_string_index, 1.00000f, qcc_ATTN_NORM)// check for dead enemy
;
    if (get_qcc_health(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))) <= 0)
        qcc_boss_idle1();
}
void qcc_boss_awake(void)
{
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
    qcc_setmodel(progs.qcc_self, progs_boss_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-128.000f, -128.000f, -24.0000f}}, (vector) {{128.000f, 128.000f, 256.000f}});
    if (progs.qcc_skill == 0)
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 1);
    else
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 3);
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_LAVASPLASH);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    set_qcc_yaw_speed(PROG_TO_EDICT(progs.qcc_self), 20);
    qcc_boss_rise1();
/*QUAKED monster_boss (1 0 0) (-128 -128 -24) (128 128 256)
*/}
void qcc_monster_boss(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model(progs_boss_mdl_string_index);
    qcc_precache_model(progs_lavaball_mdl_string_index);
    qcc_precache_sound(weapons_rocket1i_wav_string_index);
    qcc_precache_sound(boss1_out1_wav_string_index);
    qcc_precache_sound(boss1_sight1_wav_string_index);
    qcc_precache_sound(misc_power_wav_string_index);
    qcc_precache_sound(boss1_throw_wav_string_index);
    qcc_precache_sound(boss1_pain_wav_string_index);
    qcc_precache_sound(boss1_death_wav_string_index);
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_boss_awake));
//===========================================================================
}
;
// next-hack added declaration because setting self.think = lightning_fire; will generate bad code...
;
void qcc_lightning_fire(void);
void qcc_lightning_fire(void)
{
    vector qcc_p1,     qcc_p2;
    if (progs.qcc_time >= progs.qcc_lightning_end)
// done here, put the terminals back up
    {
        progs.qcc_self = progs.qcc_le1;
        qcc_door_go_down();
        progs.qcc_self = progs.qcc_le2;
        qcc_door_go_down();
        return;
    }
    qcc_p1 = vectorMulFloat(( vectorAdd(get_qcc_mins(PROG_TO_EDICT(progs.qcc_le1)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_le1))) ), 0.5f);
    qcc_p1.z = get_qcc_absmin(PROG_TO_EDICT(progs.qcc_le1)).z - 16;
    qcc_p2 = vectorMulFloat(( vectorAdd(get_qcc_mins(PROG_TO_EDICT(progs.qcc_le2)), get_qcc_maxs(PROG_TO_EDICT(progs.qcc_le2))) ), 0.5f);
    qcc_p2.z = get_qcc_absmin(PROG_TO_EDICT(progs.qcc_le2)).z - 16// compensate for length of bolt
;
    qcc_p2 = vectorSub(qcc_p2, vectorMulFloat(qcc_normalize(vectorSub(qcc_p2, qcc_p1)), 100));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_lightning_fire));
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_ALL, qcc_TE_LIGHTNING3);
    qcc_WriteEntity(qcc_MSG_ALL, progs.qcc_world);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p1.x);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p1.y);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p1.z);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p2.x);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p2.y);
    qcc_WriteCoord(qcc_MSG_ALL, qcc_p2.z);
}
void qcc_lightning_use(void)
{
    if (progs.qcc_lightning_end >= progs.qcc_time + 1)
        return;
    progs.qcc_le1 = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_target), lightning_string_index);
    progs.qcc_le2 = qcc_find(progs.qcc_le1, offsetof (big_entvars_t, qcc_target), lightning_string_index);
    if (((int) (!progs.qcc_le1)) || ((int) (!progs.qcc_le2)))
    {
        qcc_dprint(missing_lightning_targets_n__string_index);
        return;
    }
    if (((int) ((int) ( ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_le1)) != qcc_STATE_TOP) && ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_le1)) != qcc_STATE_BOTTOM) )) || ((int) ( ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_le2)) != qcc_STATE_TOP) && ((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_le2)) != qcc_STATE_BOTTOM) ))) || ((int) ( get_qcc_state(PROG_TO_EDICT(progs.qcc_le1)) != get_qcc_state(PROG_TO_EDICT(progs.qcc_le2)) )))
//		dprint ("not aligned\n");
    {
        return;
// don't let the electrodes go back up until the bolt is done
    }
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_le1), -1);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_le2), -1);
    progs.qcc_lightning_end = progs.qcc_time + 1;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, misc_power_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_lightning_fire()// advance the boss pain if down
;
    progs.qcc_self = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_monster_boss);
    if ((!progs.qcc_self))
        return;
    set_qcc_enemy(PROG_TO_EDICT(progs.qcc_self), progs.qcc_activator);
    if (((int) get_qcc_state(PROG_TO_EDICT(progs.qcc_le1)) == qcc_STATE_TOP) && ((int) get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) > 0))
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, boss1_pain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        set_qcc_health(PROG_TO_EDICT(progs.qcc_self), get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) - 1);
        if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) >= 2)
            qcc_boss_shocka1();
        else
            if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) == 1)
                qcc_boss_shockb1();
            else
                if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) == 0)
                    qcc_boss_shockc1();
    }
/*QUAKED event_lightning (0 1 1) (-16 -16 -16) (16 16 16)
Just for boss level.
*/}
void qcc_event_lightning(void)
{
    set_qcc_use(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_lightning_use));
//File: tarbaby.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

BLOB

==============================================================================
*/}
void qcc_tbaby_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_stand1));
    qcc_ai_stand();
}
void qcc_tbaby_hang1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_hang1));
    qcc_ai_stand();
}
void qcc_tbaby_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk2));
    qcc_ai_turn();
}
void qcc_tbaby_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk3));
    qcc_ai_turn();
}
void qcc_tbaby_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk4));
    qcc_ai_turn();
}
void qcc_tbaby_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk5));
    qcc_ai_turn();
}
void qcc_tbaby_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk6));
    qcc_ai_turn();
}
void qcc_tbaby_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk7));
    qcc_ai_turn();
}
void qcc_tbaby_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk8));
    qcc_ai_turn();
}
void qcc_tbaby_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk9));
    qcc_ai_turn();
}
void qcc_tbaby_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk10));
    qcc_ai_turn();
}
void qcc_tbaby_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk11));
    qcc_ai_turn();
}
void qcc_tbaby_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk12));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk13));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk14));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk15));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk16));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk17));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk18));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk19));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk20));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk21));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk22));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk23));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk24));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk25));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_walk25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk1));
    qcc_ai_walk(2.00000f);
}
void qcc_tbaby_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run2));
    qcc_ai_face();
}
void qcc_tbaby_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run3));
    qcc_ai_face();
}
void qcc_tbaby_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run4));
    qcc_ai_face();
}
void qcc_tbaby_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run5));
    qcc_ai_face();
}
void qcc_tbaby_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run6));
    qcc_ai_face();
}
void qcc_tbaby_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run7));
    qcc_ai_face();
}
void qcc_tbaby_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run8));
    qcc_ai_face();
}
void qcc_tbaby_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run9));
    qcc_ai_face();
}
void qcc_tbaby_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run10));
    qcc_ai_face();
}
void qcc_tbaby_run10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run11));
    qcc_ai_face();
}
void qcc_tbaby_run11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run12));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run13));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run14));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run15));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run16));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run17));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run18));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run19));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run20));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run21));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run22));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run23));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run24));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run25));
    qcc_ai_run(2.00000f);
}
void qcc_tbaby_run25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run1));
    qcc_ai_run(2.00000f);
//============================================================================
}
void qcc_tbaby_jump1(void);
void qcc_Tar_JumpTouch(void)
{
    float qcc_ldmg;
    if (((int) get_qcc_takedamage(PROG_TO_EDICT(progs.qcc_other))) && ((int) (!areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), get_qcc_classname(PROG_TO_EDICT(progs.qcc_self))))))
    {
        if (qcc_vlen(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self))) > 400)
        {
            qcc_ldmg = 10 + 10 * qcc_random();
            qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, qcc_ldmg);
            qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, blob_hit1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        }
    }
    else
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, blob_land1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (!qcc_checkbottom(progs.qcc_self))
    {
        if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
// jump randomly to not get hung up
//dprint ("popjump\n");
        {
            set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
            set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run1));
            set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
            set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f)//			self.velocity_x = (random() - 0.5) * 600;
//			self.velocity_y = (random() - 0.5) * 600;
//			self.velocity_z = 200;
//			self.flags = self.flags - FL_ONGROUND;
;
        }
// not on ground yet
        return;
    }
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump1));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
}
void qcc_tbaby_jump5(void);
void qcc_tbaby_fly1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_fly2));
}
void qcc_tbaby_fly2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_fly3));
}
void qcc_tbaby_fly3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_fly4));
}
void qcc_tbaby_fly4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_fly1));
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) == 4)
//dprint ("spawn hop\n");
    {
        qcc_tbaby_jump5();
    }
}
void qcc_tbaby_jump1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump2));
    qcc_ai_face();
}
void qcc_tbaby_jump2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump3));
    qcc_ai_face();
}
void qcc_tbaby_jump3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump4));
    qcc_ai_face();
}
void qcc_tbaby_jump4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump5));
    qcc_ai_face();
}
void qcc_tbaby_jump5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump6));
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_BOUNCE);
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_Tar_JumpTouch));
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z + 1);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorAdd(vectorMulFloat(progs.qcc_v_forward, 600), (vector)  {{0.000000f, 0.000000f, 200.000f}}));
    set_qcc_velocity_z(PROG_TO_EDICT(progs.qcc_self), get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)).z + qcc_random() * 150);
    if ((((int) get_qcc_flags(PROG_TO_EDICT(progs.qcc_self))) & ((int) qcc_FL_ONGROUND)))
        set_qcc_flags(PROG_TO_EDICT(progs.qcc_self), get_qcc_flags(PROG_TO_EDICT(progs.qcc_self)) - qcc_FL_ONGROUND);
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), 0);
}
void qcc_tbaby_jump6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_fly1));
//=============================================================================
}
void qcc_tbaby_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_die2));
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_NO);
}
void qcc_tbaby_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run1));
    qcc_T_RadiusDamage(progs.qcc_self, progs.qcc_self, 120.000f, progs.qcc_world);
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, blob_death1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_origin(PROG_TO_EDICT(progs.qcc_self), vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(8, qcc_normalize(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self))))));
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_TAREXPLOSION);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    qcc_BecomeExplosion();
//=============================================================================
/*QUAKED monster_tarbaby (1 0 0) (-16 -16 -24) (16 16 24) Ambush
*/}
void qcc_monster_tarbaby(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_tarbaby_mdl_string_index);
    qcc_precache_sound2(blob_death1_wav_string_index);
    qcc_precache_sound2(blob_hit1_wav_string_index);
    qcc_precache_sound2(blob_land1_wav_string_index);
    qcc_precache_sound2(blob_sight1_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_tarbaby_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 80);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_run1));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump1));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_jump1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_tbaby_die1));
    qcc_walkmonster_start();
//File: hknight.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

KNIGHT

==============================================================================
*/}
void qcc_hknight_char_a1(void);
void qcc_hknight_run1(void);
void qcc_hk_idle_sound(void);
void qcc_hknight_shot(float qcc_offset)
{
    vector qcc_offang;
    vector qcc_org,     qcc_vec;
    qcc_offang = qcc_vectoangles(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_offang.y = qcc_offang.y + qcc_offset * 6;
    qcc_makevectors(qcc_offang);
    qcc_org = vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_mins(PROG_TO_EDICT(progs.qcc_self))), vectorMulFloat(get_qcc_size(PROG_TO_EDICT(progs.qcc_self)), 0.5f)), vectorMulFloat(progs.qcc_v_forward, 20))// set missile speed
;
    qcc_vec = qcc_normalize(progs.qcc_v_forward);
    qcc_vec.z = 0 - qcc_vec.z + ( qcc_random() - 0.5f ) * 0.1f;
    qcc_launch_spike(qcc_org, qcc_vec);
    set_qcc_classname(PROG_TO_EDICT(progs.qcc_newmis), qcc_classname_knightspike);
    qcc_setmodel(progs.qcc_newmis, progs_k_spike_mdl_string_index);
    qcc_setsize(progs.qcc_newmis, qcc_VEC_ORIGIN, qcc_VEC_ORIGIN);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(qcc_vec, 300));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, hknight_attack1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_CheckForCharge(void)
{
// check for mad charge
    if (!progs.qcc_enemy_vis)
        return;
    if (progs.qcc_time < get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
        return;
    if (qcc_fabs(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z - get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))).z) > 20)
// too much height change
        return;
    if (qcc_vlen(vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))))) < 80)
// use regular attack
// charge		
        return;
    qcc_SUB_AttackFinished(2.00000f);
    qcc_hknight_char_a1();
}
void qcc_CheckContinueCharge(void)
{
    if (progs.qcc_time > get_qcc_attack_finished(PROG_TO_EDICT(progs.qcc_self)))
    {
        qcc_SUB_AttackFinished(3.00000f);
        qcc_hknight_run1();
// done charging
        return;
    }
    if (qcc_random() > 0.5f)
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, knight_sword2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    else
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, knight_sword1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
//===========================================================================
}
void qcc_hknight_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand2));
    qcc_ai_stand();
}
void qcc_hknight_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand3));
    qcc_ai_stand();
}
void qcc_hknight_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand4));
    qcc_ai_stand();
}
void qcc_hknight_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand5));
    qcc_ai_stand();
}
void qcc_hknight_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand6));
    qcc_ai_stand();
}
void qcc_hknight_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand7));
    qcc_ai_stand();
}
void qcc_hknight_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand8));
    qcc_ai_stand();
}
void qcc_hknight_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand9));
    qcc_ai_stand();
}
void qcc_hknight_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand1));
    qcc_ai_stand();
//===========================================================================
}
void qcc_hknight_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk2));
    qcc_hk_idle_sound();
    qcc_ai_walk(2.00000f);
}
void qcc_hknight_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk3));
    qcc_ai_walk(5.00000f);
}
void qcc_hknight_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk4));
    qcc_ai_walk(5.00000f);
}
void qcc_hknight_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk5));
    qcc_ai_walk(4.00000f);
}
void qcc_hknight_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk6));
    qcc_ai_walk(4.00000f);
}
void qcc_hknight_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk7));
    qcc_ai_walk(2.00000f);
}
void qcc_hknight_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk8));
    qcc_ai_walk(2.00000f);
}
void qcc_hknight_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk9));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk10));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk11));
    qcc_ai_walk(4.00000f);
}
void qcc_hknight_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk12));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk13));
    qcc_ai_walk(4.00000f);
}
void qcc_hknight_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk14));
    qcc_ai_walk(6.00000f);
}
void qcc_hknight_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk15));
    qcc_ai_walk(2.00000f);
}
void qcc_hknight_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk16));
    qcc_ai_walk(2.00000f);
}
void qcc_hknight_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk17));
    qcc_ai_walk(4.00000f);
}
void qcc_hknight_walk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk18));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk19));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk20));
    qcc_ai_walk(3.00000f);
}
void qcc_hknight_walk20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk1));
    qcc_ai_walk(2.00000f);
//===========================================================================
}
void qcc_hknight_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run2));
    qcc_hk_idle_sound();
    qcc_ai_run(20.0000f);
    qcc_CheckForCharge();
}
void qcc_hknight_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run3));
    qcc_ai_run(25.0000f);
}
void qcc_hknight_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run4));
    qcc_ai_run(18.0000f);
}
void qcc_hknight_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run5));
    qcc_ai_run(16.0000f);
}
void qcc_hknight_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run6));
    qcc_ai_run(14.0000f);
}
void qcc_hknight_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run7));
    qcc_ai_run(25.0000f);
}
void qcc_hknight_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run8));
    qcc_ai_run(21.0000f);
}
void qcc_hknight_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_run(13.0000f);
//============================================================================
}
void qcc_hknight_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_pain2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, hknight_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_hknight_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_pain3));
}
void qcc_hknight_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_pain4));
}
void qcc_hknight_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_pain5));
}
void qcc_hknight_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
//============================================================================
}
void qcc_hknight_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die2));
    qcc_ai_forward(10.0000f);
}
void qcc_hknight_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die3));
    qcc_ai_forward(8.00000f);
}
void qcc_hknight_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_ai_forward(7.00000f);
}
void qcc_hknight_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die5));
}
void qcc_hknight_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die6));
}
void qcc_hknight_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die7));
}
void qcc_hknight_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die8));
}
void qcc_hknight_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die9));
    qcc_ai_forward(10.0000f);
}
void qcc_hknight_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die10));
    qcc_ai_forward(11.0000f);
}
void qcc_hknight_die10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die11));
}
void qcc_hknight_die11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die12));
}
void qcc_hknight_die12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die12));
}
void qcc_hknight_dieb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb2));
}
void qcc_hknight_dieb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb3));
}
void qcc_hknight_dieb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_hknight_dieb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb5));
}
void qcc_hknight_dieb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb6));
}
void qcc_hknight_dieb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb7));
}
void qcc_hknight_dieb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb8));
}
void qcc_hknight_dieb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb9));
}
void qcc_hknight_dieb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_dieb9));
}
void qcc_hknight_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -40)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_hellkn_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, hknight_death1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() > 0.5f)
        qcc_hknight_die1();
    else
        qcc_hknight_dieb1();
//============================================================================
}
void qcc_hknight_magica1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica2));
    qcc_ai_face();
}
void qcc_hknight_magica2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica3));
    qcc_ai_face();
}
void qcc_hknight_magica3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica4));
    qcc_ai_face();
}
void qcc_hknight_magica4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica5));
    qcc_ai_face();
}
void qcc_hknight_magica5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica6));
    qcc_ai_face();
}
void qcc_hknight_magica6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica7));
    qcc_ai_face();
}
void qcc_hknight_magica7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica8));
    qcc_hknight_shot(-2.00000f);
}
void qcc_hknight_magica8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica9));
    qcc_hknight_shot(-1.00000f);
}
void qcc_hknight_magica9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica10));
    qcc_hknight_shot(0.000000f);
}
void qcc_hknight_magica10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica11));
    qcc_hknight_shot(1.00000f);
}
void qcc_hknight_magica11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica12));
    qcc_hknight_shot(2.00000f);
}
void qcc_hknight_magica12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica13));
    qcc_hknight_shot(3.00000f);
}
void qcc_hknight_magica13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magica14));
    qcc_ai_face();
}
void qcc_hknight_magica14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_face();
//============================================================================
}
void qcc_hknight_magicb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb2));
    qcc_ai_face();
}
void qcc_hknight_magicb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb3));
    qcc_ai_face();
}
void qcc_hknight_magicb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb4));
    qcc_ai_face();
}
void qcc_hknight_magicb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb5));
    qcc_ai_face();
}
void qcc_hknight_magicb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb6));
    qcc_ai_face();
}
void qcc_hknight_magicb6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb7));
    qcc_ai_face();
}
void qcc_hknight_magicb7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb8));
    qcc_hknight_shot(-2.00000f);
}
void qcc_hknight_magicb8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb9));
    qcc_hknight_shot(-1.00000f);
}
void qcc_hknight_magicb9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb10));
    qcc_hknight_shot(0.000000f);
}
void qcc_hknight_magicb10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 102); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb11));
    qcc_hknight_shot(1.00000f);
}
void qcc_hknight_magicb11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 103); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb12));
    qcc_hknight_shot(2.00000f);
}
void qcc_hknight_magicb12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 104); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicb13));
    qcc_hknight_shot(3.00000f);
}
void qcc_hknight_magicb13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 105); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_face();
//============================================================================
}
void qcc_hknight_magicc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 155); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc2));
    qcc_ai_face();
}
void qcc_hknight_magicc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 156); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc3));
    qcc_ai_face();
}
void qcc_hknight_magicc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 157); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc4));
    qcc_ai_face();
}
void qcc_hknight_magicc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 158); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc5));
    qcc_ai_face();
}
void qcc_hknight_magicc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 159); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc6));
    qcc_ai_face();
}
void qcc_hknight_magicc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 160); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc7));
    qcc_hknight_shot(-2.00000f);
}
void qcc_hknight_magicc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 161); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc8));
    qcc_hknight_shot(-1.00000f);
}
void qcc_hknight_magicc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 162); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc9));
    qcc_hknight_shot(0.000000f);
}
void qcc_hknight_magicc9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 163); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc10));
    qcc_hknight_shot(1.00000f);
}
void qcc_hknight_magicc10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 164); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc11));
    qcc_hknight_shot(2.00000f);
}
void qcc_hknight_magicc11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 165); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_hknight_shot(3.00000f);
//===========================================================================
}
void qcc_hknight_char_a1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a2));
    qcc_ai_charge(20.0000f);
}
void qcc_hknight_char_a2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a3));
    qcc_ai_charge(25.0000f);
}
void qcc_hknight_char_a3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a4));
    qcc_ai_charge(18.0000f);
}
void qcc_hknight_char_a4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a5));
    qcc_ai_charge(16.0000f);
}
void qcc_hknight_char_a5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a6));
    qcc_ai_charge(14.0000f);
}
void qcc_hknight_char_a6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a7));
    qcc_ai_charge(20.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a8));
    qcc_ai_charge(21.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a9));
    qcc_ai_charge(13.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a10));
    qcc_ai_charge(20.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a11));
    qcc_ai_charge(20.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a12));
    qcc_ai_charge(18.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_a12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a13));
    qcc_ai_charge(16.0000f);
}
void qcc_hknight_char_a13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a14));
    qcc_ai_charge(14.0000f);
}
void qcc_hknight_char_a14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a15));
    qcc_ai_charge(25.0000f);
}
void qcc_hknight_char_a15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_a16));
    qcc_ai_charge(21.0000f);
}
void qcc_hknight_char_a16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_charge(13.0000f);
//===========================================================================
}
void qcc_hknight_char_b1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 106); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b2));
    qcc_CheckContinueCharge();
    qcc_ai_charge(23.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_b2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 107); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b3));
    qcc_ai_charge(17.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_b3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 108); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b4));
    qcc_ai_charge(12.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_b4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 109); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b5));
    qcc_ai_charge(22.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_b5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 110); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b6));
    qcc_ai_charge(18.0000f);
    qcc_ai_melee();
}
void qcc_hknight_char_b6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 111); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_char_b1));
    qcc_ai_charge(8.00000f);
    qcc_ai_melee();
//===========================================================================
}
void qcc_hknight_slice1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 112); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice2));
    qcc_ai_charge(9.00000f);
}
void qcc_hknight_slice2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 113); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice3));
    qcc_ai_charge(6.00000f);
}
void qcc_hknight_slice3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 114); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice4));
    qcc_ai_charge(13.0000f);
}
void qcc_hknight_slice4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 115); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice5));
    qcc_ai_charge(4.00000f);
}
void qcc_hknight_slice5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 116); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice6));
    qcc_ai_charge(7.00000f);
    qcc_ai_melee();
}
void qcc_hknight_slice6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 117); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice7));
    qcc_ai_charge(15.0000f);
    qcc_ai_melee();
}
void qcc_hknight_slice7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 118); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice8));
    qcc_ai_charge(8.00000f);
    qcc_ai_melee();
}
void qcc_hknight_slice8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 119); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice9));
    qcc_ai_charge(2.00000f);
    qcc_ai_melee();
}
void qcc_hknight_slice9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 120); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_slice10));
    qcc_ai_melee();
}
void qcc_hknight_slice10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 121); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_charge(3.00000f);
//===========================================================================
}
void qcc_hknight_smash1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 122); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash2));
    qcc_ai_charge(1.00000f);
}
void qcc_hknight_smash2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 123); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash3));
    qcc_ai_charge(13.0000f);
}
void qcc_hknight_smash3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 124); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash4));
    qcc_ai_charge(9.00000f);
}
void qcc_hknight_smash4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 125); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash5));
    qcc_ai_charge(11.0000f);
}
void qcc_hknight_smash5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 126); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash6));
    qcc_ai_charge(10.0000f);
    qcc_ai_melee();
}
void qcc_hknight_smash6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 127); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash7));
    qcc_ai_charge(7.00000f);
    qcc_ai_melee();
}
void qcc_hknight_smash7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 128); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash8));
    qcc_ai_charge(12.0000f);
    qcc_ai_melee();
}
void qcc_hknight_smash8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 129); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash9));
    qcc_ai_charge(2.00000f);
    qcc_ai_melee();
}
void qcc_hknight_smash9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 130); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash10));
    qcc_ai_charge(3.00000f);
    qcc_ai_melee();
}
void qcc_hknight_smash10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 131); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_smash11));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_smash11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 132); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_charge(0.000000f);
//============================================================================
}
void qcc_hknight_watk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 133); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk2));
    qcc_ai_charge(2.00000f);
}
void qcc_hknight_watk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 134); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk3));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_watk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 135); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk4));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_watk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 136); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk5));
    qcc_ai_melee();
}
void qcc_hknight_watk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 137); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk6));
    qcc_ai_melee();
}
void qcc_hknight_watk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 138); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk7));
    qcc_ai_melee();
}
void qcc_hknight_watk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 139); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk8));
    qcc_ai_charge(1.00000f);
}
void qcc_hknight_watk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 140); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk9));
    qcc_ai_charge(4.00000f);
}
void qcc_hknight_watk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 141); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk10));
    qcc_ai_charge(5.00000f);
}
void qcc_hknight_watk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 142); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk11));
    qcc_ai_charge(3.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 143); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk12));
    qcc_ai_charge(2.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 144); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk13));
    qcc_ai_charge(2.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 145); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk14));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_watk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 146); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk15));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_watk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 147); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk16));
    qcc_ai_charge(0.000000f);
}
void qcc_hknight_watk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 148); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk17));
    qcc_ai_charge(1.00000f);
}
void qcc_hknight_watk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 149); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk18));
    qcc_ai_charge(1.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 150); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk19));
    qcc_ai_charge(3.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 151); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk20));
    qcc_ai_charge(4.00000f);
    qcc_ai_melee();
}
void qcc_hknight_watk20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 152); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk21));
    qcc_ai_charge(6.00000f);
}
void qcc_hknight_watk21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 153); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_watk22));
    qcc_ai_charge(7.00000f);
}
void qcc_hknight_watk22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 154); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    qcc_ai_charge(3.00000f);
//============================================================================
}
void qcc_hk_idle_sound(void)
{
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, hknight_idle_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_hknight_pain(int qcc_attacker, float qcc_damage)
{
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, hknight_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (progs.qcc_time - get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > 5)
// allways go into pain frame if it has been a while
    {
        qcc_hknight_pain1();
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
        return;
    }
    if (( qcc_random() * 30 > qcc_damage ))
// didn't flinch
        return;
    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
    qcc_hknight_pain1();
}
;
void qcc_hknight_melee(void)
{
    progs.qcc_hknight_type = progs.qcc_hknight_type + 1;
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, hknight_slash1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (progs.qcc_hknight_type == 1)
        qcc_hknight_slice1();
    else
        if (progs.qcc_hknight_type == 2)
            qcc_hknight_smash1();
        else
            if (progs.qcc_hknight_type == 3)
            {
                qcc_hknight_watk1();
                progs.qcc_hknight_type = 0;
            }
/*QUAKED monster_hell_knight (1 0 0) (-16 -16 -24) (16 16 40) Ambush
*/}
void qcc_monster_hell_knight(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_hknight_mdl_string_index);
    qcc_precache_model2(progs_k_spike_mdl_string_index);
    qcc_precache_model2(progs_h_hellkn_mdl_string_index);
    qcc_precache_sound2(hknight_attack1_wav_string_index);
    qcc_precache_sound2(hknight_death1_wav_string_index);
    qcc_precache_sound2(hknight_pain1_wav_string_index);
    qcc_precache_sound2(hknight_sight1_wav_string_index);
    qcc_precache_sound(hknight_hit_wav_string_index)// used by C code, so don't sound2
;
    qcc_precache_sound2(hknight_slash1_wav_string_index);
    qcc_precache_sound2(hknight_idle_wav_string_index);
    qcc_precache_sound2(hknight_grunt_wav_string_index);
    qcc_precache_sound(knight_sword1_wav_string_index);
    qcc_precache_sound(knight_sword2_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_hknight_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 250);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_run1));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_melee));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_magicc1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_hknight_die));
    qcc_walkmonster_start();
//File: fish.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/}
void qcc_swimmonster_start(void);
void qcc_f_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand2));
    qcc_ai_stand();
}
void qcc_f_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand3));
    qcc_ai_stand();
}
void qcc_f_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand4));
    qcc_ai_stand();
}
void qcc_f_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand5));
    qcc_ai_stand();
}
void qcc_f_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand6));
    qcc_ai_stand();
}
void qcc_f_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand7));
    qcc_ai_stand();
}
void qcc_f_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand8));
    qcc_ai_stand();
}
void qcc_f_stand8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand9));
    qcc_ai_stand();
}
void qcc_f_stand9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand10));
    qcc_ai_stand();
}
void qcc_f_stand10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand11));
    qcc_ai_stand();
}
void qcc_f_stand11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand12));
    qcc_ai_stand();
}
void qcc_f_stand12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand13));
    qcc_ai_stand();
}
void qcc_f_stand13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand14));
    qcc_ai_stand();
}
void qcc_f_stand14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand15));
    qcc_ai_stand();
}
void qcc_f_stand15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand16));
    qcc_ai_stand();
}
void qcc_f_stand16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand17));
    qcc_ai_stand();
}
void qcc_f_stand17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand18));
    qcc_ai_stand();
}
void qcc_f_stand18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand1));
    qcc_ai_stand();
}
void qcc_f_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk2));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk3));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk4));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk5));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk6));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk7));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk8));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk9));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk10));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk11));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk12));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk13));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk14));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk15));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk16));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk17));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk18));
    qcc_ai_walk(8.00000f);
}
void qcc_f_walk18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk1));
    qcc_ai_walk(8.00000f);
}
void qcc_f_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run2));
    qcc_ai_run(12.0000f);
    if (qcc_random() < 0.5f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, fish_idle_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_f_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run3));
    qcc_ai_run(12.0000f);
}
void qcc_f_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run4));
    qcc_ai_run(12.0000f);
}
void qcc_f_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run5));
    qcc_ai_run(12.0000f);
}
void qcc_f_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run6));
    qcc_ai_run(12.0000f);
}
void qcc_f_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run7));
    qcc_ai_run(12.0000f);
}
void qcc_f_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run8));
    qcc_ai_run(12.0000f);
}
void qcc_f_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run9));
    qcc_ai_run(12.0000f);
}
void qcc_f_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run1));
    qcc_ai_run(12.0000f);
}
void qcc_fish_melee(void)
{
    vector qcc_delta;
    float qcc_ldmg;
    if ((!get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self))))
// removed before stroke
        return;
    qcc_delta = vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)));
    if (qcc_vlen(qcc_delta) > 60)
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, fish_bite_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ldmg = ( qcc_random() + qcc_random() ) * 3;
    qcc_T_Damage(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)), progs.qcc_self, progs.qcc_self, qcc_ldmg);
}
void qcc_f_attack1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack2));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack3));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack4));
    qcc_fish_melee();
}
void qcc_f_attack4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack5));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack6));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack7));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack8));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack9));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack10));
    qcc_fish_melee();
}
void qcc_f_attack10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack11));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack12));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack13));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack14));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack15));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack16));
    qcc_fish_melee();
}
void qcc_f_attack16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack17));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack18));
    qcc_ai_charge(10.0000f);
}
void qcc_f_attack18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run1));
    qcc_ai_charge(10.0000f);
}
void qcc_f_death1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, fish_death_wav_string_index, 1.00000f, qcc_ATTN_NORM);
}
void qcc_f_death2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death3));
}
void qcc_f_death3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death4));
}
void qcc_f_death4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death5));
}
void qcc_f_death5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death6));
}
void qcc_f_death6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death7));
}
void qcc_f_death7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death8));
}
void qcc_f_death8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death9));
}
void qcc_f_death9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death10));
}
void qcc_f_death10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death11));
}
void qcc_f_death11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death12));
}
void qcc_f_death12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death13));
}
void qcc_f_death13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death14));
}
void qcc_f_death14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death15));
}
void qcc_f_death15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death16));
}
void qcc_f_death16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death17));
}
void qcc_f_death17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death18));
}
void qcc_f_death18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death19));
}
void qcc_f_death19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death20));
}
void qcc_f_death20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death21));
}
void qcc_f_death21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death21));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
}
void qcc_f_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain2));
}
void qcc_f_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain3));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain4));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain5));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain6));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain7));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain8));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_pain9));
    qcc_ai_pain(6.00000f);
}
void qcc_f_pain9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run1));
    qcc_ai_pain(6.00000f);
}
void qcc_fish_pain(int qcc_attacker, float qcc_damage)
{
// fish allways do pain frames
    qcc_f_pain1();
/*QUAKED monster_fish (1 0 0) (-16 -16 -24) (16 16 24) Ambush
*/}
void qcc_monster_fish(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_fish_mdl_string_index);
    qcc_precache_sound2(fish_death_wav_string_index);
    qcc_precache_sound2(fish_bite_wav_string_index);
    qcc_precache_sound2(fish_idle_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_fish_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 24.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 25);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_run1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_death1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_fish_pain));
    set_qcc_th_melee(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_f_attack1));
    qcc_swimmonster_start();
//File: shalrath.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

SHAL-RATH

==============================================================================
*/}
void qcc_shalrath_pain(void);
void qcc_ShalMissile(void);
void qcc_shal_stand(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_stand));
    qcc_ai_stand();
}
void qcc_shal_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(6.00000f);
}
void qcc_shal_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk3));
    qcc_ai_walk(4.00000f);
}
void qcc_shal_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk4));
    qcc_ai_walk(0.000000f);
}
void qcc_shal_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk5));
    qcc_ai_walk(0.000000f);
}
void qcc_shal_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk6));
    qcc_ai_walk(0.000000f);
}
void qcc_shal_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk7));
    qcc_ai_walk(0.000000f);
}
void qcc_shal_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk8));
    qcc_ai_walk(5.00000f);
}
void qcc_shal_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk9));
    qcc_ai_walk(6.00000f);
}
void qcc_shal_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk10));
    qcc_ai_walk(5.00000f);
}
void qcc_shal_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk11));
    qcc_ai_walk(0.000000f);
}
void qcc_shal_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk12));
    qcc_ai_walk(4.00000f);
}
void qcc_shal_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk1));
    qcc_ai_walk(5.00000f);
}
void qcc_shal_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_idle_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(6.00000f);
}
void qcc_shal_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run3));
    qcc_ai_run(4.00000f);
}
void qcc_shal_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run4));
    qcc_ai_run(0.000000f);
}
void qcc_shal_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run5));
    qcc_ai_run(0.000000f);
}
void qcc_shal_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run6));
    qcc_ai_run(0.000000f);
}
void qcc_shal_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run7));
    qcc_ai_run(0.000000f);
}
void qcc_shal_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run8));
    qcc_ai_run(5.00000f);
}
void qcc_shal_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run9));
    qcc_ai_run(6.00000f);
}
void qcc_shal_run9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run10));
    qcc_ai_run(5.00000f);
}
void qcc_shal_run10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run11));
    qcc_ai_run(0.000000f);
}
void qcc_shal_run11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run12));
    qcc_ai_run(4.00000f);
}
void qcc_shal_run12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run1));
    qcc_ai_run(5.00000f);
}
void qcc_shal_attack1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack2));
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_attack_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_ai_face();
}
void qcc_shal_attack2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack3));
    qcc_ai_face();
}
void qcc_shal_attack3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack4));
    qcc_ai_face();
}
void qcc_shal_attack4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack5));
    qcc_ai_face();
}
void qcc_shal_attack5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack6));
    qcc_ai_face();
}
void qcc_shal_attack6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack7));
    qcc_ai_face();
}
void qcc_shal_attack7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack8));
    qcc_ai_face();
}
void qcc_shal_attack8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack9));
    qcc_ai_face();
}
void qcc_shal_attack9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack10));
    qcc_ShalMissile();
}
void qcc_shal_attack10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack11));
    qcc_ai_face();
}
void qcc_shal_attack11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run1));
}
void qcc_shal_pain1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_pain2));
}
void qcc_shal_pain2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_pain3));
}
void qcc_shal_pain3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_pain4));
}
void qcc_shal_pain4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_pain5));
}
void qcc_shal_pain5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run1));
}
void qcc_shal_death1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death2));
}
void qcc_shal_death2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death3));
}
void qcc_shal_death3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death4));
}
void qcc_shal_death4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death5));
}
void qcc_shal_death5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death6));
}
void qcc_shal_death6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death7));
}
void qcc_shal_death7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_death7));
}
void qcc_shalrath_pain(void)
{
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_pain_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_shal_pain1();
    set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 3);
}
void qcc_shalrath_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -90)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_shal_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, shalrath_death_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_shal_death1();
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT)// insert death sounds here
;
/*
================
ShalMissile
================
*/}
void qcc_ShalMissileTouch(void);
void qcc_ShalHome(void);
void qcc_ShalMissile(void)
{
    int qcc_missile;
    vector qcc_dir;
    float qcc_dist,     qcc_flytime;
    qcc_dir = qcc_normalize(vectorSub(( vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), (vector)  {{0.000000f, 0.000000f, 10.0000f}}) ), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_dist = qcc_vlen(vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    qcc_flytime = qcc_dist * 0.002f;
    if (qcc_flytime < 0.1f)
        qcc_flytime = 0.1f;
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, shalrath_attack2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_missile = qcc_spawn(qcc_classname_progs_v_spike_mdl);
    set_qcc_owner(PROG_TO_EDICT(qcc_missile), progs.qcc_self);
    set_qcc_solid(PROG_TO_EDICT(qcc_missile), qcc_SOLID_BBOX);
    set_qcc_movetype(PROG_TO_EDICT(qcc_missile), qcc_MOVETYPE_FLYMISSILE);
    qcc_setmodel(qcc_missile, qcc_classname_progs_v_spike_mdl);
    qcc_setsize(qcc_missile, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_origin(PROG_TO_EDICT(qcc_missile), vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), (vector)  {{0.000000f, 0.000000f, 10.0000f}}));
    set_qcc_velocity(PROG_TO_EDICT(qcc_missile), vectorMulFloat(qcc_dir, 400));
    set_qcc_avelocity(PROG_TO_EDICT(qcc_missile), (vector)  {{300.000f, 300.000f, 300.000f}});
    set_qcc_nextthink(PROG_TO_EDICT(qcc_missile), qcc_flytime + progs.qcc_time);
    set_qcc_think(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_ShalHome));
    set_qcc_enemy(PROG_TO_EDICT(qcc_missile), get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)));
    set_qcc_touch(PROG_TO_EDICT(qcc_missile), getFunctionIndex(qcc_ShalMissileTouch));
}
void qcc_ShalHome(void)
{
    vector qcc_dir,     qcc_vtemp;
    qcc_vtemp = vectorAdd(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), (vector)  {{0.000000f, 0.000000f, 10.0000f}});
    if (get_qcc_health(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))) < 1)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_dir = qcc_normalize(vectorSub(qcc_vtemp, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
    if (progs.qcc_skill == 3)
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorMulFloat(qcc_dir, 350));
    else
        set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), vectorMulFloat(qcc_dir, 250));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.2f);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_ShalHome));
}
void qcc_ShalMissileTouch(void)
{
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_other)), qcc_classname_monster_zombie))
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, progs.qcc_self, 110.000f);
    qcc_T_RadiusDamage(progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 40.0000f, progs.qcc_world);
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, weapons_r_exp3_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_EXPLOSION);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)).z);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_self), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_SUB_Null));
    qcc_setmodel(progs.qcc_self, progs_s_explod_spr_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    qcc_s_explode1();
//=================================================================
/*QUAKED monster_shalrath (1 0 0) (-32 -32 -24) (32 32 48) Ambush
*/}
void qcc_monster_shalrath(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_shalrath_mdl_string_index);
    qcc_precache_model2(progs_h_shal_mdl_string_index);
    qcc_precache_model2(qcc_classname_progs_v_spike_mdl);
    qcc_precache_sound2(shalrath_attack_wav_string_index);
    qcc_precache_sound2(shalrath_attack2_wav_string_index);
    qcc_precache_sound2(shalrath_death_wav_string_index);
    qcc_precache_sound2(shalrath_idle_wav_string_index);
    qcc_precache_sound2(shalrath_pain_wav_string_index);
    qcc_precache_sound2(shalrath_sight_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_shalrath_mdl_string_index);
    qcc_setsize(progs.qcc_self, qcc_VEC_HULL2_MIN, qcc_VEC_HULL2_MAX);
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 400);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_stand));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_run1));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shalrath_die));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shalrath_pain));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_shal_attack1));
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_walkmonster_start));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f + qcc_random() * 0.1f);
//File: enforcer.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

SOLDIER / PLAYER

==============================================================================
*/}
void qcc_Laser_Touch(void)
{
    vector qcc_org;
    if (progs.qcc_other == get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)))
// don't explode on owner
        return;
    if (qcc_pointcontents(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))) == qcc_CONTENT_SKY)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, enforcer_enfstop_wav_string_index, 1.00000f, qcc_ATTN_STATIC);
    qcc_org = vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), floatMulVector(8, qcc_normalize(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)))));
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_other)))
    {
        qcc_SpawnBlood(qcc_org, vectorMulFloat(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_self)), 0.2f), 15.0000f);
        qcc_T_Damage(progs.qcc_other, progs.qcc_self, get_qcc_owner(PROG_TO_EDICT(progs.qcc_self)), 15.0000f);
    }
    else
    {
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
        qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_GUNSHOT);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.x);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.y);
        qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_org.z);
    }
    qcc_remove(progs.qcc_self);
}
void qcc_LaunchLaser(vector qcc_org, vector qcc_vec)
{
//local	vector	vec; //next-hack: removed
    if (areStringsEqual(get_qcc_classname(PROG_TO_EDICT(progs.qcc_self)), qcc_classname_monster_enforcer))
        qcc_sound(progs.qcc_self, qcc_CHAN_WEAPON, enforcer_enfire_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_vec = qcc_normalize(qcc_vec);
    progs.qcc_newmis = qcc_spawn(qcc_classname_progs_laser_mdl);
    set_qcc_owner(PROG_TO_EDICT(progs.qcc_newmis), progs.qcc_self);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_newmis), qcc_MOVETYPE_FLY);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_newmis), qcc_SOLID_BBOX);
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_newmis), qcc_EF_DIMLIGHT);
    qcc_setmodel(progs.qcc_newmis, qcc_classname_progs_laser_mdl);
    qcc_setsize(progs.qcc_newmis, (vector) {{0.000000f, 0.000000f, 0.000000f}}, (vector) {{0.000000f, 0.000000f, 0.000000f}});
    qcc_setorigin(progs.qcc_newmis, qcc_org);
    set_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis), vectorMulFloat(qcc_vec, 600));
    set_qcc_angles(PROG_TO_EDICT(progs.qcc_newmis), qcc_vectoangles(get_qcc_velocity(PROG_TO_EDICT(progs.qcc_newmis))));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_newmis), progs.qcc_time + 5);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_SUB_Remove));
    set_qcc_touch(PROG_TO_EDICT(progs.qcc_newmis), getFunctionIndex(qcc_Laser_Touch));
}
void qcc_enforcer_fire(void)
{
    vector qcc_org;
    set_qcc_effects(PROG_TO_EDICT(progs.qcc_self), (((int) get_qcc_effects(PROG_TO_EDICT(progs.qcc_self))) | ((int) qcc_EF_MUZZLEFLASH)));
    qcc_makevectors(get_qcc_angles(PROG_TO_EDICT(progs.qcc_self)));
    qcc_org = vectorAdd(vectorAdd(vectorAdd(get_qcc_origin(PROG_TO_EDICT(progs.qcc_self)), vectorMulFloat(progs.qcc_v_forward, 30)), vectorMulFloat(progs.qcc_v_right, 8.5f)), (vector)  {{0.000000f, 0.000000f, 16.0000f}});
    qcc_LaunchLaser(qcc_org, vectorSub(get_qcc_origin(PROG_TO_EDICT(get_qcc_enemy(PROG_TO_EDICT(progs.qcc_self)))), get_qcc_origin(PROG_TO_EDICT(progs.qcc_self))));
//============================================================================
}
void qcc_enf_stand1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand2));
    qcc_ai_stand();
}
void qcc_enf_stand2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand3));
    qcc_ai_stand();
}
void qcc_enf_stand3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand4));
    qcc_ai_stand();
}
void qcc_enf_stand4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand5));
    qcc_ai_stand();
}
void qcc_enf_stand5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand6));
    qcc_ai_stand();
}
void qcc_enf_stand6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand7));
    qcc_ai_stand();
}
void qcc_enf_stand7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand1));
    qcc_ai_stand();
}
void qcc_enf_walk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_idle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_walk(2.00000f);
}
void qcc_enf_walk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk3));
    qcc_ai_walk(4.00000f);
}
void qcc_enf_walk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk4));
    qcc_ai_walk(4.00000f);
}
void qcc_enf_walk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk5));
    qcc_ai_walk(3.00000f);
}
void qcc_enf_walk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk6));
    qcc_ai_walk(1.00000f);
}
void qcc_enf_walk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk7));
    qcc_ai_walk(2.00000f);
}
void qcc_enf_walk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk8));
    qcc_ai_walk(2.00000f);
}
void qcc_enf_walk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk9));
    qcc_ai_walk(1.00000f);
}
void qcc_enf_walk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk10));
    qcc_ai_walk(2.00000f);
}
void qcc_enf_walk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk11));
    qcc_ai_walk(4.00000f);
}
void qcc_enf_walk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk12));
    qcc_ai_walk(4.00000f);
}
void qcc_enf_walk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk13));
    qcc_ai_walk(1.00000f);
}
void qcc_enf_walk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk14));
    qcc_ai_walk(2.00000f);
}
void qcc_enf_walk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk15));
    qcc_ai_walk(3.00000f);
}
void qcc_enf_walk15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk16));
    qcc_ai_walk(4.00000f);
}
void qcc_enf_walk16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk1));
    qcc_ai_walk(2.00000f);
}
void qcc_enf_run1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run2));
    if (qcc_random() < 0.2f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_idle1_wav_string_index, 1.00000f, qcc_ATTN_IDLE);
    qcc_ai_run(18.0000f);
}
void qcc_enf_run2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run3));
    qcc_ai_run(14.0000f);
}
void qcc_enf_run3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run4));
    qcc_ai_run(7.00000f);
}
void qcc_enf_run4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run5));
    qcc_ai_run(12.0000f);
}
void qcc_enf_run5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run6));
    qcc_ai_run(14.0000f);
}
void qcc_enf_run6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run7));
    qcc_ai_run(14.0000f);
}
void qcc_enf_run7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run8));
    qcc_ai_run(7.00000f);
}
void qcc_enf_run8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
    qcc_ai_run(11.0000f);
}
void qcc_enf_atk1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk2));
    qcc_ai_face();
}
void qcc_enf_atk2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk3));
    qcc_ai_face();
}
void qcc_enf_atk3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk4));
    qcc_ai_face();
}
void qcc_enf_atk4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk5));
    qcc_ai_face();
}
void qcc_enf_atk5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk6));
    qcc_ai_face();
}
void qcc_enf_atk6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk7));
    qcc_enforcer_fire();
}
void qcc_enf_atk7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk8));
    qcc_ai_face();
}
void qcc_enf_atk8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk9));
    qcc_ai_face();
}
void qcc_enf_atk9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk10));
    qcc_ai_face();
}
void qcc_enf_atk10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk11));
    qcc_enforcer_fire();
}
void qcc_enf_atk11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk12));
    qcc_ai_face();
}
void qcc_enf_atk12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk13));
    qcc_ai_face();
}
void qcc_enf_atk13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk14));
    qcc_ai_face();
}
void qcc_enf_atk14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
    qcc_ai_face();
    qcc_SUB_CheckRefire(getFunctionIndex (qcc_enf_atk1));
}
void qcc_enf_paina1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paina2));
}
void qcc_enf_paina2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 67); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paina3));
}
void qcc_enf_paina3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 68); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paina4));
}
void qcc_enf_paina4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 69); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
}
void qcc_enf_painb1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 70); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painb2));
}
void qcc_enf_painb2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 71); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painb3));
}
void qcc_enf_painb3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 72); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painb4));
}
void qcc_enf_painb4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 73); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painb5));
}
void qcc_enf_painb5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 74); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
}
void qcc_enf_painc1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 75); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc2));
}
void qcc_enf_painc2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 76); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc3));
}
void qcc_enf_painc3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 77); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc4));
}
void qcc_enf_painc4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 78); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc5));
}
void qcc_enf_painc5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 79); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc6));
}
void qcc_enf_painc6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 80); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc7));
}
void qcc_enf_painc7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 81); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_painc8));
}
void qcc_enf_painc8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 82); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
}
void qcc_enf_paind1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 83); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind2));
}
void qcc_enf_paind2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 84); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind3));
}
void qcc_enf_paind3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 85); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind4));
}
void qcc_enf_paind4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 86); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind5));
    qcc_ai_painforward(2.00000f);
}
void qcc_enf_paind5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 87); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind6));
    qcc_ai_painforward(1.00000f);
}
void qcc_enf_paind6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 88); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind7));
}
void qcc_enf_paind7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 89); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind8));
}
void qcc_enf_paind8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 90); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind9));
}
void qcc_enf_paind9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 91); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind10));
}
void qcc_enf_paind10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 92); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind11));
}
void qcc_enf_paind11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 93); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind12));
    qcc_ai_painforward(1.00000f);
}
void qcc_enf_paind12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 94); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind13));
    qcc_ai_painforward(1.00000f);
}
void qcc_enf_paind13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 95); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind14));
    qcc_ai_painforward(1.00000f);
}
void qcc_enf_paind14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 96); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind15));
}
void qcc_enf_paind15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 97); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind16));
}
void qcc_enf_paind16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 98); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind17));
    qcc_ai_pain(1.00000f);
}
void qcc_enf_paind17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 99); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind18));
    qcc_ai_pain(1.00000f);
}
void qcc_enf_paind18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 100); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_paind19));
}
void qcc_enf_paind19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 101); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
}
void qcc_enf_pain(int qcc_attacker, float qcc_damage)
{
    float qcc_r;
    qcc_r = qcc_random();
    if (get_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self)) > progs.qcc_time)
        return;
    if (qcc_r < 0.5f)
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_pain1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    else
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_pain2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_r < 0.2f)
    {
        set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
        qcc_enf_paina1();
    }
    else
        if (qcc_r < 0.4f)
        {
            set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
            qcc_enf_painb1();
        }
        else
            if (qcc_r < 0.7f)
            {
                set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 1);
                qcc_enf_painc1();
            }
            else
            {
                set_qcc_pain_finished(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
                qcc_enf_paind1();
            }
//============================================================================
}
void qcc_enf_die1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die2));
}
void qcc_enf_die2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die3));
}
void qcc_enf_die3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), 5);
    qcc_DropBackpack();
}
void qcc_enf_die4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die5));
    qcc_ai_forward(14.0000f);
}
void qcc_enf_die5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die6));
    qcc_ai_forward(2.00000f);
}
void qcc_enf_die6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die7));
}
void qcc_enf_die7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die8));
}
void qcc_enf_die8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die9));
}
void qcc_enf_die9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die10));
    qcc_ai_forward(3.00000f);
}
void qcc_enf_die10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die11));
    qcc_ai_forward(5.00000f);
}
void qcc_enf_die11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die12));
    qcc_ai_forward(5.00000f);
}
void qcc_enf_die12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die13));
    qcc_ai_forward(5.00000f);
}
void qcc_enf_die13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die14));
}
void qcc_enf_die14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die14));
}
void qcc_enf_fdie1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie2));
}
void qcc_enf_fdie2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie3));
}
void qcc_enf_fdie3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie4));
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_NOT);
    set_qcc_ammo_cells(PROG_TO_EDICT(progs.qcc_self), 5);
    qcc_DropBackpack();
}
void qcc_enf_fdie4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 58); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie5));
}
void qcc_enf_fdie5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie6));
}
void qcc_enf_fdie6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie7));
}
void qcc_enf_fdie7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie8));
}
void qcc_enf_fdie8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie9));
}
void qcc_enf_fdie9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie10));
}
void qcc_enf_fdie10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie11));
}
void qcc_enf_fdie11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_fdie11));
}
void qcc_enf_die(void)
{
// check for gib
    if (get_qcc_health(PROG_TO_EDICT(progs.qcc_self)) < -35)
    {
        qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, player_udeath_wav_string_index, 1.00000f, qcc_ATTN_NORM);
        qcc_ThrowHead(progs_h_mega_mdl_string_index, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib1_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, get_qcc_health(PROG_TO_EDICT(progs.qcc_self)));
        return;
// regular death
    }
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, enforcer_death1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    if (qcc_random() > 0.5f)
        qcc_enf_die1();
    else
        qcc_enf_fdie1();
/*QUAKED monster_enforcer (1 0 0) (-16 -16 -24) (16 16 40) Ambush

*/}
void qcc_monster_enforcer(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_enforcer_mdl_string_index);
    qcc_precache_model2(progs_h_mega_mdl_string_index);
    qcc_precache_model2(qcc_classname_progs_laser_mdl);
    qcc_precache_sound2(enforcer_death1_wav_string_index);
    qcc_precache_sound2(enforcer_enfire_wav_string_index);
    qcc_precache_sound2(enforcer_enfstop_wav_string_index);
    qcc_precache_sound2(enforcer_idle1_wav_string_index);
    qcc_precache_sound2(enforcer_pain1_wav_string_index);
    qcc_precache_sound2(enforcer_pain2_wav_string_index);
    qcc_precache_sound2(enforcer_sight1_wav_string_index);
    qcc_precache_sound2(enforcer_sight2_wav_string_index);
    qcc_precache_sound2(enforcer_sight3_wav_string_index);
    qcc_precache_sound2(enforcer_sight4_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_enforcer_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-16.0000f, -16.0000f, -24.0000f}}, (vector) {{16.0000f, 16.0000f, 40.0000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 80);
    set_qcc_th_stand(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_stand1));
    set_qcc_th_walk(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_walk1));
    set_qcc_th_run(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_run1));
    set_qcc_th_pain(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_pain));
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_die));
    set_qcc_th_missile(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_enf_atk1));
    qcc_walkmonster_start();
//File: oldone.qc
/*  Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*//*
==============================================================================

OLD ONE

==============================================================================
*/}
void qcc_finale_1(void);
void qcc_finale_2(void);
void qcc_finale_3(void);
void qcc_finale_4(void);
//void() old_stand     =[      $old1,       old_stand    ] {};
;
void qcc_old_idle1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 0); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle2));
}
void qcc_old_idle2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 1); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle3));
}
void qcc_old_idle3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 2); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle4));
}
void qcc_old_idle4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 3); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle5));
}
void qcc_old_idle5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 4); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle6));
}
void qcc_old_idle6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 5); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle7));
}
void qcc_old_idle7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 6); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle8));
}
void qcc_old_idle8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 7); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle9));
}
void qcc_old_idle9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 8); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle10));
}
void qcc_old_idle10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 9); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle11));
}
void qcc_old_idle11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 10); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle12));
}
void qcc_old_idle12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 11); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle13));
}
void qcc_old_idle13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 12); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle14));
}
void qcc_old_idle14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 13); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle15));
}
void qcc_old_idle15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 14); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle16));
}
void qcc_old_idle16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 15); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle17));
}
void qcc_old_idle17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 16); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle18));
}
void qcc_old_idle18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 17); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle19));
}
void qcc_old_idle19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 18); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle20));
}
void qcc_old_idle20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 19); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle21));
}
void qcc_old_idle21(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 20); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle22));
}
void qcc_old_idle22(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 21); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle23));
}
void qcc_old_idle23(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 22); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle24));
}
void qcc_old_idle24(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 23); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle25));
}
void qcc_old_idle25(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 24); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle26));
}
void qcc_old_idle26(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 25); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle27));
}
void qcc_old_idle27(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 26); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle28));
}
void qcc_old_idle28(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 27); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle29));
}
void qcc_old_idle29(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 28); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle30));
}
void qcc_old_idle30(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 29); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle31));
}
void qcc_old_idle31(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 30); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle32));
}
void qcc_old_idle32(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 31); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle33));
}
void qcc_old_idle33(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 32); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle34));
}
void qcc_old_idle34(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 33); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle35));
}
void qcc_old_idle35(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 34); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle36));
}
void qcc_old_idle36(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 35); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle37));
}
void qcc_old_idle37(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 36); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle38));
}
void qcc_old_idle38(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 37); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle39));
}
void qcc_old_idle39(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 38); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle40));
}
void qcc_old_idle40(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 39); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle41));
}
void qcc_old_idle41(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 40); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle42));
}
void qcc_old_idle42(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 41); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle43));
}
void qcc_old_idle43(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 42); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle44));
}
void qcc_old_idle44(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 43); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle45));
}
void qcc_old_idle45(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 44); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle46));
}
void qcc_old_idle46(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 45); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle1));
}
void qcc_old_thrash1(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 46); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash2));
    qcc_lightstyle(0.000000f, m_string_index);
}
void qcc_old_thrash2(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 47); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash3));
    qcc_lightstyle(0.000000f, k_string_index);
}
void qcc_old_thrash3(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 48); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash4));
    qcc_lightstyle(0.000000f, k_string_index);
}
void qcc_old_thrash4(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 49); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash5));
    qcc_lightstyle(0.000000f, i_string_index);
}
void qcc_old_thrash5(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 50); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash6));
    qcc_lightstyle(0.000000f, g_string_index);
}
void qcc_old_thrash6(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 51); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash7));
    qcc_lightstyle(0.000000f, e_string_index);
}
void qcc_old_thrash7(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 52); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash8));
    qcc_lightstyle(0.000000f, c_string_index);
}
void qcc_old_thrash8(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 53); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash9));
    qcc_lightstyle(0.000000f, a_string_index);
}
void qcc_old_thrash9(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 54); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash10));
    qcc_lightstyle(0.000000f, c_string_index);
}
void qcc_old_thrash10(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 55); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash11));
    qcc_lightstyle(0.000000f, e_string_index);
}
void qcc_old_thrash11(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 56); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash12));
    qcc_lightstyle(0.000000f, g_string_index);
}
void qcc_old_thrash12(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 57); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash13));
    qcc_lightstyle(0.000000f, i_string_index);
}
void qcc_old_thrash13(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 59); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash14));
    qcc_lightstyle(0.000000f, k_string_index);
}
void qcc_old_thrash14(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 60); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash15));
    qcc_lightstyle(0.000000f, m_string_index);
}
void qcc_old_thrash15(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 61); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash16));
    qcc_lightstyle(0.000000f, m_string_index);
    set_qcc_cnt(PROG_TO_EDICT(progs.qcc_self), get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) + 1);
    if (get_qcc_cnt(PROG_TO_EDICT(progs.qcc_self)) != 3)
        set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash1));
}
void qcc_old_thrash16(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 62); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash17));
    qcc_lightstyle(0.000000f, g_string_index);
}
void qcc_old_thrash17(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 63); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash18));
    qcc_lightstyle(0.000000f, c_string_index);
}
void qcc_old_thrash18(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 64); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash19));
    qcc_lightstyle(0.000000f, b_string_index);
}
void qcc_old_thrash19(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 65); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash20));
    qcc_lightstyle(0.000000f, a_string_index);
}
void qcc_old_thrash20(void)
{
    set_qcc_frame(PROG_TO_EDICT(progs.qcc_self), 66); set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_thrash20));
    qcc_finale_4();
//============================================================================
}
void qcc_finale_1(void)
{
    int qcc_pos,     qcc_pl;
    int qcc_timer;
    progs.qcc_intermission_exittime = progs.qcc_time + 10000000// never allow exit
;
    progs.qcc_intermission_running = 1// find the intermission spot
;
    qcc_pos = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_info_intermission);
    if ((!qcc_pos))
        qcc_error(no_info_intermission_string_index);
    qcc_pl = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_misc_teleporttrain);
    if ((!qcc_pl))
        qcc_error(no_teleporttrain_string_index);
    qcc_remove(qcc_pl);
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
    qcc_WriteString(qcc_MSG_ALL, NULL_string_index);
    qcc_pl = qcc_find(progs.qcc_world, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
    while (qcc_pl != progs.qcc_world)
    {
        set_qcc_view_ofs(PROG_TO_EDICT(qcc_pl), (vector)  {{0.000000f, 0.000000f, 0.000000f}});
        set_qcc_angles(PROG_TO_EDICT(qcc_pl), set_qcc_v_angle(PROG_TO_EDICT(progs.qcc_other), get_qcc_mangle(PROG_TO_EDICT(qcc_pos))));
        set_qcc_fixangle(PROG_TO_EDICT(qcc_pl), qcc_TRUE)// turn this way immediately
;
        set_qcc_map(PROG_TO_EDICT(qcc_pl), get_qcc_map(PROG_TO_EDICT(progs.qcc_self)));
        set_qcc_nextthink(PROG_TO_EDICT(qcc_pl), progs.qcc_time + 0.5f);
        set_qcc_takedamage(PROG_TO_EDICT(qcc_pl), qcc_DAMAGE_NO);
        set_qcc_solid(PROG_TO_EDICT(qcc_pl), qcc_SOLID_NOT);
        set_qcc_movetype(PROG_TO_EDICT(qcc_pl), qcc_MOVETYPE_NONE);
        set_qcc_modelindex(PROG_TO_EDICT(qcc_pl), 0);
        qcc_setorigin(qcc_pl, get_qcc_origin(PROG_TO_EDICT(qcc_pos)));
        qcc_pl = qcc_find(qcc_pl, offsetof (big_entvars_t, qcc_classname), qcc_classname_player);
// make fake versions of all players as standins, and move the real
// players to the intermission spot
// wait for 1 second
    }
    qcc_timer = qcc_spawn(qcc_classname_nh_timer);
    set_qcc_nextthink(PROG_TO_EDICT(qcc_timer), progs.qcc_time + 1);
    set_qcc_think(PROG_TO_EDICT(qcc_timer), getFunctionIndex(qcc_finale_2));
}
void qcc_finale_2(void)
{
    vector qcc_o// start a teleport splash inside shub
;
    qcc_o = vectorSub(get_qcc_origin(PROG_TO_EDICT(progs.qcc_shub)), (vector)  {{0.000000f, 100.000f, 0.000000f}});
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_SVC_TEMPENTITY);
    qcc_WriteByte(qcc_MSG_BROADCAST, qcc_TE_TELEPORT);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_o.x);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_o.y);
    qcc_WriteCoord(qcc_MSG_BROADCAST, qcc_o.z);
    qcc_sound(progs.qcc_shub, qcc_CHAN_VOICE, misc_r_tele1_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 2);
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_finale_3));
}
void qcc_finale_3(void)
{
// start shub thrashing wildly
    set_qcc_think(PROG_TO_EDICT(progs.qcc_shub), getFunctionIndex(qcc_old_thrash1));
    qcc_sound(progs.qcc_shub, qcc_CHAN_VOICE, boss2_death_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_lightstyle(0.000000f, abcdefghijklmlkjihgfedcb_string_index);
}
void qcc_finale_4(void)
{
// throw tons of meat chunks	
    vector qcc_oldo;
    float qcc_x,     qcc_y,     qcc_z;
    float qcc_r;
    int qcc_n;
    qcc_sound(progs.qcc_self, qcc_CHAN_VOICE, boss2_pop2_wav_string_index, 1.00000f, qcc_ATTN_NORM);
    qcc_oldo = get_qcc_origin(PROG_TO_EDICT(progs.qcc_self));
    qcc_z = 16;
    while (qcc_z <= 144)
    {
        qcc_x = -64;
        while (qcc_x <= 64)
        {
            qcc_y = -64;
            while (qcc_y <= 64)
            {
                set_qcc_origin_x(PROG_TO_EDICT(progs.qcc_self), qcc_oldo.x + qcc_x);
                set_qcc_origin_y(PROG_TO_EDICT(progs.qcc_self), qcc_oldo.y + qcc_y);
                set_qcc_origin_z(PROG_TO_EDICT(progs.qcc_self), qcc_oldo.z + qcc_z);
                qcc_r = qcc_random();
                if (qcc_r < 0.3f)
                    qcc_ThrowGib(qcc_classname_progs_gib1_mdl, -999.000f);
                else
                    if (qcc_r < 0.6f)
                        qcc_ThrowGib(qcc_classname_progs_gib2_mdl, -999.000f);
                    else
                        qcc_ThrowGib(qcc_classname_progs_gib3_mdl, -999.000f);
                qcc_y = qcc_y + 32;
            }
            qcc_x = qcc_x + 32;
        }
        qcc_z = qcc_z + 96;
// start the end text
    }
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_FINALE);
    qcc_WriteString(qcc_MSG_ALL, Congratulations_and_well_done__Y_FCD34B06_long_string_index)// put a player model down
;
    qcc_n = qcc_spawn(qcc_classname_player);
    qcc_setmodel(qcc_n, progs_player_mdl_string_index);
    qcc_oldo = vectorSub(qcc_oldo, (vector)  {{32.0000f, 264.000f, 0.000000f}});
    qcc_setorigin(qcc_n, qcc_oldo);
    set_qcc_angles(PROG_TO_EDICT(qcc_n), (vector)  {{0.000000f, 290.000f, 0.000000f}});
    set_qcc_frame(PROG_TO_EDICT(qcc_n), 1);
    qcc_remove(progs.qcc_self)// switch cd track
;
    qcc_WriteByte(qcc_MSG_ALL, qcc_SVC_CDTRACK);
    qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
    qcc_WriteByte(qcc_MSG_ALL, 3.00000f);
    qcc_lightstyle(0.000000f, m_string_index);
//============================================================================
/*QUAKED monster_oldone (1 0 0) (-16 -16 -24) (16 16 32)
*/}
void qcc_monster_oldone(void)
{
    if (progs.qcc_deathmatch)
    {
        qcc_remove(progs.qcc_self);
        return;
    }
    qcc_precache_model2(progs_oldone_mdl_string_index);
    qcc_precache_sound2(boss2_death_wav_string_index);
    qcc_precache_sound2(boss2_idle_wav_string_index);
    qcc_precache_sound2(boss2_sight_wav_string_index);
    qcc_precache_sound2(boss2_pop2_wav_string_index);
    set_qcc_solid(PROG_TO_EDICT(progs.qcc_self), qcc_SOLID_SLIDEBOX);
    set_qcc_movetype(PROG_TO_EDICT(progs.qcc_self), qcc_MOVETYPE_STEP);
    qcc_setmodel(progs.qcc_self, progs_oldone_mdl_string_index);
    qcc_setsize(progs.qcc_self, (vector) {{-160.000f, -128.000f, -24.0000f}}, (vector) {{160.000f, 128.000f, 256.000f}});
    set_qcc_health(PROG_TO_EDICT(progs.qcc_self), 40000)// kill by telefrag
;
    set_qcc_think(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_old_idle1));
    set_qcc_nextthink(PROG_TO_EDICT(progs.qcc_self), progs.qcc_time + 0.1f);
    set_qcc_takedamage(PROG_TO_EDICT(progs.qcc_self), qcc_DAMAGE_YES);
    set_qcc_th_die(PROG_TO_EDICT(progs.qcc_self), getFunctionIndex(qcc_finale_1));
    progs.qcc_shub = progs.qcc_self;
    progs.qcc_total_monsters = progs.qcc_total_monsters + 1;
}
