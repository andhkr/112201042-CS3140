#include "include/semantic.h"

bool type_checking(node *left, node *right) {
  if (left->type  == right->type && left->type  != STRING)
    return true;
  if (!(left->type  != STRING || right->type != STRING)) {
    fprintf(stderr, "error:line no:%d : type mismatch\n",Lineno);
    exit(EXIT_FAILURE);
  }
  return true;
}

bool neg_type_check(node *right) {
  if (!(right->type != STRING)) {
    fprintf(stderr, "error:line no:%d : type mismatch\n",Lineno);
    exit(EXIT_FAILURE);
  }
  return true;
}

int array_index(node *treenode) {
  int index = 0;
  node *right = treenode->ptr_children_list->ptr_sibling;
  if (right->entry) {
    index = right->entry->value.integer;
  } else
    index = right->exp_value.integer;
  return index;
}


int give_type(node* tree_node){
  if(tree_node == NULL) return -1;
  int t = 0;
  switch(tree_node->type){
    case INTARRAY:
      int *arr = tree_node->entry->value.intarr.ptr;
      int index = array_index(tree_node);
      update_data(&tree_node->exp_value, arr + index, sizeof(int));
      t = INT;
      break;
    case DOUBLEARRAY:
      double *darr = tree_node->entry->value.dblarr.ptr;
      index = array_index(tree_node);
      update_data(&tree_node->exp_value, darr + index, sizeof(double));
      t = DOUBLE;
      break;
    default:
      t = tree_node->type;
  }
  return t;
}

void is_Array(node *left, node *right) {
  give_type(left);
  give_type(right);
}

void Add(node *new_node, node *left, node *right) {
  int l_type = 0,r_type = 0;
  l_type = give_type(left);
  r_type = give_type(right);
  if (l_type  == DOUBLE || r_type == DOUBLE) {
    add[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (l_type  == FLOAT || r_type == FLOAT) {
    add[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (l_type  == INT || r_type == INT || l_type  == INTARRAY || r_type == INTARRAY) {
    add[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (l_type  == CHAR && r_type == CHAR) {
    add[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error: line no : %d :addition is not applicable for these %s %s datatypes\n",Lineno,
            typename[l_type ], typename[r_type]);
  }
}

void Sub(node *new_node, node *left, node *right) {
  int l_type = 0,r_type = 0;
  l_type = give_type(left);
  r_type = give_type(right);
  if (l_type  == DOUBLE || r_type == DOUBLE) {
    sub[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (l_type  == FLOAT || r_type == FLOAT) {
    sub[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (l_type  == INT || r_type == INT) {
    sub[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (l_type  == CHAR && r_type == CHAR) {
    sub[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:line no %d : subtraction is not applicable for these %s %s datatypes\n",Lineno,
            typename[l_type ], typename[r_type]);
  }
}

void Mul(node *new_node, node *left, node *right) {
  int l_type = 0,r_type = 0;
  l_type = give_type(left);
  r_type = give_type(right);
  if (l_type  == DOUBLE || r_type == DOUBLE) {
    mul[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (l_type  == FLOAT || r_type == FLOAT) {
    mul[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (l_type  == INT || r_type == INT) {
    mul[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (l_type  == CHAR && r_type == CHAR) {
    mul[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(
        stderr,
        "Error:line no %d : multiplication is not applicable for these %s %s datatypes\n",Lineno,
        typename[l_type ], typename[r_type]);
  }
}

void Div(node *new_node, node *left, node *right) {
  int l_type = 0,r_type = 0;
  l_type = give_type(left);
  r_type = give_type(right);
  if (is_zero(&right->exp_value)) {
    fprintf(stderr, "error:line no %d : divison by zero\n",Lineno);
    exit(EXIT_FAILURE);
  }
  if (l_type  == DOUBLE || r_type == DOUBLE) {
    divide[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (l_type  == FLOAT || r_type == FLOAT) {
    divide[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (l_type  == INT || r_type == INT) {
    divide[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (l_type  == CHAR && r_type == CHAR) {
    divide[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:line no %d : division is not applicable for these %s %s datatypes\n",Lineno,
            typename[l_type], typename[r_type]);
  }
}

void Modulo(node *new_node, node *left, node *right) {
  int l_type = 0,r_type = 0;
  l_type = give_type(left);
  r_type = give_type(right);
  if (is_zero(&right->exp_value)) {
    fprintf(stderr, "error:line no %d : divison by zero\n",Lineno);
    exit(EXIT_FAILURE);
  }
  if (l_type  == INT && r_type == INT) {
    int result = ((left->exp_value.integer) % (right->exp_value.integer));
    update_data(&new_node->exp_value,&result,sizeof(int));
    new_node->type = INT;
  } else if (l_type  == CHAR && r_type == CHAR) {
    char result = ((left->exp_value.character) % (right->exp_value.character));
    update_data(&new_node->exp_value,&result,sizeof(char));
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:line no %d : modulo is not applicable for these %s %s datatypes\n", Lineno,
            typename[l_type], typename[r_type]);
  }
}
