//
//  main.c
//  test
//
//  Created by MakeThingsSimple on 26/4/2024.
//

#include <std/allocator.h>
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
            filesystem_path path = new_string_from_c_str("hello.txt");
            filesystem_path root_name = filesystem_path_root_name(&path);
            filesystem_path extension = filesystem_path_extension(&path);
            
            STDX_ASSERT(string_empty(&root_name));
            STDX_ASSERT(string_equal_c_str(&extension, "txt"));
            
            delete_filesystem_path(&path);
            delete_filesystem_path(&root_name);
            delete_filesystem_path(&extension);
        } catchall {
            
        }
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/format.h, std/string.h and stdx/assert.h tests ***\n");
    {
        string hello_world = new_string_from_c_str("Hello");
        string_append(&hello_world, ',');
        string_append(&hello_world, ' ');
        
        string_concatenate_with_c_str(&hello_world, "World");
        string_append(&hello_world, '!');
        
        STDX_ASSERT(string_equal_c_str(&hello_world, "Hello, World!"));
        STDX_ASSERT(string_case_insensitive_equal_c_str(&hello_world, "HELLO, WORLD!"));
        STDX_ASSERT(string_has_c_str_prefix(&hello_world, "Hello"));
        STDX_ASSERT(string_has_c_str_prefix_by_case_insensitive_comparison(&hello_world, "HELLO"));
        STDX_ASSERT(string_has_c_str_suffix(&hello_world, "World!"));
        STDX_ASSERT(string_has_c_str_suffix_by_case_insensitive_comparison(&hello_world, "WORLD!"));
        
        string_remove_first(&hello_world);
        STDX_ASSERT(string_equal_c_str(&hello_world, "ello, World!"));
        
        string_remove_first_n(&hello_world, 6);
        STDX_ASSERT(string_equal_c_str(&hello_world, "World!"));
        
        string_remove_last(&hello_world);
        STDX_ASSERT(string_equal_c_str(&hello_world, "World"));
        
        string_remove_last_n(&hello_world, 5);
        STDX_ASSERT(string_empty(&hello_world));
        
        delete_string(&hello_world);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/format.h, std/string.h and stdx/assert.h tests ***\n");
    {
        void *object = (void *)0x12345678;
        string formatted = format("<object: %p>", object);
        STDX_ASSERT(string_equal_c_str(&formatted, "<object: 0x12345678>"));
        delete_string(&formatted);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/string.h, std/vector.h and stdx/assert.h tests ***\n");
    {
        vector vec = new_vector(string);
        string a = new_string_from_c_str("A");
        string b = new_string_from_c_str("B");
        
        vector_push_back(&vec, &b);
        vector_push_back(&vec, &a);
        vector_push_back(&vec, &b);
        vector_insert(&vec, &a, 0);
        STDX_ASSERT(vec.size == 4);
        
        bool out_of_range_happened = false;
        try {
            vector_at(&vec, 4);
        } catch (out_of_range) {
            out_of_range_happened = true;
        }
        STDX_ASSERT(out_of_range_happened);
        
        string result = new_string();
        for (string *it = vector_begin(&vec); it != vector_end(&vec); vector_next(&vec, &it)) {
            string_concatenate(&result, it);
        }
        STDX_ASSERT(string_equal_c_str(&result, "ABAB"));
        
        delete_string(&a);
        delete_string(&b);
        delete_string(&result);
        delete_vector(&vec);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/string.h, std/unordered_map.h and stdx/assert.h tests ***\n");
    {
        unordered_map *map = new_unordered_map(uintptr_t, string, ptr_to_uintptr_t_equal, hash_uintptr_t);
        
        string a = new_string_from_c_str("A");

        for (size_t i = 0; i < 20; i++) {
            unordered_map_insert(map, &i, &a);
        }
        
        string result = new_string();
        
        STDX_ASSERT(unordered_map_begin(map) != unordered_map_end(map));
        
        for (unordered_map_value_type *it = unordered_map_begin(map);
             it != unordered_map_end(map);
             unordered_map_next(map, &it))
            string_concatenate(&result, it->value);
        
        STDX_ASSERT(string_equal_c_str(&result, "AAAAAAAAAAAAAAAAAAAA"));
        
        delete_unordered_map(map);
        delete_string(&a);
        delete_string(&result);

        unordered_map *empty_map = new_unordered_map(const char *, const char *, ptr_to_c_str_equal, hash_c_str);
        for (unordered_map_value_type *it = unordered_map_begin(empty_map);
             it != unordered_map_end(empty_map);
             unordered_map_next(empty_map, &it));
        delete_unordered_map(empty_map);
    }
    printf("*** tests completed ***\n\n");
    
    printf("*** std/unordered_map.h, stdx/assert.h and stdx/program_options.h tests ***\n");
    {
        printf("Usage: %s <options>\nOptions:\n", argv[0]);

        program_option options[] = {
            {program_option_type_flag, "verbose,v", .required=false, "Enable verbose output"},
            {program_option_type_value, "username", .required=true, "Your username"}
        };
        
        command_line_parser *parser = new_command_line_parser();
        command_line_parser_add_options(parser, options, len(options));
        command_line_parser_describe_options(parser, stdout);
        command_line_parser_parse(parser, argc, argv);
        
        const char *verbose_key = "verbose";
        STDX_ASSERT(unordered_map_contains(parser->result, &verbose_key));
        
        const char *username_key = "username";
        const char **username = unordered_map_at(parser->result, &username_key);
        STDX_ASSERT(c_str_equal(*username, "makethingssimple"));
        
        delete_command_line_parser(parser);
    }
    printf("*** tests completed ***\n\n");
}
