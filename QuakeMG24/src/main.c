/***************************************************************************//**
 * @file main.c
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
// BIG NOTE!!! This project is configured for a 20 dBm part, to support
// the Sparkfun Thing Plus Matter board.
// Unfortunately, this means BLE won't work on 10 dBm parts.
// If you have a 10 dBm part, then you'll have to configure the to a 10 dBm part
// (e.g. MGM240PB22VNA).
// Note: conversely, starting from GSDK 4.3 if you configure for 10 dBm,
// it won't work on a 20 dBm part.
// To configure, double click on DoomMG24BLE.slcp, select Oveview on top of
// the window, then on target and tools settings press "Change Target/SDK/Generators".
// Finally select the correct part number and click save.
// -----------------------------------------------------------------------------
//                                   Includes
// -----------------------------------------------------------------------------
#include "sl_component_catalog.h"

#include "sl_system_init.h"
#if defined(SL_CATALOG_POWER_MANAGER_PRESENT)
  #include "sl_power_manager.h"
#endif
#if defined(SL_CATALOG_KERNEL_PRESENT)
  #include "sl_system_kernel.h"
  #include "app_task_init.h"
#else // SL_CATALOG_KERNEL_PRESENT
  #include "sl_system_process_action.h"
#endif // SL_CATALOG_KERNEL_PRESENT
#include "sl_event_handler.h"
#include "keyboard.h"
#include "delay.h"
#include "sharedUsart.h"
#include "main.h"
#include "z_zone.h"
#include "audio.h"
#include "extMemory.h"
#include "extMemory.h"
#include "em_cmu.h"
#include "boards.h"
#include "graphics.h"
#include "diskio.h"
#include "memory_defs.h"
#include "quakedef.h"
unsigned int I_GetTimeMicrosecs(void);
//#define TEST_YMODEM                           0
#define KEY_COMBINATION_FOR_DATA_UPLOAD        (KEY_ALT | KEY_FIRE | KEY_UP | KEY_DOWN)
#include "sl_device_init_dpll_config.h"
// -----------------------------------------------------------------------------
//                              Macros and Typedefs
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                          Static Function Declarations
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Global Variables
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//                                Static Variables
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
//                          Public Function Definitions
// -----------------------------------------------------------------------------
/******************************************************************************
 * Main function
 *****************************************************************************/
void dumpToDisplay(int start, int mode)
{

  extMemSetCurrentAddress(start);
  for (int i = 0; i < 128; i++)
  {
    char linebuffer[9+8] = {0};
    char clinebuffer[8];
    char printbuffer[43];
    if (mode)
    {
        extMemGetDataFromCurrentAddress(linebuffer, 8);
    }
    else
    {
        for (int j = 0; j < 8; j++)
           linebuffer[j] = extMemGetByteFromAddress((void*)(start + j + 8 * i));
        extMemSetCurrentAddress(start + 8 * i);
    }
    linebuffer[8] = 0;
    memcpy(clinebuffer, linebuffer, 8);
    for (int x = 0; x < 8; x++)
    {
      if (linebuffer[x] < 32 || linebuffer[x] > 127)
        linebuffer[x] = '.';
      snprintf(printbuffer, sizeof(printbuffer), "0x%08x: %02x%02x%02x%02x%02x%02x%02x%02x   %s\r\n",
               start + i*8,
               clinebuffer[0],
               clinebuffer[1],
               clinebuffer[2],
               clinebuffer[3],
               clinebuffer[4],
               clinebuffer[5],
               clinebuffer[6],
               clinebuffer[7],
               linebuffer);
    }
    printf(printbuffer);
    displayPrintln(1, "%s", printbuffer );
  }
}
void overclock(void)
{
  CMU_DPLLInit_TypeDef dpll_init = {
    .frequency = 80000000,    // this is just to shut up the asserts.
    .n = OC_PLLN,
    .m = OC_PLLD,
    .refClk = SL_DEVICE_INIT_DPLL_REFCLK,
    .edgeSel = SL_DEVICE_INIT_DPLL_EDGE,
    .lockMode = SL_DEVICE_INIT_DPLL_LOCKMODE,
    .autoRecover = SL_DEVICE_INIT_DPLL_AUTORECOVER,
    .ditherEn = SL_DEVICE_INIT_DPLL_DITHER
  };

  CMU_Select_TypeDef selected_sysclk = CMU_ClockSelectGet(cmuClock_SYSCLK);

  if (selected_sysclk == cmuSelect_HFRCODPLL) {
    // From Reference Manual:
    // The CMU should not be running from the HFRCO. If necessary, the CMU
    // should switch to the FSRCO until after the DPLL has locked to avoid
    // over-clocking due to overshoot.
    CMU_CLOCK_SELECT_SET(SYSCLK, FSRCO);
  }

  CMU_ClockEnable(cmuClock_DPLL0, true);

  CMU_DPLLLock(&dpll_init);

  if (selected_sysclk == cmuSelect_HFRCODPLL) {
    CMU_CLOCK_SELECT_SET(SYSCLK, HFRCODPLL);
  }
}
#include "sl_memory_config.h"
extern uint32_t __StackLimit[];                // not really an array!
void checkForDataFileUpdate(int c)
{
  #if !TEST_YMODEM
 if ((c & KEY_COMBINATION_FOR_DATA_UPLOAD) == (KEY_COMBINATION_FOR_DATA_UPLOAD))
#endif
  {
    // let's first try to mount SD
#if HAS_SD
      // let's first check if there is a SD card on the disk
      displayPrintln(1, "Trying to init SD CARD.");
      FATFS fs;
      uint32_t stat =  f_mount(&fs, "", 1);
      printf("f_mount() %d\r\n", stat);
      if (stat == 0)
      {
        displayPrintln(1, "SD Card init successful!");
        displayPrintln(1, "Opening " PAK_FILE_NAME "...");

        FIL fil;
        stat = f_open(&fil, "0:" PAK_FILE_NAME, FA_READ);
        int32_t fsize = fil.obj.objsize;
        printf("f_open() %d, size %d\r\n", stat, fsize);
        if (stat == 0)
        {

          displayPrintln(1, "Success! size: %d bytes", fsize);
          if (fsize > 0)
          {
            uint32_t address = (uint32_t) PAK_ADDRESS;
            displayPrintln(1, "Erasing flash, please wait");
            displayPrintln(1, "(this might take up to 100 seconds)");
            SET_FLASH_MODE();
            extMemEraseAll();
            displayPrintln(1, "Programming, please wait");
            int i = 0;
            while (fsize > 0)
            {
              UINT br = 0;
              uint32_t  btr = fsize;
#define MAX_STACK_BUFFER 16384
              uint32_t maxbtr =  MAX_STACK_BUFFER & ~4095;
              if (btr > maxbtr)
              {
                btr = maxbtr;
              }
              uint8_t buffer[MAX_STACK_BUFFER]; // we have plenty of stack here.
              stat = f_read(&fil, buffer , btr, &br);
              if (!br || stat)
              {
                displayPrintln(1, "Error, read 0 bytes, stat %d", stat);
                break;
              }
              extMemProgram(address, buffer, br);
              fsize -= br;
              address += br;
              if (!(i % 8)) // displayPrintln takes time. Let's print only 1 over 8
              {
                  displayPrintln(1, "%d bytes remaining...", fsize);
              }
              i++;
            }
            displayPrintln(1, "PAK copy success!");
          }
          else
          {
            displayPrintln(1, "Error, non-positve size!", fsize);
          }
        }
        else
        {
          displayPrintln(1, "Can't open file %s!", PAK_FILE_NAME);
        }
      }
      else
      {
        displayPrintln(1, "Can't open SD card.");
      }

#endif
      displayPrintln(1, "Reset in 2 seconds!");
      delay(2000);
      NVIC_SystemReset();
  }
}
static const uint32_t clocks[] =
{
    cmuClock_EUSART0, cmuClock_EUSART1, cmuClock_PRS, cmuClock_LDMA,
    cmuClock_LDMAXBAR, cmuClock_SYSCFG, cmuClock_USART0, CAT(cmuClock_TIMER, TICK_TIMER_NUMBER),  CAT(cmuClock_TIMER, TIME_TIMER_NUMBER),
    cmuClock_GPIO, cmuClock_ICACHE, cmuClock_DMEM
};
__attribute__((noinline)) static void sysInit(void)  //noinline attribute will reduce stack usage.
{
    // Initialize Silicon Labs device, system, service(s) and protocol stack(s).
    // Note that if the kernel is present, processing task(s) will be created by
    // this call.
    // Note: system sl_system_init() call was split to allow using the malloc wrapper
    sl_platform_init();
    //
  #if OVERCLOCK
    overclock();
  #endif
    //
    // Enable clocks and overclock PCLK so it is the same as CPU clk
    CMU_ClockDivSet(cmuClock_PCLK, 1);

    for (size_t i = 0; i < sizeof (clocks) / sizeof(clocks[0]); i++)
    {
      CMU_ClockEnable(clocks[i], true);
    }
    //
    // Enable TICK_TIMER for generic delay
    TICK_TIMER->CFG = TIMER_CFG_PRESC_DIV8;
    TICK_TIMER->EN = TIMER_EN_EN;
    TICK_TIMER->TOP = 0xFFFFFFFF;
    TICK_TIMER->CMD = TIMER_CMD_START;
    // Enable TIME TIMER for ms delay
    TIME_TIMER->CFG = TIMER_CFG_PRESC_DIV1024;
    TIME_TIMER->EN = TIMER_EN_EN;
    TIME_TIMER->TOP = 0xFFFFFFFF;
    TIME_TIMER->CMD = TIMER_CMD_START;

    // enable radio to be able to use seqram
    CMU->RADIOCLKCTRL = CMU_RADIOCLKCTRL_EN;
    CMU->SYSCLKCTRL &= ~CMU_SYSCLKCTRL_RHCLKPRESC;
    memset((void*)RDMEM_SEQRAM_SEQRAM_MEM_BASE, 0, 20480);    // clear seqram.
    //
    FLASH_NCS_HIGH();

    //
  #ifdef VCOM_ENABLE_PORT
    GPIO_PinModeSet(VCOM_ENABLE_PORT, VCOM_ENABLE_PIN, gpioModePushPull, 1);
  #endif
    GPIO_PinModeSet(VCOM_TX_PORT, VCOM_TX_PIN, gpioModePushPull, 1);
    GPIO_PinModeSet(VCOM_RX_PORT, VCOM_RX_PIN, gpioModePushPull, 1);
    //
    //
    displayInit();
    //

    initGraphics();
    displayPrintln(0, "Quake on EFR32MG24 by Nicola Wrachien");
    displayPrintln(1, "Build date %s", __DATE__);
    displayPrintln(1, "Build time %s", __TIME__);
    //
    // measure refresh time!
    //
    uint32_t oldTime = TICK_TIMER->CNT;
    startDisplayRefresh(0, 1);
    startDisplayRefresh(0, 1);
    oldTime = TICK_TIMER->CNT - oldTime;
    //
    displayPrintln(1, "Frame refresh time %d us!", oldTime / 10);
    displayPrintln(1, "Memzone size %d bytes.", getStaticZoneSize());
    displayPrintln(1, "Code Size: %d bytes", FLASH_CODE_SIZE);
    displayPrintln(1, "Trying to read external flash...");
    delay(500);
    extMemInit();

    displayPrintln(1, "SPI Flash Size: %d MB.", extMemGetSize() / 1048576);

    displayPrintln(1, "HFXO: %d Hz", SystemHFXOClockGet());
    displayPrintln(1, "HCLK: %d Hz", SystemHFXOClockGet() / (OC_PLLD + 1) * (OC_PLLN + 1) );

    FLASH_NCS_HIGH();
    displayPrintln(1, "");
#if BOARD == BOARD_THEGAMEPAD_ARDUINONANOMATTER
    displayPrintln(1, "Press UP & DOWN & 4 & 3");

    #else
    displayPrintln(1, "Press ALT & FIRE & UP & DOWN");
#endif
    displayPrintln(1, "to start PAK installation.");
    delay(200);

    FLASH_NCS_LOW();
    SET_FLASH_MODE();
    // Let's check if we shall go in PAK upload mode
    initKeyboard();
    uint16_t c;
  #define TEST_KEYS 0 // define to 1 to get displayed the key code, and quickly fill the correct defines.
  #if TEST_KEYS
    while (1)
  #endif
    {
        getKeys(&c);

        displayPrintln(1, "Key Pressed: %04x", c);
        printf("Keys pressed: %x\r\n", c);
    }
    //
      checkForDataFileUpdate(c);

  #if BOARD == BOARD_THEGAMEPAD_ARDUINONANOMATTER
    GPIO_PinModeSet(gpioPortC, 3, gpioModePushPull, 0);
  #endif

    //dumpToDisplay(0x407251fc, 1); // to check read block.
    //dumpToDisplay(0x407251fc, 0); // to check read byte

    //
    SET_FLASH_MODE();
    //
    Z_Init();
    //
    // next-hack. rand() uses malloc, which in turn uses Z_Malloc() with tag PU_WRAP. To make sure we don't fragment, we uses rand() the first time right
    // after Z_Init();
    rand();
}
static void game(void)
{
    float    time, oldtime, newtime;

    Cvar_Init();
  #if WIN32
    Sys_Init();
  #endif
    memset(_g, 0, sizeof(global_data_t));
    Host_Init(NULL);
    oldtime = Sys_FloatTime () - 0.1f;
    while (1)
    {
  // find time spent rendering last frame
        newtime = Sys_FloatTime ();
        time = newtime - oldtime;
        if (time > sys_ticrate*2)
            oldtime = newtime;
        else
            oldtime += time;
        Host_Frame (time);

    }

}
int main(void)
{
  for (int i = 0; i < SL_STACK_SIZE / 4; i++)
  {
    __StackLimit[i] = 0xEFBEADDE;  // stack canary.
  }

  sysInit();
  game();
  return 0;
}
void Sys_Error (char *error, ...)
{
    va_list     argptr;
    //char        string[1024];
    printf("Error: ");
    va_start (argptr,error);
    vprintf (error,argptr);
    va_end (argptr);
    while(1);

}
unsigned int I_GetTimeMicrosecs(void)
{
    return TICK_TIMER->CNT * (1000000.0f / TICK_TIMER_FREQUENCY_HZ);
}
float Sys_FloatTime(void)
{
  return TIME_TIMER->CNT * (1.0f / TIME_TIMER_FREQUENCY_HZ);
}


// -----------------------------------------------------------------------------
//                          Static Function Definitions
// -----------------------------------------------------------------------------
