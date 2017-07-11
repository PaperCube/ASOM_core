#include "TriDigit.h"
#include <Arduino.h>

namespace communication
{

TriDigit::TriDigit(int pinA,
                   int pinB,
                   int pinC,
                   bool isOutMode) : isOut(isOutMode)
{
    pins[0] = pinA;
    pins[1] = pinB;
    pins[2] = pinC;

    for (int i = 0; i < 3; i++)
    {
        pinMode(pins[i], isOutMode ? OUTPUT : INPUT);
    }
}

void TriDigit::write(const byte value)
{
    for (int i = 0; i < 3; i++)
    {
        digitalWrite(pins[i], (value >> i) & 1);
    }
}

int TriDigit::read()
{
    int result = 0;
    for (int i = 0; i < 3; i++)
    {
        result |= (digitalRead(pins[i]) << i);
    }

    return result;
}
}