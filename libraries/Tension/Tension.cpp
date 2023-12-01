/**********************************************************************************************
 * Arduino LECTEUR DE TENSION - Version 1.0
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include "Tension.h"

/*
 * 
 * BRANCHER LE CAPTEUR DE TENSION
 * GND VCC : ENTREE SOURCE
 * S : SORTIE VERS ANALOG
 * BORNE '-' VERS GND
 * 
 */

TENSION::TENSION(){};

/** FONCTION DE LECTURE DE LA TENSION **/

//float TENSION::tension = 0;

//Fonction lecture_capteur_tension_PPV()
float TENSION::lecture_tension(unsigned char pin)
{
  // calcul de la tension
  float v = (analogRead(pin) * this->_voltage) / 1024.0;
  float v2 = v / (this->_R2 / (this->_R1 + this->_R2));  
  return v2; 
}

//Fonction tension supérieure ou égale
bool TENSION::tensionAcomparer(float valeurTENSION, unsigned char pin, unsigned char operation)
{
	float tension = TENSION::lecture_tension(pin);
	switch ( operation )
	  {
		 case 0: return(tension >= valeurTENSION); //Si la tension de la batterie est supérieure ou égale à x
			break;
		 case 1: return(tension == valeurTENSION); //Si la tension de la batterie est égale à x
			break;
		 case 2: return(tension <= valeurTENSION); //Si la tension de la batterie est inférieure ou égale à x
			break;			
		 default: return(tension >= valeurTENSION); //Si la tension de la batterie est supérieure ou égale à x
			break;
	  }
}

/////// DESTRUCTEUR ///////
TENSION::~TENSION(){};