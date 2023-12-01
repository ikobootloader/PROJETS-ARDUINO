# EEPROM TOOLS

FR

Salut!

J'ai écrit cette bibliothèque d'outils pour l'eeprom 24LC256 afin de minimiser la quantité de code dans mes projets.

Il y a d'autres bibliothèques qui proposent ce type d'outils, à l'instar de celle de Rob Tillaart, disponible par défaut dans le gestionnaire de bibilothèque de l'IDE et qui semble compatible pour des puces de capacités différentes. 

Je vous encourage vivement à tester l'EEPROM pour les projets qui nécessitent une mémoire non volatile car c'est un composant léger qui ne sursollicite pas votre microcontrolleur.

Par ailleurs, la fiche technique précise un nombre de cycles d'écriture/suppression supérieur à 1 million et une rétention de l'information supérieure à 200 ans. La puce ATMEGA328P ne dispose pas nativement de ces performances. 

Aussi, cette bibliothèque, comme d'autres, a été pensée pour la communauté francophone.

La plupart des fonctions nécessitent une adresse de début et une adresse de fin. Ces fonctions sont toujours croissantes.

/*********************/

EN

Hi there!

i wrote this librairy of tools because my experiments became often bigger than i thunk at the beginning..

so, i mean it's better to have a librairy to minimize my sketch and use more simply the eeprom 24LC256. 

i think other librairies purpose this kind of stuff but i want to improve my skills in c/c++ and it's a good challenge for me !

most of functions need an address to start and an address to end. address to start is always littlest than the address to end.
