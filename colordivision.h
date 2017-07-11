#ifndef COLOR_DIVISION_H
#define COLOR_DIVISION_H

#include "colortypes.h"

namespace colordiv
{
enum Hues : int
{
    RED = 0,
    GREEN = 85,
    BLUE = 171
};

class ColorDivision
{
  protected:
    int blackThres, whiteThres, tolerance;

  public:
    ColorDivision(const int blackThreshold = 40, const int whiteThreshold = 220, const int colorTolerance = 40)
    {
        blackThres = blackThreshold;
        whiteThres = whiteThreshold;
        tolerance = colorTolerance;
    }

    ColorType toColorType(ColorHSL);

    ColorType toColorType(Color c)
    {
        return toColorType(c.toHSL());
    }
};
}

#endif