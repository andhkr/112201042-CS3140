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

    
    // printf("%d\n",(d-i));
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
    write_in_asm_file("\t.globl %s", name);              
    write_in_asm_file("\t.section .bss,\"aw\",@nobits");
    write_in_asm_file("\t.align %d",align);      
    write_in_asm_file("\t.type %s, @object", name);
    write_in_asm_file("\t.size %s, %zu", name, size);
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
    write_in_asm_file("\t.globl %s", name);  
    write_in_asm_file("\t.align %d", align);            
    write_in_asm_file("\t.type %s, @object", name);
    write_in_asm_file("\t.size %s, %zu", name, size);
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
    write_in_asm_file("\t.space %zu",size);
    // fputc('\n', assembly_file);
    node* curr = child->ptr_sibling->ptr_sibling;
    while(curr){
        analyse_node(curr,&name,&size);
        var_decl(align,size,name);
        fprintf(assembly_file,"%s:\n",name);
        write_in_asm_file("\t.space %zu",size);
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
        write_in_asm_file("\t.space %zu",size);
        // fputc('\n', assembly_file);
        curr = curr->ptr_sibling;
        size = cp_size;
    }
}

int array_index(node *treenode);
void array_index_insert(node* root);

void getting_addr_ps(node* var){
    // char* addr = (char*) malloc((sizeof(char))*(str_len(var->label)+7));
    if(strcmp(var->label,"ArrayAccess")!=0 &&  var->entry->type == INT){
        fprintf(assembly_file,"\tla $5,%s\n",var->label);
    }else if(strcmp(var->label,"ArrayAccess")==0 && var->entry->type == INTARRAY){
        fprintf(assembly_file,"\tla $5,%s\n",var->ptr_children_list->label);
        array_index_insert(var->ptr_children_list->ptr_sibling->ptr_children_list);
        fprintf(assembly_file,"\taddu $5, $5, $10\n");
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
        if(child->entry->type == INT || child->entry->type == INTARRAY){
            curr->asm_inst = strdup("\t.ascii  \"%d\\000\"\n");
            curr->next = create_node_asm();
            curr = curr->next;
            curr->asm_inst = strdup("\t.align 2\n");
            curr->next = create_node_asm();
            curr = curr->next;
            getting_addr_ps(child);
            fprintf(assembly_file,"\tla $4, $LC%d\n",level);
            fprintf(assembly_file,"\tjal __isoc99_scanf\n");
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
        curr->asm_inst = strdup("\t.ascii  \"%d \\012\\000\"\n");
        curr->next = create_node_asm();
        curr = curr->next;
        curr->asm_inst = strdup("\t.align 2\n");
        curr->next = create_node_asm();
        curr = curr->next;
        // getting_addr_ps(child);
        solve_expr_ins(child);
        fprintf(assembly_file,"\tlw $4, %zu($fp)\n",sizeof(int));
        fprintf(assembly_file,"\taddiu $fp,$fp,%zu\n",sizeof(int));
        fprintf(assembly_file,"\tmove $5, $4\n");
        fprintf(assembly_file,"\tla $4, $LC%d\n",level);
        fprintf(assembly_file,"\tjal printf\n");
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


char* mipscmd[] = {
    [PLUS] = "add",
    [SUB] = "sub",
    [MUL] = "mul",
    [DIV] = "div",
  //   [ASSIGN] = op_Assign,
  //   [U_MINUS] = op_Uminus,
  //   [MODULO] = op_modulo,
    [LESSTHAN] = "blt",
    [EQUAL_EQUAL] = "beq",
  //   [FUN_CALL] = op_FunCall,
    [BREAK] = "j",
    [GREATERTHAN] = "bgt",
    [GREATT_EQUAL] = "bge",
    [LESST_EQUAL] = "ble",
    [NOT_EQAUL] = "bne",
    [Logical_NOT] = "not",
    [Logical_AND] = "and",
    [Logical_OR] = "or",
  };

void load_from_stack(size_t size){
    fprintf(assembly_file,"\tlw $9,%zu($fp)\n",size);
    fprintf(assembly_file,"\tlw $8,%zu($fp)\n",(size<<1));
}

void store_on_stack(size_t size){
    fprintf(assembly_file,"\taddiu $fp,$fp,%zu\n",size);
    fprintf(assembly_file,"\tsw $8,%zu($fp)\n",size);
}

void solve_expr_ins(node *tree_node) {
    if(tree_node == NULL) return;
    size_t size = sizeof(int); 
    switch (tree_node->op) {
    case PLUS:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        load_from_stack(size);
        fprintf(assembly_file,"\tadd $8,$8,$9\n");
        store_on_stack(size);
        break;
    }
    case SUB:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        load_from_stack(size);
        fprintf(assembly_file,"\tsub $8,$8,$9\n");
        store_on_stack(size);
        break;
    }
    case MUL:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        load_from_stack(size);
        fprintf(assembly_file,"\tmul $8,$8,$9\n");
        store_on_stack(size);
        break;
    }
    case DIV:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        load_from_stack(size);
        fprintf(assembly_file,"\tdiv $8,$8,$9\n");
        store_on_stack(size);
        break;
    }
    case LESSTHAN:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        load_from_stack(size);
        fprintf(assembly_file,"\tlt $8,$8,$9\n");
        store_on_stack(size);
        break;
    }
    case U_MINUS:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
        fprintf(assembly_file,"\tlw $8,%zu($fp)\n",size);
        // fprintf(assembly_file,"\taddiu $fp,$f,%zu\n",sizeof(int));
        fprintf(assembly_file,"\tsub $8,$0,$8\n");
        fprintf(assembly_file,"\tsw $8,%zu($fp)\n",size);
        // fprintf(assembly_file,"\tadd $8,$0,")
        break;
    }
    case EQUAL_EQUAL:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case GREATERTHAN:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case GREATT_EQUAL:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case LESST_EQUAL:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case MODULO:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case Logical_AND:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case Logical_OR:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    case Logical_NOT:{
        solve_expr_ins(tree_node->ptr_children_list);
        solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);

        break;
    }
    default:
      if (strcmp(tree_node->label, "ArrayAccess") == 0) {
        array_index_insert(tree_node->ptr_children_list->ptr_sibling->ptr_children_list);
        fprintf(assembly_file,"\tla $8, %s\n",tree_node->ptr_children_list->label);
        fprintf(assembly_file,"\taddu $8, $8, $10\n");
        fprintf(assembly_file,"\tlw $8, 0($8)\n");
        fprintf(assembly_file,"\taddiu $fp, $fp, -%zu\n",sizeof(int));
        fprintf(assembly_file,"\tsw $8, %zu($fp)\n",sizeof(int));
      } else if(tree_node->entry){  
        fprintf(assembly_file,"\tla $8, %s\n",tree_node->label);
        fprintf(assembly_file,"\tlw $8, 0($8)\n");
        fprintf(assembly_file,"\taddiu $fp, $fp, -4\n");
        fprintf(assembly_file,"\tsw $8, %zu($fp)\n",size);
      }else{
        fprintf(assembly_file,"\tadd $8,$0,%s\n",tree_node->label);
        fprintf(assembly_file,"\taddiu $fp, $fp, -4\n");
        fprintf(assembly_file,"\tsw $8, %zu($fp)\n",size);
      }
    }
  }
  
  void array_index_insert(node* root){
    solve_expr_ins(root);
    fprintf(assembly_file,"\tlw $10,%zu($fp)\n",sizeof(int));
    fprintf(assembly_file,"\taddiu $fp, $fp, %zu\n",sizeof(int));
    fprintf(assembly_file,"\tmul $10, $10, %zu\n",sizeof(int));
  }

  void solve_assign_ins(node *tree_node) {
    if(tree_node==NULL) return;
    node *l_value = tree_node->ptr_children_list;
    node *r_value = l_value->ptr_sibling;
    solve_expr_ins(r_value);
    if (strcmp(l_value->label, "ArrayAccess") == 0) {
    //   switch (l_value->type) {
    //   case INTARRAY:{
        // int *arr = l_value->entry->value.intarr.ptr;
        array_index_insert(l_value->ptr_children_list->ptr_sibling->ptr_children_list);
        // arr[index] = value.integer;
        fprintf(assembly_file,"\tla $8, %s\n",l_value->ptr_children_list->label);
        fprintf(assembly_file,"\taddu $8, $8, $10\n");
        fprintf(assembly_file,"\tlw $9, %zu($fp)\n",sizeof(int));
        fprintf(assembly_file,"\taddiu $fp, $fp, %zu\n",sizeof(int));
        fprintf(assembly_file,"\tsw $9,0($8)\n");
        // break;
    //   }
    //   case BOOLARRAY:{
    //     // bool *barr = l_value->entry->value.boolarr.ptr;
    //     // int bindex = array_index(l_value);
  
    //     // barr[bindex] = value.boolean;
    //   }
    //   default:
    //     break;
    //   }
    } else {
        fprintf(assembly_file,"\tla $8, %s\n",l_value->label);
        fprintf(assembly_file,"\tlw $9, %zu($fp)\n",sizeof(int));
        fprintf(assembly_file,"\taddiu $fp, $fp, %zu\n",sizeof(int));
        fprintf(assembly_file,"\tsw $9, 0($8)\n");
    }
  }
void solve_block(node* root);
void solve_condition(node* tree_node){
    if(tree_node==NULL) return;
    size_t size = sizeof(int); 
    solve_expr_ins(tree_node->ptr_children_list);
    solve_expr_ins(tree_node->ptr_children_list->ptr_sibling);
    load_from_stack(size);
    fprintf(assembly_file,"\taddiu $fp,$fp,%zu\n",(size<<1));
}

int g_loop_id = 0;
void for_statement(node* root){
    int loop_id = g_loop_id;
    g_loop_id++;
    node* assignment = root->ptr_children_list;
    node* condition  = assignment->ptr_sibling;
    node* iterator   = condition->ptr_sibling;
    node* body       = iterator->ptr_sibling;
    // assignment
    solve_assign_ins(assignment->ptr_children_list);

    //loop
    fprintf(assembly_file,"loop%d:\n",loop_id);

    //body
    node* curr = body->ptr_children_list;
    while(curr){
        solve_block(curr);
        curr = curr->ptr_sibling;
    }

    // iterator;
    solve_block(iterator->ptr_children_list);

    //condition
    solve_condition(condition->ptr_children_list);
    fprintf(assembly_file,"\t%s $8, $9, loop%d\n",mipscmd[condition->ptr_children_list->op],loop_id);
    fprintf(assembly_file,"endloop%d:\n",loop_id);
}


int g_if_stmt = 0;
void if_statement(node* root){
    int if_stmt = g_if_stmt++;
    node* condition = root->ptr_children_list;
    node* body      = condition->ptr_sibling;

    //
    solve_condition(condition->ptr_children_list);
    fprintf(assembly_file,"\t%s $8, $9, then%d\n",mipscmd[condition->ptr_children_list->op],if_stmt);
    solve_block(root->ptr_sibling);
    fprintf(assembly_file,"\tj endif%d\n",if_stmt);
    fprintf(assembly_file,"then%d:\n",if_stmt);
    solve_block(body->ptr_children_list);
    fprintf(assembly_file,"endif%d:\n",if_stmt);
}


void branch_stmt(node* root){
    node* if_clause = root->ptr_children_list;
    if_statement(if_clause);
}

void solve_block(node* root){
    if(root == NULL) return;

    if(strcmp(root->label,"ASSIGN")==0){
        solve_assign_ins(root);
    }else if(strcmp(root->label,"CALL")==0){
        if(strcmp(root->ptr_children_list->label,"read")==0){
            for_read(root);
        }else{
            for_write(root);
        }
    }else if(strcmp(root->label,"break")==0){
        fprintf(assembly_file,"\tj endloop%d\n",(g_loop_id-1));
    }else if(strcmp(root->label,"if")==0){
        if_statement(root);
    }else if(strcmp(root->label,"else")==0){
        solve_block(root->ptr_children_list->ptr_children_list);
    }else if(strcmp(root->label,"branch")==0){
        branch_stmt(root);
    }else if(strcmp(root->label,"for")==0){
        for_statement(root);
    }
}