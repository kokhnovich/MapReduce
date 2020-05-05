cmake_minimum_required(VERSION 3.15)
project(MapReduce)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(MR1 main.cpp)