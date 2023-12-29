/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {

  //Si un obstacle est détecté, la fonction reactions() est utilisée sinon le robot avance
  laser.readRange() <= maxDistance? reactions() : avancer(axe);

  delay(500);
  
  
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)

}
