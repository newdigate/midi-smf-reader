cmake_minimum_required(VERSION 3.5)

project(midi_smf_reader C CXX)
set(midi_smf_reader_VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 11)

find_package(teensy_x86_stubs REQUIRED)

add_subdirectory(src)
add_subdirectory(test)