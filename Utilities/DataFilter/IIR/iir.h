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
    float _butter_b[_ButterORDER + 1] = {0.97803048f, 1.95606096f, 0.97803048f};
    float _butter_a[_ButterORDER + 1] = {1.00000000f, 1.95557824f, 0.95654368f};
    float _Butter_buff[_ButterORDER] = {0.0f, 0.0f};

    // --- Butterworth 4nd Order ---
    static const int _Butter4ORDER = 4;
    float _butter4_b[_Butter4ORDER + 1] = {0.95978223f, 3.83912892f, 5.75869338f, 3.83912892f, 0.95978223f};
    float _butter4_a[_Butter4ORDER + 1] = {1.00000000f, 3.91790787f, 5.75707638f, 3.76034951f, 0.92118193f};
    float _Butter4_buff[_Butter4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};

    // --- Bessel 2nd Order ---
    static const int _BesselORDER = 2;
    float _bessel_b[_BesselORDER + 1] = {0.39567771f, 0.79135542f, 0.39567771f};
    float _bessel_a[_BesselORDER + 1] = {1.00000000f, 0.46411915f, 0.11859170f};
    float _Bessel_buff[_BesselORDER] = {0.0f, 0.0f};

    // --- Bessel 4nd Order ---
    static const int _Bessel4ORDER = 4;
    float _bessel4_b[_Bessel4ORDER + 1] = {0.17018073f, 0.68072294f, 1.02108440f, 0.68072294f, 0.17018073f};
    float _bessel4_a[_Bessel4ORDER + 1] = {1.00000000f, 0.98221001f, 0.57759838f, 0.14643741f, 0.01664595f};
    float _Bessel4_buff[_Bessel4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};
};