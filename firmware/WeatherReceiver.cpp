#include <MutilaDebug.h>
#include <Millis.h>
#include "WeatherReceiver.h"
#include "Config.h"

WeatherReceiverClass WeatherReceiver;

WeatherReceiverClass::WeatherReceiverClass() :
    lastSeq(0)
{
    resetData();
}

void WeatherReceiverClass::begin()
{
    DBLN(F("WeatherReceiver::begin"));
	HC12Serial.begin(HC12Baud);
	pinMode(HC12SetPin, OUTPUT);
	// Put the HC12 in receive mode (as opposted to setup mode)
	digitalWrite(HC12SetPin, HIGH);
}

void WeatherReceiverClass::printFields()
{
	Serial.println("# WEATHER,temperatureC,moisture,windSpeedMs,rainFallMmMinute,rainFallMmHour,rainFallMmDay");
}

void WeatherReceiverClass::update()
{
    // Timeout
    if ((magicPtr>0 || dataPtr>0) && Millis() - lastRead > WeatherReceiverTimeoutMs) {
        DBLN(F("timeout"));
        resetData();
    }

    while(HC12Serial.available()) {
        int c = HC12Serial.read();
        if (c < 0) {
            DBLN(F("WeatherReceiver: serial error"));
            resetData();
            break;
        }
        lastRead = Millis();
        if (!inPacket) {
            // do the magic...
            magicBuf[magicPtr++] = (uint8_t)c;
            if (!checkMagic()) { 
                DBLN(F("bad magic"));
                resetData(); 
                break; 
            }
            if (magicPtr == 2) {
                inPacket = true;
            }
            break;
        } else {
            packet.bytes[dataPtr++] = (uint8_t)c;
            if (dataPtr >= sizeof(WeatherPacket)) {
                checkWeatherPacket();
                resetData();
            }
        }
    }
}

void WeatherReceiverClass::checkWeatherPacket()
{
    if (!weatherPacketCsTest(&packet.data)) {
        DBLN(F("WeatherReceiver: bad checksum"));
    } else {
        DBLN(F("WeatherReceiver: good checksum"));
    }

    // Only handle a given message once
    if (packet.data.sequenceNumber != lastSeq) {
        lastSeq = packet.data.sequenceNumber;
        Serial.print(F("WEATHER,"));
        Serial.print(packet.data.temperatureC);
        Serial.print(',');
        Serial.print(packet.data.moisture);
        Serial.print(',');
        Serial.print(packet.data.windSpeedMs);
        Serial.print(',');
        Serial.print(packet.data.rainFallMmMinute);
        Serial.print(',');
        Serial.print(packet.data.rainFallMmHour);
        Serial.print(',');
        Serial.print(packet.data.rainFallMmDay);
		Serial.println();
    }
}

void WeatherReceiverClass::resetData()
{
    memset(magicBuf, 0, 2);
    magicPtr = 0;
    inPacket = false;
    dataPtr = 0;
}

bool WeatherReceiverClass::checkMagic()
{
    for (uint8_t i=0; i<magicPtr && i<2; i++) {
        if (magicBuf[i] != WeatherPacketMagic[i]) {
            return false;
        }
    }
    return true;
}

