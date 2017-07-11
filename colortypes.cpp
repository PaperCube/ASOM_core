#include "colortypes.h"
#include "mathutil.h"

#include "sout.h"
using namespace serial;

ColorHSL Color::toHSL()
{
    // sdebug << "RGB { R=" << r << ", G=" << g << ", B=" << b << "}" << endl;
    ColorHSL hsl;
    const int max = mathutil::maxOf(r, g, b);
    const int min = mathutil::minOf(r, g, b);

    const int range = max - min;

    double h = 0.0;
    if (range == 0)
        h = 0;
    else if (max == r)
        h = (60 * (g - b) / range) % 360;
    else if (max == g)
        h = 60.0 * (b - r) / range + 120;
    else if (max == b)
        h = 60.0 * (r - g) / range + 240;

    hsl.h = mathutil::mapWithinRange(h, 0.0, 360.0, 0.0, 255.0);

    hsl.l = (max + min) / 2;
    hsl.s = range / (255.0 - mathutil::absOf(2.0 * hsl.l - 255.0)) * 255.0;

    // sout << "HSL { H=" << hsl.h << ", S=" << hsl.s << ", L=" << hsl.l << "}" << endl;

    return hsl;
}

const char *colorTypeToCstr(ColorType cltyp)
{
    static const char *typeNames[] = {"Unknown", "White", "Black", "Red", "Green", "Blue"};
    return typeNames[cltyp];
}

SerialOut& operator<<(SerialOut& out, ColorHSL c){
    out << "HSL { H=" << c.h << ", S=" << c.s << ", L=" << c.l << " }";
}

SerialOut& operator<<(SerialOut& out, Color c){
    out << "RGB { R=" << c.r << ", G=" << c.g << ", B=" << c.b << " }";
}
