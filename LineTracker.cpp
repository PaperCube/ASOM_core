#include "LineTracker.h"
#include "LaserModule.h"
#include "sout.h"
#include "MechanicalArm.h"
#include "TCS3200.h"
#include "colortypes.h"

using namespace serial;

LineTracker::LineTracker(Motor *lmtr,
                         Motor *rmtr,
                         LaserModule *lmptr,
                         MechanicalArm *arm_ptr) : l(lmtr),
                                                   r(rmtr),
                                                   lm(lmptr),
                                                   arm(arm_ptr)
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
    // while (true)
    // {
    //     update();
    // }
    // stop();
    //=======above: only track lines.
    // colorSensor->performBalance();
    // goStraight(3);
    // turnRelatively(-2);
    // goStraight(1);

    // arm->grab();
    // arm->putUp();
    // arm->release();

    // ColorType color = colorSensor->measureColor();
    // shake();
    // goStraight(1);

    // //put object
    // arm->putDown();

}

void LineTracker::stop()
{
    changeAll(0);
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

void LineTracker::turnRelatively(int cnt, int speed)
{
    int directionFlag = (cnt > 0) ? 1 : -1;
    if (cnt == 0)
        return;

    bool isOnline = false;
    int lineCrossed = 0;

    l->setSpeed(speed * directionFlag);
    r->setSpeed(speed * directionFlag);

    do
    {
        if (lm->isBlack(3))
        {
            isOnline == true;
        }
        else if (isOnline)
        {
            lineCrossed++;
            isOnline = false;
        }

    } while (lineCrossed >= cnt);

    stop();
}

void LineTracker::calibrate()
{
    changeAll(-minPower);
    delay(500);
    while (true)
    {
        bool isLBlack = lm->isBlack(0);
        bool isRBlack = lm->isBlack(7);
        if (isLBlack && isRBlack)
        {
            stop();
            return;
        }
        else if (isLBlack || isRBlack)
        {
            Motor *motorToOperateOn =
                isLBlack ? l : r;

            stop();
            motorToOperateOn->setSpeed(-minPower);
            delay(300);
            stop();
        }
        else
        {
            changeAll(minPower);
        }
    }
}

void LineTracker::changeAll(int speed)
{
    l->setSpeed(speed);
    r->setSpeed(speed);
}

void LineTracker::shake(int cnt)
{
    for (int i = 0; i < cnt; i++)
    {
        changeAll(100);
        delay(100);
        changeAll(-100);
        delay(100);
    }
}

void LineTracker::forceStraight()
{
    l->setSpeed(standard);
    r->setSpeed(standard);
}