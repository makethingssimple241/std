//
//  vector.c
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include "vector.h"
#include "allocator.h"
#include "exception.h"
#include "stdexcept.h"

#include <errno.h>
#include <string.h>

vector *_new_vector(size_t value_size)
{
    vector *vec = allocator_allocate(sizeof(vector));
    if (!vec)
        throw(new_exception(bad_alloc));
    
    vec->value_size = value_size;
    vec->size = 0;
    vec->capacity = 0;
    vec->data = null;
    
    return vec;
}

void delete_vector(vector *vec)
{
    allocator_free(vec->data);
    allocator_free(vec);
}

void *vector_at(const vector *vec, size_t index)
{
    if (index >= vec->size)
        throw(new_exception(out_of_range));
    return vec->data + vec->value_size * index;
}

void *vector_front(const vector *vec)
{
    if (vec->size <= 0)
        throw(new_exception(out_of_range));

    return vector_at(vec, 0);
}

void *vector_back(const vector *vec)
{
    if (vec->size <= 0)
        throw(new_exception(out_of_range));

    return vector_at(vec, vec->size - 1);
}

void *vector_begin(const vector *vec)
{
    return vec->data;
}

void *vector_end(const vector *vec)
{
    return vec->data + vec->size * vec->value_size;
}

void _vector_next(const vector *vec, void **iterator)
{
    *iterator += vec->value_size;
}

bool vector_empty(const vector *vec)
{
    return vec->size == 0;
}

void vector_reserve(vector *vec, size_t capacity)
{
    if (capacity < vec->capacity)
        return;
    
    void *new_data = allocator_allocate(vec->value_size * capacity);
    if (!new_data)
        throw(new_exception(bad_alloc));

    memset(new_data, 0, vec->value_size * capacity);
    memcpy(new_data, vec->data, vec->value_size * vec->size);
    vec->data = new_data;
    vec->capacity = capacity;
}

void vector_push_back(vector *vec, const void *value)
{
    if (vec->size >= vec->capacity) {
        if (vec->capacity > 0)
            vector_reserve(vec, vec->capacity * vector_growth);
        else
            vector_reserve(vec, 1);
    }
    
    vector_push_back_unsafe(vec, value);
}

void vector_push_back_unsafe(vector *vec, const void* value)
{
    memcpy(vec->data + vec->value_size * vec->size++, value, vec->value_size);
}

void *vector_pop_back(vector *vec)
{
    if (vec->size > 0) {
        vec->size--;
        return vec->data + vec->value_size * vec->size;
    }
    
    return NULL;
}

void vector_insert(vector *vec, const void *value, size_t i)
{
    if (i >= vec->size)
        throw(new_exception(out_of_range));
    
    if (vec->size >= vec->capacity) {
        if (vec->capacity > 0)
            vector_reserve(vec, vec->capacity * vector_growth);
        else
            vector_reserve(vec, 1);
    }
    
    memmove(vec->data + vec->value_size * (i + 1),
            vec->data + vec->value_size * i,
            (vec->size - i) * vec->value_size);
    vec->size++;
    memcpy(vec->data + vec->value_size * i, value, vec->value_size);
}

void vector_clear(vector *vec)
{
    memset(vec->data, 0, vec->value_size * vec->size);
    vec->size = 0;
}
