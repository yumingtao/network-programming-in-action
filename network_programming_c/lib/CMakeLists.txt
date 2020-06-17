cmake_minimum_required(VERSION 3.16)
project(lib C)
set(ymt_lib
        common.c
        )


add_library(ymtlib ${ymt_lib})
install(TARGETS ymtlib DESTINATION lib)