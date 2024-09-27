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
// d_surf.c: rasterization driver surface heap manager
#include "quakedef.h"
#include "d_local.h"
#include "r_local.h"
static  byte tmpLightMap[18 * 18 * 4];  // TBD: I'd like to save on this.
//float           surfscale;
#if WIN32
    int textureWillNotFit = 0;
#endif
#if SURF_CACHE
qboolean        r_cache_thrash;         // set if surface cache is thrashing

int                                     sc_size;
surfcache_t                     *sc_rover, *sc_base;

#define GUARDSIZE       4

int     D_SurfaceCacheForRes (int width, int height)
{
	int             size, pix;

	if (COM_CheckParm ("-surfcachesize"))
	{
		size = Q_atoi(com_argv[COM_CheckParm("-surfcachesize")+1]) * 1024;
		return size;
	}

	size = MAX_TEXTURE_SIZE + 64; //208 * 240 + 64; //SURFCACHE_SIZE_AT_320X200;

	pix = width*height;
	if (pix > 64000)
		size += (pix-64000)*3;


	return size;
}

void D_CheckCacheGuard (void)
{
	byte    *s;
	int             i;

	s = (byte *)sc_base + sc_size;
	for (i=0 ; i<GUARDSIZE ; i++)
		if (s[i] != (byte)i)
			Sys_Error ("D_CheckCacheGuard: failed");
}

void D_ClearCacheGuard (void)
{
	byte    *s;
	int             i;

	s = (byte *)sc_base + sc_size;
	for (i=0 ; i<GUARDSIZE ; i++)
		s[i] = (byte)i;
}


/*
================
D_InitCaches

================
*/
void D_InitCaches (void *buffer, int size)
{

	if (!msg_suppress_1)
		Con_Printf ("%ik surface cache\n", size/1024);

	sc_size = size - GUARDSIZE;
	sc_base = (surfcache_t *)buffer;
	sc_rover = sc_base;

	sc_base->next = NULL;
	sc_base->owner = NULL;
	sc_base->size = sc_size;

	D_ClearCacheGuard ();
}


/*
==================
D_FlushCaches
==================
*/
void D_FlushCaches (void)
{
	surfcache_t     *c;

	if (!sc_base)
		return;

	for (c = sc_base ; c ; c = c->next)
	{
		if (c->owner)
			*c->owner = NULL;
	}

	sc_rover = sc_base;
	sc_base->next = NULL;
	sc_base->owner = NULL;
	sc_base->size = sc_size;
}

int D_SCGetSize()
{
   return sc_size;
}
/*
=================
D_SCAlloc
=================
*/
surfcache_t     *D_SCAlloc (int width, int size)
{
	surfcache_t             *new;
	qboolean                wrapped_this_time;

	if ((width < 0) || (width > 256))
		Sys_Error ("D_SCAlloc: bad cache width %d\n", width);

	if ((size <= 0) || (size > 0x10000))
		Sys_Error ("D_SCAlloc: bad cache size %d\n", size);

	size = (int)&((surfcache_t *)0)->data[size];
	size = (size + 3) & ~3;
	if (size > sc_size)
		Sys_Error ("D_SCAlloc: %i > cache size. width was %d height is %d",size, width, size / width);

// if there is not size bytes after the rover, reset to the start
	wrapped_this_time = false;

	if ( !sc_rover || (byte *)sc_rover - (byte *)sc_base > sc_size - size)
	{
		if (sc_rover)
		{
			wrapped_this_time = true;
		}
		sc_rover = sc_base;
	}

// collect and free surfcache_t blocks until the rover block is large enough
	new = sc_rover;
	if (sc_rover->owner)
		*sc_rover->owner = NULL;

	while (new->size < size)
	{
	// free another
		sc_rover = sc_rover->next;
		if (!sc_rover)
			Sys_Error ("D_SCAlloc: hit the end of memory");
		if (sc_rover->owner)
			*sc_rover->owner = NULL;

		new->size += sc_rover->size;
		new->next = sc_rover->next;
	}

// create a fragment out of any leftovers
	if (new->size - size > 256)
	{
		sc_rover = (surfcache_t *)( (byte *)new + size);
		sc_rover->size = new->size - size;
		sc_rover->next = new->next;
		sc_rover->width = 0;
		sc_rover->owner = NULL;
		new->next = sc_rover;
		new->size = size;
	}
	else
		sc_rover = new->next;

	new->width = width;
// DEBUG
//	if (width > 0)
//		new->height = (size - sizeof(*new) + sizeof(new->data)) / width;

	new->owner = NULL;              // should be set properly after return

	if (d_roverwrapped)
	{
		if (wrapped_this_time || (sc_rover >= d_initial_rover))
			r_cache_thrash = true;
	}
	else if (wrapped_this_time)
	{
		d_roverwrapped = true;
	}

D_CheckCacheGuard ();   // DEBUG
	return new;
}


/*
=================
D_SCDump
=================
*/
void D_SCDump (void)
{
	surfcache_t             *test;

	for (test = sc_base ; test ; test = test->next)
	{
		if (test == sc_rover)
			Sys_Printf ("ROVER:\n");
		printf ("%p : %i bytes     %i width\n",test, test->size, test->width);
	}
}

//=============================================================================

// if the num is not a power of 2, assume it will not repeat

int     MaskForNum (int num)
{
	if (num==128)
		return 127;
	if (num==64)
		return 63;
	if (num==32)
		return 31;
	if (num==16)
		return 15;
	return 255;
}

int D_log2 (int num)
{
	int     c;

	c = 0;

	while (num>>=1)
		c++;
	return c;
}

//=============================================================================

/*
================
D_CacheSurface
================
*/
surfcache_t *D_CacheSurface (msurface_t *surface, int miplevel)
{
	surfcache_t     *cache;

//
// if the surface is animating or flashing, flush the cache
//
	r_drawsurf.texture = R_TextureAnimation (surface->texinfo->texture);
	r_drawsurf.lightadj[0] = d_lightstylevalue[surface->styles[0]];
	r_drawsurf.lightadj[1] = d_lightstylevalue[surface->styles[1]];
	r_drawsurf.lightadj[2] = d_lightstylevalue[surface->styles[2]];
	r_drawsurf.lightadj[3] = d_lightstylevalue[surface->styles[3]];

//
// see if the cache holds appropriate data
//

	cache = surface->cachespots[miplevel];

	if (cache && !cache->dlight && surface->dlightframe != r_framecount
			&& cache->texture == r_drawsurf.texture
			&& cache->lightadj[0] == r_drawsurf.lightadj[0]
			&& cache->lightadj[1] == r_drawsurf.lightadj[1]
			&& cache->lightadj[2] == r_drawsurf.lightadj[2]
			&& cache->lightadj[3] == r_drawsurf.lightadj[3] )
		return cache;

//
// determine shape of surface
//
//	surfscale = 1.0 / (1<<miplevel);
	r_drawsurf.surfmip = miplevel;
	r_drawsurf.surfwidth = surface->extents[0] >> miplevel;
	r_drawsurf.rowbytes = r_drawsurf.surfwidth;
	r_drawsurf.surfheight = surface->extents[1] >> miplevel;

//
// allocate memory if needed
//

	if (!cache)     // if a texture just animated, don't reallocate it
	{
		cache = D_SCAlloc (r_drawsurf.surfwidth,
						   r_drawsurf.surfwidth * r_drawsurf.surfheight);
		surface->cachespots[miplevel] = cache;
		cache->owner = &surface->cachespots[miplevel];
		#if NO_MINIMIZE
		    cache->mipscale = surfscale;
		#endif
	}

	if (surface->dlightframe == r_framecount)
		cache->dlight = 1;
	else
		cache->dlight = 0;

	r_drawsurf.surfdat = (pixel_t *)cache->data;

	cache->texture = r_drawsurf.texture;
	cache->lightadj[0] = r_drawsurf.lightadj[0];
	cache->lightadj[1] = r_drawsurf.lightadj[1];
	cache->lightadj[2] = r_drawsurf.lightadj[2];
	cache->lightadj[3] = r_drawsurf.lightadj[3];

//
// draw and light the surface texture
//
	r_drawsurf.surf = surface;

	c_surf++;
	R_DrawSurface ();

	return surface->cachespots[miplevel];
}
#else
uint8_t textureCacheBuffer[MAX_TEXTURE_SIZE];        // for surface rendering and edges.
enum
{
    TEXTURE_BUFFER_STATE_NONE = 0,                  // the texture buffer is not used/initialized
    TEXTURE_BUFFER_STATE_LOADING = 1,               // the texture buffer is being filled
    TEXTURE_BUFFER_STATE_READY = 2,                 // the texture buffer is ready to be used.
    TEXTURE_BUFFER_STATE_WILL_NOT_FIT = 3,          // the texture won't be loaded aynchronously, because it does not fit.
};
const char *const tcbStateString[] =
{ "None", "Loading", "Ready", "Will Not Fit"
};

enum
{
    TCB_LOAD_ASYNC = 0, TCB_LOAD_BLOCKING = 1
};
// TODO: move everything!
#define MAX_TCB_LOAD_SIZE 8192          // TODO: check if 8192 is ok.
typedef struct
{
    byte *extMemAddress;                //  where the texture is located. This is also the texture id
    uint16_t textureSize;               //  how big is the texture.
    uint16_t bytesRead;                 //  how many bytes read so far.
    uint16_t bytesBeingRead;            //  how many bytes we are reading
    uint16_t state;                     //  might be smaller, but we have 16 bits....
} textureCacheBuffer_t;
static textureCacheBuffer_t tcb[2];
static uint8_t currentTcbIndex;
static byte* setTcbLoadParameters(textureCacheBuffer_t *ptcb, int loadType)
{
    // first determine the amount
    int maxSize = ptcb->textureSize - ptcb->bytesRead;
    if (maxSize <= 0)
    {
        maxSize = 0;
    }
    if (maxSize > MAX_TCB_LOAD_SIZE && loadType == TCB_LOAD_ASYNC)
    {
        maxSize = MAX_TCB_LOAD_SIZE;
    }
    ptcb->bytesBeingRead = maxSize;
    // second determine the position
    int textCachePosition;
    if (ptcb == &tcb[0])
    {
        // we are loading in buffer 0. So we start from byte 0 + bytesRead.
        textCachePosition = ptcb->bytesRead;
    }
    else
    {
        //  loading in buffer 1. Starting from the end.
        textCachePosition = sizeof(textureCacheBuffer) - ptcb->textureSize + ptcb->bytesRead;
    }
    return &textureCacheBuffer[textCachePosition];
}
DRAWSURF_SEC byte* getCurrentTextureCacheAddress(void)
{
    if (currentTcbIndex == 0)
    {
        // we are loading in buffer 0. So we start from byte 0 + bytesRead.
        return textureCacheBuffer;
    }
    else
    {
        //  loading in buffer 1. Starting from the end.
        return &textureCacheBuffer[sizeof(textureCacheBuffer) - tcb[1].textureSize];
    }
}
#define PRELOAD_NEXT_LIGHT_MAP 0
#if PRELOAD_NEXT_LIGHT_MAP
  int16_t nextLightMapSurfPosIndex = -1;
#endif
void clearTextureCache(void)
{
#if PRELOAD_NEXT_LIGHT_MAP
  nextLightMapSurfPosIndex = -1;
#endif
    fastMemclear32(tcb, sizeof(tcb) / 4);
}
#if SORT_SURFS
extern uint16_t surfIdx[NUMSTACKSURFACES];
#endif
#define SHOW_TCB_STATE 0
#if WIN32 && SHOW_TCB_STATE
#define tcbPrintf printf
#else
#define tcbPrintf(...)
#endif
#if 0
void loadSurfaceLighting(int surfIndex, byte *lastTexture,  byte *newTexture)
{
  textureCacheBuffer_t *otherTcb = &tcb[1 - currentTcbIndex];
  if (lastTexture == newTexture)
  {
    // we do not need to have the new texture right now, but we must have as soon as possible lighting.
    // for this reason
    if (otherTcb->state == TEXTURE_BUFFER_STATE_LOADING)
    {

    }
  }
  else
  { // texture has changed so for sure now we must wait if we were loading. There's no advantage in interrupting (actually there would be...)
    if (otherTcb->state == TEXTURE_BUFFER_STATE_LOADING)
    {
      // was correctly set up. Let's wait and finish.
      extMemWaitAsynchDataRead();
      otherTcb->bytesRead += otherTcb->bytesBeingRead;
      // read the remaining, if required
      byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_BLOCKING);
      // read (blocking) remaining bytes
      if (otherTcb->bytesBeingRead)
      {
          extMemGetDataFromAddress( dest, otherTcb->extMemAddress + otherTcb->bytesRead, otherTcb->bytesBeingRead);
      }
      otherTcb->state = TEXTURE_BUFFER_STATE_READY;
    }
#warning issue load lighting
      // we must just wait the transfer to be finish, and then load the
  }
}
#endif
static DRAWSURF_SEC void findAndStartNextPreloadTexture(int currentSurfIndex, int maxSurfIndex, textureCacheBuffer_t *oldTcb, textureCacheBuffer_t *otherTcb,
    byte *newTexture)
{
    tcbPrintf("Finding a new texture to load. Shall be different from %p\r\n", newTexture);
    // we want now to scan next surfaces, to get the next texture to be loaded in the meantime we render the new
    for (currentSurfIndex = currentSurfIndex + 1; currentSurfIndex < maxSurfIndex; currentSurfIndex++)
    {
        // get next surface data, so we will find a new texture.
        surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
        //
        if (getSurfFlags(s) & (SURF_DRAWBACKGROUND))
            continue;
        msurface_t *pface = (msurface_t*) s->data;
        // texture animation must be accounted for.
        entity_t *oldEntity = NULL;  // shut off warnings
        if (s->insubmodel) // dirty hack.
        {
            oldEntity = _g->currententity;
            _g->currententity = getSurfEntity(s);
        }
#if MSURFACE_HAS_TEXINFO_POINTER
        texture_t *texture = R_TextureAnimation(pface->texinfo->texture);

#else
           texture_t *texture = R_TextureAnimation (getMsurfaceTexinfo(pface)->texture);
#endif
        if (s->insubmodel) // again dirty hack.
        {
            _g->currententity = oldEntity;
        }

        // is this new surface with a different texture?
        if (newTexture != texture->extmemdata[s->miplevel])
        {
            // yes! set the address and size (bytes read already set to 0)
            int size;
            if (getSurfFlags(s) & SURF_DRAWSKY)
                size = SKYSIZE * SKYSIZE;
            else
                size = (texture->width * texture->height) >> (2 * s->miplevel);
            oldTcb->textureSize = size;
            oldTcb->extMemAddress = texture->extmemdata[s->miplevel];
            if (otherTcb->textureSize + oldTcb->textureSize <= MAX_TEXTURE_SIZE)
            {   // will fit. start loading
                oldTcb->state = TEXTURE_BUFFER_STATE_LOADING;
                oldTcb->bytesRead = 0;
                byte *dest = setTcbLoadParameters(oldTcb, TCB_LOAD_ASYNC);
                extMemStartAsynchDataRead((uint32_t) oldTcb->extMemAddress, dest, oldTcb->bytesBeingRead);
                tcbPrintf("Found: Start loading texture %p. Being read %d\r\n", oldTcb->extMemAddress, oldTcb->bytesBeingRead);
#if WIN32
                    static int maxSum = 0;
                    if (maxSum < otherTcb->textureSize + oldTcb->textureSize)
                        maxSum = otherTcb->textureSize + oldTcb->textureSize;
                 //  printf("Texture will fit because otherTcb->textureSize  is %d and oldTcb->textureSize is %d. Max Sum: %d\r\n",otherTcb->textureSize, oldTcb->textureSize, maxSum);
#endif
            }
            else
            {  // won't fit with current new TCB. Will be loaded after, with a blocking function :(
                oldTcb->state = TEXTURE_BUFFER_STATE_WILL_NOT_FIT;
#if WIN32
                    textureWillNotFit++;
                   //  printf("Texture will NOT fit because otherTcb->textureSize  is %d and oldTcb->textureSize is %d.\r\n",otherTcb->textureSize, oldTcb->textureSize);
#endif
                oldTcb->bytesRead = 0;
                oldTcb->bytesBeingRead = 0;
                tcbPrintf("Found but will not start loading texture %p, too big.\r\n", oldTcb->extMemAddress);
            }
            return;
        }
    }
}
// extern int blocklights[];
static DRAWSURF_SEC void finishLoadingTexture(textureCacheBuffer_t *tcb)
{
    // was correctly set up. Let's wait and finish.
    extMemWaitAsynchDataRead();
    tcb->bytesRead += tcb->bytesBeingRead;
    // read the remaining, if required
    byte *dest = setTcbLoadParameters(tcb, TCB_LOAD_BLOCKING);
    // read (blocking) remaining bytes
    if (tcb->bytesBeingRead)
    {
        extMemGetDataFromAddress(dest, tcb->extMemAddress + tcb->bytesRead, tcb->bytesBeingRead);
    }
    tcb->state = TEXTURE_BUFFER_STATE_READY;

}
#if PRELOAD_NEXT_LIGHT_MAP
void loadAndBuildLighting(int currentSurfIndex, int loadRequired)
#else
static void loadAndBuildLighting(int currentSurfIndex)
#endif
{
    tcbPrintf("Load lighting\r\n");
    surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
    msurface_t *surf = (msurface_t*) s->data;
    int smax = (surf->extents[0] >> 4) + 1;
    int tmax = (surf->extents[1] >> 4) + 1;
    int size = smax * tmax;
    if (r_fullbright || !_g->cl.worldmodel->brushModelData->lightdata)
    {
        for (int i = 0; i < size; i++)
            _g->blocklights[i] = 0;
        return;
    }
    int lmnum;
    byte *lightmap = getMsurfaceSamples(surf);
    if (lightmap)
    {
        // count num of lightmaps
        for (lmnum = 0; lmnum < MAXLIGHTMAPS && surf->styles[lmnum] != 255; lmnum++)
        {
            // just count.
        }
        //
#if PRELOAD_NEXT_LIGHT_MAP
    if (loadRequired)
#endif
        {
            extMemStartAsynchDataRead((uint32_t) lightmap, tmpLightMap, (3 + size * lmnum) & ~3);
        }
    }
    // clear to ambient
    int al = _g->r_refdef.ambientlight << 8;
    for (int i = 0; i < size; i++)
        _g->blocklights[i] = al;
    //
    int index = ((byte*) surf - (byte*) _g->cl.worldmodel->brushModelData->surfaces) / sizeof(msurface_t); //not sure why it does not work.
    if (index < _g->cl.worldmodel->brushModelData->numsurfaces)
    {
        unsigned int nodeindex = _g->cl.worldmodel->brushModelData->surfNodeIndex[index];
        if (nodeHadDlight[nodeindex / 8] & (1 << (nodeindex % 8)))
            R_AddDynamicLights();
    }

    if (lightmap)
    {
#if PRELOAD_NEXT_LIGHT_MAP
    if (loadRequired)
#endif
        {
            extMemWaitAsynchDataRead();
        }
        lightmap = tmpLightMap;
        for (int maps = 0; maps < MAXLIGHTMAPS && surf->styles[maps] != 255; maps++)
        {
            unsigned int scale = r_drawsurf.lightadj[maps];	// 8.8 fraction
            for (int i = 0; i < size; i++)
                _g->blocklights[i] += lightmap[i] * scale;
            lightmap += size;	// skip to next lightmap
        }
    }
}
static DRAWSURF_SEC void pauseLoadingTexture(textureCacheBuffer_t *tcb)
{
    tcbPrintf("(PRELIGHT) pausing loading %p\r\n", tcb->extMemAddress);
    extMemStopDMA();
    //note: the following function gives the number of bytes that MAY be not loaded yet, conservatively
    int bytesRemaining = extMemGetRemainingBytes();
    tcbPrintf("Bytes Remaining %d, being read %d, size %d\r\n", bytesRemaining, tcb->bytesBeingRead, tcb->textureSize);
    if (bytesRemaining > tcb->bytesBeingRead)
    {
        tcb->bytesBeingRead = 0;
        //  not an error, there is a safety +1 in bytesRemaining.
    }
    else
        tcb->bytesBeingRead -= bytesRemaining;

}
DRAWSURF_SEC void lightedSurfacePreTextureLoaderHandler(byte *lastTexture, byte *newTexture, int newMip, int currentSurfIndex, int maxSurfIndex)
{
#if PRELOAD_NEXT_LIGHT_MAP
    int isLightTableReady = 0;
    isLightTableReady = (nextLightMapSurfPosIndex == currentSurfIndex);
    if (isLightTableReady)
    {
        extMemWaitAsynchDataRead();
        tcbPrintf("Finished light table DMA \r\n");
    }
#endif
    textureCacheBuffer_t *otherTcb = &tcb[1 - currentTcbIndex];
    textureCacheBuffer_t *oldTcb = &tcb[currentTcbIndex];
    tcbPrintf("(PRELIGHT) New Texture: (was %p) is %p. Current TCB: %d, State of other TCB is %s\r\n", lastTexture, newTexture, currentTcbIndex, tcbStateString[otherTcb->state]);
    if (extMemHasAsynchDataReadFinished())
    {
#if PRELOAD_NEXT_LIGHT_MAP
        if (isLightTableReady)
            tcbPrintf("Lighting was already loaded\r\n");
        else
            tcbPrintf("Lighting was NOT already loaded\r\n");
#endif
        tcbPrintf("DMA finished\r\n");
        //The DMA was not loading anything. So we don't have to stop it.
#if PRELOAD_NEXT_LIGHT_MAP
        loadAndBuildLighting(currentSurfIndex, !isLightTableReady);
#else
        loadAndBuildLighting(currentSurfIndex);
#endif
    }
    else
    {
        tcbPrintf("DMA not finished\r\n");
        // determine what we were reading. Determine if it's better to stop right now
        if (newTexture != lastTexture)
        {
            int remainingBytes = extMemGetRemainingBytes();
            if (remainingBytes * EXT_MEM_BYTE_TIME > EXT_MEM_ACCESS_TIME)
            {
                tcbPrintf("pause because is too long\r\n");
                pauseLoadingTexture(otherTcb);
            }
            else
            {
                // finish loading
                tcbPrintf("Finished loading\r\n");
                finishLoadingTexture(otherTcb);
            }
        }
        else  // we are just loading next surface. so it's always convenient stopping
        {
            tcbPrintf("Same tex, pausing\r\n");
            pauseLoadingTexture(otherTcb);
        }
#if PRELOAD_NEXT_LIGHT_MAP
        loadAndBuildLighting(currentSurfIndex, !isLightTableReady);
#else
        loadAndBuildLighting(currentSurfIndex);
#endif
    }
#if WIN32
    if (newTexture == NULL)
    {
        FIXME("ERRORRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR");
        __ASM("BKPT");
    }
#endif
    // Now for sure nothing is being loaded. Continue what we were doing
    if (lastTexture != newTexture)
    {

        tcbPrintf("(PRELIGHT) texture is new\r\n");
        // what is the state of the TCB ?
        switch (otherTcb->state)
        {
            case TEXTURE_BUFFER_STATE_READY:
            case TEXTURE_BUFFER_STATE_LOADING:
            {  // was loading, but did not finish last time. But is it the correct buffer?
                if (otherTcb->extMemAddress == newTexture)
                {
                    // update size. Note, if it was ready, the bytesBeing read is 0.
                    otherTcb->bytesRead += otherTcb->bytesBeingRead;
                    otherTcb->bytesBeingRead = 0;
                    if (otherTcb->bytesRead >= otherTcb->textureSize)
                    {
                        otherTcb->state = TEXTURE_BUFFER_STATE_READY;
                    }
                    if (otherTcb->state == TEXTURE_BUFFER_STATE_READY)
                    {
                        tcbPrintf("(LIGHT) Loading of current text was finished. Will preload the next texture in oldTcb (which will become other)\r\n");
                        findAndStartNextPreloadTexture(currentSurfIndex, maxSurfIndex, oldTcb, otherTcb, newTexture);
                        tcbPrintf("data: being read %d, read %d, size %d\r\n", oldTcb->bytesRead, oldTcb->bytesBeingRead, oldTcb->textureSize );
                    }
                    else
                    {
                        tcbPrintf("(LIGHT) will continue loading current texture in otherTCB (which will become old)\r\n");
                        // if there are still bytes to be loaded, load next part
                        byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_ASYNC);
                        extMemStartAsynchDataRead((uint32_t) otherTcb->extMemAddress + otherTcb->bytesRead, dest, otherTcb->bytesBeingRead);
                        // for sure it's still loading
                    }
                }
#if WIN32
                else
                {
                    // something was wrong
                    surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
                    msurface_t *pface = (msurface_t*) s->data;
                    tcbPrintf("tcbNt: %x nt %x f: %x", otherTcb->extMemAddress, newTexture, getSurfFlags(s));
                    FIXME("SOMETHING WAS WRONG");

                    int size;
                    mtexinfo_t *ti;
                    // get size
#if MSURFACE_HAS_TEXINFO_POINTER
                    ti = pface->texinfo;
#else
                    ti = getMsurfaceTexinfo(pface);
#endif
                    size = (ti->texture->width * ti->texture->height) >> (2 * newMip);
                    //
                    otherTcb->textureSize = size;
                    otherTcb->bytesRead = 0;
                    otherTcb->state = TEXTURE_BUFFER_STATE_LOADING;
                    otherTcb->extMemAddress = newTexture;
                    // load
                    byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_ASYNC);
                    extMemStartAsynchDataRead((uint32_t) otherTcb->extMemAddress + otherTcb->bytesRead, dest, otherTcb->bytesBeingRead);
                    otherTcb->state = TEXTURE_BUFFER_STATE_LOADING;
                }
#endif
                // this should not happen, but in case, if the pointer was not ok, then switch to not loaded case.
            }
                // change index
                currentTcbIndex = 1 - currentTcbIndex;
                // now the next or current texture is being loaded.
                return;
            case TEXTURE_BUFFER_STATE_NONE:
            case TEXTURE_BUFFER_STATE_WILL_NOT_FIT:
            {
                // the texture was not loaded, not even started. Well start loading it.
                // get data. NOTE: SKY IS NOT COVERED BECAUSE SKY DOES NOT HAVE LIGHT!
                surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
                msurface_t *pface = (msurface_t*) s->data;
                int size;
                mtexinfo_t *ti;
                // get size
#if MSURFACE_HAS_TEXINFO_POINTER
                ti = pface->texinfo;
#else
                ti = getMsurfaceTexinfo(pface);
#endif
                //NOTE: SKY IS NOT COVERED BECAUSE SKY DOES NOT HAVE LIGHT!
                size = (ti->texture->width * ti->texture->height) >> (2 * newMip);
                // texture anim
                otherTcb->extMemAddress = newTexture;
                tcbPrintf("(PRELIGHT) Preloading the current texture because did not fit %p\r\n", newTexture);
                //
                otherTcb->bytesRead = 0;
                otherTcb->textureSize = size;

                // if there are still bytes to be loaded, load next part
                byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_ASYNC);
                extMemStartAsynchDataRead((uint32_t) otherTcb->extMemAddress, dest, otherTcb->bytesBeingRead);
                otherTcb->state = TEXTURE_BUFFER_STATE_LOADING;
            }
                tcbPrintf("(PRELIGHT) CHANGING TCB INDEX\r\n");
                currentTcbIndex = 1 - currentTcbIndex;
                return;
        }
    }
    else
    {
        tcbPrintf("(PRELIGHT) texture is same. State of otherTcb is: %s\r\n", tcbStateString[otherTcb->state]);
        // same texture.  continue loading, if it was loading.
        if (otherTcb->state == TEXTURE_BUFFER_STATE_LOADING)
        {
            otherTcb->bytesRead += otherTcb->bytesBeingRead;
            otherTcb->bytesBeingRead = 0;
            if (otherTcb->bytesRead >= otherTcb->textureSize)
            {
                otherTcb->state = TEXTURE_BUFFER_STATE_READY;
                tcbPrintf("(LIGHT) finished loading current texture %p\r\n", otherTcb->extMemAddress);
            }
            else
            {
                // if there are still bytes to be loaded, load next part
                //oldTcb->extMemAddress  = lastTexture;
                tcbPrintf("(LIGHT) will continue loading current texture\r\n");
                byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_ASYNC);
                extMemStartAsynchDataRead((uint32_t) otherTcb->extMemAddress + otherTcb->bytesRead, dest, otherTcb->bytesBeingRead);
            }
        }
    }
}
DRAWSURF_SEC void textureLoaderHandler(byte *lastTexture, byte *newTexture, int newMip, int currentSurfIndex, int maxSurfIndex)
{
#if WIN32
  //  printf("textures not fitting %d\r\n", textureWillNotFit);
#endif
    // note: new texture already takes into account about animation
    // If we need to load lighting, we won't load blocking anything.
    // Was there any texture change?
    textureCacheBuffer_t *otherTcb = &tcb[1 - currentTcbIndex];
    textureCacheBuffer_t *oldTcb = &tcb[currentTcbIndex];
    if (lastTexture != newTexture)
    {
#if WIN32 && SHOW_TCB_STATE
        tcbPrintf("(HANDLER) New Texture. was %p is %p. currentTCB: %d, State of other TCB is %s\r\n", lastTexture, newTexture, currentTcbIndex, tcbStateString[otherTcb->state]);
#endif
        // there is a new texture. Let's see if we have it in the other buffer.
        // note: the texture for sure won't be in the same buffer, as lastTexture != newTexture
        // make sure the current state is to none, so can be reused
        if (newTexture != NULL)
        {  // if nextexture is null, it's because we are currently drawing for instance a background, so we would like to load new one.
           // so we skip this part.
            switch (otherTcb->state)
            {
                case TEXTURE_BUFFER_STATE_READY:
                case TEXTURE_BUFFER_STATE_LOADING:
                {  // was loading, but did not finish last time. But is it the correct buffer?
                    if (otherTcb->extMemAddress == newTexture)
                    {
                        if (otherTcb->state == TEXTURE_BUFFER_STATE_READY)
                        {
                            break;
                        }
                        finishLoadingTexture(otherTcb);
                        break;
                    }
#if WIN32
                    surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
                    msurface_t *pface = (msurface_t *) s->data;
                    tcbPrintf("tcbNt: %x nt %x f: %x", otherTcb->extMemAddress, newTexture, getSurfFlags(s));
                    FIXME("ERROR");
#endif
                    // this should not happen, but in case, if the pointer was not ok, then switch to not loaded case.
                }
                    /* fall through */
                    /* no break */
                case TEXTURE_BUFFER_STATE_NONE:
                case TEXTURE_BUFFER_STATE_WILL_NOT_FIT:
                    // the texture was not loaded, not even started. Well load it.
                {
                    // get data.
                    surf_t *s = &_g->surfaces[surfIdx[currentSurfIndex]];
                    msurface_t *pface = (msurface_t*) s->data;
                    int size;
                    // get size
                    if (getSurfFlags(s) & SURF_DRAWSKY)
                    {
                        size = SKYSIZE * SKYSIZE;
                    }
                    else
                    {
                        mtexinfo_t *ti;
#if MSURFACE_HAS_TEXINFO_POINTER
                        ti = pface->texinfo;
#else
                        ti = getMsurfaceTexinfo(pface);
#endif
                        size = (ti->texture->width * ti->texture->height) >> (2 * newMip);
                    }
                    otherTcb->extMemAddress = newTexture;
                    //
                    otherTcb->bytesRead = 0;
                    otherTcb->textureSize = size;
                    finishLoadingTexture(otherTcb);
                }
            }
        }
        // now we have loaded for sure in otherTcb the data for the new surface.
        // we need to find which will be the next surface
        // switch tcb.
        currentTcbIndex = 1 - currentTcbIndex;
        // scan for a surface with different texture and load it.
        findAndStartNextPreloadTexture(currentSurfIndex, maxSurfIndex, oldTcb, otherTcb, newTexture);
    }
    else
    {
#if WIN32 && SHOW_TCB_STATE
        tcbPrintf("(HANDLER) Same Texture. (was %p) is %p. Current TCB: %d, State of other TCB is %s\r\n", lastTexture, newTexture, currentTcbIndex, tcbStateString[otherTcb->state]);
#endif

        // same texture. Then we normally need to continue loading the next one, if required. There is only one exception,
        // i.e. when the current texture is not loaded yet. This is the case when we call this handler AFTER we have loaded
        // the lighting data.
        if (oldTcb->state == TEXTURE_BUFFER_STATE_LOADING)
        {
            tcbPrintf("(HANDLER) Finishing loading texture that will be used now %p\r\n", oldTcb->extMemAddress);
            finishLoadingTexture(oldTcb); // note: this also changes the state!
            // NOTE: in the following API we swap old with other TCB because it would load on the first TCB param
            findAndStartNextPreloadTexture(currentSurfIndex, maxSurfIndex, otherTcb, oldTcb, newTexture);
        }
        // no texture changed. But we might have to load the other one.
        switch (otherTcb->state)
        {
            case TEXTURE_BUFFER_STATE_NONE:
                break;          //nothing to do
            case TEXTURE_BUFFER_STATE_WILL_NOT_FIT:
                break;          // idem
            case TEXTURE_BUFFER_STATE_READY:
                break;          // idem
            case TEXTURE_BUFFER_STATE_LOADING:
                if (extMemHasAsynchDataReadFinished())
                {
                    tcbPrintf("(HANDLER) Finished loading. Read (Excluding now) %d, being read %d, size %d\r\n", otherTcb->bytesRead, otherTcb->bytesBeingRead, otherTcb->textureSize);
                    otherTcb->bytesRead += otherTcb->bytesBeingRead;
                    if (otherTcb->bytesRead >= otherTcb->textureSize)
                    {
                        otherTcb->bytesBeingRead = 0;
                        otherTcb->state = TEXTURE_BUFFER_STATE_READY;
                    }
                    else
                    {
                        // if there are stil bytes to be loaded, load next part
                        byte *dest = setTcbLoadParameters(otherTcb, TCB_LOAD_ASYNC);
                        extMemStartAsynchDataRead((uint32_t) otherTcb->extMemAddress + otherTcb->bytesRead, dest, otherTcb->bytesBeingRead);
                    }
                }
                // else: don't do anything. Maybe next time...
                break;
            default:
#if WIN32
                FIXME("ERROR ON TCB state!\r\n");
#endif
        }
#if PRELOAD_NEXT_LIGHT_MAP
        if (otherTcb->state != TEXTURE_BUFFER_STATE_LOADING)
        {
            // if we are here, we either have finished loadding, or we could not load anyway. Therefore load next
            int nextSurfPosIdx = currentSurfIndex + 1;
            nextLightMapSurfPosIndex = - 1;
            if (nextSurfPosIdx >= maxSurfIndex)
            {
                return;
            }
            surf_t *s = &_g->surfaces[surfIdx[nextSurfPosIdx]];
            msurface_t *surf = (msurface_t *) s->data;
            if (!surf)
            {
                return;
            }
            if (getSurfFlags(s) & (SURF_DRAWBACKGROUND | SURF_DRAWSKY | SURF_DRAWTURB))
            {
                return;
            }
            if (r_fullbright || !cl.worldmodel->brushModelData->lightdata)
	        {
		        return;
	        }
            byte *lightmap =  getMsurfaceSamples(surf);
            if (!lightmap)
                return;
	        int lmnum;
            for (lmnum = 0; lmnum < MAXLIGHTMAPS && surf->styles[lmnum] != 255; lmnum++)
            {
                // just count.
            }
            if (!lmnum)
                return;
            int smax = (surf->extents[0]>>4)+1;
            int tmax = (surf->extents[1]>>4)+1;
            int size = smax*tmax;
            //
            extMemStartAsynchDataRead((uint32_t) lightmap, tmpLightMap, size * lmnum);
            nextLightMapSurfPosIndex = nextSurfPosIdx;
        }
#endif

    }
    return;
}
#define TEST_PIX_SAVED_SAME_TEXTURE 1
#if TEST_PIX_SAVED_SAME_TEXTURE
#if USE_TEXTURE_METADATA
extern texture_t*  lastTexture;
#else
extern void *lastTextureEmd;
#endif
#endif // TEST_PIX_SAVED_SAME_TEXTURE

DRAWSURF_SEC void* getSurfBuffer(msurface_t *surface, int surfPos, int surfNum, int miplevel, int *width)
{
#if MSURFACE_HAS_TEXINFO_POINTER
    r_drawsurf.texture = R_TextureAnimation(surface->texinfo->texture);

#else
	r_drawsurf.texture = R_TextureAnimation (getMsurfaceTexinfo(surface)->texture);
#endif
    //
    r_drawsurf.lightadj[0] = d_lightstylevalue[surface->styles[0]];
    r_drawsurf.lightadj[1] = d_lightstylevalue[surface->styles[1]];
    r_drawsurf.lightadj[2] = d_lightstylevalue[surface->styles[2]];
    r_drawsurf.lightadj[3] = d_lightstylevalue[surface->styles[3]];

    r_drawsurf.surfmip = miplevel;

    r_drawsurf.surfwidth = surface->extents[0] >> miplevel;
#if PRE_LIGHT_SURFACES
	r_drawsurf.rowbytes = r_drawsurf.surfwidth;
#endif
    r_drawsurf.surfheight = surface->extents[1] >> miplevel;

    r_drawsurf.surf = surface;
#if 1
    lightedSurfacePreTextureLoaderHandler(lastTextureEmd, r_drawsurf.texture->extmemdata[r_drawsurf.surfmip], miplevel, surfPos, surfNum);
#else
    textureLoaderHandler(lastTextureEmd, r_drawsurf.texture->extmemdata[r_drawsurf.surfmip], miplevel, surfPos, surfNum);
#endif
    R_DrawSurface();
    lastTextureEmd = r_drawsurf.texture->extmemdata[r_drawsurf.surfmip];
    textureLoaderHandler(lastTextureEmd, r_drawsurf.texture->extmemdata[r_drawsurf.surfmip], miplevel, surfPos, surfNum);

#if WIN32
#warning debug
    int all0 = 0;
    for (int i = 0; i < tcb[currentTcbIndex].textureSize; i++)
        if (getCurrentTextureCacheAddress()[i] == 0)
            all0++;
//    if (all0 > 100)
//        FIXME("ALL 0!");
#endif
    *width = r_drawsurf.surfwidth;
    return getCurrentTextureCacheAddress();
}

#endif
