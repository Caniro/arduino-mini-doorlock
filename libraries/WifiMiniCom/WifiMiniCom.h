#pragma once

#include <ESP8266WiFi.h>
#include <MiniCom.h>

class WifiMiniCom : public MiniCom
{
public:
    WifiMiniCom(int serial_bps=115200, int lcd_addr=0x27);
    void init(const char *ssid, const char *password);
};
