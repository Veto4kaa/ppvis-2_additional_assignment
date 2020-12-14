cmake_minimum_required(VERSION 3.10)
project(list_queue)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_SOURCE_DIR})

add_executable(tests ${CMAKE_SOURCE_DIR}/tests/tests.cpp)

