#ifndef  DATATYPES_H
#define DATATYPES_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
/*to store different data types in symbol table there are enum and union*/
typedef enum{
    INT,
    CHAR,
    STRING,
    DOUBLE,
    FLOAT,
    FUNCPTR,
    INTARRAY,
    DOUBLEARRAY,
    CHARARRAY,
    STRINGARRAY,
    ENTRY,
    OP,
    STATEMENT,
    BOOL
}datatype;

extern datatype curr_datatype;

typedef struct intarray{
    int* ptr;
    int capacity;
}intarray;

typedef struct doublearray{
    double* ptr;
    int capacity;
}doublearray;

typedef struct chararray{
    char* ptr;
    int capacity;
}chararray;

typedef struct stringarray{
    char** ptr;
    int capacity;
}stringarray;

typedef union{
    int integer;
    char character;
    char* string;
    double ldecimal;
    float  sdecimal;
    void* (*funcptr) (void);
    intarray intarr;
    doublearray dblarr;
    chararray   chararr;
    stringarray strarr;
    bool boolean;
}datavalue;

/* sizeof datatypes */
extern size_t datasize[] ;

/* string name */
extern char* typename[] ;
extern datavalue zero_set ;

bool is_zero(datavalue* d);

void update_data(void* dest,void* src,size_t datasize);

/* addition */
void add_double(datavalue* d1,datavalue* d2,datavalue* result);

void add_float(datavalue* d1,datavalue* d2,datavalue* result);

void add_int(datavalue* d1,datavalue* d2,datavalue* result);

void add_char(datavalue* d1,datavalue* d2,datavalue* result);

/* addition function pointers */
extern void (*add[])(datavalue*,datavalue*,datavalue*);

/* subtraction */
void sub_double(datavalue* d1,datavalue* d2,datavalue* result);

void sub_float(datavalue* d1,datavalue* d2,datavalue* result);

void sub_int(datavalue* d1,datavalue* d2,datavalue* result);

void sub_char(datavalue* d1,datavalue* d2,datavalue* result);

/* subtraction function pointers */
extern void (*sub[])(datavalue*,datavalue*,datavalue*);

/* multiplication */
void mul_double(datavalue* d1,datavalue* d2,datavalue* result);

void mul_float(datavalue* d1,datavalue* d2,datavalue* result);

void mul_int(datavalue* d1,datavalue* d2,datavalue* result);

void mul_char(datavalue* d1,datavalue* d2,datavalue* result);

/* multiplication function pointers */
extern void (*mul[])(datavalue*,datavalue*,datavalue*);

/* division */
void div_double(datavalue* d1,datavalue* d2,datavalue* result);

void div_float(datavalue* d1,datavalue* d2,datavalue* result);

void div_int(datavalue* d1,datavalue* d2,datavalue* result);

void div_char(datavalue* d1,datavalue* d2,datavalue* result);

/* division function pointers */
extern void (*divide[])(datavalue*,datavalue*,datavalue*);

/* negation */
void neg_double(datavalue* d1,datavalue* result);

void neg_float(datavalue* d1,datavalue* result);

void neg_int(datavalue* d1,datavalue* result);

void neg_char(datavalue* d1,datavalue* result);

/* negation function pointers */
extern void (*neg[])(datavalue*,datavalue*);

/* to manage statements, expression, operations, functions*/
typedef enum {
    PLUS,
    SUB,
    MUL,
    DIV,
    ASSIGN,
    U_MINUS,
    PERCENT,
    LESSTHAN,
    GREATERTHAN,
    GREATT_EQUAL, /*greater than or equal to */
    LESST_EQUAL,  /* less than or equal to*/
    NOT_EQAUL,
    EQUAL_EQUAL,
    Logical_NOT,
    Logical_AND,
    Logical_OR,
    FUN_CALL,
    ARRAY_ACCESS,
    BREAK
}opeartions;

typedef enum {
    IF_STMT,
    ELSE_IF_STMT,
    ELSE_STMT,
    FOR_STMT
}statements;


extern statements curr_statement;

extern char* operations_name[];

#endif