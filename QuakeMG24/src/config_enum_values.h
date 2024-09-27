/***************************************************************************//**
 * @file enum_values.h
 * @brief  enumeration for configuration values.
 *
 *  Copyright (C) 2022-2024 by Nicola Wrachien
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
 ******************************************************************************/
#ifndef SRC_ENUM_VALUES_H_
#define SRC_ENUM_VALUES_H_
// this file contains all the enum values for hardware, etc.
// External memory defines
#define EXT_MEMORY_TYPE_INTERLEAVED_SPI     0
//
// AUDIO enums
#define PWM_AUDIO_MODE                      1
#define DAC_AUDIO_MODE                      2
// KEYBOARD enums
#define I2C_KEYBOARD                        1
#define PARALLEL_KEYBOARD                   2
#define SPI74165_KEYBOARD                   3
#define SPI2X74165_KEYBOARD                 4        // two 74165 cascaded.
// BOARD type enums
#define BOARD_WSTK_1                        1       // first board, with I2C Keyboard, dual audio, and 320x240 display
#define BOARD_WSTK_2                        2       // Second board, with SPI Keyboard, dual audio, and 320x240 display
#define BOARD_WSTK_3                        3       // third board, with SPI Keyboard, dual audio, and 320x240 display
#define BOARD_SPARKDOOM                     4       // Sparkfun board, with SPI Keyboard, dual audio, and 320x240 display
#define BOARD_SPARKDOOM_ARDUINONANOMATTER   5       // Arduino nano matter board on the Sparkdoom board, with SPI Keyboard, dual audio, and 320x240 display
#define BOARD_THEGAMEPAD_ARDUINONANOMATTER  6       // The gamepad V1.0 with ARDUINO NANO MATTER board.
#endif /* SRC_ENUM_VALUES_H_ */
