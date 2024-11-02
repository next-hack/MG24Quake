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
 *  - VERSION 2.0
 *       - Retail PAK1 support.
 *       - Alias models have a 0xFFFFFFFF field to allow caching skins to flash.
 * Note: the program is full of debug messages and debug code and possibly dead code as well. It would require a serious cleanup!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "quakedef.h"
#include "pakStringGenerator.h"
#include "wavconverter.h"

#define VERSION_MINOR           2
#define VERSION_MAJOR           0
#define PROCESS_ALIAS_MODELS    1
#define DEFALUL_PAK             "pak0.pak"
#define DEFALUL_PAK_CONV        "pak0conv.pak"
#define DEFALUT_PAK_PREFIX      "pak"
#define DEFAULT_PAK_SUFFIX      "conv"
char input0[256];
char input1[256];
char output[256];
#define PAK_ENTRY_FILE_NAME_LENGHT 56
typedef struct pak_header_s
{
  char id[4];
  int offset;
  int size;
} pak_header_t;

typedef struct pak_file_s
{
  char name[PAK_ENTRY_FILE_NAME_LENGHT];
  int offset;
  int size;
} pak_file_t;//

extern void printProfileData(void);
pak_file_t *getPackFileList(uint8_t *buf, int *numFiles);
void *addNullTerminatorToFilesInPack(uint8_t * buf, int *newPakSize);
void *modifyFilesInPak(uint8_t *buf, int *newPakSize);
void *addFileToPak(uint8_t *pakBuf, int *newPakSize, uint8_t *fileBuffer, int size, char *filename);
int getPackHeader(uint8_t *buf,  pak_header_t *h);
uint8_t *readFile(char *filename)
{
    FILE *fi = fopen(filename, "rb");
    if (fi == NULL)
    {
        printf("Cannot open %s\r\n", filename);
        return NULL;
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
    return pak;
}
uint8_t * joinPaks(char *pak0_name, char *pak1_name)
{
    // first open the two files
    uint8_t *pak0 = readFile(pak0_name);
    if (!pak0)
    {
        printf("Error: pak0 can't be read.\r\n");
        return NULL;
    }
    uint8_t *pak1 = readFile(pak1_name);
    if (!pak1)
    {
        printf("Warning: pak1 can't be read. Using pak0 only\r\n");
        return pak0;
    }

    int numFiles0, numFiles1;
    pak_file_t * pakFileList0;
    pakFileList0 = getPackFileList(pak0, &numFiles0);
    if (!pakFileList0)
    {
        free(pak0);
        free(pak1);
        return NULL;
    }
    pak_file_t * pakFileList1;
    pakFileList1 = getPackFileList(pak1, &numFiles1);
    if (!pakFileList1)
    {
        free(pak1);
        free(pakFileList0);
        printf("Warning: pak1 can't be read. Using pak0 only\r\n");
        return pak0;
    }
    // here we have both pak file list 0 and 1.
    //
    // the algorithm is as follows: we now check for each file in pak1 if it is present in pak0. If it is present, then we skip the entry.
    uint8_t *presentInPak1 = calloc(1, numFiles0);
    int numDuplicates = 0;
    int totalSize = sizeof(pak_header_t);
    for (int i = 0; i < numFiles0; i++)
    {
        char *fileName = pakFileList0[i].name;
        int size = pakFileList0[i].size;
        for (int j = 0; j < numFiles1; j++)
        {
           if (!strcmp(fileName, pakFileList1[j].name))
           {
               presentInPak1[i] = 1;
               numDuplicates ++;
               size = 0;    // will be added later
               printf("skipping file %s in pak0. It is present in pak1\r\n", fileName);
               break;
           }
        }
        totalSize += size;
    }
    // add next size
    for (int i = 0; i < numFiles1; i++)
    {
        totalSize += pakFileList1[i].size;
    }
    int numFiles = numFiles0 + numFiles1 - numDuplicates;
    printf("Num files: in pak0 %d, in pak1 %d, duplicates %d, total %d\r\n", numFiles0, numFiles1, numDuplicates, numFiles);
    // Ok, now we can add all the files from pak0
    uint8_t **files = calloc(numFiles, sizeof(*files));
    int *sizes = calloc(numFiles, sizeof(*sizes));
    char (*names) [PAK_ENTRY_FILE_NAME_LENGHT] = calloc(numFiles, sizeof(*names));

    // copy first the files not duplicate.
    int j = 0;
    int checkTotalSize = sizeof(pak_header_t);
    for (int i = 0 ; i < numFiles0; i++)
    {
        if (presentInPak1[i])
        {
            // skip, will be added later.
            continue;
        }
        sizes[j] = pakFileList0[i].size;
        files[j] = calloc(sizes[j], 1);
        checkTotalSize += sizes[j];
        memcpy(files[j], &pak0[pakFileList0[i].offset], sizes[j]);
        memcpy(names[j], pakFileList0[i].name, sizeof(names[j]));
        j++;
    }
    for (int i = 0; i < numFiles1; i++)
    {
        sizes[j] = pakFileList1[i].size;
        files[j] = calloc(sizes[j], 1);
        memcpy(files[j], &pak1[pakFileList1[i].offset], sizes[j]);
        memcpy(names[j], pakFileList1[i].name, sizeof(names[j]));
        checkTotalSize += sizes[j];
        j++;
    }
    totalSize += numFiles * sizeof(pak_file_t);
    checkTotalSize += numFiles * sizeof(pak_file_t);
    printf("Total Size %d (check %d)\r\n", totalSize, checkTotalSize);
    if (totalSize != checkTotalSize)
    {
        printf("ERROR");
        return NULL;
    }
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
    //
    // store all files.
    //
    int sizeSoFar = 0;
    for (int i = 0; i < numFiles; i++)
    {
        sizeSoFar += sizes[i];
//        printf("Adding File %i (max %d), name %s. Size %d. Cumulative size: %d\r\n", i, numFiles, names[i], sizes[i], sizeSoFar);
        pak_file_t * p = (pak_file_t *) &newPak[sizeof(pak_header_t) + i * sizeof(pak_file_t)];
        // copy name
        memcpy(p->name, names[i], sizeof(names[i]));
        // copy offset
        p->offset = offset;
        // set size
        p->size = sizes[i];
        // copy file
//        printf("mcpy %d, files[i] = %p, size is %d, pos %p, offs %d, total after copy: %d\r\n", i, files[i], sizes[i], &newPak[offset], offset, sizes[i] + offset);
        memcpy(&newPak[offset], files[i], sizes[i]);
        free(files[i]);
        // new offset
        offset += sizes[i];
    }
    free(names);
    free(sizes);
    free (files);
    //
    return newPak;
}
int main(int argc, char* argv[])
{
    printf("MCUPackConverter by Nicola Wrachien\r\n");
    printf("Version %d.%d\r\n", VERSION_MAJOR, VERSION_MINOR);
    if (argc < 3)
    {
        printf("Usage:\r\n\n");
        printf("MCUPackConverter.exe pak0_file_name [pak1_file_name] output_file\r\n\r\n");
        printf("Note! pak1_file_name is optional");
        //
        printf("Using default %s<n>.pak, where n is 0 and 1\r\n", DEFALUT_PAK_PREFIX);
        snprintf(input0, sizeof(input0), "%s0.pak", DEFALUT_PAK_PREFIX);
        snprintf(input1, sizeof(input1), "%s1.pak", DEFALUT_PAK_PREFIX);
        snprintf(output, sizeof(output), "%s", DEFALUL_PAK_CONV);
    }
    else if (argc == 4 )
    {
            strncpy(input0, argv[1], sizeof (input0));
            strncpy(input1, argv[2], sizeof (input1));
            strncpy(output, argv[3], sizeof (output));
    }
    else
    {
        printf("converting a single pak\r\n");
        strncpy(input0, argv[1], sizeof (input0));
        strncpy(output, argv[2], sizeof (output));
    }
    uint8_t *pak = NULL;
    if (strlen(input1))
    {
        printf("Converting and joining two pak files\r\n");
        pak = joinPaks(input0, input1);

    }
    else
    {
        pak = readFile(input0);
    }
    if (pak == NULL)
    {
        printf("Error reading one or more pak files, exiting\r\n");
        return 1;
    }
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
    printProfileData(); // just to understand limits.
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
       //         FIXME("alias model");
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
        // check all files.
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

