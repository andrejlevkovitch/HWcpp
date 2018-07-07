#cmake

cmake_minimum_required(VERSION 3.5)

project(sort_file)

option(set_clang "set clang as default compiler" 0)
option(cros_compile "cros compile" 0)

if(set_clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    message(STATUS "Use option set_clang")
endif()
if(cros_compile)
    set(PROJECT_NAME ${PROJECT_NAME}.exe)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++-posix)
    set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
    message(STATUS "Use option cros_compile")
endif()

message(STATUS "Project      " ${PROJECT_NAME})
message(STATUS "c compiler   " ${CMAKE_C_COMPILER})
message(STATUS "cxx compiler " ${CMAKE_CXX_COMPILER})

add_definitions(-Wall -std=c++14)

include_directories(include)

set(MAIN_SRC sources/main.cpp)
file(GLOB SORT_SRC "sources/sort/*cpp")

add_executable(${PROJECT_NAME} ${MAIN_SRC} ${SORT_SRC})
