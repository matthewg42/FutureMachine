#pragma once

#include <Arduino.h>
#include <stdint.h>

// Weather station settings
#define HC12Serial Serial3
const long HC12Baud							= 4800;
const uint16_t WeatherReceiverTimeoutMs 	= 200;
const uint8_t WeatherPacketMagic[]      	= { 0x12, 0x13 };

// Pins
const uint8_t HC12SetPin					= 2;
const uint8_t HeartbeatPin	    			= 13;
const uint8_t LeverPins[] 					= { 26, 27, 28 };
const uint8_t EarthDialPins[] 				= { 29, 30, 31, 32 };
const uint8_t SeasonDialPins[] 				= { 33, 34, 35, 36 };
const uint8_t FutureDialPins[]				= { 37, 38, 39, 40, 41, 42, 43, 44 };
const uint8_t RecordButtonPin				= 45;
const uint8_t CrankSensorPin				= 46;
const uint8_t RecordIndicatorPin			= 47;
const uint8_t MoodDialPin					= A0;
const int MoodRanges[]                      = { 0, 8, 153, 298, 443, 588, 733, 878, 1024 };

// Change to force reset of saved settings
const uint16_t SettingsMagicNumber 			= 0xADDA;  

