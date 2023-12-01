#ifndef CAPTEUR_VITESSE_H
#define CAPTEUR_VITESSE_H

#include "Arduino.h"

/* 
* 
* Lecteur de vitesse
* 
*/

class CAPTEUR_VITESSE{

  public:

	CAPTEUR_VITESSE();
	~CAPTEUR_VITESSE();

	//CAPTEUR DE VITESSE DES MOTEURS
	uint8_t fin = 0;//Fin comptage
	uint8_t etatSvnt = 0;//Etat suivant
	uint8_t etatPrcdnt = 0;//Etat précédent
	double detections = 0;//Détection
	uint8_t boucles = 0;//Comptage de loop
	long memorisationDetections = 0;
	double comparatifDetections = 0;
	cvr(uint8_t, uint8_t, uint8_t);


  private:
	//SETUP
	const uint8_t CapteurVitesse1 = 6;
	const uint8_t CapteurVitesse2 = 7;
	const uint8_t NbLoop = 20;
	const uint8_t pour100DiffMax = 75;		

};

#endif