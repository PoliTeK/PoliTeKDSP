
#include "XorM.h"

using namespace politekdsp;
XorM::XorM() {}
XorM::~XorM() {}

void XorM::init()
{
    _mask = 0;
}

float XorM::process(float input, float carrier)
{

    if (_mask == 0 && carrier == 0)
        return input;

    int16_t intInput = (int16_t)(input * 32767.0f);
    int16_t intCarrier = (int16_t)(carrier * 32767.0f);
    _masked = (float)(intInput ^ (_mask + intCarrier));

    return _masked / 32767.0f;
}

void XorM::setMask(float mask)
{
    _mask = (int16_t)(mask * 32767.0f);
}