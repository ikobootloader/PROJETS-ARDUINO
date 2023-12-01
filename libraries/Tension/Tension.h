#ifndef TENSION_H
#define TENSION_H

#include "Arduino.h"

class TENSION {

	public:
		TENSION();
		~TENSION();	
		float lecture_tension(unsigned char);
		bool tensionAcomparer(float, unsigned char, unsigned char);
		
	private:
		// fiabilité à 0.04v près
		const float _voltage = 4.3;
		const float _R1 = 30000;
		const float _R2 = 7500;

};

#endif