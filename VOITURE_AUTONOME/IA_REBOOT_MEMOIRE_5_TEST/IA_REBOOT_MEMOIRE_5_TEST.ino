/****************************************************
 * ROBOT AUTONOME - Version 1.2
 * 
 * ::SCORE::
 * La stratégie du robot pour s'adapter à son environnement est de tester différentes tactiques
 * Il y a 4 tactiques principales employées face à un obstacle :
 * AVANCER || RECULER || TOURNER A GAUCHE || TOURNER A DROITE
 * 
 * Lorsque la voiture s'approche d'un obstacle, elle teste la tactique
 * qui possède le meilleur score selon l'angle en cours de balayage par le servomoteur
 * Si la tactique permet au véhicule d'éviter l'obstacle, elle conserve son score à 3
 * Si la tactique ne permet pas au véhicule d'éviter l'obstacle,
 * d'autres tactiques sont testées. C'est la tactique qui permet au véhicule
 * d'éviter l'obtacle qui obtient un score égal un 3. Les autres scores sont diminués de 1.
 * le score le plus bas est zéro.
 * 
 * ::MEMORISATION::
 * Le parcours de la voiture est intégralement mémorisé.
 * Codification des coordonnnées : (voir en-tête de MEMORY.h)
 * La tactique qui permet à la voiture d'éviter un obstacle est mémorisée.
 * A posteriori, La tactique qui apparaît le plus souvent en mémoire,(celle qui a permis 
 * d'éviter un obstacle) modifie le score automatiquement : l'idée est qu'une stratégie  
 * d'évitement qui apparaît souvent en mémoire est probablement La meilleure stratégie.
 * Cette stratégie peut changer de valeur au gré des résultats des tests de la fonction score.
 * 
 * ::PARCOURS::
 * Le parcours étant intégralement sauvegardé en mémoire, la voiture 
 * peut détecter si une séquence d'actions est en train de se répéter. 
 * La détection s'effectue sur 3 actions actuellement
 * Le robot exécute le parcours et cela indéfiniment sauf si un obstacle apparaît.
 * 
 * ::AUTONOMIE::
 * Si la charge de la batterie devient faible, 
 * le robot peut s'alimenter en énergie automatiquement lorsqu'il trouve une bonne source de lumière.
 * 
 * 
 * by ikobootloader
 *
 * License GPLv3 
 ***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//CAPTEUR INFRAROUGE
#include <Infrarouge.h>
//Class    Objet
INFRAROUGE IR;
/***************************************************/
//FONCTIONS
#include <Fonctions.h>
//Class   Objet
FONCTIONS f;
/***************************************************/
//Intterupteur qui gère la mémorisation de l'action RECHARGE (7)  
bool MEMORISERrecharge = 0;     
/***************************************************/
//CAPTEUR A ULTRASON
#include <HCSR04.h>
const unsigned char trigPin = 13;
const unsigned char echoPin = 12;
//DISTANCE MAX AUTORISEE AVANT REACTION
const unsigned char maxDistance = 30; //30
UltraSonicDistanceSensor ultrason(trigPin, echoPin);
/***************************************************/
//CONTROLE DES MOTEURS
#include <Voiture.h>
//Class             Objet
VOITURE_CONTROLES   VOITURE; 
#define AVANCER VOITURE.locomotion(AVANCER,255)
#define RECULER VOITURE.locomotion(RECULER,255)
#define GAUCHE VOITURE.locomotion(GAUCHE,255)
#define DROITE VOITURE.locomotion(DROITE,255)
#define ARRET VOITURE.locomotion(ARRET,0)
/***************************************************/
//CONTROLE DU SERVOMOTEUR
//Servomoteur.h est esclave de la bibliothèque Servo.h
//Utilisation par défaut du PIN 9 de l'ARDUINO
//Angles de position prédéfinis 5,45,90,135,175
#include <Servomoteur.h>
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;
/***************************************************/
//MEMOIRE
#include <Memoire.h>
//Class   Objet
MEMOIRE   memo;
#include "MEMORY.h"
//Pour la création d'un cycle d'enregistrement en mémoire
bool seconde = 0;
/***************************************************/
//LED
#include <Led.h>
//Class  Ojbet
LED      led;
/***************************************************/
//SYSTEME DE SCORE
#include "SCORE.h"
/***************************************************/
//SYSTEME DE RECONNAISSANCE DE PARCOURS
#include "PARCOURS.h"
/***************************************************/
//Balayage de sécurité
unsigned char scanner = 0;
/***************************************************/
#include "DETECTION_ARRIERE.h"
/***************************************************/
//Tension
#include <Tension.h>
//Class  Ojbet
TENSION  BATTERIE,PPV;
/***************************************************/

void setup() 
{  
  iSet                                //Initialisation du Port Série (uniquement pour les tests)
  VOITURE.setupPins();                //Paramétrage par défaut des moteurs
  IR.setupInfra();                    //Activer capteur infrarouge (pin A1)
  servo.setupServo();                 //Paramétrage par défaut du servomoteur
  memo.setupWire();                   //Intialisation du port I2C pour l'EEPROM
  memo.effacer(0,500);                //Effacer 500 données dans l'EEPROM (à modifier selon la durée des tests) 
  delay(2000);                        //Délai avant l'activation du loop
  led.setupLED(A3,8,11);              //led.setupLED(rouge,jaune,vert);
}

void loop() 
{                                     //Moyenne de 136ms la boucle(l'affichage sur le port série et condtions de test donnent une valeur approximative)
                                      //TEST A SUPPRIMER 
                                      //lecture_capteur_tension_batterie();
                                      //lecture_capteur_tension_PPV();
                                      //delay(500);
                                      //memo.serial(0,50);
                                      //i("test")
/*=========================================================*/ 
  
                                      /** CREATION D'UN CYCLE D'ENREGISTREMENT EN MEMOIRE **/
                                      //Utilisation de la bibliothèque Fonctions.h et de l'objet f.frequence()
                                      //Ici, renvoie 1/TRUE à chaque seconde
  seconde = f.frequence(1000);        //Sinon renvoie 0/FALSE jusqu'à atteindre le terme fixé (ici 1000ms ou 1s)
                                      //TEST 
                                      //delay(500); i(seconde)   
                                      //Problème : la détection de la seconde peut varier. Semble ne pas être précis ?
                                      
                                      /** COMPTER JUSQU'A 100 ET REINITIALISER LE COMPTEUR f.compteurIntervalle **/
                                      //Utilisation de la bibliothèque Fonctions.h et de l'objet f.intervalle() et f.compteurIntervalle
  f.intervalle(seconde,100);          //f.compteurIntervalle cumule les 1/TRUE obtenus dans la variable 'seconde'
                                      //Lorsque le cumul atteint 100, f.compteurIntervalle est réinitialisé à 0
                                      //TEST 
                                      //delay(500); i(f.compteurIntervalle) 

                                      /** ENREGISTREMENT AUTO DE L'ACTION 'AVANCER' TOUTES LES 99 SECONDES SI L'ACTION N'EST PAS INTERROMPUE **/
                                      //Utilisation de la page MEMORY.h et de l'objet cycleMemoAuto()
 cycleMemoAuto(f.compteurIntervalle); //Si la voiture avance pendant 99 secondes ou  plus, la durée est mémorisée
                                      //TEST 
                                      //delay(500); i(f.compteurIntervalle) 
  
/*=========================================================*/

                                      /** CREATION D'UN OSCILLATEUR POUR LE SERVOMOTEUR **/
                                      //Le servomoteur (SVM) doit pouvoir effectuer une rotation en arc de cercle de gauche à droite puis de droite à gauche en continu
                                      //Utilisation de la bibliothèque Servomoteur.h et de l'objet servo.oscillateur()
                                      //servo.oscillateur() permet de générer un décompte infini qui croît de 0 à 4 puis décroît de 4 à 0
                                      //La position du décompte est stocké dans l'objet servo.amplitude (réduit ici au terme 'amplitude')
                                      //La valeur 120ms correspond à la vitesse du décompte, qui correspondra à la vitesse de rotation
                                      //Pour 50ms, il y a une propagation aller-retour du son sur presque 2 mètres
  servo.oscillateur(130);             //Création de l'oscillateur pour le servomoteur //120ms
                                      //TEST
                                      //i(amplitude)
                                      
                                      //Utilisation de la bibliothèque Servomoteur.h et de l'objet servo.balayage()
                                      //Servomoteur.h agit sur le SVM en le positionnant selon la valeur de l'objet 'amplitude'
  servo.balayage(amplitude);          //Balayage du servomoteur
  
/*=========================================================*/ 

                                      /** DETECTION DES OBSTACLES ET APPRENTISSAGE **/
                                      //Le robot doit pouvoir apprendre à éviter les obstacles
                                      //Il existe 2 niveaux d'apprentissage :
                                      //1-une matrice de capture de tactiques d'évitement (matriceSCORE) est mise à jour en temps réel lorsque le robot détecte et évite un obstacle 
                                      //2-la tactique d'évitement suivi de l'angle du SVM sont conservés en mémoire. 
                                      //Après une vérification automatique de la mémoire, si une tactique domine pour un angle, la matrice sera modifiée en conséquence avant les tests de tactiques d'évitement 
                                      //TEST
                                      //i("Vérification du score avant test")
                                      //verificationScore(amplitude);       
  if(ultrason.measureDistanceCm() >= 0 && ultrason.measureDistanceCm() <= maxDistance)
  {                                   //Si un obstacle est détecté par le capteur à ultrason
                                      //ultrason.measureDistanceCm() est un objet de la bibliothèque HCSR04.h
                                      //La détection s'échelonne de 0 à 20cm (dépend de la valeur maxDistance)
                                      //Note: lorsque la distance est très grande, le capteur HCSR04 peut renvoyer la valeur 0
                                      //TODO: créer une unique fonction pour cette partie détection et apprentissage

                                      //GESTION DES VOYANTS A LA DETECTION D'UN OBSTACLE
                                      //led.rougeIsole() est un objet de la bibliothèque Led.h
    led.rougeIsole();                 //Allumer LED rouge et éteindre les autres

                                      //souvenirScore() est une fonction de la page SCORE.h
    souvenirScore(amplitude);         //Identifier en mémoire la tactique d'évitement récurrente en fonction de l'angle balayé
                                      //Réinitialise le tableau matriceSCORE et intègre la valeur trouvée (si NULL, conserve la valeur disponible dans matriceSCORE)
                                      //TEST
                                      //verificationScore(amplitude);

                                      //score() est une fonction de la page SCORE.h
    score(amplitude);                 //Teste les tactiques d'évitement et attribue un point à l'une d'elle si l'obstacle est évité

                                      //A l'issu des tests, le robot ne bouge plus
                                      //TODO: supprimer ce type de variables SOLITAIRES => créer une page 'sécurité' ? ou 'mouvement"
    scanner = 10;                     //Activation d'un balayage du servomoteur sur 10 positions   

    curseurMemoire = 0;               //Réinitialiser le compteur/pointeur de la fonction executionParcours() en cas de détection d'obstacle
    
  }
                                      //TEST
                                      //i("Vérification du score après test")                                      
                                      //verificationScore(amplitude);
                                      
/*=========================================================*/

                                      /** SECURITE AVANT REPRISE DE LA MARCHE NORMALE **/
                                      //Si la variable 'scanner' est à 10, le servomoteur effectue une rotation sur 10 positions
                                      //La valeur de scanner diminue de 1 à chaque loop
                                      //Le robot est à l'arrêt
                                      //Réinitialisation du compteur f.compteurIntervalle
                                      //TEST
                                      //i("Balayage de sécurité")                                      
                                      //i(scanner)
  if(scanner != 0 && scanner <= 10){scanner--;f.compteurIntervalle = 0;}
                                    
  if(scanner == 0 && memoParcours() != 1 && IR.detection() == false)
  {                                   //Si le servomoteur a effectué une rotation sur 10 positions (variable 'scanner' à 0)
                                      //Ou si la variable 'scanner' est à 0
                                      //Et que la fonction memoParcours() renvoie false (pas de détection d'une séquence de déplacement répétitive)
                                      //Et que la fonction detectionArriere() renvoie false (pas de détection d'obstacle sur la face arrière)   
    led.vertIsole();                  //Allumer LED verte
                                      
                                      /** RECHARGE **/
                                      /**
                                      Principe : la tension augmente proportionellement à l'intensité 
                                      de l'exposition lumineuse de la plaque PV. 
                                      Du coup, il suffit d'utiliser un capteur de tension pour évaluer 
                                      l'intensité lumineuse. 
                                      **/                                     
                                      //TODO: mettre ce programme dans une fonction dans la page RECHARGE.h (?)                                                                    
    if(BATTERIE.tensionAcomparer(7.5, A2, 0) == false) 
    {                                 //Si la tension de la batterie est <= 7.5v 
      if(PPV.tensionAcomparer(8, A0, 0) == true) 
      {                               //Si la tension émise par la PPV est assez élevée
        f.compteurIntervalle = 0;     //Réinitialiser f.compteurIntervalle
        ARRET;                        //Le robot s'arrête pour que la batterie se recharge        
      }else
      {                               //Sinon, le robot avance ou explore son environnement
                                      //Ici, on ne cherche pas à itérer un parcours de recharge car celui-ci n'a pas permis de trouver une bonne source lumineuse
        AVANCER;                      //Marche normale
                                      //TODO: intégrer un mode 'exploration' pour le cas où la tension de la batterie est faible et que la PPV n'émet pas de tension assez forte
      }
                                      //Note: si la luminosité n'est pas stable, la voiture va faire des micro-mouvements d'avance et d'arrêt et il y a risque de mémorisations intempestives!
                                      //Par ailleurs, on ne sait pas si le robot finira par trouver un emplacement stable à court terme
                                      //Solution: mémoriser lorsque la batterie est pleine (là encore la tension de la batterie peut varier mais ça peut se gérer avec un interrupteur)
      MEMORISERrecharge = 0;          //Interrupteur de mémorisation
                                      //La recharge n'est pas sauvegardée en mémoire si la batterie n'atteint pas 8.5v
                                      
    }else if(BATTERIE.tensionAcomparer(8.5, A2, 0) == true && MEMORISERrecharge != 1) 
    {                                 //Si la batterie  à une charge supérieure ou égale à 8.5v
      memo.ecrire(7);                 //Mémorisation de l'action RECHARGE 
      MEMORISERrecharge = 1;          //Interrupteur de mémorisation
    }else
    {                                 /** EXECUTION PARCOURS RECONNU **/
                                      //La marche normale, c'est avancer!
      if(memoParcoursRECHARGE() == true)
      {                               //Si parcours de recharge existe en mémoire, exécuter le parcours (fonction executionParcours() intégrée dans PARCOURS.h)
        executionParcours(0);         //Répéter parcours qui mène à la recharge       
      }else if(memoParcours() == true)
      {                               //Si le robot détecte un parcours
        executionParcours(1);         //Répéter parcours reconnu 
      }else
      {                               //Sinon, le robot avance
        AVANCER;
      }
                                   
    }
    
  }
                                  
/*=========================================================*/

  detectionARRIERE(IR.detection());

/*=========================================================*/  

}
