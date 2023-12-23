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

  //avancer(axe);

  //tournerDroite(90);

  allerA(1.50,0.80); //allerA(x,y)

  delay(350);

  allerA(0.0,0.0); //allerA(x,y)

  delay(350);

  //tournerGauche(90);


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
