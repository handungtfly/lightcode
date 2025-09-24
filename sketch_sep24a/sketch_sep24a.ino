void setup() {
  // initialize digital pin as an output.
  pinMode(2, OUTPUT);
  pinMode(6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(6, HIGH);
  digitalWrite(2, LOW);
  delay(5000);
  digitalWrite(6, LOW);
  digitalWrite(2, LOW);
  delay(5000);
  digitalWrite(2, LOW);
  digitalWrite(6, HIGH);
  delay(5000);
  digitalWrite(6, HIGH);
  digitalWrite(2, HIGH);
  delay(5000);
}

