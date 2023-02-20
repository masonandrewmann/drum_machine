#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
const int channel = 1;

void setup() {
//  MIDI.setTx(0);
//  MIDI.setRx(1);
  MIDI.begin();
}

void loop() {
  int note = 50;
//  for (note=10; note <= 127; note++) {
    MIDI.sendNoteOn(note, 100, 1);
    delay(200);
    MIDI.sendNoteOff(note, 100, 1);
//  }
  delay(1000);
}
