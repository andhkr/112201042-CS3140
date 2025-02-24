#include "include/datatypes.h"

datatype curr_datatype = 10;
statements curr_statement = 0;
/* sizeof datatypes */
size_t datasize[] = {
    [INT] sizeof(int),     [CHAR] sizeof(char), [DOUBLE] sizeof(double),
    [FLOAT] sizeof(float), [BOOL] sizeof(bool),
};

/* string name */
char *typename[] = {[INT] "int",
                    [CHAR] "char*",
                    [STRING] "char*",
                    [DOUBLE] "double",
                    [FLOAT] "float"};
datavalue zero_set = {0};

bool is_zero(datavalue *d) {
  return memcmp(d, &zero_set, sizeof(datavalue)) == 0;
}

void update_data(void *dest, void *src, size_t datasize) {
  memset(dest, 0, sizeof(datavalue));
  memcpy(dest, src, datasize);
}

/* addition */
void add_double(datavalue *d1, datavalue *d2, datavalue *result) {
  double final = d1->ldecimal + d2->ldecimal;
  update_data(result, &final, sizeof(double));
}

void add_float(datavalue *d1, datavalue *d2, datavalue *result) {
  float final = d1->sdecimal + d2->sdecimal;
  update_data(result, &final, sizeof(float));
}

void add_int(datavalue *d1, datavalue *d2, datavalue *result) {
  int final = d1->integer + d2->integer;
  update_data(result, &final, sizeof(int));
}

void add_char(datavalue *d1, datavalue *d2, datavalue *result) {
  char final = d1->character + d2->character;
  update_data(result, &final, sizeof(char));
}

void (*add[])(datavalue *, datavalue *, datavalue *) = {
    [INT] add_int, [CHAR] add_char, [FLOAT] add_float, [DOUBLE] add_double};

/* subtraction */
void sub_double(datavalue *d1, datavalue *d2, datavalue *result) {
  double final = d1->ldecimal - d2->ldecimal;
  update_data(result, &final, sizeof(double));
}

void sub_float(datavalue *d1, datavalue *d2, datavalue *result) {
  float final = d1->sdecimal - d2->sdecimal;
  update_data(result, &final, sizeof(float));
}

void sub_int(datavalue *d1, datavalue *d2, datavalue *result) {
  int final = d1->integer - d2->integer;
  update_data(result, &final, sizeof(int));
}

void sub_char(datavalue *d1, datavalue *d2, datavalue *result) {
  char final = d1->character - d2->character;
  update_data(result, &final, sizeof(char));
}

void (*sub[])(datavalue *, datavalue *, datavalue *) = {
    [INT] sub_int, [CHAR] sub_char, [FLOAT] sub_float, [DOUBLE] sub_double};

/* multiplication */
void mul_double(datavalue *d1, datavalue *d2, datavalue *result) {
  double final = d1->ldecimal * d2->ldecimal;
  update_data(result, &final, sizeof(double));
}

void mul_float(datavalue *d1, datavalue *d2, datavalue *result) {
  float final = d1->sdecimal * d2->sdecimal;
  update_data(result, &final, sizeof(float));
}

void mul_int(datavalue *d1, datavalue *d2, datavalue *result) {
  int final = d1->integer * d2->integer;
  update_data(result, &final, sizeof(int));
}

void mul_char(datavalue *d1, datavalue *d2, datavalue *result) {
  char final = d1->character * d2->character;
  update_data(result, &final, sizeof(char));
}

void (*mul[])(datavalue *, datavalue *, datavalue *) = {
    [INT] mul_int, [CHAR] mul_char, [FLOAT] mul_float, [DOUBLE] mul_double};

/* division */
void div_double(datavalue *d1, datavalue *d2, datavalue *result) {
  double final = d1->ldecimal / d2->ldecimal;
  update_data(result, &final, sizeof(double));
}

void div_float(datavalue *d1, datavalue *d2, datavalue *result) {
  float final = d1->sdecimal / d2->sdecimal;
  update_data(result, &final, sizeof(float));
}

void div_int(datavalue *d1, datavalue *d2, datavalue *result) {
  int final = d1->integer / d2->integer;
  update_data(result, &final, sizeof(int));
}

void div_char(datavalue *d1, datavalue *d2, datavalue *result) {
  char final = d1->character / d2->character;
  update_data(result, &final, sizeof(char));
}

void (*divide[])(datavalue *, datavalue *, datavalue *) = {
    [INT] div_int, [CHAR] div_char, [FLOAT] div_float, [DOUBLE] div_double};

/* negation */

void neg_double(datavalue *d1, datavalue *result) {
  double final = -d1->ldecimal;
  update_data(result, &final, sizeof(double));
}

void neg_float(datavalue *d1, datavalue *result) {
  float final = -d1->sdecimal;
  update_data(result, &final, sizeof(float));
}

void neg_int(datavalue *d1, datavalue *result) {
  int final = -(d1->integer);
  update_data(result, &final, sizeof(int));
}

void neg_char(datavalue *d1, datavalue *result) {
  char final = -d1->character;
  update_data(result, &final, sizeof(char));
}

void (*neg[])(datavalue *, datavalue *) = {
    [INT] neg_int, [CHAR] neg_char, [FLOAT] neg_float, [DOUBLE] neg_double};

char* operations_name[]={
  [PLUS] "PLUS",
  [SUB]  "SUB",
  [MUL] "MUL",
  [DIV] "DIV",
  [ASSIGN] "ASSIGN",
  [U_MINUS] "U_MINUS",
  [GREATERTHAN] ">",
  [LESSTHAN] "<",
  [LESST_EQUAL] "<=",
  [EQUAL_EQUAL] "==",
  [FUN_CALL] "CALL"
};