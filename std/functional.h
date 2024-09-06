//
//  functional.h
//  std
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#ifndef std_functional_h
#define std_functional_h

#include "string.h"

#include <stdlib.h>

typedef size_t hash;
typedef hash(* hash_function)(void *);

typedef bool(* equal_function)(void *, void *);

hash hash_integer(const uintptr_t *value);
hash hash_c_str(const char **s);
hash hash_string(const string *string);

bool ptr_to_uintptr_t_equal(uintptr_t *lhs, uintptr_t *rhs);
bool ptr_to_c_str_equal(const char **lhs, const char **rhs);

#endif /* std_functional_h */
