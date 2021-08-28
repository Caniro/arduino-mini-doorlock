#pragma once

#include <PWMLed.h>

class ColorLed
{
protected:
    PWMLed red;
    PWMLed green;
    PWMLed blue;

public:
    ColorLed(int red, int green, int blue); // 핀 번호
    void rgb(int r, int g, int b); // 0 ~ 255 PWM 값
    void off(int delay_time=0);
    void random();
};
