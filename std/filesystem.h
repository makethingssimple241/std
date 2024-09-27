//
//  filesystem.h
//  std
//
//  Created by MakeThingsSimple on 9/6/2024.
//

#ifndef std_filesystem_h
#define std_filesystem_h

#include "string.h"

#include <stdbool.h>

#ifndef _WIN32
#define filesystem_path_preferred_separator '/'
#endif

typedef string filesystem_path;

/// @brief Returns the path of the current working directory
filesystem_path new_filesystem_path(void);
void delete_filesystem_path(filesystem_path *path);

// MARK: Decomposition

filesystem_path filesystem_path_root_name(const filesystem_path *path);
filesystem_path filesystem_path_extension(const filesystem_path *path);

// MARK: Queries

bool filesystem_path_empty(const filesystem_path *path);
bool filesystem_path_has_extension(const filesystem_path *path);
bool filesystem_path_is_absolute(const filesystem_path *path);

// MARK: Non-member functions

size_t filesystem_file_size(const filesystem_path *path);

#endif /* std_filesystem_h */
