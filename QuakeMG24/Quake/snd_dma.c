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
// snd_dma.c -- main control for any streaming sound output device
#if !WIN32
#include "quakedef.h"

#ifdef _WIN32_NO_SDL
#include "winquake.h"
#endif
#if !WIN32
#include "audio.h"
#endif
void S_Play(void);
void S_PlayVol(void);
void S_SoundList(void);
void S_Update_();
void S_StopAllSounds(qboolean clear);
void S_StopAllSoundsC(void);

// =======================================================================
// Internal sound data & structures
// =======================================================================

AUX_SECTION channel_t channels[MAX_CHANNELS];
int total_channels;

int snd_blocked = 0;
static qboolean snd_ambient = 1;
qboolean snd_initialized = false;

// pointer should go away
#if WIN32
volatile dma_t  *shm = 0;
volatile dma_t sn;
#endif
vec3_t listener_origin;
//vec3_t listener_forward;
vec3_t listener_right;
//vec3_t listener_up;
const vec_t sound_nominal_clip_dist = 1000.0f;

int soundtime;		// sample PAIRS
int paintedtime; 	// sample PAIRS
sfx_t *known_sfx;		// hunk allocated [MAX_SFX]
int num_sfx;

sfx_t *ambient_sfx[NUM_AMBIENTS];

const int desired_speed = 11025;
const int desired_bits = 8;

int sound_started = 0;

#if USE_ORIGINAL_CVAR
cvar_t bgmvolume = {"bgmvolume", "1", true};
cvar_t volume = {"volume", "0.7", true};

cvar_t nosound = {"nosound", "0"};
cvar_t precache = {"precache", "1"};
cvar_t loadas8bit = {"loadas8bit", "0"};
cvar_t bgmbuffer = {"bgmbuffer", "4096"};
cvar_t ambient_level = {"ambient_level", "0.3"};
cvar_t ambient_fade = {"ambient_fade", "100"};
cvar_t snd_noextraupdate = {"snd_noextraupdate", "0"};
cvar_t snd_show = {"snd_show", "0"};
cvar_t _snd_mixahead = {"_snd_mixahead", "0.1", true};
#endif

// ====================================================================
// User-setable variables
// ====================================================================

//
// Fake dma is a synchronous faking of the DMA progress used for
// isolating performance in the renderer.  The fakedma_updates is
// number of times S_Update() is called per second.
//

qboolean fakedma = false;
int fakedma_updates = 15;

void S_AmbientOff(void)
{
    snd_ambient = false;
}

void S_AmbientOn(void)
{
    snd_ambient = true;
}

void S_SoundInfo_f(void)
{
#if WIN32
	if (!sound_started || !shm)
	{
		Con_Printf ("sound system not started. Total Channels %d\n", total_channels);
		return;
	}
    Con_Printf("%5d stereo\n", shm->channels - 1);
    Con_Printf("%5d samples\n", shm->samples);
    Con_Printf("%5d samplepos\n", shm->samplepos);
    Con_Printf("%5d samplebits\n", shm->samplebits);
    Con_Printf("%5d submission_chunk\n", shm->submission_chunk);
    Con_Printf("%5d speed\n", shm->speed);
    Con_Printf("0x%x dma buffer\n", shm->buffer);
	Con_Printf("%5d total_channels\n", total_channels);
#endif
}

/*
 ================
 S_Startup
 ================
 */

void S_Startup(void)
{
    int rc;
    if (!snd_initialized)
        return;

    rc = SNDDMA_Init();

    if (!rc)
    {
#ifdef	_WIN32
    Con_Printf("S_Startup: SNDDMA_Init failed.\n");
    FIXME("error");
#endif
        sound_started = 0;

        return;
    }

    sound_started = 1;
}

/*
 ================
 S_Init
 ================
 */
void S_Init(void)
{

    Con_Printf("\nSound Initialization\n");
#if WIN32
	if (COM_CheckParm("-nosound"))
    {

		return;

    }
#endif

#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable(&nosound);
	Cvar_RegisterVariable(&volume);
	Cvar_RegisterVariable(&precache);
	Cvar_RegisterVariable(&loadas8bit);
	Cvar_RegisterVariable(&bgmvolume);
	Cvar_RegisterVariable(&bgmbuffer);
	Cvar_RegisterVariable(&ambient_level);
	Cvar_RegisterVariable(&ambient_fade);
	Cvar_RegisterVariable(&snd_noextraupdate);
	Cvar_RegisterVariable(&snd_show);
	Cvar_RegisterVariable(&_snd_mixahead);
#endif
    Cvar_Set("loadas8bit", "1");
    Con_Printf("loading all sounds as 8bit\n");
    snd_initialized = true;

    S_Startup();
#if HAS_RUNTIME_SCALETABLE
	SND_InitScaletable ();
#endif
//	known_sfx = Hunk_AllocName (MAX_SFX*sizeof(sfx_t), "sfx_t");

    num_sfx = 0;

// create a piece of DMA memory
#if 0
	if (fakedma)
	{
	    Sys_Error("fake dma");
		//shm = (void *) Hunk_AllocName(sizeof(*shm), "shm");
		shm->splitbuffer = 0;
		shm->samplebits = 8;
		shm->speed = 11025;
		shm->channels = 2;
		shm->samples = 32768;
		shm->samplepos = 0;
		shm->soundalive = true;
		shm->gamealive = true;
		shm->submission_chunk = 1;
//		shm->buffer = Hunk_AllocName(1<<16, "shmbuf");
	}
#endif
#if WIN32
	if ( shm ) {
		Con_Printf ("Sound sampling rate: %i\n", shm->speed);
		Con_Printf ("Sound sampling bits: %i\n", shm->samplebits);
	}
	else
    {
        FIXME("ERROR");
	}
#endif

    byte sfx_buffer[MAX_SFX * sizeof(sfx_t)] =
    { 0
    };
    printf("Using %d bytes to temporarily load all sounds in pak\r\n", sizeof(sfx_buffer));
    known_sfx = (sfx_t*) sfx_buffer;
    // FIXME: this work only for single pak file!
    int numfile = 0;
    int oldpr = precache;
    precache = 1;
    while (1)
    {
        dpackfile_t packfile;
        if (!getDPackFile(&packfile, numfile))
            break;      // no more files to load
        if (num_sfx >= MAX_SFX)
            break;
#if WIN32
        printf("Pack File Name %d is %s\r\n", numfile, packfile.name);
#endif
        const char soundDir[] = "sound/";
        int soundDirNameLength = strlen(soundDir);
        if (strstr(packfile.name, ".wav"))
        {
#if WIN32
           printf("Precaching %s as sound number %d\r\n", strstr(packfile.name, "sound/") + soundDirNameLength, num_sfx);
#endif
            S_PrecacheSound(strstr(packfile.name, "sound/") + soundDirNameLength);
        }
        numfile++;
    }
    printf("precached: %d sounds. Opr is %d\r\n", num_sfx, oldpr);

    precache = oldpr;
    FIXME("sound");
    // now all sounds are there. Save them
    known_sfx = storeToInternalFlash(known_sfx, sizeof(sfx_t) * num_sfx);
    //
    //
    for (int i = 0; i < NUM_AMBIENTS; i++)
        ambient_sfx[i] = 0;

    ambient_sfx[AMBIENT_WATER] = S_PrecacheSound("ambience/water1.wav");
    ambient_sfx[AMBIENT_SKY] = S_PrecacheSound("ambience/wind2.wav");

    //
    S_StopAllSounds(true);
}

// =======================================================================
// Shutdown sound engine
// =======================================================================

void S_Shutdown(void)
{

    if (!sound_started)
        return;
#if WIN32
	if (shm)
		shm->gamealive = 0;

	shm = 0;
	sound_started = 0;

	if (!fakedma)
	{
		SNDDMA_Shutdown();
	}
#endif
}

// =======================================================================
// Load a sound
// =======================================================================

/*
 ==================
 S_FindName

 ==================
 */
sfx_t* S_FindName(char *name)
{
    int i;
    sfx_t *sfx;

    if (!name)
        Sys_Error("S_FindName: NULL\n");

    if (Q_strlen(name) >= MAX_QPATH)
        Sys_Error("Sound name too long: %s", name);

// see if already loaded
    for (i = 0; i < num_sfx; i++)
        if (!Q_strcmp(known_sfx[i].name, name))
        {
            return &known_sfx[i];
        }

    if (num_sfx == MAX_SFX)
        Sys_Error("S_FindName: out of sfx_t");

    sfx = &known_sfx[i];
    strcpy(sfx->name, name);

    num_sfx++;

    return sfx;
}

/*
 ==================
 S_TouchSound

 ==================
 */
void S_TouchSound(char *name)
{

    if (!sound_started)
        return;

    S_FindName(name);
}

/*
 ==================
 S_PrecacheSound

 ==================
 */
sfx_t* S_PrecacheSound(char *name)
{
    sfx_t *sfx;
#define LOAD_SOUNDS_ANYWAY 1
#if !LOAD_SOUNDS_ANYWAY
	if (!sound_started || nosound)
		return NULL;
#endif
    sfx = S_FindName(name);

// cache it in
    if (precache)
        S_LoadSound(sfx);

    return sfx;
}

//=============================================================================

/*
 =================
 SND_PickChannel
 =================
 */
channel_t* SND_PickChannel(int entnum, int entchannel)
{
    // printf("entnum is %d, entchannel is %d\r\n", entnum, entchannel);
    int ch_idx;
    int first_to_die;
    int life_left;

// Check for replacement sound, or find the best one to replace
    first_to_die = -1;
    life_left = 0x7fffffff;
    for (ch_idx = NUM_AMBIENTS; ch_idx < NUM_AMBIENTS + MAX_DYNAMIC_CHANNELS; ch_idx++)
    {
        if (entchannel != 0		// channel 0 never overrides
        && channels[ch_idx].entnum == entnum && (channels[ch_idx].entchannel == entchannel || entchannel == -1))
        {	// always override sound from same entity
            first_to_die = ch_idx;
            break;
        }

        // don't let monster sounds override player sounds
        if (channels[ch_idx].entnum == _g->cl.viewentity && entnum != _g->cl.viewentity && channels[ch_idx].sfxnum)
        {
            continue;
        }
#if WIN32
		if (channels[ch_idx].end - paintedtime < life_left)
		{
			life_left = channels[ch_idx].end - paintedtime;
			first_to_die = ch_idx;
		}
#else
        if (!channels[ch_idx].sfxnum)
        {
            first_to_die = ch_idx;
            life_left = 0;
            if (entchannel == 0)
              break;  //next-hack: no break now if channel != 0. Because we might want to override a looping sound.
        }
        else if ((known_sfx[channels[ch_idx].sfxnum - 1].length - channels[ch_idx].pos < life_left))
        {

            life_left = known_sfx[channels[ch_idx].sfxnum - 1].length - channels[ch_idx].pos;
            first_to_die = ch_idx;
        }

#endif
    }

    if (first_to_die == -1)
    {
        return NULL;
    }

    if (channels[first_to_die].sfxnum)
        channels[first_to_die].sfxnum = 0;

    return &channels[first_to_die];
}

/*
 =================
 SND_Spatialize
 =================
 */
void SND_Spatialize(channel_t *ch)
{
    vec_t dot;
    vec_t dist;
    vec_t lscale, rscale, scale;
    vec3_t source_vec;
#if WIN32
    if (!shm)
        return;
#endif
// anything coming from the view entity will always be full volume
    if (ch->entnum == _g->cl.viewentity)
    {
        ch->leftvol = ch->master_vol;
        ch->rightvol = ch->master_vol;
        return;
    }

// calculate stereo seperation and distance attenuation

    VectorSubtract(ch->origin_s, listener_origin, source_vec);
    /*  printf("Listener origin: %f %f %f, ch origin %d %d %d, distv: %f %f %f, distmult: %f\r\n",
     listener_origin[0], listener_origin[1], listener_origin[1], ch->origin_s[0], ch->origin_s[1], ch->origin_s[2],
     source_vec[0], source_vec[1], source_vec[2],  ch->dist_mult);*/
#if SOUND_CHANNEL_HAS_FLOAT_DIST
	dist = VectorNormalize(source_vec) * ch->dist_mult;
#else
    dist = VectorNormalize(source_vec) * (ch->frac_dist_mult * (1.0f / CHANNEL_DIST_MULT_PRECISION));
#endif

    dot = DotProduct(listener_right, source_vec);
#if WIN32
	if (shm->channels == 1)
	{
        FIXME("ONLY ONE CHANNEL\r\n");
		rscale = 1.0f;
		lscale = 1.0f;
	}
	else
#endif
    {
        rscale = 1.0f + dot;
        lscale = 1.0f - dot;
    }

// add in distance effect
    scale = (1.0f - dist) * rscale;
    if (scale < 0)
        ch->rightvol = 0;
    else
        ch->rightvol = (int) (ch->master_vol * scale);
    scale = (1.0f - dist) * lscale;
    if (scale < 0)
        ch->leftvol = 0;
    else
        ch->leftvol = (int) (ch->master_vol * scale);
}

// =======================================================================
// Start a sound effect
// =======================================================================

void S_StartSound(int entnum, int entchannel, sfx_t *sfx, vec3_t origin, float fvol, float attenuation)
{
    int sfxnum;

    // printf("Start sound entnum %d, entchannel %d, sfxnum %d, x %f, y %f, z %f, vol %f, atten %f\r\n",
    //        entnum, entchannel, sfxnum, origin[0], origin[1], origin[2], fvol, attenuation );
    channel_t *target_chan;
//	sfxcache_t	*sc;
    int vol;

    if (!sound_started)
        return;

    if (!sfx)
        return;

    if (nosound)
        return;

    vol = fvol * 255;
    //
    sfxnum = (sfx - known_sfx) + 1;
// pick a channel to play on
    target_chan = SND_PickChannel(entnum, entchannel);
    if (!target_chan)
    {
        return;
    }
// spatialize
    fastMemclear32(target_chan, sizeof(*target_chan) / 4);
    VectorCopy(origin, target_chan->origin_s);
#if SOUND_CHANNEL_HAS_FLOAT_DIST
	target_chan->dist_mult = attenuation / sound_nominal_clip_dist;
#else
    target_chan->frac_dist_mult = CHANNEL_DIST_MULT_PRECISION * attenuation / sound_nominal_clip_dist;

#endif
    target_chan->master_vol = vol;
    target_chan->entnum = entnum;
    target_chan->entchannel = entchannel;
    SND_Spatialize(target_chan);

    if (!target_chan->leftvol && !target_chan->rightvol)
        return;		// not audible at all
        /*
         // new channel
         S_LoadSound (sfx);
         if (!sc)
         {
         target_chan->sfx = NULL;
         return;		// couldn't load the sound's data
         }
         */
    target_chan->sfxnum = sfxnum;
#if WIN32
	target_chan->pos = 0.0;
    target_chan->end = paintedtime + known_sfx[sfxnum - 1].length;
#else
    target_chan->pos = 0;
    target_chan->lastAudioBufferIdx = -1;
#endif
// if an identical sound has also been started this frame, offset the pos
// a bit to keep it from just making the first one louder
#if ADD_OFFSET_TO_IDENTICAL_SOUNDS
	check = &channels[NUM_AMBIENTS];
    for (ch_idx=NUM_AMBIENTS ; ch_idx < NUM_AMBIENTS + MAX_DYNAMIC_CHANNELS ; ch_idx++, check++)
    {
		if (check == target_chan)
			continue;
		if (check->sfxnum == sfxnum && !check->pos)
		{
			skip = rand () % (int)(0.1*shm->speed);
			if (skip >= target_chan->end)
				skip = target_chan->end - 1;
			target_chan->pos += skip;
			target_chan->end -= skip;
			break;
		}

	}
#endif
}

void S_StopSound(int entnum, int entchannel)
{
    int i;
    /*	if (entchannel > 7)
     __ASM volatile ("BKPT");*/
    for (i = 0; i < MAX_DYNAMIC_CHANNELS; i++)
    {
        if (channels[i].entnum == entnum && channels[i].entchannel == entchannel)
        {
#if WIN32
			channels[i].end = 0;
#endif
            channels[i].sfxnum = 0;
            return;
        }
    }
}

void S_StopAllSounds(qboolean clear)
{
    int i;
    total_channels = MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS;	// no statics. next-hack: put here, was after check
    if (!sound_started)
        return;

    for (i = 0; i < MAX_CHANNELS; i++)
        if (channels[i].sfxnum)
            channels[i].sfxnum = 0;

    Q_memset(channels, 0, MAX_CHANNELS * sizeof(channel_t));

    if (clear)
        S_ClearBuffer();
}

void S_StopAllSoundsC(void)
{
    S_StopAllSounds(true);
}

void S_ClearBuffer(void)
{
#if WIN32
	int		clear;

#ifdef _WIN32_NO_SDL
	if (!sound_started || !shm || (!shm->buffer && !pDSBuf))
    {
		return;

    }
#else
	if (!sound_started || !shm || !shm->buffer)
    {
        FIXME("ERROR");
		return;
    }
#endif

	if (shm->samplebits == 8)
		clear = 0x80;
	else
		clear = 0;

#ifdef _WIN32_NO_SDL
#error
    FIXME("CLEARBUFFER");
	if (pDSBuf)
	{
		DWORD	dwSize;
		DWORD	*pData;
		int		reps;
		HRESULT	hresult;

		reps = 0;

		while ((hresult = pDSBuf->lpVtbl->Lock(pDSBuf, 0, gSndBufSize, &pData, &dwSize, NULL, NULL, 0)) != DS_OK)
		{
			if (hresult != DSERR_BUFFERLOST)
			{
				Con_Printf ("S_ClearBuffer: DS::Lock Sound Buffer Failed\n");
				S_Shutdown ();
				return;
			}

			if (++reps > 10000)
			{
				Con_Printf ("S_ClearBuffer: DS: couldn't restore buffer\n");
				S_Shutdown ();
				return;
			}
		}

		Q_memset(pData, clear, shm->samples * shm->samplebits/8);

		pDSBuf->lpVtbl->Unlock(pDSBuf, pData, dwSize, NULL, 0);

	}
	else
#endif
	{
		Q_memset(shm->buffer, clear, shm->samples * shm->samplebits/8);
	}
#else
    Q_memset(audioBuffer, 0x80, sizeof(audioBuffer));
#endif
}

/*
 =================
 S_StaticSound
 =================
 */
void S_StaticSound(int sfxnum, vec3_t origin, float vol, float attenuation)
{
    channel_t *ss;
    static int outOfChannels = 0;
//	sfxcache_t		*sc;
    if (sfxnum == 0)
    {
        return;
    }
    //
    sfx_t *sfx = &known_sfx[sfxnum - 1];
    if (!sfx->initialized)
    {
        return;
    }
    if (total_channels == MAX_CHANNELS)
    {
        outOfChannels++;
        printf("total_channels == MAX_CHANNELS, need %d more\n", outOfChannels);
        return;
    }

    ss = &channels[total_channels];
    total_channels++;

    if (sfx->loopstart == -1)
    {
        Con_Printf("Sound %s not looped\n", sfx->name);
        return;
    }

    ss->sfxnum = sfxnum;
    VectorCopy(origin, ss->origin_s);
    ss->master_vol = vol;
#if SOUND_CHANNEL_HAS_FLOAT_DIST
	ss->dist_mult = (attenuation/64) / sound_nominal_clip_dist;
#else
    ss->frac_dist_mult = CHANNEL_DIST_MULT_PRECISION * (attenuation / 64) / sound_nominal_clip_dist;
#endif // SOUND_CHANNEL_HAS_FLOAT_DIST
#if WIN32
    ss->end = paintedtime + sfx->length;
#else
    ss->pos = 0;
    ss->lastAudioBufferIdx = -1;
#endif
    SND_Spatialize(ss);
}

//=============================================================================

/*
 ===================
 S_UpdateAmbientSounds
 ===================
 */
void S_UpdateAmbientSounds(void)
{
    mleaf_t *l;
    float vol;
    int ambient_channel;
    channel_t *chan;

    if (!snd_ambient)
    {
        return;
    }

// calc ambient sound levels
    if (!_g->cl.worldmodel)
    {
        return;
    }

    l = Mod_PointInLeaf(listener_origin, _g->cl.worldmodel);
    if (!l || !ambient_level)
    {
        for (ambient_channel = 0; ambient_channel < NUM_AMBIENTS; ambient_channel++)
        {
            channels[ambient_channel].sfxnum = 0;
        }
        return;
    }

    for (ambient_channel = 0; ambient_channel < NUM_AMBIENTS; ambient_channel++)
    {
        //
        chan = &channels[ambient_channel];
        if (ambient_sfx[ambient_channel])
            chan->sfxnum = ambient_sfx[ambient_channel] - &known_sfx[0] + 1;
        else
        {
            chan->sfxnum = 0;
            chan->leftvol = chan->rightvol = chan->master_vol = 0;
            continue;
        }
        vol = ambient_level * l->ambient_sound_level[ambient_channel];
        if (vol < 8)
            vol = 0;

        // don't adjust volume too fast
        if (chan->master_vol < vol)
        {
            int newVol = chan->master_vol + host_frametime * ambient_fade;
            if (newVol > vol)
                chan->master_vol = vol;
            else
                chan->master_vol = newVol;
        }
        else if (chan->master_vol > vol)
        {
            int newVol = chan->master_vol - host_frametime * ambient_fade;
            if (newVol < vol)
                chan->master_vol = vol;
            else
                chan->master_vol = newVol;
        }

        chan->leftvol = chan->rightvol = chan->master_vol;
    }
}

/*
 ============
 S_Update

 Called once each time through the main loop
 ============
 */
void S_Update(vec3_t origin, vec3_t forward, vec3_t right, vec3_t up)
{
    int i, j;
    channel_t *ch;
    channel_t *combine;

    if (!sound_started || (snd_blocked > 0))
        return;
    VectorCopy(origin, listener_origin);
    VectorCopy(right, listener_right);
#if 0
    VectorCopy(forward, listener_forward);
    VectorCopy(up, listener_up);
#else
    (void) forward;
    (void) up;
#endif
// update general area ambient sound sources
    S_UpdateAmbientSounds();

    combine = NULL;

// update spatialization for static and dynamic sounds
    ch = channels + NUM_AMBIENTS;
    for (i = NUM_AMBIENTS; i < total_channels; i++, ch++)
    {
        if (!ch->sfxnum)
            continue;
        SND_Spatialize(ch);         // respatialize channel
        if (!ch->leftvol && !ch->rightvol)
            continue;

        // try to combine static sounds with a previous channel of the same
        // sound effect so we don't mix five torches every frame

        if (i >= MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS)
        {
            // see if it can just use the last one
            if (combine && combine->sfxnum == ch->sfxnum)
            {
                combine->leftvol += ch->leftvol;
                combine->rightvol += ch->rightvol;
                ch->leftvol = ch->rightvol = 0;
                continue;
            }
            // search for one
            combine = channels + MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS;
            for (j = MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS; j < i; j++, combine++)
                if (combine->sfxnum == ch->sfxnum)
                    break;

            if (j == total_channels)
            {
                combine = NULL;
            }
            else
            {
                if (combine != ch)
                {
                    if (combine->leftvol + ch->leftvol < 255)
                        combine->leftvol += ch->leftvol;
                    else
                        ch->leftvol = 255;
                    if (combine->rightvol + ch->rightvol < 255)
                        combine->rightvol += ch->rightvol;
                    else
                        combine->rightvol = 255;
                    ch->leftvol = ch->rightvol = 0;
                }
                continue;
            }
        }

    }

//
// debugging output
//
#if 0
	if (1 || snd_show)
	{
		total = 0;
		ch = channels;
		for (i=0 ; i<total_channels; i++, ch++)
			if (ch->sfxnum && (ch->leftvol || ch->rightvol) )
			{
				//Con_Printf ("%3i %3i %s\n", ch->leftvol, ch->rightvol, ch->sfx->name);
				total++;
			}

		Con_Printf ("----(%i)----\n", total);
	}
#endif

// mix some sound
    S_Update_();
}
#if WIN32
void GetSoundtime(void)
{
	int		samplepos;
	static	int		buffers;
	static	int		oldsamplepos;
	int		fullsamples;
#if WIN32
	fullsamples = shm->samples / shm->channels;
#else
	fullsamples = AUDIO_BUFFER_LENGTH;
#endif
// it is possible to miscount buffers if it has wrapped twice between
// calls to S_Update.  Oh well.
	samplepos = SNDDMA_GetDMAPos();


	if (samplepos < oldsamplepos)
	{
		buffers++;					// buffer wrapped

		if (paintedtime > 0x40000000)
		{	// time to chop things off to avoid 32 bit limits
			buffers = 0;
			paintedtime = fullsamples;
			S_StopAllSounds (true);
		}
	}
	oldsamplepos = samplepos;
#if WIN32
	soundtime = buffers * fullsamples + samplepos/shm->channels;
#else
  soundtime = buffers * fullsamples + samplepos;
#endif
}

void S_ExtraUpdate (void)
{
#if ENABLE_EXTRA_UPDAE
#ifdef _WIN32_NO_SDL
	IN_Accumulate ();
#endif

	if (snd_noextraupdate)
		return;		// don't pollute timings
	S_Update_();
#endif
}

void S_Update_(void)
{

#ifndef SDL
	unsigned        endtime;
	int				samps;

	if (!sound_started || (snd_blocked > 0))
		return;

// Updates DMA time
	GetSoundtime();

// check to make sure that we haven't overshot
	if (paintedtime < soundtime)
	{
		//Con_Printf ("S_Update_ : overflow\n");
		paintedtime = soundtime;
	}

// mix ahead of current position
#if WIN32
	endtime = soundtime + _snd_mixahead * shm->speed;
	samps = shm->samples >> (shm->channels-1);
#else
  endtime = soundtime + (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY);
  //
#endif
	if (endtime - soundtime > samps)
		endtime = soundtime + samps;

	S_PaintChannels (endtime);
#endif
	//SNDDMA_Submit ();

}
#else
void S_ExtraUpdate(void)
{
}
void SND_PaintChannelFrom8(portable_samplepair_t *paintbuffer, channel_t *ch, sfx_t *psfx, int count, int pos);
void S_Update_(void)
{
#if CHECK_SOUND_PERF
  if (host_framecount >= 83)
  {
    __ASM("BKPT");
  }
#endif
    if (M_IsQuitState())     //next-hack. Dirty hack in quit menu which takes too much time.
    {
        S_ClearBuffer();
        return;
    }
    int channelsPainted = 0;
    // where are we in our circular buffer?
    uint32_t currentIdx = ((LDMA->CH[AUDIO_DMA_CHANNEL_L].SRC - (uint32_t) audioBuffer) / sizeof(audioBuffer[0])) / 2;
    // we cannot start updating the audio buffer just on next sample (which will occur in about 90us from now).
    // if frame rate is high enough, then the audio buffer is valid several samples after currentIdx.
    // therefore we can start updating the audio buffer AUDIO_BUFFER_DELAY samples after the current one.
    // AUDIO_BUFFER_DELAY must be chosen so that we have enough time to read the sample data from all the lumps
    // and store to the buffer. This might take some time.
    // The index at which we recalculate/update audio samples is startIdx.
    // The buffer is recalculated from startIdx up to the sample before currentIdx
    // As first thing, zeroize buffer;
    // Note that we do not have to end exactly at current index.

    uint32_t startIdx = (currentIdx + AUDIO_BUFFER_DELAY) & (AUDIO_BUFFER_LENGTH - 1);
    //
    portable_samplepair_t paintbuffer[AUDIO_BUFFER_LENGTH]; // next-hack: in stack because snd update is done when small amount in stack is used
    // clear paint buffer
    fastMemclear32(paintbuffer, sizeof(paintbuffer) / 4);
    //
    channel_t *ch = channels;
    // Now, for each channel we need to copy sample data.
    for (int i = 0; i < total_channels; i++, ch++)
    {
        // channel active?
        if (!ch->sfxnum)
        {
            continue;
        }
        if (!ch->leftvol && !ch->rightvol)
        {
            continue;
        }
        //
        sfx_t *sfx = &known_sfx[ch->sfxnum - 1];

        uint32_t samplesPlayed;
        // is this a new sample (not played before? Then do not change the offset
        if (ch->lastAudioBufferIdx != -1)
        {
            // otherwise, we need to calculate how many sample do we have played since last call.
            // considering also that we are starting at startIdx.
            samplesPlayed = (startIdx - ch->lastAudioBufferIdx) & (AUDIO_BUFFER_LENGTH - 1);
            ch->pos += samplesPlayed;
            if (sfx->loopstart != -1 && ch->pos > sfx->loopstart)
            {
                // adjust position in loop
                ch->pos = sfx->loopstart + (ch->pos - sfx->loopstart) % (sfx->length - sfx->loopstart);
            }
        }
        // remember last index.
        ch->lastAudioBufferIdx = startIdx;
        // how many bytes do we need to read?
        // get sample size
        int32_t sfxSize = sfx->length;

        // read through the end of the samples
        int32_t sizeToRead = sfxSize - ch->pos;
        int pos = 0;
        if (sizeToRead <= 0) // already outputted all samples?
        {
            // no loop? zeroize sfxnum
            if (sfx->loopstart == -1)
            {
                ch->sfxnum = 0;
                continue;
            }
#if PEDANTIC_ERROR_CHECK
            else
            {
                __ASM volatile ("BKPT");
                // should not occur!
                // loop: set offset from loopstart. FIXME: is a difference enough?
                // FIXME: is it necessary ?
                pos = sfx->loopstart + (ch->pos - sfx->loopstart) % (sfx->length - sfx->loopstart);
                sizeToRead = sfxSize - pos;
            }
#endif
        }
        else
        {
            pos = ch->pos;
        }
        // if the number of samples to read exceed the size of the buffer we need to update
        // then crop it
        if (sizeToRead > (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY))
        {
            sizeToRead = (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY);
        }
        // sizeToRead is for sure strictly positive.
        if (channelsPainted < MAX_CONCURRENT_CHANNELS)
        {
            SND_PaintChannelFrom8(paintbuffer, ch, sfx, sizeToRead, pos);
            //
            if ((sizeToRead < (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY)) && sfx->loopstart != -1)
            {
                // this is because the previous read up to end of the sample
                int remaining = (AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY) - sizeToRead;
                /*        if (pos + sizeToRead + remaining > sfx->length)
                 {
                 printf("Pos: %d, chpos %d, sr %d rem %d len %d ls %d", pos, ch->pos, sizeToRead, remaining, sfx->length, sfx->loopstart);
                 __ASM volatile("BKPT");
                 }*/
                // FIXME: what about samples with short loop?
                SND_PaintChannelFrom8(&paintbuffer[sizeToRead], ch, sfx, remaining, sfx->loopstart);
            }
            channelsPainted++;
        }
    }
    // copy to audio buffer
    uint32_t stopIdx = (startIdx + AUDIO_BUFFER_LENGTH - AUDIO_BUFFER_DELAY) & (AUDIO_BUFFER_LENGTH - 1);

    int *p = (int*) paintbuffer;
    //
    int snd_vol = volume * 256;
    //

    unsigned short *out = (unsigned short*) audioBuffer;
    int val;
    for (uint32_t i = startIdx; i != stopIdx; i = (i + 1) & (AUDIO_BUFFER_LENGTH - 1))
    {
        // update audio buffer
        val = (*p++ * snd_vol) >> 8;
        __ASM volatile ("ssat %0, %1, %2" : "=r" (val) : "I" (16), "r" (val) : "cc" );

#if NOSAT
     if (val > 0x7fff)
      val = 0x7fff;
    else if (val < (short)0x8000)
      val = (short)0x8000;
#endif

        unsigned char v0 = ((val >> 8) + 128);
//    out[i * 2] = (val>>8) + 128;
        val = (*p++ * snd_vol) >> 8;
        __ASM volatile ("ssat %0, %1, %2" : "=r" (val) : "I" (16), "r" (val) : "cc" );
#if NOSAT
    if (val > 0x7fff)
        val = 0x7fff;
    else if (val < (short)0x8000)
      val = (short)0x8000;
     out[i * 2 + 1] = (val>>8) + 128;
#endif
        unsigned char v1 = ((val >> 8) + 128);
        out[i] = (v1 << 8) | v0;
    }
#if CHECK_SOUND_PERF
  if (host_framecount >= 83)
  {
    __ASM("BKPT");
  }
#endif

}
#endif
/*
 ===============================================================================

 console functions

 ===============================================================================
 */
void S_Play(void)
{
#if WIN32
    static int hash = 345;
    int i;
    char name[256];
    sfx_t *sfx;

    i = 1;
    while (i < Cmd_Argc())
    {
        if (!Q_strrchr(Cmd_Argv(i), '.'))
        {
            Q_strcpy(name, Cmd_Argv(i));
            Q_strcat(name, ".wav");
        }
        else
            Q_strcpy(name, Cmd_Argv(i));
        sfx = S_PrecacheSound(name);
        S_StartSound(hash++, 0, sfx, listener_origin, 1.0, 1.0);
        i++;
    }
#endif
}
void S_PlayVol(void)
{
#if WIN32
    static int hash = 543;
    int i;
    float vol;
    char name[256];
    sfx_t *sfx;

    i = 1;
    while (i < Cmd_Argc())
    {
        if (!Q_strrchr(Cmd_Argv(i), '.'))
        {
            Q_strcpy(name, Cmd_Argv(i));
            Q_strcat(name, ".wav");
        }
        else
            Q_strcpy(name, Cmd_Argv(i));
        sfx = S_PrecacheSound(name);
        vol = Q_atof(Cmd_Argv(i + 1));
        S_StartSound(hash++, 0, sfx, listener_origin, vol, 1.0);
        i += 2;
    }
#endif
}

void S_SoundList(void)
{
    int i;
    sfx_t *sfx;
//	sfxcache_t	*sc;
    int size, total;

    total = 0;
    for (sfx = known_sfx, i = 0; i < num_sfx; i++, sfx++)
    {
//		sc = Cache_Check (&sfx->cache);
//		if (!sc)
//			continue;
        size = sfx->length;    //*sfx->width;//*(sc->stereo+1);
        total += size;
        if (sfx->loopstart >= 0)
            Con_Printf("L");
        else
            Con_Printf(" ");
        Con_Printf(" %6i : %s\n", size, sfx->name);
    }
    Con_Printf("Total resident: %i\n", total);
}

void S_LocalSound(char *sound)
{
    sfx_t *sfx;

    if (nosound)
        return;
    if (!sound_started)
        return;

    sfx = S_PrecacheSound(sound);
    if (!sfx)
    {
        Con_Printf("S_LocalSound: can't cache %s\n", sound);
        return;
    }
    S_StartSound(_g->cl.viewentity, -1, sfx, vec3_origin, 1, 1);
}

void S_ClearPrecache(void)
{
}

void S_BeginPrecaching(void)
{
}

void S_EndPrecaching(void)
{
}
#else
#include "quakedef.h"

#ifdef _WIN32_NO_SDL
#include "winquake.h"
#endif

void S_Play(void);
void S_PlayVol(void);
void S_SoundList(void);
void S_Update_();
void S_StopAllSounds(qboolean clear);
void S_StopAllSoundsC(void);

// =======================================================================
// Internal sound data & structures
// =======================================================================

AUX_SECTION channel_t   channels[MAX_CHANNELS];
int			total_channels;

int				snd_blocked = 0;
static qboolean	snd_ambient = 1;
qboolean		snd_initialized = false;

// pointer should go away
volatile dma_t  *shm = 0;
volatile dma_t sn;

vec3_t		listener_origin;
vec3_t		listener_forward;
vec3_t		listener_right;
vec3_t		listener_up;
const vec_t		sound_nominal_clip_dist = 1000.0f;

int			soundtime;		// sample PAIRS
int   		paintedtime; 	// sample PAIRS
sfx_t		*known_sfx;		// hunk allocated [MAX_SFX]
int			num_sfx;

sfx_t		*ambient_sfx[NUM_AMBIENTS];

const int 		desired_speed = 11025;
const int 		desired_bits = 8;

int sound_started=0;

#if USE_ORIGINAL_CVAR
cvar_t bgmvolume = {"bgmvolume", "1", true};
cvar_t volume = {"volume", "0.7", true};

cvar_t nosound = {"nosound", "0"};
cvar_t precache = {"precache", "1"};
cvar_t loadas8bit = {"loadas8bit", "0"};
cvar_t bgmbuffer = {"bgmbuffer", "4096"};
cvar_t ambient_level = {"ambient_level", "0.3"};
cvar_t ambient_fade = {"ambient_fade", "100"};
cvar_t snd_noextraupdate = {"snd_noextraupdate", "0"};
cvar_t snd_show = {"snd_show", "0"};
cvar_t _snd_mixahead = {"_snd_mixahead", "0.1", true};
#endif

// ====================================================================
// User-setable variables
// ====================================================================


//
// Fake dma is a synchronous faking of the DMA progress used for
// isolating performance in the renderer.  The fakedma_updates is
// number of times S_Update() is called per second.
//

qboolean fakedma = false;
int fakedma_updates = 15;


void S_AmbientOff (void)
{
	snd_ambient = false;
}


void S_AmbientOn (void)
{
	snd_ambient = true;
}


void S_SoundInfo_f(void)
{
	if (!sound_started || !shm)
	{
		Con_Printf ("sound system not started. Total Channels %d\n", total_channels);
		return;
	}

    Con_Printf("%5d stereo\n", shm->channels - 1);
    Con_Printf("%5d samples\n", shm->samples);
    Con_Printf("%5d samplepos\n", shm->samplepos);
    Con_Printf("%5d samplebits\n", shm->samplebits);
    Con_Printf("%5d submission_chunk\n", shm->submission_chunk);
    Con_Printf("%5d speed\n", shm->speed);
    Con_Printf("0x%x dma buffer\n", shm->buffer);
	Con_Printf("%5d total_channels\n", total_channels);
}


/*
================
S_Startup
================
*/

void S_Startup (void)
{
	int		rc;
	if (!snd_initialized)
		return;

	if (!fakedma)
	{
		rc = SNDDMA_Init();

		if (!rc)
		{
#ifdef	_WIN32
			Con_Printf("S_Startup: SNDDMA_Init failed.\n");
			FIXME("error");
#endif
			sound_started = 0;

			return;
		}
	}

	sound_started = 1;
}


/*
================
S_Init
================
*/
void S_Init (void)
{
	Con_Printf("\nSound Initialization\n");

	if (COM_CheckParm("-nosound"))
    {

    		return;

    }

	if (COM_CheckParm("-simsound"))
		fakedma = true;

#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable(&nosound);
	Cvar_RegisterVariable(&volume);
	Cvar_RegisterVariable(&precache);
	Cvar_RegisterVariable(&loadas8bit);
	Cvar_RegisterVariable(&bgmvolume);
	Cvar_RegisterVariable(&bgmbuffer);
	Cvar_RegisterVariable(&ambient_level);
	Cvar_RegisterVariable(&ambient_fade);
	Cvar_RegisterVariable(&snd_noextraupdate);
	Cvar_RegisterVariable(&snd_show);
	Cvar_RegisterVariable(&_snd_mixahead);
#endif
		Cvar_Set ("loadas8bit", "1");
		Con_Printf ("loading all sounds as 8bit\n");
	snd_initialized = true;

	S_Startup ();

	SND_InitScaletable ();

//	known_sfx = Hunk_AllocName (MAX_SFX*sizeof(sfx_t), "sfx_t");

	num_sfx = 0;

// create a piece of DMA memory
#if 0
	if (fakedma)
	{
	    Sys_Error("fake dma");
		//shm = (void *) Hunk_AllocName(sizeof(*shm), "shm");
		shm->splitbuffer = 0;
		shm->samplebits = 8;
		shm->speed = 11025;
		shm->channels = 2;
		shm->samples = 32768;
		shm->samplepos = 0;
		shm->soundalive = true;
		shm->gamealive = true;
		shm->submission_chunk = 1;
//		shm->buffer = Hunk_AllocName(1<<16, "shmbuf");
	}
#endif
	if ( shm ) {
		Con_Printf ("Sound sampling rate: %i\n", shm->speed);
		Con_Printf ("Sound sampling bits: %i\n", shm->samplebits);
	}
	else
    {
        FIXME("ERROR");
    }
	// provides a tick sound until washed clean

//	if (shm->buffer)
//		shm->buffer[4] = shm->buffer[5] = 0x7f;	// force a pop for debugging
    byte sfx_buffer[MAX_SFX * sizeof(sfx_t)] = {0};
    printf("Using %d bytes to temporarily load all sounds in pak\r\n", sizeof(sfx_buffer));
    known_sfx = sfx_buffer;
  //  	known_sfx = Hunk_AllocName (MAX_SFX*sizeof(sfx_t), "sfx_t");
#warning this work only for single pak file!
    int numfile = 0;
    int oldpr = precache;
    precache = 1;
    while (1)
    {
        //FIXME("VVVV");
        dpackfile_t packfile;
        if (!getDPackFile(&packfile, numfile))
            break;      // no more files to load
        if (num_sfx >= MAX_SFX)
            break;
        printf("Pack File Name %d is %s\r\n", numfile, packfile.name);
        const char soundDir[] = "sound/";
        int soundDirNameLength = strlen(soundDir);
        if (strstr(packfile.name, ".wav"))
        {
           printf("Precaching %s as sound number %d\r\n", strstr(packfile.name, "sound/") + soundDirNameLength, num_sfx);
           S_PrecacheSound(strstr(packfile.name, "sound/") + soundDirNameLength);
        }
        numfile++;
    }
    printf("precached: %d sounds. Opr is %d\r\n", num_sfx, oldpr);

    precache = oldpr;
    // now all sounds are there. Save them
    known_sfx = storeToInternalFlash(known_sfx, sizeof(sfx_t) * num_sfx);
    //
    //
     for (int i = 0; i < NUM_AMBIENTS; i++)
	    ambient_sfx[i] = 0;

	ambient_sfx[AMBIENT_WATER] = S_PrecacheSound ("ambience/water1.wav");
	ambient_sfx[AMBIENT_SKY] = S_PrecacheSound ("ambience/wind2.wav");

    //
	S_StopAllSounds (true);
}


// =======================================================================
// Shutdown sound engine
// =======================================================================

void S_Shutdown(void)
{

	if (!sound_started)
		return;

	if (shm)
		shm->gamealive = 0;

	shm = 0;
	sound_started = 0;

	if (!fakedma)
	{
		SNDDMA_Shutdown();
	}
}


// =======================================================================
// Load a sound
// =======================================================================

/*
==================
S_FindName

==================
*/
sfx_t *S_FindName (char *name)
{
	int		i;
	sfx_t	*sfx;

	if (!name)
		Sys_Error ("S_FindName: NULL\n");

	if (Q_strlen(name) >= MAX_QPATH)
		Sys_Error ("Sound name too long: %s", name);

// see if already loaded
	for (i=0 ; i < num_sfx ; i++)
		if (!Q_strcmp(known_sfx[i].name, name))
		{
			return &known_sfx[i];
		}

	if (num_sfx == MAX_SFX)
		Sys_Error ("S_FindName: out of sfx_t");

	sfx = &known_sfx[i];
	strcpy (sfx->name, name);

	num_sfx++;

	return sfx;
}


/*
==================
S_TouchSound

==================
*/
void S_TouchSound (char *name)
{
	sfx_t	*sfx;

	if (!sound_started)
		return;

	sfx = S_FindName (name);
//	Cache_Check (&sfx->cache);
}

/*
==================
S_PrecacheSound

==================
*/
sfx_t *S_PrecacheSound (char *name)
{
	sfx_t	*sfx;
#define LOAD_SOUNDS_ANYWAY 1
#if !LOAD_SOUNDS_ANYWAY
	if (!sound_started || nosound)
		return NULL;
#endif
	sfx = S_FindName (name);

// cache it in
	if (precache)
		S_LoadSound (sfx);

	return sfx;
}


//=============================================================================

/*
=================
SND_PickChannel
=================
*/
channel_t *SND_PickChannel(int entnum, int entchannel)
{
   // printf("entnum is %d, entchannel is %d\r\n", entnum, entchannel);
    int ch_idx;
    int first_to_die;
    int life_left;

// Check for replacement sound, or find the best one to replace
    first_to_die = -1;
    life_left = 0x7fffffff;
    for (ch_idx=NUM_AMBIENTS ; ch_idx < NUM_AMBIENTS + MAX_DYNAMIC_CHANNELS ; ch_idx++)
    {
		if (entchannel != 0		// channel 0 never overrides
		&& channels[ch_idx].entnum == entnum
		&& (channels[ch_idx].entchannel == entchannel || entchannel == -1) )
		{	// always override sound from same entity
			first_to_die = ch_idx;
			break;
		}

		// don't let monster sounds override player sounds
		if (channels[ch_idx].entnum == _g->cl.viewentity && entnum != _g->cl.viewentity && channels[ch_idx].sfxnum )
        {
			continue;
        }
		if (channels[ch_idx].end - paintedtime < life_left)
		{
			life_left = channels[ch_idx].end - paintedtime;
			first_to_die = ch_idx;
		}
   }

	if (first_to_die == -1)
    {
		return NULL;
    }

	if (channels[first_to_die].sfxnum)
		channels[first_to_die].sfxnum = 0;

    return &channels[first_to_die];
}

/*
=================
SND_Spatialize
=================
*/
void SND_Spatialize(channel_t *ch)
{
    vec_t dot;
    vec_t ldist, rdist, dist;
    vec_t lscale, rscale, scale;
    vec3_t source_vec;
	sfx_t *snd;
    if (!shm)
        return;
// anything coming from the view entity will always be full volume
	if (ch->entnum == _g->cl.viewentity)
	{
		ch->leftvol = ch->master_vol;
		ch->rightvol = ch->master_vol;
		return;
	}

// calculate stereo seperation and distance attenuation

	snd = &known_sfx[ch->sfxnum - 1];
	VectorSubtract(ch->origin_s, listener_origin, source_vec);
  /*  printf("Listener origin: %f %f %f, ch origin %d %d %d, distv: %f %f %f, distmult: %f\r\n",
           listener_origin[0], listener_origin[1], listener_origin[1], ch->origin_s[0], ch->origin_s[1], ch->origin_s[2],
           source_vec[0], source_vec[1], source_vec[2],  ch->dist_mult);*/
#if SOUND_CHANNEL_HAS_FLOAT_DIST
	dist = VectorNormalize(source_vec) * ch->dist_mult;
#else
	dist = VectorNormalize(source_vec) * (ch->frac_dist_mult * (1.0f / CHANNEL_DIST_MULT_PRECISION));
#endif

	dot = DotProduct(listener_right, source_vec);

	if (shm->channels == 1)
	{
        FIXME("ONLY ONE CHANNEL\r\n");
		rscale = 1.0f;
		lscale = 1.0f;
	}
	else
	{
		rscale = 1.0f + dot;
		lscale = 1.0f - dot;
	}

// add in distance effect
        scale = (1.0f - dist) * rscale;
        if (scale < 0)
    		ch->rightvol = 0;
        else
            ch->rightvol = (int) (ch->master_vol * scale);
        scale = (1.0f - dist) * lscale;
        if (scale < 0)
            		ch->leftvol = 0;
        else
           ch->leftvol = (int) (ch->master_vol * scale);


}


// =======================================================================
// Start a sound effect
// =======================================================================

void S_StartSound(int entnum, int entchannel, sfx_t *sfx, vec3_t origin, float fvol, float attenuation)
{
    int sfxnum;
    if (sfx == NULL)
        sfxnum = 0;
    else
        sfxnum = (sfx - known_sfx) + 1;
   // printf("Start sound entnum %d, entchannel %d, sfxnum %d, x %f, y %f, z %f, vol %f, atten %f\r\n",
   //        entnum, entchannel, sfxnum, origin[0], origin[1], origin[2], fvol, attenuation );
	channel_t *target_chan, *check;
//	sfxcache_t	*sc;
	int		vol;
	int		ch_idx;
	int		skip;

	if (!sound_started)
		return;

	if (!sfxnum)
		return;

	if (nosound)
		return;

	vol = fvol*255;

// pick a channel to play on
	target_chan = SND_PickChannel(entnum, entchannel);
	if (!target_chan)
    {
		return;
    }
// spatialize
	memset (target_chan, 0, sizeof(*target_chan));
	VectorCopy(origin, target_chan->origin_s);
#if SOUND_CHANNEL_HAS_FLOAT_DIST
	target_chan->dist_mult = attenuation / sound_nominal_clip_dist;
#else
	target_chan->frac_dist_mult = CHANNEL_DIST_MULT_PRECISION * attenuation / sound_nominal_clip_dist;

#endif
	target_chan->master_vol = vol;
	target_chan->entnum = entnum;
	target_chan->entchannel = entchannel;
	SND_Spatialize(target_chan);

	if (!target_chan->leftvol && !target_chan->rightvol)
		return;		// not audible at all
/*
// new channel
	S_LoadSound (sfx);
	if (!sc)
	{
		target_chan->sfx = NULL;
		return;		// couldn't load the sound's data
	}
*/
	target_chan->sfxnum = sfxnum;
	target_chan->pos = 0.0;
    target_chan->end = paintedtime + known_sfx[sfxnum - 1].length;

// if an identical sound has also been started this frame, offset the pos
// a bit to keep it from just making the first one louder
#if ADD_OFFSET_TO_IDENTICAL_SOUNDS
	check = &channels[NUM_AMBIENTS];
    for (ch_idx=NUM_AMBIENTS ; ch_idx < NUM_AMBIENTS + MAX_DYNAMIC_CHANNELS ; ch_idx++, check++)
    {
		if (check == target_chan)
			continue;
		if (check->sfxnum == sfxnum && !check->pos)
		{
			skip = rand () % (int)(0.1*shm->speed);
			if (skip >= target_chan->end)
				skip = target_chan->end - 1;
			target_chan->pos += skip;
			target_chan->end -= skip;
			break;
		}
	}
#endif
}

void S_StopSound(int entnum, int entchannel)
{
	int i;

	for (i=0 ; i<MAX_DYNAMIC_CHANNELS ; i++)
	{
		if (channels[i].entnum == entnum
			&& channels[i].entchannel == entchannel)
		{
			channels[i].end = 0;
			channels[i].sfxnum = 0;
			return;
		}
	}
}

void S_StopAllSounds(qboolean clear)
{
	int		i;
	total_channels = MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS;	// no statics. next-hack: put here, was after check
	if (!sound_started)
		return;


	for (i=0 ; i<MAX_CHANNELS ; i++)
		if (channels[i].sfxnum)
			channels[i].sfxnum = 0;

	Q_memset(channels, 0, MAX_CHANNELS * sizeof(channel_t));

	if (clear)
		S_ClearBuffer ();
}

void S_StopAllSoundsC (void)
{
	S_StopAllSounds (true);
}

void S_ClearBuffer (void)
{
	int		clear;

#ifdef _WIN32_NO_SDL

	if (!sound_started || !shm || (!shm->buffer && !pDSBuf))
    {
		return;

    }
#else
	if (!sound_started || !shm || !shm->buffer)
    {
        FIXME("ERROR");
		return;
    }
#endif

	if (shm->samplebits == 8)
		clear = 0x80;
	else
		clear = 0;

#ifdef _WIN32_NO_SDL
#error
    FIXME("CLEARBUFFER");
	if (pDSBuf)
	{
		DWORD	dwSize;
		DWORD	*pData;
		int		reps;
		HRESULT	hresult;

		reps = 0;

		while ((hresult = pDSBuf->lpVtbl->Lock(pDSBuf, 0, gSndBufSize, &pData, &dwSize, NULL, NULL, 0)) != DS_OK)
		{
			if (hresult != DSERR_BUFFERLOST)
			{
				Con_Printf ("S_ClearBuffer: DS::Lock Sound Buffer Failed\n");
				S_Shutdown ();
				return;
			}

			if (++reps > 10000)
			{
				Con_Printf ("S_ClearBuffer: DS: couldn't restore buffer\n");
				S_Shutdown ();
				return;
			}
		}

		Q_memset(pData, clear, shm->samples * shm->samplebits/8);

		pDSBuf->lpVtbl->Unlock(pDSBuf, pData, dwSize, NULL, 0);

	}
	else
#endif
	{
		Q_memset(shm->buffer, clear, shm->samples * shm->samplebits/8);
	}
}


/*
=================
S_StaticSound
=================
*/
void S_StaticSound (int sfxnum, vec3_t origin, float vol, float attenuation)
{

	channel_t	*ss;
	static int outOfChannels = 0;
//	sfxcache_t		*sc;

    if (sfxnum == 0)
    {

            FIXME("error");
            return;

    }

    sfx_t *sfx = &known_sfx[sfxnum - 1];
    if (!sfx->initialized)
        return;
	if (total_channels == MAX_CHANNELS)
	{
	    outOfChannels++;
		printf ("total_channels == MAX_CHANNELS, need %d more\n",outOfChannels);
		return;
	}

	ss = &channels[total_channels];
	total_channels++;

/*	sc = S_LoadSound (sfx);
	if (!sc)
		return;
*/
	if (sfx->loopstart == -1)
	{
		Con_Printf ("Sound %s not looped\n", sfx->name);
		return;
	}

	ss->sfxnum = sfxnum;
	VectorCopy (origin, ss->origin_s);
	ss->master_vol = vol;
#if SOUND_CHANNEL_HAS_FLOAT_DIST
    ss->dist_mult = (attenuation/64) / sound_nominal_clip_dist;
#else
    ss->frac_dist_mult = (attenuation/64) / sound_nominal_clip_dist * CHANNEL_DIST_MULT_PRECISION;
#endif // SOUND_CHANNEL_HAS_FLOAT_DIST

    ss->end = paintedtime + sfx->length;

	SND_Spatialize (ss);
}


//=============================================================================

/*
===================
S_UpdateAmbientSounds
===================
*/
void S_UpdateAmbientSounds (void)
{
	mleaf_t		*l;
	float		vol;
	int			ambient_channel;
	channel_t	*chan;

	if (!snd_ambient)
    {
		return;
    }

// calc ambient sound levels
	if (!_g->cl.worldmodel)
    {
		return;
    }

	l = Mod_PointInLeaf (listener_origin, _g->cl.worldmodel);
	if (!l || !ambient_level)
	{
		for (ambient_channel = 0 ; ambient_channel< NUM_AMBIENTS ; ambient_channel++)
        {
			channels[ambient_channel].sfxnum = 0;
        }
 		return;
	}
//    printf("AS: %d %d %d %d\r\n",l->ambient_sound_level[0], l->ambient_sound_level[1], l->ambient_sound_level[2], l->ambient_sound_level[3]);

	for (ambient_channel = 0 ; ambient_channel< NUM_AMBIENTS ; ambient_channel++)
	{
	   //
		chan = &channels[ambient_channel];
		chan->sfxnum = ambient_sfx[ambient_channel] - &known_sfx[0] + 1;
	//	if (ambient_sfx[ambient_channel])
    //		printf("Ambient Ch %d sfx name: %s\r\n", ambient_channel, ambient_sfx[ambient_channel]->name);
		vol = ambient_level * l->ambient_sound_level[ambient_channel];
		if (vol < 8)
			vol = 0;

	// don't adjust volume too fast
		if (chan->master_vol < vol)
		{
			chan->master_vol += host_frametime * ambient_fade;
			if (chan->master_vol > vol)
				chan->master_vol = vol;
		}
		else if (chan->master_vol > vol)
		{
			chan->master_vol -= host_frametime * ambient_fade;
			if (chan->master_vol < vol)
				chan->master_vol = vol;
		}

		chan->leftvol = chan->rightvol = chan->master_vol;
	}
}


/*
============
S_Update

Called once each time through the main loop
============
*/
void S_Update(vec3_t origin, vec3_t forward, vec3_t right, vec3_t up)
{
	int			i, j;
	int			total;
	channel_t	*ch;
	channel_t	*combine;

	if (!sound_started || (snd_blocked > 0))
		return;

	VectorCopy(origin, listener_origin);
	VectorCopy(right, listener_right);
#if 0
    VectorCopy(forward, listener_forward);
	VectorCopy(up, listener_up);
#endif
// update general area ambient sound sources
	S_UpdateAmbientSounds ();

	combine = NULL;

// update spatialization for static and dynamic sounds
	ch = channels+NUM_AMBIENTS;
	for (i=NUM_AMBIENTS ; i<total_channels; i++, ch++)
	{
		if (!ch->sfxnum)
			continue;
		SND_Spatialize(ch);         // respatialize channel
		if (!ch->leftvol && !ch->rightvol)
			continue;

	// try to combine static sounds with a previous channel of the same
	// sound effect so we don't mix five torches every frame

		if (i >= MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS)
		{
		// see if it can just use the last one
			if (combine && combine->sfxnum == ch->sfxnum)
			{
				combine->leftvol += ch->leftvol;
				combine->rightvol += ch->rightvol;
				ch->leftvol = ch->rightvol = 0;
				continue;
			}
		// search for one
			combine = channels+MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS;
			for (j=MAX_DYNAMIC_CHANNELS + NUM_AMBIENTS ; j<i; j++, combine++)
				if (combine->sfxnum == ch->sfxnum)
					break;

			if (j == total_channels)
			{
				combine = NULL;
			}
			else
			{
				if (combine != ch)
				{
					combine->leftvol += ch->leftvol;
					combine->rightvol += ch->rightvol;
					ch->leftvol = ch->rightvol = 0;
				}
				continue;
			}
		}


	}

//
// debugging output
//
#if 0
	if (1 || snd_show)
	{
		total = 0;
		ch = channels;
		for (i=0 ; i<total_channels; i++, ch++)
			if (ch->sfxnum && (ch->leftvol || ch->rightvol) )
			{
				//Con_Printf ("%3i %3i %s\n", ch->leftvol, ch->rightvol, ch->sfx->name);
				total++;
			}

		Con_Printf ("----(%i)----\n", total);
	}
#endif

// mix some sound
	S_Update_();
}

void GetSoundtime(void)
{
	int		samplepos;
	static	int		buffers;
	static	int		oldsamplepos;
	int		fullsamples;

	fullsamples = shm->samples / shm->channels;

// it is possible to miscount buffers if it has wrapped twice between
// calls to S_Update.  Oh well.
#ifdef __sun__
	soundtime = SNDDMA_GetSamples();
#else
	samplepos = SNDDMA_GetDMAPos();


	if (samplepos < oldsamplepos)
	{
		buffers++;					// buffer wrapped

		if (paintedtime > 0x40000000)
		{	// time to chop things off to avoid 32 bit limits
			buffers = 0;
			paintedtime = fullsamples;
			S_StopAllSounds (true);
		}
	}
	oldsamplepos = samplepos;

	soundtime = buffers*fullsamples + samplepos/shm->channels;
#endif
}

void S_ExtraUpdate (void)
{
#if ENABLE_EXTRA_UPDAE
#ifdef _WIN32_NO_SDL
	IN_Accumulate ();
#endif
	if (snd_noextraupdate)
		return;		// don't pollute timings
	S_Update_();
#endif
}

void S_Update_(void)
{

#ifndef SDL
	unsigned        endtime;
	int				samps;

	if (!sound_started || (snd_blocked > 0))
		return;

// Updates DMA time
	GetSoundtime();

// check to make sure that we haven't overshot
	if (paintedtime < soundtime)
	{
		//Con_Printf ("S_Update_ : overflow\n");
		paintedtime = soundtime;
	}

// mix ahead of current position
	endtime = soundtime + _snd_mixahead * shm->speed;
	samps = shm->samples >> (shm->channels-1);
	if (endtime - soundtime > samps)
		endtime = soundtime + samps;

	S_PaintChannels (endtime);
#endif
	//SNDDMA_Submit ();

}

/*
===============================================================================

console functions

===============================================================================
*/
void S_Play(void)
{
	static int hash=345;
	int 	i;
	char name[256];
	sfx_t	*sfx;

	i = 1;
	while (i<Cmd_Argc())
	{
		if (!Q_strrchr(Cmd_Argv(i), '.'))
		{
			Q_strcpy(name, Cmd_Argv(i));
			Q_strcat(name, ".wav");
		}
		else
			Q_strcpy(name, Cmd_Argv(i));
		sfx = S_PrecacheSound(name);
		S_StartSound(hash++, 0, sfx, listener_origin, 1.0, 1.0);
		i++;
	}
}

void S_PlayVol(void)
{
	static int hash=543;
	int i;
	float vol;
	char name[256];
	sfx_t	*sfx;

	i = 1;
	while (i<Cmd_Argc())
	{
		if (!Q_strrchr(Cmd_Argv(i), '.'))
		{
			Q_strcpy(name, Cmd_Argv(i));
			Q_strcat(name, ".wav");
		}
		else
			Q_strcpy(name, Cmd_Argv(i));
		sfx = S_PrecacheSound(name);
		vol = Q_atof(Cmd_Argv(i+1));
		S_StartSound(hash++, 0, sfx, listener_origin, vol, 1.0);
		i+=2;
	}
}

void S_SoundList(void)
{
	int		i;
	sfx_t	*sfx;
//	sfxcache_t	*sc;
	int		size, total;

	total = 0;
	for (sfx=known_sfx, i=0 ; i<num_sfx ; i++, sfx++)
	{
//		sc = Cache_Check (&sfx->cache);
//		if (!sc)
//			continue;
		size = sfx->length;//*sfx->width;//*(sc->stereo+1);
		total += size;
		if (sfx->loopstart >= 0)
			Con_Printf ("L");
		else
			Con_Printf (" ");
		Con_Printf(" %6i : %s\n", size, sfx->name);
	}
	Con_Printf ("Total resident: %i\n", total);
}


void S_LocalSound (char *sound)
{
	sfx_t	*sfx;

	if (nosound)
		return;
	if (!sound_started)
		return;

	sfx = S_PrecacheSound (sound);
	if (!sfx)
	{
		Con_Printf ("S_LocalSound: can't cache %s\n", sound);
		return;
	}
	S_StartSound (_g->cl.viewentity, -1, sfx, vec3_origin, 1, 1);
}


void S_ClearPrecache (void)
{
}


void S_BeginPrecaching (void)
{
}


void S_EndPrecaching (void)
{
}
#endif
