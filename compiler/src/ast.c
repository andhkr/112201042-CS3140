#include "include/ast.h"

void* safe_malloc(size_t size){
    void* ptr = malloc(size);
    if(ptr == NULL){
        perror("Memory allocation Failed for astNode\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

node* create_node_ast(datatype type,nodevalue value,int exp_value){
    node* new_node = (node*)safe_malloc(sizeof(node));
    new_node->type = type;
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->exp_value = exp_value;
    return new_node;
}

void print_ast(node* root){
    if(root == NULL) return ;
    switch (root->type) {
        case INT:
            printf("%d ",root->exp_value);
            break;
        case OP:
            printf("%c ",root->value.op);
            break;
        case ENTRY:
            printf("%s ",root->value.entry->name);
            break;
        case STATEMENT:
            printf("%s ",root->value.statement);
            break;
        default:
            printf("Some Thing Problematic\n");
    }
    print_ast(root->left);
    print_ast(root->right);
}

