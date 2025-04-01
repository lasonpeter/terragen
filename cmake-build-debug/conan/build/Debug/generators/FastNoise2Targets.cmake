# Load the debug and release variables
file(GLOB DATA_FILES "${CMAKE_CURRENT_LIST_DIR}/FastNoise2-*-data.cmake")

foreach(f ${DATA_FILES})
    include(${f})
endforeach()

# Create the targets for all the components
foreach(_COMPONENT ${fastnoise2_COMPONENT_NAMES} )
    if(NOT TARGET ${_COMPONENT})
        add_library(${_COMPONENT} INTERFACE IMPORTED)
        message(${FastNoise2_MESSAGE_MODE} "Conan: Component target declared '${_COMPONENT}'")
    endif()
endforeach()

if(NOT TARGET FastNoise2::FastNoise)
    add_library(FastNoise2::FastNoise INTERFACE IMPORTED)
    message(${FastNoise2_MESSAGE_MODE} "Conan: Target declared 'FastNoise2::FastNoise'")
endif()
# Load the debug and release library finders
file(GLOB CONFIG_FILES "${CMAKE_CURRENT_LIST_DIR}/FastNoise2-Target-*.cmake")

foreach(f ${CONFIG_FILES})
    include(${f})
endforeach()