
%{
// int yyerror(const char *);
int yylex(void);
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#include <math.h>
#include <stdio.h>
#include "string.h"
#include <stdlib.h>
#include "ccalc.h"
char* vars[100];
double vals[100];
char* argslist[100];
char* argsvals[100];
int argscount = 0;
int countvars = 0;

extern FILE* outprod;
extern FILE* outerror;
extern int yylineno;
extern typer* root;
double get_value(char* vars[], double vals[], int count, char* varname){
       double ans = 0.00;
       for(int i=0; i<count; i++){
              if(strcmp(vars[i], varname)==0){
                     ans = vals[i];
              }
       }
       return ans;
}

// typedef  type_aller;

typer* create_node(int type, double decimal, int num_children, char* tag){
       typer* temp = (typer *)malloc(sizeof(typer));
       temp->type = type;
       temp->num = 0;
       temp->decimal = decimal;
       temp->string = NULL;
       temp->tag = tag;
       temp->num_children=num_children;
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
       for(int i=0; i<10; i++)
              temp->child_list[i] = NULL;
       return temp;
}

%}

%union
{
       typer* type_all;
}


%type<type_all> IDENT DOT NUM FLOAT STRING LP RP PLUS MINUS ASSIGN DIV MULT IF THEN ELIF ELSE BEG END GT LT GTEQ LTEQ EQ NEQ FOR WHILE DO LSQ RSQ COMMA SEMICOLON COLON NAME PROCESSOR ISRUN SUBJOBS GETCLSP RUN DISCJOB ISA CLSP L1MEM ARCHTYPE L2MEM LINK STPNT ENDPNT BW CHCAP MEMORY GETAVMEM MEMTYPE MEMSIZE JOB GETMEM JOBID FLOPS DEADLINE MEMREQ AFFINITY CLUSTER PROCESSORS TOPO LINKBW LINKCAP INCR DCR ENDALL PROCESSORSLIST JOBS SCHALGO PRIOLIST FINDEADLINE LOADBALALGO SCHEDULER SCHEDULE INT_TYPE FLOAT_TYPE CHAR_TYPE
%type<type_all> statements statement statement-with-else selection selection_prime selection-with-else selection-with-else_prime opt_block expression expr_temp RA_TERM expression_prime term term_prime factor array array_prime constructor function argsAll method argsRUN argsISRUN argsSUBJOBS argsGETCLSP argsDISCJOB argsGETAVMEM argsGETMEM argsPROC archterm nameterm isaterm clspterm l1memterm l2memterm argsLINK stpntterm endpntterm bwterm chcapterm argsMEM memtypeterm memsizeterm argsJOB jobidterm flopterm deadterm memreqterm affineterm argsCLUSTER processorsterm topoterm linkbwterm linkcapterm argsnonempty argsScheduler argsSchedule processors_listTerm jobsTerm scheduling_algoTerm priority_listTerm final_deadlineTerm load_balancing_algoTerm type ident-list


%token IDENT
%token DOT
%token NUM
%token FLOAT
%token STRING
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


%left MINUS PLUS
%left MULT DIV
%left GT LT EQ NEQ GTEQ LTEQ

%start statements
%%
statements:
statement statements {yyerrok; fprintf(outprod, "statements --> statement statements\n");  typer* ret; ret = create_node(1, 0.00, 1, "statements"); ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2; $$=ret; root=ret;}
| ENDALL {yyerrok;fprintf(outprod, "statements --> ENDALL\n");typer* ret; ret = create_node(1, 0.00, 1, "statements"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret; root=ret;}
| %empty {yyerrok;fprintf(outprod, "statements --> (nil)\n");typer* ret; ret = create_node(1, 0.00, 1, "statements"); ret->type=1; ret->decimal=0.00;  ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL"); $$=ret; root=ret;}
;
statement:
IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENT ASSIGN expression SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement"); ret->type=1; $1->type = 1; $1->decimal = $3->decimal; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
| IDENT LSQ expression RSQ ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENT LSQ expression RSQ ASSIGN expression SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement");ret->type=1; ret->decimal=0.00; ret->num_children=7; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7;$$=ret;}//{fprintf(outprod, ">>> %s[%f] = %.2f\n",$1, $3, $6);$$=ret;}
| expression SEMICOLON {fprintf(outprod, "statement --> expression SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement");ret->type=1; ret->decimal=$1->decimal; ret->num_children=2; ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $1);$$=ret;}
| selection {fprintf(outprod, "statement --> selection\n");typer* ret; ret = create_node(1, 0.00, 1, "statement"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
 | function SEMICOLON {fprintf(outprod, "statement --> function SEMICOLON\n");typer* ret; ret = create_node(1, 0.00, 1, "statement"); ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| WHILE LP expression RP opt_block {fprintf(outprod, "statement --> WHILE LP expression RP opt_block \n");typer* ret; ret = create_node(1, 0.00, 1, "statement"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $3);$$=ret;}
| FOR LP statement expression SEMICOLON expression RP opt_block {fprintf(outprod, "statement --> FOR LP statement expression SEMICOLON expression RP opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "statement"); ret->type=1; ret->decimal=0.00; ret->num_children=8; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7;ret->child_list[7]=$8;$$=ret;}//{fprintf(outprod, ">>> 1. %.2f     2. %.2f\n", $4, $6);$$=ret;}
| type ident-list
//////////////////ERROR HANDLING////////////////////
| FOR LP error expression SEMICOLON expression RP opt_block {fprintf(outerror, "*****Error in initialization expression!\n"); yyerrok;}
| FOR LP statement error expression RP opt_block {fprintf(outerror, "*****Error in check expression!\n"); yyerrok;}
| FOR LP statement expression SEMICOLON error RP opt_block {fprintf(outerror, "*****Error in update expression!\n"); yyerrok;}
| FOR LP statement expression SEMICOLON expression RP error {fprintf(outerror, "*****Error in body of FOR loop!\n"); yyerrok;}
| IDENT ASSIGN expression error SEMICOLON {fprintf(outerror, "*****Unknown elements after assigned expression!\n"); yyerrok;}
| IDENT ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n"); yyerrok;}
| IDENT LSQ error RSQ ASSIGN expression SEMICOLON {fprintf(outerror, "*****Unsupported indexing!\n"); yyerrok;}
| IDENT LSQ expression RSQ ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n"); yyerrok;}
| error SEMICOLON {fprintf(outerror, "*****Wrong expression or function call!\n"); yyerrok;}
//////////////////////////////////////////////////
;

statement-with-else:
IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement-with-else --> IDENT ASSIGN expression SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else"); ret->type=1; $1->type = 1; $1->decimal = $3->decimal; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
| IDENT LSQ expression RSQ ASSIGN expression SEMICOLON {fprintf(outprod, "statement-with-else --> IDENT LSQ expression RSQ ASSIGN expression SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else");ret->type=1; ret->decimal=0.00; ret->num_children=7; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7;$$=ret;}//{fprintf(outprod, ">>> %s[%f] = %.2f\n",$1, $3, $6);$$=ret;}
| expression SEMICOLON {fprintf(outprod, "statement-with-else --> expression SEMICOLON\n");typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else"); ret->type=1; ret->decimal=$1->decimal; ret->num_children=2; ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $1);$$=ret;}
| selection-with-else {fprintf(outprod, "statement-with-else --> selection-with-else\n");typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
 | function SEMICOLON {fprintf(outprod, "statement-with-else --> function SEMICOLON\n"); typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| WHILE LP expression RP opt_block {fprintf(outprod, "statement-with-else --> WHILE LP expression RP opt_block \n"); typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else");ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $3);$$=ret;}
| FOR LP statement expression SEMICOLON expression RP opt_block {fprintf(outprod, "statement-with-else --> FOR LP statement expression SEMICOLON expression RP opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "statement-with-else"); ret->type=1; ret->decimal=0.00; ret->num_children=8; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7;ret->child_list[7]=$8;$$=ret;}//{fprintf(outprod, ">>> 1. %.2f     2. %.2f\n", $4, $6);$$=ret;}
| type ident-list
//////////////////ERROR HANDLING////////////////////
| FOR LP error expression SEMICOLON expression RP opt_block {fprintf(outerror, "*****Error in initialization expression!\n"); yyerrok;}
| FOR LP statement error expression RP opt_block {fprintf(outerror, "*****Error in check expression!\n"); yyerrok;}
| FOR LP statement expression SEMICOLON error RP opt_block {fprintf(outerror, "*****Error in update expression!\n"); yyerrok;}
| FOR LP statement expression SEMICOLON expression RP error {fprintf(outerror, "*****Error in body of FOR loop!\n"); yyerrok;}
| IDENT ASSIGN expression error SEMICOLON {fprintf(outerror, "*****Unknown elements after assigned expression!\n"); yyerrok;}
| IDENT ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n"); yyerrok;}
| IDENT LSQ error RSQ ASSIGN expression SEMICOLON {fprintf(outerror, "*****Unsupported indexing!\n"); yyerrok;}
| IDENT LSQ expression RSQ ASSIGN error SEMICOLON {fprintf(outerror, "*****Error in assigned expression!\n"); yyerrok;}
| error SEMICOLON {fprintf(outerror, "*****Wrong expression or function call!\n"); yyerrok;}
//////////////////////////////////////////////////
;
selection:
    IF LP expression RP selection_prime {fprintf(outprod, "selection --> IF LP expression RP selection_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "selection"); ret->type=1; ret->decimal=0.00; ret->num_children=5; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5;$$=ret;}
| IF LP error RP selection_prime {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
;
selection_prime:    
opt_block {fprintf(outprod, "selection_prime --> opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| opt_block ELSE opt_block {fprintf(outprod, "selection_prime --> opt_block ELSE opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| opt_block ELSE statement {fprintf(outprod, "selection_prime --> opt_block ELSE statement\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| statement  {fprintf(outprod, "selection_prime --> statement\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| statement-with-else ELSE opt_block {fprintf(outprod, "selection_prime --> statement-with-else ELSE opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| statement-with-else ELSE statement {fprintf(outprod, "selection_prime --> statement-with-else ELSE statement\n");typer* ret; ret = create_node(1, 0.00, 1, "selection_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
;    
selection-with-else:
    IF LP expression RP selection-with-else_prime {fprintf(outprod, "selection-with-else --> IF LP expression RP selection-with-else_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "selection-with-else"); ret->type=1; ret->decimal=0.00; ret->num_children=5; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5;$$=ret;}
;
selection-with-else_prime:
    statement-with-else ELSE opt_block {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE opt_block\n");typer* ret; ret = create_node(1, 0.00, 1, "selection-with-else_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
    | opt_block ELSE statement-with-else {fprintf(outprod, "selection-with-else_prime --> opt_block ELSE statement-with-else\n");typer* ret; ret = create_node(1, 0.00, 1, "selection-with-else_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}
    | statement-with-else ELSE statement-with-else {fprintf(outprod, "selection-with-else_prime --> statement-with-else ELSE statement-with-else\n");typer* ret; ret = create_node(1, 0.00, 1, "selection-with-else_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}
;
opt_block:
BEG statements END {fprintf(outprod, "opt_block --> BEG statements END\n");typer* ret; ret = create_node(1, 0.00, 1, "opt_block"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
;

expression:
expr_temp {fprintf(outprod, "expression --> expr_temp\n");typer* ret; ret = create_node(1, 0.00, 1, "expression"); ret->type=1; ret->decimal=$1->decimal; ret->num_children=1;ret->child_list[0]=$1;$$=ret;}
| expr_temp RA_TERM expr_temp {fprintf(outprod, "expression --> expr_temp RA_TERM expr_temp\n");typer* ret; ret = create_node(1, 0.00, 1, "expression"); ret->type=1; ret->decimal=0.00; ret->num_children=3;ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
;

expr_temp:
term expression_prime {fprintf(outprod, "expr_temp --> term expression_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "expr_temp"); ret->type = 1; ret->decimal=$1->decimal+$2->decimal; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1] = $2;$$=ret;}
 | constructor {fprintf(outprod, "expr_temp --> constructor\n");typer* ret; ret = create_node(1, 0.00, 1, "expr_temp"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
 | IDENT DOT method {fprintf(outprod, "expr_temp --> IDENT DOT method\n");typer* ret; ret = create_node(1, 0.00, 1, "expr_temp"); ret->type=1; ret->decimal = 0.00; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1] = $2; ret->child_list[2] = $3;$$=ret;}
;

RA_TERM: 
LTEQ {fprintf(outprod, "RA_TERM --> LTEQ\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| GTEQ {fprintf(outprod, "RA_TERM --> GTEQ\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| LT  {fprintf(outprod, "RA_TERM --> LT\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| GT  {fprintf(outprod, "RA_TERM --> GT\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| EQ  {fprintf(outprod, "RA_TERM --> EQ\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| NEQ  {fprintf(outprod, "RA_TERM --> NEQ\n");typer* ret; ret = create_node(1, 0.00, 1, "RA_TERM");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
;

expression_prime:
PLUS term expression_prime {fprintf(outprod, "expression_prime --> PLUS term expression_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "expression_prime"); ret->type=1; ret->decimal=$2->decimal+$3->decimal; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| MINUS term expression_prime {fprintf(outprod, "expression_prime --> MINUS term expression_prime \n");typer* ret; ret = create_node(1, 0.00, 1, "expression_prime"); ret->type=1; ret->decimal=-($2->decimal+$3->decimal); ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| %empty {fprintf(outprod, "expression_prime --> (nil)\n");typer* ret; ret = create_node(1, 0.00, 1, "expression_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
term:
factor term_prime {fprintf(outprod, "term --> factor term_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "term"); ret->type=1; ret->decimal=$1->decimal*$2->decimal; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
;
term_prime:
MULT factor term_prime {fprintf(outprod, "term_prime --> MULT factor term_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "term_prime"); ret->type=1; ret->decimal=$2->decimal*$3->decimal; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| DIV factor term_prime {fprintf(outprod, "term_prime --> DIV factor term_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "term_prime"); ret->type=1; ret->decimal=1/($2->decimal+$3->decimal); ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| %empty {fprintf(outprod, "term_prime --> (nil)\n");typer* ret; ret = create_node(1, 0.00, 1, "term_prime"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
factor:
NUM INCR { fprintf(outprod, "factor --> NUM INCR\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor"); ret->decimal=$1->decimal+1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| NUM DCR { fprintf(outprod, "factor --> NUM DCR\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal-1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| IDENT INCR {fprintf(outprod, "factor --> IDENT INCR\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal+1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| IDENT DCR {fprintf(outprod, "factor --> IDENT DCR\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal-1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}

| INCR IDENT {fprintf(outprod, "factor --> INCR IDENT\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal+1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| DCR IDENT {fprintf(outprod, "factor -->  DCR IDENT\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal-1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| INCR NUM {fprintf(outprod, "factor -->  INCR NUM\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal+1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| DCR NUM {fprintf(outprod, "factor -->  DCR NUM\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal-1; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}

| NUM {fprintf(outprod, "factor --> NUM\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| IDENT {fprintf(outprod, "factor --> IDENT\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal; ret->num_children=1; ret->child_list[0]=$1; $$=ret;}
| STRING {fprintf(outprod, "factor --> STRING\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
| FLOAT {fprintf(outprod, "factor --> FLOAT\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$1->decimal; ret->num_children=1; ret->child_list[0]=$1; $$=ret;}
| LSQ array RSQ {fprintf(outprod, "factor --> LSQ array RSQ\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}
| LP expression RP {fprintf(outprod, "factor --> LP expression RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=$2->decimal; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}
| MINUS NUM {fprintf(outprod, "factor --> MINUS NUM\n"); typer* ret; ret = create_node(1, 0.00, 1, "factor");ret->type=1; ret->decimal=-($2->decimal); ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
;
array:
expression array_prime {fprintf(outprod, "array --> IDENT array_prime\n"); typer* ret; ret = create_node(1, 0.00, 1, "array");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2; $$=ret;}
;
array_prime:
COMMA expression array_prime {fprintf(outprod, "array_prime --> COMMA IDENT array_prime\n");typer* ret; ret = create_node(1, 0.00, 1, "array_prime"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; $$=ret;}
| %empty {fprintf(outprod, "array_prime --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "array_prime");ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL"); $$=ret;}
;

type:
INT_TYPE
| FLOAT_TYPE
| CHAR_TYPE
;

ident-list:
IDENT 
| IDENT COMMA ident-list
| IDENT LSQ array RSQ
| IDENT LSQ array RSQ COMMA ident-list
;



constructor:
 PROCESSOR LP argsPROC RP {fprintf(outprod, "constructor -->  PROCESSOR LP argsPROC RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; $$=ret;}
 | PROCESSOR LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Processor constructor!\nUSAGE: Processor([isa=] <arg1>, [clock_speed :] <arg2>, [l1_memory=] <arg3>\n\t\t[ ,[l2_memory=] <arg4> ][ ,[architecture_type=] <arg5>][ ,[name=] <arg6>]);\n"); yyerrok;}
 | LINK LP argsLINK RP {fprintf(outprod, "constructor --> LINK LP argsLINK RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;ret->child_list[3]=$4; $$=ret;}
 | LINK LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Link constructor!\nUSAGE: Link([start_point=] <arg1>, [end_point=] <arg2>, [bandwitdth=] <arg3> , [channel_capacity=] <arg4>[ ,[name=] <arg5>])\n"); yyerrok;}
 | MEMORY LP argsMEM RP {fprintf(outprod, "constructor --> MEMORY LP argsMEM RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;ret->child_list[3]=$4; $$=ret;}
 | MEMORY LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Memory constructor!\nUSAGE: Memory([memory_type=] <arg1>, [mem_size=] <arg2>[ ,[name=] <arg3>]);\n"); yyerrok;}
 | JOB LP argsJOB RP {fprintf(outprod, "constructor --> JOB LP argsJOB RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | JOB LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Job constructor!\nUSAGE: Job([job_id=] <arg1>, [flops_required=] <arg2>, [deadline=] <arg3>, [mem_required=] <arg4>, [affinity=] <arg5>);\n"); yyerrok;}
 | CLUSTER LP argsCLUSTER RP {fprintf(outprod, "constructor --> CLUSTER LP argsCLUSTER RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | CLUSTER LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Cluster constructor!\nUSAGE: Cluster([processors=] <arg1>, [topology=] <arg2>, [link_bandwidth=] <arg3>, [link_capacity=] <arg4>[ ,[name=] <arg5>);\n"); yyerrok;}
 | SCHEDULER LP argsScheduler RP {fprintf(outprod, "constructor --> SCHEDULER LP argsScheduler RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "constructor"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | SCHEDULER LP error RP {fprintf(outerror, "*****Incorrect arguments passed to Scheduler constructor!\nUSAGE: Scheduler([scheduling_algo=] <arg1>, [load_balancing_algo=] <arg2>[, [name=] <arg3>]);\n"); yyerrok;}
;
function:
 RUN LP argsRUN RP {fprintf(outprod, "function --> RUN LP argsRUN RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "function"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | RUN LP error RP {fprintf(outerror, "*****Incorrect arguments passed to 'run' function! USAGE: run(proc1);, run([proc1, proc2, ...., procN]);\n");}
 | DISCJOB LP argsDISCJOB RP {fprintf(outprod, "function --> DISCJOB LP argsDISCJOB RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "function"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | DISCJOB LP error RP {fprintf(outerror, "*****Incorrect arguments passed to 'discard_job' function! USAGE: discard_job(job1);");}
 | IDENT LP argsAll RP  {fprintf(outprod, "function -->  IDENT LP argsAll RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "function"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | IDENT LP error RP  {fprintf(outerror, "Incorrect function call syntax! USAGE: func_name(arg1, arg2, arg3, ...);\n");}
 ;
 argsAll:
 argsnonempty {fprintf(outprod, "argsAll --> argsnonempty\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsAll"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
 | %empty {fprintf(outprod, "argsAll --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsAll"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
argsnonempty:
 IDENT ASSIGN expression COMMA argsnonempty {fprintf(outprod, "argsnonempty --> IDENT ASSIGN expression COMMA argsAll\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsnonempty"); ret->type=1; ret->decimal=0.00; ret->num_children=5; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;ret->child_list[4]=$5;$$=ret;}
 | expression COMMA argsnonempty {fprintf(outprod, "argsnonempty --> expression COMMA argsAll\n");  typer* ret; ret = create_node(1, 0.00, 1, "argsnonempty"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}
 | expression {fprintf(outprod, "argsnonempty --> expression\n");typer* ret; ret = create_node(1, 0.00, 1, "argsnonempty"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
 | IDENT ASSIGN expression {fprintf(outprod, "argsnonempty --> IDENT ASSIGN expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsnonempty"); ret->type=1; ret->decimal=0.00; ret->num_children=3; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;$$=ret;}

method: 
 ISRUN LP argsISRUN RP {fprintf(outprod, "method --> ISRUN LP argsISRUN RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | SUBJOBS LP argsSUBJOBS RP {fprintf(outprod, "method --> SUBJOBS LP argsSUBJOBS\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | GETCLSP LP argsGETCLSP RP {fprintf(outprod, "method --> GETCLSP LP argsGETCLSP RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | GETAVMEM LP argsGETAVMEM RP {fprintf(outprod, "method --> GETAVMEM LP argsGETAVMEM RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;} 
 | GETMEM LP argsGETMEM RP {fprintf(outprod, "method --> GETMEM LP argsGETMEM RP\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 | SCHEDULE LP argsSchedule RP {fprintf(outprod, "method --> SCHEDULE LP argsSchedule RP\n");typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4;$$=ret;}
 ;
 argsRUN:
  expression {fprintf(outprod, "argsRUN --> expression\n");typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
  ;
argsISRUN:
 %empty {fprintf(outprod, "argsISRUN --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsISRUN"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
argsSUBJOBS: 
expression {fprintf(outprod, "argsSUBJOBS --> expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
;
argsGETCLSP:
 %empty {fprintf(outprod, "argsGETCLSP --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsGETCLSP"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
argsDISCJOB:
expression {fprintf(outprod, "argsDISCJOB --> expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "method"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
;
argsGETAVMEM:
%empty {fprintf(outprod, "argsGETAVMEM --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsGETAVMEM"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
argsGETMEM:
 %empty {fprintf(outprod, "argsGETMEM --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsGETMEM"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
argsPROC:
isaterm expression COMMA clspterm expression COMMA l1memterm expression l2memterm {fprintf(outprod, "argsProc --> isaterm expression COMMA clspterm expression COMMA l1memterm expression l2memterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsProc"); ret->type=1; ret->decimal=0.00; ret->num_children=9; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7; ret->child_list[7]=$8; ret->child_list[8]=$9;$$=ret;}
;

archterm:
COMMA ARCHTYPE ASSIGN expression nameterm {fprintf(outprod, "archterm --> COMMA ARCHTYPE ASSIGN expression nameterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "archterm"); ret->type=1; ret->decimal=0.00; ret->num_children=5; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5;$$=ret;}
| nameterm {fprintf(outprod, "archterm --> nameterm\n");typer* ret; ret = create_node(1, 0.00, 1, "archterm"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
;
nameterm:
COMMA NAME ASSIGN expression {fprintf(outprod, "nameterm --> COMMA NAME ASSIGN expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "nameterm"); ret->type=1; ret->decimal=0.00; ret->num_children=4; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3;ret->child_list[3]=$4;$$=ret;}
| %empty {fprintf(outprod, "nameterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "nameterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
| COMMA expression {fprintf(outprod, "nameterm --> COMMA epxression\n");typer* ret; ret = create_node(1, 0.00, 1, "nameterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
;
isaterm:
ISA ASSIGN {fprintf(outprod, "isaterm --> ISA ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "isaterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "isaterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "isaterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
clspterm:
CLSP COLON {fprintf(outprod, "clspterm --> CLSP COLON\n");typer* ret; ret = create_node(1, 0.00, 1, "clspterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "clspterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "clspterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
l1memterm:
L1MEM ASSIGN {fprintf(outprod, "l1memterm --> L1MEM ASSIGN\n");typer* ret; ret = create_node(1, 0.00, 1, "l1memterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "l1memterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "l1memterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
l2memterm:
COMMA L2MEM ASSIGN expression archterm {fprintf(outprod, "l2memterm --> COMMA L2MEM ASSIGN expression archterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "l2memterm"); ret->type=1; ret->decimal=0.00; ret->num_children=5; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5;$$=ret;}
| archterm {fprintf(outprod, "l2memterm --> archterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "l2memterm"); ret->type=1; ret->decimal=0.00; ret->num_children=1; ret->child_list[0]=$1;$$=ret;}
;

argsLINK:
stpntterm expression COMMA endpntterm expression COMMA bwterm expression chcapterm nameterm {fprintf(outprod, "argsLINK -> stpntterm expression COMMA endpntterm expression COMMA bwterm expression chcapterm nameterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsProc"); ret->type=1; ret->decimal=0.00; ret->num_children=9; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7; ret->child_list[7]=$8; ret->child_list[8]=$9; ret->child_list[9]=$10; $$=ret;}
;
stpntterm:
STPNT ASSIGN {fprintf(outprod, "stpntterm → STPNT  ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "stpntterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "stpntterm → (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "stpntterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
endpntterm:
ENDPNT  ASSIGN {fprintf(outprod, "endpntterm → ENDPNT  ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "endpntterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "endpntterm → (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "endpntterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
bwterm:
 BW  ASSIGN {fprintf(outprod, "bwterm → BW  ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "bwterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
 | %empty {fprintf(outprod, "bwterm → (nil)\n");typer* ret; ret = create_node(1, 0.00, 1, "bwterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
chcapterm:
CHCAP  ASSIGN {fprintf(outprod, "chcapterm → CHCAP  ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "chcapterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "chcapterm → (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "chcapterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

argsMEM:
 memtypeterm  expression COMMA memsizeterm  expression nameterm {fprintf(outprod, "argsMEM → memtypeterm  expression COMMA memsizeterm  expression nameterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsMEM"); ret->type=1; ret->decimal=0.00; ret->num_children=6; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6;$$=ret;}
 ;
memtypeterm:
MEMTYPE ASSIGN {fprintf(outprod, "memtypeterm → MEMTYPE ASSIGN\n");typer* ret; ret = create_node(1, 0.00, 1, "memtypeterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "memtypeterm → (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "memtypeterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
memsizeterm:
 MEMSIZE ASSIGN {fprintf(outprod, "memsizeterm --> MEMSIZE ASSIGN\n");typer* ret; ret = create_node(1, 0.00, 1, "memsizeterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
 | %empty {fprintf(outprod, "memsizeterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "memsizeterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;

 argsJOB:
  jobidterm expression COMMA flopterm expression COMMA deadterm expression COMMA memreqterm expression COMMA affineterm expression {fprintf(outprod, "argsJOB --> jobidterm expression COMMA flopterm expression COMMA deadterm expression COMMA memreqterm expression affineterm expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsJOB"); ret->type=1; ret->decimal=0.00; ret->num_children=13; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7; ret->child_list[7]=$8; ret->child_list[8]=$9; ret->child_list[9]=$10; ret->child_list[10]=$11; ret->child_list[11]=$12; ret->child_list[12]=$13;$$=ret;}
  ;
jobidterm:
JOBID ASSIGN {fprintf(outprod, "jobidterm --> JOBID ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "jobidterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "jobidterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "jobidterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
flopterm:
FLOPS ASSIGN {fprintf(outprod, "flopterm --> FLOPS ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "flopterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "flopterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "flopterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
deadterm:
DEADLINE ASSIGN {fprintf(outprod, "deadterm --> DEADLINE ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "deadterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "deadterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "deadterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
memreqterm: 
MEMREQ ASSIGN {fprintf(outprod, "memreqterm --> MEMREQ ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "memreqterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "memreqterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "memreqterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
affineterm:
AFFINITY ASSIGN {fprintf(outprod, "affineterm --> AFFINITY ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "affineterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "affineterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "affineterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
; 

argsCLUSTER:
processorsterm expression COMMA topoterm expression COMMA linkbwterm expression COMMA linkcapterm expression nameterm {fprintf(outprod, "argsCLUSTER --> processorsterm expression COMMA topoterm expression COMMA linkbwterm expression COMMA linkcapterm expression nameterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsCLUSTER"); ret->type=1; ret->decimal=0.00; ret->num_children=12; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7; ret->child_list[7]=$8; ret->child_list[8]=$9; ret->child_list[9]=$10; ret->child_list[10]=$11; ret->child_list[11]=$12;$$=ret;}
;
processorsterm: 
PROCESSORS ASSIGN {fprintf(outprod, "processorsterm --> PROCESSORS ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "processorsterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "processorsterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "processorsterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
topoterm:
TOPO ASSIGN {fprintf(outprod, "topoterm --> TOPO ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "topoterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "topoterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "topoterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
linkbwterm:  
LINKBW ASSIGN {fprintf(outprod, "linkbwterm --> LINKBW ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "linkbwterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "linkbwterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "linkbwterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
linkcapterm:
LINKCAP ASSIGN {fprintf(outprod, "linkcapterm --> LINKCAP ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "linkcapterm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "linkcapterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "linkcapterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

argsScheduler:
scheduling_algoTerm expression COMMA load_balancing_algoTerm expression nameterm {fprintf(outprod, "argsScheduler --> scheduling_algoTerm expression COMMA load_balancing_algoTerm expression nameterm\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsScheduler"); ret->type=1; ret->decimal=0.00; ret->num_children=6; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6;$$=ret;}
;
argsSchedule:
processors_listTerm expression COMMA jobsTerm expression COMMA  priority_listTerm expression COMMA final_deadlineTerm expression {fprintf(outprod, "argsSchedule --> processors_listTerm expression COMMA jobsTerm expression COMMA  priority_listTerm expression COMMA final_deadlineTerm expression\n"); typer* ret; ret = create_node(1, 0.00, 1, "argsSchedule"); ret->type=1; ret->decimal=0.00; ret->num_children=11; ret->child_list[0]=$1; ret->child_list[1]=$2; ret->child_list[2]=$3; ret->child_list[3]=$4; ret->child_list[4]=$5; ret->child_list[5]=$6; ret->child_list[6]=$7; ret->child_list[7]=$8; ret->child_list[8]=$9; ret->child_list[9]=$10; ret->child_list[10]=$11; $$=ret;}
;
processors_listTerm:
PROCESSORSLIST ASSIGN {fprintf(outprod, "processors_listTerm --> PROCESSORSLIST ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "processors_listTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "processorsterm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "processorsterm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
jobsTerm:
JOBS ASSIGN {fprintf(outprod, "jobsTerm --> JOBS ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "jobsTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "jobsTerm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "jobsTerm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
scheduling_algoTerm:
SCHALGO ASSIGN {fprintf(outprod, "scheduling_algoTerm --> SCHALGO ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "scheduling_algoTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "scheduling_algoTerm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "scheduling_algoTerm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
priority_listTerm:
PRIOLIST ASSIGN {fprintf(outprod, "priority_listTerm --> PRIOLIST ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "priority_listTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "priority_listTerm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "priority_listTerm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
final_deadlineTerm:
FINDEADLINE ASSIGN {fprintf(outprod, "final_deadlineTerm --> FINDEADLINE ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "final_deadlineTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "final_deadlineTerm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "final_deadlineTerm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
load_balancing_algoTerm:
LOADBALALGO ASSIGN {fprintf(outprod, "load_balancing_algoTerm --> LOADBALALGO ASSIGN\n"); typer* ret; ret = create_node(1, 0.00, 1, "load_balancing_algoTerm");ret->type=1; ret->decimal=0.00; ret->num_children=2; ret->child_list[0]=$1; ret->child_list[1]=$2;$$=ret;}
| %empty {fprintf(outprod, "load_balancing_algoTerm --> (nil)\n"); typer* ret; ret = create_node(1, 0.00, 1, "load_balancing_algoTerm"); ret->type=1; ret->decimal=1.00; ret->num_children=1; ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;
%%

extern
void yyerror(const char *s) {
  PrintError(s);
}
