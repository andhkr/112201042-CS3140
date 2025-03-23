#include "include/interpreter.h"

datavalue array_access(node *tree_node) {
  datavalue d;
  memset(&d,0,sizeof(datatype));
  switch (tree_node->type) {
  case INTARRAY:
    int *arr = tree_node->entry->value.intarr.ptr;
    d.integer = arr[array_index(tree_node)];
    break;
  case BOOLARRAY:
    bool *barr = tree_node->entry->value.boolarr.ptr;
    d.boolean = barr[array_index(tree_node)];
    break;
  default:
    break;
  }
  return d;
}

datavalue solve_expr(node *tree_node) {
  datavalue result;
  datavalue left;
  datavalue right;
  memset(&result,0,sizeof(datavalue));
  if(tree_node == NULL) return result;
  switch (tree_node->op) {
  case PLUS:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    add[tree_node->type](&left, &right, &result);
    break;
  case SUB:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    sub[tree_node->type](&left, &right, &result);
    break;
  case MUL:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    mul[tree_node->type](&left, &right, &result);
    break;
  case DIV:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    divide[tree_node->type](&left, &right, &result);
    break;
  case LESSTHAN:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    lessthanops[tree_node->type](&left, &right, &result);
    break;
  case U_MINUS:
    return tree_node->exp_value;
  case EQUAL_EQUAL:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    isequalops[tree_node->type](&left, &right, &result);
    break;
  case GREATERTHAN:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    greaterthanops[tree_node->type](&left, &right, &result);
    break;
  case GREATT_EQUAL:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    greatteqops[tree_node->type](&left, &right, &result);
    break;
  case LESST_EQUAL:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    greatteqops[tree_node->type](&left, &right, &result);
    break;
  case MODULO:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    int ans = (left.integer)%(right.integer);
    update_data(&result,&ans,sizeof(int));
    break;
  case Logical_AND:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    bool aans = (left.integer)&&(right.integer);
    update_data(&result,&aans,sizeof(bool));
    break;
  case Logical_OR:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    bool oans = (left.integer)||(right.integer);
    update_data(&result,&oans,sizeof(bool));
    break;
  case Logical_NOT:
    left = solve_expr(tree_node->ptr_children_list);
    right = solve_expr(tree_node->ptr_children_list->ptr_sibling);
    bool nans = !(left.integer);
    update_data(&result,&nans,sizeof(bool));
    break;
  default:
    if (strcmp(tree_node->label, "ArrayAccess") == 0) {
      result = array_access(tree_node);
    } else if (tree_node->entry) {     
      result = tree_node->entry->value;
    } else
      result = tree_node->exp_value;
  }
  tree_node->exp_value = result;
  return result;
}

void solve_assign(node *tree_node) {
  node *l_value = tree_node->ptr_children_list;
  node *r_value = l_value->ptr_sibling;
  datavalue value = solve_expr(r_value);
  if (strcmp(l_value->label, "ArrayAccess") == 0) {
    switch (l_value->type) {
    case INTARRAY:
      int *arr = l_value->entry->value.intarr.ptr;
      int index = array_index(l_value);
      arr[index] = value.integer;
      break;
    case BOOLARRAY:
      bool *barr = l_value->entry->value.boolarr.ptr;
      int bindex = array_index(l_value);

      barr[bindex] = value.boolean;
    default:
      break;
    }
  } else {
    l_value->entry->value = value;
  }
  l_value->exp_value = value;
}

int interprete(node *tree_node) {
  if (tree_node == NULL)
    return 0;

  if (strcmp(tree_node->label, "for") == 0) {
    node *assignment = tree_node->ptr_children_list;
    node *condition = assignment->ptr_sibling;
    node *iterator = condition->ptr_sibling;
    node *body = iterator->ptr_sibling;
    if (assignment->ptr_children_list) {
      solve_assign(assignment->ptr_children_list);
    }
    symbltbl = create_symbtbl(64, hashvalue_of_key, 0);
    push_back(&manager, symbltbl);
    while ((solve_expr(condition->ptr_children_list).boolean)) {
      node *for_body = body->ptr_children_list;
      
      while (for_body) {
        int ret_val = interprete(for_body);
        if(ret_val == 1){
          goto out;
        }
        else if (ret_val == -1) break;
        for_body = for_body->ptr_sibling;
      }
      if (iterator->ptr_children_list) {
        solve_assign(iterator->ptr_children_list);
      } 
    }
    out:
    pop_back(&manager);
  } else if (strcmp(tree_node->label, "if") == 0) {
    node *if_condition = tree_node->ptr_children_list;
    node *if_body = if_condition->ptr_sibling;
    tree_node->exp_value.boolean = false;
    if (solve_expr(if_condition->ptr_children_list).boolean) {

      symbltbl = create_symbtbl(64, hashvalue_of_key, 0);
      push_back(&manager, symbltbl);
      node *stmts_in_if_body = if_body->ptr_children_list;
      while (stmts_in_if_body) {
        int ret_val = interprete(stmts_in_if_body);
        if(ret_val != 0){
          pop_back(&manager);
          tree_node->exp_value.boolean = true;
          return ret_val;
        }
        stmts_in_if_body = stmts_in_if_body->ptr_sibling;
      }
      pop_back(&manager);
      tree_node->exp_value.boolean = true;
    }
  } else if (strcmp(tree_node->label, "branch") == 0) {
    int ret_val = interprete(tree_node->ptr_children_list);
    if(ret_val != 0) return ret_val;
    if (!(tree_node->ptr_children_list->exp_value.boolean)) {
      ret_val = interprete(tree_node->ptr_children_list->ptr_sibling);
      if(ret_val != 0) return ret_val;
    }
  } else if (strcmp(tree_node->label, "else") == 0) {
    push_back(&manager, symbltbl);
    node *else_body = tree_node->ptr_children_list;
    node *stmts_in_else_body = else_body->ptr_children_list;
    while (stmts_in_else_body) {
      int ret_val = interprete(stmts_in_else_body);
      if(ret_val != 0){
        pop_back(&manager);
        return ret_val;
      }
      stmts_in_else_body = stmts_in_else_body->ptr_sibling;
    }
    pop_back(&manager);
  } else if (strcmp(tree_node->label, "ASSIGN") == 0) {
    solve_assign(tree_node);
  } else if (strcmp(tree_node->label, "break") == 0) {
    return 1;
  }else if (strcmp(tree_node->label, "continue") == 0) {
    return -1;
  }
  return 0;
}