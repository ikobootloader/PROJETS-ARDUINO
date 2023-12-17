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
  short mesureBoussole = boussole();//valeur immédiate de la boussole
  short erreurTolere = 5; //Tolérance de ±5°
  Serial.print("mesure de la boussole: ");Serial.println(mesureBoussole);
  //droite = +90°
  //Nouvel angle = (angle initial + angle à ajouter)%360
  short angleAatteindre = (mesureAvRotation + 90)%360;//degré à atteindre
  Serial.print("angle à atteindre: ");Serial.println(angleAatteindre);
  //si la mesure (angleAatteindre-erreurTolere+360)%360) est > à (angleAatteindre+erreurTolere)%360), 
  //signer la mesure (angleAatteindre-erreurTolere+360)%360) pour éviter l'incohérence du type mesure >= 355 && mesure <= 95 (tolérance à 5)
  //signer mesureBoussole également*
  short signer = 1;
  bool cap = 0;
  if((angleAatteindre-erreurTolere+360)%360 > (angleAatteindre+erreurTolere)%360) signer = -1;
  bool estSigne = (mesureBoussole*signer) <= (((angleAatteindre-erreurTolere+360)%360)*signer) && (mesureBoussole*signer) >= (((angleAatteindre+erreurTolere)%360)*signer);
  bool pasSigne = (mesureBoussole*signer) >= (((angleAatteindre-erreurTolere+360)%360)*signer) && (mesureBoussole*signer) <= (((angleAatteindre+erreurTolere)%360)*signer);
  
  Serial.print("est signé: ");i(estSigne)
  Serial.print("pas signé: ");i(pasSigne)
  // Tolérance de rotation de 5 degrés pour arrêter la rotation
  if(estSigne || pasSigne) {
    i("droite")  //COM WBSRVR
    axe = (axe + 1) % 4;
    return true;
  }else{
      DROITE;
      delay(30);//30 ok
  }
  ARRET;
  delay(150);//350 ok
  //if(laser.readRange() > maxDistance)
  tournerDroite(); 
}

void tournerGauche() {
  //gauche = -90°
  //Nouvel angle = (angle initial - angle à ajouter+360)%360
  GAUCHE, delay(200);
  i("gauche")  //COM WBSRVR
    axe = (axe + 3) % 4;
}

void arret() {
  mesureAvRotation = boussole();//lorsqu'il y a un arrêt, on récupère la valeur de la boussole comme point de référence
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
    }
  }

  if(allerVersY == 1 && allerVersX != 1) {
    if (position.x > destinationX) {
      if(!changementDirection && axe == 0){ //haut
        tournerGauche();
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
    }
  }
  //LORSQUE L'AGENT EST AUX POSITIONS INDIQUEES, RESET L'ALGO
  if(allerVersY == 1 && allerVersX == 1) {
      allerVersY = 0;
      allerVersX = 0;
  }

}

//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les obstacles ?
//garder en mémoire les points de recharge ?
/***************************************************/
#endif