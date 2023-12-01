/**********************************************************************************************
 * Arduino EEPROM 24LC256 TOOLS - Version 2
 * by ikobootloader
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include <Wire.h>
#include "Memoire.h"

//Avec l'aide de https://www.instructables.com/Reading-and-Writing-data-to-External-EEPROM-Using-/
//La licence publique générale GPLv3 est revendiquée pour ce script
//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////

//0x50 || 0x58 => adresse de la puce 24LC256
//80   || 88

int MEMOIRE::increment = 0;

MEMOIRE::MEMOIRE(){}

void MEMOIRE::setupWire(){
  // INITIALISATION I2C
  Wire.begin();
  Wire.setClock(400000); //https://www.arduino.cc/en/Reference/WireSetClock >> Fréquence supportée par la puce
}

// ECRIRE
void MEMOIRE::ecrire(int adresseEeprom, unsigned char donnee) 
{
	//éviter les réécritures inutiles !
	if(lire(adresseEeprom) != donnee){
		  Wire.beginTransmission(0x50); // Adresse du périphérique (https://zestedesavoir.com/billets/1824/scanner-i2c-pour-arduino/)
		  Wire.write((int)(adresseEeprom >> 8));   // MSB => Décalage sur 8 bits ?
		  Wire.write((int)(adresseEeprom & 0xFF)); // LSB => Ecriture sur 1 octet ?
		  Wire.write(donnee);
		  Wire.endTransmission(); 
		  delay(5);
	 }
}

// ECRIRE AVEC ADRESSAGE AUTOMATIQUE A PARTIR DU COMPTEUR MEMOIRE::increment
void MEMOIRE::ecrire(unsigned char donnee) 
{
	if(lire(MEMOIRE::increment) != donnee){
		ecrire(MEMOIRE::increment,donnee);
		MEMOIRE::increment++;
	}
}

// LIRE UNE ADRESSE
unsigned char MEMOIRE::lire(int adresseEeprom) 
{
  byte retourneDonnee = 0xFF; // Par défaut retourneDonnee est à 255
  Wire.beginTransmission(0x50);	// Adresse du périphérique (https://zestedesavoir.com/billets/1824/scanner-i2c-pour-arduino/)
  Wire.write((int)(adresseEeprom >> 8));   // MSB => Décalage sur 8 bits ?
  Wire.write((int)(adresseEeprom & 0xFF)); // LSB => Lecture sur 1 octet ?
  Wire.endTransmission();
 
  Wire.requestFrom(0x50,1); // Reception d'un octet
 
  if (Wire.available()) retourneDonnee = Wire.read(); // lecture si disponible
 
  return retourneDonnee;
}

//LIRE PLAGE D'ADRESSES SUR PORT SERIE
int MEMOIRE::serial(int adresseEepromDebut, int adresseEepromFin)
{
	for(int r = adresseEepromDebut; r <= adresseEepromFin; r++){
		Serial.println(lire(r));
	}
}

// RESET EEPROM
// 24LC256 >> 32767 adressees
void MEMOIRE::effacer(int x, int y){
  for(short int r = x; r <= y ;r++){
	if(lire(r) != 255){ecrire(r,255);}
  }
}

//Définir pointeurs sur une adresse de début et une adresse de fin
//selon intervalle définit par l'utilisateur
static unsigned int MEMOIRE::adresseEepromMin = 0;
static unsigned int MEMOIRE::adresseEepromMax = 0;
static unsigned int MEMOIRE::qteAdresses = 0;
void MEMOIRE::pointer(const unsigned int qteATraiter)
{
  MEMOIRE::adresseEepromMin = MEMOIRE::increment - qteATraiter;
  MEMOIRE::adresseEepromMax = MEMOIRE::adresseEepromMin + qteATraiter; 
  
  if(MEMOIRE::increment <= qteATraiter){
    MEMOIRE::adresseEepromMin = 0;
    MEMOIRE::adresseEepromMax = MEMOIRE::increment;
  }
  
  MEMOIRE::qteAdresses = MEMOIRE::adresseEepromMax - MEMOIRE::adresseEepromMin;
}

//TODO: fonction qui récupère l'adresse la plus récente pour un type de donnée

MEMOIRE::~MEMOIRE(){}
