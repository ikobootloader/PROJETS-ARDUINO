# Apprentissage par renforcement sans état terminal — Archive de recherche

> **Note** : Ce dépôt est une archive personnelle. Il documente une démarche de recherche amateur conduite indépendamment, puis optimisée avec l'assistance de l'IA. Le code et les concepts sont mis à disposition à titre de référence, sans garantie de complétude ni de robustesse.

---

## Contexte

Ce projet est né d'un problème concret : concevoir un agent robotique autonome capable de naviguer dans un espace inconnu, de localiser des points de recharge, et de gérer son énergie — le tout sur un microcontrôleur embarqué de type Arduino Uno aux ressources très contraintes.

La contrainte matérielle a imposé de trouver des alternatives légères aux algorithmes classiques du reinforcement learning (Q-learning notamment), jugés trop gourmands en mémoire et en calcul pour ce contexte.

---

## Principes fondamentaux

### L'agent

L'agent évolue dans un territoire discrétisé en grille cartésienne. Chaque coordonnée de cette grille possède une *valeur d'état* (Ve). L'agent dispose de quatre actions possibles (haut, bas, gauche, droite) et d'une batterie qu'il doit recharger périodiquement.

Son comportement est régi par deux modes :

- **Exploitation** : quand la batterie est faible, l'agent suit le gradient des valeurs d'état vers le point de recharge le plus proche.
- **Exploration** : quand la batterie est suffisante, l'agent explore le territoire pour découvrir de nouveaux points de recharge ou identifier des obstacles.

La transition entre ces deux modes est gérée par un **ε-greedy booléen** indexé sur le niveau de charge de la batterie — une simplification volontaire adaptée aux contraintes embarquées.

### Propagation de la récompense

Lorsqu'un point de recharge est découvert, sa coordonnée reçoit la valeur 1. Cette valeur se propage sur l'ensemble du territoire connu via l'exponentiation du facteur d'escompte γ en fonction de la distance de Manhattan :

$$Ve(x, y) = \gamma^{|x - R(x)| + |y - R(y)|} \cdot Z$$

Pour plusieurs récompenses simultanées :

$$Ve(x, y) = \sum_{i=1}^{n} \gamma^{|x - R_i(x)| + |y - R_i(y)|} \cdot Z_i^+$$

Cette propagation est qualifiée d'**onde carrée** : elle s'étend de façon isotrope sur les quatre quadrants à partir de la coordonnée récompense, ce qui correspond mathématiquement à une transformation de distance de Manhattan normalisée (voir ci-dessous).

La valeur d'état est une variante simplifiée de l'équation de Bellman :

$$V(s) = \gamma \cdot V(s')$$

où `max(a)` est découvert dynamiquement à chaque changement d'état, sans être mémorisé.

### Navigation par gradient

L'agent retrouve son chemin vers la récompense en calculant à chaque pas :

$$\text{argmax}(V(s') - V(s)) \Rightarrow \text{argmax}(f)$$

La meilleure action est celle qui maximise l'écart entre la valeur d'état de la position suivante et la position actuelle. En cas d'égalité entre plusieurs directions, la préférence est donnée à la continuité du mouvement en cours (voir section *Principe de moindre action* ci-dessous).

---

## Recherches non abouties

### 1. Principe de moindre action appliqué à la trajectoire

Un point qui distingue cette approche des formulations standard : **la meilleure action n'est pas seulement celle qui maximise Ve+1, mais celle qui minimise les changements de direction.**

La justification est physique : chaque virage impose des contraintes mécaniques (force centrifuge, perte d'énergie cinétique) à un agent réel se déplaçant à vitesse non nulle. La règle proposée est :

$$\vec{a}_{n+1} = \vec{a}_n \quad \text{si } Ve(\vec{a}_{n+1}) \geq Ve(\vec{a}_k) \text{ pour tout } k \neq n+1$$

Autrement dit, l'agent maintient sa direction courante tant qu'elle mène vers une valeur d'état au moins aussi bonne que toute alternative disponible. Ce n'est qu'en l'absence d'une telle direction que l'agent tolère un changement de cap. La variation de vitesse angulaire est idéalement nulle :

$$\omega = 0 \quad \Rightarrow \quad \Delta\vec{a} = \vec{a}_1 - \vec{a}_0 = \vec{0}$$

Cette contrainte n'est pas habituelle dans les formulations RL sur grille, qui traitent généralement toutes les actions comme équivalentes en coût. Elle introduit implicitement une **inertie directionnelle** sans avoir à modéliser explicitement la dynamique physique de l'agent.

### 2. ε-greedy de moindre action — exploration en spirale carrée

L'exploration aléatoire est remplacée par une **spirale carrée d'Archimède** centrée sur la dernière position de recharge. Ce choix repose sur le même principe : minimiser la complexité des mouvements (nombre de virages) tout en couvrant le territoire de façon exhaustive.

La longueur du côté parcouru à l'anneau n est :

$$L_n = 2(n + 1) \quad \text{cases, avec une rotation de 90° sens horaire à chaque anneau } n \geq 0$$

Dans un espace sans obstacles, c'est la stratégie de couverture optimale en termes de nombre de changements de direction. En présence d'obstacles, un repli vers un mouvement en signal carré est envisagé, la décision étant prise dynamiquement en fonction de ce que l'agent détecte à distance.

### 3. Synthèse des schèmes par moyenne des récompenses propagées

Quand plusieurs récompenses coexistent (positives et négatives), une **synthèse par moyenne** des valeurs d'état propagées est proposée pour chaque coordonnée :

$$\overline{Ve}(x,y) = \frac{1}{n} \sum_{i=1}^{n} Ve_i(x,y)$$

Cela permet à l'agent de ne pas se satisfaire d'une récompense faible si une récompense plus forte est accessible, et d'éviter naturellement les zones à récompenses négatives sans avoir à propager celles-ci avec un gamma distinct.

Une normalisation via sigmoïde est également explorée pour borner les valeurs moyennes dans ]0, 1[ :

$$f\bigl(\overline{Ve}\bigr) = \frac{1}{1 + e^{-\,\overline{Ve}(x,y)}}$$

Le désavantage identifié est la perte de précision par arrondi, et la convergence de la sigmoïde vers 1 pour des récompenses positives élevées, ce qui peut effacer les différences entre récompenses fortes.

### 4. Propagation sectorisée pour grands territoires

Pour les territoires dépassant les capacités mémoire d'un microcontrôleur (même avec EEPROM externe), une propagation **secteur par secteur** est proposée : le territoire est divisé en secteurs de dimensions fixes, et la propagation d'un secteur initialise le secteur adjacent à partir des valeurs de la ligne limitrophe entre les deux secteurs.

> **Note** : la formule de mise à jour sectorisée est à l'état d'ébauche dans les documents source et n'est pas encore stabilisée. L'idée directrice est que la valeur d'état d'un secteur nouvellement découvert est initialisée à partir des valeurs Ve de la ligne limitrophe avec le secteur précédent, puis propagée par exponentiation de γ comme pour le territoire global.

### 5. Gestion de la précision sur systèmes embarqués

Avec γ = 0.90 et un territoire de 1 000 états, les valeurs d'état descendent en dessous de 10⁻⁴⁴, ce qu'un Arduino Uno interprète comme 0 — rendant la navigation par gradient impossible. La solution proposée est d'ajuster γ dynamiquement en fonction de la taille estimée du territoire :

$$\gamma \to 1^- \quad \text{ex. } \gamma = 0{,}9999 \text{ pour } 100\,000 \text{ états}$$

Une alternative envisagée est de substituer des entiers aux flottants dans l'implémentation bas niveau, la valeur d'état étant alors représentée comme un entier sur un octet (0–255).

---

## Lien avec les concepts établis

Sauf équation de Bellman, ces travaux ont été conduits indépendamment avant que leurs équivalents académiques soient identifiés. Les correspondances sont les suivantes :

| Concept développé ici | Équivalent dans la littérature |
|---|---|
| Propagation de récompense par γ | Équation de Bellman / Programmation dynamique |
| Onde carrée de valeurs d'état | Transformation de Distance (Manhattan) / Champ de potentiel (Khatib, 1986) |
| Grille de territoire avec obstacles | Occupancy Grid (Moravec & Elfes, 1985) |
| Synthèse des schèmes | Reward shaping / Potential-based rewards |
| Inertie directionnelle (moindre action) | Peu formalisé dans le RL sur grille — contribution potentiellement originale |
| Exploration en spirale carrée | Couverture complète (coverage path planning) — formulation spécifique originale |

La note d'édition de juin 2025 dans les documents source identifie également le lien avec les **Signed Distance Fields (SDF)** et leur usage dans le deep learning moderne (DeepSDF), ainsi qu'avec l'ingénierie de caractéristiques pré-deep learning (HOG, SVM).

## Statut

Archive. Pas de développement actif prévu. Le code source inclut la version optimisée par IA des algorithmes de propagation et de navigation décrits dans les documents de recherche.

---

*Frédéric Murat — Recherche personnelle, de 2023 à 2026 pour ce README.md