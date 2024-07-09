//
//  format.c
//  std
//
//  Created by MakeThingsSimple on 28/6/2024.
//

#include "format.h"
#include "exception.h"
#include "stdexcept.h"

#include <stdarg.h>
#include <stdio.h>

string *format(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    string *result = NULL;
    int length = vsnprintf(NULL, 0, format, args);
    
    if (length < 0) {
        throw(new_exception(format_error));
    } else if (length == 0) {
        return new_string();
    } else {
        size_t size = length + 1;
        char *buffer = malloc(sizeof(char) * size);
        vsnprintf(buffer, size, format, args);
        result = new_string_from_c_str_without_copy(buffer);
    }
    
    va_end(args);
    return result;
}
