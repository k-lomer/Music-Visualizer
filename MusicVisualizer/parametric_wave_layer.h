#pragma once

#include "visual_layer.h"
#include "../Utilities/parametric.h"

// A series of waves between two parametric curves.
class ParametricWaveLayer : public VisualLayer {
public:
    // ParamentricWaveLayer constructor.
    // param: num_waves                     - the number of waves to draw
    // param: span                          - the span of parameter t to be covered by the waves
    // param: wave_color                    - the color of the waves
    // param: curve_1                       - the curve defining the start points of the waves
    // param: curve_2                       - the curve defining the end points of the waves
    // param: centre_1                      - the centre of the first curve
    // param: centre_2                      - the centre of the second curve
    // param: step_size                     - the step along parameter t to take at each frame
    // param: amplitude                     - the maximum amplitude of the waves
    ParametricWaveLayer(int num_waves, double span, const SDL_Color & wave_color, const ParametricEquation2d & curve_1, const ParametricEquation2d & curve_2,
        const SDL_Point & centre_1, const SDL_Point & centre_2, double step_size, int amplitude)
        : wave_count(num_waves), wave_span(span), color(wave_color), curve_1(curve_1), curve_2(curve_2),
        centre_1(centre_1), centre_2(centre_2), update_step(step_size), amplitude(amplitude) {}

    // Draw the ParametricWaveLayer.
    // param: renderer                      - the renderer to draw the ParametricWaveLayer
    // param: signal                        - the signal to draw
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    // The number of waves to draw.
    int wave_count;
    // the span of parameter t to be covered by the waves.
    double wave_span;
    // The color of the waves.
    SDL_Color color;
    // The curve defining the start points of the waves.
    const ParametricEquation2d curve_1;
    // The curve defining the end points of the waves.
    const ParametricEquation2d curve_2;
    // The centre of the first curve.
    SDL_Point centre_1;
    // The centre of the second curve.
    SDL_Point centre_2;
    // The amout to update the current position on each frame.
    double update_step;
    // The current position on the parametric curves, parameter t.
    double current_pos = 0.0;
    // The maximum amplitude of the waves.
    int amplitude;
};