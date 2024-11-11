Voici un résumé des éléments et du fonctionnement (voir le modèle grifonné au format <a href="https://github.com/ikobootloader/PROJETS-ARDUINO/blob/main/VOITURE_AUTONOME/IA_REBOOT_MEMOIRE_5_TEST/mod%C3%A8leIA.jpg" target="_blank">image</a>) :

1. Table des choix disponibles : Cette table contient plusieurs options, numérotées de 1 à 4 dans l'exemple (choix 1, choix 2, etc.). Ces choix sont liés à des interactions avec l'environnement et peuvent varier en fonction des réponses de l'environnement.


2. Environnement et Interaction : Les choix disponibles sont influencés par l'environnement, par exemple dans le cas d'interactions avec des capteurs ou des actions.


3. Algorithme de détection du choix le plus fréquent : Ce bloc observe les choix précédents pour détecter celui qui a été le plus souvent sélectionné, puis l'enregistre comme choix probable pour les décisions futures.


4. Table des choix effectués : Une table linéaire répertorie les choix déjà effectués dans un ordre chronologique, du plus ancien au plus récent. Un mécanisme limite la sélection d'un sous-ensemble de ces choix pour une prise de décision immédiate.


5. Réindexation et réinitialisation : En cas de choix incorrect, le modèle réindexe les choix en fonction de nouvelles interactions avec l'environnement. Si un choix est validé, il est enregistré en mémoire.


Ce modèle suggère un apprentissage par renforcement, où les choix sont ajustés en fonction des interactions avec l'environnement et des choix passés.

***

### Variables et Notations

1. **Ensemble des Choix Disponibles** : Soit $C = \{c_1, c_2, \dots, c_n\}$ l'ensemble des choix disponibles.
2. **Table des Choix Effectués** : Soit $H = [h_1, h_2, \dots, h_m]$ une liste ordonnée des choix effectués dans le passé, avec $h_i \in C$.
3. **Fréquence d'un Choix** : La fréquence d'apparition d'un choix $c \in C$ dans $H$ est notée $f(c)$, définie par :
   $f(c) = \sum_{i=1}^{m} \delta(h_i, c)$
   où $\delta(h_i, c) = 1$ si $h_i = c$ et $0$ sinon.

### Algorithme de Détection du Choix Fréquent

L'algorithme identifie le choix le plus fréquent dans $H$ :
$c_{\text{freq}} = \arg\max_{c \in C} f(c)$
Ce choix $c_{\text{freq}}$ est celui qui a été sélectionné le plus souvent dans l'historique et qui est donc préféré pour les futures décisions.

### Sélection Temporairement Limitée des Choix

L'algorithme ne sélectionne pas automatiquement le choix $c_{\text{freq}}$ à chaque étape, mais il utilise une "fenêtre" de sélection limitée, que nous pouvons appeler $L \subset H$. Par exemple, $L$ peut contenir les $k$ derniers choix de $H$ (donc $L = [h_{m-k+1}, \dots, h_m]$).

La fréquence dans cette sous-séquence $L$ est notée $f_L(c)$, définie par :
$f_L(c) = \sum_{i=m-k+1}^{m} \delta(h_i, c)$
Le choix préféré dans cette fenêtre est donc :
$c_{\text{freq}, L} = \arg\max_{c \in C} f_L(c)$

### Interaction avec l'Environnement

À chaque itération, le système sélectionne un choix $c_t$ et observe la réponse de l'environnement. Si le choix est bon (ou correct selon un critère externe), il est ajouté à $H$. Sinon, le choix est rejeté, et le système tente un choix alternatif dans $C$, ou bien réévalue les choix selon les nouvelles conditions de l'environnement.

### Mécanisme de Réindexation

En cas de mauvais choix (échec d'interaction avec l'environnement), le choix est retiré de $L$ et une mise à jour de la fréquence est effectuée. Dans ce cas, un mécanisme de réinitialisation peut être activé, permettant de redéfinir l'indexation des choix, favorisant les choix les plus réussis dans le passé.

### Formalisation Complète de la Séquence de Choix

Le modèle suit la séquence :

1. **Calcul du Choix Préféré** : Trouver $c_{\text{freq}, L}$ dans la fenêtre $L$.
2. **Interaction avec l'Environnement** : Effectuer $c_{\text{freq}, L}$ et observer le retour de l'environnement.
3. **Mise à jour de l'Historique** :
   - Si le retour est positif, ajouter $c_{\text{freq}, L}$ dans $H$.
   - Si le retour est négatif, exclure $c_{\text{freq}, L}$ de $L$ et réévaluer le choix préféré.

Cette approche peut être itérative, permettant au modèle d'apprendre les choix optimaux au fil du temps.

***

Code généré par GPT4o

Pour intégrer ce code dans un projet Arduino avec un capteur à ultrason pour détecter les obstacles, il est nécessaire de modifier le code pour utiliser les bibliothèques Arduino et ajouter la logique de détection d’obstacles. Voici une version adaptée pour Arduino.

### Matériel requis
- Un capteur à ultrason (par exemple, le HC-SR04) pour la détection d'obstacles.
- Une carte Arduino (comme l'Arduino Uno).

### Code C++ pour Arduino

Ce code utilise le capteur à ultrason pour détecter des obstacles. Si un obstacle est détecté, l’agent sélectionne un choix d’évitement basé sur l’historique des choix passés.

```cpp
#include <Arduino.h>

// Pins du capteur ultrason
const int trigPin = 9;
const int echoPin = 10;

// Constantes pour les choix d'évitement
enum Choice {
    TURN_LEFT,
    TURN_RIGHT,
    MOVE_BACKWARD,
    MOVE_FORWARD,
    NUM_CHOICES
};

// Variables globales
std::vector<Choice> history;       // Historique des choix
const int windowSize = 5;          // Taille de la fenêtre de choix fréquents
const int obstacleThreshold = 20;  // Distance en cm pour considérer qu'il y a un obstacle

// Fonction pour mesurer la distance avec le capteur à ultrason
long measureDistance() {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    long duration = pulseIn(echoPin, HIGH);
    long distance = duration * 0.034 / 2;
    return distance;
}

// Fonction pour sélectionner le choix le plus fréquent dans une fenêtre
Choice selectFrequentChoice(const std::vector<Choice>& history, int windowSize) {
    std::unordered_map<Choice, int> frequency;
    int start = max(0, (int)history.size() - windowSize);

    // Calcul des fréquences dans la fenêtre
    for (int i = start; i < history.size(); ++i) {
        frequency[history[i]]++;
    }

    // Trouver le choix le plus fréquent
    Choice frequentChoice = history[start];
    int maxFrequency = 0;
    for (const auto& pair : frequency) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
            frequentChoice = pair.first;
        }
    }
    return frequentChoice;
}

// Fonction pour exécuter un choix d'évitement
void executeChoice(Choice choice) {
    switch (choice) {
        case TURN_LEFT:
            Serial.println("Tourne à gauche");
            // Code pour tourner à gauche
            break;
        case TURN_RIGHT:
            Serial.println("Tourne à droite");
            // Code pour tourner à droite
            break;
        case MOVE_BACKWARD:
            Serial.println("Recule");
            // Code pour reculer
            break;
        case MOVE_FORWARD:
            Serial.println("Avance");
            // Code pour avancer
            break;
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    // Mesurer la distance avec le capteur ultrason
    long distance = measureDistance();
    Serial.print("Distance mesurée: ");
    Serial.println(distance);

    // Si un obstacle est détecté
    if (distance < obstacleThreshold) {
        Choice selectedChoice = history.empty() ? static_cast<Choice>(random(NUM_CHOICES)) : selectFrequentChoice(history, windowSize);

        // Exécuter le choix sélectionné
        executeChoice(selectedChoice);

        // Enregistrer le choix dans l'historique
        history.push_back(selectedChoice);

        // Limiter la taille de l'historique pour éviter qu'il ne prenne trop de mémoire
        if (history.size() > 50) {
            history.erase(history.begin());
        }

        delay(1000);  // Attendre avant la prochaine mesure pour laisser le temps de l'action
    } else {
        Serial.println("Aucun obstacle détecté, avance en ligne droite.");
        // Code pour avancer tout droit
    }

    delay(100);  // Attente entre les mesures
}
```

### Explications du Code

1. **Mesure de la Distance** : La fonction `measureDistance()` utilise le capteur à ultrason pour mesurer la distance d'un obstacle en face de l'agent. Si la distance est inférieure à un seuil (`obstacleThreshold`), l'agent considère qu'il y a un obstacle.

2. **Sélection du Choix** : Si un obstacle est détecté, la fonction `selectFrequentChoice()` choisit la manœuvre d'évitement la plus fréquente dans les dernières actions stockées dans l'historique. Si l'historique est vide, un choix est sélectionné au hasard.

3. **Exécution du Choix** : La fonction `executeChoice()` définit les actions associées aux choix possibles (tourner à gauche, tourner à droite, reculer, avancer). Vous pouvez compléter cette fonction avec les commandes moteurs spécifiques pour votre projet.

4. **Historique des Choix** : L'historique stocke les choix effectués et est limité en taille pour éviter une surcharge de mémoire.

5. **Détection et Évitement d'Obstacles** : Dans la boucle `loop()`, si la distance est en dessous du seuil, l'agent choisit une manœuvre d'évitement et l'exécute. Sinon, il continue tout droit.

### Remarques

- **Délais** : Un délai est ajouté après chaque action pour laisser le temps à l'agent de l'exécuter.
- **Aléatoire** : L'utilisation de `random()` permet de sélectionner une action aléatoire au début si l'historique est vide.
- **Adaptation** : Le code peut être modifié pour inclure des commandes moteurs spécifiques, en fonction de la configuration de votre robot.

Ce modèle devrait fournir une base fonctionnelle pour un robot qui détecte des obstacles et adapte son comportement en fonction des actions passées, en apprenant progressivement les manœuvres les plus efficaces.

