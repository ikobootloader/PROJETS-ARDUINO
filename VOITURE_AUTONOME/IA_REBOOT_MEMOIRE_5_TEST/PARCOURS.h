#ifndef PARCOURS_H
#define PARCOURS_H

//PARCOURS
/*
 * EXECUTION D'UNE SEQUENCE D'ACTIONS CONNUE 
*/

/*=========================================================*/ 
                                                            
                                                            /** TROUVER UN MOTIF DE PARCOURS **/
int actionsPARCOURS[3] = {255,255,255};                     //tableau qui contient les actions réalisées durant le parcours
//FONCTION memoParcours()                                                     
bool memoParcours()
{                                                           //Fonction destinée à détecter une séquence répétitive de mouvements (renvoie 'true' si la séquence est détectée)
                                                            //A terme cette fonction sera modifiée (ou pas! Possibilité de créer une fonction spécifique) pour borner sa recherche de séquence sur les mouvements qui précédent une recharge de la batterie
  //Init variables  
  unsigned char incrPrcrs = 0;                              //Compteur
  int lireDernieresDonnees = 0;                             //Lecture des données antérieures
  int lireDernieresDonneesBUT = 0;                          //Lecture des données ultérieures

                                                            //Définir pointeurs sur une adresse de départ et une adresse d'arrivée
  memo.adresseEepromMin = 0;                                //Adresse mémoire de départ
  memo.adresseEepromMax = 0;                                //Adresse mémoire d'arrivée
  memo.pointer(6);                                          //Quantité de données récupérée dans la mémoire

   for(int lecture4 = memo.adresseEepromMin; lecture4 <= memo.adresseEepromMin+2; lecture4++)
   {                                                        //Boucle de lecture de la première donnée (à partir de memo.adresseEepromMin) jusqu'à la troisième
     lireDernieresDonnees = memo.lire(lecture4);            //Trouver la donnée correspondante en fonction du pointeur de la boucle
     lireDernieresDonneesBUT = memo.lire(3+lecture4);       //Trouver la donnée correspondante en fonction du pointeur de la boucle en lui ajoutant 7
                                                            //TODO:éviter un décalage trop important entre valeurs antérieures ou ultérieures
     if(lireDernieresDonnees != 255)
     {                                                      //Si la donnée n'est pas vide ou absente 
       if(lireDernieresDonnees == lireDernieresDonneesBUT)
       {                                                    //Si les valeurs sont identiques 
         actionsPARCOURS[incrPrcrs] = lireDernieresDonnees; //Enregistrer les valeurs dans le tableau 'actionsPARCOURS[3]'
         incrPrcrs++;                                       //Compter
       }
     }
   }
                                                          //TEST
                                                          //i("motif detecte")
  return incrPrcrs == 3;                                  //Si compteur 'incrPrcrs' == 3 alors renvoie true 

}

/*=========================================================*/ 

                                                            /** TROUVER UN MOTIF DE PARCOURS DE RECHARGE **/
                                                            //TODO: intégrer cette fonction dans la libraire Memoire.h ?
                                                            //NOTE: le tableau actionsRECHARGE[3] se met à jour à chaque nouvelle recharge
int actionsRECHARGE[3] = {255,255,255};                     //Conservation en mémoire de travail du parcours sur 3 valeurs

//FONCTION memoParcoursRECHARGE()                           //NOTE:la structure de la fonction est trop rigide!                                 
bool memoParcoursRECHARGE()
{

  static int pointeurMEMOincrement = memo.increment-1;      //Variable qui pointe vers la dernière adresse mémoire pleine
                                                            //Lire la donnée d'actions correspondante à 'pointeurMEMOincrement'
  static unsigned char lectureMEMOincrement = memo.lire(pointeurMEMOincrement); 
  static int lectureDONNEEincrement = 0;                    //Variable de lecture de la donnée (memo.lire())
  static unsigned char incrementEXISTE = 0;                 //Compteur d'adresses mémoire utilisées
  static unsigned char parcoursRechargeEXISTE = 0;          //Compteur cellule remplie dans tab 'actionsRECHARGE[3]'
  static bool indexRECHARGEtrouve = 0;                      //Interrupteur

  if(lectureMEMOincrement == 7)
  {                                                         //Si la valeur de l'action correspondante à 'pointeurMEMOincrement' correspond à la recharge 
                                                            //vérifier que memo.increment existe sur x valeurs (sécurité) 
    for(int existeMEMOincrement = pointeurMEMOincrement-2;existeMEMOincrement <= pointeurMEMOincrement;existeMEMOincrement++)
    {                                                       //Boucle pour explorer les valeurs de memo.increment à partir du pointeur 'lectureMEMOincrement'
      if(existeMEMOincrement > 0)
      {                                                     //Si le pointeur renvoie une valeur positive
        incrementEXISTE++;                                  //Compter les valeurs positives
      }
    }
    
    if(incrementEXISTE >= 3)
    {                                                       //s'il y a au moins 3 adresses mémoires pleines
      for(unsigned char ldi = 0;ldi <= 2;ldi++)
      {                                                     //Boucle d'exploration des adresses mémoires
        lectureDONNEEincrement = memo.lire(lectureMEMOincrement-ldi);
    
        if(lectureDONNEEincrement == 7)
        {                                                   //Si l'index de recharge est détectée
          indexRECHARGEtrouve = 1;                          //L'interrupteur est activé et la fonction renvoie false
        }
        
        if(indexRECHARGEtrouve != 1)
        {                                                   //Si aucune donnée correspondant à l'index RECHARGE n'a été trouvée 
          actionsRECHARGE[ldi] = lectureDONNEEincrement;    //Enregistrement de donnnée dans tab (la donnée la plus ancienne est en premiere entrée du tableau actionsRECHARGE[0])              
        }       
      }
    }    
  }
                                                            //S'arrurer que le tableau 'actionsRECHARGE[3]' soit rempli à 100%
                                                            //NOTE: cette condition pourra évoluer en fonction du nombre d'actions que pourra contenir 'actionsRECHARGE[3]'
  for(unsigned char valAR = 0;valAR <= 2;valAR++)
  {                                                         //Boucle pour explorer le tableau 'actionsRECHARGE[3]'
    if(actionsRECHARGE[valAR] != 255)
    {                                                       //Si actionsRECHARGE[valAR] contient une action
      parcoursRechargeEXISTE++;                             //Compter
    }
  }

  return parcoursRechargeEXISTE == 3;                       //Si on compte 3 actions enregistrées dans le tableau 'actionsRECHARGE[3]'

}

/*=========================================================*/

                                                            /** RESPECT DES DELAIS D'EXECUTION **/
                                                            //Fonction loopEXECUTION(delai de l'exécution de l'action)
int loopEXECUTION(int DELAIEXECUTION)
{   

  static int delaiExecutionF = 0;
  static bool interrupteurEXECUTION = 0;
  
  if(interrupteurEXECUTION == 0){     
    delaiExecutionF = DELAIEXECUTION;     
    interrupteurEXECUTION = 1;
                                                            //TEST
                                                            //i(delaiExecution)
  }else{
    delaiExecutionF--;
                                                            //i(delaiExecution)
  }
  if(delaiExecutionF == 0)
  {                                                         //Si delaiExecution <= 0 => mémo action + enregistrement
    interrupteurEXECUTION = 0;                              //Réinitialiation de l'interrupteur
                                                            //Mémorisation de l'action qui entrainera le déplacement du pointeur d'adresse mémoire
  }
  return delaiExecutionF;
}

/*=========================================================*/  
 
                                                            /** EXECUTION D'UNE SEQUENCE DE MOUVEMENTS REPETITIVES **/
                                                            //Rustine: je mise sur un délai stable d'exécution de la boucle loop() en index à 136ms pour exécuter les différentes actions (la fonction servo.oscillateur(120) utilise un delai de 120ms)
                                                            //Note: si obstacles rencontrés à nouveau lors de la restitution du parcours, la fonction s'arrête
                                                            //=> il faut limiter certains temps de mouvement pour éloigner le robot des obstacles (?)

const unsigned char delaiMOYENboucle = 136;                 //Délai moyen d'une boucle void loop()
int curseurMemoire = 0;                                     //Pointer de données sur tableaux actionsRECHARGE[3] ou actionsPARCOURS[3] 
//FONCTION executionParcours()
void executionParcours(unsigned char typePARCOURS)
{ 
   
  static int delaiExecution = 0;                            //Conversion du délai en nombre de loop (136ms en moyenne) à effectuer 
  static bool interrupteurRECULER = 0;                      //Interrupteur de tactique REFLEXE FACE AVANT pour exécution du délai 
  static int valdelaiExecutionF = 0;                        //Variable qui contient la fonction loopEXECUTION(délai de l'éxécution de l'action en ms)
  
  //Si memoParcoursRECHARGE() == true, 
  //Ou si actionsRECHARGE[3] est complet 
  //réaliser parcours RECHARGE, ne pas oublier de tourner le véhicule à 180°
  //Utiliser le tableau actionsRECHARGE[3]
  //Incrémenter les boucles : lorsque l'incrément atteint 3 valeurs, incrément reprend la valeur 0
  //Si memoParcours() == true : réaliser une séquence de mouvements dedondante
  //Utiliser le tableau actionsPARCOURS[3]
  //Incrémenter les boucles : lorsque l'incrément atteint 3 valeurs, incrément reprend la valeur 0
                                                                                                               
  unsigned char lireDonneesSequence = 0;                    //Lire la donnée correspondante

                                                            //L'exécution du parcours de recharge est prioritaire!
  if(typePARCOURS == 0)
  {                                                         //Si la fonction memoParcoursRECHARGE() renvoie true
                                                            //Lire la donnée d'action que cible le pointeur 'curseurMemoire' sur le tableau actionsPARCOURS[]   
    lireDonneesSequence = memo.lire(actionsRECHARGE[curseurMemoire]);   
                                                            //TODO: Faire demi-tour  
        
  }else if(typePARCOURS == 1)
  {                                                         //Sinon si la fonction memoParcours() renvoie true
                                                            //Lire la donnée d'action que cible le pointeur 'curseurMemoire' sur le tableau actionsPARCOURS[]   
    lireDonneesSequence = memo.lire(actionsPARCOURS[curseurMemoire]);    
  }
    
  if(lireDonneesSequence != 0)
  {                                                         //Si détection d'une séquence répétitive 
    
    led.jauneIsole();                                       //Allumer LED jaune
    f.compteurIntervalle = 0;                               //Réinitialisation du compteur de l'enregistrement auto toutes les 99 secondes

    unsigned char calculPrcrs = lireDonneesSequence / 10;   //Récupérer le préfixe   
    
                                                            //Moulinette de décomposition des données EEPROM et éxécution des actions
                                                            //TODO: intégrer la variation d'un délai d'une boucle loop()
                                                            //TODO: convertir en switch
    if(lireDonneesSequence >= 10 && lireDonneesSequence <= 14)
    {                                                       //Exécuter la tactique AVANCER
      delaiExecution = ceil(200/delaiMOYENboucle);          //Délai fixé à 200 (voir fonction progressif() de la page SCORE.h)
      valdelaiExecutionF = loopEXECUTION(delaiExecution);   //Note: la fonction loopEXECUTION(delaiExecution) insérée dans une variable s'exécute
      AVANCER;
    }else if(lireDonneesSequence >= 101 && lireDonneesSequence <= 199)
    {                                                       //Exécuter la marche normale AVANCER
                                                            //Délai: retirer la centaine et convertir les secondes en millisecondes
      delaiExecution = ceil(((lireDonneesSequence-100)*1000)/delaiMOYENboucle); 
      valdelaiExecutionF = loopEXECUTION(delaiExecution);   
      AVANCER;        
    }else if(calculPrcrs == 2)
    {                                                       //Exécuter la tactique RECULER
      delaiExecution = ceil(200/delaiMOYENboucle);          //Délai fixé à 200 (voir fonction progressif() de la page SCORE.h)
      valdelaiExecutionF = loopEXECUTION(delaiExecution);
      RECULER;
    }else if(calculPrcrs == 3)
    {                                                       //Exécuter la tactique GAUCHE
      delaiExecution = ceil(300/delaiMOYENboucle);          //Délai fixé à 300 (voir fonction progressif() de la page SCORE.h)  
      valdelaiExecutionF = loopEXECUTION(delaiExecution);    
      GAUCHE;
    }else if(calculPrcrs == 4)
    {                                                       //Exécuter la tactique DROITE
      delaiExecution = ceil(300/delaiMOYENboucle);          //Délai fixé à 300 (voir fonction progressif() de la page SCORE.h)  
      valdelaiExecutionF = loopEXECUTION(delaiExecution);    
      DROITE;
    }else if(calculPrcrs == 5)
    {                                                       //Exécuter la tactique REFLEXE FACE AVANT  
                                                            //TODO: simplifier!  
      if(interrupteurRECULER == 0){  
        delaiExecution = ceil(500/delaiMOYENboucle);     
        valdelaiExecutionF = loopEXECUTION(delaiExecution);
        if(valdelaiExecutionF != 0){
          RECULER;
        }
      }
      if(valdelaiExecutionF == 0){
          interrupteurRECULER = 1;             
      }
      //TOURNER A GAUCHE    
      if(interrupteurRECULER == 1){
        delaiExecution = ceil(250/136);
        valdelaiExecutionF = loopEXECUTION(delaiExecution);
        if(valdelaiExecutionF != 0){
          GAUCHE;
        }
        if(valdelaiExecutionF == 0){
            interrupteurRECULER = 0; 
        }      
      }
    }else if(calculPrcrs == 6)
    {                                                       //Exécuter la tactique REFLEXE FACE ARRIERE
      delaiExecution = ceil(250/136);
      valdelaiExecutionF = loopEXECUTION(delaiExecution);
      GAUCHE;                                               //Temps de déplacement à gauche non mentionné => délai arbitraire
    }
   
    if(valdelaiExecutionF == 0)
    {                                                       //Tant qu'il n'y aura pas d'enregistrement, le programme effectuera la même action
      memo.ecrire(lireDonneesSequence);                     //Enregistrement en EEPROM de l'action exécutée  
      curseurMemoire++;                                     //Lire la donnée suivante 
      if(curseurMemoire == 3)
      {                                                     //Si le pointeur curseurMemoire cible une entrée qui n'existe pas (3)
                                                            //TODO: Rendre modulable en fonction du nombre d'entrée dans le tableau parcouru
         curseurMemoire = 0;                                //Réinitialiser le compteur/pointeur   
      }
    }

  }

}

/*=========================================================*/


#endif  
