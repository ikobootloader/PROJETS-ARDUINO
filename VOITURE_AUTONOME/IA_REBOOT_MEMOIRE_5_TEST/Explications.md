# Modèle expérimental d’agent autonome adaptatif embarqué

## Introduction

Ce projet est une expérimentation personnelle autour d’un petit agent autonome embarqué sur microcontrôleur de type Arduino.

L’objectif n’était pas de créer une intelligence artificielle au sens académique du terme, ni un véritable système de machine learning moderne, mais plutôt un mécanisme léger permettant à un robot autonome d’adapter progressivement ses choix comportementaux en fonction de ses interactions passées avec l’environnement.

Le système repose principalement sur :

* des scores ;
* une mémoire simplifiée des actions ;
* une hiérarchisation dynamique des choix ;
* et une logique de réorganisation comportementale.

Le projet a été développé avec des contraintes fortes :

* très faible puissance de calcul ;
* mémoire limitée ;
* environnement temps réel ;
* architecture procédurale simple.

---

# Principe général

L’agent possède plusieurs comportements possibles (appelés ici “choix” ou “tactiques”).

Exemples :

* tourner à gauche ;
* tourner à droite ;
* reculer ;
* avancer ;
* contourner un obstacle.

Chaque choix possède un score ou une priorité qui évolue avec le temps selon les résultats obtenus dans l’environnement.

Le système tente progressivement de favoriser les comportements ayant produit les meilleurs résultats dans le passé.

---

# Architecture globale

Le fonctionnement général peut être résumé ainsi :

```text
Capteurs
→ interaction avec l’environnement
→ sélection d’une tactique
→ exécution
→ observation du résultat
→ mise à jour des scores
→ réorganisation des priorités
```

Le système ne construit pas de modèle mathématique complexe du monde.

Il fonctionne plutôt comme :

* une mémoire comportementale simplifiée ;
* un système de préférences dynamiques ;
* un mécanisme de compétition entre actions possibles.

---

# Mémoire des choix effectués

Le projet conserve un historique simplifié des actions précédemment exécutées.

Cette mémoire sert principalement à :

* détecter les comportements fréquemment utilisés ;
* observer certaines régularités ;
* réorienter les décisions futures.

Le système possède donc une forme de mémoire comportementale discrète.

Cette mémoire n’est cependant ni probabiliste ni neuronale.

---

# Sélection des comportements

L’agent ne choisit pas totalement ses actions au hasard.

Il utilise :

* les scores actuels ;
* les résultats précédents ;
* l’ordre de priorité des tactiques ;
* certaines interactions récentes avec l’environnement.

L’idée générale est :

> les comportements ayant historiquement mieux fonctionné deviennent progressivement prioritaires.

Inversement :

> les comportements inefficaces perdent progressivement de l’importance.

---

# Réindexation des choix

Une caractéristique importante du projet est la “réindexation” des choix.

Le système ne se contente pas d’ajouter ou retirer des points.

Il modifie progressivement l’ordre de priorité des comportements disponibles.

Ainsi :

* les tactiques efficaces remontent dans le classement ;
* les tactiques inefficaces descendent ;
* certaines alternatives restent disponibles comme solutions secondaires.

Ce mécanisme produit une adaptation comportementale simple mais relativement stable.

---

# Interaction avec l’environnement

Le robot interagit avec son environnement via différents capteurs, notamment :

* capteurs de distance ;
* détection d’obstacles ;
* informations de déplacement ;
* mémoire de certaines séquences.

Lorsqu’un comportement produit un mauvais résultat (collision, blocage, échec de déplacement), le système tente généralement une autre tactique mieux classée.

Cette logique permet d’éviter un comportement totalement figé.

---

# Nature réelle du système

Le projet ne constitue pas :

* un réseau de neurones ;
* un modèle de deep learning ;
* un véritable apprentissage par renforcement moderne ;
* ni une IA statistique avancée.

Il s’agit plutôt :

* d’un système heuristique adaptatif ;
* d’un moteur de décision expérimental ;
* d’un mécanisme léger de priorisation dynamique ;
* inspiré intuitivement de notions de mémoire et d’adaptation comportementale.

---

# Points intéressants du projet

Malgré ses limites techniques, le projet possède plusieurs aspects intéressants :

* adaptation incrémentale ;
* très faible coût de calcul ;
* fonctionnement compatible avec du matériel embarqué modeste ;
* comportement partiellement émergent ;
* logique de compétition entre actions ;
* conservation d’un historique comportemental.

Le système produit parfois des comportements donnant l’impression d’une forme de “préférence acquise”, bien que le mécanisme reste entièrement déterministe et relativement simple.

---

# Limites du projet

Le projet présente également de nombreuses limites :

* architecture logicielle peu modulaire ;
* forte dépendance aux variables globales ;
* logique parfois difficile à maintenir ;
* absence de véritable modèle probabiliste ;
* peu de séparation entre perception, décision et action ;
* comportement parfois imprévisible ;
* implémentation expérimentale et non industrielle.

Le code doit donc être considéré comme un prototype exploratoire plutôt qu’une architecture robuste ou académique.

---

# Conclusion

Ce projet représente surtout une tentative artisanale de créer un agent autonome capable :

* de mémoriser certaines expériences ;
* de modifier progressivement ses priorités ;
* et d’adapter ses comportements à son environnement.

L’intérêt du système ne réside pas dans sa sophistication mathématique, mais dans la recherche d’un comportement adaptatif simple, léger et compatible avec des contraintes matérielles très limitées.
