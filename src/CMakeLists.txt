cmake_minimum_required(VERSION 3.5)

project(midi_smf_reader_src C CXX)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

add_library(midi_smf_reader_src STATIC
        midireader.h midireader.cpp)

target_link_libraries(midi_smf_reader_src ${teensy_x86_stubs_LIB_DIR})

set(CMAKE_VERBOSE_MAKEFILE 1)