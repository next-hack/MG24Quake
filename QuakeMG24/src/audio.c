/**
 *  DAC and PWM  for sound generation for Quake.
 *
 *  Note: DAC needs external amplification.
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
 *  This was taken from our old Doom Port project to MG24 devices.
 *  The update sound function is implemented elsewhere.
 *  We kept just the init function.
 *
 */
#include "audio.h"
#include "extMemory.h"
#include "delay.h"
#include <string.h>
#include "em_ldma.h"
#include "em_cmu.h"
#include "em_vdac.h"
#include "em_gpio.h"
#include "em_prs.h"
//
#include "boards.h"
#include "main.h"
//
//
uint16_t lastMusicIdx = 0;
#if ENABLE_MUSIC
int16_t musBuffer[MUSIC_NUM_SAMPLES];
#endif
//
#define AUDIO_SAMPLE_TIMER_CLOCK CAT(cmuClock_TIMER, AUDIO_SAMPLE_TIMER_NUMBER)
#if AUDIO_MODE == PWM_AUDIO_MODE
    // Audio timer used for PWM if required. Using Timer 1 because can be routed anywhere, unlike 2, 3, 4
#if AUDIO_PORT_R != AUDIO_PORT_L
#error SAME AUDIO PORT FOR BOTH LEFT AND RIGHT CHANNELS SHALL BE USED IN PWM MODE!
#elif AUDIO_PORT_R == GPIO_PORT_A || AUDIO_PORT_R == GPIO_PORT_B
#define AUDIO_PWM_TIMER_NUMBER            4
   #else
#define AUDIO_PWM_TIMER_NUMBER            3
#endif
    #define AUDIO_PWM_TIMER           CAT(TIMER, AUDIO_PWM_TIMER_NUMBER)

    #define GLOBAL_AUDIO_RSHIFT 0
  #define AUDIO_PWM_TIMER_CLOCK CAT(cmuClock_TIMER, AUDIO_PWM_TIMER_NUMBER)
#define LDMA_REQSEL_VALUE CAT(LDMAXBAR_CH_REQSEL_SOURCESEL_TIMER, AUDIO_SAMPLE_TIMER_NUMBER) | CAT3(LDMAXBAR_CH_REQSEL_SIGSEL_TIMER, AUDIO_SAMPLE_TIMER_NUMBER, UFOF)
#elif AUDIO_MODE == DAC_AUDIO_MODE
    #define GLOBAL_AUDIO_RSHIFT 4
  #define LDMA_REQSEL_VALUE CAT(LDMAXBAR_CH_REQSEL_SOURCESEL_TIMER, AUDIO_SAMPLE_TIMER_NUMBER) | CAT3(LDMAXBAR_CH_REQSEL_SIGSEL_TIMER, AUDIO_SAMPLE_TIMER_NUMBER, UFOF)
#else
  #error audio mode not defined
#endif
//
AUX_SECTION int8_t audioBuffer[AUDIO_BUFFER_LENGTH * 2];
static LDMA_Descriptor_t dmaXfer[2];  // 2 channels only
// Set the VDAC to max frequency of 0.5 MHz
#define CLK_VDAC_FREQ              500000
//
void initAudio(void)
{
  //
  // enable timer
    CMU_ClockEnable(AUDIO_SAMPLE_TIMER_CLOCK, true);   // for Audio
    #if AUDIO_MODE == PWM_AUDIO_MODE
        CMU_ClockEnable(AUDIO_PWM_TIMER_CLOCK, true);
        // TIMER 1 generates PWM
        AUDIO_PWM_TIMER->CFG = TIMER_CFG_PRESC_DIV1 | TIMER_CFG_MODE_UPDOWN;
        AUDIO_PWM_TIMER->CC[0].CFG = TIMER_CC_CFG_MODE_PWM;
        AUDIO_PWM_TIMER->CC[1].CFG = TIMER_CC_CFG_MODE_PWM;
        AUDIO_PWM_TIMER->EN = TIMER_EN_EN;
        AUDIO_PWM_TIMER->CC[0].CTRL = TIMER_CC_CTRL_ICEVCTRL_EVERYEDGE | TIMER_CC_CTRL_CMOA_TOGGLE;
        AUDIO_PWM_TIMER->CC[1].CTRL = TIMER_CC_CTRL_ICEVCTRL_EVERYEDGE | TIMER_CC_CTRL_CMOA_TOGGLE;
        AUDIO_PWM_TIMER->TOP = 0xFF;
        //
        AUDIO_PWM_TIMER->CC[0].OC = 0x10;
        AUDIO_PWM_TIMER->CC[1].OC = 0x10;
        AUDIO_PWM_TIMER->CMD = TIMER_CMD_START;
        // Route PWM pin
        GPIO_PinModeSet(AUDIO_PORT_L, AUDIO_PIN_L , gpioModePushPullAlternate, 0);
        GPIO->TIMERROUTE[AUDIO_PWM_TIMER_NUMBER].CC0ROUTE = (AUDIO_PORT_L << _GPIO_TIMER_CC0ROUTE_PORT_SHIFT) | (AUDIO_PIN_L << _GPIO_TIMER_CC0ROUTE_PIN_SHIFT);
        GPIO_PinModeSet(AUDIO_PORT_R, AUDIO_PIN_R , gpioModePushPullAlternate, 0);
        GPIO->TIMERROUTE[AUDIO_PWM_TIMER_NUMBER].ROUTEEN = GPIO_TIMER_ROUTEEN_CC0PEN | GPIO_TIMER_ROUTEEN_CC1PEN;
        GPIO->TIMERROUTE[AUDIO_PWM_TIMER_NUMBER].CC1ROUTE = (AUDIO_PORT_R << _GPIO_TIMER_CC1ROUTE_PORT_SHIFT) | (AUDIO_PIN_R << _GPIO_TIMER_CC1ROUTE_PIN_SHIFT);
    #else
    CMU_ClockEnable(cmuClock_VDAC0, true);
    __IOM uint32_t *analogBus[] = {&GPIO->ABUSALLOC, &GPIO->BBUSALLOC, &GPIO->CDBUSALLOC, &GPIO->CDBUSALLOC};
    #if AUDIO_PIN_L & 1
        *analogBus[AUDIO_PORT_L] = GPIO_CDBUSALLOC_CDODD0_VDAC0CH0;
    #else
        *analogBus[AUDIO_PORT_L] = GPIO_CDBUSALLOC_CDEVEN0_VDAC0CH0;
    #endif
    VDAC_Init_TypeDef vdacInit          = VDAC_INIT_DEFAULT;
    vdacInit.reference = vdacRefAvdd;
    // Set prescaler to get 0.5 MHz VDAC clock frequency.
    vdacInit.prescaler = VDAC_PrescaleCalc(VDAC0, CLK_VDAC_FREQ);
    VDAC_Init(VDAC0, &vdacInit);
    VDAC_InitChannel_TypeDef vdacChInit = VDAC_INITCHANNEL_DEFAULT;
    vdacChInit.auxOutEnable = true;
    vdacChInit.mainOutEnable = false;
    //
    vdacChInit.pin = AUDIO_PIN_L;
    vdacChInit.port = AUDIO_PORT_L + 1; // GpioPortA starts from 0, but vdacPort starts from 1...
    vdacChInit.enable = true;
    VDAC_InitChannel(VDAC0, &vdacChInit, 0);
        #if STEREO_AUDIO
    #if (AUDIO_PORT_R != AUDIO_PORT_L)
      #if AUDIO_PIN_R & 1
          *analogBus[AUDIO_PORT_R] = GPIO_CDBUSALLOC_CDODD1_VDAC0CH1;
      #else
          *analogBus[AUDIO_PORT_R] = GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1;
      #endif
    #else
        #if AUDIO_PIN_R & 1
            *analogBus[AUDIO_PORT_R] |= GPIO_CDBUSALLOC_CDODD1_VDAC0CH1;
        #else
            *analogBus[AUDIO_PORT_R] |= GPIO_CDBUSALLOC_CDEVEN1_VDAC0CH1;
        #endif
    #endif
    // configure right channel as well
    vdacChInit.pin = AUDIO_PIN_R;
    vdacChInit.port = AUDIO_PORT_R + 1; // GpioPortA starts from 0, but vdacPort starts from 1...
    VDAC_InitChannel(VDAC0, &vdacChInit, 1);
        #endif
    #endif
    //
    // Configure Timer AUDIO_SAMPLE_TIMER to generate a signal every 1/11025 s
    AUDIO_SAMPLE_TIMER->CFG = TIMER_CFG_PRESC_DIV1 | TIMER_CFG_DMACLRACT;
    AUDIO_SAMPLE_TIMER->EN = TIMER_EN_EN;
    AUDIO_SAMPLE_TIMER->TOP = (CPU_FREQUENCY / AUDIO_SAMPLE_RATE) - 1;
    AUDIO_SAMPLE_TIMER->CMD = TIMER_CMD_START;
    // Config for looping sound
    LDMAXBAR->CH[AUDIO_DMA_CHANNEL_L].REQSEL = LDMA_REQSEL_VALUE;
    //
    LDMA->CH[AUDIO_DMA_CHANNEL_L].LOOP = 0 << _LDMA_CH_LOOP_LOOPCNT_SHIFT;
    LDMA->CH[AUDIO_DMA_CHANNEL_L].CFG = LDMA_CH_CFG_ARBSLOTS_ONE | LDMA_CH_CFG_SRCINCSIGN_POSITIVE | _LDMA_CH_CFG_DSTINCSIGN_POSITIVE;

    // configure transfer descriptor
    dmaXfer[0].xfer.structType = _LDMA_CH_CTRL_STRUCTTYPE_TRANSFER;
    // destination
    dmaXfer[0].xfer.dstAddrMode = _LDMA_CH_CTRL_DSTMODE_ABSOLUTE;
#if AUDIO_MODE == PWM_AUDIO_MODE
        dmaXfer[0].xfer.dstAddr = (uint32_t) &AUDIO_PWM_TIMER->CC[0].OCB;
        dmaXfer[0].xfer.srcAddr = ((uint32_t) &audioBuffer[0]); //8 bit size, even address
        dmaXfer[0].xfer.srcInc = _LDMA_CH_CTRL_SRCINC_TWO;
        //
        dmaXfer[0].xfer.size = _LDMA_CH_CTRL_SIZE_BYTE;
        dmaXfer[0].xfer.blockSize = _LDMA_CH_CTRL_BLOCKSIZE_UNIT1; // one byte per transfer
#if STEREO_AUDIO
        // Config for looping sound
      LDMAXBAR->CH[AUDIO_DMA_CHANNEL_R].REQSEL = LDMA_REQSEL_VALUE;
      //
      LDMA->CH[AUDIO_DMA_CHANNEL_R].LOOP = 0 << _LDMA_CH_LOOP_LOOPCNT_SHIFT;
      LDMA->CH[AUDIO_DMA_CHANNEL_R].CFG = LDMA_CH_CFG_ARBSLOTS_ONE | LDMA_CH_CFG_SRCINCSIGN_POSITIVE | _LDMA_CH_CFG_DSTINCSIGN_POSITIVE;

      // configure transfer descriptor
      dmaXfer[1].xfer.structType = _LDMA_CH_CTRL_STRUCTTYPE_TRANSFER;
      // destination
      dmaXfer[1].xfer.dstAddrMode = _LDMA_CH_CTRL_DSTMODE_ABSOLUTE;

      dmaXfer[1].xfer.dstAddr = (uint32_t) &AUDIO_PWM_TIMER->CC[1].OCB;
      dmaXfer[1].xfer.srcAddr = ((uint32_t) &audioBuffer[1]); //8 bit size, even pdd address
      dmaXfer[1].xfer.srcInc = _LDMA_CH_CTRL_SRCINC_TWO;
      //
      dmaXfer[1].xfer.size = _LDMA_CH_CTRL_SIZE_BYTE;
      dmaXfer[1].xfer.blockSize = _LDMA_CH_CTRL_BLOCKSIZE_UNIT1; // one unit per transfer
      dmaXfer[1].xfer.dstInc = _LDMA_CH_CTRL_DSTINC_NONE;
      //
      dmaXfer[1].xfer.srcAddrMode = _LDMA_CH_CTRL_SRCMODE_ABSOLUTE;

      dmaXfer[1].xfer.xferCnt = AUDIO_BUFFER_LENGTH - 1;
      dmaXfer[1].xfer.linkAddr = (uint32_t) &dmaXfer[1] >> 2;
      dmaXfer[1].xfer.link = 1;
      dmaXfer[1].xfer.linkMode = _LDMA_CH_LINK_LINKMODE_ABSOLUTE;
      //
      /* Set the descriptor address. */
      LDMA->CH[AUDIO_DMA_CHANNEL_R].LINK = ((uint32_t) &dmaXfer[1] & _LDMA_CH_LINK_LINKADDR_MASK) | LDMA_CH_LINK_LINK;
#endif
    #else
        #if STEREO_AUDIO
    // Config for looping sound
    LDMAXBAR->CH[AUDIO_DMA_CHANNEL_R].REQSEL = LDMA_REQSEL_VALUE;
    //
    LDMA->CH[AUDIO_DMA_CHANNEL_R].LOOP = 0 << _LDMA_CH_LOOP_LOOPCNT_SHIFT;
    LDMA->CH[AUDIO_DMA_CHANNEL_R].CFG = LDMA_CH_CFG_ARBSLOTS_ONE | LDMA_CH_CFG_SRCINCSIGN_POSITIVE | _LDMA_CH_CFG_DSTINCSIGN_POSITIVE;

    // configure transfer descriptor
    dmaXfer[1].xfer.structType = _LDMA_CH_CTRL_STRUCTTYPE_TRANSFER;
    // destination
    dmaXfer[1].xfer.dstAddrMode = _LDMA_CH_CTRL_DSTMODE_ABSOLUTE;

    dmaXfer[1].xfer.dstAddr = (uint32_t) &VDAC0->CH1F;
    dmaXfer[1].xfer.srcAddr = ((uint32_t) &audioBuffer[1]); //8 bit size,
    dmaXfer[1].xfer.srcInc = _LDMA_CH_CTRL_SRCINC_TWO;
    //
    dmaXfer[1].xfer.size = _LDMA_CH_CTRL_SIZE_BYTE;
    dmaXfer[1].xfer.blockSize = _LDMA_CH_CTRL_BLOCKSIZE_UNIT1; // one unit per transfer
    dmaXfer[1].xfer.dstInc = _LDMA_CH_CTRL_DSTINC_NONE;
    //
    dmaXfer[1].xfer.srcAddrMode = _LDMA_CH_CTRL_SRCMODE_ABSOLUTE;

    dmaXfer[1].xfer.xferCnt = AUDIO_BUFFER_LENGTH - 1;
    dmaXfer[1].xfer.linkAddr = (uint32_t) &dmaXfer[1] >> 2;
    dmaXfer[1].xfer.link = 1;
    dmaXfer[1].xfer.linkMode = _LDMA_CH_LINK_LINKMODE_ABSOLUTE;
    //
    /* Set the descriptor address. */
    LDMA->CH[AUDIO_DMA_CHANNEL_R].LINK = ((uint32_t) &dmaXfer[1] & _LDMA_CH_LINK_LINKADDR_MASK) | LDMA_CH_LINK_LINK;
        #endif
    dmaXfer[0].xfer.dstAddr = (uint32_t) &VDAC0->CH0F;
    dmaXfer[0].xfer.srcAddr = ((uint32_t) audioBuffer); //8 bit size,
    dmaXfer[0].xfer.srcInc = _LDMA_CH_CTRL_SRCINC_TWO;
    //
    dmaXfer[0].xfer.size = _LDMA_CH_CTRL_SIZE_BYTE;
    dmaXfer[0].xfer.blockSize = _LDMA_CH_CTRL_BLOCKSIZE_UNIT1; // one unit per transfer
    #endif
    dmaXfer[0].xfer.dstInc = _LDMA_CH_CTRL_DSTINC_NONE;
    //
    dmaXfer[0].xfer.srcAddrMode = _LDMA_CH_CTRL_SRCMODE_ABSOLUTE;

    dmaXfer[0].xfer.xferCnt = AUDIO_BUFFER_LENGTH - 1;
    dmaXfer[0].xfer.linkAddr = (uint32_t) &dmaXfer[0] >> 2;
    dmaXfer[0].xfer.link = 1;
    dmaXfer[0].xfer.linkMode = _LDMA_CH_LINK_LINKMODE_ABSOLUTE;
    //
    /* Set the descriptor address. */
    LDMA->CH[AUDIO_DMA_CHANNEL_L].LINK = ((uint32_t) &dmaXfer[0] & _LDMA_CH_LINK_LINKADDR_MASK) | LDMA_CH_LINK_LINK;
    //
    LDMA->IF_CLR = 1;
    //
    BUS_RegMaskedClear(&LDMA->CHDONE, (1 << AUDIO_DMA_CHANNEL_L) |(1 << AUDIO_DMA_CHANNEL_R)); /* Clear the done flag.     */
    LDMA->LINKLOAD = (1 << AUDIO_DMA_CHANNEL_L);
    LDMA->LINKLOAD = (1 << AUDIO_DMA_CHANNEL_R); /* Start a transfer by loading the descriptor.  */
   LDMA->CHEN_SET = (1 << AUDIO_DMA_CHANNEL_L) |  ((1 << AUDIO_DMA_CHANNEL_R));
    //
}
#pragma GCC optimize("Ofast") // we need to compile this code to be as fast as possible.

int SNDDMA_GetDMAPos(void)
{
  uint32_t currentIdx = (LDMA->CH[AUDIO_DMA_CHANNEL_L].SRC - (uint32_t) audioBuffer) / sizeof(audioBuffer[0]);
  return currentIdx / 2;    //there are 2 channels, so step is 2
}
