#include "TCS3200.h"
#include "sout.h"
#include "stopwatch.h"
#include "ColorDivision.h"
#include "Communicator.h"

using namespace util;
using namespace serial;
using namespace timeutil;
using namespace communication;
TCS3200Controller controller;
Communicator comm(10, 11, 12);

void setup()
{
    sout.init();

    int switches[4] = {3, 4, 5, 6};
    controller.attachSwitchesPin(switches);
    // controller.attachLEDPin(8);
    controller.attachOutPin(2);
    controller.attachOEPin(9);
    controller.initialize();

    if (!controller) //Error handle.
    {
        sout << "Initialization Failed" << endl
             << "Controller State:" << endl;

        for (int i = 0; i < 4; i++)
            sout << controller.switchesPin[i] << endl;
        sout << "switches end" << endl;
        sout << controller.LEDPin << endl;
        sout << controller.outPin << endl;
        return;
    }

    controller.setLedEnabled(true);
    controller.setLedEnabled(false);
    controller.setOEPinEnabled(false);

    controller.setColorFilterMode(TCS3200Controller::FilterMode::BLUE);
    controller.setFrequencyScaling(TCS3200Controller::FrequencyScaling::_20_PERCENT);

    sout << endl
         << endl;
    sout << "Performing White Balance in 5 seconds." << endl;
    delay(5000);
    controller.performWhiteBalance();

    // sout << "Performing Black Balance in 5 seconds." << endl;
    // delay(5000);
    // controller.performBlackBalance();

    // controller.takeOverAll(controller, nullptr); //Decommenting this statement makes everything go automatically.
}

void loop()
{
    using namespace colordiv;
    Color crgb = controller.measureColor(10);
    ColorHSL c = crgb.toHSL();

    // sout << crgb << endl;
    sout << c << endl;

    ColorDivision div;
    int colorType = div.toColorType(c);
    sout << colorTypeToCstr(colorType) << endl;
    // sout << controller.readRFreq() << ';' << controller.readGFreq() << ';' << controller.readBFreq() << endl;
    delay(333);
}
