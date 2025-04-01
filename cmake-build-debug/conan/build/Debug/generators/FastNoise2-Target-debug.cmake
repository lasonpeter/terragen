# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(fastnoise2_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(fastnoise2_FRAMEWORKS_FOUND_DEBUG "${fastnoise2_FRAMEWORKS_DEBUG}" "${fastnoise2_FRAMEWORK_DIRS_DEBUG}")

set(fastnoise2_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET fastnoise2_DEPS_TARGET)
    add_library(fastnoise2_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET fastnoise2_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${fastnoise2_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${fastnoise2_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### fastnoise2_DEPS_TARGET to all of them
conan_package_library_targets("${fastnoise2_LIBS_DEBUG}"    # libraries
                              "${fastnoise2_LIB_DIRS_DEBUG}" # package_libdir
                              "${fastnoise2_BIN_DIRS_DEBUG}" # package_bindir
                              "${fastnoise2_LIBRARY_TYPE_DEBUG}"
                              "${fastnoise2_IS_HOST_WINDOWS_DEBUG}"
                              fastnoise2_DEPS_TARGET
                              fastnoise2_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "fastnoise2"    # package_name
                              "${fastnoise2_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${fastnoise2_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${fastnoise2_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${fastnoise2_LIBRARIES_TARGETS}>
                 )

    if("${fastnoise2_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET FastNoise2::FastNoise
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     fastnoise2_DEPS_TARGET)
    endif()

    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${fastnoise2_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${fastnoise2_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${fastnoise2_LIB_DIRS_DEBUG}>)
    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${fastnoise2_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET FastNoise2::FastNoise
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${fastnoise2_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(fastnoise2_LIBRARIES_DEBUG FastNoise2::FastNoise)
