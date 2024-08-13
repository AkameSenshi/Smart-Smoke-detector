const int analogInPin = 36;  // Analog input pin that you want to use

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Configure analog pin as input
  pinMode(analogInPin, INPUT);
}

void loop() {
  // Read analog value on pin 4
  int analogValue = analogRead(analogInPin);

  // Print value to serial monitor
  // Serial.print("Analog value on pin 4: ");
  Serial.println(analogValue);

  // Wait for a short period of time
  delay(100);
}
