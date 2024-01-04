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
  AVANCER;
  Serial.print("avancer,");i(orientation)  //COM WBSRVR
  // Conversion de degrés à radians
  float angle_radian = PI * orientation / 180.0;
  // Calcul des coordonnées x et y
  float tailleY = taillePas * cos(angle_radian);
  float tailleX = taillePas * sin(angle_radian);
  // Nouvelles positions
  position.x = position.x + tailleX;
  position.y = position.y + tailleY;
}

void reculer(float orientation) {
  RECULER;
  //COM WBSRVR
  Serial.print("reculer,");i(orientation) 
  // Conversion de degrés à radians
  float angle_radian = PI * orientation / 180.0;
  // Calcul des coordonnées x et y
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
    DROITE; 
    delay(30);
    ARRET;
    delay(100);
    compteurD++;
  }
  //conversion de la décimale en un entier (possibilité d'augmenter la précision avec multiple de 10 supérieur)
  unsigned int axeActuel = axe*100;
  unsigned int axeNouveau = degre*100;
  axeActuel = (axeActuel+axeNouveau)%36000;
  axe = axeActuel/100;
  //COM WBSRVR
  Serial.print("droite,");i(degre) 
  compteurD = 0;
}

void tournerGauche(float degre) {
  static int compteurG = 0;
  float rotationParDegre = round(degre*etalon);//conversion
  while(compteurG <= rotationParDegre){
    GAUCHE; 
    delay(30);
    ARRET;
    delay(100);
    compteurG++;
  }
  //conversion de la décimale en un entier (possibilité d'augmenter la précision avec multiple de 10 supérieur)
  unsigned int axeActuel = axe*100;
  unsigned int axeNouveau = degre*100;
  axeActuel = (axeActuel-axeNouveau+36000)%36000;
  axe = axeActuel/100;
  //COM WBSRVR
  Serial.print("gauche,");i(degre) 
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

  static bool rot = 0;
  static float stableHypotenuse = 0;

  if(rot == 0){

  //Angle qui pointe vers la position de destination
  float vecteurX = abs(position.x - destinationX);
  float vecteurY = abs(position.y - destinationY);

  //Tangente
  float angleDestination = 0;
  angleDestination = atan(vecteurX/vecteurY) * 180 / PI;
  //Trajectoire : hypoténuse
  float hypotenuse = sqrt(pow(vecteurX,2.0)+pow(vecteurY,2.0));
    
    //TEST
    /**
    Serial.print("Vecteur y: ");i(vecteurY)
    Serial.print("Vecteur x: ");i(vecteurX)
    Serial.print("Tangente en degré: ");i(angleDestination)
    Serial.print("Hypoténuse: ");i(hypotenuse)
    **/
    
    //Triangulation
    //TODO: à optimiser !
    if(destinationY > position.y && destinationX > position.x) angleDestination = angleDestination; //(y,x)
    if(destinationY < position.y && destinationX > position.x) angleDestination = 180 - angleDestination; //(-y,x)
    if(destinationY < position.y && destinationX < position.x) angleDestination = 180 + angleDestination; //(-y,-x)
    if(destinationY > position.y && destinationX < position.x) angleDestination = angleDestination*-1; //(y,-x)

    //pas de triangulation 
    if(destinationY > position.y && destinationX == position.x) angleDestination = 360; //(y,x=x') 
    if(destinationY == position.y && destinationX < position.x) angleDestination = 270; //(y=y',-x)
    if(destinationY < position.y && destinationX == position.x) angleDestination = 180; //(-y,x=x')
    if(destinationY == position.y && destinationX > position.x) angleDestination = 90; //(y=y',x)

    //TEST
    //Serial.print("Angle destination intégré : ");i(angleDestination)

    //Quantité de degré vers l'angle de destination
    int qteDegre = round(angleDestination) - round(axe);
    //TODO: Convertir en float!
    qteDegre = (qteDegre + 360)%360;
    //TEST
    /**
    Serial.print("axe : ");i(axe)
    Serial.print("quantité de degré de rotation : ");i(qteDegre)
    **/
    tournerDroite(qteDegre); //Tourner dans le sens horaire !

    stableHypotenuse = hypotenuse;

    rot = 1; //STOPPER TRIANGLUATION

  }

  //TEST
  //i(stableHypotenuse)

  //Suivre hypoténuse
  static float avancement = 0.0;
  if(avancement <= stableHypotenuse){
    //TEST
    //Serial.print("avancement = ");i(avancement)
    avancer(axe);
    delay(500);
    avancement += 0.01;
  }else{
    //i("ok")
    ARRET;
    rot = 0;
    avancement = 0.0;
    stableHypotenuse = 0.0;
  }

}

//TODO
//Pouvoir définir un territoire restreint en déplacement
//garder en mémoire les points de recharge ?
/***************************************************/
#endif