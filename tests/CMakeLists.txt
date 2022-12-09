set(SOURCE_FILES
        ../src/ConfigurationReader.h
        ../src/ConfigurationReader.cpp
        ConfigurationReaderTests.h
        ConfigurationReaderTests.cpp
        main.cpp
)

add_executable(receiver-tests ${SOURCE_FILES})

find_package(PkgConfig)
pkg_check_modules(PC_ZeroMQ QUIET zmq)
find_path(ZeroMQ_INCLUDE_DIR
        NAMES ../include/zmq.hpp
        PATHS ${PC_ZeroMQ_INCLUDE_DIRS})
find_library(ZeroMQ_LIBRARY
        NAMES zmq
        PATHS ${PC_ZeroMQ_LIBRARY_DIRS})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(receiver-tests LINK_PUBLIC Boost::log_setup Boost::log)
target_link_libraries(receiver-tests LINK_PUBLIC ${Boost_LIBRARIES})
target_link_libraries(receiver-tests LINK_PUBLIC ${ZeroMQ_LIBRARY})
target_link_libraries(receiver-tests LINK_PUBLIC libcppunit.so)
target_link_libraries(receiver-tests LINK_PUBLIC jsoncpp)
target_include_directories(receiver-tests PRIVATE "/usr/include/jsoncpp")