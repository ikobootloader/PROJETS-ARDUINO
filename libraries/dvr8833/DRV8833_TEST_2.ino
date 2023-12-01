/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//CONTROLE DES MOTEURS
#include <dvr8833.h>
//Class    Objet
DVR8833    voiture; 

void setup() {
  iSet                                //Initialisation du Port Série (uniquement pour les tests)
  voiture.setupPins();                //Initialisation des pins 
}

void loop() {
  //0=DROITE;1=GAUCHE;2=RECUL;3=AVANT;4=ARRET
  //voiture.drive(3);
  //Contrôle de la vitesse de 128 (50%) à 255 (100%)
  voiture.driveSpeed(3,128);
}
