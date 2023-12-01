/**********************************************************************************************
 * Arduino SHIFT REGISTER - Version 1.0
 * by ikobootloader based on a sktech on https://retroetgeek.com
 *
 * License GPLv3
 **********************************************************************************************/
#include "Arduino.h"
#include "shift_register.h"

SHIFT_REGISTER::SHIFT_REGISTER(){}

void SHIFT_REGISTER::setupPins()
{
  pinMode(_pin_DS, OUTPUT);//Entrée de données en série
  pinMode(_pin_ST_CP, OUTPUT);//Goupille d'horloge du registre de stockage (goupille de verrouillage)
  pinMode(_pin_SH_CP, OUTPUT);//Broche d'horloge du registre à décalage
  effacerRegistres();// remise a 0 des registres
  ecrireRegistres();// on applique les valeurs au registre a decalage
}

void SHIFT_REGISTER::setupPins(const uint8_t ds,const uint8_t stcp,const uint8_t shcp) //TODO!
{
  pinMode(ds, OUTPUT);//Entrée de données en série
  pinMode(stcp, OUTPUT);//Goupille d'horloge du registre de stockage (goupille de verrouillage)
  pinMode(shcp, OUTPUT);//Broche d'horloge du registre à décalage
  effacerRegistres();// remise a 0 des registres
  ecrireRegistres();// on applique les valeurs au registre a decalage	
}

// Mettre toutes les valeurs a 0 pour le resigtre
void SHIFT_REGISTER::effacerRegistres()
{
  for(int x = _NbPins - 1; x >=  0; x--){
     registres[x] = LOW;
  }
} 

// enregistre une valeur pour un registre etat haut ou bas 
//set an individual pin HIGH or LOW
void SHIFT_REGISTER::pinRegistre(int index, int value)
{
  registres[index] = value;
}

// affectation des valeurs engregistrés dans le tableau "registres" et application (visualisation) des valeurs a la fin
void SHIFT_REGISTER::ecrireRegistres()
{
  digitalWrite(_pin_ST_CP, LOW); // Tant que LOW les modifications ne seront pas affectés
 // boucle pour affecter chaque pin des 74hc595
  for(int y = _NbPins - 1; y >=  0; y--)
  {
    digitalWrite(_pin_SH_CP, LOW);//doit etre a l'etat bas pour changer de colonne plus tard
    int val = registres[y];// recuperation de la valeur dans le tableau registres
    digitalWrite(_pin_DS, val);//affecte la valeur sur le pin DS correspondant a un pin du 74hc595
    digitalWrite(_pin_SH_CP, HIGH);//colonne suivante
  }
  digitalWrite(_pin_ST_CP, HIGH);//applique toutes les valeurs au 74hc595
} 
 
  /////// DESTRUCTEUR ///////
SHIFT_REGISTER::~SHIFT_REGISTER(){}