cmake_minimum_required(VERSION 3.28)
project(terrariaLikeC C)
set(CMAKE_C_STANDARD 11)

add_executable(TerrariaLike
        main.c
        chunk.c
        includes/chunk.h
        land.c
        includes/land.h
        includes/block.h
        cave.c
        includes/cave.h
        block.c)

include_directories(C:\\raylib\\raylib\\src)
target_link_libraries(TerrariaLike C:\\raylib\\raylib\\src\\libraylib.a)
target_link_libraries(TerrariaLike winmm.lib)