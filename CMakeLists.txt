cmake_minimum_required(VERSION 3.28)
project(terrariaLikeC C)
set(CMAKE_C_STANDARD 11)

add_executable(TerrariaLike
        main.c
        chunk.c
        chunk.h)

include_directories(C:\\raylib\\raylib\\src)
target_link_libraries(TerrariaLike C:\\raylib\\raylib\\src\\libraylib.a)
target_link_libraries(TerrariaLike winmm.lib)