#ifndef trajectoire_H
#define trajectoire_H
/***************************************************/
// Position de l'agent
struct Coordonnees {
  double x; // AVANCER ET RECULER
  double y; // GAUCHE ET DROITE
};

unsigned short axe = 0; // AXE DE ROTATION
const double taillePas = 0.01; // Taille du pas
Coordonnees position = {0, 0}; // Initialiser les coordonnées à l'origine

void avancer() {
  AVANCER;
  i("avancer") //COM WBSRVR
  switch (axe) {
    case 0: // Avancer vers le haut
      position.y += taillePas;
      break;
    case 1: // Avancer vers la droite
      position.x += taillePas;
      break;
    case 2: // Avancer vers le bas
      position.y -= taillePas;
      break;
    case 3: // Avancer vers la gauche
      position.x -= taillePas;
      break;
  }
}

void reculer() {
  RECULER;
  i("reculer") //COM WBSRVR
  switch (axe) {
    case 0: // Reculer vers le bas
      position.y -= taillePas;
      break;
    case 1: // Reculer vers la gauche
      position.x -= taillePas;
      break;
    case 2: // Reculer vers le haut
      position.y += taillePas;
      break;
    case 3: // Reculer vers la droite
      position.x += taillePas;
      break;
  }
}

void tournerDroite() {
  DROITE;
  i("droite") //COM WBSRVR
  axe = (axe + 1) % 4;
}

void tournerGauche() {
  GAUCHE;
  i("gauche") //COM WBSRVR
  axe = (axe + 3) % 4;
}

void arret() {
  ARRET;
  delay(300);
}

/***************************************************/
#endif