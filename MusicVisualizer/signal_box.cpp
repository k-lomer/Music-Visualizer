#include "signal_box.h"

#include <algorithm>
#include <iostream>

#include "../Utilities/dsp_utilities.h"

std::ostream& operator<<(std::ostream& os, const SignalBoxConfig& cfg) {
    os << "{freq: " << cfg.frequency_wave << ", decay_factor:" << cfg.decay_factor << ", time:" << cfg.time_window
        << ", normalize:" << cfg.normalize << ", reflect:" << cfg.reflect << ", absolute:" << cfg.absolute
        << ", fix_base:" << cfg.fix_base << ", taper:" << cfg.taper_edges << ", smoothing:" << cfg.smoothing_window << "}";
    return os;
}


SignalBox::SignalBox(unsigned int channels, unsigned long sample_rate)
    : m_channels(channels), m_sample_rate(sample_rate), m_cutoff_freq(800)
{
}

SignalBoxConfig SignalBox::enforce_bounds(const SignalBoxConfig& cfg) {
    SignalBoxConfig ret = cfg;
    ret.taper_edges = std::max(0.0f, std::min(0.5f, cfg.taper_edges));
    ret.smoothing_window = std::max(0.0f, std::min(0.5f, cfg.smoothing_window));
    return ret;
}

void SignalBox::reset(const SignalBoxConfig& cfg) {
    m_cfg = enforce_bounds(cfg);
    m_updated_abs_signal = wave();
    m_signal_max = 0.0f;
    m_updated_max = 0.0f;
    m_alltime_max = 0.0f;
    m_processed_signal = wave();
}

void SignalBox::update_signal(const std::vector<std::shared_ptr<wave>> & new_signal) {
    wave previous_signal = m_processed_signal;
    update_raw_signal(new_signal);

    if (m_cfg.frequency_wave) {
        wave freq = dft(m_raw_signal);
        size_t samples = freq.size();
        size_t freq_cutoff_point = std::min(size_t(double(samples) * double(m_cutoff_freq) / double(m_sample_rate)), samples / 2);
        m_processed_signal = wave(freq.begin(), freq.begin() + freq_cutoff_point);
    }
    else {
        m_processed_signal = m_raw_signal;
    }

    if (m_cfg.absolute) {
        m_processed_signal = abs(m_processed_signal);
    }

    if (m_cfg.smoothing_window > 0.0f) {
        unsigned int smoothing_window_size = unsigned int(m_cfg.smoothing_window * double(m_processed_signal.size()));
        m_processed_signal = smooth(m_processed_signal, smoothing_window_size);
    }

    m_signal_max = abs_max(m_processed_signal);
    if (m_cfg.decay_factor > 0.0) {
        m_updated_max = m_signal_max > m_updated_max ? m_signal_max : m_cfg.decay_factor * m_updated_max;
    }
    else {
        m_updated_max = m_signal_max;
    }
    m_alltime_max = (m_signal_max == 0.0f ? 0.0f : std::max(m_signal_max, m_alltime_max));


    if (m_cfg.normalize) {
        m_processed_signal = normalize(m_processed_signal);
    }
    else if(m_alltime_max > 0.0f) {
        m_processed_signal = scale(m_processed_signal, 1.0f / m_alltime_max);
    }

    // Apply linear tapering to wave 
    if (m_cfg.taper_edges > 0.0 && !m_processed_signal.empty()) {
        size_t wave_length = m_processed_signal.size();
        int tapering_length = int(double(wave_length) * m_cfg.taper_edges);
        for (int i = 0; i < tapering_length; ++i) {
            float scale_factor = float(i) / float(tapering_length);
            m_processed_signal[i] *= scale_factor;
            m_processed_signal[wave_length - i - 1] *= scale_factor;
        }
    }

    if (m_cfg.decay_factor > 0.0)
    {
        weighted_decay_update(previous_signal, m_processed_signal, m_cfg.decay_factor);
    }

    if (m_cfg.reflect) {
        m_processed_signal = max_reflection(m_processed_signal);
    }

    if (m_cfg.fix_base) {
        float min_point = min_element(m_processed_signal);
        m_processed_signal = vertical_shift(m_processed_signal, min_point);
    }
}

void SignalBox::update_raw_signal(const std::vector<std::shared_ptr<wave>>& new_signal)
{
    // Get a sample length to use if a wave is empty.
    // Use a default or a previous size if available.
    size_t sample_length = 100;
    if (!m_previous_signals.empty()) {
        m_previous_signals.back().size();
    }
    for (const std::shared_ptr<wave>& signal : new_signal) {
        if (signal->empty()) {
            m_previous_signals.push_back(wave(sample_length, 0.0f));
        }
        else {
            m_previous_signals.push_back(squish_channels(*signal, m_channels));
        }
    }
    wave new_signal_mono = m_previous_signals.empty() ? wave() : m_previous_signals.back();
    // Add to signal history and remove oldest signals if there are excess samples.
    size_t min_samples = size_t(m_cfg.time_window * double(m_sample_rate));

    if (min_samples < new_signal_mono.size()) {
        m_previous_signals = { new_signal_mono };
    }
    else {
        m_previous_signals.push_back(new_signal_mono);
        size_t total_samples(0);
        for (const wave& signal : m_previous_signals) {
            total_samples += signal.size();
        }
        while (total_samples - m_previous_signals.front().size() > min_samples) {
            total_samples -= m_previous_signals.front().size();
            m_previous_signals.pop_front();
        }
    }
    m_raw_signal.clear();
    for (const wave& signal : m_previous_signals) {
        m_raw_signal.insert(m_raw_signal.end(), signal.begin(), signal.end());
    }
}

const wave& SignalBox::get_wave() const {
    return m_processed_signal;
}

float SignalBox::get_max() const {
    return m_signal_max;
}
