########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(fastnoise2_COMPONENT_NAMES "")
if(DEFINED fastnoise2_FIND_DEPENDENCY_NAMES)
  list(APPEND fastnoise2_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES fastnoise2_FIND_DEPENDENCY_NAMES)
else()
  set(fastnoise2_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(fastnoise2_PACKAGE_FOLDER_DEBUG "C:/Users/xenu/.conan2/p/b/fastnb1f37146d7057/p")
set(fastnoise2_BUILD_MODULES_PATHS_DEBUG )


set(fastnoise2_INCLUDE_DIRS_DEBUG "${fastnoise2_PACKAGE_FOLDER_DEBUG}/include")
set(fastnoise2_RES_DIRS_DEBUG )
set(fastnoise2_DEFINITIONS_DEBUG )
set(fastnoise2_SHARED_LINK_FLAGS_DEBUG )
set(fastnoise2_EXE_LINK_FLAGS_DEBUG )
set(fastnoise2_OBJECTS_DEBUG )
set(fastnoise2_COMPILE_DEFINITIONS_DEBUG )
set(fastnoise2_COMPILE_OPTIONS_C_DEBUG )
set(fastnoise2_COMPILE_OPTIONS_CXX_DEBUG )
set(fastnoise2_LIB_DIRS_DEBUG "${fastnoise2_PACKAGE_FOLDER_DEBUG}/lib")
set(fastnoise2_BIN_DIRS_DEBUG )
set(fastnoise2_LIBRARY_TYPE_DEBUG STATIC)
set(fastnoise2_IS_HOST_WINDOWS_DEBUG 1)
set(fastnoise2_LIBS_DEBUG FastNoiseD)
set(fastnoise2_SYSTEM_LIBS_DEBUG )
set(fastnoise2_FRAMEWORK_DIRS_DEBUG )
set(fastnoise2_FRAMEWORKS_DEBUG )
set(fastnoise2_BUILD_DIRS_DEBUG )
set(fastnoise2_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(fastnoise2_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${fastnoise2_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${fastnoise2_COMPILE_OPTIONS_C_DEBUG}>")
set(fastnoise2_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${fastnoise2_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${fastnoise2_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${fastnoise2_EXE_LINK_FLAGS_DEBUG}>")


set(fastnoise2_COMPONENTS_DEBUG )