#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <FreeRam.h>

#include "Config.h"
#include "HeartBeat.h"
#include "Lever.h"
#include "EarthDial.h"
#include "SeasonDial.h"
#include "MoodDial.h"
#include "FutureDial.h"
#include "RecordButton.h"
#include "CrankMonitor.h"
#include "AltLever.h"
#include "WeatherReceiver.h"

const uint16_t OutputPeriodMs = 200;
const uint16_t UpdatePeriodMs = 25;
uint32_t LastUpdateMs = 0;
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    DBLN(F("S:setup"));
    HeartBeat.begin();
    WeatherReceiver.begin();
    Lever.begin();
    EarthDial.begin();
    SeasonDial.begin();
    MoodDial.begin();
    FutureDial.begin();
    RecordButton.begin();
    CrankMonitor.begin();
    AltLever.addRange(0, 200);
    AltLever.addRange(200, 400);
    AltLever.addRange(400, 600);
    AltLever.addRange(600, 800);
    AltLever.begin();
    pinMode(53, OUTPUT);
    digitalWrite(53, HIGH);

    Serial.println(F("#INPUT,Lever,Earth,Season,Mood,Future,Record,Crank"));
    WeatherReceiver.printFields();
    DBLN(F("E:setup"));
}

void loop()
{
    if (DoEvery(UpdatePeriodMs, LastUpdateMs)) {
        HeartBeat.update();
        WeatherReceiver.update();
        Lever.update();
        EarthDial.update();
        SeasonDial.update();
        MoodDial.update();
        FutureDial.update();
        RecordButton.update();
        CrankMonitor.update();
        AltLever.update();
    }

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        Serial.print(F("INPUT,"));
        Serial.print(Lever.position());
        Serial.print(',');
        Serial.print(EarthDial.position());
        Serial.print(',');
        Serial.print(SeasonDial.position());
        Serial.print(',');
        Serial.print(MoodDial.position());
        Serial.print(',');
        Serial.print(FutureDial.position());
        Serial.print(',');
        Serial.print(RecordButton.on());
        Serial.print(',');
        Serial.print(CrankMonitor.on());
        Serial.println();
    }

}


