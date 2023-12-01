/**********************************************************************************************
 * Arduino CAPTEUR DE VITESSE - LM393 - Version 1.1
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/

#include "Arduino.h"
#include "capteur_vitesse.h"

CAPTEUR_VITESSE::CAPTEUR_VITESSE(){}

void CAPTEUR_VITESSE::setupPins()
{
  pinMode(CapteurVitesse1, INPUT);    //Capteur Vitesse 1
  pinMode(CapteurVitesse2, INPUT);    //Capteur Vitesse 2
}

void CAPTEUR_VITESSE::setupPins(const unsigned char pin1,const unsigned char pin2)
{
  pinMode(pin1, INPUT);    //Capteur Vitesse 1
  pinMode(pin2, INPUT);    //Capteur Vitesse 2
}

//Capteur Vitesse Roue
bool CAPTEUR_VITESSE::cvr(uint8_t lectureCapteur, uint8_t tpsAvReset, uint8_t variation){
  //TODO:tenir compte de la batterie!
  //Si l'utilisateur entre une valeur supérieure ou inférieure à un octet
  tpsAvReset > 255 || tpsAvReset <= 0 ? tpsAvReset == 255 : tpsAvReset; 
  fin = tpsAvReset;//Fin du comptage de loop définit par l'utilisateur
  //Si le nombre de loop inf au nombre de loop définit par l'utilisateur
  if(boucles <= fin){ 
    etatSvnt = analogRead(lectureCapteur); //Capteur de vitesse valeur 0 ou 1
    //Si l'état précédent est différent de l'état suivant (détection obstacle ou trou)
    if(etatPrcdnt  != etatSvnt){ 
      etatPrcdnt = etatSvnt; // état suivant devient état précédent
      detections++; // incrément des détections
    }  
    boucles++; //Loop++ 
  }

  if(boucles == fin){ 
    //Vérifer les variations de vitesse
    if(memorisationDetections == 0){memorisationDetections=1;}//protection à la division par 0
    comparatifDetections = (detections/memorisationDetections)*100; //Différence en  pourcent avec détection du quota loop -1 
    memorisationDetections = detections; //Mémorisation des détections pour comparatif
    //RESET
    detections = 0;
    boucles=0;
    return (comparatifDetections > variation);//Si comparatifDetections <= seuil définit par l'utilisateur
  }
}

  /////// DESTRUCTEUR ///////
CAPTEUR_VITESSE::~CAPTEUR_VITESSE(){}