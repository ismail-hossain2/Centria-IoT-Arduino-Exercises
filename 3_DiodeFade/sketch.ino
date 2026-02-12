// Exercise 3 - Diode Fade (PWM)
// 1) Blink using analogWrite (on/off)
// 2) Fade in and out

const int LED_PIN = 9;   // PWM pin on Arduino Uno (~9)

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Part 1: blink using analogWrite
  analogWrite(LED_PIN, 255); // max brightness
  delay(1000);
  analogWrite(LED_PIN, 0);   // off
  delay(1000);

  // Part 2: fade in
  for (int value = 0; value <= 255; value++) {
    analogWrite(LED_PIN, value);
    delay(5);
  }

  // fade out
  for (int value = 255; value >= 0; value--) {
    analogWrite(LED_PIN, value);
    delay(5);
  }
}
