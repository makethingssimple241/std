#  std

## Introduction

std provides C implementations of some classes and functions of the C++ standard library.

stdx provides C implementations of some classes and functions of the Boost C++ library.

> [!CAUTION]
> This library is in development.

## Modules

### std.cstddef

`std.cstddef` provides macro definitions for commonly used functions, such as Boolean data types and length of arrays.

### std.exception and std.stdexcept

`std.exception` adds error handling with exceptions to C.

`std.stdexcept` provides IDs for different exception types.

The exception handling frame is created by `setjmp`ing when the throwing function is called.
When the function `throw`s, it will `longjmp` to the `catch` block.
In the catch block, you can specify which exception type that block catches by `id`.
If a throwing function is called without being enclosed in a `try` block and the function `throw`s, `terminate` will be called.

> [!CAUTION]
> `std.exception` is an experimental module.

### std.filesystem

`std.filesystem` contains platform-agnostic filesystem utilities.

> [!CAUTION]
> `std.filesystem` is an incomplete module. It only support macOS at the moment and is not fully tested.

### std.format

`std.format` contains functions used to produce a `std.string` from a format string and format arguments.

### std.fstream

`std.fstream` contains a wrapper around `FILE *` and exception-throwing versions of `fopen`, `fclose`, etc.

### std.functional

`std.functional` contains utilities, such as hashing.

### std.string
`std.string` provides a size-included structure for a null-terminated string and functions around it.

### std.vector
`std.vector` provides a vector (dynamic array) and functions around it.

### stdx.assert
`stdx.program_options` provides assert macros that is similar to `Boost.Assert`.

### stdx.program_options
`stdx.program_options` provides types and functions for parsing command line arguments.

### stdx.test
`stdx.test` provides utilities for unit testing.

## Building and using `std` and `stdx`

### Building `std` and `stdx`

TODO: Add building instructions

> [!NOTE]
> `stdx` depends on `std`

> [!NOTE]
> `Enable Modules (C and Objective-C)` needs to be disabled when building a target that includes `std`.

### Using `std` and `stdx`

To use `std` and `stdx`, you include the used headers, and link with `std` when linking.
