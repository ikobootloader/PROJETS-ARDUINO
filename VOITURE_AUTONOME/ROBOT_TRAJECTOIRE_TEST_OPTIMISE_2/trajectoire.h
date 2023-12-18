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
float axe = 0;           // AXE DE ROTATION de 0° à 360°
const float taillePas = 0.01;     // Taille du pas
Coordonnees position = { 0, 0 };  // Initialiser les coordonnées à l'origine
/***************************************************/

void avancer(float degre) {
  AVANCER;
  i("avancer")  //COM WBSRVR
  // Conversion de degrés à radians
  float angle_radian = PI * degre / 180.0;
  // Calcul des composantes x et y
  float tailleX = taillePas * cos(angle_radian);
  float tailleY = taillePas * sin(angle_radian);
  // Nouvelles positions
  position.x = position.x + tailleX;
  position.y = position.y + tailleY;
}

void reculer(float degre) {
  RECULER;
  i("reculer")  //COM WBSRVR
  // Conversion de degrés à radians
  float angle_radian = PI * degre / 180.0;
  // Calcul des composantes x et y
  float tailleX = taillePas * cos(angle_radian);
  float tailleY = taillePas * sin(angle_radian);
  // Nouvelles positions
  position.x = position.x - tailleX;
  position.y = position.y - tailleY;
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
  unsigned short axeActuel = axe;
  unsigned short axeNouveau = degre;
  axeActuel = (axeActuel+axeNouveau)%360;
  axe = axeActuel;
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
  i("gauche")  //COM WBSRVR
  unsigned short axeActuel = axe;
  unsigned short axeNouveau = degre;
  axeActuel = (axeActuel-axeNouveau+360)%360;
  axe = axeActuel;
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
bool rot = 0;
// Fonction pour diriger l'agent vers des coordonnées spécifiées
void allerA(float destinationX, float destinationY) {
  /***/
  //Version optimisée : déplacement sur l'hypoténuse à partir de l'angle arctan( →x / →y )
  //atan (param) * 180 / PI;
  //hypoténuse √(→x² + →y²)
  /***/
  //Angle qui pointe vers la position de destination
  float vecteurX = (position.x * -1) - (destinationX * -1);
  float vecteurY = (position.y * -1) - (destinationY * -1);
  unsigned short angleDestination = atan(vecteurX / vecteurY) * 180 / PI;
  //Trajectoire : hypoténuse
  float hypotenuse = sqrt(pow(vecteurX,2.0)+pow(vecteurY,2.0));
  //Sur l'hypoténuse, perte de l'axe!

  //TESTS
  Serial.print("Vecteur y: ");i(vecteurY)
  Serial.print("Vecteur x: ");i(vecteurX)
  Serial.print("Angle destination: ");i(angleDestination)
  Serial.print("Hypoténuse: ");i(hypotenuse)
 

//Attention à retrouver en temps réel les positions x et y pour le webserveur !
//WEBSERVER
//Doit-on faire adapter la taille du pas : Taille du pas*√2 ????
//Réelle distance : hypoténuse*(taille du pas *√2)/taille du pas ???? A tester !
}

//A adapter pour un déplacement sur l'hypoténuse
//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les obstacles ?
//garder en mémoire les points de recharge ?
/***************************************************/
#endif