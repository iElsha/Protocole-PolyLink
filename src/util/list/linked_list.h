//
// Created by maxence on 04/02/2020.
//

#ifndef PROTOCOLE_POLYLINK_LINKED_LIST_H
#define PROTOCOLE_POLYLINK_LINKED_LIST_H
#include <stdbool.h>

struct node {
	void* element;
    struct node* next;
};

struct list {
    struct node* first;
};


struct list* list_create();
struct node* node_create(void* x);

void list_destroy(struct list* L);
void node_destroy(struct node* n);


int list_is_empty(struct list* L);

int list_lenght(struct list* L);
int node_lenght(struct node* n);

bool list_find(void* x, struct list* L);
bool node_find(void *x, struct node* n);

void list_insert(void * x, struct list* L, int p);
void node_insert(struct node * x, struct node* n, int p);

void list_insert_header(void* x, struct list* L);

void list_insert_footer(void* x, struct list* L);
void node_insert_end(struct node * x, struct node* n);

void* list_delete(int pos, struct list* L);
void* node_delete(int p, struct node* n);

void* list_delete_header(struct list* L);

void* list_delete_footer(struct list* L);
void* node_delete_end(struct node* n);

void* list_getElem(int pos, struct list* L);
void* node_getElem(int p, struct node* n);

void* list_getElem_header( struct list* L);

void* list_getElem_footer(struct list* L);
void* node_getElem_end( struct node* n);

#endif //PROTOCOLE_POLYLINK_LINKED_LIST_H
