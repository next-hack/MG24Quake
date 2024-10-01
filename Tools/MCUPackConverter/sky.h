/*
 MCUpackconverter by Nicola Wrachien (next-hack in the comments)

 This file is based on model.c, from Quake.

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
#ifndef SKY_H
#define SKY_H
typedef struct
{
    uint8_t skytexture[128*256];
    uint8_t modelName[MAX_QPATH];
} sky_data_t;
typedef struct
{
    uint8_t modelName[MAX_QPATH];
    uint8_t skyNum;
} __attribute__((packed)) sky_table_t;
typedef struct
{
    int numskies;
    sky_data_t *skydata;
} sky_collection_t;
void addSky(uint8_t * skybuffer, char *modelName);
uint8_t *createSkies(int *differentSkies, int *numberOfSkies, sky_table_t **skyList);

#endif // SKY_H
