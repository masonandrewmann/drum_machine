#include <LittleFS.h>
#include <SD.h>

// Some variables for later use
uint64_t fTot, totSize1;

LittleFS_SPIFlash myfs;

// Since we are using SPI we need to tell the library what the chip select pin
#define chipSelectFlash 6  // use for access flash on audio or prop shield
#define chipSelectSD BUILTIN_SDCARD  // use for access flash on audio or prop shield


// Specifies that the file, file1 and file3 are File types, same as you would do for creating files
// on a SD Card
File myFileSD, myFileFlash;

void setup() {
  // put your setup code here, to run once:
    // Open serial communications and wait for port to open:
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
  myfs.quickFormat();
  Serial.println("LittleFS initialized.");

  // To get the current space used and Filesystem size
  Serial.println("\n---------------");
  Serial.printf("Bytes Used: %llu, Bytes Total:%llu\n", myfs.usedSize(), myfs.totalSize());
//  waitforInput();


  if (!SD.begin(chipSelectSD)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  //open file on SD that i want to copy to flash
  myFileSD = SD.open("SNARE.RAW");

  //open file on Flash chip to write to 
  myFileFlash = myfs.open("SNARE.RAW", FILE_WRITE);
  
  if(myFileSD){
    Serial.println("opened SNARE.RAW:");
    while(myFileSD.available()){
          //do smth with this sample
          char ch = myFileSD.read();
          myFileFlash.write(&ch, sizeof(ch));
    }
    
    myFileSD.close();
    myFileFlash.close();
    Serial.println("Closed SNARE.RAW");
  } else {
    Serial.println("error opening SNARE.RAW on SD card");
  }



////   Now lets create a file and write some data.  Note: basically the same usage for 
////   creating and writing to a file using SD library.
//  Serial.println("\n---------------");
//  Serial.println("Now lets create a file with some data in it");
//  Serial.println("---------------");
//  char someData[128];
//  memset( someData, 'z', 128 );
////  mySnare = myfs.open("bigfile.txt", FILE_WRITE);
//  mySnare.write(someData, sizeof(someData));
//
//  for (uint16_t j = 0; j < 100; j++)
//    mySnare.write(someData, sizeof(someData));
//  mySnare.close();

listFiles();

  
}

void loop() {
  // put your main code here, to run repeatedly:

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
