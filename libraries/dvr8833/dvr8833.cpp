/*********************************************************************************************
 * Arduino dvr8833 TOOLS - Version 1
 * by ikobootloader
 *
 * License GPLv3
 *********************************************************************************************/
 
#include "Arduino.h"
#include "dvr8833.h"

DVR8833::DVR8833(){}

void DVR8833::setupPins()
{//Paramètres des pins par défaut
   pinMode(_in1Pin, OUTPUT);
   pinMode(_in2Pin, OUTPUT);
   pinMode(_in3Pin, OUTPUT);
   pinMode(_in4Pin, OUTPUT);
}

void DVR8833::setupPins(const uint8_t in1Pin,const uint8_t in2Pin,const uint8_t in3Pin,const uint8_t in4Pin)
{//Paramètres des pins entrés par l'utilisateur	
   pinMode(in1Pin, OUTPUT);
   pinMode(in2Pin, OUTPUT);
   pinMode(in3Pin, OUTPUT);
   pinMode(in4Pin, OUTPUT);
   
   this->in1Pin = in1Pin;
   this->in2Pin = in2Pin;
   this->in3Pin = in3Pin;
   this->in4Pin = in4Pin;
}

void DVR8833::drive(uint8_t action) 
{ //0=DROITE;1=GAUCHE;2=RECUL;3=AVANT;4=ARRET
  digitalWrite(this->in1Pin != 255 ? this->in1Pin : _in1Pin, _tabDrive[action][0]);
  digitalWrite(this->in2Pin != 255 ? this->in2Pin : _in2Pin, _tabDrive[action][1]);
  digitalWrite(this->in3Pin != 255 ? this->in3Pin : _in3Pin, _tabDrive[action][2]);
  digitalWrite(this->in4Pin != 255 ? this->in4Pin : _in4Pin, _tabDrive[action][3]);
} 

//ATTENTION > analogWrite déséquilibre la tension des moteurs : 1v de différence constaté
void DVR8833::driveSpeed(uint8_t action,uint8_t vitesse)
{ //Vitesse de 50% à 100%
  vitesse < 128 ? vitesse = 128 : vitesse;
  vitesse > 255 ? vitesse = 255 : vitesse;
  //0=GAUCHE;1=DROITE;2=RECUL;3=AVANT;4=ARRET
  analogWrite(this->in1Pin != 255 ? this->in1Pin : _in1Pin, _tabDrive[action][0] == 255 ? _tabDrive[action][0] = vitesse : _tabDrive[action][0]);
  analogWrite(this->in2Pin != 255 ? this->in2Pin : _in2Pin, _tabDrive[action][1] == 255 ? _tabDrive[action][1] = vitesse : _tabDrive[action][1]);
  analogWrite(this->in3Pin != 255 ? this->in3Pin : _in3Pin, _tabDrive[action][2] == 255 ? _tabDrive[action][2] = vitesse : _tabDrive[action][2]);
  analogWrite(this->in4Pin != 255 ? this->in4Pin : _in4Pin, _tabDrive[action][3] == 255 ? _tabDrive[action][3] = vitesse : _tabDrive[action][3]);
}	

DVR8833::~DVR8833(){}