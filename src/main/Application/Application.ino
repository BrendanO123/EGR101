// Libraries
#include <Arduino.h>
#include <EEPROM.h>
#include "ArduinoLowPower.h"
using namespace std;

/************** CONFIGURATION **************/
// Pins
#define baseDelayMiddlePin 1
#define delayVariationMiddlePin 2

#define uselessMachineMosfet 3
#define speakerMosfet 4
#define solenoidHigh 5

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
#define releaseDurationMillis 500

// Vars
int delaySeconds;

inline getVoltage(int pin){return map(analogRead(pin), 0, 1024, 0, 5);}
inline pair<int,int> readDelayConfig(){
    int baseDelay = map(getVoltage(baseDelayMiddlePin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
    int delayVariability = map(getVoltage(delayVariationMiddlePin), potentMinV, potentMaxV, minDelayVariabilitySeconds, maxDelayVariabilitySeconds);
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

    digitalWrite(solenoidHigh, LOW);
    digitalWrite(speakerMosfet, LOW);

    pinMode(baseDelayMiddlePin, INPUT);
    pinMode(delayVariationMiddlePin, INPUT);
    auto delayConfig = readDelayConfig();
    delaySeconds = calculateDelay(delayConfig);

    LowPower.deepSleep(delaySeconds * SecondsToMs);
    release();
    digitalWriteFast(uselessMachineMosfet, LOW);
}

void release(){
    digitalWrite(solenoidHigh, HIGH);
    delay(releaseDurationMillis);
    digitalWrite(solenoidHigh, LOW);

    digitalWrite(speakerMosfet, HIGH);
    //TODO: play sound
    digitalWrite(speakerMosfet, LOW);
}