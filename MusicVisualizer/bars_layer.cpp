#include "bars_layer.h"

#include <algorithm>
#include <numeric>

#include "draw_utilities.h"

void BarsLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    auto wave = signal_box.gen_wave(Decay);
    std::vector<float> bar_values;
    // Take max value for bar across wave points in each step
    int bar_step = (int)wave.size() / divisions;
    for (int i = 0; i < divisions; ++i) {
        auto begin = wave.begin() + i * bar_step;
        auto end = begin + bar_step;
        bar_values.push_back(*std::max_element(begin, end));
        //bar_values.push_back(std::accumulate(begin, end, 0.0f) / (float)bar_step);
    }

    draw_bars(renderer, bar_values, start, end, amplitude, color);
    draw_bars(renderer, bar_values, start, end, -amplitude, color);

}
