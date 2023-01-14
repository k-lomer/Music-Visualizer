#pragma once

#include "parametric_curve_layer.h"

#include "../Utilities/draw_utilities.h"
#include "../Utilities/parametric.h"


void ParametricCurveLayer::draw(SDL_Renderer * const renderer, const wave & signal) {
    double value = m_peak.get_peak_positions(signal).front();
    if (m_direction) {
        m_curve.set_coeffs((m_x_coeff - m_baseline) * value + m_baseline, (m_y_coeff - m_baseline) * (1 - value) + m_baseline);
    }
    else {
        m_curve.set_coeffs((m_x_coeff - m_baseline) * (1 - value) + m_baseline, (m_y_coeff - m_baseline) * value + m_baseline);
    }
    std::vector<SDL_FPoint> raw_points = m_curve.gen_even_points(m_num_points);
    
    for (int i = 0; i < m_scales.size(); ++i) {
        std::vector<SDL_Point> points = translate(float_to_pixel_points(scale(raw_points, m_scales[i])), m_centre);
        // Join the first and last points.
        points.push_back(points[0]);
        SDL_Color color = m_colors[i % m_colors.size()];
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLines(renderer, &points[0], (int)points.size());
    }
}