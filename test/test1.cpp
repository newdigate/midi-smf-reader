//
// Created by Moolet on 31/12/2020.
//

#define BOOST_TEST_MODULE BasicArduinoTests
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "default_test_fixture.h"

BOOST_AUTO_TEST_SUITE(basic_midi_read_test)

    BOOST_FIXTURE_TEST_CASE(can_mock_arduino_SD_contents, DefaultTestFixture) {

        char *buffer = "blah blah blah blah blah";
        SD.setSDCardFileData(buffer, strlen(buffer));

        File f = SD.open("abcdefg.123");

        char *output = new char[1000];
        int bytesRead = f.read(output, 1000);

        BOOST_CHECK_EQUAL(bytesRead, 24);
        BOOST_CHECK_EQUAL(*output, *buffer);
    }

BOOST_AUTO_TEST_SUITE_END()