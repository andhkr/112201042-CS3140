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
    MODULO,
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

/*less than*/
void lessthan_double(datavalue* d1,datavalue* d2,datavalue* result);

void lessthan_float(datavalue* d1,datavalue* d2,datavalue* result);

void lessthan_int(datavalue* d1,datavalue* d2,datavalue* result);

void lessthan_char(datavalue* d1,datavalue* d2,datavalue* result);

/* lessthanision function pointers */
extern void (*lessthanops[])(datavalue*,datavalue*,datavalue*);

/*greaterthan than*/
void greaterthan_double(datavalue* d1,datavalue* d2,datavalue* result);

void greaterthan_float(datavalue* d1,datavalue* d2,datavalue* result);

void greaterthan_int(datavalue* d1,datavalue* d2,datavalue* result);

void greaterthan_char(datavalue* d1,datavalue* d2,datavalue* result);

/* greaterthanision function pointers */
extern void (*greaterthanops[])(datavalue*,datavalue*,datavalue*);

/*greaterthaneq than*/
void greatteq_double(datavalue* d1,datavalue* d2,datavalue* result);

void greatteq_float(datavalue* d1,datavalue* d2,datavalue* result);

void greatteq_int(datavalue* d1,datavalue* d2,datavalue* result);

void greatteq_char(datavalue* d1,datavalue* d2,datavalue* result);

/* greatteqision function pointers */
extern void (*greatteqops[])(datavalue*,datavalue*,datavalue*);

/*lessthaneq than*/
void lessteq_double(datavalue* d1,datavalue* d2,datavalue* result);

void lessteq_float(datavalue* d1,datavalue* d2,datavalue* result);

void lessteq_int(datavalue* d1,datavalue* d2,datavalue* result);

void lessteq_char(datavalue* d1,datavalue* d2,datavalue* result);

/* lessteqision function pointers */
extern void (*lessteqops[])(datavalue*,datavalue*,datavalue*);

/*noteq than*/
void noteq_double(datavalue* d1,datavalue* d2,datavalue* result);

void noteq_float(datavalue* d1,datavalue* d2,datavalue* result);

void noteq_int(datavalue* d1,datavalue* d2,datavalue* result);

void noteq_char(datavalue* d1,datavalue* d2,datavalue* result);

/* noteqision function pointers */
extern void (*noteqops[])(datavalue*,datavalue*,datavalue*);

/*iseq than*/
void isequal_double(datavalue* d1,datavalue* d2,datavalue* result);

void isequal_float(datavalue* d1,datavalue* d2,datavalue* result);

void isequal_int(datavalue* d1,datavalue* d2,datavalue* result);

void isequal_char(datavalue* d1,datavalue* d2,datavalue* result);

/* isequalision function pointers */
extern void (*isequalops[])(datavalue*,datavalue*,datavalue*);

/*not than*/
void logNot_double(datavalue* d1,datavalue* d2,datavalue* result);

void logNot_float(datavalue* d1,datavalue* d2,datavalue* result);

void logNot_int(datavalue* d1,datavalue* d2,datavalue* result);

void logNot_char(datavalue* d1,datavalue* d2,datavalue* result);

void logNot_bool(datavalue* d1,datavalue* d2,datavalue* result);

/* logNotision function pointers */
extern void (*logNotops[])(datavalue*,datavalue*,datavalue*);

/*and than*/
void logAnd_double(datavalue* d1,datavalue* d2,datavalue* result);

void logAnd_float(datavalue* d1,datavalue* d2,datavalue* result);

void logAnd_int(datavalue* d1,datavalue* d2,datavalue* result);

void logAnd_char(datavalue* d1,datavalue* d2,datavalue* result);

void logAnd_bool(datavalue* d1,datavalue* d2,datavalue* result);

/* logAndision function pointers */
extern void (*logAndops[])(datavalue*,datavalue*,datavalue*);

/*or than*/
void logOr_double(datavalue* d1,datavalue* d2,datavalue* result);

void logOr_float(datavalue* d1,datavalue* d2,datavalue* result);

void logOr_int(datavalue* d1,datavalue* d2,datavalue* result);

void logOr_char(datavalue* d1,datavalue* d2,datavalue* result);

void logOr_bool(datavalue* d1,datavalue* d2,datavalue* result);

/* logOrision function pointers */
extern void (*logOrops[])(datavalue*,datavalue*,datavalue*);

typedef enum {
    IF_STMT,
    ELSE_IF_STMT,
    ELSE_STMT,
    FOR_STMT
}statements;


extern statements curr_statement;

extern char* operations_name[];

#endif