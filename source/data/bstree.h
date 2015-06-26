/**
  @file bstree.h
*/
#ifndef BSTREE_H
#define BSTREE_H

typedef struct bstree_node_t {
    struct bstree_node_t* parent;
    struct bstree_node_t* left;
    struct bstree_node_t* right;
} bstree_node_t;

typedef struct {
    bstree_node_t* root;
} bstree_t;

void bstree_init(bstree_t* bstree);

bool bstree_empty(bstree_t* bstree);

size_t bstree_size(bstree_t* bstree);

void bstree_insert(bstree_t* bstree, bstree_node_t* node);

bstree_node_t* bstree_lookup(bstree_t* bstree, bstree_node_t* node);

bool bstree_node_hasnext(bstree_node_t* node);

bstree_node_t* bstree_node_next(bstree_node_t* node);

bool bstree_node_hasprev(bstree_node_t* node);

bstree_node_t* bstree_node_prev(bstree_node_t* node);

#endif /* BSTREE_H */
