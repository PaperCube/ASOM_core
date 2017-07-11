#include "MechanicalArm.h"
#include <Arduino.h>

MechanicalArm::MechanicalArm(int vPin,
                             int hPinL,
                             int hPinR) : vertical(vPin),
                                          horizontalL(hPinL),
                                          horizontalR(hPinR)
{
}

void MechanicalArm::init()
{
    svrV.detach();
    svrHL.detach();
    svrHR.detach();
    svrV.attach(vertical);
    svrHL.attach(horizontalL);
    svrHR.attach(horizontalR);
}

void MechanicalArm::putUp()
{
    svrV.write(90);
}

void MechanicalArm::putDown()
{
    svrV.write(0);
}

void MechanicalArm::grab()
{
    svrHL.write(horizontalDegree);
    svrHR.write(-horizontalDegree);
}

void MechanicalArm::release()
{
    svrHL.write(0);
    svrHR.write(0);
}
