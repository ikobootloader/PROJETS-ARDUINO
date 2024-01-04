#ifndef config_H
#define config_H
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(115200);
#define i(texte) Serial.println(texte);
/***************************************************/
//CONTROLE DES MOTEURS
#include <Voiture.h>
//Class             Objet
VOITURE_CONTROLES   VOITURE; 
#define AVANCER VOITURE.locomotion(AVANCER,255)
#define RECULER VOITURE.locomotion(RECULER,255)
#define GAUCHE VOITURE.locomotion(GAUCHE,255)
#define DROITE VOITURE.locomotion(DROITE,255)
#define ARRET VOITURE.locomotion(ARRET,0)
/***************************************************/
//CONTROLE DU TELEMETRE LASER TOF050C
#include <Wire.h>
#include "Adafruit_VL6180X.h"
Adafruit_VL6180X laser = Adafruit_VL6180X();
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 254;
/***************************************************/
//TENSION
#include <Tension.h>
//Class  Ojbet
TENSION  batterie,PPV;
/***************************************************/
//CAPTEUR DE CHOC
#define choc A7
//Récupérer l'intensité du choc'
unsigned char capteurChoc(){
  return analogRead(choc);
}
//INTENSITE DU CHOC MAX AUTORISEE AVANT REACTION
const unsigned char maxChoc = 15;
/***************************************************/
//POSITION ET TRAJECTOIRE
#include "trajectoire.h"
/***************************************************/
//REACTIONS
#include "obstacle.h"
/***************************************************/
//RECHARGE
#include "recharge.h"
/***************************************************/
#endif