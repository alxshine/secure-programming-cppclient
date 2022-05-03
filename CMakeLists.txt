cmake_minimum_required(VERSION 3.16)
project(cleanup)

set(CMAKE_CXX_STANDARD 14)
include_directories(inc)

add_executable(main src/TCP.cpp src/main.cpp)