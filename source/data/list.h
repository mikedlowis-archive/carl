/**
  @file list.h
*/
#ifndef LIST_H
#define LIST_H

#include <libc.h>

typedef struct list_node_t {
    struct list_node_t* next;
    struct list_node_t* prev;
} list_node_t;

typedef struct {
    list_node_t* head;
    list_node_t* tail;
} list_t;

void list_init(list_t* list);

bool list_empty(list_t* list);

size_t list_size(list_t* list);

list_node_t* list_front(list_t* list);

void list_push_front(list_t* list, list_node_t* node);

list_node_t* list_pop_front(list_t* list);

list_node_t* list_back(list_t* list);

void list_push_back(list_t* list, list_node_t* node);

list_node_t* list_pop_back(list_t* list);

bool list_node_has_next(list_node_t* node);

list_node_t* list_node_next(list_node_t* node);

bool list_node_has_prev(list_node_t* node);

list_node_t* list_node_prev(list_node_t* node);

#endif /* LIST_H */
