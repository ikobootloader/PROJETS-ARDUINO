/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {

  gestionPPV();
  gestionBatterie();
  reactionsObst();
  eviterObstacles();
  pileOK == 1 ? pointRecharge() : avancer(axe);
  delay(300); //300ms freq correct pour WBSVR

/**
  //TEST
  Serial.print("tension ppv :");i(PPV.lecture_tension(A3))
  Serial.print("tension batterie :");i(batterie.lecture_tension(A6))
  Serial.print("axe: ");
  i(axe)
  Serial.print("x: ");
  i(position.x)
  Serial.print("y: ");
  i(position.y)
**/
}
