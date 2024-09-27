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
// r_misc.c
#include "quakedef.h"
#include "r_local.h"

/*
 ===============
 R_CheckVariables
 ===============
 */
void R_CheckVariables(void)
{
    static float oldbright;

    if (r_fullbright != oldbright)
    {
        oldbright = r_fullbright;
#if SURF_CACHE
		D_FlushCaches ();	// so all lighting changes
#endif
    }
}

/*
 ============
 Show

 Debugging use
 ============
 */
void Show(void)
{
    vrect_t vr;

    vr.x = vr.y = 0;
    vr.width = vid.width;
    vr.height = vid.height;
    vr.pnext = NULL;
    VID_Update(&vr);
}

/*
 ====================
 R_TimeRefresh_f

 For program optimization
 ====================
 */
void R_TimeRefresh_f(void)
{
    int i;
    float start, stop, time;
    int startangle;
    vrect_t vr;

    startangle = _g->r_refdef.viewangles[1];

    start = Sys_FloatTime();
    for (i = 0; i < 128; i++)
    {
        _g->r_refdef.viewangles[1] = i / 128.0 * 360.0;

        VID_LockBuffer ();

        R_RenderView();

        VID_UnlockBuffer ();

        vr.x = _g->r_refdef.vrect.x;
        vr.y = _g->r_refdef.vrect.y;
        vr.width = _g->r_refdef.vrect.width;
        vr.height = _g->r_refdef.vrect.height;
        vr.pnext = NULL;
        VID_Update(&vr);
    }
    stop = Sys_FloatTime();
    time = stop - start;
    Con_Printf("%d milliseconds (%d mfps)\n", 1000 * time, 128 / time);

    _g->r_refdef.viewangles[1] = startangle;
}

/*
 ================
 R_LineGraph

 Only called by R_DisplayTime
 ================
 */
void R_LineGraph(int x, int y, int h)
{
    int i;
    byte *dest;
    int s;

// FIXME: should be disabled on no-buffer adapters, or should be in the driver

    x += _g->r_refdef.vrect.x;
    y += _g->r_refdef.vrect.y;

    dest = vid.buffer + vid.rowbytes * y + x;

    s = r_graphheight;

    if (h > s)
        h = s;

    for (i = 0; i < h; i++, dest -= vid.rowbytes * 2)
    {
        dest[0] = 0xff;
        *(dest - vid.rowbytes) = 0x30;
    }
    for (; i < s; i++, dest -= vid.rowbytes * 2)
    {
        dest[0] = 0x30;
        *(dest - vid.rowbytes) = 0x30;
    }
}

/*
 ==============
 R_TimeGraph

 Performance monitoring tool
 ==============
 */
#define	MAX_TIMINGS		100
#if WIN32
extern float mouse_x, mouse_y;
#endif
void R_TimeGraph(void)
{
#if HAS_TIMEGRAPH
	static	int		timex;
	int		a;
	float	r_time2;
	static byte	r_timings[MAX_TIMINGS];
	int		x;

	r_time2 = Sys_FloatTime ();

	a = (r_time2-r_time1)/0.01;
//a = fabs(mouse_y * 0.05);
//a = (int)((_g->r_refdef.vieworg[2] + 1024)/1)%(int)r_graphheight;
//a = fabs(velocity[0])/20;
//a = ((int)fabs(origin[0])/8)%20;
//a = (cl.idealpitch + 30)/5;
	r_timings[timex] = a;
	a = timex;

	if (_g->r_refdef.vrect.width <= MAX_TIMINGS)
		x = _g->r_refdef.vrect.width-1;
	else
		x = _g->r_refdef.vrect.width -
				(_g->r_refdef.vrect.width - MAX_TIMINGS)/2;
	do
	{
		R_LineGraph (x, _g->r_refdef.vrect.height-2, r_timings[a]);
		if (x==0)
			break;		// screen too small to hold entire thing
		x--;
		a--;
		if (a == -1)
			a = MAX_TIMINGS-1;
	} while (a != timex);

	timex = (timex+1)%MAX_TIMINGS;
	#endif
}

/*
 =============
 R_PrintTimes
 =============
 */
void R_PrintTimes(void)
{
#if PROFILE_SPEED
    static int maxPixAlias = 0;
    if (maxPixAlias < pixAlias)
    {
        printf("pixalias: %d\r\n", pixAlias);
        FIXME("new max pix alias");
        maxPixAlias = pixAlias;
    }
	float	r_time2;
	float		ms;

	r_time2 = Sys_FloatTime ();

	ms = 1000* (r_time2 - r_time1);
#if COUNT_FACE_CLIP
  Con_Printf ("%3.5f ms fc %3i pc %3i dpc %3i c_surf %3i pl %i spl %i ps %i us %f alias %d (max %d)\n",
        ms, c_faceclip, r_polycount, r_drawnpolycount, c_surf, pixLoaded, singlePixelLoaded, pixSaved, pixLoadMicrosecs, pixAlias, maxPixAlias);

#else
	Con_Printf ("%3.5f ms fc %3i pc %3i dpc %3i c_surf %3i pl %i spl %i ps %i us %f alias %d (max %d)\n",
				ms, 0, r_polycount, r_drawnpolycount, c_surf, pixLoaded, singlePixelLoaded, pixSaved, pixLoadMicrosecs, pixAlias, maxPixAlias);
#endif
	c_surf = 0;
	pixLoaded = 0;
	singlePixelLoaded =0;  pixSaved = 0;
    pixLoadMicrosecs = 0;
#endif

}

/*
 =============
 R_PrintDSpeeds
 =============
 */
void R_PrintDSpeeds(void)
{
#if PROFILE_SPEED

  float	ms, dp_time, r_time2, rw_time, db_time, se_time, de_time, dv_time;

	r_time2 = Sys_FloatTime ();

	dp_time = (dp_time2 - dp_time1) * 1000;
	rw_time = (rw_time2 - rw_time1) * 1000;
	db_time = (db_time2 - db_time1) * 1000;
	se_time = (se_time2 - se_time1) * 1000;
	de_time = (de_time2 - de_time1) * 1000;
	dv_time = (dv_time2 - dv_time1) * 1000;
	ms = (r_time2 - r_time1) * 1000;

	Con_Printf ("%3i %4.1fp %3iw %4.1fb %3is %4.1fe %4.1fv\n",
				(int)ms, dp_time, (int)rw_time, db_time, (int)se_time, de_time,
				dv_time);
#endif
}

/*
 =============
 R_PrintAliasStats
 =============
 */
void R_PrintAliasStats(void)
{
    Con_Printf("%3i polygon model drawn\n", _g->r_amodels_drawn);
}


/*
 ===================
 R_TransformFrustum
 ===================
 */
void R_TransformFrustum(void)
{
    int i;
    vec3_t v, v2;

    for (i = 0; i < 4; i++)
    {
        v[0] = screenedge[i].normal[2];
        v[1] = -screenedge[i].normal[0];
        v[2] = screenedge[i].normal[1];

        v2[0] = v[1] * _g->vright[0] + v[2] * _g->vup[0] + v[0] * _g->vpn[0];
        v2[1] = v[1] * _g->vright[1] + v[2] * _g->vup[1] + v[0] * _g->vpn[1];
        v2[2] = v[1] * _g->vright[2] + v[2] * _g->vup[2] + v[0] * _g->vpn[2];
#if !CLIP_PLANE_USES_FLOAT
        view_clipplanes[i].frac_normal[0] = v2[0] * (1 << CLIP_PLANE_FRACBITS);
        view_clipplanes[i].frac_normal[1] = v2[1] * (1 << CLIP_PLANE_FRACBITS);
        view_clipplanes[i].frac_normal[2] = v2[2] * (1 << CLIP_PLANE_FRACBITS);
		//VectorCopy (v2, view_clipplanes[i].frac_normal);
		view_clipplanes[i].frac_dist = DotProduct (_g->modelorg, v2) * (1 << CLIP_PLANE_FRACBITS);
#else
        VectorCopy(v2, _g->view_clipplanes[i].normal);
        _g->view_clipplanes[i].dist = DotProduct(_g->modelorg, v2);
#endif // !CLIP_PLANE_USES_FLOAT
    }
}

#if	!id386

/*
 ================
 TransformVector
 ================
 */
//inlined
#endif

/*
 ================
 R_TransformPlane
 ================
 */
void R_TransformPlane(mplane_t *p, float *normal, float *dist)
{
    float d;

    d = DotProduct(_g->r_origin, p->normal);
    *dist = getPlaneDist(p) - d;
// TODO: when we have rotating entities, this will need to use the view matrix
    TransformVector(p->normal, normal);
}

/*
 ===============
 R_SetUpFrustumIndexes
 ===============
 */
void R_SetUpFrustumIndexes(void)
{
    int i, j, *pindex;

    pindex = r_frustum_indexes;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
#if CLIP_PLANE_USES_FLOAT
            if (_g->view_clipplanes[i].normal[j] < 0)
#else
			if (view_clipplanes[i].frac_normal[j] < 0)
#endif
            {
                pindex[j] = j;
                pindex[j + 3] = j + 3;
            }
            else
            {
                pindex[j] = j + 3;
                pindex[j + 3] = j;
            }
        }

        // FIXME: do just once at start
        pfrustum_indexes[i] = pindex;
        pindex += 6;
    }
}

/*
 ===============
 R_SetupFrame
 ===============
 */
void R_SetupFrame(void)
{
    vrect_t vrect;

// don't allow cheats in multiplayer
#if !DIRECT_SINGLE_PLAYER
	if (_g->cl.maxclients > 1)
	{
		Cvar_Set ("r_draworder", "0");
		Cvar_Set ("r_fullbright", "0");
		Cvar_Set ("r_ambient", "0");
		Cvar_Set ("r_drawflat", "0");
	}
#endif
#if WIN32
    int edgecount;

	if (r_numsurfs)
    {
        if ((_g->surface_p - _g->surfaces) > r_maxsurfsseen)
            r_maxsurfsseen = _g->surface_p - _g->surfaces;

        Con_Printf("Used %d of %d surfs; %d max\n", _g->surface_p - _g->surfaces, _g->surf_max - _g->surfaces, r_maxsurfsseen);
    }

    if (r_numedges)
    {
        edgecount = _g->edge_p - _g->r_edges;

        if (edgecount > r_maxedgesseen)
            r_maxedgesseen = edgecount;

        Con_Printf("Used %d of %d edges; %d max\n", edgecount,
        NUMSTACKEDGES, r_maxedgesseen);
    }
#endif
    _g->r_refdef.ambientlight = r_ambient;

    if (_g->r_refdef.ambientlight < 0)
        _g->r_refdef.ambientlight = 0;

    if (!sv.active)
        r_draworder = 0;	// don't let cheaters look behind walls

    R_CheckVariables();

    R_AnimateLight();

#if USE_R_FRAMECOUNT
	r_framecount++;
#endif
#if r_drawpolys
	numbtofpolys = 0;
#endif
// debugging
#if 0
_g->r_refdef.vieworg[0]=  80;
_g->r_refdef.vieworg[1]=      64;
_g->r_refdef.vieworg[2]=      40;
_g->r_refdef.viewangles[0]=    0;
_g->r_refdef.viewangles[1]=    46.763641357;
_g->r_refdef.viewangles[2]=    0;
#endif

// build the transformation matrix for the given view angles
    VectorCopy(_g->r_refdef.vieworg, _g->modelorg);
    VectorCopy(_g->r_refdef.vieworg, _g->r_origin);

    AngleVectors(_g->r_refdef.viewangles, _g->vpn, _g->vright, _g->vup);

// current viewleaf
    r_oldviewleaf = r_viewleaf;
    r_viewleaf = Mod_PointInLeaf(_g->r_origin, _g->cl.worldmodel);

    r_dowarpold = r_dowarp;
    r_dowarp = r_waterwarp && (r_viewleaf->contents <= CONTENTS_WATER);

    if ((r_dowarp != r_dowarpold))
    {
        Sbar_Changed(); // next-hack: required, as if we go from warp to nowarp we need to change palette.
        if (r_viewchanged || lcd_x)
        {
            if (r_dowarp)
            {
#if 0
			if ((vid.width <= vid.maxwarpwidth) &&
				(vid.height <= vid.maxwarpheight))
			{
				vrect.x = 0;
				vrect.y = 0;
				vrect.width = vid.width;
				vrect.height = vid.height;

				R_ViewChanged (&vrect, sb_lines, vid.aspect);
			}
			else
			{
				w = vid.width;
				h = vid.height;

				if (w > vid.maxwarpwidth)
				{
					h *= (float)vid.maxwarpwidth / w;
					w = vid.maxwarpwidth;
				}

				if (h > vid.maxwarpheight)
				{
					h = vid.maxwarpheight;
					w *= (float)vid.maxwarpheight / h;
				}

				vrect.x = 0;
				vrect.y = 0;
				vrect.width = (int)w;
				vrect.height = (int)h;

				R_ViewChanged (&vrect,
							   (int)((float)sb_lines * (h/(float)vid.height)),
							   vid.aspect * (h / w) *
								 ((float)vid.width / (float)vid.height));
			}
#else
                vrect.x = 0;
                vrect.y = 0;
                vrect.width = vid.width;
                vrect.height = vid.height;
                R_ViewChanged(&vrect, sb_lines, vid.aspect);
#endif
            }
            else
            {
                vrect.x = 0;
                vrect.y = 0;
                vrect.width = vid.width;
                vrect.height = vid.height;

                R_ViewChanged(&vrect, sb_lines, vid.aspect);
            }

            r_viewchanged = false;
        }
    }

// start off with just the four screen edge clip planes
    R_TransformFrustum();

// save base values
    VectorCopy(_g->vpn, _g->base_vpn);
    VectorCopy(_g->vright, _g->base_vright);
    VectorCopy(_g->vup, _g->base_vup);
    VectorCopy(_g->modelorg, _g->base_modelorg);

    R_SetSkyFrame();

    R_SetUpFrustumIndexes();
#if SURF_CACHE
	r_cache_thrash = false;
#endif
// clear frame counts
#if COUNT_FACE_CLIP
	c_faceclip = 0;
#endif
#if PROFILE_SPEED
	d_spanpixcount = 0;
	r_polycount = 0;
	r_drawnpolycount = 0;
	r_wholepolycount = 0;
#endif
    _g->r_amodels_drawn = 0;
    r_outofsurfaces = 0;
    r_outofedges = 0;

    D_SetupFrame();
}

