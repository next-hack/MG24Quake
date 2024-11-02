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
#ifndef INTERNAL_FLASH_H
#define INTERNAL_FLASH_H
#define PAGE_SIZE 8192
#if WIN32
  #define APP_SIZE    (((78*8192) + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))
#else
    #define APP_SIZE    (((FLASH_CODE_SIZE & (0xFFFFFF))  + PAGE_SIZE - 1)  & ~(PAGE_SIZE - 1))
#endif
void eraseInternalFlash(int sections);
void *getCurrentInternalFlashPtr(void);
void *reserveInternalFlashSize(int size);
void internalFlashResetToCommonZoneEnd(void);
void internalFlashInit(void);
void internalFlashSetCommonZone(void);
void * storeToInternalFlashAtPointer(void *buffer, void *flashPos, int size);
int getInternalFlashRemaningSize(void);
#if WIN32
void * storeToInternalFlash2(void *buffer, int size, char *function, int line);
#define storeToInternalFlash(b, s) storeToInternalFlash2(b, s, __FUNCTION__, __LINE__)
#define __flashSize  APP_SIZE
#else
void * storeToInternalFlash(const void *buffer, int size);
#endif
#endif // INTERNAL_FLASH_H
