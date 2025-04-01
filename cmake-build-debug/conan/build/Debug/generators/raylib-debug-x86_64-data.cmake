########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(raylib_COMPONENT_NAMES "")
if(DEFINED raylib_FIND_DEPENDENCY_NAMES)
  list(APPEND raylib_FIND_DEPENDENCY_NAMES glfw3 opengl_system)
  list(REMOVE_DUPLICATES raylib_FIND_DEPENDENCY_NAMES)
else()
  set(raylib_FIND_DEPENDENCY_NAMES glfw3 opengl_system)
endif()
set(glfw3_FIND_MODE "NO_MODULE")
set(opengl_system_FIND_MODE "NO_MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(raylib_PACKAGE_FOLDER_DEBUG "C:/Users/xenu/.conan2/p/b/raylid1e5adc9dfade/p")
set(raylib_BUILD_MODULES_PATHS_DEBUG )


set(raylib_INCLUDE_DIRS_DEBUG "${raylib_PACKAGE_FOLDER_DEBUG}/include")
set(raylib_RES_DIRS_DEBUG )
set(raylib_DEFINITIONS_DEBUG )
set(raylib_SHARED_LINK_FLAGS_DEBUG )
set(raylib_EXE_LINK_FLAGS_DEBUG )
set(raylib_OBJECTS_DEBUG )
set(raylib_COMPILE_DEFINITIONS_DEBUG )
set(raylib_COMPILE_OPTIONS_C_DEBUG )
set(raylib_COMPILE_OPTIONS_CXX_DEBUG )
set(raylib_LIB_DIRS_DEBUG "${raylib_PACKAGE_FOLDER_DEBUG}/lib")
set(raylib_BIN_DIRS_DEBUG )
set(raylib_LIBRARY_TYPE_DEBUG STATIC)
set(raylib_IS_HOST_WINDOWS_DEBUG 1)
set(raylib_LIBS_DEBUG raylib)
set(raylib_SYSTEM_LIBS_DEBUG winmm)
set(raylib_FRAMEWORK_DIRS_DEBUG )
set(raylib_FRAMEWORKS_DEBUG )
set(raylib_BUILD_DIRS_DEBUG )
set(raylib_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(raylib_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${raylib_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${raylib_COMPILE_OPTIONS_C_DEBUG}>")
set(raylib_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${raylib_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${raylib_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${raylib_EXE_LINK_FLAGS_DEBUG}>")


set(raylib_COMPONENTS_DEBUG )