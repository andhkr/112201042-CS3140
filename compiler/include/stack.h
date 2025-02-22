#ifndef STACK_H
#define STACK_H

#include "include/datatypes.h"
#include <stdlib.h>

typedef struct data{
    statements stmt;
    bool cond_val;
}stmt_stk_data; /*statement stack data type*/

typedef struct stack{
    stmt_stk_data* array;   /*dynamic array*/
    int capacity;           /*array capacity*/
    int sp;                 /*stack pointer*/
    bool cond_val;
}stmt_stack;

extern stmt_stack stm_stack;
extern stmt_stk_data prev_stmt;

void init_stmt_stack(stmt_stack* stack);

void alloc_stmt_stk(stmt_stack* stack);

void push_stmt(
        stmt_stack* stack,
        statements stmt  /* the type of statement is pushed by lex which don't know the condition value*/
);

void pop_stmt(stmt_stack* stack);

#endif