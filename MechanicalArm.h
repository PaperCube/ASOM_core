#include <Arduino.h>
#include <Servo.h>

class MechanicalArm
{
  private:
	const int horizontalDegree = 45;

  public:
	int vertical = 0, horizontalL = 0, horizontalR = 0;
	Servo svrV, svrHL, svrHR;
	MechanicalArm(int, int, int);

	void init();

	void putUp();
	void putDown();
	void grab();
	void release();
};