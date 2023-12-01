#include <Memoire.h>

//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);

//Class   Objet
MEMOIRE   memo;

void setup() {

  //SETUP DU PORT SERIE
  iSet
  //SETUP DE WIRE
  //Peut être entré manuellement ou à l'aide de cette méthode 
  memo.setupWire();
  //TEST
  /*memo.ecrire(0,255);
    memo.ecrire(1,255);
    memo.ecrire(2,255);
    memo.ecrire(3,255);
    memo.ecrire(4,255);
    memo.ecrire(5,255);
  */
}

void loop() {
  
  //RESET
  //memo.effacer(adresse de départ,adresse d'arrivée);
  
  //ECRIRE
  //memo.ecrire(adresse,donnée);

  //LIRE UNE ADRESSE
  //memo.lire(0);

  //AFFICHER SUR LE PORT SERIE
  //memo.serial(0,5);
  
  //ADRESSAGE AUTOMATIQUE DE LA DONNEE
  //memo.ecrire(0);

}
