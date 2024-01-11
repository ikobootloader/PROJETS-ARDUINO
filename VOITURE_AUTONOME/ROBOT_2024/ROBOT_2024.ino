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
  delay(350); //300ms freq correct pour WBSVR

  /**
  //TEST
  //Serial.print("tension ppv :");i(PPV.lecture_tension(A3))
  //Serial.print("tension batterie :");i(batterie.lecture_tension(A6))
  Serial.print("axe: ");
  Serial.println(axe,5);
  Serial.print("x: ");
  Serial.println(position.x,5);
  Serial.print("y: ");
  Serial.println(position.y,5);
  **/
}
