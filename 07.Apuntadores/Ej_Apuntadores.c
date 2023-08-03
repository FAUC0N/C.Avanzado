#include <stdio.h>
#include <malloc.h>

#define PARAM_POINTER

struct Data{
    int m, n;
    struct Data* next;
};

struct Data* head;
struct Data* new;

#ifdef PARAM_POINTER
void add(struct Data** node, int val){
    if( (*node) == NULL ){
        (*node) = (struct Data*)malloc(sizeof(struct Data));
        (*node)->next = NULL;
        (*node)->m = val;
        (*node)->n = (*node)->m * 2;
    } else{
        (*node)->next = (struct Data*)malloc(sizeof(struct Data));
        (*node)->next->next =NULL;
        (*node)->next->m = val;
        (*node)->next->n = (*node)->next->m * 2;
    }
}

#else
void add(struct Data* node, int val){
    if(node == NULL){
        node = (struct Data*)malloc(sizeof(struct Data));
        node->next = NULL;
        node->m = val;
        (*node).n = node->m * 2;
    } else {
        node->next = (struct Data*)malloc(sizeof(struct Data));
        node->next->next = NULL;
        node->next->m = val;
        (*node).n = node->next->m * 2;
    }
}
#endif

int main(void){
    int a;
    int b;
    a = 5;
    b = 7;
    new = (struct Data*)calloc(1, sizeof(struct Data));
    head = new;
    new = NULL;
    add(&new, a);
    free(new);
}