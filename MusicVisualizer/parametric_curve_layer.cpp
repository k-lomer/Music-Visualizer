#pragma once

#include "parametric_curve_layer.h"

#include "../Utilities/draw_utilities.h"
#include "../Utilities/parametric.h"


void ParametricCurveLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    double value = peak.get_peak_positions(signal).front();
    if (direction) {
        curve.set_coeffs((x_coeff - baseline) * value + baseline, (y_coeff - baseline) * (1 - value) + baseline);
    }
    else {
        curve.set_coeffs((x_coeff - baseline) * (1 - value) + baseline, (y_coeff - baseline) * value + baseline);
    }
    std::vector<SDL_FPoint> raw_points = curve.gen_even_points(num_points);
    
    for (int i = 0; i < scales.size(); ++i) {
        std::vector<SDL_Point> points = translate(float_to_pixel_points(scale(raw_points, scales[i])), centre);
        // Join the first and last points.
        points.push_back(points[0]);
        SDL_Color color = colors[i % colors.size()];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLines(renderer, &points[0], (int)points.size());
    }
}