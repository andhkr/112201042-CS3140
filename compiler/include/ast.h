#ifndef AST_H
#define AST_H

#include "symbol_table.h"


typedef struct node{
    char* statement;
    symbltblentry* entry;
    struct node* left;
    struct node* right;
    int    exp_value;
}node;

void* safe_malloc(size_t size);

node* create_node_ast(char* statement,int exp_value,symbltblentry* entry);

void print_ast(node* root);

void printtree(node* root);

void print_decl(node* root);

int depth(node* root);
#endif
