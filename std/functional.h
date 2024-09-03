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

hash hash_uintptr_t(const uintptr_t *value);
hash hash_c_str(const char **s);
hash hash_string(const string *string);

#endif /* std_functional_h */
