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

void tournerDroite() {
  DROITE, delay(10);
  i("droite")  //COM WBSRVR
    axe = (axe + 1) % 4;
}

void tournerGauche() {
  GAUCHE, delay(10);
  i("gauche")  //COM WBSRVR
    axe = (axe + 3) % 4;
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
    i("ok")
    allerVersY = 1;
    changementDirection = 0;
  } 

  if(allerVersY != 1) {
    if (position.y < destinationY) {
      if(!changementDirection && axe == 0){ //haut
        //rien
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerGauche();
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerDroite();
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerDroite();
        changementDirection++;
      }
      avancer();
    }
  }

  if(allerVersY != 1) {
    if (position.y > destinationY) {
      if(!changementDirection && axe == 0){ //haut
        tournerDroite();
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        //rien
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerGauche();
        changementDirection++;
      }
      avancer();
    }
  }

  //2-Traitement X
  if((position.x * -1) - (destinationX * -1) > -0.01 && (position.x * -1) - (destinationX * -1) < 0.01){
    i("ok")
    allerVersX = 1;
    changementDirection = 0;
  } 

  if(allerVersY == 1 && allerVersX != 1) {
    if (position.x < destinationX) {
      if(!changementDirection && axe == 0){ //haut
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        //Rien
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerGauche();
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        tournerDroite();
        tournerDroite();
        changementDirection++;
      }
      avancer();
    }
  }

  if(allerVersY == 1 && allerVersX != 1) {
    if (position.x > destinationX) {
      if(!changementDirection && axe == 0){ //haut
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 1){ //droite
        tournerDroite();
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 2){ //bas
        tournerDroite();
        changementDirection++;
      }else if(!changementDirection && axe == 3){ //gauche
        //Rien
        changementDirection++;
      }
      avancer();
    }
  }
}

//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les obstacles ?
//garder en mémoire les points de recharge ?
/***************************************************/
#endif