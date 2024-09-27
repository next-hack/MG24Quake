// Field definitions for quake edicts
/*
 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments)

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
// this file is created by copy and pasting data from entList.xlsx present in the v101qc\ subfolder of QuakeCConverter project.
#define qcc_modelindex_index    0
#define qcc_absmin_index    1
#define qcc_absmax_index    2
#define qcc_ltime_index    3
#define qcc_movetype_index    4
#define qcc_solid_index    5
#define qcc_origin_index    6
#define qcc_oldorigin_index    7
#define qcc_velocity_index    8
#define qcc_angles_index    9
#define qcc_avelocity_index    10
#define qcc_punchangle_index    11
#define qcc_classname_index    12
#define qcc_model_index    13
#define qcc_frame_index    14
#define qcc_skin_index    15
#define qcc_effects_index    16
#define qcc_mins_index    17
#define qcc_maxs_index    18
#define qcc_size_index    19
#define qcc_touch_index    20
#define qcc_use_index    21
#define qcc_think_index    22
#define qcc_blocked_index    23
#define qcc_nextthink_index    24
#define qcc_groundentity_index    25
#define qcc_health_index    26
#define qcc_frags_index    27
#define qcc_weapon_index    28
#define qcc_weaponmodel_index    29
#define qcc_weaponframe_index    30
#define qcc_currentammo_index    31
#define qcc_ammo_shells_index    32
#define qcc_ammo_nails_index    33
#define qcc_ammo_rockets_index    34
#define qcc_ammo_cells_index    35
#define qcc_items_index    36
#define qcc_takedamage_index    37
#define qcc_chain_index    38
#define qcc_deadflag_index    39
#define qcc_view_ofs_index    40
#define qcc_button0_index    41
#define qcc_button1_index    42
#define qcc_button2_index    43
#define qcc_impulse_index    44
#define qcc_fixangle_index    45
#define qcc_v_angle_index    46
#define qcc_idealpitch_index    47
#define qcc_netname_index    48
#define qcc_enemy_index    49
#define qcc_flags_index    50
#define qcc_colormap_index    51
#define qcc_team_index    52
#define qcc_max_health_index    53
#define qcc_teleport_time_index    54
#define qcc_armortype_index    55
#define qcc_armorvalue_index    56
#define qcc_waterlevel_index    57
#define qcc_watertype_index    58
#define qcc_ideal_yaw_index    59
#define qcc_yaw_speed_index    60
#define qcc_aiment_index    61
#define qcc_goalentity_index    62
#define qcc_spawnflags_index    63
#define qcc_target_index    64
#define qcc_targetname_index    65
#define qcc_dmg_take_index    66
#define qcc_dmg_save_index    67
#define qcc_dmg_inflictor_index    68
#define qcc_owner_index    69
#define qcc_movedir_index    70
#define qcc_message_index    71
#define qcc_sounds_index    72
#define qcc_noise_index    73
#define qcc_noise1_index    74
#define qcc_noise2_index    75
#define qcc_noise3_index    76
#define qcc_wad_index    77
#define qcc_map_index    78
#define qcc_worldtype_index    79
#define qcc_killtarget_index    80
#define qcc_light_lev_index    81
#define qcc_style_index    82
#define qcc_th_stand_index    83
#define qcc_th_walk_index    84
#define qcc_th_run_index    85
#define qcc_th_missile_index    86
#define qcc_th_melee_index    87
#define qcc_th_pain_index    88
#define qcc_th_die_index    89
#define qcc_oldenemy_index    90
#define qcc_speed_index    91
#define qcc_lefty_index    92
#define qcc_search_time_index    93
#define qcc_attack_state_index    94
#define qcc_walkframe_index    95
#define qcc_attack_finished_index    96
#define qcc_pain_finished_index    97
#define qcc_invincible_finished_index    98
#define qcc_invisible_finished_index    99
#define qcc_super_damage_finished_index    100
#define qcc_radsuit_finished_index    101
#define qcc_invincible_time_index    102
#define qcc_invincible_sound_index    103
#define qcc_invisible_time_index    104
#define qcc_invisible_sound_index    105
#define qcc_super_time_index    106
#define qcc_super_sound_index    107
#define qcc_rad_time_index    108
#define qcc_fly_sound_index    109
#define qcc_axhitme_index    110
#define qcc_show_hostile_index    111
#define qcc_jump_flag_index    112
#define qcc_swim_flag_index    113
#define qcc_air_finished_index    114
#define qcc_bubble_count_index    115
#define qcc_deathtype_index    116
#define qcc_mdl_index    117
#define qcc_mangle_index    118
#define qcc_t_length_index    119
#define qcc_t_width_index    120
#define qcc_dest_index    121
#define qcc_dest1_index    122
#define qcc_dest2_index    123
#define qcc_wait_index    124
#define qcc_delay_index    125
#define qcc_trigger_field_index    126
#define qcc_noise4_index    127
#define qcc_pausetime_index    128
#define qcc_movetarget_index    129
#define qcc_aflag_index    130
#define qcc_dmg_index    131
#define qcc_cnt_index    132
#define qcc_think1_index    133
#define qcc_finaldest_index    134
#define qcc_finalangle_index    135
#define qcc_count_index    136
#define qcc_lip_index    137
#define qcc_state_index    138
#define qcc_pos1_index    139
#define qcc_pos2_index    140
#define qcc_height_index    141
#define qcc_waitmin_index    142
#define qcc_waitmax_index    143
#define qcc_distance_index    144
#define qcc_volume_index    145
#define qcc_healamount_index    146
#define qcc_healtype_index    147
#define qcc_hit_z_index    148
#define qcc_dmgtime_index    149
#define qcc_inpain_index    150
#define entLeaves_index    151
#define qcc_max_field_index    152

#include "progs.h"
const char *qcc_fieldNames[] = {
    "qcc_modelindex",
    "qcc_absmin",
    "qcc_absmax",
    "qcc_ltime",
    "qcc_movetype",
    "qcc_solid",
    "qcc_origin",
    "qcc_oldorigin",
    "qcc_velocity",
    "qcc_angles",
    "qcc_avelocity",
    "qcc_punchangle",
    "qcc_classname",
    "qcc_model",
    "qcc_frame",
    "qcc_skin",
    "qcc_effects",
    "qcc_mins",
    "qcc_maxs",
    "qcc_size",
    "qcc_touch",
    "qcc_use",
    "qcc_think",
    "qcc_blocked",
    "qcc_nextthink",
    "qcc_groundentity",
    "qcc_health",
    "qcc_frags",
    "qcc_weapon",
    "qcc_weaponmodel",
    "qcc_weaponframe",
    "qcc_currentammo",
    "qcc_ammo_shells",
    "qcc_ammo_nails",
    "qcc_ammo_rockets",
    "qcc_ammo_cells",
    "qcc_items",
    "qcc_takedamage",
    "qcc_chain",
    "qcc_deadflag",
    "qcc_view_ofs",
    "qcc_button0",
    "qcc_button1",
    "qcc_button2",
    "qcc_impulse",
    "qcc_fixangle",
    "qcc_v_angle",
    "qcc_idealpitch",
    "qcc_netname",
    "qcc_enemy",
    "qcc_flags",
    "qcc_colormap",
    "qcc_team",
    "qcc_max_health",
    "qcc_teleport_time",
    "qcc_armortype",
    "qcc_armorvalue",
    "qcc_waterlevel",
    "qcc_watertype",
    "qcc_ideal_yaw",
    "qcc_yaw_speed",
    "qcc_aiment",
    "qcc_goalentity",
    "qcc_spawnflags",
    "qcc_target",
    "qcc_targetname",
    "qcc_dmg_take",
    "qcc_dmg_save",
    "qcc_dmg_inflictor",
    "qcc_owner",
    "qcc_movedir",
    "qcc_message",
    "qcc_sounds",
    "qcc_noise",
    "qcc_noise1",
    "qcc_noise2",
    "qcc_noise3",
    "qcc_wad",
    "qcc_map",
    "qcc_worldtype",
    "qcc_killtarget",
    "qcc_light_lev",
    "qcc_style",
    "qcc_th_stand",
    "qcc_th_walk",
    "qcc_th_run",
    "qcc_th_missile",
    "qcc_th_melee",
    "qcc_th_pain",
    "qcc_th_die",
    "qcc_oldenemy",
    "qcc_speed",
    "qcc_lefty",
    "qcc_search_time",
    "qcc_attack_state",
    "qcc_walkframe",
    "qcc_attack_finished",
    "qcc_pain_finished",
    "qcc_invincible_finished",
    "qcc_invisible_finished",
    "qcc_super_damage_finished",
    "qcc_radsuit_finished",
    "qcc_invincible_time",
    "qcc_invincible_sound",
    "qcc_invisible_time",
    "qcc_invisible_sound",
    "qcc_super_time",
    "qcc_super_sound",
    "qcc_rad_time",
    "qcc_fly_sound",
    "qcc_axhitme",
    "qcc_show_hostile",
    "qcc_jump_flag",
    "qcc_swim_flag",
    "qcc_air_finished",
    "qcc_bubble_count",
    "qcc_deathtype",
    "qcc_mdl",
    "qcc_mangle",
    "qcc_t_length",
    "qcc_t_width",
    "qcc_dest",
    "qcc_dest1",
    "qcc_dest2",
    "qcc_wait",
    "qcc_delay",
    "qcc_trigger_field",
    "qcc_noise4",
    "qcc_pausetime",
    "qcc_movetarget",
    "qcc_aflag",
    "qcc_dmg",
    "qcc_cnt",
    "qcc_think1",
    "qcc_finaldest",
    "qcc_finalangle",
    "qcc_count",
    "qcc_lip",
    "qcc_state",
    "qcc_pos1",
    "qcc_pos2",
    "qcc_height",
    "qcc_waitmin",
    "qcc_waitmax",
    "qcc_distance",
    "qcc_volume",
    "qcc_healamount",
    "qcc_healtype",
    "qcc_hit_z",
    "qcc_dmgtime",
    "qcc_inpain",
    "entLeaves",
    "qcc_max_field",
};
const char *qcc_fieldTypes[] =
{
    [qcc_modelindex_index] =  "float",
    [qcc_absmin_index] =  "vector",
    [qcc_absmax_index] =  "vector",
    [qcc_ltime_index] =  "float",
    [qcc_movetype_index] =  "float",
    [qcc_solid_index] =  "float",
    [qcc_origin_index] =  "vector",
    [qcc_oldorigin_index] =  "vector",
    [qcc_velocity_index] =  "vector",
    [qcc_angles_index] =  "vector",
    [qcc_avelocity_index] =  "vector",
    [qcc_punchangle_index] =  "vector",
    [qcc_classname_index] =  "string_t",
    [qcc_model_index] =  "string_t",
    [qcc_frame_index] =  "float",
    [qcc_skin_index] =  "float",
    [qcc_effects_index] =  "float",
    [qcc_mins_index] =  "vector",
    [qcc_maxs_index] =  "vector",
    [qcc_size_index] =  "vector",
    [qcc_touch_index] =  "func_t",
    [qcc_use_index] =  "func_t",
    [qcc_think_index] =  "func_t",
    [qcc_blocked_index] =  "func_t",
    [qcc_nextthink_index] =  "float",
    [qcc_groundentity_index] =  "int",
    [qcc_health_index] =  "float",
    [qcc_frags_index] =  "float",
    [qcc_weapon_index] =  "float",
    [qcc_weaponmodel_index] =  "string_t",
    [qcc_weaponframe_index] =  "float",
    [qcc_currentammo_index] =  "float",
    [qcc_ammo_shells_index] =  "float",
    [qcc_ammo_nails_index] =  "float",
    [qcc_ammo_rockets_index] =  "float",
    [qcc_ammo_cells_index] =  "float",
    [qcc_items_index] =  "float",
    [qcc_takedamage_index] =  "float",
    [qcc_chain_index] =  "int",
    [qcc_deadflag_index] =  "float",
    [qcc_view_ofs_index] =  "vector",
    [qcc_button0_index] =  "float",
    [qcc_button1_index] =  "float",
    [qcc_button2_index] =  "float",
    [qcc_impulse_index] =  "float",
    [qcc_fixangle_index] =  "float",
    [qcc_v_angle_index] =  "vector",
    [qcc_idealpitch_index] =  "float",
    [qcc_netname_index] =  "string_t",
    [qcc_enemy_index] =  "int",
    [qcc_flags_index] =  "float",
    [qcc_colormap_index] =  "float",
    [qcc_team_index] =  "float",
    [qcc_max_health_index] =  "float",
    [qcc_teleport_time_index] =  "float",
    [qcc_armortype_index] =  "float",
    [qcc_armorvalue_index] =  "float",
    [qcc_waterlevel_index] =  "float",
    [qcc_watertype_index] =  "float",
    [qcc_ideal_yaw_index] =  "float",
    [qcc_yaw_speed_index] =  "float",
    [qcc_aiment_index] =  "int",
    [qcc_goalentity_index] =  "int",
    [qcc_spawnflags_index] =  "float",
    [qcc_target_index] =  "string_t",
    [qcc_targetname_index] =  "string_t",
    [qcc_dmg_take_index] =  "float",
    [qcc_dmg_save_index] =  "float",
    [qcc_dmg_inflictor_index] =  "int",
    [qcc_owner_index] =  "int",
    [qcc_movedir_index] =  "vector",
    [qcc_message_index] =  "string_t",
    [qcc_sounds_index] =  "float",
    [qcc_noise_index] =  "string_t",
    [qcc_noise1_index] =  "string_t",
    [qcc_noise2_index] =  "string_t",
    [qcc_noise3_index] =  "string_t",
    [qcc_wad_index] =  "string_t",
    [qcc_map_index] =  "string_t",
    [qcc_worldtype_index] =  "float",
    [qcc_killtarget_index] =  "string_t",
    [qcc_light_lev_index] =  "float",
    [qcc_style_index] =  "float",
    [qcc_th_stand_index] =  "func_t",
    [qcc_th_walk_index] =  "func_t",
    [qcc_th_run_index] =  "func_t",
    [qcc_th_missile_index] =  "func_t",
    [qcc_th_melee_index] =  "func_t",
    [qcc_th_pain_index] =  "func_t",
    [qcc_th_die_index] =  "func_t",
    [qcc_oldenemy_index] =  "int",
    [qcc_speed_index] =  "float",
    [qcc_lefty_index] =  "float",
    [qcc_search_time_index] =  "float",
    [qcc_attack_state_index] =  "float",
    [qcc_walkframe_index] =  "float",
    [qcc_attack_finished_index] =  "float",
    [qcc_pain_finished_index] =  "float",
    [qcc_invincible_finished_index] =  "float",
    [qcc_invisible_finished_index] =  "float",
    [qcc_super_damage_finished_index] =  "float",
    [qcc_radsuit_finished_index] =  "float",
    [qcc_invincible_time_index] =  "float",
    [qcc_invincible_sound_index] =  "float",
    [qcc_invisible_time_index] =  "float",
    [qcc_invisible_sound_index] =  "float",
    [qcc_super_time_index] =  "float",
    [qcc_super_sound_index] =  "float",
    [qcc_rad_time_index] =  "float",
    [qcc_fly_sound_index] =  "float",
    [qcc_axhitme_index] =  "float",
    [qcc_show_hostile_index] =  "float",
    [qcc_jump_flag_index] =  "float",
    [qcc_swim_flag_index] =  "float",
    [qcc_air_finished_index] =  "float",
    [qcc_bubble_count_index] =  "float",
    [qcc_deathtype_index] =  "string_t",
    [qcc_mdl_index] =  "string_t",
    [qcc_mangle_index] =  "vector",
    [qcc_t_length_index] =  "float",
    [qcc_t_width_index] =  "float",
    [qcc_dest_index] =  "vector",
    [qcc_dest1_index] =  "vector",
    [qcc_dest2_index] =  "vector",
    [qcc_wait_index] =  "float",
    [qcc_delay_index] =  "float",
    [qcc_trigger_field_index] =  "int",
    [qcc_noise4_index] =  "string_t",
    [qcc_pausetime_index] =  "float",
    [qcc_movetarget_index] =  "int",
    [qcc_aflag_index] =  "float",
    [qcc_dmg_index] =  "float",
    [qcc_cnt_index] =  "float",
    [qcc_think1_index] =  "func_t",
    [qcc_finaldest_index] =  "vector",
    [qcc_finalangle_index] =  "vector",
    [qcc_count_index] =  "float",
    [qcc_lip_index] =  "float",
    [qcc_state_index] =  "float",
    [qcc_pos1_index] =  "vector",
    [qcc_pos2_index] =  "vector",
    [qcc_height_index] =  "float",
    [qcc_waitmin_index] =  "float",
    [qcc_waitmax_index] =  "float",
    [qcc_distance_index] =  "float",
    [qcc_volume_index] =  "float",
    [qcc_healamount_index] =  "float",
    [qcc_healtype_index] =  "float",
    [qcc_hit_z_index] =  "float",
    [qcc_dmgtime_index] =  "float",
    [qcc_inpain_index] =  "float",
    [entLeaves_index] =  "entLeaves_t *",
    [qcc_max_field_index] =  "int",
};
