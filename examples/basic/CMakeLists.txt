cmake_minimum_required(VERSION 3.10)
project(untitled3)

set(CMAKE_CXX_STANDARD 11)
include(../CMakeLists.txt)
teensy_add_executable(basic
        midiread.cpp)