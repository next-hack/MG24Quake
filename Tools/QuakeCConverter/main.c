/*
    QuakeCConverter by Nicola Wrachien (next-hack in the comments)
    This code is based on Quake C compiler by Id Software.

    Copyright 2023-2024 Nicola Wrachien (next-hack in the comments)

    This program translates .qc code into equally crappy C code.
    This should be somewhat faster and smaller, though. It does not make any check,
    so code that won't compile in QuakeC, won't compile in C as well.

    Limitations, known issues:

    - Man, this really require clean up! Also, in the meantime we are creating the C code, some additional
    compiling stuff (unnecessary for what we need) is still done, should be removed.
    - Comments are also misplaced. Since they have no effects, they are left as is.
    - Functions in QuakeC code must be declared before they are used, otherwise funny crash will occur in Quake.
    - spawn function originally took no parameter, but in this case you need to specify the class name.

    No worry anyway: it is really unlikely you are using this code. There is no support for it.

    This code is based on Id Software's Quake C compiler, and follows its license:
    Copyright (C) 1996-1997  Id Software, Inc.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

    See file, 'COPYING', for details.
*/


#include <stdio.h>
#include <stdlib.h>
#include "qcc.h"


char header[] =
{
    "// Warning! Machine-generated code, do not edit!\r\n"
    "\r\n"
    "/* Copyright (C) 2023-2024 Nicola Wrachien\r\n"
    "\r\n"
    " This program is free software; you can redistribute it and/or\r\n"
    " modify it under the terms of the GNU General Public License\r\n"
    " as published by the Free Software Foundation; either version 2\r\n"
    " of the License, or (at your option) any later version.\r\n"
    "\r\n"
    " This program is distributed in the hope that it will be useful,\r\n"
    " but WITHOUT ANY WARRANTY; without even the implied warranty of\r\n"
    " MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\r\n"
    "\r\n"
    " See the GNU General Public License for more details.\r\n"
    "\r\n"
    " You should have received a copy of the GNU General Public License\r\n"
    " along with this program; if not, write to the Free Software\r\n"
    " Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.\r\n"
    "*/\r\n"
};

char	com_token[1024];
extern FILE * c_file;
int main()
{
    char	*src;
	char	*src2;
	char	filename[1024];
	char	sourcedir[1024]= "v101qc\\";
    //
 	snprintf (filename, sizeof(filename), "%sprogs.src", sourcedir);
	LoadFile (filename, (void *)&src);
    //
	src = COM_Parse (src);
	//
	c_file = fopen("bigprog.qc","wb");
    // join all the files in a single one
	while(1)
	{
		src = COM_Parse(src);
		if (!src)
			break;
        printf("Adding file %s\r\n", com_token);
		snprintf (filename, sizeof(filename), "%s%s", sourcedir, com_token);
		fprintf(c_file, "//File: %s\r\n", com_token);
		FILE *f = fopen(filename, "rb");
        int n = 0;
		char buffer[1024];
		while(1)
        {
            n = fread(buffer, 1, 1024, f);
            if (!n)
            {
                fclose(f);
                break;
            }
            fwrite(buffer, 1, n, c_file);
        }
	}
    fclose(c_file);
    // compile the single big file
	PR_BeginCompilation (malloc (0x1000000), 0x1000000);
    c_file = fopen("progs.c","wb");
    //
	LoadFile ("bigprog.qc", (void *)&src2);
    if (!PR_CompileFile (src2, filename) )
    {
        exit (1);
    }
   	if (!PR_FinishCompilation ())
    {
		Error ("compilation errors");
    }
   fclose(c_file);
//
    c_file = fopen("quakeProgs.h","wb");
    fprintf(c_file, "%s", header);
    PR_PrintSymbols(PRINT_SYMBOL_INDEX); // print only indexes
    fclose(c_file);
    c_file = fopen("progs.h","wb");
    PR_PrintSymbols(PRINT_SYMBOL_ARRAY);  // define array only.
    fclose(c_file);
    FILE *cf = fopen("progs.c","rb");
    FILE *hf = fopen("progs.h","rb");
    FILE *ff = fopen("quakeProgs.c","wb");
    char c;
    fprintf(ff, "%s", header);
    fprintf(ff, "#include \"quakedef.h\"\r\n");
    fprintf(ff, "#if !USE_PROGSDAT\r\n");
    fprintf(ff, "progsvars_t %s;\r\n", GLOBAL_STRUCT_NAME);
    fprintf (ff, "#include \"cprogs_def.h\"\r\n");
    fprintf(ff, "#pragma GCC diagnostic push\r\n");
    fprintf(ff, "// next-hack: suppress frequently occurring warnings in Quake C scripts. We don't want to fix every issue\r\n");
    fprintf(ff, "#pragma GCC diagnostic ignored \"-Wunused-parameter\"\r\n");
    fprintf(ff, "#pragma GCC diagnostic ignored \"-Wunused-variable\"\r\n");
    fprintf(ff, "#pragma GCC diagnostic ignored \"-Wunused-but-set-variable\"\r\n");
    while  (1 == fread(&c, 1, 1, hf))
    {
        fputc(c, ff);
    }
    fclose(hf);
    while (1 == fread(&c, 1, 1, cf))
    {
        fputc(c, ff);
    }
    fclose(cf);
    fprintf(ff, "#pragma GCC diagnostic pop\r\n");
    fprintf(ff, "#endif // !USE_PROGSDAT\r\n");

    fclose(ff);
    PR_WriteNewProgdefs("newprogsdef.h");
    return 0;
}

