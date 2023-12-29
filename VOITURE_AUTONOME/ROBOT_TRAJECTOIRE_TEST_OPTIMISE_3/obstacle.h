#ifndef obstacle_H
#define obstacle_H
/***************************************************/
//GESTION DES OBSTACLES

//Garder en mémoire les obstacles et les chocs pour les éviter
float obstacles[99][2]; //A intégrer à la fonction memoObstacles()

//Anticiper les positions 'obstacles' et les contourner
//A optimiser!!
void eviterObstacles(){
  for(unsigned short i = 0; i <= 99; i++){
    if(obstacles[i][0] == position.x+taillePas && obstacles[i][1] == position.y) tournerGauche(90); //(1,0)
    if(obstacles[i][0] == position.x+taillePas && obstacles[i][1] == position.y-taillePas) tournerDroite(90); //(1,-1)
    if(obstacles[i][0] == position.x && obstacles[i][1] == position.y-taillePas) tournerGauche(90); //(0,-1)
    if(obstacles[i][0] == position.x-taillePas && obstacles[i][1] == position.y-taillePas) tournerDroite(90); //(-1,-1)
    if(obstacles[i][0] == position.x-taillePas && obstacles[i][1] == position.y) tournerDroite(90); //(-1,0)
    if(obstacles[i][0] == position.x-taillePas && obstacles[i][1] == position.y+taillePas) tournerDroite(90); //(-1,1)
    if(obstacles[i][0] == position.x && obstacles[i][1] == position.y+taillePas) tournerDroite(90); //(0,1)
    if(obstacles[i][0] == position.x+taillePas && obstacles[i][1] == position.y+taillePas ) tournerGauche(90); //(1,1)
  }
}

//Mémoriser les obstacles et chocs
void memoObstacles(){
  
  static short compterObstacles = -1;
  compterObstacles += 1;
  obstacles[compterObstacles][0] = position.x;
  obstacles[compterObstacles][1] = position.y;
  if(compterObstacles == 100) compterObstacles = 0;   

  i("obstacle") //WBSVR

  /**
  //TEST
  for(int q = 0; q < 20;q++){
      Serial.print("Obstacle positions: x=");Serial.print(obstacles[q][0]);
      Serial.print(" y=");Serial.println(obstacles[q][1]);
  }
  **/

}

//REACTIONS
void reactions(){
  memoObstacles(); // Mémorise l'endroit où se trouve l'obstacle
  arret();
  tournerDroite(90);
}
/***************************************************/
#endif