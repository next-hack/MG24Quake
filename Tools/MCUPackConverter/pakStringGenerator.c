/*
 MCUpackconverter by Nicola Wrachien (next-hack in the comments)

 Copyright (C) 2023-2024 Nicola Wrachien (next-hack in the comments).

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
#define MAX_PAK_STRINGS 2048        // well, will be less.
int numPakStrings = 0;
char *pakStrings[MAX_PAK_STRINGS];
void addStringToList(char *str)
{
    for (int i = 0; i < numPakStrings; i++)
    {
        if (!strcmp(str,pakStrings[i]))
        {
//            printf("String <%s> found, skipped\r\n", str);
            return;     // found, do not add
        }
    }
//    printf("String <%s> added at index %i\r\n", str, numPakStrings);
    pakStrings[numPakStrings] = calloc(strlen(str) + 1, 1);
    strcpy(pakStrings[numPakStrings], str);
    numPakStrings++;
}
char *COM_Parse (char *data, char *com_token)
{
	int             c;
	int             len;

	len = 0;
	com_token[0] = 0;

	if (!data)
		return NULL;

// skip whitespace
skipwhite:
	while ( (c = *data) <= ' ')
	{
		if (c == 0)
			return NULL;                    // end of file;
		data++;
	}

// skip // comments
	if (c=='/' && data[1] == '/')
	{
		while (*data && *data != '\n')
			data++;
		goto skipwhite;
	}


// handle quoted strings specially
	if (c == '\"')
	{
		data++;
		while (1)
		{
			c = *data++;
			if (c=='\"' || !c)
			{
				com_token[len] = 0;
				return data;
			}
			com_token[len] = c;
			len++;
		}
	}

// parse single characters
	if (c=='{' || c=='}'|| c==')'|| c=='(' || c=='\'' || c==':')
	{
		com_token[len] = c;
		len++;
		com_token[len] = 0;
		return data+1;
	}

// parse a regular word
	do
	{
		com_token[len] = c;
		data++;
		len++;
		c = *data;
	if (c=='{' || c=='}'|| c==')'|| c=='(' || c=='\'' || c==':')
			break;
	} while (c>32);

	com_token[len] = 0;
	return data;
}
#define	SPAWNFLAG_NOT_EASY			256
#define	SPAWNFLAG_NOT_MEDIUM		512
#define	SPAWNFLAG_NOT_HARD			1024
char * parseEdictStrings (char *data, int *spawnflags)
{
	char		keyname[256];
	int			n;
    char	com_token[1024];
    int init;
// go through all the dictionary pairs
    int isLight = 0, lightTargetNameLen = 0 ;
    *spawnflags = 0;
	while (1)
	{
	// parse key
		data = COM_Parse (data, com_token);
		if (com_token[0] == '}')
			break;
		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

		strcpy (keyname, com_token);

		// another hack to fix heynames with trailing spaces
		n = strlen(keyname);
		while (n && keyname[n-1] == ' ')
		{
			keyname[n-1] = 0;
			n--;
		}

	// parse value
		data = COM_Parse (data, com_token);
		if (!data)
			Sys_Error ("ED_ParseEntity: EOF without closing brace");

		if (com_token[0] == '}')
			Sys_Error ("ED_ParseEntity: closing brace without data");

        init = 1;

		if (keyname[0] == '_')
			continue;
        //printf("Keyname is %s\r\n", keyname);
        addStringToList(keyname);
        // The following code is used just to check if the edict will actually be present
        // remove ambient sounds
        if (strcmp(keyname, "classname") == 0 && strstr(com_token, "ambient"))
        {
            *spawnflags = SPAWNFLAG_NOT_EASY | SPAWNFLAG_NOT_MEDIUM | SPAWNFLAG_NOT_HARD ;
        }
        // remove inert light
        if (strcmp(keyname, "classname") == 0 && !strcmp(com_token, "light"))
        {
                isLight = 1;
        }
        if (strcmp(keyname, "targetname") == 0)
        {
            lightTargetNameLen = strlen(com_token);
        }
        // end code to check if the edict will be present.
        if (!strcmp(keyname, "wad") ||
            !strcmp(keyname, "message") ||
            !strcmp(keyname, "worldtype") ||
            !strcmp(keyname, "map") ||
            !strcmp(keyname, "target"))
            addStringToList(com_token);
        if (strcmp(keyname, "spawnflags") == 0)
        {
            float sf = atof(com_token);
            *spawnflags = (int) sf | *spawnflags;
        }
    }
    // the following code is just to understand limits
    if (isLight && !lightTargetNameLen)
    {
      *spawnflags = SPAWNFLAG_NOT_EASY | SPAWNFLAG_NOT_MEDIUM | SPAWNFLAG_NOT_HARD ;
    }
    if (!init)
        *spawnflags = SPAWNFLAG_NOT_EASY | SPAWNFLAG_NOT_MEDIUM | SPAWNFLAG_NOT_HARD ;
    return data;
}
void parseEntityList (char *data)
{
    char	com_token[1024];
#if PROFILE_NUM_ELEMENTS
    int entnumEasy = 0;
    int entnumMedium = 0;
    int entnumHard = 0;

#endif // PROFILE_NUM_ELEMENTS
// parse ents
	while (1)
	{
// parse the opening brace
		data = COM_Parse (data, com_token);
		if (!data)
			break;
		if (com_token[0] != '{')
        {
			printf ("parseEntityList: found %s when expecting {",com_token);
			FIXME("ERROR");
        }
        int spawnflags = 0;
        data = parseEdictStrings (data, &spawnflags);
#if PROFILE_NUM_ELEMENTS
    if (!(spawnflags & SPAWNFLAG_NOT_EASY))
    {
        entnumEasy++;
        PROFILE(EntitiesEasy, entnumEasy);
    }
    if (!(spawnflags & SPAWNFLAG_NOT_MEDIUM))
    {
        entnumMedium++;
        PROFILE(EntitiesMedium, entnumMedium);
    }
    if (!(spawnflags & SPAWNFLAG_NOT_HARD))
    {
        entnumHard++;
        PROFILE(EntitiesHard, entnumHard);
    }
#endif // PROFILE_NUM_ELEMENTS
    }
    printf("# ENTITIES IN THIS MAP %d %d %d\r\n<<<<<<<<<<<<<<", entnumEasy, entnumMedium, entnumHard);
}
void printAllPakStrings(void)
{
    system("cls");
    printf("//Autogenerated file, do not edit!\r\n");
    printf("#define MAX_PAK_STRINGS     %d\r\n", numPakStrings);
    printf("const char * const pakStrings[MAX_PAK_STRINGS] = \r\n{\r\n");
    for (int i = 0; i < numPakStrings; i++)
    {
        printf("    \"%s\",\r\n", pakStrings[i]);
    }
    printf("};\r\n");
}
