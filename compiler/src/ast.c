#include "include/semantic.h"

void *safe_malloc(size_t size) {
  void *ptr = malloc(size);
  if (ptr == NULL) {
    perror("Memory allocation Failed for astNode\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

void init_node(node *new_node, symbltblentry *entry, node *left, node *right,
               char *label) {
  new_node->entry = entry;
  new_node->ptr_children_list = left;
  left->ptr_sibling = right;
  new_node->label = label;
}

node *create_empty_node(char *label) {
  node *new_node = (node *)safe_alloc(1, sizeof(node));
  if (strlen(label) != 0)
    new_node->label = strdup(label);
  return new_node;
}

void if_stmt(bool* result){
  if(stm_stack.sp >= 2){
    *result = *result & stm_stack.array[(stm_stack.sp-2)].cond_val;
  }
  symbltbl->scope_level_truth = *result;
}

void else_if_stmt(bool* result){
  if(symbltbl->scope_level_truth){
    *result = false;
  }else{
    symbltbl->scope_level_truth = *result;
  }
}

void for_stmt(bool* result){
  
}

void (*stmts[])(bool*) = {
  [IF_STMT] if_stmt,
  [ELSE_IF_STMT] else_if_stmt,
  [FOR_STMT] for_stmt
};

void op_Add(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  Add(new_node, left, right);
  init_node(new_node, entry, left, right, "PLUS");
}

void op_Sub(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  Sub(new_node, left, right);
  init_node(new_node, entry, left, right, "SUB");
}

void op_Mul(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  Mul(new_node, left, right);
  init_node(new_node, entry, left, right, "MUL");
}

void op_Div(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  Div(new_node, left, right);
  init_node(new_node, entry, left, right, "DIV");
}

void op_Percent(node* new_node,symbltblentry *entry, node *left, node *right){

}

void op_Uminus(node* new_node,symbltblentry *entry, node *left, node *right){
  neg_type_check(right);
  neg[right->type](&new_node->exp_value, &right->exp_value);
  init_node(new_node, entry, left, right, "UMINUS");
}

void op_Assign(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  init_node(new_node, entry, left, right, "ASSIGN");
  switch (left->type) {
  case INTARRAY:
    intarray iarray = left->entry->value.intarr;
    int index = left->exp_value.integer;
    if (index >= iarray.capacity) {
      fprintf(stderr, "error:index out of bounds\n");
      exit(EXIT_FAILURE);
    }
    if(stm_stack.sp == 0 || stm_stack.cond_val){
    iarray.ptr[index] = right->exp_value.integer;
    }

    break;
  case DOUBLEARRAY:
    doublearray darray = left->entry->value.dblarr;
    index = left->exp_value.integer;
    if (index >= darray.capacity) {
      fprintf(stderr, "error:index out of bounds\n");
      exit(EXIT_FAILURE);
    }
    if(stm_stack.sp == 0 || stm_stack.cond_val)
    darray.ptr[index] = right->exp_value.ldecimal;
    break;
  case CHARARRAY:
    chararray carray = left->entry->value.chararr;
    index = left->exp_value.integer;
    if (index >= carray.capacity) {
      fprintf(stderr, "error:index out of bounds\n");
      exit(EXIT_FAILURE);
    }
    if(stm_stack.sp == 0 || stm_stack.cond_val)
    carray.ptr[index] = right->exp_value.character;
    break;
  case STRINGARRAY:
    stringarray sarray = left->entry->value.strarr;
    index = left->exp_value.integer;
    if (index >= sarray.capacity) {
      fprintf(stderr, "error:index out of bounds\n");
      exit(EXIT_FAILURE);
    }
    if(stm_stack.sp == 0 || stm_stack.cond_val)
    sarray.ptr[index] = right->exp_value.string;
    break;
  default:
  if(stm_stack.sp == 0 || stm_stack.cond_val)
    update_data(&left->entry->value, &right->exp_value,
                datasize[left->entry->type]);
  }
}

void op_FunCall(node* new_node,symbltblentry *entry, node *left, node *right){
  init_node(new_node, entry, left, right, "CALL");
}

void op_isEqual(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  memset(&new_node->exp_value,0,sizeof(datavalue));
  new_node->type = BOOL;
  bool result = false;
  if(memcmp(&left->exp_value,&right->exp_value,datasize[left->type])==0){
    result = true;
  }
  /* statement wise final value of result*/
  stmts[stm_stack.array[(stm_stack.sp-1)].stmt](&result);
  stm_stack.array[(stm_stack.sp-1)].cond_val = result;
  stm_stack.cond_val = result;
  init_node(new_node,entry,left,right,"==");
}

void op_isLessthan(node* new_node,symbltblentry *entry, node *left, node *right){
  type_checking(left, right);
  memset(&new_node->exp_value,0,sizeof(datavalue));
  new_node->type = BOOL;
  bool result = false;
  if(left->exp_value.integer < right->exp_value.integer){
    result = true;
  }
  /* statement wise final value of result*/
  stmts[stm_stack.array[(stm_stack.sp-1)].stmt](&result);
  stm_stack.array[(stm_stack.sp-1)].cond_val = result;
  stm_stack.cond_val = result;
  init_node(new_node,entry,left,right,"<");
}

void for_loop(node* tree_node){
  
}
void (*operator[])(node*,symbltblentry*, node*, node*)={
  [PLUS] op_Add,
  [SUB] op_Sub,
  [MUL] op_Mul,
  [DIV] op_Div,
  [ASSIGN] op_Assign,
  [U_MINUS] op_Uminus,
  [PERCENT] op_Percent,
  [LESSTHAN] op_isLessthan,
  [EQUAL_EQUAL] op_isEqual,
  [FUN_CALL] op_FunCall,
};

node *create_node_ast(opeartions op, symbltblentry *entry, node *left, node *right) {
  node *new_node = create_empty_node("");
  operator[op](new_node,entry,left,right);
  return new_node;
}

void make_node(node *array) {
  node *left = create_empty_node(array->entry->name);
  char word[13];
  snprintf(word, sizeof(word), "%d", array->exp_value.integer);
  node *right = create_empty_node(word);
  array->ptr_children_list = left;
  left->ptr_sibling = right;
}

int depth(node *root) {
  node *children = root->ptr_children_list;
  int d = 0;
  while (children) {
    int new_d = depth(children);
    d = (d > new_d ? d : new_d);
    children = children->ptr_sibling;
  }
  return d + 1;
}

/* inpired by Graph Source Code of LexAndYaccTutorial book */
int clmax = 0;
int rmax = 0;
int node_length;

char **canvas;

void init_graph(node *root) {
  int d = depth(root);
  rmax = 5 * d;
  node_length = ((clen_for_var < 20 ? 20 : clen_for_var));
  clmax = node_length * d;
  canvas = (char **)malloc(rmax * sizeof(char *));
  char *data = (char *)malloc(rmax * clmax * sizeof(char));

  if (!canvas || !data) {
    fprintf(stderr, "Memory Allocation for AST graph is failed\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < rmax; ++i) {
    canvas[i] = data + (i * clmax);
  }
  for (int i = 0; i < rmax; ++i) {
    for (int j = 0; j < clmax; ++j) {
      canvas[i][j] = ' ';
    }
  }
}

/* source code courtesy of Frank Thomas Braun */
int hmar = 2; /* distance of graph columns*/
int vmar = 3; /* distance of graph lines */
/* hmar = 2 is i find best */

/***********************************************************/
/* main entry point of the manipulation of the syntax tree */
int graph(node *root) {
  int rte = 0, rtm = 0;
  init_graph(root);
  print_tree(root, 0, 0, &rte, &rtm);
  graphFinish();
  return 0;
}

void print_tree(node *root, int c, int l, /* start column and line of node */
                int *ce, int *cm /* resulting end column and mid of node */
) {
  int w, h;     /* node width and height */
  char *s;      /* node text */
  int cbar;     /* "real" start column of node (centred above subnodes)*/
  int che, chm; /* end column and mid of children */
  int cs;       /* start column of children */
  if (!root)
    return;
  s = root->label;
  /* construct node text box */
  graphBox(s, &w, &h);
  cbar = c;
  *ce = c + w;
  *cm = c + w / 2;

  /* node is leaf */
  node *children = root->ptr_children_list;
  if (children == NULL) {
    graphDrawBox(s, cbar, l);
    return;
  }

  /* node has children */
  cs = c;
  while (children) {
    print_tree(children, cs, l + h + vmar, &che, &chm);
    cs = che;
    children = children->ptr_sibling;
  }

  /* total node width */
  if (w < che - c) {
    cbar += (che + (hmar - 1) - c - w) / 2;
    *ce = che;
    *cm = (c + che) / 2;
  }

  /* draw node */
  graphDrawBox(s, cbar, l);

  /* draw arrows (not optimal: children are drawn a second time) */
  children = root->ptr_children_list;
  cs = c;
  while (children) {
    print_tree(children, cs, l + h + vmar, &che, &chm);
    graphDrawArrow(*cm, l + h, chm, l + h + vmar - 1);
    cs = che;
    children = children->ptr_sibling;
  }
}

// int graphNumber = 0;

void graphTest(int l, int c) {
  int ok;
  ok = 1;
  if (l < 0)
    ok = 0;
  if (l >= rmax)
    ok = 0;
  if (c < 0)
    ok = 0;
  if (c >= clmax)
    ok = 0;
  if (ok)
    return;
  fprintf(stderr,
          "\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d"
          " you need to modify int init_graph function",
          l, c, rmax, clmax);
  exit(EXIT_FAILURE);
}

void graphFinish() {
  int i, j;
  for (i = 0; i < rmax; i++) {
    for (j = clmax - 1; j > 0 && canvas[i][j] == ' '; j--)
      ;
    canvas[i][clmax - 1] = 0;
    if (j < clmax - 1)
      canvas[i][j + 1] = 0;
    if (canvas[i][j] == ' ')
      canvas[i][j] = 0;
  }
  for (i = rmax - 1; i > 0 && canvas[i][0] == 0; i--)
    ;
  // printf ("\n\nGraph %d:\n", graphNumber++);
  for (j = 0; j <= i; j++)
    printf("\n%s", canvas[j]);
  printf("\n");
}

void graphBox(char *s, int *w, int *h) {
  *w = strlen(s) + hmar;
  *h = 1;
}

void graphDrawBox(char *s, int c, int l) {
  int i;
  graphTest(l, c + strlen(s) - 1 + hmar);
  for (i = 0; i < strlen(s); i++) {
    canvas[l][c + i + hmar] = s[i];
  }
}

void graphDrawArrow(int c1, int l1, int c2, int l2) {
  int m;
  c1 = c1 + hmar - 1;
  c2 = c2 + hmar - 1;
  graphTest(l1, c1);
  graphTest(l2, c2);
  m = (l1 + l2) / 2;
  while (l1 != m) {
    canvas[l1][c1] = '|';
    if (l1 < l2)
      l1++;
    else
      l1--;
  }
  while (c1 != c2) {
    canvas[l1][c1] = '-';
    if (c1 < c2)
      c1++;
    else
      c1--;
  }
  while (l1 != l2) {
    canvas[l1][c1] = '|';
    if (l1 < l2)
      l1++;
    else
      l1--;
  }
  canvas[l1][c1] = 'v';
}

void free_graph() {
  free(canvas[0]);
  free(canvas);
}
