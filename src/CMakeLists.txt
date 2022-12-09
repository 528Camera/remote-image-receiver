cmake_minimum_required(VERSION 3.5.1)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCE_FILES "*.h" "*.cpp")
add_executable(RECEIVER ${SOURCE_FILES} Analyzer.cpp FrameSaver.cpp MessageStorage.cpp ZmqProxy.cpp ConfigurationReader.h ConfigurationReader.cpp)