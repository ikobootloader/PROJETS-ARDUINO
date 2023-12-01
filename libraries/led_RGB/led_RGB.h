#ifndef led_RGB_H
#define led_RGB_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE D'UNE LED RGB
* 
*/

class led_RGB{
	
	public:	
	
		led_RGB();
		~led_RGB();
		void setupColorsPins();
		void setupColorsPins(const uint8_t ,const uint8_t ,const uint8_t);
		void couleur(uint8_t, uint8_t, uint8_t);
		void palette(uint8_t, uint8_t);
	
		uint8_t redPin = 255;
		uint8_t greenPin = 255;
		uint8_t bluePin = 255;

	private:
		//DEFAULT PINS
		const uint8_t _redPin = 4;
		const uint8_t _greenPin = 3;
		const uint8_t _bluePin = 2;
		
};

enum couleurs{
	BLANC,
	ROUGE,
	VERT,
	BLEU,
	MAGENTA,
	CYAN,
	JAUNE
};

#endif