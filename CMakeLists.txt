cmake_minimum_required(VERSION 3.15)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)
include_directories("incs")
find_library(SDL_LIB SDL2
        PATHS
        SDL/lib)
find_library(FT_LIB ft
        PATHS
        libs/libft)
link_libraries(${SDL_LIB} ${FT_LIB})

add_executable(wolf3d srcs/main.c incs/wolf3d.h srcs/level.c)