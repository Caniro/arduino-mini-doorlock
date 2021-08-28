#pragma once

#include <Arduino.h>
#include <EEPROM.h>

void writeRom(const int& address, const String& value);

String readRom(const int& address);
