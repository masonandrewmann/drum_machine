enum playStates{
  Stopped,
  Playing,
  Paused,
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
byte analogMuxAdr = ???;
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


bool stepBool[8][16];

float tempo = 120;
unsigned int stepLen = 0;
unsigned int currStep = 0;
unsigned long currStepTime = 0;

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


void setup() {
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

   changeTempo(120);
}

void loop() {
  readAllMux(false);
  checkButtonPress();
  updateButtonArray();

  // steps
  if(playState == playing){
    if (millis() > (currStepTime  + stepLen)){ // new step has been reached
      currStep = (currStep + 1) % 16; // move step pointer to next step
      clockOutput(); //send clock signal out external output
      for(int i = 0; i < 8; i++){ //send triggers of all instruments to be played at this step
        if(stepBool[i][currStep]){
          trigNote(i);
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
  stepLen = quarterLen;
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
              stepBool[i][j] = !stepBool[currInst][j];
              break;

            case 1: // step buttons 9 - 16
              stepBool[i][j] = !stepBool[currInst][j + 8];
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
                  if (playState == Playing){
                    playState = Paused;
                  } else if ( playState == Paused || playState == Stopped){
                        for(int i = 0; i < 8; i++){ //send triggers of all instruments to be played at this step
                          if(stepBool[i][currStep]){
                            trigNote(i);
                          }
                        }
                        currStepTime = millis();
                  }
                  
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

///**************************************************************************************************
// * Function writeAllLEDs
// * -------------------------------------------------------------------------------------------------
// * Overview: prints currently selected drum pattern to the Serial Monitor
// * Input: Nothing
// * Output: Nothing
// **************************************************************************************************/
void printPattern(){ //
  Serial.println("======== PATTERN BEGIN ========");
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 16; j++){
      Serial.print(stepBool[i][j]);
      Serial.print(" ");
    }
    Serial.println(" ");
  }
  Serial.println("======== PATTERN END ========");
}


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
  Serial.print(currStep);
  Serial.print(": inst ");
//  Serial.println("KICK");
  Serial.println(instNum);
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
