/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    RETURN = 258,
    IDENT = 259,
    DOT = 260,
    NUM = 261,
    FLOAT = 262,
    CHAR = 263,
    LP = 264,
    RP = 265,
    PLUS = 266,
    MINUS = 267,
    ASSIGN = 268,
    DIV = 269,
    MULT = 270,
    IFLP = 271,
    THEN = 272,
    ELIF = 273,
    ELSE = 274,
    BEG = 275,
    END = 276,
    GT = 277,
    LT = 278,
    GTEQ = 279,
    LTEQ = 280,
    EQ = 281,
    NEQ = 282,
    FORLP = 283,
    WHILELP = 284,
    DO = 285,
    LSQ = 286,
    RSQ = 287,
    COMMA = 288,
    SEMICOLON = 289,
    COLON = 290,
    NAME = 291,
    PROCESSOR = 292,
    ISRUN = 293,
    SUBJOBS = 294,
    GETCLSP = 295,
    RUN = 296,
    DISCJOB = 297,
    ISA = 298,
    CLSP = 299,
    L1MEM = 300,
    ARCHTYPE = 301,
    L2MEM = 302,
    LINK = 303,
    STPNT = 304,
    ENDPNT = 305,
    BW = 306,
    CHCAP = 307,
    MEMORY = 308,
    GETAVMEM = 309,
    MEMTYPE = 310,
    MEMSIZE = 311,
    JOB = 312,
    GETMEM = 313,
    JOBID = 314,
    FLOPS = 315,
    DEADLINE = 316,
    MEMREQ = 317,
    AFFINITY = 318,
    CLUSTER = 319,
    PROCESSORS = 320,
    TOPO = 321,
    LINKBW = 322,
    LINKCAP = 323,
    INCR = 324,
    DCR = 325,
    ENDALL = 326,
    PROCESSORSLIST = 327,
    JOBS = 328,
    SCHALGO = 329,
    PRIOLIST = 330,
    FINDEADLINE = 331,
    LOADBALALGO = 332,
    SCHEDULER = 333,
    SCHEDULE = 334,
    INT_TYPE = 335,
    FLOAT_TYPE = 336,
    CHAR_TYPE = 337,
    IDENTARRAY = 338,
    IDENTLP = 339,
    VOID = 340
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 611 "parser.y" /* yacc.c:1909  */

       typer* type_all;

#line 144 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
