#include "bars_layer.h"

#include <algorithm>
#include <numeric>

#include "../Utilities/draw_utilities.h"

BarsLayer::BarsLayer(int num_bars, SDL_Point bars_start, SDL_Point bars_end, int bars_amplitude, SDL_Color bars_color, int bars_gap)
    : divisions(num_bars), start(bars_start), end(bars_end), amplitude(bars_amplitude), color(bars_color), gap_pixels(bars_gap) {}

void BarsLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    if (signal.empty()) {
        return;
    }

    // Take the max value for a bar across wave points in each step.
    std::vector<float> bar_values;
    int bar_step = (int)signal.size() / divisions;
    for (int i = 0; i < divisions; ++i) {
        auto begin = signal.begin() + i * bar_step;
        auto end = begin + bar_step;
        bar_values.push_back(*std::max_element(begin, end));
    }

    draw_vertical_bars(renderer, bar_values, start, end, amplitude, gap_pixels, color);
}
