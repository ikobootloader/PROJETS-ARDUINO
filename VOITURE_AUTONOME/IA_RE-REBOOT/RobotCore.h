#ifndef ROBOT_CORE_H
#define ROBOT_CORE_H

#include <Arduino.h>
#include "Movement.h"
#include "Sensors.h"
#include "Memory.h"
#include "Strategy.h"
#include "PowerManagement.h"

class RobotCore {
private:
    Movement movement;
    Sensors sensors;
    Memory memory;
    Strategy strategy;
    PowerManagement power;
    
    // Configuration
    static constexpr uint8_t MAX_DISTANCE = 30;      // Distance maximum de détection (cm)
    static constexpr uint16_t SCAN_DELAY = 130;      // Délai de balayage (ms)
    static constexpr float LOW_BATTERY_THRESHOLD = 7.5f;
    static constexpr float CHARGE_THRESHOLD = 8.5f;

    // États du robot
    enum class RobotState {
        EXPLORING,
        AVOIDING_OBSTACLE,
        CHARGING,
        FOLLOWING_PATTERN
    } currentState;

    bool isCharging = false;
    uint8_t scanCounter = 0;

public:
    void setup() {
        movement.setup();
        sensors.setup();
        memory.setup();
        strategy.setup();
        power.setup();
        
        currentState = RobotState::EXPLORING;
    }

    void loop() {
        // Mise à jour des capteurs
        SensorData sensorData = sensors.update();
        
        // Gestion de l'état de charge
        handlePowerState(sensorData);
        
        // Machine à états principale
        switch (currentState) {
            case RobotState::EXPLORING:
                handleExploring(sensorData);
                break;
                
            case RobotState::AVOIDING_OBSTACLE:
                handleObstacleAvoidance(sensorData);
                break;
                
            case RobotState::CHARGING:
                handleCharging(sensorData);
                break;
                
            case RobotState::FOLLOWING_PATTERN:
                handlePatternFollowing(sensorData);
                break;
        }
    }

private:
    void handlePowerState(const SensorData& sensorData) {
        // Si batterie faible et source de lumière détectée
        if (power.needsCharging() && power.canCharge(sensorData)) {
            currentState = RobotState::CHARGING;
            movement.stop();
            isCharging = true;
        }
        // Si charge complète
        else if (isCharging && power.isFullyCharged()) {
            memory.recordChargingLocation();
            isCharging = false;
            currentState = RobotState::EXPLORING;
        }
    }

    void handleExploring(const SensorData& sensorData) {
        if (sensorData.frontDistance <= MAX_DISTANCE) {
            currentState = RobotState::AVOIDING_OBSTACLE;
            return;
        }
        
        if (memory.hasPattern() && !power.needsCharging()) {
            currentState = RobotState::FOLLOWING_PATTERN;
            return;
        }
        
        movement.moveForward();
        memory.recordMovement(Movement::Action::FORWARD);
    }

    void handleObstacleAvoidance(const SensorData& sensorData) {
        static Strategy::AvoidanceResult result;
        
        result = strategy.computeAvoidanceStrategy(sensorData);
        
        if (result.success) {
            memory.recordSuccessfulStrategy(result.action, sensorData.servoAngle);
            currentState = RobotState::EXPLORING;
        } else {
            movement.executeEmergencyManeuver();
            memory.recordFailedAttempt();
        }
    }

    void handleCharging(const SensorData& sensorData) {
        if (!power.needsCharging()) {
            currentState = RobotState::EXPLORING;
            return;
        }
        
        LED::indicateCharging(power.getChargeLevel());
    }

    void handlePatternFollowing(const SensorData& sensorData) {
        Pattern currentPattern = memory.getCurrentPattern();
        
        if (sensorData.frontDistance <= MAX_DISTANCE) {
            currentState = RobotState::AVOIDING_OBSTACLE;
            return;
        }
        
        if (currentPattern.isComplete()) {
            currentState = RobotState::EXPLORING;
            return;
        }
        
        movement.executePatternStep(currentPattern.getNextAction());
        memory.recordPatternExecution();
    }
};

#endif // ROBOT_CORE_H