﻿cmake_minimum_required(VERSION 3.30)
project(terragen)

set(CMAKE_CXX_STANDARD 23)
find_package(raylib REQUIRED)
find_package(FastNoise2 REQUIRED)

#for raygui
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include_directories(${CMAKE_SOURCE_DIR}/include)
    #link_directories(${CMAKE_SOURCE_DIR}/lib)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    include_directories(${CMAKE_SOURCE_DIR}/include)
    #link_directories(${CMAKE_SOURCE_DIR}/lib)
endif ()
add_executable(terragen main.cpp
        procedural/terrain/BiomeGeneration.cpp
        procedural/terrain/BiomeGeneration.h
        procedural/terrain/BiomeType.h
        procedural/terrain/generators/plains/Plains.cpp
        procedural/terrain/generators/plains/Plains.h
        procedural/terrain/generators/TerrainGenerator.h
        rendering/StaticRenderer.cpp
        rendering/StaticRenderer.h
        procedural/Block.cpp
        procedural/Block.h
        procedural/BlockType.h
        utilities/FaceMask.h
        utilities/Mathf.h
        procedural/Chunk.cpp
        procedural/Chunk.h
)

target_link_libraries(terragen raylib FastNoise2::FastNoise)
