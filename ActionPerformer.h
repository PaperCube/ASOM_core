#include <Arduino.h>
#include "Motor.h"
#include "LaserModule.h"
#include "MechanicalArm.h"
#include "colortypes.h"
#include "TCS3200.h"

#ifndef ACTION_PERFORMER_H
#define ACTION_PERFORMER_H

class ActionPerformer
{
  private:
    Servo door;

    void completeMission1();
    int colorOrdinal(ColorType);

  public:
    int doorPin = 0;
    constexpr static ColorType targets[5] = {
        GREEN, WHITE, RED, BLACK, BLUE};
    LineTracker *tracker;
    util::TCS3200Controller *sensor;
    MechanicalArm *arm;

    void givePerformance();
    void init();
    void openDoor();
    void closeDoor();
};

#endif