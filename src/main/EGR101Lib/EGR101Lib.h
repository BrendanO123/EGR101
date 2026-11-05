#pragma once
#include <Settings.h>
#define uselessMachineMosfet 9
#define uselessMachineReleaseReadyLED 5

#define delayDialWiperPin A2
#define delayPotentMosfet 10

#define solenoidMosfet 3
#define speakerHigh 2

namespace EGR101Lib{
    int readDelayConfig();
}