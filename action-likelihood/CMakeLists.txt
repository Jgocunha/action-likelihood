cmake_minimum_required(VERSION 3.15)

project (action-likelihood
    DESCRIPTION "Action likelihood algorithm."
	LANGUAGES CXX
)

# Define library version
set(ACTION_LIKELIHOOD_PROJ_VERSION_MAJOR 1 CACHE STRING "major version" FORCE)
set(ACTION_LIKELIHOOD_PROJ_VERSION_MINOR 0 CACHE STRING "minor version" FORCE)
set(ACTION_LIKELIHOOD_PROJ_VERSION ${ACTION_LIKELIHOOD_PROJ_VERSION_MAJOR}.${ACTION_LIKELIHOOD_PROJ_VERSION_MINOR} CACHE STRING "version" FORCE)

set(ACTION_LIKELIHOOD_PROJ_LIB_PREFIX "release")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ACTION_LIKELIHOOD_PROJ_LIB_PREFIX "debug")
endif()

set(ACTION_LIKELIHOOD_PROJ_INC_INSTALL_DIR "include")
set(ACTION_LIKELIHOOD_PROJ_RUNTIME_INSTALL_DIR "bin")
set(ACTION_LIKELIHOOD_PROJ_LIBRARY_INSTALL_DIR "bin")
set(ACTION_LIKELIHOOD_PROJ_ARCHIVE_INSTALL_DIR "lib")
set(ACTION_LIKELIHOOD_PROJ_FRAMEWORK_INSTALL_DIR "bin")
set(ACTION_LIKELIHOOD_PROJ_CMAKE_CONFIG_INSTALL_DIR "share/${CMAKE_PROJECT_NAME}/cmake")
set(ACTION_LIKELIHOOD_PROJ_ADDITIONAL_FILES_INSTALL_DIR "share/${CMAKE_PROJECT_NAME}")
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check whether VCPKG is set up in your system
if(NOT DEFINED ENV{VCPKG_ROOT})
  message(FATAL_ERROR "ERROR: This project requires VCPKG.\n")
endif()

# Set header files
set(header
    "include/test.h"
)

# Set source files
set(src 
    "src/test.cpp"
)


# Define library target
add_library(${CMAKE_PROJECT_NAME} ${header} ${src})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}> 
    $<INSTALL_INTERFACE:${ACTION_LIKELIHOOD_PROJ_INC_INSTALL_DIR}> 
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Setup coppeliasim-cpp-client
find_package(coppeliasim-cpp-client REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE coppeliasim-cpp-client)

target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC
                            ACTION_LIKELIHOOD_PROJ=1
                            ACTION_LIKELIHOOD_PROJ_VERSION_MAJOR=${ACTION_LIKELIHOOD_PROJ_VERSION_MAJOR}
                            ACTION_LIKELIHOOD_PROJ_VERSION_MINOR=${ACTION_LIKELIHOOD_PROJ_VERSION_MINOR}
)

set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
                                       OUTPUT_NAME "${CMAKE_PROJECT_NAME}-${ACTION_LIKELIHOOD_PROJ_VERSION}"
                                       POSITION_INDEPENDENT_CODE ON
)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT ${CMAKE_PROJECT_NAME}Targets
        RUNTIME       DESTINATION ${ACTION_LIKELIHOOD_PROJ_RUNTIME_INSTALL_DIR}
        LIBRARY       DESTINATION ${ACTION_LIKELIHOOD_PROJ_LIBRARY_INSTALL_DIR}
        ARCHIVE       DESTINATION ${ACTION_LIKELIHOOD_PROJ_ARCHIVE_INSTALL_DIR}
        FRAMEWORK     DESTINATION ${ACTION_LIKELIHOOD_PROJ_FRAMEWORK_INSTALL_DIR}
)

include(CMakePackageConfigHelpers)
set(version_file "${CMAKE_CURRENT_BINARY_DIR}/cmake/${CMAKE_PROJECT_NAME}-config-version.cmake")
write_basic_package_version_file(${version_file}
                                 VERSION ${ACTION_LIKELIHOOD_PROJ_VERSION}
                                 COMPATIBILITY AnyNewerVersion
)

install(FILES ${header} DESTINATION ${ACTION_LIKELIHOOD_PROJ_INC_INSTALL_DIR})

install(EXPORT ${CMAKE_PROJECT_NAME}Targets DESTINATION ${ACTION_LIKELIHOOD_PROJ_CMAKE_CONFIG_INSTALL_DIR}
                                       FILE ${CMAKE_PROJECT_NAME}-config.cmake
)

# Add executable project
set(EXE_PROJECT ${CMAKE_PROJECT_NAME}-exe)
add_executable(${EXE_PROJECT} "src/main.cpp")
target_include_directories(${EXE_PROJECT} PRIVATE include)
target_link_libraries(${EXE_PROJECT} PRIVATE coppeliasim-cpp-client)
