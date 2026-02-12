// Exercise 8 - Transmit Data (Arduino B sender)
// Sends a byte using bitmask on DATA pin, toggles CLOCK for each bit

const int DATA_PIN  = 4;
const int CLOCK_PIN = 2;
const int BUTTON_PIN = 7;

byte dataToSend = B10101010;

void setup() {
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  digitalWrite(DATA_PIN, LOW);
  digitalWrite(CLOCK_PIN, LOW);
  Serial.begin(9600);
}

void sendByte(byte data) {
  for (byte mask = B00000001; mask > 0; mask <<= 1) {
    digitalWrite(DATA_PIN, (data & mask) ? HIGH : LOW);

    // clock pulse
    digitalWrite(CLOCK_PIN, HIGH);
    delay(10);
    digitalWrite(CLOCK_PIN, LOW);
    delay(10);
  }
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Sending byte...");
    sendByte(dataToSend);
    delay(500);
  }
}
