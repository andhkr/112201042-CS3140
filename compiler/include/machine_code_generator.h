#ifndef MACHINE_CODE_GENERATOR_H
#define MACHINE_CODE_GENERATOR_H

#include "stack.h"
#include "math.h"
extern FILE* assembly_file;
#include <stdarg.h>


char* file_stem(const char* str);

/* Close the file when you’re done */
void close_asm_file(void);

/* Variadic writer: forwards format+args safely to the file */
void write_in_asm_file(const char *fmt, ...);

/* Emit the standard .bss variable directives */
void first_var(int align,size_t size, const char *name);

void analyse_node(node* root,char** name,size_t* size);

void var_decl(int align,size_t size, const char *name);

void first_decl(node* root);

void global_decl(node* root);

void for_read(node* root);

void for_write(node* root);

void insert_top();

void insert_main();

void insert_end();
#endif