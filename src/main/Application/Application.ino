// Libraries
#include <Arduino.h>
#include "ArduinoLowPower.h"
#include "Constants.h"

using namespace std;

// Vars
int delaySeconds;

inline int getVoltage(int pin){return map(analogRead(pin), 0, 1024, 0, 5);}
inline int readDelayConfig(){
    digitalWrite(delayPotentMosfet, HIGH);
    int delay = map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
    digitalWrite(delayPotentMosfet, LOW);
    return delay;
}
void setup() {
    pinMode(uselessMachineMosfet, OUTPUT);
    digitalWriteFast(uselessMachineMosfet, HIGH);

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

    LowPower.deepSleep(delay * SecondsToMs);
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