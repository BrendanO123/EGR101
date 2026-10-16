using namespace std;

/************** CONFIGURATION **************/
// Pins
#define uselessMachineMosfet 13
#define uselessMachineReleaseReadyLED 12 

#define delayDialWiperPin A0
#define delayPotentMosfet 6

#define solenoidMosfet 4
#define speakerMosfet 5
#define speakerHigh 6

// Potentiometer Ranges
#define minDelaySeconds 1
#define maxDelaySeconds 10

#define potentMinV 0
#define potentMaxV 3.3

#define SecondsToMs 1000

#define releaseDurationMillis 1000
#define soundDurationMillis 10 * 1000
#define soundFrequency 440