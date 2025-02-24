#include "include/semantic.h"

bool type_checking(node *left, node *right) {
  if(left->type == right->type && left->type != STRING) return true;
  if (!(left->type != STRING || right->type != STRING)) {
    fprintf(stderr, "error:type mismatch\n");
    exit(EXIT_FAILURE);
  }
  return true;
}

bool neg_type_check(node *right) {
  if (!(right->type != STRING)) {
    fprintf(stderr, "error:type mismatch\n");
    exit(EXIT_FAILURE);
  }
  return true;
}

int array_index(node* treenode){
  int index = 0;
  node* right = treenode->ptr_children_list->ptr_sibling;
  if(right->entry){
      index = right->entry->value.integer;
  }else index = right->exp_value.integer;
  return index;
}

void change_to_var(node* treenode){
  if(treenode){
    switch(treenode->type){
      case INTARRAY:
        int* arr = treenode->entry->value.intarr.ptr;
        int index = array_index(treenode);
        update_data(&treenode->exp_value,arr+index,sizeof(int));
        treenode->type = INT;
        break;
      default:
        /*nothing*/
    }
  }
}

void is_Array(node* left,node* right){
  change_to_var(left);
  change_to_var(right);
}

void Add(node *new_node, node *left, node *right) {
  is_Array(left,right);
  if (left->type == DOUBLE || right->type == DOUBLE) {
    add[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (left->type == FLOAT || right->type == FLOAT) {
    add[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (left->type == INT || right->type == INT) {
    add[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (left->type == CHAR && right->type == CHAR) {
    add[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:addition is not applicable for these %s %s datatypes\n",
            typename[left->type], typename[right->type]);
  }
}

void Sub(node *new_node, node *left, node *right) {
  is_Array(left,right);
  if (left->type == DOUBLE || right->type == DOUBLE) {
    sub[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (left->type == FLOAT || right->type == FLOAT) {
    sub[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (left->type == INT || right->type == INT) {
    sub[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (left->type == CHAR && right->type == CHAR) {
    sub[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:subtraction is not applicable for these %s %s datatypes\n",
            typename[left->type], typename[right->type]);
  }
}

void Mul(node *new_node, node *left, node *right) {
  is_Array(left,right);
  if (left->type == DOUBLE || right->type == DOUBLE) {
    mul[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (left->type == FLOAT || right->type == FLOAT) {
    mul[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (left->type == INT || right->type == INT) {
    mul[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (left->type == CHAR && right->type == CHAR) {
    mul[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(
        stderr,
        "Error:multiplication is not applicable for these %s %s datatypes\n",
        typename[left->type], typename[right->type]);
  }
}

void Div(node *new_node, node *left, node *right) {
  is_Array(left,right);
  if (is_zero(&right->exp_value)) {
    fprintf(stderr, "error:divison by zero\n");
    exit(EXIT_FAILURE);
  }
  if (left->type == DOUBLE || right->type == DOUBLE) {
    divide[DOUBLE](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = DOUBLE;
  } else if (left->type == FLOAT || right->type == FLOAT) {
    divide[FLOAT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = FLOAT;
  } else if (left->type == INT || right->type == INT) {
    divide[INT](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = INT;
  } else if (left->type == CHAR && right->type == CHAR) {
    divide[CHAR](&left->exp_value, &right->exp_value, &new_node->exp_value);
    new_node->type = CHAR;
  } else {
    fprintf(stderr,
            "Error:division is not applicable for these %s %s datatypes\n",
            typename[left->type], typename[right->type]);
  }
}
