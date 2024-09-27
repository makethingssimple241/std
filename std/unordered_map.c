//
//  unordered_map.c
//  std
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#include "unordered_map.h"
#include "allocator.h"
#include "exception.h"
#include "stdexcept.h"

#include <errno.h>
#include <stddef.h>
#include <string.h>

static size_t _unordered_map_find_index(size_t capacity, unordered_map_value_type *storage, equal_function equal_function, hash_function hash_function, void *key) {
    size_t i = hash_function(key) % capacity;
    while (storage[i].value && !equal_function(key, storage[i].key)) {
        i = (i + 1) % capacity;
    }
    return i;
}

/// @link https://en.wikipedia.org/wiki/Open_addressing#Example_pseudocode
static size_t unordered_map_find_index(const unordered_map *map, void *key) {
    return _unordered_map_find_index(map->storage_capacity, map->storage, map->equal_function, map->hash_function, key);
}

unordered_map *_new_unordered_map(size_t key_size, size_t value_size, equal_function equal_function, hash_function hash_function)
{
    unordered_map *map = allocator_allocate(sizeof(unordered_map));
    if (!map)
        throw(new_exception(bad_alloc));
    
    map->size = 0;
    map->storage_capacity = 10;
    map->storage = allocator_allocate(sizeof(unordered_map_value_type) * map->storage_capacity);
    memset(map->storage, 0, sizeof(unordered_map_value_type) * map->storage_capacity);
    map->key_size = key_size;
    map->value_size = value_size;
    map->equal_function = equal_function;
    map->hash_function = hash_function;
    map->max_load_factor = 0.8f;
    
    return map;
}

void delete_unordered_map(unordered_map *map)
{
    if (!map) {
        return;
    }

    for (size_t i = 0; i < map->storage_capacity; i++) {
        void *key = map->storage[i].key;
        void *value = map->storage[i].value;
        
        if (value) {
            allocator_free(key);
            allocator_free(value);
        }
    }

    allocator_free(map->storage);
}

unordered_map_value_type *unordered_map_begin(const unordered_map *map)
{
    unordered_map_value_type *value = map->storage;
    while (value != unordered_map_end(map) && !value->key && !value->value) {
        value++;
    }
    
    return value;
}

unordered_map_value_type *unordered_map_end(const unordered_map *map)
{
    return &map->storage[map->storage_capacity];
}

void unordered_map_next(const unordered_map *map, unordered_map_value_type** iterator)
{
    ptrdiff_t i = *iterator - map->storage;
    if (i < 0)
        throw(new_exception(out_of_range));
    
    for (++i; i < map->storage_capacity; i++) {
        unordered_map_value_type *value = &map->storage[i];
        if (value->key && value->value) {
            *iterator = value;
            return;
        }
    }
    
    *iterator = unordered_map_end(map);
}

void _unordered_map_insert(unordered_map *map, unordered_map_key_type key, unordered_map_mapped_type value)
{
    if (unordered_map_load_factor(map) >= map->max_load_factor)
    {   
        // Allocate new storage
        
        size_t new_capacity = map->storage_capacity * 2;
        size_t new_capacity_in_bytes = new_capacity * sizeof(unordered_map_value_type);
        unordered_map_value_type *new_storage = allocator_allocate(new_capacity_in_bytes);
        if (!new_storage)
            throw(new_exception(bad_alloc));

        memset(new_storage, 0, new_capacity_in_bytes);
        
        // Copy the original elements into a rehashed location in the new storage

        for (size_t i = 0; i < map->storage_capacity; i++) {
            if (!map->storage[i].key || !map->storage[i].value) {
                continue;
            }
            
            size_t index_in_new_storage = _unordered_map_find_index(new_capacity, new_storage, map->equal_function, map->hash_function, map->storage[i].key);
            new_storage[index_in_new_storage] = map->storage[i];
        }
        
        // Migrate to new storage and capacity

        allocator_free(map->storage);
        map->storage = new_storage;
        map->storage_capacity = new_capacity;
    }

    size_t insert_index = unordered_map_find_index(map, key);

    void *key_storage = allocator_allocate(map->key_size);
    memset(key_storage, 0, map->key_size);
    memcpy(key_storage, key, map->key_size);
    
    void *value_storage = allocator_allocate(map->value_size);
    memset(value_storage, 0, map->value_size);
    memcpy(value_storage, value, map->value_size);

    map->storage[insert_index] = (unordered_map_value_type){key_storage, value_storage};
    map->size++;
}

unordered_map_mapped_type _unordered_map_at(const unordered_map *map, unordered_map_key_type key)
{
    if (!unordered_map_contains(map, key))
        throw(new_exception(out_of_range));
    
    return map->storage[unordered_map_find_index(map, key)].value;
}

bool _unordered_map_contains(const unordered_map *map, unordered_map_key_type key)
{
    size_t index = unordered_map_find_index(map, key);
    
    if (index >= map->storage_capacity)
        return false;
    
    return map->storage[index].value;
}

float unordered_map_load_factor(const unordered_map *map)
{
    return (float)map->size / map->storage_capacity;
}

float unordered_map_max_load_factor(const unordered_map *map)
{
    return map->max_load_factor;
}

void unordered_map_set_max_load_factor(unordered_map *map, float max_load_factor)
{
    map->max_load_factor = max_load_factor;
}
