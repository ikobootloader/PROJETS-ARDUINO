#ifndef SHIFT_REGISTER_H
#define SHIFT_REGISTER_H

#include "Arduino.h"

class SHIFT_REGISTER {

	public:
		SHIFT_REGISTER(uint8_t);
		SHIFT_REGISTER();
		~SHIFT_REGISTER();	
		void setupPins();
		void setupPins(const uint8_t ,const uint8_t ,const uint8_t );		
		
		uint8_t pin_DS = 8;  
		uint8_t pin_ST_CP = 10;
		uint8_t pin_SH_CP = 11;
		uint8_t Nb74hc595 = 1; // Nombre de registre a decalage utilise
		uint8_t NbPins = 8; // Nombre total de pin de registre a decalage
		boolean *registres; // Array contenant des bits de la taille du nombre de pin 74hc595
		
		void effacerRegistres();
		void pinRegistre(int, int);
		void ecrireRegistres();
		
	private:
		const uint8_t _pin_DS = 8;   
		const uint8_t _pin_ST_CP = 10;
		const uint8_t _pin_SH_CP = 11;
		const uint8_t _Nb74hc595 = 1;
		const uint8_t _NbPins = 8;

};

#endif