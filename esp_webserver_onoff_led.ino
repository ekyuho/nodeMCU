#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setup() {
  Serial.begin(115200); 
  WiFi.begin("cookie", "0317137263");
  Serial.println("\nBegin");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Web Server IP = " +String(WiFi.localIP()));
  pinMode(D4, OUTPUT);  
  digitalWrite(D4, 0);

  server.on("/1", [](){
    digitalWrite(D4, 0);
    server.send(200, "text/plain", "Onboard LEN ON");
  });
  server.on("/0", [](){
    digitalWrite(D4, 1);
    server.send(200, "text/plain", "Onboard LED OFF");
  });     
  server.begin(); 
}

void loop() {
  server.handleClient();
}
