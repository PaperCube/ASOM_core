#ifndef LASERMODULE_UNNAMESAPCED_H
#define LASERMODULE_UNNAMESAPCED_H

#include "WString.h"
class LaserModule
{
  private:
	int pins[8];

  public:
	double interference = 0.0;

	LaserModule(int (&)[8]);
	~LaserModule();

	String toString(char = '*');
	bool got(int);
	bool isBlack(int);
	double geometricalCenter();
	bool aligned();

	double majority(const int = 100);
	double majorityInMicros(const int = 1000);
};

#endif