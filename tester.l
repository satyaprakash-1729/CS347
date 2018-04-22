%{
#include <stdlib.h>
#include "stdio.h"
#include "string.h"
int yylex(void);

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

{DOT}    { printf("DOT");}
{COMMA}    { printf("COMMA");}
{SEMICOLON}    { printf("SEMICOLON");}
{COLON}    { printf("COLON");}
{INCR}    { printf("INCR");}
{DCR}    { printf("DCR");}
{LP}    { printf("LP");}
{RP}    { printf("RP");}
{LSQ}    { printf("LSQ");}
{RSQ}    { printf("RSQ");}
{PLUS}    { printf("PLUS");}
{MINUS}    { printf("MINUS");}
{ASSIGN}    { printf("ASSIGN");}
{DIV}    { printf("DIV");}
{MULT}    { printf("MULT");}
{GT}    { printf("GT");}
{LT}    { printf("LT");}
{GTEQ}    { printf("GTEQ");}
{LTEQ}    { printf("LTEQ");}
{EQ}    { printf("EQ");}
{NEQ}    { printf("NEQ");}
{IF}    { printf("IF");}
{THEN}    { printf("THEN");}
{INT_TYPE}    { printf("INT_TYPE");}
{FLOAT_TYPE}    { printf("FLOAT_TYPE");}
{CHAR_TYPE}    { printf("CHAR_TYPE");}
{VOID}    { printf("VOID");}
{RETURN}    { printf("RETURN");}
{ELIF}    { printf("ELIF");}
{ELSE}    { printf("ELSE");}
{BEG}    { printf("BEG");}
{END}    { printf("END");}
{FOR}    { printf("FOR");}
{WHILE}    { printf("WHILE");}
{DO}    { printf("DO");}
{NAME}    { printf("NAME");}
{PROCESSOR}    { printf("PROCESSOR");}
{ISRUN}    { printf("ISRUN");}
{SUBJOBS}    { printf("SUBJOBS");}
{GETCLSP}    { printf("GETCLSP");}
{RUN}    { printf("RUN");}
{DISCJOB}    { printf("DISCJOB");}
{ISA}    { printf("ISA");}
{CLSP}    { printf("CLSP");}
{L1MEM}    { printf("L1MEM");}
{ARCHTYPE}    { printf("ARCHTYPE");}
{L2MEM}    { printf("L2MEM");}
{LINK}    { printf("LINK");}
{STPNT}    { printf("STPNT");}
{ENDPNT}    { printf("ENDPNT");}
{BW}    { printf("BW");}
{CHCAP}    { printf("CHCAP");}
{MEMORY}    { printf("MEMORY");}
{GETAVMEM}    { printf("GETAVMEM");}
{MEMTYPE}    { printf("MEMTYPE");}
{MEMSIZE}    { printf("MEMSIZE");}
{JOB}    { printf("JOB");}
{GETMEM}    { printf("GETMEM");}
{JOBID}    { printf("JOBID");}
{FLOPS}    { printf("FLOPS");}
{DEADLINE}    { printf("DEADLINE");}
{MEMREQ}    { printf("MEMREQ");}
{AFFINITY}    { printf("AFFINITY");}
{CLUSTER}    { printf("CLUSTER");}
{PROCESSORS}    { printf("PROCESSORS");}
{TOPO}    { printf("TOPO");}
{LINKBW}    { printf("LINKBW");}
{LINKCAP}    { printf("LINKCAP");}
{PROCESSORSLIST}    { printf("PROCESSORSLIST");}
{JOBS}    { printf("JOBS");}
{SCHALGO}    { printf("SCHALGO");}
{PRIOLIST}    { printf("PRIOLIST");}
{FINDEADLINE}    { printf("FINDEADLINE");}
{LOADBALALGO}    { printf("LOADBALALGO");}
{SCHEDULER}    { printf("SCHEDULER");}
{SCHEDULE}    { printf("SCHEDULE");}

{LETTER}{LETTERDIGIT}*[ \n\t\r]*{LP}     {printf("FUNC>>>>>> \n");}
{LETTER}{LETTERDIGIT}*[ \n\t\r]*{LSQ}    {printf("IDENTARRAY");}
{LETTER}{LETTERDIGIT}*                    {printf("IDENT");}
{NUM}                                    {printf("NUM");}
{FLOAT}                            {printf("FLOAT");}
{CHAR}                             {printf("CHAR");}

[ \t]*;
[\n];
.;

%%
