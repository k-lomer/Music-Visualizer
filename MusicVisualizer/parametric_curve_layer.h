#pragma once

#include "visual_layer.h"
#include "parametric.h"

// A parametric curve whose shape varies with the current amplitude
class ParametricCurveLayer : public VisualLayer {
public:
    // param: curve_color - the color of the curve
    ParametricCurveLayer(const std::vector<SDL_Color> & curve_colors, const ParametricEquation2d & para_curve, double coeff_baseline,
        const SDL_Point & centre, const std::vector<double> & curve_scales, bool horizontal_decrease)
        : colors(curve_colors), curve(para_curve), baseline(coeff_baseline), centre(centre),  scales(curve_scales), direction(horizontal_decrease) {
        auto coeffs = curve.get_coeffs();
        x_coeff = coeffs.first;
        y_coeff = coeffs.second;
    }

    virtual void draw(SDL_Renderer * const renderer, const SignalBox & signal_box) override;

private:
    std::vector<SDL_Color> colors;
    std::vector<double> scales;
    ParametricEquation2d curve;
    SDL_Point centre;
    int num_points = 1000;
    double x_coeff, y_coeff;
    double baseline;
    bool direction;
};