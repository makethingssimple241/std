//
//  format.c
//  std
//
//  Created by MakeThingsSimple on 28/6/2024.
//

#include "format.h"
#include "allocator.h"
#include "exception.h"
#include "stdexcept.h"
#include "string.h"

#include <stdarg.h>
#include <stdio.h>

string *format(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(null, 0, format, args);
    va_end(args);
    
    if (size <= 0) {
        return null;
    }
    
    va_start(args, format);
    
    size += 1; // for null-termination character
    char *buffer = allocator_allocate(sizeof(char) * size);
    vsnprintf(buffer, size, format, args);
    
    va_end(args);
    return new_string_from_c_str_without_copy(buffer);
}
