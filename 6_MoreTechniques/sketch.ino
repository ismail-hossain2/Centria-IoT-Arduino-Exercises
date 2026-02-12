// Exercise 6 - More Techniques
// 1) Calibration for light sensor
// 2) Running average (10 samples)
// 3) Blink an LED according to a bitmask

const int SENSOR_PIN = A0;     // light/sound sensor in Wokwi
const int LED_PIN = 13;

int sensorMin = 1023;
int sensorMax = 0;

// running average
const int numReadings = 10;
int readings[numReadings];
int readIndex = 0;
long total = 0;

byte pattern = B10101010; // example bitmask pattern
byte mask = B00000001;
unsigned long lastBitTime = 0;
const unsigned long bitInterval = 200; // ms

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);

  // CALIBRATION first 5 seconds
  unsigned long start = millis();
  while (millis() - start < 5000) {
    int v = analogRead(SENSOR_PIN);
    if (v > sensorMax) sensorMax = v;
    if (v < sensorMin) sensorMin = v;
  }
  Serial.print("Calibration done. Min=");
  Serial.print(sensorMin);
  Serial.print(" Max=");
  Serial.println(sensorMax);

  // init readings
  for (int i = 0; i < numReadings; i++) readings[i] = 0;
}

void loop() {
  // 1) “dark” detection using calibrated min/max (simple threshold)
  int v = analogRead(SENSOR_PIN);
  int threshold = (sensorMin + sensorMax) / 2;
  if (v < threshold) digitalWrite(LED_PIN, HIGH);
  else digitalWrite(LED_PIN, LOW);

  // 2) Running average of 10 values
  total -= readings[readIndex];
  readings[readIndex] = v;
  total += readings[readIndex];
  readIndex = (readIndex + 1) % numReadings;
  int average = total / numReadings;

  Serial.print("raw=");
  Serial.print(v);
  Serial.print(" avg=");
  Serial.println(average);

  // 3) Bitmask blink pattern (non-blocking)
  unsigned long now = millis();
  if (now - lastBitTime >= bitInterval) {
    lastBitTime = now;

    if (pattern & mask) {
      // ON pulse
      // (Use a short flash to represent “1”)
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }

    mask <<= 1;
    if (mask == 0) mask = B00000001; // restart
  }

  delay(20);
}
