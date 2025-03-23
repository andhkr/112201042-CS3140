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
                    [FLOAT] "float",
                    [BOOL] "boolean"
              };
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

char *operations_name[] = {
    [PLUS] "PLUS",      [SUB] "SUB",       [MUL] "MUL",
    [DIV] "DIV",        [ASSIGN] "ASSIGN", [U_MINUS] "U_MINUS",
    [GREATERTHAN] "[>]",  [LESSTHAN] "[<]",    [LESST_EQUAL] "[<=]",
    [EQUAL_EQUAL] "[==]", [FUN_CALL] "CALL", [GREATT_EQUAL] "[>=]",
    [LESST_EQUAL] "[<=]", [NOT_EQAUL] "[!=]",  [Logical_NOT] "[!]",
    [Logical_AND] "[&&]", [Logical_OR] "[||]"};

/*less than*/
void lessthan_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal < d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void lessthan_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal < d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void lessthan_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer < d2->integer);
  update_data(result, &final, sizeof(bool));
}

void lessthan_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character < d2->character);
  update_data(result, &final, sizeof(bool));
}

/* lessthanision function pointers */
void (*lessthanops[])(datavalue *, datavalue *,
                      datavalue *) = {[INT] lessthan_int,
                                      [CHAR] lessthan_char,
                                      [FLOAT] lessthan_float,
                                      [DOUBLE] lessthan_double};

/*greaterthan than*/
void greaterthan_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal > d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void greaterthan_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal > d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void greaterthan_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer > d2->integer);
  update_data(result, &final, sizeof(bool));
}

void greaterthan_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character > d2->character);
  update_data(result, &final, sizeof(bool));
}

/* greaterthanision function pointers */
void (*greaterthanops[])(datavalue *, datavalue *,
                         datavalue *) = {[INT] greaterthan_int,
                                         [CHAR] greaterthan_char,
                                         [FLOAT] greaterthan_float,
                                         [DOUBLE] greaterthan_double};

/*greaterthaneq than*/
void greatteq_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal >= d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void greatteq_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal >= d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void greatteq_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer >= d2->integer);
  update_data(result, &final, sizeof(bool));
}

void greatteq_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character >= d2->character);
  update_data(result, &final, sizeof(bool));
}

/* greatteqision function pointers */
void (*greatteqops[])(datavalue *, datavalue *,
                      datavalue *) = {[INT] greatteq_int,
                                      [CHAR] greatteq_char,
                                      [FLOAT] greatteq_float,
                                      [DOUBLE] greatteq_double};

/*lessthaneq than*/
void lessteq_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal <= d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void lessteq_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal <= d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void lessteq_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer <= d2->integer);
  update_data(result, &final, sizeof(bool));
}

void lessteq_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character <= d2->character);
  update_data(result, &final, sizeof(bool));
}

/* lessteqision function pointers */
void (*lessteqops[])(datavalue *, datavalue *,
                     datavalue *) = {[INT] lessteq_int,
                                     [CHAR] lessteq_char,
                                     [FLOAT] lessteq_float,
                                     [DOUBLE] lessteq_double};

/*noteq than*/
void noteq_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal != d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void noteq_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal != d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void noteq_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer != d2->integer);
  update_data(result, &final, sizeof(bool));
}

void noteq_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character != d2->character);
  update_data(result, &final, sizeof(bool));
}

/* noteqision function pointers */
void (*noteqops[])(datavalue *, datavalue *,
                   datavalue *) = {[INT] noteq_int,
                                   [CHAR] noteq_char,
                                   [FLOAT] noteq_float,
                                   [DOUBLE] noteq_double};

/*iseq than*/
void isequal_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal == d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void isequal_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal == d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void isequal_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer == d2->integer);
  update_data(result, &final, sizeof(bool));
}

void isequal_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character == d2->character);
  update_data(result, &final, sizeof(bool));
}

/* isequalision function pointers */
void (*isequalops[])(datavalue *, datavalue *,
                     datavalue *) = {[INT] isequal_int,
                                     [CHAR] isequal_char,
                                     [FLOAT] isequal_float,
                                     [DOUBLE] isequal_double};

/*not than*/
void logNot_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = !(d1->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void logNot_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = !(d1->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void logNot_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = !(d1->integer);
  update_data(result, &final, sizeof(bool));
}

void logNot_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = !(d1->character);
  update_data(result, &final, sizeof(bool));
}

void logNot_bool(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = !(d1->boolean);
  update_data(result, &final, sizeof(bool));
}

/* logNotision function pointers */
void (*logNotops[])(datavalue *, datavalue *,
                    datavalue *) = {[INT] logNot_int,
                                    [CHAR] logNot_char,
                                    [FLOAT] logNot_float,
                                    [DOUBLE] logNot_double,
                                    [BOOL] logNot_bool};

/*and than*/
void logAnd_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal && d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void logAnd_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal && d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void logAnd_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer && d2->integer);
  update_data(result, &final, sizeof(bool));
}

void logAnd_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character && d2->character);
  update_data(result, &final, sizeof(bool));
}

void logAnd_bool(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->boolean && d2->boolean);
  update_data(result, &final, sizeof(bool));
}

/* logAndision function pointers */
void (*logAndops[])(datavalue *, datavalue *,
                    datavalue *) = {[INT] logAnd_int,
                                    [CHAR] logAnd_char,
                                    [FLOAT] logAnd_float,
                                    [DOUBLE] logAnd_double,
                                    [BOOL] logAnd_bool};

/*or than*/
void logOr_double(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->ldecimal || d2->ldecimal);
  update_data(result, &final, sizeof(bool));
}

void logOr_float(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->sdecimal || d2->sdecimal);
  update_data(result, &final, sizeof(bool));
}

void logOr_int(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->integer || d2->integer);
  update_data(result, &final, sizeof(bool));
}

void logOr_char(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->character || d2->character);
  update_data(result, &final, sizeof(bool));
}

void logOr_bool(datavalue *d1, datavalue *d2, datavalue *result) {
  bool final = (d1->boolean || d2->boolean);
  update_data(result, &final, sizeof(bool));
}

/* logOrision function pointers */
void (*logOrops[])(datavalue *, datavalue *,
                   datavalue *) = {[INT] logOr_int,
                                   [CHAR] logOr_char,
                                   [FLOAT] logOr_float,
                                   [DOUBLE] logOr_double,
                                   [BOOL] logOr_bool};