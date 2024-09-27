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
#ifndef PROGSDEFQ1_H
#define PROGSDEFQ1_H


#if USE_PROGSDAT
typedef struct
{	int	pad[28];
	int	self;
	int	other;
	int	world;
	float	time;
	float	frametime;
	float	force_retouch;
	string_t	mapname;
	float	deathmatch;
	float	coop;
	float	teamplay;
	float	serverflags;
	float	total_secrets;
	float	total_monsters;
	float	found_secrets;
	float	killed_monsters;
	float	parm1;
	float	parm2;
	float	parm3;
	float	parm4;
	float	parm5;
	float	parm6;
	float	parm7;
	float	parm8;
	float	parm9;
	float	parm10;
	float	parm11;
	float	parm12;
	float	parm13;
	float	parm14;
	float	parm15;
	float	parm16;
	vec3_t	v_forward;
	vec3_t	v_up;
	vec3_t	v_right;
	float	trace_allsolid;
	float	trace_startsolid;
	float	trace_fraction;
	vec3_t	trace_endpos;
	vec3_t	trace_plane_normal;
	float	trace_plane_dist;
	int	trace_ent;
	float	trace_inopen;
	float	trace_inwater;
	int	msg_entity;
	func_t	main;
	func_t	StartFrame;
	func_t	PlayerPreThink;
	func_t	PlayerPostThink;
	func_t	ClientKill;
	func_t	ClientConnect;
	func_t	PutClientInServer;
	func_t	ClientDisconnect;
	func_t	SetNewParms;
	func_t	SetChangeParms;
} globalvars_t;

typedef struct
{
	float	modelindex;
	vec3_t	absmin;
	vec3_t	absmax;
	float	ltime;
	float	movetype;
	float	solid;
	vec3_t	origin;
	vec3_t	oldorigin;
	vec3_t	velocity;
	vec3_t	angles;
	vec3_t	avelocity;
	vec3_t	punchangle;
	string_t	classname;
	string_t	model;
	float	frame;
	float	skin;
	float	effects;
	vec3_t	mins;
	vec3_t	maxs;
	vec3_t	size;
	func_t	touch;
	func_t	use;
	func_t	think;
	func_t	blocked;
	float	nextthink;
	int	groundentity;
	float	health;
	float	frags;
	float	weapon;
	string_t	weaponmodel;
	float	weaponframe;
	float	currentammo;
	float	ammo_shells;
	float	ammo_nails;
	float	ammo_rockets;
	float	ammo_cells;
	float	items;
	float	takedamage;
	int	chain;
	float	deadflag;
	vec3_t	view_ofs;
	float	button0;
	float	button1;
	float	button2;
	float	impulse;
	float	fixangle;
	vec3_t	v_angle;
	float	idealpitch;
	string_t	netname;
	int	enemy;
	float	flags;
	float	colormap;
	float	team;
	float	max_health;
	float	teleport_time;
	float	armortype;
	float	armorvalue;
	float	waterlevel;
	float	watertype;
	float	ideal_yaw;
	float	yaw_speed;
	int	aiment;
	int	goalentity;
	float	spawnflags;
	string_t	target;
	string_t	targetname;
	float	dmg_take;
	float	dmg_save;
	int	dmg_inflictor;
	int	owner;
	vec3_t	movedir;
	string_t	message;
	float	sounds;
	string_t	noise;
	string_t	noise1;
	string_t	noise2;
	string_t	noise3;
} entvars_t;

#define PROGHEADER_CRC 5927
#else
#include "cprogs_def.h"
typedef struct
{
    /*
    //int	pad[28];
//	int	self;
	int	other;
	int	world;
	float	time;
	float	frametime;
	float	force_retouch;
//	string_t	mapname;
	float	deathmatch;
	float	coop;
	float	teamplay;
	float	serverflags;
	float	total_secrets;
	float	total_monsters;
	float	found_secrets;
	float	killed_monsters;
	float	parm1;
	float	parm2;
	float	parm3;
	float	parm4;
	float	parm5;
	float	parm6;
	float	parm7;
	float	parm8;
	float	parm9;
	float	parm10;
	float	parm11;
	float	parm12;
	float	parm13;
	float	parm14;
	float	parm15;
	float	parm16;
	vector	v_forward;
	vector	v_up;
	vector	v_right;
	float	trace_allsolid;
	float	trace_startsolid;
	float	trace_fraction;
	vector	trace_endpos;
	vector	trace_plane_normal;
	float	trace_plane_dist;
	int	trace_ent;
	float	trace_inopen;
	float	trace_inwater;
	int	msg_entity;
	func_t	main;
	func_t	StartFrame;
	func_t	PlayerPreThink;
	func_t	PlayerPostThink;
	func_t	ClientKill;
	func_t	ClientConnect;
	func_t	PutClientInServer;
	func_t	ClientDisconnect;
	func_t	SetNewParms;
	func_t	SetChangeParms;*/
} globalvars_t;
#if 0
typedef struct
{
    int	qcc_modelindex;
	vector	qcc_absmin;
	vector	qcc_absmax;
	float	qcc_ltime;
	float	qcc_movetype;
	float	qcc_solid;
	vector	qcc_origin;
	vector	qcc_oldorigin;
	vector	qcc_velocity;
	vector	qcc_angles;
	vector	qcc_avelocity;
	vector	qcc_punchangle;
	string_t	qcc_classname;
	string_t	qcc_model;
	float	qcc_frame;
	float	qcc_skin;           // only 0-2.
	float	qcc_effects;
	vector	qcc_mins;
	vector	qcc_maxs;
	vector	qcc_size;
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	// added
	func_t	qcc_think1;
	vector qcc_finaldest;
	vector qcc_finalangle;
	//
	func_t	qcc_blocked;
	float	qcc_nextthink;
	int	qcc_groundentity;
	float	qcc_health;
	float	qcc_frags;
	float	qcc_weapon;
	string_t	qcc_weaponmodel;
	float	qcc_weaponframe;
	float	qcc_currentammo;
	float	qcc_ammo_shells;
	float	qcc_ammo_nails;
	float	qcc_ammo_rockets;
	float	qcc_ammo_cells;
	float	qcc_items;
	float	qcc_takedamage;
	int	qcc_chain;
	float	qcc_deadflag;
	vector	qcc_view_ofs;
	float	qcc_button0;
	float	qcc_button1;
	float	qcc_button2;
	float	qcc_impulse;
	float	qcc_fixangle;
	vector	qcc_v_angle;
	float	qcc_idealpitch;
	string_t	qcc_netname;
	int	qcc_enemy;
	float	qcc_flags;
	float	qcc_colormap;
	float	qcc_team;
	float	qcc_max_health;
	float	qcc_teleport_time;
	float	qcc_armortype;
	float	qcc_armorvalue;
	float	qcc_waterlevel;
	float	qcc_watertype;
	float	qcc_ideal_yaw;
	float	qcc_yaw_speed;
	int	qcc_aiment;
	int	qcc_goalentity;
	float	qcc_spawnflags;
	string_t	qcc_target;
	string_t	qcc_targetname;
	float	qcc_dmg_take;
	float	qcc_dmg_save;
	int	qcc_dmg_inflictor;
	int	qcc_owner;
	vector	qcc_movedir;
	string_t	qcc_message;
	float	qcc_sounds;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	//
	vector		qcc_dest, qcc_dest1, qcc_dest2;
    float		qcc_wait;			// time from firing to restarting
    float		qcc_delay;			// time from activation to firing
    int		qcc_trigger_field;	// door's trigger entity
    string_t		qcc_noise4;
    //
    //
    // monsters
    //
    float 		qcc_pausetime;
    int 	qcc_movetarget;

} entvars_t;
#else
/* file generated by qcc, do not modify */


typedef struct
{

	short	qcc_self;
	short	qcc_other;
	short	qcc_world;
	float	qcc_time;
	float	qcc_frametime;
	float	qcc_force_retouch;
	string_t	qcc_mapname;
	float	qcc_deathmatch;
	float	qcc_coop;
	float	qcc_teamplay;
	float	qcc_serverflags;
	float	qcc_total_secrets;
	float	qcc_total_monsters;
	float	qcc_found_secrets;
	float	qcc_killed_monsters;
	float	qcc_parm1;
	float	qcc_parm2;
	float	qcc_parm3;
	float	qcc_parm4;
	float	qcc_parm5;
	float	qcc_parm6;
	float	qcc_parm7;
	float	qcc_parm8;
	float	qcc_parm9;
	float	qcc_parm10;
	float	qcc_parm11;
	float	qcc_parm12;
	float	qcc_parm13;
	float	qcc_parm14;
	float	qcc_parm15;
	float	qcc_parm16;
	vector	qcc_v_forward;
	vector	qcc_v_up;
	vector	qcc_v_right;
	float	qcc_trace_allsolid;
	float	qcc_trace_startsolid;
	float	qcc_trace_fraction;
	vector	qcc_trace_endpos;
	vector	qcc_trace_plane_normal;
	float	qcc_trace_plane_dist;
	short	qcc_trace_ent;
	float	qcc_trace_inopen;
	float	qcc_trace_inwater;
	short	qcc_msg_entity;
	string_t	qcc_end_sys_globals;
	float	qcc_movedist;
	float	qcc_gameover;
	string_t	qcc_string_null;
	float	qcc_empty_float;
	short	qcc_newmis;
	short	qcc_activator;
	short	qcc_damage_attacker;
	float	qcc_framecount;
	float	qcc_skill;
	float	qcc_enemy_vis;
	float	qcc_enemy_infront;
	float	qcc_enemy_range;
	float	qcc_enemy_yaw;
	float	qcc_current_yaw;
	short	qcc_sight_entity;
	float	qcc_sight_entity_time;
	short	qcc_multi_ent;
	float	qcc_multi_damage;
	short	qcc_lastspawn;
	short	qcc_bodyque_head;
	float	qcc_modelindex_eyes;
	float	qcc_modelindex_player;
	float	qcc_intermission_running;
	float	qcc_intermission_exittime;
	string_t	qcc_nextmap;
	short	qcc_stemp;
	short	qcc_otemp;
	short	qcc_s;
	short	qcc_old;
	short	qcc_le1;
	short	qcc_le2;
	float	qcc_lightning_end;
	float	qcc_hknight_type;
	short	qcc_shub;
} progsvars_t;

extern AUX_SECTION progsvars_t progs;


#define ENTITY_TYPE int16_t  //note: can be 15 bit SIGNED.  String must be 12 bit signed. Func 11 bit unsigned.
#define MINIMIZE_ENTVARS 1
#if MINIMIZE_ENTVARS
typedef struct
{   // FULL ENTVAR, DO NOT CHANGE
	#if !NO
	float	qcc_pausetime;  // float.
	float	qcc_waitmin;    // float
    float	qcc_dmgtime;        // float
	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
	float	qcc_teleport_time;          // timestamp
	float	qcc_search_time;              // timestamp
	float	qcc_attack_finished;          // timestamp (all?)
	float	qcc_pain_finished;          // timestamp (all?)
	float	qcc_invincible_finished;    // timestamp
	float	qcc_invisible_finished;     // timestamp
	float	qcc_super_damage_finished;  // timestamp
	float	qcc_radsuit_finished;   // timestamp
	float	qcc_invincible_time;    // timestamp
	float	qcc_invincible_sound;   // timestamp
	float	qcc_invisible_time;     // timestamp
	float	qcc_invisible_sound;    // timestamp
	float	qcc_super_time;         // timestamp
	float	qcc_super_sound;        // timestamp
	float	qcc_rad_time;           // timestamp
	float	qcc_fly_sound;          // timestamp
	float	qcc_show_hostile;       // timestamp
	float	qcc_jump_flag;          // just for player, keep float
	float	qcc_swim_flag;          // timestamp. Player
	float	qcc_air_finished;       // timestamp. Only for player
	float	qcc_t_length;       // could be fractional 12p4
	float	qcc_t_width;        // used as timestamp as well :( float
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	short	qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_armortype;              // to be 8.8
	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000

	short	qcc_idealpitch;         // angle ? or what ?
	short	qcc_yaw_speed;              // angle ?
    short	qcc_ideal_yaw;              // angle

	shortVector	qcc_velocity;       // 12p4 ?
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
	shortVector	qcc_view_ofs;       // 12p4

	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_oldorigin;      // 13p3 ?
    shortVector	qcc_dest;           // 13p3
	shortVector	qcc_dest1;          // 13p3
	shortVector	qcc_dest2;          // 13p3
	shortVector	qcc_finaldest;      // 13p3
    shortVector	qcc_pos1;           // 13p3
	shortVector	qcc_pos2;           // 13p3

	shortVector	qcc_angles;         //
    shortVector	qcc_avelocity;      //
    shortVector	qcc_punchangle;     // PLAYER ONLY could be 10.6
    shortVector	qcc_finalangle;     // might be vecint?
    shortVector	qcc_movedir;
    shortVector	qcc_v_angle;
    shortVector	qcc_mangle;
	// entities. Can be 16-bit short pointers.
	ENTITY_TYPE	qcc_enemy;
	ENTITY_TYPE	qcc_dmg_inflictor;
	ENTITY_TYPE	qcc_owner;
	ENTITY_TYPE	qcc_oldenemy;
	ENTITY_TYPE	qcc_goalentity;
	ENTITY_TYPE	qcc_trigger_field;
    ENTITY_TYPE	qcc_movetarget;
    ENTITY_TYPE	qcc_groundentity;       //
    ENTITY_TYPE	qcc_chain;
	string_t	qcc_message;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_noise4;
	string_t	qcc_netname;
	string_t	qcc_target;
	string_t	qcc_targetname;
	string_t	qcc_model;
	string_t	qcc_weaponmodel;
	string_t	qcc_map;
	string_t	qcc_killtarget;
	string_t	qcc_deathtype;
	string_t	qcc_mdl;
	//
	func_t	qcc_th_stand;
	func_t	qcc_th_walk;
	func_t	qcc_th_run;
	func_t	qcc_th_missile;
	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
    func_t	qcc_think1;
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	func_t	qcc_blocked;

	// note: can some of those be uint8 ?
	int32_t	    qcc_health : 16;         // MUST be signed
	uint32_t	qcc_frags  : 16;          // uint16
	uint32_t	qcc_weapon : 16;         // max 4096 for weapons unless these are used in stupid way

	uint32_t	qcc_weaponframe : 16;       // uint16
	uint32_t	qcc_currentammo : 16;       // uint 16
	uint32_t	qcc_ammo_shells : 12;       // uint16
	uint32_t	qcc_ammo_nails : 12;        // uint16
	uint32_t	qcc_ammo_rockets: 12;      // uint16
	uint32_t	qcc_ammo_cells: 12;        // uint16
    //
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2
	uint32_t	qcc_button0  : 1;
	uint32_t	qcc_button1  : 1 ;
	uint32_t	qcc_button2  : 1;
	uint32_t	qcc_impulse : 8;

    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too
	uint32_t	qcc_flags: 13;              // max 4096
	uint32_t	qcc_team    :4  ;           // should be enough
	uint32_t	qcc_max_health : 16;        // fixme
    uint32_t	qcc_armorvalue : 10;         // FIXME enough?
    uint32_t	qcc_waterlevel : 2;         // 0..3
    int32_t	    qcc_watertype : 5;          // negative values up to -14
	uint32_t	qcc_spawnflags : 12;         // max 2048
	int32_t	    qcc_dmg_take : 10;       // 10 bit is enough?

	uint32_t	qcc_sounds : 3; // 0..4
	uint32_t	qcc_style : 6;                  // style between 0 and 63
	uint32_t	qcc_worldtype : 2;  // 0..2
	uint32_t	qcc_lefty : 1;
    uint32_t	qcc_attack_state    : 3;    // max 4
	uint32_t	qcc_walkframe : 8;              // FIXME: 256 is fine?
	uint32_t	qcc_axhitme :1;            // boolean
	uint32_t	qcc_bubble_count:5;   // like 20 is the maximum value
	uint32_t	qcc_fixangle:1;       //it's a boolean!
	uint32_t	qcc_deadflag : 2;      // max 3
	uint32_t	qcc_aflag : 6;          // FIXME: 50 max
	uint32_t	    qcc_dmg : 8;            // FIXME Not known, but very small
	int32_t	    qcc_dmg_save : 10;   // FIXME: how much?
	uint32_t	qcc_cnt : 5;            // FIXME: max 20
    uint32_t	qcc_count :3 ;      // FIXME: i found 4... let put 3 bits (7)
	uint32_t	qcc_lip: 8;        // FIXME saw max is 8
	uint32_t	qcc_state:2;          // 0-3
	uint32_t	qcc_height : 12;         // FIXME set max is larger!
	uint32_t	qcc_healamount : 8; // max 100
	uint32_t	qcc_healtype : 2; // 0-2
	uint32_t	qcc_inpain : 2; // 0 - 2
#endif
} old_entvars_t;
typedef struct
{   // FULL ENTVAR, DO NOT CHANGE
#if !NOT_WORKING
	float	qcc_pausetime;  // float.
	float	qcc_waitmin;    // float
    float	qcc_dmgtime;        // float
	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
	float	qcc_teleport_time;          // timestamp
	float	qcc_search_time;              // timestamp
	float	qcc_attack_finished;          // timestamp (all?)
	float	qcc_pain_finished;          // timestamp (all?)
	float	qcc_invincible_finished;    // timestamp
	float	qcc_invisible_finished;     // timestamp
	float	qcc_super_damage_finished;  // timestamp
	float	qcc_radsuit_finished;   // timestamp
	float	qcc_invincible_time;    // timestamp
	float	qcc_invincible_sound;   // timestamp
	float	qcc_invisible_time;     // timestamp
	float	qcc_invisible_sound;    // timestamp
	float	qcc_super_time;         // timestamp
	float	qcc_super_sound;        // timestamp
	float	qcc_rad_time;           // timestamp
	float	qcc_fly_sound;          // timestamp
	float	qcc_show_hostile;       // timestamp
	float	qcc_jump_flag;          // just for player, keep float
	float	qcc_swim_flag;          // timestamp. Player
	float	qcc_air_finished;       // timestamp. Only for player
	float	qcc_t_length;       // could be fractional 12p4
	float	qcc_t_width;        // used as timestamp as well :( float
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	short	qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_armortype;              // to be 8.8
	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000

	short	qcc_idealpitch;         // angle ? or what ?
	short	qcc_yaw_speed;              // angle ?
    short	qcc_ideal_yaw;              // angle

	shortVector	qcc_velocity;       // 12p4 ?
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
	shortVector	qcc_view_ofs;       // 12p4

	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_oldorigin;      // 13p3 ?
    shortVector	qcc_dest;           // 13p3
	shortVector	qcc_dest1;          // 13p3
	shortVector	qcc_dest2;          // 13p3
	shortVector	qcc_finaldest;      // 13p3
    shortVector	qcc_pos1;           // 13p3
	shortVector	qcc_pos2;           // 13p3

	shortVector	qcc_angles;         //
    shortVector	qcc_avelocity;      //
    shortVector	qcc_punchangle;     // PLAYER ONLY could be 10.6
    shortVector	qcc_finalangle;     // might be vecint?
    shortVector	qcc_movedir;
    shortVector	qcc_v_angle;
    shortVector	qcc_mangle;
	// entities. Can be 16-bit short pointers. Even 15, but still signed.
	ENTITY_TYPE	qcc_enemy;
	ENTITY_TYPE	qcc_dmg_inflictor;
	ENTITY_TYPE	qcc_owner;
	ENTITY_TYPE	qcc_oldenemy;
	ENTITY_TYPE	qcc_goalentity;
	ENTITY_TYPE	qcc_trigger_field;
    ENTITY_TYPE	qcc_movetarget;
    ENTITY_TYPE	qcc_groundentity;       //
    ENTITY_TYPE	qcc_chain;
	string_t	qcc_message;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_noise4;
	string_t	qcc_netname;
	string_t	qcc_target;
	string_t	qcc_targetname;
	string_t	qcc_model;
	string_t	qcc_weaponmodel;
	string_t	qcc_map;
	string_t	qcc_killtarget;
	string_t	qcc_deathtype;
	string_t	qcc_mdl;
	//
	func_t	qcc_th_stand;
	func_t	qcc_th_walk;
	func_t	qcc_th_run;
	func_t	qcc_th_missile;
	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
    func_t	qcc_think1;
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	func_t	qcc_blocked;

	// note: can some of those be uint8 ?
	int32_t	    qcc_health : 16;         // MUST be signed
	uint32_t	qcc_frags  : 16;          // uint16
	uint32_t	qcc_weapon : 16;         // max 4096 for weapons unless these are used in stupid way

	uint32_t	qcc_weaponframe : 16;       // uint16
	uint32_t	qcc_currentammo : 16;       // uint 16
	uint32_t	qcc_ammo_shells : 16;       // uint16
	uint32_t	qcc_ammo_nails : 16;        // uint16
	uint32_t	qcc_ammo_rockets: 16;      // uint16
	uint32_t	qcc_ammo_cells: 16;        // uint16
    //
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2
	uint32_t	qcc_button0  : 1;
	uint32_t	qcc_button1  : 1 ;
	uint32_t	qcc_button2  : 1;
	uint32_t	qcc_impulse : 8;

    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too
	uint32_t	qcc_flags: 13;              // max 4096
	uint32_t	qcc_team    :4  ;           // should be enough
	uint32_t	qcc_max_health : 16;        // fixme
    uint32_t	qcc_armorvalue : 10;         // FIXME enough?
    uint32_t	qcc_waterlevel : 2;         // 0..3
    int32_t	    qcc_watertype : 5;          // negative values up to -14
	uint32_t	qcc_spawnflags : 12;         // max 2048
	int32_t	    qcc_dmg_take : 10;       // 10 bit is enough?

	uint32_t	qcc_sounds : 3; // 0..4
	uint32_t	qcc_style : 6;                  // style between 0 and 63
	uint32_t	qcc_worldtype : 2;  // 0..2
	uint32_t	qcc_lefty : 1;
    uint32_t	qcc_attack_state    : 3;    // max 4
	uint32_t	qcc_walkframe : 8;              // FIXME: 256 is fine?
	uint32_t	qcc_axhitme :1;            // boolean
	uint32_t	qcc_bubble_count:5;   // like 20 is the maximum value
	uint32_t	qcc_fixangle:1;       //it's a boolean!
	uint32_t	qcc_deadflag : 2;      // max 3
	uint32_t	qcc_aflag : 6;          // FIXME: 50 max
	uint32_t	    qcc_dmg : 8;            // FIXME Not known, but very small
	int32_t	    qcc_dmg_save : 10;   // FIXME: how much?
	uint32_t	qcc_cnt : 5;            // FIXME: max 20
    uint32_t	qcc_count :3 ;      // FIXME: i found 4... let put 3 bits (7)
	uint32_t	qcc_lip: 8;        // FIXME saw max is 8
	uint32_t	qcc_state:2;          // 0-3
	uint32_t	qcc_height : 12;         // FIXME set max to 200, but might be higher.
	uint32_t	qcc_healamount : 8; // max 100
	uint32_t	qcc_healtype : 2; // 0-2
	uint32_t	qcc_inpain : 2; // 0 - 2
#else
	float	qcc_pausetime;  // float.
	float	qcc_waitmin;    // float
    float	qcc_dmgtime;        // float
	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
	float	qcc_teleport_time;          // timestamp
	float	qcc_search_time;              // timestamp
	float	qcc_attack_finished;          // timestamp (all?)
	float	qcc_pain_finished;          // timestamp (all?)
	float	qcc_invincible_finished;    // timestamp
	float	qcc_invisible_finished;     // timestamp
	float	qcc_super_damage_finished;  // timestamp
	float	qcc_radsuit_finished;   // timestamp
	float	qcc_invincible_time;    // timestamp
	float	qcc_invincible_sound;   // timestamp
	float	qcc_invisible_time;     // timestamp
	float	qcc_invisible_sound;    // timestamp
	float	qcc_super_time;         // timestamp
	float	qcc_super_sound;        // timestamp
	float	qcc_rad_time;           // timestamp
	float	qcc_fly_sound;          // timestamp
	float	qcc_show_hostile;       // timestamp
	float	qcc_jump_flag;          // just for player, keep float
	float	qcc_swim_flag;          // timestamp. Player
	float	qcc_air_finished;       // timestamp. Only for player
	float	qcc_t_length;       // could be fractional 12p4
	float	qcc_t_width;        // used as timestamp as well :( float

	short	qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_armortype;              // to be 8.8
	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000

	short	qcc_idealpitch;         // angle ? or what ?
	short	qcc_yaw_speed;              // angle ?
    short	qcc_ideal_yaw;              // angle

	vector	qcc_velocity;       // 12p4 ?
	vector	qcc_mins;           // 12p4 ?
	vector	qcc_maxs;           // 12p4 ?
	vector	qcc_view_ofs;       // 12p4

	vector	qcc_origin;         // 13p3 ?
	vector	qcc_oldorigin;      // 13p3 ?
    vector	qcc_dest;           // 13p3
	vector	qcc_dest1;          // 13p3
	vector	qcc_dest2;          // 13p3
	vector	qcc_finaldest;      // 13p3
    vector	qcc_pos1;           // 13p3
	vector	qcc_pos2;           // 13p3

	vector	qcc_angles;         //
    vector	qcc_avelocity;      //
    vector	qcc_punchangle;     // PLAYER ONLY could be 10.6
    vector	qcc_finalangle;     // might be vecint?
    vector	qcc_movedir;
    vector	qcc_v_angle;
    vector	qcc_mangle;
	// entities. Can be 16-bit short pointers.
	ENTITY_TYPE	qcc_enemy;
	ENTITY_TYPE	qcc_dmg_inflictor;
	ENTITY_TYPE	qcc_owner;
	ENTITY_TYPE	qcc_oldenemy;
	ENTITY_TYPE	qcc_goalentity;
	ENTITY_TYPE	qcc_trigger_field;
    ENTITY_TYPE	qcc_movetarget;
    ENTITY_TYPE	qcc_groundentity;       //
    ENTITY_TYPE	qcc_chain;
	string_t	qcc_message;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_noise4;
	string_t	qcc_netname;
	string_t	qcc_target;
	string_t	qcc_targetname;
	string_t	qcc_model;
	string_t	qcc_weaponmodel;
	string_t	qcc_map;
	string_t	qcc_killtarget;
	string_t	qcc_deathtype;
	string_t	qcc_mdl;
	//
	func_t	qcc_th_stand;
	func_t	qcc_th_walk;
	func_t	qcc_th_run;
	func_t	qcc_th_missile;
	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
    func_t	qcc_think1;
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	func_t	qcc_blocked;

	// note: can some of those be uint8 ?
	int32_t	    qcc_health : 16;         // MUST be signed
	uint32_t	qcc_frags  : 16;          // uint16
	uint32_t	qcc_weapon : 16;         // max 4096 for weapons unless these are used in stupid way

	uint32_t	qcc_weaponframe : 16;       // uint16
	uint32_t	qcc_currentammo : 16;       // uint 16
	uint32_t	qcc_ammo_shells : 16;       // uint16
	uint32_t	qcc_ammo_nails : 16;        // uint16
	uint32_t	qcc_ammo_rockets: 16;      // uint16
	uint32_t	qcc_ammo_cells: 16;        // uint16
    //
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2
	uint32_t	qcc_button0  : 1;
	uint32_t	qcc_button1  : 1 ;
	uint32_t	qcc_button2  : 1;
	uint32_t	qcc_impulse : 8;

    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too
	uint32_t	qcc_flags: 13;              // max 4096
	uint32_t	qcc_team    :4  ;           // should be enough
	uint32_t	qcc_max_health : 16;        // fixme
    uint32_t	qcc_armorvalue : 10;         // FIXME enough?
    uint32_t	qcc_waterlevel : 2;         // 0..3
    int32_t	    qcc_watertype : 5;          // negative values up to -14
	uint32_t	qcc_spawnflags : 12;         // max 2048
	int32_t	    qcc_dmg_take : 10;       // 10 bit is enough?

	uint32_t	qcc_sounds : 3; // 0..4
	uint32_t	qcc_style : 6;                  // style between 0 and 63
	uint32_t	qcc_worldtype : 2;  // 0..2
	uint32_t	qcc_lefty : 1;
    uint32_t	qcc_attack_state    : 3;    // max 4
	uint32_t	qcc_walkframe : 8;              // FIXME: 256 is fine?
	uint32_t	qcc_axhitme :1;            // boolean
	uint32_t	qcc_bubble_count:5;   // like 20 is the maximum value
	uint32_t	qcc_fixangle:1;       //it's a boolean!
	uint32_t	qcc_deadflag : 2;      // max 3
	uint32_t	qcc_aflag : 6;          // FIXME: 50 max
	uint32_t	    qcc_dmg : 8;            // FIXME Not known, but very small
	int32_t	    qcc_dmg_save : 10;   // FIXME: how much?
	uint32_t	qcc_cnt : 5;            // FIXME: max 20
    uint32_t	qcc_count :3 ;      // FIXME: i found 4... let put 3 bits (7)
	uint32_t	qcc_lip: 8;        // FIXME saw max is 8
	uint32_t	qcc_state:2;          // 0-3
	uint32_t	qcc_height : 12;         // FIXME set max to 200, but might be higher.
	uint32_t	qcc_healamount : 8; // max 100
	uint32_t	qcc_healtype : 2; // 0-2
	uint32_t	qcc_inpain : 2; // 0 - 2
#endif
} full_entvars_t;
typedef full_entvars_t entvars_t;
// missile_entvars_t
typedef struct
{
	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time

#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif

	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000
	shortVector	qcc_velocity;       // 12p4 ?

	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?

	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_angles;         //

	shortVector	qcc_avelocity;      //
	ENTITY_TYPE	qcc_owner;


	ENTITY_TYPE	qcc_groundentity;       //
	int16_t	qcc_model : 12;
  uint16_t  qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...

	uint32_t	qcc_touch : 11;
	uint32_t	qcc_think : 11;
  uint32_t  qcc_frame : 8;          // FIXME: ENOUGH?
  uint32_t  qcc_waterlevel : 2;         // 0..3

  uint32_t  qcc_solid : 3;          // maxvalue 4
  uint32_t  qcc_flags: 13;              // max 4096
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
  uint32_t  qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too

  uint32_t  qcc_effects:4;        // flag. MAxValue 8. 4 bits.
  int32_t	    qcc_watertype : 5;          // negative values up to -14


} missile_entvars_t;
typedef struct
{
	shortVector	qcc_origin;
} sound_entvars_t;
typedef struct
{
	float	qcc_nextthink;      // time
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;                  //unfortunately it has... We will fix later.
#endif
	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_angles;         //
	shortVector	qcc_velocity;       // 12p4 ?

	ENTITY_TYPE	qcc_owner;

	string_t	qcc_model;
	uint16_t	qcc_modelindex:8;     // can be uint16 or lower
    uint16_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_flags: 13;              // max 4096
    uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_solid : 3;          // maxvalue 4

} bodyque_entvars_t;
typedef struct
{
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
	shortVector qcc_angles;
	//
    func_t	    qcc_use;
    uint16_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint16_t	qcc_modelindex:8;     // can be uint16 or lower


	string_t	qcc_targetname;
	string_t	qcc_model;
	string_t	qcc_target;

    uint16_t	qcc_spawnflags : 10;         // max 2048 but higher bits are handled externally.
    uint16_t	qcc_style : 6;
} light_entvars_t;
//
typedef struct
{
    float	qcc_attack_finished;          // timestamp (all?)
    float	qcc_nextthink;      // time
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	shortVector	qcc_origin;
	shortVector	qcc_angles;         //
  shortVector	qcc_movedir;
  shortVector	qcc_mins;           // 12p4 ?


  shortVector	qcc_maxs;           // 12p4 ?
  short     qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000


  ENTITY_TYPE qcc_owner;
  ENTITY_TYPE qcc_enemy;

  short     qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
  short     qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok

  uint32_t  qcc_max_health : 8;        // FIXME: is enough for triggers?
  int32_t qcc_map : 12;
  int32_t qcc_killtarget : 12;


  int32_t     qcc_health : 8;         // MUST be signed. FIXME TBD: is 8 bit enough for triggers?
  int32_t     qcc_message : 12;
  int32_t     qcc_noise : 12;


  uint32_t  qcc_modelindex:8;     // can be uint16 or lower
  uint32_t  qcc_height : 12;         // FIXME set max to 200, but might be higher.
  uint32_t  qcc_spawnflags : 12;         // max 2048


  int32_t   qcc_target : 12;
  uint32_t  qcc_touch : 11;
  uint32_t  qcc_sounds : 3; // 0..4
  uint32_t  qcc_count :3 ;      // FIXME: i found 4... let put 4 bits (7)
  uint32_t  qcc_solid : 3;          // maxvalue 4


  uint32_t    qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
  uint32_t    qcc_effects:4;        // flag. MAxValue 8. 4 bits.
  uint32_t    qcc_use : 11;
  uint32_t    qcc_think : 11;


  int32_t qcc_targetname : 12;
  int32_t qcc_model : 12;
  uint32_t  qcc_style : 6;
  uint32_t  qcc_takedamage : 2;        // can be 0, 1 or 2


  uint32_t      qcc_th_die : 11;

} trigger_entvars_t;
typedef struct
{
	shortVector	qcc_origin;
	shortVector	qcc_angles;         //
	shortVector	qcc_mangle;         //
	string_t	qcc_targetname;
    uint16_t	qcc_spawnflags : 12;         // max 2048
} info_entvars_t;
typedef struct
{
 	float	qcc_t_length;       // could be fractional 12p4
	float	qcc_t_width;        // used as timestamp as well :( float
    float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
	float	qcc_ltime;          // time
	float	qcc_attack_finished;          // timestamp
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	//
	vector	qcc_origin;
    vector qcc_oldorigin;
	shortVector	qcc_finaldest;      // 13p3
    shortVector	qcc_mangle;
    shortVector	qcc_velocity;       // 12p4 ?
    shortVector	qcc_movedir;

    shortVector	qcc_pos1;           // 13p3
	shortVector	qcc_pos2;           // 13p3
    shortVector	qcc_dest1;           // 13p3
	shortVector	qcc_dest2;           // 13p3

	shortVector	qcc_angles;         //
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
    ENTITY_TYPE	qcc_enemy;

	ENTITY_TYPE	qcc_owner;
	ENTITY_TYPE	qcc_trigger_field;

	string_t	qcc_model;
	string_t	qcc_target;
	string_t	qcc_message;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_noise4;
	string_t	qcc_killtarget;

	string_t	qcc_targetname;
    short	    qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000
	short	    qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	    qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	uint32_t	qcc_height : 12;         // FIXME set max to 200, but might be higher.
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_lip: 8;        // FIXME saw max is 8
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower

	int32_t	    qcc_health : 15;         // MUST be signed. Must be at least 10k for doors. Useless.
    uint32_t	qcc_max_health : 15;        // fixme: needs to be at least 10000 for doors. How useless.
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2

    uint32_t	qcc_spawnflags : 12;         // max 2048
    uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_flags: 13;              // max 4096
    //
    uint32_t	qcc_use : 11;
	uint32_t	qcc_touch : 11;
 	uint32_t	qcc_sounds : 3; // 0..4
	uint32_t	qcc_state:2;          // 0-3
    uint32_t	qcc_cnt : 5;            // FIXME: max 20
    //
 	uint32_t	qcc_think : 11;
	uint32_t	qcc_blocked : 11;
    uint32_t	qcc_frame : 2;          // FIXME: ENOUGH? (for buttons)
    uint32_t	qcc_dmg : 8;            // FIXME Not known, but very small
    //
	uint32_t	qcc_th_die : 11;
    int32_t	    qcc_noise : 16;         // can be less.

	uint32_t	qcc_th_pain : 11;
    uint32_t	qcc_think1 : 11;

} func_entvars_t;

typedef struct
{
	float	qcc_pausetime;  // float.
//	float	qcc_waitmin;    // float
    float	qcc_dmgtime;        // float
//	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
	float	qcc_teleport_time;          // timestamp
//	float	qcc_search_time;              // timestamp
	float	qcc_attack_finished;          // timestamp (all?)
	float	qcc_pain_finished;          // timestamp (all?)
	float	qcc_invincible_finished;    // timestamp
	float	qcc_invisible_finished;     // timestamp
	float	qcc_super_damage_finished;  // timestamp
	float	qcc_radsuit_finished;   // timestamp
	float	qcc_invincible_time;    // timestamp
	float	qcc_invincible_sound;   // timestamp
	float	qcc_invisible_time;     // timestamp
	float	qcc_invisible_sound;    // timestamp
	float	qcc_super_time;         // timestamp
	float	qcc_super_sound;        // timestamp
	float	qcc_rad_time;           // timestamp
//	float	qcc_fly_sound;          // timestamp
	float	qcc_show_hostile;       // timestamp
	float	qcc_jump_flag;          // just for player, keep float
	float	qcc_swim_flag;          // timestamp. Player
	float	qcc_air_finished;       // timestamp. Only for player
//	float	qcc_t_length;       // could be fractional 12p4
//	float	qcc_t_width;        // used as timestamp as well :( float
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
//	short	qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
//	short	qcc_delay;      // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
	short	qcc_armortype;              // to be 8.8
//	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000

	short	qcc_idealpitch;         // angle ? or what ?
//	short	qcc_yaw_speed;              // angle ?
//    short	qcc_ideal_yaw;              // angle

	shortVector	qcc_velocity;       // 12p4 ?
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
	shortVector	qcc_view_ofs;       // 12p4

	vector	qcc_origin;         // for player it is a vector of floats!
	vector	qcc_oldorigin;      //  for player it is a vector of floats!
    shortVector	qcc_dest;           // 13p3
//	shortVector	qcc_dest1;          // 13p3
//	shortVector	qcc_dest2;          // 13p3
//	shortVector	qcc_finaldest;      // 13p3
//    shortVector	qcc_pos1;           // 13p3
//	shortVector	qcc_pos2;           // 13p3

	shortVector	qcc_angles;         //
    shortVector	qcc_avelocity;      //
    shortVector	qcc_punchangle;     // PLAYER ONLY could be 10.6
//    shortVector	qcc_finalangle;     // might be vecint?
    shortVector	qcc_movedir;
    shortVector	qcc_v_angle;
//    shortVector	qcc_mangle;
	// entities. Can be 16-bit short pointers.
	ENTITY_TYPE	qcc_enemy;
	ENTITY_TYPE	qcc_dmg_inflictor;
	ENTITY_TYPE	qcc_owner;
//	ENTITY_TYPE	qcc_oldenemy;
//	ENTITY_TYPE	qcc_goalentity;
//	ENTITY_TYPE	qcc_trigger_field;
//    ENTITY_TYPE	qcc_movetarget;
    ENTITY_TYPE	qcc_groundentity;       //
    ENTITY_TYPE	qcc_chain;
	string_t	qcc_message;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_noise4;
	string_t	qcc_netname;
//	string_t	qcc_target;
	string_t	qcc_targetname;
	string_t	qcc_model;
	string_t	qcc_weaponmodel;
//	string_t	qcc_map;
//	string_t	qcc_killtarget;
	string_t	qcc_deathtype;
//	string_t	qcc_mdl;
	//
//	func_t	qcc_th_stand;
//	func_t	qcc_th_walk;
//	func_t	qcc_th_run;
//	func_t	qcc_th_missile;
//	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
//    func_t	qcc_think1;
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
//	func_t	qcc_blocked;

	// note: can some of those be uint8 ?
	int32_t	    qcc_health : 16;         // MUST be signed
	uint32_t	qcc_frags  : 16;          // uint16
	uint32_t	qcc_weapon : 16;         // max 4096 for weapons unless these are used in stupid way

	uint32_t	qcc_weaponframe : 16;       // uint16
	uint32_t	qcc_currentammo : 16;       // uint 16
	uint32_t	qcc_ammo_shells : 12;       // uint16
	uint32_t	qcc_ammo_nails : 12;        // uint16
	uint32_t	qcc_ammo_rockets: 12;      // uint16
	uint32_t	qcc_ammo_cells: 12;        // uint16
    //
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2
	uint32_t	qcc_button0  : 1;
	uint32_t	qcc_button1  : 1 ;
	uint32_t	qcc_button2  : 1;
	uint32_t	qcc_impulse : 8;

    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too
	uint32_t	qcc_flags: 13;              // max 4096
	uint32_t	qcc_team    :4  ;           // should be enough
	uint32_t	qcc_max_health : 16;        // fixme
    uint32_t	qcc_armorvalue : 10;         // FIXME enough?
    uint32_t	qcc_waterlevel : 2;         // 0..3
    int32_t	    qcc_watertype : 5;          // negative values up to -14
	uint32_t	qcc_spawnflags : 12;         // max 2048
	int32_t	    qcc_dmg_take : 10;       // 10 bit is enough?

//	uint32_t	qcc_sounds : 3; // 0..4
//	uint32_t	qcc_style : 6;                  // style between 0 and 63
//	uint32_t	qcc_worldtype : 2;  // 0..2
//	uint32_t	qcc_lefty : 1;
 //   uint32_t	qcc_attack_state    : 3;    // max 4
	uint32_t	qcc_walkframe : 8;              // FIXME: 256 is fine?
	uint32_t	qcc_axhitme :1;            // boolean
//	uint32_t	qcc_bubble_count:5;   // like 20 is the maximum value
	uint32_t	qcc_fixangle:1;       //it's a boolean!
	uint32_t	qcc_deadflag : 2;      // max 3
//	uint32_t	qcc_aflag : 6;          // FIXME: 50 max
	uint32_t	    qcc_dmg : 8;            // FIXME Not known, but very small
	int32_t	    qcc_dmg_save : 10;   // FIXME: how much?
//	uint32_t	qcc_cnt : 5;            // FIXME: max 20
//    uint32_t	qcc_count :3 ;      // FIXME: i found 4... let put 3 bits (7)
//	uint32_t	qcc_lip: 8;        // FIXME saw max is 8
//	uint32_t	qcc_state:2;          // 0-3
//	uint32_t	qcc_height : 8;         // FIXME set max to 200, but might be higher.
//	uint32_t	qcc_healamount : 8; // max 100
//	uint32_t	qcc_healtype : 2; // 0-2
	uint32_t	qcc_inpain : 2; // 0 - 2
} player_entvars_t;

typedef struct
{
	shortVector	qcc_origin;
	uint16_t	qcc_solid : 3;          // maxvalue 4
    uint16_t	qcc_spawnflags : 12;         // max 2048

	string_t	qcc_target;
	string_t	qcc_targetname;
//   ENTITY_TYPE	qcc_chain;
//    uint16_t    minmaxssize : 8;
	short	qcc_wait;       // this is normally a small value, but it might be decimal, so need a different handling. Probably 8p8 would be ok
} path_corner_entvars_t;
typedef struct
{
	float	qcc_nextthink;      // time
	float	qcc_items;             // MUST BE 32 BITS
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
    shortVector	qcc_origin;
	shortVector	qcc_velocity;       // 12p4 ?
    shortVector qcc_oldorigin;
    shortVector qcc_mins;
    shortVector qcc_maxs;
    shortVector qcc_angles;
    

    int32_t	   qcc_groundentity : 15;       //
	uint32_t	qcc_weapon : 12;         // max 4096 for weapons unless these are used in stupid way
    int32_t	    qcc_watertype : 5;          // negative values up to -14
	//
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_spawnflags : 4;         // max 2048 but bits 8..11 are just evaluated during level load. And I see using only 0..15
	int32_t	qcc_targetname : 12;
    int32_t    qcc_netname : 12;
//
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	int32_t	qcc_model : 12;
    int32_t    qcc_mdl : 12;
//
    int32_t	qcc_noise : 12;
	uint32_t	qcc_healtype : 2; // 0-2
    uint32_t	qcc_healamount : 7; // max 100
    uint32_t      qcc_touch : 11;

    //
	uint32_t	qcc_sounds : 3; // 0..4
	uint32_t	qcc_skin : 2;           // FIXME: is it enough?
  uint32_t  qcc_flags : 12;          // ITEMS have 256,
  int32_t     qcc_owner : 15;
    //
   uint32_t      qcc_think: 11;
	int32_t	qcc_target : 12;
  uint32_t    qcc_waterlevel : 2;
	uint32_t	qcc_solid : 1;          // items are only SOLID_TRIGGER
	uint32_t	qcc_aflag : 6;          // FIXME: 50 max
}   item_entvars_t;
//typedef full_entvars_t func_entvars_t;
//typedef entvars_t missile_entvars_t;
typedef struct
{
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;                  //unfortunately it has... We will fix later.
#endif
	shortVector	qcc_origin;
    shortVector qcc_mins;
    shortVector qcc_maxs;
    int16_t	qcc_message :14;
	uint16_t	qcc_worldtype : 2;  // 0..2
    //
    int32_t	    qcc_model : 14;
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_sounds : 3; // 0..4
    uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...

} worldspawn_entvars_t;
typedef struct
{
    float	qcc_nextthink;      // time
    func_t qcc_think;
    string_t	qcc_message;
	string_t	qcc_killtarget;
	string_t	qcc_target;
	ENTITY_TYPE	qcc_enemy;
} delayedUse_entvars_t;
typedef struct
{
    float	qcc_items;             // MUST BE 32 BITS
    float	qcc_nextthink;      // time
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
    //
    shortVector	qcc_origin;
    shortVector	qcc_oldorigin;
    shortVector	qcc_velocity;
    shortVector qcc_angles;
    //
    shortVector qcc_mins;
    shortVector qcc_maxs;

 	string_t	qcc_model;
    func_t qcc_touch;
    func_t qcc_think;
    ENTITY_TYPE	qcc_groundentity;       //

	uint32_t	qcc_ammo_shells : 12;       // uint16  can be smaller as well.
	uint32_t	qcc_ammo_nails : 12;        // uint16
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower

	uint32_t	qcc_ammo_rockets: 12;      // uint16
	uint32_t	qcc_ammo_cells: 12;        // uint16
	uint32_t	qcc_solid : 3;          // maxvalue
    int32_t	    qcc_watertype : 5;          // negative values up to -14

 	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	uint32_t	qcc_flags: 13;              // max 4096
    uint32_t	qcc_waterlevel : 2;         // 0..3

} nh_backpack_entvars_t;
typedef struct
{
    float	qcc_nextthink;      // time
    shortVector	qcc_origin;
    func_t qcc_think;
} nh_tfog_entvars_t;
typedef struct
{
    float	qcc_nextthink;      // time
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
    shortVector	qcc_origin;
    shortVector	qcc_velocity;
    shortVector	qcc_oldorigin;
    shortVector qcc_mins;
    shortVector qcc_maxs;
    shortVector	qcc_angles;

    func_t qcc_think;
    func_t qcc_th_die;
    func_t qcc_touch;
    ENTITY_TYPE	qcc_chain;
    ENTITY_TYPE	qcc_groundentity;       //

	string_t	qcc_model;
	uint16_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
   	uint16_t	qcc_spawnflags : 12;         // max 2048

	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_sounds : 3; // 0..4

	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2

	int32_t	qcc_health : 16;        //  must be signed
	uint32_t	qcc_flags: 13;              // max 4096
    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?

} explo_box_entvars_t;
typedef struct
{
	float	qcc_air_finished;       // timestamp. Only for player

        float	qcc_nextthink;      // time
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
    shortVector	qcc_origin;
    shortVector	qcc_velocity;
//    shortVector	qcc_oldorigin;
    shortVector qcc_mins;
    shortVector qcc_maxs;
//    shortVector	qcc_angles;

    func_t qcc_think;
//    func_t qcc_th_die;
    func_t qcc_touch;
//    ENTITY_TYPE	qcc_chain;
//    ENTITY_TYPE	qcc_groundentity;       //
	ENTITY_TYPE	qcc_owner;

	string_t	qcc_model;
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
//   	uint16_t	qcc_spawnflags : 12;         // max 2048

	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
	uint32_t	qcc_solid : 3;          // maxvalue 4
//	uint32_t	qcc_sounds : 3; // 0..4

    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint32_t	qcc_bubble_count:5;   // like 20 is the maximum value
	uint32_t	qcc_cnt : 5;            // FIXME: max 20
} bubble_entvars_t;
typedef struct
{
    float	qcc_nextthink;      // time
    shortVector	qcc_origin;
    shortVector qcc_mins;
    shortVector qcc_maxs;
    func_t qcc_think;
    uint16_t qcc_touch : 13;            //can be 11
	uint16_t	qcc_solid : 3;          // maxvalue 4

	ENTITY_TYPE	qcc_owner;
} teledeath_entvars_t;
typedef struct
{
    float	qcc_nextthink;      // time
    func_t qcc_think;
} timer_entvars_t;
typedef struct
{
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	float	qcc_show_hostile;       // timestamp
    float	qcc_search_time;              // timestamp
    float	qcc_pausetime;              // timestamp
    float	qcc_attack_finished;          // timestamp (all?)
    float	qcc_pain_finished;          // timestamp (all?)
    float	qcc_waitmin;    // float
    float	qcc_nextthink;      // time

    //
//    shortVector	qcc_origin;
//    shortVector	qcc_oldorigin;
    vector	qcc_origin;
    vector	qcc_oldorigin;

    shortVector qcc_mins;
    shortVector qcc_maxs;
    shortVector	qcc_velocity;
    shortVector	qcc_angles;
    shortVector	qcc_avelocity;      //
    shortVector	qcc_movedir;

    shortVector qcc_view_ofs;
	ENTITY_TYPE	qcc_enemy;
	//
	ENTITY_TYPE	qcc_oldenemy;
	ENTITY_TYPE	qcc_goalentity;
    ENTITY_TYPE	qcc_movetarget;
    ENTITY_TYPE	qcc_groundentity;       //
    //
    //
	string_t	qcc_targetname;
    string_t	qcc_model;
    ENTITY_TYPE	qcc_chain;
    short	qcc_yaw_speed;              // angle ?
    //
    int32_t	    qcc_killtarget : 12;
    uint32_t	qcc_spawnflags : 5;         // max 2048 but top bits are dealt with externally. And actually I don't see using too many low bits
    int32_t     qcc_owner :  15;
    //
    short	qcc_ideal_yaw;              // angle
    short      qcc_max_health;        //
    //
	uint32_t	qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...
	int32_t	    qcc_target : 12;
	int32_t	    qcc_health : 16;         // MUST be signed

    uint32_t	qcc_flags: 13;              // max 4096
	uint32_t	qcc_solid : 3;          // maxvalue 4
	uint32_t	qcc_modelindex:8;     // can be uint16 or lower
    uint32_t	qcc_frame : 8;          // FIXME: ENOUGH?

    uint32_t	qcc_ammo_shells : 7;       // uint16
    uint32_t    qcc_think : 11;
    uint32_t    qcc_touch : 11;
    uint32_t	qcc_attack_state    : 3;    // max 4

	uint32_t	qcc_ammo_nails : 7;        // uint16
    uint32_t	qcc_th_stand : 11;
	uint32_t	qcc_th_walk : 11;
    uint32_t	qcc_waterlevel : 2;         // 0..3
    uint32_t	qcc_lefty : 1;


	uint32_t	qcc_th_run : 11;
	uint32_t	qcc_th_missile : 11;
	uint32_t	qcc_cnt : 5;            // FIXME: max 20
    int32_t	    qcc_watertype : 5;          // negative values up to -14

	uint32_t	qcc_ammo_cells: 7;        // uint16
	uint32_t	qcc_inpain : 2; // 0 - 2
    uint32_t	qcc_axhitme :1;            // boolean
	uint32_t	qcc_th_melee : 11;
	uint32_t	qcc_th_pain : 11;

	uint32_t	qcc_th_die : 11;
	uint32_t	qcc_use : 11;
	uint32_t	qcc_ammo_rockets: 4;      // uint16
	uint32_t	qcc_takedamage : 2;        // can be 0, 1 or 2
	uint32_t	qcc_effects:4;        // flag. MAxValue 8. 4 bits.

} monster_entvars_t;
typedef struct
{
#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?
  shortVector qcc_angles;           // 12p4 ?

    //
    uint16_t	qcc_frame : 8;          // FIXME: ENOUGH?
	uint16_t	qcc_modelindex:8;     // can be uint16 or lower


    func_t	    qcc_use;
	string_t	    qcc_targetname;
    string_t	    qcc_model;
	string_t	qcc_target;

    uint32_t	qcc_spawnflags : 12;         // max 2048
    uint32_t	qcc_style : 6;
} static_light_romEntvars_t;
typedef struct
{
    static_light_romEntvars_t *romEntvars;
} static_light_entvars_t;

typedef struct
{
	float	qcc_ltime;          // time
	float	qcc_nextthink;      // time

#if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif

	short	qcc_speed;                   // can be uint16_t. Will be fractional 12p4 Max is like 2000
	shortVector	qcc_velocity;       // 12p4 ?

	shortVector	qcc_mins;           // 12p4 ?
	shortVector	qcc_maxs;           // 12p4 ?

	shortVector	qcc_origin;         // 13p3 ?
	shortVector	qcc_angles;         //

	shortVector	qcc_movedir;      //    instead of avelocity, which should be 0.
	ENTITY_TYPE	qcc_owner;


	ENTITY_TYPE	qcc_groundentity;       //
	int16_t	qcc_model : 12;
  uint16_t  qcc_movetype : 4;       // maxvalue 10: can be a 4 bit...

	uint32_t	qcc_touch : 11;
	uint32_t	qcc_think : 11;
  uint32_t  qcc_frame : 8;          // FIXME: ENOUGH?
  uint32_t  qcc_waterlevel : 2;         // 0..3

  uint32_t  qcc_solid : 3;          // maxvalue 4
  uint32_t  qcc_flags: 13;              // max 4096
  uint32_t	qcc_modelindex:8;     // can be uint16 or lower
  uint32_t  qcc_skin:8;           // FIXME: sure is enough, probably smaller is ok too

  uint32_t  qcc_effects:4;        // flag. MAxValue 8. 4 bits.
  int32_t	    qcc_watertype : 5;          // negative values up to -14
  int32_t       qcc_enemy : 15;

} nh_wiz_startfast_entvars_t;

#else
typedef struct
{
	float	qcc_modelindex;     // can be uint16 or lower
#if USE_ABS_MAXMIN
	vector	qcc_absmin;         // difficult to remove
	vector	qcc_absmax;         // idem
#endif
	float	qcc_ltime;          //
	float	qcc_movetype;       // maxvalue 10: can be a 4 bit...
	float	qcc_solid;          // maxvalue 3
	vector	qcc_origin;         //
	vector	qcc_oldorigin;
	vector	qcc_velocity;
	shortVector	qcc_angles;         // could be 10.6...
	vector	qcc_avelocity;      // could be 8p8 ?
	vector	qcc_punchangle;     // could be 10.6
	//string_t	qcc_classname;  // NOT USED, IT IS HERE ONLY ON ENTVARS_
	string_t	qcc_model;
	float	qcc_frame;          // sure is not float. 16 bit enough
	float	qcc_skin;           // idem
	float	qcc_effects;        // flag. MAxValue 8. 4 bits.
	vector	qcc_mins;           //
	vector	qcc_maxs;
#if USE_QCC_SIZE
	vector	qcc_size;
#endif
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	func_t	qcc_blocked;
	float	qcc_nextthink;      // time ?
	int	qcc_groundentity;       //
	float	qcc_health;         // could be uint16?
	float	qcc_frags;          // uint16
	float	qcc_weapon;         // much smaller
	string_t	qcc_weaponmodel;
	float	qcc_weaponframe;       // uint16
	float	qcc_currentammo;       // uint 16
	float	qcc_ammo_shells;       // uint16
	float	qcc_ammo_nails;        // uint16
	float	qcc_ammo_rockets;      // uint16
	float	qcc_ammo_cells;        // uint16
	float	qcc_items;             // uint16
	float	qcc_takedamage;        // ?
	int	qcc_chain;
	float	qcc_deadflag;
	vector	qcc_view_ofs;
	float	qcc_button0;
	float	qcc_button1;
	float	qcc_button2;
	float	qcc_impulse;
	float	qcc_fixangle;
	vector	qcc_v_angle;
	float	qcc_idealpitch;
	string_t	qcc_netname;
	int	qcc_enemy;
	float	qcc_flags;
//	float	qcc_colormap;           //always 0 for all, as I see. Except for multipalyer, and at this point we can change it to be as set.
	float	qcc_team;
	float	qcc_max_health;
	float	qcc_teleport_time;
	float	qcc_armortype;
	float	qcc_armorvalue;
	float	qcc_waterlevel;
	float	qcc_watertype;
	float	qcc_ideal_yaw;
	float	qcc_yaw_speed;
	int	qcc_aiment;
	int	qcc_goalentity;
	float	qcc_spawnflags;
	string_t	qcc_target;
	string_t	qcc_targetname;
	float	qcc_dmg_take;
	float	qcc_dmg_save;
	int	qcc_dmg_inflictor;
	int	qcc_owner;
	vector	qcc_movedir;
	string_t	qcc_message;
	float	qcc_sounds;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_wad;
	string_t	qcc_map;
	float	qcc_worldtype;
	string_t	qcc_killtarget;
	float	qcc_light_lev;
	float	qcc_style;
	func_t	qcc_th_stand;
	func_t	qcc_th_walk;
	func_t	qcc_th_run;
	func_t	qcc_th_missile;
	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
	int	qcc_oldenemy;
	float	qcc_speed;      // can be uint16_t. Max is like 2000
	float	qcc_lefty;
	float	qcc_search_time;
	float	qcc_attack_state;
	float	qcc_walkframe;
	float	qcc_attack_finished;
	float	qcc_pain_finished;
	float	qcc_invincible_finished;
	float	qcc_invisible_finished;
	float	qcc_super_damage_finished;
	float	qcc_radsuit_finished;
	float	qcc_invincible_time;
	float	qcc_invincible_sound;
	float	qcc_invisible_time;
	float	qcc_invisible_sound;
	float	qcc_super_time;
	float	qcc_super_sound;
	float	qcc_rad_time;
	float	qcc_fly_sound;
	float	qcc_axhitme;
	float	qcc_show_hostile;
	float	qcc_jump_flag;
	float	qcc_swim_flag;
	float	qcc_air_finished;
	float	qcc_bubble_count;
	string_t	qcc_deathtype;
	string_t	qcc_mdl;
	vector	qcc_mangle;
	float	qcc_t_length;
	float	qcc_t_width;
	vector	qcc_dest;
	vector	qcc_dest1;
	vector	qcc_dest2;
	float	qcc_wait;
	float	qcc_delay;
	int	qcc_trigger_field;
	string_t	qcc_noise4;
	float	qcc_pausetime;
	int	qcc_movetarget;
	float	qcc_aflag;
	float	qcc_dmg;
	float	qcc_cnt;
	func_t	qcc_think1;
	vector	qcc_finaldest;      // might be vecint?
	vector	qcc_finalangle;     // might be vecint?
	float	qcc_count;
	float	qcc_lip;
	float	qcc_state;
	vector	qcc_pos1;
	vector	qcc_pos2;
	float	qcc_height;
	float	qcc_waitmin;
	float	qcc_waitmax;
	float	qcc_distance;
	float	qcc_volume;
	float	qcc_healamount;
	float	qcc_healtype;
	float	qcc_hit_z;
	float	qcc_dmgtime;
	float	qcc_inpain;
} entvars_t;
#endif
#if 1
// DO NOT MODIFY THE FOLLOWING!
typedef struct
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
    entLeaves_t entLeaves;
#endif
	float	qcc_modelindex;     // can be uint16 or lower
#if USE_ABS_MAXMIN
	vector	qcc_absmin;         // difficult to remove
	vector	qcc_absmax;         // idem
#endif
	float	qcc_ltime;          //
	float	qcc_movetype;       // maxvalue 10: can be a 4 bit...
	float	qcc_solid;          // maxvalue 3
	vector	qcc_origin;         //
	vector	qcc_oldorigin;
	vector	qcc_velocity;
	vector	qcc_angles;         // could be 10.6...
	vector	qcc_avelocity;      // could be 8p8 ?
	vector	qcc_punchangle;     // could be 10.6
	string_t	qcc_classname;  // NOT USED, IT IS HERE ONLY for offsetof(big_entvars_t) purpose.
	string_t	qcc_model;
	float	qcc_frame;          // sure is not float. 16 bit enough
	float	qcc_skin;           // 0-2. 2 bits.
	float	qcc_effects;        // flag. MAxValue 8. 4 bits.
	vector	qcc_mins;           //
	vector	qcc_maxs;
#if USE_QCC_SIZE
	vector	qcc_size;
#endif
	func_t	qcc_touch;
	func_t	qcc_use;
	func_t	qcc_think;
	func_t	qcc_blocked;
	float	qcc_nextthink;      // time ?
	int	qcc_groundentity;       //
	float	qcc_health;         // could be uint16?
	float	qcc_frags;          // uint16
	float	qcc_weapon;         // much smaller
	string_t	qcc_weaponmodel;
	float	qcc_weaponframe;       // uint16
	float	qcc_currentammo;       // uint 16
	float	qcc_ammo_shells;       // uint16
	float	qcc_ammo_nails;        // uint16
	float	qcc_ammo_rockets;      // uint16
	float	qcc_ammo_cells;        // uint16
	float	qcc_items;             // uint16
	float	qcc_takedamage;        // ?
	int	qcc_chain;
	float	qcc_deadflag;
	vector	qcc_view_ofs;
	float	qcc_button0;
	float	qcc_button1;
	float	qcc_button2;
	float	qcc_impulse;
	float	qcc_fixangle;
	vector	qcc_v_angle;
	float	qcc_idealpitch;
	string_t	qcc_netname;
	int	qcc_enemy;
	float	qcc_flags;
	float	qcc_colormap;
	float	qcc_team;
	float	qcc_max_health;
	float	qcc_teleport_time;
	float	qcc_armortype;
	float	qcc_armorvalue;
	float	qcc_waterlevel;
	float	qcc_watertype;
	float	qcc_ideal_yaw;
	float	qcc_yaw_speed;
	int	qcc_aiment;
	int	qcc_goalentity;
	float	qcc_spawnflags;
	string_t	qcc_target;
	string_t	qcc_targetname;
	float	qcc_dmg_take;
	float	qcc_dmg_save;
	int	qcc_dmg_inflictor;
	int	qcc_owner;
	vector	qcc_movedir;
	string_t	qcc_message;
	float	qcc_sounds;
	string_t	qcc_noise;
	string_t	qcc_noise1;
	string_t	qcc_noise2;
	string_t	qcc_noise3;
	string_t	qcc_wad;
	string_t	qcc_map;
	float	qcc_worldtype;
	string_t	qcc_killtarget;
	float	qcc_light_lev;
	float	qcc_style;
	func_t	qcc_th_stand;
	func_t	qcc_th_walk;
	func_t	qcc_th_run;
	func_t	qcc_th_missile;
	func_t	qcc_th_melee;
	func_t	qcc_th_pain;
	func_t	qcc_th_die;
	int	qcc_oldenemy;
	float	qcc_speed;
	float	qcc_lefty;
	float	qcc_search_time;
	float	qcc_attack_state;
	float	qcc_walkframe;
	float	qcc_attack_finished;
	float	qcc_pain_finished;
	float	qcc_invincible_finished;
	float	qcc_invisible_finished;
	float	qcc_super_damage_finished;
	float	qcc_radsuit_finished;
	float	qcc_invincible_time;
	float	qcc_invincible_sound;
	float	qcc_invisible_time;
	float	qcc_invisible_sound;
	float	qcc_super_time;
	float	qcc_super_sound;
	float	qcc_rad_time;
	float	qcc_fly_sound;
	float	qcc_axhitme;
	float	qcc_show_hostile;
	float	qcc_jump_flag;
	float	qcc_swim_flag;
	float	qcc_air_finished;
	float	qcc_bubble_count;
	string_t	qcc_deathtype;
	string_t	qcc_mdl;
	vector	qcc_mangle;
	float	qcc_t_length;
	float	qcc_t_width;
	vector	qcc_dest;
	vector	qcc_dest1;
	vector	qcc_dest2;
	float	qcc_wait;
	float	qcc_delay;
	int	qcc_trigger_field;
	string_t	qcc_noise4;
	float	qcc_pausetime;
	int	qcc_movetarget;
	float	qcc_aflag;
	float	qcc_dmg;
	float	qcc_cnt;
	func_t	qcc_think1;
	vector	qcc_finaldest;      // might be vecint?
	vector	qcc_finalangle;     // might be vecint?
	float	qcc_count;
	float	qcc_lip;
	float	qcc_state;
	vector	qcc_pos1;
	vector	qcc_pos2;
	float	qcc_height;
	float	qcc_waitmin;
	float	qcc_waitmax;
	float	qcc_distance;
	float	qcc_volume;
	float	qcc_healamount;
	float	qcc_healtype;
	float	qcc_hit_z;
	float	qcc_dmgtime;
	float	qcc_inpain;
} big_entvars_t; // do not modify!
//typedef big_entvars_t test_entvars_t;
#endif
#endif
#endif
#endif // PROGSDEFQ1_H
