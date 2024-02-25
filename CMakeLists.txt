cmake_minimum_required(VERSION 3.26)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c
        libs/ordered_set.h
        libs/bit_set.h
        main.c
        libs/array.h
        libs/unordered_set.h
        libs/vector.h
)
