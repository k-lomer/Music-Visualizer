#include "parametric_wave_layer.h"

#include "../Utilities/draw_utilities.h"

void ParametricWaveLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    current_pos += update_step;
    auto wave = signal_box.gen_wave(signal_type , 0.2);

    std::vector<SDL_Point> points_1 = translate(scale(curve_1.gen_even_points(wave_count, wave_span, current_pos, false), 1.0), centre_1);
    std::vector<SDL_Point> points_2 = translate(scale(curve_2.gen_even_points(wave_count, wave_span, current_pos, false), 1.0), centre_2);
    for (size_t i = 0; i < points_1.size(); ++i) {
        draw_wave(renderer, wave, points_1[i], points_2[i], amplitude, color);
    }
}