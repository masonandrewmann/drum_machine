#include <CSV_Parser.h>

#include <SPI.h>
#include <SD.h>

const int chipSelect = BUILTIN_SDCARD;


int32_t myPattern[8][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int32_t myVelocities[8][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int32_t myParameters[6][16] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.print("Initializing SD card...");
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    
    // don't do anything more:
    while (1);
  }
  Serial.println("card initialized.");

// format for drum pattern
  CSV_Parser cp(/*format*/ "LLLLLLLLLLLLLLLLLLLLLL", /*has_header*/ true, /*delimiter*/ ',');

  // The line below (readSDfile) wouldn't work if SD.begin wasn't called before.
  // readSDfile can be used as conditional, it returns 'false' if the file does not exist.
  if (cp.readSDfile("/PATTERNS/TESTDRUMPATTERN.CSV")) {

  // copy pattern to internal memory
    memcpy(myPattern[0],(int32_t*)cp["kk"], 64);
    memcpy(myPattern[1],(int32_t*)cp["s"], 64);
    memcpy(myPattern[2],(int32_t*)cp["c1"], 64);
    memcpy(myPattern[3],(int32_t*)cp["c2"], 64);
    memcpy(myPattern[4],(int32_t*)cp["g"], 64);
    memcpy(myPattern[5],(int32_t*)cp["d1"], 64);
    memcpy(myPattern[6],(int32_t*)cp["d2"], 64);
    memcpy(myPattern[7],(int32_t*)cp["d3"], 64);

  // copy velocities to internal memory
    memcpy(myVelocities[0],(int32_t*)cp["kv"], 64);
    memcpy(myVelocities[1],(int32_t*)cp["sv"], 64);
    memcpy(myVelocities[2],(int32_t*)cp["c1v"], 64);
    memcpy(myVelocities[3],(int32_t*)cp["c2v"], 64);
    memcpy(myVelocities[4],(int32_t*)cp["gv"], 64);
    memcpy(myVelocities[5],(int32_t*)cp["d1v"], 64);
    memcpy(myVelocities[6],(int32_t*)cp["d2v"], 64);
    memcpy(myVelocities[7],(int32_t*)cp["d3v"], 64);

  // copy digital voice parameters to internal memory
    memcpy(myParameters[0],(int32_t*)cp["d1p"], 64);
    memcpy(myParameters[1],(int32_t*)cp["d1pp"], 64);
    memcpy(myParameters[2],(int32_t*)cp["d2p"], 64);
    memcpy(myParameters[3],(int32_t*)cp["d2pp"], 64);
    memcpy(myParameters[4],(int32_t*)cp["d3p"], 64);
    memcpy(myParameters[5],(int32_t*)cp["d3pp"], 64);

//print out the pattern
    for (int i = 0 ; i < 16; i++){
      Serial.print(myPattern[0][i]);
      Serial.print(" ");
      Serial.print(myPattern[1][i]);
      Serial.print(" ");
      Serial.print(myPattern[2][i]);
      Serial.print(" ");
      Serial.print(myPattern[3][i]);
      Serial.print(" ");
      Serial.print(myPattern[4][i]);
      Serial.print(" ");
      Serial.print(myPattern[5][i]);
      Serial.print(" ");
      Serial.print(myPattern[6][i]);
      Serial.print(" ");
      Serial.println(myPattern[7][i]);
    }

//print out the velocities
    for (int i = 0 ; i < 16; i++){
      Serial.print(myVelocities[0][i]);
      Serial.print(" ");
      Serial.print(myVelocities[1][i]);
      Serial.print(" ");
      Serial.print(myVelocities[2][i]);
      Serial.print(" ");
      Serial.print(myVelocities[3][i]);
      Serial.print(" ");
      Serial.print(myVelocities[4][i]);
      Serial.print(" ");
      Serial.print(myVelocities[5][i]);
      Serial.print(" ");
      Serial.print(myVelocities[6][i]);
      Serial.print(" ");
      Serial.println(myVelocities[7][i]);
    }

//print out the digital voice parameters
    for (int i = 0 ; i < 16; i++){
      Serial.print(myParameters[0][i]);
      Serial.print(" ");
      Serial.print(myParameters[1][i]);
      Serial.print(" ");
      Serial.print(myParameters[2][i]);
      Serial.print(" ");
      Serial.print(myParameters[3][i]);
      Serial.print(" ");
      Serial.print(myParameters[4][i]);
      Serial.print(" ");
      Serial.println(myParameters[5][i]);
    }
    
    // output parsed values (allows to check that the file was parsed correctly)
//    cp.print(); // assumes that "Serial.begin()" was called before (otherwise it won't work)
    
  } else {
    Serial.println("ERROR: File called '/file.csv' does not exist...");
  }
}

void loop() {

}
