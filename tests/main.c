//
//  main.c
//  test
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include <std/cstddef.h>
#include <std/exception.h>
#include <std/filesystem.h>
#include <std/format.h>
#include <std/fstream.h>
#include <std/stdexcept.h>
#include <std/unordered_map.h>

#define STDX_ENABLE_ASSERT_HANDLER
#include <stdx/assert.h>
#include <stdx/program_options.h>

#include <string.h>

void print_element(string *s) {
    printf("%s\n", s->c_str);
}

int main(int argc, const char **argv) {
    printf("*** std/exception.h, std/fstream.h and std/stdexcept.h tests ***\n");
    {
        bool exception_rethrowed = false;
        const char* exception_what = NULL;
        
        try {
            try {
                {
                    fstream_open("test.txt", FSTREAM_OPEN_MODE_READ);
                }
            }
            catchall {
                exception_rethrowed = true;
                rethrow;
            }
        } catchall {
            exception_what = exception.what;
        }
        
        STDX_ASSERT(c_str_equal(strerror(ENOENT), exception_what));
        STDX_ASSERT(exception_rethrowed);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/filesystem.h, std/string.h and stdx/assert.h ***\n");
    {
        try {
            filesystem_path *path = new_string_from_c_str("hello.txt");
            filesystem_path *root_name = filesystem_path_root_name(path);
            filesystem_path *extension = filesystem_path_extension(path);
            
            STDX_ASSERT(string_empty(root_name));
            STDX_ASSERT(string_equal_c_str(extension, "txt"));
            
            delete_filesystem_path(path);
            delete_filesystem_path(root_name);
            delete_filesystem_path(extension);
        } catchall {
            
        }
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/format.h, std/string.h and stdx/assert.h tests ***\n");
    {
        string *hello_world = new_string_from_c_str("Hello");
        string_append(hello_world, ',');
        string_append(hello_world, ' ');
        
        string_concatenate_with_c_str(hello_world, "World");
        string_append(hello_world, '!');
        
        STDX_ASSERT(string_equal_c_str(hello_world, "Hello, World!"));
        STDX_ASSERT(string_case_insensitive_equal_c_str(hello_world, "HELLO, WORLD!"));
        STDX_ASSERT(string_has_c_str_prefix(hello_world, "Hello"));
        STDX_ASSERT(string_has_c_str_prefix_by_case_insensitive_comparison(hello_world, "HELLO"));
        STDX_ASSERT(string_has_c_str_suffix(hello_world, "World!"));
        STDX_ASSERT(string_has_c_str_suffix_by_case_insensitive_comparison(hello_world, "WORLD!"));
        
        string_remove_first(hello_world);
        STDX_ASSERT(string_equal_c_str(hello_world, "ello, World!"));
        
        string_remove_first_n(hello_world, 6);
        STDX_ASSERT(string_equal_c_str(hello_world, "World!"));
        
        string_remove_last(hello_world);
        STDX_ASSERT(string_equal_c_str(hello_world, "World"));
        
        string_remove_last_n(hello_world, 5);
        STDX_ASSERT(string_empty(hello_world));
        
        delete_string(hello_world);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/format.h, std/string.h and stdx/assert.h tests ***\n");
    {
        void *object = (void *)0x12345678;
        string *formatted = format("<object: %p>", object);
        STDX_ASSERT(string_equal_c_str(formatted, "<object: 0x12345678>"));
        delete_string(formatted);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/string.h, std/vector.h and stdx/assert.h tests ***\n");
    {
        vector *vec = new_vector(string);
        string *a = new_string_from_c_str("A");
        string *b = new_string_from_c_str("B");
        
        vector_push_back(vec, b);
        vector_push_back(vec, a);
        vector_push_back(vec, b);
        vector_insert(vec, a, 0);
        STDX_ASSERT(vec->size == 4);
        vector_for_each(vec, print_element);
        
        bool out_of_range_happened = false;
        try {
            vector_at(vec, 4);
        } catch (out_of_range) {
            out_of_range_happened = true;
        }
        STDX_ASSERT(out_of_range_happened);
        
        string *result = new_string();
        for (string *it = vector_begin(vec); it != vector_end(vec); vector_next(vec, &it)) {
            string_concatenate(result, it);
        }
        STDX_ASSERT(string_equal_c_str(result, "ABAB"));
        
        delete_string(a);
        delete_string(b);
        delete_string(result);
        delete_vector(vec);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/string.h, std/unordered_map.h and stdx/assert.h tests ***\n");
    {
        unordered_map *map = new_unordered_map(hash_string);
        
        string *a = new_string_from_c_str("A");
        string *b = new_string_from_c_str("B");
        
        unordered_map_insert(map, "A", a);
        unordered_map_insert(map, "B", b);
        
        string *result = new_string();
        
        STDX_ASSERT(unordered_map_begin(map) != unordered_map_end(map));
        
        for (unordered_map_value_type *it = unordered_map_begin(map);
             it != unordered_map_end(map);
             unordered_map_next(map, &it))
            string_concatenate(result, it->value);
        
        STDX_ASSERT(string_equal_c_str(result, "AB"));
        
        delete_unordered_map(map);
        delete_string(a);
        delete_string(b);
        delete_string(result);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/unordered_map.h, stdx/assert.h and stdx/program_options.h tests ***\n");
    {
        program_option options[] = {
            {program_option_type_flag, "verbose,v", .required=false},
            {program_option_type_value, "username", .required=true}
        };
        
        command_line_parser *parser = new_command_line_parser();
        command_line_parser_add_options(parser, options, len(options));
        command_line_parser_parse(parser, argc, argv);
        
        STDX_ASSERT(unordered_map_contains(parser->result, "verbose"));
        
        string *username = (string *)unordered_map_at(parser->result, (uintptr_t)"username");
        STDX_ASSERT(string_equal_c_str(username, "makethingssimple"));
        
        delete_command_line_parser(parser);
    }
    printf("*** tests completed ***\n\n");
}
