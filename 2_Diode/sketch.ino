// Exercise 2 - Diode
// 0.5s ON, 2s OFF

void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13, HIGH);
  delay(500);

  digitalWrite(13, LOW);
  delay(2000);
}
