unsigned int outVal = 0;

void setup() {
  // put your setup code here, to run once:
  analogWriteResolution(10); // 0 to 1023 
  analogWriteFrequency(2, 448200);
  analogWriteFrequency(3, 448200);
  analogWriteFrequency(4, 448200);
  analogWriteFrequency(5, 448200);
  analogWriteFrequency(9, 448200);
  analogWriteFrequency(37, 448200);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(2, outVal + 300);
  analogWrite(3, outVal + 300);
  analogWrite(4, outVal + 300);
  analogWrite(5, outVal + 300);
  analogWrite(9, outVal + 300);
  analogWrite(37, outVal + 300);

  outVal = (outVal + 10) % 700;
  delay(1);
}
