cmake_minimum_required(VERSION 3.5)
project(kage)

include_directories("/Users/thuanqin/Desktop/DeV/lab/python3.5/include/python3.5m")
include_directories("/Users/thuanqin/Desktop/Dev/lab/python3.5/lib/python3.5/site-packages/numpy/core/include")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp src/kageext.cpp src/numpy_import.h)

add_executable(kage ${SOURCE_FILES})