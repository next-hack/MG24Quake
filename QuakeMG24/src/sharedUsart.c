/***************************************************************************//**
 * @file sharedUsart.c
 * @brief Shared USART for display and console
 *
 * @Note: this file should be rendered hardware independent.
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
**/

// We only have 2 EUSART, and one USART. The USART is required for YMODEM operation
// therefore we are going to share with the display.
// During normal printout, the SWO is usedi instead
// The USART shall be used for asynchronous I/O
#include "em_usart.h"
#include "em_gpio.h"
#include "em_prs.h"
#include <stdint.h>
#include "sharedUsart.h"
#include "main.h"
#include "extMemory.h"
#include "em_ldma.h"
#include "printf.h"
#include "boards.h"
#include "graphics.h"
#pragma GCC optimize ("Os")
#define DEBUG_BLE ENABLE_BLE_DEBUG
#if USE_BUFFERED_USART
static uint8_t vcomOutputMode = VCOM_OUTPUT_SHARED_USART;
#define MAX_UART_BUFFER         512
typedef struct
{
    uint8_t buffer[MAX_UART_BUFFER];
    uint32_t writeIndex;
    uint32_t readIndex;
    uint32_t count;
} uart_buffer_t;
uart_buffer_t uartBuffer = {0};
void bufferedPutchar(char c)
{
  if (uartBuffer.count < MAX_UART_BUFFER)
  {
    // increment count
    uartBuffer.count++;
    // store data
    uartBuffer.buffer[uartBuffer.writeIndex] = c;
    // increment and wrap write index.
    uartBuffer.writeIndex++;
    if (uartBuffer.writeIndex >=MAX_UART_BUFFER)
    {
      uartBuffer.writeIndex = 0;
    }
  }
}

int bufferedGetchar(void)
{
  int c =  -1;
  if (uartBuffer.count)
  {
    // decrement count
    uartBuffer.count--;
    // store data
    c = uartBuffer.buffer[uartBuffer.readIndex];
    // increment and wrap write index.
    uartBuffer.readIndex++;
    if (uartBuffer.readIndex >=MAX_UART_BUFFER)
    {
      uartBuffer.readIndex = 0;
    }
  }
  return c;
}
#endif

void sharedUsartModeSet(void * interface, sharedUsartMode_t mode)
{
#if SHARED_USART_INTERFACE == SHARED_EUSART0
    static uint8_t eusart0Mode = SHARED_UART_MODE_NONE;
#elif SHARED_USART_INTERFACE == SHARED_EUSART1
  static uint8_t eusart1Mode = SHARED_UART_MODE_NONE;
#endif
  static uint8_t usart0Mode = SHARED_UART_MODE_NONE;

  if (interleavedSpiData.directMode)
  {
#if SHARED_USART_INTERFACE == SHARED_EUSART0
     eusart0Mode = SHARED_UART_MODE_NONE;
#elif SHARED_USART_INTERFACE == SHARED_EUSART1
     eusart1Mode = SHARED_UART_MODE_NONE;
#elif SHARED_USART_INTERFACE == SHARED_USART0
    usart0Mode = SHARED_UART_MODE_NONE;
#endif
    interleavedSpiData.directMode = 0;
  }
#if SHARED_USART_INTERFACE == SHARED_USART0
  // enable usart
  USART0->EN =  USART_EN_EN;
  //can't change during dma
  while ((displayData.dmaBusy));
  // wait for transmission finished
  while (! (USART0->STATUS & USART_STATUS_TXIDLE));
  if (mode == SHARED_USART_MODE_DEVICE)
  {
    USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
    USART0->CTRL = USART_CTRL_MSBF_ENABLE | USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_SYNC_ENABLE;
    USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
    USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN;
    USART0->CLKDIV = 0;     // 40 MHz
    //
    GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
  }
  else
  {
    USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_MASTERDIS |  USART_CMD_CLEARRX;
    USART0->CTRL = USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH;
    USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
    USART0->CMD = USART_CMD_RXEN | USART_CMD_TXEN;
    USART0->CLKDIV =  (256 / UART_OVERSAMPLE  * FPCLK/ UART_BAUDRATE - 1);     //
    //
    GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) VCOM_TX_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (VCOM_TX_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].RXROUTE = ((uint32_t) VCOM_RX_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) | (VCOM_RX_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
    GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_RXPEN;
    //
  }
#elif SHARED_USART_INTERFACE == SHARED_EUSART0
  if (interface == EUSART0)
  {
    if (mode != eusart0Mode)
    {
      //can't change during dma
      while ((LDMA->CHBUSY & (1 << (FIRST_SPI_LDMA_CH))));
      // wait for transmission finished.
      while ((EUSART0->EN & EUSART_EN_EN) && ! (EUSART0->STATUS & EUSART_STATUS_TXIDLE));
      // Disable EUSART
      EUSART0->EN_CLR = EUSART_EN_EN;
      // wait till disabled
      while (EUSART0->EN & EUSART_EN_DISABLING);
      if (mode == SHARED_USART_MODE_DEVICE)
      {
        EUSART0->CLKDIV = 0;
        EUSART0->CFG1 = EUSART_SPI_WATERMARK;
        EUSART0->CFG2 = _EUSART_CFG2_MASTER_MASK | (HIGH_SPEED_EUSART_DIVISOR << 24);
        EUSART0->FRAMECFG = eusartDataBits8; // will be 16 for dual SPI
        EUSART0->CFG0 = _EUSART_CFG0_SYNC_SYNC | _EUSART_CFG0_MSBF_MASK;
        // Configure frame format
        // Finally enable the Rx and/or Tx channel (as specified).
        EUSART0->EN = 1;
        while (EUSART0->SYNCBUSY & (_EUSART_SYNCBUSY_RXEN_MASK | _EUSART_SYNCBUSY_TXEN_MASK)); // Wait for low frequency register synchronization.
        EUSART0->CMD = EUSART_CMD_TXDIS |  EUSART_CMD_CLEARTX | EUSART_CMD_RXDIS;
        while (EUSART0->SYNCBUSY & (_EUSART_SYNCBUSY_RXEN_MASK | _EUSART_SYNCBUSY_TXEN_MASK));
        while (~EUSART0->STATUS & (_EUSART_STATUS_RXIDLE_MASK | _EUSART_STATUS_TXIDLE_MASK));
        while (EUSART0->SYNCBUSY);
        //
#if EXT_MEM_USES_EUSART0
        extMemRestoreInterface();
#endif
        EUSART0->TRIGCTRL = EUSART_TRIGCTRL_TXTEN | EUSART_TRIGCTRL_AUTOTXTEN | EUSART_TRIGCTRL_RXTEN;
        interleavedSpiData.directMode = 0;
      }
      else if (mode == SHARED_USART_MODE_VCOM)
      {
        // VCOM MODE
        // Disable DMA
        LDMA->CHDIS = (15 << FIRST_SPI_LDMA_CH);
        EUSART_UartInit_TypeDef init =  EUSART_UART_INIT_DEFAULT_HF;
        init.enable = eusartDisable;
        EUSART_UartInitHf(EUSART0, &init);
        EUSART0->CFG1 = EUSART_COM_WATERMARK;
        EUSART_Enable(EUSART0, eusartEnable);
        //
        EUSART_BaudrateSet(EUSART0, FPCLK / 2, UART_BAUDRATE / 2); // the /2 is to prevent overflow in overclock mode!
        //
        GPIO->EUSARTROUTE[0].TXROUTE = ((uint32_t) VCOM_TX_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT) | (VCOM_TX_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
        GPIO->EUSARTROUTE[0].RXROUTE = ((uint32_t) VCOM_RX_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT) | (VCOM_RX_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
        GPIO->EUSARTROUTE[0].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN;
        //
      }
      else
      { // error
        while(1);
      }
    }
    eusart0Mode = mode;
  }
  else if (interface == USART0)
  {
    if (mode != usart0Mode)
    {
      //can't change during dma
      while ((displayData.dmaBusy));
      while ((LDMA->CHBUSY & (1 << (DISPLAY_LDMA_CH))));
      // enable usart
      if (USART0->EN == 0)
      {
        USART0->EN =  USART_EN_EN;
      }
      else
      {
        // wait for transmission finished
        while (! (USART0->STATUS & USART_STATUS_TXC));
      }
      if (mode == SHARED_USART_MODE_DEVICE)
      {
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
#if DISPLAY_USES_RESET_INSTEAD_OF_NCS
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_SYNC_ENABLE;
#else
        USART0->CTRL = USART_CTRL_MSBF_ENABLE /*| USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH */ | USART_CTRL_SYNC_ENABLE  | USART_CTRL_SMSDELAY;;
#endif
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN;
        USART0->CLKDIV = 0;     // 40 MHz
        //
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
      }
      else if (mode == SHARED_USART_MODE_SD_FAST || mode == SHARED_USART_MODE_SD_SLOW)
      {

        DISPLAY_NCS_HIGH();
        // disable DMA
        LDMA->CHDIS_SET = (1 << DISPLAY_LDMA_CH);
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | /*USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH |*/ USART_CTRL_SYNC_ENABLE | USART_CTRL_SMSDELAY;
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN; // enable also RX
        if (mode == SHARED_USART_MODE_SD_FAST)
        {
          USART0->CLKDIV = 256 * (40000 / (2 * 10000) - 1);     // 10 MHz
        }
        else
        {
          USART0->CLKDIV = 256 * (40000 / (2 * 100) - 1);     // 100 kHz
        }
        // enable also RX pin
        GPIO->USARTROUTE[0].RXROUTE = ((uint32_t) SD_MISO_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) | (SD_MISO_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_RXPEN;
      }
      else if (mode == SHARED_USART_DISPLAY_DIRECT_MODE)
      {
        //can't change during dma
        while ((displayData.dmaBusy));
        while ((LDMA->CHBUSY & (1 << (DISPLAY_LDMA_CH))));
        //
        if (USART0->EN == 0)
        {
          // wait for pending transmission finished
          while (! (USART0->STATUS & USART_STATUS_TXIDLE));
        }
        //
        // disable DMA
        LDMA->CHDIS_SET = (1 << DISPLAY_LDMA_CH);
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | /*USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH |*/ USART_CTRL_SYNC_ENABLE | USART_CTRL_SMSDELAY;
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN; // enable also RX
#if OVERCLOCK
        USART0->CLKDIV =  256 * (40000 / (2 * 10000) - 1);  ;     //
#else
        USART0->CLKDIV = 0;     //
#endif
        //
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
      }
      usart0Mode = mode;
    }
  }
#elif SHARED_USART_INTERFACE == SHARED_EUSART1
  if (interface == EUSART1)
  {
    if (mode != eusart1Mode)
    {
      //can't change during dma
      while ((LDMA->CHBUSY & (1 << (SECOND_SPI_LDMA_CH))));
      // wait for transmission finished.
      while ((EUSART1->EN & EUSART_EN_EN) && ! (EUSART1->STATUS & EUSART_STATUS_TXIDLE));
      // Disable EUSART
      EUSART1->EN_CLR = EUSART_EN_EN;
      // wait till disabled
      while (EUSART1->EN & EUSART_EN_DISABLING);
      if (mode == SHARED_USART_MODE_DEVICE)
      {
        EUSART1->CLKDIV = 0;
        EUSART1->CFG1 = EUSART_SPI_WATERMARK;
        EUSART1->CFG2 = _EUSART_CFG2_MASTER_MASK | (HIGH_SPEED_EUSART_DIVISOR << 24);
        EUSART1->FRAMECFG = eusartDataBits8; // will be 16 for dual SPI
        EUSART1->CFG0 = _EUSART_CFG0_SYNC_SYNC | _EUSART_CFG0_MSBF_MASK;
        // Configure frame format
        // Finally enable the Rx and/or Tx channel (as specified).
        EUSART1->EN = 1;
        while (EUSART1->SYNCBUSY & (_EUSART_SYNCBUSY_RXEN_MASK | _EUSART_SYNCBUSY_TXEN_MASK)); // Wait for low frequency register synchronization.
        EUSART1->CMD = EUSART_CMD_TXDIS |  EUSART_CMD_CLEARTX | EUSART_CMD_RXDIS;
        while (EUSART1->SYNCBUSY & (_EUSART_SYNCBUSY_RXEN_MASK | _EUSART_SYNCBUSY_TXEN_MASK));
        while (~EUSART1->STATUS & (_EUSART_STATUS_RXIDLE_MASK | _EUSART_STATUS_TXIDLE_MASK));
        while (EUSART1->SYNCBUSY);
        //
#if EXT_MEM_USES_EUSART1
        extMemRestoreInterface();
#endif
        EUSART1->TRIGCTRL = EUSART_TRIGCTRL_TXTEN | EUSART_TRIGCTRL_AUTOTXTEN | EUSART_TRIGCTRL_RXTEN;
        interleavedSpiData.directMode = 0;
      }
      else if (mode == SHARED_USART_MODE_VCOM)
      {
        // VCOM MODE
        // Disable DMA
        LDMA->CHDIS = (15 << FIRST_SPI_LDMA_CH);
        EUSART_UartInit_TypeDef init =  EUSART_UART_INIT_DEFAULT_HF;
        init.enable = eusartDisable;
        EUSART_UartInitHf(EUSART1, &init);
        EUSART1->CFG1 = EUSART_COM_WATERMARK;
        EUSART_Enable(EUSART1, eusartEnable);
        //
        EUSART_BaudrateSet(EUSART1, FPCLK / 2, UART_BAUDRATE / 2); // the /2 is to prevent overflow in overclock mode!
        //
        GPIO->EUSARTROUTE[1].TXROUTE = ((uint32_t) VCOM_TX_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT) | (VCOM_TX_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
        GPIO->EUSARTROUTE[1].RXROUTE = ((uint32_t) VCOM_RX_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT) | (VCOM_RX_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
        GPIO->EUSARTROUTE[1].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN;
        //
      }
      else
      { // error
        while(1);
      }
    }
    eusart1Mode = mode;
  }
  else if (interface == USART0)
  {
    if (mode != usart0Mode)
    {
      //can't change during dma
      while ((displayData.dmaBusy));
      while ((LDMA->CHBUSY & (1 << (DISPLAY_LDMA_CH))));
      // enable usart
      if (USART0->EN == 0)
      {
        USART0->EN =  USART_EN_EN;
      }
      else
      {
        // wait for transmission finished
        while (! (USART0->STATUS & USART_STATUS_TXC));
      }
      if (mode == SHARED_USART_MODE_DEVICE)
      {
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
#if DISPLAY_USES_RESET_INSTEAD_OF_NCS
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_SYNC_ENABLE;
#else
        USART0->CTRL = USART_CTRL_MSBF_ENABLE /*| USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH */ | USART_CTRL_SYNC_ENABLE  | USART_CTRL_SMSDELAY;;
#endif
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN;
        USART0->CLKDIV = 0;     // 40 MHz
        //
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
      }
      else if (mode == SHARED_USART_MODE_SD_FAST || mode == SHARED_USART_MODE_SD_SLOW)
      {

        DISPLAY_NCS_HIGH();
        // disable DMA
        LDMA->CHDIS_SET = (1 << DISPLAY_LDMA_CH);
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | /*USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH |*/ USART_CTRL_SYNC_ENABLE | USART_CTRL_SMSDELAY;
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN; // enable also RX
        if (mode == SHARED_USART_MODE_SD_FAST)
        {
          USART0->CLKDIV = 256 * (40000 / (2 * 10000) - 1);     // 10 MHz
        }
        else
        {
          USART0->CLKDIV = 256 * (40000 / (2 * 100) - 1);     // 100 kHz
        }
        // enable also RX pin
        GPIO->USARTROUTE[0].RXROUTE = ((uint32_t) SD_MISO_PORT << _GPIO_USART_RXROUTE_PORT_SHIFT) | (SD_MISO_PIN << _GPIO_USART_RXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN | GPIO_USART_ROUTEEN_RXPEN;
      }
      else if (mode == SHARED_USART_DISPLAY_DIRECT_MODE)
      {
        //can't change during dma
        while ((displayData.dmaBusy));
        while ((LDMA->CHBUSY & (1 << (DISPLAY_LDMA_CH))));
        //
        if (USART0->EN == 0)
        {
          // wait for pending transmission finished
          while (! (USART0->STATUS & USART_STATUS_TXIDLE));
        }
        //
        // disable DMA
        LDMA->CHDIS_SET = (1 << DISPLAY_LDMA_CH);
        USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | /*USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH |*/ USART_CTRL_SYNC_ENABLE | USART_CTRL_SMSDELAY;
        USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
        USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN | USART_CMD_RXEN; // enable also RX
#if OVERCLOCK
        USART0->CLKDIV =  256 * (40000 / (2 * 10000) - 1);  ;     //
#else
        USART0->CLKDIV = 0;     //
#endif
        //
        GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
        GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
      }
      usart0Mode = mode;
    }
  }
#else
#error no valid SHARED_USART_INTERFACE configured in main.h
#endif
}
int usart_putchar(int c)
{
#if SHARED_USART_INTERFACE == SHARED_USART0
  while (!(USART0->STATUS & USART_STATUS_TXBL) || !(USART0->STATUS & USART_STATUS_TXENS));
  USART0->TXDATA = c;
  while (!(USART0->STATUS & USART_STATUS_TXC));
#elif SHARED_USART_INTERFACE == SHARED_EUSART0
  while (!(EUSART0->STATUS & EUSART_STATUS_TXIDLE) || !(EUSART0->STATUS & EUSART_STATUS_TXENS));
  EUSART0->TXDATA = c;
  while (!(EUSART0->STATUS & USART_STATUS_TXC));
#elif SHARED_USART_INTERFACE == SHARED_EUSART1
  while (!(EUSART1->STATUS & EUSART_STATUS_TXIDLE) || !(EUSART1->STATUS & EUSART_STATUS_TXENS));
  EUSART1->TXDATA = c;
  while (!(EUSART1->STATUS & USART_STATUS_TXC));
#else
#error NOT IMPLEMENTED
#endif
  return c;
}
void _putchar(char c)
{
#if USE_BUFFERED_USART

  if (VCOM_OUTPUT_SHARED_USART== vcomOutputMode)
  {
    usart_putchar(c);
  }
  else
  {
//    swoPutchar(c);
    bufferedPutchar(c);
  }
#else
  usart_putchar(c);
#endif
}
#if USE_BUFFERED_USART
void printBufferedData(void)
{
  sharedUsartModeSet(SHARED_USART_MODE_VCOM);
  int c;
  while ((c = bufferedGetchar()) != -1)
  {
    usart_putchar(c);
  }
  sharedUsartModeSet(SHARED_USART_MODE_DEVICE);
}
#endif

int sharedUsartPrintf(const char * format, ...)
{
  // config and share USART/EUSART for asynch op
  sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_VCOM);
  va_list va;
  va_start(va, format);
  const int ret = vprintf_(format, va);
  va_end(va);
  // configure back to its normal usage.
  sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_DEVICE);
  return ret;
}
int sharedUsartVPrintf(const char* format, va_list va)
{
  sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_VCOM);
  int ret = vprintf_(format, va);
  sharedUsartModeSet(VCOM_USART, SHARED_USART_MODE_DEVICE);
  return ret;
}

