// Libraries
#include <Arduino.h>
#include "LowPower.h"
#define uselessMachineMosfet 13
#define uselessMachineReleaseReadyLED 12

#define delayDialWiperPin A0
#define delayPotentMosfet 7

#define solenoidMosfet 2
#define speakerMosfet 9
#define speakerHigh 8

// Potentiometer Ranges
#define minDelaySeconds 1
#define maxDelaySeconds 10

#define potentMinV 0.0
#define potentMaxV 3.3

#define releaseDurationMillis 1 * 1000
#define soundDurationMillis 3 * 1000
#define soundFrequency 300

using namespace std;

// Vars
int delaySeconds;

inline void sleep(int seconds){
    for(int i = 0; i < seconds >> 3; i++){
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
    for(int i = 0; i < seconds & 7; i++){
        LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    }
}
inline double map(double a, double inMin, double inMax, double outMin, double outMax){
    return (a - inMin)/(inMax - inMin) * (outMax - outMin) + outMin;
}
inline double getVoltage(int pin){return map(analogRead(pin), 0.0, 1024.0, 0.0, 5.0);}
inline int readDelayConfig(){
    digitalWrite(delayPotentMosfet, HIGH);
    int delay = map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
    digitalWrite(delayPotentMosfet, LOW);
    return delay;
}
void setup() {
    pinMode(uselessMachineMosfet, OUTPUT);
    digitalWrite(uselessMachineMosfet, HIGH);

    pinMode(uselessMachineReleaseReadyLED, OUTPUT);
    digitalWrite(uselessMachineReleaseReadyLED, HIGH);
    delay(750);
    digitalWrite(uselessMachineReleaseReadyLED, LOW);

    pinMode(speakerMosfet, OUTPUT);
    pinMode(speakerHigh, OUTPUT);
    pinMode(solenoidMosfet, OUTPUT);
    pinMode(delayPotentMosfet, OUTPUT);

    digitalWrite(delayPotentMosfet, LOW);
    digitalWrite(solenoidMosfet, LOW);
    digitalWrite(speakerMosfet, LOW);
    digitalWrite(speakerHigh, LOW);

    pinMode(delayDialWiperPin, INPUT);
    int delay = readDelayConfig();

    sleep(delay);
    release();
    digitalWrite(uselessMachineMosfet, LOW);
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