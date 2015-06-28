#include <data/list.h>

void list_init(list_t* list)
{
    list->head = NULL;
    list->tail = NULL;
}

bool list_empty(list_t* list)
{
    return (list->head == NULL);
}

size_t list_size(list_t* list)
{
    size_t sz = 0;
    list_node_t* node = list->head;
    while (node != NULL) {
        sz++;
        node = node->next;
    }
    return sz;
}

list_node_t* list_front(list_t* list)
{
    return list->head;
}

void list_push_front(list_t* list, list_node_t* node)
{
    node->prev = NULL;
    node->next = list->head;
    list->head = node;
    if (list->tail == NULL)
        list->tail = node;
}

list_node_t* list_pop_front(list_t* list)
{
    list_node_t* node = list->head;
    list->head = node->next;
    if (list->head == NULL)
        list->tail = NULL;
    node->next = NULL;
    return node;
}

list_node_t* list_back(list_t* list)
{
    return list->tail;
}

void list_push_back(list_t* list, list_node_t* node)
{
    node->next = NULL;
    node->prev = list->tail;
    list->tail = node;
    if (list->head == NULL)
        list->head = node;
}

list_node_t* list_pop_back(list_t* list)
{
    list_node_t* node = list->tail;
    list->tail = node->prev;
    if (list->tail == NULL)
        list->head = NULL;
    node->prev = NULL;
    return node;
}

bool list_node_has_next(list_node_t* node)
{
    return (node->next != NULL);
}

list_node_t* list_node_next(list_node_t* node)
{
    return node->next;
}

bool list_node_has_prev(list_node_t* node)
{
    return (node->prev != NULL);
}

list_node_t* list_node_prev(list_node_t* node)
{
    return node->prev;
}

