//Contact SH_CP - Clock
int SH_CP = 31;
//Contact ST_CP - Latch
int ST_CP = 32;
//Contact DS - Data
int DS = 30;

void setup() {
   // let's set the outputs SH_CP, ST_CP, DS
   pinMode(SH_CP, OUTPUT); // clock pin
   pinMode(ST_CP, OUTPUT); // latch
   pinMode(DS, OUTPUT);    // data pin
}

void loop() {
//   for (int i = 0; i < 256; i++) {
//      // Call the start of data reception
//      digitalWrite(ST_CP, LOW);
//      // Sequential data transfer to DS pin
//      shiftOut(DS, SH_CP, MSBFIRST, i);
//      // Call the end of the data transfer.
//      // The shift register now supplies the voltage to the specified outputs.
//      digitalWrite(ST_CP, HIGH);
//      // 1 second delay
//      delay(1000);
//   }

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  digitalWrite(ST_CP, HIGH);
  delay(500);

  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, MSBFIRST, 0b11001100);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  shiftOut(DS, SH_CP, MSBFIRST, 0b00110011);
  digitalWrite(ST_CP, HIGH);
  delay(500);
}
