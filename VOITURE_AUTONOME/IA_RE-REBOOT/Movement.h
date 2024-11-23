// Movement.h - Contrôle complet des mouvements du robot
#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Arduino.h>
#include <Servo.h>

class Movement {
public:
    // Actions possibles du robot
    enum class Action {
        FORWARD,
        BACKWARD,
        TURN_LEFT,
        TURN_RIGHT,
        STOP
    };

    // Configuration des pins moteurs
    struct MotorPins {
        uint8_t enableA;    // Enable du moteur A
        uint8_t in1;        // Input 1 du moteur A
        uint8_t in2;        // Input 2 du moteur A
        uint8_t enableB;    // Enable du moteur B
        uint8_t in3;        // Input 1 du moteur B
        uint8_t in4;        // Input 2 du moteur B
    };

    // Configuration du servomoteur
    struct ServoConfig {
        uint8_t pin;           // Pin du servomoteur
        uint8_t minAngle;      // Angle minimum (typiquement 5)
        uint8_t maxAngle;      // Angle maximum (typiquement 175)
        uint8_t centerAngle;   // Angle central (typiquement 90)
        uint16_t scanDelay;    // Délai de balayage en ms
    };

private:
    // Configuration par défaut des pins
    static constexpr MotorPins DEFAULT_MOTOR_PINS = {
        .enableA = 5,  // ENA
        .in1 = 2,      // IN1
        .in2 = 3,      // IN2
        .enableB = 6,  // ENB
        .in3 = 4,      // IN3
        .in4 = 7       // IN4
    };

    // Configuration par défaut du servo
    static constexpr ServoConfig DEFAULT_SERVO_CONFIG = {
        .pin = 9,
        .minAngle = 5,
        .maxAngle = 175,
        .centerAngle = 90,
        .scanDelay = 130
    };

    MotorPins pins;
    ServoConfig servoConfig;
    Servo servo;
    
    // Variables pour le contrôle du balayage
    uint8_t currentAngle;
    int8_t scanDirection;
    unsigned long lastScanTime;

    // Paramètres de mouvement
    static constexpr uint16_t DEFAULT_TURN_DELAY = 300;  // ms
    static constexpr uint16_t DEFAULT_MOVE_DELAY = 200;  // ms
    static constexpr uint8_t DEFAULT_SPEED = 255;        // 0-255

public:
    Movement(const MotorPins& motorPins = DEFAULT_MOTOR_PINS,
            const ServoConfig& servoConf = DEFAULT_SERVO_CONFIG)
        : pins(motorPins)
        , servoConfig(servoConf)
        , currentAngle(servoConf.centerAngle)
        , scanDirection(1)
        , lastScanTime(0)
    {}

    void setup() {
        // Configuration des pins moteurs
        pinMode(pins.enableA, OUTPUT);
        pinMode(pins.in1, OUTPUT);
        pinMode(pins.in2, OUTPUT);
        pinMode(pins.enableB, OUTPUT);
        pinMode(pins.in3, OUTPUT);
        pinMode(pins.in4, OUTPUT);

        // Configuration du servomoteur
        servo.attach(servoConfig.pin);
        servo.write(servoConfig.centerAngle);

        // Arrêt initial des moteurs
        stop();
    }

    // Méthodes principales de mouvement
    void moveForward(uint8_t speed = DEFAULT_SPEED) {
        setMotorSpeeds(speed, speed);
        digitalWrite(pins.in1, HIGH);
        digitalWrite(pins.in2, LOW);
        digitalWrite(pins.in3, HIGH);
        digitalWrite(pins.in4, LOW);
    }

    void moveBackward(uint8_t speed = DEFAULT_SPEED) {
        setMotorSpeeds(speed, speed);
        digitalWrite(pins.in1, LOW);
        digitalWrite(pins.in2, HIGH);
        digitalWrite(pins.in3, LOW);
        digitalWrite(pins.in4, HIGH);
    }

    void turnLeft(uint8_t speed = DEFAULT_SPEED) {
        setMotorSpeeds(speed, speed);
        digitalWrite(pins.in1, LOW);
        digitalWrite(pins.in2, HIGH);
        digitalWrite(pins.in3, HIGH);
        digitalWrite(pins.in4, LOW);
    }

    void turnRight(uint8_t speed = DEFAULT_SPEED) {
        setMotorSpeeds(speed, speed);
        digitalWrite(pins.in1, HIGH);
        digitalWrite(pins.in2, LOW);
        digitalWrite(pins.in3, LOW);
        digitalWrite(pins.in4, HIGH);
    }

    void stop() {
        setMotorSpeeds(0, 0);
        digitalWrite(pins.in1, LOW);
        digitalWrite(pins.in2, LOW);
        digitalWrite(pins.in3, LOW);
        digitalWrite(pins.in4, LOW);
    }

    // Exécution d'une action spécifique
    void executeAction(Action action, uint8_t speed = DEFAULT_SPEED, uint16_t duration = 0) {
        switch (action) {
            case Action::FORWARD:
                moveForward(speed);
                break;
            case Action::BACKWARD:
                moveBackward(speed);
                break;
            case Action::TURN_LEFT:
                turnLeft(speed);
                break;
            case Action::TURN_RIGHT:
                turnRight(speed);
                break;
            case Action::STOP:
                stop();
                break;
        }

        if (duration > 0) {
            delay(duration);
            stop();
        }
    }

    // Contrôle du servomoteur
    void updateServoScan() {
        unsigned long currentTime = millis();
        if (currentTime - lastScanTime >= servoConfig.scanDelay) {
            currentAngle += scanDirection;
            
            if (currentAngle >= servoConfig.maxAngle || currentAngle <= servoConfig.minAngle) {
                scanDirection = -scanDirection;
            }
            
            servo.write(currentAngle);
            lastScanTime = currentTime;
        }
    }

    void setServoAngle(uint8_t angle) {
        angle = constrain(angle, servoConfig.minAngle, servoConfig.maxAngle);
        currentAngle = angle;
        servo.write(angle);
    }

    uint8_t getCurrentServoAngle() const {
        return currentAngle;
    }

    // Manœuvre d'urgence
    void executeEmergencyManeuver() {
        moveBackward(DEFAULT_SPEED);
        delay(500);
        turnLeft(DEFAULT_SPEED);
        delay(400);
        stop();
    }

private:
    void setMotorSpeeds(uint8_t speedA, uint8_t speedB) {
        analogWrite(pins.enableA, speedA);
        analogWrite(pins.enableB, speedB);
    }
};

#endif // MOVEMENT_H