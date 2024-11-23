#ifndef POWER_MANAGEMENT_H
#define POWER_MANAGEMENT_H

#include <Arduino.h>
#include "Sensors.h"

class PowerManagement {
public:
    // États de charge
    enum class ChargeState {
        CRITICAL,       // Niveau critique, arrêt imminent
        LOW,           // Niveau bas, recherche de recharge nécessaire
        CHARGING,      // En cours de charge
        CHARGED,       // Chargé
        FULLY_CHARGED  // Complètement chargé
    };

    // Configuration de l'alimentation
    struct PowerConfig {
        // Seuils de tension batterie (en volts)
        float criticalVoltage;     // Tension critique
        float lowVoltage;          // Tension basse
        float nominalVoltage;      // Tension nominale
        float fullVoltage;         // Tension pleine charge
        
        // Seuils panneau solaire
        float minSolarVoltage;     // Tension minimale pour charge
        float optimalSolarVoltage; // Tension optimale pour charge

        // Délais et temporisation
        uint16_t chargingTimeout;  // Timeout de charge en ms
        uint16_t voltageCheckInterval; // Intervalle de vérification en ms
    };

private:
    // Configuration par défaut
    static constexpr PowerConfig DEFAULT_CONFIG = {
        .criticalVoltage = 7.0f,
        .lowVoltage = 7.5f,
        .nominalVoltage = 8.0f,
        .fullVoltage = 8.5f,
        .minSolarVoltage = 8.0f,
        .optimalSolarVoltage = 9.0f,
        .chargingTimeout = 3600000,  // 1 heure
        .voltageCheckInterval = 1000  // 1 seconde
    };

    // Structure pour les statistiques de charge
    struct ChargingStats {
        unsigned long totalChargingTime;    // Temps total de charge
        uint16_t chargingCycles;           // Nombre de cycles de charge
        float averageChargingTime;         // Temps moyen de charge
        float lowestVoltageRecorded;       // Plus basse tension enregistrée
        float highestVoltageRecorded;      // Plus haute tension enregistrée
    };

    PowerConfig config;
    ChargeState currentState;
    ChargingStats stats;

    // Variables de suivi
    unsigned long lastVoltageCheck;
    unsigned long chargingStartTime;
    bool isCharging;
    float currentVoltage;
    float currentSolarVoltage;

public:
    PowerManagement(const PowerConfig& customConfig = DEFAULT_CONFIG) 
        : config(customConfig)
        , currentState(ChargeState::CHARGED)
        , lastVoltageCheck(0)
        , chargingStartTime(0)
        , isCharging(false)
        , currentVoltage(0.0f)
        , currentSolarVoltage(0.0f) {
        resetStats();
    }

    void setup() {
        // Configuration initiale si nécessaire
        lastVoltageCheck = millis();
    }

    // Mise à jour de l'état de charge
    void update(const Sensors::SensorData& sensorData) {
        unsigned long currentTime = millis();
        
        // Vérifier la tension selon l'intervalle configuré
        if (currentTime - lastVoltageCheck >= config.voltageCheckInterval) {
            currentVoltage = sensorData.batteryVoltage;
            currentSolarVoltage = sensorData.solarVoltage;
            updateChargeState();
            lastVoltageCheck = currentTime;
            
            // Mise à jour des statistiques
            updateStats();
        }

        // Vérifier le timeout de charge
        if (isCharging && (currentTime - chargingStartTime >= config.chargingTimeout)) {
            handleChargingTimeout();
        }
    }

    // Vérification de l'état de charge
    bool needsCharging() const {
        return currentState == ChargeState::LOW || currentState == ChargeState::CRITICAL;
    }

    bool isFullyCharged() const {
        return currentState == ChargeState::FULLY_CHARGED;
    }

    bool canCharge(const Sensors::SensorData& sensorData) const {
        return sensorData.solarVoltage >= config.minSolarVoltage;
    }

    ChargeState getChargeState() const {
        return currentState;
    }

    float getBatteryVoltage() const {
        return currentVoltage;
    }

    float getChargeLevel() const {
        float voltageRange = config.fullVoltage - config.criticalVoltage;
        float currentLevel = currentVoltage - config.criticalVoltage;
        return (currentLevel / voltageRange) * 100.0f;
    }

    // Gestion de la charge
    void startCharging() {
        if (!isCharging) {
            isCharging = true;
            chargingStartTime = millis();
            currentState = ChargeState::CHARGING;
        }
    }

    void stopCharging() {
        if (isCharging) {
            isCharging = false;
            updateChargingStats();
        }
    }

    // Récupération des statistiques
    const ChargingStats& getChargingStats() const {
        return stats;
    }

    // Interface de diagnostic
    void printPowerStatus() const {
        Serial.println(F("=== Power Status ==="));
        Serial.print(F("State: "));
        printChargeState();
        Serial.print(F("Battery Voltage: "));
        Serial.println(currentVoltage);
        Serial.print(F("Solar Voltage: "));
        Serial.println(currentSolarVoltage);
        Serial.print(F("Charge Level: "));
        Serial.print(getChargeLevel());
        Serial.println(F("%"));
        printChargingStats();
        Serial.println(F("=================="));
    }

private:
    void updateChargeState() {
        ChargeState previousState = currentState;

        if (currentVoltage <= config.criticalVoltage) {
            currentState = ChargeState::CRITICAL;
        } else if (currentVoltage <= config.lowVoltage) {
            currentState = ChargeState::LOW;
        } else if (currentVoltage >= config.fullVoltage) {
            currentState = ChargeState::FULLY_CHARGED;
        } else if (isCharging) {
            currentState = ChargeState::CHARGING;
        } else {
            currentState = ChargeState::CHARGED;
        }

        // Notifier les changements d'état
        if (previousState != currentState) {
            handleStateChange(previousState);
        }
    }

    void handleStateChange(ChargeState previousState) {
        switch (currentState) {
            case ChargeState::CRITICAL:
                handleCriticalBattery();
                break;
            case ChargeState::FULLY_CHARGED:
                if (isCharging) {
                    stopCharging();
                }
                break;
            default:
                break;
        }
    }

    void handleCriticalBattery() {
        // Procédure d'urgence pour batterie critique
        // Par exemple, arrêt des moteurs, signalement LED, etc.
    }

    void handleChargingTimeout() {
        stopCharging();
        // Potentiellement signaler un problème de charge
    }

    void updateStats() {
        stats.lowestVoltageRecorded = min(stats.lowestVoltageRecorded, currentVoltage);
        stats.highestVoltageRecorded = max(stats.highestVoltageRecorded, currentVoltage);
    }

    void updateChargingStats() {
        unsigned long chargingDuration = millis() - chargingStartTime;
        stats.totalChargingTime += chargingDuration;
        stats.chargingCycles++;
        stats.averageChargingTime = stats.totalChargingTime / stats.chargingCycles;
    }

    void resetStats() {
        stats = {
            .totalChargingTime = 0,
            .chargingCycles = 0,
            .averageChargingTime = 0.0f,
            .lowestVoltageRecorded = config.fullVoltage,
            .highestVoltageRecorded = config.criticalVoltage
        };
    }

    void printChargeState() const {
        switch (currentState) {
            case ChargeState::CRITICAL:
                Serial.println(F("CRITICAL"));
                break;
            case ChargeState::LOW:
                Serial.println(F("LOW"));
                break;
            case ChargeState::CHARGING:
                Serial.println(F("CHARGING"));
                break;
            case ChargeState::CHARGED:
                Serial.println(F("CHARGED"));
                break;
            case ChargeState::FULLY_CHARGED:
                Serial.println(F("FULLY CHARGED"));
                break;
        }
    }

    void printChargingStats() const {
        Serial.println(F("--- Charging Statistics ---"));
        Serial.print(F("Charging Cycles: "));
        Serial.println(stats.chargingCycles);
        Serial.print(F("Average Charging Time: "));
        Serial.print(stats.averageChargingTime / 1000);
        Serial.println(F(" seconds"));
        Serial.print(F("Lowest Voltage: "));
        Serial.println(stats.lowestVoltageRecorded);
        Serial.print(F("Highest Voltage: "));
        Serial.println(stats.highestVoltageRecorded);
    }
};

#endif // POWER_MANAGEMENT_H