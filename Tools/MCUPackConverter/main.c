/*
 * MCUPackConverter By Nicola Wrachien (next-hack in comments)
 *
 * Copyright (C) 2023-2024, Nicola Wrachien
 *
 * This program will convert the Quake PAK files to a format, which is more optimized for MCU quake.
 * In particular, the goal is to keep as many files as possible in ROM without having to copy them to RAM.
 * Such files can be also cached to Flash memory. Note: unlike quake cache, flash memory caching is done only once per level.
 *
 * In particular, these are the modifications done in the pack file:
 * - VERSION 0.0
 *      - To each file in PAK, a \0 is appended.
 * - VERSION 1.0
 *      - Alias models have triangle data as well.
 *       - Sky prerendered.
 *       - BSP models modified.
 *       - Sound resampled
 *       - all strings found in the pak file are printed to be included in C code.
 *
 * Note: the program is full of debug messages and debug code and possibly dead code as well. It would require a serious cleanup!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "quakedef.h"
#include "pakStringGenerator.h"
#include "wavconverter.h"

#define VERSION_MINOR           1
#define VERSION_MAJOR           0
#define PROCESS_ALIAS_MODELS 1

char input[256];
char output[256];

typedef struct pak_header_s
{
  char id[4];
  int offset;
  int size;
} pak_header_t;

typedef struct pak_file_s
{
  char name[56];
  int offset;
  int size;
} pak_file_t;//


pak_file_t *getPackFileList(uint8_t *buf, int *numFiles);
void *addNullTerminatorToFilesInPack(uint8_t * buf, int *newPakSize);
void *modifyFilesInPak(uint8_t *buf, int *newPakSize);
void *addFileToPak(uint8_t *pakBuf, int *newPakSize, uint8_t *fileBuffer, int size, char *filename);
int getPackHeader(uint8_t *buf,  pak_header_t *h);

int main(int argc, char* argv[])
{
    printf("MCUPackConverter by Nicola Wrachien\r\n");
    printf("Version %d.%d\r\n", VERSION_MAJOR, VERSION_MINOR);
    if (argc != 3)
    {
        printf("Usage:\r\n\n");
        printf("MCUPackConverter.exe input_file output_file:\r\n\n");
        printf("Using default pak0.pak\r\n");
        snprintf(input, sizeof(input), "%s", "pak0.pak");
        snprintf(output, sizeof(output), "%s", "pak0conv.pak");
    }
    else
    {
        strncpy(input, argv[1], sizeof (input));
        strncpy(output, argv[2], sizeof (output));
    }
    FILE *fi = fopen(input, "rb");
    if (fi == NULL)
    {
        printf("Cannot open %s\r\n", input);
        return 1;
    }
    // get file size
    fseek(fi, 0L, SEEK_END);
    uint32_t sz = ftell(fi);
    rewind(fi);
    // read pak file
    uint8_t *pak = calloc(1, sz);
    uint32_t br =fread(pak, 1, sz, fi);
    printf("Read %u bytes\r\n", br);
    fclose(fi);
    // now the whole pak file is on the buffer.
    int newPakSize;
    uint8_t * newPak;
    printf("File opened\r\n");
    #if PROCESS_ALIAS_MODELS
        newPak = modifyFilesInPak(pak, &newPakSize);
        free(pak);
        pak = newPak;
    #endif // MINIMIZE_ALIAS_MODELS

    int differentSkies;
    int numberOfSkies;
    sky_table_t *skyList;
    uint8_t *skyBuff = createSkies(&differentSkies, &numberOfSkies, &skyList);
    printf("There were %d skies, %d are unique\r\n", numberOfSkies, differentSkies);
    for (int i = 0; i < differentSkies; i++)
    {
        char filename[MAX_QPATH];
        snprintf(filename, sizeof(filename), "sky%02x", i);
        printf("Adding sky %s\r\n",filename);
        newPak  = addFileToPak(pak, &newPakSize, &skyBuff[i * 128 * 128 * 128], 128 * 128 * 128, filename);
        free(pak);
        pak = newPak;
    }
    printf("Freeing  skybuff %p\r\n", skyBuff);
    free(skyBuff);
    //
    printf("Adding skylist.dat\r\n");
    //
    printf("SIZE OF SKYTABLE_t %u", (uint32_t) sizeof(sky_table_t));
    newPak  = addFileToPak(pak, &newPakSize, (uint8_t*) skyList, sizeof(sky_table_t) * numberOfSkies, "skylist.dat");
    free(pak);
    pak = newPak;

    //
    printf("Freeing  skyList %p\r\n", skyList);
    free(skyList);
    //
    newPak = addNullTerminatorToFilesInPack(pak, &newPakSize);
    //
    FILE *fo = fopen(output, "wb");
    fwrite(newPak, newPakSize, 1, fo);
    fclose(fo);
    printf("------------------------------------ALL PACK STRINGS-------------------------\r\n");
    FIXME("Press a key");
    printAllPakStrings();
    return 0;
}

void *modifyFilesInPak(uint8_t *buf, int *newPakSize)
{
    // first load pack file List
    int numFiles;
    pak_file_t * pakFileList;
    pakFileList = getPackFileList(buf, &numFiles);
    //
    if (pakFileList)
    {
        //
        uint8_t **files = calloc(numFiles, sizeof(*files));
        int i;
        int totalSize = sizeof(pak_header_t);
        // check all files. Modify those whose name end in ".mdl"
        for (i = 0 ; i < numFiles; i++)
        {
            files[i] = calloc(pakFileList[i].size, 1);
            memcpy(files[i], &buf[pakFileList[i].offset], pakFileList[i].size);
            // now in files[i] we have the file. Let's convert it if it is mdl, otherwise we don't .
            char *name = pakFileList[i].name;
            uint32_t len = strlen(name);
            // TODO: CLEAN UP THIS SHIT
            // ALIAS MODELS
            if (len > 3 && name[len - 3] == 'm' && name[len - 2] == 'd' && name[len - 1] == 'l')
            {
                printf("The current name is %s, I will convert!\r\n", name);
                model_t mod;
                char modname[64];
#if NEW_MODEL
                mod.name = modname;
#endif
                strncpy (mod.name, name, sizeof (modname));
                uint8_t *newFile;
                uint32_t size;
                // convert
                newFile = Convert_AliasModel(&mod, files[i], &size);
                // discard old
                free(files[i]);
                // copy
                files[i] = calloc(1, size);
                memcpy(files[i], newFile, size);
                printf("Size is %u, was %u\r\n", size, pakFileList[i].size);
                pakFileList[i].size = size;
            }
            else if (strstr(name, "sound") == name)    // if starts with sounds
            {
                wavinfo_t wi = GetWavinfo(name, files[i], pakFileList[i].size);
                //
                int len = wi.samples;
                void * w = ResampleSfx(wi.rate, wi.width, (uint8_t*)files[i] + wi.dataofs, &len, wi.loopstart);
                free(files[i]);
                files[i] = w;
                printf("Converted wave: number of samples is now %d.\r\n", len);
                pakFileList[i].size = len + 2 * sizeof(int);
            }
            else if (strstr(name, "bsp"))
            {
                printf("I found a brushmodel %s!\r\n", name);
                uint8_t *newFile;
                uint32_t size = pakFileList[i].size ;
                model_t mod;
                char modname[64];
#if NEW_MODEL
                mod.name = modname;
#endif
                strncpy (mod.name, name, sizeof(modname) - 1);
                // convert
                newFile = Convert_BrushModel(&mod, files[i], &size);
                // discard old

                free(files[i]);
                // copy
                files[i] = calloc(1, size);
                memcpy(files[i], newFile, size);
                printf("Size is %d, was %d\r\n", size, pakFileList[i].size);
                pakFileList[i].size = size;
            }
            totalSize += pakFileList[i].size;
        }
        //
        totalSize += numFiles * sizeof(pak_file_t);
        // Now we have all the files read.
        printf("Total Size %d\r\n", totalSize);
        uint8_t *newPak = calloc(1, totalSize);
        pak_header_t ph;
        ph.id[0] = 'P';
        ph.id[1] = 'A';
        ph.id[2] = 'C';
        ph.id[3] = 'K';
        ph.size = sizeof(pak_file_t) * numFiles;
        ph.offset = sizeof (pak_header_t);
        memcpy(newPak, &ph, sizeof(ph));
        // now copy the header table
        //
        int offset = sizeof(pak_header_t) + numFiles *  sizeof(pak_file_t);
        // store back all files.
        for (int i = 0; i < numFiles; i++)
        {
            static int sizeSoFar = 0;
            sizeSoFar += pakFileList[i].size;
            printf("Converting File %i, name %s. Size %d. Cumulative size: %d\r\n", i, pakFileList[i].name, pakFileList[i].size, sizeSoFar);
            pak_file_t * p = (pak_file_t *) &newPak[sizeof(pak_header_t) + i * sizeof(pak_file_t)];
            // copy name
            strcpy(p->name, pakFileList[i].name);
            // copy offset
            p->offset = offset;
            // set size
            p->size = pakFileList[i].size;
            // copy file
            memcpy(&newPak[offset], files[i], pakFileList[i].size);
            free(files[i]);
            // new offset
            offset += pakFileList[i].size;
        }
        free (files);
        //
        *newPakSize = offset;
        return newPak;
    }
    return NULL;
}
//
void *addFileToPak(uint8_t *pakBuf, int *newPakSize, uint8_t *fileBuffer, int size, char *filename)
{
    // first load pack file List
    int numFiles;
    pak_file_t * oldPakFileList, *pakFileList;
    oldPakFileList = getPackFileList(pakBuf, &numFiles);
    // allocate space for numFiles + 1 entries to fit the new one
    pakFileList = calloc((numFiles + 1) * sizeof(pak_file_t), 1);
    // create new packfilelist
    memcpy(pakFileList, oldPakFileList, numFiles * sizeof(pak_file_t) );
    //
    if (pakFileList)
    {
        // allocate space for file pointers
        uint8_t **files = calloc(numFiles + 1, sizeof(*files));
        int i;
        int totalSize = sizeof(pak_header_t);
        // check all files. Modify those whose name end in ".mdl"
        for (i = 0 ; i < numFiles; i++)
        {
            printf("Adding back file %i\r\n", i);
            // allocate space for the file
            files[i] = calloc(pakFileList[i].size, 1);
            memcpy(files[i], &pakBuf[pakFileList[i].offset], pakFileList[i].size);
            totalSize += pakFileList[i].size;
        }
        printf("Adding NEW file %i\r\n", i);
        // copy new file size and name
        pakFileList[i].size = size;
        strncpy(pakFileList[i].name, filename, sizeof(pakFileList[i].name));
        printf("Copied file name\r\n");
        // create the buffer for new file entry, and copy there the data
        files[i] = calloc(pakFileList[i].size, 1);
        printf("Copying new file buffer %p to %p with size %d\r\n",fileBuffer, files[numFiles], pakFileList[numFiles].size);
        memcpy(files[numFiles], fileBuffer, pakFileList[numFiles].size);
        totalSize += pakFileList[i].size;
        //
        printf("Done\r\n");
        // now we have numFiles+1 files. Recreate the pack.
        numFiles++;
        //
        totalSize += numFiles * sizeof(pak_file_t);
        //
        // Now we have all the files read.
        printf("Total Size %d\r\n", totalSize);
      //  FIXME("");
        uint8_t *newPak = calloc(1, totalSize);
        pak_header_t ph;
        ph.id[0] = 'P';
        ph.id[1] = 'A';
        ph.id[2] = 'C';
        ph.id[3] = 'K';
        ph.size = sizeof(pak_file_t) * numFiles;
        ph.offset = sizeof (pak_header_t);
        memcpy(newPak, &ph, sizeof(ph));
        // now copy the header table
        //
        int offset = sizeof(pak_header_t) + numFiles *  sizeof(pak_file_t);
        // store back all files.
        for (int i = 0; i < numFiles; i++)
        {
            static int sizeSoFar = 0;
            sizeSoFar += pakFileList[i].size;
            printf("Storing back File %i, name %s. Size %d. Cumulative size: %d\r\n", i, pakFileList[i].name, pakFileList[i].size, sizeSoFar);
            pak_file_t * p = (pak_file_t *) &newPak[sizeof(pak_header_t) + i * sizeof(pak_file_t)];
            // copy name
            strcpy(p->name, pakFileList[i].name);
            // copy offset
            p->offset = offset;
            // set size
            p->size = pakFileList[i].size;
            // copy file
            memcpy(&newPak[offset], files[i], pakFileList[i].size);
            // we can discard the buffer.
            free(files[i]);
            // new offset
            offset += pakFileList[i].size;
        }
        free (files);
        free (pakFileList);
        //
        *newPakSize = offset;
        return newPak;
    }
    return NULL;
}

//
void *addNullTerminatorToFilesInPack(uint8_t * buf, int *newPakSize)
{
    // first get pack file List
    int numFiles;
    pak_file_t * pakFileList;
    pakFileList = getPackFileList(buf, &numFiles);
    if (pakFileList)
    {
        uint8_t **files = calloc(numFiles, sizeof(*files));
        int i;
        int totalSize = sizeof(pak_header_t);
        totalSize += numFiles * sizeof(pak_file_t);
        for (i = 0 ; i < numFiles; i++)
        {
            // load file, and add at least one byte more. And align at 4 bytes boundaries.
            int size = (pakFileList[i].size + 1 + 3) & (~3);
            totalSize += size;
            // I'm too lazy for checking memory allocation. The OS will take care.
            files[i] = calloc(size, 1);
            memcpy(files[i], &buf[pakFileList[i].offset], pakFileList[i].size);
        }
        // Now we have all the files read.
        printf("Total Size %d\r\n", totalSize);
     //   FIXME("");
        uint8_t *newPak = calloc(1, totalSize);
        pak_header_t ph;
        ph.id[0] = 'P';
        ph.id[1] = 'A';
        ph.id[2] = 'C';
        ph.id[3] = 'K';
        ph.size = sizeof(pak_file_t) * numFiles;
        ph.offset = sizeof (pak_header_t);
        memcpy(newPak, &ph, sizeof(ph));
        // now copy the header table
        //
        int offset = sizeof(pak_header_t) + numFiles *  sizeof(pak_file_t);
        for (int i = 0; i < numFiles; i++)
        {
            static int sizeSoFar = 0;
            sizeSoFar += pakFileList[i].size;
            printf("Converting File %i, name %s. Size %d. Cumulative size: %d\r\n", i, pakFileList[i].name, pakFileList[i].size, sizeSoFar);
            pak_file_t * p = (pak_file_t *) &newPak[sizeof(pak_header_t) + i * sizeof(pak_file_t)];
            // copy name
            strcpy(p->name, pakFileList[i].name);
            int size = (pakFileList[i].size + 1 + 3) & (~3);
            // copy offset
            p->offset = offset;
            // set size
            p->size = pakFileList[i].size + 1;  // only + 1, so that we keep compatibility with old Quake
            // copy file
            memcpy(&newPak[offset], files[i], pakFileList[i].size);
            free(files[i]);
            // new offset
            offset += size;
        }
         free (files);
        *newPakSize = offset;
        return newPak;
    }
    return NULL;
}

pak_file_t *getPackFileList(uint8_t *buf, int *numFiles)
{
    pak_header_t header;
    int r = getPackHeader(buf, &header);
    if (r)
        return NULL;
    int n = header.size / sizeof(pak_file_t);
    printf("Header.size is %i\r\n", header.size);
    //
    if (numFiles)
        *numFiles = n;
    pak_file_t *pfl = (pak_file_t*) &buf[header.offset];
    return pfl;
}
int getPackHeader(uint8_t *buf,  pak_header_t *h)
{
    *h = *(pak_header_t*)buf;
    if (memcmp(h->id, "PACK", 4) != 0)
    {
        printf("PACK header not found\r\n");
        return 1;
    }
    printf("PACK header found\r\n");
    return 0;
}

