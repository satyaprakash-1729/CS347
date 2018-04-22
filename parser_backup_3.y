
%{
// int yyerror(const char *);
int yylex(void);
#define YYERROR_VERBOSE 1
#define YYDEBUG 1
#define ERROR_TYPE 6
#define SYMTAB_SIZE 50

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

int scope = 0;

ste* symtab[SYMTAB_SIZE];
int symtab_num = 0;

extern FILE* outprod;
extern FILE* outerror;
extern int yylineno;
extern typer* root;

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

void copy_namelist(typer* ret, typer* toadd){
  ret->namelistnum = toadd->namelistnum+1;
  for(int i=0;
i<toadd->namelistnum;
i++){
    ret->namelist[i] = strdup(toadd->namelist[i]);
  }
  return;
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



double get_value(char* vars[], double vals[], int count, char* varname){
	double ans = 0.00;
	for(int i=0;
i<count;
i++){
		if(strcmp(vars[i], varname)==0){
			ans = vals[i];
		}
	}
	return ans;
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
       temp->decimal = decimal;
       temp->character = ' ';
       temp->tag = tag;
       temp->namelistnum=0;
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
       for(int i=0;
i<10;
i++)
              temp->child_list[i] = NULL;
       return temp;
}

%}

%union
{
       typer* type_all;
}


%type<type_all> VOID CHAR IDENTARRAY IDENT DOT NUM FLOAT LP RP PLUS MINUS ASSIGN DIV MULT IF THEN ELIF ELSE BEG END GT LT GTEQ LTEQ EQ NEQ FOR WHILE DO LSQ RSQ COMMA SEMICOLON COLON NAME PROCESSOR ISRUN SUBJOBS GETCLSP RUN DISCJOB ISA CLSP L1MEM ARCHTYPE L2MEM LINK STPNT ENDPNT BW CHCAP MEMORY GETAVMEM MEMTYPE MEMSIZE JOB GETMEM JOBID FLOPS DEADLINE MEMREQ AFFINITY CLUSTER PROCESSORS TOPO LINKBW LINKCAP INCR DCR ENDALL PROCESSORSLIST JOBS SCHALGO PRIOLIST FINDEADLINE LOADBALALGO SCHEDULER SCHEDULE INT_TYPE FLOAT_TYPE CHAR_TYPE
%type<type_all>  func_decl func_head result res_id decl_plist decl_pl decl_param beforeend beforestats ident-list argsnonempty statements statement statement-with-else selection selection_prime selection-with-else selection-with-else_prime opt_block expression expr_temp RA_TERM expression_prime term term_prime factor function argsAll type


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
%token VOID
%left MINUS PLUS
%left MULT DIV
%left GT LT EQ NEQ GTEQ LTEQ

%start statements
%%
statements:
statement statements {yyerrok;
fprintf(outprod, "statements --> statement statements\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;
root=ret;}
| beforeend END statements {yyerrok;
fprintf(outprod, "statements --> BEG statements END statements\n");
 typer* ret;
ret = create_node(7, 0.00, 3, "statements");
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
root=ret;}
| ENDALL {yyerrok;fprintf(outprod, "statements --> ENDALL\n");typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->child_list[0]=$1;$$=ret;
root=ret;}
| %empty {yyerrok;fprintf(outprod, "statements --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "statements");
 ret->decimal=0.00;
ret->child_list[0]=create_node(1,0.00,0,"NULL");
$$=ret;
root=ret;
print_symbol_table();}
;

statement:
IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENT ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
if($3->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up($1->name, scope);
        if(!identptr){
            yyerror("ERROR: Undeclared identifier!");
            yyerrok;
            break;
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
ret->child_list[3]=$4;$$=ret;}
| IDENTARRAY expression RSQ ASSIGN expression SEMICOLON {fprintf(outprod, "statement --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");

if($5->type!=ERROR_TYPE){
        ste* identptr = symtab_lookup_up($1->name, scope);
        if(!identptr){
            yyerror("ERROR: Undeclared identifier!");
            yyerrok;
            break;
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
    IDENT ASSIGN expression SEMICOLON {fprintf(outprod, "statement-with-else --> IDENT ASSIGN expression SEMICOLON\n");
            typer* ret;
            ret = create_node(1, 0.00, 1, "statement-with-else");

            if($3->type!=ERROR_TYPE){
                ste* identptr = symtab_lookup_up($1->name, scope);
                if(!identptr){
                    yyerror("ERROR: Undeclared identifier!");
                    yyerrok;
                    break;
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
                if(!identptr){
                    yyerror("ERROR: Undeclared identifier!");
                    yyerrok;
                    break;
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
$$=ret;}
;

func_head:
res_id LP decl_plist RP {fprintf(outprod, "func_head --> res_id LP decl_plist RP\n");typer* ret;
ret = create_node(7, 0.00, 1, "func_decl");
ret->num_children=4;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
$$=ret;}
;

res_id:
result IDENT {fprintf(outprod, "res_id --> result IDENT\n");typer* ret;
ret = create_node(7, 0.00, 1, "res_id");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;}
;

result:
type {fprintf(outprod, "result --> type\n");typer* ret;
ret = create_node(7, 0.00, 1, "result");
ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
| VOID {fprintf(outprod, "result --> VOID\n");typer* ret;
ret = create_node(7, 0.00, 1, "result");
ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
;

decl_plist:
decl_pl {fprintf(outprod, "decl_plist --> decl_pl\n");typer* ret;
ret = create_node(7, 0.00, 1, "decl_plist");
ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
| %empty {fprintf(outprod, "decl_plist --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "decl_plist");
 ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

decl_pl:
decl_pl COMMA decl_param {fprintf(outprod, "decl_pl --> decl_pl COMMA decl_param\n");typer* ret;
ret = create_node(7, 0.00, 1, "decl_pl");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;}
| decl_param {fprintf(outprod, "decl_pl --> decl_param\n");typer* ret;
ret = create_node(7, 0.00, 1, "decl_pl");
ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
;

decl_param:
type IDENT {fprintf(outprod, "decl_param --> type IDENT\n");typer* ret;
ret = create_node(7, 0.00, 1, "decl_param");
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;}
;

expression:
expr_temp 
{fprintf(outprod, "expression --> expr_temp\n");typer* ret;
ret = create_node(0, 0.00, 1, "expression");
ret->type = $1->type;
ret->st_entry = $1->st_entry;
ret->decimal = $1->decimal;
ret->num = $1->num;
ret->character = $1->character;
ret->num_children=1;ret->child_list[0]=$1;$$=ret;}

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
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<=b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<=b);
        }
        }else if($2->ra_term_val==2){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>=b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>=b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>=b);
        }
        }else if($2->ra_term_val==1){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a<b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<b);
        }
        }else if($2->ra_term_val==0){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>b);
        }
        }else if($2->ra_term_val==4){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a==b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a==b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a==b);
        }
        }else if($2->ra_term_val==5){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a!=b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a!=b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a!=b);
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
     }else{
        ret->type = ERROR_TYPE;
        break;
     }
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;ret->child_list[2]=$3;$$=ret;}
| %empty {fprintf(outprod, "expression_prime --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "expression_prime");
 ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
;

term:
factor term_prime {fprintf(outprod, "term --> factor term_prime\n");typer* ret;
ret = create_node(0, 0.00, 1, "term");
 if($2->type==5){
    ret->type = $1->type;
    ret->st_entry = $1->st_entry;
    ret->decimal = $1->decimal;
    ret->num = $1->num;
    ret->character = $1->character;
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
            yyerror("ERROR10 : Type Mismatch!");
            yyerrok;
            ret->type = ERROR_TYPE;
            break;
        }
        int ret_type = result_type($1->type, $2->type);
        ret->type = ret_type;

        if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($2));
            ret->num=(a*b);
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($2));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($2));
            ret->character=(a*b);
        }
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
    ret->type = $2->type;
    ret->st_entry = $2->st_entry;
    ret->decimal = $2->decimal;
    ret->num = $2->num;
    ret->character = $2->character;    
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
            int a = *((int*)setter($2));
            int b = *((int*)setter($3));
            ret->num=(a*b);
        }else if(ret->type==1){
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=(a*b);
        }
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
    ret->decimal = 1/$2->decimal;
    ret->num = 1/$2->num;
    ret->character = 1/$2->character;    
}
else if($2->type!=ERROR_TYPE && $3->type!=ERROR_TYPE){
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
            int a = *((int*)setter($2));
            int b = *((int*)setter($3));
            ret->num=1/(a*b);
        }else if(ret->type==1){
            double a = *((double*)setter($2));
            double b = *((double*)setter($3));
            ret->decimal=1/(a*b);
        }else if(ret->type==2){
            char a = *((char*)setter($2));
            char b = *((char*)setter($3));
            ret->character=1/(a*b);
        }
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
ret->decimal=1.00;
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
ret->child_list[1]=$2;$$=ret;}
| NUM DCR { fprintf(outprod, "factor --> NUM DCR\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num = $1->num--;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
| IDENT INCR {fprintf(outprod, "factor --> IDENT INCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
ret->st_entry = identptr;
if(!identptr){
    yyerror("ERROR: Undeclared identifier!");
    yyerrok;
    break;
}
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
ret->child_list[1]=$2;$$=ret;}
| IDENT DCR {fprintf(outprod, "factor --> IDENT DCR\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
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
ret->child_list[1]=$2;$$=ret;}

| INCR IDENT {fprintf(outprod, "factor --> INCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($2->name, scope);
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
ret->child_list[1]=$2;$$=ret;}
| DCR IDENT {fprintf(outprod, "factor -->  DCR IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($2->name, scope);
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
ret->child_list[1]=$2;$$=ret;}
| INCR NUM {fprintf(outprod, "factor -->  INCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=++$2->num;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
| DCR NUM {fprintf(outprod, "factor -->  DCR NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=--$2->num;
ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}

| NUM {fprintf(outprod, "factor --> NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=$1->num;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;
// printf("<>>>>>>>>>>>>>>>>  EXPR  %d  %d", $1->num, ret->type);

}
| IDENT {fprintf(outprod, "factor --> IDENT\n");
typer* ret;
ret = create_node(4, 0.00, 1, "factor");
ste* identptr = symtab_lookup_up($1->name, scope);
ret->st_entry = identptr;
ret->type = 4;
 ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
| CHAR {fprintf(outprod, "factor --> CHAR\n");
typer* ret;
ret = create_node(2, 0.00, 1, "factor");
ret->decimal=0.00;
ret->character = $1->character;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| FLOAT {fprintf(outprod, "factor --> FLOAT\n");
typer* ret;
ret = create_node(1, 0.00, 1, "factor");
ret->decimal=$1->decimal;
ret->num_children=1;
ret->child_list[0]=$1;
$$=ret;}
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
ret->child_list[2]=$3;$$=ret;}
| MINUS NUM {fprintf(outprod, "factor --> MINUS NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=-($2->num);
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
IDENT {fprintf(outprod, "ident-list -->  IDENT\n");
int done = insert_symtab($1->name, 0, 0, 1, 0, 0.00, ' ', scope);
if(!done){yyerror("ERROR15: redeclaration of identifier!");
yyerrok;}typer* ret;
ret = create_node(4, 0.00, 1, "ident-list");
ret->child_list[0]=$1;ret->namelistnum=1;ret->namelist[0]=strdup($1->name);
$$=ret;}
| ident-list COMMA IDENT {fprintf(outprod, "ident-list --> ident-list COMMA IDENT \n");
int done = insert_symtab($3->name, 0, 0, 1, 0, 0.00, ' ', scope);
if(!done){yyerror("ERROR16: redeclaration of identifier!");
yyerrok;} typer* ret;
ret = create_node(4, 0.00, 3, "ident-list");
ret->namelistnum++;copy_namelist(ret, $1);
 ret->namelist[ret->namelistnum-1]=strdup($3->name);
ret->child_list[0]=$1;ret->child_list[1]=$2;ret->child_list[2]=$3;
$$=ret;}
| ident-list COMMA IDENTARRAY expression RSQ { fprintf(outprod, "ident-list --> ident-list COMMA IDENTARRAY expression RSQ\n");
printf("SIZE>>>>>>>>>>>>>>>>>>>>>>>>  %d\n", $4->num);

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
 IDENT LP argsAll RP  {fprintf(outprod, "function -->  IDENT LP argsAll RP\n");
typer* ret;
ret = create_node(1, 0.00, 1, "function");
ret->type=1;
ret->decimal=0.00;
ret->num_children=4;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;$$=ret;}
 | IDENT LP error RP  {fprintf(outerror, "Incorrect function call syntax! USAGE: func_name(arg1, arg2, arg3, ...);\n");}
 ;
 argsAll:
 argsnonempty {fprintf(outprod, "argsAll --> argsnonempty\n");
typer* ret;
ret = create_node(1, 0.00, 1, "argsAll");
ret->type=1;
ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
 | %empty {fprintf(outprod, "argsAll --> (nil)\n");
typer* ret;
ret = create_node(1, 0.00, 1, "argsAll");
ret->type=1;
ret->decimal=1.00;
ret->num_children=1;
ret->child_list[0]=create_node(1,0.00,0,"NULL");$$=ret;}
 ;
argsnonempty:
 IDENT ASSIGN expression COMMA argsnonempty {fprintf(outprod, "argsnonempty --> IDENT ASSIGN expression COMMA argsAll\n");
typer* ret;
ret = create_node(1, 0.00, 1, "argsnonempty");
ret->type=1;
ret->decimal=0.00;
ret->num_children=5;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;ret->child_list[4]=$5;$$=ret;}
 | expression COMMA argsnonempty {fprintf(outprod, "argsnonempty --> expression COMMA argsAll\n");
 typer* ret;
ret = create_node(1, 0.00, 1, "argsnonempty");
ret->type=1;
ret->decimal=0.00;
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;$$=ret;}
 | expression {fprintf(outprod, "argsnonempty --> expression\n");typer* ret;
ret = create_node(1, 0.00, 1, "argsnonempty");
ret->type=1;
ret->decimal=0.00;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
 | IDENT ASSIGN expression {fprintf(outprod, "argsnonempty --> IDENT ASSIGN expression\n");
typer* ret;
ret = create_node(1, 0.00, 1, "argsnonempty");
ret->type=1;
ret->decimal=0.00;
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;$$=ret;}
;


%%

extern
void yyerror(const char *s) {
  PrintError(s);
}
