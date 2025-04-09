#define _GNU_SOURCE
#include "include/machine_code_generator.h"
#include <assert.h>

typedef struct rodata{
    char* asm_inst;
    struct rodata* next;
}rodata;

rodata* create_node_asm(){
    rodata* node = (rodata*) malloc(sizeof(rodata));
    assert(node != NULL);
    node->asm_inst = NULL;
    node->next = NULL;
    return node;
}

rodata* rodata_head;
rodata* curr;
extern char* file_sil;

/* Close the file when you’re done */
void close_asm_file(void) {
    if (assembly_file) {
        fclose(assembly_file);
        assembly_file = NULL;
    }
}


char* file_stem(const char* str){
	int i = 0;
	int d = 0;
	for(i = strlen(str)-1;i>=0;--i){
		if(str[i]=='/'){
			break;
		}else if(str[i]=='.'){
			d = i;
		}
	}
	i = i==0?0:i+1;

	char* file = (char*) malloc(sizeof(char)*((d-i)+3));

    
    printf("%d\n",(d-i));
	int j = 0;
	for(;i<=d;++i){
		file[j++]=str[i];
	}

	file[j++]='c';
	file[j++]='\0';
	return file;
}

/* Variadic writer: forwards format+args safely to the file */
void write_in_asm_file(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(assembly_file, fmt, args); 
    va_end(args);
    fputc('\n', assembly_file);
}

/* Emit the standard .bss variable directives */
void first_var(int align,size_t size, const char *name) {
    write_in_asm_file("     .globl %s", name);              
    write_in_asm_file("     .section .bss,\"aw\",@nobits");
    write_in_asm_file("     .align %d",align);      
    write_in_asm_file("     .type %s, @object", name);
    write_in_asm_file("     .size %s, %zu", name, size);
}

void analyse_node(node* root,char** name,size_t* size){
    if(strcmp(root->label,"array declaration")==0){
        node* subchild = root->ptr_children_list;
        (*name) = subchild->label;
        (*size) = (*size)*(atoi(subchild->ptr_sibling->label));
    }else{
        (*name) = root->label;
    }
}

void var_decl(int align,size_t size, const char *name){
    write_in_asm_file("     .space %zu",size);
    write_in_asm_file("     .globl %s", name);  
    write_in_asm_file("     .align %d", align);            
    write_in_asm_file("     .type %s, @object", name);
    write_in_asm_file("     .size %s, %zu", name, size);
}

void first_decl(node* root){
    node* child = root->ptr_children_list;
    char * type = child->label;
    size_t size = 0;
    int align   = 0;
    if(strcmp(type,"integer")==0){
        size = sizeof(int);
    }else if(strcmp(type,"boolean")==0){
        size = sizeof(bool);
    }
    align = log2(size);
    char* name = NULL;
    size_t cp_size = size;
    analyse_node(child->ptr_sibling,&name,&size);
    first_var(align,size,name);
    fprintf(assembly_file,"%s:\n",name);
    // fputc('\n', assembly_file);
    node* curr = child->ptr_sibling->ptr_sibling;
    while(curr){
        analyse_node(curr,&name,&size);
        var_decl(align,size,name);
        fprintf(assembly_file,"%s:\n",name);
        // fputc('\n', assembly_file);
        curr = curr->ptr_sibling;
        size = cp_size;
    }
}

void global_decl(node* root){
    node* child = root->ptr_children_list;
    char * type = child->label;
    size_t size = 0;
    int align   = 0;
    if(strcmp(type,"integer")==0){
        size = sizeof(int);
    }else if(strcmp(type,"boolean")==0){
        size = sizeof(bool);
    }
    align = log2(size);
    size_t cp_size = size;
    char* name = NULL;
    node* curr = child->ptr_sibling;
    while(curr){
        analyse_node(curr,&name,&size);
        var_decl(align,size,name);
        fprintf(assembly_file,"%s:\n",name);
        // fputc('\n', assembly_file);
        curr = curr->ptr_sibling;
        size = cp_size;
    }
}

int level = 0;
bool first_level = true;

void for_read(node* root){
    if(first_level){
        rodata_head = create_node_asm();
        curr = rodata_head;
        curr->asm_inst = strdup("\t.space	4\n");
        curr->next = create_node_asm();
        curr = curr->next;
        curr->asm_inst = strdup("\t.rdata\n");
        curr->next = create_node_asm();
        curr=curr->next;
        curr->asm_inst = strdup("\t.align	2\n");
        curr->next = create_node_asm();
        curr = curr->next;
        first_level = false;
    }
    // fprintf(assembly_file,"%d%d%d\000");
    node* child = root->ptr_children_list->ptr_sibling;
    while(child){
        asprintf(&curr->asm_inst, "$LC%d:\n", level);
        curr->next = create_node_asm();
        curr=curr->next;
        if(child->entry->type == INT){
            curr->asm_inst = strdup("\t.ascii  \"%d\\000\"\n");
            curr->next = create_node_asm();
            curr = curr->next;
            curr->asm_inst = strdup("\t.align 2\n");
            curr->next = create_node_asm();
            curr = curr->next;
            fprintf(assembly_file,"     la $5, %s\n",child->label);
            fprintf(assembly_file,"     la $4, $LC%d\n",level);
            fprintf(assembly_file,"     jal __isoc99_scanf\n");
        }
        ++level;
        child = child->ptr_sibling;
    }

}

void for_write(node* root){
    if(first_level){
        rodata_head = create_node_asm();
        curr = rodata_head;
        curr->asm_inst = strdup("\t.space	4\n");
        curr->next = create_node_asm();
        curr = curr->next;
        curr->asm_inst = strdup("\t.rdata\n");
        curr->next = create_node_asm();
        curr=curr->next;
        curr->asm_inst = strdup("\t.align	2\n");
        curr->next = create_node_asm();
        curr = curr->next;
        first_level = false;
    }
    // fprintf(assembly_file,"%d%d%d\000");
    node* child = root->ptr_children_list->ptr_sibling;
    while(child){
        asprintf(&curr->asm_inst, "$LC%d:\n", level);
        curr->next = create_node_asm();
        curr=curr->next;
        if(child->entry->type == INT){
            curr->asm_inst = strdup("\t.ascii  \"%d \\000\"\n");
            curr->next = create_node_asm();
            curr = curr->next;
            curr->asm_inst = strdup("\t.align 2\n");
            curr->next = create_node_asm();
            curr = curr->next;
            fprintf(assembly_file,"     la $5, %s\n",child->label);
            fprintf(assembly_file,"     lw $4, 0($5)\n");
            fprintf(assembly_file,"     move $5, $4\n");
            fprintf(assembly_file,"     la $4, $LC%d\n",level);
            fprintf(assembly_file,"     jal printf\n");
        }
        ++level;
        child = child->ptr_sibling;
    }
}

void insert_top(void){
    fprintf(assembly_file,
        "\t.file	1 \"%s\"\n"
	    "\t.section .mdebug.abi32\n"
	    "\t.previous\n"
	    "\t.nan	legacy\n"
	    "\t.module	fp=32\n"
	    "\t.module	nooddspreg\n"
	    "\t.abicalls\n"
	    "\t.text\n",file_sil);
}

void insert_main(void){
    fprintf(assembly_file,
    "\t.text\n"
    "\t.align 2\n"
    "\t.globl	main\n"
    "\t.set	nomips16\n"
    "\t.set	nomicromips\n"
    "\t.ent	main\n"
    "\t.type	main, @function\n"
    );
    fprintf(assembly_file,"main:\n");
    fprintf(assembly_file,
    "\t.frame	$fp,32,$31\n"
    "\t.mask	0xc0000000,-4\n"
    "\t.fmask	0x00000000,0\n"
    "\t.set	noreorder\n"
    "\t.cpload	$25\n"
    "\t.set	reorder\n"
    "\taddiu	$sp,$sp,-32\n"
    "\tsw	$31,28($sp)\n"
    "\tsw	$fp,24($sp)\n"
    "\tmove	$fp,$sp\n"
    "\t.cprestore	16\n"
    );
}

void insert_end(void){
    fprintf(assembly_file,
    "\tmove	$2,$0\n"
    "\tmove	$sp,$fp\n" 
    "\tlw	$31,28($sp)\n"
    "\tlw	$fp,24($sp)\n"
    "\taddiu	$sp,$sp,32\n"
    "\tj	$31\n"
    "\t.end	main\n"
    "\t.size	main, .-main\n"
    );
    curr = rodata_head;
    while(curr->next){
        fprintf(assembly_file,"%s",curr->asm_inst);
        curr = curr->next;
    }
    fprintf(assembly_file,
    "\t.ident	\"GCC: (Ubuntu 10.3.0-1ubuntu1) 10.3.0\"\n"
    "\t.section	.note.GNU-stack,\"\",@progbits\n"
    );
}