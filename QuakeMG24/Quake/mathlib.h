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
// mathlib.h
#ifndef MATHLIB_H
#define MATHLIB_H

typedef float vec_t;
typedef vec_t vec3_t[3];
typedef vec_t vec5_t[5];

typedef int fixed4_t;
typedef int fixed8_t;
typedef int fixed16_t;

#ifndef M_PI
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h
#endif

struct mplane_s;

extern vec3_t vec3_origin;
extern int nanmask;

#define	IS_NAN(x) (((*((int *)&x))&nanmask)==nanmask)

#define DotProduct(x,y) (x[0]*y[0]+x[1]*y[1]+x[2]*y[2])
#define VectorSubtract(a,b,c) {c[0]=a[0]-b[0];c[1]=a[1]-b[1];c[2]=a[2]-b[2];}
#define VectorAdd(a,b,c) {c[0]=a[0]+b[0];c[1]=a[1]+b[1];c[2]=a[2]+b[2];}
#define VectorCopy(a,b) {b[0]=a[0];b[1]=a[1];b[2]=a[2];}
void VectorMA(vec3_t veca, float scale, vec3_t vecb, vec3_t vecc);

vec_t _DotProduct(vec3_t v1, vec3_t v2);
void _VectorSubtract(vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorAdd(vec3_t veca, vec3_t vecb, vec3_t out);
void _VectorCopy(vec3_t in, vec3_t out);
int VectorCompare(vec3_t v1, vec3_t v2);
//vec_t Length (vec3_t v);
//void CrossProduct (vec3_t v1, vec3_t v2, vec3_t cross);
//float VectorNormalize (vec3_t v);		// returns vector length
//void VectorInverse (vec3_t v);
//void VectorScale (vec3_t in, vec_t scale, vec3_t out);
int Q_log2(int val);

void R_ConcatRotations(float in1[3][3], float in2[3][3], float out[3][3]);
void R_ConcatTransforms(float in1[3][4], float in2[3][4], float out[3][4]);

void FloorDivMod(QDFLOAT numer, QDFLOAT denom, int *quotient, int *rem);
fixed16_t Invert24To16(fixed16_t val);
int GreatestCommonDivisor(int i1, int i2);

//void AngleVectors (vec3_t angles, vec3_t forward, vec3_t right, vec3_t up);
int BoxOnPlaneSide(vec3_t emins, vec3_t emaxs, struct mplane_s *plane);
float anglemod(float a);

static inline void CrossProduct(vec3_t v1, vec3_t v2, vec3_t cross)
{
    cross[0] = v1[1] * v2[2] - v1[2] * v2[1];
    cross[1] = v1[2] * v2[0] - v1[0] * v2[2];
    cross[2] = v1[0] * v2[1] - v1[1] * v2[0];
}
static inline void AngleVectors(vec3_t angles, vec3_t forward, vec3_t right, vec3_t up)
{
    float angle;
    float sr, sp, sy, cr, cp, cy;

    angle = angles[YAW] * (M_PI * 2 / 360);
    sy = sin_t(angle);
    cy = cos_t(angle);
    angle = angles[PITCH] * (M_PI * 2 / 360);
    sp = sin_t(angle);
    cp = cos_t(angle);
    angle = angles[ROLL] * (M_PI * 2 / 360);
    sr = sin_t(angle);
    cr = cos_t(angle);

    forward[0] = cp * cy;
    forward[1] = cp * sy;
    forward[2] = -sp;
    right[0] = (-1 * sr * sp * cy + -1 * cr * -sy);
    right[1] = (-1 * sr * sp * sy + -1 * cr * cy);
    right[2] = -1 * sr * cp;
    up[0] = (cr * sp * cy + -sr * -sy);
    up[1] = (cr * sp * sy + -sr * cy);
    up[2] = cr * cp;
}

static inline __attribute__ ((pure)) vec_t Length(vec3_t v)
{
    int i;
    float length;

    length = 0;
    for (i = 0; i < 3; i++)
        length += v[i] * v[i];
    length = sqrtf(length);
    return length;
}

static inline float VectorNormalize(vec3_t v)
{
    float length, ilength;

    length = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
    length = sqrtf(length);

    if (length)
    {
        ilength = 1 / length;
        v[0] *= ilength;
        v[1] *= ilength;
        v[2] *= ilength;
    }

    return length;

}

static inline void VectorInverse(vec3_t v)
{
    v[0] = -v[0];
    v[1] = -v[1];
    v[2] = -v[2];
}

static inline void VectorScale(vec3_t in, vec_t scale, vec3_t out)
{
    out[0] = in[0] * scale;
    out[1] = in[1] * scale;
    out[2] = in[2] * scale;
}
#if !WIN32
static inline float ceilf_m(float f)
{
    float r;
    __asm volatile ("VRINTP.F32 %[out], %[in]\n\t" : [out] "=w" (r) : [in] "w" (f) : );
    return r;
}
#else
static inline float ceilf_m(float f)
{
  return ceilf(f);
}
#endif
#if !WIN32
static inline float floorf_m(float f)
{
    float r;
    __asm volatile ("VRINTM.F32 %[out], %[in]\n\t" : [out] "=w" (r) : [in] "w" (f) : );
    return r;
}
#else
static inline float floorf_m(float f)
{
  return floorf(f);
}
#endif
#if PROFILE_SQRTF
extern int numSqrtf;
#endif
#if !WIN32
static inline float fabsf_m(float f)
{
    float r;
    __asm volatile ("VABS.F32 %[out], %[in]\n\t" : [out] "=w" (r) : [in] "w" (f) : );
    return r;
}
#else
static inline float fabsf_m(float f)
{
  return fabsf(f);
}
#endif

static inline float sqrtf_m(float f)
{
#if PROFILE_SQRTF
    numSqrtf ++;
    #endif
#if WIN32
    return sqrtf(f);
#else
    float r;
    __asm volatile ("VSQRT.F32 %[out], %[in]\n\t" : [out] "=w" (r) : [in] "w" (f) : );
    return r;

#endif
}

#define BOX_ON_PLANE_SIDE(emins, emaxs, p)	\
	(((p)->type < 3)?						\
	(										\
		(getPlaneDist(p) <= (emins)[(p)->type])?	\
			1								\
		:									\
		(									\
			(getPlaneDist(p) >= (emaxs)[(p)->type])?\
				2							\
			:								\
				3							\
		)									\
	)										\
	:										\
		BoxOnPlaneSide( (emins), (emaxs), (p)))
#endif // MATHLIB_H
