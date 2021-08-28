#include "WifiMiniCom.h"

WifiMiniCom::WifiMiniCom(int serial_bps, int lcd_addr)
: MiniCom(serial_bps, lcd_addr)
{}

void WifiMiniCom::init(const char *ssid, const char *password)
{
    MiniCom::init();

    WiFi.begin(ssid, password);
    print(0, "Try to connect");
    Serial.println();
    while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.print(".");
	}
		
	print(0, "WiFi connected");
	print(1, WiFi.localIP().toString().c_str());
	Serial.println();
	Serial.println(WiFi.localIP());
}
