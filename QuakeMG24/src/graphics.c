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
 *  Interrupt assisted DMA-based display update engine, with double buffering 
 *  256-color functions to print general purpose texts.
 *  
 */
#include "quakedef.h"
#include "graphics.h"
#include "font8x8.h"
#include "printf.h"
#include <string.h>
#include "em_ldma.h"
#include "em_gpio.h"
#include "delay.h"
//
static uint8_t *getLine(int y);
#define  DISPLAY_LDMA_CTRL_REG_VALUE        LDMA_CH_CTRL_DSTMODE_ABSOLUTE |                                                           \
                                            LDMA_CH_CTRL_SRCMODE_ABSOLUTE |                                                           \
                                            LDMA_CH_CTRL_SRCINC_ONE |                                                                 \
                                            LDMA_CH_CTRL_SIZE_HALFWORD |                                                              \
                                            LDMA_CH_CTRL_DSTINC_NONE |                                                                \
                                            LDMA_CH_CTRL_IGNORESREQ |                                                                 \
                                            LDMA_CH_CTRL_REQMODE_BLOCK |                                                              \
                                            LDMA_CH_CTRL_BLOCKSIZE_UNIT1 |                                                            \
                                            ((sizeof(displayData.displayDmaLineBuffer[0]) / 2 - 1) <<_LDMA_CH_CTRL_XFERCNT_SHIFT) |   \
                                            LDMA_CH_CTRL_STRUCTTYPE_TRANSFER
//
#define LE2BE16(x) ((uint16_t)(((x >> 8) & 0xFF) | (x << 8)))
#define RGB(r, g, b) (((r >> 3) << (6 + 5)) | ((g >> 2) << 5) | ((b >> 3) << (0)))
//
#define MAX_STRING_SIZE ( SCREEN_WIDTH / FONT_WIDTH + 1)
//
#ifndef XSTR
#define XSTR(s) STR(s)
#define STR(s) #s
#endif
// note! LDR instructions are pipelined!
#define CONVERT_4_PIX(START_PIX)  "LDRB %[pix0], [%[buff], #0 +" XSTR(START_PIX) "]\n\t" \
                                  "LDRB %[pix1], [%[buff], #1 +" XSTR(START_PIX) "]\n\t" \
                                  "LDRB %[pix2], [%[buff], #2 +" XSTR(START_PIX) "]\n\t" \
                                  "LDRB %[pix3], [%[buff], #3 +" XSTR(START_PIX) "]\n\t" \
                                  "LDRH %[pix0], [%[palette], %[pix0], LSL #1]\n\t" \
                                  "LDRH %[pix1], [%[palette], %[pix1], LSL #1]\n\t" \
                                  "LDRH %[pix2], [%[palette], %[pix2], LSL #1]\n\t" \
                                  "LDRH %[pix3], [%[palette], %[pix3], LSL #1]\n\t" \
                                  "ORR %[pix0], %[pix0], %[pix1], LSL #16\n\t" \
                                  "STR.w %[pix0], [%[dmabuff], #0 + " XSTR(2 * START_PIX) "]\n\t" \
                                  "ORR %[pix2], %[pix2], %[pix3], LSL #16\n\t" \
                                  "STR.w %[pix2], [%[dmabuff], #4 + " XSTR(2 * START_PIX) "]\n\t"

static inline void fillNextDmaLineBuffer();
//
const uint16_t palette16[] =    // a gift who those who recognize this palette!
{ 
    LE2BE16(RGB(170, 170, 170)),
    LE2BE16(RGB(0, 0, 0)), 
    LE2BE16(RGB(255, 255, 255)),  
    LE2BE16(RGB(86, 119, 170)), 
};
//
typedef enum
{
    dm_4bpp = 4, dm_8bpp = 8
} displayMode_t;
//
displayData_t displayData;//
void initGraphics()
{
    memset(&displayData, 0, sizeof(displayData));
    displayData.pPalette = (uint16_t * ) palette16;
    displayData.displayMode = dm_8bpp;
    displayData.displayDmaLineBuffersSent = NUMBER_OF_DMA_LINES + 1;
    setDisplayPen(1,0);
    // configure DMA
    USART0->CMD = USART_CMD_TXEN;
    LDMA->EN = LDMA_EN_EN;
    LDMAXBAR->CH[DISPLAY_LDMA_CH].REQSEL = ldmaPeripheralSignal_USART0_TXBL;
    LDMA->CH[DISPLAY_LDMA_CH].CFG = (ldmaCfgArbSlotsAs2 << _LDMA_CH_CFG_ARBSLOTS_SHIFT)
                         | (ldmaCfgSrcIncSignPos << _LDMA_CH_CFG_SRCINCSIGN_SHIFT)
                         | (ldmaCfgDstIncSignPos << _LDMA_CH_CFG_DSTINCSIGN_SHIFT);
    LDMA->CH[DISPLAY_LDMA_CH].DST =  (uint32_t) &USART0->TXDOUBLE;
    //LDMA->CH[DISPLAY_LDMA_CH].SRC =  (uint32_t) displayData.displayDmaLineBuffer[displayData.currentDisplayDmaLineBuffer];
    LDMA->CH[DISPLAY_LDMA_CH].LINK = 0;
    LDMA->CH[DISPLAY_LDMA_CH].LOOP = 0;
    LDMA->IEN_SET = (1 << DISPLAY_LDMA_CH);
    LDMA->DBGHALT_SET = (1 << DISPLAY_LDMA_CH);
    NVIC_SetPriority(LDMA_IRQn, 6);
    NVIC_EnableIRQ(LDMA_IRQn);
    memset(displayData.displayFrameBuffer[0], 0, sizeof(displayData.displayFrameBuffer[0]));

}
#if 1


//
//
static uint8_t penColor = 1;
static uint8_t penBackground = 0;
static uint8_t line = 0;
//
void setDisplayMode(displayMode_t dm)
{
    displayData.displayMode = dm;
}
void setPixel(unsigned int x, unsigned int y, int c)
{
    if (x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
    {
        return;
    }
    switch (displayData.displayMode)
    {
        case dm_8bpp:
            getLine(y)[x] = c;
            break;
    }
}
void displayPutChar(char c, int x, int y)
{
    for (int cy = 0; cy < FONT_HEIGHT; cy++)
    {
        uint8_t fb = font8x8_basic[0x7F & c][cy];
        for (int cx = 0; cx < FONT_WIDTH; cx++)
        {
            setPixel(x + cx, y + cy, (fb & 1) ? penColor : penBackground);
            fb >>= 1;
        }
    }
}
void setDisplayPen(int color, int background)
{
    penColor = color;
    penBackground = background;
}
void displayVPrintf(int x, int y, const char *format, va_list va)
{
    char outString[MAX_STRING_SIZE];
    vsnprintf(outString, MAX_STRING_SIZE, format, va);
    for (int i = 0;
            i < MAX_STRING_SIZE && x < SCREEN_WIDTH && outString[i] <= 0x7F && outString[i] > 0;
            i++)
    {
        displayPutChar(outString[i], x, y);
        x += FONT_WIDTH;
    }
}
void displayPrintf(int x, int y, const char *format, ...)
{
    va_list va;
    va_start(va, format);
    displayVPrintf(x, y, format, va);
    va_end(va);
}


void displayPrintln(bool update, const char *format, ...)
{
    int y;
    // check if we have space to print.
    //
    if (line < SCREEN_HEIGHT / FONT_HEIGHT)
    {
        y = line * FONT_HEIGHT;
        line++;
    }
    else
    {
        y = SCREEN_HEIGHT - FONT_HEIGHT;
#if FULL_FRAMEBUFFER
        uint32_t *d, *s;

        // printing at the bottom of the screen. move everything up.
        d = (uint32_t*) displayData.displayFrameBuffer[displayData.workingBuffer];
        s = (uint32_t*) (&displayData.displayFrameBuffer[displayData.workingBuffer][SCREEN_WIDTH * FONT_HEIGHT]);
#if 0        
        for (int i = 0; i < SCREEN_WIDTH * (SCREEN_HEIGHT - FONT_HEIGHT) / 4;  i++)
        {
            *d++ = *s++;
        }
#else  
        memcpy(d, s, SCREEN_WIDTH * (SCREEN_HEIGHT - FONT_HEIGHT));
        d += SCREEN_WIDTH * (SCREEN_HEIGHT - FONT_HEIGHT) / 4;
#endif
        // clear last row
        uint32_t color = penBackground | (penBackground << 8) | (penBackground << 16) | (penBackground << 24);
        for (int i = 0; i < SCREEN_WIDTH * FONT_HEIGHT / 4; i++)
        {
            *d++ = color;
        }
#else
        for (int yy = FONT_HEIGHT; yy < SCREEN_HEIGHT; yy++)
        {
          uint8_t *s = getLine(yy);
          uint8_t *d = getLine(yy - FONT_HEIGHT);
          memcpy(d, s, SCREEN_WIDTH);

        }
#endif
    }
    // printf will not wrap around
    va_list va;
    va_start(va, format);
    displayVPrintf(0, y, format, va);
    va_end(va);
    if (update)
    {
        startDisplayRefresh(displayData.workingBuffer, 1);
        while (displayData.dmaBusy);
    }
}
#if 1
#pragma GCC optimize ("Ofast")  // we need to compile this code to be as fast as possible.
void startDisplayRefresh(uint8_t bufferNumber, int updateAll)
{
    // normal mode
    while (displayData.dmaBusy)
    {
    }
    while (! (USART0->STATUS & USART_STATUS_TXIDLE));  // it seems to me that there is some race condition if we are calling too frequently this function.
    //
    //
    if (displayData.updateAll != updateAll)
    {
      DISPLAY_NCS_HIGH();
      SET_DISPLAY_DIRECT_MODE();
      //
      displayData.updateAll = updateAll;
      if (displayData.updateAll)
      {
        displaySetNumberOfUpdateLines(200);
      }
      else
      {
        displaySetNumberOfUpdateLines(152);
      }
    }
    SET_DISPLAY_MODE();
    //
    DISPLAY_NCS_LOW();
    displayData.dmaBusy = 1;
    displayData.displayDmaLineBuffersSent = 0;
#if DUAL_BUFFER
    displayData.currentDmaFrameBuffer = displayData.displayFrameBuffer[bufferNumber];
#else
    (void) bufferNumber;
    displayData.currentDmaFrameBuffer = displayData.displayFrameBuffer[0];
#endif
    // fill DMA line buffer, start DMA, fill second DMA line buffer
    displayData.currentDisplayDmaLineBuffer = 0;
    fillNextDmaLineBuffer();
    LDMA->CH[DISPLAY_LDMA_CH].CTRL = DISPLAY_LDMA_CTRL_REG_VALUE;
    LDMA->CH[DISPLAY_LDMA_CH].SRC = (uint32_t) displayData.displayDmaLineBuffer[1 - displayData.currentDisplayDmaLineBuffer];
    // 29/11/2022 BUGFIX: to save 10us, we are filling the next buffer AFTER we start the DMA, because the DMA would still take
    // 256 * 16 / 40000000 s i.e. 102 us.  What happens if, for any reason, the LDMA_IRQ handler is called before fillNextDmaLineBuffer() finishes?
    // The display will receive the first line twice, and the image will be shifted. This CAN happen if, for instance, the BLE ISR is called just after
    // the DMA has been enabled.
    // Disabling LDMA IRQ alone, before enabling it back would be enough, but at this point the BLE ISR could still delay filling of next dma line buffer
    // resulting in slower display frame refresh (should be as fast as possible to make it less noticeable).
    // therefore we completely disable the IRSs
    // 2023-03-18: better to avoid blocking RADIO IRQ, so we simply disable LDMA IRQ
    NVIC_DisableIRQ(LDMA_IRQn);
    LDMA->CHEN_SET = (1 << DISPLAY_LDMA_CH);
    fillNextDmaLineBuffer();
    NVIC_EnableIRQ(LDMA_IRQn);
}
#endif

static uint8_t *getLine(int y)
{
  if (y < DRAW_BUFFER_HEIGHT)
  {
    return &displayData.displayFrameBuffer[0][y * 320];
  }
  else
    return (uint8_t *)aux_buffer + 320 * (y - DRAW_BUFFER_HEIGHT);

}

static inline void fillNextDmaLineBuffer()
{
    uint16_t * pLineBuffer = displayData.displayDmaLineBuffer[displayData.currentDisplayDmaLineBuffer];
    // displayData.pPalette is volatile.
    unsigned int pix0 = pix0, pix1 = pix1, pix2 = pix2, pix3 = pix3;  // self assignment prevents warning
    unsigned int count = 256 / 16;
    __asm volatile
    (
        ".align(4)\n\t"
        "convert8to16bpploop%=:\n\t"
        CONVERT_4_PIX(0)
        CONVERT_4_PIX(4)
        CONVERT_4_PIX(8)
        CONVERT_4_PIX(12)
        "ADD %[dmabuff], #32\n\t"
        "ADD %[buff], #16\n\t"
        "SUBS %[cnt], #1\n\t"
        "BNE convert8to16bpploop%=\n\t"
        :
        [pix0] "+r" (pix0),
        [pix1] "+r" (pix1),
        [pix2] "+r" (pix2),
        [pix3] "+r" (pix3),
        [buff] "+r"  (displayData.currentDmaFrameBuffer),
        [cnt] "+r"  (count),
        [dmabuff] "+r" (pLineBuffer)
        :
        [palette] "r" (displayData.pPalette)
        :
        "cc"
    );
    displayData.displayDmaLineBuffersSent++;
    displayData.currentDisplayDmaLineBuffer = 1 - displayData.currentDisplayDmaLineBuffer;
}
void LDMA_IRQHandler(void)
{
  if (LDMA->IF & (1 << DISPLAY_LDMA_CH))
  {
    LDMA->IF_CLR = (1 << DISPLAY_LDMA_CH);
    int dmaLineNumber = displayData.updateAll ? NUMBER_OF_DMA_LINES : (320 * 152 / 256) ;
    if (displayData.displayDmaLineBuffersSent <= dmaLineNumber)
    {
      LDMA->CHDONE_CLR = (1 << DISPLAY_LDMA_CH);
      LDMA->CH[DISPLAY_LDMA_CH].SRC = (uint32_t) displayData.displayDmaLineBuffer[1 - displayData.currentDisplayDmaLineBuffer];
      LDMA->CH[DISPLAY_LDMA_CH].CTRL = DISPLAY_LDMA_CTRL_REG_VALUE;
      LDMA->CHEN_SET = (1 << DISPLAY_LDMA_CH);
      if (displayData.displayDmaLineBuffersSent <= NUMBER_OF_DMA_LINES - 1)
      {
#if !FULL_FRAMEBUFFER
        if (displayData.currentDmaFrameBuffer == &displayData.displayFrameBuffer[0][SCREEN_WIDTH * DRAW_BUFFER_HEIGHT])
        {
          displayData.currentDmaFrameBuffer = aux_buffer;
          if (!displayData.updateAll)
          {
            // warning this is not correct anyway.
            displayData.displayDmaLineBuffersSent = NUMBER_OF_DMA_LINES + 1;
          }
        }
#endif
          fillNextDmaLineBuffer();
      }
      else
      {
        // we have to do this, to count we have sent another line, but without having to fill one.
        displayData.displayDmaLineBuffersSent++;
      }
    }
    else
    {
      // set complete even in the case we only partially updated.
      displayData.displayDmaLineBuffersSent = NUMBER_OF_DMA_LINES + 1;
      LDMA->CHDONE_CLR = (1 << DISPLAY_LDMA_CH);
      displayData.dmaBusy = 0;
      LDMA->CHDIS_SET = (1 << DISPLAY_LDMA_CH);
    }
  }
}
#endif
