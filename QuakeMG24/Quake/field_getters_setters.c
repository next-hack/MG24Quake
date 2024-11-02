// File fields_getters_setters.c
// Warning! Machine-generated code, do not edit!

/* Copyright (C) 2023-2024 Nicola Wrachien

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
#include "quakedef.h"
#include "quakedef.h"

#if EDICT_GETTER_SETTERS
void *allocEdByType(int classType)
{
  switch (classType)
  {
    case full_edict_idx:
       return Z_CallocFailable(sizeof(full_edict_t), 1, PU_LEVEL, NULL);
    case missile_edict_idx:
       return Z_CallocFailable(sizeof(missile_edict_t), 1, PU_LEVEL, NULL);
    case sound_edict_idx:
       return Z_CallocFailable(sizeof(sound_edict_t), 1, PU_LEVEL, NULL);
    case bodyque_edict_idx:
       return Z_CallocFailable(sizeof(bodyque_edict_t), 1, PU_LEVEL, NULL);
    case light_edict_idx:
       return Z_CallocFailable(sizeof(light_edict_t), 1, PU_LEVEL, NULL);
    case trigger_edict_idx:
       return Z_CallocFailable(sizeof(trigger_edict_t), 1, PU_LEVEL, NULL);
    case info_edict_idx:
       return Z_CallocFailable(sizeof(info_edict_t), 1, PU_LEVEL, NULL);
    case func_edict_idx:
       return Z_CallocFailable(sizeof(func_edict_t), 1, PU_LEVEL, NULL);
    case player_edict_idx:
       return Z_CallocFailable(sizeof(player_edict_t), 1, PU_LEVEL, NULL);
    case path_corner_edict_idx:
       return Z_CallocFailable(sizeof(path_corner_edict_t), 1, PU_LEVEL, NULL);
    case item_edict_idx:
       return Z_CallocFailable(sizeof(item_edict_t), 1, PU_LEVEL, NULL);
    case worldspawn_edict_idx:
       return Z_CallocFailable(sizeof(worldspawn_edict_t), 1, PU_LEVEL, NULL);
    case delayedUse_edict_idx:
       return Z_CallocFailable(sizeof(delayedUse_edict_t), 1, PU_LEVEL, NULL);
    case nh_backpack_edict_idx:
       return Z_CallocFailable(sizeof(nh_backpack_edict_t), 1, PU_LEVEL, NULL);
    case nh_tfog_edict_idx:
       return Z_CallocFailable(sizeof(nh_tfog_edict_t), 1, PU_LEVEL, NULL);
    case explo_box_edict_idx:
       return Z_CallocFailable(sizeof(explo_box_edict_t), 1, PU_LEVEL, NULL);
    case bubble_edict_idx:
       return Z_CallocFailable(sizeof(bubble_edict_t), 1, PU_LEVEL, NULL);
    case teledeath_edict_idx:
       return Z_CallocFailable(sizeof(teledeath_edict_t), 1, PU_LEVEL, NULL);
    case timer_edict_idx:
       return Z_CallocFailable(sizeof(timer_edict_t), 1, PU_LEVEL, NULL);
    case monster_edict_idx:
       return Z_CallocFailable(sizeof(monster_edict_t), 1, PU_LEVEL, NULL);
    case static_light_edict_idx:
       return Z_CallocFailable(sizeof(static_light_edict_t), 1, PU_LEVEL, NULL);
    case nh_wiz_startfast_edict_idx:
       return Z_CallocFailable(sizeof(nh_wiz_startfast_edict_t), 1, PU_LEVEL, NULL);
  }
 while(1) FIXME("Wrong classType");
 return NULL;
}
unsigned int getEdictEntvarSize(edict_t *e){
  int classType = qcc_classname2type[e->qcc_classname];
  switch (classType)
  {
    case full_edict_idx:
       return sizeof(full_entvars_t);
    case missile_edict_idx:
       return sizeof(missile_entvars_t);
    case sound_edict_idx:
       return sizeof(sound_entvars_t);
    case bodyque_edict_idx:
       return sizeof(bodyque_entvars_t);
    case light_edict_idx:
       return sizeof(light_entvars_t);
    case trigger_edict_idx:
       return sizeof(trigger_entvars_t);
    case info_edict_idx:
       return sizeof(info_entvars_t);
    case func_edict_idx:
       return sizeof(func_entvars_t);
    case player_edict_idx:
       return sizeof(player_entvars_t);
    case path_corner_edict_idx:
       return sizeof(path_corner_entvars_t);
    case item_edict_idx:
       return sizeof(item_entvars_t);
    case worldspawn_edict_idx:
       return sizeof(worldspawn_entvars_t);
    case delayedUse_edict_idx:
       return sizeof(delayedUse_entvars_t);
    case nh_backpack_edict_idx:
       return sizeof(nh_backpack_entvars_t);
    case nh_tfog_edict_idx:
       return sizeof(nh_tfog_entvars_t);
    case explo_box_edict_idx:
       return sizeof(explo_box_entvars_t);
    case bubble_edict_idx:
       return sizeof(bubble_entvars_t);
    case teledeath_edict_idx:
       return sizeof(teledeath_entvars_t);
    case timer_edict_idx:
       return sizeof(timer_entvars_t);
    case monster_edict_idx:
       return sizeof(monster_entvars_t);
    case static_light_edict_idx:
       return sizeof(static_light_entvars_t);
    case nh_wiz_startfast_edict_idx:
       return sizeof(nh_wiz_startfast_entvars_t);
  }
 return 0;
}
const uint8_t qcc_classname2type[max_classname_string_index] =
{
    [NULL_string_index] = full_edict_idx,
    [air_bubbles_string_index] = bubble_edict_idx,
    [ambient_drip_string_index] = sound_edict_idx,
    [ambient_drone_string_index] = sound_edict_idx,
    [ambient_comp_hum_string_index] = sound_edict_idx,
    [ambient_flouro_buzz_string_index] = sound_edict_idx,
    [ambient_light_buzz_string_index] = sound_edict_idx,
    [ambient_suck_wind_string_index] = sound_edict_idx,
    [ambient_swamp1_string_index] = sound_edict_idx,
    [ambient_swamp2_string_index] = sound_edict_idx,
    [ambient_thunder_string_index] = sound_edict_idx,
    [event_lightning_string_index] = func_edict_idx,
    [func_door_string_index] = func_edict_idx,
    [func_door_secret_string_index] = func_edict_idx,
    [func_wall_string_index] = func_edict_idx,
    [func_button_string_index] = func_edict_idx,
    [func_train_string_index] = func_edict_idx,
    [func_plat_string_index] = func_edict_idx,
    [func_dm_only_string_index] = func_edict_idx,
    [func_illusionary_string_index] = static_light_edict_idx,
    [info_null_string_index] = info_edict_idx,
    [info_notnull_string_index] = info_edict_idx,
    [info_intermission_string_index] = info_edict_idx,
    [info_player_start_string_index] = info_edict_idx,
    [info_player_deathmatch_string_index] = info_edict_idx,
    [info_player_coop_string_index] = info_edict_idx,
    [info_player_start2_string_index] = info_edict_idx,
    [info_teleport_destination_string_index] = info_edict_idx,
    [item_cells_string_index] = item_edict_idx,
    [item_rockets_string_index] = item_edict_idx,
    [item_shells_string_index] = item_edict_idx,
    [item_spikes_string_index] = item_edict_idx,
    [item_weapon_string_index] = item_edict_idx,
    [item_health_string_index] = item_edict_idx,
    [item_artifact_envirosuit_string_index] = item_edict_idx,
    [item_artifact_super_damage_string_index] = item_edict_idx,
    [item_artifact_invulnerability_string_index] = item_edict_idx,
    [item_artifact_invisibility_string_index] = item_edict_idx,
    [item_armorInv_string_index] = item_edict_idx,
    [item_armor2_string_index] = item_edict_idx,
    [item_armor1_string_index] = item_edict_idx,
    [item_key1_string_index] = item_edict_idx,
    [item_key2_string_index] = item_edict_idx,
    [item_sigil_string_index] = item_edict_idx,
    [light_string_index] = light_edict_idx,
    [light_torch_small_walltorch_string_index] = static_light_edict_idx,
    [light_flame_large_yellow_string_index] = static_light_edict_idx,
    [light_flame_small_yellow_string_index] = static_light_edict_idx,
    [light_flame_small_white_string_index] = static_light_edict_idx,
    [light_fluoro_string_index] = light_edict_idx,
    [light_fluorospark_string_index] = light_edict_idx,
    [light_globe_string_index] = static_light_edict_idx,
    [monster_army_string_index] = monster_edict_idx,
    [monster_dog_string_index] = monster_edict_idx,
    [monster_ogre_string_index] = monster_edict_idx,
    [monster_ogre_marksman_string_index] = monster_edict_idx,
    [monster_knight_string_index] = monster_edict_idx,
    [monster_zombie_string_index] = monster_edict_idx,
    [monster_wizard_string_index] = monster_edict_idx,
    [monster_demon1_string_index] = monster_edict_idx,
    [monster_shambler_string_index] = monster_edict_idx,
    [monster_boss_string_index] = monster_edict_idx,
    [monster_enforcer_string_index] = monster_edict_idx,
    [monster_hell_knight_string_index] = monster_edict_idx,
    [monster_shalrath_string_index] = monster_edict_idx,
    [monster_tarbaby_string_index] = monster_edict_idx,
    [monster_fish_string_index] = monster_edict_idx,
    [monster_oldone_string_index] = monster_edict_idx,
    [misc_fireball_string_index] = missile_edict_idx,
    [misc_explobox_string_index] = explo_box_edict_idx,
    [misc_explobox2_string_index] = explo_box_edict_idx,
    [misc_teleporttrain_string_index] = full_edict_idx,
    [path_corner_string_index] = path_corner_edict_idx,
    [trap_spikeshooter_string_index] = func_edict_idx,
    [trap_shooter_string_index] = func_edict_idx,
    [trigger_teleport_string_index] = trigger_edict_idx,
    [trigger_changelevel_string_index] = trigger_edict_idx,
    [trigger_setskill_string_index] = trigger_edict_idx,
    [trigger_counter_string_index] = trigger_edict_idx,
    [trigger_once_string_index] = trigger_edict_idx,
    [trigger_multiple_string_index] = trigger_edict_idx,
    [trigger_onlyregistered_string_index] = trigger_edict_idx,
    [trigger_secret_string_index] = trigger_edict_idx,
    [trigger_monsterjump_string_index] = trigger_edict_idx,
    [trigger_relay_string_index] = trigger_edict_idx,
    [trigger_push_string_index] = trigger_edict_idx,
    [trigger_hurt_string_index] = trigger_edict_idx,
    [weapon_supershotgun_string_index] = item_edict_idx,
    [weapon_nailgun_string_index] = item_edict_idx,
    [weapon_supernailgun_string_index] = item_edict_idx,
    [weapon_grenadelauncher_string_index] = item_edict_idx,
    [weapon_rocketlauncher_string_index] = item_edict_idx,
    [weapon_lightning_string_index] = item_edict_idx,
    [worldspawn_string_index] = worldspawn_edict_idx,
    [player_string_index] = player_edict_idx,
    [bodyque_string_index] = bodyque_edict_idx,
    [fireball_string_index] = missile_edict_idx,
    [door_string_index] = func_edict_idx,
    [func_bossgate_string_index] = func_edict_idx,
    [func_episodegate_string_index] = func_edict_idx,
    [plat_string_index] = func_edict_idx,
    [train_string_index] = func_edict_idx,
    [bubble_string_index] = bubble_edict_idx,
    [teledeath_string_index] = teledeath_edict_idx,
    [DelayedUse_string_index] = delayedUse_edict_idx,
    [spike_string_index] = missile_edict_idx,
    [grenade_string_index] = missile_edict_idx,
    [wizspike_string_index] = missile_edict_idx,
    [knightspike_string_index] = missile_edict_idx,
    [teledeath2_string_index] = teledeath_edict_idx,
    [nh_missile_string_index] = missile_edict_idx,
    [nh_trigger_string_index] = trigger_edict_idx,
    [nh_map_string_index] = trigger_edict_idx,
    [nh_timer_string_index] = timer_edict_idx,
    [nh_backpack_string_index] = nh_backpack_edict_idx,
    [nh_tfog_string_index] = nh_tfog_edict_idx,
    [nh_sigil_removed_string_index] = item_edict_idx,
    [nh_wiz_startfast_string_index] = nh_wiz_startfast_edict_idx,
    [progs_laser_mdl_string_index] = missile_edict_idx,
    [progs_s_light_mdl_string_index] = missile_edict_idx,
    [progs_v_spike_mdl_string_index] = missile_edict_idx,
    [progs_zom_gib_mdl_string_index] = missile_edict_idx,
    [progs_gib1_mdl_string_index] = missile_edict_idx,
    [progs_gib2_mdl_string_index] = missile_edict_idx,
    [progs_gib3_mdl_string_index] = missile_edict_idx,
    [explo_box_string_index] = explo_box_edict_idx,

};
float (*const setters_qcc_modelindex_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_modelindex_full, setter_qcc_modelindex_missile, setter_float_non_zero_error, setter_qcc_modelindex_bodyque, setter_qcc_modelindex_light, setter_qcc_modelindex_trigger, setter_float_non_zero_error, setter_qcc_modelindex_func, setter_qcc_modelindex_player, setter_float_non_zero_error, setter_qcc_modelindex_item, setter_qcc_modelindex_worldspawn, setter_float_non_zero_error, setter_qcc_modelindex_nh_backpack, setter_float_non_zero_error, setter_qcc_modelindex_explo_box, setter_qcc_modelindex_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_modelindex_monster, setter_qcc_modelindex_static_light, setter_qcc_modelindex_nh_wiz_startfast, };
float (*const setters_qcc_ltime_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ltime_full, setter_qcc_ltime_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ltime_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ltime_nh_wiz_startfast, };
float (*const setters_qcc_movetype_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_movetype_full, setter_qcc_movetype_missile, setter_float_non_zero_error, setter_qcc_movetype_bodyque, setter_float_non_zero_error, setter_qcc_movetype_trigger, setter_float_non_zero_error, setter_qcc_movetype_func, setter_qcc_movetype_player, setter_float_non_zero_error, setter_qcc_movetype_item, setter_qcc_movetype_worldspawn, setter_float_non_zero_error, setter_qcc_movetype_nh_backpack, setter_float_non_zero_error, setter_qcc_movetype_explo_box, setter_qcc_movetype_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_movetype_monster, setter_float_non_zero_error, setter_qcc_movetype_nh_wiz_startfast, };
float (*const setters_qcc_solid_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_solid_full, setter_qcc_solid_missile, setter_float_non_zero_error, setter_qcc_solid_bodyque, setter_float_non_zero_error, setter_qcc_solid_trigger, setter_float_non_zero_error, setter_qcc_solid_func, setter_qcc_solid_player, setter_qcc_solid_path_corner, setter_qcc_solid_item, setter_qcc_solid_worldspawn, setter_float_non_zero_error, setter_qcc_solid_nh_backpack, setter_float_non_zero_error, setter_qcc_solid_explo_box, setter_float_non_zero_error, setter_qcc_solid_teledeath, setter_float_non_zero_error, setter_qcc_solid_monster, setter_float_non_zero_error, setter_qcc_solid_nh_wiz_startfast, };
float (*const setters_qcc_origin_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_origin_full_x, setter_qcc_origin_missile_x, setter_qcc_origin_sound_x, setter_qcc_origin_bodyque_x, setter_qcc_origin_light_x, setter_qcc_origin_trigger_x, setter_qcc_origin_info_x, setter_qcc_origin_func_x, setter_qcc_origin_player_x, setter_qcc_origin_path_corner_x, setter_qcc_origin_item_x, setter_qcc_origin_worldspawn_x, setter_vector_non_zero_error_x, setter_qcc_origin_nh_backpack_x, setter_qcc_origin_nh_tfog_x, setter_qcc_origin_explo_box_x, setter_qcc_origin_bubble_x, setter_qcc_origin_teledeath_x, setter_vector_non_zero_error_x, setter_qcc_origin_monster_x, setter_qcc_origin_static_light_x, setter_qcc_origin_nh_wiz_startfast_x, };
float (*const setters_qcc_origin_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_origin_full_y, setter_qcc_origin_missile_y, setter_qcc_origin_sound_y, setter_qcc_origin_bodyque_y, setter_qcc_origin_light_y, setter_qcc_origin_trigger_y, setter_qcc_origin_info_y, setter_qcc_origin_func_y, setter_qcc_origin_player_y, setter_qcc_origin_path_corner_y, setter_qcc_origin_item_y, setter_qcc_origin_worldspawn_y, setter_vector_non_zero_error_y, setter_qcc_origin_nh_backpack_y, setter_qcc_origin_nh_tfog_y, setter_qcc_origin_explo_box_y, setter_qcc_origin_bubble_y, setter_qcc_origin_teledeath_y, setter_vector_non_zero_error_y, setter_qcc_origin_monster_y, setter_qcc_origin_static_light_y, setter_qcc_origin_nh_wiz_startfast_y, };
float (*const setters_qcc_origin_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_origin_full_z, setter_qcc_origin_missile_z, setter_qcc_origin_sound_z, setter_qcc_origin_bodyque_z, setter_qcc_origin_light_z, setter_qcc_origin_trigger_z, setter_qcc_origin_info_z, setter_qcc_origin_func_z, setter_qcc_origin_player_z, setter_qcc_origin_path_corner_z, setter_qcc_origin_item_z, setter_qcc_origin_worldspawn_z, setter_vector_non_zero_error_z, setter_qcc_origin_nh_backpack_z, setter_qcc_origin_nh_tfog_z, setter_qcc_origin_explo_box_z, setter_qcc_origin_bubble_z, setter_qcc_origin_teledeath_z, setter_vector_non_zero_error_z, setter_qcc_origin_monster_z, setter_qcc_origin_static_light_z, setter_qcc_origin_nh_wiz_startfast_z, };
vector (*const setters_qcc_origin_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_origin_full, setter_qcc_origin_missile, setter_qcc_origin_sound, setter_qcc_origin_bodyque, setter_qcc_origin_light, setter_qcc_origin_trigger, setter_qcc_origin_info, setter_qcc_origin_func, setter_qcc_origin_player, setter_qcc_origin_path_corner, setter_qcc_origin_item, setter_qcc_origin_worldspawn, setter_vector_non_zero_error, setter_qcc_origin_nh_backpack, setter_qcc_origin_nh_tfog, setter_qcc_origin_explo_box, setter_qcc_origin_bubble, setter_qcc_origin_teledeath, setter_vector_non_zero_error, setter_qcc_origin_monster, setter_qcc_origin_static_light, setter_qcc_origin_nh_wiz_startfast, };
float (*const setters_qcc_oldorigin_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_oldorigin_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_oldorigin_func_x, setter_qcc_oldorigin_player_x, setter_vector_non_zero_error_x, setter_qcc_oldorigin_item_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_oldorigin_nh_backpack_x, setter_vector_non_zero_error_x, setter_qcc_oldorigin_explo_box_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_oldorigin_monster_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_oldorigin_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_oldorigin_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_oldorigin_func_y, setter_qcc_oldorigin_player_y, setter_vector_non_zero_error_y, setter_qcc_oldorigin_item_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_oldorigin_nh_backpack_y, setter_vector_non_zero_error_y, setter_qcc_oldorigin_explo_box_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_oldorigin_monster_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_oldorigin_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_oldorigin_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_oldorigin_func_z, setter_qcc_oldorigin_player_z, setter_vector_non_zero_error_z, setter_qcc_oldorigin_item_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_oldorigin_nh_backpack_z, setter_vector_non_zero_error_z, setter_qcc_oldorigin_explo_box_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_oldorigin_monster_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_oldorigin_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_oldorigin_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_oldorigin_func, setter_qcc_oldorigin_player, setter_vector_non_zero_error, setter_qcc_oldorigin_item, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_oldorigin_nh_backpack, setter_vector_non_zero_error, setter_qcc_oldorigin_explo_box, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_oldorigin_monster, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_velocity_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_velocity_full_x, setter_qcc_velocity_missile_x, setter_vector_non_zero_error_x, setter_qcc_velocity_bodyque_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_velocity_func_x, setter_qcc_velocity_player_x, setter_vector_non_zero_error_x, setter_qcc_velocity_item_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_velocity_nh_backpack_x, setter_vector_non_zero_error_x, setter_qcc_velocity_explo_box_x, setter_qcc_velocity_bubble_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_velocity_monster_x, setter_vector_non_zero_error_x, setter_qcc_velocity_nh_wiz_startfast_x, };
float (*const setters_qcc_velocity_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_velocity_full_y, setter_qcc_velocity_missile_y, setter_vector_non_zero_error_y, setter_qcc_velocity_bodyque_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_velocity_func_y, setter_qcc_velocity_player_y, setter_vector_non_zero_error_y, setter_qcc_velocity_item_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_velocity_nh_backpack_y, setter_vector_non_zero_error_y, setter_qcc_velocity_explo_box_y, setter_qcc_velocity_bubble_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_velocity_monster_y, setter_vector_non_zero_error_y, setter_qcc_velocity_nh_wiz_startfast_y, };
float (*const setters_qcc_velocity_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_velocity_full_z, setter_qcc_velocity_missile_z, setter_vector_non_zero_error_z, setter_qcc_velocity_bodyque_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_velocity_func_z, setter_qcc_velocity_player_z, setter_vector_non_zero_error_z, setter_qcc_velocity_item_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_velocity_nh_backpack_z, setter_vector_non_zero_error_z, setter_qcc_velocity_explo_box_z, setter_qcc_velocity_bubble_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_velocity_monster_z, setter_vector_non_zero_error_z, setter_qcc_velocity_nh_wiz_startfast_z, };
vector (*const setters_qcc_velocity_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_velocity_full, setter_qcc_velocity_missile, setter_vector_non_zero_error, setter_qcc_velocity_bodyque, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_velocity_func, setter_qcc_velocity_player, setter_vector_non_zero_error, setter_qcc_velocity_item, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_velocity_nh_backpack, setter_vector_non_zero_error, setter_qcc_velocity_explo_box, setter_qcc_velocity_bubble, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_velocity_monster, setter_vector_non_zero_error, setter_qcc_velocity_nh_wiz_startfast, };
float (*const setters_qcc_angles_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_angles_full_x, setter_qcc_angles_missile_x, setter_vector_non_zero_error_x, setter_qcc_angles_bodyque_x, setter_qcc_angles_light_x, setter_qcc_angles_trigger_x, setter_qcc_angles_info_x, setter_qcc_angles_func_x, setter_qcc_angles_player_x, setter_vector_non_zero_error_x, setter_qcc_angles_item_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_angles_nh_backpack_x, setter_vector_non_zero_error_x, setter_qcc_angles_explo_box_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_angles_monster_x, setter_qcc_angles_static_light_x, setter_qcc_angles_nh_wiz_startfast_x, };
float (*const setters_qcc_angles_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_angles_full_y, setter_qcc_angles_missile_y, setter_vector_non_zero_error_y, setter_qcc_angles_bodyque_y, setter_qcc_angles_light_y, setter_qcc_angles_trigger_y, setter_qcc_angles_info_y, setter_qcc_angles_func_y, setter_qcc_angles_player_y, setter_vector_non_zero_error_y, setter_qcc_angles_item_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_angles_nh_backpack_y, setter_vector_non_zero_error_y, setter_qcc_angles_explo_box_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_angles_monster_y, setter_qcc_angles_static_light_y, setter_qcc_angles_nh_wiz_startfast_y, };
float (*const setters_qcc_angles_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_angles_full_z, setter_qcc_angles_missile_z, setter_vector_non_zero_error_z, setter_qcc_angles_bodyque_z, setter_qcc_angles_light_z, setter_qcc_angles_trigger_z, setter_qcc_angles_info_z, setter_qcc_angles_func_z, setter_qcc_angles_player_z, setter_vector_non_zero_error_z, setter_qcc_angles_item_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_angles_nh_backpack_z, setter_vector_non_zero_error_z, setter_qcc_angles_explo_box_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_angles_monster_z, setter_qcc_angles_static_light_z, setter_qcc_angles_nh_wiz_startfast_z, };
vector (*const setters_qcc_angles_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_angles_full, setter_qcc_angles_missile, setter_vector_non_zero_error, setter_qcc_angles_bodyque, setter_qcc_angles_light, setter_qcc_angles_trigger, setter_qcc_angles_info, setter_qcc_angles_func, setter_qcc_angles_player, setter_vector_non_zero_error, setter_qcc_angles_item, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_angles_nh_backpack, setter_vector_non_zero_error, setter_qcc_angles_explo_box, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_angles_monster, setter_qcc_angles_static_light, setter_qcc_angles_nh_wiz_startfast, };
float (*const setters_qcc_avelocity_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_avelocity_full_x, setter_qcc_avelocity_missile_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_avelocity_player_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_avelocity_monster_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_avelocity_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_avelocity_full_y, setter_qcc_avelocity_missile_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_avelocity_player_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_avelocity_monster_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_avelocity_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_avelocity_full_z, setter_qcc_avelocity_missile_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_avelocity_player_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_avelocity_monster_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_avelocity_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_avelocity_full, setter_qcc_avelocity_missile, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_avelocity_player, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_avelocity_monster, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_punchangle_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_punchangle_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_punchangle_player_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_punchangle_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_punchangle_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_punchangle_player_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_punchangle_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_punchangle_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_punchangle_player_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_punchangle_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_punchangle_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_punchangle_player, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
string_t (*const setters_qcc_model_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_model_full, setter_qcc_model_missile, setter_string_t_non_zero_error, setter_qcc_model_bodyque, setter_qcc_model_light, setter_qcc_model_trigger, setter_string_t_non_zero_error, setter_qcc_model_func, setter_qcc_model_player, setter_string_t_non_zero_error, setter_qcc_model_item, setter_qcc_model_worldspawn, setter_string_t_non_zero_error, setter_qcc_model_nh_backpack, setter_string_t_non_zero_error, setter_qcc_model_explo_box, setter_qcc_model_bubble, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_model_monster, setter_qcc_model_static_light, setter_qcc_model_nh_wiz_startfast, };
float (*const setters_qcc_frame_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_frame_full, setter_qcc_frame_missile, setter_float_non_zero_error, setter_qcc_frame_bodyque, setter_qcc_frame_light, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_frame_func, setter_qcc_frame_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_frame_explo_box, setter_qcc_frame_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_frame_monster, setter_qcc_frame_static_light, setter_qcc_frame_nh_wiz_startfast, };
float (*const setters_qcc_skin_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_skin_full, setter_qcc_skin_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_skin_player, setter_float_non_zero_error, setter_qcc_skin_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_skin_nh_wiz_startfast, };
float (*const setters_qcc_effects_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_effects_full, setter_qcc_effects_missile, setter_float_non_zero_error, setter_qcc_effects_bodyque, setter_float_non_zero_error, setter_qcc_effects_trigger, setter_float_non_zero_error, setter_qcc_effects_func, setter_qcc_effects_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_effects_monster, setter_float_non_zero_error, setter_qcc_effects_nh_wiz_startfast, };
float (*const setters_qcc_mins_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mins_full_x, setter_qcc_mins_missile_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_mins_light_x, setter_qcc_mins_trigger_x, setter_vector_non_zero_error_x, setter_qcc_mins_func_x, setter_qcc_mins_player_x, setter_qcc_mins_path_corner_x, setter_qcc_mins_item_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_mins_nh_backpack_x, setter_vector_non_zero_error_x, setter_qcc_mins_explo_box_x, setter_qcc_mins_bubble_x, setter_qcc_mins_teledeath_x, setter_vector_non_zero_error_x, setter_qcc_mins_monster_x, setter_qcc_mins_static_light_x, setter_qcc_mins_nh_wiz_startfast_x, };
float (*const setters_qcc_mins_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mins_full_y, setter_qcc_mins_missile_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_mins_light_y, setter_qcc_mins_trigger_y, setter_vector_non_zero_error_y, setter_qcc_mins_func_y, setter_qcc_mins_player_y, setter_qcc_mins_path_corner_y, setter_qcc_mins_item_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_mins_nh_backpack_y, setter_vector_non_zero_error_y, setter_qcc_mins_explo_box_y, setter_qcc_mins_bubble_y, setter_qcc_mins_teledeath_y, setter_vector_non_zero_error_y, setter_qcc_mins_monster_y, setter_qcc_mins_static_light_y, setter_qcc_mins_nh_wiz_startfast_y, };
float (*const setters_qcc_mins_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mins_full_z, setter_qcc_mins_missile_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_mins_light_z, setter_qcc_mins_trigger_z, setter_vector_non_zero_error_z, setter_qcc_mins_func_z, setter_qcc_mins_player_z, setter_qcc_mins_path_corner_z, setter_qcc_mins_item_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_mins_nh_backpack_z, setter_vector_non_zero_error_z, setter_qcc_mins_explo_box_z, setter_qcc_mins_bubble_z, setter_qcc_mins_teledeath_z, setter_vector_non_zero_error_z, setter_qcc_mins_monster_z, setter_qcc_mins_static_light_z, setter_qcc_mins_nh_wiz_startfast_z, };
vector (*const setters_qcc_mins_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_mins_full, setter_qcc_mins_missile, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_mins_light, setter_qcc_mins_trigger, setter_vector_non_zero_error, setter_qcc_mins_func, setter_qcc_mins_player, setter_qcc_mins_path_corner, setter_qcc_mins_item, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_mins_nh_backpack, setter_vector_non_zero_error, setter_qcc_mins_explo_box, setter_qcc_mins_bubble, setter_qcc_mins_teledeath, setter_vector_non_zero_error, setter_qcc_mins_monster, setter_qcc_mins_static_light, setter_qcc_mins_nh_wiz_startfast, };
float (*const setters_qcc_maxs_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_maxs_full_x, setter_qcc_maxs_missile_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_maxs_light_x, setter_qcc_maxs_trigger_x, setter_vector_non_zero_error_x, setter_qcc_maxs_func_x, setter_qcc_maxs_player_x, setter_qcc_maxs_path_corner_x, setter_qcc_maxs_item_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_maxs_nh_backpack_x, setter_vector_non_zero_error_x, setter_qcc_maxs_explo_box_x, setter_qcc_maxs_bubble_x, setter_qcc_maxs_teledeath_x, setter_vector_non_zero_error_x, setter_qcc_maxs_monster_x, setter_qcc_maxs_static_light_x, setter_qcc_maxs_nh_wiz_startfast_x, };
float (*const setters_qcc_maxs_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_maxs_full_y, setter_qcc_maxs_missile_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_maxs_light_y, setter_qcc_maxs_trigger_y, setter_vector_non_zero_error_y, setter_qcc_maxs_func_y, setter_qcc_maxs_player_y, setter_qcc_maxs_path_corner_y, setter_qcc_maxs_item_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_maxs_nh_backpack_y, setter_vector_non_zero_error_y, setter_qcc_maxs_explo_box_y, setter_qcc_maxs_bubble_y, setter_qcc_maxs_teledeath_y, setter_vector_non_zero_error_y, setter_qcc_maxs_monster_y, setter_qcc_maxs_static_light_y, setter_qcc_maxs_nh_wiz_startfast_y, };
float (*const setters_qcc_maxs_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_maxs_full_z, setter_qcc_maxs_missile_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_maxs_light_z, setter_qcc_maxs_trigger_z, setter_vector_non_zero_error_z, setter_qcc_maxs_func_z, setter_qcc_maxs_player_z, setter_qcc_maxs_path_corner_z, setter_qcc_maxs_item_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_maxs_nh_backpack_z, setter_vector_non_zero_error_z, setter_qcc_maxs_explo_box_z, setter_qcc_maxs_bubble_z, setter_qcc_maxs_teledeath_z, setter_vector_non_zero_error_z, setter_qcc_maxs_monster_z, setter_qcc_maxs_static_light_z, setter_qcc_maxs_nh_wiz_startfast_z, };
vector (*const setters_qcc_maxs_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_maxs_full, setter_qcc_maxs_missile, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_maxs_light, setter_qcc_maxs_trigger, setter_vector_non_zero_error, setter_qcc_maxs_func, setter_qcc_maxs_player, setter_qcc_maxs_path_corner, setter_qcc_maxs_item, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_maxs_nh_backpack, setter_vector_non_zero_error, setter_qcc_maxs_explo_box, setter_qcc_maxs_bubble, setter_qcc_maxs_teledeath, setter_vector_non_zero_error, setter_qcc_maxs_monster, setter_qcc_maxs_static_light, setter_qcc_maxs_nh_wiz_startfast, };
func_t (*const setters_qcc_touch_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_touch_full, setter_qcc_touch_missile, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_touch_trigger, setter_func_t_non_zero_error, setter_qcc_touch_func, setter_qcc_touch_player, setter_qcc_touch_path_corner, setter_qcc_touch_item, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_touch_nh_backpack, setter_func_t_non_zero_error, setter_qcc_touch_explo_box, setter_qcc_touch_bubble, setter_qcc_touch_teledeath, setter_func_t_non_zero_error, setter_qcc_touch_monster, setter_func_t_non_zero_error, setter_qcc_touch_nh_wiz_startfast, };
func_t (*const setters_qcc_use_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_use_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_use_light, setter_qcc_use_trigger, setter_func_t_non_zero_error, setter_qcc_use_func, setter_qcc_use_player, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_use_monster, setter_qcc_use_static_light, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_think_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_think_full, setter_qcc_think_missile, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_think_trigger, setter_func_t_non_zero_error, setter_qcc_think_func, setter_qcc_think_player, setter_func_t_non_zero_error, setter_qcc_think_item, setter_func_t_non_zero_error, setter_qcc_think_delayedUse, setter_qcc_think_nh_backpack, setter_qcc_think_nh_tfog, setter_qcc_think_explo_box, setter_qcc_think_bubble, setter_qcc_think_teledeath, setter_qcc_think_timer, setter_qcc_think_monster, setter_func_t_non_zero_error, setter_qcc_think_nh_wiz_startfast, };
func_t (*const setters_qcc_blocked_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_blocked_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_blocked_func, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
float (*const setters_qcc_nextthink_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_nextthink_full, setter_qcc_nextthink_missile, setter_float_non_zero_error, setter_qcc_nextthink_bodyque, setter_float_non_zero_error, setter_qcc_nextthink_trigger, setter_float_non_zero_error, setter_qcc_nextthink_func, setter_qcc_nextthink_player, setter_float_non_zero_error, setter_qcc_nextthink_item, setter_float_non_zero_error, setter_qcc_nextthink_delayedUse, setter_qcc_nextthink_nh_backpack, setter_qcc_nextthink_nh_tfog, setter_qcc_nextthink_explo_box, setter_qcc_nextthink_bubble, setter_qcc_nextthink_teledeath, setter_qcc_nextthink_timer, setter_qcc_nextthink_monster, setter_float_non_zero_error, setter_qcc_nextthink_nh_wiz_startfast, };
int (*const setters_qcc_groundentity_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_groundentity_full, setter_qcc_groundentity_missile, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_groundentity_player, setter_int_non_zero_error, setter_qcc_groundentity_item, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_groundentity_nh_backpack, setter_int_non_zero_error, setter_qcc_groundentity_explo_box, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_groundentity_monster, setter_int_non_zero_error, setter_qcc_groundentity_nh_wiz_startfast, };
float (*const setters_qcc_health_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_health_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_health_trigger, setter_float_non_zero_error, setter_qcc_health_func, setter_qcc_health_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_health_explo_box, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_health_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_frags_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_frags_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_frags_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_weapon_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_weapon_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_weapon_player, setter_float_non_zero_error, setter_qcc_weapon_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
string_t (*const setters_qcc_weaponmodel_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_weaponmodel_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_weaponmodel_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_weaponframe_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_weaponframe_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_weaponframe_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_currentammo_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_currentammo_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_currentammo_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_ammo_shells_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ammo_shells_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_shells_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_shells_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_shells_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_ammo_nails_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ammo_nails_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_nails_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_nails_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_nails_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_ammo_rockets_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ammo_rockets_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_rockets_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_rockets_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_rockets_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_ammo_cells_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ammo_cells_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_cells_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_cells_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ammo_cells_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_items_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_items_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_items_func, setter_qcc_items_player, setter_float_non_zero_error, setter_qcc_items_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_items_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_takedamage_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_takedamage_full, setter_qcc_takedamage_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_takedamage_trigger, setter_float_non_zero_error, setter_qcc_takedamage_func, setter_qcc_takedamage_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_takedamage_explo_box, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_takedamage_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
int (*const setters_qcc_chain_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_chain_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_chain_player, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_chain_explo_box, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_chain_monster, setter_int_non_zero_error, setter_int_non_zero_error, };
float (*const setters_qcc_deadflag_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_deadflag_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_deadflag_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_view_ofs_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_view_ofs_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_view_ofs_player_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_view_ofs_monster_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_view_ofs_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_view_ofs_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_view_ofs_player_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_view_ofs_monster_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_view_ofs_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_view_ofs_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_view_ofs_player_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_view_ofs_monster_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_view_ofs_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_view_ofs_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_view_ofs_player, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_view_ofs_monster, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_button0_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_button0_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_button0_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_button1_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_button1_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_button1_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_button2_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_button2_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_button2_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_impulse_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_impulse_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_impulse_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_fixangle_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_fixangle_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_fixangle_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_v_angle_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_v_angle_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_v_angle_player_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_v_angle_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_v_angle_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_v_angle_player_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_v_angle_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_v_angle_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_v_angle_player_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_v_angle_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_v_angle_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_v_angle_player, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_idealpitch_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_idealpitch_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_idealpitch_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
string_t (*const setters_qcc_netname_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_netname_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_netname_player, setter_string_t_non_zero_error, setter_qcc_netname_item, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
int (*const setters_qcc_enemy_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_enemy_full, setter_qcc_enemy_missile, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_enemy_trigger, setter_int_non_zero_error, setter_qcc_enemy_func, setter_qcc_enemy_player, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_enemy_delayedUse, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_enemy_monster, setter_int_non_zero_error, setter_qcc_enemy_nh_wiz_startfast, };
float (*const setters_qcc_flags_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_flags_full, setter_qcc_flags_missile, setter_float_non_zero_error, setter_qcc_flags_bodyque, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_flags_func, setter_qcc_flags_player, setter_float_non_zero_error, setter_qcc_flags_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_flags_nh_backpack, setter_float_non_zero_error, setter_qcc_flags_explo_box, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_flags_monster, setter_float_non_zero_error, setter_qcc_flags_nh_wiz_startfast, };
float (*const setters_qcc_team_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_team_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_team_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_max_health_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_max_health_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_max_health_trigger, setter_float_non_zero_error, setter_qcc_max_health_func, setter_qcc_max_health_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_max_health_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_teleport_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_teleport_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_teleport_time_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_armortype_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_armortype_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_armortype_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_armorvalue_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_armorvalue_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_armorvalue_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_waterlevel_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_waterlevel_full, setter_qcc_waterlevel_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_waterlevel_player, setter_float_non_zero_error, setter_qcc_waterlevel_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_waterlevel_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_waterlevel_monster, setter_float_non_zero_error, setter_qcc_waterlevel_nh_wiz_startfast, };
float (*const setters_qcc_watertype_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_watertype_full, setter_qcc_watertype_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_watertype_player, setter_float_non_zero_error, setter_qcc_watertype_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_watertype_nh_backpack, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_watertype_monster, setter_float_non_zero_error, setter_qcc_watertype_nh_wiz_startfast, };
float (*const setters_qcc_ideal_yaw_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_ideal_yaw_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_ideal_yaw_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_yaw_speed_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_yaw_speed_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_yaw_speed_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
int (*const setters_qcc_goalentity_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_goalentity_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_goalentity_monster, setter_int_non_zero_error, setter_int_non_zero_error, };
float (*const setters_qcc_spawnflags_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_spawnflags_full, setter_qcc_spawnflags_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_spawnflags_light, setter_qcc_spawnflags_trigger, setter_qcc_spawnflags_info, setter_qcc_spawnflags_func, setter_qcc_spawnflags_player, setter_qcc_spawnflags_path_corner, setter_qcc_spawnflags_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_spawnflags_explo_box, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_spawnflags_monster, setter_qcc_spawnflags_static_light, setter_float_non_zero_error, };
string_t (*const setters_qcc_target_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_target_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_target_light, setter_qcc_target_trigger, setter_string_t_non_zero_error, setter_qcc_target_func, setter_string_t_non_zero_error, setter_qcc_target_path_corner, setter_qcc_target_item, setter_string_t_non_zero_error, setter_qcc_target_delayedUse, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_target_monster, setter_qcc_target_static_light, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_targetname_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_targetname_full, setter_qcc_targetname_missile, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_targetname_light, setter_qcc_targetname_trigger, setter_qcc_targetname_info, setter_qcc_targetname_func, setter_string_t_non_zero_error, setter_qcc_targetname_path_corner, setter_qcc_targetname_item, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_targetname_monster, setter_qcc_targetname_static_light, setter_string_t_non_zero_error, };
float (*const setters_qcc_dmg_take_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dmg_take_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_dmg_take_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_dmg_save_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dmg_save_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_dmg_save_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
int (*const setters_qcc_dmg_inflictor_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_dmg_inflictor_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_dmg_inflictor_player, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, };
int (*const setters_qcc_owner_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_owner_full, setter_qcc_owner_missile, setter_int_non_zero_error, setter_qcc_owner_bodyque, setter_int_non_zero_error, setter_qcc_owner_trigger, setter_int_non_zero_error, setter_qcc_owner_func, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_owner_item, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_owner_bubble, setter_qcc_owner_teledeath, setter_int_non_zero_error, setter_qcc_owner_monster, setter_int_non_zero_error, setter_qcc_owner_nh_wiz_startfast, };
float (*const setters_qcc_movedir_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_movedir_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_movedir_trigger_x, setter_vector_non_zero_error_x, setter_qcc_movedir_func_x, setter_qcc_movedir_player_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_movedir_monster_x, setter_vector_non_zero_error_x, setter_qcc_movedir_nh_wiz_startfast_x, };
float (*const setters_qcc_movedir_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_movedir_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_movedir_trigger_y, setter_vector_non_zero_error_y, setter_qcc_movedir_func_y, setter_qcc_movedir_player_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_movedir_monster_y, setter_vector_non_zero_error_y, setter_qcc_movedir_nh_wiz_startfast_y, };
float (*const setters_qcc_movedir_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_movedir_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_movedir_trigger_z, setter_vector_non_zero_error_z, setter_qcc_movedir_func_z, setter_qcc_movedir_player_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_movedir_monster_z, setter_vector_non_zero_error_z, setter_qcc_movedir_nh_wiz_startfast_z, };
vector (*const setters_qcc_movedir_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_movedir_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_movedir_trigger, setter_vector_non_zero_error, setter_qcc_movedir_func, setter_qcc_movedir_player, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_movedir_monster, setter_vector_non_zero_error, setter_qcc_movedir_nh_wiz_startfast, };
string_t (*const setters_qcc_message_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_message_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_message_trigger, setter_string_t_non_zero_error, setter_qcc_message_func, setter_qcc_message_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_message_worldspawn, setter_qcc_message_delayedUse, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_message_monster, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_sounds_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_sounds_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_sounds_trigger, setter_float_non_zero_error, setter_qcc_sounds_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_sounds_item, setter_qcc_sounds_worldspawn, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_sounds_explo_box, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
string_t (*const setters_qcc_noise_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_noise_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_noise_trigger, setter_string_t_non_zero_error, setter_qcc_noise_func, setter_qcc_noise_player, setter_string_t_non_zero_error, setter_qcc_noise_item, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_noise1_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_noise1_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_noise1_func, setter_qcc_noise1_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_noise2_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_noise2_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_noise2_func, setter_qcc_noise2_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_noise3_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_noise3_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_noise3_func, setter_qcc_noise3_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_map_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_map_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_map_trigger, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_worldtype_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_worldtype_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_worldtype_worldspawn, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
string_t (*const setters_qcc_killtarget_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_killtarget_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_killtarget_trigger, setter_string_t_non_zero_error, setter_qcc_killtarget_func, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_killtarget_delayedUse, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_killtarget_monster, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_style_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_style_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_style_light, setter_qcc_style_trigger, setter_float_non_zero_error, setter_float_warning, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_warning, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_style_static_light, setter_float_non_zero_error, };
func_t (*const setters_qcc_th_stand_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_stand_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_stand_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_walk_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_walk_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_walk_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_run_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_run_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_run_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_missile_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_missile_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_missile_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_melee_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_melee_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_melee_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_pain_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_pain_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_pain_func, setter_qcc_th_pain_player, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_pain_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
func_t (*const setters_qcc_th_die_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_th_die_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_die_trigger, setter_func_t_non_zero_error, setter_qcc_th_die_func, setter_qcc_th_die_player, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_die_explo_box, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_th_die_monster, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
int (*const setters_qcc_oldenemy_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_oldenemy_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_oldenemy_monster, setter_int_non_zero_error, setter_int_non_zero_error, };
float (*const setters_qcc_speed_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_speed_full, setter_qcc_speed_missile, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_speed_trigger, setter_float_non_zero_error, setter_qcc_speed_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_speed_nh_wiz_startfast, };
float (*const setters_qcc_lefty_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_lefty_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_lefty_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_search_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_search_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_search_time_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_attack_state_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_attack_state_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_attack_state_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_walkframe_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_walkframe_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_walkframe_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_attack_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_attack_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_attack_finished_trigger, setter_float_non_zero_error, setter_qcc_attack_finished_func, setter_qcc_attack_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_attack_finished_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_pain_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pain_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_pain_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_pain_finished_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invincible_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invincible_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invincible_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invisible_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invisible_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invisible_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_super_damage_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_super_damage_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_super_damage_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_radsuit_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_radsuit_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_radsuit_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invincible_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invincible_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invincible_time_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invincible_sound_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invincible_sound_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invincible_sound_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invisible_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invisible_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invisible_time_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_invisible_sound_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_invisible_sound_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_invisible_sound_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_super_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_super_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_super_time_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_super_sound_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_super_sound_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_super_sound_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_rad_time_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_rad_time_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_rad_time_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_fly_sound_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_fly_sound_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_fly_sound_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_axhitme_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_axhitme_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_axhitme_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_axhitme_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_show_hostile_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_show_hostile_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_show_hostile_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_show_hostile_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_jump_flag_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_jump_flag_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_jump_flag_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_swim_flag_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_swim_flag_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_swim_flag_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_air_finished_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_air_finished_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_air_finished_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_air_finished_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_bubble_count_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_bubble_count_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_bubble_count_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
string_t (*const setters_qcc_deathtype_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_deathtype_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_deathtype_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
string_t (*const setters_qcc_mdl_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_mdl_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_mdl_item, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_mangle_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mangle_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_mangle_info_x, setter_qcc_mangle_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_mangle_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mangle_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_mangle_info_y, setter_qcc_mangle_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_mangle_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_mangle_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_mangle_info_z, setter_qcc_mangle_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_mangle_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_mangle_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_mangle_info, setter_qcc_mangle_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_t_length_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_t_length_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_t_length_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_t_width_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_t_width_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_t_width_func, setter_qcc_t_width_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_dest_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_dest_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_dest_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_dest_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_dest_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_dest1_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest1_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_dest1_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_dest1_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest1_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_dest1_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_dest1_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest1_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_dest1_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_dest1_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_dest1_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_dest1_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_dest2_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest2_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_dest2_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_dest2_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest2_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_dest2_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_dest2_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dest2_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_dest2_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_dest2_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_dest2_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_dest2_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_wait_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_wait_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_wait_trigger, setter_float_non_zero_error, setter_qcc_wait_func, setter_float_non_zero_error, setter_qcc_wait_path_corner, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_delay_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_delay_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_delay_trigger, setter_float_non_zero_error, setter_qcc_delay_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
int (*const setters_qcc_trigger_field_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_trigger_field_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_trigger_field_func, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, };
string_t (*const setters_qcc_noise4_array[qcc_max_class])(edict_t *entity, string_t value) = {setter_qcc_noise4_full, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_qcc_noise4_func, setter_qcc_noise4_player, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, setter_string_t_non_zero_error, };
float (*const setters_qcc_pausetime_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pausetime_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_pausetime_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_pausetime_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
int (*const setters_qcc_movetarget_array[qcc_max_class])(edict_t *entity, int value) = {setter_qcc_movetarget_full, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_int_non_zero_error, setter_qcc_movetarget_monster, setter_int_non_zero_error, setter_int_non_zero_error, };
float (*const setters_qcc_aflag_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_aflag_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_aflag_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_dmg_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dmg_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_dmg_trigger, setter_float_non_zero_error, setter_qcc_dmg_func, setter_qcc_dmg_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_cnt_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_cnt_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_cnt_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_cnt_bubble, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_cnt_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
func_t (*const setters_qcc_think1_array[qcc_max_class])(edict_t *entity, func_t value) = {setter_qcc_think1_full, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_qcc_think1_func, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, setter_func_t_non_zero_error, };
float (*const setters_qcc_finaldest_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finaldest_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_finaldest_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_finaldest_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finaldest_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_finaldest_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_finaldest_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finaldest_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_finaldest_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_finaldest_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_finaldest_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_finaldest_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_finalangle_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finalangle_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_finalangle_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finalangle_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_finalangle_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_finalangle_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_finalangle_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_finalangle_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_count_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_count_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_count_trigger, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_lip_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_lip_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_lip_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_state_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_state_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_state_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_pos1_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos1_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_pos1_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_pos1_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos1_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_pos1_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_pos1_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos1_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_pos1_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_pos1_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_pos1_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_pos1_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_pos2_array_x[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos2_full_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_qcc_pos2_func_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, setter_vector_non_zero_error_x, };
float (*const setters_qcc_pos2_array_y[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos2_full_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_qcc_pos2_func_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, setter_vector_non_zero_error_y, };
float (*const setters_qcc_pos2_array_z[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_pos2_full_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_qcc_pos2_func_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, setter_vector_non_zero_error_z, };
vector (*const setters_qcc_pos2_array[qcc_max_class])(edict_t *entity, vector value) = {setter_qcc_pos2_full, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_qcc_pos2_func, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, setter_vector_non_zero_error, };
float (*const setters_qcc_height_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_height_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_height_trigger, setter_float_non_zero_error, setter_qcc_height_func, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_waitmin_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_waitmin_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_waitmin_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_healamount_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_healamount_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_healamount_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_healtype_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_healtype_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_healtype_item, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_dmgtime_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_dmgtime_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_dmgtime_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const setters_qcc_inpain_array[qcc_max_class])(edict_t *entity, float value) = {setter_qcc_inpain_full, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_inpain_player, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_float_non_zero_error, setter_qcc_inpain_monster, setter_float_non_zero_error, setter_float_non_zero_error, };
float (*const getters_qcc_modelindex_array[qcc_max_class])(edict_t *entity) = {getter_qcc_modelindex_full, getter_qcc_modelindex_missile, getter_float_zero, getter_qcc_modelindex_bodyque, getter_qcc_modelindex_light, getter_qcc_modelindex_trigger, getter_float_zero, getter_qcc_modelindex_func, getter_qcc_modelindex_player, getter_float_zero, getter_qcc_modelindex_item, getter_qcc_modelindex_worldspawn, getter_float_zero, getter_qcc_modelindex_nh_backpack, getter_float_zero, getter_qcc_modelindex_explo_box, getter_qcc_modelindex_bubble, getter_float_zero, getter_float_zero, getter_qcc_modelindex_monster, getter_qcc_modelindex_static_light, getter_qcc_modelindex_nh_wiz_startfast, };
float (*const getters_qcc_ltime_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ltime_full, getter_qcc_ltime_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ltime_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ltime_nh_wiz_startfast, };
float (*const getters_qcc_movetype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_movetype_full, getter_qcc_movetype_missile, getter_float_zero, getter_qcc_movetype_bodyque, getter_float_zero, getter_qcc_movetype_trigger, getter_float_zero, getter_qcc_movetype_func, getter_qcc_movetype_player, getter_float_zero, getter_qcc_movetype_item, getter_qcc_movetype_worldspawn, getter_float_zero, getter_qcc_movetype_nh_backpack, getter_float_zero, getter_qcc_movetype_explo_box, getter_qcc_movetype_bubble, getter_float_zero, getter_float_zero, getter_qcc_movetype_monster, getter_float_zero, getter_qcc_movetype_nh_wiz_startfast, };
float (*const getters_qcc_solid_array[qcc_max_class])(edict_t *entity) = {getter_qcc_solid_full, getter_qcc_solid_missile, getter_float_zero, getter_qcc_solid_bodyque, getter_float_zero, getter_qcc_solid_trigger, getter_float_zero, getter_qcc_solid_func, getter_qcc_solid_player, getter_qcc_solid_path_corner, getter_qcc_solid_item, getter_qcc_solid_worldspawn, getter_float_zero, getter_qcc_solid_nh_backpack, getter_float_zero, getter_qcc_solid_explo_box, getter_float_zero, getter_qcc_solid_teledeath, getter_float_zero, getter_qcc_solid_monster, getter_float_zero, getter_qcc_solid_nh_wiz_startfast, };
vector (*const getters_qcc_origin_array[qcc_max_class])(edict_t *entity) = {getter_qcc_origin_full, getter_qcc_origin_missile, getter_qcc_origin_sound, getter_qcc_origin_bodyque, getter_qcc_origin_light, getter_qcc_origin_trigger, getter_qcc_origin_info, getter_qcc_origin_func, getter_qcc_origin_player, getter_qcc_origin_path_corner, getter_qcc_origin_item, getter_qcc_origin_worldspawn, getter_vector_zero, getter_qcc_origin_nh_backpack, getter_qcc_origin_nh_tfog, getter_qcc_origin_explo_box, getter_qcc_origin_bubble, getter_qcc_origin_teledeath, getter_vector_zero, getter_qcc_origin_monster, getter_qcc_origin_static_light, getter_qcc_origin_nh_wiz_startfast, };
vector (*const getters_qcc_oldorigin_array[qcc_max_class])(edict_t *entity) = {getter_qcc_oldorigin_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_oldorigin_func, getter_qcc_oldorigin_player, getter_vector_zero, getter_qcc_oldorigin_item, getter_vector_zero, getter_vector_zero, getter_qcc_oldorigin_nh_backpack, getter_vector_zero, getter_qcc_oldorigin_explo_box, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_oldorigin_monster, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_velocity_array[qcc_max_class])(edict_t *entity) = {getter_qcc_velocity_full, getter_qcc_velocity_missile, getter_vector_zero, getter_qcc_velocity_bodyque, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_velocity_func, getter_qcc_velocity_player, getter_vector_zero, getter_qcc_velocity_item, getter_vector_zero, getter_vector_zero, getter_qcc_velocity_nh_backpack, getter_vector_zero, getter_qcc_velocity_explo_box, getter_qcc_velocity_bubble, getter_vector_zero, getter_vector_zero, getter_qcc_velocity_monster, getter_vector_zero, getter_qcc_velocity_nh_wiz_startfast, };
vector (*const getters_qcc_angles_array[qcc_max_class])(edict_t *entity) = {getter_qcc_angles_full, getter_qcc_angles_missile, getter_vector_zero, getter_qcc_angles_bodyque, getter_qcc_angles_light, getter_qcc_angles_trigger, getter_qcc_angles_info, getter_qcc_angles_func, getter_qcc_angles_player, getter_vector_zero, getter_qcc_angles_item, getter_vector_zero, getter_vector_zero, getter_qcc_angles_nh_backpack, getter_vector_zero, getter_qcc_angles_explo_box, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_angles_monster, getter_qcc_angles_static_light, getter_qcc_angles_nh_wiz_startfast, };
vector (*const getters_qcc_avelocity_array[qcc_max_class])(edict_t *entity) = {getter_qcc_avelocity_full, getter_qcc_avelocity_missile, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_avelocity_player, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_avelocity_monster, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_punchangle_array[qcc_max_class])(edict_t *entity) = {getter_qcc_punchangle_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_punchangle_player, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
string_t (*const getters_qcc_model_array[qcc_max_class])(edict_t *entity) = {getter_qcc_model_full, getter_qcc_model_missile, getter_string_t_zero, getter_qcc_model_bodyque, getter_qcc_model_light, getter_qcc_model_trigger, getter_string_t_zero, getter_qcc_model_func, getter_qcc_model_player, getter_string_t_zero, getter_qcc_model_item, getter_qcc_model_worldspawn, getter_string_t_zero, getter_qcc_model_nh_backpack, getter_string_t_zero, getter_qcc_model_explo_box, getter_qcc_model_bubble, getter_string_t_zero, getter_string_t_zero, getter_qcc_model_monster, getter_qcc_model_static_light, getter_qcc_model_nh_wiz_startfast, };
float (*const getters_qcc_frame_array[qcc_max_class])(edict_t *entity) = {getter_qcc_frame_full, getter_qcc_frame_missile, getter_float_zero, getter_qcc_frame_bodyque, getter_qcc_frame_light, getter_float_zero, getter_float_zero, getter_qcc_frame_func, getter_qcc_frame_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_frame_explo_box, getter_qcc_frame_bubble, getter_float_zero, getter_float_zero, getter_qcc_frame_monster, getter_qcc_frame_static_light, getter_qcc_frame_nh_wiz_startfast, };
float (*const getters_qcc_skin_array[qcc_max_class])(edict_t *entity) = {getter_qcc_skin_full, getter_qcc_skin_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_skin_player, getter_float_zero, getter_qcc_skin_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_skin_nh_wiz_startfast, };
float (*const getters_qcc_effects_array[qcc_max_class])(edict_t *entity) = {getter_qcc_effects_full, getter_qcc_effects_missile, getter_float_zero, getter_qcc_effects_bodyque, getter_float_zero, getter_qcc_effects_trigger, getter_float_zero, getter_qcc_effects_func, getter_qcc_effects_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_effects_monster, getter_float_zero, getter_qcc_effects_nh_wiz_startfast, };
vector (*const getters_qcc_mins_array[qcc_max_class])(edict_t *entity) = {getter_qcc_mins_full, getter_qcc_mins_missile, getter_vector_zero, getter_vector_zero, getter_qcc_mins_light, getter_qcc_mins_trigger, getter_vector_zero, getter_qcc_mins_func, getter_qcc_mins_player, getter_qcc_mins_path_corner, getter_qcc_mins_item, getter_vector_zero, getter_vector_zero, getter_qcc_mins_nh_backpack, getter_vector_zero, getter_qcc_mins_explo_box, getter_qcc_mins_bubble, getter_qcc_mins_teledeath, getter_vector_zero, getter_qcc_mins_monster, getter_qcc_mins_static_light, getter_qcc_mins_nh_wiz_startfast, };
vector (*const getters_qcc_maxs_array[qcc_max_class])(edict_t *entity) = {getter_qcc_maxs_full, getter_qcc_maxs_missile, getter_vector_zero, getter_vector_zero, getter_qcc_maxs_light, getter_qcc_maxs_trigger, getter_vector_zero, getter_qcc_maxs_func, getter_qcc_maxs_player, getter_qcc_maxs_path_corner, getter_qcc_maxs_item, getter_vector_zero, getter_vector_zero, getter_qcc_maxs_nh_backpack, getter_vector_zero, getter_qcc_maxs_explo_box, getter_qcc_maxs_bubble, getter_qcc_maxs_teledeath, getter_vector_zero, getter_qcc_maxs_monster, getter_qcc_maxs_static_light, getter_qcc_maxs_nh_wiz_startfast, };
func_t (*const getters_qcc_touch_array[qcc_max_class])(edict_t *entity) = {getter_qcc_touch_full, getter_qcc_touch_missile, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_touch_trigger, getter_func_t_zero, getter_qcc_touch_func, getter_qcc_touch_player, getter_qcc_touch_path_corner, getter_qcc_touch_item, getter_func_t_zero, getter_func_t_zero, getter_qcc_touch_nh_backpack, getter_func_t_zero, getter_qcc_touch_explo_box, getter_qcc_touch_bubble, getter_qcc_touch_teledeath, getter_func_t_zero, getter_qcc_touch_monster, getter_func_t_zero, getter_qcc_touch_nh_wiz_startfast, };
func_t (*const getters_qcc_use_array[qcc_max_class])(edict_t *entity) = {getter_qcc_use_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_use_light, getter_qcc_use_trigger, getter_func_t_zero, getter_qcc_use_func, getter_qcc_use_player, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_use_monster, getter_qcc_use_static_light, getter_func_t_zero, };
func_t (*const getters_qcc_think_array[qcc_max_class])(edict_t *entity) = {getter_qcc_think_full, getter_qcc_think_missile, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_think_trigger, getter_func_t_zero, getter_qcc_think_func, getter_qcc_think_player, getter_func_t_zero, getter_qcc_think_item, getter_func_t_zero, getter_qcc_think_delayedUse, getter_qcc_think_nh_backpack, getter_qcc_think_nh_tfog, getter_qcc_think_explo_box, getter_qcc_think_bubble, getter_qcc_think_teledeath, getter_qcc_think_timer, getter_qcc_think_monster, getter_func_t_zero, getter_qcc_think_nh_wiz_startfast, };
func_t (*const getters_qcc_blocked_array[qcc_max_class])(edict_t *entity) = {getter_qcc_blocked_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_blocked_func, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, };
float (*const getters_qcc_nextthink_array[qcc_max_class])(edict_t *entity) = {getter_qcc_nextthink_full, getter_qcc_nextthink_missile, getter_float_zero, getter_qcc_nextthink_bodyque, getter_float_zero, getter_qcc_nextthink_trigger, getter_float_zero, getter_qcc_nextthink_func, getter_qcc_nextthink_player, getter_float_zero, getter_qcc_nextthink_item, getter_float_zero, getter_qcc_nextthink_delayedUse, getter_qcc_nextthink_nh_backpack, getter_qcc_nextthink_nh_tfog, getter_qcc_nextthink_explo_box, getter_qcc_nextthink_bubble, getter_qcc_nextthink_teledeath, getter_qcc_nextthink_timer, getter_qcc_nextthink_monster, getter_float_zero, getter_qcc_nextthink_nh_wiz_startfast, };
int (*const getters_qcc_groundentity_array[qcc_max_class])(edict_t *entity) = {getter_qcc_groundentity_full, getter_qcc_groundentity_missile, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_groundentity_player, getter_int_zero, getter_qcc_groundentity_item, getter_int_zero, getter_int_zero, getter_qcc_groundentity_nh_backpack, getter_int_zero, getter_qcc_groundentity_explo_box, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_groundentity_monster, getter_int_zero, getter_qcc_groundentity_nh_wiz_startfast, };
float (*const getters_qcc_health_array[qcc_max_class])(edict_t *entity) = {getter_qcc_health_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_health_trigger, getter_float_zero, getter_qcc_health_func, getter_qcc_health_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_health_explo_box, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_health_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_frags_array[qcc_max_class])(edict_t *entity) = {getter_qcc_frags_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_frags_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_weapon_array[qcc_max_class])(edict_t *entity) = {getter_qcc_weapon_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_weapon_player, getter_float_zero, getter_qcc_weapon_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
string_t (*const getters_qcc_weaponmodel_array[qcc_max_class])(edict_t *entity) = {getter_qcc_weaponmodel_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_weaponmodel_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
float (*const getters_qcc_weaponframe_array[qcc_max_class])(edict_t *entity) = {getter_qcc_weaponframe_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_weaponframe_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_currentammo_array[qcc_max_class])(edict_t *entity) = {getter_qcc_currentammo_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_currentammo_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_ammo_shells_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ammo_shells_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_shells_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_shells_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_shells_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_ammo_nails_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ammo_nails_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_nails_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_nails_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_nails_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_ammo_rockets_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ammo_rockets_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_rockets_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_rockets_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_rockets_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_ammo_cells_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ammo_cells_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_cells_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_cells_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ammo_cells_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_items_array[qcc_max_class])(edict_t *entity) = {getter_qcc_items_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_items_func, getter_qcc_items_player, getter_float_zero, getter_qcc_items_item, getter_float_zero, getter_float_zero, getter_qcc_items_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_takedamage_array[qcc_max_class])(edict_t *entity) = {getter_qcc_takedamage_full, getter_qcc_takedamage_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_takedamage_trigger, getter_float_zero, getter_qcc_takedamage_func, getter_qcc_takedamage_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_takedamage_explo_box, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_takedamage_monster, getter_float_zero, getter_float_zero, };
int (*const getters_qcc_chain_array[qcc_max_class])(edict_t *entity) = {getter_qcc_chain_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_chain_player, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_chain_explo_box, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_chain_monster, getter_int_zero, getter_int_zero, };
float (*const getters_qcc_deadflag_array[qcc_max_class])(edict_t *entity) = {getter_qcc_deadflag_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_deadflag_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
vector (*const getters_qcc_view_ofs_array[qcc_max_class])(edict_t *entity) = {getter_qcc_view_ofs_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_view_ofs_player, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_view_ofs_monster, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_button0_array[qcc_max_class])(edict_t *entity) = {getter_qcc_button0_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_button0_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_button1_array[qcc_max_class])(edict_t *entity) = {getter_qcc_button1_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_button1_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_button2_array[qcc_max_class])(edict_t *entity) = {getter_qcc_button2_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_button2_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_impulse_array[qcc_max_class])(edict_t *entity) = {getter_qcc_impulse_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_impulse_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_fixangle_array[qcc_max_class])(edict_t *entity) = {getter_qcc_fixangle_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_fixangle_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
vector (*const getters_qcc_v_angle_array[qcc_max_class])(edict_t *entity) = {getter_qcc_v_angle_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_v_angle_player, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_idealpitch_array[qcc_max_class])(edict_t *entity) = {getter_qcc_idealpitch_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_idealpitch_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
string_t (*const getters_qcc_netname_array[qcc_max_class])(edict_t *entity) = {getter_qcc_netname_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_netname_player, getter_string_t_zero, getter_qcc_netname_item, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
int (*const getters_qcc_enemy_array[qcc_max_class])(edict_t *entity) = {getter_qcc_enemy_full, getter_qcc_enemy_missile, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_enemy_trigger, getter_int_zero, getter_qcc_enemy_func, getter_qcc_enemy_player, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_enemy_delayedUse, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_enemy_monster, getter_int_zero, getter_qcc_enemy_nh_wiz_startfast, };
float (*const getters_qcc_flags_array[qcc_max_class])(edict_t *entity) = {getter_qcc_flags_full, getter_qcc_flags_missile, getter_float_zero, getter_qcc_flags_bodyque, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_flags_func, getter_qcc_flags_player, getter_float_zero, getter_qcc_flags_item, getter_float_zero, getter_float_zero, getter_qcc_flags_nh_backpack, getter_float_zero, getter_qcc_flags_explo_box, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_flags_monster, getter_float_zero, getter_qcc_flags_nh_wiz_startfast, };
float (*const getters_qcc_team_array[qcc_max_class])(edict_t *entity) = {getter_qcc_team_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_team_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_max_health_array[qcc_max_class])(edict_t *entity) = {getter_qcc_max_health_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_max_health_trigger, getter_float_zero, getter_qcc_max_health_func, getter_qcc_max_health_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_max_health_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_teleport_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_teleport_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_teleport_time_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_armortype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_armortype_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_armortype_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_armorvalue_array[qcc_max_class])(edict_t *entity) = {getter_qcc_armorvalue_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_armorvalue_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_waterlevel_array[qcc_max_class])(edict_t *entity) = {getter_qcc_waterlevel_full, getter_qcc_waterlevel_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_waterlevel_player, getter_float_zero, getter_qcc_waterlevel_item, getter_float_zero, getter_float_zero, getter_qcc_waterlevel_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_waterlevel_monster, getter_float_zero, getter_qcc_waterlevel_nh_wiz_startfast, };
float (*const getters_qcc_watertype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_watertype_full, getter_qcc_watertype_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_watertype_player, getter_float_zero, getter_qcc_watertype_item, getter_float_zero, getter_float_zero, getter_qcc_watertype_nh_backpack, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_watertype_monster, getter_float_zero, getter_qcc_watertype_nh_wiz_startfast, };
float (*const getters_qcc_ideal_yaw_array[qcc_max_class])(edict_t *entity) = {getter_qcc_ideal_yaw_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_ideal_yaw_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_yaw_speed_array[qcc_max_class])(edict_t *entity) = {getter_qcc_yaw_speed_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_yaw_speed_monster, getter_float_zero, getter_float_zero, };
int (*const getters_qcc_goalentity_array[qcc_max_class])(edict_t *entity) = {getter_qcc_goalentity_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_goalentity_monster, getter_int_zero, getter_int_zero, };
float (*const getters_qcc_spawnflags_array[qcc_max_class])(edict_t *entity) = {getter_qcc_spawnflags_full, getter_qcc_spawnflags_missile, getter_float_zero, getter_float_zero, getter_qcc_spawnflags_light, getter_qcc_spawnflags_trigger, getter_qcc_spawnflags_info, getter_qcc_spawnflags_func, getter_qcc_spawnflags_player, getter_qcc_spawnflags_path_corner, getter_qcc_spawnflags_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_spawnflags_explo_box, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_spawnflags_monster, getter_qcc_spawnflags_static_light, getter_float_zero, };
string_t (*const getters_qcc_target_array[qcc_max_class])(edict_t *entity) = {getter_qcc_target_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_target_light, getter_qcc_target_trigger, getter_string_t_zero, getter_qcc_target_func, getter_string_t_zero, getter_qcc_target_path_corner, getter_qcc_target_item, getter_string_t_zero, getter_qcc_target_delayedUse, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_target_monster, getter_qcc_target_static_light, getter_string_t_zero, };
string_t (*const getters_qcc_targetname_array[qcc_max_class])(edict_t *entity) = {getter_qcc_targetname_full, getter_qcc_targetname_missile, getter_string_t_zero, getter_string_t_zero, getter_qcc_targetname_light, getter_qcc_targetname_trigger, getter_qcc_targetname_info, getter_qcc_targetname_func, getter_string_t_zero, getter_qcc_targetname_path_corner, getter_qcc_targetname_item, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_targetname_monster, getter_qcc_targetname_static_light, getter_string_t_zero, };
float (*const getters_qcc_dmg_take_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dmg_take_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_dmg_take_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_dmg_save_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dmg_save_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_dmg_save_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
int (*const getters_qcc_dmg_inflictor_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dmg_inflictor_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_dmg_inflictor_player, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, };
int (*const getters_qcc_owner_array[qcc_max_class])(edict_t *entity) = {getter_qcc_owner_full, getter_qcc_owner_missile, getter_int_zero, getter_qcc_owner_bodyque, getter_int_zero, getter_qcc_owner_trigger, getter_int_zero, getter_qcc_owner_func, getter_int_zero, getter_int_zero, getter_qcc_owner_item, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_owner_bubble, getter_qcc_owner_teledeath, getter_int_zero, getter_qcc_owner_monster, getter_int_zero, getter_qcc_owner_nh_wiz_startfast, };
vector (*const getters_qcc_movedir_array[qcc_max_class])(edict_t *entity) = {getter_qcc_movedir_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_movedir_trigger, getter_vector_zero, getter_qcc_movedir_func, getter_qcc_movedir_player, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_movedir_monster, getter_vector_zero, getter_qcc_movedir_nh_wiz_startfast, };
string_t (*const getters_qcc_message_array[qcc_max_class])(edict_t *entity) = {getter_qcc_message_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_message_trigger, getter_string_t_zero, getter_qcc_message_func, getter_qcc_message_player, getter_string_t_zero, getter_string_t_zero, getter_qcc_message_worldspawn, getter_qcc_message_delayedUse, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_message_monster, getter_string_t_zero, getter_string_t_zero, };
float (*const getters_qcc_sounds_array[qcc_max_class])(edict_t *entity) = {getter_qcc_sounds_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_sounds_trigger, getter_float_zero, getter_qcc_sounds_func, getter_float_zero, getter_float_zero, getter_qcc_sounds_item, getter_qcc_sounds_worldspawn, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_sounds_explo_box, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
string_t (*const getters_qcc_noise_array[qcc_max_class])(edict_t *entity) = {getter_qcc_noise_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_noise_trigger, getter_string_t_zero, getter_qcc_noise_func, getter_qcc_noise_player, getter_string_t_zero, getter_qcc_noise_item, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
string_t (*const getters_qcc_noise1_array[qcc_max_class])(edict_t *entity) = {getter_qcc_noise1_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_noise1_func, getter_qcc_noise1_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
string_t (*const getters_qcc_noise2_array[qcc_max_class])(edict_t *entity) = {getter_qcc_noise2_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_noise2_func, getter_qcc_noise2_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
string_t (*const getters_qcc_noise3_array[qcc_max_class])(edict_t *entity) = {getter_qcc_noise3_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_noise3_func, getter_qcc_noise3_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
string_t (*const getters_qcc_map_array[qcc_max_class])(edict_t *entity) = {getter_qcc_map_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_map_trigger, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
float (*const getters_qcc_worldtype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_worldtype_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_worldtype_worldspawn, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
string_t (*const getters_qcc_killtarget_array[qcc_max_class])(edict_t *entity) = {getter_qcc_killtarget_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_killtarget_trigger, getter_string_t_zero, getter_qcc_killtarget_func, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_killtarget_delayedUse, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_killtarget_monster, getter_string_t_zero, getter_string_t_zero, };
float (*const getters_qcc_style_array[qcc_max_class])(edict_t *entity) = {getter_qcc_style_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_style_light, getter_qcc_style_trigger, getter_float_zero, getter_float_warning, getter_float_zero, getter_float_zero, getter_float_warning, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_style_static_light, getter_float_zero, };
func_t (*const getters_qcc_th_stand_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_stand_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_stand_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_walk_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_walk_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_walk_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_run_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_run_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_run_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_missile_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_missile_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_missile_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_melee_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_melee_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_melee_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_pain_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_pain_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_pain_func, getter_qcc_th_pain_player, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_pain_monster, getter_func_t_zero, getter_func_t_zero, };
func_t (*const getters_qcc_th_die_array[qcc_max_class])(edict_t *entity) = {getter_qcc_th_die_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_die_trigger, getter_func_t_zero, getter_qcc_th_die_func, getter_qcc_th_die_player, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_die_explo_box, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_th_die_monster, getter_func_t_zero, getter_func_t_zero, };
int (*const getters_qcc_oldenemy_array[qcc_max_class])(edict_t *entity) = {getter_qcc_oldenemy_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_oldenemy_monster, getter_int_zero, getter_int_zero, };
float (*const getters_qcc_speed_array[qcc_max_class])(edict_t *entity) = {getter_qcc_speed_full, getter_qcc_speed_missile, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_speed_trigger, getter_float_zero, getter_qcc_speed_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_speed_nh_wiz_startfast, };
float (*const getters_qcc_lefty_array[qcc_max_class])(edict_t *entity) = {getter_qcc_lefty_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_lefty_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_search_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_search_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_search_time_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_attack_state_array[qcc_max_class])(edict_t *entity) = {getter_qcc_attack_state_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_attack_state_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_walkframe_array[qcc_max_class])(edict_t *entity) = {getter_qcc_walkframe_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_walkframe_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_attack_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_attack_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_attack_finished_trigger, getter_float_zero, getter_qcc_attack_finished_func, getter_qcc_attack_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_attack_finished_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_pain_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_pain_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_pain_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_pain_finished_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invincible_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invincible_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invincible_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invisible_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invisible_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invisible_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_super_damage_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_super_damage_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_super_damage_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_radsuit_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_radsuit_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_radsuit_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invincible_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invincible_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invincible_time_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invincible_sound_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invincible_sound_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invincible_sound_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invisible_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invisible_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invisible_time_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_invisible_sound_array[qcc_max_class])(edict_t *entity) = {getter_qcc_invisible_sound_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_invisible_sound_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_super_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_super_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_super_time_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_super_sound_array[qcc_max_class])(edict_t *entity) = {getter_qcc_super_sound_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_super_sound_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_rad_time_array[qcc_max_class])(edict_t *entity) = {getter_qcc_rad_time_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_rad_time_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_fly_sound_array[qcc_max_class])(edict_t *entity) = {getter_qcc_fly_sound_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_fly_sound_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_axhitme_array[qcc_max_class])(edict_t *entity) = {getter_qcc_axhitme_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_axhitme_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_axhitme_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_show_hostile_array[qcc_max_class])(edict_t *entity) = {getter_qcc_show_hostile_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_show_hostile_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_show_hostile_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_jump_flag_array[qcc_max_class])(edict_t *entity) = {getter_qcc_jump_flag_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_jump_flag_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_swim_flag_array[qcc_max_class])(edict_t *entity) = {getter_qcc_swim_flag_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_swim_flag_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_air_finished_array[qcc_max_class])(edict_t *entity) = {getter_qcc_air_finished_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_air_finished_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_air_finished_bubble, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_bubble_count_array[qcc_max_class])(edict_t *entity) = {getter_qcc_bubble_count_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_bubble_count_bubble, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
string_t (*const getters_qcc_deathtype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_deathtype_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_deathtype_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
string_t (*const getters_qcc_mdl_array[qcc_max_class])(edict_t *entity) = {getter_qcc_mdl_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_mdl_item, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
vector (*const getters_qcc_mangle_array[qcc_max_class])(edict_t *entity) = {getter_qcc_mangle_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_mangle_info, getter_qcc_mangle_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_t_length_array[qcc_max_class])(edict_t *entity) = {getter_qcc_t_length_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_t_length_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_t_width_array[qcc_max_class])(edict_t *entity) = {getter_qcc_t_width_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_t_width_func, getter_qcc_t_width_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
vector (*const getters_qcc_dest_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dest_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_dest1_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dest1_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_dest1_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_dest2_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dest2_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_dest2_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_wait_array[qcc_max_class])(edict_t *entity) = {getter_qcc_wait_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_wait_trigger, getter_float_zero, getter_qcc_wait_func, getter_float_zero, getter_qcc_wait_path_corner, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_delay_array[qcc_max_class])(edict_t *entity) = {getter_qcc_delay_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_delay_trigger, getter_float_zero, getter_qcc_delay_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
int (*const getters_qcc_trigger_field_array[qcc_max_class])(edict_t *entity) = {getter_qcc_trigger_field_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_trigger_field_func, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, };
string_t (*const getters_qcc_noise4_array[qcc_max_class])(edict_t *entity) = {getter_qcc_noise4_full, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_qcc_noise4_func, getter_qcc_noise4_player, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, getter_string_t_zero, };
float (*const getters_qcc_pausetime_array[qcc_max_class])(edict_t *entity) = {getter_qcc_pausetime_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_pausetime_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_pausetime_monster, getter_float_zero, getter_float_zero, };
int (*const getters_qcc_movetarget_array[qcc_max_class])(edict_t *entity) = {getter_qcc_movetarget_full, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_int_zero, getter_qcc_movetarget_monster, getter_int_zero, getter_int_zero, };
float (*const getters_qcc_aflag_array[qcc_max_class])(edict_t *entity) = {getter_qcc_aflag_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_aflag_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_dmg_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dmg_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_dmg_trigger, getter_float_zero, getter_qcc_dmg_func, getter_qcc_dmg_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_cnt_array[qcc_max_class])(edict_t *entity) = {getter_qcc_cnt_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_cnt_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_cnt_bubble, getter_float_zero, getter_float_zero, getter_qcc_cnt_monster, getter_float_zero, getter_float_zero, };
func_t (*const getters_qcc_think1_array[qcc_max_class])(edict_t *entity) = {getter_qcc_think1_full, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_qcc_think1_func, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, getter_func_t_zero, };
vector (*const getters_qcc_finaldest_array[qcc_max_class])(edict_t *entity) = {getter_qcc_finaldest_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_finaldest_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_finalangle_array[qcc_max_class])(edict_t *entity) = {getter_qcc_finalangle_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_count_array[qcc_max_class])(edict_t *entity) = {getter_qcc_count_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_count_trigger, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_lip_array[qcc_max_class])(edict_t *entity) = {getter_qcc_lip_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_lip_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_state_array[qcc_max_class])(edict_t *entity) = {getter_qcc_state_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_state_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
vector (*const getters_qcc_pos1_array[qcc_max_class])(edict_t *entity) = {getter_qcc_pos1_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_pos1_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
vector (*const getters_qcc_pos2_array[qcc_max_class])(edict_t *entity) = {getter_qcc_pos2_full, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_qcc_pos2_func, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, getter_vector_zero, };
float (*const getters_qcc_height_array[qcc_max_class])(edict_t *entity) = {getter_qcc_height_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_height_trigger, getter_float_zero, getter_qcc_height_func, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_waitmin_array[qcc_max_class])(edict_t *entity) = {getter_qcc_waitmin_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_waitmin_monster, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_healamount_array[qcc_max_class])(edict_t *entity) = {getter_qcc_healamount_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_healamount_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_healtype_array[qcc_max_class])(edict_t *entity) = {getter_qcc_healtype_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_healtype_item, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_dmgtime_array[qcc_max_class])(edict_t *entity) = {getter_qcc_dmgtime_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_dmgtime_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, };
float (*const getters_qcc_inpain_array[qcc_max_class])(edict_t *entity) = {getter_qcc_inpain_full, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_inpain_player, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_float_zero, getter_qcc_inpain_monster, getter_float_zero, getter_float_zero, };
entLeaves_t * (*const getters_entLeaves_array[qcc_max_class])(edict_t *entity) = {getter_entLeaves_full, getter_entLeaves_missile, getter_entLeaves_zero, getter_entLeaves_bodyque, getter_entLeaves_light, getter_entLeaves_trigger, getter_entLeaves_zero, getter_entLeaves_func, getter_entLeaves_player, getter_entLeaves_zero, getter_entLeaves_item, getter_entLeaves_worldspawn, getter_entLeaves_zero, getter_entLeaves_nh_backpack, getter_entLeaves_zero, getter_entLeaves_explo_box, getter_entLeaves_bubble, getter_entLeaves_zero, getter_entLeaves_zero, getter_entLeaves_monster, getter_entLeaves_static_light, getter_entLeaves_nh_wiz_startfast, };
float set_qcc_modelindex(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_modelindex");
    return setters_qcc_modelindex_array[type](entity, value);
}
float set_qcc_ltime(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ltime");
    return setters_qcc_ltime_array[type](entity, value);
}
float set_qcc_movetype(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movetype");
    return setters_qcc_movetype_array[type](entity, value);
}
float set_qcc_solid(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_solid");
    return setters_qcc_solid_array[type](entity, value);
}
float set_qcc_origin_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_origin");
    return setters_qcc_origin_array_x[type](entity, value);
}
float set_qcc_origin_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_origin");
    return setters_qcc_origin_array_y[type](entity, value);
}
float set_qcc_origin_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_origin");
    return setters_qcc_origin_array_z[type](entity, value);
}
vector set_qcc_origin(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_origin");
    return setters_qcc_origin_array[type](entity, value);
}
float set_qcc_oldorigin_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldorigin");
    return setters_qcc_oldorigin_array_x[type](entity, value);
}
float set_qcc_oldorigin_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldorigin");
    return setters_qcc_oldorigin_array_y[type](entity, value);
}
float set_qcc_oldorigin_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldorigin");
    return setters_qcc_oldorigin_array_z[type](entity, value);
}
vector set_qcc_oldorigin(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldorigin");
    return setters_qcc_oldorigin_array[type](entity, value);
}
float set_qcc_velocity_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_velocity");
    return setters_qcc_velocity_array_x[type](entity, value);
}
float set_qcc_velocity_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_velocity");
    return setters_qcc_velocity_array_y[type](entity, value);
}
float set_qcc_velocity_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_velocity");
    return setters_qcc_velocity_array_z[type](entity, value);
}
vector set_qcc_velocity(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_velocity");
    return setters_qcc_velocity_array[type](entity, value);
}
float set_qcc_angles_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_angles");
    return setters_qcc_angles_array_x[type](entity, value);
}
float set_qcc_angles_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_angles");
    return setters_qcc_angles_array_y[type](entity, value);
}
float set_qcc_angles_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_angles");
    return setters_qcc_angles_array_z[type](entity, value);
}
vector set_qcc_angles(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_angles");
    return setters_qcc_angles_array[type](entity, value);
}
float set_qcc_avelocity_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_avelocity");
    return setters_qcc_avelocity_array_x[type](entity, value);
}
float set_qcc_avelocity_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_avelocity");
    return setters_qcc_avelocity_array_y[type](entity, value);
}
float set_qcc_avelocity_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_avelocity");
    return setters_qcc_avelocity_array_z[type](entity, value);
}
vector set_qcc_avelocity(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_avelocity");
    return setters_qcc_avelocity_array[type](entity, value);
}
float set_qcc_punchangle_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_punchangle");
    return setters_qcc_punchangle_array_x[type](entity, value);
}
float set_qcc_punchangle_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_punchangle");
    return setters_qcc_punchangle_array_y[type](entity, value);
}
float set_qcc_punchangle_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_punchangle");
    return setters_qcc_punchangle_array_z[type](entity, value);
}
vector set_qcc_punchangle(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_punchangle");
    return setters_qcc_punchangle_array[type](entity, value);
}
string_t set_qcc_model(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_model");
    return setters_qcc_model_array[type](entity, value);
}
float set_qcc_frame(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_frame");
    return setters_qcc_frame_array[type](entity, value);
}
float set_qcc_skin(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_skin");
    return setters_qcc_skin_array[type](entity, value);
}
float set_qcc_effects(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_effects");
    return setters_qcc_effects_array[type](entity, value);
}
float set_qcc_mins_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mins");
    return setters_qcc_mins_array_x[type](entity, value);
}
float set_qcc_mins_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mins");
    return setters_qcc_mins_array_y[type](entity, value);
}
float set_qcc_mins_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mins");
    return setters_qcc_mins_array_z[type](entity, value);
}
vector set_qcc_mins(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mins");
    return setters_qcc_mins_array[type](entity, value);
}
float set_qcc_maxs_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_maxs");
    return setters_qcc_maxs_array_x[type](entity, value);
}
float set_qcc_maxs_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_maxs");
    return setters_qcc_maxs_array_y[type](entity, value);
}
float set_qcc_maxs_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_maxs");
    return setters_qcc_maxs_array_z[type](entity, value);
}
vector set_qcc_maxs(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_maxs");
    return setters_qcc_maxs_array[type](entity, value);
}
func_t set_qcc_touch(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_touch");
    return setters_qcc_touch_array[type](entity, value);
}
func_t set_qcc_use(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_use");
    return setters_qcc_use_array[type](entity, value);
}
func_t set_qcc_think(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_think");
    return setters_qcc_think_array[type](entity, value);
}
func_t set_qcc_blocked(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_blocked");
    return setters_qcc_blocked_array[type](entity, value);
}
float set_qcc_nextthink(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_nextthink");
    return setters_qcc_nextthink_array[type](entity, value);
}
int set_qcc_groundentity(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_groundentity");
    return setters_qcc_groundentity_array[type](entity, value);
}
float set_qcc_health(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_health");
    return setters_qcc_health_array[type](entity, value);
}
float set_qcc_frags(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_frags");
    return setters_qcc_frags_array[type](entity, value);
}
float set_qcc_weapon(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weapon");
    return setters_qcc_weapon_array[type](entity, value);
}
string_t set_qcc_weaponmodel(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weaponmodel");
    return setters_qcc_weaponmodel_array[type](entity, value);
}
float set_qcc_weaponframe(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weaponframe");
    return setters_qcc_weaponframe_array[type](entity, value);
}
float set_qcc_currentammo(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_currentammo");
    return setters_qcc_currentammo_array[type](entity, value);
}
float set_qcc_ammo_shells(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_shells");
    return setters_qcc_ammo_shells_array[type](entity, value);
}
float set_qcc_ammo_nails(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_nails");
    return setters_qcc_ammo_nails_array[type](entity, value);
}
float set_qcc_ammo_rockets(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_rockets");
    return setters_qcc_ammo_rockets_array[type](entity, value);
}
float set_qcc_ammo_cells(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_cells");
    return setters_qcc_ammo_cells_array[type](entity, value);
}
float set_qcc_items(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_items");
    return setters_qcc_items_array[type](entity, value);
}
float set_qcc_takedamage(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_takedamage");
    return setters_qcc_takedamage_array[type](entity, value);
}
int set_qcc_chain(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_chain");
    return setters_qcc_chain_array[type](entity, value);
}
float set_qcc_deadflag(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_deadflag");
    return setters_qcc_deadflag_array[type](entity, value);
}
float set_qcc_view_ofs_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_view_ofs");
    return setters_qcc_view_ofs_array_x[type](entity, value);
}
float set_qcc_view_ofs_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_view_ofs");
    return setters_qcc_view_ofs_array_y[type](entity, value);
}
float set_qcc_view_ofs_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_view_ofs");
    return setters_qcc_view_ofs_array_z[type](entity, value);
}
vector set_qcc_view_ofs(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_view_ofs");
    return setters_qcc_view_ofs_array[type](entity, value);
}
float set_qcc_button0(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button0");
    return setters_qcc_button0_array[type](entity, value);
}
float set_qcc_button1(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button1");
    return setters_qcc_button1_array[type](entity, value);
}
float set_qcc_button2(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button2");
    return setters_qcc_button2_array[type](entity, value);
}
float set_qcc_impulse(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_impulse");
    return setters_qcc_impulse_array[type](entity, value);
}
float set_qcc_fixangle(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_fixangle");
    return setters_qcc_fixangle_array[type](entity, value);
}
float set_qcc_v_angle_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_v_angle");
    return setters_qcc_v_angle_array_x[type](entity, value);
}
float set_qcc_v_angle_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_v_angle");
    return setters_qcc_v_angle_array_y[type](entity, value);
}
float set_qcc_v_angle_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_v_angle");
    return setters_qcc_v_angle_array_z[type](entity, value);
}
vector set_qcc_v_angle(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_v_angle");
    return setters_qcc_v_angle_array[type](entity, value);
}
float set_qcc_idealpitch(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_idealpitch");
    return setters_qcc_idealpitch_array[type](entity, value);
}
string_t set_qcc_netname(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_netname");
    return setters_qcc_netname_array[type](entity, value);
}
int set_qcc_enemy(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_enemy");
    return setters_qcc_enemy_array[type](entity, value);
}
float set_qcc_flags(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_flags");
    return setters_qcc_flags_array[type](entity, value);
}
float set_qcc_team(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_team");
    return setters_qcc_team_array[type](entity, value);
}
float set_qcc_max_health(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_max_health");
    return setters_qcc_max_health_array[type](entity, value);
}
float set_qcc_teleport_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_teleport_time");
    return setters_qcc_teleport_time_array[type](entity, value);
}
float set_qcc_armortype(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_armortype");
    return setters_qcc_armortype_array[type](entity, value);
}
float set_qcc_armorvalue(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_armorvalue");
    return setters_qcc_armorvalue_array[type](entity, value);
}
float set_qcc_waterlevel(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_waterlevel");
    return setters_qcc_waterlevel_array[type](entity, value);
}
float set_qcc_watertype(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_watertype");
    return setters_qcc_watertype_array[type](entity, value);
}
float set_qcc_ideal_yaw(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ideal_yaw");
    return setters_qcc_ideal_yaw_array[type](entity, value);
}
float set_qcc_yaw_speed(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_yaw_speed");
    return setters_qcc_yaw_speed_array[type](entity, value);
}
int set_qcc_goalentity(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_goalentity");
    return setters_qcc_goalentity_array[type](entity, value);
}
float set_qcc_spawnflags(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_spawnflags");
    return setters_qcc_spawnflags_array[type](entity, value);
}
string_t set_qcc_target(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_target");
    return setters_qcc_target_array[type](entity, value);
}
string_t set_qcc_targetname(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_targetname");
    return setters_qcc_targetname_array[type](entity, value);
}
float set_qcc_dmg_take(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_take");
    return setters_qcc_dmg_take_array[type](entity, value);
}
float set_qcc_dmg_save(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_save");
    return setters_qcc_dmg_save_array[type](entity, value);
}
int set_qcc_dmg_inflictor(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_inflictor");
    return setters_qcc_dmg_inflictor_array[type](entity, value);
}
int set_qcc_owner(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_owner");
    return setters_qcc_owner_array[type](entity, value);
}
float set_qcc_movedir_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movedir");
    return setters_qcc_movedir_array_x[type](entity, value);
}
float set_qcc_movedir_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movedir");
    return setters_qcc_movedir_array_y[type](entity, value);
}
float set_qcc_movedir_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movedir");
    return setters_qcc_movedir_array_z[type](entity, value);
}
vector set_qcc_movedir(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movedir");
    return setters_qcc_movedir_array[type](entity, value);
}
string_t set_qcc_message(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_message");
    return setters_qcc_message_array[type](entity, value);
}
float set_qcc_sounds(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_sounds");
    return setters_qcc_sounds_array[type](entity, value);
}
string_t set_qcc_noise(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise");
    return setters_qcc_noise_array[type](entity, value);
}
string_t set_qcc_noise1(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise1");
    return setters_qcc_noise1_array[type](entity, value);
}
string_t set_qcc_noise2(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise2");
    return setters_qcc_noise2_array[type](entity, value);
}
string_t set_qcc_noise3(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise3");
    return setters_qcc_noise3_array[type](entity, value);
}
string_t set_qcc_map(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_map");
    return setters_qcc_map_array[type](entity, value);
}
float set_qcc_worldtype(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_worldtype");
    return setters_qcc_worldtype_array[type](entity, value);
}
string_t set_qcc_killtarget(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_killtarget");
    return setters_qcc_killtarget_array[type](entity, value);
}
float set_qcc_style(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_style");
    return setters_qcc_style_array[type](entity, value);
}
func_t set_qcc_th_stand(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_stand");
    return setters_qcc_th_stand_array[type](entity, value);
}
func_t set_qcc_th_walk(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_walk");
    return setters_qcc_th_walk_array[type](entity, value);
}
func_t set_qcc_th_run(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_run");
    return setters_qcc_th_run_array[type](entity, value);
}
func_t set_qcc_th_missile(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_missile");
    return setters_qcc_th_missile_array[type](entity, value);
}
func_t set_qcc_th_melee(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_melee");
    return setters_qcc_th_melee_array[type](entity, value);
}
func_t set_qcc_th_pain(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_pain");
    return setters_qcc_th_pain_array[type](entity, value);
}
func_t set_qcc_th_die(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_die");
    return setters_qcc_th_die_array[type](entity, value);
}
int set_qcc_oldenemy(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldenemy");
    return setters_qcc_oldenemy_array[type](entity, value);
}
float set_qcc_speed(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_speed");
    return setters_qcc_speed_array[type](entity, value);
}
float set_qcc_lefty(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_lefty");
    return setters_qcc_lefty_array[type](entity, value);
}
float set_qcc_search_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_search_time");
    return setters_qcc_search_time_array[type](entity, value);
}
float set_qcc_attack_state(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_attack_state");
    return setters_qcc_attack_state_array[type](entity, value);
}
float set_qcc_walkframe(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_walkframe");
    return setters_qcc_walkframe_array[type](entity, value);
}
float set_qcc_attack_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_attack_finished");
    return setters_qcc_attack_finished_array[type](entity, value);
}
float set_qcc_pain_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pain_finished");
    return setters_qcc_pain_finished_array[type](entity, value);
}
float set_qcc_invincible_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_finished");
    return setters_qcc_invincible_finished_array[type](entity, value);
}
float set_qcc_invisible_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_finished");
    return setters_qcc_invisible_finished_array[type](entity, value);
}
float set_qcc_super_damage_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_damage_finished");
    return setters_qcc_super_damage_finished_array[type](entity, value);
}
float set_qcc_radsuit_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_radsuit_finished");
    return setters_qcc_radsuit_finished_array[type](entity, value);
}
float set_qcc_invincible_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_time");
    return setters_qcc_invincible_time_array[type](entity, value);
}
float set_qcc_invincible_sound(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_sound");
    return setters_qcc_invincible_sound_array[type](entity, value);
}
float set_qcc_invisible_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_time");
    return setters_qcc_invisible_time_array[type](entity, value);
}
float set_qcc_invisible_sound(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_sound");
    return setters_qcc_invisible_sound_array[type](entity, value);
}
float set_qcc_super_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_time");
    return setters_qcc_super_time_array[type](entity, value);
}
float set_qcc_super_sound(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_sound");
    return setters_qcc_super_sound_array[type](entity, value);
}
float set_qcc_rad_time(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_rad_time");
    return setters_qcc_rad_time_array[type](entity, value);
}
float set_qcc_fly_sound(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_fly_sound");
    return setters_qcc_fly_sound_array[type](entity, value);
}
float set_qcc_axhitme(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_axhitme");
    return setters_qcc_axhitme_array[type](entity, value);
}
float set_qcc_show_hostile(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_show_hostile");
    return setters_qcc_show_hostile_array[type](entity, value);
}
float set_qcc_jump_flag(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_jump_flag");
    return setters_qcc_jump_flag_array[type](entity, value);
}
float set_qcc_swim_flag(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_swim_flag");
    return setters_qcc_swim_flag_array[type](entity, value);
}
float set_qcc_air_finished(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_air_finished");
    return setters_qcc_air_finished_array[type](entity, value);
}
float set_qcc_bubble_count(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_bubble_count");
    return setters_qcc_bubble_count_array[type](entity, value);
}
string_t set_qcc_deathtype(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_deathtype");
    return setters_qcc_deathtype_array[type](entity, value);
}
string_t set_qcc_mdl(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mdl");
    return setters_qcc_mdl_array[type](entity, value);
}
float set_qcc_mangle_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mangle");
    return setters_qcc_mangle_array_x[type](entity, value);
}
float set_qcc_mangle_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mangle");
    return setters_qcc_mangle_array_y[type](entity, value);
}
float set_qcc_mangle_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mangle");
    return setters_qcc_mangle_array_z[type](entity, value);
}
vector set_qcc_mangle(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mangle");
    return setters_qcc_mangle_array[type](entity, value);
}
float set_qcc_t_length(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_t_length");
    return setters_qcc_t_length_array[type](entity, value);
}
float set_qcc_t_width(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_t_width");
    return setters_qcc_t_width_array[type](entity, value);
}
float set_qcc_dest_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest");
    return setters_qcc_dest_array_x[type](entity, value);
}
float set_qcc_dest_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest");
    return setters_qcc_dest_array_y[type](entity, value);
}
float set_qcc_dest_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest");
    return setters_qcc_dest_array_z[type](entity, value);
}
vector set_qcc_dest(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest");
    return setters_qcc_dest_array[type](entity, value);
}
float set_qcc_dest1_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest1");
    return setters_qcc_dest1_array_x[type](entity, value);
}
float set_qcc_dest1_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest1");
    return setters_qcc_dest1_array_y[type](entity, value);
}
float set_qcc_dest1_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest1");
    return setters_qcc_dest1_array_z[type](entity, value);
}
vector set_qcc_dest1(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest1");
    return setters_qcc_dest1_array[type](entity, value);
}
float set_qcc_dest2_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest2");
    return setters_qcc_dest2_array_x[type](entity, value);
}
float set_qcc_dest2_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest2");
    return setters_qcc_dest2_array_y[type](entity, value);
}
float set_qcc_dest2_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest2");
    return setters_qcc_dest2_array_z[type](entity, value);
}
vector set_qcc_dest2(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest2");
    return setters_qcc_dest2_array[type](entity, value);
}
float set_qcc_wait(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_wait");
    return setters_qcc_wait_array[type](entity, value);
}
float set_qcc_delay(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_delay");
    return setters_qcc_delay_array[type](entity, value);
}
int set_qcc_trigger_field(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_trigger_field");
    return setters_qcc_trigger_field_array[type](entity, value);
}
string_t set_qcc_noise4(edict_t *entity, string_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise4");
    return setters_qcc_noise4_array[type](entity, value);
}
float set_qcc_pausetime(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pausetime");
    return setters_qcc_pausetime_array[type](entity, value);
}
int set_qcc_movetarget(edict_t *entity, int value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movetarget");
    return setters_qcc_movetarget_array[type](entity, value);
}
float set_qcc_aflag(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_aflag");
    return setters_qcc_aflag_array[type](entity, value);
}
float set_qcc_dmg(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg");
    return setters_qcc_dmg_array[type](entity, value);
}
float set_qcc_cnt(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_cnt");
    return setters_qcc_cnt_array[type](entity, value);
}
func_t set_qcc_think1(edict_t *entity, func_t value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_think1");
    return setters_qcc_think1_array[type](entity, value);
}
float set_qcc_finaldest_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finaldest");
    return setters_qcc_finaldest_array_x[type](entity, value);
}
float set_qcc_finaldest_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finaldest");
    return setters_qcc_finaldest_array_y[type](entity, value);
}
float set_qcc_finaldest_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finaldest");
    return setters_qcc_finaldest_array_z[type](entity, value);
}
vector set_qcc_finaldest(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finaldest");
    return setters_qcc_finaldest_array[type](entity, value);
}
float set_qcc_finalangle_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finalangle");
    return setters_qcc_finalangle_array_x[type](entity, value);
}
float set_qcc_finalangle_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finalangle");
    return setters_qcc_finalangle_array_y[type](entity, value);
}
float set_qcc_finalangle_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finalangle");
    return setters_qcc_finalangle_array_z[type](entity, value);
}
vector set_qcc_finalangle(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finalangle");
    return setters_qcc_finalangle_array[type](entity, value);
}
float set_qcc_count(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_count");
    return setters_qcc_count_array[type](entity, value);
}
float set_qcc_lip(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_lip");
    return setters_qcc_lip_array[type](entity, value);
}
float set_qcc_state(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_state");
    return setters_qcc_state_array[type](entity, value);
}
float set_qcc_pos1_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos1");
    return setters_qcc_pos1_array_x[type](entity, value);
}
float set_qcc_pos1_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos1");
    return setters_qcc_pos1_array_y[type](entity, value);
}
float set_qcc_pos1_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos1");
    return setters_qcc_pos1_array_z[type](entity, value);
}
vector set_qcc_pos1(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos1");
    return setters_qcc_pos1_array[type](entity, value);
}
float set_qcc_pos2_x(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos2");
    return setters_qcc_pos2_array_x[type](entity, value);
}
float set_qcc_pos2_y(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos2");
    return setters_qcc_pos2_array_y[type](entity, value);
}
float set_qcc_pos2_z(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos2");
    return setters_qcc_pos2_array_z[type](entity, value);
}
vector set_qcc_pos2(edict_t *entity, vector value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos2");
    return setters_qcc_pos2_array[type](entity, value);
}
float set_qcc_height(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_height");
    return setters_qcc_height_array[type](entity, value);
}
float set_qcc_waitmin(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_waitmin");
    return setters_qcc_waitmin_array[type](entity, value);
}
float set_qcc_healamount(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_healamount");
    return setters_qcc_healamount_array[type](entity, value);
}
float set_qcc_healtype(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_healtype");
    return setters_qcc_healtype_array[type](entity, value);
}
float set_qcc_dmgtime(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmgtime");
    return setters_qcc_dmgtime_array[type](entity, value);
}
float set_qcc_inpain(edict_t *entity, float value)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_inpain");
    return setters_qcc_inpain_array[type](entity, value);
}
float get_qcc_modelindex(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_modelindex");
    return getters_qcc_modelindex_array[type](entity);
}
float get_qcc_ltime(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ltime");
    return getters_qcc_ltime_array[type](entity);
}
float get_qcc_movetype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movetype");
    return getters_qcc_movetype_array[type](entity);
}
float get_qcc_solid(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_solid");
    return getters_qcc_solid_array[type](entity);
}
vector get_qcc_origin(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_origin");
    return getters_qcc_origin_array[type](entity);
}
vector get_qcc_oldorigin(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldorigin");
    return getters_qcc_oldorigin_array[type](entity);
}
vector get_qcc_velocity(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_velocity");
    return getters_qcc_velocity_array[type](entity);
}
vector get_qcc_angles(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_angles");
    return getters_qcc_angles_array[type](entity);
}
vector get_qcc_avelocity(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_avelocity");
    return getters_qcc_avelocity_array[type](entity);
}
vector get_qcc_punchangle(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_punchangle");
    return getters_qcc_punchangle_array[type](entity);
}
string_t get_qcc_model(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_model");
    return getters_qcc_model_array[type](entity);
}
float get_qcc_frame(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_frame");
    return getters_qcc_frame_array[type](entity);
}
float get_qcc_skin(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_skin");
    return getters_qcc_skin_array[type](entity);
}
float get_qcc_effects(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_effects");
    return getters_qcc_effects_array[type](entity);
}
vector get_qcc_mins(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mins");
    return getters_qcc_mins_array[type](entity);
}
vector get_qcc_maxs(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_maxs");
    return getters_qcc_maxs_array[type](entity);
}
func_t get_qcc_touch(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_touch");
    return getters_qcc_touch_array[type](entity);
}
func_t get_qcc_use(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_use");
    return getters_qcc_use_array[type](entity);
}
func_t get_qcc_think(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_think");
    return getters_qcc_think_array[type](entity);
}
func_t get_qcc_blocked(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_blocked");
    return getters_qcc_blocked_array[type](entity);
}
float get_qcc_nextthink(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_nextthink");
    return getters_qcc_nextthink_array[type](entity);
}
int get_qcc_groundentity(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_groundentity");
    return getters_qcc_groundentity_array[type](entity);
}
float get_qcc_health(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_health");
    return getters_qcc_health_array[type](entity);
}
float get_qcc_frags(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_frags");
    return getters_qcc_frags_array[type](entity);
}
float get_qcc_weapon(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weapon");
    return getters_qcc_weapon_array[type](entity);
}
string_t get_qcc_weaponmodel(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weaponmodel");
    return getters_qcc_weaponmodel_array[type](entity);
}
float get_qcc_weaponframe(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_weaponframe");
    return getters_qcc_weaponframe_array[type](entity);
}
float get_qcc_currentammo(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_currentammo");
    return getters_qcc_currentammo_array[type](entity);
}
float get_qcc_ammo_shells(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_shells");
    return getters_qcc_ammo_shells_array[type](entity);
}
float get_qcc_ammo_nails(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_nails");
    return getters_qcc_ammo_nails_array[type](entity);
}
float get_qcc_ammo_rockets(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_rockets");
    return getters_qcc_ammo_rockets_array[type](entity);
}
float get_qcc_ammo_cells(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ammo_cells");
    return getters_qcc_ammo_cells_array[type](entity);
}
float get_qcc_items(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_items");
    return getters_qcc_items_array[type](entity);
}
float get_qcc_takedamage(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_takedamage");
    return getters_qcc_takedamage_array[type](entity);
}
int get_qcc_chain(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_chain");
    return getters_qcc_chain_array[type](entity);
}
float get_qcc_deadflag(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_deadflag");
    return getters_qcc_deadflag_array[type](entity);
}
vector get_qcc_view_ofs(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_view_ofs");
    return getters_qcc_view_ofs_array[type](entity);
}
float get_qcc_button0(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button0");
    return getters_qcc_button0_array[type](entity);
}
float get_qcc_button1(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button1");
    return getters_qcc_button1_array[type](entity);
}
float get_qcc_button2(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_button2");
    return getters_qcc_button2_array[type](entity);
}
float get_qcc_impulse(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_impulse");
    return getters_qcc_impulse_array[type](entity);
}
float get_qcc_fixangle(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_fixangle");
    return getters_qcc_fixangle_array[type](entity);
}
vector get_qcc_v_angle(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_v_angle");
    return getters_qcc_v_angle_array[type](entity);
}
float get_qcc_idealpitch(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_idealpitch");
    return getters_qcc_idealpitch_array[type](entity);
}
string_t get_qcc_netname(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_netname");
    return getters_qcc_netname_array[type](entity);
}
int get_qcc_enemy(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_enemy");
    return getters_qcc_enemy_array[type](entity);
}
float get_qcc_flags(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_flags");
    return getters_qcc_flags_array[type](entity);
}
float get_qcc_team(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_team");
    return getters_qcc_team_array[type](entity);
}
float get_qcc_max_health(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_max_health");
    return getters_qcc_max_health_array[type](entity);
}
float get_qcc_teleport_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_teleport_time");
    return getters_qcc_teleport_time_array[type](entity);
}
float get_qcc_armortype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_armortype");
    return getters_qcc_armortype_array[type](entity);
}
float get_qcc_armorvalue(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_armorvalue");
    return getters_qcc_armorvalue_array[type](entity);
}
float get_qcc_waterlevel(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_waterlevel");
    return getters_qcc_waterlevel_array[type](entity);
}
float get_qcc_watertype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_watertype");
    return getters_qcc_watertype_array[type](entity);
}
float get_qcc_ideal_yaw(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_ideal_yaw");
    return getters_qcc_ideal_yaw_array[type](entity);
}
float get_qcc_yaw_speed(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_yaw_speed");
    return getters_qcc_yaw_speed_array[type](entity);
}
int get_qcc_goalentity(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_goalentity");
    return getters_qcc_goalentity_array[type](entity);
}
float get_qcc_spawnflags(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_spawnflags");
    return getters_qcc_spawnflags_array[type](entity);
}
string_t get_qcc_target(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_target");
    return getters_qcc_target_array[type](entity);
}
string_t get_qcc_targetname(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_targetname");
    return getters_qcc_targetname_array[type](entity);
}
float get_qcc_dmg_take(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_take");
    return getters_qcc_dmg_take_array[type](entity);
}
float get_qcc_dmg_save(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_save");
    return getters_qcc_dmg_save_array[type](entity);
}
int get_qcc_dmg_inflictor(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg_inflictor");
    return getters_qcc_dmg_inflictor_array[type](entity);
}
int get_qcc_owner(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_owner");
    return getters_qcc_owner_array[type](entity);
}
vector get_qcc_movedir(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movedir");
    return getters_qcc_movedir_array[type](entity);
}
string_t get_qcc_message(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_message");
    return getters_qcc_message_array[type](entity);
}
float get_qcc_sounds(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_sounds");
    return getters_qcc_sounds_array[type](entity);
}
string_t get_qcc_noise(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise");
    return getters_qcc_noise_array[type](entity);
}
string_t get_qcc_noise1(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise1");
    return getters_qcc_noise1_array[type](entity);
}
string_t get_qcc_noise2(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise2");
    return getters_qcc_noise2_array[type](entity);
}
string_t get_qcc_noise3(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise3");
    return getters_qcc_noise3_array[type](entity);
}
string_t get_qcc_map(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_map");
    return getters_qcc_map_array[type](entity);
}
float get_qcc_worldtype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_worldtype");
    return getters_qcc_worldtype_array[type](entity);
}
string_t get_qcc_killtarget(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_killtarget");
    return getters_qcc_killtarget_array[type](entity);
}
float get_qcc_style(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_style");
    return getters_qcc_style_array[type](entity);
}
func_t get_qcc_th_stand(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_stand");
    return getters_qcc_th_stand_array[type](entity);
}
func_t get_qcc_th_walk(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_walk");
    return getters_qcc_th_walk_array[type](entity);
}
func_t get_qcc_th_run(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_run");
    return getters_qcc_th_run_array[type](entity);
}
func_t get_qcc_th_missile(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_missile");
    return getters_qcc_th_missile_array[type](entity);
}
func_t get_qcc_th_melee(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_melee");
    return getters_qcc_th_melee_array[type](entity);
}
func_t get_qcc_th_pain(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_pain");
    return getters_qcc_th_pain_array[type](entity);
}
func_t get_qcc_th_die(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_th_die");
    return getters_qcc_th_die_array[type](entity);
}
int get_qcc_oldenemy(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_oldenemy");
    return getters_qcc_oldenemy_array[type](entity);
}
float get_qcc_speed(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_speed");
    return getters_qcc_speed_array[type](entity);
}
float get_qcc_lefty(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_lefty");
    return getters_qcc_lefty_array[type](entity);
}
float get_qcc_search_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_search_time");
    return getters_qcc_search_time_array[type](entity);
}
float get_qcc_attack_state(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_attack_state");
    return getters_qcc_attack_state_array[type](entity);
}
float get_qcc_walkframe(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_walkframe");
    return getters_qcc_walkframe_array[type](entity);
}
float get_qcc_attack_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_attack_finished");
    return getters_qcc_attack_finished_array[type](entity);
}
float get_qcc_pain_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pain_finished");
    return getters_qcc_pain_finished_array[type](entity);
}
float get_qcc_invincible_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_finished");
    return getters_qcc_invincible_finished_array[type](entity);
}
float get_qcc_invisible_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_finished");
    return getters_qcc_invisible_finished_array[type](entity);
}
float get_qcc_super_damage_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_damage_finished");
    return getters_qcc_super_damage_finished_array[type](entity);
}
float get_qcc_radsuit_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_radsuit_finished");
    return getters_qcc_radsuit_finished_array[type](entity);
}
float get_qcc_invincible_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_time");
    return getters_qcc_invincible_time_array[type](entity);
}
float get_qcc_invincible_sound(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invincible_sound");
    return getters_qcc_invincible_sound_array[type](entity);
}
float get_qcc_invisible_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_time");
    return getters_qcc_invisible_time_array[type](entity);
}
float get_qcc_invisible_sound(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_invisible_sound");
    return getters_qcc_invisible_sound_array[type](entity);
}
float get_qcc_super_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_time");
    return getters_qcc_super_time_array[type](entity);
}
float get_qcc_super_sound(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_super_sound");
    return getters_qcc_super_sound_array[type](entity);
}
float get_qcc_rad_time(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_rad_time");
    return getters_qcc_rad_time_array[type](entity);
}
float get_qcc_fly_sound(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_fly_sound");
    return getters_qcc_fly_sound_array[type](entity);
}
float get_qcc_axhitme(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_axhitme");
    return getters_qcc_axhitme_array[type](entity);
}
float get_qcc_show_hostile(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_show_hostile");
    return getters_qcc_show_hostile_array[type](entity);
}
float get_qcc_jump_flag(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_jump_flag");
    return getters_qcc_jump_flag_array[type](entity);
}
float get_qcc_swim_flag(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_swim_flag");
    return getters_qcc_swim_flag_array[type](entity);
}
float get_qcc_air_finished(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_air_finished");
    return getters_qcc_air_finished_array[type](entity);
}
float get_qcc_bubble_count(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_bubble_count");
    return getters_qcc_bubble_count_array[type](entity);
}
string_t get_qcc_deathtype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_deathtype");
    return getters_qcc_deathtype_array[type](entity);
}
string_t get_qcc_mdl(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mdl");
    return getters_qcc_mdl_array[type](entity);
}
vector get_qcc_mangle(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_mangle");
    return getters_qcc_mangle_array[type](entity);
}
float get_qcc_t_length(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_t_length");
    return getters_qcc_t_length_array[type](entity);
}
float get_qcc_t_width(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_t_width");
    return getters_qcc_t_width_array[type](entity);
}
vector get_qcc_dest(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest");
    return getters_qcc_dest_array[type](entity);
}
vector get_qcc_dest1(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest1");
    return getters_qcc_dest1_array[type](entity);
}
vector get_qcc_dest2(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dest2");
    return getters_qcc_dest2_array[type](entity);
}
float get_qcc_wait(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_wait");
    return getters_qcc_wait_array[type](entity);
}
float get_qcc_delay(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_delay");
    return getters_qcc_delay_array[type](entity);
}
int get_qcc_trigger_field(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_trigger_field");
    return getters_qcc_trigger_field_array[type](entity);
}
string_t get_qcc_noise4(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_noise4");
    return getters_qcc_noise4_array[type](entity);
}
float get_qcc_pausetime(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pausetime");
    return getters_qcc_pausetime_array[type](entity);
}
int get_qcc_movetarget(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_movetarget");
    return getters_qcc_movetarget_array[type](entity);
}
float get_qcc_aflag(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_aflag");
    return getters_qcc_aflag_array[type](entity);
}
float get_qcc_dmg(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmg");
    return getters_qcc_dmg_array[type](entity);
}
float get_qcc_cnt(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_cnt");
    return getters_qcc_cnt_array[type](entity);
}
func_t get_qcc_think1(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_think1");
    return getters_qcc_think1_array[type](entity);
}
vector get_qcc_finaldest(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finaldest");
    return getters_qcc_finaldest_array[type](entity);
}
vector get_qcc_finalangle(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_finalangle");
    return getters_qcc_finalangle_array[type](entity);
}
float get_qcc_count(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_count");
    return getters_qcc_count_array[type](entity);
}
float get_qcc_lip(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_lip");
    return getters_qcc_lip_array[type](entity);
}
float get_qcc_state(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_state");
    return getters_qcc_state_array[type](entity);
}
vector get_qcc_pos1(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos1");
    return getters_qcc_pos1_array[type](entity);
}
vector get_qcc_pos2(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_pos2");
    return getters_qcc_pos2_array[type](entity);
}
float get_qcc_height(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_height");
    return getters_qcc_height_array[type](entity);
}
float get_qcc_waitmin(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_waitmin");
    return getters_qcc_waitmin_array[type](entity);
}
float get_qcc_healamount(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_healamount");
    return getters_qcc_healamount_array[type](entity);
}
float get_qcc_healtype(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_healtype");
    return getters_qcc_healtype_array[type](entity);
}
float get_qcc_dmgtime(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_dmgtime");
    return getters_qcc_dmgtime_array[type](entity);
}
float get_qcc_inpain(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("qcc_inpain");
    return getters_qcc_inpain_array[type](entity);
}
entLeaves_t * get_entLeaves(edict_t *entity)
{
    int type = qcc_classname2type[entity->qcc_classname];
    DEBUG_FIELD("entLeaves");
    return getters_entLeaves_array[type](entity);
}
float setter_qcc_modelindex_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_light(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_worldspawn(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_static_light(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_modelindex = (value);
    return value;
}
float setter_qcc_modelindex_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_modelindex = (value);
    return value;
}
float setter_qcc_ltime_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ltime = (value);
    return value;
}
float setter_qcc_ltime_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_ltime = (value);
    return value;
}
float setter_qcc_ltime_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_ltime = (value);
    return value;
}
float setter_qcc_ltime_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_ltime = (value);
    return value;
}
float setter_qcc_movetype_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_worldspawn(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_movetype_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_movetype = (value);
    return value;
}
float setter_qcc_solid_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_path_corner(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_worldspawn(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_teledeath(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_solid_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_solid = (value);
    return value;
}
float setter_qcc_origin_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_sound_x(edict_t *entity, float value)
{
    ((sound_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_sound_y(edict_t *entity, float value)
{
    ((sound_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_sound_z(edict_t *entity, float value)
{
    ((sound_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_sound(edict_t *entity, vector value)
{
    ((sound_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bodyque_x(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bodyque_y(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bodyque_z(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_bodyque(edict_t *entity, vector value)
{
    ((bodyque_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_light_x(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_light_y(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_light_z(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_light(edict_t *entity, vector value)
{
    ((light_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_trigger_x(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_trigger_y(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_trigger_z(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_trigger(edict_t *entity, vector value)
{
    ((trigger_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_info_x(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_info_y(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_info_z(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_info(edict_t *entity, vector value)
{
    ((info_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_origin.x = (value);
    return value;
}
float setter_qcc_origin_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_origin.y = (value);
    return value;
}
float setter_qcc_origin_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_origin.z = (value);
    return value;
}
vector setter_qcc_origin_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_origin = v(value);
    return value;
}
float setter_qcc_origin_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_origin.x = (value);
    return value;
}
float setter_qcc_origin_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_origin.y = (value);
    return value;
}
float setter_qcc_origin_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_origin.z = (value);
    return value;
}
vector setter_qcc_origin_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_origin = v(value);
    return value;
}
float setter_qcc_origin_path_corner_x(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_path_corner_y(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_path_corner_z(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_path_corner(edict_t *entity, vector value)
{
    ((path_corner_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_worldspawn_x(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_worldspawn_y(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_worldspawn_z(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_worldspawn(edict_t *entity, vector value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_tfog_x(edict_t *entity, float value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_tfog_y(edict_t *entity, float value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_tfog_z(edict_t *entity, float value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_nh_tfog(edict_t *entity, vector value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bubble_x(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bubble_y(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_bubble_z(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_bubble(edict_t *entity, vector value)
{
    ((bubble_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_teledeath_x(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_teledeath_y(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_teledeath_z(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_teledeath(edict_t *entity, vector value)
{
    ((teledeath_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_origin.x = (value);
    return value;
}
float setter_qcc_origin_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_origin.y = (value);
    return value;
}
float setter_qcc_origin_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_origin.z = (value);
    return value;
}
vector setter_qcc_origin_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_origin = v(value);
    return value;
}
float setter_qcc_origin_static_light_x(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_static_light_y(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_static_light_z(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_static_light(edict_t *entity, vector value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_origin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_origin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_origin_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_origin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_origin_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_origin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_oldorigin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_oldorigin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_oldorigin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_oldorigin_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_oldorigin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_oldorigin.x = (value);
    return value;
}
float setter_qcc_oldorigin_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_oldorigin.y = (value);
    return value;
}
float setter_qcc_oldorigin_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_oldorigin.z = (value);
    return value;
}
vector setter_qcc_oldorigin_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_oldorigin = v(value);
    return value;
}
float setter_qcc_oldorigin_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_oldorigin.x = (value);
    return value;
}
float setter_qcc_oldorigin_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_oldorigin.y = (value);
    return value;
}
float setter_qcc_oldorigin_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_oldorigin.z = (value);
    return value;
}
vector setter_qcc_oldorigin_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_oldorigin = v(value);
    return value;
}
float setter_qcc_oldorigin_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_oldorigin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_oldorigin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_oldorigin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_oldorigin_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_oldorigin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_oldorigin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_oldorigin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_oldorigin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_oldorigin_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_oldorigin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_oldorigin.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_oldorigin.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_oldorigin.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_oldorigin_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_oldorigin = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_oldorigin_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_oldorigin.x = (value);
    return value;
}
float setter_qcc_oldorigin_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_oldorigin.y = (value);
    return value;
}
float setter_qcc_oldorigin_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_oldorigin.z = (value);
    return value;
}
vector setter_qcc_oldorigin_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_oldorigin = v(value);
    return value;
}
float setter_qcc_velocity_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bodyque_x(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bodyque_y(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bodyque_z(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_bodyque(edict_t *entity, vector value)
{
    ((bodyque_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bubble_x(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bubble_y(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_bubble_z(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_bubble(edict_t *entity, vector value)
{
    ((bubble_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_velocity.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_velocity.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_velocity_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_velocity.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_velocity_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_velocity = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_angles_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_bodyque_x(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_bodyque_y(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_bodyque_z(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_bodyque(edict_t *entity, vector value)
{
    ((bodyque_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_light_x(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_light_y(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_light_z(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_light(edict_t *entity, vector value)
{
    ((light_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_trigger_x(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_trigger_y(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_trigger_z(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_trigger(edict_t *entity, vector value)
{
    ((trigger_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_info_x(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_info_y(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_info_z(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_info(edict_t *entity, vector value)
{
    ((info_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_angles_static_light_x(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_angles.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_angles_static_light_y(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_angles.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_angles_static_light_z(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_angles.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_angles_static_light(edict_t *entity, vector value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_angles = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_angles_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_angles.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_angles.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_angles_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_angles.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_angles_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_angles = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_avelocity.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_avelocity.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_avelocity.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_avelocity_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_avelocity = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_avelocity.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_avelocity.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_avelocity.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_avelocity_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_avelocity = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_avelocity.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_avelocity.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_avelocity.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_avelocity_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_avelocity = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_avelocity.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_avelocity.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_avelocity_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_avelocity.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_avelocity_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_avelocity = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_punchangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_punchangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_punchangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_punchangle_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_punchangle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_punchangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_punchangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_punchangle_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_punchangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_punchangle_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_punchangle = vfloatToShortAngle(value);
    return value;
}
string_t setter_qcc_model_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_missile(edict_t *entity, string_t value)
{
    ((missile_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_bodyque(edict_t *entity, string_t value)
{
    ((bodyque_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_light(edict_t *entity, string_t value)
{
    ((light_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_worldspawn(edict_t *entity, string_t value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_nh_backpack(edict_t *entity, string_t value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_explo_box(edict_t *entity, string_t value)
{
    ((explo_box_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_bubble(edict_t *entity, string_t value)
{
    ((bubble_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_monster(edict_t *entity, string_t value)
{
    ((monster_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
string_t setter_qcc_model_static_light(edict_t *entity, string_t value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_model = (value);
    return value;
}
string_t setter_qcc_model_nh_wiz_startfast(edict_t *entity, string_t value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_model = (value);
    return value;
}
float setter_qcc_frame_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_light(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_frame_static_light(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_frame = (value);
    return value;
}
float setter_qcc_frame_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_frame = (value);
    return value;
}
float setter_qcc_skin_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_skin = (value);
    return value;
}
float setter_qcc_skin_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_skin = (value);
    return value;
}
float setter_qcc_skin_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_skin = (value);
    return value;
}
float setter_qcc_skin_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_skin = (value);
    return value;
}
float setter_qcc_skin_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_skin = (value);
    return value;
}
float setter_qcc_effects_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_effects_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_effects = (value);
    return value;
}
float setter_qcc_mins_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_light_x(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_light_y(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_light_z(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_light(edict_t *entity, vector value)
{
    ((light_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_trigger_x(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_trigger_y(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_trigger_z(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_trigger(edict_t *entity, vector value)
{
    ((trigger_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_bubble_x(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_bubble_y(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_bubble_z(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_bubble(edict_t *entity, vector value)
{
    ((bubble_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_teledeath_x(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_teledeath_y(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_teledeath_z(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_teledeath(edict_t *entity, vector value)
{
    ((teledeath_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_static_light_x(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_static_light_y(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_static_light_z(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_static_light(edict_t *entity, vector value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_mins.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_mins.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_mins_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_mins.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_mins_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_mins = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_missile_x(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_missile_y(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_missile_z(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_missile(edict_t *entity, vector value)
{
    ((missile_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_light_x(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_light_y(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_light_z(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_light(edict_t *entity, vector value)
{
    ((light_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_trigger_x(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_trigger_y(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_trigger_z(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_trigger(edict_t *entity, vector value)
{
    ((trigger_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_item_x(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_item_y(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_item_z(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_item(edict_t *entity, vector value)
{
    ((item_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_backpack_x(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_backpack_y(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_backpack_z(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_nh_backpack(edict_t *entity, vector value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_explo_box_x(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_explo_box_y(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_explo_box_z(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_explo_box(edict_t *entity, vector value)
{
    ((explo_box_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_bubble_x(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_bubble_y(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_bubble_z(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_bubble(edict_t *entity, vector value)
{
    ((bubble_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_teledeath_x(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_teledeath_y(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_teledeath_z(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_teledeath(edict_t *entity, vector value)
{
    ((teledeath_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_static_light_x(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_static_light_y(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_static_light_z(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_static_light(edict_t *entity, vector value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_maxs = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_maxs.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_maxs.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_maxs_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_maxs.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_maxs_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_maxs = vfloatToShort13p3(value);
    return value;
}
func_t setter_qcc_touch_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_missile(edict_t *entity, func_t value)
{
    ((missile_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_trigger(edict_t *entity, func_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_player(edict_t *entity, func_t value)
{
    ((player_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_item(edict_t *entity, func_t value)
{
    ((item_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_nh_backpack(edict_t *entity, func_t value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_explo_box(edict_t *entity, func_t value)
{
    ((explo_box_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_bubble(edict_t *entity, func_t value)
{
    ((bubble_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_teledeath(edict_t *entity, func_t value)
{
    ((teledeath_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_touch_nh_wiz_startfast(edict_t *entity, func_t value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_touch = (value);
    return value;
}
func_t setter_qcc_use_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_light(edict_t *entity, func_t value)
{
    ((light_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_trigger(edict_t *entity, func_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_player(edict_t *entity, func_t value)
{
    ((player_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_use = (value);
    return value;
}
func_t setter_qcc_use_static_light(edict_t *entity, func_t value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_use = (value);
    return value;
}
func_t setter_qcc_think_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_missile(edict_t *entity, func_t value)
{
    ((missile_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_trigger(edict_t *entity, func_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_player(edict_t *entity, func_t value)
{
    ((player_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_item(edict_t *entity, func_t value)
{
    ((item_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_delayedUse(edict_t *entity, func_t value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_nh_backpack(edict_t *entity, func_t value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_nh_tfog(edict_t *entity, func_t value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_explo_box(edict_t *entity, func_t value)
{
    ((explo_box_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_bubble(edict_t *entity, func_t value)
{
    ((bubble_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_teledeath(edict_t *entity, func_t value)
{
    ((teledeath_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_timer(edict_t *entity, func_t value)
{
    ((timer_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_think_nh_wiz_startfast(edict_t *entity, func_t value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_think = (value);
    return value;
}
func_t setter_qcc_blocked_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_blocked = (value);
    return value;
}
func_t setter_qcc_blocked_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_blocked = (value);
    return value;
}
float setter_qcc_nextthink_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_delayedUse(edict_t *entity, float value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_nh_tfog(edict_t *entity, float value)
{
    ((nh_tfog_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_teledeath(edict_t *entity, float value)
{
    ((teledeath_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_timer(edict_t *entity, float value)
{
    ((timer_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
float setter_qcc_nextthink_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_nextthink = (value);
    return value;
}
int setter_qcc_groundentity_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_missile(edict_t *entity, int value)
{
    ((missile_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_player(edict_t *entity, int value)
{
    ((player_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_item(edict_t *entity, int value)
{
    ((item_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_nh_backpack(edict_t *entity, int value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_explo_box(edict_t *entity, int value)
{
    ((explo_box_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
int setter_qcc_groundentity_nh_wiz_startfast(edict_t *entity, int value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_groundentity = (value);
    return value;
}
float setter_qcc_health_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_health_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_health_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_health_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_health_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_health_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_health = (value);
    return value;
}
float setter_qcc_frags_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_frags = (value);
    return value;
}
float setter_qcc_frags_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_frags = (value);
    return value;
}
float setter_qcc_weapon_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_weapon = (value);
    return value;
}
float setter_qcc_weapon_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_weapon = (value);
    return value;
}
float setter_qcc_weapon_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_weapon = (value);
    return value;
}
string_t setter_qcc_weaponmodel_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_weaponmodel = (value);
    return value;
}
string_t setter_qcc_weaponmodel_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_weaponmodel = (value);
    return value;
}
float setter_qcc_weaponframe_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_weaponframe = (value);
    return value;
}
float setter_qcc_weaponframe_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_weaponframe = (value);
    return value;
}
float setter_qcc_currentammo_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_currentammo = (value);
    return value;
}
float setter_qcc_currentammo_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_currentammo = (value);
    return value;
}
float setter_qcc_ammo_shells_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ammo_shells = (value);
    return value;
}
float setter_qcc_ammo_shells_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_ammo_shells = (value);
    return value;
}
float setter_qcc_ammo_shells_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_ammo_shells = (value);
    return value;
}
float setter_qcc_ammo_shells_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_ammo_shells = (value);
    return value;
}
float setter_qcc_ammo_nails_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ammo_nails = (value);
    return value;
}
float setter_qcc_ammo_nails_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_ammo_nails = (value);
    return value;
}
float setter_qcc_ammo_nails_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_ammo_nails = (value);
    return value;
}
float setter_qcc_ammo_nails_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_ammo_nails = (value);
    return value;
}
float setter_qcc_ammo_rockets_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ammo_rockets = (value);
    return value;
}
float setter_qcc_ammo_rockets_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_ammo_rockets = (value);
    return value;
}
float setter_qcc_ammo_rockets_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_ammo_rockets = (value);
    return value;
}
float setter_qcc_ammo_rockets_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_ammo_rockets = (value);
    return value;
}
float setter_qcc_ammo_cells_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ammo_cells = (value);
    return value;
}
float setter_qcc_ammo_cells_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_ammo_cells = (value);
    return value;
}
float setter_qcc_ammo_cells_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_ammo_cells = (value);
    return value;
}
float setter_qcc_ammo_cells_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_ammo_cells = (value);
    return value;
}
float setter_qcc_items_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_items = (value);
    return value;
}
float setter_qcc_items_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_items = (value);
    return value;
}
float setter_qcc_items_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_items = (value);
    return value;
}
float setter_qcc_items_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_items = (value);
    return value;
}
float setter_qcc_items_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_items = (value);
    return value;
}
float setter_qcc_takedamage_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
float setter_qcc_takedamage_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
float setter_qcc_takedamage_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
float setter_qcc_takedamage_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
float setter_qcc_takedamage_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
float setter_qcc_takedamage_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_takedamage = (value);
    return value;
}
int setter_qcc_chain_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_chain = (value);
    return value;
}
int setter_qcc_chain_player(edict_t *entity, int value)
{
    ((player_edict_t*) entity)->v.qcc_chain = (value);
    return value;
}
int setter_qcc_chain_explo_box(edict_t *entity, int value)
{
    ((explo_box_edict_t*) entity)->v.qcc_chain = (value);
    return value;
}
int setter_qcc_chain_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_chain = (value);
    return value;
}
float setter_qcc_deadflag_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_deadflag = (value);
    return value;
}
float setter_qcc_deadflag_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_deadflag = (value);
    return value;
}
float setter_qcc_view_ofs_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_view_ofs.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_view_ofs.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_view_ofs.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_view_ofs_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_view_ofs = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_view_ofs.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_view_ofs.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_view_ofs.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_view_ofs_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_view_ofs = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_view_ofs.x = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_view_ofs.y = floatToShort12p4(value);
    return value;
}
float setter_qcc_view_ofs_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_view_ofs.z = floatToShort12p4(value);
    return value;
}
vector setter_qcc_view_ofs_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_view_ofs = vfloatToShort12p4(value);
    return value;
}
float setter_qcc_button0_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_button0 = (value);
    return value;
}
float setter_qcc_button0_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_button0 = (value);
    return value;
}
float setter_qcc_button1_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_button1 = (value);
    return value;
}
float setter_qcc_button1_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_button1 = (value);
    return value;
}
float setter_qcc_button2_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_button2 = (value);
    return value;
}
float setter_qcc_button2_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_button2 = (value);
    return value;
}
float setter_qcc_impulse_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_impulse = (value);
    return value;
}
float setter_qcc_impulse_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_impulse = (value);
    return value;
}
float setter_qcc_fixangle_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_fixangle = (value);
    return value;
}
float setter_qcc_fixangle_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_fixangle = (value);
    return value;
}
float setter_qcc_v_angle_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_v_angle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_v_angle_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_v_angle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_v_angle_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_v_angle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_v_angle_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_v_angle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_v_angle_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_v_angle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_v_angle_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_v_angle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_v_angle_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_v_angle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_v_angle_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_v_angle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_idealpitch_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_idealpitch = floatToShortAngle(value);
    return value;
}
float setter_qcc_idealpitch_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_idealpitch = floatToShortAngle(value);
    return value;
}
string_t setter_qcc_netname_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_netname = (value);
    return value;
}
string_t setter_qcc_netname_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_netname = (value);
    return value;
}
string_t setter_qcc_netname_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_netname = (value);
    return value;
}
int setter_qcc_enemy_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_missile(edict_t *entity, int value)
{
    ((missile_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_trigger(edict_t *entity, int value)
{
    ((trigger_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_func(edict_t *entity, int value)
{
    ((func_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_player(edict_t *entity, int value)
{
    ((player_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_delayedUse(edict_t *entity, int value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
int setter_qcc_enemy_nh_wiz_startfast(edict_t *entity, int value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_enemy = (value);
    return value;
}
float setter_qcc_flags_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_bodyque(edict_t *entity, float value)
{
    ((bodyque_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_flags_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_flags = (value);
    return value;
}
float setter_qcc_team_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_team = (value);
    return value;
}
float setter_qcc_team_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_team = (value);
    return value;
}
float setter_qcc_max_health_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_max_health = (value);
    return value;
}
float setter_qcc_max_health_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_max_health = (value);
    return value;
}
float setter_qcc_max_health_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_max_health = (value);
    return value;
}
float setter_qcc_max_health_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_max_health = (value);
    return value;
}
float setter_qcc_max_health_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_max_health = (value);
    return value;
}
float setter_qcc_teleport_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_teleport_time = (value);
    return value;
}
float setter_qcc_teleport_time_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_teleport_time = (value);
    return value;
}
float setter_qcc_armortype_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_armortype = floatToShort8p8(value);
    return value;
}
float setter_qcc_armortype_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_armortype = floatToShort8p8(value);
    return value;
}
float setter_qcc_armorvalue_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_armorvalue = (value);
    return value;
}
float setter_qcc_armorvalue_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_armorvalue = (value);
    return value;
}
float setter_qcc_waterlevel_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_waterlevel_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_waterlevel = (value);
    return value;
}
float setter_qcc_watertype_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_nh_backpack(edict_t *entity, float value)
{
    ((nh_backpack_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_watertype_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_watertype = (value);
    return value;
}
float setter_qcc_ideal_yaw_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_ideal_yaw = floatToShortAngle(value);
    return value;
}
float setter_qcc_ideal_yaw_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_ideal_yaw = floatToShortAngle(value);
    return value;
}
float setter_qcc_yaw_speed_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_yaw_speed = floatToShortAngle(value);
    return value;
}
float setter_qcc_yaw_speed_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_yaw_speed = floatToShortAngle(value);
    return value;
}
int setter_qcc_goalentity_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_goalentity = (value);
    return value;
}
int setter_qcc_goalentity_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_goalentity = (value);
    return value;
}
float setter_qcc_spawnflags_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_light(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_info(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_path_corner(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_spawnflags = (value);
    return value;
}
float setter_qcc_spawnflags_static_light(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_spawnflags = (value);
    return value;
}
string_t setter_qcc_target_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_light(edict_t *entity, string_t value)
{
    ((light_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_path_corner(edict_t *entity, string_t value)
{
    ((path_corner_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_delayedUse(edict_t *entity, string_t value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_monster(edict_t *entity, string_t value)
{
    ((monster_edict_t*) entity)->v.qcc_target = (value);
    return value;
}
string_t setter_qcc_target_static_light(edict_t *entity, string_t value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_target = (value);
    return value;
}
string_t setter_qcc_targetname_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_light(edict_t *entity, string_t value)
{
    ((light_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_info(edict_t *entity, string_t value)
{
    ((info_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_path_corner(edict_t *entity, string_t value)
{
    ((path_corner_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_monster(edict_t *entity, string_t value)
{
    ((monster_edict_t*) entity)->v.qcc_targetname = (value);
    return value;
}
string_t setter_qcc_targetname_static_light(edict_t *entity, string_t value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_targetname = (value);
    return value;
}
float setter_qcc_dmg_take_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dmg_take = (value);
    return value;
}
float setter_qcc_dmg_take_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_dmg_take = (value);
    return value;
}
float setter_qcc_dmg_save_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dmg_save = (value);
    return value;
}
float setter_qcc_dmg_save_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_dmg_save = (value);
    return value;
}
int setter_qcc_dmg_inflictor_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_dmg_inflictor = (value);
    return value;
}
int setter_qcc_dmg_inflictor_player(edict_t *entity, int value)
{
    ((player_edict_t*) entity)->v.qcc_dmg_inflictor = (value);
    return value;
}
int setter_qcc_owner_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_missile(edict_t *entity, int value)
{
    ((missile_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_bodyque(edict_t *entity, int value)
{
    ((bodyque_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_trigger(edict_t *entity, int value)
{
    ((trigger_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_func(edict_t *entity, int value)
{
    ((func_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_item(edict_t *entity, int value)
{
    ((item_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_bubble(edict_t *entity, int value)
{
    ((bubble_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_teledeath(edict_t *entity, int value)
{
    ((teledeath_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
int setter_qcc_owner_nh_wiz_startfast(edict_t *entity, int value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_owner = (value);
    return value;
}
float setter_qcc_movedir_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_trigger_x(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_trigger_y(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_trigger_z(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_trigger(edict_t *entity, vector value)
{
    ((trigger_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_player_x(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_player_y(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_player_z(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_player(edict_t *entity, vector value)
{
    ((player_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_monster_x(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_monster_y(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_monster_z(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_monster(edict_t *entity, vector value)
{
    ((monster_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_nh_wiz_startfast_x(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_movedir.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_nh_wiz_startfast_y(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_movedir.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_movedir_nh_wiz_startfast_z(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_movedir.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_movedir_nh_wiz_startfast(edict_t *entity, vector value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_movedir = vfloatToShortAngle(value);
    return value;
}
string_t setter_qcc_message_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_worldspawn(edict_t *entity, string_t value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_delayedUse(edict_t *entity, string_t value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
string_t setter_qcc_message_monster(edict_t *entity, string_t value)
{
    ((monster_edict_t*) entity)->v.qcc_message = (value);
    return value;
}
float setter_qcc_sounds_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
float setter_qcc_sounds_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
float setter_qcc_sounds_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
float setter_qcc_sounds_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
float setter_qcc_sounds_worldspawn(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
float setter_qcc_sounds_explo_box(edict_t *entity, float value)
{
    ((explo_box_edict_t*) entity)->v.qcc_sounds = (value);
    return value;
}
string_t setter_qcc_noise_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_noise = (value);
    return value;
}
string_t setter_qcc_noise_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_noise = (value);
    return value;
}
string_t setter_qcc_noise_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_noise = (value);
    return value;
}
string_t setter_qcc_noise_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_noise = (value);
    return value;
}
string_t setter_qcc_noise_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_noise = (value);
    return value;
}
string_t setter_qcc_noise1_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_noise1 = (value);
    return value;
}
string_t setter_qcc_noise1_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_noise1 = (value);
    return value;
}
string_t setter_qcc_noise1_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_noise1 = (value);
    return value;
}
string_t setter_qcc_noise2_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_noise2 = (value);
    return value;
}
string_t setter_qcc_noise2_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_noise2 = (value);
    return value;
}
string_t setter_qcc_noise2_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_noise2 = (value);
    return value;
}
string_t setter_qcc_noise3_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_noise3 = (value);
    return value;
}
string_t setter_qcc_noise3_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_noise3 = (value);
    return value;
}
string_t setter_qcc_noise3_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_noise3 = (value);
    return value;
}
string_t setter_qcc_map_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_map = (value);
    return value;
}
string_t setter_qcc_map_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_map = (value);
    return value;
}
float setter_qcc_worldtype_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_worldtype = (value);
    return value;
}
float setter_qcc_worldtype_worldspawn(edict_t *entity, float value)
{
    ((worldspawn_edict_t*) entity)->v.qcc_worldtype = (value);
    return value;
}
string_t setter_qcc_killtarget_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_killtarget = (value);
    return value;
}
string_t setter_qcc_killtarget_trigger(edict_t *entity, string_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_killtarget = (value);
    return value;
}
string_t setter_qcc_killtarget_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_killtarget = (value);
    return value;
}
string_t setter_qcc_killtarget_delayedUse(edict_t *entity, string_t value)
{
    ((delayedUse_edict_t*) entity)->v.qcc_killtarget = (value);
    return value;
}
string_t setter_qcc_killtarget_monster(edict_t *entity, string_t value)
{
    ((monster_edict_t*) entity)->v.qcc_killtarget = (value);
    return value;
}
float setter_qcc_style_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_style = (value);
    return value;
}
float setter_qcc_style_light(edict_t *entity, float value)
{
    ((light_edict_t*) entity)->v.qcc_style = (value);
    return value;
}
float setter_qcc_style_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_style = (value);
    return value;
}
float setter_qcc_style_static_light(edict_t *entity, float value)
{
    ((static_light_edict_t*) entity)->v.romEntvars->qcc_style = (value);
    return value;
}
func_t setter_qcc_th_stand_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_stand = (value);
    return value;
}
func_t setter_qcc_th_stand_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_stand = (value);
    return value;
}
func_t setter_qcc_th_walk_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_walk = (value);
    return value;
}
func_t setter_qcc_th_walk_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_walk = (value);
    return value;
}
func_t setter_qcc_th_run_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_run = (value);
    return value;
}
func_t setter_qcc_th_run_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_run = (value);
    return value;
}
func_t setter_qcc_th_missile_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_missile = (value);
    return value;
}
func_t setter_qcc_th_missile_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_missile = (value);
    return value;
}
func_t setter_qcc_th_melee_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_melee = (value);
    return value;
}
func_t setter_qcc_th_melee_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_melee = (value);
    return value;
}
func_t setter_qcc_th_pain_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_pain = (value);
    return value;
}
func_t setter_qcc_th_pain_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_th_pain = (value);
    return value;
}
func_t setter_qcc_th_pain_player(edict_t *entity, func_t value)
{
    ((player_edict_t*) entity)->v.qcc_th_pain = (value);
    return value;
}
func_t setter_qcc_th_pain_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_pain = (value);
    return value;
}
func_t setter_qcc_th_die_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
func_t setter_qcc_th_die_trigger(edict_t *entity, func_t value)
{
    ((trigger_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
func_t setter_qcc_th_die_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
func_t setter_qcc_th_die_player(edict_t *entity, func_t value)
{
    ((player_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
func_t setter_qcc_th_die_explo_box(edict_t *entity, func_t value)
{
    ((explo_box_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
func_t setter_qcc_th_die_monster(edict_t *entity, func_t value)
{
    ((monster_edict_t*) entity)->v.qcc_th_die = (value);
    return value;
}
int setter_qcc_oldenemy_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_oldenemy = (value);
    return value;
}
int setter_qcc_oldenemy_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_oldenemy = (value);
    return value;
}
float setter_qcc_speed_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_speed = floatToShort12p4(value);
    return value;
}
float setter_qcc_speed_missile(edict_t *entity, float value)
{
    ((missile_edict_t*) entity)->v.qcc_speed = floatToShort12p4(value);
    return value;
}
float setter_qcc_speed_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_speed = floatToShort12p4(value);
    return value;
}
float setter_qcc_speed_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_speed = floatToShort12p4(value);
    return value;
}
float setter_qcc_speed_nh_wiz_startfast(edict_t *entity, float value)
{
    ((nh_wiz_startfast_edict_t*) entity)->v.qcc_speed = floatToShort12p4(value);
    return value;
}
float setter_qcc_lefty_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_lefty = (value);
    return value;
}
float setter_qcc_lefty_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_lefty = (value);
    return value;
}
float setter_qcc_search_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_search_time = (value);
    return value;
}
float setter_qcc_search_time_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_search_time = (value);
    return value;
}
float setter_qcc_attack_state_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_attack_state = (value);
    return value;
}
float setter_qcc_attack_state_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_attack_state = (value);
    return value;
}
float setter_qcc_walkframe_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_walkframe = (value);
    return value;
}
float setter_qcc_walkframe_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_walkframe = (value);
    return value;
}
float setter_qcc_attack_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_attack_finished = (value);
    return value;
}
float setter_qcc_attack_finished_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_attack_finished = (value);
    return value;
}
float setter_qcc_attack_finished_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_attack_finished = (value);
    return value;
}
float setter_qcc_attack_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_attack_finished = (value);
    return value;
}
float setter_qcc_attack_finished_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_attack_finished = (value);
    return value;
}
float setter_qcc_pain_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pain_finished = (value);
    return value;
}
float setter_qcc_pain_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_pain_finished = (value);
    return value;
}
float setter_qcc_pain_finished_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_pain_finished = (value);
    return value;
}
float setter_qcc_invincible_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invincible_finished = (value);
    return value;
}
float setter_qcc_invincible_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invincible_finished = (value);
    return value;
}
float setter_qcc_invisible_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invisible_finished = (value);
    return value;
}
float setter_qcc_invisible_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invisible_finished = (value);
    return value;
}
float setter_qcc_super_damage_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_super_damage_finished = (value);
    return value;
}
float setter_qcc_super_damage_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_super_damage_finished = (value);
    return value;
}
float setter_qcc_radsuit_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_radsuit_finished = (value);
    return value;
}
float setter_qcc_radsuit_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_radsuit_finished = (value);
    return value;
}
float setter_qcc_invincible_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invincible_time = (value);
    return value;
}
float setter_qcc_invincible_time_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invincible_time = (value);
    return value;
}
float setter_qcc_invincible_sound_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invincible_sound = (value);
    return value;
}
float setter_qcc_invincible_sound_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invincible_sound = (value);
    return value;
}
float setter_qcc_invisible_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invisible_time = (value);
    return value;
}
float setter_qcc_invisible_time_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invisible_time = (value);
    return value;
}
float setter_qcc_invisible_sound_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_invisible_sound = (value);
    return value;
}
float setter_qcc_invisible_sound_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_invisible_sound = (value);
    return value;
}
float setter_qcc_super_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_super_time = (value);
    return value;
}
float setter_qcc_super_time_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_super_time = (value);
    return value;
}
float setter_qcc_super_sound_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_super_sound = (value);
    return value;
}
float setter_qcc_super_sound_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_super_sound = (value);
    return value;
}
float setter_qcc_rad_time_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_rad_time = (value);
    return value;
}
float setter_qcc_rad_time_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_rad_time = (value);
    return value;
}
float setter_qcc_fly_sound_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_fly_sound = (value);
    return value;
}
float setter_qcc_fly_sound_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_fly_sound = (value);
    return value;
}
float setter_qcc_axhitme_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_axhitme = (value);
    return value;
}
float setter_qcc_axhitme_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_axhitme = (value);
    return value;
}
float setter_qcc_axhitme_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_axhitme = (value);
    return value;
}
float setter_qcc_show_hostile_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_show_hostile = (value);
    return value;
}
float setter_qcc_show_hostile_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_show_hostile = (value);
    return value;
}
float setter_qcc_show_hostile_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_show_hostile = (value);
    return value;
}
float setter_qcc_jump_flag_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_jump_flag = (value);
    return value;
}
float setter_qcc_jump_flag_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_jump_flag = (value);
    return value;
}
float setter_qcc_swim_flag_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_swim_flag = (value);
    return value;
}
float setter_qcc_swim_flag_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_swim_flag = (value);
    return value;
}
float setter_qcc_air_finished_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_air_finished = (value);
    return value;
}
float setter_qcc_air_finished_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_air_finished = (value);
    return value;
}
float setter_qcc_air_finished_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_air_finished = (value);
    return value;
}
float setter_qcc_bubble_count_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_bubble_count = (value);
    return value;
}
float setter_qcc_bubble_count_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_bubble_count = (value);
    return value;
}
string_t setter_qcc_deathtype_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_deathtype = (value);
    return value;
}
string_t setter_qcc_deathtype_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_deathtype = (value);
    return value;
}
string_t setter_qcc_mdl_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_mdl = (value);
    return value;
}
string_t setter_qcc_mdl_item(edict_t *entity, string_t value)
{
    ((item_edict_t*) entity)->v.qcc_mdl = (value);
    return value;
}
float setter_qcc_mangle_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_mangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_mangle_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_mangle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_info_x(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_mangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_info_y(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_mangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_info_z(edict_t *entity, float value)
{
    ((info_edict_t*) entity)->v.qcc_mangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_mangle_info(edict_t *entity, vector value)
{
    ((info_edict_t*) entity)->v.qcc_mangle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_mangle_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_mangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_mangle_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_mangle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_t_length_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_t_length = (value);
    return value;
}
float setter_qcc_t_length_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_t_length = (value);
    return value;
}
float setter_qcc_t_width_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_t_width = (value);
    return value;
}
float setter_qcc_t_width_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_t_width = (value);
    return value;
}
float setter_qcc_t_width_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_t_width = (value);
    return value;
}
float setter_qcc_dest_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_dest_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_dest = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest1.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest1.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest1.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_dest1_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_dest1 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest1.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest1.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest1_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest1.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_dest1_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_dest1 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest2.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest2.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dest2.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_dest2_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_dest2 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest2.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest2.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_dest2_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dest2.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_dest2_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_dest2 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_wait_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_wait = floatToShort8p8(value);
    return value;
}
float setter_qcc_wait_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_wait = floatToShort8p8(value);
    return value;
}
float setter_qcc_wait_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_wait = floatToShort8p8(value);
    return value;
}
float setter_qcc_wait_path_corner(edict_t *entity, float value)
{
    ((path_corner_edict_t*) entity)->v.qcc_wait = floatToShort8p8(value);
    return value;
}
float setter_qcc_delay_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_delay = floatToShort8p8(value);
    return value;
}
float setter_qcc_delay_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_delay = floatToShort8p8(value);
    return value;
}
float setter_qcc_delay_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_delay = floatToShort8p8(value);
    return value;
}
int setter_qcc_trigger_field_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_trigger_field = (value);
    return value;
}
int setter_qcc_trigger_field_func(edict_t *entity, int value)
{
    ((func_edict_t*) entity)->v.qcc_trigger_field = (value);
    return value;
}
string_t setter_qcc_noise4_full(edict_t *entity, string_t value)
{
    ((full_edict_t*) entity)->v.qcc_noise4 = (value);
    return value;
}
string_t setter_qcc_noise4_func(edict_t *entity, string_t value)
{
    ((func_edict_t*) entity)->v.qcc_noise4 = (value);
    return value;
}
string_t setter_qcc_noise4_player(edict_t *entity, string_t value)
{
    ((player_edict_t*) entity)->v.qcc_noise4 = (value);
    return value;
}
float setter_qcc_pausetime_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pausetime = (value);
    return value;
}
float setter_qcc_pausetime_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_pausetime = (value);
    return value;
}
float setter_qcc_pausetime_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_pausetime = (value);
    return value;
}
int setter_qcc_movetarget_full(edict_t *entity, int value)
{
    ((full_edict_t*) entity)->v.qcc_movetarget = (value);
    return value;
}
int setter_qcc_movetarget_monster(edict_t *entity, int value)
{
    ((monster_edict_t*) entity)->v.qcc_movetarget = (value);
    return value;
}
float setter_qcc_aflag_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_aflag = (value);
    return value;
}
float setter_qcc_aflag_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_aflag = (value);
    return value;
}
float setter_qcc_dmg_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dmg = (value);
    return value;
}
float setter_qcc_dmg_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_dmg = (value);
    return value;
}
float setter_qcc_dmg_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_dmg = (value);
    return value;
}
float setter_qcc_dmg_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_dmg = (value);
    return value;
}
float setter_qcc_cnt_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_cnt = (value);
    return value;
}
float setter_qcc_cnt_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_cnt = (value);
    return value;
}
float setter_qcc_cnt_bubble(edict_t *entity, float value)
{
    ((bubble_edict_t*) entity)->v.qcc_cnt = (value);
    return value;
}
float setter_qcc_cnt_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_cnt = (value);
    return value;
}
func_t setter_qcc_think1_full(edict_t *entity, func_t value)
{
    ((full_edict_t*) entity)->v.qcc_think1 = (value);
    return value;
}
func_t setter_qcc_think1_func(edict_t *entity, func_t value)
{
    ((func_edict_t*) entity)->v.qcc_think1 = (value);
    return value;
}
float setter_qcc_finaldest_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finaldest.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_finaldest_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finaldest.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_finaldest_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finaldest.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_finaldest_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_finaldest = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_finaldest_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_finaldest.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_finaldest_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_finaldest.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_finaldest_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_finaldest.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_finaldest_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_finaldest = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_finalangle_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finalangle.x = floatToShortAngle(value);
    return value;
}
float setter_qcc_finalangle_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finalangle.y = floatToShortAngle(value);
    return value;
}
float setter_qcc_finalangle_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_finalangle.z = floatToShortAngle(value);
    return value;
}
vector setter_qcc_finalangle_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_finalangle = vfloatToShortAngle(value);
    return value;
}
float setter_qcc_count_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_count = (value);
    return value;
}
float setter_qcc_count_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_count = (value);
    return value;
}
float setter_qcc_lip_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_lip = (value);
    return value;
}
float setter_qcc_lip_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_lip = (value);
    return value;
}
float setter_qcc_state_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_state = (value);
    return value;
}
float setter_qcc_state_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_state = (value);
    return value;
}
float setter_qcc_pos1_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos1.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos1_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos1.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos1_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos1.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_pos1_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_pos1 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_pos1_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos1.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos1_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos1.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos1_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos1.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_pos1_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_pos1 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_full_x(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos2.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_full_y(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos2.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_full_z(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_pos2.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_pos2_full(edict_t *entity, vector value)
{
    ((full_edict_t*) entity)->v.qcc_pos2 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_func_x(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos2.x = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_func_y(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos2.y = floatToShort13p3(value);
    return value;
}
float setter_qcc_pos2_func_z(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_pos2.z = floatToShort13p3(value);
    return value;
}
vector setter_qcc_pos2_func(edict_t *entity, vector value)
{
    ((func_edict_t*) entity)->v.qcc_pos2 = vfloatToShort13p3(value);
    return value;
}
float setter_qcc_height_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_height = (value);
    return value;
}
float setter_qcc_height_trigger(edict_t *entity, float value)
{
    ((trigger_edict_t*) entity)->v.qcc_height = (value);
    return value;
}
float setter_qcc_height_func(edict_t *entity, float value)
{
    ((func_edict_t*) entity)->v.qcc_height = (value);
    return value;
}
float setter_qcc_waitmin_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_waitmin = (value);
    return value;
}
float setter_qcc_waitmin_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_waitmin = (value);
    return value;
}
float setter_qcc_healamount_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_healamount = (value);
    return value;
}
float setter_qcc_healamount_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_healamount = (value);
    return value;
}
float setter_qcc_healtype_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_healtype = (value);
    return value;
}
float setter_qcc_healtype_item(edict_t *entity, float value)
{
    ((item_edict_t*) entity)->v.qcc_healtype = (value);
    return value;
}
float setter_qcc_dmgtime_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_dmgtime = (value);
    return value;
}
float setter_qcc_dmgtime_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_dmgtime = (value);
    return value;
}
float setter_qcc_inpain_full(edict_t *entity, float value)
{
    ((full_edict_t*) entity)->v.qcc_inpain = (value);
    return value;
}
float setter_qcc_inpain_player(edict_t *entity, float value)
{
    ((player_edict_t*) entity)->v.qcc_inpain = (value);
    return value;
}
float setter_qcc_inpain_monster(edict_t *entity, float value)
{
    ((monster_edict_t*) entity)->v.qcc_inpain = (value);
    return value;
}
float getter_qcc_modelindex_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_modelindex_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_modelindex);
}
float getter_qcc_modelindex_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_modelindex);
}
float getter_qcc_ltime_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_ltime);
}
float getter_qcc_ltime_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_ltime);
}
float getter_qcc_ltime_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_ltime);
}
float getter_qcc_ltime_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_ltime);
}
float getter_qcc_movetype_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_movetype_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_movetype);
}
float getter_qcc_solid_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_path_corner(edict_t *entity)
{
    return (((path_corner_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_teledeath(edict_t *entity)
{
    return (((teledeath_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_solid);
}
float getter_qcc_solid_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_solid);
}
vector getter_qcc_origin_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_missile(edict_t *entity)
{
    return vshort13p3ToFloat(((missile_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_sound(edict_t *entity)
{
    return vshort13p3ToFloat(((sound_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_bodyque(edict_t *entity)
{
    return vshort13p3ToFloat(((bodyque_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_light(edict_t *entity)
{
    return vshort13p3ToFloat(((light_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_trigger(edict_t *entity)
{
    return vshort13p3ToFloat(((trigger_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_info(edict_t *entity)
{
    return vshort13p3ToFloat(((info_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_func(edict_t *entity)
{
    return v(((func_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_player(edict_t *entity)
{
    return v(((player_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_path_corner(edict_t *entity)
{
    return vshort13p3ToFloat(((path_corner_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_item(edict_t *entity)
{
    return vshort13p3ToFloat(((item_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_worldspawn(edict_t *entity)
{
    return vshort13p3ToFloat(((worldspawn_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_nh_backpack(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_backpack_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_nh_tfog(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_tfog_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_explo_box(edict_t *entity)
{
    return vshort13p3ToFloat(((explo_box_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_bubble(edict_t *entity)
{
    return vshort13p3ToFloat(((bubble_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_teledeath(edict_t *entity)
{
    return vshort13p3ToFloat(((teledeath_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_monster(edict_t *entity)
{
    return v(((monster_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_origin_static_light(edict_t *entity)
{
    return vshort13p3ToFloat(((static_light_edict_t*) entity)->v.romEntvars->qcc_origin);
}
vector getter_qcc_origin_nh_wiz_startfast(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_origin);
}
vector getter_qcc_oldorigin_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_func(edict_t *entity)
{
    return v(((func_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_player(edict_t *entity)
{
    return v(((player_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_item(edict_t *entity)
{
    return vshort13p3ToFloat(((item_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_nh_backpack(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_backpack_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_explo_box(edict_t *entity)
{
    return vshort13p3ToFloat(((explo_box_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_oldorigin_monster(edict_t *entity)
{
    return v(((monster_edict_t*) entity)->v.qcc_oldorigin);
}
vector getter_qcc_velocity_full(edict_t *entity)
{
    return vshort12p4ToFloat(((full_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_missile(edict_t *entity)
{
    return vshort12p4ToFloat(((missile_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_bodyque(edict_t *entity)
{
    return vshort12p4ToFloat(((bodyque_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_func(edict_t *entity)
{
    return vshort12p4ToFloat(((func_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_player(edict_t *entity)
{
    return vshort12p4ToFloat(((player_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_item(edict_t *entity)
{
    return vshort12p4ToFloat(((item_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_nh_backpack(edict_t *entity)
{
    return vshort12p4ToFloat(((nh_backpack_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_explo_box(edict_t *entity)
{
    return vshort12p4ToFloat(((explo_box_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_bubble(edict_t *entity)
{
    return vshort12p4ToFloat(((bubble_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_monster(edict_t *entity)
{
    return vshort12p4ToFloat(((monster_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_velocity_nh_wiz_startfast(edict_t *entity)
{
    return vshort12p4ToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_velocity);
}
vector getter_qcc_angles_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_missile(edict_t *entity)
{
    return vshortAngleToFloat(((missile_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_bodyque(edict_t *entity)
{
    return vshortAngleToFloat(((bodyque_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_light(edict_t *entity)
{
    return vshortAngleToFloat(((light_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_trigger(edict_t *entity)
{
    return vshortAngleToFloat(((trigger_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_info(edict_t *entity)
{
    return vshortAngleToFloat(((info_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_func(edict_t *entity)
{
    return vshortAngleToFloat(((func_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_player(edict_t *entity)
{
    return vshortAngleToFloat(((player_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_item(edict_t *entity)
{
    return vshortAngleToFloat(((item_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_nh_backpack(edict_t *entity)
{
    return vshortAngleToFloat(((nh_backpack_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_explo_box(edict_t *entity)
{
    return vshortAngleToFloat(((explo_box_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_monster(edict_t *entity)
{
    return vshortAngleToFloat(((monster_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_angles_static_light(edict_t *entity)
{
    return vshort13p3ToFloat(((static_light_edict_t*) entity)->v.romEntvars->qcc_angles);
}
vector getter_qcc_angles_nh_wiz_startfast(edict_t *entity)
{
    return vshortAngleToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_angles);
}
vector getter_qcc_avelocity_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_avelocity);
}
vector getter_qcc_avelocity_missile(edict_t *entity)
{
    return vshortAngleToFloat(((missile_edict_t*) entity)->v.qcc_avelocity);
}
vector getter_qcc_avelocity_player(edict_t *entity)
{
    return vshortAngleToFloat(((player_edict_t*) entity)->v.qcc_avelocity);
}
vector getter_qcc_avelocity_monster(edict_t *entity)
{
    return vshortAngleToFloat(((monster_edict_t*) entity)->v.qcc_avelocity);
}
vector getter_qcc_punchangle_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_punchangle);
}
vector getter_qcc_punchangle_player(edict_t *entity)
{
    return vshortAngleToFloat(((player_edict_t*) entity)->v.qcc_punchangle);
}
string_t getter_qcc_model_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_model);
}
string_t getter_qcc_model_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_model);
}
string_t getter_qcc_model_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_model);
}
float getter_qcc_frame_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_frame_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_frame);
}
float getter_qcc_frame_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_frame);
}
float getter_qcc_skin_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_skin);
}
float getter_qcc_skin_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_skin);
}
float getter_qcc_skin_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_skin);
}
float getter_qcc_skin_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_skin);
}
float getter_qcc_skin_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_skin);
}
float getter_qcc_effects_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_effects);
}
float getter_qcc_effects_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_effects);
}
vector getter_qcc_mins_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_missile(edict_t *entity)
{
    return vshort13p3ToFloat(((missile_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_light(edict_t *entity)
{
    return vshort13p3ToFloat(((light_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_trigger(edict_t *entity)
{
    return vshort13p3ToFloat(((trigger_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_player(edict_t *entity)
{
    return vshort13p3ToFloat(((player_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_item(edict_t *entity)
{
    return vshort13p3ToFloat(((item_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_nh_backpack(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_backpack_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_explo_box(edict_t *entity)
{
    return vshort13p3ToFloat(((explo_box_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_bubble(edict_t *entity)
{
    return vshort13p3ToFloat(((bubble_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_teledeath(edict_t *entity)
{
    return vshort13p3ToFloat(((teledeath_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_monster(edict_t *entity)
{
    return vshort13p3ToFloat(((monster_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_mins_static_light(edict_t *entity)
{
    return vshort13p3ToFloat(((static_light_edict_t*) entity)->v.romEntvars->qcc_mins);
}
vector getter_qcc_mins_nh_wiz_startfast(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_mins);
}
vector getter_qcc_maxs_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_missile(edict_t *entity)
{
    return vshort13p3ToFloat(((missile_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_light(edict_t *entity)
{
    return vshort13p3ToFloat(((light_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_trigger(edict_t *entity)
{
    return vshort13p3ToFloat(((trigger_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_player(edict_t *entity)
{
    return vshort13p3ToFloat(((player_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_item(edict_t *entity)
{
    return vshort13p3ToFloat(((item_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_nh_backpack(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_backpack_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_explo_box(edict_t *entity)
{
    return vshort13p3ToFloat(((explo_box_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_bubble(edict_t *entity)
{
    return vshort13p3ToFloat(((bubble_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_teledeath(edict_t *entity)
{
    return vshort13p3ToFloat(((teledeath_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_monster(edict_t *entity)
{
    return vshort13p3ToFloat(((monster_edict_t*) entity)->v.qcc_maxs);
}
vector getter_qcc_maxs_static_light(edict_t *entity)
{
    return vshort13p3ToFloat(((static_light_edict_t*) entity)->v.romEntvars->qcc_maxs);
}
vector getter_qcc_maxs_nh_wiz_startfast(edict_t *entity)
{
    return vshort13p3ToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_maxs);
}
func_t getter_qcc_touch_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_teledeath(edict_t *entity)
{
    return (((teledeath_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_touch_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_touch);
}
func_t getter_qcc_use_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_use);
}
func_t getter_qcc_use_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_use);
}
func_t getter_qcc_think_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_nh_tfog(edict_t *entity)
{
    return (((nh_tfog_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_teledeath(edict_t *entity)
{
    return (((teledeath_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_timer(edict_t *entity)
{
    return (((timer_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_think_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_think);
}
func_t getter_qcc_blocked_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_blocked);
}
func_t getter_qcc_blocked_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_blocked);
}
float getter_qcc_nextthink_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_nh_tfog(edict_t *entity)
{
    return (((nh_tfog_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_teledeath(edict_t *entity)
{
    return (((teledeath_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_timer(edict_t *entity)
{
    return (((timer_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_nextthink);
}
float getter_qcc_nextthink_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_nextthink);
}
int getter_qcc_groundentity_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_groundentity);
}
int getter_qcc_groundentity_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_groundentity);
}
float getter_qcc_health_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_health_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_health_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_health_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_health_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_health_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_health);
}
float getter_qcc_frags_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_frags);
}
float getter_qcc_frags_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_frags);
}
float getter_qcc_weapon_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_weapon);
}
float getter_qcc_weapon_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_weapon);
}
float getter_qcc_weapon_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_weapon);
}
string_t getter_qcc_weaponmodel_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_weaponmodel);
}
string_t getter_qcc_weaponmodel_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_weaponmodel);
}
float getter_qcc_weaponframe_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_weaponframe);
}
float getter_qcc_weaponframe_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_weaponframe);
}
float getter_qcc_currentammo_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_currentammo);
}
float getter_qcc_currentammo_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_currentammo);
}
float getter_qcc_ammo_shells_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_ammo_shells);
}
float getter_qcc_ammo_shells_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_ammo_shells);
}
float getter_qcc_ammo_shells_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_ammo_shells);
}
float getter_qcc_ammo_shells_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_ammo_shells);
}
float getter_qcc_ammo_nails_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_ammo_nails);
}
float getter_qcc_ammo_nails_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_ammo_nails);
}
float getter_qcc_ammo_nails_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_ammo_nails);
}
float getter_qcc_ammo_nails_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_ammo_nails);
}
float getter_qcc_ammo_rockets_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_ammo_rockets);
}
float getter_qcc_ammo_rockets_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_ammo_rockets);
}
float getter_qcc_ammo_rockets_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_ammo_rockets);
}
float getter_qcc_ammo_rockets_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_ammo_rockets);
}
float getter_qcc_ammo_cells_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_ammo_cells);
}
float getter_qcc_ammo_cells_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_ammo_cells);
}
float getter_qcc_ammo_cells_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_ammo_cells);
}
float getter_qcc_ammo_cells_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_ammo_cells);
}
float getter_qcc_items_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_items);
}
float getter_qcc_items_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_items);
}
float getter_qcc_items_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_items);
}
float getter_qcc_items_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_items);
}
float getter_qcc_items_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_items);
}
float getter_qcc_takedamage_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_takedamage);
}
float getter_qcc_takedamage_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_takedamage);
}
float getter_qcc_takedamage_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_takedamage);
}
float getter_qcc_takedamage_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_takedamage);
}
float getter_qcc_takedamage_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_takedamage);
}
float getter_qcc_takedamage_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_takedamage);
}
int getter_qcc_chain_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_chain);
}
int getter_qcc_chain_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_chain);
}
int getter_qcc_chain_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_chain);
}
int getter_qcc_chain_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_chain);
}
float getter_qcc_deadflag_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_deadflag);
}
float getter_qcc_deadflag_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_deadflag);
}
vector getter_qcc_view_ofs_full(edict_t *entity)
{
    return vshort12p4ToFloat(((full_edict_t*) entity)->v.qcc_view_ofs);
}
vector getter_qcc_view_ofs_player(edict_t *entity)
{
    return vshort12p4ToFloat(((player_edict_t*) entity)->v.qcc_view_ofs);
}
vector getter_qcc_view_ofs_monster(edict_t *entity)
{
    return vshort12p4ToFloat(((monster_edict_t*) entity)->v.qcc_view_ofs);
}
float getter_qcc_button0_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_button0);
}
float getter_qcc_button0_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_button0);
}
float getter_qcc_button1_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_button1);
}
float getter_qcc_button1_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_button1);
}
float getter_qcc_button2_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_button2);
}
float getter_qcc_button2_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_button2);
}
float getter_qcc_impulse_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_impulse);
}
float getter_qcc_impulse_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_impulse);
}
float getter_qcc_fixangle_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_fixangle);
}
float getter_qcc_fixangle_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_fixangle);
}
vector getter_qcc_v_angle_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_v_angle);
}
vector getter_qcc_v_angle_player(edict_t *entity)
{
    return vshortAngleToFloat(((player_edict_t*) entity)->v.qcc_v_angle);
}
float getter_qcc_idealpitch_full(edict_t *entity)
{
    return shortAngleToFloat(((full_edict_t*) entity)->v.qcc_idealpitch);
}
float getter_qcc_idealpitch_player(edict_t *entity)
{
    return shortAngleToFloat(((player_edict_t*) entity)->v.qcc_idealpitch);
}
string_t getter_qcc_netname_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_netname);
}
string_t getter_qcc_netname_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_netname);
}
string_t getter_qcc_netname_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_netname);
}
int getter_qcc_enemy_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_enemy);
}
int getter_qcc_enemy_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_enemy);
}
float getter_qcc_flags_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_flags_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_flags);
}
float getter_qcc_team_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_team);
}
float getter_qcc_team_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_team);
}
float getter_qcc_max_health_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_max_health);
}
float getter_qcc_max_health_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_max_health);
}
float getter_qcc_max_health_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_max_health);
}
float getter_qcc_max_health_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_max_health);
}
float getter_qcc_max_health_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_max_health);
}
float getter_qcc_teleport_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_teleport_time);
}
float getter_qcc_teleport_time_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_teleport_time);
}
float getter_qcc_armortype_full(edict_t *entity)
{
    return short8p8ToFloat(((full_edict_t*) entity)->v.qcc_armortype);
}
float getter_qcc_armortype_player(edict_t *entity)
{
    return short8p8ToFloat(((player_edict_t*) entity)->v.qcc_armortype);
}
float getter_qcc_armorvalue_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_armorvalue);
}
float getter_qcc_armorvalue_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_armorvalue);
}
float getter_qcc_waterlevel_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_waterlevel_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_waterlevel);
}
float getter_qcc_watertype_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_nh_backpack(edict_t *entity)
{
    return (((nh_backpack_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_watertype_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_watertype);
}
float getter_qcc_ideal_yaw_full(edict_t *entity)
{
    return shortAngleToFloat(((full_edict_t*) entity)->v.qcc_ideal_yaw);
}
float getter_qcc_ideal_yaw_monster(edict_t *entity)
{
    return shortAngleToFloat(((monster_edict_t*) entity)->v.qcc_ideal_yaw);
}
float getter_qcc_yaw_speed_full(edict_t *entity)
{
    return shortAngleToFloat(((full_edict_t*) entity)->v.qcc_yaw_speed);
}
float getter_qcc_yaw_speed_monster(edict_t *entity)
{
    return shortAngleToFloat(((monster_edict_t*) entity)->v.qcc_yaw_speed);
}
int getter_qcc_goalentity_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_goalentity);
}
int getter_qcc_goalentity_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_goalentity);
}
float getter_qcc_spawnflags_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_info(edict_t *entity)
{
    return (((info_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_path_corner(edict_t *entity)
{
    return (((path_corner_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_spawnflags);
}
float getter_qcc_spawnflags_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_spawnflags);
}
string_t getter_qcc_target_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_path_corner(edict_t *entity)
{
    return (((path_corner_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_target);
}
string_t getter_qcc_target_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_target);
}
string_t getter_qcc_targetname_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_info(edict_t *entity)
{
    return (((info_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_path_corner(edict_t *entity)
{
    return (((path_corner_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_targetname);
}
string_t getter_qcc_targetname_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_targetname);
}
float getter_qcc_dmg_take_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_dmg_take);
}
float getter_qcc_dmg_take_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_dmg_take);
}
float getter_qcc_dmg_save_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_dmg_save);
}
float getter_qcc_dmg_save_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_dmg_save);
}
int getter_qcc_dmg_inflictor_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_dmg_inflictor);
}
int getter_qcc_dmg_inflictor_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_dmg_inflictor);
}
int getter_qcc_owner_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_missile(edict_t *entity)
{
    return (((missile_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_bodyque(edict_t *entity)
{
    return (((bodyque_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_teledeath(edict_t *entity)
{
    return (((teledeath_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_owner);
}
int getter_qcc_owner_nh_wiz_startfast(edict_t *entity)
{
    return (((nh_wiz_startfast_edict_t*) entity)->v.qcc_owner);
}
vector getter_qcc_movedir_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_movedir);
}
vector getter_qcc_movedir_trigger(edict_t *entity)
{
    return vshortAngleToFloat(((trigger_edict_t*) entity)->v.qcc_movedir);
}
vector getter_qcc_movedir_func(edict_t *entity)
{
    return vshortAngleToFloat(((func_edict_t*) entity)->v.qcc_movedir);
}
vector getter_qcc_movedir_player(edict_t *entity)
{
    return vshortAngleToFloat(((player_edict_t*) entity)->v.qcc_movedir);
}
vector getter_qcc_movedir_monster(edict_t *entity)
{
    return vshortAngleToFloat(((monster_edict_t*) entity)->v.qcc_movedir);
}
vector getter_qcc_movedir_nh_wiz_startfast(edict_t *entity)
{
    return vshortAngleToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_movedir);
}
string_t getter_qcc_message_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_message);
}
string_t getter_qcc_message_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_message);
}
float getter_qcc_sounds_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_sounds);
}
float getter_qcc_sounds_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_sounds);
}
float getter_qcc_sounds_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_sounds);
}
float getter_qcc_sounds_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_sounds);
}
float getter_qcc_sounds_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_sounds);
}
float getter_qcc_sounds_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_sounds);
}
string_t getter_qcc_noise_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_noise);
}
string_t getter_qcc_noise_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_noise);
}
string_t getter_qcc_noise_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_noise);
}
string_t getter_qcc_noise_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_noise);
}
string_t getter_qcc_noise_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_noise);
}
string_t getter_qcc_noise1_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_noise1);
}
string_t getter_qcc_noise1_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_noise1);
}
string_t getter_qcc_noise1_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_noise1);
}
string_t getter_qcc_noise2_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_noise2);
}
string_t getter_qcc_noise2_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_noise2);
}
string_t getter_qcc_noise2_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_noise2);
}
string_t getter_qcc_noise3_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_noise3);
}
string_t getter_qcc_noise3_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_noise3);
}
string_t getter_qcc_noise3_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_noise3);
}
string_t getter_qcc_map_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_map);
}
string_t getter_qcc_map_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_map);
}
float getter_qcc_worldtype_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_worldtype);
}
float getter_qcc_worldtype_worldspawn(edict_t *entity)
{
    return (((worldspawn_edict_t*) entity)->v.qcc_worldtype);
}
string_t getter_qcc_killtarget_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_killtarget);
}
string_t getter_qcc_killtarget_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_killtarget);
}
string_t getter_qcc_killtarget_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_killtarget);
}
string_t getter_qcc_killtarget_delayedUse(edict_t *entity)
{
    return (((delayedUse_edict_t*) entity)->v.qcc_killtarget);
}
string_t getter_qcc_killtarget_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_killtarget);
}
float getter_qcc_style_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_style);
}
float getter_qcc_style_light(edict_t *entity)
{
    return (((light_edict_t*) entity)->v.qcc_style);
}
float getter_qcc_style_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_style);
}
float getter_qcc_style_static_light(edict_t *entity)
{
    return (((static_light_edict_t*) entity)->v.romEntvars->qcc_style);
}
func_t getter_qcc_th_stand_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_stand);
}
func_t getter_qcc_th_stand_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_stand);
}
func_t getter_qcc_th_walk_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_walk);
}
func_t getter_qcc_th_walk_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_walk);
}
func_t getter_qcc_th_run_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_run);
}
func_t getter_qcc_th_run_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_run);
}
func_t getter_qcc_th_missile_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_missile);
}
func_t getter_qcc_th_missile_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_missile);
}
func_t getter_qcc_th_melee_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_melee);
}
func_t getter_qcc_th_melee_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_melee);
}
func_t getter_qcc_th_pain_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_pain);
}
func_t getter_qcc_th_pain_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_th_pain);
}
func_t getter_qcc_th_pain_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_th_pain);
}
func_t getter_qcc_th_pain_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_pain);
}
func_t getter_qcc_th_die_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_th_die);
}
func_t getter_qcc_th_die_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_th_die);
}
func_t getter_qcc_th_die_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_th_die);
}
func_t getter_qcc_th_die_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_th_die);
}
func_t getter_qcc_th_die_explo_box(edict_t *entity)
{
    return (((explo_box_edict_t*) entity)->v.qcc_th_die);
}
func_t getter_qcc_th_die_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_th_die);
}
int getter_qcc_oldenemy_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_oldenemy);
}
int getter_qcc_oldenemy_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_oldenemy);
}
float getter_qcc_speed_full(edict_t *entity)
{
    return short12p4ToFloat(((full_edict_t*) entity)->v.qcc_speed);
}
float getter_qcc_speed_missile(edict_t *entity)
{
    return short12p4ToFloat(((missile_edict_t*) entity)->v.qcc_speed);
}
float getter_qcc_speed_trigger(edict_t *entity)
{
    return short12p4ToFloat(((trigger_edict_t*) entity)->v.qcc_speed);
}
float getter_qcc_speed_func(edict_t *entity)
{
    return short12p4ToFloat(((func_edict_t*) entity)->v.qcc_speed);
}
float getter_qcc_speed_nh_wiz_startfast(edict_t *entity)
{
    return short12p4ToFloat(((nh_wiz_startfast_edict_t*) entity)->v.qcc_speed);
}
float getter_qcc_lefty_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_lefty);
}
float getter_qcc_lefty_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_lefty);
}
float getter_qcc_search_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_search_time);
}
float getter_qcc_search_time_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_search_time);
}
float getter_qcc_attack_state_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_attack_state);
}
float getter_qcc_attack_state_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_attack_state);
}
float getter_qcc_walkframe_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_walkframe);
}
float getter_qcc_walkframe_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_walkframe);
}
float getter_qcc_attack_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_attack_finished);
}
float getter_qcc_attack_finished_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_attack_finished);
}
float getter_qcc_attack_finished_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_attack_finished);
}
float getter_qcc_attack_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_attack_finished);
}
float getter_qcc_attack_finished_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_attack_finished);
}
float getter_qcc_pain_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_pain_finished);
}
float getter_qcc_pain_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_pain_finished);
}
float getter_qcc_pain_finished_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_pain_finished);
}
float getter_qcc_invincible_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invincible_finished);
}
float getter_qcc_invincible_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invincible_finished);
}
float getter_qcc_invisible_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invisible_finished);
}
float getter_qcc_invisible_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invisible_finished);
}
float getter_qcc_super_damage_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_super_damage_finished);
}
float getter_qcc_super_damage_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_super_damage_finished);
}
float getter_qcc_radsuit_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_radsuit_finished);
}
float getter_qcc_radsuit_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_radsuit_finished);
}
float getter_qcc_invincible_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invincible_time);
}
float getter_qcc_invincible_time_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invincible_time);
}
float getter_qcc_invincible_sound_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invincible_sound);
}
float getter_qcc_invincible_sound_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invincible_sound);
}
float getter_qcc_invisible_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invisible_time);
}
float getter_qcc_invisible_time_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invisible_time);
}
float getter_qcc_invisible_sound_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_invisible_sound);
}
float getter_qcc_invisible_sound_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_invisible_sound);
}
float getter_qcc_super_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_super_time);
}
float getter_qcc_super_time_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_super_time);
}
float getter_qcc_super_sound_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_super_sound);
}
float getter_qcc_super_sound_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_super_sound);
}
float getter_qcc_rad_time_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_rad_time);
}
float getter_qcc_rad_time_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_rad_time);
}
float getter_qcc_fly_sound_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_fly_sound);
}
float getter_qcc_fly_sound_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_fly_sound);
}
float getter_qcc_axhitme_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_axhitme);
}
float getter_qcc_axhitme_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_axhitme);
}
float getter_qcc_axhitme_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_axhitme);
}
float getter_qcc_show_hostile_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_show_hostile);
}
float getter_qcc_show_hostile_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_show_hostile);
}
float getter_qcc_show_hostile_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_show_hostile);
}
float getter_qcc_jump_flag_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_jump_flag);
}
float getter_qcc_jump_flag_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_jump_flag);
}
float getter_qcc_swim_flag_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_swim_flag);
}
float getter_qcc_swim_flag_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_swim_flag);
}
float getter_qcc_air_finished_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_air_finished);
}
float getter_qcc_air_finished_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_air_finished);
}
float getter_qcc_air_finished_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_air_finished);
}
float getter_qcc_bubble_count_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_bubble_count);
}
float getter_qcc_bubble_count_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_bubble_count);
}
string_t getter_qcc_deathtype_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_deathtype);
}
string_t getter_qcc_deathtype_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_deathtype);
}
string_t getter_qcc_mdl_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_mdl);
}
string_t getter_qcc_mdl_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_mdl);
}
vector getter_qcc_mangle_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_mangle);
}
vector getter_qcc_mangle_info(edict_t *entity)
{
    return vshortAngleToFloat(((info_edict_t*) entity)->v.qcc_mangle);
}
vector getter_qcc_mangle_func(edict_t *entity)
{
    return vshortAngleToFloat(((func_edict_t*) entity)->v.qcc_mangle);
}
float getter_qcc_t_length_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_t_length);
}
float getter_qcc_t_length_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_t_length);
}
float getter_qcc_t_width_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_t_width);
}
float getter_qcc_t_width_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_t_width);
}
float getter_qcc_t_width_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_t_width);
}
vector getter_qcc_dest_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_dest);
}
vector getter_qcc_dest1_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_dest1);
}
vector getter_qcc_dest1_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_dest1);
}
vector getter_qcc_dest2_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_dest2);
}
vector getter_qcc_dest2_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_dest2);
}
float getter_qcc_wait_full(edict_t *entity)
{
    return short8p8ToFloat(((full_edict_t*) entity)->v.qcc_wait);
}
float getter_qcc_wait_trigger(edict_t *entity)
{
    return short8p8ToFloat(((trigger_edict_t*) entity)->v.qcc_wait);
}
float getter_qcc_wait_func(edict_t *entity)
{
    return short8p8ToFloat(((func_edict_t*) entity)->v.qcc_wait);
}
float getter_qcc_wait_path_corner(edict_t *entity)
{
    return short8p8ToFloat(((path_corner_edict_t*) entity)->v.qcc_wait);
}
float getter_qcc_delay_full(edict_t *entity)
{
    return short8p8ToFloat(((full_edict_t*) entity)->v.qcc_delay);
}
float getter_qcc_delay_trigger(edict_t *entity)
{
    return short8p8ToFloat(((trigger_edict_t*) entity)->v.qcc_delay);
}
float getter_qcc_delay_func(edict_t *entity)
{
    return short8p8ToFloat(((func_edict_t*) entity)->v.qcc_delay);
}
int getter_qcc_trigger_field_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_trigger_field);
}
int getter_qcc_trigger_field_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_trigger_field);
}
string_t getter_qcc_noise4_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_noise4);
}
string_t getter_qcc_noise4_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_noise4);
}
string_t getter_qcc_noise4_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_noise4);
}
float getter_qcc_pausetime_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_pausetime);
}
float getter_qcc_pausetime_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_pausetime);
}
float getter_qcc_pausetime_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_pausetime);
}
int getter_qcc_movetarget_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_movetarget);
}
int getter_qcc_movetarget_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_movetarget);
}
float getter_qcc_aflag_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_aflag);
}
float getter_qcc_aflag_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_aflag);
}
float getter_qcc_dmg_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_dmg);
}
float getter_qcc_dmg_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_dmg);
}
float getter_qcc_dmg_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_dmg);
}
float getter_qcc_dmg_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_dmg);
}
float getter_qcc_cnt_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_cnt);
}
float getter_qcc_cnt_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_cnt);
}
float getter_qcc_cnt_bubble(edict_t *entity)
{
    return (((bubble_edict_t*) entity)->v.qcc_cnt);
}
float getter_qcc_cnt_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_cnt);
}
func_t getter_qcc_think1_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_think1);
}
func_t getter_qcc_think1_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_think1);
}
vector getter_qcc_finaldest_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_finaldest);
}
vector getter_qcc_finaldest_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_finaldest);
}
vector getter_qcc_finalangle_full(edict_t *entity)
{
    return vshortAngleToFloat(((full_edict_t*) entity)->v.qcc_finalangle);
}
float getter_qcc_count_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_count);
}
float getter_qcc_count_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_count);
}
float getter_qcc_lip_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_lip);
}
float getter_qcc_lip_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_lip);
}
float getter_qcc_state_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_state);
}
float getter_qcc_state_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_state);
}
vector getter_qcc_pos1_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_pos1);
}
vector getter_qcc_pos1_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_pos1);
}
vector getter_qcc_pos2_full(edict_t *entity)
{
    return vshort13p3ToFloat(((full_edict_t*) entity)->v.qcc_pos2);
}
vector getter_qcc_pos2_func(edict_t *entity)
{
    return vshort13p3ToFloat(((func_edict_t*) entity)->v.qcc_pos2);
}
float getter_qcc_height_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_height);
}
float getter_qcc_height_trigger(edict_t *entity)
{
    return (((trigger_edict_t*) entity)->v.qcc_height);
}
float getter_qcc_height_func(edict_t *entity)
{
    return (((func_edict_t*) entity)->v.qcc_height);
}
float getter_qcc_waitmin_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_waitmin);
}
float getter_qcc_waitmin_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_waitmin);
}
float getter_qcc_healamount_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_healamount);
}
float getter_qcc_healamount_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_healamount);
}
float getter_qcc_healtype_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_healtype);
}
float getter_qcc_healtype_item(edict_t *entity)
{
    return (((item_edict_t*) entity)->v.qcc_healtype);
}
float getter_qcc_dmgtime_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_dmgtime);
}
float getter_qcc_dmgtime_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_dmgtime);
}
float getter_qcc_inpain_full(edict_t *entity)
{
    return (((full_edict_t*) entity)->v.qcc_inpain);
}
float getter_qcc_inpain_player(edict_t *entity)
{
    return (((player_edict_t*) entity)->v.qcc_inpain);
}
float getter_qcc_inpain_monster(edict_t *entity)
{
    return (((monster_edict_t*) entity)->v.qcc_inpain);
}
entLeaves_t * getter_entLeaves_full(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((full_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_missile(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((missile_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_bodyque(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((bodyque_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_light(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((light_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_trigger(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((trigger_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_func(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((func_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_player(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((player_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_item(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((item_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_worldspawn(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((worldspawn_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_nh_backpack(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((nh_backpack_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_explo_box(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((explo_box_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_bubble(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((bubble_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_monster(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((monster_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_static_light(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((static_light_edict_t*) entity)->v.romEntvars->entLeaves));
    #else
       return NULL;
    #endif
}
entLeaves_t * getter_entLeaves_nh_wiz_startfast(edict_t *entity)
{
    #if DO_FIND_TOUCHED_LEAVES_JIT == 3
       return &((((nh_wiz_startfast_edict_t*) entity)->v.entLeaves));
    #else
       return NULL;
    #endif
}
int setter_int_error(edict_t *entity, int value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
int setter_int_warning(edict_t *entity, int value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
int setter_int_non_zero_error(edict_t *entity, int value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
string_t setter_string_t_error(edict_t *entity, string_t value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
string_t setter_string_t_warning(edict_t *entity, string_t value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
string_t setter_string_t_non_zero_error(edict_t *entity, string_t value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
float setter_float_error(edict_t *entity, float value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
float setter_float_warning(edict_t *entity, float value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
float setter_float_non_zero_error(edict_t *entity, float value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
func_t setter_func_t_error(edict_t *entity, func_t value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
func_t setter_func_t_warning(edict_t *entity, func_t value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
func_t setter_func_t_non_zero_error(edict_t *entity, func_t value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
float setter_vector_error_x(edict_t *entity, float value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
float setter_vector_warning_x(edict_t *entity, float value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
float setter_vector_non_zero_error_x(edict_t *entity, float value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
float setter_vector_error_y(edict_t *entity, float value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
float setter_vector_warning_y(edict_t *entity, float value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
float setter_vector_non_zero_error_y(edict_t *entity, float value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
float setter_vector_error_z(edict_t *entity, float value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
float setter_vector_warning_z(edict_t *entity, float value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
float setter_vector_non_zero_error_z(edict_t *entity, float value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
vector setter_vector_error(edict_t *entity, vector value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
vector setter_vector_warning(edict_t *entity, vector value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
vector setter_vector_non_zero_error(edict_t *entity, vector value)
{
    if (value.x != 0 || value.y != 0 || value.z !=0)
    {
        DEBUG_ERROR_SETTER(entity, value.x);
        DEBUG_ERROR_SETTER(entity, value.y);
        DEBUG_ERROR_SETTER(entity, value.z);
    }
    return value;
}
entLeaves_t * setter_entLeaves_error(edict_t *entity, entLeaves_t * value)
{
    DEBUG_ERROR_SETTER(entity, value);
    return value;}
entLeaves_t * setter_entLeaves_warning(edict_t *entity, entLeaves_t * value)
{
    DEBUG_WARNING_SETTER(entity, value);
    return value;}
entLeaves_t * setter_entLeaves_non_zero_error(edict_t *entity, entLeaves_t * value)
{
    if (value != 0)
        DEBUG_ERROR_SETTER(entity, value);
    return value;
}
int getter_int_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_int;
}
int getter_int_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_int;
}
int getter_int_zero(edict_t *entity)
{
    (void) entity;    return ZERO_int;
}
string_t getter_string_t_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_string_t;
}
string_t getter_string_t_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_string_t;
}
string_t getter_string_t_zero(edict_t *entity)
{
    (void) entity;    return ZERO_string_t;
}
float getter_float_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_float;
}
float getter_float_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_float;
}
float getter_float_zero(edict_t *entity)
{
    (void) entity;    return ZERO_float;
}
func_t getter_func_t_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_func_t;
}
func_t getter_func_t_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_func_t;
}
func_t getter_func_t_zero(edict_t *entity)
{
    (void) entity;    return ZERO_func_t;
}
vector getter_vector_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_vector;
}
vector getter_vector_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_vector;
}
vector getter_vector_zero(edict_t *entity)
{
    (void) entity;    return ZERO_vector;
}
entLeaves_t * getter_entLeaves_error(edict_t *entity)
{
    DEBUG_ERROR_GETTER(entity);
    return ZERO_entLeaves;
}
entLeaves_t * getter_entLeaves_warning(edict_t *entity)
{
    DEBUG_WARNING_GETTER(entity);
    return ZERO_entLeaves;
}
entLeaves_t * getter_entLeaves_zero(edict_t *entity)
{
    (void) entity;    return ZERO_entLeaves;
}
#endif // EDICT_GETTER_SETTERS
