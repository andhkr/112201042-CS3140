#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "ast.h"
#include "semantic.h"
#include "symbtbl_manager.h"

datavalue array_access(node *tree_node);

datavalue solve_expr(node *tree_node);

void solve_assign(node *tree_node);

int interprete(node *tree_node);

#endif