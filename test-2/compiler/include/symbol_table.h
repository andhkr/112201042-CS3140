#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "datatypes.h"

extern int Lineno;
extern int clen_for_var;
extern int clen_for_type;
extern int clen_for_val;
extern int row;

/*helper function for hashing*/
bool is_prime(long n);

int size_of_table(int expected_keys_count);

int hashvalue_of_key(char* key);

void* safe_alloc(size_t nmemb,size_t size);

/* symbol table entry specifications and member functions*/
typedef struct symbltblentry{
    char* name;
    datatype type; /* variable entry or function entry*/
    datavalue value;
    struct symbltblentry* next;
}symbltblentry;

symbltblentry* create_node(char* name,datatype type,datavalue value);

void init_entry(symbltblentry* entry,char* name,datatype type,datavalue value);

/* symbol table specification and member functions*/
typedef struct symbol_table{
    int (*hashvalue_of_key) (char*);
    symbltblentry* table;
    int capacity;
    int id;
    bool scope_level_truth;
    bool* used;
}symbol_table;

extern symbol_table* symbltbl;

symbol_table* create_symbtbl(int size,int (*hashvalue_of_key) (char*),int id);

symbltblentry* add_entry(symbol_table* symbtbl,char* name,datatype type,datavalue value);

symbltblentry *find_entry(symbol_table *symbtbl, char *name);

struct node;
void add_array_to_symbtbl(
    struct node* var,  /* already array name is created as node with type*/
    int n_ele   /* number of elements in array*/
);

void add_2Darray_to_symbtbl(
    struct node* var,  /* already array name is created as node with type*/
    int n_row , /* number of rows in array*/
    int n_col  /* number of column in array*/
);

#endif