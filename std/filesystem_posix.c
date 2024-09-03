//
//  filesystem_posix.c
//  std
//
//  Created by MakeThingsSimple on 9/6/2024.
//

#ifndef _WIN32

#include "filesystem.h"
#include "allocator.h"
#include "exception.h"
#include "stdexcept.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

#include <unistd.h>
#include <sys/param.h>
#include <sys/stat.h>

filesystem_path *new_filesystem_path(void)
{
    char *buffer = allocator_allocate(sizeof(char) * MAXPATHLEN);
    if (!buffer)
        throw(new_exception(bad_alloc));
    
    if (!getcwd(buffer, MAXPATHLEN))
        throw(system_error(errno, strerror(errno)));
    
    return new_string_from_c_str_without_copy(buffer);
}

filesystem_path *filesystem_path_root_name(const filesystem_path *path)
{
    if (filesystem_path_is_absolute(path))
        return new_string_from_c_str("/");
    
    char *separator_position;
    if ((separator_position = strchr(path->c_str, filesystem_path_preferred_separator)))
        return new_string_from_c_str_view(path->c_str, separator_position - path->c_str);
    
    return new_string();
}

size_t filesystem_file_size(const filesystem_path *path)
{
    struct stat s;

    if (stat(path->c_str, &s) != 0) {
        return (size_t)-1;
    }

    return s.st_size;
}

#endif