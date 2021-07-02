cmake_minimum_required(VERSION 3.5)
set(midi_smf_reader_VERSION 1.0.0)

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include/midi_smf_reader/)
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/midi_smf_reader )

find_package(teensy_x86_stubs)
include_directories(${teensy_x86_stubs_INCLUDE_DIR})

find_package(teensy_x86_sd_stubs)
include_directories(${teensy_x86_sd_stubs_INCLUDE_DIR})

add_library(midi_smf_reader STATIC ${HEADER_FILES} ${SOURCE_FILES})

set_target_properties(midi_smf_reader PROPERTIES PUBLIC_HEADER "midireader.h")

include(CMakePackageConfigHelpers)
configure_package_config_file(../cmake/midi_smf_reader.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/midi_smf_readerConfig.cmake
        INSTALL_DESTINATION ${LIB_INSTALL_DIR}/midi_smf_reader/cmake
        PATH_VARS)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/midi_smf_readerConfigVersion.cmake
        VERSION ${midi_smf_reader_VERSION}
        COMPATIBILITY SameMajorVersion )

install(TARGETS midi_smf_reader DESTINATION
        LIBRARY DESTINATION ${LIB_INSTALL_DIR}
        ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
        PUBLIC_HEADER DESTINATION "include/midi_smf_reader"
        )

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/midi_smf_readerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/midi_smf_readerConfigVersion.cmake
        ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake
        DESTINATION "lib/cmake/midi_smf_reader" )
##
# copied from: https://gist.github.com/royvandam/3033428
# Add uninstall target
# Requirements: Copy the uninstall.cmake file to the appropriate CMAKE_MODULE_PATH.
#
set(CMAKE_VERBOSE_MAKEFILE 1)
add_custom_target(installarduino
        "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/install_arduino_library.cmake")

add_custom_target(uninstall
        "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/uninstall.cmake")
