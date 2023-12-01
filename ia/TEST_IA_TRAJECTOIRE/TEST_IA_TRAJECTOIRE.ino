/***************************************************/
/** 
//APPRENTISSAGE AUTOMATIQUE 
=> test propagation/projection des valeurs d'états
**/
/***************************************************/
//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);
/***************************************************/
/***************************************************/
//FONCTIONS
#include <Fonctions.h>
//Class   Objet
FONCTIONS f;
/***************************************************/

/** GRILLE DE TERRITOIRE **/
int largeurY = 4; // Y => max=2 & min=0
int longueurX = 4; // X => max=2 & min=0
//grilleTerritoire[coordonneeY][coordonneeX]
double grilleTerritoire[5][5] = {{0xFF,0xFF,0xFF,0xFF,0xFF},
                                 {0xFF,0xFF,0xFF,0xFF,0xFF},
                                 {0xFF,0xFF,0xFF,0xFF,0xFF},
                                 {0xFF,0xFF,0xFF,0xFF,0xFF},       
                                 {0xFF,0xFF,0xFF,0xFF,0xFF}};

/***************************************************/

/** AGENT **/                                     
double agent = 0;   
// position de départ de l'agent
int positionAgentX = 0; 
int positionAgentY = 0; 

bool recompenseTrouve = 0;

//Fonction de déplacement automatisé et aléatoire de l'agent
void mouvementAgent(){

  if(recompenseTrouve != 1){
    int positionAgentXreset = positionAgentX;
    int positionAgentYreset = positionAgentY;
    // Déplacer l'agent
    int agentBas = positionAgentY + 1 <= largeurY ? positionAgentY + 1 : positionAgentY;
    int agentHaut = positionAgentY - 1 >= 0 ? positionAgentY - 1 : positionAgentY;
    int agentGauche = positionAgentX - 1 >= 0 ? positionAgentX - 1 : positionAgentX;
    int agentDroite = positionAgentX + 1 <= longueurX ? positionAgentX + 1 : positionAgentX;
    //mouvements random agent
    int action = random(0, 4);//hum, pas très random!
    int mouvement[4] = {agentBas,
                        agentHaut,
                        agentGauche,
                        agentDroite};
                    
    //valeur 0 sur trajectoire hors récompense
    positionAgentY = action == 0 || action == 1 ? mouvement[action] : positionAgentY;
    positionAgentX = action == 2 || action == 3 ? mouvement[action] : positionAgentX;
 
    grilleTerritoire[positionAgentY][positionAgentX] = agent;

    //risque d'enfermement si l'on empêche de parcourir des coordonnées déjà observées !
    
    i(action);
  }
  
}

/***************************************************/

/** OBSTACLE **/
int obstacle = -1;

/***************************************************/

/** RECOMPENSE **/ 
//Potionnement de la récompense
double recompense = 1;
int positionRecompenseX = 3;
int positionRecompenseY = 1;
float gamma = 0.90;
//Fonction de propagation de la récompense sur tout le territoire
void propagationValeursEtat(){

 if(positionAgentY == positionRecompenseY && positionAgentX == positionRecompenseX)
 {
    //Intégration de la récompense sur la position de l'agent
    grilleTerritoire[positionAgentY][positionAgentX] = 1;
    recompenseTrouve = 1;

    //** Propagation de la récompense sur la grille ou l'algorithme de l'onde carrée ;) **/
    //Algorithme simplifié
    for(int x = 0 ; x <= longueurX; x++){
      for(int y = 0; y <= largeurY; y++){
        if(positionRecompenseY-y >=0 && positionRecompenseX-x >= 0){
          grilleTerritoire[positionRecompenseY-y][positionRecompenseX-x] = pow(gamma,y+x); //Surface gauche haut 
        }
        if(positionRecompenseY+y <= largeurY && positionRecompenseX-x >= 0){
          grilleTerritoire[positionRecompenseY+y][positionRecompenseX-x] = pow(gamma,y+x);//Surface gauche bas
        }
        if(positionRecompenseY+y <= largeurY && positionRecompenseX+x <= longueurX){
          grilleTerritoire[positionRecompenseY+y][positionRecompenseX+x] = pow(gamma,y+x);//Surface droite bas
        }
        if(positionRecompenseY-y >=0 && positionRecompenseX+x <= longueurX){
          grilleTerritoire[positionRecompenseY-y][positionRecompenseX+x] = pow(gamma,y+x); //Surface droite haut       
        }
      }
    }    
 }
 
}

/***************************************************/

/** AFFICHER GRILLE SUR LE PORT SERIE **/
//int largeurY = 4; // Y => max=2 & min=0
//int longueurX = 4; // X => max=2 & min=0
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

void setup() {
  //Initialisation du Port Série (uniquement pour les tests) 
  iSet  
  //Positionner l'agent sur la grille
  grilleTerritoire[positionAgentY][positionAgentX] = agent;
  //Positionner la récompense sur la grille
  grilleTerritoire[positionRecompenseY][positionRecompenseX] = recompense;

  //test 
  //grilleTerritoire[1][2] = Agent; ok!
}


void loop() {
  
  //Mouvement agent
  mouvementAgent();
  
  //Afficher grille
  afficherGrilleTerritoire();

  //Propagation des valeurs d'état
  propagationValeursEtat();
  
  //delay(1000);

  i("**********************")
  
}
