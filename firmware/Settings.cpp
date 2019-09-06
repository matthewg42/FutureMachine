#include <stdint.h>
#include "Settings.h"

// Params: min, max, default
PersistentSetting<uint16_t> InputDisplayPeriodMs(50, UINT16_MAX, 250);
PersistentSetting<uint16_t> MagicSetting(0, UINT16_MAX, SettingsMagicNumber);

void checkSettings()
{
    // Check if we have valid settings
    if (MagicSetting.get() != SettingsMagicNumber) {
        // Save all the settings with their default values
        Serial.println("# No settings found in EEPROM - using defaults...");
        resetSettings();
        MagicSetting.reset(true);
    } else {
        Serial.println("# Settings loaded from EEPROM");
    }
}

void resetSettings()
{
    Serial.println(F("# resetting defaults & saving to EEPROM"));
    InputDisplayPeriodMs.reset(true);
}

void printSettings()
{
	Serial.println(F("# Settings:"));
	Serial.print(F("# - InputDisplayPeriodMs = "));
	Serial.print(InputDisplayPeriodMs.get());
	if (InputDisplayPeriodMs.get() == InputDisplayPeriodMs.getDefault()) {
		Serial.print(F(" [default]"));
	}
	Serial.println();
}

