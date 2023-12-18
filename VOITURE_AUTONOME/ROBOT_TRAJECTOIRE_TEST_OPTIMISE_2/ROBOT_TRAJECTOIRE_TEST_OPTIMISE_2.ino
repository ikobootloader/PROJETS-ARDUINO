/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/
int counter = 0;

void loop() {

  //Si un obstacle est détecté, la fonction reactions() est utilisée sinon le robot avance
  //laser.readRange() <= maxDistance? reactions() : avancer(axe); 
  //tournerDroite(90);

  avancer(axe);

 // allerA(0.20,0.60);

  delay(350);


  //Serial.print("counter: ");
  //i(counter)
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)

//delay(350);
}
