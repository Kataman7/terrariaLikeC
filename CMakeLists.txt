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
        block.c
        structure.c
        includes/structure.h
        player.c
        includes/player.h
        includes/entity.h
        entity.c
        includes/slime.h
        slime.c)

include_directories(C:\\raylib\\raylib\\src)
target_link_libraries(TerrariaLike C:\\raylib\\raylib\\src\\libraylib.a)
target_link_libraries(TerrariaLike winmm.lib)

file(GLOB IMAGES "texture/*.png")

add_custom_command(TARGET TerrariaLike POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:TerrariaLike>/texture
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${IMAGES} $<TARGET_FILE_DIR:TerrariaLike>/texture
)
