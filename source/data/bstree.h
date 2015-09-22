/**
  @file bstree.h
*/
#ifndef BSTREE_H
#define BSTREE_H

#include <carl.h>

typedef struct bstree_node_t {
    struct bstree_node_t* left;
    struct bstree_node_t* right;
} bstree_node_t;

typedef int (*bstree_cmpfn_t)(bstree_node_t* a, bstree_node_t* b);

typedef struct {
    bstree_node_t* root;
    bstree_cmpfn_t cmpfn;
    bool allow_dups;
} bstree_t;

void bstree_init(bstree_t* bstree, bstree_cmpfn_t cmpfn, bool allow_dups);

bool bstree_empty(bstree_t* bstree);

size_t bstree_size(bstree_t* bstree);

void bstree_insert(bstree_t* bstree, bstree_node_t* node);

bstree_node_t* bstree_lookup(bstree_t* bstree, bstree_node_t* node);

#endif /* BSTREE_H */
