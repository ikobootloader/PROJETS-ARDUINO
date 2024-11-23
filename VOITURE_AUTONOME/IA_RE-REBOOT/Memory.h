#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include "Movement.h"

class Memory {
public:
    // Structure pour stocker un mouvement
    struct MovementRecord {
        Movement::Action action;
        uint8_t servoAngle;
        uint16_t duration;
        uint8_t successRate;
    };

    // Structure pour un pattern de mouvements
    struct Pattern {
        MovementRecord movements[3];  // Pattern fixe de 3 mouvements
        uint8_t currentIndex;
        bool isValid;
        uint16_t occurrences;
        
        bool isComplete() const { return currentIndex >= 3; }
        void reset() { currentIndex = 0; }
        Movement::Action getNextAction() {
            if (currentIndex < 3) {
                return movements[currentIndex++].action;
            }
            return Movement::Action::STOP;
        }
    };

private:
    // Constantes de configuration
    static constexpr uint16_t EEPROM_SIZE = 512;
    static constexpr uint8_t PATTERN_SIZE = 3;
    static constexpr uint8_t MAX_PATTERNS = 5;
    static constexpr uint16_t RECORD_BUFFER_SIZE = 30;
    
    // Structure de l'en-tête EEPROM
    struct EepromHeader {
        uint16_t totalRecords;
        uint16_t lastWriteIndex;
        uint16_t checksum;
    };

    // Variables membres
    EepromHeader header;
    MovementRecord recordBuffer[RECORD_BUFFER_SIZE];
    uint8_t bufferIndex;
    Pattern detectedPatterns[MAX_PATTERNS];
    Pattern currentPattern;
    uint8_t patternCount;

public:
    Memory() : bufferIndex(0), patternCount(0) {
        clearBuffer();
        currentPattern.isValid = false;
    }

    void setup() {
        Wire.begin();
        loadHeader();
        if (!isHeaderValid()) {
            initializeEeprom();
        }
    }

    // Enregistrement des mouvements
    void recordMovement(Movement::Action action, uint8_t angle = 90, uint16_t duration = 0) {
        MovementRecord record = {action, angle, duration, 0};
        
        // Ajouter au buffer circulaire
        recordBuffer[bufferIndex] = record;
        bufferIndex = (bufferIndex + 1) % RECORD_BUFFER_SIZE;
        
        // Sauvegarder en EEPROM
        writeRecordToEeprom(record);
        
        // Analyser les patterns après chaque nouvel enregistrement
        analyzePatterns();
    }

    void recordSuccessfulStrategy(Movement::Action action, uint8_t angle) {
        MovementRecord record = {action, angle, 0, 100};
        writeRecordToEeprom(record);
        updateStrategySuccess(action, angle);
    }

    void recordFailedAttempt() {
        if (bufferIndex > 0) {
            recordBuffer[bufferIndex - 1].successRate = 0;
        }
    }

    // Gestion des patterns
    bool hasPattern() const {
        return currentPattern.isValid;
    }

    Pattern getCurrentPattern() const {
        return currentPattern;
    }

    void recordPatternExecution() {
        if (currentPattern.isValid && !currentPattern.isComplete()) {
            // Mise à jour des statistiques du pattern
            incrementPatternOccurrence();
        }
    }

    // Gestion de la recharge
    void recordChargingLocation() {
        // Marquer le dernier pattern comme pattern de recharge
        if (currentPattern.isValid) {
            writeChargingPatternToEeprom(currentPattern);
        }
    }

    Pattern getChargingPattern() {
        return readChargingPatternFromEeprom();
    }

    // Fonctions de diagnostic
    void printMemoryStatus() {
        Serial.println(F("=== Memory Status ==="));
        Serial.print(F("Total Records: "));
        Serial.println(header.totalRecords);
        Serial.print(F("Detected Patterns: "));
        Serial.println(patternCount);
        Serial.print(F("Current Pattern Valid: "));
        Serial.println(currentPattern.isValid ? F("Yes") : F("No"));
        Serial.println(F("=================="));
    }

private:
    // Gestion EEPROM
    void loadHeader() {
        EEPROM.get(0, header);
    }

    void saveHeader() {
        EEPROM.put(0, header);
    }

    bool isHeaderValid() {
        return header.checksum == calculateChecksum();
    }

    uint16_t calculateChecksum() {
        return ~(header.totalRecords + header.lastWriteIndex);
    }

    void initializeEeprom() {
        header.totalRecords = 0;
        header.lastWriteIndex = sizeof(EepromHeader);
        header.checksum = calculateChecksum();
        saveHeader();
    }

    void writeRecordToEeprom(const MovementRecord& record) {
        if (header.lastWriteIndex + sizeof(MovementRecord) > EEPROM_SIZE) {
            header.lastWriteIndex = sizeof(EepromHeader);
        }

        EEPROM.put(header.lastWriteIndex, record);
        header.lastWriteIndex += sizeof(MovementRecord);
        header.totalRecords++;
        header.checksum = calculateChecksum();
        saveHeader();
    }

    // Analyse des patterns
    void analyzePatterns() {
        if (bufferIndex < PATTERN_SIZE) {
            return;
        }

        Pattern newPattern;
        newPattern.reset();
        bool patternFound = false;

        // Analyser les derniers mouvements pour détecter un pattern
        for (uint8_t i = 0; i < PATTERN_SIZE; i++) {
            uint8_t idx = (bufferIndex - PATTERN_SIZE + i) % RECORD_BUFFER_SIZE;
            newPattern.movements[i] = recordBuffer[idx];
        }

        // Vérifier si ce pattern existe déjà
        for (uint8_t i = 0; i < patternCount; i++) {
            if (comparePatterns(newPattern, detectedPatterns[i])) {
                detectedPatterns[i].occurrences++;
                patternFound = true;
                // Si le pattern est fréquent, le définir comme pattern courant
                if (detectedPatterns[i].occurrences > 2) {
                    currentPattern = detectedPatterns[i];
                }
                break;
            }
        }

        // Si c'est un nouveau pattern et qu'il y a de la place
        if (!patternFound && patternCount < MAX_PATTERNS) {
            newPattern.occurrences = 1;
            newPattern.isValid = true;
            detectedPatterns[patternCount++] = newPattern;
        }
    }

    bool comparePatterns(const Pattern& p1, const Pattern& p2) {
        for (uint8_t i = 0; i < PATTERN_SIZE; i++) {
            if (p1.movements[i].action != p2.movements[i].action ||
                abs(p1.movements[i].servoAngle - p2.movements[i].servoAngle) > 10) {
                return false;
            }
        }
        return true;
    }

    void updateStrategySuccess(Movement::Action action, uint8_t angle) {
        // Mettre à jour les statistiques de réussite pour cette combinaison action/angle
        for (uint8_t i = 0; i < RECORD_BUFFER_SIZE; i++) {
            if (recordBuffer[i].action == action && 
                abs(recordBuffer[i].servoAngle - angle) <= 10) {
                recordBuffer[i].successRate = 
                    (recordBuffer[i].successRate * 3 + 100) / 4; // Moyenne pondérée
            }
        }
    }

    void incrementPatternOccurrence() {
        if (currentPattern.isValid) {
            for (uint8_t i = 0; i < patternCount; i++) {
                if (comparePatterns(currentPattern, detectedPatterns[i])) {
                    detectedPatterns[i].occurrences++;
                    break;
                }
            }
        }
    }

    void clearBuffer() {
        memset(recordBuffer, 0, sizeof(recordBuffer));
    }

    // Gestion des patterns de recharge
    void writeChargingPatternToEeprom(const Pattern& pattern) {
        // Réserver une zone spéciale dans l'EEPROM pour le pattern de recharge
        const uint16_t CHARGING_PATTERN_ADDRESS = EEPROM_SIZE - sizeof(Pattern);
        EEPROM.put(CHARGING_PATTERN_ADDRESS, pattern);
    }

    Pattern readChargingPatternFromEeprom() {
        Pattern pattern;
        const uint16_t CHARGING_PATTERN_ADDRESS = EEPROM_SIZE - sizeof(Pattern);
        EEPROM.get(CHARGING_PATTERN_ADDRESS, pattern);
        return pattern;
    }
};

#endif // MEMORY_H