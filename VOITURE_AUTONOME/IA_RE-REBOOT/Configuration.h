#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// Configuration générale du robot
namespace RobotConfig {
    // Version du programme
    constexpr char VERSION[] = "2.0.0";
    
    // Debug et communication
    constexpr unsigned long SERIAL_BAUD_RATE = 9600;
    constexpr bool DEBUG_MODE = true;  // Active les messages de debug
    
    // Dimensions physiques du robot (en mm)
    namespace Dimensions {
        constexpr float WHEEL_DIAMETER = 65.0f;
        constexpr float WHEEL_CIRCUMFERENCE = 204.2f;  // π * diameter
        constexpr float WHEEL_BASE = 150.0f;  // Distance entre les roues
        constexpr float ROBOT_LENGTH = 200.0f;
        constexpr float ROBOT_WIDTH = 150.0f;
    }
}

// Configuration des pins
namespace PinConfig {
    // Moteurs
    namespace Motors {
        // Moteur gauche
        constexpr uint8_t LEFT_ENABLE = 5;   // ENA
        constexpr uint8_t LEFT_IN1 = 2;
        constexpr uint8_t LEFT_IN2 = 3;
        
        // Moteur droit
        constexpr uint8_t RIGHT_ENABLE = 6;  // ENB
        constexpr uint8_t RIGHT_IN1 = 4;
        constexpr uint8_t RIGHT_IN2 = 7;
    }
    
    // Capteurs
    namespace Sensors {
        // Ultrason
        constexpr uint8_t ULTRASONIC_TRIG = 13;
        constexpr uint8_t ULTRASONIC_ECHO = 12;
        
        // Infrarouge
        constexpr uint8_t IR_SENSOR = A1;
        
        // Tension
        constexpr uint8_t BATTERY_VOLTAGE = A2;
        constexpr uint8_t SOLAR_VOLTAGE = A0;
        
        // Servomoteur
        constexpr uint8_t SERVO = 9;
    }
    
    // LEDs
    namespace Leds {
        constexpr uint8_t RED = A3;
        constexpr uint8_t YELLOW = 8;
        constexpr uint8_t GREEN = 11;
    }
}

// Paramètres des comportements
namespace BehaviorConfig {
    // Mouvements
    namespace Movement {
        constexpr uint8_t DEFAULT_SPEED = 255;
        constexpr uint16_t TURN_DELAY = 300;    // ms
        constexpr uint16_t MOVE_DELAY = 200;    // ms
        constexpr float MIN_SPEED_FACTOR = 0.3f; // Facteur de vitesse minimum (30%)
    }
    
    // Servomoteur
    namespace Servo {
        constexpr uint8_t MIN_ANGLE = 5;
        constexpr uint8_t MAX_ANGLE = 175;
        constexpr uint8_t CENTER_ANGLE = 90;
        constexpr uint16_t SCAN_DELAY = 130;    // ms
    }
    
    // Détection d'obstacles
    namespace ObstacleDetection {
        constexpr uint8_t MIN_DISTANCE = 20;     // cm
        constexpr uint8_t CRITICAL_DISTANCE = 10; // cm
        constexpr uint16_t MEASURE_INTERVAL = 50; // ms
        constexpr uint8_t FILTER_SAMPLES = 5;     // Nombre d'échantillons pour le filtre
    }
    
    // Gestion de l'énergie
    namespace Power {
        constexpr float CRITICAL_VOLTAGE = 7.0f;
        constexpr float LOW_VOLTAGE = 7.5f;
        constexpr float NOMINAL_VOLTAGE = 8.0f;
        constexpr float FULL_VOLTAGE = 8.5f;
        constexpr float MIN_SOLAR_VOLTAGE = 8.0f;
        constexpr uint16_t VOLTAGE_CHECK_INTERVAL = 1000; // ms
    }
}

// Configuration des stratégies d'apprentissage
namespace LearningConfig {
    constexpr uint8_t MAX_SCORE = 3;
    constexpr uint8_t MIN_SCORE = 0;
    constexpr float SUCCESS_THRESHOLD = 0.7f;
    constexpr float FAILURE_THRESHOLD = 0.3f;
    constexpr uint8_t MEMORY_PATTERN_SIZE = 3;
    constexpr uint16_t MAX_MEMORY_ENTRIES = 500;
}

// Configuration des temps et délais
namespace TimingConfig {
    constexpr unsigned long MAIN_LOOP_DELAY = 10;        // ms
    constexpr unsigned long PATTERN_CHECK_INTERVAL = 1000; // ms
    constexpr unsigned long CHARGING_TIMEOUT = 3600000;   // 1 heure en ms
    constexpr unsigned long EMERGENCY_TIMEOUT = 5000;     // 5 secondes en ms
}

// Constantes de calcul et conversion
namespace Constants {
    constexpr float VOLTAGE_FACTOR = 0.0048828125f;  // 5V / 1024
    constexpr float VOLTAGE_DIVIDER = 2.0f;
    constexpr float PI = 3.14159265359f;
    
    // Facteurs de conversion
    namespace Conversion {
        constexpr float CM_TO_MM = 10.0f;
        constexpr float MM_TO_CM = 0.1f;
        constexpr float DEGREES_TO_RADIANS = 0.01745329251f;
        constexpr float RADIANS_TO_DEGREES = 57.2957795131f;
    }
}

// Messages de debug
namespace DebugMessages {
    constexpr char STARTUP[] = "=== Robot Autonome v2.0 ===";
    constexpr char INIT_COMPLETE[] = "Initialisation terminée";
    constexpr char ERROR_ULTRASONIC[] = "Erreur capteur ultrason";
    constexpr char ERROR_BATTERY_LOW[] = "Batterie faible";
    constexpr char ERROR_PATTERN_INVALID[] = "Pattern invalide";
}

#endif // CONFIGURATION_H