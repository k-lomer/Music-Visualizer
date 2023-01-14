#pragma once

#include "visual_layer.h"
#include "../Utilities/parametric.h"
#include "../Utilities/prominent_peaks.h"

// A parametric curve whose shape varies.
class ParametricCurveLayer : public VisualLayer {
public:
    // ParametricCurveLayer constructor.
    // param: curve_colors                      - the colors to use for the curves
    // param: para_curve                        - the parametric curve to use
    // param: coeff_baseline                    - the minimum value to use for the coefficients
    // param: centre                            - the centre of the curve
    // param: curve_colors                      - the scales of the curves to draw
    // param: horizontal_decrease               - whether the coefficients should increase or decrease in the x direction with peak position
    ParametricCurveLayer(const std::vector<SDL_Color> & curve_colors, const ParametricEquation2d & para_curve, double coeff_baseline,
        const SDL_Point & centre, const std::vector<double> & curve_scales, bool horizontal_decrease)
        : m_peak(1), m_colors(curve_colors), m_curve(para_curve), m_baseline(coeff_baseline), m_centre(centre),  m_scales(curve_scales), m_direction(horizontal_decrease) {
        auto coeffs = m_curve.get_coeffs();
        m_x_coeff = coeffs.first;
        m_y_coeff = coeffs.second;
    }

    // Draw the ParametricCurveLayer.
    // param: renderer                          - the renderer to draw the ParametricCurveLayer
    // param: signal                            - the signal to draw
    virtual void draw(SDL_Renderer * const renderer, const wave & signal) override;

private:
    // The prominent peaks identifier.
    ProminentPeaks m_peak;
    // The colors to draw the curves.
    std::vector<SDL_Color> m_colors;
    // The scales of the curves to draw.
    std::vector<double> m_scales;
    // The parametric curve.
    ParametricEquation2d m_curve;
    // The centre of the curve.
    SDL_Point m_centre;
    // The number of points to draw.
    int m_num_points = 1000;
    // The x coefficient of the curve.
    double m_x_coeff;
    // The y coefficient of the curve.
    double m_y_coeff;
    // The baseline value of the parameters to use.
    double m_baseline;
    // The direction to change the parameters.
    bool m_direction;
};