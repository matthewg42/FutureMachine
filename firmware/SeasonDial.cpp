#include "SeasonDial.h"
#include "Config.h"

const uint8_t SeasonDialPins[] = { SEA1_PIN, SEA2_PIN, SEA3_PIN, SEA4_PIN };

MultiThrowSwitch SeasonDial(4, SeasonDialPins);

