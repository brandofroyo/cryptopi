cmake_minimum_required(VERSION 3.8)
project(test)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        test.cpp TradePair.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test ${SOURCE_FILES})

target_link_libraries(test bittrex curl crypto pthread
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
