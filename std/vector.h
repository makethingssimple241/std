//
//  vector.h
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#ifndef std_vector_h
#define std_vector_h

#include <stdlib.h>

#define new_vector(T) _new_vector(sizeof(T))
#define vector_for_each(vec, f) _vector_for_each((vec), (void (*)(void *))(f))
#define vector_next(vec, iterator) _vector_next((vec), (void **)(iterator))
#define vector_growth 2

typedef struct {
    void *data;
    size_t value_size, size, capacity;
} vector;

/// @note This is a private function that should not be called by the user
vector *_new_vector(size_t value_size);
void delete_vector(vector *vec);

// MARK: Element access

void *vector_at(const vector *vec, size_t index);
/// @note This is a private function that should not be called by the user
void _vector_for_each(const vector *vec, void(*f)(void *value));

// MARK: Iterators

void *vector_begin(const vector *vec);
void *vector_end(const vector *vec);
/// @note This is a private function that should not be called by the user
void _vector_next(const vector *vec, void **iterator);

// MARK: Capacity

void vector_resize(vector *vec, size_t size);

// MARK: Modifiers

/// @brief This function resizes the vector and zeroes the extra space
void vector_push_back(vector *vec, void *value);
/// @note This is an unsafe function.
/// It assumes that the vector has a size that can hold the pushed extra element.
void vector_push_back_unsafe(vector *vec, void* value);
void *vector_pop_back(vector* vec);
void vector_insert(vector *vec, void *value, size_t i);
void vector_clear(vector* vec);

#endif /* std_vector_h */
