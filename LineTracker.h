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

  protected:

  public:
	int currentDirection = 0; //i had to expose it....
	double interferenceThreshold = 0.45;
	double velocityReduction = 0.15;
	int minPower = 50;

	LineTracker(Motor *, Motor *);
	void setStandard(int, double);
	void host();
	// void host(bool (*)());
	void stop();
	void goStraight(int = -1);
	void turnRelatively(int, int = 80);
	void turnAbsolutely(int);
	void forceStraight();
	void update();
	void calibrate();
	void shake(int = 5);
	void changeAll(int);
	void doUTurn(int);
	void reverseToLine();
	LaserModule *laser()
	{
		return lm;
	}
};

#endif