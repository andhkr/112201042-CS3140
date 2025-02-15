#include "include/symbtbl_manager.h"

int clen_for_var=10;
int clen_for_type = 10;
int clen_for_val = 10;
int row = 30;

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
    
	printf("\nSymbol Table:\n");
    table_format();
    printf("| %-*s | %-*s | %-*s |\n",
            clen_for_var,"variable",
            clen_for_type,"type",
            clen_for_val,"value");
    row = clen_for_var + clen_for_type + clen_for_val;
    table_format();

    for(int i = 0;i<curr->capacity;++i){
        if(curr->table[i].name != NULL){
            print_link_list(&curr->table[i]);
        }
    }

    table_format();
}

void print_link_list(symbltblentry* head){
    while(head){
        print_entry(head);
        head = head->next;
    }
}

void print_entry(symbltblentry* entry){
    switch(entry->type){
        case INT :
            printf  ("| %-*s | %-*s | %-*d |\n",clen_for_var,entry->name,
                    clen_for_type,"int",
                    clen_for_val,entry->value.integer
                    );
            break;
        case CHAR:
            printf  ("| %-*s | %-*s | %-*c |\n",clen_for_var,entry->name,
                    clen_for_type,"char",
                    clen_for_val,entry->value.character
                    );
            break;
        case STRING:
            printf  ("| %-*s | %-*s | %-*s |\n",clen_for_var,entry->name,
                    clen_for_type,"char*",
                    clen_for_val,entry->value.string
                    );
            break;
        case BOOL:
            printf  ("| %-*s | %-*s | %-*d |\n",clen_for_var,entry->name,
                    clen_for_type,"bool",
                    clen_for_val,entry->value.boolean
                    );
            break;
        default:
            break;
    }
}


void table_format(){
    int val1 = clen_for_var+2;
    int val2 = clen_for_type+2;
    int val3 = clen_for_val+2;
    printf("+");
    while(val1--){
        printf("-");
    }
    printf("+");
    while(val2--){
        printf("-");
    }
    printf("+");
    while(val3--){
        printf("-");
    }
    printf("+\n");
}


void free_symbol_table(symbol_table* symbtbl){
    symbol_table* curr = manager.array[0];
    for(int i = 0;i<curr->capacity;++i){
        if(curr->table[i].name != NULL){
            free_link_list(curr->table[i].next);
        }
    }
    free(symbtbl->table);
    symbtbl->table = NULL;
}

void free_link_list(symbltblentry* head){
    symbltblentry* prev = NULL;
    symbltblentry* curr = head;
    while(curr){
        prev = curr->next;
        free(curr);
        curr = prev;
    }
}