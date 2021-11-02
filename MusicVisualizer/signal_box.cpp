#include "signal_box.h"

#include <algorithm>

#include "../Utilities/dsp_utilities.h"

SignalBox::SignalBox(unsigned int channels, unsigned long sample_rate)
    : m_channels(channels), m_sample_rate(sample_rate), m_decay_factor(0.92f), m_max_decay_factor(0.99f), m_cutoff_freq(800), m_freq_window(0.3)
{

}

void SignalBox::reset() {
    m_raw_signal = wave();
    m_raw_freq = wave();
    m_updated_abs_signal = wave();
    m_updated_freq = wave();
    m_raw_max = 0.0f;
    m_raw_freq_max = 0.0f;
    m_updated_max = 0.0f;
    m_updated_freq_max = 0.0f;
    m_alltime_max = 0.0f;
    m_alltime_freq_max = 0.0f;
}

void SignalBox::update_signal(const std::vector<std::shared_ptr<wave>> & new_signal) {
    for (const std::shared_ptr<wave>& signal : new_signal) {
        m_previous_signals.push_back(squish_channels(*signal, m_channels));
    }
    wave new_signal_mono = m_previous_signals.back();
    // Add to signal history and remove oldest signals if there are excess samples
    unsigned long min_samples(m_freq_window * m_sample_rate);

    if (min_samples < new_signal_mono.size()) {
        m_previous_signals = { new_signal_mono };
    }
    else {
        m_previous_signals.push_back(new_signal_mono);
        unsigned long total_samples(0);
        for (const wave& signal : m_previous_signals) {
            total_samples += signal.size();
        }
        while (total_samples - m_previous_signals.front().size() > min_samples) {
            total_samples -= m_previous_signals.front().size();
            m_previous_signals.pop_front();
        }
    }
    wave long_signal;
    for (const wave& signal : m_previous_signals) {
        long_signal.insert(long_signal.end(), signal.begin(), signal.end());
    }
    m_raw_signal = new_signal_mono;
    weighted_decay_update(m_updated_abs_signal, abs(m_raw_signal), m_decay_factor);

    wave freq = dft(long_signal);
    unsigned long samples = freq.size();
    unsigned long freq_cutoff_point = std::min( unsigned long(double(samples) * double(m_cutoff_freq) / double(m_sample_rate)), samples /2 );
    m_raw_freq = wave(freq.begin(), freq.begin() + freq_cutoff_point);
    weighted_decay_update(m_updated_freq, abs(m_raw_freq), m_decay_factor);

    m_raw_max = abs_max(m_raw_signal);
    m_updated_max = m_raw_max > m_updated_max ? m_raw_max : m_max_decay_factor * m_updated_max;
    m_alltime_max = m_raw_max == 0.0f ? 0.0f : std::max(m_raw_max, m_alltime_max);

    m_raw_freq_max = abs_max(m_raw_freq);
    m_updated_freq_max = (m_raw_freq_max > m_updated_freq_max ? m_raw_freq_max : m_max_decay_factor * m_updated_freq_max);
    m_alltime_freq_max = (m_raw_freq_max == 0.0f ? 0.0f : std::max(m_raw_freq_max, m_alltime_freq_max));
}

wave SignalBox::gen_wave(SignalFlag signal_type, double tapering) const{
    wave base_wave;
    // Get base wave
    if (signal_type & Frequency) {
            base_wave = (signal_type & Decay ? m_updated_freq : m_raw_freq);
    }
    else {
        base_wave = (signal_type & Decay ? m_updated_abs_signal : m_raw_signal);
    }

    // Apply effects
    if (signal_type & RootZero) {
        float min_value = min(base_wave);
        if (min_value > 0.0f) {
            float max_value = abs_max(base_wave);
            // Root values to zero
            base_wave = vertical_shift(base_wave, -min_value);
            // Scale up to previous size
            base_wave = scale(base_wave, max_value / (max_value - min_value));
        }
    }
    if (signal_type & Reflect) {
        base_wave = add_reflection(base_wave);
    }
    if (signal_type & Normalize) {
        base_wave = normalize(base_wave);
    }
    else { // scale relative to all time maximum value
        float max_value = (signal_type & Frequency ? m_alltime_freq_max : m_alltime_max);
        base_wave = scale(base_wave, 1.0f / max_value);
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
    return decay ? m_updated_max : m_raw_max;
}
