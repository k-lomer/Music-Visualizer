#include "dsp_utilities.h"

#include <iostream>
#include <algorithm>
#include <complex>
#include <cmath>
#include <functional> 

constexpr double pi = 3.14159265358979323846;

wave dft(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    // Trim the signal to length power of 2.
    size_t n = signal.size();
    int log_2_N = 0;
    while (n > 1) {
        n >>= 1;
        ++log_2_N;
    }
    std::vector<std::complex<double>> trimmed_complex_signal(int(std::pow(2, log_2_N)));
    for (size_t i = 0; i < trimmed_complex_signal.size(); ++i) {
        trimmed_complex_signal[i] = std::complex<double>(signal[i]);
    }

    std::vector<std::complex<double>> fft_values = fft(trimmed_complex_signal);

    wave real_dft_values(fft_values.size());
    std::transform(fft_values.begin(), fft_values.end(), real_dft_values.begin(),
        [](std::complex<double> c)->float {return float(std::abs(c)); });

    return real_dft_values;
}

std::vector<std::complex<double>> fft(const std::vector<std::complex<double>> & signal) {
    if (signal.empty()) {
        return signal;
    }

    size_t N = signal.size();
    if (N <= 1) {
        return signal;
    }

    std::vector<std::complex<double>> even;
    std::vector<std::complex<double>> odd;

    for (size_t i = 0; i < N; ++i) {
        if (i % 2 == 0) {
            even.push_back(signal[i]);
        }
        else {
            odd.push_back(signal[i]);
        }
    }

    even = fft(even);
    odd = fft(odd);

    std::vector<std::complex<double>> dft(N, 0.0f);

    for (size_t k = 0; k < N / 2; ++k) {
        std::complex<double> t = std::polar(1.0, -2 * pi * k / N) * odd[k];
        dft[k] = even[k] + t;
        dft[k + N / 2] = even[k] - t;
    }

    return dft;
 }

wave normalize(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    float max_entry = abs_max(signal);
    return scale(signal, 1.0f / max_entry);
}

wave scale(const wave & signal, float scale_factor) {
    if (signal.empty()) {
        return signal;
    }

    wave scaled_signal(signal.size());
    std::transform(signal.begin(), signal.end(), scaled_signal.begin(),
        std::bind(std::multiplies<float>(), std::placeholders::_1, scale_factor));
    return scaled_signal;
}

wave vertical_shift(const wave & signal, float shift){
    if (signal.empty()) {
        return signal;
    }

    wave shifted_signal(signal.size());
    std::transform(signal.begin(), signal.end(), shifted_signal.begin(),
        std::bind(std::plus<float>(), std::placeholders::_1, shift));
    return shifted_signal;
}

float abs_max(const wave & signal) {
    if (signal.empty()) {
        return 0.0f;
    }

    auto min_max = std::minmax_element(signal.begin(), signal.end());
    return std::max(std::fabsf(*min_max.first), std::fabsf(*min_max.second));
}

float min_element(const wave & signal) {
    if (signal.empty()) {
        return 0.0f;
    }
    return *std::min_element(signal.begin(), signal.end());
}

wave abs(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    wave abs_signal(signal.size());
    std::transform(signal.begin(), signal.end(), abs_signal.begin(), std::fabsf);
    return abs_signal;
}

void weighted_decay_update(const wave & previous_signal, wave & new_signal, float decay) {
    if (new_signal.empty()) {
        new_signal = scale(previous_signal, decay);
    }
    else if (!previous_signal.empty()) {
        wave decayed_signal = scale(previous_signal, decay);
        decayed_signal.resize(new_signal.size(), 0.0f);

        for (size_t i = 0; i < new_signal.size(); ++i) {
            if (std::fabs(new_signal[i]) < std::fabs(decayed_signal[i])) {
                new_signal[i] = decayed_signal[i];
            }
        }
    }
}

wave add_reflection(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    wave reflection(signal);
    std::reverse(reflection.begin(), reflection.end());
    std::transform(signal.begin(), signal.end(), reflection.begin(), reflection.begin(), std::plus<float>());
    return reflection;
}

wave max_reflection(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    wave reflection(signal);
    std::reverse(reflection.begin(), reflection.end());
    std::transform(signal.begin(), signal.end(), reflection.begin(), reflection.begin(),
        [](float a, float b) {return std::max(a, b); });
    return reflection;
}

wave smooth(const wave & signal, unsigned int window_size) {
    if (signal.size() < window_size || window_size < 2) {
        return signal;
    }

    wave smoothie(signal.size() - window_size + 1, 0.0);
    for (unsigned int i = 0; i < smoothie.size(); ++i) {
        for (unsigned int j = 0; j < window_size; ++j) {
            smoothie[i] += signal[i + j];
        }

        smoothie[i] /= window_size;
    }

    return smoothie;
}

wave squish_channels(const wave& signal, unsigned int channels) {
    if (channels <= 1) {
        return signal;
    }

    wave mono(signal.size() / channels, 0.0);
    for (unsigned int i = 0; i < mono.size(); ++i) {
        for(unsigned int j=0; j < channels; ++j)
        mono[i] += signal[channels * i + j];
    }

    return mono;
}

