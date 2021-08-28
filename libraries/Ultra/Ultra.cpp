#include "Ultra.h"

Ultra::Ultra(int echo, int trig)
: echo(echo), trig(trig)
{
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
    on_f = NULL;
    off_f = NULL;
    state = false;
}

int Ultra::getDistance()
{
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    return pulseIn(echo, HIGH) / 58; // 0.017 * 시간
}

void Ultra::setThreshold(int t, ultra_callback_t on_f, ultra_callback_t off_f)
{
    threshold = t;
    this->on_f = on_f;
    this->off_f = off_f;
}

int Ultra::run()
{
    int distance = getDistance();
    if (!state && distance <= threshold) // 기준 거리 내로 진입
    {
        state = true;
        if (on_f)
            on_f();
    }
    // 기준 거리를 벗어남
    else if (state && (distance == 0 || distance > (threshold + 2)))
    {
        state = false;
        if (off_f)
            off_f();
    }

    // if (distance == 0 || distance > threshold)
    //     return 0;
    
    return distance;
}
