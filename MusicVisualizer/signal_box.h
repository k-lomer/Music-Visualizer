#pragma once

#include <vector>
#include <deque>

#include "SDL.h"
#define NOMINMAX // to avoid min and max macros from windows.h
#include <windows.h>

enum SignalFlag {
    RawSignal   = 0,
    Frequency   = 1 << 0,
    Decay       = 1 << 1,
    Reflect     = 1 << 2,
    Normalize   = 1 << 3,
    RootZero    = 1 << 4
};

// From windows.h, defines all bitwise operators for SignalFlag enums
DEFINE_ENUM_FLAG_OPERATORS(SignalFlag)

typedef std::vector<float> wave;

// SignalBox is a class for handling signals
// Provides processed signals for creating visual layers
class SignalBox {
public:
    SignalBox(unsigned int channels, unsigned long sample_rate);
    ~SignalBox() {}

    // Reset the signal box
    void reset();

    // Update the base signals
    // param: new_signal - the raw signal to update values
    void update_signal(const wave & new_signal);

    // Generate a wave based on the current stored signals
    // param: signal_type - the flags describing the processing
    // param: tapering - the fraction of the signal to taper to 0 at the ends
    // return: wave - the newly generated wave
    wave gen_wave(SignalFlag signal_type, double tapering = 0.0) const;

    // Get the maximum amplitude of the signal
    // param: decay - whether to use the decayed updated signal or the raw signal
    // return: float - the maximum value
    float get_max(bool decay) const;

    
private:
    std::deque< wave > m_previous_signals;
    float m_decay_factor;
    float m_max_decay_factor;
    wave m_raw_signal;
    wave m_raw_freq;
    wave m_updated_abs_signal;
    wave m_updated_freq;

    float m_raw_max = 0.0f;
    float m_raw_freq_max = 0.0f;
    float m_updated_max = 0.0f;
    float m_updated_freq_max = 0.0f;
    float m_alltime_max = 0.0f;
    float m_alltime_freq_max = 0.0f;

    int m_channels;
    unsigned long m_sample_rate;
    unsigned long m_cutoff_freq;
    double m_freq_window;
};