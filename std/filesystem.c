//
//  filesystem.c
//  std
//
//  Created by MakeThingsSimple on 9/6/2024.
//

#include "filesystem.h"
#include "exception.h"
#include "stdexcept.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

#ifdef WIN32
#error Windows is currently not supported
#endif

#ifndef _WIN32
#include <unistd.h>
#include <sys/param.h>

#define STD_PATH_SEPARATOR '/'
#endif

filesystem_path *new_filesystem_path(void)
{
#ifndef _WIN32
    char *buffer = malloc(sizeof(char) * MAXPATHLEN);
    if (!buffer)
        throw(new_exception(bad_alloc));
    
    if (!getcwd(buffer, MAXPATHLEN))
        throw(system_error(errno, strerror(errno)));
    
    return new_string_from_c_str_without_copy(buffer);
#endif
}

void delete_filesystem_path(filesystem_path *path)
{
    delete_string(path);
}

filesystem_path *filesystem_path_root_name(const filesystem_path *path)
{
#ifndef _WIN32
    if (filesystem_path_is_absolute(path))
        return new_string_from_c_str("/");
    
    char *separatorPosition;
    if ((separatorPosition = strchr(path->c_str, STD_PATH_SEPARATOR)))
        return new_string_from_c_str_view(path->c_str, separatorPosition - path->c_str);
    
    return new_string();
#endif
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
#ifndef _WIN32
    return path->c_str[0] == '/';
#endif
}
