#include <Arduino.h>
#include <MutilaDebug.h>
#include <Millis.h>
#include <FreeRam.h>
#include "HeartBeat.h"
#include "Lever.h"
#include "EarthDial.h"
#include "SeasonDial.h"
#include "MoodDial.h"
#include "FutureDial.h"
#include "RecordButton.h"
#include "CrankMonitor.h"

const uint16_t OutputPeriodMs = 500;
uint32_t LastOutputMs = 0;

void setup()
{
    Serial.begin(115200);
    HeartBeat.begin();
    Lever.begin();
    EarthDial.begin();
    SeasonDial.begin();
    MoodDial.begin();
    FutureDial.begin();
    RecordButton.begin();
    CrankMonitor.begin();
    pinMode(53, OUTPUT);
    digitalWrite(53, HIGH);
    DBLN(F("E:setup"));
}

void loop()
{
    HeartBeat.update();
    Lever.update();
    EarthDial.update();
    SeasonDial.update();
    MoodDial.update();
    FutureDial.update();
    RecordButton.update();
    CrankMonitor.update();

    if (DoEvery(OutputPeriodMs, LastOutputMs)) {
        DB("LEV");
        DB(Lever.position());

        DB(" EAR");
        DB(EarthDial.position());

        DB(" SEA");
        DB(SeasonDial.position());

        DB(" MOO");
        DB(MoodDial.position());

        DB(" FUT=");
        DB(FutureDial.position());

        DB(" REC=");
        DB(RecordButton.on());

        DB(" CRA=");
        DB(CrankMonitor.on());

        DB(" mem=");
        DBLN(FreeRam());
    }
}

