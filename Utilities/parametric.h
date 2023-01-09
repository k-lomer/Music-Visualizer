#pragma once

#include <vector>

#include "SDL.h"

// Compute values based on a trigonometric parametric equation with defined coefficients.
class ParametricEquation2d {
public:
    // The ParametricEquation2d constructor.
    // param: x_a                           - coefficient for x parameter
    // param: y_b                           - coefficient for y parameter
    // param: scale                         - pixel scale of parametric graph
    ParametricEquation2d(double x_a, double y_b, int scale) : m_x_a(x_a), m_y_b(y_b), m_scale(scale) {}

    // Compute the point at parameter t.
    // param: t                             - the parameter value
    // return: SDL_FPoint                   - the computed float point
    SDL_FPoint operator () (double t) const;

    // Generate a vector of points, evenly spaced on the parametric curve.
    // param: num_points                    - the number of points to generate
    // param: t_span                        - the span of t that the points cover
    // param: t_offset                      - the offset from 0 of the points
    // param: join_ends                     - whether to join the first and last points
    // return: std::vector<SDL_FPoint>      - the generated points
    std::vector<SDL_FPoint> gen_even_points(int num_points, double t_span = 2.0 * M_PI, double t_offset = 0.0, bool join_ends = true) const;

    // Set the coefficients of the curve.
    // param: x_coeff                       - the x coefficient
    // param: y_coeff                       - the y coefficient
    void set_coeffs(double x_coeff, double y_coeff) { m_x_a = x_coeff; m_y_b = y_coeff; }

    // Get the coefficients of the curve.
    // return: std::pair<double, double>    - the curve coefficients <x_a, y_b>
    std::pair<double, double> get_coeffs() const { return std::pair<double, double>{m_x_a, m_y_b}; }

private:
    // The x/a coefficient.
    double m_x_a;
    // The y/b coefficient.
    double m_y_b;
    // The scale of the curve.
    double m_scale;
};