/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

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
#include "quakedef.h"

extern const uint8_t qcc_classname2type[max_classname_string_index];
vector set_qcc_absmin(edict_t *ent, vector value)
{
    (void) ent;
    (void) value;
    FIXME("Trying to set absmin!");
    return value;
}
vector set_qcc_absmax(edict_t *ent, vector value)
{
    (void) ent;
    (void) value;
    FIXME("Trying to set absmax!");
    return value;
}
vector set_qcc_size(edict_t *ent, vector value)
{
    (void) ent;
    (void) value;
    FIXME("Trying to set size!");
    return value;
}
float set_qcc_colormap(edict_t *ent, float value)
{
    (void) ent;
    if (value)
        printf("Trying to set non zero colormap!");
    return value;
}
float get_qcc_colormap(edict_t *ent)
{
    (void) ent;
    return 0;
}
/*
 from SV_LinkEdict in World.c
 if ((int)get_qcc_flags(ent) & FL_ITEM)
 {
 set_qcc_absmin_x(ent,  VEC(get_qcc_absmin(ent))[0] - 15);
 set_qcc_absmin_y(ent,  VEC(get_qcc_absmin(ent))[1] - 15);
 set_qcc_absmax_x(ent,  VEC(get_qcc_absmax(ent))[0] + 15);
 set_qcc_absmax_y(ent,  VEC(get_qcc_absmax(ent))[1] + 15);
 }
 else
 {	// because movement is clipped an epsilon away from an actual edge,
 // we must fully check even when bounding boxes don't quite touch
 set_qcc_absmin_x(ent,  VEC(get_qcc_absmin(ent))[0] - 1);
 set_qcc_absmin_y(ent,  VEC(get_qcc_absmin(ent))[1] - 1);
 set_qcc_absmin_z(ent,  VEC(get_qcc_absmin(ent))[2] - 1);
 set_qcc_absmax_x(ent,  VEC(get_qcc_absmax(ent))[0] + 1);
 set_qcc_absmax_y(ent,  VEC(get_qcc_absmax(ent))[1] + 1);
 set_qcc_absmax_z(ent,  VEC(get_qcc_absmax(ent))[2] + 1);
 }
 */

vector get_qcc_absmax(edict_t *ent)
{
    vector o = get_qcc_origin(ent);
    vector maxs = get_qcc_maxs(ent);
    o.x += maxs.x;
    o.y += maxs.y;
    o.z += maxs.z;
    int flags = get_qcc_flags(ent);
    if (flags & FL_ITEM)
    {
        o.x += 15;
        o.y += 15;
    }
    else
    {
        o.x += 1;
        o.y += 1;
        o.z += 1;
    }
    return o;
}
vector get_qcc_absmin(edict_t *ent)
{
    vector o = get_qcc_origin(ent);
    vector mins = get_qcc_mins(ent);
    o.x += mins.x;
    o.y += mins.y;
    o.z += mins.z;
    int flags = get_qcc_flags(ent);
    if (flags & FL_ITEM)
    {
        o.x -= 15;
        o.y -= 15;
    }
    else
    {
        o.x -= 1;
        o.y -= 1;
        o.z -= 1;
    }
    return o;
}
vector get_qcc_size(edict_t *ent)
{
    vector max = get_qcc_maxs(ent);
    vector min = get_qcc_mins(ent);

    vector size;
    size.x = max.x - min.x;
    size.y = max.y - min.y;
    size.z = max.z - min.z;
    return size;
}

string_t get_qcc_classname(edict_t *entity)
{
    return entity->qcc_classname;
}
string_t set_qcc_classname(edict_t *entity, string_t value)
{
    if (value >= max_classname_string_index)
    {
        printf("Class number = %d (%s)", value, getStringFromIndex(value));
        FIXME("WRONG CLASS NUMBER/NAME");
    }
    int newtype = qcc_classname2type[value];
    int oldtype = qcc_classname2type[entity->qcc_classname];
    if (entity->qcc_classname && newtype != oldtype)
    {
        printf("Old type %d, new type %d\r\n", oldtype, newtype);
        while (1)
            FIXME("CHANGING EDICT TYPE NOT ALLOWED!");
    }
    entity->qcc_classname = value;
    return value;
}
float getter_qcc_takedamage_missile(edict_t *entity)
{
    (void) entity;
    return 0;
}
float setter_qcc_takedamage_missile(edict_t *entity, float value)
{
    (void) entity;
    printf("%f value\r\n", value);
    FIXME("SET QCC TAKEDAMAGE IN MISSILE");
    return value;
}
string_t getter_qcc_targetname_missile(edict_t *entity)
{
    (void) entity;
    return 0;
}
string_t setter_qcc_targetname_missile(edict_t *entity, string_t value)
{
    (void) entity;
    if (value != 0)
    {
        printf("%d Targetname\r\n", value);
        FIXME("SET QCC TARGETNAME IN MISSILE");
    }
    return 0;
}
float getter_qcc_spawnflags_missile(edict_t *entity)
{
    (void) entity;
    return 0;
}
float setter_qcc_spawnflags_missile(edict_t *entity, float value)
{
    (void) entity;
    int ivalue = (int) value;
    const int mask = ~(SPAWNFLAG_NOT_DEATHMATCH | SPAWNFLAG_NOT_EASY | SPAWNFLAG_NOT_MEDIUM | SPAWNFLAG_NOT_HARD);
    // the previous spawnflags are handled in externally.
    if (ivalue & mask)
    {
        printf("Spawn flags %d\r\n", (int) value);
        FIXME("SET QCC SPAWNFLAGS IN MISSILE");
    }
    return 0;
}
func_t getter_qcc_touch_path_corner(edict_t *entity)
{
    (void) entity;
    return qcc_t_movetarget_func_index;
}
func_t setter_qcc_touch_path_corner(edict_t *entity, func_t f)
{
    (void) entity;
    if (f != qcc_t_movetarget_func_index)
    {
        printf("touch f index: %d\r\n", f);
        FIXME("trying to set a different touch for path corner");
    }
    return f;
}
#if PATH_CORNER_HAVE_DIFFERENT_SIZES
vector getter_qcc_mins_path_corner(edict_t *entity)
{
    (void) entity;
    int size = ((path_corner_edict_t *) entity)->v.minmaxssize;
    vector v =
    {   .x = - size, .y = - size, .z = -size};
    return v;
}
vector setter_qcc_mins_path_corner(edict_t *entity, vector v)
{
    (void) entity;
    if (v.x != v.y || v.y != v.z || v.x >= 0)
    {
        printf("wrong min size: %f %f %f\r\n", v.x, v.y, v.z);
        FIXME("path corner size error");
    }
    ((path_corner_edict_t *) entity)->v.minmaxssize = - v.x;
    return v;
}
vector getter_qcc_maxs_path_corner(edict_t *entity)
{
    (void) entity;
    int size = ((path_corner_edict_t *) entity)->v.minmaxssize;
    vector v =
    {   .x = size, .y = size, .z = size};
    return v;
}
vector setter_qcc_maxs_path_corner(edict_t *entity, vector v)
{
    (void) entity;
    if (v.x != v.y || v.y != v.z || v.x < 0)
    {
        printf("wrong max size: %f %f %f\r\n", v.x, v.y, v.z);
        FIXME("path corner size error");
    }
    ((path_corner_edict_t *) entity)->v.minmaxssize = v.x;
    return v;
}
#else
vector getter_qcc_mins_path_corner(edict_t *entity)
{
    (void) entity;
    int size = 8;
    vector v =
    { .x = -size, .y = -size, .z = -size
    };
    return v;
}
vector setter_qcc_mins_path_corner(edict_t *entity, vector v)
{
    (void) entity;
    if (v.x != -8 || v.x != v.y || v.y != v.z)
    {
        printf("wrong min size: %f %f %f\r\n", v.x, v.y, v.z);
        FIXME("path corner size error");
    }
//    ((path_corner_edict_t *) entity)->v.minmaxssize = - v.x;
    return v;
}
vector getter_qcc_maxs_path_corner(edict_t *entity)
{
    (void) entity;
    int size = 8;
    vector v =
    { .x = size, .y = size, .z = size
    };
    return v;
}
vector setter_qcc_maxs_path_corner(edict_t *entity, vector v)
{
    (void) entity;
    if (v.x != 8 || v.x != v.y || v.y != v.z)
    {
        printf("wrong max size: %f %f %f\r\n", v.x, v.y, v.z);
        FIXME("path corner size error");
    }
//    ((path_corner_edict_t *) entity)->v.minmaxssize = v.x;
    return v;
}

#endif
float setter_qcc_mins_path_corner_x(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
float setter_qcc_mins_path_corner_y(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
float setter_qcc_mins_path_corner_z(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
float setter_qcc_maxs_path_corner_x(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
float setter_qcc_maxs_path_corner_y(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
float setter_qcc_maxs_path_corner_z(edict_t *entity, float v)
{
    (void) entity;
    FIXME("Not implemented");
    return v;
}
