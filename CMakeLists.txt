cmake_minimum_required(VERSION 3.10.0)
project(Project VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O2 -Wall -DMOCK -DVERBOSE_STATES -fsanitize=address -fno-omit-frame-pointer -fno-inline")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address -lpthread -static-libgcc -static-libstdc++ -gdwarf-2")

file(GLOB_RECURSE MAIN_SRC CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE MAIN_INC CONFIGURE_DEPENDS "inc/*.h")


set (GLOB_INC_DIRS "")
foreach (_headerFile ${MAIN_INC})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND GLOB_INC_DIRS ${_dir})
endforeach()

list (REMOVE_DUPLICATES GLOB_INC_DIRS)


include_directories(${GLOB_INC_DIRS})

add_executable(Project main.cpp ${MAIN_SRC})