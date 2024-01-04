#ifndef recharge_H
#define recharge_H
/***************************************************/
////////////////////////////////////////////////////
//             GESTION DE LA RECHARGE             //
////////////////////////////////////////////////////
bool pileOK = 0; //Interrupteur d'activation du process de recharge
float positionRecharge[3];//(x,y,volts)
float tensionMinPPV = 4;
float tensionMinBatterie = 7.5;
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
  //Si la batterie est trop faible, on active le process de recharge
  if(batterie.tensionAcomparer(tensionMinBatterie, A6, 2) == true && pileOK == 0) pileOK = 1;
}

void pointRecharge(){ //2
  //Si état pileOK = 1 > GOTO recharge ou cherche recharge
  if(pileOK = 1 && positionRecharge[2] > 0){
    if(positionRecharge[0] != position.x && positionRecharge[1] != position.y) allerA(positionRecharge[0],positionRecharge[1]);
    if(positionRecharge[0] == position.x && positionRecharge[1] == position.y) ARRET;
  }
  else{
    avancer(axe); //Chercher un point de recharge
  }
  if(batterie.lecture_tension(A6) >= 8.5) pileOK = 0;
}

/***************************************************/
#endif