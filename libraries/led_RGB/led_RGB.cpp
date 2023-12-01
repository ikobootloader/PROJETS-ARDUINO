/*********************************************************************************************
 * Arduino LED RGB TOOLS - Version 1
 * by ikobootloader
 *
 * License GPLv3
 *********************************************************************************************/
 
#include "Arduino.h"
#include "led_RGB.h"

led_RGB::led_RGB(){}

void led_RGB::setupColorsPins()
{//Paramètres des pins par défaut
   pinMode(_redPin, OUTPUT);
   pinMode(_greenPin, OUTPUT);
   pinMode(_bluePin, OUTPUT);
}

void led_RGB::setupColorsPins(const uint8_t in1Pin,const uint8_t in2Pin,const uint8_t in3Pin)
{//Paramètres des pins entrés par l'utilisateur	
   pinMode(in1Pin, OUTPUT);
   pinMode(in2Pin, OUTPUT);
   pinMode(in3Pin, OUTPUT);
   
   this->redPin = in1Pin;
   this->greenPin = in2Pin;
   this->bluePin = in3Pin;
}

void led_RGB::couleur(uint8_t r, uint8_t v, uint8_t b)
{ //Intensité de la couleur de 0 à 255
  analogWrite(this->redPin != 255 ? this->redPin : _redPin, r);
  analogWrite(this->greenPin != 255 ? this->greenPin : _greenPin, v);
  analogWrite(this->bluePin != 255 ? this->bluePin : _bluePin, b);

} 

void led_RGB::palette(uint8_t melange, uint8_t intensite)
{ //Mélange des couleurs, gestion de l'intensité
  intensite < 0 || intensite >255 ? intensite = 255 : intensite;
  switch(melange)
  {
    case 0 : couleur(intensite,intensite,intensite); //BLANC
    break;
    case 1 : couleur(intensite,0,0); //ROUGE
    break;
    case 2 : couleur(0,intensite,0); //VERT
    break;   
    case 3 : couleur(0,0,intensite); //BLEU
    break;  
    case 4 : couleur(intensite,0,intensite); //MAGENTA
    break; 
    case 5 : couleur(0,intensite,intensite); //CYAN
    break; 
    case 6 : couleur(intensite,intensite,0); //JAUNE
    break; 
    default : couleur(intensite,intensite,intensite); //BLANC 
  }
}	

led_RGB::~led_RGB(){}