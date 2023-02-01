// NOTE NOTE NOTE NOTE NOTE
//need to split the reads between digitalRead and analogRead

int inputs[8][8];
int muxAddressPins[3] = {15, 16, 17};
int muxDataPins[7] = {14, 39, 38, 33, 40, 41, 22};

void setup() {

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


}

void loop() {

// read from MUX and print results
  readMux(true);
  delay(100);
}


//write address to multiplexers
void selectMuxPin(int pin) {
  for (int i = 0; i < 3; i++) {
    if (pin & (1 << i))
      digitalWrite(muxAddressPins[i],  HIGH);
    else
      digitalWrite(muxAddressPins[i],  LOW);
  }
}


void readMux(bool printEn){
  for (int i = 0; i < 8; i++){
    selectMuxPin(i);
    delay(2); // give time for signal to propogate through mux before reading
    for (int j = 0; j < 8; j++){
      inputs[j][i] = digitalRead(muxDataPins[j]);
    }
  }
  if (printEn){
    for (int i = 0; i < 8; i++){
      for (int j = 0; j < 8; j++){
        Serial.print(inputs[i][j]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }
    Serial.println(" ");
    Serial.println(" ");
  }
}
