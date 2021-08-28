#pragma once

#include <Arduino.h>

class Buzzer
{
protected:
    int pin;
    int state; // HIGH or LOW
    int on_time;
    int off_time;
    unsigned long old_time; // 이전 상태 변화 시간
    bool bstop;

public:
    Buzzer(int pin);
    void beep(int time=50);
    void stop();
    void setOffTime(int off_time);
    void run();
};
