// Arduino includes - must include any library used here, even if only used in
// a separate source, as the Arduino IDE uses this list to decide what libs
// to link...
#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>

#ifndef NOWATCHDOG
#include <avr/wdt.h>
#endif

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
#include "Format.h"

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

    // Visual indicator that arduino is restarting
#ifdef FLASHRECONBOOT
    RecordIndicator.setMode(Heartbeat::Quick);
    while (Millis() < 1000) {
        RecordIndicator.update();
    }
#endif
    RecordIndicator.setMode(Heartbeat::Off);

    checkSettings();
    printSettings();

    printRecordFormats();

#ifndef NOWATCHDOG
    // Enable watchdog
    // WDTO_15MS WDTO_30MS WDTO_60MS WDTO_120MS WDTO_250MS WDTO_500MS WDTO_1S WDTO_2S WDTO_4S WDTO_8S
    wdt_enable(WDTO_120MS);
#endif

    DBLN(F("E:setup"));
}

void loop()
{
#ifndef NOWATCHDOG
    // Feed the watchdog
    wdt_reset();
#endif

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
        printInputRecord();
    }

}


