cmake_minimum_required(VERSION 4.3)
project(PracticaSorting)

set(CMAKE_CXX_STANDARD 17)

add_executable(PracticaSorting main.cpp
        sorting/quick_sort.cpp
        sorting/heap_sort.cpp
        structures/avl_tree.cpp)

add_executable(Convertidor tools/convertir_utf8.cpp)