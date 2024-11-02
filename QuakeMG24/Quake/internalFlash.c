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
#include "quakedef.h"
#include "internalFlash.h"
#if !WIN32
#include "memory_defs.h"
#endif
#if RETAIL_QUAKE_PAK_SUPPORT
    #pragma GCC optimize("Os") //
#endif
// Note: subject to change
#define DEBUG_INTERNAL_FLASH        0
#if DEBUG_INTERNAL_FLASH
    #define internalFlashDbgPrintf printf
#else
    #define internalFlashDbgPrintf(...)
#endif
#define LET_ME_JUST_WORK       1        // used in Windows to check how much flash we need.
#define CHECK_ALIGN(size)     if ((uint32_t)size & 3)  Sys_Error("Error, storing non word-aligned object (%d) at line %d", size, __LINE__);
#if WIN32
    #if LET_ME_JUST_WORK
  #define FLASH_SIZE (15360 * 1024)
    #else
  #define FLASH_SIZE (1536 * 1024)
    #endif // LET_ME_JUST_WORK

  uint8_t  internalFlash[FLASH_SIZE];
  static uint32_t pointer = APP_SIZE;
#else
    static uint32_t pointer = 0;
#endif // WIN32_T
static int commonSize = 0;
// called after common stuff has been initialized
void internalFlashSetCommonZone(void)
{
    commonSize = (pointer - APP_SIZE + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1);
}
void internalFlashInit(void)
{
    pointer = APP_SIZE;
    commonSize = 0;
}
int getInternalFlashRemaningSize(void)
{
    #if WIN32
    return 1024*1536 - pointer;
    #else
        return FLASH_SIZE - pointer;

    #endif
}
#if WIN32
void eraseInternalFlash(int sections)
{
    // do nothing
}
void *getCurrentInternalFlashPtr(void)
{
        return &internalFlash[pointer];
}
void *reserveInternalFlashSize(int size)
{
    CHECK_ALIGN(size);
    int oldPointer = pointer;
        pointer += size;
        return &internalFlash[oldPointer];
}
void * storeToInternalFlash2(void *buffer, int size, char *function, int line)
{
    // TODO: distinguish if buffer is on external flash.
    // TODO: if page is dirty, save and erase
    if (size & 3)
    {
            printf("Caching to flash. Current %d, requested %d, remaining %d (real: %d), Line %d, function %s\r\n", pointer, size, FLASH_SIZE - size - pointer, 1536 * 1024 - size - pointer, line, function);
        FIXME("UNALIGNED STORE TO INTERNAL FLASH!");

    }
    CHECK_ALIGN(size);
    printf("Caching to flash. Current %d, requested %d, remaining %d (real: %d), Line %d, function %s\r\n", pointer, size, FLASH_SIZE - size - pointer, 1536 * 1024 - size - pointer, line, function);
    if (size + pointer > FLASH_SIZE)
    {
        while (1)
        {
            FIXME("FLASH OVERFLOW");
        }
    }
    else
    {
        memcpy(&internalFlash[pointer], buffer, size);
    }
    uint8_t *ptr = &internalFlash[pointer];
    pointer += size;
    return ptr;
}
void * storeToInternalFlashAtPointer(void *buffer, void *flashPos, int size)
{
    CHECK_ALIGN(flashPos);
    CHECK_ALIGN(size);
    // TODO: distinguish if buffer is on external flash.
    // TODO: if page is dirty, save and erase
    printf("Storing %d bytes to position fixed flash %p. Better to be reserverd!\r\n", size, flashPos);
    memcpy(flashPos, buffer, size);
    return flashPos;
}

#else

#if USE_MSC
// MSC will eat ram.
void flashErasePage(uint32_t *pageAddress)
{
    __disable_irq();
    MSC_ErasePage(pageAddress);
    __enable_irq();
}
void programFlashWord(uint32_t *address, uint32_t word)
{
    if (*address == 0xFFFFFFFF)
    {
        __disable_irq();
        MSC_WriteWord(address, &word, 4 );
        __enable_irq();
    }
}
#else
__attribute__ ((section(".ram"), noinline)) void flashEraseCurrentPage()
{
    MSC->WRITECMD = MSC_WRITECMD_ERASEPAGE;
    while (!(MSC->IF & MSC_IF_ERASE))
        ;    // wait until erase operations is done
}
void flashErasePage(uint32_t *pageAddress)
{
    __disable_irq();
    // enable write
    MSC->WRITECTRL_SET = MSC_WRITECTRL_WREN;
    // set address
    MSC->ADDRB = (uint32_t) pageAddress & ~(FLASH_BLOCK_SIZE - 1);
    uint32_t status = MSC->STATUS;
    if (!(status & (MSC_STATUS_BUSY | MSC_STATUS_INVADDR | MSC_STATUS_LOCKED)))
    {
        // wait the power up sequence to be finished
        while (!(MSC->STATUS & MSC_STATUS_WREADY))
            ;
        // issue erase CMD
        flashEraseCurrentPage();
    }
    MSC->WRITECTRL_CLR = MSC_WRITECTRL_WREN;
    __enable_irq();
}
__attribute__ ((section(".ram"), noinline)) void flashProgramCurrentWord(uint32_t word)
{
    MSC->WDATA = word;
    while (!(MSC->STATUS & MSC_STATUS_WDATAREADY))
        ;    // wait until write operation is done
}
void programFlashWord(uint32_t *address, uint32_t word)
{
#if 1
    if (*address == 0xFFFFFFFF)
    {
        __disable_irq();
        MSC->LOCK = MSC_LOCK_LOCKKEY_UNLOCK;
        // enable write
        MSC->WRITECTRL_SET = MSC_WRITECTRL_WREN;
        // set address
        MSC->ADDRB = (uint32_t) address;
        uint32_t status = MSC->STATUS;
        if (!(status & (MSC_STATUS_BUSY | MSC_STATUS_INVADDR | MSC_STATUS_LOCKED)))
        {
            // wait the power up sequence to be finished
            while (!(MSC->STATUS & MSC_STATUS_WREADY))
                ;
            while (!(MSC->STATUS & MSC_STATUS_WDATAREADY))
                ;
            // issue erase CMD
            flashProgramCurrentWord(word);
        }
        MSC->WRITECTRL_CLR = MSC_WRITECTRL_WREN;
        __enable_irq();
    }
#else
    if (*address == 0xFFFFFFFF)
    {
        __disable_irq();
        MSC_WriteWord(address, &word, 4 );
        __enable_irq();
    }

#endif
}
#endif
/**
 * @brief Store a word to flash. It checks if erase must be triggered.
 *        In such a case, it will copy also the previous header values, and the
 *        data PAST the header region.
 * @param dest
 * @param word
 * @param flashRegion
 * @param isHeader
 */
#define PROCESS_ACTION_TIME_MICROSEC    100000UL
static void storeWordToFlash(uint32_t *dest, uint32_t word)
{
    dest = (uint32_t*) ((uint32_t) dest | FLASH_PTR_BASE); // make sure to add the upper flash byte.
        /*    static uint32_t lastProcessActionTime_us = 0;
         uint32_t timeNow = I_GetTimeMicrosecs();
         if (timeNow - lastProcessActionTime_us > PROCESS_ACTION_TIME_MICROSEC)
         {
         sl_system_process_action();
         lastProcessActionTime_us = I_GetTimeMicrosecs();
         }*/
    // first check if dest is compatible, i.e. is the same as source or it is erased
    if (!(*dest == word || *dest == 0xFFFFFFFF))
    {
        // we need to erase before writing.
        uint32_t pageAddress = ((uint32_t) dest) & ~(FLASH_BLOCK_SIZE - 1); // page that will be erased
        uint32_t startCopyAddress = pageAddress;
        uint32_t stopCopyAddress = (uint32_t) dest; // copy up to the previous word.
        // now that we know from where to where (stop non inclusive) we need to copy, we can allocate enough buffer
        // note! addresses are 4-byte aligned!
        uint32_t tmp[FLASH_PAGE_SIZE / sizeof(uint32_t)];
        for (uint32_t i = 0; i < (stopCopyAddress - startCopyAddress) / sizeof(uint32_t); i++)
        {
            tmp[i] = *((uint32_t*) startCopyAddress + i);
        }
        // erase
        internalFlashDbgPrintf("Erasing page 0x%08X Start Copy Addr 0x%08X Stop Copy Addr 0x%08X\r\n. ", pageAddress, startCopyAddress, stopCopyAddress);
        flashErasePage((uint32_t*) pageAddress);
        // write back everything
        for (uint32_t i = 0; i < (stopCopyAddress - startCopyAddress) / sizeof(uint32_t); i++)
        {
            programFlashWord(((uint32_t*) startCopyAddress + i), tmp[i]);
        }
    }
    // write word
    if (!(*dest == word))
    {
        if (*dest == 0xFFFFFFFF)
            programFlashWord(dest, word);
        else
        {
            printf("trying to overwrite a non blank word: addr: 0x%08X old: 0x%08X new 0x%08X. Blocking", (unsigned int) dest, (unsigned int) *dest,
                (unsigned int) word);
            while (1)
                ;
        }
    }
    //
}
/**
 * @brief write the buffer to the flash region
 */

////////////////////////////////
void* storeToInternalFlash(const void *buffer, int size)
{
    // TODO: distinguish if buffer is on external flash.
    // TODO: if page is dirty, save and erase
    if (size & 3)
    {
        FIXME("UNALIGNED...");
    }
    CHECK_ALIGN(size);
//    internalFlashDbgPrintf("Caching to flash. Current %d, requested %d, remaining %d (real: %d)\r\n", pointer, size, FLASH_SIZE - size - pointer, 1536 * 1024 - size - pointer);
    printf("FC. Add: %xh, rq: %xh, lf: %xh\r\n", (unsigned int) pointer, (unsigned int) size, (unsigned int) (FLASH_SIZE - size - pointer));

    if (size + pointer > FLASH_SIZE)
    {
        while (1)
        {
            FIXME("FLASH OVERFLOW");
        }
    }
    else
    {
        for (int i = 0; i < size / 4; i++)
        {
            if (isOnExternalFlash(buffer))
            {
                uint32_t data;
                extMemGetDataFromAddress(&data, (uint32_t*) buffer + i, sizeof(data));
                storeWordToFlash((uint32_t*) pointer + i, data);
            }
            else
            {
                storeWordToFlash((uint32_t*) pointer + i, ((uint32_t*) buffer)[i]);
            }
        }
    }
    uint8_t *ptr = (byte*) FLASH_PTR_BASE + pointer;
    pointer += size;
    return ptr;
}

void* storeToInternalFlashAtPointer(void *buffer, void *flashPos, int size)
{
    CHECK_ALIGN(flashPos);
    CHECK_ALIGN(size);
    // TODO: distinguish if buffer is on external flash.
    // TODO: if page is dirty, save and erase
    internalFlashDbgPrintf("Storing %d bytes to position fixed flash %p. Better to be reserverd!\r\n", size, flashPos);

    if (size + ((uint32_t) flashPos & 0xFFFFFF) > FLASH_SIZE)
    {
        while (1)
        {
            FIXME("FLASH OVERFLOW");
        }
    }
    else
    {
        for (int i = 0; i < size / 4; i++)
        {
            if (isOnExternalFlash(buffer))
            {
                uint32_t data;
                extMemGetDataFromAddress(&data, (uint32_t*) buffer + i, sizeof(data));
                storeWordToFlash((uint32_t*) flashPos + i, data);
            }
            else
            {
                storeWordToFlash((uint32_t*) flashPos + i, ((uint32_t*) buffer)[i]);
            }
        }
    }
    return flashPos;
}
void* getCurrentInternalFlashPtr(void)
{
    return (byte*) FLASH_PTR_BASE + pointer;
}
void* reserveInternalFlashSize(int size)
{
    CHECK_ALIGN(size);
    int oldPointer = pointer;
#if WIN32
        pointer += size;
        return &internalFlash[oldPointer];
#endif // WIN32
    pointer += size;
    for (unsigned int i = oldPointer; i < pointer; i += 4)
    {
        storeWordToFlash((uint32_t*) i, 0xFFFFFFFF);   // this will take care of erasing and restoring previous data.
    }
    return (byte*) FLASH_PTR_BASE + oldPointer;
}
///

#endif

void internalFlashResetToCommonZoneEnd(void)
{
    // sets the pointer to the end to common zone
    pointer = APP_SIZE + commonSize;
}

