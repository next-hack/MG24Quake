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

/*

 key up events are sent even if in console mode

 */

AUX_SECTION char key_lines[MAX_HISTORY_LINES][MAXCMDLINE];
int8_t key_linepos;
int8_t shift_down = false;
uint8_t key_lastpress;

int edit_line = 0;
#if HISTORY
int		history_line=0;
#else
short cheat_line = 0;
const char *const cheats[] =
{
    "impulse 255",  // quad damage
    "impulse 9",    // all weapons/ammo
    "give h 100",   // gain 100 health
    "god",   // guess...
    "impulse 13",     // silver key
    "impulse 14",     // gold key
    "impulse 11",     // rune
    "impulse 256",      // super shield
    "map e1m1",
    "map e1m2",
    "map e1m3",
    "map e1m4",
    "map e1m5",
    "map e1m6",
    "map e1m7",
    "map e1m8",
    "showfps 0",
    "showfps 1",
    "",
// blank line.
    };
#endif
keydest_t key_dest;

int key_count;			// incremented every key event

#if FULL_KEYBINDING
char *keybindings[256];
#else
AUX_SECTION byte keybindings[256]; // returns the index of the command. 0 is not bound
#endif
#if USE_KEY_QBOOLEANS
qboolean consolekeys[256];	// if true, can't be rebound while in console
qboolean menubound[256];// if true, can't be rebound while in menu
qboolean keydown[256];

#else
AUX_SECTION byte ba_keydown[256 / 8];
#define define_setterGetterBitArray(name) static inline void set_##name(int n, int value) { if (value)  ba_##name[n >> 3] |= (1 << (n & 7)); else ba_##name[n >> 3] &= ~(1 << (n & 7));  }
#define define_getterGetterBitArray(name) static inline int get_##name(int n) { return 0 != (ba_##name[n >> 3] & (1 << (n & 7))); }
define_setterGetterBitArray(keydown);
#endif // USE_KEY_BITFIELD
#if !USE_BOUND_KEYS_ARRAY
int get_menubound(int key)
{
    if (key == K_ESCAPE)
        return 1;
    else
        return 0;
}
int get_consolekeys(int key)
{
    if (key >= 32 || key <= 128)
        return 1;
    else
        switch (key)
        {
            case K_ENTER:
            case K_CTRL:
            case K_UPARROW:
            case K_DOWNARROW:
#if WIN32
            case K_TAB:
            case K_LEFTARROW:
            case K_RIGHTARROW:
            case K_BACKSPACE:
            case K_PGUP:
            case K_PGDN:
            case K_SHIFT:
            case K_MWHEELUP:
            case K_MWHEELDOWN:
#endif
                return 1;
            default:
                return 0;
        }
}
#endif
const char keyshift[256] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x22, 0x28, 0x29, 0x2a, 0x2b, 0x3c, 0x5f, 0x3e, 0x3f, 0x29, 0x21, 0x40, 0x23, 0x24, 0x25, 0x5e, 0x26, 0x2a, 0x28, 0x3a, 0x3a, 0x3c, 0x2b, 0x3e, 0x3f,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x5e, 0x5f,
    0x7e, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7, 0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef, 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff,
};		// key to map to if shift held down in console
#if WIN32
byte	key_repeats[256];	// if > 1, it is autorepeating. Not used on MCU projects.
#endif
typedef struct
{
    char *name;
    byte keynum;
} keyname_t;

const keyname_t keynames[] =
{
    {"TAB", K_TAB},
    {"ENTER", K_ENTER},
    {"ESCAPE", K_ESCAPE},
    {"SPACE", K_SPACE},
    {"BACKSPACE", K_BACKSPACE},
    {"UPARROW", K_UPARROW},
    {"DOWNARROW", K_DOWNARROW},
    {"LEFTARROW", K_LEFTARROW},
    {"RIGHTARROW", K_RIGHTARROW},

    {"ALT", K_ALT},
    {"CTRL", K_CTRL},
    {"SHIFT", K_SHIFT},

    {"F1", K_F1},
    {"F2", K_F2},
    {"F3", K_F3},
    {"F4", K_F4},
    {"F5", K_F5},
    {"F6", K_F6},
    {"F7", K_F7},
    {"F8", K_F8},
    {"F9", K_F9},
    {"F10", K_F10},
    {"F11", K_F11},
    {"F12", K_F12},

    {"INS", K_INS},
    {"DEL", K_DEL},
    {"PGDN", K_PGDN},
    {"PGUP", K_PGUP},
    {"HOME", K_HOME},
    {"END", K_END},

    {"MOUSE1", K_MOUSE1},
    {"MOUSE2", K_MOUSE2},
    {"MOUSE3", K_MOUSE3},

    {"JOY1", K_JOY1},
    {"JOY2", K_JOY2},
    {"JOY3", K_JOY3},
    {"JOY4", K_JOY4},

    {"AUX1", K_AUX1},
    {"AUX2", K_AUX2},
    {"AUX3", K_AUX3},
    {"AUX4", K_AUX4},
    {"AUX5", K_AUX5},
    {"AUX6", K_AUX6},
    {"AUX7", K_AUX7},
    {"AUX8", K_AUX8},
    {"AUX9", K_AUX9},
    {"AUX10", K_AUX10},
    {"AUX11", K_AUX11},
    {"AUX12", K_AUX12},
    {"AUX13", K_AUX13},
    {"AUX14", K_AUX14},
    {"AUX15", K_AUX15},
    {"AUX16", K_AUX16},
    {"AUX17", K_AUX17},
    {"AUX18", K_AUX18},
    {"AUX19", K_AUX19},
    {"AUX20", K_AUX20},
    {"AUX21", K_AUX21},
    {"AUX22", K_AUX22},
    {"AUX23", K_AUX23},
    {"AUX24", K_AUX24},
    {"AUX25", K_AUX25},
    {"AUX26", K_AUX26},
    {"AUX27", K_AUX27},
    {"AUX28", K_AUX28},
    {"AUX29", K_AUX29},
    {"AUX30", K_AUX30},
    {"AUX31", K_AUX31},
    {"AUX32", K_AUX32},

    {"PAUSE", K_PAUSE},

    {"MWHEELUP", K_MWHEELUP},
    {"MWHEELDOWN", K_MWHEELDOWN},

    {"SEMICOLON", ';'},	// because a raw semicolon separates commands

    {NULL,0}
};

/*
 ==============================================================================

 LINE TYPING INTO THE CONSOLE

 ==============================================================================
 */

/*
 ====================
 Key_Console

 Interactive line editing and console scrollback
 ====================
 */
void Key_Console(int key)
{
    const char *cmd;

    if (key == K_ENTER || key == K_CTRL)
    {
        Cbuf_AddText(key_lines[edit_line] + 1);	// skip the >
        Cbuf_AddText("\n");
        Con_Printf("%s\n", key_lines[edit_line]);
        edit_line = (edit_line + 1) % MAX_HISTORY_LINES;
#if HISTORY
		history_line = edit_line;
#endif
        key_lines[edit_line][0] = ']';
        key_linepos = 1;
        if (_g->cls.state == ca_disconnected)
            SCR_UpdateScreen();	// force an update, because the command
                                // may take some time
        return;
    }

    if (key == K_TAB)
    {	// command completion
        cmd = Cmd_CompleteCommand(key_lines[edit_line] + 1);
        if (!cmd)
            cmd = Cvar_CompleteVariable(key_lines[edit_line] + 1);
        if (cmd)
        {
            Q_strcpy(key_lines[edit_line] + 1, cmd);
            key_linepos = Q_strlen(cmd) + 1;
            key_lines[edit_line][key_linepos] = ' ';
            key_linepos++;
            key_lines[edit_line][key_linepos] = 0;
            return;
        }
    }

    if (key == K_BACKSPACE || key == K_LEFTARROW)
    {
        if (key_linepos > 1)
            key_linepos--;
        return;
    }

    if (key == K_UPARROW)
    {
#if HISTORY
		do
		{
			history_line = (history_line - 1) % MAX_HISTORY_LINES;
		} while (history_line != edit_line
				&& !key_lines[history_line][1]);
		if (history_line == edit_line)
			history_line = (edit_line+1) % MAX_HISTORY_LINES;
		Q_strcpy(key_lines[edit_line], key_lines[history_line]);
		key_linepos = Q_strlen(key_lines[edit_line]);
#else
        cheat_line = ((cheat_line + 1)) % (sizeof(cheats) / sizeof(cheats[0]));
        key_lines[edit_line][0] = ']';
        Q_strcpy(&key_lines[edit_line][1], cheats[cheat_line]);
        key_linepos = Q_strlen(key_lines[edit_line]);
#endif // HISTORY
        return;
    }

    if (key == K_DOWNARROW)
    {
#if HISTORY
		if (history_line == edit_line) return;
		do
		{
			history_line = (history_line + 1) % MAX_HISTORY_LINES;
		}
		while (history_line != edit_line
			&& !key_lines[history_line][1]);
		if (history_line == edit_line)
		{
			key_lines[edit_line][0] = ']';
			key_linepos = 1;
		}
		else
		{
			Q_strcpy(key_lines[edit_line], key_lines[history_line]);
			key_linepos = Q_strlen(key_lines[edit_line]);
		}
#else
        cheat_line = cheat_line - 1;
        if (cheat_line < 0)
            cheat_line = sizeof(cheats) / sizeof(cheats[0]) - 1;
        key_lines[edit_line][0] = ']';
        Q_strcpy(&key_lines[edit_line][1], cheats[cheat_line]);
        key_linepos = Q_strlen(key_lines[edit_line]);

#endif
        return;
    }

    if (key == K_PGUP || key == K_MWHEELUP)
    {
        con_backscroll += 2;
        if (con_backscroll > con_totallines - (vid.height >> 3) - 1)
            con_backscroll = con_totallines - (vid.height >> 3) - 1;
        return;
    }

    if (key == K_PGDN || key == K_MWHEELDOWN)
    {
        con_backscroll -= 2;
        if (con_backscroll < 0)
            con_backscroll = 0;
        return;
    }

    if (key == K_HOME)
    {
        con_backscroll = con_totallines - (vid.height >> 3) - 1;
        return;
    }

    if (key == K_END)
    {
        con_backscroll = 0;
        return;
    }

    if (key < 32 || key > 127)
        return;	// non printable

    if (key_linepos < MAXCMDLINE - 1)
    {
        key_lines[edit_line][key_linepos] = key;
        key_linepos++;
        key_lines[edit_line][key_linepos] = 0;
    }

}

//============================================================================

#if ENABLE_CHAT
char chat_buffer[32];
qboolean team_message = false;

void Key_Message (int key)
{
	static int chat_bufferlen = 0;

	if (key == K_ENTER)
	{
		if (team_message)
			Cbuf_AddText ("say_team \"");
		else
			Cbuf_AddText ("say \"");
		Cbuf_AddText(chat_buffer);
		Cbuf_AddText("\"\n");

		key_dest = key_game;
		chat_bufferlen = 0;
		chat_buffer[0] = 0;
		return;
	}

	if (key == K_ESCAPE)
	{
		key_dest = key_game;
		chat_bufferlen = 0;
		chat_buffer[0] = 0;
		return;
	}

	if (key < 32 || key > 127)
		return;	// non printable

	if (key == K_BACKSPACE)
	{
		if (chat_bufferlen)
		{
			chat_bufferlen--;
			chat_buffer[chat_bufferlen] = 0;
		}
		return;
	}

	if (chat_bufferlen == 31)
		return; // all full

	chat_buffer[chat_bufferlen++] = key;
	chat_buffer[chat_bufferlen] = 0;
}
#else
void Key_Message(int key)
{
    (void) key;
}
#endif
//============================================================================

/*
 ===================
 Key_StringToKeynum

 Returns a key number to be used to index keybindings[] by looking at
 the given string.  Single ascii characters return themselves, while
 the K_* names are matched up.
 ===================
 */
int Key_StringToKeynum(char *str)
{
    const keyname_t *kn;

    if (!str || !str[0])
        return -1;
    if (!str[1])
        return str[0];

    for (kn = keynames; kn->name; kn++)
    {
        if (!Q_strcasecmp(str, kn->name))
            return kn->keynum;
    }
    return -1;
}

/*
 ===================
 Key_KeynumToString

 Returns a string (either a single ascii char, or a K_* name) for the
 given keynum.
 FIXME: handle quote special (general escape sequence?)
 ===================
 */
char* Key_KeynumToString(int keynum)
{
    const keyname_t *kn;
    static char tinystr[2];

    if (keynum == -1)
        return "<KEY NOT FOUND>";
    if (keynum > 32 && keynum < 127)
    {	// printable ascii
        tinystr[0] = keynum;
        tinystr[1] = 0;
        return tinystr;
    }

    for (kn = keynames; kn->name; kn++)
        if (keynum == kn->keynum)
            return kn->name;

    return "<UNKNOWN KEYNUM>";
}

/*
 ===================
 Key_SetBinding
 ===================
 */
void Key_SetBinding(int keynum, char *binding)
{
    if (keynum == -1)
        return;

// free old bindings
#if FULL_KEYBINDING
	 int   l;
	char  *new;
	if (keybindings[keynum])
	{
		Z_Free (keybindings[keynum]);
		keybindings[keynum] = NULL;
	}

// allocate memory for new binding
	l = Q_strlen (binding);
	new = Z_Malloc (l+1);
	Q_strcpy (new, binding);
	new[l] = 0;
	keybindings[keynum] = new;
#else
    keybindings[keynum] = findKeyCommandIndex(binding);
#endif
}

/*
 ===================
 Key_Unbind_f
 ===================
 */
void Key_Unbind_f(void)
{
    int b;

    if (Cmd_Argc() != 2)
    {
        Con_Printf("unbind <key> : remove commands from a key\n");
        return;
    }

    b = Key_StringToKeynum(Cmd_Argv(1));
    if (b == -1)
    {
        Con_Printf("\"%s\" isn't a valid key\n", Cmd_Argv(1));
        return;
    }

    Key_SetBinding(b, "");
}

void Key_Unbindall_f(void)
{
    int i;

    for (i = 0; i < 256; i++)
        Key_SetBinding(i, "");
}

/*
 ===================
 Key_Bind_f
 ===================
 */
void Key_Bind_f(void)
{
    int i, c, b;
    char cmd[1024];

    c = Cmd_Argc();
    if (c != 2 && c != 3)
    {
        Con_Printf("bind <key> [command] : attach a command to a key\n");
        return;
    }
    b = Key_StringToKeynum(Cmd_Argv(1));
    if (b == -1)
    {
        Con_Printf("\"%s\" isn't a valid key\n", Cmd_Argv(1));
        return;
    }

    if (c == 2)
    {
        if (keybindings[b])
            Con_Printf("\"%s\" = \"%s\"\n", Cmd_Argv(1), getKeybindName(b));
        else
            Con_Printf("\"%s\" is not bound\n", Cmd_Argv(1));
        return;
    }

// copy the rest of the command line
    cmd[0] = 0;		// start out with a null string
    for (i = 2; i < c; i++)
    {
        if (i > 2)
            strcat(cmd, " ");
        strcat(cmd, Cmd_Argv(i));
    }
    // FIXME("BINDING");

    Key_SetBinding(b, cmd);
    printf("Key %d is bound to: %s. Actual %s\r\n", b, cmd, getKeybindName(b));

}

/*
 ============
 Key_WriteBindings

 Writes lines containing "bind key value"
 ============
 */
void Key_WriteBindings(byte **pos)
{
    // TODO: not tested!
    int i;
    for (i = 0; i < 256; i++)
    {
        if (keybindings[i])
        {
            // get the bind command name for the selected binding.
            const char *bindname = getBindname(keybindings[i]);
            if (NULL == bindname)
                continue;
            int written;
            char tempstring[64];
            written = snprintf(tempstring, sizeof(tempstring) - 4, "bind \"%s\" \"%s\"\n", Key_KeynumToString(i), bindname);
            //  extMemory can only write in block of 4 bytes. Luckily adding spaces is not an issue.
            if (written <= 0)
            {
#if WIN32
                FIXME("SOMETHING NEEDS YOUR ATTENTION!");
        #endif // WIN32
                return;         // stop if something happened.
            }
            unsigned int nextWritten = (written + 3) & ~3;
            for (unsigned int j = written; j < nextWritten; j++)
            {
                tempstring[j] = ' ';
            }
            extMemProgram((uint32_t) *pos, (uint8_t*) tempstring, nextWritten);
            *pos = *pos + nextWritten;
        }
    }

}

/*
 ===================
 Key_Init
 ===================
 */
void Key_Init(void)
{
    int i;

    for (i = 0; i < MAX_HISTORY_LINES; i++)
    {
        key_lines[i][0] = ']';
        key_lines[i][1] = 0;
    }
    key_linepos = 1;
#if USE_BOUND_KEYS_ARRAY
//
// init ascii characters in console mode
//
	for (i=32 ; i<128 ; i++)
    {
        #if USE_KEY_QBOOLEANS
            consolekeys[i] = true;
        #else
            set_consolekeys(i, true);
        #endif // USE_KEY_QBOOLEANS
    }
        #if USE_KEY_QBOOLEANS
            consolekeys[K_ENTER] = true;
            consolekeys[K_TAB] = true;
            consolekeys[K_LEFTARROW] = true;
            consolekeys[K_RIGHTARROW] = true;
            consolekeys[K_UPARROW] = true;
            consolekeys[K_DOWNARROW] = true;
            consolekeys[K_BACKSPACE] = true;
            consolekeys[K_PGUP] = true;
            consolekeys[K_PGDN] = true;
            consolekeys[K_SHIFT] = true;
            consolekeys[K_MWHEELUP] = true;
            consolekeys[K_MWHEELDOWN] = true;
            consolekeys['`'] = false;
            consolekeys['~'] = false;
        	menubound[K_ESCAPE] = true;
        #else
            set_consolekeys(K_ENTER, true);
            set_consolekeys(K_CTRL, true);
            set_consolekeys(K_TAB, true);
            set_consolekeys(K_LEFTARROW, true);
            set_consolekeys(K_RIGHTARROW, true);
            set_consolekeys(K_UPARROW, true);
            set_consolekeys(K_DOWNARROW, true);
            set_consolekeys(K_BACKSPACE, true);
            set_consolekeys(K_PGUP, true);
            set_consolekeys(K_PGDN, true);
            set_consolekeys(K_SHIFT, true);
            set_consolekeys(K_MWHEELUP, true);
            set_consolekeys(K_MWHEELDOWN, true);
            set_consolekeys('`', false);
            set_consolekeys('~', false);
            set_menubound(K_ESCAPE, true);
        #endif
#if 0
	for (i=0 ; i<256 ; i++)
		keyshift[i] = i;
	for (i='a' ; i<='z' ; i++)
		keyshift[i] = i - 'a' + 'A';
	keyshift['1'] = '!';
	keyshift['2'] = '@';
	keyshift['3'] = '#';
	keyshift['4'] = '$';
	keyshift['5'] = '%';
	keyshift['6'] = '^';
	keyshift['7'] = '&';
	keyshift['8'] = '*';
	keyshift['9'] = '(';
	keyshift['0'] = ')';
	keyshift['-'] = '_';
	keyshift['='] = '+';
	keyshift[','] = '<';
	keyshift['.'] = '>';
	keyshift['/'] = '?';
	keyshift[';'] = ':';
	keyshift['\''] = '"';
	keyshift['['] = '{';
	keyshift[']'] = '}';
	keyshift['`'] = '~';
	keyshift['\\'] = '|';
#endif
#if USE_KEY_QBOOLEANS
	for (i=0 ; i<12 ; i++)
		menubound[K_F1+i] = true;
#else
	for (i=0 ; i<12 ; i++)
		set_menubound(K_F1 + i, true);

#endif
#endif
//
// register our functions
//

}

/*
 ===================
 Key_Event

 Called by the system between frames for both key up and key down events
 Should NOT be called during an interrupt!
 ===================
 */
void Key_Event(int key, qboolean down)
{
    const char *kb;
#if USE_MORE_STACK
	char	cmd[1024];
#else
    tempStringStack -= 1024;
    char *cmd = tempStringStack;
#endif
#if USE_KEY_QBOOLEANS
	keydown[key] = down;
#else
    set_keydown(key, down);
#endif // USE_KEY_QBOOLEANS
#if WIN32
	if (!down)
		key_repeats[key] = 0;
#endif
    key_lastpress = key;
    key_count++;
    if (key_count <= 0)
    {
        return;		// just catching keys for Con_NotifyBox
    }

// update auto-repeat status
    if (down)
    {
#if WIN32
	    if (key_repeats < 126)
		    key_repeats[key]++;
		if (key != K_BACKSPACE && key != K_PAUSE && key_repeats[key] > 1)
		{
			return;	// ignore most autorepeats
		}
#endif
        if (key >= 200 && !keybindings[key])
            Con_Printf("%s is unbound, hit F4 to set.\n", Key_KeynumToString(key));
    }

    if (key == K_SHIFT)
        shift_down = down;

//
// handle escape especially, so the user can never unbind it
//
    if (key == K_ESCAPE)
    {
        if (!down)
            return;
        switch (key_dest)
        {
            case key_message:
                Key_Message(key);
                break;
            case key_menu:
                M_Keydown(key);
                break;
            case key_game:
            case key_console:
                M_ToggleMenu_f();
                break;
            default:
                Sys_Error("Bad key_dest");
        }
        return;
    }

//
// key up events only generate commands if the game key binding is
// a button command (leading + sign).  These will occur even in console mode,
// to keep the character from continuing an action started before a console
// switch.  Button commands include the kenum as a parameter, so multiple
// downs can be matched with ups
//
    if (!down)
    {

        kb = getKeybindName(key);
        if (kb && kb[0] == '+')
        {
            sprintf(cmd, "-%s %i\n", kb + 1, key);
            Cbuf_AddText(cmd);
        }
        if (keyshift[key] != key)
        {

            kb = getKeybindName(keyshift[key]);
            if (kb && kb[0] == '+')
            {
                sprintf(cmd, "-%s %i\n", kb + 1, key);
                Cbuf_AddText(cmd);
            }
        }
        return;
    }

//
// during demo playback, most keys bring up the main menu
//
#if USE_KEY_QBOOLEANS
	if (_g->cls.demoplayback && down && consolekeys[key] && key_dest == key_game)
#else
    if (_g->cls.demoplayback && down && get_consolekeys(key) && key_dest == key_game)
#endif
    {
        M_ToggleMenu_f();
        return;
    }

//
// if not a consolekey, send to the interpreter no matter what mode is
//
#if USE_KEY_QBOOLEANS
	if ( (key_dest == key_menu && menubound[key])
	|| (key_dest == key_console && !consolekeys[key])
	|| (key_dest == key_game && ( !con_forcedup || !consolekeys[key] ) ) )
#else
    if ((key_dest == key_menu && get_menubound(key)) || (key_dest == key_console && !get_consolekeys(key))
        || (key_dest == key_game && (!con_forcedup || !get_consolekeys(key))))
#endif
    {

        kb = getKeybindName(key);
        if (kb)
        {
            if (kb[0] == '+')
            {	// button commands add keynum as a parm
                sprintf(cmd, "%s %i\n", kb, key);
                Cbuf_AddText(cmd);
            }
            else
            {
                Cbuf_AddText(kb);
                Cbuf_AddText("\n");
            }
        }
        return;
    }

    if (!down)
        return;		// other systems only care about key down events

    if (shift_down)
    {
        key = keyshift[key];
    }

    switch (key_dest)
    {
        case key_message:
            Key_Message(key);
            break;
        case key_menu:
            M_Keydown(key);
            break;

        case key_game:
        case key_console:
            Key_Console(key);
            break;
        default:
            Sys_Error("Bad key_dest");
    }
}

/*
 ===================
 Key_ClearStates
 ===================
 */
void Key_ClearStates(void)
{
#if USE_KEY_QBOOLEANS
    int     i;
    for (i=0 ; i<256 ; i++)
	{
		keydown[i] = false;
#if WIN32
		key_repeats[i] = 0;
#endif
	}
#else
    memset(ba_keydown, 0, sizeof(ba_keydown));
#if WIN32
    memset(key_repeats, 0, sizeof(key_repeats));
#endif
#endif
}


