HardwareSerial dust(1);

void setup() {
  Serial.begin(115200);
  Serial.println("Begin");
  dust.begin(9600,SERIAL_8N1, 18, 2); 
}

void loop() {
  while (dust.available()) {
    char c = dust.read();
    if (c == 0x42) Serial.printf("\n");
    Serial.printf(" %02X",c );
  }
}
