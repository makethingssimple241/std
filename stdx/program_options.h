//
//  program_options.h
//  test
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#ifndef stdx_program_options_h
#define stdx_program_options_h

#include <stdbool.h>

#include <std/string.h>
#include <std/unordered_map.h>
#include <std/vector.h>

typedef enum {
    program_option_type_flag,
    program_option_type_value
} program_option_type;

typedef struct {
    program_option_type type;
    const char *key;
    bool required;
} program_option;

/// @note Pointer to argv elements within result is a weak reference into argv.
/// The caller must guarantee that those argv elements are availible in the retrival from result.
typedef struct {
    vector *options;
    unordered_map *result;
} command_line_parser;

command_line_parser *new_command_line_parser(void);
void delete_command_line_parser(command_line_parser *parser);

void command_line_parser_add_options(command_line_parser *parser, program_option *options, size_t count);
void command_line_parser_parse(command_line_parser *parser, int argc, const char **argv);

#define command_line_parser_error EINVAL

#endif /* stdx_program_options_h */
