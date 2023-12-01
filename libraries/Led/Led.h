#ifndef LED_H
#define LED_H

#include "Arduino.h"
class LED{

  public:
  
	LED();
	~LED();
	
	//
	void LED::setupLED(unsigned char,unsigned char,unsigned char);
	void LED::Rouge(bool);
	void LED::rougeIsole();
	void LED::Vert(bool);
	void LED::vertIsole();
	void LED::Jaune(bool);
	void LED::jauneIsole();
	
   private :
	
	unsigned char _ledRouge;	
	unsigned char _ledJaune;
	unsigned char _ledVert;
};

#endif