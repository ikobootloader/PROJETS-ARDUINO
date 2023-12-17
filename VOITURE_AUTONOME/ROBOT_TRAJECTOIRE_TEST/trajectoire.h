#ifndef trajectoire_H
#define trajectoire_H
/***************************************************/
////////////////////////////////////////////////////
//               POSITION DE L'AGENT              //
////////////////////////////////////////////////////
struct Coordonnees {
  float x;  // AVANCER ET RECULER
  float y;  // GAUCHE ET DROITE
};
unsigned short axe = 0;           // AXE DE ROTATION // 0: vers le haut, 1: vers la droite, 2: vers le bas, 3: vers la gauche
const float taillePas = 0.01;     // Taille du pas
Coordonnees position = { 0, 0 };  // Initialiser les coordonnées à l'origine
/***************************************************/

void avancer() {
  AVANCER;
  i("avancer")  //COM WBSRVR
    switch (axe) {
    case 0:  // Avancer vers le haut
      position.y += taillePas;
      break;
    case 1:  // Avancer vers la droite
      position.x += taillePas;
      break;
    case 2:  // Avancer vers le bas
      position.y -= taillePas;
      break;
    case 3:  // Avancer vers la gauche
      position.x -= taillePas;
      break;
  }
}

void reculer() {
  RECULER;
  i("reculer")  //COM WBSRVR
    switch (axe) {
    case 0:  // Reculer vers le bas
      position.y -= taillePas;
      break;
    case 1:  // Reculer vers la gauche
      position.x -= taillePas;
      break;
    case 2:  // Reculer vers le haut
      position.y += taillePas;
      break;
    case 3:  // Reculer vers la droite
      position.x += taillePas;
      break;
  }
}

/***************************************************/

//26 rot pour 90° si droite delai 30 et arret delai 100
//26/90 = 0.288 rot par degré
float etalon = 0.288;

void tournerDroite(float degre) {
  static int compteurD = 0;
  degre = round(degre*etalon);//conversion
  while(compteurD <= degre){
    DROITE; 
    delay(30);
    ARRET;
    delay(100);
    compteurD++;
  }
  i("droite")  //COM WBSRVR
  axe = (axe + 1) % 4;
  compteurD = 0;
}

void tournerGauche(float degre) {
  static int compteurG = 0;
  degre = round(degre*etalon);//conversion
  while(compteurG <= degre){
    GAUCHE; 
    delay(30);
    ARRET;
    delay(100);
    compteurG++;
  }
  GAUCHE, delay(200);
  i("gauche")  //COM WBSRVR
    axe = (axe + 3) % 4;
    compteurG = 0;
}

void arret() {
  ARRET;
  i("arreter")  //COM WBSRVR
    delay(300);
}

////////////////////////////////////////////////////
//          SE DIRIGER VERS UNE POSITION          //
////////////////////////////////////////////////////
bool allerVersY = 0;
bool allerVersX = 0;
bool changementDirection = 0;
// Fonction d'aller à des coordonnées spécifiées
void allerA(float destinationX, float destinationY) {

  //1-Traitement Y
  //On compense l'incompréhension de l'Arduino sur la condition if((position.y * -1) - (destinationY * -1) == 0.0)
  if((position.y * -1) - (destinationY * -1) > -0.01 && (position.y * -1) - (destinationY * -1) < 0.01){
    //i("ok")
    allerVersY = 1;
    changementDirection = 0;
  } 

  if(allerVersY != 1) {
    if (position.y < destinationY) {
      if(!changementDirection && axe == 0){ //haut
        //rien
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerGauche(90);
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerDroite(90);
        tournerDroite(90);
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerDroite(90);
        changementDirection++;
      }
      //avancer();
    }
  }

  if(allerVersY != 1) {
    if (position.y > destinationY) {
      if(!changementDirection && axe == 0){ //haut
        tournerDroite(90);
        tournerDroite(90);
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerDroite(90);
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        //rien
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerGauche(90);
        changementDirection++;
      }
      //avancer();
    }
  }

  //2-Traitement X
  if((position.x * -1) - (destinationX * -1) > -0.01 && (position.x * -1) - (destinationX * -1) < 0.01){
    //i("ok")
    allerVersX = 1;
    changementDirection = 0;
  } 

  if(allerVersY == 1 && allerVersX != 1) {
    if (position.x < destinationX) {
      if(!changementDirection && axe == 0){ //haut
        tournerDroite(90);
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        //Rien
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerGauche(90);
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerDroite(90);
        tournerDroite(90);
        changementDirection++;
      }
      //avancer();
    }
  }

  if(allerVersY == 1 && allerVersX != 1) {
    if (position.x > destinationX) {
      if(!changementDirection && axe == 0){ //haut
        tournerGauche(90);
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerDroite(90);
        tournerDroite(90); 
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerDroite(90);
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        //Rien
        changementDirection++;
      }
      //avancer();
    }
  }
  //LORSQUE L'AGENT EST AUX POSITIONS INDIQUEES, RESET L'ALGO
  if(allerVersY == 1 && allerVersX == 1) {
      allerVersY = 0;
      allerVersX = 0;
  }

}

//A adapter pour un déplacement sur l'hypoténuse
//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les obstacles ?
//garder en mémoire les points de recharge ?
/***************************************************/
#endif