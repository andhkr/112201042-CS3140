#include "include/symbol_table.h"

symbol_table* symbtbl = NULL;

bool is_prime(long n){
    /*skipping the multiple of 2 and 3*/
    if(n %2 == 0 || n%3 == 0) return false;

    for(int i = 5 ;i*i<=n;i+=6){
        if(n%i == 0 || n%(i+2) == 0) return false;
    }

    return true;
}

int size_of_table(int expected_keys_count){
    int N = 2*expected_keys_count + 1;
    
    /*definitly thge table size will be more than 8 so i will not
     not check base case
    */

   while(is_prime(N)){
        N += 2;
   }

   return N;
}

int hashvalue_of_key(char* key){
    /* prime base and */
    long long  prime_base = 17000069;
    long long  M          = 1e9 + 7;

    int hash = 0;
    for(char* c = key;*c != '\0';++c){
        hash = ((hash*prime_base)%M + *c)%M;
    }
    return hash;
}

void* safe_alloc(size_t nmemb,size_t size){
    void* ptr = calloc(nmemb,size);
    if(ptr == NULL){
        perror("Memory Allocation Failed\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

symbltblentry* create_node(char* name,datatype type,datavalue value){
    symbltblentry* node = safe_alloc(1,sizeof(symbltblentry));
    node->name          = name;
    node->type          = type;
    node->value         = value;
    node->next          = NULL;
    return node;
}

void init_entry(symbltblentry* entry,char* name,datatype type,datavalue value){
    entry->name = name;
    entry->type = type;
    entry->value = value;
    entry->next = NULL;
}

bool is_entryequal(symbltblentry* entry1,symbltblentry* entry2){
    return strcmp(entry1->name,entry2->name)==0 && (entry1->type == entry2->type);
}

symbol_table* create_symbtbl(int size,int (*hashvalue_of_key) (char*),int id){
    symbol_table* symbtbl = safe_alloc(1,sizeof(symbol_table));
    int capacity = size_of_table(size);
    symbltblentry* table = safe_alloc(capacity,sizeof(symbltblentry));
    symbtbl->capacity = capacity;
    symbtbl->hashvalue_of_key = hashvalue_of_key;
    symbtbl->table = table;
    symbtbl->id = id;
    return symbtbl;
}

symbltblentry* add_entry(symbol_table* symbtbl,char* name,datatype type,datavalue value){
    int hashvalue = symbtbl->hashvalue_of_key(name)%symbtbl->capacity;
    // for table the max lenght of variable to be printed
    clen_for_var = (clen_for_var<strlen(name)?(strlen(name)):clen_for_var);

    if(symbtbl->table[hashvalue].name==NULL){
        init_entry(&symbtbl->table[hashvalue],name,type,value);
        return &symbtbl->table[hashvalue];
    }else{
        symbltblentry* curr = &symbtbl->table[hashvalue];
        symbltblentry* new_entry = create_node(name,type,value);
        symbltblentry* prev = NULL;
        while(curr){
            if(!is_entryequal(curr,new_entry)){
                prev = curr;
                curr = curr->next;
            }
            else if (curr->type == type){
                fprintf(stderr,"Error: confilicting types for %s",curr->name);
                exit(EXIT_FAILURE);
            }
            else{
                fprintf(stderr,"Error:Redeclaration of Variable %s\n",name);
                exit(EXIT_FAILURE);
            }
        }
        prev->next = new_entry;
        return new_entry;
    }
    return NULL;
}

symbltblentry* get_entry(symbol_table* symbtbl,char* name){
    int hashvalue = symbtbl->hashvalue_of_key(name)%symbtbl->capacity;
    if((symbtbl->table[hashvalue].name)==NULL){
        fprintf(stderr,"Error: Variable %s not declared\n",name);
        exit(EXIT_FAILURE);
    }else{
        symbltblentry* curr = &symbtbl->table[hashvalue];
        while(curr){
            if(strcmp(curr->name,name) != 0){
                curr = curr->next;
            }else{
                break;
            }
        }
        if(curr){
            return curr;
        }else{
            fprintf(stderr,"Error: Variable %s not declared\n",name);
            exit(EXIT_FAILURE);
        }
    }
}

