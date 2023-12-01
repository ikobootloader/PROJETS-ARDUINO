/***************************************************/
/** 
//APPRENTISSAGE AUTOMATIQUE 
=> test Q-learning
**/
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
//FONCTIONS
#include <Fonctions.h>
//Class   Objet
FONCTIONS f;
/***************************************************/

/** GRILLE DE TERRITOIRE **/
int largeurY = 3; // 
int longueurX = 3; // 
//grilleTerritoire[coordonneeY][coordonneeX]
double grilleTerritoire[4][4] = {{0,0,0,-100},
                                 {0,100,0,0},
                                 {0,0,0,0},
                                 {-10,0,0,-1}};                              

double idEtats[4][4] = {{0,1,2,3},
                       {4,5,6,7},
                       {8,9,10,11},
                       {12,13,14,15}}; 
/***************************************************/

/** Q-LEARNING **/
//Pour chaque état/action possible (haut, bas, gauche et droite) du système on assigne une valeur
double Q[16][4] = {{0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},
                   {0, 0, 0, 0},                              
                   {0, 0, 0, 0}};
                   
/***************************************************/

/** AGENT **/     
//double agent = 0;                                
  
// position de départ de l'agent
int positionAgentX = 0; 
int positionAgentY = 0;

void mouvement(int actionArealiser){

   //i(positionAgentY)
  if(actionArealiser == 0){//agentBas
    if(positionAgentY + 1 <= largeurY){
      //i("agentBas")
      positionAgentY = positionAgentY + 1;
    }
  }
  if(actionArealiser == 1){//agentHaut
    if(positionAgentY - 1 >= 0){
      //i("//agentHaut")
      positionAgentY = positionAgentY - 1;
    }
  } 
  if(actionArealiser == 2){//agentGauche
    if(positionAgentX - 1 >= 0){
      //i("agentGauche")
      positionAgentX = positionAgentX - 1;
    }
  } 
  if(actionArealiser == 3){//agentDroite
    if(positionAgentX + 1 <= longueurX){
      //i("agentDroite")
      positionAgentX = positionAgentX + 1;
    }
  }  
  
}
             
//Fonction de déplacement aléatoire de l'agent
void mouvementAgent(){
  
    //mouvements random agent
    int action = random(0, 4);//hum, pas très random
    mouvement(action);
    //Correspondance grille de territoire avec la matrice Q(s,a)
    int etat = idEtats[positionAgentY][positionAgentX];
    //i("état")
    //i(etat)
    propagationRecompense(etat,action);     

}

/***************************************************/

/** APPRENTISSAGE **/ 
float gamma = 0.90;
float lr = 0.1; //Tx d'apprentissage

long compteur = 0;

void propagationRecompense(int s,int a){

    
    int positionAgentY1 = positionAgentY;
    int positionAgentX1 = positionAgentX;
    //Test
    //i("coordonnées Q[s1][a1]")
    //Serial.print(positionAgentY1);Serial.print(" | ");i(positionAgentX1)
    // 

    if(a == 0){//agentBas
      if(positionAgentY1 + 1 <= largeurY){
        //i("agentBas")
        positionAgentY1 = positionAgentY1 + 1;
      }
    }
    if(a == 1){//agentHaut
      if(positionAgentY1 - 1 >= 0){
        //i("//agentHaut")
        positionAgentY1 = positionAgentY1 - 1;
      }
    } 
    if(a == 2){//agentGauche
      if(positionAgentX1 - 1 >= 0){
        //i("agentGauche")
        positionAgentX1 = positionAgentX1 - 1;
      }
    } 
    if(a == 3){//agentDroite
      if(positionAgentX1 + 1 <= longueurX){
        //i("agentDroite")
        positionAgentX1 = positionAgentX1 + 1;
      }
    }  

    int s1 = idEtats[positionAgentY1][positionAgentX1]; 

    //Trouver l'action avec valeur max sur état+1
    if(s1 > 16){
      s1 = 16;
      
    }

    int r = grilleTerritoire[positionAgentY1][positionAgentX1]; //Récompense disponible en fonction de etat+1 dans la continuité de l'action actuelle
    //En principe affiche 0 si la taille y,x ne correspond pas à celle de la grille
    //TODO: largeurY+1*longueurX+1 <= nombre total de coordonnées (16)
    //i("s1")
    //i(s1)
   
    int actionMAX[4] = {Q[s1][0],Q[s1][1],Q[s1][2],Q[s1][3]};
    int a1 = f.maxi(actionMAX,4);
    //i("a1")
    //i(a1)
    //Q-Learning
    //Q[etat][action] = Q[etat][action] + lr*(r + gamma*Q[etatPlus1][actionPlus1] - Q[etat][action])
    Q[s][a] = Q[s][a] + lr*(r + gamma*(Q[s1][a1] - Q[s][a]));
    //i("Résultat calcul Q[s][a]")
    //i(Q[s][a])
 
}

/***************************************************/ 

/** AFFICHER GRILLE SUR LE PORT SERIE **/
void afficherGrilleTerritoire()
{
  for(int coordonneeY = 0 ; coordonneeY <= largeurY; coordonneeY++){
    
    Serial.print("----------------------------------------");Serial.print("y");Serial.print(coordonneeY);i("")
   
    for(int coordonneeX = 0 ; coordonneeX <= longueurX; coordonneeX++){
      
      Serial.print(grilleTerritoire[coordonneeY][coordonneeX]);
      Serial.print(" | ");
      
    }

    i("\n")
  }
}

/***************************************************/

/** AFFICHER MATRICE Q **/

void afficherMatriceQ(){
  for(int f = 0; f <= 15; f++){

    for(int g = 0; g <= 3; g++){
      Serial.print(Q[f][g]);
      Serial.print(" | ");     
    }
    Serial.print("-");Serial.print("y");Serial.print(f);i("")
        
  }
}

/***************************************************/

void setup() {
  //Initialisation du Port Série (uniquement pour les tests) 
  iSet  
  //Positionner l'agent sur la grille
  //grilleTerritoire[positionAgentY][positionAgentX] = agent;
}


void loop() {
  
  //Mouvement agent
  mouvementAgent();

  //Afficher matrice Q
  afficherMatriceQ();
  
  //Afficher grille territoire
  //afficherGrilleTerritoire();

  compteur++;
  i(compteur)
  
  //delay(2000);

  i("**********************")
  
}
