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
  if(position.x != 0.00f && position.y != 0.00f && attente == 0){ //Si ce n'est pas la position de départ
    float taillePasY = abs(taillePas * cos(PI * axe / 180.0)); //Serial.print("taillePasY: ");i(taillePasY)
    float taillePasX = abs(taillePas * sin(PI * axe / 180.0)); //Serial.print("taillePasX: ");i(taillePasX )  
    float margeErreur = 0.005; //0.001 par défaut
    for(unsigned short i = 0; i <= 100; i++){
      if(axe == 0.00f){
        if(abs(obstacles[i][0] - position.x) < margeErreur && abs(obstacles[i][1] - (position.y + taillePasY)) < margeErreur){tournerDroite(45.0);break;}  //(0,1)
      }
      if(axe > 0.00f && axe < 90.00f){
        if(abs(obstacles[i][0] - (position.x + taillePasX)) < margeErreur && abs(obstacles[i][1] - (position.y + taillePasY)) < margeErreur){tournerDroite(45.0);break;}  //(1,1)
      }  
      if(axe == 90.00f){
        if(abs(obstacles[i][0] - (position.x + taillePasX)) < margeErreur && abs(obstacles[i][1] - position.y) < margeErreur){tournerDroite(45.0);break;}  //(1,0)
      }
      if(axe > 90.00f && axe < 180.00f){
        if(abs(obstacles[i][0] - (position.x + taillePasX)) < margeErreur && abs(obstacles[i][1] - (position.y - taillePasY)) < margeErreur){tournerDroite(45.0);break;} //(1,-1)
      }
      if(axe == 180.00f){
        if(abs(obstacles[i][0] - position.x) < margeErreur && abs(obstacles[i][1] - (position.y - taillePasY)) < margeErreur){tournerDroite(45.0);break;} //(0,-1) 
      }
      if(axe > 180.00f && axe < 270.00f){
        if(abs(obstacles[i][0] - (position.x - taillePasX)) < margeErreur && abs(obstacles[i][1] - (position.y - taillePasY)) < margeErreur){tournerDroite(45.0);break;} //(-1,-1) 
      }
      if(axe == 270.00f){
        if(abs(obstacles[i][0] - (position.x - taillePasX)) < margeErreur && abs(obstacles[i][1] - position.y) < margeErreur){tournerDroite(45.0);break;} //(-1,0) 
      }
      if(axe > 270.00f && axe < 360.00f){
        if(abs(obstacles[i][0] - (position.x - taillePasX)) < margeErreur && abs(obstacles[i][1] - (position.y + taillePasY)) < margeErreur){tournerDroite(45.0);break;} //(-1,1) 
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
      Serial.print("Obstacle positions: x=");Serial.print(obstacles[q][0],5);
      Serial.print(" y=");Serial.println(obstacles[q][1],5);
  }
**/
}

//REACTIONS AUX OBSTACLES ET CHOCS
void reactionsObst(){
  //i("test rect obst")
  if(laser.readRange() <= maxDistance || capteurChoc() >= maxChoc){
    memoObstacles(); // Mémorise l'endroit où se trouve l'obstacle
    arret();
    tournerDroite(90.0);
    attente = 1; //eviterObstacles() doit attendre 1 pas avant de fonctionner
  }
}

/***************************************************/
#endif
