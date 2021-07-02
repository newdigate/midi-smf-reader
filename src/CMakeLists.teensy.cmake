teensy_add_library(midi_smf_reader ${SOURCE_FILES})

add_custom_target(installarduino
"${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_SOURCE_DIR}/../cmake/install_arduino_library.cmake")