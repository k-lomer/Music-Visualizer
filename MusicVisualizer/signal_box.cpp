#include "signal_box.h"

#include <algorithm>

#include "dsp_utilities.h"

SignalBox::SignalBox() : raw_max(0.0f), updated_max(0.0f), decay_factor(0.8f), max_decay_factor(0.99f) {}

void SignalBox::update_signal(const wave & new_signal) {
    raw_signal = new_signal;
    weighted_decay_update(updated_abs_signal, abs(raw_signal), decay_factor);
    raw_freq = dft(raw_signal);
    weighted_decay_update(updated_freq, abs(raw_freq), decay_factor);
    raw_max = raw_signal.empty() ? 0.0f : *max_element(std::begin(raw_signal), std::end(raw_signal));
    updated_max = raw_max > updated_max ? raw_max : max_decay_factor * updated_max;
}

wave SignalBox::gen_wave(SignalFlag signal_type) const{
    wave base_wave;
    if (signal_type & Frequency) {
            base_wave = signal_type & Decay ? updated_freq : raw_freq;
    }
    else {
        base_wave = signal_type & Decay ? updated_abs_signal : raw_signal;
    }

    if (signal_type & Reflect) {
        base_wave = add_reflection(base_wave);
    }
    if (signal_type & Normalize) {
        base_wave = normalize(base_wave);
    }

    return base_wave;
}

float SignalBox::get_max(bool decay) const {
    return decay ? updated_max : raw_max;
}
