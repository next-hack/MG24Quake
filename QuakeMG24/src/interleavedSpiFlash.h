/**
 * Interleaved SPI flash implementation. Two SPI Flash IC are accessed
 * simultaneously to increase thoughput (typically 8MB @ 40 MHz)
 *
 *  Copyright (C) 2022-2023 by Nicola Wrachien
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
 */
#ifndef SRC_INTERLEAVEDSPIFLASHL_H_
#define SRC_INTERLEAVEDSPIFLASHL_H_

#include <stdint.h>
#include <stdbool.h>
#include "em_device.h"
#include "em_eusart.h"
#include "em_gpio.h"
#include "main.h"
#include "boards.h"

#define EUSART_SPI_WATERMARK (eusartRxFiFoWatermark4Frame | eusartTxFiFoWatermark16Frame) // rx  4, tx 16
#define EUSART_COM_WATERMARK (eusartRxFiFoWatermark1Frame | eusartTxFiFoWatermark16Frame)

//
void*extMemGetDataAligned(void *dest, unsigned int length);
//
#define HAS_EXT_FLASH                           1
#define HIGH_SPEED_EUSART_DIVISOR               1
#define SPI_ADDRESS_MASK                        0x3FFFFFFF   // We support up to 1G
#define SPI_MODE_CFG                            0
//
#define SPI_FLASH_SECTOR_SIZE                   4096
#define SPI_FLASH_32K_BLOCK_SIZE                (32 * 1024)
//
#define SPI_FLASH_WRITE_ENABLE_CMD              0x06
#define SPI_FLASH_PAGE_PROGRAM_CMD              0x02
#define SPI_FLASH_STATUS_REGISTER_READ_CMD      0x05
#define SPI_FLASH_CHIP_ERASE                    0xC7
#define SPI_FLASH_SECTOR_ERASE                  0x20
#define SPI_FLASH_BLOCK32K_ERASE                0x52
#define SPI_FLASH_BLOCK64K_ERASE                0xD8
#define SPI_FLASH_MFG_ID                        0x90
#define SPI_FLASH_READ_DATA                     0x03
#define SPI_FLASH_FAST_READ_DATA                0x0B
#define SPI_FLASH_ENTER_4_BYTE_ADDRESS_MODE     0xB7

#define SPI_FLASH_STATUS_REGISTER_BUSY          1
#define SPI_FLASH_PAGE_SIZE                     256
// ID for common flash sizes
#define ID_4M                                   0x15
#define ID_8M                                   0x16
#define ID_16M                                  0x17
#define ASYNCH_DMA_BYTE_POS                     (0)
typedef struct
{
    uint32_t firstData;
    uint32_t secondData;
} interleavedSpiTxRxData_t;
typedef struct
{
    uint8_t directMode;
    uint8_t asynchDMAUsartNumber;
    //uint16_t rxWord;
    uint32_t bufferStartAddress;  //address belonging to buffer. 4-byte aligned
    uint32_t currentReadIndex;      // current pointer
    uint32_t count;               // how many bytes we actually read.
    uint8_t rxBuffer[256 + 8];
    uint8_t padding[4];  //
    uint8_t mode;
    uint8_t addressIs32bit;
} interleavedSpiData_t;
extern interleavedSpiData_t interleavedSpiData;

static inline void interleavedSpiWaitDma(void)
{
  while ((LDMA->CHDONE & (3 << FIRST_SPI_LDMA_CH)) != (3 << FIRST_SPI_LDMA_CH));
}
static inline int interleavedSpiHasDmaFinished()
{
  return !((LDMA->CHDONE & (3 << FIRST_SPI_LDMA_CH)) != (3 << FIRST_SPI_LDMA_CH));
}

static inline uint8_t interleavedSpiFlashGetAsynchReadByteDMA(void)
{
  while (!(LDMA->CHDONE & (1 << (FIRST_SPI_LDMA_BYTE_CH + interleavedSpiData.asynchDMAUsartNumber))));
  return interleavedSpiData.rxBuffer[ASYNCH_DMA_BYTE_POS];
}

void interleavedSpiFlashInit();
void interleavedSpiFlashProgram(uint32_t address, uint8_t *buffer, uint32_t size);
uint32_t interleavedSpiFlashStartRead(uint32_t address, void *bufferAddress, uint32_t maxBlockSize);
void interleavedSpiFlashEraseTwoSectors(uint32_t logicalAddress);
void interleavedSpiFlashEraseTwo64kBlocks(uint32_t logicalAddress);
void interleavedSpiFlashEraseTwo32kBlocks(uint32_t logicalAddress);
int interleavedSpiFlashGetSize(void);
int interleavedSpiFlashGetDataMode(void);
void interleavedSpiFlashRestoreDataMode(void);
void interleavedSpiFlashChipErase(void);
uint8_t interleavedSpiFlashReadByteDMA(uint32_t address);
interleavedSpiTxRxData_t interleavedSpiRead(uint32_t firstData, uint32_t secondData);
interleavedSpiTxRxData_t interleavedSpiReadSameData(uint32_t data);

/**
 * @brief Read one byte from flash using DMA, asynchronously
 * @param address: flash address we need to read. Note, this is the address without the external flash address base!
 */
static inline void interleavedSpiFlashAsynchReadByteDMA(uint32_t address)
{
  FLASH_NCS_HIGH();
  EUSART_TypeDef * usart;
  // determine where is the data.
  int usartNumber = (address & 2) != 0;
  uint32_t flashAddress;
    if (interleavedSpiData.addressIs32bit)
    {
        if (usartNumber )
        {
            usart = SECOND_SPI_USART;//
            flashAddress = (address >> 1) - (address & 1) - 1;

        }
        else
        {
            usart = FIRST_SPI_USART;
            flashAddress = (address >> 1) - (address & 1);

        }
    }
    else
    {
        if (usartNumber )
        {
            flashAddress = ((address + 2) >> 1) - (address & 1);
            usart = SECOND_SPI_USART;//
        }
        else
        {
            usart = FIRST_SPI_USART;
            flashAddress =  2 + (address >> 1)  - (address & 1); //(address >> 1) + (address & 1) ;

        }
    }
  // disable usart if we were not already in this mode.
  if (!(interleavedSpiData.directMode & (1 << usartNumber)))
  {
    usart->EN = 0;
    LDMA->CHDIS = (15 << FIRST_SPI_LDMA_CH);
    PRS->ASYNC_SWLEVEL = 0; //(1 << DUAL_SPI_PRS_CH);
    interleavedSpiData.directMode |= 1 << usartNumber;
    while(usart->EN & 2);
    usart->EN = 1;
    usart->CMD = EUSART_CMD_TXEN | EUSART_CMD_RXEN;
    while ((usart->STATUS & (EUSART_STATUS_TXENS | EUSART_STATUS_RXENS)) != (EUSART_STATUS_TXENS | EUSART_STATUS_RXENS));
  }
  FLASH_NCS_LOW();
  __asm volatile ("cpsid i\r\n");

    if (interleavedSpiData.addressIs32bit)
    {
        usart->TXDATA = (SPI_FLASH_FAST_READ_DATA << 8) | (flashAddress >> 24);
        usart->TXDATA = flashAddress >> 8;
        usart->TXDATA = flashAddress << 8;
        usart->TXDATA = flashAddress << 8;  //we repeat this because it is quicker instead of writing 0.
        LDMA->CH[usartNumber + FIRST_SPI_LDMA_BYTE_CH].CTRL =  LDMA_CH_CTRL_DSTMODE_ABSOLUTE |
                                                                  LDMA_CH_CTRL_SRCMODE_ABSOLUTE |
                                                                  LDMA_CH_CTRL_DSTINC_NONE |
                                                                  LDMA_CH_CTRL_SIZE_HALFWORD |
                                                                  LDMA_CH_CTRL_SRCINC_NONE |
                                                                  LDMA_CH_CTRL_REQMODE_BLOCK |
                                                                  LDMA_CH_CTRL_BLOCKSIZE_UNIT1 |
                                                               //   LDMA_CH_CTRL_IGNORESREQ |
                                                                  ((4 - 1) <<_LDMA_CH_CTRL_XFERCNT_SHIFT) |
                                                                  LDMA_CH_CTRL_STRUCTTYPE_TRANSFER;

    }
    else
    {
        usart->TXDATA = (SPI_FLASH_FAST_READ_DATA << 8) | (flashAddress >> 16);
        usart->TXDATA = flashAddress;
        usart->TXDATA = flashAddress;
        LDMA->CH[usartNumber + FIRST_SPI_LDMA_BYTE_CH].CTRL =   LDMA_CH_CTRL_DSTMODE_ABSOLUTE |
                                                                LDMA_CH_CTRL_SRCMODE_ABSOLUTE |
                                                                LDMA_CH_CTRL_DSTINC_NONE |
                                                                LDMA_CH_CTRL_SIZE_HALFWORD |
                                                                LDMA_CH_CTRL_SRCINC_NONE |
                                                                LDMA_CH_CTRL_REQMODE_BLOCK |
                                                                LDMA_CH_CTRL_BLOCKSIZE_UNIT1 |
                                                                //   LDMA_CH_CTRL_IGNORESREQ |
                                                                ((3 - 1) <<_LDMA_CH_CTRL_XFERCNT_SHIFT) |
                                                                LDMA_CH_CTRL_STRUCTTYPE_TRANSFER;
    }
  LDMA->CHDONE_CLR = 15 << (FIRST_SPI_LDMA_CH);
  LDMA->CHEN_SET = 1 << (FIRST_SPI_LDMA_BYTE_CH + usartNumber);
  __asm volatile ("cpsie i\r\n");
  //
  interleavedSpiData.asynchDMAUsartNumber = usartNumber;
}
#endif /* SRC_INTERLEAVEDSPIFLASHL_H_ */
