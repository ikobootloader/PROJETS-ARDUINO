<h1>Nomenclature L298N</h1>
<br>
<br>
/*<br>
 *BRANCHEMENTS PAR DEFAUT<br>
 *enAPin = 6; // Contrôle de vitesse PWM du moteur gauche<br>
 *in1Pin = 7; // Moteur gauche Direction 1<br>
 *in2Pin = 5; // Moteur gauche Direction 2<br>
 *in3Pin = 4; // Moteur droit Direction 1<br>
 *in4Pin = 2; // Moteur droit Direction 2<br>
 *enBPin = 3; // Contrôle de vitesse PWM du moteur droit<br>
*/<br>
<br>
//Class             Objet<br>
VOITURE_CONTROLES   VOITURE;<br>
<br>
  <b>//Utilisation minimisée du code</b> (non obligatoire)<br>
  #define AVANCER VOITURE.locomotion(AVANCER,255)<br>
  #define RECULER VOITURE.locomotion(RECULER,255)<br>
  #define GAUCHE VOITURE.locomotion(GAUCHE,255)<br>
  #define DROITE VOITURE.locomotion(DROITE,255)<br>
  #define ARRET VOITURE.locomotion(ARRET,0)<br>
<br>
  <b>//Paramétrage par défaut</b><br>
  VOITURE.setupPins();<br>
  <br>
  <b>//Paramétrage manuel:</b> VOITURE.setupPins(enAPin,in1Pin,in2Pin,in3Pin,in4Pin,enBPin)<br>
  Exemple: VOITURE.setupPins(6,7,5,4,2,3);<br>
  <br>
  <b>//Paramétrage par nombre ou mot</b><br>
  //0 ou AVANT | 1 ou ARRIERE | 2 ou GAUCHE | 3 ou DROITE | 4 ou ARRET<br>
  //Exemple: VOITURE.locomotion(0,255) <=> VOITURE.locomotion(AVANCER,255)<br>
  //VOITURE.locomotion(0,255);<br>
  VOITURE.locomotion(AVANCER,255);<br>
  
  
  
  
