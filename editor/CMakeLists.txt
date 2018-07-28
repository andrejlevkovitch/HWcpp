#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(editor)

option(set_clang "set clang as default compiler" 0)
option(cros_compile "cros compile" 0)

if(set_clang)
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
    message(STATUS "Use option set_clang")
endif()

message(STATUS "Project      " ${PROJECT_NAME})
message(STATUS "c compiler   " ${CMAKE_C_COMPILER})
message(STATUS "cxx compiler " ${CMAKE_CXX_COMPILER})

set(CMAKE_CXX_STANDARD 14)
add_definitions(-Wall)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

include_directories("./include")

file(GLOB MAIN_SRC "sources/*.cpp" "include/*.h")

add_executable(${PROJECT_NAME} ${MAIN_SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
