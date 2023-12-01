/**********************************************************************************************
 * Arduino L298N TOOLS - Version 1
 * by ikobootloader
 *
 * Not notice => License GPLv3 
 * Others => License specific to each function
 **********************************************************************************************/

#include "Arduino.h"
#include "Fonctions.h"

FONCTIONS::FONCTIONS(){}

//////// FONCTIONS SUR VARIABLES ////////

int FONCTIONS::concatenation(int a, int b)
{//Concaténation de 2 valeurs

/*
*https://www.geeksforgeeks.org/how-to-concatenate-two-integer-values-into-one/
*https://creativecommons.org/licenses/by-sa/2.0/fr/
*/

    char s1[20];
    char s2[20];
 
    // Convert both the integers to string
    sprintf(s1, "%d", a);
    sprintf(s2, "%d", b);
 
    // Concatenate both strings
    strcat(s1, s2);
 
    // Convert the concatenated string
    // to integer
    int c = atoi(s1);
 
    // return the formed integer
    return c;
}

//////// FONCTIONS SUR LE TEMPS ////////

unsigned long FONCTIONS::termePrecedent = 0;
//Ne fonctionne pas dans plusieurs objets !
//Renvoie 0 à chaque loop puis 1 lorsqu'il atteint le terme fixé
bool FONCTIONS::frequence(unsigned long terme)
{//Créer une fréquence
  
  if(millis() - termePrecedent >= terme) {
    termePrecedent = millis();
    return true;//
  }else{
    return false; 
  }
}

/***/

int FONCTIONS::compteurIntervalle = 0;

void FONCTIONS::intervalle(int freq, int max)
{//Créer un intervalle de temps à partir de la fonction f.frequence()

	if(freq == 1){
		FONCTIONS::compteurIntervalle++;		
		if(FONCTIONS::compteurIntervalle == max){
			FONCTIONS::compteurIntervalle = 0;
		}
	}

}

void FONCTIONS::resetIntervalle()
{
	FONCTIONS::compteurIntervalle = 0;
}

/***/

//////// FONCTIONS SUR TABLEAUX ////////

int FONCTIONS::plusFrequent(int vet[], size_t dim)
{//Recupérer la valeur la plus courante dans un tableau

/*
*https://stackoverflow.com/questions/42263061/how-to-find-the-most-repeated-value-in-a-array
*https://stackoverflow.com/help/licensing
*/

    size_t i, j, count;
    size_t most = 0;
    int temp, elem;

    for(i = 0; i < dim; i++) {
        temp = vet[i];
        count = 1;
        for(j = i + 1; j < dim; j++) {
            if(vet[j] == temp) {
                count++;
            }
        }
        if (most < count) {
            most = count;
            elem = vet[i];
        }
    }
    return elem;
}

/***/

int FONCTIONS::plusFrequentExclusion(int vet[], size_t dim, int nombre)
{//Recupérer la valeur la plus courante dans un tableau

/*
*https://stackoverflow.com/questions/42263061/how-to-find-the-most-repeated-value-in-a-array
*https://stackoverflow.com/help/licensing
*/

    size_t i, j, count;
    size_t most = 0;
    int temp, elem;

    for(i = 0; i < dim; i++) {
		if(vet[i] != nombre){	//exclusion	
			temp = vet[i];
			count = 1;
			for(j = i + 1; j < dim; j++) {
				if(vet[j] == temp) {
					count++;
				}
			}
			if (most < count) {
				most = count;
				elem = vet[i];
			}		
		}		
    }
    return elem;
}

/***/

//Trouver la valeur la plus petite
// mini(tableau,taille du tableau)
int FONCTIONS::mini(int *t,size_t n){
  int o = *t;
  while(--n)
    if(*(++t) < o) o = *t;
  return o;
}

/***/

//Trouver la valeur la plus grande
// maxi(tableau,taille du tableau)
int FONCTIONS::maxi(int *t,size_t n){
  int o = *t;
  while(--n)
    if(*(++t) > o) o = *t;
  return o;
}

/***/

//Trier un tableau dans l'ordre croissant
// sortAsc(tableau,taille du tableau)
int FONCTIONS::triAsc(int t[], size_t s){     
	 int x, y, z;
     for (y=0; y<s; y++)    
        for(z=y; z<s; z++)
            if(t[z]<t[y]){
                x = t[y]; t[y] = t[z]; t[z] = x;
            }
}

/***/

//Trier un tableau dans l'ordre décroissant
// sortDesc(tableau,taille du tableau)
int FONCTIONS::triDesc(int t[], size_t s){     
	 int x, y, z;
     for (y=0; y<s; y++)    
        for(z=y; z<s; z++)
            if(t[z]>t[y]){ x = t[y]; t[y] = t[z]; t[z] = x; }
}

/***/

//Inverser un tableau
// rev(tableau,taille du tableau)
void FONCTIONS::inverser(int t[], size_t x){
  int y[x];
  for (int i = 0; i < x; i++) y[x - 1 - i] = t[i];
  for (int i = 0; i < x; i++) t[i] = y[i];
}

//////// DESTRUCTEUR ////////

FONCTIONS::~FONCTIONS(){}
