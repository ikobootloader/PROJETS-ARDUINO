#include <Voiture.h>
/*
 *BRANCHEMENTS PAR DEFAUT
 *enAPin = 6; // Contrôle de vitesse PWM du moteur gauche
 *in1Pin = 7; // Moteur gauche Direction 1
 *in2Pin = 5; // Moteur gauche Direction 2
 *in3Pin = 4; // Moteur droit Direction 1
 *in4Pin = 2; // Moteur droit Direction 2
 *enBPin = 3; // Contrôle de vitesse PWM du moteur droit
*/

//Class             Objet
VOITURE_CONTROLES   VOITURE;

void setup() {

  //Paramétrage par défaut
  VOITURE.setupPins();
  //Paramétrage manuel: VOITURE.setupPins(enAPin,in1Pin,in2Pin,in3Pin,in4Pin,enBPin)
  //Exemple: VOITURE.setupPins(6,7,5,4,2,3);

}

void loop() {

  //Paramétrage par nombre ou mot
  //0 ou AVANT | 1 ou ARRIERE | 2 ou GAUCHE | 3 ou DROITE | 4 ou ARRET
  //Exemple: VOITURE.locomotion(0,255) <=> VOITURE.locomotion(AVANCER,255)
  //VOITURE.locomotion(0,255);
  VOITURE.locomotion(AVANCER,255);

}
