//#include <LinkedList.h>
#define DEMO 1

enum instruments{
  bd,
  sd,
  cyn1,
  cyn2,
  glitch,
  digi1,
  digi2,
  digi3,
  
  digi4, 
  digi5,
  digi6, 
  digi7,
  digi8,
  digi9,
  digi10,
  digi11
};

enum transportStates{
  Stopped,
  Playing,
  Paused,
};

//transport variables
float tempo = 120;
unsigned int stepLen = 0;
unsigned int currStep = 0;
unsigned long currStepTime = 0;

int transportState = Playing;


//Contact SH_CP - Clock
int SH_CP = 31;
//Contact ST_CP - Latch
int ST_CP = 32;
//Contact DS - Data
int DS = 30;

int inputs[8][8];
int inputsPrev[8][8];
int muxAddressPins[3] = {15, 16, 17};
int muxDataPins[7] = {14, 39, 38, 33, 40, 41, 22};

int stepButtons[16];
int stepButtonsPrev[16];

int controlButtons[16];
int controlButtonsPrev[16];

bool instSteps[16][16];

bool sr0LED[8];
bool sr1LED[8];
bool sr2LED[8];
bool sr3LED[8];
bool stepLEDs[16];



int currInst = bd;

//linked list for handling output pulse timing
unsigned long outPulseTimes[16];
//class OutPulse {
//  public:
//    unsigned long endTime;
//    int instNum;
//}
//
//LinkedList<OutPulse*> outPulseTimer = LinkedList<OutPulse*>();

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

void setup() {
   //setup for shift register
   pinMode(SH_CP, OUTPUT); // clock pin
   pinMode(ST_CP, OUTPUT); // latch
   pinMode(DS, OUTPUT);    // data pin
   
  //initialize MUX address pins
  for (int i = 0; i < sizeof(muxAddressPins)/sizeof(muxAddressPins[0]); i++){
    pinMode(muxAddressPins[i], OUTPUT);
  }

  //initialize MUX data pins
  for (int i = 0; i < sizeof(muxDataPins)/sizeof(muxDataPins[0]); i++){
    pinMode(muxDataPins[i], INPUT);
  }

  //initialize serial communication
  Serial.begin(115200);
  Serial.print("Hellooo: ");

  for (int i = 0; i < 16; i++){
    stepButtons[i] = 0;
    stepButtonsPrev[i] = 0;
    outPulseTimes[i] = 0;
    for (int j = 0; j < 16; j++){
      instSteps[i][j] = false;
    }
    stepLEDs[i] = 1;
  }

  for (int i = 0; i < 8; i ++){
    sr0LED[i] = 0;
    sr1LED[i] = 0;
    sr2LED[i] = 0;
    sr3LED[i] = 0;
  }
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
}

void loop() {
  readMux(false);
  // steps
  if(transportState == Playing){
    if (millis() > (currStepTime  + stepLen)){ // new step has been reached
      currStep = (currStep + 1) % 16; // move step pointer to next step
      clockOutput(); //send clock signal out external output
      for(int i = 0; i < 16; i++){ //send triggers of all instruments to be played at this step
        if(instSteps[i][currStep]){
          trigNote(i);
        }
      }
  
      currStepTime = millis();
    }
  }

  for (int i = 0; i < 16; i++){
    if (outPulseTimes[i] != 0){
      if(millis() > outPulseTimes[i]){
        Serial.println("PULSE COMPLETE");
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
  //loop through and read all mux values
  for (int i = 0; i < 8; i++){
    selectMuxPin(i);
    delay(2); // give time for signal to propogate through mux before reading
    for (int j = 0; j < 7; j++){
      if (j == 4 ||  j == 5){
        inputs[j][i] = analogRead(muxDataPins[j]);
      } else {
        inputs[j][i] = digitalRead(muxDataPins[j]);
      }
      
    }
  }

  //check current instrument



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

  if(!controlButtons[0]){
    if(!stepButtons[0]) currInst = bd;
    else if (!stepButtons[1]) currInst = sd;
    else if (!stepButtons[2]) currInst = cyn1;
    else if (!stepButtons[3]) currInst = cyn2;
    else if (!stepButtons[4]) currInst = glitch;
    else if (!stepButtons[5]) currInst = digi1;
    else if (!stepButtons[6]) currInst = digi2;
    else if (!stepButtons[7]) currInst = digi3;

    else if (!stepButtons[8]) currInst = digi4;
    else if (!stepButtons[9]) currInst = digi5;
    else if (!stepButtons[10]) currInst = digi6;
    else if (!stepButtons[11]) currInst = digi7;
    else if (!stepButtons[12]) currInst = digi8;
    else if (!stepButtons[13]) currInst = digi9;
    else if (!stepButtons[14]) currInst = digi10;
    else if (!stepButtons[15]) currInst = digi11;
    Serial.print("current inst ");
    Serial.println(currInst);
  }
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

  //check if any step buttons have been pressed and update instSteps array
  if(controlButtons[0]){ // make sure we aren't in selection mode
    for (int i = 0; i < 16; i++){
      if (stepButtons[i] != stepButtonsPrev[i]){
        if (stepButtons[i] == LOW){
         instSteps[currInst][i] = !instSteps[currInst][i];
        }
      }
    }
  }

  //check if any control buttons have been pressed
  for (int i = 0; i < 16; i++){
    if((controlButtons[i] != controlButtonsPrev[i]) && (controlButtons[i] == LOW)){
      switch(i) {
        case 0: //inst sel
        break;

        case 1: //save
        break;

        case 2: //shift
        break;

        case 3: //song
        break;

        case 4: //mute
        break;

        case 5: //pattern
        break;

        case 6: //dataEncBut
        break;

        case 7: //tempoEncBut
        break;

        case 8: //bank
        break;

        case 9: //step
        break;

        case 10: //beatRep1
        break;

        case 11: //beatRep2
        break;

        case 12: //playpause
          if(transportState == Playing){
            transportState = Paused;
            sr1LED[1] = 0;
            Serial.println("Paused!");
          } else {
            transportState = Playing;
            sr1LED[2] = 0;
            sr1LED[1] = 1;
            Serial.println("Playing!");
          }
        break;

        case 13: //stop
          sr1LED[2] = 1;
          sr1LED[1] = 0;
          transportState = Stopped;
          currStep = -1;
          Serial.println("Stopped!");
        break;

        case 14: //forwards
        break;

        case 15: //backwards
        break;
      }
    }
  }


  //write SR outputs
  uint8_t sr0 = sr0LED[0] | sr0LED[1]<<1 | sr0LED[2]<<2 | sr0LED[3]<<3 |
                sr0LED[4]<<4 | sr0LED[5]<<5 | sr0LED[6]<<6 | sr0LED[7]<<7;
                
  uint8_t sr1 = sr1LED[0] | sr1LED[1]<<1 | sr1LED[2]<<2 | sr1LED[3]<<3 |
                sr1LED[4]<<4 | sr1LED[5]<<5 | sr1LED[6]<<6 | sr1LED[7]<<7;
                
  uint8_t sr2 = sr2LED[0] | sr2LED[1]<<1 | sr2LED[2]<<2 | sr2LED[3]<<3 |
                sr2LED[4]<<4 | sr2LED[5]<<5 | sr2LED[6]<<6 | sr2LED[7]<<7;
                
  uint8_t sr3 = sr3LED[0] | sr3LED[1]<<1 | sr3LED[2]<<2 | sr3LED[3]<<3 |
                sr3LED[4]<<4 | sr3LED[5]<<5 | sr3LED[6]<<6 | sr3LED[7]<<7;

  int stepLEDMask = 0;
  if (currStep != -1){
    stepLEDMask = 1 << currStep;
  }
  
  for (int i = 0; i < 16; i++){
    stepLEDs[i] = instSteps[currInst][i];
  }
  stepLEDs[currStep] = 1;
    
  uint8_t sr4 = stepLEDs[0] | stepLEDs[1]<<1 | stepLEDs[2]<<2 | stepLEDs[3]<<3 |
                stepLEDs[8]<<4 | stepLEDs[9]<<5 | stepLEDs[10]<<6 | stepLEDs[11]<<7;

  uint8_t sr5 = stepLEDs[4] | stepLEDs[5]<<1 | stepLEDs[6]<<2 | stepLEDs[7]<<3 |
                stepLEDs[12]<<4 | stepLEDs[13]<<5 | stepLEDs[14]<<6 | stepLEDs[15]<<7;
    
//  uint8_t sr4 = (instSteps[currInst][0] | instSteps[currInst][1]<<1 | instSteps[currInst][2]<<2 | instSteps[currInst][3]<<3 |
//                instSteps[currInst][8]<<4 | instSteps[currInst][9]<<5 | instSteps[currInst][10]<<6 | instSteps[currInst][11]<<7);
//                
//  uint8_t sr5 = (instSteps[currInst][4] | instSteps[currInst][5]<<1 | instSteps[currInst][6]<<2 | instSteps[currInst][7]<<3 |
//                instSteps[currInst][12]<<4 | instSteps[currInst][13]<<5 | instSteps[currInst][14]<<6 | instSteps[currInst][15]<<7);
  
  digitalWrite(ST_CP, LOW);
  shiftOut(DS, SH_CP, MSBFIRST, sr5);
  shiftOut(DS, SH_CP, MSBFIRST, sr4);
  shiftOut(DS, SH_CP, MSBFIRST, sr3);
  shiftOut(DS, SH_CP, MSBFIRST, sr2);
  shiftOut(DS, SH_CP, MSBFIRST, sr1);
  shiftOut(DS, SH_CP, MSBFIRST, sr0);


  digitalWrite(ST_CP, HIGH);

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

    //print stepButtons
//    for (int i  = 0; i < 16; i++){
//      for (int j = 0; j < 16; j++){
//        Serial.print(instSteps[i][j]);
//        Serial.print(" ");
//      }
//      Serial.println(" ");
//    }

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

/////**************************************************************************************************
//// * Function checkButtonPress
//// * -------------------------------------------------------------------------------------------------
//// * Overview: checks if buttons have been pressed and might do things on these presses
//// * Input: Nothing
//// * Output: Nothing
//// **************************************************************************************************/
//void checkButtonPress(){
//  for (int i = 0; i < 2; i++){ // check the step buttons 
//    for (int j = 0; j < 8; j++){
//      if (currButtons[i][j] =! lastButtons[i][j]){ // check if button changed states
//        if(currButtons[i][j] == true){ //button pressed
//
//          //check modifiers 
//          if (currButtons[2][0]){ // instrument select modifier
//            if (i == 0){
//              currInst = j;
//            } else if (i == 1){
//              currInst = j + 1;
//            }
//          }
//        } else {
//
//          switch(i){
//            case 0:// step buttons 1 - 8
//              stepBool[i][j] = !stepBool[currInst][j];
//              break;
//
//            case 1: // step buttons 9 - 16
//              stepBool[i][j] = !stepBool[currInst][j + 8];
//              break;
//
//            case 2: // first set of control buttons
//              switch(j){
//                case 0: // instrument select
//                  break;
//
//                case 1: // save
//                  break;
//
//                case 2: // shift
//                  break;
//
//                case 3: // song
//                  break;
//
//                case 4: // pattern
//                  break;
//
//                case 5: // bank
//                  break;
//
//                case 6: // play/pause
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
//                  break;
//
//                case 7: // stop
//                  playState = Stopped;
//                  currStep = 0;
//                  break;
//              }
//
//          }
//          
//        }
//          } else if (currButtons[i][j] == false){ //button released
//            //insert button released code
//          }
//        } 
//      }
//  }

///**************************************************************************************************
// * Function writeAllLEDs
// * -------------------------------------------------------------------------------------------------
// * Overview: prints currently selected drum pattern to the Serial Monitor
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
//void printPattern(){ //
//  Serial.println("======== PATTERN BEGIN ========");
//  for (int i = 0; i < 8; i++){
//    for (int j = 0; j < 16; j++){
//      Serial.print(stepBool[i][j]);
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
  for (int i = 7; i--; i > -1){
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
// * Function trigNote
// * -------------------------------------------------------------------------------------------------
// * Overview: prints to serial monitor when an note is triggered
// * Input: 
// *    int instNum : number of the instrument being triggered
// * Output: Nothing
// **************************************************************************************************/
void trigNote(int instNum){
  //send pulse voltage out
  if (instNum < 8){
    int pulseLen = 10;
    switch(instNum){
      case 0: //BD
        sr3LED[7] = 0;
        pulseLen = 10;
        break;
  
      case 1: //SN
        sr2LED[2] = 0;
        pulseLen = 5;
        break;
  
      case 2: //CYN1
        sr0LED[0] = 0;
        pulseLen = 10;
        break;
  
      case 3: //CYN2
        sr0LED[7] = 0;
        pulseLen = 10;
        break;
  
      case 4: //GLITCH
        sr2LED[4] = 0;
        pulseLen = 10;
        break;
  
      case 5: //DIGI1
        sr2LED[7] = 0;
        pulseLen = 10;
        break;
  
      case 6: //DIGI2
        sr2LED[6] = 0;
        pulseLen = 10;
        break;
  
      case 7: //DIGI3
        sr2LED[5] = 0;
        pulseLen = 100;
        break;
    }
    outPulseTimes[instNum] = millis() + pulseLen;
    Serial.print(millis());
    Serial.print(" ");
    Serial.println(outPulseTimes[instNum]);
  }
  //trigger note on audio board
  //INSERT CODE HERE TO DO THIS
  
//  Serial.print(currStep);
//  Serial.print(": inst ");
////  Serial.println("KICK");
//  Serial.println(instNum);
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
    Serial.print(instSteps[i][currStep]);
  }
  Serial.println(" ");
}

// how to write all LEDs
// digitalWrite(ST_CP, LOW);
// shiftOut(DS, SH_CP, MSBFIRST, 0b10000000);
// /* more calls to shiftOut here for daisychained shift registers */
// digitalWrite(ST_CP, HIGH);

 
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
