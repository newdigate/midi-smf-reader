cmake_minimum_required(VERSION 3.10)
project(basic)

set(CMAKE_CXX_STANDARD 11)
include(../CMakeLists.txt)
import_arduino_library(${CMAKE_SOURCE_DIR} ../../src)
teensy_add_executable(basic midiread.cpp)
#set(CMAKE_VERBOSE_MAKEFILE 1)