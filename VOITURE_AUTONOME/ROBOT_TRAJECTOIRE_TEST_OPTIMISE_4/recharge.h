#ifndef recharge_H
#define recharge_H
/***************************************************/
bool pileOK = 0; //Interrupteur
float positionRecharge[3];//(x,y,volts)

void gestionPPV(){ //0
  if(PPV.tensionAcomparer(4.5, A3, 0) == true && PPV.lecture_tension(A3) > positionRecharge[2]){
    //enregistrer les positions de recharge + volts
    positionRecharge[0] = position.x;
    positionRecharge[1] = position.y;
    positionRecharge[2] = PPV.lecture_tension(A3);
  }
}

void gestionBatterie(){ //1
  if(batterie.tensionAcomparer(7.5, A6, 2) == true && pileOK == 0){
    pileOK = 1;
  }
}

void pointRecharge(){ //2
  //Si état pileOK = 1 > GOTO recharge ou cherche recharge
  if(positionRecharge[0] != position.x && positionRecharge[1] != position.y){
    if(pileOK = 1 && positionRecharge[2] > 0){
      allerA(positionRecharge[0],positionRecharge[1]);
    }
  }else if(batterie.lecture_tension(A6) >= 8.5){
      pileOK = 0;
  }else{

  }
}
/***************************************************/
#endif