/**********************************************************************************************
 * Arduino LASER RANGEFINDER - Version 1
 * by ikobootloader - based on a sketch from www.SurtrTech.com 
 * TOF10120 Rangefinder Laser Reader
 *
 * License GPLv3
 **********************************************************************************************/
 
#include "Arduino.h"
#include <Wire.h>
#include "Laser_rangefinder.h"

LASER_RANGEFINDER::LASER_RANGEFINDER(){}

void LASER_RANGEFINDER::setupWire(){
  // INITIALISATION I2C
  Wire.begin(); //NE PAS UTILISER SI DEJA APPELE PAR UN AUTRE SCRIPT !
}

const byte LASER_RANGEFINDER::TOF10120adress = 0x52; //Adresse du module 0x52
const uint8_t LASER_RANGEFINDER::waiting = 1;
unsigned short LASER_RANGEFINDER::size = 0;

int LASER_RANGEFINDER::Reading(){
  wireReader(LASER_RANGEFINDER::TOF10120adress,LASER_RANGEFINDER::waiting,LASER_RANGEFINDER::bufferReception,2);
  LASER_RANGEFINDER::size = this->bufferReception[0];
  LASER_RANGEFINDER::size = LASER_RANGEFINDER::size<<8;
  LASER_RANGEFINDER::size |= this->bufferReception[1];
  delayMicroseconds(10);
  return size;
}

void LASER_RANGEFINDER::wireReader(uint8_t adressMod, uint8_t wait, uint8_t *stockData, uint8_t NbDataToReceive)
{
  Wire.beginTransmission(adressMod); //Communiquer avec le module
  Wire.write(byte(0x00)); //Acknowledge
  Wire.endTransmission();
  delay(wait);
  Wire.requestFrom(adressMod, NbDataToReceive);//Effectuer une requête de lecture 
  //
  if(NbDataToReceive <= Wire.available()){
    *stockData++ = Wire.read();
    *stockData++ = Wire.read();
  } 
}

//////// DESTRUCTEUR ////////

LASER_RANGEFINDER::~LASER_RANGEFINDER(){}