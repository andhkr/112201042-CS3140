#include "include/symbtbl_manager.h"

int clen_for_var = 10;
int clen_for_type = 10;
int clen_for_val = 10;
int row = 30;

symbtbl_manager manager;

void init_symbtbl_manager(symbtbl_manager *manager) {
  manager->capacity = 16;
  manager->size = 0;
  manager->array = (symbol_table **)safe_alloc(16, sizeof(symbol_table *));
  manager->current_table = 0;
}

void allocation(symbtbl_manager *manager) {
  int old_size = manager->capacity;
  manager->capacity = ((manager->capacity) << 1);
  symbol_table **ptr =
    (symbol_table **)realloc(manager->array, manager->capacity*sizeof(symbltblentry));
  if (ptr == NULL) {
    fprintf(stderr, "Memory reallocation for symbol table manager Failed\n");
    exit(EXIT_FAILURE);
  }
  memset(ptr+old_size,0,(manager->capacity-old_size));
  manager->array = ptr;
}

void push_back(symbtbl_manager *manager, symbol_table *symbtbl) {
  if (manager->capacity == manager->size) {
    allocation(manager);
  }
  manager->array[(manager->size)++] = symbtbl;
  symbltbl = symbtbl;
}

void pop_back(symbtbl_manager *manager) {
  if (manager->size == 0) {
    fprintf(stderr, "Error:No symbol table\n");
    exit(EXIT_FAILURE);
  }
  --(manager->size);
  free_symbol_table((manager->array[(manager->size)]));
  symbltbl = manager->array[(manager->size - 1)];
}

symbltblentry *get_entry(symbol_table *symbtbl, char *name) {
  symbltblentry *entry = NULL;
  for (int i = manager.size - 1; i >= 0; --i) {
    entry = find_entry(manager.array[i], name);
    if (entry)
      break;
  }
  if (entry == NULL) {
    fprintf(stderr, "error:line no:%d:variable %s not declared\n",Lineno, name);
    exit(EXIT_FAILURE);
  }
  return entry;
}

void print_symbol_table() {
  symbol_table *curr = manager.array[0];

  printf("\nSymbol Table:\n");
  table_format();
  printf("| %-*s | %-*s | %-*s |\n", clen_for_var, "variable", clen_for_type,
         "type", clen_for_val, "value");
  row = clen_for_var + clen_for_type + clen_for_val;
  table_format();

  for (int i = 0; i < curr->capacity; ++i) {
    if (curr->table[i].name != NULL) {
      print_link_list(&curr->table[i]);
    }
  }

  table_format();
}

void print_link_list(symbltblentry *head) {
  while (head) {
    print_entry(head);
    head = head->next;
  }
}

void print_entry(symbltblentry *entry) {
  switch (entry->type) {
  case INT:
    printf("| %-*s | %-*s | %-*d |\n", clen_for_var, entry->name, clen_for_type,
           "int", clen_for_val, entry->value.integer);
    break;
  case CHAR:
    printf("| %-*s | %-*s | %-*c |\n", clen_for_var, entry->name, clen_for_type,
           "char", clen_for_val, entry->value.character);
    break;
  case STRING:
    printf("| %-*s | %-*s | %-*s |\n", clen_for_var, entry->name, clen_for_type,
           "char*", clen_for_val, entry->value.string);
    break;
  case BOOL:
    printf("| %-*s | %-*s | %-*d |\n", clen_for_var, entry->name, clen_for_type,
           "bool", clen_for_val, entry->value.boolean);
    break;
  case INTARRAY:
    printf("| %-*s | %-*s | ", clen_for_var, entry->name, clen_for_type,
           "int array");
    for (int i = 0; i < entry->value.intarr.capacity; ++i) {
      printf("%d , ", entry->value.intarr.ptr[i]);
    }
    printf("|\n");
    break;
  case BOOLARRAY:
    printf("| %-*s | %-*s | ", clen_for_var, entry->name, clen_for_type,
           "bool array");
    for (int i = 0; i < entry->value.boolarr.capacity; ++i) {
      printf("%d , ", entry->value.boolarr.ptr[i]);
    }
    printf("|\n");
    break;
  default:
    break;
  }
}

void table_format() {
  int val1 = clen_for_var + 2;
  int val2 = clen_for_type + 2;
  int val3 = clen_for_val + 2;
  printf("+");
  while (val1--) {
    printf("-");
  }
  printf("+");
  while (val2--) {
    printf("-");
  }
  printf("+");
  while (val3--) {
    printf("-");
  }
  printf("+\n");
}

void free_link_list(symbltblentry *head) {
  symbltblentry *prev = NULL;
  symbltblentry *curr = head;
  while (curr) {
    prev = curr->next;
    free(curr);
    curr = prev;
  }
}

void free_symbol_table(symbol_table *symbtbl) {
  symbol_table *curr = symbtbl;
  for (int i = 0; i < curr->capacity; ++i) {
    if (curr->used[i]) {
      free_link_list(curr->table[i].next);
    }
  }
  free(symbtbl->table);
  symbtbl->table = NULL;
}

void free_symbol_table_manager(symbtbl_manager *manager) {
  for (int i = 0; i < manager->size; ++i) {
    free_symbol_table(manager->array[i]);
    manager->array[i] = NULL;
  }
  free(manager->array);
  manager->array = NULL;
}
