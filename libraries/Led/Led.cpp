/**********************************************************************************************
 * Arduino LED TOOLS - Version 1
 * by ikobootloader
 *
 * License GPLv3 
 **********************************************************************************************/

#include "Arduino.h"
#include "Led.h"
 
/*
 * 
 * CODES COULEURS
 * VERT = OK
 * ROUGE = OBSTACLE
 * JAUNE = PARCOURS/ROUTINE
 * 
 * Utilisation de la fonction native ARDUINO digitalWrite()
 * 
 */
 
 LED::LED(){}
 
/*=========================================================*/ 

//FONCTION setupLED()

void LED::setupLED(unsigned char _ledPinRouge, unsigned char _ledPinJaune, unsigned char _ledPinVert)
{                                         
	this->_ledRouge = _ledPinRouge;
	this->_ledJaune = _ledPinJaune;
	this->_ledVert = _ledPinVert;
	
	pinMode(_ledPinRouge, OUTPUT);           		//LED rouge
	pinMode(_ledPinJaune, OUTPUT);           		//LED jaune
	pinMode(_ledPinVert, OUTPUT);            		//LED verte
}

/*=========================================================*/ 

//FONCTION Rouge()
void LED::Rouge(bool etat)
{													//Si 0 éteinte Si 1 allumée                                         
	digitalWrite(this->_ledRouge, etat);            //LED ROUGE 
}

/*=========================================================*/ 

//FONCTION Vert()
void LED::Vert(bool etat)
{
	digitalWrite(this->_ledVert, etat);           	//LED VERTE
}

/*=========================================================*/ 

//FONCTION Jaune()
void LED::Jaune(bool etat)
{
	digitalWrite(this->_ledJaune, etat);            //LED JAUNE
}

/*=========================================================*/ 

//FONCTION vert()
void LED::vertIsole()
{                                        			/** ALLUMER VERT ET ETEINDRE LES AUTRES LED **/
    LED::Jaune(0);                     				//Eteindre LED jaune
    LED::Rouge(0);                     				//Eteindre LED rouge
    LED::Vert(1);                       			//Allumer LED verte 
}

/*=========================================================*/ 

//FONCTION rouge()
void LED::rougeIsole()
{                                       			/** ALLUMER ROUGE ET ETEINDRE LES AUTRES LED **/
    LED::Jaune(0);                    				//Eteindre LED jaune
    LED::Vert(0);                     				//Eteindre LED verte
    LED::Rouge(1);                     				//Allumer LED rouge
}

/*=========================================================*/ 

//FONCTION jaune()
void LED::jauneIsole()
{                                       			/** ALLUMER JAUNE ET ETEINDRE LES AUTRES LED **/
    LED::Rouge(0);                    				//Eteindre LED rouge
    LED::Vert(0);                     				//Eteindre LED verte
    LED::Jaune(1);                     				//Allumer LED jaune
}

/*=========================================================*/ 

//////// DESTRUCTEUR ////////

LED::~LED(){}