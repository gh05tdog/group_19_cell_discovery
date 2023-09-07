cmake_minimum_required(VERSION 3.26)
project(group_19_cell_discovery C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(group_19_cell_discovery
        cbmp.h
        main.c
        cbmp.c
        src/erode.c
        src/erode.h
)
