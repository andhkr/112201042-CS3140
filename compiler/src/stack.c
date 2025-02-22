#include "include/stack.h"

stmt_stack stm_stack;
stmt_stk_data prev_stmt;

void init_stmt_stack(stmt_stack* stack){
    stack->array        = (stmt_stk_data*) malloc(sizeof(stmt_stk_data)*16);
    stack->capacity     = 16;
    stack->sp           = 0;
    prev_stmt.cond_val  = false;
    prev_stmt.stmt      = -1;
}

void alloc_stmt_stk(stmt_stack* stack){
    stack->capacity = (stack->capacity)<<1;
    stmt_stk_data* arr = realloc(stack->array,stack->capacity);
    if(arr == NULL){
        fprintf(stderr,"error:stmatment stack resize failed\n");
        exit(EXIT_FAILURE);
    }
    stack->array = arr;
}

void push_stmt(
        stmt_stack* stack,
        statements stmt  /* the type of statement is pushed by lex which don't know the condition value*/
){
        if(stack->sp == stack->capacity) alloc_stmt_stk(stack);
        stack->array[(stack->sp)++].stmt = stmt;
}

void pop_stmt(stmt_stack* stack){
    if(stack->sp == 0){
        fprintf(stderr,"Error: statment stack is empty\n");
        exit(EXIT_FAILURE);
    }
    --(stack->sp);
    prev_stmt = stack->array[stack->sp];
    stack->cond_val = ((stack->sp != 0) ? (stack->array[(stack->sp-1)].cond_val) : (false) );
}