cmake_minimum_required(VERSION 3.30)
project(terragen)

set(CMAKE_CXX_STANDARD 23)
find_package(raylib REQUIRED)
find_package(FastNoise2 REQUIRED)
find_package(protobuf REQUIRED)
find_package(asio REQUIRED)

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
        procedural/ChunkGovernor.cpp
        procedural/ChunkGovernor.h
        rendering/chunks/ChunkRenderer.cpp
        rendering/chunks/ChunkRenderer.h
        procedural/terrain/TerrainImage.cpp
        procedural/terrain/TerrainImage.h
        Netcode/ProtoClient.cpp
        Netcode/ProtoClient.h
        Netcode/generated/EnvelopeModel.pb.cc
        Netcode/generated/LoginModel.pb.cc
        Netcode/generated/ChunkTransmitModel.pb.cc
        Netcode/generated/BlockUpdateBroadcastModel.pb.cc
        Netcode/generated/BlockUpdateModel.pb.cc
        Netcode/generated/LoginRespondModel.pb.cc
        Netcode/generated/PositionUpdateBroadcastModel.pb.cc
        Netcode/generated/PositionUpdateModel.pb.cc
        utilities/ChunkCache.cpp
        utilities/ChunkCache.h
        ECBS/GameObject.h
        physics/PhysiscsGovernor.cpp
        physics/PhysiscsGovernor.h
        scripts/Player.cpp
        scripts/Player.h
        ECBS/Component.h
        ECBS/components/RigidBody.h
        utilities/UUID.h
        utilities/UUID.cpp
        ECBS/GameObjectGovernor.cpp
        ECBS/GameObjectGovernor.h
        utilities/ChunkFaceMaskGenerator.h
        ECBS/components/Collider.h
        physics/ChunkCollisionManager.cpp
        Netcode/Netcode.cpp
        Netcode/Netcode.h
)

target_link_libraries(terragen raylib FastNoise2::FastNoise protobuf::libprotobuf asio::asio ws2_32)

target_compile_definitions(terragen PRIVATE FASTNOISE_STATIC_LIB)