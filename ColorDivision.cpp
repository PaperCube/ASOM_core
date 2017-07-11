#include "ColorDivision.h"
#include "mathutil.h"

using namespace mathutil;

namespace colordiv
{
bool mayBe(int, Hues, int);

ColorType ColorDivision::toColorType(ColorHSL clr)
{
    int hue = clr.h;
    if (clr.l >= whiteThres)
        return ColorType::WHITE;
    else if (clr.l <= blackThres)
        return ColorType::BLACK;
    else if (mayBe(hue, Hues::RED, tolerance))
        return ColorType::RED;
    else if (mayBe(hue, Hues::GREEN, tolerance))
        return ColorType::GREEN;
    else if (mayBe(hue, Hues::BLUE, tolerance))
        return ColorType::BLUE;
    else
        return ColorType::UNKNOWN;
}

bool mayBe(int hue, Hues hueRef, int tolerance)
{
    int hueRefVal = hueRef;
    return inCircularRange(hue, hueRefVal - tolerance, hueRefVal + tolerance, 256);
}
}