#ifndef BUILT_IN_LED
#define BUILT_IN_LED

namespace util
{
class LED
{
  private:
    int pin = 13;

  public:
    LED(int digitalPin = 13);
    void setState(bool);
    void on();
    void off();
};
}

#endif