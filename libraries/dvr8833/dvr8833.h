#ifndef dvr8833_H
#define dvr8833_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE DE 2 MOTEURS CC RELIES AU DVR8833
* 
*/

class DVR8833{
	
	public:	
	
		DVR8833();
		~DVR8833();
		void setupPins();
		void setupPins(const uint8_t ,const uint8_t ,const uint8_t ,const uint8_t);
		void drive(uint8_t);
		void driveSpeed(uint8_t, uint8_t);
	
		uint8_t in1Pin = 255;
		uint8_t in2Pin = 255;
		uint8_t in3Pin = 255;
		uint8_t in4Pin = 255;

	private:
	
		const uint8_t _in1Pin = 5;
		const uint8_t _in2Pin = 4;
		const uint8_t _in3Pin = 3;
		const uint8_t _in4Pin = 2;
		//ARRAY = GAUCHE;DROITE;RECUL;AVANT;ARRET
		uint8_t _tabDrive[5][4] = {{255,0,255,0},{0,255,0,255},{0,255,255,0},{255,0,0,255},{0,0,0,0}}; // Matrice d'actions
		
};

enum actions{
	GAUCHE,
	DROITE,
	RECULER,
	AVANCER,
	ARRET
};

#endif