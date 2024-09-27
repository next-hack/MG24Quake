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
// models.c -- model loading and caching
// models are the only shared resource between a client and server running
// on the same machine.
#include "quakedef.h"
#include "r_local.h"
#if WIN32
#include "extMemoryWin32.h"
#else
#include "extMemory.h"
#endif
#if WIN32
#include "SDL.h"
#endif
model_t *loadmodel;

void Mod_LoadSpriteModel(model_t *mod, void *buffer);
void Mod_LoadBrushModel(model_t *mod, void *buffer);
//void Mod_LoadAliasModel (model_t *mod, void *buffer);
model_t* Mod_LoadModel(model_t *mod, qboolean crash);

const byte mod_novis[MAX_MAP_LEAFS / 8] =
{ 0
};

model_t *mod_known; //[MAX_MOD_KNOWN];

//brush_model_data_t brushModelData[MAX_BRUSH_MODELS];
short mod_numknown;
uint8_t numberOfBrushModels = 0;
static uint8_t modelsFinalized = 0;
// values for model_t's needload
#define NL_PRESENT		0
#define NL_NEEDS_LOADED	1
#define NL_UNREFERENCED	2

/*
 ===============
 Mod_Init
 ===============
 */
void Mod_Init(void)
{
//	memset (mod_novis, 0xff, sizeof(mod_novis));
}

/*
 ===============
 Mod_Extradata

 Caches the data if needed
 ===============
 */
void* Mod_Extradata(model_t *mod)
{
    return mod->data;
}

/*
 ===============
 Mod_PointInLeaf
 ===============
 */
mleaf_t* Mod_PointInLeaf(vec3_t p, model_t *model)
{
    mnode_t *node;
    float d;
    mplane_t *plane;

#if !SEPARATE_BRUSH_MODEL_DATA
	if (!model || !model->nodes)
#else
    if (!model || !model->brushModelData->nodes)

#endif
        Sys_Error("Mod_PointInLeaf: bad model");
#if !SEPARATE_BRUSH_MODEL_DATA
	node = model->nodes;
#else
    node = model->brushModelData->nodes;
#endif
    while (1)
    {
        if (node->contents < 0)
            return (mleaf_t*) node;
#if NODE_HAS_PLANE_POINTER
        plane = node->plane;
#else
        plane = Mod_GetNodePlane(node, model);
#endif

        d = DotProduct (p,plane->normal) - getPlaneDist(plane);
#if NODE_HAS_CHILDREN_POINTERS
		if (d > 0)
			node = node->children[0];
		else
			node = node->children[1];
#else
        if (d > 0)
            node = Mod_GetChildNode(node, 0, model);
        else
            node = Mod_GetChildNode(node, 1, model);
#endif
    }

    return NULL;	// never reached
}

/*
 ===================
 Mod_DecompressVis
 ===================
 */
extern byte *decompressed; //next-hack: reusing tempbuffer (zbuffer) for this.
byte* Mod_DecompressVis(byte *in, model_t *model)
{
//	static byte	decompressed[MAX_MAP_LEAFS/8];  //next-hack: reusing tempbuffer (zbuffer) for this.
    int c;
    byte *out;
    int row;
#if !SEPARATE_BRUSH_MODEL_DATA
	row = (model->numleafs+7)>>3;
#else
    row = (model->brushModelData->numleafs + 7) >> 3;
#endif
    out = decompressed;

    if (!in)
    {	// no vis info, so make all visible
        while (row)
        {
            *out++ = 0xff;
            row--;
        }
        return decompressed;
    }

    do
    {
        if (*in)
        {
            *out++ = *in++;
            continue;
        }

        c = in[1];
        in += 2;
        while (c)
        {
            *out++ = 0;
            c--;
        }
    }
    while (out - decompressed < row);

    return decompressed;
}

byte* Mod_LeafPVS(mleaf_t *leaf, model_t *model)
{
#if WIN32 && 0
        static mleaf_t *oldleaf;
        if (oldleaf == leaf)
        {
            printf("Host Frame %d, same leaf %p\r\n", host_framecount, leaf);
        }
        else
        {
            printf("Host Frame %d, different leaf %p\r\n", host_framecount, leaf);
        }
        oldleaf = leaf;
    #endif // WIN32
#if !SEPARATE_BRUSH_MODEL_DATA
	if (leaf == model->leafs)
#else
    if (leaf == model->brushModelData->leafs)
#endif
        return (byte*) mod_novis;
#if LEAF_HAS_COMPRESSED_VIS_POINTER
	return Mod_DecompressVis (leaf->compressed_vis, model);
#else
    if (leaf->compressed_vis_idx == 0xFFFF)
        return Mod_DecompressVis(NULL, model);
    else
#if !SEPARATE_BRUSH_MODEL_DATA
	    return Mod_DecompressVis (model->visdata + leaf->compressed_vis_idx, model);
#else
        return Mod_DecompressVis(model->brushModelData->visdata + leaf->compressed_vis_idx, model);
#endif
#endif
}

/*
 ===================
 Mod_ClearAll
 ===================
 */
void Mod_ClearAll(void)
{
    int i;
    model_t *mod;

    for (i = 0, mod = mod_known; i < mod_numknown; i++, mod++)
    {
        mod->needload = NL_UNREFERENCED;
//FIX FOR CACHE_ALLOC ERRORS:
        if (mod->type == mod_sprite)
            mod->data = NULL;
    }
//	Cache_Flush();
    // nh: added this.
    mod_numknown = 0;

    numberOfBrushModels = 0;
}

/*
 ==================
 Mod_FindName

 ==================
 */
model_t* Mod_FindName(const char *name)
{
    int i;
    model_t *mod;

    if (!name[0])
        Sys_Error("Mod_ForName: NULL name");
//
// search the currently loaded models
//
    for (i = 0, mod = mod_known; i < mod_numknown; i++, mod++)
    {
        if (!strcmp(mod->name, name))
            break;
    }

    if (i == mod_numknown)
    {
        if (mod_numknown == MAX_MOD_KNOWN)
        {
            FIXME("TOO MANY MODELS");
            Sys_Error("mod_numknown == MAX_MOD_KNOWN");
        }
        else
            mod_numknown++;
        //
        unsigned int len = strlen(name) + 1;
        if (len > MAX_QPATH)
        {
            Sys_Error("mod name too long");
        }
        mod->name = storeToInternalFlash(name, (len + 3) & ~3);
        mod->needload = NL_NEEDS_LOADED;
    }

    return mod;
}

/*
 ==================
 Mod_TouchModel

 ==================
 */
void Mod_TouchModel(char *name)
{
    Mod_FindName(name);
}
/*
 */
void Mod_LoadAliasModelMemoryReady(model_t *mod, void *buffer, uint32_t size)
{
#if WIN32
    printf("Size of %s is %d\r\n", mod->name, size);
#else
    (void) size;
#endif

    disk_aliashdr_t header;
    extMemGetDataFromAddress(&header, buffer, sizeof(header));

    disk_mdl_t stackModel;
    disk_mdl_t *pmodel = extMemGetDataFromAddress(&stackModel, (byte*) buffer + header.model, sizeof(stackModel)); //*/(mdl_t *) ((byte *)buffer + header.model);
    mod->numframes = pmodel->numframes;
    if (pmodel->numframes >= 256)
    {
        FIXME("ERROR TOO MANY FRAMES");
    }
    mod->synctype = pmodel->synctype;
    mod->flags = pmodel->flags;
    if (pmodel->flags > 255)
    {
        while (1)
            FIXME("BAD FLAGS");
    }
    mod->type = mod_alias;
#if MODEL_HAS_FLOAT_MINS_MAX
	mod->mins[0] = mod->mins[1] = mod->mins[2] = -16;
	mod->maxs[0] = mod->maxs[1] = mod->maxs[2] = 16;
#else
    mod->mins_s[0] = mod->mins_s[1] = mod->mins_s[2] = -16;
    mod->maxs_s[0] = mod->maxs_s[1] = mod->maxs_s[2] = 16;

#endif
#if USE_CACHE_ALLOC
	Cache_Alloc (&mod->cache, size, loadname);
	if (!mod->cache.data)
    {
        FIXME("ERROR");
        return;
    }
#else
//    mod->cache.data = Z_Calloc(size, 1, PU_STATIC, NULL);
#endif
#if WIN32
	printf("Mod.flags 0x%x, Mod.numframes %d\r\n", mod->flags, mod->numframes);
#endif
    // copy disk_mdl to reduced mdl

    mdl_t rmdl;
    VectorCopy(pmodel->scale, rmdl.scale);
    VectorCopy(pmodel->scale_origin, rmdl.scale_origin);
    VectorCopy(pmodel->eyeposition, rmdl.eyeposition);
    rmdl.boundingradius = pmodel->boundingradius;
    rmdl.size = pmodel->size;
    rmdl.skinwidth = pmodel->skinwidth;
    rmdl.skinheight = pmodel->skinheight;
    rmdl.numverts = pmodel->numverts;
    rmdl.numtris = pmodel->numtris;
    rmdl.numskins = pmodel->numskins;
    rmdl.synctype = pmodel->synctype;
    rmdl.numframes = pmodel->numframes;
    rmdl.flags = pmodel->flags;
    // Copy to internal flash everything non-graphics related.
    mdl_t *prmdl = storeToInternalFlash(&rmdl, sizeof(rmdl));
#if FASTER_STVERTS
    stvert_t *pstverts = getCurrentInternalFlashPtr();

    for (int i = 0; i < (rmdl.numverts + 1) & ~1; i +=2)
    {
      disk_stvert_t dv[2];
      extMemGetDataFromAddress(dv , (byte*) buffer + header.stverts + i * sizeof(disk_stvert_t) , 2 * sizeof(disk_stvert_t));
      stvert_t sv[2];
      sv[0].onseam = dv[0].onseam;
      sv[0].s16 = dv[0].s16;
      sv[0].t16 = dv[0].t16;
      sv[1].onseam = dv[1].onseam;
      sv[1].s16 = dv[1].s16;
      sv[1].t16 = dv[1].t16;
      storeToInternalFlash(sv, sizeof(sv));
    }

 #else
    stvert_t *pstverts = storeToInternalFlash((byte*) buffer + header.stverts, sizeof(*pstverts) * rmdl.numverts);
#endif
    // loading skins is a pain in the ass.
    maliasskindesc_t *pskindesc = storeToInternalFlash((byte*) buffer + header.skindesc, sizeof(*pskindesc) * rmdl.numskins);

    for (int i = 0; i < rmdl.numskins; i++)
    {
        if (pskindesc->type == ALIAS_SKIN_GROUP)
        {
            while (1)
                FIXME("ALIAS SKIN GROUP NOT SUPPORTED FOR NOW");
        }
    }
    // get where we are going to store the data to internal flash.
    void *ptr = reserveInternalFlashSize(sizeof(aliashdr_t) + sizeof(maliasframedesc_t) * pmodel->numframes);
    // create new header
    aliashdr_t *newHeader = Z_Calloc(sizeof(aliashdr_t) + sizeof(maliasframedesc_t) * pmodel->numframes, 1, PU_STATIC, NULL);
    //trivertx_t *trivertex = Z_Calloc(sizeof (trivertx_t) * pmodel->numverts, 1, PU_STATIC, NULL);
    extMemGetDataFromAddress(&newHeader->frames[0], ((disk_aliashdr_t*) buffer)->frames, sizeof(maliasframedesc_t) * pmodel->numframes);
    for (int i = 0; i < pmodel->numframes; i++)
    {
        if (newHeader->frames[i].type == ALIAS_SINGLE)
        {
//             NOT STORING VERTS, TOO MUCH DATA.
//            byte *framePtr = storeToInternalFlash((byte*)buffer + newHeader->frames[i].frame, sizeof (trivertx_t) * pmodel->numverts);
//            newHeader->frames[i].frame = framePtr - (byte*)ptr;
        }
        else
        {
            maliasgroup_t newMaliasGrp;
            // read the alias group
            extMemGetDataFromAddress(&newMaliasGrp, (byte*) buffer + newHeader->frames[i].frame, sizeof(newMaliasGrp));
            //
            byte *pintervals = storeToInternalFlash((byte*) buffer + newMaliasGrp.intervals, newMaliasGrp.numframes * sizeof(float));
            //
            newMaliasGrp.intervals = (byte*) pintervals - (byte*) ptr;
            // store back to flash
            maliasgroup_t *maliasGroupPtr = storeToInternalFlash(&newMaliasGrp, sizeof(maliasgroup_t));
            // now we need to load the alias group frames after the group
            storeToInternalFlash((byte*) buffer + newHeader->frames[i].frame + offsetof(maliasgroup_t, frames),
                sizeof(maliasgroupframedesc_t) * maliasGroupPtr->numframes);
            // set correct ptr
            newHeader->frames[i].frame = (byte*) maliasGroupPtr - (byte*) ptr;
        }
    }
    newHeader->extMemAddress = (int) buffer;
    newHeader->triangles = header.triangles;
    newHeader->model = (byte*) prmdl - (byte*) ptr;
    newHeader->stverts = (byte*) pstverts - (byte*) ptr;
    newHeader->skindesc = (byte*) pskindesc - (byte*) ptr;

    mod->data = storeToInternalFlashAtPointer(newHeader, ptr, sizeof(aliashdr_t) + sizeof(maliasframedesc_t) * pmodel->numframes);
    Z_Free(newHeader);
}
/*
 ==================
 Mod_LoadModel

 Loads a model into the cache
 ==================
 */
model_t* Mod_LoadModel(model_t *mod, qboolean crash)
{
    edictDbgPrintf("loading model %s\r\n", mod->name);
    unsigned int *buf;
    if (mod->type == mod_alias)
    {
        if (mod->data)
        {
            edictDbgPrintf("%s is loaded\r\n", mod->name);
            mod->needload = NL_PRESENT;
            return mod;
        }
    }
    else
    {
        if (mod->needload == NL_PRESENT)
        {
            edictDbgPrintf("%s has needload NL_PRESENT\r\n", mod->name);
            return mod;
        }
    }
    if (!canNewModelBeLoaded())
    {
        Sys_Error("Asked to load: %s when models were finalized", mod->name);
    }
//
// because the world is so huge, load it one piece at a time
//

//
// load the file
//
    unsigned int size;
    buf = (unsigned int*) getExtMemPointerToFileInPak(mod->name, &size);

    if (!buf)
    {
        if (crash)
            Sys_Error("Mod_NumForName: %s not found", mod->name);
        return NULL;
    }

//
// allocate a new model
//
//	COM_FileBase (mod->name, loadname);

    loadmodel = mod;

//
// fill it in
//

// call the appropriate loader
    mod->needload = NL_PRESENT;
    uint32_t id;
    extMemGetDataFromAddress(&id, buf, sizeof(id));
    switch (id)
    {
        case IDPOLYHEADER:
#if USE_ORIGINAL_ALIAS_MODEL
		Mod_LoadAliasModel (mod, buf);
#else
            Sys_Error("Requested load of an old alias model!");
#endif
            break;

        case IDSPRITEHEADER:
            Mod_LoadSpriteModel(mod, buf);
            break;
        case IDPOLYHEADER_MEMORY_READY:
            Mod_LoadAliasModelMemoryReady(mod, buf, size);
            break;
        default:
            Mod_LoadBrushModel(mod, buf);
            break;
    }

    return mod;
}

/*
 ==================
 Mod_ForName

 Loads in a model for the given name
 ==================
 */
model_t* Mod_ForName(const char *name, qboolean crash)
{
    model_t *mod;
#define TEST_LOAD_ALL_MODELS 0
#if TEST_LOAD_ALL_MODELS
const char * list []={
{"progs/armor.mdl"},
{"progs/g_shot.mdl"},
{"progs/g_nail.mdl"},
{"progs/g_nail2.mdl"},
{"progs/g_rock.mdl"},
{"progs/g_rock2.mdl"},
{"progs/g_light.mdl"},
{"maps/b_shell1.bsp"},
{"maps/b_shell0.bsp"},
{"maps/b_nail1.bsp"},
{"maps/b_nail0.bsp"},
{"maps/b_rock1.bsp"},
{"maps/b_rock0.bsp"},
{"maps/b_batt1.bsp"},
{"maps/b_batt0.bsp"},
{"progs/w_s_key.mdl"},
{"progs/m_s_key.mdl"},
{"progs/w_g_key.mdl"},
{"progs/m_g_key.mdl"},
{"progs/end1.mdl"},
{"progs/invulner.mdl"},
{"progs/suit.mdl"},
{"progs/invisibl.mdl"},
{"progs/quaddama.mdl"},
{"progs/player.mdl"},
{"progs/eyes.mdl"},
{"progs/h_player.mdl"},
{"progs/gib1.mdl"},
{"progs/gib2.mdl"},
{"progs/gib3.mdl"},
{"progs/s_bubble.spr"},
{"progs/s_explod.spr"},
{"progs/v_axe.mdl"},
{"progs/v_shot.mdl"},
{"progs/v_nail.mdl"},
{"progs/v_rock.mdl"},
{"progs/v_shot2.mdl"},
{"progs/v_nail2.mdl"},
{"progs/v_rock2.mdl"},
{"progs/bolt.mdl"},
{"progs/bolt2.mdl"},
{"progs/bolt3.mdl"},
{"progs/lavaball.mdl"},
{"progs/missile.mdl"},
{"progs/grenade.mdl"},
{"progs/spike.mdl"},
{"progs/s_spike.mdl"},
{"progs/backpack.mdl"},
{"progs/zom_gib.mdl"},
{"progs/v_light.mdl"},
{"progs/s_light.spr"},
{"progs/flame.mdl"},
{"progs/flame2.mdl"},
{"maps/b_explob.bsp"},
{"progs/ogre.mdl"},
{"progs/h_ogre.mdl"},
{"progs/demon.mdl"},
{"progs/h_demon.mdl"},
{"progs/shambler.mdl"},
{"progs/s_light.mdl"},
{"progs/h_shams.mdl"},
{"progs/knight.mdl"},
{"progs/h_knight.mdl"},
{"progs/soldier.mdl"},
{"progs/h_guard.mdl"},
{"progs/wizard.mdl"},
{"progs/h_wizard.mdl"},
{"progs/w_spike.mdl"},
{"progs/h_dog.mdl"},
{"progs/dog.mdl"},
{"progs/zombie.mdl"},
{"progs/h_zombie.mdl"},
{"progs/boss.mdl"}};
printf("sizeof list and *list %d %d\r\n", sizeof (list), sizeof (*list));
system("pause");
int failed = 0;
for (int i = 0; i < sizeof (list) / sizeof(*list); i++)
{
    printf ("Loading %s...", list[i]);
	mod = Mod_FindName (list[i]);
    void *p = Mod_LoadModel (mod, crash);
    printf(" pointer: %p %p\r\n", mod, p);
    failed += (mod == 0 || p == 0) ? 1 : 0;

}

printf("%d Models loaded. Failed %d\r\n", sizeof (list) / sizeof(*list), failed);
system("pause");
#endif // NOT_DOING_TEST
    mod = (model_t*) Mod_FindName(name);

    return Mod_LoadModel(mod, crash);
}

/*
 ===============================================================================

 BRUSHMODEL LOADING

 ===============================================================================
 */

byte *mod_base;
#if !TEXTURE_HAS_ANIM_POINTERS
texture_t* Mod_GetNextAnimTexture(texture_t *base)
{
    return (texture_t*) ((byte*) base + base->anim_next_ofs);
}
texture_t* Mod_GetAlternateAnimTexture(texture_t *base)
{
    return (texture_t*) ((byte*) base + base->alternate_anim_ofs);
}
void Mod_SetNextAnimTexture(texture_t *base, texture_t *next)
{
    base->anim_next_ofs = (byte*) next - (byte*) base;
}
void Mod_SetAlternateAnimTexture(texture_t *base, texture_t *alternate)
{
    base->alternate_anim_ofs = (byte*) alternate - (byte*) base;
}
#endif
/*
 =================
 Mod_LoadTextures
 =================
 */
void Mod_LoadTextures(lump_t *l, int *numTextures)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
#define MAX_MIPTEX  1024
    int i, j, num, max, altmax;
    miptex_t *mt;
    miptex_t stack_mt;
    miptex_t *mt2;
    texture_t *tx, *tx2;
    texture_t *anims[10];
    texture_t *altanims[10];
    dmiptexlump_t *m;
    dmiptexlump_t *mp;
    //
    byte stack_m[sizeof(dmiptexlump_t) + MAX_MIPTEX * 4];
    //
    if (!l->filelen)
    {
        loadmodel->brushModelData->textures = NULL;
        return;
    }
    // get number of textures
    mp = (dmiptexlump_t*) (mod_base + l->fileofs);
    m = extMemGetDataFromAddress(&stack_m, mp, sizeof(int));

    *numTextures = m->nummiptex;
    if (*numTextures > MAX_MIPTEX)
    {
        Sys_Error("Too many textures %d vs %d", numTextures, MAX_MIPTEX);
    }
    // read again.
    m = extMemGetDataFromAddress(&stack_m, mp, sizeof(int) + *numTextures * sizeof(int)); // fix this
    //
    texture_t *textures_data = Z_Calloc(sizeof(texture_t) * m->nummiptex, 1, PU_STATIC, NULL);
    loadmodel->brushModelData->textures = Z_Calloc(sizeof(texture_t*) * m->nummiptex, 1, PU_STATIC, NULL);

    for (i = 0; i < m->nummiptex; i++)
    {
        if (m->dataofs[i] == -1)
            continue;
        mt = extMemGetDataFromAddress(&stack_mt, (byte*) mp + m->dataofs[i], sizeof(stack_mt)); // */ (miptex_t *)((byte *)m + m->dataofs[i]);

        if ((mt->width & 15) || (mt->height & 15))
            Sys_Error("Texture size %s is not multiple of 16", mt->name);

        tx = textures_data + i;

        tx->width = mt->width;
        tx->height = mt->height;

        if (mt->width > 2047 || mt->height > 2047)
            FIXME("MT too large");
        if (!Q_strncmp(mt->name, "*", 1))		// turbulent
        {
            tx->isTurbulent = 1;
        }

        for (j = 0; j < MIPLEVELS; j++)
            tx->extmemdata[j] = (byte*) mod_base + m->dataofs[i] + l->fileofs + mt->offsets[j]; // + sizeof(texture_t) - sizeof(miptex_t);

        if (!Q_strncmp(mt->name, "sky", 3))
        {
            tx->isSky = 1;
            R_InitFlashSky(mt, loadmodel->name);
        }
        loadmodel->brushModelData->textures[i] = tx;
    }
//
// sequence the animations
//
    for (i = 0; i < m->nummiptex; i++)
    {
        tx = loadmodel->brushModelData->textures[i];

        mt = extMemGetDataFromAddress(&stack_mt, (byte*) mp + m->dataofs[i], sizeof(stack_mt)); // */ (miptex_t *)((byte *)m + m->dataofs[i]);

        if (!mt || mt->name[0] != '+')
            continue;
        if (tx->anim_next_ofs)
            continue;
        // find the number of frames in the animation
        memset(anims, 0, sizeof(anims));
        memset(altanims, 0, sizeof(altanims));
        max = mt->name[1];

        altmax = 0;
        if (max >= 'a' && max <= 'z')
            max -= 'a' - 'A';
        if (max >= '0' && max <= '9')
        {
            max -= '0';
            altmax = 0;
            anims[max] = tx;
            max++;
        }
        else if (max >= 'A' && max <= 'J')
        {
            altmax = max - 'A';
            max = 0;
            altanims[altmax] = tx;
            altmax++;
        }
        else
            Sys_Error("Bad animating texture %s", mt->name);

        for (j = i + 1; j < m->nummiptex; j++)
        {
            miptex_t stack_mt2;
            tx2 = loadmodel->brushModelData->textures[j];
            mt2 = extMemGetDataFromAddress(&stack_mt2, (byte*) mp + m->dataofs[j], sizeof(stack_mt2)); // */ (miptex_t *)((byte *)m + m->dataofs[i]);
            if (!mt2 || mt2->name[0] != '+')
                continue;
            if (strcmp(mt2->name + 2, mt->name + 2))
                continue;

            num = mt2->name[1];

            if (num >= 'a' && num <= 'z')
                num -= 'a' - 'A';
            if (num >= '0' && num <= '9')
            {
                num -= '0';
                anims[num] = tx2;
                if (num + 1 > max)
                    max = num + 1;
            }
            else if (num >= 'A' && num <= 'J')
            {
                num = num - 'A';
                altanims[num] = tx2;
                if (num + 1 > altmax)
                    altmax = num + 1;
            }
            else
                Sys_Error("Bad animating texture %s", mt->name);
        }

#define	ANIM_CYCLE	2
        // link them all together
        for (j = 0; j < max; j++)
        {
            tx2 = anims[j];
            if (!tx2)
                Sys_Error("Missing frame %i of %s", j, mt->name);

            tx2->anim_total = max * ANIM_CYCLE;
            tx2->anim_min = j * ANIM_CYCLE;
            tx2->anim_max = (j + 1) * ANIM_CYCLE;

            Mod_SetNextAnimTexture(tx2, anims[(j + 1) % max]);
            if (tx2->anim_next_ofs == 0)
                printf("0 NEXT ANIM OFS");
            if (altmax)
                Mod_SetAlternateAnimTexture(tx2, altanims[0]);
        }
        for (j = 0; j < altmax; j++)
        {
            tx2 = altanims[j];
            if (!tx2)
                Sys_Error("Missing frame %i of %s", j, mt->name);

            tx2->anim_total = altmax * ANIM_CYCLE;
            tx2->anim_min = j * ANIM_CYCLE;
            tx2->anim_max = (j + 1) * ANIM_CYCLE;

            Mod_SetNextAnimTexture(tx2, altanims[(j + 1) % altmax]);

            if (tx2->anim_next_ofs == 0 && altmax > 1)
                printf("0 NEXT ANIM OFS alt");
            if (max)
                Mod_SetAlternateAnimTexture(tx2, anims[0]);
        }
    }

    texture_t *buff = textures_data;
    buff = storeToInternalFlash(buff, sizeof(texture_t) * m->nummiptex);
    for (i = 0; i < m->nummiptex; i++)
    {
        loadmodel->brushModelData->textures[i] = &buff[i];
    }
    Z_Free(textures_data);
    texture_t **buff2 = loadmodel->brushModelData->textures;
    loadmodel->brushModelData->textures = storeToInternalFlash(buff2, sizeof(texture_t*) * m->nummiptex);
    Z_Free(buff2);
}

/*
 =================
 Mod_LoadLighting
 =================
 */
void Mod_LoadLighting(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    if (!l->filelen)
    {
        loadmodel->brushModelData->lightdata = NULL;
        return;
    }
#if LIGHTMAP_ON_INTERNAL_FLASH
    loadmodel->brushModelData->lightdata = storeToInternalFlash(mod_base + l->fileofs, (l->filelen + 3) & ~3);
#else
    loadmodel->brushModelData->lightdata = mod_base + l->fileofs;

#endif
}

/*
 =================
 Mod_LoadVisibility
 =================
 */
void Mod_LoadVisibility(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    if (!l->filelen)
    {
        loadmodel->brushModelData->visdata = NULL;
        return;
    }
    loadmodel->brushModelData->visdata = storeToInternalFlash(mod_base + l->fileofs, (l->filelen + 3) & ~3);
}

/*
 =================
 Mod_LoadEntities
 =================
 */
void Mod_LoadEntities(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    if (!l->filelen)
    {
        loadmodel->brushModelData->entities = NULL;
        return;
    }
    // NOTE! DO NOT LOAD THIS TO FLASH. IT MUST STAY IN EXTERNAL FLASH, IT IS USED ONCE
    loadmodel->brushModelData->entities = (char*) (mod_base + l->fileofs);
}

/*
 =================
 Mod_LoadVertexes
 =================
 */
void Mod_LoadVertexes(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    dvertex_t *in;
    int count;

    in = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*in);
    loadmodel->brushModelData->vertexes = storeToInternalFlash(in, (count * sizeof(*in) + 3) & ~3);
}

/*
 =================
 Mod_LoadSubmodels
 =================
 */
void Mod_LoadSubmodels(lump_t *l, uint8_t *subModelBuffer, unsigned int submodelBufferSize)
{
    bsp_dmodel_t *in;
    int count;

    in = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*in);
    //
    loadmodel->brushModelData->numsubmodels = count;
    if (submodelBufferSize < count * sizeof(*in))
    {
        while (1)
            FIXME("Need a bigger buffer\r\n");
    }
    else
    {
        extMemGetDataFromAddress(subModelBuffer, in, count * sizeof(*in));
    }
}

/*
 =================
 Mod_LoadEdges
 =================
 */
void Mod_LoadEdges(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    //
    dedge_t *in;
    int count;

    in = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*in);
//		printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
    STATIC_ASSERT(sizeof(dedge_t) == sizeof(medge_t));
    // numedges not used
    loadmodel->brushModelData->edges = storeToInternalFlash(in, (count * sizeof(*in) + 3) & ~3);
#if WIN32
	static int totalEdgesSoFar = 0;
	totalEdgesSoFar += count;
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>EDGE SO FAR %d\r\n", totalEdgesSoFar);
#endif
}

/*
 =================
 Mod_LoadTexinfo
 =================
 */

#define MAX_TEMP_LOAD_TEXINFO 128
void Mod_LoadTexinfo(lump_t *l, int numTextures)
{
    printf("Texinfo\r\n");
    texinfo_t *pin;
    texinfo_t in;
    mtexinfo_t *out;
    int i, j, count;
    int miptex;
    float len1, len2;

    pin = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(in);
    //
    byte stackBuffer[sizeof(*out) * MAX_TEMP_LOAD_TEXINFO];
    out = (void*) stackBuffer;
    loadmodel->brushModelData->texinfo = getCurrentInternalFlashPtr();
    //
    extMemSetCurrentAddress((uint32_t) pin);
    for (i = 0; i < count; i++)
    {
        extMemGetDataFromCurrentAddress(&in, sizeof(in));
#if WIN32 && 0
	    static int numberOfVecs = 0;
		for (j=0 ; j<8 ; j++)
        {
            numberOfVecs++;
			out->vecs[0][j] = in.vecs[0][j];
			//if (in.vecs[0][j] != (int)in.vecs[0][j])
			 //   FIXME("NUAAAAA");
            printf("Vec n %d: %f\r\n", numberOfVecs, in.vecs[0][j]);
        }

	    #else
        for (j = 0; j < 8; j++)
        {
            // next-hack: had to do this to shut off compiler warnings. Was out->vecs[0][j] = in.vecs[0][j]; The compiler is right, this was awful.
            out->vecs[j / 4][j % 4] = in.vecs[j / 4][j % 4];

        }

#endif // WIN32
        len1 = Length(out->vecs[0]);
        len2 = Length(out->vecs[1]);
        len1 = (len1 + len2) / 2;
        if (len1 < 0.32)
            out->mipadjust = 4;
        else if (len1 < 0.49)
            out->mipadjust = 3;
        else if (len1 < 0.99)
            out->mipadjust = 2;
        else
            out->mipadjust = 1;

        miptex = in.miptex;
        out->reduced_flags = in.flags;

        if (!loadmodel->brushModelData->textures)
        {
            out->texture = r_notexture_mip;	// checkerboard texture
            out->reduced_flags = 0;
        }
        else
        {
            if (miptex >= numTextures)
                Sys_Error("miptex >= loadmodel->numtextures %d > %d", miptex, numTextures);
            out->texture = loadmodel->brushModelData->textures[miptex];
            if (!out->texture)
            {
                out->texture = r_notexture_mip; // texture not found
                out->reduced_flags = 0;
            }
        }
        out++;
        if ((i % MAX_TEMP_LOAD_TEXINFO) == (MAX_TEMP_LOAD_TEXINFO - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOAD_TEXINFO * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }
    // now store the remainder
    if ((i % MAX_TEMP_LOAD_TEXINFO) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, ((i % MAX_TEMP_LOAD_TEXINFO)) * sizeof(*out));
    }
    //Z_Free(buff);
}

/*
 ================
 CalcSurfaceExtents

 Fills in s->texturemins[] and s->extents[]
 ================
 */
void CalcSurfaceExtents(msurface_t *s)
{
    float mins[2], maxs[2], val;
    int i, j, e;
    mvertex_t *v;
    mtexinfo_t *tex;
    int bmins[2], bmaxs[2];

    mins[0] = mins[1] = 999999;
    maxs[0] = maxs[1] = -99999;
#if MSURFACE_HAS_TEXINFO_POINTER
    tex = s->texinfo;
#else
    tex = getMsurfaceTexinfo(s);
#endif
    for (i = 0; i < s->numedges; i++)
    {
#if !SEPARATE_BRUSH_MODEL_DATA
		e = loadmodel->surfedges[s->firstedge+i];
		if (e >= 0)
			v = &loadmodel->vertexes[loadmodel->edges[e].v[0]];
		else
			v = &loadmodel->vertexes[loadmodel->edges[-e].v[1]];
#else
        e = loadmodel->brushModelData->surfedges[s->firstedge + i];

        if (e >= 0)
            v = &(loadmodel->brushModelData->vertexes[loadmodel->brushModelData->edges[e].v[0]]);
        else
            v = &(loadmodel->brushModelData->vertexes[loadmodel->brushModelData->edges[-e].v[1]]);

#endif
        for (j = 0; j < 2; j++)
        {
            val = v->position[0] * tex->vecs[j][0] + v->position[1] * tex->vecs[j][1] + v->position[2] * tex->vecs[j][2] + tex->vecs[j][3];
            if (val < mins[j])
                mins[j] = val;
            if (val > maxs[j])
                maxs[j] = val;
        }
    }

    for (i = 0; i < 2; i++)
    {
        bmins[i] = floorf_m(mins[i] / 16);
        bmaxs[i] = ceilf_m(maxs[i] / 16);

        s->texturemins[i] = bmins[i] * 16;
        s->extents[i] = (bmaxs[i] - bmins[i]) * 16;
        if (!(tex->reduced_flags & TEX_SPECIAL) && s->extents[i] > 256)
            Sys_Error("Bad surface extents");
    }
}

/*
 =================
 Mod_LoadFaces
 =================
 */

#define MAX_TEMP_LOAD_FACES 128
void Mod_LoadFaces(lump_t *l)
{
    dface_t *pin;
    dface_t in;

    msurface_t *out;
    int i, count, surfnum;
    int planenum, side;

    pin = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(in);

    loadmodel->brushModelData->numsurfaces = count;
    printf("model has %d surfaces\r\n", count);
    if (count > MAX_SURFACES)
    {
        while (1)
        {
            FIXME("error");
        }
    }
    unsigned int modIndex = loadmodel - mod_known;
    if (modIndex > 255)
        FIXME("ERROR, POINTER BROKEN");
    extMemSetCurrentAddress((uint32_t) pin);

    byte stackBuffer[sizeof(*out) * MAX_TEMP_LOAD_FACES];
    out = (void*) stackBuffer;
    loadmodel->brushModelData->surfaces = getCurrentInternalFlashPtr();

    for (surfnum = 0; surfnum < count; surfnum++, out++)
    {

        if ((surfnum % MAX_TEMP_LOAD_FACES) == 0 && surfnum)
        {
#if WIN32
            printf("Storing surfs %d\r\n", surfnum);
#endif
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOAD_FACES * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }

        extMemGetDataFromCurrentAddress(&in, sizeof(in));
#if MSURFACE_USES_MODEL_IDX
            out->modelIdx = modIndex;
    #endif // SURF_HAS_MODEL_POINTER
        out->firstedge = in.firstedge;
        out->numedges = in.numedges;
        out->surfIdx = surfnum;
        //
        //
        out->flags = 0;

        planenum = in.planenum;
        side = in.side;
        if (side)
            out->flags |= SURF_PLANEBACK;
#if MSURFACE_HAS_PLANE_POINTER
        out->plane = loadmodel->brushModelData->planes + planenum;    // not really optimized by used only once
#else
        setMsurfacePlane(out, loadmodel->brushModelData->planes + planenum);    // not really optimized by used only once
#endif // MSURFACE_HAS_PLANE_POINTER
#if MSURFACE_HAS_TEXINFO_POINTER
        out->texinfo = loadmodel->brushModelData->texinfo + in.texinfo;
#else
        out->texinfoIdx = in.texinfo;
#endif

        CalcSurfaceExtents(out);

        /*		static int maxValue = 0;
         if (out->planeIdx > maxValue)
         {
         maxValue = out->planeIdx;
         printf("Max value increased to %d\r\n", maxValue);
         if (maxValue > 2048)
         FIXME("NEW MAX");
         }*/

        // lighting info
        for (i = 0; i < MAXLIGHTMAPS; i++)
        {
            byte ls = in.styles[i];
            if (ls >= MAX_LIGHTSTYLES && ls != 255)
            {
                printf("Warning, light style (%d) larger than MAX_LIGHTSTYLES (%d)", ls, MAX_LIGHTSTYLES);
                FIXME("ERROR LIGHTSTYLE");
                ls = 0;
            }
            out->styles[i] = ls;

        }
        i = in.lightofs;

        if ((i > 0 && (i & 0x3)) || i > 65534 * 4)
            FIXME("Wrong light data");
#if MSURFACE_HAS_LIGHT_SAMPLE_POINTER
        if (i == -1)
            out->samples = NULL;
        else
            out->samples = loadmodel->brushModelData->lightdata + i;
#else
        out->samplesIdx = i >> 2;
#endif // MSURFACE_HAS_LIGHT_SAMPLE_POINTER
        // set the drawing flags flag
#if MSURFACE_HAS_TEXINFO_POINTER
        mtexinfo_t *ti = out->texinfo;
#else
        mtexinfo_t *ti = getMsurfaceTexinfo(out);
#endif // MSURFACE_HAS_TEXINFO_POINTER
        if (ti->texture->isSky)
        {
            out->flags |= (SURF_DRAWSKY | SURF_DRAWTILED);
            continue;
        }
        if (ti->texture->isTurbulent)
        {
            out->flags |= (SURF_DRAWTURB | SURF_DRAWTILED);
            for (i = 0; i < 2; i++)
            {
                out->extents[i] = 16384;
                out->texturemins[i] = -8192;
            }
            continue;
        }
    }
    // now store the remainder
    if ((surfnum % MAX_TEMP_LOAD_FACES) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, ((surfnum % MAX_TEMP_LOAD_FACES)) * sizeof(*out));
    }

//	Z_Free(buff);
}
#if NODE_HAS_PARENT_POINTER

/*
=================
Mod_SetParent
=================
*/
void Mod_SetParent (mnode_t *node, mnode_t *parent)
{
    node->parent = parent;
	if (node->contents < 0)
		return;
	Mod_SetParent (node->children[0], node);
	Mod_SetParent (node->children[1], node);
}
#elif 0
void Mod_SetParent (mnode_t *node, mnode_t *parent, model_t *model)
{
    if (parent == NULL)
    {
        node->parent_idx = - 1;
    }
    else
    {
#if !SEPARATE_BRUSH_MODEL_DATA
        node->parent_idx = parent - model->nodes;
#else
        node->parent_idx = parent - model->brushModelData->nodes;

#endif
    }
	if (node->contents < 0)
		return;
#if NODE_HAS_CHILDREN_POINTERS
	Mod_SetParent (node->children[0], node, model);
	Mod_SetParent (node->children[1], node, model);
#else
	Mod_SetParent (Mod_GetChildNode(node, 0, model), node, model);
	Mod_SetParent (Mod_GetChildNode(node, 1, model), node, model);
#endif

}

#endif // NODE_HAS_PARENT_POINTER
#if 0
mnode_t *Mod_GetParent(mnode_t *node, model_t *model)
{
    if (node->parent_idx < 0)
        return NULL;
    else
#if !SEPARATE_BRUSH_MODEL_DATA
        return model->nodes + node->parent_idx;
#else
        return model->brushModelData->nodes + node->parent_idx;
#endif
}
#if !NODE_HAS_CHILDREN_POINTERS
mnode_t * Mod_GetChildNode(mnode_t *node, int childNumber, model_t * model)
{
    #if 1
    int p = node->children_idx[childNumber];
#if !SEPARATE_BRUSH_MODEL_DATA
    if (p >= 0)
    {
        return model->nodes + p;
    }
    else
        return (mnode_t *)(model->leafs + (-1 - p));
#else
    if (p >= 0)
    {
        return model->brushModelData->nodes + p;
    }
    else
        return (mnode_t *)(model->brushModelData->leafs + (-1 - p));

#endif
#else
    return  node->children_idx[childNumber];
#endif
}
#endif
#if !NODE_HAS_PLANE_POINTER
mplane_t *Mod_GetNodePlane(mnode_t *node, model_t *model)
{
#if !SEPARATE_BRUSH_MODEL_DATA
    return model->planes + node->plane_idx;
#else
    return model->brushModelData->planes + node->plane_idx;

#endif
}
#endif
#endif
/*
 =================
 Mod_LoadNodes
 =================
 */
#define MAX_TEMP_LOAD_NODES 256      // the mnode_t is 28 bytes and we have a huge stack.
void Mod_LoadNodesAndLeafs(lump_t *l)
{
    byte *data;
    short count, numleafs;
    data = (byte*) (mod_base + l->fileofs);
    extMemGetDataFromAddress(&count, data, sizeof(count));
    extMemGetDataFromCurrentAddress(&numleafs, sizeof(numleafs));
    // store surfaceindex
    loadmodel->brushModelData->numnodes = count;
    loadmodel->brushModelData->numleafs = numleafs;
    int size = (sizeof(short) * loadmodel->brushModelData->numsurfaces + 3) & ~3;
    loadmodel->brushModelData->surfNodeIndex = storeToInternalFlash(&data[4], size);
    // store mnodes
    // NOTE!!! THE SIZE IS ROUNDED TO 4 byte boundary but the offsets on disk should not!
#if !NODE_HAS_PLANE_POINTER
#error
    loadmodel->brushModelData->nodes = storeToInternalFlash(data + 4 + size, (count * sizeof(disk_mnode_t) + 3) & ~3);
#else
    disk_mnode_t dmnode;
    loadmodel->brushModelData->nodes = getCurrentInternalFlashPtr();
    mnode_t *out;
    byte stackBuffer[sizeof(*out) * MAX_TEMP_LOAD_NODES];
    out = (void*) stackBuffer;
    int i;
    for (i = 0; i < count; i++)
    {
        extMemGetDataFromAddress(&dmnode, data + 4 + sizeof(short) * loadmodel->brushModelData->numsurfaces + sizeof(disk_mnode_t) * i, sizeof(disk_mnode_t));

        // common with leaf
        out->contents = dmnode.contents;

        out->parent_idx = dmnode.parent_idx;
        out->node_idx = dmnode.node_idx;
        out->minmaxs[0] = dmnode.minmaxs[0];   // for bounding box culling
        out->minmaxs[1] = dmnode.minmaxs[1];   // for bounding box culling
        out->minmaxs[2] = dmnode.minmaxs[2];   // for bounding box culling
        out->minmaxs[3] = dmnode.minmaxs[3];   // for bounding box culling
        out->minmaxs[4] = dmnode.minmaxs[4];   // for bounding box culling
        out->minmaxs[5] = dmnode.minmaxs[5];   // for bounding box culling
        //
        out->plane = loadmodel->brushModelData->planes + dmnode.plane_idx;
        out->children_idx[0] = dmnode.children_idx[0];              // note: node 0 should not be a children, right ?
        out->children_idx[1] = dmnode.children_idx[1];              // note: node 0 should not be a children, right ?
        //
        out->firstsurface = dmnode.firstsurface;
        out->numsurfaces = dmnode.numsurfaces;
        out++;

        if ((i % MAX_TEMP_LOAD_NODES) == (MAX_TEMP_LOAD_NODES - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOAD_NODES * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }
    // now store the remainder
    if ((i % MAX_TEMP_LOAD_NODES) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, ((i % MAX_TEMP_LOAD_NODES)) * sizeof(*out));
    }
#endif
    loadmodel->brushModelData->leafs = storeToInternalFlash(data + 4 + sizeof(short) * loadmodel->brushModelData->numsurfaces + count * sizeof(disk_mnode_t),
        (numleafs * sizeof(mleaf_t) + 3) & ~3);

}

/*
 =================
 Mod_LoadClipnodes
 =================
 */
#if 1
#define MAX_TEMP_LOADCLIPNODES 128
void Mod_LoadClipnodes(lump_t *l, int *clipnodes)
{
    disk_clipnode_t in;
    disk_clipnode_t *pin;
    dclipnode_t *out;
    int i, count;
    hull_t *hull;

    pin = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*pin))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*pin);
    //   printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
    dclipnode_t stackBuffer[MAX_TEMP_LOADCLIPNODES];
    void *clipNodeFlashPtr = getCurrentInternalFlashPtr();
    out = stackBuffer;        // Z_Calloc(count * sizeof(*out), 1, PU_STATIC, NULL);

    *clipnodes = count;
    hull_t *modelHulls = loadmodel->brushModelData->hulls;

    hull = &modelHulls[1];
    hull->clipnodes = clipNodeFlashPtr;
    hull->firstclipnode = 0;
    hull->lastclipnode = count - 1;

    hull->planes = loadmodel->brushModelData->planes;

    hull->clip_mins[0] = -16;
    hull->clip_mins[1] = -16;
    hull->clip_mins[2] = -24;
    hull->clip_maxs[0] = 16;
    hull->clip_maxs[1] = 16;
    hull->clip_maxs[2] = 32;

    hull = &modelHulls[2];
    hull->clipnodes = clipNodeFlashPtr;
    hull->firstclipnode = 0;
    hull->lastclipnode = count - 1;

    hull->planes = loadmodel->brushModelData->planes;

    hull->clip_mins[0] = -32;
    hull->clip_mins[1] = -32;
    hull->clip_mins[2] = -24;
    hull->clip_maxs[0] = 32;
    hull->clip_maxs[1] = 32;
    hull->clip_maxs[2] = 64;
    extMemSetCurrentAddress((uint32_t) pin);
    for (i = 0; i < count; i++)
    {
        extMemGetDataFromCurrentAddress(&in, sizeof(in));
        out->planenum = in.planenum;
        out->children[0] = in.children[0];
        out->children[1] = in.children[1];
        out++;
        if ((i % MAX_TEMP_LOADCLIPNODES) == (MAX_TEMP_LOADCLIPNODES - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOADCLIPNODES * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }
    // now store the remainder
    if ((i % MAX_TEMP_LOADCLIPNODES) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, ((i % MAX_TEMP_LOADCLIPNODES) * sizeof(*out) + 3) & ~3);
    }

}

#else
void Mod_LoadClipnodes (lump_t *l, int *clipnodes)
{
    disk_clipnode_t in;
    disk_clipnode_t *pin;
	dclipnode_t *out;
	int			i, count;
	hull_t		*hull;

	pin = (void *)(mod_base + l->fileofs);
	if (l->filelen % sizeof(*pin))
		Sys_Error ("MOD_LoadBmodel: funny lump size in %s",loadmodel->name);
	count = l->filelen / sizeof(*pin);
 //   printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
    out = Z_Calloc(count * sizeof(*out), 1, PU_STATIC, NULL);
    void *buff = out;
    *clipnodes = count;
	hull_t *modelHulls = loadmodel->brushModelData->hulls;

	hull = &modelHulls[1];
	hull->clipnodes = out;
	hull->firstclipnode = 0;
	hull->lastclipnode = count-1;

    hull->planes = loadmodel->brushModelData->planes;

	hull->clip_mins[0] = -16;
	hull->clip_mins[1] = -16;
	hull->clip_mins[2] = -24;
	hull->clip_maxs[0] = 16;
	hull->clip_maxs[1] = 16;
	hull->clip_maxs[2] = 32;

	hull = &modelHulls[2];
	hull->clipnodes = out;
	hull->firstclipnode = 0;
	hull->lastclipnode = count-1;

	hull->planes = loadmodel->brushModelData->planes;

	hull->clip_mins[0] = -32;
	hull->clip_mins[1] = -32;
	hull->clip_mins[2] = -24;
	hull->clip_maxs[0] = 32;
	hull->clip_maxs[1] = 32;
	hull->clip_maxs[2] = 64;
    extMemSetCurrentAddress(pin);
	for (i=0 ; i<count ; i++, out++)
	{
	    extMemGetDataFromCurrentAddress(&in, sizeof(in));
		out->planenum = in.planenum;
		out->children[0] = in.children[0];
		out->children[1] = in.children[1];
	}

	out = storeToInternalFlash(buff, count * sizeof(*out));
	hull = &modelHulls[1];
	hull->clipnodes = out;
	hull = &modelHulls[2];
	hull->clipnodes = out;
	Z_Free(buff);

}

#endif // 1

/*
 =================
 Mod_MakeHull0

 Duplicate the drawing hull structure as a clipping hull
 =================
 */
#if 1
void Mod_MakeHull0(void)
{
    mnode_t *in, *child;
    dclipnode_t *out;
    int i, j, count;
    hull_t *hull;

    hull = &loadmodel->brushModelData->hulls[0];
    in = loadmodel->brushModelData->nodes;
    count = loadmodel->brushModelData->numnodes;

    dclipnode_t stackBuffer[MAX_TEMP_LOADCLIPNODES];
    void *clipNodeFlashPtr = getCurrentInternalFlashPtr();
    out = stackBuffer;        // Z_Calloc(count * sizeof(*out), 1, PU_STATIC, NULL);

    hull->clipnodes = out;  // necessary? don't want to think...
    hull->firstclipnode = 0;
    hull->lastclipnode = count - 1;
    hull->planes = loadmodel->brushModelData->planes;
    for (i = 0; i < count; i++, in++)
    {
#if NODE_HAS_PLANE_POINTER
        out->planenum = in->plane - loadmodel->brushModelData->planes;  // can't it be s

#else
        out->planenum =  Mod_GetNodePlane(in , loadmodel) - loadmodel->brushModelData->planes;  // can't it be s
#endif
        for (j = 0; j < 2; j++)
        {
            child = Mod_GetChildNode(in, j, loadmodel);
            if (child->contents < 0)
                out->children[j] = child->contents;
            else
                out->children[j] = child - loadmodel->brushModelData->nodes;
        }
        out++;
        if ((i % MAX_TEMP_LOADCLIPNODES) == (MAX_TEMP_LOADCLIPNODES - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOADCLIPNODES * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }
    // now store the remainder
    if ((i % MAX_TEMP_LOADCLIPNODES) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, (((i % MAX_TEMP_LOADCLIPNODES) * sizeof(*out)) + 3) & ~3);
    }
    hull->clipnodes = clipNodeFlashPtr;
}

#else
void Mod_MakeHull0 (void)
{
	mnode_t		*in, *child;
	dclipnode_t *out;
	int			i, j, count;
	hull_t		*hull;


	hull = &loadmodel->brushModelData->hulls[0];
	in = loadmodel->brushModelData->nodes;
	count = loadmodel->brushModelData->numnodes;
	out = Z_Calloc ( count*sizeof(*out), 1, PU_STATIC, NULL);
    void *buff = out;

	hull->clipnodes = out;
	hull->firstclipnode = 0;
	hull->lastclipnode = count-1;
	hull->planes = loadmodel->brushModelData->planes;
	for (i=0 ; i<count ; i++, out++, in++)
	{
        out->planenum =  Mod_GetNodePlane(in , loadmodel) - loadmodel->brushModelData->planes;  // can't it be s
		for (j=0 ; j<2 ; j++)
		{
            child = Mod_GetChildNode(in, j, loadmodel);
			if (child->contents < 0)
				out->children[j] = child->contents;
			else
				out->children[j] = child - loadmodel->brushModelData->nodes;
		}
	}
	out = storeToInternalFlash(buff, count*sizeof(*out));
	hull->clipnodes = out;
	Z_Free(buff);
}

#endif // 1

/*
 =================
 Mod_LoadMarksurfaces
 =================
 */
void Mod_LoadMarksurfaces(lump_t *l)
{
    int count;
    short *pin;
    pin = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*pin))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*pin);
    loadmodel->brushModelData->marksurfaceIdx = storeToInternalFlash(pin, (count * sizeof(*pin) + 3) & ~3);
}

/*
 =================
 Mod_LoadSurfedges
 =================
 */
#if 1
#define MAX_TEMP_LOAD_SURFEDGES 1024
void Mod_LoadSurfedges(lump_t *l)
{
    // next-hack checked (2024-01-28): this will work even if model is on external flash.
    int i, count;
    int *in;
#if SURF_EDGES_INT
    int *out;
#else
    short *out;
#endif
    in = (void*) (mod_base + l->fileofs);
    if (l->filelen % sizeof(*in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(*in);

    byte stackBuffer[sizeof(*out) * MAX_TEMP_LOAD_SURFEDGES];

    out = (void*) stackBuffer;

    extMemSetCurrentAddress((uint32_t) in);
    loadmodel->brushModelData->surfedges = getCurrentInternalFlashPtr();
//next-hack: FIXME: we might want to speed-up this, by reading everything from extFlash
    for (i = 0; i < count; i++)
    {

        int n;
        //		n = LittleLong (in[i]);
        extMemGetDataFromCurrentAddress(&n, sizeof(n));
        if (n > 32767 || n < -32768)
        {
            printf("surf edge is larger than a short %d\r\n", n);
            FIXME("BUUH");
        }
        *out = n;
        out++;
        if ((i % MAX_TEMP_LOAD_SURFEDGES) == (MAX_TEMP_LOAD_SURFEDGES - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOAD_SURFEDGES * sizeof(*out));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }
    // now store the remainder
    if ((i % MAX_TEMP_LOAD_SURFEDGES) != 0)
    {
        out = (void*) stackBuffer;
        storeToInternalFlash(out, ((i % MAX_TEMP_LOAD_SURFEDGES) * sizeof(*out) + 3) & ~3);
    }
}
#endif
/*
 =================
 Mod_LoadPlanes
 =================
 */

#define MAX_TEMP_LOAD_PLANES 256
void Mod_LoadPlanes(lump_t *l)
{
    int i, j;
    mplane_t *out;
    dplane_t in;
    int count;
    int bits;

    void *pin = (void*) (mod_base + l->fileofs);

    if (l->filelen % sizeof(in))
        Sys_Error("MOD_LoadBmodel: funny lump size in %s", loadmodel->name);
    count = l->filelen / sizeof(in);

    //
    mplane_t stackBuffer[MAX_TEMP_LOAD_PLANES];
    out = (mplane_t*) stackBuffer;

    loadmodel->brushModelData->planes = getCurrentInternalFlashPtr();

    extMemSetCurrentAddress((uint32_t) pin);
    //
    for (i = 0; i < count; i++)
    {
        bits = 0;
        extMemGetDataFromCurrentAddress(&in, sizeof(in));
        for (j = 0; j < 3; j++)
        {
            out->normal[j] = in.normal[j];
            if (out->normal[j] < 0)
                bits |= 1 << j;
        }
        setPlaneDist(out, in.dist);
        out->type = in.type; // this is byte!
#if WIN32 && 0
    static int planeMaxType = 0;
    if (planeMaxType < in.type)
        planeMaxType = in.type;
    printf("plane max type %d\r\n", planeMaxType);
    static float planeDist = 0;
    if (planeDist < fabs(in.dist))
        planeDist = fabs(in.dist);
    printf("plane max dist %f, current %f\r\n", planeDist, in.dist);

#endif // WIN32

        out->signbits = bits;
        out++;
        if ((i % MAX_TEMP_LOAD_PLANES) == (MAX_TEMP_LOAD_PLANES - 1))
        {
            // reset out to stackBuffer and save
            out = (void*) stackBuffer;
            storeToInternalFlash(out, MAX_TEMP_LOAD_PLANES * sizeof(mplane_t));
            memset(stackBuffer, 0, sizeof(stackBuffer));
        }
    }

// now store the remainder
    if ((i % MAX_TEMP_LOAD_PLANES) != 0)
    {
        out = (mplane_t*) stackBuffer;
//        printf("i is %i and mod is %d\r\n",i, i % MAX_TEMP_LOAD_PLANES);
        storeToInternalFlash(out, ((i % MAX_TEMP_LOAD_PLANES)) * sizeof(mplane_t));
    }
    //Z_Free(buff);
}

/*
 =================
 RadiusFromBounds
 =================
 */

float RadiusFromBounds(vec3_t mins, vec3_t maxs)
{
    int i;
    vec3_t corner;

    for (i = 0; i < 3; i++)
    {
        corner[i] = fabsf_m(mins[i]) > fabsf_m(maxs[i]) ? fabsf_m(mins[i]) : fabsf_m(maxs[i]);
    }

    return Length(corner);
}
float RadiusFromBounds_s(short *mins_s, short *maxs_s)
{
    vec3_t mins, maxs;
    VectorCopy(mins_s, mins);
    VectorCopy(maxs_s, maxs)
    return RadiusFromBounds(mins, maxs);
}
/*
 =================
 Mod_LoadBrushModel
 =================
 */
#define TEST_LIGHTING_REDUCTION 0
#if TEST_LIGHTING_REDUCTION && WIN32

/* Return the first occurrence of NEEDLE in HAYSTACK.  */
void *
memmem (const void *haystack, size_t haystack_len, const void *needle,
	size_t needle_len)
{
  const char *begin;
  const char *const last_possible
    = (const char *) haystack + haystack_len - needle_len;

  if (needle_len == 0)
    /* The first occurrence of the empty string is deemed to occur at
       the beginning of the string.  */
    return (void *) haystack;

  /* Sanity check, otherwise the loop might search through the whole
     memory.  */
  if (__builtin_expect (haystack_len < needle_len, 0))
    return NULL;

  for (begin = (const char *) haystack; begin <= last_possible; ++begin)
    if (begin[0] == ((const char *) needle)[0] &&
	!memcmp ((const void *) &begin[1],
		 (const void *) ((const char *) needle + 1),
		 needle_len - 1))
      return (void *) begin;

  return NULL;
}
#endif // TEST_LIGHTING_REDUCTION
void Mod_LoadBrushModel(model_t *mod, void *buffer)
{
    int i, j;
    dheader_t *header;
    bsp_dmodel_t *bm;

    loadmodel->type = mod_brush;
#if SEPARATE_BRUSH_MODEL_DATA
    loadmodel->brushModelData = Z_Calloc(sizeof(brush_model_data_t), 1, PU_STATIC, NULL);
    if (numberOfBrushModels > MAX_BRUSH_MODELS)
    {
        while (1)
            FIXME("TOO MANY BRUSH MODELS");
    }
#endif
#if !USE_EXT_MEMORY
	header = (dheader_t *)buffer;
#else
    dheader_t stackHeader;
    header = extMemGetDataFromAddress(&stackHeader, buffer, sizeof(stackHeader));
#endif
    i = LittleLong(header->version);
    if (i != BSPVERSION)
        Sys_Error("Mod_LoadBrushModel: %s has wrong version number (%i should be %i)", mod->name, i, BSPVERSION);
//    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>Brush Model Name: %s\r\n", mod->name);
// swap all the lumps
    mod_base = (byte*) buffer;

#if SWAPCRAP
	for (i=0 ; i<sizeof(dheader_t)/4 ; i++)
		((int *)header)[i] = LittleLong ( ((int *)header)[i]);
#endif // SWAPCRAP

// load into heap
    // next-hack: xx in the comments means done, including support for external flash
    Mod_LoadVertexes(&header->lumps[LUMP_VERTEXES]);           // xx All floats. Cannot be reduced, and it is not expanded
    Mod_LoadEdges(&header->lumps[LUMP_EDGES]);                 // xx all shorts
    Mod_LoadSurfedges(&header->lumps[LUMP_SURFEDGES]);         // xx Note: we might want to reduce in the original file ints to shorts
    int numTextures;
    Mod_LoadTextures(&header->lumps[LUMP_TEXTURES], &numTextures);  // xx
    Mod_LoadLighting(&header->lumps[LUMP_LIGHTING]);                // xx this might be loaded on demand. To be defined.
    Mod_LoadPlanes(&header->lumps[LUMP_PLANES]); // xx probably we should split between plane dist and plane bits and plane type. Probably type might be joined to signbits to save a little.
    Mod_LoadTexinfo(&header->lumps[LUMP_TEXINFO], numTextures);     // xx should be done by the editor
    Mod_LoadFaces(&header->lumps[LUMP_FACES]);                 // xx
    Mod_LoadMarksurfaces(&header->lumps[LUMP_MARKSURFACES]);   // xx
    Mod_LoadVisibility(&header->lumps[LUMP_VISIBILITY]);       // xx
    //Mod_LoadLeafs (&header->lumps[LUMP_LEAFS]);                 // xx
    Mod_LoadNodesAndLeafs(&header->lumps[LUMP_NODES]);                 // xx
    int numClipNodes;
    Mod_LoadClipnodes(&header->lumps[LUMP_CLIPNODES], &numClipNodes);         //xx
    Mod_LoadEntities(&header->lumps[LUMP_ENTITIES]);               //xx this is loaded and parsed directly from extmem when needed
    uint8_t subModelBuffer[16384]; // 256 submodels
    Mod_LoadSubmodels(&header->lumps[LUMP_MODELS], subModelBuffer, sizeof(subModelBuffer));

    //
#if TEST_LIGHTING_REDUCTION && WIN32
    char newLighting[280000] = {0};
    int lenghtStoredSoFar =0;
    for (int s = 0; s < mod->brushModelData->numsurfaces ; s++)
    {
        msurface_t *surf = &mod->brushModelData->surfaces[s];
        int smax, tmax;
        smax = (surf->extents[0]>>4)+1;
        tmax = (surf->extents[1]>>4)+1;
        int size = smax*tmax;
        // load lighting
        static int bytesSaved = 0;
        for (int ls = 0; ls <4 && surf->styles[ls] != 255; ls++)
        {
            char *pl = getMsurfaceSamples(surf) + size * ls;
            if (pl)
            {
                char *pos = memmem(mod->brushModelData->lightdata, lenghtStoredSoFar, pl, size);
                if (!pos)
                {
                    printf("Not found, storing new data\r\n");
                    memcpy(newLighting + lenghtStoredSoFar, pl, size);
                    lenghtStoredSoFar += size;
                }
                else
                {
                    // FIXME: store new pointer
                    printf("Found! we saved %d bytes so far\r\n", bytesSaved);
                    bytesSaved += size;
                }
            }
        }
    }
    printf("Total: %d\r\n",lenghtStoredSoFar );
    FIXME("Look at me!");
#endif // TEST_LIGHTING_REDUCTION

    Mod_MakeHull0();

    mod->numframes = 2;		// regular and alternate animation
    mod->flags = 0;
//
// set up the submodels (FIXME: this is confusing)
//
    for (i = 0; i < mod->brushModelData->numsubmodels; i++)
    {

        bm = (bsp_dmodel_t*) &subModelBuffer[i * sizeof(bsp_dmodel_t)];
        mod->brushModelData->hulls[0].firstclipnode = bm->headnode[0];
        for (j = 1; j < MAX_MAP_HULLS; j++)
        {
            mod->brushModelData->hulls[j].firstclipnode = bm->headnode[j];
            mod->brushModelData->hulls[j].lastclipnode = numClipNodes - 1;      // not really used elsewhere
        }
        mod->brushModelData->firstmodelsurface = bm->firstface;
        mod->brushModelData->nummodelsurfaces = bm->numfaces;
        ;
        mod->brushModelData->numleafs = bm->visleafs;
#if MODEL_HAS_FLOAT_MINS_MAX
		VectorCopy (bm->maxs, mod->maxs);
		VectorCopy (bm->mins, mod->mins);
		mod->radius = RadiusFromBounds (mod->mins, mod->maxs);
#else
        for (int j = 0; j < 3; j++)
        {
            mod->maxs_s[j] = bm->maxs[j] + 1;   // next-hack: this was originally done in Mod_LoadSubmodels()
            mod->mins_s[j] = bm->mins[j] - 1;
        }
        mod->radius = RadiusFromBounds_s(mod->mins_s, mod->maxs_s);

#endif
        if (i < mod->brushModelData->numsubmodels - 1)
        {	// duplicate the basic information
            char name[10];

            sprintf(name, "*%i", i + 1);
            loadmodel = Mod_FindName(name);
            *loadmodel = *mod;
            // loadmodel->brushModelDataIndex = numberOfBrushModels++;
            loadmodel->brushModelData = Z_Calloc(sizeof(brush_model_data_t), 1, PU_STATIC, NULL);
            if (numberOfBrushModels > MAX_BRUSH_MODELS)
            {
                while (1)
                    FIXME("TOO MANY BRUSH MODELS");
            }
            memcpy(loadmodel->brushModelData, mod->brushModelData, sizeof(brush_model_data_t));
//    			memcpy(&brushModelData[loadmodel->brushModelDataIndex], &brushModelData[mod->brushModelDataIndex], sizeof(brushModelData[loadmodel->brushModelDataIndex]));
            // store and free old data
            brush_model_data_t *buff = mod->brushModelData;
            mod->brushModelData = storeToInternalFlash(buff, sizeof(*buff));
            Z_Free(buff);
            int len = strlen(name) + 1;
            if (len > MAX_QPATH)
            {
                Sys_Error("mod name too long");
            }
            loadmodel->name = storeToInternalFlash(name, (len + 3) & ~3);
            mod = loadmodel;
        }

    }
    // store brush model data.
    brush_model_data_t *buff = mod->brushModelData;
    mod->brushModelData = storeToInternalFlash(buff, sizeof(*buff));
    Z_Free(buff);
}

/*
 ==============================================================================

 ALIAS MODELS

 ==============================================================================
 */

//=============================================================================
/*
 =================
 Mod_LoadSpriteFrame
 =================
 */
void* Mod_LoadSpriteFrame(void *pin, mspriteframe_t **ppframe)
{
    dspriteframe_t *pinframe;
    int width, height, size, origin[2];

    pinframe = (dspriteframe_t*) pin;

    dspriteframe_t inframe;
    extMemGetDataFromAddress(&inframe, pin, sizeof(inframe));

    width = inframe.width;
    height = inframe.height;
    size = width * height;

    mspriteframe_t spriteframe;

    spriteframe.width = width;
    spriteframe.height = height;
    origin[0] = inframe.origin[0];
    origin[1] = inframe.origin[1];

    spriteframe.up = origin[1];
    spriteframe.down = origin[1] - height;
    spriteframe.left = origin[0];
    spriteframe.right = width + origin[0];

    //Q_memcpy (&pspriteframe->pixels[0], (byte *)(pinframe + 1), size);
#if SPRITE_IN_INTERNAL_FLASH
    spriteframe.pixels = (byte *)storeToInternalFlash((byte *)(pinframe + 1), size);
#else
    spriteframe.pixels = (byte*) (pinframe + 1);

#endif // SPRITE_IN_INTERNAL_FLASH
    *ppframe = storeToInternalFlash(&spriteframe, sizeof(spriteframe));
    return (void*) ((byte*) pinframe + sizeof(dspriteframe_t) + size);
}

/*
 =================
 Mod_LoadSpriteGroup
 =================
 */
void* Mod_LoadSpriteGroup(void *pin, mspriteframe_t **ppframe)
{
    while (1)
        FIXME("SPRITEGROUP not implemented!");
    (void) pin;
    (void) ppframe;
#if 0
	dspritegroup_t		*pingroup;
	mspritegroup_t		*pspritegroup;
	int					i, numframes;
	dspriteinterval_t	*pin_intervals;
	float				*poutintervals;
	void				*ptemp;

	pingroup = (dspritegroup_t *)pin;

	numframes = LittleLong (pingroup->numframes);
 //   printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
	pspritegroup = Hunk_Alloc (sizeof (mspritegroup_t) + (numframes - 1) * sizeof (pspritegroup->frames[0]));

	pspritegroup->numframes = numframes;

	*ppframe = (mspriteframe_t *)pspritegroup;

	pin_intervals = (dspriteinterval_t *)(pingroup + 1);
 //   printf("Line %d %s  ", __LINE__ , __PRETTY_FUNCTION__);
	poutintervals = Hunk_Alloc (numframes * sizeof (float));

	pspritegroup->intervals = poutintervals;

	for (i=0 ; i<numframes ; i++)
	{
		*poutintervals = LittleFloat (pin_intervals->interval);
		if (*poutintervals <= 0.0)
			Sys_Error ("Mod_LoadSpriteGroup: interval<=0");

		poutintervals++;
		pin_intervals++;
	}

	ptemp = (void *)pin_intervals;

	for (i=0 ; i<numframes ; i++)
	{
		ptemp = Mod_LoadSpriteFrame (ptemp, &pspritegroup->frames[i]);
	}
	return ptemp;
#endif
}

/*
 =================
 Mod_LoadSpriteModel
 =================
 */
void Mod_LoadSpriteModel(model_t *mod, void *buffer)
{
    int i;
    int version;
    dsprite_t *pin;
    msprite_t *psprite;
    int numframes;
    int size;
    dspriteframetype_t *pframetype;
    dsprite_t in;
    pin = (dsprite_t*) extMemGetDataFromAddress(&in, buffer, sizeof(in));

    version = LittleLong(pin->version);
    if (version != SPRITE_VERSION)
        Sys_Error("%s has wrong version number (%i should be %i)", mod->name, version, SPRITE_VERSION);

    numframes = LittleLong(pin->numframes);

    size = sizeof(msprite_t) + numframes * sizeof(mspriteframedesc_t);
    psprite = Z_Calloc(size, 1, PU_STATIC, NULL);

    psprite->type = pin->type;
    psprite->maxwidth = pin->width;
    psprite->maxheight = pin->height;
    psprite->beamlength = pin->beamlength;
    if (pin->beamlength != (int) pin->beamlength)
        while (1)
            FIXME("ERROR BEAMLENGTH FLOAT VALUE");
    mod->synctype = pin->synctype;
    psprite->numframes = numframes;
    if (numframes > 255)
        while (1)
            FIXME("Error Too many frames");
#if MODEL_HAS_FLOAT_MINS_MAX
	mod->mins[0] = mod->mins[1] = -psprite->maxwidth/2;
	mod->maxs[0] = mod->maxs[1] = psprite->maxwidth/2;
	mod->mins[2] = -psprite->maxheight/2;
	mod->maxs[2] = psprite->maxheight/2;
#else
    mod->mins_s[0] = mod->mins_s[1] = -psprite->maxwidth / 2;
    mod->maxs_s[0] = mod->maxs_s[1] = psprite->maxwidth / 2;
    mod->mins_s[2] = -psprite->maxheight / 2;
    mod->maxs_s[2] = psprite->maxheight / 2;

#endif

//
// load the frames
//
    if (numframes < 1)
        Sys_Error("Mod_LoadSpriteModel: Invalid # of frames: %d\n", numframes);

    mod->numframes = numframes;
    mod->flags = 0;

    pin = buffer;  // restore.
    pframetype = (dspriteframetype_t*) (pin + 1);
//    int oldFrameType;
//  extMemGetDataFromAddress(oldFrameType, &pframetype->type, 4);
    for (i = 0; i < numframes; i++)
    {
#if 0
		spriteframetype_t	frametype =		extMemGetByteFromAddress(&pframetype->type);
//		if (frametype != oldFrameType)
//		    while(1) FIXME("Switching between frame types");
		psprite->frames[i].type = frametype;

		if (frametype == SPR_SINGLE)
		{
			pframetype = (dspriteframetype_t *) Mod_LoadSpriteFrame (pframetype + 1, &psprite->frames[i].frameptr);
		}
		else
		{
		    FIXME("ERROR");
			pframetype = (dspriteframetype_t *)	Mod_LoadSpriteGroup (pframetype + 1, &psprite->frames[i].frameptr);
		}
#else
        psprite->frames[i].type = SPR_SINGLE;
        pframetype = (dspriteframetype_t*) Mod_LoadSpriteFrame(pframetype + 1, &psprite->frames[i].frameptr);
#endif
    }

    mod->type = mod_sprite;
    mod->data = storeToInternalFlash(psprite, size);
    Z_Free(psprite);
}

//=============================================================================

/*
 ================
 Mod_Print
 ================
 */
void Mod_Print(void)
{
    int i;
    model_t *mod;

    Con_Printf("Cached models:\n");
    for (i = 0, mod = mod_known; i < mod_numknown; i++, mod++)
    {
        Con_Printf("%8p : %s", mod->data, mod->name);
        if (mod->needload & NL_UNREFERENCED)
            Con_Printf(" (!R)");
        if (mod->needload & NL_NEEDS_LOADED)
            Con_Printf(" (!P)");
        Con_Printf("\n");
    }
}
// Some model load assist functions
void finalizeModKnown(void)
{
    modelsFinalized = 1;
    mod_known = storeToInternalFlash(mod_known, sizeof(*mod_known) * MAX_MOD_KNOWN);
    printf("Models finalized, stored %d byte\r\n", sizeof(*mod_known) * MAX_MOD_KNOWN);
}
int canNewModelBeLoaded(void)
{
    return !modelsFinalized;
}
void resetTempModKnown(void **smb, void **mpb)
{
    modelsFinalized = 0;
    internalFlashResetToCommonZoneEnd();
    mod_known = (model_t*) d_zbuffer; // we have a gillion of bytes there, not modified...
    memset(mod_known, 0, sizeof(*mod_known) * MAX_MOD_KNOWN);
    if (smb)
        *smb = (byte*) mod_known + sizeof(*mod_known) * MAX_MOD_KNOWN;
    if (mpb)
        *mpb = (byte*) *smb + sizeof(*smb) * MAX_MODELS;
}

