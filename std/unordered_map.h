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

/// @param _equal_function It should be a function that takes in two <tt>V *</tt>s and returns a @c bool of whether they are equal
/// @param _hash_function It should be a function that takes in a <tt>V *</tt> and returns a @c hash
#define new_unordered_map(K, V, _equal_function, _hash_function) _new_unordered_map(sizeof(K), sizeof(V), (equal_function)(_equal_function), (hash_function)(_hash_function))
#define unordered_map_insert(map, key, value) _unordered_map_insert((map), (void *)(key), (void *)(value))
#define unordered_map_at(map, key) _unordered_map_at((map), (void *)(key))
#define unordered_map_contains(map, key) _unordered_map_contains((map), (void *)(key))

/// @note Can be used to hold both integers or pointers
typedef void *unordered_map_key_type;
/// @note Can only be used to hold pointers since empty key-value slots are signified by having a NULL value
typedef void *unordered_map_mapped_type;

typedef struct {
    unordered_map_key_type key;
    unordered_map_mapped_type value;
} unordered_map_value_type;

typedef struct {
    size_t size;
    size_t storage_capacity;
    unordered_map_value_type *storage;
    size_t key_size;
    size_t value_size;
    equal_function equal_function;
    hash_function hash_function;
    float max_load_factor;
} unordered_map;

/// @note This is a private function that should not be called by the user
unordered_map *_new_unordered_map(size_t key_size, size_t value_size, equal_function equal_function, hash_function hash_function);
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
