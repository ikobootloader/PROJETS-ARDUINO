/**********************************************/
#include <ESP8266WiFi.h>
#include "pass.h" //Contient les infos de connexion ssid et password
/**********************************************/
#include <ESP8266WebServer.h>
#include "html.h"
ESP8266WebServer server(80);
String message = "";

void sendValue(){
  if(Serial.available()) {
    message = Serial.readStringUntil('\r\n');
    Serial.flush();
  } 
  server.send(200, "text/plain", message);
  message = "";
}

void WEBSERVER(){
  String page(reinterpret_cast<const __FlashStringHelper *> (html));
  server.on("/direction", sendValue); 
  server.send(200, "text/html", page);
}
/**********************************************/

void setup() {
  /* COMMUNICATION SERIE */
  Serial.begin(115200);
  /* WEBSERVER */
  WiFi.begin(ssid,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP()); //Récupérer l'adresse IP locale
  /* WEBSERVER */
  server.on("/", WEBSERVER);
  server.begin();
}

void loop() {
  server.handleClient();
}
