/**********************************************************************************************
 * Arduino SG90 TOOLS - Version 1.1
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include "Servomoteur.h"

SERVOMOTEUR::SERVOMOTEUR(){};

/////// SETUP ///////

void SERVOMOTEUR::setupServo()
{//Setup par défaut
	Servo::attach(_servoPin);
}

void SERVOMOTEUR::setupServo(const unsigned char servoPin)
{//Sélection du pin par l'utilisateur
	Servo::attach(servoPin);
}

void SERVOMOTEUR::setupServo(const unsigned char servoPin, unsigned char angle)
{//Sélection du pin et de l'angle par l'utilisateur
	Servo::attach(servoPin);
	Servo::write(angle);
}

/////// FONCTIONS ///////

signed char SERVOMOTEUR::qt = 1;
signed char SERVOMOTEUR::amplitude = 0; //Varie avec la fonction oscillateur
bool SERVOMOTEUR::etat = false;

unsigned char SERVOMOTEUR::oscillateur(int delai)
{
  qt--;
  amplitude = qt;
  if(qt < 0){amplitude = qt*-1;}
  if(qt == -4){qt = 4;}
  delay(delai);
  return amplitude;  
}

unsigned char SERVOMOTEUR::angles(const unsigned char angle0, const unsigned char angle1, const unsigned char angle2, const unsigned char angle3, const unsigned char angle4)
{
	this->tabAngles[0] = angle0;
	this->tabAngles[1] = angle1;
	this->tabAngles[2] = angle2;
	this->tabAngles[3] = angle3;
	this->tabAngles[4] = angle4;
}

int SERVOMOTEUR::balayage(unsigned char angle){ //SVM EN ACTION!!	
	Servo::write(this->tabAngles[angle] != 0xFF ? this->tabAngles[angle] : _tabAngles[angle]);
}

/////// DESTRUCTEUR ///////

SERVOMOTEUR::~SERVOMOTEUR(){};

		