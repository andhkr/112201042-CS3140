#ifndef SYMBTBL_MANAGER_H
#define SYMBTBL_MANAGER_H

#include "symbol_table.h"

typedef struct manager{
    symbol_table** array;
    int capacity;
    int size;      /* it will be current scope*/
    int current_table; /* in a scope when searching for a variable */
}symbtbl_manager;

extern symbtbl_manager manager;

void init_symbtbl_manager(symbtbl_manager* manager);

void allocation(symbtbl_manager* manager);

void push_back(symbtbl_manager* manager,symbol_table* symbtbl);

void pop_back(symbtbl_manager* manager);

symbltblentry* get_entry(symbol_table* symbtbl,char* name);

void print_symbol_table();

void print_link_list(symbltblentry* head);

void print_entry(symbltblentry* entry);

void table_format();

void free_link_list(symbltblentry* head);

void free_symbol_table(symbol_table* symbtbl);

void free_symbol_table_manager(symbtbl_manager* manager);

#endif