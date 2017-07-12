#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H

#include "Motor.h"
#include "LaserModule.h"
#include "MechanicalArm.h"
#include "TCS3200.h"

class LineTracker
{
  private:
	Motor *l, *r;
	LaserModule *lm;
	int standard = 100;
	int floating = 25;

  public:
	double interferenceThreshold = 0.45;
	double velocityReduction = 0.15;
	MechanicalArm *arm;
	TCS3200Controller *colorSensor;
	int minPower = 50;

	LineTracker(Motor *, Motor *, LaserModule *, MechanicalArm*);
	void setStandard(int, double);
	void host();
	// void host(bool (*)());
	void stop();
	void goStraight(int = -1);
	void turnRelatively(int, int = 50);
	void forceStraight();
	void update();
	void calibrate();
	void shake(int = 5);
	void changeAll(int);
	LaserModule *laser()
	{
		return lm;
	}
};

#endif