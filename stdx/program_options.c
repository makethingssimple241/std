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
#include <string.h>
#include <stdio.h>

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
    for (size_t i = 0; i < parser->result->storage_capacity; i++) {
        unordered_map_value_type *entry = &parser->result->storage[i];
        string *value = entry->value;
        
        if (value)
            delete_string(value);
    }
    
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

void command_line_parser_parse(command_line_parser *parser, int argc, const char **argv)
{
    for (size_t arg_index = 1; arg_index < argc; arg_index++) {
        for (size_t opt_index = 0; opt_index < parser->options->size; opt_index++) {
            program_option *option = vector_at(parser->options, opt_index);
            string *key = new_string_from_c_str(option->key);
            
            char *long_key = key->c_str;
            char *short_key;
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
                    unordered_map_insert(parser->result, (uintptr_t)long_key, 0);
                    break;
                case program_option_type_value: {
                    if (++arg_index >= argc) {
                        // TODO: Memory of what will not be freed, allocate from arena
                        string *what = format("Expected value after value argument '%s'", key->c_str);
                        delete_string(key);
                        throw(new_exceptionx(command_line_parser_error, what->c_str));
                    }
                    
                    string *value = new_string_from_c_str(argv[arg_index]);
                    unordered_map_insert(parser->result, (uintptr_t)long_key, value);
                } break;
                }
                
                break;
            }
        }
    }
}
