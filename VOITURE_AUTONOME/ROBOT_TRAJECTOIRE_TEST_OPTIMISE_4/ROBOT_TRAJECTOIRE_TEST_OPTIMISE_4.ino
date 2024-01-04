/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {

  gestionPPV();
  reactionsObst();
  reactionsChoc();
  eviterObstacles(attente);
  avancer(axe);
  delay(300);
  //i(laser.readRange())
  
  /**
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)
  **/
}
