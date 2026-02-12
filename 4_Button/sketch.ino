// Exercise 4 - Button (Toggle LED each press)
// Using INPUT_PULLUP: pressed = LOW, released = HIGH

const int BUTTON_PIN = 2;
const int LED_PIN = 13;

int ledState = LOW;
int lastButtonReading = HIGH;           // because INPUT_PULLUP = HIGH when not pressed
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; // ms

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  Serial.begin(9600);
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);

  // debounce: detect changes and wait a bit
  if (reading != lastButtonReading) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // stable press detected: toggle when button goes from HIGH -> LOW (pressed)
    if (lastButtonReading == HIGH && reading == LOW) {
      ledState = (ledState == LOW) ? HIGH : LOW;
      digitalWrite(LED_PIN, ledState);
      Serial.print("Toggle, LED = ");
      Serial.println(ledState == HIGH ? "ON" : "OFF");
    }
  }

  lastButtonReading = reading;
}
