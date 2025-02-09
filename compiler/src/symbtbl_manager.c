#include "include/symbtbl_manager.h"

symbtbl_manager manager;

void init_symbtbl_manager(symbtbl_manager* manager){
    manager->capacity = 2;
    manager->size     = 0;
    manager->array    = (symbol_table**) safe_alloc(2,sizeof(symbol_table*));
    manager->current_table = 0;
}

void allocation(symbtbl_manager* manager){
    size_t old_size = manager->capacity;
    manager->capacity = (manager->capacity)<<1;
    symbol_table** ptr = (symbol_table**) realloc(manager->array,manager->capacity);
    if(ptr == NULL){
        fprintf(stderr,"Memory reallocation for symbol table manager Failed\n");
        exit(EXIT_FAILURE);
    }
    memset((char*)ptr+old_size,0,manager->capacity-old_size);
    manager->array = ptr;
}

void push_back(symbtbl_manager* manager,symbol_table* symbtbl){
    if(manager->capacity == manager->size){
        allocation(manager);
    }
    manager->array[(manager->size)++] = symbtbl;
}

symbol_table* pop_back(symbtbl_manager* manager){
    if(manager->size == 0){
        fprintf(stderr,"Error:No symbol table\n");
        exit(EXIT_FAILURE);
    }
    return manager->array[--(manager->size)];
}

void print_symbol_table(){
    symbol_table* curr = manager.array[0];
	printf("Symbol Table:\n");
    for(int i = 0;i<curr->capacity;++i){
        if(curr->table[i].name != NULL){
            printf("%s := %d\n",curr->table[i].name,curr->table[i].value.integer);
        }
    }
}
