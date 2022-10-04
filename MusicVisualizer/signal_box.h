#pragma once

#include <deque>
#include <memory>
#include <ostream>
#include <vector>

#include "SDL.h"
#define NOMINMAX // to avoid min and max macros from windows.h
#include <windows.h>

struct SignalBoxConfig {
    // Whether to use a frequency or a sound wave
    bool frequency_wave;
    // The decay factor for each wave, wave has
    float decay_factor;
    // How long a window to use for signal in seconds
    float time_window;
    // Whether to normalize the wave
    bool normalize;
    // Whether to reflect the wave making it symmetrical
    bool reflect;
    // Whether to take the absolute value of the wave
    bool absolute;
    // Whether to fix the minimum value of the wave to magnitude zero.
    bool fix_base;
    // How much to taper the edges of the wave, fixing the endpoints at zero
    // In range (0, 0.5) A value of zero fixes none of the wave, a value of 0.5 tapers the entire wave to the centre
    float taper_edges;
    // The size of window to use for smoothing by moving average as a proportion of the size of the wave
    // In range (0, 0.5) A value of zero performs no smoothing, 0.5 uses half the points
    float smoothing_window;
};

std::ostream& operator<<(std::ostream& os, const SignalBoxConfig& cfg);

typedef std::vector<float> wave;

// SignalBox is a class for handling signals
// Provides processed signals for creating visual layers
class SignalBox {
public:
    SignalBox(unsigned int channels, unsigned long sample_rate);
    ~SignalBox() {}

    // Enforce the bounds of config parameters.
    // param: cfg - the config input
    // return: SignalBoxConfig - the config with the parameter bounds enforced
    SignalBoxConfig enforce_bounds(const SignalBoxConfig& cfg);

    // Reset the signal box
    void reset(const SignalBoxConfig& cfg);

    // Update the base signals
    // param: new_signal - the raw signal to update values
    void update_signal(const std::vector<std::shared_ptr<wave>>& new_signal);

    // Get a wave based on the current stored signals
    // return: wave - the newly generated wave
    const wave& get_wave() const;

    // Get the maximum amplitude of the signal
    // return: float - the maximum value
    float get_max() const;

    
private:
    // Update the base signals
    // param: new_signal - the raw signal to update values
    void update_raw_signal(const std::vector<std::shared_ptr<wave>>& new_signal);

    std::deque< wave > m_previous_signals;
    wave m_raw_signal;
    wave m_processed_signal;
    wave m_updated_abs_signal;

    float m_signal_max = 0.0f;
    float m_updated_max = 0.0f;
    float m_alltime_max = 0.0f;

    SignalBoxConfig m_cfg;

    int m_channels;
    unsigned long m_sample_rate;
    unsigned long m_cutoff_freq;
    double m_freq_window;
};