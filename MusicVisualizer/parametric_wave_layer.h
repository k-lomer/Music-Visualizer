#pragma once

#include "visual_layer.h"
#include "../Utilities/parametric.h"

// A series of waves between two parametric curves
class ParametricWaveLayer : public VisualLayer {
public:
    ParametricWaveLayer(int num_waves, double span, const SDL_Color & wave_color, const ParametricEquation2d & curve_1, const ParametricEquation2d & curve_2,
        const SDL_Point & centre_1, const SDL_Point & centre_2, double step_size, int amplitude)
        : wave_count(num_waves), wave_span(span), color(wave_color), curve_1(curve_1), curve_2(curve_2),
        centre_1(centre_1), centre_2(centre_2), update_step(step_size), amplitude(amplitude) {}

    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) override;

private:
    int wave_count;
    double wave_span;
    SDL_Color color;
    const ParametricEquation2d curve_1;
    const ParametricEquation2d curve_2;
    SDL_Point centre_1;
    SDL_Point centre_2;
    double update_step;
    double current_pos = 0.0;
    int amplitude;
};