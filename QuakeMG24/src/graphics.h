/**
 *  Display utility functions for Quake Port to EFR32xG24 MCUs.
 *  It also contains the interrupt-assisted DMA update of the display
 *  and double buffer display data structure.
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
 *  Interrupt assisted DMA-based display update engine,
 *  256-color functions to print general purpose texts.
 *
 */
#ifndef SRC_GRAPHICS_H_
#define SRC_GRAPHICS_H_
#include <stdbool.h>
#include <stdint.h>
#include "display.h"
#include "quakedef.h"
#define PIXELS_PER_DMA_LINE         256
#define NUMBER_OF_DMA_LINES         (SCREEN_WIDTH * SCREEN_HEIGHT / 256)

typedef struct
{
    volatile uint16_t * pPalette;
    uint16_t displayDmaLineBuffer[2][PIXELS_PER_DMA_LINE];  // small buffer to speed up DMA send
    uint8_t displayFrameBuffer[1][SCREEN_WIDTH * DRAW_BUFFER_HEIGHT];
    uint8_t * currentDmaFrameBuffer;            // points to data to be converted, using pPalette on the displayDmaBuffer
    volatile uint16_t displayDmaLineBuffersSent; // how many lines we sent
    volatile uint8_t currentDisplayDmaLineBuffer;
    uint8_t workingBuffer;
    uint8_t displayMode;
    volatile uint8_t updateAll;
    volatile uint8_t dmaBusy;
#if NEW_DISPLAY_UPDATE_WAY
    volatile uint8_t doNotDisableShorts;
    volatile uint8_t nextBufferIndex;
#endif
} displayData_t;
extern displayData_t displayData;
void displayPrintf(int x, int y, const char * format, ...);
void startDisplayRefresh(uint8_t bufferNumber, int updateAll);
void setDisplayPen(int color, int background);
void clearScreen4bpp();
void displayPrintln(bool update, const char * format, ...);
void initGraphics();
static inline void waitForDisplayDMA(unsigned int y)
{
  if (y >= SCREEN_HEIGHT)
    return;
  // wait
  while ((y + 1) * 320 >= displayData.displayDmaLineBuffersSent * PIXELS_PER_DMA_LINE );
}

#endif /* SRC_GRAPHICS_H_ */
