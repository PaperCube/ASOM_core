#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int digitalPin, int analogPin) : dPin(digitalPin), aPin(analogPin)
{
    speed = 0;
    pinMode(digitalPin, OUTPUT);
}

void Motor::setSpeed(int speed)
{
    this->speed = speed;
    digitalWrite(dPin, (speed > 0) ? HIGH : LOW);
    analogWrite(aPin, abs(speed));
}