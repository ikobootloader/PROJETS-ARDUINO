#ifndef INFRAROUGE_H
#define INFRAROUGE_H

#include "Arduino.h"

class INFRAROUGE {

 public:
		INFRAROUGE();
		~INFRAROUGE();
		unsigned char infra = 0;
		void setupInfra();
		void setupInfra(unsigned char);
		bool detection();
				
 private:	
		const unsigned char _infra = A1;  //ANALOG A1 UTILISE PAR DEFAUT

};

#endif