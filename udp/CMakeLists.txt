# cmake for udp_server

cmake_minimum_required(VERSION 3.12)

project(udp)

find_package(Qt5 COMPONENTS Widgets Core Network REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(reciver "main_reciver.cpp" "udp_reciver.cpp")
target_link_libraries(reciver PUBLIC Qt5::Widgets Qt5::Core Qt5::Network)

add_executable(sender "main_sender.cpp" "udp_sender.cpp")
target_link_libraries(sender PUBLIC Qt5::Widgets Qt5::Core Qt5::Network)
