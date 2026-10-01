// Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include "ArduinoLowPower.h"
using namespace std;

/************** CONFIGURATION **************/
// Pins
#define uselessMachineMosfet 1

#define baseDelayMiddlePin 2
#define delayVariationMiddlePin 3
#define potentMosfet 4

#define solenoidMosfet 5
#define speakerMosfet 6
#define speakerHigh 7

// Potentiometer Ranges
#define minDelaySeconds 15 * 60
#define maxDelaySeconds 3 * 60 * 60

#define minDelayVariabilitySeconds 0
#define maxDelayVariabilitySeconds 30 * 60

#define potentMinV 0
#define potentMaxV 5

// EEPROM
#define EEPROMSeedIndex 16

#define SecondsToMs 1000

#define releaseDurationMillis 1000
#define soundDurationMillis 10 * 1000
#define soundFrequency 440

// Vars
int delaySeconds;

inline int getVoltage(int pin){return map(analogRead(pin), 0, 1024, 0, 5);}
inline pair<int,int> readDelayConfig(){
    digitalWrite(potentMosfet, HIGH);
    int baseDelay = map(getVoltage(baseDelayMiddlePin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
    int delayVariability = map(getVoltage(delayVariationMiddlePin), potentMinV, potentMaxV, minDelayVariabilitySeconds, maxDelayVariabilitySeconds);
    digitalWrite(potentMosfet, LOW);
    return pair<int,int>(baseDelay, delayVariability);
}
inline void loadSRand(){
    byte seed = EEPROM.read(EEPROMSeedIndex);
    srand(seed);
}
inline void calculateDelay(pair<int, int> delayConfig){
    loadSRand();
    EEPROM.write(EEPROMSeedIndex, ++seed);
    return rand() % (delayConfig.second << 1) - delayConfig.second + delayConfig.first;
}
void setup() {
    pinMode(uselessMachineMosfet, OUTPUT);
    digitalWriteFast(uselessMachineMosfet, HIGH);

    pinMode(speakerMosfet, OUTPUT);
    pinMode(speakerHigh, OUTPUT);
    pinMode(solenoidMosfet, OUTPUT);
    pinMode(potentMosfet, OUTPUT);

    digitalWrite(potentMosfet, LOW);
    digitalWrite(solenoidMosfet, LOW);
    digitalWrite(speakerMosfet, LOW);
    digitalWrite(speakerHigh, LOW);

    pinMode(baseDelayMiddlePin, INPUT);
    pinMode(delayVariationMiddlePin, INPUT);
    auto delayConfig = readDelayConfig();
    delaySeconds = calculateDelay(delayConfig);

    LowPower.deepSleep(delaySeconds * SecondsToMs);
    release();
    digitalWriteFast(uselessMachineMosfet, LOW);
}

void release(){
    digitalWrite(solenoidMosfet, HIGH);
    digitalWrite(speakerMosfet, HIGH);

    tone(speakerHigh, soundFrequency);

    delay(releaseDurationMillis);
    digitalWrite(solenoidMosfet, LOW);

    delay(max(soundDurationMillis - releaseDurationMillis, 0));
    noTone(speakerHigh);
    digitalWrite(speakerMosfet, LOW);
}

void loop(){}