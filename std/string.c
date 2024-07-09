//
//  string.c
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include "string.h"
#include "exception.h"
#include "stdexcept.h"

#include <ctype.h>
#include <errno.h>
#include <string.h>

string *new_string(void)
{
    return new_string_from_c_str("");
}

string *new_string_from_c_str(const char *c_str)
{
    string *s = malloc(sizeof(string));
    if (!s)
        throw(system_error(errno, strerror(errno)));
    
    size_t length = strlen(c_str) + 1;
    
    s->c_str = strdup(c_str);
    if (!s->c_str)
        throw(new_exception(bad_alloc));
    
    s->size = length;
    return s;
}

string *new_string_from_c_str_without_copy(char *c_str)
{
    string *s = malloc(sizeof(string));
    if (!s)
        throw(system_error(errno, strerror(errno)));
    
    s->c_str = c_str;
    s->size = strlen(c_str) + 1;
    return s;
}

string *new_string_from_c_str_view(const char *c_str, size_t length)
{
    string *s = malloc(sizeof(string));
    if (!s)
        throw(new_exception(bad_alloc));
    
    size_t size = length + 1;
    
    s->c_str = malloc(sizeof(char) * size);
    if (!s->c_str)
        throw(new_exception(bad_alloc));
    
    strncpy(s->c_str, c_str, size);
    s->c_str[size] = '\0';
    s->size = size;
    return s;
}

string *copy_string(const string *s)
{
    return new_string_from_c_str(s->c_str);
}

void delete_string(string *s)
{
    free(s->c_str);
    free(s);
}

void string_concatenate(string *s1, const string *s2)
{
    size_t length = s2->size - 1 + s1->size;
    char *buffer = malloc(sizeof(char) * length);
    if (!buffer)
        throw(new_exception(bad_alloc));
    
    strcpy(buffer, s1->c_str);
    strcpy(buffer + s1->size - 1, s2->c_str);
    
    free(s1->c_str);
    s1->c_str = buffer;
    s1->size = length;
}

void string_concatenate_with_c_str(string *s1, const char* s2)
{
    size_t s2Length = strlen(s2);
    
    size_t length = s2Length + s1->size;
    char *buffer = malloc(sizeof(char) * length);
    if (!buffer)
        throw(new_exception(bad_alloc));
    
    strcpy(buffer, s1->c_str);
    strcpy(buffer + s1->size - 1, s2);
    
    free(s1->c_str);
    s1->c_str = buffer;
    s1->size = length;
}

void string_append(string *s, char c)
{
    char *buffer = malloc(sizeof(char) * ++s->size);
    if (!buffer)
        throw(new_exception(bad_alloc));
    
    strcpy(buffer, s->c_str);
    buffer[s->size - 2] = c;
    buffer[s->size - 1] = '\0';
    
    free(s->c_str);
    s->c_str = buffer;
}

void string_remove_first(string *s)
{
    string_remove_first_n(s, 1);
}

void string_remove_first_n(string *s, size_t n)
{
    if (n <= 0)
        return;
    else if (n > s->size)
        throw(new_exception(out_of_range));
    
    s->size -= n;
    memmove(s->c_str, s->c_str + n, s->size);
}

void string_remove_last(string *s)
{
    string_remove_last_n(s, 1);
}

void string_remove_last_n(string *s, size_t n)
{
    if (n <= 0)
        return;
    else if (n > s->size)
        throw(new_exception(out_of_range));
    
    memset(&s->c_str[s->size - 1 - n], 0, n);
    s->size -= n;
}

bool c_str_empty(const char *s)
{
    return strcmp(s, "") == 0;
}

bool string_empty(const string *s)
{
    return c_str_empty(s->c_str);
}

bool c_str_equal(const char *s1, const char *s2)
{
    return strcmp(s1, s2) == 0;
}

bool string_equal(const string *s1, const string *s2)
{
    if (s1->size != s2->size)
        return false;
    
    return c_str_equal(s1->c_str, s2->c_str);
}

bool string_equal_c_str(const string *s1, const char *s2)
{
    if (s1->size != strlen(s2) + 1)
        return false;
    
    return strncmp(s1->c_str, s2, s1->size) == 0;
}

bool c_str_case_insensitive_equal(const char *s1, const char *s2)
{
    size_t s1_length = strlen(s1);
    size_t s2_length = strlen(s2);
    
    if (s1_length != s2_length)
        return false;
    
    for (size_t i = 0; i < s1_length + 1; i++)
        if (tolower(s1[i]) != tolower(s2[i]))
            return false;
    
    return true;
}

bool string_case_insensitive_equal(const string *s1, const string *s2)
{
    if (s1->size != s2->size)
        return false;
    
    for (size_t i = 0; i < s1->size; i++)
        if (tolower(s1->c_str[i]) != tolower(s2->c_str[i]))
            return false;
    
    return true;
}

bool string_case_insensitive_equal_c_str(const string *s1, const char *s2)
{
    if (s1->size != strlen(s2) + 1)
        return false;
    
    for (size_t i = 0; i < s1->size; i++)
        if (tolower(s1->c_str[i]) != tolower(s2[i]))
            return false;
    
    return true;
}

bool string_has_prefix(const string *s, const string *prefix)
{
    if (prefix->size > s->size)
        return false;
    
    return strncmp(s->c_str, prefix->c_str, prefix->size - 1) == 0;
}

bool string_has_c_str_prefix(const string *s, const char *prefix)
{
    size_t prefix_length = strlen(prefix);
    size_t prefix_size = prefix_length + 1;
    
    if (prefix_size > s->size)
        return false;
    
    return strncmp(s->c_str, prefix, prefix_length) == 0;
}

bool string_has_prefix_by_case_insensitive_comparison(const string *s, const string *prefix)
{
    if (prefix->size > s->size)
        return false;
    
    for (size_t i = 0; i < prefix->size - 1; i++)
        if (tolower(s->c_str[i]) != tolower(prefix->c_str[i]))
            return false;
    
    return true;
}

bool string_has_c_str_prefix_by_case_insensitive_comparison(const string *s, const char *prefix)
{
    size_t prefix_length = strlen(prefix);
    size_t prefix_size = prefix_length + 1;
    
    if (prefix_size > s->size)
        return false;
    
    for (size_t i = 0; i < prefix_length; i++)
        if (tolower(s->c_str[i]) != tolower(prefix[i]))
            return false;
    
    return true;
}

bool string_has_suffix(const string *s, const string *suffix)
{
    if (suffix->size > s->size)
        return false;
    
    return strncmp(s->c_str + (s->size - suffix->size), suffix->c_str, suffix->size) == 0;
}

bool string_has_c_str_suffix(const string *s, const char *suffix)
{
    size_t suffix_length = strlen(suffix);
    size_t suffixSize = suffix_length + 1;
    
    if (suffixSize > s->size) {
        return false;
    }
    
    return strncmp(s->c_str + (s->size - suffixSize), suffix, suffix_length) == 0;
}

bool string_has_suffix_by_case_insensitive_comparison(const string *s, const string *suffix)
{
    if (suffix->size > s->size)
        return false;
    
    size_t offset = s->size - suffix->size;
    for (size_t i = 0; i < suffix->size; i++) {
        if (tolower(s->c_str[offset + i]) != tolower(suffix->c_str[i]))
            return false;
    }
    
    return true;
}

bool string_has_c_str_suffix_by_case_insensitive_comparison(const string *s, const char *suffix)
{
    size_t suffixLength = strlen(suffix);
    size_t suffixSize = suffixLength + 1;
    
    if (suffixSize > s->size)
        return false;
    
    size_t offset = s->size - suffixSize;
    for (size_t i = 0; i < suffixSize; i++) {
        if (tolower(s->c_str[offset + i]) != tolower(suffix[i]))
            return false;
    }
    
    return true;
}

char *string_begin(string *s)
{
    return s->c_str;
}

char *string_end(string *s)
{
    return s->c_str + s->size - 1;
}
