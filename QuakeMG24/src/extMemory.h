/***************************************************************************//**
 * @file extMemory.h
 * @brief Wrapper for various external memory organization support.
 *
 * This is used to support external memory, even if it is not memory mapped.
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
 *
 ******************************************************************************/
#ifndef SRC_EXTMEMORY_H_
#define SRC_EXTMEMORY_H_
//
#include <string.h>
#include "boards.h"

// for now we use only interleaved SPI
#if EXT_MEMORY_TYPE == EXT_MEMORY_TYPE_INTERLEAVED_SPI
#include "interleavedSpiFlash.h"
#define EXT_MEM_BYTE_TIME                      1
#define EXT_MEM_ACCESS_TIME                    65
static inline void extMemSetCurrentAddress(uint32_t address);
#define EXT_MEM_USES_EUSART0                   1
#define EXT_MEM_USES_EUSART1                   1
//
// To decrease latency, we do not use two DMA descriptors, so we start filling
// the read buffer already when we send the read command, followed by the address.
// this means that 4+4 bytes (command + 3 bytes address, one per chip) are
// rubbish.
#define EXT_MEMORY_HEADER_SIZE                  0//8
#define EXT_MEMORY_READ_ALIGN_SIZE              4
//

extern uint8_t *currentSpiAddress;
//
static inline uint8_t extMemGetByteFromAddress(const void *addr);
static inline void* extMemGetDataFromCurrentAddress(void *dest, unsigned int length);
void extMemWrite(uint32_t address, void *buffer, uint32_t size);
void extMemErase(uint32_t address, uint32_t size);
//
static inline short extMemFlashGetShortFromAddress(const void *addr)
{
// NOTE:  deprecated unoptimized function, do not use, code should be modified.
    addr = (void *) ((uint32_t) addr & SPI_ADDRESS_MASK);
    interleavedSpiFlashStartRead((uint32_t) addr, interleavedSpiData.rxBuffer, 2);
    interleavedSpiWaitDma();
    short *b  = (short*) &interleavedSpiData.rxBuffer[((uint32_t) addr & 3) + EXT_MEMORY_HEADER_SIZE];
    currentSpiAddress = 2 + (void*) addr;
    return *b;
}
static inline uint8_t extMemGetByteFromAddress(const void *addr)
{
/*  // NOTE:  deprecated unoptimized function, do not use, code should be modified.
  addr = (void *) ((uint32_t) addr & SPI_ADDRESS_MASK);
  interleavedSpiFlashStartRead((uint32_t) addr, interleavedSpiData.rxBuffer, 1);
  interleavedSpiWaitDma();
  uint8_t *b  = &interleavedSpiData.rxBuffer[((uint32_t) addr & 3) + EXT_MEMORY_HEADER_SIZE];
  currentSpiAddress = 1 + (void*) addr;*/
  currentSpiAddress = (uint8_t*) addr + 1;
  return interleavedSpiFlashReadByteDMA((uint32_t) addr);
}
/**
 * This function will read data and copy to specified buffer. It is not meant to be optimized, but it can support any amount of data.
 * @param dest
 * @param length
 */
static inline void* extMemGetDataFromCurrentAddress(void *dest, unsigned int length)
{
  if (!length)
    return dest;
  if (!((uint32_t)currentSpiAddress & 3) && !(length & 3))
  {
    return extMemGetDataAligned(dest, length);
  }
  uint32_t bytesToRead;
  uint32_t bytesRead = 0;

  // align to word boundary.
  if ((uint32_t)currentSpiAddress & 3)
  {
      // read 4 bytes.
      interleavedSpiFlashStartRead( (uint32_t) currentSpiAddress & ~3, interleavedSpiData.rxBuffer, 4);
      bytesToRead =  4 - ((uint32_t)currentSpiAddress & 3);
      if (bytesToRead > length)
        bytesToRead = length;
      interleavedSpiWaitDma();
      // copy read data
      memcpy(dest, &interleavedSpiData.rxBuffer[((uint32_t)currentSpiAddress & 3)], bytesToRead);
      //
      bytesRead += bytesToRead;
      // add offset to dest
//      this is wrong if lenght is small or the offset is odd     currentSpiAddress = ((uint32_t) currentSpiAddress + 3) & ~3;
      currentSpiAddress += bytesToRead ;
  }
  while (bytesRead < length)
  {
    bytesToRead = (length - bytesRead);
    if (sizeof(interleavedSpiData.rxBuffer) - EXT_MEMORY_HEADER_SIZE < bytesToRead)
    {
      bytesToRead = sizeof(interleavedSpiData.rxBuffer) - EXT_MEMORY_HEADER_SIZE;
    }
    interleavedSpiFlashStartRead((uint32_t) currentSpiAddress, interleavedSpiData.rxBuffer, (bytesToRead + 3) & ~3);
    interleavedSpiWaitDma();
    uint8_t *b  = &interleavedSpiData.rxBuffer[((uint32_t) currentSpiAddress & 3) + EXT_MEMORY_HEADER_SIZE];
    memcpy(dest + bytesRead, b, bytesToRead);
    bytesRead += bytesToRead;
    currentSpiAddress += bytesToRead;
  }
  return dest;
}
static inline void* extMemGetDataFromAddress(void *dest, void *src, unsigned int length)
{
  extMemSetCurrentAddress((uint32_t) src);
  return extMemGetDataFromCurrentAddress(dest, length);
}
static inline void extMemSetCurrentAddress(uint32_t address)
{
  currentSpiAddress = (uint8_t*) ((uint32_t) address & SPI_ADDRESS_MASK);
}
static inline int extMemGetSize(void)
{
  return interleavedSpiFlashGetSize();
}
static inline void * extMemStartAsynchDataRead(uint32_t address, void * dest, uint32_t cnt)
{
  address = ((uint32_t) address & SPI_ADDRESS_MASK);
  interleavedSpiFlashStartRead(address, (uint8_t*)dest, cnt);
#if TEST_DISABLE_ASYNCH_LOAD
#warning ASynch read disabled! This will impact performance!
    // if TEST_ASYNCH_SPEED is non 0, it means we don't want to use asynch loading, to test how slow it is (to compare the frame rate with what's achieved when enabled)
    while ((LDMA->CHDONE & (3 << FIRST_SPI_LDMA_CH)) != (3 << FIRST_SPI_LDMA_CH));
#endif
  uint32_t alignment = address & 0x3;
  return dest + EXT_MEMORY_HEADER_SIZE + alignment;
}
static inline void extMemWaitAsynchDataRead(void)
{
  interleavedSpiWaitDma();
}
static inline void extMemRestoreInterface(void)
{
  interleavedSpiFlashRestoreDataMode();
  //
#if SHARED_USART_INTERFACE == SHARED_EUSART0
  GPIO->EUSARTROUTE[FIRST_SPI_NUMBER].TXROUTE = ((uint32_t) FIRST_FLASH_SPI_MOSI_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT) | (FIRST_FLASH_SPI_MOSI_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[FIRST_SPI_NUMBER].RXROUTE = ((uint32_t) FIRST_FLASH_SPI_MISO_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT) | (FIRST_FLASH_SPI_MISO_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[FIRST_SPI_NUMBER].SCLKROUTE = ((uint32_t) FIRST_FLASH_SPI_CLK_PORT << _GPIO_EUSART_SCLKROUTE_PORT_SHIFT) | (FIRST_FLASH_SPI_CLK_PIN << _GPIO_EUSART_SCLKROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[FIRST_SPI_NUMBER].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN | GPIO_EUSART_ROUTEEN_SCLKPEN;
  // re enable back LDMA
  LDMA->CHEN_SET = (1 << FIRST_SPI_LDMA_CH);
#else
  GPIO->EUSARTROUTE[SECOND_SPI_NUMBER].TXROUTE = ((uint32_t) SECOND_FLASH_SPI_MOSI_PORT << _GPIO_EUSART_TXROUTE_PORT_SHIFT) | (SECOND_FLASH_SPI_MOSI_PIN << _GPIO_EUSART_TXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[SECOND_SPI_NUMBER].RXROUTE = ((uint32_t) SECOND_FLASH_SPI_MISO_PORT << _GPIO_EUSART_RXROUTE_PORT_SHIFT) | (SECOND_FLASH_SPI_MISO_PIN << _GPIO_EUSART_RXROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[SECOND_SPI_NUMBER].SCLKROUTE = ((uint32_t) SECOND_FLASH_SPI_CLK_PORT << _GPIO_EUSART_SCLKROUTE_PORT_SHIFT) | (SECOND_FLASH_SPI_CLK_PIN << _GPIO_EUSART_SCLKROUTE_PIN_SHIFT);
  GPIO->EUSARTROUTE[SECOND_SPI_NUMBER].ROUTEEN = GPIO_EUSART_ROUTEEN_TXPEN | GPIO_EUSART_ROUTEEN_RXPEN | GPIO_EUSART_ROUTEEN_SCLKPEN;
  // re enable back LDMA
  LDMA->CHEN_SET = (1 << SECOND_SPI_LDMA_CH);
#endif
  // set LDMA done to avoid deadlock
  LDMA->CHDONE_SET = (3 << FIRST_SPI_LDMA_CH);
  //

}
static inline void extMemInit(void)
{
  interleavedSpiFlashInit();
}
static inline void extMemEraseAll(void)
{
  interleavedSpiFlashChipErase();
}
static inline void extMemProgram(uint32_t address, uint8_t *buffer, uint32_t size)
{
  interleavedSpiFlashProgram(address, buffer, size);
}
static inline int extMemHasAsynchDataReadFinished(void)
{
  return interleavedSpiHasDmaFinished();
}
void extMemStopDMA(void);
int extMemGetRemainingBytes(void);
#else
#error
#endif



#endif /* SRC_EXTMEMORY_H_ */
