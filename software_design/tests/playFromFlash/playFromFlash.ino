#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
//#include <SerialFlash.h>
#include <LittleFS.h>
#include <TeensyVariablePlayback.h>


LittleFS_SPIFlash myfs;
// GUItool: begin automatically generated code
//AudioPlaySerialflashRaw  playFlashRaw1;  //xy=289,391
AudioPlayLfsResmp        playLFS1(myfs);     //xy=324,457

AudioOutputI2S           i2s1;           //xy=567,414
AudioConnection          patchCord1(playLFS1, 0, i2s1, 0);
AudioConnection          patchCord2(playLFS1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=475,235
// GUItool: end automatically generated code

// Some variables for later use
uint64_t fTot, totSize1;
unsigned long lastSamplePlayed = 0;

// Since we are using SPI we need to tell the library what the chip select pin
#define chipSelectFlash 6  // use for access flash on audio or prop shield
#define chipSelectSD BUILTIN_SDCARD  // use for access flash on audio or prop shield

// Specifies that the file, file1 and file3 are File types, same as you would do for creating files
// on a SD Card
File myFileSD, myFileFlash;

const char* _filename = "SNARE.RAW";

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    // wait for serial port to connect.
  }
  Serial.println("\n" __FILE__ " " __DATE__ " " __TIME__);

  Serial.print("Initializing LittleFS ...");

    // see if the Flash is present and can be initialized:
  // Note:  SPI is default so if you are using SPI and not SPI for instance
  //        you can just specify myfs.begin(chipSelect). 
  if (!myfs.begin(chipSelectFlash, SPI)) {
    Serial.printf("Error starting %s\n", "SPI FLASH");
    while (1) {
      // Error, so don't do anything more - stay stuck here
    }
  }

  Serial.println("LittleFS initialized.");

  sgtl5000_1.enable();
    playLFS1.enableInterpolation(true);
    playLFS1.setPlaybackRate(1.0);

    listFiles();
}

void loop() {
  
    unsigned currentMillis = millis();
    if (currentMillis > lastSamplePlayed + 500) {
      Serial.println(playLFS1.positionMillis());
        if (!playLFS1.isPlaying()) {
            playLFS1.playRaw("SNARE.RAW", 1);
            lastSamplePlayed = currentMillis;

            Serial.print("Memory: ");
            Serial.print(AudioMemoryUsage());
            Serial.print(",");
            Serial.print(AudioMemoryUsageMax());
            Serial.println();
        }
    }
    delay(10);
}

void listFiles()
{
  Serial.println("---------------");
  printDirectory(myfs);
  Serial.printf("Bytes Used: %llu, Bytes Total:%llu\n", myfs.usedSize(), myfs.totalSize());
}

void printDirectory(FS &fs) {
  Serial.println("Directory\n---------");
  printDirectory(fs.open("/"), 0);
  Serial.println();
}

void printDirectory(File dir, int numSpaces) {
   while(true) {
     File entry = dir.openNextFile();
     if (! entry) {
       //Serial.println("** no more files **");
       break;
     }
     printSpaces(numSpaces);
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numSpaces+2);
     } else {
       // files have sizes, directories do not
       printSpaces(36 - numSpaces - strlen(entry.name()));
       Serial.print("  ");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

void printSpaces(int num) {
  for (int i=0; i < num; i++) {
    Serial.print(" ");
  }
}

void waitforInput()
{
  Serial.println("Press anykey to continue");
  while (Serial.read() == -1) ;
  while (Serial.read() != -1) ;
}
