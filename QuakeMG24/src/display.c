/*
 *  This file contains display-specific functions.
 *
 *  Display:
 *  These functions support an ST7789-based SPI display.
 *
 *  Original code: Adafruit tft library?
 *
 *  Modified by Nicola Wrachien (next-hack in the comments) 2018-2024
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

#include "display.h"
#include "ST77XX_registers.h"
#include "delay.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "sharedUsart.h"
#define ST7789_HEIGHT     240
#if DISPLAY_INVERT_XY
#define MADCTL_CONFIG (ST77XX_MADCTL_MV | ST77XX_MADCTL_MY)
#else
#define MADCTL_CONFIG (0x0)
#endif
#define nop() __asm__ volatile("nop");
#define CMD_ARGS_HAVE_DELAY ST_CMD_DELAY
#define END_COMMAND_LIST 0xFF
void initDisplaySpi()
{
  USART0->EN =  USART_EN_EN;
  USART0->CMD = USART_CMD_TXDIS | USART_CMD_RXDIS | USART_CMD_CLEARTX | USART_CMD_CLEARRX;
#if DISPLAY_USES_RESET_INSTEAD_OF_NCS
        USART0->CTRL = USART_CTRL_MSBF_ENABLE | USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH | USART_CTRL_SYNC_ENABLE;
#else
        USART0->CTRL = USART_CTRL_MSBF_ENABLE /*| USART_CTRL_CLKPHA_SAMPLETRAILING | USART_CTRL_CLKPOL_IDLEHIGH */ | USART_CTRL_SYNC_ENABLE  | USART_CTRL_SMSDELAY;;
#endif
  USART0->FRAME = USART_FRAME_DATABITS_EIGHT;
  USART0->CMD = USART_CMD_MASTEREN | USART_CMD_TXEN;
  USART0->CLKDIV = 0;     // 40 MHz, Overclock!
  //
  GPIO->USARTROUTE[0].TXROUTE = ((uint32_t) DISPLAY_MOSI_PORT << _GPIO_USART_TXROUTE_PORT_SHIFT) | (DISPLAY_MOSI_PIN << _GPIO_USART_TXROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].CLKROUTE = ((uint32_t) DISPLAY_SCK_PORT << _GPIO_USART_CLKROUTE_PORT_SHIFT) | (DISPLAY_SCK_PIN << _GPIO_USART_CLKROUTE_PIN_SHIFT);
  GPIO->USARTROUTE[0].ROUTEEN = GPIO_USART_ROUTEEN_TXPEN | GPIO_USART_ROUTEEN_CLKPEN;
}
void displaySpiWrite(volatile uint8_t byte)
{
    USART0->CMD_SET = USART_CMD_TXEN | USART_CMD_RXDIS;
    while (!(USART0->STATUS & USART_STATUS_TXBL) || !(USART0->STATUS & USART_STATUS_TXENS));
    USART0->TXDATA = byte;
    while (!(USART0->STATUS & USART_STATUS_TXC));
    USART0->CMD_SET = USART_CMD_TXDIS | USART_CMD_CLEARRX | USART_CMD_RXDIS;
}
void displayWriteCommand(uint8_t value)
{
    DISPLAY_DC_LOW();
    DISPLAY_NCS_LOW();
    displaySpiWrite(value);
    DISPLAY_NCS_HIGH();
}
void displayWriteData(uint8_t value)
{
    DISPLAY_DC_HIGH();
    DISPLAY_NCS_LOW();
    displaySpiWrite(value);
    DISPLAY_NCS_HIGH();
}

void initDisplayGPIO(void)
{



    GPIO_PinModeSet(DISPLAY_DC_PORT, DISPLAY_DC_PIN, gpioModePushPull, 1);

#if DISPLAY_USES_RESET_INSTEAD_OF_NCS
    GPIO_PinModeSet(DISPLAY_RES_PORT, DISPLAY_RES_PIN, gpioModePushPull, 1);
#else
    GPIO_PinModeSet(DISPLAY_NCS_PORT, DISPLAY_NCS_PIN, gpioModePushPull, 1);
#endif
    GPIO_PinModeSet(DISPLAY_MOSI_PORT, DISPLAY_MOSI_PIN, gpioModePushPullAlternate, 1);
    GPIO_PinModeSet(DISPLAY_SCK_PORT, DISPLAY_SCK_PIN, gpioModePushPullAlternate, 1);
    //


    for (int i = gpioPortA; i <= gpioPortD; i++)
    {
      GPIO_SlewrateSet(i, 1, 7);
    }
    //
    DISPLAY_NCS_HIGH();
    DISPLAY_DC_HIGH();
#ifdef DISPLAY_USES_RESET_INSTEAD_OF_NCS
    DISPLAY_RES_HIGH();
    delay(50);
    DISPLAY_RES_LOW();
    delay(50);
    DISPLAY_RES_HIGH();
    delay(50);
#endif
}

static void executeDisplayCommands(const uint8_t * cmds)
{
    // Executes a list of commands for the display.
    /* cmds array has the following structure:
     *  number of commands
     *  Command Code, number of data bytes, data bytes (if any), delay in ms (if number of bytes is in OR with 0x80)
     *  ...
     */

    uint8_t ms, numArgs;
    //
    // Send initialization commands
    while (*cmds != END_COMMAND_LIST)  // For each command...
    {
        displayWriteCommand(*cmds++);       // Read, issue command
        numArgs = *cmds++;                  // Number of args to follow
        ms = numArgs & CMD_ARGS_HAVE_DELAY; // If hibit set, delay follows args
        numArgs &= ~CMD_ARGS_HAVE_DELAY;    // Mask out delay bit
        while (numArgs--)                   // For each argument...
        {
            displayWriteData(*cmds++); // Read, issue argument
        }

        if (ms)
        {
            ms = *cmds++; // Read post-command delay time (ms)
            delay((ms == 255 ? 500 : ms));
        }
    }
}
void displaySetNumberOfUpdateLines(uint8_t num)
{
  uint8_t set_display_draw_window[] =
  {
      ST77XX_RASET,
      4,
      0,
      CENTER_SCREEN ? (ST7789_HEIGHT - SCREEN_HEIGHT) / 2 : 0,
      0,
      num - 1 + (CENTER_SCREEN ? (ST7789_HEIGHT - SCREEN_HEIGHT) / 2 : 0),
      ST77XX_RAMWR,
      0,
      END_COMMAND_LIST
  };
  executeDisplayCommands(set_display_draw_window);
  DISPLAY_DC_HIGH();
  DISPLAY_NCS_LOW();

}
void displayInit(void)
{
    // Display initialization.
    // Note: this function DOES NOT initialize the SPI.
    // It just initializes the I/O ports for D/C and nCS and sends the initialization commands to the display
    /* The following array has the following structure:
     *  number of commands
     *  Command Code, number of data bytes, data bytes (if any), delay in ms (if number of bytes is in OR with 0x80)
     *  ...
     */
    const uint8_t generic_st7789[] =
    {    // Init commands for 7789 screens
        ST77XX_SWRESET,
        ST_CMD_DELAY, //  1: Software reset, no args, w/delay
        150,          //     ~150 ms delay
        ST77XX_SLPOUT,
        ST_CMD_DELAY, //  2: Out of sleep mode, no args, w/delay
        10,           //      10 ms delay
        ST77XX_COLMOD,
        1 + ST_CMD_DELAY, //  3: Set color mode, 1 arg + delay:
        0x55,             //     16-bit color
        10,               //     10 ms delay
        ST77XX_MADCTL,
        1,             //  4: Mem access ctrl (directions), 1 arg:
        MADCTL_CONFIG, //     Row/col addr, bottom-top refresh
#if GAMMA_CORRECTION
        ST7789_GCTRL,
        1 + ST_CMD_DELAY,
        0x35,
        10, // reset value
        ST7789_VCOMS,
        1 + ST_CMD_DELAY,
        0x20,
        10, 
        ST7789_VDVVRHEN,
        2 + ST_CMD_DELAY,
        0x01,
        0xFF,
        10,
        ST7789_VRHS,
        1 + ST_CMD_DELAY,
        0x0b,
        10, // voltage VRHS
        ST7789_VDVSET,
        1 + ST_CMD_DELAY,
        0x20,
        10, // def value
        ST7789_FRCTR2,
        1 + ST_CMD_DELAY,
        0x0f,
        10,
        ST7789_PWCTRL1,
        2 + ST_CMD_DELAY,
        0xa4,
        0xa1,
        10,
        ST7789_PVGAMCTRL,
        ST_CMD_DELAY + 14,
        GAMMA_SETTINGS,
        10, // 10 ms delay
        ST7789_NVGAMCTRL,
        ST_CMD_DELAY + 14,
        GAMMA_SETTINGS,
        10, //    10 ms delay
#endif
        ST77XX_INVON,
        ST_CMD_DELAY, //  7: hack
        10,
        ST77XX_NORON,
        ST_CMD_DELAY, //  8: Normal display on, no args, w/delay
        10,           //     10 ms delay
        ST77XX_DISPON,
        ST_CMD_DELAY, //  9: Main screen turn on, no args, delay
        10,
        ST77XX_GAMSET,
        1 + ST_CMD_DELAY,
        1,  // gamma
        10, // 10 ms delay
#if DISPLAY_INVERT_XY
        ST77XX_CASET,
        4,
        0,
        320 - SCREEN_WIDTH,
        (320 - 1) >> 8,
        (319 & 0xFF),
#else
        ST77XX_CASET,
        4,
        0,
        0,
        0,
        SCREEN_WIDTH - 1,
#endif
        ST77XX_RASET,
        4,
        0,
        0,
        0,
        ST7789_HEIGHT - 1,
        ST77XX_RAMWR,
        0,

        END_COMMAND_LIST
    };

    initDisplayGPIO();

    initDisplaySpi();

    executeDisplayCommands(generic_st7789);
    DISPLAY_DC_HIGH();
    delay(1);
    DISPLAY_NCS_LOW();
    // clear display area
    for (int i = 0; i < SCREEN_WIDTH * 240 * 2; i++)
    {
        displaySpiWrite(0);
    }
    // now set correct position.  Center if required
    const uint8_t set_display_draw_window[] =
    {
        ST77XX_RASET,
        4,
        0,
        CENTER_SCREEN ? (ST7789_HEIGHT - SCREEN_HEIGHT) / 2 : 0,
        0,
        SCREEN_HEIGHT - 1 + (CENTER_SCREEN ? (ST7789_HEIGHT - SCREEN_HEIGHT) / 2 : 0),
        ST77XX_RAMWR,
        0,
        END_COMMAND_LIST
    };
    executeDisplayCommands(set_display_draw_window);
    DISPLAY_DC_HIGH();
    delay(1);
    DISPLAY_NCS_LOW();
    delay(1);
}
