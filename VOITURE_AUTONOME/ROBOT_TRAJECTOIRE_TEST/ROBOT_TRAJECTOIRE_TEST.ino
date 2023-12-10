/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/
long counter = 0;


void loop() {
  //Si un obstacle est détecté par le capteur à ultrason, la fonction reactions() est utilisée sinon le robot avance
  ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance ? reactions() : avancer(); 
  /**
  if(counter == 20){
    retourOrigine(axe);
  }else{
    avancer(axe,0.01);
    counter++;
  }
  **/
  delay(400);
  //i(axe)
  //i(position.x)
  //i(position.y)
}
