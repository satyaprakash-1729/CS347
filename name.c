#include "stdio.h"
#include "lex.h"
#include "stdlib.h"
char  *Names[] = { "_t0", "_t1", "_t2", "_t3", "_t4", "_t5", "_t6", "_t7", "_t8", "_t9", "_t10", "_t11", "_t12", "_t13", "_t14", "_t15", "_t16", "_t17", "_t18", "_t19" };   
char  **Namep  = Names;   
   
char  *newname()   
{   
    if( Namep >= &Names[ sizeof(Names)/sizeof(*Names) ] )   
    {   
        fprintf( stderr, "%d: Expression too complex\n", yylineno );   
        exit( 1 );   
    }   
   
    return( *Namep++ );   
}   
   
void freename(char *s)      
{   
    if( Namep > Names )   
       *--Namep = s;   
    // else   
       // fprintf(stderr, "%d: (Internal error) Name stack underflow\n",   
       //                          yylineno );   
}   
