/*
 *  This file contains display-specific functions.
 *
 *  Display:
 *  These functions support an ST7789-based SPI display.
 *
 *  Original code: Adafruit tft library?
 *
 *  Modified by Nicola Wrachien (next-hack in the comments) 2018-2023
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef DISPLAYH
#define DISPLAYH

#ifdef __cplusplus
extern "C"
{
#endif
#include "boards.h"
#include <stdint.h>
// Useful display macros
#define DISPLAY_DC_HIGH()     GPIO->P_SET[DISPLAY_DC_PORT].DOUT = (1 << DISPLAY_DC_PIN)
#define DISPLAY_DC_LOW()      GPIO->P_CLR[DISPLAY_DC_PORT].DOUT = (1 << DISPLAY_DC_PIN)
// for those stupid boards that does not route out NCS...
#if DISPLAY_USES_RESET_INSTEAD_OF_NCS
    // chip select always low, if defined
    #ifdef DISPLAY_NCS_PIN
        #define DISPLAY_NCS_LOW() GPIO->P_CLR[DISPLAY_NCS_PORT].DOUT = (1 << DISPLAY_NCS_PIN)
    #else
        #define DISPLAY_NCS_LOW()
    #endif
    #define DISPLAY_NCS_HIGH() DISPLAY_NCS_LOW()
    #define DISPLAY_RES_HIGH()    GPIO->P_SET[DISPLAY_RES_PORT].DOUT = (1 << DISPLAY_RES_PIN)
    #define DISPLAY_RES_LOW()     GPIO->P_CLR[DISPLAY_RES_PORT].DOUT = (1 << DISPLAY_RES_PIN)
#else
  #define DISPLAY_RES_HIGH()
  #define DISPLAY_RES_LOW()
  #define DISPLAY_NCS_HIGH() GPIO->P_SET[DISPLAY_NCS_PORT].DOUT = (1 << DISPLAY_NCS_PIN)
  #define DISPLAY_NCS_LOW() GPIO->P_CLR[DISPLAY_NCS_PORT].DOUT = (1 << DISPLAY_NCS_PIN)
#endif
#define MAXROWS (SCREEN_HEIGHT / 8)
#define MAXCOLS (SCREEN_WIDTH / 8)
//
  void UpdateDisplay(void);
void displayInit(void);
void EndUpdateDisplay(void);
void SelectDisplay(void);
void displayWriteData(uint8_t value);
void initDisplaySpi();
void displaySetNumberOfUpdateLines(uint8_t num);
#ifdef __cplusplus
}
#endif
#endif

