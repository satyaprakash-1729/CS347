
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

%}

%union
{
       typer* type_all;
}


%type<type_all> RETURN VOID CHAR IDENTLP IDENTARRAY IDENT DOT NUM FLOAT LP RP PLUS MINUS ASSIGN DIV MULT IFLP THEN ELIF ELSE BEG END GT LT GTEQ LTEQ EQ NEQ FORLP WHILELP DO LSQ RSQ COMMA SEMICOLON COLON NAME PROCESSOR ISRUN SUBJOBS GETCLSP RUN DISCJOB ISA CLSP L1MEM ARCHTYPE L2MEM LINK STPNT ENDPNT BW CHCAP MEMORY GETAVMEM MEMTYPE MEMSIZE JOB GETMEM JOBID FLOPS DEADLINE MEMREQ AFFINITY CLUSTER PROCESSORS TOPO LINKBW LINKCAP INCR DCR ENDALL PROCESSORSLIST JOBS SCHALGO PRIOLIST FINDEADLINE LOADBALALGO SCHEDULER SCHEDULE INT_TYPE FLOAT_TYPE CHAR_TYPE
%type<type_all> whileexp emptyN emptyM ifexp beforeargs external_declarations program_code func_decl func_head decl_plist decl_pl decl_param beforeend beforestats ident-list argsnonempty statements statement selection opt_block expression expr_temp RA_TERM expression_prime term term_prime factor function argsAll type

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
%token IFLP
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
%token FORLP
%token WHILELP
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
// print_code1();
}
;

statements:
statement emptyM statements {yyerrok;
fprintf(outprod, "statements --> statement statements\n");
 typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->num_children=2;
// next_list_printer($3->next);

backpatch($1->next, $2->label, $2->quad);
ret->next = $3->next;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
$$=ret;}
| ENDALL {yyerrok;fprintf(outprod, "statements --> ENDALL\n");typer* ret;
ret = create_node(7, 0.00, 1, "statements");
ret->next = makelist(-1);
ret->child_list[0]=$1;$$=ret;}
| %empty {yyerrok;fprintf(outprod, "statements --> (nil)\n");typer* ret;
ret = create_node(5, 0.00, 1, "statements");
ret->next = makelist(-1);
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
    // char* temp = (char*)malloc(120*sizeof(char));
    // sprintf(temp, );
    gen_code("return\n");
    ret->next = makelist(-1);
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
    char* temp = (char*)malloc(120*sizeof(char));
    sprintf(temp, "return %s\n", $2->result->name);
    gen_code(temp);
    ret->next = makelist(-1);
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    $$=ret;
}
| opt_block
{
    fprintf(outprod, "statement --> opt_block\n");
    typer* ret;
    ret = create_node(1, 0.00, 1, "statement");
    ret->num_children=1;
    ret->next = $1->next;
    ret->child_list[0]=$1;
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
        sprintf(tmp1, "%s = %s\n", $1->name, $3->result->name);
        gen_code(tmp1);
        freename($3->result->name);
     }else{
        break;
     }
     ret->next = makelist(-1);
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
        ret->next = makelist(-1);
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
        
        char* tmp1 = (char *)malloc(120*sizeof(char));
        sprintf(tmp1, "%s = %s\n", $1->name, $3->result->name);
        gen_code(tmp1);

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
            if($5->st_entry->type_ident==1){
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
        // printf(">>>>>>>>>>>  %d\n", $2->type);
        if($2->type!=0){
            if($2->type==4){
                ste* identptr1 = symtab_lookup_up($2->st_entry->name, scope);
                prl* prlptr1 = search_param($2->st_entry->name);
                if(!identptr1 && !prlptr1){
                    error_caller("ERROR: Undeclared identifier! ", $1->name);
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

        char* tmp1 = (char *)malloc(100*sizeof(char));
        tte* temp = newtemp(identptr->eletype);
        tte* temp2 = newtemp(0);
        tte* temp3 = newtemp(0);
        sprintf(tmp1, "%s = addr(%s)\n%s = 4\n%s = %s * %s\n%s[%s] = %s\n",
         temp->name,
         identptr->name,
         temp3->name,
         temp2->name,
         $2->result->name,
         temp3->name,
         temp->name,
         temp2->name,
         $5->result->name);
        gen_code(tmp1);
        nextquad+=2;
        freename(temp3->name);
        freename($5->result->name);
        freename($2->result->name);
     }else{
        break;
     }
ret->next = makelist(-1);
ret->num_children=6;
ret->child_list[0]=$1;ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;
ret->child_list[5]=$6;
$$=ret;
}//{fprintf(outprod, ">>> %s[%f] = %.2f\n",$1, $3, $6);$$=ret;}
| expression SEMICOLON {fprintf(outprod, "statement --> expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->next = makelist(-1);
ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $1);$$=ret;}
| selection {fprintf(outprod, "statement --> selection\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->next = $1->next;
ret->num_children=1;
ret->child_list[0]=$1;$$=ret;}
| function SEMICOLON {fprintf(outprod, "statement --> function SEMICOLON\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=2;
ret->next = makelist(-1);
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
| whileexp RP opt_block {fprintf(outprod, "statement --> WHILELP expression RP opt_block \n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;

char* temp = (char *)malloc(120*sizeof(char));
sprintf(temp, "goto %s\n", $1->label);
gen_code(temp);

tagtoaddlabel[numtags++] = strdup($1->label);
tagtoaddquad[numtags-1] = $1->begin;

backpatch($3->next, $1->label, $1->begin);
ret->next = $1->falselist;

$$=ret;}//{fprintf(outprod, ">>> %.2f\n", $3);$$=ret;}
| FORLP statement expression SEMICOLON expression RP opt_block {fprintf(outprod, "statement --> FORLP statement expression SEMICOLON expression RP opt_block\n");typer* ret;
ret = create_node(1, 0.00, 1, "statement");
ret->num_children=7;
ret->child_list[0]=$1;
ret->next = makelist(-1);
ret->child_list[1]=$2;
ret->child_list[2]=$3;
ret->child_list[3]=$4;
ret->child_list[4]=$5;
ret->child_list[5]=$6;
ret->child_list[6]=$7;
$$=ret;}
| type ident-list SEMICOLON {fprintf(outprod, "statement --> type ident-list SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 3, "statement");
 $1->decimal = $3->decimal;
ret->num_children=3;
ret->child_list[0]=$1;
ret->next = makelist(-1);
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
patchtype($2->namelist, $2->namelistnum, $1->type);}
//////////////////ERROR HANDLING////////////////////
| FORLP error expression SEMICOLON expression RP opt_block {fprintf(outerror, "*****Error in initialization expression!\n");
yyerrok;}
| FORLP statement error expression RP opt_block {fprintf(outerror, "*****Error in check expression!\n");
yyerrok;}
| FORLP statement expression SEMICOLON error RP opt_block {fprintf(outerror, "*****Error in update expression!\n");
yyerrok;}
| FORLP statement expression SEMICOLON expression RP error {fprintf(outerror, "*****Error in body of FOR loop!\n");
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

whileexp:
WHILELP emptyM expression
{
    fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
    ret = create_node(0, 0.00, 1, "selection");
    // ret->next = merge($2->next, $1->falselist);
    ret->falselist = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "if %s <= 0 goto \n", $3->result->name);
    // printf(">>>>>>>>>>>>>>>>>>>>>>>>>?? %d\n", $2->quad);
    gen_code(temp);
    ret->begin = $2->quad;
    ret->label = $2->label;
    ret->num_children=2;
    ret->child_list[0]=$1;
    ret->child_list[1]=$3;
    $$=ret;
}
;

selection:
    ifexp opt_block {fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection");
            ret->next = merge($2->next, $1->falselist);
            ret->num_children=2;
            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            $$=ret;}
    |  ifexp opt_block emptyN ELSE emptyM opt_block {fprintf(outprod, "selection --> IFLP expression RP selection_prime\n");typer* ret;
            ret = create_node(0, 0.00, 1, "selection");
            ret->num_children=4;

            backpatch($1->falselist, $5->label, $5->quad);
            ret->next = merge($2->next, $6->next);
            ret->next = merge(ret->next, $3->next);

            ret->child_list[0]=$1;
            ret->child_list[1]=$2;
            ret->child_list[2]=$3;
            ret->child_list[3]=$4;
            $$=ret;}
    | IFLP error RP opt_block {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
    | IFLP error RP opt_block ELSE opt_block {fprintf(outerror, "*****Wrong conditional expression!\n"); yyerrok;}
;

ifexp:
IFLP expression RP {
    fprintf(outprod, "ifexp --> IFLP expression RP\n");
    typer* ret;
    ret = create_node(7, 0.00, 1, "ifexp");
    ret->num_children = 3;
    ret->falselist = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "if %s <= 0 goto \n", $2->result->name);
    gen_code(temp);
    ret->child_list[0]=$1;
    ret->child_list[1]=$2;
    ret->child_list[2]=$3;
    $$=ret;
}
;

emptyN:
%empty 
{
    fprintf(outprod, "statements --> (nil)\n");typer* ret;
    ret = create_node(5, 0.00, 1, "statements");
    ret->next = makelist(nextquad);
    char* temp = (char *)malloc(120*sizeof(char));
    sprintf(temp, "goto \n");
    gen_code(temp);
    ret->child_list[0]=create_node(1,0.00,0,"NULL");
    $$=ret;
}
;

emptyM:
%empty {
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
    $$=ret;
}
;

opt_block:
beforeend END {fprintf(outprod, "opt_block --> beforeend END\n");typer* ret;
ret = create_node(7, 0.00, 1, "opt_block");
ret->num_children=2;
ret->next = $1->next;
ret->child_list[0]=$1;ret->child_list[1]=$2;$$=ret;}
;

beforeend:
beforestats statements {fprintf(outprod, "beforeend --> beforestats statements\n");typer* ret;
ret = create_node(7, 0.00, 1, "beforeend");
print_symbol_table();
ret->next = $2->next;
write_data_part2(codefile);
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

char* tag = TAGARR[tagcntr++];
backpatch($2->next, tag, nextquad);
gen_code("func end\n");

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
        insert_param(func, $3->paramlist[i]->param_type, $3->paramlist[i]->param_name);
    }
}
active_func_ptr = functab_lookup($2->name);

char* temp1 = (char *)malloc(120*sizeof(char));
sprintf(temp1, "func begin %s\n", active_func_ptr->func_name);
gen_code(temp1);

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

char* temp1 = (char *)malloc(120*sizeof(char));
sprintf(temp1, "func begin %s\n", active_func_ptr->func_name);
gen_code(temp1);

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
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);

            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s <= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if($2->ra_term_val==2){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s >= %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if($2->ra_term_val==1){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a<b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s < %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if($2->ra_term_val==0){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a>b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s > %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if($2->ra_term_val==4){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a==b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s == %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }
        }else if($2->ra_term_val==5){
            if(ret->type==0){
            int a = *((int*)setter($1));
            int b = *((int*)setter($3));
            ret->num=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==1){
            double a = *((double*)setter($1));
            double b = *((double*)setter($3));
            ret->decimal=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
            gen_code(tmp2);
            
            memset(tmp1, 0, 30);
            sprintf(tmp1, "%s = 0\n%s:\n", ret->result->name, tag);
            gen_code(tmp1);
            nextquad++;
        }else if(ret->type==2){
            char a = *((char*)setter($1));
            char b = *((char*)setter($3));
            ret->character=(a!=b);

            tte* newtmp = newtemp(ret->type);
            ret->result = newtmp;
            char* tmp1 = (char *)malloc(120*sizeof(char));
            sprintf(tmp1, "%s = 1\n", ret->result->name);
            gen_code(tmp1);

            char* tag = TAGARR[tagcntr++];
            char* tmp2 = (char *)malloc(120*sizeof(char));
            sprintf(tmp2, "if %s != %s goto %s\n", $1->result->name, $3->result->name, tag);
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


        char* tmp1 = (char *)malloc(120*sizeof(char));
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
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
            double a1 = $2->num;
            double b1 = $3->decimal;
            double c1 = 1.0/(int)(a1*b1);
            ret->decimal = c1;
            ret->num = c1;
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
        char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s + 1\n%s = %s\n%s = %s - 1\n", ret->result->name, identptr->name, ret->result->name, ret->result->name, identptr->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
nextquad+=3;
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
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s - 1\n%s = %s\n%s = %s + 1\n", ret->result->name, identptr->name, ret->result->name, ret->result->name, identptr->name, ret->result->name, ret->result->name, ret->result->name);
gen_code(tmp1);
nextquad+=3;
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
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s+1\n%s = %s\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name);
gen_code(tmp1);
nextquad+=2;
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
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n%s = %s-1\n%s = %s\n", ret->result->name, $2->name, ret->result->name, ret->result->name, $2->name, ret->result->name);
gen_code(tmp1);

nextquad+=2;
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
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
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %s\n", ret->result->name, $2->result->name);
gen_code(tmp1);

$$=ret;
}
| MINUS NUM {fprintf(outprod, "factor --> MINUS NUM\n");
typer* ret;
ret = create_node(0, 0.00, 1, "factor");
ret->num=-($2->num);

ret->result = newtemp(0);
char* tmp1 = (char *)malloc(120*sizeof(char));
sprintf(tmp1, "%s = %d\n", ret->result->name, ret->num);
gen_code(tmp1);

ret->num_children=2;
ret->child_list[0]=$1;
ret->child_list[1]=$2;$$=ret;}
| IDENTARRAY expression RSQ {fprintf(outprod, "statement --> IDENTARRAY expression RSQ ASSIGN expression SEMICOLON\n");
typer* ret;
ret = create_node(1, 0.00, 3, "statement");

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
        if($2->type!=0){
            if($2->type==4){
                ste* identptr1 = symtab_lookup_up($2->st_entry->name, scope);
                prl* prlptr1 = search_param($2->st_entry->name);
                if(!identptr1 && !prlptr1){
                    error_caller("ERROR: Undeclared identifier! ", $1->name);
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
        if($2->num >= identptr->dim || $2->num < 0){
            yyerror("ERROR: Array index out of bounds!");
            yyerrok;
            break;
        }
        ret->type = identptr->eletype;
        if(identptr->eletype==0){
            ret->num = identptr->arrayint[$2->num];
        }else if(identptr->eletype==1){
            ret->decimal = identptr->arraydouble[$2->num];
        }else if(identptr->eletype==2){
            ret->character = identptr->arraychar[$2->num];
        }

        char* tmp1 = (char *)malloc(100*sizeof(char));
        tte* temp = newtemp(identptr->eletype);
        tte* temp3 = newtemp(identptr->eletype);
        tte* temp2 = newtemp(0);

        sprintf(tmp1, "%s = addr(%s)\n%s = 4\n%s = %s * %s\n%s = %s[%s]\n",
         temp->name,
         identptr->name,
         temp2->name,
         $2->result->name,
         $2->result->name,
         temp2->name,
         temp3->name,
         temp->name,
         $2->result->name);
        gen_code(tmp1);
        nextquad+=2;
        ret->result = temp3;
ret->next = makelist(-1);
ret->num_children=3;
ret->child_list[0]=$1;
ret->child_list[1]=$2;
ret->child_list[2]=$3;
$$=ret;
}
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
| IDENT ASSIGN factor
{
    fprintf(outprod, "ident-list -->  IDENT\n");
    int done;
    if($3->type==0){
        // printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.\n");
        done = insert_symtab($1->name, 0, 0, 1, $3->num, 0.00, ' ', scope);
    }
    else if($3->type==0) 
        done = insert_symtab($1->name, 0, 0, 1, 0, $3->decimal, ' ', scope);
    else if($3->type==0) 
        done = insert_symtab($1->name, 0, 0, 1, 0, 0.00, $3->character, scope);
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
    tte* temp1 = newtemp(callfunc->res_type);
    char* temp2 = (char *)malloc(120*sizeof(char));
    sprintf(temp2, "refparam %s\n", temp1->name);
    gen_code(temp2);

    memset(temp2, 0, 60);
    sprintf(temp2, "call %s %d\n", callfunc->func_name, callfunc->num_params+1);
    gen_code(temp2);
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
    
    char* temp1 = (char *)malloc(120*sizeof(char));
    sprintf(temp1, "param %s\n", $3->result->name);
    gen_code(temp1);

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

    char* temp1 = (char *)malloc(120*sizeof(char));
    sprintf(temp1, "param %s\n", $1->result->name);
    gen_code(temp1);

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
