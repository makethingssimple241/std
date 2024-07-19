# TODO: build system
clang -o build/libstd.dylib std/*.c stdx/*.c -I . -dynamiclib -fPIC -g -fsanitize=address
clang -o build/test tests/*.c -I . -L build/ -lstd -g -fsanitize=address
