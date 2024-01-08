#ifndef obstacle_H
#define obstacle_H
/***************************************************/
////////////////////////////////////////////////////
//              GESTION DES OBSTACLES             //
////////////////////////////////////////////////////
bool attente = 0; //Interrupteur process d'évitement
float obstacles[100][2]; //Garder en mémoire les obstacles et les chocs pour les éviter
/***************************************************/

//Anticiper les positions 'obstacles' et les contourner 
void eviterObstacles(){
  if(position.x != 0 && position.y != 0 && attente == 0){ //Si ce n'est pas la position de départ
    float taillePasY = abs(taillePas * cos(PI * axe / 180.0)); //Serial.print("taillePasY: ");i(taillePasY)
    float taillePasX = abs(taillePas * sin(PI * axe / 180.0)); //Serial.print("taillePasX: ");i(taillePasX )  
    for(unsigned short i = 0; i <= 100; i++){
      //TODO: à optimiser ! A revoir, ne fonctionne pas correctement
      if(axe == 0){
        if(obstacles[i][0] == position.x && obstacles[i][1] == position.y+taillePasY) tournerDroite(45); //(0,1)
      }
      if(axe > 0 && axe < 90){
        if(obstacles[i][0] == position.x+taillePasX && obstacles[i][1] == position.y+taillePasY ) tournerDroite(45); //(1,1)
      }     
      if(axe == 90){
        if(obstacles[i][0] == position.x+taillePasY && obstacles[i][1] == position.y) tournerDroite(45); //(1,0)
      }
      if(axe > 90 && axe < 180){
        if(obstacles[i][0] == position.x+taillePasX && obstacles[i][1] == position.y-taillePasY) tournerDroite(45); //(1,-1)
      }
      if(axe == 180){
        if(obstacles[i][0] == position.x && obstacles[i][1] == position.y-taillePasY) tournerDroite(45); //(0,-1)
      }
      if(axe > 180 && axe < 270){
        if(obstacles[i][0] == position.x-taillePasX && obstacles[i][1] == position.y-taillePasY) tournerDroite(45); //(-1,-1)
      }
      if(axe == 270){
        if(obstacles[i][0] == position.x-taillePasY && obstacles[i][1] == position.y) tournerDroite(45); //(-1,0)
      }
      if(axe > 270 && axe < 360){
        if(obstacles[i][0] == position.x-taillePasX && obstacles[i][1] == position.y+taillePasY) tournerDroite(45); //(-1,1)
      } 
    }
  }
  attente = 0;
}

//Mémoriser les obstacles et chocs
void memoObstacles(){
  //i("memo obst")
  static short compterObstacles = -1;
  compterObstacles += 1;
  obstacles[compterObstacles][0] = position.x;
  obstacles[compterObstacles][1] = position.y;
  if(compterObstacles == 99) compterObstacles = 0;   
  Serial.print("obstacle,");i("")  //WBSVR
  delay(150);
  /**
  //TEST
  for(int q = 0; q < 40;q++){
      Serial.print("Obstacle positions: x=");Serial.print(obstacles[q][0]);
      Serial.print(" y=");Serial.println(obstacles[q][1]);
  }
  **/
}

//REACTIONS AUX OBSTACLES ET CHOCS
void reactionsObst(){
  //i("test rect obst")
  if(laser.readRange() <= maxDistance || capteurChoc() >= maxChoc){
    memoObstacles(); // Mémorise l'endroit où se trouve l'obstacle
    arret();
    tournerDroite(90);
    attente = 1; //eviterObstacles() doit attendre 1 pas avant de fonctionner
  }
}

/***************************************************/
#endif