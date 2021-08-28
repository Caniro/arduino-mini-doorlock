#pragma once

#include <Led.h>

class PWMLed: public Led
{
protected:
    int value;
public:
    PWMLed(int pin, int value=0);
    void setValue(int value);
};
