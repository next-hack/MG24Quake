/*  Quake C Converter by Nicola Wrachien (next-hack in the comments)

    Copyright (C) 2023-2024, Nicola Wrachien (next-hack in the comments)

    Based on Id Software's Quake C compiler, and following its license:
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

#include "qcc.h"
#include <stdint.h>
#include <stdbool.h>
char *paramsStringDbg[] = {"void", "string", "float", "vector", "int", "field", "function", "void *"};
char *paramsString[] = {"void", "uint16_t", "float", "vector", "int", "field", "function", "void *"};

#define MAIN_FUNCTION_TRANSLATION    "qcc_main"
char functionStatePreamble[1024];       // for expanding state definition insinde function.
int tablevel = 0;
const int tabspace = 4;
int g_compile_progs_dat = 0;
int g_showInConsole = 0;
#define TABMOD "%*s"
#define TABSPACE (tablevel*tabspace),""
pr_info_t	pr;
def_t		*pr_global_defs[MAX_REGS];	// to find def for a global variable
int			pr_edict_size;

//========================================

def_t		*pr_scope;		// the function being parsed, or NULL
boolean	pr_dumpasm;
string_t	s_file;			// filename for function definition

int			locals_end;		// for tracking local variables vs temps

jmp_buf		pr_parse_abort;		// longjump with this on parse error

void PR_ParseDefs (void);

//========================================


opcode_t pr_opcodes[] =
{
 {"<DONE>", "DONE", -1, false, &def_entity, &def_field, &def_void},

 {"*", "MUL_F", 2, false, &def_float, &def_float, &def_float},
 {"*", "MUL_V", 2, false, &def_vector, &def_vector, &def_float},
 {"*", "MUL_FV", 2, false, &def_float, &def_vector, &def_vector},
 {"*", "MUL_VF", 2, false, &def_vector, &def_float, &def_vector},

 {"/", "DIV", 2, false, &def_float, &def_float, &def_float},

 {"+", "ADD_F", 3, false, &def_float, &def_float, &def_float},
 {"+", "ADD_V", 3, false, &def_vector, &def_vector, &def_vector},

 {"-", "SUB_F", 3, false, &def_float, &def_float, &def_float},
 {"-", "SUB_V", 3, false, &def_vector, &def_vector, &def_vector},

 {"==", "EQ_F", 4, false, &def_float, &def_float, &def_float},
 {"==", "EQ_V", 4, false, &def_vector, &def_vector, &def_float},
 {"==", "EQ_S", 4, false, &def_string, &def_string, &def_float},
 {"==", "EQ_E", 4, false, &def_entity, &def_entity, &def_float},
 {"==", "EQ_FNC", 4, false, &def_function, &def_function, &def_float},

 {"!=", "NE_F", 4, false, &def_float, &def_float, &def_float},
 {"!=", "NE_V", 4, false, &def_vector, &def_vector, &def_float},
 {"!=", "NE_S", 4, false, &def_string, &def_string, &def_float},
 {"!=", "NE_E", 4, false, &def_entity, &def_entity, &def_float},
 {"!=", "NE_FNC", 4, false, &def_function, &def_function, &def_float},

 {"<=", "LE", 4, false, &def_float, &def_float, &def_float},
 {">=", "GE", 4, false, &def_float, &def_float, &def_float},
 {"<", "LT", 4, false, &def_float, &def_float, &def_float},
 {">", "GT", 4, false, &def_float, &def_float, &def_float},

 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_float},
 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_vector},
 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_string},
 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_entity},
 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_field},
 {".", "INDIRECT", 1, false, &def_entity, &def_field, &def_function},

 {".", "ADDRESS", 1, false, &def_entity, &def_field, &def_pointer},

 {"=", "STORE_F", 5, true, &def_float, &def_float, &def_float},
 {"=", "STORE_V", 5, true, &def_vector, &def_vector, &def_vector},
 {"=", "STORE_S", 5, true, &def_string, &def_string, &def_string},
 {"=", "STORE_ENT", 5, true, &def_entity, &def_entity, &def_entity},
 {"=", "STORE_FLD", 5, true, &def_field, &def_field, &def_field},
 {"=", "STORE_FNC", 5, true, &def_function, &def_function, &def_function},

 {"=", "STOREP_F", 5, true, &def_pointer, &def_float, &def_float},
 {"=", "STOREP_V", 5, true, &def_pointer, &def_vector, &def_vector},
 {"=", "STOREP_S", 5, true, &def_pointer, &def_string, &def_string},
 {"=", "STOREP_ENT", 5, true, &def_pointer, &def_entity, &def_entity},
 {"=", "STOREP_FLD", 5, true, &def_pointer, &def_field, &def_field},
 {"=", "STOREP_FNC", 5, true, &def_pointer, &def_function, &def_function},

 {"return", "RETURN", -1, false, &def_void, &def_void, &def_void},

 {"!", "NOT_F", -1, false, &def_float, &def_void, &def_float},
 {"!", "NOT_V", -1, false, &def_vector, &def_void, &def_float},
 {"!", "NOT_S", -1, false, &def_vector, &def_void, &def_float},
 {"!", "NOT_ENT", -1, false, &def_entity, &def_void, &def_float},
 {"!", "NOT_FNC", -1, false, &def_function, &def_void, &def_float},

  {"if", "IF", -1, false, &def_float, &def_float, &def_void},
  {"<IFNOT>", "IFNOT", -1, false, &def_float, &def_float, &def_void},

// calls returns REG_RETURN
 {"<CALL0>", "CALL0", -1, false, &def_function, &def_void, &def_void},
 {"<CALL1>", "CALL1", -1, false, &def_function, &def_void, &def_void},
 {"<CALL2>", "CALL2", -1, false, &def_function, &def_void, &def_void},
 {"<CALL3>", "CALL3", -1, false, &def_function, &def_void, &def_void},
 {"<CALL4>", "CALL4", -1, false, &def_function, &def_void, &def_void},
 {"<CALL5>", "CALL5", -1, false, &def_function, &def_void, &def_void},
 {"<CALL6>", "CALL6", -1, false, &def_function, &def_void, &def_void},
 {"<CALL7>", "CALL7", -1, false, &def_function, &def_void, &def_void},
 {"<CALL8>", "CALL8", -1, false, &def_function, &def_void, &def_void},

 {"<STATE>", "STATE", -1, false, &def_float, &def_float, &def_void},

 {"<GOTO>", "GOTO", -1, false, &def_float, &def_void, &def_void},

 {"&&", "AND", 6, false, &def_float, &def_float, &def_float},
 {"||", "OR", 6, false, &def_float, &def_float, &def_float},

 {"&", "BITAND", 2, false, &def_float, &def_float, &def_float},
 {"|", "BITOR", 2, false, &def_float, &def_float, &def_float},

 {NULL}
};

#define	TOP_PRIORITY	6
#define	NOT_PRIORITY	4

def_t *PR_Expression (int priority);

def_t	junkdef;
FILE *c_file;

//
char * getParamTypeName(char * buffer, type_t *type, char *nameParam, int expandFunction);
//===========================================================================
uint32_t strhash(const char *string)
{
    int n = strlen(string);
    int n4 = n / 4;
    uint32_t hash = 0;
    for (int i = 0; i < n4; i++)
    {
        hash += *((uint32_t*)(&string[i * 4]));
    }
    // remainder
    for (int i = 0; i < n - n4 * 4; i++)
    {
        hash = hash + ((uint32_t) string [i + n4 *4] << (8 * i));
    }
    return hash;
}
char *symbolizeString(char *buffer, const char * string)
{
    char *p = buffer;
    int n = strlen(string);
    int longSymbol = 0;
    uint32_t hash = 0;
    if (n > MAX_STRING_SYMBOL_LENGTH)
    {
        longSymbol = 1;
        hash = strhash(string);
        n = MAX_STRING_SYMBOL_LENGTH;
    }
    if (string[0] >= '0' && string[0] <= '9') // first char can't be a number
    {
        *p++ = 'n';     //n indicates it's a number
        n--;
    }
    for (int i = 0; i < n; i++)
    {
        char  c = string[i];
        if ((c >='A' && c <= 'Z') || (c >='0' && c <= '9') || (c >='a' && c <='z'))
        {
            *p++ = c;
        }
        else if (c == '\n')
        {
          //  printf("c is %d, i is %d, n is %d", c, i,n);
          //  FIXME("");
            *p++ = '_';
            *p++ = 'n';
            *p++ = '_';
        }
        else
        {
            *p++ = '_';
        }
    }
    *p = 0;
    if (longSymbol)
    {
        char temp[64];
        snprintf(temp, sizeof(temp), "_%08X_long", hash);
        strcat(buffer, temp);
    }
    if (n == 0)
    {
        strcat(buffer, "NULL");
    }
    strcat(buffer, "_string_index");
    return buffer;
}
//===========================================================================
int qc_printf(const char *format, ...)
{
int n = 0;
  va_list args;
  va_start (args, format);
  if (g_showInConsole)
    vprintf (format, args);
  if (c_file)
  {
    n = vfprintf(c_file, format, args);
  }
  va_end (args);
  return n;
}
//===========================================================================

void printVariable(def_t *var_a, char *buffer)
{
    int len = strlen(var_a->expression);
    if (!strcasecmp(var_a->name, "IMMEDIATE"))
    {

        if (var_a->type == &type_float)
        {
            float value = G_FLOAT(var_a->ofs);
            if (value == (int) value)       //integer part
            {
                snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%d", (int) value);
            }
            else
            {
                snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%gf", value);
            }
        }
        else if (var_a->type == &type_string)
        {
//            snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "\"%s\"", G_STRING(var_a->ofs));
            char symbolized[MAX_TEMP_EXPRESSION_TYPE];
            symbolizeString(symbolized, G_STRING(var_a->ofs));
            snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%s", symbolized);
        }
        else if (var_a->type == &type_vector)
        {
            snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "(vector)  {{%#gf, %#gf, %#gf}}", G_FLOAT(var_a->ofs), G_FLOAT(var_a->ofs + 1), G_FLOAT(var_a->ofs + 2));
        }
        else
            FIXME("Immediate not set");
    }
    else  // not immediate
    {
        // check and correct vectors
        // FIXME: FIX THIS CRAP....
        if (len >= 3)   // if we have A_x
        {
            if (var_a->expression[len - 2] == '_' && (var_a->expression[len - 1] >= 'x' && var_a->expression[len - 1] <= 'z'))
            {
                // special case when we have x, y, z. We would have qcc_x, qcc_y, qcc_z. These are not components of vector
                if (!(len >= 5 && var_a->expression[len - 5] == 'q' && var_a->expression[len - 4] == 'c' && var_a->expression[len - 3] == 'c'))
                {
                    var_a->expression[len - 2] = '.';
#if !NO_GLOBAL_IN_STRUCT && NOOOOOO
                    if (!var_a->scope && !strstr(var_a->expression,"(") )   // very crappy.
                    {
                        printf("Check me: %s\r\n", var_a->expression);
                       char string[MAX_TEMP_EXPRESSION_TYPE];
                        sprintf(string, "%s.%s", GLOBAL_STRUCT_NAME, var_a->expression);
                        free(var_a->expression);
                        var_a->expression = malloc(strlen(string) + 1);
                        strcpy(var_a->expression, string);
                                                printf("Became me: %s\r\n", string);


                    }
#endif // NO_GLOBAL_IN_STRUCT
                }
            }
        }
        snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%s", var_a->expression);
    }

}
char * generateSubExpressionString(opcode_t *op, def_t *var_a, def_t *var_b, char *setterString)
{
    char firstParam[MAX_TEMP_EXPRESSION_TYPE] = {0};
    char operatorString[MAX_TEMP_EXPRESSION_TYPE] = {0};
    char secondParam[MAX_TEMP_EXPRESSION_TYPE] = {0};
    char intermediateParam[MAX_TEMP_EXPRESSION_TYPE] = {0};
    /* we might have different cases based on:
        operand types
        operator

        For instance, * might translate into * if there are two floats
        but it might translate into vectorMulScalar(a, b) or scalarMulVector(a, b)

    */
        if (op->type_a->type != ev_void && var_a->expression != NULL)
        {
            if (var_a->type->type == ev_function && var_a->isRealFunction)
            {
                // NEVER FOUND
                FIXME("ERROR");
                    snprintf(firstParam, MAX_TEMP_EXPRESSION_TYPE, "getFunctionIndex(%s)", var_a->expression);
            }
            else
                printVariable(var_a, firstParam);
        };
	    // print operator
        snprintf(operatorString, MAX_TEMP_EXPRESSION_TYPE, "%s", op->name);
        // second param
        if (op->type_b->type->type != ev_void)
        {
            if (var_b->type->type == ev_function && var_b->isRealFunction)
            // used for something like: areFunctionsEqual(a, functionIndex)
            {
                    snprintf(secondParam, MAX_TEMP_EXPRESSION_TYPE, "getFunctionIndex(%s)", var_b->expression);
                    var_b->functionIndexUsed = true;
            }
            else
                printVariable(var_b, secondParam);
        }
        //
        int n;
        if (op->type_b->type->type != ev_void)
        {
            if (var_a->expression != NULL)
            {
                switch(op - pr_opcodes)
                {
                    case OP_MUL_FV:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "floatMulVector(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_MUL_VF:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "vectorMulFloat(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_MUL_V:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "dotProduct(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_SUB_V:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "vectorSub(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_ADD_V:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "vectorAdd(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_EQ_E:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "%s == %s", firstParam, secondParam);
                        break;
                    case OP_EQ_V:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "areVectorEqual(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_EQ_FNC:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "areFunctionsEqual(%s, %s)", firstParam, secondParam);
                        break;
                    case OP_EQ_S:
//                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(!strcmp(%s, %s))", firstParam, secondParam);
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "areStringsEqual(%s, %s)", firstParam, secondParam);
                        break;
                    case  OP_NE_E:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "%s != %s", firstParam, secondParam);
                        break;
                    case OP_NE_V:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(!areVectorEqual(%s, %s))", firstParam, secondParam);
                        break;
                    case OP_NE_FNC:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(!areFunctionsEqual(%s, %s))", firstParam, secondParam);
                        break;
                    case OP_NE_S:
//                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "strcmp(%s, %s)", firstParam, secondParam);
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(!areStringsEqual(%s, %s))", firstParam, secondParam);

                        break;
                    case OP_ADDRESS:
                    case OP_LOAD_F:
                    case OP_LOAD_V:
                    case OP_LOAD_S:
                    case OP_LOAD_ENT:
                    case OP_LOAD_FLD:
                    case OP_LOAD_FNC:
                        #if GETTER_FUNCTIONS
                            // let's remove the vector field.
                            {
                                bool hasVectorComponent = false;
                                int len = strlen(secondParam);
                                if (len >= 3)   // if we have A_x
                                {
                                    if (secondParam[len - 2] == '.' && (secondParam[len - 1] >= 'x' && secondParam[len - 1] <= 'z'))
                                    {
                                        // special case when we have x, y, z. We would have qcc_x, qcc_y, qcc_z. These are not components of vector
                                        if (!(len >= 5 && secondParam[len - 5] == 'q' && secondParam[len - 4] == 'c' && secondParam[len - 3] == 'c'))
                                        {
                                            secondParam[len - 2] = 0;
                                            hasVectorComponent = true;
                                        }
                                    }
                                }
                                if (hasVectorComponent)
                                {
                                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "get_%s(PROG_TO_EDICT(%s)).%c", secondParam, firstParam, secondParam[len - 1]);
                                    secondParam[len - 2] = '_';
                                    snprintf(setterString, MAX_TEMP_EXPRESSION_TYPE, "set_%s(PROG_TO_EDICT(%s), %%s)", secondParam, firstParam);
                                }
                                else
                                {
                                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "get_%s(PROG_TO_EDICT(%s))", secondParam, firstParam);
                                    snprintf(setterString, MAX_TEMP_EXPRESSION_TYPE, "set_%s(PROG_TO_EDICT(%s), %%s)", secondParam, firstParam);
                                }

                            }
                        #else
                            n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "PROG_TO_EDICT(%s)->v.%s", firstParam, secondParam);
                        #endif
                        break;
#if 0
                    case OP_LOAD_FNC:

                        #if GETTER_FUNCTIONS
                            n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "get_%s(PROG_TO_EDICT(%s))", secondParam, firstParam);
                            snprintf(setterString, MAX_TEMP_EXPRESSION_TYPE, "set_%s(PROG_TO_EDICT(%s), %%s)", secondParam, firstParam);
                        #else
                            n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "PROG_TO_EDICT(%s)->v.%s", firstParam, secondParam);
                        #endif
                        break;
#endif
                    case OP_AND:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "((int) %s) && ((int) %s)", firstParam, secondParam);
                        break;
                    case OP_BITAND: // in quakeC bitand and bitor have higher priority
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(((int) %s) & ((int) %s))", firstParam, secondParam);
                        break;
                    case OP_OR:
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "((int) %s) || ((int) %s)", firstParam, secondParam);
                        break;
                    case OP_BITOR:  // in quakeC bitand and bitor have higher priority
                        n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(((int) %s) | ((int) %s))", firstParam, secondParam);
                        break;
                    case    OP_STOREP_F:
                    case    OP_STOREP_V:
                    case OP_STOREP_S:
                    case OP_STOREP_ENT:
                    case OP_STOREP_FLD:
                    case OP_STOREP_FNC:
                        FIXME("error store not impl not used.");
                        break;

                    default:
                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "%s %s %s", firstParam, operatorString, secondParam);
                }

            }
            else
                n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "%s", firstParam);
        }
        else
        {
            switch(op - pr_opcodes)
            {
                case OP_NOT_ENT:
                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "(!%s)",firstParam);
                    break;
                case OP_NOT_V:
                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "isZeroVector(%s)",firstParam);
                    break;
                case OP_NOT_S:
                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "isEmptyString(%s)",firstParam);
                    break;
                default:
                    n = snprintf(intermediateParam, MAX_TEMP_EXPRESSION_TYPE, "%s%s", operatorString, firstParam);
            }
        }
        //
        //
        char *finalString = calloc(n + 1, 1);
        //
        strncpy(finalString, intermediateParam, n + 1);
        return finalString;
}
/*
============
PR_Statement

Emits a primitive statement, returning the var it places it's value in
============
*/
def_t *PR_Statement ( opcode_t *op, def_t *var_a, def_t *var_b)
{
  	dstatement_t	*statement;
	def_t			*var_c;

	statement = &statements[numstatements];
	numstatements++;

	statement_linenums[statement-statements] = pr_source_line;
	statement->op = op - pr_opcodes;
	statement->a = var_a ? var_a->ofs : 0;
	statement->b = var_b ? var_b->ofs : 0;
//
	if (op->type_c == &def_void || op->right_associative)
	{

        char *newExpression = calloc(1, MAX_TEMP_EXPRESSION_TYPE);
	    if (op->type_c != &def_void)
        {

            if (var_b->expression != NULL)
            {
                char varAString[MAX_TEMP_EXPRESSION_TYPE] = {0};
                char varBString[MAX_TEMP_EXPRESSION_TYPE] = {0};
                printVariable(var_a, varAString);
                printVariable(var_b, varBString);
                if (op - pr_opcodes == OP_STOREP_FNC)
                {
                    // check if previous statement was an indirection:
                    if (statements[numstatements-2].op == OP_LOAD_FNC)
                    {  //method = method, i.e. already number
                        #if GETTER_FUNCTIONS
                            snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, var_b->setterExpressionFormat, varAString);
                        #else
                            snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, "%s = %s", varBString, varAString);
                        #endif
                    }
                    else
                    {  // method = function, need to convert function name to index.
                        if (var_a->isRealFunction && var_a->type->type == ev_function)
                        {
                            #if GETTER_FUNCTIONS
                                char getFunctionIndexStr[MAX_TEMP_EXPRESSION_TYPE] = {0};
                                snprintf(getFunctionIndexStr, MAX_TEMP_EXPRESSION_TYPE, "getFunctionIndex(%s)", varAString);
                                snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, var_b->setterExpressionFormat, getFunctionIndexStr);
                            #else
                                snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, "%s = getFunctionIndex(%s)", varBString, varAString );
                                var_a->functionIndexUsed = true;
                            #endif
                        }
                        else
                        {
                            #if GETTER_FUNCTIONS
                            snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, var_b->setterExpressionFormat, varAString);
                            #else
                                snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, "%s = %s", varBString, varAString );
                            #endif
                        }
                        // We used a function index. Let's check if it was defined before otherwise declare
                        var_a->functionIndexUsed = 1;
                    }
                }
                else
                {
                    #if GETTER_FUNCTIONS
                        if (var_b->type->type == ev_pointer && (op->name[0] == '='))
                            snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, var_b->setterExpressionFormat, varAString);
                        else
                            snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, "%s %s %s", varBString, op->name, varAString);

                    #else
                        snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE, "%s %s %s", varBString, op->name, varAString);

                    #endif // GETTER_FUNCTIONS
                }

            }
            else
            {
                char varAString[MAX_TEMP_EXPRESSION_TYPE] = {0};
                printVariable(var_a, varAString);
                snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE,  "%s", var_a->expression);
            }
//            free(var_a->expression);
//            var_a->expression = newExpression;
        }
		var_c = NULL;
		statement->c = 0;			// ifs, gotos, and assignments
									// don't need vars allocated
        if (op->right_associative && !g_compile_progs_dat)  // next-hack added: probably not good this.
        {
            var_c = malloc (sizeof(def_t));
            memset (var_c, 0, sizeof(def_t));

            var_c->type = var_a->type;

            var_c->expression = newExpression;
            //
            //var_c->ofs = numpr_globals;   // is this required?
            //statement->c = numpr_globals;
            //numpr_globals += type_size[var_a->type->type];
            return var_c;
        }
	}
	else
	{	// allocate result space
	    char setterString[MAX_TEMP_EXPRESSION_TYPE] = {0};
        char *finalString = generateSubExpressionString(op, var_a, var_b, setterString);
		int n = strlen(setterString);
		char *finalSetterString = calloc(n + 1, 1);
		strcpy(finalSetterString, setterString);
		var_c = malloc (sizeof(def_t));
		memset (var_c, 0, sizeof(def_t));
		var_c->ofs = numpr_globals;
		var_c->type = op->type_c->type;
		var_c->expression = finalString;
		var_c->setterExpressionFormat = finalSetterString;
        //
		statement->c = numpr_globals;
		numpr_globals += type_size[op->type_c->type->type];
	}

	if (op->right_associative)
    {
		return var_a;
    }
	return var_c;
}

/*
============
PR_ParseImmediate

Looks for a preexisting constant
============
*/
def_t	*PR_ParseImmediate (void)
{
	def_t	*cn;

	if (g_compile_progs_dat || pr_immediate_type == &type_string)  // next-hack. This prevents from generating code with wierd constant values.
    {
    // check for a constant with the same value
        for (cn=pr.def_head.next ; cn ; cn=cn->next)
        {
            if (!cn->initialized)
                continue;
            if (cn->type != pr_immediate_type)
                continue;
            if (pr_immediate_type == &type_string)
            {
                if (!strcmp(G_STRING(cn->ofs), pr_immediate_string) )
                {
                    PR_Lex ();
                    return cn;
                }
            }
            else if (pr_immediate_type == &type_float)
            {
                if ( G_FLOAT(cn->ofs) == pr_immediate._float )
                {
                    PR_Lex ();
                    return cn;
                }
            }
            else if	(pr_immediate_type == &type_vector)
            {
                if ( ( G_FLOAT(cn->ofs) == pr_immediate.vector[0] )
                && ( G_FLOAT(cn->ofs+1) == pr_immediate.vector[1] )
                && ( G_FLOAT(cn->ofs+2) == pr_immediate.vector[2] ) )
                {
                    PR_Lex ();
                    return cn;
                }
            }
            else
                PR_ParseError ("weird immediate type");
        }
    }
// allocate a new one
	cn = malloc (sizeof(def_t));
	cn->next = NULL;
	pr.def_tail->next = cn;
	pr.def_tail = cn;
	cn->type = pr_immediate_type;
	cn->name = "IMMEDIATE";
	cn->initialized = 1;
	cn->scope = NULL;		// always share immediates

// copy the immediate to the global area
	cn->ofs = numpr_globals;
	pr_global_defs[cn->ofs] = cn;
	numpr_globals += type_size[pr_immediate_type->type];
	if (pr_immediate_type == &type_string)
    {
		pr_immediate.string = CopyString (pr_immediate_string);
    }

	memcpy (pr_globals + cn->ofs, &pr_immediate, 4*type_size[pr_immediate_type->type]);
    cn->expression = calloc(MAX_TEMP_EXPRESSION_TYPE, 1);
	PR_Lex ();
    if (pr_immediate_type == &type_float)
    {
        snprintf(cn->expression, MAX_TEMP_EXPRESSION_TYPE, "%#gf", pr_immediate._float);
    }
    else if (pr_immediate_type == &type_string)
    {
        char symbolized[MAX_TEMP_EXPRESSION_TYPE];
        symbolizeString(symbolized, pr_immediate_string);
        snprintf(cn->expression, MAX_TEMP_EXPRESSION_TYPE, "%s", symbolized);
        //snprintf(cn->expression, MAX_TEMP_EXPRESSION_TYPE, "\"%s\"", pr_immediate_string);
    }
    else if (pr_immediate_type == &type_vector)
    {
        snprintf(cn->expression, MAX_TEMP_EXPRESSION_TYPE, "(vector) {{%#gf, %#gf, %#gf}}", pr_immediate.vector[0], pr_immediate.vector[1], pr_immediate.vector[2]);
    }
    else
        FIXME("");
	return cn;
}


void PrecacheSound (def_t *e, int ch)
{
	char	*n;
	int		i;

	if (!e->ofs)
		return;
	n = G_STRING(e->ofs);
	for (i=0 ; i<numsounds ; i++)
		if (!strcmp(n, precache_sounds[i]))
			return;
	if (numsounds == MAX_SOUNDS)
		Error ("PrecacheSound: numsounds == MAX_SOUNDS");
	strcpy (precache_sounds[i], n);
	if (ch >= '1'  && ch <= '9')
		precache_sounds_block[i] = ch - '0';
	else
		precache_sounds_block[i] = 1;
	numsounds++;
}

void PrecacheModel (def_t *e, int ch)
{
	char	*n;
	int		i;

	if (!e->ofs)
		return;
	n = G_STRING(e->ofs);
	for (i=0 ; i<nummodels ; i++)
		if (!strcmp(n, precache_models[i]))
			return;
	if (numsounds == MAX_SOUNDS)
		Error ("PrecacheModels: numsounds == MAX_SOUNDS");
	strcpy (precache_models[i], n);
	if (ch >= '1'  && ch <= '9')
		precache_models_block[i] = ch - '0';
	else
		precache_models_block[i] = 1;
	nummodels++;
}

void PrecacheFile (def_t *e, int ch)
{
	char	*n;
	int		i;

	if (!e->ofs)
		return;
	n = G_STRING(e->ofs);
	for (i=0 ; i<numfiles ; i++)
		if (!strcmp(n, precache_files[i]))
			return;
	if (numfiles == MAX_FILES)
		Error ("PrecacheFile: numfiles == MAX_FILES");
	strcpy (precache_files[i], n);
	if (ch >= '1'  && ch <= '9')
		precache_files_block[i] = ch - '0';
	else
		precache_files_block[i] = 1;
	numfiles++;
}

/*
============
PR_ParseFunctionCall
============
*/
def_t *PR_ParseFunctionCall (def_t *func)
{
    static int call = 0;
    call++;
    if (call > 1)
    {
        // FIXME: is this fixed ?
//        FIXME("QuakeC: >>>>>>>>>>>>>>>>>> function cannot have expressions with functions!");
    }
	def_t		*e;
	int			arg;
	type_t		*t;

	t = func->type;
	if (t->type != ev_function)
		PR_ParseError ("not a function");
    def_t *def_return = calloc(1, sizeof(def_t));
    if (g_compile_progs_dat)
    {
        def_return = &def_ret;
    }
    else
        def_return->expression = calloc(MAX_TEMP_EXPRESSION_TYPE, 1);
    //
    //#warning we need to understand if this is a call to a function.
    if (!func->isRealFunction)
    {
        char castString[MAX_TEMP_EXPRESSION_TYPE];
        snprintf(castString, MAX_TEMP_EXPRESSION_TYPE, "%s (*)(", paramsString[func->type->aux_type->type]);
        for (int i = 0; i < func->type->num_parms; i++)
        {
            if (i > 0)
            {
                strcat(castString, ",");
            }
            strcat(castString, paramsString[func->type->parm_types[i]->type]);
        }
        strcat(castString, ")");
        snprintf(def_return->expression, MAX_TEMP_EXPRESSION_TYPE, "((%s )getFunction(%s))(", castString, func->expression );

    }
    else
    {

    	snprintf(def_return->expression, MAX_TEMP_EXPRESSION_TYPE, "%s(", func->expression );

    }
    // copy the arguments to the global parameter variables
	arg = 0;
	if (!PR_Check(")"))
	{
        int checkComma = 0;
		do
		{
			if (t->num_parms != -1 && arg >= t->num_parms)
				PR_ParseError ("too many parameters");
			e = PR_Expression (TOP_PRIORITY);

			if (arg == 0 && func->name)
			{
			// save information for model and sound caching
				if (!strncmp(func->name,"precache_sound", 14))
					PrecacheSound (e, func->name[14]);
				else if (!strncmp(func->name,"precache_model", 14))
					PrecacheModel (e, func->name[14]);
				else if (!strncmp(func->name,"precache_file", 13))
					PrecacheFile (e, func->name[13]);
			}

			if (t->num_parms != -1 && ( e->type != t->parm_types[arg] ) )
				PR_ParseError ("type mismatch on parm %i", arg);
		// a vector copy will copy everything
			def_parms[arg].type = t->parm_types[arg];
            PR_Statement (&pr_opcodes[OP_STORE_V], e, &def_parms[arg]);
            if (!e->isRealFunction || e->type->type != ev_function)
            {
                if (t->parm_types[arg]->aux_type && t->parm_types[arg]->aux_type->type == ev_string && t->parm_types[arg]->type == ev_field)
                {   // case when we want to put the field name for instance in find function.
                    char symbolized[MAX_TEMP_EXPRESSION_TYPE];
                    //symbolizeString(symbolized,  e->expression);
                    sprintf(symbolized, "offsetof (big_entvars_t, %s)", e->expression);
                    strcat(def_return->expression, symbolized);
                }
                else
                {
                    strcat(def_return->expression, e->expression);
                }
            }
            else
            {
              strcat(def_return->expression, "getFunctionIndex (");
              strcat(def_return->expression,e->expression);
              strcat(def_return->expression, ")");
              e->functionIndexUsed = true;
            }
			arg++;
            checkComma = PR_Check (",");
			if (checkComma)
            {
                strcat(def_return->expression, ", ");
            }
		} while (checkComma);

		if (t->num_parms != -1 && arg != t->num_parms)
			PR_ParseError ("too few parameters");
		PR_Expect (")");
	}
    strcat(def_return->expression, ")");
	if (arg >8)
		PR_ParseError ("More than eight parameters");


	PR_Statement (&pr_opcodes[OP_CALL0+arg], func, 0);

	def_return->type = t->aux_type;
	call--;
	return def_return;
}

/*
============
PR_ParseValue

Returns the global ofs for the current token
============
*/
def_t	*PR_ParseValue (void)
{
	def_t		*d;
	char		*name;

// if the token is an immediate, allocate a constant for it
	if (pr_token_type == tt_immediate)
    {
		return PR_ParseImmediate ();
    }

	name = PR_ParseName ();
// look through the defs
	d = PR_GetDef (NULL, name, pr_scope, false);
	if (!d)
		PR_ParseError ("Unknown value \"%s\"", name);
	return d;
}


/*
============
PR_Term
============
*/
def_t *PR_Term (void)
{
	def_t	*e, *e2;
	etype_t	t;

	if (PR_Check ("!"))
	{
		e = PR_Expression (NOT_PRIORITY);
		t = e->type->type;
		if (t == ev_float)
			e2 = PR_Statement (&pr_opcodes[OP_NOT_F], e, 0);
		else if (t == ev_string)
			e2 = PR_Statement (&pr_opcodes[OP_NOT_S], e, 0);
		else if (t == ev_entity)
			e2 = PR_Statement (&pr_opcodes[OP_NOT_ENT], e, 0);
		else if (t == ev_vector)
			e2 = PR_Statement (&pr_opcodes[OP_NOT_V], e, 0);
		else if (t == ev_function)
			e2 = PR_Statement (&pr_opcodes[OP_NOT_FNC], e, 0);
		else
		{
			e2 = NULL;		// shut up compiler warning;
			PR_ParseError ("type mismatch for !");
		}
		return e2;
	}

	if (PR_Check ("("))
	{
		e = PR_Expression (TOP_PRIORITY);
		char *newExpression = calloc(MAX_TEMP_EXPRESSION_TYPE, 1);
		snprintf(newExpression, MAX_TEMP_EXPRESSION_TYPE,"( %s )",e->expression);
		free(e->expression);
		e->expression = newExpression;
		PR_Expect (")");
		return e;
	}

	return PR_ParseValue ();
}

/*
==============
PR_Expression
==============
*/

def_t *PR_Expression (int priority)
{
	opcode_t	*op, *oldop;
	def_t		*e, *e2;
	etype_t		type_a, type_b, type_c;

	if (priority == 0)
		return PR_Term ();

	e = PR_Expression (priority-1);

	while (1)
	{
		if (priority == 1 && PR_Check ("(") )
        {
			return PR_ParseFunctionCall (e);
        }

		for (op=pr_opcodes ; op->name ; op++)
		{
			if (op->priority != priority)
				continue;
			if (!PR_Check (op->name))
				continue;
			if ( op->right_associative )
			{
			// if last statement is an indirect, change it to an address of
				if ( (unsigned)(statements[numstatements-1].op - OP_LOAD_F) < 6 )
				{
					statements[numstatements-1].op = OP_ADDRESS;
					def_pointer.type->aux_type = e->type;
					e->type = def_pointer.type;
				}
				e2 = PR_Expression (priority);
			}
			else
				e2 = PR_Expression (priority-1);

		// type check
			type_a = e->type->type;
			type_b = e2->type->type;

			if (op->name[0] == '.')// field access gets type from field
			{
				if (e2->type->aux_type)
					type_c = e2->type->aux_type->type;
				else
					type_c = -1;	// not a field
			}
			else
				type_c = ev_void;

			oldop = op;
			while (type_a != op->type_a->type->type
			|| type_b != op->type_b->type->type
			|| (type_c != ev_void && type_c != op->type_c->type->type) )
			{
				op++;
				if (!op->name || strcmp (op->name , oldop->name))
					PR_ParseError ("type mismatch for %s", oldop->name);
			}

			if (type_a == ev_pointer && type_b != e->type->aux_type->type)
				PR_ParseError ("type mismatch for %s", op->name);

			if (op->right_associative)
				e = PR_Statement (op, e2, e);
			else
				e = PR_Statement (op, e, e2);

			if (type_c != ev_void)	// field access gets type from field
				e->type = e2->type->aux_type;

			break;
		}
		if (!op->name)
			break;	// next token isn't at this priority level
	}

	return e;
}


/*
============
PR_ParseStatement

============
*/
void PR_ParseStatement (void)
{
	def_t				*e;
	dstatement_t		*patch1, *patch2;

	if (PR_Check ("{"))
	{
	    tablevel--;
        qc_printf(TABMOD, TABSPACE);
        if (tablevel < 0)
		{
		    tablevel = 0;
		}

	    qc_printf("{\r\n");
	    tablevel++;
		do
		{
			PR_ParseStatement ();
		} while (!PR_Check ("}"));
		tablevel--;
		if (tablevel < 0)
		{
		    tablevel = 0;
		}
        qc_printf(TABMOD, TABSPACE);
		qc_printf("}\r\n");
		return;
	}

	if (PR_Check("return"))
	{
		if (PR_Check (";"))
		{
		    //
			PR_Statement (&pr_opcodes[OP_RETURN], 0, 0);
            qc_printf(TABMOD, TABSPACE);
		    qc_printf("return;\r\n");
			return;
		}
		e = PR_Expression (TOP_PRIORITY);
		//

		PR_Expect (";");
		PR_Statement (&pr_opcodes[OP_RETURN], e, 0);
        qc_printf(TABMOD, TABSPACE);
		qc_printf("return %s;\r\n", e->expression);
		return;
	}

	if (PR_Check("while"))
	{
		PR_Expect ("(");
		int tmpLevel = tablevel;
        qc_printf(TABMOD, TABSPACE);
		qc_printf("while (");
		patch2 = &statements[numstatements];
		e = PR_Expression (TOP_PRIORITY);
		//
		qc_printf("%s)\r\n",   e->expression);
		tablevel ++;
		PR_Expect (")");
		patch1 = &statements[numstatements];
		PR_Statement (&pr_opcodes[OP_IFNOT], e, 0);
		PR_ParseStatement ();
		tablevel = tmpLevel;
		junkdef.ofs = patch2 - &statements[numstatements];
		PR_Statement (&pr_opcodes[OP_GOTO], &junkdef, 0);
		patch1->b = &statements[numstatements] - patch1;
		return;
	}

	if (PR_Check("do"))
	{
        qc_printf(TABMOD, TABSPACE);
	    qc_printf("do\r\n");
	    int tmpLevel = tablevel;
	    tablevel++;
		patch1 = &statements[numstatements];
		PR_ParseStatement ();
		PR_Expect ("while");
		PR_Expect ("(");
		tablevel = tmpLevel;
        qc_printf(TABMOD, TABSPACE);
		qc_printf("while(");
		e = PR_Expression (TOP_PRIORITY);
		qc_printf("%s);\r\n", e->expression);
		PR_Expect (")");
		PR_Expect (";");
		junkdef.ofs = patch1 - &statements[numstatements];
		PR_Statement (&pr_opcodes[OP_IF], e, &junkdef);
		return;
	}

	if (PR_Check("local"))
	{
		PR_ParseDefs ();
		locals_end = numpr_globals;
		return;
	}

	if (PR_Check("if"))
	{
	    int tmpLevel = tablevel;
		PR_Expect ("(");
		e = PR_Expression (TOP_PRIORITY);
		PR_Expect (")");
        qc_printf(TABMOD, TABSPACE);
        qc_printf("if (%s)\r\n", e->expression);
        tablevel++;
		patch1 = &statements[numstatements];
		PR_Statement (&pr_opcodes[OP_IFNOT], e, 0);

		PR_ParseStatement ();
        tablevel = tmpLevel;
		if (PR_Check ("else"))
		{
            qc_printf(TABMOD, TABSPACE);
		    qc_printf("else\r\n");
		    tablevel++;
			patch2 = &statements[numstatements];
			PR_Statement (&pr_opcodes[OP_GOTO], 0, 0);
			patch1->b = &statements[numstatements] - patch1;
			PR_ParseStatement ();
			patch2->a = &statements[numstatements] - patch2;
            tablevel = tmpLevel;
		}
		else
			patch1->b = &statements[numstatements] - patch1;

		return;
	}

	e = PR_Expression (TOP_PRIORITY);
	if (e->expression)
    {
        qc_printf(TABMOD, TABSPACE);
	    qc_printf("%s", e->expression);
    }
    else
        FIXME("NO EXPRESSION");
	PR_Expect (";");
	qc_printf(";\r\n");
}


/*
==============
PR_ParseState

States are special functions made for convenience.  They automatically
set frame, nextthink (implicitly), and think (allowing forward definitions).

// void() name = [framenum, nextthink] {code}
// expands to:
// function void name ()
// {
//		self.frame=framenum;
//		self.nextthink = time + 0.1;
//		self.think = nextthink
//		<code>
// };
==============
*/
void PR_ParseState (void)
{
	char	*name;
	def_t	*s1, *def;
	if (pr_token_type != tt_immediate || pr_immediate_type != &type_float)
		PR_ParseError ("state frame must be a number");
	s1 = PR_ParseImmediate ();

	PR_Expect (",");

	name = PR_ParseName ();
	def = PR_GetDef (&type_function, name,0, true);

	PR_Expect ("]");
    // next-hack
    #if GETTER_FUNCTIONS
        #if NO_GLOBAL_IN_STRUCT
            snprintf(functionStatePreamble, sizeof(functionStatePreamble), "set_qcc_frame(PROG_TO_EDICT(qcc_self), %g); set_qcc_nextthink(PROG_TO_EDICT(qcc_self), qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT(qcc_self), getFunctionIndex(%s));\r\n", G_FLOAT(s1->ofs), def->expression);
        #else
            snprintf(functionStatePreamble, sizeof(functionStatePreamble), "set_qcc_frame(PROG_TO_EDICT("GLOBAL_STRUCT_NAME".qcc_self), %g); set_qcc_nextthink(PROG_TO_EDICT("GLOBAL_STRUCT_NAME".qcc_self), "GLOBAL_STRUCT_NAME".qcc_time + 0.1f); set_qcc_think(PROG_TO_EDICT("GLOBAL_STRUCT_NAME
        ".qcc_self), getFunctionIndex(%s));\r\n", G_FLOAT(s1->ofs), def->expression);
        #endif
    #else
    #if NO_GLOBAL_IN_STRUCT
        snprintf(functionStatePreamble, sizeof(functionStatePreamble), "PROG_TO_EDICT(qcc_self)->v.qcc_frame = %g; PROG_TO_EDICT(qcc_self)->v.qcc_nextthink = qcc_time + 0.1f; PROG_TO_EDICT(qcc_self)->v.qcc_think = getFunctionIndex(%s);\r\n", G_FLOAT(s1->ofs), def->expression);
    #else
        snprintf(functionStatePreamble, sizeof(functionStatePreamble), "PROG_TO_EDICT("GLOBAL_STRUCT_NAME".qcc_self)->v.qcc_frame = %g; PROG_TO_EDICT("GLOBAL_STRUCT_NAME".qcc_self)->v.qcc_nextthink = "
                 GLOBAL_STRUCT_NAME".qcc_time + 0.1f; PROG_TO_EDICT("GLOBAL_STRUCT_NAME".qcc_self)->v.qcc_think = getFunctionIndex(%s);\r\n", G_FLOAT(s1->ofs), def->expression);

    #endif
    #endif // GETTER_FUNCTIONS
    def->functionIndexUsed = true;
    //
	PR_Statement (&pr_opcodes[OP_STATE], s1, def);
}

/*
============
PR_ParseImmediateStatements

Parse a function body
============
*/
function_t *PR_ParseImmediateStatements (type_t *type)
{
	int			i;
	function_t	*f;
	def_t		*defs[MAX_PARMS];

	f = malloc (sizeof(function_t));

//
// check for builtin function definition #1, #2, etc
//
	if (PR_Check ("#"))
	{
		if (pr_token_type != tt_immediate
		|| pr_immediate_type != &type_float
		|| pr_immediate._float != (int)pr_immediate._float)
			PR_ParseError ("Bad builtin immediate");
		f->builtin = (int)pr_immediate._float;
		PR_Lex ();
		return f;
	}

	f->builtin = 0;
//
// define the parms
//
	for (i=0 ; i<type->num_parms ; i++)
	{
		defs[i] = PR_GetDef (type->parm_types[i], pr_parm_names[i], pr_scope, true);
		if (i >= 1)
		    qc_printf(", ");
        char paramTypeName[MAX_TEMP_EXPRESSION_TYPE] = {0};
        getParamTypeName(paramTypeName, type->parm_types[i], defs[i]->expression, 0);
		qc_printf("%s", paramTypeName );
		f->parm_ofs[i] = defs[i]->ofs;
		if (i > 0 && f->parm_ofs[i] < f->parm_ofs[i-1])
			Error ("bad parm order");
	}
	if (type->num_parms == 0)
    {
        qc_printf("void");
    }
    else if (type->num_parms == -1)
    {
        qc_printf("...");
    }
	qc_printf(")\r\n{\r\n");
	f->code = numstatements;

//
// check for a state opcode
//
	if (PR_Check ("["))
    {
		PR_ParseState ();
        qc_printf("%*s%s", (tablevel*tabspace),"", functionStatePreamble);
        functionStatePreamble[0] = 0;
    }

//
// parse regular statements
//
	PR_Expect ("{");

	while (!PR_Check("}"))
		PR_ParseStatement ();

// emit an end of statements opcode
	PR_Statement (pr_opcodes, 0,0);


	return f;
}

/*
============
PR_GetDef

If type is NULL, it will match any type
If allocate is true, a new def will be allocated if it can't be found
============
*/
def_t *PR_GetDef (type_t *type, char *name, def_t *scope, boolean allocate)
{
	def_t		*def;
	char element[MAX_NAME];

// see if the name is already in use
	for (def = pr.def_head.next ; def ; def = def->next)
		if (!strcmp(def->name,name) )
		{
			if ( def->scope && def->scope != scope)
				continue;		// in a different function

			if (type && def->type != type)
				PR_ParseError ("Type mismatch on redeclaration of %s. Was %s (%p), is %s (%p).",name, paramsString[def->type->type], def->type, paramsString[type->type], type, &type_function);
			return def;
		}

	if (!allocate)
		return NULL;

// allocate a new def
	def = malloc (sizeof(def_t));
	memset (def, 0, sizeof(*def));
	def->next = NULL;
	pr.def_tail->next = def;
	pr.def_tail = def;

    //
	def->name = calloc (strlen(name)+1, 1);
	def->expression = calloc (strlen(name)+1, 1);
	strcpy (def->name, name);
	strcpy (def->expression, name);
	def->type = type;
	def->scope = scope;

	def->ofs = numpr_globals;
	pr_global_defs[numpr_globals] = def;

//
// make automatic defs for the vectors elements
// .origin can be accessed as .origin_x, .origin_y, and .origin_z
//
	if (type->type == ev_vector)
	{
	    #if NO_GLOBAL_IN_STRUCT
		sprintf (element, "%s_x",name);
		PR_GetDef (&type_float, element, scope, true);

		sprintf (element, "%s_y",name);
		PR_GetDef (&type_float, element, scope, true);

		sprintf (element, "%s_z",name);
		PR_GetDef (&type_float, element, scope, true);
		#else
            if (scope)
            {
                sprintf (element, "%s_x",name);
                PR_GetDef (&type_float, element, scope, true);

                sprintf (element, "%s_y",name);
                PR_GetDef (&type_float, element, scope, true);

                sprintf (element, "%s_z",name);
                PR_GetDef (&type_float, element, scope, true);
            }
            else
            {
                char string[MAX_TEMP_EXPRESSION_TYPE];
                char *formats[] = {"%s_x", "%s_y", "%s_z"};
                for (int i = 0; i < 3; i++)
                {
                    sprintf (element, formats[i], name);
                    def_t *td;
                    td = PR_GetDef (&type_float, element, scope, true);
                    sprintf(string, "%s.%s", GLOBAL_STRUCT_NAME, td->expression);
                    free(td->expression);
                    td->expression = malloc(strlen(string) + 1);
                    strcpy(td->expression, string);
                    printf("New expression %s\r\n", td->expression);
                }
            }
		#endif
	}
	else
		numpr_globals += type_size[type->type];

	if (type->type == ev_field)
	{
		*(int *)&pr_globals[def->ofs] = pr.size_fields;

		if (type->aux_type->type == ev_vector)
		{
			sprintf (element, "%s_x",name);
			PR_GetDef (&type_floatfield, element, scope, true);

			sprintf (element, "%s_y",name);
			PR_GetDef (&type_floatfield, element, scope, true);

			sprintf (element, "%s_z",name);
			PR_GetDef (&type_floatfield, element, scope, true);
		}
		else
			pr.size_fields += type_size[type->aux_type->type];
	}

//	if (pr_dumpasm)
//		PR_PrintOfs (def->ofs);

	return def;
}
void setShowInConsole(int show)
{
    g_showInConsole = 1;
}
char * getParamTypeName(char * buffer, type_t *type, char *nameParam, int expandFunction)
{
    if (type->type == ev_function && expandFunction)
    {

        snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%s (*%s) (",paramsString[type->aux_type->type], nameParam);

        for (int i = 0; i < type->num_parms; i++)
        {
            if (i > 0)
                strcat(buffer, ", ");
            strcat(buffer , paramsString[type->parm_types[i]->type]);
        }
        strcat (buffer, ")");
    }
    else
    {
         snprintf(buffer, MAX_TEMP_EXPRESSION_TYPE, "%s %s", paramsString[type->type], nameParam);
    }
    return buffer;
}
/*
================
PR_ParseDefs

Called at the outer layer and when a local statement is hit
================
*/

void PR_ParseDefs (void)
{
	char		*name;
	type_t		*type;
	def_t		*def;
	function_t	*f = NULL;
	dfunction_t	*df;
	int			i;
	int			locals_start;
    int checkComma = 0;
	type = PR_ParseType ();
    int functionBodyDeclared = 0;
	if (pr_scope && (type->type == ev_field || type->type == ev_function) )
		PR_ParseError ("Fields and functions must be global");
	do
	{
		name = PR_ParseName ();
        if (!strcmp(name, "main") && !g_compile_progs_dat)
        {
            name = MAIN_FUNCTION_TRANSLATION;
        }
		def = PR_GetDef (type, name, pr_scope, true);
		int checkEqual = PR_Check ("=");
        if (type->type != ev_function && !checkEqual)
        {
            qc_printf(TABMOD, TABSPACE);
            if (type->type != ev_field)
            {
                if (!checkComma)
                {
                    if (pr_scope)
                       qc_printf("%s %s", paramsString[type->type], name);
                    else
                    {
                        #if NO_GLOBAL_IN_STRUCT
                           qc_printf("%s %s", paramsString[type->type], name);
                        #else
                        char string[MAX_TEMP_EXPRESSION_TYPE];
                        sprintf(string, "%s.%s", GLOBAL_STRUCT_NAME, name);
                        if (def->expression)
                            free(def->expression);
                        def->expression = malloc(strlen(string) + 1);
                        strcpy(def->expression, string);
                        name = def->expression;
                      // qc_printf("%s %s", paramsString[type->type], name);
                       #endif
                    }


                }
                else
                {
                    if (pr_scope)
                        qc_printf(" %s", name);
                    else
                    {
                        #define NO_GLOBAL_IN_STRUCT 0
                        #if NO_GLOBAL_IN_STRUCT
                           qc_printf(" %s", name);
                        #else
                        char string[MAX_TEMP_EXPRESSION_TYPE];
                        sprintf(string, "%s.%s", GLOBAL_STRUCT_NAME, name);
                        if (def->expression)
                            free(def->expression);
                        def->expression = malloc(strlen(string) + 1);
                        strcpy(def->expression, string);
                        name = def->expression;
                      // qc_printf("%s %s", paramsString[type->type], name);
                       #endif
                    }

                }
            }
        }
		if ( checkEqual )
		{
			if (def->initialized)
				PR_ParseError ("%s redeclared", name);

			if (type->type == ev_function)
			{
			    tablevel ++;
			    functionBodyDeclared = 1;
                //
                qc_printf("%s %s(", paramsString[type->aux_type->type], name);
                //
				locals_start = locals_end = numpr_globals;
				pr_scope = def;

				f = PR_ParseImmediateStatements (type);

				pr_scope = NULL;
				def->initialized = 1;
				G_FUNCTION(def->ofs) = numfunctions;
				f->def = def;
                f->def->isRealFunction = 1;

		// fill in the dfunction
				df = &functions[numfunctions];
				numfunctions++;
				if (f->builtin)
					df->first_statement = -f->builtin;
				else
					df->first_statement = f->code;
				df->s_name = CopyString (f->def->name);
				df->s_file = s_file;
				df->numparms =  f->def->type->num_parms;
				df->locals = locals_end - locals_start;
				df->parm_start = locals_start;

				for (i=0 ; i<df->numparms ; i++)
                {
					df->parm_size[i] = type_size[f->def->type->parm_types[i]->type];

                }

				continue;
			}
			else if (pr_immediate_type != type)
				PR_ParseError ("wrong immediate type for %s", name);
            if (type->type != ev_function)
            {
                if (!checkComma)
                {
                    qc_printf(TABMOD, TABSPACE);
                    //if (type->type != ev_string)    // special case for strings, which are always const char *
                    qc_printf("const %s %s", paramsString[type->type], name);
                    //else
                    //    qc_printf("%s%s", paramsString[type->type], name);

                }
                else
                {
                    qc_printf(TABMOD, TABSPACE);

                    qc_printf(" %s", name);
                }

                if (pr_immediate_type->type == ev_string)
                {
//                    qc_printf(" = \"%s\"",  pr_immediate_string);
                    char symbolized[MAX_TEMP_EXPRESSION_TYPE];
                    symbolizeString(symbolized, pr_immediate_string);
                    qc_printf(" = %s", symbolized);
                }
                else if (pr_immediate_type->type == ev_float)
                {
                    if (pr_immediate._float == (int)pr_immediate._float)
                        qc_printf(" = %d", (int) pr_immediate._float);
                    else
                        qc_printf(" = %#gf", (int) pr_immediate._float);
                }
                else if (pr_immediate_type->type == ev_vector)
                {
                    qc_printf(" = {{%#gf,%#gf, %#gf}}", pr_immediate.vector[0], pr_immediate.vector[1], pr_immediate.vector[2]);
                }
                else
                {
                    FIXME(" Something broken");
                }

            }
			def->initialized = 1;
            // copy the immediate to the global area
            if (pr_immediate_type == &type_string) // next-hack added this.
            {
                pr_immediate.string = CopyString (pr_immediate_string);
            }
			memcpy (pr_globals + def->ofs, &pr_immediate, 4*type_size[pr_immediate_type->type]);
			PR_Lex ();
		}
        checkComma = PR_Check (",");
        if (checkComma && type->type != ev_field && (pr_scope != NULL || NO_GLOBAL_IN_STRUCT))
            qc_printf(",");
	} while (checkComma);

	PR_Expect (";");
	if (type->type == ev_function &&  functionBodyDeclared /*def->initialized*/ && !f->builtin)
	{
	    tablevel = 0;
        qc_printf("}\r\n");
	}
	else if (type->type != ev_function && type->type != ev_field)
    {
        qc_printf(";\r\n");
    }
    else if (type->type == ev_function)
    {
        // it was a function declaration. Let's print it;
        if (!strcmp(def->name, "main"))
        {
            def->name = MAIN_FUNCTION_TRANSLATION;
        }
        def->isRealFunction = 1;
        if (!f || f->builtin == 0)
        {
            qc_printf("%s %s(",paramsString[def->type->aux_type->type] ,def->name);
        }
        tablevel = 0;
        for (int i = 0; i < type->num_parms; i++)
        {
            if (i > 0)
            {
                qc_printf(", ");
            }
            char paramTypeName[MAX_TEMP_EXPRESSION_TYPE] = {0};
            getParamTypeName(paramTypeName, type->parm_types[i], "", 0);
            qc_printf("%s", paramTypeName);
        }
        if (type->num_parms == 0)
        {
            qc_printf("void");
        }
        qc_printf(");\r\n");
    }
}

/*
============
PR_CompileFile

compiles the 0 terminated text, adding defintions to the pr structure
============
*/
boolean	PR_CompileFile (char *string, char *filename)
{
	if (!pr.memory)
		Error ("PR_CompileFile: Didn't clear");

	PR_ClearGrabMacros ();	// clear the frame macros

	pr_file_p = string;
	s_file = CopyString (filename);

	pr_source_line = 0;

	PR_NewLine ();

	PR_Lex ();	// read first token

	while (pr_token_type != tt_eof)
	{
		if (setjmp(pr_parse_abort))
		{
			if (++pr_error_count > MAX_ERRORS)
				return false;
			PR_SkipToSemicolon ();
			if (pr_token_type == tt_eof)
				return false;
		}

		pr_scope = NULL;	// outside all functions

		PR_ParseDefs ();
	}

	return (pr_error_count == 0);
}

