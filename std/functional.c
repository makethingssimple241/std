//
//  functional.c
//  std
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#include "functional.h"

hash hash_string(const char *s)
{
    if (s) {
        unsigned long hash = 5381;
        char c;
        
        const char *s_copy = s;
        
        while ((c = *s_copy++))
            hash = hash * 33 + c;

        return hash;
    } else {
        return 0;
    }
}
