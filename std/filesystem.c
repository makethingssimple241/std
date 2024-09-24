//
//  filesystem.c
//  std
//
//  Created by MakeThingsSimple on 3/9/2024.
//

#include "filesystem.h"

#include <ctype.h>
#include <string.h>

void delete_filesystem_path(filesystem_path *path)
{
    if (!path) {
        return;
    }

    delete_string(path);
}

filesystem_path *filesystem_path_extension(const filesystem_path *path)
{
    if (filesystem_path_has_extension(path))
        return new_string_from_c_str(strrchr(path->c_str, '.') + 1);
    else
        return new_string();
}

bool filesystem_path_empty(const filesystem_path *path)
{
    return string_empty(path);
}

bool filesystem_path_has_extension(const filesystem_path *path)
{
    char *extension = strrchr(path->c_str, '.');
    if (!extension)
        return false;
    
    if (*++extension == '\0')
        return false;
    
    for (size_t i = 0; extension[i] != '\0'; i++) {
        if (!isalnum(extension[i]))
            return false;
    }
    
    return true;
}

bool filesystem_path_is_absolute(const filesystem_path *path)
{
    return path->c_str[0] == filesystem_path_preferred_separator;
}
