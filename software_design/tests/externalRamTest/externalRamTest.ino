EXTMEM long myExtInt = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myExtInt = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println((long)myExtInt++);
  delay(100);
}
