#pragma once

#include <QuantizedPot.h>

class MoodDialClass : public QuantizedPot {
public:
	MoodDialClass();
	int8_t position() { return value(); }

};

extern MoodDialClass MoodDial;


