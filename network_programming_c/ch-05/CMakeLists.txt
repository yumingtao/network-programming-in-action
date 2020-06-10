cmake_minimum_required(VERSION 3.16)
project(ch-05 C)

set(CMAKE_C_STANDARD 99)

add_executable(tcp_server tcp_server.c)
add_executable(tcp_client tcp_client.c)