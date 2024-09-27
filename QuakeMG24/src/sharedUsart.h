/***************************************************************************//**
 * @file sharedUsart.h
 * @brief 
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
#ifndef SRC_SHAREDUSART_H_
#define SRC_SHAREDUSART_H_
#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include "em_usart.h"
#include "em_eusart.h"
#include <stdarg.h>
#define SHARED_USART0     0
#define SHARED_EUSART0    1
#define SHARED_EUSART1    2
  typedef enum
  {
    SHARED_UART_MODE_NONE = 0,       // not initiialized
    SHARED_USART_MODE_DEVICE = 1,    // primary device
    // alternate modes
    SHARED_USART_MODE_VCOM = 2,
    SHARED_USART_MODE_SD_SLOW = 3,
    SHARED_USART_MODE_SD_FAST = 4,
    SHARED_USART_DISPLAY_DIRECT_MODE = 5,     // when need to update manually the config.

  } sharedUsartMode_t;
  typedef enum
  {
    VCOM_OUTPUT_SHARED_USART = 0,
#if USE_BUFFERED_USART
    VCOM_OUTPUT_SHARED_USART_BUFFERED = 1
#endif
  } vcomOutput_t;
  void sharedUsartModeSet(void * interface, sharedUsartMode_t mode);
  void vcomOutputSet(vcomOutput_t mode);
  void _putchar(char c);
  void printBufferedData(void);
  int sharedUsartPrintf(const char * format, ...);
  int sharedUsartVPrintf(const char* format, va_list va);
  int usart_putchar(int c);
#define USE_SHARED_USART              1
#define SHARED_USART_INTERFACE        SHARED_EUSART1
#if SHARED_USART_INTERFACE == SHARED_EUSART0
    #define VCOM_USART                    EUSART0
#elif SHARED_USART_INTERFACE == SHARED_EUSART1
    #define VCOM_USART                    EUSART1
#else
    #error not supported shared usart.
#endif
#define DISPLAY_USART                 USART0
#define SET_DISPLAY_MODE()            sharedUsartModeSet(DISPLAY_USART, SHARED_USART_MODE_DEVICE)
#define SET_DISPLAY_DIRECT_MODE()     sharedUsartModeSet(DISPLAY_USART, SHARED_USART_DISPLAY_DIRECT_MODE)
#define SET_SD_MODE_FAST()            sharedUsartModeSet(DISPLAY_USART, SHARED_USART_MODE_SD_FAST)
#define SET_SD_MODE_SLOW()            sharedUsartModeSet(DISPLAY_USART, SHARED_USART_MODE_SD_SLOW)
#define SET_SD_MODE(mode)             sharedUsartModeSet(DISPLAY_USART, mode)
#define SET_VCOM_MODE()               sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_VCOM)
#define SET_FLASH_MODE()              sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_DEVICE)
#ifdef __cplusplus
}
#endif
#endif /* SRC_SHAREDUSART_H_ */
