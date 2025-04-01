cmake_minimum_required(VERSION 3.30)
project(terragen)

set(CMAKE_CXX_STANDARD 23)
find_package(raylib)
find_package(FastNoise2)

add_executable(terragen main.cpp)

target_link_libraries(terragen raylib FastNoise2::FastNoise)
