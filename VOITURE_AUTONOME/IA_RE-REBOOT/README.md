# Robot Autonome v2.0

Un robot autonome intelligent capable d'explorer son environnement, d'éviter les obstacles et de gérer son énergie de manière autonome.

## 🌟 Fonctionnalités

- **Navigation Autonome**: Exploration et évitement d'obstacles intelligent
- **Apprentissage**: Mémorisation des patterns de mouvement réussis
- **Gestion d'Énergie**: Système de recharge solaire autonome
- **États Multiples**: Exploration, évitement, recharge, suivi de pattern
- **Feedback Visuel**: Indication d'état par LED multicolore

## 🔧 Architecture

Le projet est organisé en modules distincts et réutilisables :

- `AutoRobot.ino` - Programme principal
- `RobotCore.h` - Coordinateur principal
- `Movement.h` - Gestion des mouvements
- `Sensors.h` - Interface des capteurs
- `Memory.h` - Gestion de la mémoire et patterns
- `Strategy.h` - Logique d'évitement d'obstacles
- `PowerManagement.h` - Gestion de l'énergie
- `LED.h` - Feedback visuel
- `Configuration.h` - Configuration globale

## 📋 Prérequis

### Matériel
- Arduino Uno/Nano ou compatible
- 2 moteurs DC avec pont en H (L298N recommandé)
- Servomoteur pour le balayage
- Capteur ultrason HC-SR04
- Capteur infrarouge
- LEDs (rouge, jaune, verte)
- Panneau solaire et batterie
- Châssis robot (2 roues motrices + 1 roue folle)

### Logiciel
- Arduino IDE 1.8.x ou supérieur
- Bibliothèques:
  - HCSR04.h (pour le capteur ultrason)
  - Servo.h
  - EEPROM.h
  - Wire.h

## ⚡ Installation

1. Cloner le repository:
```bash
git clone https://github.com/votre-username/robot-autonome.git
```

2. Ouvrir `AutoRobot.ino` dans l'Arduino IDE

3. Installer les bibliothèques requises

4. Configurer les broches dans `Configuration.h` selon votre montage

5. Téléverser le programme

## 🔌 Connexions

### Moteurs
- ENA -> Pin 5
- IN1 -> Pin 2
- IN2 -> Pin 3
- ENB -> Pin 6
- IN3 -> Pin 4
- IN4 -> Pin 7

### Capteurs
- TRIG (Ultrason) -> Pin 13
- ECHO (Ultrason) -> Pin 12
- IR_SENSOR -> Pin A1
- BATTERY_VOLTAGE -> Pin A2
- SOLAR_VOLTAGE -> Pin A0

### Servomoteur
- SERVO -> Pin 9

### LEDs
- RED -> Pin A3
- YELLOW -> Pin 8
- GREEN -> Pin 11

## 🛠️ Configuration

Le fichier `Configuration.h` permet de personnaliser:

- Dimensions du robot
- Paramètres des moteurs
- Seuils de détection
- Paramètres de comportement
- Seuils de tension
- Temporisations

## 📊 Fonctionnement

Le robot utilise une machine à états avec 4 modes principaux:

1. **EXPLORING**: Exploration de l'environnement
2. **AVOIDING_OBSTACLE**: Évitement d'obstacle avec apprentissage
3. **CHARGING**: Recherche et utilisation de source d'énergie
4. **FOLLOWING_PATTERN**: Reproduction de patterns mémorisés

## 🔍 Diagnostic

Les LEDs indiquent l'état du robot:
- 🟢 **Vert**: Fonctionnement normal
- 🟡 **Jaune**: En charge
- 🔴 **Rouge**: Batterie faible ou obstacle

## 🤝 Contribution

Les contributions sont bienvenues! Merci de:

1. Fork le projet
2. Créer une branche (`git checkout -b feature/amelioration`)
3. Commit les changements (`git commit -m 'Ajout de fonctionnalité'`)
4. Push la branche (`git push origin feature/amelioration`)
5. Ouvrir une Pull Request

## 📝 Licence

Ce projet est sous licence MIT - voir le fichier [LICENSE.md](LICENSE.md) pour plus de détails.

## ✨ Remerciements

- Équipe Arduino pour leur excellent framework
- Communauté open-source pour les bibliothèques utilisées
- Contributeurs du projet