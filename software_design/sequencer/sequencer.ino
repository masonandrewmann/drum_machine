#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <LinkedList.h>
#include <CSV_Parser.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav5;     //xy=166,407
AudioPlaySdWav           playSdWav6;     //xy=166,463
AudioPlaySdWav           playSdWav3;     //xy=168,301
AudioPlaySdWav           playSdWav4;     //xy=169,355
AudioPlaySdWav           playSdWav1;     //xy=170,189
AudioPlaySdWav           playSdWav2;     //xy=170,246
AudioAmplifier           amp5;           //xy=313,410
AudioAmplifier           amp6;           //xy=313,467
AudioAmplifier           amp4;           //xy=315,357
AudioAmplifier           amp1;           //xy=321,189
AudioAmplifier           amp2;           //xy=321,246
AudioAmplifier           amp3;           //xy=321,301
AudioMixer4              mixer1;         //xy=513,246
AudioMixer4              mixer2;         //xy=695,329
AudioOutputI2S           i2s1;           //xy=886,311
AudioConnection          patchCord1(playSdWav5, 0, amp5, 0);
AudioConnection          patchCord2(playSdWav6, 0, amp6, 0);
AudioConnection          patchCord3(playSdWav3, 0, amp3, 0);
AudioConnection          patchCord4(playSdWav4, 0, amp4, 0);
AudioConnection          patchCord5(playSdWav1, 0, amp1, 0);
AudioConnection          patchCord6(playSdWav2, 0, amp2, 0);
AudioConnection          patchCord7(amp5, 0, mixer2, 1);
AudioConnection          patchCord8(amp6, 0, mixer2, 2);
AudioConnection          patchCord9(amp4, 0, mixer1, 3);
AudioConnection          patchCord10(amp1, 0, mixer1, 0);
AudioConnection          patchCord11(amp2, 0, mixer1, 1);
AudioConnection          patchCord12(amp3, 0, mixer1, 2);
AudioConnection          patchCord13(mixer1, 0, mixer2, 0);
AudioConnection          patchCord14(mixer2, 0, i2s1, 0);
AudioConnection          patchCord15(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=631,613
// GUItool: end automatically generated code

enum playStates{
  Stopped,
  Playing,
  Paused,
};

class Pattern {
  public:
    int32_t pattern[8][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    float velocity[8][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int32_t parameter[6][16] = {
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int sdChipSelect = BUILTIN_SDCARD;

    Pattern(){
    }

    void readFromSD(const char* path){
//      if (!SD.begin(sdChipSelect)) {
//        Serial.println("Card failed, or not present");
//      }

      // format for drum pattern
      CSV_Parser cp(/*format*/ "LfLfLfLfLfLfLLLfLLLfLL", /*has_header*/ true, /*delimiter*/ ',');

      if (cp.readSDfile(path)) {

      // copy pattern to internal memory
        memcpy(pattern[0],(int32_t*)cp["kk"], 64);
        memcpy(pattern[1],(int32_t*)cp["s"], 64);
        memcpy(pattern[2],(int32_t*)cp["c1"], 64);
        memcpy(pattern[3],(int32_t*)cp["c2"], 64);
        memcpy(pattern[4],(int32_t*)cp["g"], 64);
        memcpy(pattern[5],(int32_t*)cp["d1"], 64);
        memcpy(pattern[6],(int32_t*)cp["d2"], 64);
        memcpy(pattern[7],(int32_t*)cp["d3"], 64);
    
      // copy velocities to internal memory
        memcpy(velocity[0],(int32_t*)cp["kv"], 64);
        memcpy(velocity[1],(int32_t*)cp["sv"], 64);
        memcpy(velocity[2],(int32_t*)cp["c1v"], 64);
        memcpy(velocity[3],(int32_t*)cp["c2v"], 64);
        memcpy(velocity[4],(int32_t*)cp["gv"], 64);
        memcpy(velocity[5],(int32_t*)cp["d1v"], 64);
        memcpy(velocity[6],(int32_t*)cp["d2v"], 64);
        memcpy(velocity[7],(int32_t*)cp["d3v"], 64);
    
      // copy digital voice parameters to internal memory
        memcpy(parameter[0],(int32_t*)cp["d1p"], 64);
        memcpy(parameter[1],(int32_t*)cp["d1pp"], 64);
        memcpy(parameter[2],(int32_t*)cp["d2p"], 64);
        memcpy(parameter[3],(int32_t*)cp["d2pp"], 64);
        memcpy(parameter[4],(int32_t*)cp["d3p"], 64);
        memcpy(parameter[5],(int32_t*)cp["d3pp"], 64);
      }

      
    }

    void printPattern(){
//      //print out the pattern
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 8; j++){
        Serial.print(pattern[j][i]);
        Serial.print(" ");
        }
        Serial.println(" ");
      }
  
      //print out the velocities
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 8; j++){
          Serial.print(velocity[j][i]);
          Serial.print(" "); 
        }
        Serial.println(" ");
      }
//  
//      //print out the digital voice parameters
      for (int i = 0 ; i < 16; i++){
        for (int j = 0; j < 6; j++){
        Serial.print(parameter[j][i]);
        Serial.print(" ");
        }
      Serial.println(" ");
      }
    }
};


bool lastButtons[4][8];
bool currButtons[4][8];
    // MUX 0 : steps 1 - 8
    // MUX 1 : steps 9 - 16
    // MUX 2 :
        // 0 - inst sel
        // 1 - save 
        // 2 - shift
        // 3 - song
        // 4 - pattern
        // 5 - bank
        // 6 - play/pause
        // 7 - stop
    // MUX 3 : 
        // 0 - pattern back
        // 1 - pattern forwards
        // 2 - 
        // 3 - 
        // 4 - 
        // 5 - 
        // 6 - 
        // 7 - 

int analogMux[8];        
    // MUX 4 : 
        // 0 - Voice 5 Parameter
        // 1 - Voice 6 Parameter
        // 2 - Voice 7 Parameter
        // 3 - Voice 8 Parameter
        // 4 - Voice 5 Volume
        // 5 - Voice 6 Volume
        // 6 - Voice 7 Volume
        // 7 - Voice 8 Volume

byte muxAdrPins[3] = {0, 1, 2};
byte analogMuxAdr = 7;
byte muxDataPins[4] = {3, 4, 5, 6};

bool ledStates[4][8];
  // SR1 : steps 1 - 8
  // SR2 : steps 9 - 16
  // SR3 :         
        // 0 - 
        // 1 - 
        // 2 - 
        // 3 - 
        // 4 - 
        // 5 - 
        // 6 - 
        // 7 - 
  // SR4 :         
        // 0 - 
        // 1 - 
        // 2 - 
        // 3 - 
        // 4 - 
        // 5 - 
        // 6 - 
        // 7 - 

byte trigOutPins[8];



// Use these with the Teensy 3.5 & 3.6 SD card
#define SDCARD_CS_PIN    BUILTIN_SDCARD
#define SDCARD_MOSI_PIN  11  // not actually used
#define SDCARD_SCK_PIN   13  // not actually used

#define GRANULAR_MEMORY_SIZE 12800  // enough for 290 ms at 44.1 kHz
int16_t granularMemory[GRANULAR_MEMORY_SIZE];

long lastTrig = 0;

Pattern MyPattern;

float tempo = 120;
unsigned int stepLen = 0;
unsigned int currStep = 0;
unsigned long currStepTime = 0;
int pulseLength = 20; // 10 ms pulses
int playState = Playing;

int currInst = 0;
  // 0 : Kick
  // 1 : Snare

  //SHIFT REGISTER PINS

//Pin SH_CP
byte SH_CP = 10;
//In pin ST_CP
byte ST_CP = 9;
//DS pin
byte DS = 8;


//class for keeping track of output pulses
class Pulse {
  public:
    byte pinNum;
    unsigned long endTime;
};

LinkedList <Pulse*> myPulseList = LinkedList<Pulse*>();

void setup() {

  Serial.begin(9600);

  AudioMemory(8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);

  //initialize button state arrays
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 8; j++){
      currButtons[i][j] = 0;
      lastButtons[i][j] = 0;
    }
  }

// set up the shift register pins
   pinMode(SH_CP, OUTPUT);
   pinMode(ST_CP, OUTPUT);
   pinMode(DS, OUTPUT);

// set up the multiplexer address pins
   for (int i = 0; i < sizeof(muxAdrPins) / sizeof(byte); i++){
      pinMode(muxAdrPins, OUTPUT);
   }
   
// set up the multiplexer data pins
   for (int i = 0; i < sizeof(muxDataPins) / sizeof(byte); i++){
      pinMode(muxDataPins, INPUT);
   }



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
  mixer1.gain(3, 0.5);
  
  mixer2.gain(0, 0.5);
  mixer2.gain(1, 0.5);
  mixer2.gain(2, 0.5);
  mixer2.gain(3, 0.5);

  amp1.gain(1.0);
  amp2.gain(1.0);
  amp3.gain(1.0);
  amp4.gain(1.0);
  amp5.gain(1.0);
  amp6.gain(1.0);

  
  delay(1000);
  changeTempo(120);

  MyPattern.readFromSD("/PATTERNS/TESTDRUMPATTERN.CSV");
  MyPattern.printPattern();

  writePatternToSD(MyPattern, "PATTERNS/TESTDRUMPATTERN_COPY.TXT");
}

void loop() {

//  readAllMux(false);
//  checkButtonPress();
//  updateButtonArray();


  // steps
  if(playState == Playing){
    if (millis() > (currStepTime  + stepLen)){ // new step has been reached
      currStep = (currStep + 1) % 16; // move step pointer to next step
//      clockOutput(); //send clock signal out external output
      for(int i = 0; i < sizeof(MyPattern.pattern[0])/sizeof(MyPattern.pattern[0][0]); i++){ //send triggers of all instruments to be played at this step
        if(MyPattern.pattern[i][currStep]){
          trigNote(i, MyPattern.velocity[i][currStep]/127.0);
        }
      }
  
      currStepTime = millis();
    }
  }

}

///**************************************************************************************************
// * Function changeTempo
// * -------------------------------------------------------------------------------------------------
// * Overview: moves contents of currButtons[][] array to lastButtons[][]
// * Input: 
// *    float newTempo : tempo to update to
// * Output: Nothing
// **************************************************************************************************/
void changeTempo(float newTempo){
  tempo = newTempo;
  float quarterLen = (60.0 / tempo) * 1000;
  float eigthLen = quarterLen / 2;
  float sixteenthLen = quarterLen / 4;
  stepLen = sixteenthLen;
}



///**************************************************************************************************
// * Function trigNote
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an note is triggered
// * Input: 
// *    int instNum : number of the instrument being triggered
// * Output: Nothing
// **************************************************************************************************/
void trigNote(int instNum, float velocity){
//  Serial.print(currStep);
//  Serial.print(": inst ");
////  Serial.println("KICK");
//  Serial.println(instNum);

switch(instNum){
  case 0: 
//    Serial.println("KICK");
    playSdWav1.play("DRUMS/KICK.WAV");
    amp1.gain(velocity);
    break;
  
  case 1:
//    Serial.println("HAT");
    playSdWav2.play("DRUMS/SNARE.WAV");
    amp2.gain(velocity);
    break;

  case 2:
//    Serial.println("SNARE");
    playSdWav3.play("DRUMS/CH.WAV");
    amp3.gain(velocity);
    break;

  case 3:
//    Serial.print("OH ");
//    Serial.println(velocity);
    playSdWav4.play("DRUMS/ee.WAV");
    amp4.gain(velocity);
    break;

  case 4: 
//    Serial.println("KICK");
    playSdWav5.play("DRUMS/ee.WAV");
    amp1.gain(velocity);
    break;
  
  case 5:
//    Serial.println("HAT");
    playSdWav6.play("DRUMS/CH.WAV");
    amp2.gain(velocity);
    break;

}
  
}


///**************************************************************************************************
// * Function selectMuxPin
// * -------------------------------------------------------------------------------------------------
// * Overview: writes microcontroller's defined MUX address pins to a specific address
// *          NOTE: Be sure to give time for signal to propogate before reading data pin
// * Input:
// *    byte address : address on multiplexer to connect to data pin
// * Output: Nothing
// **************************************************************************************************/
void selectMuxPin(byte address) {
  for (int i = 0; i < 3; i++) {
    if (address & (1 << i))
      digitalWrite(muxAdrPins[i],  HIGH);
    else
      digitalWrite(muxAdrPins[i],  LOW);
  }
}

///**************************************************************************************************
// * Function readAllMux
// * -------------------------------------------------------------------------------------------------
// * Overview: reads all the multiplexers and puts them in the currButtons array
// * Input:
// *    bool printEn : prints arrays to serial monitor when true
// * Output: Nothing
// **************************************************************************************************/
void readAllMux(bool printEn){
  
  for (int i = 0; i < 8; i = i){ //loop through all MUX addresses
    selectMuxPin(i);
    delay(2); // give time for signal to propogate through mux before reading
    for (int j = 0; j< sizeof(muxDataPins)/sizeof(int); j++){ // read from each MUX data pin
      currButtons [j][i] = digitalRead(muxAdrPins[j]);
    }
    analogMux[i] = analogRead(analogMuxAdr);
    i++;
  }
  
  if (printEn){ // print 
    for (int i = 0; i < sizeof(muxDataPins)/sizeof(int); i++){
      for (int j = 0; j < 8; j++){
        Serial.print(currButtons[i][j]);
        Serial.print(" ");
      }
      Serial.print(" ||| ");
    }
    Serial.println(" ");
  }
}

///**************************************************************************************************
// * Function updateButtonArray
// * -------------------------------------------------------------------------------------------------
// * Overview: moves contents of currButtons[][] array to lastButtons[][]
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
void updateButtonArray(){
  for (int i = 0; i < 3; i++){
    for (int j = 0; j < 8; j++){
      currButtons[i][j] = lastButtons[i][j];
    }
  }
}

///**************************************************************************************************
// * Function checkButtonPress
// * -------------------------------------------------------------------------------------------------
// * Overview: checks if buttons have been pressed and might do things on these presses
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
void checkButtonPress(){
  for (int i = 0; i < 2; i++){ // check the step buttons 
    for (int j = 0; j < 8; j++){
      if (currButtons[i][j] =! lastButtons[i][j]){ // check if button changed states
        if(currButtons[i][j] == true){ //button pressed

          //check modifiers 
          if (currButtons[2][0]){ // instrument select modifier
            if (i == 0){
              currInst = j;
            } else if (i == 1){
              currInst = j + 1;
            }
          }
        } else {

          switch(i){
            case 0:// step buttons 1 - 8
//              myPattern[i][j] = !analogMuxAdr[currInst][j];
              break;

            case 1: // step buttons 9 - 16
//              analogMuxAdr[i][j] = !analogMuxAdr[currInst][j + 8];
              break;

            case 2: // first set of control buttons
              switch(j){
                case 0: // instrument select
                  break;

                case 1: // save
                  break;

                case 2: // shift
                  break;

                case 3: // song
                  break;

                case 4: // pattern
                  break;

                case 5: // bank
                  break;

                case 6: // play/pause
//                  if (playState == Playing){
//                    playState = Paused;
//                  } else if ( playState == Paused || playState == Stopped){
//                        for(int i = 0; i < 8; i++){ //send triggers of all instruments to be played at this step
//                          if(stepBool[i][currStep]){
//                            trigNote(i);
//                          }
//                        }
//                        currStepTime = millis();
//                  }
//                  
                  break;

                case 7: // stop
                  playState = Stopped;
                  currStep = 0;
                  break;
              }

          }
          
        }
          } else if (currButtons[i][j] == false){ //button released
            //insert button released code
          }
        } 
      }
  }

/////**************************************************************************************************
//// * Function writeAllLEDs
//// * -------------------------------------------------------------------------------------------------
//// * Overview: prints currently selected drum pattern to the Serial Monitor
//// * Input: Nothing
//// * Output: Nothing
//// **************************************************************************************************/
//void printPattern(){ //
//  Serial.println("======== PATTERN BEGIN ========");
//  for (int i = 0; i < 8; i++){
//    for (int j = 0; j < 16; j++){
//      Serial.print(myPattern[i][j]);
//      Serial.print(" ");
//    }
//    Serial.println(" ");
//  }
//  Serial.println("======== PATTERN END ========");
//}


///**************************************************************************************************
// * Function writeAllLEDs
// * -------------------------------------------------------------------------------------------------
// * Overview: writes contents of ledStates[][] array to the shift registers
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
void writeAllLEDs(){
  byte byte0 = 0;
  byte byte1 = 0;
  byte byte2 = 0;
  byte byte3 = 0;
  
  digitalWrite(ST_CP, LOW);
  
  //prepare byte for first shift register
  bool ledStates[4][8];
  for (int i = 7;i > -1; i--){
    byte0 += (ledStates[0][i] << i);
    byte1 += (ledStates[1][i] << i);
    byte2 += (ledStates[2][i] << i);
    byte3 += (ledStates[3][i] << i);
  }
  shiftOut(DS, SH_CP, MSBFIRST, byte0);
  shiftOut(DS, SH_CP, MSBFIRST, byte1);
  shiftOut(DS, SH_CP, MSBFIRST, byte2);
  shiftOut(DS, SH_CP, MSBFIRST, byte3);
  
  digitalWrite(ST_CP, HIGH);
}

///**************************************************************************************************
// * Function clockOutput
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an clock step is reached
// * Input: 
// * Output: Nothing
// **************************************************************************************************/
void clockOutput(){
  Serial.println("CLOCK STEP");
}

// how to write all LEDs
// digitalWrite(ST_CP, LOW);
// shiftOut(DS, SH_CP, MSBFIRST, 0b10000000);
// /* more calls to shiftOut here for daisychained shift registers */
// digitalWrite(ST_CP, HIGH);



///**************************************************************************************************
// * Function startPulse
// * -------------------------------------------------------------------------------------------------
// * Overview: Begin an output pulse on specified pin
// * Input: 
// *        byte pinNumber : pin to send ouput pulse on
// * Output: 
// **************************************************************************************************/
void startPulse(byte pinNumber){
  digitalWrite(pinNumber, HIGH);
  
  Pulse *myPulse = new Pulse();
  myPulse -> pinNum = pinNumber;
  myPulse -> endTime = millis() + pulseLength;

  myPulseList.add(myPulse);
}


///**************************************************************************************************
// * Function checkPulses
// * -------------------------------------------------------------------------------------------------
// * Overview: Check if any output triggers are high and check if they should be lowered
// * Input: 
// * Output: 
// **************************************************************************************************/
void checkPulses(){
  Pulse *myPulse;
  int i;
  
  if (myPulseList.size() > 0){
    for (i = 0; i < myPulseList.size(); i++){
      myPulse = myPulseList.get(i);
      unsigned long timeCheck = myPulse -> endTime;
      if (millis() > timeCheck){
        digitalWrite(myPulse->pinNum, LOW);
        break;
      }
    }
    myPulseList.remove(i); 
  }
}

///**************************************************************************************************
// * Function writePatternToSD
// * -------------------------------------------------------------------------------------------------
// * Overview: Writes a Pattern object to a csv file on SD card
// * Input: 
//          patt: Pattern object to be written to SD Card
//          path: path on SD card to write object to ( in format 'FILEPATH/NAME.TXT'
// * Output: 
// **************************************************************************************************/
void writePatternToSD(Pattern &patt, const char* path)
{
  //clear out old data file
  if (SD.exists(path)) 
  {
    Serial.println("Removing old csv");
    SD.remove(path);
    Serial.println("Done");
  } 

  //create new file
  File myFile = SD.open(path, FILE_WRITE);
  if (myFile){
    Serial.println("Writing headers to new CSV");
    myFile.println("kk,kv,s,sv,c1,c1v,c2,c2v,g,gv,d1,d1v,d1p,d1pp,d2,d2v,d2p,d2pp,d3,d3v,d3p,d3pp");
    Serial.println("Headers written");

    //writing data
    for (int i = 0; i < 16; i++){
      myFile.print(patt.pattern[0][i]); //KICK
      myFile.print(",");
      myFile.print(patt.velocity[0][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[1][i]); //SNARE
      myFile.print(",");
      myFile.print(patt.velocity[1][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[2][i]); //CYNARE 1
      myFile.print(",");
      myFile.print(patt.velocity[2][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[3][i]); //CCYNARE 2
      myFile.print(",");
      myFile.print(patt.velocity[3][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[4][i]); // GLITCH
      myFile.print(",");
      myFile.print(patt.velocity[4][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[5][i]); // DIGITAL VOICE 1
      myFile.print(",");
      myFile.print(patt.velocity[5][i]);
      myFile.print(",");
      myFile.print(patt.parameter[0][i]);
      myFile.print(",");
      myFile.print(patt.parameter[1][i]);
      myFile.print(",");
      
      myFile.print(patt.pattern[6][i]); // DIGITAL VOICE 2
      myFile.print(",");
      myFile.print(patt.velocity[6][i]);
      myFile.print(",");
      myFile.print(patt.parameter[2][i]);
      myFile.print(",");
      myFile.print(patt.parameter[3][i]);
      myFile.print(",");

      myFile.print(patt.pattern[7][i]); // DIGITAL VOICE 3
      myFile.print(",");
      myFile.print(patt.velocity[7][i]);
      myFile.print(",");
      myFile.print(patt.parameter[4][i]);
      myFile.print(",");
      myFile.println(patt.parameter[5][i]);
  }

  myFile.close(); 
}
}
