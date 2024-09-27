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
#include "quakedef.h"

sky_collection_t skies = {.numskies = 0, .skydata = NULL};

// TODO: clean up these routines
#define SKYSIZE 128
#define SKYMASK (SKYSIZE - 1)
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
void R_InitSky (byte		*src)
{
	int			i, j;


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
}


/*
=================
R_MakeSky
=================
*/
void R_MakeSky (int offset)
{
	int			x, y;
	int			ofs, baseofs;
	int			xshift, yshift;
	unsigned	*pnewsky;

	xshift = offset;
	yshift = offset;


	pnewsky = (unsigned *)&newsky[0];

	for (y=0 ; y<SKYSIZE ; y++)
	{
		baseofs = ((y+yshift) & SKYMASK) * 131;

// FIXME: clean this up

		for (x=0 ; x<SKYSIZE ; x++)
		{
			ofs = baseofs + ((x+xshift) & SKYMASK);

			*(byte *)pnewsky = (*((byte *)pnewsky + 128) &
						*(byte *)&bottommask[ofs]) |
						*(byte *)&bottomsky[ofs];
			pnewsky = (unsigned *)((byte *)pnewsky + 1);
		}
		pnewsky += 128 / sizeof (unsigned);
	}
}


void addSky(uint8_t * skybuffer, char *modelName)
{
    skies.numskies++;
    skies.skydata = realloc (skies.skydata, skies.numskies * sizeof(sky_data_t));
    strncpy((char*)skies.skydata[skies.numskies - 1].modelName, modelName, MAX_QPATH);
    memcpy(skies.skydata[skies.numskies - 1].skytexture, skybuffer, sizeof(skies.skydata[skies.numskies - 1].skytexture));
}
void renderSky(uint8_t *skyTexData, uint8_t *renderedSky)
{
    R_InitSky(skyTexData);
    for (int i = 0 ; i < 128; i++)
    {
        R_MakeSky(i);
        for (int y = 0; y < 128; y++)
        {
            memcpy(&renderedSky[y * 128 + i * 128 * 128], &newsky[y * 256], 128);
        }
    }
    // create mask, top and bottom
    // render sky.
}
uint8_t *createSkies(int *differentSkies, int *numberOfSkies, sky_table_t **skyList)
{
    int skip;
    *differentSkies = 0;
    uint8_t *renderedSkies = calloc(skies.numskies , 128 * 128 * 128);
    *skyList = calloc(skies.numskies, sizeof(sky_table_t));
    *numberOfSkies = skies.numskies;
    // scan through the lists
    for (int i = 0; i < skies.numskies; i++)
    {
        int j;
        skip = 0;
        // check if we have duplicate sky
        for (j = 0; j < i; j++)
        {
            if (!memcmp(skies.skydata[i].skytexture, skies.skydata[j].skytexture, sizeof(skies.skydata[i].skytexture)))
            {
                printf("Skipping sky %d, equal to sky %d\r\n", i, j);
                skip = 1;
                break;
            }
        }
        // in j we have the new unique sky number.
        (*skyList)[i].skyNum = j;
        snprintf((char*)((*skyList)[i].modelName), sizeof((*skyList)[i].modelName), "%s", skies.skydata[i].modelName);
        if (!skip)
        {
            printf("Saving sky %d. different Skies %d, renderedSkies ptr %p\r\n", i, *differentSkies, renderedSkies);
            renderSky(skies.skydata[i].skytexture,
                      &renderedSkies[*differentSkies * 128 * 128 * 128]);
            *differentSkies = *differentSkies + 1;
        }
    }
    return renderedSkies;
}
