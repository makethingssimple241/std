//
//  fstream.h
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#ifndef std_fstream_h
#define std_fstream_h

#include "string.h"

#include <stdio.h>

typedef struct {
    FILE *native_handle;
} fstream;

typedef enum {
    FSTREAM_OPEN_MODE_READ,
    FSTREAM_OPEN_MODE_WRITE,
    FSTREAM_OPEN_MODE_CREATE_WRITE,
    FSTREAM_OPEN_MODE_APPEND,
    FSTREAM_OPEN_MODE_READ_BINARY,
    FSTREAM_OPEN_MODE_WRITE_BINARY,
    FSTREAM_OPEN_MODE_CREATE_WRITE_BINARY,
    FSTREAM_OPEN_MODE_APPEND_BINARY,
    FSTREAM_OPEN_MODE_READ_WRITE_UPDATE,
    FSTREAM_OPEN_MODE_WRITE_UPDATE,
    FSTREAM_OPEN_MODE_CREATE_WRITE_UPDATE,
    FSTREAM_OPEN_MODE_APPEND_UPDATE,
    FSTREAM_OPEN_MODE_READ_WRITE_BINARY_UPDATE,
    FSTREAM_OPEN_MODE_WRITE_BINARY_UPDATE,
    FSTREAM_OPEN_MODE_CREATE_WRITE_BINARY_UPDATE,
    FSTREAM_OPEN_MODE_APPEND_BINARY_UPDATE,
} fstream_open_mode;

fstream fstream_open(const char *path, fstream_open_mode mode);
void fstream_close(const fstream *fs);

/// @note If the function succeed, `*s` will be a valid `string *` that needs to be `delete_string`ed by the caller.
/// If the function fails, `*s` will be left untouched.
void fstream_getline(const fstream *fs, string *s);

#endif /* std_fstream_h */
