#ifndef TCS3200_CONTROLLER_PAPERCUBE
#define TCS3200_CONTROLLER_PAPERCUBE

#include <Arduino.h>

#include "sout.h"
#include "mathutil.h"
#include "colortypes.h"


struct Color; //Forward declaration

namespace util
{
class TCS3200Controller
{
  public:
    struct ColorAdjustment
    {
        double baseValue = 0;
    };

    struct BalanceConfig
    {
        ColorAdjustment r;
        ColorAdjustment g;
        ColorAdjustment b;
    };

  public:
    mutable int outPin = -2;
    mutable int switchesPin[4] = {-2, -2, -2, -2}; //S0,S1 -> FrequencyScaling, S2,S3 -> ColorFilterMode
    mutable int OEPin = -2;
    mutable int LEDPin = -2;

    mutable bool initialized = false;
    mutable BalanceConfig wbcfg;
    mutable BalanceConfig bbcfg;

  public:
    enum class FilterMode : unsigned int
    {
        RED,
        GREEN,
        BLUE,
        NONE
    };

    enum class FrequencyScaling : unsigned int
    {
        DOWN,
        _2_PERCENT,
        _20_PERCENT,
        _100_PERCENT
    };

    TCS3200Controller();
    ~TCS3200Controller();
    TCS3200Controller(const TCS3200Controller &);

    void attachOutPin(int pin);
    void attachSwitchesPin(int (&)[4]);
    void attachSwitchPin(int, int);

    void attachOEPin(int);
    void attachLEDPin(int);

    void setColorFilterMode(util::TCS3200Controller::FilterMode);
    void setFrequencyScaling(util::TCS3200Controller::FrequencyScaling);

    void setOEPinEnabled(bool);
    void setLedEnabled(bool);

    void initialize();

    long readRawValue(FilterMode, const int repeatForAverage = 1);
    double readRawFreq(FilterMode, const int repeatForAverage = 1);

    double readRFreq() { return 1000.0 / readRawValue(FilterMode::RED); }
    double readGFreq() { return 1000.0 / readRawValue(FilterMode::GREEN); }
    double readBFreq() { return 1000.0 / readRawValue(FilterMode::BLUE); }
    double readBrightnessFreq() { return 1000.0 / readRawValue(FilterMode::NONE); }

    typename ::Color measureColor(const int = 1);

    void performBalance(BalanceConfig &);
    void performWhiteBalance() { performBalance(wbcfg); }
    void performBlackBalance() { performBalance(bbcfg); }

    explicit operator bool();

    void test();

  protected:
    void filterModeToIntArray(FilterMode, int (&)[2]);
    void frequencyScalingToIntArray(FrequencyScaling, int (&)[2]);
};
}


serial::SerialOut &
operator<<(serial::SerialOut &out, util::TCS3200Controller::BalanceConfig &cfg);

#endif