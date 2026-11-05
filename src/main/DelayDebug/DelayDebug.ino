#include <EGR101Lib.h>

// Libraries
#include <Arduino.h>
using namespace std;

// Vars
int delaySeconds;

inline double map(double a, double inMin, double inMax, double outMin, double outMax){
    return (a - inMin)/(inMax - inMin) * (outMax - outMin) + outMin;
}
inline double getVoltage(int pin) {
  return map(analogRead(pin), 0.0, 1024.0, 0.0, 5.0);
}
inline int readDelayConfig() {
  return map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds) + 0.5;
}
void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialization Started"));
  pinMode(uselessMachineMosfet, OUTPUT);
  digitalWrite(uselessMachineMosfet, HIGH);

  pinMode(speakerHigh, OUTPUT);
  pinMode(solenoidMosfet, OUTPUT);
  pinMode(delayPotentMosfet, OUTPUT);

  digitalWrite(solenoidMosfet, LOW);
  digitalWrite(speakerHigh, LOW);

  digitalWrite(delayPotentMosfet, HIGH);
  pinMode(delayDialWiperPin, INPUT);
}
void loop() {
  Serial.print("Voltage: "); Serial.print(getVoltage(delayDialWiperPin)); Serial.print("; Delay (Minutes): "); Serial.println(readDelayConfig());
  delay(100);
}