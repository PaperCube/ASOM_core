#ifndef LINE_TRACKER_H
#define LINE_TRACKER_H

#include "Motor.h"
#include "LaserModule.h"

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

	LineTracker(Motor *, Motor *, LaserModule *);
	void setStandard(int, double);
	void host(bool (*)() = nullptr);
	void goStraight(int = -1);
	void forceStraight();
	LaserModule *laser()
	{
		return lm;
	}
};

#endif