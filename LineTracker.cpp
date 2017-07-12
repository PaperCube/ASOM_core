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
void LineTracker::host()
{
    while (true)
    {
        update();
    }
    stop();
}

void LineTracker::stop()
{
    l->setSpeed(0);
    r->setSpeed(0);
}

void LineTracker::update()
{
    int speedL = 0, speedR = 0;
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

void LineTracker::goStraight(int lines)
{
    bool isOnline = false;
    int lineCrossed = 0;
    do
    {
        if (lm->isBlack(0) && lm->isBlack(7))
        {
            isOnline == true;
        }
        else if (isOnline)
        {
            lineCrossed++;
            isOnline = false;
        }

        update();
    } while (lineCrossed >= lines);
}

bool goStraightHandler()
{
}

void LineTracker::turnRelatively(int count)
{
}

void LineTracker::forceStraight()
{
    l->setSpeed(standard);
    r->setSpeed(standard);
}