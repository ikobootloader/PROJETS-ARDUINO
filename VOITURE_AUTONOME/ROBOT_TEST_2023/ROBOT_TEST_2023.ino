/***************************************************/
#include "config.h"
/***************************************************/
#include "setup.h"
/***************************************************/

void loop() {
  etatBatterie(tension);              //Si la batterie est trop faible : avertissement lumineux sinon LED blanche
  servo.oscillateur(150);             //Création de l'oscillateur pour le servomoteur (vitesse à 200ms/angle)
  i(amplitude)                        //Communiquer l'angle à l'ESP8266
  servo.balayage(amplitude);          //Balayage du servomoteur
                                      //Si un obstacle est détecté par le capteur à ultrason, la fonction reactions() est utilisée sinon le robot avance
  laser.Reading() <= maxDistance ? reactions() : AVANCER;
  choc();                             //Mouvement de recul en cas de choc        
                                      //Si la vitesse diminue de 75% sur l'une des roues : mouvement réflexe
  vitesseRoues(cv.cvr(cv.CapteurVitesse1,NbLoop,pour100DiffMax),cv.cvr(cv.CapteurVitesse2,NbLoop,pour100DiffMax)); 
  //infraDetection(); //Ne fonctionne pas correctement, détecte le fonctionnement des moteurs
}