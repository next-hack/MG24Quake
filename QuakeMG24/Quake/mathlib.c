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
// mathlib.c -- math primitives
#include <math.h>
#include "quakedef.h"
void Sys_Error(char *error, ...);

vec3_t vec3_origin =
{ 0, 0, 0
};
int nanmask = 255 << 23;

/*-----------------------------------------------------------------*/

//#define DEG2RAD( a ) ( a * M_PI ) / 180.0F
#define DEG2RAD( a ) ( (a) * (M_PI / 180.0F) )

void ProjectPointOnPlane(vec3_t dst, const vec3_t p, const vec3_t normal)
{
    float d;
    vec3_t n;
    float inv_denom;

    inv_denom = 1.0f / DotProduct(normal, normal);

    d = DotProduct( normal, p ) * inv_denom;

    n[0] = normal[0] * inv_denom;
    n[1] = normal[1] * inv_denom;
    n[2] = normal[2] * inv_denom;

    dst[0] = p[0] - d * n[0];
    dst[1] = p[1] - d * n[1];
    dst[2] = p[2] - d * n[2];
}

/*
 ** assumes "src" is normalized
 */
void PerpendicularVector(vec3_t dst, const vec3_t src)
{
    int pos;
    int i;
    float minelem = 1.0F;
    vec3_t tempvec;

    /*
     ** find the smallest magnitude axially aligned vector
     */
    for (pos = 0, i = 0; i < 3; i++)
    {
        if (fabsf_m(src[i]) < minelem)
        {
            pos = i;
            minelem = fabsf_m(src[i]);
        }
    }
    tempvec[0] = tempvec[1] = tempvec[2] = 0.0F;
    tempvec[pos] = 1.0F;

    /*
     ** project the point onto the plane defined by src
     */
    ProjectPointOnPlane(dst, tempvec, src);

    /*
     ** normalize the result
     */
    VectorNormalize(dst);
}

#ifdef _WIN32
#pragma optimize( "", off )
#endif

void RotatePointAroundVector(vec3_t dst, const vec3_t dir, const vec3_t point, float degrees)
{
    float m[3][3];
    float im[3][3];
    float zrot[3][3];
    float tmpmat[3][3];
    float rot[3][3];
    int i;
    vec3_t vr, vup, vf;

    vf[0] = dir[0];
    vf[1] = dir[1];
    vf[2] = dir[2];

    PerpendicularVector(vr, dir);
    CrossProduct(vr, vf, vup);

    m[0][0] = vr[0];
    m[1][0] = vr[1];
    m[2][0] = vr[2];

    m[0][1] = vup[0];
    m[1][1] = vup[1];
    m[2][1] = vup[2];

    m[0][2] = vf[0];
    m[1][2] = vf[1];
    m[2][2] = vf[2];

    memcpy(im, m, sizeof(im));

    im[0][1] = m[1][0];
    im[0][2] = m[2][0];
    im[1][0] = m[0][1];
    im[1][2] = m[2][1];
    im[2][0] = m[0][2];
    im[2][1] = m[1][2];

    fastMemclear32(zrot, sizeof(zrot) / 4);
    zrot[0][0] = zrot[1][1] = zrot[2][2] = 1.0F;

    zrot[0][0] = cos_t(DEG2RAD(degrees));
    zrot[0][1] = sin_t(DEG2RAD(degrees));
    zrot[1][0] = -sin_t(DEG2RAD(degrees));
    zrot[1][1] = cos_t(DEG2RAD(degrees));

    R_ConcatRotations(m, zrot, tmpmat);
    R_ConcatRotations(tmpmat, im, rot);

    for (i = 0; i < 3; i++)
    {
        dst[i] = rot[i][0] * point[0] + rot[i][1] * point[1] + rot[i][2] * point[2];
    }
}

#ifdef _WIN32
#pragma optimize( "", on )
#endif

/*-----------------------------------------------------------------*/

__attribute__ ((pure)) float anglemod(float a)
{
#if 0
	if (a >= 0)
		a -= 360*(int)(a/360);
	else
		a += 360*( 1 + (int)(-a/360) );
#endif
    a = (360.0f / 65536) * ((int) (a * (65536 / 360.0f)) & 65535);
    return a;
}

/*
 ==================
 BOPS_Error

 Split out like this for ASM to call.
 ==================
 */
void BOPS_Error(void)
{
    Sys_Error("BoxOnPlaneSide:  Bad signbits");
}

#if	!id386

/*
 ==================
 BoxOnPlaneSide

 Returns 1, 2, or 1 + 2
 ==================
 */
int BoxOnPlaneSide(vec3_t emins, vec3_t emaxs, mplane_t *p)
{
    float dist1, dist2;
    int sides;

#if 0	// this is done by the BOX_ON_PLANE_SIDE macro before calling this
		// function
// fast axial cases
	if (p->type < 3)
	{
		if (p->dist <= emins[p->type])
			return 1;
		if (p->dist >= emaxs[p->type])
			return 2;
		return 3;
	}
#endif

// general case
    switch (p->signbits)
    {
        case 0:
            dist1 = p->normal[0] * emaxs[0] + p->normal[1] * emaxs[1] + p->normal[2] * emaxs[2];
            dist2 = p->normal[0] * emins[0] + p->normal[1] * emins[1] + p->normal[2] * emins[2];
            break;
        case 1:
            dist1 = p->normal[0] * emins[0] + p->normal[1] * emaxs[1] + p->normal[2] * emaxs[2];
            dist2 = p->normal[0] * emaxs[0] + p->normal[1] * emins[1] + p->normal[2] * emins[2];
            break;
        case 2:
            dist1 = p->normal[0] * emaxs[0] + p->normal[1] * emins[1] + p->normal[2] * emaxs[2];
            dist2 = p->normal[0] * emins[0] + p->normal[1] * emaxs[1] + p->normal[2] * emins[2];
            break;
        case 3:
            dist1 = p->normal[0] * emins[0] + p->normal[1] * emins[1] + p->normal[2] * emaxs[2];
            dist2 = p->normal[0] * emaxs[0] + p->normal[1] * emaxs[1] + p->normal[2] * emins[2];
            break;
        case 4:
            dist1 = p->normal[0] * emaxs[0] + p->normal[1] * emaxs[1] + p->normal[2] * emins[2];
            dist2 = p->normal[0] * emins[0] + p->normal[1] * emins[1] + p->normal[2] * emaxs[2];
            break;
        case 5:
            dist1 = p->normal[0] * emins[0] + p->normal[1] * emaxs[1] + p->normal[2] * emins[2];
            dist2 = p->normal[0] * emaxs[0] + p->normal[1] * emins[1] + p->normal[2] * emaxs[2];
            break;
        case 6:
            dist1 = p->normal[0] * emaxs[0] + p->normal[1] * emins[1] + p->normal[2] * emins[2];
            dist2 = p->normal[0] * emins[0] + p->normal[1] * emaxs[1] + p->normal[2] * emaxs[2];
            break;
        case 7:
            dist1 = p->normal[0] * emins[0] + p->normal[1] * emins[1] + p->normal[2] * emins[2];
            dist2 = p->normal[0] * emaxs[0] + p->normal[1] * emaxs[1] + p->normal[2] * emaxs[2];
            break;
        default:
            dist1 = dist2 = 0;		// shut up compiler
            BOPS_Error();
            break;
    }

#if 0
	int		i;
	vec3_t	corners[2];

	for (i=0 ; i<3 ; i++)
	{
		if (plane->normal[i] < 0)
		{
			corners[0][i] = emins[i];
			corners[1][i] = emaxs[i];
		}
		else
		{
			corners[1][i] = emins[i];
			corners[0][i] = emaxs[i];
		}
	}
	dist = DotProduct (plane->normal, corners[0]) - plane->dist;
	dist2 = DotProduct (plane->normal, corners[1]) - plane->dist;
	sides = 0;
	if (dist1 >= 0)
		sides = 1;
	if (dist2 < 0)
		sides |= 2;

#endif

    sides = 0;
#if PLANE_HAS_FLOAT_DIST
	if (dist1 >= p->dist)
		sides = 1;
	if (dist2 < p->dist)
		sides |= 2;
#else
    float planeDist = getPlaneDist(p);
    if (dist1 >= planeDist)
        sides = 1;
    if (dist2 < planeDist)
        sides |= 2;

#endif

#ifdef PARANOID
if (sides == 0)
	Sys_Error ("BoxOnPlaneSide: sides==0");
#endif

    return sides;
}

#endif

/*__attribute__ ((pure))*/int VectorCompare(vec3_t v1, vec3_t v2)
{
    int i;

    for (i = 0; i < 3; i++)
        if (v1[i] != v2[i])
            return 0;

    return 1;
}

void VectorMA(vec3_t veca, float scale, vec3_t vecb, vec3_t vecc)
{
    vecc[0] = veca[0] + scale * vecb[0];
    vecc[1] = veca[1] + scale * vecb[1];
    vecc[2] = veca[2] + scale * vecb[2];
}

vec_t _DotProduct(vec3_t v1, vec3_t v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void _VectorSubtract(vec3_t veca, vec3_t vecb, vec3_t out)
{
    out[0] = veca[0] - vecb[0];
    out[1] = veca[1] - vecb[1];
    out[2] = veca[2] - vecb[2];
}

void _VectorAdd(vec3_t veca, vec3_t vecb, vec3_t out)
{
    out[0] = veca[0] + vecb[0];
    out[1] = veca[1] + vecb[1];
    out[2] = veca[2] + vecb[2];
}

void _VectorCopy(vec3_t in, vec3_t out)
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
}

int Q_log2(int val)
{
    int answer = 0;
    while (val >>= 1)
        answer++;
    return answer;
}

/*
 ================
 R_ConcatRotations
 ================
 */
void R_ConcatRotations(float in1[3][3], float in2[3][3], float out[3][3])
{
    out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] + in1[0][2] * in2[2][0];
    out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] + in1[0][2] * in2[2][1];
    out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] + in1[0][2] * in2[2][2];
    out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] + in1[1][2] * in2[2][0];
    out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] + in1[1][2] * in2[2][1];
    out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] + in1[1][2] * in2[2][2];
    out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] + in1[2][2] * in2[2][0];
    out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] + in1[2][2] * in2[2][1];
    out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] + in1[2][2] * in2[2][2];
}

/*
 ================
 R_ConcatTransforms
 ================
 */
void R_ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4])
{
#if WIN32 && 0
    static int cnt = 0;
    cnt ++;
    printf("%s %d\r\n", __FUNCTION__, cnt);
    #endif // WIN32
    out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] + in1[0][2] * in2[2][0];
    out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] + in1[0][2] * in2[2][1];
    out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] + in1[0][2] * in2[2][2];
    out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] + in1[0][2] * in2[2][3] + in1[0][3];
    out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] + in1[1][2] * in2[2][0];
    out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] + in1[1][2] * in2[2][1];
    out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] + in1[1][2] * in2[2][2];
    out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] + in1[1][2] * in2[2][3] + in1[1][3];
    out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] + in1[2][2] * in2[2][0];
    out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] + in1[2][2] * in2[2][1];
    out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] + in1[2][2] * in2[2][2];
    out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] + in1[2][2] * in2[2][3] + in1[2][3];
}

/*
 ===================
 FloorDivMod

 Returns mathematically correct (floor-based) quotient and remainder for
 numer and denom, both of which should contain no fractional part. The
 quotient must fit in 32 bits.
 ====================
 */
void FloorDivMod(QDFLOAT numer, QDFLOAT denom, int *quotient, int *rem)
{
    int q, r;
    QDFLOAT x;

#ifdef PARANOID
	if (denom <= 0.0)
		Sys_Error ("FloorDivMod: bad denominator %d\n", denom);

//	if ((floor(numer) != numer) || (floor(denom) != denom))
//		Sys_Error ("FloorDivMod: non-integer numer or denom %f %f\n",
//				numer, denom);
#endif

    if (numer >= 0.0)
    {

        x = floorf_m(numer / denom);
        q = (int) x;
        r = (int) floorf_m(numer - (x * denom));
    }
    else
    {
        //
        // perform operations with positive values, and fix mod to make floor-based
        //
        x = floorf_m(-numer / denom);
        q = -(int) x;
        r = (int) floorf_m(-numer - (x * denom));
        if (r != 0)
        {
            q--;
            r = (int) denom - r;
        }
    }

    *quotient = q;
    *rem = r;
}

/*
 ===================
 GreatestCommonDivisor
 ====================
 */
__attribute__ ((pure)) int GreatestCommonDivisor(int i1, int i2)
{
    if (i1 > i2)
    {
        if (i2 == 0)
            return (i1);
        return GreatestCommonDivisor(i2, i1 % i2);
    }
    else
    {
        if (i1 == 0)
            return (i2);
        return GreatestCommonDivisor(i1, i2 % i1);
    }
}

#if	!id386

// TODO: move to nonintel.c

/*
 ===================
 Invert24To16

 Inverts an 8.24 value to a 16.16 value
 ====================
 */

fixed16_t Invert24To16(fixed16_t val)
{
    if (val < 256)
        return (0xFFFFFFFF);

    return (fixed16_t) (((QDFLOAT) 0x10000 * (QDFLOAT) 0x1000000 / (QDFLOAT) val) + 0.5);
}
#if PROFILE_SQRTF
int numSqrtf = 0;
#endif

#endif
