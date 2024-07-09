//
//  vector.c
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include "vector.h"
#include "exception.h"
#include "stdexcept.h"

#include <errno.h>
#include <string.h>

vector *_new_vector(size_t value_size) {
    vector *vec = malloc(sizeof(vector));
    if (!vec)
        throw(new_exception(bad_alloc));
    
    vec->value_size = value_size;
    vec->size = 0;
    vec->capacity = 0;
    vec->data = NULL;
    
    return vec;
}

void delete_vector(vector *vec) {
    free(vec->data);
    free(vec);
}

void *vector_at(const vector *vec, size_t index) {
    if (index >= vec->size)
        throw(new_exception(out_of_range));
    return vec->data + vec->value_size * index;
}

void _vector_for_each(const vector *vec, void(*f)(void *value)) {
    for (size_t i = 0; i < vec->size; i++)
        f(vec->data + vec->value_size * i);
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

void vector_resize(vector *vec, size_t size)
{
    if (size < vec->capacity)
        return;
    
    // TODO: Zero memory
    void* new_data = realloc(vec->data, vec->value_size * size);
    if (new_data) {
        vec->data = new_data;
        vec->capacity = size;
    } else {
        throw(new_exception(bad_alloc));
    }
}

void vector_push_back(vector *vec, void *value) {
    if (vec->size >= vec->capacity) {
        if (vec->capacity > 0)
            vector_resize(vec, vec->capacity * vector_growth);
        else
            vector_resize(vec, 1);
    }
    
    vector_push_back_unsafe(vec, value);
}

void vector_push_back_unsafe(vector *vec, void* value)
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

void vector_insert(vector *vec, void *value, size_t i) {
    if (i >= vec->size)
        throw(new_exception(out_of_range));
    
    if (vec->size >= vec->capacity) {
        if (vec->capacity > 0)
            vector_resize(vec, vec->capacity * vector_growth);
        else
            vector_resize(vec, 1);
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
