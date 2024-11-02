/*
    FunctionArrayCreator for MCU Quake, by Nicola Wrachien (next-hack in the comments)

    This program generates the getters and setters of each edict class.
    The configuration is done through the array at the beginning of the source.
    It has been tweaked by actually playing the game and spotting issues,
    as well as analyzing Quake C script files and Quake source code.

    Note: if you make any changes to the Quake C files, you need to run QuakeCConverter, and
    the fieldDefs, progs.h and quakeProgs.h must be modified accordingly here and on Quake.

    This would require serious cleanup.

    Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments).

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include "quakeProgs.h"
#include "fieldDefs.h"
#define GENERATE_XYZ    1
#define FIXME(reason) do {printf("File: %s, Line %d, FIXME: %s\r\n",__FILE__, __LINE__, reason); system("pause");}while(0)
#define MAX_SUB_CLASS_NUMBER max_classname_string_index
#define MAX_FIELDS  qcc_max_field_index
#define full_edict_idx                  qcc_full

char header[] =
{
    "// Warning! Machine-generated code, do not edit!\r\n"
    "\r\n"
    "/* Copyright (C) 2023-2024 Nicola Wrachien\r\n"
    "\r\n"
    " This program is free software; you can redistribute it and/or\r\n"
    " modify it under the terms of the GNU General Public License\r\n"
    " as published by the Free Software Foundation; either version 2\r\n"
    " of the License, or (at your option) any later version.\r\n"
    "\r\n"
    " This program is distributed in the hope that it will be useful,\r\n"
    " but WITHOUT ANY WARRANTY; without even the implied warranty of\r\n"
    " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\r\n"
    "\r\n"
    " See the GNU General Public License for more details.\r\n"
    "\r\n"
    " You should have received a copy of the GNU General Public License\r\n"
    " along with this program; if not, write to the Free Software\r\n"
    " Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\r\n"
    "*/\r\n"
};

uint16_t listOfRemovedFields[] =
{
    qcc_absmax_index, qcc_absmin_index, qcc_size_index, qcc_colormap_index,
    qcc_volume_index, qcc_hit_z_index, qcc_distance_index, qcc_waitmax_index, qcc_wad_index, qcc_aiment_index,
    qcc_light_lev_index,
};
char cFriendlyClassNames[max_classname_string_index][64] = {0};
#define TEST_EDICT 0
enum
{
    full_edict_idx = 0,               // everything
    missile_edict_idx,
    sound_edict_idx,                // sounds. Have only origin.
    bodyque_edict_idx,
    light_edict_idx,
    trigger_edict_idx,
    info_edict_idx,
    func_edict_idx,
    player_edict_idx,
    path_corner_edict_idx,
    item_edict_idx,
    worldspawn_edict_idx,
    delayedUse_edict_idx,
    nh_backpack_edict_idx,
    nh_tfog_edict_idx,
    explo_box_edict_idx,
    bubble_edict_idx,
    teledeath_edict_idx,
    timer_edict_idx,
    monster_edict_idx,
    static_light_edict_idx,
    nh_wiz_startfast_edict_idx,
#if TEST_EDICT
    test_edict_idx,
#endif // TEST_EDICT
    qcc_max_class,
};
char *qcc_entityClassNames[qcc_max_class] =
{
    [full_edict_idx] = "full",
    [missile_edict_idx] = "missile",
    [sound_edict_idx] = "sound",
    [bodyque_edict_idx] = "bodyque",
    [light_edict_idx] = "light",
    [trigger_edict_idx] = "trigger",
    [info_edict_idx] = "info",
    [func_edict_idx] = "func",
    [player_edict_idx] = "player",
    [item_edict_idx] = "item",
    [path_corner_edict_idx] = "path_corner",
    [worldspawn_edict_idx] = "worldspawn",
    [delayedUse_edict_idx] = "delayedUse",
    [nh_backpack_edict_idx] = "nh_backpack",
    [nh_tfog_edict_idx] = "nh_tfog",
    [explo_box_edict_idx] = "explo_box",
    [bubble_edict_idx] = "bubble",
    [teledeath_edict_idx] = "teledeath",
    [timer_edict_idx] = "timer",
    [monster_edict_idx] = "monster",
    [static_light_edict_idx] = "static_light",
    [nh_wiz_startfast_edict_idx] = "nh_wiz_startfast",
    //

#if TEST_EDICT
    [test_edict_idx] = "test",
#endif

};

enum
{
    FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,   // not implemented. Will error if set different from 0
    FUNCTION_IMPLEMENTATION_ERROR_NOT_IMPLEMENTED,                            // no implemented. Will halt program
    FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING,                          // no implemented. Won't have effect / return 0.
    FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,           // Only the prototype is generated, the body must be custom, but it is not class specific.
    FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,               // Only the prototype is generated, the body must be custom, and it is class specific
    FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED,                     // field dependent. For instance it is something moved in the base class.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,                               // fully automatically generated.
    FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,                               // fully automatically generated.
    FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE,                   // fully automatically generated but with short to float and vice versa angle conversion.
    FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3,               // fully automatically generated but with short to float and vice versa 13p3 fixed point.
    FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4,               // fully automatically generated but with short to float and vice versa 12p4 fixed point.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,                           // as before, but in this case the field will remain its original form (float/vector)
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE,                   // fully automatically generated but with short to float and vice versa angle conversion.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3,               // fully automatically generated but with short to float and vice versa 13p3 fixed point.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4,               // fully automatically generated but with short to float and vice versa 12p4 fixed point.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6,               // fully automatically generated but with short to float and vice versa 10p6 fixed point.
    FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8,               // fully automatically generated but with short to float and vice versa 8p8 fixed point.
    MAX_FUNCTION_IMPLEMENTATION,
};
uint8_t doNotGenerateXYZ[MAX_FIELDS] = {0};
uint8_t classSetup[qcc_max_class][MAX_FIELDS] =
{
    // missile. Full attributes
    [missile_edict_idx][qcc_skin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_avelocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_ltime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [missile_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,

    // missile specific
    [missile_edict_idx][qcc_size_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [missile_edict_idx][qcc_absmin_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [missile_edict_idx][qcc_absmax_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [missile_edict_idx][qcc_classname_index] = FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED,
    [missile_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,  // should be FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO
    [missile_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    [missile_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    //
        // nh_wiz_startfast_edict_idx. Full attributes
    [nh_wiz_startfast_edict_idx][qcc_skin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_movedir_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_ltime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //  specific
    [nh_wiz_startfast_edict_idx][qcc_size_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_absmin_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_absmax_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_classname_index] = FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED,
    [nh_wiz_startfast_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,  // should be FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO
    [nh_wiz_startfast_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [nh_wiz_startfast_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,



    //
    //[full_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    // sound
    [sound_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [sound_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [sound_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,

    // bodyque
    [bodyque_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [bodyque_edict_idx][qcc_colormap_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bodyque_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // really needed?
    [bodyque_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [bodyque_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [bodyque_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,

    // light
    [light_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [light_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [light_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [light_edict_idx][qcc_skin_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    // trigger_edict_idx
    [trigger_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_height_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_killtarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_map_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_wait_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_delay_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_count_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_movedir_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_noise_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_th_die_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_max_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // can be reduced in size.
    [trigger_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_attack_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [trigger_edict_idx][qcc_dmg_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [trigger_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    // info
    [info_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [info_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [info_edict_idx][qcc_mangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [info_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [info_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [info_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [info_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    // door
    [func_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_killtarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // worked with force AND WITHOUT
    [func_edict_idx][qcc_wait_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_lip_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_noise_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_noise1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_noise2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_noise3_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_noise4_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_height_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_dmg_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_max_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_movedir_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // new,worked with force AND WITHOUT
    [func_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_blocked_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_items_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_pos1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // WORKED WITH FORCE AND WITHOUT
    [func_edict_idx][qcc_pos2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // WORKED WITH FORCE AND WITHOUT
    [func_edict_idx][qcc_dest1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // worked with force AND WITHOUT
    [func_edict_idx][qcc_dest2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // worked with force AND WITHOUT
    [func_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,      // worked with force does not without
    [func_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE, // worked with force does not without
    [func_edict_idx][qcc_finaldest_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,     // WOKED WITH FORCE AND WITHOUT
    [func_edict_idx][qcc_state_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_th_die_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,      // worked with force
    [func_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,      // worked with force
    [func_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_ltime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // worked with force
    [func_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_trigger_field_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_mangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // worked with force AND WITHOUT
    [func_edict_idx][qcc_th_pain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_delay_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_cnt_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_think1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_t_width_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_t_length_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_attack_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [func_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [func_edict_idx][qcc_armortype_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [func_edict_idx][qcc_armorvalue_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [func_edict_idx][qcc_invincible_finished_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    //
    [func_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING,  // this to fix a strange behavior on E1M6

    //  player
    [player_edict_idx][qcc_pausetime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_waitmin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_dmgtime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_ltime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_items_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_teleport_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_search_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_attack_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_pain_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invincible_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invisible_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_super_damage_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_radsuit_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invincible_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invincible_sound_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invisible_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_invisible_sound_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_super_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_super_sound_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_rad_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_fly_sound_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_show_hostile_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_jump_flag_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_swim_flag_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_air_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//n    [player_edict_idx][qcc_t_length_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_t_width_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
//n    [player_edict_idx][qcc_wait_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//n    [player_edict_idx][qcc_delay_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_armortype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_idealpitch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_yaw_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_ideal_yaw_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4,
    [player_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_view_ofs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,
    [player_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,
//    [player_edict_idx][qcc_dest_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_dest1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_dest2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_finaldest_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_pos1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_pos2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_avelocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_punchangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_finalangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_movedir_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_v_angle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_mangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
//    [player_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_dmg_inflictor_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
//    [player_edict_idx][qcc_oldenemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_goalentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_trigger_field_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_movetarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_chain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_noise_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // is noise required for player?
    [player_edict_idx][qcc_noise1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_noise2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_noise3_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_noise4_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_netname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [player_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_weaponmodel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_map_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_killtarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_deathtype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_mdl_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
//    [player_edict_idx][qcc_th_stand_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_th_walk_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_th_run_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_th_missile_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_th_melee_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_th_pain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_th_die_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_think1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_blocked_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_frags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_weapon_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_weaponframe_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_currentammo_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_ammo_shells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_ammo_nails_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_ammo_rockets_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_ammo_cells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_button0_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_button1_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_button2_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_impulse_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
    [player_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_skin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_team_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_max_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_armorvalue_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_dmg_take_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//
//    [player_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_worldtype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_lefty_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_attack_state_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_walkframe_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_axhitme_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_bubble_count_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_fixangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_deadflag_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_aflag_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_dmg_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_dmg_save_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_cnt_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_count_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_lip_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_state_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_height_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_healamount_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [player_edict_idx][qcc_healtype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_inpain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [player_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [path_corner_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [path_corner_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [path_corner_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [path_corner_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [path_corner_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    [path_corner_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    [path_corner_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED,
    [path_corner_edict_idx][qcc_wait_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [path_corner_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // item
    [item_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_healtype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_aflag_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_healamount_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_weapon_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_mdl_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_netname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_skin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_noise_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_items_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [item_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,

    //
    [item_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING,  // this to fix a strange behavior on E1M6

    // worldspawn
    [worldspawn_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [worldspawn_edict_idx][qcc_worldtype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // delayUse
    [delayedUse_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [delayedUse_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [delayedUse_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [delayedUse_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [delayedUse_edict_idx][qcc_killtarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [delayedUse_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // backpack
    [nh_backpack_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_items_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_ammo_cells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_ammo_nails_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_ammo_rockets_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_ammo_shells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // could be fixed
    [nh_backpack_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed
    [nh_backpack_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed ?
    [nh_backpack_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_backpack_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,

    //
    [nh_tfog_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [nh_tfog_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,  // could be fixed ?
    [nh_tfog_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [explo_box_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_sounds_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_th_die_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_chain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [explo_box_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // bubble
    [bubble_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [bubble_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_air_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_bubble_count_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_cnt_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [bubble_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // teledeath_edict_idx
    [teledeath_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [teledeath_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO,
    [teledeath_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [teledeath_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // timer only
    [timer_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [timer_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    // monsters
//    [monster_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
//    [monster_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,
    [monster_edict_idx][qcc_oldorigin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE,

    [monster_edict_idx][qcc_nextthink_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_think_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_cnt_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_goalentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_yaw_speed_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_ideal_yaw_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_watertype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_movedir_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_enemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_chain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_takedamage_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_groundentity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_touch_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_pain_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_attack_finished_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_killtarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_inpain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_waitmin_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_movetarget_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_pausetime_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_attack_state_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_search_time_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_lefty_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_oldenemy_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_die_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_melee_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_missile_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_pain_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_run_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_walk_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_th_stand_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_max_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_health_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_movetype_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_solid_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_velocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_owner_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
   // [monster_edict_idx][qcc_mangle_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_flags_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_view_ofs_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_waterlevel_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_show_hostile_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_effects_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_message_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, // added to support E4M3

    //
    [monster_edict_idx][qcc_avelocity_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,

    [monster_edict_idx][qcc_ammo_shells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_ammo_nails_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_ammo_rockets_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    [monster_edict_idx][qcc_ammo_cells_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,
    //
    [monster_edict_idx][qcc_axhitme_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED,

    // static light
    [static_light_edict_idx][qcc_origin_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3,
    [static_light_edict_idx][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3,
    [static_light_edict_idx][qcc_style_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_spawnflags_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_frame_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,             // should be RAM instead ?
    [static_light_edict_idx][qcc_targetname_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_target_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_model_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_modelindex_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_use_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED,
    [static_light_edict_idx][qcc_mins_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3,
    [static_light_edict_idx][qcc_maxs_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3,


};
// which fields should be patched to use short angle
typedef struct
{
    int index;
    int type;
} fix_type_t;
fix_type_t fixFields[] =
{
    // angle vectors
    { qcc_angles_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_avelocity_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_punchangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_finalangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_movedir_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_v_angle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    { qcc_mangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},
    // float angles or angular speed
	{ qcc_idealpitch_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},         // angle ? or what ?
	{ qcc_yaw_speed_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},              // angle ?
    { qcc_ideal_yaw_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE},              // angle
    //12p4 vectors and values
    {qcc_velocity_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4},
    {qcc_view_ofs_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4},
    {qcc_speed_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4},

    // 13p3 vectors and values
    {qcc_origin_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_oldorigin_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_mins_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_maxs_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_dest_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_dest1_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_dest2_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_finaldest_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_pos1_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    {qcc_pos2_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3},
    // 8p8 values
    {qcc_wait_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
    {qcc_delay_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
    {qcc_armortype_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
};
fix_type_t fullFix[] =
{
    // angle vectors
    { qcc_angles_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_avelocity_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_punchangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_finalangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_movedir_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_v_angle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    { qcc_mangle_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    // float angles or angular speed
	{ qcc_idealpitch_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},         // angle ? or what ?
	{ qcc_yaw_speed_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},              // angle ?
    { qcc_ideal_yaw_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},              // angle
    //12p4 vectors and values
    {qcc_velocity_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_mins_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_maxs_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_view_ofs_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_speed_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},

    // 13p3 vectors and values
    {qcc_origin_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_oldorigin_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_dest_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_dest1_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_dest2_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_finaldest_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_pos1_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    {qcc_pos2_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED},
    // 8p8 values
    {qcc_wait_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
    {qcc_delay_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
    {qcc_armortype_index, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8},
};
uint8_t classFieldsSetterFunctions[qcc_max_class][MAX_FIELDS];
uint8_t classFieldsGetterFunctions[qcc_max_class][MAX_FIELDS];
static const uint8_t qcc_classname2type[max_classname_string_index] =
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
    [func_illusionary_string_index] = static_light_edict_idx,   // modified to light, so it can be static.
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
    [misc_explobox_string_index] = explo_box_edict_idx,   // fixme
    [misc_explobox2_string_index] = explo_box_edict_idx,
    [misc_teleporttrain_string_index] = full_edict_idx,     // this is just called on the end map. Can be full, we have tons of ram.
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
    [explo_box_string_index] = explo_box_edict_idx,   // fixme
};
enum
{
 TYPE_INT = 0,
 TYPE_STRING,
 TYPE_FLOAT,
 TYPE_FUNC,
 TYPE_VECTOR,
 TYPE_ENTLEAVES,
 TYPE_MAX
};
#define ENTITY_PARAM "edict_t *entity"
#define ENTITY_PARAM_MACRO "entity"
#define GET_TYPE_STRING "int type = qcc_classname2type[entity->qcc_classname];"
FILE * c_file = NULL;
int g_showInConsole = 0;
int qc_printf(const char *format, ...)
{
  va_list args;
  va_start (args, format);
  if (g_showInConsole)
    vprintf (format, args);
  if (c_file)
  {
    vfprintf(c_file, format, args);
  }
  va_end (args);
  return 0;
}
const char *vectorComponents[] = {"_x", "_y", "_z", ""};
const char *vectorComponentsIndirection[] = {".x", ".y", ".z", ""};
const char *setterConversionFunction[MAX_FUNCTION_IMPLEMENTATION] =
{
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE] = "floatToShortAngle",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3] = "floatToShort13p3",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4] = "floatToShort12p4",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6] = "floatToShort10p6",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8] = "floatToShort8p8",
    // rom funcions
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE] = "floatToShortAngle",
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3] = "floatToShort13p3",
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4] = "floatToShort12p4",

};
const char *getterConversionFunction[MAX_FUNCTION_IMPLEMENTATION] =
{
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE] = "shortAngleToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3] = "short13p3ToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4] = "short12p4ToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6] = "short10p6ToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8] = "short8p8ToFloat",
    // rom functions
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE] =  "shortAngleToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3] = "short13p3ToFloat",
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4] = "short12p4ToFloat",
};
bool isRomGenerated[MAX_FUNCTION_IMPLEMENTATION] =
{
    // rom functions
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED] = true,
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE] =  true,
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3] =  true,
    [FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4] = true
};

const char *types[] = {[TYPE_INT] = "int", [TYPE_STRING] = "string_t", [TYPE_FLOAT] = "float", [TYPE_FUNC] = "func_t", [TYPE_VECTOR] = "vector", [TYPE_ENTLEAVES] = "entLeaves_t *"};
const char *funcNameTypes[] = {[TYPE_INT] = "int", [TYPE_STRING] = "string_t", [TYPE_FLOAT] = "float", [TYPE_FUNC] = "func_t", [TYPE_VECTOR] = "vector", [TYPE_ENTLEAVES] = "entLeaves"};
const char *zero_by_type[] = {[TYPE_INT] = "0", [TYPE_STRING] = "0", [TYPE_FLOAT] = "0", [TYPE_FUNC] = "0", [TYPE_VECTOR] = "(vector) {{0, 0, 0}}", [TYPE_ENTLEAVES] = "NULL"};
enum
{
    FUNCTION_TYPE_GETTER = 0,
    FUNCTION_TYPE_SETTER,
    MAX_FUNCTION_TYPE
};
#define indexOf(name) name##_index


//
void addSetterFieldToClass(unsigned int classNumber, unsigned int fieldNumber, unsigned int functionType, uint8_t functionImplementation)
{
    if (classNumber >= qcc_max_class || fieldNumber >= MAX_FIELDS || functionType >= MAX_FUNCTION_TYPE || functionImplementation >= MAX_FUNCTION_IMPLEMENTATION)
    {
        FIXME("Error in addFieldToCall");
        return;
    }
    if (functionType == FUNCTION_TYPE_SETTER)
        classFieldsSetterFunctions[classNumber][fieldNumber] = functionImplementation;
    else
        classFieldsGetterFunctions[classNumber][fieldNumber] = functionImplementation;
}
void initCFriendlyClassNames()
{
    char *s;
    for (int i = 0; i < max_classname_string_index; i++)
    {
        s = (char *) quakeProgStrings[i];
        int j = 0;
        while (*s && j < sizeof(cFriendlyClassNames[0]) - 1)
        {
            char c = *s++;
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
            {
               cFriendlyClassNames[i][j] = c;
            }
            else
            {
                cFriendlyClassNames[i][j] = '_';
            }
            j++;
        }
        cFriendlyClassNames[i][j] = 0;  // nul terminator
    }
}
int classHasBeenSetUp[qcc_max_class] = {0};
void setupGetterSetters(int classIndex)
{
    memcpy(classFieldsGetterFunctions[classIndex], classSetup[classIndex], sizeof(classSetup[classIndex]));
    memcpy(classFieldsSetterFunctions[classIndex], classSetup[classIndex], sizeof(classSetup[classIndex]));
    classHasBeenSetUp[classIndex] =  1;
}
int main()
{
    uint8_t printed[MAX_FIELDS];
    initCFriendlyClassNames();
 //   memset(qcc_classname2type, qcc_full, sizeof qcc_classname2type);
    memset(classFieldsSetterFunctions, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, sizeof classFieldsSetterFunctions);
    memset(classFieldsGetterFunctions, FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED, sizeof classFieldsGetterFunctions);
    // FIXME: do this in a single function
    // missile
    for (int i = 1; i < qcc_max_class; i++)
    {
        #if TEST_EDICT
        if (i == test_edict_idx)
            continue;
        #endif
        setupGetterSetters(i);
    }
    if (!classHasBeenSetUp[qcc_max_class - 1])
        FIXME("NOTE! forgot to set up last class!");

    //
    // remove unused variables, custom fields.
    for (int c = 0; c < qcc_max_class; c++)
    {
        // classname is field specific and it is custom generated
        classFieldsGetterFunctions[c][qcc_classname_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED;
        classFieldsSetterFunctions[c][qcc_classname_index] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED;
        //
//        classFieldsSetterFunctions[c][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE;
//        classFieldsGetterFunctions[c][qcc_angles_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE;
        //
        for (int f = 0; f < sizeof (listOfRemovedFields) / sizeof (listOfRemovedFields[0]); f++)
        {
            int field = listOfRemovedFields[f];
            doNotGenerateXYZ[field] = 1;
            classFieldsGetterFunctions[c][field] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED;
            classFieldsSetterFunctions[c][field] = FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED;

        }
    }
    for (int f = 0; f < sizeof(fixFields)/sizeof(fixFields[0]); f++)
    {
        int field = fixFields[f].index;
        for (int c = 0; c < qcc_max_class; c++)
        {
            #if TEST_EDICT
            if (classFieldsGetterFunctions[c][field] == FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED && c != test_edict_idx)
            #else
            if (classFieldsGetterFunctions[c][field] == FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED)
            #endif
            {
              /*  if (c == 0)
                {
                    classFieldsGetterFunctions[c][field] = fullFix[f].type;
                    classFieldsSetterFunctions[c][field] = fullFix[f].type;
                   continue;
                }*/
                classFieldsGetterFunctions[c][field] = fixFields[f].type;
                classFieldsSetterFunctions[c][field] = fixFields[f].type;
            }
        }
    }
    // for all the classes where modelindex is present, we need to add entLeaves.
    for (int c = 0; c < qcc_max_class; c++)
    {
        if (classFieldsGetterFunctions[c][qcc_modelindex_index] == FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED)
        {
            classFieldsGetterFunctions[c][entLeaves_index] = FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED;
        }
        else
        {
            classFieldsGetterFunctions[c][entLeaves_index] = FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO;
        }
        classFieldsSetterFunctions[c][entLeaves_index] = FUNCTION_IMPLEMENTATION_ERROR_NOT_IMPLEMENTED;
    }
    // special case for static lights
    classFieldsGetterFunctions[static_light_edict_idx][entLeaves_index] = FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED;
    //
    c_file = fopen ("field_getters_setters.h", "wb");
    qc_printf("// File fields_getters_setters.h\r\n");
    qc_printf("%s", header);

    qc_printf("#ifndef FIELD_GETTER_SETTERS\r\n");
    qc_printf("#define FIELD_GETTER_SETTERS\r\n");
    qc_printf("#if EDICT_GETTER_SETTERS\r\n");
    qc_printf("void *allocEdByType(int classType);\r\n");
    qc_printf("unsigned int getEdictEntvarSize(edict_t *e);\r\n");
    for (int i = 0; i < qcc_max_class; i++)
    {
        qc_printf("#define %s_edict_idx %d\r\n", qcc_entityClassNames[i], i);
    }
    qc_printf("#define %s_edict_idx %d\r\n", "world", 0);
    //
    qc_printf("#define qcc_max_class %d\r\n", qcc_max_class);
    // define zero types
    for (int type = 0; type < TYPE_MAX; type ++)
    {
        qc_printf("#define ZERO_%s %s\r\n", funcNameTypes[type], zero_by_type[type]);
    }
    // array declaration;
    qc_printf("extern const uint8_t qcc_classname2type[max_classname_string_index];\r\n");
    //
    // now print the autogenerated functions prototypes
    // first the error and warnings. Only field-type dependent
    for (int i = 0; i < TYPE_MAX; i++)
    {
        qc_printf("%s setter_%s_error(%s, %s value);\r\n", types[i], funcNameTypes[i], ENTITY_PARAM, types[i]);
        qc_printf("%s setter_%s_non_zero_error(%s, %s value);\r\n", types[i], funcNameTypes[i], ENTITY_PARAM, types[i]);
        qc_printf("%s setter_%s_warning(%s, %s value);\r\n", types[i], funcNameTypes[i], ENTITY_PARAM, types[i]);
        if (TYPE_VECTOR == i && GENERATE_XYZ && !doNotGenerateXYZ[i])
        {
            // print _x, _y, _z variants as well
            for (int comp = 0; comp < 3; comp++)
            {
                qc_printf("float setter_%s_non_zero_error%s(%s, float value);\r\n", types[i], vectorComponents[comp], ENTITY_PARAM);
                qc_printf("float setter_%s_error%s(%s, float value);\r\n", types[i], vectorComponents[comp], ENTITY_PARAM);
                qc_printf("float setter_%s_warning%s(%s, float value);\r\n", types[i], vectorComponents[comp], ENTITY_PARAM);
            }
        }
    }
    for (int i = 0; i < TYPE_MAX; i++)
    {
        qc_printf("%s getter_%s_error(%s);\r\n", types[i], funcNameTypes[i], ENTITY_PARAM);
        qc_printf("%s getter_%s_zero(%s);\r\n", types[i], funcNameTypes[i], ENTITY_PARAM);
        qc_printf("%s getter_%s_warning(%s);\r\n", types[i], funcNameTypes [i], ENTITY_PARAM);
#if !GENERATE_XYZ
        if (TYPE_VECTOR == i && !GENERATE_XYZ)
        {
            qc_printf("float* getter_%s_ptr_error(%s);\r\n",  types[i], ENTITY_PARAM);
            qc_printf("float* getter_%s_ptr_warning(%s);\r\n", types[i], ENTITY_PARAM);
        }
#endif
    }
    memset(printed, 0, sizeof printed);
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        for (int c = 0; c < qcc_max_class; c++)
        {

            switch (classFieldsSetterFunctions[c][field])
            {
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED:          // Only the prototype is generated, the body must be custom, but it is not class specific.
                case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                    if (!printed[field]) // don't print more than once
                    {
                        qc_printf("%s setter_%s(%s, %s value);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM, qcc_fieldTypes[field]);
                        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && GENERATE_XYZ && !doNotGenerateXYZ[field]) // print vector components setters as well
                        {
                            // print _x, _y, _z variants as well
                            for (int comp = 0; comp < 3; comp++)
                            {
                                qc_printf("float setter_%s%s(%s, float value);\r\n", qcc_fieldNames[field], vectorComponents[comp],  ENTITY_PARAM);
                            }
                        }
                    }
                    printed[field] = 1;
                break;

                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED:
                    qc_printf("%s setter_%s_%s(%s, %s value);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], qcc_entityClassNames[c], ENTITY_PARAM, qcc_fieldTypes[field]);
                    if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && GENERATE_XYZ && !doNotGenerateXYZ[field]) // print vector components setters as well
                    {
                        // print _x, _y, _z variants as well
                        for (int comp = 0; comp < 3; comp++)
                        {
                            qc_printf("float setter_%s_%s%s(%s, float value);\r\n",  qcc_fieldNames[field], qcc_entityClassNames[c], vectorComponents[comp], ENTITY_PARAM);
                        }
                    }
                break;
            }
        }
    }
    // getters prototypes
    memset(printed, 0, sizeof printed);
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        for (int c = 0; c < qcc_max_class; c++)
        {

            switch (classFieldsGetterFunctions[c][field])
            {
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED:          // Only the prototype is generated, the body must be custom, but it is not class specific.
                case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                    if (!printed[field]) // don't print more than once
                    {
                        qc_printf("%s getter_%s(%s);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM);
                        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && !GENERATE_XYZ)
                        {
                            qc_printf("float* getter_%s_ptr(%s);\r\n",  qcc_fieldNames[field], ENTITY_PARAM);
                        }
                    }
                    printed[field] = 1;
                break;
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED:
                    qc_printf("%s getter_%s_%s(%s);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], qcc_entityClassNames[c], ENTITY_PARAM);
                    if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) & !GENERATE_XYZ)
                    {
                        qc_printf("float* getter_%s_%s_ptr(%s);\r\n", qcc_fieldNames[field], qcc_entityClassNames[c], ENTITY_PARAM);
                    }
                break;
            }
        }
    }
    // now the real getter and setter functions.
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        if (field == entLeaves_index)
        {
            // no setter for entleaves!
            continue;
        }
        qc_printf("%s set_%s(%s, %s value);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM, qcc_fieldTypes[field]);
        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR])) // print vector components setters as well
        {
            if (GENERATE_XYZ)
            {
                if (!doNotGenerateXYZ[field])
                {

                    // print _x, _y, _z variants as well
                    for (int comp = 0; comp < 3; comp++)
                    {
                        qc_printf("float set_%s%s(%s, float value);\r\n", qcc_fieldNames[field], vectorComponents[comp], ENTITY_PARAM);
                    }
                }

            }
            else
            {
                // print _x, _y, _z variants as well
                for (int comp = 0; comp < 3; comp++)
                {
                    qc_printf("#define set_%s%s(%s, value) (get_%s_ptr((%s))[%d] = (value))\r\n", qcc_fieldNames[field], vectorComponents[comp], ENTITY_PARAM_MACRO, qcc_fieldNames[field], ENTITY_PARAM_MACRO, comp);
                }

            }
        }
    }
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        qc_printf("%s get_%s(%s);\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM);
        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && !GENERATE_XYZ) // print vector components setters as well
        {
            qc_printf("float* get_%s_ptr(%s);\r\n", qcc_fieldNames[field], ENTITY_PARAM);
        }

    }
    qc_printf("#endif //EDICT_GETTER_SETTERS\r\n");
    //
    qc_printf("#endif //FIELD_GETTER_SETTERS\r\n");
    fclose(c_file);
    //
    //>>>>>>>>>>>>>>>>> TO PUT IN C FILE
    //
    c_file = fopen ("field_getters_setters.c", "wb");
    qc_printf("// File fields_getters_setters.c\r\n");
    qc_printf("%s", header);
    // converters
    qc_printf("#include \"quakedef.h\"\r\n");

    // array definition
    qc_printf("#include \"quakedef.h\"\r\n");
    qc_printf("#if EDICT_GETTER_SETTERS\r\n");
    //
    // ed allocator function
    qc_printf("void *allocEdByType(int classType)\r\n");
    qc_printf("{\r\n");
    qc_printf("  switch (classType)\r\n");
    qc_printf("  {\r\n");
    for (int i = 0; i < qcc_max_class; i++)
    {
        qc_printf("    case %s_edict_idx: \r\n", qcc_entityClassNames[i]);
        qc_printf("       return Z_CallocFailable(sizeof(%s_edict_t), 1, PU_LEVEL, NULL);\r\n", qcc_entityClassNames[i]);
    }
    qc_printf("  }\r\n");
    qc_printf(" while(1) FIXME(\"Wrong classType\");\r\n");
    qc_printf(" return NULL;\r\n");
    qc_printf("}\r\n");
    qc_printf("unsigned int getEdictEntvarSize(edict_t *e)");
    qc_printf("{\r\n");
    qc_printf("  int classType = qcc_classname2type[e->qcc_classname];\r\n");
    qc_printf("  switch (classType)\r\n");
    qc_printf("  {\r\n");
    for (int i = 0; i < qcc_max_class; i++)
    {
        qc_printf("    case %s_edict_idx: \r\n", qcc_entityClassNames[i]);
        qc_printf("       return sizeof(%s_entvars_t);\r\n", qcc_entityClassNames[i]);
    }
    qc_printf("  }\r\n");
    qc_printf(" return 0;\r\n");
    qc_printf("}\r\n");

    //
    qc_printf("const uint8_t qcc_classname2type[max_classname_string_index] = \r\n{\r\n");
    for (int i = 0; i < max_classname_string_index; i++)
    {
        qc_printf("    [%s_string_index] = %s_edict_idx,\r\n", (i==0) ? "NULL" : cFriendlyClassNames[i], qcc_entityClassNames[qcc_classname2type[i]]);
    }
    qc_printf("\r\n};\r\n");
    // now let's print the setter array
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        if (classFieldsSetterFunctions[full_edict_idx][field] == FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED)
        {
            continue;
        }
        if (field == entLeaves_index)
        {
            // no setter for entleaves!
            continue;
        }
        int isVector = 0;
        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && GENERATE_XYZ && !doNotGenerateXYZ[field]) // print vector components setters as well
        {
            isVector = 1;
        }
        for (int comp = (isVector ? 0 : 3); comp < 4; comp++)
        {
            if (comp == 3)
                qc_printf("%s (*const setters_%s_array[qcc_max_class])(" ENTITY_PARAM ", %s value) = {", qcc_fieldTypes[field], qcc_fieldNames[field], qcc_fieldTypes[field]);
            else
            {
                qc_printf("float (*const setters_%s_array%s[qcc_max_class])(" ENTITY_PARAM ", float value) = {",  qcc_fieldNames[field], vectorComponents[comp]);
            }
            for (int c = 0; c < qcc_max_class; c++)
            {

                switch (classFieldsSetterFunctions[c][field])
                {
                    case FUNCTION_IMPLEMENTATION_ERROR_NOT_IMPLEMENTED:
                            qc_printf("setter_%s_error%s, ", qcc_fieldTypes[field], vectorComponents[comp]);
                    break;
                    case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING:
                        qc_printf("setter_%s_warning%s, ", qcc_fieldTypes[field], vectorComponents[comp]);
                    break;
                    case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO:
                        qc_printf("setter_%s_non_zero_error%s, ", qcc_fieldTypes[field], vectorComponents[comp]);
                    break;
                    case FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED:          // Only the prototype is generated, the body must be custom, but it is not class specific.
                    case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                        qc_printf("setter_%s%s, ", qcc_fieldNames[field],vectorComponents[comp]);
                    break;
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                    case FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED:
                        qc_printf("setter_%s_%s%s, ", qcc_fieldNames[field], qcc_entityClassNames[c],vectorComponents[comp]);
                    break;
                }
            }
            qc_printf("};\r\n");
        }
    }
    // now the getter array definition
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        if (classFieldsGetterFunctions[full_edict_idx][field] == FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED)
        {
            continue;
        }
        qc_printf("%s (*const getters_%s_array[qcc_max_class])(" ENTITY_PARAM ") = {", qcc_fieldTypes[field], qcc_fieldNames[field]);
        for (int c = 0; c < qcc_max_class; c++)
        {
            switch (classFieldsGetterFunctions[c][field])
            {
                case FUNCTION_IMPLEMENTATION_ERROR_NOT_IMPLEMENTED:
                    qc_printf("getter_%s_error, ", qcc_fieldTypes[field]);
                break;
                case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING:
                    qc_printf("getter_%s_warning, ", qcc_fieldTypes[field]);
                break;
                case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO:
                    if (field == entLeaves_index)
                    {
                        qc_printf("getter_%s_zero, ", funcNameTypes[TYPE_ENTLEAVES]);
                    }
                    else
                    {
                        qc_printf("getter_%s_zero, ", qcc_fieldTypes[field]);
                    }
                break;
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED:          // Only the prototype is generated, the body must be custom, but it is not class specific.
                case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                    qc_printf("getter_%s, ", qcc_fieldNames[field]);
                break;
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED:
                    qc_printf("getter_%s_%s, ", qcc_fieldNames[field], qcc_entityClassNames[c]);
                break;
            }
        }
        qc_printf("};\r\n");
    }
    #if (!GENERATE_XYZ)
    {
        // for vector we need to put also the getter_ptr function.
        for (int field = 0; field < MAX_FIELDS; field++)
        {
            if (strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]))
                continue;
            qc_printf("float* (*const getters_%s_ptr_array[qcc_max_class])(" ENTITY_PARAM ") = {", qcc_fieldNames[field]);
            for (int c = 0; c < qcc_max_class; c++)
            {
                switch (classFieldsGetterFunctions[c][field])
                {
                    case FUNCTION_IMPLEMENTATION_ERROR_NOT_IMPLEMENTED:
                        qc_printf("getter_%s_ptr_error, ", qcc_fieldTypes[field]);
                    break;
                    case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_WARNING:
                        qc_printf("getter_%s_ptr_warning, ", qcc_fieldTypes[field]);
                    break;
                    case FUNCTION_IMPLEMENTATION_NOT_IMPLEMENTED_RETURNS_ZERO_ERROR_ON_SET_NON_ZERO:
                        qc_printf("getter_%s_ptr_zero, ", qcc_fieldTypes[field]);
                    break;
                    case FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED:          // Only the prototype is generated, the body must be custom, but it is not class specific.
                    case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                        qc_printf("getter_%s_ptr, ", qcc_fieldNames[field]);
                    break;
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_PROTOTYPE_FULL_SPECIFIC_AUTOGENERATED:
                        qc_printf("getter_%s_%s_ptr, ", qcc_fieldNames[field], qcc_entityClassNames[c]);
                    break;
                }
            }
            qc_printf("};\r\n");
        }
    }
    #endif
    // now the real getter and setter functions.
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        // Note: field specific are defined entity full
        if (classFieldsSetterFunctions[full_edict_idx][field] == FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED)
        {
            continue;
        }
        if (field == entLeaves_index)
        {
            // no setter for entleaves!
            continue;
        }
        int isVector = 0;
        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && GENERATE_XYZ && !doNotGenerateXYZ[field]) // print vector components setters as well
        {
            isVector = 1;
        }
        for (int comp = (isVector ? 0 : 3); comp < 4; comp++)
        {
            const char *typestring = comp != 3 ? "float" : qcc_fieldTypes[field];
            qc_printf("%s set_%s%s(%s, %s value)\r\n", typestring, qcc_fieldNames[field], vectorComponents[comp], ENTITY_PARAM, typestring);
            qc_printf("{\r\n");
            qc_printf("    %s\r\n", GET_TYPE_STRING);
            if (field == qcc_classname_index)
            {
                qc_printf("#if CLASSNAME_DEBUG\r\n");
                qc_printf("    int oldClass = getters_qcc_classname_array[type](entity);\r\n");
                qc_printf("    if (oldClass != value)\r\n");
                qc_printf("    {\r\n");
                qc_printf("        printf(\"Class will change from %%d to %%d (%%s to %%s)\\r\\n\", oldClass, value, getStringFromIndex(oldClass), getStringFromIndex(value));\r\n");
                qc_printf("        if (oldClass || PRINT_ZERO_START_CLASSNAME)\r\n");
                qc_printf("           FIXME(\"\");\r\n");
                qc_printf("    }\r\n");
                qc_printf("#endif //CLASSNAME_DEBUG\r\n");

            }
            qc_printf("    DEBUG_FIELD(\"%s\");\r\n", qcc_fieldNames[field]);  // to set the accessed field name
            qc_printf("    return setters_%s_array%s[type](entity, value);\r\n",qcc_fieldNames[field], vectorComponents[comp]);
            qc_printf("}\r\n");
        }
    }
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        if (classFieldsGetterFunctions[full_edict_idx][field] == FUNCTION_IMPLEMENTATION_PROTOTYPE_FIELD_SPECIFIC_AUTOGENERATED)
        {
            continue;
        }
        if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && !GENERATE_XYZ) // print vector components setters as well
        {
            qc_printf("float* get_%s_ptr(%s)\r\n", qcc_fieldNames[field], ENTITY_PARAM);
            qc_printf("{\r\n");
            qc_printf("    %s\r\n", GET_TYPE_STRING);
            qc_printf("    DEBUG_FIELD(\"%s\");\r\n", qcc_fieldNames[field]);  // to set the accessed field name
            qc_printf("    return getters_%s_ptr_array[type](entity);\r\n",qcc_fieldNames[field]);
            qc_printf("}\r\n");
        }
        qc_printf("%s get_%s(%s)\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM);
        qc_printf("{\r\n");
        qc_printf("    %s\r\n", GET_TYPE_STRING);
        qc_printf("    DEBUG_FIELD(\"%s\");\r\n", qcc_fieldNames[field]);  // to set the accessed field name
        qc_printf("    return getters_%s_array[type](entity);\r\n",qcc_fieldNames[field]);
        qc_printf("}\r\n");
    }
    // now actual implementation of each setter which is marked as implemented automatically
    memset(printed, 0, sizeof printed);
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        for (int c = 0; c < qcc_max_class; c++)
        {
            int isVector = 0;
            if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR]) && GENERATE_XYZ && !doNotGenerateXYZ[field]) // print vector components setters as well
            {
                isVector = 1;
            }
            for (int comp = (isVector ? 0 : 3); comp < 4; comp++)
            {
                const char *typestring = comp != 3 ? "float" : qcc_fieldTypes[field];
                const char *cf = setterConversionFunction[classFieldsSetterFunctions[c][field]];
                if (!cf)
                    cf = "";
                switch (classFieldsSetterFunctions[c][field])
                {
                    case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                        if (!printed[field]) // don't print more than once
                        {
                            qc_printf("%s setter_%s%s(%s, %s value)\r\n", typestring, qcc_fieldNames[field], vectorComponents[comp], ENTITY_PARAM, typestring);
                            qc_printf("{\r\n");
                            qc_printf("    return entity->%s%s = value;\r\n", qcc_fieldNames[field], vectorComponentsIndirection[comp]);
                            qc_printf("}\r\n");
                        }
                        printed[field] = 1;
                    break;
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                    case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                    case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                        qc_printf("%s setter_%s_%s%s(%s, %s value)\r\n", typestring, qcc_fieldNames[field], qcc_entityClassNames[c], vectorComponents[comp], ENTITY_PARAM, typestring);
                        qc_printf("{\r\n");
                        if (field == entLeaves_index)   // special case
                        {
                            qc_printf("    #if DO_FIND_TOUCHED_LEAVES_JIT == 3\r\n");
                        }
                        if (isRomGenerated[classFieldsSetterFunctions[c][field]])
                            qc_printf("    ((%s_edict_t*) entity)->v.romEntvars->%s%s = %s%s(value);\r\n", qcc_entityClassNames[c], qcc_fieldNames[field], vectorComponentsIndirection[comp], (comp == 3 && isVector) ? "v" : "", cf);
                        else
                            qc_printf("    ((%s_edict_t*) entity)->v.%s%s = %s%s(value);\r\n", qcc_entityClassNames[c], qcc_fieldNames[field], vectorComponentsIndirection[comp], (comp == 3 && isVector) ? "v" : "", cf);
                        if (field == entLeaves_index)   // special case
                        {
                            qc_printf("    #endif\r\n");
                        }
                        qc_printf("    return value;\r\n", qcc_entityClassNames[c], qcc_fieldNames[field], vectorComponentsIndirection[comp]);
                        qc_printf("}\r\n");
                    break;
                }
            }
        }
    }
    // now getters
    memset(printed, 0, sizeof printed);
    for (int field = 0; field < MAX_FIELDS; field++)
    {
        for (int c = 0; c < qcc_max_class; c++)
        {
            int isVector = 0;
            if (!strcmp(qcc_fieldTypes[field], types[TYPE_VECTOR])) // print vector components setters as well
            {
                isVector = 1;
            }
            const char *cf = getterConversionFunction[classFieldsGetterFunctions[c][field]];
            if (!cf)
                cf = "";
            switch (classFieldsGetterFunctions[c][field])
            {
                case FUNCTION_IMPLEMENTATION_FIELD_SPECIFIC_AUTOGENERATED:
                    if (!printed[field]) // don't print more than once
                    {
                        qc_printf("%s getter_%s(%s)\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], ENTITY_PARAM);
                        qc_printf("{\r\n");
                        qc_printf("    return entity->%s;\r\n",  qcc_fieldNames[field]);
                        qc_printf("}\r\n");
#if !GENERATE_XYZ
                        if (isVector)
                        {
                            qc_printf("float* getter_%s_ptr(%s)\r\n", qcc_fieldNames[field], ENTITY_PARAM);
                            qc_printf("{\r\n");
                            qc_printf("    return &entity->%s;\r\n", qcc_fieldNames[field]);
                            qc_printf("}\r\n");
                        }
#endif
                    }
                    printed[field] = 1;
                break;
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED12P4:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED10P6:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_SHORT_FIXED8P8:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED_FORCE:
                case FUNCTION_IMPLEMENTATION_FULL_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_ANGLE:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED13P3:
                case FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED_SHORT_FIXED12P4:
                    qc_printf("%s getter_%s_%s(%s)\r\n", qcc_fieldTypes[field], qcc_fieldNames[field], qcc_entityClassNames[c], ENTITY_PARAM);
                    qc_printf("{\r\n");
                    if (field == entLeaves_index)   // special case
                    {
                        qc_printf("    #if DO_FIND_TOUCHED_LEAVES_JIT == 3\r\n");
                        if (classFieldsGetterFunctions[c][field] == FUNCTION_IMPLEMENTATION_FULL_ROM_AUTOGENERATED)
                           qc_printf("       return &(%s%s(((%s_edict_t*) entity)->v.romEntvars->%s));\r\n", isVector ? "v" : "", cf, qcc_entityClassNames[c], qcc_fieldNames[field]);
                        else
                           qc_printf("       return &(%s%s(((%s_edict_t*) entity)->v.%s));\r\n", isVector ? "v" : "", cf, qcc_entityClassNames[c], qcc_fieldNames[field]);
                        qc_printf("    #else\r\n");
                        qc_printf("       return NULL;\r\n");
                        qc_printf("    #endif\r\n");

                    }
                    else
                    {
                        if (isRomGenerated[classFieldsGetterFunctions[c][field]])
                            qc_printf("    return %s%s(((%s_edict_t*) entity)->v.romEntvars->%s);\r\n", isVector ? "v" : "", cf, qcc_entityClassNames[c], qcc_fieldNames[field]);
                        else
                            qc_printf("    return %s%s(((%s_edict_t*) entity)->v.%s);\r\n", isVector ? "v" : "", cf, qcc_entityClassNames[c], qcc_fieldNames[field]);
                    }
                    qc_printf("}\r\n");
#if !GENERATE_XYZ
                    if (isVector)
                    {
                        qc_printf("float* getter_%s_%s_ptr(%s)\r\n", qcc_fieldNames[field], qcc_entityClassNames[c], ENTITY_PARAM);
                        qc_printf("{\r\n");
                        qc_printf("    return &((%s_edict_t*) entity)->v.%s.v;\r\n", qcc_entityClassNames[c],qcc_fieldNames[field]);
                        qc_printf("}\r\n");
                    }
#endif
                break;
            }
        }
    }
    // now warnings and errors
    for (int i = 0; i < TYPE_MAX; i++)
    {
        int isVector = 0;
#if GENERATE_XYZ
        if (i == TYPE_VECTOR ) // print vector components setters as well
        {
            isVector = 1;
        }
#endif
        for (int comp = (isVector ? 0 : 3); comp < 4; comp++)
        {
            const char *typestring = comp != 3 ? "float" : types[i];
            qc_printf("%s setter_%s_error%s(%s, %s value)\r\n", typestring, funcNameTypes[i], vectorComponents[comp], ENTITY_PARAM, typestring);
            qc_printf("{\r\n");
            qc_printf("    DEBUG_ERROR_SETTER(entity, value);\r\n");
            qc_printf("    return value;");
            qc_printf("}\r\n");
            qc_printf("%s setter_%s_warning%s(%s, %s value)\r\n", typestring, funcNameTypes[i], vectorComponents[comp], ENTITY_PARAM, typestring);
            qc_printf("{\r\n");
            qc_printf("    DEBUG_WARNING_SETTER(entity, value);\r\n");
            qc_printf("    return value;");
            qc_printf("}\r\n");
            if (isVector && comp == 3)
            {
                qc_printf("%s setter_%s_non_zero_error%s(%s, %s value)\r\n", typestring, funcNameTypes[i], vectorComponents[comp], ENTITY_PARAM, typestring);
                qc_printf("{\r\n");
                qc_printf("    if (value.x != 0 || value.y != 0 || value.z !=0)\r\n");
                qc_printf("    {\r\n");
                qc_printf("        DEBUG_ERROR_SETTER(entity, value.x);\r\n");
                qc_printf("        DEBUG_ERROR_SETTER(entity, value.y);\r\n");
                qc_printf("        DEBUG_ERROR_SETTER(entity, value.z);\r\n");
                qc_printf("    }\r\n");
                qc_printf("    return value;\r\n");
                qc_printf("}\r\n");
            }
            else
            {
                qc_printf("%s setter_%s_non_zero_error%s(%s, %s value)\r\n", typestring, funcNameTypes[i], vectorComponents[comp], ENTITY_PARAM, typestring);
                qc_printf("{\r\n");
                qc_printf("    if (value != 0)\r\n");
                qc_printf("        DEBUG_ERROR_SETTER(entity, value);\r\n");
                qc_printf("    return value;\r\n");
                qc_printf("}\r\n");
            }

        }

    }
    for (int i = 0; i < TYPE_MAX; i++)
    {
        #if !GENERATE_XYZ
        if (i == TYPE_VECTOR && !GENERATE_XYZ) // print vector components setters as well
        {
            qc_printf("float* getter_%s_ptr_error(%s)\r\n", types[i], ENTITY_PARAM);
            qc_printf("{\r\n");
            qc_printf("    DEBUG_ERROR_GETTER(entity);\r\n");
            qc_printf("    return dummyVecPtr;\r\n");
            qc_printf("}\r\n");
            qc_printf("float* getter_%s_ptr_warning(%s)\r\n", types[i], ENTITY_PARAM);
            qc_printf("{\r\n");
            qc_printf("    DEBUG_WARNING_GETTER(entity);\r\n");
            qc_printf("    return dummyVecPtr;\r\n");
            qc_printf("}\r\n");
            //
        }
        #endif
        qc_printf("%s getter_%s_error(%s)\r\n", types[i], funcNameTypes[i], ENTITY_PARAM);
        qc_printf("{\r\n");
        qc_printf("    DEBUG_ERROR_GETTER(entity);\r\n");
        qc_printf("    return ZERO_%s;\r\n", funcNameTypes[i]);
        qc_printf("}\r\n");
        qc_printf("%s getter_%s_warning(%s)\r\n", types[i], funcNameTypes[i], ENTITY_PARAM);
        qc_printf("{\r\n");
        qc_printf("    DEBUG_WARNING_GETTER(entity);\r\n");
        qc_printf("    return ZERO_%s;\r\n", funcNameTypes[i]);
        qc_printf("}\r\n");
        //
        qc_printf("%s getter_%s_zero(%s)\r\n", types[i], funcNameTypes[i], ENTITY_PARAM);
        qc_printf("{\r\n");
        qc_printf("    (void) entity;");
        qc_printf("    return ZERO_%s;\r\n", funcNameTypes[i]);
        qc_printf("}\r\n");

    }
    qc_printf("#endif // EDICT_GETTER_SETTERS\r\n");
    fclose(c_file);
    return 0;
}
