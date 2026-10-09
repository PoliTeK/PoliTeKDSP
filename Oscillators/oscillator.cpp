
#include "oscillator.h"

using namespace politekdsp;
static inline float Polyblep(float phase_inc, float t);

float Oscillator::Process()
{
    float out, t;
    switch(waveform_)
    {
        case WAVE_SIN: out = sinf(phase_ * TWOPI_F); break;
        
        case WAVE_TRI:
        {
            // Generazione del Triangolo base
            t   = -1.0f + (2.0f * phase_);
            out = 2.0f * (fabsf(t) - 0.5f);
            
            // WAVEFOLDING LIMITATO
            // shape_ (0.0 -> 1.0) imposta un moltiplicatore da 1.0x a 1.9x
            // Fermandosi a 1.9x, la punta ripiegata arriva a 0.1 (o -0.1) e non attraversa lo zero.
            float fold_gain = 1.0f + (shape_ * 0.9f); 
            out *= fold_gain;
            
            // Algoritmo di fold: con un gain massimo di 1.9x non serve più il while().
            // Bastano due if, riducendo il carico sulla CPU.
            if(out > 1.0f) {
                out = 2.0f - out;
            } 
            else if(out < -1.0f) {
                out = -2.0f - out;
            }
            
            break;
        }
        
        case WAVE_SAW:
        {
            if ((phase_ > (c_ - 0.05f) && phase_ < (0.95f - c_)) || c_ == 0.0f)
            {
                out = -1.0f + (phase_ * 2.0f); // Corretto l'=- ambiguo
            }
            else
            {
                out = 1.0f - (phase_ * 2.0f);
            }
            break;
        }
        
        case WAVE_RAMP: out = ((phase_ * 2.0f)) - 1.0f; break;
        case WAVE_SQUARE:
        {
            // shape_ (0.0 -> 1.0)
            // Se shape_ = 1.0 -> duty_cycle = 0.5 (50%, onda quadra perfetta)
            // Se shape_ = 0.0 -> duty_cycle = 0.05 (5%, impulso strettissimo e nasale)
            float duty_cycle = 0.5f - (shape_ * 0.45f);

            out = phase_ < duty_cycle ? 1.0f : -1.0f;
            break;
        }
        
        case WAVE_POLYBLEP_TRI:
            t   = phase_;
            out = phase_ < 0.5f ? 1.0f : -1.0f;
            out += Polyblep(phase_inc_, t);
            out -= Polyblep(phase_inc_, daisysp::fastmod1f(t + 0.5f));
            // Leaky Integrator:
            out       = phase_inc_ * out + (1.0f - phase_inc_) * last_out_;
            last_out_ = out;
            out *= 4.f; 
            break;
            
        case WAVE_POLYBLEP_SAW:
            t   = phase_;
            out = (2.0f * t) - 1.0f;
            out -= Polyblep(phase_inc_, t);
            out *= -1.0f;
            break;
            
        case WAVE_POLYBLEP_SQUARE:
            t   = phase_;
            out = phase_ < shape_ ? 1.0f : -1.0f;
            out += Polyblep(phase_inc_, t);
            out -= Polyblep(phase_inc_, daisysp::fastmod1f(t + (1.0f - shape_)));
            out *= 0.707f; 
            break;
            
        default: out = 0.0f; break;
    }
    
    phase_ += phase_inc_;
    if(phase_ > 1.0f)
    {
        phase_ -= 1.0f;
        eoc_ = true;
    }
    else
    {
        eoc_ = false;
    }
    eor_ = (phase_ - phase_inc_ < 0.5f && phase_ >= 0.5f);

    return out * amp_;
}

float Oscillator::CalcPhaseInc(float f)
{
    return f * sr_recip_;
}

static float Polyblep(float phase_inc, float t)
{
    float dt = phase_inc;
    if(t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.0f;
    }
    else if(t > 1.0f - dt)
    {
        t = (t - 1.0f) / dt;
        return t * t + t + t + 1.0f;
    }
    else
    {
        return 0.0f;
    }
}
