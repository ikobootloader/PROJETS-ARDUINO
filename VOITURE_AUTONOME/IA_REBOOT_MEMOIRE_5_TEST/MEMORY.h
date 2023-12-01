#ifndef MEMORY_H
#define MEMORY_H

//////////////////
// 24LC256 >> ARDUINO
// WP | A0 | A1 | A2 >> GND 
// VCC >> 5V
// SCL >> A5
// SDA >> A4
// GND >> GND
//////////////////
/*
 * SYSTEME DE MEMORISATION SPECIFIQUE A L'AGENT
 * 0 à 4 > 5 angles > ex: 5,45,90,135,175
 * 0 à 4 en mémorisation 
 * 1 à 4 > 4 actions > avancer, reculer, gauche, droite
 * 1 à 4 en mémorisation 
 * Mémorisations : 
 * - action avancer + secondes écoulées ex: 1 suivi de 10 (pour 10 econdes) = memorisé 110
 * - action reculer ou gauche ou droite + angle ex: 3 suivi de 4 (correspondance : GAUCHE suivi de 175°) = 34
 * - action reflexe code 5 (si test score non réussi)
 * - action détection arrière code 6
 * - action recharge code 7
 * 
 */

/*=========================================================*/ 

                                                            /** ENREGISTREMENT AUTO DE LA TACTIQUE 'AVANCER' TOUTES LES 100 SECONDES SI L'ACTION N'EST PAS INTERROMPUE **/
                                                            //Par défaut, la voiture avance
                                                            //Si la voiture avance pendant 100 secondes, la durée est mémorisée

//INIT VARIABLE(S)
const unsigned char compteurMemoMax = 99;                   //Réglée à 99
const unsigned char AVANCERetSecondes = 199;                //AVANCER (1) suivi de 99 (secondes) 

                                                            //Mémorisation automatique toutes les 99 secondes
                                                            //FONCTION cycleMemoAuto(f.compteurIntervalle)
void cycleMemoAuto(unsigned char OBJETcompteurIntervalle)
{      

  static bool stopEcriture = 0;                             //Interrupteur qui permet de ne pas mémoriser plusieurs fois de suite
  if(OBJETcompteurIntervalle >= compteurMemoMax && stopEcriture != 1)
  {                                                         //Si f.compteurIntervalle possède une valeur sup. ou égale à compteurMemoMax (99)
                                                            //TEST
                                                            //i("f.compteurIntervalle supérieur à compteurMemoMax !")
                                                            //mémorisation avec la fonction memo.ecrire() disponible dans la bibliothèque Memoire
    memo.ecrire(AVANCERetSecondes);                         //mémorisation de la valeur 199 équivalente à la tactique 1 (AVANCER) suivi de 99 (secondes)
    stopEcriture = 1;                                       //Eviter de mémoriser plusieurs fois de suite! 
                                                            //Tant que OBJETcompteurIntervalle >= compteurMemoMax, stopEcriture = 1 permet de ne pas entrer dans la condition
                                                            //TODO: trouver un moyen de ne plus être dépendant de cette rustine stopEcriture !
  }else{
    stopEcriture = 0;                                       //stopEcriture permet à nouveau d'entrer dans la conditon
  } 

}

/*=========================================================*/ 

                                                            /** MEMORISATION DU TEMPS PARCOURU POUR L'ACTION AVANCER /99S MAX **/
                                                            //FONCTION memoInstantTAvancer()
void memoInstantTAvancer()
{
   unsigned char compositionNombre,cctntnJ1 = 0;
   if(f.compteurIntervalle < 10)
   {                                                        //Si f.compteurIntervalle < à 10, il faut ajouter un 0 devant les chiffre (0 à 9)
      compositionNombre = f.concatenation(10,f.compteurIntervalle);
      cctntnJ1 = compositionNombre;
   }else{
      compositionNombre = f.compteurIntervalle;
      cctntnJ1 = f.concatenation(1,compositionNombre);      //concatenation action AVANCER suivi du délai écoulé en cours inférieur à 99 secondes
   }

   if(cctntnJ1 > 100)
   {                                                        //Si 'cctntnJ1' est supérieure à 100 (inutile de mémoriser un temps à 0)
                                                            //TEST
                                                            //i("Mémo AVANCER suivi de valeur")                                                           
                                                            //i(cctntnJ1)    
    memo.ecrire(cctntnJ1);                                  //mémorisation avec la fonction memo.ecrire() disponible dans la bibliothèque Memoire   
   }
}

/*=========================================================*/ 

                                                            /** MEMORISATION DE LA TACTIQUE D'EVITEMENT SUIVI DE LA POSITION DU SERVOMOTEUR **/
                                                            //memorisation de l'action qui évite l'obstacle + position du SVM
                                                            //FONCTION memoInstantT(action,position du svm)
void memoInstantT(unsigned char actJ, unsigned char posSVM)
{
   unsigned char cctntnJ2 = f.concatenation(actJ,posSVM);   //concatenation de l'action suivi de la position du SVM
   memo.ecrire(cctntnJ2);                                   //mémorisation avec la fonction memo.ecrire() disponible dans la bibliothèque Memoire
}

/*=========================================================*/ 

                                                           /** RECUPERER L'ACTION QUI FONCTIONNE LE MIEUX SUR LES 30 DERNIERES VALEURS **/
                                                           //La fonction est utilisée dans la page SCORE.h
                                                           //Note: Malloc et realloc pour l'allocation dynamique du tableau cas0 font crasher le microcontrôleur !
//INIT VARIABLE
int cas0[30] = {255,255,255,255,255,                       //Ce tableau doit contenir toutes les données dans une limite de 30
                255,255,255,255,255,                       //Si la valeur de memo.pointer() est modifié, il faut également modifier le tableau en conséquence
                255,255,255,255,255,                       //TODO: Dans l'idéal, le tableau devrait être créé dynamiquement
                255,255,255,255,255,
                255,255,255,255,255,
                255,255,255,255,255};
         
//FONCTION occurrencesSCORE(position du SVM)
unsigned char occurrencesSCORE(unsigned char angleEnJauge)
{
                                                            //Définir pointeurs sur une adresse de départ et une adresse d'arrivée
  memo.adresseEepromMin = 0;                                //Reset Adresse de départ
  memo.adresseEepromMax = 0;                                //Reset Adresse d'arrivée
  memo.pointer(30);                                         //fonction memo.pointer() disponible dans la bibliothèque Memoire
                                                            //Pointer sur les 30 dernières données enregistrées
                                                            //TODO: memo.pointer() devrait pouvoir être modifié plus simplement par l'utilisateur
                                                            //TODO: Tester sur les 100 dernières données et évaluer temps de réponse
  unsigned char lireDonnees,operationSplit = 0;                                 
  int cas0compte = 0;                                       //Compteur   

  for(int lecture1 = memo.adresseEepromMin;lecture1 < memo.adresseEepromMax; lecture1++)
  {                                                         //Boucle destinée à compter le nombre d'occurrences en mémoire pour une action|positionSVM 
    lireDonnees = memo.lire(lecture1);                      //Lire la donnée avec la fonction memo.lire() disponible dans la bibliothèque Memoire
    operationSplit = lireDonnees % 10;                      //récupérer le DERNIER chiffre qui correspond à l'index de la position du servomoteur
                                                            //Ne pas inclure la marche normale, c'est à dire les enregistrements dont les valeurs sont > à 100 (AVANCER suivi de x secondes)
    float centAdetecter = lireDonnees;                      
    if(centAdetecter / 100 < 1)                             //Si la donnée correspond à une marche normale, le résultat du calcul sera supérieur à 1 (exemple: 115/100 = 1,15 | 34/100 = 0,34)
    {                                                       
      if(lireDonnees >= 10 && lireDonnees <= 44)            //Lire données tactiques d'évitement uniquement
      {                                                     //Si la valeur de lireDonnees est comprise entre 10 et 44
        if(operationSplit == angleEnJauge)
        {                                                   //Si la position SVM trouvée en mémoire est égale à la position SVM tester
          cas0[cas0compte] = lireDonnees;                   //Insérer lireDonnees (donnée complète) dans un tableau
          cas0compte++;                                     //Compter le nombre d'enregistrement
                                                            //Simplifier : ajouter tout à la suite chaque donnée (ex : 32223232) dans une variable puis split base 2 pour former un tableau ?
        }      
      }      
    }
  }   
 
  unsigned char valeurFrequenteCas0 = 0;                    //Capture de l'action la plus fréquente par position
  unsigned char actionplusfrequente0 = 0;                   //var pour resultat split

  if(cas0compte != 0)                                       //Si des enregistrements de données on été comptabilisés
  {                                                         //Trouver la combinaison action|positionSVM la plus fréquente en excluant d'éventuelles données vides (255)
    valeurFrequenteCas0 = f.plusFrequentExclusion(cas0,cas0compte,255);
                                                            //TEST
                                                            //i(valeurFrequenteCas0)
    actionplusfrequente0 = valeurFrequenteCas0 / 10;        //On récupère l'index de l'action la plus fréquente trouvée
    return actionplusfrequente0;
  }else{
    return NULL;
  }

}

/*=========================================================*/ 

#endif   
