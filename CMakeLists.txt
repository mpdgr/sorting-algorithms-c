cmake_minimum_required(VERSION 3.31)
project(c_sort C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_RELEASE "-O3 -march=native -ffast-math")

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(c_sort
        src/main.c
        src/sorting/bubble_sort/bubble_sort.c
        src/sorting/heap_sort/heap_sort.c
        src/sorting/insertion_sort/insertion_sort.c
        src/sorting/merge_sort/merge_sort.c
        src/sorting/quick_sort/quick_sort.c
        src/sorting/radix_sort/radix_sort.c
        src/sorting/tim_sort/tim_sort.c)

