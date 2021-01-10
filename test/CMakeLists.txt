cmake_minimum_required(VERSION 3.5)
project(midi_smf_reader_test CXX)

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

include_directories(../src)

add_executable(midi_smf_reader_test
        test1.cpp default_test_fixture.h test_read_midi.cpp test_read_poly_midi.cpp)

target_link_libraries(midi_smf_reader_test midi_smf_reader_src)
target_link_libraries(midi_smf_reader_test ${teensy_x86_stubs_LIBS})
target_link_libraries(midi_smf_reader_test ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})