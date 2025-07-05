cmake_minimum_required(VERSION 3.16)
project(Project VERSION 0.1.0 LANGUAGES CXX)

# Options for development
option(UNITY_BUILD "Enable unity builds for faster compilation" OFF)
option(USE_SANITIZERS "Enable address sanitizers" ON)

enable_testing()

if(UNITY_BUILD)
    set(CMAKE_UNITY_BUILD ON)
    set(CMAKE_UNITY_BUILD_BATCH_SIZE 10)
endif()

# Use file globbing carefully
file(GLOB_RECURSE MAIN_SRC LIST_DIRECTORIES false CONFIGURE_DEPENDS "src/[A-Za-z]*.cpp")
file(GLOB_RECURSE MAIN_INC LIST_DIRECTORIES false CONFIGURE_DEPENDS "inc/[A-Za-z]*.h")

# Get include directories
set(GLOB_INC_DIRS "")
foreach(_headerFile ${MAIN_INC})
    get_filename_component(_dir ${_headerFile} DIRECTORY)
    list(APPEND GLOB_INC_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES GLOB_INC_DIRS)

# Create a library
add_library(ProjectLib STATIC ${MAIN_SRC})
target_include_directories(ProjectLib PUBLIC ${GLOB_INC_DIRS})

add_compile_definitions(MOCK)
add_compile_definitions(VERBOSE_STATES)

# Executables
add_executable(Project main.cpp)

# Compiler options and definitions
target_compile_options(Project PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
)

# Conditional optimizations
if(USE_SANITIZERS)
    target_compile_options(Project PRIVATE 
        $<$<COMPILE_LANGUAGE:CXX>:-fsanitize=address -fno-omit-frame-pointer -fno-inline>
    )
    target_link_options(Project PRIVATE -fsanitize=address)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Project PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-O2>)
else()
    target_compile_options(Project PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-O0 -g>)
endif()

# Precompiled headers (fixed duplicate <typeinfo>)
target_precompile_headers(ProjectLib PRIVATE 
    <vector>
    <string>
    <memory>
    <deque>
    <iostream>
    <typeinfo>
    <stack>
    <cxxabi.h>
    <cstdint>
    <unordered_map>
)


target_link_libraries(Project PRIVATE ProjectLib pthread)

# Tests
find_package(GTest REQUIRED)
add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE ProjectLib GTest::GTest GTest::Main)
target_precompile_headers(tests PRIVATE <gtest/gtest.h>)
gtest_discover_tests(tests)