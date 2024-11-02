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
// vid_sdl.h -- sdl video driver
#if WIN32
#include "SDL.h"
#include "quakedef.h"
#include "d_local.h"
byte displayBuffer[320 * 200];

extern viddef_t    vid;                // global video state

// The original defaults
#define    BASEWIDTH    320
#define    BASEHEIGHT   200


int    VGA_width, VGA_height, VGA_rowbytes, VGA_bufferrowbytes = 0;
byte    *VGA_pagebase;

static SDL_Surface *screen = NULL;
static SDL_Surface * workSurface = NULL;
static SDL_Window * window  = NULL;
static qboolean mouse_avail;
static float   mouse_x, mouse_y;
static int mouse_oldbuttonstate = 0;

// No support for option menus
#if 0
void (*vid_menudrawfn)(void) = NULL;
void (*vid_menukeyfn)(int key) = NULL;
#endif
void VID_SetPalette (unsigned char *palette)
{
    int i;
    SDL_Color colors[256];

    for ( i=0; i<256; ++i )
    {
        colors[i].r = *palette++;
        colors[i].g = *palette++;
        colors[i].b = *palette++;
    }
    SDL_SetPaletteColors(workSurface->format->palette, colors, 0, 256);
    //SDL_SetColors(screen, colors, 0, 256);
}

void    VID_ShiftPalette (unsigned char *palette)
{
    VID_SetPalette(palette);
}

void    VID_Init (unsigned char *palette)
{
    int pnum, chunk;
    byte *cache;
    int cachesize;
    Uint8 video_bpp;
    Uint16 video_w, video_h;
    Uint32 flags;

    // Load the SDL library
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
        Sys_Error("VID: Couldn't load SDL: %s", SDL_GetError());

    // Set up display mode (width and height)
//    vid.maxwarpwidth = WARP_WIDTH;
//    vid.maxwarpheight = WARP_HEIGHT;
    if ((pnum=COM_CheckParm("-winsize")))
    {
        if (pnum >= com_argc-2)
            Sys_Error("VID: -winsize <width> <height>\n");
    }

    // Set video width, height and flags
    flags = (SDL_WINDOW_SHOWN );


    // Initialize display
//    if (!(screen = SDL_SetVideoMode(VID_WIDTH, VID_HEIGHT, 8, flags)))
    window =   SDL_CreateWindow( "SDL Tutorial", 10, 10, VID_WIDTH, VID_HEIGHT, SDL_WINDOW_SHOWN );
    screen = SDL_GetWindowSurface(window);
    workSurface = SDL_CreateRGBSurface(0, VID_WIDTH, VID_HEIGHT,8, 0, 0, 0, 0);
    if (!screen)
        Sys_Error("VID: Couldn't set video mode: %s\n", SDL_GetError());
    VID_SetPalette(palette);
    //SDL_WM_SetCaption("sdlquake","sdlquake");
    // now know everything we need to know about the buffer
    VGA_width = VID_WIDTH;
    VGA_height = VID_HEIGHT;
    vid.aspect = ((float)VID_HEIGHT / (float)VID_WIDTH) * (320.0 / 240.0);
//    vid.numpages = 1;
    vid.colormap = host_colormap;
    vid.fullbright = 256 - LittleLong (*((int *)vid.colormap + 2048));
    vid.buffer = displayBuffer;
    VGA_pagebase = workSurface->pixels;
    VGA_rowbytes = workSurface->pitch;
    vid.conbuffer = vid.buffer;
//    vid.direct = 0;
#if DYNAMIC_3D_VIEWPORT_SIZE
    // allocate z buffer and surface cache
    chunk = VID_WIDTH * VID_HEIGHT * sizeof (*d_zbuffer);
#if SURF_CACHE
    cachesize = D_SurfaceCacheForRes (VID_WIDTH, VID_HEIGHT);
    chunk += cachesize;
#endif
    printf("Chunk size for graphics: %d\r\n", chunk);
    d_pzbuffer = Hunk_HighAllocName(chunk, "video");
    if (d_pzbuffer == NULL)
        Sys_Error ("Not enough memory for video mode\n");
    // initialize the cache memory
        cache = (byte *) d_pzbuffer
                + VID_WIDTH * VID_HEIGHT * sizeof (*d_pzbuffer);
    printf("Size of *d_pzbuffer %d and byte %d\r\n", sizeof (*d_pzbuffer), sizeof(byte), sizeof(pixel_t));
#if SURF_CACHE
    D_InitCaches (cache, cachesize);
#endif
#endif

    // initialize the mouse
    SDL_ShowCursor(1);
   // debug_triangle_init(palette);
}

void    VID_Shutdown (void)
{
    SDL_Quit();
}

void    VID_Update (vrect_t *rects)
{
    #define SCREEN_HEIGHT 200
    #define FULL_FRAME_BUFFER 0
#if FULL_FRAME_BUFFER
 memcpy(VGA_pagebase, displayBuffer, 320 * 200);

#else
    memcpy(VGA_pagebase, displayBuffer, 320 * 152);
    if (rects->height > 152)
        memcpy((byte*) VGA_pagebase + 320 * 152, ((byte*) (&d_zbuffer[320*DRAW_BUFFER_HEIGHT]) - 320 * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT)), 48 * 320);
#endif
        SDL_BlitSurface(workSurface, NULL, screen, NULL);
    //Update the surface
    SDL_UpdateWindowSurface( window );
}

/*
================
D_BeginDirectRect
================
*/
void D_BeginDirectRect (int x, int y, byte *pbitmap, int width, int height)
{
    Uint8 *offset;


    if (!screen) return;
    if ( x < 0 ) x = screen->w+x-1;
    offset = (Uint8 *)screen->pixels + y*screen->pitch + x;
    while ( height-- )
    {
        memcpy(offset, pbitmap, width);
        offset += screen->pitch;
        pbitmap += width;
    }
}


/*
================
D_EndDirectRect
================
*/
void D_EndDirectRect (int x, int y, int width, int height)
{
    if (!screen) return;
    if (x < 0) x = screen->w+x-1;
//    SDL_UpdateRect(screen, x, y, width, height);
    SDL_Rect r;
    r.x = x; r.w = width; r.h = height; r.y  = y ;
    SDL_UpdateWindowSurfaceRects(window, &r, 1);
}


/*
================
Sys_SendKeyEvents
================
*/

void Sys_SendKeyEvents(void)
{
    SDL_Event event;
    int sym, state;
     int modstate;

    while (SDL_PollEvent(&event))
    {
        switch (event.type) {

            case SDL_KEYDOWN:
            case SDL_KEYUP:
                sym = event.key.keysym.sym;
                state = event.key.state;
                modstate = SDL_GetModState();
                switch(sym)
                {
                   case SDLK_DELETE: sym = K_DEL; break;
                   case SDLK_BACKSPACE: sym = K_BACKSPACE; break;
                   case SDLK_F1: sym = K_F1; break;
                   case SDLK_F2: sym = K_F2; break;
                   case SDLK_F3: sym = K_F3; break;
                   case SDLK_F4: sym = K_F4; break;
                   case SDLK_F5: sym = K_F5; break;
                   case SDLK_F6: sym = K_F6; break;
                   case SDLK_F7: sym = K_F7; break;
                   case SDLK_F8: sym = K_F8; break;
                   case SDLK_F9: sym = K_F9; break;
                   case SDLK_F10: sym = K_F10; break;
                   case SDLK_F11: sym = K_F11; break;
                   case SDLK_F12: sym = K_F12; break;
                   case SDLK_PAUSE: sym = K_PAUSE; break;
                   case SDLK_UP: sym = K_UPARROW; break;
                   case SDLK_DOWN: sym = K_DOWNARROW; break;
                   case SDLK_RIGHT: sym = K_RIGHTARROW; break;
                   case SDLK_LEFT: sym = K_LEFTARROW; break;
                   case SDLK_INSERT: sym = K_INS; break;
                   case SDLK_HOME: sym = K_HOME; break;
                   case SDLK_END: sym = K_END; break;
                   case SDLK_PAGEUP: sym = K_PGUP; break;
                   case SDLK_PAGEDOWN: sym = K_PGDN; break;
                   case SDLK_RSHIFT:
                   case SDLK_LSHIFT: sym = K_SHIFT; break;
                   case SDLK_RCTRL:
                   case SDLK_LCTRL: sym = K_CTRL; break;
                   case SDLK_RALT:
                   case SDLK_LALT: sym = K_ALT; break;
                   case SDLK_KP_0:
                       if(modstate & KMOD_NUM) sym = K_INS;
                       else sym = SDLK_0;
                       break;
                   case SDLK_KP_1:
                       if(modstate & KMOD_NUM) sym = K_END;
                       else sym = SDLK_1;
                       break;
                   case SDLK_KP_2:
                       if(modstate & KMOD_NUM) sym = K_DOWNARROW;
                       else sym = SDLK_2;
                       break;
                   case SDLK_KP_3:
                       if(modstate & KMOD_NUM) sym = K_PGDN;
                       else sym = SDLK_3;
                       break;
                   case SDLK_KP_4:
                       if(modstate & KMOD_NUM) sym = K_LEFTARROW;
                       else sym = SDLK_4;
                       break;
                   case SDLK_KP_5: sym = SDLK_5; break;
                   case SDLK_KP_6:
                       if(modstate & KMOD_NUM) sym = K_RIGHTARROW;
                       else sym = SDLK_6;
                       break;
                   case SDLK_KP_7:
                       if(modstate & KMOD_NUM) sym = K_HOME;
                       else sym = SDLK_7;
                       break;
                   case SDLK_KP_8:
                       if(modstate & KMOD_NUM) sym = K_UPARROW;
                       else sym = SDLK_8;
                       break;
                   case SDLK_KP_9:
                       if(modstate & KMOD_NUM) sym = K_PGUP;
                       else sym = SDLK_9;
                       break;
                   case SDLK_KP_PERIOD:
                       if(modstate & KMOD_NUM) sym = K_DEL;
                       else sym = SDLK_PERIOD;
                       break;
                   case SDLK_KP_DIVIDE: sym = SDLK_SLASH; break;
                   case SDLK_KP_MULTIPLY: sym = SDLK_ASTERISK; break;
                   case SDLK_KP_MINUS: sym = SDLK_MINUS; break;
                   case SDLK_KP_PLUS: sym = SDLK_PLUS; break;
                   case SDLK_KP_ENTER: sym = SDLK_RETURN; break;
                   case SDLK_KP_EQUALS: sym = SDLK_EQUALS; break;
                }
                // If we're not directly handled and still above 255
                // just force it to 0
                if(sym > 255) sym = 0;
                Key_Event(sym, state);
                break;

            case SDL_MOUSEMOTION:
                if ( (event.motion.x != (VID_WIDTH/2)) ||
                     (event.motion.y != (VID_HEIGHT/2)) ) {
                    mouse_x = event.motion.xrel*10;
                    mouse_y = event.motion.yrel*10;
                    if ( (event.motion.x < ((VID_WIDTH/2)-(VID_WIDTH/4))) ||
                         (event.motion.x > ((VID_WIDTH/2)+(VID_WIDTH/4))) ||
                         (event.motion.y < ((VID_HEIGHT/2)-(VID_HEIGHT/4))) ||
                         (event.motion.y > ((VID_HEIGHT/2)+(VID_HEIGHT/4))) ) {
                        //SDL_WarpMouse(VID_WIDTH/2, VID_HEIGHT/2);
             //           SDL_WarpMouseGlobal(VID_WIDTH/2, VID_HEIGHT/2);
                    }
                }
                break;

            case SDL_QUIT:
                CL_Disconnect ();
                Host_ShutdownServer(false);
                Sys_Quit ();
                break;
            default:
                break;
        }
    }
}

void IN_Init (void)
{
    if ( COM_CheckParm ("-nomouse") )
        return;
    mouse_x = mouse_y = 0.0;
    mouse_avail = 1;
}

void IN_Shutdown (void)
{
    mouse_avail = 0;
}

void IN_Commands (void)
{
    int i;
    int mouse_buttonstate;

    if (!mouse_avail) return;

    i = SDL_GetMouseState(NULL, NULL);
    /* Quake swaps the second and third buttons */
    mouse_buttonstate = (i & ~0x06) | ((i & 0x02)<<1) | ((i & 0x04)>>1);
    for (i=0 ; i<3 ; i++) {
        if ( (mouse_buttonstate & (1<<i)) && !(mouse_oldbuttonstate & (1<<i)) )
            Key_Event (K_MOUSE1 + i, true);

        if ( !(mouse_buttonstate & (1<<i)) && (mouse_oldbuttonstate & (1<<i)) )
            Key_Event (K_MOUSE1 + i, false);
    }
    mouse_oldbuttonstate = mouse_buttonstate;
}

void IN_Move (usercmd_t *cmd)
{
    if (!mouse_avail)
        return;

    mouse_x *= sensitivity;
    mouse_y *= sensitivity;

    if ( (in_strafe.state & 1) || (lookstrafe && (in_mlook.state & 1) ))
        cmd->sidemove += m_side * mouse_x;
    else
        _g->cl.viewangles[YAW] -= m_yaw * mouse_x;
    if (in_mlook.state & 1)
        V_StopPitchDrift ();

    if ( (in_mlook.state & 1) && !(in_strafe.state & 1)) {
        _g->cl.viewangles[PITCH] += m_pitch * mouse_y;
        if (_g->cl.viewangles[PITCH] > 80)
            _g->cl.viewangles[PITCH] = 80;
        if (_g->cl.viewangles[PITCH] < -70)
            _g->cl.viewangles[PITCH] = -70;
    } else {
        if ((in_strafe.state & 1) && noclip_anglehack)
            cmd->upmove -= m_forward * mouse_y;
        else
            cmd->forwardmove -= m_forward * mouse_y;
    }
    mouse_x = mouse_y = 0.0;
}

void VID_LockBuffer (void)
{
}

void VID_UnlockBuffer (void)
{
}
/*
================
Sys_ConsoleInput
================
*/
char *Sys_ConsoleInput (void)
{
    return 0;
}
#else

#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
#include "d_local.h"
#include "keyboard.h"
char* Sys_ConsoleInput(void)
{
    return 0;
}
void VID_SetPalette(unsigned char *palette)
{
    VID_ShiftPalette(palette);
}
uint16_t g_palette[256];
void VID_ShiftPalette(unsigned char *palette)
{
    int changed = 0;
    int i = 0;
    for (i = 0; i < 256; i+= 2)
    {
        uint16_t r, g, b, rgb, rgb2;
        r= *palette++ >> 3;
        g = *palette++ >> 2;
        b = *palette++ >> 3;
        rgb = (r << (6 + 5)) | (g << 5) | (b << (0));
        rgb = (rgb >> 8) | (rgb << 8);
        //
        r= *palette++ >> 3;
        g = *palette++ >> 2;
        b = *palette++ >> 3;
        rgb2 = (r << (6 + 5)) | (g << 5) | (b << (0));
        rgb2 = (rgb2 >> 8) | (rgb2 << 8);
        uint32_t *bp = (uint32_t *) &g_palette[i];
        uint32_t p = rgb | ((uint32_t)rgb2 << 16);
        if (*bp != p)
        {
            *bp = p;
            changed = 1;
            i+=2;
            break;
        }
    }
    // continue without checking
    for (; i < 256; i+= 2)
    {
        uint16_t r, g, b, rgb, rgb2;
        r= *palette++ >> 3;
        g = *palette++ >> 2;
        b = *palette++ >> 3;
        rgb = (r << (6 + 5)) | (g << 5) | (b << (0));
        rgb = (rgb >> 8) | (rgb << 8);
        //
        r= *palette++ >> 3;
        g = *palette++ >> 2;
        b = *palette++ >> 3;
        rgb2 = (r << (6 + 5)) | (g << 5) | (b << (0));
        rgb2 = (rgb2 >> 8) | (rgb2 << 8);
        uint32_t *bp = (uint32_t *) &g_palette[i];
        uint32_t p = rgb | (rgb2 << 16);
        *bp = p;
    }

    if (changed)
        Sbar_Changed();

    displayData.pPalette = g_palette;
}

void VID_Init(unsigned char *palette)
{
    (void) palette;
    // Set up display mode (width and height)
    vid.aspect = ((float) SCREEN_HEIGHT / (float) SCREEN_WIDTH) * (320.0 / 240.0);
//    vid.numpages = 1;
    vid.colormap = host_colormap;
    int fb;
    extMemGetDataFromAddress(&fb, (int*) vid.colormap + 2048, sizeof(fb));
    vid.fullbright = 256 - fb;
    vid.buffer = (void*) displayData.displayFrameBuffer;
    vid.conbuffer = vid.buffer;
    //vid.conrowbytes = 320;
    //     vid.direct = 0;
}

void VID_Shutdown(void)
{
}

void VID_Update(vrect_t *r)
{
    startDisplayRefresh(displayData.workingBuffer, r->height > 152);

}

/*
 ================
 D_BeginDirectRect
 ================
 */
void D_BeginDirectRect(int x, int y, byte *pbitmap, int width, int height)
{
    (void) x;
    (void) y;
    (void) pbitmap;
    (void) width;
    (void) height;
}

/*
 ================
 D_EndDirectRect
 ================
 */
void D_EndDirectRect(int x, int y, int width, int height)
{
    (void) x;
    (void) y;
    (void) width;
    (void) height;
}

/*
 ================
 Sys_SendKeyEvents
 ================
 */
enum
{
    vk_up = 0, vk_down = 1, vk_left = 2, vk_right = 3, vk_strafe_left = 4, vk_strafe_right = 5, vk_look_up = 6,       // alt + up
    vk_look_down = 7,     // alt + down
    vk_fire = 8,          // fire
    vk_change_weapon = 9, // chg weapon
    vk_jump = 10,         // use
    vk_esc = 11,          // alt + use
    vk_swim_up = 12,
    vk_swim_down = 13,
    vk_run = 14,
    vk_f3 = 15,
    vk_max_keys

};
void Sys_SendKeyEvents(void)
{
    static uint16_t oldVirtualKeys = 0; // 0 = not pressed
    uint16_t virtualKeys = 0;
    uint16_t keys;

    getKeys(&keys);
    //
#if KEYBOARD == SPI2X74165_KEYBOARD
    for (int i = 0; i < 16; i++)
    {
        if ((keys & (1 << i)) != 0)
        {
            switch (1 << i)
            {
                // right dpad
                case KEY_R_LEFT:
                    virtualKeys |= 1 << vk_fire;
                    break;
                case KEY_R_RIGHT:
                    virtualKeys |= 1 << vk_jump;
                    break;
                case KEY_R_UP:
                    virtualKeys |= 1 << vk_change_weapon;
                    break;
                case KEY_R_DOWN:
                    virtualKeys |= 1 << vk_run;
                    break;
                    // left dpad
                case KEY_UP:
                    virtualKeys |= 1 << vk_up;
                    break;
                case KEY_DOWN:
                    virtualKeys |= 1 << vk_down;
                    break;
                case KEY_LEFT:
                    virtualKeys |= 1 << vk_left;
                    break;
                case KEY_RIGHT:
                    virtualKeys |= 1 << vk_right;
                    break;
                    // triggers
                case KEY_LT_UP:
                    virtualKeys |= 1 << vk_look_up;
                    break;
                case KEY_LT_DOWN:
                    virtualKeys |= 1 << vk_look_down;
                    break;
                case KEY_RT_UP:
                    virtualKeys |= 1 << vk_strafe_right;
                    break;
                case KEY_RT_DOWN:
                    virtualKeys |= 1 << vk_strafe_left;
                    break;

                case KEY_F1:
                    virtualKeys |= 1 << vk_esc;
                    break;
                case KEY_F2:
                    virtualKeys |= 1 << vk_swim_down;
                    break;
                case KEY_F3:
                    virtualKeys |= 1 << vk_f3;
                    break;
                case KEY_F4:
                    virtualKeys |= 1 << vk_swim_down;
                    break;
            }
        }
    }
#else
  int alt = (keys & KEY_ALT) != 0;
  for (int i = 0; i < 8; i++)
  {
    if ((1 << i) == KEY_ALT)
    {
      continue;
    }
    if ((keys & (1 << i)) != 0)
    {
      switch( 1 << i)
      {
        case KEY_FIRE:
          virtualKeys |= (1 << vk_fire);
          break;
        case KEY_USE:
          virtualKeys |= 1 << (alt ? vk_esc: vk_jump );
          break;
        case KEY_CHGW:
          virtualKeys |= 1 << vk_change_weapon;
          break;
        case KEY_UP:
          virtualKeys |= 1 << (alt ? vk_look_up: vk_up );
          break;
        case KEY_DOWN:
          virtualKeys |= 1 << (alt ? vk_look_down: vk_down);
          break;
        case KEY_LEFT:
          virtualKeys |= 1 << (alt ? vk_strafe_left: vk_left);
          break;
        case KEY_RIGHT:
          virtualKeys |= 1 << (alt ? vk_strafe_right: vk_right);
          break;
      }
    }
  }
#endif
    uint32_t changed = virtualKeys ^ oldVirtualKeys;

    for (int i = 0; i < vk_max_keys; i++)
    {
        if (changed & (1 << i))
        {
            int state = (virtualKeys & (1 << i)) != 0;
            int sym = 0;
            switch (i)
            {
                case vk_up:
                    sym = K_UPARROW;
                    break;
                case vk_down:
                    sym = K_DOWNARROW;
                    break;
                case vk_left:
                    sym = K_LEFTARROW;
                    break;
                case vk_right:
                    sym = K_RIGHTARROW;
                    break;
                case vk_strafe_left:
                    sym = ',';
                    break;
                case vk_strafe_right:
                    sym = '.';
                    break;
                case vk_look_up:
                    sym = 'a';
                    break;
                case vk_look_down:
                    sym = 'z';
                    break;
                case vk_fire:
                    sym = K_CTRL;
                    break;
                case vk_change_weapon:
                    sym = '/';
                    break;
                case vk_jump:
                    sym = K_SPACE;
                    break;
                case vk_esc:
                    sym = K_ESCAPE;
                    break;
                case vk_swim_down:
                    sym = 'c';
                    break;
                case vk_swim_up:
                    sym = 'd';
                    break;
                case vk_run:
                    sym = K_SHIFT;
                    break;
                case vk_f3:
                    sym = 'y';
                    break;
            }
            Key_Event(sym, state);
        }
    }

    oldVirtualKeys = virtualKeys;
}

void IN_Init(void)
{

}

void IN_Shutdown(void)
{

}

void IN_Commands(void)
{

}

void IN_Move(usercmd_t *cmd)
{
    int32_t lx, ly, rx, ry;
    getAnalogInput(&lx, &ly, &rx, &ry);

    lx *= sensitivity;
    ly *= sensitivity;
    rx *= sensitivity;
    ry *= sensitivity;

    _g->cl.viewangles[YAW] -= m_yaw * rx;

    if (in_mlook.state & 1)
    {
        V_StopPitchDrift();
        _g->cl.viewangles[PITCH] += m_pitch * ry;
        if (_g->cl.viewangles[PITCH] > 80)
            _g->cl.viewangles[PITCH] = 80;
        if (_g->cl.viewangles[PITCH] < -70)
            _g->cl.viewangles[PITCH] = -70;
    }
    cmd->forwardmove -= m_forward * ly;
    cmd->sidemove += m_side * lx;
}

#endif
