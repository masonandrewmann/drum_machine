//#include <LinkedList.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
//#include <SerialFlash.h>
#include <CSV_Parser.h>
#include <U8g2lib.h>
#include "frames.h"
#include "Pattern.h"

//#define DEMO 1

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_DC 25
#define LCD_CS 10
#define LCD_RST 24

#define SDCARD_CS_PIN    BUILTIN_SDCARD



enum instruments{
  INST_BD,
  INST_SD,
  INST_CYN1,
  INST_CYN2,
  INST_GLITCH,
  INST_DIGI1,
  INST_DIGI2,
  INST_DIGI3,
  
  INST_DIGI4, 
  INST_DIGI5,
  INST_DIGI6, 
  INST_DIGI7,
  INST_DIGI8,
  INST_DIGI9,
  INST_DIGI10,
  INST_DIGI11
};

enum transportStates{
  STOPPED,
  PLAYING,
  PAUSED,
};

enum controlStates{
  STEP_SEL,
  INST_SEL,
  PATTERN_SEL,
  SONG_SEL,
  BANK_SEL
};

enum ledDisplayStates{
  DISP_STEPS,
  DISP_PATTERNS
};


//------EXTERNAL QSPI RAM CHIP SECTION BEGIN------
EXTMEM Pattern PatternStorage[16][16] ;
//------EXTERNAL QSPI RAM CHIP SECTION END------

//Pattern variables
Pattern* currPattern;
Pattern MyPattern;
int patternNum = 1;
int nextPattern = 1;
int patternQueue[16];
int patternQueueLen = 1;
int patternQueueIndex = 0;
int patternQueueWriteIndex = 0;

// GUItool: begin automatically generated code
AudioSynthSimpleDrum     drum3;          //xy=123,598
AudioSynthSimpleDrum     drum2;          //xy=126,556
AudioSynthSimpleDrum     drum1;          //xy=133,508
AudioPlaySdWav           playSdWav5;     //xy=180,303
AudioPlaySdWav           playSdWav4;     //xy=184,245
AudioPlaySdWav           playSdWav6;     //xy=188,351
AudioPlaySdWav           playSdWav7;     //xy=188,398
AudioPlaySdWav           playSdWav3;     //xy=189,202
AudioPlaySdWav           playSdWav2;     //xy=192,162
AudioPlaySdWav           playSdWav8;     //xy=192,449
AudioPlaySdWav           playSdWav1;     //xy=198,114
AudioMixer4              mixer4;         //xy=309,560
AudioMixer4              mixer1;         //xy=408,156
AudioMixer4              mixer2;         //xy=413,305
AudioMixer4              mixer3;         //xy=600,264
AudioOutputI2S           i2s1;           //xy=726,266
AudioConnection          patchCord1(drum3, 0, mixer4, 2);
AudioConnection          patchCord2(drum2, 0, mixer4, 1);
AudioConnection          patchCord3(drum1, 0, mixer4, 0);
AudioConnection          patchCord4(playSdWav5, 0, mixer2, 0);
AudioConnection          patchCord5(playSdWav4, 0, mixer1, 3);
AudioConnection          patchCord6(playSdWav6, 0, mixer2, 1);
AudioConnection          patchCord7(playSdWav7, 0, mixer2, 2);
AudioConnection          patchCord8(playSdWav3, 0, mixer1, 2);
AudioConnection          patchCord9(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord10(playSdWav8, 0, mixer2, 3);
AudioConnection          patchCord11(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord12(mixer4, 0, mixer3, 2);
AudioConnection          patchCord13(mixer1, 0, mixer3, 0);
AudioConnection          patchCord14(mixer2, 0, mixer3, 1);
AudioConnection          patchCord15(mixer3, 0, i2s1, 0);
AudioConnection          patchCord16(mixer3, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=815,326
// GUItool: end automatically generated code


//transport variables
float tempo = 120;
unsigned int stepLen = 0;
unsigned int currStep = 0;
unsigned long currStepTime = 0;

int transportState = PLAYING;
int currInst = INST_BD;
int controlState = STEP_SEL;
int ledDisplayState = DISP_STEPS;

//Contact SH_CP - Clock
int SH_CP = 31;
//Contact ST_CP - Latch
int ST_CP = 32;
//Contact DS - Data
int DS = 30;

int inputs[8][8];                 //reading button inputs
int inputsPrev[8][8];
int muxAddressPins[3] = {15, 16, 17};
int muxDataPins[7] = {14, 39, 38, 33, 40, 41, 22};

int stepButtons[16];
int stepButtonsPrev[16];

int controlButtons[16];
int controlButtonsPrev[16];

float controlPots[16];


bool sr0LED[8];
bool sr1LED[8];
bool sr2LED[8];
bool sr3LED[8];
bool stepLEDs[16];


//linked list for handling output pulse timing
unsigned long outPulseTimes[16];


//ROTARY ENCOCDER SETUP
// tempo encoder phase A pin
static const int tempoEncBPin =34;
// tempo encoder phase B pin
static const int tempoEncAPin = 35;

// data encoder phase A pin
static const int dataEncBPin = 29;
// ddata encoder phase B pin
static const int dataEncAPin = 28;


// Rotary encoder variables, used by interrupt routines
volatile int tempoEncState = 0;
volatile int tempoEncAval = 1;
volatile int tempoEncBval = 1;
volatile int tempoEncAcc = 0;

volatile int dataEncState = 0;
volatile int dataEncAval = 1;
volatile int dataEncBval = 1;
volatile int dataEncAcc = 0;

//LCD stuff
unsigned long LCDFrameTimer = 0;
int starsFrameCount = 0;
U8G2_PCD8544_84X48_F_4W_HW_SPI u8g2(U8G2_R2, LCD_CS, LCD_DC, LCD_RST);
//u8g2_t u8g2;
 int xx;

//nonblocking mux reading
unsigned long muxTimer = 0;
int muxIndex = 0;
bool muxCpltFlg = false;
bool muxTimerFlg = false;


void setup() {
  Serial.begin(115200);
  Serial.print("Hellooo: ");
  
  u8g2.begin();
  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  
  //setup for shift register
  pinMode(SH_CP, OUTPUT); // clock pin
  pinMode(ST_CP, OUTPUT); // latch
  pinMode(DS, OUTPUT);    // data pin

  //flash setup
  //----SD CARD setup
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
      Serial.println("Unable to access the SD card, fix the problem and restart!");
  }
//  //----FLASH CHIP Setup
//  if (!SerialFlash.begin(flashChipSelect)) {
//    Serial.println("Unable to access SPI Flash chip");
//  }

  mixer1.gain(0, 0.2);
  mixer1.gain(1, 0.2);
  mixer1.gain(2, 0.2);
  mixer2.gain(0, 0.2);
  mixer2.gain(1, 0.2);
  mixer2.gain(2, 0.2);

  //digital drum initialization
  drum1.frequency(60);
  drum1.length(1500);
  drum1.secondMix(0.0);
  drum1.pitchMod(0.55);

  drum2.frequency(60);
  drum2.length(300);
  drum2.secondMix(0.0);
  drum2.pitchMod(1.0);
  
  drum3.frequency(550);
  drum3.length(400);
  drum3.secondMix(1.0);
  drum3.pitchMod(0.5);
  
  //initialize MUX address pins
  for (int i = 0; i < sizeof(muxAddressPins)/sizeof(muxAddressPins[0]); i++){
    pinMode(muxAddressPins[i], OUTPUT);
  }

  //initialize MUX data pins
  for (int i = 0; i < sizeof(muxDataPins)/sizeof(muxDataPins[0]); i++){
    pinMode(muxDataPins[i], INPUT);
  }

  //initialize serial communication


  for (int i = 0; i < 16; i++){
    stepButtons[i] = 0;
    stepButtonsPrev[i] = 0; 
    outPulseTimes[i] = 0;
    stepLEDs[i] = 1;
    patternQueue[i] = 0;
    controlPots[i] = 0;
  }

  for (int i = 0; i < 8; i ++){
    sr0LED[i] = 1;
    sr1LED[i] = 1;
    sr2LED[i] = 1;
    sr3LED[i] = 1;
  }
  sr1LED[2] = 0;
  
  changeTempo(tempo);

  //rotary encoder setup
  pinMode(tempoEncAPin, INPUT);
  pinMode(tempoEncBPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(tempoEncAPin), 
  ISRtempoEncAChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(tempoEncBPin), 
  ISRtempoEncBChange, CHANGE);

  pinMode(dataEncAPin, INPUT);
  pinMode(dataEncBPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(dataEncAPin), 
    ISRdataEncAChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dataEncBPin), 
    ISRdataEncBChange, CHANGE);


    //load patterns from SD Card
    Serial.println("Reading patterns from SD");
    PatternStorage[0][0].readFromSD("/PATTERNS/A/1.CSV");
    PatternStorage[0][1].readFromSD("/PATTERNS/A/2.CSV");
    PatternStorage[0][2].readFromSD("/PATTERNS/A/3.CSV");
    PatternStorage[0][3].readFromSD("/PATTERNS/A/4.CSV");
    PatternStorage[0][4].readFromSD("/PATTERNS/A/5.CSV");
    PatternStorage[0][5].readFromSD("/PATTERNS/A/6.CSV");
    PatternStorage[0][6].readFromSD("/PATTERNS/A/7.CSV");
    PatternStorage[0][7].readFromSD("/PATTERNS/A/8.CSV");

    PatternStorage[0][8].readFromSD("/PATTERNS/A/9.CSV");
    PatternStorage[0][9].readFromSD("/PATTERNS/A/10.CSV");
    PatternStorage[0][10].readFromSD("/PATTERNS/A/11.CSV");
    PatternStorage[0][11].readFromSD("/PATTERNS/A/12.CSV");
    PatternStorage[0][12].readFromSD("/PATTERNS/A/13.CSV");
    PatternStorage[0][13].readFromSD("/PATTERNS/A/14.CSV");
    PatternStorage[0][14].readFromSD("/PATTERNS/A/15.CSV");
    PatternStorage[0][15].readFromSD("/PATTERNS/A/16.CSV");
    Serial.println("Done reading patterns!");

    
  currPattern = &PatternStorage[0][0];
  patternNum = 0;
//  MyPattern.readFromSD("/PATTERNS/SIXTEENPATTERNTEST.CSV");
//  MyPattern.printPattern();
//  MyPattern.writePatternToSD("/PATTERNS/MYTESTWRITE.CSV");

//  currPattern->readFromSD("/PATTERNS/A/1.CSV");
  currPattern->printPattern();

//  MyPattern.readFromSD("/PATTERNS/MYTESTWRITE.CSV");
//  MyPattern.printPattern();
//  MyPattern.writePatternToSD("/PATTERNS/MYTESTWRITE2.CSV");

  currStepTime = millis();
}

void loop() {
  //brute force LCD
  if(millis() > LCDFrameTimer + 500){
  u8g2.clearBuffer();          // clear the internal memory
   switch (starsFrameCount){
      case 0:
        u8g2.drawXBMP(0,0, 84, 48, frame1);
        starsFrameCount = 1;
        break;
      case 1:
        u8g2.drawXBMP(0,0, 84, 48, frame2);
        starsFrameCount = 0;
        break;
   }
   u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
//  u8g2.drawStr(0,11,"Hello Worldo!");  // write something to the internal memory
//  u8g2.drawStr(20,30," <3");  // write something to the internal memory
  u8g2.drawStr(40,44,"drums!");  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  LCDFrameTimer = millis();
  }
  
  readMux(false);
  
  // steps
  if(transportState == PLAYING){
    if (millis() > (currStepTime  + stepLen)){ // new step has been reached
      if(currStep == 15){
        patternQueueIndex = (patternQueueIndex + 1) % patternQueueLen;
        currPattern = &PatternStorage[0][patternQueue[patternQueueIndex]];
        patternNum = patternQueue[patternQueueIndex];
      }
      currStep = (currStep + 1) % 16; // move step pointer to next step
      
//      clockOutput(); //send clock signal out external output
      for(int i = 0; i < 16; i++){ //send triggers of all instruments to be played at this step
        if(currPattern->pattern[i][currStep]){
          trigNote(i);
        }
      }
      currStepTime = currStepTime  + stepLen;
    }
  }

  for (int i = 0; i < 16; i++){
    if (outPulseTimes[i] != 0){
      if(millis() > outPulseTimes[i]){
//        Serial.println("PULSE COMPLETE");
        outPulseTimes[i] = 0;
            switch(i){
              case 0:
                sr3LED[7] = 1;
                break;
          
              case 1:
                sr2LED[2] = 1;
                break;
          
              case 2:
                sr0LED[0] = 1;
                break;
          
              case 3:
                sr0LED[7] = 1;
                break;
          
              case 4:
                sr2LED[4] = 1;
                break;
          
              case 5:
                sr2LED[7] = 1;
                break;
          
              case 6:
                sr2LED[6] = 1;
                break;
          
              case 7:
                sr2LED[5] = 1;
                break;
            }
      }
    }
  }
}



void readMux(bool printEn){

  if (!muxCpltFlg){ //mux not done being read
    //loop through and read all mux values
//    for (int i = 0; i < 8; i++){
      if(!muxTimerFlg){ //set pin on mux and set internal timer to wait for signal to propogate before reading
        selectMuxPin(muxIndex);
        muxTimerFlg = true;
        muxTimer = millis() + 2;
      }
      
//      delay(2); // give time for signal to propogate through mux before reading
      if( millis() > muxTimer){ // timer is up, we are OK to read from mux!
        muxTimerFlg = false; //reset mux timer flag
        for (int j = 0; j < 7; j++){ //read from the muxs
          if (j == 4 ||  j == 5){
            inputs[j][muxIndex] = analogRead(muxDataPins[j]);
          } else {
            inputs[j][muxIndex] = digitalRead(muxDataPins[j]);
          }
        }

        if(muxIndex == 7){ //if we've read all indices move to processing
          muxCpltFlg = true;
          muxIndex = 0;
        } else{ //if we havent read all indices move to the next index
          muxIndex++;
        }
    }
  }

  if (muxCpltFlg){ //all MUX addresses read!
    muxCpltFlg = false;
    //shift current stepButtons values to the stepButtonsPrev array
    for (int i = 0; i < 16; i++){
      stepButtonsPrev[i] = stepButtons[i];
    }
  
    //grab current stepButtons values from mux input array
    stepButtons[0] = inputs[0][0];
    stepButtons[1] = inputs[0][1];
    stepButtons[2] = inputs[0][2];
    stepButtons[3] = inputs[0][3];
    stepButtons[4] = inputs[1][0];
    stepButtons[5] = inputs[1][1];
    stepButtons[6] = inputs[1][2];
    stepButtons[7] = inputs[1][3];
    
    stepButtons[8] = inputs[0][4];
    stepButtons[9] = inputs[0][5];
    stepButtons[10] = inputs[0][6];
    stepButtons[11] = inputs[0][7];
    stepButtons[12] = inputs[1][4];
    stepButtons[13] = inputs[1][5];
    stepButtons[14] = inputs[1][6];
    stepButtons[15] = inputs[1][7];
  
    //shift current controlButtons values to the controlButtonsPrev array
    for (int i = 0; i < 16; i++){
      controlButtonsPrev[i] = controlButtons[i];
    }
    
    //grab control buttons and place in array
    controlButtons[0] = inputs[2][0]; // inst sel
    controlButtons[1] = inputs[2][1]; // save
    controlButtons[2] = inputs[2][2]; // shift
    controlButtons[3] = inputs[2][3]; // song
    controlButtons[4] = inputs[2][4]; // mute
    controlButtons[5] = inputs[2][5]; // pattern
    controlButtons[6] = inputs[3][2]; // dataEncBut
    controlButtons[7] = inputs[3][3]; // tempoEncBut
    controlButtons[8] = inputs[3][4]; // bank
    controlButtons[9] = inputs[3][5]; // step
    controlButtons[10] = inputs[6][0]; // beatRep1
    controlButtons[11] = inputs[6][1]; // beatRep2
    controlButtons[12] = inputs[6][2]; // playpause
    controlButtons[13] = inputs[6][3]; // stop
    controlButtons[14] = inputs[6][5]; // forwards
    controlButtons[15] = inputs[6][6]; // back

    //grab analog values and place in array
    controlPots[0] = inputs[4][0]; //digi 1 param
    controlPots[1] = inputs[4][1]; //digi 1 vol
    controlPots[2] = inputs[4][2]; //digi 2 param
    controlPots[3] = inputs[4][3]; //digi 2 vol
    controlPots[4] = inputs[4][5]; //digi 3 param
    controlPots[5] = inputs[4][4]; //digi 3 vol
    controlPots[6] = inputs[4][6]; //break vol
    controlPots[7] = inputs[5][0]; //break chaos
    controlPots[8] = inputs[5][3]; //break pitch
    controlPots[9] = inputs[5][1]; //repeat
    controlPots[10] = inputs[5][4]; //swing
    controlPots[11] = inputs[4][7]; //analog aux in 1
    controlPots[12] = inputs[5][2]; //analog aux in 2
    controlPots[13] = inputs[5][5]; //analog aux in 3
    controlPots[14] = inputs[5][6]; //analog aux in 4
    controlPots[15] = inputs[5][7]; //analog aux in 5
    
  
  
  
    //check if any control buttons have been pressed
    for (int i = 0; i < 16; i++){
      if((controlButtons[i] != controlButtonsPrev[i])){
        switch(i) {
          case 0: //inst sel
            if (controlButtons[i] == LOW){ //inst sel PRESSED
              controlState = INST_SEL;
            } else { //inst sel RELEASED
              controlState = STEP_SEL;
            }
          break;
  
          case 1: //save
            if (controlButtons[i] == LOW){ //save PRESSED
  //            String patternPath = "/PATTERNS/A/" + String(patternNum) + ".CSV";
  //            Serial.print("WRITING ");
  //            Serial.println(patternPath);
  //            char patternBuf[patternPath.length()];
  //            patternPath.toCharArray(patternBuf, patternPath.length());
  //            
  ////            currPattern->writePatternToSD("/PATTERNS/A/BEEP.CSV");
  //            String myPath = "/PATTERNS/A/";
  //            String myEnd = ".CSV";
  //            myPath = myPath + to_string(patternNum + 1) + myEnd;
  //            Serial.print("writing: ");
  //            Serial.println(myPath);
  //            currPattern->writePatternToSD(patternBuf);


                PatternStorage[0][0].writePatternToSD("/PATTERNS/A/1.CSV");
                PatternStorage[0][1].writePatternToSD("/PATTERNS/A/2.CSV");
                PatternStorage[0][2].writePatternToSD("/PATTERNS/A/3.CSV");
                PatternStorage[0][3].writePatternToSD("/PATTERNS/A/4.CSV");
                PatternStorage[0][4].writePatternToSD("/PATTERNS/A/5.CSV");
                PatternStorage[0][5].writePatternToSD("/PATTERNS/A/6.CSV");
                PatternStorage[0][6].writePatternToSD("/PATTERNS/A/7.CSV");
                PatternStorage[0][7].writePatternToSD("/PATTERNS/A/8.CSV");
                PatternStorage[0][8].writePatternToSD("/PATTERNS/A/9.CSV");
                PatternStorage[0][9].writePatternToSD("/PATTERNS/A/10.CSV");
                PatternStorage[0][10].writePatternToSD("/PATTERNS/A/11.CSV");
                PatternStorage[0][11].writePatternToSD("/PATTERNS/A/12.CSV");
                PatternStorage[0][12].writePatternToSD("/PATTERNS/A/13.CSV");
                PatternStorage[0][13].writePatternToSD("/PATTERNS/A/14.CSV");
                PatternStorage[0][14].writePatternToSD("/PATTERNS/A/15.CSV");
                PatternStorage[0][15].writePatternToSD("/PATTERNS/A/16.CSV");
            } else { //save RELEASED
              
            }
          break;
  
          case 2: //shift
            if (controlButtons[i] == LOW){ //shift PRESSED
              
            } else { //shift RELEASED
              
            }
          break;
  
          case 3: //song
            if (controlButtons[i] == LOW){ //song PRESSED
              
            } else { //song RELEASED
              
            }
          break;
  
          case 4: //mute
            if (controlButtons[i] == LOW){ //mute PRESSED
              
            } else { //mute RELEASED
              
            }
          break;
  
          case 5: //pattern
            if (controlButtons[i] == LOW){ //pattern PRESSED
              controlState = PATTERN_SEL;
              patternQueueWriteIndex = 0;
              patternQueueLen = 1;
              ledDisplayState = DISP_PATTERNS;
            } else { //pattern RELEASED
              controlState = STEP_SEL;
              patternQueueIndex = 0;
              currPattern = &PatternStorage[0][patternQueue[0]];
              ledDisplayState = DISP_STEPS;
            }
          break;
  
          case 6: //dataEncBut
            if (controlButtons[i] == LOW){ //dataEncBut PRESSED
              
            } else { //dataEncBut RELEASED
              
            }
          break;
  
          case 7: //tempoEncBut
            if (controlButtons[i] == LOW){ //tempoEncBut PRESSED
              
            } else { //tempoEncBut RELEASED
              
            }
          break;
  
          case 8: //bank
            if (controlButtons[i] == LOW){ //bank PRESSED
              
            } else { //bank RELEASED
              
            }
          break;
  
          case 9: //step
            if (controlButtons[i] == LOW){ //step PRESSED
              currPattern->clearPattern();
            } else { //step RELEASED
              
            }
          break;
  
          case 10: //beatRep1
            if (controlButtons[i] == LOW){ //beatRep1 PRESSED
              
            } else { //beatRep1 RELEASED
              
            }
          break;
  
          case 11: //beatRep2
            if (controlButtons[i] == LOW){ //beatRep2 PRESSED
              
            } else { //beatRep2 RELEASED
              
            }
          break;
  
          case 12: //playpause
            if (controlButtons[i] == LOW){ //playpause PRESSED
              if(transportState == PLAYING){
                transportState = PAUSED;
                sr1LED[1] = 0;
                Serial.println("Paused!");
              } else { 
                transportState = PLAYING;
                sr1LED[2] = 0;
                sr1LED[1] = 1;
                currStepTime = millis();
                Serial.println("Playing!");
              }
            } else { //playpause RELEASED
              
            }
  
          break;
  
          case 13: //stop
            if (controlButtons[i] == LOW){ //stop PRESSED
              sr1LED[2] = 1;
              sr1LED[1] = 0;
              transportState = STOPPED;
              currStep = -1;
              Serial.println("Stopped!");
            } else { //stop RELEASED
              
            }
  
          break;
  
          case 14: //forwards
            if (controlButtons[i] == LOW){ //forwards PRESSED
              
            } else { //forwards RELEASED
              
            }
          break;
  
          case 15: //backwards
            if (controlButtons[i] == LOW){ //backwards PRESSED
              
            } else { //backwards RELEASED
              
            }
          break;
        }
      }
    }
  
  // CONTROL STRUCTURE
  
    switch(controlState){
      case STEP_SEL:
        for (int i = 0; i < 16; i++){
          if(stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]){
            currPattern->pattern[currInst][i] = !currPattern->pattern[currInst][i];
          }
        }
      break;
  
      case INST_SEL:
        for(int i = 0; i < 16; i++){
          if(stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]){
            currInst = i;
          }
        }
      break;
  
      case PATTERN_SEL:
        for(int i = 0; i < 16; i++){
          if(stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]){
  //          currPattern = &PatternStorage[0][i];
  //            nextPattern = i;
              if(patternQueueWriteIndex > 0) patternQueueLen++;
              patternQueue[patternQueueWriteIndex++] = i;
  
              if (transportState != PLAYING){
                patternQueueIndex = 0;
                currPattern = &PatternStorage[0][i];
                patternNum = i;
              }
  
          }
        }
      break;
  
      case SONG_SEL:
      break;
  
      case BANK_SEL:
      break;
    }

    //handle potentiometer updates
    
//      controlPots[0] = inputs[4][0] //digi 1 param
//    controlPots[1] = inputs[4][1] //digi 1 vol
//    controlPots[2] = inputs[4][2] //digi 2 param
//    controlPots[3] = inputs[4][3] //digi 2 vol
//    controlPots[4] = inputs[4][5] //digi 3 param
//    controlPots[5] = inputs[4][4] //digi 3 vol
    drum1.frequency(map(controlPots[0], 1023, 0, 60, 700));
    drum2.frequency(map(controlPots[2], 1023, 0, 60, 700));
    drum3.frequency(map(controlPots[4], 1023, 0, 60, 700));
    mixer4.gain(0, (1023 - controlPots[1])/1023);
    mixer4.gain(1, (1023 - controlPots[3])/1023);
    mixer4.gain(2, (1023 - controlPots[5])/1023);
    

    //print mux inputs
    if (printEn){
      for (int i = 0; i < 7; i++){
        for (int j = 0; j < 8; j++){
          Serial.print(inputs[i][j]);
          Serial.print(" ");
        }
        Serial.println(" ");
      }
      Serial.println(" ");
  
      //print control buttons
      Serial.print("ctrl");
      for (int i = 0; i < 16; i++){
        Serial.print(controlButtons[i]);
        Serial.print(" ");
      }
      Serial.println(" ");
      Serial.println(" ");
    }
  }


    uint8_t sr0 = sr0LED[0] | sr0LED[1]<<1 | sr0LED[2]<<2 | sr0LED[3]<<3 |
                  sr0LED[4]<<4 | sr0LED[5]<<5 | sr0LED[6]<<6 | sr0LED[7]<<7;
                  
    uint8_t sr1 = sr1LED[0] | sr1LED[1]<<1 | sr1LED[2]<<2 | sr1LED[3]<<3 |
                  sr1LED[4]<<4 | sr1LED[5]<<5 | sr1LED[6]<<6 | sr1LED[7]<<7;
                  
    uint8_t sr2 = sr2LED[0] | sr2LED[1]<<1 | sr2LED[2]<<2 | sr2LED[3]<<3 |
                  sr2LED[4]<<4 | sr2LED[5]<<5 | sr2LED[6]<<6 | sr2LED[7]<<7;
                  
    uint8_t sr3 = sr3LED[0] | sr3LED[1]<<1 | sr3LED[2]<<2 | sr3LED[3]<<3 |
                  sr3LED[4]<<4 | sr3LED[5]<<5 | sr3LED[6]<<6 | sr3LED[7]<<7;

    uint8_t sr4 = 0b00000000;
    uint8_t sr5 = 0b00000000;

  //STEP LED STUFF
  switch(ledDisplayState){
    case DISP_STEPS:
      for (int i = 0; i < 16; i++){ //light up which stepss are on for current instrument
        stepLEDs[i] = currPattern->pattern[currInst][i];
      }
      stepLEDs[currStep] = 1; // light up the playhead/current step
      break;

    case DISP_PATTERNS:
      for (int i = 0; i < 16; i ++){
        stepLEDs[i] = 0;
      }
      stepLEDs[patternNum] = 1;
      break;
  }

      sr4 = stepLEDs[0] | stepLEDs[1]<<1 | stepLEDs[2]<<2 | stepLEDs[3]<<3 | // send it to the sr variables
                    stepLEDs[8]<<4 | stepLEDs[9]<<5 | stepLEDs[10]<<6 | stepLEDs[11]<<7;
    
      sr5 = stepLEDs[4] | stepLEDs[5]<<1 | stepLEDs[6]<<2 | stepLEDs[7]<<3 |
                    stepLEDs[12]<<4 | stepLEDs[13]<<5 | stepLEDs[14]<<6 | stepLEDs[15]<<7;

      
    digitalWrite(ST_CP, LOW);
    shiftOut(DS, SH_CP, MSBFIRST, sr5);
    shiftOut(DS, SH_CP, MSBFIRST, sr4);
    shiftOut(DS, SH_CP, MSBFIRST, sr3);
    shiftOut(DS, SH_CP, MSBFIRST, sr2);
    shiftOut(DS, SH_CP, MSBFIRST, sr1);
    shiftOut(DS, SH_CP, MSBFIRST, sr0);
    digitalWrite(ST_CP, HIGH);
  
  
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
// * Function selectMuxPin
// * -------------------------------------------------------------------------------------------------
// * Overview: writes microcontroller's defined MUX address pins to a specific address
// *          NOTE: Be sure to give time for signal to propogate before reading data pin
// * Input:
// *    byte address : address on multiplexer to connect to data pin
// * Output: Nothing
// **************************************************************************************************/
void selectMuxPin(int pin) {
  for (int i = 0; i < 3; i++) {
    if (pin & (1 << i))
      digitalWrite(muxAddressPins[i],  HIGH);
    else
      digitalWrite(muxAddressPins[i],  LOW);
  }
}

///**************************************************************************************************
// * Function trigNote
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an note is triggered
// * Input: 
// *    int instNum : number of the instrument being triggered
// * Output: Nothing
// **************************************************************************************************/
void trigNote(int instNum){
  //send pulse voltage out
    int pulseLen = 10;
    switch(instNum){
      case INST_BD: //BD
        sr3LED[7] = 0;
        pulseLen = 10;
        break;
  
      case INST_SD: //SN
        sr2LED[2] = 0;
        pulseLen = 5;
        break;
  
      case INST_CYN1: //CYN1
        sr0LED[0] = 0;
        pulseLen = 10;
        break;
  
      case INST_CYN2: //CYN2
        sr0LED[7] = 0;
        pulseLen = 10;
        break;
  
      case INST_GLITCH: //GLITCH
        sr2LED[4] = 0;
        pulseLen = 10;
        break;
  
      case INST_DIGI1: //DIGI1
        sr2LED[7] = 0;
        pulseLen = 10;
//        playSdWav1.play("DRUMS/KICK.WAV");
        drum1.noteOn();
        break;
  
      case INST_DIGI2: //DIGI2
        sr2LED[6] = 0;
        pulseLen = 10;
        drum2.noteOn();
//        playSdWav2.play("DRUMS/TOM.WAV");
        break;
  
      case INST_DIGI3: //DIGI3
        sr2LED[5] = 0;
        pulseLen = 10;
//        playSdWav3.play("DRUMS/CH.WAV");
        drum3.noteOn();
        break;

      case INST_DIGI4: //casio kick
        pulseLen = 10;
        playSdWav4.play("DRUMS/CASIOSK1/kick.wav");
        break;

      case INST_DIGI5: //casio snare
        pulseLen = 10;
        playSdWav5.play("DRUMS/CASIOSK1/snare.wav");
        break;

      case INST_DIGI6: //casio closed hat
        pulseLen = 10;
        playSdWav6.play("DRUMS/CASIOSK1/chh.wav");
        break;

      case INST_DIGI7: //casio open hat
        pulseLen = 10;
        playSdWav7.play("DRUMS/CASIOSK1/ohh.wav");
        break;

      case INST_DIGI8: //casio cowbell hi
        pulseLen = 10;
        playSdWav4.play("DRUMS/CASIOSK1/kick.wav");
        break;

      case INST_DIGI9: //casio cowbell lo
        pulseLen = 10;
        playSdWav5.play("DRUMS/CASIOSK1/snare.wav");
        break;

      case INST_DIGI10: //casio hi tom
        pulseLen = 10;
        playSdWav6.play("DRUMS/CASIOSK1/skhitom.wav");
        break;

      case INST_DIGI11: //casio lo tom
        pulseLen = 10;
        playSdWav7.play("DRUMS/CASIOSK1/tom.wav");
        break;
       
    }
    outPulseTimes[instNum] = millis() + pulseLen;
}

///**************************************************************************************************
// * Function clockOutput
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an clock step is reached
// * Input: 
// * Output: Nothing
// **************************************************************************************************/
void clockOutput(){
  Serial.print("PATTERN STEP: ");
  Serial.print(currStep);
  Serial.print("   ");
  

  for (int i = 0; i < 16; i++){
    Serial.print(currPattern->pattern[i][currStep]);
  }
  Serial.println(" ");
}


// Return the current value of the rotaryEncoder 
// counter in an interrupt safe way.
int GetTempoEncAcc() 
{
  int rot;
   
  cli();
  rot = tempoEncAcc;
  sei();
  return rot;
}
 
 
// Interrupt routines
void ISRtempoEncAChange()
{
  if(digitalRead(tempoEncAPin)) {
    tempoEncAval = 1;
    UpdateTempoEnc();
  } else {
    tempoEncAval = 0;
    UpdateTempoEnc();
  }
}
 
 
void ISRtempoEncBChange() 
{
  if(digitalRead(tempoEncBPin)) {
    tempoEncBval = 1;
    UpdateTempoEnc();
  } else {
    tempoEncBval = 0;
    UpdateTempoEnc();
  }
}
 
 
// Update rotary encoder accumulator. 
// This function is called by the interrupt routines.
void UpdateTempoEnc() 
{
  // Increment rotAcc if going CW, decrement it if going CCW.
  // Do not increment anything if it was just a glitch.
  switch(tempoEncState) {
    case 0: // Idle state, look for direction
      if(!tempoEncBval) {
        tempoEncState = 1;  // CW 1
      }
      if(!tempoEncAval) {
        tempoEncState = 11; // CCW 1
      }
      break;
    case 1: // CW, wait for A low while B is low
      if(!tempoEncBval) {
        if(!tempoEncAval) {
          tempoEncAcc++;
          //update tempo variable
          tempo += 10;
          changeTempo(tempo);
#ifdef DEMO          
          // Remove this when not in demo mode
          Serial.print(" ..tempo right.. "); 
#endif
          tempoEncState = 2; // CW 2
        }
      } else {
        if(tempoEncAval) {
          // It was just a glitch on B, go back to start
          tempoEncState = 0;
        }
      }
      break;
    case 2: // CW, wait for B high
      if(tempoEncBval) {
        tempoEncState = 3; // CW 3
      }
      break;
    case 3: // CW, wait for A high
      if(tempoEncAval) {
        tempoEncState = 0; // back to idle (detent) state
      }
      break;
    case 11: // CCW, wait for B low while A is low
      if(!tempoEncAval) {
        if(!tempoEncBval) {
          tempoEncAcc--;
          tempo -= 10;
          changeTempo(tempo);
#ifdef DEMO
          // Remove this when not in demo mode
          Serial.print(" ..tempo left.. "); 
#endif
          tempoEncState = 12; // CCW 2
        }
      } else {
        if(tempoEncBval) {
          // It was just a glitch on A, go back to start
          tempoEncState = 0;
        }
      }
      break;
    case 12: // CCW, wait for A high
      if(tempoEncAval) {
        tempoEncState = 13; // CCW 3
      }
      break;
    case 13: // CCW, wait for B high
      if(tempoEncBval) {
        tempoEncState = 0; // back to idle (detent) state
      }
      break;
  }
}


// DATA ENCODER

// Return the current value of the rotaryEncoder 
// counter in an interrupt safe way.
int GetDataEncAcc() 
{
  int rot;
   
  cli();
  rot = dataEncAcc;
  sei();
  return rot;
}
 
 
// Interrupt routines
void ISRdataEncAChange()
{
  if(digitalRead(dataEncAPin)) {
    dataEncAval = 1;
    UpdateDataEnc();
  } else {
    dataEncAval = 0;
    UpdateDataEnc();
  }
}
 
 
void ISRdataEncBChange() 
{
  if(digitalRead(dataEncBPin)) {
    dataEncBval = 1;
    UpdateDataEnc();
  } else {
    dataEncBval = 0;
    UpdateDataEnc();
  }
}
 
 
// Update rotary encoder accumulator. 
// This function is called by the interrupt routines.
void UpdateDataEnc() 
{
  // Increment rotAcc if going CW, decrement it if going CCW.
  // Do not increment anything if it was just a glitch.
  switch(dataEncState) {
    case 0: // Idle state, look for direction
      if(!dataEncBval) {
        dataEncState = 1;  // CW 1
      }
      if(!dataEncAval) {
        dataEncState = 11; // CCW 1
      }
      break;
    case 1: // CW, wait for A low while B is low
      if(!dataEncBval) {
        if(!dataEncAval) {
          dataEncAcc++;
#ifdef DEMO          
          // Remove this when not in demo mode
          Serial.print(" ..data right.. "); 
#endif
          dataEncState = 2; // CW 2
        }
      } else {
        if(dataEncAval) {
          // It was just a glitch on B, go back to start
          dataEncState = 0;
        }
      }
      break;
    case 2: // CW, wait for B high
      if(dataEncBval) {
        dataEncState = 3; // CW 3
      }
      break;
    case 3: // CW, wait for A high
      if(dataEncAval) {
        dataEncState = 0; // back to idle (detent) state
      }
      break;
    case 11: // CCW, wait for B low while A is low
      if(!dataEncAval) {
        if(!dataEncBval) {
          dataEncAcc--;
#ifdef DEMO
          // Remove this when not in demo mode
          Serial.print(" ..data left.. "); 
#endif
          dataEncState = 12; // CCW 2
        }
      } else {
        if(dataEncBval) {
          // It was just a glitch on A, go back to start
          dataEncState = 0;
        }
      }
      break;
    case 12: // CCW, wait for A high
      if(dataEncAval) {
        dataEncState = 13; // CCW 3
      }
      break;
    case 13: // CCW, wait for B high
      if(dataEncBval) {
        dataEncState = 0; // back to idle (detent) state
      }
      break;
  }
}
