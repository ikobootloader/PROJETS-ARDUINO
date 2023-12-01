/***************************************************/
/** 
//APPRENTISSAGE AUTOMATIQUE 
=> Tester le perceptron
**/
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//Configuration des données
/**

1 | 0
0 | 0

(x1,y1) = (0,1) = 1
(x2,y2) = (1,1) = 0
(x3,y3) = (1,0) = 0
(x4,y4) = (0,0) = 0

**/
//A chaque donnée à entrer dans le perceptron est associée :
//Un poids qui variera en fonction du cycle d'apprentissage
//Une valeur de sortie 1 ou -1 attendue
//Ex 1ère ligne de la matrice : 1 = donnée du modèle de référence , 0 = poids , 1 = valeur attendue
float donneesX[4][3] = {{1,0,1},
                        {0,0,-1},
                        {0,0,-1},
                        {0,0,-1}};

//Définir un biais 
/**
 * 
 * Ce biais (bias) peut être vu comme un neurone externe supplémentaire 
 * qui envoie systématiquement le signal 1 de poids b au neurone bleu. 
 * Grâce à lui, la fonction d'activation va être décalée et le réseau aura donc de 
 * plus grandes opportunités d'apprentissage.
 * Source : https://penseeartificielle.fr/focus-reseau-neurones-artificiels-perceptron-multicouche/#:~:text=Ce%20biais%20(bias)%20peut%20%C3%AAtre,plus%20grandes%20opportunit%C3%A9s%20d'apprentissage.
 * 
 */
 
float biais = 1.00;

//Définir un taux d'apprentissage
/**
 * 
 *A quoi ça sert d’ajouter une vitesse d’apprentissage ?
 *Le problème avec la convergence, c’est qu’elle peut-être très longue à « arriver ». 
 *Si le calcul nous donne la direction et le pas à effectuer pour nous rapprocher 
 *d’un minimum du système, il y a tout d’abord un risque de tomber sur un minimum local. 
 *
 *A l’inverse, si on choisit une valeur trop élevée, on risque de sauter d’un côté de 
 *la solution optimale à l’autre sans jamais se rapprocher (voire même en s’éloignant) !
 *
 *La vitesse d’apprentissage est donc impactante pour notre perceptron, 
 *et en général on la choisit de 0.001 à 0.5. 
 *On peut également laisser cette valeur « élevée » au début 
 *(puisque nos poids sont initialisés au hasard) afin de se diriger rapidement vers la solution, 
 *puis diminuer cette vitesse pour affiner notre réponse…
 *Source: https://penseeartificielle.fr/focus-reseau-neurones-artificiels-perceptron-multicouche/
 * 
 */

float tauxApprentissage = 0.1;

//Définir une quantité d'itération d'apprentissage
int iteration = 20;

/** PERCEPTRON **/ 
// x = Donnée en entrée
// p = Poids
// b = Biais
float perceptron(int x, float p, float b){
  
  // y = donnée * poids + biais
  double y = x * p + b;
  //ex: y = 1 * 0 + 1 = 1
  //ex: y = 1 * 0 + 0.9
  //ex: y = 0 * 0 + 1 = 1
  //ex: y = 0 * 0 + 0.90 = 0.90
  // fonction de probabilité sigmoide
  //y = 1/(1+pow(exp(1),-y));
  
  if(y > 0){ //Si utilisation de la sigmoide, doit être supérieur à 0.50
    i("return 1")
    i("donnée")
    i(x)
    i("poids")
    i(p)
    i("biais")
    i(b)    
    return 1;
  }else{
    i("return -1")
    i("donnée")
    i(x)
    i("poids")
    i(p)
    i("biais")
    i(b)
    return -1;
  }
  
}

//Définir une donnée de sortie
int sortieY = 0;


/***************************************************/

void setup() {
  //Initialisation du Port Série (uniquement pour les tests) 
  iSet 
}

void loop() {
  
  //Boucle d'apprentissage
  for(int i = 1; i <= iteration; i++){
    for(int donnees = 0; donnees <= 3 ; donnees++)
    {
      //donneesX[4][3];
      //perceptron(donnée, poids, biais)
      sortieY = perceptron(donneesX[donnees][0],donneesX[donnees][1],biais);
      //Si la donnée en sortie du perceptron ne correspond pas à la donnée attendue      
      if(sortieY != donneesX[donnees][2])
      {
        //On modifie la valeur du poids pour chaque entrée
        //Modèle pratique
        //donneesX[donnees][1] = donneesX[donnees][1] + ((donneesX[donnees][0] * tauxApprentissage) * donneesX[donnees][2]);       
        //Théorie : poids + taux d'apprentissage x (sortie attendue - sortie effective) x donnée
        //Modèle théorique
        donneesX[donnees][1] = donneesX[donnees][1] + tauxApprentissage * (donneesX[donnees][2] - sortieY) * donneesX[donnees][0];
        i("valeur du poids après correction")
        i(donneesX[donnees][1])
        //On modifie la valeur du biais
        biais = biais + (tauxApprentissage * donneesX[donnees][2]);
        //ex: biais = 1 + 0.10 * -1 = 0.90
        i("valeur du biais après correction")
        i(biais) 
      }     
    }    
  }

  i("Valeur des poids")
  for(int z=0;z <= 3;z++ ){
    i(donneesX[z][1])
  }

  //On remarquera que la donnée de sortie = 1 prend en poids la valeur du taux d'apprentissage

  delay(5000);

  /** 

  p1 * x1 + p2 * x2 + b = 0
  y = p1 / p2 * x + b / p2
  
  **/

}
