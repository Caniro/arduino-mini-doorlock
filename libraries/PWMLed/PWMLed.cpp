#include "PWMLed.h"

PWMLed::PWMLed(int pin, int value)
: Led(pin), value(value)
{
    analogWrite(pin, value);
}

void PWMLed::setValue(int value)
{
    this->value = value;
    analogWrite(pin, value);
}
