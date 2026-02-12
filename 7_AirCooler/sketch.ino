// Exercise 7 - Air Cooler (Servo + Temperature + Relay + Emergency stop)
// Based on course "7 air cooler"

#include <Servo.h>

const int SERVO_PIN = 5;
const int TEMP_PIN  = A0;  // simulate temperature sensor with potentiometer in Wokwi
const int RELAY_PIN = 7;   // relay output (simulated with LED if needed)
const int EMERGENCY_PIN = 2; // interrupt pin (button)

Servo myservo;

volatile bool emergencyStop = false;

void emergencyISR() {
  emergencyStop = true; // latch STOP (does NOT resume)
}

void setup() {
  Serial.begin(9600);
  myservo.attach(SERVO_PIN);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(EMERGENCY_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(EMERGENCY_PIN), emergencyISR, FALLING);
}

void loop() {
  if (emergencyStop) {
    myservo.write(0);
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("EMERGENCY STOP ACTIVE");
    delay(500);
    return;
  }

  int raw = analogRead(TEMP_PIN);           // 0..1023
  // simulate temperature 0..50°C
  float tempC = map(raw, 0, 1023, 0, 50);

  // show temperature with servo position (0..180)
  int angle = map(raw, 0, 1023, 0, 180);
  myservo.write(angle);

  // relay closes when temp > 28°C
  if (tempC > 28.0) digitalWrite(RELAY_PIN, HIGH);
  else digitalWrite(RELAY_PIN, LOW);

  Serial.print("tempC=");
  Serial.print(tempC);
  Serial.print(" servo=");
  Serial.print(angle);
  Serial.print(" relay=");
  Serial.println(tempC > 28.0 ? "ON" : "OFF");

  delay(200);
}
