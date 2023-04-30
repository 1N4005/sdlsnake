project(sdlsnake)

cmake_minimum_required(VERSION 3.23)

set(CXX_STANDARD C++17)
set(CMAKE_BUILD_TYPE Release)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_library(snake src/snake.cpp)

add_executable(sdlsnake src/main.cpp)
target_link_libraries(sdlsnake snake)
target_link_libraries(sdlsnake ${SDL2_LIBRARIES})