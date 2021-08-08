# midi smf reader
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/project-CMake-brightgreen.svg?label=built%20with&colorA=555555&colorB=8a8fff&logo=)](CMakelists.txt)
[![Ubuntu-x64](https://github.com/newdigate/midi-smf-reader/workflows/Ubuntu-x64/badge.svg)](https://github.com/newdigate/midi-smf-reader/actions?query=workflow%3AUbuntu-x64)
[![teensy40](https://github.com/newdigate/midi-smf-reader/workflows/teensy40/badge.svg)](https://github.com/newdigate/midi-smf-reader/actions?query=workflow%3Ateensy40)

c++ midi file reader for linux (`amd64 arch`) and teensy (`32 bit arm cortex m7 thumb arch`)  

## contents:
* [usage](#usage)
* [dependencies](#dependencies)
* [compile and install on linux](#compile-and-install-on-linux)
* [compile example for teensy](#compile-example-for-teensy)
* [todo](#todo)
* [credits](#credits)
* [license](#license)
  
## usage:
``` c++
midireader reader;
reader.open("1234.mid");
double microsPerTick = reader.get_microseconds_per_tick();
int totalNumNotesRead = 0;
for (int t = 0; t < reader.getNumTracks(); t++) {
    reader.setTrackNumber(t);
    midimessage midiMessage{};
    int i = 0;
    long totalTicks = 0, microseconds = 0;
    smfmidimessage *message;
    while ((message = reader.read()) != nullptr) {
        totalTicks += message->delta_ticks;
        microseconds += microsPerTick * message->delta_ticks;
        switch(message->getMessageType()) {
            case smftype_channelvoicemessage : {
                smfchannelvoicemessage *channelvoicemessage = (smfchannelvoicemessage *)message;
                printf("%5d: [%2d,%4d]: %6d: delta: %3d\tstatus: 0x%2x\tdata1: %3d\tdata2: %3d\tdata3: %2d\t\n",
                    microseconds/1000,
                    t,
                    i,
                    totalTicks,
                    channelvoicemessage->delta_ticks,
                    channelvoicemessage->status,
                    channelvoicemessage->data1,
                    channelvoicemessage->data2,
                    channelvoicemessage->data3);
                break; 
            }

            case smftype_settempomessage : {
                printf("tempo change: %f\n", ((smfsettempomessage *)message)->getTempo());
                break;
            }

            default: 
                break;
        }

        delete message;
        i++;
    }
    totalNumNotesRead += i;
}
```

## dependencies:
* src (`32 bit arm cortex m7 thumb arch`)  
  * [PaulStoffregen/cores](https://github.com/PaulStoffregen/cores)
  * [greiman/SdFat](https://github.com/greiman/SdFat)
  * [PaulStoffregen/SD @ Juse_Use_SdFat](https://github.com/PaulStoffregen/SD)
  * [PaulStoffregen/SPI](https://github.com/PaulStoffregen/SPI)
  * [gcc-arm-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
  * [teensy-cmake-marcos](https://github.com/newdigate/teensy-cmake-marcos)
  
* tests (`amd64 arch`)
  * [teensy_x86_stubs](https://github.com/newdigate/teensy-x86-stubs)
    ``` sh
    git clone https://github.com/newdigate/teensy-x86-stubs.git
    cd teensy-x86-stubs
    mkdir cmake-build-debug
    cd cmake-build-debug
    cmake ..
    sudo make install
    ```
  * [libboost-test-dev](https://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/index.html)
    ``` sh
    sudo apt-get update && sudo apt-get install -yq libboost-test-dev
    ```
## compile and install on linux      
* clone:
  ``` sh
  git clone https://github.com/newdigate/midi-smf-reader.git
  cd midi-smf-reader
  ```
* compile src, tests
  ``` sh
  mkdir cmake-build-debug
  cd cmake-build-debug
  cmake ..
  make
  ```
* run tests
  ``` sh
  test/midi_smf_reader_test
  ```
* install library for linux: 
  ``` sh
  sudo make install
  ```
* uninstall library for linux: 
  ``` sh
  sudo make uninstall
  ```
  
## compile example for teensy:
* download [gcc-arm-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
* clone src dependencies into a directory (in this case `/Users/me/git`)
``` sh
mkdir /Users/me/git
cd /Users/me/git
git clone https://github.com/PaulStoffregen/cores
git clone https://github.com/greiman/SdFat
git clone -b Juse_Use_SdFat https://github.com/PaulStoffregen/SD
git clone https://github.com/PaulStoffregen/SPI
```

* update *COMPILERPATH*, *DEPSPATH* in `examples/CMakeLists.include.txt:`
``` cmake
set(COMPILERPATH "/Applications/ARM/bin/")   # should point to folder with GCC-ARM-NONE-EABI executables
set(DEPSPATH "/Users/me/git")                # path with 4 x src dependencies 
```

* run these commands in a terminal from the root repository directory
``` sh
cd examples/basic
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. 
```

## todo:
* read tempo / key changes

## credits
##### Don't Run Unit Tests on the Arduino Device or Emulator
* [stackoverflow 11437456](https://stackoverflow.com/a/11437456)
* includes code from [IronSavior/dsm2_tx](https://github.com/IronSavior/dsm2_tx)

##### cmake uninstaller
*  [gist.github.com/royvandam/3033428](https://gist.github.com/royvandam/3033428)

## license
Unless specified in source code file, all code is MIT license.
