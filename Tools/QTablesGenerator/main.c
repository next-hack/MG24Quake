/*
 QTablesGenerator by Nicola Wrachien (next-hack in the comments)
 A tools that prints tables to be used in the MCU Quake game.

 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments).

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
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#define FINE_ANGLES         8192
#define MAX_FLOATS_PER_LINE 8
#define MAX_INT_PER_LINE    32
#define	AMP		            (8*0x10000)
#define	AMP2	            3
#define	CYCLE			    128		// turbulent cycle size
#define MAXDIMENSION        320
#define SIN_BUFFER_SIZE     (MAXDIMENSION+CYCLE)
#define NUMVERTEXNORMALS	162
#define MAX_MODELS          256
void R_InitTurb (void);
char localmodels[MAX_MODELS][5];
int sintable[SIN_BUFFER_SIZE];
char intsintable[SIN_BUFFER_SIZE];

int main()
{
    printf("const float fine_sintable[FINE_ANGLE90] = \r\n{\r\n    ");
    int maxIndex;
    maxIndex = FINE_ANGLES / 4;
    for (int i = 0; i < maxIndex; i++)
    {
        printf("%e, ", sin(i * 2 * M_PI / FINE_ANGLES));
        if (i % MAX_FLOATS_PER_LINE == (MAX_FLOATS_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");
    // turbolent
    R_InitTurb();
    maxIndex = SIN_BUFFER_SIZE;
    printf("const int sintable[SIN_BUFFER_SIZE] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        printf("0x%08x, ", sintable[i]);
        if (i % MAX_INT_PER_LINE == (MAX_INT_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");
    //
    printf("const byte intsintable[SIN_BUFFER_SIZE] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        printf("0x%02x, ", intsintable[i]);
        if (i % MAX_INT_PER_LINE == (MAX_INT_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");
    //
    maxIndex = NUMVERTEXNORMALS;
    printf("const byte b_avelocities[NUMVERTEXNORMALS][3] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        printf("{0x%02x, 0x%02x, 0x%02x}, ", rand() & 0xFF, rand() & 0xFF, rand() & 0xFF);
        if (i % MAX_FLOATS_PER_LINE == (MAX_FLOATS_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");
    for (int i=0 ; i<MAX_MODELS ; i++)
		sprintf (localmodels[i], "*%i", i);

    maxIndex = NUMVERTEXNORMALS;
    printf("const char localmodels[MAX_MODELS][5] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        printf("\"%s\", ", localmodels[i]);
        if (i % MAX_INT_PER_LINE == (MAX_FLOATS_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");
    //
    maxIndex = 256;
    uint8_t keyshift[256];
    for (int i=0 ; i<256 ; i++)
        keyshift[i] = i;
    for (int i='a' ; i<='z' ; i++)
        keyshift[i] = i - 'a' + 'A';
    keyshift['1'] = '!';
    keyshift['2'] = '@';
    keyshift['3'] = '#';
    keyshift['4'] = '$';
    keyshift['5'] = '%';
    keyshift['6'] = '^';
    keyshift['7'] = '&';
    keyshift['8'] = '*';
    keyshift['9'] = '(';
    keyshift['0'] = ')';
    keyshift['-'] = '_';
    keyshift['='] = '+';
    keyshift[','] = '<';
    keyshift['.'] = '>';
    keyshift['/'] = '?';
    keyshift[';'] = ':';
    keyshift['\''] = '"';
    keyshift['['] = '{';
    keyshift[']'] = '}';
    keyshift['`'] = '~';
    keyshift['\\'] = '|';

    printf("const byte keyshift[256] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        printf("0x%02x, ", keyshift[i]);
        if (i % MAX_INT_PER_LINE == (MAX_INT_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");

    //
    maxIndex = 256;
    printf("const int fixedReciprocal256[256] = \r\n{\r\n    ");
    for (int i = 0; i < maxIndex; i++)
    {
        if (i == 0)
        printf("0x7FFF, ");
            else
        printf("0x10000 / 0x%02x, ", i);
        if (i % MAX_FLOATS_PER_LINE == (MAX_FLOATS_PER_LINE - 1) && i != maxIndex - 1)
        {
            printf("\r\n    ");
        }
    }
    printf("\r\n};\r\n");


    return 0;

}
void R_InitTurb (void)
{
	int		i;

	for (i=0 ; i<(SIN_BUFFER_SIZE) ; i++)
	{
	    #if SINTABLE7P25
		sintable[i] = (int)(AMP + sin(i*3.14159*2/CYCLE)*AMP) << 9;    // next-hack: this way we are saving a couple of & CYCLE - 1.
        #else
		sintable[i] = AMP + sin(i*3.14159*2/CYCLE)*AMP;
        #endif
		intsintable[i] = AMP2 + sin(i*3.14159*2/CYCLE)*AMP2 ;	// AMP2, not 20
	}
}
