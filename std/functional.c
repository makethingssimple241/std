//
//  functional.c
//  std
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#include "functional.h"

hash hash_uintptr_t(const uintptr_t *value)
{
    return *value * 2654435761;
}

hash hash_c_str(const char **s)
{
    if (*s) {
        unsigned long hash = 5381;
        char c = '\0';
        
        const char *s_copy = *s;
        
        while ((c = *s_copy++))
            hash = hash * 33 + c;

        return hash;
    } else {
        return 0;
    }
}

hash hash_string(const string *string)
{
    unsigned long hash = 5381;

    for (size_t i = 0; i < string->size; ++i)
        hash = hash * 33 + string->c_str[i];

    return hash;
}

bool ptr_to_uintptr_t_equal(const uintptr_t *lhs, const uintptr_t *rhs) {
    return *lhs == *rhs;
}

bool ptr_to_c_str_equal(const char **lhs, const char **rhs) {
    return c_str_equal(*lhs, *rhs);
}
