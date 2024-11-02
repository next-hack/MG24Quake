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

#include "quakedef.h"
#include "r_local.h"

//  time
#define ABSOLUTE_MIN_PARTICLES	512		// no fewer than this no matter what's
//  on the command line

const int ramp1[8] =
{ 0x6f, 0x6d, 0x6b, 0x69, 0x67, 0x65, 0x63, 0x61
};
const int ramp2[8] =
{ 0x6f, 0x6e, 0x6d, 0x6c, 0x6b, 0x6a, 0x68, 0x66
};
const int ramp3[8] =
{ 0x6d, 0x6b, 6, 5, 4, 3
};
AUX_SECTION particle_t particles[MAX_PARTICLES];
#if COPY_PARTICLES_TO_TEXTURE_BUFFER
extern uint8_t textureCacheBuffer[MAX_TEXTURE_SIZE];
#define tmpparticles ((particle_t*) textureCacheBuffer)
#else
#define tmpparticles particles
#endif


#define FIRE_RAMP_FRAC_SHIFT        5       // this is the fastest but has less frames (6 max)
#define EXPLODE_RAMP_FRAC_SHIFT     4       // Twice as slow, but 8 frames
#define EXPLODE2_RAMP_FRAC_SHIFT    4       // even slower, 8 frames
#define DIE_FRAC_SHIFT              10       // to get good resolution for 0.01 step
#define DIE_MAX_CONST               (16 << (DIE_FRAC_SHIFT))      // a particle does not last 16 seconds or more.
#define DIE_MASK                    0xFFFF
#define VEL9P7_FRAC_SHIFT           5
#define CHECK9P7(v) do{ \
                         if (v > 32767 || v < - 32768){ \
                             /*printf("vector too large %d at line %d\r\n", v, __LINE__)*/; \
                             /*system("pause")*/;   \
                             if (v > 0)  \
                                v = 32767; \
                             else if (v < 0) \
                                v = -32768;  \
                        }                     \
                        }while (0)

#define NUMVERTEXNORMALS	162
extern float r_avertexnormals[NUMVERTEXNORMALS][3];

#if !RUNTIME_RND_AVELOCITIES
const byte b_avelocities[NUMVERTEXNORMALS][3] =
{
    {0xbe, 0x23, 0x29}, {0x6c, 0xe1, 0x84}, {0x52, 0xae, 0xd6}, {0xf1, 0x49, 0x90}, {0xe9, 0xbb, 0xf1}, {0xa6, 0xb3, 0xeb}, {0x87, 0x3c, 0xdb}, {0x99, 0x3e, 0x0c},
    {0x0d, 0x5e, 0x24}, {0xb7, 0x06, 0x1c}, {0xb3, 0xde, 0x47}, {0xc8, 0x4d, 0x12}, {0x8b, 0xbb, 0x43}, {0x03, 0x1f, 0xa6}, {0x09, 0x7d, 0x5a}, {0x1f, 0x25, 0x38}, {0xcb, 0xd4, 0x5d}, {0xf5, 0x96, 0xfc}, {0x13, 0x3b, 0x45}, {0x0a, 0x89, 0x0d}, {0xae, 0xdb, 0x1c}, {0x9a, 0x20, 0x32}, {0x40, 0xee, 0x50}, {0xfd, 0x36, 0x78}, {0x32, 0x49, 0x12}, {0x7d, 0x9e, 0xf6}, {0xad, 0xdc, 0x49}, {0xf2, 0x14, 0x4f}, {0x66, 0x40, 0x44}, {0xc4, 0x6b, 0xd0}, {0x32, 0xb7, 0x30}, {0x22, 0xa1, 0x3b}, {0x91, 0x22, 0xf6}, {0x8b, 0xe1, 0x9d}, {0xb0, 0xda, 0x1f}, {0x02, 0x99, 0xca}, {0x9d, 0x72, 0xb9}, {0x80, 0x2c, 0x49}, {0x99, 0xc5, 0x7e}, {0x80, 0xe9, 0xd5},
    {0xc9, 0xea, 0xb2}, {0xbf, 0x53, 0xcc}, {0xbf, 0xd6, 0x67}, {0x7e, 0xd6, 0x14}, {0x8e, 0xdc, 0x2d}, {0xef, 0x83, 0x66}, {0x61, 0x49, 0x57}, {0x8f, 0x69, 0xff}, {0xd1, 0xcd, 0x61}, {0x9c, 0x9d, 0x1e}, {0x72, 0x72, 0x16}, {0xf0, 0x1d, 0xe6}, {0x4a, 0x4f, 0x84}, {0xd7, 0x02, 0x77}, {0x2c, 0x39, 0xe8}, {0xc9, 0xcb, 0x53}, {0x33, 0x1e, 0x12}, {0x0c, 0x9e, 0x74}, {0xd4, 0xd5, 0xf4}, {0xa4, 0xd4, 0x9f}, {0x35, 0x7e, 0x59}, {0x22, 0x32, 0xcf}, {0xcf, 0xcc, 0xf4}, {0x2d, 0x90, 0xd3}, {0x8f, 0xd3, 0x48}, {0xd9, 0xe6, 0x75}, {0xe5, 0x2a, 0x1d}, {0x2b, 0xf7, 0xc0}, {0x87, 0x81, 0x78}, {0x5f, 0x0e, 0x44}, {0xd4, 0x00, 0x50}, {0xbe, 0x8d, 0x61},
    {0x15, 0x05, 0x7b}, {0x33, 0x3b, 0x07}, {0x18, 0x1f, 0x82}, {0xda, 0x92, 0x70}, {0xce, 0x54, 0x64}, {0x3e, 0x85, 0xb1}, {0xf8, 0x15, 0x69}, {0x04, 0x6a, 0x46}, {0x0e, 0x73, 0x96}, {0x2f, 0x16, 0xd9}, {0xd4, 0x68, 0x67}, {0x4a, 0x4a, 0xf7}, {0x68, 0x57, 0xd0}, {0x16, 0xfa, 0x76}, {0xad, 0x11, 0xbb}, {0x88, 0x24, 0xae}, {0x52, 0xfe, 0x79}, {0x43, 0x25, 0xdb}, {0xf4, 0x3c, 0xe5}, {0xd8, 0xd3, 0x45}, {0x0b, 0xce, 0x28}, {0x60, 0xc5, 0xf5}, {0x97, 0x3d, 0x59}, {0x59, 0x8a, 0x27}, {0xd0, 0x2d, 0x76}, {0xcd, 0xc9, 0xc2}, {0x49, 0xd4, 0x68}, {0x25, 0x79, 0x6a}, {0x40, 0x61, 0x08}, {0x3b, 0xb1, 0x14}, {0x11, 0xa5, 0x6a}, {0x8c, 0xc1, 0x28},
    {0x0b, 0xa9, 0xd6}, {0x8c, 0x97, 0x87}, {0x15, 0xf1, 0x2f}, {0x95, 0x9a, 0x1d}, {0xe1, 0x9b, 0xc1}, {0xe9, 0x7e, 0xc0}, {0xa7, 0x9a, 0xa8}, {0xb5, 0xc2, 0x86}, {0x9a, 0xbf, 0x54}, {0x23, 0xd9, 0xe7}, {0x90, 0x55, 0xd1}, {0xd1, 0x28, 0x38}, {0xa1, 0x6c, 0xd9}, {0x4e, 0x5e, 0x66}, {0x9c, 0x30, 0xe1}, {0x71, 0xd9, 0xfe}, {0xa5, 0xe2, 0x9f}, {0x9b, 0x0c, 0xe2}, {0x65, 0x47, 0xb4}, {0x46, 0x2a, 0x38}, {0x82, 0xa9, 0x89}, {0x76, 0x7a, 0x79}, {0x63, 0xc2, 0x78}, {0xdf, 0x26, 0xb1}, {0x6d, 0x29, 0xda}, {0xe0, 0x62, 0x3e}, {0x34, 0x12, 0x96}, {0xa6, 0x39, 0xbf}, {0x5e, 0x89, 0x3f}, {0x0e, 0x6d, 0xf1}, {0x28, 0x6c, 0xe3}, {0x20, 0x1e, 0xa1},
    {0xc2, 0xcb, 0x1d}, {0x41, 0x3f, 0x03}, {0x0f, 0x84, 0x07}, {0x65, 0x05, 0x14}, {0x61, 0x28, 0x1b}, {0xe7, 0xc5, 0xc9}, {0x46, 0x8e, 0x2c}, {0xdc, 0x08, 0x36}, {0x8d, 0xa8, 0xf3}, {0xf2, 0xbe, 0xfe}, {0xff, 0x71, 0xeb}, {0x3b, 0xd0, 0xa0}, {0x8c, 0x06, 0x75}, {0x78, 0x87, 0x7e}, {0xd0, 0x4d, 0x73}, {0xbe, 0x82, 0xbe}, {0x46, 0xc2, 0xdb}, {0x8c, 0x2b, 0x41}, {0x7f, 0x30, 0xfa}, {0xa7, 0xf0, 0x70}, {0x32, 0x86, 0x54}, {0x5b, 0xaa, 0x95}, {0x0b, 0x13, 0x68}, {0xf5, 0xfc, 0xe6}, {0x7d, 0xbe, 0xca}, {0x8a, 0x89, 0x9f},
};
byte p_coord_rnd[3];
#else
vec3_t	avelocities[NUMVERTEXNORMALS];
#endif
#if PARTICLES_LINKED_LIST
particle_t	*active_particles, *free_particles;

particle_t	*particles;
#endif
//int			r_numparticles;

vec3_t			r_pright, r_pup, r_ppn;

uint16_t usedParticles = 0;
particle_t* getFreeParticle(void)
{
    static uint16_t rover = 0;
    if (usedParticles >= MAX_PARTICLES)
    {
        return NULL;
    }
    else
        while (1)
        {
            rover++;
            if (rover >= MAX_PARTICLES)
            {
                rover = 0;
            }
            if (particles[rover].inUse == 0)
            {
                particles[rover].inUse = 1;
                usedParticles++;
                return &particles[rover];
            }
        }
}
void freeParticle(particle_t *p)
{
    if (usedParticles == 0)
    {
        FIXME("Freed too many particles!");
    }
    usedParticles--;
    p->inUse = 0;
}
/*
 ===============
 R_InitParticles
 ===============
 */
void R_InitParticles(void)
{
#if !PARTICLES_LINKED_LIST
    R_ClearParticles();
#endif
#if !RUNTIME_RND_AVELOCITIES
#if RANDOMIZE_AVELOCITIES
	// next-hack: it won't change too much.
        for (int i = 0; i < 3; i++)
        {
            p_coord_rnd[i] = rand();
        }
    #endif
#endif
    /*
     i = COM_CheckParm ("-particles");

     if (i)
     {
     r_numparticles = (int)(Q_atoi(com_argv[i+1]));
     if (r_numparticles < ABSOLUTE_MIN_PARTICLES)
     r_numparticles = ABSOLUTE_MIN_PARTICLES;
     }
     else
     {
     r_numparticles = MAX_PARTICLES;
     }
     */
}


/*
 ===============
 R_EntityParticles
 ===============
 */
#if !RUNTIME_RND_AVELOCITIES
static inline float getAvelocity(int index, int coord)
{
    return 0.01f * (b_avelocities[index][coord] ^ p_coord_rnd[coord]);
}
#endif
float beamlength = 16;
vec3_t avelocity =
{ 23, 7, 3
};
float partstep = 0.01f;
float timescale = 0.01f;

void R_EntityParticles(entity_t *ent)
{
    int i;
    particle_t *p;
    float angle;
    float sp, sy, cp, cy;
    vec3_t forward;
    float dist;

    dist = 64;
#if RUNTIME_RND_AVELOCITIES
    if (!avelocities[0][0]) // next-hack does this mean that probably only one time this is called?
    {
        for (i=0 ; i<NUMVERTEXNORMALS*3 ; i++)
            avelocities[0][i] = (rand()&255) * 0.01;
    }
#endif

    for (i = 0; i < NUMVERTEXNORMALS; i++)
    {
#if !RUNTIME_RND_AVELOCITIES
        angle = _g->cl.time * (getAvelocity(i, 0));
        sy = sin_t(angle);
        cy = cos_t(angle);
        angle = _g->cl.time * getAvelocity(i, 1);
        sp = sin_t(angle);
        cp = cos_t(angle);
        angle = _g->cl.time * getAvelocity(i, 2);

#else
		angle = cl.time * avelocities[i][0];
		sy = sin_t(angle);
		cy = cos_t(angle);
		angle = cl.time * avelocities[i][1];
		sp = sin_t(angle);
		cp = cos_t(angle);
		angle = cl.time * avelocities[i][2];
		sr = sin_t(angle);
		cr = cos_t(angle);
#endif
        forward[0] = cp * cy;
        forward[1] = cp * sy;
        forward[2] = -sp;
#if PARTICLES_LINKED_LIST
		if (!free_particles)
			return;
		p = free_particles;)
		free_particles = R_GetNextParticle(p);
		R_SetNextParticle(p, active_particles);
		active_particles = p;
#else
        p = getFreeParticle();
        if (!p)
            return;
#endif
#if NO_MINIMIZE_PARTICLES
		p->die = cl.time + 0.01;
#else
        p->fixed_die = (_g->cl.time + 0.01f) * (1 << DIE_FRAC_SHIFT);
#endif
        p->color = 0x6f;
        p->type = pt_explode;
#if !ENTITY_HAS_SHORT_COORDS
		p->org[0] = ent->origin[0] + r_avertexnormals[i][0]*dist + forward[0]*beamlength;
		p->org[1] = ent->origin[1] + r_avertexnormals[i][1]*dist + forward[1]*beamlength;
		p->org[2] = ent->origin[2] + r_avertexnormals[i][2]*dist + forward[2]*beamlength;
#else
#if PART_HAS_FLOAT_ORG
		p->org[0] = toFloatCoord(ent->origin_s[0]) + r_avertexnormals[i][0]*dist + forward[0]*beamlength;
		p->org[1] = toFloatCoord(ent->origin_s[1]) + r_avertexnormals[i][1]*dist + forward[1]*beamlength;
		p->org[2] = toFloatCoord(ent->origin_s[2]) + r_avertexnormals[i][2]*dist + forward[2]*beamlength;
#else
        p->org16[0] = toShortCoord(getEntityOrigin(ent, 0)) + (r_avertexnormals[i][0] * dist + forward[0] * beamlength) * 8;
        p->org16[1] = toShortCoord(getEntityOrigin(ent, 1)) + (r_avertexnormals[i][1] * dist + forward[1] * beamlength) * 8;
        p->org16[2] = toShortCoord(getEntityOrigin(ent, 2)) + (r_avertexnormals[i][2] * dist + forward[2] * beamlength) * 8;
#endif
#endif
    }
}

/*
 ===============
 R_ClearParticles
 ===============
 */
void R_ClearParticles(void)
{
    int i;
    usedParticles = 0;
    for (i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i].inUse = 0;
    }
}
/*
 ===============
 R_ParseParticleEffect

 Parse an effect out of the server message
 ===============
 */
void R_ParseParticleEffect(void)
{
    vec3_t org, dir;
    int i, count, msgcount, color;

    for (i = 0; i < 3; i++)
        org[i] = MSG_ReadCoord();
    for (i = 0; i < 3; i++)
        dir[i] = MSG_ReadChar() * (1.0 / 16);
    msgcount = MSG_ReadByte();
    color = MSG_ReadByte();

    if (msgcount == 255)
        count = 1024;
    else
    {
        count = msgcount;
    }
    R_RunParticleEffect(org, dir, color, count);
}

/*
 ===============
 R_ParticleExplosion

 ===============
 */
void R_ParticleExplosion(vec3_t org)
{
    int i, j;
    particle_t *p;
#define PARTICLE_EXPLOSION_NUMBER 1024
#define PARTICLE_EXPLOSION2_NUMBER 512
    for (i = 0; i < PARTICLE_EXPLOSION_NUMBER; i++)
    {
        p = getFreeParticle();
        if (!p)
            return;

        p->color = ramp1[0];
#if NO_MINIMIZE_PARTICLES
		p->die = cl.time + 5;
		p->ramp = rand()&3;
#else
        p->fixed_die = (_g->cl.time + 5) * (1 << DIE_FRAC_SHIFT);
        p->fixed_ramp = (rand() & 3) << EXPLODE_RAMP_FRAC_SHIFT;
#endif
        if (i & 1)
        {
            p->type = pt_explode;
            for (j = 0; j < 3; j++)
            {
#if PART_HAS_FLOAT_ORG
				p->org[j] = org[j] + ((rand()%32)-16);
#else
                p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
#if NO_MINIMIZE_PARTICLES
				p->vel[j] = (rand()%512)-256;
#endif
            }
#if !NO_MINIMIZE_PARTICLES
            setParticleVel0(p, ((rand() % 512) - 256));
            setParticleVel1(p, ((rand() % 512) - 256));
            setParticleVel2(p, ((rand() % 512) - 256));
#endif
        }
        else
        {
            p->type = pt_explode2;
            for (j = 0; j < 3; j++)
            {
#if PART_HAS_FLOAT_ORG
				p->org[j] = org[j] + ((rand()%32)-16);
#else
                p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
#if NO_MINIMIZE_PARTICLES
				p->vel[j] = (rand()%512)-256;
#endif
            }
#if !NO_MINIMIZE_PARTICLES
            setParticleVel0(p, ((rand() % 512) - 256));
            setParticleVel1(p, ((rand() % 512) - 256));
            setParticleVel2(p, ((rand() % 512) - 256));
#endif
        }
    }
}

/*
 ===============
 R_ParticleExplosion2

 ===============
 */
void R_ParticleExplosion2(vec3_t org, int colorStart, int colorLength)
{
    int i, j;
    particle_t *p;
    int colorMod = 0;

    for (i = 0; i < PARTICLE_EXPLOSION2_NUMBER; i++)
    {
        p = getFreeParticle();
        if (!p)
            return;
#if NO_MINIMIZE_PARTICLES
		p->die = cl.time + 0.3;
#else
        p->fixed_die = (_g->cl.time + 0.3f) * (1 << DIE_FRAC_SHIFT);

#endif
        p->color = colorStart + (colorMod % colorLength);
        colorMod++;

        p->type = pt_blob;
        for (j = 0; j < 3; j++)
        {
#if PART_HAS_FLOAT_ORG
			p->org[j] = org[j] + ((rand()%32)-16);
#else
            p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
#if NO_MINIMIZE_PARTICLES
			p->vel[j] = (rand()%512)-256;
#endif
        }
#if !NO_MINIMIZE_PARTICLES
        setParticleVel0(p, ((rand() % 512) - 256));
        setParticleVel1(p, ((rand() % 512) - 256));
        setParticleVel2(p, ((rand() % 512) - 256));
#endif
    }
}

/*
 ===============
 R_BlobExplosion

 ===============
 */
void R_BlobExplosion(vec3_t org)
{
    int i, j;
    particle_t *p;

    for (i = 0; i < 1024; i++)
    {
#if PARTICLES_LINKED_LIST
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = R_GetNextParticle(p);
		R_SetNextParticle(p, active_particles);
		active_particles = p;
#else
        p = getFreeParticle();
        if (!p)
            return;
#endif
#if NO_MINIMIZE_PARTICLES
		p->die = cl.time + 1 + (rand()&8)*0.05;
#else
        p->fixed_die = (_g->cl.time + 1 + (rand() & 8) * 0.05f) * (1 << DIE_FRAC_SHIFT);
#endif
        if (i & 1)
        {
            p->type = pt_blob;
            p->color = 66 + rand() % 6;
            for (j = 0; j < 3; j++)
            {
#if PART_HAS_FLOAT_ORG
				p->org[j] = org[j] + ((rand()%32)-16);
#else
                p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));

#endif
#if NO_MINIMIZE_PARTICLES
				p->vel[j] = (rand()%512)-256;
#endif
            }
#if !NO_MINIMIZE_PARTICLES
            setParticleVel0(p, ((rand() % 512) - 256));
            setParticleVel1(p, ((rand() % 512) - 256));
            setParticleVel2(p, ((rand() % 512) - 256));
#endif
        }
        else
        {
            p->type = pt_blob2;
            p->color = 150 + rand() % 6;
            for (j = 0; j < 3; j++)
            {
#if PART_HAS_FLOAT_ORG
				p->org[j] = org[j] + ((rand()%32)-16);
#else
                p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
#if NO_MINIMIZE_PARTICLES
				p->vel[j] = (rand()%512)-256;
#endif
            }
#if !NO_MINIMIZE_PARTICLES
            setParticleVel0(p, ((rand() % 512) - 256));
            setParticleVel1(p, ((rand() % 512) - 256));
            setParticleVel2(p, ((rand() % 512) - 256));
#endif
        }
    }
}

/*
 ===============
 R_RunParticleEffect

 ===============
 */
void R_RunParticleEffect(vec3_t org, vec3_t dir, int color, int count)
{
    int i, j;
    particle_t *p;

    for (i = 0; i < count; i++)
    {

        p = getFreeParticle();
        if (!p)
            return;

        if (count == 1024)
        {	// rocket explosion
            p->color = ramp1[0];
#if NO_MINIMIZE_PARTICLES
			p->die = cl.time + 5;
			p->ramp = rand()&3;
			if (i & 1)
			{
				p->type = pt_explode;
				for (j=0 ; j<3 ; j++)
				{
					p->org[j] = org[j] + ((rand()%32)-16);
					p->vel[j] = (rand()%512)-256;
				}
			}
			else
			{
				p->type = pt_explode2;
				for (j=0 ; j<3 ; j++)
				{
					p->org[j] = org[j] + ((rand()%32)-16);
					p->vel[j] = (rand()%512)-256;
				}
			}
#else
            p->fixed_die = (_g->cl.time + 5) * (1 << DIE_FRAC_SHIFT);
            p->fixed_ramp = rand() & 3;
            if (i & 1)
            {
                p->fixed_ramp = p->fixed_ramp << EXPLODE_RAMP_FRAC_SHIFT;
                p->type = pt_explode;
                for (j = 0; j < 3; j++)
                {
#if PART_HAS_FLOAT_ORG
					p->org[j] = org[j] + ((rand()%32)-16);
#else
                    p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
                }
                setParticleVel0(p, ((rand() % 512) - 256));
                setParticleVel1(p, ((rand() % 512) - 256));
                setParticleVel2(p, ((rand() % 512) - 256));
            }
            else
            {
                p->fixed_ramp = p->fixed_ramp << EXPLODE2_RAMP_FRAC_SHIFT;
                p->type = pt_explode2;
                for (j = 0; j < 3; j++)
                {
#if PART_HAS_FLOAT_ORG
					p->org[j] = org[j] + ((rand()%32)-16);
#else
                    p->org16[j] = 8 * (org[j] + ((rand() % 32) - 16));
#endif
                }
                setParticleVel0(p, ((rand() % 512) - 256));
                setParticleVel1(p, ((rand() % 512) - 256));
                setParticleVel2(p, ((rand() % 512) - 256));
            }
#endif
        }
        else
        {
#if NO_MINIMIZE_PARTICLES
			p->die = cl.time + 0.1*(rand()%5);
#else
            p->fixed_die = (_g->cl.time + 0.1f * (rand() % 5)) * (1 << DIE_FRAC_SHIFT);
#endif
            p->color = (color & ~7) + (rand() & 7);
            p->type = pt_slowgrav;
            for (j = 0; j < 3; j++)
            {
#if PART_HAS_FLOAT_ORG
				p->org[j] = org[j] + ((rand()&15)-8);
#else
                p->org16[j] = 8 * (org[j] + ((rand() & 15) - 8));
#endif
#if NO_MINIMIZE_PARTICLES
				p->vel[j] = dir[j]*15;// + (rand()%300)-150;
#endif
            }
#if !NO_MINIMIZE_PARTICLES
            setParticleVel0(p, dir[0] * 15);
            setParticleVel1(p, dir[1] * 15);
            setParticleVel2(p, dir[2] * 15);
#endif
        }
    }
}

/*
 ===============
 R_LavaSplash

 ===============
 */
void R_LavaSplash(vec3_t org)
{
    int i, j, k;
    particle_t *p;
    float vel;
    vec3_t dir;
    for (i = -16; i < 16; i++)
        for (j = -16; j < 16; j++)
            for (k = 0; k < 1; k++)
            {
#if PARTICLES_LINKED_LIST
				if (!free_particles)
					return;
				p = free_particles;
		        free_particles = R_GetNextParticle(p);
		        R_SetNextParticle(p, active_particles);
				active_particles = p;
#else
                p = getFreeParticle();
                if (!p)
                    return;
#endif
#if NO_MINIMIZE_PARTICLES
				p->die = cl.time + 2 + (rand()&31) * 0.02;
#else
                p->fixed_die = (_g->cl.time + 2 + (rand() & 31) * 0.02f) * (1 << DIE_FRAC_SHIFT);
#endif
                p->color = 224 + (rand() & 7);
                p->type = pt_slowgrav;

                dir[0] = j * 8 + (rand() & 7);
                dir[1] = i * 8 + (rand() & 7);
                dir[2] = 256;
#if PART_HAS_FLOAT_ORG
				p->org[0] = org[0] + dir[0];
				p->org[1] = org[1] + dir[1];
				p->org[2] = org[2] + (rand()&63);
#else
                p->org16[0] = 8 * (org[0] + dir[0]);
                p->org16[1] = 8 * (org[1] + dir[1]);
                p->org16[2] = 8 * (org[2] + (rand() & 63));
#endif
                VectorNormalize(dir);
                vel = 50 + (rand() & 63);
#if NO_MINIMIZE_PARTICLES
				VectorScale (dir, vel, p->vel);
#else
                //
                setParticleVel0(p, dir[0] * vel);
                setParticleVel1(p, dir[1] * vel);
                setParticleVel2(p, dir[2] * vel);
#endif
            }
}

/*
 ===============
 R_TeleportSplash

 ===============
 */
void R_TeleportSplash(vec3_t org)
{
    int i, j, k;
    particle_t *p;
    float vel;
    vec3_t dir;

    for (i = -16; i < 16; i += 4)
        for (j = -16; j < 16; j += 4)
            for (k = -24; k < 32; k += 4)
            {
#if PARTICLES_LINKED_LIST
				if (!free_particles)
					return;
				p = free_particles;
		        free_particles = R_GetNextParticle(p);
		        R_SetNextParticle(p, active_particles);
				active_particles = p;
#else
                p = getFreeParticle();
                if (!p)
                    return;
#endif
#if NO_MINIMIZE_PARTICLES
				p->die = cl.time + 0.2 + (rand()&7) * 0.02;
#else
                p->fixed_die = (_g->cl.time + 0.2f + (rand() & 7) * 0.02f) * (1 << DIE_FRAC_SHIFT);
#endif
                p->color = 7 + (rand() & 7);
                p->type = pt_slowgrav;

                dir[0] = j * 8;
                dir[1] = i * 8;
                dir[2] = k * 8;
#if PART_HAS_FLOAT_ORG
				p->org[0] = org[0] + i + (rand()&3);
				p->org[1] = org[1] + j + (rand()&3);
				p->org[2] = org[2] + k + (rand()&3);
#else
                p->org16[0] = 8 * (org[0] + i + (rand() & 3));
                p->org16[1] = 8 * (org[1] + j + (rand() & 3));
                p->org16[2] = 8 * (org[2] + k + (rand() & 3));
#endif
                VectorNormalize(dir);
                vel = 50 + (rand() & 63);
#if NO_MINIMIZE_PARTICLES
				VectorScale (dir, vel, p->vel);
#else

                //
                setParticleVel0(p, dir[0] * vel);
                setParticleVel1(p, dir[1] * vel);
                setParticleVel2(p, dir[2] * vel);
#endif

            }
}

void R_RocketTrail(vec3_t start, vec3_t end, int type)
{
    vec3_t vec;
    float len;
    int j;
    particle_t *p;
    int dec;
    static int tracercount;
    VectorSubtract(end, start, vec);
    len = VectorNormalize(vec);
    if (type < 128)
    {
        dec = 3;
        // next-hack: added this because at low frame rate, the particles would be concentrated only in few spots.
        // because len would be large, and start would be incremented only by one third of it.
        VectorScale(vec, dec, vec);
    }
    else
    {
        dec = 1;
        type -= 128;
    }

    while (len > 0)
    {
        len -= dec;
#if PARTICLES_LINKED_LIST
		if (!free_particles)
			return;
		p = free_particles;
		free_particles = R_GetNextParticle(p);
		R_SetNextParticle(p, active_particles);
		active_particles = p;
#else
        p = getFreeParticle();
        if (!p)
            return;
#endif
#if NO_MINIMIZE_PARTICLES
		VectorCopy (vec3_origin, p->vel);
		p->die = cl.time + 2;
#else
        setParticleVel0(p, 0);
        setParticleVel1(p, 0);
        setParticleVel2(p, 0);
        p->fixed_die = (_g->cl.time + 2) * (1 << DIE_FRAC_SHIFT);
#endif

        switch (type)
        {
            case 0:	// rocket trail
#if NO_MINIMIZE_PARTICLES
				p->ramp = (rand()&3);
				p->color = ramp3[(int)p->ramp];
#else
                p->fixed_ramp = (rand() & 3) << FIRE_RAMP_FRAC_SHIFT;
                p->color = ramp3[p->fixed_ramp >> FIRE_RAMP_FRAC_SHIFT];
#endif
                p->type = pt_fire;
                for (j = 0; j < 3; j++)
#if PART_HAS_FLOAT_ORG
					p->org[j] = start[j] + ((rand()%6)-3);
#else
                    p->org16[j] = 8 * (start[j] + ((rand() % 6) - 3));
#endif
                break;

            case 1:	// smoke smoke
#if NO_MINIMIZE_PARTICLES
				p->ramp = (rand()&3) + 2;
				p->color = ramp3[(int)p->ramp];
#else
                p->fixed_ramp = ((rand() & 3) + 2) << FIRE_RAMP_FRAC_SHIFT;
                p->color = ramp3[p->fixed_ramp >> FIRE_RAMP_FRAC_SHIFT];
#endif
                p->type = pt_fire;
                for (j = 0; j < 3; j++)
#if PART_HAS_FLOAT_ORG
					p->org[j] = start[j] + ((rand()%6)-3);
#else
                    p->org16[j] = 8 * (start[j] + ((rand() % 6) - 3));
#endif
                break;

            case 2:	// blood
                p->type = pt_grav;
                p->color = 67 + (rand() & 3);
                for (j = 0; j < 3; j++)
#if PART_HAS_FLOAT_ORG
					p->org[j] = start[j] + ((rand()%6)-3);
#else
                    p->org16[j] = 8 * (start[j] + ((rand() % 6) - 3));
#endif
                break;

            case 3:
            case 5:	// tracer
#if NO_MINIMIZE_PARTICLES
				p->die = cl.time + 0.5;
#else
                p->fixed_die = (_g->cl.time + 0.5f) * (1 << DIE_FRAC_SHIFT);
#endif
                p->type = pt_static;
                if (type == 3)
                    p->color = 52 + ((tracercount & 4) << 1);
                else
                    p->color = 230 + ((tracercount & 4) << 1);

                tracercount++;
#if PART_HAS_FLOAT_ORG
				VectorCopy (start, p->org);
#else
                p->org16[0] = 8 * start[0];
                p->org16[1] = 8 * start[1];
                p->org16[2] = 8 * start[2];
#endif
                if (tracercount & 1)
                {
#if NO_MINIMIZE_PARTICLES
					p->vel[0] = 30*vec[1];
					p->vel[1] = 30*-vec[0];
#else
                    setParticleVel0(p, (30 * vec[1]));
                    setParticleVel1(p, (30 * -vec[0]));
#endif
                }
                else
                {
#if NO_MINIMIZE_PARTICLES
					p->vel[0] = 30*-vec[1];
					p->vel[1] = 30*vec[0];
#else
                    setParticleVel0(p, (30 * -vec[1]));
                    setParticleVel1(p, (30 * vec[0]));
#endif
                }
                break;

            case 4:	// slight blood
                p->type = pt_grav;
                p->color = 67 + (rand() & 3);
                for (j = 0; j < 3; j++)
#if PART_HAS_FLOAT_ORG
					p->org[j] = start[j] + ((rand()%6)-3);
#else
                    p->org16[j] = 8 * (start[j] + ((rand() % 6) - 3));
#endif
                len -= 3;
                break;

            case 6:	// voor trail
                p->color = 9 * 16 + 8 + (rand() & 3);
                p->type = pt_static;
#if NO_MINIMIZE_PARTICLES
				p->die = cl.time + 0.3;
#else
                p->fixed_die = (_g->cl.time + 0.3f) * (1 << DIE_FRAC_SHIFT);
#endif
                for (j = 0; j < 3; j++)
#if PART_HAS_FLOAT_ORG
					p->org[j] = start[j] + ((rand()&15)-8);
#else
                    p->org16[j] = 8 * (start[j] + ((rand() & 15) - 8));
#endif
                break;
        }
        VectorAdd(start, vec, start);
    }
}

/*
 ===============
 R_DrawParticles
 ===============
 */
#if USE_ORIGINAL_CVAR
extern	cvar_t	sv_gravity;
#endif
void R_DrawParticles(void)
{
    particle_t *p, *kill;
    float grav;

    uint32_t fireTime, explodeTime, explode2Time;
    float dvel;
    float frametime;

    D_StartParticles();

    VectorScale(_g->vright, xscaleshrink, r_pright);
    VectorScale(_g->vup, yscaleshrink, r_pup);
    VectorCopy(_g->vpn, r_ppn);

    frametime = _g->cl.time - _g->cl.oldtime;
    fireTime = frametime * 5 * (1 << FIRE_RAMP_FRAC_SHIFT);
    explodeTime = frametime * 10 * (1 << EXPLODE_RAMP_FRAC_SHIFT);
    explode2Time = frametime * 15 * (1 << EXPLODE2_RAMP_FRAC_SHIFT);

    grav = frametime * sv_gravity * 0.05f;
    dvel = 4 * frametime;

    for (int partN = 0; partN < MAX_PARTICLES; partN++)
    {
        if (!tmpparticles[partN].inUse)
            continue;
        kill = &tmpparticles[partN];
        if (kill)
        {
            uint16_t clTime = ((uint16_t) (_g->cl.time * (1 << DIE_FRAC_SHIFT))) & DIE_MASK;
            clTime = (kill->fixed_die - clTime) & DIE_MASK;
            if (clTime > DIE_MAX_CONST)
            {

                freeParticle(kill);
                continue;
            }

        }
        break;
    }

    for (int partN = 0; partN < MAX_PARTICLES; partN++)
    {
        p = &tmpparticles[partN];
        if (!p->inUse)
            continue;
        // check if kill is necessary
        uint16_t clTime = ((uint16_t) (_g->cl.time * (1 << DIE_FRAC_SHIFT))) & DIE_MASK;
        clTime = (p->fixed_die - clTime) & DIE_MASK;
        if (clTime > DIE_MAX_CONST)
        {
            freeParticle(p);
            continue;
        }

        D_DrawParticle(p);
        //
        float frametime8 = frametime * 8;
        float vel0, vel1, vel2;
        vel0 =  getParticleVel0(p);
        vel1 =  getParticleVel1(p);
        vel2 =  getParticleVel2(p);

        p->org16[0] += (vel0 * frametime8);
        p->org16[1] += (vel1 * frametime8);
        p->org16[2] += (vel2 * frametime8);

        switch (p->type)
        {
            case pt_static:
                break;
            case pt_fire:
                p->fixed_ramp += fireTime;
                if (p->fixed_ramp >= (6 << FIRE_RAMP_FRAC_SHIFT))
                {
                    p->fixed_die = (_g->cl.time - 1) * (1 << DIE_FRAC_SHIFT);
                }
                else
                    p->color = ramp3[p->fixed_ramp >> FIRE_RAMP_FRAC_SHIFT];
                // braces only for declaring v
                {
                    float v = vel2 + grav;
                    setParticleVel2(p, v);
                }
                break;
            case pt_explode:
                p->fixed_ramp += explodeTime;
                if (p->fixed_ramp >= (8 << EXPLODE_RAMP_FRAC_SHIFT))
                {
                    p->fixed_die = (_g->cl.time - 1) * (1 << DIE_FRAC_SHIFT);
                }
                else
                    p->color = ramp1[p->fixed_ramp >> EXPLODE_RAMP_FRAC_SHIFT];
                setParticleVel0(p, vel0 * (1 + dvel));
                setParticleVel1(p, vel1 * (1 + dvel));
                setParticleVel2(p, vel2 * (1 + dvel) - grav);
                break;

            case pt_explode2:
                p->fixed_ramp += explode2Time;
                if (p->fixed_ramp >= (8 << EXPLODE2_RAMP_FRAC_SHIFT))
                {
                    p->fixed_die = (_g->cl.time - 1) * (1 << DIE_FRAC_SHIFT);
                }
                else
                    p->color = ramp2[p->fixed_ramp >> EXPLODE2_RAMP_FRAC_SHIFT];
                setParticleVel0(p, vel0 * (1 - frametime));
                setParticleVel1(p, vel1 * (1 - frametime));
                setParticleVel2(p, vel2 * (1 - frametime) - grav);
                break;

            case pt_blob:
                setParticleVel0(p, vel0 * (1 + dvel));
                setParticleVel1(p, vel1 * (1 + dvel));
                setParticleVel2(p, vel2 * (1 + dvel) - grav);
                break;

            case pt_blob2:
                setParticleVel0(p, vel0 * (1 - dvel));
                setParticleVel1(p, vel1 * (1 - dvel));
                setParticleVel2(p, vel2 * (1 - dvel) - grav);
                break;

            case pt_grav:
            case pt_slowgrav:
                setParticleVel2(p, vel2 - grav);
                break;
        }
    }
    D_EndParticles();
}

