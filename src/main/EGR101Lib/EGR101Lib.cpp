#include <Arduino.h>
#include "EGR101Lib.h"

inline double map(double a, double inMin, double inMax, double outMin, double outMax){
    return (a - inMin)/(inMax - inMin) * (outMax - outMin) + outMin;
}
inline double getVoltage(int pin){return map(analogRead(pin), 0.0, 1024.0, 0.0, 5.0);}
int EGR101Lib::readDelayConfig(){
    digitalWrite(delayPotentMosfet, HIGH);
    int delay = map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds) + 0.5;
    digitalWrite(delayPotentMosfet, LOW);
    return delay;
}