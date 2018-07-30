#cmake for qt project

cmake_minimum_required(VERSION 3.5)

project(model)

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

set(MAIN_SRC "sources/main.cpp" "sources/model.cpp" "include/model.h" "include/model_reader.h" "sources/model_reader.cpp")
set(BOOK_LIB "books")
file(GLOB BOOK_SRC "sources/book_library/*.cpp")

add_executable(${PROJECT_NAME} ${MAIN_SRC})
add_library(${BOOK_LIB} SHARED ${BOOK_SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ${BOOK_LIB})
