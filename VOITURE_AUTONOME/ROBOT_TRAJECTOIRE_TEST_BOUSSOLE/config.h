#ifndef config_H
#define config_H
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(115200);//115200
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
//CONTROLE DU TELEMETRE LASER TOF050C I2C
#include <Wire.h>
#include "Adafruit_VL6180X.h"
Adafruit_VL6180X laser = Adafruit_VL6180X();
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned short maxDistance = 254;
/***************************************************/
//BOUSSOLE I2C
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
//Position par rapport au Nord en degré
float boussole(){
  sensors_event_t event; 
  mag.getEvent(&event);
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  //Calibrage à -0.5 pour trouver le nord chez moi. 
  //Ce qui compte, c'est la stabilité magnétique de la boussole !
  float declinationAngle = -0.50;
  heading += declinationAngle; 
  if(heading < 0)heading += 2*PI;
  if(heading > 2*PI)heading -= 2*PI;
  float headingDegrees = heading * 180/M_PI;
  //i(headingDegrees)
  return headingDegrees;
}
//Mesure avant rotation
int mesureAvRotation = 0;
/***************************************************/
//POSITION ET TRAJECTOIRE
#include "trajectoire.h"
/***************************************************/
//REACTIONS
void reactions(){
      arret();
      tournerDroite();
    }
/***************************************************/
#endif
