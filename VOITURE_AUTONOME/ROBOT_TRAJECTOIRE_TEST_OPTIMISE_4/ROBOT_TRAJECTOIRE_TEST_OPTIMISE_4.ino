/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {

  gestionPPV();
  gestionBatterie();
  reactionsObst();
  reactionsChoc();
  eviterObstacles();
  pileOK == 1 ? pointRecharge() : avancer(axe);
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
