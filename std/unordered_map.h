//
//  unordered_map.h
//  std
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#ifndef std_unordered_map_h
#define std_unordered_map_h

#include "functional.h"
#include "vector.h"

#include <stdbool.h>

#define new_unordered_map(_f) _new_unordered_map((hash_function)(_f))
#define unordered_map_insert(map, key, value) _unordered_map_insert((map), (uintptr_t)(key), (value))
#define unordered_map_at(map, key) _unordered_map_at((map), (uintptr_t)(key))
#define unordered_map_contains(map, key) _unordered_map_contains((map), (uintptr_t)(key))

typedef uintptr_t unordered_map_key_type;
typedef void *unordered_map_mapped_type;

typedef struct {
    unordered_map_key_type key;
    unordered_map_mapped_type value;
} unordered_map_value_type;

typedef struct {
    unordered_map_value_type *storage;
    size_t size;
    size_t storage_capacity;
    hash_function hash_function;
    float max_load_factor;
} unordered_map;

/// @note This is a private function that should not be called by the user
unordered_map *_new_unordered_map(hash_function hash_function);
void delete_unordered_map(unordered_map *map);

// MARK: Iterators

unordered_map_value_type *unordered_map_begin(const unordered_map *map);
unordered_map_value_type *unordered_map_end(const unordered_map *map);
void unordered_map_next(const unordered_map *map, unordered_map_value_type** iterator);

// MARK: Modifiers

/// @note This is a private function that should not be called by the user
void _unordered_map_insert(unordered_map *map, unordered_map_key_type key, unordered_map_mapped_type value);

// MARK: Lookup

unordered_map_mapped_type _unordered_map_at(const unordered_map *map, unordered_map_key_type key);
/// @note This is a private function that should not be called by the user
bool _unordered_map_contains(const unordered_map *map, unordered_map_key_type key);

// MARK: Hash policy

float unordered_map_load_factor(const unordered_map *map);
float unordered_map_max_load_factor(const unordered_map *map);
void unordered_map_set_max_load_factor(unordered_map *map, float max_load_factor);

#endif /* std_unordered_map_h */
