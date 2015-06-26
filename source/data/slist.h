/**
  @file slist.h
*/
#ifndef SLIST_H
#define SLIST_H

#include <libc.h>

typedef struct slist_node_t {
    struct slist_node_t* next;
} slist_node_t;

typedef struct {
    slist_node_t* head;
} slist_t;

void slist_init(slist_t* list);

bool slist_empty(slist_t* list);

size_t slist_size(slist_t* list);

slist_node_t* slist_front(slist_t* list);

void slist_push_front(slist_t* list, slist_node_t* node);

slist_node_t* slist_pop_front(slist_t* list);

slist_node_t* slist_back(slist_t* list);

void slist_push_back(slist_t* list, slist_node_t* node);

slist_node_t* slist_pop_back(slist_t* list);

bool slist_node_has_next(slist_node_t* node);

slist_node_t* slist_node_next(slist_node_t* node);

#endif /* SLIST_H */
