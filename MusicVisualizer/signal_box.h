#pragma once

#include <vector>

#include "SDL.h"
#define NOMINMAX // to avoid min and max macros from windows.h
#include <windows.h>

enum SignalFlag {
    RawSignal   = 0,
    Frequency   = 1 << 0,
    Decay       = 1 << 1,
    Reflect     = 1 << 2,
    Normalize   = 1 << 3
};

// From windows.h, defines all bitwise operators for SignalFlag enums
DEFINE_ENUM_FLAG_OPERATORS(SignalFlag)

typedef std::vector<float> wave;

class SignalBox {
public:
    SignalBox();
    ~SignalBox() {}
    void update_signal(const wave & new_signal);
    wave gen_wave(SignalFlag signal_type, double tapering = 0.0) const;
    float get_max(bool decay) const;
    
private:
    float decay_factor = 0.9f;
    float max_decay_factor = 0.9f;
    wave raw_signal;
    wave raw_freq;
    float raw_max;
    wave updated_abs_signal;
    wave updated_freq;
    float updated_max;
};