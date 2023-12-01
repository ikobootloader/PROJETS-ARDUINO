#include <Fonctions.h>

//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);

//Class   Objet
FONCTIONS f;

void setup() {

  iSet

}

void loop() {

  //////// FONCTIONS SUR VARIABLES ////////
  
  //Concaténation de 2 valeurs
  /*
  int c1= 5;
  int c2 = 99; 
  int c3 = f.concatenation(c1,c2); //Retourne 599
  */

  //////// FONCTIONS SUR LE TEMPS ////////

  //Créer une fréquence
  /*
  // f.frequence(limite de temps à insérer en millisecondes)
  f.frequence(1000); //la fonction renvoie true toute les secondes
  */

  /***/

  //Créer un intervalle de temps à partir de la fonction f.frequence()
  /*
  bool val  = f.frequence(1000);
  f.intervalle(val,10);
  f.resetIntervalle() permet de réinitialiser à 0 la méthode f.compteurIntervalle 
  Le résultat est tjs retourné dans la méthode f.compteurIntervalle 
  i(f.compteurIntervalle) 
  */

  bool val  = f.frequence(1000);
  f.intervalle(val,10);
  i(f.compteurIntervalle)

  //////// FONCTIONS SUR TABLEAUX ////////

  //Retounrner la taille d'un tableau => SIZE_ARR(tableau);
  
  //Retourner la valeur la plus courante
  /*
  f.plusFrequent(nom du tableau, taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.plusFrequent(tab,SIZE_ARR(tab)) <=> f.plusFrequent(tab,10);
  */

  //Retourner la valeur la plus courante avec exclusion d'une valeur
  /*
  f.plusFrequentExclusion(nom du tableau, taille du tableau, valeur à exclure);
  */

  /***/

  //Trouver la valeur la plus petite
  /*
  //f.mini(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  int val = f.mini(tab,10); //Retourne 0
  i(val)
  */

  /***/

  //Trouver la valeur la plus grande
  /*
  //f.maxi(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7}; //Retourne 9
  int val = f.maxi(tab,10);
  i(val)  
  */

  /***/

  //Trier un tableau dans l'ordre croissant
  /*
  //f.triAsc(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.triAsc(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */

  /***/

  //Trier un tableau dans l'ordre décroissant
  /*
  //f.triDesc(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.triDesc(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */  

  /***/

  //Inverser un tableau
  /*
  //f.inverser(tableau,taille du tableau);
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};
  f.inverser(tab,10);
  for(int i = 0; i <= 9;i++){
    i(tab[i])    
  }  
  */ 

  delay(1000);
}
