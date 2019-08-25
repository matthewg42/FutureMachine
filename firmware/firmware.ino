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
#include "AltLever.h"

const uint16_t OutputPeriodMs = 200;
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
    AltLever.addRange(0, 200);
    AltLever.addRange(200, 400);
    AltLever.addRange(400, 600);
    AltLever.addRange(600, 800);
    AltLever.begin();
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
    AltLever.update();

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

        DB(" ALT[value=");
        DB(AltLever.value());
        DB(" velocity=");
        DB(AltLever.velocity());
        DB(" raw=");
        DB(analogRead(A15));
        DB(']');

        DB(" mem=");
        DBLN(FreeRam());
    }
}

