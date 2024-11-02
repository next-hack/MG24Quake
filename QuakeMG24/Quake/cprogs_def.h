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

#ifndef CPROGS_DEF_H
#define CPROGS_DEF_H
#include <stdint.h>
#include <stdlib.h>
#define vector vect_t
#define shortVector shortVect_t

typedef uint16_t field;
typedef uint16_t function;
#define ENTITY_LIST_START_INDEX       (-512)
#define SUBMODEL_NAME_START_INDEX     (-1024)
#define  DYNAMIC_STRING_INDEX        (ENTITY_LIST_START_INDEX * 3)

#define areFunctionsEqual(a, b)  (a == b)
#define TEMP_STRING_SIZE      64    //tempstring is used typically to print coordinates for debug. 64 is even too much!
#include "quakeProgs.h"
void* getFunction(func_t fnum);
//
extern AUX_SECTION char tempPrintString[TEMP_STRING_SIZE];
extern const char *const quakeProgStrings[];
extern const void *const quakeProgFunctions[];

char* getStringFromIndex(int16_t index);
int16_t findStringIndex(const char *value);
static inline int areStringsEqual(uint16_t s1, uint16_t s2)
{
    if (s1 == s2)
        return 1;
    else if ((s1 == 0) || (s2 == 0))
    {  // note: case in which s1 == s2 == 0 handled before. So here only only s1 or s2 is 0.
        return 0;
    }
    else
        return !strcmp(getStringFromIndex(s1), getStringFromIndex(s2));
}
#define getFunctionIndex(f) (f ## _func_index)

#include "quakedef.h"

extern char *entityFieldName;
#if WIN32
#define DEBUG_FIELD(x) do{entityFieldName = x;}while (0)
#else
#define DEBUG_FIELD(x) do{(void) x;}while (0)
#endif
#if WIN32
#define DEBUG_ERROR_SETTER(x, v) do{printf("Error setting entity %s, field %s, value %f\r\n", getStringFromIndex(x->qcc_classname), entityFieldName, v); FIXME("");} while(0)
#else
#define DEBUG_ERROR_SETTER(x, v) do{(void) x; (void) v; printf("Error setting entity");} while(0)
#endif
#define STOP_ON_WARNING_SETTER 1
#if STOP_ON_WARNING_SETTER
#define DEBUG_WARNING_SETTER(x, v)  do{printf("Warning setting entity %s, field %s\r\n", getStringFromIndex(x->qcc_classname), entityFieldName); FIXME("");} while(0)
#else
#define DEBUG_WARNING_SETTER(x, v)  do{printf("Warning setting entity %s, field %s\r\n", getStringFromIndex(x->qcc_classname), entityFieldName);} while(0)
#endif
#define DEBUG_ERROR_GETTER(x)  do{printf("Error getting entity %s, field %s\r\n", getStringFromIndex(x->qcc_classname), entityFieldName); FIXME("");} while(0)
#define DEBUG_WARNING_GETTER(x) do{printf("Warning getting entity %s, field %s\r\n", getStringFromIndex(x->qcc_classname), entityFieldName); FIXME("");} while(0)
static inline float dotProduct(vector a, vector b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
static inline int areVectorEqual(vector v1, vector v2)
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}
static inline vector vectorSub(vector v1, vector v2)
{
    vector vr;
    vr.x = v1.x - v2.x;
    vr.y = v1.y - v2.y;
    vr.z = v1.z - v2.z;
    return vr;
}
static inline vector vectorAdd(vector v1, vector v2)
{
    vector vr;
    vr.x = v1.x + v2.x;
    vr.y = v1.y + v2.y;
    vr.z = v1.z + v2.z;
    return vr;
}
static inline vector vectorMulFloat(vector v1, float f)
{
    vector vr;
    vr.x = v1.x * f;
    vr.y = v1.y * f;
    vr.z = v1.z * f;
    return vr;
}
static inline vector floatMulVector(float f, vector v1)
{
    return vectorMulFloat(v1, f);
}
static inline int isEmptyString(int s)
{
    return s == 0;
}
#endif // CPROGS_DEF_H
