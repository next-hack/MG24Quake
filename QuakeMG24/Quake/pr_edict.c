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
// sv_edict.c -- entity dictionary
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
static void ED_ForceRemove(edict_t *ed);
#if USE_PROGSDAT
dprograms_t		*progs;
dfunction_t		*pr_functions;
char			*pr_strings;
ddef_t			*pr_fielddefs;
ddef_t			*pr_globaldefs;
dstatement_t	*pr_statements;
globalvars_t	*pr_global_struct;
float			*pr_globals;			// same as pr_global_struct
#else
uint8_t canForceEdictFree = false;
#endif
int pr_edict_size;	// in bytes

unsigned short pr_crc;

int type_size[8] =
{ 1, sizeof(string_t) / 4, 1, 3, 1, 1, sizeof(func_t) / 4, sizeof(void*) / 4
};
#if USE_PROGSDAT
ddef_t *ED_FieldAtOfs (int ofs);

qboolean	ED_ParseEpair (void *base, ddef_t *key, char *s);
#endif
#if USE_ORIGINAL_CVAR
cvar_t	nomonsters = {"nomonsters", "0"};
cvar_t	gamecfg = {"gamecfg", "0"};
cvar_t	scratch1 = {"scratch1", "0"};
cvar_t	scratch2 = {"scratch2", "0"};
cvar_t	scratch3 = {"scratch3", "0"};
cvar_t	scratch4 = {"scratch4", "0"};
cvar_t	savedgamecfg = {"savedgamecfg", "0", true};
cvar_t	saved1 = {"saved1", "0", true};
cvar_t	saved2 = {"saved2", "0", true};
cvar_t	saved3 = {"saved3", "0", true};
cvar_t	saved4 = {"saved4", "0", true};

#define	MAX_FIELD_LEN	64
#define GEFV_CACHESIZE	2

typedef struct {
	ddef_t	*pcache;
	char	field[MAX_FIELD_LEN];
} gefv_cache;

static gefv_cache	gefvCache[GEFV_CACHESIZE] = {{NULL, ""}, {NULL, ""}};
#endif
#if EDICT_LINKED_LIST_WITH_WATCH
static uint8_t hasBeenWatchedEntityFreed = 0;
static edict_t * watchedEntityForFree = NULL;
#endif
/*
 =================
 ED_ClearEdict

 Sets everything to NULL
 =================
 */
void ED_ClearEdict(edict_t *e)
{
#if USE_PROGSDAT
	memset (&e->v, 0, progs->entityfields * 4);
	e->free = false;

	#else
    edictDbgPrintf("clearing. Size of is %d\r\n", getEdictEntvarSize(e));
    // FIXME("");
#if !EDICT_LINKED_LIST_WITH_WATCH
    e->free = false;
#endif
    fastMemclear32(&e->v, getEdictEntvarSize(e) / 4);
#endif
}
//
#if EDICT_LINKED_LIST_WITH_WATCH // required because entity might self free
void ED_WatchForFree(edict_t *e)
{
    hasBeenWatchedEntityFreed = 0;
    printf("Watching entity: %d\r\n", e);
    watchedEntityForFree = e;
}
int ED_hasBeenWatchedEntityFreed(edict_t *ent)
{
    if (watchedEntityForFree != ent)
        while(1)  FIXME("WATCHED ENTITY CHANGED!");
    if (hasBeenWatchedEntityFreed)
    {
        hasBeenWatchedEntityFreed = 0;
        return 1;
    }
    else
    {
        return 0;
    }
}

#endif
edict_t* findOldestRemovableEdict(int isMissile)
{
    float thinkTime = host_time + 1E6;  // should be enough :)
    edict_t *oldest = NULL;
    edict_t *e = sv.edicts;
    while ((e = getNextEdict(e)) != END_EDICT)
    {
        int className = get_qcc_classname(e);
        if ((isMissile
            && (className == progs_zom_gib_mdl_string_index || className == progs_gib1_mdl_string_index || className == progs_gib2_mdl_string_index
                || className == progs_gib3_mdl_string_index)) || (!isMissile && className == nh_backpack_string_index))
        {
            float nextThink = get_qcc_nextthink(e);
            if (nextThink < thinkTime)
            {
                // found a candidate. Let's see others.
                oldest = e;
                nextThink = thinkTime;
                #if WIN32
                    printf("found %s as candidate\r\n", getStringFromIndex(className));
                #endif // WIN32
            }
        }
    }
    if (!oldest && isMissile)
    {
        #if WIN32
            printf("Not found. Trying to remove missiles then!\r\n");
        #endif // WIN32
        e = sv.edicts;
        while ((e = getNextEdict(e)) != END_EDICT)
        {
            // check again. Remove missiles
            isMissile = qcc_classname2type[get_qcc_classname(e)] == missile_edict_idx;
            if (isMissile)
            {
                float nextThink = get_qcc_nextthink(e);
                if (nextThink < thinkTime)
                {
                    // found a candidate. Let's see others.
                    oldest = e;
                    nextThink = thinkTime;
                    #if WIN32
                        printf("found %s as candidate\r\n", getStringFromIndex(get_qcc_classname(e)));
                    #endif // WIN32
                }
            }
        }
    }
    return oldest;
}
// last resort. Remove all removable edicts, hoping that this won't crash anything and there will be 2 consecutive edicts that can hold a new one
void freeAllRemovableEdicts(void)
{
    edict_t *e = sv.edicts;
    do
    {

        int className = get_qcc_classname(e);
        // remove all gibs, spawn backpacks and dead monsters
        if (className == progs_zom_gib_mdl_string_index || className == progs_gib1_mdl_string_index || className == progs_gib2_mdl_string_index
            || className == progs_gib3_mdl_string_index || className == nh_backpack_string_index
            || (qcc_classname2type[className] == monster_edict_idx && get_qcc_health(e) <= 0))
        {
            edict_t *r = e;
            e = getNextEdict(e);
            ED_ForceRemove(r);      // TODO: is it an issue, if we force remove a gib or a backpack?
        }
        else
        {   // just go to next edict.
            e = getNextEdict(e);
        }
    }
    while (e != END_EDICT);
}

/*
 =================
 ED_Alloc

 Either finds a free edict, or allocates a new one.
 Try to avoid reusing an entity that was recently freed, because it
 can cause the client to think the entity morphed into something else
 instead of being removed and recreated, which can cause interpolated
 angles and bad trails.
 =================
 */
edict_t* ED_Alloc(uint16_t className)
{
    STATIC_ASSERT(sizeof(nh_wiz_startfast_entvars_t) == sizeof(missile_entvars_t));
    edict_t *e;
    int reused = false;
#if !EDICT_LINKED_LIST
    #error
#endif
    // allocate space
    // FIXME automatically generated.
    int type = qcc_classname2type[className];
    e = allocEdByType(type);
    if (e == NULL)
    {
        #if WIN32
            printf("Failed on allocation. Trying to reuse an old edict\r\n");
        #endif
        // not enough memory. We need to clean up less useful stuff.
        // If we have to spawn a gib, then use the oldest gib. If not available, then try free all backpacks and gibs.
        // if (className == progs_zom_gib_mdl_string_index || className == progs_gib1_mdl_string_index || className == progs_gib2_mdl_string_index || progs_gib3_mdl_string_index)
        if (type == missile_edict_idx || type == nh_wiz_startfast_edict_idx) // as gibs are missile, we can swap missiles for gibs.
        {
            e = findOldestRemovableEdict(true);
        }
        else if (className == nh_backpack_string_index)
        {
            e = findOldestRemovableEdict(false);
        }
        if (e == NULL)
        {
            #if WIN32
                printf("freeing all what I can. I want to allocate class %s\r\n", getStringFromIndex(className));
            #endif
            freeAllRemovableEdicts();
            e = allocEdByType(type);
            if (e == NULL)
            {
                FIXME("Error in allocating entity. blocking");
                while (1)
                    ;
            }
        }
        else
        {
            edictDbgPrintf("Reused edict %p\r\n", e);

            // if we are here, we have reused an old entity, just changing position and other data.
            reused = true;
        }
        // If we have to spawn a backpack, then free oldest backpack.
    }
    if ((className == worldspawn_string_index) != (sv.lastEdict == NULL))
    {
        FIXME("Error, worldspawn was not the first edict");
    }
    if (className == worldspawn_string_index)
    {
        sv.edicts = e;
    }
    // is last edict non null ?
    if (!reused)
    {
        if (sv.lastEdict != NULL)
        {
            setNextEdict(sv.lastEdict, e);
        }
        setNextEdict(e, END_EDICT);
        sv.lastEdict = e;
        sv.num_edicts++;
        if (sv.num_edicts == MAX_EDICTS)
            Sys_Error("ED_Alloc: no free edicts");
    } edictDbgPrintf(">>>>>>>>>>>>>>>>>>>>> num Entities: %d\r\n", sv.num_edicts);
    e->qcc_classname = className;   // must be set before!
    ED_ClearEdict(e);
    return e;
}
//
static void ED_ForceRemove(edict_t *ed)
{
    edict_t *next_ent = getNextEdict(ed);  // could be NULL
    if (ed == sv.edicts)
    {
        while (1)
            FIXME("CAN'T FREE the world!");
    }
    edict_t *prev_ent = sv.edicts;

    while (getNextEdict(prev_ent) != ed)
    {
        prev_ent = getNextEdict(prev_ent);
    }
    if (ed == sv.lastEdict)
    {
        sv.lastEdict = prev_ent;
    }
    // Remove link between previous and the edict to be removed. Connect to next_ent instead.
    setNextEdict(prev_ent, next_ent);
    // reduce by 1 the count.
    if (sv.num_edicts > 0)
    {
        sv.num_edicts--;
        edictDbgPrintf (">>>>>>>>>>>>>>>>>EdForceFree: Number of edicts: %d\r\n",sv.num_edicts);
    }
    else
    {
        FIXME("sv.num_edicts == 0 on free\r\n");
    }
#if EDICT_LINKED_LIST_WITH_WATCH
    if (watchedEntityForFree == ed)
    {
        hasBeenWatchedEntityFreed = 1;
    }
    else
    {
        hasBeenWatchedEntityFreed = 0;
    }
    #else
    ed->free = true;
#endif
    Z_Free(ed);

}

/*
 =================
 ED_Free

 Marks the edict as free
 FIXME: walk all entities and NULL out references to this entity
 =================
 */
void ED_Free(edict_t *ed)
{
    edictDbgPrintf("freeing edict model class name %s\r\n", getStringFromIndex(ed->qcc_classname));
    SV_UnlinkEdict(ed);		// unlink from world bsp

#if EDICT_LINKED_LIST
#if EDICT_IMMEDIATE_FREE
`       ED_ForceRemove(ed);
#else
    ed->free = true;
    if (canForceEdictFree)
        ED_ForceRemove(ed);

#endif
#else
        ed->free = true;
        set_qcc_model(ed,  0);
        set_qcc_takedamage(ed,  0);
        set_qcc_modelindex(ed,  0);
        set_qcc_colormap(ed,  0);
        set_qcc_skin(ed,  0);
        set_qcc_frame(ed,  0);
set_qcc_origin(ed, vectorize(vec3_origin));
set_qcc_angles(ed, vectorize(vec3_origin));
        set_qcc_nextthink(ed,  -1);
        set_qcc_solid(ed,  0);
	#endif
//	ed->freetime = sv.time;

}
#if !EDICT_IMMEDIATE_FREE
/*
 * next-hack: this function was added because we can simply free entities immediately, we must do at the end of physics.
 */
void ED_PendingRemoval(void)
{
    edict_t *e = sv.edicts;
    if (e == NULL)
    {
#if WIN32
        FIXME("Warning null sv.edicts on ED_PendingRemoval()\r\n");
#endif
        return;
    }
    e = getNextEdict(e);
    for (int i = 1; i < sv.num_edicts; i++)
    {
        if (END_EDICT == e)
            break;
        if (e->free)
        {
            edict_t *d = e;
            e = getNextEdict(e);
            ED_ForceRemove(d);
        }
        else
        {
            e = getNextEdict(e);
        }
    }
}
#endif

//===========================================================================

/*
 ============
 ED_GlobalAtOfs
 ============
 */
#if USE_PROGSDAT
ddef_t *ED_GlobalAtOfs (int ofs)
{
	ddef_t		*def;
	int			i;

	for (i=0 ; i<progs->numglobaldefs ; i++)
	{
		def = &pr_globaldefs[i];
		if (def->ofs == ofs)
			return def;
	}
	return NULL;
}

/*
============
ED_FieldAtOfs
============
*/
ddef_t *ED_FieldAtOfs (int ofs)
{
	ddef_t		*def;
	int			i;

	for (i=0 ; i<progs->numfielddefs ; i++)
	{
		def = &pr_fielddefs[i];
		if (def->ofs == ofs)
			return def;
	}
	return NULL;
}

/*
============
ED_FindField
============
*/
ddef_t *ED_FindField (char *name)
{
	ddef_t		*def;
	int			i;

	for (i=0 ; i<progs->numfielddefs ; i++)
	{
		def = &pr_fielddefs[i];
		if (!strcmp(pr_strings + def->s_name,name) )
			return def;
	}
	return NULL;
}


/*
============
ED_FindGlobal
============
*/
ddef_t *ED_FindGlobal (char *name)
{
	ddef_t		*def;
	int			i;

	for (i=0 ; i<progs->numglobaldefs ; i++)
	{
		def = &pr_globaldefs[i];
		if (!strcmp(pr_strings + def->s_name,name) )
			return def;
	}
	return NULL;
}


/*
============
ED_FindFunction
============
*/
dfunction_t *ED_FindFunction (char *name)
{
	dfunction_t		*func;
	int				i;

	for (i=0 ; i<progs->numfunctions ; i++)
	{
		func = &pr_functions[i];
		if (!strcmp(pr_strings + func->s_name,name) )
			return func;
	}
	return NULL;
}

eval_t *GetEdictFieldValue(edict_t *ed, char *field)
{
	ddef_t			*def = NULL;
	int				i;
	static int		rep = 0;

	for (i=0 ; i<GEFV_CACHESIZE ; i++)
	{
		if (!strcmp(field, gefvCache[i].field))
		{
			def = gefvCache[i].pcache;
			goto Done;
		}
	}

	def = ED_FindField (field);

	if (strlen(field) < MAX_FIELD_LEN)
	{
		gefvCache[rep].pcache = def;
		strcpy (gefvCache[rep].field, field);
		rep ^= 1;
	}

Done:
	if (!def)
		return NULL;

	return (eval_t *)((char *)&ed->v + def->ofs*4);
}


/*
============
PR_ValueString

Returns a string describing *data in a type specific manner
=============
*/
char *PR_ValueString (etype_t type, eval_t *val)
{
	static char	line[256];
	ddef_t		*def;
	dfunction_t	*f;

	type &= ~DEF_SAVEGLOBAL;

	switch (type)
	{
	case ev_string:
		sprintf (line, "%s", pr_strings + val->string);
		break;
	case ev_entity:
		sprintf (line, "entity %i", NUM_FOR_EDICT(PROG_TO_EDICT(val->edict)) );
		break;
	case ev_function:
		f = pr_functions + val->function;
		sprintf (line, "%s()", pr_strings + f->s_name);
		break;
	case ev_field:
		def = ED_FieldAtOfs ( val->_int );
		sprintf (line, ".%s", pr_strings + def->s_name);
		break;
	case ev_void:
		sprintf (line, "void");
		break;
	case ev_float:
		sprintf (line, "%5.1f", val->_float);
		break;
	case ev_vector:
		sprintf (line, "'%5.1f %5.1f %5.1f'", val->vector[0], val->vector[1], val->vector[2]);
		break;
	case ev_pointer:
		sprintf (line, "pointer");
		break;
	default:
		sprintf (line, "bad type %i", type);
		break;
	}

	return line;
}
#endif

/*
 ============
 PR_UglyValueString

 Returns a string describing *data in a type specific manner
 Easier to parse than PR_ValueString
 =============
 */
#if USE_PROGSDAT
char *PR_UglyValueString (etype_t type, eval_t *val)
{
	static char	line[256];
	ddef_t		*def;
	dfunction_t	*f;

	type &= ~DEF_SAVEGLOBAL;

	switch (type)
	{
	case ev_string:
		sprintf (line, "%s", pr_strings + val->string);
		break;
	case ev_entity:
		sprintf (line, "%i", NUM_FOR_EDICT(PROG_TO_EDICT(val->edict)));
		break;
	case ev_function:
		f = pr_functions + val->function;
		sprintf (line, "%s", pr_strings + f->s_name);
		break;
	case ev_field:
		def = ED_FieldAtOfs ( val->_int );
		sprintf (line, "%s", pr_strings + def->s_name);
		break;
	case ev_void:
		sprintf (line, "void");
		break;
	case ev_float:
		sprintf (line, "%f", val->_float);
		break;
	case ev_vector:
		sprintf (line, "%f %f %f", val->vector[0], val->vector[1], val->vector[2]);
		break;
	default:
		sprintf (line, "bad type %i", type);
		break;
	}

	return line;
}

/*
============
PR_GlobalString

Returns a string with a description and the contents of a global,
padded to 20 field width
============
*/
char *PR_GlobalString (int ofs)
{
	char	*s;
	int		i;
	ddef_t	*def;
	void	*val;
	static char	line[128];

	val = (void *)&pr_globals[ofs];
	def = ED_GlobalAtOfs(ofs);
	if (!def)
		sprintf (line,"%i (?)", ofs);
	else
	{
		s = PR_ValueString (def->type, val);
		sprintf (line,"%i(%s)%s", ofs, pr_strings + def->s_name, s);
	}

	i = strlen(line);
	for ( ; i<20 ; i++)
		strcat (line," ");
	strcat (line," ");

	return line;
}

char *PR_GlobalStringNoContents (int ofs)
{
	int		i;
	ddef_t	*def;
	static char	line[128];

	def = ED_GlobalAtOfs(ofs);
	if (!def)
		sprintf (line,"%i (?)", ofs);
	else
		sprintf (line,"%i(%s)", ofs, pr_strings + def->s_name);

	i = strlen(line);
	for ( ; i<20 ; i++)
		strcat (line," ");
	strcat (line," ");

	return line;
}

#endif
/*
 =============
 ED_Print

 For debugging
 =============
 */

void ED_Print(edict_t *ed)
{
#if !EDICT_LINKED_LIST_WITH_WATCH
    if (ed->free)
    {
        Con_Printf("FREE\n");
        return;
    }
#endif
    Con_Printf("\nEDICT %i:\n", NUM_FOR_EDICT(ed));
#if USE_PROGSDAT
    int     l;

    int     *v;
    int     i, j;
    char    *name;
    int     type;

	ddef_t	*d;
	for (i=1 ; i<progs->numfielddefs ; i++)
	{
		d = &pr_fielddefs[i];
		name = pr_strings + d->s_name;
		if (name[strlen(name)-2] == '_')
			continue;	// skip _x, _y, _z vars

		v = (int *)((char *)&ed->v + d->ofs*4);

	// if the value is still all 0, skip the field
		type = d->type & ~DEF_SAVEGLOBAL;

		for (j=0 ; j<type_size[type] ; j++)
			if (v[j])
				break;
		if (j == type_size[type])
			continue;

		Con_Printf ("%s",name);
		l = strlen (name);
		while (l++ < 15)
			Con_Printf (" ");

		Con_Printf ("%s\n", PR_ValueString(d->type, (eval_t *)v));
	}
	#endif
}

/*
 =============
 ED_Write

 For savegames
 =============
 */
void ED_Write(FILE *f, edict_t *ed)
{
    (void) f;
    (void) ed;
#if USE_PROGSDAT
	ddef_t	*d;
	int		*v;
	int		i, j;
	char	*name;
	int		type;

	fprintf (f, "{\n");

	if (ed->free)
	{
		fprintf (f, "}\n");
		return;
	}

	for (i=1 ; i<progs->numfielddefs ; i++)
	{
		d = &pr_fielddefs[i];
		name = pr_strings + d->s_name;
		if (name[strlen(name)-2] == '_')
			continue;	// skip _x, _y, _z vars

		v = (int *)((char *)&ed->v + d->ofs*4);

	// if the value is still all 0, skip the field
		type = d->type & ~DEF_SAVEGLOBAL;
		for (j=0 ; j<type_size[type] ; j++)
			if (v[j])
				break;
		if (j == type_size[type])
			continue;

		fprintf (f,"\"%s\" ",name);
		fprintf (f,"\"%s\"\n", PR_UglyValueString(d->type, (eval_t *)v));
	}

	fprintf (f, "}\n");
	#else
    FIXME("Not implemented");
#endif
}

void ED_PrintNum(int ent)
{
#if !EDICT_LINKED_LIST
	ED_Print (EDICT_NUM(ent));
#else
    (void) ent;
    FIXME("Not implemented");
#endif
}

/*
 =============
 ED_PrintEdicts

 For debugging, prints all the entities in the current server
 =============
 */
void ED_PrintEdicts(void)
{
    int i;

    Con_Printf("%i entities\n", sv.num_edicts);
    for (i = 0; i < sv.num_edicts; i++)
        ED_PrintNum(i);
}

/*
 =============
 ED_PrintEdict_f

 For debugging, prints a single edicy
 =============
 */
void ED_PrintEdict_f(void)
{
    int i;

    i = Q_atoi(Cmd_Argv(1));
    if (i >= sv.num_edicts)
    {
        Con_Printf("Bad edict number\n");
        return;
    }
    ED_PrintNum(i);
}

/*
 =============
 ED_Count

 For debugging
 =============
 */
void ED_Count(void)
{
    int i;
    edict_t *ent;
    int active, models, solid, step;

    active = models = solid = step = 0;
    ent = sv.edicts;
    for (i = 0; i < sv.num_edicts; i++)
    {
#if !EDICT_LINKED_LIST
		ent = EDICT_NUM(i);
#endif
#if !EDICT_LINKED_LIST_WITH_WATCH
        if (!ent->free)
#endif
        {
            active++;
            if (get_qcc_solid(ent))
                solid++;
            if (get_qcc_model(ent))
                models++;
            if (get_qcc_movetype(ent) == MOVETYPE_STEP)
                step++;

        }
#if EDICT_LINKED_LIST
        ent = getNextEdict(ent);
#endif // EDICT_LINKED_LIST
    }

    Con_Printf("num_edicts:%3i\n", sv.num_edicts);
    Con_Printf("active    :%3i\n", active);
    Con_Printf("view      :%3i\n", models);
    Con_Printf("touch     :%3i\n", solid);
    Con_Printf("step      :%3i\n", step);

}

/*
 ==============================================================================

 ARCHIVING GLOBALS

 FIXME: need to tag constants, doesn't really work
 ==============================================================================
 */

/*
 =============
 ED_WriteGlobals
 =============
 */
void ED_WriteGlobals(FILE *f)
{
    (void) f;
#if USE_PROGSDAT
	ddef_t		*def;
	int			i;
	char		*name;
	int			type;

	fprintf (f,"{\n");
	for (i=0 ; i<progs->numglobaldefs ; i++)
	{
		def = &pr_globaldefs[i];
		type = def->type;
		if ( !(def->type & DEF_SAVEGLOBAL) )
			continue;
		type &= ~DEF_SAVEGLOBAL;

		if (type != ev_string
		&& type != ev_float
		&& type != ev_entity)
			continue;

		name = pr_strings + def->s_name;
		fprintf (f,"\"%s\" ", name);
		fprintf (f,"\"%s\"\n", PR_UglyValueString(type, (eval_t *)&pr_globals[def->ofs]));
	}
	fprintf (f,"}\n");
	#else
    FIXME("Not implemented WriteGlobals");
#endif
}

/*
 =============
 ED_ParseGlobals
 =============
 */
#if USE_PROGSDAT
void ED_ParseGlobals (char *data)
{
	char	keyname[64];
	ddef_t	*key;

	while (1)
	{
	// parse key
		data = COM_Parse (data);
		if (com_token[0] == '}')
			break;
		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

		strcpy (keyname, com_token);

	// parse value
		data = COM_Parse (data);
		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

		if (com_token[0] == '}')
			Sys_Error ("ED_ParseEntity: closing brace without data");

		key = ED_FindGlobal (keyname);
		if (!key)
		{
			Con_Printf ("'%s' is not a global\n", keyname);
			continue;
		}

		if (!ED_ParseEpair ((void *)pr_globals, key, com_token))
			Host_Error ("ED_ParseGlobals: parse error");
	}
}
#endif
//============================================================================

/*
 =============
 ED_NewString
 =============
 */
#if 0
char *ED_NewString (char *string)
{
	char	*new, *new_p;
	int		i,l;

	l = strlen(string) + 1;
	new = Hunk_Alloc (l);
	new_p = new;

	for (i=0 ; i< l ; i++)
	{
		if (string[i] == '\\' && i < l-1)
		{
			i++;
			if (string[i] == 'n')
				*new_p++ = '\n';
			else
				*new_p++ = '\\';
		}
		else
			*new_p++ = string[i];
	}

	return new;
}
#endif

/*
 =============
 ED_ParseEval

 Can parse either fields or globals
 returns false if error
 =============
 */
#if USE_PROGSDAT
qboolean	ED_ParseEpair (void *base, ddef_t *key, char *s)
{
	int		i;
	char	string[128];
	ddef_t	*def;
	char	*v, *w;
	void	*d;
	dfunction_t	*func;

	d = (void *)((int *)base + key->ofs);

	switch (key->type & ~DEF_SAVEGLOBAL)
	{
	case ev_string:
		*(string_t *)d = ED_NewString (s) - pr_strings;
		break;

	case ev_float:
		*(float *)d = atof (s);
		break;

	case ev_vector:
		strcpy (string, s);
		v = string;
		w = string;
		for (i=0 ; i<3 ; i++)
		{
			while (*v && *v != ' ')
				v++;
			*v = 0;
			((float *)d)[i] = atof (w);
			w = v = v+1;
		}
		break;

	case ev_entity:
		*(int *)d = EDICT_TO_PROG(EDICT_NUM(atoi (s)));
		break;

	case ev_field:
		def = ED_FindField (s);
		if (!def)
		{
			Con_Printf ("Can't find field %s\n", s);
			return false;
		}
		*(int *)d = G_INT(def->ofs);
		break;

	case ev_function:
		func = ED_FindFunction (s);
		if (!func)
		{
			Con_Printf ("Can't find function %s\n", s);
			return false;
		}
		*(func_t *)d = func - pr_functions;
		break;

	default:
		break;
	}
	return true;
}
#endif
/*
 ====================
 ED_ParseEdict

 Parses an edict out of the given string, returning the new position
 ed should be a properly initialized empty edict.
 Used for initial level load and for savegames.
 ====================
 */
#if USE_PROGSDAT
char *ED_ParseEdict (char *data, edict_t *ent)
{
	ddef_t		*key;
	qboolean	anglehack;
	qboolean	init;
	char		keyname[256];
	int			n;

	init = false;

// clear it
	if (ent != sv.edicts)	// hack
		memset (&ent->v, 0, progs->entityfields * 4);

// go through all the dictionary pairs
	while (1)
	{
	// parse key
		data = COM_Parse (data);
		if (com_token[0] == '}')
			break;
		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

// anglehack is to allow QuakeEd to write single scalar angles
// and allow them to be turned into vectors. (FIXME...)
if (!strcmp(com_token, "angle"))
{
	strcpy (com_token, "angles");
	anglehack = true;
}
else
	anglehack = false;

// FIXME: change light to _light to get rid of this hack
if (!strcmp(com_token, "light"))
	strcpy (com_token, "light_lev");	// hack for single light def

		strcpy (keyname, com_token);

		// another hack to fix heynames with trailing spaces
		n = strlen(keyname);
		while (n && keyname[n-1] == ' ')
		{
			keyname[n-1] = 0;
			n--;
		}

	// parse value
		data = COM_Parse (data);

		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

		if (com_token[0] == '}')
			Sys_Error ("ED_ParseEntity: closing brace without data");

		init = true;

// keynames with a leading underscore are used for utility comments,
// and are immediately discarded by quake
		if (keyname[0] == '_')
			continue;

		key = ED_FindField (keyname);
		if (!key)
		{
			Con_Printf ("'%s' is not a field\n", keyname);
			continue;
		}

if (anglehack)
{
char	temp[32];
strcpy (temp, com_token);
sprintf (com_token, "0 %s 0", temp);
}
        printf("Keyname is %s and value is %s\r\n", keyname, com_token);

		if (!ED_ParseEpair ((void *)&ent->v, key, com_token))
			Host_Error ("ED_ParseEdict: parse error");
	}

	if (!init)
		ent->free = true;

	return data;
}
#else

#define str(s) #s
typedef struct
{
    const char *name;
    void (*spawn_function)(void);
} entityDef_t;
#define def_ent(x) {str(x), qcc_##x}
const entityDef_t entityDefList[] =
{
    def_ent(air_bubbles),                 //  : Rising bubbles
    def_ent(ambient_drip),                //   : Dripping sound
    def_ent(ambient_drone),               //   : Engine/machinery sound
    def_ent(ambient_comp_hum),            //  : Computer background sounds
    def_ent(ambient_swamp1),              //  : Frogs croaking
    def_ent(ambient_swamp2),              //  : Slightly different sounding frogs croaking
    def_ent(event_lightning),             //  : Lightning (Used to kill Cthon, shareware boss)
    def_ent(func_door),                   //  : Door
    def_ent(func_door_secret),            //  : A door that is triggered to open
    def_ent(func_wall),                   //  : A moving wall?
    def_ent(func_button),                 //  : A button
    def_ent(func_train),                  //  : A platform (moves along a "train")
    def_ent(func_plat),                   //  : A lift/elevator
//   def_ent(func_dm_only),                //  : A teleporter that only appears in deathmatch
    def_ent(info_null),                   //  : no idea
    def_ent(info_intermission),           //  : Cameras positioning for intermission (?)
    def_ent(info_player_start),           //  : Main player starting point (only one allowed)
    def_ent(info_player_deathmatch),      //  : A deathmatch start (more than one allowed)
    def_ent(info_player_coop),            //  : A coop player start (more than one allowed)
    def_ent(info_player_start2),          //  : ? Player2 start?
    def_ent(info_teleport_destination),   //  : Gives coords for a teleport destination using a targetname
    //All item_ tags may have a target tag.  It triggers the event when the item is picked up.
    def_ent(item_cells),                  //  : Ammo for the Thunderbolt
    def_ent(item_rockets),                //  : Ammo for Rocket/Grenade Launcher
    def_ent(item_shells),                 //  : Ammo for both Shotgun and SuperShotgun
    def_ent(item_spikes),                 //  : Ammo for Perforator and Super Perforator
    def_ent(item_health),                 //  : Medkit
    def_ent(item_artifact_envirosuit),    //  : Environmental Protection Suit
    def_ent(item_artifact_super_damage),  //  : Quad Damage
    def_ent(item_artifact_invulnerability), // : Pentagram of Protection
    def_ent(item_artifact_invisibility),   // : Ring of Shadows (Invisibility)
    def_ent(item_armorInv),                // : Red armor
    def_ent(item_armor2),                  // : Yellow armor
    def_ent(item_armor1),                  // : Green armor
    def_ent(item_key1),                    // : Silver Key
    def_ent(item_key2),                    // : Gold Key
    def_ent(item_sigil),                   // : Sigil (a rune)
    def_ent(light),                        // : A projected light. No visible lightsource.
    def_ent(light_torch_small_walltorch),  // : Small wall torch (gives off light)
    def_ent(light_flame_large_yellow),     // : Large yellow fire (gives off light)
    def_ent(light_flame_small_yellow),     // : Small yellow fire (gives off light)
    def_ent(light_flame_small_white),      // : Small white fire  (gives off light)
    def_ent(light_fluoro),                 //  : Fluorescent light? (Gives off light, humming sound?)
    def_ent(light_fluorospark),            // : Fluorescent light? (Gives off light, makes sparking sound)
    def_ent(monster_army),                 // : Grunt
    def_ent(monster_dog),                  // : Attack dog
    def_ent(monster_ogre),                 // : Ogre
    def_ent(monster_knight),               // : Knight
    def_ent(monster_zombie),               // : Zombie
    def_ent(monster_wizard),               // : Scragg (Wizard)
    def_ent(monster_demon1),               // : Fiend (Demon)
    def_ent(monster_shambler),             // : Shambler
    def_ent(monster_boss),                 // : Cthon (Boss of Shareware Quake)
    def_ent(misc_fireball),                // : Small fireball (gives off light, harms player)
    def_ent(misc_explobox),                // : Nuclear container (explodes upon being shot, harms player)
    def_ent(path_corner),                  // : Used to define path of func_train platforms
    def_ent(trap_spikeshooter),            // : Shoots spikes (nails)
    def_ent(trap_shooter),                 // : Fires nails without needing to be triggered.
    def_ent(trigger_teleport),             // : Teleport (all trigger_ tags are triggered by walkover)
    def_ent(trigger_changelevel),          // : Changes to another level
    def_ent(trigger_setskill),             // : Changes skill level
    def_ent(trigger_counter),              // : Triggers action after it has been triggered count times.
    def_ent(trigger_once),                 // : Triggers action only once
    def_ent(trigger_multiple),             // : Triggers action (can be retriggered)
    def_ent(trigger_onlyregistered),       // : Triggers only if game is registered (registered == 1)
    def_ent(trigger_secret),               // : Triggers action and awards secret credit.
    def_ent(trigger_monsterjump),          // : Causes a targeted monster to jump [off something]?
    def_ent(trigger_relay),                // : Allows delayed/multiple actions from one trigger
    def_ent(trigger_push),				 //	 : Pushes a player in a direction (like a windtunnel)
    def_ent(weapon_supershotgun),          // : Super Shotgun
    def_ent(weapon_nailgun),               // : Perforator
    def_ent(weapon_supernailgun),          // : Super Perforator
    def_ent(weapon_grenadelauncher),       // : Grenade Launcher
    def_ent(weapon_rocketlauncher),        // : Rocket Launcher
    def_ent(weapon_lightning),             // : Lightning Gun
    def_ent(worldspawn),                     // : World
    def_ent(light),                          // : light
    def_ent(light_torch_small_walltorch),
    def_ent(misc_fireball),
    def_ent(trigger_teleport),
    def_ent(light_fluorospark),
    def_ent(light_fluoro),
    def_ent(light_torch_small_walltorch),
    def_ent(info_teleport_destination),
    def_ent(func_door),
    def_ent(func_bossgate),
    def_ent(func_episodegate),
    #if RETAIL_QUAKE_PAK_SUPPORT
    def_ent(func_illusionary),
    def_ent(misc_explobox2),
    def_ent(monster_enforcer),
    def_ent(item_weapon),
    def_ent(monster_hell_knight),
    def_ent(monster_fish),
    def_ent(monster_shalrath),
    def_ent(ambient_suck_wind),
    def_ent(monster_tarbaby),
    def_ent(light_globe),
    def_ent(monster_oldone),
    def_ent(trigger_hurt),
    def_ent(misc_teleporttrain),
    #endif
};
//
#define DYNAMIC_STRINGS 0
#if DYNAMIC_STRINGS
#define MAX_DYNAMIC_STRINGS 1024
char *dynamicStrings[MAX_DYNAMIC_STRINGS] = {0};
int dynamicStringsNum = 0;
#else
#include "pakStrings.h"
#endif
extern const char localmodels[MAX_MODELS][5];

char* getStringFromIndex(int16_t index)
{

    if (index == 0)
        return NULL;
    if (index == tempPrintString_string_index)
        return tempPrintString;
    else if (index > 0)
    {
        return (char*) quakeProgStrings[index];
    }
    else if (index > SUBMODEL_NAME_START_INDEX)
    {
        // from -512 to -1023
        index = -index;
        index += ENTITY_LIST_START_INDEX;
        return (char*) entityDefList[index].name;
    }
    else if (index > DYNAMIC_STRING_INDEX)
    {
        // from -1024 to -1535
        index = -index;
        index += SUBMODEL_NAME_START_INDEX;
        return (char*) localmodels[index];
    }
    else
    {
        // -1536 up to -2047
        index = -index;
        index += DYNAMIC_STRING_INDEX;
#if !DYNAMIC_STRINGS
        return (char*) pakStrings[index];
#else
        return dynamicStrings[index];
#endif
        while (1)
        {
            printf("stooopid index %d", index);
            FIXME("Wrong index\r\n");
        }
    }
}
typedef struct
{
    const char *name;
    int (*handler)(edict_t *e, const char *value);
    void (*copyHandler)(edict_t *dst, edict_t *src);
} ed_properties_t;
float parse_float(const char *s)
{
    return Q_atof(s);
}
vector parse_vector(const char *s)
{
    char string[128];
    char *v, *w;
    strcpy(string, s);
    v = string;
    w = string;
    vector ret;
    for (int i = 0; i < 3; i++)
    {
        while (*v && *v != ' ')
            v++;
        *v = 0;
        ret.v[i] = Q_atof(w);
        w = v = v + 1;
    }
    return ret;
}
void strToCstr(char *out, const char *in, int size)
{
    int inpos = 0;
    int outpos = 0;
    char c;
    while (outpos < size - 2)
    {
        c = in[inpos];
        if (!c)
        {
            out[outpos] = 0;
            return;
        }
        else if (c == '\\')
        {
            inpos++;
            c = in[inpos];
            switch (c)
            {
                case '\"':
                    out[outpos] = '\"';
                    break;
                case 'r':
                    out[outpos] = '\r';
                    break;

                case 'n':
                    out[outpos] = '\n';
                    break;

                case '\\':
                    out[outpos] = '\\';
                    break;
                default:
                    out[outpos++] = '\\';
                    out[outpos] = c;
            }
        }
        else
        {
            out[outpos] = c;
        }
        outpos++;
        inpos++;
    }
    out[outpos] = 0;
}
//
int16_t findStringIndex(const char *value)
{
    edictDbgPrintf("looking for string %s\r\n", value);
    for (int i = 1; i < tempPrintString_string_index; i++)
    {
        if (!strcmp(quakeProgStrings[i], value))
        {
            return i;
        }
    }
    // let's check on entity list
    for (unsigned int i = 0; i < sizeof(entityDefList) / sizeof(entityDefList[0]); i++)
    {
        if (!strcmp(entityDefList[i].name, value))
        {
            return -i + ENTITY_LIST_START_INDEX;
        }
    }
    // not found. Look at the models
    for (int i = 0; i < MAX_MODELS; i++)
    {
        if (!strcmp(localmodels[i], value))
        {
            return -i + SUBMODEL_NAME_START_INDEX;
        }
    }
#if DYNAMIC_STRINGS
    for (int i = 0; i < dynamicStringsNum; i++)
    {
        if (!strcmp(dynamicStrings[i], value))
        {
            return -i + DYNAMIC_STRING_INDEX;
        }
    }
    // then add.
    if (dynamicStringsNum < MAX_DYNAMIC_STRINGS)
    {
        int len = strlen(value);
        char *s = calloc (1, len + 1);
        strcpy(s, value);
        printf("Creating new string, index %d, string %s\r\n", dynamicStringsNum, s);
        dynamicStrings[dynamicStringsNum++] = s;
        return - dynamicStringsNum + DYNAMIC_STRING_INDEX + 1;
    }
#else
    char tmp[1024];
    strToCstr(tmp, value, sizeof(tmp));
    for (int i = 0; i < MAX_PAK_STRINGS; i++)
    {
        if (!strcmp(pakStrings[i], tmp))
        {
            return -i + DYNAMIC_STRING_INDEX;
        }
    }

#endif
    return -32768;
}
int is_float_non_zero(float value)
{
#if WIN32
    edictDbgPrintf("float: %f\r\n",value);
	#endif
    return value != 0;
}
int is_vector_non_zero(vector value)
{
#if WIN32
    edictDbgPrintf("Vector: %f %f %f\r\n", value.x, value.y, value.z);
    #endif
    return value.x != 0 || value.y != 0 || value.z != 0;
}

#define DEF_PROP(n) {#n, ed_set_ ## n, ed_copy_ ## n}

#define implement_default_parse_handler(name, type) \
int ed_set_##name(edict_t *e, const char  *value) \
{                                             \
    type parsed;                              \
    parsed = parse_##type(value);             \
    set_qcc_##name(e, parsed);                   \
    return 1;                                 \
}   \
void ed_copy_##name(edict_t *dst, edict_t* src) \
{                                             \
    type value = get_qcc_##name(src); \
    if (is_##type##_non_zero(value)) \
        set_qcc_##name(dst, value);\
}

#define implement_string_parse_handler(name)        \
int ed_set_##name(edict_t *e, const char  *value)       \
{                                                   \
    int16_t idx = findStringIndex(value);             \
    if (idx != -32768)                                    \
    {                                               \
        set_qcc_##name(e, idx);                        \
        edictDbgPrintf("Found " #name " %s, index %d\r\n", value, idx); \
        return 1;                                           \
    }                                                       \
    else                                                    \
    {                                                       \
        edictDbgPrintf(#name " %s not found\r\n", value);            \
        FIXME("");                                          \
    }                               \
    return 0;                               \
} \
void ed_copy_##name(edict_t *dst, edict_t* src) \
{                                             \
    if (get_qcc_##name(src))                  \
    set_qcc_##name(dst, get_qcc_##name(src)); \
}
#if WIN32
    #define parsePrintf printf
#else
#define parsePrintf(...)
#endif
#define implement_dummy_string_parse_handler(name)        \
int ed_set_##name(edict_t *e, const char  *value)       \
{                                                   \
    (void) e;                                        \
    (void) value;                                       \
   edictDbgPrintf("Ignoring unused property " #name "\r\n"); \
   return 1;    \
} \
void ed_copy_##name(edict_t *dst, edict_t* src) \
{                                             \
    (void) dst;   \
    (void) src;   \
}
static int16_t currentParseClassName;
int ed_set_classname(edict_t *e, const char *value)
{
    // note: this will not really change the classname of the edict directly. It is done later.
    // It just changes currentParseClassName.
    (void) e;
    int16_t idx = findStringIndex(value);
    currentParseClassName = idx;
    if (idx != -32768)
    {
        edictDbgPrintf("Found classname %s, index %d\r\n", value, idx);
        return 1;
    }
    else
    {
        printf("classname %s not found\r\n", value);
        FIXME("");
    }
    return 0;
}
void ed_copy_classname(edict_t *dst, edict_t *src)
{
    // done externally, but this must still be declared.
    (void) dst;
    (void) src;
}

//implement_string_parse_handler(classname);
implement_string_parse_handler(target);
implement_string_parse_handler(targetname);
implement_string_parse_handler(killtarget);
implement_string_parse_handler(message);
implement_string_parse_handler(map);
implement_string_parse_handler(model);
implement_default_parse_handler(origin, vector);
implement_default_parse_handler(angles, vector);
implement_default_parse_handler(spawnflags, float);
implement_default_parse_handler(style, float);
implement_default_parse_handler(mangle, vector);
implement_default_parse_handler(speed, float);
implement_default_parse_handler(wait, float);
implement_default_parse_handler(lip, float);
implement_default_parse_handler(dmg, float);
implement_default_parse_handler(health, float);
implement_default_parse_handler(delay, float);
implement_default_parse_handler(sounds, float);
implement_default_parse_handler(height, float);
implement_default_parse_handler(worldtype, float);
implement_default_parse_handler(count, float);
// dummy
implement_dummy_string_parse_handler(light_lev);
implement_dummy_string_parse_handler(wad);
const ed_properties_t propertyList[] =
{
    DEF_PROP(classname),  // "name"    // Type of entity to be defined (mandatory)
    DEF_PROP(origin),    // "X Y Z"   // Coordinates of where it starts in space.
    DEF_PROP(angles),     // "#"       // Direction it faces or moves (sometimes in degrees)
    DEF_PROP(light_lev),     // "#"       // Used with the light classname. THIS IS NOT USED SO CUSTOM SETTER IS CREATED
    DEF_PROP(wad),      //  "wadfile" // The wad2 graphics file used by the world for textures. This is not really used. CUSTOM SETTER IS CREATED
    DEF_PROP(target),    // "t#"      // Matches a targetname.
    DEF_PROP(targetname), // "t#"      // Like a linedef tag.
    DEF_PROP(killtarget), // "#"       // How much damage the model causes when it shuts on you?
    DEF_PROP(spawnflags), // "#"       // Used to flag/describe an entity that is not default.
    DEF_PROP(style),     // "#"       // Used to flag/describe an entity that is not default.
    DEF_PROP(message),   // "string"  // Message displayed when triggered (/n for linebreaks)
    DEF_PROP(mangle),    // "X Y Z"   // Point where the intermission camera looks at
    DEF_PROP(speed),    // "#"       // How fast the model is moved.
    DEF_PROP(wait),     // "#"       // How long a pause between completion of movement or
    DEF_PROP(lip),       // "#"       // Seems to be a means of adjusting the starting position.
    DEF_PROP(dmg),       //  "#"       // How much damage the model causes when it shuts on you?
    DEF_PROP(health),    // "#"       // How much damage the model takes before it triggers
    DEF_PROP(delay),    //  "#"       // Time before event is triggered
    DEF_PROP(sounds),   //  "#"       // How much damage the model causes when it shuts on you?
    DEF_PROP(height),   //  "#"       // How high a platform will raise
    DEF_PROP(worldtype),
    DEF_PROP(map),
    DEF_PROP(model),
    DEF_PROP(count),

};
int ED_StoreValue(edict_t *v, const char *keyname, const char *token)
{
    for (unsigned int i = 0; i < sizeof(propertyList) / sizeof(propertyList[0]); i++)
    {
        if (!strcmp(propertyList[i].name, keyname))
        {
            return propertyList[i].handler(v, token);
        }
    }
    printf("\r\nProperty: %s not found\r\n", keyname);
    FIXME("");
    return 0;
}
char* ED_ParseEdict(char *data, edict_t *ent)
{
    //ddef_t		*key;
    qboolean anglehack;
    qboolean init;
    char keyname[256];
    int n;
    char com_token[1024];
    init = false;

// clear it
    if (ent != sv.edicts)	// hack
        memset(&ent->v, 0, sizeof(ent->v));

// go through all the dictionary pairs
    while (1)
    {
        // parse key
        data = COM_Parse(data, com_token);
        if (com_token[0] == '}')
            break;
        if (!data)
            Sys_Error("ED_ParseEntity: EOF without closing brace");

// anglehack is to allow QuakeEd to write single scalar angles
// and allow them to be turned into vectors. (FIXME...)
        if (!strcmp(com_token, "angle"))
        {
            strcpy(com_token, "angles");
            anglehack = true;
        }
        else
            anglehack = false;

// FIXME: change light to _light to get rid of this hack
        if (!strcmp(com_token, "light"))
            strcpy(com_token, "light_lev");	// hack for single light def

        strcpy(keyname, com_token);

        // another hack to fix heynames with trailing spaces
        n = strlen(keyname);
        while (n && keyname[n - 1] == ' ')
        {
            keyname[n - 1] = 0;
            n--;
        }

        // parse value
        data = COM_Parse(data, com_token);
        if (!data)
            Sys_Error("ED_ParseEntity: EOF without closing brace");

        if (com_token[0] == '}')
            Sys_Error("ED_ParseEntity: closing brace without data");

        init = true;

// keynames with a leading underscore are used for utility comments,
// and are immediately discarded by quake
        if (keyname[0] == '_')
            continue;
#if DEBUG_EDICTS
        printf("Keyname is %s, value is %s\r\n", keyname, com_token);
#endif
        if (anglehack)
        {
            char temp[32];
            strcpy(temp, com_token);
            sprintf(com_token, "0 %s 0", temp);
        }

#if NOT_YET_IMPLEMENTED
		key = ED_FindField (keyname);
		if (!key)
		{
			Con_Printf ("'%s' is not a field\n", keyname);
			continue;
		}
		if (!ED_ParseEpair ((void *)&ent->v, key, com_token))
			Host_Error ("ED_ParseEdict: parse error");
#else
        if (!ED_StoreValue(ent, keyname, com_token))
        {
#define TEST_MODELS 1
#if !TEST_MODELS
                Host_Error ("ED_ParseEdict: parse error");
            #endif
        }
#endif
    }

    if (!init)
#if !EDICT_LINKED_LIST_WITH_WATCH
        ent->free = true;
#elif EDICT_LINKED_LIST
    while(1) FIXME("EDICT NOT INITIALIZED!!!");
#endif

    return data;
}
#endif

#if !USE_PROGSDAT
void* ED_FindSpawnFunction(char *name)
{
    for (unsigned int i = 0; i < sizeof(entityDefList) / sizeof(entityDefList[0]); i++)
    {
        if (!strcmp(name, entityDefList[i].name))
            return entityDefList[i].spawn_function;
    }
    return NULL;
}
#endif
void ED_CopyNonZeroFields(edict_t *dst, edict_t *src)
{
    static_light_romEntvars_t *entvars;
    int type = qcc_classname2type[dst->qcc_classname];
    if (type == static_light_edict_idx)
    {
        // will be freed by makestatic
        entvars = Z_Calloc(sizeof(*entvars), 1, PU_STATIC, NULL);
        ((static_light_edict_t*) dst)->v.romEntvars = entvars;
    }
    for (unsigned int i = 0; i < sizeof(propertyList) / sizeof(propertyList[0]); i++)
    {
        propertyList[i].copyHandler(dst, src);
    }

}
/*
 ================
 ED_LoadFromFile

 The entities are directly placed in the array, rather than allocated with
 ED_Alloc, because otherwise an error loading the map would have entity
 number references out of order.

 Creates a server's entity / program execution context by
 parsing textual entity definitions out of an ent file.

 Used for both fresh maps and savegame loads.  A fresh map would also need
 to call ED_CallSpawnFunctions () to let the objects initialize themselves.
 ================
 */
void ED_LoadFromFile(char *data)
{
    char com_token[1024];
#if USE_PROGSDAT
	edict_t		*ent;
	int			inhibit;
	dfunction_t	*func;

	ent = NULL;
	inhibit = 0;
	pr_global_struct->time = sv.time;

// parse ents
	while (1)
	{
// parse the opening brace
		data = COM_Parse (data);
		if (!data)
			break;
		if (com_token[0] != '{')
			Sys_Error ("ED_LoadFromFile: found %s when expecting {",com_token);

		if (!ent)
			ent = EDICT_NUM(0);
		else
			ent = ED_Alloc ();
		data = ED_ParseEdict (data, ent);

// remove things from different skill levels or deathmatch
		if (deathmatch)
		{
			if (((int)get_qcc_spawnflags(ent) & SPAWNFLAG_NOT_DEATHMATCH))
			{
				ED_Free (ent);
				inhibit++;
				continue;
			}
		}
		else if ((current_skill == 0 && ((int)get_qcc_spawnflags(ent) & SPAWNFLAG_NOT_EASY))
				|| (current_skill == 1 && ((int)get_qcc_spawnflags(ent) & SPAWNFLAG_NOT_MEDIUM))
				|| (current_skill >= 2 && ((int)get_qcc_spawnflags(ent) & SPAWNFLAG_NOT_HARD)) )
		{
			ED_Free (ent);
			inhibit++;
			continue;
		}

//
// immediately call spawn function
//
       printf("Trying to spawn %s\r\n", pr_strings + get_qcc_classname(ent));

		if (!get_qcc_classname(ent))
		{
			Con_Printf ("No classname for:\n");
			ED_Print (ent);
			ED_Free (ent);
			FIXME("NO CLASS NAME");
			continue;
		}

	// look for the spawn function
		func = ED_FindFunction ( pr_strings + get_qcc_classname(ent) );

		if (!func)
		{
			Con_Printf ("No spawn function for:\n");
			ED_Print (ent);
			ED_Free (ent);
			FIXME("NO CLASS FUNC");

			continue;
		}

		pr_global_struct->self = EDICT_TO_PROG(ent);
		PR_ExecuteProgram (func - pr_functions);
	}

	Con_DPrintf ("%i entities inhibited\n", inhibit);
	#else

    edict_t *ent;
    int inhibit;

    ent = NULL;
    inhibit = 0;
    progs.qcc_time = sv.time;
    sv.edicts->qcc_classname = findStringIndex("worldspawn");
#if DEBUG_EDICTS
    printf("sv.edicts->qcc_classname %d\r\n", sv.edicts->qcc_classname);
    FIXME("");
#endif
// parse ents
    while (1)
    {
// parse the opening brace
        data = COM_Parse(data, com_token);
        if (!data)
            break;
        if (com_token[0] != '{')
            Sys_Error("ED_LoadFromFile: found %s when expecting {", com_token);

        edict_t tmpent =
        { 0
        };
        edict_t *stemp;
        if (!ent)
        {
            stemp = sv.edicts;
        }
        else
            stemp = &tmpent;
        tmpent.qcc_classname = 0;
        data = ED_ParseEdict(data, stemp);
        if (!ent)
        {
            ent = sv.edicts;
        }
        else
        {
#if DEBUG_EDICTS
            printf("Current class name to parse: %d %s\r\n", currentParseClassName, getStringFromIndex(currentParseClassName));
#endif
            /*    if (currentParseClassName == info_null_string_index)
             {
             FIXME("not allocating info null");
             continue;
             }*/
            ent = ED_Alloc(currentParseClassName);
//            printf("Ent Ptr: %p static zone: %p distance %d sv.edicts distance %d\r\n", ent, staticZone, (byte*) ent - (byte*)staticZone,  (byte*) ent - (byte*)sv.edicts);
            ent->qcc_classname = currentParseClassName;
            if (currentParseClassName == player_string_index)
            {
                FIXME("SPAWNING PLAYER?!?");
            }
            tmpent.qcc_classname = 0;   //must be 0 (full class by default) because otherwise wrong data will be copied.
            ED_CopyNonZeroFields(ent, &tmpent);
            ent->qcc_classname = currentParseClassName;
            ent->free = tmpent.free;

        }
// remove things from different skill levels or deathmatch
        int spawnflags = get_qcc_spawnflags(stemp); // next-hack we need this one, because some entities will have reduced spawnflags
        if (deathmatch)
        {
            if ((spawnflags & SPAWNFLAG_NOT_DEATHMATCH))
            {
                //ED_Free (ent);
                ED_ForceRemove(ent);
                inhibit++;
                continue;
            }
        }
        else if ((current_skill == 0 && (spawnflags & SPAWNFLAG_NOT_EASY)) || (current_skill == 1 && (spawnflags & SPAWNFLAG_NOT_MEDIUM))
            || (current_skill >= 2 && (spawnflags & SPAWNFLAG_NOT_HARD)))
        {
            //ED_Free (ent);
            ED_ForceRemove(ent);
            inhibit++;
            continue;
        }

        //
        // immediately call spawn function
        //
#if DEBUG_EDICTS
    static int item = 0;
		printf("Item %d\r\n", item++);
#endif
        if (!get_qcc_classname(ent))
        {
            Con_Printf("No classname for:\n");
            ED_Print(ent);
//			ED_Free (ent);
            ED_ForceRemove(ent);
            continue;
        }

        // look for the spawn function
#if DEBUG_EDICTS
		printf(getStringFromIndex(get_qcc_classname(ent)));
	printf("\r\ntrying to spawn %s\r\n", getStringFromIndex(get_qcc_classname(ent)));
	//FIXME("");
#endif
        void (*spawnFunc)(void) = ED_FindSpawnFunction(getStringFromIndex(get_qcc_classname(ent)));
        if (!spawnFunc)
        {
            Con_Printf("No spawn function for: %s\n", getStringFromIndex(get_qcc_classname(ent)));
            ED_Print(ent);
            ED_ForceRemove(ent);
            FIXME("");
            continue;
        }

        //	pr_global_struct->self = EDICT_TO_PROG(ent);
        progs.qcc_self = EDICT_TO_PROG(ent);

        canForceEdictFree = true;
#if DEBUG_EDICTS
		printf("SPAWNING\r\n");
#endif // DEBUG_EDICTS

        spawnFunc();
        // sounds do not really have to remain there. We can freeze them!
        if (qcc_classname2type[ent->qcc_classname] == sound_edict_idx)
        {
            ED_ForceRemove(ent);
        }
        canForceEdictFree = false;
    }

    Con_DPrintf("%i entities inhibited\n", inhibit);

#endif
}

/*
 ===============
 PR_Init
 ===============
 */
void PR_Init(void)
{
//	Cmd_AddCommand ("profile", PR_Profile_f);
#if USE_ORIGINAL_CVAR
	Cvar_RegisterVariable (&nomonsters);
	Cvar_RegisterVariable (&gamecfg);
	Cvar_RegisterVariable (&scratch1);
	Cvar_RegisterVariable (&scratch2);
	Cvar_RegisterVariable (&scratch3);
	Cvar_RegisterVariable (&scratch4);
	Cvar_RegisterVariable (&savedgamecfg);
	Cvar_RegisterVariable (&saved1);
	Cvar_RegisterVariable (&saved2);
	Cvar_RegisterVariable (&saved3);
	Cvar_RegisterVariable (&saved4);
#endif
}

edict_t* EDICT_NUM(int n)
{
#if !EDICT_LINKED_LIST
	if (n < 0 || n >= sv.max_edicts)
		Sys_Error ("EDICT_NUM: bad number %i", n);
	return (edict_t *)((byte *)sv.edicts+ (n)*pr_edict_size);
#else
    if (n <= 0 || n >= svs.maxclients + 1)
        Sys_Error("EDICT_NUM: bad number %i. Max Value: %d", n, svs.maxclients);
    edict_t *ent = sv.edicts;
    for (int i = 0; i < n; i++)
    {
        ent = getNextEdict(ent);
    }
    return ent;

#endif

}
int NUM_FOR_EDICT(edict_t *e)
{
    //
#if EDICT_LINKED_LIST
    edict_t *te = sv.edicts;
    for (int i = 0; i < sv.num_edicts; i++)
    {
        if (te == e)
            return i;
        te = getNextEdict(te);
    }
    Sys_Error("NUM_FOR_EDICT: bad pointer");
    return -1;
#else
#error
	int		b;

	b = (byte *)e - (byte *)sv.edicts;
	b = b / pr_edict_size;

	if (b < 0 || b >= sv.num_edicts)
		Sys_Error ("NUM_FOR_EDICT: bad pointer");
	return b;
#endif
}
