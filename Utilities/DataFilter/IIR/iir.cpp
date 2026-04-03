#include "iir.h"
#include <string.h>

IIR::IIR() {}
IIR::~IIR() {}

void IIR::Init(FilterType filter_type) {
    _filterType = filter_type;

    // Reset di tutti i buffer per sicurezza
    memset(_Butter_buff, 0, sizeof(_Butter_buff));
    memset(_Butter4_buff, 0, sizeof(_Butter4_buff));
    memset(_Bessel_buff, 0, sizeof(_Bessel_buff));
    memset(_Bessel4_buff, 0, sizeof(_Bessel4_buff));
}

float IIR::Process(float in) {
    float out = 0.0f;
    float wn = 0.0f;

    switch (_filterType) {
        case BUTTERWORTH2:
            wn = in - (_butter_a[1] * _Butter_buff[0] + _butter_a[2] * _Butter_buff[1]);
            out = _butter_b[0] * wn + _butter_b[1] * _Butter_buff[0] + _butter_b[2] * _Butter_buff[1];
            _Butter_buff[1] = _Butter_buff[0];
            _Butter_buff[0] = wn;
            break;

        case BUTTERWORTH4:
            wn = in - (_butter4_a[1] * _Butter4_buff[0] + _butter4_a[2] * _Butter4_buff[1] + 
                       _butter4_a[3] * _Butter4_buff[2] + _butter4_a[4] * _Butter4_buff[3]);
            out = _butter4_b[0] * wn + _butter4_b[1] * _Butter4_buff[0] + _butter4_b[2] * _Butter4_buff[1] + 
                  _butter4_b[3] * _Butter4_buff[2] + _butter4_b[4] * _Butter4_buff[3];
            _Butter4_buff[3] = _Butter4_buff[2];
            _Butter4_buff[2] = _Butter4_buff[1];
            _Butter4_buff[1] = _Butter4_buff[0];
            _Butter4_buff[0] = wn;
            break;

        case BESSEL2:
            wn = in - (_bessel_a[1] * _Bessel_buff[0] + _bessel_a[2] * _Bessel_buff[1]);
            out = _bessel_b[0] * wn + _bessel_b[1] * _Bessel_buff[0] + _bessel_b[2] * _Bessel_buff[1];
            _Bessel_buff[1] = _Bessel_buff[0];
            _Bessel_buff[0] = wn;
            break;

        case BESSEL4:
            wn = in - (_bessel4_a[1] * _Bessel4_buff[0] + _bessel4_a[2] * _Bessel4_buff[1] + 
                       _bessel4_a[3] * _Bessel4_buff[2] + _bessel4_a[4] * _Bessel4_buff[3]);
            out = _bessel4_b[0] * wn + _bessel4_b[1] * _Bessel4_buff[0] + _bessel4_b[2] * _Bessel4_buff[1] + 
                  _bessel4_b[3] * _Bessel4_buff[2] + _bessel4_b[4] * _Bessel4_buff[3];
            _Bessel4_buff[3] = _Bessel4_buff[2];
            _Bessel4_buff[2] = _Bessel4_buff[1];
            _Bessel4_buff[1] = _Bessel4_buff[0];
            _Bessel4_buff[0] = wn;
            break;
    }
    return out;
}