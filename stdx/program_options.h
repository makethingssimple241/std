//
//  program_options.h
//  test
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#ifndef stdx_program_options_h
#define stdx_program_options_h

#include <std/string.h>
#include <std/unordered_map.h>
#include <std/vector.h>

#include <stdio.h>

typedef enum {
    program_option_type_flag,
    /// @note Value options are provided in the forms @c long_key value @c or @c short_key value @c
    program_option_type_value
} program_option_type;

typedef struct {
    program_option_type type;
    /// @note Keys either have the form @c long_key,short_key @c or @c key @c
    const char *key;
    bool required;
    const char *description;
} program_option;

/// @note Pointer to argv elements within result is a weak reference into argv.
/// The caller must guarantee that those argv elements are availible in the retrival from result.
typedef struct {
    vector *options;
    /// @brief unordered_map from @c const char * @c to @c const char * @c
    /// @note Values of @c program_option_type_flag @c will be @c 1 @c
    unordered_map *result;
} command_line_parser;

command_line_parser *new_command_line_parser(void);
void delete_command_line_parser(command_line_parser *parser);

void command_line_parser_add_options(command_line_parser *parser, program_option *options, size_t count);
void command_line_parser_describe_options(command_line_parser *parser, FILE *stream);
void command_line_parser_parse(command_line_parser *parser, int argc, const char **argv);

#define command_line_parser_error EINVAL

#endif /* stdx_program_options_h */
