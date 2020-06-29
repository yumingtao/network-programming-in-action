cmake_minimum_required(VERSION 3.16)
project(ch-07 C)

set(CMAKE_C_STANDARD 99)

add_executable(local_stream_server local_stream_server.c)
target_link_libraries(local_stream_server ymtlib)

add_executable(local_stream_client local_stream_client.c)
target_link_libraries(local_stream_client ymtlib)

add_executable(local_data_server local_data_server.c)
target_link_libraries(local_data_server ymtlib)

add_executable(local_data_client local_data_client.c)
target_link_libraries(local_data_client ymtlib)