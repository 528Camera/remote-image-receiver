project(RECEIVER C CXX)

cmake_minimum_required(VERSION 3.5.1)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(proto)
add_subdirectory(src)