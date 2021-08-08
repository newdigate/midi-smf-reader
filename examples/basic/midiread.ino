#include <Arduino.h>
#include "midireader.h"

void setup() {
    midireader reader;
    reader.open("1234.mid");

    double microsPerTick = reader.get_microseconds_per_tick();

    int totalNumNotesRead = 0;
    for (int t = 0; t < reader.getNumTracks(); t++)
    {
        reader.setTrackNumber(t);
        int i = 0;
        long totalTicks = 0;
        long microseconds = 0;
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
}

void loop() {
    
}