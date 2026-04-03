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
    float _butter_b[_ButterORDER + 1] = {0.80059240f, 1.60118481f, 0.80059240f};
    float _butter_a[_ButterORDER + 1] = {1.00000000f, 1.56101808f, 0.64135154f};
    float _Butter_buff[_ButterORDER] = {0.0f, 0.0f};

    // --- Butterworth 4nd Order ---
    static const int _Butter4ORDER = 4;
    float _butter4_b[_Butter4ORDER + 1] = {0.66201584f, 2.64806335f, 3.97209502f, 2.64806335f, 0.66201584f};
    float _butter4_a[_Butter4ORDER + 1] = {1.00000000f, 3.18063855f, 3.86119435f, 2.11215536f, 0.43826514f};
    float _Butter4_buff[_Butter4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};

    // --- Bessel 2nd Order ---
    static const int _BesselORDER = 2;
    float _bessel_b[_BesselORDER + 1] = {0.36690154f, 0.73380308f, 0.36690154f};
    float _bessel_a[_BesselORDER + 1] = {1.00000000f, 0.36664359f, 0.10096257f};
    float _Bessel_buff[_BesselORDER] = {0.0f, 0.0f};

    // --- Bessel 4nd Order ---
    static const int _Bessel4ORDER = 4;
    float _bessel4_b[_Bessel4ORDER + 1] = {0.14667875f, 0.58671500f, 0.88007250f, 0.58671500f, 0.14667875f};
    float _bessel4_a[_Bessel4ORDER + 1] = {1.00000000f, 0.77973170f, 0.45580012f, 0.09992817f, 0.01140001f};
    float _Bessel4_buff[_Bessel4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};

    // --- Bessel 4nd Order ---
    static const int _Bessel4ORDER = 4;
    float _bessel4_b[_Bessel4ORDER + 1] = {0.00002987f, 0.00011946f, 0.00017920f, 0.00011946f, 0.00002987f};
    float _bessel4_a[_Bessel4ORDER + 1] = {1.00000000f, -3.52224590f, 4.66711231f, -2.75679304f, 0.61240450f};
    float _Bessel4_buff[_Bessel4ORDER] = {0.0f, 0.0f, 0.0f, 0.0f};
};