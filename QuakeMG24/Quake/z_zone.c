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

 --------------------------------------------------------------------------

 This memory allocator is based on our previous project, which, in turn,
 is based on the original Id Software's code. See below old copyright notice
 and discussion.

 For Quake, we have made it even more optimized so that each block uses 4 Bytes.

 */
/**
 *  Doom Port to Silicon Labs EFR32xG24 devices and MGM240 modules
 *  by Nicola Wrachien (next-hack in the comments).
 *
 *  This port is based on the excellent doomhack's GBA Doom Port,
 *  with Kippykip additions.
 *
 *  Several data structures and functions have been optimized
 *  to fit in only 256kB RAM (GBA has 384 kB RAM).
 *  Z-Depth Light has been restored with almost no RAM consumption!
 *  Added BLE-based multiplayer.
 *  Added OPL2-based music.
 *  Restored screen melt effect!
 *  Tons of speed optimizations have been done, and the game now
 *  runs extremely fast, despite the much higher 3D resolution with
 *  respect to GBA.
 *
 *  PrBoom: a Doom port merged with LxDoom and LSDLDoom
 *  based on BOOM, a modified and improved DOOM engine
 *  Copyright (C) 1999 by
 *  id Software, Chi Hoang, Lee Killough, Jim Flynn, Rand Phares, Ty Halderman
 *  Copyright (C) 1999-2000 by
 *  Jess Haas, Nicolas Kalkhof, Colin Phipps, Florian Schulze
 *  Copyright 2005, 2006 by
 *  Florian Schulze, Colin Phipps, Neil Stevens, Andrey Budko
 *  Copyright (C) 2021-2023 Nicola Wrachien (next-hack in the comments)
 *  on the EFR32xG24 and MGM240 port.
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
 *      Zone Memory Allocation. Neat.
 *
 * Neat enough to be rewritten by Lee Killough...
 *
 * Must not have been real neat :)
 *
 * Made faster and more general, and added wrappers for all of Doom's
 * memory allocation functions, including malloc() and similar functions.
 *
 *
 * next-hack
 * Changed back to old Zone.c because it makes no sense to use malloc, which
 * also requires additional memory to store malloc'ed block information!
 * Removed unused tags to keep the structure at a minimum size.
 * Used short pointers and bitfields to reduce overhead to 8 bytes/block instead
 * of 20 + malloc overhead (typically 8).
 * 2022-03-19: changed to get an unified allocator for pool and single block,
 * chunk size is 4. Some bytes saved.
 *-----------------------------------------------------------------------------
 */
#ifdef CPLUSPLUS
#error
#endif

#include "quakedef.h"
#if !WIN32
#include "memory_defs.h"
#endif
#define ZONE_ENTER_CRITICAL()
#define ZONE_EXIT_CRITICAL()
//#include "z_zone.h" included by quakedef.h
// Minimum chunk size at which blocks are allocated.
#define CHUNK_SIZE 4
#define MEM_ALIGN CHUNK_SIZE
#if WIN32
#define ZMALLOC_STAT 1
#else
#define ZMALLOC_STAT 0
#endif
// End Tunables
#if ZMALLOC_STAT
int numblocks = 0;
static int largest_occupied = 0;
#endif

static const int HEADER_SIZE = (sizeof(memblock_t) + CHUNK_SIZE - 1) & ~(CHUNK_SIZE - 1);

static int free_memory = 0;

typedef struct
{
    // start / end cap for linked list
    memblock_t blocklist;

    // total bytes malloced, including header
    //int size;

    memblock_t *rover;

} memzone_t;

__attribute__ ((aligned (CHUNK_SIZE)))  uint8_t staticZone[MAX_STATIC_ZONE];

memzone_t *mainzone;
#if MAX_STATIC_ZONE < 262144 && MAX_STATIC_ZONE >= 65536
  extern inline unsigned short getShortPtr(void *longPtr);
#endif
uint32_t getStaticZoneSize(void)
{
  return sizeof(staticZone);
}
void* I_ZoneBase(int *size)
{
    *size = sizeof(staticZone);
    return staticZone;
}
#if MAX_STATIC_ZONE < 262144
// returns short pointer relative to static zone
static inline uint16_t zoneGetShortPtr(void *ptr)
{
    if (NULL == ptr)
        return 0;
#if MAX_STATIC_ZONE < 131072 - 4
    else if (ptr == &mainzone->blocklist)
         return 0x7FFF;
#else
    else if (ptr == &mainzone->blocklist)
        return 0xFFFF;
#endif
    else
    {
        uint32_t r;
        r = ((byte*)ptr - (byte*)staticZone);
        return r / 4;
    }
}
static void* zoneGetLongPtr(uint16_t shortPtr)
{
    if (0 == shortPtr)
        return NULL;
#if MAX_STATIC_ZONE < 131072 - 4
    else if (0x7FFF == shortPtr)
        return &mainzone->blocklist;
#else
   else if (0xFFFF == shortPtr)
        return &mainzone->blocklist;
#endif
    else
        return ((byte*)staticZone + ((unsigned int)shortPtr * 4));
}
#endif
static void setMemblockNext( memblock_t *block,  memblock_t *next)
{
#if MAX_STATIC_ZONE < 262144
    block->next_sptr = zoneGetShortPtr(next);
#else
    block->next = next;
#endif
}
static void setMemblockPrev( memblock_t *block,  memblock_t *prev)
{
#if MAX_STATIC_ZONE < 262144
    block->prev_sptr = zoneGetShortPtr(prev);
#else
    block->prev = prev;
#endif // MAX_STATIC_ZONE
}
static inline memblock_t* getMemblockPrev(memblock_t *mb)
{
    #if MAX_STATIC_ZONE < 262144
        return (memblock_t*) zoneGetLongPtr(mb->prev_sptr);
    #else
        return mb->prev;
    #endif
}
static inline void** getMemblockUser(memblock_t *mb)
{
    #if MAX_STATIC_ZONE < 262144 && MAX_STATIC_ZONE >= 131072 - 4
    #if !WIN32
        return (void**) getLongPtr(mb->user_spptr);
    #endif
    #elif MAX_STATIC_ZONE >= 262144
        return mb->user;
    #else
        (void) mb;
        return 0;
    #endif
}
static inline memblock_t* getMemblockNext(memblock_t *mb)
{
#if MAX_STATIC_ZONE < 262144
    return (memblock_t*) zoneGetLongPtr(mb->next_sptr);
#else
    return mb->next;
#endif
}
static inline uint32_t getMemblockSize(memblock_t *mb)
{
#if MAX_STATIC_ZONE < 262144
    uint8_t *next = (uint8_t*) getMemblockNext(mb);
    if ((uint32_t) next < (uint32_t) mb)
    {
        return (uint32_t) staticZone + sizeof(staticZone) - (uint32_t) mb;
    }
    return (uint32_t) next - (uint32_t) mb;
#else
    uint8_t *next = (uint8_t*) getMemblockNext(mb);
    //if ((uint32_t) next < (uint32_t) mb)
    if (((uint8_t*) next - (uint8_t *) mb) < 0)
    {
//        return (uint32_t) staticZone + sizeof(staticZone) - (uint32_t) mb;

        return (uint32_t)((uint8_t*) staticZone + sizeof(staticZone) - (uint8_t*) mb);

    }
    return ((uint8_t*) next - (uint8_t *) mb);
#endif
}
void zmallocTest()
{
    #if 0
    byte *test, *test2;

    test2 = Z_Malloc(1200);
    test = Z_Malloc(26000);

    Z_Free(test2);
    byte *p = test;
    memblock_t *block = (memblock_t*) ((char*) p - HEADER_SIZE);
    printf("Size is:  %d next is %d", getMemblockSize(block), getMemblockSize(getMemblockNext(block)));
    FIXME("MEMTEST");
    #endif
}

static void setMemblockUser(memblock_t *block, void *user)
{
#if MAX_STATIC_ZONE < 262144 && MAX_STATIC_ZONE >= 65536
  #if !WIN32
    block->user_spptr = getShortPtr(user);
   #endif
#elif MAX_STATIC_ZONE >= 262144
    block->user = user;
#else
    (void) block;
    (void) user;
#endif
}
//
// Z_Init
//
void Z_Init(void)
{
    printf("Z-Zone size: %d bytes\r\n", MAX_STATIC_ZONE);
    memblock_t *block;
    int size;

    memset(staticZone, 0, sizeof(staticZone));

    mainzone = (memzone_t*) I_ZoneBase(&size);
   // mainzone->size = size;
    // set the entire zone to one free block
    block = (memblock_t*) ((byte*) mainzone + sizeof(memzone_t));

// mainzone->blocklist.next_sptr = mainzone->blocklist.prev_sptr = getShortPtr(block);
    setMemblockNext(&(mainzone->blocklist), block);


//    mainzone->blocklist.user_spptr = getShortPtr((void*) mainzone);
    setMemblockUser(&(mainzone->blocklist), mainzone);

    mainzone->blocklist.tag = PU_STATIC;
    mainzone->rover = block;

//    block->prev_sptr = block->next_sptr = getShortPtr(&mainzone->blocklist);
    setMemblockPrev(block, &(mainzone->blocklist));
    setMemblockNext(block, &(mainzone->blocklist));

    // free block
    block->tag = PU_FREE;

}

//
// Z_Malloc
// You can pass a NULL user if the tag is < PU_PURGELEVEL.
//
#define MINFRAGMENT     32

void* Z_Malloc2(uint32_t size, int tag, void **user, const char *sz, int canFail)
{
        #if WIN32 && MAX_STATIC_ZONE > 262144 && USE_MALLOC
        return (malloc)(size);
    #endif // WIN32
#if !ZMALLOC_STAT
  (void) sz;
#else
    printf("Zmalloc: size %d\r\n", size);
#endif
    int extra;
    memblock_t *start;
    memblock_t *rover;
    memblock_t *newblock;
    memblock_t *base;
    void *result;

    if (!size)
        return user ? *user = NULL : NULL;           // malloc(0) returns NULL

    ZONE_ENTER_CRITICAL();

    size = (size + MEM_ALIGN - 1) & ~(MEM_ALIGN - 1);

    // scan through the block list,
    // looking for the first free block
    // of sufficient size,
    // throwing out any purgable blocks along the way.

    // account for size of block header
    size += sizeof(memblock_t);

    // if there is a free block behind the rover,
    //  back up over them
    base = mainzone->rover;

    if (getMemblockPrev(base)->tag == PU_FREE)
        base = getMemblockPrev(base);

    rover = base;
    start = getMemblockPrev(base);

    do
    {
        if (rover == start)
        {
            // scanned all the way around the list. Fail if cannot fail.
            printf("Z_Malloc: failed on allocation of %i bytes", (int) size);
            if (!canFail)
            while (1);
            return NULL;
        }
        if (rover->tag != PU_FREE)
        {
            if (rover->tag < PU_PURGELEVEL)
            {
                // hit a block that can't be purged,
                // so move base past it
                base = rover = getMemblockNext(rover);
            }
            else
            {
                // free the rover block (adding the size to base)

                // the rover can be the base block
                base = getMemblockPrev(base);
                Z_Free((byte*) rover + sizeof(memblock_t));
                base = getMemblockNext(base);
                rover = getMemblockNext(base);
            }
        }
        else
        {
            rover = getMemblockNext(rover);
        }
//        printf("nextblk\r\n");
    } while (base->tag != PU_FREE || getMemblockSize(base) < size);

    // found a block big enough
    extra = getMemblockSize(base) - size;

    if (extra > MINFRAGMENT)
    {
        // there will be a free fragment after the allocated block
        newblock = (memblock_t*) ((byte*) base + size);
        newblock->tag = PU_FREE;
        setMemblockUser(newblock, NULL);
        setMemblockPrev(newblock, base);
        setMemblockNext(newblock, getMemblockNext(base));
        setMemblockPrev(getMemblockNext(newblock), newblock);
        setMemblockNext(base, newblock);
    }
    free_memory -= getMemblockSize(base);
    //
    if (user == NULL && tag >= PU_PURGELEVEL)
    {
        printf("Z_Malloc: an owner is required for purgable blocks");
        while (1);
    }
    setMemblockUser(base, user);
    base->tag = tag;

    result = (void*) ((byte*) base + sizeof(memblock_t));

    if (user)                   // if there is a user
        *user = result;            // set user to point to new block

    // next allocation will start looking here
    mainzone->rover = getMemblockNext(base);
#if ZMALLOC_STAT
    numblocks++;
    if (free_memory < largest_occupied)
        largest_occupied = free_memory;
#endif

    ZONE_EXIT_CRITICAL();
#if ZMALLOC_STAT
    printf("Mall: num %d, occ. %d lrgst %d Addr %04x. BlkSz %d %s\r\n", numblocks, -free_memory, -largest_occupied, base, getMemblockSize(base), sz);
#endif

    return result;
}

void (Z_Free)(void *p)
{
    #if WIN32 && MAX_STATIC_ZONE > 262144 && USE_MALLOC
        (free)(p);
        return;
    #endif // WIN32

    if (!p)
        return;

    ZONE_ENTER_CRITICAL();

    memblock_t *block = (memblock_t*) ((char*) p - HEADER_SIZE);

    if (getMemblockUser(block) && block->tag != PU_FREE && block->tag != PU_POOL) // Nullify user if one exists
    {
        printf("Nullifying\r\n");
        *(getMemblockUser(block)) = NULL;
    }
    // free memory
    size_t freedBlockSize = getMemblockSize(block);
    free_memory += freedBlockSize;

    // mark this block as free
    block->tag = PU_FREE;
    setMemblockUser(block, NULL);
    //
    memblock_t *other = getMemblockPrev(block);
    //
    if (other->tag == PU_FREE)
    {
        // merge with previous free block
        //other->next_sptr = block->next_sptr;
        setMemblockNext(other, getMemblockNext(block));
        //getMemblockNext(other)->prev_sptr = getShortPtr(other);
        setMemblockPrev(getMemblockNext(other), other);
        if (block == mainzone->rover)
            mainzone->rover = other;

        block = other;
    }

    other = getMemblockNext(block);
    if (other->tag == PU_FREE)
    {
        // merge the next free block onto the end
        //block->next_sptr = other->next_sptr;
        setMemblockNext(block, getMemblockNext(other));
//        getMemblockNext(block)->prev_sptr = getShortPtr(block);
        setMemblockPrev(getMemblockNext(block), block);
        if (other == mainzone->rover)
            mainzone->rover = block;
    }
#if ZMALLOC_STAT
    numblocks--;
#endif
    ZONE_EXIT_CRITICAL();
#if ZMALLOC_STAT
    printf("Free: num: %d, occ. %d lrgst %d Addr %04x. BlkSz %d\r\n", numblocks, -free_memory, -largest_occupied, (byte*) block - (byte*)staticZone, freedBlockSize);
#endif

}

void Z_FreeTags(int lowtag, int hightag)
{
    memblock_t *block;
    memblock_t *next;
    ZONE_ENTER_CRITICAL();

    for (block = getMemblockNext(&mainzone->blocklist); block != &mainzone->blocklist; block = next)
    {
        // get link before freeing
        next = getMemblockNext(block);

        // free block?
        if (block->tag == PU_FREE)
            continue;

        if (block->tag >= lowtag && block->tag <= hightag)
            Z_Free((byte*) block + sizeof(memblock_t));
    }
    ZONE_EXIT_CRITICAL();
}

void* (Z_Realloc)(void *ptr, size_t n, int tag, void **user)
{
    ZONE_ENTER_CRITICAL();
    void *p = Z_MallocOld(n, tag, user );
    if (ptr)
    {
        memblock_t *block = (memblock_t*) ((char*) ptr - HEADER_SIZE);
        memcpy(p, ptr, n <= getMemblockSize(block) ? n : getMemblockSize(block));
        (Z_Free)(ptr);
        if (user) // in case Z_Free nullified same user
            *user = p;
    }
    ZONE_EXIT_CRITICAL();
    return p;
}

void* (Z_Calloc)(size_t n1, size_t n2, int tag, void **user)
{
    void *r;
    ZONE_ENTER_CRITICAL();
    r = (n1 *= n2) ? memset(Z_Malloc2(n1, tag, user, "ZC", false), 0, n1) : NULL;
    ZONE_EXIT_CRITICAL();
    return r;
}
void* (Z_CallocFailable)(size_t n1, size_t n2, int tag, void **user)
{
    void *r;
    ZONE_ENTER_CRITICAL();
    n1 *= n2;
    if (!n1)
        r = NULL;
    else
    {
        r = Z_Malloc2(n1, tag, user, "ZCF", true);
        if (r)
            memset(r, 0, n1);
    }
    ZONE_EXIT_CRITICAL();
    return r;
}

char* (Z_Strdup)(const char *s, int tag, void **user)
{
    char *r;
    ZONE_ENTER_CRITICAL();
    r = strcpy(Z_MallocOld(strlen(s) + 1, tag, user), s);
    ZONE_EXIT_CRITICAL();
    return r;
}
//
