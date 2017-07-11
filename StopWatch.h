#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <Arduino.h>
namespace timeutil
{

class AbstractStopWatch
{
  protected:
    unsigned long value;
    virtual unsigned long get() {}

  public:
    virtual AbstractStopWatch();
    virtual unsigned long mark();
    virtual unsigned long peek();
};

class StopWatchInMillis : public AbstractStopWatch
{
  public:
    StopWatchInMillis() : AbstractStopWatch()
    {
        value = get();
    }

  protected:
    virtual unsigned long get() override
    {
        return millis(); //Get time in millisecond
    }
};

class StopWatchInMicros : public AbstractStopWatch
{
  public:
    StopWatchInMicros() : AbstractStopWatch()
    {
        value = get();
    }

  protected:
    virtual unsigned long get() override
    {
        return micros(); //Get time in microsecond
    }
};
}

#endif