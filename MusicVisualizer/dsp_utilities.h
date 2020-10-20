#pragma once

#include <complex>
#include <vector>

typedef std::vector<float> wave;

// Compute the dft of a real signal using the FFT algorithm
// param: signal - the real float values of a signal
// return: wave - the dft of the signal
wave dft(const wave & signal);

// A recursive, FFT implementation
// param: signal - the complex double values of a signal, must have length a power of 2
// return: std::vector<std::complex<double>> - the dft of the signal
std::vector<std::complex<double>> fft(const std::vector<std::complex<double>> & signal);

// Linearly scale a signal so they have absolute max 1
// If the vector is empty or all zero do nothing
// param: signal - the real float values of a signal
// return: wave - the normalized signal
wave normalize(const wave & signal);

// Scale the values in a vector by a given factor
// param: signal - the real float values of a signal
// param: scale_factor - the factor to multiply the values by
// return: wave - the scaled signal
wave scale(const wave & signal, float scale_factor);

// The largest absolute value of the signal
// If the signal is empty return zero
// param: signal - the real float values of a signal
// return: float - the maximum absolute value
float abs_max(const wave & signal);

// Take the absolute of each value in the signal
// param: signal - the float values of a signal
// return: wave - the absolute signal
wave abs(const wave & signal);

// Update the values of a signal with larger new values or decay
// param: previous_signal - the previous values to use
// param: new_signal - the new values to use
// param: decay - value between 0 and 1, the proportion of the previous_signal to keep
void weighted_decay_update(wave & previous_signal, const wave & new_signal, float decay);
