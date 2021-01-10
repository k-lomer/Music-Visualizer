#include "bars_layer.h"

#include <algorithm>

#include "draw_utilities.h"

void BarsLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    auto wave = signal_box.gen_wave(signal_type);
    std::vector<float> bar_values;
    // Take max value for bar across wave points in each step
    int bar_step = wave.size() / divisions;
    for (int i = 0; i < divisions; ++i) {
        auto begin = wave.begin() + i * bar_step;
        auto end = begin + bar_step;
        bar_values.push_back(*std::max_element(begin, end));
    }

    draw_bars(renderer, bar_values, start, end, amplitude, color);
    draw_bars(renderer, bar_values, start, end, -amplitude, color);

}
