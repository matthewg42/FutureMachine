#include "FutureDial.h"
#include "Config.h"

const uint8_t FutureDialPins[] = { FUT1_PIN, FUT2_PIN, FUT3_PIN, FUT4_PIN, 
							     FUT5_PIN, FUT6_PIN, FUT7_PIN, FUT8_PIN };

MultiThrowSwitch FutureDial(8, FutureDialPins);

