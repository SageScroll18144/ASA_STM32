void setup() {
  pinMode(PC13, OUTPUT);
}

void loop() {
  digitalWrite(PC13, !digitalRead(PC13));
}
