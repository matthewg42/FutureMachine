#pragma once

#include <PersistentSetting.h>
#include "Config.h"

extern PersistentSetting<uint16_t> InputDisplayPeriodMs;

// Used to automatically detect invalid settings
extern PersistentSetting<uint16_t> MagicSetting;


void checkSettings();
void resetSettings();
void printSettings();

