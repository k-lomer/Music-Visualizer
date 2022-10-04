#pragma once

#include "visual_layer.h"
#include "../Utilities/parametric.h"
#include "../Utilities/prominent_peaks.h"

// A parametric curve whose shape varies
class ParametricCurveLayer : public VisualLayer {
public:
    // param: curve_colors - the colors to use for the curves
    // param: para_curve - the parametric curve to use
    // param: coeff_baseline - the minimum value to use for the coefficients
    // param: centre - the centre of the curve
    // param: horizontal_decrease - whether the coefficients should increase or decrease in the x direction with sound amplitude
    ParametricCurveLayer(const std::vector<SDL_Color> & curve_colors, const ParametricEquation2d & para_curve, double coeff_baseline,
        const SDL_Point & centre, const std::vector<double> & curve_scales, bool horizontal_decrease)
        : peak(1), colors(curve_colors), curve(para_curve), baseline(coeff_baseline), centre(centre),  scales(curve_scales), direction(horizontal_decrease) {
        auto coeffs = curve.get_coeffs();
        x_coeff = coeffs.first;
        y_coeff = coeffs.second;
    }

    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    ProminentPeaks peak;
    std::vector<SDL_Color> colors;
    std::vector<double> scales;
    ParametricEquation2d curve;
    SDL_Point centre;
    int num_points = 1000;
    double x_coeff, y_coeff;
    double baseline;
    bool direction;
};