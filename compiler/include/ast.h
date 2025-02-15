#ifndef AST_H
#define AST_H

#include "symbol_table.h"


typedef struct node{
    char* statement;
    symbltblentry* entry;
    struct node* left;
    struct node* right;
    datatype     type;
    datavalue    exp_value;
}node;

void* safe_malloc(size_t size);

node* create_node_ast(char op,symbltblentry* entry,node* left,node* right);

/* these are routines used by me for ast print*/
void print_ast(node* root);

void printtree(node* root);

void print_decl(node* root);

int depth(node* root);

/* 
inpired by Graph Source Code of LexAndYaccTutorial book 
*/
/*
i have done the modification wherever required for better look of graph
after understanding them properly.
*/

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
        int *ce, int *cm          /* resulting end column and mid of node */
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
