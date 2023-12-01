/**********************************************/
#include <ESP8266WiFi.h>
#include "pass.h" //Contient les infos de connexion ssid et password
/**********************************************/
#include <ESP8266WebServer.h>
#include "html.h"
ESP8266WebServer server(80);
String message = "";

void sendTEST(){
  if(Serial.available()) {
    message = Serial.readString();
  } 
  server.send(200, "text/plain", message);
}

void WEBSERVER(){
  String page(reinterpret_cast<const __FlashStringHelper *> (html));
  server.on("/TEST", sendTEST); 
  server.send(200, "text/html", page);
}
/**********************************************/

void setup() {
  /* COMMUNICATION SERIE */
  Serial.begin(9600);
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
