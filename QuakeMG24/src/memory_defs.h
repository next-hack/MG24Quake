/**
 *  Copyright (C) 2023-2024 by Nicola Wrachien (next-hack in the comments)
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
 * DESCRIPTION:
 * next-hack: 16-bit pointers utility functions and memory region definitions
 */

#ifndef MEMORY_DEFS_H_
#define MEMORY_DEFS_H_
#include <stdint.h>

#define RAM_PTR_BASE                0x20000000UL
#define EXT_FLASH_BASE              0x40000000   // next-hack: changed to 0x40000000 to support up to 1GB external flash
#define FLASH_PTR_BASE              0x08000000
#define AUX_RAM_ADDRESS_BASE        0xB0000000
//
#define FLASH_BLOCK_SIZE 8192
//
#define PAK_ADDRESS                           ((uint8_t*)(EXT_FLASH_BASE + 4))
extern uint8_t                                *ext_memory;
extern uint32_t __flashSize[];                // not really an array!
#define FLASH_CODE_SIZE                       ( (((uint32_t) __flashSize) + FLASH_BLOCK_SIZE - 1 ) & ~(FLASH_BLOCK_SIZE - 1))
#if (FLASH_CODE_KB * 1024) & (FLASH_BLOCK_SIZE - 1)
#error FLASH_CODE_KB not multiple of 8kB
#endif
#define FLASH_ADDRESS                         (FLASH_PTR_BASE + FLASH_CODE_SIZE)
#ifndef FLASH_SIZE
  #define FLASH_SIZE           (1536 * 1024)
#endif
#define FLASH_CACHE_REGION_SIZE ((FLASH_SIZE - FLASH_CODE_SIZE))

//
#define DEBUG_GETSHORTPTR 0
//
#define isOnExternalFlash(a) ((((uint32_t) (a)) & EXT_FLASH_BASE) == EXT_FLASH_BASE)
//
static inline void* getLongPtr(unsigned short shortPointer)
{ // Special case: short pointer being all 0 => NULL
    if (!shortPointer)
        return 0;
    return (void*) (((unsigned int) shortPointer << 2) | RAM_PTR_BASE);
}
static inline unsigned short getShortPtr(void *longPtr)
{
#if 0
    if ((uint32_t) longPtr & 0x2)
        printf("Error Long Ptr %p\r\n", longPtr);
#endif
    return ((unsigned int) longPtr) >> 2;
}
#endif
