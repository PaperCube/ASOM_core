#include "LineTracker.h"
#include "LaserModule.h"
#include "sout.h"
using namespace serial;

LineTracker::LineTracker(Motor *lmtr,
                         Motor *rmtr,
                         LaserModule *lmptr) : l(lmtr),
                                               r(rmtr),
                                               lm(lmptr)
{
}

void LineTracker::setStandard(int standard, double sensitivity)
{
    this->standard = standard;
    floating = standard * sensitivity;

    sdebug << "Standard speed is set to " << this->standard << endl;
}

void LineTracker::host(bool (*breakCondition)())
{
    int speedL, speedR;
    while (breakCondition == nullptr || !breakCondition())
    {
        double ct = lm->majorityInMicros(10 * 1000);
        speedL = standard + floating * ct;
        speedR = standard - floating * ct;

        if (lm->interference > interferenceThreshold)
        {
            double veloReductionRate = 1.0 - velocityReduction;
            speedL *= veloReductionRate;
            speedR *= veloReductionRate;
        }

        l->setSpeed(speedL);
        r->setSpeed(speedR);
    }

    l->setSpeed(0);
    r->setSpeed(0);
}

void LineTracker::goStraight(int lines)
{
    bool isOnline = false;
    int lineCrossed = 0;
    host([&]() -> bool {
        if (lm->isBlack(0) && lm->isBlack(7))
        {
            isOnline == true;
        }
        else if (isOnline)
        {
            lineCrossed++;
            isOnline = false;
        }

        return lineCrossed >= lines;
    });
}

void LineTracker::forceStraight()
{
    l->setSpeed(standard);
    r->setSpeed(standard);
}