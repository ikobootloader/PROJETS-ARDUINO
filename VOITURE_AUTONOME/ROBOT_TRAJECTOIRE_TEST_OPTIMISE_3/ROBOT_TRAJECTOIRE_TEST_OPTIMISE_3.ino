/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {

  reactionsObst();
  reactionsChoc();
  avancer(axe);
  eviterObstacles(attente);
  delay(350);
  
  /**
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)
  **/
}
