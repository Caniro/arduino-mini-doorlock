#include "storage.h"

void writeRom(const int& address, const String& value)
{
    int length = value.length();

    EEPROM.write(address, length);
    for (int ix = 0; ix < length; ++ix)
    {
        EEPROM.write(address + 1 + ix, value.charAt(ix));
        delay(100);
    }
}

String readRom(const int& address)
{
    String value = "";

    int length = EEPROM.read(address);
    for (int ix = 0; ix < length; ++ix)
    {
        value += (char)EEPROM.read(address + 1 + ix);
        delay(100);
    }
    return value;
}
