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

unordered_map *_new_unordered_map(hash_function hash_function)
{
    unordered_map *map = allocator_allocate(sizeof(unordered_map));
    if (!map)
        throw(new_exception(bad_alloc));
    
    map->size = 0;
    map->storage_capacity = 10;
    map->storage = calloc(map->storage_capacity, sizeof(unordered_map_value_type));
    map->max_load_factor = 0.8f;
    map->hash_function = hash_function;
    
    return map;
}

void delete_unordered_map(unordered_map *map)
{
    allocator_free(map->storage);
}

unordered_map_value_type *unordered_map_begin(const unordered_map *map)
{
    unordered_map_value_type *value = map->storage;
    while (!value->value && value != unordered_map_end(map)) {
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
        if (map->hash_function(value->key) % map->storage_capacity == i && value->value) {
            *iterator = value;
            return;
        }
    }
    
    *iterator = unordered_map_end(map);
}

void _unordered_map_insert(unordered_map *map, unordered_map_key_type key, unordered_map_mapped_type value)
{
    size_t index = map->hash_function(key) % map->storage_capacity;
    
    if (unordered_map_load_factor(map) >= map->max_load_factor)
    {
        // 1. Make a copy of the original entries
        
        unordered_map_value_type *copy = allocator_allocate(sizeof(unordered_map_value_type) * map->storage_capacity);
        if (!copy)
            throw(new_exception(bad_alloc));
        
        memcpy(copy, map->storage, sizeof(unordered_map_value_type) * map->storage_capacity);
        
        // 2. Resize storage
        
        size_t new_capacity = map->storage_capacity * 2;
        map->storage_capacity *= 2;
        allocator_free(map->storage);
        map->storage = allocator_allocate(new_capacity * sizeof(unordered_map_value_type));
        if (!map->storage)
            throw(new_exception(bad_alloc));

        memset(map->storage + map->storage_capacity, 0, map->storage_capacity);
        map->storage_capacity = new_capacity;
        
        // 3. Refill the reallocated storage with rehashed entries
        
        for (size_t i = 0; i < map->storage_capacity; i++) {
            size_t index = map->hash_function(copy[i].key) % map->storage_capacity;
            map->storage[index] = copy[i];
        }
        
        // 4. Free the memory of the copy
        
        allocator_free(copy);
        
        // 5. Generate a index to insert the new element with the resized size
        
        index = map->hash_function(key) % map->storage_capacity;
    }
    
    map->storage[index] = (unordered_map_value_type){key, value};
    map->size++;
}

unordered_map_mapped_type _unordered_map_at(const unordered_map *map, unordered_map_key_type key)
{
    if (!unordered_map_contains(map, key))
        throw(new_exception(out_of_range));
    
    size_t index = map->hash_function(key) % map->storage_capacity;
    return map->storage[index].value;
}

bool _unordered_map_contains(const unordered_map *map, unordered_map_key_type key)
{
    size_t index = map->hash_function(key) % map->storage_capacity;
    
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
