//
// Created by Moolet on 31/12/2020.
//

#ifndef MIDI_SMF_READER_DEFAULT_TEST_FIXTURE_H
#define MIDI_SMF_READER_DEFAULT_TEST_FIXTURE_H

#include <Arduino.h>
#include <SD.h>

struct DefaultTestFixture
{
    DefaultTestFixture()
    {
        initialize_mock_arduino();
    }

};
#endif //MIDI_SMF_READER_DEFAULT_TEST_FIXTURE_H
