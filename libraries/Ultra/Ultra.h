#pragma once

#include <Arduino.h>

typedef void (*ultra_callback_t)();

class Ultra
{
protected:
    int echo;
    int trig;
    int threshold;
    ultra_callback_t on_f;
    ultra_callback_t off_f;
    int state;

public:
    Ultra(int echo, int trig);
    int getDistance();
    void setThreshold(int t, ultra_callback_t on_f, ultra_callback_t off_f);
    int run();
};
