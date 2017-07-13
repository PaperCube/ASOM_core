#include "LineTracker.h"
#include "LaserModule.h"
#include "sout.h"
#include "MechanicalArm.h"
#include "TCS3200.h"
#include "colortypes.h"
#include "ColorDivision.h"
#include "ActionPerformer.h"
#include "mathutil.h"
#include <Arduino.h>

using namespace colordiv;
using namespace mathutil;

///executing this function requires the robot to be
///in initial state.
void ActionPerformer::givePerformance()
{
    completeMission1();
}

void ActionPerformer::completeMission1()
{
    ColorType color;
    ColorDivision division;
    tracker->goStraight(4);
    for (int i = 0; i < 5; i++)
    {
        tracker->turnRelatively(i - 2);
        tracker->goStraight(2); //to storage area of mission 1
        color = division.toColorType(sensor->measureColor());
        int colorOrd = colorOrdinal(color);
        if (colorOrd == i)
        {
            tracker->shake();
            tracker->goStraight(1);
            arm->grab();
            arm->putUp();
            arm->release();
        }
        else
        {
            tracker->doUTurn(1);
            tracker->goStraight(2);
            tracker->shake();

            tracker->turnAbsolutely(0); //issues may occur.
            tracker->turnRelatively(i - colorOrd);
            tracker->goStraight(3); //to target area

            openDoor();
            tracker->reverseToLine();
            tracker->doUTurn(2);
            tracker->goStraight(2);
            tracker->turnAbsolutely(0);
        }
    }
}

int ActionPerformer::colorOrdinal(ColorType type)
{
    for (int i = 0; i < 5; i++)
    {
        if (type == targets[i])
            return i;
    }
    return -1;
}

void ActionPerformer::init()
{
    door.attach(doorPin);
}

void ActionPerformer::openDoor()
{
    door.write(90);
    delay(50);
}

void ActionPerformer::closeDoor()
{
    door.write(0);
    delay(50);
}