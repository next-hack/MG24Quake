/***************************************************************************//**
 * @file main.h
 * @brief main function for Quake  on EFR32xg24 MCUs
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
 *******************************************************************************
 ******************************************************************************/
#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>
#include "macros.h"
#include "sl_system_process_action.h"
//
#define OVERCLOCK                         1
#if OVERCLOCK
#define OC_PLLN                           4095
#define OC_PLLD                           1169
#else
#define OC_PLLN                           3999
#define OC_PLLD                           1949
#endif
#define CPU_FREQUENCY                     (39000 * (OC_PLLN + 1) / (OC_PLLD + 1) * 1000)
// Test configuration
#define DISABLE_CACHING_TEXTURE_TO_FLASH  0    // non 0 is only for debug and to test how bad we can get if too many textures are uncached
#define TEST_DISABLE_ASYNCH_LOAD          0    // non 0 is to check how slow the rendering will be if data is not drawn asynchronously.
//
// Feature config
#define FAST_CPU_SMALL_FLASH              0       // if we have fast cpu but small flash, we can reduce math table sizes
#define CORRECT_TABLE_ERROR               1       // mandatory for demo compatibility. Will correct errors due to small math tables
//
#define CACHE_ALL_COLORMAP_TO_RAM         0       // if enabled this wastes 8.25 more kB, but will improve a little bit the performance
//////
#define PAK_FILE_NAME                     "PAK0.PAK" // this is the name on SD card
//
// Board-independent configs
//
#define FPCLK                             CPU_FREQUENCY
//
// Serial Output configuration
//
#define DEBUG_OUT_PRINTF                  1
//
#define UART_OVERSAMPLE                   16U
#define UART_BAUDRATE                     115200U
//
// Timer config
#define TICK_TIMER_FREQUENCY_HZ           (CPU_FREQUENCY / 8)    // 10MHz without OC
#define TIMER_TICKS_PER_MILLISECOND       (TICK_TIMER_FREQUENCY_HZ / 1000UL)
//
// TIMERS
// Free running timer, used for delays and timings
#define TICK_TIMER_NUMBER                 0
#define TIME_TIMER_NUMBER                 1   // used by sys float time.
#define TIME_TIMER_FREQUENCY_HZ           (CPU_FREQUENCY / 1024 )    // FIXME 78kHz @ 10MHz... we would like it even slower, so this will fail after 55ks (32000 s with OC)... which is quite a lot.

#define AUDIO_SAMPLE_TIMER_NUMBER         2

#define FIRST_SPI_NUMBER                  0
#define SECOND_SPI_NUMBER                 1
#define FIRST_SPI_USART                   CAT(EUSART, FIRST_SPI_NUMBER)
#define SECOND_SPI_USART                  CAT(EUSART, SECOND_SPI_NUMBER)

// LDMA and PRS
#define FIRST_SPI_LDMA_CH                 (0)
#define SECOND_SPI_LDMA_CH                (FIRST_SPI_LDMA_CH + 1)
#define INTERLEAVED_SPI_PRS_CH            8     // DO NOT USE PRS 7, it's for BT
//
#define FIRST_SPI_LDMA_BYTE_CH                 (SECOND_SPI_LDMA_CH + 1)
#define SECOND_SPI_LDMA_BYTE_CH                (FIRST_SPI_LDMA_BYTE_CH + 1)


#define DISPLAY_LDMA_CH                   (SECOND_SPI_LDMA_BYTE_CH + 1)
//

//
#define AUDIO_DMA_CHANNEL_L               (DISPLAY_LDMA_CH + 1)
#define AUDIO_DMA_CHANNEL_R               (AUDIO_DMA_CHANNEL_L + 1)
//
#define ADC_USES_DMA 1
//
#define IADC_LDMA_CH                      (AUDIO_DMA_CHANNEL_R + 1)
//
// Actual timer definitions.
#define TICK_TIMER                        CAT(TIMER, TICK_TIMER_NUMBER)
#define TIME_TIMER                        CAT(TIMER, TIME_TIMER_NUMBER)
#define AUDIO_SAMPLE_TIMER                CAT(TIMER, AUDIO_SAMPLE_TIMER_NUMBER)
#define AUDIO_PWM_TIMER                   CAT(TIMER, AUDIO_PWM_TIMER_NUMBER)
//
#define AUX_SECTION __attribute__ ((section(".aux_ram_bss")))
// functions declared in main but used elsewhere
unsigned int I_GetTimeMicrosecs(void);

//
#endif
