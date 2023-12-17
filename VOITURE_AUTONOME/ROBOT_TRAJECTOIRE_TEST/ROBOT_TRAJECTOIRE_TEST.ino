/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/
int counter = 0;

void loop() {

  //Si un obstacle est détecté, la fonction reactions() est utilisée sinon le robot avance
  laser.readRange() <= maxDistance? reactions() : avancer(); 
  //tournerDroite(90);
  delay(350);

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

//delay(350);
}
