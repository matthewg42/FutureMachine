#include "EarthDial.h"
#include "Config.h"

const uint8_t EarthDialPins[] = { EAR1_PIN, EAR2_PIN, EAR3_PIN, EAR4_PIN };

MultiThrowSwitch EarthDial(4, EarthDialPins);

