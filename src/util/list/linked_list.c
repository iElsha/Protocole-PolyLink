//
// Created by maxence on 04/02/2020.
//

#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"


struct list* list_create(){
    return (struct list*) malloc(sizeof(struct list));
}
struct node* node_create(void* x){
    struct node* n = (struct node*)malloc(sizeof(struct node));
    n->element = x;
    return n;
}

void list_destroy(struct list* L){
    if (!list_is_empty(L)){
        node_destroy(L->first);
    }
    free(L);
}

void node_destroy(struct node* n){
    if (n->next != NULL){
        node_destroy(n->next);
    }
    free(n);
}

int list_is_empty(struct list* L){
    return L->first == NULL;
}

int list_lenght(struct list* L){
    if (list_is_empty(L)){
        return 0;
    }
    return node_lenght(L->first);
}
int node_lenght(struct node* n){
    if (n->next == NULL){
        return 1;
    } else {
        return node_lenght(n->next)+1;
    }
}

int list_find(void* x, struct list* L){
    if (list_is_empty(L)){
        return -1;
    }
    return node_find(x, L->first);
}

int node_find(void *x, struct node* n){
    if (n->element == x){
        return 0;
    } else if (n->next == NULL){
        return -1;
    } else{
        int nb = node_find(x,n->next);
        if (nb == -1){
            return -1;
        }
        return nb+1;
    }
}
void list_insert(void * x, struct list* L, int p){
    struct node* newNode = node_create(x);
    if (list_is_empty(L)){
        L->first = newNode;
    } else if (p == 0){
        list_insert_header(x,L);
    } else {
        node_insert(newNode, L->first, p);
    }
}
void node_insert(struct node * x, struct node* n, int p){
    if (p == 1){
        x->next = n->next;
        n->next = x;
    } else if (n->next == NULL){
        n->next = x;
    } else {
            node_insert(x,n->next,p-1);
    }
}

void list_insert_header(void* x, struct list* L){
    struct node* newNode = node_create(x);
    if (list_is_empty(L)){
        L->first = newNode;
    } else {
        newNode->next = L->first;
        L->first = newNode;
    }
}

void list_insert_footer(void* x, struct list* L){
    struct node* newNode = node_create(x);
    if (list_is_empty(L)){
        L->first = newNode;
    } else {
        node_insert_end(newNode, L->first);
    }
}
void node_insert_end(struct node * x, struct node* n){
    if (n->next == NULL){
        n->next = x;
    } else {
        node_insert_end(x,n->next);
    }
}

void* list_delete(int pos, struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else if (pos == 0) {
        return list_delete_header(L);
    }
    else {
        return node_delete(pos, L->first);
    }
}
void* node_delete(int p, struct node* n){
    if (p == 1) {
        void * elem = n->next->element;
        n->next = n->next->next;
        return elem;
    } else if (n->next == NULL){
        return NULL;
    } else {
        return node_delete(p-1,n->next);
    }
}

void* list_delete_header(struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else {
        void* elem = L->first->element;
        L->first= L->first->next;
        return elem;
    }
}

void* list_delete_footer(struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else if (L->first->next == NULL) {
        return list_delete_header(L);
    }
    else {
        return node_delete_end(L->first);
    }
}
void* node_delete_end(struct node* n){
    if (n->next->next == NULL){
        void* elem = n->next->element;
        n->next = NULL;
        return elem;
    } else {
        return node_delete_end(n->next);
    }
}

void* list_getElem(int pos, struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else {
        return node_getElem(pos, L->first);
    }
}
void* node_getElem(int p, struct node* n) {
    if (p == 0) {
        return n->element;
    } else if (n->next == NULL) {
        return NULL;
    } else {
        return node_getElem(p-1, n->next);
    }
}

void* list_getElem_header(struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else {
        return L->first->element;
    }
}

void* list_getElem_footer( struct list* L){
    if (list_is_empty(L)){
        return NULL;
    } else {
        return node_getElem_end(L->first);
    }
}
void* node_getElem_end( struct node* n) {
    if (n->next == NULL) {
        return n->element;
    } else {
        return node_getElem_end(n->next);
    }
}