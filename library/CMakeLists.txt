#cmake

cmake_minimum_required(VERSION 3.5)

project(library)

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

set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC on)
set(CMAKE_AUTOUIC on)
set(CMAKE_AUTORCC on)

include_directories("./include")

set(MAIN_SRC sources/main.cpp)
set(INTERFACE_LIB "interface")
file(GLOB INTERFACE_SRC "sources/interface/*.cpp" "include/screen.hpp")
set(BOOKLIB_LIB "booklib")
file(GLOB BOOKLIB_SRC "sources/book_library/*.cpp")

add_executable(${PROJECT_NAME} ${MAIN_SRC})
add_library(${BOOKLIB_LIB} SHARED ${BOOKLIB_SRC})
add_library(${INTERFACE_LIB} SHARED ${INTERFACE_SRC})
target_link_libraries(${INTERFACE_LIB} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${INTERFACE_LIB} ${BOOKLIB_LIB} Qt5::Widgets)
