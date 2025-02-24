#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"
#include "math.h"
int array_index(node* treenode);
void is_Array(node* left,node* right);

bool type_checking(node* left,node* right);

bool neg_type_check(node* right);

void Add(node* new_node,node* left,node* right);

void Sub(node* new_node,node* left,node* right);

void Mul(node* new_node,node* left,node* right);

void Div(node* new_node,node* left,node* right);
#endif