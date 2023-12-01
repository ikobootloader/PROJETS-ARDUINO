//SERVO
#include <Servomoteur.h>

//SIMPLIFICATION DE L'UTILISATION DU PORT SERIE
#define iSet     Serial.begin(9600);
#define i(texte) Serial.println(texte);

/*********************************/
#define amplitude servo.amplitude
//Class       Ojbet
SERVOMOTEUR   servo;


void setup() {

  iSet
  servo.setupServo();
 
}
 
void loop(){

  //Initialiser l'oscillateur en déinissant une vitesse (obligatoire!)
  //servo.oscillateur(500);
  
  //Activer le balayage du servomoteur 
  //servo.balayage(amplitude); //ou// servo.balayage(servo.amplitude);

  //Initialisation des angles par l'utilisateur (Toujours 5 entrées!)
  //sinon lecteur des angles par défaut : 5,45,90,135,175
  //servo.angles(0,100,120,140,170);

  //TEST
  //i(servo.oscillateur(1000))

  servo.oscillateur(1000);
  servo.balayage(amplitude);

}
