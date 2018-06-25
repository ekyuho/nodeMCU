// from Arduino>Example>ESP8266WebServer>HelloServer
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "your_ssid";
const char* password = "your_password";

ESP8266WebServer server(80);

const int led = D4;
const int relay = D3;
const int ON = LOW;
const int OFF = HIGH;

void handleRoot(int cmd) {
  Serial.println("cmd="+ String(cmd));
  digitalWrite(relay, cmd);
  digitalWrite(led, ON);
  server.send(200, "text/plain", "hello from esp8266! cmd="+ String(cmd));
  delay(50);
  digitalWrite(led, OFF);
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void){
  pinMode(led, OUTPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(led, OFF);
  digitalWrite(relay, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  // WiFi.config(IPAddress(192,168,0,250), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){ handleRoot(1); });
  server.on("/1", [](){ handleRoot(1); });
  server.on("/0", [](){ handleRoot(0); });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
