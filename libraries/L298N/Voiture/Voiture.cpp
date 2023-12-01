/**********************************************************************************************
 * Arduino L298N TOOLS - Version 1
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/

#include "Arduino.h"
#include "Voiture.h"

VOITURE_CONTROLES::VOITURE_CONTROLES(){}

void VOITURE_CONTROLES::setupPins()
{//Paramètres des pins par défaut
   pinMode(_enAPin, OUTPUT);
   pinMode(_in1Pin, OUTPUT);
   pinMode(_in2Pin, OUTPUT);
   pinMode(_in3Pin, OUTPUT);
   pinMode(_in4Pin, OUTPUT);
   pinMode(_enBPin, OUTPUT);
}

void VOITURE_CONTROLES::setupPins(const unsigned char enAPin,const unsigned char in1Pin,const unsigned char in2Pin,const unsigned char in3Pin,const unsigned char in4Pin,const unsigned char enBPin)
{//Paramètres des pins entrés par l'utilisateur	
   pinMode(enAPin, OUTPUT);
   pinMode(in1Pin, OUTPUT);
   pinMode(in2Pin, OUTPUT);
   pinMode(in3Pin, OUTPUT);
   pinMode(in4Pin, OUTPUT);
   pinMode(enBPin, OUTPUT);
   
   this->enAPin = enAPin;
   this->in1Pin = in1Pin;
   this->in2Pin = in2Pin;
   this->in3Pin = in3Pin;
   this->in4Pin = in4Pin;
   this->enBPin = enBPin;
}

void VOITURE_CONTROLES::locomotion(unsigned char action,unsigned char vitesse) 
{ //0 = AVANT | 1 = ARRIERE | 2 = GAUCHE | 3 = DROITE | 4 = ARRET
  vitesse > 255 ? vitesse = 255 : vitesse;
  analogWrite(this->enAPin != 255 ? this->enAPin : _enAPin,vitesse);//MAX 255 
  digitalWrite(this->in1Pin != 255 ? this->in1Pin : _in1Pin,_tabActions[action][0]);
  digitalWrite(this->in2Pin != 255 ? this->in2Pin : _in2Pin,_tabActions[action][1]);
  analogWrite(this->enBPin != 255 ? this->enBPin : _enBPin,vitesse);//MAX 255
  digitalWrite(this->in3Pin != 255 ? this->in3Pin : _in3Pin,_tabActions[action][2]);
  digitalWrite(this->in4Pin != 255 ? this->in4Pin : _in4Pin,_tabActions[action][3]);
} 

VOITURE_CONTROLES::~VOITURE_CONTROLES(){}
