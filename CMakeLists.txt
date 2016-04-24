cmake_minimum_required(VERSION 3.5)
project(kage)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/datarobot2d.cpp
    src/datarobot2d.h
    src/kageext.cpp
    src/numpy_import.h
    main.cpp src/utils.h src/utils.cpp)

include_directories("/Users/thuanqin/Desktop/DeV/lab/python3.5/include/python3.5m")
include_directories("/Users/thuanqin/Desktop/Dev/lab/python3.5/lib/python3.5/site-packages/numpy/core/include")

add_executable(kage ${SOURCE_FILES})