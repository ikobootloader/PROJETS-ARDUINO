#ifndef MEMOIRE_H
#define MEMOIRE_H

#include "Arduino.h"

/* 
* 
* OUTILS POUR LE CONTROLE DE L'EEPROM 24LC256
* 
*/

class MEMOIRE{

  public:

	MEMOIRE();
	~MEMOIRE();
	void setupWire();
	static int increment;
	void ecrire(int, unsigned char);
	void ecrire(unsigned char);
	unsigned char lire(int);
	int serial(int, int);
	void effacer(int, int);	
	//Pointer sur intervalle d'adresses
	static unsigned int adresseEepromMin;
	static unsigned int adresseEepromMax;
	static unsigned int qteAdresses;
	void pointer(const unsigned int);
        
};


#endif