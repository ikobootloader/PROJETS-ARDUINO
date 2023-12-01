  <H1>NOMENCLATURE </H1>
  
  <H2>//////// FONCTIONS SUR VARIABLES ////////</H2>
  
  <H3>//Concaténation de 2 valeurs</H3>
  /*<br>
  int c1= 5;<br>
  int c2 = 99; <br>
  int c3 = f.concatenation(c1,c2); //Retourne 599<br>
  */

  <H2>//////// FONCTIONS SUR LE TEMPS ////////</H2>

  <H3>//Créer une fréquence / minuterie</H3>
  /*<br>
  // f.frequence(limite de temps à insérer en millisecondes)<br>
  f.frequence(1000); //la fonction renvoie true toutes les secondes<br>
  */<br>
<br>
  /***/
<br>
  <H3>//Créer un intervalle de temps à partir de la fonction f.frequence()</H3>
  /*<br>
  bool val  = f.frequence(1000);<br>
  f.intervalle(val,10);<br>
  f.resetIntervalle() permet de réinitialiser à 0 la méthode f.compteurIntervalle <br>
  Le résultat est tjs retourné dans la méthode f.compteurIntervalle <br>
  i(f.compteurIntervalle) <br>
  */<br>

  <H2>//////// FONCTIONS SUR TABLEAUX ////////</H2>

  <H3>//Retourner la taille d'un tableau => SIZE_ARR(tableau);</H3>
  
  //Retourner la valeur la plus courante<br>
  /*<br>
  f.plusFrequent(nom du tableau, taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  f.plusFrequent(tab,SIZE_ARR(tab)) <=> f.plusFrequent(tab,10);<br>
  */<br>
<br>
  /***/<br>
<br>
  <H3>//Trouver la valeur la plus petite</H3>
  /*<br>
  //f.mini(tableau,taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  int val = f.mini(tab,10); //Retourne 0<br>
  i(val)<br>
  */<br>
<br>
  /***/<br>
<br>
  <H3>//Trouver la valeur la plus grande</H3>
  /*<br>
  //f.maxi(tableau,taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7}; //Retourne 9<br>
  int val = f.maxi(tab,10);<br>
  i(val)  <br>
  */<br>
<br>
  /***/<br>
<br>
  <H3>//Trier un tableau dans l'ordre croissant</H3>
  /*<br>
  //f.triAsc(tableau,taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  f.triAsc(tab,10);<br>
  for(int i = 0; i <= 9;i++){<br>
    i(tab[i])    <br>
  }  <br>
  */<br>
<br>
  /***/<br>
<br>
  <H3>//Trier un tableau dans l'ordre décroissant</H3>
  /*<br>
  //f.triDesc(tableau,taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  f.triDesc(tab,10);<br>
  for(int i = 0; i <= 9;i++){<br>
    i(tab[i])    <br>
  }  <br>
  */  <br>
<br>
  /***/<br>
<br>
  <H3>//Inverser un tableau</H3>
  /*<br>
  //f.inverser(tableau,taille du tableau);<br>
  int tab[10] = {0,1,2,4,4,9,6,8,3,7};<br>
  f.inverser(tab,10);<br>
  for(int i = 0; i <= 9;i++){<br>
    i(tab[i])    <br>
  }  <br>
  */ <br>
