/*  

  Polyphony support for Korg Volca Sample 2 via MIDI.

  Version 2.0

  Translates incoming MIDI notes into CC control 49 values and
  cycles through MIDI channels 1-8 using Arduino MIDI library
    https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/5.0.2
  
  Parts 1-8 must be set to same sample and same settings.
  Change master settings for parts 1-8 using CC. See MIDI Implementation chart
  for Volca Sample 2 for corresponding CC controls: 
    https://cdn.korg.com/us/support/download/files/c19d48a599794ff64a25b553e951c2fb.pdf
  
  MIDI controller must be set to channel 16.
  Global settings on Volca must be set to multichannel (setting 10, LED off).

  Volca Sample uses One Shot samples and has no Note Off support. Note sustain
  and decay must be set with sample and amp decay or corresponding MIDI CC.

  MIDI input circuit:
    https://hackaday.com/tag/6n137/

  MIDI output circuit:
    https://www.notesandvolts.com/2015/03/midi-for-arduino-build-midi-output.html

  Finley Baker, 01/23/2022(1.0) - 04/21/23(2.0)

*/


#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

#define LED 13                                                          //LED on Arduino lights up with incoming MIDI signal, helps troubleshoot circuit

int sampleChannel = 1;

void HandleNoteOn(byte channel, byte note, byte velocity) 
{
  
  if (sampleChannel >= 9){sampleChannel = 1;}

  MIDI.sendNoteOn(note, velocity, sampleChannel);
  MIDI.sendControlChange(49, note + 4, sampleChannel);                  //loops through channels 1-8, matching MIDI note value to Volca CC note change
  
  sampleChannel++;
  
  digitalWrite(LED,HIGH);

}

void HandleNoteOff(byte channel, byte note, byte velocity) 
{
  digitalWrite(LED,LOW);
}

 void HandleControlChange(byte channel, byte number, byte value)         //writes CC to MIDI Out
{
  
  if (number == 91)                                                      //Reverb mix CC, only responds to Ch.1
  {
    MIDI.sendControlChange(91, value, 1);
  } else
  for(int i = 1; i < 9; i++)
  {
    MIDI.sendControlChange(number, value, i);                           //see Volca Sample 2 MIDI implementation chart for corresponding CC
  }

}

void setup() 
{

  pinMode(LED, OUTPUT);

  MIDI.setHandleNoteOn(HandleNoteOn);                                   //incoming MIDI Note On
  MIDI.setHandleNoteOff(HandleNoteOff);                                 //incoming MIDI Note Off
  MIDI.setHandleControlChange(HandleControlChange);                     //incoming MIDI CC
  MIDI.begin(16);                                                       //sets incoming MIDI channel to 16
  
}

void loop() 
{
  MIDI.read();                                                         //Reads incoming MIDI
}
