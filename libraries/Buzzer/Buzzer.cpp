#include "Buzzer.h"

Buzzer::Buzzer(int pin)
: pin(pin)
{
    state = LOW;
    off_time = 0;
    on_time = 100;
    old_time = millis();
    pinMode(pin, OUTPUT);
    bstop = true;
}

void Buzzer::beep(int time)
{
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
}

void Buzzer::stop()
{
    bstop = true;
    digitalWrite(pin, LOW);
}

void Buzzer::setOffTime(int off_time)
{
    this->off_time = off_time;
    bstop = false;
}

void Buzzer::run()
{
    unsigned long cur, diff;

    if (bstop) return;

    cur = millis();
    diff = cur - old_time;
    
    if (state)
    {
        if (diff > on_time) // 소리 출력 시간 끝
        {
            digitalWrite(pin, LOW);
            state = LOW;
            old_time = cur;
        }
    }
    else
    {
        if (diff > off_time) // 소리 출력할 시간이 됨
        {
            digitalWrite(pin, HIGH);
            state = HIGH;
            old_time = cur;
        }
    }
}
