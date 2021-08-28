#pragma once

#include <Arduino.h>

class Led
{
protected:
    int pin; // 연결 핀 번호
public:
    Led(int pin);

    void on();
    void off();
    void setValue(int value);
    int toggle(); // 최종 상태 값 반환
};
