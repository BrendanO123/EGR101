// Libraries
#include <Arduino.h>
#include "Constants.h"
using namespace std;

// Vars
int delaySeconds;

inline int getVoltage(int pin){return map(analogRead(pin), 0, 1024, 0, 5);}
inline int readDelayConfig(){
    return map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
}
void setup() {
    Serial.begin(115200);
    Serial.println(F("Initialization Started"));
    pinMode(uselessMachineMosfet, OUTPUT);
    digitalWriteFast(uselessMachineMosfet, HIGH);

    pinMode(speakerMosfet, OUTPUT);
    pinMode(speakerHigh, OUTPUT);
    pinMode(solenoidMosfet, OUTPUT);
    pinMode(delayPotentMosfet, OUTPUT);

    digitalWrite(solenoidMosfet, LOW);
    digitalWrite(speakerMosfet, LOW);
    digitalWrite(speakerHigh, LOW);

    digitalWrite(delayPotentMosfet, HIGH);
    pinMode(delayDialWiperPin, INPUT);
}
void loop(){
    Serial.println(F("Voltage: %d; Delay (Minutes): %d", getVoltage(delayDialWiperPin), readDelayConfig()));
    delay(100);
}