#ifndef config_H
#define config_H
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(115200);
#define i(texte) Serial.println(texte);
/***************************************************/
//REGISTRE A DECALAGE
#include <shift_register.h>
//Class          Objet
SHIFT_REGISTER   reg;
/***************************************************/
//CONTROLER LED RGB
void couleurs(uint8_t couleur){
  switch(couleur)
  {
    case 0 :reg.pinRegistre(1, HIGH);reg.pinRegistre(2, HIGH);reg.pinRegistre(3, HIGH); //BLANC
    break;
    case 1 :reg.pinRegistre(1, HIGH);reg.pinRegistre(2, LOW);reg.pinRegistre(3, LOW); //ROUGE
    break;
    case 2 :reg.pinRegistre(1, LOW);reg.pinRegistre(2, HIGH);reg.pinRegistre(3, LOW); //VERT
    break;   
    case 3 :reg.pinRegistre(1, LOW);reg.pinRegistre(2, LOW);reg.pinRegistre(3, HIGH); //BLEU
    break;  
    case 4 :reg.pinRegistre(1, HIGH);reg.pinRegistre(2, LOW);reg.pinRegistre(3, HIGH); //MAGENTA
    break; 
    case 5 :reg.pinRegistre(1, LOW);reg.pinRegistre(2, HIGH);reg.pinRegistre(3, HIGH); //CYAN
    break; 
    case 6 :reg.pinRegistre(1, HIGH);reg.pinRegistre(2, HIGH);reg.pinRegistre(3, LOW); //JAUNE
    break; 
    default :reg.pinRegistre(1, HIGH);reg.pinRegistre(2, HIGH);reg.pinRegistre(3, HIGH); //BLANC 
  }

  reg.ecrireRegistres(); // appelle la fonction pour appliquer les valeurs
}
/***************************************************/
//CONTROLE DES MOTEURS
#include <dvr8833.h>
//Class    Objet
DVR8833    voiture;
#define AVANCER voiture.drive(AVANCER)
#define RECULER voiture.drive(RECULER)
#define GAUCHE voiture.drive(GAUCHE)
#define DROITE voiture.drive(DROITE)
#define ARRET voiture.drive(ARRET)
/***************************************************/
//CONTROLE DU TELEMETRE LASER TOF10120
#include <Laser_rangefinder.h>
//Class             Ojbet
LASER_RANGEFINDER   laser;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned short maxDistance = 250; //300mm
/***************************************************/
//CONTROLE DU SERVOMOTEUR SG90
//Servomoteur.h est esclave de la bibliothèque Servo.h
//Utilisation par défaut du PIN 9 de l'ARDUINO
//Angles de position prédéfinis 5,45,90,135,175
#include <Servomoteur.h>
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;
/***************************************************/
//REACTIONS
void reactions(){
      ARRET; delay(300);
      switch(amplitude)
      {
        case 0 : DROITE; //5°
        break;
        case 1 : DROITE; //45°
        break;
        case 2 : GAUCHE; //90°
        break;
        case 3 : GAUCHE; //135°
        break;   
        case 4 : GAUCHE; //175°
        break;     
        default : AVANCER;
      }
    }
/***************************************************/
//  REFLLEXES
void reflexes(){
    ARRET,delay(300);
    RECULER,delay(200);
    GAUCHE,delay(200);
}
/***************************************************/
//CAPTEUR DE PERCUSSION KY-027
#define KY027 A0
//ACTIVER LED CAPTEUR DE PERCUSSION KY-027
void ledKY027(bool etat){
  reg.pinRegistre(4, etat);
  reg.ecrireRegistres(); // appelle la fonction pour appliquer les valeurs
}
//Si choc, recul d'urgence
void choc(){
  bool percussion = digitalRead(KY027);
  ledKY027(LOW);//LED du capteur OFF
  if(!percussion){
    ledKY027(HIGH);//LED du capteur ON
    reflexes();
  }
}
/***************************************************/
//TENSION
#include <Tension.h>
#define tension A1
//Class  Ojbet
TENSION  pile;
//ETAT DE LA BATTERIE
void etatBatterie(float pinTension){
  pile.lecture_tension(pinTension) < 5 ? couleurs(6) : couleurs(0);
}
/***************************************************/
//CAPTEUR DE VITESSE DE ROUES
#include <capteur_vitesse.h>
//Class          Ojbet
CAPTEUR_VITESSE  cv;
#define NbLoop 20
#define pour100DiffMax 75
//
void vitesseRoues(bool etatVitesse1, bool etatVitesse2){
  if(!etatVitesse1 || !etatVitesse2){
    //reflexes(); 
    couleurs(1);
  }
}
/***************************************************/
//CAPTEURS INFRAROUGES ARRIERES
//=>Sensibles aux moteurs actifs ??
#include<Infrarouge.h>
//Class          Ojbet
INFRAROUGE       inf1,inf2;
#define infrarouge1 A2
#define infrarouge2 A3
void infraDetection(){
  if(inf1.detection()&&!inf2.detection())GAUCHE;
  else if(inf2.detection()&&!inf1.detection())DROITE,delay(200);
  else if(inf2.detection()&&inf1.detection())AVANCER,delay(200);
}
/***************************************************/
#endif