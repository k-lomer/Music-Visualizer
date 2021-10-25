#pragma once

#include "parametric_curve_layer.h"

#include "../Utilities/draw_utilities.h"
#include "../Utilities/parametric.h"


void ParametricCurveLayer::draw(SDL_Renderer * const renderer, const SignalBox & signal_box) {
    float max_value = signal_box.get_max(true);
    if (direction) {
        curve.set_coeffs((x_coeff - baseline) * max_value + baseline, (y_coeff - baseline) * (1 - max_value) + baseline);
    }
    else {
        curve.set_coeffs((x_coeff - baseline) * (1 - max_value) + baseline, (y_coeff - baseline) * max_value + baseline);
    }
    std::vector<SDL_FPoint> raw_points = curve.gen_even_points(num_points);
    
    for (int i = 0; i < scales.size(); ++i) {
        std::vector<SDL_Point> points = translate(scale(raw_points, scales[i]), centre);
        points.push_back(points[0]); // join first and last points
        SDL_Color color = colors[i % colors.size()];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLines(renderer, &points[0], (int)points.size());
    }
}