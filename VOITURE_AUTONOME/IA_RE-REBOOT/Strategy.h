#ifndef STRATEGY_H
#define STRATEGY_H

#include <Arduino.h>
#include "Movement.h"
#include "Sensors.h"

class Strategy {
public:
    // Résultat d'une stratégie d'évitement
    struct AvoidanceResult {
        Movement::Action action;
        bool success;
        uint8_t score;
        uint8_t angleIndex;
    };
    
    // Structure pour le score d'une action
    struct ActionScore {
        Movement::Action action;
        uint8_t score;        // 0-3
        uint16_t successes;   // Nombre de réussites
        uint16_t attempts;    // Nombre de tentatives
    };

private:
    // Configuration des secteurs angulaires
    struct AngleSector {
        uint8_t minAngle;
        uint8_t maxAngle;
        uint8_t index;
    };

    static constexpr uint8_t NUM_SECTORS = 5;        // Nombre de secteurs angulaires
    static constexpr uint8_t NUM_ACTIONS = 4;        // Nombre d'actions possibles
    static constexpr uint8_t MAX_SCORE = 3;          // Score maximum
    static constexpr uint8_t MIN_DISTANCE = 20;      // Distance minimale en cm
    
    // Seuils pour l'apprentissage
    static constexpr float SUCCESS_THRESHOLD = 0.7f;  // Taux de succès pour augmenter le score
    static constexpr float FAILURE_THRESHOLD = 0.3f;  // Taux d'échec pour diminuer le score
    
    // Définition des secteurs angulaires
    const AngleSector angleSectors[NUM_SECTORS] = {
        {0, 30, 0},    // Extrême gauche
        {31, 60, 1},   // Gauche
        {61, 120, 2},  // Centre
        {121, 150, 3}, // Droite
        {151, 180, 4}  // Extrême droite
    };
    
    // Matrice de scores [secteur][action]
    ActionScore scoreMatrix[NUM_SECTORS][NUM_ACTIONS];
    
    // Cache pour la dernière action réussie par secteur
    Movement::Action lastSuccessfulAction[NUM_SECTORS];

public:
    Strategy() {
        initializeScoreMatrix();
    }

    void setup() {
        // Initialisation supplémentaire si nécessaire
    }

    // Calcul de la meilleure stratégie d'évitement
    AvoidanceResult computeAvoidanceStrategy(const Sensors::SensorData& sensorData) {
        uint8_t sector = getSectorFromAngle(sensorData.servoAngle);
        return findBestStrategy(sector, sensorData);
    }

    // Mise à jour des scores après une tentative
    void updateStrategy(const AvoidanceResult& result) {
        updateScore(result.angleIndex, result.action, result.success);
        if (result.success) {
            lastSuccessfulAction[result.angleIndex] = result.action;
        }
    }

    // Apprentissage à partir des données historiques
    void learnFromHistory(const Movement::Action action, const uint8_t angle, const bool success) {
        uint8_t sector = getSectorFromAngle(angle);
        updateScore(sector, action, success);
        analyzeSuccessPatterns(sector);
    }

    // Récupération des statistiques
    void getActionStats(uint8_t sector, Movement::Action action, uint16_t& successes, uint16_t& attempts) const {
        for (const auto& score : scoreMatrix[sector]) {
            if (score.action == action) {
                successes = score.successes;
                attempts = score.attempts;
                return;
            }
        }
        successes = attempts = 0;
    }

    // Affichage des statistiques pour le débogage
    void printStrategyStats() const {
        Serial.println(F("=== Strategy Statistics ==="));
        for (uint8_t sector = 0; sector < NUM_SECTORS; sector++) {
            Serial.print(F("Sector "));
            Serial.print(sector);
            Serial.println(F(":"));
            
            for (uint8_t action = 0; action < NUM_ACTIONS; action++) {
                const auto& score = scoreMatrix[sector][action];
                Serial.print(F("  Action "));
                Serial.print(static_cast<int>(score.action));
                Serial.print(F(": Score="));
                Serial.print(score.score);
                Serial.print(F(", Success Rate="));
                float successRate = score.attempts > 0 ? 
                    (float)score.successes / score.attempts * 100 : 0;
                Serial.print(successRate);
                Serial.println(F("%"));
            }
        }
        Serial.println(F("========================"));
    }

private:
    void initializeScoreMatrix() {
        for (uint8_t sector = 0; sector < NUM_SECTORS; sector++) {
            for (uint8_t action = 0; action < NUM_ACTIONS; action++) {
                scoreMatrix[sector][action] = {
                    static_cast<Movement::Action>(action),
                    0,  // score initial
                    0,  // successes
                    0   // attempts
                };
            }
            lastSuccessfulAction[sector] = Movement::Action::STOP;
        }
    }

    uint8_t getSectorFromAngle(uint8_t angle) const {
        for (const auto& sector : angleSectors) {
            if (angle >= sector.minAngle && angle <= sector.maxAngle) {
                return sector.index;
            }
        }
        return 2; // Secteur central par défaut
    }

    AvoidanceResult findBestStrategy(uint8_t sector, const Sensors::SensorData& sensorData) {
        // Si une action a déjà réussi dans ce secteur, la privilégier
        if (lastSuccessfulAction[sector] != Movement::Action::STOP) {
            return {lastSuccessfulAction[sector], true, MAX_SCORE, sector};
        }

        // Trouver l'action avec le meilleur score
        ActionScore bestAction = findHighestScoringAction(sector);
        
        // Si aucune action n'a de bon score, utiliser une stratégie adaptative
        if (bestAction.score == 0) {
            return computeAdaptiveStrategy(sector, sensorData);
        }

        return {bestAction.action, true, bestAction.score, sector};
    }

    ActionScore findHighestScoringAction(uint8_t sector) const {
        ActionScore best = scoreMatrix[sector][0];
        for (uint8_t i = 1; i < NUM_ACTIONS; i++) {
            if (scoreMatrix[sector][i].score > best.score) {
                best = scoreMatrix[sector][i];
            }
        }
        return best;
    }

    AvoidanceResult computeAdaptiveStrategy(uint8_t sector, const Sensors::SensorData& sensorData) {
        // Logique adaptative basée sur les conditions actuelles
        if (sensorData.frontDistance < MIN_DISTANCE) {
            if (sector < NUM_SECTORS/2) {
                return {Movement::Action::TURN_RIGHT, true, 1, sector};
            } else {
                return {Movement::Action::TURN_LEFT, true, 1, sector};
            }
        }
        
        return {Movement::Action::BACKWARD, true, 1, sector};
    }

    void updateScore(uint8_t sector, Movement::Action action, bool success) {
        for (auto& score : scoreMatrix[sector]) {
            if (score.action == action) {
                // Mise à jour des statistiques
                score.attempts++;
                if (success) {
                    score.successes++;
                }

                // Calcul du taux de succès
                float successRate = (float)score.successes / score.attempts;

                // Ajustement du score
                if (successRate >= SUCCESS_THRESHOLD && score.score < MAX_SCORE) {
                    score.score++;
                    rebalanceScores(sector, score.action);
                } else if (successRate <= FAILURE_THRESHOLD && score.score > 0) {
                    score.score--;
                }
                
                break;
            }
        }
    }

    void rebalanceScores(uint8_t sector, Movement::Action excludeAction) {
        // Réduire les scores des autres actions quand une action réussit
        for (auto& score : scoreMatrix[sector]) {
            if (score.action != excludeAction && score.score > 0) {
                score.score--;
            }
        }
    }

    void analyzeSuccessPatterns(uint8_t sector) {
        // Analyse des patterns de succès pour l'apprentissage à long terme
        ActionScore bestAction = findHighestScoringAction(sector);
        
        if (bestAction.successes > 5 && 
            (float)bestAction.successes / bestAction.attempts >= SUCCESS_THRESHOLD) {
            // Renforcer les actions qui réussissent constamment
            bestAction.score = std::min(bestAction.score + 1, MAX_SCORE);
        }
    }
};

#endif // STRATEGY_H