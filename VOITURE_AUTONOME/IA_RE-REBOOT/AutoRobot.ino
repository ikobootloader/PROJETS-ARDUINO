// AutoRobot.ino - Programme principal du robot autonome
#include "RobotCore.h"
#include "LED.h"

// Instance principale du robot
RobotCore robot;

// Instance pour les LEDs de statut
LED statusLed;

void setup() {
    // Initialisation de la communication série pour le debugging
    Serial.begin(9600);
    Serial.println(F("=== Robot Autonome v2.0 ==="));
    
    // Initialisation des LEDs
    statusLed.setup();
    statusLed.setStatus(LED::Status::INITIALIZING);
    
    // Initialisation du robot
    robot.setup();
    
    // Indication que l'initialisation est terminée
    statusLed.setStatus(LED::Status::READY);
    Serial.println(F("Initialisation terminée"));
}

void loop() {
    // Mise à jour de l'état du robot
    robot.loop();
}