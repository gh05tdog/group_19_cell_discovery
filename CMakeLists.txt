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
        src/cell_check.c
        src/cell_check.h
        src/global_vars.h
        src/add_squares.c
        src/add_squares.h
        src/convert_to_binary.c
        src/convert_to_binary.h
        src/cluster_find.c
        src/cluster_find.h
)
