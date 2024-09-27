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
// r_edge.c
#include "quakedef.h"
#include "r_local.h"
#if 0
// FIXME
the complex cases add new polys on most lines, so dont optimize for keeping them the same
have multiple free span lists to try to get better coherence?
low depth complexity -- 1 to 3 or so

this breaks spans at every edge, even hidden ones (bad)

have a sentinal at both ends?
#endif

static inline void R_GenerateSpans(void);
//void R_GenerateSpansBackward (void);

static inline void R_LeadingEdge(const edge_t *edge);
//void R_LeadingEdgeBackwards (edge_t *edge);
static inline void R_TrailingEdge(surf_t *surf, edge_t *edge);

//=============================================================================

/*
 ==============
 R_BeginEdgeFrame
 ==============
 */
const msurface_t bkgsurf =
{ .flags = SURF_DRAWBACKGROUND
};
void R_BeginEdgeFrame(void)
{
    int v;

    _g->edge_p = _g->r_edges;
    _g->edge_max = &_g->r_edges[NUMSTACKEDGES];
    _g->surface_p = &_g->surfaces[2];	// background is surface 1,
    //  surface 0 is a dummy
#if OLD_SPAN_METHOD
	surfaces[1].spans = NULL;	// no background spans yet
#else
    setSurfSpans(&_g->surfaces[1], NULL);
#endif
    //surfaces[1].flags = SURF_DRAWBACKGROUND;
    _g->surfaces[1].data = (void*) &bkgsurf;

// put the background behind everything in the world
#if 0
	if (r_draworder)
	{
		pdrawfunc = R_GenerateSpansBackward;
		r_currentkey = 1;
	}
	else
#endif
    {
#if 0
	  pdrawfunc = R_GenerateSpans;
#endif
        _g->surfaces[1].key = MAX_SURFACE_KEY;
        _g->r_currentkey = 0;
    }

// FIXME: set with memset
    for (v = _g->r_refdef.vrect.y; v < _g->r_refdef.vrectbottom; v++)
    {
        _g->newedges[v] = _g->removeedges[v] = NULL;
    }
}

#if	!id386

/*
 ==============
 R_InsertNewEdges

 Adds the edges in the linked list edgestoadd, adding them to the edges in the
 linked list edgelist.  edgestoadd is assumed to be sorted on u, and non-empty (this is actually newedges[v]).  edgelist is assumed to be sorted on u, with a
 sentinel at the end (actually, this is the active edge table starting at
 edge_head.next).
 ==============
 */
#define FASTER_WAY 1
#if EDGE_POINTERS
void R_InsertNewEdges (edge_t *edgestoadd, edge_t *edgelist)
{
	edge_t	*next_edge;

	do
	{
		next_edge = edgestoadd->next;
edgesearch:
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
		edgelist=edgelist->next;
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
		edgelist=edgelist->next;
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
		edgelist=edgelist->next;
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
		edgelist=edgelist->next;
		goto edgesearch;

	// insert edgestoadd before edgelist
addedge:
		edgestoadd->next = edgelist;
		edgestoadd->prev = edgelist->prev;
		edgelist->prev->next = edgestoadd;
		edgelist->prev = edgestoadd;
	} while ((edgestoadd = next_edge) != NULL);
}
#elif FASTER_WAY
void R_InsertNewEdges(edge_t *edgestoadd, edge_t *edgelist)
{
#if WIN32
  edge_t  *next_edge;
  edge_t *edges = _g->base_edge_p;
  do
  {
#if EDGE_POINTERS
    next_edge = edgestoadd->next;
#else
        next_edge = &edges[edgestoadd->NextIdx];
#endif

edgesearch:
    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    if (edgelist->u >= edgestoadd->u)
      goto addedge;
    edgelist= &edges[edgelist->NextIdx];

    goto edgesearch;

  // insert edgestoadd before edgelist
addedge:
  //    setEdgeNext(edgestoadd, edgelist);
    edgestoadd->NextIdx = edgelist - edges;
    edgestoadd->PrevIdx = edgelist->PrevIdx;
    setEdgeNext(&edges[edgelist->PrevIdx], edgestoadd);
    //edges[edgelist->PrevIdx].NextIdx = edgestoadd - edges;
    edgelist->PrevIdx = edgestoadd - edges;

  } while ((edgestoadd = next_edge) != edges);
#else
    int edgeListU, edgeToAddU;
    int nextIdx, next_edge;
    int edgeListPrevIdx;
    int pBaseEdgeU = (int) ((byte*) _g->base_edge_p + offsetof(edge_t, u));

#if 0
  int tmp;
  __ASM volatile
  (
      "loopAddEdge%=:\n\t"
      // next_edge = &edges[edgestoadd->NextIdx]; (placed here to exploit pipelining)is recycled as nextIdx
      "LDR %[edgeToAddU], [%[pEdgesToAddU]]\n\t"   // load u of current edge to add
      "LDRH %[next_edge], [%[pEdgesToAddU], %[offsetNextIndexU]]\n\t"  // edgeToAddU
      "B firstEdgeSearch%=\n\t"
      "edgeSearch%=:\n\t"
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "firstEdgeSearch%=:\n\t"
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"     // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t" // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
       "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR.W %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BGE addEdge%=\n\t"
      // edgelist= &edges[edgelist->NextIdx];
      "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"       // note size of edge must be 16!
      "LDR %[edgeListU], [%[pEdgeListU]]\n\t"                          // load the current u of current edge in the list
      "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"     // speculatively load nextIdx
      // if (edgelist->u >= edgestoadd->u)
      "CMP %[edgeListU], %[edgeToAddU]\n\t"
      "BLT edgeSearch%=\n\t"                                           // goto edgesearch

      "addEdge%=:\n\t"

      //      edgestoadd->NextIdx = edgelist - edges;
      // (tmp = current index)
      "SUB %[tmp], %[pEdgeListU], %[pBaseEdgeU]\n\t"
      "ASR %[tmp], %[tmp], #4\n\t"             // note size of edge must be 16!
      "LDRH %[edgeListPrevIdx], [%[pEdgeListU], %[offsetPrevIndexU]]\n\t" // placed here to exploit pipelining
      "STRH %[tmp], [%[pEdgesToAddU], %[offsetNextIndexU]]\n\t"
      //      edgestoadd->PrevIdx = edgelist->PrevIdx;
      "STRH %[edgeListPrevIdx], [%[pEdgesToAddU], %[offsetPrevIndexU]]\n\t"
      // setEdgeNext(&edges[edgelist->PrevIdx], edgestoadd);
      // this is: get edgeList->PrevIdx (already have), left shift 4, and set its next to edgeAdd
      "ADD %[edgeListPrevIdx], %[pBaseEdgeU], %[edgeListPrevIdx], LSL #4\n\t"       // note size of edge must be 16!
      // now in edgeListPrevIdx we have &edges[edgelist->PrevIdx]
      "SUB %[tmp], %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
      "ASR %[tmp], %[tmp], #4\n\t"             // note size of edge must be 16!
      "STRH %[tmp], [%[edgeListPrevIdx], %[offsetNextIndexU]]\n\t"
      // edgelist->PrevIdx = edgestoadd - edges (already have);
      "STRH %[tmp], [%[pEdgeListU], %[offsetPrevIndexU]]\n\t"
      // compute next edge to add
      "ADD %[pEdgesToAddU], %[pBaseEdgeU], %[next_edge], LSL #4\n\t"       // note size of edge must be 16!
      // } while ((edgestoadd = next_edge) != edges);
      "CMP %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
      "BNE loopAddEdge%=\n\t"
     : // outputs, or in-outs
       [pBaseEdgeU] "+r" (pBaseEdgeU),
       [pEdgeListU] "+r" ((byte*) edgelist + offsetof(edge_t, u)),
       [edgeListU] "+r" (edgeListU),
       [edgeToAddU] "+r" (edgeToAddU),
       [nextIdx] "+r" (nextIdx),
       [pEdgesToAddU] "+r" (edgestoadd),
       [edgeListPrevIdx] "+r" (edgeListPrevIdx),
       [tmp] "+r" (tmp),
       [next_edge] "+r" (next_edge)
     : // input-only
       [offsetNextIndexU] "I" (offsetof(edge_t, NextIdx) - offsetof(edge_t, u)),
       [offsetPrevIndexU] "I" (offsetof(edge_t, PrevIdx) - offsetof(edge_t, u))
       : // colbber list
        "cc"
  );
#else
    __ASM volatile
    (
        ".align(2)\n\t"
        "loopAddEdge%=:\n\t"
        // next_edge = &edges[edgestoadd->NextIdx]; (placed here to exploit pipelining)is recycled as nextIdx
        "LDR %[edgeToAddU], [%[pEdgesToAddU]]\n\t"// load u of current edge to add
        "LDRH %[next_edge], [%[pEdgesToAddU], %[offsetNextIndexU]]\n\t"// rembember next edge index
        //
        "edgeSearch%=:\n\t"
        "LDR %[edgeListUorTmp], [%[pEdgeListU]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge%=\n\t"
        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU2], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU2]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU2], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge2%=\n\t"
#define UNROLL8 0
#if UNROLL8
        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge%=\n\t"

        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU2], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU2]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU2], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge2%=\n\t"

        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge%=\n\t"

        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU2], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU2]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU2], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge2%=\n\t"
#endif
        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BGE addEdge%=\n\t"

        // edgelist= &edges[edgelist->NextIdx];
        "ADD %[pEdgeListU2], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "LDR %[edgeListUorTmp], [%[pEdgeListU2]]\n\t"// load the current u of current edge in the list
        "LDRH %[nextIdx], [%[pEdgeListU2], %[offsetNextIndexU]]\n\t"// speculatively load nextIdx
        // if (edgelist->u >= edgestoadd->u)
        "ADD %[pEdgeListU], %[pBaseEdgeU], %[nextIdx], LSL #4\n\t"// note size of edge must be 16!
        "CMP %[edgeListUorTmp], %[edgeToAddU]\n\t"
        "BLT edgeSearch%=\n\t"

        "addEdge2%=:\n\t"

        // we must put in pEdgeList the pEdgeList2
        "MOVS %[pEdgeListU], %[pEdgeListU2]\n\t"
        "SUBS %[edgeListUorTmp], %[pEdgeListU2], %[pBaseEdgeU]\n\t"// get index of current edgeList
        "ASR.W %[edgeListUorTmp], %[edgeListUorTmp], #4\n\t"// Index is difference/size. note size of edge must be 16!
        "LDRH.W %[edgeListPrevIdx], [%[pEdgeListU2], %[offsetPrevIndexU]]\n\t"// load edgeList->PrevIdx placed here to exploit pipelining
        "STRH.W %[edgeListUorTmp], [%[pEdgesToAddU], %[offsetNextIndexU]]\n\t"
        //      edgestoadd->PrevIdx = edgelist->PrevIdx;
        "STRH.W %[edgeListPrevIdx], [%[pEdgesToAddU], %[offsetPrevIndexU]]\n\t"
        // setEdgeNext(&edges[edgelist->PrevIdx], edgestoadd);
        // this is: get edgeList->PrevIdx (already have), left shift 4, and set its next to edgeAdd
        // now in edgeListPrevIdx we have &edges[edgelist->PrevIdx]
        "SUB.W %[edgeListUorTmp], %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
        "ADD %[edgeListPrevIdx], %[pBaseEdgeU], %[edgeListPrevIdx], LSL #4\n\t"// note size of edge must be 16!
        "ASR.W %[edgeListUorTmp], %[edgeListUorTmp], #4\n\t"// note size of edge must be 16!
        "STRH.W %[edgeListUorTmp], [%[edgeListPrevIdx], %[offsetNextIndexU]]\n\t"
        // edgelist->PrevIdx = edgestoadd - edges (already have);
        "STRH.W %[edgeListUorTmp], [%[pEdgeListU2], %[offsetPrevIndexU]]\n\t"

        // compute next edge to add
        "ADD.W %[pEdgesToAddU], %[pBaseEdgeU], %[next_edge], LSL #4\n\t"// note size of edge must be 16!
        // } while ((edgestoadd = next_edge) != edges);
        "CMP %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
        "BNE loopAddEdge%=\n\t"
        "B.W done%=\n\t"

        "addEdge%=:\n\t"

        //      edgestoadd->NextIdx = edgelist - edges;
        // (tmp = current index)
        "SUB.W %[edgeListUorTmp], %[pEdgeListU], %[pBaseEdgeU]\n\t"
        "ASR.W %[edgeListUorTmp], %[edgeListUorTmp], #4\n\t"// note size of edge must be 16!
        "LDRH.W %[edgeListPrevIdx], [%[pEdgeListU], %[offsetPrevIndexU]]\n\t"// placed here to exploit pipelining
        "STRH.W %[edgeListUorTmp], [%[pEdgesToAddU], %[offsetNextIndexU]]\n\t"
        //      edgestoadd->PrevIdx = edgelist->PrevIdx;
        "STRH.W %[edgeListPrevIdx], [%[pEdgesToAddU], %[offsetPrevIndexU]]\n\t"
        // setEdgeNext(&edges[edgelist->PrevIdx], edgestoadd);
        // this is: get edgeList->PrevIdx (already have), left shift 4, and set its next to edgeAdd
        "ADD.W %[edgeListPrevIdx], %[pBaseEdgeU], %[edgeListPrevIdx], LSL #4\n\t"// note size of edge must be 16!
        // now in edgeListPrevIdx we have &edges[edgelist->PrevIdx]
        "SUB.W %[edgeListUorTmp], %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
        "ASR.W %[edgeListUorTmp], %[edgeListUorTmp], #4\n\t"// note size of edge must be 16!
        "STRH.W %[edgeListUorTmp], [%[edgeListPrevIdx], %[offsetNextIndexU]]\n\t"
        // edgelist->PrevIdx = edgestoadd - edges (already have);
        "STRH.W %[edgeListUorTmp], [%[pEdgeListU], %[offsetPrevIndexU]]\n\t"
        // compute next edge to add
        "ADD.W %[pEdgesToAddU], %[pBaseEdgeU], %[next_edge], LSL #4\n\t"// note size of edge must be 16!
        // } while ((edgestoadd = next_edge) != edges);
        "CMP %[pEdgesToAddU], %[pBaseEdgeU]\n\t"
        "BNE loopAddEdge%=\n\t"
        "done%=:\n\t"
        :// outputs, or in-outs
        [pEdgeListU] "+r" ((byte*) edgelist + offsetof(edge_t, u)),
        [pEdgeListU2] "=&r" ((byte*) edgelist + offsetof(edge_t, u)),
        [edgeListUorTmp] "=&l" (edgeListU),
        [edgeToAddU] "=&h" (edgeToAddU),
        [nextIdx] "=&l" (nextIdx),
        [pEdgesToAddU] "+r" (edgestoadd),
        [edgeListPrevIdx] "=&r" (edgeListPrevIdx),
        [next_edge] "=&h" (next_edge)
        :// input-only
        [pBaseEdgeU] "r" ((byte*) pBaseEdgeU + offsetof(edge_t, u)),
        [offsetNextIndexU] "I" (offsetof(edge_t, NextIdx) - offsetof(edge_t, u)),
        [offsetPrevIndexU] "I" (offsetof(edge_t, PrevIdx) - offsetof(edge_t, u))
        :// colbber list
        "cc", "memory"
    );

#endif
#endif
}
#else
void R_InsertNewEdges (edge_t *edgestoadd, edge_t *edgelist)
{
	edge_t	*next_edge;

	do
	{
#if EDGE_POINTERS
		next_edge = edgestoadd->next;
#else
        next_edge = getEdgeNext(edgestoadd);
#endif
edgesearch:
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
#if EDGE_POINTERS
		edgelist=edgelist->next;
#else
		edgelist=getEdgeNext(edgelist);
#endif
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
#if EDGE_POINTERS
		edgelist=edgelist->next;
#else
		edgelist=getEdgeNext(edgelist);
#endif
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
#if EDGE_POINTERS
		edgelist=edgelist->next;
#else
		edgelist=getEdgeNext(edgelist);
#endif
		if (edgelist->u >= edgestoadd->u)
			goto addedge;
#if EDGE_POINTERS
		edgelist=edgelist->next;
#else
		edgelist=getEdgeNext(edgelist);
#endif
		goto edgesearch;

	// insert edgestoadd before edgelist
addedge:
#if EDGE_POINTERS
		edgestoadd->next = edgelist;
		edgestoadd->prev = edgelist->prev;
		edgelist->prev->next = edgestoadd;
		edgelist->prev = edgestoadd;

#else
        setEdgeNext(edgestoadd, edgelist);
		setEdgePrev(edgestoadd, getEdgePrev(edgelist));
		setEdgeNext(getEdgePrev(edgelist), edgestoadd);
		setEdgePrev(edgelist, edgestoadd);

#endif

	} while ((edgestoadd = next_edge) != NULL);
}
#endif
#endif	// !id386

#if	!id386

/*
 ==============
 R_RemoveEdges
 ==============
 */
#if FASTER_WAY
void R_RemoveEdges(edge_t *pedge)
{
#if EDGE_POINTERS
  do
  {
    pedge->next->prev = pedge->prev;
    pedge->prev->next = pedge->next;
  } while ((pedge = pedge->nextremove) != NULL);
#else
#if 0
  do
  {
    _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
  } while ((pedge = &_g->base_edge_p[pedge->NextRemoveIdx]) != _g->base_edge_p);
#else
    while (1)
    {
#if EDGE_HAS_NEXTREMOVEIDX
    _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
    pedge = &_g->base_edge_p[pedge->NextRemoveIdx];
    if (pedge == _g->base_edge_p)
      break;
    _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
    pedge = &_g->base_edge_p[pedge->NextRemoveIdx];
    if (pedge == _g->base_edge_p)
      break;
    _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
    pedge = &_g->base_edge_p[pedge->NextRemoveIdx];
    if (pedge == _g->base_edge_p)
      break;
    _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
    pedge = &_g->base_edge_p[pedge->NextRemoveIdx];
    if (pedge == _g->base_edge_p)
      break;
#else
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
        pedge = getEdgeNextRemove(pedge, 0);
        if (pedge == _g->base_edge_p)
            break;
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
        pedge = getEdgeNextRemove(pedge, 0);
        if (pedge == _g->base_edge_p)
            break;
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
        pedge = getEdgeNextRemove(pedge, 0);
        if (pedge == _g->base_edge_p)
            break;
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;
        pedge = getEdgeNextRemove(pedge, 0);
        if (pedge == _g->base_edge_p)
            break;

#endif
    }
#endif
#endif
}

#else
void R_RemoveEdges (edge_t *pedge)
{
#if EDGE_POINTERS
	do
	{
		pedge->next->prev = pedge->prev;
		pedge->prev->next = pedge->next;
	} while ((pedge = pedge->nextremove) != NULL);
#else
	do
	{
		setEdgePrev(getEdgeNext(pedge), getEdgePrev(pedge));
		setEdgeNext(getEdgePrev(pedge), getEdgeNext(pedge));
	} while ((pedge = getEdgeNextRemove(pedge)) != NULL);

#endif
}
#endif

#endif	// !id386

#if	!id386

/*
 ==============
 R_StepActiveU
 ==============
 */
 #if EDGE_POINTERS
static inline  void R_StepActiveU (edge_t *pedge)
{
	edge_t		*pnext_edge, *pwedge;

	while (1)
	{
nextedge:
		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		goto nextedge;

pushback:
		if (pedge == _g->edge_aftertail)
			return;

	// push it back to keep it sorted
		pnext_edge = pedge->next;

	// pull the edge out of the edge list
		pedge->next->prev = pedge->prev;
		pedge->prev->next = pedge->next;

	// find out where the edge goes in the edge list
		pwedge = pedge->prev->prev;

		while (pwedge->u > pedge->u)
		{
			pwedge = pwedge->prev;
		}

	// put the edge back into the edge list
		pedge->next = pwedge->next;
		pedge->prev = pwedge;
		pedge->next->prev = pedge;
		pwedge->next = pedge;

		pedge = pnext_edge;
		if (pedge == _g->edge_tail)
			return;
	}
}

#elif FASTER_WAY
static inline void R_StepActiveU(edge_t *pedge)
{
    edge_t *pnext_edge, *pwedge;

    while (1)
    {
#if EDGE_POINTERS
nextedge:
    pedge->u += pedge->u_step;
    if (pedge->u < pedge->prev->u)
      goto pushback;
    pedge = pedge->next;

    pedge->u += pedge->u_step;
    if (pedge->u < pedge->prev->u)
      goto pushback;
    pedge = pedge->next;

    pedge->u += pedge->u_step;
    if (pedge->u < pedge->prev->u)
      goto pushback;
    pedge = pedge->next;

    pedge->u += pedge->u_step;
    if (pedge->u < pedge->prev->u)
      goto pushback;
    pedge = pedge->next;

    goto nextedge;

pushback:
    if (pedge == &_g->edge_aftertail)
      return;

  // push it back to keep it sorted
    pnext_edge = pedge->next;

  // pull the edge out of the edge list
    pedge->next->prev = pedge->prev;
    pedge->prev->next = pedge->next;

  // find out where the edge goes in the edge list
    pwedge = pedge->prev->prev;

    while (pwedge->u > pedge->u)
    {
      pwedge = pwedge->prev;
    }

  // put the edge back into the edge list
    pedge->next = pwedge->next;
    pedge->prev = pwedge;
    pedge->next->prev = pedge;
    pwedge->next = pedge;

    pedge = pnext_edge;
    if (pedge == _g->edge_tail)
      return;
#elif OLD_WAY
    nextedge:
        pedge->u += pedge->u_step;
        if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
          goto pushback;
        pedge = &_g->base_edge_p[pedge->NextIdx];

        pedge->u += pedge->u_step;
        if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
          goto pushback;
        pedge = getEdgeNext(pedge);

        pedge->u += pedge->u_step;
        if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
          goto pushback;
        pedge = getEdgeNext(pedge);

        pedge->u += pedge->u_step;
        if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
          goto pushback;
        pedge = &_g->base_edge_p[pedge->NextIdx];

        goto nextedge;

    pushback:
        if (pedge == _g->edge_aftertail)
          return;

      // push it back to keep it sorted
        pnext_edge = &_g->base_edge_p[pedge->NextIdx];    // SHOULD I CHECK FOR NULL ?

      // pull the edge out of the edge list
    //    setEdgePrev(getEdgeNext(pedge), getEdgePrev(pedge));
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
    //    setEdgeNext(getEdgePrev(pedge), getEdgeNext(pedge));
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;

      // find out where the edge goes in the edge list
     //   pwedge = getEdgePrev(getEdgePrev(pedge));
        pwedge = &_g->base_edge_p[pedge->PrevIdx];
        while (pwedge->u > pedge->u)
        {
    //      pwedge = getEdgePrev(pwedge);
          pwedge = &_g->base_edge_p[pwedge->PrevIdx];
        }

      // put the edge back into the edge list
      //  setEdgeNext(pedge, getEdgeNext(pwedge));
        pedge->NextIdx = pwedge->NextIdx;
        //  setEdgePrev(pedge, pwedge);
        pedge->PrevIdx = pwedge - _g->base_edge_p;
      //  setEdgePrev(getEdgeNext(pedge), pedge);
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge - _g->base_edge_p;
       // setEdgeNext(pwedge, pedge);
        pwedge->NextIdx = pedge - _g->base_edge_p;
        pedge = pnext_edge;
        if (pedge == _g->edge_tail)
          return;

#else
        // next edge
        while (1)
        {
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
            pedge->u += pedge->u_step;
            if (pedge->u < _g->base_edge_p[pedge->PrevIdx].u)
                break;
            pedge = &_g->base_edge_p[pedge->NextIdx];
        }
        // pushback
        if (pedge == _g->edge_aftertail)
            return;

        // push it back to keep it sorted
        pnext_edge = &_g->base_edge_p[pedge->NextIdx];    // SHOULD I CHECK FOR NULL ?

        // pull the edge out of the edge list
        //    setEdgePrev(getEdgeNext(pedge), getEdgePrev(pedge));
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge->PrevIdx;
        //    setEdgeNext(getEdgePrev(pedge), getEdgeNext(pedge));
        _g->base_edge_p[pedge->PrevIdx].NextIdx = pedge->NextIdx;

        // find out where the edge goes in the edge list
        //   pwedge = getEdgePrev(getEdgePrev(pedge));
        pwedge = &_g->base_edge_p[pedge->PrevIdx];
        while (pwedge->u > pedge->u)
        {
            //      pwedge = getEdgePrev(pwedge);
            pwedge = &_g->base_edge_p[pwedge->PrevIdx];
        }

        // put the edge back into the edge list
        //  setEdgeNext(pedge, getEdgeNext(pwedge));
        pedge->NextIdx = pwedge->NextIdx;
        //  setEdgePrev(pedge, pwedge);
        pedge->PrevIdx = pwedge - _g->base_edge_p;
        //  setEdgePrev(getEdgeNext(pedge), pedge);
        _g->base_edge_p[pedge->NextIdx].PrevIdx = pedge - _g->base_edge_p;
        // setEdgeNext(pwedge, pedge);
        pwedge->NextIdx = pedge - _g->base_edge_p;
        pedge = pnext_edge;
        if (pedge == _g->edge_tail)
            return;

#endif
    }
}
#else
void R_StepActiveU (edge_t *pedge)
{
	edge_t		*pnext_edge, *pwedge;

	while (1)
	{
#if EDGE_POINTERS
nextedge:
		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		pedge->u += pedge->u_step;
		if (pedge->u < pedge->prev->u)
			goto pushback;
		pedge = pedge->next;

		goto nextedge;

pushback:
		if (pedge == &edge_aftertail)
			return;

	// push it back to keep it sorted
		pnext_edge = pedge->next;

	// pull the edge out of the edge list
		pedge->next->prev = pedge->prev;
		pedge->prev->next = pedge->next;

	// find out where the edge goes in the edge list
		pwedge = pedge->prev->prev;

		while (pwedge->u > pedge->u)
		{
			pwedge = pwedge->prev;
		}

	// put the edge back into the edge list
		pedge->next = pwedge->next;
		pedge->prev = pwedge;
		pedge->next->prev = pedge;
		pwedge->next = pedge;

		pedge = pnext_edge;
		if (pedge == &edge_tail)
			return;
#else
nextedge:
		pedge->u += pedge->u_step;
		if (pedge->u < getEdgePrev(pedge, 0)->u)
			goto pushback;
		pedge = getEdgeNext(pedge, 0);

		pedge->u += pedge->u_step;
		if (pedge->u < getEdgePrev(pedge, 0)->u)
			goto pushback;
		pedge = getEdgeNext(pedge, 0);

		pedge->u += pedge->u_step;
		if (pedge->u < getEdgePrev(pedge, 0)->u)
			goto pushback;
		pedge = getEdgeNext(pedge, 0);

		pedge->u += pedge->u_step;
		if (pedge->u < getEdgePrev(pedge, 0)->u)
			goto pushback;
		pedge = getEdgeNext(pedge, 0);

		goto nextedge;

pushback:
		if (pedge == _g->edge_aftertail)
			return;

	// push it back to keep it sorted
		pnext_edge = getEdgeNext(pedge, 1);

	// pull the edge out of the edge list
		setEdgePrev(getEdgeNext(pedge, 1), getEdgePrev(pedge, 1));
		setEdgeNext(getEdgePrev(pedge, 1), getEdgeNext(pedge, 1));

	// find out where the edge goes in the edge list
		pwedge = getEdgePrev(getEdgePrev(pedge, 1), 1);

		while (pwedge->u > pedge->u)
		{
			pwedge = getEdgePrev(pwedge, 1);
		}

	// put the edge back into the edge list
		setEdgeNext(pedge, getEdgeNext(pwedge, 1));
		setEdgePrev(pedge, pwedge);
		setEdgePrev(getEdgeNext(pedge, 1), pedge);
		setEdgeNext(pwedge, pedge);

		pedge = pnext_edge;
		if (pedge == _g->edge_tail)
			return;

#endif
	}
}
#endif
#endif	// !id386

/*
 ==============
 R_CleanupSpan
 ==============
 */
#if FASTER_WAY
void R_CleanupSpan()
{
    surf_t *surf;
    int iu;
    espan_t *span;

// now that we've reached the right edge of the screen, we're done with any
// unfinished surfaces, so emit a span for whatever's on top
#if SURF_HAS_PREV_NEXT
  surf = surfaces[1].next;
#else
    surf = getSurfNext(&_g->surfaces[1], 0);
#endif
    iu = _g->edge_tail_u_shift20;
    if (iu > surf->last_u)
    {
        span = _g->span_p++;
        span->u = surf->last_u;
        span->count = iu - span->u;

#if !ESPANS_HAVE_V
        int spanIndex = span - _g->basespan_p;
        _g->basespanV_p[spanIndex] = _g->current_iv;
#else
    span->v = _g->current_iv;
#endif
#if OLD_SPAN_METHOD
    span->pnext = surf->spans;
    surf->spans = span;
#else
        span->nextSpanIdx = surf->spansIdx;
        surf->spansIdx = span - _g->basespan_p;
#endif
    }
#if 0
// reset spanstate for all surfaces in the surface stack
  do
  {
    surf->spanstate = 0;
#if SURF_HAS_PREV_NEXT
    surf = surf->next;
#else
    surf = &_g->base_surf_p[surf->NextIdx];
#endif
  } while (surf != &_g->surfaces[1]);
#else
    // reset spanstate for all surfaces in the surface stack

    while (1)
    {
        surf->spanstate = 0;
        if (surf->NextIdx == 1)
            break;
        surf = &_g->base_surf_p[surf->NextIdx];

        surf->spanstate = 0;
        if (surf->NextIdx == 1)
            break;
        surf = &_g->base_surf_p[surf->NextIdx];

        surf->spanstate = 0;
        if (surf->NextIdx == 1)
            break;
        surf = &_g->base_surf_p[surf->NextIdx];

        surf->spanstate = 0;
        if (surf->NextIdx == 1)
            break;
        surf = &_g->base_surf_p[surf->NextIdx];
    }
#endif
}
#else
void R_CleanupSpan ()
{
	surf_t	*surf;
	int		iu;
	espan_t	*span;

// now that we've reached the right edge of the screen, we're done with any
// unfinished surfaces, so emit a span for whatever's on top
#if SURF_HAS_PREV_NEXT
	surf = surfaces[1].next;
#else
    surf = getSurfNext(&surfaces[1]);
#endif
	iu = edge_tail_u_shift20;
	if (iu > surf->last_u)
	{
		span = span_p++;
		span->u = surf->last_u;
		span->count = iu - span->u;
		span->v = current_iv;
#if OLD_SPAN_METHOD
		span->pnext = surf->spans;
		surf->spans = span;
#else
    setNextSpan(span, getSurfSpans(surf));
		setSurfSpans(surf, span);
#endif
	}

// reset spanstate for all surfaces in the surface stack
	do
	{
		surf->spanstate = 0;
#if SURF_HAS_PREV_NEXT
		surf = surf->next;
#else
    surf = getSurfNext(surf);
#endif
	} while (surf != &surfaces[1]);
}
#endif

#if 0
/*
==============
R_LeadingEdgeBackwards
==============
*/
void R_LeadingEdgeBackwards (edge_t *edge)
{
	espan_t			*span;
	surf_t			*surf, *surf2;
	int				iu;

// it's adding a new surface in, so find the correct place
#if EDGE_SURF_ARRAY
	surf = &surfaces[edge->surfs[1]];
#else
	surf = &_g->surfaces[edge->surf1];
#endif
// don't start a span if this is an inverted span, with the end
// edge preceding the start edge (that is, we've already seen the
// end edge)
	if (++surf->spanstate == 1)
	{
#if SURF_HAS_PREV_NEXT
		surf2 = surfaces[1].next;
#else
        surf2 = getSurfNext(&_g->surfaces[1]);
#endif
		if (surf->key > surf2->key)
			goto newtop;

	// if it's two surfaces on the same plane, the one that's already
	// active is in front, so keep going unless it's a bmodel
		if (surf->insubmodel && (surf->key == surf2->key))
		{
		// must be two bmodels in the same leaf; don't care, because they'll
		// never be farthest anyway
			goto newtop;
		}

continue_search:

		do
		{
#if SURF_HAS_PREV_NEXT
			surf2 = surf2->next;
#else
            surf2 = getSurfNext(surf2);
#endif
		} while (surf->key < surf2->key);

		if (surf->key == surf2->key)
		{
		// if it's two surfaces on the same plane, the one that's already
		// active is in front, so keep going unless it's a bmodel
			if (!surf->insubmodel)
				goto continue_search;

		// must be two bmodels in the same leaf; don't care which is really
		// in front, because they'll never be farthest anyway
		}

		goto gotposition;

newtop:
	// emit a span (obscures current top)
		iu = edge->u >> 20;

		if (iu > surf2->last_u)
		{
			span = _g->span_p++;
			span->u = surf2->last_u;
			span->count = iu - span->u;
			span->v = _g->current_iv;
#if OLD_SPAN_METHOD
			span->pnext = surf2->spans;
			surf2->spans = span;
#else
            setNextSpan(span, getSurfSpans(surf2));
			setSurfSpans(surf2, span);
#endif
		}

		// set last_u on the new span
		surf->last_u = iu;

gotposition:
	// insert before surf2
#if SURF_HAS_PREV_NEXT
		surf->next = surf2;
		surf->prev = surf2->prev;
		surf2->prev->next = surf;
		surf2->prev = surf;
#else
		setSurfNext(surf, surf2);
		setSurfPrev(surf, getSurfPrev(surf2));
		setSurfNext(getSurfPrev(surf2), surf);
		setSurfPrev(surf2, surf);

#endif
	}
}

#endif
/*
 ==============
 R_TrailingEdge
 ==============
 */
#if FASTER_WAY
__attribute__ ((always_inline)) static inline void R_TrailingEdge(surf_t *surf, edge_t *edge)
{
    espan_t *span;
    int iu;

// don't generate a span if this is an inverted span, with the end
// edge preceding the start edge (that is, we haven't seen the
// start edge yet)
    if (--surf->spanstate == 0)
    {
#if BMODEL_STAT
    if (surf->insubmodel)
      r_bmodelactive--;
#endif
#if SURF_HAS_PREV_NEXT
    if (surf == surfaces[1].next)
#else
        if (surf == &_g->base_surf_p[_g->surfaces[1].NextIdx])
#endif
        {
            // emit a span (current top going away)
            iu = edge->u >> 20;
            if (iu > surf->last_u)
            {
                span = _g->span_p++;
                span->u = surf->last_u;
                span->count = iu - span->u;

#if !ESPANS_HAVE_V
                int spanIndex = span - _g->basespan_p;
                _g->basespanV_p[spanIndex] = _g->current_iv;
#else
                span->v = _g->current_iv;
#endif

#if OLD_SPAN_METHOD
                span->pnext = surf->spans;
                surf->spans = span;
#else
                //        setNextSpan(span, getSurfSpans(surf));
                span->nextSpanIdx = surf->spansIdx;
                //       setSurfSpans(surf, span);
                surf->spansIdx = span - _g->basespan_p;
#endif
            }

            // set last_u on the surface below
#if SURF_HAS_PREV_NEXT
            surf->next->last_u = iu;
#else
            _g->base_surf_p[surf->NextIdx].last_u = iu;
#endif
        }
#if SURF_HAS_PREV_NEXT
    surf->prev->next = surf->next;
    surf->next->prev = surf->prev;
#else
        //  setSurfNext(getSurfPrev(surf), getSurfNext(surf));
        _g->base_surf_p[surf->PrevIdx].NextIdx = surf->NextIdx;
        //  setSurfPrev(getSurfNext(surf), getSurfPrev(surf));
        _g->base_surf_p[surf->NextIdx].PrevIdx = surf->PrevIdx;

#endif
    }
}
#else
void R_TrailingEdge (surf_t *surf, edge_t *edge)
{
	espan_t			*span;
	int				iu;

// don't generate a span if this is an inverted span, with the end
// edge preceding the start edge (that is, we haven't seen the
// start edge yet)
	if (--surf->spanstate == 0)
	{
		if (surf->insubmodel)
			r_bmodelactive--;
#if SURF_HAS_PREV_NEXT
		if (surf == surfaces[1].next)
#else
		if (surf == getSurfNext(&_g->surfaces[1]))
#endif
		{
		// emit a span (current top going away)
			iu = edge->u >> 20;
			if (iu > surf->last_u)
			{
				span = _g->span_p++;
				span->u = surf->last_u;
				span->count = iu - span->u;
				span->v = _g->current_iv;
#if OLD_SPAN_METHOD
				span->pnext = surf->spans;
				surf->spans = span;
#else
                setNextSpan(span, getSurfSpans(surf));
                setSurfSpans(surf, span);

#endif
			}

		// set last_u on the surface below
#if SURF_HAS_PREV_NEXT
			surf->next->last_u = iu;
#else
            getSurfNext(surf)->last_u = iu;
#endif
		}
#if SURF_HAS_PREV_NEXT
		surf->prev->next = surf->next;
		surf->next->prev = surf->prev;
#else
		setSurfNext(getSurfPrev(surf), getSurfNext(surf));
		setSurfPrev(getSurfNext(surf), getSurfPrev(surf));

#endif
	}
}
#endif

#if	!id386

/*
 ==============
 R_LeadingEdge
 ==============
 */
#if FASTER_WAY
static inline void R_LeadingEdge(const edge_t *edge)
{
    espan_t *span;
    surf_t *surf, *surf2;
    int iu;
    QDFLOAT fu, newzi, testzi, newzitop, newzibottom;
#if EDGE_SURF_ARRAY
  if (edge->surfs[1])
#else
  //  if (edge->surf1)  // next-hack: not sure why it was checked here and not outside the function.
#endif
    {
        // it's adding a new surface in, so find the correct place
#if EDGE_SURF_ARRAY
    surf = &surfaces[edge->surfs[1]];
#else
        surf = &_g->surfaces[edge->surf1];
#endif
        // don't start a span if this is an inverted span, with the end
        // edge preceding the start edge (that is, we've already seen the
        // end edge)
        if (++surf->spanstate == 1)
        {
            fu = (float) (edge->u - 0xFFFFF) * (1.0f / 0x100000);

#if BMODEL_STAT
      if (surf->insubmodel)
        r_bmodelactive++;
#endif
#if SURF_HAS_PREV_NEXT
      surf2 = surfaces[1].next;
#else
            surf2 = &_g->base_surf_p[_g->surfaces[1].NextIdx];
#endif
            if (surf->key < surf2->key)
                goto newtop;

            // if it's two surfaces on the same plane, the one that's already
            // active is in front, so keep going unless it's a bmodel
            if (surf->insubmodel && (surf->key == surf2->key))
            {
                // must be two bmodels in the same leaf; sort on 1/z
// moved up        fu = (float)(edge->u - 0xFFFFF) * (1.0f / 0x100000);
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
                newzi = surf->d_ziorigin + _g->fv * surf->d_zistepv + fu * surf->d_zistepu;
                newzibottom = newzi * 0.99f;
                testzi = surf2->d_ziorigin + _g->fv * surf2->d_zistepv + fu * surf2->d_zistepu;
#else
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
#warning we could optimize much more than this!
        newzi =  getSurfD_ziorigin(surf) + (_g->fv*surf->fixed_d_zistepv + fu * surf->fixed_d_zistepu) *  (1.0f / D_ZISTEP_PRECISION) ;
        newzibottom = newzi * 0.99f;
        testzi =  getSurfD_ziorigin(surf2) + (_g->fv*surf2->fixed_d_zistepv + fu * surf2->fixed_d_zistepu) *  (1.0f / D_ZISTEP_PRECISION) ;
#else
        newzi = surf->d_ziorigin + fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
        newzibottom = newzi * 0.99f;
        testzi = surf2->d_ziorigin + fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);
#endif
#endif
                if (newzibottom >= testzi)
                {
                    goto newtop;
                }

                newzitop = newzi * 1.01f;
                if (newzitop >= testzi)
                {
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
                    if (surf->d_zistepu >= surf2->d_zistepu)
#else
        //  if (getSurfD_zistepu(surf) >= getSurfD_zistepu(surf2))
            if (surf->fixed_d_zistepu >= surf2->fixed_d_zistepu)
#endif
#else
                    if ( temp_d_zistepu >= temp_d_zistepu2)
#endif
                    {
                        goto newtop;
                    }
                }
            }

            continue_search:

            do
            {
#if SURF_HAS_PREV_NEXT
        surf2 = surf2->next;
#else
                surf2 = &_g->base_surf_p[surf2->NextIdx];
#endif
            }
            while (surf->key > surf2->key);

            if (surf->key == surf2->key)
            {
                // if it's two surfaces on the same plane, the one that's already
                // active is in front, so keep going unless it's a bmodel
                if (!surf->insubmodel)
                    goto continue_search;

                // must be two bmodels in the same leaf; sort on 1/z
// moved up        fu = (float)(edge->u - 0xFFFFF) * (1.0f / 0x100000);
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
                newzi = surf->d_ziorigin + _g->fv * surf->d_zistepv + fu * surf->d_zistepu;
                newzibottom = newzi * 0.99f;
                testzi = surf2->d_ziorigin + _g->fv * surf2->d_zistepv + fu * surf2->d_zistepu;
#else
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
        newzi = getSurfD_ziorigin(surf) + (_g->fv*surf->fixed_d_zistepv + fu * surf->fixed_d_zistepu) *  (1.0f / D_ZISTEP_PRECISION) ;
        newzibottom = newzi * 0.99f;
        testzi = getSurfD_ziorigin(surf2) + (_g->fv*surf2->fixed_d_zistepv + fu * surf2->fixed_d_zistepu) *  (1.0f / D_ZISTEP_PRECISION) ;

#else
        newzi = surf->d_ziorigin + fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
        newzibottom = newzi * 0.99;
        testzi = surf2->d_ziorigin + fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);

#endif
#endif
                if (newzibottom >= testzi)
                {
                    goto gotposition;
                }

                newzitop = newzi * 1.01f;
                if (newzitop >= testzi)
                {
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
                    if (surf->d_zistepu >= surf2->d_zistepu)
#else
        //  if (getSurfD_zistepu(surf) >= getSurfD_zistepu(surf2))
            if(surf->fixed_d_zistepu >= surf2->fixed_d_zistepu)
#endif
#else
                    if ( temp_d_zistepu >= temp_d_zistepu2)
#endif
                    {
                        goto gotposition;
                    }
                }

                goto continue_search;
            }

            goto gotposition;

            newtop:
            // emit a span (obscures current top)
            iu = edge->u >> 20;

            if (iu > surf2->last_u)
            {
                span = _g->span_p++;
                span->u = surf2->last_u;
                span->count = iu - span->u;

#if !ESPANS_HAVE_V
                int spanIndex = span - _g->basespan_p;
                _g->basespanV_p[spanIndex] = _g->current_iv;
#else
    span->v = _g->current_iv;
#endif

#if OLD_SPAN_METHOD
        span->pnext = surf2->spans;
        surf2->spans = span;
#else
//                setNextSpan(span, getSurfSpans(surf2));
                span->nextSpanIdx = surf2->spansIdx;
//                setSurfSpans(surf2, span);
                surf2->spansIdx = span - _g->basespan_p;
#endif
            }

            // set last_u on the new span
            surf->last_u = iu;

            gotposition:
            // insert before surf2
#if SURF_HAS_PREV_NEXT
      surf->next = surf2;
      surf->prev = surf2->prev;
      surf2->prev->next = surf;
      surf2->prev = surf;
#else
            //   setSurfNext(surf, surf2);
            surf->NextIdx = surf2->surfIndex;
            //   setSurfPrev(surf, getSurfPrev(surf2));
            surf->PrevIdx = surf2->PrevIdx;
            //    setSurfNext(getSurfPrev(surf2), surf);
            _g->base_surf_p[surf2->PrevIdx].NextIdx = surf->surfIndex;
            //    setSurfPrev(surf2, surf);
            surf2->PrevIdx = surf->surfIndex;
#endif
        }
    }
}
#else
void R_LeadingEdge (edge_t *edge)
{
	espan_t			*span;
	surf_t			*surf, *surf2;
	int				iu;
	QDFLOAT			fu, newzi, testzi, newzitop, newzibottom;
#if EDGE_SURF_ARRAY
	if (edge->surfs[1])
#else
	if (edge->surf1)
#endif
	{
	// it's adding a new surface in, so find the correct place
#if EDGE_SURF_ARRAY
		surf = &surfaces[edge->surfs[1]];
#else
		surf = &_g->surfaces[edge->surf1];
#endif
	// don't start a span if this is an inverted span, with the end
	// edge preceding the start edge (that is, we've already seen the
	// end edge)
		if (++surf->spanstate == 1)
		{
			if (surf->insubmodel)
				r_bmodelactive++;
#if SURF_HAS_PREV_NEXT
			surf2 = surfaces[1].next;
#else
			surf2 = getSurfNext(&_g->surfaces[1]);
#endif
			if (surf->key < surf2->key)
				goto newtop;

		// if it's two surfaces on the same plane, the one that's already
		// active is in front, so keep going unless it's a bmodel
			if (surf->insubmodel && (surf->key == surf2->key))
			{
			// must be two bmodels in the same leaf; sort on 1/z
				fu = (float)(edge->u - 0xFFFFF) * (1.0f / 0x100000);
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
				newzi = surf->d_ziorigin + fv*surf->d_zistepv + fu*surf->d_zistepu;
				newzibottom = newzi * 0.99;
				testzi = surf2->d_ziorigin + fv*surf2->d_zistepv + fu*surf2->d_zistepu;
#else
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA

				newzi =  getSurfD_ziorigin(surf) + _g->fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
				newzibottom = newzi * 0.99f;
				testzi =  getSurfD_ziorigin(surf2) + _g->fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);
#else
				newzi = surf->d_ziorigin + fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
				newzibottom = newzi * 0.99;
				testzi = surf2->d_ziorigin + fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);
#endif
#endif
#else
    vec3_t tempPnormal;
    float *tempModelOrg;
    tempModelOrg = modelorg;
    mplane_t *tempPlane = ((msurface_t*) surf->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	float temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;
    //
    tempPlane = ((msurface_t*) surf2->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu2 = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv2 = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin2 =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;


    newzi = temp_d_ziorigin + fv*temp_d_zistepv + fu*temp_d_zistepu;
    newzibottom = newzi * 0.99;
    testzi = temp_d_ziorigin2 + fv*temp_d_zistepv2 + fu*temp_d_zistepu2;

#endif
				if (newzibottom >= testzi)
				{
					goto newtop;
				}

				newzitop = newzi * 1.01f;
				if (newzitop >= testzi)
				{
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
					if (surf->d_zistepu >= surf2->d_zistepu)
#else
					if (getSurfD_zistepu(surf) >= getSurfD_zistepu(surf2))
#endif
#else
                    if ( temp_d_zistepu >= temp_d_zistepu2)
#endif
					{
						goto newtop;
					}
				}
			}

continue_search:

			do
			{
#if SURF_HAS_PREV_NEXT
				surf2 = surf2->next;
#else
                surf2 = getSurfNext(surf2);
#endif
			} while (surf->key > surf2->key);

			if (surf->key == surf2->key)
			{
			// if it's two surfaces on the same plane, the one that's already
			// active is in front, so keep going unless it's a bmodel
				if (!surf->insubmodel)
					goto continue_search;

			// must be two bmodels in the same leaf; sort on 1/z
				fu = (float)(edge->u - 0xFFFFF) * (1.0f / 0x100000);
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
				newzi = surf->d_ziorigin + fv*surf->d_zistepv + fu*surf->d_zistepu;
				newzibottom = newzi * 0.99;
				testzi = surf2->d_ziorigin + fv*surf2->d_zistepv + fu*surf2->d_zistepu;
#else
#if SURF_HAS_FIXED_D_ZIORIGIN_DATA
				newzi = getSurfD_ziorigin(surf) + _g->fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
				newzibottom = newzi * 0.99f;
				testzi = getSurfD_ziorigin(surf2) + _g->fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);

#else
				newzi = surf->d_ziorigin + fv*getSurfD_zistepv(surf) + fu*getSurfD_zistepu(surf);
				newzibottom = newzi * 0.99;
				testzi = surf2->d_ziorigin + fv*getSurfD_zistepv(surf2) + fu*getSurfD_zistepu(surf2);

#endif
#endif
#else
vec3_t tempPnormal;
    float *tempModelOrg;
    tempModelOrg = modelorg;
    mplane_t *tempPlane = ((msurface_t*) surf->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	float temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;
    //
    tempPlane = ((msurface_t*) surf2->data)->plane;
	TransformVector (tempPlane->normal, tempPnormal);
	temp_distinv = 1.0 / (tempPlane->dist - DotProduct (tempModelOrg, tempPlane->normal));
	float temp_d_zistepu2 = tempPnormal[0] * xscaleinv * temp_distinv;
	float temp_d_zistepv2 = -tempPnormal[1] * yscaleinv * temp_distinv;
    float temp_d_ziorigin2 =  tempPnormal[2] * temp_distinv -	xcenter * temp_d_zistepu - ycenter * temp_d_zistepv;

    newzi = temp_d_ziorigin + fv*temp_d_zistepv + fu*temp_d_zistepu;
    newzibottom = newzi * 0.99;
    testzi = temp_d_ziorigin2 + fv*temp_d_zistepv2 + fu*temp_d_zistepu2;
#endif
				if (newzibottom >= testzi)
				{
					goto gotposition;
				}

				newzitop = newzi * 1.01f;
				if (newzitop >= testzi)
				{
#if SURF_HAS_D_ZI_DATA
#if !SURF_HAS_FIXED_D_ZISTEP_DATA
					if (surf->d_zistepu >= surf2->d_zistepu)
#else
					if (getSurfD_zistepu(surf) >= getSurfD_zistepu(surf2))
#endif
#else
                    if ( temp_d_zistepu >= temp_d_zistepu2)
#endif
					{
						goto gotposition;
					}
				}

				goto continue_search;
			}

			goto gotposition;

newtop:
		// emit a span (obscures current top)
			iu = edge->u >> 20;

			if (iu > surf2->last_u)
			{
				span = _g->span_p++;
				span->u = surf2->last_u;
				span->count = iu - span->u;
				span->v = _g->current_iv;
#if OLD_SPAN_METHOD
				span->pnext = surf2->spans;
				surf2->spans = span;
#else
                setNextSpan(span, getSurfSpans(surf2));
                setSurfSpans(surf2, span);
#endif
			}

			// set last_u on the new span
			surf->last_u = iu;

gotposition:
		// insert before surf2
#if SURF_HAS_PREV_NEXT
			surf->next = surf2;
			surf->prev = surf2->prev;
			surf2->prev->next = surf;
			surf2->prev = surf;
#else
            setSurfNext(surf, surf2);
			setSurfPrev(surf, getSurfPrev(surf2));
			setSurfNext(getSurfPrev(surf2), surf);
			setSurfPrev(surf2, surf);

#endif
		}
	}
}
#endif

/*
 ==============
 R_GenerateSpans
 ==============
 */
static inline void R_GenerateSpans(void)
{
    edge_t *edge;
    surf_t *surf;
#if BMODEL_STAT
	r_bmodelactive = 0;
#endif
// clear active surfaces to just the background surface
#if SURF_HAS_PREV_NEXT
	surfaces[1].next = surfaces[1].prev = &surfaces[1];
#else
    _g->surfaces[1].NextIdx = 1;
    _g->surfaces[1].PrevIdx = 1;
#endif
    _g->surfaces[1].last_u = _g->edge_head_u_shift20;
// generate spans
#if EDGE_POINTERS
	for (edge=_g->edge_head->next ; edge != _g->edge_tail; edge=edge->next)
#else
    for (edge = &_g->base_edge_p[_g->edge_head->NextIdx]; edge != _g->edge_tail; edge = &_g->base_edge_p[edge->NextIdx])
#endif
    {
#if EDGE_SURF_ARRAY
		if (edge->surfs[0])
#else
        if (edge->surf0)
#endif
        {
            // it has a left surface, so a surface is going away for this span
#if EDGE_SURF_ARRAY
			surf = &surfaces[edge->surfs[0]];
#else
            surf = &_g->surfaces[edge->surf0];
#endif
            R_TrailingEdge(surf, edge);
#if EDGE_SURF_ARRAY
			if (!edge->surfs[1])
				continue;
#else
#if 0
            if (!edge->surf1)
                continue;
#endif
#endif
        }
#if 1
		// next-hack: added the check here. It was in R_LeadingEdge.
        if (!edge->surf1)
            continue;

#endif
        R_LeadingEdge(edge);
    }

    R_CleanupSpan();
}

#endif	// !id386

#if 0
/*
==============
R_GenerateSpansBackward
==============
*/
void R_GenerateSpansBackward (void)
{
	edge_t			*edge;

	r_bmodelactive = 0;

// clear active surfaces to just the background surface
#if SURF_HAS_PREV_NEXT
	surfaces[1].next = surfaces[1].prev = &surfaces[1];
#else
    setSurfNext(&_g->surfaces[1], &_g->surfaces[1]);
    setSurfPrev(&_g->surfaces[1], &_g->surfaces[1]);
#endif

    _g->surfaces[1].last_u = _g->edge_head_u_shift20;

// generate spans
#if EDGE_POINTERS
	for (edge=edge_head.next ; edge != &edge_tail; edge=edge->next)
#else
	for (edge=getEdgeNext(_g->edge_head) ; edge != _g->edge_tail; edge = getEdgeNext(edge))
#endif
	{
#if EDGE_SURF_ARRAY
		if (edge->surfs[0])
			R_TrailingEdge (&surfaces[edge->surfs[0]], edge);

		if (edge->surfs[1])
			R_LeadingEdgeBackwards (edge);
#else
		if (edge->surf0)
			R_TrailingEdge (&_g->surfaces[edge->surf0], edge);

		if (edge->surf1)
			R_LeadingEdgeBackwards (edge);

#endif
	}

	R_CleanupSpan ();
}
#endif

/*
 ==============
 R_ScanEdges

 Input:
 newedges[] array
 this has links to edges, which have links to surfaces

 Output:
 Each surface has a linked list of its visible spans
 ==============
 */
#if SEPARATE_SPAN_NEXT
    short *nextSpanIndexes_p;
#endif
#define Z_BUFFER_SIZE                           (SCREEN_WIDTH * DRAW_BUFFER_HEIGHT * sizeof(d_zbuffer[0]))
#define STATUS_BAR_BUFFER_SIZE                  (SCREEN_WIDTH * (SCREEN_HEIGHT - DRAW_BUFFER_HEIGHT))
#define NEW_AND_REMOVE_EDGE_SIZE                (sizeof(edge_t*) * 2 * MAXHEIGHT)
#define EDGE_SIZE                               (sizeof(edge_t) * (NUMSTACKEDGES + 5))
#if EDGE_POINTERS
#define EDGE_NEXT_REMOVE_IDX_SIZE               0
#else
#define EDGE_NEXT_REMOVE_IDX_SIZE               (sizeof(uint16_t) * (NUMSTACKEDGES + 6))
#endif
#if WIN32
extern byte* VGA_pagebase;
#endif // WIN32
#define MAX_Y_FOR_RESTORE_EDGES  ((int) ((Z_BUFFER_SIZE - STATUS_BAR_BUFFER_SIZE - NEW_AND_REMOVE_EDGE_SIZE - EDGE_SIZE - EDGE_NEXT_REMOVE_IDX_SIZE) / SCREEN_WIDTH / sizeof(d_zbuffer[0]) - 1))

#define COPY_COLORS_TO_FRAME_BUFFER    0

#if COPY_COLORS_TO_FRAME_BUFFER
void copyColorsToRam(void)
{
  uint64_t *src = vid.colormap;
#if !WIN32
  uint64_t *dst = (byte*) displayData.displayFrameBuffer + MAX_Y_FOR_RESTORE_EDGES * 320;
#else
  uint64_t *dst = (byte*) VGA_pagebase + MAX_Y_FOR_RESTORE_EDGES * 320;
#endif
  vid.colormap = dst;
  for (int i = 0; i < 16384; i+=8)
  {
    *dst++ =  *src++;
  }
}
#endif
void R_ScanEdges(void)
{
    int iv, bottom;
    byte basespans[MAXSPANS * sizeof(espan_t)];
    // next-hack: added this to prevent compiler complaining a pointer is outside bounds
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    _g->basespan_p = (espan_t*) basespans - 1;
#pragma GCC diagnostic pop
#if !ESPANS_HAVE_V
    byte baseSpansV[MAXSPANS + 1];
    _g->basespanV_p = (byte*) &baseSpansV[0];
#endif
    surf_t *s;

#if !OLD_SPAN_METHOD
#if SEPARATE_SPAN_NEXT
	short nextSpanIndexes[MAXSPANS] = {0};
	nextSpanIndexes_p = nextSpanIndexes;
#else
//    basespan_p->nextSpanIdx = 0;
#endif
#endif
    _g->max_span_p = &_g->basespan_p[MAXSPANS - _g->r_refdef.vrect.width];
#if OLD_SPAN_METHOD
	span_p = basespan_p ;
#else
    _g->span_p = _g->basespan_p + 1; // 0 is considered null
#endif
// clear active edges to just the background edges around the whole screen
// FIXME: most of this only needs to be set up once
#if EDGE_POINTERS  // head, tail, aftertail and sentinel edges are now in stack.
	_g->edge_head->u = _g->r_refdef.vrect.x << 20;
	_g->edge_head_u_shift20 = _g->edge_head->u >> 20;
	_g->edge_head->u_step = 0;
	_g->edge_head->prev = NULL;
	_g->edge_head->next = _g->edge_tail;
	_g->edge_head->surf0 = 0;
	_g->edge_head->surf1 = 1;

	_g->edge_tail->u = (_g->r_refdef.vrectright << 20) + 0xFFFFF;
	_g->edge_tail_u_shift20 = _g->edge_tail->u >> 20;
	_g->edge_tail->u_step = 0;
	_g->edge_tail->prev = _g->edge_head;
	_g->edge_tail->next = _g->edge_aftertail;
	_g->edge_tail->surf0 = 1;
	_g->edge_tail->surf1 = 0;

	_g->edge_aftertail->u = -1;		// force a move
	_g->edge_aftertail->u_step = 0;
	_g->edge_aftertail->next = _g->edge_sentinel;
	_g->edge_aftertail->prev = _g->edge_tail;

// FIXME: do we need this now that we clamp x in r_draw.c?
	_g->edge_sentinel->u = 127 << 24;		// make sure nothing sorts past this
	_g->edge_sentinel->prev = _g->edge_aftertail;
#else
    _g->edge_head->u = _g->r_refdef.vrect.x << 20;
    _g->edge_head_u_shift20 = _g->edge_head->u >> 20;
    _g->edge_head->u_step = 0;
    setEdgePrev(_g->edge_head, NULL);
    setEdgeNext(_g->edge_head, _g->edge_tail);
#if EDGE_SURF_ARRAY
	edge_head->surfs[0] = 0;
	edge_head->surfs[1] = 1;
#else
    _g->edge_head->surf0 = 0;
    _g->edge_head->surf1 = 1;
#endif
    _g->edge_tail->u = (_g->r_refdef.vrectright << 20) + 0xFFFFF;
    _g->edge_tail_u_shift20 = _g->edge_tail->u >> 20;
    _g->edge_tail->u_step = 0;
    setEdgePrev(_g->edge_tail, _g->edge_head);
    setEdgeNext(_g->edge_tail, _g->edge_aftertail);
#if EDGE_SURF_ARRAY
	edge_tail->surfs[0] = 1;
	edge_tail->surfs[1] = 0;
#else
    _g->edge_tail->surf0 = 1;
    _g->edge_tail->surf1 = 0;
#endif
    _g->edge_aftertail->u = -1;		// force a move
    _g->edge_aftertail->u_step = 0;
    setEdgeNext(_g->edge_aftertail, _g->edge_sentinel);
    setEdgePrev(_g->edge_aftertail, _g->edge_tail);

// FIXME: do we need this now that we clamp x in r_draw.c?
    _g->edge_sentinel->u = 20 << 24;		// make sure nothing sorts past this
    setEdgePrev(_g->edge_sentinel, _g->edge_aftertail);

#endif
//
// process all scan lines
//
    bottom = _g->r_refdef.vrectbottom - 1;
#if WIN32 
    static int maxedges = 0;
    if (maxedges < _g->edge_p - _g->base_edge_p)
        maxedges = _g->edge_p - _g->base_edge_p;
    printf("EDGES IN THIS FRAME: %d, max %d\r\n", _g->edge_p - _g->base_edge_p, maxedges);
#endif

#if COPY_COLORS_TO_FRAME_BUFFER
    byte *oldColorMap = vid.colormap;
    qboolean colorCopied = false;
#endif // COPY_COLORS_TO_FRAME_BUFFER

    for (iv = _g->r_refdef.vrect.y; iv < bottom; iv++)
    {
        _g->current_iv = iv;
        _g->fv = (float) iv;

        // mark that the head (background start) span is pre-included
        _g->surfaces[1].spanstate = 1;

        if (_g->newedges[iv])
        {
#if EDGE_POINTERS
			R_InsertNewEdges (_g->newedges[iv], _g->edge_head->next);
#else
            R_InsertNewEdges(_g->newedges[iv], getEdgeNext(_g->edge_head, 1));
#endif

            }
        //(*pdrawfunc) ();
        R_GenerateSpans();
        // flush the span list if we can't be sure we have enough spans left for
        // the next scan

        if (_g->span_p >= _g->max_span_p || iv == MAX_Y_FOR_RESTORE_EDGES)
        {

            D_DrawSurfaces();
            if (iv > MAX_Y_FOR_RESTORE_EDGES)
            {
#if WIN32
              printf("BLEAH\r\n"); // This message is clear, isn't it ?
#endif
                return;
            }
            // clear the surface span pointers
            for (s = &_g->surfaces[1]; s < _g->surface_p;)
            { // if odd, then one more. If even, then ok, because surfaces[1] is actually the start of the array
                setSurfSpans(s++, NULL);
                setSurfSpans(s++, NULL);
            }
            _g->span_p = _g->basespan_p + 1;
        }

        if (_g->removeedges[iv])
        {
            R_RemoveEdges(_g->removeedges[iv]);
        }
#if EDGE_POINTERS
		if (_g->edge_head->next != _g->edge_tail)
        {
			R_StepActiveU (_g->edge_head->next);
        }

#else
        if (getEdgeNext(_g->edge_head, 0) != _g->edge_tail)
        {
            R_StepActiveU(getEdgeNext(_g->edge_head, 1));
        }
#endif
    }

// do the last scan (no need to step or sort or remove on the last scan)

    _g->current_iv = iv;
    _g->fv = (float) iv;

// mark that the head (background start) span is pre-included
    _g->surfaces[1].spanstate = 1;

    if (_g->newedges[iv])
#if EDGE_POINTERS
		R_InsertNewEdges (_g->newedges[iv], _g->edge_head->next);
#else
        R_InsertNewEdges(_g->newedges[iv], getEdgeNext(_g->edge_head, 1));
#endif
    R_GenerateSpans();
// draw whatever's left in the span list
#if (r_drawculledpolys)      // this is false
		R_DrawCulledPolys ();
#else
#if !WIN32 // we check in draw z span and drawspan
    while (displayData.updateAll && displayData.dmaBusy)
    {
        // wait
    }
#endif

    D_DrawSurfaces();
#endif
//    printf("span used %d\r\n", span_p - basespan_p);
}

