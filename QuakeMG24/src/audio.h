/**
 *  DAC and PWM  for sound generation..
 *
 *  Note: DAC needs external amplification.
 *
 *  Copyright (C) 2021-2024 by Nicola Wrachien (next-hack in the comments)
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
 *  DESCRIPTION:
 *  This was taken from our old Doom Port project to MG24 devices.
 *  The update sound function is implemented elsewhere.
 *  We kept just the init function.
 *
 */
#ifndef SRC_PWM_AUDIO_H_
#define SRC_PWM_AUDIO_H_
#include "main.h"
#include "em_device.h"
#include "em_gpio.h"
#include "macros.h"
#include "boards.h"
//
#define AUDIO_SAMPLE_RATE               11025
//
#define AUDIO_BUFFER_LENGTH             (1024)
#define AUDIO_BUFFER_DELAY              (200)   // up to 20 ms delay
#define ZERO_AUDIO_LEVEL                (2048)  // 12 bit dac
//
#define DMX_DATA_SOUND_OFFSET       0x18
//
#ifndef AUDIO_SAMPLE_TIMER
  #define AUDIO_SAMPLE_TIMER_NUMBER     2
  #define AUDIO_SAMPLE_TIMER            CAT(TIMER, AUDIO_SAMPLE_TIMER_NUMBER)
#endif

//
typedef struct
{
    uint16_t lastAudioBufferIdx;
    uint16_t offset;
    uint8_t sfxIdx;
    int8_t volumeLeft;
    int8_t volumeRight;
} soundChannel_t;
//
void initAudio();
//
extern AUX_SECTION int8_t audioBuffer[AUDIO_BUFFER_LENGTH * 2];
#endif /* SRC_PWM_AUDIO_H_ */
