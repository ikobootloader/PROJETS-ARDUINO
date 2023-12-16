/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/
int counter = 0;

void loop() {


  //Si un obstacle est détecté, la fonction reactions() est utilisée sinon le robot avance 
  laser.readRange() <= maxDistance? reactions() : avancer(); 
  i(boussole())//écart de 3° à 4° en position statique
  delay(350);

/**
  int val = analogRead(A7);  // read the input pin
  Serial.println(val);          // debug value
**/
/**
  Serial.print("counter: ");
  i(counter)
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)
**/

}
