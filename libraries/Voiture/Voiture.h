#ifndef VOITURE_H
#define VOITURE_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE DES MOTEURS RELIES AU L298N / L293D
* 
*/

class VOITURE_CONTROLES{

  public:

	VOITURE_CONTROLES();
	~VOITURE_CONTROLES();
	void setupPins();
	void setupPins(const unsigned char ,const unsigned char ,const unsigned char ,const unsigned char ,const unsigned char ,const unsigned char );
	void locomotion(unsigned char ,unsigned char );
	
	unsigned char enAPin = 255;
	unsigned char in1Pin = 255;
	unsigned char in2Pin = 255;
	unsigned char in3Pin = 255;
	unsigned char in4Pin = 255;
	unsigned char enBPin = 255;

  private:
	
	const unsigned char _enAPin = 6; // Contrôle de vitesse PWM du moteur gauche
	const unsigned char _in1Pin = 7; // Moteur gauche Direction 1
	const unsigned char _in2Pin = 5; // Moteur gauche Direction 2
	const unsigned char _in3Pin = 4; // Moteur droit Direction 1
	const unsigned char _in4Pin = 2; // Moteur droit Direction 2
	const unsigned char _enBPin = 3; // Contrôle de vitesse PWM du moteur droit
									 // enBPin sur VCC
									 // VCC sur 12V
	const unsigned char _tabActions[5][4] = {{1,0,1,0},{0,1,0,1},{0,1,1,0},{1,0,0,1},{1,1,1,1}}; // Matrice d'actions
        
};

enum actions{
	AVANCER,
	RECULER,
	GAUCHE,
	DROITE,
	ARRET
};

#endif