#include "MoodDial.h"
#include "Config.h"

const uint8_t MoodDialPins[] = { MOO1_PIN, MOO2_PIN, MOO3_PIN, MOO4_PIN, 
							     MOO5_PIN, MOO6_PIN, MOO7_PIN, MOO8_PIN };

MultiThrowSwitch MoodDial(8, MoodDialPins);

