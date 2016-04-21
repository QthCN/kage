cmake_minimum_required(VERSION 3.5)
project(kage)

include_directories("/Users/thuanqin/Desktop/DeV/lab/python3.5/include/python3.5m")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/kageext.cpp)

add_executable(kage ${SOURCE_FILES})