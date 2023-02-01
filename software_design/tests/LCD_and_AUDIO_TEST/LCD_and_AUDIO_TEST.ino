#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_DC 25
#define LCD_CS 10
#define LCD_RST 24


// End of constructor list

U8G2_PCD8544_84X48_F_4W_HW_SPI u8g2(U8G2_R0, LCD_CS, LCD_DC, LCD_RST);


//u8g2_t u8g2;
 int xx;

 AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;

Bounce button0 = Bounce(0, 15);
Bounce button1 = Bounce(1, 15);
Bounce button2 = Bounce(2, 15);

int count=1;
int a1history=0, a2history=0, a3history=0;

void setup(void) {
u8g2.begin();
 xx = 10;
//SPI.begin();
// SPI.setClockDivider(128);
  AudioMemory(10);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  Serial.begin(115200);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.3);
  waveform1.begin(WAVEFORM_SINE);
  delay(1000);
  button0.update();
  button1.update();
  button2.update();
  a1history = analogRead(A1);
  a2history = analogRead(A2);
  a3history = analogRead(A3);
}

void loop(void) {
//  u8g2.clearBuffer();          // clear the internal memory
//  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
//  u8g2.drawStr(0,11,"Hello Worldo!");  // write something to the internal memory
//  u8g2.drawStr(20,30," <3");  // write something to the internal memory
//  u8g2.sendBuffer();          // transfer internal memory to the display
//  delay(1000);   
}
