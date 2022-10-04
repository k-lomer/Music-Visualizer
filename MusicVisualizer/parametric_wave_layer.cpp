#include "parametric_wave_layer.h"

#include "../Utilities/draw_utilities.h"

void ParametricWaveLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    current_pos += update_step;
    auto wave = signal;

    std::vector<SDL_Point> points_1 = translate(float_to_pixel_points(scale(curve_1.gen_even_points(wave_count, wave_span, current_pos, false), 1.0)), centre_1);
    std::vector<SDL_Point> points_2 = translate(float_to_pixel_points(scale(curve_2.gen_even_points(wave_count, wave_span, current_pos, false), 1.0)), centre_2);
    for (size_t i = 0; i < points_1.size(); ++i) {
        draw_wave(renderer, wave, points_1[i], points_2[i], amplitude, color);
    }
}