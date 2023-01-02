#include "bars_layer.h"

#include <algorithm>
#include <numeric>

#include "../Utilities/draw_utilities.h"

void BarsLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    std::vector<float> bar_values;
    // Take max value for bar across wave points in each step
    int bar_step = (int)signal.size() / divisions;
    for (int i = 0; i < divisions; ++i) {
        auto begin = signal.begin() + i * bar_step;
        auto end = begin + bar_step;
        bar_values.push_back(*std::max_element(begin, end));
    }

    draw_vertical_bars(renderer, bar_values, start, end, amplitude, gap_pixels, color);
}
