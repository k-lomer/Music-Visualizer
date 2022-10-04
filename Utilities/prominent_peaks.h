#pragma once

#include <vector>

typedef std::vector<float> wave;

class ProminentPeaks {
public:
    // param: num_peaks - the number of peaks to report
    ProminentPeaks(int num_peaks);

    // Get the positions of the prominent peaks
    // The signal to check
    std::vector< double > get_peak_positions(const wave& signal);

    // based on https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.peak_prominences.html
    static float get_peak_prominence(const wave& signal, int peak_index);

private:
    std::vector< int > get_all_peaks(const wave& signal);
    int num_peaks;
};
