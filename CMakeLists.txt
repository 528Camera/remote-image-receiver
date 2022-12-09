project(RECEIVER C CXX)

cmake_minimum_required(VERSION 3.5.1)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

find_package(Boost COMPONENTS system filesystem unit_test_framework log log_setup REQUIRED)

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES ../include/zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS})
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS})

include_directories(${Boost_INCLUDE_DIR} ./src)

add_subdirectory(proto)
add_subdirectory(src)

enable_testing()
add_subdirectory(tests)