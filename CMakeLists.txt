cmake_minimum_required(VERSION 3.14)
project(wolf3d C)

set(CMAKE_C_STANDARD 99)
include_directories("incs")
find_library(SDL_LIB SDL2
        PATHS
        libs/SDL2/VisualC/Win32/Debug)
find_library(FT_LIB libft
        PATHS
        libs/libft)

include_directories(incs)
add_subdirectory(libs/libft)
add_subdirectory(libs/SDL2)
link_directories(libs/libft libs/SDL2/VisualC/Win32/Debug/SDL2.dll)
link_libraries(${SDL_LIB} ${FT_LIB})

message(VERBOSE, ${SDL_LIB})
message(VERBOSE, ${FT_LIB})

add_executable(wolf3d srcs/main.c incs/wolf3d.h srcs/level.c)