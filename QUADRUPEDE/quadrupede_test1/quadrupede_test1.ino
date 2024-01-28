
#include <Servo.h> 
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

const unsigned char angle_90 = 90;
unsigned char angle_marche_1 = 135;
unsigned char angle_marche_2 = 45;

void setup() {
  //Setup servos
  servo1.attach(5);//1
  servo2.attach(4);//2
  servo3.attach(3);//3
  servo4.attach(2);//4
  //COUCHE
  /**
  servo1.write(180);//1 
  servo2.write(0);//2
  servo3.write(180);//3
  servo4.write(0);//4
  **/
  //DEBOUT
  servo1.write(90),delay(500);
  servo2.write(90),delay(500);
  servo3.write(90),delay(500);
  servo4.write(90),delay(500);
  delay(2000);
}

void loop() {

  //BEST ONE POUR AVANCER
  unsigned char i = 0;
  //Variation de 45°
  for(i=0;i<=45;i++){
    servo1.write(angle_90-i),delay(1);//90-45
    servo2.write(angle_90-i),delay(1);//90-45
    servo3.write(angle_90+i),delay(1);//90+45
    servo4.write(angle_90+i),delay(1);//90+45
  }

  //45 et 135
  for(i=0;i<=45;i++){
    servo1.write(angle_marche_2+i),delay(1);//45=>90
    servo2.write(angle_marche_2+i),delay(1);//45=>90
    servo3.write(angle_marche_1-i),delay(1);//135=>90
    servo4.write(angle_marche_1-i),delay(1);//135=>90
  }


  for(i=0;i<=45;i++){
    servo1.write(angle_90+i),delay(1);//90+45
    servo2.write(angle_90+i),delay(1);//90+45
    servo3.write(angle_90-i),delay(1);//90-45
    servo4.write(angle_90-i),delay(1);//90-45 
  }


  for(i=0;i<=45;i++){
    servo1.write(angle_marche_1-i),delay(1);//135=>90
    servo2.write(angle_marche_1-i),delay(1);//135=>90
    servo3.write(angle_marche_2+i),delay(1);//45=>90
    servo4.write(angle_marche_2+i),delay(1);//45=>90 
  }


}
