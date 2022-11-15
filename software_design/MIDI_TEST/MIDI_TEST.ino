/* MIDI Input Test - for use with Teensy or boards where Serial is separate from MIDI
 * As MIDI messages arrive, they are printed to the Arduino Serial Monitor.
 *
 * Where MIDI is on "Serial", eg Arduino Duemilanove or Arduino Uno, this does not work!
 *
 * This example code is released into the public domain.
 */
 
#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Input Test");
}

unsigned long t=0;
bool switcher = false;

void loop() {
  int type, note, velocity, channel, d1, d2;
//  if (MIDI.read()) {                    // Is there a MIDI message incoming ?
//    byte type = MIDI.getType();
//    switch (type) {
//      case midi::NoteOn:
//        note = MIDI.getData1();
//        velocity = MIDI.getData2();
//        channel = MIDI.getChannel();
//        if (velocity > 0) {
//          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
//        } else {
//          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
//        }
//        break;
//      case midi::NoteOff:
//        note = MIDI.getData1();
//        velocity = MIDI.getData2();
//        channel = MIDI.getChannel();
//        Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
//        break;
//      default:
//        d1 = MIDI.getData1();
//        d2 = MIDI.getData2();
//        Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
//    }
////    t = millis();
//  }
//  if (millis() - t > 10000) {
//    t += 10000;
//    Serial.println("(inactivity)");
//  }


  if (millis() - t > 1000) {
    t += 1000;
    if (switcher){
      MIDI.sendNoteOn(40, 127, 1);
    Serial.println("(note on)");
    switcher = false;
    } else {
      MIDI.sendNoteOff(40, 127, 1);
      switcher = true;
      Serial.println("(note off)");
    }
  }
//  MIDI.sendNoteOn(40, 127, 1);
//  Serial.println("++++note on");
////  delay(1000);
//  Serial.println("----note off");
//  MIDI.sendNoteOff(40, 127, 1);
//  delay(1000);
}
