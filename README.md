# midi smf reader
[![MIT license](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![CMake](https://img.shields.io/badge/project-CMake-brightgreen.svg?label=built%20with&colorA=555555&colorB=8a8fff&logo=)](CMakelists.txt)

simple c++ smf midi file reader targeting teensy cores 

## dependencies:
* [teensy_x86_stubs](https://github.com/newdigate/teensy-x86-stubs)

## todo:
* read tempo / key changes

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