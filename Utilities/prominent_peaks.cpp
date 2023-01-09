#include "prominent_peaks.h"
#include <algorithm>
#include <queue>
#include <vector>

ProminentPeaks::ProminentPeaks(int num_peaks) : m_num_peaks(num_peaks) {}

std::vector< double > ProminentPeaks::get_peak_positions(const wave& signal) {
    std::vector<int> all_peak_indexes = get_all_peaks(signal);
    std::vector<int> prominent_peak_indexes;
    if (signal.empty() || all_peak_indexes.empty())
    {
        // No peaks!
        // Set all to zero for now, this could be changed to something later
        // e.g. evenly spaced peaks moving at a consistent rate.
        return std::vector<double>(m_num_peaks, 0.0);
    }
    else if (all_peak_indexes.size() > m_num_peaks) {
        // Select num_peaks most prominent peaks.

        // Get peak prominences.
        std::vector<float> peak_significances(all_peak_indexes.size());
        std::transform(all_peak_indexes.begin(), all_peak_indexes.end(), peak_significances.begin(),
            [signal](int x) {return ProminentPeaks::get_peak_prominence(signal, x);});

        // Get index of most prominent peaks.
        std::priority_queue< std::pair<float, int>, std::vector< std::pair<float, int> >, std::greater <std::pair<float, int> > > q;
        for (int i = 0; i < peak_significances.size(); ++i) {
            if (q.size() < m_num_peaks) {
                q.push(std::pair<float, int>(peak_significances[i], all_peak_indexes[i]));
            }
            else if (q.top().first < peak_significances[i]) {
                q.pop();
                q.push(std::pair<float, int>(peak_significances[i], all_peak_indexes[i]));
            }
        }
        while(!q.empty()) {
            prominent_peak_indexes.push_back(q.top().second);
            q.pop();
        }
        std::sort(prominent_peak_indexes.begin(), prominent_peak_indexes.end());
    }
    else {
        std::sort(all_peak_indexes.begin(), all_peak_indexes.end());
        // Front load with the first index
        for (int i = 0; i < m_num_peaks - all_peak_indexes.size(); ++i) {
            prominent_peak_indexes.push_back(all_peak_indexes.front());
        }
        for (const auto& index : all_peak_indexes) {
            prominent_peak_indexes.push_back(index);
        }
    }

    // transform indexes to a double position in the range [0, 1];
    std::vector<double> peak_positions(prominent_peak_indexes.size());
    std::transform(prominent_peak_indexes.begin(), prominent_peak_indexes.end(), peak_positions.begin(),
        [signal](int x) { return double(x) / double(signal.size()); });
    return peak_positions;
}

float ProminentPeaks::get_peak_prominence(const wave& signal, int peak_index) {
    float peak_height = signal[peak_index];

    // Find left peak base.
    float peak_base_left = peak_height;
    for (int i = peak_index - 1; i >= 0; --i) {
        if (signal[i] > peak_height) {
            break;
        }
        peak_base_left = std::min(peak_base_left, signal[i]);
    }

    // Find right peak base.
    float peak_base_right = peak_height;
    for (int i = peak_index + 1; i < int(signal.size()); ++i) {
        if (signal[i] > peak_height) {
            break;
        }
        peak_base_right = std::min(peak_base_right, signal[i]);
    }

    float peak_base = std::max(peak_base_left, peak_base_right);
    return peak_height - peak_base;
}

std::vector< int > ProminentPeaks::get_all_peaks(const wave& signal) {
    std::vector< int > peak_index;

    for (int i = 1; i < int(signal.size()) - 1; ++i) {
        if (signal[i - 1] < signal[i] && signal[i] >= signal[i + 1]) {
            peak_index.push_back(i);
        }
    }

    return peak_index;
}
