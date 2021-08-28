#pragma once

#include <Arduino.h>

#define OFF 0
#define ON 1

typedef void (*button_callback_t)();

class Button {
protected:
    int pin;
    button_callback_t callback;
    unsigned long t1;

public:
    Button(int pin);
    void setCallback(button_callback_t callback);
    int read();
    void check();
    void attachInterrupt(button_callback_t callback, int mode=FALLING);
    bool debounce();
};
