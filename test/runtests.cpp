#include "../src/midireader.h"

#include <Arduino.h>
#include <SD.h>

using namespace std;

int main(int argc, char **argv){
    std::cout << "starting app...\n";
    initialize_mock_arduino();

    char *buffer = "blah blah blah blah blah";
    SD.setSDCardFileData(buffer, strlen(buffer));

    File f = SD.open("abcdefg.123");

    char *output = new char[1000];
    int bytesRead = f.read(output, 1000);

    std::cout << bytesRead << " bytes read: \n" << output;
}

