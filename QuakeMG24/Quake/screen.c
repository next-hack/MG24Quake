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
// screen.c -- master for refresh, status bar, console, chat, notify, etc
#include "quakedef.h"
#include "r_local.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
// only the refresh window will be updated unless these variables are flagged
int scr_copytop;
int scr_copyeverything;

float scr_con_current;
float scr_conlines;		// lines of console to display

float oldscreensize, oldfov;
#if USE_ORIGINAL_CVAR
cvar_t		scr_viewsize = {"viewsize","100", true};
cvar_t		scr_fov = {"fov","90"};	// 10 - 170
cvar_t		scr_conspeed = {"scr_conspeed","300"};
cvar_t		scr_centertime = {"scr_centertime","2"};
cvar_t		scr_showram = {"showram","1"};
cvar_t		scr_showturtle = {"showturtle","0"};
cvar_t		scr_showpause = {"showpause","1"};
cvar_t		scr_printspeed = {"scr_printspeed","8"};
#endif
qboolean scr_initialized;		// ready to draw
#if DRAW_ICONS
qpic_t		*scr_ram;
qpic_t		*scr_net;
qpic_t		*scr_turtle;
#endif

int scr_fullupdate;

int clearconsole;
int clearnotify;

viddef_t vid;				// global video state

vrect_t *pconupdate;
vrect_t scr_vrect;

qboolean scr_disabled_for_loading;
qboolean scr_drawloading;
float scr_disabled_time;
qboolean scr_skipupdate;

qboolean block_drawing;

void SCR_ScreenShot_f(void);

/*
 ===============================================================================

 CENTER PRINTING

 ===============================================================================
 */

AUX_SECTION char scr_centerstring[428];      // Originally was 1024.
float scr_centertime_start;	// for slow victory printing
float scr_centertime_off;
int scr_center_lines;
int scr_erase_lines;
int scr_erase_center;

/*
 ==============
 SCR_CenterPrint

 Called for important messages that should stay in the center of the screen
 for a few moments
 ==============
 */
void SCR_CenterPrint(char *str)
{
    strncpy(scr_centerstring, str, sizeof(scr_centerstring) - 1);
    scr_centertime_off = scr_centertime;
    scr_centertime_start = _g->cl.time;

// count the number of lines for centering
    scr_center_lines = 1;
    while (*str)
    {
        if (*str == '\n')
            scr_center_lines++;
        str++;
    }
}

void SCR_EraseCenterString(void)
{
    int y;

    if (scr_erase_center++ > VID_NUMPAGES)
    {
        scr_erase_lines = 0;
        return;
    }

    if (scr_center_lines <= 4)
        y = VID_HEIGHT * 0.35f;
    else
        y = 48;

    scr_copytop = 1;
    Draw_TileClear(0, y, VID_WIDTH, 8 * scr_erase_lines);
}

void SCR_DrawCenterString(void)
{
    char *start;
    int l;
    int j;
    int x, y;
    int remaining;

// the finale prints the characters one at a time
    if (_g->cl.intermission)
        remaining = scr_printspeed * (_g->cl.time - scr_centertime_start);
    else
        remaining = 9999;

    scr_erase_center = 0;
    start = scr_centerstring;

    if (scr_center_lines <= 4)
        y = VID_HEIGHT * 0.35f;
    else
        y = 48;

    do
    {
        // scan the width of the line
        for (l = 0; l < 40; l++)
            if (start[l] == '\n' || !start[l])
                break;
        x = (VID_WIDTH - l * 8) / 2;
        for (j = 0; j < l; j++, x += 8)
        {
            Draw_Character(x, y, start[j]);
            if (!remaining--)
                return;
        }

        y += 8;

        while (*start && *start != '\n')
            start++;

        if (!*start)
            break;
        start++;		// skip the \n
    }
    while (1);
}

void SCR_CheckDrawCenterString(void)
{
    scr_copytop = 1;
    if (scr_center_lines > scr_erase_lines)
        scr_erase_lines = scr_center_lines;

    scr_centertime_off -= host_frametime;

    if (scr_centertime_off <= 0 && !_g->cl.intermission)
        return;
    if (key_dest != key_game)
        return;

    SCR_DrawCenterString();
}

//=============================================================================

/*
 ====================
 CalcFov
 ====================
 */
float CalcFov(float fov_x, float width, float height)
{
    float a;
    float x;

    if (fov_x < 1 || fov_x > 179)
        Sys_Error("Bad fov: %f", fov_x);

    x = width / tan_t(fov_x / 360 * M_PI);

    a = atanf(height / x);

    a = a * 360 / M_PI;

    return a;
}

/*
 =================
 SCR_CalcRefdef

 Must be called whenever vid changes
 Internal use only
 =================
 */
static void SCR_CalcRefdef(void)
{
    vrect_t vrect;

    scr_fullupdate = 0;		// force a background redraw
    vid.recalc_refdef = 0;

// force the status bar to redraw
    Sbar_Changed();

//========================================

// bound viewsize
    /*
     if (viewsize < 30)
     Cvar_Set ("viewsize","30");
     if (viewsize > 120)
     Cvar_Set ("viewsize","120");*/

    if (viewsize != 100)
    {
        printf("Setting size\r\n");
        Cvar_Set("viewsize", "100");

    }

// bound field of view
    if (fov < 10)
        Cvar_Set("fov", "10");
    if (fov > 170)
        Cvar_Set("fov", "170");

    _g->r_refdef.fov_x = fov;
    _g->r_refdef.fov_y = CalcFov(_g->r_refdef.fov_x, _g->r_refdef.vrect.width, _g->r_refdef.vrect.height);

// intermission is always full screen
#if FULL_SCREEN_INTERMISSION
	if (_g->cl.intermission)
		size = 120;
	else
#endif
#if FULL_SCREEN_INTERMISSION

	if (size >= 120)
		sb_lines = 0;		// no status bar at all
	else if (size >= 110)
		sb_lines = 24;		// no inventory
	else
#endif
    sb_lines = 24 + 16 + 8;

// these calculations mirror those in R_Init() for _g->r_refdef, but take no
// account of water warping
    vrect.x = 0;
    vrect.y = 0;
    vrect.width = VID_WIDTH;
    vrect.height = VID_HEIGHT;

    R_SetVrect(&vrect, &scr_vrect, sb_lines);

// guard against going from one mode to another that's less than half the
// vertical resolution
    if (scr_con_current > VID_HEIGHT)
        scr_con_current = VID_HEIGHT;

// notify the refresh of the change
    R_ViewChanged(&vrect, sb_lines, vid.aspect);
}

/*
 =================
 SCR_SizeUp_f

 Keybinding command
 =================
 */
#if 0
void SCR_SizeUp_f(void)
{
    Cvar_SetValue("viewsize", viewsize + 10);
    vid.recalc_refdef = 1;
}

/*
 =================
 SCR_SizeDown_f

 Keybinding command
 =================
 */
void SCR_SizeDown_f(void)
{
    Cvar_SetValue("viewsize", viewsize - 10);
    vid.recalc_refdef = 1;
}
#endif
//============================================================================

/*
 ==================
 SCR_Init
 ==================
 */
void SCR_Init(void)
{
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&scr_fov);
	Cvar_RegisterVariable (&scr_viewsize);
	Cvar_RegisterVariable (&scr_conspeed);
	Cvar_RegisterVariable (&scr_showram);
	Cvar_RegisterVariable (&scr_showturtle);
	Cvar_RegisterVariable (&scr_showpause);
	Cvar_RegisterVariable (&scr_centertime);
	Cvar_RegisterVariable (&scr_printspeed);
#endif
//
// register our commands
//
#if DRAW_ICONS
	scr_ram = Draw_PicFromWad ("ram");
	scr_net = Draw_PicFromWad ("net");
	scr_turtle = Draw_PicFromWad ("turtle");
#endif
    scr_initialized = true;
}

/*
 ==============
 SCR_DrawRam
 ==============
 */
#if 0
void SCR_DrawRam (void)
{
	if (!showram)
		return;
#if SURF_CACHE
	if (!r_cache_thrash)
		return;
#endif
	Draw_Pic (scr_vrect.x+32, scr_vrect.y, scr_ram);
}
#else
#define SCR_DrawRam()
#endif
/*
 ==============
 SCR_DrawTurtle
 ==============
 */
#if 0
void SCR_DrawTurtle (void)
{
	static int	count;

	if (!showturtle)
		return;

	if (host_frametime < 0.1)
	{
		count = 0;
		return;
	}

	count++;
	if (count < 3)
		return;

	Draw_Pic (scr_vrect.x, scr_vrect.y, scr_turtle);
}
#else
#define SCR_DrawTurtle()
#endif

/*
 ==============
 SCR_DrawNet
 ==============
 */
#if 0
void SCR_DrawNet (void)
{
	if (realtime - _g->cl.last_received_message < 0.3)
		return;
	if (_g->cls.demoplayback)
		return;

	Draw_Pic (scr_vrect.x+64, scr_vrect.y, scr_net);
}
#else
#define SCR_DrawNet()
#endif
/*
 ==============
 DrawPause
 ==============
 */
void SCR_DrawPause(void)
{
    qpic_t *pic;

    if (!showpause)		// turn off for screenshots
        return;

    if (!_g->cl.paused)
        return;

    pic = Draw_CachePic("gfx/pause.lmp");
    qpic_t qpd;
    extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));
    Draw_Pic((VID_WIDTH - qpd.width) / 2, (VID_HEIGHT - 48 - qpd.height) / 2, pic);
}

/*
 ==============
 SCR_DrawLoading
 ==============
 */
void SCR_DrawLoading(void)
{
    qpic_t *pic;

    if (!scr_drawloading)
        return;

    pic = Draw_CachePic("gfx/loading.lmp");
    qpic_t qpd;
    extMemGetDataFromAddress(&qpd, pic, sizeof(qpd));
    Draw_Pic((VID_WIDTH - qpd.width) / 2, (VID_HEIGHT - 48 - qpd.height) / 2, pic);
}

//=============================================================================

/*
 ==================
 SCR_SetUpToDrawConsole
 ==================
 */
void SCR_SetUpToDrawConsole(void)
{
    Con_CheckResize();

    if (scr_drawloading)
        return;		// never a console with loading plaque

// decide on the height of the console
    con_forcedup = !_g->cl.worldmodel || _g->cls.signon != SIGNONS;

    if (con_forcedup)
    {
        scr_conlines = VID_HEIGHT;		// full screen
        scr_con_current = scr_conlines;
    }
    else if (key_dest == key_console)
        scr_conlines = VID_HEIGHT / 2;	// half screen
    else
        scr_conlines = 0;				// none visible

    if (scr_conlines < scr_con_current)
    {
        scr_con_current -= scr_conspeed * host_frametime;
        if (scr_conlines > scr_con_current)
            scr_con_current = scr_conlines;

    }
    else if (scr_conlines > scr_con_current)
    {
        scr_con_current += scr_conspeed * host_frametime;
        if (scr_conlines < scr_con_current)
            scr_con_current = scr_conlines;
    }

    if (clearconsole++ < VID_NUMPAGES)
    {
        scr_copytop = 1;
        Draw_TileClear(0, (int) scr_con_current, VID_WIDTH, VID_HEIGHT - (int) scr_con_current);
        Sbar_Changed();
    }
    else if (clearnotify++ < VID_NUMPAGES)
    {
        scr_copytop = 1;
        Draw_TileClear(0, 0, VID_WIDTH, con_notifylines);
    }
    else
        con_notifylines = 0;
}

/*
 ==================
 SCR_DrawConsole
 ==================
 */
void SCR_DrawConsole(void)
{
    if (scr_con_current)
    {
        scr_copyeverything = 1;
        Con_DrawConsole(scr_con_current, true);
        clearconsole = 0;
    }
    else
    {
        if (key_dest == key_game || key_dest == key_message)
            Con_DrawNotify();	// only draw notify in game
    }
}

/*
 ==============================================================================

 SCREEN SHOTS

 ==============================================================================
 */

typedef struct
{
    char manufacturer;
    char version;
    char encoding;
    char bits_per_pixel;
    unsigned short xmin, ymin, xmax, ymax;
    unsigned short hres, vres;
    unsigned char palette[48];
    char reserved;
    char color_planes;
    unsigned short bytes_per_line;
    unsigned short palette_type;
    char filler[58];
    unsigned char data;			// unbounded
} pcx_t;

/*
 ==============
 WritePCXfile
 ==============
 */
#if 0

void WritePCXfile (char *filename, byte *data, int width, int height,
	int rowbytes, byte *palette)
{
	int		i, j, length;
	pcx_t	*pcx;
	byte		*pack;

	pcx = Hunk_TempAlloc (width*height*2+1000);
	if (pcx == NULL)
	{
		Con_Printf("SCR_ScreenShot_f: not enough memory\n");
		return;
	}

	pcx->manufacturer = 0x0a;	// PCX id
	pcx->version = 5;			// 256 color
 	pcx->encoding = 1;		// uncompressed
	pcx->bits_per_pixel = 8;		// 256 color
	pcx->xmin = 0;
	pcx->ymin = 0;
	pcx->xmax = LittleShort((short)(width-1));
	pcx->ymax = LittleShort((short)(height-1));
	pcx->hres = LittleShort((short)width);
	pcx->vres = LittleShort((short)height);
	Q_memset (pcx->palette,0,sizeof(pcx->palette));
	pcx->color_planes = 1;		// chunky image
	pcx->bytes_per_line = LittleShort((short)width);
	pcx->palette_type = LittleShort(2);		// not a grey scale
	Q_memset (pcx->filler,0,sizeof(pcx->filler));

// pack the image
	pack = &pcx->data;

	for (i=0 ; i<height ; i++)
	{
		for (j=0 ; j<width ; j++)
		{
			if ( (*data & 0xc0) != 0xc0)
				*pack++ = *data++;
			else
			{
				*pack++ = 0xc1;
				*pack++ = *data++;
			}
		}

		data += rowbytes - width;
	}

// write the palette
	*pack++ = 0x0c;	// palette ID byte
	for (i=0 ; i<768 ; i++)
		*pack++ = *palette++;

// write output file
	length = pack - (byte *)pcx;
	COM_WriteFile (filename, pcx, length);
}
#endif

/*
 ==================
 SCR_ScreenShot_f
 ==================
 */
void SCR_ScreenShot_f(void)
{
#if !USE_EXT_MEMORY
	int     i;
	char		pcxname[80];
	char		checkname[MAX_OSPATH];

//
// find a file name to save it to
//
	strcpy(pcxname,"quake00.pcx");

	for (i=0 ; i<=99 ; i++)
	{
		pcxname[5] = i/10 + '0';
		pcxname[6] = i%10 + '0';
		sprintf (checkname, "%s/%s", com_gamedir, pcxname);
		if (Sys_FileTime(checkname) == -1)
			break;	// file doesn't exist
	}
	if (i==100)
	{
		Con_Printf ("SCR_ScreenShot_f: Couldn't create a PCX file\n");
		return;
 	}

//
// save the pcx file
//
	D_EnableBackBufferAccess ();	// enable direct drawing of console to back
									//  buffer

	WritePCXfile (pcxname, vid.buffer, VID_WIDTH, VID_HEIGHT, VID_ROWBYTES,
				  host_basepal);

	D_DisableBackBufferAccess ();	// for adapters that can't stay mapped in
									//  for linear writes all the time

	Con_Printf ("Wrote %s\n", pcxname);
	#endif
}

//=============================================================================

/*
 ===============
 SCR_BeginLoadingPlaque

 ================
 */
void SCR_BeginLoadingPlaque(void)
{
    S_StopAllSounds(true);

    if (_g->cls.state != ca_connected)
        return;
    if (_g->cls.signon != SIGNONS)
        return;

// redraw with no console and the loading plaque
    Con_ClearNotify();
    scr_centertime_off = 0;
    scr_con_current = 0;

    scr_drawloading = true;
    scr_fullupdate = 0;
#if SBAR_CHANGED_ON_LOADING_PLAQUE
	Sbar_Changed ();
#endif
#define UPDATE_SCREEN_ON_BEGIN_LOADING_PLAQUE 1
#if UPDATE_SCREEN_ON_BEGIN_LOADING_PLAQUE
    SCR_UpdateScreen();
#endif
    scr_drawloading = false;

    scr_disabled_for_loading = true;
    scr_disabled_time = realtime;
    scr_fullupdate = 0;
}

/*
 ===============
 SCR_EndLoadingPlaque

 ================
 */
void SCR_EndLoadingPlaque(void)
{
    scr_disabled_for_loading = false;
    scr_fullupdate = 0;
    Con_ClearNotify();
}

//=============================================================================

char *scr_notifystring;
qboolean scr_drawdialog;

void SCR_DrawNotifyString(void)
{
    char *start;
    int l;
    int j;
    int x, y;

    start = scr_notifystring;

    y = VID_HEIGHT * 0.35f;

    do
    {
        // scan the width of the line
        for (l = 0; l < 40; l++)
            if (start[l] == '\n' || !start[l])
                break;
        x = (VID_WIDTH - l * 8) / 2;
        for (j = 0; j < l; j++, x += 8)
            Draw_Character(x, y, start[j]);

        y += 8;

        while (*start && *start != '\n')
            start++;

        if (!*start)
            break;
        start++;		// skip the \n
    }
    while (1);
}

/*
 ==================
 SCR_ModalMessage

 Displays a text string in the center of the screen and waits for a Y or N
 keypress.
 ==================
 */
int SCR_ModalMessage(char *text)
{
    if (_g->cls.state == ca_dedicated)
        return true;

    scr_notifystring = text;

// draw a fresh screen
    scr_fullupdate = 0;
    scr_drawdialog = true;
    SCR_UpdateScreen();
    scr_drawdialog = false;

    S_ClearBuffer();		// so dma doesn't loop current sound

    do
    {
        key_count = -1;		// wait for a key down and up
        Sys_SendKeyEvents();
    }
    while (key_lastpress != 'y' && key_lastpress != 'n' && key_lastpress != K_ESCAPE && key_lastpress != '/');
#if !WIN32
    if (key_lastpress == '/')
    {
        key_lastpress = 'y';
    }
#endif
    scr_fullupdate = 0;
//	SCR_UpdateScreen (); // next-hack removed, it will eat a lot of stack from here.

    return key_lastpress == 'y';
}

//=============================================================================

/*
 ===============
 SCR_BringDownConsole

 Brings the console down and fades the palettes back to normal
 ================
 */
void SCR_BringDownConsole(void)
{
    int i;

    scr_centertime_off = 0;

    for (i = 0; i < 20 && scr_conlines != scr_con_current; i++)
        SCR_UpdateScreen();

    _g->cl.cshifts[0].percent = 0;		// no area contents palette on next frame
    VID_SetPalette(host_basepal);
}

/*
 ==================
 SCR_UpdateScreen

 This is called every frame, and can also be called explicitly to flush
 text to the screen.

 WARNING: be very careful calling this from elsewhere, because the refresh
 needs almost the entire 256k of stack space!
 ==================
 */
#if PROFILE_EXT_MEM_LOADS
    int bytesLoadedFromExtMem = 0;
int extMemAccesses = 0;
#endif
temp_entity_t clientViewEntity;
#if WIN32
extern int screenUpdated;
#endif // WIN32
void SCR_UpdateScreen(void)
{
#if WIN32
    screenUpdated = 1;
    #endif // WIN32
    static float oldscr_viewsize;
#if LCD_X
    static float oldlcd_x;
#endif
    vrect_t vrect;

    if (scr_skipupdate || block_drawing)
        return;
    _g->cl.viewent.data = &clientViewEntity;
    _g->cl.viewent.entityType = TYPE_TEMP_ENTITY;
    scr_copytop = 0;
    scr_copyeverything = 0;

    if (scr_disabled_for_loading)
    {
        /*if (realtime - scr_disabled_time > 60)
         {
         scr_disabled_for_loading = false;
         Con_Printf ("load failed.\n");
         }
         else*/
        return;
    }

    if (_g->cls.state == ca_dedicated)
        return;				// stdout only

    if (!scr_initialized || !con_initialized)
        return;				// not initialized yet

    if (viewsize != oldscr_viewsize)
    {
        oldscr_viewsize = viewsize;
        vid.recalc_refdef = 1;
    }

//
// check for vid changes
//
    if (oldfov != fov)
    {
        oldfov = fov;
        vid.recalc_refdef = true;
    }
#if LCD_X
    if (oldlcd_x != lcd_x)
    {
        oldlcd_x = lcd_x;
        vid.recalc_refdef = true;
    }
#endif

    if (oldscreensize != viewsize)
    {
        oldscreensize = viewsize;
        vid.recalc_refdef = true;
    }

    if (vid.recalc_refdef)
    {
        // something changed, so reorder the screen
        SCR_CalcRefdef();
    }

//
// do 3D refresh drawing, and then update the screen
//
    D_EnableBackBufferAccess();	// of all overlay stuff if drawing directly

    if (scr_fullupdate++ < VID_NUMPAGES)
    {	// clear the entire screen
        scr_copyeverything = 1;
        Draw_TileClear(0, 0, VID_WIDTH, VID_HEIGHT);
        Sbar_Changed();
    }

    pconupdate = NULL;

    SCR_SetUpToDrawConsole();
    SCR_EraseCenterString();

    D_DisableBackBufferAccess();	// for adapters that can't stay mapped in
                                    //  for linear writes all the time

//	VID_LockBuffer ();
    if (!scr_drawloading && !scr_drawdialog)  // next-hack: added those, because otherwise it might create issues
        V_RenderView();

//	VID_UnlockBuffer ();

    D_EnableBackBufferAccess();	// of all overlay stuff if drawing directly

    if (scr_drawdialog)
    {
        Sbar_Draw();
        Draw_FadeScreen();
        SCR_DrawNotifyString();
        scr_copyeverything = true;
    }
    else if (scr_drawloading)
    {
        SCR_DrawLoading();
        Sbar_Draw(); // next-hack should be this drawn?
    }
    else if (_g->cl.intermission == 1 && key_dest == key_game)
    {
        Sbar_IntermissionOverlay();
    }
    else if (_g->cl.intermission == 2 && key_dest == key_game)
    {
        Sbar_FinaleOverlay();
        SCR_CheckDrawCenterString();
    }
    else if (_g->cl.intermission == 3 && key_dest == key_game)
    {
        SCR_CheckDrawCenterString();
    }
    else
    {
        SCR_DrawRam (); SCR_DrawNet (); SCR_DrawTurtle ();
        SCR_DrawPause();
        SCR_CheckDrawCenterString();
        Sbar_Draw();
        SCR_DrawConsole();
        M_Draw();
    }

    D_DisableBackBufferAccess();	// for adapters that can't stay mapped in
                                    //  for linear writes all the time
    if (pconupdate)
    {
        D_UpdateRects(pconupdate);
    }
    V_UpdatePalette();

//
// update one of three areas
//

    if (scr_copyeverything)
    {
        vrect.x = 0;
        vrect.y = 0;
        vrect.width = VID_WIDTH;
        vrect.height = VID_HEIGHT;
//        vrect.pnext = 0;

        VID_Update(&vrect);
    }
    else //if (scr_copytop)
    {
        vrect.x = 0;
        vrect.y = 0;
        vrect.width = VID_WIDTH;
        vrect.height = VID_HEIGHT - sb_lines;
//        vrect.pnext = 0;

        VID_Update(&vrect);
    }
    /*
     else
     {
     vrect.x = scr_vrect.x;
     vrect.y = scr_vrect.y;
     vrect.width = scr_vrect.width;
     vrect.height = scr_vrect.height;
     vrect.pnext = 0;

     VID_Update (&vrect);
     }*/
//	printf("ta %d, fta %d\r\n", timeAsked, floatTimeAsked);
//	timeAsked = floatTimeAsked = 0;
}

//
void SCR_UpdateConsoleOnly(void)
{
    static float oldscr_viewsize;
#if LCD_X
    static float oldlcd_x;
#endif
    vrect_t vrect;

    if (scr_skipupdate || block_drawing)
        return;
    _g->cl.viewent.data = &clientViewEntity;
    _g->cl.viewent.entityType = TYPE_TEMP_ENTITY;
    scr_copytop = 0;
    scr_copyeverything = 0;

    if (scr_disabled_for_loading)
    {
        if (realtime - scr_disabled_time > 60)
        {
            scr_disabled_for_loading = false;
            Con_Printf("load failed.\n");
        }
        else
            return;
    }

    if (_g->cls.state == ca_dedicated)
        return;				// stdout only

    if (!scr_initialized || !con_initialized)
        return;				// not initialized yet

    if (viewsize != oldscr_viewsize)
    {
        oldscr_viewsize = viewsize;
        vid.recalc_refdef = 1;
    }

//
// check for vid changes
//
    if (oldfov != fov)
    {
        oldfov = fov;
        vid.recalc_refdef = true;
    }
#if LCD_X
    if (oldlcd_x != lcd_x)
    {
        oldlcd_x = lcd_x;
        vid.recalc_refdef = true;
    }
#endif
    if (oldscreensize != viewsize)
    {
        oldscreensize = viewsize;
        vid.recalc_refdef = true;
    }

    if (vid.recalc_refdef)
    {
        // something changed, so reorder the screen
        SCR_CalcRefdef();
    }

//
// do 3D refresh drawing, and then update the screen
//
    D_EnableBackBufferAccess();	// of all overlay stuff if drawing directly

    if (scr_fullupdate++ < VID_NUMPAGES)
    {	// clear the entire screen
        scr_copyeverything = 1;
        Draw_TileClear(0, 0, VID_WIDTH, VID_HEIGHT);
        Sbar_Changed();
    }

    pconupdate = NULL;

    SCR_SetUpToDrawConsole();
    SCR_EraseCenterString();

    D_DisableBackBufferAccess();	// for adapters that can't stay mapped in
                                    //  for linear writes all the time

    VID_LockBuffer ();

//	V_RenderView ();

    VID_UnlockBuffer ();

    D_EnableBackBufferAccess();	// of all overlay stuff if drawing directly

    if (scr_drawdialog)
    {
        Sbar_Draw();
        Draw_FadeScreen();
        SCR_DrawNotifyString();
        scr_copyeverything = true;
    }
    else if (scr_drawloading)
    {
        SCR_DrawLoading();
        Sbar_Draw();
    }
    else if (_g->cl.intermission == 1 && key_dest == key_game)
    {
        Sbar_IntermissionOverlay();
    }
    else if (_g->cl.intermission == 2 && key_dest == key_game)
    {
        Sbar_FinaleOverlay();
        SCR_CheckDrawCenterString();
    }
    else if (_g->cl.intermission == 3 && key_dest == key_game)
    {
        SCR_CheckDrawCenterString();
    }
    else
    {
        SCR_DrawRam (); SCR_DrawNet (); SCR_DrawTurtle ();
        SCR_DrawPause();
        SCR_CheckDrawCenterString();
        Sbar_Draw();
        SCR_DrawConsole();
        M_Draw();
    }

    D_DisableBackBufferAccess();	// for adapters that can't stay mapped in
                                    //  for linear writes all the time
    if (pconupdate)
    {
        D_UpdateRects(pconupdate);
    }

    V_UpdatePalette();

//
// update one of three areas
//
    scr_copyeverything = 1;
    if (scr_copyeverything)
    {
        vrect.x = 0;
        vrect.y = 0;
        vrect.width = VID_WIDTH;
        vrect.height = VID_HEIGHT;
//        vrect.pnext = 0;

        VID_Update(&vrect);
    }
    else if (scr_copytop)
    {
        vrect.x = 0;
        vrect.y = 0;
        vrect.width = VID_WIDTH;
        vrect.height = VID_HEIGHT - sb_lines;
//        vrect.pnext = 0;

        VID_Update(&vrect);
    }
    else
    {
        vrect.x = scr_vrect.x;
        vrect.y = scr_vrect.y;
        vrect.width = scr_vrect.width;
        vrect.height = scr_vrect.height;
//        vrect.pnext = 0;

        VID_Update(&vrect);
    }
}

/*
 ==================
 SCR_UpdateWholeScreen
 ==================
 */
void SCR_UpdateWholeScreen(void)
{
    scr_fullupdate = 0;
    SCR_UpdateScreen();
}
