/**
  @file hash.c
  @brief See header for details
  $Revision$
  $HeadURL$
  */
#include <data/hash.h>
#include <stdlib.h>

#define NUM_PRIMES (sizeof(primes)/sizeof(unsigned int))

static unsigned int Primes[] = {
    5, 13, 23, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739, 6291469,
    12582917, 25165843, 50331653, 100663319, 201326611, 402653189,
    805306457, 1610612741
};

static inline unsigned int num_buckets(hash_t* hash) {
    return Primes[hash->bkt_count];
}

void hash_init(hash_t* hash, hash_hashfn_t hashfn, hash_cmpfn_t cmpfn, hash_freefn_t delfn)
{
    hash->size      = 0;
    hash->bkt_count = 0;
    hash->hashfn    = hashfn;
    hash->cmpfn     = cmpfn;
    hash->delfn     = delfn;
    hash->buckets   = (hash_entry_t**)calloc(sizeof(hash_entry_t*), num_buckets(hash));
}

void hash_deinit(hash_t* hash)
{
    (void)hash;
}

bool hash_set(hash_t* hash, hash_entry_t* entry)
{
    //if (hash->size >= num_buckets(hash))
    //    rehash(hash);
    unsigned int hashval = hash->hashfn(entry);
    unsigned int index   = (hashval % num_buckets(hash));
    hash_entry_t* parent = NULL;
    hash_entry_t* node   = hash->buckets[index];
    //find_entry(&parent, &node, hash);

    if (node != NULL) {
        if (parent == NULL) {
            hash_entry_t* deadite = node;
            node = node->next;
            hash->delfn(deadite);
        }

    } else {

    }
    return true;
}

hash_entry_t* hash_get(hash_t* hash, hash_entry_t* entry)
{
    unsigned int hashval = hash->hashfn(entry);
    unsigned int index   = (hashval % num_buckets(hash));
    //hash_entry_t* parent = NULL;
    hash_entry_t* node   = hash->buckets[index];
    //find_entry(&parent, &node, hashval, entry);
    return node;
}

bool hash_del(hash_t* hash, hash_entry_t* entry)
{
    (void)hash;
    (void)entry;
    return false;
}

void hash_clr(hash_t* hash)
{
    /* Delete all the entries  in the hash */
    for (unsigned int i = 0; i < num_buckets(hash); i++) {
        hash_entry_t* node = hash->buckets[0];
        while (node != NULL) {
            hash_entry_t* deadite = node;
            node = node->next;
            hash->delfn(deadite);
        }
    }
    /* Shrink the buckets array */
    free(hash->buckets);
    hash->bkt_count = 0;
    hash->buckets   = (hash_entry_t**)calloc(sizeof(hash_entry_t*), num_buckets(hash));
}

