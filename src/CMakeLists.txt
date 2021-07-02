cmake_minimum_required(VERSION 3.10)
project(midi_smf_reader)

set(SOURCE_FILES
        midireader.cpp)

set(HEADER_FILES
        midireader.h)

if (DEFINED BUILD_FOR_LINUX)    
        include(CMakeLists.linux.cmake)
else()
        include(CMakeLists.teensy.cmake)
endif()
