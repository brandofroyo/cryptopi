cmake_minimum_required(VERSION 3.8)
project(brandon)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES
        brandon.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(brandon ${SOURCE_FILES})

target_link_libraries(brandon bittrex curl crypto pthread
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})