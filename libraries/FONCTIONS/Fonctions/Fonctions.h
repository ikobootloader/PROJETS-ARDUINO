#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "Arduino.h"

/* 
* 
* OUTILS GENERIQUES
* 
*/

#define SIZE_ARR(arr) (sizeof((arr))/sizeof(((arr)[0]))) //Renvoie la taille d'un tableau

class FONCTIONS{

  public:
  
	FONCTIONS();
	~FONCTIONS();
	
	// FONCTIONS SUR VARIABLES
	int concatenation(int, int);
	
	// FONCTIONS SUR LE TEMPS
	static unsigned long termePrecedent;
	bool frequence(unsigned long); //Créer une fréquence
	/***/
	static int compteurIntervalle; //le type est à modifier à convenance
	void intervalle(int,int);//Créer une limite de temps à partir de la fonction f.frequence()
	void resetIntervalle();
	
    // FONCTIONS SUR TABLEAUX
	int plusFrequent(int*, size_t);
	/***/
	int plusFrequentExclusion(int*, size_t, int);
	/***/
	int mini(int *,size_t);
	/***/
	int maxi(int *,size_t);
	/***/
	int triAsc(int *, size_t);
	/***/
	int triDesc(int *, size_t);
	/***/
	void inverser(int *, size_t);

	
};


#endif