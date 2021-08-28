#include "MqttCom.h"

MqttCom::MqttCom(int serial_bps, int lcd_addr)
: WifiMiniCom(serial_bps, lcd_addr), client(espClient)
{
    topic = NULL;
    callback = NULL;
    server = NULL;

    randomSeed(analogRead(0));
    int r = random(300);
    client_id = String("ESP8266Client") + r;
}

void MqttCom::init(const char *ssid, const char *password, int no_lcd)
{
    WifiMiniCom::init(ssid, password);
    if (no_lcd)
        WifiMiniCom::setNoLcd();
}

void MqttCom::setServer(const char *server, const char *topic, 
                MQTT_CALLBACK_SIGNATURE)
{
    this->server = server;
    this->callback = callback;
    this->topic = topic;
    
    client.setServer(server, 1883);
    if (callback)
        client.setCallback(callback);
}

void MqttCom::reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        print(0, "try MQTT con...");
        if (client.connect(client_id.c_str()))
        {
            Serial.println("connected");
            print(1, "connected");
            if (topic)
                client.subscribe(topic);
        }
        else
        {
            char buf[17];
            sprintf(buf, "failed, rc=%d", client.state());
            Serial.print(buf);
            print(0, buf);
            Serial.println(" try again in 5 seconds");
            print(1, "try again in 5 sec");
            delay(5000);
        }
    }
}

void MqttCom::run()
{
    MiniCom::run();
    if (!client.connected())
        reconnect();
    client.loop();
}


void MqttCom::publish(const char *topic, const char *value)
{
    client.publish(topic, value);
}

void MqttCom::publish(const char *topic, int value)
{
    char msg[10];
    sprintf(msg, "%d", value);
    client.publish(topic, msg);
}

void MqttCom::publish(const char *topic, float value)
{
    String msg("");
    msg += value;
    client.publish(topic, msg.c_str());
}
