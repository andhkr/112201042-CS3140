#include "include/semantic.h"

void* safe_malloc(size_t size){
    void* ptr = malloc(size);
    if(ptr == NULL){
        perror("Memory allocation Failed for astNode\n");
        exit(EXIT_FAILURE);
    }
    return ptr;
}

void init_node(node* new_node,symbltblentry* entry,node* left,node* right,char* statement){
    new_node->entry     = entry;
    new_node->left      = left;
    new_node->right     = right;
    new_node->statement = statement;
}

node* create_node_ast(char op,symbltblentry* entry,node* left,node* right){
    node* new_node = (node*)safe_malloc(sizeof(node));
    switch (op){
        case '+':
            type_checking(left,right);
            Add(new_node,left,right);
            init_node(new_node,entry,left,right,"PLUS");
            break;
        case '-':
            type_checking(left,right);
            Sub(new_node,left,right);
            init_node(new_node,entry,left,right,"SUB");
            break;
        case '*':
            type_checking(left,right);
            Mul(new_node,left,right);
            init_node(new_node,entry,left,right,"MUL");
            break;
        case '/':
            type_checking(left,right);
            Div(new_node,left,right);
            init_node(new_node,entry,left,right,"DIV");
            break;
        case 'n':
            neg_type_check(right);
            neg[right->type](&new_node->exp_value,&right->exp_value);
            init_node(new_node,entry,left,right,"UMINUS");
            break;
        case 'c':
            init_node(new_node,entry,left,right,"CALL");
            break;
        case 'v':
            init_node(new_node,entry,left,right,entry->name);
            update_data(&new_node->exp_value,&entry->value,datasize[entry->type]);
            new_node->type = entry->type;
            break;
        case '=':
            type_checking(left,right);
            // printf("RAdha2\n");
            init_node(new_node,entry,left,right,"ASSIGN");
            // update_data(&new_node->exp_value,&right->exp_value,datasize[right->type]);
            // printf("RAdha3\n");
            if(left->type != INTARRAY)
            update_data(&left->entry->value,&right->exp_value,datasize[left->entry->type]);
            // printf("RAdha4\n");
            break;
        case 'd':
            init_node(new_node,entry,left,right," ");
            break;
        default:
            fprintf(stderr,"Error: Some new operation:%c\n",op);
            exit(EXIT_FAILURE);

    }
    return new_node;
}
/* these are routines developed by me for ast print*/
/*
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
    printf("--------------------------------------------------------------------------------------\n");
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
*/


void print_decl(node* root){
    printf("                %s\n",root->statement);
    printf("    %s                ",root->left->statement);
    root = root->right;
    while(root){
        printf("%s  ",root->statement);
        root = root->right;
        if(root && root->entry == NULL){
            printf("\n");
            printf("--------------------------------------------------------------------------------------\n");
            printf("                DECL\n");
            printf("    %s                ",root->statement);
            root = root->right;
        }
    }
    printf("\n");
}

int depth(node* root){
    if(root == NULL) return 0;
    int d1 = depth(root->left);
    int d2 = depth(root->right);
    return (d1>d2 ? d1+1:d2+1);
}

/* inpired by Graph Source Code of LexAndYaccTutorial book */
int clmax = 0;
int rmax =  0;
int node_length;

char** canvas;

void init_graph(node* root){
    int d   = depth(root);
    rmax    = 5*d;
    node_length = ((clen_for_var<20?20:clen_for_var));
    clmax   = node_length*d;
    canvas = (char**) malloc(rmax*sizeof(char*));
    char*  data = (char*)  malloc(rmax*clmax*sizeof(char));

    if(!canvas || !data) {
        fprintf(stderr,"Memory Allocation for AST graph is failed\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0;i<rmax;++i){
        canvas[i] = data + (i*clmax);
    }
    for(int i = 0;i<rmax;++i){
        for(int j = 0;j<clmax;++j){
            canvas[i][j] = ' ';
        }
    }
}


/* source code courtesy of Frank Thomas Braun */
int hmar = 2; /* distance of graph columns*/
int vmar = 3; /* distance of graph lines */
/* hmar = 2 is i find best */

/***********************************************************/
/* main entry point of the manipulation of the syntax tree */ 
int graph (node *root) {
    int rte=0, rtm=0;
    init_graph(root);
    print_tree (root, 0, 0, &rte, &rtm);
    graphFinish();
    return 0;
}

void print_tree(  
        node *root,
        int c, int l,        /* start column and line of node */
        int *ce, int *cm          /* resulting end column and mid of node */
) 
{
    int w, h;       /* node width and height */
    char *s;        /* node text */
    int cbar;       /* "real" start column of node (centred above subnodes)*/
    int che, chm;   /* end column and mid of children */
    int cs;         /* start column of children */
    if (!root) return;
    s = root->statement;
    /* construct node text box */
    graphBox (s, &w, &h);
    cbar = c;
    *ce = c + w;
    *cm = c + w / 2;

    /* node is leaf */
    if (root->left == NULL && root->right == NULL) {
        graphDrawBox (s, cbar, l);
        return; 
    }

    /* node has children */
    cs = c;
    /*left children*/
    print_tree (root->left, cs, l+h+vmar, &che, &chm);
    cs = che;
    /*right children*/
    print_tree (root->right, cs, l+h+vmar, &che, &chm);
    cs = che;

    /* total node width */
    if (w < che - c) {
        cbar += (che + (hmar-1) - c - w) / 2;
        *ce = che;
        *cm = (c + che) / 2;
    }    
    
    /* draw node */
    graphDrawBox (s, cbar, l);

    /* draw arrows (not optimal: children are drawn a second time) */ 
     cs = c;
    /*left children*/
    print_tree (root->left, cs, l+h+vmar, &che, &chm);
    graphDrawArrow (*cm, l+h, chm, l+h+vmar-1);
    cs = che;
    /*right children*/
    print_tree (root->right, cs, l+h+vmar, &che, &chm);
    graphDrawArrow (*cm, l+h, chm, l+h+vmar-1);
    cs = che;
}


// int graphNumber = 0;

void graphTest (int l, int c)
{   
    int ok;
    ok = 1;
    if (l < 0) ok = 0;
    if (l >= rmax) ok = 0;
    if (c < 0) ok = 0;
    if (c >= clmax) ok = 0;
    if (ok) return;
    fprintf(stderr, 
        "\n+++error: l=%d, c=%d not in drawing rectangle 0, 0 ... %d, %d"
        " you need to modify int init_graph function", 
        l, c, rmax, clmax
    ); 
    exit (EXIT_FAILURE); 
}

void graphFinish() {
    int i, j;
    for (i = 0; i < rmax; i++) {
        for (j = clmax-1; j > 0 && canvas[i][j] == ' '; j--);
        canvas[i][clmax-1] = 0;
        if (j < clmax-1) canvas[i][j+1] = 0;
        if (canvas[i][j] == ' ') canvas[i][j] = 0;
    }
    for (i = rmax-1; i > 0 && canvas[i][0] == 0; i--); 
    // printf ("\n\nGraph %d:\n", graphNumber++);
    for (j = 0; j <= i; j++) printf ("\n%s", canvas[j]); 
    printf("\n");
}

void graphBox (char *s, int *w, int *h) {
    *w = strlen (s) + hmar;
    *h = 1;
}

void graphDrawBox (char *s, int c, int l) {
    int i;
    graphTest (l, c+strlen(s)-1+hmar);
    for (i = 0; i < strlen (s); i++) {
        canvas[l][c+i+hmar] = s[i];
    }
}

void graphDrawArrow (int c1, int l1, int c2, int l2) {
    int m;
    c1 = c1+hmar-1;
    c2 = c2+hmar-1;
    graphTest (l1, c1);
    graphTest (l2, c2);
    m = (l1 + l2) / 2;
    while (l1 != m) {
        canvas[l1][c1] = '|'; if (l1 < l2) l1++; else l1--;
    }
    while (c1 != c2) {
        canvas[l1][c1] = '-'; if (c1 < c2) c1++; else c1--;
    }
    while (l1 != l2) {
        canvas[l1][c1] =    '|'; if (l1 < l2) l1++; else l1--;
    }
    canvas[l1][c1] = 'v';
}

void free_graph(){
    free(canvas[0]);
    free(canvas);
}
