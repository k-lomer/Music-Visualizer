#include "bars_layer.h"

#include <algorithm>
#include <numeric>
#include <iostream>

#include "../Utilities/draw_utilities.h"

BarsLayer::BarsLayer(int num_bars, SDL_Point bars_start, SDL_Point bars_end, int bars_amplitude, SDL_Color bars_color, int bars_gap)
    : m_divisions(num_bars), m_start(bars_start), m_end(bars_end), m_amplitude(bars_amplitude), m_color(bars_color), m_gap_pixels(bars_gap) {}

void BarsLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    if (signal.empty()) {
        return;
    }

    // Take the max value for a bar across wave points in each window.
    std::vector<float> bar_values;
    if ((int)signal.size() < m_divisions) {
        bar_values = signal;
    }
    else {
        int bar_window = (int)signal.size() / m_divisions;
        int bar_window_leftovers = (int)signal.size() % m_divisions;

        auto bar_window_begin = signal.begin();
        auto bar_window_end = bar_window_begin;
        for (int i = 0; i < m_divisions; ++i) {
            auto bar_window_end = bar_window_begin + bar_window - 1;

            // Include the leftovers at the start and end of the bars.
            if (i < bar_window_leftovers / 2 || i >= (m_divisions - bar_window_leftovers / 2)) {
                ++bar_window_end;
            }
            bar_values.push_back(*std::max_element(bar_window_begin, bar_window_end));
            bar_window_begin = bar_window_end + 1;
        }
    }

    draw_vertical_bars(renderer, bar_values, m_start, m_end, m_amplitude, m_gap_pixels, m_color);
}
