#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <CSV_Parser.h>
#include <U8g2lib.h>
#include "frames.h"
#include "Pattern.h"
#include <TeensyVariablePlayback.h>
#include "flashloader.h"

// #define DEMO 1

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_DC 25
#define LCD_CS 10
#define LCD_RST 24

#define SDCARD_CS_PIN BUILTIN_SDCARD

enum instruments
{
  INST_BD,
  INST_SD,
  INST_CYN1,
  INST_CYN2,
  INST_GLITCH,
  INST_DIGI1,
  INST_DIGI2,
  INST_DIGI3,

  INST_SMP1,
  INST_SMP2,
  INST_SMP3,
  INST_SMP4,
  INST_SMP5,
  INST_SMP6,
  INST_SMP7,
  INST_SMP8
};

enum lcdStates
{
  LCD_INST_PROP,
  LCD_TEMPO,
  LCD_DEMO,
  LCD_KIT_SEL
};

enum transportStates
{
  STOPPED,
  PLAYING,
  PAUSED,
};

enum controlStates
{
  STEP_SEL,
  INST_SEL,
  PATTERN_SEL,
  SONG_SEL,
  BANK_SEL,
  KIT_SEL
};

enum ledDisplayStates
{
  DISP_STEPS,
  DISP_PATTERNS,
  DISP_SONGS
};

//------EXTERNAL QSPI RAM CHIP SECTION BEGIN------
EXTMEM Pattern PatternStorage[16][16];
//------EXTERNAL QSPI RAM CHIP SECTION END------

// Pattern variables
Pattern *currPattern;
Pattern MyPattern;
int patternNum = 1;
int nextPattern = 1;
int patternQueue[16];
int patternQueueLen = 1;
int patternQueueIndex = 0;
int patternQueueWriteIndex = 0;

AudioPlayArrayResmp playSdRaw1; // xy=321,513
AudioPlayArrayResmp playSdRaw2; // xy=321,513
AudioPlayArrayResmp playSdRaw3; // xy=321,513
AudioPlayArrayResmp playSdRaw4; // xy=321,513
AudioPlayArrayResmp playSdRaw5; // xy=321,513
AudioPlayArrayResmp playSdRaw6; // xy=321,513
AudioPlayArrayResmp playSdRaw7; // xy=321,513
AudioPlayArrayResmp playSdRaw8; // xy=321,513
AudioPlayArrayResmp playSdRaw9; // xy=321,513

newdigate::audiosample *sample1;
newdigate::audiosample *sample2;
newdigate::audiosample *sample3;
newdigate::audiosample *sample4;
newdigate::audiosample *sample5;
newdigate::audiosample *sample6;
newdigate::audiosample *sample7;
newdigate::audiosample *sample8;
newdigate::audiosample *sample9;
newdigate::audiosample *sample10;

// GUItool: begin automatically generated code
// AudioPlaySdRaw           playSdRaw1;     //xy=387,149
// AudioPlaySdRaw           playSdRaw2;     //xy=390,191
// AudioPlaySdRaw           playSdRaw3;     //xy=406,236
// AudioPlaySdRaw           playSdRaw7;     //xy=406,412
// AudioPlaySdRaw           playSdRaw6;     //xy=407,373
// AudioPlaySdRaw           playSdRaw4;     //xy=410,286
// AudioPlaySdRaw           playSdRaw5;     //xy=410,332
// AudioPlaySdRaw           playSdRaw8;     //xy=416,456
// AudioPlaySdRaw           playSdRaw9;     //xy=451,694
AudioSynthSimpleDrum drum3;        // xy=475,631
AudioSynthSimpleDrum drum2;        // xy=478,589
AudioSynthSimpleDrum drum1;        // xy=485,541
AudioMixer4 mixer4;                // xy=661,593
AudioMixer4 mixer1;                // xy=760,189
AudioMixer4 mixer2;                // xy=765,338
AudioMixer4 mixer3;                // xy=952,297
AudioEffectBitcrusher bitcrusher1; // xy=979,485
AudioOutputI2S i2s1;               // xy=1078,299
AudioConnection patchCord1(playSdRaw1, 0, mixer1, 0);
AudioConnection patchCord2(playSdRaw2, 0, mixer1, 1);
AudioConnection patchCord3(playSdRaw3, 0, mixer1, 2);
AudioConnection patchCord4(playSdRaw7, 0, mixer2, 2);
AudioConnection patchCord5(playSdRaw6, 0, mixer2, 1);
AudioConnection patchCord6(playSdRaw4, 0, mixer1, 3);
AudioConnection patchCord7(playSdRaw5, 0, mixer2, 0);
AudioConnection patchCord8(playSdRaw8, 0, mixer2, 3);
AudioConnection patchCord9(playSdRaw9, 0, mixer4, 3);
AudioConnection patchCord10(drum3, 0, mixer4, 2);
AudioConnection patchCord11(drum2, 0, mixer4, 1);
AudioConnection patchCord12(drum1, 0, mixer4, 0);
AudioConnection patchCord13(mixer4, 0, mixer3, 2);
AudioConnection patchCord14(mixer1, 0, mixer3, 0);
AudioConnection patchCord15(mixer2, 0, mixer3, 1);
AudioConnection patchCord16(mixer3, 0, i2s1, 0);
AudioConnection patchCord17(mixer3, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1; // xy=1154,637
// GUItool: end automatically generated code

// transport variables
float tempo = 120;
unsigned int stepLen = 0;
unsigned int currStep = 0;
unsigned long currStepTime = 0;

int transportState = PLAYING;
int currInst = INST_BD;
int controlState = STEP_SEL;
int ledDisplayState = DISP_STEPS;
int lcdState = LCD_INST_PROP;
int lastLcdState = LCD_INST_PROP;
bool tempoLcdFlag = true;

// Shift Register Pins
int SH_CP = 31; // Contact SH_CP - Clock
int ST_CP = 32; // Contact ST_CP - Latch
int DS = 30;    // Contact DS - Data

int inputs[8][8]; // reading button inputs
int inputsPrev[8][8];
int muxAddressPins[3] = {15, 16, 17};
int muxDataPins[7] = {14, 39, 38, 33, 40, 41, 22};

int stepButtons[16];
int stepButtonsPrev[16];

int controlButtons[16];
int controlButtonsPrev[16];

float controlPots[16];

float sampleParameters[8][2];
float sampleVolumes[8];
float parameterInc = 0.01;

// LCD navigation
int cursorLoc = 0;
bool paramSel = false;
unsigned long tempoDispTimer = 0;

bool sr0LED[8];
bool sr1LED[8];
bool sr2LED[8];
bool sr3LED[8];
bool stepLEDs[16];

// linked list for handling output pulse timing
unsigned long outPulseTimes[16];

// ROTARY ENCODER SETUP
static const int tempoEncBPin = 34; //  tempo encoder phase A pin
static const int tempoEncAPin = 35; // tempo encoder phase B pin
static const int dataEncBPin = 29;  // data encoder phase A pin
static const int dataEncAPin = 28;  // ddata encoder phase B pin
// Rotary encoder variables, used by interrupt routines
volatile int tempoEncState = 0;
volatile int tempoEncAval = 1;
volatile int tempoEncBval = 1;
volatile int tempoEncAcc = 0;
volatile int dataEncState = 0;
volatile int dataEncAval = 1;
volatile int dataEncBval = 1;
volatile int dataEncAcc = 0;

// LCD stuff
unsigned long LCDFrameTimer = 0;                                       // local framerate limiter, redundant! SHOUlD PROBABY REMOVE!
int starsFrameCount = 0;                                               // counter for demo animation
U8G2_PCD8544_84X48_F_4W_HW_SPI u8g2(U8G2_R2, LCD_CS, LCD_DC, LCD_RST); // set up u8g2
unsigned long lcdTimeout = 0;                                          // timer to globally limit LCD framerate

// nonblocking mux reading
unsigned long muxTimer = 0; //
int muxIndex = 0;
bool muxCpltFlg = false;
bool muxTimerFlg = false;
bool stateInitFlag = false; // don't remember why i added this, sets state to STEP_SEL after first time through muxRead

bool patternWrite = false; //

// bank navigation
int kitNum = 0;

void setup()
{
  Serial.begin(115200); // start serial and give a welcome message :~)
  Serial.print("Hellooo: ");

  u8g2.begin();           // start communication with LCD
  AudioMemory(8);         // THIS IS REALLY IMPORTANTT!! CHECK THAT MEMORY USAGE
  sgtl5000_1.enable();    // enable the output
  sgtl5000_1.volume(0.5); // set master volume on output

  // setup for shift register
  pinMode(SH_CP, OUTPUT); // clock pin
  pinMode(ST_CP, OUTPUT); // latch
  pinMode(DS, OUTPUT);    // data pin

  // flash setup
  //----SD CARD setup
  if (!(SD.begin(SDCARD_CS_PIN)))
  {
    // stop here, but print a message repetitively
    Serial.println("Unable to access the SD card, fix the problem and restart!");
  }
  //  //----FLASH CHIP Setup
  //  if (!SerialFlash.begin(flashChipSelect)) {
  //    Serial.println("Unable to access SPI Flash chip");
  //  }

  // digital drum initialization
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

  // SAMPLER setup
  playSdRaw1.enableInterpolation(true);
  playSdRaw2.enableInterpolation(true);
  playSdRaw3.enableInterpolation(true);
  playSdRaw4.enableInterpolation(true);
  playSdRaw5.enableInterpolation(true);
  playSdRaw6.enableInterpolation(true);
  playSdRaw7.enableInterpolation(true);
  playSdRaw8.enableInterpolation(true);
  playSdRaw9.enableInterpolation(true);

  playSdRaw1.setPlaybackRate(1);
  playSdRaw2.setPlaybackRate(1);
  playSdRaw3.setPlaybackRate(1);
  playSdRaw4.setPlaybackRate(1);
  playSdRaw5.setPlaybackRate(1);
  playSdRaw6.setPlaybackRate(1);
  playSdRaw7.setPlaybackRate(1);
  playSdRaw8.setPlaybackRate(1);
  //  playSdRaw9.setPlaybackRate(1);
  playSdRaw9.setPlaybackRate(tempo / 175.0);

  newdigate::flashloader loader;

  sample1 = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");
  sample2 = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");
  sample2 = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");
  sample3 = loader.loadSample("DRUMS/CASIOSK1/CHH.RAW");
  sample4 = loader.loadSample("DRUMS/CASIOSK1/OHH.RAW");
  sample5 = loader.loadSample("DRUMS/CASIOSK1/CB_LO.RAW");
  sample6 = loader.loadSample("DRUMS/CASIOSK1/CB_HI.RAW");
  sample7 = loader.loadSample("DRUMS/CASIOSK1/SKLOTOM.RAW");
  sample8 = loader.loadSample("DRUMS/CASIOSK1/SKHITOM.RAW");
  sample9 = loader.loadSample("BREAKS/AMEN175.RAW");
  sample1 = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");

  for (int i = 0; i < 4; i++)
  { // mute all digital mixers
    mixer1.gain(i, 0);
    mixer2.gain(i, 0);
    mixer3.gain(i, 0);
    mixer4.gain(i, 0);
  }

  // play and stop all samplers to associate sample data with the player
  playSdRaw1.playRaw(sample1->sampledata, sample1->samplesize / 2, 1);
  playSdRaw1.stop();
  playSdRaw2.playRaw(sample2->sampledata, sample2->samplesize / 2, 1);
  playSdRaw2.stop();
  playSdRaw3.playRaw(sample3->sampledata, sample3->samplesize / 2, 1);
  playSdRaw3.stop();
  playSdRaw4.playRaw(sample4->sampledata, sample4->samplesize / 2, 1);
  playSdRaw4.stop();
  playSdRaw5.playRaw(sample5->sampledata, sample5->samplesize / 2, 1);
  playSdRaw5.stop();
  playSdRaw6.playRaw(sample6->sampledata, sample6->samplesize / 2, 1);
  playSdRaw6.stop();
  playSdRaw7.playRaw(sample7->sampledata, sample7->samplesize / 2, 1);
  playSdRaw7.stop();
  playSdRaw8.playRaw(sample8->sampledata, sample8->samplesize / 2, 1);
  playSdRaw8.stop();
  playSdRaw9.playRaw(sample9->sampledata, sample9->samplesize / 2, 1);
  playSdRaw9.stop();

  // set all mixer gains
  mixer1.gain(0, 1);   // playSdRaw1
  mixer1.gain(1, 1);   // playSdRaw2
  mixer1.gain(2, 1);   // playSdRaw3
  mixer1.gain(3, 1);   // playSdRaw4
  mixer2.gain(0, 1);   // playSdRaw5
  mixer2.gain(1, 1);   // playSdRaw6
  mixer2.gain(2, 1);   // playSdRaw7
  mixer2.gain(3, 1);   // playSdRaw8
  mixer3.gain(0, 0.2); // mixer 1
  mixer3.gain(1, 0.2); // mixer 2
  mixer3.gain(2, 0.2); // mixer 4
  mixer3.gain(3, 0.2); // empty
  mixer4.gain(0, 1);   // digi drum 1
  mixer4.gain(1, 1);   // digi drum 2
  mixer4.gain(2, 1);   // digi drum 3
  mixer4.gain(3, 2);   // playSdRaw9

  // initialize MUX address pins
  for (int i = 0; i < sizeof(muxAddressPins) / sizeof(muxAddressPins[0]); i++)
  {
    pinMode(muxAddressPins[i], OUTPUT);
  }

  // initialize MUX data pins
  for (int i = 0; i < sizeof(muxDataPins) / sizeof(muxDataPins[0]); i++)
  {
    pinMode(muxDataPins[i], INPUT);
  }

  // inittialize a bunch of arrays
  for (int i = 0; i < 16; i++)
  {
    stepButtons[i] = 0;
    stepButtonsPrev[i] = 0;
    outPulseTimes[i] = 0;
    stepLEDs[i] = 1;
    patternQueue[i] = 0;
    controlPots[i] = 0;
  }
  // initialize even more arrays
  for (int i = 0; i < 8; i++)
  {
    sr0LED[i] = 0;
    sr1LED[i] = 0;
    sr2LED[i] = 1;
    sr3LED[i] = 0;
    sampleParameters[i][0] = 1;   // sample playback speed
    sampleParameters[i][1] = 100; // another parameter
    sampleVolumes[i] = 1;
  }
  // set some default led states
  sr1LED[2] = 0;
  sr1LED[1] = 1;
  sr3LED[1] = 0;
  sr0LED[5] = 1;

  changeTempo(tempo); // set the tempo

  // rotary encoder setup
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

  // load patterns from SD Card
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
  currStepTime = millis();
}

void loop()
{

  if (millis() > lcdTimeout) // LCD framerate limiter
  {
    displayLCD(false);
    lcdTimeout = millis() + 100;
  }
  readMux(false); // read inputs and process them

  // steps
  if (transportState == PLAYING)
  {
    if (millis() > (currStepTime + stepLen)) // new step has been reached
    {
      recallParameters(); // update parameters for this step
      if (currStep == 15)
      {                                                                    // last step off pattern, time to move to the next one
        patternQueueIndex = (patternQueueIndex + 1) % patternQueueLen;     // step to the next pattern in sequence
        currPattern = &PatternStorage[0][patternQueue[patternQueueIndex]]; // actually grab the pattern from memory
        patternNum = patternQueue[patternQueueIndex];                      // store pattern number for reference
        changeKit(currPattern->settings[1]);                               // grab kit from next pattern
      }
      currStep = (currStep + 1) % 16; // move step pointer to next step

      // clockOutput(); //send clock signal out external output

      for (int i = 0; i < 16; i++)
      { // send triggers of all instruments to be played at this step
        if (currPattern->pattern[i][currStep])
        {
          int myParam = 0; // initialize myParam to zero for instruments that don't need it
          if (i == 16 || i == 17 || i == 18 || i == 19 || i == 20)
            myParam = currPattern->pattern[i][currStep]; // grab the parameter for chord/break sample voices
          trigNote(i, myParam);                          // trigger correct instrument and send the parameter
        }
      }
      float swingAmt = map(controlPots[10], 1023, 0, 0, 0.4); // parse swing amount
      if (currStep % 2 == 0)
      { // set timing for steps, accounting for swing
        currStepTime = currStepTime + stepLen * (1.0 + swingAmt);
      }
      else
      {
        currStepTime = currStepTime + stepLen * (1.0 - swingAmt);
      }
    }
  }

  for (int i = 0; i < 16; i++) // check if hardware output pulses need to finish
  {
    if (outPulseTimes[i] != 0) // only check active pulses
    {
      if (millis() > outPulseTimes[i]) // check if the pulse should be done
      {
        //        Serial.println("PULSE COMPLETE");
        outPulseTimes[i] = 0;
        switch (i) // turn off the corresponding LEDs and stop the samples. TODO: maybe output pulses length should be timed separately from the sample cutoffs
        {
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
        case 8: // SMP1
          playSdRaw1.stop();
          break;
        case 9: // SMP2
          playSdRaw2.stop();
          break;
        case 10: // SMP3
          playSdRaw3.stop();
          break;
        case 11: // SMP4
          playSdRaw4.stop();
          break;
        case 12: // SMP5
          playSdRaw5.stop();
          break;
        case 13: // SMP6
          playSdRaw6.stop();
          break;
        case 14: // SMP7
          playSdRaw7.stop();
          break;
        case 15: // SMP8
          playSdRaw8.stop();
          break;
        }
      }
    }
  }
}

///**************************************************************************************************
// * Function readMux
// * -------------------------------------------------------------------------------------------------
// * Overview: reads multiplexers and does a lot with their values, this is really the main control processing function
// * Input:
// *    bool printEn : enables some serial prints for testing purposes
// * Output: Nothing
// **************************************************************************************************/
void readMux(bool printEn)
{
  if (!muxCpltFlg) // check if all mux addresses have been read
  {
    if (!muxTimerFlg) // set pin on mux and set internal timer to wait for signal to propogate before reading
    {
      selectMuxPin(muxIndex);  // send outputs to select mux input
      muxTimerFlg = true;      // indicate we are waiting for input selection signals to propogate
      muxTimer = millis() + 2; // set a timer of 2 ms to wait for signals to propogate before reading
    }
    if (millis() > muxTimer) // timer is up, we are OK to read from mux!
    {
      muxTimerFlg = false;        // reset mux timer flag
      for (int j = 0; j < 7; j++) // read from the muxs
      {
        if (j == 4 || j == 5)
        {
          inputs[j][muxIndex] = analogRead(muxDataPins[j]); // read analog inputs
        }
        else
        {
          inputs[j][muxIndex] = digitalRead(muxDataPins[j]); // read digital inputs
        }
      }

      if (muxIndex == 7) // if we've read all indices move to processing
      {
        muxCpltFlg = true; // tell program we're done reading
        muxIndex = 0;      // get ready to read from the beginning again
      }
      else // if we havent read all indices move to the next index
      {
        muxIndex++;
      }
    }
  }

  if (muxCpltFlg) // all MUX addresses read! time to do stuff with the input data
  {
    muxCpltFlg = false;
    // shift current stepButtons values to the stepButtonsPrev array
    for (int i = 0; i < 16; i++)
    {
      stepButtonsPrev[i] = stepButtons[i];
    }

    // grab current stepButtons values from mux input array
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

    // shift current controlButtons values to the controlButtonsPrev array
    for (int i = 0; i < 16; i++)
    {
      controlButtonsPrev[i] = controlButtons[i];
    }

    // grab control buttons and place in array
    controlButtons[0] = inputs[2][0];  // inst sel
    controlButtons[1] = inputs[2][1];  // save
    controlButtons[2] = inputs[2][2];  // shift
    controlButtons[3] = inputs[2][3];  // song
    controlButtons[4] = inputs[2][4];  // mute
    controlButtons[5] = inputs[2][5];  // pattern
    controlButtons[6] = inputs[3][2];  // dataEncBut
    controlButtons[7] = inputs[3][3];  // tempoEncBut
    controlButtons[8] = inputs[3][4];  // bank
    controlButtons[9] = inputs[3][5];  // step
    controlButtons[10] = inputs[6][0]; // beatRep1
    controlButtons[11] = inputs[6][1]; // beatRep2
    controlButtons[12] = inputs[6][2]; // playpause
    controlButtons[13] = inputs[6][3]; // stop
    controlButtons[14] = inputs[6][5]; // forwards
    controlButtons[15] = inputs[6][6]; // back

    // grab analog values and place in array
    controlPots[0] = inputs[4][0];  // digi 1 param
    controlPots[1] = inputs[4][1];  // digi 1 vol
    controlPots[2] = inputs[4][2];  // digi 2 param
    controlPots[3] = inputs[4][3];  // digi 2 vol
    controlPots[4] = inputs[4][5];  // digi 3 param
    controlPots[5] = inputs[4][4];  // digi 3 vol
    controlPots[6] = inputs[4][6];  // break vol
    controlPots[7] = inputs[5][0];  // break chaos
    controlPots[8] = inputs[5][3];  // break pitch
    controlPots[9] = inputs[5][1];  // repeat
    controlPots[10] = inputs[5][4]; // swing
    controlPots[11] = inputs[4][7]; // analog aux in 1
    controlPots[12] = inputs[5][2]; // analog aux in 2
    controlPots[13] = inputs[5][5]; // analog aux in 3
    controlPots[14] = inputs[5][6]; // analog aux in 4
    controlPots[15] = inputs[5][7]; // analog aux in 5

    // check if any control buttons have been pressed
    for (int i = 0; i < 16; i++)
    {
      if ((controlButtons[i] != controlButtonsPrev[i]))
      {
        switch (i)
        {
        case 0:                         // inst sel
          if (controlButtons[i] == LOW) // inst sel PRESSED
          {
            controlState = INST_SEL;
          }
          else // inst sel RELEASED
          {
            if (controlState != KIT_SEL)
            {
              controlState = STEP_SEL;
            }
          }
          break;

        case 1: // save
          if (controlButtons[i] == LOW)
          { // save PRESSED
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

            // save all patterns in bank A for now, maybe make this more elegant later
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
          }
          else
          { // save RELEASED
          }
          break;

        case 2: // shift -----> now write
          if (controlButtons[i] == LOW)
          { // shift->write PRESSED
            //              currPattern->clearPattern();
            patternWrite = !patternWrite;
            sr3LED[2] = patternWrite;
          }
          else
          { // shift->write RELEASED
          }
          break;

        case 3: // song
          if (controlButtons[i] == LOW)
          { // song PRESSED
            controlState = SONG_SEL;
          }
          else
          { // song RELEASED
          }
          break;

        case 4: // mute
          if (controlButtons[i] == LOW)
          { // mute PRESSED
          }
          else
          { // mute RELEASED
          }
          break;

        case 5: // pattern
          if (controlButtons[i] == LOW)
          { // pattern PRESSED
            controlState = PATTERN_SEL;
            patternQueueWriteIndex = 0;
            patternQueueLen = 1;
            //              ledDisplayState = DISP_PATTERNS;
          }
          else
          { // pattern RELEASED
          }
          break;

        case 6: // dataEncBut
          if (controlButtons[i] == LOW)
          {                               // dataEncBut PRESSED
            if (controlState == INST_SEL) // if we're holding down inst_sel button, move to kit selection mode
            {
              controlState = KIT_SEL;
              lcdState = LCD_KIT_SEL;
            }
            else if (controlState == KIT_SEL) // if we're in kit_sel mode, choose the currently selected kit
            {
              changeKit(kitNum);                 // change the kit
              currPattern->settings[1] = kitNum; // place kit into pattern memory
              controlState = STEP_SEL;           // exit kit selection mode
              lcdState = LCD_INST_PROP;          // exit kit selection display
            }
            else // if in paramter selection mode, swap between menu navigation and data entry
            {
              paramSel = !paramSel;
            }
          }
          else
          { // dataEncBut RELEASED
          }
          break;

        case 7: // tempoEncBut
          if (controlButtons[i] == LOW)
          {                            // tempoEncBut PRESSED
            tempoDispTimer = millis(); // set timer to start displaying tempo
          }
          else
          { // tempoEncBut RELEASED
          }
          break;

        case 8: // bank
          if (controlButtons[i] == LOW)
          { // bank PRESSED
          }
          else
          { // bank RELEASED
          }
          break;

        case 9: // step
          if (controlButtons[i] == LOW)
          { // step PRESSED
            controlState = STEP_SEL;
          }
          else
          { // step RELEASED
          }
          break;

        case 10: // beatRep1
          if (controlButtons[i] == LOW)
          { // beatRep1 PRESSED
          }
          else
          { // beatRep1 RELEASED
          }
          break;

        case 11: // beatRep2
          if (controlButtons[i] == LOW)
          { // beatRep2 PRESSED
          }
          else
          { // beatRep2 RELEASED
          }
          break;

        case 12: // playpause
          if (controlButtons[i] == LOW)
          { // playpause PRESSED
            if (transportState == PLAYING)
            {
              transportState = PAUSED;
              sr1LED[1] = 0;
              Serial.println("Paused!");
              stopSamples(); // force stop playing all samples
            }
            else
            {
              transportState = PLAYING;
              sr1LED[2] = 0;
              sr1LED[1] = 1;
              currStepTime = millis();
              Serial.println("Playing!");
            }
          }
          else
          { // playpause RELEASED
          }

          break;

        case 13: // stop
          if (controlButtons[i] == LOW)
          { // stop PRESSED
            // set play and stop LEDs
            sr1LED[2] = 1;
            sr1LED[1] = 0;
            transportState = STOPPED;
            currStep = -1;         // jump back to start of pattern
            patternQueueIndex = 0; // jump back to start of song
            currPattern = &PatternStorage[0][patternQueue[patternQueueIndex]];
            patternNum = patternQueue[patternQueueIndex];
            stopSamples(); // force stop playing all samples
            Serial.println("Stopped!");
          }
          else
          { // stop RELEASED
          }

          break;

        case 14: // forwards
          if (controlButtons[i] == LOW)
          { // forwards PRESSED
          }
          else
          { // forwards RELEASED
          }
          break;

        case 15: // backwards
          if (controlButtons[i] == LOW)
          { // backwards PRESSED
          }
          else
          { // backwards RELEASED
          }
          break;
        }
      }
    }

    if (!stateInitFlag) // don't know why i have this, I don't think it ever executes but it will force the state to STEP_SEL once per power cycle
    {
      controlState = STEP_SEL;
      stateInitFlag = true;
    }

    // CONTROL STRUCTURE
    switch (controlState)
    {
    case STEP_SEL:                 // mode for selecting steps where currently selected instrument is played
      for (int i = 0; i < 16; i++) // loop through all 16 step buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          currPattern->pattern[currInst][i] = !currPattern->pattern[currInst][i]; // record buttom press into current pattern array
        }
      }
      break;

    case INST_SEL:                 // mode for selecting current instrument
      for (int i = 0; i < 16; i++) // loop through all 16 instrument buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          currInst = i; // set current instrument to the one that was pressed
        }
      }
      break;

    case PATTERN_SEL:   // mode for selecting pattern
      if (patternWrite) // patternWrite is currently how i indicate that sequentially pressed patterns will be chained
      {
        for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
        {
          if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
          {
            //          currPattern = &PatternStorage[0][i];
            //            nextPattern = i;
            if (patternQueueWriteIndex > 0) // extend pattern length by one
              patternQueueLen++;

            patternQueue[patternQueueWriteIndex++] = i; // write pattern to current index

            if (transportState != PLAYING) // if we're not playing, safe to jump right to the pattern pressed
            {
              patternQueueIndex = 0;               // jump to the first pattern of sequence
              currPattern = &PatternStorage[0][i]; // grab the first pattern from memory
              patternNum = i;                      // set pattern num to the one you pressed
            }
          }
        }
      }
      else // if we're not in pattern write mode we can just set a queue of length one, and jump there after the current pattern is done
      {
        for (int i = 0; i < 16; i++)
        {
          if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
          {
            if (transportState == PLAYING) // if playing, we wait for current pattern to end before switching over
            {
              patternQueue[0] = i; // set pressed pattern to index 0
              patternQueueLen = 1; // set length of queue to 2
            }
            else // if not playing we can jump to new pattern immediately
            {
              patternQueueIndex = 0;
              patternQueueLen = 1;                 // set length of queue to 2
              currPattern = &PatternStorage[0][i]; // grab the new pattern from memory
              patternQueue[0] = i;                 // put pattern num at the first place in queue
              patternNum = i;                      // set pattern num to the one you pressed
            }
          }
        }
      }
      break;
    case SONG_SEL:
      // INSERT CODE HERE FOR SELECTING SONGS
      break;

    case BANK_SEL:
      // INSERT CODE HERE FOR SELECTING BANKS
      // WILL NEED TO WRITE SEPARATE CODE FOR INST BANKS VS PATTERN BANKS VS SONG BANKS + maybe some sort of sample bank idk
      break;
    }

    drum1.frequency(map(controlPots[0], 1023, 0, 60, 700)); // set drum 1 freq from param pot
    drum2.frequency(map(controlPots[2], 1023, 0, 60, 700)); // set drum 2 freq from param pot
    drum3.frequency(map(controlPots[4], 1023, 0, 60, 700)); // set drum 3 freq from param pot
    mixer4.gain(0, (1023 - controlPots[1]) / 1023);         // set drum 1 gain from param pot
    mixer4.gain(1, (1023 - controlPots[3]) / 1023);         // set drum 2 gain from param pot
    mixer4.gain(2, (1023 - controlPots[5]) / 1023);         // set drum 3 gain from param pot

    // print mux inputs
    if (printEn)
    {
      for (int i = 0; i < 7; i++)
      {
        for (int j = 0; j < 8; j++)
        {
          Serial.print(inputs[i][j]);
          Serial.print(" ");
        }
        Serial.println(" ");
      }
      Serial.println(" ");

      // print control buttons
      Serial.print("ctrl");
      for (int i = 0; i < 16; i++)
      {
        Serial.print(controlButtons[i]);
        Serial.print(" ");
      }
      Serial.println(" ");
      Serial.println(" ");
    }
  }

  // grab LED states and pack them into 8-bit numbers to be sent out the shift registers
  uint8_t sr0 = sr0LED[0] | sr0LED[1] << 1 | sr0LED[2] << 2 | sr0LED[3] << 3 |
                sr0LED[4] << 4 | sr0LED[5] << 5 | sr0LED[6] << 6 | sr0LED[7] << 7;

  uint8_t sr1 = sr1LED[0] | sr1LED[1] << 1 | sr1LED[2] << 2 | sr1LED[3] << 3 |
                sr1LED[4] << 4 | sr1LED[5] << 5 | sr1LED[6] << 6 | sr1LED[7] << 7;

  uint8_t sr2 = sr2LED[0] | sr2LED[1] << 1 | sr2LED[2] << 2 | sr2LED[3] << 3 |
                sr2LED[4] << 4 | sr2LED[5] << 5 | sr2LED[6] << 6 | sr2LED[7] << 7;

  uint8_t sr3 = sr3LED[0] | sr3LED[1] << 1 | sr3LED[2] << 2 | sr3LED[3] << 3 |
                sr3LED[4] << 4 | sr3LED[5] << 5 | sr3LED[6] << 6 | sr3LED[7] << 7;

  // make two blank variables for the step LEDs, not necessary i could just define them below
  uint8_t sr4 = 0b00000000;
  uint8_t sr5 = 0b00000000;

  // STEP LED STUFF
  switch (controlState) // determine what should be displayed on LEDs
  {
  case STEP_SEL: // display active steps and playhead
    ledDisplayState = DISP_STEPS;
    break;
  case PATTERN_SEL: // display current pattern on step LEDs
    ledDisplayState = DISP_PATTERNS;
    break;
  case SONG_SEL: // display current song on step LEDs
    ledDisplayState = DISP_SONGS;
    break;
  }

  switch (ledDisplayState)
  {
  case DISP_STEPS:
    for (int i = 0; i < 16; i++) // light up which stepss are on for current instrument
    {
      stepLEDs[i] = currPattern->pattern[currInst][i];
    }
    stepLEDs[currStep] = 1; // light up the playhead/current step
    break;

  case DISP_PATTERNS: // display current pattern on step LEDs
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[patternNum] = 1;
    break;
  }

  // arrange step LED states we just defined into 8-bit numbers to send to shift registers
  sr4 = stepLEDs[0] | stepLEDs[1] << 1 | stepLEDs[2] << 2 | stepLEDs[3] << 3 |
        stepLEDs[8] << 4 | stepLEDs[9] << 5 | stepLEDs[10] << 6 | stepLEDs[11] << 7;

  sr5 = stepLEDs[4] | stepLEDs[5] << 1 | stepLEDs[6] << 2 | stepLEDs[7] << 3 |
        stepLEDs[12] << 4 | stepLEDs[13] << 5 | stepLEDs[14] << 6 | stepLEDs[15] << 7;

  // control mode LEDs
  sr3LED[3] = 0; // turn off song LED
  sr3LED[4] = 0; // turn off pattern LED
  sr3LED[6] = 0; // turn off step LED
  switch (controlState)
  {
  case STEP_SEL:
    sr3LED[6] = 1; // turn on step LED
    break;
  case SONG_SEL:
    sr3LED[3] = 1; // turn on song LED
    break;

  case PATTERN_SEL:
    sr3LED[4] = 1; // turn on pattern LED
    break;
  }

  // send all shift register values out
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
void changeTempo(float newTempo)
{
  currPattern->settings[0] = newTempo;
  tempo = newTempo;                          // set this global tempo variable to the specified tempo though i don't think I'm really using this variable anyway
  float quarterLen = (60.0 / tempo) * 1000;  // subdivide to quarter notes
  float eigthLen = quarterLen / 2;           // subdivide to eighth notes
  float sixteenthLen = quarterLen / 4;       // subdivide to sixteenth notes
  stepLen = sixteenthLen;                    // use sixteenth notes as our step length
  playSdRaw9.setPlaybackRate(tempo / 175.0); // shift breakbeat to match new tempo
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
void selectMuxPin(int pin)
{
  for (int i = 0; i < 3; i++)
  {
    if (pin & (1 << i)) // hacky way to sen out the right address, trust me on this one :~)
      digitalWrite(muxAddressPins[i], HIGH);
    else
      digitalWrite(muxAddressPins[i], LOW);
  }
}

///**************************************************************************************************
// * Function trigNote
// * -------------------------------------------------------------------------------------------------
// * Overview: Plays notes. Begins output pulses and triggers appropriate samples depending on the instrument
// * Input:
// *    int instNum : number of the instrument being triggered
// *    int instParam: param sent with some instruments. can indicate chord quality, sample or some other extra info
// * Output: Nothing
// **************************************************************************************************/
void trigNote(int instNum, int instParam)
{
  // send pulse voltage out
  int pulseLen = 10;
  switch (instNum)
  {
  case INST_BD: // BD
    sr3LED[7] = 0;
    pulseLen = 10;
    break;

  case INST_SD: // SN
    sr2LED[2] = 0;
    pulseLen = 5;
    break;

  case INST_CYN1: // CYN1
    sr0LED[0] = 0;
    pulseLen = 10;
    break;

  case INST_CYN2: // CYN2
    sr0LED[7] = 0;
    pulseLen = 10;
    break;

  case INST_GLITCH: // GLITCH
    sr2LED[4] = 0;
    pulseLen = 10;
    break;

  case INST_DIGI1: // DIGI1
    sr2LED[7] = 0;
    pulseLen = 10;
    drum1.noteOn();
    break;

  case INST_DIGI2: // DIGI2
    sr2LED[6] = 0;
    pulseLen = 10;
    drum2.noteOn();
    break;

  case INST_DIGI3: // DIGI3 -> currently being used as a crappy breakbeat sample thing
    sr2LED[5] = 0;
    pulseLen = 10;
    //        drum3.noteOn();
    playSdRaw9.playRaw(sample9->sampledata, sample9->samplesize / 2, 1);
    break;

  case INST_SMP1: // casio kick
    pulseLen = playSdRaw1.lengthMillis() * (currPattern->parameter[7][0] / 100.0) / currPattern->parameter[6][0];
    //        Serial.println(playSdRaw1.lengthMillis());
    playSdRaw1.playRaw(sample1->sampledata, sample1->samplesize / 2, 1);
    break;

  case INST_SMP2: // casio snare
    pulseLen = playSdRaw2.lengthMillis() * (currPattern->parameter[9][0] / 100.0) / currPattern->parameter[8][0];
    playSdRaw2.playRaw(sample2->sampledata, sample2->samplesize / 2, 1);
    break;

  case INST_SMP3: // casio closed hat
    pulseLen = playSdRaw3.lengthMillis() * (currPattern->parameter[11][0] / 100.0) / currPattern->parameter[10][0];
    playSdRaw3.playRaw(sample3->sampledata, sample3->samplesize / 2, 1);
    break;

  case INST_SMP4: // casio open hat
    pulseLen = playSdRaw4.lengthMillis() * (currPattern->parameter[13][0] / 100.0) / currPattern->parameter[12][0];
    playSdRaw4.playRaw(sample4->sampledata, sample4->samplesize / 2, 1);
    break;

  case INST_SMP5: // casio cowbell hi
    pulseLen = playSdRaw5.lengthMillis() * (currPattern->parameter[15][0] / 100.0) / currPattern->parameter[14][0];
    playSdRaw5.playRaw(sample5->sampledata, sample5->samplesize / 2, 1);
    break;

  case INST_SMP6: // casio cowbell lo
    pulseLen = playSdRaw6.lengthMillis() * (currPattern->parameter[17][0] / 100.0) / currPattern->parameter[16][0];
    playSdRaw6.playRaw(sample6->sampledata, sample6->samplesize / 2, 1);
    break;

  case INST_SMP7: // casio hi tom
    pulseLen = playSdRaw7.lengthMillis() * (currPattern->parameter[19][0] / 100.0) / currPattern->parameter[18][0];
    playSdRaw7.playRaw(sample7->sampledata, sample7->samplesize / 2, 1);
    break;

  case INST_SMP8: // casio lo tom
    pulseLen = playSdRaw8.lengthMillis() * (currPattern->parameter[21][0] / 100.0) / currPattern->parameter[20][0];
    playSdRaw8.playRaw(sample8->sampledata, sample8->samplesize / 2, 1);
    break;
  }
  outPulseTimes[instNum] = millis() + pulseLen; // send the pulse end time to or pulse timer array
}

///**************************************************************************************************
// * Function clockOutput
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an clock step is reached
// * Input:
// * Output: Nothing
// **************************************************************************************************/
void clockOutput()
{
  Serial.print("PATTERN STEP: ");
  Serial.print(currStep); // prints current pattern number
  Serial.print("   ");

  for (int i = 0; i < 16; i++)
  {
    Serial.print(currPattern->pattern[i][currStep]); // prints which instruments are played on this step
  }
  Serial.println(" ");
}

///**************************************************************************************************
// * Function displayLCD
// * -------------------------------------------------------------------------------------------------
// * Overview: handles displaying stuff on the LCD screen
// * Input:
// * Output: Nothing
// **************************************************************************************************/
void displayLCD(bool demoMode)
{
  if (demoMode) // forces demo mode if we are in demo mode
    lcdState = LCD_DEMO;

  // After changing tempo, display it for 3/4 of a second.
  // This checks if time is up and forces it to display tempo if not
  if (millis() > (tempoDispTimer + 750)) // time is up! stop displaying tempo
  {
    if (!tempoLcdFlag)
    {
      lcdState = lastLcdState; // if time is up go back to whatever was being displayed before
      tempoLcdFlag = true;     // flag says we'll be ready to switch back into tempo display mode next time we need to
    }
  }
  else // time is not up. Keep displaying tempo
  {
    if (tempoLcdFlag) // for switching into tempo display mode
    {
      tempoLcdFlag = false;    // flag so we only grab the current display state when we enter tempo display mode
      lastLcdState = lcdState; // grabs current display state and stores it before displaying tempo
      lcdState = LCD_TEMPO;    // moves over to tempo display mode
    }
  }

  switch (lcdState) // determine what we want to display on the LCD
  {
  case LCD_DEMO:                        // Demo mode! show a cute little animation
    if (millis() > LCDFrameTimer + 500) // only swap frames every half second
    {
      u8g2.clearBuffer();      // clear the internal memory
      switch (starsFrameCount) // which frame are we on?
      {
      case 0:
        u8g2.drawXBMP(0, 0, 84, 48, frame1); // display first frame
        starsFrameCount = 1;                 // move to the other frame
        break;
      case 1:
        u8g2.drawXBMP(0, 0, 84, 48, frame2); // display second frame
        starsFrameCount = 0;                 // move to the other frame
        break;
      }
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
                                          //     u8g2.drawStr(0,11,"Hello Worldo!");  // write something to the internal memory
      u8g2.drawStr(20, 30, " <3");        // write something to the internal memory
      u8g2.drawStr(40, 44, "drums!");     // write something to the internal memory
      u8g2.sendBuffer();                  // transfer internal memory to the display
      LCDFrameTimer = millis();
    }
    break;

  case LCD_INST_PROP: // mode for displaying paramter of selected instrument, and allows you to edit them
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      char paramStr[30];                  // char array for parameter value
      char volStr[30];                    // char array for volume value
      char envStr[30];                    // char array for envelope value

      switch (currInst) // set name string and parameters, these are unique to each instrument so i have this dumb huge switch statement :~(
      {
      case INST_BD:
        u8g2.drawStr(0, 11, "Bass Drum");
        break;
      case INST_SD:
        u8g2.drawStr(0, 11, "Snare Drum");
        break;
      case INST_CYN1:
        u8g2.drawStr(0, 11, "Cynare #1");
        break;
      case INST_CYN2:
        u8g2.drawStr(0, 11, "Cynare #2");
        break;
      case INST_GLITCH:
        u8g2.drawStr(0, 11, "Glitch");
        break;
      case INST_DIGI1:
        u8g2.drawStr(0, 11, "DigiDrum #1");
        break;
      case INST_DIGI2:
        u8g2.drawStr(0, 11, "DigiDrum #2");
        break;
      case INST_DIGI3:
        u8g2.drawStr(0, 11, "DigiDrum #3");
        break;
      case INST_SMP1:
        u8g2.drawStr(0, 11, "Casio Kick");
        sprintf(paramStr, "%.02f", currPattern->parameter[6][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[8][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[7][0]);
        break;
      case INST_SMP2:
        u8g2.drawStr(0, 11, "Casio Snare");
        sprintf(paramStr, "%.02f", currPattern->parameter[8][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[9][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[9][0]);
        break;
      case INST_SMP3:
        u8g2.drawStr(0, 11, "Casio CHH");
        sprintf(paramStr, "%.02f", currPattern->parameter[10][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[10][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[11][0]);
        break;
      case INST_SMP4:
        u8g2.drawStr(0, 11, "Casio OHH");
        sprintf(paramStr, "%.02f", currPattern->parameter[12][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[11][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[13][0]);
        break;
      case INST_SMP5:
        u8g2.drawStr(0, 11, "Casio Lo Cowbell");
        sprintf(paramStr, "%.02f", currPattern->parameter[14][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[12][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[15][0]);
        break;
      case INST_SMP6:
        u8g2.drawStr(0, 11, "Casio Hi Cowbell");
        sprintf(paramStr, "%.02f", currPattern->parameter[16][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[13][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[17][0]);
        break;
      case INST_SMP7:
        u8g2.drawStr(0, 11, "Casio Lo Tom");
        sprintf(paramStr, "%.02f", currPattern->parameter[18][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[14][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[19][0]);
        break;
      case INST_SMP8:
        u8g2.drawStr(0, 11, "Casio Hi Tom");
        sprintf(paramStr, "%.02f", currPattern->parameter[20][0]); // grab parameters from pattern object
        sprintf(volStr, "%.02f", currPattern->velocity[15][0]);
        sprintf(envStr, "%.01f", currPattern->parameter[21][0]);
        break;
      }
      if (currInst >= 8) // draw all the parameter stuff on the screen for instruments that need them
      {
        u8g2.setFontMode(0);
        u8g2.setDrawColor(1);
        u8g2.drawStr(0, 24, "spd:");
        u8g2.drawStr(30, 24, paramStr);
        u8g2.drawStr(0, 34, "vol:");
        u8g2.drawStr(30, 34, volStr);
        u8g2.drawStr(0, 44, "len: ");
        u8g2.drawStr(30, 44, envStr);

        u8g2.setDrawColor(2);
        if (paramSel) // draw a selection box
        {
          u8g2.drawBox(30, 15 + 10 * cursorLoc, 27, 11); // selection box on parameter being edited
        }
        else
        {
          u8g2.drawBox(0, 15 + 10 * cursorLoc, 27, 11); // selection box on menu for navigation
        }
      }
      u8g2.sendBuffer();        // transfer internal memory to the display
      LCDFrameTimer = millis(); // timer for next frame
    }
    break;
  case LCD_TEMPO: // displays the tempo
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.drawStr(10, 10, "BPM");
      char tempoStr[30];
      sprintf(tempoStr, "%.01f", tempo);
      u8g2.drawStr(30, 30, tempoStr);
      u8g2.sendBuffer();
      LCDFrameTimer = millis();
    }
    break;
  case LCD_KIT_SEL: // display kit selection menu
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Casio SK-1"); // draw kit names
      u8g2.drawStr(0, 24, "808");
      u8g2.drawStr(0, 34, "Happy Hxc");
      u8g2.setDrawColor(2);
      u8g2.drawBox(0, 5 + 10 * kitNum, 80, 11); // draw selection box
      u8g2.sendBuffer();
      LCDFrameTimer = millis();
    }
  }
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
  if (digitalRead(tempoEncAPin))
  {
    tempoEncAval = 1;
    UpdateTempoEnc();
  }
  else
  {
    tempoEncAval = 0;
    UpdateTempoEnc();
  }
}

void ISRtempoEncBChange()
{
  if (digitalRead(tempoEncBPin))
  {
    tempoEncBval = 1;
    UpdateTempoEnc();
  }
  else
  {
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
  switch (tempoEncState)
  {
  case 0: // Idle state, look for direction
    if (!tempoEncBval)
    {
      tempoEncState = 1; // CW 1
    }
    if (!tempoEncAval)
    {
      tempoEncState = 11; // CCW 1
    }
    break;
  case 1: // CW, wait for A low while B is low
    if (!tempoEncBval)
    {
      if (!tempoEncAval)
      {
        tempoEncAcc++;
        // update tempo variable
        tempo += 1;         // increment the tempo
        changeTempo(tempo); // and update that tempo
#ifdef DEMO
        Serial.print(" ..tempo right.. ");
#endif
        tempoDispTimer = millis(); // set timer to start displaying tempo
        tempoEncState = 2;         // CW 2
      }
    }
    else
    {
      if (tempoEncAval)
      {
        // It was just a glitch on B, go back to start
        tempoEncState = 0;
      }
    }
    break;
  case 2: // CW, wait for B high
    if (tempoEncBval)
    {
      tempoEncState = 3; // CW 3
    }
    break;
  case 3: // CW, wait for A high
    if (tempoEncAval)
    {
      tempoEncState = 0; // back to idle (detent) state
    }
    break;
  case 11: // CCW, wait for B low while A is low
    if (!tempoEncAval)
    {
      if (!tempoEncBval)
      {
        tempoEncAcc--;
        tempo -= 1;         // decrease tempo
        changeTempo(tempo); // and update that tempo
#ifdef DEMO
        Serial.print(" ..tempo left.. ");
#endif
        tempoDispTimer = millis(); // set timer to start displaying tempo
        tempoEncState = 12;        // CCW 2
      }
    }
    else
    {
      if (tempoEncBval)
      {
        // It was just a glitch on A, go back to start
        tempoEncState = 0;
      }
    }
    break;
  case 12: // CCW, wait for A high
    if (tempoEncAval)
    {
      tempoEncState = 13; // CCW 3
    }
    break;
  case 13: // CCW, wait for B high
    if (tempoEncBval)
    {
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
  if (digitalRead(dataEncAPin))
  {
    dataEncAval = 1;
    UpdateDataEnc();
  }
  else
  {
    dataEncAval = 0;
    UpdateDataEnc();
  }
}

void ISRdataEncBChange()
{
  if (digitalRead(dataEncBPin))
  {
    dataEncBval = 1;
    UpdateDataEnc();
  }
  else
  {
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
  switch (dataEncState)
  {
  case 0: // Idle state, look for direction
    if (!dataEncBval)
    {
      dataEncState = 1; // CW 1
    }
    if (!dataEncAval)
    {
      dataEncState = 11; // CCW 1
    }
    break;
  case 1: // CW, wait for A low while B is low
    if (!dataEncBval)
    {
      if (!dataEncAval)
      {
        dataEncAcc++;
#ifdef DEMO
        Serial.print(" ..data right.. "); // only print in demo mode
#endif
        //          Serial.println(currInst);
        if (controlState == KIT_SEL) // navigate kit selection menu
        {
          kitNum = (kitNum + 1);
          if (kitNum > 2)
            kitNum = 2;
        }
        else // SHOULD MAKE THIS MORE ROBUST WITH A SWITCH STATEMENT. We assume we're in parameter selection mode if not in KIT_SEL
        {
          if (paramSel) // if cursor is modifying parameter
          {
            switch (cursorLoc) // figure out which parameter is being modified
            {
            case 0:             // first parameter (playback speed) selected
              switch (currInst) // figure out which instrument we are modifying parameters on
              {
              case INST_SMP1:
                currPattern->parameter[6][0] += parameterInc;
                playSdRaw1.setPlaybackRate(currPattern->parameter[6][0]);
                break;
              case INST_SMP2:
                currPattern->parameter[8][0] += parameterInc;
                playSdRaw2.setPlaybackRate(currPattern->parameter[8][0]);
                break;
              case INST_SMP3:
                currPattern->parameter[10][0] += parameterInc;
                playSdRaw3.setPlaybackRate(currPattern->parameter[10][0]);
                break;
              case INST_SMP4:
                currPattern->parameter[12][0] += parameterInc;
                playSdRaw4.setPlaybackRate(currPattern->parameter[12][0]);
                break;
              case INST_SMP5:
                currPattern->parameter[14][0] += parameterInc;
                playSdRaw5.setPlaybackRate(currPattern->parameter[14][0]);
                break;
              case INST_SMP6:
                currPattern->parameter[16][0] += parameterInc;
                playSdRaw6.setPlaybackRate(currPattern->parameter[16][0]);
                break;
              case INST_SMP7:
                currPattern->parameter[18][0] += parameterInc;
                playSdRaw7.setPlaybackRate(currPattern->parameter[18][0]);
                break;
              case INST_SMP8:
                currPattern->parameter[20][0] += parameterInc;
                playSdRaw8.setPlaybackRate(currPattern->parameter[20][0]);
                break;
              }
              break;
            case 1:             // volume selected
              switch (currInst) // figure out which instrument we are modifying volumes on
              {
              case INST_SMP1:
                currPattern->velocity[8][0] += parameterInc;
                mixer1.gain(0, currPattern->velocity[8][0]);
                break;
              case INST_SMP2:
                currPattern->velocity[9][0] += parameterInc;
                mixer1.gain(1, currPattern->velocity[9][0]);
                break;
              case INST_SMP3:
                currPattern->velocity[10][0] += parameterInc;
                mixer1.gain(2, currPattern->velocity[10][0]);
                break;
              case INST_SMP4:
                currPattern->velocity[11][0] += parameterInc;
                mixer1.gain(3, currPattern->velocity[11][0]);
                break;
              case INST_SMP5:
                currPattern->velocity[12][0] += parameterInc;
                mixer2.gain(0, currPattern->velocity[12][0]);
                break;
              case INST_SMP6:
                currPattern->velocity[13][0] += parameterInc;
                mixer2.gain(1, currPattern->velocity[13][0]);
                break;
              case INST_SMP7:
                currPattern->velocity[14][0] += parameterInc;
                mixer2.gain(2, currPattern->velocity[14][0]);
                break;
              case INST_SMP8:
                currPattern->velocity[15][0] += parameterInc;
                mixer2.gain(3, currPattern->velocity[15][0]);
                break;
              }
              break;

            case 2:             // param 2 (length) selected
              switch (currInst) // figure out which instrument we are modifying the envelope parameter on
              {
              case INST_SMP1:
                currPattern->parameter[7][0] += 1;
                if (currPattern->parameter[7][0] > 100)
                  currPattern->parameter[7][0] = 100;
                break;
              case INST_SMP2:
                currPattern->parameter[9][0] += 1;
                if (currPattern->parameter[9][0] > 100)
                  currPattern->parameter[9][0] = 100;
                break;
              case INST_SMP3:
                currPattern->parameter[11][0] += 1;
                if (currPattern->parameter[11][0] > 100)
                  currPattern->parameter[11][0] = 100;
                break;
              case INST_SMP4:
                currPattern->parameter[13][0] += 1;
                if (currPattern->parameter[13][0] > 100)
                  currPattern->parameter[13][0] = 100;
                break;
              case INST_SMP5:
                currPattern->parameter[15][0] += 1;
                if (currPattern->parameter[15][0] > 100)
                  currPattern->parameter[15][0] = 100;
                break;
              case INST_SMP6:
                currPattern->parameter[17][0] += 1;
                if (currPattern->parameter[17][0] > 100)
                  currPattern->parameter[17][0] = 100;
                break;
              case INST_SMP7:
                currPattern->parameter[19][0] += 1;
                if (currPattern->parameter[19][0] > 100)
                  currPattern->parameter[19][0] = 100;
                break;
              case INST_SMP8:
                currPattern->parameter[21][0] += 1;
                if (currPattern->parameter[21][0] > 100)
                  currPattern->parameter[21][0] = 100;
                break;
              }
              break;
            }
          }
          else // navigate through menu
          {
            cursorLoc++;
            if (cursorLoc > 2)
              cursorLoc = 2;
          }
        }

        dataEncState = 2; // CW 2
      }
    }
    else
    {
      if (dataEncAval)
      {
        // It was just a glitch on B, go back to start
        dataEncState = 0;
      }
    }
    break;
  case 2: // CW, wait for B high
    if (dataEncBval)
    {
      dataEncState = 3; // CW 3
    }
    break;
  case 3: // CW, wait for A high
    if (dataEncAval)
    {
      dataEncState = 0; // back to idle (detent) state
    }
    break;
  case 11: // CCW, wait for B low while A is low
    if (!dataEncAval)
    {
      if (!dataEncBval)
      {
        dataEncAcc--;
#ifdef DEMO
        // Remove this when not in demo mode
        Serial.print(" ..data left.. ");
#endif
        //          Serial.println(currInst);
        if (controlState == KIT_SEL) // navigate kit selection menu
        {
          kitNum = (kitNum - 1);
          if (kitNum < 0)
            kitNum = 0;
        }
        else // SHOULD MAKE THIS MORE ROBUST WITH A SWITCH STATEMENT. We assume we're in parameter selection mode if not in KIT_SEL
        {
          if (paramSel) // if cursor is modifying parameter
          {
            switch (cursorLoc) // check which parameter is being modified
            {
            case 0:             // first parameter (playback speed) selected
              switch (currInst) // check which instrument is being modified
              {
              case INST_SMP1:
                currPattern->parameter[6][0] -= parameterInc;
                if (currPattern->parameter[6][0] < 0.05)
                  currPattern->parameter[6][0] = 0.05;
                playSdRaw1.setPlaybackRate(currPattern->parameter[6][0]);
                break;
              case INST_SMP2:
                currPattern->parameter[8][0] -= parameterInc;
                if (currPattern->parameter[8][0] < 0.05)
                  currPattern->parameter[8][0] = 0.05;
                playSdRaw2.setPlaybackRate(currPattern->parameter[8][0]);
                break;
              case INST_SMP3:
                currPattern->parameter[10][0] -= parameterInc;
                if (currPattern->parameter[10][0] < 0.05)
                  currPattern->parameter[10][0] = 0.05;
                playSdRaw3.setPlaybackRate(currPattern->parameter[10][0]);
                break;
              case INST_SMP4:
                currPattern->parameter[12][0] -= parameterInc;
                if (currPattern->parameter[12][0] < 0.05)
                  currPattern->parameter[12][0] = 0.05;
                playSdRaw4.setPlaybackRate(currPattern->parameter[12][0]);
                break;
              case INST_SMP5:
                currPattern->parameter[14][0] -= parameterInc;
                if (currPattern->parameter[14][0] < 0.05)
                  currPattern->parameter[14][0] = 0.05;
                playSdRaw5.setPlaybackRate(currPattern->parameter[14][0]);
                break;
              case INST_SMP6:
                currPattern->parameter[16][0] -= parameterInc;
                if (currPattern->parameter[16][0] < 0.05)
                  currPattern->parameter[16][0] = 0.05;
                playSdRaw6.setPlaybackRate(currPattern->parameter[16][0]);
                break;
              case INST_SMP7:
                currPattern->parameter[18][0] -= parameterInc;
                if (currPattern->parameter[18][0] < 0.05)
                  currPattern->parameter[18][0] = 0.05;
                playSdRaw7.setPlaybackRate(currPattern->parameter[18][0]);
                break;
              case INST_SMP8:
                currPattern->parameter[20][0] -= parameterInc;
                if (currPattern->parameter[20][0] < 0.05)
                  currPattern->parameter[20][0] = 0.05;
                playSdRaw8.setPlaybackRate(currPattern->parameter[20][0]);
                break;
              }
              break;

            case 1:             // volume is being modified
              switch (currInst) // check which instrument is being modified
              {
              case INST_SMP1:
                currPattern->velocity[8][0] -= parameterInc;
                if (currPattern->velocity[8][0] < 0)
                  currPattern->velocity[8][0] = 0;
                mixer1.gain(0, currPattern->velocity[8][0]);
                break;
              case INST_SMP2:
                currPattern->velocity[9][0] -= parameterInc;
                if (currPattern->velocity[9][0] < 0)
                  currPattern->velocity[9][0] = 0;
                mixer1.gain(1, currPattern->velocity[9][0]);
                break;
              case INST_SMP3:
                currPattern->velocity[10][0] -= parameterInc;
                if (currPattern->velocity[10][0] < 0)
                  currPattern->velocity[10][0] = 0;
                mixer1.gain(2, currPattern->velocity[10][0]);
                break;
              case INST_SMP4:
                currPattern->velocity[11][0] -= parameterInc;
                if (currPattern->velocity[11][0] < 0)
                  currPattern->velocity[11][0] = 0;
                mixer1.gain(3, currPattern->velocity[11][0]);
                break;
              case INST_SMP5:
                currPattern->velocity[12][0] -= parameterInc;
                if (currPattern->velocity[12][0] < 0)
                  currPattern->velocity[12][0] = 0;
                mixer2.gain(0, currPattern->velocity[12][0]);
                break;
              case INST_SMP6:
                currPattern->velocity[13][0] -= parameterInc;
                if (currPattern->velocity[13][0] < 0)
                  currPattern->velocity[13][0] = 0;
                mixer2.gain(1, currPattern->velocity[13][0]);
                break;
              case INST_SMP7:
                currPattern->velocity[14][0] -= parameterInc;
                if (currPattern->velocity[14][0] < 0)
                  currPattern->velocity[14][0] = 0;
                mixer2.gain(2, currPattern->velocity[14][0]);
                break;
              case INST_SMP8:
                currPattern->velocity[15][0] -= parameterInc;
                if (currPattern->velocity[15][0] < 0)
                  currPattern->velocity[15][0] = 0;
                mixer2.gain(3, currPattern->velocity[15][0]);
                break;
              }
              break;
            case 2:             // param 2 (length) selected
              switch (currInst) // check which instrument is being modified
              {
              case INST_SMP1:
                currPattern->parameter[7][0] -= 1;
                if (currPattern->parameter[7][0] < 0)
                  currPattern->parameter[7][0] = 1;
                break;
              case INST_SMP2:
                currPattern->parameter[9][0] -= 1;
                if (currPattern->parameter[9][0] < 0)
                  currPattern->parameter[9][0] = 1;
                break;
              case INST_SMP3:
                currPattern->parameter[11][0] -= 1;
                if (currPattern->parameter[11][0] < 0)
                  currPattern->parameter[11][0] = 1;
                break;
              case INST_SMP4:
                currPattern->parameter[13][0] -= 1;
                if (currPattern->parameter[13][0] < 0)
                  currPattern->parameter[13][0] = 1;
                break;
              case INST_SMP5:
                currPattern->parameter[15][0] -= 1;
                if (currPattern->parameter[15][0] < 0)
                  currPattern->parameter[15][0] = 1;
                break;
              case INST_SMP6:
                currPattern->parameter[17][0] -= 1;
                if (currPattern->parameter[17][0] < 0)
                  currPattern->parameter[17][0] = 1;
                break;
              case INST_SMP7:
                currPattern->parameter[19][0] -= 1;
                if (currPattern->parameter[19][0] < 0)
                  currPattern->parameter[19][0] = 1;
                break;
              case INST_SMP8:
                currPattern->parameter[21][0] -= 1;
                if (currPattern->parameter[21][0] < 0)
                  currPattern->parameter[21][0] = 1;
                break;
              }
              break;
            }
          }
          else // navigate through parameter menu
          {
            cursorLoc--;
            if (cursorLoc < 0)
              cursorLoc = 0;
          }
        }
        dataEncState = 12; // CCW 2
      }
    }
    else
    {
      if (dataEncBval)
      {
        // It was just a glitch on A, go back to start
        dataEncState = 0;
      }
    }
    break;
  case 12: // CCW, wait for A high
    if (dataEncAval)
    {
      dataEncState = 13; // CCW 3
    }
    break;
  case 13: // CCW, wait for B high
    if (dataEncBval)
    {
      dataEncState = 0; // back to idle (detent) state
    }
    break;
  }
}

///**************************************************************************************************
// * Function recallParameters
// * -------------------------------------------------------------------------------------------------
// * Overview: Grabs parameter (and tempo) values from pattern object and applies them to instruments
// *           Currently this uses zero indexed parameter for entire pattern but eventually it would be cool to allow step-wise parameter edit/recall
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
void recallParameters()
{
  mixer1.gain(0, currPattern->velocity[8][0]);
  mixer1.gain(1, currPattern->velocity[9][0]);
  mixer1.gain(2, currPattern->velocity[10][0]);
  mixer1.gain(3, currPattern->velocity[11][0]);
  mixer2.gain(0, currPattern->velocity[12][0]);
  mixer2.gain(1, currPattern->velocity[13][0]);
  mixer2.gain(2, currPattern->velocity[14][0]);
  mixer2.gain(3, currPattern->velocity[15][0]);
  playSdRaw1.setPlaybackRate(currPattern->parameter[6][0]);
  playSdRaw2.setPlaybackRate(currPattern->parameter[8][0]);
  playSdRaw3.setPlaybackRate(currPattern->parameter[10][0]);
  playSdRaw4.setPlaybackRate(currPattern->parameter[12][0]);
  playSdRaw5.setPlaybackRate(currPattern->parameter[14][0]);
  playSdRaw6.setPlaybackRate(currPattern->parameter[16][0]);
  playSdRaw7.setPlaybackRate(currPattern->parameter[18][0]);
  playSdRaw8.setPlaybackRate(currPattern->parameter[20][0]);

  changeTempo(currPattern->settings[0]); // probably don't need this here. This function is run every step and tempo won't be changing per step
}

///**************************************************************************************************
// * Function changeKit
// * -------------------------------------------------------------------------------------------------
// * Overview: changes the 8 samples on the main instrument layer to another kit
// * Input:
// *        int kit_number: number of the  kit to select, associations defined within function
// * Output: Nothing
// **************************************************************************************************/
void changeKit(int kit_number)
{
  newdigate::flashloader loader;
  switch (kit_number)
  {
  case 0: // CasioSK1
    sample1 = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");
    sample2 = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");
    sample2 = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");
    sample3 = loader.loadSample("DRUMS/CASIOSK1/CHH.RAW");
    sample4 = loader.loadSample("DRUMS/CASIOSK1/OHH.RAW");
    sample5 = loader.loadSample("DRUMS/CASIOSK1/CB_LO.RAW");
    sample6 = loader.loadSample("DRUMS/CASIOSK1/CB_HI.RAW");
    sample7 = loader.loadSample("DRUMS/CASIOSK1/SKLOTOM.RAW");
    sample8 = loader.loadSample("DRUMS/CASIOSK1/SKHITOM.RAW");
    sample1 = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");
    sample9 = loader.loadSample("BREAKS/AMEN175.RAW");
    break;
  case 1: // 808
    sample1 = loader.loadSample("DRUMS/808/KICK.RAW");
    sample2 = loader.loadSample("DRUMS/808/SNARE.RAW");
    sample2 = loader.loadSample("DRUMS/808/SNARE.RAW");
    sample3 = loader.loadSample("DRUMS/808/CHH.RAW");
    sample4 = loader.loadSample("DRUMS/808/OHH.RAW");
    sample5 = loader.loadSample("DRUMS/808/CYM.RAW");
    sample6 = loader.loadSample("DRUMS/808/CYM_REV.RAW");
    sample7 = loader.loadSample("DRUMS/808/CL.RAW");
    sample8 = loader.loadSample("DRUMS/808/CB.RAW");
    sample9 = loader.loadSample("BREAKS/AMEN175.RAW");
    break;
  case 2: // Happy Hardcore
    sample1 = loader.loadSample("DRUMS/HPYHXC/KICK.RAW");
    sample2 = loader.loadSample("DRUMS/HPYHXC/KICK2.RAW");
    sample3 = loader.loadSample("DRUMS/HPYHXC/SNARE.RAW");
    sample4 = loader.loadSample("DRUMS/HPYHXC/CLAP.RAW");
    sample5 = loader.loadSample("DRUMS/HPYHXC/CHH.RAW");
    sample6 = loader.loadSample("DRUMS/HPYHXC/OHH.RAW");
    sample7 = loader.loadSample("DRUMS/HPYHXC/RIDE.RAW");
    sample8 = loader.loadSample("DRUMS/HPYHXC/CRASH.RAW");
    sample9 = loader.loadSample("BREAKS/AMEN175.RAW");
    break;
  }
}

///**************************************************************************************************
// * Function stopSamples
// * -------------------------------------------------------------------------------------------------
// * Overview: stops all currently playing samples
// * Input:
// * Output: Nothing
// **************************************************************************************************/
void stopSamples()
{
  playSdRaw1.stop();
  playSdRaw2.stop();
  playSdRaw3.stop();
  playSdRaw4.stop();
  playSdRaw5.stop();
  playSdRaw6.stop();
  playSdRaw7.stop();
  playSdRaw8.stop();
  playSdRaw9.stop();
}
