/*
 Quake port to Silicon Labs EFR32MG24 and MGM240x
 by Nicola Wrachien (next-hack in the comments)

 Original Quake code has been deeply changed to run in only
 276 kB RAM, and 32 MB external flash, while maintaining all
 the game and 3D engine features (except music and multiplayer).

 Copyright (C) 1996-1997 Id Software, Inc.
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
// comndef.h  -- general definitions
#ifndef COMMON_H
#define COMMON_H
#if !defined BYTE_DEFINED
typedef unsigned char byte;
#define BYTE_DEFINED 1
#endif

#undef true
#undef false

typedef enum
{
    false, true
} qboolean;

//============================================================================

typedef struct sizebuf_s
{
    byte *data;
    int maxsize :15;
    unsigned int allowoverflow :1;  // if false, do a Sys_Error
    int cursize :15;
    unsigned int overflowed :1;   // set to true if the buffer size failed

} sizebuf_t;
//
// on disk
//
typedef struct
{
    char name[56];
    int filepos, filelen;
} dpackfile_t;

typedef struct
{
    char id[4];
    int dirofs;
    int dirlen;
} dpackheader_t;
void SZ_Alloc(sizebuf_t *buf, int startsize);
void SZ_Free(sizebuf_t *buf);
void SZ_Clear(sizebuf_t *buf);
void* SZ_GetSpace(sizebuf_t *buf, int length);
void SZ_Write(sizebuf_t *buf, const void *data, int length);
void SZ_Print(sizebuf_t *buf, char *data);	// strcats onto the sizebuf

//============================================================================

typedef struct link_s
{
#if LINKS_USE_SHORT_PTR
    uint16_t    prev_sptr;
    uint16_t    next_sptr;
#else
    struct link_s *prev, *next;
#endif

} link_t;

void ClearLink(link_t *l);
void RemoveLink(link_t *l);
void InsertLinkBefore(link_t *l, link_t *before);
void InsertLinkAfter(link_t *l, link_t *after);

// (type *)STRUCT_FROM_LINK(link_t *link, type, member)
// ent = STRUCT_FROM_LINK(link,entity_t,order)
// FIXME: remove this mess!
#define	STRUCT_FROM_LINK(l,t,m) ((t *)((byte *)l - (int)&(((t *)0)->m)))

//============================================================================

#ifndef NULL
#define NULL ((void *)0)
#endif

#define Q_MAXCHAR ((char)0x7f)
#define Q_MAXSHORT ((short)0x7fff)
#define Q_MAXINT	((int)0x7fffffff)
#define Q_MAXLONG ((int)0x7fffffff)
#define Q_MAXFLOAT ((int)0x7fffffff)

#define Q_MINCHAR ((char)0x80)
#define Q_MINSHORT ((short)0x8000)
#define Q_MININT 	((int)0x80000000)
#define Q_MINLONG ((int)0x80000000)
#define Q_MINFLOAT ((int)0x7fffffff)

//============================================================================

extern qboolean bigendien;

extern short (*BigShort)(short l);
extern short (*LittleShort)(short l);
extern int (*BigLong)(int l);
extern int (*LittleLong)(int l);
extern float (*BigFloat)(float l);
extern float (*LittleFloat)(float l);

//============================================================================

void MSG_WriteChar(sizebuf_t *sb, int c);
void MSG_WriteByte(sizebuf_t *sb, int c);
void MSG_WriteShort(sizebuf_t *sb, int c);
void MSG_WriteLong(sizebuf_t *sb, int c);
void MSG_WriteFloat(sizebuf_t *sb, float f);
void MSG_WriteString(sizebuf_t *sb, const char *s);
void MSG_WriteCoord(sizebuf_t *sb, float f);
void MSG_WriteAngle(sizebuf_t *sb, float f);

extern int msg_readcount;
extern qboolean msg_badread;		// set if a read goes beyond end of message

void MSG_BeginReading(void);
#define DEBUG_MSG_READS 0
#if !DEBUG_MSG_READS
int MSG_ReadChar(void);
int MSG_ReadByte(void);
int MSG_ReadShort(void);
int MSG_ReadLong(void);
char* MSG_ReadString(char *bufferIn, int maxsize);
#else
extern int readCanFail;
#define MSG_ReadChar() MSG_ReadChar_(__FILE__, __LINE__)
#define MSG_ReadByte() MSG_ReadByte_(__FILE__, __LINE__)
#define MSG_ReadShort() MSG_ReadShort_(__FILE__, __LINE__)
#define MSG_ReadLong() MSG_ReadLong_(__FILE__, __LINE__)
#define MSG_ReadString(buffer, maxsize) MSG_ReadString_ (buffer, maxsize, __FILE__, __LINE__)
#endif
float MSG_ReadFloat(void);

float MSG_ReadCoord(void);
float MSG_ReadAngle(void);
short MSG_ReadAngleS(void);
short MSG_ReadCoordS(void);

//============================================================================

void Q_memset(void *dest, int fill, int count);
void Q_memcpy(void *dest, const void *src, int count);
int Q_memcmp(const void *m1, const void *m2, int count);
void Q_strcpy(char *dest, const char *src);
void Q_strncpy(char *dest, char *src, int count);
int Q_strlen(const char *str);
char* Q_strrchr(char *s, char c);
void Q_strcat(char *dest, char *src);
int Q_strcmp(const char *s1, const char *s2);
int Q_strncmp(const char *s1, const char *s2, int count);
int Q_strcasecmp(const char *s1, const char *s2);
int Q_strncasecmp(const char *s1, const char *s2, int n);
int Q_atoi(const char *str);
float Q_atof(const char *str);

//============================================================================

extern char com_token[1024];
extern qboolean com_eof;

char* COM_Parse(char *data, char *com_token);
byte* getExtMemPointerToFileInPak(char *filename, unsigned int *fileSize);

extern int com_argc;
extern char **com_argv;

int COM_CheckParm(char *parm);
void COM_Init(char *path);
void COM_InitArgv(int argc, char **argv);

char* COM_SkipPath(char *pathname);
void COM_StripExtension(char *in, char *out);
void COM_FileBase(char *in, char *out);
void COM_DefaultExtension(char *path, char *extension);

#define va(buff, format, ...) van(buff, sizeof(buff), format, __VA_ARGS__)

char* van(char *stringbuff, unsigned int size, char *format, ...);
// does a varargs printf into a temp buffer

//============================================================================

extern int com_filesize;
struct cache_user_s;
#if !USE_EXT_MEMORY
extern char com_gamedir[MAX_OSPATH];
#endif
void COM_WriteFile(char *filename, void *data, int len);
int COM_OpenFile(char *filename, int *hndl);
int COM_FOpenFile(char *filename, FILE **file);
void COM_CloseFile(int h);

byte* COM_LoadStackFile(char *path, void *buffer, int bufsize);
byte* COM_LoadTempFile(char *path);
byte* COM_LoadHunkFile(char *path);
void COM_LoadCacheFile(char *path, struct cache_user_s *cu);
int getDPackFile(dpackfile_t *packFile, int num);
byte* COM_LoadFileFromExtMem(char *filename, unsigned int *fileSize);

#if USE_ORIGINAL_CVAR
extern	struct cvar_s	registered;
#endif
extern qboolean standard_quake, rogue, hipnotic;
#endif
