HardwareSerial dust(1);

int led[3] = {15, 4, 17};
int gnd[3] = {2, 16, 5};

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], 1);
    
    pinMode(gnd[i], OUTPUT);
    digitalWrite(gnd[i], 0);
  }
  Serial.begin(115200);
  Serial.println("Begin");
  dust.begin(9600,SERIAL_8N1, 18, 2); 
}

void loop() {
  static int j=30;
  // put your main code here, to run repeatedly:
#ifdef XXX
#define COUNT 5
  for (int i=0; i<COUNT; i++) 
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
      delay(300);
      digitalWrite(led[k], 0);
    }
  
  for (int i=0; i<COUNT; i++) 
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
      delay(300);
      digitalWrite(led[k], 0);
      delay(300);
    }

  for (int i=0; i<COUNT; i++) 
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
      delay(30);
      digitalWrite(led[k], 0);
      delay(300);
    }

  for (int i=0; i<COUNT; i++) {
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
      delay(100);
    }
    delay(500);
    for (int k=2; k>=0; k--) {
      digitalWrite(led[k], 0);
      delay(300);
    }
  }

  for (int i=0; i<COUNT; i++) {
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 1);
    }
    delay(500);
    for (int k=0; k<3; k++) {
      digitalWrite(led[k], 0);
    }
    delay(200);
  }
#endif
   
  while (dust.available()) {
    char c = dust.read();
    if (c == 0x42) Serial.printf("\n");
    Serial.printf(" %02X",c );
  }
}
