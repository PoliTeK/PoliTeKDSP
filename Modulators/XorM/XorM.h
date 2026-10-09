#pragma once
#ifndef XORM_H
#define XORM_H


#include <stdint.h>
#include <math.h>
namespace politekdsp
{
class XorM
{
public:
    XorM();
    ~XorM();


    void init();

    float process(float input, float carrier);

    void setMask(float mask);

    int16_t getMask() { return _mask; }
    
private:
    int16_t _mask;
    float _masked;
};
};

#endif