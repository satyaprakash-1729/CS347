/* A Bison parser, made by GNU Bison 3.0.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 2 "parser.y" /* yacc.c:339  */

// int yyerror(const char *);
int yylex(void);
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define ERROR_TYPE 6
#define SYMTAB_SIZE 50
#define TEMPTAB_SIZE 50
#define FUNCTAB_SIZE 50
#define MAXQUADS 200
#include <math.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "ccalc.h"

/////////// CODE GEN /////////////////////
char  *Names[] = { "_t0", "_t1", "_t2", "_t3", "_t4", "_t5", "_t6", "_t7", "_t8", "_t9", "_t10", "_t11", "_t12", "_t13", "_t14", "_t15", "_t16", "_t17", "_t18", "_t19", "_t20",  "_t21",  "_t22",  "_t23",  "_t24",  "_t25",  "_t26",  "_t27",  "_t28",  "_t29",  "_t30",  "_t31",  "_t32",  "_t33",  "_t34",  "_t35",  "_t36",  "_t37",  "_t38",  "_t39",  "_t40",  "_t41",  "_t42",  "_t43",  "_t44",  "_t45",  "_t46",  "_t47",  "_t48",  "_t49"};   
char  **Namep  = Names;   
   
char  *newname()   
{   
    if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )   
    {   
        printf(">>>>>>>>>>>>DHASDSAFJAFASFSAKFKASKFASKFKASKFASKK\n");
        exit( 1 );   
    }   
   
    return( *Namep++ );   
}   
   
void freename(char *s)      
{   
    if( Namep > Names )   
       *--Namep = s;   
}   

char* TAGARR[] = {"TAG0", "TAG1", "TAG2", "TAG3","TAG4","TAG5","TAG6","TAG7", "TAG8", "TAG9", "TAG10","TAG11","TAG12","TAG13"};
static int tagcntr = 0;


/////////////////////////////////

fte* active_func_ptr = NULL;
fte* call_name_ptr = NULL;
int scope = 0;
int nextquad = 0;
char* quads[MAXQUADS];

ste* symtab[SYMTAB_SIZE];
int symtab_num = 0;
fte* functab[FUNCTAB_SIZE];
int functab_num = 0;
tte* temptab[TEMPTAB_SIZE];
int temp_num = 0;
int tagtoaddquad[100];
char* tagtoaddlabel[100];
int numtags = 0;

extern FILE* outprod;
extern FILE* outerror;
extern FILE* codefile;
extern int yylineno;
extern typer* root;
extern fte* functab_lookup(char *);
extern void print_code1(void);
extern void write_data_part(FILE*);
nl* merge(nl* a, nl* b){
    nl* temp2 = a;
    while(temp2->next){
        temp2 = temp2->next;
    }
    temp2->next = b;
    return a;    
}

void write_data_part(FILE* codefile){
    for(int i=0; i<symtab_num; i++){
        ste* temp = symtab[i];
        if(temp->type_ident==0){
            if(temp->eletype==0){
                fprintf(codefile, "%s:  .word %d\n", temp->name, temp->num_init);
            }else if(temp->eletype==1){
                fprintf(codefile, "%s:  .double %.2f\n", temp->name, temp->decimal_init);
            }else if(temp->eletype==2){
                fprintf(codefile, "%s:  .byte '%c'\n", temp->name, temp->character_init);
            }
        }else{
            if(temp->eletype==0){
                fprintf(codefile, "%s:  .word ", temp->name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "%d, ", temp->arrayint_init[k]);
                    else
                        fprintf(codefile, "%d", temp->arrayint_init[k]);
                }
            }else if(temp->eletype==1){
                fprintf(codefile, "%s:  .double ", temp->name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "%.2f, ", temp->arraydouble_init[k]);
                    else
                        fprintf(codefile, "%.2f", temp->arraydouble_init[k]);
                }
            }else if(temp->eletype==2){
                fprintf(codefile, "%s:  .byte ", temp->name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "'%c', ", temp->arraychar_init[k]);
                    else
                        fprintf(codefile, "'%c'", temp->arraychar_init[k]);
                }
            }
            fprintf(codefile, "\n");
        }
    }
}
void write_data_part2(FILE* codefile){
    int numv = active_func_ptr->num_vars;
    lvl* list = active_func_ptr->local_var_list;
    lvl* temp = list;
    while(temp){
        if(temp->var_ident_type==0){
            if(temp->var_eletype==0){
                fprintf(codefile, "%s:  .word 0\n", temp->var_name);
            }else if(temp->var_eletype==1){
                fprintf(codefile, "%s:  .double 0.00\n", temp->var_name);
            }else if(temp->var_eletype==2){
                fprintf(codefile, "%s:  .byte ' '\n", temp->var_name);
            }
        }else{
            if(temp->var_eletype==0){
                fprintf(codefile, "%s:  .word ", temp->var_name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "0, ");
                    else
                        fprintf(codefile, "0");
                }
            }else if(temp->var_eletype==1){
                fprintf(codefile, "%s:  .double ", temp->var_name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "0.00, ");
                    else
                        fprintf(codefile, "0.00");
                }
            }else if(temp->var_eletype==2){
                fprintf(codefile, "%s:  .byte ", temp->var_name);
                for(int k=0; k<temp->dim; k++){
                    if(k<temp->dim-1)
                        fprintf(codefile, "' ', ");
                    else
                        fprintf(codefile, "' '");
                }
            }
            fprintf(codefile, "\n");
        }
        temp = temp->next;
    }
}

void tagadder(){
    for(int i=0; i<numtags; i++){
        // printf(">>>>>>>>>>>> %s  %d  %s\n", tagtoaddlabel[i], tagtoaddquad[i], quads[tagtoaddquad[i]]);

        char* temp1 = (char *)malloc(120*sizeof(char));
        memset(temp1, 0, 60);
        strcat(temp1, tagtoaddlabel[i]);
        strcat(temp1, ": \n");

        if(quads[tagtoaddquad[i]]){
            strcat(temp1, quads[tagtoaddquad[i]]);
            memset(quads[tagtoaddquad[i]], 0, strlen(quads[tagtoaddquad[i]]));
            strcpy(quads[tagtoaddquad[i]], temp1);
        }else{
            quads[tagtoaddquad[i]] = strdup(tagtoaddlabel[i]);
            strcat(quads[tagtoaddquad[i]], ":\n");
            nextquad++;
        }
    }
}

void backpatch(nl* list, char* label, int quad){
    nl* temp = list;
    int flag = 0;
    while(temp){
        // printf("KKKKKKKK  %d  %d  %s\n", temp->quad, quad, label);
        if(temp->quad!=-1){
            flag = 1;
            char* temp1 = (char *)malloc((strlen(quads[temp->quad])-1)*(sizeof(char)));
            strncpy(temp1, quads[temp->quad], strlen(quads[temp->quad])-1);
            strcat(temp1, label);
            strcat(temp1, "\n");
            memset(quads[temp->quad], 0 , strlen(quads[temp->quad]));
            strcpy(quads[temp->quad], temp1);
        }
        temp=temp->next;
    }
    if(flag){
        tagtoaddlabel[numtags++] = strdup(label);
        tagtoaddquad[numtags-1] = quad;
    }
}

void gen_code(char* quad){
    quads[nextquad++] = strdup(quad);
}

nl* makelist(int quad){
    nl* temp = (nl*)malloc(sizeof(nl));
    temp->quad = quad;
    temp->next = NULL;
    return temp;
}

tte* newtemp(int type){
    tte* tmp = (tte*)malloc(sizeof(tte));
    tmp->name = newname();
    tmp->type = type;
    temptab[temp_num++] = tmp;
    return tmp;
}

void print_code1 (){
    // printf(">>>>>>>>>WRITING\n");
    FILE* int_code_file = fopen("intcode", "w+");
    tagadder();
    fprintf(int_code_file, "\n------------------INTERMEDIATE CODE-----------------------------\n");
    for(int i=0; i<nextquad; i++){
        if(quads[i])
            fprintf(int_code_file, "%s", quads[i]);
    }
    fprintf(int_code_file, "\n----------------------------------------------------------------\n");
    fclose(int_code_file);
}

fte* functab_lookup(char* func_name){
    for(int i=0;i<functab_num;i++){
        if(strcmp(func_name, functab[i]->func_name)==0){
            return functab[i];
        }
    }
    return NULL;
}

prl* search_param(char* param_name){
    fte* func = active_func_ptr;
    prl* temp = func->param_list_ptr;
    while(temp){
        if(strcmp(param_name, temp->param_name)==0){
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int insert_functab(int result_type, char* func_name){
    if(functab_lookup(func_name)){
      return 0;
    }
    fte* temp = (fte*)malloc(sizeof(fte));
    temp->func_name = strdup(func_name);
    temp->res_type = result_type;
    temp->num_params = 0;
    temp->num_vars = 0;
    temp->param_list_ptr = NULL;
    temp->local_var_list = NULL;
    functab[functab_num++] = temp;
    return 1;
}

prl* create_param(int type, char* name){
    prl* temp = (prl *)malloc(sizeof(prl));
    temp->param_type = type;
    temp->param_name = strdup(name);
    temp->next = NULL;
    return temp;
}

lvl* create_lvl(int type, char* name, int ident_type, int dim){
    lvl* temp = (lvl *)malloc(sizeof(lvl));
    temp->var_eletype = type;
    temp->var_ident_type = ident_type;
    temp->dim = dim;
    temp->var_name = strdup(name);
    return temp;
}

int insert_param(fte* func, int type, char* param_name){
    if(func->param_list_ptr==NULL){
        func->param_list_ptr = create_param(type, param_name);
    }else{
        prl* temp = func->param_list_ptr;
        while(temp->next){
            if(strcmp(temp->param_name, param_name)==0){
                return 0;
            }
            temp = temp->next;
        }
        temp->next = create_param(type, param_name);
    }
    func->num_params++;
    return 1;
}

int insert_var(fte* func, int type, char* var_name, int type_ident, int dim){
    if(func->local_var_list==NULL){
        func->local_var_list = create_lvl(type, var_name, type_ident, dim);
    }else{
        lvl* temp = func->local_var_list;
        while(temp->next){
            if(strcmp(temp->var_name, var_name)==0){
                return 0;
            }
            temp = temp->next;
        }
        temp->next = create_lvl(type, var_name, type_ident, dim);
    }
    func->num_vars++;
    return 1;
}

void print_func_table(){
    printf("------------------------------------------------------------------------\n");
    for(int i=0; i<functab_num; i++){
        prl* temp = functab[i]->param_list_ptr;
        while(temp){
            printf("(%d %s)  ", temp->param_type, temp->param_name);
            temp = temp->next;
        }
        printf("%s >> %d   %d\n", functab[i]->func_name, functab[i]->res_type, functab[i]->num_params);
    }
    printf("------------------------------------------------------------------------\n");
}

ste* symtab_lookup(char* name, int level){
  for(int i=0;i<symtab_num;i++){
    if(symtab[i]->valid && strcmp(name, symtab[i]->name)==0 && symtab[i]->level == level){
      return symtab[i];
    }
  }
  return NULL;
}

ste* symtab_lookup_up(char* name, int level){
    int maxlevel = -1;
    ste* tmp = NULL;
  for(int i=0;i<symtab_num;i++){
    if(symtab[i]->valid && strcmp(name, symtab[i]->name)==0 && symtab[i]->level<=level){
        if(symtab[i]->level > maxlevel){
            tmp = symtab[i];
            maxlevel = symtab[i]->level;
        }
    }
  }
  return tmp;
}

void patchtype(char* namelist[], int namelistnum, int type){
  for(int i=0;i<namelistnum;i++){
    ste* nameptr = symtab_lookup(namelist[i], scope);
    if(!nameptr){
      continue;
    }
    nameptr->eletype = type;
    insert_var(active_func_ptr, type, namelist[i], nameptr->type_ident, nameptr->dim);
    if(nameptr->type_ident==1){
        if(type==0){
            nameptr->arrayint = (int*)malloc(nameptr->dim*sizeof(int));
            nameptr->arrayint_init = (int*)malloc(nameptr->dim*sizeof(int));
        }else if(type==1){
            nameptr->arraydouble = (double*)malloc(nameptr->dim*sizeof(double));
            nameptr->arraydouble_init = (double*)malloc(nameptr->dim*sizeof(double));
        }else if(type==2){
            nameptr->arraychar = (char*)malloc(nameptr->dim*sizeof(char));
            nameptr->arraychar_init = (char*)malloc(nameptr->dim*sizeof(char));
        }
    }
  }
}

int check_param_type(int type, int index){
    prl* prlptr = call_name_ptr->param_list_ptr;
    int k = 1;
    while(prlptr){
        if(k==index){
            if(prlptr->param_type==type){
                return 1;
            }
        }
        prlptr = prlptr->next;
        k++;
    }
    return 0;
}

void copy_namelist(typer* ret, typer* toadd){
  ret->namelistnum = toadd->namelistnum+1;
  for(int i=0;
i<toadd->namelistnum;
i++){
    ret->namelist[i] = strdup(toadd->namelist[i]);
  }
  return;
}

void copy_paramlist(typer* ret, typer* toadd){
    ret->paramlistnum = toadd->paramlistnum+1;
    for(int i=0;i<toadd->paramlistnum;i++){
        ret->paramlist[i] = toadd->paramlist[i];
    }
}

int insert_symtab(char* name,int type_ident,int eletype,int dim,int num, double decimal, char character, int level){
    if(symtab_lookup(name, level)){
      return 0;
    }
    ste* temp = (ste*)malloc(sizeof(ste));
    temp->name = strdup(name);
    temp->type_ident = type_ident;
    temp->valid = 1;
    if(temp->type_ident==1){
      temp->dim = dim;
    }else{
      temp->dim = 1;
    }
    temp->eletype = eletype;
    if(eletype == 0){
      temp->num = num;
      temp->num_init = num;
    }else if(eletype == 1){
      temp->decimal = decimal;
      temp->decimal_init = decimal;
    }else if(eletype == 2){
      temp->character = character;
      temp->character_init = character;
    }
    temp->arraychar = NULL;
    temp->arrayint = NULL;
    temp->arraydouble = NULL;
    temp->arraychar_init = NULL;
    temp->arrayint_init = NULL;
    temp->arraydouble_init = NULL;

    temp->level = level;
    for(int j=0; j<symtab_num; j++){
        if(!symtab[j]->valid){
            symtab[j] = temp;
            return 1;
        }
    }
    symtab[symtab_num++] = temp;
    return 1;
}


int coercible(int a, int b){
  if(((a==0 || a==1) && (b==0 || b==1)) || ((a==0 || a==2) && (b==0 || b==2))){
    return 1;
  }else{
    return 0;
  }
}

int compatible_arithop(int a, int b){
  // if(((a==1 && b==2) || (a==2 && b==1)) ){
  //   return 0;
  // }else{
    return 1;
  // }
}

void delete_var_level(int level){
    for(int i=0; i<symtab_num; i++){
        if(symtab[i]->level == level){
            symtab[i]->valid = 0;
        }
    }
}

void print_symbol_table(){
    printf("------------------------------------------------------------------------\n");
    for(int i=0; i<symtab_num; i++){
        if(symtab[i]->valid){
            printf("%s ", symtab[i]->name);
            printf("(%d)  >>  ", symtab[i]->level);
            if(symtab[i]->type_ident==0){
                if(symtab[i]->eletype==0){
                    printf("%d  ", symtab[i]->num);
                    printf("INIT(%d)\n", symtab[i]->num_init);
                }else if(symtab[i]->eletype==1){
                    printf("%.2f  ", symtab[i]->decimal);
                    printf("INIT(%.2f)\n", symtab[i]->decimal_init);
                }else if(symtab[i]->eletype==2){
                    printf("%c  ", symtab[i]->character);
                    printf("INIT(%c)\n", symtab[i]->character_init);
                }else{
                    printf("NAN\n");
                }
            }else{
                if(symtab[i]->eletype==0){
                    for(int j=0; j<symtab[i]->dim; j++){
                        printf("%d, ", symtab[i]->arrayint[j]);
                    }
                    printf("\n");
                }else if(symtab[i]->eletype==1){
                    for(int j=0; j<symtab[i]->dim; j++){
                        printf("%.2f, ", symtab[i]->arraydouble[j]);
                    }
                    printf("\n");
                }else if(symtab[i]->eletype==2){
                    for(int j=0; j<symtab[i]->dim; j++){
                        printf("%c, ", symtab[i]->arraychar[j]);
                    }
                    printf("\n");
                }else{
                    printf("NAN\n");
                }
            }
        }
    }
    printf("------------------------------------------------------------------------\n");
}

void* setter(typer* node){
    if(node->type==0){
        int* ret = (int*)malloc(sizeof(int));
        ret = &node->num;
        return ret;
    }else if(node->type==1){
        double* ret = (double*)malloc(sizeof(double));
        ret = &node->decimal;
        return ret;
    }else{
        char* ret = (char*)malloc(sizeof(char));
        ret = &node->character;
        return ret;
    }
}

int result_type(int a, int b){
  if(a==b){
    return a;
  }
  if((a==0 || a==1) && (b==0 || b==1))
    return a | b;
  else if((a==0 || a==2) && (b==0 || b==2)){
    return 0;
  }else{
    return ERROR_TYPE;
  }
}

// typedef  type_aller;

typer* create_node(int type, double decimal, int num_children, char* tag){
       typer* temp = (typer *)malloc(sizeof(typer));
       temp->type = type;
       temp->num = 0;
       temp->result = NULL;
       temp->next = NULL;
       temp->quad = 0;
       temp->label = NULL;
       temp->decimal = decimal;
       temp->character = ' ';
       temp->tag = tag;
       temp->namelistnum=0;
       temp->begin = 0;
       temp->paramlistnum=0;
       temp->falselist = NULL;
       temp->num_children=num_children;
       temp->name = NULL;
       temp->st_entry = NULL;
       if(temp->num_children==0){
              temp->nodetype = TERMINAL;
       }else{
              temp->nodetype = NONTERMINAL;
       }
       temp->lastwidth = temp->depth = 0;
       temp->subtree_width = temp->width = strlen(tag);
       temp->done =0;
       temp->done2 = 0;
       temp->sibling = temp->leftChild = temp->parent = NULL;
       for(int i=0;i<10;i++)
              temp->child_list[i] = NULL;
       return temp;
}
void error_caller(char* msg, char* arg){
    char* tmp = (char *)malloc(120*sizeof(char));
    strcat(tmp, msg);
    strcat(tmp, "'");
    strcat(tmp, arg);
    strcat(tmp, "'");
    yyerror(tmp);
}
void next_list_printer(nl* list){
    nl* temp = list;
    while(temp){
        if(temp->quad>=0)
            // printf(">>>>>>>>>  %s\n", quads[temp->quad]);
        temp = temp->next;
    }
}


#line 674 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
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
#line 611 "parser.y" /* yacc.c:355  */

       typer* type_all;

#line 804 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 819 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef __attribute__
/* This feature is available in gcc versions 2.5 and later.  */
# if (! defined __GNUC__ || __GNUC__ < 2 \
      || (__GNUC__ == 2 && __GNUC_MINOR__ < 5))
#  define __attribute__(Spec) /* empty */
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   389

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  86
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  94
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  187

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   340

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   710,   710,   720,   733,   742,   754,   766,   770,   779,
     802,   826,   836,   901,   949,  1064,  1070,  1075,  1081,  1099,
    1111,  1123,  1125,  1127,  1129,  1131,  1133,  1135,  1137,  1139,
    1145,  1165,  1172,  1185,  1186,  1190,  1207,  1221,  1237,  1245,
    1257,  1266,  1281,  1307,  1336,  1346,  1358,  1373,  1387,  1401,
    1416,  1846,  1939,  1945,  1951,  1957,  1963,  1969,  1979,  2066,
    2157,  2164,  2273,  2383,  2488,  2495,  2509,  2523,  2563,  2603,
    2643,  2685,  2699,  2713,  2726,  2753,  2767,  2781,  2803,  2816,
    2906,  2911,  2916,  2924,  2936,  2956,  2969,  2981,  3006,  3039,
    3043,  3064,  3074,  3086,  3111
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "RETURN", "IDENT", "DOT", "NUM", "FLOAT",
  "CHAR", "LP", "RP", "PLUS", "MINUS", "ASSIGN", "DIV", "MULT", "IFLP",
  "THEN", "ELIF", "ELSE", "BEG", "END", "GT", "LT", "GTEQ", "LTEQ", "EQ",
  "NEQ", "FORLP", "WHILELP", "DO", "LSQ", "RSQ", "COMMA", "SEMICOLON",
  "COLON", "NAME", "PROCESSOR", "ISRUN", "SUBJOBS", "GETCLSP", "RUN",
  "DISCJOB", "ISA", "CLSP", "L1MEM", "ARCHTYPE", "L2MEM", "LINK", "STPNT",
  "ENDPNT", "BW", "CHCAP", "MEMORY", "GETAVMEM", "MEMTYPE", "MEMSIZE",
  "JOB", "GETMEM", "JOBID", "FLOPS", "DEADLINE", "MEMREQ", "AFFINITY",
  "CLUSTER", "PROCESSORS", "TOPO", "LINKBW", "LINKCAP", "INCR", "DCR",
  "ENDALL", "PROCESSORSLIST", "JOBS", "SCHALGO", "PRIOLIST", "FINDEADLINE",
  "LOADBALALGO", "SCHEDULER", "SCHEDULE", "INT_TYPE", "FLOAT_TYPE",
  "CHAR_TYPE", "IDENTARRAY", "IDENTLP", "VOID", "$accept", "program_code",
  "external_declarations", "statements", "statement", "whileexp",
  "selection", "ifexp", "emptyN", "emptyM", "opt_block", "beforeend",
  "beforestats", "func_decl", "func_head", "decl_plist", "decl_pl",
  "decl_param", "expression", "expr_temp", "RA_TERM", "expression_prime",
  "term", "term_prime", "factor", "type", "ident-list", "function",
  "beforeargs", "argsAll", "argsnonempty", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340
};
# endif

#define YYPACT_NINF -80

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-80)))

#define YYTABLE_NINF -91

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -15,   -80,   -80,   -80,   -79,     3,   -80,   -80,    -9,     9,
     -47,   -80,   -80,   -80,   -80,    -7,   119,    18,   306,   -47,
      44,     8,   -11,   -80,    39,   -80,     2,    38,    -1,   -21,
     -80,   -80,   306,    58,   221,   203,   -80,    67,    70,   -80,
     306,   167,   -80,   -80,    65,   -80,    -9,   -80,    45,    33,
      75,    85,    12,    60,   306,   306,    32,   306,    64,   100,
      15,   -80,   -80,   -47,   -80,   -80,   -80,    79,    20,   237,
     -80,   -80,   -80,   -80,   106,   -80,   109,   120,   288,   247,
     306,   -80,   -80,   -80,   -80,    97,   122,   119,    -9,   114,
     -80,   -80,   -80,   -80,   -80,   -80,   -80,   306,   306,   306,
     -80,   306,   306,   -80,    48,   -80,   -80,   128,   108,   -80,
     110,   -80,   -80,   -80,   306,   -80,   -80,   111,     7,   115,
     112,   118,   -80,    -9,   -80,   117,   306,   121,   -80,   130,
     -80,   -80,   -80,   133,   -80,    75,    75,    85,    85,   -80,
     -80,   306,   -80,   124,   -80,   126,   -80,   -80,   140,   141,
     139,   306,   151,   256,   306,   -80,   -80,   -80,   -80,   -80,
     -80,   -80,   -80,   306,   161,    -9,   154,    -9,   155,   156,
     138,    -9,   144,   146,   -80,    -9,   -80,    -9,     5,   -80,
     -80,   -80,   -80,   -80,   -80,   -80,   -80
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    80,    81,    82,     0,     0,     3,     5,     0,     0,
      45,     1,     2,    40,    41,     0,     0,    83,     0,    45,
       0,     0,    44,    47,     0,    38,     0,     0,    74,    73,
      76,    75,     0,     0,     0,     0,    37,     0,     0,     7,
       0,     0,    39,    37,     0,    16,     0,    11,     0,    49,
      60,    64,     0,     0,    92,     0,    74,     0,     0,     0,
       0,     4,    43,     0,    48,    29,     9,     0,     0,     0,
      67,    68,    65,    66,     0,    78,     0,     0,     0,     0,
       0,    69,    71,    70,    72,     0,     0,     0,     0,    31,
      15,    55,    54,    53,    52,    56,    57,     0,     0,     0,
      51,     0,     0,    61,     0,    17,    94,     0,    91,    84,
       0,    87,    42,    85,     0,    46,    10,     0,     0,     0,
       0,     0,    77,     0,    35,     0,     0,     0,    30,    79,
      89,     6,    18,     0,    50,    60,    60,    64,    64,    20,
      88,     0,    79,     0,    26,     0,    12,    13,     0,     0,
      33,     0,     0,     0,     0,    37,    58,    59,    63,    62,
      93,    86,    25,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,    22,     0,     0,    14,
      32,    27,    28,    21,    23,    24,    19
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -80,   -80,   176,    95,   148,   -80,   -80,   -80,   -80,   -41,
      -8,   -80,   -80,   -80,   -80,   165,   -80,   123,   -17,    88,
     -80,   -30,    13,   -20,   -48,     4,   135,   125,   -80,   -80,
     -80
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     5,     6,    42,    43,    44,    45,    46,   133,    80,
      47,    15,    16,     7,     8,    21,    22,    23,    48,    49,
      97,   100,    50,   103,    51,    24,    20,    53,    54,   107,
     108
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      14,    58,    87,    11,     9,    10,   185,   109,   145,     9,
      67,    13,    68,    17,    25,    74,    17,    77,    62,   113,
      52,   117,    63,    85,    56,    13,    29,    30,    31,    32,
      69,    55,    33,     1,     2,     3,    65,   106,    89,    52,
     110,   146,    56,    64,    29,    30,    31,    32,    72,    73,
      33,   118,   121,   137,   138,    91,    92,    93,    94,    95,
      96,   125,   127,   128,    75,     1,     2,     3,    70,    71,
       4,    81,    66,    82,    83,    88,    84,    60,    61,    90,
     132,    60,   139,     1,     2,     3,    98,    99,     4,    37,
      38,    52,    18,    19,   105,    18,   111,   143,   114,   101,
     102,    70,    71,    57,    41,   156,   157,    37,    38,   152,
     112,   135,   136,   116,   171,   150,   122,   158,   159,   123,
      26,    57,    27,    28,   160,    29,    30,    31,    32,   129,
     124,    33,   130,   -36,   166,    34,   169,   170,   140,    13,
      -8,   141,   142,   154,   148,   144,   172,    35,    36,   147,
     149,   151,   155,   163,   164,   153,   161,   174,   165,   176,
     162,   167,   173,   180,   175,   177,   178,   183,    86,   184,
     186,   -90,   179,   -90,   -90,   -90,   -90,   -90,   181,   -90,
     182,    12,   131,    79,    59,   134,   115,   104,    37,    38,
      39,     0,     0,   119,     0,     0,     0,     0,     0,     1,
       2,     3,    40,    41,    78,     0,    27,    28,     0,    29,
      30,    31,    32,     0,     0,    33,     0,     0,     0,    34,
       0,     0,    76,    13,     0,    56,     0,    29,    30,    31,
      32,    35,    36,    33,     0,     0,   -90,   -90,   120,     0,
       0,    56,     0,    29,    30,    31,    32,     0,   126,    33,
     -90,    56,     0,    29,    30,    31,    32,   168,     0,    33,
      56,     0,    29,    30,    31,    32,     0,     0,    33,     0,
       0,     0,    37,    38,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     1,     2,     3,    40,    41,     0,     0,
      37,    38,    56,     0,    29,    30,    31,    32,     0,     0,
      33,     0,     0,     0,    57,     0,    37,    38,     0,     0,
      56,     0,    29,    30,    31,    32,    37,    38,    33,     0,
      57,     0,    65,     0,     0,    37,    38,     0,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,    57,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    37,    38,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,     0,     0,     0,    37,    38,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    57
};

static const yytype_int16 yycheck[] =
{
       8,    18,    43,     0,     0,    84,     1,    55,     1,     5,
      27,    20,    13,     4,    21,    32,     4,    34,    10,     4,
      16,     1,    33,    40,     4,    20,     6,     7,     8,     9,
      31,    13,    12,    80,    81,    82,    34,    54,    46,    35,
      57,    34,     4,     4,     6,     7,     8,     9,    69,    70,
      12,    68,    69,   101,   102,    22,    23,    24,    25,    26,
      27,    78,    79,    80,     6,    80,    81,    82,    69,    70,
      85,     4,    34,     6,     4,    10,     6,    33,    34,    34,
      88,    33,    34,    80,    81,    82,    11,    12,    85,    69,
      70,    87,    83,    84,    34,    83,    32,   114,    83,    14,
      15,    69,    70,    83,    84,   135,   136,    69,    70,   126,
      10,    98,    99,    34,   155,   123,    10,   137,   138,    10,
       1,    83,     3,     4,   141,     6,     7,     8,     9,    32,
      10,    12,    10,    19,   151,    16,   153,   154,    10,    20,
      21,    33,    32,    13,    32,    34,   163,    28,    29,    34,
      32,    34,    19,    13,    13,    34,    32,   165,    19,   167,
      34,    10,     1,   171,    10,    10,    10,   175,     1,   177,
     178,     4,    34,     6,     7,     8,     9,    10,    34,    12,
      34,     5,    87,    35,    19,    97,    63,    52,    69,    70,
      71,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    80,
      81,    82,    83,    84,     1,    -1,     3,     4,    -1,     6,
       7,     8,     9,    -1,    -1,    12,    -1,    -1,    -1,    16,
      -1,    -1,     1,    20,    -1,     4,    -1,     6,     7,     8,
       9,    28,    29,    12,    -1,    -1,    69,    70,     1,    -1,
      -1,     4,    -1,     6,     7,     8,     9,    -1,     1,    12,
      83,     4,    -1,     6,     7,     8,     9,     1,    -1,    12,
       4,    -1,     6,     7,     8,     9,    -1,    -1,    12,    -1,
      -1,    -1,    69,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    80,    81,    82,    83,    84,    -1,    -1,
      69,    70,     4,    -1,     6,     7,     8,     9,    -1,    -1,
      12,    -1,    -1,    -1,    83,    -1,    69,    70,    -1,    -1,
       4,    -1,     6,     7,     8,     9,    69,    70,    12,    -1,
      83,    -1,    34,    -1,    -1,    69,    70,    -1,    -1,    -1,
      83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    69,    70,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    83
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    80,    81,    82,    85,    87,    88,    99,   100,   111,
      84,     0,    88,    20,    96,    97,    98,     4,    83,    84,
     112,   101,   102,   103,   111,    21,     1,     3,     4,     6,
       7,     8,     9,    12,    16,    28,    29,    69,    70,    71,
      83,    84,    89,    90,    91,    92,    93,    96,   104,   105,
     108,   110,   111,   113,   114,    13,     4,    83,   104,   101,
      33,    34,    10,    33,     4,    34,    34,   104,    13,    31,
      69,    70,    69,    70,   104,     6,     1,   104,     1,    90,
      95,     4,     6,     4,     6,   104,     1,    95,    10,    96,
      34,    22,    23,    24,    25,    26,    27,   106,    11,    12,
     107,    14,    15,   109,   112,    34,   104,   115,   116,   110,
     104,    32,    10,     4,    83,   103,    34,     1,   104,   113,
       1,   104,    10,    10,    10,   104,     1,   104,   104,    32,
      10,    89,    96,    94,   105,   108,   108,   110,   110,    34,
      10,    33,    32,   104,    34,     1,    34,    34,    32,    32,
      96,    34,   104,    34,    13,    19,   107,   107,   109,   109,
     104,    32,    34,    13,    13,    19,   104,    10,     1,   104,
     104,    95,   104,     1,    96,    10,    96,    10,    10,    34,
      96,    34,    34,    96,    96,     1,    96
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    86,    87,    87,    88,    88,    89,    89,    89,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    90,    90,    90,    90,
      91,    92,    92,    92,    92,    93,    94,    95,    96,    97,
      98,    99,   100,   100,   101,   101,   102,   102,   103,   104,
     104,   105,   106,   106,   106,   106,   106,   106,   107,   107,
     107,   108,   109,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     111,   111,   111,   112,   112,   112,   112,   112,   113,   113,
     114,   115,   115,   116,   116
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     1,     3,     1,     0,     2,
       3,     1,     4,     4,     6,     2,     1,     2,     3,     7,
       3,     7,     6,     7,     7,     5,     4,     7,     7,     2,
       3,     2,     6,     4,     6,     3,     0,     0,     2,     2,
       1,     2,     4,     4,     1,     0,     3,     1,     2,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     3,     3,
       0,     2,     3,     3,     0,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     3,     2,     3,
       1,     1,     1,     1,     3,     3,     5,     3,     3,     3,
       1,     1,     0,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 710 "parser.y" /* yacc.c:1646  */
    {
fprintf(outprod, "program_code --> program_code external_declarations\n");
 typer* ret;
ret = create_node(7, 0.00, 2, "program_code");
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
root=ret;
// print_symbol_table();
}
#line 2070 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 720 "parser.y" /* yacc.c:1646  */
    {
fprintf(outprod, "program_code --> external_declarations\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "program_code");
ret->child_list[0]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
root=ret;
// print_symbol_table();

}
#line 2085 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 733 "parser.y" /* yacc.c:1646  */
    {
fprintf(outprod, "external_declarations --> type ident-list SEMICOLON\n");
 typer* ret;
ret = create_node(7, 0.00, 3, "external_declarations");
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 2099 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 742 "parser.y" /* yacc.c:1646  */
    {
fprintf(outprod, "external_declarations --> func_decl\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "external_declarations");
ret->child_list[0]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
// print_func_table();
// print_code1();
}
#line 2113 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 754 "parser.y" /* yacc.c:1646  */
    {yyerrok;
fprintf(outprod, "statements --> statement statements\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->num_children=2;
// next_list_printer($3->next);

backpatch((yyvsp[-2].type_all)->next, (yyvsp[-1].type_all)->label, (yyvsp[-1].type_all)->quad);
ret->next = (yyvsp[0].type_all)->next;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
(yyval.type_all)=ret;}
#line 2130 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 766 "parser.y" /* yacc.c:1646  */
    {yyerrok;fprintf(outprod, "statements --> ENDALL\n");typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->next = makelist(-1);
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2139 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 770 "parser.y" /* yacc.c:1646  */
    {yyerrok;fprintf(outprod, "statements --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "statements");
ret->next = makelist(-1);
 ret->decimal=0.00;
ret->child_list[0]=create_node(1,0.00,0,"NULL");
(yyval.type_all)=ret;}
#line 2150 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 780 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "statement --> RETURN SEMICOLON\n");typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=2;
    if(active_func_ptr==NULL){
        yyerror("ERROR : Return in a construct not a function!");
        yyerrok;
        break;
    }
    if(active_func_ptr->res_type!=3){
        yyerror("ERROR : NULL return in a non-void function!");
        yyerrok;
        break;
    }
    ret->child_list[0]=(yyvsp[-1].type_all);
    ret->child_list[1]=(yyvsp[0].type_all);
    // char* temp = (char*)malloc(120*sizeof(char));
    // sprintf(temp, );
    gen_code("return\n");
    ret->next = makelist(-1);
    (yyval.type_all)=ret;
}
#line 2177 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 803 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "statement --> RETURN expression SEMICOLON\n");typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=3;
    if(active_func_ptr==NULL){
        yyerror("ERROR : Return in a construct not a function!");
        yyerrok;
        break;
    }
    if(active_func_ptr->res_type==3){
        yyerror("ERROR : Non NULL return in a void function!");
        yyerrok;
        break;
    }
    char* temp = (char*)malloc(120*sizeof(char));
    sprintf(temp, "return %s\n", (yyvsp[-1].type_all)->result->name);
    gen_code(temp);
    ret->next = makelist(-1);
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2205 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 827 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "statement --> opt_block\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=1;
    ret->next = (yyvsp[0].type_all)->next;
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2219 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 836 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> IDENT ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
if((yyvsp[-1].type_all)->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up((yyvsp[-3].type_all)->name, scope);
        prl* prlptr = search_param((yyvsp[-3].type_all)->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", (yyvsp[-3].type_all)->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }
        if( (yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if(identptr->type_ident==1 || (yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR: Cannot assign array");
                yyerrok;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if(!coercible(identptr->eletype, (yyvsp[-1].type_all)->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, (yyvsp[-1].type_all)->type);

        if(identptr->eletype==0){
            int b = *((int*)setter((yyvsp[-1].type_all)));
            identptr->num = b;
        }else if(identptr->eletype==1){
            double b = *((double*)setter((yyvsp[-1].type_all)));
            identptr->decimal = b;
        }else if(identptr->eletype==2){
            char b = *((char*)setter((yyvsp[-1].type_all)));
            identptr->character = b;
        }
        char* tmp1 = (char *)malloc(120*sizeof(char));
        sprintf(tmp1, "%s = %s\n", (yyvsp[-3].type_all)->name, (yyvsp[-1].type_all)->result->name);
        gen_code(tmp1);
        freename((yyvsp[-1].type_all)->result->name);
     }else{
        break;
     }
     ret->next = makelist(-1);
ret->num_children=4;
ret->child_list[0]=(yyvsp[-3].type_all);
ret->child_list[1]=(yyvsp[-2].type_all);
ret->child_list[2]=(yyvsp[-1].type_all);
ret->child_list[3]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 2289 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 902 "parser.y" /* yacc.c:1646  */
    {
        fprintf(outprod, "statement --> IDENT ASSIGN function SEMICOLON\n");
        typer* ret;
        ret = create_node(1, 0.00, 1, "statement");
        ret->next = makelist(-1);
        ste* identptr = symtab_lookup_up((yyvsp[-3].type_all)->name, scope);
        prl* prlptr = search_param((yyvsp[-3].type_all)->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", (yyvsp[-3].type_all)->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }

        if(identptr->type_ident==1){
            yyerror("ERROR: Cannot assign array");
            yyerrok;
            break;
        }
        if((yyvsp[-1].type_all)->type==3){
            yyerror("ERROR: Void cannot be assigned!");
            yyerrok;
            break;
        }
        if(!coercible(identptr->eletype, (yyvsp[-1].type_all)->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, (yyvsp[-1].type_all)->type);
        
        char* tmp1 = (char *)malloc(120*sizeof(char));
        sprintf(tmp1, "%s = %s\n", (yyvsp[-3].type_all)->name, (yyvsp[-1].type_all)->result->name);
        gen_code(tmp1);

        ret->num_children=4;
        ret->child_list[0]=(yyvsp[-3].type_all);
        ret->child_list[1]=(yyvsp[-2].type_all);
        ret->child_list[2]=(yyvsp[-1].type_all);
        ret->child_list[3]=(yyvsp[0].type_all);
        (yyval.type_all)=ret;
}
#line 2341 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 949 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");

if((yyvsp[-1].type_all)->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up((yyvsp[-5].type_all)->name, scope);
        prl* prlptr = search_param((yyvsp[-5].type_all)->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", (yyvsp[-5].type_all)->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }
        if( (yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR: Cannot assign array");
                yyerrok;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if(!coercible(identptr->eletype, (yyvsp[-1].type_all)->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        // printf(">>>>>>>>>>>  %d\n", $2->type);
        if((yyvsp[-4].type_all)->type!=0){
            if((yyvsp[-4].type_all)->type==4){
                ste* identptr1 = symtab_lookup_up((yyvsp[-4].type_all)->st_entry->name, scope);
                prl* prlptr1 = search_param((yyvsp[-4].type_all)->st_entry->name);
                if(!identptr1 && !prlptr1){
                    error_caller("ERROR: Undeclared identifier! ", (yyvsp[-5].type_all)->name);
                    yyerrok;
                    break;
                }
                int ident_type;
                if(!identptr){
                    ident_type = prlptr1->param_type;
                } else{
                    ident_type = identptr1->eletype;
                }
                if(ident_type!=0){
                    yyerror("ERROR: Non Integer Indexing!");
                    yyerrok;
                    break;
                }
            }else{
                yyerror("ERROR: Non Integer Indexing!");
                yyerrok;
                break;
            }
        }
        if((yyvsp[-4].type_all)->num >= identptr->dim || (yyvsp[-4].type_all)->num < 0){
            yyerror("ERROR: Array index out of bounds!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, (yyvsp[-1].type_all)->type);

        if(identptr->eletype==0){
            int b = *((int*)setter((yyvsp[-1].type_all)));
            identptr->arrayint[(yyvsp[-4].type_all)->num] = b;
        }else if(identptr->eletype==1){
            double b = *((double*)setter((yyvsp[-1].type_all)));
            identptr->arraydouble[(yyvsp[-4].type_all)->num] = b;
        }else if(identptr->eletype==2){
            char b = *((char*)setter((yyvsp[-1].type_all)));
            identptr->arraychar[(yyvsp[-4].type_all)->num] = b;
        }

        char* tmp1 = (char *)malloc(100*sizeof(char));
        tte* temp = newtemp(identptr->eletype);
        tte* temp2 = newtemp(0);
        tte* temp3 = newtemp(0);
        sprintf(tmp1, "%s = addr(%s)\n%s = 4\n%s = %s * %s\n%s[%s] = %s\n",
         temp->name,
         identptr->name,
         temp3->name,
         temp2->name,
         (yyvsp[-4].type_all)->result->name,
         temp3->name,
         temp->name,
         temp2->name,
         (yyvsp[-1].type_all)->result->name);
        gen_code(tmp1);
        nextquad+=2;
        freename(temp3->name);
        freename((yyvsp[-1].type_all)->result->name);
        freename((yyvsp[-4].type_all)->result->name);
     }else{
        break;
     }
ret->next = makelist(-1);
ret->num_children=6;
ret->child_list[0]=(yyvsp[-5].type_all);ret->child_list[1]=(yyvsp[-4].type_all);
ret->child_list[2]=(yyvsp[-3].type_all);
ret->child_list[3]=(yyvsp[-2].type_all);
ret->child_list[4]=(yyvsp[-1].type_all);
ret->child_list[5]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 2461 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 1064 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->next = makelist(-1);
ret->child_list[0]=(yyvsp[-1].type_all);ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2472 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 1070 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> selection\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->next = (yyvsp[0].type_all)->next;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2482 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 1075 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> function SEMICOLON\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->next = makelist(-1);
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2493 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 1081 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> WHILELP expression RP opt_block \n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);

char* temp = (char *)malloc(120*sizeof(char));
sprintf(temp, "goto %s\n", (yyvsp[-2].type_all)->label);
gen_code(temp);

tagtoaddlabel[numtags++] = strdup((yyvsp[-2].type_all)->label);
tagtoaddquad[numtags-1] = (yyvsp[-2].type_all)->begin;

backpatch((yyvsp[0].type_all)->next, (yyvsp[-2].type_all)->label, (yyvsp[-2].type_all)->begin);
ret->next = (yyvsp[-2].type_all)->falselist;

(yyval.type_all)=ret;}
#line 2516 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 1099 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> FORLP statement expression SEMICOLON expression RP opt_block\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=7;
ret->child_list[0]=(yyvsp[-6].type_all);
ret->next = makelist(-1);
ret->child_list[1]=(yyvsp[-5].type_all);
ret->child_list[2]=(yyvsp[-4].type_all);
ret->child_list[3]=(yyvsp[-3].type_all);
ret->child_list[4]=(yyvsp[-2].type_all);
ret->child_list[5]=(yyvsp[-1].type_all);
ret->child_list[6]=(yyvsp[0].type_all);
(yyval.type_all)=ret;}
#line 2533 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 1111 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> type ident-list SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 3, "statement");
 (yyvsp[-2].type_all)->decimal = (yyvsp[0].type_all)->decimal;
ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->next = makelist(-1);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
patchtype((yyvsp[-1].type_all)->namelist, (yyvsp[-1].type_all)->namelistnum, (yyvsp[-2].type_all)->type);}
#line 2549 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 1123 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in initialization expression!\n");
yyerrok;}
#line 2556 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 1125 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in check expression!\n");
yyerrok;}
#line 2563 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 1127 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in update expression!\n");
yyerrok;}
#line 2570 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 1129 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in body of FOR loop!\n");
yyerrok;}
#line 2577 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 1131 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Unknown elements after assigned expression!\n");
yyerrok;}
#line 2584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 1133 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in assigned expression!\n");
yyerrok;}
#line 2591 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 1135 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Unsupported indexing!\n");
yyerrok;}
#line 2598 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 1137 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Error in assigned expression!\n");
yyerrok;}
#line 2605 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 1139 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Wrong expression or function call!\n");
yyerrok;}
#line 2612 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 1146 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
    ret = create_node(0, 0.00, 1, "selection");
    // ret->next = merge($2->next, $1->falselist);
    ret->falselist = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "if %s <= 0 goto \n", (yyvsp[0].type_all)->result->name);
    // printf(">>>>>>>>>>>>>>>>>>>>>>>>>?? %d\n", $2->quad);
    gen_code(temp);
    ret->begin = (yyvsp[-1].type_all)->quad;
    ret->label = (yyvsp[-1].type_all)->label;
    ret->num_children=2;
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 1165 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection");
            ret->next = merge((yyvsp[0].type_all)->next, (yyvsp[-1].type_all)->falselist);
            ret->num_children=2;
            ret->child_list[0]=(yyvsp[-1].type_all);
            ret->child_list[1]=(yyvsp[0].type_all);
            (yyval.type_all)=ret;}
#line 2645 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 1172 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection");
            ret->num_children=4;

            backpatch((yyvsp[-5].type_all)->falselist, (yyvsp[-1].type_all)->label, (yyvsp[-1].type_all)->quad);
            ret->next = merge((yyvsp[-4].type_all)->next, (yyvsp[0].type_all)->next);
            ret->next = merge(ret->next, (yyvsp[-3].type_all)->next);

            ret->child_list[0]=(yyvsp[-5].type_all);
            ret->child_list[1]=(yyvsp[-4].type_all);
            ret->child_list[2]=(yyvsp[-3].type_all);
            ret->child_list[3]=(yyvsp[-2].type_all);
            (yyval.type_all)=ret;}
#line 2663 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 1185 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
#line 2669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 1186 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
#line 2675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 1190 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "ifexp --> IFLP expression RP\n");
    typer* ret;
    ret = create_node(7, 0.00, 1, "ifexp");
    ret->num_children = 3;
    ret->falselist = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "if %s <= 0 goto \n", (yyvsp[-1].type_all)->result->name);
    gen_code(temp);
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2694 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 1208 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "statements --> (nil)\n");typer* ret;
    ret = create_node(5, 0.00, 1, "statements");
    ret->next = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "goto \n");
    gen_code(temp);
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    (yyval.type_all)=ret;
}
#line 2709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 1221 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "statements --> (nil)\n");
    typer* ret;
    ret = create_node(5, 0.00, 1, "statements");
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    char* tag = TAGARR[tagcntr++];
    ret->label = strdup(tag);
    ret->quad = nextquad;
    // char* temp = (char *)malloc(120*sizeof(char));
    // sprintf(temp, "%s:\n", tag);
    // gen_code(temp);
    (yyval.type_all)=ret;
}
#line 2727 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 1237 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "opt_block --> beforeend END\n");typer* ret;
ret = create_node(7, 0.00, 1, "opt_block");
ret->num_children=2;
ret->next = (yyvsp[-1].type_all)->next;
ret->child_list[0]=(yyvsp[-1].type_all);ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2737 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 1245 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "beforeend --> beforestats statements\n");typer* ret;
ret = create_node(7, 0.00, 1, "beforeend");
print_symbol_table();
ret->next = (yyvsp[0].type_all)->next;
write_data_part2(codefile);
delete_var_level(scope);
scope--;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2751 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 1257 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "beforestats --> BEG\n");typer* ret;
ret = create_node(7, 0.00, 1, "beforestats");
ret->num_children=1;
scope++;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 2761 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 1266 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "func_decl --> func_head opt_block\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_decl");
ret->num_children=2;

char* tag = TAGARR[tagcntr++];
backpatch((yyvsp[0].type_all)->next, tag, nextquad);
gen_code("func end\n");

ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);
active_func_ptr = NULL;
(yyval.type_all)=ret;}
#line 2778 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 1281 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "func_head --> type IDENTLP decl_plist RP\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_head");
ret->num_children=4;
ret->child_list[0]=(yyvsp[-3].type_all);
ret->child_list[1]=(yyvsp[-2].type_all);
ret->child_list[2]=(yyvsp[-1].type_all);
ret->child_list[3]=(yyvsp[0].type_all);
int res = insert_functab((yyvsp[-3].type_all)->type, (yyvsp[-2].type_all)->name);
if(!res){
    yyerror("ERROR: Function already declared!");
    yyerrok;
    break;
}
if((yyvsp[-1].type_all)->type!=5){
    fte* func = functab_lookup((yyvsp[-2].type_all)->name);
    for(int i=0; i<(yyvsp[-1].type_all)->paramlistnum; i++){
        insert_param(func, (yyvsp[-1].type_all)->paramlist[i]->param_type, (yyvsp[-1].type_all)->paramlist[i]->param_name);
    }
}
active_func_ptr = functab_lookup((yyvsp[-2].type_all)->name);

char* temp1 = (char *)malloc(120*sizeof(char));
sprintf(temp1, "func begin %s\n", active_func_ptr->func_name);
gen_code(temp1);

(yyval.type_all)=ret;}
#line 2809 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 1307 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "func_head --> VOID IDENTLP decl_plist RP\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_head");
ret->num_children=4;
ret->child_list[0]=(yyvsp[-3].type_all);
ret->child_list[1]=(yyvsp[-2].type_all);
ret->child_list[2]=(yyvsp[-1].type_all);
ret->child_list[3]=(yyvsp[0].type_all);
int res = insert_functab((yyvsp[-3].type_all)->type, (yyvsp[-2].type_all)->name);
if(!res){
    yyerror("ERROR: Function already declared!");
    yyerrok;
    break;
}
if((yyvsp[-1].type_all)->type!=5){
    fte* func = functab_lookup((yyvsp[-2].type_all)->name);
    for(int i=0; i<(yyvsp[-1].type_all)->paramlistnum; i++){
        insert_param(func, (yyvsp[-1].type_all)->paramlist[i]->param_type, (yyvsp[-1].type_all)->paramlist[i]->param_name);
    }
}
active_func_ptr = functab_lookup((yyvsp[-2].type_all)->name);

char* temp1 = (char *)malloc(120*sizeof(char));
sprintf(temp1, "func begin %s\n", active_func_ptr->func_name);
gen_code(temp1);

(yyval.type_all)=ret;}
#line 2840 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 1337 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "decl_plist --> decl_pl\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_plist");
    ret->num_children=1;
    copy_paramlist(ret, (yyvsp[0].type_all));
    ret->paramlistnum--;
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2854 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 1347 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "decl_plist --> (nil)\n");typer* ret;
    ret = create_node(5, 0.00, 1, "decl_plist");
    ret->decimal=0.00;
    ret->num_children=1;
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    (yyval.type_all)=ret;
}
#line 2867 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 1359 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "decl_pl --> decl_pl COMMA decl_param\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_pl");

    ret->paramlistnum++;
    copy_paramlist(ret, (yyvsp[-2].type_all));
    ret->paramlist[ret->paramlistnum-1] = (yyvsp[0].type_all)->paramlist[0];

    ret->num_children=3;
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2886 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 1375 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "decl_pl --> decl_param\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_pl");
    ret->num_children=1;
    ret->paramlistnum++;
    ret->paramlist[0] = (yyvsp[0].type_all)->paramlist[0];
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2900 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 1388 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "decl_param --> type IDENT\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_param");
    ret->paramlistnum=1;
    ret->paramlist[0] = create_param((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->name);
    ret->num_children=2;
    ret->child_list[0]=(yyvsp[-1].type_all);
    ret->child_list[1]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 2915 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 1402 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "expression --> expr_temp\n");typer* ret;
    ret = create_node(0, 0.00, 1, "expression");
    ret->type = (yyvsp[0].type_all)->type;
    ret->st_entry = (yyvsp[0].type_all)->st_entry;
    ret->decimal = (yyvsp[0].type_all)->decimal;
    ret->num = (yyvsp[0].type_all)->num;
    ret->character = (yyvsp[0].type_all)->character;
    ret->num_children=1;
    ret->child_list[0]=(yyvsp[0].type_all);
    ret->result = (yyvsp[0].type_all)->result;
    (yyval.type_all)=ret;
}
#line 2933 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 1417 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression --> expr_temp RA_TERM expr_temp\n");typer* ret;
ret = create_node(0, 0.00, 1, "expression");
if((yyvsp[-2].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-2].type_all)->type==4){
            if(!(yyvsp[-2].type_all)->st_entry){
                break;
            }
            if((yyvsp[-2].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-2].type_all)->type==4){
            if(!(yyvsp[-2].type_all)->st_entry){
                break;
            }
            (yyvsp[-2].type_all)->type = (yyvsp[-2].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-2].type_all)->type, (yyvsp[0].type_all)->type)){
            yyerror("ERROR2 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-2].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;
        if((yyvsp[-1].type_all)->ra_term_val==3){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);

            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if((yyvsp[-1].type_all)->ra_term_val==2){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if((yyvsp[-1].type_all)->ra_term_val==1){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if((yyvsp[-1].type_all)->ra_term_val==0){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if((yyvsp[-1].type_all)->ra_term_val==4){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if((yyvsp[-1].type_all)->ra_term_val==5){
            if(ret->type==0){
            int a = *((int*)setter((yyvsp[-2].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-2].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-2].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", (yyvsp[-2].type_all)->result->name, (yyvsp[0].type_all)->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }

     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=3;ret->child_list[0]=(yyvsp[-2].type_all);ret->child_list[1]=(yyvsp[-1].type_all);ret->child_list[2]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3363 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 1846 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expr_temp --> term expression_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "expr_temp");
if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    ret->decimal = (yyvsp[-1].type_all)->decimal;
    ret->num = (yyvsp[-1].type_all)->num;
    ret->character = (yyvsp[-1].type_all)->character; 

    ret->result = (yyvsp[-1].type_all)->result;   
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR4 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter((yyvsp[-1].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a+b);
        }

        tte* newtmp = newtemp(ret->type);


        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }

        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1] = (yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3457 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 1939 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> LTEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
// ret->decimal=0.00;
ret->ra_term_val = 3;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3468 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 1945 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> GTEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 2;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3479 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 1951 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> LT\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 1;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3490 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 1957 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> GT\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 0;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3501 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 1963 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> EQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 4;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3512 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 1969 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "RA_TERM --> NEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 5;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3523 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 1979 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> PLUS term expression_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "expression_prime");
 if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    ret->decimal = (yyvsp[-1].type_all)->decimal;
    ret->num = (yyvsp[-1].type_all)->num;
    ret->character = (yyvsp[-1].type_all)->character; 

    ret->am_sd = 0;
    ret->result = (yyvsp[-1].type_all)->result;    
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR6 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter((yyvsp[-1].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a+b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }
        ret->am_sd = 0;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);ret->child_list[2]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3615 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 2066 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> MINUS term expression_prime \n");typer* ret;
ret = create_node(0, 0.00, 1, "expression_prime");
 if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    ret->decimal = -(yyvsp[-1].type_all)->decimal;
    ret->num = -(yyvsp[-1].type_all)->num;
    ret->character = -(yyvsp[-1].type_all)->character;  

    ret->am_sd = 1;
    ret->result = (yyvsp[-1].type_all)->result;  
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR8 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter((yyvsp[-1].type_all)));
            int b = *((int*)setter((yyvsp[0].type_all)));
            ret->num=-(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=-(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=-(a+b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }
        ret->am_sd = 1;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 3711 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 2157 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "expression_prime --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "expression_prime");
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");(yyval.type_all)=ret;}
#line 3720 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 2164 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term --> factor term_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "term");
 if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    ret->decimal = (yyvsp[-1].type_all)->decimal;
    ret->num = (yyvsp[-1].type_all)->num;
    ret->character = (yyvsp[-1].type_all)->character;
    if((yyvsp[-1].type_all)->decimal==0){
        ret->decimal = (yyvsp[-1].type_all)->num;
    }else if((yyvsp[-1].type_all)->num==0){
        ret->num = (yyvsp[-1].type_all)->decimal;
    }
    ret->result = (yyvsp[-1].type_all)->result;
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR10 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            // int a = *((int*)setter($1));
            // int b = *((int*)setter($2));
            // ret->num=(a*b);
            if(!(yyvsp[0].type_all)->am_sd){
                int a = *((int*)setter((yyvsp[-1].type_all)));
                int b = *((int*)setter((yyvsp[0].type_all)));
                ret->num=(a*b);
                ret->decimal = ret->num;
            }else{
                double a1 = (yyvsp[-1].type_all)->num;
                double b1 = (yyvsp[0].type_all)->decimal;
                double c1 = (a1*b1);
                ret->num = c1;
                ret->decimal = ret->num;
            }
            if(ret->decimal==0){
                ret->decimal = ret->num;
            }else if(ret->num==0){
                ret->num = ret->decimal;
            }
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a*b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 3831 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 2273 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "term_prime --> MULT factor term_prime\n");
    typer* ret;
ret = create_node(0, 0.00, 1, "term_prime");
    if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    ret->decimal = (yyvsp[-1].type_all)->decimal;
    ret->num = (yyvsp[-1].type_all)->num;
    if((yyvsp[-1].type_all)->decimal==0){
        ret->decimal = (yyvsp[-1].type_all)->num;
    }else if((yyvsp[-1].type_all)->num==0){
        ret->num = (yyvsp[-1].type_all)->decimal;
    }
    ret->character = (yyvsp[-1].type_all)->character; 
    ret->am_sd = 0;
    ret->result = (yyvsp[-1].type_all)->result;   
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[-1].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR12 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            if(!(yyvsp[0].type_all)->am_sd){
                int a = *((int*)setter((yyvsp[-1].type_all)));
                int b = *((int*)setter((yyvsp[0].type_all)));
                ret->num=(a*b);
                ret->decimal = ret->num;
            }else{
                double a1 = (yyvsp[-1].type_all)->num;
                double b1 = (yyvsp[0].type_all)->decimal;
                double c1 = (a1*b1);
                ret->num = c1;
                ret->decimal = ret->num;
            }
            if(ret->decimal==0){
                ret->decimal = ret->num;
            }else if(ret->num==0){
                ret->num = ret->decimal;
            }
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=(a*b);
        }
        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }
        ret->am_sd = 0;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
    ret->num_children=3;
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);

    (yyval.type_all)=ret;
}
#line 3946 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 2383 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "term_prime --> DIV factor term_prime\n");
    typer* ret;
ret = create_node(0, 0.00, 1, "term_prime");
if((yyvsp[0].type_all)->type==5){
    ret->type = (yyvsp[-1].type_all)->type;
    ret->st_entry = (yyvsp[-1].type_all)->st_entry;
    if((yyvsp[-1].type_all)->decimal)
        ret->decimal = 1/(yyvsp[-1].type_all)->decimal;
    if((yyvsp[-1].type_all)->num)
        ret->num = 1/(yyvsp[-1].type_all)->num;
    if((yyvsp[-1].type_all)->type==0){
        ret->decimal = 1.0/(yyvsp[-1].type_all)->num;
    }
    if((yyvsp[-1].type_all)->decimal==0){
        ret->decimal = 1.0/(yyvsp[-1].type_all)->num;
    }else if((yyvsp[-1].type_all)->num==0){
        ret->num = 1.0/(yyvsp[-1].type_all)->decimal;
    }
    ret->character = 1/(yyvsp[-1].type_all)->character;   

    ret->am_sd = 1;
    ret->result = (yyvsp[-1].type_all)->result;
}
else if((yyvsp[-1].type_all)->type!=ERROR_TYPE && (yyvsp[0].type_all)->type!=ERROR_TYPE){
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            if((yyvsp[0].type_all)->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if((yyvsp[-1].type_all)->type==4){
            if(!(yyvsp[-1].type_all)->st_entry){
                break;
            }
            (yyvsp[-1].type_all)->type = (yyvsp[-1].type_all)->st_entry->eletype;
        }
        if((yyvsp[0].type_all)->type==4){
            if(!(yyvsp[0].type_all)->st_entry){
                break;
            }
            (yyvsp[0].type_all)->type = (yyvsp[0].type_all)->st_entry->eletype;
        }
        if(!coercible((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type) || (!compatible_arithop((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type))){
            yyerror("ERROR14 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type((yyvsp[-1].type_all)->type, (yyvsp[0].type_all)->type);
        ret->type = ret_type;

        if(ret->type==0){
            // int a = *((int*)setter($2));
            // int b = *((int*)setter($3));
            double a1 = (yyvsp[-1].type_all)->num;
            double b1 = (yyvsp[0].type_all)->decimal;
            double c1 = 1.0/(int)(a1*b1);
            ret->decimal = c1;
            ret->num = c1;
        }else if(ret->type==1){
            double a = *((double*)setter((yyvsp[-1].type_all)));
            double b = *((double*)setter((yyvsp[0].type_all)));
            ret->decimal=1/(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter((yyvsp[-1].type_all)));
            char b = *((char*)setter((yyvsp[0].type_all)));
            ret->character=1/(a*b);
        }
        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(120*sizeof(char));
        if((yyvsp[0].type_all)->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, (yyvsp[-1].type_all)->result->name, (yyvsp[0].type_all)->result->name);
        }
        ret->am_sd = 1;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 4056 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 2488 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "term_prime --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "term_prime");
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");(yyval.type_all)=ret;}
#line 4065 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 2495 "parser.y" /* yacc.c:1646  */
    { fprintf(outprod, "factor --> NUM INCR\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=(yyvsp[-1].type_all)->num++;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4084 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 2509 "parser.y" /* yacc.c:1646  */
    { fprintf(outprod, "factor --> NUM DCR\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num = (yyvsp[-1].type_all)->num--;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4103 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 2523 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> IDENT INCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up((yyvsp[-1].type_all)->name, scope);
prl* prlptr = search_param((yyvsp[-1].type_all)->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", (yyvsp[-1].type_all)->name);
    yyerrok;
    break;
}
if(!identptr){
    identptr = (ste*)malloc(sizeof(ste));
    identptr->type_ident = 0;
    identptr->eletype = prlptr->param_type;
    identptr->name = strdup(prlptr->param_name);
}
ret->st_entry = identptr;
if(identptr->eletype==0){
    ret->num = identptr->num++;
}else if(identptr->eletype==2){
    ret->character = identptr->character++;
}else if(identptr->eletype==1){
    ret->decimal = identptr->decimal++;
}else{
    yyerror("Cannot increment non int!");
    yyerrok;
    break;
}
ret->st_entry = identptr;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s + 1\n%s = %s\n%s = %s - 1\n", ret->result->name, identptr->name, ret->result->name, ret->result->name, identptr->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
nextquad+=3;
(yyval.type_all)=ret;
}
#line 4148 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 2563 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> IDENT DCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up((yyvsp[-1].type_all)->name, scope);
prl* prlptr = search_param((yyvsp[-1].type_all)->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", (yyvsp[-1].type_all)->name);
    yyerrok;
    break;
}
if(!identptr){
    identptr = (ste*)malloc(sizeof(ste));
    identptr->type_ident = 0;
    identptr->eletype = prlptr->param_type;
    identptr->name = strdup(prlptr->param_name);
}
ret->st_entry = identptr;
if(identptr->eletype==0){
    ret->num = identptr->num--;
}else if(identptr->eletype==2){
    ret->character = identptr->character--;
}else if(identptr->eletype==1){
    ret->decimal = identptr->decimal--;
}else{
    yyerror("Cannot increment non int!");
    yyerrok;
    break;
}
ret->st_entry = identptr;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s - 1\n%s = %s\n%s = %s + 1\n", ret->result->name, identptr->name, ret->result->name, ret->result->name, identptr->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
nextquad+=3;
(yyval.type_all)=ret;
}
#line 4193 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 2603 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> INCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up((yyvsp[0].type_all)->name, scope);
prl* prlptr = search_param((yyvsp[0].type_all)->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", (yyvsp[0].type_all)->name);
    yyerrok;
    break;
}
if(!identptr){
    identptr = (ste*)malloc(sizeof(ste));
    identptr->type_ident = 0;
    identptr->eletype = prlptr->param_type;
    identptr->name = strdup(prlptr->param_name);
}
ret->st_entry = identptr;
if(identptr->eletype==0){
    ret->num = ++identptr->num;
}else if(identptr->eletype==2){
    ret->character = ++identptr->character;
}else if(identptr->eletype==1){
    ret->decimal = ++identptr->decimal;
}else{
    yyerror("Cannot increment non int!");
    yyerrok;
    break;
}
ret->st_entry = identptr;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s+1\n%s = %s\n", ret->result->name, (yyvsp[0].type_all)->name, ret->result->name, ret->result->name, (yyvsp[0].type_all)->name, ret->result->name);
gen_code(tmp1);
nextquad+=2;
(yyval.type_all)=ret;
}
#line 4238 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 2643 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor -->  DCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up((yyvsp[0].type_all)->name, scope);
prl* prlptr = search_param((yyvsp[0].type_all)->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", (yyvsp[0].type_all)->name);
    yyerrok;
    break;
}
if(!identptr){
    identptr = (ste*)malloc(sizeof(ste));
    identptr->type_ident = 0;
    identptr->eletype = prlptr->param_type;
    identptr->name = strdup(prlptr->param_name);
}
ret->st_entry = identptr;
// ret->decimal=$1->decimal-1;
if(identptr->eletype==0){
    ret->num = --identptr->num;
}else if(identptr->eletype==2){
    ret->character = --identptr->character;
}else if(identptr->eletype==1){
    ret->decimal = --identptr->decimal;
}else{
    yyerror("Cannot increment non int!");
    yyerrok;
    break;
}
ret->st_entry = identptr;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s-1\n%s = %s\n", ret->result->name, (yyvsp[0].type_all)->name, ret->result->name, ret->result->name, (yyvsp[0].type_all)->name, ret->result->name);
gen_code(tmp1);

nextquad+=2;
(yyval.type_all)=ret;
}
#line 4285 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 2685 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor -->  INCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=++(yyvsp[0].type_all)->num;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d+1\n", ret->result->name, ret->num);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4304 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 2699 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor -->  DCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=--(yyvsp[0].type_all)->num;
ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d-1\n", ret->result->name, ret->num);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4323 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 2713 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=(yyvsp[0].type_all)->num;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4341 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 2726 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up((yyvsp[0].type_all)->name, scope);
prl* prlptr = search_param((yyvsp[0].type_all)->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", (yyvsp[0].type_all)->name);
    yyerrok;
    break;
}
if(!identptr){
    identptr = (ste*)malloc(sizeof(ste));
    identptr->type_ident = 0;
    identptr->eletype = prlptr->param_type;
    identptr->name = strdup(prlptr->param_name);
}
ret->st_entry = identptr;
ret->type = 4;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n", ret->result->name, (yyvsp[0].type_all)->name);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4373 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 2753 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> CHAR\n");
typer* ret;
ret = create_node(2, 0.00, 1, "factor");
ret->decimal=0.00;
ret->character = (yyvsp[0].type_all)->character;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);

ret->result = newtemp(2);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %c\n", ret->result->name, ret->character);
gen_code(tmp1);
(yyval.type_all)=ret;
}
#line 4392 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 2767 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> FLOAT\n");
typer* ret;
ret = create_node(1, 0.00, 1, "factor");
ret->decimal=(yyvsp[0].type_all)->decimal;
ret->num_children=1;
ret->child_list[0]=(yyvsp[0].type_all);

ret->result = newtemp(1);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %.2f\n", ret->result->name, ret->decimal);
gen_code(tmp1);

(yyval.type_all)=ret;
}
#line 4411 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 2781 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> LP expression RP\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");ret->type=(yyvsp[-1].type_all)->type;

ret->type = (yyvsp[-1].type_all)->type;
ret->st_entry = (yyvsp[-1].type_all)->st_entry;
ret->decimal = (yyvsp[-1].type_all)->decimal;
ret->num = (yyvsp[-1].type_all)->num;
ret->character = (yyvsp[-1].type_all)->character; 

ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n", ret->result->name, (yyvsp[-1].type_all)->result->name);
gen_code(tmp1);

(yyval.type_all)=ret;
}
#line 4438 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 2803 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "factor --> MINUS NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=-((yyvsp[0].type_all)->num);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);

ret->num_children=2;
ret->child_list[0]=(yyvsp[-1].type_all);
ret->child_list[1]=(yyvsp[0].type_all);(yyval.type_all)=ret;}
#line 4456 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 2816 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "statement --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 3, "statement");

        ste* identptr = symtab_lookup_up((yyvsp[-2].type_all)->name, scope);
        prl* prlptr = search_param((yyvsp[-2].type_all)->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", (yyvsp[-2].type_all)->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }
        if((yyvsp[-1].type_all)->type!=0){
            if((yyvsp[-1].type_all)->type==4){
                ste* identptr1 = symtab_lookup_up((yyvsp[-1].type_all)->st_entry->name, scope);
                prl* prlptr1 = search_param((yyvsp[-1].type_all)->st_entry->name);
                if(!identptr1 && !prlptr1){
                    error_caller("ERROR: Undeclared identifier! ", (yyvsp[-2].type_all)->name);
                    yyerrok;
                    break;
                }
                int ident_type;
                if(!identptr){
                    ident_type = prlptr1->param_type;
                } else{
                    if(identptr1->type_ident==1){
                        yyerror("ERROR: Array cannot be used as index!");
                        yyerrok;
                        break;
                    }
                    ident_type = identptr1->eletype;
                }
                if(ident_type!=0){
                    yyerror("ERROR: Non Integer Indexing!");
                    yyerrok;
                    break;
                }
            }else{
                yyerror("ERROR: Non Integer Indexing!");
                yyerrok;
                break;
            }
        }
        if((yyvsp[-1].type_all)->num >= identptr->dim || (yyvsp[-1].type_all)->num < 0){
            yyerror("ERROR: Array index out of bounds!");
            yyerrok;
            break;
        }
        ret->type = identptr->eletype;
        if(identptr->eletype==0){
            ret->num = identptr->arrayint[(yyvsp[-1].type_all)->num];
        }else if(identptr->eletype==1){
            ret->decimal = identptr->arraydouble[(yyvsp[-1].type_all)->num];
        }else if(identptr->eletype==2){
            ret->character = identptr->arraychar[(yyvsp[-1].type_all)->num];
        }

        char* tmp1 = (char *)malloc(100*sizeof(char));
        tte* temp = newtemp(identptr->eletype);
        tte* temp3 = newtemp(identptr->eletype);
        tte* temp2 = newtemp(0);

        sprintf(tmp1, "%s = addr(%s)\n%s = 4\n%s = %s * %s\n%s = %s[%s]\n",
         temp->name,
         identptr->name,
         temp2->name,
         (yyvsp[-1].type_all)->result->name,
         (yyvsp[-1].type_all)->result->name,
         temp2->name,
         temp3->name,
         temp->name,
         (yyvsp[-1].type_all)->result->name);
        gen_code(tmp1);
        nextquad+=2;
        ret->result = temp3;
ret->next = makelist(-1);
ret->num_children=3;
ret->child_list[0]=(yyvsp[-2].type_all);
ret->child_list[1]=(yyvsp[-1].type_all);
ret->child_list[2]=(yyvsp[0].type_all);
(yyval.type_all)=ret;
}
#line 4548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 80:
#line 2906 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "type --> INT_TYPE\n");
typer* ret;
ret = create_node(0, 0.00, 1, "type");
ret->child_list[0]=(yyvsp[0].type_all);
(yyval.type_all)=ret;}
#line 4558 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 81:
#line 2911 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "type --> FLOAT_TYPE\n");
 typer* ret;
ret = create_node(1, 0.00, 1, "type");
ret->child_list[0]=(yyvsp[0].type_all);
(yyval.type_all)=ret;}
#line 4568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 82:
#line 2916 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "type --> CHAR_TYPE\n");
typer* ret;
ret = create_node(2, 0.00, 1, "type");
ret->child_list[0]=(yyvsp[0].type_all);
(yyval.type_all)=ret;}
#line 4578 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 83:
#line 2925 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "ident-list -->  IDENT\n");
    int done = insert_symtab((yyvsp[0].type_all)->name, 0, 0, 1, 0, 0.00, ' ', scope);
    if(!done){yyerror("ERROR15: redeclaration of identifier!");
    yyerrok;}typer* ret;
    ret = create_node(4, 0.00, 1, "ident-list");
    ret->child_list[0]=(yyvsp[0].type_all);
    ret->namelistnum=1;
    ret->namelist[0]=strdup((yyvsp[0].type_all)->name);
    (yyval.type_all)=ret;
}
#line 4594 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 84:
#line 2937 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "ident-list -->  IDENT\n");
    int done;
    if((yyvsp[0].type_all)->type==0){
        // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.\n");
        done = insert_symtab((yyvsp[-2].type_all)->name, 0, 0, 1, (yyvsp[0].type_all)->num, 0.00, ' ', scope);
    }
    else if((yyvsp[0].type_all)->type==0) 
        done = insert_symtab((yyvsp[-2].type_all)->name, 0, 0, 1, 0, (yyvsp[0].type_all)->decimal, ' ', scope);
    else if((yyvsp[0].type_all)->type==0) 
        done = insert_symtab((yyvsp[-2].type_all)->name, 0, 0, 1, 0, 0.00, (yyvsp[0].type_all)->character, scope);
    if(!done){yyerror("ERROR15: redeclaration of identifier!");
    yyerrok;}typer* ret;
    ret = create_node(4, 0.00, 1, "ident-list");
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->namelistnum=1;
    ret->namelist[0]=strdup((yyvsp[-2].type_all)->name);
    (yyval.type_all)=ret;
}
#line 4618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 85:
#line 2957 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "ident-list --> ident-list COMMA IDENT \n");
    int done = insert_symtab((yyvsp[0].type_all)->name, 0, 0, 1, 0, 0.00, ' ', scope);
    if(!done){yyerror("ERROR16: redeclaration of identifier!");
    yyerrok;} typer* ret;
    ret = create_node(4, 0.00, 3, "ident-list");
    ret->namelistnum++;
    copy_namelist(ret, (yyvsp[-2].type_all));
    ret->namelist[ret->namelistnum-1]=strdup((yyvsp[0].type_all)->name);
    ret->child_list[0]=(yyvsp[-2].type_all);ret->child_list[1]=(yyvsp[-1].type_all);ret->child_list[2]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 4635 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 86:
#line 2969 "parser.y" /* yacc.c:1646  */
    { fprintf(outprod, "ident-list --> ident-list COMMA IDENTARRAY expression RSQ\n");

if((yyvsp[-1].type_all)->type!=0){yyerror("ERROR17: Non integer size!");
yyerrok;} else if((yyvsp[-1].type_all)->num <=0){yyerror("ERROR18: NonPositive Array Size!");
yyerrok;} else{int done = insert_symtab((yyvsp[-2].type_all)->name, 1, 0, (yyvsp[-1].type_all)->num, 0, 0.00, ' ', scope);
if(!done){yyerror("ERROR19: redeclaration of identifier!");
yyerrok;} } typer* ret;
ret = create_node(4, 0.00, 5, "ident-list");
 ret->namelistnum++;copy_namelist(ret, (yyvsp[-4].type_all));
 ret->namelist[ret->namelistnum-1]=strdup((yyvsp[-2].type_all)->name);
ret->child_list[0]=(yyvsp[-4].type_all);ret->child_list[1]=(yyvsp[-3].type_all);ret->child_list[2]=(yyvsp[-2].type_all);ret->child_list[3]=(yyvsp[-1].type_all);ret->child_list[4]=(yyvsp[0].type_all);
(yyval.type_all)=ret;}
#line 4652 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 87:
#line 2981 "parser.y" /* yacc.c:1646  */
    {fprintf(outprod, "ident-list --> IDENTARRAY expression RSQ\n");
if((yyvsp[-1].type_all)->type!=0){
    yyerror("ERROR20: Non integer size!");
    yyerrok;
} 
else if((yyvsp[-1].type_all)->num <=0){
    yyerror("ERROR21: NonPositive Array Size!");
    yyerrok;
} 
else{
    int done = insert_symtab((yyvsp[-2].type_all)->name, 1, 0, (yyvsp[-1].type_all)->num, 0, 0.00, ' ', scope);
    if(!done){
        yyerror("ERROR22: redeclaration of identifier!");
        yyerrok;
    }
}
typer* ret;
ret = create_node(4, 0.00, 3, "ident-list");
ret->child_list[0]=(yyvsp[-2].type_all);ret->child_list[1]=(yyvsp[-1].type_all);ret->child_list[2]=(yyvsp[0].type_all);
ret->namelistnum=1;ret->namelist[0]=strdup((yyvsp[-2].type_all)->name);
(yyval.type_all)=ret;}
#line 4678 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 88:
#line 3007 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "function -->  beforeargs argsAll RP\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "function");
    ret->num_children=3;
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);
    ret->type = (yyvsp[-2].type_all)->type;

    fte* callfunc = call_name_ptr;
    if(!callfunc){
        // error_caller("ERROR: Function not declared! ", $1->name);
        // yyerrok;
        break;
    }
    if((yyvsp[-1].type_all)->paramlistnum != callfunc->num_params){
        yyerror("ERROR: No. of parameters don't match!");
        yyerrok;
        break;
    }
    tte* temp1 = newtemp(callfunc->res_type);
    char* temp2 = (char *)malloc(120*sizeof(char));
    sprintf(temp2, "refparam %s\n", temp1->name);
    gen_code(temp2);

    memset(temp2, 0, 60);
    sprintf(temp2, "call %s %d\n", callfunc->func_name, callfunc->num_params+1);
    gen_code(temp2);
    (yyval.type_all)=ret;

}
#line 4715 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 89:
#line 3039 "parser.y" /* yacc.c:1646  */
    {fprintf(outerror, "Incorrect function call syntax! USAGE: func_name(arg1, arg2, arg3, ...);\n");}
#line 4721 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 90:
#line 3043 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "function -->  beforeargs argsAll RP\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "function");

    fte* func = functab_lookup((yyvsp[0].type_all)->name);
    if(!func){
        error_caller("ERROR: Function not declared! ", (yyvsp[0].type_all)->name);
        yyerrok;
        call_name_ptr = NULL;
        break;
    }
    ret->type = func->res_type;
    call_name_ptr = func;
    ret->num_children=1;
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 4744 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 3065 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "argsAll --> argsnonempty\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsAll");
    ret->num_children=1;
    ret->paramlistnum = (yyvsp[0].type_all)->paramlistnum;
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 4758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 3075 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "argsAll --> (nil)\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsAll");
    ret->num_children=1;
    ret->paramlistnum = 0;
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    (yyval.type_all)=ret;
}
#line 4772 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 3087 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "argsnonempty --> argsnonempty COMMA expression\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsnonempty");
    ret->num_children=3;
    ret->child_list[0]=(yyvsp[-2].type_all);
    ret->child_list[1]=(yyvsp[-1].type_all);
    ret->child_list[2]=(yyvsp[0].type_all);

    ret->paramlistnum = (yyvsp[-2].type_all)->paramlistnum+1;
    
    char* temp1 = (char *)malloc(120*sizeof(char));
    sprintf(temp1, "param %s\n", (yyvsp[0].type_all)->result->name);
    gen_code(temp1);

    int res = check_param_type((yyvsp[0].type_all)->type,1);
    if(!res){
        yyerror("ERROR: Parameter type doesn't match!");
        yyerrok;
        break;
    }

    (yyval.type_all)=ret;
}
#line 4801 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 3112 "parser.y" /* yacc.c:1646  */
    {
    fprintf(outprod, "argsnonempty --> expression\n");typer* ret;
    ret = create_node(1, 0.00, 1, "argsnonempty");
    ret->paramlistnum = 1;

    char* temp1 = (char *)malloc(120*sizeof(char));
    sprintf(temp1, "param %s\n", (yyvsp[0].type_all)->result->name);
    gen_code(temp1);

    int res = check_param_type((yyvsp[0].type_all)->type,1);
    if(!res){
        yyerror("ERROR: Parameter type doesn't match!");
        yyerrok;
        break;
    }
    ret->num_children=1;
    ret->child_list[0]=(yyvsp[0].type_all);
    (yyval.type_all)=ret;
}
#line 4825 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 4829 "parser.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 3134 "parser.y" /* yacc.c:1906  */


extern
void yyerror(const char *s) {
  PrintError(s);
}
