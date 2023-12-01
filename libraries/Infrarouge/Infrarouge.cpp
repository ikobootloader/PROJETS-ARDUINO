/**********************************************************************************************
 * Arduino INFRARED TOOLS - Version 1.0
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include "Infrarouge.h"

INFRAROUGE::INFRAROUGE(){};

/////// SETUP ///////
void INFRAROUGE::setupInfra()
{//setup pin par défaut
	pinMode(this->_infra, INPUT);
}

void INFRAROUGE::setupInfra(unsigned char pin)
{//setup pin par l'utilisateur
	pinMode(pin, INPUT);
	this->infra = pin;
}
                                                   //FONCTION DE DETECTION SUR LA FACE ARRIERE A L'AIDE D'UN CAPTEUR INFRAROUGE
                                                   //FONCTION detectionArriere()
bool INFRAROUGE::detection()
{                                                  //Détection d'obstacle avec le capteur infrarouge
												   //La sensibilité est réglée mécaniquement sur le capteur
  unsigned char valeurIF = digitalRead(this->infra != 0 ? this->infra : this->_infra);               
  return(valeurIF == 0);                           //Si détection retourne TRUE sinon FALSE

}

/////// DESTRUCTEUR ///////
INFRAROUGE::~INFRAROUGE(){};