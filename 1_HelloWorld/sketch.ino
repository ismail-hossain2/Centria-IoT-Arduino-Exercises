// Exercise 1 - Hello World

int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(counter);
  counter++;

  if(counter > 10) {
    counter = 0;
  }

  delay(1000);
}
