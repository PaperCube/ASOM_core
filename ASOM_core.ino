#include "LaserModule.h"
#include "sout.h"
#include "LineTracker.h"
#include "Motor.h"

LaserModule *lm = nullptr;
Motor *motors[2] = {nullptr, nullptr};
LineTracker *tracker = nullptr;

using namespace serial;
void setup()
{
    sout.init();

    int pins[8] = {30, 31, 32, 33, 34, 35, 36, 37};
    lm = new LaserModule(pins);

    motors[0] = new Motor(4, 5);
    motors[1] = new Motor(7, 6);

    tracker = new LineTracker(motors[0], motors[1], lm);
    tracker->setStandard(65, 0.45);
    tracker->interferenceThreshold = 0.65;
    tracker->velocityReduction = 0.0;
    // tracker->host([&]() -> bool {
    //     !lm->aligned();
    // });

    tracker->host();
    // tracker->forceStraight();
}

void loop()
{
}