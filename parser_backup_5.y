
%{
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
char  *Names[] = { "_t0", "_t1", "_t2", "_t3", "_t4", "_t5", "_t6", "_t7", "_t8", "_t9", "_t10", "_t11", "_t12", "_t13", "_t14", "_t15", "_t16", "_t17", "_t18", "_t19" };   
char  **Namep  = Names;   
   
char  *newname()   
{   
    if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )   
    {   
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

extern FILE* outprod;
extern FILE* outerror;
extern int yylineno;
extern typer* root;

void gen_code(char* quad){
    quads[nextquad++] = strdup(quad);
}

tte* newtemp(int type){
    tte* tmp = (tte*)malloc(sizeof(tte));
    tmp->name = newname();
    tmp->type = type;
    temptab[temp_num++] = tmp;
    return tmp;
}

void print_code1 (){
    for(int i=0; i<nextquad; i++){
        printf("%s", quads[i]);
    }
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
    if(nameptr->type_ident==1){
        if(type==0){
            nameptr->arrayint = (int*)malloc(nameptr->dim*sizeof(int));
        }else if(type==1){
            nameptr->arraydouble = (double*)malloc(nameptr->dim*sizeof(double));
        }else if(type==2){
            nameptr->arraychar = (char*)malloc(nameptr->dim*sizeof(char));
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
    }else if(eletype == 1){
      temp->decimal = decimal;
    }else if(eletype == 2){
      temp->character = character;
    }
    temp->arraychar = NULL;
    temp->arrayint = NULL;
    temp->arraydouble = NULL;

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
    printf("------------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------------\n");
    for(int i=0; i<symtab_num; i++){
        if(symtab[i]->valid){
            printf("%s ", symtab[i]->name);
            printf("(%d)  >>  ", symtab[i]->level);
            if(symtab[i]->type_ident==0){
                if(symtab[i]->eletype==0){
                    printf("%d\n", symtab[i]->num);
                }else if(symtab[i]->eletype==1){
                    printf("%.2f\n", symtab[i]->decimal);
                }else if(symtab[i]->eletype==2){
                    printf("%c\n", symtab[i]->character);
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
    printf("------------------------------------------------------------------------\n");
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
       temp->paramlistnum=0;
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
    char* tmp = (char *)malloc(30*sizeof(char));
    strcat(tmp, msg);
    strcat(tmp, "'");
    strcat(tmp, arg);
    strcat(tmp, "'");
    yyerror(tmp);
}
%}

%union
{
       typer* type_all;
}


%type<type_all> RETURN VOID CHAR IDENTLP IDENTARRAY IDENT DOT NUM FLOAT LP RP PLUS MINUS ASSIGN DIV MULT IF THEN ELIF ELSE BEG END GT LT GTEQ LTEQ EQ NEQ FOR WHILE DO LSQ RSQ COMMA SEMICOLON COLON NAME PROCESSOR ISRUN SUBJOBS GETCLSP RUN DISCJOB ISA CLSP L1MEM ARCHTYPE L2MEM LINK STPNT ENDPNT BW CHCAP MEMORY GETAVMEM MEMTYPE MEMSIZE JOB GETMEM JOBID FLOPS DEADLINE MEMREQ AFFINITY CLUSTER PROCESSORS TOPO LINKBW LINKCAP INCR DCR ENDALL PROCESSORSLIST JOBS SCHALGO PRIOLIST FINDEADLINE LOADBALALGO SCHEDULER SCHEDULE INT_TYPE FLOAT_TYPE CHAR_TYPE
%type<type_all> beforeargs external_declarations program_code func_decl func_head decl_plist decl_pl decl_param beforeend beforestats ident-list argsnonempty statements statement statement-with-else selection selection_prime selection-with-else selection-with-else_prime opt_block expression expr_temp RA_TERM expression_prime term term_prime factor function argsAll type

%token RETURN
%token IDENT
%token DOT
%token NUM
%token FLOAT
%token CHAR
%token LP
%token RP
%token PLUS
%token MINUS
%token ASSIGN
%token DIV
%token MULT
%token IF
%token THEN
%token ELIF
%token ELSE
%token BEG
%token END
%token GT
%token LT
%token GTEQ
%token LTEQ
%token EQ
%token NEQ
%token FOR
%token WHILE
%token DO
%token LSQ
%token RSQ
%token COMMA
%token SEMICOLON
%token COLON
%token NAME
%token PROCESSOR
%token ISRUN
%token SUBJOBS
%token GETCLSP
%token RUN
%token DISCJOB
%token ISA
%token CLSP
%token L1MEM
%token ARCHTYPE
%token L2MEM
%token LINK
%token STPNT
%token ENDPNT
%token BW
%token CHCAP
%token MEMORY
%token GETAVMEM
%token MEMTYPE
%token MEMSIZE
%token JOB
%token GETMEM
%token JOBID
%token FLOPS
%token DEADLINE
%token MEMREQ
%token AFFINITY
%token CLUSTER
%token PROCESSORS
%token TOPO
%token LINKBW
%token LINKCAP
%token INCR
%token DCR
%token ENDALL
%token PROCESSORSLIST
%token JOBS
%token SCHALGO
%token PRIOLIST
%token FINDEADLINE
%token LOADBALALGO
%token SCHEDULER
%token SCHEDULE
%token INT_TYPE
%token FLOAT_TYPE
%token CHAR_TYPE
%token IDENTARRAY
%token IDENTLP
%token VOID
%left MINUS PLUS
%left MULT DIV
%left GT LT EQ NEQ GTEQ LTEQ

%start program_code
%%

program_code:
program_code external_declarations {
fprintf(outprod, "program_code --> program_code external_declarations\n");
 typer* ret;
ret = create_node(7, 0.00, 2, "program_code");
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;
root=ret;
// print_symbol_table();
}
| external_declarations {
fprintf(outprod, "program_code --> external_declarations\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "program_code");
ret->child_list[0]=$1;
$$=ret;
root=ret;
// print_symbol_table();

}
;

external_declarations:
type ident-list SEMICOLON {
fprintf(outprod, "external_declarations --> type ident-list SEMICOLON\n");
 typer* ret;
ret = create_node(7, 0.00, 3, "external_declarations");
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
}
| func_decl {
fprintf(outprod, "external_declarations --> func_decl\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "external_declarations");
ret->child_list[0]=$1;
$$=ret;
// print_func_table();
print_code1();
}
;

statements:
statement statements {yyerrok;
fprintf(outprod, "statements --> statement statements\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;}
| beforeend END statements {yyerrok;
fprintf(outprod, "statements --> BEG statements END statements\n");
 typer* ret;
ret = create_node(7, 0.00, 3, "statements");
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;}
| ENDALL {yyerrok;fprintf(outprod, "statements --> ENDALL\n");typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->child_list[0]=$1;$$=ret;}
| %empty {yyerrok;fprintf(outprod, "statements --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "statements");
 ret->decimal=0.00;
ret->child_list[0]=create_node(1,0.00,0,"NULL");
$$=ret;}
;

statement:
RETURN SEMICOLON 
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
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    $$=ret;
}
| RETURN expression SEMICOLON
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
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    $$=ret;
}
| IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENT ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
if($3->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up($1->name, scope);
        prl* prlptr = search_param($1->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", $1->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }
        if( $3->type==4){
            if(!$3->st_entry){
                break;
            }
            if(identptr->type_ident==1 || $3->st_entry->type_ident==1){
                yyerror("ERROR: Cannot assign array");
                yyerrok;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible(identptr->eletype, $3->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, $3->type);

        if(identptr->eletype==0){
            int b = *((int*)setter($3));
            identptr->num = b;
        }else if(identptr->eletype==1){
            double b = *((double*)setter($3));
            identptr->decimal = b;
        }else if(identptr->eletype==2){
            char b = *((char*)setter($3));
            identptr->character = b;
        }
     }else{
        break;
     }
ret->num_children=4;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
$$=ret;
}
| IDENT ASSIGN function SEMICOLON 
{
        fprintf(outprod, "statement --> IDENT ASSIGN function SEMICOLON\n");
        typer* ret;
        ret = create_node(1, 0.00, 1, "statement");

        ste* identptr = symtab_lookup_up($1->name, scope);
        prl* prlptr = search_param($1->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", $1->name);
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
        if($3->type==3){
            yyerror("ERROR: Void cannot be assigned!");
            yyerrok;
            break;
        }
        if(!coercible(identptr->eletype, $3->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, $3->type);
        ret->num_children=4;
        ret->child_list[0]=$1;
        ret->child_list[1]=$2;
        ret->child_list[2]=$3;
        ret->child_list[3]=$4;
        $$=ret;
}
| IDENTARRAY expression RSQ ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");

if($5->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up($1->name, scope);
        prl* prlptr = search_param($1->name);
        if(!identptr && !prlptr){
            error_caller("ERROR: Undeclared identifier! ", $1->name);
            yyerrok;
            break;
        }
        if(!identptr){
            identptr = (ste*)malloc(sizeof(ste));
            identptr->type_ident = 0;
            identptr->eletype = prlptr->param_type;
            identptr->name = strdup(prlptr->param_name);
        }
        if( $5->type==4){
            if(!$5->st_entry){
                break;
            }
            if(identptr->type_ident==1 || $5->st_entry->type_ident==1){
                yyerror("ERROR: Cannot assign array");
                yyerrok;
                break;
            }
        }
        if($5->type==4){
            if(!$5->st_entry){
                break;
            }
            $5->type = $5->st_entry->eletype;
        }
        if(!coercible(identptr->eletype, $5->type)){
            yyerror("ERROR : Type Mismatch!");
            yyerrok;
            break;
        }
        if($2->type!=0){
            yyerror("ERROR: Non Integer Indexing!");
            yyerrok;
            break;
        }
        if($2->num >= identptr->dim || $2->num < 0){
            yyerror("ERROR: Array index out of bounds!");
            yyerrok;
            break;
        }
        int ret_type = result_type(identptr->eletype, $5->type);

        if(identptr->eletype==0){
            int b = *((int*)setter($5));
            identptr->arrayint[$2->num] = b;
        }else if(identptr->eletype==1){
            double b = *((double*)setter($5));
            identptr->arraydouble[$2->num] = b;
        }else if(identptr->eletype==2){
            char b = *((char*)setter($5));
            identptr->arraychar[$2->num] = b;
        }
     }else{
        break;
     }

ret->num_children=6;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;
ret->child_list[5]=$6;$$=ret;}//{fprintf(outprod, ">>> %s[%f] = %.2f\n",$1, $3, $6);$$=ret;}
| expression SEMICOLON {fprintf(outprod, "statement --> expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $1);$$=ret;}
| selection {fprintf(outprod, "statement --> selection\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| function SEMICOLON {fprintf(outprod, "statement --> function SEMICOLON\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
| WHILE LP expression RP opt_block {fprintf(outprod, "statement --> WHILE LP expression RP opt_block \n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=5;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;
$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $3);$$=ret;}
| FOR LP statement expression SEMICOLON expression RP opt_block {fprintf(outprod, "statement --> FOR LP statement expression SEMICOLON expression RP opt_block\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=8;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;
ret->child_list[5]=$6;
ret->child_list[6]=$7;
ret->child_list[7]=$8;
$$=ret;}
| type ident-list SEMICOLON {fprintf(outprod, "statement --> type ident-list SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 3, "statement");
 $1->decimal = $3->decimal;
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
patchtype($2->namelist, $2->namelistnum, $1->type);}
//////////////////ERROR HANDLING////////////////////
| FOR LP error expression SEMICOLON expression RP opt_block {fprintf(outerror, "*****Error in initialization expression!\n");
yyerrok;}
| FOR LP statement error expression RP opt_block {fprintf(outerror, "*****Error in check expression!\n");
yyerrok;}
| FOR LP statement expression SEMICOLON error RP opt_block {fprintf(outerror, "*****Error in update expression!\n");
yyerrok;}
| FOR LP statement expression SEMICOLON expression RP error {fprintf(outerror, "*****Error in body of FOR loop!\n");
yyerrok;}
| IDENT ASSIGN expression error SEMICOLON {fprintf(outerror, "*****Unknown elements after assigned expression!\n");
yyerrok;}
| IDENT ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n");
yyerrok;}
| IDENT LSQ error RSQ ASSIGN expression SEMICOLON {fprintf(outerror, "*****Unsupported indexing!\n");
yyerrok;}
| IDENT LSQ expression RSQ ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n");
yyerrok;}
| error SEMICOLON {fprintf(outerror, "*****Wrong expression or function call!\n");
yyerrok;}
//////////////////////////////////////////////////
;


statement-with-else:
    RETURN SEMICOLON 
{
    fprintf(outprod, "statement --> RETURN SEMICOLON\n");typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=2;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    $$=ret;
}
| RETURN expression SEMICOLON
{
    fprintf(outprod, "statement --> RETURN expression SEMICOLON\n");typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=3;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    $$=ret;
}
| IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement-with-else --> IDENT ASSIGN expression SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");

            if($3->type!=ERROR_TYPE){
                ste* identptr = symtab_lookup_up($1->name, scope);
                prl* prlptr = search_param($1->name);
                if(!identptr && !prlptr){
                    error_caller("ERROR: Undeclared identifier! ", $1->name);
                    yyerrok;
                    break;
                }
                if(!identptr){
                    identptr = (ste*)malloc(sizeof(ste));
                    identptr->type_ident = 0;
                    identptr->eletype = prlptr->param_type;
                    identptr->name = strdup(prlptr->param_name);
                }
                if( $3->type==4){
                    if(!$3->st_entry){
                        break;
                    }
                    if(identptr->type_ident==1 || $3->st_entry->type_ident==1){
                        yyerror("ERROR: Cannot assign array");
                        yyerrok;
                        break;
                    }
                }
                if($3->type==4){
                    if(!$3->st_entry){
                        break;
                    }
                    $3->type = $3->st_entry->eletype;
                }
                if(!coercible(identptr->eletype, $3->type)){
                    yyerror("ERROR : Type Mismatch!");
                    yyerrok;
                    break;
                }
                int ret_type = result_type(identptr->eletype, $3->type);

                if(ret_type==0){
                    int b = *((int*)setter($3));
                    identptr->num = b;
                }else if(ret_type==1){
                    double b = *((double*)setter($3));
                    identptr->decimal = b;
                }else if(ret_type==2){
                    char b = *((char*)setter($3));
                    identptr->character = b;
                }
             }else{
                break;
             }

            ret->num_children=4;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;
            $$=ret;}
    | IDENTARRAY expression RSQ ASSIGN expression SEMICOLON {fprintf(outprod, "statement-with-else --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            if($5->type!=ERROR_TYPE){
                ste* identptr = symtab_lookup_up($1->name, scope);
                prl* prlptr = search_param($1->name);
                if(!identptr && !prlptr){
                    error_caller("ERROR: Undeclared identifier! ", $1->name);
                    yyerrok;
                    break;
                }
                if(!identptr){
                    identptr = (ste*)malloc(sizeof(ste));
                    identptr->type_ident = 0;
                    identptr->eletype = prlptr->param_type;
                    identptr->name = strdup(prlptr->param_name);
                }
                if( $5->type==4){
                    if(!$5->st_entry){
                        break;
                    }
                    if(identptr->type_ident==1 || $5->st_entry->type_ident==1){
                        yyerror("ERROR: Cannot assign array");
                        yyerrok;
                        break;
                    }
                }
                if($5->type==4){
                    if(!$5->st_entry){
                        break;
                    }
                    $5->type = $5->st_entry->eletype;
                }
                if(!coercible(identptr->eletype, $5->type)){
                    yyerror("ERROR : Type Mismatch!");
                    yyerrok;
                    break;
                }
                if($2->type!=0){
                    yyerror("ERROR: Non Integer Indexing!");
                    yyerrok;
                    break;
                }
                if($2->num >= identptr->dim || $2->num < 0){
                    yyerror("ERROR: Array index out of bounds!");
                    yyerrok;
                    break;
                }
                int ret_type = result_type(identptr->eletype, $5->type);

                if(ret_type==0){
                    int b = *((int*)setter($5));
                    identptr->arrayint[$2->num] = b;
                }else if(ret_type==1){
                    double b = *((double*)setter($5));
                    identptr->arraydouble[$2->num] = b;
                }else if(ret_type==2){
                    char b = *((char*)setter($5));
                    identptr->arraychar[$2->num] = b;
                }
             }else{
                break;
             }
            ret->num_children=6;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;
            ret->child_list[4]=$5;
            ret->child_list[5]=$6;
            $$=ret;}
    | expression SEMICOLON {fprintf(outprod, "statement-with-else --> expression SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            ret->decimal=$1->decimal;
            ret->num_children=2;
            ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}
    | selection-with-else {fprintf(outprod, "statement-with-else --> selection-with-else\n");typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            ret->decimal=0.00;
            ret->num_children=1;
            ret->child_list[0]=$1;$$=ret;}
    | function SEMICOLON {fprintf(outprod, "statement-with-else --> function SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            ret->decimal=0.00;
            ret->num_children=2;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;$$=ret;}
    | WHILE LP expression RP opt_block {fprintf(outprod, "statement-with-else --> WHILE LP expression RP opt_block \n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            ret->decimal=0.00;
            ret->num_children=4;
            ret->child_list[0]=$1;ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $3);$$=ret;}
    | FOR LP statement expression SEMICOLON expression RP opt_block {fprintf(outprod, "statement-with-else --> FOR LP statement expression SEMICOLON expression RP opt_block\n");typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");
            ret->decimal=0.00;
            ret->num_children=8;
            ret->child_list[0]=$1;ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;
            ret->child_list[4]=$5;
            ret->child_list[5]=$6;
            ret->child_list[6]=$7;ret->child_list[7]=$8;$$=ret;}//{fprintf(outprod, ">>> 1. %.2f     2. %.2f\n", $4, $6);$$=ret;}
    | type ident-list SEMICOLON {fprintf(outprod, "statement-with-else --> type ident-list SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 3, "statement-with-else");
            $1->decimal = $3->decimal;
            ret->decimal=0.00;
            ret->num_children=3;
            ret->child_list[0]=$1;ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            $$=ret;
            patchtype($2->namelist, $2->namelistnum, $1->type);}
//////////////////ERROR HANDLING////////////////////
    | FOR LP error expression SEMICOLON expression RP opt_block {fprintf(outerror, "*****Error in initialization expression!\n");
    yyerrok;}
    | FOR LP statement error expression RP opt_block {fprintf(outerror, "*****Error in check expression!\n");
    yyerrok;}
    | FOR LP statement expression SEMICOLON error RP opt_block {fprintf(outerror, "*****Error in update expression!\n");
    yyerrok;}
    | FOR LP statement expression SEMICOLON expression RP error {fprintf(outerror, "*****Error in body of FOR loop!\n");
    yyerrok;}
    | IDENT ASSIGN expression error SEMICOLON {fprintf(outerror, "*****Unknown elements after assigned expression!\n");
    yyerrok;}
    | IDENT ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n");
    yyerrok;}
    | IDENT LSQ error RSQ ASSIGN expression SEMICOLON {fprintf(outerror, "*****Unsupported indexing!\n");
    yyerrok;}
    | IDENT LSQ expression RSQ ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n");
    yyerrok;}
    | error SEMICOLON {fprintf(outerror, "*****Wrong expression or function call!\n");
    yyerrok;}
//////////////////////////////////////////////////
;

selection:
    IF LP expression RP selection_prime {fprintf(outprod, "selection --> IF LP expression RP selection_prime\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection");
            ret->num_children=5;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;
            ret->child_list[4]=$5;
            $$=ret;}
    | IF LP error RP selection_prime {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
;

selection_prime:    
    opt_block {fprintf(outprod, "selection_prime --> opt_block\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
            ret->decimal=0.00;
            ret->num_children=1;
            ret->child_list[0]=$1;$$=ret;}
    | opt_block ELSE opt_block {fprintf(outprod, "selection_prime --> opt_block ELSE opt_block\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
             ret->decimal=0.00;
            ret->num_children=3;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            $$=ret;}
    | opt_block ELSE statement {fprintf(outprod, "selection_prime --> opt_block ELSE statement\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
            ret->decimal=0.00;
            ret->num_children=3;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            $$=ret;}
    | statement  {fprintf(outprod, "selection_prime --> statement\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
            ret->decimal=0.00;
            ret->num_children=1;
            ret->child_list[0]=$1;
            $$=ret;}
    | statement-with-else ELSE opt_block {fprintf(outprod, "selection_prime --> statement-with-else ELSE opt_block\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
            ret->decimal=0.00;
            ret->num_children=3;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            $$=ret;}
    | statement-with-else ELSE statement {fprintf(outprod, "selection_prime --> statement-with-else ELSE statement\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection_prime");
            ret->decimal=0.00;
            ret->num_children=3;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            $$=ret;}
;

   
selection-with-else:
    IF LP expression RP selection-with-else_prime {fprintf(outprod, "selection-with-else --> IF LP expression RP selection-with-else_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "selection-with-else");
 // ret->decimal=0.00;
ret->num_children=5;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;$$=ret;}
;

selection-with-else_prime:
    statement-with-else ELSE opt_block {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE opt_block\n");typer* ret;
ret = create_node(0, 0.00, 1, "selection-with-else_prime");
 // ret->decimal=0.00;
ret->num_children=3;
ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
    | opt_block ELSE statement-with-else {fprintf(outprod, "selection-with-else_prime --> opt_block ELSE statement-with-else\n");typer* ret;
ret = create_node(0, 0.00, 1, "selection-with-else_prime");
 // ret->decimal=0.00;
ret->num_children=3;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;$$=ret;}
    | statement-with-else ELSE statement-with-else {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE statement-with-else\n");typer* ret;
ret = create_node(0, 0.00, 1, "selection-with-else_prime");
 // ret->decimal=0.00;
ret->num_children=3;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;$$=ret;}
;

opt_block:
beforeend END {fprintf(outprod, "opt_block --> beforeend END\n");typer* ret;
ret = create_node(7, 0.00, 1, "opt_block");
ret->num_children=2;
ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}
;

beforeend:
beforestats statements {fprintf(outprod, "beforeend --> beforestats statements\n");typer* ret;
ret = create_node(7, 0.00, 1, "beforeend");
print_symbol_table();
delete_var_level(scope);
scope--;
ret->num_children=2;
ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}
;

beforestats:
BEG {fprintf(outprod, "beforestats --> BEG\n");typer* ret;
ret = create_node(7, 0.00, 1, "beforestats");
ret->num_children=1;
scope++;
ret->child_list[0]=$1;$$=ret;}
;


func_decl:
func_head opt_block {fprintf(outprod, "func_decl --> func_head opt_block\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_decl");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
active_func_ptr = NULL;
$$=ret;}
;

func_head:
type IDENTLP decl_plist RP {fprintf(outprod, "func_head --> type IDENTLP decl_plist RP\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_head");
ret->num_children=4;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
int res = insert_functab($1->type, $2->name);
if(!res){
    yyerror("ERROR: Function already declared!");
    yyerrok;
    break;
}
if($3->type!=5){
    fte* func = functab_lookup($2->name);
    for(int i=0; i<$3->paramlistnum; i++){
        // printf("############################### %p #################\n\n", $3->paramlist[i]);
        insert_param(func, $3->paramlist[i]->param_type, $3->paramlist[i]->param_name);
    }
}
active_func_ptr = functab_lookup($2->name);
$$=ret;}
| VOID IDENTLP decl_plist RP {fprintf(outprod, "func_head --> VOID IDENTLP decl_plist RP\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_head");
ret->num_children=4;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
int res = insert_functab($1->type, $2->name);
if(!res){
    yyerror("ERROR: Function already declared!");
    yyerrok;
    break;
}
if($3->type!=5){
    fte* func = functab_lookup($2->name);
    for(int i=0; i<$3->paramlistnum; i++){
        insert_param(func, $3->paramlist[i]->param_type, $3->paramlist[i]->param_name);
    }
}
active_func_ptr = functab_lookup($2->name);
$$=ret;}
;

decl_plist:
decl_pl 
{
    fprintf(outprod, "decl_plist --> decl_pl\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_plist");
    ret->num_children=1;
    copy_paramlist(ret, $1);
    ret->paramlistnum--;
    ret->child_list[0]=$1;
    $$=ret;
}
| %empty 
{
    fprintf(outprod, "decl_plist --> (nil)\n");typer* ret;
    ret = create_node(5, 0.00, 1, "decl_plist");
    ret->decimal=0.00;
    ret->num_children=1;
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    $$=ret;
}
;

decl_pl:
decl_pl COMMA decl_param 
{
    fprintf(outprod, "decl_pl --> decl_pl COMMA decl_param\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_pl");

    ret->paramlistnum++;
    copy_paramlist(ret, $1);
    ret->paramlist[ret->paramlistnum-1] = $3->paramlist[0];

    ret->num_children=3;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    $$=ret;
}
| decl_param 

{
    fprintf(outprod, "decl_pl --> decl_param\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_pl");
    ret->num_children=1;
    ret->paramlistnum++;
    ret->paramlist[0] = $1->paramlist[0];
    ret->child_list[0]=$1;
    $$=ret;
}
;

decl_param:
type IDENT 
{
    fprintf(outprod, "decl_param --> type IDENT\n");typer* ret;
    ret = create_node(7, 0.00, 1, "decl_param");
    ret->paramlistnum=1;
    ret->paramlist[0] = create_param($1->type, $2->name);
    ret->num_children=2;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    $$=ret;
}
;

expression:
expr_temp 
{
    fprintf(outprod, "expression --> expr_temp\n");typer* ret;
    ret = create_node(0, 0.00, 1, "expression");
    ret->type = $1->type;
    ret->st_entry = $1->st_entry;
    ret->decimal = $1->decimal;
    ret->num = $1->num;
    ret->character = $1->character;
    ret->num_children=1;
    ret->child_list[0]=$1;
    ret->result = $1->result;
    $$=ret;
}

| expr_temp RA_TERM expr_temp 
{fprintf(outprod, "expression --> expr_temp RA_TERM expr_temp\n");typer* ret;
ret = create_node(0, 0.00, 1, "expression");
if($1->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            if($1->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            $1->type = $1->st_entry->eletype;
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible($1->type, $3->type)){
            yyerror("ERROR2 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($1->type, $3->type);
        ret->type = ret_type;

        if($2->ra_term_val==3){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);

            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }else if($2->ra_term_val==2){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }else if($2->ra_term_val==1){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }else if($2->ra_term_val==0){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }else if($2->ra_term_val==4){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }else if($2->ra_term_val==5){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(30*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(30*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
        }
        }

     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=3;ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
;


expr_temp:
term expression_prime {fprintf(outprod, "expr_temp --> term expression_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "expr_temp");
if($2->type==5){
    ret->type = $1->type;
    ret->st_entry = $1->st_entry;
    ret->decimal = $1->decimal;
    ret->num = $1->num;
    ret->character = $1->character; 

    ret->result = $1->result;   
}
else if($1->type!=ERROR_TYPE && $2->type!=ERROR_TYPE){
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            if($1->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($2->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            $1->type = $1->st_entry->eletype;
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if(!coercible($1->type, $2->type) || (!compatible_arithop($1->type, $2->type))){
            yyerror("ERROR4 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($1->type, $2->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($2));
            ret->num=(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($2));
            ret->decimal=(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($2));
            ret->character=(a+b);
        }

        tte* newtmp = newtemp(ret->type);


        char* tmp1 = (char *)malloc(60*sizeof(char));
        if($2->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, $1->result->name, $2->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, $1->result->name, $2->result->name);
        }

        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1] = $2;$$=ret;}
;


RA_TERM: 
LTEQ {fprintf(outprod, "RA_TERM --> LTEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
// ret->decimal=0.00;
ret->ra_term_val = 3;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| GTEQ {fprintf(outprod, "RA_TERM --> GTEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 2;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| LT  {fprintf(outprod, "RA_TERM --> LT\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 1;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| GT  {fprintf(outprod, "RA_TERM --> GT\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 0;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| EQ  {fprintf(outprod, "RA_TERM --> EQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 4;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| NEQ  {fprintf(outprod, "RA_TERM --> NEQ\n");typer* ret;
ret = create_node(1, 0.00, 1, "RA_TERM");
ret->ra_term_val = 5;
// ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
;


expression_prime:
PLUS term expression_prime {fprintf(outprod, "expression_prime --> PLUS term expression_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "expression_prime");
// printf(">>>>>>>>>> %d   %d\n", $2->type,$3->type);
 if($3->type==5){
    ret->type = $2->type;
    ret->st_entry = $2->st_entry;
    ret->decimal = $2->decimal;
    ret->num = $2->num;
    ret->character = $2->character; 

    ret->am_sd = 0;
    ret->result = $2->result;    
}
else if($2->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($2->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible($2->type, $3->type) || (!compatible_arithop($2->type, $3->type))){
            yyerror("ERROR6 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($2->type, $3->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter($2));
            int b = *((int*)setter($3));
            ret->num=(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=(a+b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(30*sizeof(char));
        if($3->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, $2->result->name, $3->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, $2->result->name, $3->result->name);
        }
        ret->am_sd = 0;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| MINUS term expression_prime {fprintf(outprod, "expression_prime --> MINUS term expression_prime \n");typer* ret;
ret = create_node(0, 0.00, 1, "expression_prime");
 if($3->type==5){
    ret->type = $2->type;
    ret->st_entry = $2->st_entry;
    ret->decimal = -$2->decimal;
    ret->num = -$2->num;
    ret->character = -$2->character;  

    ret->am_sd = 1;
    ret->result = $2->result;  
}
else if($2->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($2->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible($2->type, $3->type) || (!compatible_arithop($2->type, $3->type))){
            yyerror("ERROR8 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($2->type, $3->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter($2));
            int b = *((int*)setter($3));
            ret->num=-(a+b);
        }else if(ret->type==1){
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=-(a+b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=-(a+b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(30*sizeof(char));
        if($3->am_sd){
            sprintf(tmp1, "%s = %s - %s\n", newtmp->name, $2->result->name, $3->result->name);
        }else{
            sprintf(tmp1, "%s = %s + %s\n", newtmp->name, $2->result->name, $3->result->name);
        }
        ret->am_sd = 1;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }

ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
}
| %empty {fprintf(outprod, "expression_prime --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "expression_prime");
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

term:
factor term_prime {fprintf(outprod, "term --> factor term_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "term");
printf(">>>>>>>>> %d-%.2f\n", $2->num, $2->decimal);
 if($2->type==5){
    ret->type = $1->type;
    ret->st_entry = $1->st_entry;
    ret->decimal = $1->decimal;
    ret->num = $1->num;
    ret->character = $1->character;
    if($1->decimal==0){
        ret->decimal = $1->num;
    }else if($1->num==0){
        ret->num = $1->decimal;
    }
    ret->result = $1->result;
}
else if($1->type!=ERROR_TYPE && $2->type!=ERROR_TYPE){
    printf("%d  %.2f\n", $1->num, $2->decimal);
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            if($1->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($2->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($1->type==4){
            if(!$1->st_entry){
                break;
            }
            $1->type = $1->st_entry->eletype;
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if(!coercible($1->type, $2->type) || (!compatible_arithop($1->type, $2->type))){
            yyerror("ERROR10 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($1->type, $2->type);
        ret->type = ret_type;

        if(ret->type==0){
            // int a = *((int*)setter($1));
            // int b = *((int*)setter($2));
            // ret->num=(a*b);
            if(!$2->am_sd){
                int a = *((int*)setter($1));
                int b = *((int*)setter($2));
                ret->num=(a*b);
                ret->decimal = ret->num;
            }else{
                double a1 = $1->num;
                double b1 = $2->decimal;
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
            double a = *((double*)setter($1));
            double b = *((double*)setter($2));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($2));
            ret->character=(a*b);
        }

        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(30*sizeof(char));
        if($2->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, $1->result->name, $2->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, $1->result->name, $2->result->name);
        }
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
;

term_prime:
MULT factor term_prime {
    fprintf(outprod, "term_prime --> MULT factor term_prime\n");
    typer* ret;
ret = create_node(0, 0.00, 1, "term_prime");
    if($3->type==5){
        // printf("TRYWEASRASFA\n");
    ret->type = $2->type;
    ret->st_entry = $2->st_entry;
    ret->decimal = $2->decimal;
    ret->num = $2->num;
    if($2->decimal==0){
        ret->decimal = $2->num;
    }else if($2->num==0){
        ret->num = $2->decimal;
    }
    ret->character = $2->character; 
    ret->am_sd = 0;
    ret->result = $2->result;   
}
else if($2->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($2->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible($2->type, $3->type) || (!compatible_arithop($2->type, $3->type))){
            yyerror("ERROR12 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($2->type, $3->type);
        ret->type = ret_type;

        if(ret->type==0){
            if(!$3->am_sd){
                int a = *((int*)setter($2));
                int b = *((int*)setter($3));
                ret->num=(a*b);
                ret->decimal = ret->num;
            }else{
                double a1 = $2->num;
                double b1 = $3->decimal;
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
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=(a*b);
        }
        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(60*sizeof(char));
        if($3->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, $2->result->name, $3->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, $2->result->name, $3->result->name);
        }
        ret->am_sd = 0;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
    ret->num_children=3;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;

    $$=ret;
}
| DIV factor term_prime {
    fprintf(outprod, "term_prime --> DIV factor term_prime\n");
    typer* ret;
ret = create_node(0, 0.00, 1, "term_prime");
if($3->type==5){
    ret->type = $2->type;
    ret->st_entry = $2->st_entry;
    if($2->decimal)
        ret->decimal = 1/$2->decimal;
    if($2->num)
        ret->num = 1/$2->num;
    if($2->type==0){
        ret->decimal = 1.0/$2->num;
    }
    if($2->decimal==0){
        ret->decimal = 1.0/$2->num;
    }else if($2->num==0){
        ret->num = 1.0/$2->decimal;
    }
    ret->character = 1/$2->character;   

    ret->am_sd = 1;
    ret->result = $2->result;
}
else if($2->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
    printf("%d-%.2f   %d-%.2f\n", $2->num, $2->decimal,$3->num, $3->decimal);
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            if($3->st_entry->type_ident==1){
                yyerror("ERROR3: Cannot compute on array");
                yyerrok;
                ret->type=ERROR_TYPE;
                break;
            }
        }
        if($2->type==4){
            if(!$2->st_entry){
                break;
            }
            $2->type = $2->st_entry->eletype;
        }
        if($3->type==4){
            if(!$3->st_entry){
                break;
            }
            $3->type = $3->st_entry->eletype;
        }
        if(!coercible($2->type, $3->type) || (!compatible_arithop($2->type, $3->type))){
            yyerror("ERROR14 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($2->type, $3->type);
        ret->type = ret_type;

        if(ret->type==0){
            // int a = *((int*)setter($2));
            // int b = *((int*)setter($3));
            // printf("%d %.2f\n", $2->num, $3->decimal);
            double a1 = $2->num;
            double b1 = $3->decimal;
            double c1 = 1.0/(int)(a1*b1);
            ret->decimal = c1;
            ret->num = c1;
            // printf("%d %f ######\n",$2->num,$3->decimal );
        }else if(ret->type==1){
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=1/(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=1/(a*b);
        }
        tte* newtmp = newtemp(ret->type);
        char* tmp1 = (char *)malloc(60*sizeof(char));
        if($3->am_sd){
            sprintf(tmp1, "%s = %s / %s\n", newtmp->name, $2->result->name, $3->result->name);
        }else{
            sprintf(tmp1, "%s = %s * %s\n", newtmp->name, $2->result->name, $3->result->name);
        }
        ret->am_sd = 1;
        ret->result = newtmp;
        gen_code(tmp1);
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
}
| %empty {fprintf(outprod, "term_prime --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "term_prime");
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

factor:
NUM INCR { fprintf(outprod, "factor --> NUM INCR\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=$1->num++;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
$$=ret;
}
| NUM DCR { fprintf(outprod, "factor --> NUM DCR\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num = $1->num--;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
$$=ret;
}
| IDENT INCR {fprintf(outprod, "factor --> IDENT INCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
prl* prlptr = search_param($1->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", $1->name);
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
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(40*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s + 1\n%s = %s\n%s = %s - 1\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
$$=ret;
}
| IDENT DCR {fprintf(outprod, "factor --> IDENT DCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
prl* prlptr = search_param($1->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", $1->name);
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
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(40*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s - 1\n%s = %s\n%s = %s + 1\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
$$=ret;
}
| INCR IDENT {fprintf(outprod, "factor --> INCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($2->name, scope);
prl* prlptr = search_param($2->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", $2->name);
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
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(40*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s+1\n%s = %s\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name);
gen_code(tmp1);

$$=ret;
}
| DCR IDENT {fprintf(outprod, "factor -->  DCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($2->name, scope);
prl* prlptr = search_param($2->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", $2->name);
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
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(40*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s-1\n%s = %s\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name);
gen_code(tmp1);

$$=ret;
}
| INCR NUM {fprintf(outprod, "factor -->  INCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=++$2->num;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d+1\n", ret->result->name, ret->num);
gen_code(tmp1);
$$=ret;
}
| DCR NUM {fprintf(outprod, "factor -->  DCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=--$2->num;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d-1\n", ret->result->name, ret->num);
gen_code(tmp1);
$$=ret;
}
| NUM {fprintf(outprod, "factor --> NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=$1->num;
ret->num_children=1;
ret->child_list[0]=$1;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);
$$=ret;
}
| IDENT {fprintf(outprod, "factor --> IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
prl* prlptr = search_param($1->name);
if(!identptr && !prlptr){
    error_caller("ERROR: Undeclared identifier! ", $1->name);
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
ret->child_list[0]=$1;

ret->result = newtemp(identptr->eletype);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %s\n", ret->result->name, $1->name);
gen_code(tmp1);
$$=ret;
}
| CHAR {fprintf(outprod, "factor --> CHAR\n");
typer* ret;
ret = create_node(2, 0.00, 1, "factor");
ret->decimal=0.00;
ret->character = $1->character;
ret->num_children=1;
ret->child_list[0]=$1;

ret->result = newtemp(2);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %c\n", ret->result->name, ret->character);
gen_code(tmp1);
$$=ret;
}
| FLOAT {fprintf(outprod, "factor --> FLOAT\n");
typer* ret;
ret = create_node(1, 0.00, 1, "factor");
ret->decimal=$1->decimal;
ret->num_children=1;
ret->child_list[0]=$1;

ret->result = newtemp(1);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %.2f\n", ret->result->name, ret->decimal);
gen_code(tmp1);

$$=ret;
}
| LP expression RP {fprintf(outprod, "factor --> LP expression RP\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");ret->type=$2->type;

ret->type = $2->type;
ret->st_entry = $2->st_entry;
ret->decimal = $2->decimal;
ret->num = $2->num;
ret->character = $2->character; 

ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %s\n", ret->result->name, $2->result->name);
gen_code(tmp1);

$$=ret;
}
| MINUS NUM {fprintf(outprod, "factor --> MINUS NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=-($2->num);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(20*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);

ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
;

type:
INT_TYPE {fprintf(outprod, "type --> INT_TYPE\n");
typer* ret;
ret = create_node(0, 0.00, 1, "type");
ret->child_list[0]=$1;
$$=ret;}
| FLOAT_TYPE {fprintf(outprod, "type --> FLOAT_TYPE\n");
 typer* ret;
ret = create_node(1, 0.00, 1, "type");
ret->child_list[0]=$1;
$$=ret;}
| CHAR_TYPE {fprintf(outprod, "type --> CHAR_TYPE\n");
typer* ret;
ret = create_node(2, 0.00, 1, "type");
ret->child_list[0]=$1;
$$=ret;}
;

ident-list:
IDENT 
{
    fprintf(outprod, "ident-list -->  IDENT\n");
    int done = insert_symtab($1->name, 0, 0, 1, 0, 0.00, ' ', scope);
    if(!done){yyerror("ERROR15: redeclaration of identifier!");
    yyerrok;}typer* ret;
    ret = create_node(4, 0.00, 1, "ident-list");
    ret->child_list[0]=$1;
    ret->namelistnum=1;
    ret->namelist[0]=strdup($1->name);
    $$=ret;
}
| ident-list COMMA IDENT 
{
    fprintf(outprod, "ident-list --> ident-list COMMA IDENT \n");
    int done = insert_symtab($3->name, 0, 0, 1, 0, 0.00, ' ', scope);
    if(!done){yyerror("ERROR16: redeclaration of identifier!");
    yyerrok;} typer* ret;
    ret = create_node(4, 0.00, 3, "ident-list");
    ret->namelistnum++;
    copy_namelist(ret, $1);
    ret->namelist[ret->namelistnum-1]=strdup($3->name);
    ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;
    $$=ret;
}
| ident-list COMMA IDENTARRAY expression RSQ { fprintf(outprod, "ident-list --> ident-list COMMA IDENTARRAY expression RSQ\n");
// printf("SIZE>>>>>>>>>>>>>>>>>>>>>>>>  %d\n", $4->num);

if($4->type!=0){yyerror("ERROR17: Non integer size!");
yyerrok;} else if($4->num <=0){yyerror("ERROR18: NonPositive Array Size!");
yyerrok;} else{int done = insert_symtab($3->name, 1, 0, $4->num, 0, 0.00, ' ', scope);
if(!done){yyerror("ERROR19: redeclaration of identifier!");
yyerrok;} } typer* ret;
ret = create_node(4, 0.00, 5, "ident-list");
 ret->namelistnum++;copy_namelist(ret, $1);
 ret->namelist[ret->namelistnum-1]=strdup($3->name);
ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;ret->child_list[3]=$4;ret->child_list[4]=$5;
$$=ret;}
| IDENTARRAY expression RSQ {fprintf(outprod, "ident-list --> IDENTARRAY expression RSQ\n");
if($2->type!=0){
    yyerror("ERROR20: Non integer size!");
    yyerrok;
} 
else if($2->num <=0){
    yyerror("ERROR21: NonPositive Array Size!");
    yyerrok;
} 
else{
    int done = insert_symtab($1->name, 1, 0, $2->num, 0, 0.00, ' ', scope);
    if(!done){
        yyerror("ERROR22: redeclaration of identifier!");
        yyerrok;
    }
}
typer* ret;
ret = create_node(4, 0.00, 3, "ident-list");
ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;
ret->namelistnum=1;ret->namelist[0]=strdup($1->name);
$$=ret;}
;


function:
 beforeargs argsAll RP  
{
    fprintf(outprod, "function -->  beforeargs argsAll RP\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "function");
    ret->num_children=3;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    ret->type = $1->type;

    fte* callfunc = call_name_ptr;
    if(!callfunc){
        // error_caller("ERROR: Function not declared! ", $1->name);
        // yyerrok;
        break;
    }
    if($2->paramlistnum != callfunc->num_params){
        yyerror("ERROR: No. of parameters don't match!");
        yyerrok;
        break;
    }
    $$=ret;

}
 | IDENTLP error RP  {fprintf(outerror, "Incorrect function call syntax! USAGE: func_name(arg1, arg2, arg3, ...);\n");}
 ;

beforeargs:
IDENTLP {
    fprintf(outprod, "function -->  beforeargs argsAll RP\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "function");

    fte* func = functab_lookup($1->name);
    if(!func){
        error_caller("ERROR: Function not declared! ", $1->name);
        yyerrok;
        call_name_ptr = NULL;
        break;
    }
    ret->type = func->res_type;
    call_name_ptr = func;
    ret->num_children=1;
    ret->child_list[0]=$1;
    $$=ret;
}
;

 argsAll:
 argsnonempty 
 {
    fprintf(outprod, "argsAll --> argsnonempty\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsAll");
    ret->num_children=1;
    ret->paramlistnum = $1->paramlistnum;
    ret->child_list[0]=$1;
    $$=ret;
}
 | %empty 
 {
    fprintf(outprod, "argsAll --> (nil)\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsAll");
    ret->num_children=1;
    ret->paramlistnum = 0;
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    $$=ret;
}
 ;
argsnonempty:
argsnonempty COMMA expression 
{
    fprintf(outprod, "argsnonempty --> argsnonempty COMMA expression\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "argsnonempty");
    ret->num_children=3;
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;

    ret->paramlistnum = $1->paramlistnum+1;
    int res = check_param_type($3->type,1);
    if(!res){
        yyerror("ERROR: Parameter type doesn't match!");
        yyerrok;
        break;
    }

    $$=ret;
}
 | expression 
 {
    fprintf(outprod, "argsnonempty --> expression\n");typer* ret;
    ret = create_node(1, 0.00, 1, "argsnonempty");
    ret->paramlistnum = 1;
    int res = check_param_type($1->type,1);
    if(!res){
        yyerror("ERROR: Parameter type doesn't match!");
        yyerrok;
        break;
    }
    ret->num_children=1;
    ret->child_list[0]=$1;
    $$=ret;
}
;


%%

extern
void yyerror(const char *s) {
  PrintError(s);
}
