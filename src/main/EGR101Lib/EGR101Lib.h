#pragma once
#include <Settings.h>
#define uselessMachineMosfet 9
#define uselessMachineReleaseReadyLED 12

#define delayDialWiperPin A7
#define delayPotentMosfet 10

#define solenoidMosfet 5
#define speakerMosfet 4
#define speakerHigh 3

#define releaseDurationMillis 1 * 1000
#define soundDurationMillis 3 * 1000
#define soundFrequency 300
namespace EGR101Lib{
    int readDelayConfig();
}