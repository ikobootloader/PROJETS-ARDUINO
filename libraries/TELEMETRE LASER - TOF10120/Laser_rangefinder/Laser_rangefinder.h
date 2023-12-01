#ifndef LASER_RANGEFINDER_H
#define LASER_RANGEFINDER_H

#include "Arduino.h"
class LASER_RANGEFINDER{
	
	public:
	
		LASER_RANGEFINDER();
		~LASER_RANGEFINDER();
		
		static const byte TOF10120adress; //Adresse du module 0x52 
		uint8_t bufferReception[16];
		static const uint8_t waiting;
		static unsigned short size;
		
		void setupWire();
		int Reading();
		void wireReader(uint8_t, uint8_t, uint8_t *, uint8_t);
	
};

#endif