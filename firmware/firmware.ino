// Arduino includes - must include any library used here, even if only used in
// a separate source, as the Arduino IDE uses this list to decide what libs
// to link...
#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

// Mutila includes
#include <MutilaDebug.h>
#include <Millis.h>
#include <FreeRam.h>

// Project objects
#include "Config.h"
#include "HeartBeat.h"
#include "Lever.h"
#include "EarthDial.h"
#include "SeasonDial.h"
#include "MoodDial.h"
#include "FutureDial.h"
#include "RecordButton.h"
#include "CrankMonitor.h"
#include "WeatherReceiver.h"
#include "CommandHandler.h"
#include "RecordIndicator.h"
#include "Settings.h"

// Globals for timers
uint16_t UpdatePeriodMs = 5;
uint32_t LastUpdateMs = 0;
uint32_t LastInputDisplayMs = 0;

void setup()
{
    Serial.begin(115200);
    DBLN(F("S:setup"));
    HeartBeat.begin();
    WeatherReceiver.begin();
    CommandHandler.begin(Serial);

    Lever.begin();
    EarthDial.begin();
    SeasonDial.begin();
    MoodDial.begin();
    FutureDial.begin();
    RecordButton.begin();
    CrankMonitor.begin();
    RecordIndicator.begin();
    RecordIndicator.setMode(Heartbeat::Off);

    checkSettings();
    printSettings();

    Serial.println(F("# INPUT,Lever,Earth,Season,Mood,Future,Record,Crank"));
    WeatherReceiver.printFields();
    DBLN(F("E:setup"));
}

void loop()
{

    if (DoEvery(UpdatePeriodMs, LastUpdateMs)) {
        CommandHandler.update();
        WeatherReceiver.update();
        HeartBeat.update();
        Lever.update();
        EarthDial.update();
        SeasonDial.update();
        MoodDial.update();
        FutureDial.update();
        RecordButton.update();
        CrankMonitor.update();
        RecordIndicator.update();
    }

    if (DoEvery(InputDisplayPeriodMs.get(), LastInputDisplayMs)) {
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


