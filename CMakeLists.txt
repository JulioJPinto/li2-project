cmake_minimum_required(VERSION 3.16)
project(_0M C)

set(CMAKE_C_STANDARD 11)

add_executable(_0M code/main.c code/stack.h code/stack.c code/operations.c code/operations.h code/logger.h code/conversions.c code/conversions.h code/logica.c code/logica.h code/operations_storage.c code/operations_storage.h code/variable_operations.c code/variable_operations.h code/string_operations.c code/string_operations.h code/parser.c code/parser.h code/array_operations.c code/array_operations.h code/polymorphic_operations.c code/polymorphic_operations.h code/block_operations.c code/block_operations.h)
target_link_libraries(_0M m)

if (DEBUG_MODE)
    add_definitions(-DDEBUG_MODE=1)
endif (DEBUG_MODE)

add_definitions(
        -Wall
        -Wextra
        -pedantic
        -Werror
        -pedantic-errors
        -Wconversion
        -Wimplicit-fallthrough
        -Wuninitialized
        -Wsign-conversion
        -Wundef
        -Wshadow
        -Wpointer-arith
        -Wwrite-strings
        -Wswitch-default
        -Wswitch-enum
        -Wunreachable-code
)
