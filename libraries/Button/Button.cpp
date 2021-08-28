#include <Button.h>

Button::Button(int pin) : pin(pin) {
    pinMode(pin, INPUT_PULLUP);
    callback = NULL;
}

void Button::setCallback(button_callback_t callback)
{
    this->callback = callback;
}

int Button::read()
{
    return !digitalRead(pin);
}

void Button::check()
{
    boolean o_sw, n_sw;

    o_sw = !digitalRead(pin);
    delay(10);
    n_sw = !digitalRead(pin);

    if (o_sw == OFF && n_sw == ON)
    {
        if (callback != NULL)
            callback();
    }
}

void Button::attachInterrupt(button_callback_t callback, int mode)
{
    ::attachInterrupt(digitalPinToInterrupt(pin), callback, mode);
    t1 = millis();
}

bool Button::debounce()
{
    unsigned long t2 = millis();

    if (t2 - t1 < 200) return false;

    t1 = t2;
    return true;
}
