//CONTROLE DES MOTEURS
#include <Voiture.h>
//Class             Objet
VOITURE_CONTROLES   VOITURE; 
#define AVANCER VOITURE.locomotion(AVANCER,200)
#define RECULER VOITURE.locomotion(RECULER,255)
#define GAUCHE VOITURE.locomotion(GAUCHE,255)
#define DROITE VOITURE.locomotion(DROITE,255)
#define ARRET VOITURE.locomotion(ARRET,0)
/***************************************************/
//CONTROLE DU SERVOMOTEUR
//Servomoteur.h est esclave de la bibliothèque Servo.h
//Utilisation par défaut du PIN 9 de l'ARDUINO
//Angles de position prédéfinis 5,45,90,135,175
#include <Servomoteur.h>
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;
/***************************************************/
//CAPTEUR A ULTRASON
#include <HCSR04.h>
const unsigned char trigPin = 13;
const unsigned char echoPin = 12;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 40; //30
UltraSonicDistanceSensor ultrason(trigPin, echoPin);
/***************************************************/
//REACTIONS
void reactions(){
      ARRET; delay(200);
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
  servo.setupServo();                 //Paramétrage par défaut du servomoteur
  delay(2000);                        //Délai avant l'activation de la boucle loop()
}

void loop() {
  servo.oscillateur(100);             //Création de l'oscillateur pour le servomoteur (vitesse à 200ms/angle)
  servo.balayage(amplitude);          //Balayage du servomoteur
  //Si un obstacle est détecté par le capteur à ultrason, la fonction reactions() est utilisée sinon le robot avance
  ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance ? reactions() : AVANCER; 
}
