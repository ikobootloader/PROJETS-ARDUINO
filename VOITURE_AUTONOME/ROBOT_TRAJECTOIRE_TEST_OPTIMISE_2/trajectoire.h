#ifndef trajectoire_H
#define trajectoire_H
/***************************************************/
////////////////////////////////////////////////////
//               POSITION DE L'AGENT              //
////////////////////////////////////////////////////
struct Coordonnees {
  float x;  // 
  float y;  // 
};
float axe = 0; // AXE DE ROTATION 0° à 360°
const float taillePas = 0.01;     // Taille du pas
Coordonnees position = { 0, 0 };  // Initialiser les coordonnées à l'origine
/***************************************************/

void avancer(float orientation) {
  //AVANCER;
  i("avancer")  //COM WBSRVR
  // Conversion de degrés à radians
  float angle_radian = PI * orientation / 180.0;
  // Calcul des composantes x et y
  float tailleY = taillePas * cos(angle_radian);
  float tailleX = taillePas * sin(angle_radian);
  // Nouvelles positions
  position.x = position.x + tailleX;
  position.y = position.y + tailleY;
}

void reculer(float orientation) {
  //RECULER;
  i("reculer")  //COM WBSRVR
  // Conversion de degrés à radians
  float angle_radian = PI * orientation / 180.0;
  // Calcul des composantes x et y
  float tailleY = taillePas * cos(angle_radian);
  float tailleX = taillePas * sin(angle_radian);
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
  float rotationParDegre = round(degre*etalon);//conversion
  while(compteurD <= rotationParDegre){
    //DROITE; 
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
  float rotationParDegre = round(degre*etalon);//conversion
  while(compteurG <= rotationParDegre){
    //GAUCHE; 
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

// Fonction pour diriger l'agent vers des coordonnées spécifiées
void allerA(float destinationX, float destinationY) {
  /***/
  //Version optimisée : déplacement sur l'hypoténuse à partir de l'angle arctan( →x / →y )
  //atan (param) * 180 / PI;
  //hypoténuse √(→x² + →y²)
  /***/
  //Angle qui pointe vers la position de destination
  float vecteurX = abs((position.x * -1) - (destinationX * -1));
  float vecteurY = abs((position.y * -1) - (destinationY * -1));

  //Tangente
  float angleDestination = atan2(vecteurX,vecteurY) * 180 / PI;
  //Trajectoire : hypoténuse
  float hypotenuse = sqrt(pow(vecteurX,2.0)+pow(vecteurY,2.0));

  static bool rot = 0;

  if(rot == 0){
    //TESTS
    Serial.print("Vecteur y: ");i(vecteurY)
    Serial.print("Vecteur x: ");i(vecteurX)
    Serial.print("Tangente en degré: ");i(angleDestination)
    Serial.print("Hypoténuse: ");i(hypotenuse)
    
    //Triangulation
    //(y,x)
    if(destinationY > position.y && destinationX > position.x) angleDestination = angleDestination; 
    //(-y,x)
    if(destinationY < position.y && destinationX > position.x) angleDestination = 180 - angleDestination; 
    //(-y,-x)
    if(destinationY < position.y && destinationX < position.x) angleDestination = 180 + angleDestination; 
    //(y,-x)
    if(destinationY > position.y && destinationX < position.x) angleDestination = 360 - angleDestination; 

    //pas de triangulation
    //(y,x=x')
    if(destinationY > position.y && destinationX == position.x) angleDestination = 0;
    //(y=y',-x)
    if(destinationY == position.y && destinationX < position.x) angleDestination = 270;
    //(-y,x=x')
    if(destinationY < p //osition.y && destinationX == position.x) angleDestination = 180;
    //(y=y',x)
    if(destinationY == position.y && destinationX > position.x) angleDestination = 90;

    Serial.print("Angle destination intégré : ");i(angleDestination)

    //Quantité de degré vers l'angle de destination
    float qteDegre = 0;
    if(axe < angleDestination) qteDegre = angleDestination - axe;
    if(axe > angleDestination) qteDegre = axe - angleDestination;

    Serial.print("quantité de degré de rotation : ");i(qteDegre)

    tournerDroite(qteDegre); //Tourner dans le sens horaire !

/**
    //Suivre hypoténuse
    static long avancement = 0;
    while(avancement <= hypotenuse){
      avancer(axe);
      avancement++;
    }
**/
    ARRET;
    rot = 1;
    //avancement = 0;
  }


//Attention à retrouver en temps réel les positions x et y pour le webserveur !
//=>Doit-on faire adapter la taille du pas : Taille du pas*√2 ????
//=>Réelle distance : hypoténuse*(taille du pas *√2)/taille du pas ???? A tester !
}

//TODO
//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les obstacles ?
//garder en mémoire les points de recharge ?
/***************************************************/
#endif