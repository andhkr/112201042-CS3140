#include "include/symbol_table.h"

#include "include/ast.h"

symbol_table *symbltbl = NULL;

bool is_prime(long n) {
  /*skipping the multiple of 2 and 3*/
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0)
      return false;
  }

  return true;
}

int size_of_table(int expected_keys_count) {
  int N = 2 * expected_keys_count + 1;

  /*definitly thge table size will be more than 8 so i will not
   not check base case
  */

  while (is_prime(N)) {
    N += 2;
  }

  return N;
}

int hashvalue_of_key(char *key) {
  /* prime base and */
  long long prime_base = 17000069;
  long long M = 1e9 + 7;

  int hash = 0;
  for (char *c = key; *c != '\0'; ++c) {
    hash = ((hash * prime_base) % M + *c) % M;
  }
  return hash;
}

void *safe_alloc(size_t nmemb, size_t size) {
  void *ptr = calloc(nmemb, size);
  if (ptr == NULL) {
    perror("Memory Allocation Failed\n");
    exit(EXIT_FAILURE);
  }
  return ptr;
}

symbltblentry *create_node(char *name, datatype type, datavalue value) {
  symbltblentry *node = safe_alloc(1, sizeof(symbltblentry));
  node->name = name;
  node->type = type;
  node->value = value;
  node->next = NULL;
  return node;
}

void init_entry(symbltblentry *entry, char *name, datatype type,
                datavalue value) {
  entry->name = name;
  entry->type = type;
  entry->value = value;
  entry->next = NULL;
  
}

symbol_table *create_symbtbl(int size, int (*hashvalue_of_key)(char *),
                             int id) {
  symbol_table *symbtbl = safe_alloc(1, sizeof(symbol_table));
  int capacity = size_of_table(size);
  symbltblentry *table = safe_alloc(capacity, sizeof(symbltblentry));
  symbtbl->capacity = capacity;
  symbtbl->hashvalue_of_key = hashvalue_of_key;
  symbtbl->table = table;
  symbtbl->id = id;
  symbtbl->scope_level_truth = false;
  symbtbl->used = (bool*) malloc(sizeof(bool)*capacity);
  for(int i = 0;i<capacity;++i){
    symbtbl->used[i] = false;
  }
  return symbtbl;
}

symbltblentry *add_entry(symbol_table *symbtbl, char *name, datatype type,
                         datavalue value) {
  int hashvalue = symbtbl->hashvalue_of_key(name) % symbtbl->capacity;
  // for table the max lenght of variable to be printed
  clen_for_var = (clen_for_var < (int)strlen(name) ? ((int)strlen(name)) : clen_for_var);
  symbltblentry *entry = NULL;
  if (!symbtbl->used[hashvalue]) {
    init_entry(&symbtbl->table[hashvalue], name, type, value);
    entry = &symbtbl->table[hashvalue];
    symbtbl->used[hashvalue] = true;
  } else {
    symbltblentry *curr = &symbtbl->table[hashvalue];
    symbltblentry *new_entry = create_node(name, type, value);
    symbltblentry *prev = NULL;
    while (curr) {
      if (strcmp(curr->name, new_entry->name) != 0) {
        prev = curr;
        curr = curr->next;
      } else if (curr->type != type) {
        fprintf(stderr, "error:line no:%d : confilicting types for '%s';have '%s'\n",Lineno,
                curr->name, typename[type]);
        fprintf(stderr, "\t\t  note:previous defination of '%s' with type '%s'\n",
                curr->name, typename[curr->type]);
        exit(EXIT_FAILURE);
      } else {
        fprintf(stderr, "Error:line no : %d : Redeclaration of Variable %s\n", Lineno,name);
        exit(EXIT_FAILURE);
      }
    }
    prev->next = new_entry;
    entry = new_entry;
  }
  return entry;
}

symbltblentry *find_entry(symbol_table *symbtbl, char *name) {
  int hashvalue = symbtbl->hashvalue_of_key(name) % symbtbl->capacity;
  if (!(symbtbl->used[hashvalue])) {
    return NULL;
  } else {
    symbltblentry *curr = &symbtbl->table[hashvalue];
    while (curr) {
      if (strcmp(curr->name, name) != 0) {
        curr = curr->next;
      } else {
        break;
      }
    }
    return curr;
  }
}

void add_array_to_symbtbl(
    struct node *var, /* already array name is created as node with type*/
    int n_ele         /* number of elements in array*/
) {
  switch (var->type) {
  case INT:{
    int *arr = (int *)calloc(n_ele, sizeof(int));
    var->entry->type = INTARRAY;
    intarray array;
    array.capacity = n_ele;
    array.ptr = arr;
    update_data(&var->entry->value.intarr, &array, sizeof(intarray));
    var->type = INTARRAY;
    break;
  }
  case BOOL:{
    bool *barr = (bool *)calloc(n_ele, sizeof(bool));
    var->entry->type = BOOLARRAY;
    boolarray barray;
    barray.capacity = n_ele;
    barray.ptr = barr;
    update_data(&var->entry->value.boolarr, &barray, sizeof(boolarray));
    var->type = BOOLARRAY;
    break;
  }
  default:
    break;
  }
}
