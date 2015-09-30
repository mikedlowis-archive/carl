/**
  @file vec.h
*/
#ifndef VEC_H
#define VEC_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    size_t   elem_count;
    size_t   elem_size;
    size_t   elem_capacity;
    uint8_t* elem_buffer;
} vec_t;

void vec_init(vec_t* vec, size_t elem_size);

size_t vec_size(vec_t* vec);

bool vec_empty(vec_t* vec);

size_t vec_capacity(vec_t* vec);

void vec_resize(vec_t* vec, size_t size, void* data);

size_t vec_next_capacity(size_t req_size);

void vec_shrink_to_fit(vec_t* vec);

void vec_reserve(vec_t* vec, size_t size);

void* vec_at(vec_t* vec, size_t index);

void vec_set(vec_t* vec, size_t index, void* data);

bool vec_insert(vec_t* vec, size_t index, size_t num_elements, ...);

bool vec_erase(vec_t* vec, size_t start_idx, size_t end_idx);

void vec_push_back(vec_t* vec, void* data);

void vec_pop_back(vec_t* vec, void* outdata);

void vec_clear(vec_t* vec);

#endif /* VEC_H */
