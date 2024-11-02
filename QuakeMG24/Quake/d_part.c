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
// d_part.c: software driver module for drawing particles
#include "quakedef.h"
#include "d_local.h"
#include "r_local.h"
#if COPY_PARTICLES_TO_TEXTURE_BUFFER
extern AUX_SECTION particle_t particles[MAX_PARTICLES];
#endif
/*
 ==============
 D_EndParticles
 ==============
 */
void D_EndParticles(void)
{
#if COPY_PARTICLES_TO_TEXTURE_BUFFER
    particle_t *sparticles = (particle_t *) textureCacheBuffer;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (sparticles[i].inUse)
        {
            Q_memcpy(&particles[i], &sparticles[i], sizeof(particle_t));
        }
        else
        {
            particles[i].inUse = 0;
        }
    }
#endif
}

/*
 ==============
 D_StartParticles
 ==============
 */
void D_StartParticles(void)
{
#if COPY_PARTICLES_TO_TEXTURE_BUFFER
    particle_t *dparticles = (particle_t *) textureCacheBuffer;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (particles[i].inUse)
        {
            Q_memcpy(&dparticles[i], &particles[i], sizeof(particle_t));
        }
        else
        {
            dparticles[i].inUse = 0;
        }
    }
#endif
}

#if	!id386

/*
 ==============
 D_DrawParticle
 ==============
 */
void D_DrawParticle(const particle_t *pparticle)
{
    vec3_t local, transformed;
    float zi;
    byte *pdest;
    short *pz;
    int i, izi, pix, count, u, v;

// transform point
#if PART_HAS_FLOAT_ORG
	VectorSubtract (pparticle->org, r_origin, local);
#else
    local[0] = pparticle->org16[0] * (1.0f / 8) - _g->r_origin[0];
    local[1] = pparticle->org16[1] * (1.0f / 8) - _g->r_origin[1];
    local[2] = pparticle->org16[2] * (1.0f / 8) - _g->r_origin[2];

#endif
    transformed[2] = DotProduct(local, r_ppn);

    if (transformed[2] < PARTICLE_Z_CLIP)
        return;

    transformed[0] = DotProduct(local, r_pright);
    transformed[1] = DotProduct(local, r_pup);

// project the point
// FIXME: preadjust xcenter and ycenter
    zi = 1.0f / transformed[2];
    u = (int) (xcenter + zi * transformed[0] + 0.5f);
    v = (int) (ycenter - zi * transformed[1] + 0.5f);

    if ((v > d_vrectbottom_particle) || (u > d_vrectright_particle) || (v < d_vrecty) || (u < d_vrectx))
    {
        return;
    }

    pz = _g->d_pzbuffer + (d_zwidth * v) + u;
    pdest = _g->d_viewbuffer + d_scantable(v) + u;
    izi = (int) (zi * 0x8000);

    pix = izi >> d_pix_shift;

    if (pix < d_pix_min)
        pix = d_pix_min;
    else if (pix > d_pix_max)
        pix = d_pix_max;
    uint8_t partcolor = pparticle->color;
    switch (pix)
    {
        case 1:
            count = 1 << d_y_aspect_shift;

            for (; count; count--, pz += d_zwidth, pdest += screenwidth)
            {
                if (pz[0] <= izi)
                {
                    pz[0] = izi;
                    pdest[0] = partcolor;
                }
            }
            break;

        case 2:
            count = 2 << d_y_aspect_shift;

            for (; count; count--, pz += d_zwidth, pdest += screenwidth)
            {
                if (pz[0] <= izi)
                {
                    pz[0] = izi;
                    pdest[0] = partcolor;
                }

                if (pz[1] <= izi)
                {
                    pz[1] = izi;
                    pdest[1] = partcolor;
                }
            }
            break;

        case 3:
            count = 3 << d_y_aspect_shift;

            for (; count; count--, pz += d_zwidth, pdest += screenwidth)
            {
                if (pz[0] <= izi)
                {
                    pz[0] = izi;
                    pdest[0] = partcolor;
                }

                if (pz[1] <= izi)
                {
                    pz[1] = izi;
                    pdest[1] = partcolor;
                }

                if (pz[2] <= izi)
                {
                    pz[2] = izi;
                    pdest[2] = partcolor;
                }
            }
            break;

        case 4:
            count = 4 << d_y_aspect_shift;

            for (; count; count--, pz += d_zwidth, pdest += screenwidth)
            {
                if (pz[0] <= izi)
                {
                    pz[0] = izi;
                    pdest[0] = partcolor;
                }

                if (pz[1] <= izi)
                {
                    pz[1] = izi;
                    pdest[1] = partcolor;
                }

                if (pz[2] <= izi)
                {
                    pz[2] = izi;
                    pdest[2] = partcolor;
                }

                if (pz[3] <= izi)
                {
                    pz[3] = izi;
                    pdest[3] = partcolor;
                }
            }
            break;

        default:
            count = pix << d_y_aspect_shift;

            for (; count; count--, pz += d_zwidth, pdest += screenwidth)
            {
                for (i = 0; i < pix; i++)
                {
                    if (pz[i] <= izi)
                    {
                        pz[i] = izi;
                        pdest[i] = partcolor;
                    }
                }
            }
            break;
    }
}

#endif	// !id386

