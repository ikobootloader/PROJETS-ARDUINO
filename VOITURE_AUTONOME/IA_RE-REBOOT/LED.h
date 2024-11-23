#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
    // États possibles du robot
    enum class Status {
        INITIALIZING,     // Initialisation en cours
        READY,           // Prêt à fonctionner
        RUNNING,         // En fonctionnement normal
        AVOIDING,        // Évitement d'obstacle
        CHARGING,        // En charge
        LOW_BATTERY,     // Batterie faible
        ERROR           // Erreur
    };

    // Configuration des pins LED
    struct LedPins {
        uint8_t redPin;     // LED rouge
        uint8_t yellowPin;  // LED jaune
        uint8_t greenPin;   // LED verte
    };

private:
    static constexpr LedPins DEFAULT_PINS = {
        .redPin = A3,
        .yellowPin = 8,
        .greenPin = 11
    };

    LedPins pins;
    Status currentStatus;
    unsigned long lastBlinkTime;
    bool blinkState;
    
    // Paramètres de clignotement
    static constexpr unsigned long BLINK_INTERVAL_NORMAL = 1000;  // ms
    static constexpr unsigned long BLINK_INTERVAL_FAST = 200;     // ms
    static constexpr unsigned long BLINK_INTERVAL_SLOW = 2000;    // ms

public:
    LED(const LedPins& ledPins = DEFAULT_PINS) 
        : pins(ledPins)
        , currentStatus(Status::INITIALIZING)
        , lastBlinkTime(0)
        , blinkState(false) {}

    void setup() {
        pinMode(pins.redPin, OUTPUT);
        pinMode(pins.yellowPin, OUTPUT);
        pinMode(pins.greenPin, OUTPUT);
        
        // Test initial des LEDs
        testLeds();
    }

    void setStatus(Status status) {
        currentStatus = status;
        updateLeds();
    }

    void update() {
        switch (currentStatus) {
            case Status::INITIALIZING:
                blinkAll();
                break;
            
            case Status::LOW_BATTERY:
                blinkLed(pins.redPin, BLINK_INTERVAL_FAST);
                break;
            
            case Status::CHARGING:
                blinkLed(pins.yellowPin, BLINK_INTERVAL_NORMAL);
                break;
            
            case Status::AVOIDING:
                blinkLed(pins.redPin, BLINK_INTERVAL_NORMAL);
                break;
            
            case Status::ERROR:
                blinkAllFast();
                break;
            
            default:
                updateLeds();  // État statique
                break;
        }
    }

private:
    void updateLeds() {
        switch (currentStatus) {
            case Status::READY:
                setLed(pins.greenPin, true);
                setLed(pins.yellowPin, false);
                setLed(pins.redPin, false);
                break;

            case Status::RUNNING:
                setLed(pins.greenPin, true);
                setLed(pins.yellowPin, false);
                setLed(pins.redPin, false);
                break;

            case Status::AVOIDING:
                setLed(pins.greenPin, false);
                setLed(pins.yellowPin, false);
                setLed(pins.redPin, true);
                break;

            case Status::CHARGING:
                setLed(pins.greenPin, false);
                setLed(pins.yellowPin, true);
                setLed(pins.redPin, false);
                break;

            case Status::LOW_BATTERY:
                setLed(pins.greenPin, false);
                setLed(pins.yellowPin, false);
                setLed(pins.redPin, true);
                break;

            case Status::ERROR:
                setLed(pins.greenPin, false);
                setLed(pins.yellowPin, false);
                setLed(pins.redPin, true);
                break;

            default:
                setLed(pins.greenPin, false);
                setLed(pins.yellowPin, true);
                setLed(pins.redPin, false);
                break;
        }
    }

    void setLed(uint8_t pin, bool state) {
        digitalWrite(pin, state ? HIGH : LOW);
    }

    void blinkLed(uint8_t pin, unsigned long interval) {
        unsigned long currentTime = millis();
        if (currentTime - lastBlinkTime >= interval) {
            blinkState = !blinkState;
            setLed(pin, blinkState);
            lastBlinkTime = currentTime;
        }
    }

    void blinkAll() {
        unsigned long currentTime = millis();
        if (currentTime - lastBlinkTime >= BLINK_INTERVAL_NORMAL) {
            blinkState = !blinkState;
            setLed(pins.redPin, blinkState);
            setLed(pins.yellowPin, blinkState);
            setLed(pins.greenPin, blinkState);
            lastBlinkTime = currentTime;
        }
    }

    void blinkAllFast() {
        unsigned long currentTime = millis();
        if (currentTime - lastBlinkTime >= BLINK_INTERVAL_FAST) {
            blinkState = !blinkState;
            setLed(pins.redPin, blinkState);
            setLed(pins.yellowPin, blinkState);
            setLed(pins.greenPin, blinkState);
            lastBlinkTime = currentTime;
        }
    }

    void testLeds() {
        // Allumer chaque LED séquentiellement
        setLed(pins.redPin, true);
        delay(200);
        setLed(pins.redPin, false);
        
        setLed(pins.yellowPin, true);
        delay(200);
        setLed(pins.yellowPin, false);
        
        setLed(pins.greenPin, true);
        delay(200);
        setLed(pins.greenPin, false);
        
        delay(200);
    }
};

#endif // LED_H