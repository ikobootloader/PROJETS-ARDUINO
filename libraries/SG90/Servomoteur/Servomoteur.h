#ifndef SERVOMOTEUR_H
#define SERVOMOTEUR_H

#include "Arduino.h"
#include <Servo.h>

/* 
* 
* OUTILS POUR LE CONTROLE DU SERVOMOTEUR SG90
* 
*/

class SERVOMOTEUR : public Servo{

  public:
		SERVOMOTEUR();
		~SERVOMOTEUR();	
		
		//SETUP
		void setupServo();
		void setupServo(const unsigned char);
		void setupServo(const unsigned char, unsigned char);
		//FONCTIONS
		unsigned char tabAngles[5] = {0xFF,0xFF,0xFF,0xFF,0xFF};//byte
		unsigned char angles(const unsigned char,const unsigned char,const unsigned char,const unsigned char,const unsigned char);//Matrice d'angles créée par l'utilisateur
		static signed char qt;
		static signed char amplitude; //Compteur/Amplitude
		static bool etat; //Booleen
		unsigned char oscillateur(int); //Oscillation
		int balayage(unsigned char);//Balayage en fonction de _tabAngles

  private: 
		const unsigned char _servoPin = 9;
		const unsigned char _tabAngles[5] = {5,45,90,135,175}; //Matrice d'angles par défaut
};


#endif