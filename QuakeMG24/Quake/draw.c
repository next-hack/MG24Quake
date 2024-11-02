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

// draw.c -- this is the only file outside the refresh that touches the
// vid buffer
#include "quakedef.h"
#if !WIN32
#include "memory_defs.h"
#endif
#define SCREEN_HEIGHT           200
typedef struct
{
    vrect_t rect;
    int width;
    int height;
    byte *ptexbytes;
    int rowbytes;
} rectdesc_t;

static rectdesc_t r_rectdesc;

byte *draw_chars;				// 8*8 graphic characters
qpic_t *draw_disc;
qpic_t *draw_backtile;

//=============================================================================
/* Support Routines */

#if !USE_EXT_MEMORY
typedef struct cachepic_s
{
	char		name[MAX_QPATH];
	cache_user_t	cache;
} cachepic_t;

#define	MAX_CACHED_PICS		128

cachepic_t	menu_cachepics[MAX_CACHED_PICS];
int			menu_numcachepics;
#endif

qpic_t* Draw_PicFromWad(char *name)
{
    return W_GetLumpName(name);
}

/*
 ================
 Draw_CachePic
 ================
 */

qpic_t* Draw_CachePic(char *path)
{
#if USE_EXT_MEMORY
    return (qpic_t*) COM_LoadFileFromExtMem(path, NULL);
#else
	cachepic_t	*pic;
	int			i;
	qpic_t		*dat;

	for (pic=menu_cachepics, i=0 ; i<menu_numcachepics ; pic++, i++)
		if (!strcmp (path, pic->name))
			break;

	if (i == menu_numcachepics)
	{
		if (menu_numcachepics == MAX_CACHED_PICS)
			Sys_Error ("menu_numcachepics == MAX_CACHED_PICS");
		menu_numcachepics++;
		strcpy (pic->name, path);
	}
	dat = Cache_Check (&pic->cache);

	if (dat)
		return dat;

//
// load the pic from disk
//
	COM_LoadCacheFile (path, &pic->cache);

	dat = (qpic_t *)pic->cache.data;

	if (!dat)
	{
		Sys_Error ("Draw_CachePic: failed to load %s", path);
	}

	SwapPic (dat);

	return dat;
#endif // USE_EXT_MEMORY

}

/*
 ===============
 Draw_Init
 ===============
 */
void Draw_Init(void)
{
    draw_chars = W_GetLumpName("conchars");
    draw_chars = storeToInternalFlash(draw_chars, 16 * 16 * 8 * 8);
    draw_disc = W_GetLumpName("disc");
    draw_backtile = W_GetLumpName("backtile");
    qpic_t backtile;
    extMemGetDataFromAddress(&backtile, draw_backtile, sizeof(backtile));
    r_rectdesc.width = backtile.width;
    r_rectdesc.height = backtile.height;
    r_rectdesc.ptexbytes = backtile.data;
    r_rectdesc.rowbytes = backtile.width;
}

/*
 ================
 Draw_Character

 Draws one 8*8 graphics character with 0 being transparent.
 It can be clipped to the top of the screen to allow the console to be
 smoothly scrolled off.
 ================
 */
void Draw_Character(int x, int y, int num)
{
    byte *dest;
    byte *source;
    int drawline;
    int row, col;

    num &= 255;

    if (y <= -8 || y >= SCREEN_HEIGHT)
        return;			// totally off screen

#ifdef PARANOID
	if (y > VID_HEIGHT - 8 || x < 0 || x > VID_WIDTH - 8)
		Sys_Error ("Con_DrawCharacter: (%i, %i)", x, y);
	if (num < 0 || num > 255)
		Sys_Error ("Con_DrawCharacter: char %i", num);
#endif

    row = num >> 4;
    col = num & 15;
    source = draw_chars + (row << 10) + (col << 3);

    if (y < 0)
    {	// clipped
        drawline = 8 + y;
        source -= 128 * y;
        y = 0;
    }
    else
    {
        if (y + 8 > SCREEN_HEIGHT)
        {
            drawline = SCREEN_HEIGHT - y;
        }
        else
            drawline = 8;

    }
//
    if (y >= DRAW_BUFFER_HEIGHT)
    {
        dest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        dest = vid.conbuffer + y * VID_ROWBYTES + x;
    }

#if !WIN32
    int dmabusy = displayData.dmaBusy;
    int ffffffff = 0xffffffff;

#endif
    while (drawline--)
    {
#if !WIN32
        if (dmabusy)  // most of the time when we are here the DMA is free.
            waitForDisplayDMA(y);
#endif
#if WIN32
        if (source[0])
            dest[0] = source[0];
        if (source[1])
            dest[1] = source[1];
        if (source[2])
            dest[2] = source[2];
        if (source[3])
            dest[3] = source[3];
        if (source[4])
            dest[4] = source[4];
        if (source[5])
            dest[5] = source[5];
        if (source[6])
            dest[6] = source[6];
        if (source[7])
            dest[7] = source[7];
#else
#if 0
        uint32_t dp, sourcepix, tmp;
       __asm volatile
       (
           "LDR %[destpix], [%[dest]]\n\t"
           "LDR %[sourcepix], [%[source]]\n\t"
           "SADD8 %[tmp], %[sourcepix], %[m1]\n\t"    // this is actually a 4-byte wise add
           "SEL %[tmp], %[sourcepix], %[destpix]\n\t"
           "LDR %[destpix], [%[dest], #4]\n\t"
           "LDR %[sourcepix], [%[source], #4]\n\t"
           "STR %[tmp], [%[dest]]\n\t"
           "SADD8 %[tmp], %[sourcepix], %[m1]\n\t"    // this is actually a 4-byte wise add
           "SEL %[tmp], %[sourcepix], %[destpix]\n\t"
           "STR %[tmp], [%[dest], #4]\n\t"

           : [destpix] "=&r"  (dp), [sourcepix] "=&r"  (sourcepix), [tmp]  "=&r" (tmp)
           :  [source] "r" (source), [dest]  "r" (dest), [m1] "r"  (ffffffff)
           :
       );
#else
        uint32_t destpix, sourcepix, destpix2, sourcepix2, tmp;
        __asm volatile
        (
            "LDR %[destpix], [%[dest]]\n\t"
            "LDR %[sourcepix], [%[source]]\n\t"
            "LDR %[destpix2], [%[dest], #4]\n\t"
            "LDR %[sourcepix2], [%[source], #4]\n\t"
            "SADD8 %[tmp], %[sourcepix], %[m1]\n\t"    // this is actually a 4-byte wise add
            "SEL %[tmp], %[sourcepix], %[destpix]\n\t"
            "STR %[tmp], [%[dest]]\n\t"
            "SADD8 %[tmp], %[sourcepix2], %[m1]\n\t"// this is actually a 4-byte wise add
            "SEL %[tmp], %[sourcepix2], %[destpix2]\n\t"
            "STR %[tmp], [%[dest], #4]\n\t"

            : [destpix] "=&r" (destpix), [sourcepix] "=&r" (sourcepix), [destpix2] "=&r" (destpix2), [sourcepix2] "=&r" (sourcepix2), [tmp] "=&r" (tmp)
            : [source] "r" (source), [dest] "r" (dest), [m1] "r" (ffffffff)
            :
        );
#endif
#endif
        source += 128;
        y++;
        if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
        {
            // move to aux_buffer
            dest = (byte*) aux_buffer + x;

        }
        else
            dest += VID_ROWBYTES;
    }
}

/*
 ================
 Draw_String
 ================
 */
void Draw_String(int x, int y, char *str)
{
    while (*str)
    {
        Draw_Character(x, y, *str);
        str++;
        x += 8;
    }
}

/*
 ================
 Draw_DebugChar

 Draws a single character directly to the upper right corner of the screen.
 This is for debugging lockups by drawing different chars in different parts
 of the code.
 ================
 */
#if 0
void Draw_DebugChar (char num)
{
	byte			*dest;
	byte			*source;
	int				drawline;
	extern byte		*draw_chars;
	int				row, col;

	if (!vid.direct)
		return;		// don't have direct FB access, so no debugchars...

	drawline = 8;

	row = num>>4;
	col = num&15;
	source = draw_chars + (row<<10) + (col<<3);

	dest = vid.direct + 312;

	while (drawline--)
	{
		dest[0] = source[0];
		dest[1] = source[1];
		dest[2] = source[2];
		dest[3] = source[3];
		dest[4] = source[4];
		dest[5] = source[5];
		dest[6] = source[6];
		dest[7] = source[7];
		source += 128;
		dest += 320;
	}
}
#endif
/*
 =============
 Draw_Pic
 =============
 */
extern uint8_t textureCacheBuffer[];

void Draw_Pic(int x, int y, qpic_t *pic)
{
    byte *dest;
    int v;
    qpic_t qpd;
    byte *picSource = pic->data;
    pic = extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));

    if ((x < 0) || (x + pic->width > VID_WIDTH) || (y < 0) || (y + pic->height > VID_HEIGHT))
    {
        Sys_Error("Draw_Pic: bad coordinates");
    }


    if (y >= DRAW_BUFFER_HEIGHT)
    {
        dest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        dest = vid.buffer + y * VID_ROWBYTES + x;
    }
#if !WIN32
    int wasBusy = displayData.dmaBusy;
#endif
    for (v = 0; v < pic->height; v++)
    {
#if !WIN32
        if (wasBusy)
            waitForDisplayDMA(y);
#endif
        picSource += pic->width;
        extMemGetDataFromAddress(dest, picSource, pic->width);
        y++;
        if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
        {
            // move to aux_buffer
            dest = (byte*) aux_buffer + x;
        }
        else
            dest += VID_ROWBYTES;

    }
}

/*
 =============
 Draw_TransPic
 =============
 */
void Draw_TransPic(int x, int y, qpic_t *pic)
{
    byte *dest, *source, tbyte;
    int v, u;
    qpic_t qpd;
    byte *picSource = pic->data;
    pic = extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));

    if (x < 0 || (x + pic->width) > VID_WIDTH || y < 0 || (y + pic->height) > VID_HEIGHT)
    {
        Sys_Error("Draw_TransPic: bad coordinates");
    }

    source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);

//    dest = vid.buffer + y * VID_ROWBYTES + x;
    if (y >= DRAW_BUFFER_HEIGHT)
    {
        dest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        dest = vid.buffer + y * VID_ROWBYTES + x;
    }
#if !WIN32
    int wasBusy = displayData.dmaBusy;
#endif
    if (pic->width & 7)
    {	// general
        for (v = 0; v < pic->height; v++)
        {
#if !WIN32
            if (wasBusy)
                waitForDisplayDMA(y);
#endif

            for (u = 0; u < pic->width; u++)
                if ((tbyte = source[u]) != TRANSPARENT_COLOR)
                    dest[u] = tbyte;

            picSource += pic->width;
            source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);

            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                dest = (byte*) aux_buffer + x;
            }
            else
                dest += VID_ROWBYTES;
        }
    }
    else
    {	// unwound
        for (v = 0; v < pic->height; v++)
        {
#if !WIN32
            if (wasBusy)
                waitForDisplayDMA(y);
#endif
            for (u = 0; u < pic->width; u += 8)
            {
                if ((tbyte = source[u]) != TRANSPARENT_COLOR)
                    dest[u] = tbyte;
                if ((tbyte = source[u + 1]) != TRANSPARENT_COLOR)
                    dest[u + 1] = tbyte;
                if ((tbyte = source[u + 2]) != TRANSPARENT_COLOR)
                    dest[u + 2] = tbyte;
                if ((tbyte = source[u + 3]) != TRANSPARENT_COLOR)
                    dest[u + 3] = tbyte;
                if ((tbyte = source[u + 4]) != TRANSPARENT_COLOR)
                    dest[u + 4] = tbyte;
                if ((tbyte = source[u + 5]) != TRANSPARENT_COLOR)
                    dest[u + 5] = tbyte;
                if ((tbyte = source[u + 6]) != TRANSPARENT_COLOR)
                    dest[u + 6] = tbyte;
                if ((tbyte = source[u + 7]) != TRANSPARENT_COLOR)
                    dest[u + 7] = tbyte;
            }
            picSource += pic->width;
            source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);
            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                dest = (byte*) aux_buffer + x;
            }
            else
                dest += VID_ROWBYTES;

        }
    }
}

/*
 =============
 Draw_TransPicTranslate
 =============
 */
void Draw_TransPicTranslate(int x, int y, qpic_t *pic, byte *translation)
{
    byte *dest, *source, tbyte;
    int v, u;

    if (x < 0 || (x + pic->width) > VID_WIDTH || y < 0 || (y + pic->height) > VID_HEIGHT)
    {
        Sys_Error("Draw_TransPic: bad coordinates");
    }
    byte *picSource = pic->data;
    source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);

    if (y >= DRAW_BUFFER_HEIGHT)
    {
        dest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        dest = vid.buffer + y * VID_ROWBYTES + x;
    }

#if !WIN32
    int wasBusy = displayData.dmaBusy;
#endif
    if (pic->width & 7)
    {	// general
        for (v = 0; v < pic->height; v++)
        {
#if !WIN32
            if (wasBusy)
                waitForDisplayDMA(y);
#endif
            for (u = 0; u < pic->width; u++)
                if ((tbyte = source[u]) != TRANSPARENT_COLOR)
                    dest[u] = translation[tbyte];

            picSource += pic->width;
            source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);
            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                dest = (byte*) aux_buffer + x;
            }
            else
                dest += VID_ROWBYTES;

        }
    }
    else
    {	// unwound
        for (v = 0; v < pic->height; v++)
        {
#if !WIN32
            if (wasBusy)
                waitForDisplayDMA(y);
#endif
            for (u = 0; u < pic->width; u += 8)
            {
                if ((tbyte = source[u]) != TRANSPARENT_COLOR)
                    dest[u] = translation[tbyte];
                if ((tbyte = source[u + 1]) != TRANSPARENT_COLOR)
                    dest[u + 1] = translation[tbyte];
                if ((tbyte = source[u + 2]) != TRANSPARENT_COLOR)
                    dest[u + 2] = translation[tbyte];
                if ((tbyte = source[u + 3]) != TRANSPARENT_COLOR)
                    dest[u + 3] = translation[tbyte];
                if ((tbyte = source[u + 4]) != TRANSPARENT_COLOR)
                    dest[u + 4] = translation[tbyte];
                if ((tbyte = source[u + 5]) != TRANSPARENT_COLOR)
                    dest[u + 5] = translation[tbyte];
                if ((tbyte = source[u + 6]) != TRANSPARENT_COLOR)
                    dest[u + 6] = translation[tbyte];
                if ((tbyte = source[u + 7]) != TRANSPARENT_COLOR)
                    dest[u + 7] = translation[tbyte];
            }
            picSource += pic->width;
            source = extMemGetDataFromAddress(textureCacheBuffer, picSource, pic->width);

            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                dest = (byte*) aux_buffer + x;
            }
            else
                dest += VID_ROWBYTES;

        }
    }
}

void Draw_CharToConback(int num, int x, int y)
{
    int row, col;
    byte *source;
    int drawline;
    byte *dest;
    row = num >> 4;
    col = num & 15;
    source = draw_chars + (row << 10) + (col << 3);

    if (y <= -8)
        return;			// totally off screen

    if (y < 0)
    {	// clipped
        drawline = 8 + y;
        source -= 128 * y;
        y = 0;
    }
    else
        drawline = 8;

    if (y >= DRAW_BUFFER_HEIGHT)
    {
        dest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        dest = vid.conbuffer + y * VID_ROWBYTES + x;
    }

#if 0
	while (drawline--)
	{
		for (x=0 ; x<8 ; x++)
			if (source[x])
				dest[x] = 0x60 + source[x];
		source += 128;
		dest += 320;
	}
	#else
    while (drawline--)
    {
        waitForDisplayDMA(y);
        if (source[0])
            dest[0] = source[0] + 0x60;
        if (source[1])
            dest[1] = source[1] + 0x60;
        if (source[2])
            dest[2] = source[2] + 0x60;
        if (source[3])
            dest[3] = source[3] + 0x60;
        if (source[4])
            dest[4] = source[4] + 0x60;
        if (source[5])
            dest[5] = source[5] + 0x60;
        if (source[6])
            dest[6] = source[6] + 0x60;
        if (source[7])
            dest[7] = source[7] + 0x60;
        source += 128;
        y++;
        if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
        {
            // move to aux_buffer
            dest = (byte*) aux_buffer + x;

        }
        else
            dest += VID_ROWBYTES;
    }
#endif

}

/*
 ================
 Draw_ConsoleBackground

 ================
 */
/*
 ================
 Draw_ConsoleBackground

 ================
 */
void Draw_ConsoleBackground(int lines)
{
    int y, v;
    byte *dest;

    qpic_t *conback;
    char ver[100];

    conback = Draw_CachePic("gfx/conback.lmp");

// draw the pic
    dest = vid.conbuffer;
    byte *picSrc;
    for (y = 0; y < lines; y++)
    {
        waitForDisplayDMA(y);
        v = 200 - lines + y; //)*200/vid.conheight;
        picSrc = (byte*) conback->data + v * 320;
        extMemGetDataFromAddress(dest, picSrc, 320);

        if (y == DRAW_BUFFER_HEIGHT - 1) // if we reached the limit, change to zbuffer
        {
            // move to aux_buffer
            dest = (byte*) aux_buffer;
        }
        else
            dest += VID_ROWBYTES;
    }
    sprintf(ver, "(MG24Quake) %s", XSTR(VERSION));
    int startx = 320 - 11 - 8 * strlen(ver);
    y = lines - (200 - 186);
    for (unsigned int x = 0; x < strlen(ver); x++)
        Draw_CharToConback(ver[x], startx + (x << 3), y);

}

/*
 ==============
 R_DrawRect8
 ==============
 */
void R_DrawRect8(vrect_t *prect, int rowbytes, byte *psrc, int transparent)
{
    byte t;
    int i, j, destdelta;
    byte *pdest;

    int y = prect->y;

    int x = prect->x;

    if (y >= DRAW_BUFFER_HEIGHT)
    {
        pdest = (byte*) aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    }
    else
    {
        pdest = vid.buffer + y * VID_ROWBYTES + x;
    }

    byte *psrcadd = psrc;
    psrc = extMemGetDataFromAddress(textureCacheBuffer, psrcadd, prect->width);

    destdelta = VID_ROWBYTES - prect->width;
#if !WIN32
    int wasBusy = displayData.dmaBusy;
#endif
    if (transparent)
    {
#if !WIN32
        if (wasBusy)
            waitForDisplayDMA(y);
#endif
        for (i = 0; i < prect->height; i++)
        {
            for (j = 0; j < prect->width; j++)
            {
                t = *psrc;
                if (t != TRANSPARENT_COLOR)
                {
                    *pdest = t;
                }

                psrc++;
                pdest++;
            }

            psrcadd += rowbytes;
            psrc = extMemGetDataFromAddress(textureCacheBuffer, psrcadd, prect->width);

            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                pdest = (byte*) aux_buffer + x;
            }
            else
                pdest += destdelta;
        }
    }
    else
    {
        //return;
        for (i = 0; i < prect->height; i++)
        {
#if !WIN32
            if (wasBusy)
                waitForDisplayDMA(y);
#endif
            extMemGetDataFromAddress(pdest, psrcadd, prect->width);
            psrcadd += rowbytes;
            y++;
            if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
            {
                // move to aux_buffer
                pdest = (byte*) aux_buffer + x;
            }
            else
                pdest += VID_ROWBYTES;
        }
    }
}

/*
 =============
 Draw_TileClear

 This repeats a 64*64 tile graphic to fill the screen around a sized down
 refresh window.
 =============
 */
void Draw_TileClear(int x, int y, int w, int h)
{
#if 0  // next-hack: why do we need this crap in the first place, if we update everything from scratch?
	int				width, height, tileoffsetx, tileoffsety;
	byte			*psrc;
	vrect_t			vr;

	r_rectdesc.rect.x = x;
	r_rectdesc.rect.y = y;
	r_rectdesc.rect.width = w;
	r_rectdesc.rect.height = h;

	vr.y = r_rectdesc.rect.y;
	height = r_rectdesc.rect.height;

	tileoffsety = vr.y % r_rectdesc.height;

	while (height > 0)
	{
		vr.x = r_rectdesc.rect.x;
		width = r_rectdesc.rect.width;

		if (tileoffsety != 0)
			vr.height = r_rectdesc.height - tileoffsety;
		else
			vr.height = r_rectdesc.height;

		if (vr.height > height)
			vr.height = height;

		tileoffsetx = vr.x % r_rectdesc.width;

		while (width > 0)
		{
			if (tileoffsetx != 0)
				vr.width = r_rectdesc.width - tileoffsetx;
			else
				vr.width = r_rectdesc.width;

			if (vr.width > width)
				vr.width = width;

			psrc = r_rectdesc.ptexbytes +
					(tileoffsety * r_rectdesc.rowbytes) + tileoffsetx;

				R_DrawRect8 (&vr, r_rectdesc.rowbytes, psrc, 0);

			vr.x += vr.width;
			width -= vr.width;
			tileoffsetx = 0;	// only the left tile can be left-clipped
		}

		vr.y += vr.height;
		height -= vr.height;
		tileoffsety = 0;		// only the top tile can be top-clipped
	}
#else
    // shut up compiler!
    (void) x;
    (void) y;
    (void) w;
    (void) h;

#endif
}

/*
 =============
 Draw_Fill

 Fills a box of pixels with a single color
 =============
 */
void Draw_Fill(int x, int y, int w, int h, int c)
{
    byte *dest;
    int u, v;
    if (y < DRAW_BUFFER_HEIGHT)
        dest = vid.buffer + y * VID_ROWBYTES + x;
    else
        dest = aux_buffer + (y - DRAW_BUFFER_HEIGHT) * VID_ROWBYTES + x;
    for (v = 0; v < h; v++)
    {
        waitForDisplayDMA(y);
        for (u = 0; u < w; u++)
            dest[u] = c;
        y++;
        if (y == DRAW_BUFFER_HEIGHT) // if we reached the limit, change to zbuffer
        {
            // move to aux_buffer
            dest = (byte*) aux_buffer + x;
        }
        else
            dest += VID_ROWBYTES;
    }
}
//=============================================================================

/*
 ================
 Draw_FadeScreen

 ================
 */
void Draw_FadeScreen(void)
{
    int x, y;
    byte *pbuf;

    VID_UnlockBuffer ();
    S_ExtraUpdate();
    VID_LockBuffer ();

    for (y = 0; y < VID_HEIGHT; y++)
    {
        waitForDisplayDMA(y);
        if (y < DRAW_BUFFER_HEIGHT)
            pbuf = (byte*) (vid.buffer + VID_ROWBYTES * y);
        else
            pbuf = (byte*) ((byte*) aux_buffer + VID_ROWBYTES * (y - DRAW_BUFFER_HEIGHT));

        uint32_t *p = (uint32_t*) pbuf;
        if (y & 1)
        {
            for (x = 0; x < VID_WIDTH; x += 16)
            {
                *p = *p & 0x00FF0000;
                p++;
                *p = *p & 0x00FF0000;
                p++;
                *p = *p & 0x00FF0000;
                p++;
                *p = *p & 0x00FF0000;
                p++;
            }

        }
        else
        {
            for (x = 0; x < VID_WIDTH; x += 16)
            {
                *p = *p & 0x000000FF;
                p++;
                *p = *p & 0x000000FF;
                p++;
                *p = *p & 0x000000FF;
                p++;
                *p = *p & 0x000000FF;
                p++;
            }

        }
    }

    VID_UnlockBuffer ();
    S_ExtraUpdate();
    VID_LockBuffer ();
}

//=============================================================================

/*
 ================
 Draw_BeginDisc

 Draws the little blue disc in the corner of the screen.
 Call before beginning any disc IO.
 ================
 */
void Draw_BeginDisc(void)
{

    D_BeginDirectRect(VID_WIDTH - 24, 0, draw_disc->data, 24, 24);
}

/*
 ================
 Draw_EndDisc

 Erases the disc icon.
 Call after completing any disc IO
 ================
 */
void Draw_EndDisc(void)
{

    D_EndDirectRect(VID_WIDTH - 24, 0, 24, 24);
}

