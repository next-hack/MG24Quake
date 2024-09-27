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
// snd_mix.c -- portable code to mix sounds for snd_dma.c
#if !WIN32
#include "quakedef.h"
#if !WIN32
#include "audio.h"
#endif
#ifdef _WIN32_NO_SDL
#include "winquake.h"
#else
#define DWORD	unsigned long
#endif
#define	PAINTBUFFER_SIZE	                1024
//AUX_SECTION portable_samplepair_t paintbuffer[PAINTBUFFER_SIZE];
#if HAS_RUNTIME_SCALE_TABLE
int		snd_scaletable[32][256];
#elif WIN32
static inline int snd_scaletable(int i, int j)
{
    return ((signed char)j) * i * 8;
}
#endif
int *snd_p, snd_linear_count, snd_vol;
short *snd_out;
#if WIN32
void S_TransferPaintBuffer(int endtime, portable_samplepair_t * paintbuffer)
{
#if WIN32
	int 	out_idx;
	int 	count;
	int 	out_mask;
	int 	*p;
	int 	step;
	int		val;
	int		snd_vol;
	DWORD	*pbuf;
#ifdef _WIN32_NO_SDL
	int		reps;
	DWORD	dwSize,dwSize2;
	DWORD	*pbuf2;
	HRESULT	hresult;
#endif
#if 0
	if (shm->samplebits == 16 && shm->channels == 2)
	{
		S_TransferStereo16 (endtime);
		return;
	}
#endif
	p = (int *) paintbuffer;
	count = (endtime - paintedtime) * shm->channels;
	out_mask = shm->samples - 1;
	out_idx = paintedtime * shm->channels & out_mask;
	step = 3 - shm->channels;
	snd_vol = volume*256;

#ifdef _WIN32_NO_SDL
	else
#endif
	{
		pbuf = (DWORD *)shm->buffer;
	}

	{
//	        FIXME("TRANSFER8");

		unsigned char *out = (unsigned char *) pbuf;
		while (count--)
		{
			val = (*p * snd_vol) >> 8;
			p+= step;
			if (val > 0x7fff)
				val = 0x7fff;
			else if (val < (short)0x8000)
				val = (short)0x8000;
			out[out_idx] = (val>>8) + 128;
			out_idx = (out_idx + 1) & out_mask;
		}
	}

#ifdef _WIN32_NO_SDL
	if (pDSBuf) {
		DWORD dwNewpos, dwWrite;
		int il = paintedtime;
		int ir = endtime - paintedtime;

		ir += il;

		pDSBuf->lpVtbl->Unlock(pDSBuf, pbuf, dwSize, NULL, 0);

		pDSBuf->lpVtbl->GetCurrentPosition(pDSBuf, &dwNewpos, &dwWrite);

//		if ((dwNewpos >= il) && (dwNewpos <= ir))
//			Con_Printf("%d-%d p %d c\n", il, ir, dwNewpos);
	}
#endif
#else
	int   out_idx;
	  int   count;
	  int   out_mask;
	  int   *p;
	  int   val;
	  int   snd_vol;
	  p = (int *) paintbuffer;
	  count = (endtime - paintedtime) * 2;
	  out_mask = 2 * AUDIO_BUFFER_LENGTH - 1;
	  out_idx = (paintedtime * 2) & out_mask;
	  snd_vol = volume*256;
	  unsigned char *out = (unsigned char *) audioBuffer;
    while (count--)
    {
      val = (*p * snd_vol) >> 8;
      p++;
      if (val > 0x7fff)
        val = 0x7fff;
      else if (val < (short)0x8000)
        val = (short)0x8000;
      out[out_idx] = (val>>8) + 128;
      out_idx = (out_idx + 1) & out_mask;
    }
#endif
}
#endif

/*
 ===============================================================================

 CHANNEL MIXING

 ===============================================================================
 */
#if WIN32
void SND_PaintChannelFrom8 (portable_samplepair_t * paintbuffer, channel_t *ch, sfx_t *psfx, int endtime);
#else
void SND_PaintChannelFrom8(portable_samplepair_t *paintbuffer, channel_t *ch, sfx_t *psfx, int endtime, int pos);
#endif
#if WIN32
extern sfx_t *known_sfx;

void S_PaintChannels(int endtime)
{
    int	paintedChannels = 0;
	int 	i;
	int 	end;
	channel_t *ch;
//	sfxcache_t	*sc;
	int		ltime, count;
    portable_samplepair_t paintbuffer[PAINTBUFFER_SIZE]; // next-hack: in stack because snd update is done when small amount in stack is used
	while (paintedtime < endtime)
	{
	//            printf("In loop start %d %d\r\n", paintedtime, endtime);

	// if paintbuffer is smaller than DMA buffer
		end = endtime;
		if (endtime - paintedtime > PAINTBUFFER_SIZE)
			end = paintedtime + PAINTBUFFER_SIZE;

	// clear the paint buffer
		Q_memset(paintbuffer, 0, (end - paintedtime) * sizeof(portable_samplepair_t));

	// paint in the channels.
		ch = channels;

		for (i=0; i<total_channels ; i++, ch++)
		{
			if (!ch->sfxnum)
            {
             //   printf("0 sfxnum\r\n");
				continue;

            }
			if (!ch->leftvol && !ch->rightvol)
            {
            //    printf("0 vol\r\n");
				continue;
            }


			ltime = paintedtime;
			while (ltime < end)
			{	// paint up to end
				if (ch->end < end)
					count = ch->end - ltime;
				else
					count = end - ltime;

				if (count > 0)
				{
				//    printf("Painting %d from sfx %d, name %s\r\n", count, ch->sfxnum, known_sfx[ch->sfxnum - 1].name);
				    if (paintedChannels < MAX_CONCURRENT_CHANNELS)
            {
    				    paintedChannels ++;
                        SND_PaintChannelFrom8(paintbuffer, ch, &known_sfx[ch->sfxnum - 1], count);
            }
					ltime += count;
				//    printf("End Painting %d\r\n", ltime);

				}

			// if at end of loop, restart
				if (ltime >= ch->end)
				{
					if (known_sfx[ch->sfxnum-1].loopstart >= 0)
					{
						ch->pos = known_sfx[ch->sfxnum-1].loopstart;
						ch->end = ltime + known_sfx[ch->sfxnum-1].length - ch->pos;
					}
					else
					{	// channel just stopped
						ch->sfxnum = 0;
						break;
					}
				}
			}

		}

	// transfer out according to DMA format
		S_TransferPaintBuffer(end, paintbuffer);
		paintedtime = end;
	}
#if 0
	// endtime is currentTime + AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY
  int paintedChannels = 0;
  int   i;
  int   end;
  channel_t *ch;
  //  sfxcache_t  *sc;
  int   ltime, count;
  portable_samplepair_t paintbuffer[PAINTBUFFER_SIZE]; // next-hack: in stack because snd update is done when small amount in stack is used
  int startTime = endtime - (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY);
  int difference = paintedtime - startTime;
  paintedtime = startTime;
  // we painted "paintedTime" but we are updating earlier, i.e. from startTime.
  // we need to increase all channels by the difference
  for (i=0; i<total_channels ; i++, ch++)
   {
     if (!ch->sfxnum)
     {
            //   printf("0 sfxnum\r\n");
       continue;

     }
   }
  while (paintedtime < endtime)
  {
  // if paintbuffer is smaller than DMA buffer
    end = endtime;
    if (endtime - paintedtime > PAINTBUFFER_SIZE)
      end = paintedtime + PAINTBUFFER_SIZE;

  // clear the paint buffer
    Q_memset(paintbuffer, 0, (end - paintedtime) * sizeof(portable_samplepair_t));

    // paint in the channels.
    ch = channels;
    //
    for (i=0; i<total_channels ; i++, ch++)
    {
      if (!ch->sfxnum)
      {
             //   printf("0 sfxnum\r\n");
        continue;

      }
      if (!ch->leftvol && !ch->rightvol)
      {
            //    printf("0 vol\r\n");
        continue;
      }

      ltime = paintedtime;
      while (ltime < end)
      {
        // paint up to end
        if (ch->end < end)
          count = ch->end - ltime;
        else
          count = end - ltime;

        if (count > 0)
        {
        //    printf("Painting %d from sfx %d, name %s\r\n", count, ch->sfxnum, known_sfx[ch->sfxnum - 1].name);
            if (paintedChannels < MAX_CONCURRENT_CHANNELS)
            {
                paintedChannels ++;
                        SND_PaintChannelFrom8(paintbuffer, ch, &known_sfx[ch->sfxnum - 1], count);
            }
          ltime += count;
        //    printf("End Painting %d\r\n", ltime);

        }

      // if at end of loop, restart
        if (ltime >= ch->end)
        {
          if (known_sfx[ch->sfxnum-1].loopstart >= 0)
          {
            ch->pos = known_sfx[ch->sfxnum-1].loopstart;
            ch->end = ltime + known_sfx[ch->sfxnum-1].length - ch->pos;
          }
          else
          { // channel just stopped
            ch->sfxnum = 0;
            break;
          }
        }
      }

    }

  // transfer out according to DMA format
  S_TransferPaintBuffer(end, paintbuffer);
  paintedtime = end;
#endif
}
//	printf("Used Channels %d\r\n", usedChannels);
#endif

void SND_InitScaletable(void)
{
#if HAS_RUNTIME_SCALE_TABLE
	int		i, j;

	for (i=0 ; i<32 ; i++)
		for (j=0 ; j<256 ; j++)
			snd_scaletable[i][j] = ((signed char)j) * i * 8;
#endif
}

#if	WIN32

void SND_PaintChannelFrom8 (portable_samplepair_t * paintbuffer, channel_t *ch, sfx_t *psfx, int count)
{
	int 	data;
	int		*lscale, *rscale;

	int		i;

	if (ch->leftvol > 255)
		ch->leftvol = 255;
	if (ch->rightvol > 255)
		ch->rightvol = 255;
	// load data
  unsigned char tsfx[PAINTBUFFER_SIZE + 4];
  unsigned char *sfx = extMemGetDataFromAddress(tsfx, (signed char *)psfx->data + ch->pos, (count + 3) & ~3);

	for (i=0 ; i<count ; i++)
	{
		data = sfx[i];
    paintbuffer[i].left += snd_scaletable(ch->leftvol >> 3, data);
		paintbuffer[i].right += snd_scaletable(ch->rightvol >> 3, data);
	}

	ch->pos += count;
}
#else
void SND_PaintChannelFrom8(portable_samplepair_t *paintbuffer, channel_t *ch, sfx_t *psfx, int count, int pos)
{
    int data;
    int i;

    // load data
    unsigned char tsfx[PAINTBUFFER_SIZE + 8];
#define ALIGNED_SND_LOAD 1
#if ALIGNED_SND_LOAD
    int offs = ((uint32_t) psfx->data + pos) & 3;
    char *sfx = extMemGetDataFromAddress((char*) tsfx, (signed char*) (((uint32_t) psfx->data + pos) & ~3), (count + 3 + offs) & ~3);
    sfx += offs;
#else
  char *sfx = extMemGetDataFromAddress((char *) tsfx, (signed char *)(((uint32_t)psfx->data + pos)), count);
#endif
#if 1
    int lvol = ch->leftvol & ~7; // >> 3);
    int rvol = ch->rightvol & ~7; // >> 3);
#else
  int lvol = ch->leftvol  >> 3;
  int rvol = ch->rightvol  >> 3;

#endif
    for (i = 0; i < (count & 3); i++)
    {
        data = sfx[i];
        paintbuffer[i].left += ((signed char) data) * lvol; //* 8;//snd_scaletable(lvol, data);
        paintbuffer[i].right += ((signed char) data) * rvol; // * 8; // snd_scaletable(rvol, data);
    }

    for (; i < count; i += 4)
    {
        data = sfx[i];
        paintbuffer[i].left += ((signed char) data) * lvol; //* 8;//snd_scaletable(lvol, data);
        paintbuffer[i].right += ((signed char) data) * rvol; // * 8; // snd_scaletable(rvol, data);
        data = sfx[i + 1];
        paintbuffer[i + 1].left += ((signed char) data) * lvol; //* 8;//snd_scaletable(lvol, data);
        paintbuffer[i + 1].right += ((signed char) data) * rvol; // * 8; // snd_scaletable(rvol, data);
        data = sfx[i + 2];
        paintbuffer[i + 2].left += ((signed char) data) * lvol; //* 8;//snd_scaletable(lvol, data);
        paintbuffer[i + 2].right += ((signed char) data) * rvol; // * 8; // snd_scaletable(rvol, data);
        data = sfx[i + 3];
        paintbuffer[i + 3].left += ((signed char) data) * lvol; //* 8;//snd_scaletable(lvol, data);
        paintbuffer[i + 3].right += ((signed char) data) * rvol; // * 8; // snd_scaletable(rvol, data);
    }
}

#endif
#else
#include "quakedef.h"

#ifdef _WIN32_NO_SDL
#include "winquake.h"
#else
#define DWORD	unsigned long
#endif
#define MAX_CONCURRENT_CHANNELS             8
#define	PAINTBUFFER_SIZE	                1024
//AUX_SECTION portable_samplepair_t paintbuffer[PAINTBUFFER_SIZE];
 #if HAS_RUNTIME_SCALE_TABLE
int		snd_scaletable[32][256];
#else
static inline int snd_scaletable(int i, int j)
{
    return ((signed char)j) * i * 8;
}
#endif
int 	*snd_p, snd_linear_count, snd_vol;
short	*snd_out;

void Snd_WriteLinearBlastStereo16 (void);

#if	!id386
void Snd_WriteLinearBlastStereo16 (void)
{
	int		i;
	int		val;

	for (i=0 ; i<snd_linear_count ; i+=2)
	{
		val = (snd_p[i]*snd_vol)>>8;
		if (val > 0x7fff)
			snd_out[i] = 0x7fff;
		else if (val < (short)0x8000)
			snd_out[i] = (short)0x8000;
		else
			snd_out[i] = val;

		val = (snd_p[i+1]*snd_vol)>>8;
		if (val > 0x7fff)
			snd_out[i+1] = 0x7fff;
		else if (val < (short)0x8000)
			snd_out[i+1] = (short)0x8000;
		else
			snd_out[i+1] = val;
	}
}
#endif

#if 0
void S_TransferStereo16 (int endtime)
{
	int		lpos;
	int		lpaintedtime;
	DWORD	*pbuf;
#ifdef _WIN32_NO_SDL
	int		reps;
	DWORD	dwSize,dwSize2;
	DWORD	*pbuf2;
	HRESULT	hresult;
#endif

	snd_vol = volume*256;

	snd_p = (int *) paintbuffer;
	lpaintedtime = paintedtime;

#ifdef _WIN32_NO_SDL
	if (pDSBuf)
	{
		reps = 0;

		while ((hresult = pDSBuf->lpVtbl->Lock(pDSBuf, 0, gSndBufSize, &pbuf, &dwSize,
									   &pbuf2, &dwSize2, 0)) != DS_OK)
		{
			if (hresult != DSERR_BUFFERLOST)
			{
				Con_Printf ("S_TransferStereo16: DS::Lock Sound Buffer Failed\n");
				S_Shutdown ();
				S_Startup ();
				return;
			}

			if (++reps > 10000)
			{
				Con_Printf ("S_TransferStereo16: DS: couldn't restore buffer\n");
				S_Shutdown ();
				S_Startup ();
				return;
			}
		}
	}
	else
#endif
	{
		pbuf = (DWORD *)shm->buffer;
	}

	while (lpaintedtime < endtime)
	{
	// handle recirculating buffer issues
		lpos = lpaintedtime & ((shm->samples>>1)-1);

		snd_out = (short *) pbuf + (lpos<<1);

		snd_linear_count = (shm->samples>>1) - lpos;
		if (lpaintedtime + snd_linear_count > endtime)
			snd_linear_count = endtime - lpaintedtime;

		snd_linear_count <<= 1;

	// write a linear blast of samples
		Snd_WriteLinearBlastStereo16 ();

		snd_p += snd_linear_count;
		lpaintedtime += (snd_linear_count>>1);
	}

#ifdef _WIN32_NO_SDL
	if (pDSBuf)
		pDSBuf->lpVtbl->Unlock(pDSBuf, pbuf, dwSize, NULL, 0);
#endif
}
#endif
void S_TransferPaintBuffer(int endtime, portable_samplepair_t * paintbuffer)
{
	int 	out_idx;
	int 	count;
	int 	out_mask;
	int 	*p;
	int 	step;
	int		val;
	int		snd_vol;
	DWORD	*pbuf;
#ifdef _WIN32_NO_SDL
	int		reps;
	DWORD	dwSize,dwSize2;
	DWORD	*pbuf2;
	HRESULT	hresult;
#endif
#if 0
	if (shm->samplebits == 16 && shm->channels == 2)
	{
		S_TransferStereo16 (endtime);
		return;
	}
#endif
	p = (int *) paintbuffer;
	count = (endtime - paintedtime) * shm->channels;
	out_mask = shm->samples - 1;
	out_idx = paintedtime * shm->channels & out_mask;
	step = 3 - shm->channels;
	snd_vol = volume*256;

#ifdef _WIN32_NO_SDL
	if (pDSBuf)
	{
		reps = 0;

		while ((hresult = pDSBuf->lpVtbl->Lock(pDSBuf, 0, gSndBufSize, &pbuf, &dwSize,
									   &pbuf2,&dwSize2, 0)) != DS_OK)
		{
			if (hresult != DSERR_BUFFERLOST)
			{
				Con_Printf ("S_TransferPaintBuffer: DS::Lock Sound Buffer Failed\n");
				S_Shutdown ();
				S_Startup ();
				return;
			}

			if (++reps > 10000)
			{
				Con_Printf ("S_TransferPaintBuffer: DS: couldn't restore buffer\n");
				S_Shutdown ();
				S_Startup ();
				return;
			}
		}
	}
	else
#endif
	{
		pbuf = (DWORD *)shm->buffer;
	}

#if 0
	if (shm->samplebits == 16)
	{
//	        FIXME("TRANSFER16");

		short *out = (short *) pbuf;
		while (count--)
		{
			val = (*p * snd_vol) >> 8;
			p+= step;
			if (val > 0x7fff)
				val = 0x7fff;
			else if (val < (short)0x8000)
				val = (short)0x8000;
			out[out_idx] = val;
			out_idx = (out_idx + 1) & out_mask;
		}
			        FIXME("TRANSFER16BIS");

	}
	else if (shm->samplebits == 8)
#endif
	{
//	        FIXME("TRANSFER8");

		unsigned char *out = (unsigned char *) pbuf;
		while (count--)
		{
			val = (*p * snd_vol) >> 8;
			p+= step;
			if (val > 0x7fff)
				val = 0x7fff;
			else if (val < (short)0x8000)
				val = (short)0x8000;
			out[out_idx] = (val>>8) + 128;
			out_idx = (out_idx + 1) & out_mask;
		}
	}

#ifdef _WIN32_NO_SDL
	if (pDSBuf) {
		DWORD dwNewpos, dwWrite;
		int il = paintedtime;
		int ir = endtime - paintedtime;

		ir += il;

		pDSBuf->lpVtbl->Unlock(pDSBuf, pbuf, dwSize, NULL, 0);

		pDSBuf->lpVtbl->GetCurrentPosition(pDSBuf, &dwNewpos, &dwWrite);

//		if ((dwNewpos >= il) && (dwNewpos <= ir))
//			Con_Printf("%d-%d p %d c\n", il, ir, dwNewpos);
	}
#endif
}


/*
===============================================================================

CHANNEL MIXING

===============================================================================
*/

void SND_PaintChannelFrom8 (portable_samplepair_t * paintbuffer, channel_t *ch, sfx_t *psfx, int endtime);
extern sfx_t *known_sfx;

void S_PaintChannels(int endtime)
{
    #if WIN32
        int usedChannels = 0;
    #endif // WIN32
    int	paintedChannels = 0;
	int 	i;
	int 	end;
	channel_t *ch;
//	sfxcache_t	*sc;
	int		ltime, count;
    portable_samplepair_t paintbuffer[PAINTBUFFER_SIZE]; // next-hack: in stack because snd update is done when small amount in stack is used
	while (paintedtime < endtime)
	{
	//            printf("In loop start %d %d\r\n", paintedtime, endtime);

	// if paintbuffer is smaller than DMA buffer
		end = endtime;
		if (endtime - paintedtime > PAINTBUFFER_SIZE)
			end = paintedtime + PAINTBUFFER_SIZE;

	// clear the paint buffer
		Q_memset(paintbuffer, 0, (end - paintedtime) * sizeof(portable_samplepair_t));

	// paint in the channels.
		ch = channels;

		for (i=0; i<total_channels ; i++, ch++)
		{
			if (!ch->sfxnum)
            {
             //   printf("0 sfxnum\r\n");
				continue;

            }
			if (!ch->leftvol && !ch->rightvol)
            {
            //    printf("0 vol\r\n");
				continue;
            }
//			sc = S_LoadSound (ch->sfx);
//			if (!sc)
//				continue;

			ltime = paintedtime;
            usedChannels ++ ;
			while (ltime < end)
			{	// paint up to end
				if (ch->end < end)
					count = ch->end - ltime;
				else
					count = end - ltime;

				if (count > 0)
				{
				//    printf("Painting %d from sfx %d, name %s\r\n", count, ch->sfxnum, known_sfx[ch->sfxnum - 1].name);
				    if (paintedChannels < MAX_CONCURRENT_CHANNELS)
                    {
    				    paintedChannels ++;
                        SND_PaintChannelFrom8(paintbuffer, ch, &known_sfx[ch->sfxnum - 1], count);
                    }
					ltime += count;
				//    printf("End Painting %d\r\n", ltime);

				}

			// if at end of loop, restart
				if (ltime >= ch->end)
				{
					if (known_sfx[ch->sfxnum-1].loopstart >= 0)
					{
						ch->pos = known_sfx[ch->sfxnum-1].loopstart;
						ch->end = ltime + known_sfx[ch->sfxnum-1].length - ch->pos;
					}
					else
					{	// channel just stopped
						ch->sfxnum = 0;
						break;
					}
				}
			}

		}

	// transfer out according to DMA format
		S_TransferPaintBuffer(end, paintbuffer);
		paintedtime = end;

	}
//	printf("Used Channels %d\r\n", usedChannels);
}
void SND_InitScaletable (void)
{
#if HAS_RUNTIME_SCALE_TABLE
	int		i, j;

	for (i=0 ; i<32 ; i++)
		for (j=0 ; j<256 ; j++)
			snd_scaletable[i][j] = ((signed char)j) * i * 8;
#endif
}


#if	!id386

void SND_PaintChannelFrom8 (portable_samplepair_t * paintbuffer, channel_t *ch, sfx_t *psfx, int count)
{
	int 	data;
	int		*lscale, *rscale;
	unsigned char *sfx;
	int		i;

	if (ch->leftvol > 255)
		ch->leftvol = 255;
	if (ch->rightvol > 255)
		ch->rightvol = 255;
#if HAS_RUNTIME_SCALE_TABLE
	lscale = snd_scaletable[ch->leftvol >> 3];
	rscale = snd_scaletable[ch->rightvol >> 3];
#endif
	sfx = (signed char *)psfx->data + ch->pos;

	for (i=0 ; i<count ; i++)
	{
		data = sfx[i];
#if HAS_RUNTIME_SCALE_TABLE
        paintbuffer[i].left += lscale[data];
		paintbuffer[i].right += rscale[data];
#else
        paintbuffer[i].left += snd_scaletable(ch->leftvol >> 3, data);
		paintbuffer[i].right += snd_scaletable(ch->rightvol >> 3, data);
#endif
	}

	ch->pos += count;
}

#endif	// !id386
#endif
