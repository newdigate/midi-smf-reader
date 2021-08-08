//
// Created by Nicholas Newdigate on 10/04/2018.
//
#ifndef MIDI_SMF_READER_MIDIREADER_H
#define MIDI_SMF_READER_MIDIREADER_H

#include <vector>
#include <functional>
#include <algorithm>
#include <Arduino.h>
#include <SD.h>
#include <string>

using namespace std;

enum smfmessagetype {
    smftype_channelvoicemessage = 1,
    smftype_keysignaturemessage = 2, 
    smftype_timesignaturemessage = 3,
    smftype_smpteoffsetmessage = 4, 
    smftype_settempomessage = 5, 
    smftype_endoftrackmessage = 6,
    smftype_sequencenumbermessage = 7, 
    smftype_sysexmessage = 8,
    smftype_metatextmessage = 9 
};

struct smfmidimessage {
    uint32_t delta_ticks;
    smfmidimessage() : delta_ticks(0) {};
    smfmidimessage(uint32_t deltaticks) : delta_ticks(deltaticks) {};
    virtual smfmessagetype getMessageType() = 0;
    virtual ~smfmidimessage() {};
};

struct smfchannelvoicemessage : smfmidimessage {
    smfchannelvoicemessage() : smfmidimessage(), status(0), data1(0), data2(0), data3(0) {} ;

    smfchannelvoicemessage( uint32_t delta_ticks, byte st, byte d1, byte d2) : smfmidimessage(delta_ticks), status(st), data1(d1), data2(d2) {} ;
    
    smfchannelvoicemessage( uint32_t delta_ticks, byte st, byte d1, byte d2, byte d3) : smfmidimessage(delta_ticks), status(st), data1(d1), data2(d2), data3(d3) {} ;

    ~smfchannelvoicemessage() override {
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_channelvoicemessage;
    }

    byte status;
    byte data1;
    byte data2;
    byte data3;
    byte channel;
};

struct smfkeysignaturemessage : smfmidimessage {
    smfkeysignaturemessage() : smfmidimessage(), sf(0), mi(0) {} ;

    smfkeysignaturemessage( uint32_t delta_ticks, byte sf, byte mi) : smfmidimessage(delta_ticks), sf(sf), mi(mi) {} ;

    ~smfkeysignaturemessage() override {
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_keysignaturemessage;
    }
    byte sf;
    byte mi;
};

struct smftimesignaturemessage : smfmidimessage {
    smftimesignaturemessage() : smfmidimessage(), nn(0), dd(0), cc(0), bb(0) {} ;

    smftimesignaturemessage( uint32_t delta_ticks, byte nn, byte dd, byte cc, byte bb) : smfmidimessage(delta_ticks), nn(nn), dd(dd), cc(cc), bb(bb) {} ;
    ~smftimesignaturemessage() override {
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_timesignaturemessage;
    }    

    byte nn;
    byte dd;
    byte cc;
    byte bb; 
};

struct smfsmpteoffsetmessage : smfmidimessage {
    smfsmpteoffsetmessage() : smfmidimessage(), hr(0), mn(0), se(0), fr(0), ff(0) {} ;

    smfsmpteoffsetmessage( uint32_t delta_ticks, byte hr, byte mn, byte se, byte fr, byte ff) : smfmidimessage(delta_ticks), hr(hr), mn(mn), se(se), fr(fr), ff(ff) {} ;

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_smpteoffsetmessage;
    }

    byte hr;
    byte mn;
    byte se;
    byte fr;
    byte ff;
};

struct smfsettempomessage : smfmidimessage {
    smfsettempomessage() : smfmidimessage(), microseconds_per_quarter_note(120 * 60000000) {}

    smfsettempomessage( uint32_t delta_ticks, unsigned int microseconds_per_quarter_note) : smfmidimessage(delta_ticks), microseconds_per_quarter_note(microseconds_per_quarter_note) {};     

    smfsettempomessage( uint32_t delta_ticks, double tempo) : smfmidimessage(delta_ticks), microseconds_per_quarter_note(tempo * 60000000) {};     
    
    ~smfsettempomessage() override {
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_settempomessage;
    }

    unsigned int microseconds_per_quarter_note;

    double getTempo() {
        return 60000000.0 / (double)microseconds_per_quarter_note;
    }
};

struct smfendoftrackmessage : smfmidimessage {
    smfendoftrackmessage() : smfmidimessage(), trackNumber(0) {} ;    
    smfendoftrackmessage( uint32_t delta_ticks, byte trackNumber) : smfmidimessage(delta_ticks), trackNumber(trackNumber) {};     
    ~smfendoftrackmessage() override {
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_endoftrackmessage;
    }

    byte trackNumber;
};

struct smfsequencenumbermessage : smfmidimessage {
    smfsequencenumbermessage() : smfmidimessage(), sequenceNumber(0) {} ;    
    smfsequencenumbermessage( uint32_t delta_ticks, byte sequenceNumber) : smfmidimessage(delta_ticks), sequenceNumber(sequenceNumber) {};  
    ~smfsequencenumbermessage() override {
    }
    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_sequencenumbermessage;
    }

    byte sequenceNumber;
};

struct smfsysexmessage : smfmidimessage {
    smfsysexmessage() : smfmidimessage(), data(nullptr) {} ;    
    smfsysexmessage( uint32_t delta_ticks, char *data) : smfmidimessage(delta_ticks), data(data) {};    
    ~smfsysexmessage() override {
        if (data)
            delete [] data;
    }
    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_sysexmessage;
    } 
    char *data;        
};

struct smfmetatextmessage : smfmidimessage {
    smfmetatextmessage() : smfmidimessage(), text(nullptr), textType(01) {} ;    
    smfmetatextmessage( uint32_t delta_ticks, char *text, byte textType) : smfmidimessage(delta_ticks), text(text), textType(textType) {};     
    ~smfmetatextmessage() override {
        if (text)
            delete [] text;
    }

    smfmessagetype getMessageType() override {
        return smfmessagetype::smftype_metatextmessage;
    } 

    char *text;   
    byte textType;
};

class midireader {
public:
    midireader() :
            _filename(),
            _midifile(),
            _initialized(false),
            _track_offset(),
            _track_size()
    {

    };

    bool open(const char* filename);
    void close();
    bool setTrackNumber(unsigned char trackNumber);
    smfmidimessage* read();

    unsigned getNumTracks() {
        return _numTracks;
    }

    unsigned int get_microseconds_per_tick() {
        double micros_per_beat = 60000000.0 / _currentBPM;
        unsigned int micros_per_tick = micros_per_beat / 480;
        return micros_per_tick;
    }

private:
    bool _initialized;
    File _midifile;
    char* _filename;
    unsigned _ticks_per_quarter_note;
    double _currentBPM = 120.0;
    int _current_track = -1;
    unsigned _currentTrackOffset = 0;
    unsigned _numTracks = 0;
    vector<unsigned long> _track_size;
    vector<unsigned long> _track_offset;
    unsigned char status_byte = 0;

    smfmetatextmessage* readMetaText(unsigned int delta_ticks, byte textType);

    const char * voice_message_status_name(unsigned char status);
};


#endif //MIDI_SMF_READER_MIDIREADER_H