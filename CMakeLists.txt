cmake_minimum_required(VERSION 3.5)

project(midi_smf_reader C CXX)

set(CMAKE_CXX_STANDARD 11)

find_package(teensy_x86_stubs REQUIRED)

add_subdirectory(src)
add_subdirectory(test)

##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
add_custom_target(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/cmake/uninstall.cmake")