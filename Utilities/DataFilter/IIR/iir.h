#pragma once
#include <cstdint>

class IIR {
public:
    IIR();
    ~IIR();

    enum FilterType {
        BESSEL2 = 0,
        BESSEL4,      
        BUTTERWORTH2,
        BUTTERWORTH4
    };

    void Init(FilterType filter_type);
    float Process(float in);

private:
    FilterType _filterType;

    // --- Butterworth 2nd Order ---
    static const int _ButterORDER = 2;
    float _butter_b[_ButterORDER + 1] = {0.04948996f, 0.09897991f, 0.04948996f};
    float _butter_a[_ButterORDER + 1] = {1.00000000f, -1.27963242f, 0.47759225f};
    float _Butter_buff[_ButterORDER] = {0.0f, 0.0f};

    // --- Butterworth 4nd Order ---
    static const int _Butter4ORDER = 4;
    float _butter4_b[_Butter4ORDER + 1] = {0.00257643f, 0.01030574f, 0.01545861f, 0.01030574f, 0.00257643f};
    float _butter4_a[_Butter4ORDER + 1] = {1.00000000f, -2.63862774f, 2.76930979f, -1.33928076f, 0.24982167f};
    float _Butter4_buff[_Butter4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};

    // --- Bessel 2nd Order ---
    static const int _BesselORDER = 2;
    float _bessel_b[_BesselORDER + 1] = {0.04503247f, 0.09006495f, 0.04503247f};
    float _bessel_a[_BesselORDER + 1] = {1.00000000f, -1.22400520f, 0.40413510f};
    float _Bessel_buff[_BesselORDER] = {0.0f, 0.0f};

    // --- Bessel 4nd Order ---
    static const int _Bessel4ORDER = 4;
    float _bessel4_b[_Bessel4ORDER + 1] = {0.00215389f, 0.00861557f, 0.01292336f, 0.00861557f, 0.00215389f};
    float _bessel4_a[_Bessel4ORDER + 1] = {1.00000000f, -2.52273724f, 2.48797181f, -1.12811791f, 0.19734562f};
    float _Bessel4_buff[_Bessel4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};
};