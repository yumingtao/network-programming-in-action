cmake_minimum_required(VERSION 3.16)
project(network_programming_c C)

set(CMAKE_C_STANDARD 99)

add_executable(network_programming_c main.c)

add_subdirectory(lib/)
add_subdirectory(ch-04/)
add_subdirectory(ch-05/)
add_subdirectory(ch-06/)