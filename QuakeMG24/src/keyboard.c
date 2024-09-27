/**
 *  Keyboard interface for Doom Port to the EFR32xG2x MCUs by Nicola Wrachien
 *
 *  Copyright (C) 2021-23 Nicola Wrachien (next-hack in the comments).
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
 * Description: Keyboard handling functions for different types
 * (i2c, shift register).
 */


#include "main.h"
#include "keyboard.h"
#include "printf.h"
#include "delay.h"
#include "em_gpio.h"
#include "em_ldma.h"
#if KEYBOARD == I2C_KEYBOARD
#include "em_i2c.h"
#endif
#include "em_cmu.h"
#if HAS_LEFT_JOYPAD || HAS_RIGHT_JOYPAD
#define ADC_FREQ 5000000L
#include "em_iadc.h"
#endif
#if KEYBOARD == PARALLEL_KEYBOARD
#if 0
    const uint8_t pins[] =
    {
        PIN_KEY_UP,
        PIN_KEY_DOWN,
        PIN_KEY_LEFT,
        PIN_KEY_RIGHT,
        PIN_KEY_USE,
        PIN_KEY_CHGW,
        PIN_KEY_ALT,
        PIN_KEY_FIRE
    };
#endif
    const uint8_t keys[] = 
    {
        KEY_UP,
        KEY_DOWN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_USE,
        KEY_CHGW,
        KEY_ALT,
        KEY_FIRE,
    };
#endif
#if KEYBOARD == I2C_KEYBOARD
//
// for port expander
//
#define MCP23008_IODIR 0
#define MCP23008_IPOL 1
#define MCP23008_GPINTEN 2
#define MCP23008_DEFVAL 3
#define MCP23008_INTCON 4
#define MCP23008_IOCON 5
#define MCP23008_GPPU 6
#define MCP23008_INTF 7
#define MCP23008_INTCAP 8
#define MCP23008_GPIO 9
#define MCP23008_OLAT 10
//
I2C_TransferReturn_TypeDef i2cTransfer( I2C_TransferSeq_TypeDef *seq)
{
  I2C_TransferReturn_TypeDef rc = i2cTransferDone;
  uint32_t timeout = 10000000;

  /* Start a polled transfer */
  rc = I2C_TransferInit(I2C0, seq);
  while ((i2cTransferInProgress == rc) && (timeout--))
  {
    rc = I2C_Transfer(I2C0);
  }
  return rc;
}

void i2cSendAndWait(uint8_t addr, uint8_t value)
{
    uint8_t buf[2];
    I2C_TransferSeq_TypeDef seq =
    {
        .addr = EXPANDER_I2C_ADDRESS << 1,
        .flags = I2C_FLAG_WRITE
    };
    seq.buf[0].data = buf;
    seq.buf[0].len = 2;
    buf[0] = addr;
    buf[1] = value;
    i2cTransfer(&seq);
}
void updateI2cKeyboard(uint8_t *keys)
{
  uint8_t wrBuf;
  I2C_TransferSeq_TypeDef seq =
  {
      .addr = EXPANDER_I2C_ADDRESS << 1,
      .flags = I2C_FLAG_WRITE_READ,
  };
  wrBuf = MCP23008_GPIO;
  // write confi
  seq.buf[0].data = &wrBuf;
  seq.buf[0].len = 1;
  // read config: directly on keys value
  seq.buf[1].data = keys;
  seq.buf[1].len = 1;
  i2cTransfer(&seq);
}
void initI2cKeyboard()
{
  // enable i2c clk
  CMU_ClockEnable(cmuClock_I2C0, true);
  // configure GPIO
  GPIO_PinModeSet(I2C_SDA_PORT_NUMBER, I2C_SDA_PIN_NUMBER, gpioModeWiredAndPullUp, 1);
  GPIO_PinModeSet(I2C_SCL_PORT_NUMBER, I2C_SCL_PIN_NUMBER, gpioModeWiredAndPullUp, 1);
  // to avoid issue if the device is reset in between an i2c transaction.
  for (int i = 0; i < 9; i++)
  {
    GPIO_PinOutClear(I2C_SCL_PORT_NUMBER, I2C_SCL_PIN_NUMBER);
    delay(10);
    GPIO_PinOutSet(I2C_SCL_PORT_NUMBER, I2C_SCL_PIN_NUMBER);
    delay(10);
  }
  GPIO->I2CROUTE[0].SDAROUTE = (I2C_SDA_PORT_NUMBER << _GPIO_I2C_SDAROUTE_PORT_SHIFT) | (I2C_SDA_PIN_NUMBER << _GPIO_I2C_SDAROUTE_PIN_SHIFT);
  GPIO->I2CROUTE[0].SCLROUTE = (I2C_SCL_PORT_NUMBER << _GPIO_I2C_SCLROUTE_PORT_SHIFT) | (I2C_SCL_PIN_NUMBER << _GPIO_I2C_SCLROUTE_PIN_SHIFT);
  GPIO->I2CROUTE[0].ROUTEEN = GPIO_I2C_ROUTEEN_SCLPEN | GPIO_I2C_ROUTEEN_SDAPEN;
  I2C_Init_TypeDef init = I2C_INIT_DEFAULT;
  init.freq = 400000;
  I2C_Init(I2C0, &init);
  //

    // configure port expander
    // all input
    i2cSendAndWait(MCP23008_IODIR, 255);
    // all pull up
    i2cSendAndWait(MCP23008_GPPU, 255);
    // wait some time, because pull ups are quite weak and there is 100nF cap
    delay(10);
}
#endif
#if KEYBOARD == PARALLEL_KEYBOARD

void initParallelKeyboard()
{
 // error not implemented !
}
#endif
#if KEYBOARD == SPI74165_KEYBOARD || KEYBOARD == SPI2X74165_KEYBOARD
void initSpi74165Keyboard()
{
  //
  GPIO_PinModeSet(SR_MISO_PORT, SR_MISO_PIN, gpioModeInput, 1);
  GPIO_PinModeSet(SR_PL_PORT, SR_PL_PIN, gpioModePushPull, 1);
  GPIO_PinModeSet(SR_CLK_PORT, SR_CLK_PIN, gpioModePushPull, 1);
}
#endif
#if ADC_USES_DMA
static LDMA_Descriptor_t iadc_descriptor;
static volatile int32_t joydata[4];
void initADC_LDMA(volatile int32_t *buffer, uint32_t size)
{
 // Trigger LDMA transfer on IADC scan completion
 LDMA_TransferCfg_t transferCfg =
   LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SCAN);

 /*
  * Set up a linked descriptor to save scan results to the
  * user-specified buffer.  By linking the descriptor to itself
  * (the last argument is the relative jump in terms of the number of
  * descriptors), transfers will run continuously until firmware
  * otherwise stops them.
  */
 iadc_descriptor =
   (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_WORD(&(IADC0->SCANFIFODATA), buffer, size, 0);
  // no ISR
  iadc_descriptor.xfer.doneIfs = 0;

 /*
  * Start the transfer.  The LDMA request and interrupt after saving
  * the specified number of IADC conversion results.
  */
 LDMA_StartTransfer(IADC_LDMA_CH, (void*)&transferCfg, (void*)&iadc_descriptor);
}
#endif
#if HAS_LEFT_JOYPAD || HAS_RIGHT_JOYPAD
static int8_t joystickADCtoDelta(int data, int reverse)
{
    if (reverse)
    {
        data = JOYSTICK_MIDSCALE - data;
    }
    else
    {
        data = data - JOYSTICK_MIDSCALE;
    }
    // dead zone: no movement.
    if (data < JOYSTICK_DEADBAND && data > -JOYSTICK_DEADBAND)
    {
        return 0;
    }
    if (data >= JOYSTICK_MAXVALUE)
        return 127;
    if (data <= - JOYSTICK_MAXVALUE)
        return -128;
    // intermediate value: between DEADBAND and MAXVALUE
    if (data > 0)
    {
        return 128 * (data - JOYSTICK_DEADBAND) / JOYSTICK_MAXVALUE;
    }
    else
    {
        return 128 * (data + JOYSTICK_DEADBAND) / JOYSTICK_MAXVALUE;
    }
}
#endif
void getAnalogInput(int32_t * lx, int32_t *ly, int32_t *rx, int32_t *ry)
{
#if HAS_LEFT_JOYPAD || HAS_RIGHT_JOYPAD
#if ADC_USES_DMA
    int32_t data;
    data =     joydata[0];
    *lx = joystickADCtoDelta(data, false);
    data =     joydata[1];
    *ly = joystickADCtoDelta(data, false);
    data =     joydata[2];
    *rx = joystickADCtoDelta(data, true);
    data =     joydata[3];
    *ry = joystickADCtoDelta(data, false);
#else
    while (!(IADC0->IF & IADC_IF_SCANTABLEDONE))
    {
        // wait. Should not happen, as this function always issues a new read.
    }
    IADC0->IF_CLR =  IADC_IF_SCANTABLEDONE;
    int32_t data;
    data = IADC0->SCANFIFODATA;
    //printf("Res LX =  %x, ", data);
    *lx = joystickADCtoDelta(data, false);
    data = IADC0->SCANFIFODATA;
    //printf("Res LY =  %x, ", data);
    *ly = joystickADCtoDelta(data, false);
    data = IADC0->SCANFIFODATA;
    //printf("Res RX =  %x, ", data);
    *rx = joystickADCtoDelta(data, true);
    data = IADC0->SCANFIFODATA;
    //printf("Res RY =  %x\r\n", data);
    *ry = joystickADCtoDelta(data, false);
    IADC_command(IADC0, iadcCmdStartScan);
#endif
#else
    *lx = 0;
    *ly = 0;
    *rx = 0;
    *ry = 0;
  #endif

}
void initKeyboard()
{
#if KEYBOARD == PARALLEL_KEYBOARD
    initParallelKeyboard();
#elif KEYBOARD == I2C_KEYBOARD
    initI2cKeyboard();
#elif KEYBOARD == SPI74165_KEYBOARD || KEYBOARD == SPI2X74165_KEYBOARD
    initSpi74165Keyboard();
#else
#error You should have a keyboard to play Doom, right?
#endif
#if HAS_LEFT_JOYPAD || HAS_RIGHT_JOYPAD
    // GPIOs for ADC shall be disabled.
    GPIO_PinModeSet(JOYPAD_RIGHT_X_PORT, JOYPAD_RIGHT_X_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(JOYPAD_RIGHT_Y_PORT, JOYPAD_RIGHT_Y_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(JOYPAD_LEFT_X_PORT, JOYPAD_LEFT_X_PIN, gpioModeDisabled, 0);
    GPIO_PinModeSet(JOYPAD_LEFT_Y_PORT, JOYPAD_LEFT_Y_PIN, gpioModeDisabled, 0);
//
    IADC_Init_t init = IADC_INIT_DEFAULT;
    IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
    IADC_InitScan_t initScan = IADC_INITSCAN_DEFAULT;

    // Scan table structure
    IADC_ScanTable_t scanTable = IADC_SCANTABLE_DEFAULT;
    CMU_ClockEnable(cmuClock_IADC0, true);
    // Use the crystal oscillator, so we don't care about
    CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);
    // Shutdown between conversions to reduce current
    init.warmup = iadcWarmupNormal;

    // Set the HFSCLK prescale value here
    init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, SystemFSRCOClockGet(), 0);
    printf("set clk FSRCOClock\r\n");

      /*
       * Configuration 0 is used by both scan and single conversions by
       * default.  Using VDD, because potentiometer are referred to it.
       * We just want to know the ratio.
       */
      initAllConfigs.configs[0].reference = iadcCfgReferenceVddx;
      initAllConfigs.configs[0].vRef = 3300;
      initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed64x;
      initAllConfigs.configs[0].analogGain = iadcCfgAnalogGain1x;

      /*
       * CLK_SRC_ADC must be prescaled by some value greater than 1 to
       * derive the intended CLK_ADC frequency.
       *
       * Based on the default 2x oversampling rate (OSRHS)...
       *
       * conversion time = ((4 * OSRHS) + 2) / fCLK_ADC
       *       */
      initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                         500000L,
                                                                         0,
                                                                         iadcCfgModeNormal,
                                                                         init.srcClkPrescale);

      initScan.dataValidLevel = iadcFifoCfgDvl4;
#if ADC_USES_DMA
      initScan.triggerAction = iadcTriggerActionContinuous;
      initScan.fifoDmaWakeup = true;
#else
      initScan.triggerAction = iadcTriggerActionOnce;
      initScan.fifoDmaWakeup = false;
#endif
      /*
       * Configure entries in the scan table.
       */
      for (int i = 0; i < 4; i++)
      {
          scanTable.entries[i].negInput = iadcNegInputGnd;
          scanTable.entries[i].includeInScan = true;

      }
#if LEFT_JOYSTICK_ORIENTATION == 0
      scanTable.entries[0].posInput = iadcPosInputPortAPin0 + JOYPAD_LEFT_X_PIN + JOYPAD_LEFT_X_PORT * 16;
      scanTable.entries[1].posInput = iadcPosInputPortAPin0 + JOYPAD_LEFT_Y_PIN + JOYPAD_LEFT_Y_PORT * 16;
#else
#error figure you out what to do!
#endif
#if RIGHT_JOYSTICK_ORIENTATION == 270
      scanTable.entries[2].posInput = iadcPosInputPortAPin0 + JOYPAD_RIGHT_Y_PIN + JOYPAD_RIGHT_Y_PORT * 16;
      scanTable.entries[3].posInput = iadcPosInputPortAPin0 + JOYPAD_RIGHT_X_PIN + JOYPAD_RIGHT_X_PORT * 16;
#endif

      // Initialize IADC
      IADC_init(IADC0, &init, &initAllConfigs);
      // Initialize scan
      IADC_initScan(IADC0, &initScan, &scanTable);
      // Allocate the analog bus for ADC0 inputs.

      __IOM uint32_t *analogBus[] = {&GPIO->ABUSALLOC, &GPIO->BBUSALLOC, &GPIO->CDBUSALLOC, &GPIO->CDBUSALLOC};
      #if AUDIO_PIN_L & 1
          *analogBus[AUDIO_PORT_L] = GPIO_CDBUSALLOC_CDODD0_VDAC0CH0;
      #else
      #endif
      // allocate buses
        *analogBus[JOYPAD_RIGHT_X_PORT] |= (JOYPAD_RIGHT_X_PIN & 1) ?  GPIO_CDBUSALLOC_CDODD1_ADC0 : GPIO_CDBUSALLOC_CDEVEN1_ADC0 ;
        *analogBus[JOYPAD_RIGHT_Y_PORT] |= (JOYPAD_RIGHT_Y_PIN & 1) ?  GPIO_CDBUSALLOC_CDODD1_ADC0 : GPIO_CDBUSALLOC_CDEVEN1_ADC0 ;

        *analogBus[JOYPAD_LEFT_X_PORT] |= (JOYPAD_LEFT_X_PIN & 1) ?  GPIO_CDBUSALLOC_CDODD1_ADC0 : GPIO_CDBUSALLOC_CDEVEN1_ADC0 ;
      *analogBus[JOYPAD_LEFT_Y_PORT] |= (JOYPAD_LEFT_Y_PIN & 1) ?  GPIO_CDBUSALLOC_CDODD1_ADC0 : GPIO_CDBUSALLOC_CDEVEN1_ADC0 ;
      //
      initADC_LDMA(joydata, 4);
      //
      IADC_command(IADC0, iadcCmdStartScan);
#define TEST_ADC_VALUES 0
#if TEST_ADC_VALUES
      // for debug.
      while (1)
      {
          int32_t lx, ly, rx, ry;
          getAnalogInput(&lx, &ly, &rx, &ry);
          printf("Out values: L(x, y) = (%d, %d), R(x, y) = (%d, %d)\r\n", lx, ly, rx, ry);
      }
#endif
#endif
}
void keySRDelay(void)
{
    __asm volatile ("MOV r0, #10\n\t"
                  "loop%=:\n\t"
                  "SUBS r0, #1\n\t"
                  "BNE loop%=\n\t"
                  : : : "r0", "cc");
}
void getKeys(uint16_t * keys)
{
#if KEYBOARD == PARALLEL_KEYBOARD
    uint8_t buttons = 0;
    for (int i = 0; i < 8; i++)
    {
#if 0
      uint32_t pressed = !(ports[i]->IN & (1 << pins[i]));
        if (pressed)
        {
            buttons |= keys[i];
        }
#endif
    }
    *keys = buttons;

#elif KEYBOARD == I2C_KEYBOARD
    updateI2cKeyboard(keys);
    *keys = ~ *keys;
#elif KEYBOARD == SPI74165_KEYBOARD || KEYBOARD == SPI2X74165_KEYBOARD
    uint32_t buttons = 0;
    // pulse on parallel load
    // Note some chips require some delay. Repeating the instruction twice.
    // start with clock low
    GPIO->P_CLR[SR_CLK_PORT].DOUT = 1 << SR_CLK_PIN;
    keySRDelay();
    // shift mode
    GPIO->P_SET[SR_PL_PORT].DOUT = 1 << SR_PL_PIN;
    keySRDelay();
    // Load
    GPIO->P_CLR[SR_PL_PORT].DOUT = 1 << SR_PL_PIN;
    keySRDelay();
    // shift mode
    GPIO->P_SET[SR_PL_PORT].DOUT = 1 << SR_PL_PIN;
    keySRDelay();
    //
#if SPI2X74165_KEYBOARD == KEYBOARD
    for (int i = 0; i < 16; i++)
#else
        for (int i = 0; i < 8; i++)
#endif
    {
      // read data (should be already there).
      uint32_t bit = (GPIO->P[SR_MISO_PORT].DIN >> SR_MISO_PIN) & 1;
      // clock high
      GPIO->P_SET[SR_CLK_PORT].DOUT = 1 << SR_CLK_PIN;
      keySRDelay();
      // clock low
      GPIO->P_CLR[SR_CLK_PORT].DOUT = 1 << SR_CLK_PIN;
      keySRDelay();
      //
      buttons = buttons << 1;
      buttons |= bit;
    }
    *keys =  ~buttons;
#else
    *keys = 0;
    #warning define some keyboard!
#endif
}
