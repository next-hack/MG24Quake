/**
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
 *
 */
/**
 *  DESCRIPTION:
 *  delay utility function.
 *
 */
#ifndef SRC_DELAY_H_
#define SRC_DELAY_H_
#include <stdint.h>
#include "em_timer.h"
#include "main.h"
static inline void delay(uint32_t milliseconds)
{
    milliseconds *= (TICK_TIMER_FREQUENCY_HZ / 1000);    // TICK_TIMER is clocked at 10 MHz
    uint32_t timeNow = TICK_TIMER->CNT;
    while ((uint32_t) TICK_TIMER->CNT - timeNow < milliseconds)
        ;
}
#endif /* SRC_DELAY_H_ */
