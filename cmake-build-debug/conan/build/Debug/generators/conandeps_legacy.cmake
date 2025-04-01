message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(FastNoise2)
find_package(raylib)

set(CONANDEPS_LEGACY  FastNoise2::FastNoise  raylib )