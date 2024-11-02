/*
 MCUpackconverter by Nicola Wrachien (next-hack in the comments)

 This file is based on model.c, from Quake.

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
// models.c -- model loading and caching

// models are the only shared resource between a client and server running
// on the same machine.

#include "quakedef.h"
#include "pakStringGenerator.h"
#include "r_local.h"
#include <stdio.h>
#include <stdlib.h>

//
#define PROFILE_NUM_ELEMENTS 1

#if PROFILE_NUM_ELEMENTS
int maxLeaves = 0;
int maxFaces = 0;
int maxNodes = 0;
int maxEdges = 0;
int maxEntitiesEasy = 0;
int maxEntitiesMedium = 0;
int maxEntitiesHard = 0;

int maxLighting = 0;
#endif // PROFILE_NUM_ELEMENTS
//

int modelNumsurfaces = 0;
int modelNumnodes = 0;
int modelNumleafs = 0;
short * surfNodeIndex = 0;
byte *mnodeData = NULL;
mnode_t *modelNodes = NULL;
mleaf_t *modelLeafs = NULL;

char	loadname[32];	// for hunk tags
#define MAX_MODEL_NAME_LENGTH 64
char *modelName;
//void Mod_LoadSpriteModel (model_t *mod, void *buffer);
//void Mod_LoadBrushModel (model_t *mod, void *buffer);
void Mod_LoadAliasModel (model_t *mod, void *buffer);
model_t *Mod_LoadModel (model_t *mod, qboolean crash);

void * chunk_AllocName(uint32_t size, char * name);
void chunk_Align4();
int addSkinTriangle(uint8_t *skin, int width, coord16_t *coords);


// values for model_t's needload
#define NL_PRESENT		0
#define NL_NEEDS_LOADED	1
#define NL_UNREFERENCED	2


/*
==============================================================================

ALIAS MODELS

==============================================================================
*/

/*
=================
Mod_LoadAliasFrame
=================
*/
#if 0
void * Mod_LoadAliasFrame (void * pin, int *pframeindex, int numv,
	trivertx_t *pbboxmin, trivertx_t *pbboxmax, disk_aliashdr_t *pheader, char *name)
{
	trivertx_t		*pframe, *pinframe;
	int				i, j;
	daliasframe_t	*pdaliasframe;

	pdaliasframe = (daliasframe_t *)pin;

	strcpy (name, pdaliasframe->name);

	for (i=0 ; i<3 ; i++)
	{
	// these are byte values, so we don't have to worry about
	// endianness
		pbboxmin->v[i] = pdaliasframe->bboxmin.v[i];
		pbboxmax->v[i] = pdaliasframe->bboxmax.v[i];
	}

	pinframe = (trivertx_t *)(pdaliasframe + 1);
//    printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
	pframe = Hunk_AllocName (numv * sizeof(*pframe), loadname);

	*pframeindex = (byte *)pframe - (byte *)pheader;

	for (j=0 ; j<numv ; j++)
	{
		int		k;

	// these are all byte values, so no need to deal with endianness
		pframe[j].lightnormalindex = pinframe[j].lightnormalindex;

		for (k=0 ; k<3 ; k++)
		{
			pframe[j].v[k] = pinframe[j].v[k];
		}
	}

	pinframe += numv;

	return (void *)pinframe;
}
#endif
void * Mod_LoadAliasFrameChunk (void * pin, int *pframeindex, int numv,
	trivertx_t *pbboxmin, trivertx_t *pbboxmax, disk_aliashdr_t *pheader, char *name)
{
	trivertx_t		*pframe, *pinframe;
	int				i, j;
	daliasframe_t	*pdaliasframe;

	pdaliasframe = (daliasframe_t *)pin;

	strcpy (name, pdaliasframe->name);

	for (i=0 ; i<3 ; i++)
	{
	// these are byte values, so we don't have to worry about
	// endianness
		pbboxmin->v[i] = pdaliasframe->bboxmin.v[i];
		pbboxmax->v[i] = pdaliasframe->bboxmax.v[i];
	}

	pinframe = (trivertx_t *)(pdaliasframe + 1);

    chunk_Align4();
	pframe = chunk_AllocName (numv * sizeof(*pframe), loadname);

	*pframeindex = (byte *)pframe - (byte *)pheader;

	for (j=0 ; j<numv ; j++)
	{
		int		k;

	// these are all byte values, so no need to deal with endianness
		pframe[j].lightnormalindex = pinframe[j].lightnormalindex;

		for (k=0 ; k<3 ; k++)
		{
			pframe[j].v[k] = pinframe[j].v[k];
		}
	}

	pinframe += numv;

	return (void *)pinframe;
}




/*
=================
Mod_LoadAliasGroup
=================
*/

void * Mod_LoadAliasGroupChunk (void * pin, int *pframeindex, int numv,
                                trivertx_t *pbboxmin, trivertx_t *pbboxmax, disk_aliashdr_t *pheader, char *name)
{
    daliasgroup_t       *pingroup;
    maliasgroup_t       *paliasgroup;
    int                 i, numframes;
    daliasinterval_t    *pin_intervals;
    float               *poutintervals;
    void                *ptemp;

    pingroup = (daliasgroup_t *)pin;

    numframes = LittleLong (pingroup->numframes);
    chunk_Align4();
	paliasgroup = chunk_AllocName (sizeof (maliasgroup_t) +
			(numframes) * sizeof (paliasgroup->frames[0]), loadname);

	paliasgroup->numframes = numframes;

	for (i=0 ; i<3 ; i++)
	{
	// these are byte values, so we don't have to worry about endianness
		pbboxmin->v[i] = pingroup->bboxmin.v[i];
		pbboxmax->v[i] = pingroup->bboxmax.v[i];
	}
	*pframeindex = (byte *)paliasgroup - (byte *)pheader;

	pin_intervals = (daliasinterval_t *)(pingroup + 1);
	poutintervals = chunk_AllocName (numframes * sizeof (float), loadname);

	paliasgroup->intervals = (byte *)poutintervals - (byte *)pheader;

	for (i=0 ; i<numframes ; i++)
	{
		*poutintervals = LittleFloat (pin_intervals->interval);
		if (*poutintervals <= 0.0)
			Sys_Error ("Mod_LoadAliasGroup: interval<=0");

		poutintervals++;
		pin_intervals++;
	}

	ptemp = (void *)pin_intervals;

	for (i=0 ; i<numframes ; i++)
	{
		ptemp = Mod_LoadAliasFrameChunk (ptemp,
									&paliasgroup->frames[i].frame,
									numv,
									&paliasgroup->frames[i].bboxmin,
									&paliasgroup->frames[i].bboxmax,
									pheader, name);
	}

	return ptemp;
}

/*
=================
Mod_LoadAliasSkin
=================
*/

void * chunk_LowMark(void);
int chunk_LowMarkInt(void);

void * Mod_LoadAliasSkinChunk (void * pin, int *pskinindex, int skinsize, disk_aliashdr_t *pheader);
#if !NO_MINIMIZE
void * Mod_LoadAliasSkinChunkTri (void * pin, int *pskinindex, int skinsize, disk_aliashdr_t *pheader,  stvert_t *oldpstverts, mtriangle_t *oldptri, int numtri, int skinwidth, int *pOriginalSkinIndex)
{
	byte	*pskin, *pinskin;
    pskin = chunk_LowMark();
#if 1
    for (int i = 0; i < numtri; i++)
    {
        coord16_t coords[3];
		//
		for (int j=0 ; j<3 ; j++)
		{

			int idx;
			if (j == 0)
			    idx = oldptri[i].vertindex0;
            else if (j == 1)
			    idx = oldptri[i].vertindex1;
            else
			    idx = oldptri[i].vertindex2;

            //
			int x = oldpstverts[idx].s16 + ((!oldptri[i].facesfront && oldpstverts[idx].onseam) ? skinwidth / 2 : 0);
			int y = oldpstverts[idx].t16;
			coords[j].s = x;
			coords[j].t = y;
		}
        if (coords[0].s == coords[1].s && coords[1].s == coords[2].s )
            if (coords[0].t == coords[1].t && coords[1].t == coords[2].t )
                FIXME("Single Point Triangle!");
        addSkinTriangle(pin, skinwidth, coords);
        chunk_Align4();         //needed to prevent loading unaligned addresses which will result later in 8 cycles per byte memcpy penalty!

    }
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
    byte	*pOriginalSkin = chunk_LowMark();
    chunk_AllocName(skinsize,"");
    memcpy(pOriginalSkin, pin, skinsize);   // copy old skin
    *pOriginalSkinIndex =  (byte *)pOriginalSkin - (byte *)pheader;
#endif
	pinskin = (byte *)pin;
	*pskinindex = (byte *)pskin - (byte *)pheader;



	pinskin += skinsize;

	return ((void *)pinskin);
}
#endif
#endif
//

void * Mod_LoadAliasSkinChunk (void * pin, int *pskinindex, int skinsize, disk_aliashdr_t *pheader)
{
    // This is quite hard to optimize. Looks like pskin is modified later.
	byte	*pskin, *pinskin;
	pskin = chunk_AllocName (skinsize * r_pixbytes, loadname);
	pinskin = (byte *)pin;
	*pskinindex = (byte *)pskin - (byte *)pheader;
    memcpy (pskin, pinskin, skinsize);
	pinskin += skinsize;

	return ((void *)pinskin);
}
/*
=================
Mod_LoadAliasSkinGroup
=================
*/
void * Mod_LoadAliasSkinGroupChunkTri (void * pin, int *pskinindex, int skinsize, disk_aliashdr_t *pheader, stvert_t *oldpstverts, mtriangle_t *oldptri, int numtri, int skinwidth)
{
	daliasskingroup_t		*pinskingroup;
	maliasskingroup_t		*paliasskingroup;
	int						i, numskins;
	daliasskininterval_t	*pinskinintervals;
	float					*poutskinintervals;
	void					*ptemp;

	pinskingroup = (daliasskingroup_t *)pin;

	numskins = LittleLong (pinskingroup->numskins);
	printf("This model has %d skins\r\n", numskins);
	paliasskingroup = chunk_AllocName (sizeof (maliasskingroup_t) +
			(numskins - 1) * sizeof (paliasskingroup->skindescs[0]),
			loadname);
	paliasskingroup->numskins = numskins;

	*pskinindex = (byte *)paliasskingroup - (byte *)pheader;

	pinskinintervals = (daliasskininterval_t *)(pinskingroup + 1);
	poutskinintervals = chunk_AllocName (numskins * sizeof (float),loadname);

	paliasskingroup->intervals = (byte *)poutskinintervals - (byte *)pheader;

	for (i=0 ; i<numskins ; i++)
	{
		*poutskinintervals = LittleFloat (pinskinintervals->interval);
		if (*poutskinintervals <= 0)
			Sys_Error ("Mod_LoadAliasSkinGroup: interval<=0");

		poutskinintervals++;
		pinskinintervals++;
	}

	ptemp = (void *)pinskinintervals;

	for (i=0 ; i<numskins ; i++)
	{
	    int skin, originalSkin;
		ptemp = Mod_LoadAliasSkinChunkTri (ptemp, &skin, skinsize, pheader, oldpstverts, oldptri, numtri, skinwidth, &originalSkin);
        paliasskingroup->skindescs[i].skin = skin;
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
        paliasskingroup->skindescs[i].originalSkin = originalSkin;
#if CACHEABLE_SKIN
        // this is set to 0xFFFFFFFF so that it can be overwritten into flash, after being cached.
         paliasskingroup->skindescs[i].pCachedSkin = 0xFFFFFFFF;
#endif
#endif // MODELS_HAVE_ORIGINAL_SKIN_TOO
	}

	return ptemp;
}
/*
*/
typedef struct
{
    uint16_t offsetS;          // the real s is a positive integer. To select the column in offsetTable, we need to remove this value.
    uint16_t bufferOffset;     // when we pass the buffer to retrieve the skin data, we need to subtract this value. This allows the offsetTable to be uint16_t instead of int32_t
    uint16_t numOffset;        // number of offsets for s calculation. It's the number of columns
    uint16_t offsetTablePos;
} triangle_decoder_t;
#define MIN_TRI_CALC 1
uint8_t getOriginalSkinPixel( uint8_t * skin, int width, int x, int y)
{
    return  skin[y * width + x];
}
#if OLD_INCREASESIZE
#else
void findBoundaries(int *minT, int *maxT, int t3, int t4)
{
    int min = *minT;
    if (min > *maxT) min = *maxT;
    if (min > t3) min = t3;
    if (min > t4) min = t4;
    int max = *minT;
    if (max < *maxT) max = *maxT;
    if (max < t3) max = t3;
    if (max < t4) max = t4;
    *minT = min;
    *maxT = max;
}
void findMinMaxT(int x0, int y0, int x1, int y1, int x, int *minY, int *maxY)
{
    // clip boundaries:
    int minx = x0;
    if (minx > x1) minx = x1;
    int maxx = x0;
    if (maxx < x1) maxx = x1;
    if (x < minx)
    {
        x = minx;
    }
    if (x > maxx)
    {
        x = maxx;
    }

    int dx = x1 - x0;
    if (dx < 0) dx = -dx;
    int sx = x0 < x1 ? 1 : -1;
    int dy = (y1 - y0);
    if (dy > 0) dy = -dy;
    int sy = y0 < y1 ? 1 : -1;
    int error = dx + dy;
    int foundX = 0;

    int firstY = -1, secondY = -2;
   // printf("x0 = %d, y0 = %d, x1 = %d, y1 = %d\r\n", x0, y0, x1, y1);
    while (1)
    {
        if (x0 == x && foundX == 0)
        {   // first time we find x
            firstY = y0;
            secondY = y0;
            foundX = 1;
        }
        else if (x0 == x && foundX == 1)
        {
            secondY = y0;
        }
        else if (foundX == 1 && x0 != x )
        {
            // finish.
            if (secondY > firstY)
            {
                *minY = firstY;
                *maxY = secondY;
            }
            else
            {
                *minY = secondY;
                *maxY = firstY;
            }
            return;
        }
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * error;
        if (e2 >= dy)
        {
            if (x0 == x1) break;
            error = error + dy;
            x0 = x0 + sx;
        }
        if (e2 <= dx)
        {
            if (y0 == y1) break;
            error = error + dx;
            y0 = y0 + sy;
        }
    }
    // finish, it was last point
    secondY = y0;
    if (!foundX)
        firstY = y0;
    if (secondY > firstY)
    {
        *minY = firstY;
        *maxY = secondY;
    }
    else
    {
        *minY = secondY;
        *maxY = firstY;
    }
    return;
}
void clip(int *sclip, int minS, int maxS)
{
    if (*sclip > maxS + 1)
    {
        *sclip = maxS + 1;
    }
    else if (*sclip < minS)
    {
        *sclip = minS;
    }
}
#if 1
int addSkinTriangle(uint8_t *skin, int width, coord16_t *coords)
{
    int r;
    // find how is our triangle
    uint16_t minS = coords[0].s;
    uint16_t maxS = coords[0].s;
    uint16_t minT = coords[0].t;
    uint16_t maxT = coords[0].t;
    int leftmost = 0;
    int rightmost = 0;
    for (int i = 1; i < 3; i++)
    {
        if (minS > coords[i].s)
        {
            minS = coords[i].s;
            leftmost = i;
        }
        if (minT > coords[i].t)
            minT = coords[i].t;
        if (maxS < coords[i].s)
        {
            maxS = coords[i].s;
            rightmost = i;
        }
        if (maxT < coords[i].t)
            maxT = coords[i].t;
    }
    // now we have the minimum s and t values. these will be our offsets
    // Now, we will draw a line between the leftmost and rightmost, and from these two to the central
    int central = 3 - leftmost - rightmost;
    if (central == 3)
    {
        central = 1;
        rightmost = 2;
        leftmost = 0;
    }
    // for each column, it will say where x = 0 is located.
    if (minT == maxT)
    {
        for (int s = minS; s <= maxS; s++)
        {
                    uint8_t pix =  getOriginalSkinPixel(skin, width, s, maxT);
                    uint8_t *dest = chunk_AllocName(1, "");
                    *dest = pix;
        }
    }
    else if (minS != maxS)
    {
        if (coords[central].s == maxS)
        {
            // two points are aligned to the right.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[central].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);

                t1-= REMOVE_T; t2 += ADD_T; // ADDED

                for (int t = t1; t <= t2; t++)
                {
                    uint8_t pix =  getOriginalSkinPixel(skin, width, s, t);
                    uint8_t *dest = chunk_AllocName(1, "");
                    *dest = pix;
                }
            }
        }
        else if (coords[central].s == minS)
        {
            // two points are aligned to the left.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);

                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                for (int t = t1; t <= t2; t++)
                {
                    uint8_t pix = getOriginalSkinPixel(skin, width, s, t);
                    uint8_t *dest = chunk_AllocName(1, "");
                    *dest = pix;
//                    dbgDrawTriPixel(s, t, pix, 0);

                }
            }

        }
        else
        {
            // three points not x-aligned.
            // from leftmost to central
            for (int s = minS - REMOVE_S; s < coords[central].s; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, coords[central].s, coords[central].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                for (int t = t1; t <= t2; t++)
                {
                    uint8_t pix = getOriginalSkinPixel(skin, width, s, t);
                    uint8_t *dest = chunk_AllocName(1, "");
                    *dest = pix;
                }
            }
            // from central to rightmost
            for (int s = coords[central].s; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(coords[central].s, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED

                for (int t = t1; t <= t2; t++)
                {
                    uint8_t pix = getOriginalSkinPixel(skin, width, s, t);
                    uint8_t *dest = chunk_AllocName(1, "");
                    *dest = pix;
                }
            }
        }
        r = 1;
    }
    else
    {
        int t1  = coords[0].t;
        int t2 =  coords[0].t;
        if (t1 > coords[1].t)
            t1 = coords[1].t;
        if (t1 > coords[2].t)
            t1 = coords[2].t;
        if (t2 < coords[1].t)
            t2 = coords[1].t;
        if (t2 < coords[2].t)
        {
            t2 = coords[2].t;
        }
        int s = coords[0].s;
        t1-= REMOVE_T; t2 += ADD_T; // ADDED
        for (int t = t1; t <= t2; t++)
        {
            uint8_t pix = getOriginalSkinPixel(skin, width, s, t);
            uint8_t *dest = chunk_AllocName(1, "");
            *dest = pix;
        }
        r = 0;
    }
    return r;
}
int calculateTriangleOffsets(coord16_t *coords, mtriangleOffsetData_t **tod, uint32_t *offset_, int *numberOfOffsets, unsigned int *tridatasize, uint32_t *startOffset, uint32_t *bufferOffset, uint32_t *offsetS)
{
  //  int firstT;
    uint32_t offsetv;
    offsetv = *offset_;
    uint32_t *offset = &offsetv;
    if (offsetv  >= 65536)
        while(1) FIXME("Error: vertical offset is larger than 65535");
    int r;
    // find how is our triangle
    uint16_t minS = coords[0].s;
    uint16_t maxS = coords[0].s;
    uint16_t minT = coords[0].t;
    uint16_t maxT = coords[0].t;
    int leftmost = 0;
    int rightmost = 0;
    *tridatasize = 0;
    for (int i = 1; i < 3; i++)
    {
        if (minS > coords[i].s)
        {
            minS = coords[i].s;
            leftmost = i;
        }
        if (minT > coords[i].t)
            minT = coords[i].t;
        if (maxS < coords[i].s)
        {
            maxS = coords[i].s;
            rightmost = i;
        }
        if (maxT < coords[i].t)
            maxT = coords[i].t;
    }
    // now we have the minimum s and t values. these will be our offsets
    // Now, we will draw a line between the leftmost and rightmost, and from these two to the central
    int central = 3 - leftmost - rightmost;
    //
    if (central == 3)
    {
        rightmost = 0;
        leftmost = 1;
        central = 2;
    }
    chunk_Align4();
#if MTRIANGLE_HAS_OFFSET_DATA
    *tod =  chunk_AllocName((maxS - minS + 1 + ADD_S + REMOVE_S) * sizeof( ((mtriangleOffsetData_t *)(NULL))->offsets[0]), "");
#else
    *tod =  chunk_AllocName((maxS - minS + 1 + ADD_S + REMOVE_S) * sizeof( ((mtriangleOffsetData_t *)(NULL))->offsets[0]) + sizeof(**tod), "");
#endif

    mtriangleOffsetData_t *td = *tod;
    *startOffset = offsetv;
    uint16_t *offsetTable = td->offsets;
    *offsetS = minS - REMOVE_S;
    *numberOfOffsets = (maxS - minS + 1 + ADD_S + REMOVE_S);

#if MTOD_HAS_SENTINEL
    td->sentinel = 'D' | ('O' << 8) |('O' << 16) | ('M' << 24) ;
#endif
    *bufferOffset = maxT + ADD_T;
    //
    if (minS != maxS)
    {
        // this slope is common for all triangles
        if (coords[central].s == maxS)
        {
            // two points are aligned to the right.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[central].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED

                offsetTable[s - (minS - REMOVE_S)] = *offset - t1 + *bufferOffset;  // we will sum to S this value, to get each column position in the buffer
                *offset = *offset +  t2 - t1 + 1;
                *tridatasize = *tridatasize +  t2 - t1 + 1;
            }
        }
        else if (coords[central].s == minS)
        {
            // two points are aligned to the left.
            for (int s = minS - REMOVE_S; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);

                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                offsetTable[s - (minS - REMOVE_S)] = *offset - t1 + *bufferOffset;  // we will sum to S this value, to get each column position in the buffer
                *offset = *offset +  t2 - t1 + 1;
                *tridatasize = *tridatasize +  t2 - t1 + 1;
            }

        }
        else
        {
            // three points not x-aligned.
            // from leftmost to central
            for (int s = minS - REMOVE_S; s < coords[central].s; s++)
            {
                int t1, t2;
                findMinMaxT(minS, coords[leftmost].t, coords[central].s, coords[central].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                offsetTable[s - (minS - REMOVE_S)] = *offset - t1 + *bufferOffset;  // we will sum to S this value, to get each column position in the buffer
                *offset = *offset +  t2 - t1 + 1;
                *tridatasize =  *tridatasize + t2 - t1 + 1;

            }
            // from central to rightmost
            for (int s = coords[central].s; s <= maxS + ADD_S; s++)
            {
                int t1, t2;
                findMinMaxT(coords[central].s, coords[central].t, maxS, coords[rightmost].t, s, &t1, &t2);
                int t3, t4;
                findMinMaxT(minS, coords[leftmost].t, maxS, coords[rightmost].t, s, &t3, &t4);
                findBoundaries(&t1, &t2, t3, t4);
                t1-= REMOVE_T; t2 += ADD_T; // ADDED
                offsetTable[s - (minS - REMOVE_S)] = *offset - t1 + *bufferOffset;  // we will sum to S this value, to get each column position in the buffer
                *offset = *offset +  t2 - t1 + 1;
                *tridatasize = *tridatasize + t2 - t1 + 1;

            }
        }
        r = 1;
    }
    else
    {
        // todo fix this shit source of headaches!
        int t1  = coords[0].t;
        int t2 =  coords[0].t;
        if (t1 > coords[1].t)
            t1 = coords[1].t;
        if (t1 > coords[2].t)
            t1 = coords[2].t;
        if (t2 < coords[1].t)
            t2 = coords[1].t;
        if (t2 < coords[2].t)
            t2 = coords[2].t;
        int s = coords[0].s;
        t1-= REMOVE_T; t2 += ADD_T; // ADDED
//        firstT = t1;
        for (int t = t1; t <= t2; t++)
        {
                offsetTable[s - (minS - REMOVE_S)] = *offset - t1 + *bufferOffset;  // we will sum to S this value, to get each column position in the buffer
        }
       *offset = *offset +  t2 - t1 + 1;
       *tridatasize = *tridatasize +  t2 - t1 + 1;
        r = 0;
    }
    if (*offset > 65535)
    {
        FIXME("Error, offset is larger than 65535");
    }
    *offset_ = (*offset + 3) & ~3;  // added this to prevent data to be stored not 4-bytes aligned
    return r;
}

#endif
#endif

#define TEMP_HUNK_CODE 1
#if TEMP_HUNK_CODE
#define HUNK_SIZE 20485760       // should be enough for each
byte chunkdata[HUNK_SIZE];
static int chunkPos = 0;
void * chunk_AllocName(uint32_t size, char * name)
{
    if (chunkPos + size > HUNK_SIZE)
    {
        Sys_Error("Too much chunk alloc (%d %d)!", chunkPos, size);
        return NULL;
    }
//    printf("Allocating %d bytes\r\n", size);
    void *data = &chunkdata[chunkPos];
    chunkPos += size;
    memset(data, 0, size);
    return data;
}
void chunk_Align4()
{
    chunkPos = (chunkPos + 3) & ~3;
}
void chunk_Flush()
{
    memset(chunkdata, 0, sizeof(chunkdata));
    chunkPos = 0;
}
void * chunk_LowMark(void)
{
    return  &chunkdata[chunkPos];
}
int chunk_LowMarkInt(void)
{
    return  chunkPos;
}
#endif // TEMP_HUNK_CODE
/*
=================
Mod_LoadAliasModel
=================
*/

void* Mod_LoadAliasModel2 (model_t *mod, void *buffer, 	disk_aliashdr_t	*poldHeader)
{
    static int maxVertsSeen = 0;
    	int					i;
	disk_mdl_t				*pmodel, *pinmodel;
	stvert_t			*pstverts;
    dstvert_t           *pinstverts;

	disk_aliashdr_t			*pheader;
	mtriangle_t			*ptri;
	dtriangle_t			*pintriangles;
	int					version, numframes, numskins;
	int					size;
	daliasframetype_t	*pframetype;
	daliasskintype_t	*pskintype;
	maliasskindesc_t	*pskindesc;
	int					skinsize;


    pinmodel = (disk_mdl_t *)buffer;

	version = LittleLong (pinmodel->version);
	if (version != ALIAS_VERSION)
		Sys_Error ("%s has wrong version number (%i should be %i)",
				 mod->name, version, ALIAS_VERSION);
//
// allocate space for a working header, plus all the data except the frames,
// skin and group info
//
	size = 	sizeof (disk_aliashdr_t) + (LittleLong (pinmodel->numframes)) *
			 sizeof (pheader->frames[0]) +
			sizeof (disk_mdl_t) +
			LittleLong (pinmodel->numverts) * sizeof (stvert_t) +
			LittleLong (pinmodel->numtris) * sizeof (mtriangle_t);
  //  printf("Line %d %s  size: %d ", __LINE__ , __PRETTY_FUNCTION__, size);
    chunk_Align4();
	pheader = chunk_AllocName (size, loadname);
	pmodel = (disk_mdl_t *) ((byte *)&pheader[1] +
			(LittleLong (pinmodel->numframes)) *
			 sizeof (pheader->frames[0]));
    pheader->id = IDPOLYHEADER_MEMORY_READY;
    //
	mod->flags = LittleLong (pinmodel->flags);
	// copy to pmodel so that it can be retrieved later for mod.
    pmodel->flags = LittleLong (pinmodel->flags);
    pmodel->synctype = LittleLong (pinmodel->synctype);
    //
    // endian-adjust and copy the data, starting with the alias model header
    //
	pmodel->boundingradius = LittleFloat (pinmodel->boundingradius);
	pmodel->numskins = LittleLong (pinmodel->numskins);
	printf("This model has %d skins\r\n", pmodel->numskins );
	pmodel->skinwidth = LittleLong (pinmodel->skinwidth);
	pmodel->skinheight = LittleLong (pinmodel->skinheight);

	if (pmodel->skinheight > MAX_LBM_HEIGHT)
		Sys_Error ("model %s has a skin taller than %d", mod->name,
				   MAX_LBM_HEIGHT);

	pmodel->numverts = LittleLong (pinmodel->numverts);
    // some profiling...
    if (pmodel->numverts > maxVertsSeen)
    {
        maxVertsSeen = pmodel->numverts;
        printf("Max number of Vertex seen reached %d\r\n", pmodel->numverts);
    }
	if (pmodel->numverts <= 0)
		Sys_Error ("model %s has no vertices", mod->name);

	if (pmodel->numverts > MAXALIASVERTS)
		Sys_Error ("model %s has too many vertices, %d", mod->name, pmodel->numverts);

	pmodel->numtris = LittleLong (pinmodel->numtris);

	if (pmodel->numtris <= 0)
		Sys_Error ("model %s has no triangles", mod->name);

	pmodel->numframes = LittleLong (pinmodel->numframes);
	if (pmodel->numframes >= 256)
	    FIXME("TOO MANY FRAMES");
	pmodel->size = LittleFloat (pinmodel->size) * ALIAS_BASE_SIZE_RATIO;
	mod->synctype = LittleLong (pinmodel->synctype);
	mod->numframes = pmodel->numframes;

	for (i=0 ; i<3 ; i++)
	{
		pmodel->scale[i] = LittleFloat (pinmodel->scale[i]);
		pmodel->scale_origin[i] = LittleFloat (pinmodel->scale_origin[i]);
		pmodel->eyeposition[i] = LittleFloat (pinmodel->eyeposition[i]);
	}

	numskins = pmodel->numskins;
	numframes = pmodel->numframes;
    static int maxSkinSize = 0;
	if (pmodel->skinwidth & 0x03)
		Sys_Error ("Mod_LoadAliasModel: skinwidth not multiple of 4");

	pheader->model = (byte *)pmodel - (byte *)pheader;

//
// load the skins
//
	skinsize = pmodel->skinheight * pmodel->skinwidth;
    printf("This model has skin %d bytes large\r\n", skinsize);
//
	if (numskins < 1)
		Sys_Error ("Mod_LoadAliasModel: Invalid # of skins: %d\n", numskins);

	pskintype = (daliasskintype_t *)&pinmodel[1];
  //  printf("Line %d %s  Skins size: %d ", __LINE__ , __PRETTY_FUNCTION__, numskins * sizeof (maliasskindesc_t));
	pskindesc = chunk_AllocName (numskins * sizeof (maliasskindesc_t),
								loadname);
	static int totalSkin = 0;
	int skinMarkStart = chunk_LowMarkInt();
	pheader->skindesc = (byte *)pskindesc - (byte *)pheader;
 //   printf("SIZE WAS %d SKINDESK is %d, sizeof header is %d\r\n", size, pheader->skindesc, sizeof (*pheader));
	for (i=0 ; i<numskins ; i++)
	{
		aliasskintype_t	skintype;

		skintype = LittleLong (pskintype->type);
		pskindesc[i].type = skintype;
#if CACHEABLE_SKIN
        pskindesc[i].pCachedSkin = 0xFFFFFFFF;
#endif
		if (skintype == ALIAS_SKIN_SINGLE)
		{
		    int skin, originalSkin;
		    if (!poldHeader )
            {
                pskintype = (daliasskintype_t *) Mod_LoadAliasSkinChunk (pskintype + 1, &skin, skinsize, pheader);
                originalSkin = skin;
            }
            else
            {
                stvert_t			*oldpstverts;
 	            mtriangle_t			*oldptri;
                oldpstverts = (stvert_t *) ((((byte *) poldHeader) + poldHeader->stverts) );
                oldptri = (mtriangle_t*)   ((((byte *) poldHeader) + poldHeader->triangles) );
                pskintype = (daliasskintype_t *) Mod_LoadAliasSkinChunkTri (pskintype + 1, &skin, skinsize, pheader, oldpstverts, oldptri, pmodel->numtris, pmodel->skinwidth, &originalSkin);
            }
#if MODELS_HAVE_ORIGINAL_SKIN_TOO
            pskindesc[i].originalSkin = originalSkin;
#if CACHEABLE_SKIN
            pskindesc[i].pCachedSkin = 0xFFFFFFFF;      // this so that it can be overwritten in internal flash once cached.
#endif
#endif // MODELS_HAVE_ORIGINAL_SKIN_TOO
            pskindesc[i].skin = skin;
		}
		else
		{
		    while(1)
		        FIXME("SKINGROUP: I thought these were not present!");
#if 0 // DISABLED. I did not find SKINGROUP
		    int skin;
		    if (!poldHeader)
            {
    			pskintype = (daliasskintype_t *) Mod_LoadAliasSkinGroupChunk (pskintype + 1, &skin, skinsize, pheader);
            }
            else
            {
                stvert_t			*oldpstverts;
 	            mtriangle_t			*oldptri;
                oldpstverts = (stvert_t *) ((((byte *) poldHeader) + poldHeader->stverts) );
                oldptri = (mtriangle_t*)   ((((byte *) poldHeader) + poldHeader->triangles) );
                pskintype = (daliasskintype_t *) Mod_LoadAliasSkinGroupChunkTri (pskintype + 1, &skin, skinsize, pheader, oldpstverts, oldptri, pmodel->numtris, pmodel->skinwidth);
            }
            pskindesc[i].skin = skin;
#endif
		}
	}
	int skinMark = chunk_LowMarkInt();
	if (poldHeader)
	    totalSkin += skinMark - skinMarkStart;
	if (skinsize > maxSkinSize)
	    maxSkinSize = skinsize;
//	printf("Skin Size = %d. Number of skins %d\r\n", skinsize, numskins);

//
// set base s and t vertices
//
	pstverts = (stvert_t *)&pmodel[1];
	pinstverts = (dstvert_t *)pskintype;

	pheader->stverts = (byte *)pstverts - (byte *)pheader;
      static int offsetTableOccupation = 0, deltax = 0;
	for (i=0 ; i<pmodel->numverts ; i++) // already in header
	{
		pstverts[i].onseam = LittleLong (pinstverts[i].onseam) != 0;
	// put s and t in 16.16 format
		pstverts[i].s16 = LittleLong (pinstverts[i].s);
		pstverts[i].t16 = LittleLong (pinstverts[i].t);
	}

//
// set up the triangles
//
	ptri = (mtriangle_t *)&pstverts[pmodel->numverts];
	pintriangles = (dtriangle_t *)&pinstverts[pmodel->numverts];

	pheader->triangles = (byte *)ptri - (byte *)pheader;
    static int totalAreaPixels = 0;
    int areaM = 0;
    int sumX = 0, sumY = 0;
    static int totalSumX = 0, totalSumY = 0, totalMinSum = 0;

    if (pmodel->skinheight * pmodel->skinheight > 65535)
    {
        printf("Skin too big: %d %d\r\n", pmodel->skinwidth, pmodel->skinheight);
        while(1)
            system("pause");
    }
    uint32_t offset = 0;
    int tringlePixData = 0;
	for (i=0 ; i<pmodel->numtris ; i++)  // already in header
	{
		int		j;
		ptri[i].facesfront = LittleLong (pintriangles[i].facesfront);
		#if TRIANGLE_HAS_SENTINEL
		ptri[i].sentinel = 0xDEADBEEF;
		#endif
        coord16_t coords[3];
		//
    int minx = 1000000;
    int maxx = -1;

        ptri[i].vertindex0 = LittleLong (pintriangles[i].vertindex[0]);
        ptri[i].vertindex1 = LittleLong (pintriangles[i].vertindex[1]);
        ptri[i].vertindex2 = LittleLong (pintriangles[i].vertindex[2]);

		for (j=0 ; j<3 ; j++)
		{
			int idx;
			if (j == 0)
			    idx = ptri[i].vertindex0;
            else if (j == 1)
			    idx = ptri[i].vertindex1;
            else
			    idx = ptri[i].vertindex2;

			int x = pinstverts[idx].s + ((!ptri[i].facesfront && pinstverts[idx].onseam) ? pmodel->skinwidth / 2 : 0);
			int y = pinstverts[idx].t;
			coords[j].s = x;
			coords[j].t = y;
			if (minx > x) minx =x;
			if (maxx < x) maxx = x;
		}

        mtriangleOffsetData_t *tod;
      //  printf ("tri: %d\r\n", i);

      int otmark = chunk_LowMarkInt();
      int numberOfOffsets;
      unsigned int tridatasize = 8999;
      uint32_t offsetS, startOffset, bufferOffset;
      calculateTriangleOffsets(coords, &tod, &offset, &numberOfOffsets, &tridatasize, &startOffset, &bufferOffset, &offsetS);
#if MTRIANGLE_HAS_OFFSET_DATA
    ptri[i].offsetS = offsetS;
    ptri[i].startOffset = startOffset;
    ptri[i].bufferOffset = bufferOffset;
#else
    tod->offsetS = offsetS;
    tod->startOffset = startOffset;
    tod->bufferOffset = bufferOffset;
#endif // MTRIANGLE_HAS_OFFSET_DATA
      int otmark2 = chunk_LowMarkInt();
      if (poldHeader)
      {
        offsetTableOccupation+= otmark2 - otmark;
        deltax += maxx - minx;
      }
        uint32_t todOffset = (byte *) tod - (byte *)pheader;
        if (todOffset > 32767 * 4 || (todOffset & 3))
        {
            printf("todOffset > 32767 * 4 %u. OldHeader %p, offset &3 is %d\r\n", todOffset, poldHeader, todOffset & 3);
            while (1) FIXME("OFFSET TOO BIG");
        }
        ptri[i].triangleOffsetDataPos = todOffset >> 2;     // word aligned
        ptri[i].triangleOffsetNumber = numberOfOffsets;
        if (numberOfOffsets > 255)
        {
            while(1)
                FIXME("Too many offsets!");
        }
        if (tridatasize > 4096)
        {
            while(1)
                FIXME("triangle data size too large!");

        }
        static int maxTridataSize = 0;
        if (maxTridataSize < tridatasize)
        {
                maxTridataSize = tridatasize;
        }
        ptri[i].triangleSize = tridatasize;
        tringlePixData +=tridatasize;
        #if !NO_TEST_MTOD
          mtriangleOffsetData_t *ttod;
          ttod = ( mtriangleOffsetData_t *) ((byte *)pheader +  (ptri[i].triangleOffsetDataPos << 2));
#if !MTRIANGLE_HAS_OFFSET_DATA
          if (ttod->offsetS > 320)
          {
            printf("ttod->offsetS > 320, %d. The expected is %d\r\n", ttod->offsetS, tod->offsetS);
            system("pause");
          }
#else
          if (ptri[i].offsetS > 320)
          {
            printf("ptri[i].offsetS > 320, %d. The expected is %d\r\n",ptri[i].offsetS, ptri[i].offsetS);
            system("pause");
          }

#endif
        #endif
    }
    totalAreaPixels += areaM;
    totalSumX += sumX;
    totalSumY += sumY;
    if (sumY > sumX)
        totalMinSum += sumX;
    else
        totalMinSum += sumY;
//
// load the frames
//
	if (numframes < 1)
		Sys_Error ("Mod_LoadAliasModel: Invalid # of frames: %d\n", numframes);

	pframetype = (daliasframetype_t *)&pintriangles[pmodel->numtris];
	static int totalFrame = 0;
    printf("There are %d frames\r\n", numframes);
    if (poldHeader) totalFrame += numframes;
    printf("total frames: %d\r\n", totalFrame);
    static int totalVertexAnimations = 0;
    if (poldHeader)
    {
        totalVertexAnimations -= (uint32_t) chunk_LowMarkInt();
    }
	for (i=0 ; i<numframes ; i++)
	{
		aliasframetype_t	frametype;

		frametype = LittleLong (pframetype->type);
		pheader->frames[i].type = frametype;

		if (frametype == ALIAS_SINGLE)
		{
            char dummy[16];
            int frame;
			pframetype = (daliasframetype_t *)
					Mod_LoadAliasFrameChunk (pframetype + 1,
										&frame,
										pmodel->numverts,
										&pheader->frames[i].bboxmin,
										&pheader->frames[i].bboxmax,
										pheader,dummy);
            pheader->frames[i].frame = frame;
            if (frame & 3)
            {
                printf("Frame is %x, not word-aligned", frame);
                FIXME("Error on alias single");
            }
		}
		else
		{
            char dummy[16];
            int frame;
			pframetype = (daliasframetype_t *)
					Mod_LoadAliasGroupChunk (pframetype + 1,
										&frame,
										pmodel->numverts,
										&pheader->frames[i].bboxmin,
										&pheader->frames[i].bboxmax,
										pheader, dummy);
            pheader->frames[i].frame = frame;
            if (frame & 3)
            {
                printf("Frame is %x, not word-aligned", frame);
                FIXME("error on alias multi");
            }

		}
	}
    if (poldHeader)
        totalVertexAnimations += (uint32_t) chunk_LowMarkInt();
    if (poldHeader)
    {
        static int oldTotalVertex = 0;
        printf("Total bytes for vertex: %d. This model: %d, per frame %f\r\n", totalVertexAnimations, totalVertexAnimations - oldTotalVertex, (float)(totalVertexAnimations - oldTotalVertex) / numframes);
        printf("Num triangles: %d\r\n", pmodel->numtris);
        oldTotalVertex = totalVertexAnimations;
        printf("mtod data %d\r\n", offsetTableOccupation);
//        FIXME("");

    }
	mod->type = mod_alias;

// FIXME: do this right
#if NEW_MODEL
	mod->mins_s[0] = mod->mins_s[1] = mod->mins_s[2] = -16;
	mod->maxs_s[0] = mod->maxs_s[1] = mod->maxs_s[2] = 16;
#endif
//
// move the complete, relocatable alias model to the cache
//
    printf("Total occupied by skins %d. MaxSkinSize %d. Area %d, Total Area %d\r\n", totalSkin, maxSkinSize, areaM, totalAreaPixels);
    printf("Total sum x %d, y %d. Total MinSum = %d\r\n", totalSumX, totalSumY, totalMinSum);
    printf("Skin Width %d, skin height %d, skin rect size %d\r\n", pmodel->skinwidth, pmodel->skinheight, pmodel->skinheight * pmodel->skinwidth);
    static int maxSkinDataSize = 0;
    printf("Total Triangle Data size for model %s %d, max %d\r\n", mod->name, tringlePixData, maxSkinDataSize);
    if (maxSkinDataSize < tringlePixData)
    {
        maxSkinDataSize = tringlePixData;
    }
    return pheader;
}
uint8_t skytexture[128*256];
uint8_t* Modify_Textures(uint8_t * buffer, int size, int *newSize)
{
    static int firstTimeSky = 0;

    dmiptexlump_t *m;
	m = (dmiptexlump_t *)(buffer);
	miptex_t	*mt;
    printf("There  are %d textures \r\n", m->nummiptex);

	for (int i=0 ; i < m->nummiptex ; i++)
	{
		if (m->dataofs[i] == -1)
			continue;
		mt = (miptex_t *)((byte *)m + m->dataofs[i]);
        //
		if (strstr(mt->name,"sky"))
        {
            if (!firstTimeSky)
            {
                printf("Copying skytex\r\n");
                memcpy(skytexture, mt+1, sizeof(skytexture));
            }
            else
            {
                if (memcmp(skytexture, mt+1, sizeof(skytexture)))
                {
                    printf("Different Sky\r\n");
                }
                else
                {
                    printf("same Sky\r\n");
                }
            }
            firstTimeSky = 1;
            printf("Found a sky!\r\n");
            addSky((uint8_t*) (mt+1), modelName); // skydata follows miptex structure.
        }
	}
    uint8_t * data = chunk_AllocName(size , "");
    memcpy(data, buffer, size);
    *newSize = size;
    return data;
}
//--------------------------- MODIFICATION OF NODES
void Mod_SetParent (mnode_t *node, mnode_t *parent, model_t *model)
{
    if (parent == NULL)
    {
        node->parent_idx = - 1;
    }
    else
    {
        node->parent_idx = parent - modelNodes;
    }
	if (node->contents < 0)
		return;
	Mod_SetParent (Mod_GetChildNode(node, 0, model), node, model);
	Mod_SetParent (Mod_GetChildNode(node, 1, model), node, model);
}

mnode_t *Mod_GetParent(mnode_t *node, model_t *model)
{
    if (node->parent_idx < 0)
        return NULL;
    else
        return modelNodes + node->parent_idx;
}
mnode_t * Mod_GetChildNode(mnode_t *node, int childNumber, model_t * model)
{
    int p = node->children_idx[childNumber];
    if (p >= 0)
    {
        return modelNodes + p;
    }
    else
    {
        return (mnode_t *)(modelLeafs + (-1 - p));
    }
}
/*
=================
Mod_LoadNodes
=================
*/

void Mod_LoadLeafs (lump_t *l, byte *data)
{
	dleaf_t 	in;
	dleaf_t 	*pin;
	mleaf_t 	*out;
	int			i, j, count, p;

	pin = (void *)(data);
	count = l->filelen / sizeof(in);
    mleaf_t *buff =  out = calloc(count, sizeof(*out));

    modelNumleafs = count;
#if PROFILE_NUM_ELEMENTS
    PROFILE(Leaves, modelNumleafs);
#endif // PROFILE_NUM_ELEMENTS
	for ( i=0 ; i<count ; i++, out++)
	{
	    memcpy(&in, pin, sizeof(in));
	    pin++;
		for (j=0 ; j<3 ; j++)
		{
			out->minmaxs[j] = in.mins[j];
			out->minmaxs[3+j] = in.maxs[j];
		}

		p = LittleLong(in.contents);
		out->leaf_idx = i;
		out->contents = p;
        out->firstMarkSurfaceIdx = in.firstmarksurface;
		out->nummarksurfaces = in.nummarksurfaces;

		p = in.visofs;
		if (p > 65534)
		    FIXME(" too large COMPRESSED VIS");
        out->compressed_vis_idx = p;

#if LEAF_HAS_EFRAGS
		out->efrags = NULL;
#endif
		for (j=0 ; j<4 ; j++)
			out->ambient_sound_level[j] = in.ambient_level[j];
	}
    modelLeafs = buff;

}


void Mod_LoadNodes (lump_t *l, byte *data, int *newSize)
{

	int			i, j, count, p;
	dnode_t		in;
	dnode_t		*pin;

	mnode_t 	*out;

    short *surfnode = calloc( sizeof (short) * modelNumsurfaces, 1);

	pin = (dnode_t *) data;

	count = l->filelen / sizeof(*pin);




    mnode_t *buff = out = calloc(count * sizeof(*out), 1);

    modelNumnodes = count;
#if PROFILE_NUM_ELEMENTS
    PROFILE(Nodes, modelNumnodes);
#endif // PROFILE_NUM_ELEMENTS

	if (count > MAX_MAP_NODES)
    {
        printf("n Nodes: %d\r\n", count);
        FIXME("ERROR");
    }

	for ( i=0 ; i<count ; i++, out++)
	{
	    memcpy(&in, pin, sizeof(in));
	    pin++;
		for (j=0 ; j<3 ; j++)
		{
			out->minmaxs[j] = in.mins[j];
			out->minmaxs[3+j] = in.maxs[j];
		}

		p = in.planenum;
        out->plane_idx = p;
        if (p > 32767 || p < -32768)
            while(1) FIXME("BAD planenum");
        out->node_idx = i;
		out->firstsurface = in.firstface;
		out->numsurfaces = in.numfaces;
        for (int s = out->firstsurface; s < out->firstsurface + out->numsurfaces; s++)
        {
            surfnode[s] = i;            // set the surface node
        }
		for (j=0 ; j<2 ; j++)
		{
			p = in.children[j];
            out->children_idx[j] = p;
		}
	}
	surfNodeIndex = surfnode;
	modelNodes = buff;
	//
    Mod_SetParent (modelNodes, NULL, NULL);	// sets nodes and leafs
    //
	*newSize = 2 + 2 + sizeof(*surfnode) * modelNumsurfaces + sizeof(*modelNodes) * count + sizeof(*modelLeafs) * modelNumleafs;
	mnodeData = calloc(*newSize, 1);
	// set mnode count
	printf("Count is %d. NumSurfaces is %d\r\n", count, modelNumsurfaces);
	mnodeData[0] = count & 0xFF;
	mnodeData[1] = count >> 8;
	//
	mnodeData[2] = modelNumleafs & 0xFF;
	mnodeData[3] = modelNumleafs >> 8;

	// then store data
	memcpy(&mnodeData[4], surfNodeIndex, sizeof(*surfNodeIndex) * modelNumsurfaces );
	memcpy(mnodeData + 4 + sizeof(*surfNodeIndex) * modelNumsurfaces, modelNodes,   sizeof(*modelNodes) * count );
	memcpy(mnodeData + 4 + sizeof(*surfNodeIndex) * modelNumsurfaces + sizeof(*modelNodes) * count,
        modelLeafs,   sizeof(*modelLeafs) * modelNumleafs );

	free(surfNodeIndex);
	free(modelNodes);
	free(modelLeafs);
}
int lumpLoadOrder[] =
{
    LUMP_VERTEXES,
    LUMP_EDGES,
    LUMP_SURFEDGES,
    LUMP_TEXTURES,
    LUMP_LIGHTING,
    LUMP_PLANES,
    LUMP_TEXINFO,
    LUMP_FACES,
    LUMP_MARKSURFACES,
    LUMP_VISIBILITY,
    LUMP_LEAFS,
    LUMP_NODES,
    LUMP_CLIPNODES,
    LUMP_ENTITIES,
    LUMP_MODELS,
};
uint8_t * Convert_BrushModel(model_t *mod, uint8_t *buffer, uint32_t * size)
{
    modelName = mod->name;
    printf("Brush Model Name %s\r\n", modelName);
    dheader_t * header = (dheader_t *)buffer;
    //
    chunk_Flush();
    // allocate the new file
    uint8_t *newFile = chunk_AllocName(sizeof(dheader_t), "");
    dheader_t *newHeader = (dheader_t *)newFile;
    // copy version
    newHeader->version = header->version;
    // align (not really needed, header 4-byte is aligned)
    chunk_Align4();
    for (int l = 0; l < HEADER_LUMPS; l++)
    {
        int i = lumpLoadOrder[l];   // this because we need
        uint8_t *data;
        lump_t *plump = &header->lumps[i];
        lump_t *pnewlump = &newHeader->lumps[i];
        int newLumpSize = plump->filelen;   // copy old value this if not modified
        pnewlump->fileofs= chunk_LowMarkInt(); // get current offset
        printf("Lump %i has ofs %i and len %i. 4-byte divisible length: %s\r\n", i, plump->fileofs, plump->filelen, (plump->filelen &3) ? "NOOOO" : "yes") ;
        uint8_t *oldLumpBuffer = &buffer[plump->fileofs];
        switch (i)
        {
            case LUMP_CLIPNODES:
                {
                        printf("clipnode Lump %i will be copied without modifications\r\n", i);
                        data = chunk_AllocName(plump->filelen , "" );
                        memcpy(data, oldLumpBuffer, plump->filelen);
                        printf("Copied %d bytes at pos %p (chunkdata is at %p, offset %d)\r\n", plump->filelen, data, chunkdata, data - chunkdata);
                        printf("There are %d clipnodes\r\n", plump->filelen / sizeof(disk_clipnode_t));
                        disk_clipnode_t *dcn = (disk_clipnode_t *) oldLumpBuffer;
                        static int maxPn, minPn, maxCh[2], minCh[2];
                        for (int n = 0 ; n < plump->filelen / sizeof(disk_clipnode_t); n++)
                        {
                            if (dcn->planenum > maxPn)
                                maxPn = dcn->planenum;
                            if (dcn->planenum < minPn)
                                minPn = dcn->planenum;
                            for (int j = 0; j < 2 ; j++)
                            {
                                if (dcn->children[j] > maxCh[j])
                                    maxCh[j] = dcn->children[j];
                                if (dcn->children[j] < minCh[j])
                                    minCh[j] = dcn->children[j];
                            }

                            dcn++;

                        }
                        printf("Value so far: max Pn %d, minPn %d, maxCh0 %d, minCh0 %d,  maxCh1 %d, minCh1 %d\r\n", maxPn, minPn, maxCh[0], minCh[0], maxCh[1], minCh[1]);
                }

                break;
                case LUMP_VISIBILITY:
                    {
                        printf("visibility Lump %i will be copied without modifications\r\n", i);
                        data = chunk_AllocName(plump->filelen , "" );
                        memcpy(data, oldLumpBuffer, plump->filelen);
                        printf("Copied %d bytes at pos %p (chunkdata is at %p, offset %d)\r\n", plump->filelen, data, chunkdata, data - chunkdata);
                    }

                break;
                case LUMP_EDGES:
                    {
                        printf("Edges Lump %i will be copied without modifications\r\n", i);
#if PROFILE_NUM_ELEMENTS
    PROFILE(Edges, plump->filelen / sizeof(int));
#endif // PROFILE_NUM_ELEMENTS
                        data = chunk_AllocName(plump->filelen , "" );
                        memcpy(data, oldLumpBuffer, plump->filelen);
                        printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
                    }
                break;
                case LUMP_TEXINFO:
                        printf("TEX_INFO Lump %i will be copied without modifications\r\n", i);
                        data = chunk_AllocName(plump->filelen , "" );
                        memcpy(data, oldLumpBuffer, plump->filelen);
                        printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);

                break;
            case LUMP_TEXTURES:
                printf("Found textures in lump. Checking for data\r\n");
                Modify_Textures(oldLumpBuffer, plump->filelen, &newLumpSize);

            break;
            case LUMP_FACES:
                modelNumsurfaces = plump->filelen / sizeof(dface_t);
 #if PROFILE_NUM_ELEMENTS
    PROFILE(Faces, modelNumsurfaces);
#endif // PROFILE_NUM_ELEMENTS
                printf("Getting number of surfaces: %d\r\n", modelNumsurfaces);
                data = chunk_AllocName(plump->filelen , "" );
                memcpy(data, oldLumpBuffer, plump->filelen);
                printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);

            break;
            case LUMP_LEAFS:
                // joined to nodes.
                Mod_LoadLeafs(plump, oldLumpBuffer);
                newLumpSize = 0;
            break;
            case LUMP_NODES:
                Mod_LoadNodes (plump, oldLumpBuffer, &newLumpSize);
                data = chunk_AllocName(newLumpSize , "" );
                memcpy(data, mnodeData, newLumpSize);
                printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
                printf("Number of nodes = %d\r\n", plump->filelen / sizeof(mnode_t));
                free(mnodeData);
                break;
            case LUMP_LIGHTING:
                {
                    static int totalLighting = 0;
                    totalLighting +=  plump->filelen;
 #if PROFILE_NUM_ELEMENTS
    PROFILE(Lighting, plump->filelen);
#endif // PROFILE_NUM_ELEMENTS
                    printf("LIGHTING AT LUMP %i will be copied without modifications. Size is: %d, total: %d\r\n", i, plump->filelen, totalLighting);
                    data = chunk_AllocName(plump->filelen , "" );
                    memcpy(data, oldLumpBuffer, plump->filelen);
                    printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
                }
                break;
#if 0
            case LUMP_VERTEXES:
                printf("Lump %i will be copied without modifications\r\n", i);
                data = chunk_AllocName(plump->filelen , "" );
                memcpy(data, oldLumpBuffer, plump->filelen);
                printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
                {
                    int badmodel = 0;
                    float *pf = (float *)data;
                    for (int n = 0; n < plump->filelen / 4; n++)
                    {
                        if ((*pf) != (int)(*pf))
                        {
                            printf("vertex %i is not integer %f in model %s\r\n", n, *pf, modelName);
                            badmodel = 1;
                            break;
                        }
                        pf++;
                    }
                    FIXME(badmodel ? "Model bad :(" : "model is good!");
                }
                break;
#endif
            case LUMP_ENTITIES:
                parseEntityList (oldLumpBuffer);
                printf("Lump %i will be copied without modifications\r\n", i);
                data = chunk_AllocName(plump->filelen , "" );
                memcpy(data, oldLumpBuffer, plump->filelen);
                printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
            break;
            default:
                printf("Lump %i will be copied without modifications\r\n", i);
                data = chunk_AllocName(plump->filelen , "" );
                memcpy(data, oldLumpBuffer, plump->filelen);
                printf("Copied at pos %p (chunkdata is at %p, offset %d)\r\n", data, chunkdata, data - chunkdata);
            break;
        }
        // update new lump
        pnewlump->filelen = newLumpSize;
        // align for next lump.
        chunk_Align4();
    }
    printf("This model had size: %d, now it is %d\r\n", *size, chunk_LowMarkInt());
    *size = chunk_LowMarkInt();
    return newFile;
}
uint8_t * Convert_AliasModel(model_t *mod, void *buffer, uint32_t * size)
{
	int	start, end, total;
    disk_aliashdr_t *pheader;
    // first we load the model
	chunk_Flush();
	start =  chunk_LowMarkInt();
    pheader = Mod_LoadAliasModel2(mod, buffer, NULL);
	end = chunk_LowMarkInt ();
	total = end - start;

	// then we need to load again the model, but this time we have all the triangle data
	int oldTotal = total;
	start = chunk_LowMarkInt();
    pheader = Mod_LoadAliasModel2(mod, buffer, pheader);
	end = chunk_LowMarkInt ();
	total = end - start;

	static int totalSoFar = 0;
	static int totalSoFarSmall = 0;
	if (total < 50000)
	    totalSoFarSmall += total;
	totalSoFar += total;
    printf("The model %s occupies %d Cache. Old was: %d Total so far: %d\r\n", mod->name, total, oldTotal, totalSoFar);
    printf("Not Cached %d. Cached: %d\r\n", totalSoFarSmall, totalSoFar - totalSoFarSmall);
    //
   *size = total;
    return (uint8_t *) pheader;

}
void Mod_LoadAliasModel (model_t *mod, void *buffer)
{
	int	start, end, total;
    disk_aliashdr_t *pheader;
    // first we load the model
	chunk_Flush();
	start = chunk_LowMarkInt();
    pheader = Mod_LoadAliasModel2(mod, buffer, NULL);
	end = chunk_LowMarkInt();
	total = end - start;

	// then we need to load again the model, but this time we have all the triangle data
	int oldTotal = total;
	start = chunk_LowMarkInt();
    pheader = Mod_LoadAliasModel2(mod, buffer, pheader);
	end = chunk_LowMarkInt();
	total = end - start;

	static int totalSoFar = 0;
	static int totalSoFarSmall = 0;
	if (total < 50000)
	    totalSoFarSmall += total;
	totalSoFar += total;
    printf("The model %s occupies %d Cache. Old was: %d Total so far: %d\r\n", mod->name, total, oldTotal, totalSoFar);
    printf("Not Cached %d. Cached: %d\r\n", totalSoFarSmall, totalSoFar - totalSoFarSmall);
    //
}
void printProfileData(void)
{
    #if PROFILE_NUM_ELEMENTS
        printf(">>>Max number of elements: Edges = %d, Entities = (%d, %d, %d), Faces = %d, leaves = %d, Nodes = %d, lighting = %d\r\n<<<",
               maxEdges, maxEntitiesEasy, maxEntitiesMedium, maxEntitiesHard, maxFaces, maxLeaves, maxNodes, maxLighting);
    #else
    // dummy
    #endif // PROFILE_NUM_ELEMENTS
}

//=============================================================================
