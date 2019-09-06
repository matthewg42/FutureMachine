#pragma once

#include <Arduino.h>
#include <stdint.h>

// Weather station settings
#define HC12Serial Serial1
const long HC12Baud							= 4800;
const uint16_t WeatherReceiverTimeoutMs 	= 200;
const uint8_t WeatherPacketMagic[]      	= { 0x12, 0x13 };

// Pins
const uint8_t HC12SetPin					= 20;
const uint8_t HeartbeatPin	    			= 13;
const uint8_t LeverPins[] 					= { 22, 23, 24 };
const uint8_t EarthDialPins[] 				= { 26, 27, 28, 29 };
const uint8_t SeasonDialPins[] 				= { 30, 31, 32, 33 };
const uint8_t MoodDialPins[] 				= { 34, 35, 36, 37, 38, 39, 40, 41 };
const uint8_t FutureDialPins[]				= { 42, 43, 44, 45, 46, 47, 48, 49 };
const uint8_t RecordButtonPin				= 50;
const uint8_t CrankSensorPin				= 51;
const uint8_t RecordIndicatorPin			= 52;

// Change to force reset of saved settings
const uint16_t SettingsMagicNumber 			= 0xADDA;  

