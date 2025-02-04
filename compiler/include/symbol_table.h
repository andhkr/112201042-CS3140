#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*helper function for hashing*/
bool is_prime(long n);

int size_of_table(int expected_keys_count);

int hashvalue_of_key(char* key);

void* safe_alloc(size_t nmemb,size_t size);

/*to store different data types in symbol table there are enum and union*/
typedef enum{
    INT,
    CHAR,
    STRING,
    DOUBLE,
    FLOAT,
    FUNCPTR,
    ARRAY,
    ENTRY,
    OP,
    STATEMENT,
}datatype;

typedef union{
    int integer;
    char character;
    char* string;
    double ldecimal;
    float  sdecimal;
    void* (*funcptr) (void);
    void* array;
}datavalue;

/* symbol table entry specifications and member functions*/
typedef struct symbltblentry{
    char* name;
    datatype type; /* variable entry or function entry*/
    datavalue value;
    struct symbltblentry* next;
}symbltblentry;

symbltblentry* create_node(char* name,datatype type,datavalue value);

void init_entry(symbltblentry* entry,char* name,datatype type,datavalue value);

bool is_entryequal(symbltblentry* entry1,symbltblentry* entry2);

/* symbol table specification and member functions*/
typedef struct symbol_table{
    int (*hashvalue_of_key) (char*);
    symbltblentry* table;
    int capacity;
    int id;
}symbol_table;

extern symbol_table* symbtbl;

symbol_table* create_symbtbl(int size,int (*hashvalue_of_key) (char*),int id);

symbltblentry* add_entry(symbol_table* symbtbl,char* name,datatype type,datavalue value);

symbltblentry* get_entry(symbol_table* symbtbl,char* name,datatype type);

void print_symbol_table();
#endif