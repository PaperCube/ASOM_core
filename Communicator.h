#ifndef INTERBOARD_COMMUNICATOR_H
#define INTERBOARD_COMMUNICATOR_H

#include "colortypes.h"
#include "TCS3200.h"

namespace communication
{
class Communicator
{
  private:
    int pwmOutPin;
    int monitorPin;
    int notifierPin;

  public:
    typedef bool (*BreakCondition)();
    Communicator(int pwmOut, int monitor, int notifier);
    // void initialize();

    void awaitResponse(const unsigned long timeout = 0xFFFFFFFF);
    bool isReplyRequested();
    void sendBack(ColorType);
    void setStateReady(bool);

    void takeOverAll(util::TCS3200Controller &,BreakCondition b = nullptr);
};
}

#endif