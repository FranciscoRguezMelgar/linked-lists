cmake_minimum_required(VERSION 3.28)
project(linked_list C)
set (CMAKE_C_STANDARD 23)
add_compile_options(-Wall -Werror -Wpedantic -Wextra)
# Not necessary for compiling, necessary for clangd to pick it up
add_definitions(-Dnullptr=NULL)
add_subdirectory(src)