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
// r_sky.c
#include "quakedef.h"
#include "r_local.h"
#include "d_local.h"

int iskyspeed = 8;
int iskyspeed2 = 2;
float skyspeed, skyspeed2;

float skytime;

byte *r_skysource;

#if SKY_IN_RAM
int r_skymade;
int r_skydirect;		// not used?


// TODO: clean up these routines

byte	bottomsky[128*131];
byte	bottommask[128*131];
byte	newsky[128*256];	// newsky and topsky both pack in here, 128 bytes
							//  of newsky on the left of each scan, 128 bytes
							//  of topsky on the right, because the low-level
							//  drawers need 256-byte scan widths

/*
=============
R_InitSky

A sky texture is 256*128, with the right side being a masked overlay
==============
*/
void R_InitSky (texture_t *mt)
{
	int			i, j;
	byte		*src;

	src = (byte *)mt + mt->offsets[0];

	for (i=0 ; i<128 ; i++)
	{
		for (j=0 ; j<128 ; j++)
		{
			newsky[(i*256) + j + 128] = src[i*256 + j + 128];
		}
	}

	for (i=0 ; i<128 ; i++)
	{
		for (j=0 ; j<131 ; j++)
		{
			if (src[i*256 + (j & 0x7F)])
			{
				bottomsky[(i*131) + j] = src[i*256 + (j & 0x7F)];
				bottommask[(i*131) + j] = 0;
			}
			else
			{
				bottomsky[(i*131) + j] = 0;
				bottommask[(i*131) + j] = 0xff;
			}
		}
	}

	r_skysource = newsky;
}


/*
=================
R_MakeSky
=================
*/
void R_MakeSky (void)
{
	int			x, y;
	int			ofs, baseofs;
	int			xshift, yshift;
	unsigned	*pnewsky;
	static int	xlast = -1, ylast = -1;

	xshift = skytime*skyspeed;
	yshift = skytime*skyspeed;
#warning sky needs to be remade each time.
	if ((xshift == xlast) && (yshift == ylast))
		return;

	xlast = xshift;
	ylast = yshift;

	pnewsky = (unsigned *)&newsky[0];

	for (y=0 ; y<SKYSIZE ; y++)
	{
		baseofs = ((y+yshift) & SKYMASK) * 131;

// FIXME: clean this up
#if UNALIGNED_OK

		for (x=0 ; x<SKYSIZE ; x += 4)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

		// PORT: unaligned dword access to bottommask and bottomsky

			*pnewsky = (*(pnewsky + (128 / sizeof (unsigned))) &
						*(unsigned *)&bottommask[ofs]) |
						*(unsigned *)&bottomsky[ofs];
			pnewsky++;
		}

#else

		for (x=0 ; x<SKYSIZE ; x++)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

			*(byte *)pnewsky = (*((byte *)pnewsky + 128) &
						*(byte *)&bottommask[ofs]) |
						*(byte *)&bottomsky[ofs];
			pnewsky = (unsigned *)((byte *)pnewsky + 1);
		}

#endif

		pnewsky += 128 / sizeof (unsigned);
	}

	r_skymade = 1;
}
#else
typedef struct
{
    uint8_t modelName[MAX_QPATH];
    uint8_t skyNum;
} __attribute__((packed)) sky_table_t;
uint8_t *r_skyFlashSource;
void R_InitFlashSky(miptex_t *mt, char *modelName)
{
    (void) mt;
#if USE_EXT_MEMORY
    unsigned int size = 0;
    sky_table_t *pskyTable;
    // load sky table, to understand which file is containing the sky based on model name
    pskyTable = (sky_table_t*) COM_LoadFileFromExtMem("skylist.dat", &size);
    if (!pskyTable || !size)
    {
        while (1)
        {
            FIXME("CAN'T LOAD SKYTABLE");
        }
    }
    int numberOfEntries = size / sizeof(sky_table_t);
    int skytablesize = (numberOfEntries * sizeof(sky_table_t) + 3) & ~3;
    sky_table_t *skyTable = Z_Calloc(skytablesize, 1, PU_STATIC, NULL);
    extMemGetDataFromAddress(skyTable, pskyTable, skytablesize);
    // find the sky number
    int skyNumber = -1;
    for (int i = 0; i < numberOfEntries; i++)
    {
#if DEBUG_SKY
        printf("Checking Model name %s against %s in skytable %i\r\n", modelName, skyTable[i].modelName, i);
#endif
        if (!strcmp(modelName, (char*) skyTable[i].modelName))
        {
#if DEBUG_SKY
            printf("Found sky number: %i\r\n", skyTable[i].skyNum);
#endif
            skyNumber = skyTable[i].skyNum;
            break;
        }
    }
    if (skyNumber != -1)
    {
        char filename[10];
        snprintf(filename, sizeof(filename), "sky%02x", skyNumber);
        r_skyFlashSource = COM_LoadFileFromExtMem(filename, &size);
#if DEBUG_SKY
        if (size != 128 * 128 * 128 + 1) // +1 is because we add a null terminator
        {
            printf("Error, sky anim size is %d\r\n", size);
            FIXME("");
        }
#endif
        r_skysource = r_skyFlashSource;
    }
#else
        #error flash sky works only with external memory!
    #endif
    Z_Free(skyTable);
}
void R_MakeSky(void)
{
    int xshift;
    xshift = skytime * skyspeed;
    r_skysource = &r_skyFlashSource[128 * 128 * (xshift % 128)];
    /*  for (int i = 0 ; i < 128; i++)
     {
     if (!(i % 16))
     printf("\r\n");
     printf("%02x",r_skysource[i]);
     }*/
}

#endif

#if DO_WE_REALLY_NEED_THIS
/*
=================
R_GenSkyTile
=================
*/
void R_GenSkyTile (void *pdest)
{
	int			x, y;
	int			ofs, baseofs;
	int			xshift, yshift;
	unsigned	*pnewsky;
	unsigned	*pd;

	xshift = skytime*skyspeed;
	yshift = skytime*skyspeed;

	pnewsky = (unsigned *)&newsky[0];
	pd = (unsigned *)pdest;

	for (y=0 ; y<SKYSIZE ; y++)
	{
		baseofs = ((y+yshift) & SKYMASK) * 131;

// FIXME: clean this up
#if UNALIGNED_OK

		for (x=0 ; x<SKYSIZE ; x += 4)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

		// PORT: unaligned dword access to bottommask and bottomsky

			*pd = (*(pnewsky + (128 / sizeof (unsigned))) &
				   *(unsigned *)&bottommask[ofs]) |
				   *(unsigned *)&bottomsky[ofs];
			pnewsky++;
			pd++;
		}

#else

		for (x=0 ; x<SKYSIZE ; x++)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

			*(byte *)pd = (*((byte *)pnewsky + 128) &
						*(byte *)&bottommask[ofs]) |
						*(byte *)&bottomsky[ofs];
			pnewsky = (unsigned *)((byte *)pnewsky + 1);
			pd = (unsigned *)((byte *)pd + 1);
		}

#endif

		pnewsky += 128 / sizeof (unsigned);
	}
}


/*
=================
R_GenSkyTile16
=================
*/
void R_GenSkyTile16 (void *pdest)
{
	int				x, y;
	int				ofs, baseofs;
	int				xshift, yshift;
	byte			*pnewsky;
	unsigned short	*pd;

	xshift = skytime * skyspeed;
	yshift = skytime * skyspeed;

	pnewsky = (byte *)&newsky[0];
	pd = (unsigned short *)pdest;

	for (y=0 ; y<SKYSIZE ; y++)
	{
		baseofs = ((y+yshift) & SKYMASK) * 131;

// FIXME: clean this up
// FIXME: do faster unaligned version?
		for (x=0 ; x<SKYSIZE ; x++)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

			*pd = d_8to16table[(*(pnewsky + 128) &
					*(byte *)&bottommask[ofs]) |
					*(byte *)&bottomsky[ofs]];
			pnewsky++;
			pd++;
		}

		pnewsky += TILE_SIZE;
	}
}

#endif
/*
 =============
 R_SetSkyFrame
 ==============
 */
void R_SetSkyFrame(void)
{
    int g, s1, s2;
    float temp;

    skyspeed = iskyspeed;
    skyspeed2 = iskyspeed2;

    g = GreatestCommonDivisor(iskyspeed, iskyspeed2);
    s1 = iskyspeed / g;
    s2 = iskyspeed2 / g;
    temp = SKYSIZE * s1 * s2;

    skytime = _g->cl.time - ((int) (_g->cl.time / temp) * temp);

#if SKY_IN_RAM
	r_skymade = 0;
#endif
}

