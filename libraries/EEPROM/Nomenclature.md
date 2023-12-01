<h1>Nomenlature EERPOM</h1>
<br>

<b>//Class    Objet</b><br>
<span style="color:orange;">MEMOIRE</span>   memo;<br>
<br><br>
  <b>//RESET</b><br>
  //memo.effacer(adresse de départ,adresse d'arrivée);<br>
  <br>
  <b>//ECRIRE</b><br>
  //memo.ecrire(adresse,donnée);<br>
  <br>
  <b>//ADRESSAGE AUTOMATIQUE DE LA DONNEE</b><br>
  //memo.increment (variable d'incrémentation)<br>
  //memo.ecrire(0);  <br>
<br>
  <b>//LIRE UNE ADRESSE</b><br>
  //memo.lire(0);<br>
<br>
  <b>//AFFICHER LES DONNEES SUR LE PORT SERIE</b><br>
  memo.serial(0,5);<br>
    <br>
  <b>//DEFINIR UN POINTEUR D'ENTREE ET UN POINTEUR DE SORTIE EN FONCTION D'UN INTERVALLE</b><br>
  memo.adresseEepromMin = 0;<br>
  memo.adresseEepromMax = 0;<br>
  memo.pointer(30);<br>
