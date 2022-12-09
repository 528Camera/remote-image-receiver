cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(jsoncpp REQUIRED)

file(GLOB SOURCE_FILES "*.h" "*.cpp")
add_executable(receiver ${SOURCE_FILES})

target_link_libraries(receiver proto ${PROTOBUF_LIBRARY})
target_link_libraries(receiver jsoncpp_lib)