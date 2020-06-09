cmake_minimum_required(VERSION 3.14)
project(wolf3d C)
set(CMAKE_C_STANDARD 99)

find_library(SDL_LIB SDL2
        PATHS
        libs/SDL2/VisualC/Win32/Debug)
#find_library(FT_LIB libft
#        PATHS
#        libs/libft)


include_directories(incs)
add_subdirectory(libs/libft)
add_subdirectory(libs/SDL2)

target_link_directories(wolf3d libs/libft libs/SDL2)
target_link_libraries(wolf3d SDL2 libft)
target_link_directories(test_level libs/libft)
target_link_libraries(test_level libft)
# link_libraries(${SDL_LIB})

# link_libraries(../libs/libft/libft.lib ../libs/SDL2/VisualC/Win32/Debug/SDL2.lib)
message(VERBOSE, ${SDL_LIB})
message(VERBOSE, ${FT_LIB})

add_executable(test_level test.c incs/wolf3d.h srcs/level.c)
add_executable(wolf3d srcs/main.c incs/wolf3d.h srcs/level.c)