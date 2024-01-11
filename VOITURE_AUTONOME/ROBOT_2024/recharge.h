#ifndef recharge_H
#define recharge_H
/***************************************************/
////////////////////////////////////////////////////
//             GESTION DE LA RECHARGE             //
////////////////////////////////////////////////////
bool pileOK = 0; //Interrupteur d'activation du process de recharge
float positionRecharge[3];//(x,y,volts)
float tensionMinPPV = 3; //4.5
float tensionMinBatterie = 5.5; //7.5
float tensionMaxBatterie = 7.0; //8.5
/***************************************************/

void gestionPPV(){ //0
  if(PPV.tensionAcomparer(tensionMinPPV, A3, 0) == true && PPV.lecture_tension(A3) > positionRecharge[2]){
    //enregistrer la meilleure position de recharge + volts
    positionRecharge[0] = position.x;
    positionRecharge[1] = position.y;
    positionRecharge[2] = PPV.lecture_tension(A3);
  }
}

void gestionBatterie(){ //1
  //Si la batterie est trop faible, on active le process d'accès au point de recharge connu
  if(batterie.tensionAcomparer(tensionMinBatterie, A6, 2) == true && pileOK == 0) pileOK = 1;
}

void pointRecharge(){ //2
  //Si état pileOK = 1 > GOTO point de recharge connu ou cherche énergie
  static bool stopallerA = 0; //Interrupteur à la fonction allerA()
  if(pileOK == 1 && positionRecharge[2] > 0){
    /**
    //TEST
    i("goto point de recharge")
    Serial.print("position recharge x : "); i(positionRecharge[0])
    Serial.print("position recharge y : "); i(positionRecharge[1])
    **/
    if(positionRecharge[0] != position.x && stopallerA == 0 || positionRecharge[1] != position.y && stopallerA == 0){
        allerA(positionRecharge[0],positionRecharge[1]);
    } 
    if(positionRecharge[0] >= position.x-0.01f && positionRecharge[0] <= position.x+0.01f && positionRecharge[1] >= position.y-0.01f && positionRecharge[1] <= position.y+0.01f){
      ARRET;
      stopallerA = 1;
    } 
  }
  else if(pileOK == 1 && positionRecharge[2] == 0){
    avancer(axe); //Chercher un point de recharge
  }
  if(batterie.lecture_tension(A6) >= tensionMaxBatterie){
    pileOK = 0;
    stopallerA = 0;
  }
}

/***************************************************/
#endif