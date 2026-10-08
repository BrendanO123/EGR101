using namespace std;

/************** CONFIGURATION **************/
// Pins
#define uselessMachineMosfet 1

#define delayDialWiperPin 2
#define delayPotentMosfet 3

#define solenoidMosfet 4
#define speakerMosfet 5
#define speakerHigh 6

// Potentiometer Ranges
#define minDelaySeconds 1 * 60 * 60
#define maxDelaySeconds 3 * 60 * 60

#define potentMinV 0
#define potentMaxV 5

#define SecondsToMs 1000

#define releaseDurationMillis 1000
#define soundDurationMillis 10 * 1000
#define soundFrequency 440