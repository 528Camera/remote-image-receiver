cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
find_package(jsoncpp REQUIRED)

file(GLOB SOURCE_FILES "*.h" "*.cpp")
add_executable(receiver ${SOURCE_FILES})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(receiver LINK_PUBLIC proto ${PROTOBUF_LIBRARY})
target_link_libraries(receiver LINK_PUBLIC jsoncpp_lib)
target_link_libraries(receiver LINK_PUBLIC Boost::log_setup Boost::log)
target_link_libraries(receiver LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(receiver LINK_PUBLIC ${ZeroMQ_LIBRARY})
target_link_libraries(receiver LINK_PUBLIC libcppunit.so)
target_link_libraries(receiver LINK_PUBLIC jsoncpp)
target_include_directories(receiver PRIVATE "/usr/include/jsoncpp")