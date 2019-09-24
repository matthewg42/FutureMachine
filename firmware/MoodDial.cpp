#include "MoodDial.h"
#include "Config.h"

MoodDialClass MoodDial;

MoodDialClass::MoodDialClass() :
	QuantizedPot(MoodDialPin, 8)
{
	for (uint8_t i=0; i<8; i++) {
		addRange(MoodRanges[i], MoodRanges[i+1]);
	}
}


