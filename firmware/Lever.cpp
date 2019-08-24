#include "Lever.h"
#include "Config.h"

const uint8_t LeverPins[] = { LEV1_PIN, LEV2_PIN, LEV3_PIN };

MultiThrowSwitch Lever(3, LeverPins);

