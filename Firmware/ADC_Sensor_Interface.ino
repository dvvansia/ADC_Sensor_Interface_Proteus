const int TEMP_PIN = A0;  // PF0 (Pin 61) -> LM35
const int VOLT_PIN = A1;  // PF1 (Pin 60) -> Potentiometer
unsigned long packetID = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("=== SATELLITE TELEMETRY NODE (ATMEGA329P) ===");
  Serial.println("PKT_ID | TIME(ms) | TEMP(C) | BUS_VOLT(V) | ADC0 | ADC1");
}

void loop() {
  int rawTemp = analogRead(TEMP_PIN);
  int rawVolt = analogRead(VOLT_PIN);

  float temperatureC = ((rawTemp * 5.0) / 1024.0) * 100.0;
  float busVoltage = (rawVolt * 5.0) / 1024.0;

  Serial.print(packetID++);
  Serial.print("      | ");
  Serial.print(millis());
  Serial.print("     | ");
  Serial.print(temperatureC, 2);
  Serial.print("   | ");
  Serial.print(busVoltage, 2);
  Serial.print("        | ");
  Serial.print(rawTemp);
  Serial.print("  | ");
  Serial.println(rawVolt);

  delay(1000);
}