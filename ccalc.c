#include "ccalc.h"
#include <assert.h>
#define true 1
#define false 0
FILE* outtree;
FILE* fp;
// FILE* outerror;
int is_main = 0;
int is_func = 0;
fte* active_func = NULL;
int debug=0;
int error_flag = 0;
int param_cnt = 0;
char* current_refparam;
int params_list[100];

static FILE *file;
static int eof = 0;
static int nRow = 0;
static int nBuffer = 0;
static int lBuffer = 0;
static int nTokenStart = 0;
static int nTokenLength = 0;
static int nTokenNextStart = 0;
static int lMaxBuffer = 1000;
static char *buffer;

static
char dumpChar(char c) {
  if (  isprint(c)  )
    return c;
  return '@';
}
static
char *dumpString(char *s) {
  static char buf[101];
  int i;
  int n = strlen(s);

  if (  n > 100  )
    n = 100;

  for (i=0; i<n; i++)
    buf[i] = dumpChar(s[i]);
  buf[i] = 0;
  return buf;
}
extern
void DumpRow(void) {
  if (  nRow == 0  ) {
    int i;
    fprintf(outerror, "       |");
    for (i=1; i<71; i++)
      if (  i % 10 == 0  )
        fprintf(outerror, ":"); 
      else if (  i % 5 == 0  )
        fprintf(outerror, "+"); 
      else
        fprintf(outerror, ".");
    fprintf(outerror, "\n"); 
  }
  else 
    fprintf(outerror, "%6d |%.*s", nRow, lBuffer, buffer);
}
extern
void PrintError(const char *errorstring, ...) {
  static char errmsg[10000];
  va_list args;

  error_flag = 1;
  int start=nTokenStart;
  int end=start + nTokenLength - 1;
  int i;

  if (  eof  ) {
    fprintf(outerror, "\n...... !");
    for (i=0; i<lBuffer; i++)
      fprintf(outerror, ".");
    fprintf(outerror, "^-EOF\n");
  }
  else {
    fprintf(outerror, "\n...... !");
    for (i=1; i<start; i++)
      fprintf(outerror, ".");
    for (i=start; i<=end; i++)
      fprintf(outerror, "^");
    for (i=end+1; i<lBuffer; i++)
      fprintf(outerror, ".");
    fprintf(outerror, "   token%d:%d\n", start, end);
  }
  va_start(args, errorstring);
  vsprintf(errmsg, errorstring, args);
  va_end(args);

  fprintf(outerror, "Error: %s\n", errmsg);
}
char* print_code(typer* root){
  typer* temp = root;
  char* ans = (char *)malloc(20*sizeof(char));
  if(temp){
    for(int i=0; i<temp->num_children; i++){
      ans = print_code(temp->child_list[i]);
    }
    if(temp->nodetype==TERMINAL && temp->type!=5 && strcmp(temp->tag, "NULL")){
      if(!strcmp(temp->tag, "PLUS") || !strcmp(temp->tag, "MULT") || !strcmp(temp->tag, "DIV") || !strcmp(temp->tag, "MINUS")){
        char* g1 = (char*)malloc(20*sizeof(char));
        char* g2 = (char*)malloc(20*sizeof(char));
        g1 = "NAN";
        g2 = "NAN";
        typer* temp1 = temp;
        while(g1=="NAN" && temp->back_sibling){
          temp = temp->back_sibling;
          g1 = print_code(temp);
        }
        while(g2=="NAN" && temp1->sibling){
    // printf(">>>>>>>>> %s\n", temp->tag);
          temp1 = temp1->sibling;
          g2 = print_code(temp1);
        }
        // g1 = print_code(temp->back_sibling);
        // char* g2 = print_code(temp->sibling);
        printf("%s   %s\n", g1,g2);
        if(strcmp(g1, "NAN") && strcmp(g2, "NAN")){
          printf("t0 = %s\n", g1);
          printf("t1 = %s\n", g2);
          printf("t2 = t0 %s t1\n", temp->tag);
        }
      }else if(!strcmp(temp->tag, "FLOAT")){
        printf("t0 = %.2f\n", temp->decimal);
        return "t0";
      }else if(!strcmp(temp->tag, "NUM")){
        printf("t0 = %d\n", temp->num);
        return "t0";
      }
    return "t2";
    }
    return ans;
  }
  return "NAN";
}

static
int getNextLine(void) {
  int i;
  char *p;
  
  nBuffer = 0;
  nTokenStart = -1;
  nTokenNextStart = 1;
  eof = false;

  p = fgets(buffer, lMaxBuffer, file);
  if (  p == NULL  ) {
    if (  ferror(file)  )
      return -1;
    eof = true;
    return 1;
  }

  nRow += 1;
  lBuffer = strlen(buffer);
  DumpRow();

  return 0;
}
extern
int GetNextChar(char *b, int maxBuffer) {
  int frc;
  
  if (  eof  )
    return 0;
  
  while (  nBuffer >= lBuffer  ) {
    frc = getNextLine();
    if (  frc != 0  )
      return 0;
    }

  b[0] = buffer[nBuffer];
  nBuffer += 1;

  return b[0]==0?0:1;
}
extern
void BeginToken(char *t) {
  nTokenStart = nTokenNextStart;
  nTokenLength = strlen(t);
  nTokenNextStart = nBuffer;
}


//////////////////////////////////////////////////////

void width_init(typer* root){
  if(root){
    root->subtree_width = root->width = strlen(root->tag);
  }
}

void leftchildsetter(typer* root){
  if(root){
    if(root->num_children>0){
      root->leftChild = root->child_list[0]; 
    }else{
      root->leftChild = NULL;
    }
    typer* temp = root;
    for(int i=0; i<temp->num_children-1; i++){
      temp->child_list[i]->sibling = temp->child_list[i+1];
    }
    for(int i=1; i<temp->num_children; i++){
      temp->child_list[i]->back_sibling = temp->child_list[i-1];
    }
    temp = root;
    for(int i=0; i<temp->num_children; i++){
      leftchildsetter(temp->child_list[i]);
    }
  }
}
int calculateSubtreeDepth(typer* root,int depth)
{
  int maxdepth = depth;
  if(root=='\0')
    return 0;
  root->depth = depth;
  int childmaxdepth;
  typer* p = root->leftChild;
  while(p!='\0')
  {
    childmaxdepth = calculateSubtreeDepth(p,depth+1);
    p = p->sibling;
    maxdepth = maxdepth>childmaxdepth?maxdepth:childmaxdepth;
  }
  return maxdepth;
}

void addSpaceNode_ver(typer* root,int depth)
{
  assert(root->nodetype==TERMINAL);
  int i = 0;
   char *spaces = (char *)malloc((root->width+1)*(sizeof(char)));
    int j;
    for(j=0;j<root->width;j++)
    {
      spaces[j] = ' ' ;
    }
    spaces[j] = 0;
    // printf("%s %d ",spaces,root->width);
  for(;i<depth;i++)
  {
   
    root->leftChild = create_node(1, 0.00, 0,spaces);
    root->leftChild->nodetype = SPACE; 
    root = root->leftChild;
  }
}
void addSpaceNode_hor(typer* root){
  if( !root || root->nodetype==TERMINAL )
    return;
  int i = 0;
  int children_width=0;
  typer* p = root->leftChild;
  typer* prev = root->leftChild;

  while(1)
  {
    children_width += p->width;
    prev = p;
    p=p->sibling;
    
    if(p!='\0')
    {
      children_width++;
    }
    else
    {
      break;
    }
  }
  int space_width=root->width-children_width-1;
   char *spaces = (char *)malloc((space_width+1)*(sizeof(char)));
    int j;
    for(j=0;j<space_width;j++)
    {
      spaces[j] = ' ' ;
    }
    spaces[j] = 0;
    prev->sibling = create_node(1, 0.00, 0,spaces);
    // printf("%s %s\n", prev->tag, prev->sibling->tag);
}
int calculateSubtreeWidth(typer* root)
{
  if(root=='\0')
    return 0;
  if(root->leftChild=='\0')
    return root->width;
  int children_width = 0;
  typer* p = root->leftChild;
  while(1)
  {
    children_width += calculateSubtreeWidth(p);
    p=p->sibling;
    if(p!='\0')
    {
      children_width++;
    }
    else
    {
      break;
    }
  }
  root->subtree_width = (children_width>root->width)?children_width:root->width;
  if(root->width==root->subtree_width && root->leftChild){
      addSpaceNode_hor(root);
    } 
  return root->subtree_width; 
}
void printTree(typer* root)
{
  typer* temp = root;
  typer* leftmost = root;
  while(temp!='\0')
  {
    if(temp->width==temp->subtree_width){
      if(temp->nodetype!=SPACE)
        fprintf(outtree, "%s ",temp->tag);
      else
        fprintf(outtree, "%s ",temp->tag);
    }
    else{
      if(temp->nodetype!=SPACE)
        fprintf(outtree, "%s",temp->tag);
      else
        fprintf(outtree, "%s",temp->tag);
      int i=0;
      for(;i<=temp->subtree_width-temp->width;i++)
        fprintf(outtree, " ");
    }
    if(temp->sibling=='\0')
    {
      temp = leftmost->leftChild;
      leftmost = temp;
      fprintf(outtree, "\n");
    }
    else
      temp = temp->sibling;
  } 
}
void joinAllSiblings(typer* root,int maxdepth)
{
  typer* parent = root;
  typer* leftparent = root;
  while(parent!='\0')
  {
    typer* current = parent->leftChild;
    if(current=='\0')
      break;
    while(1)
    {
      // printf("check1 %s\n",parent->tag);
      int innerloopflag =0;
      while(current->sibling!='\0')
      { 
        // printf("check2 %s\n",current->tag);
        if(current->nodetype==TERMINAL)
        {
          // printf("check3\n");
          addSpaceNode_ver(current,maxdepth-current->depth);
        }
        current = current->sibling;
      }
      // printf("check2 %s\n",current->tag);
      if(current->nodetype==TERMINAL)
      {
        // printf("check3\n");
        addSpaceNode_ver(current,maxdepth-current->depth);
      }
      if(parent->sibling=='\0')
      {
        parent = leftparent->leftChild;
        leftparent = parent;
        break;
      }
      parent = parent->sibling;
      while(parent->leftChild=='\0')
      {
        if(parent=='\0')
        {
          parent = parent->leftChild;
          innerloopflag = 1;
          break;
        }
        parent = parent->sibling;
      }
      if(innerloopflag)
        break;
      current->sibling = parent->leftChild;
      current = parent->leftChild;
    }
  } 
}

char* replacer(char** s, int* index){
       char  *names[] = {"_t0", "_t1", "_t2", "_t3", "_t4", "_t5", "_t6", "_t7", "_t8", "_t9", "_t10", "_t11", "_t12", "_t13", "_t14", "_t15", "_t16", "_t17", "_t18", "_t19" };
       char *regs[] = { "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9"};
       int n = 18;
       for(int i=0; i<n; i++){
              if(strcmp(*s, names[i])==0){
                     strcpy(*s, regs[i]);
                     *index = i;
                     return regs[i];
              }
       }   
       return *s;
}
int countlines(FILE* fp){
       int ch;
       int ans = 0;
       while((ch=getc(fp))!=EOF){
              if((char)ch=='\n'){
                     ans++;
              }
       }
       return ans;
}
void strip2(char** inp){
       while(**inp==' ' || **inp=='\n' || **inp=='\t'){
              (*inp)++;
       }
       int l= strlen(*inp);
       while((*inp)[l-1]==' ' || (*inp)[l-1]=='\n' || (*inp)[l-1]=='\t'){
              l--;
              (*inp)[l]==0;
       }
}


char** get_tokens(char* line){
    // printf(":::::::: %s\n", line);
       char* tmp = (char *)malloc(strlen(line)*sizeof(char));
       // strcpy(tmp, line);

       char** ptr = &tmp;
       char* bla = (char *)malloc(strlen(line)*sizeof(char));
       memset(bla, 0, strlen(line));
       char** ans = (char **)malloc(10*sizeof(char *));
       memset(ans, 0, 10*sizeof(char*));
       for(int i=0; i<10; i++){
              ans[i] = (char *)malloc(100*sizeof(char));
              memset(ans[i], 0, 100*sizeof(char));
       }
       strcpy(tmp, line);

       int ind = 0;

       while((bla=strstr(tmp, " "))!=NULL){
              strncpy(ans[ind], tmp, bla-tmp);
              *ptr = bla+1;
              ind++;

       }

       strcpy(ans[ind], tmp);
       ans[ind+1]=NULL;
       return ans;
}

char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}

void replace1(char** inp, fte* func){
    prl* prlist = func->param_list_ptr;
    int which = 0;
    while(prlist){
        char** tokens = get_tokens(*inp);
        int k=0;
        char* argl = (char*)malloc(20*sizeof(char));
        memset(argl, 0, 20);
        sprintf(argl, "$a%d", which);
        while(tokens[k++]){
          if(strcmp(tokens[k-1], prlist->param_name)==0)
            *inp = str_replace(*inp, prlist->param_name, argl);
        }
        which++;
        prlist = prlist->next;
    }
}

void convert(char* line, char** tokens){
       int temp = 0;
       int flag = 0;
       if(is_func && active_func){
        // printf("***%s\n", line);
        char* before = line;
          replace1(&line, active_func);
          tokens = get_tokens(line);
          if(strcmp(line, before))
            flag = 1;
        // printf("***%s\n", line);
       }
       if(strstr(line, "[")==NULL && strstr(line, "=")!=NULL && strstr(line, ">")==NULL && strstr(line, "<")==NULL && strstr(line, "!")==NULL){
              if(strstr(line, "+")!=NULL){
                     fprintf(fp, "\tadd %s, %s, %s\n", replacer(&tokens[0], &temp), replacer(&tokens[2], &temp), replacer(&tokens[4], &temp));
              }else if(strstr(line, "-")!=NULL){
                     fprintf(fp, "\tsub %s, %s, %s\n", replacer(&tokens[0], &temp), replacer(&tokens[2], &temp), replacer(&tokens[4], &temp));
              }else if(strstr(line, "*")!=NULL){
                     fprintf(fp, "\tmult %s, %s\n", replacer(&tokens[2], &temp), replacer(&tokens[4], &temp));
                      fprintf(fp, "\tmflo %s\n", replacer(&tokens[0], &temp));
              }else if(strstr(line, "/")!=NULL){
                     fprintf(fp, "\tdiv %s, %s\n", replacer(&tokens[2], &temp), replacer(&tokens[4], &temp));
                      fprintf(fp, "\tmflo %s\n", replacer(&tokens[0], &temp));
              }else if(strstr(line, "GT")!=NULL){
                     fprintf(fp,"MOV A, %s\n", replacer(&tokens[0], &temp));
                     fprintf(fp,"SUB %s\n", replacer(&tokens[4], &temp));
                     fprintf(fp,"JM ");
              }else{
                     if(tokens[0][0]=='_' && strstr(line, "addr")==NULL){
                            if(isdigit(tokens[2][0])){
                                fprintf(fp,"\tli %s, %s\n", replacer(&tokens[0], &temp), replacer(&tokens[2], &temp));
                            }else{
                              if(!is_func || !active_func || !flag)
                                fprintf(fp,"\tlw %s, %s\n", replacer(&tokens[0], &temp), tokens[2]);
                              else
                                fprintf(fp,"\tmove %s, %s\n", replacer(&tokens[0], &temp), tokens[2]);
                            }
                     }else if(strstr(line, "addr")==NULL){
                          if(!is_func || !active_func || !flag)
                            fprintf(fp, "\tsw %s, %s\n", replacer(&tokens[2], &temp), tokens[0]);
                          else
                            fprintf(fp, "\tmove %s, %s\n", replacer(&tokens[0], &temp), tokens[2]);
                     }else{
                        char* tmp = (char *)malloc(20*sizeof(char));
                        tokens[2][strlen(tokens[2])-1] = 0;
                            fprintf(fp, "\tla %s, %s\n", replacer(&tokens[0], &temp), &tokens[2][5]);
                     }
              }
       }else if(strstr(line, "func begin")!=NULL){
              fprintf(fp,"%s:\n", tokens[2]);
              is_func = 1;
              active_func = functab_lookup(tokens[2]);
              if(!strcmp(tokens[2], "main")){
                is_main = 1;
              }else{
                fprintf(fp, "\taddi $sp,$sp,-4\n\tsw $s0,0($sp)\n\taddi $sp,$sp,-4\n\tsw $s1,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t0,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t1,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t2,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t3,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t4,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t5,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t6,0($sp)\n\taddi $sp,$sp,-4\n\tsw $t7,0($sp)\n");
              }
       }else if(strstr(line, "func end")!=NULL){
              if(!is_main){
                fprintf(fp, "\tlw $t7,0($sp)\n\taddi $sp,$sp,4\n\tlw $t6,0($sp)\n\taddi $sp,$sp,4\n\tlw $t5,0($sp)\n\taddi $sp,$sp,4\n\tlw $t4,0($sp)\n\taddi $sp,$sp,4\n\tlw $t3,0($sp)\n\taddi $sp,$sp,4\n\tlw $t2,0($sp)\n\taddi $sp,$sp,4\n\tlw $t1,0($sp)\n\taddi $sp,$sp,4\n\tlw $t0,0($sp)\n\taddi $sp,$sp,4\n\tlw $s1,0($sp)\n\taddi $sp,$sp,4\n\tlw $s0,0($sp)\n\taddi $sp,$sp,4\n\tjr $ra\n");
              }else{
                is_main = 0;
              }
              is_func = 0;
       }else if(strstr(line, ":")!=NULL){
              fprintf(fp, "\t%s\n", tokens[0]);
       }else if(strstr(line, ">=")!=NULL){
              fprintf(fp, "\tbge %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, "<=")!=NULL){
              fprintf(fp, "\tble %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, ">")!=NULL){
              fprintf(fp, "\tbgt %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, "<")!=NULL){
              fprintf(fp, "\tblt %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, "!=")!=NULL){
              fprintf(fp, "\tbne %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, "==")!=NULL){
              fprintf(fp, "\tbeq %s, %s, %s\n", replacer(&tokens[1], &temp), replacer(&tokens[3], &temp), tokens[5]);
       }else if(strstr(line, "param")!=NULL && strstr(line, "refparam")==NULL){
              fprintf(fp, "\tmove $a%d, %s\n", param_cnt, replacer(&tokens[1], &temp));
              params_list[param_cnt] = param_cnt;
              param_cnt++;
              // printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
       }else if(strstr(line, "refparam")!=NULL){
              memset(current_refparam, 0, 30);
              // printf(">>>>>>>>>>>>>>>>>>>>  %s\n", tokens[1]);
              strcpy(current_refparam, replacer(&tokens[1], &temp));
       }else if(strstr(line, "call")!=NULL){
              fprintf(fp, "\tjal %s\n", tokens[1]);
              param_cnt = 0;
              if(current_refparam){
                  fprintf(fp, "\tmove %s, $v0\n",current_refparam);
              }
       }else if(strstr(line, "[")!=NULL){
              char* arr = (char *)malloc(20*sizeof(char));
              char* ind = (char *)malloc(20*sizeof(char));
              char* tmp = (char *)malloc(20*sizeof(char));
              if(strstr(tokens[0], "[")!=NULL){
                  ind = strchr(tokens[0], '[');
                  ind++;
                  ind[strlen(ind)-1] = 0;
                  tmp = strchr(tokens[0], '[');
                  int till = tmp - tokens[0];
                  arr = tokens[0];
                  arr[till] = 0;
                  fprintf(fp, "\tadd $s0, %s, %s\n\tsw %s, 0($s0)\n", replacer(&arr, &temp), replacer(&ind, &temp), replacer(&tokens[2], &temp));
              }else if(strstr(tokens[2], "[")!=NULL){
                  ind = strchr(tokens[2], '[');
                  ind++;
                  ind[strlen(ind)-1] = 0;
                  tmp = strchr(tokens[2], '[');
                  int till = tmp - tokens[2];
                  arr = tokens[2];
                  arr[till] = 0;
                  fprintf(fp, "\tadd $s0, %s, %s\n\tlw %s, 0($s0)\n", replacer(&arr, &temp), replacer(&ind, &temp), replacer(&tokens[0], &temp));
              }
       }else if(strstr(line, "goto")!=NULL){
            fprintf(fp, "\tj %s\n", tokens[1]);
       }else if(strstr(line, "return")!= NULL){
            fprintf(fp, "\tmove $v0, %s\n", replacer(&tokens[1], &temp));
       }
}

//////////////////////////////////////////////////////////


extern
int main(int argc, char *argv[]) {
  int i;
  current_refparam = (char *)malloc(30*sizeof(char));
  outprod = fopen("output", "w+");        //output of reductions
  outerror = fopen("outerror", "w+");     //program string with errors marked, if any
  codefile = fopen("codefinal.s", "w+");
  fprintf(codefile, ".data\n");

  char *infile=NULL;
  debug = 0;
if(argc>1){
  outtree = fopen("outtree", "w+");
} else{
  outtree = stdout;
}
  for (i=1; i<argc; i++) {
    if (  strcmp(argv[i], "-debug") == 0  ) {
      printf("Debugging activated\n");
      debug = 1;
    }
    else if(i==2)
      infile = argv[i];
  }

  if (  infile == NULL  )
    infile = "inputfile";

  printf("Reading file '%s'\n", infile);
  file = fopen(infile, "r");
  if (  file == NULL  ) {
    printf("Cannot open input file!\n");
    return 12;
    }

  buffer = malloc(lMaxBuffer);
  if (  buffer == NULL  ) {
    printf("cannot allocate %d bytes of memory\n", lMaxBuffer);
    fclose(file);
    return 12;
  }

  DumpRow();
  if (  getNextLine() == 0  )             //start parsing
    yyparse();
  fprintf(codefile, ".text\n");
  free(buffer);
  fclose(file);
  fclose(outerror);
  fclose(outprod);
  system("python errorprinter.py");       //replace tokens with values
  if(error_flag)                          //if error found
    printf("\n***SYNTAX ERROR! COMPILATION TERMINATED!\n");
  else{
    if(!functab_lookup("main")){
      printf("ERROR : No Main Function Found!\n");
      return 0;
    }
    printf("\n***COMPILATION COMPLETED SUCCESSFULLY!\n");
    leftchildsetter(root);
    int treewidth = calculateSubtreeWidth(root); 
    int maxdepth = calculateSubtreeDepth(root,0);
    fprintf(outtree, "%d\n",treewidth);
    fprintf(outtree, "%d\n",maxdepth);
    printf("OUTPUT TREE IN FILE %s\n", argv[1]);
    fprintf(outtree, "-------------------------------------------------------------\nPARSE TREE FOR THE PARSE OF THE GIVEN INPUT:\n--------------------------------------------------\n");
    joinAllSiblings(root,maxdepth);
    printTree(root);
    print_code1();
    // write_data_part(codefile);
    fclose(codefile);
    fp = fopen("codefinal.s", "a+");
    FILE* infp = fopen("intcode", "r+");
    int count = countlines(infp);
    fseek(infp, 0, SEEK_SET);
    int i=0;
    char* line = (char *)malloc(100*sizeof(char));
    for(i=0; i<count; i++){
          fscanf(infp, " %[^\n]", line);
          strip2(&line);
          char** tokens;
          tokens = get_tokens(line);
          convert(line, tokens);
          memset(tokens, 0, sizeof(char**));
    }
    fprintf(fp, "\tli $v0, 10\n\tsyscall\n");
    fclose(infp);
    fclose(fp);
  }
  fclose(outtree);
  // fclose
  return 0;
}
