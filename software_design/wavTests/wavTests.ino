#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav3;     //xy=156,336
AudioPlaySdWav           playSdWav2;     //xy=164,268
AudioPlaySdWav           playSdWav1;     //xy=170,189
AudioMixer4              mixer2;         //xy=409,265
AudioMixer4              mixer1;         //xy=460,174
AudioEffectGranular      granular1;      //xy=622,168
AudioOutputI2S           i2s1;           //xy=778,193
AudioConnection          patchCord1(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord2(playSdWav3, 1, mixer2, 2);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord6(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord7(mixer1, granular1);
AudioConnection          patchCord8(granular1, 0, i2s1, 0);
AudioConnection          patchCord9(granular1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=495,408
// GUItool: end automatically generated code


// Use these with the Teensy 3.5 & 3.6 SD card
//#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_CS_PIN    6
//#define SDCARD_MOSI_PIN  11  // not actually used
//#define SDCARD_SCK_PIN   13  // not actually used

#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

long lastTrig = 0;

void setup() {

  Serial.begin(9600);

  AudioMemory(8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

//  SPI.setMOSI(SDCARD_MOSI_PIN);
//  SPI.setSCK(SDCARD_SCK_PIN);


  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }

  mixer1.gain(0, 0.5);
  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  mixer2.gain(2, 0.5);
  delay(1000);

    // the Granular effect requires memory to operate
  granular1.begin(granularMemory, GRANULAR_MEMORY_SIZE);
  granular1.setSpeed(4);
  granular1.beginPitchShift(5);
}

void loop() {
//  if(playSdWav1.isPlaying() == false){
//    Serial.println("Start playing 1");
//    playSdWav1.play("DRUMS/HAT.WAV");
//    delay(10);
//  }
//
//  if (playSdWav2.isPlaying() == false){
//    Serial.println("Start playing 2");
//    playSdWav2.play("DRUMS/TOM.WAV");
//    delay(10);
//  }

    if (playSdWav3.isPlaying() == false){
    Serial.println("Start playing 3");
    playSdWav3.play("HAT.WAV");
    delay(10);
  }


    // Button 1 starts Pitch Shift effect
//  if (millis() > lastTrig + 2000) {
////    float msec = 25.0 + (0.3 * 75.0);
////    granular1.beginPitchShift(msec);
////    Serial.print("Begin granular pitch phift using ");
////    Serial.print(msec);
////    Serial.println(" grains");
//
//
//
//    lastTrig = millis();
//  }

}
