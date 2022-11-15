/* Interrupt driven rotary encoder routines.
   Target: Teensy 3.1
    
   Written by Per Magnusson, http://www.axotron.se
   v 1.0 2015-11-15
   This program is public domain.
*/
 
// Rotary encoder push button pin, active low
static const int pushPin = 16;
// Rotary encoder phase A pin
static const int rotBPin = 28;
// Rotary encoder phase B pin
static const int rotAPin = 29;
 
#define DEMO 1
 
// Rotary encoder variables, used by interrupt routines
volatile int rotState = 0;
volatile int rotAval = 1;
volatile int rotBval = 1;
volatile int rotAcc = 0;
 
void setup() 
{
  Serial.begin(57600);
 
  pinMode(rotAPin, INPUT);
  pinMode(rotBPin, INPUT);
  pinMode(pushPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(rotAPin), 
    ISRrotAChange, CHANGE);
  attachInterrupt(digitalPinToInterrupt(rotBPin), 
    ISRrotBChange, CHANGE);
}
 
 
void loop() 
{
  static int oldRotAcc = 0; // Remember previous state
  int newRotAcc;
   
  // Do not look directly at the rotary accumulator variable, 
  // it must be done in an interrupt safe manner
  newRotAcc = GetRotAcc(); 
 
  if(!digitalRead(pushPin)) {
    // The button was pushed.
    // Button detection is not interrupt driven, but detection of the 
    // rotary encoder movements goes on also in the busy way below.
    Serial.println("Button down");
    delay(10); // Debounce
    while(!digitalRead(pushPin))
      ;
    delay(10); // Debounce
    Serial.println("Button up");
  } else if(newRotAcc != oldRotAcc) {
    // The encoder was rotated at least one step.
    Serial.println(newRotAcc);
    oldRotAcc = newRotAcc;
  }
}
 
 
// Return the current value of the rotaryEncoder 
// counter in an interrupt safe way.
int GetRotAcc() 
{
  int rot;
   
  cli();
  rot = rotAcc;
  sei();
  return rot;
}
 
 
// Interrupt routines
void ISRrotAChange()
{
  if(digitalRead(rotAPin)) {
    rotAval = 1;
    UpdateRot();
  } else {
    rotAval = 0;
    UpdateRot();
  }
}
 
 
void ISRrotBChange() 
{
  if(digitalRead(rotBPin)) {
    rotBval = 1;
    UpdateRot();
  } else {
    rotBval = 0;
    UpdateRot();
  }
}
 
 
// Update rotary encoder accumulator. 
// This function is called by the interrupt routines.
void UpdateRot() 
{
  // Increment rotAcc if going CW, decrement it if going CCW.
  // Do not increment anything if it was just a glitch.
  switch(rotState) {
    case 0: // Idle state, look for direction
      if(!rotBval) {
        rotState = 1;  // CW 1
      }
      if(!rotAval) {
        rotState = 11; // CCW 1
      }
      break;
    case 1: // CW, wait for A low while B is low
      if(!rotBval) {
        if(!rotAval) {
          rotAcc++;
#ifdef DEMO          
          // Remove this when not in demo mode
          Serial.print(" right "); 
#endif
          rotState = 2; // CW 2
        }
      } else {
        if(rotAval) {
          // It was just a glitch on B, go back to start
          rotState = 0;
        }
      }
      break;
    case 2: // CW, wait for B high
      if(rotBval) {
        rotState = 3; // CW 3
      }
      break;
    case 3: // CW, wait for A high
      if(rotAval) {
        rotState = 0; // back to idle (detent) state
      }
      break;
    case 11: // CCW, wait for B low while A is low
      if(!rotAval) {
        if(!rotBval) {
          rotAcc--;
#ifdef DEMO
          // Remove this when not in demo mode
          Serial.print(" left "); 
#endif
          rotState = 12; // CCW 2
        }
      } else {
        if(rotBval) {
          // It was just a glitch on A, go back to start
          rotState = 0;
        }
      }
      break;
    case 12: // CCW, wait for A high
      if(rotAval) {
        rotState = 13; // CCW 3
      }
      break;
    case 13: // CCW, wait for B high
      if(rotBval) {
        rotState = 0; // back to idle (detent) state
      }
      break;
  }
}
