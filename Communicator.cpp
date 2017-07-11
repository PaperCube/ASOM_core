#include "Communicator.h"
#include <Arduino.h>
#include "colortypes.h"
#include "TCS3200.h"
#include "colordivision.h"

using namespace util;
namespace communication
{
Communicator::Communicator(int pwmOut,
                           int monitor,
                           int notifier) : pwmOutPin(pwmOut),
                                           monitorPin(monitor),
                                           notifierPin(notifier)
{
    pinMode(pwmOutPin, OUTPUT);
    pinMode(monitorPin, INPUT);
    pinMode(notifierPin, OUTPUT);
}

void Communicator::awaitResponse(const unsigned long timeout = 0xFFFFFFFF)
{
    unsigned long start = millis();
    while (true)
    {
        if ((millis() - start) > timeout || isReplyRequested())
            return;
    }
}

bool Communicator::isReplyRequested()
{
    return digitalRead(monitorPin) != HIGH;
}

void Communicator::sendBack(ColorType clr)
{
    static const int typeCodeMap[] = {31, 0, 1, 2, 3, 4};
    analogWrite(pwmOutPin, typeCodeMap[clr]);
}

void Communicator::setStateReady(bool state)
{
    digitalWrite(notifierPin, state ? HIGH : LOW);
}

void Communicator::takeOverAll(TCS3200Controller &controller, BreakCondition brk)
{
    using namespace colordiv;

    setStateReady(true);

    ColorDivision div;
    controller.performWhiteBalance();

    bool exit = false;
    while (true)
    {
        while (!isReplyRequested())
            if (brk != nullptr && brk())
            {
                exit = true;
                break;
            }

        if (exit)
            break;

        setStateReady(false);
        sendBack(div.toColorType(controller.measureColor(30).toHSL()));
        setStateReady(true);
    }
}
}