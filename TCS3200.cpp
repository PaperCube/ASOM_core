#include "TCS3200.h"
#include <Arduino.h>
#include "sout.h"
#include "mathutil.h"
#include <EEPROM.h>

namespace util
{
using namespace serial;
using namespace mathutil;

static const int blcfgLength = sizeof(TCS3200Controller::BalanceConfig);
static int wbcfgHeaderAddr = 0; //These two declaraction are used when balance configurations are saved in EEPROM

TCS3200Controller::TCS3200Controller()
{
    // int idx = wbcfgHeaderAddr;
    // if (EEPROM.read(idx++) == blcfgLength)
    //     EEPROM.get(idx, wbcfg);

    // idx += blcfgLength;

    // if (EEPROM.read(idx++) == blcfgLength)
    //     EEPROM.get(idx, bbcfg);

}

TCS3200Controller::~TCS3200Controller()
{
}

TCS3200Controller::TCS3200Controller(const TCS3200Controller &con)
{
}

void TCS3200Controller::attachSwitchesPin(int (&switches)[4])
{
    for (int i = 0; i < 4; i++)
    {
        attachSwitchPin(i, switches[i]);
    }
}

void TCS3200Controller::attachSwitchPin(int ordinal, int pin)
{
    switchesPin[ordinal] = pin;
}

void TCS3200Controller::attachOEPin(int pin)
{
    OEPin = pin;
}

void TCS3200Controller::attachLEDPin(int pin)
{
    LEDPin = pin;
}

void TCS3200Controller::attachOutPin(int pin)
{
    outPin = pin;
}

void TCS3200Controller::setColorFilterMode(TCS3200Controller::FilterMode filterMode)
{
    int pinState[2];
    filterModeToIntArray(filterMode, pinState);
    digitalWrite(switchesPin[2], pinState[0]);
    digitalWrite(switchesPin[3], pinState[1]);
}

void TCS3200Controller::setFrequencyScaling(TCS3200Controller::FrequencyScaling scaling)
{
    int pinState[2];
    frequencyScalingToIntArray(scaling, pinState);
    digitalWrite(switchesPin[0], pinState[0]);
    digitalWrite(switchesPin[1], pinState[1]);
}

void TCS3200Controller::filterModeToIntArray(FilterMode filterMode, int (&ret)[2])
{
    switch (filterMode)
    {
    case FilterMode::RED:
        ret[0] = LOW;
        ret[1] = LOW;
        break;
    case FilterMode::BLUE:
        ret[0] = LOW;
        ret[1] = HIGH;
        break;
    case FilterMode::NONE:
        ret[0] = HIGH;
        ret[1] = LOW;
        break;
    case FilterMode::GREEN:
        ret[0] = ret[1] = HIGH;
        break;
    }
}

void TCS3200Controller::frequencyScalingToIntArray(FrequencyScaling scaling, int (&ret)[2])
{
    switch (scaling)
    {
    case FrequencyScaling::DOWN:
        ret[0] = ret[1] = LOW;
        break;
    case FrequencyScaling::_2_PERCENT:
        ret[0] = LOW;
        ret[1] = HIGH;
        break;
    case FrequencyScaling::_20_PERCENT:
        ret[0] = HIGH;
        ret[1] = LOW;
        break;
    case FrequencyScaling::_100_PERCENT:
        ret[0] = ret[1] = HIGH;
        break;
    }
}

void TCS3200Controller::setOEPinEnabled(bool flag)
{
    if (OEPin >= 0)
    {
        digitalWrite(OEPin, flag ? HIGH : LOW);
    }
}

void TCS3200Controller::setLedEnabled(bool flag)
{
    if (LEDPin >= 0)
    {
        digitalWrite(LEDPin, flag ? HIGH : LOW);
    }
}

void TCS3200Controller::initialize()
{
    for (int i = 0; i < 4; i++)
    {
        if (switchesPin[i] < 0)
            return;
        else
        {
            pinMode(switchesPin[i], OUTPUT); //Input to the chip is output from the board.
        }
    }

    if (outPin < 0)
        return;
    else
        pinMode(outPin, INPUT);

    if (OEPin >= 0)
        pinMode(OEPin, OUTPUT);

    if (LEDPin >= 0)
        pinMode(LEDPin, OUTPUT);

    initialized = true;
}

TCS3200Controller::operator bool()
{
    return initialized;
}

void TCS3200Controller::test()
{
}

long TCS3200Controller::readRawValue(TCS3200Controller::FilterMode filterMode, const int repeatForAverage = 1)
{
    setColorFilterMode(filterMode);
    int sum = 0;
    for (int i = 0; i < repeatForAverage; i++)
    {
        sum += pulseIn(outPin, LOW);
    }
    return sum / repeatForAverage;
}

double TCS3200Controller::readRawFreq(TCS3200Controller::FilterMode fMode, const int repeatForAverage = 1)
{
    return 1000.0 / readRawValue(fMode, repeatForAverage);
}

typename ::Color TCS3200Controller::measureColor(const int repeatSampling)
{
    typename ::Color color;
    double r = readRawFreq(FilterMode::RED, repeatSampling);
    double g = readRawFreq(FilterMode::GREEN, repeatSampling);
    double b = readRawFreq(FilterMode::BLUE, repeatSampling);

    // sdebug << "BBCFG" << endl
    //        << bbcfg;
    // sdebug << "WBCFG" << endl
    //        << wbcfg;
    // sdebug << r << " " << g << " " << b << endl;

    color.r = mapWithinRange(r, bbcfg.r.baseValue, wbcfg.r.baseValue, 0.0, 255.0);
    color.g = mapWithinRange(g, bbcfg.g.baseValue, wbcfg.g.baseValue, 0.0, 255.0);
    color.b = mapWithinRange(b, bbcfg.b.baseValue, wbcfg.b.baseValue, 0.0, 255.0);

    return color;
}

void TCS3200Controller::performBalance(BalanceConfig &cfg)
{
    const int r = 30;
    cfg.r.baseValue = readRawFreq(FilterMode::RED, r);
    cfg.g.baseValue = readRawFreq(FilterMode::GREEN, r);
    cfg.b.baseValue = readRawFreq(FilterMode::BLUE, r);

    // int idx = wbcfgHeaderAddr;
    // if (&cfg == &wbcfg)
    // {
    //     EEPROM.update(idx++, blcfgLength);
    //     EEPROM.put(idx, wbcfg);
    // }

    // idx += blcfgLength;
    // if (&cfg == &bbcfg)
    // {
    //     EEPROM.update(idx++, blcfgLength);
    //     EEPROM.put(idx, bbcfg);
    // }
}
}

serial::SerialOut &operator<<(serial::SerialOut &out, util::TCS3200Controller::BalanceConfig &cfg)
{
    using namespace serial;
    return out << " R:BaseValue = " << cfg.r.baseValue
               << " G:BaseValue = " << cfg.g.baseValue
               << " B:BaseValue = " << cfg.b.baseValue
               << endl;
}