/***************************************************************************//**
 * @file extMemory.h
 * @brief Wrapper for various external memory organization support.
 *
 * This is used to support external memory, even if it is not memory mapped.
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
#include "extMemory.h"

#if EXT_MEMORY_TYPE == EXT_MEMORY_TYPE_INTERLEAVED_SPI
#pragma GCC optimize("Ofast")
void* extMemGetDataAligned(void *dest, unsigned int length)
{
  uint32_t bytesToRead;
  uint32_t bytesRead = 0;
  interleavedSpiData.directMode = 0;
  while (bytesRead < length)
  {
    bytesToRead = (length - bytesRead);
    if (2048 * 4 <= bytesToRead)
    {
      bytesToRead = 2048 * 4 - EXT_MEMORY_HEADER_SIZE;
    }
    interleavedSpiFlashStartRead((uint32_t) currentSpiAddress, (uint8_t*) dest + bytesRead, (bytesToRead + 3) & ~3);
    interleavedSpiWaitDma();
    bytesRead += bytesToRead;
    currentSpiAddress += bytesToRead;
  }
  return dest;

}
void extMemStopDMA(void)
{
  LDMA->CHDIS = (15 << FIRST_SPI_LDMA_CH);
  while(LDMA->CHSTATUS & (15 << FIRST_SPI_LDMA_CH));
  LDMA->CHDONE = 3 << FIRST_SPI_LDMA_CH;
}
// Erase external memory.
void extMemErase(uint32_t address, uint32_t size)
{
  // first erase as many as 32k sectors as possible.
  uint32_t numBlocks = size / (2 * SPI_FLASH_32K_BLOCK_SIZE);
  for (uint32_t b = 0; b < numBlocks; b++)
  {
    interleavedSpiFlashEraseTwo32kBlocks((address) & SPI_ADDRESS_MASK);
    address +=  2 * SPI_FLASH_32K_BLOCK_SIZE;
    size -= 2 * SPI_FLASH_32K_BLOCK_SIZE;
  }
  //
  // Now erase the remainder. With a minimum size of SPI_FLASH_SECTOR_SIZE
  uint32_t numSectors = (size + 2 * SPI_FLASH_SECTOR_SIZE - 1) / ( 2 * SPI_FLASH_SECTOR_SIZE) ;
  for (uint32_t s = 0; s < numSectors; s++)
  {
    interleavedSpiFlashEraseTwoSectors((address) & SPI_ADDRESS_MASK);
    address += SPI_FLASH_SECTOR_SIZE * 2;
  }
}
void extMemWrite(uint32_t address, void *buffer, uint32_t size)
{
    extMemErase(address, size);
    // note: when we are executing this, we are sure that all pending read operations for QSPI have ended.
    //
    interleavedSpiFlashProgram(address & SPI_ADDRESS_MASK, buffer, size);
    // put again in dual mode
}

int extMemGetRemainingBytes(void)
{
  int hWordsCh0, hWordsCh1;
  hWordsCh0 = ((LDMA->CH[FIRST_SPI_LDMA_CH].CTRL & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);
  hWordsCh1 = ((LDMA->CH[FIRST_SPI_LDMA_CH + 1].CTRL & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT);
  if (hWordsCh0 < hWordsCh1)
    hWordsCh0 = hWordsCh1;
  return 4 * (hWordsCh0 + 1); // should be +1 ?
}

#endif
