cmake_minimum_required(VERSION 3.26)
project(C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c
        ordered_set.h
        bit_set.h
        main.c
        array.h
        unordered_set.h
)
