#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <CSV_Parser.h>
#include <U8g2lib.h>
#include "Pattern.h"
#include "Song.h"
#include <TeensyVariablePlayback.h>
#include "flashloader.h"
#include <MIDI.h>

// #define DEMO 1

#define LCD_SCK 13
#define LCD_MOSI 11
#define LCD_MISO 12
#define LCD_DC 25
#define LCD_CS 10
#define LCD_RST 24

#define GRANULAR_MEMORY_SIZE 12800 // enough for 290 ms at 44.1 kHz

#define SDCARD_CS_PIN BUILTIN_SDCARD

#define NUM_BANKS 2

#define CHAR_BUFF_SIZE 4

#define NUM_KITS 11

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
  INST_SMP8,
  INST_ORGAN_CHORDS,
  INST_GUITAR_CHORDS,
  INST_GUITAR_ONE,
  INST_ORGAN_NOTES,
  INST_ORGAN_NOTES_2,
  INST_ORGAN_NOTES_3,
  INST_ORGAN_NOTES_4,
  INST_ORGAN_NOTES_5
};

enum lcdStates
{
  LCD_INST_PROP,
  LCD_TEMPO,
  LCD_DEMO,
  LCD_KIT_SEL,
  LCD_SONG_WRITE,
  LCD_SONG_SEL,
  LCD_PATT_SEL,
  LCD_INST_BANK,
  LCD_PATT_BANK,
  LCD_SONG_BANK,
  LCD_LENGTH_SEL,
  LCD_PATTERN_WRITE
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
  KIT_SEL,
  SONG_WRITE,
  INST_BANK_SEL,
  PATTERN_BANK_SEL,
  SONG_BANK_SEL,
  LENGTH_SEL,
  PLAY_STEP_SEL,
  PATTERN_WRITE
};

enum ledDisplayStates
{
  DISP_STEPS,
  DISP_PATTERNS,
  DISP_SONGS,
  DISP_INST,
  DISP_PATT_BANK,
  DISP_SONG_BANK,
  DISP_INST_BANK
};

enum playMode
{
  PLAY_PATTERN,
  PLAY_SONG
};

//------EXTERNAL QSPI RAM CHIP SECTION BEGIN------
// EXTMEM char myAudioBlock[AUDIO_BLOCK_LEN]; // block of memory for audio
//                         9099342
EXTMEM Song SongStorage[NUM_BANKS][16];
EXTMEM Pattern PatternStorage[NUM_BANKS][16];
EXTMEM int16_t granularMemory1[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory2[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory3[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory4[GRANULAR_MEMORY_SIZE];
EXTMEM int16_t granularMemory5[GRANULAR_MEMORY_SIZE];
newdigate::audiosample *kitSamples[NUM_KITS][8]; // samples for bank A kits
//------EXTERNAL QSPI RAM CHIP SECTION END------

// Pattern variables
Pattern *currPattern;
int patternNum = 1;
int nextPattern = 1;
int patternQueue[16];
int patternQueueLen = 1;
int patternQueueIndex = 0;
int patternQueueWriteIndex = 0;
Pattern *myCopiedPattern;

// Song Variables
Song *currSong;
int songNum = 0;
int songWriteIndex = 0;

//MIDI
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
int midiChannel = 1;

// bank A kit
AudioPlayArrayResmp playSdRaw1; // xy=321,513
AudioPlayArrayResmp playSdRaw2; // xy=321,513
AudioPlayArrayResmp playSdRaw3; // xy=321,513
AudioPlayArrayResmp playSdRaw4; // xy=321,513
AudioPlayArrayResmp playSdRaw5; // xy=321,513
AudioPlayArrayResmp playSdRaw6; // xy=321,513
AudioPlayArrayResmp playSdRaw7; // xy=321,513
AudioPlayArrayResmp playSdRaw8; // xy=321,513

// bank A break
AudioPlayArrayResmp playSdRaw9; // xy=321,513

// bank B
AudioPlayArrayResmp playSdRaw10; // xy=321,513
AudioPlayArrayResmp playSdRaw11; // xy=321,513
AudioPlayArrayResmp playSdRaw12; // xy=321,513
AudioPlayArrayResmp playSdRaw13; // xy=321,513
AudioPlayArrayResmp playSdRaw14; // xy=321,513
AudioPlayArrayResmp playSdRaw15; // xy=321,513
AudioPlayArrayResmp playSdRaw16; // xy=321,513
AudioPlayArrayResmp playSdRaw17; // xy=321,513
AudioPlayArrayResmp playSdRaw18; // xy=321,513
AudioPlayArrayResmp playSdRaw19; // xy=321,513
AudioPlayArrayResmp playSdRaw20; // xy=321,513
AudioPlayArrayResmp playSdRaw21; // xy=321,513
AudioPlayArrayResmp playSdRaw22; // xy=321,513
AudioPlayArrayResmp playSdRaw23; // xy=321,513
AudioPlayArrayResmp playSdRaw24; // xy=321,513
AudioPlayArrayResmp playSdRaw25; // xy=321,513



const char *kitNames[NUM_KITS][8] = {
    {"KICK","SNARE","CHH", "OHH", "LO CB", "HI CB", "LO TOM", "HI TOM"}, // casio
    {"KICK","SNARE","CHH", "OHH", "CYM", "REV CYM", "Clave", "CB"},      //808
    {"KICK","KICK2","SNARE", "CLAP", "CHH", "OHH", "Ride", "Crash"},     // happy hardcore
    {"KICK","SNARE","CHH", "OHH", "HI TOM", "LO TOM", "CRASH", "SPLASH"}, // akai amb
    {"KICK","SNARE","CHH", "OHH", "HI TOM", "MID TOM", "LO TOM", "STICK"}, // akai bedroom
    {"KICK","SNARE","CHH", "OHH", "BIGKICK", "COWKICK", "CHH2", "CRASH"}, // akai garage
    {"KICK","SNARE","CHH", "OHH", "HAT2", "CB", "BLOCK", "SHAKER"}, // emu mophat clear
    {"KICK","SNARE","CHH", "OHH", "HI SNARE", "CLAP", "REV", "BOOM"}, // emu mophat dark
    {"KICK","SNARE","CHH", "OHH", "RIM", "HALFHAT", "SHAKER", "TAMB"},  // alesis hr16
    {"KICK","SNARE","CHH", "OHH", "SNARE 2", "DING", "CLANG", "TOM"}, // elektron clean
    {"KICK","SNARE","CHH", "OHH", "SNARE 2", "CLICK", "CRUNCH", "CLANG"} // elektron crush
//    {"KICK","SNARE","CHH", "OHH", "SNARE 2", "RATTLE", "MECH", "CLANG"}  // elektron noisy
  };
  
newdigate::audiosample *chordSamples[3][7]; // samples for organ and guitar chords
                                            // 0 - Cmaj
                                            // 1 - Cmin
                                            // 2 - C7
                                            // 3 - Cmaj7
                                            // 4 - Cmin7
                                            // 5 - Cdim
                                            // 6 - Caug

newdigate::audiosample *organNotes[8];

newdigate::audiosample *sample9;
newdigate::audiosample *sample10;

// GUItool: begin automatically generated code
AudioSynthSimpleDrum drum2; // xy=55,814
AudioSynthSimpleDrum drum3; // xy=55,858
// AudioPlaySdRaw           playSdRaw9;     //xy=69.5,917
AudioSynthSimpleDrum drum1; // xy=71,754
// AudioPlaySdRaw           playSdRaw1;     //xy=93,353
// AudioPlaySdRaw           playSdRaw2;     //xy=96,395
// AudioPlaySdRaw           playSdRaw3;     //xy=112,440
// AudioPlaySdRaw           playSdRaw7;     //xy=112,616
// AudioPlaySdRaw           playSdRaw12;    //xy=111,1046
// AudioPlaySdRaw           playSdRaw6;     //xy=113,577
// AudioPlaySdRaw           playSdRaw13;    //xy=112,1087
// AudioPlaySdRaw           playSdRaw4;     //xy=116,490
// AudioPlaySdRaw           playSdRaw11;    //xy=114,1003
// AudioPlaySdRaw           playSdRaw5;     //xy=116,536
// AudioPlaySdRaw           playSdRaw10;    //xy=116,966
// AudioPlaySdRaw           playSdRaw8;     //xy=122,660
// AudioPlaySdRaw           playSdRaw14;    //xy=146,1347
// AudioPlaySdRaw           playSdRaw16;    //xy=148,1419
// AudioPlaySdRaw           playSdRaw15;    //xy=151,1383
// AudioPlaySdRaw           playSdRaw21;    //xy=150,1638
// AudioPlaySdRaw           playSdRaw20;    //xy=151,1595
// AudioPlaySdRaw           playSdRaw17;    //xy=152,1464
// AudioPlaySdRaw           playSdRaw18;    //xy=153,1512
// AudioPlaySdRaw           playSdRaw19;    //xy=154,1551
// AudioPlaySdRaw           playSdRaw25;    //xy=163,1838
// AudioPlaySdRaw           playSdRaw23;    //xy=164,1753
// AudioPlaySdRaw           playSdRaw24;    //xy=164,1793
// AudioPlaySdRaw           playSdRaw22;    //xy=166,1713
AudioMixer4 mixer4;                // xy=224,762
AudioEffectGranular granular1;     // xy=228,917
AudioEffectGranular granular5;     // xy=299,1091
AudioEffectGranular granular4;     // xy=300,1049
AudioEffectGranular granular3;     // xy=301,1003
AudioEffectGranular granular2;     // xy=303,963
AudioMixer4 mixer7;                // xy=324,1366
AudioMixer4 mixer8;                // xy=325,1528
AudioMixer4 mixer9;                // xy=334,1738
AudioMixer4 mixer1;                // xy=342,380
AudioMixer4 mixer2;                // xy=385,599
AudioMixer4 mixer6;                // xy=497,1007
AudioMixer4 mixer3;                // xy=610,595
AudioEffectBitcrusher bitcrusher2; // xy=768,604
AudioEffectBitcrusher bitcrusher1; // xy=772,569
AudioMixer4 mixer5;                // xy=860,1053
AudioOutputI2S i2s1;               // xy=941,571
AudioConnection patchCord1(drum2, 0, mixer4, 1);
AudioConnection patchCord2(drum3, 0, mixer4, 2);
AudioConnection patchCord3(playSdRaw9, granular1);
AudioConnection patchCord4(drum1, 0, mixer4, 0);
AudioConnection patchCord5(playSdRaw1, 0, mixer1, 0);
AudioConnection patchCord6(playSdRaw2, 0, mixer1, 1);
AudioConnection patchCord7(playSdRaw3, 0, mixer1, 2);
AudioConnection patchCord8(playSdRaw7, 0, mixer2, 2);
AudioConnection patchCord9(playSdRaw12, granular4);
AudioConnection patchCord10(playSdRaw6, 0, mixer2, 1);
AudioConnection patchCord11(playSdRaw13, granular5);
AudioConnection patchCord12(playSdRaw4, 0, mixer1, 3);
AudioConnection patchCord13(playSdRaw11, granular3);
AudioConnection patchCord14(playSdRaw5, 0, mixer2, 0);
AudioConnection patchCord15(playSdRaw10, granular2);
AudioConnection patchCord16(playSdRaw8, 0, mixer2, 3);
AudioConnection patchCord17(playSdRaw14, 0, mixer7, 0);
AudioConnection patchCord18(playSdRaw16, 0, mixer7, 2);
AudioConnection patchCord19(playSdRaw15, 0, mixer7, 1);
AudioConnection patchCord20(playSdRaw21, 0, mixer8, 3);
AudioConnection patchCord21(playSdRaw20, 0, mixer8, 2);
AudioConnection patchCord22(playSdRaw17, 0, mixer7, 3);
AudioConnection patchCord23(playSdRaw18, 0, mixer8, 0);
AudioConnection patchCord24(playSdRaw19, 0, mixer8, 1);
AudioConnection patchCord25(playSdRaw25, 0, mixer9, 3);
AudioConnection patchCord26(playSdRaw23, 0, mixer9, 1);
AudioConnection patchCord27(playSdRaw24, 0, mixer9, 2);
AudioConnection patchCord28(playSdRaw22, 0, mixer9, 0);
AudioConnection patchCord29(mixer4, 0, mixer3, 2);
AudioConnection patchCord30(granular1, 0, mixer4, 3);
AudioConnection patchCord31(granular5, 0, mixer6, 3);
AudioConnection patchCord32(granular4, 0, mixer6, 2);
AudioConnection patchCord33(granular3, 0, mixer6, 1);
AudioConnection patchCord34(granular2, 0, mixer6, 0);
AudioConnection patchCord35(mixer7, 0, mixer5, 1);
AudioConnection patchCord36(mixer8, 0, mixer5, 2);
AudioConnection patchCord37(mixer9, 0, mixer5, 3);
AudioConnection patchCord38(mixer1, 0, mixer3, 0);
AudioConnection patchCord39(mixer2, 0, mixer3, 1);
AudioConnection patchCord40(mixer6, 0, mixer5, 0);
AudioConnection patchCord41(mixer3, bitcrusher1);
AudioConnection patchCord42(mixer3, bitcrusher2);
AudioConnection patchCord43(bitcrusher2, 0, i2s1, 1);
AudioConnection patchCord44(bitcrusher1, 0, i2s1, 0);
AudioConnection patchCord45(mixer5, 0, mixer3, 3);
AudioControlSGTL5000 sgtl5000_1; // xy=713,316
// GUItool: end automatically generated code

// transport variables
float tempo = 120;
unsigned int stepLen = 0;
int currStep = 0;
unsigned long currStepTime = 0;

int transportState = PLAYING;
int currInst = INST_BD;
int controlState = STEP_SEL;
int ledDisplayState = DISP_STEPS;
int lcdState = LCD_INST_PROP;
int lastLcdState = LCD_INST_PROP;
bool tempoLcdFlag = true;
int prevState = STEP_SEL;

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

bool sr0LED[8] = {false, false, false, false, false, false, false, false};
bool sr1LED[8] = {false, false, false, false, false, false, false, false};
bool sr2LED[8] = {false, false, false, false, false, false, false, false};
bool sr3LED[8] = {false, false, false, false, false, false, false, false};
bool stepLEDs[16] = {false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false};

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
int kitSel = 0;
int prevControlState = STEP_SEL;
int prevLcdState = LCD_INST_PROP;
int instBankNum = 0;
int pattBankNum = 0;
int songBankNum = 0;
int pattWriteSel = 0;

// playback stuff
int playMode = PLAY_PATTERN;
int songPlayStep = 0;
int patternPlaySection = 0;

// chord playback
int stepEditIndex = 0;
const char rootNotes[12][6] = {"C", "C#/Db", "D", "D#/Eb", "E", "F", "F#/Gb", "G", "G#/Ab", "A", "A#/Bb", "B"};
const char chordQual[7][6] = {"maj", "min", "7", "maj7", "min7", "dim", "aug"};
int chordCursorLoc = 0;
int instChordTypes[3] = {0, 0, 0};

//MIDI sync
float midi24ppqMs = 20;
float midi24ppqUs = 20000;
unsigned long midiClockTimer = 0;

volatile int s;

unsigned long pauseBlinkTimer = 0;
bool pauseLedState = true;

void setup()
{
  Serial.begin(115200); // start serial and give a welcome message :~)
  Serial.print("Hellooo: ");

  u8g2.begin();           // start communication with LCD
  AudioMemory(20);        // THIS IS REALLY IMPORTANTT!! CHECK THAT MEMORY USAGE
  sgtl5000_1.enable();    // enable the output
  sgtl5000_1.volume(0.5); // set master volume on output

  // setup for shift register
  pinMode(SH_CP, OUTPUT); // clock pin
  pinMode(ST_CP, OUTPUT); // latch
  pinMode(DS, OUTPUT);    // data pin

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
  sr3LED[7] = 1;

//   flash setup
  //----SD CARD setup
  if (!(SD.begin(SDCARD_CS_PIN)))
  {
    // stop here, but print a message repetitively
    Serial.println("SD fail!");
  }
  
  // load patterns from SD Card ::: NOTE THIS TAKES LIKE 10 SEC TO LOAD ALL BANKS
  for (int j = 0; j < NUM_BANKS; j++)
  { // limit on j determines how many banks to load
    for (int i = 0; i < 16; i++)
    {
      char myFullArr[25];
      sprintf(myFullArr, "/PATTERNS/%i/%i.CSV", j + 1, i + 1);
      PatternStorage[j][i].readFromSD((const char *)myFullArr);
      sprintf(myFullArr, "/SONGS/%i/%i.CSV", j + 1, i + 1);
      SongStorage[j][i].readFromSD(myFullArr);
    }
  }

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
  playSdRaw10.enableInterpolation(true);
  playSdRaw11.enableInterpolation(true);
  playSdRaw12.enableInterpolation(true);
  playSdRaw13.enableInterpolation(true);
  playSdRaw14.enableInterpolation(true);
  playSdRaw15.enableInterpolation(true);
  playSdRaw16.enableInterpolation(true);
  playSdRaw17.enableInterpolation(true);
  playSdRaw18.enableInterpolation(true);
  playSdRaw19.enableInterpolation(true);
  playSdRaw20.enableInterpolation(true);
  playSdRaw21.enableInterpolation(true);
  playSdRaw22.enableInterpolation(true);
  playSdRaw23.enableInterpolation(true);
  playSdRaw24.enableInterpolation(true);
  playSdRaw25.enableInterpolation(true);

  playSdRaw1.setPlaybackRate(1);
  playSdRaw2.setPlaybackRate(1);
  playSdRaw3.setPlaybackRate(1);
  playSdRaw4.setPlaybackRate(1);
  playSdRaw5.setPlaybackRate(1);
  playSdRaw6.setPlaybackRate(1);
  playSdRaw7.setPlaybackRate(1);
  playSdRaw8.setPlaybackRate(1);
  playSdRaw9.setPlaybackRate(1);
  playSdRaw10.setPlaybackRate(1);
  playSdRaw11.setPlaybackRate(1);
  playSdRaw12.setPlaybackRate(1);
  playSdRaw13.setPlaybackRate(1);
  playSdRaw14.setPlaybackRate(1);
  playSdRaw15.setPlaybackRate(1);
  playSdRaw16.setPlaybackRate(1);
  playSdRaw17.setPlaybackRate(1);
  playSdRaw18.setPlaybackRate(1);
  playSdRaw19.setPlaybackRate(1);
  playSdRaw20.setPlaybackRate(1);
  playSdRaw21.setPlaybackRate(1);
  playSdRaw22.setPlaybackRate(1);
  playSdRaw23.setPlaybackRate(1);
  playSdRaw24.setPlaybackRate(1);
  playSdRaw24.setPlaybackRate(1);

  playSdRaw9.setPlaybackRate(tempo / 175.0);

  newdigate::flashloader loader;

  kitSamples[0][0] = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");
  kitSamples[0][1] = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");
  kitSamples[0][2] = loader.loadSample("DRUMS/CASIOSK1/CHH.RAW");
  kitSamples[0][3] = loader.loadSample("DRUMS/CASIOSK1/OHH.RAW");
  kitSamples[0][4] = loader.loadSample("DRUMS/CASIOSK1/CB_LO.RAW");
  kitSamples[0][5] = loader.loadSample("DRUMS/CASIOSK1/CB_HI.RAW");
  kitSamples[0][6] = loader.loadSample("DRUMS/CASIOSK1/SKLOTOM.RAW");
  kitSamples[0][7] = loader.loadSample("DRUMS/CASIOSK1/SKHITOM.RAW");

  kitSamples[0][0] = loader.loadSample("DRUMS/CASIOSK1/KICK.RAW");
  kitSamples[0][1] = loader.loadSample("DRUMS/CASIOSK1/SNARE.RAW");

  kitSamples[1][0] = loader.loadSample("DRUMS/808/KICK.RAW");
  kitSamples[1][1] = loader.loadSample("DRUMS/808/SNARE.RAW");
  kitSamples[1][2] = loader.loadSample("DRUMS/808/CHH.RAW");
  kitSamples[1][3] = loader.loadSample("DRUMS/808/OHH.RAW");
  kitSamples[1][4] = loader.loadSample("DRUMS/808/CYM.RAW");
  kitSamples[1][5] = loader.loadSample("DRUMS/808/CYM_REV.RAW");
  kitSamples[1][6] = loader.loadSample("DRUMS/808/CL.RAW");
  kitSamples[1][7] = loader.loadSample("DRUMS/808/CB.RAW");

  kitSamples[2][0] = loader.loadSample("DRUMS/HPYHXC/KICK.RAW");
  kitSamples[2][1] = loader.loadSample("DRUMS/HPYHXC/KICK2.RAW");
  kitSamples[2][2] = loader.loadSample("DRUMS/HPYHXC/SNARE.RAW");
  kitSamples[2][3] = loader.loadSample("DRUMS/HPYHXC/CLAP.RAW");
  kitSamples[2][4] = loader.loadSample("DRUMS/HPYHXC/CHH.RAW");
  kitSamples[2][5] = loader.loadSample("DRUMS/HPYHXC/OHH.RAW");
  kitSamples[2][6] = loader.loadSample("DRUMS/HPYHXC/RIDE.RAW");
  kitSamples[2][7] = loader.loadSample("DRUMS/HPYHXC/CRASH.RAW");

  kitSamples[3][0] = loader.loadSample("DRUMS/AKAI_AMB/KICK.RAW");
  kitSamples[3][1] = loader.loadSample("DRUMS/AKAI_AMB/SNARE.RAW");
  kitSamples[3][2] = loader.loadSample("DRUMS/AKAI_AMB/CHH.RAW");
  kitSamples[3][3] = loader.loadSample("DRUMS/AKAI_AMB/OHH.RAW");
  kitSamples[3][4] = loader.loadSample("DRUMS/AKAI_AMB/HITOM.RAW");
  kitSamples[3][5] = loader.loadSample("DRUMS/AKAI_AMB/MIDTOM.RAW");
  kitSamples[3][6] = loader.loadSample("DRUMS/AKAI_AMB/CRASH.RAW");
  kitSamples[3][7] = loader.loadSample("DRUMS/AKAI_AMB/SPLASH.RAW");

  kitSamples[4][0] = loader.loadSample("DRUMS/AKAI_BDRM/KICK.RAW");
  kitSamples[4][1] = loader.loadSample("DRUMS/AKAI_BDRM/SNARE.RAW");
  kitSamples[4][2] = loader.loadSample("DRUMS/AKAI_BDRM/CHH.RAW");
  kitSamples[4][3] = loader.loadSample("DRUMS/AKAI_BDRM/OHH.RAW");
  kitSamples[4][4] = loader.loadSample("DRUMS/AKAI_BDRM/HITOM.RAW");
  kitSamples[4][5] = loader.loadSample("DRUMS/AKAI_BDRM/MIDTOM.RAW");
  kitSamples[4][6] = loader.loadSample("DRUMS/AKAI_BDRM/LOTOM.RAW");
  kitSamples[4][7] = loader.loadSample("DRUMS/AKAI_BDRM/STICK.RAW");

  kitSamples[5][0] = loader.loadSample("DRUMS/AKAI_GARAGE/KICK.RAW");
  kitSamples[5][1] = loader.loadSample("DRUMS/AKAI_GARAGE/SNARE.RAW");
  kitSamples[5][2] = loader.loadSample("DRUMS/AKAI_GARAGE/CHH.RAW");
  kitSamples[5][3] = loader.loadSample("DRUMS/AKAI_GARAGE/OHH.RAW");
  kitSamples[5][4] = loader.loadSample("DRUMS/AKAI_GARAGE/BIGKICK.RAW");
  kitSamples[5][5] = loader.loadSample("DRUMS/AKAI_GARAGE/COWKICK.RAW");
  kitSamples[5][6] = loader.loadSample("DRUMS/AKAI_GARAGE/CHH2.RAW");
  kitSamples[5][7] = loader.loadSample("DRUMS/AKAI_GARAGE/CRASH.RAW");

  kitSamples[6][0] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/KICK.RAW");
  kitSamples[6][1] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/SNARE.RAW");
  kitSamples[6][2] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/CHH.RAW");
  kitSamples[6][3] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/OHH.RAW");
  kitSamples[6][4] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/HAT2.RAW");
  kitSamples[6][5] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/CB.RAW");
  kitSamples[6][6] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/BLOCK.RAW");
  kitSamples[6][7] = loader.loadSample("DRUMS/EMU_MOPHAT_CLEAR/SHAKER.RAW");

  kitSamples[7][0] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/KICK.RAW");
  kitSamples[7][1] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/LOSNARE.RAW");
  kitSamples[7][2] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/CHH.RAW");
  kitSamples[7][3] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/OHH.RAW");
  kitSamples[7][4] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/HISNARE.RAW");
  kitSamples[7][5] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/CLAP.RAW");
  kitSamples[7][6] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/REV.RAW");
  kitSamples[7][7] = loader.loadSample("DRUMS/EMU_MOPHAT_DARK/BOOM.RAW");

  kitSamples[8][0] = loader.loadSample("DRUMS/ALESIS_HR16/KICK.RAW");
  kitSamples[8][1] = loader.loadSample("DRUMS/ALESIS_HR16/SNARE.RAW");
  kitSamples[8][2] = loader.loadSample("DRUMS/ALESIS_HR16/CHH.RAW");
  kitSamples[8][3] = loader.loadSample("DRUMS/ALESIS_HR16/OHH.RAW");
  kitSamples[8][4] = loader.loadSample("DRUMS/ALESIS_HR16/RIM.RAW");
  kitSamples[8][5] = loader.loadSample("DRUMS/ALESIS_HR16/HALFHAT.RAW");
  kitSamples[8][6] = loader.loadSample("DRUMS/ALESIS_HR16/SHAKER.RAW");
  kitSamples[8][7] = loader.loadSample("DRUMS/ALESIS_HR16/TAMB.RAW");

  kitSamples[9][0] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/KICK.RAW");
  kitSamples[9][1] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/SNARE.RAW");
  kitSamples[9][2] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/CHH.RAW");
  kitSamples[9][3] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/OHH.RAW");
  kitSamples[9][4] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/SNARE2.RAW");
  kitSamples[9][5] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/DING.RAW");
  kitSamples[9][6] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/CLANG.RAW");
  kitSamples[9][7] = loader.loadSample("DRUMS/ELEKTRON_CLEAN/TOM.RAW");

  kitSamples[10][0] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/KICK.RAW");
  kitSamples[10][1] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/SNARE.RAW");
  kitSamples[10][2] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/CHH.RAW");
  kitSamples[10][3] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/OHH.RAW");
  kitSamples[10][4] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/SNARE2.RAW");
  kitSamples[10][5] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/LOCLICK.RAW");
  kitSamples[10][6] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/CRUNCH.RAW");
  kitSamples[10][7] = loader.loadSample("DRUMS/ELEKTRON_CRUSH/CLANG.RAW");
//
//  kitSamples[11][0] = loader.loadSample("DRUMS/ELEKTRON_NOISY/SNARE.RAW");
//  kitSamples[11][1] = loader.loadSample("DRUMS/ELEKTRON_NOISY/SNARE.RAW");
//  kitSamples[11][2] = loader.loadSample("DRUMS/ELEKTRON_NOISY/CHH.RAW");
//  kitSamples[11][3] = loader.loadSample("DRUMS/ELEKTRON_NOISY/OHH.RAW");
//  kitSamples[11][4] = loader.loadSample("DRUMS/ELEKTRON_NOISY/SNARE2.RAW");
//  kitSamples[11][5] = loader.loadSample("DRUMS/ELEKTRON_NOISY/RATTLE.RAW");
//  kitSamples[11][6] = loader.loadSample("DRUMS/ELEKTRON_NOISY/MECH.RAW");
//  kitSamples[11][7] = loader.loadSample("DRUMS/ELEKTRON_NOISY/CLANG.RAW");

  sample9 = loader.loadSample("BREAKS/AMEN175.RAW");

  chordSamples[0][0] = loader.loadSample("SAMPLES/ORGAN/CMAJ.RAW");
  chordSamples[0][1] = loader.loadSample("SAMPLES/ORGAN/CMIN.RAW");
  chordSamples[0][2] = loader.loadSample("SAMPLES/ORGAN/C7.RAW");
  chordSamples[0][3] = loader.loadSample("SAMPLES/ORGAN/CMAJ7.RAW");
  chordSamples[0][4] = loader.loadSample("SAMPLES/ORGAN/CMIN7.RAW");
  chordSamples[0][5] = loader.loadSample("SAMPLES/ORGAN/CDIM.RAW");
  chordSamples[0][6] = loader.loadSample("SAMPLES/ORGAN/CAUG.RAW");

  chordSamples[1][0] = loader.loadSample("SAMPLES/ORGAN/CMAJ.RAW");
  chordSamples[1][1] = loader.loadSample("SAMPLES/ORGAN/CMIN.RAW");
  chordSamples[1][2] = loader.loadSample("SAMPLES/ORGAN/C7.RAW");
  chordSamples[1][3] = loader.loadSample("SAMPLES/ORGAN/CMAJ7.RAW");
  chordSamples[1][4] = loader.loadSample("SAMPLES/ORGAN/CMIN7.RAW");
  chordSamples[1][5] = loader.loadSample("SAMPLES/ORGAN/CDIM.RAW");
  chordSamples[1][6] = loader.loadSample("SAMPLES/ORGAN/CAUG.RAW");

  chordSamples[2][0] = loader.loadSample("SAMPLES/STRING/CMAJ.RAW");
  chordSamples[2][1] = loader.loadSample("SAMPLES/STRING/CMIN.RAW");
  chordSamples[2][2] = loader.loadSample("SAMPLES/STRING/C7.RAW");
  chordSamples[2][3] = loader.loadSample("SAMPLES/STRING/CMAJ7.RAW");
  chordSamples[2][4] = loader.loadSample("SAMPLES/STRING/CMIN7.RAW");
  chordSamples[2][5] = loader.loadSample("SAMPLES/STRING/CDIM.RAW");
  chordSamples[2][6] = loader.loadSample("SAMPLES/STRING/CAUG.RAW");

  organNotes[0] = loader.loadSample("SAMPLES/NOTES/STRING.RAW");
  organNotes[1] = loader.loadSample("SAMPLES/NOTES/BASS.RAW");
  organNotes[2] = loader.loadSample("SAMPLES/NOTES/BASSUPCLK.RAW");
  organNotes[3] = loader.loadSample("SAMPLES/NOTES/SINE.RAW");
  organNotes[4] = loader.loadSample("SAMPLES/NOTES/STRING.RAW");
  organNotes[5] = loader.loadSample("SAMPLES/NOTES/STRING.RAW");
  organNotes[6] = loader.loadSample("SAMPLES/NOTES/STRING.RAW");
  organNotes[7] = loader.loadSample("SAMPLES/NOTES/STRING.RAW");


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
  mixer5.gain(0, 1);   // playSdRaw5
  mixer5.gain(1, 1);   // playSdRaw6
  mixer5.gain(2, 1);   // playSdRaw7
  mixer5.gain(3, 1);   // playSdRaw8
  mixer6.gain(0, 1);   // playSdRaw5
  mixer6.gain(1, 1);   // playSdRaw6
  mixer6.gain(2, 1);   // playSdRaw7
  mixer6.gain(3, 1);   // playSdRaw8
  mixer7.gain(0, 1);   // playSdRaw5
  mixer7.gain(1, 1);   // playSdRaw6
  mixer7.gain(2, 1);   // playSdRaw7
  mixer7.gain(3, 1);   // playSdRaw8
  mixer8.gain(0, 1);   // playSdRaw5
  mixer8.gain(1, 1);   // playSdRaw6
  mixer8.gain(2, 1);   // playSdRaw7
  mixer8.gain(3, 1);   // playSdRaw8
  mixer9.gain(0, 1);   // playSdRaw5
  mixer9.gain(1, 1);   // playSdRaw6
  mixer9.gain(2, 1);   // playSdRaw7
  mixer9.gain(3, 1);   // playSdRaw8
  
  // granular setup
  granular1.begin(granularMemory1, GRANULAR_MEMORY_SIZE);
  //  granular1.beginPitchShift(50);

  granular2.begin(granularMemory2, GRANULAR_MEMORY_SIZE);
  granular2.beginPitchShift(50);
  granular3.begin(granularMemory3, GRANULAR_MEMORY_SIZE);
  granular3.beginPitchShift(50);
  granular4.begin(granularMemory4, GRANULAR_MEMORY_SIZE);
  granular4.beginPitchShift(50);
  granular5.begin(granularMemory5, GRANULAR_MEMORY_SIZE);
  granular5.beginPitchShift(50);

  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
  bitcrusher2.bits(16);
  bitcrusher2.sampleRate(44100);

  // initialize MUX address pins
  for (unsigned int i = 0; i < sizeof(muxAddressPins) / sizeof(muxAddressPins[0]); i++)
  {
    pinMode(muxAddressPins[i], OUTPUT);
  }

  // initialize MUX data pins
  for (unsigned int i = 0; i < sizeof(muxDataPins) / sizeof(muxDataPins[0]); i++)
  {
    pinMode(muxDataPins[i], INPUT);
  }

  changeTempo(tempo); // set the tempo

  // rotary encoder setup
  pinMode(tempoEncAPin, INPUT);
  pinMode(tempoEncBPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(tempoEncAPin), ISRtempoEncAChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(tempoEncBPin), ISRtempoEncBChange, CHANGE);

  pinMode(dataEncAPin, INPUT);
  pinMode(dataEncBPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(dataEncAPin), ISRdataEncAChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dataEncBPin), ISRdataEncBChange, CHANGE);

  currPattern = &PatternStorage[0][0];
  myCopiedPattern = currPattern;
  patternNum = 0;

  currSong = &SongStorage[0][0];

  writeShiftRegisters();

  currStepTime = millis();
  MIDI.begin();
  
}

void loop()
{
  if (millis() > lcdTimeout) // LCD framerate limiter
  {
    displayLCD(false);
    lcdTimeout = millis() + 200;
//    Serial.println(midi24ppqUs);
  }

  if(micros() > midiClockTimer){
//    Serial.println("Clock");
    midiClockTimer = midiClockTimer + midi24ppqUs;
    MIDI.sendRealTime(0xF8);
  }



//  mixer1.gain(0, 1);
//  mixer1.gain(1, 1);
//  mixer1.gain(2, 1);
//  mixer1.gain(3, 1);
//
//  mixer2.gain(0, 1);
//  mixer2.gain(1, 1);
//  mixer2.gain(2, 1);
//  mixer2.gain(3, 1);

//  mixer3.gain(0, 1);
//  mixer3.gain(1, 1);
//  mixer3.gain(2, 1);
//  mixer3.gain(3, 1);
  
  readMux(false); // read inputs and process them

  // steps
  if (transportState == PLAYING)
  {
    if (millis() > (currStepTime + stepLen)) // new step has been reached
    {
      recallParameters(); // update parameters for this step
      if (playMode == PLAY_PATTERN)
      {
        if (currStep == (int)currPattern->settings[2] - 1)
        {                                                                    // last step off pattern, time to move to the next one
          patternQueueIndex = (patternQueueIndex + 1) % patternQueueLen;     // step to the next pattern in sequence
          patternNum = patternQueue[patternQueueIndex];                      // store pattern number for reference
          currPattern = &PatternStorage[patternNum/16][patternNum%16]; // actually grab the pattern from memory
        }
        currStep = (currStep + 1) % (int)currPattern->settings[2]; // move step pointer to next step
      }
      else if (playMode == PLAY_SONG)
      {
        if (currStep == (int)currPattern->settings[2] - 1)
        {                 // last step off pattern, time to move to the next one
          songPlayStep++; // increment the song pattern index
          if (currSong->patterns[songPlayStep] == -1)
          {
            songPlayStep = 0;
          }
          patternNum = currSong->patterns[songPlayStep];
          currPattern = &PatternStorage[patternNum/16][patternNum%16]; // grab the next pattern from memory
          currStep = -1;
        }
        currStep = (currStep + 1) % (int)currPattern->settings[2]; // move step pointer to next step
      }
      
      endChords();

      for (int i = 0; i < 24; i++)
      { // send triggers of all instruments to be played at this step
        if (currStep != -1 && currPattern->pattern[i][currStep])
        {
          int myParam = 0;      // initialize myParam to zero for instruments that don't need it
                                //            if (i == 16 || i == 17 || i == 18 || i == 19 || i == 20){
                                //              myParam = currPattern->pattern[i][currStep]; // grab the parameter for chord/break sample voices
                                //            }
          trigNote(i, myParam); // trigger correct instrument and send the parameter
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
      if (currStep < 16)
      {
        patternPlaySection = 0;
      }
      else if (currStep > 15 && currStep < 32)
      {
        patternPlaySection = 1;
      }
      else if (currStep > 31 && currStep < 48)
      {
        patternPlaySection = 2;
      }
      else if (currStep > 47 && currStep < 64)
      {
        patternPlaySection = 3;
      }
    }
  }

  for (int i = 0; i < 16; i++) // check if hardware output pulses need to finish
  {
    if (outPulseTimes[i] != 0) // only check active pulses
    {
      if (millis() > outPulseTimes[i]) // check if the pulse should be done
      {
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
                                    //    float mySpeed = ((float)controlPots[7] / 1023.0) * 1.5 + 0.5;
                                    //    Serial.println(mySpeed);
                                    //    granular2.setSpeed(pow(2, 2/12));
    // check if any control buttons have been pressed

    int bitDepth = (int)map(controlPots[7], 0, 1023, 17, 1);
    if (bitDepth == 17)
    {
      bitDepth = 16;
    }

    int sampleRateVal = (int)map(controlPots[8], 0, 1023, 44100, 1000);
    if (sampleRateVal > 43900)
    {
      sampleRateVal = 44100;
    }

    //    Serial.print("bits: ");
    //    Serial.println(bitDepth);
    //
    //    Serial.print("samplerate: ");
    //    Serial.println(sampleRateVal);
    //    Serial.println();

    bitcrusher1.bits(bitDepth);
    bitcrusher2.bits(bitDepth);

    bitcrusher1.sampleRate(sampleRateVal);
    bitcrusher2.sampleRate(sampleRateVal);

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
            lcdState = LCD_INST_PROP;
          }
          else // inst sel RELEASED
          {
            if (controlState != KIT_SEL)
            {
              controlState = STEP_SEL;
              lcdState = LCD_INST_PROP;
            }
          }
          break;

        case 1: // save
          if (controlButtons[i] == LOW)
          { // save PRESSED
            // grab LED states and pack them into 8-bit numbers to be sent out the shift registers
            sr3LED[1] = 1;
            writeShiftRegisters();
            
            // load patterns from SD Card ::: NOTE THIS TAKES LIKE 10 SEC TO LOAD ALL BANKS
            for (int j = 0; j < NUM_BANKS; j++)
            { // limit on j determines how many banks to load
              for (int i = 0; i < 16; i++)
              {
                char myFullArr[25];
                sprintf(myFullArr, "/PATTERNS/%i/%i.CSV", j + 1, i + 1);
                PatternStorage[j][i].writePatternToSD((const char *)myFullArr);
                sprintf(myFullArr, "/SONGS/%i/%i.CSV", j + 1, i + 1);
                SongStorage[j][i].writeSongToSD(myFullArr);
              }
            }

            sr3LED[1] = 0;
            writeShiftRegisters();
          }
          else
          { // save RELEASED
          }
          break;

        case 2:                         // shift -----> now write
          if (controlButtons[i] == LOW) // shift->write PRESSED
          {
            //            patternWrite = !patternWrite;
            //            sr3LED[2] = patternWrite;
            if (controlState == SONG_SEL)
            { // entering song write mode from song sel mode
              controlState = SONG_WRITE;
              lcdState = LCD_SONG_WRITE;
            }
            else if (controlState == SONG_WRITE)
            {                                          // entering song store mode from song write mode
              currSong->patterns[songWriteIndex] = -1; // add stop point to song
              for (int i = songWriteIndex + 1; i < 65; i++)
              { // clear everything after the stop point
                currSong->patterns[i] = -1;
              }
              if (songWriteIndex == 0)
              {
                currSong->patterns[0] = 0;
                currSong->patterns[1] = -1;
              }
              songWriteIndex = 0;
              controlState = SONG_SEL;
              lcdState = LCD_SONG_SEL;
            } else if (controlState == PATTERN_SEL){
              controlState = PATTERN_WRITE;
              lcdState = LCD_PATTERN_WRITE;
            } else if (controlState == PATTERN_WRITE){
              controlState = PATTERN_SEL;
              lcdState = LCD_PATT_SEL;
            }
          }
          else
          { // shift->write RELEASED
          }
          break;

        case 3: // song
          if (controlButtons[i] == LOW)
          { // song PRESSED
            controlState = SONG_SEL;
            lcdState = LCD_SONG_SEL;
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
            lcdState = LCD_PATT_SEL;
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
              currPattern->settings[1] = kitSel; // place kit into pattern memory
              controlState = STEP_SEL;           // exit kit selection mode
              lcdState = LCD_INST_PROP;          // exit kit selection display
            }
            else if (controlButtons[5] == LOW)
            { // if pattern being held down, enter length selection mode
              controlState = LENGTH_SEL;
              lcdState = LCD_LENGTH_SEL;
            }
            else if (controlState == LENGTH_SEL)
            {
              controlState = STEP_SEL;
              lcdState = LCD_INST_PROP;
            } else if (controlState == PATTERN_WRITE){
              switch(pattWriteSel){
                case 0: // clear pattern
                   currPattern->clearPattern();
                  break;
                case 1: // copy pattern
                  myCopiedPattern = currPattern;
                  break;
                case 2: // paste pattern
                  for(int i = 0; i < 64; i++){ // loop through all steps
                    for(int j = 0; j < 24; j++){
                      currPattern->pattern[j][i] = myCopiedPattern->pattern[j][i];
                      currPattern->velocity[j][i] = myCopiedPattern->velocity[j][i];
                    }

                    for(int j = 0; j < 38; j++){
                      currPattern->parameter[j][i] = myCopiedPattern->parameter[j][i];
                    }

                    currPattern->settings[i] = myCopiedPattern->settings[i];
                  }
                  break;
              }
              controlState = PATTERN_SEL;
              lcdState = LCD_PATT_SEL;
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
            switch (controlState)
            {
            case PATTERN_SEL:
              prevControlState = controlState;
              prevLcdState = lcdState;
              controlState = PATTERN_BANK_SEL;
              lcdState = LCD_PATT_BANK;
              break;
            case SONG_WRITE:
              prevControlState = controlState;
              prevLcdState = lcdState;
              controlState = PATTERN_BANK_SEL;
              lcdState = LCD_PATT_BANK;
              break;
            case SONG_SEL:
              prevControlState = controlState;
              prevLcdState = lcdState;
              controlState = SONG_BANK_SEL;
              lcdState = LCD_SONG_BANK;
              break;
            case STEP_SEL:
              prevControlState = controlState;
              prevLcdState = lcdState;
              controlState = INST_BANK_SEL;
              lcdState = LCD_INST_BANK;
              break;
            }
          }
          else
          { // bank RELEASED
            if (controlState == PATTERN_BANK_SEL || controlState == SONG_BANK_SEL || controlState == INST_BANK_SEL)
            {
              controlState = prevControlState;
              lcdState = prevLcdState;
            }
          }
          break;

        case 9: // step
          if (controlButtons[i] == LOW)
          { // step PRESSED
            controlState = STEP_SEL;
            lcdState = LCD_INST_PROP;
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
            prevState = controlState;
            controlState = PLAY_STEP_SEL;
          }
          else
          { // playpause RELEASED
            controlState = prevState;
            if (transportState == PLAYING)
            {
              transportState = PAUSED;
              MIDI.sendRealTime(0xFC); // midi start message
              sr1LED[1] = 0;
//              Serial.println("Paused!");
              stopSamples(); // force stop playing all samples
              midiClockTimer = micros();
            }
            else
            {
              transportState = PLAYING;
              MIDI.sendRealTime(0xFA); // midi stop message
              sr1LED[2] = 0;
              sr1LED[1] = 1;
              currStepTime = millis();
//              Serial.println("Playing!");
            }
          }

          break;

        case 13: // stop
          if (controlButtons[i] == LOW)
          { // stop PRESSED
            // set play and stop LEDs
            MIDI.sendRealTime(0xFC); // midi stop message
            sr1LED[2] = 1;
            sr1LED[1] = 0;
            songPlayStep = 0;
            transportState = STOPPED;

            

            if (playMode == PLAY_PATTERN)
            {
              patternQueueIndex = 0; // jump back to start of song
              currPattern = &PatternStorage[patternQueue[patternQueueIndex] / 16][patternQueue[patternQueueIndex] % 16];
              patternNum = patternQueue[patternQueueIndex];
            }
            else if (playMode == PLAY_SONG)
            {
                songPlayStep = 0;
                currPattern = &PatternStorage[currSong->patterns[0] / 16][currSong->patterns[0] % 16];
            }
            stopSamples(); // force stop playing all samples
//            Serial.println("Stopped!");
            currStep = -1; // jump back to start of pattern
          }
          else
          { // stop RELEASED
          }

          break;

        case 14: // forwards
          if (controlButtons[i] == LOW)
          { // forwards PRESSED
            if (transportState != PLAYING)
            {
              if (++patternPlaySection > 3)
              {
                patternPlaySection = 3;
              }
            }
          }
          else
          { // forwards RELEASED
          }
          break;

        case 15: // backwards
          if (controlButtons[i] == LOW)
          { // backwards PRESSED
            if (transportState != PLAYING)
            {
              if (--patternPlaySection < 0)
                patternPlaySection = 0;
            }
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
          // THIS CURRENTLY CAUSES ERRORS BECAUSE THERE ARE MORE BANKS/INST INDICES THAN THERE ARE INSTRUMENTS IN PATTERN OBJECT
          // THIS RESULTS IN AN OUT OF BOUNDS ERROR IF YOU TRY TO ACCESS ANY INSTRUMENT GREATER THAN I THINK 20 OR 21
//          int myInd = getButtonOffset(i, patternPlaySection);
          int myInd = i + 16 * patternPlaySection;
          currPattern->pattern[currInst][myInd] = !currPattern->pattern[currInst][myInd]; // record buttom press into current pattern array
          stepEditIndex = myInd;
          int ofs = 0;
          for (int i = 16; i < 24; i++){
             if(currPattern->pattern[currInst][myInd] > 0){
              int prevStep = myInd - 1;
              if (prevStep == -1)
              {
                prevStep = currPattern->settings[2] - 1; // if first step, grab from last step
              }
              if (currPattern->pattern[currInst][prevStep] > 0)
              { // retrieve it
                currPattern->pattern[currInst][myInd] = currPattern->pattern[currInst][prevStep];
                currPattern->parameter[currInst + 6 + ofs][myInd] = currPattern->parameter[currInst + 6 + ofs][prevStep];
                currPattern->parameter[currInst + 7 + ofs][myInd] = currPattern->parameter[currInst + 7 + ofs][prevStep];
              }
             }
             ofs += 1;
          }
        }
      }
      break;

    case INST_SEL:                 // mode for selecting current instrument
      for (int i = 0; i < 16; i++) // loop through all 16 instrument buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          currInst = i + 16 * instBankNum; // set current instrument to the one that was pressed offsetting by 16 for each bank
//          controlState = STEP_SEL;
//          lcdState = LCD_INST_PROP;                                                                                                                                                                                                                                                                                                                          
        }
      }
      break;

    case PATTERN_SEL: // mode for selecting pattern
      for (int i = 0; i < 16; i++)
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          playMode = PLAY_PATTERN;
          if (transportState == PLAYING) // if playing, we wait for current pattern to end before switching over
          {
            patternQueue[0] = i + 16 * pattBankNum; // set pressed pattern to index 0
            patternQueueLen = 1; // set length of queue to 2
          }
          else // if not playing we can jump to new pattern immediately
          {
            patternQueueIndex = 0;
            patternQueueLen = 1;                 // set length of queue to 2
            patternNum = i + 16 * pattBankNum;                      // set pattern num to the one you pressed
            patternQueue[0] = patternNum;                 // put pattern num at the first place in queue
            
            currPattern = &PatternStorage[patternNum/16][i%16]; // grab the new pattern from memory
          }
        }
      }
      break;
    case SONG_SEL:
      // INSERT CODE HERE FOR SELECTING SONGS
      for (int i = 0; i < 16; i++)
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          int mySongIndex = i + songBankNum * 16;
          currSong = &SongStorage[mySongIndex / 16][mySongIndex % 16];
          playMode = PLAY_SONG;
          currStep = -1;
          if (currSong->patterns[0] == -1) //if song is empty just grab pattern 0
          {
            currPattern = &PatternStorage[0][0];
          }
          else
          {
            currPattern = &PatternStorage[currSong->patterns[0] / 16][currSong->patterns[0] % 16];
          }
          songNum = mySongIndex;
        }
      }

      break;
    case SONG_WRITE:
      for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          int myPatternIndex = i + 16 * pattBankNum;
          currSong->patterns[songWriteIndex] = myPatternIndex;
          songWriteIndex++;
          if (songWriteIndex > 63)
          {
            // pattern is full!!!! do something about it
            currSong->patterns[64] = -1;
            lcdState = LCD_SONG_SEL;
            controlState = SONG_SEL;
          }
        }
      }
      break;
    case INST_BANK_SEL:
      for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          instBankNum = i;
        }
      }
      break;
    case SONG_BANK_SEL:
      for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          songBankNum = i;
        }
      }
      break;
    case PATTERN_BANK_SEL:
      for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
          pattBankNum = i;
        }
      }
      break;
    case PLAY_STEP_SEL:
      for (int i = 0; i < 16; i++) // loop through all 16 pattern buttons
      {
        if (stepButtons[i] != stepButtonsPrev[i] && !stepButtons[i]) // if button state changed and is pressed down
        {
            currStep = i + 16 * patternPlaySection - 1;
        }
      }
    }

    drum1.frequency(map(controlPots[0], 1023, 0, 60, 700)); // set drum 1 freq from param pot
    drum2.frequency(map(controlPots[2], 1023, 0, 60, 700)); // set drum 2 freq from param pot
    drum3.frequency(map(controlPots[4], 1023, 0, 60, 700)); // set drum 3 freq from param pot
    mixer4.gain(0, (1023 - controlPots[1]) / 1023);         // set drum 1 gain from param pot
    mixer4.gain(1, (1023 - controlPots[3]) / 1023);         // set drum 2 gain from param pot
    mixer4.gain(2, (1023 - controlPots[5]) / 1023);         // set drum 3 gain from param pot

  }
  writeShiftRegisters();

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
//  float eigthLen = quarterLen / 2;           // subdivide to eighth notes
  float sixteenthLen = quarterLen / 4;       // subdivide to sixteenth notes
  midi24ppqMs = quarterLen / 24.0;// subdivide to 24ppq
  midi24ppqUs = midi24ppqMs * 1000;
  
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
//    MIDI.sendNoteOn(50, 100, 1);
//    Serial.println("kick triggered");
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
    playSdRaw1.playRaw(kitSamples[(int)currPattern->settings[1]][0]->sampledata, kitSamples[(int)currPattern->settings[1]][0]->samplesize / 2, 1);
    break;

  case INST_SMP2: // casio snare
    pulseLen = playSdRaw2.lengthMillis() * (currPattern->parameter[9][0] / 100.0) / currPattern->parameter[8][0];
    playSdRaw2.playRaw(kitSamples[(int)currPattern->settings[1]][1]->sampledata, kitSamples[(int)currPattern->settings[1]][1]->samplesize / 2, 1);
    break;

  case INST_SMP3: // casio closed hat
    pulseLen = playSdRaw3.lengthMillis() * (currPattern->parameter[11][0] / 100.0) / currPattern->parameter[10][0];
    playSdRaw3.playRaw(kitSamples[(int)currPattern->settings[1]][2]->sampledata, kitSamples[(int)currPattern->settings[1]][2]->samplesize / 2, 1);
    break;

  case INST_SMP4: // casio open hat
    pulseLen = playSdRaw4.lengthMillis() * (currPattern->parameter[13][0] / 100.0) / currPattern->parameter[12][0];
    playSdRaw4.playRaw(kitSamples[(int)currPattern->settings[1]][3]->sampledata, kitSamples[(int)currPattern->settings[1]][3]->samplesize / 2, 1);
    break;

  case INST_SMP5: // casio cowbell hi
    pulseLen = playSdRaw5.lengthMillis() * (currPattern->parameter[15][0] / 100.0) / currPattern->parameter[14][0];
    playSdRaw5.playRaw(kitSamples[(int)currPattern->settings[1]][4]->sampledata, kitSamples[(int)currPattern->settings[1]][4]->samplesize / 2, 1);
    break;

  case INST_SMP6: // casio cowbell lo
    pulseLen = playSdRaw6.lengthMillis() * (currPattern->parameter[17][0] / 100.0) / currPattern->parameter[16][0];
    playSdRaw6.playRaw(kitSamples[(int)currPattern->settings[1]][5]->sampledata, kitSamples[(int)currPattern->settings[1]][5]->samplesize / 2, 1);
    break;

  case INST_SMP7: // casio hi tom
    pulseLen = playSdRaw7.lengthMillis() * (currPattern->parameter[19][0] / 100.0) / currPattern->parameter[18][0];
    playSdRaw7.playRaw(kitSamples[(int)currPattern->settings[1]][6]->sampledata, kitSamples[(int)currPattern->settings[1]][6]->samplesize / 2, 1);
    break;

  case INST_SMP8: // casio lo tom
    pulseLen = playSdRaw8.lengthMillis() * (currPattern->parameter[21][0] / 100.0) / currPattern->parameter[20][0];
    playSdRaw8.playRaw(kitSamples[(int)currPattern->settings[1]][7]->sampledata, kitSamples[(int)currPattern->settings[1]][7]->samplesize / 2, 1);
    break;
                
  case INST_ORGAN_CHORDS:
    if (currStep >= 0)
    {
      mixer6.gain(0, currPattern->velocity[16][0]);
      playSdRaw10.playRaw(chordSamples[0][(int)currPattern->parameter[22][currStep]]->sampledata, chordSamples[0][(int)currPattern->parameter[22][currStep]]->samplesize / 2, 1);
      float mySpeed = pow(2, (currPattern->pattern[16][currStep] - 1) / 12.0);
      granular2.setSpeed(mySpeed);
    }
    break;

  case INST_GUITAR_CHORDS:
    if (currStep >= 0)
    {
      mixer6.gain(1, currPattern->velocity[17][0]);
      playSdRaw11.playRaw(chordSamples[1][(int)currPattern->parameter[24][currStep]]->sampledata, chordSamples[1][(int)currPattern->parameter[24][currStep]]->samplesize / 2, 1);
      float mySpeed = pow(2, (currPattern->pattern[17][currStep] - 1) / 12.0);
      granular3.setSpeed(mySpeed);
    }
    break;

  case INST_GUITAR_ONE:
    if (currStep >= 0)
    {
      mixer6.gain(2, currPattern->velocity[18][0]);
      playSdRaw12.playRaw(chordSamples[2][(int)currPattern->parameter[26][currStep]]->sampledata, chordSamples[2][(int)currPattern->parameter[26][currStep]]->samplesize / 2, 1);
      float mySpeed = pow(2, (currPattern->pattern[18][currStep] - 1) / 12.0);
      granular4.setSpeed(mySpeed);
    }
    break;

  case INST_ORGAN_NOTES:
    if (currStep >= 0)
    {
      mixer7.gain(0, currPattern->velocity[19][0]);
      float mySpeed = pow(2, (currPattern->pattern[19][currStep] - 1) / 12.0);
      float myOct = currPattern->parameter[28][currStep];
      if (myOct > 0)
      {
        mySpeed = mySpeed * (2 * myOct);
      }
      else if (myOct < 0)
      {
        mySpeed = mySpeed * (0.5 * (1 / (-1 * myOct)));
      }
      playSdRaw14.setPlaybackRate(mySpeed);
      playSdRaw14.playRaw(organNotes[0]->sampledata, organNotes[0]->samplesize / 2, 1);
    }
    break;

  case INST_ORGAN_NOTES_2:
    if (currStep >= 0)
    {
      mixer7.gain(1, currPattern->velocity[20][0]);
      float mySpeed = pow(2, (currPattern->pattern[20][currStep] - 1) / 12.0);
      float myOct = currPattern->parameter[30][currStep];
      if (myOct > 0)
      {
        mySpeed = mySpeed * (2 * myOct);
      }
      else if (myOct < 0)
      {
        mySpeed = mySpeed * (0.5 * (1 / (-1 * myOct)));
      }
      playSdRaw15.setPlaybackRate(mySpeed);
      playSdRaw15.playRaw(organNotes[1]->sampledata, organNotes[1]->samplesize / 2, 1);
    }
    break;

  case INST_ORGAN_NOTES_3:
    if (currStep >= 0)
    {
      mixer7.gain(2, currPattern->velocity[21][0]);
      float mySpeed = pow(2, (currPattern->pattern[21][currStep] - 1) / 12.0);
      float myOct = currPattern->parameter[32][currStep];
      if (myOct > 0)
      {
        mySpeed = mySpeed * (2 * myOct);
      }
      else if (myOct < 0)
      {
        mySpeed = mySpeed * (0.5 * (1 / (-1 * myOct)));
      }
      playSdRaw16.setPlaybackRate(mySpeed);
      playSdRaw16.playRaw(organNotes[2]->sampledata, organNotes[2]->samplesize / 2, 1);
    }
    break;

  case INST_ORGAN_NOTES_4:
    if (currStep >= 0)
    {
      mixer7.gain(3, currPattern->velocity[22][0]);
      float mySpeed = pow(2, (currPattern->pattern[22][currStep] - 1) / 12.0);
      float myOct = currPattern->parameter[34][currStep];
      if (myOct > 0)
      {
        mySpeed = mySpeed * (2 * myOct);
      }
      else if (myOct < 0)
      {
        mySpeed = mySpeed * (0.5 * (1 / (-1 * myOct)));
      }
      playSdRaw17.setPlaybackRate(mySpeed);
      playSdRaw17.playRaw(organNotes[3]->sampledata, organNotes[3]->samplesize / 2, 1);
    }
    break;

  case INST_ORGAN_NOTES_5:
    if (currStep >= 0)
    {
      mixer8.gain(0, currPattern->velocity[23][0]);
      float mySpeed = pow(2, (currPattern->pattern[23][currStep] - 1) / 12.0);
      float myOct = currPattern->parameter[36][currStep];
      if (myOct > 0)
      {
        mySpeed = mySpeed * (2 * myOct);
      }
      else if (myOct < 0)
      {
        mySpeed = mySpeed * (0.5 * (1 / (-1 * myOct)));
      }
      playSdRaw18.setPlaybackRate(mySpeed * -1);
      playSdRaw18.playRaw(organNotes[4]->sampledata, organNotes[4]->samplesize / 2, 1);
    }
    break;
  }
  if (instNum < 16)
  {
    outPulseTimes[instNum] = millis() + pulseLen; // send the pulse end time to or pulse timer array
  }
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
  //  Serial.print("PATTERN STEP: ");
  //  Serial.print(currStep); // prints current pattern number
  //  Serial.print("   ");
  //
  //  for (int i = 0; i < 16; i++)
  //  {
  //    Serial.print(currPattern->pattern[i][currStep]); // prints which instruments are played on this step
  //  }
  //  Serial.println(" ");
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
  case LCD_INST_PROP: // mode for displaying paramter of selected instrument, and allows you to edit them
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      char* paramStr = (char*)calloc(sizeof(char) * CHAR_BUFF_SIZE, sizeof(char));
      char* volStr = (char*)calloc(sizeof(char) * CHAR_BUFF_SIZE, sizeof(char));
      char* envStr = (char*)calloc(sizeof(char) * CHAR_BUFF_SIZE, sizeof(char));
      char stepNumStr[CHAR_BUFF_SIZE]; // display num of curr edit step
      int32_t myRootNote;
      switch (currInst)    // set name string and parameters, these are unique to each instrument so i have this dumb huge switch statement :~(
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
        u8g2.drawStr(0, 11, kitNames[kitSel][0]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[6][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[8][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[7][0]);
        paramStr = _float_to_char(currPattern->parameter[6][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[8][0], volStr);
        break;
      case INST_SMP2:
        u8g2.drawStr(0, 11, kitNames[kitSel][1]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[8][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[9][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[9][0]);
        paramStr = _float_to_char(currPattern->parameter[8][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[9][0], volStr);
        break;
      case INST_SMP3:
        u8g2.drawStr(0, 11, kitNames[kitSel][2]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[10][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[10][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[11][0]);
        paramStr = _float_to_char(currPattern->parameter[10][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[10][0], volStr);
        break;
      case INST_SMP4:
        u8g2.drawStr(0, 11, kitNames[kitSel][3]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[12][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[11][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[13][0]);
        paramStr = _float_to_char(currPattern->parameter[12][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[11][0], volStr);
        break;
      case INST_SMP5:
        u8g2.drawStr(0, 11, kitNames[kitSel][4]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[14][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[12][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[15][0]);
        paramStr = _float_to_char(currPattern->parameter[14][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[12][0], volStr);
        break;
      case INST_SMP6:
        u8g2.drawStr(0, 11, kitNames[kitSel][5]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[16][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[13][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[17][0]);
        paramStr = _float_to_char(currPattern->parameter[16][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[13][0], volStr);
        break;
      case INST_SMP7:
        u8g2.drawStr(0, 11, kitNames[kitSel][6]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[18][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[14][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[19][0]);
        paramStr = _float_to_char(currPattern->parameter[18][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[14][0], volStr);
        break;
      case INST_SMP8:
        u8g2.drawStr(0, 11, kitNames[kitSel][7]);
//        sprintf(paramStr, "%.02f", currPattern->parameter[20][0]); // grab parameters from pattern object
//        sprintf(volStr, "%.02f", currPattern->velocity[15][0]);
        sprintf(envStr, "%i", (int)currPattern->parameter[21][0]);
        paramStr = _float_to_char(currPattern->parameter[20][0], paramStr);
        volStr = _float_to_char(currPattern->velocity[15][0], volStr);
        break;
      case INST_ORGAN_CHORDS:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ chords");
        myRootNote = currPattern->pattern[16][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "chord:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[16][0]);
        volStr = _float_to_char(currPattern->velocity[16][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          float myChordQual = currPattern->parameter[22][stepEditIndex];
          u8g2.drawStr(40, 34, chordQual[(int)myChordQual]);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_GUITAR_CHORDS:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Guitar chords");
        myRootNote = currPattern->pattern[17][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "chord:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[17][0]);
        volStr = _float_to_char(currPattern->velocity[17][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          float myChordQual = currPattern->parameter[24][stepEditIndex];
          u8g2.drawStr(40, 34, chordQual[(int)myChordQual]);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_GUITAR_ONE:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Guitar oneshots");
        myRootNote = currPattern->pattern[18][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "chord:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[18][0]);
        volStr = _float_to_char(currPattern->velocity[18][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          float myChordQual = currPattern->parameter[26][stepEditIndex];
          u8g2.drawStr(40, 34, chordQual[(int)myChordQual]);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_ORGAN_NOTES:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ notes");
        myRootNote = currPattern->pattern[19][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "oct:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[19][0]);
        volStr = _float_to_char(currPattern->velocity[19][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          int myChordQual = (int)currPattern->parameter[28][stepEditIndex];
          sprintf(paramStr, "%i", myChordQual);

          u8g2.drawStr(40, 34, paramStr);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_ORGAN_NOTES_2:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ notes 2");
        myRootNote = currPattern->pattern[20][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "oct:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[20][0]);
        volStr = _float_to_char(currPattern->velocity[20][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          int myChordQual = (int)currPattern->parameter[30][stepEditIndex];
          sprintf(paramStr, "%i", myChordQual);

          u8g2.drawStr(40, 34, paramStr);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_ORGAN_NOTES_3:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ notes 3");
        myRootNote = currPattern->pattern[21][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "oct:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[21][0]);
        volStr = _float_to_char(currPattern->velocity[21][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          int myChordQual = (int)currPattern->parameter[32][stepEditIndex];
          sprintf(paramStr, "%i", myChordQual);

          u8g2.drawStr(40, 34, paramStr);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_ORGAN_NOTES_4:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ notes 4");
        myRootNote = currPattern->pattern[22][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "oct:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[22][0]);
        volStr = _float_to_char(currPattern->velocity[22][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          int myChordQual = (int)currPattern->parameter[34][stepEditIndex];
          sprintf(paramStr, "%i", myChordQual);

          u8g2.drawStr(40, 34, paramStr);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;

      case INST_ORGAN_NOTES_5:
        if (stepEditIndex < 0 || stepEditIndex > 63)
        {
          stepEditIndex = 0;
        }
        u8g2.drawStr(0, 11, "Organ notes 5");
        myRootNote = currPattern->pattern[23][stepEditIndex];
        u8g2.drawStr(0, 24, "root:");
        u8g2.drawStr(0, 34, "oct:");
        u8g2.drawStr(0, 44, "vol: ");
//        sprintf(volStr, "%.02f", currPattern->velocity[23][0]);
        volStr = _float_to_char(currPattern->velocity[23][0], volStr);
        u8g2.drawStr(30, 44, volStr);
        if (myRootNote > 0)
        {
          u8g2.drawStr(40, 24, rootNotes[myRootNote - 1]);
          int myChordQual = (int)currPattern->parameter[36][stepEditIndex];
          sprintf(paramStr, "%i", myChordQual);

          u8g2.drawStr(40, 34, paramStr);
        }
        else
        {
          u8g2.drawStr(40, 24, "N.C.");
        }
        sprintf(stepNumStr, "%i", stepEditIndex);
        u8g2.drawStr(70, 35, stepNumStr);
        break;
      }

  
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      char instNumStr[30]; // display num of curr inst
      sprintf(instNumStr, "%i", currInst);
      u8g2.drawStr(70, 45, instNumStr);
      if (currInst >= 8 && currInst < 16) // draw all the parameter stuff on the screen for instruments that need them
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
      if (currInst > 15 && currInst < 24)
      { // organ and guitar chords
        u8g2.setDrawColor(2);
        if (paramSel) // draw a selection box
        {
          switch (cursorLoc)
          {
          case 0:
            u8g2.drawBox(40, 15 + 10 * cursorLoc, 36, 11); // selection box on parameter being edited
            break;
          case 1:
            u8g2.drawBox(40, 15 + 10 * cursorLoc, 26, 11); // selection box on parameter being edited
            break;
          case 2:
            u8g2.drawBox(30, 15 + 10 * cursorLoc, 36, 11); // selection box on parameter being edited
            break;
          }
          //          if(cursorLoc == 2){
          //            u8g2.drawBox(30, 15 + 10 * cursorLoc, 36, 11); // selection box on parameter being edited
          //          } else if (cursorLoc == 1) {
          //            u8g2.drawBox(40, 15 + 10 * cursorLoc, 26, 11); // selection box on parameter being edited
          //          } else {
          //            u8g2.drawBox(40, 15 + 10 * cursorLoc, 36, 11); // selection box on parameter being edited
          //          }
        }
        else
        {
          if (cursorLoc != 2)
          {
            u8g2.drawBox(0, 15 + 10 * cursorLoc, 36, 11); // selection box on menu for navigation
          }
          else
          {
            u8g2.drawBox(0, 15 + 10 * cursorLoc, 26, 11); // selection box on menu for navigation
          }
        }
      }
      u8g2.sendBuffer();        // transfer internal memory to the display
      free(paramStr);
      free(envStr);
      free(volStr);
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
      sprintf(tempoStr, "%i", (int)tempo);
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
      if(kitSel == 0 || kitSel == 1 || kitSel == 2){
        u8g2.drawStr(0, 14, "Casio SK-1"); // draw kit names
        u8g2.drawStr(0, 24, "808");
        u8g2.drawStr(0, 34, "Happy Hxc");
      } else if (kitSel == 3 || kitSel == 4 || kitSel == 5){
        u8g2.drawStr(0, 14, "AKAI AMB"); // draw kit names
        u8g2.drawStr(0, 24, "AKAI BDRM");
        u8g2.drawStr(0, 34, "AKAI GARAGE");
      } else if (kitSel == 6 || kitSel == 7 || kitSel == 8){
        u8g2.drawStr(0, 14, "EMU MP CLEAR"); // draw kit names
        u8g2.drawStr(0, 24, "EMU MP DARK");
        u8g2.drawStr(0, 34, "ALESIS HR16");
      } else if (kitSel == 9 || kitSel == 10 || kitSel == 11){
        u8g2.drawStr(0, 14, "ELEK CLEAN"); // draw kit names
        u8g2.drawStr(0, 24, "ELEK CRUSH");
//        u8g2.drawStr(0, 34, "ELEK NOISY");
      }

      u8g2.setDrawColor(2);
      u8g2.drawBox(0, 5 + 10 * (kitSel%3), 80, 11); // draw selection box
      u8g2.sendBuffer();
      LCDFrameTimer = millis();
    }
    break;
  case LCD_SONG_WRITE:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Writing pattern"); // draw kit names
      char songLenStr[30];
      sprintf(songLenStr, "%i", songWriteIndex);
      u8g2.drawStr(30, 34, songLenStr);
      u8g2.sendBuffer();
    }
    break;
  case LCD_SONG_SEL:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      if (playMode == PLAY_SONG)
      {
        u8g2.drawStr(0, 14, "Song number");
        char songNumStr[30];
        sprintf(songNumStr, "%i", songNum + 1);
        u8g2.drawStr(30, 34, songNumStr);
      }
      else
      {
        u8g2.drawStr(0, 14, "Select a song <3");
      }

      u8g2.sendBuffer();
    }
    break;
  case LCD_PATT_SEL:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Pattern number"); // draw kit names
      char pattNumStr[30];
      sprintf(pattNumStr, "%i", patternNum + 1);
      u8g2.drawStr(30, 34, pattNumStr);
      u8g2.sendBuffer();
    }
    break;
  case LCD_PATT_BANK:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Pattern bank sel"); // draw kit names
      char pattBankStr[30];
      sprintf(pattBankStr, "%i", pattBankNum + 1);
      u8g2.drawStr(30, 34, pattBankStr);
      u8g2.sendBuffer();
    }
    break;
  case LCD_INST_BANK:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Inst bank sel"); // draw kit names
      char instBankStr[30];
      sprintf(instBankStr, "%i", instBankNum + 1);
      u8g2.drawStr(30, 34, instBankStr);
      u8g2.sendBuffer();
    }
    break;
  case LCD_SONG_BANK:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Song bank sel");
      char songBankStr[30];
      sprintf(songBankStr, "%i", songBankNum + 1);
      u8g2.drawStr(30, 34, songBankStr);
      u8g2.sendBuffer();
    }
    break;

  case LCD_LENGTH_SEL:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Pattern Length");
      char patLenStr[30];
      sprintf(patLenStr, "%i", (int)currPattern->settings[2]);
      u8g2.drawStr(30, 34, patLenStr);
      int myPattLen = (int)currPattern->settings[2];
      int i = 0;
      while (myPattLen > 0)
      {
        for (int j = 0; j < 16; j++)
        {
          u8g2.drawPixel(20 + j * 2, 40 + i * 2);
          myPattLen--;
          if (myPattLen < 1)
          {
            break;
          }
        }
        i++;
      }
      u8g2.sendBuffer();
    }
    break;

  case LCD_PATTERN_WRITE:
    if (millis() > LCDFrameTimer + 10)
    {
      u8g2.clearBuffer();                 // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFontMode(0);
      u8g2.setDrawColor(1);
      u8g2.drawStr(0, 14, "Clear Patt?");
      u8g2.drawStr(0, 24, "Copy");
      u8g2.drawStr(0, 34, "Paste");
      u8g2.setDrawColor(2);
      u8g2.drawBox(0, 6 + 10 * (pattWriteSel%3), 80, 10); // draw selection box
      u8g2.sendBuffer();
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
          kitSel = (kitSel + 1);
          if (kitSel > NUM_KITS - 1)
            kitSel = NUM_KITS - 1;
        } else if( controlState == PATTERN_WRITE){
          pattWriteSel += 1;
          if (pattWriteSel > 2){
            pattWriteSel = 2;
          }
        }
        else if (controlState == LENGTH_SEL)
        {
          currPattern->settings[2] = currPattern->settings[2] + 1;
          if (currPattern->settings[2] > 64)
          {
            currPattern->settings[2] = 64;
          }
        }
        else // SHOULD MAKE THIS MORE ROBUST WITH A SWITCH STATEMENT. We assume we're in parameter selection mode if not in KIT_SEL
        {
          if (currInst > 7 && currInst < 24)
          {               // bank A sample kit
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
                case INST_ORGAN_CHORDS:
                  currPattern->pattern[16][stepEditIndex] = currPattern->pattern[16][stepEditIndex] + 1;
                  if (currPattern->pattern[16][stepEditIndex] > 12)
                    currPattern->pattern[16][stepEditIndex] = 1;
                  break;
                case INST_GUITAR_CHORDS:
                  currPattern->pattern[17][stepEditIndex] = currPattern->pattern[17][stepEditIndex] + 1;
                  if (currPattern->pattern[17][stepEditIndex] > 12)
                    currPattern->pattern[17][stepEditIndex] = 1;
                  break;
                case INST_GUITAR_ONE:
                  currPattern->pattern[18][stepEditIndex] = currPattern->pattern[18][stepEditIndex] + 1;
                  if (currPattern->pattern[18][stepEditIndex] > 12)
                    currPattern->pattern[18][stepEditIndex] = 1;
                  break;
                case INST_ORGAN_NOTES:
                  currPattern->pattern[19][stepEditIndex] = currPattern->pattern[19][stepEditIndex] + 1;
                  if (currPattern->pattern[19][stepEditIndex] > 12)
                    currPattern->pattern[19][stepEditIndex] = 1;
                  break;
                case INST_ORGAN_NOTES_2:
                  currPattern->pattern[20][stepEditIndex] = currPattern->pattern[20][stepEditIndex] + 1;
                  if (currPattern->pattern[20][stepEditIndex] > 12)
                    currPattern->pattern[20][stepEditIndex] = 1;
                  break;
                case INST_ORGAN_NOTES_3:
                  currPattern->pattern[21][stepEditIndex] = currPattern->pattern[21][stepEditIndex] + 1;
                  if (currPattern->pattern[21][stepEditIndex] > 12)
                    currPattern->pattern[21][stepEditIndex] = 1;
                  break;
                case INST_ORGAN_NOTES_4:
                  currPattern->pattern[22][stepEditIndex] = currPattern->pattern[22][stepEditIndex] + 1;
                  if (currPattern->pattern[22][stepEditIndex] > 12)
                    currPattern->pattern[22][stepEditIndex] = 1;
                  break;
                case INST_ORGAN_NOTES_5:
                  currPattern->pattern[23][stepEditIndex] = currPattern->pattern[23][stepEditIndex] + 1;
                  if (currPattern->pattern[23][stepEditIndex] > 12)
                    currPattern->pattern[23][stepEditIndex] = 1;
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
                case INST_ORGAN_CHORDS:
                  currPattern->parameter[22][stepEditIndex] = currPattern->parameter[22][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[22][stepEditIndex] > 6)
                  { // cycle back to beginning of list
                    currPattern->parameter[22][stepEditIndex] = 0;
                  }
                  break;
                case INST_GUITAR_CHORDS:
                  currPattern->parameter[24][stepEditIndex] = currPattern->parameter[24][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[24][stepEditIndex] > 6)
                  { // cycle back to beginning of list
                    currPattern->parameter[24][stepEditIndex] = 0;
                  }
                  break;
                case INST_GUITAR_ONE:
                  currPattern->parameter[26][stepEditIndex] = currPattern->parameter[26][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[26][stepEditIndex] > 6)
                  { // cycle back to beginning of list
                    currPattern->parameter[26][stepEditIndex] = 0;
                  }
                  break;
                case INST_ORGAN_NOTES:
                  currPattern->parameter[28][stepEditIndex] = currPattern->parameter[28][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[28][stepEditIndex] > 3)
                  { // cycle back to beginning of list
                    currPattern->parameter[28][stepEditIndex] = 3;
                  }
                  break;
                case INST_ORGAN_NOTES_2:
                  currPattern->parameter[30][stepEditIndex] = currPattern->parameter[30][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[30][stepEditIndex] > 3)
                  { // cycle back to beginning of list
                    currPattern->parameter[30][stepEditIndex] = 3;
                  }
                  break;
                case INST_ORGAN_NOTES_3:
                  currPattern->parameter[32][stepEditIndex] = currPattern->parameter[32][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[32][stepEditIndex] > 3)
                  { // cycle back to beginning of list
                    currPattern->parameter[32][stepEditIndex] = 3;
                  }
                  break;
                case INST_ORGAN_NOTES_4:
                  currPattern->parameter[34][stepEditIndex] = currPattern->parameter[34][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[34][stepEditIndex] > 3)
                  { // cycle back to beginning of list
                    currPattern->parameter[34][stepEditIndex] = 3;
                  }
                  break;
                case INST_ORGAN_NOTES_5:
                  currPattern->parameter[36][stepEditIndex] = currPattern->parameter[36][stepEditIndex] + 1; // increment chord type
                  if (currPattern->parameter[36][stepEditIndex] > 3)
                  { // cycle back to beginning of list
                    currPattern->parameter[36][stepEditIndex] = 3;
                  }
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
                case INST_ORGAN_CHORDS:
                  currPattern->velocity[16][0] += parameterInc;
                  mixer6.gain(0, currPattern->velocity[16][0]);
                  break;
                case INST_GUITAR_CHORDS:
                  currPattern->velocity[17][0] += parameterInc;
                  mixer6.gain(1, currPattern->velocity[17][0]);
                  break;
                case INST_GUITAR_ONE:
                  currPattern->velocity[18][0] += parameterInc;
                  mixer6.gain(2, currPattern->velocity[18][0]);
                  break;
                case INST_ORGAN_NOTES:
                  currPattern->velocity[19][0] += parameterInc;
                  mixer7.gain(0, currPattern->velocity[19][0]);
                  break;
                case INST_ORGAN_NOTES_2:
                  currPattern->velocity[20][0] += parameterInc;
                  mixer7.gain(1, currPattern->velocity[20][0]);
                  break;
                case INST_ORGAN_NOTES_3:
                  currPattern->velocity[21][0] += parameterInc;
                  mixer7.gain(2, currPattern->velocity[21][0]);
                  break;
                case INST_ORGAN_NOTES_4:
                  currPattern->velocity[22][0] += parameterInc;
                  mixer7.gain(3, currPattern->velocity[22][0]);
                  break;
                case INST_ORGAN_NOTES_5:
                  currPattern->velocity[23][0] += parameterInc;
                  mixer8.gain(0, currPattern->velocity[23][0]);
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
          kitSel = (kitSel - 1);
          if (kitSel < 0)
            kitSel = 0;
        }
        else if (controlState == LENGTH_SEL)
        {
          currPattern->settings[2] = currPattern->settings[2] - 1;
          if (currPattern->settings[2] < 1)
          {
            currPattern->settings[2] = 1;
          }
        } else if( controlState == PATTERN_WRITE){
          pattWriteSel -= 1;
          if (pattWriteSel < 0){
            pattWriteSel = 0;
          }
        } else // SHOULD MAKE THIS MORE ROBUST WITH A SWITCH STATEMENT. We assume we're in parameter selection mode if not in KIT_SEL
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
              case INST_ORGAN_CHORDS:
                currPattern->pattern[16][stepEditIndex] = currPattern->pattern[16][stepEditIndex] - 1;
                if (currPattern->pattern[16][stepEditIndex] < 1)
                  currPattern->pattern[16][stepEditIndex] = 12;
                break;
              case INST_GUITAR_CHORDS:
                currPattern->pattern[17][stepEditIndex] = currPattern->pattern[17][stepEditIndex] - 1;
                if (currPattern->pattern[17][stepEditIndex] < 1)
                  currPattern->pattern[17][stepEditIndex] = 12;
                break;
              case INST_GUITAR_ONE:
                currPattern->pattern[18][stepEditIndex] = currPattern->pattern[18][stepEditIndex] - 1;
                if (currPattern->pattern[18][stepEditIndex] < 1)
                  currPattern->pattern[18][stepEditIndex] = 12;
                break;
              case INST_ORGAN_NOTES:
                currPattern->pattern[19][stepEditIndex] = currPattern->pattern[19][stepEditIndex] - 1;
                if (currPattern->pattern[19][stepEditIndex] < 1)
                  currPattern->pattern[19][stepEditIndex] = 12;
                break;
              case INST_ORGAN_NOTES_2:
                currPattern->pattern[20][stepEditIndex] = currPattern->pattern[20][stepEditIndex] - 1;
                if (currPattern->pattern[20][stepEditIndex] < 1)
                  currPattern->pattern[20][stepEditIndex] = 12;
                break;
              case INST_ORGAN_NOTES_3:
                currPattern->pattern[21][stepEditIndex] = currPattern->pattern[21][stepEditIndex] - 1;
                if (currPattern->pattern[21][stepEditIndex] < 1)
                  currPattern->pattern[21][stepEditIndex] = 12;
                break;
              case INST_ORGAN_NOTES_4:
                currPattern->pattern[22][stepEditIndex] = currPattern->pattern[22][stepEditIndex] - 1;
                if (currPattern->pattern[22][stepEditIndex] < 1)
                  currPattern->pattern[22][stepEditIndex] = 12;
                break;
              case INST_ORGAN_NOTES_5:
                currPattern->pattern[23][stepEditIndex] = currPattern->pattern[23][stepEditIndex] - 1;
                if (currPattern->pattern[23][stepEditIndex] < 1)
                  currPattern->pattern[23][stepEditIndex] = 12;
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
              case INST_ORGAN_CHORDS:
                currPattern->parameter[22][stepEditIndex] = currPattern->parameter[22][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[22][stepEditIndex] < 0)
                { // cycle back to beginning of list
                  currPattern->parameter[22][stepEditIndex] = 6;
                }
                break;
              case INST_GUITAR_CHORDS:
                currPattern->parameter[24][stepEditIndex] = currPattern->parameter[24][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[24][stepEditIndex] < 0)
                { // cycle back to beginning of list
                  currPattern->parameter[24][stepEditIndex] = 6;
                }
                break;
              case INST_GUITAR_ONE:
                currPattern->parameter[26][stepEditIndex] = currPattern->parameter[26][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[26][stepEditIndex] < 0)
                { // cycle back to beginning of list
                  currPattern->parameter[26][stepEditIndex] = 6;
                }
                break;
              case INST_ORGAN_NOTES:
//                Serial.println(currPattern->parameter[28][stepEditIndex]);
                currPattern->parameter[28][stepEditIndex] = currPattern->parameter[28][stepEditIndex] - 1; // increment chord type
//                Serial.println(currPattern->parameter[28][stepEditIndex]);
                if (currPattern->parameter[28][stepEditIndex] < -3)
                { // cycle back to beginning of list
                  currPattern->parameter[28][stepEditIndex] = -3;
                }
//                Serial.println("beep");
//                Serial.println(currPattern->parameter[28][stepEditIndex]);
//                Serial.println(" ");
                break;
              case INST_ORGAN_NOTES_2:
                currPattern->parameter[30][stepEditIndex] = currPattern->parameter[30][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[30][stepEditIndex] < -3)
                { // cycle back to beginning of list
                  currPattern->parameter[30][stepEditIndex] = -3;
                }
                break;
              case INST_ORGAN_NOTES_3:
                currPattern->parameter[32][stepEditIndex] = currPattern->parameter[32][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[32][stepEditIndex] < -3)
                { // cycle back to beginning of list
                  currPattern->parameter[32][stepEditIndex] = -3;
                }
                break;
              case INST_ORGAN_NOTES_4:
                currPattern->parameter[34][stepEditIndex] = currPattern->parameter[34][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[34][stepEditIndex] < -3)
                { // cycle back to beginning of list
                  currPattern->parameter[34][stepEditIndex] = -3;
                }
                break;
              case INST_ORGAN_NOTES_5:
                currPattern->parameter[36][stepEditIndex] = currPattern->parameter[36][stepEditIndex] - 1; // increment chord type
                if (currPattern->parameter[36][stepEditIndex] < -3)
                { // cycle back to beginning of list
                  currPattern->parameter[36][stepEditIndex] = -3;
                }
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
              case INST_ORGAN_CHORDS:
                currPattern->velocity[16][0] -= parameterInc;
                mixer6.gain(0, currPattern->velocity[16][0]);
                break;
              case INST_GUITAR_CHORDS:
                currPattern->velocity[17][0] -= parameterInc;
                mixer6.gain(1, currPattern->velocity[17][0]);
                break;
              case INST_GUITAR_ONE:
                currPattern->velocity[18][0] -= parameterInc;
                mixer6.gain(2, currPattern->velocity[18][0]);
                break;
              case INST_ORGAN_NOTES:
                currPattern->velocity[19][0] -= parameterInc;
                mixer7.gain(0, currPattern->velocity[19][0]);
                break;
              case INST_ORGAN_NOTES_2:
                currPattern->velocity[20][0] -= parameterInc;
                mixer7.gain(1, currPattern->velocity[20][0]);
                break;
              case INST_ORGAN_NOTES_3:
                currPattern->velocity[21][0] -= parameterInc;
                mixer7.gain(2, currPattern->velocity[21][0]);
                break;
              case INST_ORGAN_NOTES_4:
                currPattern->velocity[22][0] -= parameterInc;
                mixer7.gain(3, currPattern->velocity[22][0]);
                break;
              case INST_ORGAN_NOTES_5:
                currPattern->velocity[23][0] -= parameterInc;
                mixer8.gain(0, currPattern->velocity[23][0]);
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
  playSdRaw10.stop();
  playSdRaw11.stop();
  playSdRaw12.stop();
  playSdRaw13.stop();
  playSdRaw14.stop();
  playSdRaw15.stop();
  playSdRaw16.stop();
  playSdRaw17.stop();
  playSdRaw18.stop();
  playSdRaw19.stop();
  playSdRaw20.stop();
  playSdRaw21.stop();
  playSdRaw22.stop();
  playSdRaw23.stop();
  playSdRaw24.stop();
  playSdRaw25.stop();
}

///**************************************************************************************************
// * Function endChords
// * -------------------------------------------------------------------------------------------------
// * Overview: checks what chords need to be ended and ends them
// * Input:
// * Output: Nothing
// **************************************************************************************************/
void endChords()
{
  if (currStep >= 0)
  {
    if (currPattern->pattern[16][currStep] <= 0)
    {
      playSdRaw10.stop();
    }
    if (currPattern->pattern[17][currStep] <= 0)
    {
      playSdRaw11.stop();
    }
    if (currPattern->pattern[22][currStep] <= 0){
      playSdRaw17.stop();
    }
  }
}

///**************************************************************************************************
// * Function writeShiftRegisters()
// * -------------------------------------------------------------------------------------------------
// * Overview: checks what chords need to be ended and ends them
// * Input:
// * Output: Nothing
// **************************************************************************************************/
void writeShiftRegisters(){
// grab LED states and pack them into 8-bit numbers to be sent out the shift registers
  uint8_t sr0 = sr0LED[0] | sr0LED[1] << 1 | sr0LED[2] << 2 | sr0LED[3] << 3 |
                sr0LED[4] << 4 | sr0LED[5] << 5 | sr0LED[6] << 6 | sr0LED[7] << 7;

  uint8_t sr1 = sr1LED[0] | sr1LED[1] << 1 | sr1LED[2] << 2 | sr1LED[3] << 3 |
                sr1LED[4] << 4 | sr1LED[5] << 5 | sr1LED[6] << 6 | sr1LED[7] << 7;

  uint8_t sr2 = sr2LED[0] | sr2LED[1] << 1 | sr2LED[2] << 2 | sr2LED[3] << 3 |
                sr2LED[4] << 4 | sr2LED[5] << 5 | sr2LED[6] << 6 | sr2LED[7] << 7;

  uint8_t sr3 = sr3LED[0] | sr3LED[1] << 1 | sr3LED[2] << 2 | sr3LED[3] << 3 |
                sr3LED[4] << 4 | sr3LED[5] << 5 | sr3LED[6] << 6 | sr3LED[7] << 7;
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
  case INST_SEL:
    ledDisplayState = DISP_INST;
    break;
  case SONG_BANK_SEL:
    ledDisplayState = DISP_SONG_BANK;
    break;
  case INST_BANK_SEL:
    ledDisplayState = DISP_INST_BANK;
    break;
  case PATTERN_BANK_SEL:
    ledDisplayState = DISP_PATT_BANK;
    break;
  }
  
  switch (ledDisplayState)
  {
  case DISP_STEPS:
    for (int i = 0; i < 16; i++) // light up which stepss are on for current instrument
    {
      int myInd = i + 16 * patternPlaySection;
      stepLEDs[i] = currPattern->pattern[currInst][myInd];
    }
    if (currStep >= 0)
    {
      stepLEDs[currStep % 16] = 1; // light up the playhead/current step
    }
    break;

  case DISP_PATTERNS: // display current pattern on step LEDs
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[patternNum % 16] = 1;
    break;

  case DISP_SONGS:
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    if (playMode == PLAY_SONG)
    {
      stepLEDs[songNum % 16] = 1;
    }

    break;
  case DISP_INST:
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[currInst % 16] = 1;
    break;
  case DISP_PATT_BANK:
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[pattBankNum] = 1;
    break;
  case DISP_INST_BANK:
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[instBankNum] = 1;
    break;
  case DISP_SONG_BANK:
    for (int i = 0; i < 16; i++)
    {
      stepLEDs[i] = 0;
    }
    stepLEDs[songBankNum] = 1;
    break;
  }
  
  sr0LED[2] = 0;
  sr0LED[3] = 0;
  sr0LED[4] = 0;
  sr0LED[5] = 0;
  switch (patternPlaySection)
  {
  case 0:
    sr0LED[5] = 1;
    break;
  case 1:
    sr0LED[4] = 1;
    break;
  case 2:
    sr0LED[3] = 1;
    break;
  case 3:
    sr0LED[2] = 1;
    break;
  }

  // arrange step LED states we just defined into 8-bit numbers to send to shift registers
  uint8_t sr4 = stepLEDs[0] | stepLEDs[1] << 1 | stepLEDs[2] << 2 | stepLEDs[3] << 3 |
        stepLEDs[8] << 4 | stepLEDs[9] << 5 | stepLEDs[10] << 6 | stepLEDs[11] << 7;

  uint8_t sr5 = stepLEDs[4] | stepLEDs[5] << 1 | stepLEDs[6] << 2 | stepLEDs[7] << 3 |
        stepLEDs[12] << 4 | stepLEDs[13] << 5 | stepLEDs[14] << 6 | stepLEDs[15] << 7;

  // control mode LEDs
  sr3LED[3] = 0; // turn off song LED
  sr3LED[4] = 0; // turn off pattern LED
  sr3LED[6] = 0; // turn off step LED
  sr3LED[0] = 0; // turn off inst LED
  sr3LED[5] = 0; // turn off bank LED
  switch (controlState)
  {
  case STEP_SEL:
    sr3LED[6] = 1; // turn on step LED
    break;
  case SONG_SEL:
    sr3LED[3] = 1; // turn on song LED
    break;
  case SONG_WRITE:
    sr3LED[4] = 1; // turn on pattern LED
    break;
  case PATTERN_SEL:
    sr3LED[4] = 1; // turn on pattern LED
    break;
  case INST_SEL:
    sr3LED[0] = 1; // turn on inst LED
    break;
  case INST_BANK_SEL:
    sr3LED[5] = 1; // turn on bank LED
    break;
  case PATTERN_BANK_SEL:
    sr3LED[5] = 1; // turn on bank LED
    break;
  case SONG_BANK_SEL:
    sr3LED[5] = 1; // turn on bank LED
    break;
  }

  if(transportState == PAUSED){ //blink playpause led if paused
    if (millis() > pauseBlinkTimer){
      sr1LED[1] = pauseLedState;
      pauseLedState = !pauseLedState;
      pauseBlinkTimer += 500;
    }
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


// from https://stackoverflow.com/questions/23191203/convert-float-to-string-without-sprintf
static char * _float_to_char(float x, char *p) {
    char *s = p + CHAR_BUFF_SIZE; // go to end of buffer
    uint16_t decimals;  // variable to store the decimals
    int units;  // variable to store the units (part to left of decimal place)
    if (x < 0) { // take care of negative numbers
        decimals = (int)(x * -100) % 100; // make 1000 for 3 decimals etc.
        units = (int)(-1 * x);
    } else { // positive numbers
        decimals = (int)(x * 100) % 100;
        units = (int)x;
    }

    *--s = (decimals % 10) + '0';
    decimals /= 10; // repeat for as many decimal places as you need
    *--s = (decimals % 10) + '0';
    *--s = '.';

    do {
        *--s = (units % 10) + '0';
        units /= 10;
    } while (units > 0);
    
    if (x < 0) *--s = '-'; // unary minus sign for negative numbers
    return s;
}
