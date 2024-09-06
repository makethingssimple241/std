//
//  string.h
//  std
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#ifndef std_string_h
#define std_string_h

#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    /// @brief The null-terminated C string of the `string`
    char *c_str;
    /// @brief Size of `c_str` not including the null-termination character
    size_t size;
    /// @note This is a private member that should not be used by the user
    bool owns_c_str;
} string;

/// @brief Creates an empty string
string *new_string(void);
string *new_string_from_c_str(const char *c_str);
string *new_string_from_c_str_without_copy(char *c_str);
string *new_string_from_c_str_view(const char *c_str, size_t length);
string *new_string_from_c_str_view_without_copy(char *c_str, size_t length);
string *copy_string(const string *s);
void delete_string(string *s);

// MARK: Modifiers

void string_concatenate(string *s1, const string *s2);
void string_concatenate_with_c_str(string *s1, const char* s2);
void string_append(string *s, char c);

void string_remove_first(string *s);
void string_remove_first_n(string *s, size_t n);
void string_remove_last(string *s);
void string_remove_last_n(string *s, size_t n);

// MARK: Queries

bool c_str_empty(const char *s);
bool string_empty(const string *s);
bool c_str_equal(const char *s1, const char *s2);
bool string_equal(const string *s1, const string *s2);
bool string_equal_c_str(const string *s1, const char *s2);
bool string_case_insensitive_equal(const string *s1, const string *s2);
bool string_case_insensitive_equal_c_str(const string *s1, const char *s2);
bool string_has_prefix(const string *s, const string *prefix);
bool string_has_c_str_prefix(const string *s, const char *prefix);
bool string_has_prefix_by_case_insensitive_comparison(const string *s, const string *prefix);
bool string_has_c_str_prefix_by_case_insensitive_comparison(const string *s, const char *prefix);
bool string_has_suffix(const string *s, const string *suffix);
bool string_has_c_str_suffix(const string *s, const char *suffix);
bool string_has_suffix_by_case_insensitive_comparison(const string *s, const string *suffix);
bool string_has_c_str_suffix_by_case_insensitive_comparison(const string *s, const char *suffix);

// MARK: Iterators
/// @returns A pointer that points to the start of the C string of `s`
char *string_begin(string *s);
/// @returns A pointer that points to the null-termination character of `s`
char *string_end(string *s);

#endif /* std_string_h */
