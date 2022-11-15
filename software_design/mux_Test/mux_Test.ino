bool inputs[8];
int addressPins[3] = {15, 16, 17};
int mux1Data = 3;
int mux2Data = 4;
float tempo = 120;
unsigned long pattern_start_time = 0;
unsigned long curr_step_time = 0;
unsigned int currStep = 0;
unsigned int stepLen = 0;

void setup() {
  //initialize pattern array
  for (int i = 0; i < sizeof(inputs)/sizeof(bool); i++){
    inputs[i] = false;
  }

  //initialize MUX pins
  for (int i = 0; i < 3; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(mux1Data, INPUT);
  pinMode(mux2Data, OUTPUT);

  //initialize serial communication
  Serial.begin(9600);
  Serial.print("Hellooo: ");

  //initialize tempo
  changeTempo(120.0);

  readMux1(true);
  
  //start pattern
      if(inputs[currStep] == true){
      trigNote();
    }
    curr_step_time = millis();
}

void loop() {

// read from MUX and print results
  readMux1(true);
//  writeMux2();

//  //steps
//  if(millis() > curr_step_time + stepLen){
//    currStep = (currStep+1)%8;
//    
//    if(inputs[currStep] == 1){
//      trigNote();
//    }
//    curr_step_time = millis();
//    
//  }
}


//write address to multiplexers
void selectMuxPin(int pin) {
  for (int i = 0; i < 3; i++) {
    if (pin & (1 << i))
      digitalWrite(addressPins[i],  HIGH);
    else
      digitalWrite(addressPins[i],  LOW);
  }
}

void changeTempo(float newTempo){
  tempo = newTempo;
  float quarterLen = (60.0 / tempo) * 1000;
  float eigthLen = quarterLen / 2;
  float sixteenthLen = quarterLen / 4;
  stepLen = quarterLen;
}

void readMux1(bool printEn){
  for (int i = 0; i < 8; i = i){
    selectMuxPin(i);
    delay(2); // give time for signal to propogate through mux before reading
    inputs[i] = digitalRead(3);
    if (printEn){
      Serial.print(inputs[i]);
      Serial.print(" ");
    }
    i++;
  }
  if (printEn){
    Serial.println(" ");
  }
}

void writeMux2(){
    for (int i = 0; i < 8; i = i){
    selectMuxPin(i);
//    delay(2); // give time for signal to propogate through mux before reading
    digitalWrite(mux2Data, !inputs[i]);
    delay(2);
    i++;
  }
}

void trigNote(){
  Serial.print(currStep);
  Serial.print(": ");
  Serial.println("KICK");
}
