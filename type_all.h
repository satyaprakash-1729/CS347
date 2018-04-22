typedef struct symbol_table_entry {
       char* name;
       int type_ident;  //0 : simple 1: array
       int eletype;         //same
       int dim;
       int valid;
       int num;
       double decimal;
       char character;
       int level;
       char* arraychar;
       int* arrayint;
       double* arraydouble;

       //intial
       double decimal_init;
       int num_init;
       char character_init;
       char* arraychar_init;
       int* arrayint_init;
       double* arraydouble_init;
} ste;

typedef struct temp_table_entry {
       char* name;
       int type;
} tte;

typedef struct next_list {
       int quad;
       struct next_list* next;
} nl;

typedef struct param_list {
       int param_type;
       char* param_name;
       struct param_list* next;
} prl;

typedef struct localvar_list {
       int var_ident_type;
       int dim;
       int var_eletype;
       char* var_name;
       struct localvar_list* next;
} lvl;

typedef struct func_table_entry {
       char* func_name;
       int res_type;
       prl* param_list_ptr;
       lvl* local_var_list;
       int num_params;
       int num_vars;
} fte;

typedef struct type_all1{
       int type;                   //0:num, 1:decimal, 2:char 4:ident 5:null 6:error_type 7:unimportant
       int num;
       double decimal;
       char character;
       char* name;
       char* namelist[20];
       int namelistnum;
       prl* paramlist[20];
       int paramlistnum;
       ste* st_entry;
       
       tte* result;
       nl* next;
       nl* falselist;
       int quad;
       char* label;
       int begin;
       int am_sd;                    //Mult : 0 OR Div : 1

       int ra_term_val;                   //0:>  1:<  2:>=  3:<=  4:==  5:!=
       ///////////////////////////////////////////
       char* tag;
       int num_children;
       int done;
       int done2;
       struct type_all1* child_list[15];
       struct type_all1* sibling;
       struct type_all1* back_sibling;
       int width;
       int lastwidth;
       struct type_all1* parent;
       int subtree_width;
       int depth;
       struct type_all1* leftChild;
       //////////////////////////////////////////////////
       int nodetype;
} typer;



#define TERMINAL 0
#define NONTERMINAL 1
#define SPACE 2
typer* create_node(int type, double decimal, int num_children, char* tag);