/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//CONTROLE DES MOTEURS
#include <dvr8833.h>
//Class    Objet
DVR8833    voiture;
#define AVANCER voiture.driveSpeed(AVANCER,200)
#define RECULER voiture.driveSpeed(RECULER,200)
#define GAUCHE voiture.driveSpeed(GAUCHE,255)
#define DROITE voiture.driveSpeed(DROITE,255)
#define ARRET voiture.driveSpeed(ARRET,0)
/***************************************************/
//CONTROLE DU TELEMETRE LASER TOF10120
#include <Laser_rangefinder.h>
//Class             Ojbet
LASER_RANGEFINDER   laser;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned short maxDistance = 300; //300mm
/***************************************************/
//CONTROLE DU SERVOMOTEUR SG90
//Servomoteur.h est esclave de la bibliothèque Servo.h
//Utilisation par défaut du PIN 9 de l'ARDUINO
//Angles de position prédéfinis 5,45,90,135,175
#include <Servomoteur.h>
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;
/***************************************************/
//REACTIONS
void reactions(){
      ARRET; delay(300);
      switch(amplitude)
      {
        case 0 : DROITE; //5°
        break;
        case 1 : DROITE; //45°
        break;
        case 2 : GAUCHE; //90°
        break;
        case 3 : GAUCHE; //135°
        break;   
        case 4 : GAUCHE; //175°
        break;     
        default : AVANCER;
      }
    }
/***************************************************/

void setup() {
  //iSet                                //Initialisation du Port Série (uniquement pour les tests)
  voiture.setupPins();                //Paramétrage par défaut des moteurs
  laser.setupWire();                  //Initialisation du télémètre laser
  servo.setupServo();                 //Paramétrage par défaut du servomoteur
  delay(2000);                        //Délai avant l'activation de la boucle loop()
}

void loop() {
  //i(laser.Reading())
  servo.oscillateur(150);             //Création de l'oscillateur pour le servomoteur (vitesse à 200ms/angle)
  servo.balayage(amplitude);          //Balayage du servomoteur
  //Si un obstacle est détecté par le capteur à ultrason, la fonction reactions() est utilisée sinon le robot avance
  laser.Reading() <= maxDistance ? reactions() : AVANCER;
}