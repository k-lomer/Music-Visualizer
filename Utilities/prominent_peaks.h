#pragma once

#include <vector>

typedef std::vector<float> wave;

// Class for identifying the n most prominent peaks of a signal.
class ProminentPeaks {
public:
    // ProminentPeaks constructor.
    // param: num_peaks - the number of prominent peaks to report
    ProminentPeaks(int num_peaks);

    // Get the positions of the prominent peaks.
    // param: signal                - the signal to check
    // return: std::vector<double>  - the positions of the prominent peaks normalized to the range [0,1]
    std::vector<double> get_peak_positions(const wave& signal);

    // Get the prominence of a peak at a given index.
    // Algorithm based on https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.peak_prominences.html
    // param: signal                - the signal containing the peak
    // param: peak_index            - the index position of the peak in the signal
    // return: float                - the prominence of the peak
    static float get_peak_prominence(const wave& signal, int peak_index);

private:
    // The number of peaks to identify.
    int m_num_peaks;
    // The window size a point must be maximal in to be considered a peak.
    const double m_window_size = 0.05;

    // Get all peaks in a signal.
    // param: signal                - the signal to check
    // return: std::vector<int>     - the indexes of the peaks in the signal
    std::vector<int> get_all_peaks(const wave& signal);
};
