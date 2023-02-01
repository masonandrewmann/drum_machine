#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_DC 25
#define LCD_CS 10
#define LCD_RST 24


// End of constructor list

U8G2_PCD8544_84X48_F_4W_HW_SPI u8g2(U8G2_R2, LCD_CS, LCD_DC, LCD_RST);


//u8g2_t u8g2;
 int xx;

void setup(void) {
u8g2.begin();
 xx = 10;
//SPI.begin();
// SPI.setClockDivider(128);
}

void loop(void) {
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,11,"Hello Worldo!");  // write something to the internal memory
  u8g2.drawStr(20,30," <3");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  delay(1000);   
}
