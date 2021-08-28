#include "Led.h"

Led::Led(int pin) : pin(pin)
{
    pinMode(pin, OUTPUT);
}

void Led::on()
{
    digitalWrite(pin, HIGH);
}

void Led::off()
{
    digitalWrite(pin, LOW);
}

void Led::setValue(int value)
{
    digitalWrite(pin, value);
}

int Led::toggle()
{
    int v = !digitalRead(pin);
    digitalWrite(pin, v);
    return v;
}
