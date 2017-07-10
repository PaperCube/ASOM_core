#include "LaserModule.h"
#include "WString.h"
#include "sout.h"
using namespace serial;
#include <Arduino.h>

double LaserModule::majority(const int resamplingCnt)
{
    double sum = 0;
    for (int i = 0; i < resamplingCnt; i++)
    {
        sum += geometricalCenter();
    }

    return sum / resamplingCnt;
}

double LaserModule::majorityInMicros(const int resamplingTimeout)
{
    const long start = micros();
    double sum = 0;
    int cnt = 0;
    while (micros() - start < resamplingTimeout)
    {
        sum += geometricalCenter();
        cnt++;
    }

    return sum / cnt;
}

LaserModule::LaserModule(int (&dPins)[8])
{
    for (int i = 0; i < 8; i++)
    {
        pinMode(dPins[i], INPUT);
        pins[i] = dPins[i];
    }
}

String LaserModule::toString(const char placeholder)
{
    String result = "        ";
    for (int i = 0; i < 8; i++)
    {
        if (got(i))
            result[i] = placeholder;
    }

    return result;
}

bool LaserModule::got(int i)
{
    return !digitalRead(pins[i]);
    // return i < 4;
}

bool LaserModule::isBlack(int i)
{
    return digitalRead(pins[i]) == HIGH;
}

double LaserModule::geometricalCenter()
{
    double sum = 0;
    int sampleCnt = 0;
    double w = -3.5;
    for (int i = 0; i < 8; i++)
    {
        if (isBlack(i))
        {
            sum += w;
            sampleCnt++;
        }

        w += 1;
    }

    interference = sampleCnt / 8.0;
    sdebug << "sampleCnt " << sampleCnt << endl;

    return (sampleCnt == 0) ? 0 : sum / sampleCnt / 2.5;
}

bool LaserModule::aligned()
{
    return isBlack(0) && isBlack(7);
}