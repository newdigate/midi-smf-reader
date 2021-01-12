# midi smf reader
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/project-CMake-brightgreen.svg?label=built%20with&colorA=555555&colorB=8a8fff&logo=)](CMakelists.txt)
[![Ubuntu-x64](https://github.com/newdigate/midi-smf-reader/workflows/Ubuntu-x64/badge.svg)](https://github.com/newdigate/midi-smf-reader/actions?query=workflow%3Ateensy40)
[![teensy40](https://github.com/newdigate/midi-smf-reader/workflows/teensy40/badge.svg)](https://github.com/newdigate/midi-smf-reader/actions?query=workflow%3AUbuntu-x64)

simple c++ smf midi file reader targeting teensy cores 

## dependencies:
* src
  * [PaulStoffregen/cores](https://github.com/PaulStoffregen)
  * [greiman/SdFat](https://github.com/greiman/SdFat)
  * [PaulStoffregen/SD @ Juse_Use_SdFat](https://github.com/PaulStoffregen/SD)
  * [PaulStoffregen/SPI](https://github.com/PaulStoffregen/SPI)
  * [gcc-arm-none-eabi](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
      
* tests
  * [teensy_x86_stubs](https://github.com/newdigate/teensy-x86-stubs)
  * [libboost-test-dev](https://www.boost.org/doc/libs/1_63_0/libs/test/doc/html/index.html)
 ``` sh
        sudo apt-get update && sudo apt-get install -yq libboost-test-dev
 ```

  
## basic usage:
``` c++
        midireader reader;
        reader.open("1234.mid");

        double microsPerTick = reader.get_microseconds_per_tick();

        int totalNumNotesRead = 0;
        for (int t = 0; t < reader.getNumTracks(); t++)
        {
            reader.setTrackNumber(t);
            midimessage midiMessage{};
            int i = 0;
            long totalTicks = 0;
            long microseconds = 0;
            while (reader.read(midiMessage)) {
                totalTicks += midiMessage.delta_ticks;
                microseconds += microsPerTick * midiMessage.delta_ticks;
                printf("%5d: [%2d,%4d]: %6d: delta: %3d\tstatus: 0x%2x\tkey: %3d\tvelocity: %3d\tchannel: %2d\t\n",
                       microseconds/1000,
                       t,
                       i,
                       totalTicks,
                       midiMessage.delta_ticks,
                       midiMessage.status,
                       midiMessage.key,
                       midiMessage.velocity,
                       midiMessage.channel);
                i++;
            }
            totalNumNotesRead += i;
        }
```

## compile example for teensy:
* update COMPILERPATH, DEPSPATH in examples/CMakeLists.txt:
``` cmake
set(COMPILERPATH "/Applications/ARM/bin/")   # should point to folder with GCC-ARM-NONE-EABI executables
set(DEPSPATH "/Users/me/git")                # path with 4 x src dependencies 
set(COREPATH "${DEPSPATH}/cores/teensy4/")   
```
* 
``` sh
cd examples/basic
mkdir cmake-build-debug
cd cmake-build-debug
cmake .. 
```

## package installation:
``` sh
git clone https://github.com/newdigate/midi-smf-reader.git
cd midi-smf-reader
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
sudo make install
```

### uninstall:
``` sh
sudo make uninstall
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
