#include <Analog.h>

Analog::Analog(int pin, int from_min, int from_max,
        int to_min, int to_max)
: pin(pin), from_min(from_min), from_max(from_max), 
    to_min(to_min), to_max(to_max)
{}

Analog::Analog(int pin, int to_min, int to_max)
: pin(pin), to_min(to_min), to_max(to_max)
{
    from_min = 0;
    from_max = 1023;
}

void Analog::setRange(int from_min, int from_max, int to_min, int to_max)
{
    this->from_min = from_min;
    this->from_max = from_max;
    this->to_min = to_min;
    this->to_max = to_max;
}

int Analog::read()
{
    int value = analogRead(pin);
    return map(value, from_min, from_max, to_min, to_max);
}
