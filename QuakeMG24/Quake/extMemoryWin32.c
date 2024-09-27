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
#if WIN32

#include "extMemoryWin32.h"
#include "quakedef.h"
#ifdef WIN32
uint8_t ext_memory[EXT_MEMORY_SIZE];
#else
uint8_t *ext_memory = (void*) 0x9000000;
#endif // WIN32
/*
typedef struct
{
    uint8_t *loadBufferPtr;          // whereto in RAM we are loading
    uint8_t *currentBufferPtr;       // where in flash the first buffer of the RAM points to
    uint16_t bytesInBuffer;                 // how many buffer in RAM
    uint16_t bufferSize;                    // how big is the buffer
} extMemData_t;
static extMemData_t extMemData = {NULL};
// this must be called every time we need to load, in a function, providing for instance a local buffer in RAM, or malloced
void extMemSetBuffer(uint8_t *buffer, uint16_t size)
{
    extMemData.loadBufferPtr = buffer;
    extMemData.currentBufferPtr = NULL;
    extMemData.bytesInBuffer = 0;
    extMemData.bufferSize = size;
}*/
#ifndef NULL
#define NULL  ((void*)0)
#endif
#if PROFILE_EXT_MEM_LOADS
    void countExtMemBytes(int size, int address)
    {
           bytesLoadedFromExtMem += size;
           if (address & 3)
               bytesLoadedUnalignedFromExtMem += size;
            extMemAccesses++;
    }
#endif
static uint8_t *currentAddress = NULL;
void extMemSetCurrentAddress(void *address)
{
    currentAddress = address;
}

void* extMemGetDataFromAddress(void *dest, void *source, unsigned int length)
{
    #if WIN32
        extMemSetCurrentAddress(source);
        memcpy(dest, currentAddress, length);
        currentAddress += length;
#if PROFILE_EXT_MEM_LOADS
     countExtMemBytes(length, source);
#endif
        return dest;
    #endif // WIN32

}
uint8_t extMemGetByteFromCurrentAddress(void)
{
    #if WIN32
        uint8_t b = *currentAddress;
#if PROFILE_EXT_MEM_LOADS
     countExtMemBytes(1, currentAddress );
#endif

        currentAddress++;
//        printf("b is %d (%c)\r\n", b, b);

        return b;
    #endif // WIN32
}
uint8_t extMemGetByteFromAddress(void *address)
{
    #if WIN32
        extMemSetCurrentAddress(address);
    #if PROFILE_EXT_MEM_LOADS
     countExtMemBytes(1,address);
#endif

        uint8_t b = *currentAddress;
        currentAddress++;

        return b;
    #endif // WIN32
}

void* extMemGetDataFromCurrentAddress(void *dest, unsigned int length)
{
    #if WIN32
#if PROFILE_EXT_MEM_LOADS
     countExtMemBytes(length, currentAddress);
#endif

        memcpy(dest, currentAddress, length);
        currentAddress += length;

        return dest;
    #endif // WIN32
}
// Asynch emulation
static int asyncSize = 0;
static void * asyncDest = NULL;
//static uint32_t asyncAddress = 0;
void * extMemStartAsynchDataRead(uint32_t address, void * dest, uint32_t cnt)
{
    asyncDest = dest;
    asyncSize = cnt;
    currentAddress = address;
    #if PROFILE_EXT_MEM_LOADS
        countExtMemBytes(cnt, address);
    #endif
    #define SIMULATE_DELAY 1
    #if !SIMULATE_DELAY
        memcpy(asyncDest, currentAddress, asyncSize);
        currentAddress = currentAddress + asyncSize;
        asyncSize = 0;
    #endif
    return dest;
}
void extMemWaitAsynchDataRead(void)
{
    if (asyncSize)
    {
        memcpy(asyncDest, currentAddress, asyncSize);
        currentAddress = currentAddress + asyncSize;
        asyncSize = 0;
    }
}
int extMemHasAsynchDataReadFinished(void)
{
    static int asyncDelaySimulation = 0;
    if (asyncSize == 0)
    {
        asyncDelaySimulation = 0;
        return 1;
    }
    if (asyncDelaySimulation)
    {
        if (asyncSize)
        {
        memcpy(asyncDest, currentAddress, asyncSize);
        currentAddress = currentAddress + asyncSize;
            asyncSize = 0;
            asyncDelaySimulation = 0;
        }
            return 1;

    }
    asyncDelaySimulation++;
    // simulate that we were not ready yet.
    return 0;
}
static uint8_t dmaByte;
uint8_t extMemGetDMAByte(void)
{
    return dmaByte;
}
void interleavedSpiFlashAsynchReadByteDMA(uint32_t address)
{
    dmaByte = extMemGetByteFromAddress(address);
}
void extMemProgram(uint32_t address, uint8_t *buffer, uint32_t size)
{
    address &= extMemGetSize() - 1;
    printf("Address is 0x%x, size is %d. First Data: %x\r\n", address, size, buffer[0]);
    if (address + size > extMemGetSize())
        FIXME("Attempt to write outside extmem!");
    memcpy(&ext_memory[address], buffer, size);
}
#endif
