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
// cmd.c -- Quake script command processing module
#include "quakedef.h"
#if RETAIL_QUAKE_PAK_SUPPORT
#pragma GCC optimize("Os") //
#endif
// EXTERN FUNCTIONS REQUIRED FOR STATIC COMMANDS DECLARATION
extern void IN_UpDown(void);
extern void IN_UpUp(void);
extern void IN_DownDown(void);
extern void IN_DownUp(void);
extern void IN_LeftDown(void);
extern void IN_LeftUp(void);
extern void IN_RightDown(void);
extern void IN_RightUp(void);
extern void IN_ForwardDown(void);
extern void IN_ForwardUp(void);
extern void IN_BackDown(void);
extern void IN_BackUp(void);
extern void IN_LookupDown(void);
extern void IN_LookupUp(void);
extern void IN_LookdownDown(void);
extern void IN_LookdownUp(void);
extern void IN_MoveleftDown(void);
extern void IN_MoveleftUp(void);
extern void IN_MoverightDown(void);
extern void IN_MoverightUp(void);

extern void IN_SpeedDown(void);
extern void IN_SpeedUp(void);
extern void IN_StrafeDown(void);
extern void IN_StrafeUp(void);

extern void IN_AttackDown(void);
extern void IN_AttackUp(void);

extern void IN_UseDown(void);
extern void IN_UseUp(void);
extern void IN_JumpDown(void);
extern void IN_JumpUp(void);

extern void IN_Impulse(void);
extern void IN_KLookDown(void);
extern void IN_KLookUp(void);
extern void IN_MLookDown(void);
extern void IN_MLookUp(void);
//
extern void V_cshift_f(void);
extern void V_BonusFlash_f(void);
extern void V_StartPitchDrift(void);
// snd
extern void S_Play(void);
extern void S_PlayVol(void);
extern void S_StopAllSoundsC(void);
extern void S_SoundList(void);
extern void S_SoundInfo_f(void);
// screen
extern void SCR_ScreenShot_f(void);
extern void SCR_SizeUp_f(void);
extern void SCR_SizeDown_f(void);
// sbar
extern void Sbar_ShowScores(void);
extern void Sbar_DontShowScores(void);
// edict
extern void ED_PrintEdict_f(void);
extern void ED_PrintEdicts(void);
extern void ED_Count(void);
// net-main
#if HAS_MULTIPLAYER
extern void NET_Slist_f (void);
extern void NET_Listen_f (void);
extern void MaxPlayers_f (void);
extern void NET_Port_f (void);
#endif
// menu
extern void M_ToggleMenu_f(void);
extern void M_Menu_Main_f(void);
extern void M_Menu_SinglePlayer_f(void);
extern void M_Menu_Load_f(void);
extern void M_Menu_Save_f(void);
#if HAS_MULTIPLAYER
extern void M_Menu_MultiPlayer_f (void);
extern void M_Menu_Setup_f (void);
#endif
extern void M_Menu_Options_f(void);
extern void M_Menu_Keys_f(void);
extern void M_Menu_Video_f(void);
extern void M_Menu_Help_f(void);
extern void M_Menu_Quit_f(void);
// keys
extern void Key_Bind_f(void);
extern void Key_Unbind_f(void);
extern void Key_Unbindall_f(void);
// host_cmd
extern void Host_Status_f(void);
extern void Host_Quit_f(void);
extern void Host_God_f(void);
extern void Host_Notarget_f(void);
extern void Host_Fly_f(void);
extern void Host_Map_f(void);
extern void Host_Restart_f(void);
extern void Host_Changelevel_f(void);

extern void Host_Connect_f(void);
extern void Host_Reconnect_f(void);
extern void Host_Name_f(void);
extern void Host_Noclip_f(void);
extern void Host_Version_f(void);
#ifdef IDGODS
	Cmd_AddCommand ("please", Host_Please_f);
#endif
extern void Host_Say_f(void);
extern void Host_Say_Team_f(void);
extern void Host_Tell_f(void);
extern void Host_Color_f(void);
extern void Host_Kill_f(void);
extern void Host_Pause_f(void);
extern void Host_Spawn_f(void);
extern void Host_Begin_f(void);
extern void Host_PreSpawn_f(void);
extern void Host_Kick_f(void);
extern void Host_Ping_f(void);
extern void Host_Loadgame_f(void);
extern void Host_Savegame_f(void);
extern void Host_Give_f(void);

extern void Host_Startdemos_f(void);
extern void Host_Demos_f(void);
extern void Host_Stopdemo_f(void);

extern void Host_Viewmodel_f(void);
extern void Host_Viewframe_f(void);
extern void Host_Viewnext_f(void);
extern void Host_Viewprev_f(void);

extern void Mod_Print(void);
// console
extern void Con_ToggleConsole_f(void);
extern void Con_MessageMode_f(void);
extern void Con_MessageMode2_f(void);
extern void Con_Clear_f(void);
// common
#if 0
extern void COM_Path_f(void);
#endif
//
extern void CL_PrintEntities_f(void);
extern void CL_Disconnect_f(void);
extern void CL_Record_f(void);
extern void CL_Stop_f(void);
extern void CL_PlayDemo_f(void);
extern void CL_TimeDemo_f(void);
extern void Cmd_Complete_f(void);
//-------
void Cmd_ForwardToServer(void);

#define	MAX_ALIAS_NAME	32

typedef struct cmdalias_s
{
    struct cmdalias_s *next;
    char name[MAX_ALIAS_NAME];
    char *value;
} cmdalias_t;

cmdalias_t *cmd_alias;

int trashtest;
int *trashspot;

qboolean cmd_wait;

//=============================================================================

/*
 ============
 Cmd_Wait_f

 Causes execution of the remainder of the command buffer to be delayed until
 next frame.  This allows commands like:
 bind g "impulse 5 ; +attack ; wait ; -attack ; impulse 2"
 ============
 */
void Cmd_Wait_f(void)
{
//	cmd_wait = true;
    printf("WAIT CMD DISABLED\r\n");
}

/*
 =============================================================================

 COMMAND BUFFER

 =============================================================================
 */

sizebuf_t cmd_text;

/*
 ============
 Cbuf_Init
 ============
 */
static AUX_SECTION char cbuf_buffer[64];    // next-hack: should be enough, right? (note! it MUST be not in stack!)

void Cbuf_Init(void)
{
    cmd_text.data = (byte*) cbuf_buffer;
    cmd_text.maxsize = sizeof(cbuf_buffer);
}

/*
 ============
 Cbuf_AddText

 Adds command text at the end of the buffer
 ============
 */
void Cbuf_AddText(const char *text)
{
    int l;

    l = Q_strlen(text);

    if (cmd_text.cursize + l >= cmd_text.maxsize)
    {
        Con_Printf("Cbuf_AddText: overflow\n");
        return;
    }

    SZ_Write(&cmd_text, text, Q_strlen(text));
}

/*
 ============
 Cbuf_InsertText

 Adds command text immediately after the current command
 Adds a \n to the text
 FIXME: actually change the command buffer to do less copying
 ============
 */
void Cbuf_InsertText(char *text)
{
    char *temp;
    int templen;

// copy off any commands still remaining in the exec buffer
    templen = cmd_text.cursize;
    if (templen)
    {
#if WIN32
	    printf("About to adding: %s\r\n", text);
#endif
        temp = Z_Malloc(templen);
        Q_memcpy(temp, cmd_text.data, templen);
        SZ_Clear(&cmd_text);
    }
    else
        temp = NULL;	// shut up compiler

// add the entire text of the file
    Cbuf_AddText(text);

// add the copied off data
    if (templen)
    {
        SZ_Write(&cmd_text, temp, templen);
        Z_Free(temp);
    }
}

/*
 ============
 Cbuf_Execute
 ============
 */
void Cbuf_Execute(void)
{
    int i;
    char *text;
    char line[1024];
    int quotes;

    while (cmd_text.cursize)
    {
// find a \n or ; line break
        text = (char*) cmd_text.data;

        quotes = 0;
        for (i = 0; i < cmd_text.cursize; i++)
        {
            if (text[i] == '"')
                quotes++;
            if (!(quotes & 1) && text[i] == ';')
                break;	// don't break if inside a quoted string
            if (text[i] == '\n')
                break;
        }

        memcpy(line, text, i);
        line[i] = 0;

// delete the text from the command buffer and move remaining commands down
// this is necessary because commands (exec, alias) can insert data at the
// beginning of the text buffer

        if (i == cmd_text.cursize)
            cmd_text.cursize = 0;
        else
        {
            i++;
            cmd_text.cursize -= i;
            Q_memcpy(text, text + i, cmd_text.cursize);
        }

// execute the command line
#if WIN32
		printf("Executing command <%s>\r\n", line);
#endif
        Cmd_ExecuteString(line, src_command);

        if (cmd_wait)
        {
            FIXME("WAIT FUNCTION REQUESTED");
            // skip out while text still remains in buffer, leaving it
            // for next frame
            cmd_wait = false;
            break;
        }
    }
}

/*
 ==============================================================================

 SCRIPT COMMANDS

 ==============================================================================
 */

/*
 ===============
 Cmd_StuffCmds_f

 Adds command line parameters as script statements
 Commands lead with a +, and continue until a - or another +
 quake +prog jctest.qp +cmd amlev1
 quake -nosound +cmd amlev1
 ===============
 */
void Cmd_StuffCmds_f(void)
{
#if 0
	int		i, j;
	int		s;
	char	*text, *build, c;

	if (Cmd_Argc () != 1)
	{
		Con_Printf ("stuffcmds : execute command line parameters\n");
		return;
	}

// build the combined string to parse from
	s = 0;
	for (i=1 ; i<com_argc ; i++)
	{
		if (!com_argv[i])
			continue;		// NEXTSTEP nulls out -NXHost
		s += Q_strlen (com_argv[i]) + 1;
	}
	if (!s)
		return;

	text = Z_Malloc (s+1);
	text[0] = 0;
	for (i=1 ; i<com_argc ; i++)
	{
		if (!com_argv[i])
			continue;		// NEXTSTEP nulls out -NXHost
		Q_strcat (text,com_argv[i]);
		if (i != com_argc-1)
			Q_strcat (text, " ");
	}

// pull out the commands
	build = Z_Malloc (s+1);
	build[0] = 0;

	for (i=0 ; i<s-1 ; i++)
	{
		if (text[i] == '+')
		{
			i++;

			for (j=i ; (text[j] != '+') && (text[j] != '-') && (text[j] != 0) ; j++)
				;

			c = text[j];
			text[j] = 0;

			Q_strcat (build, text+i);
			Q_strcat (build, "\n");
			text[j] = c;
			i = j-1;
		}
	}

	if (build[0])
		Cbuf_InsertText (build);

	Z_Free (text);
	Z_Free (build);
	#else
    printf("StuffCMD is disabled\r\n");
#endif // 0
}

/*
 ===============
 Cmd_Exec_f
 ===============
 */
void Cmd_Exec_f(void)
{
    char *f;
    if (Cmd_Argc() != 2)
    {
        Con_Printf("exec <filename> : execute a script file\n");
        return;
    }

    printf("------Load from Cmd Exec: %s\r\n", Cmd_Argv(1));
    f = (char*) getExtMemPointerToFileInPak(Cmd_Argv(1), NULL);
//	printf("<BEGIN FILE CONTENT>\r\n%s\r\n<END FILE CONTENT>\r\n", f);
    if (!f)
    {
        Con_Printf("couldn't exec %s\n", Cmd_Argv(1));
        return;
    }
    Con_Printf("executing %s\n", Cmd_Argv(1));

    char line[1024 + 1] =
    { 0
    };
    unsigned int chPos = 0;
    int quotes = 0;
    char c;
    // slow as hell. but executed few times.
    while ((c = extMemGetByteFromAddress(f)) != 0)
    {
        f++;
        line[chPos] = c;
        chPos++;
        if (chPos >= sizeof(line) - 1)
        {
            FIXME("ERROR, LINE TOO LONG");
            break;
        }
        if (c == '"')
            quotes++;
        if ((!(quotes & 1) && (c == ';')) || c == '\n' || c == 0)
        {
            if (chPos > 1)
            {
                line[chPos] = 0;
                chPos = 0;
                Cmd_ExecuteString(line, src_command);
            }
        }
    }
}
// next-hack: some debug cmds...
void Cmd_StepX_f(void)
{
    edict_t *ent = getNextEdict(sv.edicts);
    float x = VEC(get_qcc_origin(ent))[0];
    x += 1;
    set_qcc_origin_x(ent, x);
}
void Cmd_ParticleRect_f(void)
{
    edict_t *ent = getNextEdict(sv.edicts);
    vec3_t dir =
    { 0
    };
    vec3_t org;
    VectorCopy(VEC(get_qcc_origin(ent)), org);
    org[2] += 5;

    for (int y = -10; y < 10; y++)
    {
        for (int x = -10; x < 10; x++)
        {
            vec3_t porg;
            porg[0] = org[0] + x;
            porg[1] = org[1] + y;
            R_RunParticleEffect(porg, dir, 1, 1);
        }
    }

    Con_Printf("\n");
}

/*
 ===============
 Cmd_Echo_f

 Just prints the rest of the line to the console
 ===============
 */
void Cmd_Echo_f(void)
{
    int i;

    for (i = 1; i < Cmd_Argc(); i++)
        Con_Printf("%s ", Cmd_Argv(i));
    Con_Printf("\n");
}
void Cmd_Complete_f(void)
{
#if WIN32
    // this to be fixed
    printf("forcing level complete\r\n");
    qcc_execute_changelevel();
#endif
}
// next-hack added to test mipmap effet
void Cmd_MipMap_f(void)
{
#if WIN32
    allowMipMapReduction = 1 - allowMipMapReduction;
    Con_Printf ("Mimmap Reduction: %d\r\n", allowMipMapReduction);
#endif
}

// next-hack added cmds
void Cmd_CheckEdict_f(void)
{
    edict_t *ent = sv.edicts;
#if !USE_PROGSDAT
    for (int i = 0; i < sv.num_edicts; i++)
    {
        int clidx = get_qcc_classname(ent);
        const char *s = getStringFromIndex(clidx);
        printf("Editct %d, class index %d, name %s, is within boundary %s\r\n", i, clidx, s, clidx < max_classname_string_index ? "YES" : "NOOOOOOOOOOOOOOOO");
        ent = getNextEdict(ent);
    }
    printf(">>> AND NOW THE LIST TO BE ADDED <<<\r\n");
    uint8_t printed[65536 / 8];
    ent = sv.edicts;
    for (int i = 0; i < sv.num_edicts; i++)
    {
        int clidx = get_qcc_classname(ent);
        const char *s = getStringFromIndex(clidx);
        if (clidx >= max_classname_string_index && !(printed[clidx / 8] & (1 << (clidx & 7))))
        {
            printf("string classname_%s = \"%s\";\r\n", s, s);
            printed[clidx / 8] |= 1 << (clidx & 7);
        }
        ent = getNextEdict(ent);
    }
#endif

}
/*
 ===============
 Cmd_Alias_f

 Creates a new command that executes a command string (possibly ; seperated)
 ===============
 */

char* CopyString(char *in)
{
    char *out;

    out = Z_Malloc(strlen(in) + 1);
    strcpy(out, in);
    return out;
}

void Cmd_Alias_f(void)
{
#if !ENABLE_ALIAS_COMMAND
    printf("(ALIAS DISABLED) <%s>\r\n", Cmd_Argv(1));
    return;
#else
	cmdalias_t	*a;
	char		cmd[1024];
	int			i, c;
	char		*s;

	if (Cmd_Argc() == 1)
	{
		Con_Printf ("Current alias commands:\n");
		for (a = cmd_alias ; a ; a=a->next)
			Con_Printf ("%s : %s\n", a->name, a->value);
		return;
	}

	s = Cmd_Argv(1);
	if (strlen(s) >= MAX_ALIAS_NAME)
	{
		Con_Printf ("Alias name is too long\n");
		return;
	}

	// if the alias already exists, reuse it
	for (a = cmd_alias ; a ; a=a->next)
	{
		if (!strcmp(s, a->name))
		{
			Z_Free (a->value);
			break;
		}
	}

	if (!a)
	{
		a = Z_Malloc (sizeof(cmdalias_t));
		a->next = cmd_alias;
		cmd_alias = a;
	}
	strcpy (a->name, s);

// copy the rest of the command line
	cmd[0] = 0;		// start out with a null string
	c = Cmd_Argc();
	for (i=2 ; i< c ; i++)
	{
		strcat (cmd, Cmd_Argv(i));
		if (i != c)
			strcat (cmd, " ");
	}
	strcat (cmd, "\n");
    printf("ALIAS <%s>=<%s>\r\n", a->name, cmd);
	a->value = CopyString (cmd);
#endif
}

/*
 =============================================================================

 COMMAND EXECUTION

 =============================================================================
 */

typedef struct cmd_function_s
{
//	struct cmd_function_s	*next;
    const char *const name;
    xcommand_t function;
} cmd_function_t;

#define	MAX_ARGS		8  // was 80

static int cmd_argc;
AUX_SECTION static char *cmd_argv[MAX_ARGS];
static char *cmd_null_string = "";
static char *cmd_args = NULL;

cmd_source_t cmd_source;

#define Cmd_AddCommand(string, f) {.name = string, .function = f}
static const cmd_function_t cmd_functions[] =
{
//
// register our commands
//
    Cmd_AddCommand ("stuffcmds",Cmd_StuffCmds_f),
    Cmd_AddCommand ("exec",Cmd_Exec_f),
    Cmd_AddCommand ("echo",Cmd_Echo_f),
    Cmd_AddCommand ("alias",Cmd_Alias_f),
    Cmd_AddCommand ("cmd", Cmd_ForwardToServer),
    Cmd_AddCommand ("wait", Cmd_Wait_f),
    Cmd_AddCommand ("mipmap", Cmd_MipMap_f),
    Cmd_AddCommand ("chked", Cmd_CheckEdict_f),
    Cmd_AddCommand ("part", Cmd_ParticleRect_f),
    //
    Cmd_AddCommand ("step", Cmd_StepX_f),
    Cmd_AddCommand ("+moveup",IN_UpDown),
    Cmd_AddCommand ("-moveup",IN_UpUp),
    Cmd_AddCommand ("+movedown",IN_DownDown),
    Cmd_AddCommand ("-movedown",IN_DownUp),
    Cmd_AddCommand ("+left",IN_LeftDown),
    Cmd_AddCommand ("-left",IN_LeftUp),
    Cmd_AddCommand ("+right",IN_RightDown),
    Cmd_AddCommand ("-right",IN_RightUp),
    Cmd_AddCommand ("+forward",IN_ForwardDown),
    Cmd_AddCommand ("-forward",IN_ForwardUp),
    Cmd_AddCommand ("+back",IN_BackDown),
    Cmd_AddCommand ("-back",IN_BackUp),
    Cmd_AddCommand ("+lookup", IN_LookupDown),
    Cmd_AddCommand ("-lookup", IN_LookupUp),
    Cmd_AddCommand ("+lookdown", IN_LookdownDown),
    Cmd_AddCommand ("-lookdown", IN_LookdownUp),
    Cmd_AddCommand ("+strafe", IN_StrafeDown),
    Cmd_AddCommand ("-strafe", IN_StrafeUp),
    Cmd_AddCommand ("+moveleft", IN_MoveleftDown),
    Cmd_AddCommand ("-moveleft", IN_MoveleftUp),
    Cmd_AddCommand ("+moveright", IN_MoverightDown),
    Cmd_AddCommand ("-moveright", IN_MoverightUp),
    Cmd_AddCommand ("+speed", IN_SpeedDown),
    Cmd_AddCommand ("-speed", IN_SpeedUp),
    Cmd_AddCommand ("+attack", IN_AttackDown),
    Cmd_AddCommand ("-attack", IN_AttackUp),
    Cmd_AddCommand ("+use", IN_UseDown),
    Cmd_AddCommand ("-use", IN_UseUp),
    Cmd_AddCommand ("+jump", IN_JumpDown),
    Cmd_AddCommand ("-jump", IN_JumpUp),
    Cmd_AddCommand ("impulse", IN_Impulse),
    Cmd_AddCommand ("+klook", IN_KLookDown),
    Cmd_AddCommand ("-klook", IN_KLookUp),
    Cmd_AddCommand ("+mlook", IN_MLookDown),
    Cmd_AddCommand ("-mlook", IN_MLookUp),
    //  view
    Cmd_AddCommand ("v_cshift", V_cshift_f),
    Cmd_AddCommand ("bf", V_BonusFlash_f),
    Cmd_AddCommand ("centerview", V_StartPitchDrift),
    // snd
    Cmd_AddCommand("play", S_Play),
    Cmd_AddCommand("playvol", S_PlayVol),
    Cmd_AddCommand("stopsound", S_StopAllSoundsC),
    Cmd_AddCommand("soundlist", S_SoundList),
    Cmd_AddCommand("soundinfo", S_SoundInfo_f),
    // screen
    Cmd_AddCommand ("screenshot",SCR_ScreenShot_f),
//    Cmd_AddCommand ("sizeup",SCR_SizeUp_f),
//    Cmd_AddCommand ("sizedown",SCR_SizeDown_f),
    // sbar
    Cmd_AddCommand ("+showscores", Sbar_ShowScores),
    Cmd_AddCommand ("-showscores", Sbar_DontShowScores),
    // edict
    Cmd_AddCommand ("edict", ED_PrintEdict_f),
    Cmd_AddCommand ("edicts", ED_PrintEdicts),
    Cmd_AddCommand ("edictcount", ED_Count),
    // net-main
#if HAS_MULTIPLAYER
    Cmd_AddCommand ("slist", NET_Slist_f),
    Cmd_AddCommand ("listen", NET_Listen_f),
    Cmd_AddCommand ("maxplayers", MaxPlayers_f),
    Cmd_AddCommand ("port", NET_Port_f),
#endif
    // menu
    Cmd_AddCommand ("togglemenu", M_ToggleMenu_f),
    Cmd_AddCommand ("menu_main", M_Menu_Main_f),
    Cmd_AddCommand ("menu_singleplayer", M_Menu_SinglePlayer_f),
    Cmd_AddCommand ("menu_load", M_Menu_Load_f),
    Cmd_AddCommand ("menu_save", M_Menu_Save_f),
#if HAS_MULTIPLAYER
    Cmd_AddCommand ("menu_multiplayer", M_Menu_MultiPlayer_f),
    Cmd_AddCommand ("menu_setup", M_Menu_Setup_f),
#endif
    Cmd_AddCommand ("menu_options", M_Menu_Options_f),
    Cmd_AddCommand ("menu_keys", M_Menu_Keys_f),
    Cmd_AddCommand ("menu_video", M_Menu_Video_f),
    Cmd_AddCommand ("help", M_Menu_Help_f),
    Cmd_AddCommand ("menu_quit", M_Menu_Quit_f),
    // keys
    Cmd_AddCommand ("bind",Key_Bind_f),
    Cmd_AddCommand ("unbind",Key_Unbind_f),
    Cmd_AddCommand ("unbindall",Key_Unbindall_f),
    // host_cmd
    Cmd_AddCommand ("status", Host_Status_f),
    Cmd_AddCommand ("quit", Host_Quit_f),
    Cmd_AddCommand ("god", Host_God_f),
    Cmd_AddCommand ("notarget", Host_Notarget_f),
    Cmd_AddCommand ("fly", Host_Fly_f),
    Cmd_AddCommand ("map", Host_Map_f),
    Cmd_AddCommand ("restart", Host_Restart_f),
    Cmd_AddCommand ("changelevel", Host_Changelevel_f),
#ifdef QUAKE2
    Cmd_AddCommand ("changelevel2", Host_Changelevel2_f);
#endif
    Cmd_AddCommand ("connect", Host_Connect_f),
    Cmd_AddCommand ("reconnect", Host_Reconnect_f),
    Cmd_AddCommand ("name", Host_Name_f),
    Cmd_AddCommand ("noclip", Host_Noclip_f),
    Cmd_AddCommand ("version", Host_Version_f),
#ifdef IDGODS
    Cmd_AddCommand ("please", Host_Please_f);
#endif
    Cmd_AddCommand ("say", Host_Say_f),
    Cmd_AddCommand ("say_team", Host_Say_Team_f),
    Cmd_AddCommand ("tell", Host_Tell_f),
    Cmd_AddCommand ("color", Host_Color_f),
    Cmd_AddCommand ("kill", Host_Kill_f),
    Cmd_AddCommand ("pause", Host_Pause_f),
    Cmd_AddCommand ("spawn", Host_Spawn_f),
    Cmd_AddCommand ("begin", Host_Begin_f),
    Cmd_AddCommand ("prespawn", Host_PreSpawn_f),
#if HAS_MULTIPLAYER
    Cmd_AddCommand ("kick", Host_Kick_f),
#endif
    Cmd_AddCommand ("ping", Host_Ping_f),
    Cmd_AddCommand ("load", Host_Loadgame_f),
    Cmd_AddCommand ("save", Host_Savegame_f),
    Cmd_AddCommand ("give", Host_Give_f),

    Cmd_AddCommand ("startdemos", Host_Startdemos_f),
    Cmd_AddCommand ("demos", Host_Demos_f),
    Cmd_AddCommand ("stopdemo", Host_Stopdemo_f),

    Cmd_AddCommand ("viewmodel", Host_Viewmodel_f),
    Cmd_AddCommand ("viewframe", Host_Viewframe_f),
    Cmd_AddCommand ("viewnext", Host_Viewnext_f),
    Cmd_AddCommand ("viewprev", Host_Viewprev_f),

    Cmd_AddCommand ("mcache", Mod_Print),
    // console
    Cmd_AddCommand ("toggleconsole", Con_ToggleConsole_f),
    Cmd_AddCommand ("messagemode", Con_MessageMode_f),
    Cmd_AddCommand ("messagemode2", Con_MessageMode2_f),
    Cmd_AddCommand ("clear", Con_Clear_f),
    // common
    //Cmd_AddCommand ("path", COM_Path_f),
    // cl_main
    Cmd_AddCommand ("entities", CL_PrintEntities_f),
    Cmd_AddCommand ("disconnect", CL_Disconnect_f),
    Cmd_AddCommand ("record", CL_Record_f),
    Cmd_AddCommand ("stop", CL_Stop_f),
    Cmd_AddCommand ("playdemo", CL_PlayDemo_f),
    Cmd_AddCommand ("timedemo", CL_TimeDemo_f),
    //
    Cmd_AddCommand("complete", Cmd_Complete_f),
    }
;		// possible commands to execute

/*
 ============
 Cmd_Init
 ============
 */
void Cmd_Init(void)
{
}

/*
 ============
 Cmd_Argc
 ============
 */
int Cmd_Argc(void)
{
    return cmd_argc;
}

/*
 ============
 Cmd_Argv
 ============
 */
char* Cmd_Argv(int arg)
{
#if 0
    static int testarg = 0;
    if (arg > testarg)
    {
        testarg = arg;
        printf("Max TestArg %d\r\n", testarg);
        FIXME("argc max increased");
    }
    #endif
    if (arg >= cmd_argc)
        return cmd_null_string;
    return cmd_argv[arg];
}

/*
 ============
 Cmd_Args
 ============
 */
char* Cmd_Args(void)
{
    return cmd_args;
}

/*
 ============
 Cmd_TokenizeString

 Parses the given string into command line tokens.
 ============
 */
#if TOKENIZE_MALLOC
void Cmd_TokenizeString (char *text)
#else
void Cmd_TokenizeString(char *text, char *buffer)
#endif
{
    char com_token[1024];

// clear the args from the last string
#if TOKENIZE_MALLOC
    int     i;
    for (i=0 ; i<cmd_argc ; i++)
		Z_Free (cmd_argv[i]);
#endif
    cmd_argc = 0;
    cmd_args = NULL;

    while (1)
    {
// skip whitespace up to a /n
        while (*text && *text <= ' ' && *text != '\n')
        {
            text++;
        }

        if (*text == '\n')
        {	// a newline seperates commands in the buffer
            text++;
            break;
        }

        if (!*text)
            return;

        if (cmd_argc == 1)
            cmd_args = text;

        text = COM_Parse(text, com_token);
        if (!text)
            return;

        if (cmd_argc < MAX_ARGS)
        {
#if TOKENIZE_MALLOC
			cmd_argv[cmd_argc] = Z_Malloc (Q_strlen(com_token)+1);
#else
            cmd_argv[cmd_argc] = buffer;
            buffer += Q_strlen(com_token) + 1;
#endif

            Q_strcpy(cmd_argv[cmd_argc], com_token);
            cmd_argc++;
        }
    }

}

#if DYNAMIC_COMMANDS
/*
============
Cmd_AddCommand
============
*/
void	Cmd_AddCommand (char *cmd_name, xcommand_t function)
{
	cmd_function_t	*cmd;

	if (host_initialized)	// because hunk allocation would get stomped
		Sys_Error ("Cmd_AddCommand after host_initialized");

// fail if the command is a variable name
	if (Cvar_VariableString(cmd_name)[0])
	{
		Con_Printf ("Cmd_AddCommand: %s already defined as a var\n", cmd_name);
		return;
	}

// fail if the command already exists
	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
	{
		if (!Q_strcmp (cmd_name, cmd->name))
		{
			Con_Printf ("Cmd_AddCommand: %s already defined\n", cmd_name);
			return;
		}
	}

	cmd = Hunk_Alloc (sizeof(cmd_function_t));
	cmd->name = cmd_name;
	cmd->function = function;
	cmd->next = cmd_functions;
	cmd_functions = cmd;
}
#endif
/*
 ============
 Cmd_Exists
 ============
 */
qboolean Cmd_Exists(char *cmd_name)
{
#if DYNAMIC_COMMANDS
    cmd_function_t  *cmd;
    for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
	{
		if (!Q_strcmp (cmd_name,cmd->name))
			return true;
	}
#else
    for (unsigned int i = 0; i < sizeof(cmd_functions) / sizeof(cmd_functions[0]); i++)
    {

        if (!Q_strcmp(cmd_name, cmd_functions[i].name))
            return true;
    }
#endif
    return false;
}

/*
 ============
 Cmd_CompleteCommand
 ============
 */
const char* Cmd_CompleteCommand(char *partial)
{
    int len;

    len = Q_strlen(partial);

    if (!len)
        return NULL;

// check functions
#if DYNAMIC_COMMANDS
    cmd_function_t  *cmd;
	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
		if (!Q_strncmp (partial,cmd->name, len))
			return cmd->name;
#else
    for (unsigned int i = 0; i < sizeof(cmd_functions) / sizeof(cmd_functions[0]); i++)
    {

        if (!Q_strncmp(partial, cmd_functions[i].name, len))
            return cmd_functions[i].name;
    }
#endif

    return NULL;
}

/*
 ============
 Cmd_ExecuteString

 A complete command line has been parsed, so try to execute it
 FIXME: lookupnoadd the token to speed search?
 ============
 */
void Cmd_ExecuteString(char *text, cmd_source_t src)
{
    cmdalias_t *a;

    cmd_source = src;
#if TOKENIZE_MALLOC
	Cmd_TokenizeString (text);
#else
    char tokenBuffer[1024];
    Cmd_TokenizeString(text, tokenBuffer);
#endif

// execute the command line
    if (!Cmd_Argc())
        return;		// no tokens

// check functions
#if DYNAMIC_COMMANDS
    cmd_function_t  *cmd;
	for (cmd=cmd_functions ; cmd ; cmd=cmd->next)
	{
		if (!Q_strcasecmp (cmd_argv[0],cmd->name))
		{
			cmd->function ();
			return;
		}
	}
#else
    for (unsigned int i = 0; i < sizeof(cmd_functions) / sizeof(cmd_functions[0]); i++)
    {
        if (!Q_strcasecmp(cmd_argv[0], cmd_functions[i].name))
        {
            cmd_functions[i].function();
            return;
        }
    }
#endif
// check alias
    for (a = cmd_alias; a; a = a->next)
    {
        if (!Q_strcasecmp(cmd_argv[0], a->name))
        {
            Cbuf_InsertText(a->value);
            return;
        }
    }

// check cvars
    if (!Cvar_Command())
        Con_Printf("Unknown command \"%s\"\n", Cmd_Argv(0));

}
//

/*
 ===================
 Cmd_ForwardToServer

 Sends the entire command line over to the server
 ===================
 */
void Cmd_ForwardToServer(void)
{
    if (_g->cls.state != ca_connected)
    {
        Con_Printf("Can't \"%s\", not connected\n", Cmd_Argv(0));
        return;
    }

    if (_g->cls.demoplayback)
        return;		// not really connected

    MSG_WriteByte(&_g->cls.message, clc_stringcmd);
    if (Q_strcasecmp(Cmd_Argv(0), "cmd") != 0)
    {
        SZ_Print(&_g->cls.message, Cmd_Argv(0));
        SZ_Print(&_g->cls.message, " ");
    }
    if (Cmd_Argc() > 1)
        SZ_Print(&_g->cls.message, Cmd_Args());
    else
        SZ_Print(&_g->cls.message, "\n");
}

/*
 ================
 Cmd_CheckParm

 Returns the position (1 to argc-1) in the command's argument list
 where the given parameter apears, or 0 if not present
 ================
 */

int Cmd_CheckParm(char *parm)
{
    int i;

    if (!parm)
        Sys_Error("Cmd_CheckParm: NULL");

    for (i = 1; i < Cmd_Argc(); i++)
        if (!Q_strcasecmp(parm, Cmd_Argv(i)))
            return i;

    return 0;
}
