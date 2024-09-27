/**
 *  Keyboard interface for Doom Port to the EFR32xG2x MCUs by Nicola Wrachien
 *
 *  Copyright (C) 2021-23 Nicola Wrachien (next-hack in the comments).
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 *  02111-1307, USA.
 *
 * Description: Keyboard handling functions for different types
 * (i2c, shift register).
 */
#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <stdint.h>
#include "main.h"
#include "config_enum_values.h"
//Keys
#include "boards.h"
void initKeyboard();
void getKeys(uint16_t *keys);
void getAnalogInput(int32_t * lx, int32_t *ly, int32_t *rx, int32_t *ry);
#endif
