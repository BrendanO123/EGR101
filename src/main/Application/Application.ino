#include <EGR101Lib.h>

// Libraries
#include <Arduino.h>
#include "LowPower.h"

using namespace std;

// Vars
int delaySeconds;

inline void sleep(int seconds){
    for(int i = 0; i < seconds >> 3; i++){
        LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
    }
    for(int i = 0; i < (seconds & 7); i++){
        LowPower.powerDown(SLEEP_1S, ADC_OFF, BOD_OFF);
    }
}
void setup() {
    pinMode(uselessMachineMosfet, OUTPUT);
    digitalWrite(uselessMachineMosfet, HIGH);

    pinMode(uselessMachineReleaseReadyLED, OUTPUT);
    digitalWrite(uselessMachineReleaseReadyLED, HIGH);
    delay(750);
    digitalWrite(uselessMachineReleaseReadyLED, LOW);

    pinMode(speakerHigh, OUTPUT);
    pinMode(solenoidMosfet, OUTPUT);
    pinMode(delayPotentMosfet, OUTPUT);

    digitalWrite(delayPotentMosfet, LOW);
    digitalWrite(solenoidMosfet, LOW);
    digitalWrite(speakerHigh, LOW);

    pinMode(delayDialWiperPin, INPUT);
    int delay = EGR101Lib::readDelayConfig();

    sleep(delay);
    release();
    digitalWrite(uselessMachineMosfet, LOW);
}

void release(){
    digitalWrite(solenoidMosfet, HIGH);
    delay(releaseDurationMillis);
    digitalWrite(solenoidMosfet, LOW);

    tone(speakerHigh, soundFrequency);
    delay(soundDurationMillis);
    noTone(speakerHigh);
}

void loop(){}