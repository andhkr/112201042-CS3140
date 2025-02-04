#ifndef AST_H
#define AST_H

#include "symbol_table.h"

typedef union{
    symbltblentry* entry;
    char op;
    char* statement;
    int num;
}nodevalue;


typedef struct node{
    datatype type;
    nodevalue value;
    struct node* left;
    struct node* right;
    int    exp_value;
}node;

void* safe_malloc(size_t size);

node* create_node_ast(datatype type,nodevalue value,int exp_value);

void print_ast(node* root);
#endif
