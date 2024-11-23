#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include <HCSR04.h>  // Pour le capteur ultrason

class Sensors {
public:
    // Structure pour regrouper toutes les données des capteurs
    struct SensorData {
        // Distances
        float frontDistance;      // Distance avant en cm
        bool rearObstacle;       // Détection obstacle arrière
        uint8_t servoAngle;      // Angle actuel du servo

        // Alimentation
        float batteryVoltage;    // Tension batterie
        float solarVoltage;      // Tension panneau solaire

        // Horodatage
        unsigned long timestamp; // Pour le suivi temporel
    };

    // Configuration des pins des capteurs
    struct SensorPins {
        // Ultrason
        uint8_t trigPin;
        uint8_t echoPin;
        
        // Infrarouge
        uint8_t irPin;
        
        // Tensions
        uint8_t batteryPin;
        uint8_t solarPin;
    };

private:
    // Configuration par défaut des pins
    static constexpr SensorPins DEFAULT_SENSOR_PINS = {
        .trigPin = 13,
        .echoPin = 12,
        .irPin = A1,
        .batteryPin = A2,
        .solarPin = A0
    };

    // Paramètres de calibration
    struct CalibrationParams {
        // Facteurs de conversion pour les tensions
        static constexpr float VOLTAGE_FACTOR = 0.0048828125f;  // 5V / 1024
        static constexpr float VOLTAGE_DIVIDER = 2.0f;          // Facteur diviseur de tension
        
        // Seuils
        static constexpr float MIN_VALID_DISTANCE = 2.0f;      // Distance minimale valide en cm
        static constexpr float MAX_VALID_DISTANCE = 400.0f;    // Distance maximale valide en cm
        static constexpr int IR_THRESHOLD = 500;               // Seuil de détection IR
    };

    SensorPins pins;
    SensorData currentData;
    UltraSonicDistanceSensor* ultrasonicSensor;

    // Filtrage
    static constexpr uint8_t FILTER_SAMPLES = 5;
    float distanceBuffer[FILTER_SAMPLES];
    uint8_t filterIndex = 0;

public:
    Sensors(const SensorPins& sensorPins = DEFAULT_SENSOR_PINS)
        : pins(sensorPins) {
        ultrasonicSensor = new UltraSonicDistanceSensor(pins.trigPin, pins.echoPin);
    }

    ~Sensors() {
        delete ultrasonicSensor;
    }

    void setup() {
        // Configuration des pins
        pinMode(pins.irPin, INPUT);
        pinMode(pins.batteryPin, INPUT);
        pinMode(pins.solarPin, INPUT);

        // Initialisation des buffers
        for (uint8_t i = 0; i < FILTER_SAMPLES; i++) {
            distanceBuffer[i] = 0.0f;
        }
    }

    // Mise à jour de toutes les données des capteurs
    SensorData update() {
        currentData.timestamp = millis();
        currentData.frontDistance = measureFilteredDistance();
        currentData.rearObstacle = detectRearObstacle();
        currentData.batteryVoltage = measureBatteryVoltage();
        currentData.solarVoltage = measureSolarVoltage();
        
        return currentData;
    }

    // Mesures individuelles
    float measureDistance() {
        float distance = ultrasonicSensor->measureDistanceCm();
        
        // Validation de la mesure
        if (distance < CalibrationParams::MIN_VALID_DISTANCE || 
            distance > CalibrationParams::MAX_VALID_DISTANCE || 
            distance < 0) {
            return -1.0f;  // Mesure invalide
        }
        
        return distance;
    }

    float measureFilteredDistance() {
        float rawDistance = measureDistance();
        
        // Si la mesure est invalide, retourner la dernière valeur valide
        if (rawDistance < 0) {
            return currentData.frontDistance;
        }
        
        // Filtre médian glissant
        distanceBuffer[filterIndex] = rawDistance;
        filterIndex = (filterIndex + 1) % FILTER_SAMPLES;
        
        return calculateMedianDistance();
    }

    bool detectRearObstacle() {
        int irValue = analogRead(pins.irPin);
        return irValue > CalibrationParams::IR_THRESHOLD;
    }

    float measureBatteryVoltage() {
        int rawValue = analogRead(pins.batteryPin);
        return convertToVoltage(rawValue);
    }

    float measureSolarVoltage() {
        int rawValue = analogRead(pins.solarPin);
        return convertToVoltage(rawValue);
    }

    // Accesseurs
    float getFrontDistance() const { return currentData.frontDistance; }
    bool hasRearObstacle() const { return currentData.rearObstacle; }
    float getBatteryVoltage() const { return currentData.batteryVoltage; }
    float getSolarVoltage() const { return currentData.solarVoltage; }

private:
    float convertToVoltage(int rawValue) {
        return rawValue * CalibrationParams::VOLTAGE_FACTOR * CalibrationParams::VOLTAGE_DIVIDER;
    }

    float calculateMedianDistance() {
        // Copie du buffer pour le tri
        float sortedBuffer[FILTER_SAMPLES];
        memcpy(sortedBuffer, distanceBuffer, sizeof(distanceBuffer));
        
        // Tri simple (ok pour petit tableau)
        for (uint8_t i = 0; i < FILTER_SAMPLES - 1; i++) {
            for (uint8_t j = i + 1; j < FILTER_SAMPLES; j++) {
                if (sortedBuffer[j] < sortedBuffer[i]) {
                    float temp = sortedBuffer[i];
                    sortedBuffer[i] = sortedBuffer[j];
                    sortedBuffer[j] = temp;
                }
            }
        }
        
        // Retourne la valeur médiane
        return sortedBuffer[FILTER_SAMPLES / 2];
    }

    // Méthodes de diagnostic
public:
    void printSensorStatus() {
        Serial.println(F("=== Sensor Status ==="));
        Serial.print(F("Front Distance: "));
        Serial.println(currentData.frontDistance);
        Serial.print(F("Rear Obstacle: "));
        Serial.println(currentData.rearObstacle ? F("Detected") : F("None"));
        Serial.print(F("Battery Voltage: "));
        Serial.println(currentData.batteryVoltage);
        Serial.print(F("Solar Voltage: "));
        Serial.println(currentData.solarVoltage);
        Serial.println(F("=================="));
    }

    bool selfTest() {
        bool success = true;
        
        // Test ultrason
        float distance = measureDistance();
        if (distance < 0) {
            Serial.println(F("Ultrasonic sensor test failed"));
            success = false;
        }

        // Test IR
        int irValue = analogRead(pins.irPin);
        if (irValue < 0) {
            Serial.println(F("IR sensor test failed"));
            success = false;
        }

        // Test tensions
        if (measureBatteryVoltage() <= 0 || measureSolarVoltage() <= 0) {
            Serial.println(F("Voltage measurement test failed"));
            success = false;
        }

        return success;
    }
};

#endif // SENSORS_H