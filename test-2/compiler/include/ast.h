#ifndef AST_H
#define AST_H

#include "symbol_table.h"
#include <assert.h>

typedef struct node{
    char* label;
    datatype     type;
    datavalue    exp_value;
    opeartions   op;
    symbltblentry* entry;
    struct node* ptr_children_list;
    struct node* ptr_sibling;
}node;

void* safe_malloc(size_t size);

node* create_empty_node(char* label);

node* create_node_ast(opeartions op, symbltblentry *entry, node *left, node *right);

void op_Add(node *new_node, symbltblentry *entry, node *left, node *right);

void op_Sub(node *new_node, symbltblentry *entry, node *left, node *right);

void op_Mul(node *new_node, symbltblentry *entry, node *left, node *right);

void op_Div(node *new_node, symbltblentry *entry, node *left, node *right);

void op_modulo(node *new_node, symbltblentry *entry, node *left, node *right);

void op_Uminus(node *new_node, symbltblentry *entry, node *left, node *right);

void op_FunCall(node *new_node, symbltblentry *entry, node *left, node *right);

void op_isEqual(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_isLessthan(node *new_node, symbltblentry *entry, node *left,node *right);
  
void op_isGreatt(node *new_node, symbltblentry *entry, node *left,node *right);
  
void op_isgreatteq(node *new_node, symbltblentry *entry, node *left,node *right);
  
void op_islessteq(node *new_node, symbltblentry *entry, node *left,node *right);
  
void op_isNoteq(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_logNot(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_logAnd(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_logOr(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_Assign(node *new_node, symbltblentry *entry, node *left, node *right);
  
void op_break(node *new_node, symbltblentry *entry, node *left, node *right);

extern void (*operator[])(node *, symbltblentry *, node *, node *);

void make_node(node* array);

void init_graph(node* root);

int graph (node *root);
/*c----cm---ce---->            drawing of leaf-nodes
 l leaf-info
 */

/*c---------------cm--------------ce----> drawing of non-leaf-nodes 
l                 node-info
*                    |
*         ------------- ...----
*        |        |            | 
*        v        v            v
*     child1     child2 ...     child-n
*     che     che           che 
*    cs         cs         cs         cs 
*
*/

void print_tree(  
        node *root,
        int c, int l,        /* start column and line of node */
        int *ce, int *cm     /* resulting end column and mid of node */
) 
;

/* interface for drawing */

void graphTest (int l, int c);

void graphFinish();

void graphBox (char *s, int *w, int *h);

void graphDrawBox (char *s, int c, int l) ;

void graphDrawArrow (int c1, int l1, int c2, int l2);

void free_graph();

#endif
