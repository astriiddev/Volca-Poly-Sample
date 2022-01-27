/*  Polyphony support for Korg Volca Sample 2 via MIDI.

    Translates incoming MIDI notes into CC control 49 values and
    cycles through MIDI channels 1-8 using Arduino MIDI library
      https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/5.0.2
    
    Parts 1-8 must be set to same sample and same settings.
    MIDI controller must be set to channel 16.
    Global settings must be set to multichannel (setting 10, LED off).
    Volca Sample uses One Shot samples and has no Note Off support. Note sustain
      and decay must be set with sample and amp decay.

    MIDI input circuit:
      https://hackaday.com/tag/6n137/

    MIDI output circuit:
      https://www.notesandvolts.com/2015/03/midi-for-arduino-build-midi-output.html

    Finley Ondioline, 23/01/2022

*/


#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13                                                          //LED on Arduino lights up with incoming MIDI signal, helps troubleshoot circuit

byte ch = 0;
byte x = 175;

void HandleNoteOn(byte channel, byte note, byte velocity) {
  ++ch;                                                                 //increments output MIDI channel
  MIDI.sendNoteOn(note, velocity, ch);
  ++x;                                                                  //increments CC 49 control channel by 1
  HandleControlChange(x,49,note+4);                                     //sets CC 49 value equal with note
  digitalWrite(LED,HIGH);
}

void HandleNoteOff(byte channel, byte note, byte velocity) {
  digitalWrite(LED,LOW);
}

void HandleControlChange(byte channel, byte number, byte value) {        //writes CC to MIDI Out
  Serial.write(channel);
  Serial.write(number);
  Serial.write(value);
}

void setup() {
  pinMode(LED, OUTPUT);

  MIDI.setHandleNoteOn(HandleNoteOn);                                   //incoming MIDI Note On
  MIDI.setHandleNoteOff(HandleNoteOff);                                 //incoming MIDI Note Off
  MIDI.setHandleControlChange(HandleControlChange);                     //incoming MIDI CC
  MIDI.begin(16);                                                       //sets incoming MIDI channel to 16
  
}

void loop() {
  MIDI.read();                                                          //read incoming MIDI  
  if (ch==8){ch=0;}                                                     //loops MIDI channel cycle back to channel 1 after channel 8
  if (x==183){x=175;}                                                   //loops MIDI CC channel cycle back to 1 after channel 8
}
