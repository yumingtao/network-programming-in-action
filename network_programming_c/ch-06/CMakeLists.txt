cmake_minimum_required(VERSION 3.16)
project(ch-06 C)

set(CMAKE_C_STANDARD 99)

add_executable(udp_server udp_server.c)
#target_link_libraries(udp_server ymtlib)

add_executable(udp_client udp_client.c)
target_link_libraries(udp_client ymtlib)