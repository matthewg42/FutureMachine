#include <Arduino.h>

#include "Format.h"
#include "WeatherReceiver.h"
#include "Lever.h"
#include "EarthDial.h"
#include "SeasonDial.h"
#include "MoodDial.h"
#include "FutureDial.h"
#include "RecordButton.h"
#include "CrankMonitor.h"

void printRecordFormats()
{
    Serial.println(F("# INPUT,Lever,Earth,Season,Mood,Future,Record,Crank"));
    WeatherReceiver.printFields();
}

void printInputRecord()
{
	Serial.print(F("INPUT,"));
	Serial.print(Lever.position());
	Serial.print(',');
	Serial.print(EarthDial.position());
	Serial.print(',');
	Serial.print(SeasonDial.position());
	Serial.print(',');
	Serial.print(MoodDial.position()+1);
	Serial.print(',');
	Serial.print(FutureDial.position());
	Serial.print(',');
	Serial.print(RecordButton.on());
	Serial.print(',');
	Serial.print(CrankMonitor.on());
	Serial.println();
}

