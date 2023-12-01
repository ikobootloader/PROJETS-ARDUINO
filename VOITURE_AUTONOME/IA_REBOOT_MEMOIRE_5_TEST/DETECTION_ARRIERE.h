#ifndef DETECTION_ARRIERE_H
#define DETECTION_ARRIERE_H

 
void detectionARRIERE(bool detection){

                                                  /** DETECTION D'UN OBSTACLE SUR LA FACE ARRIERE **/
                                                  //FONCTION infrarougeARRIERE()
    if(detection == true)
    {                                             //Si détection arrière
                                                  //TEST
                                                  i("détection arrière")
      memoInstantTAvancer();                      //Mémorisation du parcours déjà effectué
      f.compteurIntervalle = 0;                   //Réinitialisation de f.compteurIntervalle
      memo.ecrire(6);                             //Mémorisation du réflexe
                                                  //TODO: créer un apprentissage pour la détection arrière ?
                                                  //TODO: créer une unique fonction pour cette partie
      GAUCHE;                                     //Mouvement réflexe gauche
                                                  //Le temps de déplacement à gauche n'est pas indiqué                                      
    }  
}

#endif
