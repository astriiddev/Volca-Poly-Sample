# Volca-Poly-Sample
Allows the Korg Volca Sample 2 to be played polyphonically via a MIDI controller


The Korg Volca Sample 2 is a great low cost Sampler/Sequencer that's a major upgrade from its first iteration. Unfortunately, like its first iteration, there isn't any ability to play the Volca Sample live via a MIDI controller. Plugging a MIDI keyboard into the volca sample will only play back the sample's set pitch, no matter which key is pressed. On top of that, there's currently no support for Pajen's custom firmware that fixed this problem on the Sample 1. Using an Arduino UNO board, I decided to create a MIDI interface that not only allows one to play a Volca Sample 2 chromatically, but with 8-voice polyphony as well.

Luckily, the Volca Sample 2 added some new CC controls. CC control #49 chromatically changes the speed, and therefore pitch, of the sample that's being played. This Arduino code takes advantage of that CC control.

To begin, parts 1-8 on the Volca Sample 2 must be set up to the same sample and with the same settings. The Arduino will cycle through these parts allowing you to play all 8 parts at once, so any major difference between the setup of each sample part will be apparent if they're not setup the same.

The Volca Sample only uses One Shot samples, meaning it only reads the MIDI note ON messages, but not the MIDI note OFF messages. This means that your sustain and release can only be set by the decay knobs on the Sample and Amp section of the Volca. Holding keys down for longer or shorter amounts of times unfortunately will not change the sustain length.

Setting number 10 in the Global Settings must be set to Multi (LED off).

Your MIDI controller must be outputing on MIDI channel 16.

You must also have the Arduino MIDI Library installed: https://github.com/FortySevenEffects/arduino_midi_library/releases/tag/5.0.2

For a MIDI input schematic, see: https://hackaday.com/tag/6n137/

For a MIDI output schematic, see:https://www.notesandvolts.com/2015/03/midi-for-arduino-build-midi-output.html

Further down the line, I hope to add other CC controls across all channels (such as CC #42 so that one knob on the MIDI controller can change the LP filter on all 8 parts), but for now, please enjoy this project.
