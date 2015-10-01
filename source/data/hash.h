/**
  @file hash.h
  @brief Generic hashtable implementation.
*/
#ifndef HASH_H
#define HASH_H

#include <stddef.h>
#include <stdbool.h>

typedef struct hash_entry_t {
    unsigned int hash;
    struct hash_entry_t* next;
} hash_entry_t;

typedef unsigned int (*hash_hashfn_t)(const hash_entry_t* entry);

typedef int (*hash_cmpfn_t)(const hash_entry_t* entry1, const hash_entry_t* entry2);

typedef void (*hash_freefn_t)(hash_entry_t* key);

typedef struct {
    size_t size;
    size_t bkt_count;
    hash_entry_t** buckets;
    hash_hashfn_t hashfn;
    hash_cmpfn_t cmpfn;
    hash_freefn_t delfn;
} hash_t;

void hash_init(hash_t* hash, hash_hashfn_t hashfn, hash_cmpfn_t cmpfn, hash_freefn_t delfn);

void hash_deinit(hash_t* hash);

bool hash_set(hash_t* hash, hash_entry_t* entry);

hash_entry_t* hash_get(hash_t* hash, hash_entry_t* entry);

bool hash_del(hash_t* hash, hash_entry_t* entry);

void hash_clr(hash_t* hash);

#endif /* HASH_H */
