#include "dsp_utilities.h"

#include <algorithm>
#include <complex>
#include <cmath>
#include <functional> 

constexpr double pi = 3.14159265358979323846;

wave dft(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    // pad signal to length power of 2
    size_t n = signal.size();
    int log_2_N = 0;
    while (n > 0) {
        n >>= 1;
        ++log_2_N;
    }
    std::vector<std::complex<double>> padded_complex_signal(int(std::pow(2, log_2_N)), 0.0);
    for (size_t i = 0; i < signal.size(); ++i) {
        padded_complex_signal[i] = std::complex<double>(signal[i]);
    }

    std::vector<std::complex<double>> fft_values = fft(padded_complex_signal);

    int dft_length = std::min(100, int(fft_values.size()));
    wave real_dft_values(dft_length);
    std::transform(fft_values.begin(), fft_values.begin() + dft_length, real_dft_values.begin(),
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

    for (size_t k = 0; k < N / 2; ++k)
    {
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

float abs_max(const wave & signal) {
    if (signal.empty()) {
        return 0.0f;
    }

    auto min_max = std::minmax_element(signal.begin(), signal.end());
    return std::max(std::fabsf(*min_max.first), std::fabsf(*min_max.second));
}

wave abs(const wave & signal) {
    if (signal.empty()) {
        return signal;
    }

    wave abs_signal(signal.size());
    std::transform(signal.begin(), signal.end(), abs_signal.begin(), std::fabsf);
    return abs_signal;
}

void weighted_decay_update(wave & previous_signal, const wave & new_signal, float decay) {
    if (previous_signal.empty()) {
        previous_signal = new_signal;
    }
    else if (new_signal.empty()) {
        for (auto & amplitude : previous_signal) {
            amplitude *= decay;
        }
    }
    else {
        size_t shared_length = std::min(previous_signal.size(), new_signal.size());
        for (size_t i = 0; i < shared_length; ++i) {
            if (new_signal[i] > decay * previous_signal[i]) {
                previous_signal[i] = new_signal[i];
            }
            else {
                previous_signal[i] = decay * previous_signal[i];
            }
        }
        // shrink to smaller size if needed
        if (previous_signal.size() > new_signal.size()) {
            previous_signal.resize(shared_length);
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
