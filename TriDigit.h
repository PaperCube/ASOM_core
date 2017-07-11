#ifndef TRIDIGIT_H
#define TRIDIGIT_H

namespace communication
{

typedef unsigned char byte;
class TriDigit
{
    public:
    int pins[3];
    bool isOut;

    TriDigit(int, int, int, bool);

    void write(byte);

    int read();

};
}

#endif