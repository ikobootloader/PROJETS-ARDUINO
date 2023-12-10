/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {
  //Si un obstacle est détecté par le capteur à ultrason, la fonction reactions() est utilisée sinon le robot avance
  //ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance ? reactions() : avancer(); 

  allerA(0.20,0.20);
  
  delay(500);

  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)
}
