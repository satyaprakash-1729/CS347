/*! @file ccalc.h
 * @brief Include for all modules
 *********************************************************************
 * a simple calculator with variables
 * 
 * sample-files for a artikel in developerworks.ibm.com
 * Author: Christian Hagen, chagen@de.ibm.com
 * 
 * @par ccalc.h
 * includes, prototypes & types
 * 
 *********************************************************************
 */
#ifndef CCALC_H_
#define CCALC_H_

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdarg.h>
#include <float.h>
#include "type_all.h"
#include "parser.tab.h"

/*
 * global variables
 */
extern int debug;
FILE* outprod;
FILE* outerror;
FILE* codefile;
typer* root;
fte* functab_lookup(char*);
void print_code1(void);
void write_data_part(FILE*);
/*
 * lex & parse
 */
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char*);

/*
 * ccalc.c
 */
extern void DumpRow(void); 
extern int GetNextChar(char *b, int maxBuffer);
extern void BeginToken(char*);
extern void PrintError(const char *s, ...);
extern void width_init(typer* root);


#endif /*CCALC_H_*/
