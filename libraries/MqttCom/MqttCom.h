#pragma once

#include <WifiMiniCom.h>
#include <PubSubClient.h>

class MqttCom: public WifiMiniCom
{
protected:
    const char *server;
    String client_id;
    WiFiClient espClient;
    PubSubClient client;

    const char *topic;
    MQTT_CALLBACK_SIGNATURE;

public:
    MqttCom(int serial_bps=115200, int lcd_addr=0x27);
    void init(const char *ssid, const char *password, int no_lcd=false);
    void setServer(const char *server, const char *topic = NULL,
                MQTT_CALLBACK_SIGNATURE=NULL);
    void reconnect();
    void run();

    void publish(const char *topic, const char *value);
    void publish(const char *topic, int value);
    void publish(const char *topic, float value);
};
