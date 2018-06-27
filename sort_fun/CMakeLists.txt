#cmake
cmake_minimum_required(VERSION 3.5)

project(sort_funs)

option(set_clang "set clang defolt compiler" 0)

if(set_clang)
    set(CMAKE_CXX_COMPILER clang++)
endif()
message(STATUS "Cxx Compiler is " ${CMAKE_CXX_COMPILER})

add_definitions(-Wall -std=c++14)

include_directories(include)

set(MAIN_SRC sources/main.cpp)
set(SORT_LIBRARY "sort")
file(GLOB SORT_SRC "sources/sort/*.cpp")

add_library(${SORT_LIBRARY} STATIC ${SORT_SRC})

add_executable(${PROJECT_NAME} ${MAIN_SRC})

target_link_libraries(${PROJECT_NAME} ${SORT_LIBRARY})
