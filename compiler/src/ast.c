#include "include/ast.h"
#include "math.h"

void* safe_malloc(size_t size){
    void* ptr = malloc(size);
    if(ptr == NULL){
        perror("Memory allocation Failed for astNode\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

node* create_node_ast(char* statement,int exp_value,symbltblentry* entry){
    node* new_node = (node*)safe_malloc(sizeof(node));
    new_node->statement = statement;
    new_node->entry = entry;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->exp_value = exp_value;
    return new_node;
}

void print_ast(node* root){
    if(root == NULL) return ;
    printf("%s ",root->statement);
    print_ast(root->left);
    print_ast(root->right);
}

typedef struct queue{
    node* array[4096];
    int tail;
    int head;
    int size;
}queue;

void init_q(queue* q){
    q->size = 0;
    q->head = 0;
    q->tail = 0;
}

void pushend(queue* q,node* n){
    q->array[q->tail] = n;
    q->tail = (q->tail + 1)%4096;
    q->size += 1;
}

node* popfront(queue*q){
    node* n = q->array[q->head];
    q->head  = (q->head + 1)%4096;
    q->size -= 1;
    return n;
}

void padding(int level){
    if(level>0){
        while(level--){
            printf(" ");
        }
    }
}
void print_name(char* name);
void printtree(node* root){
    queue q;
    init_q(&q);
    pushend(&q,root);
    int level = depth(root);
    while(level--){
        int n = q.size;
        int pads = 0;
        if((level-1)>0){
            pads = 3 + (6*((pow(2,level-1))-1));}
        else if (level-1 == 0){pads = 3;}
        else {pads = 0;}

        // printf("%d\n",pads);
        padding(pads);
        for(int i = 0;i<n;++i){
            node* trnode =  popfront(&q);
            if(trnode == NULL){
                pushend(&q,NULL);
                pushend(&q,NULL);
                print_name("");
                if(level)
                padding(pow(3,(level-1))*6);
                continue;
            }
            pushend(&q,trnode->left);
            pushend(&q,trnode->right);
            if(level){
                print_name(trnode->statement);
                padding(pow(3,(level-1))*6);
            }else{
                print_name(trnode->statement);
            }

        }
        printf("\n");
    }
}

void print_name(char* name){
    int i = strlen(name);
    if(i != 0)
    printf("%s",name);
    while(i < 6){
        printf(" ");
        ++i;
    }
}

void print_decl(node* root){
    printf("                %s\n",root->statement);
    printf("    %s                ",root->left->statement);
    root = root->right;
    while(root){
        printf("%s  ",root->statement);
        root = root->right;
    }
    printf("\n");
}
int depth(node* root){
    if(root == NULL) return 0;
    int d1 = depth(root->left);
    int d2 = depth(root->right);
    return (d1>d2 ? d1+1:d2+1);
}
