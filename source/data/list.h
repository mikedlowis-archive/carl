/**
  @file list.h
*/
#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct list_node_t {
    struct list_node_t* next;
    struct list_node_t* prev;
} list_node_t;

typedef struct {
    list_node_t* head;
    list_node_t* tail;
} list_t;

static void list_init(list_t* list)
{
    list->head = NULL;
    list->tail = NULL;
}

static bool list_empty(list_t* list)
{
    return (list->head == NULL);
}

static size_t list_size(list_t* list)
{
    size_t sz = 0;
    list_node_t* node = list->head;
    while (node != NULL) {
        sz++;
        node = node->next;
    }
    return sz;
}

static list_node_t* list_front(list_t* list)
{
    return list->head;
}

static void list_push_front(list_t* list, list_node_t* node)
{
    node->prev = NULL;
    node->next = list->head;
    if (list->head != NULL)
        list->head->prev = node;
    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
}

static list_node_t* list_pop_front(list_t* list)
{
    list_node_t* node = list->head;
    if (node != NULL) {
        list->head = node->next;
        if (list->head == NULL)
            list->tail = NULL;
        else
            list->head->prev = NULL;
        node->next = NULL;
    }
    return node;
}

static list_node_t* list_back(list_t* list)
{
    return list->tail;
}

static void list_push_back(list_t* list, list_node_t* node)
{
    node->next = NULL;
    node->prev = list->tail;
    if (list->tail != NULL)
        list->tail->next = node;
    list->tail = node;
    if (list->head == NULL)
        list->head = node;
}

static list_node_t* list_pop_back(list_t* list)
{
    list_node_t* node = list->tail;
    if (node != NULL) {
        list->tail = node->prev;
        if (list->tail == NULL)
            list->head = NULL;
        else
            list->tail->next = NULL;
        node->prev = NULL;
    }
    return node;
}

static bool list_node_has_next(list_node_t* node)
{
    return (node->next != NULL);
}

static list_node_t* list_node_next(list_node_t* node)
{
    return node->next;
}

static bool list_node_has_prev(list_node_t* node)
{
    return (node->prev != NULL);
}

static list_node_t* list_node_prev(list_node_t* node)
{
    return node->prev;
}

#define list_foreach(var,list) \
    for (list_node_t* var = (list)->head; var != NULL; var = var->next)

#endif /* LIST_H */
