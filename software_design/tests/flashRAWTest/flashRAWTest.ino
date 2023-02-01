#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySerialflashRaw  playFlashRaw1;  //xy=250,173
AudioSynthSimpleDrum     drum1;          //xy=298,272
AudioSynthWavetable      wavetable1;     //xy=301,411
AudioOutputI2S           i2s1;           //xy=462,193
AudioConnection          patchCord1(playFlashRaw1, 0, i2s1, 0);
AudioConnection          patchCord2(drum1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=631,613
// GUItool: end automatically generated code


const int FlashChipSelect = 6; // digital pin for flash chip CS pin




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  
  AudioMemory(8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  if (!SerialFlash.begin(FlashChipSelect)) {
    Serial.println("Unable to access SPI Flash chip");
  }

  
 drum1.frequency(200);
 drum1.length(500);
 drum1.secondMix(0.7);
 drum1.pitchMod(0.5);

}

void loop() {
  // put your main code here, to run repeatedly:

//    if (playFlashRaw1.isPlaying() == false){
//    Serial.println("Start playing HAT.RAW");
//    playFlashRaw1.play("HAT.RAW");
//    delay(10);
//  }

  drum1.noteOn();
  delay(1000);

}
