#ifndef setup_H
#define setup_H
/***************************************************/
void setup() {
  iSet                                //Initialisation du Port Série
  /*
  *BRANCHEMENTS PAR DEFAUT (compatiblité vérifiée avec le L298N et le L293D)
  *enAPin = 6; // Contrôle de vitesse PWM du moteur gauche
  *in1Pin = 7; // Moteur gauche Direction 1
  *in2Pin = 5; // Moteur gauche Direction 2
  *in3Pin = 4; // Moteur droit Direction 1
  *in4Pin = 2; // Moteur droit Direction 2
  *enBPin = 3; // Contrôle de vitesse PWM du moteur droit
  */
  VOITURE.setupPins();                //Paramétrage par défaut des moteurs
  laser.begin();                      //Télémètre laser
  delay(2000);                        //Délai avant l'activation de la boucle loop()
}
/***************************************************/
#endif