#include <Arduino.h>
#include "BuiltInLED.h"

namespace util
{
LED::LED(int digitalPin) : pin(digitalPin) {
    pinMode(digitalPin, OUTPUT);
}

void LED::setState(bool isOn)
{
    digitalWrite(pin, isOn ? HIGH : LOW);
}

void LED::on()
{
    setState(true);
}

void LED::off()
{
    setState(false);
}
}