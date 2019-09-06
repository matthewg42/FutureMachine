#pragma once

#include "WeatherPacket.h"

class WeatherReceiverClass {
public:
    WeatherReceiverClass();
    void begin();
	void update();
	void printFields();

    // Called when new weather data comes in from the weather station
    void checkWeatherPacket();

protected:
    uint8_t magicBuf[2];
    uint8_t magicPtr;
    bool inPacket;
    uint8_t dataPtr;
    WeatherUnion packet;
    uint32_t lastRead;
    uint32_t lastSeq;

    void resetData();
    bool checkMagic();

};

extern WeatherReceiverClass WeatherReceiver;

