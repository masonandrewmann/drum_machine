unsigned int outVal = 0;

void setup() {
  // put your setup code here, to run once:
  analogWriteResolution(10); // 0 to 4095 
  analogWriteFrequency(5, 448200);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(5, outVal);

  outVal = (outVal + 1) % 1000;
  delay(4);
}
