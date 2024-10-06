cmake_minimum_required(VERSION 3.5)
project(midi_smf_reader_test CXX C)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

include_directories(../src)

add_executable(midi_smf_reader_test
        test1.cpp test_read_midi.cpp test_read_poly_midi.cpp)

target_link_libraries(midi_smf_reader_test midi_smf_reader)
target_link_libraries(midi_smf_reader_test teensy_x86_stubs)
target_link_libraries(midi_smf_reader_test teensy_x86_sd_stubs)
target_link_libraries(midi_smf_reader_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})