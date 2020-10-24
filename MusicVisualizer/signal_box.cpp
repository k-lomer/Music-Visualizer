#include "signal_box.h"

#include <algorithm>

#include "dsp_utilities.h"

SignalBox::SignalBox() : raw_max(0.0f), updated_max(0.0f), decay_factor(0.9f), max_decay_factor(0.99f) {}

void SignalBox::update_signal(const wave & new_signal) {
    raw_signal = new_signal;
    weighted_decay_update(updated_abs_signal, abs(raw_signal), decay_factor);
    raw_freq = dft(raw_signal);
    weighted_decay_update(updated_freq, abs(raw_freq), decay_factor);
    raw_max = raw_signal.empty() ? 0.0f : *max_element(std::begin(raw_signal), std::end(raw_signal));
    updated_max = raw_max > updated_max ? raw_max : max_decay_factor * updated_max;
}

wave SignalBox::gen_wave(SignalFlag signal_type, double tapering) const{
    wave base_wave;
    // Get base wave
    if (signal_type & Frequency) {
            base_wave = signal_type & Decay ? updated_freq : raw_freq;
    }
    else {
        base_wave = signal_type & Decay ? updated_abs_signal : raw_signal;
    }

    // Apply effects
    if (signal_type & Reflect) {
        base_wave = add_reflection(base_wave);
    }
    if (signal_type & Normalize) {
        base_wave = normalize(base_wave);
    }

    // Apply linear tapering to wave 
    if (tapering > 0.0 && !base_wave.empty()) {
        size_t wave_length = base_wave.size();
        tapering = std::min(tapering, 0.5);
        int tapering_length = int(double(wave_length) * tapering);
        for (int i = 0; i < tapering_length; ++i) {
            float scale_factor = float(i) / float(tapering_length);
            base_wave[i] *= scale_factor;
            base_wave[wave_length - i - 1] *= scale_factor;
        }
    }

    return base_wave;
}

float SignalBox::get_max(bool decay) const {
    return decay ? updated_max : raw_max;
}
