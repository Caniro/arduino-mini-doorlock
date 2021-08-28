#pragma once

#include <Arduino.h>

class Analog
{
protected:
    int pin;
    int from_min;
    int from_max;
    int to_min;
    int to_max;

public:
    Analog(int pin, int from_min, int from_max, int to_min, int to_max);
    Analog(int pin, int to_min, int to_max);
    void setRange(int from_min, int from_max, int to_min, int to_max);
    int read();
};
