// Libraries
#include <Arduino.h>
#define uselessMachineMosfet 13
#define uselessMachineReleaseReadyLED 12

#define delayDialWiperPin A0
#define delayPotentMosfet 7

#define solenoidMosfet 4
#define speakerMosfet 5
#define speakerHigh 6

// Potentiometer Ranges
#define minDelaySeconds 1
#define maxDelaySeconds 10

#define potentMinV 0.0
#define potentMaxV 3.3

#define SecondsToMs 1000

#define releaseDurationMillis 1000
#define soundDurationMillis 10 * 1000
#define soundFrequency 440
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
  return map(getVoltage(delayDialWiperPin), potentMinV, potentMaxV, minDelaySeconds, maxDelaySeconds);
}
void setup() {
  Serial.begin(9600);
  Serial.println(F("Initialization Started"));
  pinMode(uselessMachineMosfet, OUTPUT);
  digitalWrite(uselessMachineMosfet, HIGH);

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
void loop() {
  Serial.print("Voltage: "); Serial.print(getVoltage(delayDialWiperPin)); Serial.print("; Delay (Minutes): "); Serial.println(readDelayConfig());
  delay(100);
}