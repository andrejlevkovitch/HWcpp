#CMakeLists.txt

cmake_minimum_required(VERSION 3.5)

project(structures)

option(set_clang "set clang as default compiler" 0)
option(cros_compile "cros compile for win32" 0)

if(set_clang)
    set(CMAKE_CXX_COMPILER clang++)
endif(set_clang)

if(cros_compile)
    set(PROJECT_NAME ${PROJECT_NAME}.exe)
    set(CMAKE_CXX_COMPILER i686-w64-mingw32-g++-posix)
    set(CMAKE_CXX_FLAGS "-static-libstdc++ -static-libgcc")
endif(cros_compile)

add_definitions(-Wall -std=c++14)

set(MAIN_SRC sources/main.cpp)

include_directories(include)

add_executable(${PROJECT_NAME} ${MAIN_SRC})
