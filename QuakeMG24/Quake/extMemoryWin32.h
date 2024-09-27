/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments)
 on EFR32MG24 and MGM240 port.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

 See the GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

 */
#ifndef EXTMEMORYWIN32_H
#define EXTMEMORYWIN32_H
#if WIN32
#include <stdint.h>
#define USE_EXT_MEMORY 1
#ifdef WIN32
#define EXT_MEMORY_SIZE (32 * 1024 * 1024)
#define extMemGetSize() EXT_MEMORY_SIZE
#define EXT_MEMORY_PAGE_SIZE    4096
extern uint8_t ext_memory[EXT_MEMORY_SIZE];
void extMemProgram(uint32_t address, uint8_t *buffer, uint32_t size);
static inline int isOnExternalFlash(void *address)
{
    return ( (uint64_t) address >=  (uint64_t) ext_memory && (uint64_t) address < (uint64_t) ext_memory + EXT_MEMORY_SIZE);
}
static inline int extMemGetRemainingBytes(void)
{
    return 0;
}
static inline void extMemErase(uint32_t address, uint32_t size)
{
    address &= EXT_MEMORY_SIZE - 1;
    size = (size + EXT_MEMORY_PAGE_SIZE) & ~( EXT_MEMORY_PAGE_SIZE - 1);
    address &=  ~( EXT_MEMORY_PAGE_SIZE - 1);
    memset (&ext_memory[address], 0xFF, size);
}
#define EXT_MEM_BYTE_TIME   1
#define EXT_MEM_ACCESS_TIME 65
static inline void extMemStopDMA(void)
{

}
uint8_t extMemGetDMAByte(void);
#else
extern uint8_t *ext_memory;
#endif
#else
#include "extMemory.h"
#endif
#endif // EXT_MEMORY_H
