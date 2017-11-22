//
//    FILE: test_ds18b20.ino
//  AUTHOR: Kyuho Kim (ekyuho@gmail.com)
// CREATED: November 22, 2017
// Released to the public domain
//
#include <SoftwareSerial.h>
SoftwareSerial dust(D1, D0, false, 256);  // RX, TX   no conneciton for TX (D0)

void setup() {
  Serial.begin(115200);
  dust.begin(9600);

  Serial.println("\nReading dust sensors");
}

void loop() {
  while (dust.available() > 0)
    Serial.println(dust.read(), HEX);
}
