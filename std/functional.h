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
typedef hash(* hash_function)(uintptr_t);

hash hash_string(const char *s);

#endif /* std_functional_h */
