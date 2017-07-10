#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
  private:
    int dPin, aPin;
    int speed;

  public:
    Motor(int, int);
    void setSpeed(int);
};

#endif