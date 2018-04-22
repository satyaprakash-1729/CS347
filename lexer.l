%{
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
// #include "header.h"
// #include "assign2_2.tab.h"
#include "ccalc.h"
int yylex(void);
// int yywrap(void);
int yylineno;
extern int scope;
#define YY_INPUT(buf,result,max_size)  {\
    result = GetNextChar(buf, max_size); \
    if (  result <= 0  ) \
      result = YY_NULL; \
    }
%}
%option noyywrap

LETTER [a-zA-Z_]
LETTERDIGIT [a-zA-Z0-9_]
INT_TYPE  int
FLOAT_TYPE double
CHAR_TYPE char
VOID void
DOT  "."
NUM        [0-9]+
FLOAT  [0-9]+\.[0-9]+
STRING  (\"(\\.|[^"\\])*\")|(\'(\\.|[^'\\])*\')
CHAR  (\'(\\.|.)\')
RP  \)
LP \(
INCR "++"
DCR  "--"
PLUS  "+"
MINUS  "-"
ASSIGN  "="
DIV  "/"
MULT  "*"
IF  if
THEN  then
ELIF  elsif
ELSE  else
BEG  "{"
END "}"
GT  ">"
GTEQ ">="
LTEQ "<="
LT  "<"
EQ  "=="
NEQ  "!="
FOR  for
WHILE  while
DO  do
LSQ  "["
RSQ  "]"
COMMA  ","
SEMICOLON ";"
COLON  ":"
NAME  name
PROCESSOR  Processor
ISRUN  is_running
SUBJOBS  submit_jobs
GETCLSP  get_clock_speed
RUN  run
DISCJOB  discard_job
ISA  isa
CLSP  clock_speed
L1MEM  l1_memory
ARCHTYPE  architecture_type
L2MEM  l2_memory
LINK  Link
STPNT  start_point
ENDPNT  end_point
BW  bandwidth
CHCAP  channel_capacity
MEMORY  Memory
GETAVMEM  get_available_memory
MEMTYPE  memory_type
MEMSIZE  mem_size
JOB   Job
GETMEM   get_memory
JOBID   job_id
FLOPS   flops_required
DEADLINE   deadline
MEMREQ   mem_required
AFFINITY   affinity
CLUSTER   Cluster
PROCESSORS   processors
TOPO   topology
LINKBW   link_bandwidth
LINKCAP   link_capacity
RETURN return

PROCESSORSLIST processors_list
JOBS jobs
SCHALGO scheduling_algo
PRIOLIST priority_list
FINDEADLINE final_deadline
LOADBALALGO load_balancing_algo
SCHEDULER Scheduler
SCHEDULE schedule


%%

{DOT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DOT"; width_init(yylval.type_all); return DOT; }
{COMMA}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="COMMA"; width_init(yylval.type_all); return COMMA; }
{SEMICOLON}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="SEMICOLON"; width_init(yylval.type_all); return SEMICOLON; }
{COLON}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="COLON"; width_init(yylval.type_all); return COLON; }
{INCR}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="INCR"; width_init(yylval.type_all); return INCR; }
{DCR}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DCR"; width_init(yylval.type_all); return DCR; }
{LP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LP"; width_init(yylval.type_all); return LP; }
{RP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="RP"; width_init(yylval.type_all); return RP; }
{LSQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LSQ"; width_init(yylval.type_all); return LSQ; }
{RSQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="RSQ"; width_init(yylval.type_all); return RSQ; }
{PLUS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="PLUS"; width_init(yylval.type_all); return PLUS; }
{MINUS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MINUS"; width_init(yylval.type_all); return MINUS; }
{ASSIGN}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ASSIGN"; width_init(yylval.type_all); return ASSIGN; }
{DIV}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DIV"; width_init(yylval.type_all); return DIV; }
{MULT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MULT"; width_init(yylval.type_all); return MULT; }
{GT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="GT"; width_init(yylval.type_all); return GT; }
{LT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LT"; width_init(yylval.type_all); return LT; }
{GTEQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="GTEQ"; width_init(yylval.type_all); return GTEQ; }
{LTEQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LTEQ"; width_init(yylval.type_all); return LTEQ; }
{EQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="EQ"; width_init(yylval.type_all); return EQ; }
{NEQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="NEQ"; width_init(yylval.type_all); return NEQ; }
{IF}[ \n\t\r]*{LP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="IFLP"; width_init(yylval.type_all); return IFLP; }
{THEN}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="THEN"; width_init(yylval.type_all); return THEN; }

{INT_TYPE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=0; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="INT_TYPE"; width_init(yylval.type_all); return INT_TYPE; }
{FLOAT_TYPE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="FLOAT_TYPE"; width_init(yylval.type_all); return FLOAT_TYPE; }
{CHAR_TYPE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=2; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="CHAR_TYPE"; width_init(yylval.type_all); return CHAR_TYPE; }
{VOID}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=3; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="VOID"; width_init(yylval.type_all); return VOID; }
{RETURN}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=3; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="RETURN"; width_init(yylval.type_all); return RETURN; }
                              

{ELIF}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ELIF"; width_init(yylval.type_all); return ELIF; }
{ELSE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ELSE"; width_init(yylval.type_all); return ELSE; }
{BEG}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="BEG"; width_init(yylval.type_all); return BEG; }
{END}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="END"; width_init(yylval.type_all); return END; }
{FOR}[ \n\t\r]*{LP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="FORLP"; width_init(yylval.type_all); return FORLP; }
{WHILE}[ \n\t\r]*{LP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="WHILELP"; width_init(yylval.type_all); return WHILELP; }
{DO}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DO"; width_init(yylval.type_all); return DO; }
{NAME}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="NAME"; width_init(yylval.type_all); return NAME; }
{PROCESSOR}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="PROCESSOR"; width_init(yylval.type_all); return PROCESSOR; }
{ISRUN}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ISRUN"; width_init(yylval.type_all); return ISRUN; }
{SUBJOBS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="SUBJOBS"; width_init(yylval.type_all); return SUBJOBS; }
{GETCLSP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="GETCLSP"; width_init(yylval.type_all); return GETCLSP; }
{RUN}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="RUN"; width_init(yylval.type_all); return RUN; }
{DISCJOB}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DISCJOB"; width_init(yylval.type_all); return DISCJOB; }
{ISA}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ISA"; width_init(yylval.type_all); return ISA; }
{CLSP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="CLSP"; width_init(yylval.type_all); return CLSP; }
{L1MEM}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="L1MEM"; width_init(yylval.type_all); return L1MEM; }
{ARCHTYPE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ARCHTYPE"; width_init(yylval.type_all); return ARCHTYPE; }
{L2MEM}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="L2MEM"; width_init(yylval.type_all); return L2MEM; }
{LINK}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LINK"; width_init(yylval.type_all); return LINK; }
{STPNT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="STPNT"; width_init(yylval.type_all); return STPNT; }
{ENDPNT}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="ENDPNT"; width_init(yylval.type_all); return ENDPNT; }
{BW}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="BW"; width_init(yylval.type_all); return BW; }
{CHCAP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="CHCAP"; width_init(yylval.type_all); return CHCAP; }
{MEMORY}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MEMORY"; width_init(yylval.type_all); return MEMORY; }
{GETAVMEM}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="GETAVMEM"; width_init(yylval.type_all); return GETAVMEM; }
{MEMTYPE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MEMTYPE"; width_init(yylval.type_all); return MEMTYPE; }
{MEMSIZE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MEMSIZE"; width_init(yylval.type_all); return MEMSIZE; }
{JOB}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="JOB"; width_init(yylval.type_all); return JOB; }
{GETMEM}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="GETMEM"; width_init(yylval.type_all); return GETMEM; }
{JOBID}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="JOBID"; width_init(yylval.type_all); return JOBID; }
{FLOPS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="FLOPS"; width_init(yylval.type_all); return FLOPS; }
{DEADLINE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="DEADLINE"; width_init(yylval.type_all); return DEADLINE; }
{MEMREQ}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="MEMREQ"; width_init(yylval.type_all); return MEMREQ; }
{AFFINITY}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="AFFINITY"; width_init(yylval.type_all); return AFFINITY; }
{CLUSTER}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="CLUSTER"; width_init(yylval.type_all); return CLUSTER; }
{PROCESSORS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="PROCESSORS"; width_init(yylval.type_all); return PROCESSORS; }
{TOPO}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="TOPO"; width_init(yylval.type_all); return TOPO; }
{LINKBW}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LINKBW"; width_init(yylval.type_all); return LINKBW; }
{LINKCAP}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LINKCAP"; width_init(yylval.type_all); return LINKCAP; }
{PROCESSORSLIST}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="PROCESSORSLIST"; width_init(yylval.type_all); return PROCESSORSLIST; }
{JOBS}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="JOBS"; width_init(yylval.type_all); return JOBS; }
{SCHALGO}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="SCHALGO"; width_init(yylval.type_all); return SCHALGO; }
{PRIOLIST}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="PRIOLIST"; width_init(yylval.type_all); return PRIOLIST; }
{FINDEADLINE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="FINDEADLINE"; width_init(yylval.type_all); return FINDEADLINE; }
{LOADBALALGO}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="LOADBALALGO"; width_init(yylval.type_all); return LOADBALALGO; }
{SCHEDULER}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="SCHEDULER"; width_init(yylval.type_all); return SCHEDULER; }
{SCHEDULE}              { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=1; yylval.type_all->num_children=0; BeginToken(yytext);  yylval.type_all->tag="SCHEDULE"; width_init(yylval.type_all); return SCHEDULE; }

{LETTER}{LETTERDIGIT}*[ \n\t\r]*{LP}              {BeginToken(yytext);yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=4; yylval.type_all->num_children=0; char* name = (char *)malloc(sizeof(yyleng-1)); strncpy(name, yytext, yyleng-1); yylval.type_all->name=strdup(name); yylval.type_all->tag="IDENTLP"; width_init(yylval.type_all); return IDENTLP;}
{LETTER}{LETTERDIGIT}*[ \n\t\r]*{LSQ}              {BeginToken(yytext);yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=4; yylval.type_all->num_children=0; char* name = (char *)malloc(sizeof(yyleng-1)); strncpy(name, yytext, yyleng-1); yylval.type_all->name=strdup(name); yylval.type_all->tag="IDENTARRAY"; width_init(yylval.type_all); return IDENTARRAY;}
{LETTER}{LETTERDIGIT}*              {BeginToken(yytext);yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->decimal=0.00; yylval.type_all->type=4; yylval.type_all->num_children=0; yylval.type_all->tag="IDENT"; width_init(yylval.type_all); char* name = (char *)malloc(sizeof(yyleng)); strncpy(name, yytext, yyleng); yylval.type_all->name=strdup(name);return IDENT;}
{NUM}		 { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0;yylval.type_all->type=0; yylval.type_all->num_children=0;yylval.type_all->num=atoi(yytext);BeginToken(yytext); yylval.type_all->tag="NUM"; width_init(yylval.type_all); return NUM;}
{FLOAT}		 { yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0;yylval.type_all->type=1; yylval.type_all->num_children=0;BeginToken(yytext);yylval.type_all->decimal=atof(yytext); yylval.type_all->tag="FLOAT"; width_init(yylval.type_all); return FLOAT;}
{CHAR}               {BeginToken(yytext);yylval.type_all = (typer *)malloc(sizeof(typer)); yylval.type_all->num_children = 0; yylval.type_all->done=0; yylval.type_all->character=*(yytext+1); yylval.type_all->type=2; yylval.type_all->num_children=0; yylval.type_all->tag="CHAR"; width_init(yylval.type_all); return CHAR;}

[ \t]*               {BeginToken(yytext);}
[\n]                 {BeginToken(yytext); yylineno++;}
.               {BeginToken(yytext); return yytext[0];}

%%
