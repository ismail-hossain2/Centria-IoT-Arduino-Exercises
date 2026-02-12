// Exercise 8 - Transmit Data (Arduino A receiver)
// Data line on pin 4, Clock line on pin 2 (interrupt)

#include <Wire.h>
// LCD optional (depends on simulator/library)

const int DATA_PIN  = 4;
const int CLOCK_PIN = 2;

volatile byte received = 0;
volatile byte bitIndex = 0;
volatile bool byteReady = false;

void onClockRise() {
  int bit = digitalRead(DATA_PIN);
  received |= (bit << bitIndex);
  bitIndex++;
  if (bitIndex >= 8) {
    byteReady = true;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(DATA_PIN, INPUT);
  pinMode(CLOCK_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(CLOCK_PIN), onClockRise, RISING);
}

void loop() {
  if (byteReady) {
    noInterrupts();
    byte msg = received;
    received = 0;
    bitIndex = 0;
    byteReady = false;
    interrupts();

    Serial.print("Received byte: ");
    Serial.println(msg, BIN);
  }
}
