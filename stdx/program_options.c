//
//  program_options.c
//  test
//
//  Created by MakeThingsSimple on 8/6/2024.
//

#include "program_options.h"

#include <std/exception.h>
#include <std/format.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

command_line_parser *new_command_line_parser(void)
{
    command_line_parser *parser = malloc(sizeof(command_line_parser));
    if (!parser)
        throw(system_error(errno, strerror(errno)));
    
    parser->options = new_vector(program_option);
    parser->result = new_unordered_map(hash_string);
    return parser;
}

void delete_command_line_parser(command_line_parser *parser)
{
    delete_unordered_map(parser->result);
    delete_vector(parser->options);
    free(parser);
}

void command_line_parser_add_options(command_line_parser *parser, program_option *options, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        vector_push_back(parser->options, &options[i]);
    }
}

void command_line_parser_describe_options(command_line_parser *parser, FILE *stream)
{
    vector *key_lengths = new_vector(size_t);
    vector_reserve(key_lengths, parser->options->size);
    size_t max_key_and_requirements_length = 0;

    for (size_t i = 0; i < parser->options->size; i++) {
        program_option *option = vector_at(parser->options, i);
        size_t length = strlen(option->key);
        if (length > max_key_and_requirements_length)
            max_key_and_requirements_length = length;

        vector_push_back(key_lengths, &length);
    }

    for (size_t i = 0; i < parser->options->size; i++) {
        program_option *option = vector_at(parser->options, i);
        size_t *length = vector_at(key_lengths, i);
        fprintf(stream, "  %s", option->key);

        for (size_t spaces_to_be_printed = 0; spaces_to_be_printed < max_key_and_requirements_length - *length; spaces_to_be_printed++)
            fputc(' ', stream);

        fprintf(stream, "    %s%s\n", option->description, option->required ? " (required)" : "");
    }

    delete_vector(key_lengths);
}

void command_line_parser_parse(command_line_parser *parser, int argc, const char **argv)
{
    for (size_t arg_index = 1; arg_index < argc; arg_index++) {
        for (size_t opt_index = 0; opt_index < parser->options->size; opt_index++) {
            program_option *option = vector_at(parser->options, opt_index);
            string *key = new_string_from_c_str(option->key);
            
            char *long_key = key->c_str;
            char *short_key = null;
            if ((short_key = strchr(key->c_str, ','))) {
                *short_key = '\0';
                short_key++; // make short key point to character after ','
                
                if (*short_key == '\0') {
                    delete_string(key);
                    throw(new_exceptionx(command_line_parser_error, "Expected short key after ','"));
                }
            }
            
            bool used_long_key = strcmp(argv[arg_index], long_key) == 0;
            bool used_short_key = short_key && strcmp(argv[arg_index], short_key) == 0;
            
            if (used_long_key || used_short_key) {
                switch (option->type) {
                case program_option_type_flag:
                    unordered_map_insert(parser->result, (uintptr_t)long_key, 1);
                    break;
                case program_option_type_value: {
                    if (++arg_index >= argc) {
                        // TODO: Memory of what will not be freed, allocate from arena
                        string *what = format("Expected value after value argument '%s'", key->c_str);
                        delete_string(key);
                        throw(new_exceptionx(command_line_parser_error, what->c_str));
                    }
                    
                    unordered_map_insert(parser->result, (uintptr_t)long_key, argv[arg_index]);
                } break;
                }
                
                break;
            }
        }
    }
}
