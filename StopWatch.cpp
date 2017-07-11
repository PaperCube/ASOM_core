#include "StopWatch.h"
#include "sout.h"
using namespace serial;

namespace timeutil
{

AbstractStopWatch::AbstractStopWatch(){}

unsigned long AbstractStopWatch::mark()
{
    unsigned long old = value;
    value = get();
    return value - old;
}

unsigned long AbstractStopWatch::peek()
{
    return get() - value;
}
}