#ifndef COLORTYPES_H
#define COLORTYPES_H

#include "sout.h"
using serial::SerialOut;

struct ColorHSL;

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    ColorHSL toHSL();
};

struct ColorHSL
{
    unsigned char h;
    unsigned char s;
    unsigned char l;
};

enum ColorType
{
    UNKNOWN,
    WHITE,
    BLACK,
    RED,
    GREEN,
    BLUE
};

const char *colorTypeToCstr(ColorType);

SerialOut& operator<<(SerialOut& out, ColorHSL c);

SerialOut& operator<<(SerialOut& out, Color c);

#endif