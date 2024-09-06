//
//  vector.h
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#ifndef std_vector_h
#define std_vector_h

#include <stdbool.h>
#include <stdlib.h>

#define new_vector(T) _new_vector(sizeof(T))
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
void *vector_front(const vector *vec);
void *vector_back(const vector *vec);

// MARK: Iterators

void *vector_begin(const vector *vec);
void *vector_end(const vector *vec);
/// @note This is a private function that should not be called by the user
void _vector_next(const vector *vec, void **iterator);

// MARK: Capacity

bool vector_empty(const vector *vec);

/// @brief This function resizes the vector if the new capacity is greater than its capacity
void vector_reserve(vector *vec, size_t capacity);

// MARK: Modifiers

void vector_push_back(vector *vec, const void *value);
/// @note This is an unsafe function.
/// It assumes that the vector has a size that can hold the pushed extra element.
void vector_push_back_unsafe(vector *vec, const void* value);
void *vector_pop_back(vector* vec);
void vector_insert(vector *vec, const void *value, size_t i);
void vector_clear(vector* vec);

#endif /* std_vector_h */
