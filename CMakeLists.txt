cmake_minimum_required(VERSION 3.3)
project(matrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp nvector.h random_tests.h)
add_executable(matrix ${SOURCE_FILES})