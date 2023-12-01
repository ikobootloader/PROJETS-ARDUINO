/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//CONTROLE LED RGB
#include <led_RGB.h>
//Class   Ojbet
led_RGB   led;

void setup() {
  //iSet                        //Initialisation du Port Série (uniquement pour les tests)
  led.setupColorsPins();      //Initialisation de la led RGB
}

void loop() {
  //Créer la couleur - intensité de 0 à 255
  //led.couleur(255,255,255);
  //Utiliser une couleur existante - intensité de 0 à 255
  //0:blanc;1:rouge;2:vert;3:bleu;4:magenta;5:cyan;6:jaune
  //led.palette(4,255);
  //VARIANTE Utiliser une couleur existante - intensité de 0 à 255
  led.palette(CYAN,255);
}
