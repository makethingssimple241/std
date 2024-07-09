//
//  fstream.c
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include "fstream.h"
#include "exception.h"
#include "stdexcept.h"

#include <assert.h>
#include <errno.h>
#include <string.h>

static const char *fstream_open_mode_to_string(fstream_open_mode mode)
{
    switch (mode) {
    case FSTREAM_OPEN_MODE_READ:
        return "r";
    case FSTREAM_OPEN_MODE_WRITE:
        return "w";
    case FSTREAM_OPEN_MODE_CREATE_WRITE:
        return "wx";
    case FSTREAM_OPEN_MODE_APPEND:
        return "a";
    case FSTREAM_OPEN_MODE_READ_BINARY:
        return "rb";
    case FSTREAM_OPEN_MODE_WRITE_BINARY:
        return "wb";
    case FSTREAM_OPEN_MODE_CREATE_WRITE_BINARY:
        return "wbx";
    case FSTREAM_OPEN_MODE_APPEND_BINARY:
        return "ab";
    case FSTREAM_OPEN_MODE_READ_WRITE_UPDATE:
        return "r+";
    case FSTREAM_OPEN_MODE_WRITE_UPDATE:
        return "w+";
    case FSTREAM_OPEN_MODE_CREATE_WRITE_UPDATE:
        return "w+x";
    case FSTREAM_OPEN_MODE_APPEND_UPDATE:
        return "a+";
    case FSTREAM_OPEN_MODE_READ_WRITE_BINARY_UPDATE:
        return "rb+";
    case FSTREAM_OPEN_MODE_WRITE_BINARY_UPDATE:
        return "wb+";
    case FSTREAM_OPEN_MODE_CREATE_WRITE_BINARY_UPDATE:
        return "wb+x";
    case FSTREAM_OPEN_MODE_APPEND_BINARY_UPDATE:
        return "ab+";
    }
    
    assert(false && "Unkown fstream_open_mode");
}

fstream fstream_open(const char *path, fstream_open_mode mode) {
    FILE *file = fopen(path, fstream_open_mode_to_string(mode));
    if (!file)
        throw(system_error(errno, strerror(errno)));
    
    return (fstream) {
        .native_handle = file
    };
}

void fstream_close(const fstream *fs) {
    if (fclose(fs->native_handle))
        throw(system_error(errno, strerror(errno)));
}

void fstream_getline(const fstream *fs, string **s)
{
    char* buffer = NULL;
    size_t size = 0;
    
    if (getline(&buffer, &size, fs->native_handle) == -1) {
        if (errno == EINVAL || errno == EOVERFLOW)
            throw(system_error(errno, strerror(errno)));
        else
            // it just reached EOF
            return;
    }
    
    *s = new_string_from_c_str_without_copy(buffer);
}
