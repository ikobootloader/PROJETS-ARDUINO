#ifndef SCORE_H
#define SCORE_H

/*
 * 
 * SYSTEME DE RECOMPENSE : SCORE
 * DEFINITION D'UNE ECHELLE DE VALEUR POUR LES TACTIQUES D'EVITEMENT 
 * S'APPLIQUE POUR CHAQUE POSITION DU SVM
 * 
 */

/*=========================================================*/ 

//INIT VARIABLES
/** CREATION D'UNE MATRICE DE SCORE **/
//Composition de matriceSCORE : 5 colonnes correspondent aux positions du servomoteur (Observations de l'environnemment), 
//                              4 valeurs notées de 1 à 4 correspondent aux tactiques (Actions), 
//                              4 valeurs de 0 à 3 correspondent au score (Récompenses)
//Aide mémoire : matriceSCORE[indexPOSITIONSVM][indexTACTIQUE-1][0] => pointe sur l'index de la tactique 
//               matriceSCORE[indexPOSITIONSVM][indexTACTIQUE-1][1] => pointe sur la valeur du score
                                                            //POSITIONS SVM
unsigned char matriceSCORE[5][4][2] = {{{1,0},{2,0},{3,0},{4,0}},      //5°
                                       {{1,0},{2,0},{3,0},{4,0}},      //45°
                                       {{1,0},{2,0},{3,0},{4,0}},      //90°
                                       {{1,0},{2,0},{3,0},{4,0}},      //135°
                                       {{1,0},{2,0},{3,0},{4,0}}};     //175°

/*=========================================================*/ 

                                                            /** MOUVEMENT ET CONTROLE CONTRE LES COLLISIONS **/
                                                            //TODO: toutes les fonctions de déplacement et de sécurité devraient se situer dans une page à part entère
                                                            //FONCTION progressif(tactique)
                                                            //Fonction permettant de contrôler la vitesse de mouvement du robot en fonction de sa distance avec l'obstacle
                                                            //Plus l'obstacle est proche du robot plus celui-ci se déplace lentement
                                                            //Le paramétrage de cette fonction est adapté au montage du prototype
unsigned char progressif(unsigned char actP)
{ 
  unsigned short delaiNormal = 0;                           //Définition du délai normal de mouvement      
  unsigned int distanceObstacle = 0;                        //Variable contenant la distance vers l'obstacle                                                        
  
  if(actP == 0 || actP == 1)                                //Si la tactique d'évitement est avancer ou reculer 
  {
      delaiNormal = 100;                                    //Délai normal de mouvement fixé à 150ms (si modification ici, modifier également PARCOURS.h)    
                                                            //ultrason.measureDistanceCm() est un objet de la Bibliothèque HCSR04.h
                                                            //Prise en compte d'un bug du capteur qui peut indiquer la donnée -1     
      ultrason.measureDistanceCm() == -1 ? distanceObstacle = 0 : distanceObstacle = ultrason.measureDistanceCm();
      distanceObstacle = map(distanceObstacle,0,20,0,100);  //La fonction native map() permet d'effectuer une conversion en proportionnalité d'une valeur d'entrée vers une valeur de sortie
                                                            //Pour map(distanceObstacle,0,20,0,100) : 
                                                            //une valeur d'entrée (distanceObstacle) 
                                                            //se situant entre 0 et 20cm (0,20), 
                                                            //produira une valeur proportionnelle de sortie (utilisée dans la fonction delay()) se situant entre 0 et 100 (0,100) 
      if(distanceObstacle <= 20)
      {                                                     //Si la distance à l'obstacle est inférieure ou égale à 20cm
                                                            //Le robot effectue le mouvement avec une vitesse dépendante de la fonction delay()
                                                            //Le délai dépend de la valeur de sortie de la fonction map()
                                                            //VOITURE.locomotion() est un objet de la Bibliothèque Voiture.h
        VOITURE.locomotion(actP,255),delay(distanceObstacle);   
      }else{                                                //Sinon, si la distance vers l'obstacle est supérieure à 20cm
        VOITURE.locomotion(actP,255),delay(delaiNormal);    //le délai normal est fixé à 150
      }
  }
  if(ultrason.measureDistanceCm() >= maxDistance/2)
  {                                                         //Si la distance est supérieure à maxDistance (20cm, voire page index IA_ROBOT_MEMOIRE_X)
    if(actP == 2 || actP == 3)                              //Concerne uniquement les tactiques GAUCHE et DROITE
    {
      delaiNormal = 400;                                    //Délai normal de mouvement fixé à 300ms 
      VOITURE.locomotion(actP,255),delay(delaiNormal);  
    }
  }
}

/*=========================================================*/ 

                                                            /** MOUVEMENT EFFECTUE LORS DU TEST **/
                                                            //FONCTION testerTACTIQUE(tactique)
unsigned char testerTACTIQUE(unsigned char reference)
{                                                           //Réaliser une tactique en fonction du résultat de la fonction score(positionSVM)
  
  //TODO:TESTER
  const unsigned char tab[4][4] = {{1,progressif(0)},
                                   {2,progressif(1)},
                                   {3,progressif(2)},
                                   {4,progressif(3)}};
                                                           //TEST
                                                           i(reference == 1 ? "AVANT" : "")
                                                           i(reference == 2 ? "RECUL" : "")
                                                           i(reference == 3 ? "GAUCHE" : "")
                                                           i(reference == 4 ? "DROITE" : "")
  return tab[reference][1];

}

/*=========================================================*/ 

                                                            /** RECOMPOSER matriceSCORE EN FONCTION DE LA MEILLEURE TACTIQUE TESTEE POUR UNE POSITION SVM DONNEE **/
                                                            //FONCTION recompositionMatrice(positionSVM, tactique)
                                                            //NOTE:cet algorithme est un système de permutation automatique des scores
                                                            //Le principe est que la permutation du score antérieur x vers le score ultérieur limite y (ici 3)
                                                            //impose derechef une diminution de -1 des autres scores si ceux-ci ont une valeur > 0
                                                            //La diminution des autres scores commence à partir de "score antérieur + 1" et se poursuit vers le score ultérieur limite.
                                                            //En outre, un score antérieur = score ultérieur ne vérifie pas cette propriété
void recompositionMatrice(unsigned char pSVM, unsigned char scoreDorigine, unsigned char tactique)
{                                                     
  for(unsigned char f = (scoreDorigine+1); f <= 3;f++)
  {    
    if(f != tactique && matriceSCORE[pSVM][f][1] > 0)
    {       
      matriceSCORE[pSVM][f][1] = matriceSCORE[pSVM][f][1] - 1;
    }         
  }                
}

/*=========================================================*/ 

                                                            /** RECOMPOSER matriceSCORE EN FONCTION DE LA TACTIQUE LA PLUS FREQUENTE POUR UNE POSITION DU SVM DONNEE **/
                                                            //FONCTION souvenirScore(positionSVM)
void souvenirScore(int pstnSVM)
{                                                           
   unsigned char souvenirAction = 0;
   unsigned char scoreDOrigine = 0;
                                                            //occurrencesSCORE() est une fonction de la page MEMORY.h
   souvenirAction = occurrencesSCORE(pstnSVM);              //Récupérer la tactique la plus fréquemment utilisée pour la position du SVM
                                                            //TEST
                                                            //i("occurrencesSCORE : Tactique la plus fréquente")
                                                            //i(souvenirAction)
                                                            //La tactique la plus fréquemment utilisée pour un type de position est présumée être la meilleure 
                                                            //matriceSCORE devra être modifiée au besoin
                                                            
   bool pasDeChangement = 0;                                //Interrupteur
   unsigned char meilleureTACTIQUE = 0;                     //variable qui sera associée à la tactique dont le score est le plus haut
    
    if(souvenirAction != 0)
    {                                                       //Si la fonction occurrencesSCORE() renvoie une valeur qui n'est pas nulle, soit l'index d'une tactique
                                                            //Vérifier la correspondance entre les valeurs actuelles de matriceSCORE et celle issue de la fonction occurrencesSCORE()                                 
                                                            //Si l'index de la tactique inscrite dans matriceSCORE n'est pas identique à l'index de la tactique récupérée dans occurrencesSCORE()                                                                                                   
                                                            //Modifier la matriceSCORE en fonction du résultat de occurrencesSCORE(pstnSVM)
        for(int chercheP = 0; chercheP <= 3; chercheP++)
        {
          if(matriceSCORE[pstnSVM][chercheP][0] == souvenirAction && matriceSCORE[pstnSVM][chercheP][1] != 3)
          {                                                 //Pour la tactique dont l'index est égal à celui récupéré dans la fonction occurrencesSCORE()
            meilleureTACTIQUE = chercheP;                   //Enregistrer la nouvelle valeur de score (3) pour la tactique concernée
            scoreDOrigine = matriceSCORE[pstnSVM][meilleureTACTIQUE][1];
            matriceSCORE[pstnSVM][meilleureTACTIQUE][1] = 3;
            pasDeChangement = 1;
          }
        }                                                   //Recomposer matriceSCORE en fonction de la tactique dont le score est dorénavant le plus haut                                                             
        if(pasDeChangement == 1){
         recompositionMatrice(pstnSVM,scoreDOrigine,meilleureTACTIQUE);             
        }
    }  
}

/*=========================================================*/ 

void reflexeFaceAvant()                                     /** REFLEXES FACE AVANT **/
{                                                           //TODO:insérer les fonctions d'évitement dans une page à part
  for(unsigned char prg = 0;prg <= 250;prg++)
  {                                                         
    if(IR.detection() == false)                             //detectionArriere() est une fonction de la page INFRAROUGE.h
    {                                                       //Si pas de détection d'un obstacle sur la face arrière
                                                            //TEST
                                                            //i("Recul de réflexe")          
     RECULER,delay(1);                                      //Recul progresif du robot
    }
  }  
  GAUCHE,delay(400);                                        //Le robot tourne à gauche sur 300ms                                    
  ARRET,delay(500);                                         //Le robot s'arrête sur 500ms   
  memo.ecrire(5);                                           //Mémorisation du réflexe    
}

/*=========================================================*/ 

                                                            /** SCORE **/
                                                            //S'il y a détection d'un obstacle, les tactiques d'évitement sont testées tour à tour.
                                                            //L'index de la tactique qui parvient à éviter l'obstacle est conservé en mémoire avec la position du SVM concernée
                                                            //FONCTION score(positionSVM)
void score(int positionSM)
{
  static bool reaction = false;                             //Interrupteur
                                                            //Si "true" la tactique a fonctionné pour éviter l'obstacle 
  static int actPrinc = 0;                                  //Initialisation de la variable qui sera à la tactique déjà testée
  static bool stopMemo = 0;                                 //Interrupteur pour ne pas mémoriser plusieurs fois via memoInstantTAvancer()
                                                            //memoInstantTAvancer() est une fonction de la page MEMORY.h
                                                            //stopMemo est une variable de la page MEMORY.h 
                                                            //TEST
                                                            //i("stopmemo")
                                                            //i(stopMemo)
  if(stopMemo != 1)
  {                                                         // mémorisation action AVANCER + quantité de secondes a l'instant où il y détection d'obstacle
    memoInstantTAvancer();
                                                            //TEST
                                                            //i("score:enregistrement du temps de marche")
                                                            //i("stopmemo")
                                                            //i(stopMemo)
  }                 
  
  //INIT VARIABLES DE SCORE
  actPrinc = 0;                                             //Tactique déjà testée  
  reaction = false;                                         //variable 'reaction' réinitialisée à false

  //Respecter classement
  bool pasDeChangement3, pasDeChangement4 = 0;              //Interrupteurs
  unsigned char tactiqueSCOREegale3 = 0;
  unsigned char scoreDorigineSurTactique = 0;

  ARRET,delay(500);//ARRET ROUES 

  //JAUGE
  for(int seq = 3; seq >= 0; seq--)
  {                                                         //La boucle (seq) dénombre du plus haut score (3) au plus bas
    for(int chkJ = 0; chkJ <= 3; chkJ++)
    {                                                       //La boucle (chkJ) dénombre les index associés aux tactiques
      if(matriceSCORE[positionSM][chkJ][1] == seq && reaction == false && matriceSCORE[positionSM][chkJ][0] != actPrinc)
      {                                                     //Si le score est égal à la variable 'seq' (variable de la boucle de dénombrement)
                                                            //Et si la variable 'reaction' (indique si une tactique a fonctionné) est à false
                                                            //Et si la tactique pointée dans matriceSCORE est différent de 'actPrinc' (tactique testée précédemment)
                                                            //TODO: changer le nom de la variable 'actPrinc' en 'tactiqueDEJATESTEE'                                                           
                                                            //Tester la tactique sur laquelle la boucle pointe
          testerTACTIQUE(matriceSCORE[positionSM][chkJ][0]);
                                                            //TEST        
                                                            //i(actPrinc)
          ARRET,delay(500);                                 //Arrêt des roues pendant 500ms
          
          if(ultrason.measureDistanceCm() > maxDistance)
          {                                                 //Si la distance à l'obstacle est supérieure à la limite fixée dans maxDistance (20, voir page index)
            for(unsigned char e = 0; e <= 3;e++)
            {                                               //Chercher si la tactique qui possède un score à 3 existe déjà
              if(matriceSCORE[positionSM][e][1] == 3)
              {                                             //Si le score est égale à 3
                tactiqueSCOREegale3 = e;                    //L'index de la tactique est associée à la variable tactiqueSCOREegale3                                                                                    
              }
            }
                                                            //Capturer la valeur du score précédent
            scoreDorigineSurTactique = matriceSCORE[positionSM][chkJ][1];                                               
            matriceSCORE[positionSM][chkJ][1] = 3;          //Enregistrer la nouvelle valeur de score (3) pour la tactique concernée 
                                                            //TEST
                                                            //i("TACTIQUE PRINCIPALE A FONCTIONNE")       
  
                                                            //Mémorisation en EEPROM de l'index de la tactique d'évitement suivi de l'index de position du SVM
            memoInstantT(matriceSCORE[positionSM][chkJ][0],positionSM);                            
                
                                                            //Ne pas checker si même action est répéter pour éviter l'obstacle !!
            if(chkJ != tactiqueSCOREegale3)
            {                                               //Si l'index de la tactique associée à la variable tactiqueSCOREegale3 est différent de celui qui possède un score à 3
                                                            //Il faut Recomposer matriceSCORE en conséquence
              recompositionMatrice(positionSM, scoreDorigineSurTactique, chkJ);        
            }
                          
            reaction = true;                                //Si "true" la tactique a fonctionné pour éviter l'obstacle 
            stopMemo = 0;                                   //Interrupteur
          }else{ 
            //reaction = false;                               //TODO: est-ce nécessaire de conserver cette variable à cet endroit ?
                                                            //Conserver l'index de la tactique qui vient d'être testé et qui n'a pas fonctionné pour ne pas la retester à nouveau lors de la prochaine boucle
            actPrinc = matriceSCORE[positionSM][chkJ][0];         
            stopMemo = 1;                                   //Interrupteur
          } 
       }
    }
  }    
  
  if(reaction == false)
  {                                                         //Si "false", aucune tactique n'a fonctionné pour éviter l'obstacle
                                                            //Fusionner variables 'reaction' et 'stopMemo'
                                                            //TEST
                                                            //i("RIEN A FONCTIONNE")                                                                                                    
    reflexeFaceAvant();                                     //Activation de la fonction reflexeFaceAvant()
    stopMemo = 0;                                           //Interrupteur
                                                            //TODO: problème est que s'il y a nouvelle boucle de tests il y aura mémorisation memoInstantTAvancer()
  }
                                                            //f.compteurIntervalle est une fonction de la Bibliothèque Fonctions.h                                                      
  f.compteurIntervalle = 0;                                 //Réinitialisation du compteur f.compteurIntervalle

}

/*=========================================================*/ 

                                                            /** VERIFICATION DU SCORE**/
                                                            //Fonction uniquement destinée aux tests
                                                            //Fonction verificationScore(positionSVM)
unsigned char verificationScore(unsigned char pos){


  //TODO:TESTER
  const unsigned char tab2[5][5] = {{0,5},
                                    {1,45},
                                    {2,90},
                                    {3,135},
                                    {4,175}};

  return i(tab2[pos][1])

  Serial.println(F("________________________"));
  for(int test = 0;test <= 3;test++){i(matriceSCORE[pos][test][1])}  
  Serial.println(F("________________________"));    
}

/*=========================================================*/

#endif
