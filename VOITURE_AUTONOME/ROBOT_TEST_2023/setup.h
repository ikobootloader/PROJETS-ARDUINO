#ifndef setup_H
#define setup_H

void setup() {
  iSet                                //Initialisation du Port Série
  voiture.setupPins();                //Paramétrage par défaut des moteurs
  laser.setupWire();                  //Initialisation du télémètre laser
  servo.setupServo();                 //Paramétrage par défaut du servomoteur
  pinMode(KY027, INPUT);              //Paramétrage du capteur de percussion
  cv.setupPins();
  reg.setupPins();                    //SETUP REGISTRE A DECALAGE
  inf1.setupInfra(infrarouge1);       //Capteur infrarouge 1
  inf2.setupInfra(infrarouge2);       //Capteur infrarouge 2
                                      //
  delay(2000);                        //Délai avant l'activation de la boucle loop()
}

#endif