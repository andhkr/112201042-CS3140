#ifndef SYMBTBL_MANAGER_H
#define SYMBTBL_MANAGER_H

#include "symbol_table.h"

typedef struct manager{
    symbol_table** array;
    int capacity;
    int size;
    int current_table;
}symbtbl_manager;

extern symbtbl_manager manager;

void init_symbtbl_manager(symbtbl_manager* manager);

void allocation(symbtbl_manager* manager);

void push_back(symbtbl_manager* manager,symbol_table* symbtbl);

symbol_table* pop_back(symbtbl_manager* manager);
#endif